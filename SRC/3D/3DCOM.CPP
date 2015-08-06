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
//Filename       3dcom.cpp
//System     
//Author         Paul.   
//Date           Wed 16 Aug 1995
//Description    
//------------------------------------------------------------------------------

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//				           INCLUDE FILES
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴


#ifndef	NDEBUG
//#define	TRAILREPORT
//#define	_DRAW_COLBOX_
//#define	   _NOSMOKETRAILS_
//#define	MEMTRACE
//#define	_IMAP_TEXTURE_MEM_
//DeadCode RJS 20Apr00 #define	_NOLENSFLARE_
//#define	_LIGHTEXTREME_

//#define	_FXTEST_
//#define _NO_MIST
//#define	_BOMBBUG_
#ifdef	_FXTEST_
const	int	AOFF_LEFTIN = 142;
const	int	AOFF_RIGHTIN = 144;
const	int	AOFF_ENGLEFT = 145;
const	int	AOFF_ENGRIGHT = 146;
static bool	logDamage = false;
#endif

#define	DBGMEMTEST
//DeadCode RJS 9Aug00 #define	_SIMPLETRAIL_
//#define	_NOPOLYS_
//#define	_NOPOINTS_
//#define	_NOBODY_
//#define	_PROCDEBUG_
//#define	_BIGPROCDEBUG_
///#define	_NODOT_
//#define	_NOLINE_
//DeadCode RJS 16Oct00 #define	_REPLAYCOL_
#endif

	#include	"DOSDefs.h"
	//#include	"MAClib.h"f
#define F_GRAFIX												//DAW 05Aug96
//DeadCode RJS 17Oct96 #define F_SOUNDS
#define F_BATTLE
	#include	"Files.g"
	#include 	"myerror.h"
	#include	"FileMan.h"
	#include 	"Palette.h"
//deaded	#include	"Fonts.h"
	#include	"myAngles.h"
	#include	"Worldinc.h"
	#include	"AnimData.h"									//RJS 10Feb97

	#include	"3DDefs.h"
 	#include	"World.h"
//	#include	"3DInstr.h"
	#include	"shapes.h"										//RJS 02Dec97
	#include	"3DCom.h"
#define MATRIX_CODE_REQ
	#include	"Matrix.h"
	#include	"polygon.h"										//RJS 02Dec97
	#include	"3dcode.h"
	#include	"shpbld.h"										//PD 22Jan96
	#include	"landscap.h"									//MGA 09May96
//DeadCode DAW 23Feb98 	#include	"Wrapper.h"										//PD 26Oct95

	#include	"Mytime.h"										//PD 15Mar96

	#include	"keytest.h"										//PD 01Apr96

	#include	"flymodel.h"									//PD 16Apr96
	#include	"Transite.h"									//PD 24Apr96
	#include	"mymath.h"										//RJS 25Jul96
	#include	"savegame.h"									//RJS 12Aug96
	#include	"missman2.h"										//RDH 24Oct96
	#include	"viewsel.h"										//RJS 30Aug96
	#include	"LnchrDat.h"									//RJS 09Sep96
	#include	"speed.h"										//RJS 01Oct96
	#include	"miles.h"										//RJS 17Oct96
	#include	"BoxCol.h"										//RJS 24Feb97
	#include	"shpweap.h"										//RJS 16Apr97
	#include	"deathnum.g"									//RJS 23May97
	#include "monotxt.h"
	#include <stdio.h>											//ARM 09Jun97

	#include	"shpinstr.h"									//RJS 03Jul98
	#include	"modinst.h"										//RJS 03Jul98
	#include	"weappak.h"										//RJS 03Jul98
	#include	"model.h"										//RJS 03Jul98
	#include	"smktrl.g"										//RJS 03Jul98
#include	"winmove.h"
#include	"persons2.h"
#include	<string.h>
#include	"replay.h"
	#include	"shapenam.h"
#include "fastmath.h"
#include	"sqddiary.h"										//RJS 21Feb00

FastMath fastMath;
ULong FastMath::fastSqrtTable[0x10000];
SWord FastMath::tableCode1[65536];
SWord FastMath::tableCode2[257];										//JIM 08/06/00
#include	"animmove.h"										//RJS 17Nov99
#include	"intcock.h"											//RJS 19Nov99
#include	"smktrls.h"											//RJS 09Feb00

#ifdef	_DRAW_COLBOX_
#include	"overlay.h"
#endif

// revs per min = ANGLES_360Deg / 6000
const	Float	REV_PER_MIN = 65.536/6.;						//RJS 28Mar00
const	ULong	MAX_TIME_OFF_SCREEN_SMOKE	= 4500;				//RJS 6Sep00
const	ULong	MAX_TIME_OFF_SCREEN_VAPOUR	= 3000;				//RJS 6Sep00

const float	MIN_SAMP_DIST = (512.f * float(Timer_Code.FRAMETIME));	//RJS 6Nov00
const float	MIN_SAMP_DIST_SQUARED = MIN_SAMP_DIST*MIN_SAMP_DIST;	//RJS 6Nov00

static	int	poopy = 0;

static	void*	poopitem;

#ifdef	__WATCOMC__
	extern	"C" SLong ASM_GetFadeColour(SLong, SLong );			//PD 10May96
#else
#ifdef	__MSVC__
//-----------------------------------------------------------------------------
// Procedure    ASM_GetFadeColour
// Author       Paul
// Date         05/11/97
//
// Description  
//
// Inputs       
//
// Returns      
//
//-----------------------------------------------------------------------------
extern	"C" void XASM_GetFadeColour(void);
#pragma warning (disable:4035)
inline	SLong ASM_GetFadeColour(SLong a, SLong b)
{
	_asm {
		mov		eax,a
		mov		edx,b
		call	XASM_GetFadeColour
	}
}
#pragma warning (default:4035)
#endif
#endif
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//				      EXTERNAL REFERENCES
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//	extern	KeyMapping	*Debug3dMapTable;						//PD 01Apr96
//
//	extern class matrix _matrix;
//	extern class Error _Error;		//For 'EmitSysErr'

//DEADCODE PD 03/12/99 	extern SWord winmode_w;					//RJS 04Nov98

	class shape	SHAPE;

//DeadCode RJS 01Dec97 	shape::InterpProc*	shape::InterpTable[dosetglassrangeno+1];
	shape::InterpProc*	*shape::InterpTable;
	UByteP				shape::animflags;
	SLong				shape::fade_start,
						shape::fade_end,
						shape::object_dist;

//DeadCode PD 10Jan97 	MATRIX_PTR 			shape::object_matrix;
	FPMATRIX_PTR 		shape::fpobject_matrix;
	Obj3DPtr	  		shape::object_obj3d;					//RJS 07Feb00
	FPMATRIX_PTR 		shape::fprealobject_matrix;				//RJS 15Jan99

	CLib3D*				shape::g_lpLib3d;
	Colour				shape::colour;
	HMATERIAL			shape::hMaterial;

	ColourRange			shape::range;
	ImageMapNumber		shape::image;

	SWord 				shape::shapescale,
						shape::AnimWeaponPack;					//RJS 11May98

	shape::GlobalAnimTime	shape::globalanimtime;
	TrailRecord		shape::traillist[REAL_MAX_VAPOURS];				//RJS 21Jan99
	DoPointStruc		*shape::newco;							//RJS 02Dec97
//	static DoPointStruc		shape::shpco[MAX_DOPOINTS];				//RJS 02Dec97
	 UByte		shape::lastdamage[8];					//RJS 23Feb99
	 UByte		shape::laststationdamage[8];					//RJS 06Apr98
	 UByteP		shape::lastdamptr;						//RJS 21Feb97
	 UWord		shape::HitThisOffset;					//RJS 24Nov98
	 Bool			shape::CommsDamage;						//RJS 15May97
	 Bool			shape::CollisionOn;						//RJS 21Feb97

	 DoPointStruc		shape::CylPnt1;						//RJS 14May97
	 DoPointStruc		shape::CylPnt2;						//RJS 14May97
	 Bool				shape::VapourCyl;					//RJS 15May97

	 UByte	shape::VapourAnim;							//RJS 20May97
	 Bool		shape::IsSubShape;							//RJS 03Jun97
	LightVec	shape::TransLightVector;					//PD 13Nov97
	LightVec	shape::TransViewVector;
	LightVec	shape::ViewLightVector;					//PD 13Nov97
	FPMATRIX	shape::light_matrix;						//PD 13Nov97
	Bool		shape::ClearMorph;								//RJS 12Mar98
			static	SWord	vsin_ang;							//RJS 17Mar98
	SWord		shape::v_sin_ang;
	SWord		shape::v_cos_ang;

	UByte	shape::RandTable[256];						//RJS 17Nov97
	ViewPoint*	shape::View_Point;					//JIM

	SByte	shape::VapDeadList[REAL_MAX_VAPOURS];				//RJS 21Jan99
	int		shape::VapDeadCnt;									//RJS 09Apr98
	UWord 	shape::andedFlags;
	UWord 	shape::oredFlags;
	SWord 	shape::polyVertCount;
	DoPointStruc* shape::polyVertIndex[64];
	bool	shape::specularEnabled;
	bool	shape::doingHW3D;
	AirStrucPtr	shape::globinitairitem;							//RJS 13May98
	SWord	shape::oldAlphaSwitch;								//RJS 04Jun98
	Bool	shape::DamageNow;									//RJS 07Jul98
	SLong	shape::CollisionCnt;								//RJS 07Jul98
	Bool	shape::FixUpCollision;								//RJS 07Jul98
	SphTreeTypeP	shape::SphereTree;							//RJS 09Jul98
	SphTreeTypeP	shape::SphereTreeTable;						//RJS 09Jul98
	UByte	shape::SphereList[256];								//RJS 09Jul98
	SLong	shape::GlobSphereCnt;								//RJS 09Jul98
	Bool	shape::DrawnClouds;									//RJS 16Jul98
	ItemPtr	shape::damage_ItemPtr;	//RJS 25Aug98
	animptr	shape::damage_AnimPtr;								//RJS 21Apr99
	SLong	shape::damage_Scale;	//RJS 25Aug98
   ShapeNum shape::damage_Shape;	//RJS 16Sep98
    SLong	shape::damage_GrpElmt;	//RJS 16Sep98
	animptr	shape::damage_GrpAnimPrev;							//RJS 21Apr99
	animptr	shape::damage_GrpAnimNext;							//RJS 21Apr99
	UByteP	shape::damage_GrpPrev;
	UByteP	shape::damage_GrpNext;
	UByteP	shape::damage_Sdptr;
	SWord shape::dotNLineFadeValue;
	ItemPtr	shape::pTrailItm;						//RJS 02Sep98
	Float	shape::DistScale;
//deadcode	UByte	shape::staticRed;									//PD 20Jan99
//deadcode	UByte	shape::staticGreen;									//PD 20Jan99
//deadcode	UByte	shape::staticBlue;									//PD 20Jan99
//deadcode	UByte	shape::shadedRed;									//PD 20Jan99
//deadcode	UByte	shape::shadedGreen;									//PD 20Jan99
//deadcode	UByte	shape::shadedBlue;									//PD 20Jan99

	ULong	shape::shadedRGBlo;
	ULong	shape::shadedRGBhi;
	ULong	shape::shadedRGBamb;
	ULong	shape::staticRGBlo;
	ULong	shape::staticRGBhi;
	ULong	shape::staticRGBamb;

	bool	shape::fSpecialShade;
	bool	shape::fPolyPitShade;
	animptr	shape::damage_GrpTokenDep;							//RJS 21Apr99
	animptr	shape::GlobalAdptr;									//RJS 21Apr99
	UByte	shape::damage_ItemState;							//RJS 26Apr99
	UByte	shape::current_level;
	UByte	shape::IsAircraft;

	bool	shape::oldMipMapState;								//RJS 24May99

	FPMATRIX		shape::subMatrix;							//DAW 07May99
	FPMATRIX_PTR	shape::subMatrixP;							//DAW 07May99

	SLong	shape::gunsightX;									//AMM 25Jun99
	SLong	shape::gunsightY;									//AMM 25Jun99
	SLong	shape::gunsightZ;									//AMM 25Jun99
	ULong	shape::gunsightmvel;								//RJS 12Nov99

	SLong	shape::animlag;										//RJS 30Jun99

//From Footy...

	SLong	shape::anim_posesize;								//RJS 08Nov99
	SLong	shape::anim_framesize;								//RJS 08Nov99
	FPMATRIX_PTR	shape::fpanim_matrix;						//RJS 08Nov99
	FPMATRIX_PTR	shape::fplight_matrix;						//RJS 08Nov99
	FPMATRIX		shape::anim_matrix;							//RJS 08Nov99
	FPMATRIX		shape::animlight_matrix;					//RJS 08Nov99
	Coords3D		shape::anim_translation;					//RJS 08Nov99

	void*	shape::theBlokeAnimPtr;								//RJS 17Nov99
	bool	shape::interactivefound;							//RJS 18Nov99
	void*	shape::globalSdptr;									//RJS 18Nov99
	SWord	shape::lastMX;										//RJS 19Nov99
	SWord	shape::lastMY;										//RJS 19Nov99
	bool	shape::lastMPressed;								//RJS 19Nov99

	SLong	shape::vd_width;									//RJS 22Nov99
	SLong	shape::vd_height;									//RJS 22Nov99
	Float	shape::vd_hoD;										//RJS 22Nov99
	SLong	shape::vd_originx;									//RJS 23Nov99
	SLong	shape::vd_originy;									//RJS 23Nov99

	bool	shape::reargunner_active;							//RJS 10Dec99
	SWord	shape::reargunner_index;							//RJS 10Dec99
	SWord	shape::reargunner_launcher;							//RJS 10Dec99
	AirStrucPtr	shape::reargunner_item;							//RJS 10Dec99
	SWord	shape::gunner_minHdg;
	SWord	shape::gunner_arcHdg;
	SWord	shape::gunner_minPitch;
	SWord	shape::gunner_arcPitch;
	SLong	shape::reargunner_pivotx;
	SLong	shape::reargunner_pivoty;
	SLong	shape::reargunner_pivotz;
	SWord	shape::reargunner_launchtime;								//RJS 23May00

	MyGroundVectorPtr	shape::damage_GrpOffset;				//RJS 26Nov99

	SWordP	shape::intAnimMatrixPtr;							//RJS 17Feb00
	SWord	shape::intSubAnimMatrix[9];							//RJS 17Feb00
	SWord	shape::reargunner_cockpitindex;						//RJS 28Feb00

	ULong	shape::bakRGBlo;									//RJS 23Feb00
	ULong	shape::bakRGBhi;									//RJS 23Feb00
	ULong	shape::bakRGBamb;									//RJS 23Feb00

	float	shape::movegunmatrix[9];							//RJS 28Feb00

	Coords3D	shape::reargunner_eyeoffset;

	float	shape::anim_interpolatefrac;						//RJS 20Mar00
	bool	shape::anim_firstframe;								//RJS 20Mar00
	UByteP	shape::anim_nextframe;								//RJS 20Mar00

	int		shape::anim_interpolatemul;							//RJS 05Apr00
	int 	shape::anim_morphframe;								//RJS 05Apr00
	void*	shape::theNextBlokeAnimPtr;							//RJS 05Apr00

	UByte	shape::alphaRestore[32];							//RJS 18May00
	SWord	shape::alphaRestoreCnt;								//RJS 18May00

	int		shape::collisionDepth;								//RJS 16Jun00

	ColBoxInfo	shape::lastColBox;										//RJS 19Oct00


//...from Footy

#ifndef	NDEBUG

#define AFX_CDECL __cdecl
typedef char CHAR;
#define CONST               const
typedef CONST CHAR *LPCSTR, *PCSTR;
typedef LPCSTR LPCTSTR;
void AFX_CDECL AfxTrace(LPCTSTR lpszFormat, ...);

#endif


class	Bollox
{
public:
	Bollox(const char*	theName)
	{
//DeadCode RJS 15Aug00 		static	int	theWindow = AllocConsole();
	}

	~Bollox()
	{
	}
};



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	shape::shape
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
shape::shape()
{
	InterpTable = new InterpProc*[dosetglassrangeno+1];			//RJS 01Dec97

	if (InterpTable)
	{
		InterpTable[dopointno] 				= &dopoint;
		InterpTable[dopolygonno] 			= &dopolygon;
		InterpTable[dosetlcno] 				= &dosetlc;
		InterpTable[dosetcolourno] 			= &dosetcolour;
		
		InterpTable[dolineno] 				= &doline;
		InterpTable[doretno] 				= &doret;
		InterpTable[doifcrossno] 			= &doifcross;
		InterpTable[dogosubno] 				= &dogosub;

		InterpTable[doifeqno] 				= &doifeq;
		InterpTable[doifneno] 				= &doifne;		
		InterpTable[donopno] 				= &donop;
		InterpTable[dogroupno] 				= &dogroup;

		InterpTable[dogotono] 				= &dogoto;
		InterpTable[doendno] 				= &doend;
		InterpTable[dowindowdialno] 		= &dowindowdial;	//RJS 06Apr98
		InterpTable[doattitudeno] 			= &doattitude;		//RJS 01Apr98

		InterpTable[dodotno] 				= &dodot;
		InterpTable[doscalesizeno] 			= &doscalesize;		//RJS 03Mar98
		InterpTable[dogunsightno] 			= &dogunsight;		//RJS 04Mar98
		InterpTable[dowheelsprayno] 		= &dowheelspray;

		InterpTable[doifbrightno] 			= &doifbright;		//RJS 20Mar98
		InterpTable[doquikpolyno] 			= &doquikpoly;
		InterpTable[dofadeenvelopeno] 		= &dofadeenvelope;	//RJS 27Mar98
		InterpTable[dowhiteoutno] 			= &dowhiteout;		//RJS 31Mar98

		InterpTable[donpointsno] 			= &donpoints;
		InterpTable[don4cmpntsno] 			= &don4cmpnts;
		InterpTable[do4cmpntno] 			= &do4cmpnt;
		InterpTable[dondupvecno] 			= &dondupvec;

		InterpTable[dondeltapointsno]		= &dondeltapoints;	//RJS 02Jun98
		InterpTable[dodrawsunno] 			= &dodrawsun;		//RJS 22Jun98
		InterpTable[dosetcolour256no] 		= &dosetcolour256;
		InterpTable[doswitchno] 			= &doswitch;

		InterpTable[dosetcolourallno] 		= &dosetcolourall;
		InterpTable[dopoint2xno] 			= &dopoint2x;
		InterpTable[do4cmpt2xno] 			= &do4cmpt2x;
		InterpTable[doifcaseno] 			= &doifcase;

		InterpTable[donincpntsno] 			= &donincpnts;
		InterpTable[dotransparentonno] 		= &dotransparenton;
		InterpTable[dotransparentoffno] 	= &dotransparentoff;
		InterpTable[dosphereno] 			= &dosphere;

		InterpTable[dosmokedonno] 			= &dosmokedon;
		InterpTable[dosmokedoffno] 			= &dosmokedoff;
		InterpTable[donormalno] 			= &donormal;
		InterpTable[dosmoothpolyno] 		= &dosmoothpoly;

		InterpTable[dovectorno] 			= &dovector;
		InterpTable[dotransformlightno] 	= &dotransformlight;
		InterpTable[dolshadeonno] 			= &dolshadeon;			//RJS 30Apr98
		InterpTable[dorelpolyno] 			= &dorelpoly;

		InterpTable[donspheresno]	 		= &donspheres;			//RJS 13Jul98
		InterpTable[donspheresimapdno]	 	= &donspheresimapd;		//RJS 13Jul98
		InterpTable[doweaponoffno] 			= &doweaponoff;			//RJS 13Jul98
		InterpTable[dodrawreflectpolyno] 	= &dodrawreflectpoly;	//RJS 26Aug98

		InterpTable[doresetanimno] 			= &doresetanim;		//RJS 13Nov98
		InterpTable[dospinno] 				= &dospin;				//RJS 19Nov98
		InterpTable[dosetcolourhno] 		= &dosetcolourh;
		InterpTable[doquiksmoothpolyno]		= &doquiksmoothpoly;

		InterpTable[doreposno] 				= &dorepos;
		InterpTable[dodepthcolourno] 		= &dodepthcolour;
		InterpTable[dodepthpolyno] 			= &dodepthpoly;
		InterpTable[doimagemapno] 			= &doimagemap;

		InterpTable[docreateipolyno] 		= &docreateipoly;
		InterpTable[docreateivertno] 		= &docreateivert;
		InterpTable[dodrawipolyno] 			= &dodrawipoly;
		InterpTable[docopyivertno] 			= &docopyivert;

		InterpTable[dosmthrelpolyno] 		= &dosmthrelpoly;
		InterpTable[doquikrelpolyno] 		= &doquikrelpoly;
		InterpTable[donsubsno] 				= &donsubs;
		InterpTable[dobitsofffxno] 			= &dobitsofffx;		//RJS 15Jan99

		InterpTable[doondamagedno] 			= &doondamaged;		//RJS 18Jan99
		InterpTable[dosetmipmapno] 			= &dosetmipmap;		//RJS 24May99
		InterpTable[donvecno] 				= &donvec;
		InterpTable[donextvecno] 			= &donextvec;

		InterpTable[donpoint2xno] 			= &donpoint2x;
		InterpTable[docallshapeno] 			= &docallshape;
		InterpTable[dosmokepntno] 			= &dosmokepnt;
		InterpTable[dobitsoffno] 			= &dobitsoff;

		InterpTable[doplumepntno] 			= &doplumepnt;
		InterpTable[doisphereno] 			= &doisphere;
		InterpTable[docreaterpolyno] 		= &docreaterpoly;
		InterpTable[dodrawipolysno] 		= &dodrawipolys;

		InterpTable[domappolyno] 			= &domappoly;
		InterpTable[dosetmapmapno] 			= &dosetmapmap;
		InterpTable[do3dbreakno] 			= &do3dbreak;
		InterpTable[docylinderno] 			= &docylinder;

		InterpTable[dontpointsno] 			= &dontpoints;
		InterpTable[dosetmapoffno] 			= &dosetmapoff;
		InterpTable[dosetmappingplanerno]	= &dosetmappingplaner;
		InterpTable[dosetmappingtanno] 		= &dosetmappingtan;

		InterpTable[dosmktrailno] 			= &dosmktrail;
		InterpTable[dooffsetpntno] 			= &dooffsetpnt;
		InterpTable[doicylinderno] 			= &doicylinder;
		InterpTable[dodrawbetweenno] 		= &drawbetween;

		InterpTable[docreatebumppolyno] 	= &docreatebpoly;
		InterpTable[docopybvertno] 			= &docopybvert;
		InterpTable[dodrawbpolyno] 			= &dodrawbpoly;
		InterpTable[dodrawrpolyno] 			= &dodrawrpoly;

		InterpTable[dodrawopolyno] 			= &dodrawopoly;
		InterpTable[dorealisphereno] 		= &dorealisphere;	//RJS 16Dec97
		InterpTable[dolauncherno] 			= &dolauncher;
		InterpTable[dodialno] 				= &dodial;

		InterpTable[docompassno] 			= &docompass;
		InterpTable[doiswitchno] 			= &doiswitch;
		InterpTable[doinclnno] 				= &doincln;
		InterpTable[doanimationno] 			= &doanimation;			//RJS 18Feb97

		InterpTable[docollisionno] 			= &docollision;			//RJS 18Feb97
		InterpTable[dodamageno] 			= &dodamage;			//RJS 18Feb97
		InterpTable[doeffectno] 			= &doeffect;			//RJS 18Feb97
		InterpTable[dodrawstationno]		= &dodrawstation;		//RJS 28Feb97
		InterpTable[docaserangeno]			= &docaserange;			//RJS 03Mar97
		InterpTable[doifpilotedno]			= &doifpiloted;			//RJS 07Mar97
		InterpTable[donivertsno]			= &doniverts;			//RJS 20Mar97

		InterpTable[dotrifanno]				= &dotrifan;			//RJS 27Mar97
		InterpTable[dotrizagno]				= &dotrizag;			//RJS 27Mar97
		InterpTable[dotrifanflatno]			= &dotrifanflat;		//RJS 16Apr97
		InterpTable[dotrizagflatno]			= &dotrizagflat;		//RJS 16Apr97

		InterpTable[dostretchpointno]		= &dostretchpoint;		//RJS 11Jun97
		InterpTable[dostretchmapno]			= &dostretchmap;		//RJS 11Jun97

		InterpTable[doflipvectorno]			= &doflipvector;		//RJS 30Jul97
		InterpTable[doflipnvecno]			= &doflipnvec;			//RJS 30Jul97

		InterpTable[domorphpointno]			= &domorphpoint;	//RJS 10Dec97
		InterpTable[domorphnpointsno]		= &domorphnpoints;	//RJS 10Dec97
		InterpTable[douserealtimeno]		= &douserealtime;	//RJS 10Dec97
		InterpTable[dotimerphaseno]			= &dotimerphase;	//RJS 10Dec97
		InterpTable[dobloblineno]			= &doblobline;		//RJS 15Dec97
		InterpTable[dowheeldamageno]		= &dowheeldamage;
		InterpTable[dolightno]				= &dolight;
		InterpTable[dolighttimerno]			= &dolighttimer;	//RJS 06Jan98
		InterpTable[dodigitdialno]			= &dodigitdial;		//RJS 08Jan98
		InterpTable[donianimvertsno]		= &donianimverts;	//RJS 13Jan98
		InterpTable[dosetluminosityno]		= &dosetluminosity;	//RJS 20Jan98
		InterpTable[dobitsoffcockno]		= &dobitsoffcock;	//RJS 23Jan98
		InterpTable[domorphsphereno]		= &domorphsphere;	//RJS 27Jan98
		InterpTable[domorphcylinderimapdno]	= &domorphsphereimapd;//RJS 19Nov98
		InterpTable[doheathazeno]			= &doheathaze;	//RJS 30Jan98

		InterpTable[doifhard3dno]			= &doifhard3d;			//RJS 04Feb98
		InterpTable[domorphnsphrsno]		= &domorphnsphrs;		//RJS 04Feb98
		InterpTable[domorphnsphrsimapdno]	= &domorphnsphrsimapd;	//RJS 04Feb98

// 3DS MAX...
		InterpTable[dosetposeno]			= &dosetpose;		//RJS 05Nov99
		InterpTable[doenvanimno]			= &doenvanim;		//RJS 05Nov99
		InterpTable[dontrianglesno]			= &dontriangles;	//RJS 05Nov99
		InterpTable[donmaxpointsno]			= &donmaxpoints;	//RJS 05Nov99
		InterpTable[doanimmatrixno]			= &doanimmatrix;	//RJS 05Nov99
		InterpTable[dobitsoffblokeno]		= &dobitsoffbloke;	//RJS 05Nov99
															
		InterpTable[dosetmaterialtypeno]	= &dosetmaterialtype;//RJS 05Nov99
		InterpTable[doanimtransformno]		= &doanimtransform;	//RJS 10Nov99
		InterpTable[docreatemirrorno]		= &docreatemirror;	//RJS 18Nov99
		InterpTable[dointeractivehitboxno]	= &dointeractivehitbox;//RJS 19Nov99
		InterpTable[dotmorphnpointsno]		= &dotmorphnpoints;	//RJS 01Dec99

		InterpTable[doabsolutetimerphaseno] = &doabsolutetimerphase;//RJS 02Dec99
		InterpTable[doanimtransformhpno]	= &doanimtransformhp;	//RJS 03Dec99
		InterpTable[doontimerno]			= &doontimer;		//RJS 10Dec99
		InterpTable[dofingerno]				= &dofinger;		//RJS 13Dec99
		InterpTable[donanimvecno]			= &donanimvec;		//RJS 17Feb00

		InterpTable[doambientonno]			= &doambienton;		//RJS 23Feb00
		InterpTable[doambientoffno]			= &doambientoff;	//RJS 23Feb00
		InterpTable[domovegunno]			= &domovegun;		//RJS 28Feb00

		InterpTable[dosetglassrangeno] 		= &dosetglassrange;
		InterpTable[dobitsoffcockunsetno]	= &dobitsoffcockunset;//RJS 22Mar00
		InterpTable[doneedleno]				= &doneedle;		//RJS 12Apr00
		InterpTable[dosetblendtypeno]		= &dosetblendtype;	//RJS 16May00
		InterpTable[dousefadeenvelopeno]	= &dousefadeenvelope;//RJS 18May00

		InterpTable[dorestorealphano]		= &dorestorealpha;	//RJS 18May00
		InterpTable[docollisiongotono]		= &docollisiongoto;	//RJS 21Sep00
		InterpTable[dosetzbiasno]			= &dosetzbias;		//RJS 21Sep00
		
		InterpTable[0] 						= &donop;				//RJS 11Feb98
	}
	else
		_Error.EmitSysErr(__FILE__":Could not create interptable!");

	int		i;

	shape_ptr = NULL;
	draw_data = NULL;

	globalanimtime.centisec =
		globalanimtime.tnthssec =
		globalanimtime.secs = 0;								//PD 08Mar96

	animflags = new UByte [MAXANIMFLAG];

	for (i=0; i < REAL_MAX_VAPOURS; i++)						//RJS 21Jan99
	{
		traillist[i].thelist = NULL;							//RJS 20Sep96
		traillist[i].lifetime = 0;								//RJS 29May97
		traillist[i].nopoints = 0;								//RJS 29May97
		traillist[i].bitshift = 0;								//RJS 29May97
		traillist[i].nextlist = 0;								//RJS 29May97
		traillist[i].beendrawn = 0;								//RJS 29May97
		traillist[i].LaunchCountdown = -1;						//RJS 25Nov97
		traillist[i].SampleTime = 0;							//RJS 08Jan98
		traillist[i].FakePointPtr = NULL;						//RJS 25Feb98
//DeadCode RJS 06May99 		traillist[i].InitVelH = 0;								//RJS 09Apr98
//DeadCode RJS 06May99 		traillist[i].InitVelY = 0;								//RJS 09Apr98
//DeadCode RJS 06May99 		traillist[i].Acceleration = 0;							//RJS 09Apr98
		traillist[i].SmkDescPtr = NULL;							//RJS 09Apr98
		traillist[i].cloudlaunched = FALSE;						//RJS 03Jul98
		traillist[i].transient = 0;								//RJS 22Jan99
		traillist[i].currTime = 0;								//RJS 16Jun99

#ifdef	_SMOKETRAILDEBUG_
		traillist[i].theItemPtr=NULL;
#endif

	}

	for (i=0; i < 8; i++)
	{
		lastdamage[i] = 0;										//RJS 23Feb98
		laststationdamage[i] = 0;								//RJS 06Apr98
	}

	lastdamptr = 0;											//RJS 18Feb97
	HitThisOffset = 0;											//RJS 21Feb97
	CommsDamage = FALSE;										//RJS 21Feb97
	CollisionOn = FALSE;										//RJS 21Feb97

	VapourAnim = 0;												//RJS 20May97

	for (i = 0; i < 256; i++)									//RJS 17Nov97
		RandTable[i] = (Math_Lib.rnd() >> 8);					//RJS 17Nov97

	newco = shpco;												//RJS 02Dec97
#ifndef	_NO_VERTEX_SHARING_HDR
	// set up the dopoint numbers in the newco thingy.					//JON 5/24/00
	for ( i = 1; i <= MAX_DOPOINTS; i++ )
	{
		newco->info.setDoPointNum( i );
		newco++;
	}
#endif
	newco = shpco;

	object_obj3d = NULL;										//RJS 18Mar98
	DoWhiteFade = 0;											//RJS 31Mar98
	VapDeadCnt = 0;

	ClosestGap = 1000000;
//	RequiredRange = 50000;										//MS 30Nov98
	RequiredRange = 40000;										//MS 30Nov98
	WingSpan = 35 * 16 * 2;
	ValidGunSight = FALSE;
	globinitairitem = NULL;
	FixUpCollision = FALSE;
	CollisionCnt = 0;

	AnimDeltaList = new ReplayAnimOffsets[sizeof(PolyPitAnimData)];
	SphereTree= NULL;											//RJS 09Jul98
	SphereTreeTable = new SphTreeType[256];						//RJS 09Jul98
	GlobSphereCnt = 0;											//RJS 09Jul98
	OldWhiteFade = 0;											//RJS 15Jul98
	DrawnClouds = FALSE;											//RJS 15Jul98
	MaxMuzzles = 0;
	damage_ItemPtr = NULL;
	damage_AnimPtr = ANIM_NULL;
	damage_Scale = 0;
	pTrailItm = NULL;											//RJS 02Sep98
	damage_Shape = (ShapeNum) 0;
	damage_Sdptr = NULL;

	animptr	poo;												//RJS 21Apr99
	SetGroupDamage(-1,NULL,NULL,poo,poo,poo);					//RJS 21Apr99

	ClosestGap2 = 1000000;										//RJS 09Nov98

	poopitem = NULL;

	damage_GrpTokenDep = ANIM_NULL;									//RJS 30Nov99
	newprobecnt = 0;											//AMM 26Mar99

//DeadCode AMM 14Apr99 	safeTrail = FALSE;
	radarTimer = -1;											//RJS 07Apr99
	fSpecialShade=false;
	fPolyPitShade=false;
	globinititem = NULL;

	damage_ItemState = 0;										//AMM 26Apr99

	subMatrixP = &subMatrix;

	fpanim_matrix = NULL;										//RJS 08Nov99
	fplight_matrix = &animlight_matrix;							//RJS 08Nov99

	lastMX = 0;													//RJS 19Nov99
	lastMY = 0;													//RJS 19Nov99

	damage_GrpOffset = NULL;									//RJS 26Nov99

	reargunner_active = false;									//RJS 10Dec99
	reargunner_cockpitindex = 0;

	collisionDepth = 0;

	lastMActive = false;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		shape
//Author		Paul.   
//Date			Mon 15 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
shape::~shape()
{
	delete InterpTable;											//RJS 01Dec97
	delete []AnimDeltaList;											  //JIM 02/05/99
	delete animflags;											//PD 27Mar96
	delete []SphereTreeTable;									//RJS 09Jul98
	pTrailItm = NULL;											//RJS 02Sep98
}

inline double ARCCOS(double x,double pi)
{
	double temp=(1.-x*x)/(x*x);
	bool xneg=x<0?true:false;
	_asm{
		fld temp;
		fsqrt;
		fld1;
		fpatan;
		fstp temp;
	}
	if (xneg) temp=pi-temp;
	return temp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		calcSpecular
//Author		Paul.   
//Date			Tue 25 Aug 1998
//
//Description	generates a value to be used for specular lighting
//				based on the dot product of the light and view vectors
//				with the vertex normal.
//
//Inputs		result of the two dot products
//
//Returns	
//
//------------------------------------------------------------------------------
void calcSpecular(Float& specDot,Float& lightDot,SLong& specular,SLong& specFlip)
{
	double pi;
	_asm
	{
		fldpi;
		fstp pi;
	}

	double spa=ARCCOS(specDot,pi);
	double lia=ARCCOS(lightDot,pi);

	if (spa<pi/2. && lia<pi/2.)
	{
		double delta=spa-lia; delta=delta<0?-delta:delta;

		if (delta<pi/4.)
		{
			delta=double(specMax)*(1.-delta/(pi/4.));
			specFlip=SLong(delta);
			if (specFlip<0)	specFlip=0;
			else if (specFlip>specMax) specFlip=specMax;
		}
		else specFlip=0;
	}
	else specFlip=0;

	spa+=pi; if (spa>pi) spa=2*pi-spa;
	lia+=pi; if (lia>pi) lia=2*pi-lia;

	if (spa<pi/2. && lia<pi/2.)
	{
		double delta=spa-lia; delta=delta<0?-delta:delta;

		if (delta<pi/4.)
		{
			delta=double(specMax)*(1.-delta/(pi/4.));
			specular=SLong(delta);
			if (specular<0)	specular=0;
			else if (specular>specMax) specular=specMax;
		}
		else specular=0;
	}
	else specular=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateGlobalFlags
//Author		Paul.   
//Date			Fri 8 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::UpdateGlobalFlags(int ft)
{
	SLong	temp;

	temp = globalanimtime.centisec + ft;//Timer_Code.frametime;		//PD 15Mar96

	if(temp<globalanimtime.centisec)	//Wrapped arround
	{
		temp = globalanimtime.centisec - 0x07FFFFFFF;
		temp = temp + ft;//Timer_Code.frametime;						//PD 15Mar96
	}

	globalanimtime.centisec = temp;
	globalanimtime.tnthssec = temp/10;
	globalanimtime.secs = temp/100;

	//PD 16Apr96 - test code

//	PolyPitAnimData* adptr = (PolyPitAnimData* )Manual_Pilot.ControlledAC2->Anim;
}

//DeadCode PD 10Jun97 Bool	bZBufferLock;
Bool	bOldZState;

Bool	bPlayerTextures;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLineAndDotShade
//Author		Paul.   
//Date			Mon 2 Nov 1998
//------------------------------------------------------------------------------
void shape::SetLineAndDotShade(itemptr ip,ViewPoint* vp)
{
#ifdef	_PROCDEBUG_
	Bollox("0");
#endif
	const SLong FADE_DIST=FT_50;
	const SLong HALF_FADE_DIST=FADE_DIST>>1;
	if (ip && vp && ((ip->shape==BULLT2) || (ip->shape==BULLET) || (IsAircraft && current_level>=2)))//RJS 15Dec99
	{
		Float fintensity=-TransLightVector.nj.f*TransViewVector.nj.f;
		fintensity*=Float(32385);
		SLong top_intens=fintensity;
		top_intens+=32385;
		top_intens/=232;
		top_intens=280-top_intens;
		if (top_intens>256)	top_intens=256;
		else if (top_intens<0) top_intens=0;
		dotNLineFadeValue=top_intens;
	}
	else dotNLineFadeValue=-1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	shape::process_shape
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
void shape::process_shape(	CLib3D			*lib3d,
							ViewPoint*		vp,					//JIM 12Dec95
							Obj3DPtr 	this_obj3d,			//RJS 07Feb00
							FPMATRIX_PTR 	this_matrix,
							Bool			subshape,			//RJS 15Jan99
							FPMATRIX_PTR 	this_objmatrix)		//RJS 15Jan99
{
	g_lpLib3d=lib3d;
	
	Smoke_Trails.SetGraphLib(lib3d);							//RJS 09Feb00
	Smoke_Trails.SetDoPoints(newco);

//DeadCode JON 2Nov00 	if (fPolyPitShade)
//DeadCode JON 2Nov00 	{
//DeadCode JON 2Nov00 		staticRGBlo=	Land_Scape.currentLighting.cockpitAmbientCollo.col();
//DeadCode JON 2Nov00 		staticRGBhi=	Land_Scape.currentLighting.cockpitAmbientColhi.col();
//DeadCode JON 2Nov00 		staticRGBamb=	Land_Scape.currentLighting.cockpitAmbientColamb.col();
//DeadCode JON 2Nov00 		shadedRGBlo=	staticRGBlo;
//DeadCode JON 2Nov00 		shadedRGBhi=	staticRGBhi;
//DeadCode JON 2Nov00 		shadedRGBamb=	staticRGBamb;
//DeadCode JON 2Nov00 	}
//DeadCode JON 2Nov00 	else
	if (fSpecialShade)
	{
		staticRGBlo=	Land_Scape.currentLighting.landAmbientCollo.col();
		staticRGBhi=	Land_Scape.currentLighting.landAmbientColhi.col();
		staticRGBamb=	Land_Scape.currentLighting.landAmbientColamb.col();
		shadedRGBlo=	staticRGBlo;
		shadedRGBhi=	staticRGBhi;
		shadedRGBamb=	staticRGBamb;
	}
	else
	{
		staticRGBlo=	Land_Scape.currentLighting.staticAmbientCollo.col();
		staticRGBhi=	Land_Scape.currentLighting.staticAmbientColhi.col();
		staticRGBamb=	Land_Scape.currentLighting.staticAmbientColamb.col();
		shadedRGBlo=	Land_Scape.currentLighting.shadedAmbientCollo.col();
		shadedRGBhi=	Land_Scape.currentLighting.shadedAmbientColhi.col();
		shadedRGBamb=	Land_Scape.currentLighting.shadedAmbientColamb.col();
	}

	LIGHTINGDESC lightDesc;
	lightDesc.lowRGB=staticRGBlo;
	lightDesc.highRGB=staticRGBhi;
	lightDesc.ambientRGB=staticRGBamb;
	lightDesc.lowDot=0.f;
	lightDesc.highDot=1.f;
//DeadCode JON 11Sep00 	lightDesc.specularPower=1.2f;
	lightDesc.specularRGB = 	Land_Scape.currentLighting.specularHighlight.col();
	g_lpLib3d->SetAmbientLighting(lightDesc);

	specularEnabled=false;
	if (!subshape) current_level=0;
	IsAircraft=(this_obj3d->ItemPtr && this_obj3d->ItemPtr->Status.size==AirStrucSize)?1:0;
	fpobject_matrix = this_matrix;
	fprealobject_matrix = this_objmatrix;						//RJS 15Jan99
	object_obj3d  = this_obj3d;
//	current_screen->DoCalcItemFog(	true,
//									this_obj3d->Body.X.f,
//									this_obj3d->Body.Y.f,
//									this_obj3d->Body.Z.f);		//PD 09Sep98

	//pre-calculate pseudo lighshading values for dots and lines
 	SetLineAndDotShade(object_obj3d->ItemPtr,vp);

//	bPlayerTextures=FALSE;										//PD 20Jun97
//	if (object_obj3d->ItemPtr==Manual_Pilot.ControlledAC2)
//	{
//		bPlayerTextures=TRUE;									//PD 20Jun97
//		current_screen->DoSetPlayerTextures(TRUE);
//	}
	VapourCyl = FALSE;											//RJS 14May97
	IsSubShape = subshape;										//RJS 03Jun97

//DeadCode JON 22Sep00 	if (Save_Data.detail_3d[DETAIL3D_ITEMSHADING])				//PD 10Dec98
//DeadCode JON 22Sep00 			View_Point->isLightShaded = TRUE;					//PD 10Dec98
//DeadCode JON 22Sep00 	else														//PD 10Dec98
//DeadCode JON 22Sep00 			View_Point->isLightShaded = FALSE;					//PD 10Dec98

	View_Point->isLightShaded = (Save_Data.itemShading!=0);

	LIGHTFLAG lf=LF_AMBIENT;
	g_lpLib3d->SetObjectLighting(lf);
	oldAlphaSwitch = -1;										//RJS 04Jun98
																//RJS 30Apr98
	GlobalAdptr = this_obj3d->AnimPtr;							//RJS 21Apr99

	oldMipMapState = true;										//RJS 24May99

	alphaRestoreCnt = 0;										//RJS 18May00

	draw_shape(this_obj3d);										//RJS 30Apr98
																//RJS 30Apr98
//DEADCODE JON 4/19/00  	View_Point->isLightShaded = TRUE;							//RJS 30Apr98
//DEADCODE JON 3/30/00 	lf=LF_AMBIENT;
	g_lpLib3d->SetObjectLighting(lf);
//DEAD	POLYGON.SetCrossProduct(TRUE);								//PD 11Dec96
//	if (doingHW3D)												//PD 19Jun98
	{
//		current_screen->DoSetPlayerTextures(FALSE);
//		current_screen->DoCalcItemFog(	false,
//										this_obj3d->Body.X.f,
//										this_obj3d->Body.Y.f,
//										this_obj3d->Body.Z.f);	//PD 09Sep98
	}															//PD 06Jun97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	shape::animate_shape
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
void shape::animate_shape(Obj3DPtr thisobj3d, Coords3D& itempos)//RJS 07Feb00
{
	if (thisobj3d->objtype <= MOBILE_OBJECT)
	{
/*#ifdef	DBGMEMTEST
	TransientItemPtr	tmpentry = TransientItem::TransientList;
	while (tmpentry)
	{
		DbgMemTest2(tmpentry);
		tmpentry->Anim.MemTest();
		tmpentry = tmpentry->nexttrans;
	}
#endif*/

		smokeFirstIsSpecial = true;
		if (/*!Three_Dee.shapecheat && */thisobj3d->ItemPtr!=Persons2::PlayerGhostAC)									//RJS 09Dec97
		{
			ShapeDescPtr	sdptr;

			animptr	adptr;											//RJS 21Apr99

 			object_obj3d  = thisobj3d;									//RJS 19Jun97

			adptr = thisobj3d->AnimPtr;								//RJS 21Apr99

			sdptr = SHAPESTUFF.GetShapePtr((ShapeNum)thisobj3d->Shape);

		// We need this for smoke launchers......				//MS 30Nov98
//DEADCODE DAW 23/04/99  		switch (SHAPESTUFF.GetShapeScale(sdptr))				//MS 30Nov98
//DEADCODE DAW 23/04/99  		{														//MS 30Nov98
//DEADCODE DAW 23/04/99  			case SHP_GRP:										//MS 30Nov98
//DEADCODE DAW 23/04/99  				_Error.EmitSysErr(__FILE__":Bad shape type field (SHAPE NUMBER %d)",thisobj3d->Shape);//MS 30Nov98
//DEADCODE DAW 23/04/99  				break;											//MS 30Nov98
//DEADCODE DAW 23/04/99  			case SHP_1CM:										//MS 30Nov98
//DEADCODE DAW 23/04/99  				shapescale = 0;									//MS 30Nov98
//DEADCODE DAW 23/04/99  				break;											//MS 30Nov98
//DEADCODE DAW 23/04/99  			case SHP_4CM:										//MS 30Nov98
//DEADCODE DAW 23/04/99  				shapescale = 2;									//MS 30Nov98
//DEADCODE DAW 23/04/99  				break;											//MS 30Nov98
//DEADCODE DAW 23/04/99  			case SHP_16CM:										//MS 30Nov98
//DEADCODE DAW 23/04/99  				shapescale = 4;									//MS 30Nov98
//DEADCODE DAW 23/04/99  				break;											//MS 30Nov98
//DEADCODE DAW 23/04/99  		}														//MS 30Nov98
		// ....We need this for smoke launchers					//MS 30Nov98

			UByte	vaptype = sdptr->Type.VapourType;				//RJS 21Jan99

			//Call the correct anim routine in this case statement

			if (sdptr->AnimDataSize > -1)
			{
				switch (sdptr->AnimDataSize)
				{
					case POLYPITANIM:										//PD 15Apr96
						vaptype = TRAIL_OFF;							//RJS 23Oct00
						PolyPitItemAnim((PolyPitAnimData *)adptr);
						break;

					case BLOKESANIM:								//RJS 01Jun99
						BlokesItemAnim((BlokesAnimData* )adptr);	//RJS 01Jun99
						break;										//RJS 01Jun99

					case AIRCRAFTANIM:
						AircraftAnim((AircraftAnimData* )adptr);			//RJS 09Jan97
						break;

					case SUNANIM:											//PD 24Jun96
						SunItemAnim((SunAnimData* )adptr);					//PD 24Jun96
						break;												//PD 24Jun96

					case WINDSOCANIM:									//RJS 05Jun97
						WindsockItemAnim((WindsocAnimData*) adptr);		//RJS 05Jun97
						break;

					case BARAGEANIM:										//RJS 24Sep96
						BarageItemAnim((BarageAnimData*) adptr);
						break;

					case MOVEGUNANIM:
						if (!sdptr->Type.VapourType)						//RJS 10Mar98
							MoveGunItemAnim((MoveGunAnimData*) adptr);	//RJS 04Jun97
						break;
					case TANKANIM:
						TankItemAnim((MoveGunAnimData*) adptr);				//RJS 17Oct96
						break;
					case TRUCKANIM:
						TruckItemAnim((MoveGunAnimData*) adptr,(UByteP)sdptr);	//RJS 18May99
						break;
 					case TRAINANIM:
 						TrainItemAnim((TrainAnimData*) adptr);				//RJS 07Feb97
 						break;
					case TROOPANIM:
						TroopItemAnim((TroopAnimData*) adptr,thisobj3d->ItemPtr);//RJS 22Dec99
						break;
					case SMOKETRAILANIM:
						vaptype = TRAIL_OFF;
						ProbeStaticTrail((UByteP)sdptr,thisobj3d->ItemPtr,adptr);
						break;
//Using MiG technique...
//DeadCode RJS 22Dec99 				case PARACHUTEANIM:
//DeadCode RJS 22Dec99 				{
//DeadCode RJS 22Dec99 					if (thisobj3d->ItemPtr->Status.size == TRANSIENTSIZE)
//DeadCode RJS 22Dec99 					{
//DeadCode RJS 22Dec99 						TransientItem*	targ = (TransientItem*) thisobj3d->ItemPtr;
//DeadCode RJS 22Dec99 						if (targ->isOwned && targ->Target)
//DeadCode RJS 22Dec99 						{
//DeadCode RJS 22Dec99 							Coords3D	oldcoords;
//DeadCode RJS 22Dec99 							TransientItem*	theChute = (TransientItem*)targ->Target; 
//DeadCode RJS 22Dec99 							oldcoords = theChute->World;
//DeadCode RJS 22Dec99 							theChute->World = thisobj3d->ItemPtr->World;
//DeadCode RJS 22Dec99 							Three_Dee.StuffInBinaryTree(theChute);//DAW 23Apr99
//DeadCode RJS 22Dec99 							theChute->World = oldcoords;
//DeadCode RJS 22Dec99 						}
//DeadCode RJS 22Dec99 					}
//DeadCode RJS 22Dec99 				}	 
//DeadCode RJS 22Dec99 				break;
					case BIRDLAUNCHERANIM:									//RJS 01Dec99
						BirdLauncherItemAnim((BirdLauncherAnimData*)adptr,itempos);//RJS 01Dec99
						break;
				}
			}

#ifndef	_NOSMOKETRAILS_														//RJS 08Apr99
			switch (vaptype)							//RJS 10Mar98
			{
				case TRAIL_NORMAL:
				case TRAIL_STATIC:
					UpdateVapourCoords(thisobj3d->ItemPtr,adptr);	//DAW 23Apr99
					break;
				case TRAIL_GROUND:
					UpdateSmokeDriftCoords(thisobj3d->ItemPtr,adptr);//DAW 23Apr99
					break;
			}
#else
		#pragma message (__HERE__ "Smoke-trails disabled!")
#endif
		}
/*#ifdef	DBGMEMTEST
	tmpentry = TransientItem::TransientList;
	while (tmpentry)
	{
		DbgMemTest2(tmpentry);
		tmpentry->Anim.MemTest();
		tmpentry = tmpentry->nexttrans;
	}
#endif*/
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		sfx_shape
//Author		Robert Slater
//Date			Mon 20 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::sfx_shape(ItemPtr	itm, D3DVECTOR&	pos, float& theRange)
{
	if (itm->Status.size == FORMATIONSIZE)						//RJS 17May99
	{															//RJS 17May99
		if (	(((FormationItemPtr)itm)->leader != NULL)		//RJS 17May99
			&&	(((FormationItemPtr)itm)->follower != NULL)	)	//RJS 17May99
			return;												//RJS 17May99
	}															//RJS 17May99

	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);	//RJS 17May99
	switch (sdptr->AnimDataSize)								//RJS 17May99
	{															//RJS 17May99
		case TANKANIM:											//RJS 17May99
		case TRUCKANIM:											//RJS 17May99
		case TRAINANIM:											//RJS 17May99
		case BIRDLAUNCHERANIM:									//RJS 09Jun00
			break;												//RJS 17May99
		default:												//RJS 17May99
			return;												//RJS 17May99
	}															//RJS 17May99

	if (theRange < 150000.)										//RJS 9Jun00
	{															//RJS 17May99
		MinAnimData		*mad = (MinAnimData*) itm->Anim;		//RJS 17May99
		if (mad->itemstate == ALIVE)							//RJS 17May99
		{
			switch (sdptr->AnimDataSize)
			{
				case TANKANIM:
					_Miles.PlayDelayed(FIL_SFX_TANK_LOOP1,itm,128,TRUE);//RJS 05Nov99
					break;
				case TRUCKANIM:
					_Miles.PlayDelayed(FIL_SFX_TRUCK_NORM_LOOP,itm,128,TRUE);//RJS 05Nov99
					break;
				case TRAINANIM:
					_Miles.PlayDelayed(FIL_SFX_TRAIN_LOOP, itm,128,TRUE);//RJS 05Nov99
					break;
				case BIRDLAUNCHERANIM:
				{
					FileNum	theSoundFile = FIL_NULL;
					BirdLauncherAnimData*	adptr = (BirdLauncherAnimData*)itm->Anim;
					Bool	looped = TRUE;

					switch (adptr->theShape)
					{
					case RAVEN:
					case PIGEON:
						theSoundFile = FIL_SFX_AMB_TOWEROFLONDON;
					break;
					case GULL:
						theSoundFile = FIL_SFX_AMB_BIRDLOOP_SEA;
					break;
					case BIRD:
					{
						SLong	time24hr = View_Point->TimeOfDay();
						SLong	theHours = time24hr / (100*60*60);
						if ((theHours < 5) || (theHours > 23))
						{
							UWord	rand = Math_Lib.rnd();
							if (rand > 60000)
							{
								rand = ((rand-60000)*2)/5535;

								theSoundFile = FileNum(FIL_SFX_AMB_BIRD_OWL1 + rand);

								looped = FALSE;
							}
						}
						else
							theSoundFile = FIL_SFX_AMB_BIRDLOOP_NICE;
					}
					break;
					}

					_Miles.PlayDelayed(theSoundFile, itm,128,looped);//RJS 05Nov99
					break;
				}
			}
		}
		else
		{
			if (sdptr->AnimDataSize == TRAINANIM)
				_Miles.PlayDelayed(FIL_SFX_SMALL_FIRE_LOOP,itm,128,TRUE);//RJS 05Nov99
		}
	}
}

//Dead static	UByteP	shphedr;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	shape::draw_shape
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
void shape::draw_shape(Obj3DPtr this_obj3d)					//RJS 07Feb00
{
#ifdef	_BIGPROCDEBUG_
	Bollox("1");
#endif
	UWord 	instruction;
	int		cnt;
	MinAnimData*	mad = (MinAnimData*) GlobalAdptr;				//RJS 22Apr99

	ShapeDescPtr	header_ptr;

	UByte 	*instr_ptr;

	object_obj3d = this_obj3d;

//DeadCode RJS	this_obj3d->realbz.f = D3Distance(SLong(this_obj3d->Body.X.f),SLong(this_obj3d->Body.Y.f),SLong(this_obj3d->Body.Z.f));

//DeadCode RJS 07Feb00	object_dist=(SLong)this_obj3d->realbz.f;
	fade_start	=200000;	//Land_Scape.GetFadeStart();		//PD 19Dec96
	fade_end  	=400000;	//Land_Scape.GetFadeEnd();			//PD 19Dec96

	theBlokeAnimPtr = NULL;										//RJS 17Nov99

	SHAPESTUFF.shape_image_mem = 0;
	SHAPESTUFF.shape_alpha_mem = 0;
	
	animlag = 0;													//RJS 30Jun99
	header_ptr = SHAPESTUFF.GetShapePtr((ShapeNum)this_obj3d->Shape);
	if (header_ptr->AnimDataSize == AIRCRAFTANIM)					//RJS 30Jun99
	{
		AircraftAnimData*	adptr = (AircraftAnimData*)GlobalAdptr;
		animlag = adptr->timenotvis;
	}

	globalSdptr = header_ptr;
//DeadCode PD 05Oct98 	switch(SHAPESTUFF.GetShapeScale(header_ptr))				//PD 23Apr96
//DeadCode PD 05Oct98 	{
//DeadCode PD 05Oct98 		case SHP_1CM:
//DeadCode PD 05Oct98 			shapescale = 0;										//PD 10Apr96
//DeadCode PD 05Oct98 			break;												//PD 10Apr96
//DeadCode PD 05Oct98 
//DeadCode PD 05Oct98 		case SHP_4CM:
//DeadCode PD 05Oct98 			shapescale = 2;										//PD 10Apr96
//DeadCode PD 05Oct98 			break;												//PD 10Apr96
//DeadCode PD 05Oct98 
//DeadCode PD 05Oct98 		case SHP_16CM:
//DeadCode PD 05Oct98 			shapescale = 4;										//PD 10Apr96
//DeadCode PD 05Oct98 			break;												//PD 10Apr96
//DeadCode PD 05Oct98 
//DeadCode PD 05Oct98 		case SHP_GRP:
//DeadCode PD 05Oct98 			_Error.EmitSysErr(__FILE__"Bad shape type field (SHAPE NUMBER %d)",this_obj3d->Shape);
//DeadCode PD 05Oct98 			break;
//DeadCode PD 05Oct98 	}

#ifndef	NDEBUG
 	DrawHitBox(object_obj3d,NULL);
#endif
#ifndef	_NOBODY_
	instr_ptr =(UByte *)header_ptr;								//RJS 23Nov99

	if (object_obj3d->objtype == SMOKE_OBJECT)							//RJS 20Oct00
		instr_ptr += header_ptr->liveshpref;							//RJS 20Oct00
	else
	{
//DeadCode RJS 19Oct100 	if (!mad->repair || !object_obj3d->ItemPtr)					//RJS 23Nov99
		if (!mad->repair)											//RJS 19Oct00
		{
			switch (mad->itemstate)									//RJS 16Nov98
			{														//RJS 16Nov98
			case ALIVE:												//RJS 16Nov98
				instr_ptr += header_ptr->liveshpref;				//RJS 16Nov98
				break;												//RJS 16Nov98
			case DAMMAGED:											//RJS 16Nov98
				instr_ptr += header_ptr->damagedshpref;				//RJS 16Nov98
				break;												//RJS 16Nov98
			case DYING:												//RJS 16Nov98
				instr_ptr += header_ptr->dyingshpref;				//RJS 16Nov98
				break;												//RJS 16Nov98
			case DEAD:												//RJS 16Nov98
				instr_ptr += header_ptr->deadshpref;				//RJS 16Nov98
				break;												//RJS 16Nov98
			}														//RJS 16Nov98
		}
		else
		{
			//Select repair image...

			switch (mad->itemstate)
			{
			case ALIVE:
			case DAMMAGED:
				instr_ptr += header_ptr->damagedshpref;				//RJS 23Nov99
				break;
			case DYING:
				instr_ptr += header_ptr->repairshpref;				//RJS 23Nov99
				break;
			case DEAD:
				// Cheat, and draw special rubble shape...
				instr_ptr += header_ptr->liveshpref;
				break;
			}
		}
	}

	if (header_ptr->AnimDataSize == AIRCRAFTANIM)			//RJS 30Jun99
	{
		AircraftAnimData*	adptr = (AircraftAnimData*)GlobalAdptr;
		adptr->timenotvis = 0;
	}

#ifdef	_IMAP_TEXTURE_MEM_
 	if (header_ptr->AnimDataSize == AIRCRAFTANIM)
	{
		if (object_obj3d->ItemPtr == Persons2::PlayerSeenAC)
	 		Image_Map.DoingPilotedAC = true;
		else
 			Image_Map.DoingAC = TRUE;
	}
 
 	if (header_ptr->AnimDataSize == POLYPITANIM)
 		Image_Map.DoingCock = TRUE;
#endif

	InterpLoop(instr_ptr);									//RJS 16Nov98

#ifdef	_IMAP_TEXTURE_MEM_
 	Image_Map.DoingPilotedAC = false;
 	Image_Map.DoingAC = FALSE;
 	Image_Map.DoingCock = FALSE;
#endif
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//					    SHAPE INSTRUCTIONS
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dopoint
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
void shape::dopoint(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("2");
#endif
	DOPOINT_PTR ptr = (DOPOINT_PTR )instr_ptr;
	DoPointStruc* dp=newco+UWord(ptr->vertex);
	
#ifndef	_NOPOINTS_
	dp->setPosition(ptr->xcoord + object_obj3d->Body.X.f,
					ptr->ycoord + object_obj3d->Body.Y.f,
					ptr->zcoord + object_obj3d->Body.Z.f	);	//RJS 19May00
#endif
	instr_ptr+=sizeof(DOPOINT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dopolygon
//LastModified:	PD 24Apr98
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
void shape::dopolygon(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("3");
#endif
	DOPOLYGON_PTR poly_data;
	ULong numVertices;
	UWord* vertices;
	Lib3DPoint *pRVerts;										//RJS 19May00

	poly_data=(DOPOLYGON_PTR)instr_ptr;
	numVertices=poly_data->edges;
	vertices=(UWord*)(instr_ptr+sizeof(DOPOLYGON));

#ifndef	_NOPOLYS_
	pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(shape::colour),numVertices);//RJS 19May00
	for (int i=0;i<numVertices;i++)
		pRVerts[i]=newco[*vertices++];
	g_lpLib3d->EndPoly();
#endif

   	instr_ptr+=sizeof(DOPOLYGON)+(UWord)poly_data->edges * sizeof(UWord);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetlc
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dosetlc(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("4");
#endif
	instr_ptr += sizeof(DOSETLC);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetcolour
//LastModified:	PD 10Jul96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dosetcolour(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("5");
#endif
	ImageMapNumber	imapno;
	SLong	flag;												//RJS 12Feb97
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;				//RJS 18Feb97

	DOSETCOLOUR_PTR	dscptr = (DOSETCOLOUR_PTR )instr_ptr;

	imapno = (ImageMapNumber )(dscptr->imageno);

	ImageMapDescPtr imptr = Image_Map.GetImageMapPtr(imapno);

	flag = GlobalAdptr[dscptr->flagname];						//RJS 16Apr99
//DeadCode RJS 12Feb97 	flag = *(animflags+flag);

	flag <<= 6;		// * 64

	flag *= imptr->w;											//RJS 06Feb98

	Colour base_colour = (Colour )(*(imptr->body)+flag);

/*	SWord intense = Three_Dee.IntensFromRange(object_dist,fade_start,fade_end);

 	intense = intense>>4;

	if (intense)												//RJS 27Jun97
	{
		SLong	temp1,temp2;

		temp1 = (SLong )base_colour;
		temp1 &= 0x0FF;

		temp2 = intense;
		temp1 = ASM_GetFadeColour(temp1,temp2);

		base_colour = (Colour )temp1;
	}
*/
	shape::colour = base_colour;

//	current_screen->SetColour(base_colour);

	instr_ptr += sizeof(DOSETCOLOUR);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doline
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::doline(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("6");
#endif
 	DOLINE_PTR ptr = (DOLINE_PTR )instr_ptr;
#ifndef	_NOLINE_

 	SWord start_vertex,end_vertex;

	SetLineAndDotShade(object_obj3d->ItemPtr,View_Point);
	
 	start_vertex=(SWord )ptr->start_vertex;
 	end_vertex=(SWord )ptr->end_vertex;

	g_lpLib3d->DrawLine(HMATERIAL(shape::colour),newco[start_vertex],newco[end_vertex]);
//DeadCode JON 8Aug00 	g_lpLib3d->DrawPoint(HMATERIAL(shape::colour),newco[start_vertex]);
#endif
	instr_ptr += sizeof(DOLINE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doret
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::doret(UByte *& )									//PD 04Jan96
{
#ifdef	_PROCDEBUG_
	Bollox("7");
#endif
	//Empty
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doifcross
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::doifcross(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("8");
#endif
	SWord	v1, v2, v3;											//PD 04Jan96

	DOIFCROSS_PTR ptr = (DOIFCROSS_PTR)instr_ptr;

	v1 = (SWord )ptr->vertex1;									//RJS 10Mar97
	v2 = (SWord )ptr->vertex2;									//RJS 10Mar97
	v3 = (SWord )ptr->vertex3;									//RJS 10Mar97

	if(!_matrix.crossproduct(newco[v1],newco[v2],newco[v3]))
//Old_Code PD 06Dec96 	if(!_matrix.accuratecrossproduct(newco[v1],newco[v2],newco[v3]))
	{
		instr_ptr += ptr->offset;
	}
	else
	{
		instr_ptr += sizeof(DOIFCROSS);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dogosub
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dogosub(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("9");
#endif
	UByte 	*old_ptr;

	old_ptr = instr_ptr;

	instr_ptr += *(SWord *)instr_ptr;	//Signed word offset from the
										//current position.

	InterpLoop(instr_ptr);

	instr_ptr = old_ptr + sizeof(SWord);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doifeq
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::doifeq(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("10");
#endif
	instr_ptr += sizeof(DOIFEQ);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doifne
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::doifne(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("11");
#endif
	instr_ptr += sizeof(DOIFNE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donop
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::donop(UByte *& )									//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("12");
#endif
	_Error.EmitSysErr(__FILE__":Not a real instruction (DONOP)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dogroup
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dogroup(UByte *& )									//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("13");
#endif
	_Error.EmitSysErr(__FILE__":Not a real instruction (DOGROUP)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dogoto
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dogoto(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("14");
#endif
	instr_ptr += *(SWord *)instr_ptr;//RJS 17Jun98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doend
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::doend(UByte *& )
{
#ifdef	_PROCDEBUG_
	Bollox("15");
#endif
	_Error.EmitSysErr(__FILE__":Not a real instruction (DOEND), shape %d\n",object_obj3d->Shape);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dowindowdial
//Author		Robert Slater
//Date			Tue 6 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dowindowdial(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("16");
#endif
	DOWINDOWDIAL_PTR ptr = (DOWINDOWDIAL_PTR )instr_ptr;
	SWord			minx, miny, maxx, maxy;
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;
	SLong			val=0;
	SWord			rwidth, rheight;
	SLong			maxshift=0;

	switch (ptr->nobytes)
	{
	case 1:
		val = GlobalAdptr[ptr->animoffset];						//RJS 16Apr99
		maxshift = 8;
		break;
	case 2:
		val = *((UWordP)&GlobalAdptr[ptr->animoffset]);			//RJS 16Apr99
		maxshift = 16;
		break;
	case 4:
		val = *((ULongP)&GlobalAdptr[ptr->animoffset]);			//RJS 16Apr99
		maxshift = 32;
		break;
	}
	rwidth = ptr->winwidth;
	rheight = ptr->winheight;

	minx = ptr->minx;
	miny = ptr->miny;

	if (ptr->issigned)
	{
		if (ptr->shiftx)
			minx += (val * ptr->width)/510;

		if (ptr->shifty)
			miny += (val * ptr->height)/510;
	}
	else
	{
		if (ptr->shiftx)
		{
			minx += (val * ptr->width)>>maxshift;
			minx-=(rwidth/2);
		}

		if (ptr->shifty)
		{
			miny += (val * ptr->height)>>maxshift;
			miny-=(rheight/2);
		}
	}

	maxx = minx + rwidth;
	maxy = miny + rheight;

#ifndef	_NOPOINTS_
	newco[0].setIMapCoords(minx,miny);							//RJS 19May00
	newco[1].setIMapCoords(maxx,miny);							//RJS 19May00
	newco[2].setIMapCoords(maxx,maxy);							//RJS 19May00
	newco[3].setIMapCoords(minx,maxy);							//RJS 19May00
#endif
	Lib3DPoint *pRVert;										//RJS 19May00
	ImageMapDesc *pmap=Image_Map.GetImageMapPtr((ImageMapNumber)ptr->imagemap);

#ifndef	_NOPOLYS_

	pRVert = g_lpLib3d->BeginPoly(HMATERIAL(pmap),4);
	pRVert[0]=newco[0];
	pRVert[1]=newco[1];
	pRVert[2]=newco[2];
	pRVert[3]=newco[3];
	g_lpLib3d->EndPoly();
#endif
	instr_ptr += sizeof(DOWINDOWDIAL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doattitude
//Author		Robert Slater
//Date			Wed 1 Apr 1998
//
//Description	Imagemapped cockpit attitude dial thing
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doattitude(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("17");
#endif
	DOATTITUDE_PTR	ptr = (DOATTITUDE_PTR) instr_ptr;
	ImageMapDescPtr imptr;
	SLong			cx,cy,cz;
	SWord			ystep;
	SWord			pitch = object_obj3d->AngC;
	SWord			windy, windy2;
	SWord			minx,miny, maxx,maxy;
	SWord			sin_ang, cos_ang;
	FPMATRIX		tmat;
	FPMATRIX_PTR	tmatp = &tmat;
	IFShare			wx,wy,wz;
	SWord			radius = ptr->radius;
	DoPointStruc	dp0, dp1, dp2, dp3;

	imptr = Image_Map.GetImageMapPtr((ImageMapNumber )ptr->imagemap);

 	windy = ptr->height / 4;
 	windy2 = ptr->height>>1;

	ystep = (-pitch * windy) / ANGLES_20Deg;								//RJS 21Apr98
	ystep += windy;

	if (ystep < 0)
		ystep = 0;

	if (ystep > windy2)
		ystep = windy2;

	miny = ptr->miny + ystep;
	minx = ptr->minx;
	maxx = minx + ptr->width;
	maxy = miny + windy2;

	cx = ptr->xpos;
	cy = -ptr->ypos;
	cz = ptr->zpos;

	//radius <<= shapescale;
	_matrix.Generate2(ANGLES_0Deg,ANGLES_0Deg,(ANGLES)-object_obj3d->AngR,1,tmatp);//RJS 19Jun98

	wx.i = -radius;
	wy.i = radius;
	wz.i = 0;
	_matrix.transformNC(tmatp,wx,wy,wz);
#ifndef	_NOPOINTS_

	dp0.setPosition(cx + wx.f,cy + wy.f,cz);
	dp0.setIMapCoords(minx,miny);

	wx.i = radius;
	wy.i = radius;
	wz.i = 0;
	_matrix.transformNC(tmatp,wx,wy,wz);

	dp1.setPosition(cx + wx.f,cy + wy.f,cz);
	dp1.setIMapCoords(maxx,miny);

	wx.i = radius;
	wy.i = -radius;
	wz.i = 0;
	_matrix.transformNC(tmatp,wx,wy,wz);

	dp2.setPosition(cx + wx.f,cy + wy.f,cz);
	dp2.setIMapCoords(maxx,maxy);

	wx.i = -radius;
	wy.i = -radius;
	wz.i = 0;
	_matrix.transformNC(tmatp,wx,wy,wz);

	dp3.setPosition(cx + wx.f,cy + wy.f,cz);
	dp3.setIMapCoords(minx,maxy);
#endif
	ImageMapDesc *pmap=Image_Map.GetImageMapPtr((ImageMapNumber )ptr->imagemap);
#ifndef	_NOPOLYS_

	Lib3DPoint *pRVert = g_lpLib3d->BeginPoly(HMATERIAL(pmap),4);
	pRVert[0]=dp0;
	pRVert[1]=dp1;
	pRVert[2]=dp2;
	pRVert[3]=dp3;
	g_lpLib3d->EndPoly();
#endif
	instr_ptr += sizeof(DOATTITUDE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodot
//LastModified:	PD 07May96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dodot(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("18");
#endif
	DODOT_PTR	ddptr = (DODOT_PTR )instr_ptr;
#ifndef	_NODOT_
//DeadCode RJS 23Oct00 	SLong	glintrange = (SLong)object_obj3d->realbz.f;			//RJS 07Feb00
	SetLineAndDotShade(object_obj3d->ItemPtr,View_Point);
//	if (glintrange < RANGE_AIRCRAFT)							//DAW 01Sep98
	{
 		UWord	vertex;
 
 		vertex = (UWord )ddptr->vertex;								//RJS 10Mar97
 
 		Colour	clr = (Colour )(ddptr->colour);
 
 		if (object_obj3d->Shape==BULLET)							//PD 26Jul96
 			clr = YELLOW;											//PD 26Jul96

		g_lpLib3d->DrawPoint(HMATERIAL(clr),newco[vertex]);
 	}

	// Do glint....
//DeadCode RJS 19May00 	if (	(Three_Dee.lightson == FALSE)						//RJS 10May99
//DeadCode RJS 19May00 		&& 	ddptr->imagemap										//RJS 10May99
//DeadCode RJS 19May00 		&&	!Land_Scape.blackingout						)		//RJS 10May99
//DeadCode RJS 19May00 	{
//DeadCode RJS 19May00 		MinAnimData*	mad = (MinAnimData*) GlobalAdptr;
//DeadCode RJS 19May00 		if (mad->itemstate != DEAD)							//RJS 10May99
//DeadCode RJS 19May00 		{
//DeadCode RJS 19May00 //			SLong		roll = object_obj3d->AngR;
//DeadCode RJS 19May00 			SLong		randno = 0;										//RJS 16Jun99
//DeadCode RJS 19May00 			SLong		specular;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 			if (View_Point->isLightShaded)								//RJS 06May98
//DeadCode RJS 19May00 			{
//DeadCode RJS 19May00 				SLong	specflip;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 				// Vector pointing up
//DeadCode RJS 19May00 				Float fintensity=TransLightVector.nj.f;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 				double fspecular=TransViewVector.nj.f;
//DeadCode RJS 19May00 				calcSpecular(fspecular,fintensity,specular,specflip);
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 				specular *= 4;			// 3 frames						//RJS 16Jun99
//DeadCode RJS 19May00 				specular /= specMax;									//RJS 16Jun99
//DeadCode RJS 19May00 																		//RJS 16Jun99
//DeadCode RJS 19May00 				specflip *= 4;			// 3 frames						//RJS 16Jun99
//DeadCode RJS 19May00 				specflip /= specMax;									//RJS 16Jun99
//DeadCode RJS 19May00 																		//RJS 16Jun99
//DeadCode RJS 19May00 				if (specular > specflip)								//RJS 16Jun99
//DeadCode RJS 19May00 					randno = specular;									//RJS 16Jun99
//DeadCode RJS 19May00 				else													//RJS 16Jun99
//DeadCode RJS 19May00 					randno = specflip;									//RJS 16Jun99
//DeadCode RJS 19May00 			}
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 			if (randno)				//RJS 22Mar99
//DeadCode RJS 19May00 			{
//DeadCode RJS 19May00 				randno--;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 				DoPointStruc	dp1,dp2,dp3,dp4;
//DeadCode RJS 19May00 				SWord			width = ddptr->ix;
//DeadCode RJS 19May00 				SWord			height = ddptr->iy;
//DeadCode RJS 19May00 				SWord			nofx,stepx,stepy,minx,miny,maxx,maxy;
//DeadCode RJS 19May00 				ImageMapDescPtr	imptr = Image_Map.GetImageMapPtr((ImageMapNumber )ddptr->imagemap);
//DeadCode RJS 19May00 				Float			gscale;
//DeadCode RJS 19May00 				COORDS3D	*wptr = &object_obj3d->ItemPtr->World;
//DeadCode RJS 19May00 				SLong			fno = SHAPE.Noise(wptr->X,wptr->Y,wptr->Z)/128;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 				randno -= fno;
//DeadCode RJS 19May00 				if (randno > -1)
//DeadCode RJS 19May00 				{
//DeadCode RJS 19May00 					SLong	range = RANGE_AIRCRAFT_FLASH - 100000;
//DeadCode RJS 19May00 					gscale = 100000 / object_obj3d->realbz.f;			//RJS 07Feb00
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 					dp1.bodyx.f = object_obj3d->Body.X.f * gscale;
//DeadCode RJS 19May00 					dp1.bodyy.f = object_obj3d->Body.Y.f * gscale;
//DeadCode RJS 19May00 					dp1.bodyz.f = 100000.0;		//5000.0;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 					dp4 = dp3 = dp2 = dp1;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //					if (SHAPE.ClipSphere(dp1,dp2,dp3,dp4,120)==FALSE)//DAW 01Sep98
//DeadCode RJS 19May00 //					if (SHAPE.ClipSphere(dp1,dp2,dp3,dp4,750)==FALSE)//rjs 16Jun99
//DeadCode RJS 19May00 					{
//DeadCode RJS 19May00 						minx = miny = 0;
//DeadCode RJS 19May00 						nofx = imptr->w / width;						
//DeadCode RJS 19May00 						if (nofx)
//DeadCode RJS 19May00 						{
//DeadCode RJS 19May00 	 						stepy = randno / nofx;			
//DeadCode RJS 19May00 							stepx = randno - (stepy*nofx);	
//DeadCode RJS 19May00 												
//DeadCode RJS 19May00 							minx += stepx * width;	
//DeadCode RJS 19May00 							miny += stepy * height;	
//DeadCode RJS 19May00 							if (miny >= imptr->h)
//DeadCode RJS 19May00 								minx = miny = 0;
//DeadCode RJS 19May00 						}
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 						maxx = minx + width;
//DeadCode RJS 19May00 						maxy = miny + height;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //DeadCode RJS 19May00 						R3DVERTEX *pRVert;
//DeadCode RJS 19May00 						ImageMapDesc *pmap=Image_Map.GetImageMapPtr((ImageMapNumber )ddptr->imagemap);
//DeadCode RJS 19May00 						Lib3DPoint *pRVert = g_lpLib3d->BeginPoly(HMATERIAL(pmap),4);
//DeadCode RJS 19May00 						pRVert[0]=dp1;	pRVert[0].ix=minx;	pRVert[0].iy=miny;
//DeadCode RJS 19May00 						pRVert[1]=dp2;	pRVert[1].ix=maxx;	pRVert[1].iy=miny;
//DeadCode RJS 19May00 						pRVert[2]=dp3;	pRVert[2].ix=maxx;	pRVert[2].iy=maxy;
//DeadCode RJS 19May00 						pRVert[3]=dp4;	pRVert[3].ix=minx;	pRVert[3].iy=maxy;
//DeadCode RJS 19May00 						g_lpLib3d->EndPoly();
//DeadCode RJS 19May00 					}
//DeadCode RJS 19May00 				}
//DeadCode RJS 19May00 			}
//DeadCode RJS 19May00 		}
//DeadCode RJS 19May00 	}
#endif

	instr_ptr += sizeof(DODOT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doscalesize
//Author		Robert Slater
//Date			Tue 3 Mar 1998
//
//Description	Scales the shape size by the anim counter
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doscalesize(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("19");
#endif
	DOSCALESIZE_PTR	ptr = (DOSCALESIZE_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;
	SLong	frameno = GlobalAdptr[ptr->animoffsrc];				//RJS 16Apr99
	UByte	animscale = ptr->animscale;

	frameno *= 255;
	if (animscale)
		frameno /= animscale;

	GlobalAdptr[ptr->animoffdest] = frameno;

	instr_ptr += sizeof(DOSCALESIZE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dogunsight
//Author		Robert Slater
//Date			Wed 4 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dogunsight(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("20");
#endif
#ifndef	_ACTIVEGUNSIGHT_
#pragma warnmsg("**** MiG Alley GUN-SIGHT code removed //CSB ****")
#else
	DOGUNSIGHT_PTR	ptr = (DOGUNSIGHT_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;
	int		count;
	int		vertno;
	int		count2;
	DoPointStruc	dp1,dp2,dp3,dp4,dpc;
	int		angstep = 65536 / 6;
	int		radius = 20;
	int		radius2 = 30;
	int		radius3 = 25;
	UWord	theangle = angstep;
	SWord	sin_ang, cos_ang;
	SLong	px, py, pz;
	DoPointStruc *dpptr;
	DoPointStruc *dpptr2;
	Float	minx, maxx;
	Float	miny, maxy;
	Float	gapx, gapy;
	int		left, right, up, down;
	UByteP	plist_ptr;
	SWord	angle1, angle2;
	SWord	adj, opp;
	Bool	doclip;
	UByteP	psave_ptr;
	UWord	realhdg, realpitch;
	SLong	px2,py2,pz2,pzclip;
//	FPMATRIX	omat,vomat;
	FPMATRIX_PTR	viewptr = Three_Dee.fpviewer_matrix;
//	FPMATRIX_PTR	matptr = &omat;
//	FPMATRIX_PTR	vmatptr = &vomat;

	R3DVALUE		screenx,screeny,screenz;					//RJS 07Feb00
	R3DMATRIX		omat,vomat;
	HMATRIX			matptr=HMATRIX(SLong(&omat));
	HMATRIX			vmatptr=HMATRIX(SLong(&vomat));

	Float			zscale, testPointX,testPointY;
	Float			ddx, ddy, ddxscaled, ddfrac;
	Float			TopX,TopY,BotX,BotY;
	Float			CentreX,CentreY;
	SLong			bpx,bpy;
	SLong			gs_x,gs_y,gs_z;
	SWord			minix,miniy,maxix,maxiy;

	g_lpLib3d->LoadIdentity(matptr);
	g_lpLib3d->LoadIdentity(vmatptr);

	minix = miniy = 1;
	maxix = maxiy = 2;
	
//Calc gunsight pos.....
// default range = 500m

	SLong	time;		//time in csecs
	SWord	vx,vy,vz,vhori;
	SLong	sx,sy,sz;
	SLong	usexpos, useypos, usezpos;
	SLong	xpos, ypos, zpos;
	SLong	index, wpcnt;

	gs_x = gunsightX;									//AMM 25Jun99
	gs_y = gunsightY;									//AMM 25Jun99
	gs_z = gunsightZ;									//AMM 25Jun99

	Manual_Pilot.ControlledAC2->fly.pModel->CalcGunsightPos(SHAPE.RequiredRange, gunsightmvel, sx, sy, sz);

	gs_x += sx;
	gs_y += sy;
	gs_z += sz;

	//....Calced gunsight pos

	instr_ptr += sizeof(DOGUNSIGHT);

	g_lpLib3d->Rotate(matptr,AXIS_ROLL,(Angles)-SHAPE.GunSightRoll);
	g_lpLib3d->Rotate(matptr,AXIS_PITCH,(Angles)-SHAPE.GunSightPitch);
	g_lpLib3d->Rotate(matptr,AXIS_HEADING,(Angles)-SHAPE.GunSightHdg);

	px = gs_x - SHAPE.GunSightPos.X;							//RDH 29Nov98
	py = gs_y - SHAPE.GunSightPos.Y;							//RDH 29Nov98
	pz = gs_z - SHAPE.GunSightPos.Z;							//RDH 29Nov98

	px2 = ptr->posx;
	py2 = ptr->posy;
	pz2 = ptr->posz;									//RJS 08May98
	pzclip = (ptr->posz-60);								//RJS 08May98

	dp1.bodyx.f = px;
	dp1.bodyy.f = py;
	dp1.bodyz.f = pz;

	g_lpLib3d->Transform(matptr,dp1);

	px = (SLong) dp1.bodyx.f;
	py = (SLong) dp1.bodyy.f;
	pz = (SLong) dp1.bodyz.f;

	px = (px*pz2)/pz;
	py = (py*pz2)/pz;
	pz = pz2;

	radius = (SHAPE.WingSpan*pz2*256)/SHAPE.RequiredRange;		//RJS 10May99
	radius >>= 1;

	//Scale to f86 distance from eye to get small diamonds...
	radius2 = radius + ((2560*ptr->posz)/930);		//10 * 256
	radius3 = ((1280*ptr->posz)/930);					//5 * 256

	dpc.bodyx.f = px2;
	dpc.bodyy.f = py2;
	dpc.bodyz.f = pz2;

	g_lpLib3d->BodyToScreen(dpc,screenx,screeny,screenz);		//RJS 07Feb00

	plist_ptr = psave_ptr = instr_ptr;
	instr_ptr+= ptr->nopoints*sizeof(UByte);

	if (pz > pzclip)
	{
		SLong	xoff, yoff;

		SLong	donecnt = 0;							//RJS 11Jun99

		CentreX = (Float)screenx;
		CentreY = (Float)-screeny;

		// Clip and draw diamonds...
		for (count2 = 0; count2 < 6; count2++)
		{
			Math_Lib.high_sin_cos((Angles) theangle,sin_ang,cos_ang);
			xoff = (radius * sin_ang) >> 15;
			yoff = (radius * cos_ang) >> 15;
			bpx = (px<<8) + xoff;
			bpy = (py<<8) + yoff;

			dp1.bodyx.f = bpx;
			dp1.bodyy.f = bpy;
			dp1.bodyz.f = (pz<<8);
			g_lpLib3d->Transform(MATRIX_OBJECT,dp1);
			dp1.bodyx.f *=0.00390625;
			dp1.bodyy.f *=0.00390625;
			dp1.bodyz.f *=0.00390625;
			g_lpLib3d->Transform(MATRIX_VIEWER,dp1);
			R3DVALUE screenx1,screeny1;
			g_lpLib3d->BodyToScreen(dp1,screenx1,screeny1,screenz);//RJS 07Feb00
			xoff = (radius2 * sin_ang) >> 15;
			yoff = (radius2 * cos_ang) >> 15;

			dp3.bodyx.f = (px<<8) + xoff;
			dp3.bodyy.f = (py<<8) + yoff;
			dp3.bodyz.f = (pz<<8);
			g_lpLib3d->Transform(MATRIX_OBJECT,dp3);
			dp3.bodyx.f *=0.00390625;
			dp3.bodyy.f *=0.00390625;
			dp3.bodyz.f *=0.00390625;
			g_lpLib3d->Transform(MATRIX_VIEWER,dp3);
			R3DVALUE screenx3,screeny3;
			g_lpLib3d->BodyToScreen(dp3,screenx3,screeny3,screenz);//RJS 07Feb00

			testPointX = screenx3;
			testPointY = screeny3;

			// is it within box.....

			doclip = TRUE;
			if (testPointX > CentreX)
			{
				// Test for right hand side clip...
				plist_ptr = psave_ptr;
				R3DVALUE screenxx,screenyy;
				g_lpLib3d->BodyToScreen(newco[*plist_ptr],screenxx,screenyy,screenz);//RJS 07Feb00
				for (count=0; count < (ptr->nopoints-1); count++)
				{
					dpptr = &newco[*plist_ptr];
					plist_ptr++;
					dpptr2 = &newco[*plist_ptr];
					R3DVALUE screenxx2,screenyy2;
					g_lpLib3d->BodyToScreen(*dpptr2,screenxx2,screenyy2,screenz);//RJS 07Feb00

					TopX = (Float)screenxx;
					BotX = (Float)screenxx2;
					TopY = (Float)-screenyy;
					BotY = (Float)-screenyy2;

					if (	(TopX > CentreX)
						||	(BotX > CentreX)	)
					{
						if (	(testPointY < TopY)
							&&	(testPointY > BotY)	)
						{
							ddy = TopY - BotY;
							ddxscaled = BotX;
							if (ddy != 0)
							{
								ddx = TopX - BotX;
								ddxscaled = (testPointY - BotY)*ddx;
								ddxscaled /= ddy;
								ddxscaled += BotX;
							}

							if (testPointX < ddxscaled)
								doclip = FALSE;
						}
					}
				}
			}
			else
			{
				// Test for left hand clip...
				plist_ptr = psave_ptr;
				R3DVALUE screenxx,screenyy;
				g_lpLib3d->BodyToScreen(newco[*plist_ptr],screenxx,screenyy,screenz);//RJS 07Feb00
				for (count=0; count < (ptr->nopoints-1); count++)
				{
					dpptr = &newco[*plist_ptr];
					plist_ptr++;
					dpptr2 = &newco[*plist_ptr];
					R3DVALUE screenxx2,screenyy2;
					g_lpLib3d->BodyToScreen(*dpptr2,screenxx2,screenyy2,screenz);//RJS 07Feb00

					TopX = (Float)screenxx;
					BotX = (Float)screenxx2;
					TopY = (Float)-screenyy;
					BotY = (Float)-screenyy2;

					if (	(TopX < CentreX)
						||	(BotX < CentreX)	)
					{
						if (	(testPointY < BotY)
							&&	(testPointY > TopY)	)
						{
							ddy = BotY - TopY;
							ddxscaled = TopX;
							if (ddy != 0)
							{
								ddx = BotX - TopX;
								ddxscaled = (testPointY - TopY)*ddx;
								ddxscaled /= ddy;
								ddxscaled = TopX - ddxscaled;
							}

							if (testPointX > ddxscaled)
								doclip = FALSE;
						}
					}
				}
			}

			if (!doclip)
			{
				Math_Lib.high_sin_cos((Angles) (theangle-ANGLES_45Deg),sin_ang,cos_ang);
				xoff = (radius3 * sin_ang) >> 15;
				yoff = (radius3 * cos_ang) >> 15;
				dp2.bodyx.f = bpx + xoff;
				dp2.bodyy.f = bpy + yoff;
				dp2.bodyz.f = (pz<<8);
				g_lpLib3d->Transform(MATRIX_OBJECT,dp2);
				dp2.bodyx.f *=0.00390625;
				dp2.bodyy.f *=0.00390625;
				dp2.bodyz.f *=0.00390625;
				g_lpLib3d->Transform(MATRIX_VIEWER,dp2);
				R3DVALUE screenx2,screeny2;
				g_lpLib3d->BodyToScreen(dp2,screenx2,screeny2,screenz);//RJS 07Feb00

				Math_Lib.high_sin_cos((Angles) (theangle+ANGLES_45Deg),sin_ang,cos_ang);
				xoff = (radius3 * sin_ang) >> 15;
				yoff = (radius3 * cos_ang) >> 15;

				dp4.bodyx.f = bpx + xoff;
				dp4.bodyy.f = bpy + yoff;
				dp4.bodyz.f = (pz<<8);
				g_lpLib3d->Transform(MATRIX_OBJECT,dp4);
				dp4.bodyx.f *=0.00390625;
				dp4.bodyy.f *=0.00390625;
				dp4.bodyz.f *=0.00390625;
				g_lpLib3d->Transform(MATRIX_VIEWER,dp4);
				R3DVALUE screenx4,screeny4;
				g_lpLib3d->BodyToScreen(dp4,screenx4,screeny4,screenz);//RJS 07Feb00

				R3DVERTEX *pRVert;
				ImageMapDesc *pmap;
				pmap=(ptr->imap)?Image_Map.GetImageMapPtr((ImageMapNumber)ptr->imap):NULL;
#ifndef	_NOPOLYS_

				if (pmap)
				{
					g_lpLib3d->BeginPoly(HMATERIAL(pmap),4,pRVert);
					pRVert[0]=dp1; pRVert[0].ix=minix;	pRVert[0].iy=miniy;
					pRVert[1]=dp2; pRVert[1].ix=maxix;	pRVert[1].iy=miniy;
					pRVert[2]=dp3; pRVert[2].ix=maxix;	pRVert[2].iy=maxiy;
					pRVert[3]=dp4; pRVert[3].ix=minix;	pRVert[3].iy=maxiy;
				}
				else
				{
					g_lpLib3d->BeginPoly(HMATERIAL(shape::colour),4,pRVert);
					pRVert[0]=dp1;
					pRVert[1]=dp2;
					pRVert[2]=dp3;
					pRVert[3]=dp4;
				}
				g_lpLib3d->EndPoly();
#endif
				donecnt++;
			}

			theangle += angstep;
		}

		//Centre dot...
		if (donecnt)
		{
			if (donecnt > 4)	//most likely we'll not need to clip!
			{
				xoff = (ptr->posz<<8)/930;
				dp1.bodyx.f = (px<<8)-xoff;
				dp1.bodyy.f = (py<<8);
				dp1.bodyz.f = (pz<<8);
				g_lpLib3d->Transform(MATRIX_OBJECT,dp1);
				dp1.bodyx.f *=0.00390625;
				dp1.bodyy.f *=0.00390625;
				dp1.bodyz.f *=0.00390625;
				g_lpLib3d->Transform(MATRIX_VIEWER,dp1);
				R3DVALUE screenx1,screeny1;
				g_lpLib3d->BodyToScreen(dp1,screenx1,screeny1,screenz);//RJS 07Feb00

				dp2.bodyx.f = (px<<8);
				dp2.bodyy.f = (py<<8)-xoff;
				dp2.bodyz.f = (pz<<8);
				g_lpLib3d->Transform(MATRIX_OBJECT,dp2);
				dp2.bodyx.f *=0.00390625;
				dp2.bodyy.f *=0.00390625;
				dp2.bodyz.f *=0.00390625;
				g_lpLib3d->Transform(MATRIX_VIEWER,dp2);
				R3DVALUE screenx2,screeny2;
				g_lpLib3d->BodyToScreen(dp2,screenx2,screeny2,screenz);//RJS 07Feb00

				dp3.bodyx.f = (px<<8)+xoff;
				dp3.bodyy.f = (py<<8);
				dp3.bodyz.f = (pz<<8);
				g_lpLib3d->Transform(MATRIX_OBJECT,dp3);
				dp3.bodyx.f *=0.00390625;
				dp3.bodyy.f *=0.00390625;
				dp3.bodyz.f *=0.00390625;
				g_lpLib3d->Transform(MATRIX_VIEWER,dp3);
				R3DVALUE screenx3,screeny3;
				g_lpLib3d->BodyToScreen(dp3,screenx3,screeny3,screenz);//RJS 07Feb00

				dp4.bodyx.f = (px<<8);
				dp4.bodyy.f = (py<<8)+xoff;
				dp4.bodyz.f = (pz<<8);
				g_lpLib3d->Transform(MATRIX_OBJECT,dp4);
				dp4.bodyx.f *=0.00390625;
				dp4.bodyy.f *=0.00390625;
				dp4.bodyz.f *=0.00390625;
				g_lpLib3d->Transform(MATRIX_VIEWER,dp4);
				R3DVALUE screenx4,screeny4;
				g_lpLib3d->BodyToScreen(dp4,screenx4,screeny4,screenz);//RJS 07Feb00

				R3DVERTEX *pRVert;
				ImageMapDesc *pmap;
				pmap=(ptr->imap)?Image_Map.GetImageMapPtr((ImageMapNumber)ptr->imap):NULL;
#ifndef	_NOPOLYS_

				if (pmap)
				{
					g_lpLib3d->BeginPoly(HMATERIAL(pmap),4,pRVert);
					pRVert[0]=dp4;	pRVert[0].ix=minix;	pRVert[0].iy=miniy;
					pRVert[1]=dp3;	pRVert[1].ix=minix;	pRVert[1].iy=maxiy;
					pRVert[2]=dp2;	pRVert[2].ix=maxix;	pRVert[2].iy=maxiy;
					pRVert[3]=dp1;	pRVert[3].ix=maxix;	pRVert[3].iy=miniy;
				}
				else
				{
					g_lpLib3d->BeginPoly(HMATERIAL(shape::colour),4,pRVert);
					pRVert[0]=dp4;
					pRVert[1]=dp3;
					pRVert[2]=dp2;
					pRVert[3]=dp1;
				}
				g_lpLib3d->EndPoly();
#endif
			}
		}
	}
#endif
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dowheelspray
//Author		Robert Slater
//Date			Mon 16 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dowheelspray(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("21");
#endif
//DeadCode RJS 19May00 	DOWHEELSPRAY_PTR ptr = (DOWHEELSPRAY_PTR) instr_ptr;
//DeadCode RJS 19May00 	UByte		suspension = GlobalAdptr[ptr->animflag];
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	if (suspension)
//DeadCode RJS 19May00 	{
//DeadCode RJS 19May00 		mobileitem*	mobptr = (mobileitem*)object_obj3d->ItemPtr;
//DeadCode RJS 19May00 //DEADCODE CSB 08/11/99 		SLong		vel = mobptr->velhori;
//DeadCode RJS 19May00 		SLong		vel = mobptr->vel_; //CSB 08/11/99
//DeadCode RJS 19May00 		SLong		totdist;
//DeadCode RJS 19May00 		SLong		diststep ;
//DeadCode RJS 19May00 		SLong		angfrac;
//DeadCode RJS 19May00 		SLong		thedist = 0;
//DeadCode RJS 19May00 		SLong		index;
//DeadCode RJS 19May00 		SWord		theangle;
//DeadCode RJS 19May00 		SWord		sin_ang, cos_ang;
//DeadCode RJS 19May00 		SLong		ystep;
//DeadCode RJS 19May00 		IFShare		wx,wy,wz;
//DeadCode RJS 19May00 		SLong		wxx,wyy,wzz, wystep;
//DeadCode RJS 19May00 		DODOT		dotinst;
//DeadCode RJS 19May00 		UByteP		dinstptr;
//DeadCode RJS 19May00 		SLong		outback;
//DeadCode RJS 19May00 		DoPointStruc	dp1,dp2,dp3,dp4;
//DeadCode RJS 19May00 		totdist = vel >> 3;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		wxx = ptr->xcoord;
//DeadCode RJS 19May00 		wyy = ptr->ycoord;
//DeadCode RJS 19May00 		wzz = ptr->zcoord;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		dotinst.vertex = 0;
//DeadCode RJS 19May00 		dotinst.colour = 31;
//DeadCode RJS 19May00 		dotinst.imagemap = 0;									//RJS 04Jun98
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		outback = wzz<<12;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		if (totdist)
//DeadCode RJS 19May00 		{
//DeadCode RJS 19May00 			diststep = totdist<<7;		// <<12 / 32
//DeadCode RJS 19May00 			angfrac = ANGLES_180Deg >> 5;
//DeadCode RJS 19May00 			theangle = 0;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 			for (index = 0; index < 32; index++)
//DeadCode RJS 19May00 			{
//DeadCode RJS 19May00 				Math_Lib.high_sin_cos((Angles) theangle,sin_ang,cos_ang);
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 				wystep = (totdist * sin_ang)>>16;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 				wzz = outback>>12;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 				for (ystep = 0; ystep < wystep; ystep++)
//DeadCode RJS 19May00 				{
//DeadCode RJS 19May00 					wy.f = wyy + ystep;
//DeadCode RJS 19May00 					wz.f = wzz;
//DeadCode RJS 19May00 					wx.f = wxx;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 					if (SHAPE.Noise(wx.i,wy.i,wz.i) > 180)
//DeadCode RJS 19May00 					{
//DeadCode RJS 19May00 						dinstptr = (UByteP) &dotinst;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 						newco[0].bodyx.f = wx.f;
//DeadCode RJS 19May00 						newco[0].bodyx.f = wy.f;
//DeadCode RJS 19May00 						newco[0].bodyx.f = wz.f;
//DeadCode RJS 19May00 						dodot(dinstptr);
//DeadCode RJS 19May00 					}
//DeadCode RJS 19May00 				}
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 				outback -= diststep;
//DeadCode RJS 19May00 				theangle += angfrac;
//DeadCode RJS 19May00 			}
//DeadCode RJS 19May00 		}
//DeadCode RJS 19May00 	}

	instr_ptr += sizeof(DOWHEELSPRAY);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doifbright
//Author		Robert Slater
//Date			Mon 23 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doifbright(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("22");
#endif

#pragma message(__HERE__" No IF BRIGHT!!")

	DOIFBRIGHT_PTR	ptr = (DOIFBRIGHT_PTR) instr_ptr;
//DeadCode RJS 20Oct00 	int		count = ptr->nopoints;
//DeadCode RJS 20Oct00 	int		i;
//DeadCode RJS 20Oct00 	UWord	vert;
//DeadCode RJS 20Oct00 	UWordP	tmp_instr_ptr;
//DeadCode RJS 20Oct00 	SLong	totintensity = 0;

	instr_ptr += sizeof(DOIFBRIGHT);
//DeadCode RJS 19May00 	tmp_instr_ptr = (UWordP)instr_ptr;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	for (i=0; i < count; i++)
//DeadCode RJS 19May00 	{
//DeadCode RJS 19May00 		vert = *tmp_instr_ptr;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //deadcode		totintensity += (256 - newco[vert].intensity);//RJS 17Feb99
//DeadCode RJS 19May00 //deadcode		newco[vert].intensity = -1;//0;//-1;
//DeadCode RJS 19May00 //deadcode		newco[vert].specular = -1;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		tmp_instr_ptr++;
//DeadCode RJS 19May00 	}
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	SHAPE.oldAlphaSwitch = -1;
//DeadCode RJS 19May00 	totintensity = totintensity / count;
//deadcode	if (totintensity > ptr->threshold)
//deadcode	{
//deadcode		SWord	depth = ((totintensity-ptr->threshold)*255)/(256-ptr->threshold);
//deadcode
//deadcode		SHAPE.oldAlphaSwitch = current_screen->DoSetGlobalAlpha(depth);
//deadcode		instr_ptr = (UByteP)tmp_instr_ptr;
//deadcode	}
//deadcode	else
		instr_ptr += ptr->offset;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doquikpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
void shape::doquikpoly(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("23");
#endif
	DOQUIKPOLY_PTR poly_data=(DOQUIKPOLY_PTR)instr_ptr;
	ULong numVerts=poly_data->edges;
	UWord* vertices=(UWord*)(instr_ptr+sizeof(DOQUIKPOLY));
#ifndef	_NOPOLYS_

	Lib3DPoint*	pRVert = g_lpLib3d->BeginPoly(HMATERIAL(UByte(shape::newco)),numVerts);//RJS 19May00

	for (int i=0;i<numVerts;i++)
		pRVert[i]=newco[*vertices++];

	g_lpLib3d->EndPoly();
#endif
	instr_ptr+=sizeof(DOQUIKPOLY)+(UWord)poly_data->edges*sizeof(UWord);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dofadeenvelope
//Author		Robert Slater
//Date			Fri 27 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dofadeenvelope(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("24");
#endif
	DOFADEENVELOPE_PTR	ptr = (DOFADEENVELOPE_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;
	SLong	btime = *((SLongP)&GlobalAdptr[ptr->birthtimeoffset]);
	SLong	lastval, thisval;
	SLong	totval = ptr->attackval;
	SLong	tottime;

	lastval = ptr->attackval;
	thisval = ptr->decayval;

	btime = View_Point->TotalDrawFrameTime() - btime - ptr->starttime;	//RJS 05Apr00
	tottime = 0;
	if (btime > ptr->attacktime)
	{
		tottime += ptr->attacktime;
		if (btime > (tottime + ptr->decaytime))
		{
			tottime += ptr->decaytime;
			if (btime > (tottime + ptr->sustaintime))
			{
				tottime += ptr->sustaintime;
				if (btime > (tottime + ptr->releasetime))
					totval = ptr->releaseval;
				else
				{
					btime -= tottime;
					lastval = ptr->sustainval;
					thisval = ptr->releaseval;

					if (ptr->releasetime)
					{
						totval = ((thisval - lastval) * btime) / ptr->releasetime;
						totval += lastval;
					}
					else
						totval = ptr->sustainval;
				}
			}
			else
				totval = ptr->sustainval;
		}
		else
		{
			btime -= tottime;
			lastval = ptr->decayval;
			thisval = ptr->sustainval;

			if (ptr->decaytime)
			{
				totval = ((thisval - lastval) * btime) / ptr->decaytime;
				totval += lastval;
			}
			else
				totval = ptr->decayval;
		}		
	}
	else
	{
		if (ptr->attacktime)
		{
			totval = ((thisval - lastval) * btime) / ptr->attacktime;
			totval += lastval;
		}
	}

	GlobalAdptr[ptr->animfadeoffset] = totval;

	instr_ptr += sizeof(DOFADEENVELOPE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dowhiteout
//Author		Robert Slater
//Date			Tue 31 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dowhiteout(UByte *& instr_ptr)						//RJS 31Mar98
{
#ifdef	_PROCDEBUG_
	Bollox("25");
#endif
	DOWHITEOUT_PTR	ptr = (DOWHITEOUT_PTR) instr_ptr;
	SLong	dist;
	SLong	x,y,z,maxdist;

	maxdist = ptr->fadedist + 1;
	x = (SLong)object_obj3d->Body.X.f;
	y = (SLong)object_obj3d->Body.Y.f;
	z = (SLong)object_obj3d->Body.Z.f;

	z = (z<0)?-z:z;
	x = (x<0)?-x:x;
	y = (y<0)?-y:y;
	
	// Must be in the fade box...
	if ((x < maxdist) && (y < maxdist) && (z < maxdist))
	{
		if(x<y)	{dist=y;y=x;x=dist;}
		if(x<z) {dist=z;z=x;x=dist;}
		if(y<z) {dist=y;y=z;z=dist;}

		//Sorted so that absdx > absdy > absdz
		//Try +/- 8% option
		dist = x;
		y >>= 2;
		dist += y;
		y >>= 2;
		dist += y;
		y >>= 1;
		dist += y;
		z >>= 2;
		dist += z;

		if (dist < ptr->fadedist)
		{
			SLong	fadeval = 32 - ((dist << 5)/ptr->fadedist);
			if (fadeval > SHAPE.DoWhiteFade)
				SHAPE.DoWhiteFade = fadeval;

			DrawnClouds = TRUE;
		}
	}

	instr_ptr += sizeof(DOWHITEOUT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donpoints
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::donpoints(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("26");
#endif
	DONPOINTS_PTR npnt_ptr=(DONPOINTS_PTR )instr_ptr;
	COORDS_PTR ptr=(COORDS_PTR)(instr_ptr+sizeof(DONPOINTS));
	UWord vertex_count=npnt_ptr->vertex_count;
	instr_ptr+=vertex_count*sizeof(NNEXT)+sizeof(DONPOINTS);
	DoPointStruc* pdp=newco+npnt_ptr->start_vertex;
	while (vertex_count--)
	{
#ifndef	_NOPOINTS_
		pdp->setPosition(	ptr->xcoord + object_obj3d->Body.X.f,
							ptr->ycoord + object_obj3d->Body.Y.f,
							ptr->zcoord + object_obj3d->Body.Z.f	);	//RJS 19May00
#endif
		ptr++;
		pdp++;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	don4cmpnts
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::don4cmpnts(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("27");
#endif
	DON4CMPNTS_PTR npnt_ptr;

	npnt_ptr = (DON4CMPNTS_PTR )instr_ptr;

	instr_ptr += npnt_ptr->vertex_count * sizeof(COORDS) + sizeof(DON4CMPNTS);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	do4cmpnt
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::do4cmpnt(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("28");
#endif
	instr_ptr+=sizeof(DO4CMPNT);
}

//inline double ARCCOS(double x,double pi)
//{
//	double temp=(1.-x*x)/(x*x);
//	bool xneg=x<0?true:false;
//	_asm{
//		fld temp;
//		fsqrt;
//		fld1;
//		fpatan;
//		fstp temp;
//	}
//	if (xneg) temp=pi-temp;
//	return temp;
//}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		calcSpecular
//Author		Paul.   
//Date			Tue 25 Aug 1998
//
//Description	generates a value to be used for specular lighting
//				based on the dot product of the light and view vectors
//				with the vertex normal.
//
//Inputs		result of the two dot products
//
//Returns	
//
//------------------------------------------------------------------------------
//void calcSpecular(Float& specDot,Float& lightDot,SLong& specular,SLong& specFlip)
//{
	//const SLong specMax=95;	//127;
	//double pi;
//
//	_asm
//	{
//		fldpi;
//		fstp pi;
//	}
//
//	double spa=ARCCOS(specDot,pi);
//	double lia=ARCCOS(lightDot,pi);
//
//	if (spa<pi/2. && lia<pi/2.)
//	{
//		double delta=spa-lia; delta=delta<0?-delta:delta;
//
//		if (delta<pi/4.)
//		{
/*			delta=(pi/2.)+2.*delta;
			_asm{
				fld delta;
				fcos;
//				fmul st(0),st;
//				fmul st(0),st;
				fstp delta;
			}
			delta=double(specMax)*(delta+1.);
*/
//			delta=double(specMax)*(1.-delta/(pi/4.));
//			specFlip=SLong(delta);
//			if (specFlip<0)	specFlip=0;
//			else if (specFlip>specMax) specFlip=specMax;
//		}
//		else specFlip=0;
//	}
//	else specFlip=0;
//
//	spa+=pi; if (spa>pi) spa=2*pi-spa;
//	lia+=pi; if (lia>pi) lia=2*pi-lia;
//
//	if (spa<pi/2. && lia<pi/2.)
//	{
//		double delta=spa-lia; delta=delta<0?-delta:delta;
//
//		if (delta<pi/4.)
//		{
/*
			delta=(pi/2.)+2.*delta;
			_asm{
				fld delta;
				fcos;
//				fmul st(0),st;
//				fmul st(0),st;
				fstp delta;
			}
			delta=double(specMax)*(delta+1.);
*/
//			delta=double(specMax)*(1.-delta/(pi/4.));
//			specular=SLong(delta);
//			if (specular<0)	specular=0;
//			else if (specular>specMax) specular=specMax;
//		}
//		else specular=0;
//	}
//	else specular=0;
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dondupvec
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dondupvec(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("29");
#endif
	DONDUPVEC_PTR ptr=(DONDUPVEC_PTR)instr_ptr;
	if (View_Point->isLightShaded)								
	{
		R3DVALUE an,bn,cn,mag;
		DoPointStruc *vertex=newco+ptr->vertex;
		an=ptr->an;
		bn=ptr->bn;
		cn=ptr->cn;
		mag=an*an+bn*bn+cn*cn;
		mag=fastMath.FastInvSqrt(mag);
		an*=mag;
		bn*=mag;
		cn*=mag;
		for (int count=ptr->count;count>0;count--)
		{
#ifndef	_NOPOINTS_
			vertex->setNormal(an,bn,cn);
#endif
			vertex++;
		}
	}
	instr_ptr+=sizeof(DONDUPVEC);

/*OLDCODE	DONDUPVEC_PTR	ptr = (DONDUPVEC_PTR) instr_ptr;
	int				vertex = ptr->vertex;
	int				count;
	SLong			intensity;
	SLong			specular;
	SLong			specflip;

	if (View_Point->isLightShaded)								
	{
		IFShare& li=TransLightVector.ni;
		IFShare& lj=TransLightVector.nj;
		IFShare& lk=TransLightVector.nk;
		Float an=ptr->an;
		Float bn=ptr->bn;
		Float cn=ptr->cn;
		double mag=an*an+bn*bn+cn*cn;
		_asm {	fld mag;
				fsqrt;
				fstp mag;
		}
		an/=mag; bn/=mag; cn/=mag;
		Float fintensity=li.f*an+lj.f*bn+lk.f*cn;
		if (specularEnabled)
		{
		 	IFShare& vi=TransViewVector.ni;
		 	IFShare& vj=TransViewVector.nj;
		 	IFShare& vk=TransViewVector.nk;
			double fspecular=vi.f*an+vj.f*bn+vk.f*cn;
			calcSpecular(fspecular,fintensity,specular,specflip);
		}
		else specular=specflip=-1;

		fintensity*=Float(32385);

		intensity = fintensity;
		intensity+=32385;	//range is (-127 * 255) to (127 * 255) (ie. -32385 to 32385)
		if (ptr->ambientfiddle)
		{
			intensity /= 232;					
			intensity = 280 - intensity;		
			if (intensity > 256)				
				intensity = 256;				
		}
		else
		{
			intensity >>= 8;
			intensity = 256 - intensity;
		}

		if (intensity<0) intensity=0;

		for (count=0; count < ptr->count; count++ )
		{
			newco[vertex].intensity = intensity;
			newco[vertex].specular = specular;
			newco[vertex].specFlip = specflip;
			vertex++;
		}
	}

	instr_ptr+=sizeof(DONDUPVEC);
	OLDCODE*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dondeltapoints
//Author		Robert Slater
//Date			Tue 2 Jun 1998
//
//Description	For key-frame anims (now with morph between frames!)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dondeltapoints(UByte *&instr_ptr )
{
#ifdef	_PROCDEBUG_
	Bollox("30");
#endif
//DeadCode RJS 20Mar00 	DONDELTAPOINTS_PTR	ptr = (DONDELTAPOINTS_PTR) instr_ptr;
//DeadCode RJS 20Mar00 	NNEXT_PTR			npoint;
//DeadCode RJS 20Mar00 	int					count;
//DeadCode RJS 20Mar00 	DoPointStruc		*dpPtr = &newco[ptr->vertex];
//DeadCode RJS 20Mar00 	int					vno = ptr->count;
//DeadCode RJS 20Mar00 	UWord				mask = ptr->mask;
//DeadCode RJS 20Mar00 	UWord				nobitsset = ((mask&4)>>2)+((mask&2)>>1)+(mask&1);
//DeadCode RJS 20Mar00 	UWord				nextstep = nobitsset*sizeof(NDNEXT1);
//DeadCode RJS 20Mar00 	SLong				scaleup = ptr->scale;				
//DeadCode RJS 20Mar00 
//DeadCode RJS 20Mar00 	npoint = (NNEXT_PTR) (instr_ptr + ptr->offset);
//DeadCode RJS 20Mar00 	for (count = 0; count < vno; count++)
//DeadCode RJS 20Mar00 	{
//DeadCode RJS 20Mar00 		dpPtr->bodyx.f = npoint->xcoord;
//DeadCode RJS 20Mar00 		dpPtr->bodyy.f = npoint->ycoord;
//DeadCode RJS 20Mar00 		dpPtr->bodyz.f = npoint->zcoord;
//DeadCode RJS 20Mar00 		npoint++;
//DeadCode RJS 20Mar00 		dpPtr++;
//DeadCode RJS 20Mar00 	}
//DeadCode RJS 20Mar00 
//DeadCode RJS 20Mar00 	instr_ptr += sizeof(DONDELTAPOINTS);
//DeadCode RJS 20Mar00 
//DeadCode RJS 20Mar00 	dpPtr = &newco[ptr->vertex];
//DeadCode RJS 20Mar00 	switch (mask)
//DeadCode RJS 20Mar00 	{
//DeadCode RJS 20Mar00 		case DMASK_X:
//DeadCode RJS 20Mar00 		{
//DeadCode RJS 20Mar00 			NDNEXT1_PTR	npointdelta = (NDNEXT1_PTR) instr_ptr;
//DeadCode RJS 20Mar00 			for (count=0; count < vno; count++)
//DeadCode RJS 20Mar00 			{
//DeadCode RJS 20Mar00 				dpPtr->bodyx.f += (npointdelta->delta*scaleup)>>8;//RJS 24May99
//DeadCode RJS 20Mar00 				npointdelta++;
//DeadCode RJS 20Mar00 				dpPtr++;
//DeadCode RJS 20Mar00 			}
//DeadCode RJS 20Mar00 			break;
//DeadCode RJS 20Mar00 		}
//DeadCode RJS 20Mar00 		case DMASK_Y:
//DeadCode RJS 20Mar00 		{
//DeadCode RJS 20Mar00 			NDNEXT1_PTR	npointdelta = (NDNEXT1_PTR) instr_ptr;
//DeadCode RJS 20Mar00 			for (count=0; count < vno; count++)
//DeadCode RJS 20Mar00 			{
//DeadCode RJS 20Mar00 				dpPtr->bodyy.f -= (npointdelta->delta*scaleup)>>8;
//DeadCode RJS 20Mar00 				npointdelta++;
//DeadCode RJS 20Mar00 				dpPtr++;
//DeadCode RJS 20Mar00 			}
//DeadCode RJS 20Mar00 			break;
//DeadCode RJS 20Mar00 		}
//DeadCode RJS 20Mar00 		case DMASK_Z:
//DeadCode RJS 20Mar00 		{
//DeadCode RJS 20Mar00 			NDNEXT1_PTR	npointdelta = (NDNEXT1_PTR) instr_ptr;
//DeadCode RJS 20Mar00 			for (count=0; count < vno; count++)
//DeadCode RJS 20Mar00 			{
//DeadCode RJS 20Mar00 				dpPtr->bodyz.f += (npointdelta->delta*scaleup)>>8;
//DeadCode RJS 20Mar00 				npointdelta++;
//DeadCode RJS 20Mar00 				dpPtr++;
//DeadCode RJS 20Mar00 			}
//DeadCode RJS 20Mar00 			break;
//DeadCode RJS 20Mar00 		}
//DeadCode RJS 20Mar00 		case DMASK_X_Y:
//DeadCode RJS 20Mar00 		{
//DeadCode RJS 20Mar00 			NDNEXT2_PTR	npointdelta = (NDNEXT2_PTR) instr_ptr;
//DeadCode RJS 20Mar00 			for (count=0; count < vno; count++)
//DeadCode RJS 20Mar00 			{
//DeadCode RJS 20Mar00 				dpPtr->bodyx.f += (npointdelta->delta[0]*scaleup)>>8;
//DeadCode RJS 20Mar00 				dpPtr->bodyy.f -= (npointdelta->delta[1]*scaleup)>>8;
//DeadCode RJS 20Mar00 				npointdelta++;
//DeadCode RJS 20Mar00 				dpPtr++;
//DeadCode RJS 20Mar00 			}
//DeadCode RJS 20Mar00 			break;
//DeadCode RJS 20Mar00 		}
//DeadCode RJS 20Mar00 		case DMASK_X_Z:
//DeadCode RJS 20Mar00 		{
//DeadCode RJS 20Mar00 			NDNEXT2_PTR	npointdelta = (NDNEXT2_PTR) instr_ptr;
//DeadCode RJS 20Mar00 			for (count=0; count < vno; count++)
//DeadCode RJS 20Mar00 			{
//DeadCode RJS 20Mar00 				dpPtr->bodyx.f += (npointdelta->delta[0]*scaleup)>>8;
//DeadCode RJS 20Mar00 				dpPtr->bodyz.f += (npointdelta->delta[1]*scaleup)>>8;
//DeadCode RJS 20Mar00 				npointdelta++;
//DeadCode RJS 20Mar00 				dpPtr++;
//DeadCode RJS 20Mar00 			}
//DeadCode RJS 20Mar00 			break;
//DeadCode RJS 20Mar00 		}
//DeadCode RJS 20Mar00 		case DMASK_Y_Z:
//DeadCode RJS 20Mar00 		{
//DeadCode RJS 20Mar00 			NDNEXT2_PTR	npointdelta = (NDNEXT2_PTR) instr_ptr;
//DeadCode RJS 20Mar00 			for (count=0; count < vno; count++)
//DeadCode RJS 20Mar00 			{
//DeadCode RJS 20Mar00 				dpPtr->bodyy.f -= (npointdelta->delta[0]*scaleup)>>8;
//DeadCode RJS 20Mar00 				dpPtr->bodyz.f += (npointdelta->delta[1]*scaleup)>>8;
//DeadCode RJS 20Mar00 				npointdelta++;
//DeadCode RJS 20Mar00 				dpPtr++;
//DeadCode RJS 20Mar00 			}
//DeadCode RJS 20Mar00 			break;
//DeadCode RJS 20Mar00 		}
//DeadCode RJS 20Mar00 		case DMASK_X_Y_Z:
//DeadCode RJS 20Mar00 		{
//DeadCode RJS 20Mar00 			NDNEXT3_PTR	npointdelta = (NDNEXT3_PTR) instr_ptr;
//DeadCode RJS 20Mar00 			for (count=0; count < vno; count++)
//DeadCode RJS 20Mar00 			{
//DeadCode RJS 20Mar00 				dpPtr->bodyx.f += (npointdelta->delta[0]*scaleup)>>8;
//DeadCode RJS 20Mar00 				dpPtr->bodyy.f -= (npointdelta->delta[1]*scaleup)>>8;
//DeadCode RJS 20Mar00 				dpPtr->bodyz.f += (npointdelta->delta[2]*scaleup)>>8;
//DeadCode RJS 20Mar00 				npointdelta++;
//DeadCode RJS 20Mar00 				dpPtr++;
//DeadCode RJS 20Mar00 			}
//DeadCode RJS 20Mar00 			break;
//DeadCode RJS 20Mar00 		}
//DeadCode RJS 20Mar00 	}
//DeadCode RJS 20Mar00 
//DeadCode RJS 20Mar00 	dpPtr = &newco[ptr->vertex];
//DeadCode RJS 20Mar00 	for (count=vno;count>0;count--)
//DeadCode RJS 20Mar00 	{
//DeadCode RJS 20Mar00 		DoPointStruc &dp = *dpPtr;
//DeadCode RJS 20Mar00 		R3DVALUE mag;
//DeadCode RJS 20Mar00 		mag=dp.bodyx.f*dp.bodyx.f+dp.bodyy.f*dp.bodyy.f+dp.bodyz.f*dp.bodyz.f;
//DeadCode RJS 20Mar00 		mag=fastMath.FastInvSqrt(mag);
//DeadCode RJS 20Mar00 		dp.nx=dp.bodyx.f*mag;
//DeadCode RJS 20Mar00 		dp.ny=dp.bodyy.f*mag;
//DeadCode RJS 20Mar00 		dp.nz=dp.bodyz.f*mag;
//DeadCode RJS 20Mar00 		dpPtr++;
//DeadCode RJS 20Mar00 	}
//DeadCode RJS 20Mar00 
//DeadCode RJS 20Mar00 	instr_ptr += (ptr->count * nextstep);

	DONDELTAPOINTS_PTR	ptr = (DONDELTAPOINTS_PTR) instr_ptr;
	NNEXT_PTR			npoint;
	int					count;
	DoPointStruc		*dpPtr = &newco[ptr->vertex];
	int					vno = ptr->count;
	float				scaleup = float(ptr->scale)/256.0;				
	float				deltax,deltay,deltaz;
	float				basex,basey,basez;
	NDNEXT3_PTR			npointdelta;
	NDNEXT3_PTR			npointdelta2;

	npoint = (NNEXT_PTR) (instr_ptr + ptr->offset);

	if (anim_firstframe && anim_nextframe)
	{
		instr_ptr += sizeof(DONDELTAPOINTS) + (sizeof(NDNEXT3) * vno);
		npointdelta = (NDNEXT3_PTR)instr_ptr;

//we want the next frame...
		ptr = (DONDELTAPOINTS_PTR) anim_nextframe;

		scaleup = float(ptr->scale)/256.0;

		anim_nextframe += sizeof(DONDELTAPOINTS);
		
		npointdelta2 = (NDNEXT3_PTR) anim_nextframe;
		scaleup *= anim_interpolatefrac;

		for (count = 0; count < vno; count++)
		{
#ifndef	_NOPOINTS_
			dpPtr->setPosition(	float(npoint->xcoord)+(float(npointdelta2->delta[0])*scaleup),
								float(npoint->ycoord)-(float(npointdelta2->delta[1])*scaleup),
								float(npoint->zcoord)+(float(npointdelta2->delta[2])*scaleup)	);
#endif
			npoint++;
			dpPtr++;
			npointdelta2++;
		}
	}
	else
	{
		if (anim_nextframe)
		{
			instr_ptr += sizeof(DONDELTAPOINTS);
		
			npointdelta = (NDNEXT3_PTR) instr_ptr;

			ptr = (DONDELTAPOINTS_PTR) anim_nextframe;
			float	scaleup2 = float(ptr->scale)/256.0;

			anim_nextframe += sizeof(DONDELTAPOINTS);
		
			npointdelta2 = (NDNEXT3_PTR) anim_nextframe;

			for (count = 0; count < vno; count++)
			{
				basex = float(npointdelta->delta[0])*scaleup;
				basey = float(npointdelta->delta[1])*scaleup;
				basez = float(npointdelta->delta[2])*scaleup;

				deltax = ((float(npointdelta2->delta[0])*scaleup2) - basex)*anim_interpolatefrac;
				deltay = ((float(npointdelta2->delta[1])*scaleup2) - basey)*anim_interpolatefrac;
				deltaz = ((float(npointdelta2->delta[2])*scaleup2) - basez)*anim_interpolatefrac;

#ifndef	_NOPOINTS_
				dpPtr->setPosition(	float(npoint->xcoord)+basex+deltax,
									float(npoint->ycoord)-(basey+deltay),
									float(npoint->zcoord)+basez+deltaz	);
#endif
				npoint++;
				dpPtr++;
				npointdelta++;
				npointdelta2++;
			}
		}
		else
		{
			instr_ptr += sizeof(DONDELTAPOINTS);
		
			npointdelta = (NDNEXT3_PTR) instr_ptr;

			for (count = 0; count < vno; count++)
			{
#ifndef	_NOPOINTS_
				dpPtr->setPosition(	float(npoint->xcoord)+(float(npointdelta->delta[0])*scaleup),
									float(npoint->ycoord)-(float(npointdelta->delta[1])*scaleup),
									float(npoint->zcoord)+(float(npointdelta->delta[2])*scaleup)	);
#endif
				npoint++;
				dpPtr++;
				npointdelta++;
			}
		}
	}

	instr_ptr = (UByteP)npointdelta;

//DEADCODE RDH 5/19/00 	dpPtr = &newco[ptr->vertex];
//DEADCODE RDH 5/19/00 	for (count=vno;count>0;count--)
//DEADCODE RDH 5/19/00 	{
//DEADCODE RDH 5/19/00 		DoPointStruc &dp = *dpPtr;
//DEADCODE RDH 5/19/00 		R3DVALUE mag;
//DEADCODE RDH 5/19/00 		mag=dp.bodyx.f*dp.bodyx.f+dp.bodyy.f*dp.bodyy.f+dp.bodyz.f*dp.bodyz.f;
//DEADCODE RDH 5/19/00 		mag=fastMath.FastInvSqrt(mag);
//DEADCODE RDH 5/19/00 		dp.nx=dp.bodyx.f*mag;
//DEADCODE RDH 5/19/00 		dp.ny=dp.bodyy.f*mag;
//DEADCODE RDH 5/19/00 		dp.nz=dp.bodyz.f*mag;
//DEADCODE RDH 5/19/00 		dpPtr++;
//DEADCODE RDH 5/19/00 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodrawsun
//------------------------------------------------------------------------------
//Author		RJS.   
//Date		Wed 22 Jun 1998
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
 void shape::dodrawsun(UByte *&instr_ptr)		
{
//DeadCode JON 18Oct00 #ifdef	_PROCDEBUG_
//DeadCode JON 18Oct00 	Bollox("31");
//DeadCode JON 18Oct00 #endif
//DeadCode JON 18Oct00 	DODRAWSUN_PTR	ptr = (DODRAWSUN_PTR) instr_ptr;
//DeadCode JON 18Oct00 //DeadCode RJS 21Apr99  	UByteP			adptr = (UByteP) object_obj3d->AnimPtr; 			
//DeadCode JON 18Oct00 	SWord			minx, maxx;
//DeadCode JON 18Oct00 	SWord			miny, maxy;
//DeadCode JON 18Oct00 	SWord			width, height;
//DeadCode JON 18Oct00 	SWord			oldGlobalAlpha = -1;
//DeadCode JON 18Oct00 	SWord			depth;
//DeadCode JON 18Oct00 	SWord			radius = ptr->radius;
//DeadCode JON 18Oct00 	SWord			radadd;
//DeadCode JON 18Oct00 	DOHEATHAZE		hhaze;
//DeadCode JON 18Oct00 	UByteP			hhazeptr = (UByteP) &hhaze;
//DeadCode JON 18Oct00 	
//DeadCode JON 18Oct00 	minx = ptr->minx;							
//DeadCode JON 18Oct00 	miny = ptr->miny;						 	
//DeadCode JON 18Oct00 	width = ptr->width;							
//DeadCode JON 18Oct00 	height = ptr->height;						
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (SHAPE.AnimMap(GlobalAdptr,ptr->image,ptr->animoffset,ptr->animscale,minx,miny,width,height))
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		depth = GlobalAdptr[ptr->animoffset];
//DeadCode JON 18Oct00 		if (depth != SMOKED_SOLID)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			ULong val=ULong(depth);
//DeadCode JON 18Oct00 //DEADCODE RJS 5/16/00 			g_lpLib3d->SetGlobal(TOGGLE_GLOBALTRANSPARENCY,val);
//DeadCode JON 18Oct00 			g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,&val);
//DeadCode JON 18Oct00 			oldGlobalAlpha=val;
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		//Make sun grow....
//DeadCode JON 18Oct00 		radadd = ((255 - depth) * 4000)>>8;
//DeadCode JON 18Oct00 		radius += radadd;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	maxx = minx + width - 1;							
//DeadCode JON 18Oct00 	maxy = miny + height;								
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SHAPE.imapsphere(0,radius,(ImageMapNumber)ptr->image,minx,miny,maxx,maxy);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (oldGlobalAlpha != -1)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,ULong(oldGlobalAlpha));
//DeadCode JON 18Oct00 //DEADCODE RJS 5/16/00 		g_lpLib3d->SetGlobal(TOGGLE_GLOBALTRANSPARENCY,ULong(SMOKED_OFF));
//DeadCode JON 18Oct00 	}

//DEADCODE RJS 4/13/00 	if (ptr->hazeimage)
//DEADCODE RJS 4/13/00 	{
//DEADCODE RJS 4/13/00 		newco[0].bodyz.f -= 10;
//DEADCODE RJS 4/13/00 		hhaze.colour = 0;
//DEADCODE RJS 4/13/00 		hhaze.animflag = ptr->hazeanim;
//DEADCODE RJS 4/13/00 		hhaze.animscale = 1;
//DEADCODE RJS 4/13/00 		hhaze.image = ptr->hazeimage;
//DEADCODE RJS 4/13/00 		hhaze.minx = ptr->hazeminx;
//DEADCODE RJS 4/13/00 		hhaze.miny = ptr->hazeminy;
//DEADCODE RJS 4/13/00 		hhaze.width = ptr->hazewidth;
//DEADCODE RJS 4/13/00 		hhaze.height = ptr->hazeheight;
//DEADCODE RJS 4/13/00 		hhaze.vertex = 0;
//DEADCODE RJS 4/13/00 		hhaze.radius = (radius*5)>>2;
//DEADCODE RJS 4/13/00 
//DEADCODE RJS 4/13/00 		doheathaze(hhazeptr);
//DEADCODE RJS 4/13/00 	}

	instr_ptr += sizeof(DODRAWSUN);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetcolour256
//LastModified:	PD 07Jun96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	This should be the only colour setting command in the 
//				shape instruction set
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosetcolour256(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("32");
#endif
	Colour			base_colour;								//JIM 12Dec95

	DOSETCOLOUR256_PTR	temp = (DOSETCOLOUR256_PTR)instr_ptr;

//	SWord intense = Three_Dee.IntensFromRange(object_dist,fade_start,fade_end);//MGA 09May96
	//returns 0-256 so scale to 0-16.							//MGA 09May96

// 	intense = intense>>4;										//PD 10May96

	base_colour = (Colour) ((temp->basecolour)>>1);

//	if (intense)												//RJS 27Jun97
//	{															//RJS 27Jun97
//		SLong	temp1,temp2;									//RJS 27Jun97
//		temp1 = (SLong )base_colour;							//RJS 27Jun97
//		temp1 &= 0x0FF;											//RJS 27Jun97

//		temp2 = intense;										//RJS 27Jun97
//		temp1 = ASM_GetFadeColour(temp1,temp2);					//RJS 27Jun97
//		base_colour = (Colour )temp1;							//RJS 27Jun97
//	}

	shape::range = temp->spread;								//PD 25Jan96

	shape::colour = base_colour;								//PD 25Jan96

	shape::image = (ImageMapNumber) temp->imap;					//RJS 18Feb97

//	if(((shape::image & 0x7FFF) != 0x0FF)&&(object_dist<fade_start))//RJS 05Nov98
//		current_screen->SetColour(shape::image);				//PD 25Jan96

//	if(shape::range == -1)
//		current_screen->SetColour(base_colour);
//	else
//		current_screen->SetColour(base_colour,shape::range);	//PD 25Jan96

	instr_ptr += sizeof(DOSETCOLOUR256);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doswitch
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::doswitch(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("33");
#endif
	DOSWITCH_PTR	ptr = (DOSWITCH_PTR) instr_ptr;				//RJS 13Mar98
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;		//RJS 13Mar98
	ULong			flag = GlobalAdptr[ptr->animoff];					//RJS 13Mar98
																//RJS 13Mar98

	instr_ptr += sizeof(DOSWITCH);								//RJS 27May98
																//RJS 27May98
	if (ptr->nobits)											//RJS 27May98
	{															//RJS 27May98
		flag >>= ptr->bitoffset;
		flag &= 1;
																//RJS 27May98
		if (flag != ptr->value)									//RJS 15Jun98
			instr_ptr--;										//RJS 27May98
	}															//RJS 27May98
	else
	{
		flag /= ptr->animscale;										//RJS 13Mar98
																	//RJS 13Mar98
		switch (ptr->condition)										//RJS 13Mar98
		{															//RJS 13Mar98
			case GREATER_THAN:										//RJS 13Mar98
				if (flag <= ptr->value)								//RJS 13Mar98
					instr_ptr--;									//RJS 13Mar98
				break;												//RJS 13Mar98
			case LESS_THAN:											//RJS 13Mar98
				if (flag >= ptr->value)								//RJS 13Mar98
					instr_ptr--;									//RJS 13Mar98
				break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetcolourall
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dosetcolourall(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("34");
#endif
	_Error.EmitSysErr(__FILE__":ILLEGAL instruction - dosetcolourall");
	instr_ptr += sizeof(DOSETCOLOURALL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dopoint2x
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
void shape::dopoint2x(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("35");
#endif
	DOPOINT2X_PTR dp2x_ptr=(DOPOINT2X_PTR)instr_ptr;
	DoPointStruc *p0,*p1;
	R3DVALUE mag;
	p0=newco+dp2x_ptr->start_vertex;
	p1=p0+SWord(dp2x_ptr->next_vertex_offset);

#ifndef	_NOPOINTS_
	p0->setPosition(dp2x_ptr->xcoord + object_obj3d->Body.X.f,
					dp2x_ptr->ycoord + object_obj3d->Body.Y.f,
					dp2x_ptr->zcoord + object_obj3d->Body.Z.f	);	//RJS 19May00

	p1->setPosition(-dp2x_ptr->xcoord + object_obj3d->Body.X.f,
					dp2x_ptr->ycoord + object_obj3d->Body.Y.f,
					dp2x_ptr->zcoord + object_obj3d->Body.Z.f	);	//RJS 19May00
#endif
	instr_ptr += sizeof(DOPOINT2X);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	do4cmpt2x
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::do4cmpt2x(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("36");
#endif
	instr_ptr += sizeof(DO4CMPT2X);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doifcase
//LastModified:	PD 15Apr96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::doifcase(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("37");
#endif
	DOIFCASE_PTR dic_ptr = (DOIFCASE_PTR )instr_ptr;			//RJS 04Nov98
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;				//RJS 18Feb97
	SLong	offset;												//RJS 15May98
	UWord	realcnt = dic_ptr->count - 1;						//RJS 04Nov98
	UWord	animbyte;											//RJS 20Mar00

	instr_ptr += sizeof(DOIFCASE);								//RJS 20Mar00

	if (dic_ptr->bidirectional)									//RJS 15May98
	{															//RJS 15May98
		offset = *((SByteP)&GlobalAdptr[dic_ptr->flag]);				//RJS 15May98
		offset /= dic_ptr->factor;								//RJS 15May98
		if (offset)												//RJS 15May98
			offset += dic_ptr->shiftup;							//RJS 15May98

		if (offset > realcnt)									//RJS 21Feb00
			offset = realcnt;									//RJS 21Feb00
	}															//RJS 15May98
	else														//RJS 15May98
	{
		animbyte = GlobalAdptr[dic_ptr->flag];
		offset = (animbyte * realcnt)/255;						//RJS 20Mar00

// Calc fraction of sandwich filling we want...

		anim_interpolatefrac = (float(realcnt*animbyte)* 0.003921568627451) - float(offset);
		if (!offset)
			anim_firstframe = true;
		else
			anim_firstframe = false;

// Grab next frame and see if it is valid...
		if (offset < realcnt)
		{
			anim_nextframe = instr_ptr + ((offset+1) * sizeof(UWord));
			anim_nextframe += *(UWord*)anim_nextframe;
			UWord	itest = *anim_nextframe;
			if (itest == dondeltapointsno)
				anim_nextframe++;
			else
				anim_nextframe = NULL;
		}
		else
			anim_nextframe = NULL;
	}

	instr_ptr += (offset * sizeof(UWord));	//RJS 15May98
	instr_ptr += *(UWord *)instr_ptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donincpnts
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::donincpnts(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("38");
#endif
	DONINCPNTS_PTR nip_ptr;

	nip_ptr = (DONINCPNTS_PTR )instr_ptr;

	instr_ptr += nip_ptr->count * (sizeof(DOINIT) + sizeof(DOINC)) + 
					sizeof(DONINCPNTS);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dotransparenton
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dotransparenton(UByte *&instr_ptr)			//RJS 18Jun97
{
#ifdef	_PROCDEBUG_
	Bollox("39");
#endif
	DOTRANSPARENTON_PTR	ptr = (DOTRANSPARENTON_PTR) instr_ptr;

	g_lpLib3d->SetGlobal(TOGGLE_GLOBALTRANSPARENCY,ULong(ptr->depth));

	instr_ptr += sizeof(DOTRANSPARENTON);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dotransparentoff
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dotransparentoff(UByte *& )							//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("40");
#endif
	 g_lpLib3d->SetGlobal(TOGGLE_GLOBALLUMINOSITY,ULong(0));
	 g_lpLib3d->SetGlobal(TOGGLE_GLOBALTRANSPARENCY,ULong(SMOKED_OFF));

	if (SHAPE.oldAlphaSwitch != -1)
	{
		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,ULong(SHAPE.oldAlphaSwitch));
		SHAPE.oldAlphaSwitch = -1;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosphere
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	Martin 16 Apr 1996
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
void shape::dosphere(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("41");
#endif
	DOSPHERE_PTR sphere_ptr;

	sphere_ptr = (DOSPHERE_PTR )instr_ptr;

//DEADCODE JON 4/12/00 	SHAPE.drawsphere(	sphere_ptr->vertex,
//DEADCODE JON 4/12/00 						sphere_ptr->radius,
//DEADCODE JON 4/12/00 						sphere_ptr->colour,
//DEADCODE JON 4/12/00 						sphere_ptr->animflag,
//DEADCODE JON 4/12/00 						sphere_ptr->animscale,
//DEADCODE JON 4/12/00 						sphere_ptr->transp,
//DEADCODE JON 4/12/00 						(Bool)sphere_ptr->smooth,
//DEADCODE JON 4/12/00 						sphere_ptr->halowidth,
//DEADCODE JON 4/12/00 						sphere_ptr->lumtype,
//DEADCODE JON 4/12/00 						sphere_ptr->animflag2);					//RJS 21Jan98

	instr_ptr += sizeof(DOSPHERE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		domorphsphere
//Author		Robert Slater
//Date			Tue 27 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::domorphsphere(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("42");
#endif
	DOMORPHSPHERE_PTR sphere_ptr = (DOMORPHSPHERE_PTR )instr_ptr;
	SLong		 radius;
//DeadCode RJS 21Apr99 	UByteP		adptr = (UByteP) object_obj3d->AnimPtr;
	UWord		timeframe;
	SLong		timefrac;
	int			lumtype;
	int			transp;
	int			growth = sphere_ptr->MrphGrowtime;
	int			delta;
	UByte		animflag;
	UByte		colour = sphere_ptr->colour;
	int			randcol;

	radius = sphere_ptr->radius;
	lumtype = sphere_ptr->lumtype;
	transp = sphere_ptr->transp;

	timeframe = *((UWordP)&GlobalAdptr[sphere_ptr->MrphAnim]);
	timefrac = (timeframe << 15)/growth;

	delta = (timefrac*(sphere_ptr->MrphRadius - radius))>>15;
	radius += delta;

	delta = (timefrac*(sphere_ptr->MrphLumtype - lumtype))>>15;
	lumtype += delta;

	delta = (timefrac*(sphere_ptr->MrphTransp - transp))>>15;
	transp += delta;

	delta = (timefrac*(sphere_ptr->MrphColour - colour))>>15;
	colour += delta;

	if (sphere_ptr->animflag && sphere_ptr->animscale && object_obj3d->ItemPtr)	//RJS 15Nov00
	{
		animflag = GlobalAdptr[sphere_ptr->animflag];
		randcol = SHAPE.Noise(	object_obj3d->ItemPtr->World.X + animflag,
								object_obj3d->ItemPtr->World.Y + animflag,
								object_obj3d->ItemPtr->World.Z + animflag	);

		animflag++;

		randcol *= -sphere_ptr->animscale;
		randcol >>= 8;

		colour += randcol;
		GlobalAdptr[sphere_ptr->animflag] = animflag;
	}

//DeadCode RJS 03Feb98 	SHAPE.drawsphere(	sphere_ptr->vertex,
//DeadCode RJS 03Feb98 						radius,
//DeadCode RJS 03Feb98 						sphere_ptr->colour,
//DeadCode RJS 03Feb98 						sphere_ptr->animflag,
//DeadCode RJS 03Feb98 						sphere_ptr->animscale,
//DeadCode RJS 03Feb98 						transp,
//DeadCode RJS 03Feb98 						(Bool)sphere_ptr->smooth,
//DeadCode RJS 03Feb98 						sphere_ptr->halowidth,
//DeadCode RJS 03Feb98 						lumtype,
//DeadCode RJS 03Feb98 						0			);

//DEADCODE JON 4/12/00 	SHAPE.drawsphere(	sphere_ptr->vertex,
//DEADCODE JON 4/12/00 						radius,
//DEADCODE JON 4/12/00 						colour,
//DEADCODE JON 4/12/00 						0,
//DEADCODE JON 4/12/00 						1,
//DEADCODE JON 4/12/00 						transp,
//DEADCODE JON 4/12/00 						(Bool)sphere_ptr->smooth,
//DEADCODE JON 4/12/00 						sphere_ptr->halowidth,
//DEADCODE JON 4/12/00 						lumtype,
//DEADCODE JON 4/12/00 						0			);

	instr_ptr += sizeof(DOMORPHSPHERE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		domorphsphereimapd
//Author		Robert Slater
//Date			Tue 27 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::domorphsphereimapd(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("43");
#endif
	DOMORPHCYLINDERIMAPD_PTR ptr = (DOMORPHCYLINDERIMAPD_PTR )instr_ptr;
	SWord		 radius;
//DeadCode RJS 21Apr99 	UByteP		adptr = (UByteP) object_obj3d->AnimPtr;
	UWord		timeframe;
	int			lumtype;
	int			transp;
	int			growth = ptr->MrphGrowtime;
	int			delta;
	UWord		frameno = 0;
	ImageMapNumber	imap;
	SWord		oldalpha = -1;									//RJS 27Nov98
	UByte		fadedepth;// = GlobalAdptr[ptr->fadeoff];				//RJS 27Nov98

	if (ptr->fadeoff)// && (fadedepth < 255))						//RJS 27Nov98
	{
		fadedepth = GlobalAdptr[ptr->fadeoff];					//RJS 15May00
		if (!fadedepth)
		{
			instr_ptr += sizeof(DOMORPHCYLINDERIMAPD);
			return;
		}

		ULong val=ULong(fadedepth);
		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,&val);
		oldalpha=val;
	}

	radius = ptr->radius;
	lumtype = ptr->lumtype;
	transp = ptr->transp;

	timeframe = *((UWordP)&GlobalAdptr[ptr->MrphAnim]);

	delta = (timeframe*(ptr->MrphRadius - radius))/growth;
	radius += delta;

	delta = (timeframe*(ptr->MrphLumtype - lumtype))/growth;
	lumtype += delta;

	if (!lumtype)
	{
		delta = (timeframe*(ptr->MrphTransp - transp))/growth;
		transp += delta;
	}

	if (ptr->animflag)
	{
		frameno = GlobalAdptr[ptr->animflag] / ptr->animscale;
		if (ptr->imap2 && (frameno >= ptr->framelimit))
		{
			frameno -= ptr->framelimit;
			imap = (ImageMapNumber) ptr->imap2;
		}
		else
			imap = (ImageMapNumber) ptr->imap1;
	}
	else
		imap = (ImageMapNumber) ptr->imap1;

	SHAPE.imapcylinder(	ptr->vertex1,
						ptr->vertex2,
						radius,
						imap,
					   	ptr->min_ix,ptr->min_iy,
					  	ptr->width,ptr->height,
						frameno,
						0);   // trans depth...					//RJS 20Nov98

	if (oldalpha > -1)											//RJS 27Nov98
		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,ULong(oldalpha));

	instr_ptr += sizeof(DOMORPHCYLINDERIMAPD);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosmokedon
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dosmokedon(UByte *& )								//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("44");
#endif
	g_lpLib3d->SetGlobal(TOGGLE_GLOBALTRANSPARENCY,ULong(0));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosmokedoff
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dosmokedoff(UByte *& )								//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("45");
#endif
	g_lpLib3d->SetGlobal(TOGGLE_GLOBALTRANSPARENCY,ULong(0));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donormal
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::donormal(UByte *& instr_ptr)
{
	DONORMAL_PTR	ptr = DONORMAL_PTR(instr_ptr);
	instr_ptr += sizeof(DONORMAL);

	if (View_Point->isLightShaded)								//RJS 06May98
	{
		UWordP		vertexp = UWordP(instr_ptr);
		int			v1 = vertexp[0];
		int			v2 = vertexp[1];
		int			v3 = vertexp[2];
		D3DVALUE	v1i = newco[v1].getPosX() - newco[v2].getPosX();
		D3DVALUE	v1j = newco[v1].getPosY() - newco[v2].getPosY();
		D3DVALUE	v1k = newco[v1].getPosZ() - newco[v2].getPosZ();
		D3DVALUE	v2i = newco[v3].getPosX() - newco[v2].getPosX();
		D3DVALUE	v2j = newco[v3].getPosY() - newco[v2].getPosY();
		D3DVALUE	v2k = newco[v3].getPosZ() - newco[v2].getPosZ();
		D3DVALUE	ni = v1j*v2k - v1k*v2j;
		D3DVALUE	nj = v1k*v2i - v1i*v2k;
		D3DVALUE	nk = v1i*v2j - v1j*v2i;
		D3DVALUE	rmag = fastMath.FastInvSqrt(ni*ni+nj*nj+nk*nk);

		ni *= rmag;
		nj *= rmag;
		nk *= rmag;

		int	count=ptr->nopoints;
		while (count)
		{
			newco[*vertexp++].setNormal(ni,nj,nk);

			count--;
		}

		instr_ptr = UByteP(vertexp);
	}
	else
		instr_ptr += sizeof(UWord)*ptr->nopoints;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosmoothpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dosmoothpoly(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("47");
#endif
  	DOSMOOTHPOLY_PTR	poly_data;
 	
 	poly_data = (DOSMOOTHPOLY_PTR )instr_ptr;
 
//DeadCode RJS 23Mar98  	SWord intensity = 0;//temp code
//DeadCode RJS 23Mar98 	int i;
//DeadCode RJS 23Mar98  	UByte j;
//DeadCode RJS 23Mar98  	UWord vertex;
//DeadCode RJS 23Mar98  
//DeadCode RJS 23Mar98  	POLYGON.createpoly(shape::colour,shape::range);				//PD 25Jan96
//DeadCode RJS 23Mar98  	j= poly_data->edges;
//DeadCode RJS 23Mar98  
//DeadCode RJS 23Mar98  
//DeadCode RJS 23Mar98  	for (i=0;i<j;i++)
//DeadCode RJS 23Mar98  	{
//DeadCode RJS 23Mar98   		vertex = poly_data->vertices[i];
//DeadCode RJS 23Mar98  		vertex = (UWord )vertex;								//RJS 10Mar97
//DeadCode RJS 23Mar98  		POLYGON.createvert(newco[vertex],intensity);
//DeadCode RJS 23Mar98  		if (i==1)
//DeadCode RJS 23Mar98 		intensity =255;
//DeadCode RJS 23Mar98  	}
//DeadCode RJS 23Mar98 	POLYGON.drawpoly();
 	instr_ptr +=  sizeof(DOSMOOTHPOLY) + poly_data->edges*sizeof(UWord);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dovector
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
void shape::dovector(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("48");
#endif
	DOVECTOR_PTR	ptr = (DOVECTOR_PTR) instr_ptr;
//DEADCODE PD 18/01/00 	int				vertex;
	
	if (View_Point->isLightShaded)								//RJS 06May98
	{
		DoPointStruc *vptr=newco+ptr->vertex;
		R3DVALUE an,bn,cn,mag;
		an=ptr->an;
		bn=ptr->bn;
		cn=ptr->cn;
		mag=an*an+bn*bn+cn*cn;
		mag=fastMath.FastInvSqrt(mag);
		an*=mag;
		bn*=mag;
		cn*=mag;

#ifndef	_NOPOINTS_
		vptr->setNormal(an,bn,cn);								//RJS 19May00
#endif
	}
//DeadCode RJS 19May00 /*	SLong			intensity;									//RJS 20Mar98
//DeadCode RJS 19May00 	SLong			specular;
//DeadCode RJS 19May00 	SLong			specflip;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	if (View_Point->isLightShaded)								//RJS 06May98
//DeadCode RJS 19May00 	{
//DeadCode RJS 19May00 		IFShare& li=TransLightVector.ni;
//DeadCode RJS 19May00 		IFShare& lj=TransLightVector.nj;
//DeadCode RJS 19May00 		IFShare& lk=TransLightVector.nk;
//DeadCode RJS 19May00 		Float an=Float(ptr->an);
//DeadCode RJS 19May00 		Float bn=Float(ptr->bn);
//DeadCode RJS 19May00 		Float cn=Float(ptr->cn);
//DeadCode RJS 19May00 //DeadCode RJS 18Nov99 		double mag=an*an+bn*bn+cn*cn;
//DeadCode RJS 19May00 //DeadCode RJS 18Nov99 		_asm {	fld mag;
//DeadCode RJS 19May00 //DeadCode RJS 18Nov99 				fsqrt;
//DeadCode RJS 19May00 //DeadCode RJS 18Nov99 				fstp mag;
//DeadCode RJS 19May00 //DeadCode RJS 18Nov99 		}
//DeadCode RJS 19May00 //DeadCode RJS 18Nov99 		an/=mag; bn/=mag; cn/=mag;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 // Magnitude is fixed (this vector is normalised to 127)
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		an *= 0.0078740157;		// 1/127						//RJS 18Nov99
//DeadCode RJS 19May00 		bn *= 0.0078740157;										//RJS 18Nov99
//DeadCode RJS 19May00 		cn *= 0.0078740157;										//RJS 18Nov99
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		Float fintensity=li.f*an+lj.f*bn+lk.f*cn;
//DeadCode RJS 19May00 		if (specularEnabled)
//DeadCode RJS 19May00 		{
//DeadCode RJS 19May00 		 	IFShare& vi=TransViewVector.ni;
//DeadCode RJS 19May00 		 	IFShare& vj=TransViewVector.nj;
//DeadCode RJS 19May00 		 	IFShare& vk=TransViewVector.nk;
//DeadCode RJS 19May00 			double fspecular=vi.f*an+vj.f*bn+vk.f*cn;
//DeadCode RJS 19May00 			calcSpecular(fspecular,fintensity,specular,specflip);
//DeadCode RJS 19May00 		}
//DeadCode RJS 19May00 		else specular=specflip=-1;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		fintensity*=Float(32385);
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		intensity = fintensity;
//DeadCode RJS 19May00 		intensity+=32385;	//range is (-127 * 255) to (127 * 255) (ie. -32385 to 32385)
//DeadCode RJS 19May00 		if (ptr->ambientfiddle)
//DeadCode RJS 19May00 		{
//DeadCode RJS 19May00 			intensity /= 232;											//RJS 23Apr98
//DeadCode RJS 19May00 			intensity = 280 - intensity;								//RJS 20Mar98
//DeadCode RJS 19May00 			if (intensity > 256)										//RJS 20Mar98
//DeadCode RJS 19May00 				intensity = 256;										//RJS 20Mar98
//DeadCode RJS 19May00 		}
//DeadCode RJS 19May00 		else
//DeadCode RJS 19May00 		{
//DeadCode RJS 19May00 			intensity >>= 8;
//DeadCode RJS 19May00 			intensity = 256 - intensity;
//DeadCode RJS 19May00 		}
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		vertex = ptr->vertex;
//DeadCode RJS 19May00 		if (intensity<0) intensity=0;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		newco[vertex].intensity = intensity;						//RJS 20Mar98
//DeadCode RJS 19May00 		newco[vertex].specular = specular;						//PD 24Aug98
//DeadCode RJS 19May00 		newco[vertex].specFlip = specflip;						//PD 24Aug98
//DeadCode RJS 19May00 	}
//DeadCode RJS 19May00 */
	instr_ptr += sizeof(DOVECTOR);
}

void shape::makeViewLightVec()
{
#ifdef	_PROCDEBUG_
	Bollox("49");
#endif
/*DEAD	COORDS3D &viewPos=View_Point->World;
	//COORDS3D &itemPos=object_obj3d->ItemPtr->World;
	LightVec &sunPos=Three_Dee.SunLightVector;
	IFShare &li=ViewLightVector.ni,&lj=ViewLightVector.nj,&lk=ViewLightVector.nk;
	li.i=sunPos.ni.i-viewPos.X;
	lj.i=sunPos.nj.i-viewPos.Y;
	lk.i=sunPos.nk.i-viewPos.Z;
	_matrix.transform(Three_Dee.fpviewer_matrix,li,lj,lk);
	li.f-=object_obj3d->Body.X.f;
	lj.f-=object_obj3d->Body.Y.f;
	lk.f-=object_obj3d->Body.Z.f;
	double mag=li.f*li.f+lj.f*lj.f+lk.f*lk.f;
	_asm 
	{
	fld mag;
	fsqrt;
	fstp mag;
	}
	li.f/=mag; lj.f/=mag; lk.f/=mag;
	IsAircraft|=0x02;
DEAD*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dotransformlight
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
void shape::dotransformlight(UByte *& instr_ptr)
{
	DOTRANSFORMLIGHT_PTR	ptr = DOTRANSFORMLIGHT_PTR(instr_ptr);

#ifdef	_PROCDEBUG_
	Bollox("50");
#endif
	if (!IsSubShape)
	{
		if (object_obj3d->ItemPtr && object_obj3d->ItemPtr->Status.size==AirStrucSize) specularEnabled=true;

		LIGHTINGDESC lightDesc;
#ifdef	_LIGHTEXTREME_
		lightDesc.lowRGB=0x000000;/*shadedRGBlo;*/
		lightDesc.highRGB=0xFFFFFF;/*shadedRGBhi;*/
#else
		lightDesc.lowRGB=shadedRGBlo;
		lightDesc.highRGB=shadedRGBhi;
#endif
		lightDesc.ambientRGB=shadedRGBamb;
		lightDesc.lowDot=0.f;
		lightDesc.highDot=1.f;
//DeadCode JON 11Sep00 		lightDesc.specularPower=1.2f;
		lightDesc.specularRGB = 	Land_Scape.currentLighting.specularHighlight.col();
		g_lpLib3d->SetAmbientLighting(lightDesc);

		staticRGBlo = lightDesc.lowRGB;
		staticRGBhi = lightDesc.highRGB;
		staticRGBamb = lightDesc.ambientRGB;

//DeadCode RJS 15Nov00 		COORDS3D itemPos;
//DeadCode RJS 15Nov00 
//DeadCode RJS 15Nov00 		if (!Three_Dee.GetPosRec(object_obj3d->ItemPtr,itemPos))
//DeadCode RJS 15Nov00 			itemPos=object_obj3d->ItemPtr->World;

//DeadCode JON 11Sep00 		LightVec& sunPos=Three_Dee.SunLightVector;
//DeadCode JON 11Sep00 		g_lpLib3d->SetLightVector(R3DVALUE(-sunPos.ni.i),
//DeadCode JON 11Sep00 									R3DVALUE(-sunPos.nj.i),
//DeadCode JON 11Sep00 									R3DVALUE(-sunPos.nk.i));

		LIGHTFLAG	lf = LIGHTFLAG(GetLightingType(ptr->lightflag));
		g_lpLib3d->SetObjectLighting(lf);//RJS 27Sep00

//Old_Code PD 18Jan100 		LightVec& sunPos=Three_Dee.SunLightVector;
//Old_Code PD 18Jan100 
//Old_Code PD 18Jan100 		IFShare& li=TransLightVector.ni;
//Old_Code PD 18Jan100 		IFShare& lj=TransLightVector.nj;
//Old_Code PD 18Jan100 		IFShare& lk=TransLightVector.nk;
//Old_Code PD 18Jan100 			
//Old_Code PD 18Jan100 		li.i=sunPos.ni.i;	//-itemPos.X;
//Old_Code PD 18Jan100 		lj.i=sunPos.nj.i;	//-itemPos.Y;
//Old_Code PD 18Jan100 		lk.i=sunPos.nk.i;	//-itemPos.Z;
//Old_Code PD 18Jan100 
//Old_Code PD 18Jan100 		_matrix.inverseMobileMatrix(object_obj3d->AngH,object_obj3d->AngC,
//Old_Code PD 18Jan100 									object_obj3d->AngR,light_matrix);
//Old_Code PD 18Jan100 
//Old_Code PD 18Jan100 		_matrix.transform(&light_matrix,li,lj,lk);
//Old_Code PD 18Jan100 
//Old_Code PD 18Jan100 		//and normalise...
//Old_Code PD 18Jan100 
//Old_Code PD 18Jan100 		double mag=li.f*li.f+lj.f*lj.f+lk.f*lk.f;
//Old_Code PD 18Jan100 
//Old_Code PD 18Jan100 		_asm {	fld mag;
//Old_Code PD 18Jan100 				fsqrt;
//Old_Code PD 18Jan100 				fstp mag;
//Old_Code PD 18Jan100 		}
//Old_Code PD 18Jan100 		li.f/=mag; lj.f/=mag; lk.f/=mag;
//Old_Code PD 18Jan100 
//Old_Code PD 18Jan100 //dead		if (specularEnabled)
//Old_Code PD 18Jan100 		{
//Old_Code PD 18Jan100 			IFShare& vi=TransViewVector.ni;
//Old_Code PD 18Jan100 			IFShare& vj=TransViewVector.nj;
//Old_Code PD 18Jan100 			IFShare& vk=TransViewVector.nk;
//Old_Code PD 18Jan100 
//Old_Code PD 18Jan100 			COORDS3D& viewPos=View_Point->World;
//Old_Code PD 18Jan100 
//Old_Code PD 18Jan100 			vi.i=(viewPos.X-itemPos.X)&0xFFFFFF80;
//Old_Code PD 18Jan100   			vj.i=(viewPos.Y-itemPos.Y)&0xFFFFFF80;
//Old_Code PD 18Jan100 			vk.i=(viewPos.Z-itemPos.Z)&0xFFFFFF80;
//Old_Code PD 18Jan100 
//Old_Code PD 18Jan100 			_matrix.transform(&light_matrix,vi,vj,vk);
//Old_Code PD 18Jan100 
//Old_Code PD 18Jan100 			mag=vi.f*vi.f+vj.f*vj.f+vk.f*vk.f;
//Old_Code PD 18Jan100 
//Old_Code PD 18Jan100 			_asm {	fld mag;
//Old_Code PD 18Jan100 					fsqrt;
//Old_Code PD 18Jan100 					fstp mag;
//Old_Code PD 18Jan100 			}
//Old_Code PD 18Jan100 
//Old_Code PD 18Jan100 			vi.f/=mag; vj.f/=mag; vk.f/=mag;
//Old_Code PD 18Jan100 		}
	}

	View_Point->isLightShaded = TRUE;
	instr_ptr += sizeof(DOTRANSFORMLIGHT);						//RJS 27Sep00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doswitchlightson
//Author		Robert Slater
//Date			Thu 30 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dolshadeon(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("51");
#endif
	DOLSHADEON_PTR	ptr = (DOLSHADEON_PTR) instr_ptr;
	LIGHTFLAG		lflag = LF_AMBIENT;
	LIGHTINGDESC	lightDesc;

	lightDesc.lowDot=0.f;
	lightDesc.highDot=1.f;
//DeadCode JON 11Sep00 	lightDesc.specularPower=1.2f;
	lightDesc.specularRGB = 	Land_Scape.currentLighting.specularHighlight.col();
	lightDesc.lowRGB=shadedRGBlo;
	lightDesc.highRGB=shadedRGBhi;
	lightDesc.ambientRGB=shadedRGBamb;

	switch (ptr->surfacetype)
	{
	case STEXT_DULL:
		lflag = LF_LIGHTING;
	break;
	case STEXT_SHINY:
		lflag = LF_SPECULAR;
	break;
	case STEXT_REFLECTIVE:
		lflag = LF_ALPHA;
	break;
	case STEXT_LIGHT:
		lightDesc.lowRGB=0xFFFFFF;
		lightDesc.highRGB=0xFFFFFF;
		lightDesc.ambientRGB=0xFFFFFF;
		lflag = LF_LIGHTSOURCE;
	break;
	}

	g_lpLib3d->SetAmbientLighting(lightDesc);
	g_lpLib3d->SetObjectLighting(lflag);

	instr_ptr += sizeof(DOLSHADEON);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dorelpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
void shape::dorelpoly(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("52");
#endif
	DORELPOLY_PTR drp_ptr=(DORELPOLY_PTR)instr_ptr;
	ULong numVertices=drp_ptr->edges;
	SWord* pOffset=(SWord*)(instr_ptr+sizeof(DORELPOLY));
	UWord vertex=UWord(drp_ptr->start_vertex);
#ifndef	_NOPOLYS_

	Lib3DPoint*	pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(shape::colour),numVertices);//RJS 19May00
	for (int i=0;i<numVertices;i++)
	{
		pRVerts[i]=newco[vertex];
		vertex=UWord(vertex+*pOffset++);
	}
	g_lpLib3d->EndPoly();
#endif
	instr_ptr+=sizeof(DORELPOLY)+(numVertices-1)*sizeof(SWord);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		donspheres
//Author		Robert Slater
//Date			Mon 13 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::donspheres(UByte *& instr_ptr)						//RJS 13Jul98
{
#ifdef	_PROCDEBUG_
	Bollox("53");
#endif
//DeadCode RJS 20Oct00 	DONSPHERES_PTR	ptr = (DONSPHERES_PTR) instr_ptr;
//DeadCode RJS 20Oct00 	int	count;



	instr_ptr += sizeof(DONSPHERES);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		donspheresimapd
//Author		Robert Slater
//Date			Mon 13 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::donspheresimapd(UByte *& instr_ptr)				//RJS 13Jul98
{
#ifdef	_PROCDEBUG_
	Bollox("54");
#endif
//DeadCode RJS 20Oct00 	DONSPHERESIMAPD_PTR	ptr = (DONSPHERESIMAPD_PTR) instr_ptr;
//DeadCode RJS 20Oct00 	int	count;



	instr_ptr += sizeof(DONSPHERESIMAPD);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doweaponoff
//Author		Robert Slater
//Date			Tue 14 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doweaponoff(UByte *& instr_ptr)								//RJS 13Jul98
{
#ifdef	_PROCDEBUG_
	Bollox("55");
#endif
	DOWEAPONOFF_PTR ptr = (DOWEAPONOFF_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP)object_obj3d->AnimPtr;

	instr_ptr += sizeof(DOWEAPONOFF);
	if (GlobalAdptr[ptr->launchoffset] == ptr->launchertype)
	{
		SWord	stores = *((SWordP)&GlobalAdptr[ptr->storesoffset]);
		if (stores == 0)
			instr_ptr--;
	}
	else
		instr_ptr--;													//RJS 02Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodrawreflectpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dodrawreflectpoly(UByte *& instr_ptr )				
{
#ifdef	_PROCDEBUG_
	Bollox("56");
#endif
	ULong numVertices=((DODRAWREFLECTPOLY_PTR)instr_ptr)->nopoints;
	instr_ptr+=sizeof(DODRAWREFLECTPOLY);
	UWordP	vertexp = (UWordP)instr_ptr;						//RJS 11Feb00

	//test clip flags before drawing the polygon...
	if (Save_Data.cockpit3Ddetail[COCK3D_SKYIMAGES])
	{
		LIGHTFLAG lf(LF_ALPHA);
		g_lpLib3d->SetObjectLighting(lf);
#ifndef	_NOPOLYS_

		Lib3DPoint*	pRVerts = g_lpLib3d->BeginPoly(shape::hMaterial,numVertices);//RJS 19May00
#endif
		for (int i=0;i<numVertices;i++)
		{
			instr_ptr++;
#ifndef	_NOPOLYS_

			pRVerts[i]=newco[*vertexp++];						//RJS 11Feb00
#endif
		}
#ifndef	_NOPOLYS_

		g_lpLib3d->EndPoly();
#endif
		g_lpLib3d->SetObjectLighting(lf);
	}
	else instr_ptr+=2*numVertices;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doresetanim
//Author		Robert Slater
//Date			Fri 13 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doresetanim(UByte *& instr_ptr)			
{
#ifdef	_PROCDEBUG_
	Bollox("57");
#endif
	DORESETANIM_PTR	ptr = (DORESETANIM_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;
	UWord			controlframe = *((UWordP)&GlobalAdptr[ptr->animofftimer]);

	if (controlframe == 0)
		GlobalAdptr[ptr->animoffframe] = ptr->resetval;

	instr_ptr += sizeof(DORESETANIM);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	docapture
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dospin(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("58");
#endif
	DOSPIN_PTR	ptr = (DOSPIN_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP		adptr = (UByteP) object_obj3d->AnimPtr;
	UWordP		anglep = (UWordP)&GlobalAdptr[ptr->animoff];
	UWord		currentangle = *anglep;
	UWord		spinspeed = *((UWordP)&GlobalAdptr[ptr->speedoff]);

	if (spinspeed)
	{
		currentangle += ((spinspeed * View_Point->DrawFrameTime())/100);
		*anglep = currentangle;
	}
	else
	{
		UWord	diff = ptr->maxspeed - ptr->minspeed;
		if (diff)												//MS 10Dec98
		{
			spinspeed = ptr->minspeed + Math_Lib.rnd(diff);
			*((UWordP)&GlobalAdptr[ptr->speedoff]) = spinspeed;
		}
		else
			*anglep = ptr->minspeed;			// crap fix to fix rotate...//MS 10Dec98
	}

	instr_ptr += sizeof(DOSPIN);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetcolourh
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dosetcolourh(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("59");
#endif
	_Error.EmitSysErr(__FILE__":ILLEGAL instruction - dosetcolourh");
	instr_ptr += sizeof(DOSETCOLOURH);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doquiksmoothpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::doquiksmoothpoly(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("60");
#endif
//DeadCode RJS 23Mar98 	DOQUIKSMOOTHPOLY_PTR poly_data;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	poly_data = (DOQUIKSMOOTHPOLY_PTR )instr_ptr;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	
//DeadCode RJS 23Mar98 	SWord intensity = 0;//temp code
//DeadCode RJS 23Mar98 	int i,j;
//DeadCode RJS 23Mar98 	UWord vertex;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	POLYGON.createpoly(shape::colour,shape::range);				//PD 25Jan96
//DeadCode RJS 23Mar98 	j= poly_data->edges;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	for (i=0;i<j;i++)
//DeadCode RJS 23Mar98 	{
//DeadCode RJS 23Mar98 		vertex = (UWord )poly_data->vertices[i];				//RJS 10Mar97
//DeadCode RJS 23Mar98 		POLYGON.createvert(newco[vertex],intensity);
//DeadCode RJS 23Mar98 		if (i==1)
//DeadCode RJS 23Mar98 		intensity =255;
//DeadCode RJS 23Mar98 	}
//DeadCode RJS 23Mar98 	POLYGON.drawpoly();
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	instr_ptr += sizeof(DOQUIKSMOOTHPOLY) + j*sizeof(UWord);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dorepos
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dorepos(UByte *& )									//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("61");
#endif
	_Error.EmitSysErr(__FILE__":Not a real instruction (DOREPOS)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodepthcolour
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dodepthcolour(UByte *& )							//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("62");
#endif
	_Error.EmitSysErr(__FILE__":Not a real instruction (DODEPTHCOLOUR)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodepthpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dodepthpoly(UByte *& )								//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("63");
#endif
	_Error.EmitSysErr(__FILE__":Not a real instruction (DODEPTHPOLY)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doimagemap
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::doimagemap(UByte *& )								//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("64");
#endif
	//Empty
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	docreateipoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
void shape::docreateipoly(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("65");
#endif

#ifndef	_NOPOLYS_
	DOCREATEIPOLY_PTR ptr = (DOCREATEIPOLY_PTR)instr_ptr;
	ImageMapNumber	imapno;
	imapno = (ImageMapNumber )ptr->image_no;
//	if (IsAircraft && (current_level>=2))
//	{
//		//once only per shape, generate light shade info
//		//if (!(IsAircraft&0x02))	makeViewLightVec();
//		//select colour from the image;
//		ImageMapDescPtr imap=Image_Map.GetImageMapPtr(imapno);
//		shape::colour=Colour(*imap->body);
//		shape::hMaterial=HMATERIAL(shape::colour);
//	}
//	else 
	shape::hMaterial=HMATERIAL(Image_Map.GetImageMapPtr(imapno));
#endif
	instr_ptr += sizeof(DOCREATEIPOLY);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	docreateivert
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::docreateivert(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("66");
#endif
	instr_ptr += sizeof(DOCREATEIVERT);
}

SWord shape::plainPolyLight(DoPointStruc** pDp)
{
	//generate 2 vectors
	Float a[3],b[3],n[3];
	D3DVALUE	v2x,v1x,v0x;
	D3DVALUE	v2y,v1y,v0y;
	D3DVALUE	v2z,v1z,v0z;

	pDp[0]->getPosition(v0x,v0y,v0z);
	pDp[1]->getPosition(v1x,v1y,v1z);
	pDp[2]->getPosition(v2x,v2y,v2z);

	a[0]=v1x-v0x;
	a[1]=v1y-v0y;
	a[2]=v1z-v0z;
	b[0]=v1x-v2x;
	b[1]=v1y-v2y;
	b[2]=v1z-v2z;
	//use cross product to generate normal
	n[0]=a[1]*b[2]-a[2]*b[1];
	n[1]=a[2]*b[0]-a[0]*b[2];
	n[2]=a[0]*b[1]-a[1]*b[0];
	//normalise vector
	double mag=n[0]*n[0]+n[1]*n[1]+n[2]*n[2];
	_asm 
	{
	fld mag;
	fsqrt
	fstp mag
	}
	n[0]/=-mag; n[1]/=-mag; n[2]/=-mag;
	//dot product normal with light vector
	mag=Float(32385)*(n[0]*ViewLightVector.ni.f+
		n[1]*ViewLightVector.nj.f+
		n[2]*ViewLightVector.nk.f);
	SLong intensity=SLong(mag)+32385;
	intensity/=232;
	intensity=280-intensity;
	if (intensity>256)		intensity=256;
	else if (intensity<0)	intensity=0;
	return SWord(intensity);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodrawipoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
void shape::dodrawipoly(UByte *& instr_ptr)				//RJS 19Mar97
{
#ifdef	_PROCDEBUG_
	Bollox("67");
#endif
	UWordP		vertexptr;										//RJS 11Feb00

	ULong numVertices=((DODRAWIPOLY_PTR)instr_ptr)->nopoints;
	instr_ptr+=sizeof(DODRAWIPOLY);
	vertexptr = (UWordP)instr_ptr;								//RJS 11Feb00
#ifndef	_NOPOLYS_

	Lib3DPoint*	pRVerts = g_lpLib3d->BeginPoly(shape::hMaterial,numVertices);//RJS 19May00
	for (int i=0;i<numVertices;i++)
		pRVerts[i]=newco[*vertexptr++];							//RJS 11Feb00
	g_lpLib3d->EndPoly();
#else
	for (int i=0;i<numVertices;i++)
		vertexptr++;	
#endif

	instr_ptr = (UByteP) vertexptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dodrawopoly
//Author		Paul.   
//Date			Tue 16 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dodrawopoly(UByte *& )
{
#ifdef	_PROCDEBUG_
	Bollox("68");
#endif
	g_lpLib3d->SetGlobal(TOGGLE_GLOBALTRANSPARENCY,ULong(SMOKED_ON));
	g_lpLib3d->EndPoly();
	g_lpLib3d->SetGlobal(TOGGLE_GLOBALTRANSPARENCY,ULong(SMOKED_OFF));
}
			 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodrawrpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dodrawrpoly(UByte *& instr_ptr)								//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("69");
#endif
	DODRAWRPOLY_PTR	ptr = (DODRAWRPOLY_PTR )instr_ptr;
	SLong	flag;												//RJS 12Feb97
	int		novertices;									
	int		i;											
	UWordP	vertexp;												//RJS 11Feb00
	SWord	ix,iy;

	flag = SLong(GlobalAdptr[ptr->flag])<<6;
	novertices = ptr->nopoints;									
	instr_ptr += sizeof(DODRAWRPOLY);
	vertexp = (UWordP)instr_ptr;

#ifndef	_NOPOLYS_

	Lib3DPoint*	pRVerts = g_lpLib3d->BeginPoly(shape::hMaterial,novertices);//RJS 19May00
	for (i=0;i<novertices;i++)
	{
		pRVerts[i]=newco[*vertexp++];							//RJS 11Feb00
		pRVerts[i].getIMapCoords(ix,iy);
		pRVerts[i].setIMapCoords(ix,iy+flag);
	}
	g_lpLib3d->EndPoly();

#endif
}
			 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	docopyivert
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::docopyivert(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("70");
#endif
//DeadCode RJS 19May00 	UWord	vertex;
//DeadCode RJS 19May00 	SWord	ix,
//DeadCode RJS 19May00 			iy;

	DOCOPYIVERT_PTR ptr = (DOCOPYIVERT_PTR)instr_ptr;

//DeadCode RJS 19May00 	vertex = ptr->vertex;
//DeadCode RJS 19May00 	ix = ptr->image_x;
//DeadCode RJS 19May00 	iy = ptr->image_y;
#ifndef	_NOPOINTS_

	newco[ptr->vertex].setIMapCoords(SWord(ptr->image_x),SWord(ptr->image_y));//RJS 19May00
#endif
	instr_ptr += sizeof(DOCOPYIVERT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosmthrelpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dosmthrelpoly(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("71");
#endif
//DeadCode RJS 23Mar98 	DOSMTHRELPOLY_PTR drp_ptr;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	UWord	counter;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	drp_ptr = (DOSMTHRELPOLY_PTR )instr_ptr;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	counter = (UWord )(((UWord )drp_ptr->edges)-1);				//PD 15Jan96
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	SWord intensity = 3;//temp code
//DeadCode RJS 23Mar98 	int i;
//DeadCode RJS 23Mar98 	UWord vertex,old_vertex,new_vertex;
//DeadCode RJS 23Mar98 	SByte offset;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	POLYGON.createpoly(shape::colour,shape::range);				//PD 25Jan96
//DeadCode RJS 23Mar98 	
//DeadCode RJS 23Mar98 	vertex = (UWord )drp_ptr->start_vertex;						//RJS 10Mar97
//DeadCode RJS 23Mar98 	POLYGON.createvert(newco[vertex]);
//DeadCode RJS 23Mar98 	old_vertex=drp_ptr->start_vertex;
//DeadCode RJS 23Mar98 	
//DeadCode RJS 23Mar98 	for (i=0;i<counter;i++)
//DeadCode RJS 23Mar98 	{
//DeadCode RJS 23Mar98 		offset=*(instr_ptr +(sizeof(DOSMTHRELPOLY))+(i*sizeof(SByte)));
//DeadCode RJS 23Mar98 		new_vertex = (UWord )(old_vertex + offset);				//PD 15Jan96
//DeadCode RJS 23Mar98 		vertex = (UWord )new_vertex;							//RJS 10Mar97
//DeadCode RJS 23Mar98 		POLYGON.createvert(newco[vertex],intensity);
//DeadCode RJS 23Mar98 		old_vertex=new_vertex;
//DeadCode RJS 23Mar98 		if (i==1)
//DeadCode RJS 23Mar98 			intensity =255;
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	}
//DeadCode RJS 23Mar98 	POLYGON.drawpoly();
//DeadCode RJS 23Mar98 
//DeadCode RJS 23Mar98 	instr_ptr += sizeof(DOSMTHRELPOLY) + counter * sizeof(SByte);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doquikrelpoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::doquikrelpoly(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("72");
#endif
	DOQUIKRELPOLY_PTR drp_ptr=(DOQUIKRELPOLY_PTR )instr_ptr;
	instr_ptr+=sizeof(DOQUIKRELPOLY);
	ULong numVertices;

	numVertices=drp_ptr->edges;
#ifndef	_NOPOLYS_

	Lib3DPoint*	pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(shape::colour),numVertices);//RJS 19May00
	UWord vertex=drp_ptr->start_vertex;
#endif
	for (int i=0;i<numVertices;i++)
	{
#ifndef	_NOPOLYS_
		pRVerts[i]=newco[vertex];
		vertex+=*SByteP(instr_ptr);
#endif
		instr_ptr++;
	}
#ifndef	_NOPOLYS_
	g_lpLib3d->EndPoly();
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donsubs
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::donsubs(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("73");
#endif
	DONSUBS_PTR dns_ptr;
	UWord	i;
	UByteP	old_ptr;											//RJS 19Mar97

	dns_ptr = (DONSUBS_PTR )instr_ptr;

//	instr_ptr += sizeof(UWord);
	instr_ptr += sizeof(DONSUBS);

	for(i=0;i<dns_ptr->count;i++)								//RJS 19Mar97
	{
		old_ptr = instr_ptr;
		instr_ptr += *(UWord *)instr_ptr;	//Unsigned offset from current pos//RJS 19Mar97
		InterpLoop(instr_ptr);
		instr_ptr = old_ptr + sizeof(SWord);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dobitsofffx
//Author		Robert Slater
//Date			Fri 15 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dobitsofffx(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("74");
#endif
//DeadCode RJS 20Oct00 	DOBITSOFFFX_PTR	ptr = (DOBITSOFFFX_PTR)  instr_ptr;

#pragma message("dobitsofffx does nowt!")
//DEADCODE RDH 5/19/00 //DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;
//DEADCODE RDH 5/19/00 	UByte			damval = GlobalAdptr[ptr->animoff];
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 	if (damval > ptr->threshold)
//DEADCODE RDH 5/19/00 	{
//DEADCODE RDH 5/19/00 		if (fprealobject_matrix)
//DEADCODE RDH 5/19/00 		{
//DEADCODE RDH 5/19/00 			UWord	threshscale = 255 - ptr->threshold;
//DEADCODE RDH 5/19/00 			if (threshscale)
//DEADCODE RDH 5/19/00 			{
//DEADCODE RDH 5/19/00 				UWord	randno = Math_Lib.rnd() * (damval - ptr->threshold);
//DEADCODE RDH 5/19/00 				randno /= threshscale;
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 				if (randno > 32767)
//DEADCODE RDH 5/19/00 				{
//DEADCODE RDH 5/19/00 					DoPointStruc dp;
//DEADCODE RDH 5/19/00 					dp.bodyx.i = ptr->xpos;
//DEADCODE RDH 5/19/00 					dp.bodyy.i = ptr->ypos;
//DEADCODE RDH 5/19/00 					dp.bodyz.i = ptr->zpos;
//DEADCODE RDH 5/19/00 					_matrix.transformNC(fprealobject_matrix,&dp);
//DEADCODE RDH 5/19/00 					dp.bodyx.f += object_obj3d->ItemPtr->World.X;
//DEADCODE RDH 5/19/00 					dp.bodyy.f += object_obj3d->ItemPtr->World.Y;
//DEADCODE RDH 5/19/00 					dp.bodyz.f += object_obj3d->ItemPtr->World.Z;
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 					WorldStuff*	worldptr = mobileitem::currworld;
//DEADCODE RDH 5/19/00 					Coords3D	launchcoords;
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 					launchcoords.X = SLong(dp.bodyx.f);
//DEADCODE RDH 5/19/00 					launchcoords.Y = SLong(dp.bodyy.f);
//DEADCODE RDH 5/19/00 					launchcoords.Z = SLong(dp.bodyz.f);
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 					switch (ptr->fxtype)
//DEADCODE RDH 5/19/00 					{
//DEADCODE RDH 5/19/00 						case DAMFX_SPARKS:
//DEADCODE RDH 5/19/00 							Trans_Obj.LaunchJunk((mobileitem*)object_obj3d->ItemPtr,SPARK,launchcoords,*worldptr);
//DEADCODE RDH 5/19/00 							break;
//DEADCODE RDH 5/19/00 						case DAMFX_SMOKE:
//DEADCODE RDH 5/19/00 							Trans_Obj.LaunchJunk((mobileitem*)object_obj3d->ItemPtr,SPARK,launchcoords,*worldptr);
//DEADCODE RDH 5/19/00 							break;
//DEADCODE RDH 5/19/00 						case DAMFX_JUNK:
//DEADCODE RDH 5/19/00 							Trans_Obj.LaunchJunk((mobileitem*)object_obj3d->ItemPtr,SPARK,launchcoords,*worldptr);
//DEADCODE RDH 5/19/00 							break;
//DEADCODE RDH 5/19/00 					}
//DEADCODE RDH 5/19/00 				}
//DEADCODE RDH 5/19/00 			}
//DEADCODE RDH 5/19/00 		}
//DEADCODE RDH 5/19/00 	}

	instr_ptr += sizeof(DOBITSOFFFX);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doondamaged
//Author		Robert Slater
//Date			Mon 18 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doondamaged(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("75");
#endif
	DOONDAMAGED_PTR	ptr = (DOONDAMAGED_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;
	SLong			damval = GlobalAdptr[ptr->animoff];			//RJS 28Apr99
	SLong			topthresh;									//RJS 28Apr99

	instr_ptr += sizeof(DOONDAMAGED);

	if (ptr->topthresh == 0)
		topthresh = 256;
	else
		topthresh = SLong(ptr->topthresh);

	if ((damval <= ptr->thresh) || (damval >= topthresh))		//RJS 22May00
		instr_ptr--;											//RJS 22May00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dosetmipmap
//Author		Robert Slater
//Date			Mon 24 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dosetmipmap(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("76");
#endif
	DOSETMIPMAP_PTR	ptr = (DOSETMIPMAP_PTR) instr_ptr;

	if (ptr->textureflag)
	{
		ULong val=oldMipMapState;
		oldMipMapState=val?true:false;
	}
	else
	{
		ULong val=ULong(FALSE);
		oldMipMapState=val?true:false;
	}

	instr_ptr += sizeof(DOSETMIPMAP);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donvec
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
void shape::donvec(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("77");
#endif
	DONVEC_PTR dnv_ptr=(DONVEC_PTR )instr_ptr;
//DeadCode RJS 18Nov99 	int			vertex;
	int			nopoints;
	NEXTVEC_PTR	vecptr;		//RJS 23Feb00
	SLong		intensity;
	SLong		specular;
	SLong		specflip;
//DeadCode RJS 20Oct00 	DoPointStruc*	dp = &newco[dnv_ptr->vertex];				//RJS 18Nov99

//DeadCode RJS 18Nov99 	vertex = dnv_ptr->vertex;
	nopoints = dnv_ptr->count;

	instr_ptr += sizeof(DONVEC);
	vecptr = (NEXTVEC_PTR) instr_ptr;							//RJS 23Feb00

	instr_ptr += (sizeof(NEXTVEC)*nopoints);

	if (View_Point->isLightShaded)								//RJS 06May98
	{
		DoPointStruc *vptr=newco+dnv_ptr->vertex;
//DeadCode RJS 23Feb00		NEXTVEC_PTR	vecptr=(NEXTVEC_PTR)instr_ptr;

		for (int j=nopoints;j>0;j--)
		{
			R3DVALUE an,bn,cn,mag;
			an=vecptr->an;
			bn=vecptr->bn;
			cn=vecptr->cn;
			mag=an*an+bn*bn+cn*cn;
			mag=fastMath.FastInvSqrt(mag);
			an*=mag;
			bn*=mag;
			cn*=mag;
#ifndef	_NOPOINTS_
			vptr->setNormal(an,bn,cn);							//RJS 19May00
#endif
			vptr++;
			vecptr++;
		}
//DeadCode RJS 17Feb00 //		instr_ptr=UByteP(vecptr);
	}
//DeadCode RJS 17Feb00 //	else instr_ptr+=(sizeof(NEXTVEC)*nopoints);

//Old_Code PD 24Nov99 	DONVEC_PTR dnv_ptr = (DONVEC_PTR )instr_ptr;
//Old_Code PD 24Nov99 	int			j;
//Old_Code PD 24Nov99 	int			vertex;
//Old_Code PD 24Nov99 	int			nopoints;
//Old_Code PD 24Nov99 	NEXTVEC_PTR	vecpoo;
//Old_Code PD 24Nov99 	SLong		intensity;
//Old_Code PD 24Nov99 	SLong		specular;
//Old_Code PD 24Nov99 	SLong		specflip;
//Old_Code PD 24Nov99 
//Old_Code PD 24Nov99 	vertex = dnv_ptr->vertex;
//Old_Code PD 24Nov99 	nopoints = dnv_ptr->count;
//Old_Code PD 24Nov99 
//Old_Code PD 24Nov99 	instr_ptr += sizeof(DONVEC);
//Old_Code PD 24Nov99 
//Old_Code PD 24Nov99 	if (View_Point->isLightShaded)								//RJS 06May98
//Old_Code PD 24Nov99 	{
//Old_Code PD 24Nov99 		IFShare& li=TransLightVector.ni;
//Old_Code PD 24Nov99 		IFShare& lj=TransLightVector.nj;
//Old_Code PD 24Nov99 		IFShare& lk=TransLightVector.nk;
//Old_Code PD 24Nov99 
//Old_Code PD 24Nov99 		for (j = 0; j < nopoints; j++)
//Old_Code PD 24Nov99 		{
//Old_Code PD 24Nov99 			vecpoo = (NEXTVEC_PTR) instr_ptr;
//Old_Code PD 24Nov99 
//Old_Code PD 24Nov99 			Float an=vecpoo->an;
//Old_Code PD 24Nov99 			Float bn=vecpoo->bn;
//Old_Code PD 24Nov99 			Float cn=vecpoo->cn;
//Old_Code PD 24Nov99 
//Old_Code PD 24Nov99 			double mag=an*an+bn*bn+cn*cn;
//Old_Code PD 24Nov99 
//Old_Code PD 24Nov99 			_asm {	fld mag;
//Old_Code PD 24Nov99 					fsqrt;
//Old_Code PD 24Nov99 					fstp mag;
//Old_Code PD 24Nov99 			}
//Old_Code PD 24Nov99 
//Old_Code PD 24Nov99 			an/=mag; bn/=mag; cn/=mag;
//Old_Code PD 24Nov99 
//Old_Code PD 24Nov99 			Float fintensity=li.f*an+lj.f*bn+lk.f*cn;
//Old_Code PD 24Nov99 
//Old_Code PD 24Nov99 			if (specularEnabled)
//Old_Code PD 24Nov99 			{
//Old_Code PD 24Nov99 			 	IFShare& vi=TransViewVector.ni;
//Old_Code PD 24Nov99 		 		IFShare& vj=TransViewVector.nj;
//Old_Code PD 24Nov99 			 	IFShare& vk=TransViewVector.nk;
//Old_Code PD 24Nov99 				double fspecular=vi.f*an+vj.f*bn+vk.f*cn;
//Old_Code PD 24Nov99 				calcSpecular(fspecular,fintensity,specular,specflip);
//Old_Code PD 24Nov99 			}
//Old_Code PD 24Nov99 			else specular=specflip=-1;
//Old_Code PD 24Nov99 
//Old_Code PD 24Nov99 			fintensity*=Float(32385);
//Old_Code PD 24Nov99 
//Old_Code PD 24Nov99 			intensity = fintensity;
//Old_Code PD 24Nov99 			intensity+=32385;	//range is (-127 * 255) to (127 * 255) (ie. -32385 to 32385)
//Old_Code PD 24Nov99 			intensity /= 232;											//RJS 23Apr98
//Old_Code PD 24Nov99 			intensity = 280 - intensity;								//RJS 20Mar98
//Old_Code PD 24Nov99 			if (intensity > 256)										//RJS 20Mar98
//Old_Code PD 24Nov99 				intensity = 256;										//RJS 20Mar98
//Old_Code PD 24Nov99 
//Old_Code PD 24Nov99 			if (intensity<0) intensity=0;
//Old_Code PD 24Nov99 		
//Old_Code PD 24Nov99 			newco[vertex].intensity = intensity;					//RJS 20Mar98
//Old_Code PD 24Nov99 			newco[vertex].specular = specular;					//PD 24Aug98
//Old_Code PD 24Nov99 			newco[vertex].specFlip = specflip;					//PD 24Aug98
//Old_Code PD 24Nov99 			vertex++;
//Old_Code PD 24Nov99 
//Old_Code PD 24Nov99 			instr_ptr += sizeof(NEXTVEC);
//Old_Code PD 24Nov99 		}
//Old_Code PD 24Nov99 	}
//Old_Code PD 24Nov99 	else
//Old_Code PD 24Nov99 		instr_ptr += (sizeof(NEXTVEC)*nopoints);
//DeadCode RJS 18Nov99 			vecpoo = (NEXTVEC_PTR) instr_ptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		donanimvec
//Author		Robert Slater
//Date			Thu 17 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::donanimvec(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("78");
#endif
	DONANIMVEC_PTR dnv_ptr=(DONANIMVEC_PTR )instr_ptr;
	int			nopoints;
	NEXTVEC_PTR	vecptr;
//DeadCode RJS 19May00 	DoPointStruc*	dp = &newco[dnv_ptr->vertex];
	SWordP			bmat = intAnimMatrixPtr;
	SWordP			m= intSubAnimMatrix; //pitch..
	SLong			x,y,z;
	SLong			nx,ny,nz;
	R3DVALUE 		an,bn,cn,mag;


	nopoints = dnv_ptr->count;

	instr_ptr += sizeof(DONVEC);

	vecptr = (NEXTVEC_PTR) instr_ptr;

	instr_ptr += (sizeof(NEXTVEC)*nopoints);

	if (View_Point->isLightShaded)
	{
		DoPointStruc *vptr=newco+dnv_ptr->vertex;
//DeadCode RJS 23Feb00		NEXTVEC_PTR	vecptr=(NEXTVEC_PTR)instr_ptr;

		for (int j=nopoints;j>0;j--)
		{
			x = vecptr->an;
			y = vecptr->cn;
			z = vecptr->bn;

			ny = (m[4] * y)>>15; // pitch..
			ny += (m[5] * z)>>15;

			nz = (m[7] * y)>>15;
			nz += (m[8] * z)>>15;

// Forward transform...

			y = nz;
			z = ny;

			nx = (bmat[0] * x)>>14;
			nx += (bmat[3] * y)>>14;
			nx += (bmat[6] * z)>>14;

			ny = (bmat[1] * x)>>14;
			ny += (bmat[4] * y)>>14;
			ny += (bmat[7] * z)>>14;

			nz = (bmat[2] * x)>>14;
			nz += (bmat[5] * y)>>14;
			nz += (bmat[8] * z)>>14;


			an=nx;
			bn=ny;
			cn=nz;
			mag=an*an+bn*bn+cn*cn;
			mag=fastMath.FastInvSqrt(mag);
			an*=mag;
			bn*=mag;
			cn*=mag;

#ifndef	_NOPOINTS_
			vptr->setNormal(an,cn,bn);							//RJS 19May00
#endif
			vptr++;
			vecptr++;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donextvec
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::donextvec(UByte *& )								//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("79");
#endif
	_Error.EmitSysErr(__FILE__":Not a real instruction (DONEXTVEC)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	donpoint2x
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
void shape::donpoint2x(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("80");
#endif
	UWord	vertex1,
			vertex2;

	UWord	counter;

	DONPOINT2X_PTR npnt_ptr = (DONPOINT2X_PTR )instr_ptr;

	NNEXT2X_PTR ptr = (NNEXT2X_PTR)(instr_ptr+sizeof(DONPOINT2X));

	vertex1 = (UWord )npnt_ptr->start_vertex;					//RJS 10Mar97
#ifndef	_NOPOINTS_

	for(counter=0;counter<npnt_ptr->count;counter++)
	{
		vertex2=(UWord )(vertex1+ptr->vertex);				//RJS 10Mar97
		{
			DoPointStruc& dp=newco[vertex1];

			dp.setPosition(	ptr->xcoord + object_obj3d->Body.X.f,
							ptr->ycoord + object_obj3d->Body.Y.f,
							ptr->zcoord + object_obj3d->Body.Z.f	);	//RJS 19May00
		}
		{
			DoPointStruc& dp=newco[vertex2];

			dp.setPosition(	-ptr->xcoord + object_obj3d->Body.X.f,
							ptr->ycoord + object_obj3d->Body.Y.f,
							ptr->zcoord + object_obj3d->Body.Z.f	);	//RJS 19May00
		}
		vertex1++;
		ptr++;
	}
#endif
	instr_ptr += npnt_ptr->count * sizeof(NNEXT2X) + sizeof(DONPOINT2X);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		docallshape
//Author		Robert Slater
//Date			Thu 27 Feb 1997
//
//Description	Backs up current important shape information,
//				and processes sub shape as a new shape.
//				Restores old shape information.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::docallshape(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("81");
#endif
//DeadCode RJS 20Oct00 	DOCALLSHAPE_PTR	ptr = (DOCALLSHAPE_PTR) instr_ptr;
	UByteP			instr_bak = instr_ptr;

	DrawSubShape(instr_ptr);

	instr_ptr = instr_bak;
	instr_ptr += sizeof(DOCALLSHAPE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosmokepnt
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dosmokepnt(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("82");
#endif
//DeadCode RJS 17Sep97 	DOSMOKEPNT_PTR	ptr = (DOSMOKEPNT_PTR) instr_ptr;
//DeadCode RJS 17Sep97 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;		//RJS 22May97
//DeadCode RJS 17Sep97 	SWord		*countptr = (SWord*) &adptr[ptr->countoffset];	//RJS 05Jun97
//DeadCode RJS 17Sep97 	SWord		Stores = *countptr;								//RJS 05Jun97
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 	if (	adptr
//DeadCode RJS 17Sep97 		&&	adptr[ptr->flagoffset]
//DeadCode RJS 17Sep97 		&&	!Timer_Code.paused
//DeadCode RJS 17Sep97 		&&	Stores
//DeadCode RJS 17Sep97 		&&	!IsSubShape)										//RJS 03Jun97
//DeadCode RJS 17Sep97 	{
//DeadCode RJS 17Sep97 		int			index = adptr[ptr->flagoffset];				//RJS 22May97
//DeadCode RJS 17Sep97 		SLong		wx, wy, wz;									//RJS 21May97
//DeadCode RJS 17Sep97 		MATRIX  	omat;										//RJS 21May97
//DeadCode RJS 17Sep97 		MATRIX_PTR	obj_matrix = &omat;							//RJS 21May97
//DeadCode RJS 17Sep97 		UWord		scaleback;									//RJS 21May97
//DeadCode RJS 17Sep97 		TrailRecord*	trailptr = &traillist[index];			//RJS 21May97
//DeadCode RJS 17Sep97 		int			lifetime;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 		trailptr->addtime = ptr->LifeTime;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 		// -1 is infinite....
//DeadCode RJS 17Sep97 		if (Stores != -1)
//DeadCode RJS 17Sep97 		{
//DeadCode RJS 17Sep97 			Stores-=16;											//RJS 04Jun97
//DeadCode RJS 17Sep97 		
//DeadCode RJS 17Sep97 			if (Stores < 0)
//DeadCode RJS 17Sep97 				Stores = 0;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			*countptr = Stores;
//DeadCode RJS 17Sep97 		}
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 		if (Stores)
//DeadCode RJS 17Sep97 		{
//DeadCode RJS 17Sep97 			lifetime = ptr->LifeTime;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			if (trailptr->lifetime && (lifetime > 500))
//DeadCode RJS 17Sep97 				lifetime = trailptr->lifetime;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97  			if (trailptr->nextlist)
//DeadCode RJS 17Sep97  			{
//DeadCode RJS 17Sep97  				Coords3DListPtr	nextptr = traillist[trailptr->nextlist].thelist;
//DeadCode RJS 17Sep97  				if (nextptr)
//DeadCode RJS 17Sep97  				{
//DeadCode RJS 17Sep97  					wx = nextptr->trailpoint.gx;
//DeadCode RJS 17Sep97  					wy = nextptr->trailpoint.gy;
//DeadCode RJS 17Sep97  					wz = nextptr->trailpoint.gz;
//DeadCode RJS 17Sep97  
//DeadCode RJS 17Sep97  					SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,lifetime);
//DeadCode RJS 17Sep97  					lifetime = trailptr->lifetime;
//DeadCode RJS 17Sep97  				}
//DeadCode RJS 17Sep97  
//DeadCode RJS 17Sep97  				trailptr->nextlist = 0;
//DeadCode RJS 17Sep97  			}
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			// Every frame....
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			wx = ptr->xcoord << shapescale;
//DeadCode RJS 17Sep97 			wy = ptr->ycoord << shapescale;
//DeadCode RJS 17Sep97 			wz = ptr->zcoord << shapescale;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			_matrix.generate2(	object_obj3d->AngH,
//DeadCode RJS 17Sep97 								object_obj3d->AngC,
//DeadCode RJS 17Sep97 								object_obj3d->AngR,
//DeadCode RJS 17Sep97 								obj_matrix);
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			scaleback = _matrix.transform(obj_matrix,wx,wy,wz);
//DeadCode RJS 17Sep97  			wx >>= (16-scaleback);
//DeadCode RJS 17Sep97  			wy >>= (16-scaleback);
//DeadCode RJS 17Sep97  			wz >>= (16-scaleback);
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			wx += trailptr->lastwx;
//DeadCode RJS 17Sep97 			wy += trailptr->lastwy;
//DeadCode RJS 17Sep97 			wz += trailptr->lastwz;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 			// Reset after approx 128 points.
//DeadCode RJS 17Sep97 			if (trailptr->bitshift == 8)
//DeadCode RJS 17Sep97 			{
//DeadCode RJS 17Sep97 				trailptr->bitshift = 0;
//DeadCode RJS 17Sep97 				trailptr->lifetime = 0;
//DeadCode RJS 17Sep97 				trailptr->addtime = 0;
//DeadCode RJS 17Sep97 				trailptr->nopoints = 0;
//DeadCode RJS 17Sep97 
//DeadCode RJS 17Sep97 				adptr[ptr->flagoffset] = -index;
//DeadCode RJS 17Sep97 				SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,ptr->LifeTime);
//DeadCode RJS 17Sep97 				SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
//DeadCode RJS 17Sep97 			}
//DeadCode RJS 17Sep97 			else
//DeadCode RJS 17Sep97 				SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,lifetime);//RJS 29May97
//DeadCode RJS 17Sep97 		}
//DeadCode RJS 17Sep97 		else
//DeadCode RJS 17Sep97 		{
//DeadCode RJS 17Sep97 			adptr[ptr->flagoffset] = 0;
//DeadCode RJS 17Sep97 			SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
//DeadCode RJS 17Sep97 		}
//DeadCode RJS 17Sep97 	}

	instr_ptr += sizeof(DOSMOKEPNT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dobitsoff
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified		Feb 1997
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
 void shape::dobitsoff(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("83");
#endif
	DOBITSOFF_PTR	dbo_ptr = (DOBITSOFF_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;				//RJS 18Feb97
	UByte	damageflag = GlobalAdptr[dbo_ptr->animoff];					//RJS 18Feb97
	SWord	deadoff = dbo_ptr->deadoffset;//RJS 29AUG98

//DeadCode RJS 13Feb97 	UWordP	dammageflags = (UWordP )(animflags+ACBITSFLAGS);
//DeadCode RJS 13Feb97 
//DeadCode RJS 13Feb97 	UWord	localdamflag = *dammageflags;
//DeadCode RJS 13Feb97 
//DeadCode RJS 13Feb97 	localdamflag >>= dbo_ptr->flag;
//DeadCode RJS 13Feb97 
//DeadCode RJS 13Feb97 	localdamflag &= BS_DEAD;

	instr_ptr += sizeof(DOBITSOFF);

	if (damageflag >= BS_DAMLV1)
	{
		if (damageflag < BS_DAMLV2)
			instr_ptr += dbo_ptr->dam1offset;
		else
		{
			if (damageflag < BS_DEAD)
				instr_ptr += dbo_ptr->dam2offset;
			else
			{
				if ((object_obj3d->copySize == TransientSize) && (deadoff==0))	//RJS 26May00
					deadoff = -1;

				instr_ptr += deadoff;
									//After adding the instruction
									//size at the end of this routine
									//the instruction pointer is left
									//looking at a RETURN instruction.
			}
		}
	}
}

static	ULong	biggestcyl = 0;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doplumepnt
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description	Draws a section of a smoke/vapour/fire trail...
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::doplumepnt(UByte *& instr_ptr)						//PD 13Nov97
{
#ifdef	_PROCDEBUG_
	Bollox("84");
#endif
//	ULongP		lo3dptr = (ULongP) &object_obj3d->AngH;			//RJS 17Sep97
//	Obj3DPtr	lastobj3d = (Obj3DPtr) (*lo3dptr);				//RJS 17Sep97
//	VapAnimDatPtr	vapptr = (VapAnimDatPtr) &object_obj3d->AngR;//RJS 18Sep97
//																//RJS 17Sep97
//	if (lastobj3d && vapptr->radius && !Three_Dee.shapecheat)	//RJS 27Mar98
//	{
//		DOPLUMEPNT_PTR	ptr = (DOPLUMEPNT_PTR) instr_ptr;
//		Coords3DListPtr	adptr = (Coords3DListPtr) object_obj3d->AnimPtr;
//		Coords3DListPtr	lastadptr = (Coords3DListPtr) lastobj3d->AnimPtr;
//		VapAnimDatPtr	oldvapptr = (VapAnimDatPtr) &lastobj3d->AngR;//RJS 18Sep97
//		SByte	fadetype = vapptr->depth;		
//		UWord	frameno = vapptr->frameno;
//		UWord	radius = vapptr->radius<<2;
//		UWord	oldrad = oldvapptr->radius<<2;
//		SLong	minx, miny;
//		SLong	realdist;
//		SLong	rangefix = 32768;
//		Bool	drawsphere;
 //		Bool	justsphere= FALSE;								//RJS 04Mar98
//		UByteP	tmpinstptr;
////		UWord	savebornat = adptr->birthdelta;
//	//	ULong	frameoff = ((ULong)&adptr->birthdelta) - ((ULong)adptr);
	//	SWord	xoff0;
	//	SWord	yoff0;
	//	SWord	xoff1 = adptr->xdelta;
	//	SWord	yoff1 = adptr->ydelta;
//
//		if (oldvapptr->radius)
//		{
//			xoff0 = lastadptr->xdelta;
//			yoff0 = lastadptr->ydelta;
//		}
//		else
//		{
//			oldrad = radius;
//
//			xoff0 = (adptr->xdelta * oldrad)/radius;
//			yoff0 = (adptr->ydelta * oldrad)/radius;
//		}
//
//		newco[0].bodyx.f = lastobj3d->Body.X.f;
//		newco[0].bodyy.f = lastobj3d->Body.Y.f;
//		newco[0].bodyz.f = lastobj3d->Body.Z.f;
//
//		newco[1].bodyx.f = object_obj3d->Body.X.f;
//		newco[1].bodyy.f = object_obj3d->Body.Y.f;
//		newco[1].bodyz.f = object_obj3d->Body.Z.f;
//
//		adptr->birthdelta = frameno;
//
//		realdist = (newco[0].bodyz.f + newco[1].bodyz.f)/2;	//RJS 17Sep97
//		if (ptr->rangefar)
//			rangefix = 218918;
//
//		minx = 0;
//		miny = 0;
//
//		if (realdist < rangefix)
//		{
//			drawsphere = FALSE;
//			fadetype = (fadetype * 255)/7;						//RJS 27Mar98
//			current_screen->SetTransparency(fadetype);			//RJS 27Mar98
//
//			if (ptr->sphereframe && realdist < 70000)
//			{
//				drawsphere = TRUE;
//				if (ptr->justspheres && !justsphere)
//					drawsphere = FALSE;
//				else
//				{
//					if (!fadetype)
//						justsphere = FALSE;
//				}
//			}
//
 //			if (!justsphere || !drawsphere)						//RJS 17Nov97
 //			{													//RJS 17Nov97
  //				SHAPE.imaptrailcyl(	0,							//RJS 17Nov97
  	//								1,							//RJS 17Nov97
  	//								(ImageMapNumber )ptr->imagemap,//RJS 17Nov97
  	 //	 							minx,miny,					//RJS 17Nov97
  	//								ptr->width,ptr->height,		//RJS 17Nov97
  	//								ptr->width,ptr->height,		//RJS 17Nov97
  	//								1,frameoff,					//RJS 17Nov97
  	//								xoff0, yoff0,				//RJS 17Nov97
  	//								xoff1, yoff1);				//RJS 17Nov97
 	//		}													//RJS 17Nov97
 //
//DeadCode RJS 06Feb98  			if (drawsphere)
//DeadCode RJS 06Feb98  			{
//DeadCode RJS 06Feb98  				SWord	mapstart = ptr->height*ptr->sphereframe;
//DeadCode RJS 06Feb98  				SWord	mapend = mapstart+ptr->height;
//DeadCode RJS 06Feb98  
//DeadCode RJS 06Feb98  				SHAPE.imapsphere(1,
//DeadCode RJS 06Feb98  							 	radius,
//DeadCode RJS 06Feb98  							 	(ImageMapNumber )ptr->imagemap,
//DeadCode RJS 06Feb98  							 	minx,mapstart,
//DeadCode RJS 06Feb98  							 	ptr->width,ptr->height,
//DeadCode RJS 06Feb98  							 	0);							//RJS 05Feb98
//DeadCode RJS 06Feb98  			}

// 			dotransparentoff(tmpinstptr);
//			current_screen->SetTransparency(SMOKED_OFF);		//RJS 25Nov97
//		}
//		else
//		{
//			DOLINE	tmpinst2;
//
//			tmpinst2.start_vertex = 0;
//			tmpinst2.end_vertex = 1;
//
//			tmpinstptr = (UByteP) &tmpinst2;
//			doline(tmpinstptr);
//		}
//
//		adptr->birthdelta = savebornat;
//	}
//
	instr_ptr += sizeof(DOPLUMEPNT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doisphere
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	Martin 16 Apr 1996	
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
 void shape::doisphere(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("85");
#endif
	DOISPHERE_PTR 	isphere_ptr = (DOISPHERE_PTR )instr_ptr;			//RJS 05Feb98
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr; 			//RJS 05Feb98
	UWord			frameno = 0;										//RJS 05Feb98
	SWord			stepx,stepy;
	SWord			nofx;
	SWord			minx, maxx;
	SWord			miny, maxy;
	SWord			width, height;
	SWord			imap = isphere_ptr->image;
	SWord			imap2 = isphere_ptr->image2;
	ImageMapDescPtr imptr;
	SWord			oldGlobalAlpha = -1;
	UWord			angle;
	ImageMapNumber	realmap = (ImageMapNumber) imap;
	UByte			fadedepth;// = GlobalAdptr[isphere_ptr->fadeoff];	//RJS 27Nov98

	if (isphere_ptr->fadeoff)							//RJS 15May00
	{
		fadedepth = GlobalAdptr[isphere_ptr->fadeoff];
		if (!fadedepth)
		{
			//The sphere is totally transparent...		
			instr_ptr += sizeof(DOISPHERE);				//RJS 15May00
			return;										//RJS 15May00
		}

		ULong val=ULong(fadedepth);					//RJS 15May00
		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,&val);
		oldGlobalAlpha=SWord(val);
	}

	minx = isphere_ptr->minx;							//RJS 05Feb98
	miny = isphere_ptr->miny;						 	//RJS 05Feb98
	width = isphere_ptr->width;							//RJS 05Feb98
	height = isphere_ptr->height;						//RJS 05Feb98

	if (isphere_ptr->flagoffset)
	{
		frameno = GlobalAdptr[isphere_ptr->flagoffset] / isphere_ptr->animscale;
		if (imap2 && (frameno >= isphere_ptr->framelimit))
		{
			frameno -= isphere_ptr->framelimit;
			realmap = (ImageMapNumber) imap2;
			minx = miny = 0;
		}

		imptr = Image_Map.GetImageMapPtr(realmap);
		nofx = imptr->w / width;						//RJS 05Feb98
														//RJS 05Feb98
		if (nofx)
		{
	 		stepy = frameno / nofx;							//RJS 05Feb98
			stepx = frameno - (stepy*nofx);					//RJS 05Feb98
														//RJS 05Feb98
			minx += stepx * width;							//RJS 05Feb98
			miny += stepy * height;							//RJS 05Feb98
			if (miny >= imptr->h)
				minx = miny = 0;
		}

		if (isphere_ptr->depthoffset && GlobalAdptr[isphere_ptr->depthoffset])
		{
			SLong	depth = GlobalAdptr[isphere_ptr->depthoffset];

			if (isphere_ptr->quadsphere)
			{
				if (oldGlobalAlpha != -1)
					g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,ULong(oldGlobalAlpha));

				ULong val=ULong(depth);
				g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,&val);
				oldGlobalAlpha=val;
			}
//DeadCode RJS 23May00 			g_lpLib3d->SetGlobal(TOGGLE_GLOBALTRANSPARENCY,ULong(SMOKED_SOLID-depth));
//DeadCode RJS 23May00 			depth = 255 - ((depth*255)/LUM_MAX);
//DeadCode RJS 23May00 			g_lpLib3d->SetGlobal(TOGGLE_GLOBALLUMINOSITY,ULong((SMOKED_SOLID-depth*255)>>5));
		}
	}

	maxx = minx + width - 1;							//RJS 17Feb98
	maxy = miny + height;								//RJS 05Feb98

	if (!isphere_ptr->quadsphere)
	{
		SHAPE.imapspherespin(isphere_ptr->vertex,isphere_ptr->radius,realmap,
				minx,miny,maxx,maxy,View_Point->roll);
	}
	else
	{
		g_lpLib3d->DrawQuadSphere(	HMATERIAL(Image_Map.GetImageMapPtr(realmap)),
									newco[isphere_ptr->vertex],
									isphere_ptr->radius,
									ANGLES_0Deg,
									minx,miny,
									maxx,maxy	);
	}

	if (oldGlobalAlpha != -1)
		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,ULong(oldGlobalAlpha));

	instr_ptr += sizeof(DOISPHERE);						//RJS 05Feb98
}

//DeadCode RJS 16Dec97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 16Dec97 //Procedure	dorealisphere
//DeadCode RJS 16Dec97 //------------------------------------------------------------------------------
//DeadCode RJS 16Dec97 //Author		Paul.   
//DeadCode RJS 16Dec97 //Date		Wed 16 Aug 1995
//DeadCode RJS 16Dec97 //Modified	Martin 16 Apr 1996	
//DeadCode RJS 16Dec97 //
//DeadCode RJS 16Dec97 //Description	
//DeadCode RJS 16Dec97 //
//DeadCode RJS 16Dec97 //Inputs	
//DeadCode RJS 16Dec97 //
//DeadCode RJS 16Dec97 //Returns	
//DeadCode RJS 16Dec97 //
//DeadCode RJS 16Dec97 //Externals
//DeadCode RJS 16Dec97 //------------------------------------------------------------------------------
//DeadCode RJS 16Dec97 //------------------------------------------------------------------------------
//DeadCode RJS 16Dec97  void shape::doosphere(UByte *& instr_ptr)
//DeadCode RJS 16Dec97 {
//DeadCode RJS 16Dec97 	DOOSPHERE_PTR osphere_ptr;
//DeadCode RJS 16Dec97 
//DeadCode RJS 16Dec97 	osphere_ptr = (DOOSPHERE_PTR )instr_ptr;
//DeadCode RJS 16Dec97 
//DeadCode RJS 16Dec97 	GREY3DTYPE	gtdt = (GREY3DTYPE )0;							//PD 21Jun96
//DeadCode RJS 16Dec97 
//DeadCode RJS 16Dec97 	SHAPE.omapsphere(osphere_ptr->vertex,osphere_ptr->radius,(ImageMapNumber )osphere_ptr->image,//PD 17Oct96
//DeadCode RJS 16Dec97 					osphere_ptr->minx,osphere_ptr->miny,osphere_ptr->maxx,osphere_ptr->maxy,osphere_ptr->width,osphere_ptr->height,
//DeadCode RJS 16Dec97 					osphere_ptr->factor,
//DeadCode RJS 16Dec97 					osphere_ptr->flagoffset);					//RJS 19Feb97
//DeadCode RJS 16Dec97 	
//DeadCode RJS 16Dec97 	instr_ptr += sizeof(DOOSPHERE);
//DeadCode RJS 16Dec97 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dorealisphere
//Author		Robert Slater
//Date			Tue 16 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::dorealisphere(UByteP	&instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("86");
#endif
//DeadCode RJS 20Oct00 	DOREALISPHERE_PTR	ptr = (DOREALISPHERE_PTR) instr_ptr;	//RJS 14Jan98

//DEADCODE JON 4/12/00 	SHAPE.RealImapSphere(	ptr->vertex,
//DEADCODE JON 4/12/00 							ptr->radius,
//DEADCODE JON 4/12/00 							ptr->image,
//DEADCODE JON 4/12/00 							ptr->minix,
//DEADCODE JON 4/12/00 							ptr->miniy,
//DEADCODE JON 4/12/00 							ptr->maxix,
//DEADCODE JON 4/12/00 							ptr->maxiy,
//DEADCODE JON 4/12/00 							ptr->flagoffset,
//DEADCODE JON 4/12/00 							ptr->animfactor	);

	instr_ptr += sizeof(DOREALISPHERE);
}

//------------------------------------------------------------------------------
//Procedure	docreaterpoly
//------------------------------------------------------------------------------
//Author		Martin.   
//Date			Mon 19 Feb 1996
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
 void shape::docreaterpoly(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("87");
#endif
	DOCREATERPOLY_PTR	ptr = (DOCREATERPOLY_PTR)instr_ptr;				//RJS 13Aug98
	SWord				relimage = ptr->imagemap;						//RJS 13Aug98
	SWord				offset = GlobalAdptr[ptr->animoff];
	SWord				scaleoffset = offset / ptr->animscale;

	relimage += scaleoffset;											//RJS 13Aug98

	if (IsAircraft && (current_level>=2))
	{
		ImageMapDescPtr imap=Image_Map.GetImageMapPtr((ImageMapNumber)relimage);
		ULong			ydelta = offset - (scaleoffset * ptr->animscale);
		UByteP			body = imap->body;
		
		if (ydelta)
		{
			ydelta *= (imap->h / ptr->animscale);
			body += (imap->w * ydelta);
		}

		shape::colour=Colour(*body);
		shape::hMaterial=HMATERIAL(shape::colour);
	}
	else 
		shape::hMaterial=HMATERIAL(Image_Map.GetImageMapPtr((ImageMapNumber) relimage));

	instr_ptr += sizeof(DOCREATERPOLY);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dodrawipolys
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dodrawipolys(UByte *& )								//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("88");
#endif
	g_lpLib3d->EndPoly();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	domappoly
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::domappoly(UByte *& )								//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("89");
#endif
	_Error.EmitSysErr(__FILE__":Not a real instruction (DOMAPPOLY)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetmapmap
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dosetmapmap(UByte *& )								//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("90");
#endif
	_Error.EmitSysErr(__FILE__":Not a real instruction (DOMAPPOLY)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	do3dbreak
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::do3dbreak(UByte *& )								//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("91");
#endif
	_Error.EmitSysErr(__FILE__":Not a real instruction (DOMAPPOLY)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	docylinder
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::docylinder(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("92");
#endif
//DeadCode RJS 20Oct00 	DOCYLINDER_PTR	ptr = (DOCYLINDER_PTR )instr_ptr;

//DEADCODE JON 4/12/00 	SHAPE.plaincylinder(ptr->point0,ptr->point1,ptr->radius);

	instr_ptr += sizeof(DOCYLINDER);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dontpoints
//LastModified:	PD 25Jul96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	Martin 8Nov1995	
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
 void shape::dontpoints(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("93");
#endif
	DONTPOINTS_PTR ntp_ptr;
	
	ntp_ptr = (DONTPOINTS_PTR )instr_ptr;

	NEXTT_PTR next_ptr;

	next_ptr = (NEXTT_PTR )(instr_ptr + sizeof(DONTPOINTS));

	//Generate a temporary transformation matrix to rotate the prop( or whatever else it is)

//	FPMATRIX		tmat;

//	FPMATRIX_PTR	tmatp = &tmat;
	R3DMATRIX tmat;
	HMATRIX tmatp=HMATRIX(ULong(&tmat));

	UWord			rpm;										//RJS 02Sep97

	ANGLES	h,p,r;

	h =	p = r = ANGLES_0Deg;									//RJS 03Sep97

	SLong	roll_angle;											//PD 08Mar96

	// RPM value is a 16-bit ROWAN angle
	if (ntp_ptr->flag)											//RJS 02Sep97
	{															//RJS 02Sep97
		if (ntp_ptr->isWord)									//RJS 06Oct98
		{
			UWordP	adptr2 = (UWordP) &GlobalAdptr[ntp_ptr->flag];	//RJS 22Apr99
			rpm = *adptr2;											//RJS 03Sep97
		}
		else
			rpm = GlobalAdptr[ntp_ptr->flag] * 257;//To ROWAN...		//RJS 06Oct98

//		rpm = 2000;	//cludge
	}															//RJS 02Sep97
	else														//RJS 02Sep97
		rpm = ntp_ptr->fixedrpm;								//RJS 03Sep97

	if (rpm)
	{

		if (!ntp_ptr->notrpm)									//RJS 03Sep97
		{														//RJS 03Sep97
			if (rpm > 750)
			{
				rpm = 30;
				if (rpm < 1500)
					rpm += (((1500-rpm)*720)/750);
			}

			Float	fRollAngle = REV_PER_MIN * Float(rpm) * Float(globalanimtime.centisec);
			ULong	uroll = fastMath.DoubleToULong(fRollAngle);

			roll_angle = SLong(uroll);									//RJS 26Oct00
//DeadCode RJS 26Oct00 			fastMath.FloatToInt(&roll_angle,float(fRollAngle));

//DeadCode RJS 29Mar00 			roll_angle = (ANGLES_359Deg * rpm)/120;				//RJS 16Feb99
//DeadCode RJS 29Mar00 			roll_angle *= globalanimtime.centisec;				//RJS 03Sep97
//DeadCode RJS 29Mar00  			roll_angle /= 1000;									//RJS 03Sep97slowitdown
		}														//RJS 03Sep97
		else													//RJS 03Sep97
			roll_angle = rpm;									//RJS 03Sep97

		switch (ntp_ptr->hpr_data)									//RJS 03Sep97
		{															//RJS 03Sep97
			case 1:													//RJS 03Sep97
				h = (Angles )roll_angle;							//PD 13Nov97
				break;												//RJS 03Sep97
			case 2:													//RJS 03Sep97
				p = (Angles )roll_angle;							//PD 13Nov97
				break;												//RJS 03Sep97
			case 4:													//RJS 03Sep97
				r = (Angles )roll_angle;							//PD 13Nov97
				break;												//RJS 03Sep97
		}															//RJS 03Sep97
	}

	g_lpLib3d->LoadIdentity(tmatp);
	g_lpLib3d->Rotate(tmatp,AXIS_HEADING,(Angles)(int)h);
	g_lpLib3d->Rotate(tmatp,AXIS_PITCH,(Angles)(int)p);
	g_lpLib3d->Rotate(tmatp,AXIS_ROLL,(Angles)-(int)r);

	SWord	vertex = ntp_ptr->start_vertex;						//RJS 10Mar97

	SLong	basex,basey,basez;		//origin to rotate around

	basex = ntp_ptr->base_x;						//PD 08Mar96
	basey = ntp_ptr->base_y;						//PD 08Mar96
	basez = ntp_ptr->base_z;						//PD 08Mar96

	D3DVECTOR	t;
	t.dvX=basex;												//RJS 19May00
	t.dvY=basey;												//RJS 19May00
	t.dvZ=basez;												//RJS 19May00

	g_lpLib3d->Translate(tmatp,t);								//RJS 19May00

	int	j = (int )ntp_ptr->count;
#ifndef	_NOPOINTS_

	while(j--)
	{
		R3DVALUE mag;
//DeadCode RJS 19May00 		DoPointStruc v;

		newco[vertex].setPosition(	next_ptr->xcoord-basex,
									next_ptr->ycoord-basey,
									next_ptr->zcoord-basez	);
		
		//Transform the point around the selected origin
		g_lpLib3d->Transform(tmatp,newco[vertex]);

//DeadCode RJS 19May00 		//Scale back to cm units and add the base coordinates back on//PD 08Mar96
//DeadCode RJS 19May00 		v.bodyx.f+=basex;
//DeadCode RJS 19May00 		v.bodyy.f+=basey;
//DeadCode RJS 19May00 		v.bodyz.f+=basez;

//DeadCode RJS 19May00 		newco[vertex++]=v;
		vertex++;
		next_ptr++;
	}
#endif
	instr_ptr += ntp_ptr->count * sizeof(NEXTT) + sizeof(DONTPOINTS);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetmapoff
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dosetmapoff(UByte *& )								//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("94");
#endif
	//Empty
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetmappingplaner
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dosetmappingplaner(UByte *& )						//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("95");
#endif
	//Empty
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetmappingtan
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dosetmappingtan(UByte *& )							//PD 29Nov95
{
#ifdef	_PROCDEBUG_
	Bollox("96");
#endif
	//Empty
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosmktrail
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
//Modified	
//
//Description			Draws an image-mapped trail of cylinders from a list
//				of points.  The trail is transparent if you are looking upwards
//			 	towards the sky, or if you are above the clouds....
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
 void shape::dosmktrail(UByte *& instr_ptr)						//RJS 20Sep96
{
#ifdef	_PROCDEBUG_
	Bollox("97");
#endif
//Old_Code RJS 08Feb00 	ULongP			lo3dptr = (ULongP) &object_obj3d->AngH;
//Old_Code RJS 08Feb00 	Obj3DPtr		lastobj3d = (Obj3DPtr) (*lo3dptr);		//RJS 07Feb00
//Old_Code RJS 08Feb00 	VapAnimDatPtr	vapptr = (VapAnimDatPtr) &object_obj3d->AngR;
//Old_Code RJS 08Feb00 											
//Old_Code RJS 08Feb00 	if (lastobj3d && vapptr->drawit && !Three_Dee.shapecheat)	//RJS 15Apr98
//Old_Code RJS 08Feb00 	{
//Old_Code RJS 08Feb00 		if (	(object_obj3d->objtype == SMOKE_OBJECT)			//RJS 05Nov99
//Old_Code RJS 08Feb00 			&&	(lastobj3d->objtype == SMOKE_OBJECT)	)		//RJS 05Nov99
//Old_Code RJS 08Feb00 		{
//Old_Code RJS 08Feb00 			DOSMKTRAIL_PTR	ptr = (DOSMKTRAIL_PTR) instr_ptr;
//Old_Code RJS 08Feb00 			Coords3DList*	adptr = (Coords3DList*) object_obj3d->AnimPtr;
//Old_Code RJS 08Feb00 			Coords3DList*	lastadptr = (Coords3DList*) lastobj3d->AnimPtr;
//Old_Code RJS 08Feb00 			VapAnimDatPtr	oldvapptr = (VapAnimDatPtr) &lastobj3d->AngR;
//Old_Code RJS 08Feb00  			SWord	fadetype = vapptr->depth;
//Old_Code RJS 08Feb00 			UWord	radius = adptr->radius;							//RJS 15Apr98
//Old_Code RJS 08Feb00 			UWord	oldrad = lastadptr->radius;						//RJS 15Apr98
//Old_Code RJS 08Feb00 			SLong	realdist;
//Old_Code RJS 08Feb00 			UByteP	tmpinstptr;
//Old_Code RJS 08Feb00 			SWord	xoff0;
//Old_Code RJS 08Feb00 			SWord	yoff0;
//Old_Code RJS 08Feb00 			SWord	xoff1 = adptr->xdelta;
//Old_Code RJS 08Feb00 			SWord	yoff1 = adptr->ydelta;
//Old_Code RJS 08Feb00 			MyGroundVectorPtr	WCylStartP = NULL;					
//Old_Code RJS 08Feb00 			MyGroundVectorPtr	WCylEndP = NULL;					
//Old_Code RJS 08Feb00 			ULong	avdist, avrad;
//Old_Code RJS 08Feb00 			SLong	pixpercyl;
//Old_Code RJS 08Feb00 			SLong	dx, dy, dz;
//Old_Code RJS 08Feb00 			SWord	MaxRadius, Degrade;
//Old_Code RJS 08Feb00  			SWord	ThisDepth = (ptr->MaxTransparency * 255)>>2;	//RJS 27Mar98
//Old_Code RJS 08Feb00 			UWord	FrameNo;
//Old_Code RJS 08Feb00 			SWord	minx, miny;
//Old_Code RJS 08Feb00 			SWord	MaxDepth = 64;
//Old_Code RJS 08Feb00 			ImageMapNumber	theImap;
//Old_Code RJS 08Feb00 			ImageMapNumber	theImap2;
//Old_Code RJS 08Feb00 			SWord	minx2,miny2,maxx2,maxy2;
//Old_Code RJS 08Feb00 			SWord	realfade = fadetype;
//Old_Code RJS 08Feb00 			SLong	fadetime = adptr->LifeTime - adptr->FadeTime;
//Old_Code RJS 08Feb00 			SLong	lifegone = adptr->LifeTime - adptr->lifeleft;
//Old_Code RJS 08Feb00 			SWord	oldGlobalAlpha = -1;
//Old_Code RJS 08Feb00 			UWord	noframes = ptr->noframes - 1;
//Old_Code RJS 08Feb00 			Bool	nocyl = FALSE;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 	//DeadCode DAW 21Jun99 #ifndef NDEBUG
//Old_Code RJS 08Feb00 	//DeadCode DAW 21Jun99 		if (!radius || !fadetime)
//Old_Code RJS 08Feb00 	//DeadCode DAW 21Jun99 			INT3;
//Old_Code RJS 08Feb00 	//DeadCode DAW 21Jun99 #endif
//Old_Code RJS 08Feb00 			if (radius && fadetime>0)									//RJS 09Jul99
//Old_Code RJS 08Feb00 			{
//Old_Code RJS 08Feb00 				if (lifegone > adptr->FadeTime)
//Old_Code RJS 08Feb00 				{
//Old_Code RJS 08Feb00 					lifegone -= adptr->FadeTime;
//Old_Code RJS 08Feb00 					if (lifegone<0) lifegone=0;
//Old_Code RJS 08Feb00 					realfade = (lifegone * fadetype)/fadetime;
//Old_Code RJS 08Feb00 					realfade = fadetype - realfade;
//Old_Code RJS 08Feb00 					if (realfade < 0)
//Old_Code RJS 08Feb00 						realfade = 0;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					if (realfade > 255)
//Old_Code RJS 08Feb00 						realfade = 255;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,realfade);
//Old_Code RJS 08Feb00 					ThisDepth = realfade;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					FrameNo = noframes*lifegone;
//Old_Code RJS 08Feb00 					FrameNo /= fadetime;
//Old_Code RJS 08Feb00 				}
//Old_Code RJS 08Feb00 				else
//Old_Code RJS 08Feb00 				{
//Old_Code RJS 08Feb00 					if (lifegone < 0)							//RJS 05Nov99
//Old_Code RJS 08Feb00 						lifegone=0;								//RJS 05Nov99
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 //DeadCode RJS 05Nov99 					lifegone=0;
//Old_Code RJS 08Feb00 					ThisDepth = fadetype;								//MS 10Dec98
//Old_Code RJS 08Feb00 					g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,ThisDepth);
//Old_Code RJS 08Feb00 					if (ptr->frametime)
//Old_Code RJS 08Feb00 					{
//Old_Code RJS 08Feb00 						UWord	framepoo = lifegone / ptr->frametime;
//Old_Code RJS 08Feb00 						ULong	frametot = framepoo * ptr->frametime;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 						FrameNo = ((lifegone - frametot)*noframes)/ptr->frametime;
//Old_Code RJS 08Feb00 					}
//Old_Code RJS 08Feb00 					else
//Old_Code RJS 08Feb00 						FrameNo = 0;
//Old_Code RJS 08Feb00 				}
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 				Float	fxoff,fyoff;									//RJS 03Dec98
//Old_Code RJS 08Feb00 																		//RJS 03Dec98
//Old_Code RJS 08Feb00 				if (oldvapptr->drawit)									//RJS 15Apr98
//Old_Code RJS 08Feb00 				{
//Old_Code RJS 08Feb00 					xoff0 = lastadptr->xdelta;
//Old_Code RJS 08Feb00 					yoff0 = lastadptr->ydelta;
//Old_Code RJS 08Feb00 				}
//Old_Code RJS 08Feb00 				else
//Old_Code RJS 08Feb00 				{
//Old_Code RJS 08Feb00 					MaxDepth = 96;
//Old_Code RJS 08Feb00 					xoff0 = (xoff1 * oldrad)/radius;					//RJS 03Dec98
//Old_Code RJS 08Feb00 					yoff0 = (yoff1 * oldrad)/radius;					//RJS 03Dec98
//Old_Code RJS 08Feb00 				}
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 				fxoff = xoff1;											//RJS 03Dec98
//Old_Code RJS 08Feb00 				fxoff *= SHAPE.SphereXScale;							//RJS 03Dec98
//Old_Code RJS 08Feb00 																		//RJS 03Dec98
//Old_Code RJS 08Feb00 				fyoff = yoff1;											//RJS 03Dec98
//Old_Code RJS 08Feb00 				fyoff *= SHAPE.SphereYScale;							//RJS 03Dec98
//Old_Code RJS 08Feb00 																		//RJS 03Dec98
//Old_Code RJS 08Feb00 				xoff1 = SWord(fxoff);									//RJS 03Dec98
//Old_Code RJS 08Feb00 				yoff1 = SWord(fyoff);									//RJS 03Dec98
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 				fxoff = xoff0;											//RJS 03Dec98
//Old_Code RJS 08Feb00 				fxoff *= SHAPE.SphereXScale;							//RJS 03Dec98
//Old_Code RJS 08Feb00 																		//RJS 03Dec98
//Old_Code RJS 08Feb00 				fyoff = yoff0;											//RJS 03Dec98
//Old_Code RJS 08Feb00 				fyoff *= SHAPE.SphereYScale;							//RJS 03Dec98
//Old_Code RJS 08Feb00 																		//RJS 03Dec98
//Old_Code RJS 08Feb00 				xoff0 = SWord(fxoff);									//RJS 03Dec98
//Old_Code RJS 08Feb00 				yoff0 = SWord(fyoff);									//RJS 03Dec98
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 				if (	((xoff1 < 0) && (xoff0 > 0))
//Old_Code RJS 08Feb00 					||	((xoff1 > 0) && (xoff0 < 0))	)
//Old_Code RJS 08Feb00 					xoff0 = -xoff0;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 				if (	((yoff1 < 0) && (yoff0 > 0))
//Old_Code RJS 08Feb00 					||	((yoff1 > 0) && (yoff0 < 0))	)
//Old_Code RJS 08Feb00 					yoff0 = -yoff0;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 				WCylStartP = &lastadptr->trailpoint;					
//Old_Code RJS 08Feb00 				WCylEndP = &adptr->trailpoint;							
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 				newco[0].bodyx.f = lastobj3d->Body.X.f;
//Old_Code RJS 08Feb00 				newco[0].bodyy.f = lastobj3d->Body.Y.f;
//Old_Code RJS 08Feb00 				newco[0].bodyz.f = lastobj3d->Body.Z.f;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 				newco[1].bodyx.f = object_obj3d->Body.X.f;
//Old_Code RJS 08Feb00 				newco[1].bodyy.f = object_obj3d->Body.Y.f;
//Old_Code RJS 08Feb00 				newco[1].bodyz.f = object_obj3d->Body.Z.f;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 				// if it is clipped... distance is different
//Old_Code RJS 08Feb00 				SLong	rz0 = newco[0].bodyz.f;							//RJS 06Dec98
//Old_Code RJS 08Feb00 				SLong	rz1 = newco[1].bodyz.f;							//RJS 06Dec98
//Old_Code RJS 08Feb00 																		//RJS 06Dec98
//Old_Code RJS 08Feb00 				if (rz0 < 1)											//RJS 06Dec98
//Old_Code RJS 08Feb00 					rz0 = 1;											//RJS 06Dec98
//Old_Code RJS 08Feb00 																		//RJS 06Dec98
//Old_Code RJS 08Feb00 				if (rz1 < 1)											//RJS 06Dec98
//Old_Code RJS 08Feb00 					rz1 = 1;											//RJS 06Dec98
//Old_Code RJS 08Feb00 																		//RJS 06Dec98
//Old_Code RJS 08Feb00 				realdist = (rz0 + rz1)>>1;								//RJS 06Dec98
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 				if (realdist < ptr->FadeDist)
//Old_Code RJS 08Feb00 				{
//Old_Code RJS 08Feb00 					DoPointStruc	dpoint0,dpoint1;
//Old_Code RJS 08Feb00 					SLong			opp , adj;
//Old_Code RJS 08Feb00 					SLong			prad0,prad1;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					dpoint0 = newco[0];
//Old_Code RJS 08Feb00 					dpoint1 = newco[1];
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					minx = 0;
//Old_Code RJS 08Feb00 					miny = 0;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					R3DVALUE screenx0,screeny0,screenz0,screenx1,screeny1,screenz1;//RJS 07Feb00
//Old_Code RJS 08Feb00 					g_lpLib3d->BodyToScreen(newco[0],screenx0,screeny0,screenz0);//RJS 07Feb00
//Old_Code RJS 08Feb00 					g_lpLib3d->BodyToScreen(newco[1],screenx1,screeny1,screenz1);//RJS 07Feb00
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					opp = (screeny1 - screeny0);
//Old_Code RJS 08Feb00 					adj = (screenx1 - screenx0);
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					dpoint0.bodyx.f += oldrad;
//Old_Code RJS 08Feb00 					dpoint1.bodyx.f += radius;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					R3DVALUE sxdp0,sydp0,szdp0,sxdp1,sydp1,szdp1;//RJS 07Feb00
//Old_Code RJS 08Feb00 					g_lpLib3d->BodyToScreen(dpoint0,sxdp0,sydp0,szdp0);//RJS 07Feb00
//Old_Code RJS 08Feb00 					g_lpLib3d->BodyToScreen(dpoint1,sxdp1,sydp1,szdp1);//RJS 07Feb00
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					prad1 = (sxdp1 - screenx1);
//Old_Code RJS 08Feb00 					prad0 = (sxdp0 - screenx0);
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					avrad = (prad1+prad0)>>1;
//Old_Code RJS 08Feb00 					if (!avrad)
//Old_Code RJS 08Feb00 						avrad = 1;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					opp = (opp<0)?-opp:opp;
//Old_Code RJS 08Feb00 					adj = (adj<0)?-adj:adj;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					avdist = (3*(opp+adj))>>2;
//Old_Code RJS 08Feb00 					if (!avdist)
//Old_Code RJS 08Feb00 						avdist = 1;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 		//DeadCode RJS 24Nov98 			fadetype = SMOKED_SOLID - fadetype;
//Old_Code RJS 08Feb00 		//DeadCode RJS 24Nov98 			ThisDepth -= fadetype;
//Old_Code RJS 08Feb00 		//DeadCode RJS 24Nov98 			if (ThisDepth < SMOKED_LIGHT)
//Old_Code RJS 08Feb00 		//DeadCode RJS 24Nov98 			{
//Old_Code RJS 08Feb00 		//DeadCode RJS 24Nov98 				Degrade = ((SMOKED_LIGHT - ThisDepth) / 63)+1;	//RJS 27Mar98
//Old_Code RJS 08Feb00 		//DeadCode RJS 24Nov98 				ThisDepth = SMOKED_LIGHT;
//Old_Code RJS 08Feb00 		//DeadCode RJS 24Nov98 				avdist /= Degrade;
//Old_Code RJS 08Feb00 		//DeadCode RJS 24Nov98 			}
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					theImap = (ImageMapNumber) ptr->Imagemap;
//Old_Code RJS 08Feb00 					theImap2 = (ImageMapNumber) ptr->Imagemap2;
//Old_Code RJS 08Feb00 					if (theImap)							//RJS 29Jun99
//Old_Code RJS 08Feb00 					{
//Old_Code RJS 08Feb00 						ImageMapDescPtr imptr;
//Old_Code RJS 08Feb00 						SLong			nofx;
//Old_Code RJS 08Feb00 						SLong			stepy, stepx;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 						if (theImap2)
//Old_Code RJS 08Feb00 						{
//Old_Code RJS 08Feb00 							imptr = Image_Map.GetImageMapPtr(theImap2);
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 							nofx = imptr->w / ptr->width2;
//Old_Code RJS 08Feb00 							stepy = FrameNo / nofx;
//Old_Code RJS 08Feb00 							stepx = FrameNo - (stepy*nofx);
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 							minx2 = ptr->minix2;
//Old_Code RJS 08Feb00 							miny2 = ptr->miniy2;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 							minx2 += stepx*ptr->width2;
//Old_Code RJS 08Feb00 							miny2 += stepy*ptr->height2;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 							maxx2 = minx2 + ptr->width2;
//Old_Code RJS 08Feb00 							maxy2 = miny2 + ptr->height2;
//Old_Code RJS 08Feb00 						}
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 						if (ptr->framelimit && (FrameNo >= ptr->framelimit))
//Old_Code RJS 08Feb00 						{
//Old_Code RJS 08Feb00 							SWord	framefrac = FrameNo / ptr->framelimit;
//Old_Code RJS 08Feb00 							SWord	framestep = framefrac * ptr->framelimit;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 							FrameNo -= framestep;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 							minx = 0;
//Old_Code RJS 08Feb00 							miny = 0;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 							theImap = (ImageMapNumber) (ptr->Imagemap + framefrac);
//Old_Code RJS 08Feb00 						}
//Old_Code RJS 08Feb00 						else
//Old_Code RJS 08Feb00 						{
//Old_Code RJS 08Feb00 							minx = ptr->MinIx;
//Old_Code RJS 08Feb00 							miny = ptr->MinIy;
//Old_Code RJS 08Feb00 						}
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 						imptr = Image_Map.GetImageMapPtr(theImap);
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 						nofx = imptr->w / ptr->Width;
//Old_Code RJS 08Feb00 						stepy = FrameNo / nofx;
//Old_Code RJS 08Feb00 						stepx = FrameNo - (stepy*nofx);
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 						minx += stepx*ptr->Width;
//Old_Code RJS 08Feb00 						miny += stepy*ptr->Height;
//Old_Code RJS 08Feb00 					}
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 					switch (ptr->TrailType)
//Old_Code RJS 08Feb00 					{
//Old_Code RJS 08Feb00 						case SMK_SCATTER:
//Old_Code RJS 08Feb00 						{
//Old_Code RJS 08Feb00 							MaxRadius = (7*oldrad)>>3;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 							pixpercyl = (avdist * avrad)>>5;
//Old_Code RJS 08Feb00 							pixpercyl += 8;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00  							if (pixpercyl > MaxDepth)								//RJS 31Mar98
//Old_Code RJS 08Feb00  								pixpercyl = MaxDepth;								//RJS 31Mar98
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 							pixpercyl = (pixpercyl * ThisDepth)/100;
//Old_Code RJS 08Feb00 							pixpercyl = (pixpercyl*ptr->Density)>>7;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 		//DeadCode RJS 29Jun99 					if (doingHW3D)								//PD 19Jun98
//Old_Code RJS 08Feb00 	 							SHAPE.ParticleCylinderImapd(0,1,
//Old_Code RJS 08Feb00  															xoff0,yoff0,
//Old_Code RJS 08Feb00  															xoff1,yoff1,
//Old_Code RJS 08Feb00  															pixpercyl,MaxRadius,
//Old_Code RJS 08Feb00  															WCylStartP, WCylEndP,
//Old_Code RJS 08Feb00  															ptr->Imagemap,
//Old_Code RJS 08Feb00 															minx,miny,
//Old_Code RJS 08Feb00  															ptr->Width, ptr->Height,
//Old_Code RJS 08Feb00 		 													ThisDepth);
//Old_Code RJS 08Feb00 		//DeadCode DAW 30Jun99 					else
//Old_Code RJS 08Feb00 		//DeadCode DAW 30Jun99 						SHAPE.ParticleCylinderPlain(0,1,
//Old_Code RJS 08Feb00 		//DeadCode DAW 30Jun99  													xoff0,yoff0,
//Old_Code RJS 08Feb00 		//DeadCode DAW 30Jun99  													xoff1,yoff1,
//Old_Code RJS 08Feb00 		//DeadCode DAW 30Jun99  													pixpercyl,MaxRadius,
//Old_Code RJS 08Feb00 		//DeadCode DAW 30Jun99  													WCylStartP, WCylEndP,
//Old_Code RJS 08Feb00 		//DeadCode DAW 30Jun99 													ptr->Colour,
//Old_Code RJS 08Feb00 		//DeadCode DAW 30Jun99 		 											ThisDepth);
//Old_Code RJS 08Feb00 						}
//Old_Code RJS 08Feb00 						break;
//Old_Code RJS 08Feb00 						case SMK_STREAM:
//Old_Code RJS 08Feb00 						{
//Old_Code RJS 08Feb00 							SLong	realdist2 = (realdist << 7) / 7500;	//MS 10Dec98
//Old_Code RJS 08Feb00 							if (realdist2 <= 0)
//Old_Code RJS 08Feb00 								realdist2 = 128;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 							if (realdist2 > 65535)
//Old_Code RJS 08Feb00 								realdist2 = 65535;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 							SHAPE.ParticleStreamImapd(	0,1,
//Old_Code RJS 08Feb00 														xoff0,yoff0,
//Old_Code RJS 08Feb00 														xoff1,yoff1,
//Old_Code RJS 08Feb00 														UWord(realdist2),	//RJS 10Dec98
//Old_Code RJS 08Feb00 														oldrad,
//Old_Code RJS 08Feb00 														radius,
//Old_Code RJS 08Feb00 														WCylStartP, WCylEndP,
//Old_Code RJS 08Feb00 														ptr->Imagemap,
//Old_Code RJS 08Feb00 														minx,miny,
//Old_Code RJS 08Feb00 														ptr->Width, ptr->Height,
//Old_Code RJS 08Feb00 														ThisDepth);
//Old_Code RJS 08Feb00 						}
//Old_Code RJS 08Feb00 						break;
//Old_Code RJS 08Feb00 //DeadCode RJS 16Dec99 						case SMK_CLUSTER:
//Old_Code RJS 08Feb00 //DeadCode RJS 16Dec99 						{
//Old_Code RJS 08Feb00 //DeadCode RJS 16Dec99 							SHAPE.FixedPolyOnFloor(adptr,
//Old_Code RJS 08Feb00 //DeadCode RJS 16Dec99 										   		lastadptr,
//Old_Code RJS 08Feb00 //DeadCode RJS 16Dec99 										   		xoff0,yoff0,
//Old_Code RJS 08Feb00 //DeadCode RJS 16Dec99 										   		xoff1,yoff1,
//Old_Code RJS 08Feb00 //DeadCode RJS 16Dec99 										   		theImap,
//Old_Code RJS 08Feb00 //DeadCode RJS 16Dec99 										   		minx,miny,
//Old_Code RJS 08Feb00 //DeadCode RJS 16Dec99 										   		ptr->Width,miny+ptr->Height);
//Old_Code RJS 08Feb00 //DeadCode RJS 16Dec99 						}
//Old_Code RJS 08Feb00 //DeadCode RJS 16Dec99 						break;
//Old_Code RJS 08Feb00 						case SMK_HEAVY_STREAM:
//Old_Code RJS 08Feb00 						{
//Old_Code RJS 08Feb00 							if (realdist < 6000)
//Old_Code RJS 08Feb00 							{
//Old_Code RJS 08Feb00 								MaxRadius = (7*oldrad)>>3;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 								pixpercyl = ThisDepth * ptr->Density;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 	 							SHAPE.ParticleCylinderImapd(0,1,
//Old_Code RJS 08Feb00  															xoff0,yoff0,
//Old_Code RJS 08Feb00  															xoff1,yoff1,
//Old_Code RJS 08Feb00  															pixpercyl,MaxRadius,
//Old_Code RJS 08Feb00  															WCylStartP, WCylEndP,
//Old_Code RJS 08Feb00  															theImap2,
//Old_Code RJS 08Feb00 															minx2,miny2,
//Old_Code RJS 08Feb00  															maxx2 - minx2,maxy2-miny2,
//Old_Code RJS 08Feb00 		 													ThisDepth);
//Old_Code RJS 08Feb00 							}
//Old_Code RJS 08Feb00 							else
//Old_Code RJS 08Feb00 							{
//Old_Code RJS 08Feb00 								SHAPE.imaptrailcylWrapped(	0,						
//Old_Code RJS 08Feb00   															1,				
//Old_Code RJS 08Feb00   															theImap,
//Old_Code RJS 08Feb00 															radius,
//Old_Code RJS 08Feb00   															theImap2,
//Old_Code RJS 08Feb00   	 	 													miny,miny+ptr->Height,			
//Old_Code RJS 08Feb00 		  													xoff0, yoff0,	
//Old_Code RJS 08Feb00   															xoff1, yoff1,
//Old_Code RJS 08Feb00 															minx2,miny2,
//Old_Code RJS 08Feb00 															maxx2,maxy2,
//Old_Code RJS 08Feb00 															nocyl);
//Old_Code RJS 08Feb00 							}
//Old_Code RJS 08Feb00 						}
//Old_Code RJS 08Feb00 						break;
//Old_Code RJS 08Feb00 						case SMK_LINES:
//Old_Code RJS 08Feb00 						{
//Old_Code RJS 08Feb00 							pixpercyl = (32 * ptr->Density)>>7;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 							SHAPE.LineStream(	0,1,
//Old_Code RJS 08Feb00 												xoff0,yoff0,
//Old_Code RJS 08Feb00 												xoff1,yoff1,
//Old_Code RJS 08Feb00 												pixpercyl,
//Old_Code RJS 08Feb00 												oldrad,
//Old_Code RJS 08Feb00 												radius,
//Old_Code RJS 08Feb00 												WCylStartP, WCylEndP,
//Old_Code RJS 08Feb00 												ptr->Colour,
//Old_Code RJS 08Feb00 												ThisDepth);
//Old_Code RJS 08Feb00 						}
//Old_Code RJS 08Feb00 						break;
//Old_Code RJS 08Feb00 						case SMK_FISHPOO:
//Old_Code RJS 08Feb00 						{
//Old_Code RJS 08Feb00 							SHAPE.imaptrailcylWrapped(	0,						
//Old_Code RJS 08Feb00   														1,				
//Old_Code RJS 08Feb00   														theImap,
//Old_Code RJS 08Feb00 														radius,
//Old_Code RJS 08Feb00   														theImap2,
//Old_Code RJS 08Feb00   	 	 												miny,miny+ptr->Height,			
//Old_Code RJS 08Feb00 		  												xoff0, yoff0,	
//Old_Code RJS 08Feb00   														xoff1, yoff1,
//Old_Code RJS 08Feb00 														minx2,miny2,
//Old_Code RJS 08Feb00 														maxx2,maxy2,
//Old_Code RJS 08Feb00 														nocyl);
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 						}
//Old_Code RJS 08Feb00 						break;
//Old_Code RJS 08Feb00 						case SMK_TRACER:
//Old_Code RJS 08Feb00 						break;
//Old_Code RJS 08Feb00 						case SMK_ENGINEFIRE:
//Old_Code RJS 08Feb00 						{
//Old_Code RJS 08Feb00 							if (realdist < 6000)
//Old_Code RJS 08Feb00 							{
//Old_Code RJS 08Feb00 								MaxRadius = (7*oldrad)>>3;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 								pixpercyl = ThisDepth * ptr->Density;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 								if (adptr->isFirst)
//Old_Code RJS 08Feb00 	 								SHAPE.DblParticleCylinderImapd(0,1,
//Old_Code RJS 08Feb00  																xoff0,yoff0,
//Old_Code RJS 08Feb00  																xoff1,yoff1,
//Old_Code RJS 08Feb00  																pixpercyl,MaxRadius,
//Old_Code RJS 08Feb00  																WCylStartP, WCylEndP,
//Old_Code RJS 08Feb00  																theImap2,
//Old_Code RJS 08Feb00 																minx2,miny2,
//Old_Code RJS 08Feb00  																maxx2-minx2,
//Old_Code RJS 08Feb00 																maxy2-miny2,
//Old_Code RJS 08Feb00 																0,0,
//Old_Code RJS 08Feb00  																64,
//Old_Code RJS 08Feb00 																64,
//Old_Code RJS 08Feb00 		 														ThisDepth);
//Old_Code RJS 08Feb00 								else
//Old_Code RJS 08Feb00 									SHAPE.ParticleCylinderImapd(0,1,
//Old_Code RJS 08Feb00  																xoff0,yoff0,
//Old_Code RJS 08Feb00  																xoff1,yoff1,
//Old_Code RJS 08Feb00  																pixpercyl,MaxRadius,
//Old_Code RJS 08Feb00  																WCylStartP, WCylEndP,
//Old_Code RJS 08Feb00  																theImap2,
//Old_Code RJS 08Feb00 																minx2,miny2,
//Old_Code RJS 08Feb00  																maxx2-minx2,
//Old_Code RJS 08Feb00 																maxy2-miny2,
//Old_Code RJS 08Feb00 		 														ThisDepth);
//Old_Code RJS 08Feb00 							}
//Old_Code RJS 08Feb00 							else
//Old_Code RJS 08Feb00 								SHAPE.imaptrailcylWrapped(	0,						
//Old_Code RJS 08Feb00   															1,				
//Old_Code RJS 08Feb00   															theImap,
//Old_Code RJS 08Feb00 															radius,
//Old_Code RJS 08Feb00   															theImap2,
//Old_Code RJS 08Feb00   	 	 													miny,miny+ptr->Height,			
//Old_Code RJS 08Feb00 		  													xoff0, yoff0,	
//Old_Code RJS 08Feb00   															xoff1, yoff1,
//Old_Code RJS 08Feb00 															minx2,miny2,
//Old_Code RJS 08Feb00 															maxx2,maxy2,
//Old_Code RJS 08Feb00 															nocyl);
//Old_Code RJS 08Feb00 						}
//Old_Code RJS 08Feb00 						break;
//Old_Code RJS 08Feb00 						case SMK_CONTRAIL:
//Old_Code RJS 08Feb00 						{
//Old_Code RJS 08Feb00 							if (realdist < 6000)
//Old_Code RJS 08Feb00 							{
//Old_Code RJS 08Feb00 								MaxRadius = (7*oldrad)>>3;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 								pixpercyl = ThisDepth * ptr->Density;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 								if (adptr->isFirst)
//Old_Code RJS 08Feb00 	 								SHAPE.FadeParticleCylinderImapd(0,1,
//Old_Code RJS 08Feb00  																xoff0,yoff0,
//Old_Code RJS 08Feb00  																xoff1,yoff1,
//Old_Code RJS 08Feb00  																pixpercyl,MaxRadius,
//Old_Code RJS 08Feb00  																WCylStartP, WCylEndP,
//Old_Code RJS 08Feb00  																theImap2,
//Old_Code RJS 08Feb00 																minx2,miny2,
//Old_Code RJS 08Feb00  																maxx2-minx2,
//Old_Code RJS 08Feb00 																maxy2-miny2,															
//Old_Code RJS 08Feb00 		 														ThisDepth);
//Old_Code RJS 08Feb00 								else
//Old_Code RJS 08Feb00 									SHAPE.ParticleCylinderImapd(0,1,
//Old_Code RJS 08Feb00  																xoff0,yoff0,
//Old_Code RJS 08Feb00  																xoff1,yoff1,
//Old_Code RJS 08Feb00  																pixpercyl,MaxRadius,
//Old_Code RJS 08Feb00  																WCylStartP, WCylEndP,
//Old_Code RJS 08Feb00  																theImap2,
//Old_Code RJS 08Feb00 																minx2,miny2,
//Old_Code RJS 08Feb00  																maxx2-minx2,
//Old_Code RJS 08Feb00 																maxy2-miny2,
//Old_Code RJS 08Feb00 		 														ThisDepth);
//Old_Code RJS 08Feb00 							}
//Old_Code RJS 08Feb00 							else
//Old_Code RJS 08Feb00 								SHAPE.imaptrailcylWrapped(	0,						
//Old_Code RJS 08Feb00   															1,				
//Old_Code RJS 08Feb00   															theImap,
//Old_Code RJS 08Feb00 															radius,
//Old_Code RJS 08Feb00   															theImap2,
//Old_Code RJS 08Feb00   	 	 													miny,miny+ptr->Height,			
//Old_Code RJS 08Feb00 		  													xoff0, yoff0,	
//Old_Code RJS 08Feb00   															xoff1, yoff1,
//Old_Code RJS 08Feb00 															minx2,miny2,
//Old_Code RJS 08Feb00 															maxx2,maxy2,
//Old_Code RJS 08Feb00 															nocyl);
//Old_Code RJS 08Feb00 						}
//Old_Code RJS 08Feb00 						break;
//Old_Code RJS 08Feb00 					}
//Old_Code RJS 08Feb00 				}
//Old_Code RJS 08Feb00 				else
//Old_Code RJS 08Feb00 				{
//Old_Code RJS 08Feb00 					if (ptr->Colour)									//MS 10Dec98
//Old_Code RJS 08Feb00 					{
//Old_Code RJS 08Feb00 						DOLINE	tmpinst2;									//RJS 24Nov97
//Old_Code RJS 08Feb00 						DOSETCOLOUR256	tmpinst3;							//RJS 24Nov97
//Old_Code RJS 08Feb00 																			//RJS 24Nov97
//Old_Code RJS 08Feb00 						tmpinst3.basecolour = ptr->Colour<<1;				//RJS 24Nov97
//Old_Code RJS 08Feb00 						tmpinst3.spread = 0;								//RJS 24Nov97
//Old_Code RJS 08Feb00 						tmpinst3.imap = 0xFF;
//Old_Code RJS 08Feb00 																			//RJS 24Nov97
//Old_Code RJS 08Feb00 						tmpinstptr = (UByteP) &tmpinst3;					//RJS 24Nov97
//Old_Code RJS 08Feb00 						dosetcolour256(tmpinstptr);							//RJS 24Nov97
//Old_Code RJS 08Feb00 																			//RJS 24Nov97
//Old_Code RJS 08Feb00 						tmpinst2.start_vertex = 0;							//RJS 24Nov97
//Old_Code RJS 08Feb00 						tmpinst2.end_vertex = 1;							//RJS 24Nov97
//Old_Code RJS 08Feb00 																			//RJS 24Nov97
//Old_Code RJS 08Feb00 						tmpinstptr = (UByteP) &tmpinst2;					//RJS 24Nov97
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 //deadcode 						_matrix.SetClipFlags(newco[0]);						//RJS 27Nov98
//Old_Code RJS 08Feb00  //deadcode						_matrix.SetClipFlags(newco[1]);						//RJS 27Nov98
//Old_Code RJS 08Feb00 																		//MS 10Dec98
//Old_Code RJS 08Feb00 						doline(tmpinstptr);								//MS 10Dec98
//Old_Code RJS 08Feb00 					}													//MS 10Dec98
//Old_Code RJS 08Feb00 				}														//RJS 24Nov97
//Old_Code RJS 08Feb00 				g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,SMOKED_OFF);
//Old_Code RJS 08Feb00 			}
//Old_Code RJS 08Feb00 		}
//Old_Code RJS 08Feb00 	}
#ifndef	_NOPOINTS_

	VapAnimDatPtr	vapptr = (VapAnimDatPtr) &object_obj3d->AngR;

	if (vapptr->drawit && !Three_Dee.shapecheat)
	{
		if (object_obj3d->objtype == SMOKE_OBJECT)
		{
			Coords3DList*		apoint = (Coords3DList*) object_obj3d->AnimPtr;
 			SLong				fadedepth = vapptr->depth;
			MyGroundVectorPtr	WCylStartP = NULL;					
			MyGroundVectorPtr	WCylEndP = NULL;					
			Coords3DList*		lastapoint = NULL;
			Coords3DList*		nextpoint;
			SLong				view_x = object_obj3d->Body.X.i;		//RJS 9Aug00
 			SLong				view_y = object_obj3d->Body.Y.i;		//RJS 9Aug00
 			SLong				view_z = object_obj3d->Body.Z.i;		//RJS 9Aug00
			SLong				dpx, dpy, dpz;
			SLong				reltoviewx, reltoviewy, reltoviewz;
			SLong				degcnt,degrade;
			D3DVECTOR			pos;
			ULong				clipflag0,clipflag1;
			SLong				dist0,dist1;
			SLong				oldradius;

			degrade = 0x7FFFFFFF;
			degcnt = 0;

			WCylStartP = WCylEndP = &apoint->trailpoint;

			reltoviewx = WCylEndP->gx-view_x;
			reltoviewy = WCylEndP->gy-view_y;
			reltoviewz = WCylEndP->gz-view_z;

			pos.x = D3DVALUE(reltoviewx);
			pos.y = D3DVALUE(reltoviewy);
			pos.z = D3DVALUE(reltoviewz);

//DeadCode RJS 7Nov00 			g_lpLib3d->VisibleCheck(&pos,1,&clipflag1);
// fix to see 1st element of trail...
			clipflag1 = 0;												//RJS 7Nov00

			fastMath.FloatToInt(&dist1,fastMath.FastSqrt((pos.x*pos.x)+(pos.y*pos.y)+(pos.z*pos.z)));
			dist0 = dist1;// = D3Distance(reltoviewx,reltoviewy,reltoviewz);
			oldradius = 0;

// Start strip...

			newco[0].setPosition(	reltoviewx,
									reltoviewy,
									reltoviewz	);				//RJS 19May00

			if (apoint->next)
			{
				newco[1].setPosition(	apoint->next->trailpoint.gx - view_x,
										apoint->next->trailpoint.gy - view_y,
										apoint->next->trailpoint.gz - view_z	);//RJS 19May00

				Smoke_Trails.radius = apoint->radius;
				Smoke_Trails.Init();
			}

			while (apoint)
			{
				nextpoint = apoint->next;
				if (!degcnt || !nextpoint)
				{
					if (lastapoint)
					{
						WCylEndP = &apoint->trailpoint;

						newco[0].setPosition(	reltoviewx,
												reltoviewy,
												reltoviewz	);	//RJS 19May00

						reltoviewx = WCylEndP->gx-view_x;
						reltoviewy = WCylEndP->gy-view_y;
						reltoviewz = WCylEndP->gz-view_z;

						pos.x = D3DVALUE(reltoviewx);
						pos.y = D3DVALUE(reltoviewy);
						pos.z = D3DVALUE(reltoviewz);

						fastMath.FloatToInt(&dist1,fastMath.FastSqrt((pos.x*pos.x)+(pos.y*pos.y)+(pos.z*pos.z)));

						g_lpLib3d->VisibleCheck(&pos,1,&clipflag1);

						if ((clipflag0 == 0) || (clipflag1==0))
						{
							newco[1].setPosition(	reltoviewx,
													reltoviewy,
													reltoviewz	);//RJS 19May00

							DoDrawTrail(	instr_ptr,
											apoint,
											WCylStartP,
											WCylEndP,
											fadedepth,
											dist0,
											dist1,
											oldradius	);
						}
					}

					degcnt = dist1 / degrade;

					oldradius = apoint->radius;
					dist0 = dist1;
					clipflag0 = clipflag1;
					WCylStartP = WCylEndP;
				}
				else
					degcnt--;

				lastapoint = apoint;
				apoint = nextpoint;
			}
		}

// End strip...
	}
#endif
	instr_ptr += sizeof(DOSMKTRAIL);
}

// SUN MOVED HERE BECAUSE bOldZState used.
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SunItemAnim
//Author		Paul.   
//Date			Mon 24 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::SunItemAnim(SunAnimData* adptr)
{
#ifdef	_PROCDEBUG_
	Bollox("98");
#endif
#ifndef _NOLENSFLARE_
//DEADCODE RJS 4/20/00 	if (!Three_Dee.lightson)									//RJS 03Jun99
	{
		Float	sunXpos,											//PD 24Jun96
				sunYpos;											//PD 24Jun96
		DoPointStruc	dps,dps2;

		adptr->wasdrawn=TRUE;

		Land_Scape.sun_glare = 0;										//RJS 31Aug00

		if (Land_Scape.strongSun)										//RJS 31Aug00
		{
			//Now, use object_obj3d to fill in the suns screen x and y
			//coordinates used to detect white outs

			dps.setPosition(object_obj3d->Body.X.f,
							object_obj3d->Body.Y.f,
							object_obj3d->Body.Z.f	);
 
			float	origin_x = vd_originx;
			float	origin_y = vd_originy;
			R3DVALUE screenx,screeny,screenz;
			g_lpLib3d->BodyToScreen(dps.getR3DVert(),screenx,screeny,screenz);

			sunXpos = (screenx-origin_x)/origin_x;					//RJS 20Apr00
			sunYpos = (screeny-origin_y)/origin_y;					//RJS 20Apr00

			Land_Scape.sun_screen_x = sunXpos;						//RJS 20Apr00
			Land_Scape.sun_screen_y = sunYpos;						//RJS 20Apr00

// Is the sun on the screen?
			if (	(screenx < float(vd_width))							//RJS 20Apr00
				&&	(screenx > 0)
				&&	(screeny < float(vd_height))
				&&	(screeny > 0)			)
			{
				Float	disx, disy;
				Float	abssunXpos,abssunYpos;
				Float	brightbox = 100;

	// Centre of screen is 0,0
	// Scale distance from centre to 180.3 max
 
				sunXpos *= 180.3;
				sunYpos *= 180.3;

				abssunXpos = sunXpos<0?-sunXpos:sunXpos;
 				abssunYpos = sunYpos<0?-sunYpos:sunYpos;

				disx = abssunXpos;
				disy = abssunYpos;

				if (View_Point && !View_Point->PolyPitEnabled())
				{
					int			i;
					Float		dx, dy, dz;
					Float		dx2, dy2, dz2;
					Float		bdz;
					SLong		fade;
					D3DVECTOR	pos;
					float		fdx,fdy,fdz;

					dps2.setPosition(	object_obj3d->Body.X.f,
										object_obj3d->Body.Y.f,
										object_obj3d->Body.Z.f	);

					g_lpLib3d->Transform(MATRIX_OBJECT,dps2);
					g_lpLib3d->Transform(MATRIX_VIEWER,dps2);

	// Sqrt max should be about 255... in this case, max fade...

					fastMath.FloatToInt(&fade,fastMath.FastSqrt(float(abssunXpos*abssunXpos+abssunYpos*abssunYpos)));

					bdz = 100;

					dps2.getPosition(fdx,fdy,fdz);
					float	rintensity = fastMath.FastInvSqrt(fdx*fdx+fdy*fdy+fdz*fdz);
					
					rintensity *= (100. / 9.);		// nzclip / no of blobs

					fdx *= rintensity;
					fdy *= rintensity;
					fdz *= rintensity;

	// Mid plane = 49 cm z, therefore 1 = 49
	//DeadCode RJS 19Jun00 				dx = object_obj3d->Body.X.f / 10000;
	//DeadCode RJS 19Jun00 				dy = object_obj3d->Body.Y.f / 10000;
	//DeadCode RJS 19Jun00 				dz = object_obj3d->Body.Z.f / 10000;
	//DeadCode RJS 19Jun00 
	//DeadCode RJS 19Jun00 				pos.x = -dx;
	//DeadCode RJS 19Jun00 				pos.y = -dy;
	//DeadCode RJS 19Jun00 				pos.z = bdz-dz;
	//DeadCode RJS 19Jun00 				dps.setPosition(-dx,-dy,bdz - dz);

	//DeadCode RJS 19Jun00 				dx *= .5;
	//DeadCode RJS 19Jun00 				dy *= .5;
	//DeadCode RJS 19Jun00 				dz *= .5;

					dx = fdx;
					dy = fdy;
					dz = fdz;

					pos.x = -fdx*3.;
					pos.y = -fdy*3.;
					pos.z = 100-(fdz*3.);

					dps.setPosition(pos.x,pos.y,pos.z);

					dx2 = dx * 0.1;
					dy2 = dy * 0.1;
					dz2 = dz * 0.1;

					fade = 255 - fade;

					if (Land_Scape.haveSunGlare)						//RJS 19Sep00
						Land_Scape.sun_glare = float(fade)/255.0;		//RJS 19Sep00
					else												//RJS 19Sep00
						Land_Scape.sun_glare = 0;						//RJS 19Sep00

					for (i=0; i < 10; i++)
					{
						switch (i)
						{
						case 0:
							//White...
							Three_Dee.AddLensObject(&dps,LNHALS,0,fade);
							pos.x += dx2;	
							pos.y += dy2;
							pos.z += dz2;
							break;
						case 1:
							//Blue-indigo....
							Three_Dee.AddLensObject(&dps,LNHALB,0,fade);
							pos.x += dx2;	
							pos.y += dy2;
							pos.z += dz2;
							break;
						case 2:
							//Red....
							Three_Dee.AddLensObject(&dps,DUMMY5,0,fade);
							pos.x += dx2;	
							pos.y += dy2;
							pos.z += dz2;
							break;
						case 3:
							//Blue....
							Three_Dee.AddLensObject(&dps,LNSOLS,0,fade);
							pos.x += dx;	
							pos.y += dy;
							pos.z += dz;
							break;
						case 4:
							//White...
							Three_Dee.AddLensObject(&dps,DUMMY4,0,fade);
							pos.x += (dx/2.0);	
							pos.y += (dy/2.0);
							pos.z += (dz/2.0);
							break;
						case 5:
							//Red.....
							Three_Dee.AddLensObject(&dps,LNSOLS,0,fade);
							pos.x += (dx/2.0);	
							pos.y += (dy/2.0);
							pos.z += (dz/2.0);
							break;
						case 6:
							//Orange-yellow
							Three_Dee.AddLensObject(&dps,DUMMY5,0,fade);
							pos.x += dx*2;	
							pos.y += dy*2;
							pos.z += dz*2;
							break;
						case 7:
							//Blue...
							Three_Dee.AddLensObject(&dps,DUMMY5,0,fade);
							pos.x += dx*2;	
							pos.y += dy*2;
							pos.z += dz*2;
							break;
						case 8:
							//More red...
							Three_Dee.AddLensObject(&dps,DUMMY5,0,fade);
							pos.x += dx*2;	
							pos.y += dy*2;
							pos.z += dz*2;
							break;
						}

						dps.setPosition(pos.x,pos.y,pos.z);
					}
				}

 				//Generate the dimensions of a box of screen area
 				//and test to see if the sun lies inside it.
 
	//DeadCode RJS 20Apr00  			const Float VIRTUALBOXSIZE = PIXEL640 * 64;				//PD 04Dec96
 
 				if (abssunXpos<brightbox && abssunYpos<brightbox)
 				{
 					SunInVision = TRUE;
 				}
			}
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dooffsetpnt
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dooffsetpnt(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("99");
#endif
	instr_ptr += sizeof(DOOFFSETPNT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	doicylinder
//------------------------------------------------------------------------------
//Author		Paul.
//Date		Wed 16 Aug 1995
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
 void shape::doicylinder(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("a0");
#endif
	DOICYLINDER_PTR ptr= (DOICYLINDER_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;
	UWord	frameno = 0;
	ImageMapNumber	imap;
	UByte			fadedepth;// = GlobalAdptr[ptr->fadeoff];		//RJS 16Apr99
	SWord			oldGlobalAlpha = -1;						//RJS 27Nov98

	if (ptr->fadeoff)	
	{
		fadedepth = GlobalAdptr[ptr->fadeoff];				//RJS 15May00
		if (!fadedepth)
		{
			instr_ptr += sizeof(DOICYLINDER);
			return;
		}

		ULong val=ULong(fadedepth);
		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,&val);
		oldGlobalAlpha=val;
	}

	if (ptr->flagoffset)
	{
		frameno = GlobalAdptr[ptr->flagoffset] / ptr->factor;
		if (ptr->image2 && (frameno >= ptr->framelimit))
		{
			frameno -= ptr->framelimit;
			imap = (ImageMapNumber) ptr->image2;
		}
		else
			imap = (ImageMapNumber) ptr->image;
	}
	else
		imap = (ImageMapNumber) ptr->image;

	SHAPE.imapcylinder(	ptr->point0,
						ptr->point1,
						ptr->radius,
						imap,
					   	ptr->min_ix,ptr->min_iy,
					  	ptr->width,ptr->height,
						frameno,
						0	);   // trans depth					//RJS 20Nov98

	if (oldGlobalAlpha > -1)									//RJS 27Nov98
		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,ULong(oldGlobalAlpha));

	instr_ptr += sizeof(DOICYLINDER);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drawbetween
//LastModified:	PD 07May96
//Author		Martin Alderton
//Date			Tue 28 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::drawbetween(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("a1");
#endif
	DRAWBETWEEN_PTR ptr;

	ptr = (DRAWBETWEEN_PTR) instr_ptr;

	SLong dist;													//PD 07May96

	fastMath.FloatToInt(&dist,float(object_obj3d->realbz.f*DistScale));	//RJS 23Mar00
//hack 	dist = SLong(object_obj3d->Body.Z.f * DistScale);			//RJS 21Dec99
//DeadCode RJS 07Feb00 	dist = SLong(object_obj3d->Body.Z.f * DistScale);			//RJS 21Dec99

	if ((dist >= ptr->mindist)&& (dist < ptr->maxdist))
	{
//		if (!IsSubShape) current_level++;
		instr_ptr += (UWord )ptr->offset;						//RJS 19Mar97
	}
	else
	{
		if (!IsSubShape) current_level++;
		instr_ptr += sizeof(DRAWBETWEEN);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dolauncher
//Author		Paul.   
//Date			Wed 10 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dolauncher(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("a2");
#endif
	instr_ptr += sizeof(DOLAUNCHER);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dodial
//Author		Robert Slater
//Date			Thu 12 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dodial(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("a3");
#endif
	DODIAL_PTR	ptr = (DODIAL_PTR )instr_ptr;
	SLong		cx,cy,cz;										//RJS 19May00
	SLong		radius;						
	SLong		tipx,tipy,tipz;									//RJS 19May00
	SWord		ex,ey;
	SLong		xpos2,ypos2,zpos2;								//RJS 19May00
	SLong		xpos3,ypos3,zpos3;
	SWord		sin_ang,cos_ang,radius2;
	SLong		flag=0;
	SLong		arc;
	SWord		totalangle = ptr->startangle;
	UWord		flagsize = ptr->flagsize;					//RJS 10Feb98

	switch (flagsize)										//RJS 10Feb98
	{
		case 8:
			flag = GlobalAdptr[ptr->animflag];
			break;
		case 16:
			flag = *((SWordP)&GlobalAdptr[ptr->animflag]);
			flagsize--;										//RJS 10Feb98
			break;
		case 32:
			flag = *((SLongP)&GlobalAdptr[ptr->animflag]);
			flagsize--;										//RJS 10Feb98
			break;
	}

	arc = (flag*ptr->arc)>>flagsize;						//RJS 10Feb98

	radius = ptr->radius;
	radius2 = ptr->radius2;
	ex = 0;
	ey = 0;

	totalangle += arc;

	Math_Lib.high_sin_cos((Angles) totalangle,sin_ang,cos_ang);
	tipx = (sin_ang * radius) / ANGLES_FRACT;					//RJS 19May00
	tipy = (cos_ang * radius) / ANGLES_FRACT;					//RJS 19May00

	cx = ptr->xpos;												//RJS 19May00
	cy = -ptr->ypos;											//RJS 19May00
	cz = ptr->zpos;												//RJS 19May00

	tipx += cx;													//RJS 19May00
	tipy += cy;													//RJS 19May00
	tipz = cz;													//RJS 19May00

	if (radius2)
	{
		ex = (sin_ang * radius2) / ANGLES_FRACT;
		ey = (cos_ang * radius2) / ANGLES_FRACT;
	}

	if (ptr->fatneedle)
	{
		totalangle -= ANGLES_5Deg;
		Math_Lib.high_sin_cos((Angles) totalangle,sin_ang,cos_ang);

		radius *= 3;
		radius >>= 2;

		xpos2 = (sin_ang * radius) / ANGLES_FRACT;
		ypos2 = (cos_ang * radius) / ANGLES_FRACT;

		totalangle += ANGLES_10Deg;
		Math_Lib.high_sin_cos((Angles) totalangle,sin_ang,cos_ang);

		xpos3 = (sin_ang * radius) / ANGLES_FRACT;
		ypos3 = (cos_ang * radius) / ANGLES_FRACT;

		xpos2 += cx;
		ypos2 += cy;
		zpos2 = cz;

		xpos3 += cx;
		ypos3 += cy;
		zpos3 = cz;
	}

	cx += ex;
	cy += ey;

//DeadCode PD 26Jan100 	_matrix.transformNC(fpobject_matrix,cx,cy,cz);
//DeadCode PD 26Jan100 
//DeadCode PD 26Jan100 	newco[0].bodyx.f = cx.f + object_obj3d->Body.X.f;
//DeadCode PD 26Jan100 	newco[0].bodyy.f = cy.f + object_obj3d->Body.Y.f;
//DeadCode PD 26Jan100 	newco[0].bodyz.f = cz.f + object_obj3d->Body.Z.f;
//DeadCode PD 26Jan100 
//DeadCode PD 26Jan100 	_matrix.transformNC(fpobject_matrix,tipx,tipy,tipz);
//DeadCode PD 26Jan100 
//DeadCode PD 26Jan100 	newco[1].bodyx.f = tipx.f + object_obj3d->Body.X.f;
//DeadCode PD 26Jan100 	newco[1].bodyy.f = tipy.f + object_obj3d->Body.Y.f;
//DeadCode PD 26Jan100 	newco[1].bodyz.f = tipz.f + object_obj3d->Body.Z.f;

#ifndef	_NOPOINTS_
	newco[0].setPosition(cx,cy,cz);								//RJS 19May00
	newco[1].setPosition(tipx,tipy,tipz);						//RJS 19May00
#endif
	if (ptr->fatneedle)
	{
#ifndef	_NOPOINTS_

		newco[2].setPosition(xpos2,ypos2,zpos2);				//RJS 19May00
		newco[3].setPosition(xpos3,ypos3,zpos3);				//RJS 19May00
#endif
#ifndef	_NOPOLYS_

		Lib3DPoint*	pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(shape::colour),4);//RJS 19May00
		pRVerts[0]=newco[0];
		pRVerts[1]=newco[2];
		pRVerts[2]=newco[1];
		pRVerts[3]=newco[3];
		g_lpLib3d->EndPoly();
#endif
	}
	else
	{
		DOLINE	doinst;
		UByteP	pinst = (UByteP) &doinst;

		doinst.start_vertex = 0;
		doinst.end_vertex = 1;

		doline(pinst);
	}
	instr_ptr += sizeof(DODIAL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		docompass
//Author		Paul.   
//Date			Wed 10 Jul 1996
//
//Description	Updated for fancy modern cockpit stuff.....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::docompass(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("a4");
#endif
	
	instr_ptr += sizeof(DOCOMPASS);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doiswitch
//Author		Paul.   
//Date			Wed 10 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doiswitch(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("a5");
#endif
	instr_ptr += sizeof(DOISWITCH);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doincln
//Author		Robert Slater
//Date			Tue 17 Sep 1996
//
//Description	Updated for fancy modern cockpit stuff.....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doincln(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("a6");
#endif
	DOINCLN_PTR	ptr = (DOINCLN_PTR )instr_ptr;
	IFShare		cx,cy,cz;
	SLong		radius,radius2;						
	IFShare		tipx,tipy,tipz;
	IFShare		tipx2,tipy2,tipz2;
	IFShare		tipx3,tipy3,tipz3;
	IFShare		tipx4,tipy4,tipz4;
	SLong		ex,ey,ez;
	SWord		sin_ang,cos_ang;
	DOLINE		doinst;
	UByteP		pinst = (UByteP) &doinst;
	SWord		pitch = object_obj3d->AngC;
	SWord		l1;

	radius = (-pitch * ptr->radius) / ANGLES_20Deg;
	if (radius > ptr->radius)
		radius = ptr->radius;
	else
	{
		if (radius < -ptr->radius)
			radius = -ptr->radius;
	}

	radius2 = ((radius<0)?-radius:radius);

	cx.i = ptr->xpos;
	cy.i = -ptr->ypos;
	cz.i = ptr->zpos;

	Math_Lib.high_sin_cos(object_obj3d->AngR,sin_ang,cos_ang);
	l1 = (ptr->radius * Math_Lib.Cos_ArcSin((radius2<<8)/ptr->radius)) >> 15;

	ex = (cos_ang * l1) / ANGLES_FRACT;
	ey = (sin_ang * l1) / ANGLES_FRACT;

	sin_ang = -sin_ang;

	cx.i += ((sin_ang * radius) / ANGLES_FRACT);
	cy.i += ((cos_ang * radius) / ANGLES_FRACT);

	tipx.i = cx.i - ex;
	tipy.i = cy.i - ey;
	tipz.i = cz.i;

	tipx2.i = cx.i + ex;
	tipy2.i = cy.i + ey;
	tipz2.i = cz.i;

	tipx3.i = (tipx2.i<<15)-(sin_ang*3);
	tipy3.i = (tipy2.i<<15)-(cos_ang*3);
	tipz3.i = (tipz2.i<<15);

	tipx4.i = (tipx.i<<15)-(sin_ang*3);
	tipy4.i = (tipy.i<<15)-(cos_ang*3);
	tipz4.i = (tipz.i<<15);

	_matrix.transformNC(fpobject_matrix,tipx,tipy,tipz);
	_matrix.transformNC(fpobject_matrix,tipx2,tipy2,tipz2);
	_matrix.transformNC(fpobject_matrix,tipx3,tipy3,tipz3);
	_matrix.transformNC(fpobject_matrix,tipx4,tipy4,tipz4);

#ifndef	_NOPOINTS_
	newco[0].setPosition(	tipx.f + object_obj3d->Body.X.f,
							tipy.f + object_obj3d->Body.Y.f,
							tipz.f + object_obj3d->Body.Z.f	);	//RJS 19May00

	newco[1].setPosition(	tipx2.f + object_obj3d->Body.X.f,
							tipy2.f + object_obj3d->Body.Y.f,
							tipz2.f + object_obj3d->Body.Z.f	);	//RJS 19May00

	newco[2].setPosition(	(tipx3.f*0.00003052) + object_obj3d->Body.X.f,
							(tipy3.f*0.00003052) + object_obj3d->Body.Y.f,
							(tipz3.f*0.00003052) + object_obj3d->Body.Z.f	);	//RJS 19May00

	newco[3].setPosition(	(tipx4.f*0.00003052) + object_obj3d->Body.X.f,
							(tipy4.f*0.00003052) + object_obj3d->Body.Y.f,
							(tipz4.f*0.00003052) + object_obj3d->Body.Z.f	);	//RJS 19May00
#endif
	SWord	minx,miny,maxx,maxy;

	minx = ptr->minx;
	miny = ptr->miny;
	maxx = ptr->maxx;
	maxy = ptr->maxy;

#ifndef	_NOPOLYS_

	Lib3DPoint*	pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr((ImageMapNumber) ptr->imagamap)),4);//RJS 19May00
	pRVerts[0]=newco[0];
	pRVerts[1]=newco[1];
	pRVerts[2]=newco[2];
	pRVerts[3]=newco[3];
	g_lpLib3d->EndPoly();
#endif
	tipx.i = (ptr->xpos) - ptr->radius;
	tipy.i = (-ptr->ypos);
	tipz.i = (ptr->zpos);

	tipx2.i = tipx.i + (ptr->radius<<1);
	tipy2.i = tipy.i;
	tipz2.i = tipz.i;

	_matrix.transformNC(fpobject_matrix,tipx,tipy,tipz);
	_matrix.transformNC(fpobject_matrix,tipx2,tipy2,tipz2);

#ifndef	_NOPOINTS_
	newco[0].setPosition(	tipx.f + object_obj3d->Body.X.f,
							tipy.f + object_obj3d->Body.Y.f,
							tipz.f + object_obj3d->Body.Z.f	);	//RJS 19May00

	newco[1].setPosition(	tipx2.f + object_obj3d->Body.X.f,
							tipy2.f + object_obj3d->Body.Y.f,
							tipz2.f + object_obj3d->Body.Z.f	);	//RJS 19May00
#endif
	doinst.start_vertex = 0;
	doinst.end_vertex = 1;

	pinst = (UByteP) &doinst;
	doline(pinst);

	instr_ptr += sizeof(DOINCLN);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	dosetglassrange
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Wed 16 Aug 1995
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
 void shape::dosetglassrange(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("a7");
#endif
	DOSETGLASSRANGE_PTR ptr;

	ptr = (DOSETGLASSRANGE_PTR) instr_ptr;
	
	UByte MAPPING_BASE;
	UByte MAPPING_RANGE;

	MAPPING_BASE = ptr->base;
	MAPPING_RANGE = ptr->spread;

//PD 29Nov95 - THIS SHOULD BE IN WRAPPER!

	instr_ptr += sizeof(DOSETGLASSRANGE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		docreatebpoly
//Author		Paul.   
//Date			Mon 15 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::docreatebpoly(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("a8");
#endif
	instr_ptr += sizeof(DOCREATEBUMPPOLY);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		docopybvert
//Author		Paul.   
//Date			Mon 15 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::docopybvert(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("a9");
#endif
	instr_ptr += sizeof(DOCOPYBVERT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dodrawbpoly
//Author		Paul.   
//Date			Mon 15 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dodrawbpoly(UByte *&)
{
#ifdef	_PROCDEBUG_
	Bollox("b0");
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doanimation
//Author		Robert Slater
//Date			Tue 18 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doanimation(UByte *&instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("b1");
#endif
	DOANIMATION_PTR	ptr = (DOANIMATION_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;			
	SByte			toggleflag;
//DeadCode RJS 20Oct00 	UByte			loopflag = GlobalAdptr[ptr->loopoffset];
	SLong			framecounter;
	SLong			cntinc, speedinc;
	MinAnimData*	mad = (MinAnimData*) GlobalAdptr;
	bool			doit = false;
	bool			cheattrigger = false;
	AtMax			MaxAction = AtMax(ptr->maxaction);					//RJS 1Jun00
	ClockType		ClockInc = ClockType(ptr->increment);				//RJS 1Jun00
	UByte			ThisState = 1 << mad->itemstate;					//RJS 1Jun00
	UByte			Condition = ptr->activatenow;				//RJS 27Oct97
	SLong			themax = ptr->maxframes;
	int				animtimer = ptr->flagoffset;
	float			fcntinc,frameScale;

	if (ptr->damagetoggle)
	{
		ThisState = GlobalAdptr[ptr->damageoffset];
		ThisState /= 96;
		ThisState = 1 << ThisState;
	}

	if (ThisState & Condition)											//RJS 1Jun00
		doit = true;													//RJS 1Jun00
											
	if (ptr->toggleoffset)										//RJS 07Apr97
	{
		toggleflag = GlobalAdptr[ptr->toggleoffset];
		if (toggleflag)
			cheattrigger = doit = true;									//RJS 1Jun00
		else
			toggleflag = 1;
	}
	else
		toggleflag = 1;

	if (ptr->fadeoffset && GlobalAdptr[ptr->fadedepth])
	{
		animtimer = ptr->fadeoffset;
		themax = ptr->maxfadeframes;
	}

	framecounter = GlobalAdptr[animtimer];							//RJS 05May98
 	if (!doit && framecounter)									//RJS 15Oct97
 		cheattrigger = doit = true;										//RJS 1Jun00

	if (doit)
	{
		frameScale = ptr->framescale * float(toggleflag);			//RJS 11May00

		cntinc = View_Point->DrawFrameTime();							//RJS 27Sep00
		if (cntinc)												//RJS 30Jun99
		{
			switch (ClockInc)										//RJS 27Oct97
			{
				case PER_FRAME:
					cntinc = 1;
					fcntinc = 1.f;
					frameScale = float(toggleflag);
					break;
				case PER_SEC10:
					fcntinc = float(cntinc+animlag) * 0.1f;
					break;
				case PER_SEC100:
					fcntinc = float(cntinc+animlag);
					break;
			}
		}
		else
			fcntinc = 0;

		if (ptr->timeroffset)
			fcntinc = float(GlobalAdptr[ptr->timeroffset]);		//RJS 11May00

		fastMath.FloatToInt(&cntinc,fcntinc * frameScale);		//RJS 27Sep00
		framecounter += cntinc;											//RJS 27Sep00

		if (ptr->toggleoffset)									//RJS 30Jun97
			GlobalAdptr[ptr->toggleoffset] = toggleflag;				//RJS 30Jun97

		if (toggleflag > 0)
		{
			if (framecounter > themax)							//RJS 05May98
			{
				switch (MaxAction)								//RJS 27Oct97
				{
					case MAX_STAY:
						framecounter = themax;
						break;
					case MAX_RESET_ZERO:
						if (cheattrigger)
							framecounter = cntinc;
						else
							framecounter = 0;
						break;
					case MAX_RESET_ONE:
						framecounter = cntinc;
						break;
					case MAX_DECREMENT:
						framecounter = themax - cntinc;
						GlobalAdptr[ptr->toggleoffset] = -GlobalAdptr[ptr->toggleoffset];
						break;
					case MAX_FADEOUT:
						framecounter = themax;
						if (!GlobalAdptr[ptr->fadedepth])
							GlobalAdptr[ptr->fadedepth] = 1;
						break;
				}
			}
		}
		else
		{
			if (framecounter < 0)
			{
				switch (MaxAction)								//RJS 27Oct97
				{
					case MAX_STAY:
						framecounter = 0;
						break;
					case MAX_RESET_ZERO:
						framecounter = themax;
						break;
					case MAX_RESET_ONE:
						framecounter = themax + cntinc;
						break;
					case MAX_DECREMENT:
						framecounter = 0;
						if (ptr->loopoffset)
						{
							if (GlobalAdptr[ptr->loopoffset])
							{
								GlobalAdptr[ptr->loopoffset]--;
								framecounter = cntinc;
								GlobalAdptr[ptr->toggleoffset] = -GlobalAdptr[ptr->toggleoffset];
							}
						}
						break;
				}
			}
		}

		GlobalAdptr[animtimer] = framecounter;
		if (animtimer == ptr->fadeoffset)
		{
			GlobalAdptr[ptr->fadedepth] = (framecounter * 254)/themax;
			GlobalAdptr[ptr->fadedepth]++;
		}
	}
	else
	{
		//Protect against going over max frames...
		if (MaxAction == MAX_STAY)								//RJS 31May99
		{
			if (toggleflag > 0)
			{
				if (framecounter > themax)
					GlobalAdptr[animtimer] = themax;
			}
			else
			{
				if (framecounter < 0)
					GlobalAdptr[animtimer] = 0;
			}
		}


	}

	instr_ptr += sizeof(DOANIMATION);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dodamage
//Author		Robert Slater
//Date			Tue 18 Feb 1997
//
//Description	Increments damage flags,
//				or damage bits....
//
//			Could be a problem for transient items....
//
//		For group element damage..
//
//				Col_AnimPrevPtr--->Col_AnimPtr--->Col_AnimNextPtr
//					Col_NextDep------>THIS<-------Col_PrevDep
//
//					If dependencies < 0,   then just disable the dependent item,
//											else inflict damage.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dodamage(UByte *&instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("b2");
#endif
	if (CollisionOn)		
	{
		DODAMAGE_PTR	ptr = (DODAMAGE_PTR) instr_ptr;
//DeadCode RJS 21Apr99 		UByteP			adptr = damage_AnimPtr;			//RJS 25Aug98
		UWord			damageflag;									//RJS 27Feb98
//DeadCode RJS 21Apr99 		UWord			velrand = adptr[ptr->veloffset];
		ItemPtr			itemhit = damage_ItemPtr;//RJS 25Aug98
		ULong			thisdead = BS_DEAD;
		WeapAnimData*	weapon = NULL;								//RJS 23May97
		MinAnimData*	mad = (MinAnimData*) damage_AnimPtr;				//RJS 27Feb98
//DeadCode RJS 27Oct00 		UWord	randno = Math_Lib.rnd();					//RJS 30Jun98
//DeadCode RJS 12Feb99 		SLong	realHitStrength = BoxCol::HitterStrength * (BoxCol::HitterDamageType + 1);//RJS 08Jan99
//DeadCode RJS 16Oct00 		SLong	realHitStrength = BoxCol::HitterStrength;		//RJS 12Feb99
#ifndef NDEBUG
		AirStrucPtr ac = NULL;
		if(itemhit->Status.size == AIRSTRUCSIZE)
			ac = AirStrucPtr(itemhit);
#endif

		if (!HitThisOffset)
		{
			if (ptr->stationno)
			{
//DeadCode RJS 21Apr99 				weapon = (WeapAnimData*)(adptr + (sizeof(WeapAnimData)*(ptr->stationno-1)) + sizeof(MinAnimData));
				MoveGunAnimData* adptr = (MoveGunAnimData*)damage_AnimPtr;
				SLong	realstationno = ptr->stationno-1;
				SLong	fxindex = adptr->weaponlaunchers[adptr->nolaunchers-1].launcherIndex;
				if (realstationno >= fxindex)
				{
					//is fuel-type damage...
					realstationno = adptr->nolaunchers+fxindex-ptr->stationno;
					if (realstationno < 0)
						realstationno = 0;
				}

				weapon = (WeapAnimData*) &adptr->weaponlaunchers[realstationno];
				laststationdamage[0] = weapon->SubDamage;		//RJS 25Nov98
				if (weapon->SubDamage < 31)
				{
					ULong	destruction = damage_AnimPtr[ptr->flagoffset];
					if (destruction == BS_DEAD)
						weapon->SubDamage = 31;
					else
					{
						ULong	dmain,drand;
						ULong	damage;

						dmain = (destruction * 7)>>3;
						drand = (destruction - dmain)<<1;

 						damage = dmain + ((_DPlay.damageRandom * drand)>>16);	//RJS 27Oct00
						damage = dmain + drand;							//RJS 27Oct00

						if (damage > 255)
							damage = 255;

						damage *= 31;
						damage /= 255;

						laststationdamage[0] = weapon->SubDamage;					//RJS 06Apr98

						weapon->SubDamage = damage;
#ifdef	_REPLAYCOL_
			::AfxTrace("WD: %d ... %d\n",int(ptr->flagoffset),int(damage));
#endif
					}
				}

				instr_ptr += sizeof(DODAMAGE);
				return;
			}

			lastdamptr = &damage_AnimPtr[ptr->flagoffset];				//RJS 27Feb98
			if (ptr->flagoffset)								//RJS 27Feb98
			{
				ULong		vulnerability = ptr->vulnerability;	//RJS 30Jun98
				ULong		realinc = ptr->increment;
#ifdef	_FXTEST_
				if (	(ptr->flagoffset == AOFF_ENGLEFT)
					||	(ptr->flagoffset == AOFF_ENGRIGHT)	)
				{
					logDamage = true;
					UWord cw=GETFPCW();
					::AfxTrace("Collision:\t%d\n",ptr->flagoffset);
					SETFPCW(cw);
				}
				else
					logDamage = false;
#endif
				damageflag = damage_AnimPtr[ptr->flagoffset];			//RJS 27Feb98
																//RJS 27Feb98
				lastdamage[0] = damageflag;						//RJS 27Feb98

				vulnerability >>= (BoxCol::HitterDamageType<<3);//RJS 30Jun98
				vulnerability &= 0xFF;							//RJS 30Jun98
				if (vulnerability)
				{
					if (BoxCol::HitterStrength)
					{
						ULong	nohitstokill = vulnerability / BoxCol::HitterStrength;
						if (nohitstokill)
						{
							realinc = (thisdead*BoxCol::HitterStrength)/vulnerability;
							damageflag += realinc;							//RJS 22Jan98
						}
						else
							damageflag = thisdead;
					}
					else
						damageflag = thisdead;

//A vulnerability of 255 is a special:   can damage, but not kill
					if (	(vulnerability == 255)						//RJS 22Jun00
						&&	(damageflag >= thisdead)	)
						damageflag = thisdead-1;
				}

#ifdef	_REPLAYCOL_
			::AfxTrace("D: %d ... %d (%d) -> %d\n",int(ptr->flagoffset),int(BoxCol::HitterStrength),int(vulnerability),int(damageflag));
#endif
			}
			else
			{
				ULong		vulnerability = ptr->vulnerability;
				ULong		destruction, hitstrength;

   				thisdead = 3;
				vulnerability >>= (BoxCol::HitterDamageType*8);	//RJS 30Jun98
				vulnerability &= 0xFF;							//RJS 30Jun98

				lastdamage[0] = mad->itemstate;					//RJS 27Feb98
				damageflag = mad->itemstate;					//RJS 27Feb98

				if (vulnerability)	//damage points needed to kill...
				{
					ULong	nohitstokill;
					//Make harder to kill if protected...
					if (damage_GrpTokenDep != NULL)
						vulnerability += vulnerability*(thisdead-((MinAnimData*)damage_GrpTokenDep)->itemstate);
					if (BoxCol::HitterStrength)						  //JIM 22/02/99
						nohitstokill = vulnerability / BoxCol::HitterStrength;
					else											  //JIM 22/02/99
						nohitstokill=1;								  //JIM 22/02/99
					if (nohitstokill)
					{
						UWord	randno = Math_Lib.rnd();				//RJS 27Oct00

						// Calc what it takes to move up a notch...
						destruction = ((thisdead<<16)*BoxCol::HitterStrength)/vulnerability;
						if (randno < destruction)
						{
							SLong	notchsize = (destruction<<1)/65535;
							if (notchsize < 3)
								notchsize = 2;			//1 notch
							else
							{
								if (notchsize > 5)
									notchsize = 6;		//3 notches
								else
									notchsize = 4;	//poop fiddle, cos we can't add 1.5 units of damage...2 notches
							}

							damageflag+=(notchsize>>1);
						}
					}
					else
						damageflag = thisdead;

//A vulnerability of 255 is a special:   can damage, but not kill
					if (	(vulnerability == 255)						//RJS 22Jun00
						&&	(damageflag >= thisdead)	)
						damageflag = thisdead-1;
				}
			}
		}
		else
		{
			if (ptr->stationno)
			{
				MoveGunAnimData* adptr = (MoveGunAnimData*)damage_AnimPtr;
				SLong	realstationno = ptr->stationno-1;
				SLong	fxindex = adptr->weaponlaunchers[adptr->nolaunchers-1].launcherIndex;
				if (realstationno >= fxindex)
				{
					//is fuel-type damage...
					realstationno = adptr->nolaunchers+fxindex-ptr->stationno;
					if (realstationno < 0)
						realstationno = 0;
				}

				weapon = (WeapAnimData*)&adptr->weaponlaunchers[realstationno];	//RJS 09Dec99
				laststationdamage[0] = weapon->SubDamage;		//RJS 25Nov98
				if (weapon->SubDamage < 31)
				{
					ULong	damage = (damage_AnimPtr[ptr->flagoffset] * 31)/255;//RJS 25Nov98
																//RJS 25Nov98
					weapon->SubDamage = damage;					//RJS 25Nov98
#ifdef	_REPLAYCOL_
			::AfxTrace("FWD: %d ... %d\n",int(ptr->flagoffset),int(damage));
#endif
				}

				instr_ptr += sizeof(DODAMAGE);
				return;
			}
			else
			{
				lastdamptr = &damage_AnimPtr[ptr->flagoffset];				//RJS 27Feb98
				if (ptr->flagoffset)								//RJS 27Feb98
				{
					damageflag = damage_ItemState;					//RJS 26Apr99
#ifdef	_REPLAYCOL_
					::AfxTrace("FD: %d ... %d\n",int(ptr->flagoffset),int(damageflag));
#endif
				}
				else
				{
   					thisdead = 3;
					damageflag = mad->itemstate;					//RJS 27Feb98
				}
			}
		}

		if (damageflag > thisdead)
			damageflag = thisdead;

		if (lastdamage[0] != damageflag)
		{
			Bool	isplane = FALSE;
			bool	isKillable = true;									//RJS 13Jul00

			if (itemhit->Status.size == AirStrucSize)
			{
				if (	(itemhit == Persons2::PlayerSeenAC)				//RJS 13Jul00
					&&	(Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW)	)
					isKillable = false;

				isplane = TRUE;						//RJS 08Jun99
				if (BoxCol::Col_Shooter)
				{
					if (!AirStrucPtr(itemhit)->lasthitter.count && BoxCol::Col_Shooter->Status.size==AIRSTRUCSIZE) //RJS 08Jun99
					{
						if (AirStrucPtr(itemhit)->ai.diaryptr!=AirStrucPtr(BoxCol::Col_Shooter)->ai.diaryptr)	//DAW 08/03/00
						{
//DEADCODE DAW 08/03/00 							if (AirStrucPtr(itemhit)->IsUsingPilotedAcLog()) 
//DEADCODE DAW 08/03/00 								Persons2::UpdateLog	(AirStrucPtr(BoxCol::Col_Shooter),-1,EventLog::DAMAGED);
//DEADCODE DAW 08/03/00 							else
//DEADCODE DAW 08/03/00 								if (AirStrucPtr(BoxCol::Col_Shooter)->IsUsingPilotedAcLog())
//DEADCODE DAW 08/03/00 									Persons2::UpdateLog	(AirStrucPtr(itemhit),+1,EventLog::DAMAGED);
//DEADCODE DAW 08/03/00 								else
								{
									Persons2::UpdateLog	(AirStrucPtr(itemhit),0,EventLog::ATTACKEDBYOTHERS);
									Persons2::UpdateLog	(AirStrucPtr(BoxCol::Col_Shooter),0,EventLog::ATTACKEDBYOTHERS);
								}
						}
					}

					if (itemhit->uniqueID.count != BoxCol::Col_Shooter->uniqueID.count)			//RJS 08Jun99
						((AirStrucPtr)itemhit)->lasthitter.count <<= BoxCol::Col_Shooter->uniqueID.count;

// cant do this in record/playback because in playback there is no shooter
// and so ac wont get shoved in same way as in record, resulting in complete
// breakdown of playback and me getting very annoyed 			//AMM 08Jul99

// shooter is now available but still cannot do this because ShoveX,Y and Z
// are set up when the collision occurs and this information is not available 
					
//DeadCode AMM 08Jul99 					if (!_Replay.Playback || (itemhit != Persons2::PlayerSeenAC))		//RJS 29Jun99
//DEADCODE AMM 18/01/00 					if (!_Replay.Playback && !_Replay.Record)	//AMM 08Jul99
					if (!_Replay.Playback && !_Replay.Record && !_DPlay.Implemented)
					{									
						if (BoxCol::ShoveX || BoxCol::ShoveY || BoxCol::ShoveZ)
						{
							AirStrucPtr	ac = (AirStrucPtr) itemhit;

							//+- 0.001						
							const float fact = 0.00004;
							ac->fly.pModel->RotVel.x += (Float(BoxCol::ShoveX) * fact);
							ac->fly.pModel->RotVel.y += (Float(BoxCol::ShoveY) * fact);
							ac->fly.pModel->RotVel.z += (Float(BoxCol::ShoveZ) * fact);
						}
					}
				}

// If we have been damaged for the first time...
				if (	((damageflag >= 63) && (damageflag < thisdead))	//RJS 5Sep00
					&&	(mad->itemstate < DAMMAGED)	)					//RJS 16Aug00
					mad->itemstate = DAMMAGED;								//RJS 21Feb00
			}

			if (damageflag == thisdead)
			{
				ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(damage_Shape);//RJS 16Sep98

				if ((BoxCol::Col_Shooter == Manual_Pilot.ControlledAC2) && !isplane)	//RJS 18Jun99
					View_Point->PossDirectorAction(BoxCol::colpos_hitgrp);//RJS 24May99

				if (damage_GrpElmt > -1)//RJS 16Sep98
				{
					ShapeDescPtr	supersdptr = (ShapeDescPtr) damage_Sdptr;
					SLong			timedead, supertimedead;
					SLong			ndam,odam;
					GrpMinAnimData		*madder;
					DOGROUP_PTR		gptr;
					SLong			Col_NextDep = 0;
					SLong			Col_PrevDep = 0;
					Coords3D		pPos,nPos;
					GrpMinAnimData*	gmad = (GrpMinAnimData*) mad;
					UWord			panimoff,nanimoff;


					if (ptr->setinvisible)						//RJS 22Nov98
						gmad->IsInvisible = 1;					//RJS 22Nov98

					panimoff = nanimoff = 0;					//RJS 27Apr99

					if (damage_GrpPrev)
					{
						gptr = (DOGROUP_PTR) damage_GrpPrev;
						Col_NextDep = gptr->element_next;
						madder = (GrpMinAnimData*) damage_GrpAnimPrev;//RJS 17Nov98
//DeadCode RJS 23Dec99						if ((madder->itemstate == DEAD) || (madder->IsBullied==1))//RJS 17Nov98
						if (madder->itemstate == DEAD)					//RJS 23Dec99
						{
							Col_NextDep = 0;
//Dead							panimoff = 0;
						}
						else
						{
							if (Col_NextDep)
							{
								pPos.X = gptr->xoffset + itemhit->World.X;
								pPos.Y = gptr->yoffset + itemhit->World.Y;
								pPos.Z = gptr->zoffset + itemhit->World.Z;
//DeadCode RJS 23Dec99								madder->IsBullied = 1;
								panimoff = damage_GrpAnimPrev - itemhit->Anim;
							}
						}
					}

					if (damage_GrpNext)
					{
						gptr = (DOGROUP_PTR) damage_GrpNext;
						Col_PrevDep = gptr->element_prev;
						madder = (GrpMinAnimData*) damage_GrpAnimNext;//RJS 17Nov98
//DeadCode RJS 23Dec99						if ((madder->itemstate == DEAD) || (madder->IsBullied==1))//RJS 17Nov98
						if (madder->itemstate == DEAD)					//RJS 23Dec99
						{
							Col_PrevDep = 0;
//Dead							nanimoff = 0;
						}
						else
						{
							if (Col_PrevDep)
							{
								nPos.X = gptr->xoffset + itemhit->World.X;
								nPos.Y = gptr->yoffset + itemhit->World.Y;
								nPos.Z = gptr->zoffset + itemhit->World.Z;
//DeadCode RJS 23Dec99								madder->IsBullied = 1;
								nanimoff = damage_GrpAnimNext - itemhit->Anim;
							}
						}
					}

					if (Col_PrevDep || Col_NextDep)
					{
						Trans_Obj.LaunchGroupThug(	itemhit,
													FIST,
													damage_GrpElmt-1,
													Col_NextDep,
													Col_PrevDep,
													pPos,
													nPos,
													panimoff,
													nanimoff,
													BoxCol::Col_Shooter);//RJS 05Jul99
					}

//DeadCode AMM 10Oct00 					if (	!itemhit->Status.deaded				//AMM 10Jun98
//DeadCode AMM 10Oct00 						&&	SHAPE.GetGroupDeathToll(itemhit) )
//DeadCode AMM 10Oct00 					{
//DeadCode AMM 10Oct00 						itemhit->Status.deaded = TRUE;			//AMM 10Jun98
//DeadCode AMM 10Oct00 						if (BoxCol::Col_Shooter)				//RJS 09Jun99
//DeadCode AMM 10Oct00 						{
//DeadCode AMM 16Nov99 							if (_DPlay.Implemented)						
//DeadCode AMM 16Nov99 							{											
//DeadCode AMM 16Nov99 								if (_DPlay.GameType>TEAMPLAY)
//DeadCode AMM 16Nov99 									_DPlay.NewScoreClaim(BoxCol::Col_Shooter,itemhit->uniqueID.count);
//DeadCode AMM 16Nov99 							}
//DeadCode AMM 16Nov99 							else
//DeadCode AMM 10Oct00 							{
//DeadCode AMM 10Oct00 								if (BoxCol::Col_Shooter->Status.size == AIRSTRUCSIZE)
//DeadCode AMM 10Oct00 									itemhit->ScoreSimpleItemKilled(true,(AirStrucPtr)BoxCol::Col_Shooter);
//DeadCode AMM 10Oct00 							}
//DeadCode AMM 10Oct00 						}
//DeadCode AMM 10Oct00 					}

					if (itemhit->Status.size == AIRSTRUCSIZE)			//CSB 23Aug00
					{													//CSB 23Aug00
						if (	(mad->itemstate < DYING)				//CSB 23Aug00
							&&	!itemhit->Status.deadtime	)			//CSB 23Aug00
						{												//CSB 23Aug00
							mad->itemstate = DYING;						//CSB 23Aug00

							AirStrucPtr	sag = AirStrucPtr(itemhit);		//CSB 23Aug00
							if((sag->fly.numinsag) && (!sag->fly.expandedsag))	//CSB 23Aug00
							{											//CSB 23Aug00
								if(sag->ShouldDumpAndRun(false, true))
									sag->DumpAndRun();

								if(Art_Int.CountSquadronSize(sag) == 1)
								{										//CSB 23Aug00
									itemhit->Status.deadtime = 7;		//CSB 23Aug00
									sag->DestroySag();					//CSB 23Aug00
								}										//CSB 23Aug00
							}											//CSB 23Aug00
						}												//CSB 23Aug00
					}
					else
					{
						timedead = sdptr->DeadTime + itemhit->Status.deadtime;
						supertimedead = supersdptr->DeadTime;

						if (supertimedead < timedead)
							itemhit->Status.deadtime = supertimedead;
						else
						{
							itemhit->Status.deadtime = timedead;
//DeadCode CSB 23Aug00 							if(itemhit->Status.size == AIRSTRUCSIZE)				//CSB 10Aug00
//DeadCode CSB 23Aug00 							{														//CSB 10Aug00
//DeadCode CSB 23Aug00 								AirStrucPtr sag = AirStrucPtr(itemhit);				//CSB 10Aug00
//DeadCode CSB 23Aug00 								if((sag->fly.numinsag) && (!sag->fly.expandedsag))	//CSB 10Aug00
//DeadCode CSB 23Aug00 									sag->DestroySag();								//CSB 10Aug00
//DeadCode CSB 23Aug00 							}														//CSB 10Aug00
						}															//CSB 10Aug00
					}

					itemhit->Status.deadscale = supersdptr->DeadScale;
				}
				else											//RJS 27Feb98
				{
					if (ptr->setinvisible)						//RJS 22Nov98
						mad->IsInvisible = 1;					//RJS 22Nov98

					if (	(itemhit != Manual_Pilot.ControlledAC2)	//RJS 06Mar97
						&&	isplane
						&&	(mad->itemstate < DYING)	)			//CSB 23Aug00
						mad->itemstate = DYING;						//RJS 21Feb00

					if (itemhit->Status.deadtime == FALSE)			//RJS 06May99
					{
						if (ptr->isfatal || isKillable)					//RJS 13Jul00
						{
//DeadCode RJS 15Aug00 							itemhit->Status.deadtime = sdptr->DeadTime;
//DeadCode RJS 15Aug00 							itemhit->Status.deadscale = sdptr->DeadScale;
//DeadCode RJS 15Aug00 	 						itemhit->Status.deaded = TRUE;		//RJS 27Feb98
//DeadCode RJS 15Aug00 							if (itemhit == Persons2::PlayerSeenAC)//RJS 09Jul99
//DeadCode RJS 15Aug00 							{
//DeadCode RJS 15Aug00 								Persons2::PlayerGhostAC->Status.deadtime = sdptr->DeadTime;
//DeadCode RJS 15Aug00 								Persons2::PlayerGhostAC->Status.deadscale = sdptr->DeadScale;
//DeadCode RJS 15Aug00 								Persons2::PlayerGhostAC->Status.deaded = TRUE;
//DeadCode RJS 15Aug00 							}

//DeadCode AMM 5Jul00 	// if we are in coop game score needs to be set when claim packets arrive
// shooter is passed through in collision packets now		//AMM 5Jul00

//DeadCode AMM 5Jul00 							if (_DPlay.Implemented && _DPlay.GameType<DPlay::COMMSQUICKMISSION && isplane)	//RJS 09Jun99
							if (_DPlay.Implemented && isplane)
							{
								_DPlay.SetScore((AirStrucPtr)itemhit,BoxCol::Col_Shooter);//JIM 11Mar99
// as player has been killed reset assist

// cant as player can explode upon hitting ground requiring as assist
// this can result however in a player being killed, still being in control and crashing so shooter gets kill
// and assist. But thats what you get for constantly changing the damage model so nobody knows whats going on

//DeadCode AMM 16Nov00 								int killed=_DPlay.UID_2Slot(itemhit->uniqueID.count);	//RJS 13Oct00
//DeadCode AMM 16Nov00 
//DeadCode AMM 16Nov00 								if (killed<MAXPLAYERS)
//DeadCode AMM 16Nov00 								{
//DeadCode AMM 16Nov00 									_DPlay.CommsKiller[killed]=255;
//DeadCode AMM 16Nov00 								}
							}

							if (itemhit->Status.size == FORMATIONSIZE)
								FormationItemPtr(itemhit)->BreakForm();
							else
							{
								if (isplane)
								{
	// Screws up other aircraft death movecodes....
									if  (Manual_Pilot.ControlledAC2 == itemhit)
										_Miles.SequenceAudible(FIL_MUSIC_SPIRALLING);	  //RDH 01/03/99
									Manual_Pilot.DeathSequenceOverride(itemhit,AUTO_DEATHSEQUENCE);

//DeadCode CSB 18Sep00 									if((BoxCol::Col_Shooter == Persons2::PlayerSeenAC) && (AirStrucPtr(itemhit)->nationality == Persons2::PlayerGhostAC->nationality))
//DeadCode CSB 18Sep00 									{
//DeadCode CSB 18Sep00 										Persons2::PlayerSeenAC->BreakForm();
//DeadCode CSB 18Sep00 										Persons2::PlayerSeenAC->nationality = NAT_AMBER;
//DeadCode CSB 18Sep00 										Persons2::PlayerGhostAC->nationality = NAT_AMBER;
//DeadCode CSB 18Sep00 										Art_Int.AlertFighters(AirStrucPtr(itemhit), AirStrucPtr(Persons2::PlayerGhostAC), AirStrucPtr(itemhit));
//DeadCode CSB 18Sep00 									}

									((AirStrucPtr)itemhit)->BreakForm();
									mad->itemstate = DYING;					//RJS 21Feb00
								}
							}

// Moved to here, because it must be called after DeathSequenceOverride!
							itemhit->Status.deadtime = sdptr->DeadTime;	//RJS 15Aug00
							itemhit->Status.deadscale = sdptr->DeadScale;
	 						itemhit->Status.deaded = TRUE;
							if (itemhit == Persons2::PlayerSeenAC)
							{
								Persons2::PlayerGhostAC->Status.deadtime = sdptr->DeadTime;
								Persons2::PlayerGhostAC->Status.deadscale = sdptr->DeadScale;
								Persons2::PlayerGhostAC->Status.deaded = TRUE;
							}

//DeadCode AMM 10Oct00 							if (!_DPlay.Implemented)
//DeadCode AMM 10Oct00 							{
//DeadCode AMM 10Oct00 //DeadCode AMM 5Jul00 	// claims in comms dealt with when claim packets arrive
//DeadCode AMM 10Oct00 								itemhit->ScoreSimpleItemKilled(true,(AirStrucPtr)BoxCol::Col_Shooter);//JIM 11Mar99
//DeadCode AMM 10Oct00 	//							itemhit->ScoreSimpleItemKilled(true,(AirStrucPtr)BoxCol::Col_Hitter);
//DeadCode AMM 10Oct00 							}
//DeadCode AMM 5Jul00 							else
//DeadCode AMM 5Jul00 							{
//DeadCode AMM 5Jul00 								if (_DPlay.GameType>DPlay::TEAMPLAY)
//DeadCode AMM 5Jul00 								{
//DeadCode AMM 5Jul00 	// coop games only
//DeadCode AMM 5Jul00 	//DeadCode AMM 08Apr99 								if (hitterscorer)
//DeadCode AMM 5Jul00 	//DeadCode AMM 08Apr99 									_DPlay.NewScoreClaim(hitterscorer,(UniqueID)uniqueid);
//DeadCode AMM 5Jul00 //DeadCode AMM 16Nov99 									if (BoxCol::Col_Shooter)		//AMM 08Apr99
//DeadCode AMM 5Jul00 //DeadCode AMM 16Nov99 										_DPlay.NewScoreClaim(BoxCol::Col_Shooter,itemhit->uniqueID.count);//AMM 08Apr99
//DeadCode AMM 5Jul00 
//DeadCode AMM 5Jul00 
//DeadCode AMM 5Jul00 								}
//DeadCode AMM 5Jul00 							}
						}
					}
				}

				if (ptr->isejected)
				{
					WorldStuff*	worldptr = mobileitem::currworld;

					BoxCol::AddEffect(FX_VISUAL,BS_DEAD,ANIM_SMALLFLASH,0,NULL,damage_GrpElmt,damage_Shape);//RJS 05May99

					Trans_Obj.LaunchBitsOffPart(itemhit,
												damage_Shape,	//RJS 14Jun00
												damage_AnimPtr,	//RJS 14Jun00
												&damage_AnimPtr[ptr->flagoffset],//RJS 21Apr99
												*worldptr,
												lastdamage[0],
												lastdamptr,
												BoxCol::HitterStrength);
				}

				if (!isplane)
				{
					if (BoxCol::Col_Shooter == Persons2::PlayerSeenAC)
						Trans_Obj.NewRaid(itemhit->SGT);

					Squad_Diary.HitTarget(BoxCol::Col_Shooter,itemhit,BoxCol::Col_GroupPtr);//RJS 23Feb00
				}
			}
		}														//RJS 27Feb98
																//RJS 27Feb98
		if (ptr->flagoffset)									//RJS 27Feb98
			damage_AnimPtr[ptr->flagoffset] = damageflag;		//RJS 21Apr99
		else													//RJS 27Feb98
			mad->itemstate = damageflag;						//RJS 27Feb98
	}															//RJS 27Feb98

	instr_ptr += sizeof(DODAMAGE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doeffect
//Author		Robert Slater
//Date			Tue 18 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doeffect(UByte *&instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("b3");
#endif
	if (CollisionOn)					
	{
		DOEFFECT_PTR	ptr = (DOEFFECT_PTR) instr_ptr;
//DeadCode RJS 21Apr99 		UByteP			adptr = damage_AnimPtr;			//RJS 25Aug98
		UWord			damageflag;
		ULong			knockval;
//DeadCode RJS 27Oct00 		UWord			randomval;
		Bool			doit = FALSE;
		EffectType		thetype = (EffectType) ptr->type;				//RJS 23May97
		WeapAnimData	*weapon = NULL;								//RJS 23May97
		UWord			EffectVal = ptr->enumvalue;						//RJS 23May97
		SWord			damtype = ptr->damagetype - 1;
		MinAnimData		*mad = (MinAnimData*) damage_AnimPtr;	//RJS 21Apr99
		UByte			maxscale = 255;
		UByte			lastdamval = lastdamage[ptr->damindexold];

		if ((damtype == -1) || (damtype == BoxCol::HitterDamageType))
		{
			UByte	levelactive = ptr->levelactive;
			if (ptr->flagoffset == 0)
			{
				damageflag = mad->itemstate;
				maxscale = 3;
			}
			else
			{
				if (ptr->stationno)
				{
// New code here allows fuel launchers to stomp backwards all over weapon launchers.
// Rule is that there cannot be more than 5 vapour stream fx at once...

					MoveGunAnimData*	adptr = (MoveGunAnimData*)damage_AnimPtr;
					SLong				realstationno = ptr->stationno-1;
					SLong				fxindex = adptr->weaponlaunchers[adptr->nolaunchers-1].launcherIndex;

					if (realstationno >= fxindex)				//RJS 09Dec99
					{
						EffectVal = ANIM_FUELDAMAGE;

						//Word backwards and stomp over weapon launcher if needs be...
						realstationno = adptr->nolaunchers+fxindex-ptr->stationno;
						if (realstationno < 0)
							realstationno = 0;
					}
					else
						EffectVal = ANIM_WEAPONDAMAGE;

					// Always assume the weapon array is first in the animation data....
					weapon = (WeapAnimData*)&adptr->weaponlaunchers[realstationno];//RJS 09Dec99

//DeadCode RJS 09Dec99 					if (	(weapon->LauncherType == LT_INTFUEL)
//DeadCode RJS 09Dec99 						||	(weapon->LauncherType == LT_FUEL)
//DeadCode RJS 09Dec99 						||	(weapon->LauncherType == LT_VAPOUR)	)
//DeadCode RJS 09Dec99 						EffectVal = ANIM_FUELDAMAGE;
//DeadCode RJS 09Dec99 					else
//DeadCode RJS 09Dec99 						EffectVal = ANIM_WEAPONDAMAGE;

					lastdamval = laststationdamage[ptr->damindexold];
					damageflag = weapon->SubDamage;
					maxscale = 31;
				}
				else
					damageflag = damage_AnimPtr[ptr->flagoffset];//RJS 21Apr99
			}

			if (ptr->levelactive)
			{
				UByte	levellimit = BS_DAMLV1;

				levelactive = (maxscale * levelactive)/255;
				if (thetype < FX_ALIGN)
				{
#ifdef	_FXTEST_
	if (logDamage)
	{
		UWord cw=GETFPCW();
		::AfxTrace("...check:\t%d < \t%d < %d\n",lastdamval,levelactive,damageflag);
		SETFPCW(cw);
	}
#endif
					if (	(damageflag >= levelactive)
						&&	(lastdamval < levelactive) )				//RJS 06Apr98
						doit = TRUE;
				}
				else
				{
					switch (ptr->levelactive)
					{
						case BS_DAMLV1:
							levellimit = BS_DAMLV2;
							break;
						case BS_DAMLV2:
						case BS_DEAD:
							levellimit = BS_DEAD;
							break;
					}

					levellimit = (maxscale*levellimit)/255;

					if (	(damageflag >= levelactive)
						&&	(damageflag < levellimit)	)
					{
						doit = TRUE;
						if (	(EffectVal == ANIM_FUELDAMAGE)
							&&	(ptr->levelactive == BS_DEAD)	)
							thetype = FX_EJECT;
					}
				}
			}
			else
			{
				//We can pretty much guarantee that the only effects 
				//  to come in here are bullet hits
				if (HitThisOffset == FALSE)								//RJS 15Sep98
				{
					if (damage_GrpElmt > -1)
					{
						GrpMinAnimData*	gmad = (GrpMinAnimData*) mad;
						if (!gmad->IsBullied)
							doit = TRUE;
					}
					else
						doit = TRUE;										//RJS 15Sep98
				}
			}
		
			if (doit)
			{
#ifdef	_FXTEST_
	if (logDamage)
	{
		UWord cw=GETFPCW();
		::AfxTrace("...do FX\t%d\t%d\n",thetype,EffectVal);
		SETFPCW(cw);
	}
#endif
				switch (thetype)
				{
//DeadCode RJS 04Feb99 					case FX_SFX_ALL:									//RJS 15Sep98
					case FX_SFX:										//RJS 15Sep98
						BoxCol::AddEffect(thetype,ptr->levelactive,ptr->enumvalue,ptr->randomdelta,NULL,damage_GrpElmt,damage_Shape);
						break;

					case FX_RADIO:
					{
						// Only trigger if another ac has inflicted this damage...
						if ((BoxCol::Col_Shooter)&&
							BoxCol::Col_Shooter->Status.size >= AIRSTRUCSIZE)		//RDH 18May99
							BoxCol::AddEffect(thetype,ptr->levelactive,EffectVal,ptr->randomdelta,(UByteP)weapon,damage_GrpElmt,damage_Shape);//RDH 18May99
					}
					break;
					case FX_VISUAL:										//RJS 15Sep98
						if (weapon)								//RJS 09Dec99
						{
							if ((weapon->LauncherType & LT_MASK) != LT_SMKTRAILS)
							{
// Disable this gun position...
								weapon->LauncherType = LT_CONTACT;		//dummy	//RJS 10Aug00
								weapon->hdg = 0;						//RJS 11Jul00
								weapon->pitch = -1;
							}

							weapon->launcherIndex = ptr->stationno-1;//RJS 09Dec99
						}

						BoxCol::AddEffect(thetype,ptr->levelactive,EffectVal,ptr->randomdelta,(UByteP)weapon,damage_GrpElmt,damage_Shape);
						break;
					case FX_EJECT:
					{
//DeadCode RJS 23Mar99 						if (BoxCol::Col_ExplodeIt == FALSE)		//RJS 30Mar98
						{
							WorldStuff*	worldptr = mobileitem::currworld;
							UByte		lastdam = damage_AnimPtr[ptr->enumvalue];//RJS 21Apr99
							UByteP		lastptr = &damage_AnimPtr[ptr->enumvalue];//RJS 21Apr99

							if (lastdam != BS_DEAD)
							{
								BoxCol::AddEffect(FX_VISUAL,ptr->levelactive,ANIM_SMALLFLASH,ptr->randomdelta,(UByteP)weapon,damage_GrpElmt,damage_Shape);//RJS 05May99
//DeadCode RJS 23Mar99 								adptr[ptr->enumvalue] = BS_DEAD;

								Trans_Obj.LaunchBitsOffPart(damage_ItemPtr,
															damage_Shape,//RJS 14Jun00
															damage_AnimPtr,//RJS 14Jun00
															lastptr,
															*worldptr,
															lastdam,
															lastptr,
															ptr->randomdelta);

								damage_AnimPtr[ptr->enumvalue] = BS_DEAD;//RJS 21Apr99
							}
						}
					}
					break;
					case FX_INCREMENT:
					{
						UWord	maxhit = ((damageflag - lastdamage[0]) * ptr->randomdelta)/100;
						if (maxhit)
						{
							SLong	hitrand = (_DPlay.effectRandom * (maxhit>>3))>>16;	//RJS 27Oct00

							knockval = damage_AnimPtr[ptr->enumvalue] + maxhit - (maxhit>>4) + hitrand;//RJS 21Apr99
							if (knockval > BS_DEAD)
								knockval = BS_DEAD;

							lastdamage[ptr->damindexnew] = damage_AnimPtr[ptr->enumvalue];//RJS 21Apr99

							damage_AnimPtr[ptr->enumvalue] = knockval;//RJS 21Apr99
						}
						break;
					}
					case FX_IMPACTFUZZY:
					{
						SLong	oldDamage = damage_AnimPtr[ptr->enumvalue];
						SLong	fuzzyDamage = (damageflag + oldDamage)>>1;
						if (fuzzyDamage)
						{
							SLong	fuzzyDifference = ((damageflag - oldDamage)*ptr->randomdelta)/100;

							fuzzyDamage += ((_DPlay.effectRandom*fuzzyDifference)>>16) - (fuzzyDifference>>1);
							if (fuzzyDamage < oldDamage)
								fuzzyDamage = oldDamage;
							else
							{
								if (fuzzyDamage > BS_DEAD)
									fuzzyDamage = BS_DEAD;
							}

							lastdamage[ptr->damindexnew] = oldDamage;

							damage_AnimPtr[ptr->enumvalue] = UByte(fuzzyDamage);
						}
					}
					break;
				}
			}
		}
	}

	instr_ptr += sizeof(DOEFFECT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		docollision
//Author		Robert Slater
//Date			Tue 18 Feb 1997
//
//Description	
//				Macca stuff...
//			
//				send flag:
//							0 ... don't send
//							1 ... transient hit
//							2 ... non-transient hit
//							3 ... forced hit
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::docollision(UByte *&instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("b4");
#endif
	if (FixUpCollision)
	{
		DOCOLLISION_PTR	ptr = DOCOLLISION_PTR(instr_ptr);
		if (ptr->radius)
		{
			lastColBox.pos.X = ptr->xoff;
			lastColBox.pos.Y = ptr->yoff;
			lastColBox.pos.Z = ptr->zoff;
			lastColBox.radius = ptr->radius << 4;
		}

		CollisionCnt++;
		instr_ptr += sizeof(DOCOLLISION);
	}
	else
	{
		DOCOLLISION_PTR	ptr = (DOCOLLISION_PTR) instr_ptr;
//DeadCode RJS 21Apr99 		UByteP			adptr = damage_AnimPtr;						//RJS 25Aug98
		UByte			flag = damage_AnimPtr[ptr->flagoffset];
		Bool			hitit = FALSE;

		if (HitThisOffset)
		{
			if (ptr->flagoffset == HitThisOffset)
			{
				DOLAUNCHER	thislaunch;
				Coords3D	*cptr = &BoxCol::colpos_impact;

				collisionDepth++;										//RJS 16Jun00

				CollisionOn = TRUE;
				DamageNow = TRUE;
			
				thislaunch.posx = ptr->xoff;
				thislaunch.posy = ptr->yoff;
				thislaunch.posz = ptr->zoff;

				SHAPE.LauncherToWorld(damage_ItemPtr,(UByteP)&thislaunch,damage_Scale,cptr->X,cptr->Y,cptr->Z,damage_GrpOffset);//RJS 26Nov99

				instr_ptr += sizeof(DOCOLLISION);

				if ((_DPlay.Implemented || _Replay.Record) 
					&& damage_ItemPtr==Persons2::PlayerSeenAC)//RJS 09Sep98
				{
#ifdef	_REPLAYCOL_
	::AfxTrace("FC_S: %d\n",int(ptr->flagoffset));
#endif
					// Log a successful collision...
//						DamageNow = TRUE;
//DeadCode AMM 12Jul99 					CollisionOn = FALSE;
					_Replay.FakeCollisionOn=true;				//AMM 12Jul99

					SHAPE.LogCollision(	damage_ItemPtr,
										BoxCol::Col_Shooter,		  //JIM 11/03/99
										damage_Shape,			//AMM 26Nov98
										instr_ptr,
										damage_GrpElmt,					//RJS 16Sep98
										FORCE_SET+BoxCol::HitterDamageType,
										(damage_ItemState * FORCE_MAX)/BS_DEAD,
										3);						//AMM 08Jan99
				}
#ifdef	_REPLAYCOL_
				else
				{
					::AfxTrace("FC_R: %d\n",int(ptr->flagoffset));
				}
#endif
			}
			else
				instr_ptr += sizeof(DOCOLLISION);
		}
		else
		{
			if (ptr->radius > 0)									//RJS 04Mar97
			{
 				if (ptr->flagoffset == 0)
 					flag = BS_ALIVE;
 
 				if (flag != BS_DEAD)	
 				{
 					// Detailed Collision test here....
					if (BoxCol::Col_ExplodeIt)						//RJS 30Mar98
						hitit = TRUE;								//RJS 30Mar98
					else
	 					hitit = BoxCol::TestCol2(ptr->xoff,			//RJS 20Apr98
												 ptr->yoff,			//RJS 20Apr98
												 ptr->zoff,			//RJS 20Apr98
												 ptr->sx,			//RJS 20Apr98
												 ptr->sy,			//RJS 20Apr98
												 ptr->sz);			//RJS 20Apr98
//DeadCode RJS 16Jun00 												 ptr->succeed);		//RJS 20Apr98
 				}

  				CollisionOn = hitit;								//RJS 22Jun98
			}
			else
				CollisionOn = hitit = BoxCol::DetailedTest();//New hit-box test//RJS 01Dec98

			if (hitit)
			{
//DeadCode RJS 16Jun00 				if (ptr->succeed)
//DeadCode RJS 16Jun00 					instr_ptr += ptr->succeed;
//DeadCode RJS 16Jun00 				else
				instr_ptr += sizeof(DOCOLLISION);
				if (ptr->radius)								//RJS 26Jun00
					collisionDepth++;							//RJS 26Jun00

				SLong	send;								//AMM 08Jan99

				DamageNow = TRUE;
				if (_DPlay.PossTransmitColl(damage_ItemPtr,BoxCol::Col_Hitter,send))//AMM 08Jan99
				{
					if (collisionDepth)
					{
#ifdef	_REPLAYCOL_
						if (ptr->radius)
							::AfxTrace("C_S: %d\n",int(ptr->flagoffset));
						else
							::AfxTrace("OUTER!\n");
#endif
						// Log a successful collision...
						_Replay.FakeCollisionOn=true;			//AMM 12Jul99
						// send calc moved to posstransmitcoll...//AMM 08Jan99

						if (send==-1)							//AMM 13Apr99
						{
// we are going to do this collision so kill the transient that caused it on all machines

//DeadCode AMM 16Nov99 							_DPlay.SendKillTransientsMessage();
						}

						SHAPE.LogCollision(	damage_ItemPtr,
											BoxCol::Col_Shooter,		  //JIM 11/03/99
											damage_Shape,		//AMM 26Nov98
											instr_ptr,
											damage_GrpElmt,					//RJS 16Sep98
											BoxCol::HitterDamageType,
											BoxCol::HitterStrength,
 											send);//AMM 31Aug98
					}
				}
#ifdef	_REPLAYCOL_
				else
				{
					if (ptr->radius)
						::AfxTrace("C_R: %d\n",int(ptr->flagoffset));
					else
						::AfxTrace("OUTER!\n");
				}
#endif
			}
			else
				instr_ptr += ptr->fail;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dodrawstation
//Author		Robert Slater
//Date			Fri 28 Feb 1997
//
//Description	Duplicates weapon anim information for this station,
//				then draws the station....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dodrawstation(UByte *&instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("b5");
#endif
	DODRAWSTATION_PTR	ptr = (DODRAWSTATION_PTR) instr_ptr;
	MoveGunAnimData*	adptr = (MoveGunAnimData*) GlobalAdptr;
	WeapAnimData		weap = adptr->weaponlaunchers[ptr->stationno];

	if (weap.stationshape)										//RJS 24May99
	{															//RJS 24May99
		DOCALLSHAPE			subptr;								//RJS 24May99
		LauncherAnimData	newadptr;							//RJS 24May99
		MinAnimData*		mad;								//RJS 24May99
		animptr				oldadptr;							//RJS 24May99

		subptr.vertex = 0;
		subptr.shape = (ShapeNum) weap.stationshape;
		subptr.hdg = ANGLES_0Deg;
		subptr.pitch = ANGLES_0Deg;
		subptr.roll = ANGLES_0Deg;

		mad = (MinAnimData*) &newadptr;
		*mad = *((MinAnimData*) GlobalAdptr);
		mad->itemstate = ALIVE;		//otherwise rockets ignite!		//RJS 10May99

//Inherit animdata from daddy
		if (SHAPESTUFF.GetShapePtr(ShapeNum(object_obj3d->Shape))->AnimDataSize == AIRCRAFTANIM)
		{
			AircraftAnimData*	adptr = (AircraftAnimData*)GlobalAdptr;

			newadptr.ammoleft = weap.LoadedStores;					//RJS 27Mar00
			newadptr.LEFTWINGIN = adptr->LEFTWINGIN;
			newadptr.LEFTWINGOUT = adptr->LEFTWINGOUT;
			newadptr.RIGHTWINGIN = adptr->RIGHTWINGIN;
			newadptr.RIGHTWINGOUT= adptr->RIGHTWINGOUT;
			newadptr.OTHER = adptr->OTHER;
		}
		else
		{
			SimpleAircraftAnimData*	adptr = (SimpleAircraftAnimData*)GlobalAdptr;

			newadptr.ammoleft = weap.LoadedStores;					//RJS 27Mar00
			newadptr.LEFTWINGIN = adptr->LEFTWINGIN;
			newadptr.LEFTWINGOUT = adptr->LEFTWINGOUT;
			newadptr.RIGHTWINGIN = adptr->RIGHTWINGIN;
			newadptr.RIGHTWINGOUT= adptr->RIGHTWINGOUT;
			newadptr.OTHER = adptr->OTHER;
		}

		oldadptr = GlobalAdptr;
		GlobalAdptr = (UByteP)mad;
		GlobalAdptr = (AnimSizeField) sizeof(LauncherAnimData);	//RJS 01Dec99
		GlobalAdptr = (AnimFlagField) (1<<MINANIM)+ (1<<LAUNCHERANIM);//RJS 01Dec99

		DrawSubShape((UByteP)&subptr);							//RJS 01Dec97

		GlobalAdptr = oldadptr;
	}

	instr_ptr += sizeof(DODRAWSTATION);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		docaserange
//Author		Robert Slater
//Date			Mon 3 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::docaserange(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("b6");
#endif
	DOCASERANGE_PTR ptr = (DOCASERANGE_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;	
	SWord			flag;										//RJS 04Sep97
	SWord			thisjump;									//RJS 03Sep97
	UByteP			offset;
	int				i;											//RJS 03Sep97
	SWord			range;										//RJS 03Sep97
	SWord			possiblejump;								//RJS 03Sep97
	
	if (!ptr->useword)
		flag = GlobalAdptr[ptr->flag] / ptr->factor;			//RJS 21Apr99
	else
		flag = *((SWordP) &GlobalAdptr[ptr->flag]);				//RJS 21Apr99

	offset = instr_ptr + sizeof(DOCASERANGE);

	possiblejump = ptr->failjump;

	for (i=0; i < ptr->nofields; i++)
	{
		range = *(SWordP)offset;
		offset += sizeof(SWord);

		thisjump = *(SWordP)offset;
		offset += sizeof(SWord);

		if (flag >= range)
			possiblejump = thisjump;
		else
			break;
	}

//DeadCode RJS 03Sep97 	if (flag < ptr->range)
//DeadCode RJS 03Sep97 		offset += (ptr->nofields-1) * sizeof(UWord);
//DeadCode RJS 03Sep97 
//DeadCode RJS 03Sep97 	instr_ptr += *(UWord *)offset;

	instr_ptr += possiblejump;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doifpiloted
//Author		Robert Slater
//Date			Fri 7 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doifpiloted(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("b7");
#endif
	DOIFPILOTED_PTR ptr = (DOIFPILOTED_PTR )instr_ptr;
	
	if (BoxCol::Col_Shooter == Manual_Pilot.ControlledAC2)		//JIM 11Mar99
		instr_ptr += sizeof(DOIFPILOTED);
	else
		instr_ptr += ptr->offset;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doniverts
//Author		Robert Slater
//Date			Thu 20 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doniverts(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("b8");
#endif
	DONIVERTS_PTR ptr = (DONIVERTS_PTR )instr_ptr;
	NEXTMAP_PTR	  mapit;
	int		counter;
	int		i;
	DoPointStruc*	dp = &newco[ptr->vertex];

	counter = ptr->count;

	instr_ptr += sizeof(DONIVERTS);
	mapit = (NEXTMAP_PTR) instr_ptr;

	for (i=0; i < counter; i++)
	{
#ifndef	_NOPOINTS_
		dp->setIMapCoords(mapit->ix,mapit->iy);					//RJS 19May00
#endif
		dp++;

		mapit++;
	}

	instr_ptr = UByteP(mapit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dotrifan
//Author		Robert Slater
//Date			Thu 27 Mar 1997
//
//Description	Crappy test for a fan of triangles......
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dotrifan(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("b9");
#endif
	DOTRIFAN_PTR ptr = (DOTRIFAN_PTR )instr_ptr;

	instr_ptr += sizeof(DOTRIFAN);
	
	HMATERIAL hMaterial;

	if (ptr->material)
		hMaterial=HMATERIAL(Image_Map.GetImageMapPtr((ImageMapNumber)ptr->material));
	else
		hMaterial=HMATERIAL(shape::colour);

	Lib3DPoint*	pRVerts = g_lpLib3d->BeginFan(hMaterial,ptr->edges);
	pRVerts[0]=newco[ptr->rootpnt];
	for (int i=1;i<ptr->edges;i++)
		pRVerts[i]=newco[*instr_ptr++];
	g_lpLib3d->EndFan();

//Old_Code PD 25Nov99	DOTRIFAN_PTR ptr = (DOTRIFAN_PTR )instr_ptr;
//Old_Code PD 25Nov99	int		counter;
//Old_Code PD 25Nov99	UByte	vertex;
//Old_Code PD 25Nov99	int		rootvert;
//Old_Code PD 25Nov99	int		tricnt;
//Old_Code PD 25Nov99	instr_ptr += sizeof(DOTRIFAN);
//Old_Code PD 25Nov99 	rootvert = ptr->rootpnt;
//Old_Code PD 25Nov99 	counter = ptr->edges;
//Old_Code PD 25Nov99 	tricnt = 0;
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 	if (ptr->material)
//Old_Code PD 25Nov99 	{
//Old_Code PD 25Nov99 		DOCREATEIPOLY	tmpinst;
//Old_Code PD 25Nov99 		UByteP			tmpptr;
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 		tmpinst.image_no = ptr->material;
//Old_Code PD 25Nov99 		tmpptr = (UByteP) &tmpinst;
//Old_Code PD 25Nov99 		docreateipoly(tmpptr);
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 		while (counter)
//Old_Code PD 25Nov99 		{
//Old_Code PD 25Nov99 			if (!tricnt)
//Old_Code PD 25Nov99 			{
//Old_Code PD 25Nov99 				tricnt++;
//Old_Code PD 25Nov99 				POLYGON.createvert(newco[rootvert],newco[rootvert].ix,newco[rootvert].iy);
//Old_Code PD 25Nov99 			}
//Old_Code PD 25Nov99 			else
//Old_Code PD 25Nov99 			{
//Old_Code PD 25Nov99 				vertex = *((UByteP) instr_ptr);
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 				POLYGON.createvert(newco[vertex],newco[vertex].ix,newco[vertex].iy);
//Old_Code PD 25Nov99 				counter--;
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 				if (tricnt < 2)
//Old_Code PD 25Nov99 				{
//Old_Code PD 25Nov99 					instr_ptr += sizeof(UByte);
//Old_Code PD 25Nov99 					tricnt++;
//Old_Code PD 25Nov99 				}
//Old_Code PD 25Nov99 				else
//Old_Code PD 25Nov99 				{
//Old_Code PD 25Nov99 					tricnt = 0;
//Old_Code PD 25Nov99 					POLYGON.drawpoly();
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 					if (counter)
//Old_Code PD 25Nov99 					{
//Old_Code PD 25Nov99 						counter++;
//Old_Code PD 25Nov99 						tmpptr = (UByteP) &tmpinst;
//Old_Code PD 25Nov99 						docreateipoly(tmpptr);
//Old_Code PD 25Nov99 					}
//Old_Code PD 25Nov99 				}
//Old_Code PD 25Nov99 			}
//Old_Code PD 25Nov99 		}
//Old_Code PD 25Nov99 	}
//Old_Code PD 25Nov99 	else
//Old_Code PD 25Nov99 	{
//Old_Code PD 25Nov99 		POLYGON.createpoly(shape::colour);
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 		while (counter)
//Old_Code PD 25Nov99 		{
//Old_Code PD 25Nov99 			if (!tricnt)
//Old_Code PD 25Nov99 			{
//Old_Code PD 25Nov99 				POLYGON.createvert(newco[rootvert]);
//Old_Code PD 25Nov99 				tricnt++;
//Old_Code PD 25Nov99 			}
//Old_Code PD 25Nov99 			else
//Old_Code PD 25Nov99 			{
//Old_Code PD 25Nov99 				vertex = *((UByteP) instr_ptr);
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 				POLYGON.createvert(newco[vertex]);
//Old_Code PD 25Nov99 				counter--;
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 				if (tricnt < 2)
//Old_Code PD 25Nov99 				{
//Old_Code PD 25Nov99 					tricnt++;
//Old_Code PD 25Nov99 					instr_ptr += sizeof(UByte);
//Old_Code PD 25Nov99 				}
//Old_Code PD 25Nov99 				else
//Old_Code PD 25Nov99 				{
//Old_Code PD 25Nov99 					tricnt = 0;
//Old_Code PD 25Nov99 					POLYGON.drawpoly();
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 					if (counter)
//Old_Code PD 25Nov99 					{
//Old_Code PD 25Nov99 						counter++;
//Old_Code PD 25Nov99 						POLYGON.createpoly(shape::colour);
//Old_Code PD 25Nov99 					}
//Old_Code PD 25Nov99 				}
//Old_Code PD 25Nov99 			}
//Old_Code PD 25Nov99 		}
//Old_Code PD 25Nov99 	}
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 	instr_ptr += sizeof(UByte);

//DeadCode RJS 23Apr97	_Error.EmitSysErr(__FILE__":Not a real instruction yet.....(DOTRIFAN)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dotrizag
//Author		Robert Slater
//Date			Thu 27 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dotrizag(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("c0");
#endif
	DOTRIZAG_PTR ptr = (DOTRIZAG_PTR )instr_ptr;
	int		tricnt;
	UByte	vertex[3];
	int		counter;
	Bool	clockwise = (Bool) ptr->direction;
	int		p1, p2, p3;

	counter = ptr->edges;
	tricnt = 0;

	instr_ptr += sizeof(DOTRIZAG);

	HMATERIAL hMaterial;

	if (ptr->material)
		hMaterial=HMATERIAL(Image_Map.GetImageMapPtr((ImageMapNumber)ptr->material));
	else
		hMaterial=HMATERIAL(shape::colour);

	DOCREATEIPOLY	tmpinst;
	UByteP			tmpptr;

	tmpinst.image_no = ptr->material;
	tmpptr = (UByteP) &tmpinst;
	docreateipoly(tmpptr);

	while (counter)
	{
		vertex[tricnt] = *((UByteP) instr_ptr);

		counter--;

		if (tricnt < 2)
		{
			tricnt++;
			instr_ptr += sizeof(UByte);
		}
		else
		{
			tricnt = 0;

			if (clockwise)
			{
				p1 = 0;
				p2 = 2;
				p3 = 1;
				clockwise = FALSE;
			}
			else
			{
				p1 = 0;
				p2 = 1;
				p3 = 2;
				clockwise = TRUE;
			}
#ifndef	_NOPOLYS_

			Lib3DPoint*	pRVerts = g_lpLib3d->BeginPoly(hMaterial,3);//RJS 19May00
			*pRVerts++=newco[vertex[p1]];
			*pRVerts++=newco[vertex[p2]];
			*pRVerts++=newco[vertex[p3]];
			g_lpLib3d->EndPoly();
#endif
//deadcode			POLYGON.createvert(newco[vertex[p1]],newco[vertex[p1]].ix,newco[vertex[p1]].iy);
//deadcode			POLYGON.createvert(newco[vertex[p2]],newco[vertex[p2]].ix,newco[vertex[p2]].iy);
//deadcode			POLYGON.createvert(newco[vertex[p3]],newco[vertex[p3]].ix,newco[vertex[p3]].iy);
//deadcode			POLYGON.drawpoly();

			if (counter)
			{
				instr_ptr -= sizeof(UByte);
				counter+=2;

				tmpptr = (UByteP) &tmpinst;
//deadcode				docreateipoly(tmpptr);
			}
		}
	}

	instr_ptr += sizeof(UByte);

//DeadCode RJS 23Apr97 	_Error.EmitSysErr(__FILE__":Not a real instruction yet.....(DOTRIZAG)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dotrifanflat
//Author		Robert Slater
//Date			Wed 16 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dotrifanflat(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("c1");
#endif
	DOTRIFANFLAT_PTR ptr = (DOTRIFANFLAT_PTR )instr_ptr;
	instr_ptr += sizeof(DOTRIFANFLAT);

	HMATERIAL hMaterial;

	if (ptr->material)
		hMaterial=HMATERIAL(Image_Map.GetImageMapPtr((ImageMapNumber)ptr->material));
	else
		hMaterial=HMATERIAL(shape::colour);

	Lib3DPoint*	pRVerts = g_lpLib3d->BeginFan(hMaterial,ptr->edges);
	pRVerts[0]=newco[ptr->rootpnt];
	for (int i=1;i<ptr->edges;i++)
		pRVerts[i]=newco[*instr_ptr++];
	g_lpLib3d->EndFan();

//Old_Code PD 25Nov99 	DOTRIFANFLAT_PTR ptr = (DOTRIFANFLAT_PTR )instr_ptr;
//Old_Code PD 25Nov99 	int		counter;
//Old_Code PD 25Nov99 	UByte	vertex;
//Old_Code PD 25Nov99 	int		rootvert;
//Old_Code PD 25Nov99 	int		tricnt;
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 	instr_ptr += sizeof(DOTRIFANFLAT);
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 	rootvert = ptr->rootpnt;
//Old_Code PD 25Nov99 	counter = ptr->edges;
//Old_Code PD 25Nov99 	tricnt = 0;
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 	if (ptr->material)
//Old_Code PD 25Nov99 	{
//Old_Code PD 25Nov99 		DOCREATEIPOLY	tmpinst;
//Old_Code PD 25Nov99 		UByteP			tmpptr;
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 		tmpinst.image_no = ptr->material;
//Old_Code PD 25Nov99 		tmpptr = (UByteP) &tmpinst;
//Old_Code PD 25Nov99 		docreateipoly(tmpptr);
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 		while (counter)
//Old_Code PD 25Nov99 		{
//Old_Code PD 25Nov99 			if (!tricnt)
//Old_Code PD 25Nov99 			{
//Old_Code PD 25Nov99 				tricnt++;
//Old_Code PD 25Nov99 				POLYGON.createvert(newco[rootvert],newco[rootvert].ix,newco[rootvert].iy);
//Old_Code PD 25Nov99 			}
//Old_Code PD 25Nov99 			else
//Old_Code PD 25Nov99 			{
//Old_Code PD 25Nov99 				vertex = *((UByteP) instr_ptr);
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 				POLYGON.createvert(newco[vertex],newco[vertex].ix,newco[vertex].iy);
//Old_Code PD 25Nov99 				counter--;
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 				if (tricnt < 2)
//Old_Code PD 25Nov99 				{
//Old_Code PD 25Nov99 					tricnt++;
//Old_Code PD 25Nov99 					instr_ptr += sizeof(UByte);
//Old_Code PD 25Nov99 				}
//Old_Code PD 25Nov99 				else
//Old_Code PD 25Nov99 				{
//Old_Code PD 25Nov99 					tricnt = 0;
//Old_Code PD 25Nov99 					POLYGON.drawpoly();
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 					if (counter)
//Old_Code PD 25Nov99 					{
//Old_Code PD 25Nov99 						counter++;
//Old_Code PD 25Nov99 						tmpptr = (UByteP) &tmpinst;
//Old_Code PD 25Nov99 						docreateipoly(tmpptr);
//Old_Code PD 25Nov99 					}
//Old_Code PD 25Nov99 				}
//Old_Code PD 25Nov99 			}
//Old_Code PD 25Nov99 		}
//Old_Code PD 25Nov99 	}
//Old_Code PD 25Nov99 	else
//Old_Code PD 25Nov99 	{
//Old_Code PD 25Nov99 		POLYGON.createpoly(shape::colour);
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 		while (counter)
//Old_Code PD 25Nov99 		{
//Old_Code PD 25Nov99 			if (!tricnt)
//Old_Code PD 25Nov99 			{
//Old_Code PD 25Nov99 				tricnt++;
//Old_Code PD 25Nov99 				POLYGON.createvert(newco[rootvert]);
//Old_Code PD 25Nov99 			}
//Old_Code PD 25Nov99 			else
//Old_Code PD 25Nov99 			{
//Old_Code PD 25Nov99 				vertex = *((UByteP) instr_ptr);
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 				POLYGON.createvert(newco[vertex]);
//Old_Code PD 25Nov99 				counter--;
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 				if (tricnt < 2)
//Old_Code PD 25Nov99 				{
//Old_Code PD 25Nov99 					tricnt++;
//Old_Code PD 25Nov99 					instr_ptr += sizeof(UByte);
//Old_Code PD 25Nov99 				}
//Old_Code PD 25Nov99 				else
//Old_Code PD 25Nov99 				{
//Old_Code PD 25Nov99 					tricnt = 0;
//Old_Code PD 25Nov99 					POLYGON.drawpoly();
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 					if (counter)
//Old_Code PD 25Nov99 					{
//Old_Code PD 25Nov99 						counter++;
//Old_Code PD 25Nov99 						POLYGON.createpoly(shape::colour);
//Old_Code PD 25Nov99 					}
//Old_Code PD 25Nov99 				}
//Old_Code PD 25Nov99 			}
//Old_Code PD 25Nov99 		}
//Old_Code PD 25Nov99 	}
//Old_Code PD 25Nov99 
//Old_Code PD 25Nov99 	instr_ptr += sizeof(UByte);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dotrizagflat
//Author		Robert Slater
//Date			Thu 27 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dotrizagflat(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("c2");
#endif
	DOTRIZAGFLAT_PTR ptr = (DOTRIZAGFLAT_PTR )instr_ptr;
 	int		tricnt;
	UByte	vertex[3];
	int		counter;
	Bool	clockwise = (Bool) ptr->direction;
	int		p1,p2,p3;

	counter = ptr->edges;
	tricnt = 0;

	instr_ptr += sizeof(DOTRIZAGFLAT);

	HMATERIAL hMaterial;

	if (ptr->material)
		hMaterial=HMATERIAL(Image_Map.GetImageMapPtr((ImageMapNumber)ptr->material));
	else
		hMaterial=HMATERIAL(shape::colour);

	DOCREATEIPOLY	tmpinst;
	UByteP			tmpptr;

	tmpinst.image_no = ptr->material;
	tmpptr = (UByteP) &tmpinst;
//deadcode	docreateipoly(tmpptr);

	while (counter)
	{
		vertex[tricnt] = *((UByteP) instr_ptr);

		counter--;

		if (tricnt < 2)
		{
			tricnt++;
			instr_ptr += sizeof(UByte);
		}
		else
		{
			tricnt = 0;

			if (clockwise)
			{
				p1 = 0;
				p2 = 2;
				p3 = 1;
				clockwise = FALSE;
			}
			else
			{
				p1 = 0;
				p2 = 1;
				p3 = 2;
				clockwise = TRUE;
			}
#ifndef	_NOPOLYS_

			Lib3DPoint*	pRVerts = g_lpLib3d->BeginPoly(hMaterial,4);//RJS 19May00
			*pRVerts++=newco[vertex[p1]];
			*pRVerts++=newco[vertex[p2]];
			*pRVerts++=newco[vertex[p3]];
			g_lpLib3d->EndPoly();
#endif
			if (counter)
			{
				instr_ptr -= sizeof(UByte);
				counter+=2;

				tmpptr = (UByteP) &tmpinst;
//deadcode					docreateipoly(tmpptr);
			}
		}
	}
	instr_ptr += sizeof(UByte);

//DeadCode RJS 23Apr97 	_Error.EmitSysErr(__FILE__":Not a real instruction yet.....(DOTRIZAGFLAT)\n");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dostretchpoint
//Author		Robert Slater
//Date			Mon 9 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dostretchpoint(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("c3");
#endif
	DOSTRETCHPOINT_PTR  ptr = (DOSTRETCHPOINT_PTR )instr_ptr;
	int					nokills = GlobalAdptr[ptr->killflag];
	Float				xdiff, ydiff, zdiff;
	int					killfrac,killdiff;
	float				r16 = 1./16.;

 	newco[ptr->outpoint] = newco[ptr->minpoint];

	if (nokills)
	{
		D3DVALUE	oldX,oldY,oldZ;

		newco[ptr->minpoint].getPosition(oldX,oldY,oldZ);

		xdiff = (newco[ptr->maxpoint].getPosX() - oldX)*r16;
		ydiff = (newco[ptr->maxpoint].getPosY() - oldY)*r16;
		zdiff = (newco[ptr->maxpoint].getPosZ() - oldZ)*r16;

		killfrac = nokills / 16;
		killdiff = nokills - (killfrac * 16);

		ydiff *= (killfrac+1);
		xdiff *= (killdiff+1);
		zdiff *= (killdiff+1);

#ifndef	_NOPOINTS_
		newco[ptr->outpoint].setPosition(	oldX+xdiff,
											oldY+ydiff,
											oldZ+zdiff	);		//RJS 19May00
#endif
	}

	instr_ptr += sizeof(DOSTRETCHPOINT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dostretchmap
//Author		Robert Slater
//Date			Mon 9 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dostretchmap(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("c4");
#endif
	DOSTRETCHMAP_PTR ptr = (DOSTRETCHMAP_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP			 adptr = (UByteP) object_obj3d->AnimPtr;
	int				 nokills = GlobalAdptr[ptr->killflag];
	Float			 xdiff, ydiff, zdiff;
	int				 killfrac,killdiff;
	float			r16 = 1./16.;

 	newco[ptr->outpoint] = newco[ptr->minpoint];

	if (nokills)
	{
		SWord	oldIX, oldIY;

		newco[ptr->minpoint].getIMapCoords(oldIX,oldIY);		//RJS 19May00

		xdiff = newco[ptr->maxpoint].getIMapX() - oldIX;
		ydiff = newco[ptr->maxpoint].getIMapY() - oldIY;

		xdiff *= r16;
		ydiff *= r16;

		killfrac = nokills / 16;
		killdiff = nokills - (killfrac * 16);

		ydiff *= (killfrac+1);
		xdiff *= (killdiff+1);

#ifndef	_NOPOINTS_
		newco[ptr->outpoint].setIMapCoords(	oldIX + xdiff,
											oldIY + ydiff	);
#endif
	}

	instr_ptr += sizeof(DOSTRETCHMAP);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doflipvector
//Author		Robert Slater
//Date			Wed 30 Jul 1997
//
//Description	Negates known vector intensity for two-sided flat polys
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doflipvector(UByte *& instr_ptr)		//PD 13Nov97
{
#ifdef	_PROCDEBUG_
	Bollox("c5");
#endif
	DOFLIPVECTOR_PTR ptr=(DOFLIPVECTOR_PTR )instr_ptr;
	DoPointStruc& dp=newco[ptr->vertex];
#ifndef	_NOPOINTS_

	dp.setNormal(-dp.getNormalX(),-dp.getNormalY(),-dp.getNormalZ());//RJS 19May00
#endif
	instr_ptr+=sizeof(DOFLIPVECTOR);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doflipnvec
//Author		Robert Slater
//Date			Wed 30 Jul 1997
//
//Description	Copys a temporary vector into a real do-point
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doflipnvec(UByte *& instr_ptr)			//PD 13Nov97
{
#ifdef	_PROCDEBUG_
	Bollox("c6");
#endif
	DOFLIPNVEC_PTR ptr=(DOFLIPNVEC_PTR )instr_ptr;
	DoPointStruc* pDpFrom=newco+ptr->vertex;
	DoPointStruc* pDpTo=newco+ptr->nopoints;
//DeadCode RJS 2Jun00 	int nopoints=ptr->nopoints;
//DeadCode RJS 2Jun00 	for (int count=nopoints; count >0; count--)
//DeadCode RJS 2Jun00 	{
//DeadCode RJS 2Jun00 		DoPointStruc& dp=*pDp++;
//DeadCode RJS 2Jun00 
//DeadCode RJS 2Jun00 		dp.setNormal(-dp.getNormalX(),-dp.getNormalY(),-dp.getNormalZ());//RJS 19May00
//DeadCode RJS 2Jun00 	}

	instr_ptr+=sizeof(DOFLIPNVEC);

#ifndef	_NOPOINTS_
	pDpTo->setNormal(pDpFrom->getNormalX(),pDpFrom->getNormalY(),pDpFrom->getNormalZ());
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		domorphpoint
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
 void shape::domorphpoint(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("c7");
#endif
	DOMORPHPOINT_PTR  ptr = (DOMORPHPOINT_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	DOPOINT			ptr2;
	UByteP			instptr2 = (UByteP) &ptr2;
	SLong			TotDist;
	SWord			sin_ang,cos_ang;
	SLong			xdelta, ydelta, zdelta;
	UByteP			timedeltap = &GlobalAdptr[ptr->framecntoffset];//RJS 21Apr99
	UWord			timedelta = *((UWordP)timedeltap);

	xdelta = (timedelta*(ptr->mxcoord - ptr->xcoord))/ptr->growtime;
	ydelta = (timedelta*(ptr->mycoord - ptr->ycoord))/ptr->growtime;
	zdelta = (timedelta*(ptr->mzcoord - ptr->zcoord))/ptr->growtime;

	ptr2.vertex = ptr->vertex;
	ptr2.xcoord = ptr->xcoord + xdelta;
	ptr2.ycoord = ptr->ycoord + ydelta;
	ptr2.zcoord = ptr->zcoord + zdelta;

//DEADCODE RJS 5/15/00 	if (ptr->haswind)
//DEADCODE RJS 5/15/00 	{
//DEADCODE RJS 5/15/00 		//rdh need to change to MiG Alley wind
//DEADCODE RJS 5/15/00 //		TotDist = (Timer_Code.FRAMETIME * MMC.wind.speed)/10;
//DEADCODE RJS 5/15/00 //		Math_Lib.high_sin_cos((ANGLES )MMC.wind.direction,sin_ang,cos_ang);
//DEADCODE RJS 5/15/00 //		xdelta = (TotDist*sin_ang)>>15;
//DEADCODE RJS 5/15/00 //		zdelta = (TotDist*cos_ang)>>15;
//DEADCODE RJS 5/15/00 //
//DEADCODE RJS 5/15/00 //		ptr2.xcoord += xdelta;
//DEADCODE RJS 5/15/00 //		ptr2.zcoord += zdelta;
//DEADCODE RJS 5/15/00 	}

	dopoint(instptr2);

	instr_ptr += sizeof(DOMORPHPOINT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		domorphnpoints
//Author		Robert Slater
//Date			Mon 8 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::domorphnpoints(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("c8");
#endif
	DOMORPHNPOINTS_PTR  ptr = (DOMORPHNPOINTS_PTR )instr_ptr;
	MORPHNNEXT_PTR		ptr2;
	SLong			xdelta, ydelta, zdelta;
	UByteP			timedeltap = &GlobalAdptr[ptr->framecntoffset];//RJS 21Apr99
	UWord			timedelta = *((UWordP)timedeltap);
	ULong			count;
	SLong			timefrac = (timedelta<<13)/ptr->growtime;
	DoPointStruc*	dp = &newco[ptr->startvertex];

	count = ptr->nopoints;										//RJS 01Dec99
																//RJS 01Dec99
	instr_ptr += sizeof(DOMORPHNPOINTS);						//RJS 01Dec99
	ptr2 = (MORPHNNEXT_PTR) instr_ptr;							//RJS 01Dec99
	instr_ptr += (sizeof(MORPHNNEXT)*count);					//RJS 01Dec99
																//RJS 01Dec99
	if (timefrac)
	{
		float	fTimeFrac = float(timefrac)*0.0001220703125;	//RJS 17May00
		while (count)												//RJS 01Dec99
		{
#ifndef	_NOPOINTS_
			dp->setPosition(float(ptr2->xcoord) + (fTimeFrac*float(ptr2->mxcoord - ptr2->xcoord)),
							float(ptr2->ycoord) + (fTimeFrac*float(ptr2->mycoord - ptr2->ycoord)),
							float(ptr2->zcoord) + (fTimeFrac*float(ptr2->mzcoord - ptr2->zcoord))	);//RJS 19May00
#endif
																	//RJS 01Dec99
			ptr2++;													//RJS 01Dec99
			count--;												//RJS 01Dec99
			dp++;													//RJS 01Dec99
		}
	}
	else
	{
		while (count)												//RJS 03Dec99
		{															//RJS 03Dec99
#ifndef	_NOPOINTS_
			dp->setPosition(ptr2->xcoord,ptr2->ycoord,ptr2->zcoord);//RJS 19May00
#endif
																	//RJS 03Dec99
			ptr2++;													//RJS 03Dec99
			count--;												//RJS 03Dec99
			dp++;													//RJS 03Dec99
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		douserealtime
//Author		Robert Slater
//Date			Wed 10 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::douserealtime(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("c9");
#endif
	DOUSEREALTIME_PTR  ptr = (DOUSEREALTIME_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	ULongP			btimep = (ULongP) &GlobalAdptr[ptr->birthtimeoffset];//RJS 21Apr99
	ULong			btime = *btimep;
	int				theTime = View_Point->TotalDrawFrameTime();

	if (btime == 0)												//RJS 16Nov98
		*btimep = theTime;										//RJS 05Apr00
 	else
 	{
		if (	ptr->loopset									//RJS 15Dec99
			&&	((theTime-btime)>ptr->looptime))				//RJS 05Apr00
 			*btimep = theTime;									//RJS 05Apr00
 	}

	instr_ptr += sizeof(DOUSEREALTIME);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dotimerphase
//Author		Robert Slater
//Date			Wed 10 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dotimerphase(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("d0");
#endif
	DOTIMERPHASE_PTR  ptr = (DOTIMERPHASE_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	ULongP			btimep = (ULongP) &GlobalAdptr[ptr->birthtimeoffset];//RJS 21Apr99
	UWordP			dtimep = (UWordP) &GlobalAdptr[ptr->deltatimeoffset];//RJS 21Apr99
	ULong			btime = *btimep;
//DeadCode RJS 02Dec99	UWord			dtime = *dtimep;
	UWord			nophases = ptr->nophases;
	UWord			count;
	ULong			phasetdelta;
	UWord			lowtime = 0;
	ULong			tdelta;
	TPHASESTEP_PTR	ptr2;
	UByteP			instr_ptr2 = instr_ptr;

	tdelta = View_Point->TotalDrawFrameTime() - btime;

	instr_ptr2 += sizeof(DOTIMERPHASE);
	ptr2 = (TPHASESTEP_PTR) instr_ptr2;
	instr_ptr2 += (nophases * sizeof(TPHASESTEP));

	for (count=0; count < nophases; count++)
	{
		phasetdelta = ptr2->timedelta;
		if (phasetdelta == 65535)
			tdelta = 65534;

		if (	(tdelta >= lowtime)
			&&	(tdelta < phasetdelta)	)
		{
			*dtimep = (UWord)(tdelta - lowtime);
			instr_ptr += ptr2->objjump;
			instr_ptr2 = instr_ptr;
			break;
		}

		lowtime = phasetdelta;
		ptr2++;
	}

	instr_ptr = instr_ptr2;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dowheeldamage
//Author		Robert Slater
//Date			Thu 18 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dowheeldamage(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("d1");
#endif
	DOWHEELDAMAGE_PTR  ptr = (DOWHEELDAMAGE_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	UByteP				oldinstr_ptr = instr_ptr;
	MinAnimData*		mad = (MinAnimData*) GlobalAdptr;

	if (mad->itemstate != DEAD)
	{
		if (GlobalAdptr[ptr->suspoffset])
		{
			if (GlobalAdptr[ptr->underoffset])
			{
				ULong	damage = (GlobalAdptr[ptr->suspoffset] * ((GlobalAdptr[ptr->underoffset]<<8)/ptr->animmax))>>8;
				if (damage > BS_DEAD)
					damage = BS_DEAD;

				SHAPE.ForceDamage(	object_obj3d->ItemPtr,
									object_obj3d->ItemPtr,
									&GlobalAdptr[ptr->damageoffset],//RJS 21Apr99
									(BitStates) damage	);

/*				if (damage >= ptr->threshold)
				{
					if (ptr->subdamageoffset)
					{
						damage -= ptr->threshold;
						damage += GlobalAdptr[ptr->subdamageoffset];
						if (damage > BS_DEAD)
							damage = BS_DEAD;


						SHAPE.ForceDamage(	object_obj3d->ItemPtr,
											&GlobalAdptr[ptr->subdamageoffset],
											(BitStates) damage	);
					}
				}*/
			}
		}

		instr_ptr = oldinstr_ptr;
	}
	instr_ptr += sizeof(DOWHEELDAMAGE);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doblobline
//Author		Robert Slater
//Date			Thu 11 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doblobline(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("d2");
#endif
	LINETYPE	ltLine;
	struct		vertex	startVertex,endVertex;

 	SWord start_vertex,end_vertex;								//PD 08Jan96
	Float	z0,z1;
 	
 	DOBLOBLINE_PTR ptr = (DOBLOBLINE_PTR )instr_ptr;
 
 	start_vertex = (SWord )ptr->start_vertex;					//RJS 10Mar97
 	end_vertex	 = (SWord )ptr->end_vertex;					//RJS 10Mar97

	g_lpLib3d->DrawLine(HMATERIAL(shape::colour),newco[start_vertex],newco[end_vertex]);
 
	instr_ptr += sizeof(DOBLOBLINE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dolight
//Author		Robert Slater
//Date			Thu 18 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dolight(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("d3");
#endif
	DOLIGHT_PTR	ptr = (DOLIGHT_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP		adptr = (UByteP) object_obj3d->AnimPtr;
	UWord		frametime;
	LIGHTDATA_PTR	ldataptr = (LIGHTDATA_PTR) SHAPE.GetLightDataPtr((ShapeNum)object_obj3d->Shape,ptr->lightoffset);

	if (ldataptr)
	{
//DeadCode RJS 15Feb99 		DOPOINT dopointno;
//DeadCode RJS 15Feb99 		UByteP	instr_ptr2 = (UByteP) &dopointno;
//DeadCode RJS 15Feb99 		Colour	colon = (Colour) ldataptr->colouron;
//DeadCode RJS 15Feb99 		Colour	coloff = (Colour) ldataptr->colouroff;
//DeadCode RJS 15Feb99 		DOSETCOLOUR256	tmpinst3;								//RJS 06Jan98
//DeadCode RJS 15Feb99 		UByteP			tmpinstptr;
//DeadCode RJS 15Feb99 		Bool			issmooth = FALSE;
//DeadCode RJS 15Feb99 		UWord			radius = ptr->radius;
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 		tmpinst3.spread = 0;									//RJS 06Jan98
//DeadCode RJS 15Feb99 		tmpinst3.imap = 0xFF;									//RJS 06Jan98
//DeadCode RJS 15Feb99 		tmpinst3.basecolour = coloff<<1;						//RJS 06Jan98
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 		if (ptr->animoff)
//DeadCode RJS 15Feb99 		{
//DeadCode RJS 15Feb99 			if (ptr->isword)
//DeadCode RJS 15Feb99 				frametime = *((UWordP)&adptr[ptr->animoff]);
//DeadCode RJS 15Feb99 			else
//DeadCode RJS 15Feb99 				frametime = adptr[ptr->animoff];
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 			if (frametime >= ptr->timeoff)
//DeadCode RJS 15Feb99 			{
//DeadCode RJS 15Feb99 				if (frametime < ptr->timeup)
//DeadCode RJS 15Feb99 					tmpinst3.basecolour = coloff<<1;			//RJS 06Jan98
//DeadCode RJS 15Feb99 				else
//DeadCode RJS 15Feb99 				{
//DeadCode RJS 15Feb99 					if (frametime < ptr->timeon)
//DeadCode RJS 15Feb99 					{
//DeadCode RJS 15Feb99 						tmpinst3.basecolour = colon<<1;			//RJS 06Jan98
//DeadCode RJS 15Feb99 						radius += 6;
//DeadCode RJS 15Feb99 						issmooth = TRUE;
//DeadCode RJS 15Feb99 					}
//DeadCode RJS 15Feb99 				}
//DeadCode RJS 15Feb99 			}
//DeadCode RJS 15Feb99 		}
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 		tmpinstptr = (UByteP) &tmpinst3;						//RJS 06Jan98
//DeadCode RJS 15Feb99 		dosetcolour256(tmpinstptr);								//RJS 06Jan98
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 		if (ptr->radius)
//DeadCode RJS 15Feb99 		{
//DeadCode RJS 15Feb99 			dopointno.xcoord = ldataptr->xpos;
//DeadCode RJS 15Feb99 			dopointno.ycoord = ldataptr->ypos;
//DeadCode RJS 15Feb99 			dopointno.zcoord = ldataptr->zpos;
//DeadCode RJS 15Feb99 			dopointno.vertex = 0;
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 			dopoint(instr_ptr2);
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 			SHAPE.drawsphere(	0,
//DeadCode RJS 15Feb99 	 							radius,
//DeadCode RJS 15Feb99  								shape::colour,
//DeadCode RJS 15Feb99  								0,
//DeadCode RJS 15Feb99  								1,
//DeadCode RJS 15Feb99  								4,
//DeadCode RJS 15Feb99  								issmooth,
//DeadCode RJS 15Feb99 								0,
//DeadCode RJS 15Feb99 								LUM_MAX,
//DeadCode RJS 15Feb99 								0);								//RJS 21Jan98
//DeadCode RJS 15Feb99 		}
		DOPOINT dopointno;
		UByteP	instr_ptr2 = (UByteP) &dopointno;
		SWord	minx,miny,maxx,maxy;
		UWord	radius = ptr->radius;

		minx = ptr->minx;
		miny = ptr->miny;
		maxx = ptr->minx + ptr->width;
		maxy = ptr->miny + ptr->height;

		if (ptr->animoff)
		{
			if (ptr->isword)
				frametime = *((UWordP)&GlobalAdptr[ptr->animoff]);
			else
				frametime = GlobalAdptr[ptr->animoff];

			if (frametime >= ptr->timeoff)
			{
				if (frametime < ptr->timeup)
				{
					//Fade...

//hmmm...					oldGlobalAlpha = current_screen->DoSetGlobalAlpha();
				}
				else
				{
					if (frametime < ptr->timeon)
					{
						//On...
						ImageMapDescPtr imptr;
						SLong			nofx;
						SLong			stepy, stepx;

						imptr = Image_Map.GetImageMapPtr((ImageMapNumber)ptr->imagemap);
						
						nofx = imptr->w / ptr->width;

						stepy = 1 / nofx;
						stepx = 1 - (stepy*nofx);

						minx += stepx*ptr->width;
						miny += stepy*ptr->height;

						maxx = minx + ptr->width;
						maxy = miny + ptr->height;

						radius += 3;
					}
				}
			}
		}

		if (ptr->radius)
		{
			dopointno.vertex = 0;
			dopointno.xcoord = ldataptr->xpos;
			dopointno.ycoord = ldataptr->ypos;
			dopointno.zcoord = ldataptr->zpos;

			dopoint(instr_ptr2);

			SHAPE.imapsphere(0,radius,(ImageMapNumber)ptr->imagemap,minx,miny,maxx,maxy);
		}
	}

	instr_ptr += sizeof(DOLIGHT);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dolighttimer
//Author		Robert Slater
//Date			Tue 6 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dolighttimer(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("d4");
#endif
	DOLIGHTTIMER_PTR	ptr = (DOLIGHTTIMER_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	UWordP				wordptr = (UWordP)&GlobalAdptr[ptr->animoff];
	UWord				frametime;
	LightTimerTypes		timertype = (LightTimerTypes)ptr->timertype;
//DeadCode RJS 20Oct00 	Bool				islit = TRUE;

	if (	(timertype&LGT_ONLY_DARK)
		&&	!Three_Dee.lightson			)
	{
		frametime = 0;
	}
	else
	{
		if (ptr->isword)
			frametime = *wordptr;
		else
			frametime = GlobalAdptr[ptr->animoff];				//RJS 21Apr99

		//frametime of 0 means switched off...					//DAW 17Feb99
		if (frametime && (timertype&LGT_PERIODIC))				//DAW 17Feb99
		{
			frametime += View_Point->DrawFrameTime();
			if (frametime > ptr->duration)
				frametime = Timer_Code.FRAMETIME;				//DAW 17Feb99
		}
	}

	if (ptr->isword)
		*wordptr = frametime;
	else
		GlobalAdptr[ptr->animoff] = frametime;					//RJS 21Apr99

	instr_ptr += sizeof(DOLIGHTTIMER);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dodigitdial
//Author		Robert Slater
//Date			Thu 8 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dodigitdial(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("d5");
#endif
	DODIGITDIAL_PTR	ptr = (DODIGITDIAL_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	UWordP				wordptr = (UWordP)&GlobalAdptr[ptr->animoff];
	Float				dx, dy, dz;
	Float				dx2, dy2, dz2;
	DoPointStruc		dopoint0, dopoint1, dopoint2, dopoint3;
	int					i;
	int					nodigits = ptr->nodigits;
	ImageMapNumber		imapno;
	SWord				minx,miny,maxx,maxy;
	UWord				theno = *wordptr;
	UByteP				digits;
	UWord				thenoleft;
	int					dcnt = 0;
	Float				digdiv = 1.0 / Float(nodigits);

	digits = new UByte[nodigits];
	dcnt = nodigits-1;

	while (dcnt > -1)
	{
		thenoleft = theno;
		theno /= 10;

		thenoleft -= (theno*10);

		digits[dcnt--] = thenoleft;
	}

	imapno = (ImageMapNumber) ptr->imagemap;
	ImageMapDescPtr imptr = Image_Map.GetImageMapPtr(imapno);
	SLong	noxframes = imptr->w / ptr->width;
	SLong	stepy,stepx;

	D3DVALUE	v0x,v0y,v0z;
	D3DVALUE	v1x,v1y,v1z;
	D3DVALUE	v2x,v2y,v2z;
	D3DVALUE	v3x,v3y,v3z;

	newco[ptr->vertex0].getPosition(v0x,v0y,v0z);				//RJS 19May00
	newco[ptr->vertex1].getPosition(v1x,v1y,v1z);				//RJS 19May00
	newco[ptr->vertex2].getPosition(v2x,v2y,v2z);				//RJS 19May00
	newco[ptr->vertex3].getPosition(v3x,v3y,v3z);				//RJS 19May00

	dx = v1x - v0x;												//RJS 19May00
	dy = v1y - v0y;												//RJS 19May00
	dz = v1z - v0z;												//RJS 19May00

	dx2 = v2x - v3x;											//RJS 19May00
	dy2 = v2y - v3y;											//RJS 19May00
	dz2 = v2z - v3z;											//RJS 19May00

	dx *= digdiv;
	dy *= digdiv;
	dz *= digdiv;

	dx2 *= digdiv;
	dy2 *= digdiv;
	dz2 *= digdiv;

	dopoint1 = newco[ptr->vertex0];
	dopoint2 = newco[ptr->vertex3];

	maxx = ptr->width;
	minx = 0;
#ifndef	_NOPOINTS_

	for (i=0; i < nodigits; i++)
	{
		stepy = digits[i]/noxframes;
		stepx = digits[i] - (stepy*noxframes);

		miny = 32 + (stepy * ptr->height);		//poop cheat!
		minx = stepx * ptr->width;
		maxx = minx + ptr->width;
		maxy = miny + ptr->height;

		dopoint0 = dopoint1;
		dopoint1.incPos(dx,dy,dz);								//RJS 17Oct00
//DeadCode RJS 17Oct00 		dopoint1.setPosition(v0x+dx,v0y+dy,v0z+dz);

		dopoint3 = dopoint2;
		dopoint2.incPos(dx2,dy2,dz2);							//RJS 17Oct00
//DeadCode RJS 17Oct00 		dopoint2.setPosition(v3x+dx2,v3y+dy2,v3z+dz2);			//RJS 19May00

		// draw it.....
		dopoint3.setIMapCoords(minx,miny);						//RJS 19May00
		dopoint2.setIMapCoords(maxx,miny);						//RJS 19May00
		dopoint1.setIMapCoords(maxx,maxy);						//RJS 19May00
		dopoint0.setIMapCoords(minx,maxy);						//RJS 19May00
#ifndef	_NOPOLYS_

		Lib3DPoint*	pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),4);//RJS 19May00
		pRVerts[0]=dopoint3;
		pRVerts[1]=dopoint2;
		pRVerts[2]=dopoint1;
		pRVerts[3]=dopoint0;
		g_lpLib3d->EndPoly();
#endif
	}
#endif
	delete digits;

	instr_ptr += sizeof(DODIGITDIAL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		donianimverts
//Author		Robert Slater
//Date			Tue 13 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::donianimverts(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("d6");
#endif
	DONIANIMVERTS_PTR	ptr = (DONIANIMVERTS_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	NEXTMAP_PTR			mapit;
	int					counter;
//DeadCode RJS 23Feb00 	int					vertex;
	int					i;
	UByte				frameno = GlobalAdptr[ptr->animoff];
	int					minx, miny;
	int					nofx;
	int					stepx,stepy;
	int					animscale = ptr->factor;
	DoPointStruc*		dp = &newco[ptr->vertex];					//RJS 22Feb00

	if (ptr->isthresh)
	{
		if (frameno > animscale)
			frameno = 1;
		else
			frameno = 0;
	}
	else
	{
		frameno /= animscale;
		if (ptr->mapscale)
		{
			UByte	totframes = frameno;

			frameno /= ptr->mapscale;
			frameno = totframes - (frameno * ptr->mapscale);
		}
	}

	nofx = ptr->noxframes;

	stepy = frameno/nofx;
	stepx = frameno - (stepy*nofx);

	miny = stepy * ptr->framewy;
	minx = stepx * ptr->framewx;

	instr_ptr += sizeof(DONIANIMVERTS);

	counter = ptr->count;
//DeadCode RJS 22Feb00	vertex = ptr->vertex;

	mapit = (NEXTMAP_PTR) instr_ptr;
	for (i=0; i < counter; i++)
	{
//DeadCode RJS 22Feb00		mapit = (NEXTMAP_PTR) instr_ptr;

#ifndef	_NOPOINTS_
		dp->setIMapCoords(SWord(minx+mapit->ix),SWord(miny+mapit->iy));//RJS 19May00
#endif

		dp++;													//RJS 23Feb00
		mapit++;												//RJS 23Feb00
	}
	instr_ptr = (UByteP)mapit;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dosetluminosity
//Author		Robert Slater
//Date			Tue 20 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dosetluminosity(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("d7");
#endif
	DOSETLUMINOSITY_PTR	ptr = (DOSETLUMINOSITY_PTR) instr_ptr;
//DeadCode RJS 21Apr99 	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	UByte				depth;

	if (ptr->animoff)
		depth = GlobalAdptr[ptr->animoff] / ptr->animscale;
	else
		depth = ptr->brightness;

	if (depth > LUM_MAX)
		depth = LUM_MAX;

	g_lpLib3d->SetGlobal(TOGGLE_GLOBALLUMINOSITY,ULong(depth));

	instr_ptr += sizeof(DOSETLUMINOSITY);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dobitsoffcock
//Author		Robert Slater
//Date			Fri 23 Jan 1998
//
//Description	Check for cockpit detail....
//				If detail bit flag is set, then it means we want to skip
//				the draw.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dobitsoffcock(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("d8");
#endif
	DOBITSOFFCOCK_PTR	ptr = (DOBITSOFFCOCK_PTR )instr_ptr;
//DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr;
	ULong	flag = *((ULongP)&GlobalAdptr[ptr->animflag]);

	flag >>= ptr->bitflag;
	flag &= 1;

	if (!flag)
		instr_ptr += ptr->offset;
	else
		instr_ptr += sizeof(DOBITSOFFCOCK);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doheathaze
//Author		Robert Slater
//Date			Fri 30 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doheathaze(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("d9");
#endif
	DOHEATHAZE_PTR	ptr = (DOHEATHAZE_PTR) instr_ptr;
	SWord			colour;
	SWord			radius = ptr->radius;

	SWord			minx, maxx;
	SWord			miny, maxy;
	SWord			width, height;

	radius /= 2;

	minx = ptr->minx;							
	miny = ptr->miny;						 	
	width = ptr->width;							
	height = ptr->height;						

	SHAPE.AnimMap(GlobalAdptr,ptr->image,ptr->animflag,ptr->animscale,minx,miny,width,height);

	maxx = minx + width - 1;							
	maxy = miny + height;	

	SHAPE.imapsphere(ptr->vertex,radius,(ImageMapNumber)ptr->image,minx,miny,maxx,maxy);

	instr_ptr += sizeof(DOHEATHAZE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doifhard3d
//Author		Robert Slater
//Date			Wed 4 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doifhard3d(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("e0");
#endif
	DOIFHARD3D_PTR	ptr = (DOIFHARD3D_PTR) instr_ptr;

//	if (doingHW3D)												//PD 19Jun98
		instr_ptr += ptr->offset;
//	else
//		instr_ptr += sizeof(DOIFHARD3D);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		domorphnsphrs
//Author		Robert Slater
//Date			Tue 24 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::domorphnsphrs(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("e1");
#endif
	DOMORPHNSPHRS_PTR ptr = (DOMORPHNSPHRS_PTR )instr_ptr;
	SLong		 radius;
//DeadCode RJS 21Apr99 	UByteP		adptr = (UByteP) object_obj3d->AnimPtr;
	UWord		timeframe;
	SLong		timefrac;
	int			lumtype;
	int			transp;
	int			growth = ptr->MrphGrowtime;
	int			delta;
	UByte		animflag;
	UByte		colour = ptr->colour;
	int			randcol;
	int			count = ptr->count;
	int			i = 0;
	MORPHSPHNEXT_PTR	ptr2;
	int			animscale = ptr->animscale;
//DeadCode RJS 20Oct00 	int			vertex = ptr->vertex;

	instr_ptr += sizeof(DOMORPHNSPHRS);

	lumtype = ptr->lumtype;
	transp = ptr->transp;

	timeframe = *((UWordP)&GlobalAdptr[ptr->MrphAnim]);
	timefrac = (timeframe << 15)/growth;

	delta = (timefrac*(ptr->MrphLumtype - lumtype))>>15;
	lumtype += delta;

	delta = (timefrac*(ptr->MrphTransp - transp))>>15;
	transp += delta;

	delta = (timefrac*(ptr->MrphColour - colour))>>15;
	colour += delta;

	while (i < count)
	{
		ptr2 = (MORPHSPHNEXT_PTR) instr_ptr;

		radius = ptr2->radius;

		delta = (timefrac*(ptr2->MrphRadius - radius))>>15;
		radius += delta;

		if (ptr->animflag && animscale && object_obj3d->ItemPtr)		//RJS 15Nov00
		{
			animflag = GlobalAdptr[ptr->animflag];
			randcol = SHAPE.Noise(	object_obj3d->ItemPtr->World.X + animflag,
									object_obj3d->ItemPtr->World.Y + animflag,
									object_obj3d->ItemPtr->World.Z + animflag	);

			animflag++;

			randcol *= -animscale;
			randcol >>= 8;

			colour += randcol;
			GlobalAdptr[ptr->animflag] = animflag;
		}

//DEADCODE JON 4/12/00 		SHAPE.drawsphere(	vertex++,
//DEADCODE JON 4/12/00 							radius,
//DEADCODE JON 4/12/00 							colour,
//DEADCODE JON 4/12/00 							0,
//DEADCODE JON 4/12/00 							1,
//DEADCODE JON 4/12/00 							transp,
//DEADCODE JON 4/12/00 							(Bool)ptr->smooth,
//DEADCODE JON 4/12/00 							0,
//DEADCODE JON 4/12/00 							lumtype,
//DEADCODE JON 4/12/00 							0			);

		i++;
		instr_ptr += sizeof(MORPHSPHNEXT);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		domorphnsphrsimapd
//Author		Robert Slater
//Date			Thu 5 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::domorphnsphrsimapd(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("e2");
#endif
	DOMORPHNSPHRSIMAPD_PTR ptr = (DOMORPHNSPHRSIMAPD_PTR )instr_ptr;
	SLong		 radius;
//DeadCode RJS 21Apr99 	UByteP		adptr = (UByteP) object_obj3d->AnimPtr;
	UWord		timeframe;
	SLong		timefrac;
	int			lumtype;
	int			transp;
	int			growth = ptr->MrphGrowtime;
	int			delta;
	UWord		imap;											//RJS 19Nov98
	int			randcol;
	MORPHSPHNEXT_PTR	ptr2;
	int			vertex = ptr->vertex;
	int			i = 0;
	int			count = ptr->count;
	UByte		width, height;
	UWord		frameno = 0;
	UWord		minix, miniy;
	UWord		maxix, maxiy;
	SWord		stepx,stepy;
	SWord		nofx;
	ImageMapDescPtr imptr;										//RJS 19Nov98
	UWord		jmpsize = sizeof(MORPHSPHNEXT);
	UByteP		pnt_base;
	UWord		angle;
	bool		pivoted = ptr->pivoted;							//RJS 26Nov98
	SWord		oldalpha = -1;
	UByte		fadedepth;// = GlobalAdptr[ptr->fadeoff];

	instr_ptr += sizeof(DOMORPHNSPHRSIMAPD);			//RJS 15May00

	if (ptr->fadeoff)									//RJS 15May00
	{
		fadedepth = GlobalAdptr[ptr->fadeoff];			//RJS 15May00
		if (!fadedepth)
		{
			//They are all totally transparent...
			instr_ptr += count * sizeof(MORPHSPHNEXT);
			return;
		}

		ULong val=ULong(fadedepth);
		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,&val);
		oldalpha=val;
	}

//DEADCODE RJS 5/15/00 	instr_ptr += sizeof(DOMORPHNSPHRSIMAPD);

	minix = ptr->minix;
	miniy = ptr->miniy;

	width = ptr->ix;
	height = ptr->iy;

	lumtype = ptr->lumtype;
	transp = ptr->transp;

	timeframe = *((UWordP)&GlobalAdptr[ptr->MrphAnim]);
	timefrac = (timeframe << 15)/growth;

	delta = (timefrac*(ptr->MrphLumtype - lumtype))>>15;
	lumtype += delta;

	delta = (timefrac*(ptr->MrphTransp - transp))>>15;
	transp += delta;

	if (ptr->animflag)
	{
		frameno = GlobalAdptr[ptr->animflag] / ptr->animscale;
		if (ptr->SwitchImagemap && (frameno >= ptr->framelimit))
		{
			frameno -= ptr->framelimit;
			imap = ptr->SwitchImagemap;
		}
		else
			imap = ptr->imagemap;

		imptr = Image_Map.GetImageMapPtr((ImageMapNumber )imap);

		nofx = imptr->w / width;				
														
		stepy = frameno / nofx;							
		stepx = frameno - (stepy*nofx);					
														
		minix += stepx * width;							
		miniy += stepy * height;
	}
	else
		imap = ptr->imagemap;

	maxix = minix + width;								
	maxiy = miniy + height;								

	if (count > 1)													//RJS 10Jul98
	{
		for (i = 0; i < count; i++)
		{
			SHAPE.AddToTree(vertex);
			vertex++;
		}
	}

	i = 0;
	vertex = ptr->vertex;

	SLong	newcnt = SHAPE.EmptyTree();										//RJS 09Jul98
	if (newcnt)
	{
		pnt_base = instr_ptr - (vertex * jmpsize);
		if (ptr->spinoff)
		{
			angle = *((UWordP)&GlobalAdptr[ptr->spinoff]);
			while (i < newcnt)
			{
				ptr2 = (MORPHSPHNEXT_PTR) (pnt_base + (SphereList[i]*jmpsize));
				
				radius = ptr2->radius;

				delta = (timefrac*(ptr2->MrphRadius - radius))>>15;
				radius += delta;

				SHAPE.imapspherespin(	SphereList[i],
										radius,
										(ImageMapNumber )imap,
										minix,
										miniy,
										maxix,
										maxiy,
										angle	);
				i++;
			}
		}
		else
		{
			while (i < newcnt)
			{
				ptr2 = (MORPHSPHNEXT_PTR) (pnt_base + (SphereList[i]*jmpsize));
				
				radius = ptr2->radius;

				delta = (timefrac*(ptr2->MrphRadius - radius))>>15;
				radius += delta;

				SHAPE.imapsphere(	SphereList[i],
									radius,
									(ImageMapNumber )imap,
									minix,
									miniy,
									maxix,
									maxiy,
									pivoted	);
				i++;
			}
		}
		instr_ptr += (count * jmpsize);
	}
	else
	{
		if (ptr->spinoff)
		{
			angle = *((UWordP)&GlobalAdptr[ptr->spinoff]);
			while (i < count)
	 		{
	 			ptr2 = (MORPHSPHNEXT_PTR) instr_ptr;
 
	 			radius = ptr2->radius;
 
 				delta = (timefrac*(ptr2->MrphRadius - radius))>>15;
 				radius += delta;
 
				SHAPE.imapspherespin(	vertex++,
										radius,
										(ImageMapNumber )imap,
										minix,
										miniy,
										maxix,
										maxiy,
										angle	);

				instr_ptr += sizeof(MORPHSPHNEXT);
 				i++;
 			}
		}
		else
		{
			while (i < count)
	 		{
	 			ptr2 = (MORPHSPHNEXT_PTR) instr_ptr;
 
	 			radius = ptr2->radius;
 
 				delta = (timefrac*(ptr2->MrphRadius - radius))>>15;
 				radius += delta;
 
				SHAPE.imapsphere(	vertex++,
									radius,
									(ImageMapNumber )imap,
									minix,
									miniy,
									maxix,
									maxiy,
									pivoted );

				instr_ptr += sizeof(MORPHSPHNEXT);
 				i++;
 			}
		}
	}																	//RJS 09Jul98

	if (oldalpha > -1)											//RJS 27Nov98
		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,ULong(oldalpha));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dosetpose
//Author		Robert Slater
//Date			Fri 5 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dosetpose(UByte *&instr_ptr )
{
#ifdef	_PROCDEBUG_
	Bollox("e3");
#endif
 	DOSETPOSE_PTR	ptr = (DOSETPOSE_PTR) instr_ptr;
// 	UByteP			adptr = (UByteP) object_obj3d->AnimPtr;			
 	SLong			pose = GlobalAdptr[ptr->animpose];
//DeadCode RJS 17Nov99  	ULongP			poseptr = (ULongP)&GlobalAdptr[ptr->poseoff];
 	SLong			offset;
 	UByteP			sdptr = (UByteP) globalSdptr;		//RJS 21Dec99
 	UWord			mainoff = *((UWordP)(sdptr - 2));//size of shape
 	SLongP			staticrealbase = (SLongP) (sdptr + mainoff - 2);
 	SLongP			realbase = staticrealbase;
 	UByteP			posebase = (UByteP) realbase;
 	MAXANIMLIST_PTR	animptr;
 
 	realbase += pose;		//should increment in longs
 
 	offset = *realbase;	
 
 	posebase = posebase + offset;	//Start of anim data for this pose
 
 	theNextBlokeAnimPtr = theBlokeAnimPtr = posebase;			//RJS 05Apr00
 
 	animptr = (MAXANIMLIST_PTR) posebase;

//DeadCode RJS 14Apr00 	if ((animptr->tloopend - animptr->tloopstart) < ((animptr->noFrames*animptr->frametime)/10))//RJS 04Apr00
	if (animptr->tloopstart > 0)
 	{	
 		GlobalAdptr[ptr->loopable] = 1;
 		GlobalAdptr[ptr->looptog] = 1;
//DEADCODE RJS 4/6/00  		if (GlobalAdptr[ptr->newanimpose] != pose)
//DEADCODE RJS 4/6/00  			GlobalAdptr[ptr->looptog] = 0;
 	}
 	else
 		GlobalAdptr[ptr->loopable] = 0;

	if (GlobalAdptr[ptr->newanimpose] != pose)
	{
		pose = GlobalAdptr[ptr->newanimpose];

		realbase = staticrealbase;
 		posebase = (UByteP) realbase;
		realbase += pose;
 
 		offset = *realbase;	
 
 		posebase = posebase + offset;
 
 		theNextBlokeAnimPtr = posebase;

 		GlobalAdptr[ptr->looptog] = 0;
	}

	instr_ptr += sizeof(DOSETPOSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doenvanim
//Author		Robert Slater
//Date			Fri 5 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doenvanim(UByte *&instr_ptr )						//RJS 12Oct98
{
#ifdef	_PROCDEBUG_
	Bollox("e4");
#endif
 	DOENVANIM_PTR	ptr = (DOENVANIM_PTR) instr_ptr;
 	MAXANIMLIST_PTR	animptr = (MAXANIMLIST_PTR) theBlokeAnimPtr;//RJS 17Nov99
 	ULong			animscale = animptr->frametime;	// in cs*128	//RJS 17Apr00
 
 	if (animscale)
 	{
 		UByte	looptog = GlobalAdptr[ptr->looptog];
 		UWord	tloopstart = animptr->tloopstart;
 		UWord	tloopend = animptr->tloopend - 1;
 		UByte	loopable = GlobalAdptr[ptr->loopable];
//DeadCode RJS 20Oct00  		UByte	maxframes = animptr->noFrames - 1;
 		ULong	frameno,frametime;
		bool	transition = (theBlokeAnimPtr != theNextBlokeAnimPtr);
 
 		switch (ptr->flagsize)
 		{
 			case 16:
 				frametime = *((UWordP)&GlobalAdptr[ptr->animoff]);
 			break;
 			case 32:
 				frametime = *((ULongP)&GlobalAdptr[ptr->animoff]);
 			break;
 			default:
 				frametime = GlobalAdptr[ptr->animoff];
 			break;
 		}
 
 		if (loopable)
 		{
 			if (looptog)
 			{
				frametime += (ULong)View_Point->DrawFrameTime();

				frameno = (frametime << 7)/ animscale;			//RJS 17Apr00
 
 				if (frametime >= tloopend)						//RJS 04Apr00
				{
					anim_morphframe = (tloopstart<<7)/animscale;//RJS 17Apr00
	 				if (frametime > tloopend)					//RJS 04Apr00
					{
						frameno = (tloopstart<<7)/animscale;	//RJS 17Apr00
						anim_morphframe++;
 						frametime = tloopstart;					//RJS 04Apr00
					}
				}
				else
					anim_morphframe = frameno+1;
 			}
 			else
 			{
				frametime += (ULong)View_Point->DrawFrameTime();
 
 				frameno = (frametime<<7)/ animscale;
				if (frametime >= tloopstart)
				{
					if (frametime >= tloopend)						//RJS 04Apr00
					{
						anim_morphframe = (tloopend<<7)/animscale;	//RJS 17Apr00
	 					if (frametime > tloopend)					//RJS 04Apr00
						{
							frameno = anim_morphframe;				//RJS 04Apr00

 							frametime = tloopend;						//RJS 04Apr00
 							GlobalAdptr[ptr->swapnow] = 1;
						}
 					}													//RJS 28Jul99
					else
						anim_morphframe = frameno+1;
				}
				else
				{
					tloopend = tloopstart;
					tloopstart = 0;

					GlobalAdptr[ptr->swapnow] = 1;
				}
 			}
 		}
 		else
 		{
			if (!GlobalAdptr[ptr->swapnow])
			{
	 			frametime += (ULong)View_Point->DrawFrameTime();
 				frameno = (frametime<<7)/ animscale;			//RJS 17Apr00
 
				if (frametime >= tloopend)						//RJS 04Apr00
				{
					anim_morphframe = (tloopend<<7)/animscale;	//RJS 17Apr00
	 				if (frametime > tloopend)					//RJS 04Apr00
					{
						frameno = anim_morphframe;				//RJS 04Apr00

 						frametime = tloopend;						//RJS 04Apr00
 						GlobalAdptr[ptr->swapnow] = 1;
					}
 				}													//RJS 28Jul99
				else
					anim_morphframe = frameno+1;
//DEADCODE RJS 4/14/00 
//DEADCODE RJS 4/14/00  				if (frameno > maxframes)
//DEADCODE RJS 4/14/00  				{
//DEADCODE RJS 4/14/00 					frameno = maxframes;
//DEADCODE RJS 4/14/00 					frametime = (frameno*animscale)/10;
//DEADCODE RJS 4/14/00 					anim_morphframe = frameno;
//DEADCODE RJS 4/14/00 	 				GlobalAdptr[ptr->swapnow] = 1;
//DEADCODE RJS 4/14/00 				}
//DEADCODE RJS 4/14/00 				else
//DEADCODE RJS 4/14/00 					anim_morphframe = frameno+1;
 			}
			else
			{
				frameno = (frametime<<7)/ animscale;			//RJS 17Apr00
				anim_morphframe = frameno;
			}
 		}
 
 		GlobalAdptr[ptr->animframe] = frameno;

// Calc fraction of sandwich filling we want...
		if (!transition)
			anim_interpolatemul = ((frametime<<21)/animscale)-(frameno<<14);
		else
		{
			SLong	lplength = tloopend-tloopstart;

			anim_morphframe = 0;
			anim_interpolatemul = ((lplength-tloopend+frametime)<<14)/lplength;
		}

 		switch (ptr->flagsize)
 		{
 			case 16:
 				*((UWordP)&GlobalAdptr[ptr->animoff]) = (UWord) frametime;
 			break;
 			case 32:
 				*((ULongP)&GlobalAdptr[ptr->animoff]) = frametime;
 			break;
 			default:
 				GlobalAdptr[ptr->animoff] = frametime;
 			break;
 		}
 	}
 	else
	{
		anim_morphframe = 0;
		anim_interpolatemul = 0;
 		GlobalAdptr[ptr->swapnow] = 1;
	}

	instr_ptr += sizeof(DOENVANIM);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dontriangles
//Author		Robert Slater
//Date			Fri 25 Sep 1998
//
//Description	Draws a number of image-mapped triangles
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::dontriangles(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("e5");
#endif
	DONTRIANGLES_PTR	ptr = (DONTRIANGLES_PTR) instr_ptr;
	TRINEXT_PTR			faceP;
//	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	SLong				counter = ptr->count;
	SLong				i;
	SLong				vertex;
	bool 				clipping;
	bool				visible;
	DoPointStruc		dp[3];
	SWord				material = ptr->material;
	SWord				animframe = ptr->animoff;
	SWord				intensity[3];
	SWord				realintensity;

	if (animframe)
	{
		ULong	frame = GlobalAdptr[animframe];

		frame /= ptr->animscale;
		material += frame;
	}

	instr_ptr += sizeof(DONTRIANGLES);

//DeadCode RJS 20Oct00 	int	noverts = 0;

	faceP = (TRINEXT_PTR) instr_ptr;

	instr_ptr += (sizeof(TRINEXT) * counter);

	while (counter)
	{
		for (i=0; i < 3; i++)
		{
			vertex = faceP->vertex[i];

#ifndef	_NOPOINTS_
			newco[vertex].setIMapCoords(SWord(faceP->ix[i]),SWord(faceP->iy[i]));//RJS 19May00

			dp[i] = newco[vertex];
#endif
		}

		//test clip flags before drawing the polygon...

//TempCode RJS 12Apr00 		if (faceP->normal)
//TempCode RJS 12Apr00 		{
//TempCode RJS 12Apr00 			realintensity = intensity[0];
//TempCode RJS 12Apr00 			realintensity = 256 - realintensity;
//TempCode RJS 12Apr00 			intensity[0] = realintensity;
//TempCode RJS 12Apr00 			intensity[1] = realintensity;
//TempCode RJS 12Apr00 			intensity[2] = realintensity;
//TempCode RJS 12Apr00 		}

#ifndef	_NOPOLYS_
		Lib3DPoint*	pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr((ImageMapNumber)material)),3);//RJS 19May00

		for (i=0; i < 3; i++)
			*pRVerts++= dp[i];

 		g_lpLib3d->EndPoly();
#endif
		faceP++;
		counter--;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		donmaxpoints
//Author		Robert Slater
//Date			Fri 5 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::donmaxpoints(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("e6");
#endif
	DONMAXPOINTS_PTR	ptr = (DONMAXPOINTS_PTR) instr_ptr;
	SWord				counter = ptr->count;
	UWord				vertex = ptr->vertex;
	IFShare				wx,wy,wz;
	SLong				intensity2;
	Float				dotx, doty, dotz, intensity;
	SLong				swap;
	SLong				x,y,z;
	DoPointStruc*		dpPtr=&newco[vertex];

	instr_ptr += sizeof(DONMAXPOINTS);

	NMAXNEXT_PTR	vptr = (NMAXNEXT_PTR) instr_ptr;

	instr_ptr += (counter * sizeof(NMAXNEXT));

	if (fpanim_matrix)
	{
		double* mp=(double*)fpanim_matrix;					//RJS 24Feb00
		double* ml=(double*)fplight_matrix;						//RJS 03Apr00
		double	fptran_x = double(anim_translation.X);
		double	fptran_y = double(anim_translation.Y);
		double	fptran_z = double(anim_translation.Z);
		double	f[3];

		intensity2 = -1;
		while (counter)
		{
			//object transform

			f[0] = vptr->x;
			f[1] = vptr->y;
			f[2] = vptr->z;

// Transform points using 3DS convention... then swap y&z

#ifndef	_NOPOINTS_
			dpPtr->setPosition(	f[0]*mp[0]+f[1]*mp[1]+f[2]*mp[2]+fptran_x,
								f[0]*mp[6]+f[1]*mp[7]+f[2]*mp[8]+fptran_z,
								f[0]*mp[3]+f[1]*mp[4]+f[2]*mp[5]+fptran_y	);
#endif

//DeadCode RJS 19May00 			dpPtr->bodyx.f=f[0]*mp[0]+f[1]*mp[1]+f[2]*mp[2]+fptran_x;
//DeadCode RJS 19May00 			dpPtr->bodyz.f=f[0]*mp[3]+f[1]*mp[4]+f[2]*mp[5]+fptran_y;
//DeadCode RJS 19May00 			dpPtr->bodyy.f=f[0]*mp[6]+f[1]*mp[7]+f[2]*mp[8]+fptran_z;

			//Light shading...
//DeadCode RJS 03Apr00 			if (View_Point->isLightShaded)
//DeadCode RJS 03Apr00 			{
//DeadCode RJS 03Apr00 				wx.i = vptr->na;
//DeadCode RJS 03Apr00 				wy.i = vptr->nb;
//DeadCode RJS 03Apr00 				wz.i = vptr->nc;
//DeadCode RJS 03Apr00 
//DeadCode RJS 03Apr00 				_matrix.transformNC(fplight_matrix,wx,wy,wz);
//DeadCode RJS 03Apr00 
//DeadCode RJS 03Apr00 				intensity = wx.f + wy.f + wz.f;
//DeadCode RJS 03Apr00 
//DeadCode RJS 03Apr00 				intensity2 = intensity;
//DeadCode RJS 03Apr00 				intensity2 += 127;
//DeadCode RJS 03Apr00 				intensity2 = 256 - intensity2;
//DeadCode RJS 03Apr00 				intensity2 *= 330;
//DeadCode RJS 03Apr00 				intensity2 >>= 8;
//DeadCode RJS 03Apr00 
//DeadCode RJS 03Apr00 				if (intensity2 > 256)
//DeadCode RJS 03Apr00 					intensity2 = 256;
//DeadCode RJS 03Apr00 				else
//DeadCode RJS 03Apr00 				{
//DeadCode RJS 03Apr00 					if (intensity2 < 48)
//DeadCode RJS 03Apr00 						intensity2 = 48;
//DeadCode RJS 03Apr00 				}
//DeadCode RJS 03Apr00 			}

			if (View_Point->isLightShaded)
			{
				f[0] = vptr->na;
				f[1] = vptr->nb;
				f[2] = vptr->nc;

#ifndef	_NOPOINTS_
				dpPtr->setNormal(	f[0]*ml[0]+f[2]*ml[2],
									f[0]*ml[6]+f[1]*ml[7]+f[2]*ml[8],
									f[0]*ml[3]+f[1]*ml[4]+f[2]*ml[5]	);//RJS 19May00
#endif
									
//DeadCode RJS 19May00 				dpPtr->nx=f[0]*ml[0]+f[2]*ml[2];
//DeadCode RJS 19May00 				dpPtr->nz=f[0]*ml[3]+f[1]*ml[4]+f[2]*ml[5];
//DeadCode RJS 19May00 				dpPtr->ny=f[0]*ml[6]+f[1]*ml[7]+f[2]*ml[8];
			}

			vptr++;
			counter--;
			dpPtr++;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doanimmatrix
//Author		Robert Slater
//Date			Wed 7 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void shape::doanimmatrix(UByte *&instr_ptr )					//RJS 07Oct98
{
#ifdef	_PROCDEBUG_
	Bollox("e7");
#endif
	DOANIMMATRIX_PTR	ptr = (DOANIMMATRIX_PTR) instr_ptr;
//	UByteP				adptr = (UByteP) object_obj3d->AnimPtr;
	MAXANIMLIST_PTR		posePtr = (MAXANIMLIST_PTR) theBlokeAnimPtr;

	if (posePtr	&& (SByte(ptr->node) != -1))
	{
		UByte	theNode = posePtr->nodemap[ptr->node];
		if (theNode)
		{
			SLong				frame = GlobalAdptr[ptr->animframe];
			SLong				offset;
			MAXANIMNODE_PTR		nodePtr;
			Float				*fpptr;
			Float				*fpptr2;
			SLong				i;
			Float				mscale;
			Float				mscale256;
			Float				mnumber;
			SLong				framesize;
			UByteP				posebase = (UByteP) posePtr;
			MAXANIMFRAME_PTR	framePtr;
			Float*				tmplm;
			Float*				tmpom;

			posebase += posePtr->rootnodecnt;

			framePtr = (MAXANIMFRAME_PTR) (posebase + sizeof(MAXANIMLIST));

			framesize = framePtr->noNodes * sizeof(MAXANIMNODE);
			framesize += sizeof(MAXANIMFRAME);

			posebase += sizeof(MAXANIMLIST);

			offset = sizeof(MAXANIMFRAME);
			offset += (theNode * sizeof(MAXANIMNODE));
			posebase += offset;

			//The node for this frame...

			posebase += (framesize * frame);

			nodePtr = (MAXANIMNODE_PTR) posebase;
//DeadCode RJS 03Apr00 			mscale = Float(nodePtr->matrixscale);
//DeadCode RJS 03Apr00 			mscale256 = mscale * 0.00390625;

//DEADCODE RJS 4/4/00 			anim_translation.X = nodePtr->px;
//DEADCODE RJS 4/4/00 			anim_translation.Y = nodePtr->py;
//DEADCODE RJS 4/4/00 			anim_translation.Z = ULong(nodePtr->pz);

			fpanim_matrix = &anim_matrix;
//DeadCode RJS 03Apr00 			fpptr = (Float*) &fpanim_matrix->L11;
//DeadCode RJS 03Apr00 			fpptr2 = (Float*) &fplight_matrix->L11;
//DeadCode RJS 03Apr00 			for (i=0; i < 9; i++)
//DeadCode RJS 03Apr00 			{
//DeadCode RJS 03Apr00 				mnumber = Float(nodePtr->matrix[i]);
//DeadCode RJS 03Apr00 
//DeadCode RJS 03Apr00 				*fpptr = (mnumber * mscale256);
//DeadCode RJS 03Apr00 				*fpptr2 = (mnumber * mscale);
//DeadCode RJS 03Apr00 				fpptr++;
//DeadCode RJS 03Apr00 				fpptr2++;
//DeadCode RJS 03Apr00 			}

			tmpom = (Float*)fpanim_matrix;
			tmplm = (Float*)fplight_matrix;

			if (	(anim_morphframe != frame)
				&&	anim_interpolatemul			)
			{
				MAXANIMNODE_PTR		nodenextPtr;
				SWord				newHdg;
				SWord				newPitch;
				SWord				newRoll;
				
				posePtr = (MAXANIMLIST_PTR) theNextBlokeAnimPtr;
				if (!posePtr->nodemap[ptr->node])
					posePtr = (MAXANIMLIST_PTR) theBlokeAnimPtr;

				posebase = (UByteP) posePtr;
				posebase += posePtr->rootnodecnt;

				framePtr = (MAXANIMFRAME_PTR) (posebase + sizeof(MAXANIMLIST));

				framesize = framePtr->noNodes * sizeof(MAXANIMNODE);
				framesize += sizeof(MAXANIMFRAME);

				posebase += sizeof(MAXANIMLIST);

				offset = sizeof(MAXANIMFRAME);
				offset += (theNode * sizeof(MAXANIMNODE));
				posebase += offset;

				//The node for this frame...

				posebase += (framesize * anim_morphframe);

				nodenextPtr = (MAXANIMNODE_PTR) posebase;

				newHdg=nodenextPtr->hdg-nodePtr->hdg;
				newPitch=nodenextPtr->pitch-nodePtr->pitch;
				newRoll=nodenextPtr->roll-nodePtr->roll;

				newHdg = nodePtr->hdg + ((newHdg*anim_interpolatemul)>>14);
				newPitch = nodePtr->pitch + ((newPitch*anim_interpolatemul)>>14);
				newRoll = nodePtr->roll + ((newRoll*anim_interpolatemul)>>14);

				SLong	zoff = ULong(nodenextPtr->pz)-ULong(nodePtr->pz);
				anim_translation.X = nodePtr->px + (((nodenextPtr->px-nodePtr->px)*anim_interpolatemul)>>14);
				anim_translation.Y = nodePtr->py + (((nodenextPtr->py-nodePtr->py)*anim_interpolatemul)>>14);
				anim_translation.Z = ULong(nodePtr->pz) + ((zoff*anim_interpolatemul)>>14);

				_matrix.Generate3DS(tmpom,newHdg,newPitch,newRoll);
			}
			else
			{
				anim_translation.X = nodePtr->px;
				anim_translation.Y = nodePtr->py;
				anim_translation.Z = ULong(nodePtr->pz);

				_matrix.Generate3DS(tmpom,nodePtr->hdg,nodePtr->pitch,nodePtr->roll);
			}

//Light matrix includes a /32767 scale...
			Float	theNum;
			SLong	tmpcnt = 0;
			while (tmpcnt < 9)
			{
				*tmplm++ = *tmpom*3.051851e-5;
				tmpom++;
				tmpcnt++;
			}
//DeadCode RJS 03Apr00 			Float	scalex = TransLightVector.ni.f * 0.003875732406;
//DeadCode RJS 03Apr00 			Float	scaley = TransLightVector.nk.f * 0.003875732406;
//DeadCode RJS 03Apr00 			Float	scalez = TransLightVector.nj.f * 0.003875732406;
//DeadCode RJS 03Apr00 			fplight_matrix->L11 *= scalex;
//DeadCode RJS 03Apr00 			fplight_matrix->L12 *= scalex;
//DeadCode RJS 03Apr00 			fplight_matrix->L13 *= scalex;
//DeadCode RJS 03Apr00 			fplight_matrix->L21 *= scaley;
//DeadCode RJS 03Apr00 			fplight_matrix->L22 *= scaley;
//DeadCode RJS 03Apr00 			fplight_matrix->L23 *= scaley;
//DeadCode RJS 03Apr00 			fplight_matrix->L31 *= scalez;
//DeadCode RJS 03Apr00 			fplight_matrix->L32 *= scalez;
//DeadCode RJS 03Apr00 			fplight_matrix->L33 *= scalez;
		}
		else
			instr_ptr--;
	}
	else
		fpanim_matrix = NULL;

	instr_ptr += sizeof(DOANIMMATRIX);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dobitsoffbloke
//Author		Robert Slater
//Date			Fri 5 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dobitsoffbloke(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("e8");
#endif
	DOBITSOFFBLOKE_PTR	ptr = (DOBITSOFFBLOKE_PTR )instr_ptr;
	UWord				flag = *((UWordP)&GlobalAdptr[ptr->animflag]);

	flag >>= ptr->bitflag;
	flag &= 1;

	instr_ptr += sizeof(DOBITSOFFBLOKE);

	if (!flag)
		instr_ptr--;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dosetmaterialtype
//Author		Robert Slater
//Date			Mon 8 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dosetmaterialtype(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("e9");
#endif
	DOSETMATERIALTYPE_PTR	ptr = (DOSETMATERIALTYPE_PTR)instr_ptr;

	instr_ptr += sizeof(DOSETMATERIALTYPE);

	if (	(ptr->flags == STEXT_REFLECTIVE)							//RJS 30Aug00
		&&	!Save_Data.cockpit3Ddetail[COCK3D_SKYIMAGES]	)
		instr_ptr--;
	else
	{
		LIGHTFLAG	lf = LIGHTFLAG(GetLightingType(ptr->flags));		//RJS 27Sep00
		g_lpLib3d->SetObjectLighting(lf);								//RJS 27Sep00
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doanimtransform
//Author		Robert Slater
//Date			Wed 10 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doanimtransform(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("f0");
#endif
	DOANIMTRANSFORM_PTR	ptr = (DOANIMTRANSFORM_PTR )instr_ptr;
	UWord				theAngle=0;
	SWord				minDef = ptr->mindef;
	SWord				maxDef = ptr->maxdef;
	bool				isBlank = false;
	SLong				isInteractive = ptr->interactivepnt;

	switch (ptr->nobits)
	{
	case 8:
		SLong				range;
		if (ptr->mindef < 0)		//is it signed?
		{
			range = SByte(GlobalAdptr[ptr->animflag]);
			range += 128;

			range *= (maxDef-minDef);
			range >>= 8;

			theAngle = range + minDef;
		}
		else
		{
			range = GlobalAdptr[ptr->animflag];

			if (isInteractive == -1)
			{
				if (ptr->maxblank && (range == 255))
				{
					isBlank = true;
					break;
				}
				else
				{
					if (ptr->minblank && !range)
					{
						isBlank = true;
						break;
					}
				}
			}

			range *= (maxDef-minDef);
			theAngle = range >> 8;
		}
		break;
	case 16:
		theAngle = *((UWordP)&GlobalAdptr[ptr->animflag]);
		if (theAngle > maxDef)
			theAngle = maxDef;
		else
		{
			if (theAngle < minDef)
				theAngle = minDef;
		}
		break;
	}

	instr_ptr += sizeof(DOANIMTRANSFORM);
	if (isBlank)
		instr_ptr--;
	else
	{
		ANIMPOINT_PTR		vptr = (ANIMPOINT_PTR) instr_ptr;
		DoPointStruc* 		dp = &newco[ptr->vertex];
		SLong				count = ptr->count;
		SLong				nx,ny,nz;
		SLong				x,y,z;
		SWord				*bmat;
		SWordP				m;


		bmat = intAnimMatrixPtr = &ptr->Xx;
		m = intSubAnimMatrix;

		instr_ptr += sizeof(ANIMPOINT) * count;

// Generate pitch plane rotation...

//DeadCode RJS 03Dec99 		m[0] = 0x7FFF;		//11

//		theAngle = -theAngle;
		if (theAngle)
		{
			SWord	sin_pitch,cos_pitch;

			Math_Lib.high_sin_cos((Angles)theAngle,sin_pitch,cos_pitch);

			// 21 31 12 13	are all 0

			m[4] = m[8] = cos_pitch;	//22 33
			m[7] = sin_pitch;		//32
			m[5] = -sin_pitch;		//23
		}
		else
		{
			m[4] = m[8] = 0x7FFF;	//22 33
			m[7] = 0;		//32
			m[5] = 0;		//23
		}

		if (isInteractive > -1)
			count--;

		while (count)
		{
			x = vptr->x;
			y = vptr->z;		// swap y & z to Rowan convention
			z = vptr->y;

// 1st, rotate raw points by 'angle'

//DeadCode RJS 03Dec99 			nx = (m[0] * x)>>15;
//DeadCode RJS 03Dec99 			nx = x;

			ny = (m[4] * y)>>15;
			ny += (m[5] * z)>>15;

			nz = (m[7] * y)>>15;
			nz += (m[8] * z)>>15;

// Forward transform...

//DeadCode RJS 03Dec99 			x = nx;
			y = nz;				// swap y & z to normal convention
			z = ny;

			nx = (bmat[0] * x)>>14;
			nx += (bmat[3] * y)>>14;
			nx += (bmat[6] * z)>>14;

			ny = (bmat[1] * x)>>14;
			ny += (bmat[4] * y)>>14;
			ny += (bmat[7] * z)>>14;

			nz = (bmat[2] * x)>>14;
			nz += (bmat[5] * y)>>14;
			nz += (bmat[8] * z)>>14;

// Swap y & z back to Rowan convention...

#ifndef	_NOPOINTS_
			dp->setPosition(	nx + bmat[9],
								nz + bmat[11],
								ny + bmat[10]	);
#endif

//DeadCode RJS 19May00 			dp->bodyx.f = nx + bmat[9];
//DeadCode RJS 19May00 			dp->bodyz.f = ny + bmat[10];	//swap back to Rowan
//DeadCode RJS 19May00 			dp->bodyy.f = nz + bmat[11];

			dp++;
			vptr++;
			count--;
		}

		if (isInteractive > -1)
		{
			ShapeDescPtr sdptr = (ShapeDescPtr) globalSdptr;
			DOINTERACTIVEHITBOX_PTR	hbptr = (DOINTERACTIVEHITBOX_PTR) ((UByteP)globalSdptr + sdptr->InteractiveOffset + 1 + (isInteractive * (sizeof(DOINTERACTIVEHITBOX)+1)));//RJS 22Nov99

			x = vptr->x;
			y = vptr->z;		// swap y & z to Rowan convention
			z = vptr->y;

// 1st, rotate raw points by 'angle'

//			nx = (m[0] * x)>>15;

			ny = (m[4] * y)>>15;
			ny += (m[5] * z)>>15;

			nz = (m[7] * y)>>15;
			nz += (m[8] * z)>>15;

// Forward transform...

//			x = nx;
			y = nz;				// swap y & z to normal convention
			z = ny;

			nx = (bmat[0] * x)>>14;
			nx += (bmat[3] * y)>>14;
			nx += (bmat[6] * z)>>14;

			ny = (bmat[1] * x)>>14;
			ny += (bmat[4] * y)>>14;
			ny += (bmat[7] * z)>>14;

			nz = (bmat[2] * x)>>14;
			nz += (bmat[5] * y)>>14;
			nz += (bmat[8] * z)>>14;

			InteractiveAnimData*	iadptr = (InteractiveAnimData*) &GlobalAdptr[hbptr->animflag];
			iadptr->anim_x = nx + bmat[9];
			iadptr->anim_y = nz + bmat[11];
			iadptr->anim_z = ny + bmat[10];
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		docreatemirror
//Author		Robert Slater
//Date			Thu 18 Nov 1999
//
//Description	Should fill in the imagemap with a mirror image,
//				and load it back into hardware memory
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::docreatemirror(UByte *& instr_ptr)
{
	if (Save_Data.cockpit3Ddetail[COCK3D_SKYIMAGES])			//RJS 21Sep00
	{
		DOCREATEMIRROR_PTR	ptr = (DOCREATEMIRROR_PTR )instr_ptr;
		Coords3D			pos;

		pos.X = ptr->x;
		pos.Y = ptr->y;
		pos.Z = ptr->z;

		Three_Dee.UseMirror(ptr->material,pos,ptr->Ni,ptr->Nj,ptr->Nk,ANGLES_45Deg);	//RJS 12Jul00

		instr_ptr += sizeof(DOCREATEMIRROR);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		donteractivehitbox
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
void shape::dointeractivehitbox(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("f2");
#endif
	DOINTERACTIVEHITBOX_PTR	ptr = (DOINTERACTIVEHITBOX_PTR )instr_ptr;
	R3DVERTEX		dp0,dp1,dp2,dp3,dpcentre;
	R3DVERTEX		dpoints[4];
	IFShare			wx,wy,wz;
	float			radiusx,radiusy,radiusz;

	radiusx = float(ptr->radiusx);								//RJS 02Dec99
	radiusy = float(ptr->radiusy);								//RJS 02Dec99
	radiusz = float(ptr->radiusz);								//RJS 02Dec99
	if (ptr->animflag)
	{
		InteractiveAnimData*	adptr = (InteractiveAnimData*) &GlobalAdptr[ptr->animflag];

		wx.i = adptr->anim_x;
		wy.i = adptr->anim_y;
		wz.i = adptr->anim_z;
	}
	else
	{
		wx.i = ptr->x;
		wy.i = ptr->y;
		wz.i = ptr->z;
	}

	dp0.x = wx.i;
	dp0.y = wy.i;
	dp0.z = wz.i;

	dpcentre = dp0;

	float	sx,sy,sz,zscale;
	float	radius;														//RJS 30May00

	radius = fastMath.FastSqrt(radiusx*radiusx+radiusy*radiusy+radiusz*radiusz);	//RJS 22Jun00

	g_lpLib3d->BodyToScreen(dpcentre,sx,sy,sz,&zscale);

	float	sradius = radius*zscale*Three_Dee.cockScale*1.25;				//RJS 30May00
	float	minx,maxx,miny,maxy;
	float	mx,my;

	mx = float(lastMX);
	my = float(lastMY);

	minx = sx-sradius;
	maxx = sx+sradius;
	miny = sy-sradius;
	maxy = sy+sradius;

	dpoints[0] = dpoints[1] = dpoints[2] = dpoints[3] = dp0;

// TL
	dpoints[0].x -= radiusx;
	dpoints[0].y += radiusy;
	dpoints[0].z += radiusz;

// TR
	dpoints[1].x += radiusx;
	dpoints[1].y += radiusy;
	dpoints[1].z += radiusz;

// BR
	dpoints[2].x += radiusx;
	dpoints[2].y -= radiusy;
	dpoints[2].z -= radiusz;

// BL
	dpoints[3].x -= radiusx;
	dpoints[3].y -= radiusy;
	dpoints[3].z -= radiusz;

	if (	(mx > minx)
		&&	(mx < maxx)
		&&	(my > miny)
		&&	(my < maxy)	)
	{
		float	tl_x,tl_y,tl_z,tr_x,tr_y,tr_z,br_x,br_y,br_z,bl_x,bl_y,bl_z;
		SLong	passed=4;												//RJS 30May00

// Screen coords start at 0 (top)
		g_lpLib3d->BodyToScreen(dpoints[0],tl_x,tl_y,tl_z);
		g_lpLib3d->BodyToScreen(dpoints[1],tr_x,tr_y,tr_z);
		if ((tr_x - tl_x) > 20.)										//RJS 30May00
		{
			g_lpLib3d->BodyToScreen(dpoints[2],br_x,br_y,br_z);
			g_lpLib3d->BodyToScreen(dpoints[3],bl_x,bl_y,bl_z);

// Detailed test...
			float	gradient;
			float	dx,dy, tmpx, testy, tmpy, testx;				//RJS 28Apr00
			
			passed=0;													//RJS 30May00

//DeadCode RJS 30May00 		OverLay.HitLine(mx,my,minx,maxx,miny,maxy);
// 0 - 1
			dx = tr_x - tl_x;
			dy = tr_y - tl_y;
			if (dx)
			{
// Top edge...
				gradient = dy/dx;
				tmpx = mx-tl_x;
				testy = tmpx * gradient;
				if (my > (tl_y + testy))
				{
					passed++;
// Bot edge...
					dx = br_x - bl_x;
					if (dx)
					{
						dy = br_y - bl_y;

						gradient = dy/dx;
						tmpx = mx-bl_x;
						testy = tmpx * gradient;
						if (my < (bl_y + testy))
						{
							passed++;
// Now test sides (left)
 							dx = bl_x - tl_x;							//RJS 28Apr00
 							dy = bl_y - tl_y;
							if (dy)
							{
  								gradient = dx/dy;
 								tmpy = my-tl_y;
 								testx = tl_x + (tmpy * gradient);			
 								if (mx > testx)
 								{
 									passed++;
// Now test right side...
 									dx = br_x - tr_x;
									dy = br_y - tr_y;
									if (dy)
									{
 										gradient = dx/dy;
 										tmpy = my-tr_y;
 										testx = tr_x + (tmpy * gradient);
 										if (mx < testx)
 											passed++;
									}
								}
							}
						}
 					}
				}
			}
			else
			{
// Vertical...
				if (	(mx > tl_x)
					&&	(my < bl_y)									//RJS 28Apr00
					&&	(my > tr_y)									//RJS 28Apr00
					&&	(mx < tr_x))
					passed+=4;										//RJS 28Apr00
			}
		}

		if (passed == 4)										//RJS 28Apr00
		{
			interactivefound = true;

			_Interactive.Collide((InstrumentKey)ptr->coltype,lastMPressed);
		}
	}

#ifdef	_DRAW_COLBOX_
	UByteP			tmpinstr_ptr;
	DOSETCOLOUR256	idosetcolour256;
	DOLINE			idoline;

#ifndef	_NOPOINTS_
	newco[0].setPosition(dpoints[0].x,dpoints[0].y,dpoints[0].z);
	newco[1].setPosition(dpoints[1].x,dpoints[1].y,dpoints[1].z);
	newco[2].setPosition(dpoints[2].x,dpoints[2].y,dpoints[2].z);
	newco[3].setPosition(dpoints[3].x,dpoints[3].y,dpoints[3].z);
#endif

	idosetcolour256.basecolour = (Colour)127;
	idosetcolour256.spread = 0;
	idosetcolour256.imap = 0xFF;
	tmpinstr_ptr = (UByteP)&idosetcolour256;
	
	SHAPE.dosetcolour256(tmpinstr_ptr);

	idoline.start_vertex = 0;
	idoline.end_vertex = 1;
	tmpinstr_ptr = (UByte*)&idoline;
	SHAPE.doline(tmpinstr_ptr);

	idoline.start_vertex = 1;
	idoline.end_vertex = 2;
	tmpinstr_ptr = (UByte*)&idoline;
	SHAPE.doline(tmpinstr_ptr);

	idoline.start_vertex = 2;
	idoline.end_vertex = 3;
	tmpinstr_ptr = (UByte*)&idoline;
	SHAPE.doline(tmpinstr_ptr);

	idoline.start_vertex = 3;
	idoline.end_vertex = 0;
	tmpinstr_ptr = (UByte*)&idoline;
	SHAPE.doline(tmpinstr_ptr);

//	OverLay.HitLine(mx,my,minx,maxx,miny,maxy);

#endif

	instr_ptr += sizeof(DOINTERACTIVEHITBOX);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dotmorphnpoints
//Author		Robert Slater
//Date			Wed 1 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dotmorphnpoints(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("f3");
#endif
	DOTMORPHNPOINTS_PTR  ptr = (DOTMORPHNPOINTS_PTR )instr_ptr;
	TMORPHNNEXT_PTR		ptr2;
	SLong			xdelta, ydelta;
	UByteP			timedeltap = &GlobalAdptr[ptr->framecntoffset];
	UWord			timedelta = *((UWordP)timedeltap);
	ULong			count;
	SLong			timefrac = (timedelta<<13)/ptr->growtime;
	DoPointStruc*	dp = &newco[ptr->startvertex];

	count = ptr->nopoints;										
																
	instr_ptr += sizeof(DOTMORPHNPOINTS);						
	ptr2 = (TMORPHNNEXT_PTR) instr_ptr;							
	instr_ptr += (sizeof(TMORPHNNEXT)*count);					
					
	if (timefrac)
	{
		while (count)												
		{															
			xdelta = (timefrac*(ptr2->ix2 - ptr2->ix))>>13;	
			ydelta = (timefrac*(ptr2->iy2 - ptr2->iy))>>13;
			 
#ifndef	_NOPOINTS_
			dp->setIMapCoords(SWord(ptr2->ix + xdelta),SWord(ptr2->iy + ydelta));
#endif

			ptr2++;													
			count--;												
			dp++;													
		}
	}
	else
	{
		while (count)												
		{
#ifndef	_NOPOINTS_
			dp->setIMapCoords(SWord(ptr2->ix),SWord(ptr2->iy));
#endif

			ptr2++;													
			count--;												
			dp++;													
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doabsolutetimerphase
//Author		Robert Slater
//Date			Thu 2 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doabsolutetimerphase(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("f4");
#endif
	DOABSOLUTETIMERPHASE_PTR  ptr = (DOABSOLUTETIMERPHASE_PTR )instr_ptr;
	UWordP			ltimep = (UWordP) &GlobalAdptr[ptr->lifetimeoffset];
	UWordP			dtimep = (UWordP) &GlobalAdptr[ptr->deltatimeoffset];
	UWord			lifetime = *ltimep;
	UWord			nophases = ptr->nophases;
	UWord			count;
	ULong			phasetdelta;
	UWord			lowtime = 0;
	ULong			tdelta;
	TPHASESTEP_PTR	ptr2;
	UByteP			instr_ptr2 = instr_ptr;

	instr_ptr2 += sizeof(DOABSOLUTETIMERPHASE);
	ptr2 = (TPHASESTEP_PTR) instr_ptr2;
	instr_ptr2 += (nophases * sizeof(TPHASESTEP));

	for (count=0; count < nophases; count++)
	{
		phasetdelta = ptr2->timedelta;
		if (phasetdelta == 65535)
			lifetime = 65534;

		if (	(lifetime >= lowtime)
			&&	(lifetime < phasetdelta)	)
		{
			*dtimep = (UWord)(lifetime - lowtime);
			instr_ptr += ptr2->objjump;
			instr_ptr2 = instr_ptr;
			break;
		}

		lowtime = phasetdelta;
		ptr2++;
	}

	instr_ptr = instr_ptr2;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doanimtransformhp
//Author		Robert Slater
//Date			Fri 3 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doanimtransformhp(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("f5");
#endif
//DeadCode RJS 28Feb00 	DOANIMTRANSFORMHP_PTR	ptr = (DOANIMTRANSFORMHP_PTR )instr_ptr;
//DeadCode RJS 28Feb00 	UWord				theHdg,thePitch;
//DeadCode RJS 28Feb00 	SWord				minHDef = ptr->minHdef;
//DeadCode RJS 28Feb00 	SWord				maxHDef = ptr->maxHdef;
//DeadCode RJS 28Feb00 	SWord				minPDef = ptr->minPdef;
//DeadCode RJS 28Feb00 	SWord				maxPDef = ptr->maxPdef;
//DeadCode RJS 28Feb00 	ANIMPOINT_PTR		vptr;
//DeadCode RJS 28Feb00 	DoPointStruc* 		dp = &newco[ptr->vertex];
//DeadCode RJS 28Feb00 	SLong				count = ptr->count;
//DeadCode RJS 28Feb00 	SLong				nx,ny,nz;
//DeadCode RJS 28Feb00 	SLong				x,y,z;
//DeadCode RJS 28Feb00 	SWord				*bmath;
//DeadCode RJS 28Feb00 	SWord				*bmatp;
//DeadCode RJS 28Feb00 	SWord				mh[9];
//DeadCode RJS 28Feb00 	SWord				mp[9];
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 	theHdg = *((UWordP)&GlobalAdptr[ptr->animhflag]);
//DeadCode RJS 28Feb00 	if (theHdg > maxHDef)
//DeadCode RJS 28Feb00 		theHdg = maxHDef;
//DeadCode RJS 28Feb00 	else
//DeadCode RJS 28Feb00 	{
//DeadCode RJS 28Feb00 		if (theHdg < minHDef)
//DeadCode RJS 28Feb00 			theHdg = minHDef;
//DeadCode RJS 28Feb00 	}
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 	thePitch = *((UWordP)&GlobalAdptr[ptr->animpflag]);
//DeadCode RJS 28Feb00 	if (thePitch > maxPDef)
//DeadCode RJS 28Feb00 		thePitch = maxPDef;
//DeadCode RJS 28Feb00 	else
//DeadCode RJS 28Feb00 	{
//DeadCode RJS 28Feb00 		if (thePitch < minPDef)
//DeadCode RJS 28Feb00 			thePitch = minPDef;
//DeadCode RJS 28Feb00 	}
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 	instr_ptr += sizeof(DOANIMTRANSFORMHP);	//RJS 25Feb00
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 	vptr = (ANIMPOINT_PTR) instr_ptr;
//DeadCode RJS 28Feb00 	bmath = &ptr->Xx;
//DeadCode RJS 28Feb00 	bmatp = &ptr->Xx2;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 	instr_ptr += sizeof(ANIMPOINT) * count;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 // Generate pitch plane rotation...
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 	if (theHdg || thePitch)
//DeadCode RJS 28Feb00 	{
//DeadCode RJS 28Feb00 		SWord	sin_pitch,cos_pitch;
//DeadCode RJS 28Feb00 		SWord	sin_hdg,cos_hdg;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		// 0 1 2	11 12 13
//DeadCode RJS 28Feb00 		// 3 4 5	21 22 23
//DeadCode RJS 28Feb00 		// 6 7 8	31 32 33
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		Math_Lib.high_sin_cos((Angles)thePitch,sin_pitch,cos_pitch);
//DeadCode RJS 28Feb00 		Math_Lib.high_sin_cos((Angles)theHdg,sin_hdg,cos_hdg);
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		// 21 31 12 13	are all 0
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 // Using pitch generate...
//DeadCode RJS 28Feb00 		mh[0] = 0x7FFF;
//DeadCode RJS 28Feb00 		mh[4] = mh[8] = cos_hdg;	//22 33
//DeadCode RJS 28Feb00 		mh[7] = sin_hdg;		//32
//DeadCode RJS 28Feb00 		mh[5] = -sin_hdg;		//23
//DeadCode RJS 28Feb00 		mh[3] = mh[6] = mh[1] = mh[2] = 0;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 // Using hdg generate...
//DeadCode RJS 28Feb00 //DeadCode RJS 25Feb00 		mp[4] = mp[8] = cos_pitch;	//22 33
//DeadCode RJS 28Feb00 //DeadCode RJS 25Feb00 		mp[7] = sin_pitch;		//32
//DeadCode RJS 28Feb00 //DeadCode RJS 25Feb00 		mp[5] = -sin_pitch;		//23
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		mp[0] = mp[8] = cos_pitch;	//11 33
//DeadCode RJS 28Feb00 		mp[6] = -sin_pitch;			//31
//DeadCode RJS 28Feb00 		mp[2] = sin_pitch;			//13
//DeadCode RJS 28Feb00 		mp[3] = mp[1] = mp[7] = mp[5] = 0;
//DeadCode RJS 28Feb00 		mp[4] = 0x7FFF;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 	}
//DeadCode RJS 28Feb00 	else
//DeadCode RJS 28Feb00 	{
//DeadCode RJS 28Feb00 		mh[4] = mh[8] = 0x7FFF;	//22 33
//DeadCode RJS 28Feb00 		mh[7] = 0;		//32
//DeadCode RJS 28Feb00 		mh[5] = 0;		//23
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		mp[4] = mp[8] = 0x7FFF;	//22 33
//DeadCode RJS 28Feb00 		mp[7] = 0;		//32
//DeadCode RJS 28Feb00 		mp[5] = 0;		//23
//DeadCode RJS 28Feb00 	}
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 	m = 
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 	while (count)
//DeadCode RJS 28Feb00 	{
//DeadCode RJS 28Feb00 		x = vptr->x;
//DeadCode RJS 28Feb00 		y = vptr->z;		// swap y & z to Rowan convention
//DeadCode RJS 28Feb00 		z = vptr->y;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 // 1st, rotate raw points by 'pitch'
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		ny = (mp[4] * y)>>15;
//DeadCode RJS 28Feb00 		ny += (mp[5] * z)>>15;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		nz = (mp[7] * y)>>15;
//DeadCode RJS 28Feb00 		nz += (mp[8] * z)>>15;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 // Forward transform...
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		y = nz;				// swap y & z to normal convention
//DeadCode RJS 28Feb00 		z = ny;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		nx = (bmatp[0] * x)>>14;
//DeadCode RJS 28Feb00 		nx += (bmatp[3] * y)>>14;
//DeadCode RJS 28Feb00 		nx += (bmatp[6] * z)>>14;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		ny = (bmatp[1] * x)>>14;
//DeadCode RJS 28Feb00 		ny += (bmatp[4] * y)>>14;
//DeadCode RJS 28Feb00 		ny += (bmatp[7] * z)>>14;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		nz = (bmatp[2] * x)>>14;
//DeadCode RJS 28Feb00 		nz += (bmatp[5] * y)>>14;
//DeadCode RJS 28Feb00 		nz += (bmatp[8] * z)>>14;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		// Swap to Rowan...
//DeadCode RJS 28Feb00 		x = nx + bmatp[9];
//DeadCode RJS 28Feb00 		z = ny + bmatp[10];
//DeadCode RJS 28Feb00 		y = nz + bmatp[11];
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 // 2nd, rotate raw points by 'hdg'
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		ny = (mh[4] * y)>>15;
//DeadCode RJS 28Feb00 		ny += (mh[5] * z)>>15;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		nz = (mh[7] * y)>>15;
//DeadCode RJS 28Feb00 		nz += (mh[8] * z)>>15;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 // Forward transform...
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		y = nz;				// swap y & z to normal convention
//DeadCode RJS 28Feb00 		z = ny;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		nx = (bmath[0] * x)>>14;
//DeadCode RJS 28Feb00 		nx += (bmath[3] * y)>>14;
//DeadCode RJS 28Feb00 		nx += (bmath[6] * z)>>14;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		ny = (bmath[1] * x)>>14;
//DeadCode RJS 28Feb00 		ny += (bmath[4] * y)>>14;
//DeadCode RJS 28Feb00 		ny += (bmath[7] * z)>>14;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		nz = (bmath[2] * x)>>14;
//DeadCode RJS 28Feb00 		nz += (bmath[5] * y)>>14;
//DeadCode RJS 28Feb00 		nz += (bmath[8] * z)>>14;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		dp->bodyx.f = nx + bmath[9];							//RJS 23Feb00
//DeadCode RJS 28Feb00 		dp->bodyz.f = ny + bmath[10];	//swap back to Rowan	//RJS 23Feb00
//DeadCode RJS 28Feb00 		dp->bodyy.f = nz + bmath[11];							//RJS 23Feb00
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 //DeadCode RJS 23Feb00 // Object transform...
//DeadCode RJS 28Feb00 //DeadCode RJS 23Feb00 
//DeadCode RJS 28Feb00 //DeadCode RJS 23Feb00 		_matrix.transformNC(fpobject_matrix,dp);
//DeadCode RJS 28Feb00 //DeadCode RJS 23Feb00 
//DeadCode RJS 28Feb00 //DeadCode RJS 23Feb00 		dp->bodyx.f +=object_obj3d->Body.X.f;
//DeadCode RJS 28Feb00 //DeadCode RJS 23Feb00 		dp->bodyy.f +=object_obj3d->Body.Y.f;
//DeadCode RJS 28Feb00 //DeadCode RJS 23Feb00 		dp->bodyz.f +=object_obj3d->Body.Z.f;
//DeadCode RJS 28Feb00 //DeadCode RJS 23Feb00 	
//DeadCode RJS 28Feb00 //DeadCode RJS 23Feb00 //deadcode		_matrix.SetClipFlags(*dp);
//DeadCode RJS 28Feb00 //DeadCode RJS 23Feb00 
//DeadCode RJS 28Feb00 //DeadCode RJS 23Feb00 //deadcode		dp->intensity= dp->specFlip= dp->specular=-1;
//DeadCode RJS 28Feb00 
//DeadCode RJS 28Feb00 		dp++;
//DeadCode RJS 28Feb00 		vptr++;
//DeadCode RJS 28Feb00 		count--;
//DeadCode RJS 28Feb00 	}

	DOANIMTRANSFORMHP_PTR	ptr = (DOANIMTRANSFORMHP_PTR )instr_ptr;
	ANIMPOINT_PTR			vptr;
 	DoPointStruc* 			dp = &newco[ptr->vertex];
 	SLong					count = ptr->count;
	float					tx = ptr->Tx;
	float					ty = ptr->Ty;
	float					tz = ptr->Tz;
	float					x, y, z;
	float					nx, ny, nz;
	float*					m = movegunmatrix;

	instr_ptr += sizeof(DOANIMTRANSFORMHP);
	vptr = (ANIMPOINT_PTR)instr_ptr;

	while (count)
	{
		x = vptr->x;
		y = vptr->y;
		z = vptr->z;

//Transform each point...

		nx = (m[0] * x)+(m[3] * y)+(m[6] * z);
		ny = (m[1] * x)+(m[4] * y)+(m[7] * z);
		nz = (m[2] * x)+(m[5] * y)+(m[8] * z);

//Translate...

#ifndef	_NOPOINTS_
		dp->setPosition(nx+tx,
						ny+ty,
						nz+tz	);								//RJS 19May00
#endif

		vptr++;
		dp++;
		count--;
	}

	instr_ptr = (UByteP)vptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doontimer
//Author		Robert Slater
//Date			Fri 10 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doontimer(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("f6");
#endif
	DOONTIMER_PTR	ptr = (DOONTIMER_PTR )instr_ptr;
	UWord			time = *((UWordP)&GlobalAdptr[ptr->animflag]);

	instr_ptr += sizeof(DOONTIMER);
	if (time < ptr->time)
		instr_ptr--;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dofinger
//Author		Robert Slater
//Date			Mon 13 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dofinger(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("f7");
#endif
/*	DOFINGER_PTR	ptr = (DOFINGER_PTR )instr_ptr;
	UWord			nofingers = GlobalAdptr[ptr->anim_nofingers];

	instr_ptr += sizeof(DOFINGER);
	if (ptr->fingerindex < nofingers)
	{
		SLong	now = View_Point->TimeOfDay();
		UByte	frameno = GlobalAdptr[ptr->anim_frameno];
		SLongP	drawtime = (SLongP)&GlobalAdptr[ptr->anim_timedrawn];
		SWordP	totaltime = (SWordP)&GlobalAdptr[ptr->anim_timer];
		SWord	ttime = *totaltime;
		SLong	lasttime = *drawtime;
		SLong	dtime = now - lasttime;
		FingerAnimData*	finger = (FingerAnimData*)&GlobalAdptr[ptr->anim_finger];
		SLong	wx2 = finger->wx2;
		SLong	wy2 = finger->wy2;
		SLong	wz2 = finger->wz2;
		SLong	velx = finger->velx;
		SLong	vely = finger->vely;
		SLong	velz = finger->velz;
		SWord	maxradius = *((SWordP)&GlobalAdptr[ptr->anim_maxradius]);

		ttime += dtime;
		if (velx && vely && velz)
		{
			SLong	deltax = (velx * dtime)/10;
			SLong	deltay = (vely * dtime)/10;
			SLong	deltaz = (velz * dtime)/10;
			Float	vx = Float(velx);
			Float	vy = Float(vely);
			Float	vz = Float(velz);
			Float	friction = (0.1 * Float(dtime)) / Float(Timer_Code.FRAMETIME);

			vx *= friction;
			vy *= friction;
			vz *= friction;

			wx2 += deltax;
			wy2 += deltay;
			wz2 += deltaz;

			finger->velx = SWord(vx);
			finger->vely = SWord(vy);
			finger->velz = SWord(vz);
		}

		finger->wx2 = SLong(wx2);
		finger->wy2 = SLong(wy2);
		finger->wz2 = SLong(wz2);

		*drawtime = now;
		*totaltime = ttime;

		Float	startradius = 50;
		SLong	fadedepth = 255;
		if (ttime > ptr->dusttime)
		{
			SLong	fdelta = ttime - ptr->dusttime;

			fdelta *= 255;
			fdelta /= ptr->fadetime;

			if (fdelta > 255)
				fdelta = 255;

			fadedepth -= fdelta;
		}
		else
		{
			maxradius *= ttime;
			maxradius /= ptr->dusttime;
			if (maxradius < 50)
				maxradius = 50;
		}

		Float	endradius = Float(maxradius);

		IFShare	wwx,wwy,wwz,wwx2,wwy2,wwz2;

		wwx.i =	finger->wx - View_Point->World.X;
		wwy.i = finger->wy - View_Point->World.Y;
		wwz.i = finger->wz - View_Point->World.Z;
		wwx2.i = wx2 - View_Point->World.X;
		wwy2.i = wy2 - View_Point->World.Y;
		wwz2.i = wz2 - View_Point->World.Z;

		_matrix.transform(fpviewer_matrix,wwx,wwy,wwz);
		_matrix.transform(fpviewer_matrix,wwx2,wwy2,wwz2);

		Float	xx,yy,zz;
		Float	xx2,yy2,zz2;

		if (wwz2.f > wwz.f)
		{
			xx = wwx2.f;
			yy = wwy2.f;
			zz = wwz2.f;

			xx2 = wwx.f;
			yy2 = wwy.f;
			zz2 = wwz.f;
		}
		else
		{
			xx = wwx.f;
			yy = wwy.f;
			zz = wwz.f;

			xx2 = wwx2.f;
			yy2 = wwy2.f;
			zz2 = wwz2.f;
		}

		Float	radius = startradius;
		Float	fx = xx2-xx;
		Float	fy = yy2-yy;
		Float	fz = zz2-zz;
		Float	realrad = 50;
		Float	tdist = 0;

		double dist=fx*fx+fy*fy+fz*fz;
		_asm {	fld dist;
				fsqrt;
				fstp dist;
		}

		Float	ddist = 1./dist;
		fx*=ddist; fy*=ddist; fz*=ddist;


		DoPointStruc dp0,dp1,dp2,dp3;
		while (realrad < endradius)
		{
			dp0.bodyx.f = xx;
			dp0.bodyy.f = yy;
			dp0.bodyz.f = zz;

			dp1.bodyx.f = xx;
			dp1.bodyy.f = yy;
			dp1.bodyz.f = zz;

			dp2.bodyx.f = xx;
			dp2.bodyy.f = yy;
			dp2.bodyz.f = zz;

			dp3.bodyx.f = xx;
			dp3.bodyy.f = yy;
			dp3.bodyz.f = zz;

			if (ClipSphere(dp0,dp1,dp2,dp3,realrad)==FALSE)
			{
				POLYGON.createpoly((ImageMapNumber)ptr->imagemap);
				POLYGON.createvert(dp0,minx,miny);
				POLYGON.createvert(dp1,maxx,miny);
				POLYGON.createvert(dp2,maxx,maxy);
				POLYGON.createvert(dp3,minx,maxy);
				POLYGON.drawpoly();
			}

			xx += realrad*fx;
			xy += realrad*fy;
			xz += realrad*fz;

			tdist += realrad;
			realrad = startradius + (((endradius-startradius)*tdist)/dist);
		}
	}*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doambienton
//Author		Robert Slater
//Date			Wed 23 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doambienton(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("f8");
#endif
	DOAMBIENTON_PTR	ptr = (DOAMBIENTON_PTR )instr_ptr;
	UByte			red= ptr->red;
	UByte			green= ptr->green;
	UByte			blue= ptr->blue;

	SetLightingColour(red,green,blue,Land_Scape.currentLighting);//RJS 14Apr00

	instr_ptr += sizeof(DOAMBIENTON);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doambientoff
//Author		Robert Slater
//Date			Wed 23 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doambientoff(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("f9");
#endif
	instr_ptr += sizeof(DOAMBIENTOFF);

	SetLightingColour(shadedRGBhi,shadedRGBlo,shadedRGBamb);			//RJS 25May00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	domovegun
//Author		Robert Slater
//Date			Mon 28 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::domovegun(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("g0");
#endif
	DOMOVEGUN_PTR	ptr = (DOMOVEGUN_PTR) instr_ptr;
	float*			m =	movegunmatrix;
	Float			sin_pitch, cos_pitch;
	Float			sin_hdg, cos_hdg;
	SWord			theHdg = *((UWordP)&GlobalAdptr[ptr->hdgflag]);
	SWord			thePitch = *((UWordP)&GlobalAdptr[ptr->pitchflag]);
	float			mh[9];
	float			mp[9];
	float*			mpp = mp;

/*	if (theHdg > ptr->maxhdef)
		theHdg = ptr->maxhdef;
	else
	{
		if (theHdg < ptr->minhdef)
			theHdg = ptr->minhdef;
	}

	if (thePitch > ptr->maxpdef)
		thePitch = ptr->maxpdef;
	else
	{
		if (thePitch < ptr->minpdef)
			thePitch = ptr->minpdef;
	}*/

	// 0 1 2	11 12 13
	// 3 4 5	21 22 23
	// 6 7 8	31 32 33

	Math_Lib.high_sin_cos((Angles)thePitch,sin_pitch,cos_pitch);
	Math_Lib.high_sin_cos((Angles)-theHdg,sin_hdg,cos_hdg);

	// 21 31 12 13	are all 0

//	pitch generate...
	mp[0] = 1.;
	mp[4] = mp[8] = cos_pitch;	//22 33
	mp[7] = sin_pitch;		//32
	mp[5] = -sin_pitch;		//23
	mp[3] = mp[6] = mp[1] = mp[2] = 0.;

//	hdg generate...
	mh[0] = mh[8] = cos_hdg;	//11 33
	mh[6] = -sin_hdg;			//31
	mh[2] = sin_hdg;			//13
	mh[3] = mh[1] = mh[7] = mh[5] = 0.;
	mh[4] = 1.;

// multiply hdg by pitch

	for(int j=0;j<3;j++)
	{
		*m++	= (mpp[0] * mh[0])
				+ (mpp[1] * mh[3])
				+ (mpp[2] * mh[6]);

		*m++ 	= (mpp[0] * mh[1])
				+ (mpp[1] * mh[4])
				+ (mpp[2] * mh[7]);

		*m++ 	= (mpp[0] * mh[2])
				+ (mpp[1] * mh[5])
				+ (mpp[2] * mh[8]);

		mpp += 3;
	}

	instr_ptr += sizeof(DOMOVEGUN);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dobitsoffcockunset
//Author		Robert Slater
//Date			Wed 22 Mar 2000
//
//Description	Same as bitsoffcock, but true if the flag is NOT set
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dobitsoffcockunset(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("g1");
#endif
	DOBITSOFFCOCK_PTR	ptr = (DOBITSOFFCOCK_PTR )instr_ptr;
	ULong	flag = *((ULongP)&GlobalAdptr[ptr->animflag]);

	flag >>= ptr->bitflag;
	flag &= 1;

	if (flag)
		instr_ptr += ptr->offset;
	else
		instr_ptr += sizeof(DOBITSOFFCOCK);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		doneedle
//Author		Robert Slater
//Date			Wed 12 Apr 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::doneedle(UByte *& instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("g2");
#endif
	DONEEDLE_PTR	ptr = (DONEEDLE_PTR )instr_ptr;
	UByte			val = GlobalAdptr[ptr->animflag];
	SLong			realval=0;
	Float			scale=1;
	D3DVALUE		posx0;
	D3DVALUE		posy0;
	D3DVALUE		posx1;
	D3DVALUE		posy1;
	D3DVALUE		posy2 = newco[2].getPosY();
	D3DVALUE		posz0;
	D3DVALUE		posz1;

	newco[0].getPosition(posx0,posy0,posz0);
	newco[1].getPosition(posx1,posy1,posz1);

	Float			width = posx1 - posx0;						//RJS 19May00
	Float			height = posy1 - posy2;						//RJS 19May00
	Float			xpos,ypos,xoff,yoff;
	Float			valscale;

	switch (ptr->startzero)
	{
	case NEEDLE_BOT:
		scale = 0;
		realval = val;
	break;
	case NEEDLE_MID:
		scale = 0.5;
		realval = SByte(val);
	break;
	case NEEDLE_TOP:
		scale = 1;
		realval = -val;
	break;
	}

	valscale = Float(realval)/255.0;

	if (ptr->horiz)
	{
		xoff = 0;
		yoff = height;
		ypos = posy2;
		xpos = valscale*width;
		xpos = posx0 + (width*scale) + xpos;
	}
	else
	{
		xoff = width;
		yoff = 0;
		xpos = posx0;
		ypos = valscale*height;
		ypos = posy2 + (height*scale) + ypos;
	}

	if (ptr->fat)
	{


	}
	else
	{
		DOLINE	doinst;
		UByteP	pinst = (UByteP) &doinst;

		shape::colour = Colour(31);

#ifndef	_NOPOINTS_
		newco[0].setPosition(xpos,ypos,posz0);					//RJS 19May00
		newco[1].setPosition(xpos + xoff,ypos - yoff,posz1);	//RJS 19May00
#endif
		doinst.start_vertex = 0;
		doinst.end_vertex = 1;

		doline(pinst);
	}

	instr_ptr += sizeof(DONEEDLE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dosetblendtype
//Author		Robert Slater
//Date			Tue 16 May 2000
//
//Description	Sets the transparency blend type for a specified imagemap
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::dosetblendtype(UByteP&	instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("g3");
#endif
	DOSETBLENDTYPE_PTR	ptr = (DOSETBLENDTYPE_PTR) instr_ptr;
	ImageMapDescPtr	imap = Image_Map.GetImageMapPtr(ImageMapNumber(ptr->material));

	imap->blendType = ptr->blendtype;

	instr_ptr += sizeof(DOSETBLENDTYPE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dousefadeenvelope
//Author		Robert Slater
//Date			Thu 18 May 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::dousefadeenvelope(UByteP&	instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("g4");
#endif
	DOUSEFADEENVELOPE_PTR	ptr = (DOUSEFADEENVELOPE_PTR) instr_ptr;
	ULong					fadedepth = GlobalAdptr[ptr->animfadeoffset];

	g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,&fadedepth);

	alphaRestore[alphaRestoreCnt++] = fadedepth;

	instr_ptr += sizeof(DOUSEFADEENVELOPE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dorestorealpha
//Author		Robert Slater
//Date			Thu 18 May 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::dorestorealpha(UByteP&	instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("g5");
#endif
	ULong	fadedepth = alphaRestore[--alphaRestoreCnt];

	g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,&fadedepth);

	instr_ptr += sizeof(DORESTOREALPHA);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		docollisiongoto
//Author		Robert Slater
//Date			Thu 21 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::docollisiongoto(UByteP&	instr_ptr)
{
	if (FixUpCollision || !CollisionOn)
		instr_ptr += sizeof(DOCOLLISIONGOTO);
	else
		instr_ptr += *SWordP(instr_ptr+1);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dosetzbias
//Author		Robert Slater / Jon
//Date			Thu 21 Sep 2000
//
//Description	Only sets a transparent z bias for now.... - JON
//				This pulls the z sort of transparent objects towards the camera
//
//Inputs		The bias value is multiplied by 32, and this is the number of cm
//				the objects are pulled forward by allowing a range from 
//				0 -> 81.92 metres for the fudge.
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::dosetzbias(UByteP&	instr_ptr)
{
	DOSETZBIAS_PTR	ptr = DOSETZBIAS_PTR(instr_ptr);

	g_lpLib3d->SetGlobal( TOGGLE_TRANSPARENT_ZBIAS, ULong(ptr->bias)<<5 );	//JON 3Oct00

	instr_ptr += sizeof(DOSETZBIAS);
}






//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//				      GENERAL SUPPORT ROUTINES
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawSubShape
//Author		Robert Slater
//Date			Mon 3 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void	shape::DrawSubShape(UByteP	thisptr)					//RJS 01Dec97
{
#ifdef	_PROCDEBUG_
	Bollox("g6");
#endif
	DOCALLSHAPE_PTR	ptr = (DOCALLSHAPE_PTR) thisptr;			//RJS 01Dec97
	DoPointStruc	*const	subco=new DoPointStruc[64];//RJS 02Dec97
	Obj3D			tmpobj3d;
	Obj3D*			bakobj3dptr;
	int				index;
//DeadCode DAW 07May99 	Bool			oldsubstat = IsSubShape;
	DoPointStruc	*oldco;
	FPMATRIX bupMatrix=light_matrix;			//PD 8May98
	Bool			oldsubstate = IsSubShape;

	if (subco)
	{
		bakobj3dptr = object_obj3d;
		tmpobj3d = *object_obj3d;

//DEADCODE RJS 4/10/00 		object_obj3d->Shape = ptr->shape;//rjs 28aug98
//DEADCODE RJS 4/10/00 		object_obj3d->IsTransient = 0;//rjs 28aug98
//DEADCODE RJS 4/10/00 		object_obj3d->Body.X.f += newco[ptr->vertex].bodyx.f;
//DEADCODE RJS 4/10/00 		object_obj3d->Body.Y.f += newco[ptr->vertex].bodyy.f;
//DEADCODE RJS 4/10/00 		object_obj3d->Body.Z.f += newco[ptr->vertex].bodyz.f;
//DEADCODE RJS 4/10/00 		object_obj3d->AngH = (Angles)ptr->hdg;
//DEADCODE RJS 4/10/00 		object_obj3d->AngC = (Angles)ptr->pitch;
//DEADCODE RJS 4/10/00 		object_obj3d->AngR = (Angles)ptr->roll;
		tmpobj3d.Shape = ptr->shape;

		tmpobj3d.Body.X.f = newco[ptr->vertex].getPosX();
		tmpobj3d.Body.Y.f = newco[ptr->vertex].getPosY();
		tmpobj3d.Body.Z.f = newco[ptr->vertex].getPosZ();

//DeadCode RJS 19May00 		tmpobj3d.Body.X.f += newco[ptr->vertex].bodyx.f;
//DeadCode RJS 19May00 		tmpobj3d.Body.Y.f += newco[ptr->vertex].bodyy.f;
//DeadCode RJS 19May00 		tmpobj3d.Body.Z.f += newco[ptr->vertex].bodyz.f;
		tmpobj3d.AngH = Angles(ptr->hdg);
		tmpobj3d.AngC = Angles(ptr->pitch);
		tmpobj3d.AngR = Angles(ptr->roll);

		oldco = newco;												//RJS 02Dec97
		newco = subco;

//DEADCODE RJS 4/10/00 		FPMATRIX_PTR	matrixbak = fpobject_matrix;
//DEADCODE RJS 4/10/00 		fpobject_matrix = subMatrixP;

		IsSubShape = TRUE;
		SHAPE.draw_shape(&tmpobj3d);				//RJS 08Apr00
		IsSubShape = oldsubstate;

		object_obj3d = bakobj3dptr;

//DEADCODE RJS 4/10/00 		fpobject_matrix = matrixbak;

		newco = oldco;

//DEADCODE RJS 4/10/00 		*object_obj3d = backobj3d;

//DeadCode DAW 07May99 		IsSubShape = oldsubstat;
 
		delete subco;												//RJS 02Dec97
	}
	light_matrix=bupMatrix;						//PD 8May98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterpLoop
//Author		Robert Slater
//Date			Wed 19 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
 void	shape::InterpLoop(UByteP	instr_ptr)
{
#ifdef	_PROCDEBUG_
	Bollox("g7");
#endif
	UWord	instruction;
	UWord	lastinst = -1;
	SLong	instcnt = 0;
//	ULong	instcnt = 0;
//	struct	fart
//	{
//		SHPINST	instno;
//		UByteP	address;
//		UWord	offset;
//	};
//	fart	DInst[512];

	for(;;)
	{
		instruction = (UWord )*instr_ptr;
		instr_ptr ++;

//		DInst[instcnt].instno = (SHPINST)instruction;	//RJS 16Jun98
//		DInst[instcnt].offset = instr_ptr - shphedr;	//RJS 16Jun98
//		DInst[instcnt++].address = instr_ptr;
//		DInst[instcnt].instno = (SHPINST)0;

		if (instruction > dosetglassrangeno)
			_Error.EmitSysErr(__FILE__":Bollocks instruction!!");

		if(instruction==doretno) break;

		(*InterpTable[instruction]) (instr_ptr);

		lastinst = instruction;
		instcnt++;

//		if (IsAircraft && current_level>=2)
//			IsAircraft|=4;

	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestHitBoxes
//Author		Robert Slater
//Date			Mon 24 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::TestHitBoxes(ItemPtr	itm, ShapeNum theShape,animptr& AnimPtr, UByteP	rsdptr)//RJS 21Apr99
{
	UByteP			instr_ptr;									//RJS 17Sep98
	Bool			go = TRUE;									//RJS 17Sep98
	UWord			instruction;								//RJS 17Sep98
	ShapeDescPtr	sdptr = (ShapeDescPtr) rsdptr;				//RJS 17Sep98
																//RJS 17Sep98
	damage_ItemPtr = itm;										//RJS 17Sep98
	damage_AnimPtr = AnimPtr;									//RJS 17Sep98
	damage_Shape = theShape;									//RJS 16Nov98
	damage_Sdptr = (UByteP) SHAPESTUFF.GetShapePtr(itm->shape);	//RJS 16Nov98
																//RJS 17Sep98

#ifdef	_FXTEST_
logDamage = false;
#endif

	collisionDepth = 0;
	CollisionOn = FALSE;
	HitThisOffset = 0;											//RJS 17Sep98
	DamageNow = FALSE;											//RJS 17Sep98
	CollisionCnt = 0;											//RJS 17Sep98
	_Replay.FakeCollisionOn=false;								//AMM 12Jul99

	Squad_Diary.SetAC(itm,AnimPtr);										//RJS 21Sep00
																//RJS 17Sep98
	instr_ptr = (UByteP )sdptr + sdptr->CollisionOffset;		//RJS 17Sep98
																//RJS 17Sep98
	while (go)		  											//RJS 17Sep98
	{															//RJS 17Sep98
		instruction = (UWord) *instr_ptr;						//RJS 17Sep98
																//RJS 17Sep98
		instr_ptr ++;											//RJS 17Sep98
																//RJS 17Sep98
		if (instruction > dosetglassrangeno)					//RJS 17Sep98
			_Error.EmitSysErr(__FILE__":Bad instruction in collision (%d)",instruction);//RJS 17Sep98
																//RJS 17Sep98
		if (	((instruction == doretno) && collisionDepth)	//RJS 17Sep98
			||	(instruction==doendno))							//RJS 17Sep98
			break;												//RJS 17Sep98
																//RJS 17Sep98
		if (_Replay.FakeCollisionOn)							//AMM 12Jul99
		{
			collisionDepth++;
			CollisionOn=FALSE;									//AMM 12Jul99
		}

		(*InterpTable[instruction]) (instr_ptr);				//RJS 17Sep98

		if (_Replay.FakeCollisionOn)							//AMM 12Jul99
			CollisionOn=TRUE;									//AMM 12Jul99
	}															//RJS 17Sep98
																//RJS 17Sep98
	_Replay.FakeCollisionOn=false;								//AMM 12Jul99
	CollisionOn = DamageNow;									//RJS 17Sep98
																//RJS 17Sep98
	Squad_Diary.UpdateACDamage();								//RJS 23Feb00

	return(CollisionOn);										//RJS 17Sep98
}





	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ForceDamage
//Author		Robert Slater
//Date			Fri 21 Feb 1997
//
//Description	Forces a new damage state on a specified damage byte.
//				This in-turn pretends there has been a hit-box collision,
//				and executes the relevant special effects....
//
//Inputs		Item
//				Address of damage byte to hit
//				Its new state
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ForceDamage(	ItemPtr		itm,
							ItemPtr		theShooter,			//JIM 11Mar99
  							UByteP	 	damageptr,		
 							BitStates 	whatstate,
							UByte		HitterStrength,
							Bool		commsdamage)
{
#ifdef	_PROCDEBUG_
	Bollox("g8");
#endif
	if (*damageptr != whatstate)								//RJS 27Aug98
	{
		animptr			adptr;									//RJS 21Apr99
		UWord			offset;
		ShapeDescPtr	sdptr;
		UByteP			instr_ptr;
		Bool			go;
		UWord			instruction;
		Bool			oldcolflag;
		ULong			oldoffset;
		SLong			oldcollogcnt = ColLogCnt;				//DAW 07Apr99

		BoxCol::ResetCollisionStuff();

		BoxCol::Col_Shooter = theShooter;						//JIM 11Mar99

		bool	oldState = BoxCol::SetTestState(true);					//AMM 4Jul00

		oldcolflag = CollisionOn;
		oldoffset = HitThisOffset;

		adptr = itm->Anim;										//RJS 21Apr99
//DeadCode AMM 26Apr99 		animptr		damageanim = adptr;
//DeadCode AMM 26Apr99 		damageanim = damageptr;
//DeadCode AMM 26Apr99 		offset = damageanim - adptr;
		offset = adptr.Offset(damageptr);						//AMM 26Apr99
		sdptr = SHAPESTUFF.GetShapePtr(itm->shape);

		Squad_Diary.SetAC(itm,adptr);									//RJS 21Sep00
		if ((sdptr->CollisionOffset != 0) && (offset != 0))
		{
			damage_ItemPtr = itm;								//RJS 17Sep98
			damage_AnimPtr = adptr;								//RJS 17Sep98
			damage_Shape = itm->shape;							//RJS 17Sep98
			damage_GrpElmt = -1;								//RJS 17Sep98
			damage_Sdptr = (UByteP) sdptr;						//RJS 17Sep98

			go = TRUE;
			HitThisOffset = offset;

			lastdamage[0] = *damageptr;
			lastdamptr = damageptr;

//DeadCode AMM 26Apr99 			*damageptr = whatstate;
			damage_ItemState = whatstate;						//AMM 26Apr99
			CommsDamage = commsdamage;
			CollisionOn = FALSE;
			collisionDepth = 0;											//AMM 3Jul00

			BoxCol::HitterStrength = HitterStrength;

			switch (SHAPESTUFF.GetShapeScale(sdptr))				//RJS 30Mar98
			{
				case SHP_GRP:
					_Error.EmitSysErr(__FILE__":Bad shape type field (SHAPE NUMBER %d)",itm->shape);
					break;
				case SHP_1CM:
					damage_Scale = 0;										
					break;												
				case SHP_4CM:
					damage_Scale = 2;										
					break;												
				case SHP_16CM:
					damage_Scale = 4;										
					break;
			}

			instr_ptr = (UByteP )sdptr + sdptr->CollisionOffset;

			_Replay.FakeCollisionOn=false;						//AMM 12Jul99
			while (go)
			{
				instruction = (UWord) *instr_ptr;

				instr_ptr ++;
				if (instruction > dosetglassrangeno)				//RJS 11Feb98
					_Error.EmitSysErr(__FILE__":Bad instruction in collision (%d)",instruction);//RJS 11Feb98

				if (	((instruction == doretno) && collisionDepth)//CollisionOn)	//AMM 3Jul00
					||	(instruction==doendno))
					break;

				if (_Replay.FakeCollisionOn)					//AMM 12Jul99
				{
					CollisionOn=FALSE;							//AMM 12Jul99
					collisionDepth++;									//AMM 3Jul00
				}

				(*InterpTable[instruction]) (instr_ptr);

				if (_Replay.FakeCollisionOn)					//AMM 12Jul99
					CollisionOn=TRUE;							//AMM 12Jul99
			}

			_Replay.FakeCollisionOn=false;						//AMM 12Jul99
			if (!oldcollogcnt)									//DAW 07Apr99
			{													//DAW 07Apr99
				FixUpColLog();									//DAW 07Apr99
				BoxCol::ProcessEffectQueue(itm);				//DAW 07Apr99
			}													//DAW 07Apr99
		}

		Squad_Diary.UpdateACDamage();							//RJS 23Feb00

		BoxCol::SetTestState(oldState);							//AMM 4Jul00

		HitThisOffset = oldoffset;
		CommsDamage = FALSE;
		CollisionOn = oldcolflag;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroupDeps
//Author		Robert Slater
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GetGroupDeps(UByteP	inst_ptr,SLong	&nextdep, SLong &prevdep)
{
	SWord inst = *inst_ptr;

	if (inst != dogroupno)
	{
		nextdep = 0;
		prevdep = 0;
	}
	else
	{
		inst_ptr++;

		DOGROUP_PTR	temp = (DOGROUP_PTR) inst_ptr;
	
		prevdep = temp->element_prev;
		nextdep = temp->element_next;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroupElement
//Author		Paul.   
//Date			Fri 8 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	   	 0 fail,
//				 1 - 255 success, 
//
//------------------------------------------------------------------------------
SLong shape::GetGroupElement(UByte *&instr_ptr,
							ShapeNum& shape,
							SLong& x, SLong& y, SLong& z,
							SLong range,
							UByteP	*PrevIptr,
							SWordP	heading,
							UByteP	*NextIptr	)
{
	SWord	inst;
	SLong	priority;											//RJS 14Nov96

	inst = (SWord )*instr_ptr;
	instr_ptr ++;

	if(inst!=dogroupno)
		return(0);

	DOGROUP_PTR temp = (DOGROUP_PTR)instr_ptr;

	shape = (ShapeNum )temp->shapenum;

	x = temp->xoffset;
	y = temp->yoffset;
	z = temp->zoffset;
	priority = temp->element_number;							//RJS 27Feb98
	if (PrevIptr)
		*PrevIptr = (UByteP)temp;
	if (heading)
		*heading = temp->angle;

	temp++;

	instr_ptr = (UByte *)temp;
	if (NextIptr)												//RJS 30Jun99
	{
		if (*instr_ptr == dogroupno)
			*NextIptr = (instr_ptr + 1);
		else
			*NextIptr = NULL;
	}

	return(priority);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLiveElement
//Author		Jim Taylor
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int shape::GetLiveElementPos(int num, ItemPtr itm, SLong& x, SLong& y, SLong& z)
{
	ShapeDescPtr sdptr,newshpp;
	SLong	ret_val;
	SByte	priority;											//RJS 22Nov96
	int		actualeltnum=0;
	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
	ShapeNum	newshp;
	if (SHAPESTUFF.GetShapeScale(sdptr)==SHP_GRP)				//JIM 06Sep96
	{
//DeadCode RJS 21Apr99 		UByteP	animdataptr = (UByteP )itm->Anim;
		MinAnimData*	aptr = (MinAnimData*) itm->Anim;			  //MS 06/05/99
		UByteP	li,instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		while ((priority = GetGroupElement(instr_ptr,newshp,x,y,z))!=0 )//RJS 22Nov96
		{
			actualeltnum++;
			if ((aptr->itemstate!=DEAD) && priority < 0)		//RJS 22Nov96
			{
				if (num==0)	return(actualeltnum);
				num--;
			}
			aptr=(MinAnimData*)((int)aptr+GetElementAnimOffset(newshp));//RJS 20Nov97
		}
		x=y=z=0;
		return(0);
	}
	else
	{
		x=y=z=0;
		if (itm->Status.size==FORMATIONSIZE)
		{
			if (itm->Status.deadtime)
				num++;
			FormationItemPtr i2=*itm;

			{
				FormationItemPtr i3=i2;
//Old_Code PD 09Dec96 				while (i3 && !i3->uniqueID.deaded && num--)
//Old_Code PD 09Dec96 				{
//Old_Code PD 09Dec96 					i2=i3;
//Old_Code PD 09Dec96 					i3=i3->follower;
//Old_Code PD 09Dec96 				}

				while (i3)
				{
					if (!i3->Status.deadtime)
					{
						num--;
					}
					if (num<=0)	break;
					i2=i3;
					i3=i3->follower;
				}

				if (i3)
					i2=i3;
			}

			if (i2)
			{
				x=itm->World.X-i2->World.X;
				y=itm->World.Y-i2->World.Y;
				z=itm->World.Z-i2->World.Z;
				return(1);
			}
			else
				return(0);
		}
		if (itm->Status.deadtime)
			return(0);
		else
			return(1);
	}
}

void	TraceChain(int yoff);
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetAnimData
//Author		Paul.   
//Date			Tue 26 Mar 1996
//
//Description	Uses functional GetAnimDataSize to get size, now
//
//Inputs		The item to initialise,
//				The weapon pack to be used (if there is one)...
//
//Returns	
//
//------------------------------------------------------------------------------
SLong shape::SetAnimData(itemptr itm,SWord pack)
{
	AnimWeaponPack = pack;
	SLong	animdatasize;
	SLong	animflagsize;

	animdatasize = GetAnimDataSize(itm->shape);

	if (itm->Anim != NULL)										//RJS 21Apr99
		itm->Anim.Delete();										//RJS 21Apr99
	UByteP	p;
#ifdef DEBUG_NEW_MODE
	#undef	new
	itm->Anim = p = new (__HERE__,itm->Status.size) UByte[animdatasize];
	#define	new DEBUG_NEW
#else
	itm->Anim = p = new UByte[animdatasize];
#endif
	
	for (int i=0;i<animdatasize;i++)							//JIM 06Sep96
		p[i]=0;													//JIM 06Sep96

#ifndef	NDEBUG

	itm->Anim = AnimSizeField(animdatasize);					//RJS 14Jun00

	animflagsize = 0;
	SetAnimDataFlags(itm->shape,itm->Anim,animflagsize);		//RJS 21Apr99
#endif
	
	InitAnimData(itm);

	return(animdatasize);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNumberOfLaunchers
//Author		Robert Slater
//Date			Wed 21 Aug 1996
//
//Description	Calculates number of launchers in a shape
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte shape::GetNumberOfLaunchers(ShapeNum shpno)
{
	ShapeDescPtr	sdptr;
//DeadCode RJS 05Nov99 	UByteP			launcher_ptr = NULL;
	UByte 			*instr_ptr;
	UWord		 	instruction, last_inst;
//DeadCode RJS 05Nov99 	Bool			go=TRUE;
	UByte			nolaunchers;
	DOLAUNCHER_PTR	lptr;

	nolaunchers = 0;

	sdptr = SHAPESTUFF.GetShapePtr(shpno);

//DeadCode RJS 05Nov99 	launcher_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

	if (sdptr->LauncherDataSize)
	{
		Bool			go=TRUE;
		UByteP			launcher_ptr;							//AMM 30Jul99

		launcher_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;//AMM 30Jul99

		instr_ptr = launcher_ptr;

		while (go)
		{
			instruction = (UWord )*instr_ptr;

			instr_ptr ++;
//DeadCode RJS 19Dec97 			instruction>>=1;

			if(instruction>dosetglassrangeno || instruction==0)
				_Error.EmitSysErr(__FILE__":Bad instruction in launcher size (%d)",instruction);

			if(instruction==doretno || instruction==doendno)
				go=FALSE;
			else
			{
				switch (instruction)
				{
					case dolauncherno:
						{
							lptr = (DOLAUNCHER_PTR) instr_ptr;	//RJS 09Apr98
							instr_ptr += sizeof(DOLAUNCHER);

							if (lptr->lnchrtype < LT_CONTACT)	//RJS 09Apr98
								nolaunchers++;					//RJS 09Apr98
						}
					break;
					default:
						_Error.EmitSysErr(__FILE__":Bad launcher instruction (%d)",instruction);
				}
			}

			last_inst = instruction;
		}
	}

	return(nolaunchers);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAnimDataSizeAndCheck
//Author		Robert Slater
//Date			Fri 30 Oct 1998
//
//Description	Should never be a group......
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong shape::GetAnimDataSizeAndCheck(ShapeNum shpno, AnimSizes  theanim, Bool &isTrue)
{
	ShapeDescPtr	sdptr = (ShapeDescPtr) SHAPESTUFF.GetShapePtr(shpno);
	SLong			ret_val;
	SWord			animdatasize = sdptr->AnimDataSize;

	isTrue = FALSE;

	if (animdatasize > -1)									
	{
		if (animdatasize == theanim)
			isTrue = TRUE;

		switch (animdatasize)				
		{											
			case MINANIM:			RETURN(sizeof(MinAnimData));
			case POLYPITANIM:		RETURN(sizeof(PolyPitAnimData));
			case BLOKESANIM: 		RETURN(sizeof(BlokesAnimData));
			case SIMPLEAIRCRAFTANIM:		RETURN(sizeof(SimpleAircraftAnimData));//RJS 17Nov99
			case AIRCRAFTANIM:		RETURN(sizeof(AircraftAnimData));
			case SUNANIM:			RETURN(sizeof(SunAnimData ));
			case WINDSOCANIM:		RETURN(sizeof(WindsocAnimData ));
			case BARAGEANIM:		RETURN(sizeof(BarageAnimData ));
			case MOVEGUNANIM:		RETURN(sizeof(MoveGunAnimData ));
			case TANKANIM:			RETURN(sizeof(TwoGunAnimData ));
			case TRUCKANIM:			RETURN(sizeof(MoveGunAnimData ));
			case TRAINANIM:			RETURN(sizeof(TrainAnimData ));
			case TROOPANIM:			RETURN(sizeof(TroopAnimData ));
			case BRIDGEANIM:		RETURN(sizeof(MinAnimData ));//RJS 18Apr99
			case CLONEANIM:			RETURN(sizeof(CloneAnimData ));
			case FLAREANIM:			RETURN(sizeof(FlareAnimData ));
			case THUGANIM:			RETURN(sizeof(ThugAnimData ));
			case MISSILEANIM:		RETURN(sizeof(MissileAnimData ));
			case DEBRISANIM:		RETURN(sizeof(DebrisAnimData ));//RJS 20Jan99
			case SMOKETRAILANIM:	RETURN(sizeof(SmokeTrailAnimData ));//RJS 21Jan99
			case PARACHUTEANIM:		RETURN(sizeof(ParachuteAnimData ));//RJS 25Mar99
			case LAUNCHERANIM:		RETURN(sizeof(LauncherAnimData ));//RJS 16Apr99
			case BIRDLAUNCHERANIM:	RETURN(sizeof(BirdLauncherAnimData));//RJS 01Dec99
			case BALLOONANIM:		RETURN(sizeof(BalloonAnimData));//RJS 15Dec99
			case WIREANIM:			RETURN(sizeof(MinAnimData ));//RJS 21Dec99
			case AMBIENCEANIM:		RETURN(sizeof(MinAnimData ));//RJS 09Jun00
			case TWOGUNANIM:		RETURN(sizeof(TwoGunAnimData ));	//RJS 27Jun00
			default:	//unique number below 4					
				RETURN(3);										
		}
	}
	else
		return(-animdatasize);	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAnimDataSize
//Author		Paul.				//JIM 06Sep96
//Date			Tue 26 Mar 1996
//
//Description	Modified so that correct value for groups is also returned//JIM 06Sep96
//				Also fills launcher count for group, but doesn't allocate any memory!//JIM 06Sep96
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong shape::GetAnimDataSize(ShapeNum shpno)
{
	ShapeDescPtr sdptr,newshpp;
	SLong	ret_val;
	SWord	animdatasize;										//RJS 30Jun97

	sdptr = SHAPESTUFF.GetShapePtr(shpno);
	ShapeNum	newshp;

	if (SHAPESTUFF.GetShapeScale(sdptr)==SHP_GRP)				//JIM 06Sep96
		if (sdptr->AnimDataSize>1)								//JIM 06Sep96
			RETURN(sdptr->AnimDataSize);						//JIM 06Sep96
		else													//JIM 06Sep96
		{														//JIM 06Sep96
			ULong	elementcnt = 0;
			ULong	haslaunchers=0;
			SLong	tmp,										//JIM 06Sep96
					animdatasize = 0;
			UByteP	instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
			UByteP	li = UByteP(sdptr);							//RJS 20Oct00

			while (GetGroupElement(instr_ptr,newshp,tmp,tmp,tmp))
			{
				newshpp=SHAPESTUFF.GetShapePtr(newshp);
				animdatasize += GetElementAnimOffset(newshp);	//RJS 20Nov97
				haslaunchers|=(ULong) newshpp->LauncherDataSize;
				li=instr_ptr;
				elementcnt++;
			}
			if (!elementcnt)									//DAW 23Apr99
				animdatasize = sizeof(MinAnimData) + 1;			//DAW 23Apr99

			sdptr->AnimDataSize=animdatasize;
			if (haslaunchers)
				sdptr->LauncherDataSize=li-(UByteP)sdptr;
		 	return(animdatasize);
		}
	else
	{
		animdatasize = sdptr->AnimDataSize;						//RJS 30Jun97
		if (animdatasize > -1)									//RJS 30Jun97
		{
			switch (animdatasize)								//RJS 30Jun97
			{														//JIM 06Sep96
				case MINANIM:			RETURN(sizeof(MinAnimData));//JIM 06Sep96
				case POLYPITANIM:		RETURN(sizeof(PolyPitAnimData));
				case BLOKESANIM: 		RETURN(sizeof(BlokesAnimData));
				case SIMPLEAIRCRAFTANIM: RETURN(sizeof(SimpleAircraftAnimData));//RJS 17Nov99
				case AIRCRAFTANIM:		RETURN(sizeof(AircraftAnimData));
				case SUNANIM:			RETURN(sizeof(SunAnimData ));						//PD 24Jun96
				case WINDSOCANIM:		RETURN(sizeof(WindsocAnimData ));//RJS 05Jun97
				case BARAGEANIM:		RETURN(sizeof(BarageAnimData ));
				case MOVEGUNANIM:		RETURN(sizeof(MoveGunAnimData ));
				case TANKANIM:			RETURN(sizeof(TwoGunAnimData ));//RJS 17Oct96
				case TRUCKANIM:			RETURN(sizeof(MoveGunAnimData ));//JIM 14Dec96
				case TRAINANIM:			RETURN(sizeof(TrainAnimData ));//RJS 03Mar98
				case TROOPANIM:			RETURN(sizeof(TroopAnimData ));//RJS 07Nov96
				case BRIDGEANIM:		RETURN(sizeof(MinAnimData ));//RJS 18Apr99
				case CLONEANIM:			RETURN(sizeof(CloneAnimData ));//RJS 21Jan98
				case FLAREANIM:			RETURN(sizeof(FlareAnimData ));//RJS 21Jan98
				case THUGANIM:			RETURN(sizeof(ThugAnimData ));//RJS 03Mar98
				case MISSILEANIM:		RETURN(sizeof(MissileAnimData ));//RJS 03Mar98
				case DEBRISANIM:		RETURN(sizeof(DebrisAnimData ));//RJS 20Jan99
				case SMOKETRAILANIM:	RETURN(sizeof(SmokeTrailAnimData ));//RJS 21Jan99
				case PARACHUTEANIM:		RETURN(sizeof(ParachuteAnimData ));//RJS 25Mar99
				case LAUNCHERANIM:		RETURN(sizeof(LauncherAnimData ));//RJS 16Apr99
				case BIRDLAUNCHERANIM:	RETURN(sizeof(BirdLauncherAnimData));//RJS 01Dec99
				case BALLOONANIM:		RETURN(sizeof(BalloonAnimData));//RJS 15Dec99
				case WIREANIM:			RETURN(sizeof(MinAnimData ));//RJS 21Dec99
				case AMBIENCEANIM:		RETURN(sizeof(MinAnimData ));//RJS 09Jun00
				case TWOGUNANIM:		RETURN(sizeof(TwoGunAnimData ));	//RJS 27Jun00
				default:	//unique number below 4					//JIM 06Sep96
					RETURN(3);										//JIM 06Sep96
			}
		}
		else
			return(-animdatasize);								//RJS 30Jun97
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetElementYDelta
//Author		Robert Slater
//Date			Thu 20 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SByte	shape::GetElementYDelta(ShapeNum	shpno, animptr	&adptr, Coords3D&	pos, SLong centreY)
{
	SByte			delta = 0;										//RJS 09Jun99
	Bool			isTrue;
	MinAnimData*	mad = (MinAnimData*) adptr;

	adptr += GetAnimDataSizeAndCheck(shpno,BRIDGEANIM,isTrue);
	if (centreY)
	{	
		if (isTrue)
		{
			if (mad->itemstate == DEAD)								//RJS 09Jun99
			{
	//DeadCode RJS 21Apr99 			delta = *((SByteP)adptr);
				delta = (SByte) adptr[0];
				if (delta == -128)
				{
					SLong	ey = _Collide.AccurateGroundAltitude(pos);//RJS 28Apr99
					if (ey)											//RJS 28Apr99
					{												//RJS 28Apr99
						ey -= pos.Y;								//RJS 28Apr99

						ey >>= 4;

						if (ey < -127)
							ey = -127;
						else
						{
							if (ey > 127)
								ey = 127;
						}

						delta = SByte(ey);
						adptr[0] = (UByte)delta;						//RJS 21Apr99
					}
					else
					{
						//We don't have real altitude!!
						delta = 0;									//RJS 28Apr99
					}
				}
			}
		}
		else
		{
			// Init Group Y Delta here....							//DAW 01Dec98
			delta = (SByte) adptr[0];								//RJS 21Apr99
			if (delta == -128)										//DAW 01Dec98
			{														//DAW 01Dec98
				SLong	ey = _Collide.AccurateGroundAltitude(pos);	//RJS 28Apr99
				if (ey)
				{
					ey -= pos.Y;									//RJS 28Apr99
																	//DAW 01Dec98
					ey >>= 4;											//DAW 01Dec98
																		//DAW 01Dec98
					if (ey < -127)										//DAW 01Dec98
						ey = -127;										//DAW 01Dec98
					else												//DAW 01Dec98
					{													//DAW 01Dec98
						if (ey > 127)									//DAW 01Dec98
							ey = 127;									//DAW 01Dec98
					}													//DAW 01Dec98
																		//DAW 01Dec98
					delta = SByte(ey);									//DAW 01Dec98
					adptr[0] = (UByte)delta;							//RJS 21Apr99
				}
				else
				{
					//We don't have real altitude!!
					delta = 0;										//RJS 28Apr99
				}
			}														//DAW 01Dec98
		}
	}

	adptr += 1;													//RJS 21Apr99

	return(delta);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitAnimData
//Author		Paul.   
//Date			Tue 26 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::InitAnimData(itemptr itm)
{
	DefaultAnimData(itm,itm->Anim);								//RJS 21Apr99

//DeadCode RJS 06Jul98 	ShapeDescPtr	sdptr;
//DeadCode RJS 06Jul98 	UByteP			instr_ptr;
//DeadCode RJS 06Jul98 	Bool			haslaunchers = FALSE;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 	UByteP	animdataptr = (UByteP )itm->Anim;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 	globinitairitem = NULL;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 	switch (SHAPESTUFF.GetShapeScale(sdptr))					//PD 23Apr96
//DeadCode RJS 06Jul98 	{
//DeadCode RJS 06Jul98 		case SHP_GRP:
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 			SLong	tmp;
//DeadCode RJS 06Jul98 			ShapeNum	newshp;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 			instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 			while (GetGroupElement(instr_ptr,newshp,tmp,tmp,tmp))
//DeadCode RJS 06Jul98 			{
//DeadCode RJS 06Jul98 				if (GetNumberOfLaunchers(newshp) > 0)
//DeadCode RJS 06Jul98 					haslaunchers = TRUE;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 				InitItemAnim(animdataptr,newshp);
//DeadCode RJS 06Jul98 				*animdataptr++ = 0x80;							//RJS 20Nov97
//DeadCode RJS 06Jul98 			}
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 			if (haslaunchers)
//DeadCode RJS 06Jul98 				sdptr->Type.haslaunchers = TRUE;
//DeadCode RJS 06Jul98 			else
//DeadCode RJS 06Jul98 				sdptr->Type.haslaunchers = FALSE;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 			break;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 		case SHP_1CM:
//DeadCode RJS 06Jul98 		case SHP_4CM:
//DeadCode RJS 06Jul98 		case SHP_16CM:
//DeadCode RJS 06Jul98 			if (itm->Status.size == AirStrucSize)					//RJS 13May98
//DeadCode RJS 06Jul98 			{
//DeadCode RJS 06Jul98 				AirStrucPtr	asptr = (AirStrucPtr) itm;
//DeadCode RJS 06Jul98 				asptr->weap.left.mass = 0;
//DeadCode RJS 06Jul98 				asptr->weap.left.drag = 0;
//DeadCode RJS 06Jul98 				asptr->weap.left.int_fuel = 0;
//DeadCode RJS 06Jul98 				asptr->weap.left.int_fuel_leakage = 0;
//DeadCode RJS 06Jul98 				asptr->weap.left.ext_fuel = 0;
//DeadCode RJS 06Jul98 				asptr->weap.left.ext_fuel_leakage = 0;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 				asptr->weap.centre.mass = 0;
//DeadCode RJS 06Jul98 				asptr->weap.centre.drag = 0;
//DeadCode RJS 06Jul98 				asptr->weap.centre.int_fuel = 0;
//DeadCode RJS 06Jul98 				asptr->weap.centre.int_fuel_leakage = 0;
//DeadCode RJS 06Jul98 				asptr->weap.centre.ext_fuel = 0;
//DeadCode RJS 06Jul98 				asptr->weap.centre.ext_fuel_leakage = 0;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 				asptr->weap.right.mass = 0;
//DeadCode RJS 06Jul98 				asptr->weap.right.drag = 0;
//DeadCode RJS 06Jul98 				asptr->weap.right.int_fuel = 0;
//DeadCode RJS 06Jul98 				asptr->weap.right.int_fuel_leakage = 0;
//DeadCode RJS 06Jul98 				asptr->weap.right.ext_fuel = 0;
//DeadCode RJS 06Jul98 				asptr->weap.right.ext_fuel_leakage = 0;
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 				asptr->weap.UseIntFuel = TRUE;		//Default fuel switch	RJS 23Jun98
//DeadCode RJS 06Jul98 				asptr->weap.FuelDumped = TRUE;		//Default fuel dump		RJS 23Jun98
//DeadCode RJS 06Jul98 
//DeadCode RJS 06Jul98 				globinitairitem = asptr;
//DeadCode RJS 06Jul98 			}
//DeadCode RJS 06Jul98 			InitItemAnim(animdataptr,itm->shape);					//RJS 13May98
//DeadCode RJS 06Jul98 			break;
//DeadCode RJS 06Jul98 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitItemAnim
//Author		Paul.   
//Date			Wed 27 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord shape::InitItemAnim(animptr& adptr,ShapeNum shpno, SLong groupindex)//RJS 08Dec99
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shpno);		//RJS 30Jun97
	SWord			storesweight = 0;							//RJS 30Jun97
	SWord			animdatasize = sdptr->AnimDataSize;			//RJS 30Jun97
 	MinAnimData*	mad = (MinAnimData*) adptr;					//RJS 22Oct97
	int				maxGuns = 1;
 
  	mad->IsInvisible = 0;										//RJS 17Nov98

	if (animdatasize > -1)										//RJS 30Jun97
	{
		switch (animdatasize)									//RJS 30Jun97
		{
			default:
			case MINANIM:										//RJS 11Nov97
				adptr += sizeof(MinAnimData);					//RJS 11Nov97
			break;											//RJS 11Nov97
			case WINDSOCANIM:										//RJS 05Jun97
				adptr += sizeof(WindsocAnimData);					//RJS 05Jun97
				break;
			case DEBRISANIM:									//RJS 20Jan99
				adptr += sizeof(DebrisAnimData);				//RJS 20Jan99
				break;											//RJS 20Jan99

			case TRAINANIM:											//RJS 09Dec96
			{
				TrainAnimData* aptr;								//RJS 09Jan97
				aptr = (TrainAnimData* )adptr;						//RJS 09Jan97
				InitLauncherAnim(adptr,shpno);						//RJS 04Jun99
			}														//RJS 09Dec96
				adptr += sizeof(TrainAnimData);						//RJS 07Feb97
				break;												//RJS 09Dec96
			case TRUCKANIM:											//DAW 14Dec96
			case TANKANIM:
			{
				MoveGunAnimData*	mptr=(MoveGunAnimData*) adptr;	  	
//Dead				mptr->nolaunchers = 0;								//RJS 23Aug96
				InitLauncherAnim(adptr,shpno);
				if (mptr->nolaunchers >2)
					_Error.EmitSysErr("Shape %x Num launchers %i !=1",shpno,mptr->nolaunchers);

				adptr+=sizeof(MoveGunAnimData);
		 		break;
			}
			case TWOGUNANIM:
				maxGuns = 2;
			case MOVEGUNANIM:
			{
				MoveGunAnimData*	mptr=(MoveGunAnimData*) adptr;	  	
				mptr->nolaunchers = 0;								//RJS 23Aug96
				InitLauncherAnim(adptr,shpno);
				if (mptr->nolaunchers > maxGuns)
					_Error.EmitSysErr("Agh %i",shpno);

				adptr+=sizeof(MoveGunAnimData);
		 		break;
			}
			case POLYPITANIM:										//PD 15Apr96
				{
				PolyPitAnimData* aptr;
				aptr = (PolyPitAnimData* )adptr;
				aptr->detailmask = 0;										//RJS 26Jan98

				aptr->detailmask |= (1 << COCK3D_DIALSROW1ON);				//RJS 26Jan98
				aptr->detailmask |= (1 << COCK3D_DIALSROW2ON);				//RJS 26Jan98
				aptr->detailmask |= (1 << COCK3D_DIALSROW3ON);				//RJS 26Jan98
				aptr->detailmask |= (1 << COCK3D_DIALSROW4ON);				//RJS 26Jan98
				aptr->detailmask |= (1 << COCK3D_PANELIMAPDSPLIT);				//RJS 26Jan98
				aptr->detailmask |= (1 << COCK3D_PANELGLASSFRONT);			//RJS 25Mar98

//				aptr->compasscount = 0;								//RJS 24Sep96
	//DeadCode JIM 06Sep96 			aptr->itemstate=ALIVE;
				}
				adptr += sizeof(PolyPitAnimData);
				break;

			case AIRCRAFTANIM:
				{
				AircraftAnimData* aptr;
				aptr = (AircraftAnimData* )adptr;
				aptr->nolaunchers = 0;								//RJS 23Aug96
				storesweight = InitLauncherAnim(adptr,shpno,AnimWeaponPack);//RJS 11May98

				if (globinititem->Status.size != AIRSTRUCSIZE)			//RJS 21Apr99
				{
					//Put gear down...
					aptr->acleglowerl = 0;
					aptr->acleglowerf = 0;
					aptr->acleglowerr = 0;
				}

				adptr += sizeof(AircraftAnimData);					//RJS 11May98

				}
				break;

			case SUNANIM:											//PD 24Jun96
				{													//PD 24Jun96
				SunAnimData *aptr;									//PD 24Jun96
				aptr = (SunAnimData* )adptr;						//PD 24Jun96
				aptr->wasdrawn=FALSE;								//PD 24Jun96
				}													//PD 24Jun96

				adptr += sizeof(SunAnimData);						//PD 24Jun96
				break;												//PD 24Jun96

			case BARAGEANIM:										//RJS 24Sep96
				{
				BarageAnimData* aptr;
				aptr = (BarageAnimData* )adptr;
				aptr->countdown=0;
				}

				adptr += sizeof(BarageAnimData);
				break;

			case TROOPANIM:											//RJS 07Nov96
			{
				TroopAnimData* aptr;								
				aptr = (TroopAnimData* )adptr;

				aptr->swapnow = 1;
				aptr->BITSOFFFLAGS = 0xFFFF;					//RJS 23Dec99
				aptr->BITSOFFFLAGS &= ~(1<<BF_ONFIRE);			//RJS 23Dec99
				aptr->BITSOFFFLAGS &= ~(1<<BF_HELMET);			//RJS 23Dec99
				aptr->BITSOFFFLAGS &= ~(1<<BF_PARACHUTE);		//RJS 23Dec99
				aptr->BITSOFFFLAGS &= ~(1<<BF_GUN);				//RJS 23Dec99

				if (globinititem->Status.size >= MOBILESIZE)
				{
					if (Math_Lib.rnd() > 32700)
					{
						if (MobileItemPtr(globinititem)->nationality == NAT_RAF)
							aptr->stripno = CLOTHING_RAFPILOT;
						else
							aptr->stripno = CLOTHING_LWPILOT;
					}
					else
						aptr->stripno = CLOTHING_GROUND;
				}
				else
					aptr->stripno = CLOTHING_GROUND;
			}

			adptr += sizeof(TroopAnimData);					
			break;

			case CLONEANIM:										//RJS 21Jan98
				adptr += sizeof(CloneAnimData);					//RJS 21Jan98
				break;
			case FLAREANIM:										//RJS 21Jan98
				adptr += sizeof(FlareAnimData);					//RJS 21Jan98
				break;											//RJS 21Jan98
			case THUGANIM:										//RJS 03Mar98
				adptr += sizeof(ThugAnimData);					//RJS 03Mar98
				break;											//RJS 03Mar98
			case MISSILEANIM:									//RJS 03Mar98
			{
				MissileAnimData*	aptr = (MissileAnimData*) adptr;

				aptr->hitstrength = 0;
				aptr->novirtualguns = 0;
				aptr->lastmissile = 0;

				adptr += sizeof(MissileAnimData);				//RJS 03Mar98
				break;
			}
			case SMOKETRAILANIM:
			{
				MoveGunAnimData*	mptr=(MoveGunAnimData*) adptr;	  	
				mptr->nolaunchers = 0;
				InitLauncherAnim(adptr,shpno);
				if (mptr->nolaunchers >1) ///!=1)
					_Error.EmitSysErr("Agh %i",shpno);

				adptr+=sizeof(SmokeTrailAnimData);
		 		break;
			}
			case PARACHUTEANIM:									//RJS 25Mar99
				adptr += sizeof(ParachuteAnimData);				//RJS 25Mar99
				break;											//RJS 25Mar99

			case BLOKESANIM:
			{
//DeadCode RJS 20Oct00 				BlokesAnimData*	aptr = (BlokesAnimData*)adptr;
				adptr += sizeof(BlokesAnimData);
				break;
			}
			case BIRDLAUNCHERANIM:								//RJS 01Dec99
			{
				BirdLauncherAnimData*	aptr = (BirdLauncherAnimData*)adptr;
				// 1 in 5 chance of birds being here...
				aptr->isPregnant = 1;//Math_Lib.rnd(5) >> 2;
				aptr->theShape = sdptr->Type.shapenumber;
				aptr->countdown = 0;
				adptr+=sizeof(BirdLauncherAnimData);			//RJS 01Dec99
				break;
			}
			case SIMPLEAIRCRAFTANIM:
			{
				SimpleAircraftAnimData* aptr;
				aptr = (SimpleAircraftAnimData* )adptr;
				aptr->nolaunchers = 0;
				
				if (groupindex == 0)
				{
					FakeLauncherAnim(adptr,shpno,AnimWeaponPack);
//DeadCode CSB 9Aug00 					aptr->IsInvisible = 0;
					aptr->IsInvisible = 1;								//CSB 9Aug00
				}
				else
					InitLauncherAnim(adptr,shpno,AnimWeaponPack);

				adptr += sizeof(SimpleAircraftAnimData);
				break;											//RJS 15Dec99
			}													//RJS 15Dec99
			case BALLOONANIM:									//RJS 15Dec99
				//turn elements off randomly							//JIM 29Jun00
				static UWord	ballcount=0;							//JIM 29Jun00
				if (ballcount==0)										//JIM 29Jun00
					ballcount=Math_Lib.rnd();							//JIM 29Jun00
				if (!(ballcount&3))										//JIM 29Jun00
					mad->IsInvisible=1;									//JIM 29Jun00
				ballcount>>=2;											//JIM 29Jun00

				adptr += sizeof(BalloonAnimData);
				break;
		}

		if (globinitairitem)
		{
			InitUndercarriageAnim(globinitairitem);				//RJS 28May98
//			Trans_Obj.WeaponSearch(globinitairitem);			//RJS 09Sep98
		}
	}
	else
	{
		animdatasize = -animdatasize;							//RJS 27Apr98

		adptr += animdatasize;
	}

	return (storesweight);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindWeapRecord
//Author		Robert Slater
//Date			Thu 17 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void*	shape::FindWeapRecord(ShapeNum	shpno,SLong	&index)
{
	ShpToWeapTypeP	wprec = NULL;
	SLong			i = 0;
	
	index = 0;
	while (ShpToWeap[i].LchShape)
	{
		if (ShpToWeap[i].LchShape == shpno)
		{
			wprec = &ShpToWeap[i];
			index = i;
			break;
		}

		i++;
	}

	return ((void*)wprec);
}

SWord	shape::WeapInfo(int	weapindex, const LnchrType	lchtype)
{
	UWord	muzandweapIndex;

// 8bits weapindex ... 8bits muzzleindex;

	if (weapindex > -1)
		muzandweapIndex = (weapindex << 8);
	else
		muzandweapIndex = 0;

	muzandweapIndex = muzandweapIndex | GetMuzzleIndex(lchtype);

	return SWord(muzandweapIndex);
}

bool	shape::FindWeaponRec(void*	WeapPtr,const LnchrType	lchtype, int& i)
{
	bool			foundweap = false;
	ShpToWeapTypeP	WeapRec = ShpToWeapTypeP(WeapPtr);

	i=-1;
	if (WeapRec)
	{
		i=0;
		while ((i < MaxWeapTypes) && (WeapRec->LchList[i].lnchr != LT_CONTACT))
		{
			if (WeapRec->LchList[i].lnchr == lchtype)
			{
				foundweap = true;
				break;
			}
			else
				i++;
		}
	}	

	return foundweap;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddWeapToAnim
//Author		Robert Slater
//Date			Thu 17 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void  shape::AddWeapToAnim(	void*				WeapPtr,
	  						MoveGunAnimData* 	adptr,
	  						LnchrType			lchtype,
							int					stores,
	  						int					&index,
							int					&addweight,
							int					&adddrag,
							int					realIndex,
							int					noChildren,
							bool				isTwinned)		//RJS 15Nov99
{
	int 			i,j,k;
	bool			foundweap;											//RJS 23May00
	ShpToWeapTypeP	WeapRec = (ShpToWeapTypeP) WeapPtr;			//RJS 27Aug98
	SLong			noWeapons = 1;								//RJS 15Nov99
	SWord			defaultHdg = 0;									//RJS 24Oct00
	SWord			defaultPitch = 0;										//RJS 24Oct00

	if (globinitairitem)
	{
		if (UByte(lchtype) < UByte(globinitairitem->weap.weapontype))
			globinitairitem->weap.weapontype = lchtype;
	}
	
	foundweap = FindWeaponRec(WeapPtr,lchtype,i);						//RJS 23May00

	//Return weight and drag for this station...
	addweight = 0;															//RJS 25Aug98
	adddrag = 0;

	adptr->weaponlaunchers[index].launcherIndex = realIndex;	//RJS 12Nov99
	if (isTwinned)												//RJS 15Nov99
	{
		if ((index + 1) < MAX_WEAP_LAUNCHERS)
		{
			adptr->weaponlaunchers[index+1].launcherIndex = realIndex + noChildren;//RJS 15Nov99
			noWeapons = 2;
		}
		else
			_Error.EmitSysErr(__FILE__": Too many launchers!\n");
	}

	UWord	muzandweapIndex;									//RJS 27May99
	if (foundweap)
	{
//DeadCode RJS 27May99 		UWord	muzandweapIndex;										//RJS 25Aug98

		addweight = WeapRec->LchList[i].Weight;
		adddrag = WeapRec->LchList[i].Drag;
		if (lchtype == LT_FUEL)									//RJS 18Jan99
		{														//RJS 18Jan99
			// 500 kilos max...									//RJS 18Jan99
			stores *= 32767;									//RJS 18Jan99
			stores /= 50000000;									//RJS 18Jan99
		}														//RJS 18Jan99

		// 8bits weapindex ... 8bits muzzleindex;
		muzandweapIndex = WeapInfo(i,lchtype);							//RJS 23May00

		GetDefaultHdgPitch(lchtype,defaultHdg,defaultPitch);			//RJS 24Oct00

		for (k=0; k < noWeapons; k++)  						// Keep symmetrical
		{
			adptr->weaponlaunchers[index+k].LauncherType = lchtype;
			adptr->weaponlaunchers[index+k].stationshape = (UWord) WeapRec->LchList[i].StationShape[k];
			adptr->weaponlaunchers[index+k].target = UID_Null;
			adptr->weaponlaunchers[index+k].LaunchTime = muzandweapIndex;//RDH 03Aug98
  			adptr->weaponlaunchers[index+k].Stores = stores;		//RJS 11May98
			adptr->weaponlaunchers[index+k].SubDamage = 0;
			adptr->weaponlaunchers[index+k].hdg = defaultHdg;			//RJS 24Oct00
			adptr->weaponlaunchers[index+k].pitch = defaultPitch;		//RJS 24Oct00
			adptr->weaponlaunchers[index+k].LoadedStores = stores;	//RJS 11May98
		}

		index += noWeapons;										//RJS 15Nov99
		adptr->nolaunchers += noWeapons;						//RJS 15Nov99
	}
	else
	{
		GetDefaultHdgPitch(lchtype,defaultHdg,defaultPitch);			//RJS 24Oct00

		if (lchtype == LT_FUEL)									//RJS 18Jan99
			stores = 32767;										//RJS 18Jan99

		SLong	masked = lchtype & LT_MASK;
		if ((masked == LT_SMKTRAILS) || (masked == LT_MOVEGUN))//RJS 22Oct98
		{
			// Must be an effect launcher, like LT_CONTRAIL, or LT_VAPOUR...
			if (noWeapons != 1)										//RJS 15Nov99
				INT3;												//RJS 15Nov99

			adptr->weaponlaunchers[index].LauncherType = lchtype;
			adptr->weaponlaunchers[index].stationshape = 0;
			adptr->weaponlaunchers[index].target = UID_Null;
			adptr->weaponlaunchers[index].LaunchTime = 0;
  			adptr->weaponlaunchers[index].Stores = stores;			//RJS 11/04/00
			adptr->weaponlaunchers[index].SubDamage = 0;
			adptr->weaponlaunchers[index].hdg = defaultHdg;			//RJS 24Oct00
			adptr->weaponlaunchers[index].pitch = defaultPitch;			//RJS 24Oct00
			adptr->weaponlaunchers[index].LoadedStores = stores;	//RJS 28/04/00
			if (masked==LT_MOVEGUN)								//RJS 09Dec99
				adptr->nolaunchers += noWeapons;					//RJS 15Nov99
			else
				adptr->nolaunchers = index+1;

			index += noWeapons;										//RJS 15Nov99
		}
		else
		{
			//Must be a dummy station; keep symmetrical
			for (k=0; k < noWeapons; k++)  							//RJS 15Nov99
			{
				adptr->weaponlaunchers[index+k].LauncherType = lchtype;
				adptr->weaponlaunchers[index+k].stationshape = 0;
				adptr->weaponlaunchers[index+k].target = UID_Null;
				adptr->weaponlaunchers[index+k].LaunchTime = GetMuzzleIndex(lchtype);//RJS 27May99
  				adptr->weaponlaunchers[index+k].Stores = stores;					//RJS 23Apr99
				adptr->weaponlaunchers[index+k].SubDamage = 0;
				adptr->weaponlaunchers[index+k].hdg = 0;
				adptr->weaponlaunchers[index+k].pitch = 0;
				adptr->weaponlaunchers[index+k].LoadedStores = stores;				//RJS 23Apr99
			}

			index += noWeapons;										//RJS 15Nov99
			adptr->nolaunchers += noWeapons;						//RJS 15Nov99
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetWeaponPack
//Author		Robert Slater
//Date			Wed 8 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByteP	shape::GetWeaponPack(ShapeNum	shape, int packno)
{
	UByteP	retval = NULL;
	int		i;

	i = 0;
	if ((packno >= 0) && (packno < MaxPackNo))
	{
		while (ShpToWeapPak[i].shape)
		{
			if (ShpToWeapPak[i].shape == shape)
			{
				retval = (UByteP) ShpToWeapPak[i].weappack[packno].stationlaunchers;
				break;
			}

			i++;
		}

		// Default to F86 launchers.....
//		if (!retval)
//	 		retval = (UByteP) ShpToWeapPak[0].weappack[packno].stationlaunchers;
	}

	return(retval);
}

void	shape::AddFuelLauncher(UByteP instr_ptr, int launcher, int index)
{
//Old_Code RJS 26Nov99 	if (globinitairitem && (launcher==LT_INTFUEL))
//Old_Code RJS 26Nov99 	{
//Old_Code RJS 26Nov99 		DOLAUNCHER_PTR	lptr = (DOLAUNCHER_PTR) instr_ptr;
//Old_Code RJS 26Nov99 		SLong			dx = lptr->posx;
//Old_Code RJS 26Nov99 		weap_info		*WIPtrL;
//Old_Code RJS 26Nov99 		weap_info		*WIPtrR;
//Old_Code RJS 26Nov99 		weap_info		*WIPtrC;
//Old_Code RJS 26Nov99 
//Old_Code RJS 26Nov99 		WIPtrL = &globinitairitem->weap.left;
//Old_Code RJS 26Nov99 		WIPtrR = &globinitairitem->weap.right;
//Old_Code RJS 26Nov99 		WIPtrC = &globinitairitem->weap.centre;
//Old_Code RJS 26Nov99 
//Old_Code RJS 26Nov99 		if ((dx < -40) || (dx > 40))
//Old_Code RJS 26Nov99 		{
//Old_Code RJS 26Nov99 			if (dx < 0)
//Old_Code RJS 26Nov99 				WIPtrL->int_launcher = index;
//Old_Code RJS 26Nov99 			else
//Old_Code RJS 26Nov99 				WIPtrR->int_launcher = index;
//Old_Code RJS 26Nov99 		}
//Old_Code RJS 26Nov99 		else
//Old_Code RJS 26Nov99 			WIPtrC->int_launcher = index;
//Old_Code RJS 26Nov99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddMassAndDrag
//Author		Robert Slater
//Date			Wed 13 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::AddMassAndDrag(UByteP	instr_ptr, int	launcher, int count, int mass, int drag, SLong wpIndex, SWord launcherindex)
{
	if (globinitairitem)
	{
		DOLAUNCHER_PTR lptr = (DOLAUNCHER_PTR) instr_ptr;
		SLong			dx = lptr->posx;
		weap_info		*WIPtrL;
		weap_info		*WIPtrR;
		weap_info		*WIPtrC;
		SLong			totmass,totdrag;

		globinitairitem->weap.shpweapindex = (UWord) wpIndex;

		WIPtrL = &globinitairitem->weap.left;
		WIPtrR = &globinitairitem->weap.right;
		WIPtrC = &globinitairitem->weap.centre;

		if ((dx < -40) || (dx > 40))
		{
			weap_info		*WIPtr;								//RJS 21May99
			if (dx < 0)											//RJS 21May99
				WIPtr = WIPtrL;									//RJS 21May99
			else												//RJS 21May99
				WIPtr = WIPtrR;									//RJS 21May99

			if (launcher == LT_FUEL)
			{
//DeadCode RJS 26Nov99				WIPtr->ext_fuel = count;						//RJS 21May99
				globinitairitem->weap.UseIntFuel = FALSE;		//RJS 25Jan99
				globinitairitem->weap.FuelDumped = FALSE;		//RJS 25Jan99
				globinitairitem->weap.StoresDumped = FALSE;		//RDH 04/03/99
				totmass = mass;									//RJS 25Jan99
				totdrag = drag;									//RJS 25Jan99

//DeadCode RJS 26Nov99				WIPtr->ext_launcher = launcherindex;			//RJS 21May99
			}
			else
			{													//RJS 25Jan99
				totmass = mass * count;							//RJS 25Jan99
				totdrag = drag * count;							//RJS 25Jan99
																//RJS 25Jan99
				WIPtr->reloadmass += totmass;					//RJS 21May99
 				WIPtr->reloaddrag += totdrag;					//RJS 21May99
			}													//RJS 25Jan99

			WIPtr->mass += totmass;								//RJS 21May99
			WIPtr->drag += totdrag;								//RJS 21May99
		}
		else
		{
			if (launcher == LT_FUEL)
			{
//DeadCode RJS 26Nov99				WIPtrC->ext_fuel = count;
				globinitairitem->weap.UseIntFuel = FALSE;		//RJS 25Jan99
				globinitairitem->weap.FuelDumped = FALSE;		//RJS 25Jan99
																//RJS 25Jan99
				totmass = mass;									//RJS 25Jan99
				totdrag = drag;									//RJS 25Jan99

//DeadCode RJS 26Nov99				WIPtrC->ext_launcher = launcherindex;
			}
			else
			{
				totmass = mass * count;							//RJS 25Jan99
				totdrag = drag * count;							//RJS 25Jan99
																//RJS 25Jan99
				WIPtrC->reloadmass += totmass;					//RJS 25Jan99
				WIPtrC->reloaddrag += totdrag;					//RJS 25Jan99
			}

			WIPtrC->mass += totmass;
			WIPtrC->drag += totdrag;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitLauncherAnim
//Author		Robert Slater
//Date			Wed 21 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord shape::InitLauncherAnim(animptr& adptr,ShapeNum shpno,int  packno)
{
	ShapeDescPtr	sdptr;
	UByte 			*instr_ptr;
	LnchrType		lchtype,addExtStore;						//RJS 13May98
	UWord		 	instruction, last_inst;
	Bool			go=TRUE;
	int				count=0;
	int				count2 = 0;
	SWord			storesweight = 0;
	void*			weaprec;
	LchrInfoP		lchlist;									//RJS 11May98
	int				fiddlecnt = 0;								//RJS 12May97
	int				addWeight, addDrag, addExtCount;			//RJS 13May98
	SLong			masked;
	SLong			wpIndex;
	Bool			setMassDrag = FALSE;						//RJS 13May99


//THIS NOBBLE FORCES A SPECIFIC WEAP PACK FOR ALL AIRCRAFT
	assert((packno==0)||(packno==1));									//RJS 25Aug00

	lchlist = (LchrInfoP) GetWeaponPack(shpno,packno);			//RJS 11May98
	sdptr = SHAPESTUFF.GetShapePtr(shpno);						//RJS 11May98
	weaprec = FindWeapRecord(shpno,wpIndex);					//RDH 03Aug98

	if (sdptr->LauncherDataSize)
	{
		MoveGunAnimData* aptr = (MoveGunAnimData*) adptr;
		SLong			realIndex = 0;
		SLong			nextIndex = 0;
		SLong			maxWeapLaunchers = 0;
		SLong			realMaxLaunchers = 1;
		WeapAnimData*	weapon = (WeapAnimData*) aptr->weaponlaunchers;
		
		switch (sdptr->AnimDataSize)
		{																//RJS 11Jul00
		case AIRCRAFTANIM:
			realMaxLaunchers = MAX_WEAP_LAUNCHERS;
			maxWeapLaunchers = MAX_WEAP_LAUNCHERS-1;
		break;
		case TWOGUNANIM:
			realMaxLaunchers = 2;
		break;
		}

		aptr->nolaunchers = 0;									//RJS 15Nov99

		instr_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

		while (go)
		{
			instruction = (UWord )*instr_ptr;

			instr_ptr ++;
//DeadCode RJS 19Dec97 			instruction>>=1;

			if(instruction>dosetglassrangeno || instruction==0)
				_Error.EmitSysErr(__FILE__":Bad instruction in launcher shape (%d)",instruction);

			if(instruction==doretno || instruction==doendno)
				go=FALSE;
			else
			{
				switch (instruction)
				{
					case dolauncherno:
					{
						DOLAUNCHER_PTR aptrsrc;
						aptrsrc = (DOLAUNCHER_PTR) instr_ptr;

						realIndex = nextIndex;

						if (aptrsrc->noChildren)
						{
							nextIndex = realIndex + aptrsrc->noChildren + 1;
							instr_ptr += ((sizeof(DOLAUNCHER)+1) * aptrsrc->noChildren);
						}
						else
							nextIndex = realIndex + 1;

						lchtype = (LnchrType) aptrsrc->lnchrtype;//RJS 17Apr97
						masked = lchtype & LT_MASK;					//RJS 11May00
						if (count < realMaxLaunchers)					//RJS 11Jul00
						{
							if (!weapon->Stores)						//RJS 10Jul00
								weapon->LauncherType = LT_CONTACT;		//RJS 10Jul00

							if (lchtype < LT_CONTACT)
							{
								if (count == count2)				//RJS 17Apr97
								{
									setMassDrag = FALSE;
//DEADCODE RJS 5/11/00 									masked = lchtype & LT_MASK;
									switch (masked)
									{
									case LT_SMKTRAILS:
									{
										int	useindex = maxWeapLaunchers;//RJS 09Dec99
										
//TempCode RJS 10Jul00 										if (!aptr->weaponlaunchers[useindex].Stores)
//TempCode RJS 10Jul00 										{
											AddWeapToAnim(	weaprec,
															aptr,
															lchtype,
															900,
															useindex,	//RJS 09Dec99
															addWeight,
															addDrag,
															realIndex,
															aptrsrc->noChildren+1,
															aptrsrc->isTwinned);//RJS 15Nov99

//TempCode RJS 10Jul00 											if (maxWeapLaunchers > 0)
//TempCode RJS 10Jul00 												maxWeapLaunchers--;
//TempCode RJS 10Jul00 
//TempCode RJS 10Jul00 											useindex = maxWeapLaunchers;
//TempCode RJS 10Jul00 										}

										count2 = useindex;

										AddFuelLauncher(instr_ptr,lchtype,count);
									}
									break;
									case LT_WEAPON:
									{
										if (lchlist)			//RJS 17May99
										{
											addExtStore = lchlist[fiddlecnt].lnchrtype;
											addExtCount = lchlist[fiddlecnt++].ammocount;
											AddWeapToAnim(	weaprec,
															aptr,
															addExtStore,
															addExtCount,
															count2,
															addWeight,
															addDrag,
															realIndex,
															aptrsrc->noChildren+1,
															aptrsrc->isTwinned);//RJS 15Nov99

											setMassDrag = TRUE;
											AddMassAndDrag(instr_ptr,addExtStore,addExtCount,addWeight,addDrag,wpIndex,count);//RJS 25Mar99
										}
									}
									break;
									case LT_MOVEGUN:
									{
										AddWeapToAnim(	weaprec,
														aptr,
														lchtype,
														900,			//default stores
														count2,
														addWeight,
														addDrag,
														realIndex,
														aptrsrc->noChildren+1,
														aptrsrc->isTwinned);//RJS 15Nov99
									}
									break;
									}
								}
								else
								{
									//Needs to be twinned...
									if (setMassDrag)
										AddMassAndDrag(instr_ptr,addExtStore,addExtCount,addWeight,addDrag,wpIndex,count);//RJS 13May99
								}
							}
							else
								count2++;

							weapon++;
							count++;
						}
						else
						{
							// is it a weapon?
							if (masked < LT_SMKTRAILS)				//RJS 11May00
								_Error.EmitSysErr(__FILE__":Weapon launcher index out of range; shape %d",shpno);
						}

						instr_ptr += sizeof(DOLAUNCHER);
					}
					break;
					default:
						_Error.EmitSysErr(__FILE__":Bad launcher instruction (%d)",instruction);
				}
			}

			last_inst = instruction;
		}

//DeadCode RJS 15Nov99		aptr->nolaunchers = GetNumberOfLaunchers(shpno);
	}

	return (storesweight);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLightData
//Author		Robert Slater
//Date			Thu 18 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByteP	shape::GetLightDataPtr(ShapeNum	shpno, int	index)
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shpno);
	ULong			lsize = (index * (sizeof(LIGHTDATA) + 1)) + sdptr->LightDataOffset;//RJS 19Dec97
	UByteP			retval = NULL;

	if (sdptr->LightDataOffset)
		retval = (UByteP) ((ULong)sdptr + lsize + 1);			//RJS 19Dec97

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLauncherPos
//Author		Robert Slater
//Date			Fri 23 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByteP shape::GetLauncherPos(ShapeNum	shpno, UByte	offset)
{
	ShapeDescPtr	sdptr;
	UByte 			*instr_ptr;
	UWord		 	instruction, last_inst;
//DeadCode RJS 20Oct00 	Bool			go=TRUE;
	DOLAUNCHER_PTR	launchfound = NULL;
	UByte			instsize = sizeof(DOLAUNCHER) + 1;

	sdptr = SHAPESTUFF.GetShapePtr(shpno);

	if (SHAPESTUFF.GetShapeScale(sdptr) != SHP_GRP)				//JIM 29Sep96
	{															//JIM 29Sep96
		if (sdptr->LauncherDataSize)
		{
			instr_ptr = (UByteP )sdptr + sdptr->LauncherDataSize + (instsize * offset);

			instruction = (UWord) *instr_ptr;
			instr_ptr++;

//DeadCode RJS 19Dec97 			instruction >>= 1;

			if (instruction == dolauncherno)
				return(instr_ptr);
			else
			{
				if (	(instruction == doretno)
					 || (instruction == doendno)	)
					return(NULL);
				else
					_Error.EmitSysErr(__FILE__":Bad launcher instruction (%d)",instruction);
			}

//DeadCode RJS 21May97 			while (go)
//DeadCode RJS 21May97 			{
//DeadCode RJS 21May97 				instruction = (UWord )*instr_ptr;
//DeadCode RJS 21May97 
//DeadCode RJS 21May97 				instr_ptr ++;
//DeadCode RJS 21May97 				instruction>>=1;
//DeadCode RJS 21May97 
//DeadCode RJS 21May97 				if(instruction>dosetglassrangeno || instruction==0)
//DeadCode RJS 21May97 					_Error.EmitSysErr(__FILE__":Bad instruction in launcher GetLauncherPos (%d)",instruction);
//DeadCode RJS 21May97 
//DeadCode RJS 21May97 				if(instruction==doretno || instruction==doendno)//JIM 29Sep96
//DeadCode RJS 21May97 					go=FALSE;
//DeadCode RJS 21May97 				else
//DeadCode RJS 21May97 				{
//DeadCode RJS 21May97 					switch (instruction)
//DeadCode RJS 21May97 					{
//DeadCode RJS 21May97 						case dolauncherno:
//DeadCode RJS 21May97 							{
//DeadCode RJS 21May97 								if (offset > 0)
//DeadCode RJS 21May97 									offset--;
//DeadCode RJS 21May97 								else
//DeadCode RJS 21May97 								{
//DeadCode RJS 21May97 									RETURN(instr_ptr);			//JIM 29Sep96
//DeadCode RJS 21May97 								}
//DeadCode RJS 21May97 
//DeadCode RJS 21May97 								instr_ptr += sizeof(DOLAUNCHER);
//DeadCode RJS 21May97 							}
//DeadCode RJS 21May97 						break;
//DeadCode RJS 21May97 						default:
//DeadCode RJS 21May97 							_Error.EmitSysErr(__FILE__":Bad launcher instruction (%d)",instruction);
//DeadCode RJS 21May97 					}
//DeadCode RJS 21May97 				}
//DeadCode RJS 21May97 
//DeadCode RJS 21May97 			}
		}
	}
	else														//JIM 29Sep96
	{
		if (sdptr->AnimDataSize==0)
			SHAPE.GetAnimDataSize(shpno);	
 		if (sdptr->LauncherDataSize)
		{
			UByteP	instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
			Coords3D	g;
			ShapeNum	newshp;
			while	(GetGroupElement(instr_ptr,newshp,g.X,g.Y,g.Z))
			{
				sdptr = SHAPESTUFF.GetShapePtr(newshp);
				if (sdptr->LauncherDataSize)
				{
					if (offset--==0)
						RETURN((UByteP)sdptr + sdptr->LauncherDataSize +1);
				}
			}
		}
	}

	return((UByteP) launchfound);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetContactPoint
//Author		Paul.   
//Date			Wed 11 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GetContactPoint(	itemptr itm,LnchrType ct,
	  							COORDS3D&	position,
	  							COORDS3D&	offset,
								COORDS3D&	dummyoffset)
{
	DOLAUNCHER_PTR	thislaunch = NULL;
	DOLAUNCHER_PTR	dummylaunch = NULL;
	ClassPtr		clstyp;
	ShapeDescPtr	sdptr;
	ShapeNum		shpno;
//DeadCode RJS 20Oct00 	Bool			polypit = FALSE;
	UByte count 	= 0;
//DeadCode RJS 20Oct00 	SByte target 	= (SByte )ct;
	UByte			thisscale = 0;
	MyGroundVectorPtr		goffset = NULL;								//RJS 21Nov96
	SLong			xpos, ypos, zpos;							//RJS 12Aug97
//DeadCode RJS 20Oct00 	Bool			inCock = FALSE;

//DeadCode RJS 21Apr99  	if ((itm == Manual_Pilot.ControlledAC2) && View_Point)
//DeadCode RJS 21Apr99  	{
//DeadCode RJS 21Apr99  		if (View_Point)
//DeadCode RJS 21Apr99 		{
//DeadCode RJS 21Apr99 			if (View_Point->PolyPitEnabled())
//DeadCode RJS 21Apr99  			{
//DeadCode RJS 21Apr99 	 			clstyp = Manual_Pilot.ControlledAC2->classtype;
//DeadCode RJS 21Apr99  				if (View_Point->viewnum.viewmode == VM_Inside)
//DeadCode RJS 21Apr99  					shpno = clstyp->cockpit1;
//DeadCode RJS 21Apr99  				else
//DeadCode RJS 21Apr99  					shpno = clstyp->cockpit2;
//DeadCode RJS 21Apr99 
//DeadCode RJS 21Apr99 				inCock = TRUE;
//DeadCode RJS 21Apr99 			}
//DeadCode RJS 21Apr99 			else
//DeadCode RJS 21Apr99 			{
//DeadCode RJS 21Apr99 				if (View_Point->viewnum.viewmode == VM_InsideCheat)
//DeadCode RJS 21Apr99 				{
//DeadCode RJS 21Apr99 					clstyp = Manual_Pilot.ControlledAC2->classtype;
//DeadCode RJS 21Apr99 					shpno = clstyp->cockpit1;
//DeadCode RJS 21Apr99 					inCock = TRUE;
//DeadCode RJS 21Apr99 				}
//DeadCode RJS 21Apr99 				else
//DeadCode RJS 21Apr99 					shpno = itm->shape;
//DeadCode RJS 21Apr99 			}
//DeadCode RJS 21Apr99  		}
//DeadCode RJS 21Apr99  		else
//DeadCode RJS 21Apr99  			shpno = itm->shape;
//DeadCode RJS 21Apr99  	}
//DeadCode RJS 21Apr99  	else
	shpno = itm->shape;											//RJS 21Apr99

 	sdptr = SHAPESTUFF.GetShapePtr(shpno);
 
 	switch (SHAPESTUFF.GetShapeScale(sdptr))
 	{
 		case SHP_1CM:
 			thisscale = 0;
 			break;
 
 		case SHP_4CM:
 			thisscale = 2;
 			break;
 
 		case SHP_16CM:
 			thisscale = 4;
 			break;
 	}

	offset.X = 0;
	offset.Y = 0;
	offset.Z = 0;

	do
	{
		thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shpno,count++);

		if (thislaunch)
		{
//DeadCode RJS 17Mar97 			if (thislaunch->lnchrtype==LT_CONTACT)
//DeadCode RJS 17Mar97 			{
//DeadCode RJS 17Mar97 				target--;
//DeadCode RJS 17Mar97 				if (target<0)
//DeadCode RJS 17Mar97 					break;
//DeadCode RJS 17Mar97 			}

			if (thislaunch->lnchrtype == ct)
			{
 				xpos = thislaunch->posx << thisscale;			//RJS 10Feb99
 				ypos = thislaunch->posy << thisscale;			//RJS 10Feb99
 				zpos = thislaunch->posz << thisscale;			//RJS 10Feb99
//DeadCode RJS 10Feb99 				xpos = thislaunch->posx;						//RJS 27Aug97
//DeadCode RJS 10Feb99 				ypos = thislaunch->posy;						//RJS 27Aug97
//DeadCode RJS 10Feb99 				zpos = thislaunch->posz;						//RJS 27Aug97


				// Set dummy suspension pushed-in default to fully suspended...
				offset.X = dummyoffset.X = xpos;				//RJS 12Aug97
				offset.Y = dummyoffset.Y = ypos;				//RJS 12Aug97
				offset.Z = dummyoffset.Z = zpos;				//RJS 12Aug97

				dummylaunch = (DOLAUNCHER_PTR) GetLauncherPos(shpno,count);//RJS 13Jun97
				if (dummylaunch)
				{
					if (dummylaunch->lnchrtype == CT_DUMMY)
					{
 						dummyoffset.X = dummylaunch->posx << thisscale;//RJS 10Feb99
 						dummyoffset.Y = dummylaunch->posy << thisscale;//RJS 10Feb99
 						dummyoffset.Z = dummylaunch->posz << thisscale;//RJS 10Feb99
//DeadCode RJS 10Feb99 						dummyoffset.X = dummylaunch->posx;		//RJS 27Aug97
//DeadCode RJS 10Feb99 						dummyoffset.Y = dummylaunch->posy;		//RJS 27Aug97
//DeadCode RJS 10Feb99 						dummyoffset.Z = dummylaunch->posz;		//RJS 27Aug97
					}
				}
				break;
			}
		}
	}
	while (thislaunch);

//Dead	LauncherToWorld(itm,(UByteP )thislaunch,thisscale,position.X,position.Y,position.Z,goffset,NULL,inCock);
	LauncherToWorld(itm,(UByteP )thislaunch,thisscale,position.X,position.Y,position.Z,goffset);

	if (goffset)	delete (goffset);

//DeadCode RJS 12Aug97 	return((UByteP) dummylaunch);								//RJS 13Jun97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetVapourPoint
//Author		Robert Slater
//Date			Fri 20 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong shape::GetVapourPoint(itemptr itm,int index,int ltype,SLong &xpos,SLong &ypos,SLong &zpos)
{
	DOLAUNCHER_PTR	thislaunch = NULL;
	ShapeDescPtr	sdptr;
	ShapeNum		shpno;
	int				count 	= 0;
	SByte			thisscale = 0;
//DeadCode RJS 20Oct00 	MinAnimData		*mad = (MinAnimData*) itm->Anim;
	int				vapindex = 0;

//	if (index < mad->nolaunchers)
//	{
		count = index;

		shpno = itm->shape;
		sdptr = SHAPESTUFF.GetShapePtr(shpno);

		switch (SHAPESTUFF.GetShapeScale(sdptr))
		{
			case SHP_GRP:
				thisscale = -1;
				break;
			case SHP_1CM:
				thisscale = 0;
				break;

			case SHP_4CM:
				thisscale = 2;
				break;

			case SHP_16CM:
				thisscale = 4;
				break;
		}

		if (thisscale > -1)
		{
			do
			{
				thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shpno,count++);
				if (thislaunch && (thislaunch->lnchrtype==ltype))
				{
					LauncherToWorld(itm,(UByteP) thislaunch,thisscale,xpos,ypos,zpos,NULL);

					vapindex = count;
					break;
				}
			}
			while (thislaunch);
		}
//	}

	return (vapindex);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetWeaponLauncher
//Author		Robert Slater
//Date			Thu 22 Aug 1996
//
//Description	Gets a pointer to indexed weapon launcher
//
//Inputs		The item, index, x,y,z dummies, and launcher type
//
//Returns		Pointer to weapon launcher data
//
//------------------------------------------------------------------------------
WeapAnimData* shape::GetWeaponLauncher(itemptr	itm, UByte	index,
									   SLong&	xpos, SLong&	ypos,
									   SLong&	zpos,
									   ULong&	MuzzleVel,
									   UWord&	MuzzleDelay,
									   UWord&	MuzzleBurst,
									   SByte 	ltype,
									   UWord	*bulletShape
									   )
{
	WeapAnimData*		weapon=NULL;
	if (itm)															//RJS 18Sep00
	{
		ShapeDescPtr		sdptr;
		DOLAUNCHER_PTR		thislaunch = NULL;
		animptr				animdataptr;
		UByteP				instr_ptr;
		ShapeNum			shape;
		ShapeDescPtr		tmpsdptr;
		MoveGunAnimData*	aptr;
		UByte				thisscale = 0;
		SLong				gx, gy, gz;
		MyGroundVectorPtr			goffset = NULL;
		int					cnt;
		Coords3D			eyeDelta;
		ULong				muzindex = 0;
		UWord				noLaunchers = 0;						//RJS 09Dec98
//DeadCode RJS 13Mar00 	Bool				incock = FALSE;							//RDH 08Dec98
		ShapeNum			scaleshape;								//RJS 19Jan99
		Bool				nofix = FALSE;							//RJS 25Jan99
		SLong				shapeIndex = index;						//RJS 15Nov99


 		MuzzleVel = 8110000;										//RJS 12Nov99
		MuzzleDelay = 15;
		MuzzleBurst = 8;											//RDH 31Jul98
		shape= scaleshape = itm->shape;								//RJS 19Jan99

		animdataptr = itm->Anim;

		aptr = (MoveGunAnimData*) animdataptr;
		sdptr = SHAPESTUFF.GetShapePtr(scaleshape);

		if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
		{
			SLong	tmp;

			if (sdptr->Type.haslaunchers)
			{
				instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
				while	(GetGroupElement(instr_ptr,shape,gx,gy,gz))
				{
					sdptr = SHAPESTUFF.GetShapePtr(shape);
					if (sdptr->LauncherDataSize && aptr->itemstate==ALIVE)//RJS 22Nov96
					{
						thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shape,0);
						if ((thislaunch->lnchrtype & LT_MASK)!= LT_CONTACT)
							if (ltype==-1||(thislaunch->lnchrtype & LT_MASK)==ltype)
								if (index--==0)
								{	//found my launcher
									GrpMinAnimData*	gmad;				//RJS 09Dec98
									gmad = (GrpMinAnimData*) aptr;		//RJS 09Dec98
									noLaunchers = gmad->nolaunchers;	//RJS 09Dec98

									goffset=new MyGroundVector;			//RJS 21Nov96
									goffset->gx=gx;
									goffset->gy=gy;
									goffset->gz=gz;
									break;
								}
					}
					aptr=(MoveGunAnimData*)((int)aptr+GetElementAnimOffset(shape));//RJS 20Nov97
				}
				if (index!=0xff)
					return(NULL);
				index=0;
			}
			else return(NULL);
		}
		else
			noLaunchers = aptr->nolaunchers;						//RJS 17Nov98

		// now shape and sdptr points to correct element & so does aptr
		//
		//

		if ( (index >= 0) && (index < noLaunchers) && aptr->itemstate < DYING)	//CSB 23Jun00
		{
			DOLAUNCHER	fiddledlauncher;

			switch(SHAPESTUFF.GetShapeScale(sdptr))
			{
				case SHP_1CM:
					thisscale = 0;
					break;												
				case SHP_4CM:
					thisscale = 2;										
					break;												
				case SHP_16CM:
					thisscale = 4;										
					break;
			}

			// Handle sub-shape launchers.....
			if (index < MAX_WEAP_LAUNCHERS)							//RJS 10Dec99
			{
				weapon = &aptr->weaponlaunchers[index];
				if (weapon)
				{
					shapeIndex = weapon->launcherIndex;									//RJS 15Nov99
					if (weapon->stationshape)
					{
						// Get base x,y,z...
						thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shape,shapeIndex);	//RJS 15Nov99
						if (thislaunch)
						{
							// Real index and shape...
							if (weapon->LoadedStores)
							{
								DOLAUNCHER_PTR	thislaunch2;

								index = weapon->Stores - weapon->LoadedStores;
								thislaunch2 = (DOLAUNCHER_PTR) GetLauncherPos((ShapeNum)weapon->stationshape,index);//RJS 08Dec99
								if (thislaunch2)
								{
									// Sub launcher is relative to main launcher...
									fiddledlauncher = *thislaunch;
									fiddledlauncher.posx += thislaunch2->posx;
									fiddledlauncher.posy += thislaunch2->posy;
									fiddledlauncher.posz += thislaunch2->posz;
									thislaunch = &fiddledlauncher;
									nofix = TRUE;
								}
							}
						}
					}
					else
						thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shape,shapeIndex);	//RJS 15Nov99
				}
				else
					thislaunch = NULL;
			}
			else
			{
				thislaunch = NULL;
				weapon = NULL;										//RJS 25Jan99
			}

			if (thislaunch)
			{
				if (	(thislaunch->lnchrtype < LT_CONTACT)		//RJS 27May97
					||	(thislaunch->lnchrtype > CT_DUMMY)	)		//RJS 27May97
				{
					if (weapon == NULL)
						_Error.EmitSysErr(__FILE__":Weapon launcher index out of range!");
				}

				if (ltype > -1)
				{
					if (weapon)												//RJS 14Aug98
					{
						if ((weapon->LauncherType & LT_MASK) != ltype)		//RJS 14Aug98
						{
							thislaunch = NULL;
							weapon = NULL;
						}
						else
						{
							SLong	noGuns = thislaunch->noChildren;		//RJS 15Nov99
							SLong	gunno = weapon->currGun;

							if (noGuns && gunno)
							{
								if (gunno > noGuns)
									weapon->currGun = 0;
								else
									thislaunch = (DOLAUNCHER_PTR) ((UByteP)thislaunch + ((1+sizeof(DOLAUNCHER))*gunno));
							}

							//DAVE----- KEEP THIS CODE IN!!!!!!!!!						//RJS 10Sep98
							muzindex = weapon->LaunchTime & 0x00FF;						//RJS 10Sep98
							if (muzindex > MaxMuzzles)									//RJS 10Sep98
								muzindex = 0;											//RJS 10Sep98
																						//RJS 10Sep98
							MuzzleVel = launcherdata[muzindex].muzlvel;					//RJS 10Sep98
							MuzzleDelay = launcherdata[muzindex].firingdelay;			//RJS 10Sep98
							MuzzleBurst = launcherdata[muzindex].burstcount;			//RJS 10Sep98
																						//RJS 10Sep98
							if (bulletShape)											//RJS 10Sep98
								*bulletShape = (UWord) launcherdata[muzindex].theShape;	//RJS 10Sep98
						}

					}
				}
			}

//DeadCode RJS 13Mar00 		LauncherToWorld(itm,(UByteP) thislaunch,thisscale,xpos,ypos,zpos,goffset);//RJS 13Mar00
			WeaponToWorld(itm,weapon,thislaunch,thisscale,xpos,ypos,zpos,goffset);//RJS 13Mar00
		}

		if (goffset)
			delete goffset;
	}

	return(weapon);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetWeaponShape
//Author		Robert Slater
//Date			Thu 9 Dec 1999
//
//Description	Gets weapon shape for a particular launch type
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ShapeNum	shape::GetWeaponShape(WeapAnimData*	weapon)
{
	SLong	wpindex = weapon->LaunchTime & 0x00FF;
	
	if (wpindex > MaxMuzzles)
		wpindex = 0;
					
	return (ShapeNum)launcherdata[wpindex].theShape;	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNearestTrench
//Author		Robert Slater
//Date			Thu 7 Nov 1996
//
//Description	Finds nearest trench to a given troop launcher
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool shape::GetNearestTrench(	itemptr	itm,
						     	SLong&	xpos, SLong&	ypos,
							 	SLong&	zpos, SWord&	hdg)
{
	ShapeDescPtr		sdptr;
	UByteP				animdataptr;
	UByteP				instr_ptr;
	ShapeNum			shape;
	SLong				gx, gy, gz;
	SLong				dx, dy, dz;
	SLong				tx, ty, tz;
	SLong				dist;
	SWord				thehdg,thepitch;
	Bool				foundone;
	SLong				nearest;

	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
	foundone = FALSE;

	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
	{
		tx = xpos;
		ty = ypos;
		tz = zpos;

		nearest = 0x7fffffff;

		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		while	(GetGroupElement(instr_ptr,shape,gx,gy,gz))
		{
			if (	(shape == TrenchShapeBrit)
				||	(shape == TrenchShapeGerm)	)				//RJS 15Dec96
			{
//DeadCode JIM 18Dec96 			if (shape == TrenchShape)
//DeadCode JIM 18Dec96 			{
				foundone = TRUE;

				gx += itm->World.X;
				gy += itm->World.Y;
				gz += itm->World.Z;

				dx = gx - tx;
				dy = gy - ty;
				dz = gz - tz;

				Math_Lib.Intercept(dx,dy,dz,dist,thehdg,thepitch);

				if (dist < nearest)
				{
					nearest = dist;
					xpos = gx;
					ypos = gy;
					zpos = gz;

					hdg = thehdg;
				}
			}
		}
	}
	
	return(foundone);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RechargeWeapons
//Author		Robert Slater
//Date			Tue 19 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::RechargeWeapons(itemptr	itm)
{
//DeadCode RJS 7Jun00 	ShapeDescPtr		sdptr;
//DeadCode RJS 7Jun00 	AircraftAnimData*	adptr;
//DeadCode RJS 7Jun00 	WeapAnimData*		weapon=NULL;
//DeadCode RJS 7Jun00 	int					count,index;
//DeadCode RJS 7Jun00 	UByte				lchtype;

//DeadCode RJS 7Jun00 	adptr = (AircraftAnimData*) itm->Anim;

	if (itm->Status.size == AirStrucSize)
	{
		Trans_Obj.ReloadWeapons(AirStrucPtr(itm));				//RJS 11May98	//RJS 7Jun00
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WeapUnitWeight
//Author		Robert Slater
//Date			Thu 2 Oct 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::WeapUnitWeight(LnchrType	lnchr)
{
//	int	index;
//	int	retval = 0;
//
//	index = 0;
//
//	while (WeapWeights[index].lnchr != LT_CONTACT)
//	{
//		if (WeapWeights[index].lnchr == lnchr)
//		{
//			retval = WeapWeights[index].unitweight;
//			break;
//		}
//		else
//			index++;
//	}
//
	return(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReduceLauncherLoad
//Author		Robert Slater
//Date			Wed 13 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::ReduceLauncherLoad(	AirStrucPtr	itm,
									SWord		index,
									SWord		count)
{
	SLong	mass = 0;											//RJS 15Nov99
	if (index < MAX_WEAP_LAUNCHERS)								//RJS 15Nov99
	{
		DOLAUNCHER_PTR		lptr;
		WeapAnimData*		weapon;
		MoveGunAnimData*	adptr = (MoveGunAnimData*) itm->Anim;		//RJS 7Jun00
		ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
		UByte				instsize = sizeof(DOLAUNCHER) + 1;
		UByteP				instr_ptr;
		UByteP				base_ptr;
		UWord				instruction;
		SLong				stores;
		weap_info			*weapptr;
		Bool				isFuel=TRUE;
		SLong				xdelta, drag;						//RJS 15Nov99

		base_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

//DeadCode RJS 10Jul00 		instr_ptr = base_ptr + (instsize * index);
//DeadCode RJS 10Jul00 		instr_ptr++;
//DeadCode RJS 10Jul00 
//DeadCode RJS 10Jul00 		lptr = (DOLAUNCHER_PTR) instr_ptr;
//DeadCode RJS 10Jul00 
//DeadCode RJS 10Jul00 		xdelta = lptr->posx;
		mass = 0;//RJS 16Sep98
		if (count)													//RJS 18Jun99
		{
			weapon = (WeapAnimData*) &adptr->weaponlaunchers[index];
			if (((weapon->LauncherType == LT_FUEL) || (!Save_Data.gamedifficulty[GD_UNLIMITEDARM]))//RJS 06May99
				&& !(_DPlay.Implemented && _DPlay.GameType<DPlay::COMMSQUICKMISSION && weapon->LauncherType==LT_BOMB))	// 13Oct00
			{
				UWord			index_shpweap = itm->weap.shpweapindex;	//RJS 10Jul00
				UWord			index_weap;
				ShpToWeapType	sweap = ShpToWeap[index_shpweap];

				instr_ptr = base_ptr + (instsize * (weapon->launcherIndex + weapon->currGun));

				lptr = DOLAUNCHER_PTR(instr_ptr+1);						//RJS 10Jul00

				xdelta = lptr->posx;

				index_weap = (weapon->LaunchTime & 0xFF00)>>8;

				mass = sweap.LchList[index_weap].Weight;
				if (mass)
				{
					LnchrType	lchtype = (LnchrType) weapon->LauncherType;

					drag = sweap.LchList[index_weap].Drag;

					mass *= count;
					drag *= count;

					if ((xdelta < -40) || (xdelta > 40))
					{
						if (xdelta < 0)
							weapptr = &itm->weap.left;
						else
							weapptr = &itm->weap.right;
					}
					else
					{
						xdelta = 0;
						weapptr = &itm->weap.centre;
					}

					if (lchtype != LT_FUEL)
						isFuel = FALSE;

					if (mass > weapptr->mass)	mass = weapptr->mass;	//RJS 10Jul00
					if (drag > weapptr->drag)	drag = weapptr->drag;	//RJS 10Jul00
					weapptr->mass -= mass;						//RJS 18Jun99
					weapptr->drag -= drag;						//RJS 18Jun99

					itm->fly.pModel->RemoveStore(weapptr,xdelta,mass,drag,isFuel);
					if (isFuel)
					{
						int	tankindex;
						for (tankindex = 0; tankindex < 4; tankindex++)
						{
							if (	(xdelta==itm->classtype->fueltankxpos[tankindex])
								&&	(itm->classtype->fueltanktype[tankindex] == FT_DROPTANK)	)
								break;
						}

						if (tankindex != 4)
							itm->fly.fuel_content[tankindex]=0;
					}
				}																	//RDH 03Aug98
			}
		}
	}

	return(mass);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LauncherToWorld
//Author		Robert Slater
//Date			Wed 28 Aug 1996
//
//Description	Transforms and scales an item's launcher coordinates relative
//				to the item
//
//Inputs		The item, position, scale, x,y,z return values
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::LauncherToWorld(	itemptr	itm,
								UByteP position,
								UByte	thisscale,
								SLong& xpos, SLong& ypos, SLong& zpos,
								MyGroundVectorPtr	goffset	)			//RJS 13Mar00
{
//	MATRIX   			omat;						
//	MATRIX_PTR			obj_matrix = &omat;
	SLong				tmpx, tmpy, tmpz;
	SLong				pivotx, pivoty, pivotz;
	DOLAUNCHER_PTR		thislaunch;
	mobileitem*			tmpitm = (mobileitem*) itm;
 	UWord				scaleback;
//DeadCode RJS 13Mar00	SWord				eyefixX, eyefixY, eyefixZ;

//DeadCode RJS 10Dec99 	if (eyePtr)
//DeadCode RJS 10Dec99 	{
//DeadCode RJS 10Dec99 		eyefixX = eyePtr->X;
//DeadCode RJS 10Dec99 		eyefixY = eyePtr->Y;
//DeadCode RJS 10Dec99 		eyefixZ = eyePtr->Z;
//DeadCode RJS 10Dec99 	}
//DeadCode RJS 10Dec99 	else
//DeadCode RJS 10Dec99 	{
//DeadCode RJS 10Dec99 		eyefixX = 0;
//DeadCode RJS 10Dec99 		eyefixY = 0;
//DeadCode RJS 10Dec99 		eyefixZ = 0;
//DeadCode RJS 10Dec99 	}

	thislaunch = (DOLAUNCHER_PTR) position;
	if (thislaunch)
	{
		tmpx = thislaunch->posx << thisscale;			
		tmpy = thislaunch->posy << thisscale;		
		tmpz = thislaunch->posz << thisscale;

//DeadCode RJS 13Mar00		if (incock)			//RJS 08Dec98
//DeadCode RJS 13Mar00		{
//DeadCode RJS 13Mar00			ClassPtr	clstyp = ((AirStrucPtr)itm)->classtype;		//RJS 19Jan99
//DeadCode RJS 13Mar00
//DeadCode RJS 13Mar00			tmpx=SLong(Float(tmpx)*clstyp->cockscale);		//RJS 19Jan99
//DeadCode RJS 13Mar00			tmpy=SLong(Float(tmpy)*clstyp->cockscale); 		//RJS 19Jan99
//DeadCode RJS 13Mar00			tmpz=SLong(Float(tmpz)*clstyp->cockscale);		//RJS 19Jan99
//DeadCode RJS 13Mar00		}
//DeadCode RJS 10Dec99 //		tmpx += eyefixX;
//DeadCode RJS 10Dec99 //		tmpy += eyefixY;
//DeadCode RJS 10Dec99 //		tmpz += eyefixZ;
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 		ANGLES	weaphdg;
//DeadCode RJS 13Mar00 		ANGLES	weappitch;
//DeadCode RJS 13Mar00 		ANGLES	weaproll;
//DeadCode RJS 13Mar00 		bool	usemodel = false;
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 		if (tmpitm == Manual_Pilot.ControlledAC2)			//RJS 10Dec99
//DeadCode RJS 13Mar00 		{
//DeadCode RJS 13Mar00 			//store hdg, pitch in the weapon struc,
//DeadCode RJS 13Mar00 			// but remember to null them if taken over by smoke trail
//DeadCode RJS 13Mar00 			if (reargunner_active)
//DeadCode RJS 13Mar00 			{
//DeadCode RJS 13Mar00 				MoveGunAnimData* adptr = (MoveGunAnimData*)tmpitm->Anim;
//DeadCode RJS 13Mar00 				FPMATRIX		omat;
//DeadCode RJS 13Mar00 				FPMATRIX_PTR	omatp = &omat;
//DeadCode RJS 13Mar00 				Float			sh,sp,ch,cp;
//DeadCode RJS 13Mar00 				Float			sp_sh,sp_ch;
//DeadCode RJS 13Mar00 				float			nx,ny,nz;
//DeadCode RJS 13Mar00 				Float			f_nx,f_ny,f_nz;
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				weaphdg = (Angles)adptr->weaponlaunchers[reargunner_index].hdg;//RJS 10Mar00
//DeadCode RJS 13Mar00 				weappitch = (Angles)adptr->weaponlaunchers[reargunner_index].pitch;//RJS 10Mar00
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				Math_Lib.high_sin_cos(weaphdg,sh,ch);
//DeadCode RJS 13Mar00 				Math_Lib.high_sin_cos(weappitch,sp,cp);
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				sp_sh = sp * sh;
//DeadCode RJS 13Mar00 				sp_ch = sp * ch;
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				// Unit vectors:
//DeadCode RJS 13Mar00 				// v_x = sh * cp;			// 13
//DeadCode RJS 13Mar00 				// v_y = sp;				// 23
//DeadCode RJS 13Mar00 				// v_z = ch * cp;			// 33
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				omat.L11 = ch;
//DeadCode RJS 13Mar00 				omat.L12 = -sp_sh;
//DeadCode RJS 13Mar00 				omat.L13 = cp * sh;
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				omat.L21 = 0;
//DeadCode RJS 13Mar00 				omat.L22 = cp;
//DeadCode RJS 13Mar00 				omat.L23 = sp;
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				omat.L31 = -sh;
//DeadCode RJS 13Mar00 				omat.L32 = -sp_ch;
//DeadCode RJS 13Mar00 				omat.L33 = cp * ch;
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				pivotx = thislaunch->pivotx << thisscale;			
//DeadCode RJS 13Mar00 				pivoty = thislaunch->pivoty << thisscale;		
//DeadCode RJS 13Mar00 				pivotz = thislaunch->pivotz << thisscale;
//DeadCode RJS 13Mar00 		
//DeadCode RJS 13Mar00 				// Subtract base pivot offset...
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				tmpx -= pivotx;
//DeadCode RJS 13Mar00 				tmpy -= pivoty;
//DeadCode RJS 13Mar00 				tmpz -= pivotz;
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				f_nx = tmpx;
//DeadCode RJS 13Mar00 				f_ny = tmpy;
//DeadCode RJS 13Mar00 				f_nz = tmpz;
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				nx = (omatp->L11 * f_nx) + (omatp->L12 * f_ny) + (omatp->L13 * f_nz);
//DeadCode RJS 13Mar00 				ny = (omatp->L21 * f_nx) + (omatp->L22 * f_ny) + (omatp->L23 * f_nz);
//DeadCode RJS 13Mar00 				nz = (omatp->L31 * f_nx) + (omatp->L32 * f_ny) + (omatp->L33 * f_nz);
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				fastMath.FloatToInt(&tmpx,nx);
//DeadCode RJS 13Mar00 				fastMath.FloatToInt(&tmpy,ny);
//DeadCode RJS 13Mar00 				fastMath.FloatToInt(&tmpz,nz);
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				// Add base pivot back on...
//DeadCode RJS 13Mar00 				tmpx += pivotx;
//DeadCode RJS 13Mar00 				tmpy += pivoty;
//DeadCode RJS 13Mar00 				tmpz += pivotz;
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				((AirStrucPtr)tmpitm)->fly.pModel->SetGunOri(omat.L13,omat.L23,omat.L33);
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 				if((!_Replay.Playback) && (!tmpitm->Status.deadtime))
//DeadCode RJS 13Mar00 					usemodel = true;
//DeadCode RJS 13Mar00 				else
//DeadCode RJS 13Mar00 				{
//DeadCode RJS 13Mar00 					weaphdg = tmpitm->hdg;
//DeadCode RJS 13Mar00 					weappitch = tmpitm->pitch;
//DeadCode RJS 13Mar00 					weaproll = tmpitm->roll;
//DeadCode RJS 13Mar00 				}
//DeadCode RJS 13Mar00 			}
//DeadCode RJS 13Mar00 			else
//DeadCode RJS 13Mar00 			{
//DeadCode RJS 13Mar00 				if((!_Replay.Playback) && (!tmpitm->Status.deadtime))
//DeadCode RJS 13Mar00 					usemodel = true;
//DeadCode RJS 13Mar00 				else
//DeadCode RJS 13Mar00 				{
//DeadCode RJS 13Mar00 					weaphdg = tmpitm->hdg;
//DeadCode RJS 13Mar00 					weappitch = tmpitm->pitch;
//DeadCode RJS 13Mar00 					weaproll = tmpitm->roll;
//DeadCode RJS 13Mar00 				}
//DeadCode RJS 13Mar00 			}
//DeadCode RJS 13Mar00 		}
//DeadCode RJS 13Mar00 		else
//DeadCode RJS 13Mar00 		{
//DeadCode RJS 13Mar00 			weaphdg = tmpitm->hdg;
//DeadCode RJS 13Mar00 			weappitch = tmpitm->pitch;
//DeadCode RJS 13Mar00 			weaproll = tmpitm->roll;
//DeadCode RJS 13Mar00 		}
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 		if (usemodel)											//RJS 10Dec99
//DeadCode RJS 13Mar00 			((AirStrucPtr)tmpitm)->fly.pModel->CalcLauncherPos(tmpx,tmpy,tmpz);
//DeadCode RJS 13Mar00 		else
//DeadCode RJS 13Mar00 		{

		if (	(itm == Persons2::PlayerSeenAC)
			&&	!_Replay.Playback
			&&	!itm->Status.deadtime	)
 			((AirStrucPtr)tmpitm)->fly.pModel->CalcLauncherPos(tmpx,tmpy,tmpz);
		else
		{
			if (itm->Status.size >= MOBILESIZE)
			{
				MATRIX   			omat;						
				MATRIX_PTR			obj_matrix = &omat;

				_matrix.generate2(tmpitm->hdg,tmpitm->pitch,tmpitm->roll,obj_matrix);//RJS 13Mar00
			
				scaleback = _matrix.transform(obj_matrix,tmpx,tmpy,tmpz);

 				tmpx >>= (16-scaleback);
 				tmpy >>= (16-scaleback);
 				tmpz >>= (16-scaleback);
 			}
		}
	}
	else
	{
		tmpx = 0;												//RJS 10Dec99
		tmpy = 0;												//RJS 10Dec99
		tmpz = 0;												//RJS 10Dec99
	}

	xpos = tmpx + itm->World.X;
	ypos = tmpy + itm->World.Y;
	zpos = tmpz + itm->World.Z;

	if (goffset)
	{
		xpos += goffset->gx;
		ypos += goffset->gy;
		zpos += goffset->gz;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoTrailPoint
//Author		Robert Slater
//Date			Mon 23 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Float	shape::DoTrailPoint(UWord	vertex, SLong wx, SLong wy, SLong wz)
{
//DeadCode RJS 19May00 	IFShare	ifwx,ifwy,ifwz;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	ifwx.i=wx; ifwy.i=wy; ifwz.i=wz;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	FPMATRIX_PTR	fpobj_matrix = Three_Dee.fpviewer_matrix;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	_matrix.transformNC(fpobj_matrix,ifwx,ifwy,ifwz);
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	newco[vertex].setPosition(	ifwx.f, ifwy.f,	ifwz.f	);		//RJS 19May00
//DeadCode RJS 19May00 //DeadCode RJS 19May00  	newco[vertex].bodyx.f = ifwx.f;								//RJS 02Jun97
//DeadCode RJS 19May00 //DeadCode RJS 19May00  	newco[vertex].bodyy.f = ifwy.f;								//RJS 02Jun97
//DeadCode RJS 19May00 //DeadCode RJS 19May00  	newco[vertex].bodyz.f = ifwz.f;								//RJS 02Jun97
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //deadcode	_matrix.body2screen(newco[vertex]);							//PD 25Jul96
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	return (newco[vertex].bodyz.f);								//RJS 02Jun97

	return 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroupItemAnim
//Author		Robert Slater
//Date			Wed 2 Oct 1996
//
//Description	Finds position in group anim data, with regard to group index
//
//Inputs		Group item, index
//
//Returns		animation data pointer
//
//------------------------------------------------------------------------------
UByteP	shape::GetGroupItemAnim(itemptr	itm, ShapeNum& shape, SByte	index, MyGroundVectorPtr P)
{
	ShapeDescPtr		sdptr;
	ShapeNum			newshp;
	animptr				animdataptr;
	UByteP				indexedptr;
	UByteP				instr_ptr;
	int					totalsize;
	int					thisindex;
	animptr				dummyadptr;

	animdataptr = itm->Anim;
	indexedptr = &animdataptr[0];
	dummyadptr = animdataptr;

	shape = itm->shape;
	sdptr = SHAPESTUFF.GetShapePtr(shape);						//RJS 14Oct96

	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
	{
		SLong	tmpx,tmpy,tmpz,yDelta;							//RJS 03Dec98
		
		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		thisindex = 0;
		totalsize = 0;

		while	(GetGroupElement(instr_ptr,newshp,tmpx,tmpy,tmpz))//RJS 21Nov96
		{
			if (thisindex == index)
			{
				Coords3D	tmpworld;
				indexedptr = (UByteP) &animdataptr[totalsize];
				shape = newshp;
				tmpworld = itm->World;
				tmpworld.X += tmpx;
				tmpworld.Y += tmpy;
				tmpworld.Z += tmpz;

				dummyadptr = indexedptr;

				yDelta = GetElementYDelta(shape,dummyadptr,tmpworld,itm->World.Y);	//RJS 09Jun99
				yDelta <<= 4;

				P->gx = tmpworld.X;
				P->gy = tmpworld.Y + yDelta;
				P->gz = tmpworld.Z;
				break;
			}
			else
			{
				thisindex++;
				totalsize += GetElementAnimOffset(newshp);		//RJS 20Nov97
			}
		}
	}
	else
	{
		P->gx = itm->World.X;
		P->gy = itm->World.Y;
		P->gz = itm->World.Z;
	}

	return(indexedptr);
}

UByteP	shape::GetGroupItemAnimHdg(itemptr	itm, ShapeNum& shape, SByte	index, MyGroundVector* P, UWord& ghdg)
{
	ShapeDescPtr		sdptr;
	ShapeNum			newshp;
	animptr				animdataptr;
	UByteP				indexedptr = NULL;
	UByteP				instr_ptr;
	int					totalsize;
	int					thisindex;
	SWord				thehdg;
	animptr				dummyadptr;

	animdataptr = itm->Anim;
	dummyadptr = animdataptr;
	indexedptr = &animdataptr[0];

	shape = itm->shape;
	sdptr = SHAPESTUFF.GetShapePtr(shape);						//RJS 14Oct96
	ghdg = 0;

	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
	{
		SLong	tmpx,tmpy,tmpz,yDelta;							//RJS 03Dec98
		
		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		thisindex = 0;
		totalsize = 0;

		while	(GetGroupElement(instr_ptr,newshp,tmpx,tmpy,tmpz,0,NULL,&thehdg))//RJS 18Nov98
		{
			if (thisindex == index)
			{
				Coords3D	tmpworld;
				indexedptr = (UByteP) &animdataptr[totalsize];
				shape = newshp;
				ghdg = UWord(thehdg);

				tmpworld = itm->World;
				tmpworld.X += tmpx;
				tmpworld.Y += tmpy;
				tmpworld.Z += tmpz;

				dummyadptr = indexedptr;

				yDelta = GetElementYDelta(shape,dummyadptr,tmpworld,itm->World.Y);	//RJS 09Jun99
				yDelta <<= 4;

				P->gx = tmpworld.X;
				P->gy = tmpworld.Y + yDelta;
				P->gz = tmpworld.Z;
				break;
			}
			else
			{
				thisindex++;
				totalsize += GetElementAnimOffset(newshp);		//RJS 20Nov97
			}
		}
	}
	else
	{
		P->gx = itm->World.X;
		P->gy = itm->World.Y;
		P->gz = itm->World.Z;
		if (itm->Status.size >= HDGSIZE)						//RJS 02Dec98
			ghdg = ((rotitem*)itm)->hdg;						//RJS 02Dec98
	}

	return(indexedptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroupDeathToll
//Author		Robert Slater
//Date			Wed 16 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte	shape::GetGroupDeathToll(itemptr	itm)
{
	ShapeDescPtr		sdptr;
	ShapeNum			newshp;
	animptr				animdataptr;
	MinAnimData*		adptr = NULL;
	UByteP				instr_ptr;
	SLong				deathtoll;
	SLong				priority ;
	UByte				noimportant;

	animdataptr = itm->Anim;
	adptr = (MinAnimData*) animdataptr;

	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);						//RJS 14Oct96
	deathtoll = 0;
	noimportant = 0;

	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
	{
		SLong	tmp;
		
		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;

		priority = GetGroupElement(instr_ptr,newshp,tmp,tmp,tmp);//RJS 14Nov96

		while(priority)											//RJS 27Feb98
		{														//RJS 27Feb98
			adptr = (MinAnimData*) animdataptr;
			if (adptr->itemstate == DEAD)						//RJS 27Feb98
				deathtoll += priority;							//RJS 27Feb98

			animdataptr += (int)GetElementAnimOffset(newshp);
			priority = GetGroupElement(instr_ptr,newshp,tmp,tmp,tmp);//RJS 14Nov96
		}

		if (deathtoll < 250)									//RJS 27Feb98
			deathtoll = 0;										//RJS 27Feb98
	}

	return(deathtoll);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyAnimData
//Author		Paul.   
//Date			Wed 27 Mar 1996
//
//Description	Copys animdata from one source to a new source
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByteP shape::CopyAnimData(animptr& adptr,ShapeNum shpno)
{
	int	j;

	SLong	adsize;

	UByteP	dstptr,retval;

	adsize = GetAnimDataSize(shpno);

	dstptr =
		retval = new UByte [adsize];

	for (j=0; j < adsize; j++)
		dstptr[j] = adptr[j];

//DeadCode RJS 21Apr99 	for (j=adsize;j--;)
//DeadCode RJS 21Apr99 		*dstptr++ = *adptr++;

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetAnimFlags
//Author		Paul.   
//Date			Wed 27 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::ResetAnimFlags()
{
	UByteP	tmp = animflags;

	int	j;

//DeadCode RJS 26Nov96 	for (j=MAXANIMFLAG;j--;)
//DeadCode RJS 26Nov96 		*tmp++=0;

	for (j=MAXANIMFLAG-2;j--;)									//RJS 26Nov96
		*tmp++=0;
}

//DeadCode RJS 05Jun97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 05Jun97 //Procedure		SimpleItemAnim
//DeadCode RJS 05Jun97 //Author		Paul.   
//DeadCode RJS 05Jun97 //Date			Wed 27 Mar 1996
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //Description	
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //Inputs		
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //Returns	
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //------------------------------------------------------------------------------
//DeadCode RJS 05Jun97 void shape::SimpleItemAnim(MinAnimData* adptr)
//DeadCode RJS 05Jun97 {
//DeadCode RJS 05Jun97 	if (adptr)													//PD 02Apr96
//DeadCode RJS 05Jun97 		*(animflags+ITEMSTATE) = (UByte )(adptr->itemstate);	//PD 02Apr96
//DeadCode RJS 05Jun97 }

//DeadCode RJS 05Jun97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 05Jun97 //Procedure		ExplodeItemAnim
//DeadCode RJS 05Jun97 //Author		Paul.   
//DeadCode RJS 05Jun97 //Date			Mon 15 Apr 1996
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //Description	
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //Inputs		
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //Returns	
//DeadCode RJS 05Jun97 //
//DeadCode RJS 05Jun97 //------------------------------------------------------------------------------
//DeadCode RJS 05Jun97 void shape::ExplodeItemAnim(ExplodeAnimData* adptr)
//DeadCode RJS 05Jun97 {
//DeadCode RJS 05Jun97 //DeadCode RJS 05Jun97 	SimpleItemAnim((MinAnimData* )adptr);
//DeadCode RJS 05Jun97 
//DeadCode RJS 05Jun97 	*(animflags+EXPLODEFRAME) = adptr->frameno;
//DeadCode RJS 05Jun97 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlameItemAnim
//Author		Robert Slater
//Date			Wed 10 Jul 1996
//
//Description	Launch point for birds or troops...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::FlameItemAnim(FireAnimData* adptr)

{
//DeadCode RJS 05Jun97 	SimpleItemAnim((MinAnimData* )adptr);
//DeadCode RJS 16Nov98 
//DeadCode RJS 16Nov98 	if (!Three_Dee.IsPaused())									//RJS 27Feb98
//DeadCode RJS 16Nov98 	{
//DeadCode RJS 16Nov98 		WorldStuff*	worldptr = mobileitem::currworld;				//RJS 08Nov96
//DeadCode RJS 16Nov98 
//DeadCode RJS 16Nov98 	//DeadCode RJS 18Oct96 	*(animflags+EXPLODEFRAME) = adptr->frameno;
//DeadCode RJS 16Nov98 		if (object_obj3d->Shape == TroopLauncherShape)
//DeadCode RJS 16Nov98 		{
//DeadCode RJS 16Nov98 			if (adptr->frameno == 0)								
//DeadCode RJS 16Nov98 				Trans_Obj.LaunchTroops((mobileitem*) object_obj3d->ItemPtr,0,0,0,*worldptr);				//RJS 08Nov96
//DeadCode RJS 16Nov98 		}
//DeadCode RJS 16Nov98 		else
//DeadCode RJS 16Nov98 		{
//DeadCode RJS 16Nov98 			if (	(Math_Lib.rnd() > 65000)					//RJS 10Dec96
//DeadCode RJS 16Nov98 				&&  (adptr->frameno == 0)
//DeadCode RJS 16Nov98 				&&	(object_obj3d->realbz.f < (Float)30000))
//DeadCode RJS 16Nov98 				Trans_Obj.LaunchBirds((mobileitem*) object_obj3d->ItemPtr,BirdShape,*worldptr);
//DeadCode RJS 16Nov98 		}
//DeadCode RJS 16Nov98 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BalloonItemAnim
//Author		Robert Slater
//Date			Mon 5 Aug 1996
//
//Description	Launch a parachute from balloon if close enough and not already
//				done so...
//				Then lower the balloon
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::BalloonItemAnim(BalloonAnimData* adptr, Obj3DPtr thisobj3d)//RJS 07Feb00
{
//DeadCode RJS 06Dec99 	SLong	yshift;
//DeadCode RJS 06Dec99 
//DeadCode RJS 06Dec99 //DeadCode RJS 05Jun97 	SimpleItemAnim((MinAnimData* )adptr);
//DeadCode RJS 06Dec99 
//DeadCode RJS 06Dec99 	if (!Three_Dee.IsPaused())									//RJS 27Feb98
//DeadCode RJS 06Dec99 	{
//DeadCode RJS 06Dec99 		if ( (adptr->itemstate == DEAD) && (adptr->countdown > -300) )
//DeadCode RJS 06Dec99 		{
//DeadCode RJS 06Dec99 			adptr->frameno++;
//DeadCode RJS 06Dec99 			if (adptr->frameno > 7)
//DeadCode RJS 06Dec99 				adptr->frameno = 0;
//DeadCode RJS 06Dec99 
//DeadCode RJS 06Dec99 			*(animflags+EXPLODEFRAME) = adptr->frameno;
//DeadCode RJS 06Dec99 			adptr->countdown--;
//DeadCode RJS 06Dec99 			adptr->manjumped = TRUE;							//RJS 26Nov96
//DeadCode RJS 06Dec99 		}
//DeadCode RJS 06Dec99 
//DeadCode RJS 06Dec99 		if (adptr->manjumped == FALSE)
//DeadCode RJS 06Dec99 		{
//DeadCode RJS 06Dec99 			if (	(thisobj3d->realbz.f < (Float)30000)
//DeadCode RJS 06Dec99 				)
//DeadCode RJS 06Dec99 			{
//DeadCode RJS 06Dec99 				WorldStuff*	worldptr = mobileitem::currworld;
//DeadCode RJS 06Dec99 				Trans_Obj.LaunchParachute((mobileitem*) thisobj3d->ItemPtr,*worldptr);
//DeadCode RJS 06Dec99 			}
//DeadCode RJS 06Dec99 		}
//DeadCode RJS 06Dec99 		else
//DeadCode RJS 06Dec99 		{
//DeadCode RJS 06Dec99 			if (adptr->countdown > 0)
//DeadCode RJS 06Dec99 				adptr->countdown--;
//DeadCode RJS 06Dec99 			else
//DeadCode RJS 06Dec99 			{
//DeadCode RJS 06Dec99 				if (thisobj3d->ItemPtr->World.Y > (adptr->groundheight + 500))
//DeadCode RJS 06Dec99 				{
//DeadCode RJS 06Dec99 					if (adptr->itemstate == DEAD)
//DeadCode RJS 06Dec99 					{
//DeadCode RJS 06Dec99 						yshift = (15000 * Timer_Code.FRAMETIME) / 100;
//DeadCode RJS 06Dec99 						thisobj3d->ItemPtr->World.Y -= yshift;
//DeadCode RJS 06Dec99 						Trans_Obj.AddWindDrift(thisobj3d->ItemPtr);//RJS 07Jan97
//DeadCode RJS 06Dec99 					}
//DeadCode RJS 06Dec99 					else
//DeadCode RJS 06Dec99 					{
//DeadCode RJS 06Dec99 						yshift = (5000 * Timer_Code.FRAMETIME) / 100;
//DeadCode RJS 06Dec99 						thisobj3d->ItemPtr->World.Y -= yshift;
//DeadCode RJS 06Dec99 					}
//DeadCode RJS 06Dec99 				}
//DeadCode RJS 06Dec99 				else
//DeadCode RJS 06Dec99 				{
//DeadCode RJS 06Dec99 					if (adptr->itemstate == DEAD)
//DeadCode RJS 06Dec99 					{
//DeadCode RJS 06Dec99 						WorldStuff*	worldptr = mobileitem::currworld;
//DeadCode RJS 06Dec99 						Trans_Obj.LaunchBigExplosion((mobileitem*) thisobj3d->ItemPtr,*worldptr);
//DeadCode RJS 06Dec99 //DeadCode RDH 17Dec96 						worldptr->RemoveFromWorld(thisobj3d->ItemPtr);
//DeadCode RJS 06Dec99 						thisobj3d->ItemPtr->shape = EMPTY;		//RDH 17Dec96
//DeadCode RJS 06Dec99 					}
//DeadCode RJS 06Dec99 				}
//DeadCode RJS 06Dec99 			}
//DeadCode RJS 06Dec99 		}
//DeadCode RJS 06Dec99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WindsockItemAnim
//Author		Robert Slater
//Date			Mon 12 Aug 1996
//
//Description	Points a windsoc animation item in the right direction.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::WindsockItemAnim(WindsocAnimData* adptr)			//RJS 05Jun97
{
	SLong	windscale = 0;
	SLong	vx,vy,vz;

	float	vel = MissManCampSky().GetWind(object_obj3d->ItemPtr->World.Y,vx,vy,vz);//RJS 16Dec99
	if (vel)
	{
//DeadCode RJS 16Dec99		vel = Math_Lib.distance3d(vx,vy,vz) / 10000;				//RJS 30Apr99 //CB 18/11/99
		object_obj3d->AngH = Angles(SLong(MissManCampSky().dir0) * 10430);

		vel*=0.00255;	//	(255 max frame, maxwindvel = 10ms (100000)

		windscale = SLong(vel);
		if (windscale > 255)
			windscale = 255;
	}

	// this is a morph frame, i.e. 0-255 csecs
	adptr->animclock = windscale;									//RJS 05Jun97
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveGunItemAnim
//Author		Robert Slater
//Date			Tue 15 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::MoveGunItemAnim(MoveGunAnimData* adptr)
{
	object_obj3d->AngH += Angles(adptr->weaponlaunchers[0].hdg);
	object_obj3d->AngC = ANGLES_0Deg;			
	object_obj3d->AngR = ANGLES_0Deg;		
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TankItemAnim
//Author		Robert Slater
//Date			Thu 17 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::TankItemAnim(MoveGunAnimData* adptr)
{
	SWord		pitchscale;
	UWord		framestep = ANGLES_90Deg / 6;			 
	ANGLES		thepitch;

//DeadCode RJS 05Jun97 	SimpleItemAnim((MinAnimData* )adptr);						//RJS 14Nov96

	if ((adptr->itemstate == ALIVE)	&& !Three_Dee.IsPaused())	//RJS 27Feb98
	{
		ShapeDescPtr	sdptr;									//RJS 13Nov96

		sdptr = SHAPESTUFF.GetShapePtr(object_obj3d->ItemPtr->shape);//RJS 13Nov96
		if (SHAPESTUFF.GetShapeScale(sdptr) != SHP_GRP)			//RJS 13Nov96
		{
			SByte		distance;								//RJS 13Nov96
//DeadCode RJS 20Oct00 			WorldStuff*	worldptr = mobileitem::currworld;			//RJS 13Nov96
			WeapAnimData*	weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];//RJS 05Jun97

//DeadCode RJS 05Jun97 			SimpleItemAnim((MinAnimData* )adptr);

 			pitchscale = ((SWord)weapon->pitch / framestep);			//RJS 05Jun97

			if (pitchscale < 0)
				pitchscale = 0;

			if (pitchscale > 5)
				pitchscale = 5;

			weapon->stationshape = pitchscale;					//RJS 05Jun97

			if (object_obj3d->realbz.f > (Float)30000)					//RJS 13Nov96
				distance = 1;
			else
				distance = 0;

			if (object_obj3d->ItemPtr->Status.size == FORMATIONSIZE)//RJS 15Dec96
			{
//DeadCode RJS 20Apr98 				_Miles.PlayLooped(FIL_SFX_TANK_LOOP1, (ItemBasePtr) object_obj3d->ItemPtr,128,8);//RJS 22Nov96
//DeadCode RJS 27Aug98 				Trans_Obj.LaunchDustTrail((mobileitem*) object_obj3d->ItemPtr,*worldptr,distance);//RJS 13Nov96
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TruckItemAnim
//Author		Robert Slater
//Date			Thu 17 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::TruckItemAnim(MinAnimData* adptr, UByteP	descptr)
{
//TempCode RJS 18May99 	if (adptr->itemstate == ALIVE)
//TempCode RJS 18May99 	{
//TempCode RJS 18May99 		if (object_obj3d->ItemPtr->Status.size >= MovingSize)
//TempCode RJS 18May99 		{
//TempCode RJS 18May99 			mobileitem*	itm = (mobileitem*)object_obj3d->ItemPtr;
//TempCode RJS 18May99 			FakeDustTrail(itm,vel,SWord(itm->hdg),descptr);
//TempCode RJS 18May99 		}
//TempCode RJS 18May99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TrainItemAnim
//Author		Robert Slater
//Date			Thu 17 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::TrainItemAnim(TrainAnimData* adptr)
{
	WeapAnimData*	weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];
	if (weapon)
	{
		SLong	index = weapon->hdg;

		if (adptr->itemstate != DEAD)
		{
			if (Math_Lib.rnd() > 65000)
				_Miles.PlayDelayed(FIL_SFX_TRAIN_WHISTLE,object_obj3d->ItemPtr);//RJS 05Nov99

			if (!index)
			{
				Trans_Obj.LaunchVapourStream((UByteP)weapon,(ShapeNum)object_obj3d->Shape);
				weapon->pitch = -1;
			}
		}
		else
		{
			if (index > 0)
			{
				pTrailItm = object_obj3d->ItemPtr;				//RJS 07Jul99
				SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
			 	weapon->hdg = 0;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TroopItemAnim
//Author		Robert Slater
//Date			Fri 18 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::TroopItemAnim(TroopAnimData* adptr,ItemPtr	theItem)	//RJS 22Dec99
{
#ifndef	NOANIMATIONS

// May as well transition smoothly between all anims, as this game is not time-critical...
//DEADCODE RJS 4/14/00 	if (adptr->animCtrl_new != adptr->animCtrl_prev)
//DEADCODE RJS 4/14/00 	{
//DEADCODE RJS 4/14/00 		AnimMoves		transAnim = BLOKE_NULL;
//DEADCODE RJS 4/14/00 
//DEADCODE RJS 4/14/00 		adptr->newanimpose = Anim_Control.GetAnimMove(tAnimation(adptr->animCtrl_new),AnimMoves(adptr->animpose),transAnim);
//DEADCODE RJS 4/14/00 		adptr->animCtrl_prev = adptr->animCtrl_new;
//DEADCODE RJS 4/14/00 	}

	if (adptr->swapnow)
	{
		adptr->animCtrl_current = adptr->animCtrl_new;			//RJS 13Apr00
		if (adptr->newanimpose != adptr->animpose)
		{
			adptr->animtime = 0;
			adptr->animframe = 0;
			adptr->swapnow = 0;

			adptr->animpose = adptr->newanimpose;
		}
	}
#else
	adptr->animpose = 0;
#endif

	if (adptr->haschute)										//RJS 22Dec99
	{
		TransientItem*	targ = (TransientItem*) *theItem;
		TransientItem*	theChute = (TransientItem*) *targ->Target; 
		if (theChute)
		{
			if (targ->pitch)
			{
				Float	sin_hdg, cos_hdg;
				Float	sin_pitch,cos_pitch;
				const	Float	bloke_height = 150.;
				float	bx, by, bz, bh;
				float	pos_x, pos_y, pos_z;


				Math_Lib.high_sin_cos(targ->pitch,sin_pitch,cos_pitch);
				Math_Lib.high_sin_cos(targ->hdg,sin_hdg,cos_hdg);

				bh = sin_pitch * bloke_height;
				by = cos_pitch * bloke_height;

				bx = bh * sin_hdg;
				bz = bh * cos_hdg;

				pos_x = object_obj3d->Body.X.f;
				pos_y = object_obj3d->Body.Y.f;
				pos_z = object_obj3d->Body.Z.f;

				object_obj3d->Body.X.f -= bx;
				object_obj3d->Body.Y.f -= (bloke_height - by);
				object_obj3d->Body.Z.f -= bz;

				Three_Dee.StuffInBinaryTree(theChute,object_obj3d);

				object_obj3d->Body.X.f = pos_x;
				object_obj3d->Body.Y.f = pos_y;
				object_obj3d->Body.Z.f = pos_z;
			}
			else
				Three_Dee.StuffInBinaryTree(theChute,object_obj3d);
		}
	}
	else
	{
		if (object_obj3d->copySize < MOBILESIZE)						//RJS 26May00
			Trans_Obj.ControlDummyBloke(theItem);					//RJS 26Apr00
	}

	if (object_obj3d->realbz.f < 20000.)
	{
		D3DVECTOR	pos;
		UByte		theArea;

		pos.x = object_obj3d->Body.X.f;
		pos.y = object_obj3d->Body.Y.f + Trans_Obj.GetGroundLevel(theItem,theArea) - theItem->World.Y;
		pos.z = object_obj3d->Body.Z.f;

		Three_Dee.AddObject(BLKSHD,pos,ANGLES_0Deg,ANGLES_0Deg,ANGLES_0Deg);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BarageItemAnim
//Author		Robert Slater
//Date			Tue 24 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::BarageItemAnim(BarageAnimData* adptr)
{
	SLong	xpos, ypos, zpos;
	SWord	doit;

	if (!Three_Dee.IsPaused())									//RJS 27Feb98
	{
		if (adptr->countdown <= 0)
		{
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(object_obj3d->Shape);

			doit = Math_Lib.rnd();
			if (doit > 16384)									//RJS 07Dec98
			{
				WorldStuff*	worldptr = mobileitem::currworld;
				Coords3D	oldcoords = object_obj3d->ItemPtr->World;
				Coords3D	newcoords = oldcoords;
				SLong		sizex = sdptr->sx << 6;
				SLong		sizez = sdptr->sz << 6;

				if (doit < 32767)
				{
					newcoords.X += Math_Lib.rnd(sizex) - (sizex >> 1);
					newcoords.Z += Math_Lib.rnd(sizez) - (sizez >> 1);

					object_obj3d->ItemPtr->World = newcoords;

					Trans_Obj.LaunchDirtSmall((mobileitem*)object_obj3d->ItemPtr,*worldptr,false);//RJS 05Nov99
//DeadCode RJS 05Nov99 					Trans_Obj.LaunchDirtSmall((mobileitem*)object_obj3d->ItemPtr,*worldptr);

					object_obj3d->ItemPtr->World = oldcoords;
				}
				else
				{
					newcoords.X += Math_Lib.rnd(sizex>>1) - (sizex >> 2);
					newcoords.Z += Math_Lib.rnd(sizez>>1) - (sizez >> 2);
					newcoords.Y += Math_Lib.rnd(200);

					object_obj3d->ItemPtr->World = newcoords;

					Trans_Obj.LaunchGunDot((mobileitem*)object_obj3d->ItemPtr,*worldptr);

					object_obj3d->ItemPtr->World = oldcoords;
				}
			}

			adptr->countdown = 20 + Math_Lib.rnd(50);
		}
		else
			adptr->countdown -= Timer_Code.FRAMETIME;

		if (Math_Lib.rnd() > 63000)												//RJS 24Jun99
			_Miles.PlayDelayed(FIL_SFX_MACHINE_GUN_LOOP1,object_obj3d->ItemPtr);//RJS 05Nov99
//DeadCode DAW 25Jun99 		_Miles.PlayLooped(FIL_SFX_BATTLEFIELD_LOOP, (ItemBasePtr) object_obj3d->ItemPtr,128,8);//RJS 22Nov96
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FireballItemAnim
//Author		Robert Slater
//Date			Mon 7 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::FireballItemAnim(ExplodeAnimData* adptr)
{
//DeadCode RJS 05Jun97 	SimpleItemAnim((MinAnimData* )adptr);

//DeadCode RJS 26Nov98 	if (!Three_Dee.IsPaused())									//RJS 27Feb98
//DeadCode RJS 26Nov98 	{
//DeadCode RJS 26Nov98 		adptr->frameno++;
//DeadCode RJS 26Nov98 
//DeadCode RJS 26Nov98 		if (adptr->frameno > 3)
//DeadCode RJS 26Nov98 			adptr->frameno = 0;
//DeadCode RJS 26Nov98 
//DeadCode RJS 26Nov98 		_Miles.PlayLooped(FIL_SFX_SMALL_FIRE_LOOP, (ItemBasePtr) object_obj3d->ItemPtr);//RJS 09Jan97
//DeadCode RJS 26Nov98 
//DeadCode RJS 26Nov98 		*(animflags+EXPLODEFRAME) = adptr->frameno;
//DeadCode RJS 26Nov98 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BridgeItemAnim
//Author		Robert Slater
//Date			Wed 20 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::BridgeItemAnim(ExplodeAnimData* adptr)
{
//DeadCode RJS 05Jun97  	SimpleItemAnim((MinAnimData* )adptr);
//DeadCode RJS 19Jun97  
//DeadCode RJS 19Jun97  	FPMATRIX		smat;									 	//RJS 14May97
//DeadCode RJS 19Jun97  	FPMATRIX_PTR	stan_matrix = &smat;					 	//RJS 14May97
//DeadCode RJS 26Nov98  	ANGLES		thehdg;
//DeadCode RJS 26Nov98  
//DeadCode RJS 26Nov98  	thehdg = (Angles) adptr->frameno;
//DeadCode RJS 26Nov98  
//DeadCode RJS 19Jun97 	*stan_matrix=*Three_Dee.fpviewer_matrix;					//RJS 14May97
//DeadCode RJS 19Jun97  
//DeadCode RJS 19Jun97  	_matrix.generate2(thehdg,ANGLES_0Deg,ANGLES_0Deg,fpobject_matrix);//RJS 14May97
//DeadCode RJS 19Jun97  	_matrix.multiply(fpobject_matrix,stan_matrix);				//RJS 14May97
//DeadCode RJS 26Nov98  
//DeadCode RJS 26Nov98 	object_obj3d->AngH = thehdg;								//RJS 19Jun97
//DeadCode RJS 26Nov98 	object_obj3d->AngC = ANGLES_0Deg;							//RJS 19Jun97
//DeadCode RJS 26Nov98 	object_obj3d->AngR = ANGLES_0Deg;							//RJS 19Jun97

//DeadCode RJS 05Jun97  	SimpleItemAnim((MinAnimData* )adptr);
}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PolyPitItemAnim
//Author		Paul.   
//Date			Mon 15 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns									 
//
//------------------------------------------------------------------------------
void shape::PolyPitItemAnim(PolyPitAnimData* adptr)
{
 	AircraftAnim((AircraftAnimData *)adptr,TRUE);				//RJS 12Feb98
	ULong		timesec = View_Point->TimeOfDay() / 100;

	Manual_Pilot.ControlledAC2->fly.pInst->SetCockpitAnims(Manual_Pilot.ControlledAC2,(UByteP)adptr);
	Manual_Pilot.ControlledAC2->fly.pInst->UpdateCockpitTimers(View_Point->DrawFrameTime());

//	adptr->detailmask = 0;										//RJS 26Jan98
  //
//	adptr->detailmask |= (1 << COCK3D_DIALSROW1ON);				//RJS 26Jan98
//	adptr->detailmask |= (1 << COCK3D_DIALSROW2ON);				//RJS 26Jan98
//	adptr->detailmask |= (1 << COCK3D_DIALSROW3ON);				//RJS 26Jan98
//	adptr->detailmask |= (1 << COCK3D_DIALSROW4ON);				//RJS 26Jan98
//	adptr->detailmask |= (1 << COCK3D_PANELIMAPDSPLIT);				//RJS 26Jan98
//	adptr->detailmask |= (1 << COCK3D_PANELGLASSFRONT);			//RJS 25Mar98

//DEAD	if (View_Point->PolyPitEnabled())							//PD 11Dec96
//DEAD		POLYGON.SetCrossProduct(FALSE);							//PD 11Dec96

	adptr->acclocksec = (timesec<<8)/60;	//60secs == 256	(1 min)//RJS 05Nov99
	timesec /= 60;							//mins
	adptr->acclockmin = (timesec<<8)/60;	//60mins == 256	(1 hr)
	timesec /= 60;							//hrs
	adptr->acclockhour = (timesec<<8)/12;	//12hrs == 256	(.5 day)
	//so each hour is worth 21.3 units on the clock (out of 256)
	//hour units = acclockhour + (21.3 * acclockmin)/256
	adptr->acclockhour += ((adptr->acclockmin * 213)/2560);		//RJS 05Nov99

//DeadCode RJS 24Nov99	adptr->acwingspam = 255- ((WingSpan * 255)/5791);	// 0 feet to 190 feet

	Float	ydsrange = RequiredRange;
	ydsrange *= 0.0984;

//DeadCode RJS 24Nov99	adptr->acgunrange = (SLong(ydsrange) * 255)/5000;		// 0 to 5000 yds

	UByte	gunswitch = 0;
	UByte	rocketswitch = 0;
	SLong	launcher = Manual_Pilot.ControlledAC2->weap.weapontype & LT_MASK;

	if (launcher != LT_BULLET)
	{
		gunswitch = 1;
		if (launcher != LT_ROCKET)
			rocketswitch = 1;
	}

	adptr->gunotherswitch = gunswitch;
	adptr->bombrocketswitch = rocketswitch;

	if (Manual_Pilot.ControlledAC2->weap.UseIntFuel)
		adptr->fuelswitch = 1;
	else
		adptr->fuelswitch = 0;

	if (_Replay.Record)
		adptr->lightguncamera = 1;
	else
		adptr->lightguncamera = 0;

	adptr->acgyrocompassflip = -adptr->acgyrocompass;			//RJS 20Mar00

	if (radarTimer > -1)										//RJS 07Apr99
	{
		radarTimer -= View_Point->DrawFrameTime();
		if (radarTimer < 0)
		{
			radarTimer = 0;
			adptr->lightgunsight = 1;
		}
	}
	else
		adptr->lightgunsight = 0;

	if (adptr->ENGINELEFT >= BS_DAMLV2)							//RJS 22Nov99
		adptr->lightfire = 1;
	else
		adptr->lightfire = 0;

	//stall light (high revs thing from Craig...)

	//gear ... don't need
//	if (adptr->acleglowerl == 0)
//		adptr->lightlanding = 1;
//	else
//		adptr->lightlanding = 0;

//DeadCode RJS 24Nov99	if (Manual_Pilot.ControlledAC2->weap.UseIntFuel)			//RJS 14Apr99
//DeadCode RJS 24Nov99		adptr->acfuelext = 0;									//RJS 14Apr99
//DeadCode RJS 24Nov99	else														//RJS 14Apr99
//DeadCode RJS 24Nov99		adptr->acfuelext = 1;									//RJS 14Apr99

// Toggle between two frames of anim...
// (0 - 255) (0-127 = off, 128-255 = on)
	if (adptr->reargunnershooting)
		adptr->reargunner += 128;

	adptr->canopyclock = adptr->accanopy;

	adptr->detailmask = Three_Dee.cockpitPrefs;					//RJS 24Mar00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AircraftAnim
//Author		Paul.   
//Date			Wed 27 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::AircraftAnim(AircraftAnimData* adptr,Bool pitset)
{
	if (	object_obj3d->ItemPtr
		&&	(object_obj3d->ItemPtr->Status.size == AIRSTRUCSIZE)	)
	{
		AirStrucPtr	ac = (AirStrucPtr)object_obj3d->ItemPtr;
		ac->fly.pModel->Animations(ac);
		int vel = 0;
		if(ac->fly.pModel->GearTouched)
			vel = int(fastMath.DoubleToULong(double(ac->fly.pModel->Speed * 10000.0)));

		int delta = (View_Point->DrawFrameTime() * vel) >> 13;

		if (delta > 160)			//220 degrees
			delta = 160;

		if(adptr->aclegsuspr)
			adptr->acwheelr -= delta;
		if(adptr->aclegsuspl)
			adptr->acwheell -= delta;
		if(adptr->aclegsuspb)
			adptr->acwheelb -= 2 * delta;

		if (View_Point->DrawFrameTime() && !View_Point->Accel())		//RJS 12Sep00
		{
			if (adptr->gunshooting)										//RJS 25Aug00
				adptr->muzzleflash = !adptr->muzzleflash;				//RJS 25Aug00
			else														//RJS 25Aug00
				adptr->muzzleflash = 0;									//RJS 25Aug00
																		//RJS 25Aug00
			if (adptr->cannonshooting)									//RJS 25Aug00
				adptr->cannonflash = !adptr->cannonflash;				//RJS 25Aug00
			else														//RJS 25Aug00
				adptr->cannonflash = 0;									//RJS 25Aug00
		}
		else
		{
			adptr->muzzleflash = 0;
			adptr->cannonflash = 0;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcTrailDeltas
//Author		Robert Slater
//Date			Thu 18 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE JON 4/12/00 UWord	shape::CalcTrailDeltas(	UByteP	thisdrawnobj,
//DEADCODE JON 4/12/00 								UByteP	lastdrawnobj,
//DEADCODE JON 4/12/00 								UWord	radius,
//DEADCODE JON 4/12/00 								SWord	&xoff, SWord &yoff)
//DEADCODE JON 4/12/00 {
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 	DoPointStruc dopoint0,dopoint2;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 	Obj3DPtr	 objold = (Obj3DPtr) lastdrawnobj;			//RJS 07Feb00
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 	Obj3DPtr	 objnew = (Obj3DPtr) thisdrawnobj;			//RJS 07Feb00
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 	SLong		valid = 0;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 	SWord		angleofcyl = 0;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 	SWord		sin_ang, cos_ang;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 	xoff = 0;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 	yoff = 0;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 	if (objold && objnew)
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 	{
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 		Float	opposite, adjacent;								//RJS 03Dec98
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 		SWord	angleofcyl;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 		dopoint0.bodyx.f = objold->Body.X.f;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 		dopoint0.bodyy.f = objold->Body.Y.f;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 		dopoint0.bodyz.f = objold->Body.Z.f;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 		dopoint2.bodyx.f = objnew->Body.X.f;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 		dopoint2.bodyy.f = objnew->Body.Y.f;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 		dopoint2.bodyz.f = objnew->Body.Z.f;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 		if (	(dopoint0.bodyz.f > 0)								
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00  			||	(dopoint2.bodyz.f > 0)	)							
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00  		{
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 			if (	(dopoint0.bodyz.f < 1)							
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 				||	(dopoint2.bodyz.f < 1)	)
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 			{
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 //deadcode		 		current_screen->zclipline(dopoint0,dopoint2);
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 	 	
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 				objold->Body.X.f = dopoint0.bodyx.f;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 				objold->Body.Y.f = dopoint0.bodyy.f;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 				objold->Body.Z.f = dopoint0.bodyz.f;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 			}
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 				
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 			objnew->Body.X.f = dopoint2.bodyx.f;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 			objnew->Body.Y.f = dopoint2.bodyy.f;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 			objnew->Body.Z.f = dopoint2.bodyz.f;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 			R3DVALUE screenx0,screeny0,screenz0,screenx2,screeny2,screenz2;//RJS 07Feb00
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 			g_lpLib3d->BodyToScreen(dopoint0,screenx0,screeny0,screenz0);//RJS 07Feb00
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 			g_lpLib3d->BodyToScreen(dopoint2,screenx2,screeny2,screenz2);//RJS 07Feb00
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 			opposite = screeny0 - screeny2;		//RJS 03Dec98
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00  			adjacent = screenx2 - screenx0;	//RJS 03Dec98
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 //DeadCode DAW 07Apr99 			valid = 1;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 			if (opposite || adjacent)							//RJS 03Dec98
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 			{
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 				Float	res = 10430.37835047*FPATan(adjacent,opposite);
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 //DeadCode RJS 03Dec98 				angleofcyl = Math_Lib.HighArcTan(adjacent,opposite);
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00  				angleofcyl = SWord(res);
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00  				angleofcyl -= ANGLES_90Deg;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 				Math_Lib.high_sin_cos((Angles) angleofcyl,sin_ang,cos_ang);		//PD 13Nov97
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 				xoff = (sin_ang * radius) / ANGLES_FRACT;				
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00   				yoff = (cos_ang * radius) / ANGLES_FRACT;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 				valid = 1;										//DAW 07Apr99
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 			}
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 //DeadCode RJS 03Dec98 			else
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 //DeadCode RJS 03Dec98 			{
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 //DeadCode RJS 03Dec98 				xoff = radius;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 //DeadCode RJS 03Dec98 				yoff = 0;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 //DeadCode RJS 03Dec98 
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 //DeadCode RJS 03Dec98 				if (adjacent)
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 //DeadCode RJS 03Dec98 				{
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 //DeadCode RJS 03Dec98 					xoff = 0;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 //DeadCode RJS 03Dec98 					yoff = radius;
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 //DeadCode RJS 03Dec98 				}
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 //DeadCode RJS 03Dec98 			}
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 		}
//DEADCODE JON 4/12/00 //Old_Code RJS 08Feb00 	}
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	DoPointStruc dopoint0,dopoint2;
//DEADCODE JON 4/12/00 	Obj3DPtr	 objold = (Obj3DPtr) lastdrawnobj;
//DEADCODE JON 4/12/00 	Obj3DPtr	 objnew = (Obj3DPtr) thisdrawnobj;
//DEADCODE JON 4/12/00 	SLong		valid = 0;
//DEADCODE JON 4/12/00 	SWord		angleofcyl = 0;
//DEADCODE JON 4/12/00 	SWord		sin_ang, cos_ang;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	xoff = 0;
//DEADCODE JON 4/12/00 	yoff = 0;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	if (objold && objnew)
//DEADCODE JON 4/12/00 	{
//DEADCODE JON 4/12/00 		Float	opposite, adjacent;
//DEADCODE JON 4/12/00 		SWord	angleofcyl;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		dopoint0.bodyx.f = objold->Body.X.f;
//DEADCODE JON 4/12/00 		dopoint0.bodyy.f = objold->Body.Y.f;
//DEADCODE JON 4/12/00 		dopoint0.bodyz.f = objold->Body.Z.f;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		dopoint2.bodyx.f = objnew->Body.X.f;
//DEADCODE JON 4/12/00 		dopoint2.bodyy.f = objnew->Body.Y.f;
//DEADCODE JON 4/12/00 		dopoint2.bodyz.f = objnew->Body.Z.f;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		R3DVALUE screenx0,screeny0,screenz0,screenx2,screeny2,screenz2;
//DEADCODE JON 4/12/00 		g_lpLib3d->BodyToScreen(dopoint0,screenx0,screeny0,screenz0);
//DEADCODE JON 4/12/00 		g_lpLib3d->BodyToScreen(dopoint2,screenx2,screeny2,screenz2);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		if ((screenz0 > 1.0) || (screenz2 > 1.0))
//DEADCODE JON 4/12/00 		{
//DEADCODE JON 4/12/00 			opposite = screeny0 - screeny2;
//DEADCODE JON 4/12/00  			adjacent = screenx2 - screenx0;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 			if (opposite || adjacent)
//DEADCODE JON 4/12/00 			{
//DEADCODE JON 4/12/00 				Float	res = 10430.37835047*FPATan(adjacent,opposite);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00  				angleofcyl = SWord(res);
//DEADCODE JON 4/12/00  				angleofcyl -= ANGLES_90Deg;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 				Math_Lib.high_sin_cos((Angles) angleofcyl,sin_ang,cos_ang);
//DEADCODE JON 4/12/00 				xoff = (sin_ang * radius) / ANGLES_FRACT;				
//DEADCODE JON 4/12/00   				yoff = (cos_ang * radius) / ANGLES_FRACT;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 				valid = 1;
//DEADCODE JON 4/12/00 			}
//DEADCODE JON 4/12/00 		}
//DEADCODE JON 4/12/00 	}
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	return(valid);
//DEADCODE JON 4/12/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleSmokePnt
//Author		Robert Slater
//Date			Tue 16 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::SampleSmokePnt(	UByteP		smkinfo,
								SWord		&listindex,
								UByteP		instr_ptr,
								SWord		&Stores,
								UWord		LifeTime	)
{
	Bool	validpoint = TRUE;

	if (SamplePntTime)
	{
		DOLAUNCHER_PTR	ptr = (DOLAUNCHER_PTR) instr_ptr;
		TrailRecord*	trailptr = &traillist[listindex];
		SmokeTypeP		smkptr = (SmokeTypeP) smkinfo;
		SLong			xcoord = ptr->posx;
		SLong			ycoord = ptr->posy;
		SLong			zcoord = ptr->posz;
		SLong			lifetime;
		SLong			wx, wy, wz;
		SWord			index = listindex;
		MATRIX  		omat;										
		MATRIX_PTR		obj_matrix = &omat;							
		UWord			scaleback;

		if (!LifeTime)											//RJS 09Apr98
			LifeTime = smkptr->LifeTime;						//RJS 09Apr98

//		if (Three_Dee.IsPaused())								//RJS 27Feb98
//			SamplePntTime = FALSE;

		trailptr->SampleTime -= View_Point->DrawFrameTime();			//RJS 08Jan98
		if (trailptr->SampleTime < 0)							//RJS 08Jan98
			trailptr->SampleTime = smkptr->SampleTime;			//RJS 02Feb98
		else													//RJS 02Feb98
			validpoint = FALSE;									//RJS 02Feb98

		// -1 is infinite....
		if (Stores != -1)
		{
			Stores-=Timer_Code.FRAMETIME;						//RJS 25Mar99

			if (Stores < 0)
				Stores = 0;
		}

		if (Stores)
		{
			lifetime = LifeTime;								//RJS 08Dec97

//			if (trailptr->lifetime && (lifetime > 500))
//				lifetime = trailptr->lifetime;

 			if (trailptr->nextlist)
 			{
 				Coords3DList*	nextptr = traillist[trailptr->nextlist].thelist;
 				if (nextptr)
 				{
 					wx = nextptr->trailpoint.gx;
 					wy = nextptr->trailpoint.gy;
 					wz = nextptr->trailpoint.gz;

 					SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,lifetime,smkptr->FadeTime);
 					lifetime = trailptr->lifetime;
 				}

 				trailptr->nextlist = 0;
 			}

			// Every frame....

 			wx = xcoord << shapescale;
 			wy = ycoord << shapescale;
 			wz = zcoord << shapescale;

			_matrix.generate2(	object_obj3d->AngH,
								object_obj3d->AngC,
								object_obj3d->AngR,
								obj_matrix);

			scaleback = _matrix.transform(obj_matrix,wx,wy,wz);
			wx >>= (16-scaleback);
			wy >>= (16-scaleback);
			wz >>= (16-scaleback);

			wx += trailptr->lastwx;
			wy += trailptr->lastwy;
			wz += trailptr->lastwz;

			AddNewVapourPoint(trailptr,wx,wy,wz,lifetime,smkptr->FadeTime);

			if (trailptr->nopoints > smkptr->MaxPoints)
			{
				switch (smkptr->DeadAction)
				{
				case DEADSMK_DEFAULT:
	 				trailptr->bitshift = 0;
//DEADCODE DAW 23/04/99 				listindex = 0;				//RJS 12Apr99
//DEADCODE DAW 12/04/99 					listindex = -index;
					DetatchVapourStream(index,LIFETIME_VAPOUR);
					listindex = NextFreeVapour(0,0,0,smkinfo);										//RJS 23Apr99
					if (listindex)																	//RJS 23Apr99
						AddNewVapourPoint(&traillist[listindex],wx,wy,wz,lifetime,smkptr->FadeTime);//RJS 23Apr99
					break;
				case DEADSMK_SMOKECLOUD:
					AddSmokeCloud(trailptr,smkptr->CloudShape,index);
					break;
				}
			}
		}
		else
		{
			listindex = 0;
			DetatchVapourStream(index,LIFETIME_VAPOUR);	//RJS 09Apr98
		}
	}

	return(validpoint);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawSmokeTrail
//Author		Robert Slater
//Date			Tue 16 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::DrawSmokeTrail(	SWord		index,
								UByteP		smkinfo,
								ULong		LifeTime,
								Bool		valid,
								bool		drawIt	)
{
	SLong	totpoints = 0;
	if (index)
	{
		if (index < 0)											
			index = -index;

		if (index > MAX_VAPOURS)
			_Error.EmitSysErr(__FILE__":(DOSMKTRAIL)    Shouldn't be this : %d\n",index);

		TrailRecordPtr	TrailPtr = &traillist[index];			
																
		if (smkinfo)											
			TrailPtr->SmkDescPtr = smkinfo;						
		else													
		{
			smkinfo = TrailPtr->SmkDescPtr;						
			LifeTime = TrailPtr->lifetime;						
		}

		if (smkinfo)
		{
			SmokeTypeP		ptr = (SmokeTypeP) smkinfo;
			Coords3DList*	apoint;
			Coords3DList*	*lastpointptr;						
			Coords3DList*	nextpoint;							
			Coords3DList*	lastpoint;							
//DeadCode RJS 20Oct00 			SLong			nocyls = 0;
			SLong			lifegone, lifeleft;
			SWord			grow2time = ptr->Growth;
			UWord			startradius = ptr->Radius;
			SWord			radius;
			SWord			radiusinc;
 			SByte			frameno;
			ShapeNum		trailshape = (ShapeNum) ptr->Shape;
			SLong			timesincebirth;
			SLong			totcount = 0;
			SWord			uy,vy;
			SWord			hdist;
			SLong			dragy;
			SWord			Acceleration;
			SLong			reallife;
			SLong			frametime;
			SLong			currtime = View_Point->TotalDrawFrameTime();
			SLong			wvelx,wvely,wvelz;
			VapAnimDat		AnimDat;
			VapAnimDatPtr	AnimDataPtr;
			double			centrex, centrey, centrez;
			double			maxx,maxy,maxz;
//DeadCode RJS 24Oct00 			SLong			minx,miny,minz;
			Coords3D		worldpos;
			SLong			galaxyradius;
			UByteP			thisdrawnobj;

#ifdef	_SMOKETRAILDEBUG_
	TrailPtr->theItemPtr = pTrailItm;
#endif

			maxx = 0;
			maxy = 0;
			maxz = 0;

//DeadCode RJS 24Oct00 			minx = 0x7FFFFFFF;
//DeadCode RJS 24Oct00 			miny = 0x7FFFFFFF;
//DeadCode RJS 24Oct00 			minz = 0x7FFFFFFF;

			centrex = 0;
			centrey = 0;
			centrez = 0;

			//If it's a static transient, we want real time...

			frametime = currtime - TrailPtr->currTime;

 			lastpointptr = &TrailPtr->thelist;

			lastpoint = NULL;
			apoint = TrailPtr->thelist;			
 			while (apoint)
 			{
 				nextpoint = apoint->next;
				lifeleft = reallife = apoint->lifeleft;
 				if (!Three_Dee.IsPaused())			   
 				{
					if (apoint->KillMe)				   
 					{
						// Add to dead list...
						apoint->next = TrailPtr->FakePointPtr;
						TrailPtr->FakePointPtr = apoint;
 
#ifdef	_SMOKETRAILDEBUG_
	if (nextpoint)	nextpoint->prevkilled = true;
	if (lastpoint)	lastpoint->nextkilled = true;
#endif

#ifdef	TRAILREPORT
	::AfxTrace("DSM: %x %x %x\n",int(apoint),int(&apoint->next),int(lastpointptr));
#endif
 						TrailPtr->nopoints--;
 						*lastpointptr = nextpoint;

						lifeleft = 0;
 					}
					else
					{
						reallife -= frametime;
						if (reallife <= 0)	  
							reallife = 0;	  
											  
						apoint->lifeleft = reallife;
					}
				}

 				if (!apoint->KillMe)
 				{
					if (!apoint->lifeleft)	apoint->KillMe = 1;
					if (apoint->LifeTime)					   
					{
						lifegone = apoint->LifeTime - lifeleft;
						if (lifegone >= 0)
							radius = startradius + ((startradius*lifegone)/grow2time);
						else
						{
							// For some reason lifeleft > total LifeTime,
							// so set lifeleft to LifeTime...

							apoint->lifeleft = apoint->LifeTime;
							lifegone = 0;						
							radius = startradius;				
						}										

// Add wind drift...
						apoint->isFirst = 0;
						if (totcount)
						{
							if (totcount == 1)
								apoint->isFirst = smokeFirstIsSpecial;//RJS 29Mar00
//DeadCode RJS 12Sep00  							else
//DeadCode RJS 12Sep00  							{
//DeadCode RJS 12Sep00  								if (MissManCampSky().GetWind(apoint->trailpoint.gy,wvelx,wvely,wvelz))
//DeadCode RJS 12Sep00  								{
//DeadCode RJS 12Sep00  									SLong	distx = (wvelx * frametime)/10000;
//DeadCode RJS 12Sep00  									SLong	distz = (wvelz * frametime)/10000;
//DeadCode RJS 12Sep00  
//DeadCode RJS 12Sep00  									apoint->trailpoint.gx += distx;
//DeadCode RJS 12Sep00  									apoint->trailpoint.gz += distz;
//DeadCode RJS 12Sep00  								}
//DeadCode RJS 12Sep00  							}
						}

						apoint->radius = radius;
					}

					double	fgx = double(apoint->trailpoint.gx);
					double	fgy = double(apoint->trailpoint.gy);
					double	fgz = double(apoint->trailpoint.gz);

					centrex += fgx;
					centrey += fgy;
					centrez += fgz;

					fgx *= fgx;
					fgy *= fgy;
					fgz *= fgz;
					if (fgx > maxx)
						maxx = fgx;

					if (fgy > maxy)
						maxy = fgy;

					if (fgz > maxz)
						maxz = fgz;

 					lastpointptr = &apoint->next;

					totcount++;
 				}
 
 				lastpoint = apoint;
 				apoint = nextpoint;
 			}

			apoint = TrailPtr->thelist;
			if (apoint && !valid && !TrailPtr->transient)
				apoint->KillMe = 1;

			totpoints = TrailPtr->nopoints;

 			if (View_Point->DrawFrameTime())
				TrailPtr->currTime = currtime;

			if (totcount && drawIt)										//RJS 24Oct00
			{
				double	htot = 1./double(totcount);

				centrex *= htot;
				centrey *= htot;
				centrez *= htot;

//DeadCode RJS 24Oct00 				minx=minx<0?-minx:minx;
//DeadCode RJS 24Oct00 				miny=miny<0?-miny:miny;
//DeadCode RJS 24Oct00 				minz=minz<0?-minz:minz;
//DeadCode RJS 24Oct00 
//DeadCode RJS 24Oct00 				if (minx > maxx)	maxx = minx;
//DeadCode RJS 24Oct00 				if (miny > maxy)	maxy = miny;
//DeadCode RJS 24Oct00 				if (minz > maxz)	maxz = minz;

				maxx -= centrex*centrex;
				maxy -= centrey*centrey;
				maxz -= centrez*centrez;

				fastMath.FloatToInt(&worldpos.X,float(centrex));
				fastMath.FloatToInt(&worldpos.Y,float(centrey));
				fastMath.FloatToInt(&worldpos.Z,float(centrez));

				galaxyradius = SLong(fastMath.DoubleToULong(double(fastMath.FastSqrt(float(maxx+maxy+maxz)))));

				Three_Dee.AddNewVapourObject(	trailshape,
												apoint,			//1st point
												thisdrawnobj,
												worldpos,
												galaxyradius,
												pTrailItm	);			//RJS 12Sep00

				if (thisdrawnobj)
				{
					AnimDat.depth = ptr->Depth;
					AnimDat.drawit = 1;

					AnimDataPtr = (VapAnimDatPtr) &((Obj3DPtr)thisdrawnobj)->AngR;
					*AnimDataPtr = AnimDat;
				}
			}
		}
	}

	return (totpoints);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateVapourCoords
//Author		Robert Slater
//Date			Thu 29 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::UpdateVapourCoords(itemptr	itm,animptr&	aptr, bool drawIt)
{
	ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(itm->shape);//RJS 23Apr99
	int					wpnum, index, oldindex;
	WeapAnimData*		weapon;
	MoveGunAnimData*	adptr = (MoveGunAnimData*) aptr;
	SLong				wx = itm->World.X;
	SLong				wy = itm->World.Y;
	SLong				wz = itm->World.Z;
	int					weapcnt = 1;
	UByte				instsize = sizeof(DOLAUNCHER) + 1;
	DOLAUNCHER_PTR		lptr;
	UByteP				instr_ptr;
	UByteP				base_ptr;
	UWord				instruction;
	SmokeTypeP			smkptr = NULL;
	UWord				lifetime=0;
	ULong				reallifetime;
	SByte				TType;
	Bool				validpoint = TRUE;						//RJS 30Nov98
	SLong				driftx,drifty,driftz;					//RJS 10Mar98
//DeadCode RJS 20Oct00 	Bool				justlanded=FALSE;								//RJS 11Mar98
	UByte				weaplaunchertype=0;
	SLong				nopoints;
	bool				validForContrails;
//DeadCode RJS 27Oct00 	bool				explodeMe = false;

	bool				launchBlobInstead = false;

	if (	(Save_Data.detail_3d[DETAIL3D_TRANSSMOKE] != 0)				//RJS 6Nov00
		&&	(itm->Status.size >= MOBILESIZE)
		&&	(MobileItemPtr(itm)->vel_ < 70000)	)
		launchBlobInstead = true;

	if (sdptr->AnimDataSize == AIRCRAFTANIM)
		validForContrails = true;
	else
		validForContrails = false;

	//Remove all trails at altitude, because we have no wind.
//DeadCode RJS 20Dec99 	Bool				toohigh;
//DeadCode RJS 20Dec99 								
//DeadCode RJS 20Dec99 	if (itm->World.Y >= FT_34000)								//RJS 27Jun99	//CSB 01/07/99	
//DeadCode RJS 20Dec99 		toohigh = TRUE;
//DeadCode RJS 20Dec99 	else
//DeadCode RJS 20Dec99 		toohigh = FALSE;

	switch (SHAPESTUFF.GetShapeScale(sdptr))				
 	{														
 		case SHP_1CM:										
 			shapescale = 0;									
 			break;											
 		case SHP_4CM:										
 			shapescale = 2;									
 			break;											
 		case SHP_16CM:										
 			shapescale = 4;									
 			break;											
 	}			

	pTrailItm = itm;//RJS 02Sep98
	weapcnt = adptr->nolaunchers;								//RJS 09Apr98

//	Math_Lib.high_sin_cos((ANGLES )((mobileitem*)itm)->hdg,v_sin_ang,v_cos_ang);

	base_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

	weapon = &adptr->weaponlaunchers[0];							//RJS 09Dec99
	for (wpnum = 0; wpnum < weapcnt; wpnum++)
	{
		oldindex = 0;
		if (weapon && ((weapon->LauncherType & LT_MASK)==LT_SMKTRAILS))//RJS 09Dec99
		{
			instr_ptr = base_ptr + (instsize * weapon->launcherIndex);//RJS 09Dec99
			instr_ptr++;

			lptr = (DOLAUNCHER_PTR) instr_ptr;
			if (	!lptr->damageflag
				|| (aptr[lptr->damageflag] < lptr->damthresh)	)
			{
				TType = lptr->trailtype;
				if (TType < 0)
				{
					if (TType == -1)
					{
						if (	(weapon->LauncherType == LT_FUEL)
							||	(weapon->LauncherType == LT_INTFUEL)	)	//RJS 10May99
						{
							TType = TRAIL_VAPOUR;
							smkptr = (SmokeTypeP) &SmokeTrlList[TRAIL_VAPOUR];
							lifetime = smkptr->LifeTime;

							weaplaunchertype = weapon->LauncherType;//MS 30Nov98
						}
					}
					else
					{
						// Generic one for engines...
						if (lptr->lnchrtype == LT_ENGINE)		//MS 30Nov98
						{
							UByte	dolaunch = LT_ENGINE;

//DeadCode RJS 29Aug00 							if (aptr[lptr->damageflag] < BS_DAMLV2)
//DeadCode RJS 29Aug00 							{
//DeadCode RJS 29Aug00 								if (validForContrails)					//RJS 7Jun00
//DeadCode RJS 29Aug00 								{
//DeadCode RJS 29Aug00 									dolaunch = LT_CONTRAIL;
//DeadCode RJS 29Aug00 									TType = TRAIL_CONTRAIL;
//DeadCode RJS 29Aug00 									smkptr = (SmokeTypeP) &SmokeTrlList[TType];
//DeadCode RJS 29Aug00 									lifetime = smkptr->LifeTime;
//DeadCode RJS 29Aug00 								}
//DeadCode RJS 29Aug00 							}
//DeadCode RJS 29Aug00 							else
//DeadCode RJS 29Aug00 							{
//DeadCode RJS 29Aug00 								dolaunch = LT_FUEL;
//DeadCode RJS 29Aug00 								TType = TRAIL_ENGINEPLUME;
//DeadCode RJS 29Aug00 								smkptr = (SmokeTypeP) &SmokeTrlList[TType];
//DeadCode RJS 29Aug00 								lifetime = smkptr->LifeTime;
//DeadCode RJS 29Aug00 							}
//DeadCode RJS 29Aug00 					
//DeadCode RJS 29Aug00 							index = weapon->hdg;
//DeadCode RJS 29Aug00 							if (index > 0)
//DeadCode RJS 29Aug00 							{
//DeadCode RJS 29Aug00 								if (traillist[index].SmkDescPtr != (UByteP)smkptr)
//DeadCode RJS 29Aug00 								{
//DeadCode RJS 29Aug00 									SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
//DeadCode RJS 29Aug00 									weapon->hdg = 0;
//DeadCode RJS 29Aug00 								}
//DeadCode RJS 29Aug00 								weapon->LauncherType = LT_ENGINE;
//DeadCode RJS 29Aug00 							}
//DeadCode RJS 29Aug00 							else
//DeadCode RJS 29Aug00 								weapon->LauncherType = LT_ENGINE;
//DeadCode RJS 29Aug00 
//DeadCode RJS 29Aug00 							if (weapon->LauncherType != dolaunch)
//DeadCode RJS 29Aug00 							{
//DeadCode RJS 29Aug00 								if (dolaunch != LT_CONTRAIL)
//DeadCode RJS 29Aug00 								{
//DeadCode RJS 29Aug00 									weapon->LauncherType = dolaunch;
//DeadCode RJS 29Aug00 									oldindex = Trans_Obj.LaunchVapourStream((UByteP)weapon,(ShapeNum)object_obj3d->Shape);//RJS 09Apr98
//DeadCode RJS 29Aug00 								}
//DeadCode RJS 29Aug00 								weapon->pitch = -1;
//DeadCode RJS 29Aug00 							}
//DeadCode RJS 29Aug00 
//DeadCode RJS 29Aug00 							 weaplaunchertype = dolaunch;

							if (weapon->hdg > 0)						//RJS 29Aug00
							{
								dolaunch = LT_FUEL;
 								TType = TRAIL_ENGINEPLUME;
 								smkptr = (SmokeTypeP) &SmokeTrlList[TType];
 								lifetime = smkptr->LifeTime;
							}

							weapon->LauncherType = weaplaunchertype = dolaunch;
						}
						else
						{
// This is a generic, inherited trail...make sure we sample no extra points!
							smkptr = NULL;
							weaplaunchertype = LT_CONTACT;
						}
					}											//MS 30Nov98
				}
				else
				{
					smkptr = (SmokeTypeP) &SmokeTrlList[TType];	//RJS 09Apr98
					lifetime = smkptr->LifeTime;

					weaplaunchertype = weapon->LauncherType;	//MS 30Nov98
				}

				if (TType != -1)
				{
// min sample distance is 1024 cm per frame, which is 256m/s
//DeadCode RJS 6Nov00 					SLong	mindist = (51200 * Timer_Code.FRAMETIME)/100;
//DeadCode RJS 6Nov00 					SLong	distscale;

					validpoint = TRUE;
					driftx = 0;										//RJS 10Mar98
					drifty = 0;										//RJS 10Mar98
					driftz = 0;										//RJS 10Mar98

					index = weapon->hdg;	//RJS 23Apr99

					switch (weaplaunchertype)					//RJS 29Nov98
					{
						case LT_CONTRAIL:
						{
							if (MissManCampSky().Contrails((AirStrucPtr) itm, reallifetime))
							{
//Cannot implement different lifetime until we extend
//smoke trail coordinate type to include this master lifetime
								lifetime = reallifetime;

								oldindex = Trans_Obj.LaunchVapourStream((UByteP)weapon,(ShapeNum)object_obj3d->Shape);//RJS 09Apr98
								index = weapon->hdg;					//RJS 12Jan98
								if (index > 0)
								{
									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);	//RJS 02Feb98
								}
							}
							else
							{
								index = weapon->hdg;				//RJS 12Jan98
								if (index > 0)
								{
									SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);//RJS 09Apr98
									weapon->hdg = 0;				//RJS 12Jan98
								}
							}
							break;
						}
						case LT_FUNNEL:							//RJS 06Jun99
						{
							index = weapon->hdg;
							if (index > 0)
							{
//Not really a trail, but samples points...and draws them seperately.

								traillist[index].lastwx = wx;
								traillist[index].lastwy = wy;
								traillist[index].lastwz = wz;

								validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);
								DrawTempBlobTrail(index,(UByteP)smkptr,lifetime,validpoint);

								index = 0;
							}
							break;
						}
						case LT_INTFUEL:
						case LT_VAPOUR:
						case LT_FUEL:
						{
							index = weapon->hdg;					//RJS 12Jan98
							if (index > 0)
							{
								if (	(TType == TRAIL_ENGINEPLUME)
									&&	launchBlobInstead	)
								{
									traillist[index].SampleTime -= View_Point->DrawFrameTime();
									if (traillist[index].SampleTime < 0)
									{
										traillist[index].SampleTime = 33;

										Coords3D	pos;

										TransformSmokePoint(instr_ptr,pos);	//RJS 6Nov00

										pos.X += itm->World.X;
										pos.Y += itm->World.Y;
										pos.Z += itm->World.Z;

										Trans_Obj.LaunchSmokePuff2((mobileitem*)itm,pos,SBANKC,0,0,0,0,lifetime,lifetime,*mobileitem::currworld);
									}
								}
								else
								{
									if (traillist[index].thelist)
									{
										float	dx,dy,dz;					//RJS 6Nov00

										dx = wx - traillist[index].lastwx;
										dy = wy - traillist[index].lastwy;
										dz = wz - traillist[index].lastwz;

										if ((dx*dx+dy*dy+dz*dz) >= MIN_SAMP_DIST_SQUARED)			//RJS 6Nov00
										{
											traillist[index].lastwx = wx;
											traillist[index].lastwy = wy;
											traillist[index].lastwz = wz;
											traillist[index].nextlist = oldindex;

											validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);	//RJS 02Feb98
										}
										else
										{
											if (SamplePntTime)
											{
												SLong	oldx, oldy, oldz;

												oldx = traillist[index].lastwx;
												oldy = traillist[index].lastwy;
												oldz = traillist[index].lastwz;

												traillist[index].lastwx = wx;
												traillist[index].lastwy = wy;
												traillist[index].lastwz = wz;

												SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);
												validpoint = FALSE;

												traillist[index].lastwx = oldx;
												traillist[index].lastwy = oldy;
												traillist[index].lastwz = oldz;
											}
										}
									}
									else
									{
										traillist[index].lastwx = wx;
										traillist[index].lastwy = wy;
										traillist[index].lastwz = wz;
										traillist[index].nextlist = oldindex;

										validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);	//RJS 02Feb98
									}
								}
							}
							break;
						}
						case LT_DUST:
						{
							index = weapon->hdg;					//RJS 12Jan98
							if (index > 0)
							{
								traillist[index].lastwx = wx;
								traillist[index].lastwy = Land_Scape.GetGroundLevel(itm);
								traillist[index].lastwz = wz;
								traillist[index].nextlist = oldindex;

								validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);	//RJS 2Feb98
							}
							break;
						}
						case LT_MUDDY:
						{
							index = weapon->hdg;					//RJS 12Jan98
							if (index > 0)
							{
								if (traillist[index].thelist)
								{
									SLong	dist;
									SLong	dx,dy,dz;
									SLong	ox,oy,oz;

									ox = traillist[index].lastwx;
									oy = traillist[index].lastwy;
									oz = traillist[index].lastwz;

									dx = wx - ox;
									dy = wy - oy;
									dz = wz - oz;

									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);

									dist = Math_Lib.distance3d(dx,dy,dz);
									if (dist < 100)
									{
										if (SamplePntTime)
										{
											validpoint = FALSE;
											if (dist == 0)
												drifty = -View_Point->DrawFrameTime();
										}

										traillist[index].lastwx = ox;
										traillist[index].lastwy = oy;
										traillist[index].lastwz = oz;
									}
								}
								else
								{
									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);//RJS 25Nov98
								}
							}
							break;
						}
					}

					nopoints = DrawSmokeTrail(index,(UByteP)smkptr,lifetime,validpoint,drawIt);	//RJS 24Oct00
					if (nopoints && validForContrails)
					{
						AircraftAnimData*	adptr = (AircraftAnimData*) aptr;
						adptr->hassmoked = 1;
					}
				}
			}
			else
			{
// Kill this trail (if it is one!)...
				if (weapon->hdg > 0)										//RJS 7Jun00
				{
					SHAPE.DetatchVapourStream(weapon->hdg,LIFETIME_VAPOUR);
					weapon->hdg = 0;
				}
			}
		}
		weapon++;
	}

//DeadCode RJS 27Oct00 	if (explodeMe)														//RJS 16Sep00
//DeadCode RJS 27Oct00 		Trans_Obj.KillLauncher(pTrailItm,pTrailItm,*mobileitem::currworld);	//RJS 16Sep00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateSmokeDriftCoords
//Author		Robert Slater
//Date			Mon 24 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::UpdateSmokeDriftCoords(itemptr	itm,animptr&	aptr)
{
	ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(itm->shape);//RJS 23Apr99
	int					index;
	WeapAnimData*		weapon;
	MoveGunAnimData*	adptr = (MoveGunAnimData*) aptr;
	SLong				wx = itm->World.X;
	SLong				wy = itm->World.Y;
	SLong				wz = itm->World.Z;
//DeadCode RJS 20Oct00 	SWord				animsize = sdptr->AnimDataSize;
//DeadCode RJS 20Oct00 	UByte				instsize = sizeof(DOLAUNCHER) + 1;
	DOLAUNCHER_PTR		lptr;
	UByteP				instr_ptr;
	UByteP				base_ptr;
	UWord				instruction;
	SWord				xdrift,ydrift,zdrift;
	SWord				sin_ang,cos_ang;
	SLong				distpframe;
	SmokeTypeP			smkptr;
	UWord				lifetime;
	Bool				validpoint;

	switch (SHAPESTUFF.GetShapeScale(sdptr))				
 	{														
 		case SHP_1CM:										
 			shapescale = 0;									
 			break;											
 		case SHP_4CM:										
 			shapescale = 2;									
 			break;											
 		case SHP_16CM:										
 			shapescale = 4;									
 			break;											
 	}

	v_sin_ang = 0;
	v_cos_ang = 0;

//	if (!Three_Dee.IsPaused())										//RJS 27Feb98
//		SamplePntTime = TRUE;									

	base_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

	weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];
	if (weapon)
	{
		instr_ptr = base_ptr;
		instr_ptr++;

		lptr = (DOLAUNCHER_PTR) instr_ptr;
		if (	!lptr->damageflag
			|| (aptr[lptr->damageflag] < lptr->damthresh)	)
		{
			if (lptr->trailtype > -1)
			{
				smkptr = (SmokeTypeP) &SmokeTrlList[lptr->trailtype];//RJS 08Dec97
				lifetime = smkptr->LifeTime;					//RJS 08Dec97

				index = weapon->hdg;								//RJS 12Jan98
				if (index > 0)									//RJS 13Apr99
				{
					traillist[index].lastwx = wx;
					traillist[index].lastwy = wy;
					traillist[index].lastwz = wz;
					traillist[index].nextlist = 0;
					validpoint = TRUE;

					SLong	dist = object_obj3d->realbz.f;			//RJS 07Feb00
					if (SamplePntTime)
					{
						SLong		degradetime;						//RJS 22Jun00
						Coords3D	pos = itm->World;				//RJS 24May00
						pos.Y += 20000;									//RJS 22Jun00

//DeadCode RJS 22Jun00 						Land_Scape.AddSmokeCloud(pos);				//RJS 24May00

						if (dist < 40000)
							degradetime = 16;
						else
						{
							degradetime = 16 + ((100 * (dist-40000))/80000);
							if (degradetime > 150)	degradetime = 150;	//RJS 22Jun00
						}

						if (degradetime < traillist[index].SampleTime)
							traillist[index].SampleTime = degradetime;

						if (traillist[index].SampleTime < 1)
						{
							SWord	stores = weapon->pitch;
//DeadCode RJS 22Jun00 							SLong	degradetime = 10;						//RJS 07Jun99

							if (dist < 20000)							//RJS 22Jun00
								lifetime = (dist * lifetime)/20000;		//RJS 22Jun00

//DeadCode RJS 22Jun00 							if (dist < 40000)
//DeadCode RJS 22Jun00 							{
//DeadCode RJS 22Jun00 								if (dist < 20000)
//DeadCode RJS 22Jun00 									lifetime = (dist * lifetime)/20000;
//DeadCode RJS 22Jun00 							}
//DeadCode RJS 22Jun00 							else
//DeadCode RJS 22Jun00 							{
//DeadCode RJS 22Jun00 								dist -= 40000;
//DeadCode RJS 22Jun00 								degradetime = 10 + ((100 * dist)/80000);//1 sec sampling is slowest...
//DeadCode RJS 22Jun00 								if (degradetime > 150)	degradetime = 150;	//RJS 22Jun00
//DeadCode RJS 22Jun00 							}
							
							traillist[index].SampleTime = degradetime;

							Land_Scape.AddSmokeCloud(pos,degradetime);	//RJS 22Jun00

							stores -= 1;
							if (stores < 0)
							{
								SHAPE.DetatchVapourStream((SWord)weapon->hdg,0);
								weapon->hdg = 0;
								weapon->pitch = 0;
							}
							else
							{
								if (Save_Data.detail_3d[DETAIL3D_TRANSSMOKE] != 0)	//RJS 9Aug00
								{
									Coords3D	pos;
									SLong		xcoord = lptr->posx << shapescale;
									SLong		ycoord = lptr->posy << shapescale;
									SLong		zcoord = lptr->posz << shapescale;

									xcoord += wx;
									ycoord += wy;
									zcoord += wz;

									pos.X = xcoord;
									pos.Y = ycoord;
									pos.Z = zcoord;

									weapon->pitch = (Angles) stores;

									// Should only get here if launcher is in visible anyway...
									WorldStuff	*world = mobileitem::currworld;
									SWord		vhori;

									if (degradetime)
									{
										vhori = Math_Lib.rnd(smkptr->VelHori/2);
										Trans_Obj.LaunchSmokePuff2((mobileitem*)itm,pos,SMKDRK,SMKMED,vhori*2000,smkptr->VelY*2000,Math_Lib.rnd(),lifetime,lifetime,*world);
									}
									else
									{
										SLong		sno;
										UWord		randval;
										SWord		poovel = smkptr->VelY>>1;
										SWord		poovelh = smkptr->VelHori>>1;
										UWord		reallife;

										randval = Math_Lib.rnd();
										vhori = Math_Lib.rnd(smkptr->VelHori);
										reallife = (lifetime * (smkptr->VelHori - vhori))/smkptr->VelHori;
										if (vhori > poovelh)
											Trans_Obj.LaunchSmokePuff2((mobileitem*)itm,pos,BSMKE,0,vhori*2000,(poovel+Math_Lib.rnd(poovel))*2000,Math_Lib.rnd(),reallife,65535,*world);
										else
										{
											if (randval > 45000)
												Trans_Obj.LaunchSmokePuff2((mobileitem*)itm,pos,SMKDRK,SMKMED,vhori*2000,smkptr->VelY*2000,Math_Lib.rnd(),reallife,lifetime,*world);
											else
												Trans_Obj.LaunchSmokePuff2((mobileitem*)itm,pos,SMKDRK,0,vhori*2000,(poovel+Math_Lib.rnd(poovel))*2000,Math_Lib.rnd(),(reallife*randval)/45000,65536,*world);
										}
									}
								}
							}
						}
						else
							traillist[index].SampleTime -= View_Point->DrawFrameTime();
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddNewVapourPoint
//Author		Robert Slater
//Date			Fri 20 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::AddNewVapourPoint(TrailRecord* trailptr,SLong	wx, SLong wy, SLong wz, ULong	lifetime, ULong fadetime)
{
	Coords3DList*	anewpoint;									//RJS 02Jun97

	anewpoint = new Coords3DList;
	if (anewpoint)												//RJS 02Jun97
	{
		anewpoint->next = trailptr->thelist;					//RJS 18Sep97
		anewpoint->trailpoint.gx = wx;							//RJS 18Sep97
		anewpoint->trailpoint.gy = wy;							//RJS 18Sep97
		anewpoint->trailpoint.gz = wz;							//RJS 18Sep97
		anewpoint->lifeleft = lifetime;							//RJS 14Apr98
		anewpoint->radius = 1;									//RJS 21Jun99
		anewpoint->LifeTime = lifetime;							//RJS 15Apr98
		anewpoint->FadeTime = fadetime;							//RJS 24Nov98
		anewpoint->KillMe = 0;					//RJS 17Feb99

		trailptr->thelist = anewpoint;							//RJS 18Sep97
		trailptr->lifetime = lifetime;							//RJS 13Apr98
		trailptr->nopoints++;										//RJS 29May97

#ifdef	_SMOKETRAILDEBUG_
		anewpoint->trailIndex = trailptr-traillist;
		anewpoint->nextkilled = false;
		anewpoint->prevkilled = false;
		anewpoint->probed = false;
#endif

#ifndef	NDEBUG
	//Get ROB very quickly!
	if (!anewpoint->LifeTime)									//RJS 21Jun99
		INT3;
#endif
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillVapourStream
//Author		Robert Slater
//Date			Mon 23 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::KillVapourStream(int	index)
{
 	Coords3DList*		apoint, nextpoint;
	if (index < 0)											
		index = -index;

	if (index >= MAX_VAPOURS)					
		_Error.EmitSysErr(__FILE__":(KILL_VAPOUR)    Shouldn't be this : %d\n",index);

 	traillist[index].thelist->Wipe();
//DeadCode RJS 21Apr99  	apoint = traillist[index].thelist;
//DeadCode RJS 21Apr99  	while (apoint)												//RJS 02Jun97
//DeadCode RJS 21Apr99  	{															//RJS 02Jun97
//DeadCode RJS 21Apr99  		nextpoint = (Coords3DListPtr) apoint->next;				//RJS 02Jun97
//DeadCode RJS 21Apr99 																//RJS 02Jun97
//DeadCode RJS 21Apr99  		delete apoint;											//RJS 02Jun97
//DeadCode RJS 21Apr99  		apoint = nextpoint;										//RJS 02Jun97
//DeadCode RJS 21Apr99  	}															//RJS 02Jun97
																//RJS 02Jun97
 	traillist[index].thelist = NULL;							//RJS 02Jun97
 	traillist[index].lifetime = 0;								//RJS 02Jun97
 	traillist[index].nopoints = 0;								//RJS 02Jun97
 	traillist[index].bitshift = 0;								//RJS 02Jun97
	traillist[index].nextlist = 0;								//RJS 03Jun97
	traillist[index].beendrawn = 0;								//RJS 03Jun97
//DeadCode RJS 14Apr98 	traillist[index].birthtime = 0;								//RJS 18Sep97
	traillist[index].SampleTime = 0;							//RJS 08Jan98
//DeadCode RJS 17Feb99 	traillist[index].FakePointPtr = NULL;						//RJS 17Mar98
//DeadCode RJS 06May99 	traillist[index].InitVelH = 0;								//RJS 09Apr98
//DeadCode RJS 06May99 	traillist[index].InitVelY = 0;								//RJS 17Mar98
//DeadCode RJS 06May99 	traillist[index].Acceleration = 0;							//RJS 17Mar98
	traillist[index].SmkDescPtr = NULL;							//RJS 09Apr98
	traillist[index].cloudlaunched = FALSE;						//RJS 03Jul98
	traillist[index].transient = 0;
	traillist[index].currTime = 0;								//RJS 16Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DetatchVapourStream
//Author		Robert Slater
//Date			Tue 27 May 1997
//
//Description	Hands over the mantle to a transient item.....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::DetatchVapourStream(int	index,int	LifeTime, bool novapour)
{
	SLong	newlife = 0;
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(pTrailItm->shape);//DAW 19May99
	if (sdptr->Type.VapourType != TRAIL_OFF)
	{
		if (index > 0)
		{
//DeadCode DAW 19May99 			if (traillist[index].thelist && LifeTime && (traillist[index].nopoints > 1))//RJS 13Apr99
			if (	traillist[index].thelist
				&&	LifeTime
				&& (traillist[index].nopoints > 1)
				&&	!novapour						)
			{
				ShapeNum	detachshape = (ShapeNum) 0;
				SmokeTypeP	smkdptr = (SmokeTypeP) traillist[index].SmkDescPtr;//RJS 09Apr98
				if (smkdptr)
					detachshape = smkdptr->DetachShape;

				if (detachshape > 0)									//RJS 10Mar98
				{
					WorldStuff*	worldptr = mobileitem::currworld;
					TrailRecordPtr	TrailPtr = &traillist[index];
					Coords3DList*	apoint = TrailPtr->thelist;
					Coords3DList*	fpoint = apoint;
					SLong	lastx,lasty,lastz;

					lastx = lasty = lastz = 0;							//RJS 20Oct00

					// Calculate mid point of trail...
 					while (apoint)
 					{
						if (apoint->next == NULL)
						{
							lastx = apoint->trailpoint.gx;
							lasty = apoint->trailpoint.gy;
							lastz = apoint->trailpoint.gz;
						}
						apoint = apoint->next;
 					}

					lastx += fpoint->trailpoint.gx;
					lasty += fpoint->trailpoint.gy;
					lastz += fpoint->trailpoint.gz;

					lastx >>= 1;
					lasty >>= 1;
					lastz >>= 1;

					TrailPtr->transient = 1;

  					if (!Trans_Obj.LaunchVapourTransient((mobileitem*) pTrailItm,		//RJS 12Apr99
	  													lastx,							//RJS 22Jan99
  														lasty,							//RJS 22Jan99
  														lastz,							//RJS 22Jan99
  														index,
  														500,			//give it 5 secs before degrade
  														*worldptr,
  														SMKSHP))	//always this shape	//RJS 07Jul99
						AddVapourStreamToDeadList(index,pTrailItm);			//DAW 06Apr99
				}
				else
					AddVapourStreamToDeadList(index,pTrailItm);					//RJS 09Apr98
			}
			else
				AddVapourStreamToDeadList(index,pTrailItm);						//RJS 09Apr98
		}
		else
		{
			//Must be a static trail....
			if (index)
			{
				SmokeTrailAnimData*	adptr = (SmokeTrailAnimData*) pTrailItm->Anim;

				if (adptr->nopoints || novapour)					//RJS 19May99
				{
					if (adptr->nopoints)
					{
						MakeProbes[newprobecnt].action = PROBER_KILL;
						MakeProbes[newprobecnt++].itm = (TransientItem*) pTrailItm;
					}
					else
						AddVapourStreamToDeadList(-index,pTrailItm);					//RJS 12Apr99
				}
				else
				{
					// Prepare the trail for abandonment...
					if (adptr->thelist == 0)
					{
						index = -index;

						Coords3DList*	apoint = traillist[index].thelist;
						while (apoint)
						{
							if (apoint->lifeleft > newlife)
								newlife = apoint->lifeleft;
					
							apoint = apoint->next;
						}
						if (newlife)								//AMM 26Mar99
						{
							if (!adptr->isDegraded)					//RJS 06May99
							{
								adptr->isDegraded = TRUE;				//RJS 06May99

								MakeProbes[newprobecnt].action = PROBER_DEGRADE;
								MakeProbes[newprobecnt].index = index;
								MakeProbes[newprobecnt++].itm = (TransientItem*)pTrailItm;
							}
						}
						else
							AddVapourStreamToDeadList(index,pTrailItm);					//RJS 12Apr99
					}
					else
					{
						// shouldn't get here...
						Trans_Obj.RemoveTransientItemFromTrailList((TransientItemPtr)pTrailItm);//RJS 18Feb99
					}
				}
			}
		}
	}

	return(newlife);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddVapourStreamToDeadList
//Author		Robert Slater
//Date			Thu 9 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::AddVapourStreamToDeadList(int	index, ItemPtr	itm)
{
	if (index > 0)
	{
		int	i;
		for (i=0; i < VapDeadCnt; i++)
		{
			if (VapDeadList[i] == index)
				break;
		}

		if (i==VapDeadCnt)
		{
			if (VapDeadCnt == REAL_MAX_VAPOURS)
				_Error.EmitSysErr(__FILE__":Vapour Dead List is full");
			else
			{
				SLong	absindex = index;
				if (absindex < 0)
					absindex = -absindex;

				if (absindex > MAX_VAPOURS)
					INT3;

				VapDeadList[VapDeadCnt++] = index;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillVapourStreamDeadList
//Author		Robert Slater
//Date			Thu 9 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::KillVapourStreamDeadList()
{
	int	i;

		// and kill unwanted trail points...
		for (i=0; i < REAL_MAX_VAPOURS; i++)
		{
			traillist[i].FakePointPtr->Wipe();
			traillist[i].FakePointPtr = NULL;
		}

		for (i=0; i < VapDeadCnt; i++)					//RJS 17Feb99
			KillVapourStream(VapDeadList[i]);			//RJS 17Feb99

		VapDeadCnt = 0;									//RJS 17Feb99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DetatchAllVapourStreams
//Author		Robert Slater
//Date			Tue 27 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::DetatchAllVapourStreams(itemptr	itm,int	LifeTime, bool novapour)
{
	MinAnimData*		aptr = (MinAnimData*) itm->Anim;
	UWord				noLaunchers;
	ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(itm->shape);//RJS 17Nov98
	SLong				newlife = 0;

	if (	(SHAPESTUFF.GetShapeScale(sdptr) != SHP_GRP)		//RJS 19May99
		&&	(sdptr->Type.VapourType != TRAIL_OFF)		)		//RJS 19May99
	{
		noLaunchers = aptr->nolaunchers;							//RJS 17Nov98
		if (noLaunchers)											//RJS 17Nov98
		{
			int					index;
			WeapAnimData*		weapon;
			MoveGunAnimData*	adptr = (MoveGunAnimData*) itm->Anim;

			pTrailItm = itm;//RJS 02Sep98

			for (index=0; index < noLaunchers; index++)			//RJS 17Nov98
			{
				weapon = &adptr->weaponlaunchers[index];
				if (weapon && weapon->hdg)									//RJS 08Apr99
				{
					if ((weapon->LauncherType & LT_MASK) == LT_SMKTRAILS)	//RJS 13Apr99
					{
						newlife = DetatchVapourStream(weapon->hdg,LifeTime,novapour);//RJS 19May99
						if (newlife==0)						//RJS 21Jan99
						{
							//if transient death, alert transite...
							if (weapon->hdg < 0)			//RJS 06Apr99
								newlife = -1;				//RJS 06Apr99

							weapon->hdg = 0;				//DAW 06Apr99
						}
					}
				}
			}
		}
	}

	return(newlife);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NextFreeVapour
//Author		Robert Slater
//Date			Tue 27 May 1997
//
//Description	
//				acceleration is -g (scaled up) * resistance percentage
//												   (100% is no drag)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte	shape::NextFreeVapour(SWord	velh,SWord vely, SWord	resistance,UByteP smkptr)
{
	int		index;			
	UByte	retval = 0;

	if (View_Point)
	{
		for (index=1; index < MAX_VAPOURS; index++)
		{
			if (!traillist[index].thelist && !traillist[index].beendrawn)
			{
				if (smkptr)
				{
					SmokeTypeP	smkdptr = (SmokeTypeP) smkptr;

					velh = smkdptr->VelHori;
					vely = smkdptr->VelY;
					resistance = smkdptr->Resistance;
				}

				resistance = (resistance << 7) / 100;
				resistance = 128 - resistance;

				traillist[index].beendrawn = 1;						//RJS 17Sep97
//DeadCode RJS 06May99 				traillist[index].InitVelY = vely;
//DeadCode RJS 06May99 				traillist[index].InitVelH = velh;
//DeadCode RJS 06May99 				traillist[index].Acceleration = -100 * resistance;
				traillist[index].SmkDescPtr = smkptr;
				traillist[index].cloudlaunched = FALSE;
//Dead...				traillist[index].FakePointPtr = NULL;	//always maintain the deadlist...
				traillist[index].transient = 0;
				traillist[index].currTime = View_Point->TotalDrawFrameTime();//RJS 05Apr00

#ifdef	_SMOKETRAILDEBUG_
				traillist[index].theItemPtr = NULL;
#endif

				retval = index;
				break;
			}
		}
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BlokesItemAnim
//Author		Robert Slater
//Date			Tue 1 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::BlokesItemAnim(BlokesAnimData* adptr)
{
	if (object_obj3d->realbz.f < 80000.0)				//RJS 07Feb00
	{
		bool	ejectblokes = false;

		ItemPtr		itm = NULL;
		SLong		placecnt = 0;
		Coords3D	*placelist = NULL;

		if (adptr->nearestuid)
		{
			itm = (ItemPtr)Persons2::ConvertPtrUID((UniqueID)adptr->nearestuid);
			if (itm && !itm->Status.deadtime)
			{
				if (!adptr->timer)
				{
					placelist = new Coords3D[48];
					if (placelist)
						placelist[0] = itm->World;

					ejectblokes = true;
				}
				else
				{
					SLong	realtime = adptr->timer;
					realtime -= View_Point->DrawFrameTime();
					if (realtime < 0)
						realtime = 0;

					adptr->timer = UWord(realtime);
				}
			}
		}
		else
		{
			if (adptr->itemstate == ALIVE)
			{
				ejectblokes = true;

				adptr->itemstate = DEAD;
				adptr->timer = 12000;		//give them 2 mins to come back

				itm = Three_Dee.NearestAliveThing(object_obj3d->ItemPtr);
				if (itm)
				{
					adptr->nearestuid = itm->uniqueID.count;
					
					placelist = new Coords3D[48];
					if (placelist)
						placelist[0] = itm->World;
				}
			}
		}

		if (ejectblokes)
		{
			if (itm && placelist)
			{
				ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
				animptr			adptrtmp = itm->Anim;
				ShapeNum		newshp;
				SLong			xpos,ypos,zpos;
				MinAnimData*	mad;

				if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
				{
					UByteP		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;

					// Search for nearest strongest....

					while (GetGroupElement(instr_ptr,newshp,xpos,ypos,zpos))
					{
						mad = (MinAnimData*) adptrtmp;
						if (mad->itemstate == ALIVE)
						{
							placelist[placecnt].X = xpos + itm->World.X;
							placelist[placecnt].Y = ypos + itm->World.Y;
							placelist[placecnt++].Z = zpos + itm->World.Z;
						}

						adptrtmp += SHAPE.GetElementAnimOffset(newshp);
					}
				}
				else
					placecnt = 1;
			}

			Trans_Obj.PointBlokes(object_obj3d->ItemPtr,BLOKE,object_obj3d->ItemPtr->World,12,placelist,placecnt);//RJS 11Jun99
		}

		if (placelist)
			delete []placelist;
	}
}

//DeadCode RJS 17Nov99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 17Nov99 //Procedure		WeapItemAnim
//DeadCode RJS 17Nov99 //Author		Paul.   
//DeadCode RJS 17Nov99 //Date			Mon 1 Apr 1996
//DeadCode RJS 17Nov99 //
//DeadCode RJS 17Nov99 //Description	
//DeadCode RJS 17Nov99 //
//DeadCode RJS 17Nov99 //Inputs		
//DeadCode RJS 17Nov99 //
//DeadCode RJS 17Nov99 //Returns	
//DeadCode RJS 17Nov99 //
//DeadCode RJS 17Nov99 //------------------------------------------------------------------------------
//DeadCode RJS 17Nov99 void shape::WeapItemAnim(WeapAnimData* adptr)
//DeadCode RJS 17Nov99 {
//DeadCode RJS 01Jun99 	DirectItemAnim((DirectAnimData* )adptr);
//DeadCode RJS 17Nov99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLauncherData
//Author		Paul.   
//Date			Mon 1 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::SetLauncherData(WeapAnimData* adptr, ShapeNum shpno)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		drawsphere
//Author		Robert Slater
//Date			Tue 16 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE JON 4/12/00 void	shape::drawsphere(	int	vertex,
//DEADCODE JON 4/12/00 							int	radius,
//DEADCODE JON 4/12/00 							int	colour,
//DEADCODE JON 4/12/00 							int	animflag,
//DEADCODE JON 4/12/00 							int	animscale,
//DEADCODE JON 4/12/00 							int	transdepth,
//DEADCODE JON 4/12/00 							Bool	smoothed,
//DEADCODE JON 4/12/00 							int	halowidth,
//DEADCODE JON 4/12/00 							int	lumdepth,
//DEADCODE JON 4/12/00 							int	animflag2	)
//DEADCODE JON 4/12/00 {
//DEADCODE JON 4/12/00 //DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr; 			
//DEADCODE JON 4/12/00 	DoPointStruc	dopointr, dopoint0;
//DEADCODE JON 4/12/00 	SWord			RealRadius,BandWidth;
//DEADCODE JON 4/12/00 	Colour			thecol = (Colour) colour;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	transdepth *= 25;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	dopointr = dopoint0 = newco[vertex];
//DEADCODE JON 4/12/00 	dopointr.bodyx.f += radius;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	R3DVALUE screenxr,screenyr,screenzr;						//RJS 07Feb00
//DEADCODE JON 4/12/00 	R3DVALUE screenx0,screeny0,screenz0;						//RJS 07Feb00
//DEADCODE JON 4/12/00 	g_lpLib3d->BodyToScreen(dopointr,screenxr,screenyr,screenzr);//RJS 07Feb00
//DEADCODE JON 4/12/00 	g_lpLib3d->BodyToScreen(dopoint0,screenx0,screeny0,screenz0);//RJS 07Feb00
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	RealRadius = screenxr - screenx0;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	if (animflag)
//DEADCODE JON 4/12/00 		thecol = (Colour) (colour + (GlobalAdptr[animflag]/animscale));
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 //DEAD	POLYGON.SetPixelWidth(1);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	if (!halowidth)
//DEADCODE JON 4/12/00 	{
//DEADCODE JON 4/12/00 		if (smoothed)
//DEADCODE JON 4/12/00 		{
//DEADCODE JON 4/12/00 			if (lumdepth)
//DEADCODE JON 4/12/00 			{
//DEADCODE JON 4/12/00 				if (animflag2)
//DEADCODE JON 4/12/00 					lumdepth -= (GlobalAdptr[animflag2]/animscale);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 				if (lumdepth > 0)
//DEADCODE JON 4/12/00 				{
//DEADCODE JON 4/12/00 					g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,lumdepth);
//DEADCODE JON 4/12/00 					g_lpLib3d->DrawSphere(HMATERIAL(thecol),dopoint0,RealRadius,ANGLES_0Deg,0,0,0,0);
//DEADCODE JON 4/12/00 				}
//DEADCODE JON 4/12/00 			}
//DEADCODE JON 4/12/00 			else
//DEADCODE JON 4/12/00 			{
//DEADCODE JON 4/12/00 				if (animflag2)
//DEADCODE JON 4/12/00 					transdepth -= ((GlobalAdptr[animflag2]*25)/animscale);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 				g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,transdepth);
//DEADCODE JON 4/12/00 				g_lpLib3d->DrawSphere(HMATERIAL(thecol),dopoint0,RealRadius,ANGLES_0Deg,0,0,0,0);
//DEADCODE JON 4/12/00 			}
//DEADCODE JON 4/12/00 		}
//DEADCODE JON 4/12/00 		else
//DEADCODE JON 4/12/00 		{
//DEADCODE JON 4/12/00 			g_lpLib3d->DrawSphere(HMATERIAL(thecol),dopoint0,RealRadius,ANGLES_0Deg,0,0,0,0);
//DEADCODE JON 4/12/00 		}
//DEADCODE JON 4/12/00 	}
//DEADCODE JON 4/12/00 	else
//DEADCODE JON 4/12/00 	{
//DEADCODE JON 4/12/00 		BandWidth = (RealRadius * halowidth) >> 7;
//DEADCODE JON 4/12/00 		if (BandWidth)
//DEADCODE JON 4/12/00 		{
//DEADCODE JON 4/12/00 			if (animflag2)
//DEADCODE JON 4/12/00 				lumdepth -= (GlobalAdptr[animflag2]/animscale);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 			if (lumdepth > 0)
//DEADCODE JON 4/12/00 			{
//DEADCODE JON 4/12/00 				g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,lumdepth);
//DEADCODE JON 4/12/00 				g_lpLib3d->DrawSphere(HMATERIAL(thecol),dopoint0,RealRadius,ANGLES_0Deg,0,0,0,0);
//DEADCODE JON 4/12/00 //deadcode				POLYGON.createhalo(thecol,lumdepth);
//DEADCODE JON 4/12/00 //deadcode				POLYGON.createsphvert(dopoint0,RealRadius,BandWidth);
//DEADCODE JON 4/12/00 //deadcode				POLYGON.drawsphere();
//DEADCODE JON 4/12/00 			}
//DEADCODE JON 4/12/00 		}
//DEADCODE JON 4/12/00 	}
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	g_lpLib3d->SetGlobal(TOGGLE_GLOBALLUMINOSITY,ULong(LUM_OFF));
//DEADCODE JON 4/12/00 	g_lpLib3d->SetGlobal(TOGGLE_GLOBALTRANSPARENCY,ULong(SMOKED_OFF));
//DEADCODE JON 4/12/00 }

//DEADCODE JON 4/12/00 void	shape::DrawHeatHaze(int	vertex,
//DEADCODE JON 4/12/00 							int	radius,
//DEADCODE JON 4/12/00 							int	colour	)
//DEADCODE JON 4/12/00 {
//DEADCODE JON 4/12/00 	DoPointStruc	dopointr, dopoint0;
//DEADCODE JON 4/12/00 	SWord			RealRadius;
//DEADCODE JON 4/12/00 	Colour			thecol = (Colour) colour;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	dopointr = dopoint0 = newco[vertex];
//DEADCODE JON 4/12/00 	dopointr.bodyx.f += radius;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	R3DVALUE screenxr,screenyr,screenzr;						//RJS 07Feb00
//DEADCODE JON 4/12/00 	R3DVALUE screenx0,screeny0,screenz0;						//RJS 07Feb00
//DEADCODE JON 4/12/00 	g_lpLib3d->BodyToScreen(dopointr,screenxr,screenyr,screenzr);//RJS 07Feb00
//DEADCODE JON 4/12/00 	g_lpLib3d->BodyToScreen(dopoint0,screenx0,screeny0,screenz0);//RJS 07Feb00
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	RealRadius = screenxr - screenx0;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	g_lpLib3d->DrawSphere(HMATERIAL(thecol),dopoint0,RealRadius,ANGLES_0Deg,0,0,0,0);
//DEADCODE JON 4/12/00 //deadcode	POLYGON.createhaze(thecol);
//DEADCODE JON 4/12/00 //deadcode	POLYGON.createsphvert(dopoint0,RealRadius);
//DEADCODE JON 4/12/00 //deadcode	POLYGON.drawsphere();
//DEADCODE JON 4/12/00 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RealImapSphere
//Author		Robert Slater
//Date			Tue 16 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE JON 4/12/00 void	shape::RealImapSphere(	int	vertex,
//DEADCODE JON 4/12/00 								int	radius,
//DEADCODE JON 4/12/00 								int	imageno,
//DEADCODE JON 4/12/00 								int	minx,
//DEADCODE JON 4/12/00 								int	miny,
//DEADCODE JON 4/12/00 								int	maxx,
//DEADCODE JON 4/12/00 								int	maxy,
//DEADCODE JON 4/12/00 								int	animflag,
//DEADCODE JON 4/12/00 								int	animscale	)
//DEADCODE JON 4/12/00 {
//DEADCODE JON 4/12/00 //DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr; 			
//DEADCODE JON 4/12/00 	DoPointStruc	dopointr, dopoint0;
//DEADCODE JON 4/12/00 	SWord			RealRadius;
//DEADCODE JON 4/12/00 	ImageMapNumber	imapno = (ImageMapNumber)imageno;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	dopointr = dopoint0 = newco[vertex];
//DEADCODE JON 4/12/00 	dopointr.bodyx.f += radius;
//DEADCODE JON 4/12/00 //deadcode	_matrix.body2screen(dopointr);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	R3DVALUE screenx0,screeny0,screenz0,screenxr,screenyr,screenzr;//RJS 07Feb00
//DEADCODE JON 4/12/00 	g_lpLib3d->BodyToScreen(dopoint0,screenx0,screeny0,screenz0);//RJS 07Feb00
//DEADCODE JON 4/12/00 	g_lpLib3d->BodyToScreen(dopointr,screenxr,screenyr,screenzr);//RJS 07Feb00
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	RealRadius = screenxr - screenx0;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	if (animflag)
//DEADCODE JON 4/12/00 	{
//DEADCODE JON 4/12/00 		UWord	frameno = GlobalAdptr[animflag] / animscale;
//DEADCODE JON 4/12/00 		SWord	sizey = maxy - miny;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		miny += (frameno * sizey);
//DEADCODE JON 4/12/00 		maxy = miny + sizey;
//DEADCODE JON 4/12/00 	}
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 //DEAD	POLYGON.SetPixelWidth(1);
//DEADCODE JON 4/12/00 	
//DEADCODE JON 4/12/00 	g_lpLib3d->DrawSphere(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),dopoint0,RealRadius,ANGLES_0Deg,minx,miny,maxx,maxy);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 //DEAD	POLYGON.SetPixelWidth(1);
//DEADCODE JON 4/12/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		imapsphere
//Author		Martin Alderton
//Date			Tue 16 Apr 1996
//
//Description		
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::imapsphere(	UWord vertex,
						UWord 	radius,	
						ImageMapNumber imapno,
						SWord	minx, SWord	miny,
						SWord	maxx, SWord	maxy,
						bool	ispivoted	)
{
	if (ispivoted)
	{
		static SWord myAngle=0;
		myAngle = -SWord(View_Point->roll);

		g_lpLib3d->DrawPivotedSphere(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),newco[vertex],radius,Angles(myAngle),minx,miny,maxx,maxy);
	}
	else
		g_lpLib3d->DrawSphere(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),newco[vertex],radius,ANGLES_0Deg,minx,miny,maxx,maxy);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		imapsphereQuad
//Author		Robert Slater
//Date			Fri 20 Feb 1998
//
//Description	Quad sphere to make things BIGGER
//
// 	dopoints:	2----3----2
//				|	 |	  |
//				|	 |	  |
//				1----0----1
//				|	 |	  |
//				|	 |	  |
//				2----3----2
//
//
// NOTE: This would be more efficient as 1 poly using a 9 point fan centred on point 0
//
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::imapsphereQuad(	UWord vertex,
							UWord 	radius,	
							ImageMapNumber imapno,
							SWord	minx, SWord	miny,
							SWord	maxx, SWord	maxy	)
{
//DeadCode RJS 06Jun100  	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopoint4;
//DeadCode RJS 06Jun100 	D3DVALUE	scaleradius = radius;
//DeadCode RJS 06Jun100 	D3DVALUE	scaleradius2 = (radius<<1);
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 	dopoint0 = dopoint1 = dopoint2 = dopoint3 = dopoint4 = newco[vertex];
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 //DEADCODE RDH 5/19/00 	if (dopoint0.bodyz.f > 1)								
//DeadCode RJS 06Jun100 	{															
//DeadCode RJS 06Jun100 		//Crappy line fix...
//DeadCode RJS 06Jun100 		maxy-=2;
//DeadCode RJS 06Jun100 	  	maxx--;
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		dopoint1.setPosX(dopoint1.getPosX() - scaleradius);		//RJS 19May00
//DeadCode RJS 06Jun100 																
//DeadCode RJS 06Jun100 		dopoint2.setPosX(dopoint2.getPosX() - scaleradius);		//RJS 19May00
//DeadCode RJS 06Jun100 		dopoint2.setPosY(dopoint2.getPosY() + scaleradius);		//RJS 19May00
//DeadCode RJS 06Jun100 																
//DeadCode RJS 06Jun100 		dopoint3.setPosY(dopoint3.getPosY() + scaleradius);		//RJS 19May00
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		dopoint4 = dopoint1;
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 .>.>.>.>.>.>.>.>.>.>  3DCOM.CPP  Rev "RJS branch" (1.0.45.1)//JIM 19Jul100
//DeadCode RJS 06Jun100 		dopoint0.setIMapCoords(maxx,maxy);						//RJS 19May00
//DeadCode RJS 06Jun100 		dopoint1.setIMapCoords(minx,maxy);						//RJS 19May00
//DeadCode RJS 06Jun100 		dopoint2.setIMapCoords(minx,miny);						//RJS 19May00
//DeadCode RJS 06Jun100 		dopoint3.setIMapCoords(maxx,miny);						//RJS 19May00
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		Lib3DPoint*	pRVerts;
//DeadCode RJS 06Jun100 		pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),4);//RJS 19May00
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint0;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint1;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint2;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint3;
//DeadCode RJS 06Jun100 		g_lpLib3d->EndPoly();
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		dopoint2.setPosX(dopoint2.getPosX() + scaleradius2);	//RJS 19May00
//DeadCode RJS 06Jun100 		dopoint1.setPosX(dopoint1.getPosX() + scaleradius2);	//RJS 19May00
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),4);//RJS 19May00
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint0;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint3;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint2;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint1;
//DeadCode RJS 06Jun100 		g_lpLib3d->EndPoly();
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		dopoint2.setPosY(dopoint2.getPosY() - scaleradius2);	//RJS 19May00
//DeadCode RJS 06Jun100 		dopoint3.setPosY(dopoint3.getPosY() - scaleradius2);	//RJS 19May00
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),4);//RJS 19May00
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint0;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint1;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint2;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint3;
//DeadCode RJS 06Jun100 		g_lpLib3d->EndPoly();
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		dopoint2.setPosX(dopoint2.getPosX() - scaleradius2);	//RJS 19May00
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 <<<<<<<<<<  3DCOM.CPP  Rev "Tip" (1.0.50.0)
//DeadCode RJS 06Jun100 		dopoint0.setIMapCoords(maxx,maxy);						//RJS 19May00
//DeadCode RJS 06Jun100 		dopoint1.setIMapCoords(minx,maxy);						//RJS 19May00
//DeadCode RJS 06Jun100 		dopoint2.setIMapCoords(minx,miny);						//RJS 19May00
//DeadCode RJS 06Jun100 		dopoint3.setIMapCoords(maxx,miny);						//RJS 19May00
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		Lib3DPoint*	pRVerts;
//DeadCode RJS 06Jun100 		pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),4);//RJS 19May00
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint0;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint1;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint2;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint3;
//DeadCode RJS 06Jun100 		g_lpLib3d->EndPoly();
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		dopoint2.setPosX(dopoint2.getPosX() + scaleradius2);	//RJS 19May00
//DeadCode RJS 06Jun100 		dopoint1.setPosX(dopoint1.getPosX() + scaleradius2);	//RJS 19May00
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),4);//RJS 19May00
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint0;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint3;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint2;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint1;
//DeadCode RJS 06Jun100 		g_lpLib3d->EndPoly();
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		dopoint2.setPosY(dopoint2.getPosY() - scaleradius2);	//RJS 19May00
//DeadCode RJS 06Jun100 		dopoint3.setPosY(dopoint3.getPosY() - scaleradius2);	//RJS 19May00
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),4);//RJS 19May00
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint0;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint1;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint2;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint3;
//DeadCode RJS 06Jun100 		g_lpLib3d->EndPoly();
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		dopoint2.setPosX(dopoint2.getPosX() - scaleradius2);	//RJS 19May00
//DeadCode RJS 06Jun100 ==========
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 		dopoint1 = dopoint4;
//DeadCode RJS 06Jun100 
//DeadCode RJS 06Jun100 >.>.>.>.>.>.>.>.>.>  3DCOM.CPP  Rev "RJS branch" (1.0.45.1)
//DeadCode RJS 06Jun100 		pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),4);//RJS 19May00
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint0;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint3;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint2;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint1;
//DeadCode RJS 06Jun100 		g_lpLib3d->EndPoly();
//DeadCode RJS 06Jun100 <<<<<<<<<<  3DCOM.CPP  Rev "Tip" (1.0.50.0)
//DeadCode RJS 06Jun100 		pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),4);//RJS 19May00
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint0;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint3;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint2;
//DeadCode RJS 06Jun100 		*pRVerts++=dopoint1;
//DeadCode RJS 06Jun100 		g_lpLib3d->EndPoly();
//DeadCode RJS 06Jun100 ==========
//DeadCode RJS 06Jun100 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		imaptrailcyl
//Author		Robert Slater
//Date			Wed 17 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::imaptrailcyl(UWord   vertex1, UWord vertex2,
						ImageMapNumber imapno,
						SWord	minix, SWord	miniy,
						SWord	maxix, SWord	maxiy,
						UWord	width, UWord	height,
						UByte	divfactor,
						UByte	flagoffset,
						SWord	xoff0, SWord yoff0,
						SWord	xoff1, SWord yoff1)
{
//DeadCode RJS 19May00 //DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr; 			
//DeadCode RJS 19May00 //	UByte	frameno = adptr[flagoffset] / divfactor;
//DeadCode RJS 19May00 //	SWord	minx, miny, maxx, maxy;								
//DeadCode RJS 19May00 	ULong	thewidth, theheight;
//DeadCode RJS 19May00 	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3;
//DeadCode RJS 19May00  	Float	xdelt1 = (Float) xoff0;
//DeadCode RJS 19May00  	Float	ydelt1 = (Float) yoff0;
//DeadCode RJS 19May00  	Float	xdelt2 = (Float) xoff1;
//DeadCode RJS 19May00  	Float	ydelt2 = (Float) yoff1;
//DeadCode RJS 19May00  	Bool	oldcross;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 // 	minx = minix;		
//DeadCode RJS 19May00 // 	miny = miniy;		
//DeadCode RJS 19May00 // 	maxx = maxix - 1;	
//DeadCode RJS 19May00 // 	maxy = maxiy;
//DeadCode RJS 19May00  
//DeadCode RJS 19May00 // 	theheight = maxiy - miniy;
//DeadCode RJS 19May00 // 
//DeadCode RJS 19May00 // 	miny += height * frameno;							
//DeadCode RJS 19May00 // 	maxy = miny + theheight - 1;
//DeadCode RJS 19May00   
//DeadCode RJS 19May00 //DEAD  	oldcross = POLYGON.SetCrossProduct(FALSE);
//DeadCode RJS 19May00   
//DeadCode RJS 19May00 //  	ImageMapNumber	absimapno = (ImageMapNumber )((imapno<0)?-imapno:imapno);
//DeadCode RJS 19May00   	ImageMapDescPtr imptr = Image_Map.GetImageMapPtr(imapno);
//DeadCode RJS 19May00  
//DeadCode RJS 19May00    	dopoint0 = dopoint1 = newco[vertex1];				
//DeadCode RJS 19May00    	dopoint2 = dopoint3 = newco[vertex2];
//DeadCode RJS 19May00 
//DeadCode RJS 19May00  	dopoint0.bodyx.f += xdelt1;								
//DeadCode RJS 19May00   	dopoint0.bodyy.f += ydelt1;
//DeadCode RJS 19May00 //deadcode	_matrix.SetClipFlags(dopoint0);
//DeadCode RJS 19May00  
//DeadCode RJS 19May00   	dopoint1.bodyx.f += -xdelt1;								
//DeadCode RJS 19May00  	dopoint1.bodyy.f += -ydelt1;								
//DeadCode RJS 19May00 //deadcode	_matrix.SetClipFlags(dopoint1);
//DeadCode RJS 19May00  
//DeadCode RJS 19May00    	dopoint2.bodyx.f += -xdelt2;								
//DeadCode RJS 19May00    	dopoint2.bodyy.f += -ydelt2;								
//DeadCode RJS 19May00 //deadcode	_matrix.SetClipFlags(dopoint2);
//DeadCode RJS 19May00  
//DeadCode RJS 19May00    	dopoint3.bodyx.f += xdelt2;								
//DeadCode RJS 19May00    	dopoint3.bodyy.f += ydelt2;								
//DeadCode RJS 19May00 //deadcode	_matrix.SetClipFlags(dopoint3);
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //deadcode	andedFlags=CF3D_ALL;
//DeadCode RJS 19May00 //deadcode	andedFlags&=dopoint0.clipFlags;
//DeadCode RJS 19May00 //deadcode	andedFlags&=dopoint1.clipFlags;
//DeadCode RJS 19May00 //deadcode	andedFlags&=dopoint2.clipFlags;
//DeadCode RJS 19May00 //deadcode	andedFlags&=dopoint3.clipFlags;
//DeadCode RJS 19May00 //deadcode	if (andedFlags==0)
//DeadCode RJS 19May00 //deadcode	{
//DeadCode RJS 19May00 //		if (!doingHW3D)
//DeadCode RJS 19May00 //		{
//DeadCode RJS 19May00 //			_matrix.body2screen(dopoint0);
//DeadCode RJS 19May00 //			_matrix.body2screen(dopoint1);
//DeadCode RJS 19May00 //			_matrix.body2screen(dopoint2);
//DeadCode RJS 19May00 //			_matrix.body2screen(dopoint3);
//DeadCode RJS 19May00 //		}
//DeadCode RJS 19May00  
//DeadCode RJS 19May00 //DEAD   		POLYGON.SetPixelWidth(1<<Save_Data.pixelsize);			
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		dopoint3.ix=minix;
//DeadCode RJS 19May00 		dopoint3.iy=miniy;					
//DeadCode RJS 19May00 		dopoint2.ix=maxix;
//DeadCode RJS 19May00 		dopoint2.iy=miniy;					
//DeadCode RJS 19May00 		dopoint1.ix=maxix;
//DeadCode RJS 19May00 		dopoint1.iy=maxiy;					
//DeadCode RJS 19May00 		dopoint0.ix=minix;
//DeadCode RJS 19May00 		dopoint0.iy=maxiy;					
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		R3DVERTEX *pRVerts;
//DeadCode RJS 19May00 		g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),4,pRVerts);
//DeadCode RJS 19May00 		*pRVerts++=dopoint3;
//DeadCode RJS 19May00 		*pRVerts++=dopoint2;
//DeadCode RJS 19May00 		*pRVerts++=dopoint1;
//DeadCode RJS 19May00 		*pRVerts++=dopoint0;
//DeadCode RJS 19May00 		g_lpLib3d->EndPoly();
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //deadcode   		POLYGON.createpoly(imapno);								
//DeadCode RJS 19May00    																
//DeadCode RJS 19May00 //deadcode 		POLYGON.createvert(dopoint3,minix,miniy);					
//DeadCode RJS 19May00 //deadcode   		POLYGON.createvert(dopoint2,maxix,miniy);					
//DeadCode RJS 19May00 //deadcode   		POLYGON.createvert(dopoint1,maxix,maxiy);					
//DeadCode RJS 19May00 //deadcode  		POLYGON.createvert(dopoint0,minix,maxiy);					
//DeadCode RJS 19May00    																
//DeadCode RJS 19May00 //deadcode   		POLYGON.drawpoly();									
//DeadCode RJS 19May00   
//DeadCode RJS 19May00 //DEAD   		POLYGON.SetPixelWidth(1);
//DeadCode RJS 19May00 //deadcode	}
//DeadCode RJS 19May00    
//DeadCode RJS 19May00 //DEAD   	POLYGON.SetCrossProduct(oldcross);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		plaintrailcyl
//Author		Robert Slater
//Date			Mon 12 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::plaintrailcyl(	UWord   vertex1,
							UWord	vertex2,
							SWord	col,
							SWord	xoff0, SWord yoff0,
							SWord	xoff1, SWord yoff1,
							SWord	fadedepth			)
{
//DeadCode RJS 19May00 	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	xoff0 = (xoff0 * 90)>>7;
//DeadCode RJS 19May00 	xoff1 = (xoff1 * 90)>>7;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	yoff0 = (yoff0 * 90)>>7;
//DeadCode RJS 19May00 	yoff1 = (yoff1 * 90)>>7;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00  	Float	xdelt1 = (Float) xoff0;
//DeadCode RJS 19May00  	Float	ydelt1 = (Float) yoff0;
//DeadCode RJS 19May00  	Float	xdelt2 = (Float) xoff1;
//DeadCode RJS 19May00  	Float	ydelt2 = (Float) yoff1;
//DeadCode RJS 19May00  	Bool	oldcross;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	if (fadedepth < SMOKED_LIGHT)
//DeadCode RJS 19May00 		return;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //DEAD  	oldcross = POLYGON.SetCrossProduct(FALSE);
//DeadCode RJS 19May00   
//DeadCode RJS 19May00    	dopoint0 = dopoint1 = newco[vertex1];				
//DeadCode RJS 19May00    	dopoint2 = dopoint3 = newco[vertex2];
//DeadCode RJS 19May00 
//DeadCode RJS 19May00   	dopoint0.bodyx.f += xdelt1;								
//DeadCode RJS 19May00   	dopoint0.bodyy.f += ydelt1;								
//DeadCode RJS 19May00 //deadcode	_matrix.SetClipFlags(dopoint0);
//DeadCode RJS 19May00  
//DeadCode RJS 19May00   	dopoint1.bodyx.f += -xdelt1;								
//DeadCode RJS 19May00  	dopoint1.bodyy.f += -ydelt1;								
//DeadCode RJS 19May00 //deadcode	_matrix.SetClipFlags(dopoint1);
//DeadCode RJS 19May00  
//DeadCode RJS 19May00    	dopoint2.bodyx.f += -xdelt2;								
//DeadCode RJS 19May00    	dopoint2.bodyy.f += -ydelt2;								
//DeadCode RJS 19May00 //deadcode	_matrix.SetClipFlags(dopoint2);
//DeadCode RJS 19May00  
//DeadCode RJS 19May00    	dopoint3.bodyx.f += xdelt2;								
//DeadCode RJS 19May00    	dopoint3.bodyy.f += ydelt2;								
//DeadCode RJS 19May00 //deadcode	_matrix.SetClipFlags(dopoint3);
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //deadcode	andedFlags=CF3D_ALL;
//DeadCode RJS 19May00 //deadcode	andedFlags&=dopoint0.clipFlags;
//DeadCode RJS 19May00 //deadcode	andedFlags&=dopoint1.clipFlags;
//DeadCode RJS 19May00 //deadcode	andedFlags&=dopoint2.clipFlags;
//DeadCode RJS 19May00 //deadcode	andedFlags&=dopoint3.clipFlags;
//DeadCode RJS 19May00 //deadcode	if (andedFlags==0)
//DeadCode RJS 19May00 	{
//DeadCode RJS 19May00 //		if (!doingHW3D)
//DeadCode RJS 19May00 //		{
//DeadCode RJS 19May00 //			_matrix.body2screen(dopoint0);
//DeadCode RJS 19May00 //			_matrix.body2screen(dopoint1);
//DeadCode RJS 19May00 //			_matrix.body2screen(dopoint2);
//DeadCode RJS 19May00 //			_matrix.body2screen(dopoint3);
//DeadCode RJS 19May00 //		}
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,fadedepth);
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //DEAD   		POLYGON.SetPixelWidth(1);			
//DeadCode RJS 19May00 		R3DVERTEX *pRVerts;
//DeadCode RJS 19May00 		g_lpLib3d->BeginPoly(HMATERIAL(col),4,pRVerts);
//DeadCode RJS 19May00 		*pRVerts++=dopoint0;
//DeadCode RJS 19May00 		*pRVerts++=dopoint1;
//DeadCode RJS 19May00 		*pRVerts++=dopoint2;
//DeadCode RJS 19May00 		*pRVerts++=dopoint3;
//DeadCode RJS 19May00 		g_lpLib3d->EndPoly();
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //deadcode   		POLYGON.createpoly((Colour)col);								
//DeadCode RJS 19May00    																
//DeadCode RJS 19May00 //deadcode 		POLYGON.createvert(dopoint0);					
//DeadCode RJS 19May00 //deadcode   		POLYGON.createvert(dopoint1);					
//DeadCode RJS 19May00 //deadcode   		POLYGON.createvert(dopoint2);					
//DeadCode RJS 19May00 //deadcode  		POLYGON.createvert(dopoint3);					
//DeadCode RJS 19May00    																
//DeadCode RJS 19May00 //deadcode   		POLYGON.drawpoly();									
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,SMOKED_OFF);
//DeadCode RJS 19May00 	}
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //DEAD   	POLYGON.SetCrossProduct(oldcross);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LineStream
//Author		Robert Slater
//Date			Mon 5 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::LineStream(	UWord	vertex0,
						 	UWord	vertex1,
						 	SWord	xoff0, SWord yoff0,
							SWord	xoff1, SWord yoff1,
							UWord	depth,
							SWord	StartRadius,
							SWord	EndRadius,
							MyGroundVectorPtr	WCylStartP,
							MyGroundVectorPtr	WCylEndP,
							SWord	col,
							SWord	transdepth	)
{
//DeadCode RJS 19May00 	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
//DeadCode RJS 19May00  	Bool	oldcross;
//DeadCode RJS 19May00 	Float	RelX, RelY, RelZ;
//DeadCode RJS 19May00 	Float	RelXStep,RelYStep, RelZStep;
//DeadCode RJS 19May00 	UWord	counter;
//DeadCode RJS 19May00 	SLong	xDelta,yDelta;
//DeadCode RJS 19May00 	SLong	RandxDelta,RandyDelta;
//DeadCode RJS 19May00 	SLong	xDeltCap,yDeltCap;
//DeadCode RJS 19May00 	UWord	RSeed;
//DeadCode RJS 19May00 	SLong	XoffGap;
//DeadCode RJS 19May00 	SLong	YoffGap;
//DeadCode RJS 19May00 	SLong	Radius;
//DeadCode RJS 19May00 	SWord	MaxRadius;
//DeadCode RJS 19May00 	SWord	RadStep;
//DeadCode RJS 19May00 	SLong	wXStep, wYStep, wZStep;								
//DeadCode RJS 19May00 	SLong	wXStart, wYStart, wZStart;							
//DeadCode RJS 19May00 	Colour	thecol = (Colour) col;
//DeadCode RJS 19May00 	SLong	MaxDist, Dist;
//DeadCode RJS 19May00 	DOSETCOLOUR256	tmpinst3;									//RJS 08Jan98
//DeadCode RJS 19May00 	UByteP	tmpinstptr;
//DeadCode RJS 19May00 	DOLINE	lineinst;
//DeadCode RJS 19May00 	DoPointStruc	*dp0ptr,*dp1ptr;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	dp0ptr = &newco[2];
//DeadCode RJS 19May00 	dp1ptr = &newco[3];
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	lineinst.start_vertex = 2;
//DeadCode RJS 19May00 	lineinst.end_vertex = 3;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	tmpinst3.basecolour = thecol<<1;							//RJS 08Jan98
//DeadCode RJS 19May00 	tmpinst3.spread = 0;										//RJS 08Jan98
//DeadCode RJS 19May00 	tmpinst3.imap = 0xFF;										//RJS 08Jan98
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	tmpinstptr = (UByteP) &tmpinst3;							//RJS 08Jan98
//DeadCode RJS 19May00 	dosetcolour256(tmpinstptr);									//RJS 08Jan98
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //DeadCode RJS 30Mar98 	if (transdepth == SMOKED_SOLID)
//DeadCode RJS 19May00 //DeadCode RJS 30Mar98 		transdepth = SMOKED_OFF;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	wXStart = WCylStartP->gx;									
//DeadCode RJS 19May00 	wYStart = WCylStartP->gy;									
//DeadCode RJS 19May00 	wZStart = WCylStartP->gz;									
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //DEAD 	oldcross = POLYGON.SetCrossProduct(FALSE);
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	dopointRoot = newco[vertex0];								
//DeadCode RJS 19May00    	dopoint2 = newco[vertex1];
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	RelX = dopoint2.bodyx.f - dopointRoot.bodyx.f;
//DeadCode RJS 19May00 	RelY = dopoint2.bodyy.f - dopointRoot.bodyy.f;
//DeadCode RJS 19May00 	RelZ = dopoint2.bodyz.f - dopointRoot.bodyz.f;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	wXStep = (WCylEndP->gx - wXStart) / depth;					
//DeadCode RJS 19May00 	wYStep = (WCylEndP->gy - wYStart) / depth;					
//DeadCode RJS 19May00 	wZStep = (WCylEndP->gz - wZStart) / depth;					
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	XoffGap = (xoff1 - xoff0)/depth;
//DeadCode RJS 19May00 	YoffGap = (yoff1 - yoff0)/depth;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	RelXStep = RelX / depth;
//DeadCode RJS 19May00 	RelYStep = RelY / depth;
//DeadCode RJS 19May00 	RelZStep = RelZ / depth;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	RadStep = (EndRadius - StartRadius)/depth;
//DeadCode RJS 19May00 	MaxRadius = StartRadius;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	xDelta = xoff0;
//DeadCode RJS 19May00 	yDelta = yoff0;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //DEAD 	POLYGON.SetPixelWidth(1);
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	SLong	xloff, yloff, zloff;
//DeadCode RJS 19May00 	g_lpLib3d->SetGlobal(TOGGLE_GLOBALTRANSPARENCY,ULong(transdepth));
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	for (counter = 0; counter < depth; counter++)
//DeadCode RJS 19May00 	{
//DeadCode RJS 19May00 		tmpinstptr = (UByteP)&lineinst;
//DeadCode RJS 19May00 		RSeed = Noise(wXStart,wYStart,wZStart);					//RJS 11Mar98
//DeadCode RJS 19May00 																//RJS 11Mar98
//DeadCode RJS 19May00 		RandxDelta = ((RSeed*xDelta)>>7) - xDelta;				//RJS 11Mar98
//DeadCode RJS 19May00 		RandyDelta = ((RSeed*yDelta)>>7) - yDelta;				//RJS 11Mar98
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		*dp0ptr = dopointRoot;									//RJS 11Mar98
//DeadCode RJS 19May00 		dp0ptr->bodyx.f += RandxDelta;							//RJS 11Mar98
//DeadCode RJS 19May00 		dp0ptr->bodyy.f += RandyDelta;							//RJS 11Mar98
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		if (dp0ptr->bodyz.f > 100)								
//DeadCode RJS 19May00 		{
//DeadCode RJS 19May00 			*dp1ptr = *dp0ptr;									//RJS 11Mar98
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 			RSeed = 256 - RSeed;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 			xloff = RSeed * RelXStep;
//DeadCode RJS 19May00 			yloff = RSeed * RelYStep;
//DeadCode RJS 19May00 			zloff = RSeed * RelZStep;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 			xloff >>= 9;
//DeadCode RJS 19May00 			yloff >>= 9;
//DeadCode RJS 19May00 			zloff >>= 9;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 			dp0ptr->bodyx.f += xloff;							//RJS 11Mar98
//DeadCode RJS 19May00 			dp0ptr->bodyy.f += yloff;							//RJS 11Mar98
//DeadCode RJS 19May00 			dp0ptr->bodyz.f += zloff;							//RJS 11Mar98
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 			dp1ptr->bodyx.f -= xloff;							//RJS 11Mar98
//DeadCode RJS 19May00 			dp1ptr->bodyy.f -= yloff;							//RJS 11Mar98
//DeadCode RJS 19May00 			dp1ptr->bodyz.f -= zloff;							//RJS 11Mar98
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 			doline(tmpinstptr);									//RJS 11Mar98
//DeadCode RJS 19May00 		}
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		dopointRoot.bodyx.f += RelXStep;
//DeadCode RJS 19May00 		dopointRoot.bodyy.f += RelYStep;
//DeadCode RJS 19May00   		dopointRoot.bodyz.f += RelZStep;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		xDelta += XoffGap;
//DeadCode RJS 19May00 		yDelta += YoffGap;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		wXStart += wXStep;										//RJS 12Nov97
//DeadCode RJS 19May00 		wYStart += wYStep;										//RJS 12Nov97
//DeadCode RJS 19May00 		wZStart += wZStep;										//RJS 12Nov97
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		MaxRadius += RadStep;
//DeadCode RJS 19May00 	}
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	g_lpLib3d->SetGlobal(TOGGLE_GLOBALTRANSPARENCY,ULong(SMOKED_OFF));
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 //DEAD 	POLYGON.SetCrossProduct(oldcross);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlainBlobLine
//Author		Robert Slater
//Date			Thu 11 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode RJS 07Feb00void	shape::PlainBlobLine(	UWord	vertex0,
//DeadCode RJS 07Feb00							 	UWord	vertex1,
//DeadCode RJS 07Feb00								UWord	MaxRadius)
//DeadCode RJS 07Feb00{
//DeadCode RJS 07Feb00 	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot;
//DeadCode RJS 07Feb00  	Bool	oldcross;
//DeadCode RJS 07Feb00 	SLong	RelX, RelY, RelZ;
//DeadCode RJS 07Feb00 	SLong	RelXStep, RelYStep, RelZStep;
//DeadCode RJS 07Feb00 	UWord	counter;
//DeadCode RJS 07Feb00 	UWord	RSeed;
//DeadCode RJS 07Feb00 	SLong	Radius,RealRadius;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 //DEAD 	oldcross = POLYGON.SetCrossProduct(FALSE);
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	dopointRoot = newco[vertex0];
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	RelX = newco[vertex1].bodyx.f - newco[vertex0].bodyx.f;
//DeadCode RJS 07Feb00 	RelY = newco[vertex1].bodyy.f - newco[vertex0].bodyy.f;
//DeadCode RJS 07Feb00 	RelZ = newco[vertex1].bodyz.f - newco[vertex0].bodyz.f;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	RelXStep = RelX / 2;
//DeadCode RJS 07Feb00 	RelYStep = RelY / 2;
//DeadCode RJS 07Feb00 	RelZStep = RelZ / 2;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	Radius = MaxRadius;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	dopoint0 = dopointRoot;
//DeadCode RJS 07Feb00 	dopoint0.bodyx.f += RelXStep;
//DeadCode RJS 07Feb00 	dopoint0.bodyy.f += RelXStep;
//DeadCode RJS 07Feb00 	dopoint0.bodyz.f += RelXStep;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	dopoint2 = dopoint0;
//DeadCode RJS 07Feb00 	dopoint2.bodyx.f += Radius;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 //deadcode	_matrix.SetClipFlags(dopoint0);
//DeadCode RJS 07Feb00 //deadcode	_matrix.SetClipFlags(dopoint2);
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	R3DVALUE screenx0,screeny0,screenx2,screeny2;
//DeadCode RJS 07Feb00 	g_lpLib3d->BodyToScreen(dopoint0,screenx0,screeny0,screenz);//RJS 07Feb00
//DeadCode RJS 07Feb00 	g_lpLib3d->BodyToScreen(dopoint2,screenx2,screeny2,screenz);//RJS 07Feb00
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 //deadcode	_matrix.body2screen(dopoint0);
//DeadCode RJS 07Feb00 //deadcode	_matrix.body2screen(dopoint2);
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	RealRadius = screenx2 - screenx0;
//DeadCode RJS 07Feb00 	if (RealRadius)
//DeadCode RJS 07Feb00 	{
//DeadCode RJS 07Feb00 		g_lpLib3d->DrawSphere(HMATERIAL(shape::colour),dopoint0,RealRadius,ANGLES_0Deg,0,0,0,0);
//DeadCode RJS 07Feb00 //deadcode		POLYGON.createsphere(shape::colour,SMOKED_SOLID);			
//DeadCode RJS 07Feb00 //deadcode		POLYGON.createsphvert(dopoint0,RealRadius);				
//DeadCode RJS 07Feb00 //deadcode		POLYGON.drawsphere();
//DeadCode RJS 07Feb00 	}
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 //deadcode	POLYGON.SetOpacityON();
//DeadCode RJS 07Feb00 //DEAD 	POLYGON.SetPixelWidth(1);
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	dopoint1 = dopoint0;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	while (Radius > 2)
//DeadCode RJS 07Feb00 	{
//DeadCode RJS 07Feb00 		RelXStep /= 2;
//DeadCode RJS 07Feb00 		RelYStep /= 2;
//DeadCode RJS 07Feb00 		RelZStep /= 2;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		Radius /= 2;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		dopoint0.bodyx.f -= RelXStep;
//DeadCode RJS 07Feb00 		dopoint0.bodyy.f -= RelXStep;
//DeadCode RJS 07Feb00 		dopoint0.bodyz.f -= RelXStep;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		dopoint2 = dopoint0;
//DeadCode RJS 07Feb00 		dopoint2.bodyx.f += Radius;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		dopoint1.bodyx.f += RelXStep;
//DeadCode RJS 07Feb00 		dopoint1.bodyy.f += RelXStep;
//DeadCode RJS 07Feb00 		dopoint1.bodyz.f += RelXStep;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		dopoint3 = dopoint1;
//DeadCode RJS 07Feb00 		dopoint3.bodyx.f += Radius;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 //deadcode		_matrix.SetClipFlags(dopoint0);
//DeadCode RJS 07Feb00 //deadcode		_matrix.SetClipFlags(dopoint1);
//DeadCode RJS 07Feb00 //deadcode		_matrix.SetClipFlags(dopoint2);
//DeadCode RJS 07Feb00 //deadcode		_matrix.SetClipFlags(dopoint3);
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		R3DVALUE screenx0,screeny0,screenx1,screeny1,screenx2,screeny2,screenx3,screeny3;
//DeadCode RJS 07Feb00 		g_lpLib3d->BodyToScreen(dopoint0,screenx0,screeny0,screenz);//RJS 07Feb00
//DeadCode RJS 07Feb00 		g_lpLib3d->BodyToScreen(dopoint1,screenx1,screeny1,screenz);//RJS 07Feb00
//DeadCode RJS 07Feb00 		g_lpLib3d->BodyToScreen(dopoint2,screenx2,screeny2,screenz);//RJS 07Feb00
//DeadCode RJS 07Feb00 		g_lpLib3d->BodyToScreen(dopoint3,screenx3,screeny3,screenz);//RJS 07Feb00
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		RealRadius = screenx2 - screenx0;
//DeadCode RJS 07Feb00 		if (RealRadius)
//DeadCode RJS 07Feb00 		{
//DeadCode RJS 07Feb00 			g_lpLib3d->DrawSphere(HMATERIAL(shape::colour),dopoint0,RealRadius,ANGLES_0Deg,0,0,0,0);
//DeadCode RJS 07Feb00 //deadcode			POLYGON.createsphere(shape::colour,SMOKED_SOLID);			
//DeadCode RJS 07Feb00 //deadcode			POLYGON.createsphvert(dopoint0,RealRadius);				
//DeadCode RJS 07Feb00 //deadcode			POLYGON.drawsphere();
//DeadCode RJS 07Feb00 		}
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		RealRadius = screenx3 - screenx1;
//DeadCode RJS 07Feb00 		if (RealRadius)
//DeadCode RJS 07Feb00 		{
//DeadCode RJS 07Feb00 			g_lpLib3d->DrawSphere(HMATERIAL(shape::colour),dopoint1,RealRadius,ANGLES_0Deg,0,0,0,0);
//DeadCode RJS 07Feb00 //deadcode			POLYGON.createsphere(shape::colour,SMOKED_SOLID);			
//DeadCode RJS 07Feb00 //deadcode			POLYGON.createsphvert(dopoint1,RealRadius);				
//DeadCode RJS 07Feb00 //deadcode			POLYGON.drawsphere();							
//DeadCode RJS 07Feb00 		}
//DeadCode RJS 07Feb00 	}
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 //deadcode	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97
//DeadCode RJS 07Feb00 	g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,SMOKED_OFF);
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 //DEAD 	POLYGON.SetCrossProduct(oldcross);
//DeadCode RJS 07Feb00}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ParticleBoxPlain
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
//DeadCode RJS 07Feb00void	shape::ParticleBoxPlain(	UWord	vertex0,
//DeadCode RJS 07Feb00							 		UWord	vertex1,
//DeadCode RJS 07Feb00									UWord	width,
//DeadCode RJS 07Feb00									UWord	height,
//DeadCode RJS 07Feb00									UWord	length,
//DeadCode RJS 07Feb00							 		MyGroundVectorPtr	WCylStartP,
//DeadCode RJS 07Feb00							 		SWord	col,
//DeadCode RJS 07Feb00									SWord	cvar,
//DeadCode RJS 07Feb00									SWord	fadedepth,
//DeadCode RJS 07Feb00									Bool	fuzzy)
//DeadCode RJS 07Feb00{
//DeadCode RJS 07Feb00 	DoPointStruc dopoint0,dopoint1,dopointRoot;
//DeadCode RJS 07Feb00  	Bool	oldcross;
//DeadCode RJS 07Feb00 	SLong	RelX, RelY, RelZ;
//DeadCode RJS 07Feb00 	SLong	RelX2, RelY2, RelZ2;
//DeadCode RJS 07Feb00 	SLong	RelX3, RelY3, RelZ3;
//DeadCode RJS 07Feb00 	UWord	counter;
//DeadCode RJS 07Feb00 	UWord	RSeed;
//DeadCode RJS 07Feb00 	SLong	Radius;
//DeadCode RJS 07Feb00 	SLong	wXStep, wYStep, wZStep;								
//DeadCode RJS 07Feb00 	SLong	wXStart, wYStart, wZStart;							
//DeadCode RJS 07Feb00 	Colour	thecol = (Colour) col;
//DeadCode RJS 07Feb00 	SLong	MaxDist, Dist;
//DeadCode RJS 07Feb00 	SLong	MaxRadius;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	wXStart = WCylStartP->gx;									
//DeadCode RJS 07Feb00 	wYStart = WCylStartP->gy;									
//DeadCode RJS 07Feb00 	wZStart = WCylStartP->gz;									
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 //DEAD 	oldcross = POLYGON.SetCrossProduct(FALSE);
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	dopointRoot = newco[vertex0];								
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	RelX = width;
//DeadCode RJS 07Feb00 	RelY = height;
//DeadCode RJS 07Feb00 	RelZ = length;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	SLong depth = 1 + ((RelX * RelY * RelZ)/230000);
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	MaxRadius = ((RelX/2) + (RelY/2) + (RelZ/2))/3;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	RelX2 = RelX;
//DeadCode RJS 07Feb00 	RelY2 = RelY;
//DeadCode RJS 07Feb00 	RelZ2 = RelZ;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	RelX /= 2;
//DeadCode RJS 07Feb00 	RelY /= 2;
//DeadCode RJS 07Feb00 	RelZ /= 2;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	RelX3 = (RelX<0)?-RelX:RelX;
//DeadCode RJS 07Feb00 	RelY3 = (RelY<0)?-RelY:RelY;
//DeadCode RJS 07Feb00 	RelZ3 = (RelZ<0)?-RelZ:RelZ;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 //deadcode	POLYGON.SetOpacityON();
//DeadCode RJS 07Feb00 //DEAD 	POLYGON.SetPixelWidth(1);
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	SLong	randx,Spazx,Spazx2,Distx;
//DeadCode RJS 07Feb00 	SLong	randy,Spazy,Spazy2,Disty;
//DeadCode RJS 07Feb00 	SLong	randz,Spazz,Spazz2,Distz;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	Spazx2 = dopointRoot.bodyx.f + RelX;
//DeadCode RJS 07Feb00 	Spazy2 = dopointRoot.bodyy.f + RelY;
//DeadCode RJS 07Feb00 	Spazz2 = dopointRoot.bodyz.f + RelZ;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	if (fuzzy)
//DeadCode RJS 07Feb00 	{
//DeadCode RJS 07Feb00 		for (counter = 0; counter < depth; counter++)
//DeadCode RJS 07Feb00 		{
//DeadCode RJS 07Feb00 			randx = (Math_Lib.rnd()*RelX2)>>16;
//DeadCode RJS 07Feb00 			randy = (Math_Lib.rnd()*RelY2)>>16;
//DeadCode RJS 07Feb00 			randz = (Math_Lib.rnd()*RelZ2)>>16;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			Spazx = randx + dopointRoot.bodyx.f;
//DeadCode RJS 07Feb00 			Spazy = randy + dopointRoot.bodyy.f;
//DeadCode RJS 07Feb00 			Spazz = randz + dopointRoot.bodyz.f;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			Distx = Spazx - Spazx2;
//DeadCode RJS 07Feb00 			Disty = Spazy - Spazy2;
//DeadCode RJS 07Feb00 			Distz = Spazz - Spazz2;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			Distx = (Distx<0)?-Distx:Distx;
//DeadCode RJS 07Feb00 			Disty = (Disty<0)?-Disty:Disty;
//DeadCode RJS 07Feb00 			Distz = (Distz<0)?-Distz:Distz;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			Radius = (	((MaxRadius*(RelX3 - Distx))/RelX3)
//DeadCode RJS 07Feb00 				  	+ ((MaxRadius*(RelY3 - Disty))/RelY3)
//DeadCode RJS 07Feb00 				  	+ ((MaxRadius*(RelZ3 - Distz))/RelZ3)	)/3;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			thecol = (Colour) (col - (((MaxRadius - Radius)*cvar)/MaxRadius));
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			dopoint0.bodyx.f = Spazx;
//DeadCode RJS 07Feb00 			dopoint0.bodyy.f = Spazy;
//DeadCode RJS 07Feb00 			dopoint0.bodyz.f = Spazz;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			dopoint1 = dopoint0;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 //deadcode			_matrix.SetClipFlags(dopoint0);
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			R3DVALUE screenx0,screeny0;
//DeadCode RJS 07Feb00 			g_lpLib3d->BodyToScreen(dopoint0,screenx0,screeny0,screenz);//RJS 07Feb00
//DeadCode RJS 07Feb00 //deadcode			_matrix.body2screen(dopoint0);
//DeadCode RJS 07Feb00 			dopoint1.bodyx.f += Radius;
//DeadCode RJS 07Feb00 //deadcode			_matrix.SetClipFlags(dopoint1);
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			R3DVALUE screenx1,screeny1;
//DeadCode RJS 07Feb00 			g_lpLib3d->BodyToScreen(dopoint1,screenx1,screeny1,screenz);//RJS 07Feb00
//DeadCode RJS 07Feb00 //deadcode			_matrix.body2screen(dopoint1);
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			Radius = screenx1 - screenx0;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			if (Radius)
//DeadCode RJS 07Feb00 			{
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 				g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,fadedepth);
//DeadCode RJS 07Feb00 				g_lpLib3d->DrawSphere(HMATERIAL(thecol),dopoint0,Radius,ANGLES_0Deg,0,0,0,0);
//DeadCode RJS 07Feb00 //deadcode				POLYGON.createsphere(thecol,fadedepth);			//RJS 04Dec97
//DeadCode RJS 07Feb00 //deadcode				POLYGON.createsphvert(dopoint0,Radius);				//RJS 04Dec97
//DeadCode RJS 07Feb00 //deadcode				POLYGON.drawsphere();								//RJS 04Dec97
//DeadCode RJS 07Feb00 			}
//DeadCode RJS 07Feb00 		}
//DeadCode RJS 07Feb00 	}
//DeadCode RJS 07Feb00 	else
//DeadCode RJS 07Feb00 	{
//DeadCode RJS 07Feb00 		for (counter = 0; counter < depth; counter++)
//DeadCode RJS 07Feb00 		{
//DeadCode RJS 07Feb00 			RSeed = Noise(wXStart,wYStart,wZStart);
//DeadCode RJS 07Feb00 			wXStart += 16;
//DeadCode RJS 07Feb00 			wYStart += 16;
//DeadCode RJS 07Feb00 			wZStart += 16;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			randx = (RSeed*RelX2)>>8;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			RSeed = Noise(wXStart,wYStart,wZStart);
//DeadCode RJS 07Feb00 			wXStart += 16;
//DeadCode RJS 07Feb00 			wYStart += 16;
//DeadCode RJS 07Feb00 			wZStart += 16;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			randy = (RSeed*RelY2)>>8;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			RSeed = Noise(wXStart,wYStart,wZStart);
//DeadCode RJS 07Feb00 			wXStart += 16;
//DeadCode RJS 07Feb00 			wYStart += 16;
//DeadCode RJS 07Feb00 			wZStart += 16;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			randz = (RSeed*RelZ2)>>8;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			Spazx = randx + dopointRoot.bodyx.f;
//DeadCode RJS 07Feb00 			Spazy = randy + dopointRoot.bodyy.f;
//DeadCode RJS 07Feb00 			Spazz = randz + dopointRoot.bodyz.f;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			Distx = Spazx - Spazx2;
//DeadCode RJS 07Feb00 			Disty = Spazy - Spazy2;
//DeadCode RJS 07Feb00 			Distz = Spazz - Spazz2;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			Distx = (Distx<0)?-Distx:Distx;
//DeadCode RJS 07Feb00 			Disty = (Disty<0)?-Disty:Disty;
//DeadCode RJS 07Feb00 			Distz = (Distz<0)?-Distz:Distz;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			Radius = (	((MaxRadius*(RelX3 - Distx))/RelX3)
//DeadCode RJS 07Feb00 				  	+ ((MaxRadius*(RelY3 - Disty))/RelY3)
//DeadCode RJS 07Feb00 				  	+ ((MaxRadius*(RelZ3 - Distz))/RelZ3)	)/3;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			thecol = (Colour) (col - (((MaxRadius - Radius)*cvar)/MaxRadius));
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			dopoint0.bodyx.f = Spazx;
//DeadCode RJS 07Feb00 			dopoint0.bodyy.f = Spazy;
//DeadCode RJS 07Feb00 			dopoint0.bodyz.f = Spazz;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			dopoint1 = dopoint0;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 //deadcode			_matrix.SetClipFlags(dopoint0);
//DeadCode RJS 07Feb00 			R3DVALUE screenx0,screeny0;
//DeadCode RJS 07Feb00 			g_lpLib3d->BodyToScreen(dopoint0,screenx0,screeny0,screenz);//RJS 07Feb00
//DeadCode RJS 07Feb00 //deadcode			_matrix.body2screen(dopoint0);
//DeadCode RJS 07Feb00 			dopoint1.bodyx.f += Radius;
//DeadCode RJS 07Feb00 //deadcode			_matrix.SetClipFlags(dopoint1);
//DeadCode RJS 07Feb00 			R3DVALUE screenx1,screeny1;
//DeadCode RJS 07Feb00 			g_lpLib3d->BodyToScreen(dopoint1,screenx1,screeny1,screenz);//RJS 07Feb00
//DeadCode RJS 07Feb00 //deadcode			_matrix.body2screen(dopoint1);
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			Radius = screenx1 - screenx0;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			if (Radius)
//DeadCode RJS 07Feb00 			{
//DeadCode RJS 07Feb00 				g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,fadedepth);
//DeadCode RJS 07Feb00 				g_lpLib3d->DrawSphere(HMATERIAL(thecol),dopoint0,Radius,ANGLES_0Deg,0,0,0,0);
//DeadCode RJS 07Feb00 //deadcode				POLYGON.createsphere(thecol,fadedepth);			//RJS 04Dec97
//DeadCode RJS 07Feb00 //deadcode				POLYGON.createsphvert(dopoint0,Radius);				//RJS 04Dec97
//DeadCode RJS 07Feb00 //deadcode				POLYGON.drawsphere();								//RJS 04Dec97
//DeadCode RJS 07Feb00 			}
//DeadCode RJS 07Feb00 		}
//DeadCode RJS 07Feb00 	}
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,SMOKED_OFF);
//DeadCode RJS 07Feb00 //deadcode	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 //DEAD 	POLYGON.SetCrossProduct(oldcross);
//DeadCode RJS 07Feb00}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ParticleStream
//Author		Robert Slater
//Date			Tue 4 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE JON 4/12/00 void	shape::ParticleStreamPlain(	UWord	vertex0,
//DEADCODE JON 4/12/00 							 		UWord	vertex1,
//DEADCODE JON 4/12/00 							 		SWord	xoff0, SWord yoff0,
//DEADCODE JON 4/12/00 							 		SWord	xoff1, SWord yoff1,
//DEADCODE JON 4/12/00 							 		UWord	depth,
//DEADCODE JON 4/12/00 							 		SWord	StartRadius,
//DEADCODE JON 4/12/00 									SWord	EndRadius,
//DEADCODE JON 4/12/00 							 		MyGroundVectorPtr	WCylStartP,
//DEADCODE JON 4/12/00 							 		MyGroundVectorPtr	WCylEndP,
//DEADCODE JON 4/12/00 							 		SWord	col,
//DEADCODE JON 4/12/00 							 		SWord	transdepth)
//DEADCODE JON 4/12/00 {
//DEADCODE JON 4/12/00 	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
//DEADCODE JON 4/12/00  	Bool	oldcross;
//DEADCODE JON 4/12/00 	Float	RelX, RelY, RelZ;
//DEADCODE JON 4/12/00 	Float	RelXStep,RelYStep, RelZStep;
//DEADCODE JON 4/12/00 	UWord	counter;
//DEADCODE JON 4/12/00 	SLong	xDelta,yDelta;
//DEADCODE JON 4/12/00 	SLong	RandxDelta,RandyDelta;
//DEADCODE JON 4/12/00 	SLong	xDeltCap,yDeltCap;
//DEADCODE JON 4/12/00 	UWord	RSeed;
//DEADCODE JON 4/12/00 	SLong	XoffGap;
//DEADCODE JON 4/12/00 	SLong	YoffGap;
//DEADCODE JON 4/12/00 	SLong	Radius;
//DEADCODE JON 4/12/00 	SWord	MaxRadius;
//DEADCODE JON 4/12/00 	SWord	RadStep;
//DEADCODE JON 4/12/00 	SLong	wXStep, wYStep, wZStep;								
//DEADCODE JON 4/12/00 	SLong	wXStart, wYStart, wZStart;							
//DEADCODE JON 4/12/00 	Colour	thecol = (Colour) col;
//DEADCODE JON 4/12/00 	SLong	MaxDist, Dist;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	depth = 1 + (depth >> 1);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	wXStart = WCylStartP->gx;									
//DEADCODE JON 4/12/00 	wYStart = WCylStartP->gy;									
//DEADCODE JON 4/12/00 	wZStart = WCylStartP->gz;									
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 //DEAD 	oldcross = POLYGON.SetCrossProduct(FALSE);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	if (newco[vertex1].bodyz.f > newco[vertex0].bodyz.f)		//RJS 09Jul98
//DEADCODE JON 4/12/00 	{															//RJS 09Jul98
//DEADCODE JON 4/12/00 		SLong	vswap = vertex0;								//RJS 09Jul98
//DEADCODE JON 4/12/00 		vertex0 = vertex1;										//RJS 09Jul98
//DEADCODE JON 4/12/00 		vertex1 = vswap;										//RJS 09Jul98
//DEADCODE JON 4/12/00 	}															//RJS 09Jul98
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	dopointRoot = newco[vertex0];								
//DEADCODE JON 4/12/00    	dopoint2 = newco[vertex1];
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	RelX = dopoint2.bodyx.f - dopointRoot.bodyx.f;
//DEADCODE JON 4/12/00 	RelY = dopoint2.bodyy.f - dopointRoot.bodyy.f;
//DEADCODE JON 4/12/00 	RelZ = dopoint2.bodyz.f - dopointRoot.bodyz.f;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	wXStep = (WCylEndP->gx - wXStart) / depth;					
//DEADCODE JON 4/12/00 	wYStep = (WCylEndP->gy - wYStart) / depth;					
//DEADCODE JON 4/12/00 	wZStep = (WCylEndP->gz - wZStart) / depth;					
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	XoffGap = (xoff1 - xoff0)/depth;
//DEADCODE JON 4/12/00 	YoffGap = (yoff1 - yoff0)/depth;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	RelXStep = RelX / depth;
//DEADCODE JON 4/12/00 	RelYStep = RelY / depth;
//DEADCODE JON 4/12/00 	RelZStep = RelZ / depth;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	RadStep = (EndRadius - StartRadius)/depth;
//DEADCODE JON 4/12/00 	MaxRadius = StartRadius;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	xDelta = xoff0;
//DEADCODE JON 4/12/00 	yDelta = yoff0;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 //deadcode	POLYGON.SetOpacityON();
//DEADCODE JON 4/12/00 //DEAD 	POLYGON.SetPixelWidth(1);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	for (counter = 0; counter < depth; counter++)
//DEADCODE JON 4/12/00 	{
//DEADCODE JON 4/12/00 		xDeltCap = xDelta << 1;
//DEADCODE JON 4/12/00 		yDeltCap = yDelta << 1;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		RSeed = Noise(wXStart,wYStart,wZStart);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		RandxDelta = (((RSeed*xDeltCap)>>8) - xDelta)>>3;			
//DEADCODE JON 4/12/00 		RandyDelta = (((RSeed*yDeltCap)>>8) - yDelta)>>3;			
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		dopoint0 = dopointRoot;
//DEADCODE JON 4/12/00 		dopoint0.bodyx.f += RandxDelta;
//DEADCODE JON 4/12/00 		dopoint0.bodyy.f += RandyDelta;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		if (dopoint0.bodyz.f > 100)								
//DEADCODE JON 4/12/00 		{
//DEADCODE JON 4/12/00 			dopoint1 = dopoint2 = dopoint3 = dopoint0;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 //deadcode			_matrix.SetClipFlags(dopoint0);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 			R3DVALUE screenx0,screeny0,screenz0;				//RJS 07Feb00
//DEADCODE JON 4/12/00 			g_lpLib3d->BodyToScreen(dopoint0,screenx0,screeny0,screenz0);//RJS 07Feb00
//DEADCODE JON 4/12/00 //deadcode			_matrix.body2screen(dopoint0);
//DEADCODE JON 4/12/00 			dopoint1.bodyx.f += MaxRadius;
//DEADCODE JON 4/12/00 //deadcode			_matrix.SetClipFlags(dopoint1);
//DEADCODE JON 4/12/00 			R3DVALUE screenx1,screeny1,screenz1;				//RJS 07Feb00
//DEADCODE JON 4/12/00 			g_lpLib3d->BodyToScreen(dopoint1,screenx1,screeny1,screenz1);//RJS 07Feb00
//DEADCODE JON 4/12/00 //deadcode			_matrix.body2screen(dopoint1);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 			Radius = screenx1 - screenx0;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 			g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,transdepth);
//DEADCODE JON 4/12/00 			g_lpLib3d->DrawSphere(HMATERIAL(thecol),dopoint0,Radius,ANGLES_0Deg,0,0,0,0);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 //deadcode			POLYGON.createsphere(thecol,transdepth);			//RJS 04Dec97
//DEADCODE JON 4/12/00 //deadcode			POLYGON.createsphvert(dopoint0,Radius);				//RJS 04Dec97
//DEADCODE JON 4/12/00 //deadcode			POLYGON.drawsphere();								//RJS 04Dec97
//DEADCODE JON 4/12/00 		}
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		dopointRoot.bodyx.f += RelXStep;
//DEADCODE JON 4/12/00 		dopointRoot.bodyy.f += RelYStep;
//DEADCODE JON 4/12/00   		dopointRoot.bodyz.f += RelZStep;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		xDelta += XoffGap;
//DEADCODE JON 4/12/00 		yDelta += YoffGap;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		wXStart += wXStep;										//RJS 12Nov97
//DEADCODE JON 4/12/00 		wYStart += wYStep;										//RJS 12Nov97
//DEADCODE JON 4/12/00 		wZStart += wZStep;										//RJS 12Nov97
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		MaxRadius += RadStep;
//DEADCODE JON 4/12/00 	}
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,SMOKED_OFF);
//DEADCODE JON 4/12/00 //deadcode	current_screen->SetTransparency(SMOKED_OFF);				//RJS 18Jun97
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 //DEAD 	POLYGON.SetCrossProduct(oldcross);
//DEADCODE JON 4/12/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		plaincylinder
//Author		Robert Slater
//Date			Tue 4 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE JON 4/12/00 void	shape::plaincylinder(UWord	vertex0,UWord	vertex1, UWord	radius)
//DEADCODE JON 4/12/00 {
//DEADCODE JON 4/12/00 	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3;
//DEADCODE JON 4/12/00 	SLong		xDelta, yDelta;
//DEADCODE JON 4/12/00 	Float		xoff, yoff;											
//DEADCODE JON 4/12/00   	SWord		angleofcylinder;									
//DEADCODE JON 4/12/00  	SWord		sin_ang,cos_ang;
//DEADCODE JON 4/12/00  	Bool		oldcross;
//DEADCODE JON 4/12/00  	Float		opposite, adjacent;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 //DEAD 	oldcross = POLYGON.SetCrossProduct(FALSE);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	dopoint0 = dopoint1 = newco[vertex0];										
//DEADCODE JON 4/12/00    	dopoint2 = dopoint3 = newco[vertex1];										
//DEADCODE JON 4/12/00  
//DEADCODE JON 4/12/00  	// Clip Z...
//DEADCODE JON 4/12/00  
//DEADCODE JON 4/12/00  	if (	(dopoint0.bodyz.f > 1.0)								//RJS 27Aug98
//DEADCODE JON 4/12/00  		||	(dopoint2.bodyz.f > 1.0)	)							//RJS 27Aug98
//DEADCODE JON 4/12/00  	{
//DEADCODE JON 4/12/00 //		if (doingHW3D)												//RJS 21Aug98
//DEADCODE JON 4/12/00 //		{															//RJS 21Aug98
//DEADCODE JON 4/12/00 //			_matrix.body2screen(dopoint0);							//RJS 21Aug98
//DEADCODE JON 4/12/00  //			_matrix.body2screen(dopoint2);							//RJS 21Aug98
//DEADCODE JON 4/12/00 //		}															//RJS 21Aug98
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		R3DVALUE screenx0,screeny0,screenz0,screenx2,screeny2,screenz2;//RJS 07Feb00
//DEADCODE JON 4/12/00 		g_lpLib3d->BodyToScreen(dopoint0,screenx0,screeny0,screenz0);//RJS 07Feb00
//DEADCODE JON 4/12/00 		g_lpLib3d->BodyToScreen(dopoint2,screenx2,screeny2,screenz2);//RJS 07Feb00
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		opposite = screeny0 - screeny2;		
//DEADCODE JON 4/12/00  		adjacent = screenx2 - screenx0;		
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		if (opposite && adjacent)
//DEADCODE JON 4/12/00 		{
//DEADCODE JON 4/12/00  			angleofcylinder = Math_Lib.HighArcTan(adjacent,opposite);
//DEADCODE JON 4/12/00  			angleofcylinder -= ANGLES_90Deg;
//DEADCODE JON 4/12/00  
//DEADCODE JON 4/12/00  			Math_Lib.high_sin_cos((Angles) angleofcylinder,sin_ang,cos_ang);	//PD 13Nov97
//DEADCODE JON 4/12/00  
//DEADCODE JON 4/12/00   			xDelta = (sin_ang * radius) >> ANGLES_SHIFT;				
//DEADCODE JON 4/12/00   			yDelta = (cos_ang * radius) >> ANGLES_SHIFT;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 //			if (ClipCylinder(dopoint0,dopoint1,dopoint2,dopoint3,xDelta,yDelta)==FALSE)//RJS 21Aug98
//DEADCODE JON 4/12/00 //			{
//DEADCODE JON 4/12/00 //DEAD 		 		POLYGON.SetPixelWidth(1<<Save_Data.pixelsize);			
//DEADCODE JON 4/12/00 //				R3DVERTEX *pRVerts;
//DEADCODE JON 4/12/00 //				g_lpLib3d->BeginPoly(HMATERIAL(shape::colour),4,pRVerts);
//DEADCODE JON 4/12/00 //				*pRVerts++=dopoint0;
//DEADCODE JON 4/12/00 //				*pRVerts++=dopoint1;
//DEADCODE JON 4/12/00 //				*pRVerts++=dopoint2;
//DEADCODE JON 4/12/00 //				*pRVerts++=dopoint3;
//DEADCODE JON 4/12/00 //				g_lpLib3d->EndPoly();
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 //deadcode 				POLYGON.createpoly(shape::colour);						
//DEADCODE JON 4/12/00 																	
//DEADCODE JON 4/12/00 //deadcode	  			POLYGON.createvert(dopoint0);					
//DEADCODE JON 4/12/00 //deadcode  				POLYGON.createvert(dopoint1);					
//DEADCODE JON 4/12/00 //deadcode  				POLYGON.createvert(dopoint2);					
//DEADCODE JON 4/12/00 //deadcode	  			POLYGON.createvert(dopoint3);					
//DEADCODE JON 4/12/00  																
//DEADCODE JON 4/12/00 //deadcode 				POLYGON.drawpoly();							
//DEADCODE JON 4/12/00  
//DEADCODE JON 4/12/00 //DEAD 				POLYGON.SetPixelWidth(1);
//DEADCODE JON 4/12/00 //			}
//DEADCODE JON 4/12/00 		}
//DEADCODE JON 4/12/00  	}
//DEADCODE JON 4/12/00  
//DEADCODE JON 4/12/00 //DEAD 	POLYGON.SetCrossProduct(oldcross);
//DEADCODE JON 4/12/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		imapcylinder
//Author		Robert Slater
//Date			Fri 16 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::imapcylinder(	UWord   vertex1,
							UWord 	vertex2,
							SLong 	radius,
							ImageMapNumber imapno,
							UWord	minix, UWord	miniy,
							UWord	width, UWord	height,
							UWord	frameno,
							UWord	depth	)					//RJS 20Nov98
{
//Old_Code RJS 08Feb00 //DeadCode RJS 21Apr99 	UByteP	adptr = (UByteP) object_obj3d->AnimPtr; 			
//Old_Code RJS 08Feb00 	SWord	minx, miny, maxx, maxy;								
//Old_Code RJS 08Feb00 	ULong	thewidth, theheight;
//Old_Code RJS 08Feb00 	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3;
//Old_Code RJS 08Feb00  	Float	xoff, yoff;											//RJS 20Feb97
//Old_Code RJS 08Feb00   	SWord	angleofcylinder;									
//Old_Code RJS 08Feb00  	SWord	sin_ang,cos_ang;
//Old_Code RJS 08Feb00  	Bool	oldcross;
//Old_Code RJS 08Feb00  	Float	opposite, adjacent;									//RJS 20Feb97
//Old_Code RJS 08Feb00 	Bool	wantwind = FALSE;									//RJS 18Mar97
//Old_Code RJS 08Feb00  	ImageMapDescPtr imptr = Image_Map.GetImageMapPtr(imapno);	//RJS 05Feb98
//Old_Code RJS 08Feb00 	SWord	stepx,stepy;
//Old_Code RJS 08Feb00 	SWord	nofx;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 	minx = minix;		
//Old_Code RJS 08Feb00 	miny = miniy;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 	if (frameno)										//RJS 05Feb98
//Old_Code RJS 08Feb00 	{													//RJS 05Feb98
//Old_Code RJS 08Feb00 		nofx = imptr->w / width;				//RJS 05Feb98
//Old_Code RJS 08Feb00 														//RJS 05Feb98
//Old_Code RJS 08Feb00 		stepy = frameno / nofx;							//RJS 05Feb98
//Old_Code RJS 08Feb00 		stepx = frameno - (stepy*nofx);					//RJS 05Feb98
//Old_Code RJS 08Feb00 														//RJS 05Feb98
//Old_Code RJS 08Feb00 		minx += stepx * width;							//RJS 05Feb98
//Old_Code RJS 08Feb00 		miny += stepy * height;							//RJS 05Feb98
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 		if (miny >= imptr->h)
//Old_Code RJS 08Feb00 			minx = miny = 0;
//Old_Code RJS 08Feb00 	}													//RJS 05Feb98
//Old_Code RJS 08Feb00 														//RJS 05Feb98
//Old_Code RJS 08Feb00 	maxx = minx + width-1;								//RJS 05Feb98
//Old_Code RJS 08Feb00 	maxy = miny + height;								//RJS 05Feb98
//Old_Code RJS 08Feb00  
//Old_Code RJS 08Feb00 //DEAD 	oldcross = POLYGON.SetCrossProduct(FALSE);
//Old_Code RJS 08Feb00  
//Old_Code RJS 08Feb00    	dopoint0 = newco[vertex1];									//RJS 20Nov98
//Old_Code RJS 08Feb00    	dopoint2 = newco[vertex2];									//RJS 20Nov98
//Old_Code RJS 08Feb00  
//Old_Code RJS 08Feb00  	// Clip Z...
//Old_Code RJS 08Feb00  
//Old_Code RJS 08Feb00  	if (	(dopoint0.bodyz.f > 0.0)							//RJS 27Aug98
//Old_Code RJS 08Feb00  		||	(dopoint2.bodyz.f > 0.0)	)						//RJS 27Aug98
//Old_Code RJS 08Feb00  	{
//Old_Code RJS 08Feb00 //deadcode		if (	(dopoint0.bodyz.f < 1.0)						//RJS 27Aug98
//Old_Code RJS 08Feb00 //deadcode			||	(dopoint2.bodyz.f < 1.0)	)					//RJS 27Aug98
//Old_Code RJS 08Feb00 //deadcode		{														//RJS 23Jun97
//Old_Code RJS 08Feb00 //deadcode		 	current_screen->zclipline(dopoint0,dopoint2);		//RJS 23Jun97
//Old_Code RJS 08Feb00 //deadcode	 		_matrix.body2screen(dopoint0);						//RJS 23Jun97
//Old_Code RJS 08Feb00 //deadcode 			_matrix.body2screen(dopoint2);						//RJS 23Jun97
//Old_Code RJS 08Feb00 //deadcode		}														//RJS 23Jun97
//Old_Code RJS 08Feb00 //deadcode		else
//Old_Code RJS 08Feb00 //deadcode		{
//Old_Code RJS 08Feb00 //			if (doingHW3D)
//Old_Code RJS 08Feb00 //			{
//Old_Code RJS 08Feb00 //deadcode				_matrix.body2screen(dopoint0);					//RJS 21Aug98
//Old_Code RJS 08Feb00 //deadcode				_matrix.body2screen(dopoint2);					//RJS 21Aug98
//Old_Code RJS 08Feb00 //			}
//Old_Code RJS 08Feb00 //deadcode		}
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 		R3DVALUE screenx0,screeny0,screenx2,screeny2;
//Old_Code RJS 08Feb00 		R3DVALUE screenz0,screenz2;
//Old_Code RJS 08Feb00 		g_lpLib3d->BodyToScreen(dopoint0,screenx0,screeny0,screenz0);//RJS 07Feb00
//Old_Code RJS 08Feb00 		g_lpLib3d->BodyToScreen(dopoint2,screenx2,screeny2,screenz2);//RJS 07Feb00
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 		dopoint1 = dopoint0;									//RJS 25Jun97
//Old_Code RJS 08Feb00 		dopoint3 = dopoint2;									//RJS 25Jun97
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 //		if (dopoint2.bodyz.f < 1172)							//RJS 24Jun97
//Old_Code RJS 08Feb00 //			depth = 0;											//RJS 24Jun97
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 		opposite = screeny0 - screeny2;		//RJS 19May97
//Old_Code RJS 08Feb00  		adjacent = screenx2 - screenx0;		//RJS 19May97
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 		if (opposite || adjacent)								//MS 30Nov98
//Old_Code RJS 08Feb00 		{
//Old_Code RJS 08Feb00 			Float res=10430.37835047*FPATan(adjacent,opposite);
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 			angleofcylinder = res;   //Math_Lib.HighArcTan(adjacent,opposite);	//RJS 23Sep96
//Old_Code RJS 08Feb00  			angleofcylinder -= ANGLES_90Deg;
//Old_Code RJS 08Feb00  
//Old_Code RJS 08Feb00  			Math_Lib.high_sin_cos((Angles) angleofcylinder,sin_ang,cos_ang);
//Old_Code RJS 08Feb00  
//Old_Code RJS 08Feb00   			xoff = (sin_ang * radius) / ANGLES_FRACT;				//RJS 13Jun97
//Old_Code RJS 08Feb00   			yoff = (cos_ang * radius) / ANGLES_FRACT;				//RJS 13Jun97
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 			if (ClipCylinder(dopoint0,dopoint1,dopoint2,dopoint3,xoff,yoff)==FALSE)//RJS 21Aug98
//Old_Code RJS 08Feb00 			{														//RJS 21Aug98
//Old_Code RJS 08Feb00 //DEAD 		 		POLYGON.SetPixelWidth(1<<Save_Data.pixelsize);			//RJS 25Jun97
//Old_Code RJS 08Feb00 				R3DVERTEX *pRVerts;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 				if (depth)
//Old_Code RJS 08Feb00 					g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,depth);
//Old_Code RJS 08Feb00 				g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),4,pRVerts);
//Old_Code RJS 08Feb00 				dopoint3.ix=minx;
//Old_Code RJS 08Feb00 				dopoint3.iy=maxy;
//Old_Code RJS 08Feb00 				dopoint2.ix=maxx;
//Old_Code RJS 08Feb00 				dopoint2.iy=maxy;
//Old_Code RJS 08Feb00 				dopoint1.ix=maxx;
//Old_Code RJS 08Feb00 				dopoint1.iy=miny;
//Old_Code RJS 08Feb00 				dopoint0.ix=minx;
//Old_Code RJS 08Feb00 				dopoint0.iy=miny;
//Old_Code RJS 08Feb00 				*pRVerts++=dopoint3;
//Old_Code RJS 08Feb00 				*pRVerts++=dopoint2;
//Old_Code RJS 08Feb00 				*pRVerts++=dopoint1;
//Old_Code RJS 08Feb00 				*pRVerts++=dopoint0;
//Old_Code RJS 08Feb00 				g_lpLib3d->EndPoly();
//Old_Code RJS 08Feb00 				g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,SMOKED_OFF);
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 //deadcode 				POLYGON.createpoly(imapno);								//RJS 25Jun97
//Old_Code RJS 08Feb00 //deadcode	  			POLYGON.createvert(dopoint3,minx,maxy);					//RJS 13Jun97
//Old_Code RJS 08Feb00 //deadcode  				POLYGON.createvert(dopoint2,maxx,maxy);					//RJS 13Jun97
//Old_Code RJS 08Feb00 //deadcode  				POLYGON.createvert(dopoint1,maxx,miny);					//RJS 13Jun97
//Old_Code RJS 08Feb00 //deadcode	  			POLYGON.createvert(dopoint0,minx,miny);					//RJS 13Jun97
//Old_Code RJS 08Feb00 									//RJS 13Jun97
//Old_Code RJS 08Feb00 //deadcode				if (depth)												//RJS 20Jun97
//Old_Code RJS 08Feb00 //deadcode				{														//RJS 20Jun97
//Old_Code RJS 08Feb00 //deadcode					current_screen->SetTransparency(depth);				//RJS 20Jun97
//Old_Code RJS 08Feb00 //deadcode					POLYGON.SetOpacityON();								//RJS 20Jun97
//Old_Code RJS 08Feb00 //deadcode 					POLYGON.drawpoly();									//RJS 20Jun97
//Old_Code RJS 08Feb00 //deadcode	  				current_screen->SetTransparency(SMOKED_OFF);		//RJS 20Jun97
//Old_Code RJS 08Feb00 //deadcode				}														//RJS 20Jun97
//Old_Code RJS 08Feb00 //deadcode				else													//RJS 20Jun97
//Old_Code RJS 08Feb00 //deadcode	 				POLYGON.drawpoly();									//RJS 20Jun97
//Old_Code RJS 08Feb00  
//Old_Code RJS 08Feb00 //DEAD 				POLYGON.SetPixelWidth(1);
//Old_Code RJS 08Feb00 			}
//Old_Code RJS 08Feb00 		}
//Old_Code RJS 08Feb00  	}
//Old_Code RJS 08Feb00  
//Old_Code RJS 08Feb00 //DEAD 	POLYGON.SetCrossProduct(oldcross);

	SWord	minx, miny, maxx, maxy;								
	ULong	thewidth, theheight;
//DeadCode RJS 14Feb00 	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3;
 	Float	xoff, yoff;
  	SWord	angleofcylinder;									
 	SWord	sin_ang,cos_ang;
 	Bool	oldcross;
 	Float	opposite, adjacent;
 	ImageMapDescPtr imptr = Image_Map.GetImageMapPtr(imapno);
	SWord	stepx,stepy;
	SWord	nofx;


	minx = minix;		
	miny = miniy;

	if (frameno)										
	{													
		nofx = imptr->w / width;						
														
		stepy = frameno / nofx;							
		stepx = frameno - (stepy*nofx);					
														
		minx += stepx * width;							
		miny += stepy * height;							

		if (miny >= imptr->h)
			minx = miny = 0;
	}													
														
	maxx = minx + width-1;								
	maxy = miny + height;

	g_lpLib3d->DrawCylinder(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),newco[vertex1],newco[vertex2],radius,minx,miny,maxx,maxy);//RJS 14Feb00
 
//DeadCode RJS 14Feb00    	dopoint0 = newco[vertex1];
//DeadCode RJS 14Feb00    	dopoint2 = newco[vertex2];
//DeadCode RJS 14Feb00  
//DeadCode RJS 14Feb00  	// Clip Z...
//DeadCode RJS 14Feb00  
//DeadCode RJS 14Feb00 	R3DVALUE screenx0,screeny0,screenx2,screeny2;
//DeadCode RJS 14Feb00 	R3DVALUE screenz0,screenz2;
//DeadCode RJS 14Feb00 	g_lpLib3d->Transform(MATRIX_OBJECT,dopoint0);
//DeadCode RJS 14Feb00 	g_lpLib3d->Transform(MATRIX_VIEWER,dopoint0);
//DeadCode RJS 14Feb00 	screenx0 = dopoint0.bodyx.f;
//DeadCode RJS 14Feb00 	screeny0 = dopoint0.bodyy.f;
//DeadCode RJS 14Feb00 	screenz0 = dopoint0.bodyz.f;
//DeadCode RJS 14Feb00 	g_lpLib3d->Transform(MATRIX_OBJECT,dopoint2);
//DeadCode RJS 14Feb00 	g_lpLib3d->Transform(MATRIX_VIEWER,dopoint2);
//DeadCode RJS 14Feb00 	screenx2 = dopoint2.bodyx.f;
//DeadCode RJS 14Feb00 	screeny2 = dopoint2.bodyy.f;
//DeadCode RJS 14Feb00 	screenz2 = dopoint2.bodyz.f;
//DeadCode RJS 14Feb00 
//DeadCode RJS 14Feb00 	if ((screenz0 > 1.0) || (screenz2 > 1.0))
//DeadCode RJS 14Feb00 	{
//DeadCode RJS 14Feb00 		dopoint1 = dopoint0;
//DeadCode RJS 14Feb00 		dopoint3 = dopoint2;
//DeadCode RJS 14Feb00 
//DeadCode RJS 14Feb00 		opposite = screeny0 - screeny2;
//DeadCode RJS 14Feb00  		adjacent = screenx2 - screenx0;
//DeadCode RJS 14Feb00 
//DeadCode RJS 14Feb00 		if (opposite || adjacent)
//DeadCode RJS 14Feb00 		{
//DeadCode RJS 14Feb00 			Float res=10430.37835047*FPATan(adjacent,opposite);
//DeadCode RJS 14Feb00 
//DeadCode RJS 14Feb00 			angleofcylinder = SWord(res);
//DeadCode RJS 14Feb00  			angleofcylinder -= ANGLES_90Deg;
//DeadCode RJS 14Feb00  
//DeadCode RJS 14Feb00  			Math_Lib.high_sin_cos((Angles) angleofcylinder,sin_ang,cos_ang);
//DeadCode RJS 14Feb00  
//DeadCode RJS 14Feb00   			xoff = (sin_ang * radius) / ANGLES_FRACT;
//DeadCode RJS 14Feb00   			yoff = (cos_ang * radius) / ANGLES_FRACT;
//DeadCode RJS 14Feb00 
//DeadCode RJS 14Feb00 			if (ClipCylinder(dopoint0,dopoint1,dopoint2,dopoint3,xoff,yoff)==FALSE)
//DeadCode RJS 14Feb00 			{									
//DeadCode RJS 14Feb00 				R3DVERTEX *pRVerts;
//DeadCode RJS 14Feb00 
//DeadCode RJS 14Feb00 				if (depth)
//DeadCode RJS 14Feb00 					g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,depth);
//DeadCode RJS 14Feb00 
//DeadCode RJS 14Feb00 				g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),4,pRVerts);
//DeadCode RJS 14Feb00 				dopoint3.ix=minx;
//DeadCode RJS 14Feb00 				dopoint3.iy=maxy;
//DeadCode RJS 14Feb00 				dopoint2.ix=maxx;
//DeadCode RJS 14Feb00 				dopoint2.iy=maxy;
//DeadCode RJS 14Feb00 				dopoint1.ix=maxx;
//DeadCode RJS 14Feb00 				dopoint1.iy=miny;
//DeadCode RJS 14Feb00 				dopoint0.ix=minx;
//DeadCode RJS 14Feb00 				dopoint0.iy=miny;
//DeadCode RJS 14Feb00 				*pRVerts++=dopoint3;
//DeadCode RJS 14Feb00 				*pRVerts++=dopoint2;
//DeadCode RJS 14Feb00 				*pRVerts++=dopoint1;
//DeadCode RJS 14Feb00 				*pRVerts++=dopoint0;
//DeadCode RJS 14Feb00 				g_lpLib3d->EndPoly();
//DeadCode RJS 14Feb00 				g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,SMOKED_OFF);
//DeadCode RJS 14Feb00 
//DeadCode RJS 14Feb00 			}
//DeadCode RJS 14Feb00 		}
//DeadCode RJS 14Feb00  	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		omapcylinder
//Author		Robert Slater
//Date			Mon 23 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::omapcylinder(	UWord vertex,
							UWord depth,						//RJS 20Jun97
							SLong radius,
							ImageMapNumber imapno,
							UWord	minix, UWord miniy,
							UWord	maxix, UWord maxiy,
							UWord	width, UWord height,
							UByte	divfactor,
							UByte	flagoffset)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetPilotedAcAnim
//Author		Paul.   
//Date			Tue 16 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::SetPilotedAcAnim(AirStrucPtr pilotedac)
{
	int		count;												//RJS 23Aug96

	PolyPitAnimData		*newanim = new PolyPitAnimData;
	AircraftAnimData	*oldanim = (AircraftAnimData* )pilotedac->Anim,
						*naa=newanim;

	animptr		thenewanim;

	*naa=*oldanim;

	thenewanim = pilotedac->Anim;
	thenewanim = (UByteP)newanim;

	//Bollocks for the detail.....
	newanim->detailmask = 0xFFFFFFFF;							//RJS 24Mar00

//	newanim->compasscount = 0;									//RJS 05Jun97
//	newanim->muzzlego = FALSE;									//RJS 05Jun97

	delete (oldanim);

	pilotedac->Anim = thenewanim;
	pilotedac->Anim = (AnimSizeField)sizeof(PolyPitAnimData);		//RJS 01Dec99
	pilotedac->Anim = (AnimFlagField) (1<<MINANIM)
									+ (1<<MOVEGUNANIM)
									+ (1<<AIRCRAFTANIM)
									+ (1<<POLYPITANIM);				//RJS 01Dec99

	for (count=0; count < newanim->nolaunchers; count++)				//RJS 10Jul00
		newanim->prevammo[count] = newanim->weaponlaunchers[count].LoadedStores;

	Trans_Obj.WeaponSearch(pilotedac);								//RJS 02Nov98
};


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawHitBox
//Author		Paul.   
//Date			Wed 23 Oct 1996
//
//Description	Draws a Magenta box around a shapes hit area
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::DrawHitBox(Obj3DPtr obj3dptr,MATRIX_PTR matp)	//RJS 07Feb00
{
 	if (!Three_Dee.shapecheat)
		return;

	SLong	dx,dy,dz;
	SLong	cx,cy,cz;

	ShapeDescPtr	sdp;

	DOSETCOLOUR256	idosetcolour256;
	DOPOINT			idopoint;
	DOLINE			idoline;

	UByte*			instp;

 	SLong		tmpscale=0;

	sdp = SHAPESTUFF.GetShapePtr((ShapeNum)obj3dptr->Shape);
  	switch(SHAPESTUFF.GetShapeScale(sdp))				//PD 23Apr96
  	{
  		case SHP_1CM:
  			tmpscale = 0;										//PD 10Apr96
  			break;												//PD 10Apr96
  
  		case SHP_4CM:
  			tmpscale = 2;										//PD 10Apr96
  			break;												//PD 10Apr96
  
  		case SHP_16CM:
  			tmpscale = 4;										//PD 10Apr96
  			break;												//PD 10Apr96
  	}

	cx = cy = cz = 0;

	dx = sdp->sx;
	dy = sdp->sy;
	dz = sdp->sz;

	if (sdp->CollisionOffset)
	{
		UWord	instruction;
		UByteP	instr_ptr = UByteP(sdp) + sdp->CollisionOffset;

		instruction = *instr_ptr;
		instr_ptr++;

		if (instruction == docollisionno)
		{
			DOCOLLISION_PTR	ptr = DOCOLLISION_PTR(instr_ptr);
			if (ptr->radius)
			{
				cx = ptr->xoff >> tmpscale;
				cy = ptr->yoff >> tmpscale;
				cz = ptr->zoff >> tmpscale;

				dx = ptr->sx;
				dy = ptr->sy;
				dz = ptr->sz;
			}
		}
	}

  	dx <<= (4-tmpscale);
  	dy <<= (4-tmpscale);
  	dz <<= (4-tmpscale);

	switch (Save_Data.targetsize)
	{
		case TS_LARGE:
			dx *= 48;
			dx >>= 4;
			dy *= 48;
			dy >>= 4;
			dz *= 48;
			dz >>= 4;
			break;
		case TS_MEDIUM:
			dx *= 32;
			dx >>= 4;
			dy *= 32;
			dy >>= 4;
			dz *= 32;
			dz >>= 4;
			break;
		case TS_SMALL:
			break;
	}

	if (	(	obj3dptr->ItemPtr
			 &&	!BoxCol::TargetAllowed(Persons2::PlayerSeenAC,obj3dptr->ItemPtr,0)	)
		||	(obj3dptr->AnimPtr.GetItemState() == DEAD)	)
		idosetcolour256.basecolour = 200;
	else
		idosetcolour256.basecolour = 254;

	idosetcolour256.spread = 1;
	idosetcolour256.imap = 0xFF;
	instp = (UByte*)&idosetcolour256;
	SHAPE.dosetcolour256(instp);

//DeadCode RJS 15Aug00 	idopoint.vertex = 0;
//DeadCode RJS 15Aug00 	idopoint.xcoord = -dx + cx;
//DeadCode RJS 15Aug00 	idopoint.ycoord = -dy + cy;
//DeadCode RJS 15Aug00 	idopoint.zcoord = -dz + cz;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idopoint;
//DeadCode RJS 15Aug00 	SHAPE.dopoint(instp);
		
	DoPointStruc* dp=newco;
	dp->setPosition(-dx + cx,
					-dy + cy,
					-dz + cz	);	//RJS 19May00

//DeadCode RJS 15Aug00 	idopoint.vertex = 1;
//DeadCode RJS 15Aug00 	idopoint.xcoord = -dx + cx;
//DeadCode RJS 15Aug00 	idopoint.ycoord = -dy + cy;
//DeadCode RJS 15Aug00 	idopoint.zcoord = dz + cz;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idopoint;
//DeadCode RJS 15Aug00 	SHAPE.dopoint(instp);

	dp++;
	dp->setPosition(-dx + cx,
					-dy + cy,
					dz + cz	);	//RJS 19May00

//DeadCode RJS 15Aug00  	idopoint.vertex = 2;
//DeadCode RJS 15Aug00 	idopoint.xcoord = dx + cx;
//DeadCode RJS 15Aug00 	idopoint.ycoord = -dy + cy;
//DeadCode RJS 15Aug00 	idopoint.zcoord = dz + cz;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idopoint;
//DeadCode RJS 15Aug00 	SHAPE.dopoint(instp);

	dp++;
	dp->setPosition(dx + cx,
					-dy + cy,
					dz + cz	);	//RJS 19May00

//DeadCode RJS 15Aug00 	idopoint.vertex = 3;
//DeadCode RJS 15Aug00 	idopoint.xcoord = dx  + cx;
//DeadCode RJS 15Aug00 	idopoint.ycoord = -dy + cy;
//DeadCode RJS 15Aug00 	idopoint.zcoord = -dz + cz;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idopoint;
//DeadCode RJS 15Aug00 	SHAPE.dopoint(instp);

	dp++;
	dp->setPosition(dx + cx,
					-dy + cy,
					-dz + cz	);	//RJS 19May00

//DeadCode RJS 15Aug00 	idopoint.vertex = 4;
//DeadCode RJS 15Aug00 	idopoint.xcoord = -dx + cx;
//DeadCode RJS 15Aug00 	idopoint.ycoord = dy  + cy;
//DeadCode RJS 15Aug00 	idopoint.zcoord = -dz + cz;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idopoint;
//DeadCode RJS 15Aug00 	SHAPE.dopoint(instp);

	dp++;
	dp->setPosition(-dx + cx,
					dy + cy,
					-dz + cz	);	//RJS 19May00

//DeadCode RJS 15Aug00 	idopoint.vertex = 5;
//DeadCode RJS 15Aug00 	idopoint.xcoord = -dx + cx;
//DeadCode RJS 15Aug00 	idopoint.ycoord = dy  + cy;
//DeadCode RJS 15Aug00 	idopoint.zcoord = dz  + cz;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idopoint;
//DeadCode RJS 15Aug00 	SHAPE.dopoint(instp);

	dp++;
	dp->setPosition(-dx + cx,
					dy + cy,
					dz + cz	);	//RJS 19May00

//DeadCode RJS 15Aug00 	idopoint.vertex = 6;
//DeadCode RJS 15Aug00 	idopoint.xcoord = dx + cx;
//DeadCode RJS 15Aug00 	idopoint.ycoord = dy + cy;
//DeadCode RJS 15Aug00 	idopoint.zcoord = dz + cz;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idopoint;
//DeadCode RJS 15Aug00 	SHAPE.dopoint(instp);

	dp++;
	dp->setPosition(dx + cx,
					dy + cy,
					dz + cz	);	//RJS 19May00

//DeadCode RJS 15Aug00 	idopoint.vertex = 7;
//DeadCode RJS 15Aug00 	idopoint.xcoord = dx  + cx;
//DeadCode RJS 15Aug00 	idopoint.ycoord = dy  + cy;
//DeadCode RJS 15Aug00 	idopoint.zcoord = -dz + cz;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idopoint;
//DeadCode RJS 15Aug00 	SHAPE.dopoint(instp);

	dp++;
	dp->setPosition(dx + cx,
					dy + cy,
					-dz + cz	);	//RJS 19May00

//DeadCode RJS 15Aug00 	idoline.start_vertex = 0;
//DeadCode RJS 15Aug00 	idoline.end_vertex = 1;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idoline;
//DeadCode RJS 15Aug00 	SHAPE.doline(instp);

	g_lpLib3d->DrawLine(HMATERIAL(shape::colour),newco[0],newco[1]);

//DeadCode RJS 15Aug00 	idoline.start_vertex = 1;
//DeadCode RJS 15Aug00 	idoline.end_vertex = 2;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idoline;
//DeadCode RJS 15Aug00 	SHAPE.doline(instp);

	g_lpLib3d->DrawLine(HMATERIAL(shape::colour),newco[1],newco[2]);

//DeadCode RJS 15Aug00 	idoline.start_vertex = 2;
//DeadCode RJS 15Aug00 	idoline.end_vertex = 3;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idoline;
//DeadCode RJS 15Aug00 	SHAPE.doline(instp);

	g_lpLib3d->DrawLine(HMATERIAL(shape::colour),newco[2],newco[3]);

//DeadCode RJS 15Aug00 	idoline.start_vertex = 3;
//DeadCode RJS 15Aug00 	idoline.end_vertex = 0;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idoline;
//DeadCode RJS 15Aug00 	SHAPE.doline(instp);

	g_lpLib3d->DrawLine(HMATERIAL(shape::colour),newco[3],newco[0]);

//DeadCode RJS 15Aug00 	idoline.start_vertex = 4;
//DeadCode RJS 15Aug00 	idoline.end_vertex = 5;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idoline;
//DeadCode RJS 15Aug00 	SHAPE.doline(instp);

	g_lpLib3d->DrawLine(HMATERIAL(shape::colour),newco[4],newco[5]);

//DeadCode RJS 15Aug00 	idoline.start_vertex = 5;
//DeadCode RJS 15Aug00 	idoline.end_vertex = 6;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idoline;
//DeadCode RJS 15Aug00 	SHAPE.doline(instp);

	g_lpLib3d->DrawLine(HMATERIAL(shape::colour),newco[5],newco[6]);

//DeadCode RJS 15Aug00 	idoline.start_vertex = 6;
//DeadCode RJS 15Aug00 	idoline.end_vertex = 7;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idoline;
//DeadCode RJS 15Aug00 	SHAPE.doline(instp);

	g_lpLib3d->DrawLine(HMATERIAL(shape::colour),newco[6],newco[7]);

//DeadCode RJS 15Aug00 	idoline.start_vertex = 7;
//DeadCode RJS 15Aug00 	idoline.end_vertex = 4;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idoline;
//DeadCode RJS 15Aug00 	SHAPE.doline(instp);

	g_lpLib3d->DrawLine(HMATERIAL(shape::colour),newco[7],newco[4]);

//DeadCode RJS 15Aug00 	idoline.start_vertex = 0;
//DeadCode RJS 15Aug00 	idoline.end_vertex = 4;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idoline;
//DeadCode RJS 15Aug00 	SHAPE.doline(instp);

	g_lpLib3d->DrawLine(HMATERIAL(shape::colour),newco[0],newco[4]);

//DeadCode RJS 15Aug00 	idoline.start_vertex = 1;
//DeadCode RJS 15Aug00 	idoline.end_vertex = 5;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idoline;
//DeadCode RJS 15Aug00 	SHAPE.doline(instp);

	g_lpLib3d->DrawLine(HMATERIAL(shape::colour),newco[1],newco[5]);

//DeadCode RJS 15Aug00 	idoline.start_vertex = 2;
//DeadCode RJS 15Aug00 	idoline.end_vertex = 6;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idoline;
//DeadCode RJS 15Aug00 	SHAPE.doline(instp);

	g_lpLib3d->DrawLine(HMATERIAL(shape::colour),newco[2],newco[6]);

//DeadCode RJS 15Aug00 	idoline.start_vertex = 3;
//DeadCode RJS 15Aug00 	idoline.end_vertex = 7;
//DeadCode RJS 15Aug00 	instp = (UByte*)&idoline;
//DeadCode RJS 15Aug00 	SHAPE.doline(instp);

	g_lpLib3d->DrawLine(HMATERIAL(shape::colour),newco[3],newco[7]);
}

SLong shape::Noise(SLong	wx, SLong	wy, SLong	wz)
{
	return RandTable[(RandTable[(RandTable[wx&0xFF]+wy)&0xFF]+wz)&0xFF];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitTrailFields
//Author		Robert Slater
//Date			Mon 12 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::InitTrailFields(	UByteP		wptr,
								int			index,
								int			capacity,
								LnchrType	ltype		)
{
	if (wptr)			
	{
		WeapAnimData  *weapon = (WeapAnimData*) wptr;

		if (weapon->hdg==0)						//RJS 21Jan99
		{
			weapon->LauncherType = ltype;
			weapon->LaunchTime = 0;
			weapon->hdg = index;
			weapon->pitch = capacity;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WingSpanUp
//Author		Robert Slater
//Date			Mon 20 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::WingSpanUp()
{
	WingSpan += 15;					// 0.5 feet
	if (WingSpan > 4876)
		WingSpan = 4876;			// 160 feet
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WingSpanDown
//Author		Robert Slater
//Date			Mon 20 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::WingSpanDown()
{
	WingSpan -= 15;					// .5 feet
	if (WingSpan < 609)		
		WingSpan = 609;				//20 feet
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GunRangeUp
//Author		Robert Slater
//Date			Mon 20 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GunRangeUp()
{
	// Max is 5000 yds...
	RequiredRange += 100;
	if (RequiredRange > 50813)									//RJS 11Dec98
		RequiredRange = 50813;									//RJS 11Dec98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GunRangeDown
//Author		Robert Slater
//Date			Mon 20 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GunRangeDown()
{
	RequiredRange -= 100;
	if (RequiredRange < 10000)									//RJS 11Dec98
		RequiredRange = 10000;									//RJS 11Dec98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleDustPnt
//Author		Robert Slater
//Date			Thu 7 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::SampleDustPnt(	UByteP		smkinfo,
								SWord		&listindex,
								UByteP		instr_ptr,
								UWord		LifeTime,
								SLong		gheight,
								SWord		realpitch	)
{
	Bool	validpoint = TRUE;

	if (SamplePntTime)
	{
		DOLAUNCHER_PTR	ptr = (DOLAUNCHER_PTR) instr_ptr;
		TrailRecord*	trailptr = &traillist[listindex];
		SmokeTypeP		smkptr = (SmokeTypeP) smkinfo;
		SLong			xcoord = ptr->posx;
		SLong			ycoord = ptr->posy;
		SLong			zcoord = ptr->posz;
		SLong			lifetime;
		SLong			wx, wy, wz;
		SWord			index = listindex;
		MATRIX  		omat;										
		MATRIX_PTR		obj_matrix = &omat;							
		UWord			scaleback;
		SWord			sin_ang, cos_ang;
		SLong			hyp = 0;
		SLong			wwz;
		SLong			tailbit = zcoord << shapescale;
		SLong			tailfrac;
		ItemPtr			tmpitem;

		Math_Lib.high_sin_cos((Angles) realpitch,sin_ang,cos_ang);

		if (sin_ang)
			hyp = (gheight<<15) / sin_ang;

		tmpitem = new item;

		hyp -= tailbit;

		if (!LifeTime)											
			LifeTime = smkptr->LifeTime;						

		LifeTime = (LifeTime * -tailbit)/hyp;
		if (!LifeTime)
		{
			LifeTime = 10;
			hyp = -tailbit;
		}

		trailptr->SampleTime -= View_Point->DrawFrameTime();		
		if (trailptr->SampleTime < 0)							
			trailptr->SampleTime = smkptr->SampleTime;			
		else													
			validpoint = FALSE;									

		lifetime = LifeTime;							

 		if (trailptr->nextlist)
 		{
 			Coords3DList*	nextptr = traillist[trailptr->nextlist].thelist;
 			if (nextptr)
 			{
 				wx = nextptr->trailpoint.gx;
 				wy = nextptr->trailpoint.gy;
 				wz = nextptr->trailpoint.gz;

 				SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,lifetime,smkptr->FadeTime);
 				lifetime = trailptr->lifetime;
 			}

 			trailptr->nextlist = 0;
 		}

		// Every frame....

 		wx = xcoord << shapescale;
 		wy = ycoord << shapescale;
 		wz = -hyp;

		_matrix.generate2(	object_obj3d->AngH,
							object_obj3d->AngC,
							object_obj3d->AngR,
							obj_matrix);

		scaleback = _matrix.transform(obj_matrix,wx,wy,wz);
		wx >>= (16-scaleback);
		wy >>= (16-scaleback);
		wz >>= (16-scaleback);

		wx += trailptr->lastwx;
		wy += trailptr->lastwy;
		wz += trailptr->lastwz;

		tmpitem->World.X = wx;
		tmpitem->World.Y = wy;
		tmpitem->World.Z = wz;

		wy = Land_Scape.GetGroundLevel(tmpitem);
		if (wy <= trailptr->lastwy)
		{
			SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,lifetime,smkptr->FadeTime);
			if (trailptr->nopoints > 127)
			{
 				trailptr->bitshift = 0;
				listindex = 0;			//RJS 12/4/99
//DEADCODE DAW 12/04/99 				listindex = -index;
				SHAPE.DetatchVapourStream(index,lifetime);
			}
		}

		delete tmpitem;
	}

	return(validpoint);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitUndercarriageAnim
//Author		Robert Slater
//Date			Thu 28 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::InitUndercarriageAnim(AirStrucPtr	itm)
{
	if (itm->vel_)
		itm->fly.pModel->SetGearAnimPos(itm, ANIM_GEAR_UP);
	else
		itm->fly.pModel->SetGearAnimPos(itm, ANIM_GEAR_DOWN);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RipStores					   MODIFIED
//Author		Robert Slater				   CRAIG BEESTON
//Date			Wed 3 Jun 1998				   Tue 27 Apr 1999
//
//Description	Removes fuel stores after (5 g's for 13 secs - to - 8g's for 1 frame)
//
//				Should set up a flag in airstruc to say they've been removed,
//				so we don't come into this routine again.....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::RipStores(AirStrucPtr	ac)
{
	if(!Save_Data.flightdifficulty [FD_EXCESSIVEACCELDAMAGE])
		return;
	
	const FP MinGs = 5.0;
	const FP MaxGs = 8.0;

	if (ac->weap.FuelDumped == FALSE)
		if(ac->fly.pModel->Inst.I_NormalAcc > MinGs)
		{
			bool dodump = false;
			if(ac->fly.pModel->Inst.I_NormalAcc < MaxGs)
			{
				SLong gs = ((MaxGs - ac->fly.pModel->Inst.I_NormalAcc) * 65535.0) / (MaxGs - MinGs) + 1.0;
				gs = (100 * 65535) / gs;
				UWord chance = Math_Lib.rnd();
				if (chance < gs)
					dodump = true;
			}
			else
				dodump = true;

			if (dodump)
			{
				WorldStuff*	world = mobileitem::currworld;
				Trans_Obj.DumpFuel(ac,*world,TRUE);				//RJS 04Feb99
			}
		}
//DeadCode CSB 27/04/99		if (ac->weap.FuelDumped == FALSE)
//DeadCode CSB 27/04/99		{
//DeadCode CSB 27/04/99			SLong	gs = ((ac->fly.pModel->Inst.NormalAcc - 3.0) * 65535.0);
//DeadCode CSB 27/04/99			if (gs > 0)
//DeadCode CSB 27/04/99			{
//DeadCode CSB 27/04/99				bool dodump = false;
//DeadCode CSB 27/04/99				gs /= 3;
//DeadCode CSB 27/04/99				if (gs < 65535)
//DeadCode CSB 27/04/99				{
//DeadCode CSB 27/04/99					ULong	chance = Math_Lib.rnd();
//DeadCode CSB 27/04/99					chance = (chance*gs)>>16;
//DeadCode CSB 27/04/99					if (chance > 64000)
//DeadCode CSB 27/04/99						dodump = true;
//DeadCode CSB 27/04/99				}
//DeadCode CSB 27/04/99				else
//DeadCode CSB 27/04/99					dodump = true;
//DeadCode CSB 27/04/99	
//DeadCode CSB 27/04/99				if (dodump)
//DeadCode CSB 27/04/99				{
//DeadCode CSB 27/04/99					WorldStuff*	world = mobileitem::currworld;
//DeadCode CSB 27/04/99					Trans_Obj.DumpFuel(ac,*world,TRUE);				//RJS 04Feb99
//DeadCode CSB 27/04/99				}
//DeadCode CSB 27/04/99			}
//DeadCode CSB 27/04/99		}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AnimMap
//Author		Robert Slater
//Date			Mon 22 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::AnimMap(	animptr&	adptr,
						SWord	imap,
						SWord	animflag,
						SWord	animscale,
						SWord	&minx,
						SWord	&miny,
						SWord	width,
						SWord	height)
{
	Bool	retval = FALSE;
	if (animflag)
	{
		SWord			frameno;
		SWord			nofx,stepy,stepx;
		ImageMapDescPtr imptr = Image_Map.GetImageMapPtr((ImageMapNumber )imap);

		frameno = adptr[animflag]/animscale;

		nofx = imptr->w / width;						
		if (nofx)
		{
	 		stepy = frameno / nofx;					
			stepx = frameno - (stepy*nofx);		
												
			minx += stepx * width;					
			miny += stepy * height;
			if (miny >= imptr->h)
				minx = miny = 0;
		}
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRadarItem
//Author		Robert Slater
//Date			Thu 25 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GetRadarItem(ItemPtr	itm, SLong	range)
{
	if ((range > 100) && (range < radarRange))		// must be at least a metre away
	{
		FPMATRIX_PTR	matp = &radarMatrix;
		IFShare			wx, wy, wz;
		SLong			wxx,wyy,wzz;
		SLong			viewz;
		SLong			temp;

		wx.i = itm->World.X - viewer_x;
		wy.i = itm->World.Y - viewer_y;
		wz.i = itm->World.Z - viewer_z;

		_matrix.transform(matp,wx,wy,wz);

		// Cleaned up by Rob.
		wzz = SLong(wz.f);
		if (wzz > 0)
		{
			wxx = SLong(wx.f);
			wyy = SLong(wy.f);

			viewz = wzz;
			temp = (wxx<0?-wxx:wxx);
			if (temp<=viewz)
			{
				temp = (wyy<0?-wyy:wyy);
				if (temp <= viewz)
				{
					// New lock....
					radarTmpItm = itm;
					radarRange = range;
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcRadarRange
//Author		Robert Slater
//Date			Thu 25 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::CalcRadarRange(AirStrucPtr	me)
{
//DeadCode RDH 13Apr99 	if (RadarItemPtr)
//DeadCode RDH 13Apr99 	{
//DeadCode RDH 29Nov98 		SWord	dummy1, dummy2;
//DeadCode RDH 29Nov98 		Math_Lib.Intercept(	RadarItemPtr->World.X - me->World.X,
//DeadCode RDH 29Nov98 							RadarItemPtr->World.Y - me->World.Y,
//DeadCode RDH 29Nov98 							RadarItemPtr->World.Z - me->World.Z,
//DeadCode RDH 29Nov98 							RequiredRange,dummy1,dummy2);
//DeadCode RDH 13Apr99 
//DeadCode RDH 13Apr99 		RequiredRange = Math_Lib.distance3d(RadarItemPtr->World.X - me->World.X,
//DeadCode RDH 13Apr99 											RadarItemPtr->World.Y - me->World.Y,
//DeadCode RDH 13Apr99 											RadarItemPtr->World.Z - me->World.Z	);
//DeadCode RDH 13Apr99 
//DeadCode RDH 13Apr99 		if (RequiredRange > 100000)								//RJS 11Dec98
//DeadCode RDH 13Apr99 			RequiredRange = 100000;								//RJS 11Dec98
//DeadCode RDH 13Apr99 																//RJS 11Dec98
//DeadCode RDH 13Apr99 		if (RequiredRange < 20000)								//RJS 11Dec98
//DeadCode RDH 13Apr99 			RequiredRange = 20000;								//RJS 11Dec98
//DeadCode RDH 13Apr99 	}
	bool fixsight;												//CSB 09Jun99
	if ((me->weap.weapontype & LT_MASK) == LT_BULLET)			//CSB 09Jun99
		fixsight = false;										//CSB 09Jun99
	else														//CSB 09Jun99
		fixsight = true;										//CSB 09Jun99
																//CSB 09Jun99
	me->fly.pModel->RememberForGunSight(fixsight,me);				//CSB 09Jun99

	GunSightPos.X = me->World.X;
	GunSightPos.Y = me->World.Y;
	GunSightPos.Z = me->World.Z;

	GunSightHdg = me->hdg;
	GunSightPitch = me->pitch;
	GunSightRoll = me->roll;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearRadar
//Author		Robert Slater
//Date			Thu 25 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ClearRadar()
{
	RadarItemPtr = NULL;
	ResetRadar(NULL,0,0,0);
	radarTimer = -1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddSmokeCloud
//Author		Robert Slater
//Date			Fri 3 Jul 1998
//
//Description	Kill the oldest smoke point,
//				Then launch transient smoke cloud...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::AddSmokeCloud(TrailRecord* trailptr, ShapeNum	cloudshape, int index)
{
//DeadCode RJS 20Oct00 	Coords3DList*	apoint = trailptr->thelist;
//DeadCode RJS 20Oct00 	Coords3DList*	npoint;
//DeadCode RJS 20Oct00 	Coords3DList*	*lpointptr = &trailptr->thelist;
//DeadCode RJS 20Oct00 	COORDS3D		World;
//DeadCode RJS 20Oct00 
//DeadCode RJS 20Oct00 	World.X = 0;
//DeadCode RJS 20Oct00 	World.Y = 0;
//DeadCode RJS 20Oct00 	World.Z = 0;
//DeadCode RJS 20Oct00 
//DeadCode RJS 20Oct00 	while (apoint)
//DeadCode RJS 20Oct00 	{
//DeadCode RJS 20Oct00 		npoint = apoint->next;
//DeadCode RJS 20Oct00 		if (npoint == NULL)
//DeadCode RJS 20Oct00 		{
//DeadCode RJS 20Oct00 			World.X = apoint->trailpoint.gx;
//DeadCode RJS 20Oct00 			World.Y = apoint->trailpoint.gy;
//DeadCode RJS 20Oct00 			World.Z = apoint->trailpoint.gz;
//DeadCode RJS 20Oct00 
//DeadCode RJS 20Oct00 			delete apoint;
//DeadCode RJS 20Oct00 			trailptr->nopoints--;
//DeadCode RJS 20Oct00 
//DeadCode RJS 20Oct00 			apoint = NULL;
//DeadCode RJS 20Oct00 			*lpointptr = NULL;
//DeadCode RJS 20Oct00 		}
//DeadCode RJS 20Oct00 		else
//DeadCode RJS 20Oct00 		{
//DeadCode RJS 20Oct00 			lpointptr = &apoint->next;
//DeadCode RJS 20Oct00 			apoint = npoint;
//DeadCode RJS 20Oct00 		}
//DeadCode RJS 20Oct00 	}
//DeadCode RJS 20Oct00 
//DeadCode RJS 20Oct00 	if (cloudshape && (trailptr->cloudlaunched==FALSE))
//DeadCode RJS 20Oct00 	{
//DeadCode RJS 20Oct00 		WorldStuff*	worldptr = mobileitem::currworld;
//DeadCode RJS 20Oct00 
//DeadCode RJS 20Oct00 		trailptr->cloudlaunched = TRUE;
//DeadCode RJS 20Oct00 		Trans_Obj.LaunchSmokeCloud((mobileitem*) object_obj3d->ItemPtr,
//DeadCode RJS 20Oct00 									cloudshape,
//DeadCode RJS 20Oct00  									World,
//DeadCode RJS 20Oct00 									*worldptr	);
//DeadCode RJS 20Oct00 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DefaultAnimData
//Author		Robert Slater
//Date			Mon 6 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::DefaultAnimData(itemptr itm, animptr&	adptr, Bool isReplay)
{
	ShapeDescPtr	sdptr;
	UByteP			instr_ptr;
	Bool			haslaunchers = FALSE;

	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);

	animptr	animdataptr = adptr;

	globinitairitem = NULL;
	globinititem = itm;											//RJS 21Apr99

	//This has been moved because of SAGs !!
	if ((itm->Status.size == AirStrucSize) && (isReplay == FALSE))
	{
		AirStrucPtr	asptr = (AirStrucPtr) itm;

		asptr->weap.Weapons = AnimWeaponPack;										//AMM 31Aug00

		asptr->weap.shpweapindex = 0;					//RDH 03Aug98

		asptr->weap.left.reloadmass = 0;				//RJS 25Jan99
		asptr->weap.left.reloaddrag = 0;				//RJS 25Jan99
		asptr->weap.left.mass = 0;
		asptr->weap.left.drag = 0;

		asptr->weap.centre.reloadmass = 0;				//RJS 25Jan99
		asptr->weap.centre.reloaddrag = 0;				//RJS 25Jan99
		asptr->weap.centre.mass = 0;
		asptr->weap.centre.drag = 0;

		asptr->weap.right.reloadmass = 0;				//RJS 25Jan99
		asptr->weap.right.reloaddrag = 0;				//RJS 25Jan99
		asptr->weap.right.mass = 0;
		asptr->weap.right.drag = 0;

		asptr->weap.UseIntFuel = TRUE;		//Default fuel switch	RJS 23Jun98
		asptr->weap.FuelDumped = TRUE;		//Default fuel dump		RJS 23Jun98
		asptr->weap.weapforce = 0;			//Weapon force
		asptr->weap.Ejected = FALSE;
		asptr->weap.StoresDumped = TRUE;	//Default dumped//RJS 18Jun99

		asptr->lasthitter.count = (UniqueID)0;								//RJS 23May99

		globinitairitem = asptr;
		globinitairitem->weap.weapontype = LT_CONTACT;					//RJS 21Jun00
	}


	switch (SHAPESTUFF.GetShapeScale(sdptr))					//PD 23Apr96
	{
		case SHP_GRP:
		{
			SLong		tmp;
			ShapeNum	newshp;
			SLong		gindex = 0;								//RJS 08Dec99

			instr_ptr = (UByteP )sdptr + sdptr->liveshpref;

			while (GetGroupElement(instr_ptr,newshp,tmp,tmp,tmp))
			{
				if (GetNumberOfLaunchers(newshp) > 0)
					haslaunchers = TRUE;

				InitItemAnim(animdataptr,newshp,gindex);		//RJS 08Dec99
				animdataptr[0] = 0x80;							//RJS 21Apr99
				animdataptr += 1;								//RJS 21Apr99
				gindex++;										//RJS 08Dec99
			}

			sdptr->Type.haslaunchers = haslaunchers;			//RJS 08Dec99

//DeadCode RJS 08Dec99 			if (haslaunchers)
//DeadCode RJS 08Dec99 				sdptr->Type.haslaunchers = TRUE;
//DeadCode RJS 08Dec99 			else
//DeadCode RJS 08Dec99 				sdptr->Type.haslaunchers = FALSE;

			break;
		}
		case SHP_1CM:
		case SHP_4CM:
		case SHP_16CM:
//DEADCODE CSB 06/06/00 			if ((itm->Status.size == AirStrucSize) && (isReplay == FALSE))//RJS 06Jul98
//DEADCODE CSB 06/06/00 			{
//DEADCODE CSB 06/06/00 				AirStrucPtr	asptr = (AirStrucPtr) itm;
//DEADCODE CSB 06/06/00 
//DEADCODE CSB 06/06/00 //DEADCODE JIM 09/12/99 				asptr->fly.inRadarSight = FALSE;				//RJS 13May99
//DEADCODE CSB 06/06/00 
//DEADCODE CSB 06/06/00 				asptr->weap.shpweapindex = 0;					//RDH 03Aug98
//DEADCODE CSB 06/06/00 
//DEADCODE CSB 06/06/00 				asptr->weap.left.reloadmass = 0;				//RJS 25Jan99
//DEADCODE CSB 06/06/00 				asptr->weap.left.reloaddrag = 0;				//RJS 25Jan99
//DEADCODE CSB 06/06/00 				asptr->weap.left.mass = 0;
//DEADCODE CSB 06/06/00 				asptr->weap.left.drag = 0;
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.left.int_fuel = 0;
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.left.int_fuel_leakage = 0;
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.left.int_launcher = -1;				//RJS 25Mar99
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.left.ext_fuel = 0;					//RJS 25Mar99
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.left.ext_fuel_leakage = 0;			//RJS 25Mar99
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.left.ext_launcher = -1;				//RJS 25Mar99
//DEADCODE CSB 06/06/00 
//DEADCODE CSB 06/06/00 				asptr->weap.centre.reloadmass = 0;				//RJS 25Jan99
//DEADCODE CSB 06/06/00 				asptr->weap.centre.reloaddrag = 0;				//RJS 25Jan99
//DEADCODE CSB 06/06/00 				asptr->weap.centre.mass = 0;
//DEADCODE CSB 06/06/00 				asptr->weap.centre.drag = 0;
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.centre.int_fuel = 0;
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.centre.int_fuel_leakage = 0;
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.centre.int_launcher = -1;			//RJS 25Mar99
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.centre.ext_fuel = 0;				//RJS 25Mar99
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.centre.ext_fuel_leakage = 0;		//RJS 25Mar99
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.centre.ext_launcher = -1;			//RJS 25Mar99
//DEADCODE CSB 06/06/00 
//DEADCODE CSB 06/06/00 				asptr->weap.right.reloadmass = 0;				//RJS 25Jan99
//DEADCODE CSB 06/06/00 				asptr->weap.right.reloaddrag = 0;				//RJS 25Jan99
//DEADCODE CSB 06/06/00 				asptr->weap.right.mass = 0;
//DEADCODE CSB 06/06/00 				asptr->weap.right.drag = 0;
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.right.int_fuel = 0;
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.right.int_fuel_leakage = 0;
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.right.int_launcher = -1;			//RJS 25Mar99
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.right.ext_fuel = 0;					//RJS 25Mar99
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.right.ext_fuel_leakage = 0;			//RJS 25Mar99
//DEADCODE CSB 06/06/00 //DeadCode RJS 26Nov99				asptr->weap.right.ext_launcher = -1;			//RJS 25Mar99
//DEADCODE CSB 06/06/00 
//DEADCODE CSB 06/06/00 				asptr->weap.UseIntFuel = TRUE;		//Default fuel switch	RJS 23Jun98
//DEADCODE CSB 06/06/00 				asptr->weap.FuelDumped = TRUE;		//Default fuel dump		RJS 23Jun98
//DEADCODE CSB 06/06/00 				asptr->weap.weapforce = 0;			//Weapon force
//DEADCODE CSB 06/06/00 				asptr->weap.Ejected = FALSE;
//DEADCODE CSB 06/06/00 				asptr->weap.StoresDumped = TRUE;	//Default dumped//RJS 18Jun99
//DEADCODE CSB 06/06/00 
//DEADCODE CSB 06/06/00 				asptr->lasthitter.count = (UniqueID)0;								//RJS 23May99
//DEADCODE CSB 06/06/00 
//DEADCODE CSB 06/06/00 				globinitairitem = asptr;
//DEADCODE CSB 06/06/00 			}

			InitItemAnim(animdataptr,itm->shape);					//RJS 13May98
			break;
	}

// Default launcher, if necessary...
	if (globinitairitem && globinitairitem->weap.weapontype >= LT_BOMB)	//RJS 27Jun00
		globinitairitem->weap.weapontype = LT_BULLET_REAR;				//RJS 27Jun00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScanAnimData
//Author		Robert Slater
//Date			Mon 6 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	shape::ScanAnimData(itemptr	itm)
{
	int	ChangeCnt = 0;

	SLong	animdatasize = GetAnimDataSize(itm->shape);
	if (itm->Anim != NULL)
	{
		UByteP	adptr2 = new UByte[animdatasize];
		if (adptr2)
		{
			UByteP	adptr = &itm->Anim[0];						//RJS 26May99
			UByte	oldval, newval;
			UWord	newoffset = 0;
			UWord	oldoffset = 0;
			UByteP	temp;
			animptr newanimdata = itm->Anim;					//RJS 26May99
			int		animcnt;									//RJS 26May99

			temp=adptr2;
			newanimdata = adptr2;

			memset(adptr2,0,animdatasize);	//Banana
			if (itm->Status.size == AIRSTRUCSIZE)						//RJS 27May99
				AnimWeaponPack = ((AirStrucPtr)itm)->weap.Weapons;		//RJS 27May99
			else														//RJS 27May99
				AnimWeaponPack = 0;										//RJS 27May99

			DefaultAnimData(itm,newanimdata,TRUE);

//Dead			AircraftAnimData*	acanimnow = (AircraftAnimData*) adptr;
//Dead			AircraftAnimData*	acanimdefault = (AircraftAnimData*) adptr2;

#ifndef NDEBUG
			int mycount=0;												//AMM 3Oct00
#endif

			for (animcnt = 0; animcnt < animdatasize; animcnt++)//DAW 26May99
			{
				oldval = *adptr2;
				newval = *adptr;								//DAW 26May99

				if (newval != oldval)
				{
					AnimDeltaList[ChangeCnt].deltaoffset = newoffset - oldoffset;
					AnimDeltaList[ChangeCnt++].newbyte = newval;

					oldoffset = newoffset;

#ifndef NDEBUG
					if (_DPlay.Implemented && _DPlay.GameType<DPlay::COMMSQUICKMISSION)
					{
						mycount+=AnimDeltaList[ChangeCnt-1].deltaoffset;	//AMM 3Oct00
						if (mycount>animdatasize)									//AMM 3Oct00
							INT3;											//AMM 3Oct00
					}
#endif
				}

				newoffset++;

				adptr2++;
				adptr++;										//DAW 26May99

//DeadCode DAW 26May99 				animdatasize--;
			}

			adptr2=temp;
			delete[]adptr2;
		}
	}

	return(ChangeCnt);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PatchAnimData
//Author		Robert Slater
//Date			Mon 6 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::PatchAnimData(itemptr	itm, int count)
{
	int	ChangeCnt = 0;

	SLong	animdatasize = GetAnimDataSize(itm->shape);
	if (itm->Anim != NULL)
	{
		animptr	adptr = itm->Anim;
		UByte	newval;
		UWord	newoffset = 0;

		ChangeCnt = 0;
		newoffset = 0;

		do
		{
			newoffset += AnimDeltaList[ChangeCnt].deltaoffset;
			newval = AnimDeltaList[ChangeCnt++].newbyte;// = newval;

			if (newoffset < animdatasize)
				adptr[newoffset] = newval;
			else
			{
#ifndef NDEBUG
				_Error.EmitSysErr(__FILE__": Playback anim data wrong size!");
#endif
				break;
			}

		}while (ChangeCnt < count);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LogCollision
//Author		Robert Slater
//Date			Tue 7 Jul 1998
//
//Description	
//
//Inputs		grpel    -1  not group    ----> log is 0
//						  0  element 1	  ----> log is 1
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::LogCollision(	ItemPtr		itm,
								ItemPtr		killer,
								ShapeNum	shapehit,
								UByteP		instr_ptr,
								SLong		grpel,
								int			coltype,
								int			colstrength,
								UByte		send		)//DAW 18Sep98
{
	if (ColLogCnt < MaxColLogs)
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shapehit);//A REAL CHANGE!! 02Dec98
		UByteP			inst_base = (UByteP )sdptr + sdptr->CollisionOffset;

		ColLog[ColLogCnt].theShooter = killer;		//RJS 11Mar99
		ColLog[ColLogCnt].item = itm;
		ColLog[ColLogCnt].shapehit = shapehit;
		ColLog[ColLogCnt].coloffset = instr_ptr - inst_base;
		ColLog[ColLogCnt].grpel = grpel + 1;// //RJS 16Sep98
		ColLog[ColLogCnt].coltype = coltype;
		ColLog[ColLogCnt].send=send;							//AMM 31Aug98
		ColLog[ColLogCnt++].colstrength = colstrength;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FixupColLog
//Author		Robert Slater
//Date			Tue 7 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::FixUpColLog()
{
	ShapeDescPtr	sdptr;
	UByteP			inst_col;
	int				index = 0;
	Bool			go=TRUE;
	UByteP			instr_ptr;
	Bool			oldcolon = CollisionOn;
	UWord			instruction;
	UWord			Hit_Offset;											//RJS 19Jun00
	Bool			oldFixUpState = FixUpCollision;						//AMM 4Jul00

	while (index < ColLogCnt)
	{
		sdptr = SHAPESTUFF.GetShapePtr((ShapeNum)ColLog[index].shapehit);//AMM 26Nov98
 
		instr_ptr = (UByteP )sdptr + sdptr->CollisionOffset;
		inst_col = instr_ptr + ColLog[index].coloffset;
		CollisionOn = FALSE;
		FixUpCollision = TRUE;
		CollisionCnt = 0;
		Hit_Offset = 0;

		while (go)
		{
			instruction = (UWord) *instr_ptr;
			instr_ptr ++;

			if ((instr_ptr == inst_col) || (instr_ptr > inst_col))
				break;

			(*InterpTable[instruction]) (instr_ptr);
		}

		// Hit_Offset (actually 9 bits now)
		// | 000 | 000000 |

		if (ColLog[index].grpel == 0)							//AMM 24Jun99
			Hit_Offset = CollisionCnt;									//RJS 19Jun00
		else													//AMM 24Jun99
		{														//AMM 24Jun99
			// Can only have 7 hit boxes per group element		//AMM 24Jun99
 			Hit_Offset = CollisionCnt << 6;								//RJS 19Jun00
 			Hit_Offset |= (ColLog[index].grpel-1);						//RJS 19Jun00
		}														//AMM 24Jun99

//DeadCode RJS 20Oct00 		ItemPtr	hitterscorer=Persons2::PlayerSeenAC;

		if (ColLog[index].send)									//AMM 31Aug98
		{

// pass in the hitter here as well.....RJS 11Mar99

			_DPlay.NewCollision2(ColLog[index].item->uniqueID.count,		//14BITS
								Hit_Offset,					// 9-bits			//RJS 19Jun00
								ColLog[index].coltype,					//3 BITS
								ColLog[index].colstrength,		//6 bits
								ColLog[index].theShooter->uniqueID.count);		//RJS 11Mar99
//								hitterscorer->uniqueID.count);

			if (ColLog[index].send==2)
			{
// collision with another AC, send a kill launcher if its a comms AC

				if (ColLog[index].theShooter)
				{
					if (ColLog[index].theShooter->uniqueID.commsmove)
					{
// dont want to have a killer for these packets

//DeadCode AMM 11Oct00 						UByte temp=_DPlay.CommsKiller;
//DeadCode AMM 11Oct00 						_DPlay.CommsKiller=255;
						_DPlay.NewKillLauncher(ColLog[index].theShooter->uniqueID.count);
//DeadCode AMM 11Oct00 						_DPlay.CommsKiller=temp;
					}
				}
			}

//DeadCode AMM 18Mar99 			if (!_DPlay.Implemented)
//DeadCode AMM 18Mar99 			{
// if in replay can score now - no, wait till collision is processed!
//DeadCode AMM 18Mar99 			}
		}

		index++;
	}

	FixUpCollision = oldFixUpState;										//AMM 4Jul00
	CollisionOn = oldcolon;
	ColLogCnt = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToCollisionList
//Author		Robert Slater
//Date			Thu 17 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::AddToCollisionList(	SLong	uniqueid,
									SLong	element,
									SLong	hittype,
									SLong	hitstrength)
//DeadCode AMM 16Nov99 									UByte	pnum,
//DeadCode AMM 16Nov99 									bool	myscorer)
{
	ItemPtr	itm = (ItemPtr)Persons2::ConvertPtrUID(UniqueID(uniqueid));

	if (ColLogCnt < MaxColLogs)
	{
		SLong	grpel, hitel;
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);//AMM 24Jun99
		if (SHAPESTUFF.GetShapeScale(sdptr)==SHP_GRP)			//AMM 24Jun99
		{														//AMM 24Jun99
			grpel = element & 63;								//AMM 24Jun99
//DeadCode RJS 19Jun00 			hitel = (element >> 6) & 3;							//AMM 24Jun99
			hitel = (element >> 6) & 7;									//RJS 19Jun00
		}														//AMM 24Jun99
		else													//AMM 24Jun99
		{														//AMM 24Jun99
			grpel = -1;													//RJS 19Jun00
			hitel = element;									//AMM 24Jun99
		}														//AMM 24Jun99

		ColLog[ColLogCnt].send=0; //AMM27Nov98
		ColLog[ColLogCnt].item = itm;
		ColLog[ColLogCnt].coloffset = hitel;
//DeadCode RJS 19Jun00 		ColLog[ColLogCnt].grpel = grpel - 1;
		ColLog[ColLogCnt].grpel = grpel;								//RJS 19Jun00
		ColLog[ColLogCnt].coltype = hittype;
		ColLog[ColLogCnt].colstrength = hitstrength;			//AMM 08Apr99
		ColLog[ColLogCnt].shapehit=0;//AMM 03Jun99
		ColLog[ColLogCnt].theShooter=BoxCol::Col_Shooter;

		ColLogCnt++;											//AMM 08Apr99

		CollisionPlayback();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CollisionPlayback
//Author		Robert Slater
//Date			Tue 7 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::CollisionPlayback()
{
	if (ColLogCnt)
	{
		UByteP			instr_ptr;
		UWord			instruction;
		Obj3D			tmpobj3d;
		ShapeDescPtr	sdptr;
		int				index = 0;
		Bool			go=TRUE;
		Bool			oldcolon = CollisionOn;
		ItemPtr			itm;
		Bool			isDifferent;
		SWord			new_damage_GrpElmt;
		UWord			new_damage_Shape;
		Coords3D		colpos_impact;
		Coords3D		colpos_hititem;
		Coords3D		colpos_hitgrp;
		SLong			last_vdeltax, last_vdeltay, last_vdeltaz;//RJS 20May99
		SLong			vdeltax, vdeltay, vdeltaz;				//RJS 20May99
		SWord			sin_ang, cos_ang;						//RJS 20May99
		ANGLES			theHdg, thePitch;						//RJS 20May99
		SLong			theDist;
		SLong			dy,dh,dx,dz;							//RJS 20May99
		bool			isRotated;
		ItemPtr			lastItem = NULL;
		MATRIX   		omat;						
		MATRIX_PTR		obj_matrix = &omat;
		mobileitem*		tmpitm;
		SLong			scaleback;
		Coords3D*		posptr = &lastColBox.pos;						//RJS 19Oct00

		last_vdeltax = 0;
		last_vdeltay = 0;
		last_vdeltaz = 0;

		HitThisOffset = 0;
		DamageNow = TRUE;										
		CollisionCnt = 0;

		damage_Scale = 2;	
		
		bool	oldState = BoxCol::SetTestState(true);					//AMM 4Jul00

		while (index < ColLogCnt)
		{															//AMM 26Nov98
#ifdef	_REPLAYCOL_
			::AfxTrace("R!\n");
#endif
			itm = ColLog[index].item;								//AMM 26Nov98
																	//AMM 26Nov98
			new_damage_Shape = itm->shape;							//AMM 26Nov98
			new_damage_GrpElmt = ColLog[index].grpel;				//AMM 26Nov98
																	//AMM 26Nov98
 			sdptr = SHAPESTUFF.GetShapePtr(new_damage_Shape);		//AMM 26Nov98
																	//AMM 26Nov98
			damage_Sdptr = (UByteP) sdptr;							//AMM 26Nov98
			damage_AnimPtr = itm->Anim;							//DAW 23Apr99

			BoxCol::Col_Shooter = ColLog[index].theShooter;			//RJS 11Mar99

			colpos_hitgrp = itm->World;
			colpos_hititem = itm->World;
			colpos_impact = itm->World;

// Null the hitpos coords...
			posptr->X = 0;
			posptr->Y = 0;
			posptr->Z = 0;
			lastColBox.radius = sdptr->Size << 4;						//RJS 19Oct00

			isRotated = true;

			if (new_damage_GrpElmt != -1)
			{
				UByteP	instr_ptr2 = (UByteP) damage_Sdptr + sdptr->liveshpref;
				UByte	groupel = -1;
				UByteP	Col_GroupPrev = NULL;
				UByteP	Col_GroupNext = NULL;
				animptr	Col_AnimPrevPtr;						//DAW 23Apr99
				animptr	Col_AnimNextPtr = damage_AnimPtr;		//DAW 23Apr99
				animptr	Col_TokenDepAnim;						//DAW 23Apr99
				SLong	tmpx,tmpy,tmpz;

				forever
				{
					instruction = *instr_ptr2;

					instr_ptr2++;

					if (instruction == dogroupno)
					{
						DOGROUP_PTR	gptr = (DOGROUP_PTR) instr_ptr2;
						
						new_damage_Shape = gptr->shapenum;
						tmpx = gptr->xoffset;
						tmpy = gptr->yoffset;
						tmpz = gptr->zoffset;
						
						groupel++;

						instr_ptr2 += sizeof(DOGROUP);	

						damage_AnimPtr = Col_AnimNextPtr;

						if (groupel == new_damage_GrpElmt)
						{
							sdptr = SHAPESTUFF.GetShapePtr(new_damage_Shape);

							lastColBox.radius = sdptr->Size << 4;		//RJS 19Oct00

							Col_AnimNextPtr += GetElementAnimOffset((ShapeNum)new_damage_Shape);

//DeadCode RJS 30 Jun99							instruction = *((UByteP)instr_ptr2+1);
							instruction = *((UByteP)instr_ptr2);			//RJS 30Jun99
							if (instruction == dogroupno)
								Col_GroupNext = (UByteP)instr_ptr2+1;
							else
								Col_GroupNext = NULL;

							colpos_hitgrp.X = colpos_hititem.X + tmpx;
							colpos_hitgrp.Y = colpos_hititem.Y + tmpy;
							colpos_hitgrp.Z = colpos_hititem.Z + tmpz;

							colpos_impact = colpos_hitgrp;

							SetGroupDamage(new_damage_GrpElmt,Col_GroupPrev,Col_GroupNext,Col_AnimPrevPtr,Col_AnimNextPtr,Col_TokenDepAnim);//DAW 07Apr99
							break;
						}
						else
						{
							Col_GroupPrev = instr_ptr2;

							Col_AnimPrevPtr = Col_AnimNextPtr;
							Col_AnimNextPtr += GetElementAnimOffset((ShapeNum)new_damage_Shape);
						}
					}
					else
						break;
				}
			}
			else
			{
				if (	((ColLog[index].coltype & FORCE_SET)==0)		//RJS 19Oct00
					&&	(itm->Status.size >= MOBILESIZE)	)
				{
					isRotated = true;
// Set up rotation matrix...
					if (lastItem != itm)
					{
						tmpitm = MobileItemPtr(itm);

						_matrix.generate2(tmpitm->hdg,tmpitm->pitch,tmpitm->roll,obj_matrix);
					}
				}
			}

			lastItem = itm;												//RJS 19Oct00

 			instr_ptr = (UByteP )sdptr + sdptr->CollisionOffset;

			collisionDepth = 0;											//RJS 19Jun00
			CollisionOn = FALSE;
			CollisionCnt = 0;
			Bool	oldFixUpState = FixUpCollision;						//AMM 4Jul00
			
			FixUpCollision = TRUE;										//AMM 4Jul00
			isDifferent = FALSE;

			damage_ItemPtr = itm;				//RJS 26Aug98
			damage_GrpElmt = new_damage_GrpElmt;				//RJS 27Apr99
			damage_Shape = (ShapeNum)new_damage_Shape;					//RJS 27Apr99

			Squad_Diary.SetAC(damage_ItemPtr,damage_AnimPtr);			//RJS 26Oct00

			while (go)
			{
				instruction = (UWord) *instr_ptr;
				instr_ptr ++;

				if (CollisionCnt == ColLog[index].coloffset)
				{
//DeadCode AMM 3Jul00 					FixUpCollision = FALSE;
					CollisionCnt = -1;
					CollisionOn = TRUE;
					collisionDepth++;									//AMM 3Jul00

					if (ColLog[index].coltype & FORCE_SET)				//RJS 19Jun00
					{
//DeadCode RJS 19Jun00 						damage_ItemState = (ColLog[index].coltype*BS_DEAD)/FORCE_LEVEL4;
						damage_ItemState = BoxCol::HitterStrength = (ColLog[index].colstrength*BS_DEAD)/FORCE_MAX;	//RJS 19Jun00
						BoxCol::HitterDamageType = ColLog[index].coltype - FORCE_SET;	//RJS 19Jun00
						HitThisOffset = 1;
					}
					else
					{
						HitThisOffset = 0;
						BoxCol::HitterStrength = ColLog[index].colstrength;
						BoxCol::HitterDamageType = ColLog[index].coltype;

						if (isRotated)										//RJS 19Oct00
						{
							isRotated = false;								//RJS 19Oct00

							scaleback = _matrix.transform(obj_matrix,posptr->X,posptr->Y,posptr->Z);

 							posptr->X >>= (16-scaleback);
 							posptr->Y >>= (16-scaleback);
 							posptr->Z >>= (16-scaleback);
						}
					}

					colpos_impact.X += posptr->X;						//RJS 19Oct00
					colpos_impact.Y += posptr->Y;
					colpos_impact.Z += posptr->Z;

					vdeltax = colpos_impact.X - View_Point->World.X;
					vdeltay = colpos_impact.Y - View_Point->World.Y;
					vdeltaz = colpos_impact.Z - View_Point->World.Z;

					if (	(vdeltax != last_vdeltax)
						||	(vdeltay != last_vdeltay)
						||	(vdeltaz != last_vdeltaz)	)
					{
						Math_Lib.Intercept(vdeltax,vdeltay,vdeltaz,theDist,theHdg,thePitch);
						theDist = lastColBox.radius + 50;				//RJS 19Oct00

						Math_Lib.high_sin_cos(thePitch,sin_ang,cos_ang);

						dy = (sin_ang * theDist)/ANGLES_FRACT;
						dh = (cos_ang * theDist)/ANGLES_FRACT;

						Math_Lib.high_sin_cos(theHdg,sin_ang,cos_ang);

						dx = (sin_ang * dh)/ANGLES_FRACT;
						dz = (cos_ang * dh)/ANGLES_FRACT;
					}

					last_vdeltax = vdeltax;						//RJS 20May99
					last_vdeltay = vdeltay;						//RJS 20May99
					last_vdeltaz = vdeltaz;						//RJS 20May99

					BoxCol::colpos_impact.X = colpos_impact.X - dx;	//RJS 20May99
					BoxCol::colpos_impact.Y = colpos_impact.Y - dy;	//RJS 20May99
					BoxCol::colpos_impact.Z = colpos_impact.Z - dz;	//RJS 20May99

					BoxCol::colpos_hititem = colpos_hititem;				//RJS 20Apr99
					BoxCol::colpos_hitgrp = colpos_hitgrp;				//RJS 20Apr99
				}

				if (	((instruction == doretno) && collisionDepth)	//RJS 19Jun00
					||	(instruction==doendno))
					break;

				(*InterpTable[instruction]) (instr_ptr);
			}

			Squad_Diary.UpdateACDamage();								//RJS 23Feb00

			index++;
			FixUpCollision = oldFixUpState;								//AMM 4Jul00

			BoxCol::ProcessEffectQueue(itm);			//RJS 15Jan99
		}

		BoxCol::SetTestState(oldState);									//AMM 4Jul00

		ColLogCnt = 0;
		CollisionOn = oldcolon;
//DeadCode AMM 03Jun99 		ColLogCnt = 0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToTree
//Author		Robert Slater
//Date			Wed 8 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::AddToTree(int	vertex)
{
//DeadCode RJS 19May00 	SphTreeTypeP	NewTree = &SphereTreeTable[vertex];
//DeadCode RJS 19May00 	SphTreeTypeP 	TreeRoot = SphereTree;
//DeadCode RJS 19May00 	Float			bodyz = newco[vertex].bodyz.f;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	NewTree->vertex = vertex;
//DeadCode RJS 19May00 	NewTree->left = NULL;
//DeadCode RJS 19May00 	NewTree->right = NULL;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	if (SphereTree == NULL)
//DeadCode RJS 19May00 		SphereTree = NewTree;
//DeadCode RJS 19May00 	else
//DeadCode RJS 19May00 	{
//DeadCode RJS 19May00 		while (TreeRoot)
//DeadCode RJS 19May00 		{
//DeadCode RJS 19May00 			if (bodyz <= newco[TreeRoot->vertex].bodyz.f)
//DeadCode RJS 19May00 			{
//DeadCode RJS 19May00 				if (TreeRoot->left == NULL)
//DeadCode RJS 19May00 				{
//DeadCode RJS 19May00 					TreeRoot->left = NewTree;
//DeadCode RJS 19May00 					break;
//DeadCode RJS 19May00 				}
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 				TreeRoot = TreeRoot->left;
//DeadCode RJS 19May00 			}
//DeadCode RJS 19May00 			else
//DeadCode RJS 19May00 			{
//DeadCode RJS 19May00 				if (TreeRoot->right == NULL)
//DeadCode RJS 19May00 				{
//DeadCode RJS 19May00 					TreeRoot->right = NewTree;
//DeadCode RJS 19May00 					break;
//DeadCode RJS 19May00 				}
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 				TreeRoot = TreeRoot->right;
//DeadCode RJS 19May00 			}
//DeadCode RJS 19May00 		}
//DeadCode RJS 19May00 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RecurseTree
//Author		Robert Slater
//Date			Thu 9 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::RecurseTree(SphTreeTypeP 	TreeRoot)
{
//DeadCode RJS 19May00 	while (TreeRoot)
//DeadCode RJS 19May00 	{
//DeadCode RJS 19May00 		RecurseTree(TreeRoot->right);
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		SphereList[GlobSphereCnt++] = TreeRoot->vertex;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 		TreeRoot = TreeRoot->left;
//DeadCode RJS 19May00 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EmptyTree
//Author		Robert Slater
//Date			Thu 9 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::EmptyTree()
{
//DeadCode RJS 19May00 	GlobSphereCnt = 0;
//DeadCode RJS 19May00 	RecurseTree(SphereTree);
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	SphereTree = NULL;
//DeadCode RJS 19May00 
//DeadCode RJS 19May00 	return(GlobSphereCnt);

	return 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCloudFade
//Author		Robert Slater
//Date			Thu 16 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SetCloudFade()
{
/*	if (OldWhiteFade != DoWhiteFade)
	{
		GREY3DTYPE	softfade;

		if (DrawnClouds)
		{
			if (doingHW3D)					
				current_screen->DoSetFade((Colour)26,DoWhiteFade,TDE_UNIFORM);
			else
			{
				softfade = (GREY3DTYPE) (DoWhiteFade>>2);

//DEAD				POLYGON.SetFadeData(_WHITEOUT);
//DEAD				POLYGON.SetFaded3DType(softfade);
			}
		}
		else
		{
			DoWhiteFade = 0;
			if (doingHW3D)							
				current_screen->DoSetFade((Colour)26,0,TDE_UNIFORM);
			else
			{
				softfade = (GREY3DTYPE) 0;

//DEAD				POLYGON.SetFadeData(_WHITEOUT);
//DEAD				POLYGON.SetFaded3DType(softfade);
			}
		}

		OldWhiteFade = DoWhiteFade;
	}
	*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitCloudFade
//Author		Robert Slater
//Date			Thu 16 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::InitCloudFade()
{
	DrawnClouds = FALSE;
	DoWhiteFade = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMuzzleInfo
//Author		Robert Slater
//Date			Thu 23 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord	shape::GetMuzzleIndex(LnchrType	launcher)
{
	UWord	cnt = 0;
	UWord	retval = 0;

	while (launcherdata[cnt].lnchrtype != LT_CONTACT)		//RJS 25Jan99
	{
		if (launcherdata[cnt].lnchrtype == launcher)
		{
			retval = cnt;
			if (retval > MaxMuzzles)
				MaxMuzzles = retval;

			break;
		}

		cnt++;
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DirectWeaponLauncher
//Author		Dave Whiteside
//Date			Wed 29 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
WeapAnimData* shape::DirectWeaponLauncher(	itemptr	itm,
											UByte	index,
											UWord&	theShape,
											SLong&	xpos,
											SLong&	ypos,
											SLong&	zpos,
//DEADCODE AMM 23/11/99 											UWord&	MuzzleVel,
											ULong&	MuzzleVel, //AMM 23/11/99
											UWord&	MuzzleDelay,
											UByte&  ltype	)
{
	ShapeDescPtr		sdptr;
	DOLAUNCHER_PTR		thislaunch = NULL;
	animptr				animdataptr;
	UByteP				instr_ptr;
	ShapeNum			shape;
	WeapAnimData*		weapon=NULL;
	MoveGunAnimData*	aptr;
	UByte				thisscale = 0;
	SLong				muzindex;								//DAW 29Jul98
	SLong				shapeIndex = index;						//RJS 27Jun00

	shape= itm->shape;

	animdataptr = itm->Anim;

	ltype = LT_BULLET;	//Default
	theShape = (UWord) BULLET;					//RJS 01Jul99

	aptr = (MoveGunAnimData*) animdataptr;
	sdptr = SHAPESTUFF.GetShapePtr(shape);

	if ((index >= 0) && (index < aptr->nolaunchers))
	{
		switch(SHAPESTUFF.GetShapeScale(sdptr))
		{
			case SHP_1CM:
				thisscale = 0;
				break;												
			case SHP_4CM:
				thisscale = 2;										
				break;												
			case SHP_16CM:
				thisscale = 4;										
				break;
		}
//DeadCode RJS 27Jun00 		thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shape,index);
//DeadCode RJS 27Jun00 
//DeadCode RJS 27Jun00 		if (thislaunch)
//DeadCode RJS 27Jun00 		{
//DeadCode RJS 27Jun00 			if (	(thislaunch->lnchrtype < LT_CONTACT)
//DeadCode RJS 27Jun00 				||	(thislaunch->lnchrtype > CT_DUMMY)	)
//DeadCode RJS 27Jun00 			{
//DeadCode RJS 27Jun00  				if (index < 10)						
//DeadCode RJS 27Jun00 				{
//DeadCode RJS 27Jun00 					weapon = &aptr->weaponlaunchers[index];
//DeadCode RJS 27Jun00 					if (weapon)
//DeadCode RJS 27Jun00 					{
//DeadCode RJS 27Jun00 						ltype = weapon->LauncherType;
//DeadCode RJS 27Jun00 
//DeadCode RJS 27Jun00 						muzindex = weapon->LaunchTime & 0x00FF;	//RDH 03Aug98
//DeadCode RJS 27Jun00 						if (muzindex > MaxMuzzles)						//RDH 03Aug98
//DeadCode RJS 27Jun00 							muzindex = 0;								//RDH 03Aug98
//DeadCode RJS 27Jun00 		
//DeadCode RJS 27Jun00 						MuzzleVel = launcherdata[muzindex].muzlvel;//DAW 29Jul98
//DeadCode RJS 27Jun00 						MuzzleDelay = launcherdata[muzindex].firingdelay;//DAW 29Jul98
//DeadCode RJS 27Jun00 						theShape = (UWord) launcherdata[muzindex].theShape;//RJS 01Jul99
//DeadCode RJS 27Jun00 					}
//DeadCode RJS 27Jun00 				}
//DeadCode RJS 27Jun00 				else
//DeadCode RJS 27Jun00 					_Error.EmitSysErr(__FILE__":Weapon launcher index out of range!");
//DeadCode RJS 27Jun00 			}
//DeadCode RJS 27Jun00 		}
		DOLAUNCHER	fiddledlauncher;

		weapon = &aptr->weaponlaunchers[index];
		if (weapon)
		{
			shapeIndex = weapon->launcherIndex;									//RJS 15Nov99
			if (weapon->stationshape)
			{
				// Get base x,y,z...
				thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shape,shapeIndex);	//RJS 15Nov99
				if (thislaunch)
				{
					// Real index and shape...
					DOLAUNCHER_PTR	thislaunch2;

					index = weapon->Stores - weapon->LoadedStores;
					thislaunch2 = (DOLAUNCHER_PTR) GetLauncherPos(ShapeNum(weapon->stationshape),index);//RJS 08Dec99
					if (thislaunch2)
					{
						// Sub launcher is relative to main launcher...
						fiddledlauncher = *thislaunch;
						fiddledlauncher.posx += thislaunch2->posx;
						fiddledlauncher.posy += thislaunch2->posy;
						fiddledlauncher.posz += thislaunch2->posz;
						thislaunch = &fiddledlauncher;
					}
				}
			}
			else
				thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shape,shapeIndex);	//RJS 15Nov99
		}
		else
			thislaunch = NULL;

		if (thislaunch)
		{
			SLong	noGuns = thislaunch->noChildren;
			SLong	gunno = weapon->currGun;

			if (	(thislaunch->lnchrtype < LT_CONTACT)
				||	(thislaunch->lnchrtype > CT_DUMMY)	)
			{
				if (weapon == NULL)
					_Error.EmitSysErr(__FILE__":Weapon launcher index out of range!");
			}

			ltype = weapon->LauncherType;

			if (noGuns && gunno)
			{
				if (gunno > noGuns)
					weapon->currGun = 0;
				else
					thislaunch = (DOLAUNCHER_PTR) ((UByteP)thislaunch + ((1+sizeof(DOLAUNCHER))*gunno));
			}

			muzindex = weapon->LaunchTime & 0x00FF;
			if (muzindex > MaxMuzzles)
				muzindex = 0;

			MuzzleVel = launcherdata[muzindex].muzlvel;
			MuzzleDelay = launcherdata[muzindex].firingdelay;

			theShape = UWord(launcherdata[muzindex].theShape);
		}
	}

 	LauncherToWorld(itm,(UByteP) thislaunch,thisscale,xpos,ypos,zpos,NULL);

	return(weapon);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetAnimData_NewShape
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
Bool	shape::ResetAnimData_NewShape(ItemPtr	itm,ShapeNum	newshape,UByte  weappack,bool sendPacket)
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
	Bool	valid = FALSE;
	SLong	animdatasize;
	
	sdptr = SHAPESTUFF.GetShapePtr(newshape);

	if (itm!=Persons2::PlayerSeenAC)
		sendPacket=0;

	// Only do if anim datas for old shape and replacement shape are the same...
	SLong olddatasize = GetAnimDataSize(itm->shape);
	animdatasize = GetAnimDataSize(newshape);
	if (olddatasize == animdatasize)
	{
		if (sendPacket && (_Replay.Record || _DPlay.Implemented))	//RJS 21Apr99
		{
			//Send a packet instead...
			_DPlay.NewShapePacket(itm->uniqueID.count,newshape);
		}
		else if (sendPacket && _Replay.Playback)
		{
// playback wait for packet
		}
		else
		{
			animdatasize = GetAnimDataSize(newshape);
			UByteP		adptr = (UByteP) &itm->Anim[0];

			memset(adptr,0,animdatasize);

			itm->shape = newshape;

			AnimWeaponPack = weappack;								//AMM 08Apr99

			DefaultAnimData(itm,itm->Anim,TRUE);
		}

		valid = TRUE;
	}

	return(valid);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillGear
//Author		Robert Slater
//Date			Mon 7 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::KillGear(ItemPtr	itm)
{
	if (itm->Status.size == AIRSTRUCSIZE)
	{
		AirStrucPtr	ac = (AirStrucPtr) itm;
		ac->fly.pModel->SetGearAnimPos(ac,ANIM_GEAR_AUTO,TRUE);	//Drop gear regardless
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGroupDamage
//Author		Robert Slater
//Date			Thu 17 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SetGroupDamage(	SLong	element,
								UByteP	gp,
								UByteP	gn,
								animptr	&gpa,
								animptr	&gna,
								animptr &tkndp	)
{
	damage_GrpElmt = element;					
	damage_GrpAnimPrev = gpa;					
	damage_GrpAnimNext = gna;
//DeadCode DAW 30Jun99 	if (gpa != NULL)
		damage_GrpPrev = gp;
//DeadCode DAW 30Jun99 	else
//DeadCode DAW 30Jun99 		damage_GrpPrev = NULL;

//DeadCode DAW 30Jun99 	if (gna != NULL)
		damage_GrpNext = gn;
//DeadCode DAW 30Jun99 	else
//DeadCode DAW 30Jun99 		damage_GrpNext = NULL;

	damage_GrpTokenDep = tkndp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FixUpGroupCol
//Author		Robert Slater
//Date			Thu 17 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::FixUpGroupCol()
{
//DeadCode DAW 30Jun99 	ShapeDescPtr	sdptr = (ShapeDescPtr) damage_Sdptr;
//DeadCode DAW 30Jun99 	UByteP			iptr = (UByteP) sdptr->liveshpref; 
//DeadCode DAW 30Jun99 	int				groupindex = 0;
//DeadCode DAW 30Jun99 	MinAnimData*	mad = (MinAnimData*) damage_AnimPtr;
//DeadCode DAW 30Jun99 	UByteP			PrevIptr;
//DeadCode DAW 30Jun99 	ShapeNum		newshape;
//DeadCode DAW 30Jun99 	SLong			ex,ey,ez;
//DeadCode DAW 30Jun99 	UByteP			Col_GroupPrev = NULL;
//DeadCode DAW 30Jun99 	UByteP			Col_GroupNext = NULL;
//DeadCode DAW 30Jun99 	animptr			Col_AnimPrevPtr;
//DeadCode DAW 30Jun99 	animptr			Col_AnimNextPtr = damage_AnimPtr;
//DeadCode DAW 30Jun99 	animptr			Col_TokenDepAnim;
//DeadCode DAW 30Jun99 
//DeadCode DAW 30Jun99 	while(GetGroupElement(iptr,newshape,ex,ey,ez,0,&PrevIptr))
//DeadCode DAW 30Jun99 	{
//DeadCode DAW 30Jun99 		Col_GroupNext = iptr + 1;
//DeadCode DAW 30Jun99 
//DeadCode DAW 30Jun99 		damage_AnimPtr = Col_AnimNextPtr;
//DeadCode DAW 30Jun99 		damage_Shape = newshape;													//RJS 16Nov98
//DeadCode DAW 30Jun99 
//DeadCode DAW 30Jun99 		Col_AnimNextPtr += GetElementAnimOffset(newshape);
//DeadCode DAW 30Jun99 		Col_AnimPrevPtr = Col_AnimNextPtr;						
//DeadCode DAW 30Jun99 		Col_GroupPrev = PrevIptr;
//DeadCode DAW 30Jun99 	
//DeadCode DAW 30Jun99 		if (groupindex != damage_GrpElmt)
//DeadCode DAW 30Jun99 			groupindex++;								
//DeadCode DAW 30Jun99 		else
//DeadCode DAW 30Jun99 			break;
//DeadCode DAW 30Jun99 	}
//DeadCode DAW 30Jun99 
//DeadCode DAW 30Jun99 	SetGroupDamage(damage_GrpElmt,Col_GroupPrev,Col_GroupNext,Col_AnimPrevPtr,Col_AnimNextPtr,Col_TokenDepAnim);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDistScale
//Author		Robert Slater
//Date			Fri 6 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ppTan(ANGLES ang,Float& tanAng)
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

void	shape::SetDistScale()
{
//DeadCode RJS 20Mar00 	DistScale = _matrix.FoV * (Float(640)/Float(winmode_w));

// Field of View?...
	Float	FoV;
	Float	aspectRatio;

	Angles viewConeAngle=Angles(UWord(Save_Data.fieldOfView)>>1);
	ppTan(viewConeAngle,FoV);
//DEADCODE RJS 3/21/00 	DistScale*=.5;

	View_Point->perspective_FoV = DistScale = FoV;

// Scale using default screen size of 640...

	ROWANSURFACEDESC	sdesc;
	sdesc.dwSize = sizeof(ROWANSURFACEDESC);
	if (g_lpLib3d->GetSurfaceDesc(&sdesc) == S_OK)
	{
		View_Point->perspective_Width = sdesc.dwWidth;
		DistScale *= Float(640)/Float(sdesc.dwWidth);

// tune ranges...
//DeadCode CSB 18Aug00 		DistScale *= 5./Float(1+Save_Data.contourDetail);					//RJS 10Aug00
		DistScale *= 6.0 / (3.0 + Save_Data.contourDetail);				//CSB 18Aug00

		aspectRatio = Float(sdesc.dwHeight)/Float(sdesc.dwWidth);
		aspectRatio *= FoV;

		SphereXScale=1./FoV;
		SphereYScale=1./aspectRatio;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetRader
//Author		Robert Slater
//Date			Fri 6 Nov 1998
//
//Description	Clear radar flags and generate view matrix view ac...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ResetRadar(AirStrucPtr	eye, SLong vx, SLong vy, SLong vz)
{
	FPMATRIX_PTR	matp = &radarMatrix;

	if (eye)
		_matrix.GenerateRadar(eye->hdg,eye->pitch,eye->roll,matp);

	viewer_x = vx;
	viewer_y = vy;
	viewer_z = vz;
	
	radarRange = RANGE_RADAR;
 	radarTmpItm = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetRadar
//Author		Robert Slater
//Date			Fri 6 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE JIM 09/12/99 void	shape::SetRadar()
//DEADCODE JIM 09/12/99 {
//DEADCODE JIM 09/12/99 	if (Manual_Pilot.ControlledAC2)
//DEADCODE JIM 09/12/99 	{
//DEADCODE JIM 09/12/99 		//Do we have a new lock?
//DEADCODE JIM 09/12/99 		if (RadarItemPtr != radarTmpItm)							//RJS 07Apr99
//DEADCODE JIM 09/12/99 			radarTimer = 0;	//pause for 1 sec...				//RJS 07Apr99
//DEADCODE JIM 09/12/99 	//		radarTimer = 100;	//pause for 1 sec...				//RJS 07Apr99
//DEADCODE JIM 09/12/99 
//DEADCODE JIM 09/12/99 		RadarItemPtr = radarTmpItm;
//DEADCODE JIM 09/12/99 		if (radarTmpItm)
//DEADCODE JIM 09/12/99 		{
//DEADCODE JIM 09/12/99 			if (radarTmpItm->Status.size == AIRSTRUCSIZE)
//DEADCODE JIM 09/12/99 				((AirStrucPtr)radarTmpItm)->fly.inRadarSight = TRUE;//RJS 13May99
//DEADCODE JIM 09/12/99 
//DEADCODE JIM 09/12/99  			RequiredRange = radarRange;
//DEADCODE JIM 09/12/99 			if (RequiredRange > 100000)								//RDH 13Apr99
//DEADCODE JIM 09/12/99 				RequiredRange = 100000;								//RDH 13Apr99
//DEADCODE JIM 09/12/99 																	//RDH 13Apr99
//DEADCODE JIM 09/12/99 			if (RequiredRange < 20000)								//RDH 13Apr99
//DEADCODE JIM 09/12/99 				RequiredRange = 20000;								//RDH 13Apr99
//DEADCODE JIM 09/12/99 		}
//DEADCODE JIM 09/12/99 		else
//DEADCODE JIM 09/12/99 		{
//DEADCODE JIM 09/12/99 			//if realistic radar, we can lock onto the ground...
//DEADCODE JIM 09/12/99 			if (Three_Dee.groundlockOn)								//RJS 04Jun99
//DEADCODE JIM 09/12/99 			{
//DEADCODE JIM 09/12/99 				UWord thePitch = Manual_Pilot.ControlledAC2->pitch;
//DEADCODE JIM 09/12/99 				if ((thePitch > ANGLES_240Deg) && (thePitch < ANGLES_300Deg))
//DEADCODE JIM 09/12/99 				{
//DEADCODE JIM 09/12/99 					//Ground lock!
//DEADCODE JIM 09/12/99 					SLong	radarRange = Manual_Pilot.ControlledAC2->fly.pModel->GroundHeight;
//DEADCODE JIM 09/12/99 					SLong	disang = thePitch - ANGLES_270Deg;
//DEADCODE JIM 09/12/99 					ULong	disfiddle = (radarRange * 77)>>9;
//DEADCODE JIM 09/12/99 
//DEADCODE JIM 09/12/99 					disang = (disang<0)?-disang:disang;
//DEADCODE JIM 09/12/99 
//DEADCODE JIM 09/12/99 					disfiddle *= disang;
//DEADCODE JIM 09/12/99 					disfiddle /= ANGLES_30Deg;
//DEADCODE JIM 09/12/99 
//DEADCODE JIM 09/12/99 					radarRange += disfiddle;
//DEADCODE JIM 09/12/99 				}
//DEADCODE JIM 09/12/99 
//DEADCODE JIM 09/12/99 				RequiredRange = radarRange;							
//DEADCODE JIM 09/12/99 				if (RequiredRange > 100000)							
//DEADCODE JIM 09/12/99 					RequiredRange = 100000;							
//DEADCODE JIM 09/12/99 																	
//DEADCODE JIM 09/12/99 				if (RequiredRange < 20000)							
//DEADCODE JIM 09/12/99 					RequiredRange = 20000;							
//DEADCODE JIM 09/12/99 			}
//DEADCODE JIM 09/12/99 
//DEADCODE JIM 09/12/99 			radarTimer = -1;										//RJS 07Apr99
//DEADCODE JIM 09/12/99 		}
//DEADCODE JIM 09/12/99 	}
//DEADCODE JIM 09/12/99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleTrailList
//Author		Robert Slater
//Date			Mon 23 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::SampleTrailList()
{
	SLong			index;
	ReplaySmkStruc	replaysmk;
	SLong			smkindex;

	ULong reallist=0;

	if (MAX_VAPOURS>32)
		_Error.SayAndQuit("MAX_VAPOURS>32");

	for (index=1; index < MAX_VAPOURS; index++)
	{
		if (traillist[index].thelist || traillist[index].beendrawn)
		{
			reallist|=1<<index;
		}
	}

	if (!_Replay.StoreSmkIndexData(reallist))
		return FALSE;

	for (index=1; index < MAX_VAPOURS; index++)
	{
		if (traillist[index].thelist || traillist[index].beendrawn)
		{
			if (traillist[index].SmkDescPtr)
			{
				smkindex = ((UByteP)(traillist[index].SmkDescPtr) - (UByteP)&SmokeTrlList[0]);
				smkindex /= sizeof(SmokeType);
			}
			else
				smkindex = -1;

			replaysmk.lifetime = traillist[index].lifetime;
			replaysmk.lastwx = traillist[index].lastwx;
			replaysmk.lastwy = traillist[index].lastwy;
			replaysmk.lastwz = traillist[index].lastwz;
			replaysmk.nextlist= traillist[index].nextlist;
			replaysmk.beendrawn= traillist[index].beendrawn;
			replaysmk.cloudlaunched= traillist[index].cloudlaunched;
			replaysmk.LaunchCountdown= traillist[index].LaunchCountdown;
			replaysmk.SampleTime= traillist[index].SampleTime;
			replaysmk.smkindex = smkindex;
			replaysmk.nopoints = traillist[index].nopoints;	//RJS 17Feb99
			replaysmk.transient = traillist[index].transient;	//RJS 18Feb99
			replaysmk.currTime = traillist[index].currTime;	//RJS 16Jun99
							  	
			if (!_Replay.StoreSmkData(&replaysmk,(UByteP)traillist[index].thelist))//RJS 17Feb99
				return FALSE;

		}
	}

	//Now sample static trails...
	//Header...
	UByte	smltrailtot = Trans_Obj.StaticTrailCnt;
	if (!_Replay.ReplayWrite(&smltrailtot,sizeof(smltrailtot)))	//RJS 18Feb99
		return FALSE;

	//Data...
	ReplaySmlSmkStruc	replaysmlsmk;
	SmokeTrailAnimData*	adptr;
	for (index = 0; index < MaxTrails; index++)						//RJS 08Apr99
	{
		if (Trans_Obj.StaticTrailList[index].item)				//RJS 13May99
		{
			adptr = (SmokeTrailAnimData*) Trans_Obj.StaticTrailList[index].item->Anim;//RJS 13May99

			if (Trans_Obj.StaticTrailList[index].item->Launcher)//RJS 13May99
			{
				replaysmlsmk.uniqueid = Trans_Obj.StaticTrailList[index].item->Launcher->uniqueID.count;//RJS 13May99

#ifndef NDEBUG
				if (!(Persons2::ConvertPtrUID((UniqueID)(replaysmlsmk.uniqueid))))
					INT3;
#endif
			}
			else
			{
				//The trail's launcher was also a transient,
				//so set up uniqueid to be YOU, to keep things clean...
				replaysmlsmk.uniqueid = Persons2::PlayerSeenAC->uniqueID.count;		//RJS 21Apr99
			}

			replaysmlsmk.lifetime = adptr->lifetime;
			replaysmlsmk.nopoints = adptr->nopoints;
			replaysmlsmk.smkindex = adptr->SmkDescIndex;
			replaysmlsmk.currTime = adptr->currTime;				//RJS 16Jun99

			if (!_Replay.StoreSmlSmkData(&replaysmlsmk,(UByteP)adptr->thelist))
				return FALSE;
		}
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSmokeTrailList
//Author		Robert Slater
//Date			Mon 23 Nov 1998
//
//Description	
//
//Inputs		dummy flag
//				... if dummy is true, we want to skip through all the data,
//					but do nothing with it.
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	shape::GetSmokeTrailList(Bool dummy)
{
	ULong bigindex;
	ReplaySmkStruc	replaysmk;
	SLong index;
	UByteP	listptr;											//RJS 18Feb99

	if (!_Replay.LoadSmkIndexData(bigindex))
		return FALSE;

	for (index=1; index < MAX_VAPOURS; index++)
	{
		if (bigindex&(1<<index))								//RJS 17Feb99
		{
// load smoke list
			listptr = NULL;										//RJS 18Feb99
			if (!_Replay.LoadSmkData(&replaysmk,dummy,listptr))//RJS 18Feb99
				return FALSE;

			if (!dummy)
			{
				SLong	smkindex = replaysmk.smkindex;

				traillist[index].lifetime =	replaysmk.lifetime;
				traillist[index].lastwx	= replaysmk.lastwx;
				traillist[index].lastwy	= replaysmk.lastwy;
				traillist[index].lastwz	= replaysmk.lastwz;
				traillist[index].nextlist = replaysmk.nextlist;
				traillist[index].beendrawn = replaysmk.beendrawn;
				traillist[index].cloudlaunched = (Bool)replaysmk.cloudlaunched;
				traillist[index].LaunchCountdown = replaysmk.LaunchCountdown;
				traillist[index].SampleTime	= replaysmk.SampleTime;
				if (smkindex > -1)
					traillist[index].SmkDescPtr = (UByteP)&SmokeTrlList[smkindex];
				else
					traillist[index].SmkDescPtr = NULL;

				traillist[index].thelist = (Coords3DList*)listptr;
				traillist[index].nopoints = replaysmk.nopoints;
				traillist[index].nextlist = 0;
				traillist[index].transient = replaysmk.transient;
				traillist[index].currTime = replaysmk.currTime;			//RJS 16Jun99
			}
		}
		else
		{
			if (!dummy)
			{
// null smoke list

			}
		}
	}

	UByte	smltrailtot;
//DeadCode AMM 20Apr99 	if (!_Replay.ReplayRead(&smltrailtot,sizeof(smltrailtot)))
	if (!_Replay.SmokeRead(&smltrailtot,sizeof(smltrailtot)))
		return FALSE;

	ReplaySmlSmkStruc	replaysmlsmk;
	Coords3D	centrepos;
	for (index = 0; index < smltrailtot; index++)
	{
		listptr = NULL;								
		if (_Replay.LoadSmlSmkData(&replaysmlsmk,dummy,listptr,centrepos))
		{
			if (!dummy)
				Trans_Obj.LaunchReplayTrail(centrepos,(UByteP)&replaysmlsmk,listptr);
		}
		else
			return FALSE;
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteAllSmokeTrails
//Author		Andy McMaster
//Date			Wed 4 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::DeleteAllSmokeTrails()
{
	SLong	i;

	//Just in case...											//DAW 21Jun99
	GenerateProbeTrails();										//DAW 21Jun99

	// First kill orphaned trail points...
	for (i=0; i < REAL_MAX_VAPOURS; i++)
	{
//		Coords3DList* apoint = traillist[i].FakePointPtr;
//		Coords3DList* dpoint;
// 
//		while (apoint)
//		{						
//			dpoint = apoint;
//			apoint = apoint->next;
//
//			delete dpoint;
//		}

		traillist[i].FakePointPtr->Wipe();
		traillist[i].FakePointPtr = NULL;
	}

	VapDeadCnt = 0;
	for (i=0; i < MAX_VAPOURS; i++)
		KillVapourStream(i);

	newprobecnt = 0;			//RJS 26Mar99
	Trans_Obj.CleanUpTrailList();									//RJS 18Feb99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		imapspherespin
//Author		Robert Slater
//Date			Mon 23 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::imapspherespin(	UWord vertex,
							UWord 	radius,	
							ImageMapNumber imapno,
							SWord	minx, SWord	miny,
							SWord	maxx, SWord	maxy,
							SWord	angle	)
{
	ImageMapDesc *pmap=Image_Map.GetImageMapPtr(imapno);
	g_lpLib3d->DrawSphere(	HMATERIAL(pmap),
							SHAPE.newco[vertex],
							D3DVALUE(radius),
							Angles(-angle),
							minx,miny,maxx,maxy);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawDirtTrail
//Author		Mark Shaw
//Date			Thu 10 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::DrawDirtTrail(	SWord		index,
								UByteP		smkinfo,
								ULong		LifeTime,
								Bool		valid	)
{
/*	if (index)
	{
		if (index < 0)											
			index = -index;

		if (index > MAX_VAPOURS)			
			_Error.EmitSysErr(__FILE__":(DOSMKTRAIL)    Shouldn't be this : %d\n",index);

		TrailRecordPtr	TrailPtr = &traillist[index];			
																
		if (smkinfo)											
			TrailPtr->SmkDescPtr = smkinfo;						
		else													
		{
			smkinfo = TrailPtr->SmkDescPtr;						
			LifeTime = TrailPtr->lifetime;						
		}

		SmokeTypeP		ptr = (SmokeTypeP) smkinfo;
		Coords3DList*	apoint;
		Coords3DList*	*lastpointptr;						
		Coords3DList*	nextpoint;							
		Coords3DList*	lastpoint;							
		SLong			nocyls = 0;
		SLong			lifegone, lifeleft;				
		SLong			distz,lastdistz;
		SWord			grow2time = ptr->Growth;
		UWord			startradius = ptr->Radius;
		SWord			radius;
		SWord			radiusinc;
 		SByte			frameno;
		SLong			degrade;
		ShapeNum		trailshape = (ShapeNum) ptr->Shape;
		SLong			degcnt;
		UByteP			lastdrawnobj = NULL;
		UByteP			thisdrawnobj = NULL;
		UWord			failedcnt = 0;
		VapAnimDat		AnimDat;
		VapAnimDatPtr	AnimDataPtr;
		SLong			timesincebirth;
		SLong			totcount = 0;
		SWord			hdist;
		SLong			reallife;

 		lastpointptr = &TrailPtr->thelist;
		degrade = ptr->DegradeDist << 4;
		distz = 0;
		degcnt = 0;

		apoint = lastpoint = TrailPtr->thelist;			
 		while (apoint)
 		{
 			nextpoint = apoint->next;
			lifeleft = reallife = apoint->lifeleft;				
 			if (!Three_Dee.IsPaused())							
 			{
				if (lifeleft == 0)
 				{
					// Add to dead list...
					apoint->next = TrailPtr->FakePointPtr;
					TrailPtr->FakePointPtr = apoint;
 
 					TrailPtr->nopoints--;
 					*lastpointptr = nextpoint;
 				}
				else
				{
					reallife -= Timer_Code.FRAMETIME;
					if (reallife < 0)
						reallife = 0;

					apoint->lifeleft = reallife;				//RJS 14Apr98
				}
			}

 			if (lifeleft)
 			{
				lifegone = apoint->LifeTime - lifeleft;
				radius = startradius + ((startradius*lifegone)/grow2time);

				apoint->radius = radius;
 				if (!degcnt || !nextpoint)
 				{
					if (lifegone > ptr->FadeTime)
					{
						if (ptr->FadeShape)
							trailshape = ptr->FadeShape;
					}

					distz = Three_Dee.AddVapourObject(	trailshape,
														(UByteP)apoint,
														lastdrawnobj,
														thisdrawnobj,
														failedcnt);

					if (thisdrawnobj)
					{
						AnimDat.depth = ptr->Depth;		//initial fade depth...
						AnimDat.drawit = CalcDirtDeltas( apoint,
														 lastpoint,
														 radius,
 														 apoint->xdelta,apoint->ydelta);//RJS 15Apr98

						AnimDataPtr = (VapAnimDatPtr) &((Obj3DPtr)thisdrawnobj)->AngR;//RJS 07Feb00
						*AnimDataPtr = AnimDat;

						lastdrawnobj = thisdrawnobj;
						nocyls++;
					}
					else
						failedcnt++;

					degcnt = distz / degrade;
				}												
				else											
					degcnt--;									

 				lastpointptr = &apoint->next;
 				lastpoint = apoint;

				totcount++;
 			}
 
 			apoint = nextpoint;
 		}

		apoint = TrailPtr->thelist;
		if (apoint && !valid)
		{
			TrailPtr->thelist = apoint->next;

			apoint->next = TrailPtr->FakePointPtr;
			TrailPtr->FakePointPtr = apoint;					

			TrailPtr->nopoints--;
		}
	}*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcDirtDeltas
//Author		Mark Shaw
//Date			Thu 10 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord	shape::CalcDirtDeltas(	Coords3DList*	apoint,
								Coords3DList*	lastpoint,
								UWord	radius,
								SWord	&xoff, SWord &yoff)
{
	DoPointStruc dopoint0,dopoint2;
	SLong		valid = 0;
	SWord		angleofcyl = 0;
	SWord		sin_ang, cos_ang;
	SLong		adjacent,opposite;

	xoff = 0;
	yoff = 0;

	adjacent = apoint->trailpoint.gx - lastpoint->trailpoint.gx;
	opposite = apoint->trailpoint.gz - lastpoint->trailpoint.gz;

	if (opposite || adjacent)
	{
		Float	res = 10430.37835047*FPATan(adjacent,opposite);
		angleofcyl = SWord(res);
 		angleofcyl -= ANGLES_90Deg;

		Math_Lib.high_sin_cos((Angles) angleofcyl,sin_ang,cos_ang);		//PD 13Nov97
		xoff = (sin_ang * radius) / ANGLES_FRACT;				
		yoff = (cos_ang * radius) / ANGLES_FRACT;

		valid = 1;
	}

	return(valid);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LogFuelDamage
//Author		Robert Slater
//Date			Mon 18 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::LogFuelDamage(	ItemPtr		itm,
								UByteP		weapon,
								SLong		launcherindex	)		//RJS 29Nov99
{
	SLong	foundtank = -1;
	SLong	fxpercent = 0;

	if (itm->Status.size == AIRSTRUCSIZE)
	{
		AirStrucPtr	ac = (AirStrucPtr) itm;
//DeadCode RJS 20Oct00 		SLong		subdamage = 31;
		SLong		weapelement = launcherindex;
//DeadCode RJS 20Oct00 		SLong		externalshape = 0;
//DeadCode RJS 20Oct00 		SLong		xDelta = 0;
		ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
		UByteP				instr_ptr;
		UWord				instruction;
		SLong				instsize = sizeof(DOLAUNCHER) + 1;
		SLong				tankindex;
		WeapAnimData*		weapptr = NULL;
		bool				isfuel = true;


		if (weapon)
		{
			weapptr = (WeapAnimData*)weapon;
			weapelement = weapptr->launcherIndex;
		}

		// Find relative launcher offset in shape...
		// Calc whether internal, external fuel hit,
		// Damage level and which wing....

		if (sdptr->LauncherDataSize)
		{
			instr_ptr = (UByteP )sdptr + sdptr->LauncherDataSize + (instsize * weapelement);

			instruction = (UWord) *instr_ptr;
			instr_ptr++;

			if (instruction == dolauncherno)
			{
				DOLAUNCHER_PTR	ptr = (DOLAUNCHER_PTR) instr_ptr;
				if (weapptr)									//RJS 09Dec99
				{
// Make sure we reset the weapon hdg to 0 if we are to take over this launcher
					if ((weapptr->LauncherType & LT_MASK) != LT_SMKTRAILS)	//RJS 12Jul00
						weapptr->hdg = 0;								//RJS 12Jul00

					weapptr->LauncherType = ptr->lnchrtype;		//RJS 09Dec99

					if (ptr->hdg < 0)		//hdg doubles as tank number
						isfuel = false;
					else
						tankindex = ptr->hdg;			
				}
			}
		}
		
		if (isfuel)
		{	
			if (tankindex > 4)									//RJS 09Dec99
				tankindex =0;									//RJS 09Dec99
																//RJS 09Dec99
			if (ac->classtype->fueltankcap[tankindex] > 0)		//RJS 09Dec99
				foundtank = tankindex;							//RJS 09Dec99

//DeadCode RJS 10Dec99			if (externalshape && (foundtank > -1))
//DeadCode RJS 10Dec99			{
//DeadCode RJS 10Dec99				if (ac->classtype->fueltanktype[foundtank] != FT_DROPTANK)
//DeadCode RJS 10Dec99					foundtank = -1;
//DeadCode RJS 10Dec99			}

			//Can we start a fire, or leak???
			if (foundtank > -1)
			{
				fxpercent = (ac->fly.fuel_content[foundtank]*2)/(ac->classtype->fueltankcap[foundtank]*10);
//DeadCode RJS 16Nov00 
//DeadCode RJS 16Nov00 				ac->fly.fuel_content[tankindex] = 0;
//DeadCode RJS 16Nov00 				if(ac->fly.fuel_content[0] + ac->fly.fuel_content[1] + ac->fly.fuel_content[2] + ac->fly.fuel_content[3] == 0)
//DeadCode RJS 16Nov00 					Manual_Pilot.DeathSequenceOverrideDiary(ac, AUTO_DEATHGLIDE);
			}
		}
		else
			fxpercent = 100;
	}

//DeadCode RJS 26Nov99						if (dx > 40)
//DeadCode RJS 26Nov99							WIPtr = &ac->weap.right;
//DeadCode RJS 26Nov99						else
//DeadCode RJS 26Nov99						{
//DeadCode RJS 26Nov99							if (dx < -40)
//DeadCode RJS 26Nov99								WIPtr = &ac->weap.left;
//DeadCode RJS 26Nov99							else
//DeadCode RJS 26Nov99								WIPtr = &ac->weap.centre;
//DeadCode RJS 26Nov99						}
//DeadCode RJS 26Nov99
//DeadCode RJS 26Nov99						if (ac->weap.FuelDumped || ac->weap.UseIntFuel)
//DeadCode RJS 26Nov99						{
//DeadCode RJS 26Nov99							// Can't be external leak...
//DeadCode RJS 26Nov99							if (!weapptr->stationshape)
//DeadCode RJS 26Nov99								WIPtr->int_fuel_leakage = leakval;
//DeadCode RJS 26Nov99						}
//DeadCode RJS 26Nov99						else
//DeadCode RJS 26Nov99						{
//DeadCode RJS 26Nov99							if (!weapptr->stationshape)
//DeadCode RJS 26Nov99			WIPtr->int_fuel_leakage = leakval;
//DeadCode RJS 26Nov99							else
//DeadCode RJS 26Nov99								WIPtr->ext_fuel_leakage = leakval;
//DeadCode RJS 26Nov99						}

	return fxpercent;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProbeStaticTrail
//Author		Robert Slater
//Date			Thu 21 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ProbeStaticTrail(UByteP	rsdptr, itemptr	itm,animptr&	aptr)
{
//DeadCode RJS 20Oct00 	ShapeDescPtr		sdptr = (ShapeDescPtr) rsdptr;
	int					wpnum, index, oldindex;
	WeapAnimData*		weapon;
	SmokeTrailAnimData*	adptr = (SmokeTrailAnimData*) aptr;
	SmokeTypeP			smkptr = NULL;
	UWord				lifetime=0;
	SByte				TType;
//DeadCode RJS 20Oct00 	Bool				validpoint = TRUE;
//DeadCode RJS 20Oct00 	UByte				istransient = 0;

	smokeFirstIsSpecial = false;

	pTrailItm = itm;
//DeadCode RJS 17Feb99 	if (pTrailItm->Status.size == TRANSIENTSIZE)			//RJS 15Feb99
//DeadCode RJS 17Feb99 		istransient = 1;									//RJS 15Feb99

	weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];
	if (adptr->nopoints == 0)
	{
		smkptr = NULL;

		DrawSmokeTrail((SWord)weapon->hdg,(UByteP)smkptr,lifetime,TRUE);	//RJS 24Oct00
	}
	else
	{
		TrailRecordPtr	TrailPtr = &traillist[MAX_VAPOURS];
		SWord			index;

		// if the list is empty, draw nothing...
		if (adptr->thelist)
		{
			TrailPtr->thelist = (Coords3DList*) adptr->thelist;
			TrailPtr->nopoints = adptr->nopoints;
			TrailPtr->lifetime = adptr->lifetime;
			TrailPtr->SmkDescPtr = (UByteP) &SmokeTrlList[adptr->SmkDescIndex];
 			TrailPtr->transient = 1;							//RJS 17Feb99
			TrailPtr->beendrawn = 1;			//RJS 15Feb99
			TrailPtr->currTime = adptr->currTime;				//RJS 16Jun99

			index = MAX_VAPOURS;

			DrawSmokeTrail(index,NULL,TrailPtr->lifetime,TRUE);			//RJS 24Oct00

			adptr->thelist = (ULong)TrailPtr->thelist;
			adptr->currTime = TrailPtr->currTime;				//RJS 17Jun99
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReloadMassAndDrag
//Author		Robert Slater
//Date			Mon 25 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ReloadMassAndDrag(AirStrucPtr	ac)
{
	if (ac->Status.size == AirStrucSize)
	{
		weap_info		*WIPtrL = &ac->weap.left;
		weap_info		*WIPtrR = &ac->weap.right;
		weap_info		*WIPtrC = &ac->weap.centre;

		WIPtrL->mass = WIPtrL->reloadmass;						//RJS 18Jun99
		WIPtrL->drag = WIPtrL->reloaddrag;						//RJS 18Jun99

		WIPtrR->mass = WIPtrR->reloadmass;						//RJS 18Jun99
		WIPtrR->drag = WIPtrR->reloaddrag;						//RJS 18Jun99

		WIPtrC->mass = WIPtrC->reloadmass;						//RJS 18Jun99
		WIPtrC->drag = WIPtrC->reloaddrag;						//RJS 18Jun99

		//At the mo', tip tanks are special cases...
		if (!ac->weap.FuelDumped)								//RJS 18Jun99
		{
			WIPtrL->mass += 4535970;	//100lbs				//RJS 18Jun99
			WIPtrL->drag += 1250;								//RJS 18Jun99

			WIPtrR->mass += 4535970;	//100lbs				//RJS 18Jun99
			WIPtrR->drag += 1250;								//RJS 18Jun99
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGrpTokenVisibility
//Author		Robert Slater
//Date			Fri 12 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SetGrpTokenVisibility(UByteP	instr_ptr, animptr& astart, animptr& adptr)
{
	MinAnimData*	mad = (MinAnimData*) adptr;
	DOGROUP_PTR		ptr = (DOGROUP_PTR) instr_ptr;

	if (ptr->tokenflag)
	{
		if (ptr->tokenflag < GRP_TKN_VIS)
			mad->IsInvisible = 1;
		else
		{
			if ((ptr->tokenflag == GRP_TKN_VIS_DEP) && ptr->tokendepanim)
			{
				MinAnimData*	mad2 = (MinAnimData*) &astart[ptr->tokendepanim-1];
				if (mad->itemstate > BS_DAMLV2)
					mad2->IsInvisible = 0;
				else
					mad2->IsInvisible = 1;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroupElementToken
//Author		Robert Slater
//Date			Fri 12 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong shape::GetGroupElementToken(	UByte *&instr_ptr,
									ShapeNum& shape,
									SLong& x, SLong& y, SLong& z,
									SLong range,
									UByteP	*PrevIptr,
									SWordP	heading,
									ULong&	animdepoff,
									UByteP&	nextgrpptr
									)
{
	SWord	inst;
	SLong	priority;											//RJS 14Nov96

	inst = (SWord )*instr_ptr;
	instr_ptr ++;

	nextgrpptr = NULL;
	if(inst!=dogroupno)
		return(0);

	DOGROUP_PTR temp = (DOGROUP_PTR)instr_ptr;

	shape = (ShapeNum )temp->shapenum;

	x = temp->xoffset;
	y = temp->yoffset;
	z = temp->zoffset;
	priority = temp->element_number;							//RJS 27Feb98
	if (PrevIptr)
		*PrevIptr = (UByteP)temp;
	if (heading)
		*heading = temp->angle;

	animdepoff = temp->tokendepanim;

	temp++;

	instr_ptr = (UByte *)temp;
	if (*instr_ptr == dogroupno)								//RJS 30Jun99
		nextgrpptr = instr_ptr+1;								//RJS 30Jun99

	return(priority);
}

void	shape::InitGlobalItem()
{
	globinitairitem = NULL;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NavigationLightsActive
//Author		Dave Whiteside
//Date			Wed 17 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::NavigationLightsActive(ItemPtr itm,Bool haveon)
{
//DeadCode RJS 02Feb00 	if (itm->Status.size == AIRSTRUCSIZE)
//DeadCode RJS 02Feb00 	{
//DeadCode RJS 02Feb00 		if (itm==Persons2::PlayerGhostAC)
//DeadCode RJS 02Feb00 			itm=Persons2::PlayerSeenAC;
//DeadCode RJS 02Feb00 
//DeadCode RJS 02Feb00 		AircraftAnimData*	adptr = (AircraftAnimData*) itm->Anim;
//DeadCode RJS 02Feb00 		if (adptr->lighttoggle)
//DeadCode RJS 02Feb00 		{
//DeadCode RJS 02Feb00 			//Switch off...
//DeadCode RJS 02Feb00 			if (!haveon)
//DeadCode RJS 02Feb00 			{
//DeadCode RJS 02Feb00 				adptr->lighttoggle = 0;
//DeadCode RJS 02Feb00 				adptr->aclightclock1 = 0;
//DeadCode RJS 02Feb00 				adptr->aclightclock2 = 0;
//DeadCode RJS 02Feb00 			}
//DeadCode RJS 02Feb00 		}
//DeadCode RJS 02Feb00 		else
//DeadCode RJS 02Feb00 		{
//DeadCode RJS 02Feb00 			//Switch on...
//DeadCode RJS 02Feb00 			if (haveon)
//DeadCode RJS 02Feb00 			{
//DeadCode RJS 02Feb00 				adptr->lighttoggle = 1;
//DeadCode RJS 02Feb00 				adptr->aclightclock1 = Timer_Code.FRAMETIME;
//DeadCode RJS 02Feb00 				adptr->aclightclock2 = Timer_Code.FRAMETIME;
//DeadCode RJS 02Feb00 			}
//DeadCode RJS 02Feb00 		}
//DeadCode RJS 02Feb00 	}

	if (itm->Status.size == AIRSTRUCSIZE)
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);		//RJS 7Jun00
		if (SHAPESTUFF.GetShapeScale(sdptr)!=SHP_GRP)					//RJS 7Jun00
		{
			if (sdptr->AnimDataSize == AIRCRAFTANIM)					//RJS 7Jun00
			{
				if (itm==Persons2::PlayerGhostAC)
					itm=Persons2::PlayerSeenAC;

				AircraftAnimData*	adptr = (AircraftAnimData*) itm->Anim;
				if (adptr->lighttoggle)
				{
					//Switch off...
					if (!haveon)
					{
						adptr->lighttoggle = 0;
						adptr->aclightclock1 = 0;
						adptr->aclightclock2 = 0;
					}
				}
				else
				{
					//Switch on...
					if (haveon)
					{
						adptr->lighttoggle = 1;
						adptr->aclightclock1 = Timer_Code.FRAMETIME;
						adptr->aclightclock2 = Timer_Code.FRAMETIME;
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BombBaysActive
//Author		Dave Whiteside
//Date			Wed 17 Feb 1999
//
//Description	Works on similar principle as undercarriage anim.
//
//				... this means it hogs 'animtoggle',
//				which means an ac with bombbays cannot have an
//				undercarriage lowering/raising anim!
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ActivateBombBays(ItemPtr itm)
{
	if (itm->Status.size == AIRSTRUCSIZE)
	{
		ShapeDescPtr sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
		if (sdptr->AnimDataSize == AIRCRAFTANIM)
		{
			AircraftAnimData*	adptr = (AircraftAnimData*) itm->Anim;
			if (adptr->animtoggle)									
				adptr->animtoggle = -adptr->animtoggle;				
			else													
				adptr->animtoggle = 1;	
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AmISmoking
//Author		Robert Slater
//Date			Thu 18 Feb 1999
//
//Description	Checks to see if ac has contrail...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	AirStruc::AmISmoking()
{
	MoveGunAnimData*	adptr = (MoveGunAnimData*) Anim;
	SLong				weapcnt = adptr->nolaunchers;
	SLong				index;
	WeapAnimData*		weapon;
	Bool				retval = FALSE;

	for (index=0; index < weapcnt; index++)
	{
		weapon = (WeapAnimData*) &adptr->weaponlaunchers[index];
		if (weapon)
		{
			if (weapon->LauncherType == LT_ENGINE)	//nowt wrong, exit
				break;
			else
			{
				if (weapon->LauncherType==LT_CONTRAIL)
				{
					retval = TRUE;
					break;
				}
			}
		}
	}

	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateReplayVapourCoords
//Author		Robert Slater
//Date			Wed 21 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::UpdateReplayVapourCoords(UByteP	rsdptr, itemptr	itm,animptr&	aptr)
{
	ShapeDescPtr		sdptr = (ShapeDescPtr) rsdptr;			//RJS 02Dec97
	int					wpnum, index, oldindex;
	WeapAnimData*		weapon;
	MoveGunAnimData*	adptr = (MoveGunAnimData*) aptr;		//RJS 21Apr99
	SLong				wx = itm->World.X;
	SLong				wy = itm->World.Y;
	SLong				wz = itm->World.Z;
	int					weapcnt = 1;
//DeadCode RJS 20Oct00 	SWord				animsize = sdptr->AnimDataSize;
	UByte				instsize = sizeof(DOLAUNCHER) + 1;
	DOLAUNCHER_PTR		lptr;
	UByteP				instr_ptr;
	UByteP				base_ptr;
	UWord				instruction;
	SmokeTypeP			smkptr = NULL;
	UWord				lifetime=0;										//RJS 20Oct00
	ULong				reallifetime;
	SByte				TType;
	Bool				validpoint = TRUE;						//RJS 30Nov98
	SLong				driftx,drifty,driftz;					//RJS 10Mar98
//DeadCode RJS 20Oct00 	Bool				justlanded=FALSE;								//RJS 11Mar98
	UByte				weaplaunchertype=0;
	SWord				theHdg,thePitch,theRoll;

	switch (SHAPESTUFF.GetShapeScale(sdptr))				
 	{														
 		case SHP_1CM:										
 			shapescale = 0;									
 			break;											
 		case SHP_4CM:										
 			shapescale = 2;									
 			break;											
 		case SHP_16CM:										
 			shapescale = 4;									
 			break;											
 	}

	if (itm->Status.size >= ROTATEDSIZE)
	{
		theHdg = ((RotItemPtr)itm)->hdg;
		thePitch = ((RotItemPtr)itm)->pitch;
		theRoll = ((RotItemPtr)itm)->roll;
	}
	else
	{
		theHdg = thePitch = theRoll = 0;
	}

	pTrailItm = itm;//RJS 02Sep98
	weapcnt = adptr->nolaunchers;								//RJS 09Apr98

	Math_Lib.high_sin_cos((ANGLES )((mobileitem*)itm)->hdg,v_sin_ang,v_cos_ang);

	base_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

	for (wpnum = 0; wpnum < weapcnt; wpnum++)
	{
		oldindex = 0;
		weapon = (WeapAnimData*) &adptr->weaponlaunchers[wpnum];
		if (weapon)
		{
			instr_ptr = base_ptr + (instsize * wpnum);
			instr_ptr++;

			lptr = (DOLAUNCHER_PTR) instr_ptr;
			if (	!lptr->damageflag
				|| (aptr[lptr->damageflag] < lptr->damthresh)	)
			{
				TType = lptr->trailtype;
				if (TType < 0)
				{
					if (TType == -1)
					{
						if (weapon->LauncherType == LT_FUEL)
						{
							TType = TRAIL_VAPOUR;
							smkptr = (SmokeTypeP) &SmokeTrlList[TRAIL_VAPOUR];
							lifetime = smkptr->LifeTime;

							weaplaunchertype = weapon->LauncherType;//MS 30Nov98
						}
					}
					else
					{
						// Generic one for engines...
						if (lptr->lnchrtype == LT_ENGINE)		//MS 30Nov98
						{
							UByte	dolaunch = LT_ENGINE;

							if (itm->Status.size == AirStrucSize)				//RJS 20Jan99
							{
//DeadCode RJS 20Oct00 								AirStrucPtr	acptr = (AirStrucPtr) itm;
//DeadCode RJS 20Oct00 								SLong	rpm = acptr->fly.pModel->Inst.I_EngineRpm0;//Rpm1;
//DeadCode RJS 20Oct00 								SLong	mph = acptr->fly.pModel->Inst.I_TrueGroundSpeed;//ActualSpeed;

								if (aptr[lptr->damageflag] < BS_DAMLV2)
								{
									dolaunch = LT_CONTRAIL;
									TType = TRAIL_CONTRAIL;
									smkptr = (SmokeTypeP) &SmokeTrlList[TType];
									lifetime = smkptr->LifeTime;

//DeadCode RJS 28Jan00									if (weapon->LauncherType != LT_CONTRAIL)
//DeadCode RJS 28Jan00									{
//DeadCode RJS 28Jan00										if (	(object_obj3d->Shape == F86)
//DeadCode RJS 28Jan00											&&	(acptr->fly.thrustpercent > 33))
//DeadCode RJS 28Jan00										{
//DeadCode RJS 28Jan00											if (!MMC.Sky.Contrails((AirStrucPtr)itm, reallifetime))
//DeadCode RJS 28Jan00											{
//DeadCode RJS 28Jan00								 				dolaunch = LT_FUEL;
//DeadCode RJS 28Jan00												if (rpm > 7000)
//DeadCode RJS 28Jan00												{
//DeadCode RJS 28Jan00													TType = TRAIL_EXHAUSTDIRTY;
//DeadCode RJS 28Jan00													smkptr = (SmokeTypeP) &SmokeTrlList[TType];
//DeadCode RJS 28Jan00													lifetime = smkptr->LifeTime;
//DeadCode RJS 28Jan00												}
//DeadCode RJS 28Jan00												else
//DeadCode RJS 28Jan00												{
//DeadCode RJS 28Jan00													TType = TRAIL_EXHAUST;
//DeadCode RJS 28Jan00													smkptr = (SmokeTypeP) &SmokeTrlList[TType];
//DeadCode RJS 28Jan00													lifetime = smkptr->LifeTime;
//DeadCode RJS 28Jan00												}
//DeadCode RJS 28Jan00											}
//DeadCode RJS 28Jan00										}
//DeadCode RJS 28Jan00									}
								}
								else
								{
									dolaunch = LT_FUEL;
									TType = TRAIL_ENGINEPLUME;
									smkptr = (SmokeTypeP) &SmokeTrlList[TType];
									lifetime = smkptr->LifeTime;
								}
							
								index = weapon->hdg;
								if (index > 0)
								{
									if (traillist[index].SmkDescPtr != (UByteP)smkptr)
									{
										SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
										weapon->hdg = 0;
									}
									weapon->LauncherType = LT_ENGINE;
								}
								else
									weapon->LauncherType = LT_ENGINE;

								if (weapon->LauncherType != dolaunch)
								{
//DeadCode AMM 30Mar99 									weapon->LauncherType = dolaunch;
									if (dolaunch != LT_CONTRAIL)
									{
										weapon->LauncherType = dolaunch;//AMM 30Mar99
										oldindex = Trans_Obj.LaunchVapourStream((UByteP)weapon,itm->shape);//RJS 09Apr98
//DeadCode AMM 30Mar99 										weapon->pitch = -1;
									}
									weapon->pitch = -1;			//AMM 30Mar99
								}
							}

							weaplaunchertype = dolaunch;
						}
						else
						{
							// This is a generic, inherited trail...
							// ... make sure we sample no extra points!

							smkptr = NULL;
							weaplaunchertype = LT_CONTACT;
						}
					}											//MS 30Nov98
				}
				else
				{
					smkptr = (SmokeTypeP) &SmokeTrlList[TType];	//RJS 09Apr98
					lifetime = smkptr->LifeTime;

					weaplaunchertype = weapon->LauncherType;	//MS 30Nov98
				}

				if (TType != -1)
				{
					// min sample distance is 1024 cm per frame, which is 256m/s
//DeadCode RJS 6Nov00 					SLong	mindist = (51200 * Timer_Code.FRAMETIME)/100;
//DeadCode RJS 6Nov00 					SLong	distscale;

					validpoint = TRUE;
					driftx = 0;										//RJS 10Mar98
					drifty = 0;										//RJS 10Mar98
					driftz = 0;										//RJS 10Mar98

					switch (weaplaunchertype)					//RJS 29Nov98
					{
						case LT_CONTRAIL:
						{
							if (MissManCampSky().Contrails((AirStrucPtr) itm, reallifetime))
							{
								//Cannot implement different lifetime until we extend
								//smoke trail coordinate type to include this master lifetime
								lifetime = reallifetime;

								oldindex = Trans_Obj.LaunchVapourStream((UByteP)weapon,itm->shape);//RJS 09Apr98
								index = weapon->hdg;					//RJS 12Jan98
								if (index > 0)
								{
									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);	//RJS 02Feb98
								}
							}
							else
							{
								index = weapon->hdg;				//RJS 12Jan98
								if (index > 0)
								{
									SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);//RJS 09Apr98
									weapon->hdg = 0;				//RJS 12Jan98
								}
							}
							break;
						}
						case LT_FUNNEL:							//RJS 06Jun99
						{
//In real draw, this also removes the point straight away,
//so this bit doesn't actually do anything...
//							index = weapon->hdg;
//							if (index > 0)
//							{
//								traillist[index].lastwx = wx;
//								traillist[index].lastwy = wy;
//								traillist[index].lastwz = wz;
//
//								validpoint = ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);
//							}
							break;
						}
						case LT_INTFUEL:
						case LT_FUEL:
						{
							index = weapon->hdg;					//RJS 12Jan98
							if (index > 0)
							{
								if (traillist[index].thelist)
								{
//DeadCode RJS 6Nov00 									SLong	dist;
									float	dx,dy,dz;					//RJS 6Nov00

									dx = wx - traillist[index].lastwx;
									dy = wy - traillist[index].lastwy;
									dz = wz - traillist[index].lastwz;

//DeadCode RJS 6Nov00 									dist = Math_Lib.distance3d(dx,dy,dz);
									if ((dx*dx+dy*dy+dz*dz) >= MIN_SAMP_DIST_SQUARED)			//RJS 6Nov00
									{
//DeadCode RJS 6Nov00 										distscale = dist / mindist;

										traillist[index].lastwx = wx;
										traillist[index].lastwy = wy;
										traillist[index].lastwz = wz;
										traillist[index].nextlist = oldindex;

										validpoint = ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);	//RJS 02Feb98
									}
									else
									{
										if (SamplePntTime)
										{
											SLong	oldx, oldy, oldz;

											oldx = traillist[index].lastwx;
											oldy = traillist[index].lastwy;
											oldz = traillist[index].lastwz;

											traillist[index].lastwx = wx;
											traillist[index].lastwy = wy;
											traillist[index].lastwz = wz;

											ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);
											validpoint = FALSE;

											traillist[index].lastwx = oldx;
											traillist[index].lastwy = oldy;
											traillist[index].lastwz = oldz;
										}
									}
								}
								else
								{
									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);
								}
							}
							break;
						}
						case LT_DUST:
						{
							index = weapon->hdg;					//RJS 12Jan98
							if (index > 0)
							{
								traillist[index].lastwx = wx;
								traillist[index].lastwy = Land_Scape.GetGroundLevel(itm);
								traillist[index].lastwz = wz;
								traillist[index].nextlist = oldindex;

								validpoint = ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);
							}
							break;
						}
						case LT_MUDDY:
						{
//DeadCode RJS 25Nov98 							if (justlanded)	  //NOT INITIALISED!!
//DeadCode RJS 25Nov98 								oldindex = Trans_Obj.LaunchVapourStream((UByteP)weapon,(ShapeNum)object_obj3d->Shape);//RJS 09Apr98
//DeadCode RJS 25Nov98 							else
//DeadCode RJS 25Nov98 							{
//DeadCode RJS 25Nov98 								if (weapon->hdg > 0)
//DeadCode RJS 25Nov98 								{
//DeadCode RJS 25Nov98 									SHAPE.DetatchVapourStream(weapon->hdg,LIFETIME_VAPOUR);//RJS 09Apr98
//DeadCode RJS 25Nov98 									weapon->hdg = 0;			
//DeadCode RJS 25Nov98 								}
//DeadCode RJS 25Nov98 							}
//DeadCode RJS 25Nov98 
//DeadCode RJS 25Nov98 							index = weapon->hdg;
//DeadCode RJS 25Nov98 							if (index > 0)
//DeadCode RJS 25Nov98 							{
//DeadCode RJS 25Nov98 								traillist[index].lastwx = wx;
//DeadCode RJS 25Nov98 								traillist[index].lastwy = wy;
//DeadCode RJS 25Nov98 								traillist[index].lastwz = wz;
//DeadCode RJS 25Nov98 								traillist[index].nextlist = 0;
//DeadCode RJS 25Nov98 
//DeadCode RJS 25Nov98 								validpoint = SampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime);
//DeadCode RJS 25Nov98 								drifty = (((mobileitem*)itm)->velhori << 7)>>10;
//DeadCode RJS 25Nov98 							}
//DeadCode RJS 25Nov98 							break;
							index = weapon->hdg;					//RJS 12Jan98
							if (index > 0)
							{
								if (traillist[index].thelist)
								{
									SLong	dist;
									SLong	dx,dy,dz;
									SLong	ox,oy,oz;

									ox = traillist[index].lastwx;
									oy = traillist[index].lastwy;
									oz = traillist[index].lastwz;

									dx = wx - ox;
									dy = wy - oy;
									dz = wz - oz;

									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);

									dist = Math_Lib.distance3d(dx,dy,dz);
									if (dist < 100)
									{
										if (SamplePntTime)
										{
											validpoint = FALSE;
											if (dist == 0)
												drifty = -View_Point->DrawFrameTime();
										}

										traillist[index].lastwx = ox;
										traillist[index].lastwy = oy;
										traillist[index].lastwz = oz;
									}
								}
								else
								{
									traillist[index].lastwx = wx;
									traillist[index].lastwy = wy;
									traillist[index].lastwz = wz;
									traillist[index].nextlist = oldindex;

									validpoint = ReplaySampleSmokePnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,weapon->pitch,lifetime,theHdg,thePitch,theRoll);//RJS 25Nov98
								}
							}
							break;
						}
//DeadCode RJS 6Nov00 						case LT_JETDUST:
//DeadCode RJS 6Nov00 						{
//DeadCode RJS 6Nov00 							if (itm->Status.size == AirStrucSize)
//DeadCode RJS 6Nov00 							{
//DeadCode RJS 6Nov00 								AirStrucPtr	acptr = (AirStrucPtr) itm;
//DeadCode RJS 6Nov00 								SLong		gheight = acptr->fly.pModel->GroundHeight;
//DeadCode RJS 6Nov00 								SLong		height = wy - gheight;
//DeadCode RJS 6Nov00 								SWord		realpitch = acptr->pitch;
//DeadCode RJS 6Nov00 
//DeadCode RJS 6Nov00 								if ((height < 4000) && (realpitch > ANGLES_0Deg))
//DeadCode RJS 6Nov00 								{
//DeadCode RJS 6Nov00 									oldindex = Trans_Obj.LaunchVapourStream((UByteP)weapon,itm->shape);
//DeadCode RJS 6Nov00 									index = weapon->hdg;
//DeadCode RJS 6Nov00 									if (index > 0)
//DeadCode RJS 6Nov00 									{
//DeadCode RJS 6Nov00 										weapon->pitch = -1;
//DeadCode RJS 6Nov00 
//DeadCode RJS 6Nov00 										traillist[index].lastwx = wx;
//DeadCode RJS 6Nov00 										traillist[index].lastwy = wy;
//DeadCode RJS 6Nov00 										traillist[index].lastwz = wz;
//DeadCode RJS 6Nov00 										traillist[index].nextlist = 0;
//DeadCode RJS 6Nov00 
//DeadCode RJS 6Nov00 										if (traillist[index].LaunchCountdown < 0)
//DeadCode RJS 6Nov00 										{
//DeadCode RJS 6Nov00 //DEADCODE CSB 08/11/99 											SLong	veltime = 300 - acptr->velhori;
//DeadCode RJS 6Nov00 											SLong	veltime = 300000 - acptr->vel_; //CSB 08/11/99
//DeadCode RJS 6Nov00 											veltime /= 10000;						//CSB 08/11/99
//DeadCode RJS 6Nov00 											traillist[index].LaunchCountdown = veltime;
//DeadCode RJS 6Nov00 
//DeadCode RJS 6Nov00 											validpoint = SampleDustPnt((UByteP)smkptr,(SWord&)weapon->hdg,instr_ptr,lifetime,height,realpitch);
//DeadCode RJS 6Nov00 										}
//DeadCode RJS 6Nov00 										else
//DeadCode RJS 6Nov00 											traillist[index].LaunchCountdown -= View_Point->DrawFrameTime();
//DeadCode RJS 6Nov00 									}
//DeadCode RJS 6Nov00 								}
//DeadCode RJS 6Nov00 								else
//DeadCode RJS 6Nov00 								{
//DeadCode RJS 6Nov00 									if (weapon->hdg > 0)
//DeadCode RJS 6Nov00 									{
//DeadCode RJS 6Nov00 										SHAPE.DetatchVapourStream(weapon->hdg,LIFETIME_VAPOUR);//RJS 09Apr98
//DeadCode RJS 6Nov00 										weapon->hdg = 0;			
//DeadCode RJS 6Nov00 									}	
//DeadCode RJS 6Nov00 								}
//DeadCode RJS 6Nov00 							}
//DeadCode RJS 6Nov00 							break;
//DeadCode RJS 6Nov00 						}
					}
				}
			}
		}
	}
}

void shape::replay_animate_shape(ItemPtr	itm)
{
	if (itm !=Persons2::PlayerGhostAC)						
	{
		ShapeDescPtr	sdptr;

		animptr	adptr;

		// could cack if something is being drawn...
//DeadCode JIM 26Mar99  		object_obj3d  = NULL;									//RJS 19Jun97

		adptr = itm->Anim;

		sdptr = SHAPESTUFF.GetShapePtr((ShapeNum)itm->shape);

		// We need this for smoke launchers......				//MS 30Nov98
 		switch (SHAPESTUFF.GetShapeScale(sdptr))				//MS 30Nov98
 		{														//MS 30Nov98
 			case SHP_GRP:										//MS 30Nov98
				return;
 				break;											//MS 30Nov98
 			case SHP_1CM:										//MS 30Nov98
 				shapescale = 0;									//MS 30Nov98
 				break;											//MS 30Nov98
 			case SHP_4CM:										//MS 30Nov98
 				shapescale = 2;									//MS 30Nov98
 				break;											//MS 30Nov98
 			case SHP_16CM:										//MS 30Nov98
 				shapescale = 4;									//MS 30Nov98
 				break;											//MS 30Nov98
 		}														//MS 30Nov98
		// ....We need this for smoke launchers					//MS 30Nov98

		UByte	vaptype = sdptr->Type.VapourType;				//RJS 21Jan99

		//Call the correct anim routine in this case statement
		if (sdptr->AnimDataSize > -1)
		{
			switch (sdptr->AnimDataSize)
			{
				case SMOKETRAILANIM:
					vaptype = TRAIL_OFF;
//					ProbeReplayStaticTrail((UByteP)sdptr,itm,adptr);
					break;
			}
		}

		switch (vaptype)							//RJS 10Mar98
		{
			case TRAIL_NORMAL:
			case TRAIL_STATIC:
				UpdateReplayVapourCoords((UByteP)sdptr,itm,adptr);
				break;
			case TRAIL_GROUND:
//				UpdateReplaySmokeDriftCoords((UByteP)sdptr,itm,adptr);
				break;
		}
	}
}

Bool	shape::ReplaySampleSmokePnt(	UByteP		smkinfo,
										SWord		&listindex,
										UByteP		instr_ptr,
										SWord		&Stores,
										UWord		LifeTime,
										SWord		&hdg,
										SWord		&pitch,
										SWord		&roll
										)
{
	Bool	validpoint = TRUE;

	if (SamplePntTime)
	{
		DOLAUNCHER_PTR	ptr = (DOLAUNCHER_PTR) instr_ptr;
		TrailRecord*	trailptr = &traillist[listindex];
		SmokeTypeP		smkptr = (SmokeTypeP) smkinfo;
		SLong			xcoord = ptr->posx;
		SLong			ycoord = ptr->posy;
		SLong			zcoord = ptr->posz;
		SLong			lifetime;
		SLong			wx, wy, wz;
		SWord			index = listindex;
		MATRIX  		omat;										
		MATRIX_PTR		obj_matrix = &omat;							
		UWord			scaleback;

		if (!LifeTime)											//RJS 09Apr98
			LifeTime = smkptr->LifeTime;						//RJS 09Apr98

//		if (Three_Dee.IsPaused())								//RJS 27Feb98
//			SamplePntTime = FALSE;

		trailptr->SampleTime -= View_Point->DrawFrameTime();
		if (trailptr->SampleTime < 0)							//RJS 08Jan98
			trailptr->SampleTime = smkptr->SampleTime;			//RJS 02Feb98
		else													//RJS 02Feb98
			validpoint = FALSE;									//RJS 02Feb98

		// -1 is infinite....
		if (Stores != -1)
		{
			Stores-=1;											

			if (Stores < 0)
				Stores = 0;
		}

		if (Stores)
		{
			lifetime = LifeTime;								//RJS 08Dec97

//			if (trailptr->lifetime && (lifetime > 500))
//				lifetime = trailptr->lifetime;

 			if (trailptr->nextlist)
 			{
 				Coords3DList*	nextptr = traillist[trailptr->nextlist].thelist;
 				if (nextptr)
 				{
 					wx = nextptr->trailpoint.gx;
 					wy = nextptr->trailpoint.gy;
 					wz = nextptr->trailpoint.gz;

 					SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,lifetime,smkptr->FadeTime);
 					lifetime = trailptr->lifetime;
 				}

 				trailptr->nextlist = 0;
 			}

			// Every frame....

 			wx = xcoord << shapescale;
 			wy = ycoord << shapescale;
 			wz = zcoord << shapescale;

			_matrix.generate2(	(Angles)hdg,
								(Angles)pitch,
								(Angles)roll,
								obj_matrix);

			scaleback = _matrix.transform(obj_matrix,wx,wy,wz);
			wx >>= (16-scaleback);
			wy >>= (16-scaleback);
			wz >>= (16-scaleback);

			wx += trailptr->lastwx;
			wy += trailptr->lastwy;
			wz += trailptr->lastwz;

			SHAPE.AddNewVapourPoint(trailptr,wx,wy,wz,lifetime,smkptr->FadeTime);

			if (trailptr->nopoints > smkptr->MaxPoints)
			{
				switch (smkptr->DeadAction)
				{
				case DEADSMK_DEFAULT:
	 				trailptr->bitshift = 0;
//DEADCODE DAW 23/04/99 					listindex = 0;					//RJS 12Apr99
//DEADCODE DAW 12/04/99 					listindex = -index;
					SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);
					listindex = NextFreeVapour(0,0,0,smkinfo);										//RJS 23Apr99
					if (listindex)																	//RJS 23Apr99
						AddNewVapourPoint(&traillist[listindex],wx,wy,wz,lifetime,smkptr->FadeTime);//RJS 23Apr99
					break;
				case DEADSMK_SMOKECLOUD:
					SHAPE.AddSmokeCloud(trailptr,smkptr->CloudShape,index);
					break;
				}
			}
		}
		else
		{
			listindex = 0;
			SHAPE.DetatchVapourStream(index,LIFETIME_VAPOUR);	//RJS 09Apr98
		}
	}

	return(validpoint);
}

Bool	AirStruc::HasSmoked()
{
	Bool	retval = FALSE;
	if (this)
	{
		ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(shape);

		if (sdptr->AnimDataSize == AIRCRAFTANIM)
		{
			AircraftAnimData*	adptr = (AircraftAnimData*) Anim;
			if (adptr->hassmoked)
				retval = TRUE;
		}
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenerateProbeTrails
//Author		Andy McMaster
//Date			Fri 26 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GenerateProbeTrails()
{
	if (newprobecnt)
	{
		TrailRecordPtr		TrailPtr;
	 	SmokeTrailAnimData*	adptr;
		Coords3DList*		apoint;
		Coords3DList*		dpoint;
		Coords3DList*		npoint;
		Coords3DList*		*lpointptr;
		SLong				counter;
		SLong				howmany;
		SLong				divvy;
		SLong				staticlifeleft;
		SLong				realnopoints;

		int	index;
		for (index=0; index < newprobecnt; index++)
		{
			adptr = (SmokeTrailAnimData*) MakeProbes[index].itm->Anim;

			switch (MakeProbes[index].action)
			{
			case PROBER_KILL:
			{
				TrailPtr = &traillist[MAX_VAPOURS];
				apoint = (Coords3DList*) adptr->thelist;
				while (apoint)
				{
					dpoint = apoint;
					apoint = apoint->next;

#ifdef	TRAILREPORT
	::AfxTrace("GPT: %x %x (%d)\n",int(dpoint),int(&dpoint->next),int(dpoint->KillMe));
#endif
					dpoint->next = TrailPtr->FakePointPtr;
					TrailPtr->FakePointPtr = dpoint;

#ifdef	_SMOKETRAILDEBUG_
					if (apoint)	apoint->prevkilled = true;
					dpoint->nextkilled = true;
					dpoint->probed = true;
#endif

				}

				adptr->thelist = NULL;

				Trans_Obj.RemoveTransientItemFromTrailList(MakeProbes[index].itm);//AMM 26Mar99
			}
			break;
			case PROBER_DEGRADE:
			{
				TrailPtr = &traillist[MakeProbes[index].index];
				apoint = TrailPtr->thelist;
				counter = 0;
				howmany = TrailPtr->nopoints;
				divvy = howmany / 6;
				staticlifeleft = 0;
				realnopoints = 0;

				// Down-grade first to max 6 points...
				if (divvy)
				{
					realnopoints++;

					howmany /= divvy;

#ifdef	_SMOKETRAILDEBUG_
					Coords3DList*	lastPoint = NULL;
#endif

					lpointptr = &apoint->next;
					apoint = apoint->next;
					while (apoint)
					{
						npoint = apoint;
						apoint = apoint->next;

						if (apoint && (counter != howmany))
						{
#ifdef	TRAILREPORT
	::AfxTrace("GPT2: %x %x %x (%d)\n",int(npoint),int(&npoint->next),int(lpointptr),int(npoint->KillMe));
#endif
							//After draw, so any KillMe points are new and have not
							//already been added to fakepoint list...
//Dead							if (!npoint->KillMe)
//Dead							{
								npoint->next = TrailPtr->FakePointPtr;
								TrailPtr->FakePointPtr = npoint;
								TrailPtr->nopoints--;

#ifdef	_SMOKETRAILDEBUG_
								if (apoint)	apoint->prevkilled = true;
								if (lastPoint)	lastPoint->nextkilled = true;
								npoint->probed = true;
#endif

//Dead							}
							counter++;
						}
					  	else
					  	{
					  		*lpointptr = npoint;

					  		lpointptr = &npoint->next;
					  		counter = 0;
					  		realnopoints++;
					  	}

#ifdef	_SMOKETRAILDEBUG_
						lastPoint = npoint;
#endif

					}
				}
				else
					realnopoints = howmany;

				adptr->nopoints = realnopoints;
				adptr->thelist = (ULong) TrailPtr->thelist;
				adptr->lifetime = TrailPtr->lifetime;
				adptr->SmkDescIndex = ((UByteP)TrailPtr->SmkDescPtr - (UByteP) &SmokeTrlList[0])/sizeof(SmokeType);
				adptr->currTime = TrailPtr->currTime;						//RJS 16Jun99

	
				TrailPtr->thelist = NULL;							
				TrailPtr->lifetime = 0;
				TrailPtr->nopoints = 0;								
				TrailPtr->bitshift = 0;								
				TrailPtr->nextlist = 0;								
				TrailPtr->beendrawn = 0;								
				TrailPtr->SampleTime = 0;							
//DeadCode RJS 06May99 				TrailPtr->InitVelH = 0;								
//DeadCode RJS 06May99 				TrailPtr->InitVelY = 0;								
//DeadCode RJS 06May99 				TrailPtr->Acceleration = 0;						
				TrailPtr->SmkDescPtr = NULL;						
				TrailPtr->cloudlaunched = FALSE;
				TrailPtr->transient = 0;
				TrailPtr->currTime = 0;							//RJS 16Jun99

				//Log this item as transient fiddle...
				Trans_Obj.AddTransientItemToTrailList(MakeProbes[index].itm);//AMM 26Mar99
			}
			break;
			}
		}

		newprobecnt = 0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		dummy_animate_shape
//Author		Robert Slater
//Date			Tue 6 Apr 1999
//
//Description	Routine to handle vapour trails that are off screen.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::dummy_animate_shape(ItemPtr	itm, UByteP	sptr,bool& trailvisible)
{
	if (itm && (itm->Status.size == AIRSTRUCSIZE))
	{
		ShapeDescPtr	sdptr = (ShapeDescPtr) sptr;
		switch (sdptr->Type.VapourType)
		{
			case TRAIL_NORMAL:
			case TRAIL_STATIC:
				HandleVapourCoords(sptr,itm,trailvisible);		//RJS 04Feb00
				break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HandleVapourCoords
//Author		Robert Slater
//Date			Tue 6 Apr 1999
//
//Description	Kills vapour streams that aren't important...
//				... such as the F86 exhaust
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::HandleVapourCoords(UByteP	rsdptr, itemptr	itm,bool& trailvisible)
{
	bool			hasSmoked;
	ShapeDescPtr	sdptr = (ShapeDescPtr) rsdptr;
	UWord			timeNotVisible = MAX_TIME_OFF_SCREEN_SMOKE;			//RJS 6Sep00

	if (sdptr->AnimDataSize == AIRCRAFTANIM)							//RJS 7Jun00
	{
		AircraftAnimData*	adptr = (AircraftAnimData*) itm->Anim;
		hasSmoked = adptr->hassmoked;

		adptr->timenotvis += View_Point->DrawFrameTime();

		timeNotVisible = adptr->timenotvis;								//RJS 6Sep00
	}
	else
	{
		SimpleAircraftAnimData*	adptr = (SimpleAircraftAnimData*) itm->Anim;
		hasSmoked = adptr->hassmoked;
	}

	if (hasSmoked)														//RJS 7Jun00
	{
		ShapeDescPtr		sdptr = (ShapeDescPtr) rsdptr;
		int					wpnum;
		WeapAnimData*		weapon;
		UByte				instsize = sizeof(DOLAUNCHER) + 1;
		DOLAUNCHER_PTR		lptr;
		UByteP				instr_ptr;
		UByteP				base_ptr;
		UWord				instruction;
		MoveGunAnimData*	adptr = (MoveGunAnimData*)itm->Anim;
//DeadCode RJS 20Oct00 		UByteP				aptr = (UByteP)adptr;

		base_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

		for (wpnum = 0; wpnum < adptr->nolaunchers; wpnum++)
		{
			weapon = (WeapAnimData*) &adptr->weaponlaunchers[wpnum];
			if (	weapon
				&& ((weapon->LauncherType & LT_MASK)==LT_SMKTRAILS)
				&&	(weapon->hdg > 0)	)	
			{
				instr_ptr = base_ptr + (instsize * weapon->launcherIndex);	//RJS 29Aug00
				instr_ptr++;

				lptr = (DOLAUNCHER_PTR) instr_ptr;
				switch (lptr->lnchrtype)
				{
				case LT_FUNNEL:
				{
					SHAPE.DetatchVapourStream(weapon->hdg,200);
					weapon->hdg = 0;
					weapon->LauncherType = lptr->lnchrtype;

					trailvisible = true;
				}
				break;
				case LT_FUEL:
				case LT_INTFUEL:										//RJS 6Sep00
				case LT_VAPOUR:
				{
					DrawNonVisibleTrail(itm,weapon,TRAIL_VAPOUR,timeNotVisible,lptr->lnchrtype,MAX_TIME_OFF_SCREEN_VAPOUR);	//RJS 6Sep00

					trailvisible = true;
				}
				break;
				case LT_ENGINE:
				{
					if (weapon->LauncherType != LT_ENGINE)
						DrawNonVisibleTrail(itm,weapon,TRAIL_ENGINEPLUME,timeNotVisible,lptr->lnchrtype,MAX_TIME_OFF_SCREEN_SMOKE);	//RJS 6Sep00
					
					trailvisible = true;
				}
				break;
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReplayAnimData_NewShape
//Author		Robert Slater
//Date			Wed 21 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ReplayAnimData_NewShape(UWord	uniqueid, UWord	theShape)
{
	ItemPtr		itm = (ItemPtr)Persons2::ConvertPtrUID((UniqueID)uniqueid);
	SLong		animdatasize = GetAnimDataSize((ShapeNum)theShape);

	memset(&itm->Anim[0],0,animdatasize);

	itm->shape = (ShapeNum)theShape;

	AnimWeaponPack = 0;

	DefaultAnimData(itm,itm->Anim,TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FakeDustTrail
//Author		Robert Slater
//Date			Tue 18 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::FakeDustTrail(Coords3D& pos, SLong	vel, SWord	hdg, UByteP	descptr)
{
	if (vel > MPHHALF)
	{
		ShapeDescPtr	sdptr = (ShapeDescPtr)descptr;
		if (sdptr->LauncherDataSize && Trans_Obj.WithinVisibleRange(pos,50000))
		{
			SWord			direction = hdg + ANGLES_180Deg;
			UByteP			instr_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;
			DOLAUNCHER_PTR	lptr;
			SLong			deltax, deltaz;
			SWord			sin_ang, cos_ang;
			SLong			distance = (vel * 800)/MPH30;

			if (distance > 800)	distance = 800;

			instr_ptr++;

			lptr = (DOLAUNCHER_PTR)instr_ptr;

			Math_Lib.high_sin_cos((Angles)direction,sin_ang,cos_ang);
			deltax = (cos_ang * distance) / ANGLES_FRACT;
			deltaz = (sin_ang * distance) / ANGLES_FRACT;

			//Put dust trail object in the binary tree...


		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetACGears
//Author		Robert Slater
//Date			Tue 1 Jun 1999
//
//Description
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	mobileitem::ResetACGears()
{
	AircraftAnimData*	adptr;
	MobileItemPtr		entry = ACList;
	AirStrucPtr			ac;

	while (entry)
	{
		if (	(entry->Status.size == AIRSTRUCSIZE)
			&&	(entry->vel_ >= MPH100)							//RJS 10Jun99
			&&	(entry->movecode != AUTO_TAKEOFF)				//RJS 10Jun99
			&&	(entry->movecode != AUTO_LANDING)	)			//RJS 10Jun99
		{
			ac = (AirStrucPtr) entry;
			if (ac != Persons2::PlayerSeenAC)					//RJS 30Jun99
			{
				SHAPE.NavigationLightsActive(entry,FALSE);

				if (SHAPESTUFF.GetShapePtr(entry->shape)->AnimDataSize == AIRCRAFTANIM)
				{
					adptr = (AircraftAnimData*) entry->Anim;
					adptr->acleglowerl = 255;
					adptr->acleglowerr = 255;
					adptr->acleglowerf = 255;
					adptr->acleglowerb = 255;
					adptr->animtoggle = 1;
				}

				ac->fly.pModel->ResetGearPos(false);			//RJS 30Jun99
			}
			else
				ac->fly.pModel->ResetGearPos(true);				//RJS 30Jun99
		}

		entry = entry->nextmobile;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawTempBlobTrail
//Author		Robert Slater
//Date			Mon 7 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::DrawTempBlobTrail(SLong	index, UByteP smkinfo,SLong lifetime,Bool validpoint)
{
	if (index)
	{
		if (index < 0)											
			index = -index;

		if (index > MAX_VAPOURS)						
			_Error.EmitSysErr(__FILE__":(DOSMKTRAIL)    Shouldn't be this : %d\n",index);

		TrailRecordPtr	TrailPtr = &traillist[index];
													 
		if (smkinfo)								 
			TrailPtr->SmkDescPtr = smkinfo;			 
		else										 
		{
			smkinfo = TrailPtr->SmkDescPtr;			 
			lifetime = TrailPtr->lifetime;			 
		}

		if (smkinfo)
		{
			SmokeTypeP		ptr = (SmokeTypeP) smkinfo;
			Coords3DList*	apoint;

			apoint = TrailPtr->thelist;
			if (apoint)
			{
				Coords3D	pos;
				
				pos.X = apoint->trailpoint.gx;
				pos.Y = apoint->trailpoint.gy;
				pos.Z = apoint->trailpoint.gz;

				apoint->KillMe = 1;

				apoint->next = TrailPtr->FakePointPtr;
				TrailPtr->FakePointPtr = apoint;
				TrailPtr->nopoints--;

				if (validpoint)
				{
					SLong	velhori = ptr->VelHori;
					SLong	vely = ptr->VelY;
					SWord	hdg;

					if (pTrailItm->Status.size >= MOBILESIZE)
					{	
						vely += ((mobileitem*)pTrailItm)->vel_y;
						hdg = ((mobileitem*)pTrailItm)->hdg;
					}
					else
						hdg = Math_Lib.rnd();

					Trans_Obj.LaunchSmokePuff2((mobileitem*)pTrailItm,pos,SMFLSH,NULL,velhori*1000,vely*1000,hdg,lifetime,lifetime,*mobileitem::currworld);//RJS 15Dec99
				}

				TrailPtr->thelist = NULL;
			}
		}
	}
}

void	Coords3DList::Wipe()
{
	Coords3DList*	apoint = this;
	Coords3DList*	tmpptr;
	while (apoint)
	{
		tmpptr = apoint->next;
#ifdef	TRAILREPORT
	::AfxTrace("DEAD: %x\n",int(apoint));
#endif
		delete apoint;
		apoint = tmpptr;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BombBayDoors
//Author		Robert Slater
//Date			Mon 28 Jun 1999
//
//Description	Shares the anim toggle with the gear...
//				...bombers have fake gear anyway, so this doesn't matter
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::BombBayDoors(AirStrucPtr	ac, SLong animval, bool setNow)
{
	if ((ac->shape == HE11) || (ac->shape == DO17))
	{
		if (SHAPESTUFF.GetShapePtr(ac->shape)->AnimDataSize == AIRCRAFTANIM)
		{
			AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;

			if (setNow)													//CSB 31Aug00
			{															//CSB 31Aug00
				if (animval == ANIM_BOMBDOORS_OPEN)						//CSB 31Aug00
					adptr->animtoggle = 1;								//CSB 31Aug00
				else													//CSB 31Aug00
					adptr->animtoggle = -1;								//CSB 31Aug00
																		//CSB 31Aug00
				adptr->acbombbays = animval;							//CSB 31Aug00
			}															//CSB 31Aug00
			else														//CSB 31Aug00
			{															//CSB 31Aug00
				if (adptr->animtoggle)									//CSB 31Aug00
					adptr->animtoggle = -adptr->animtoggle;				//CSB 31Aug00
				else													//CSB 31Aug00
					adptr->animtoggle = 1;								//CSB 31Aug00
			}															//CSB 31Aug00
		}
		else
		{
			SimpleAircraftAnimData*	adptr = (SimpleAircraftAnimData*)ac->Anim;
			if (animval == ANIM_BOMBDOORS_OPEN)
				adptr->bombbaysopen = 1;
			else
				adptr->bombbaysopen = 0;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ACtoSAG
//Author		Robert Slater
//Date			Wed 17 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ACtoSAG(AirStrucPtr	ac, animptr& to)
{
	AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
	SimpleAircraftAnimData*	adptr2 = (SimpleAircraftAnimData*) to;

	adptr2->itemstate = adptr->itemstate;						//RJS 25Nov99

// Launchers...

	SLong	realindex = adptr2->weaponlaunchers[0].launcherIndex;
	adptr2->weaponlaunchers[0] = adptr->weaponlaunchers[4];
	adptr2->weaponlaunchers[0].launcherIndex = realindex;

	adptr->weaponlaunchers[4].hdg = 0;							//RJS 20Dec99
	adptr->weaponlaunchers[4].pitch = 0;						//RJS 20Dec99

	if (	((adptr->weaponlaunchers[0].LauncherType & LT_MASK)==LT_SMKTRAILS)//RJS 20Dec99
		&&	adptr->weaponlaunchers[0].hdg	)					//RJS 20Dec99
		adptr2->station1dead = 1;
	else
		adptr2->station1dead = 0;

	if (	((adptr->weaponlaunchers[1].LauncherType & LT_MASK)==LT_SMKTRAILS)//RJS 20Dec99
		&&	adptr->weaponlaunchers[1].hdg	)					//RJS 20Dec99
		adptr2->station2dead = 1;
	else
		adptr2->station2dead = 0;

	if (	((adptr->weaponlaunchers[2].LauncherType & LT_MASK)==LT_SMKTRAILS)//RJS 20Dec99
		&&	adptr->weaponlaunchers[2].hdg	)					//RJS 20Dec99
		adptr2->station3dead = 1;
	else
		adptr2->station3dead = 0;

	if (	((adptr->weaponlaunchers[3].LauncherType & LT_MASK)==LT_SMKTRAILS)//RJS 20Dec99
		&&	adptr->weaponlaunchers[3].hdg	)					//RJS 20Dec99
		adptr2->station4dead = 1;
	else
		adptr2->station4dead = 0;
	
	adptr2->bombsdropped = 0;
	for (int i=0; i < adptr->nolaunchers; i++)
	{
		if (	((adptr->weaponlaunchers[i].LauncherType & LT_MASK)==LT_BOMB)
			&&	!adptr->weaponlaunchers[i].LoadedStores	)
		{
			adptr2->bombsdropped = 1;
			break;
		}
	}

// Anims...

	adptr2->LEFTWINGOUT = adptr->LEFTWINGOUT;
	adptr2->LEFTWINGIN = adptr->LEFTWINGIN;
	adptr2->RIGHTWINGOUT = adptr->RIGHTWINGOUT;
	adptr2->RIGHTWINGIN = adptr->RIGHTWINGIN;
	adptr2->ENGINELEFT = adptr->ENGINELEFT;
	adptr2->ENGINERIGHT = adptr->ENGINERIGHT;
	adptr2->OTHER = adptr->OTHER;
//DeadCode RJS 11Jul00 	memcpy(&adptr2->LEFTWINGOUT,&adptr->LEFTWINGOUT,&adptr->ENGINERIGHT-&adptr->LEFTWINGOUT);
//DeadCode RJS 11Jul00 	adptr2->OTHER = adptr->OTHER;

	if (adptr->acbombbays)
		adptr2->bombbaysopen = 1;
	else
		adptr2->bombbaysopen = 0;

// Others...

	adptr2->hassmoked = adptr->hassmoked;
	adptr2->acrpm = adptr->acrpm;

// Damage...

	DetachUnwantedVapourStreams(ac);							//RJS 20Dec99
	adptr->hasdust = FALSE;										//RJS 20Dec99

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ACtoSAG
//Author		Robert Slater
//Date			Wed 17 Nov 1999
//
//Description	Copies from SAG animdata to Aircraft anim data.
//
//				Assumes that the a/c animdata has been reset,
//				either by a call to resetanimdata, or defaultanimdata.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SAGtoAC(animptr&	from, animptr& to)
{
	SimpleAircraftAnimData*	adptr = (SimpleAircraftAnimData*) from;
	AircraftAnimData*	adptr2 = (AircraftAnimData*) to;

// Launchers...

	adptr2->itemstate = adptr->itemstate;						//RJS 25Nov99

	SLong	realindex = adptr2->weaponlaunchers[4].launcherIndex;	//RJS 10Dec99
	adptr2->weaponlaunchers[4] = adptr->weaponlaunchers[0];			//RJS 10Dec99
	adptr2->weaponlaunchers[4].launcherIndex = realindex;			//RJS 10Dec99

	adptr->weaponlaunchers[0].hdg = 0;							//RJS 20Dec99
	adptr->weaponlaunchers[0].pitch = 0;						//RJS 20Dec99

	if (adptr->station1dead)
	{
		adptr2->weaponlaunchers[0].hdg = 0;								//RJS 29Aug00
		adptr2->weaponlaunchers[0].pitch = 0;							//RJS 29Aug00
		adptr2->weaponlaunchers[0].Stores = 0;
		adptr2->weaponlaunchers[0].LoadedStores = 0;
		adptr2->weaponlaunchers[0].IsArmed = 0;
		adptr2->weaponlaunchers[0].LauncherType = LT_FUEL;
	}

	if (adptr->station2dead)
	{
		adptr2->weaponlaunchers[1].hdg = 0;								//RJS 29Aug00
		adptr2->weaponlaunchers[1].pitch = 0;							//RJS 29Aug00
		adptr2->weaponlaunchers[1].Stores = 0;
		adptr2->weaponlaunchers[1].LoadedStores = 0;
		adptr2->weaponlaunchers[1].IsArmed = 0;
		adptr2->weaponlaunchers[1].LauncherType = LT_FUEL;
	}

	if (adptr->station3dead)
	{
		adptr2->weaponlaunchers[2].hdg = 0;								//RJS 29Aug00
		adptr2->weaponlaunchers[2].pitch = 0;							//RJS 29Aug00
		adptr2->weaponlaunchers[2].Stores = 0;
		adptr2->weaponlaunchers[2].LoadedStores = 0;
		adptr2->weaponlaunchers[2].IsArmed = 0;
		adptr2->weaponlaunchers[2].LauncherType = LT_FUEL;
	}

	if (adptr->station4dead)
	{
		adptr2->weaponlaunchers[3].hdg = 0;								//RJS 29Aug00
		adptr2->weaponlaunchers[3].pitch = 0;							//RJS 29Aug00
		adptr2->weaponlaunchers[3].Stores = 0;
		adptr2->weaponlaunchers[3].LoadedStores = 0;
		adptr2->weaponlaunchers[3].IsArmed = 0;
		adptr2->weaponlaunchers[3].LauncherType = LT_FUEL;
	}

	if (adptr->bombsdropped)
	{
		for (int i=0; i < adptr2->nolaunchers; i++)
		{
			if ((adptr2->weaponlaunchers[i].LauncherType&LT_MASK)==LT_BOMB)
				adptr2->weaponlaunchers[i].LoadedStores = 0;
		}
	}

// Anims...

	if (adptr->bombbaysopen)
		adptr2->acbombbays = 255;


// Damage...

	memcpy(&adptr2->LEFTWINGOUT,&adptr->LEFTWINGOUT,&adptr->ENGINERIGHT-&adptr->LEFTWINGOUT);
	adptr2->OTHER = adptr->OTHER;

// Others...

	adptr2->hassmoked = adptr->hassmoked;
	adptr2->acrpm = adptr->acrpm;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestInteractive
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
void	shape::TestInteractive(ShapeNum	theShape, animptr& animdata)
{
	if (	Save_Data.flightdifficulty[FD_ENGINEMANAGMENT]				//RJS 29Aug00
		&&	(Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW)	)	//RJS 29Aug00
	{
		if (	(OverLay.disableInteractiveMouse==false)				//RJS 10Oct00
			&&	!lastMActive	)										//RJS 10Oct00
		{
			int		passed = 0;
			SLong	testx,testy;
			SLong	mx,my;

			if (_Analogue.ReadPosition(AU_VIEWH) == -0x8000)
			{
				mx = lastMX - vd_originx;
				my = lastMY - vd_originy;

				SLong	mxSquared = mx*mx;
				SLong	mySquared = my*my;
 				float	hRadius = fastMath.FastInvSqrt(float(mxSquared+mySquared)) * (6.f/14.f);
				
				passed = 2;
 
  				fastMath.FloatToInt(&testx,float(vd_width*mx) * hRadius);
  				fastMath.FloatToInt(&testy,float(vd_height*my) * hRadius);

				if (mxSquared <= (testx*testx))
				{
					passed--;
					mx = testx;
				}

				if (mySquared <= (testy*testy))
				{
					passed--;
					my = testy;
				}
			}

			if (passed)
				View_Point->AddHeadOffset(mx-testx,my-testy);
			else
			{
				ShapeDescPtr sdptr = SHAPESTUFF.GetShapePtr(theShape);

				if (sdptr->InteractiveOffset)
				{
					UByteP	instr_ptr = (UByteP )sdptr + sdptr->InteractiveOffset;
					UWord	instruction = UWord(*instr_ptr);

					lastMPressed = false;
					if (Key_Tests.KeyPress3d(MENUSELECT))
						lastMPressed = true;
					else
					{
						if (Key_Tests.KeyHeld3d(MENUSELECT))
							lastMPressed = true;
					}

					interactivefound = false;
					GlobalAdptr = animdata;

					while (instruction == dointeractivehitboxno)
					{
						instr_ptr++;

						(*InterpTable[instruction]) (instr_ptr);

						instruction = UWord(*instr_ptr);
						if (interactivefound)
							instruction = 0;
					}

					if (!interactivefound)
						_Interactive.ClearCollide(lastMPressed);
					else
					{
						ULong	theCol;
						ULong	stringresource = _Interactive.GetStringResource(theCol);
						if (stringresource)
						{
							const char*	theString;
							CString		tmpstring;
							tmpstring.LoadString(stringresource);
							SWord		screeny = lastMY-20;

							theString = (const char*)tmpstring;

							OverLay.PrintCentered(lastMX,screeny,theString,theCol);	//RJS 09May00
						}
					}

					_Interactive.Process();										//RJS 23Nov99
				}
			}
 		}

		OverLay.doInteractiveCockpit = true;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LogMousePos
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
void	shape::LogMousePos(SWord	mouseX, SWord mouseY, SLong swidth, SLong sheight, const bool isActive)
{
	lastMX = mouseX;
	lastMY = mouseY;
	lastMActive = isActive;

	_Interactive.LogMousePos(mouseX,mouseY,swidth,sheight);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GroupAnimInherit
//Author		Robert Slater
//Date			Wed 24 Nov 1999
//
//Description	Inherit each element's 'invisible' flag.
//				Used to switch dead bomber's bombs off.
//
//				If we have seperate bomb group per squadron,
//				we will want to inherit the xyz offsets too...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GroupAnimInherit(ShapeNum fromShape, ShapeNum toShape, ShapeNum subShape, animptr& fromAnim, animptr& toAnim)
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(fromShape);
	ShapeDescPtr	sdptr2 = SHAPESTUFF.GetShapePtr(toShape);
			
	if (	(SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
		&&	(SHAPESTUFF.GetShapeScale(sdptr2) == SHP_GRP)	)
	{
		UByteP		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		UByteP		instr_ptr2 = (UByteP )sdptr2 + sdptr2->liveshpref;
		MinAnimData*	mad;
		MinAnimData*	mad2;
		animptr		adptr = fromAnim;
		animptr		adptr2 = toAnim;
		UWord		instruction, instruction2;

		forever
		{
			instruction = (UWord )*instr_ptr;
			instr_ptr ++;

			instruction2 = (UWord )*instr_ptr2;
			instr_ptr2 ++;

			if (	(instruction == dogroupno)
				&&	(instruction2 == dogroupno)	)
			{
				DOGROUP_PTR temp = (DOGROUP_PTR)instr_ptr;
				DOGROUP_PTR temp2 = (DOGROUP_PTR)instr_ptr2;

				mad = (MinAnimData*) adptr;
				mad2 = (MinAnimData*) adptr2;

				mad2->IsInvisible = mad->IsInvisible;

// Do we want to inherit coordinates too?
//
				temp2->xoffset = temp->xoffset;
				temp2->yoffset = temp->yoffset;
				temp2->zoffset = temp->zoffset;
				temp2->shapenum = subShape;						//RJS 08Dec99

				// The animdata for 'subShape' MUST be the same as the dummy shape
				// originally defined in the group!

				adptr += SHAPE.GetElementAnimOffset((ShapeNum)temp->shapenum);
				adptr2 += SHAPE.GetElementAnimOffset((ShapeNum)temp2->shapenum);

				instr_ptr += sizeof(DOGROUP);
				instr_ptr2 += sizeof(DOGROUP);
			}
			else
				break;
		}
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    GroupMemberInherit
// Date:		02/06/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	shape::GroupMemberInherit(ItemBasePtr launcher, ShapeNum toShape, ShapeNum subShape,  animptr& toAnim)
{
	ShapeDescPtr	sdptr2 = SHAPESTUFF.GetShapePtr(toShape);
	const int MAXHORI=METRES2000,MAXVERT=METRES500,SQRT_MH2_MH2_MV2=METRES3000;//2800, but who's counting?
	sdptr2->sx=MAXHORI>>4;
	sdptr2->sz=MAXHORI>>4;
	sdptr2->sy=MAXVERT>>4;
	sdptr2->Size=SQRT_MH2_MH2_MV2;

	if ((SHAPESTUFF.GetShapeScale(sdptr2) == SHP_GRP)	)
	{
		UByteP		instr_ptr2 = (UByteP )sdptr2 + sdptr2->liveshpref;
		MinAnimData*	mad;
		MinAnimData*	mad2;
		animptr		adptr2 = toAnim;
		UWord		instruction, instruction2;
		AirStrucPtr SAG=AirStrucPtr(*launcher);
		int	grouplpos=SAG->fly.originalformpos&InFormMAX, 
			groupwpos=0;
		int totalac=SAG->fly.numinsag;
		SingleFormation	
			wingmanpos=Aircraft_Formations[(SAG->formation&FORMTYPE_WING)>>FORMTYPE_WING_SH];
		int perfl=wingmanpos->GetPerFl(totalac);						//JIM 7Jul00
//DeadCode JIM 7Jul00 		int perfl=wingmanpos->numentries;
//DeadCode JIM 7Jul00 		if (perfl>=10)
//DeadCode JIM 7Jul00 		{
//DeadCode JIM 7Jul00 			UWord fl2=perfl;
//DeadCode JIM 7Jul00 			while (fl2>=0)
//DeadCode JIM 7Jul00 			{
//DeadCode JIM 7Jul00 				perfl=fl2%10;
//DeadCode JIM 7Jul00 				breakif (totalac%perfl==0);			//JIM 7Jul00
//DeadCode JIM 7Jul00 				fl2/=10;
//DeadCode JIM 7Jul00 			}
//DeadCode JIM 7Jul00 		}
		AirStrucPtr l=SAG->fly.expandedsag;
		AirStrucPtr w=l;
		int		aclpos=w->fly.originalformpos&InFormMAX;
		int		acwpos=w->fly.originalformpos&InWingMAX; 

		forever
		{

			instruction2 = (UWord )*instr_ptr2;
			instr_ptr2 ++;

			if (	(instruction2 == dogroupno)	)
			{
				DOGROUP_PTR temp2 = (DOGROUP_PTR)instr_ptr2;

				mad2 = (MinAnimData*) adptr2;

				
				bool	invisible=true;	//mad->IsInvisible;
				COORDS3D* p=NULL;
				if (aclpos==grouplpos&&acwpos==groupwpos)
				{
					invisible=false;
					p=&w->World;
					w=w->Follower();
					if (!w)
						w=l=l->fly.nextflight;
					if (w)
					{
						aclpos=w->fly.originalformpos&InFormMAX; 
						acwpos=w->fly.originalformpos&InWingMAX; 
					}
					else
						aclpos=-1;
				}
				groupwpos++;
				if (groupwpos==perfl)
				{
					groupwpos=0;
					grouplpos++;
				}


				mad2->IsInvisible = invisible;

// Do we want to inherit coordinates too?

				if (!invisible)
				{
					temp2->xoffset = p->X-launcher->World.X;//temp->xoffset;
					temp2->yoffset = p->Y-launcher->World.Y;//temp->yoffset;
					temp2->zoffset = p->Z-launcher->World.Z;//temp->zoffset;
					if (	temp2->xoffset>MAXHORI || temp2->xoffset<-MAXHORI
						||	temp2->zoffset>MAXHORI || temp2->zoffset<-MAXHORI
						||	temp2->yoffset>MAXVERT || temp2->yoffset<-MAXVERT
						)
						mad2->IsInvisible = true;
				}
				temp2->shapenum = subShape;						//RJS 08Dec99

				// The animdata for 'subShape' MUST be the same as the dummy shape
				// originally defined in the group!

				adptr2 += SHAPE.GetElementAnimOffset((ShapeNum)temp2->shapenum);

				instr_ptr2 += sizeof(DOGROUP);
			}
			else
				break;
		}
	}




}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleGroupItemAnim
//Author		Robert Slater
//Date			Thu 25 Nov 1999
//
//Description	Just returns the shape and animdata pointer for a group element
//				as indicated by 'index'
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SimpleGroupItemAnim(animptr& adptr, ShapeNum& shape, SLong index, Coords3D& position)
{
	ShapeDescPtr		sdptr;

	sdptr = SHAPESTUFF.GetShapePtr(shape);
	if ((SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP) && (index > -1))
	{
		UByteP		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		UWord		instruction;
		DOGROUP_PTR temp;
		SLong		count = 0;

		forever
		{
			instruction = (UWord )*instr_ptr;
			instr_ptr ++;

			if (instruction != dogroupno)
				break;

			temp = (DOGROUP_PTR)instr_ptr;
				
			shape = (ShapeNum)temp->shapenum;

			if (count==index)
			{
				position.X = temp->xoffset;
				position.Y = temp->yoffset;
				position.Z = temp->zoffset;
				break;
			}
			else
			{
				adptr += GetElementAnimOffset(shape);

				instr_ptr += sizeof(DOGROUP);
				count++;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllBombsDropped
//Author		Robert Slater
//Date			Fri 10 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::AllBombsDropped(ItemPtr	ac)
{
	SimpleAircraftAnimData*	aptr;
	ShapeDescPtr			sdptr = SHAPESTUFF.GetShapePtr(ac->shape);
	UByteP					instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
	UWord					instruction;
	DOGROUP_PTR				temp;
	animptr					adptr = ac->Anim;
	ShapeNum				shape;

	instruction = (UWord )*instr_ptr;
	while (instruction == dogroupno)
	{
		aptr = (SimpleAircraftAnimData*)adptr;
		if (!aptr->IsInvisible)
			aptr->bombsdropped = 1;

		instr_ptr ++;

		temp = (DOGROUP_PTR)instr_ptr;
				
		shape = (ShapeNum)temp->shapenum;

		adptr += GetElementAnimOffset(shape);

		instr_ptr += sizeof(DOGROUP);
		instruction = (UWord )*instr_ptr;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ForceWeaponDamage
//Author		Robert Slater
//Date			Thu 25 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ForceWeaponDamage(	ItemPtr		theItem,
									ItemPtr		theShooter,
									ShapeNum	newShape,
									animptr&	adptr,
									SLong		elementindex,
									SLong		damageloc,
									SLong		damagetype,
									SLong		damageAmount,
									Coords3D*	groupoffset		)
{
	SLong	olddamage = adptr[(int)damageloc];
	SLong	newdamage = olddamage + damageAmount;				//RJS 10May00

	if (newdamage > BS_DEAD)
		newdamage = BS_DEAD;

	if (damageloc && (olddamage != newdamage))					//RJS 10May00
	{
		Squad_Diary.SetAC(theItem,adptr);								//CSB 3Nov00

		ShapeDescPtr sdptr = SHAPESTUFF.GetShapePtr(newShape);
		if (sdptr->CollisionOffset)
		{
			SLong	oldoffset;
			bool	go;
			UByteP	instr_ptr;
			UWord	instruction;
//DEADCODE RJS 5/10/00 			UByte	olddamage = adptr[(int)damageloc];
			SLong	oldcollogcnt = ColLogCnt;
			Bool	oldcolflag;


			BoxCol::ResetCollisionStuff();
			BoxCol::Col_Shooter = theShooter;
			BoxCol::HitterStrength = damageAmount;				//RJS 10May00
			BoxCol::HitterDamageType = damagetype;

			bool	oldState = BoxCol::SetTestState(true);				//AMM 4Jul00

			if (SHAPESTUFF.GetShapeScale(SHAPESTUFF.GetShapePtr(theItem->shape))!=SHP_GRP)
			{
				elementindex = -1;
				newShape = theItem->shape;
			}

			oldcolflag = CollisionOn;
			oldoffset = HitThisOffset;

			damage_ItemPtr = theItem;
			damage_AnimPtr = adptr;		
			damage_Shape = newShape;	
			damage_GrpElmt = elementindex;		
			damage_Sdptr = (UByteP) sdptr;
			damage_ItemState = newdamage;
			damage_GrpPrev = NULL;
			damage_GrpNext = NULL;
			if ((elementindex != -1) && groupoffset)
			{
				damage_GrpOffset = new MyGroundVector;
				if (damage_GrpOffset)
				{
					damage_GrpOffset->gx=groupoffset->X;
					damage_GrpOffset->gy=groupoffset->Y;
					damage_GrpOffset->gz=groupoffset->Z;
				}
			}
			else
				damage_GrpOffset = NULL;

			go = true;
			HitThisOffset = damageloc;

			lastdamage[0] = UByte(olddamage);
			lastdamptr = &adptr[(int)damageloc];

			CommsDamage = FALSE;
			CollisionOn = FALSE;

			collisionDepth = 0;											//RJS 21Sep00

			switch (SHAPESTUFF.GetShapeScale(sdptr))
			{
				case SHP_GRP:
					_Error.EmitSysErr(__FILE__":Bad shape type field (SHAPE NUMBER %d)",theItem->shape);
					break;
				case SHP_1CM:
					damage_Scale = 0;										
					break;												
				case SHP_4CM:
					damage_Scale = 2;										
					break;												
				case SHP_16CM:
					damage_Scale = 4;										
					break;
			}

			instr_ptr = (UByteP )sdptr + sdptr->CollisionOffset;

			_Replay.FakeCollisionOn=false;
			while (go)
			{
				instruction = (UWord) *instr_ptr;
				instr_ptr ++;
#ifndef	NDEBUG
				if (instruction > dosetglassrangeno)
					_Error.EmitSysErr(__FILE__":Bad instruction in collision (%d)",instruction);
#endif
				if (	((instruction == doretno) && collisionDepth)//CollisionOn)	//RJS 21Sep00
					||	(instruction==doendno))
					break;

				if (_Replay.FakeCollisionOn)
				{
					CollisionOn=FALSE;
					collisionDepth++;									//RJS 21Sep00
				}

				(*InterpTable[instruction]) (instr_ptr);

				if (_Replay.FakeCollisionOn)
					CollisionOn=TRUE;
			}

			delete damage_GrpOffset;
			damage_GrpOffset = NULL;

			_Replay.FakeCollisionOn=false;
			if (!oldcollogcnt)					
			{									
				FixUpColLog();					
				BoxCol::ProcessEffectQueue(theItem);
			}

			BoxCol::SetTestState(oldState);								//AMM 4Jul00

			HitThisOffset = oldoffset;
			CommsDamage = FALSE;
			CollisionOn = oldcolflag;
		}

		Squad_Diary.UpdateACDamage();							//RJS 23Feb00
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BirdLauncherItemAnim
//Author		Robert Slater
//Date			Wed 1 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::BirdLauncherItemAnim(BirdLauncherAnimData*	adptr, Coords3D& itemCoords)
{
	if (!Three_Dee.IsPaused())
	{
		if (adptr->isPregnant)
		{
			if (!adptr->countdown)
			{
				if (	(object_obj3d->realbz.f < 50000.0)				//RJS 16Jun00
					&& 	(Math_Lib.rnd() > 64000)			)
				{
					ItemPtr			theItem = object_obj3d->ItemPtr;
					Coords3D		theCoords = itemCoords;
					ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(object_obj3d->Shape);
					if (sdptr->LauncherDataSize)
					{
						SLong	instsize = sizeof(DOLAUNCHER) + 1;
						UByteP	instr_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;
						UWord	instruction = (UWord)*instr_ptr;
						DOLAUNCHER_PTR	ptr;
						SLong			nolaunchers = 0;

						instr_ptr++;
						while (instruction == dolauncherno)
						{
							nolaunchers++;
							instruction = (UWord)*instr_ptr;
							instr_ptr++;
						}

						if (nolaunchers)
						{
							nolaunchers = Math_Lib.rnd(nolaunchers);

							instr_ptr = (UByteP)sdptr + sdptr->LauncherDataSize + (nolaunchers*instsize);
							instr_ptr++;
							ptr = (DOLAUNCHER_PTR)instr_ptr;

							theCoords.X += ptr->posx;
							theCoords.Y += ptr->posy;
							theCoords.Z += ptr->posz;
						}
					}

					adptr->countdown = 30000;		//5mins

					Trans_Obj.LaunchBirds((mobileitem*)theItem,theCoords,(ShapeNum)adptr->theShape,8,*mobileitem::currworld);

					_Miles.PlayDelayed(FIL_SFX_AMB_WINGS,theItem);
				}
			}
			else
			{
				SLong	countdown = adptr->countdown;
				countdown -= View_Point->DrawFrameTime();
				if (countdown < 0)
					countdown = 0;

				adptr->countdown = countdown;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetTotalPilots
//Author		Robert Slater
//Date			Thu 21 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::GetTotalPilots(ItemPtr	itm, animptr&	adptr)
{
	SLong			total = 0;
	MinAnimData*	mad;

	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
	if (SHAPESTUFF.GetShapeScale(sdptr)==SHP_GRP)
	{
		UByteP			instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		UWord			instruction;
		DOGROUP_PTR		ptr;
		animptr			tmpadptr = itm->Anim;
		UWord			theShape;
		UByteP			byteAddress = &adptr;							//RJS 3Nov00

		forever
		{
			instruction = UWord(*instr_ptr);
			instr_ptr ++;

			if (instruction != dogroupno)
				break;

			ptr = DOGROUP_PTR(instr_ptr);
				
			theShape = ptr->shapenum;

			if (byteAddress == &tmpadptr)										//RJS 3Nov00
			{
				mad = (MinAnimData*)tmpadptr;
				if (	(mad->itemstate < DYING)
					&&	!mad->IsInvisible	)
					total = GetTotalPilots(ShapeNum(theShape));

				break;
			}

			tmpadptr += GetElementAnimOffset(ShapeNum(theShape));
		 
			instr_ptr += sizeof(DOGROUP);
		}
	}
	else
	{
		mad = (MinAnimData*)adptr;
		if (	(mad->itemstate < DYING)
			&&	!mad->IsInvisible	)
			total = GetTotalPilots(itm->shape);
	}

	return total;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetTotalPilots
//Author		Robert Slater
//Date			Mon 6 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::GetTotalPilots(ShapeNum	theShape)
{
	SLong			total = 0;

	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(theShape);
	if (sdptr->LauncherDataSize)
	{
		UByteP			instr_ptr = (UByteP)sdptr + sdptr->LauncherDataSize;
		UWord			instruction;
		DOLAUNCHER_PTR	ptr;

		instruction = (UWord) *instr_ptr;
		while (instruction == dolauncherno)
		{
			instr_ptr++;

			ptr = (DOLAUNCHER_PTR)instr_ptr;
			if (ptr->lnchrtype == CT_PILOT)
			{
				total++;
				total += ptr->noChildren;
			}

			instr_ptr += sizeof(DOLAUNCHER);
			instruction = (UWord) *instr_ptr;
		}
	}

	return total;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPilotPos
//Author		Robert Slater
//Date			Mon 6 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GetPilotPos(ItemPtr	itm,UWord index,Coords3D& pos, SWord& relypos)
{
	DOLAUNCHER_PTR	thislaunch = NULL;
	ShapeDescPtr	sdptr;
	UByte			thisscale = 0;
//DeadCode RJS 20Oct00 	MyGroundVectorPtr		goffset = NULL;								//RJS 21Nov96
	SLong			count = 0;
	SLong			pilotcnt = 0;
	ShapeNum		theShape = itm->shape;

 	sdptr = SHAPESTUFF.GetShapePtr(theShape);
 	switch (SHAPESTUFF.GetShapeScale(sdptr))
 	{
 		case SHP_1CM:
 			thisscale = 0;
 			break;
 
 		case SHP_4CM:
 			thisscale = 2;
 			break;
 
 		case SHP_16CM:
 			thisscale = 4;
 			break;
 	}

	pos.X = 0;
	pos.Y = 0;
	pos.Z = 0;

	relypos = 0;														//RJS 3Jul00

	do
	{
		thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(theShape,count++);
		if (thislaunch)
		{
			if (thislaunch->lnchrtype == CT_PILOT)
			{
				pilotcnt++;
				pilotcnt += thislaunch->noChildren;
				if (index < pilotcnt)
				{
//DeadCode RJS 3Jul00 					heading = thislaunch->hdg;
//DeadCode RJS 3Jul00 					heading <<= 8;
					relypos= thislaunch->posy;
					break;
				}
			}
		}
	}
	while (thislaunch);

	LauncherToWorld(itm,(UByteP )thislaunch,thisscale,pos.X,pos.Y,pos.Z,NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FakeLauncherAnim
//Author		Robert Slater
//Date			Wed 8 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::FakeLauncherAnim(animptr&	adptr, ShapeNum	shpno, SLong weappak)
{
	AircraftAnimData	fakeanim;
	animptr				fakeadptr = adptr;
	ShapeNum			fakeshape;
	ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(shpno);
	SLong				wpindex, ltype;

	fakeadptr = (UByteP)&fakeanim;
	fakeshape = (ShapeNum)sdptr->Type.shapenumber;

	InitLauncherAnim(fakeadptr,fakeshape,weappak);

	for (wpindex = 0; wpindex < fakeanim.nolaunchers; wpindex++)
	{
		ltype = fakeanim.weaponlaunchers[wpindex].LauncherType;
		if ((ltype & LT_MASK)==LT_BOMB)
		{
			if (sdptr->LauncherDataSize)
			{
				SimpleAircraftAnimData* aptr = (SimpleAircraftAnimData*)adptr;
//TEMPCODE JIM 31/05/00 				UByteP	instr_ptr = (UByteP)sdptr + sdptr->LauncherDataSize;
//TEMPCODE JIM 31/05/00 				UWord	instruction;
//TEMPCODE JIM 31/05/00 				DOLAUNCHER_PTR	ptr;
		
				aptr->nolaunchers = 1;
				aptr->weaponlaunchers[0] = fakeanim.weaponlaunchers[wpindex];
//TEMPCODE JIM 31/05/00 				aptr->weaponlaunchers[0].launcherIndex = 0;
//TEMPCODE JIM 31/05/00 
//TEMPCODE JIM 31/05/00 				// This bit should not be necessary, as the simple ac should
//TEMPCODE JIM 31/05/00 				// contain the same launchers as the complicated ac...
//TEMPCODE JIM 31/05/00 
//TEMPCODE JIM 31/05/00 				SLong	realindex = 0;
//TEMPCODE JIM 31/05/00 				instruction = (UWord)*instr_ptr;
//TEMPCODE JIM 31/05/00 				while (instruction == dolauncherno)
//TEMPCODE JIM 31/05/00 				{
//TEMPCODE JIM 31/05/00 					instr_ptr++;
//TEMPCODE JIM 31/05/00 					ptr = (DOLAUNCHER_PTR)instr_ptr;
//TEMPCODE JIM 31/05/00 					if ((ptr->lnchrtype & LT_MASK)==LT_BOMB)
//TEMPCODE JIM 31/05/00 					{
//TEMPCODE JIM 31/05/00 						aptr->weaponlaunchers[0].launcherIndex = realindex;
//TEMPCODE JIM 31/05/00 						break;
//TEMPCODE JIM 31/05/00 					}
//TEMPCODE JIM 31/05/00 
//TEMPCODE JIM 31/05/00 					realindex++;
//TEMPCODE JIM 31/05/00 					instr_ptr += sizeof(DOLAUNCHER);
//TEMPCODE JIM 31/05/00 					instruction = (UWord)*instr_ptr;
//TEMPCODE JIM 31/05/00 				}
			}
			break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSuperLauncher
//Author		Robert Slater
//Date			Wed 8 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
WeapAnimData* shape::GetSuperLauncher(	itemptr		itm,
										Coords3D&	pos,
									 	UWord&		muzzleDelay,
										UWord&		bombsDropped,	
										SByte 		ltype,
										UWord		*bulletShape	)
{
	ShapeDescPtr		sdptr;
	DOLAUNCHER_PTR		thislaunch = NULL;
	animptr				animdataptr;
	UByteP				instr_ptr;
	ShapeNum			shape;
	ShapeDescPtr		tmpsdptr;
	WeapAnimData*		weapon=NULL;
	MoveGunAnimData*	aptr;
	UByte				thisscale = 0;
	int					cnt;
	ULong				muzindex = 0;
//DeadCode RJS 20Oct00 	UWord				noLaunchers = 0;					
	ShapeNum			scaleshape;								
	SLong				shapeIndex = 0;						
	bool				foundone = false;
	SLong				xpos,ypos,zpos;						


	bombsDropped = 0;
	muzzleDelay = 15;
	shape= scaleshape = itm->shape;								

	animdataptr = itm->Anim;

	aptr = (MoveGunAnimData*) animdataptr;
	sdptr = SHAPESTUFF.GetShapePtr(scaleshape);

	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
	{
		SLong	tmp;

		if (sdptr->Type.haslaunchers)
		{
			instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
			while (GetGroupElement(instr_ptr,shape,xpos,ypos,zpos))
			{
				ShapeDescPtr	mastersdptr = SHAPESTUFF.GetShapePtr(shape);	//JIM 31/05/00
																		//JIM 31/05/00
				if (mastersdptr->Type.shapenumber)						//JIM 31/05/00
					shape = ShapeNum(mastersdptr->Type.shapenumber);	//JIM 31/05/00

				foundone = true;
				break;
			}
		}
	}

	xpos = ypos = zpos = 0;
	if (foundone)
	{
		if (aptr->nolaunchers && aptr->itemstate==ALIVE)
		{
			DOLAUNCHER	fiddledlauncher;
			bool		noFix = false;

			sdptr = SHAPESTUFF.GetShapePtr(shape);	
			switch(SHAPESTUFF.GetShapeScale(sdptr))
			{
				case SHP_1CM:
					thisscale = 0;
					break;												
				case SHP_4CM:
					thisscale = 2;										
					break;												
				case SHP_16CM:
					thisscale = 4;										
					break;
			}

			weapon = &aptr->weaponlaunchers[0];
			if (weapon)
			{
				shapeIndex = weapon->launcherIndex;

				thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shape,shapeIndex);	//RJS 15Nov99

				if (weapon->stationshape)
				{
					// Get base x,y,z...
					if (thislaunch)
					{
						// Real index and shape...
						if (weapon->LoadedStores)
						{
							DOLAUNCHER_PTR	thislaunch2;

							SLong	index = weapon->Stores - weapon->LoadedStores;
							thislaunch2 = (DOLAUNCHER_PTR) GetLauncherPos(ShapeNum(weapon->stationshape),index);
							if (thislaunch2)
							{
								// Sub launcher is relative to main launcher...
								fiddledlauncher = *thislaunch;
								fiddledlauncher.posx += thislaunch2->posx;
								fiddledlauncher.posy += thislaunch2->posy;
								fiddledlauncher.posz += thislaunch2->posz;
								thislaunch = &fiddledlauncher;
								noFix = true;
							}
						}
					}
				}
//DeadCode RJS 13Nov00 				thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(shape,shapeIndex);
//DeadCode RJS 13Nov00 				if (thislaunch)
//DeadCode RJS 13Nov00 				{
//DeadCode RJS 13Nov00 					// Real index and shape...
//DeadCode RJS 13Nov00 				 	if (weapon->LoadedStores)
//DeadCode RJS 13Nov00 				 	{
//DeadCode RJS 13Nov00 				 		DOLAUNCHER_PTR	thislaunch2;
//DeadCode RJS 13Nov00 
//DeadCode RJS 13Nov00 				 		SLong	index = weapon->Stores - weapon->LoadedStores;
//DeadCode RJS 13Nov00 				 		thislaunch2 = (DOLAUNCHER_PTR) GetLauncherPos((ShapeNum)weapon->stationshape,index);//RJS 08Dec99
//DeadCode RJS 13Nov00 				 		if (thislaunch2)
//DeadCode RJS 13Nov00 				 		{
//DeadCode RJS 13Nov00 				 			// Sub launcher is relative to main launcher...
//DeadCode RJS 13Nov00 				 			fiddledlauncher = *thislaunch;
//DeadCode RJS 13Nov00 				 			fiddledlauncher.posx += thislaunch2->posx;
//DeadCode RJS 13Nov00 				 			fiddledlauncher.posy += thislaunch2->posy;
//DeadCode RJS 13Nov00 				 			fiddledlauncher.posz += thislaunch2->posz;
//DeadCode RJS 13Nov00 				 			thislaunch = &fiddledlauncher;
//DeadCode RJS 13Nov00 							noFix = true;
//DeadCode RJS 13Nov00 				 		}
//DeadCode RJS 13Nov00 				 	}
//DeadCode RJS 13Nov00 				}
			}
			else
				thislaunch = NULL;

			if (thislaunch)
			{
				if (	(thislaunch->lnchrtype < LT_CONTACT)
					||	(thislaunch->lnchrtype > CT_DUMMY)	)
				{
					if (weapon == NULL)
						_Error.EmitSysErr(__FILE__":Weapon launcher index out of range!");
				}

				if (ltype > -1)
				{
					if (weapon)
					{
						if ((weapon->LauncherType & LT_MASK) != ltype)
						{
							thislaunch = NULL;
							weapon = NULL;
						}
						else
						{
							bombsDropped = thislaunch->noChildren;
							if (!noFix)
							{
								SLong	gunno = weapon->currGun;

								bombsDropped = thislaunch->noChildren;
								if (bombsDropped && gunno)
								{
									if (gunno > bombsDropped)
										weapon->currGun = 0;
									else
										thislaunch = (DOLAUNCHER_PTR) ((UByteP)thislaunch + ((1+sizeof(DOLAUNCHER))*gunno));
								}
							}

							muzindex = weapon->LaunchTime & 0x00FF;						
							if (muzindex > MaxMuzzles)									
								muzindex = 0;											
																						
							muzzleDelay = launcherdata[muzindex].firingdelay;			
																						
							if (bulletShape)											
								*bulletShape = (UWord) launcherdata[muzindex].theShape;	
						}

					}
				}
			}

			if (thislaunch)
			{
				xpos = thislaunch->posx << thisscale;
				ypos = thislaunch->posy << thisscale;
				zpos = thislaunch->posz << thisscale;

				if (itm->Status.size >= MOBILESIZE)
				{
					MATRIX   	omat;						
					MATRIX_PTR	obj_matrix = &omat;
					SLong		scaleback;
					mobileitem*	tmpitm = (mobileitem*)itm;

					_matrix.generate2(tmpitm->hdg, tmpitm->pitch, tmpitm->roll, obj_matrix);
		
					scaleback = _matrix.transform(obj_matrix,xpos,ypos,zpos);

					xpos >>= (16-scaleback);
					ypos >>= (16-scaleback);
					zpos >>= (16-scaleback);
				}
			}
		}
	}

	pos.X = xpos;
	pos.Y = ypos;
	pos.Z = zpos;

	return(weapon);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SwitchToRearGunner
//Author		Robert Slater
//Date			Fri 10 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SwitchToRearGunner(AirStrucPtr	ac, int gunnerNumber)
{
	int	gunnerCount = -1;										//RJS 02May00

	reargunner_cockpitindex = 0;								//RJS 02May00
	if (reargunner_active == false)
	{
		AircraftAnimData*	adptr = (AircraftAnimData*)ac->Anim;
		SLong				index;
		SLong				launchindex;
		DOLAUNCHER_PTR		lptr;

//DeadCode RJS 02May00 		reargunner_cockpitindex = 0;								//RJS 28Feb00
		for (index=0; index < adptr->nolaunchers; index++)
		{
			if ((adptr->weaponlaunchers[index].LauncherType & LT_MASK)==LT_MOVEGUN)
			{
				gunnerCount++;
				if (gunnerCount == gunnerNumber)
					SetRearGunner(ac,index,index);						//RJS 24Oct00
			}
		}

		if (gunnerCount == -1)									//RJS 24Oct00
		{
// All our guns have been destroyed, so force view to outside!
			if (View_Point)
				View_Point->ForceToOutside();
		}
	}
	else
	{
		if (ac == reargunner_item)
		{
			SwitchToPilot();			//Restore old gunner	//RJS 02May00

			// Switch to next gun, if there is one...
			AircraftAnimData*	adptr = (AircraftAnimData*)ac->Anim;
			SLong				index;
			SLong				tmplauncher,tmpindex;
			SLong				launchindex;
			DOLAUNCHER_PTR		lptr;
	
			tmpindex = -1;
			for (index=0; index < adptr->nolaunchers; index++)
			{
				if ((adptr->weaponlaunchers[index].LauncherType & LT_MASK)==LT_MOVEGUN)
				{
					gunnerCount++;
					if (gunnerCount == gunnerNumber)
					{
//DeadCode RJS 23May00 						tmplauncher = adptr->weaponlaunchers[index].LauncherType;
						tmpindex = index;
						break;
					}
				}
			}

//DeadCode RJS 02May00 			SwitchToPilot();			//Restore old gunner
			if (tmpindex != -1)
				SetRearGunner(ac,tmpindex,tmpindex);					//RJS 24Oct00
			else
			{
				if (gunnerCount != -1)									//RJS 24Oct00
					SwitchToRearGunner(ac);	//This will just reset
				else
				{
// All our guns have been destroyed, so force view to outside!
					if (View_Point)
						View_Point->ForceToOutside();
				}
			}
		}
		else
		{
			SwitchToPilot();
			SwitchToRearGunner(ac);
		}
	}

	if (	Manual_Pilot.ControlledAC2
		&&	(Manual_Pilot.ControlledAC2 == ac)	)
		Trans_Obj.SetTotalAmmo(ac);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SwitchToPilot
//Author		Robert Slater
//Date			Fri 10 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SwitchToPilot(bool entering3d)
{
	if (entering3d)
	{
		reargunner_cockpitindex = 0;							//RJS 28Feb00
		reargunner_active = false;
	}
	else
	{
		if (reargunner_active == true)
		{
			AircraftAnimData*	adptr = (AircraftAnimData*)reargunner_item->Anim;

			if ((adptr->weaponlaunchers[reargunner_index].LauncherType & LT_MASK) < LT_SMKTRAILS)	//RJS 10Aug00
			{
				adptr->weaponlaunchers[reargunner_index].LaunchTime = reargunner_launchtime;
				adptr->weaponlaunchers[reargunner_index].LauncherType = reargunner_launcher;
			}

			reargunner_active = false;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetCockpitShape
//Author		Robert Slater
//Date			Mon 28 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ShapeNum	shape::GetCockpitShape(Coords3D&	eyepos)
{
	ClassPtr	clsp = Persons2::PlayerSeenAC->classtype;
	ShapeNum	visShape;

	eyepos = reargunner_eyeoffset;								//RJS 27Mar00
	if (reargunner_active)
	{
		AircraftAnimData*	adptr = (AircraftAnimData*)Persons2::PlayerSeenAC->Anim;		
		SWord	angHdg;
		SWord	angPitch;

		visShape = clsp->gunnerpit[reargunner_cockpitindex].theShape;	//RJS 11Oct00
		View_Point->GetControlView(angHdg,angPitch);
		ClipGunner(angHdg,angPitch);

// Check to see if this station hasn't been taken over by a smoke trail...
		if ((adptr->weaponlaunchers[reargunner_index].LauncherType & LT_MASK) < LT_SMKTRAILS)	//RJS 21Aug00
		{
			Land_Scape.gunnerDead = false;

			adptr->weaponlaunchers[reargunner_index].hdg = angHdg;
			adptr->weaponlaunchers[reargunner_index].pitch = angPitch;
		}
		else
			Land_Scape.gunnerDead = true;

		eyepos = reargunner_eyeoffset;

#ifndef	NDEBUG
/*		char	thestring[255];
		sprintf(thestring,"%d   %d",int(angHdg),int(angPitch));

		OverLay.Diagnostic(thestring);*/
#endif
	}
	else
	{
//DEADCODE RJS 3/27/00 		eyepos.X = eyepos.Y = eyepos.Z = 0;
		visShape = clsp->cockpit1;
	}

	return visShape;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetTotalFuelLaunchers
//Author		Robert Slater
//Date			Mon 13 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::GetTotalFuelLaunchers(ShapeNum	theShape)
{
	SLong			total = 0;

	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(theShape);
	if (sdptr->LauncherDataSize)
	{
		UByteP			instr_ptr = (UByteP)sdptr + sdptr->LauncherDataSize;
		UWord			instruction;
		DOLAUNCHER_PTR	ptr;

		instruction = (UWord) *instr_ptr;
		while (instruction == dolauncherno)
		{
			instr_ptr++;

			ptr = (DOLAUNCHER_PTR)instr_ptr;
			if (ptr->lnchrtype == LT_INTFUEL)
				total++;

			instr_ptr += sizeof(DOLAUNCHER);
			instruction = (UWord) *instr_ptr;
		}
	}

	return total;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFuelPos
//Author		Robert Slater
//Date			Mon 13 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GetFuelPos(ItemPtr	itm,UWord index,Coords3D& pos,SLong launchtype)
{
	DOLAUNCHER_PTR	thislaunch = NULL;
	ShapeDescPtr	sdptr;
	UByte			thisscale = 0;
	SLong			count = 0;
	SLong			fuelcnt = 0;
	ShapeNum		theShape = itm->shape;

 	sdptr = SHAPESTUFF.GetShapePtr(theShape);
 	switch (SHAPESTUFF.GetShapeScale(sdptr))
 	{
 		case SHP_1CM:
 			thisscale = 0;
 			break;
 
 		case SHP_4CM:
 			thisscale = 2;
 			break;
 
 		case SHP_16CM:
 			thisscale = 4;
 			break;
 	}

	pos.X = 0;
	pos.Y = 0;
	pos.Z = 0;

	do
	{
		thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(theShape,count++);
		if (thislaunch)
		{
			if (thislaunch->lnchrtype == launchtype)
			{
				if (index == fuelcnt)
					break;
				else
					fuelcnt++;
			}
		}
	}
	while (thislaunch);

	LauncherToWorld(itm,(UByteP )thislaunch,thisscale,pos.X,pos.Y,pos.Z,NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDirectLauncherPos
//Author		Robert Slater
//Date			Tue 14 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GetDirectLauncherPos(ItemPtr	itm,UWord index,Coords3D& pos)
{
	DOLAUNCHER_PTR	thislaunch = NULL;
	ShapeDescPtr	sdptr;
	UByte			thisscale = 0;
	ShapeNum		theShape = itm->shape;

 	sdptr = SHAPESTUFF.GetShapePtr(theShape);
 	switch (SHAPESTUFF.GetShapeScale(sdptr))
 	{
 		case SHP_1CM:
 			thisscale = 0;
 			break;
 
 		case SHP_4CM:
 			thisscale = 2;
 			break;
 
 		case SHP_16CM:
 			thisscale = 4;
 			break;
 	}

	pos.X = 0;
	pos.Y = 0;
	pos.Z = 0;

	thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(theShape,index);

	LauncherToWorld(itm,(UByteP )thislaunch,thisscale,pos.X,pos.Y,pos.Z,NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShootFin
//Author		Robert Slater
//Date			Fri 17 Dec 1999
//
//Description	Fake a collision with the fin...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::ShootFin(AirStrucPtr ac, UByteP	animdata, bool	rightfin)
{
	if (reargunner_active)
	{
		UByte	oldstate = *animdata;
		if (oldstate < 255)
		{
			MoveGunAnimData*	adptr = (MoveGunAnimData*)ac->Anim;
// Need real gunner hdg&pitch
			UWord	gunhdg = adptr->weaponlaunchers[reargunner_index].hdg;		//RJS 13Mar00
			UWord	gunpitch = adptr->weaponlaunchers[reargunner_index].pitch;	//RJS 13Mar00
			UWord	hdgMin;
			UWord	hdgMax;
			UWord	pitch;
			if (rightfin)
			{
				hdgMin = ac->classtype->finrhdgmin;
				hdgMax = ac->classtype->finrhdgmax;
			}
			else
			{
				hdgMin = ac->classtype->finlhdgmin;
				hdgMax = ac->classtype->finlhdgmax;
			}
			pitch = ac->classtype->finpitch;

//fin positions assume ac is pointing north
//DeadCode RJS 13Mar00			gunhdg += UWord(ac->hdg);
//DeadCode RJS 13Mar00			gunpitch += UWord(ac->pitch);
			if (	(gunhdg > hdgMin)
				&&	(gunhdg < hdgMax)
				&&	(gunpitch > 0)
				&&	(gunpitch < pitch)
//DEADCODE CSB 14/01/00 				&&	(	(reargunner_launcher == LT_BTURRET)
//DEADCODE CSB 14/01/00 				 	||	(reargunner_launcher == LT_RREARTOP))
				&&	(	(reargunner_launcher == LT_RAF_TURRET)
				 	||	(reargunner_launcher == LT_LUF_REARTOP))
				&&	(Math_Lib.rnd() < 1024) )
			{
				UWord	newstate = oldstate + 8;
				if (newstate > 255)	newstate = 255;

				ForceDamage(ac,ac,animdata,BitStates(newstate));
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MostDamagedGroupItemAnim
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
SLong	shape::MostDamagedGroupItemAnim(animptr& adptr, ShapeNum& shape, Coords3D& position)
{
	ShapeDescPtr		sdptr;
	SLong				chosenindex = -2;

	sdptr = SHAPESTUFF.GetShapePtr(shape);
	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
	{
		UByteP		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		UWord		instruction;
		DOGROUP_PTR temp;
		SLong		count = 0;
		SLong		damindex;
		SLong		totdamage,maxdamage,flagend;
		MinAnimData*	mad;
		DOGROUP_PTR	chosenptr = NULL;
		static SLong		grplist[64];
		static DOGROUP_PTR	ptrlist[64];
		static animptr		adptrlist[64];
		animptr				tmpadptr = adptr;							//CSB 25/05/00

		SLong		totcnt = 0;

		chosenindex = -1;

		maxdamage = -1;

		forever
		{
			instruction = (UWord )*instr_ptr;
			instr_ptr ++;

			if (instruction != dogroupno)
				break;

			temp = (DOGROUP_PTR)instr_ptr;
				
			shape = (ShapeNum)temp->shapenum;
			mad = (MinAnimData*)tmpadptr;
			if (	!mad->IsInvisible
				&&	(mad->itemstate != DEAD)	)
			{
				sdptr = SHAPESTUFF.GetShapePtr(shape);
				damindex = sdptr->DamageOffset;
				if (damindex)
				{
					grplist[totcnt] = count;
					ptrlist[totcnt] = temp;
					adptrlist[totcnt] = tmpadptr;

// We don't want to remember the leader...
// ...but if all other elements are dead, then this slot is still filled.
// Result is that the leader will always die last.
					if (count > 1)			
						totcnt++;

					flagend = SHAPE.GetAnimDataSize(shape);

					totdamage = 0;

					for (int k=damindex;k<flagend;k++)
						totdamage+=tmpadptr[k];							//RJS 16Nov00

					if (totdamage > maxdamage)
					{
						maxdamage = totdamage;
						chosenindex = count;
						chosenptr = temp;
						adptr = tmpadptr;
					}
				}
			}

			tmpadptr += GetElementAnimOffset(shape);

			instr_ptr += sizeof(DOGROUP);
			count++;
		}

		if (chosenptr)
		{
			SLong	randno = Math_Lib.rnd();
			SLong	random_shift = 12;									//RJS 16Nov00
			SLong	random_chance = 4096;								//RJS 16Nov00

			if (	(chosenindex == 1)		// this is the Leader
				&&	(totcnt > 0)	)		// we have more than the Leader
			{
				random_shift = 16;
				random_chance = 65536;
			}

			if (randno < random_chance)									//RJS 16Nov00
			{
// if totcnt == 0 (i.e. the only one left is Leader), then he still gets picked...
				randno = (totcnt*randno)>>random_shift;					//RJS 16Nov00
				chosenindex = grplist[randno];
				chosenptr = ptrlist[randno];
				adptr = adptrlist[randno];
			}

			position.X = chosenptr->xoffset;
			position.Y = chosenptr->yoffset;
			position.Z = chosenptr->zoffset;
		}
	}

	return chosenindex;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DetachUnwantedVapourStreams
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
SLong	shape::DetachUnwantedVapourStreams(itemptr	itm)
{
	MinAnimData*		aptr = (MinAnimData*) itm->Anim;
	UWord				noLaunchers;
	ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(itm->shape);
	SLong				newlife = 0;

	if (	(SHAPESTUFF.GetShapeScale(sdptr) != SHP_GRP)
		&&	(sdptr->Type.VapourType != TRAIL_OFF)		)
	{
		noLaunchers = aptr->nolaunchers;
		if (noLaunchers)				
		{
			int					index;
			WeapAnimData*		weapon;
			MoveGunAnimData*	adptr = (MoveGunAnimData*) itm->Anim;

			// Don't kill the last one, as this one is inherited...
			if (noLaunchers == MAX_WEAP_LAUNCHERS)
				noLaunchers--;

			pTrailItm = itm;

			for (index=0; index < noLaunchers; index++)
			{
				weapon = &adptr->weaponlaunchers[index];
				if (weapon && weapon->hdg)
				{
					if ((weapon->LauncherType & LT_MASK) == LT_SMKTRAILS)
					{
						newlife = DetatchVapourStream(weapon->hdg,500,false);
						if (newlife==0)
						{
							//if transient death, alert transite...
							if (weapon->hdg < 0)
								newlife = -1;	

							weapon->hdg = 0;	
						}
					}
				}
			}
		}
	}

	return(newlife);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SafestPlace
//Author		Robert Slater
//Date			Mon 10 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	shape::SafestPlace(ItemPtr	tmpitem, ItemPtr blokeitem, Coords3D& position)
{
	ShapeDescPtr	sdptr;
	bool			foundone = false;
	Coords3D		currloc = blokeitem->World;
	ShapeNum		theShape;
	SLong			biggestsize;
	animptr			adptr;
	MinAnimData*	mad;
	bool			trythis;
	DOGROUP_PTR 	temp;
	SLong			deltax,deltaz;
	ULong			nearest,squared;

	sdptr = SHAPESTUFF.GetShapePtr(blokeitem->shape);
	biggestsize = sdptr->Size;

	nearest = 0xFFFFFFFF;

	while (tmpitem)
	{
		if (	(tmpitem->Status.size < MOVINGSIZE)						//RJS 24May00
			&&	(tmpitem->uniqueID.count != RunwaySBAND)
			&&	(tmpitem->uniqueID.count != RunwayEBAND)	)
		{
			adptr = tmpitem->Anim;
			sdptr = SHAPESTUFF.GetShapePtr(tmpitem->shape);
			if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
			{
				UByteP			instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
				UWord			instruction;

				forever
				{
					instruction = (UWord )*instr_ptr;
					instr_ptr ++;

					if (instruction != dogroupno)
						break;

					temp = (DOGROUP_PTR)instr_ptr;
					
					theShape = (ShapeNum)temp->shapenum;
					mad = (MinAnimData*)adptr;
					if (	!mad->IsInvisible
						&&	(mad->itemstate == ALIVE)	)
					{
						sdptr = SHAPESTUFF.GetShapePtr(theShape);							
						if (sdptr->Size >= biggestsize)
						{
							biggestsize = sdptr->Size;

							deltax = tmpitem->World.X + temp->xoffset - blokeitem->World.X;
							deltaz = tmpitem->World.Z + temp->zoffset - blokeitem->World.Z;

							squared = ULong((deltax*deltax)+(deltaz*deltaz));
							if (squared < nearest)
							{
								nearest = squared;
							
								foundone = true;

								position.X = tmpitem->World.X + temp->xoffset;
								position.Y = tmpitem->World.Y + temp->yoffset;
								position.Z = tmpitem->World.Z + temp->zoffset;
							}
						}
					}

					adptr += GetElementAnimOffset(theShape);
					instr_ptr += sizeof(DOGROUP);
				}
			}
			else
			{
				mad = (MinAnimData*)adptr;
				if (	!mad->IsInvisible
					&&	(mad->itemstate == ALIVE)	
					&&	(sdptr->Size >= biggestsize)	)
				{
					biggestsize = sdptr->Size;

					deltax = tmpitem->World.X - blokeitem->World.X;
					deltaz = tmpitem->World.Z - blokeitem->World.Z;

					squared = ULong((deltax*deltax)+(deltaz*deltaz));
					if (squared < nearest)
					{
						nearest = squared;
				
						foundone = true;

						position.X = tmpitem->World.X;
						position.Y = tmpitem->World.Y;
						position.Z = tmpitem->World.Z;
					}
				}
			}
		}

		tmpitem = tmpitem->Next;
	}

	return foundone;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckForDamage
//Author		Robert Slater
//Date			Mon 10 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	shape::CheckForDamage(ItemPtr	tmpitem, Coords3D&	pos)
{
	ShapeDescPtr	sdptr;
	bool			foundone = false;
	ShapeNum		theShape;
	animptr			adptr;
	MinAnimData*	mad;
	DOGROUP_PTR 	temp;
	SLong			deltax,deltaz,distance;
	SLong			nearest;
	WorldStuff*		worldptr = mobileitem::currworld;
	UWord			uniqueid = tmpitem->SGT;
	ItemPtr			firstitem;
	MinAnimData*	foundMAD=NULL;
	SLong			trucksize = SHAPESTUFF.GetShapePtr(tmpitem->shape)->Size<<5;//double
	SLong			elementsize;


	nearest = 10000;			//this is as far as it goes...

	firstitem = worldptr->getfirstitem(worldptr->GetSector(tmpitem));
	while (firstitem)
	{
		if (	(firstitem != tmpitem)
			&&	(firstitem->SGT == uniqueid)
			&&	(firstitem->Status.size < MOVINGSIZE)					//RJS 24May00
			&&	(firstitem->uniqueID.count != RunwaySBAND)
			&&	(firstitem->uniqueID.count != RunwayEBAND)	)
		{
			adptr = firstitem->Anim;								//RJS 25Feb00
			sdptr = SHAPESTUFF.GetShapePtr(firstitem->shape);
			if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
			{
				UByteP			instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
				UWord			instruction;

				forever
				{
					instruction = (UWord )*instr_ptr;
					instr_ptr ++;

					if (instruction != dogroupno)
						break;

					temp = (DOGROUP_PTR)instr_ptr;
					
					theShape = (ShapeNum)temp->shapenum;
					mad = (MinAnimData*)adptr;
					if (	!mad->IsInvisible
						&&	!mad->repair		)
					{
						elementsize = SHAPESTUFF.GetShapePtr(theShape)->Size<<5;//double size
						if (elementsize > trucksize)
						{
							deltax = firstitem->World.X + temp->xoffset - tmpitem->World.X;
							deltaz = firstitem->World.Z + temp->zoffset - tmpitem->World.Z;

							fastMath.FloatToInt(&distance,fastMath.FastSqrt(float((deltax*deltax)+(deltaz*deltaz))));
							distance -= elementsize;
							distance=distance<0?-distance:distance;
							if (distance < nearest)
							{
								pos.X = firstitem->World.X + temp->xoffset;
								pos.Z = firstitem->World.Z + temp->zoffset;
								nearest = distance;
								foundMAD = mad;						//RJS 25Feb00
							}
						}
					}

					adptr += GetElementAnimOffset(theShape);
					instr_ptr += sizeof(DOGROUP);
				}
			}
			else
			{
				mad = (MinAnimData*)adptr;
				if (	!mad->IsInvisible
					&&	!mad->repair		)
				{
					elementsize = sdptr->Size<<5;//double size
					if (elementsize > trucksize)
					{
						deltax = firstitem->World.X - tmpitem->World.X;
						deltaz = firstitem->World.Z - tmpitem->World.Z;

						fastMath.FloatToInt(&distance,fastMath.FastSqrt(float((deltax*deltax)+(deltaz*deltaz))));
						distance -= elementsize;
						distance=distance<0?-distance:distance;
						if (distance < nearest)
						{
							pos.X = firstitem->World.X;
							pos.Z = firstitem->World.Z;
							nearest = distance;
							foundMAD = mad;							//RJS 25Feb00
						}
					}
				}
			}
		}
		firstitem = firstitem->Next;
	}

	if (foundMAD && (foundMAD->itemstate != ALIVE))				//RJS 25Feb00
	{
//DeadCode RJS 19Oct00 		foundMAD->repair = 1;
		foundone = true;
	}

	return foundone;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoDrawTrail
//Author		Robert Slater
//Date			Wed 9 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::DoDrawTrail(	UByteP				instr_ptr,
							Coords3DList*		currpoint,
							MyGroundVectorPtr	WCylStartP,
							MyGroundVectorPtr	WCylEndP,
							SLong				fadedepth,
							SLong				dist0,
							SLong				dist1,
							SLong				oldrad	)
{
	DOSMKTRAIL_PTR	ptr = (DOSMKTRAIL_PTR) instr_ptr;
	UByteP			tmpinstptr;
	SLong			radius;
//DeadCode RJS 20Oct00 	SWord			xoff0=0;
//DeadCode RJS 20Oct00 	SWord			yoff0=0;
//DeadCode RJS 20Oct00 	SWord			xoff1=0;
//DeadCode RJS 20Oct00 	SWord			yoff1=0;
	SLong			dx, dy, dz;
	SWord			MaxRadius, Degrade;
 	SWord			ThisDepth = (ptr->MaxTransparency * 255)>>2;
	UWord			FrameNo;
	SWord			minx, miny;
	SWord			MaxDepth = 64;
	ImageMapNumber	theImap;
	ImageMapNumber	theImap2;
	SWord			minx2,miny2,maxx2,maxy2;
	SWord			realfade = fadedepth;
	SLong			fadetime;
	SLong			lifegone;
//DeadCode RJS 20Oct00 	SWord			oldGlobalAlpha = -1;
	UWord			noframes = ptr->noframes - 1;
//DeadCode RJS 20Oct00 	Bool			nocyl = FALSE;
	SLong			realdist;
	SLong			linelength;

	radius = currpoint->radius;
	fadetime = currpoint->LifeTime - currpoint->FadeTime;
 	if (radius && (fadetime > 0))
	{
		lifegone = currpoint->LifeTime - currpoint->lifeleft;
 		if (lifegone > currpoint->FadeTime)
 		{
 			lifegone -= currpoint->FadeTime;
 			if (lifegone<0) lifegone=0;
 			realfade = (lifegone * fadedepth)/fadetime;
 			realfade = fadedepth - realfade;
 			if (realfade < 0)
 				realfade = 0;

 			if (realfade > 255)
 				realfade = 255;

 			ThisDepth = realfade;

 			FrameNo = noframes*lifegone;
 			FrameNo /= fadetime;
 		}
 		else
 		{
 			if (lifegone < 0)
 				lifegone=0;	 

 			ThisDepth = fadedepth;
 			if (ptr->frametime)
 			{
 				UWord	framepoo = lifegone / ptr->frametime;
 				ULong	frametot = framepoo * ptr->frametime;

 				FrameNo = ((lifegone - frametot)*noframes)/ptr->frametime;
 			}
 			else
 				FrameNo = 0;
 		}

 		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,ThisDepth);

		realdist = (dist0 + dist1)>>1;
 		if (realdist < ptr->FadeDist)
 		{
			SLong		linelength;
			SLong		avdiameter = oldrad + radius;
			SLong		pixpercyl;
			Float		fdx, fdy, fdz;
			D3DVALUE	fLineLength;
			D3DVALUE	v1x,v0x;
			D3DVALUE	v1y,v0y;
			D3DVALUE	v1z,v0z;

			newco[1].getPosition(v1x,v1y,v1z);
			newco[0].getPosition(v0x,v0y,v0z);

			fdx = v1x-v0x;										//RJS 19May00
			fdy = v1y-v0y;										//RJS 19May00
			fdz = v1z-v0z;										//RJS 19May00

			fLineLength = fastMath.FastSqrt(D3DVALUE((fdx*fdx)+(fdy*fdy)+(fdz*fdz)));
			fastMath.FloatToInt(&linelength,fLineLength);

			Smoke_Trails.SetVisibility(fdx,fdy,fdz,fLineLength);

			pixpercyl = linelength / avdiameter;
 			
			minx = 0;
 			miny = 0;

 			theImap = (ImageMapNumber) ptr->Imagemap;
 			theImap2 = (ImageMapNumber) ptr->Imagemap2;
 			if (theImap)
 			{
 				ImageMapDescPtr imptr;
 				SLong			nofx;
 				SLong			stepy, stepx;

 				if (theImap2)
 				{
 					imptr = Image_Map.GetImageMapPtr(theImap2);

 					nofx = imptr->w / ptr->width2;
 					stepy = FrameNo / nofx;
 					stepx = FrameNo - (stepy*nofx);

 					minx2 = ptr->minix2;
 					miny2 = ptr->miniy2;

 					minx2 += stepx*ptr->width2;
 					miny2 += stepy*ptr->height2;

 					maxx2 = minx2 + ptr->width2;
 					maxy2 = miny2 + ptr->height2;
 				}

 				if (ptr->framelimit && (FrameNo >= ptr->framelimit))
 				{
 					SWord	framefrac = FrameNo / ptr->framelimit;
 					SWord	framestep = framefrac * ptr->framelimit;

 					FrameNo -= framestep;

 					minx = 0;
 					miny = 0;

 					theImap = (ImageMapNumber) (ptr->Imagemap + framefrac);
 				}
 				else
 				{
 					minx = ptr->MinIx;
 					miny = ptr->MinIy;
 				}

 				imptr = Image_Map.GetImageMapPtr(theImap);

 				nofx = imptr->w / ptr->Width;
 				stepy = FrameNo / nofx;
 				stepx = FrameNo - (stepy*nofx);

 				minx += stepx*ptr->Width;
 				miny += stepy*ptr->Height;
 			}

			Smoke_Trails.imagemap0 = theImap;
			Smoke_Trails.imagemap1 = theImap2;
			Smoke_Trails.minix0 = minx;
			Smoke_Trails.miniy0 = miny;
			Smoke_Trails.maxix0 = minx + ptr->Width;
			Smoke_Trails.maxiy0 = miny + ptr->Height;
			Smoke_Trails.minix1 = minx2;
			Smoke_Trails.miniy1 = miny2;
			Smoke_Trails.maxix1 = maxx2;
			Smoke_Trails.maxiy1 = maxy2;
			Smoke_Trails.fadedepth = ThisDepth;
			Smoke_Trails.oldradius = oldrad;
			Smoke_Trails.radius = radius;
			Smoke_Trails.distance = realdist;
			Smoke_Trails.traillength = linelength;
			Smoke_Trails.WCylStartP = WCylStartP;
			Smoke_Trails.WCylEndP = WCylEndP;
			Smoke_Trails.dist0 = dist0;
			Smoke_Trails.dist1 = dist1;
			Smoke_Trails.vertex0 = 0;
			Smoke_Trails.vertex1 = 1;

			Smoke_Trails.CalcCylinder();

 			switch (ptr->TrailType)
 			{
 				case SMK_SCATTER:
 				{
 					MaxRadius = (7*oldrad)>>3;

// 					pixpercyl = (avdist * avrad)>>5;
// 					pixpercyl += 8;

  					if (pixpercyl > MaxDepth)
  						pixpercyl = MaxDepth;

 					pixpercyl = (pixpercyl * ThisDepth)/100;
 					pixpercyl = (pixpercyl*ptr->Density)>>7;

					Smoke_Trails.pixpercyl = pixpercyl;
					Smoke_Trails.maxradius = MaxRadius;
					
					Smoke_Trails.CheckNearest();
 					Smoke_Trails.ParticleCylinderImapd();
 				}
 				break;
 				case SMK_STREAM:
 				{
 					SLong	realdist2 = (realdist << 7) / 7500;
 					if (realdist2 <= 0)
 						realdist2 = 128;

 					if (realdist2 > 65535)
 						realdist2 = 65535;

					Smoke_Trails.distance = realdist2;

					Smoke_Trails.CheckNearest();
 					Smoke_Trails.ParticleStreamImapd();
 				}
 				break;
 				case SMK_HEAVY_STREAM:
 				{
 					if (realdist < 6000)
 					{
 						MaxRadius = (7*oldrad)>>3;

 						pixpercyl = ThisDepth * ptr->Density;

						Smoke_Trails.pixpercyl = pixpercyl;
						Smoke_Trails.maxradius = MaxRadius;

						Smoke_Trails.CheckNearest();
 	 					Smoke_Trails.ParticleCylinderImapd();
 					}
 					else
 						Smoke_Trails.imaptrailcylWrapped();
 				}
 				break;
 				case SMK_LINES:
 				break;
 				case SMK_FISHPOO:
 				{
 					Smoke_Trails.imaptrailcylWrapped();
 				}
 				break;
 				case SMK_TRACER:
 				break;
 				case SMK_ENGINEFIRE:
 				{
 					if (realdist < 6000)
 					{
 						MaxRadius = (7*oldrad)>>3;

 						pixpercyl = ThisDepth * ptr->Density;

						Smoke_Trails.pixpercyl = pixpercyl;
						Smoke_Trails.maxradius = MaxRadius;

						Smoke_Trails.minix0 = minx2;
						Smoke_Trails.miniy0 = miny2;
						Smoke_Trails.maxix0 = maxx2;
						Smoke_Trails.maxiy0 = maxy2;

						Smoke_Trails.minix1 = Smoke_Trails.miniy1 = 0;
						Smoke_Trails.maxix1 = Smoke_Trails.maxiy1 = 64;

						Smoke_Trails.imagemap0 = Smoke_Trails.imagemap1;

						Smoke_Trails.CheckNearest();
 						if (currpoint->isFirst)
 	 						Smoke_Trails.DblParticleCylinderImapd();
 						else
 							Smoke_Trails.ParticleCylinderImapd();
 					}
 					else
					{
						Smoke_Trails.miniy0 = miny;
						Smoke_Trails.maxiy0 = miny+ptr->Height;

 						Smoke_Trails.imaptrailcylWrapped();
					}
 				}
 				break;
 				case SMK_CONTRAIL:
 				{
 					if (realdist < 6000)
 					{
 						MaxRadius = (7*oldrad)>>3;

 						pixpercyl = ThisDepth * ptr->Density;

						Smoke_Trails.pixpercyl = pixpercyl;

						Smoke_Trails.maxradius = MaxRadius;
						Smoke_Trails.minix0 = minx2;
						Smoke_Trails.miniy0 = miny2;
						Smoke_Trails.maxix0 = maxx2;
						Smoke_Trails.maxiy0 = maxy2;
				
						Smoke_Trails.CheckNearest();
 						if (currpoint->isFirst)
 	 						Smoke_Trails.FadeParticleCylinderImapd();
 						else
 							Smoke_Trails.ParticleCylinderImapd();
 					}
 					else
					{
						Smoke_Trails.miniy0 = miny;
						Smoke_Trails.maxiy0 = miny+ptr->Height;

 						Smoke_Trails.imaptrailcylWrapped();
					}
 				}
 				break;
 			}

			Smoke_Trails.Restore();
 		}
 		else
 		{
 			if (ptr->Colour)
 			{
 				DOLINE	tmpinst2;
 				DOSETCOLOUR256	tmpinst3;

 				tmpinst3.basecolour = ptr->Colour<<1;
 				tmpinst3.spread = 0;				 
 				tmpinst3.imap = 0xFF;

 				tmpinstptr = (UByteP) &tmpinst3;
 				dosetcolour256(tmpinstptr);		
 												
 				tmpinst2.start_vertex = 0;		
 				tmpinst2.end_vertex = 1;		
 												
 				tmpinstptr = (UByteP) &tmpinst2;

 				doline(tmpinstptr);

				Smoke_Trails.DuffButNecessary();						//RJS 9Aug00
 			}					   
 		}

		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,SMOKED_OFF);
 	}
}

Bool	shape::ClipCylinder(DoPointStruc	&dp0,
							DoPointStruc	&dp1,
							DoPointStruc	&dp2,
							DoPointStruc	&dp3,
							SLong			xRadius,
							SLong			yRadius	)
{
//Old_Code RJS 08Feb00 	Bool	Clipped = TRUE;
//Old_Code RJS 08Feb00 	Float	xRad = Float(xRadius);
//Old_Code RJS 08Feb00 	Float	yRad = Float(yRadius);
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 	xRad *= SphereXScale;
//Old_Code RJS 08Feb00 	yRad *= SphereYScale;
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 	dp0.bodyx.f += xRad;						
//Old_Code RJS 08Feb00 	dp0.bodyy.f += yRad;						
//Old_Code RJS 08Feb00 																
//Old_Code RJS 08Feb00 	dp1.bodyx.f -= xRad;						
//Old_Code RJS 08Feb00 	dp1.bodyy.f -= yRad;						
//Old_Code RJS 08Feb00 																
//Old_Code RJS 08Feb00 	dp2.bodyx.f -= xRad;						
//Old_Code RJS 08Feb00 	dp2.bodyy.f -= yRad;						
//Old_Code RJS 08Feb00 																
//Old_Code RJS 08Feb00 	dp3.bodyx.f += xRad;						
//Old_Code RJS 08Feb00 	dp3.bodyy.f += yRad;						
//Old_Code RJS 08Feb00 																
//Old_Code RJS 08Feb00 	_matrix.SetClipFlags(dp0);
//Old_Code RJS 08Feb00 	_matrix.SetClipFlags(dp1);
//Old_Code RJS 08Feb00 	_matrix.SetClipFlags(dp2);
//Old_Code RJS 08Feb00 	_matrix.SetClipFlags(dp3);
//Old_Code RJS 08Feb00 
//Old_Code RJS 08Feb00 	andedFlags=CF3D_ALL;
//Old_Code RJS 08Feb00 	andedFlags&=dp0.clipFlags;
//Old_Code RJS 08Feb00 	andedFlags&=dp1.clipFlags;
//Old_Code RJS 08Feb00 	andedFlags&=dp2.clipFlags;
//Old_Code RJS 08Feb00 	andedFlags&=dp3.clipFlags;
//Old_Code RJS 08Feb00 	if (andedFlags==0)
//Old_Code RJS 08Feb00 	{
//Old_Code RJS 08Feb00 		Clipped = FALSE;
//Old_Code RJS 08Feb00 		if (!doingHW3D)
//Old_Code RJS 08Feb00 		{
//Old_Code RJS 08Feb00 			_matrix.body2screen(dp0);
//Old_Code RJS 08Feb00 			_matrix.body2screen(dp1);
//Old_Code RJS 08Feb00 			_matrix.body2screen(dp2);
//Old_Code RJS 08Feb00 			_matrix.body2screen(dp3);
//Old_Code RJS 08Feb00 		}
//Old_Code RJS 08Feb00 	}

	Bool	Clipped = TRUE;
//DEADCODE RDH 5/19/00 	Float	xRad = Float(xRadius);
//DEADCODE RDH 5/19/00 	Float	yRad = Float(yRadius);
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 //	xRad *= SphereXScale;
//DEADCODE RDH 5/19/00 //	yRad *= SphereYScale;
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 	dp0.bodyx.f += xRad;						
//DEADCODE RDH 5/19/00 	dp0.bodyy.f += yRad;						
//DEADCODE RDH 5/19/00 																
//DEADCODE RDH 5/19/00 	dp1.bodyx.f -= xRad;						
//DEADCODE RDH 5/19/00 	dp1.bodyy.f -= yRad;						
//DEADCODE RDH 5/19/00 																
//DEADCODE RDH 5/19/00 	dp2.bodyx.f -= xRad;						
//DEADCODE RDH 5/19/00 	dp2.bodyy.f -= yRad;						
//DEADCODE RDH 5/19/00 																
//DEADCODE RDH 5/19/00 	dp3.bodyx.f += xRad;						
//DEADCODE RDH 5/19/00 	dp3.bodyy.f += yRad;						
																
	return(Clipped);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLauncherPoint
//Author		Robert Slater
//Date			Tue 22 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	shape::GetLauncherPoint(ItemPtr	itm, SLong& index, SLong ltype, Coords3D& pos, SLong& xoffset)
{
	ShapeNum		theShape = itm->shape;
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(theShape);
	SLong			thisscale = -1;
	DOLAUNCHER_PTR	thislaunch;
	bool			retval = false;

	pos = itm->World;												//RJS 10Mar00

	switch (SHAPESTUFF.GetShapeScale(sdptr))
	{
	case SHP_GRP:
		break;
	case SHP_1CM:
		thisscale = 0;
		break;
	case SHP_4CM:
		thisscale = 2;
		break;
	case SHP_16CM:
		thisscale = 4;
		break;
	}

	if (thisscale > -1)
	{
		do
		{
			thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(theShape,index++);
			if (thislaunch && (thislaunch->lnchrtype==ltype))
			{
				xoffset = thislaunch->posx;
				LauncherToWorld(itm,(UByteP) thislaunch,thisscale,pos.X,pos.Y,pos.Z,NULL);
				retval = true;
				break;
			}
		}
		while (thislaunch);
	}

	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SufficientDamage
//Author		Robert Slater
//Date			Wed 23 Feb 2000
//
//Description	If groupptr==null, then wasn't a group, so always valuable
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	shape::SufficientDamage(const ItemPtr itm, void*	groupptr)
{
	bool	retval = true;
	if (groupptr)
	{
		DOGROUP_PTR	ptr = (DOGROUP_PTR)groupptr;

		if (ptr->element_number < 50)	//importance < 20%
			retval = false;
	}
	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetEyePoint
//Author		Robert Slater
//Date			Fri 10 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GetEyePointAndHdg(ItemPtr	itm, Coords3D&	pos)
{
	SLong			searchindex = -1;
	SLong			index = 0;
	ShapeNum		theShape = itm->shape;
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(theShape);
	SLong			thisscale = -1;
	DOLAUNCHER_PTR	thislaunch;

	pos = itm->World;

	reargunner_eyeoffset.X = 0;
	reargunner_eyeoffset.Y = 0;
	reargunner_eyeoffset.Z = 0;

	switch (SHAPESTUFF.GetShapeScale(sdptr))
	{
	case SHP_GRP:
		break;
	case SHP_1CM:
		thisscale = 0;
		break;
	case SHP_4CM:
		thisscale = 2;
		break;
	case SHP_16CM:
		thisscale = 4;
		break;
	}

	if (thisscale > -1)
	{
		do
		{
			thislaunch = (DOLAUNCHER_PTR) GetLauncherPos(theShape,index++);
			if (	thislaunch
				&&	(thislaunch->lnchrtype==CT_EYE)	)
			{
				searchindex++;
				if (searchindex == reargunner_cockpitindex)
				{
//DeadCode RJS 12Oct00 					hdg = thislaunch->hdg << 8;
					thisscale += 10;		// scale up by 1024

// Buffet Eye Deltas are scaled up by 1024

					pos.X = buffetData.delta.X + (thislaunch->posx << thisscale);
					pos.Y = buffetData.delta.Y + (thislaunch->posy << thisscale);
					pos.Z = buffetData.delta.Z + (thislaunch->posz << thisscale);

					if (reargunner_active)
					{
						Coords3D	pivot;
						MoveGunAnimData*	adptr = (MoveGunAnimData*)itm->Anim;
						ANGLES		weaphdg,weappitch;
						D3DVECTOR	ori;
						SLong		tmpx,tmpy,tmpz;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						SWord	angHdg, angPitch, hdg, pitch;			//RJS 12Oct00

						hdg = Persons2::PlayerSeenAC->classtype->gunnerpit[reargunner_cockpitindex].eyeHdg;	//RJS 12Oct00
  						pitch = Persons2::PlayerSeenAC->classtype->gunnerpit[reargunner_cockpitindex].eyePitch;	//RJS 12Oct00

						View_Point->GetControlViewNewEye(hdg,pitch,angHdg,angPitch);

						ClipGunner(angHdg,angPitch);

// Check to see if this station hasn't been taken over by a smoke trail...
						if ((adptr->weaponlaunchers[reargunner_index].LauncherType & LT_MASK) < LT_SMKTRAILS)	//RJS 21Aug00
						{
							adptr->weaponlaunchers[reargunner_index].hdg = angHdg;
							adptr->weaponlaunchers[reargunner_index].pitch = angPitch;
						}

#ifndef	NDEBUG
//						char	boff[256];
//						sprintf(boff,"%d   %d",angHdg,angPitch);
//						OverLay.Diagnostic(boff);
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
//DeadCode RJS 27Mar00 						thisscale += 10;		// scale up by 1024

						weaphdg = Angles(adptr->weaponlaunchers[reargunner_index].hdg + hdg);//RJS 08May00
 						if (UWord(hdg) > ANGLES_90Deg)							//RJS 12Oct00
 							weappitch = Angles(-adptr->weaponlaunchers[reargunner_index].pitch);	//RJS 12Oct00
 						else
							weappitch = Angles(adptr->weaponlaunchers[reargunner_index].pitch);	//RJS 12Oct00

						pivot.X = reargunner_pivotx << thisscale;
						pivot.Y = reargunner_pivoty << thisscale;
						pivot.Z = reargunner_pivotz << thisscale;

//DeadCode RJS 27Mar00 						pos.X = tmpx = thislaunch->posx << thisscale;
//DeadCode RJS 27Mar00 						pos.Y = tmpy = thislaunch->posy << thisscale;
//DeadCode RJS 27Mar00 						pos.Z = tmpz = thislaunch->posz << thisscale;
						tmpx = pos.X;
						tmpy = pos.Y;
						tmpz = pos.Z;

						MovePointWRTGun(weaphdg,weappitch,pivot,pos,ori);

						reargunner_eyeoffset = pos;
						reargunner_eyeoffset.X -= tmpx;
						reargunner_eyeoffset.Y -= tmpy;
						reargunner_eyeoffset.Z -= tmpz;

						LauncherToWorld(itm,pos);

						pos.X >>= 10;
						pos.Y >>= 10;
						pos.Z >>= 10;

						pos.X += itm->World.X;
						pos.Y += itm->World.Y;
						pos.Z += itm->World.Z;
					}
					else
					{
//DeadCode RJS 27Mar00 						LauncherToWorld(itm,(UByteP) thislaunch,thisscale,pos.X,pos.Y,pos.Z,NULL);
						LauncherToWorld(itm,pos);

						pos.X >>= 10;
						pos.Y >>= 10;
						pos.Z >>= 10;

						pos.X += itm->World.X;
						pos.Y += itm->World.Y;
						pos.Z += itm->World.Z;

						reargunner_eyeoffset = buffetData.delta;		//RJS 25Aug00
					}

					break;
				}
			}
		}
		while (thislaunch);
	}
}

void	shape::ClipGunner(SWord&	angHdg, SWord&	angPitch)
{
	SWord	fiddle_arcHdg = gunner_arcHdg - ANGLES_5Deg;				//RJS 16Aug00
	SWord	fiddle_arcPitch = gunner_arcPitch - ANGLES_5Deg;			//RJS 16Aug00
	SWord	maxHdg = gunner_minHdg + fiddle_arcHdg;						//RJS 16Aug00
	SWord	maxPitch = gunner_minPitch + fiddle_arcPitch;				//RJS 16Aug00
	SLong	absarc;

// Hdg Clip...
	if (angHdg < 0)
	{
// -'ve quadrant
		absarc = SLong(UWord(angHdg) - UWord(gunner_minHdg));
		if (absarc > fiddle_arcHdg)
			angHdg = maxHdg;
		else
		{
			if (absarc < 0)
				angHdg = gunner_minHdg;
		}
	}
	else
	{
// +'ve quadrant
		absarc = angHdg - gunner_minHdg;
		if (absarc > fiddle_arcHdg)
			angHdg = maxHdg;
		else
		{
			if (absarc < 0)
				angHdg = gunner_minHdg;
		}
	}

// Pitch Clip...
	if (angPitch < 0)
	{
// -'ve quadrant
		absarc = SLong(UWord(angPitch) - UWord(gunner_minPitch));
		if (absarc > fiddle_arcPitch)
			angPitch = maxPitch;
		else
		{
			if (absarc < 0)
				angPitch = gunner_minPitch;
		}
	}
	else
	{
// +'ve quadrant
		absarc = angPitch - gunner_minPitch;
		if (absarc > fiddle_arcPitch)
			angPitch = maxPitch;
		else
		{
			if (absarc < 0)
				angPitch = gunner_minPitch;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WeaponToWorld
//Author		Robert Slater
//Date			Mon 13 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::WeaponToWorld(	itemptr		itm,
								void*		weapptr,
								void*		position,
								UByte		thisscale,
								SLong& 		xpos,
								SLong& 		ypos,
								SLong& 		zpos,
								MyGroundVectorPtr	goffset	)
{
	DOLAUNCHER_PTR		thislaunch = (DOLAUNCHER_PTR) position;
	WeapAnimData*		weapon = (WeapAnimData*)weapptr;

	if (weapon && thislaunch)
	{
		MoveGunAnimData* adptr = (MoveGunAnimData*)itm->Anim;
		ANGLES		weaphdg;
		ANGLES		weappitch;
//DeadCode RJS 20Oct00 		bool		usemodel = false;
		bool		swivelgun = false;
		Coords3D	theGunPoint;										//RJS 26Sep00

		theGunPoint.X = thislaunch->posx << thisscale;					//RJS 26Sep00
		theGunPoint.Y = thislaunch->posy << thisscale;					//RJS 26Sep00
		theGunPoint.Z = thislaunch->posz << thisscale;					//RJS 26Sep00

		if (	(itm == Persons2::PlayerSeenAC)
			&&	reargunner_active
			&&	(weapon == &adptr->weaponlaunchers[reargunner_index])	)
			swivelgun = true;
		else
		{
			if ((weapon->LauncherType & LT_MASK) == LT_MOVEGUN)
				swivelgun = true;
		}

		if (swivelgun)
		{
// The gun will point in a specific direction...
			Coords3D	thePivot;
			D3DVECTOR	gunori;

			thePivot.X = thislaunch->pivotx << thisscale;			
			thePivot.Y = thislaunch->pivoty << thisscale;		
			thePivot.Z = thislaunch->pivotz << thisscale;

			weaphdg = Angles(weapon->hdg);
			weappitch = Angles(weapon->pitch);

			MovePointWRTGun(weaphdg,weappitch,thePivot,theGunPoint,gunori);	//RJS 26Sep00

			if (itm == Persons2::PlayerSeenAC)
				((AirStrucPtr)itm)->fly.pModel->SetGunOri(gunori.x,gunori.y,gunori.z);
		}
		else
		{
// The gun will point in the direction of the aircraft...
			weapon->hdg = 0;					//RJS 12May00
			weapon->pitch = 0;					//RJS 12May00
		}

#ifdef	_BOMBBUG_
		if ((weapon->LauncherType & LT_MASK)==LT_BOMB)
			::AfxTrace("%d,%d,%d  -->  ",theGunPoint.X,theGunPoint.Y,theGunPoint.Z);
#endif
		LauncherToWorld(itm,theGunPoint);								//RJS 26Sep00

#ifdef	_BOMBBUG_
		if ((weapon->LauncherType & LT_MASK)==LT_BOMB)
			::AfxTrace("%d,%d,%d\n",theGunPoint.X,theGunPoint.Y,theGunPoint.Z);
#endif
		theGunPoint.X += itm->World.X;									//RJS 26Sep00
		theGunPoint.Y += itm->World.Y;									//RJS 26Sep00
		theGunPoint.Z += itm->World.Z;									//RJS 26Sep00

		xpos = theGunPoint.X;
		ypos = theGunPoint.Y;
		zpos = theGunPoint.Z;
	}
	else
	{
		xpos = itm->World.X;
		ypos = itm->World.Y;
		zpos = itm->World.Z;
	}

	if (goffset)
	{
		xpos += goffset->gx;
		ypos += goffset->gy;
		zpos += goffset->gz;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MovePointWRTGun
//Author		Robert Slater
//Date			Wed 15 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::MovePointWRTGun(ANGLES&	weaphdg, ANGLES& weappitch, Coords3D& pivot, Coords3D& theeye, D3DVECTOR& ori)
{
	FPMATRIX		omat;
	FPMATRIX_PTR	omatp = &omat;
	Float			sh,sp,ch, cp;
	Float			sp_sh,sp_ch;
	float			nx,ny,nz;
	Float			f_nx,f_ny,f_nz;
	SLong			tmpx, tmpy, tmpz;

	Math_Lib.high_sin_cos(weaphdg,sh,ch);
	Math_Lib.high_sin_cos(weappitch,sp,cp);

	sp_sh = sp * sh;
	sp_ch = sp * ch;

	// Unit vectors:
	// v_x = sh * cp;			// 13
	// v_y = sp;				// 23
	// v_z = ch * cp;			// 33

	omat.L11 = ch;
	omat.L12 = -sp_sh;
	omat.L13 = cp * sh;

	omat.L21 = 0;
	omat.L22 = cp;
	omat.L23 = sp;

	omat.L31 = -sh;
	omat.L32 = -sp_ch;
	omat.L33 = cp * ch;

	// Subtract base pivot offset...

	tmpx = theeye.X - pivot.X;
	tmpy = theeye.Y - pivot.Y;
	tmpz = theeye.Z - pivot.Z;

	f_nx = tmpx;
	f_ny = tmpy;
	f_nz = tmpz;

	nx = (omatp->L11 * f_nx) + (omatp->L12 * f_ny) + (omatp->L13 * f_nz);
	ny = (omatp->L21 * f_nx) + (omatp->L22 * f_ny) + (omatp->L23 * f_nz);
	nz = (omatp->L31 * f_nx) + (omatp->L32 * f_ny) + (omatp->L33 * f_nz);

	fastMath.FloatToInt(&tmpx,nx);
	fastMath.FloatToInt(&tmpy,ny);
	fastMath.FloatToInt(&tmpz,nz);

	// Add base pivot back on...
	theeye.X = tmpx + pivot.X;
	theeye.Y = tmpy + pivot.Y;
	theeye.Z = tmpz + pivot.Z;

	ori.x = omat.L13;
	ori.y = omat.L23;
	ori.z = omat.L33;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LauncherToWorld
//Author		Robert Slater
//Date			Wed 15 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::LauncherToWorld(ItemPtr	itm, Coords3D&	pos)
{
	if (	(itm == Persons2::PlayerSeenAC)								//RJS 28Jun00
		&&	(Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW)	//RJS 28Jun00
		&&	!_Replay.Playback											//RJS 28Jun00
		&&	!itm->Status.deadtime	)									//RJS 28Jun00
		((AirStrucPtr)itm)->fly.pModel->CalcLauncherPos(pos.X,pos.Y,pos.Z);
	else
	{
		if (itm->Status.size >= MOBILESIZE)
		{
			MATRIX   			omat;						
			MATRIX_PTR			obj_matrix = &omat;
			mobileitem*			tmpitm = (mobileitem*)itm;
			SLong				scaleback;

			_matrix.generate2(tmpitm->hdg,tmpitm->pitch,tmpitm->roll,obj_matrix);
		
			scaleback = _matrix.transform(obj_matrix,pos.X,pos.Y,pos.Z);

 			pos.X >>= (16-scaleback);
 			pos.Y >>= (16-scaleback);
 			pos.Z >>= (16-scaleback);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCockpitBuffet
//Author		Robert Slater
//Date			Mon 27 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SetCockpitBuffet(CockpitBuf* newBuffetData)
{
 	buffetData=*newBuffetData;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLightingColour
//Author		Robert Slater
//Date			Fri 14 Apr 2000
//
//Description	Shaded and with time of day...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SetLightingColour(const UByte& r, const UByte& g, const UByte& b, SLightingRGB& lightbase)
{
	SLayerRGB&		pLoCol = lightbase.shadedAmbientCollo;				//MS 15Nov00
	SLayerRGB&		pHiCol = lightbase.shadedAmbientColhi;				//MS 15Nov00
	SLayerRGB&		pAmbCol = lightbase.shadedAmbientColamb;			//MS 15Nov00
	UByte			hired = (r*pHiCol.red())>>8;
	UByte			higreen = (g*pHiCol.green())>>8;
	UByte			hiblue = (b*pHiCol.blue())>>8;
	UByte			lored = (r*pLoCol.red())>>8;
	UByte			logreen = (g*pLoCol.green())>>8;
	UByte			loblue = (b*pLoCol.blue())>>8;
	UByte			ambred = (r*pAmbCol.red())>>8;
	UByte			ambgreen = (g*pAmbCol.green())>>8;
	UByte			ambblue = (b*pAmbCol.blue())>>8;

// Calc colours...
	LIGHTINGDESC lightDesc;
	lightDesc.lowRGB=RGBMake(lored,logreen,loblue);
	lightDesc.highRGB=RGBMake(hired,higreen,hiblue);
	lightDesc.ambientRGB=RGBMake(ambred,ambgreen,ambblue);
	lightDesc.lowDot=0.f;
	lightDesc.highDot=1.f;
//DeadCode JON 11Sep00 	lightDesc.specularPower=1.2f;
	lightDesc.specularRGB = 	Land_Scape.currentLighting.specularHighlight.col();
	g_lpLib3d->SetAmbientLighting(lightDesc);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLightingColour
//Author		Robert Slater
//Date			Fri 14 Apr 2000
//
//Description	As solid light colour (no shading or time of day...)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SetLightingColour(const UByte& r, const UByte& g, const UByte& b)
{
	LIGHTINGDESC lightDesc;
	lightDesc.ambientRGB = lightDesc.highRGB = lightDesc.lowRGB=RGBMake(r,g,b);
	lightDesc.lowDot=0.f;
	lightDesc.highDot=1.f;
//DeadCode JON 11Sep00 	lightDesc.specularPower=1.2f;
	lightDesc.specularRGB = 	Land_Scape.currentLighting.specularHighlight.col();
	g_lpLib3d->SetAmbientLighting(lightDesc);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLightingColour
//Author		Robert Slater
//Date			Fri 14 Apr 2000
//
//Description	With known rgb values...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SetLightingColour(const ULong& colHi, const ULong& colLo, const ULong& colAmb)
{
	LIGHTINGDESC lightDesc;
	lightDesc.lowRGB=colLo;
	lightDesc.highRGB=colHi;
	lightDesc.ambientRGB=colAmb;
	lightDesc.lowDot=0.f;
	lightDesc.highDot=1.f;	
	lightDesc.specularRGB = 	Land_Scape.currentLighting.specularHighlight.col();
//DeadCode JON 11Sep00 	lightDesc.specularPower=1.2f;
	g_lpLib3d->SetAmbientLighting(lightDesc);
	g_lpLib3d->SetAmbientLighting(lightDesc);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MistyMoistyMorning
//Author		Robert Slater
//Date			Thu 25 May 2000
//
//Description	Draws a bank of foggy mist...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::MistyMoistyMorning(const SLong&	mistHeight, const ULong& mistDensity)
{
#ifdef _NO_MIST
	return;
#endif
	if (	(mistHeight > 100)											//RJS 31Aug00
		&&	(Save_Data.detail_3d[DETAIL3D_TRANSSMOKE] != 0)	)			//RJS 31Aug00
	{
//		DoPointStruc	dp[16];
		DoPointStruc*	dp=SHAPE.newco;
		const SLong	sectorShift=20;
		const SLong	sectorSize=1<<sectorShift;
		const SLong sectorStep = sectorSize / 3;
		Coords3D		corner;
		Coords3D		curpos;
		ULong			sector_x, sector_z;
		SLong			RootX;
		SLong			x,y;
		Lib3DPoint*		pRVerts;
		ULong			aval = mistDensity;
		int				polynumber;
		static	int	plist[]={	0,1,2,3,		
								1,4,5,2,
								4,6,7,5,
								8,9,1,0,
								9,10,4,1,
								10,11,6,4,
								12,13,9,8,
								13,14,10,9,
								14,15,11,10};


		corner.X = Three_Dee.ViewerX();
		corner.Y = Three_Dee.ViewerY();
		corner.Z = Three_Dee.ViewerZ();

	// 1st clips to corner point...
		sector_x = corner.X >> sectorShift;
		sector_z = corner.Z >> sectorShift;

		corner.X = sector_x << sectorShift;
		corner.Z = sector_z << sectorShift;
		corner.X -= sectorSize;
		corner.Z -= sectorSize;

		corner.X -= Three_Dee.ViewerX();
		corner.Y = mistHeight - Three_Dee.ViewerY();
		corner.Z -= Three_Dee.ViewerZ();

		if (corner.Y < 0)
		{
			shape::hMaterial=HMATERIAL(Colour(30));

			//Render...
			g_lpLib3d->PushMatrix(MATRIX_OBJECT);
			g_lpLib3d->LoadIdentity(MATRIX_OBJECT);

			D3DVECTOR	t;
			t.dvX=0;									//RJS 12May00
			t.dvY=0;
			t.dvZ=0;

			g_lpLib3d->Translate(MATRIX_OBJECT,t);

			staticRGBlo=	Land_Scape.currentLighting.staticAmbientCollo.col();
			staticRGBhi=	Land_Scape.currentLighting.staticAmbientColhi.col();
			staticRGBamb=	Land_Scape.currentLighting.staticAmbientColamb.col();
			shadedRGBlo=	Land_Scape.currentLighting.shadedAmbientCollo.col();
			shadedRGBhi=	Land_Scape.currentLighting.shadedAmbientColhi.col();
			shadedRGBamb=	Land_Scape.currentLighting.shadedAmbientColamb.col();

			LIGHTINGDESC lightDesc;
			lightDesc.lowRGB=staticRGBlo;
			lightDesc.highRGB=staticRGBhi;
			lightDesc.ambientRGB=staticRGBamb;
			lightDesc.lowDot=0.f;
			lightDesc.highDot=1.f;
	//DeadCode JON 11Sep00 		lightDesc.specularPower=1.2f;
			lightDesc.specularRGB=Land_Scape.currentLighting.specularHighlight.col();
			g_lpLib3d->SetAmbientLighting(lightDesc);

			LIGHTFLAG lf=LF_AMBIENT;
			g_lpLib3d->SetObjectLighting(lf);

			
			g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,&aval);

	// corner(X,Y,Z) is start position
			RootX = corner.X;

			for (sector_z = 0; sector_z < 3; sector_z++)
			{
				corner.X = RootX;
				for (sector_x = 0; sector_x < 3; sector_x++)
				{
					polynumber = 0;
					curpos = corner;
					for (y=0; y < 3; y++)
					{
						curpos.X = corner.X;
						for (x=0; x < 3; x++)
						{
#ifndef	_NOPOLYS_
							pRVerts = g_lpLib3d->BeginPoly(shape::hMaterial,4);

							dp[plist[polynumber]].setPosition(curpos.X,curpos.Y,curpos.Z+sectorStep);
							dp[plist[polynumber]].setIMapCoords(0,0);
							pRVerts[0] = dp[plist[polynumber]];

							polynumber++;
							dp[plist[polynumber]].setPosition(curpos.X+sectorStep,curpos.Y,curpos.Z+sectorStep);
							dp[plist[polynumber]].setIMapCoords(63,0);
							pRVerts[1] = dp[plist[polynumber]];

							polynumber++;
							dp[plist[polynumber]].setPosition(curpos.X+sectorStep,curpos.Y,curpos.Z);
							dp[plist[polynumber]].setIMapCoords(63,63);
							pRVerts[2] = dp[plist[polynumber]];

							polynumber++;
							dp[plist[polynumber]].setPosition(curpos.X,curpos.Y,curpos.Z);
							dp[plist[polynumber]].setIMapCoords(0,63);
							pRVerts[3] = dp[plist[polynumber]];

							polynumber++;

							g_lpLib3d->EndPoly();
#endif
							curpos.X += sectorStep;
						}
						curpos.Z += sectorStep;
					}

					corner.X += sectorSize;
				}
				corner.Z += sectorSize;
			}

			g_lpLib3d->SetObjectLighting(lf);
			g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,aval);
			g_lpLib3d->PopMatrix(MATRIX_OBJECT);

		}
		else
		{
//TempCode RJS 31Aug00 			g_lpLib3d->PushMatrix(MATRIX_VIEWER);
//TempCode RJS 31Aug00 			g_lpLib3d->LoadIdentity(MATRIX_VIEWER);
//TempCode RJS 31Aug00 
//TempCode RJS 31Aug00 			aval -= ((30*Noise(Three_Dee.ViewerX(),mistHeight,Three_Dee.ViewerZ()))>>8);
//TempCode RJS 31Aug00 
//TempCode RJS 31Aug00 			g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,&aval);
//TempCode RJS 31Aug00 
//TempCode RJS 31Aug00 #ifndef	_NOPOINTS_
//TempCode RJS 31Aug00 
//TempCode RJS 31Aug00 			dp[0].setPosition(-101.,101.,101.);
//TempCode RJS 31Aug00 			dp[0].setIMapCoords(0,0);
//TempCode RJS 31Aug00 			dp[1].setPosition(101.,101.,101.);
//TempCode RJS 31Aug00 			dp[1].setIMapCoords(63,0);
//TempCode RJS 31Aug00 			dp[2].setPosition(101.,-101.,101.);
//TempCode RJS 31Aug00 			dp[2].setIMapCoords(63,63);
//TempCode RJS 31Aug00 			dp[3].setPosition(-101.,-101.,101.);
//TempCode RJS 31Aug00 			dp[3].setIMapCoords(0,63);
//TempCode RJS 31Aug00 #endif
//TempCode RJS 31Aug00 #ifndef	_NOPOLYS_
//TempCode RJS 31Aug00 			pRVerts = g_lpLib3d->BeginPoly(shape::hMaterial,4);
//TempCode RJS 31Aug00 			pRVerts[0] = dp[0];
//TempCode RJS 31Aug00 			pRVerts[1] = dp[1];
//TempCode RJS 31Aug00 			pRVerts[2] = dp[2];
//TempCode RJS 31Aug00 			pRVerts[3] = dp[3];
//TempCode RJS 31Aug00 			g_lpLib3d->EndPoly();
//TempCode RJS 31Aug00 #endif
//TempCode RJS 31Aug00 			g_lpLib3d->PopMatrix(MATRIX_VIEWER);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WriteReplayGroup
//Author		Robert Slater
//Date			Mon 4 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	shape::WriteReplayGroup(ItemPtr	tempitem)
{
	animptr			adptr = tempitem->Anim;
	UByte			numberofelements = UByte(NumInGroup(tempitem->shape));	//RJS 11Sep00
	bool			isOk = false;

	if (numberofelements)												//RJS 11Sep00
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(tempitem->shape);
		UByteP			instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		UWord			instruction;
		MinAnimData*	mad;
		UWord			theShape;
		DOGROUP_PTR		ptr;
		ReplayGroupInfo	data;

// Write number of elements...

		if (_Replay.ReplayWrite(&numberofelements,sizeof(UByte)))
		{
// Write out group...
			isOk = true;

			instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
			forever
			{
				instruction = UWord(*instr_ptr);
				instr_ptr ++;

				if (instruction != dogroupno)
					break;

				ptr = DOGROUP_PTR(instr_ptr);
					
				theShape = ptr->shapenum;
					
	// Write out
				data.shape = SLong(theShape);
				data.xoffset = ptr->xoffset;
				data.yoffset = SLong(ptr->yoffset);
				data.zoffset = ptr->zoffset;
				data.animdata = SLong(adptr[0]);

				if (!_Replay.ReplayWrite(UByteP(&data),sizeof(ReplayGroupInfo)))
				{
					isOk = false;
					break;
				}

				adptr += GetElementAnimOffset(ShapeNum(theShape));

				instr_ptr += sizeof(DOGROUP);
			}
		}
	}
	else
	{
// write out number of elements...
		return _Replay.ReplayWrite(&numberofelements,sizeof(UByte))!=FALSE;	//JIM 3Oct00
	}

	return isOk;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReadReplayGroup
//Author		Robert Slater
//Date			Mon 4 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	shape::ReadReplayGroup(ItemPtr	tempitem, UByte	noInGroup)
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(tempitem->shape);

	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
	{
		ReplayGroupInfo	data;
		UByteP			instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		UWord			instruction;
		DOGROUP_PTR		ptr;
		animptr			adptr = tempitem->Anim;

		while (noInGroup)
		{
			instruction = UWord(*instr_ptr);
			instr_ptr ++;

			if (instruction != dogroupno)
			{
				_Error.EmitSysErr(__FILE__":REPLAY GROUP IS OUT OF STEP!");
				break;
			}

			if (!_Replay.ReplayRead(UByteP(&data),sizeof(ReplayGroupInfo)))
				return false;

			ptr = DOGROUP_PTR(instr_ptr);
			ptr->shapenum = UWord(data.shape);
			ptr->xoffset = data.xoffset;
			ptr->yoffset = data.yoffset;
			ptr->zoffset = data.zoffset;

			adptr[0] = UByte(data.animdata);

			adptr += GetElementAnimOffset(ShapeNum(ptr->shapenum));

			instr_ptr += sizeof(DOGROUP);

			noInGroup--;
		}
	}
	else
		_Error.EmitSysErr(__FILE__":REPLAY SHAPE IS NOT A GROUP!");

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawNonVisibleTrail
//Author		Robert Slater
//Date			Mon 11 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::DrawNonVisibleTrail(const itemptr	itm, const void* weapPtr, const int trailType, const UWord& timeNotVisible, const UByte& theLauncher, const	ULong maxTime)
{
	WeapAnimData*	weapon = (WeapAnimData*)weapPtr;

	pTrailItm = itm;
	if (timeNotVisible >= maxTime)
	{
		SHAPE.DetatchVapourStream(weapon->hdg,200);
		weapon->hdg = 0;
		weapon->LauncherType = theLauncher;
	}
	else
	{
		int			index = weapon->hdg;
 		SmokeTypeP	smkptr = SmokeTypeP(&SmokeTrlList[trailType]);
 		int			lifetime = smkptr->LifeTime;

		DrawSmokeTrail(index,UByteP(smkptr),lifetime,TRUE);				//RJS 24Oct00
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NumInGroup
//Author		Robert Slater
//Date			Mon 11 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	shape::NumInGroup(ShapeNum	theShape)
{
	SLong			numberofelements = 0;
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(theShape);
	
	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
	{
		UByteP			instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		UWord			instruction;

		forever
		{
			instruction = UWord(*instr_ptr);
			instr_ptr ++;

			if (instruction != dogroupno)
				break;

			numberofelements++;

			instr_ptr += sizeof(DOGROUP);
		}
	}

	return numberofelements;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitialiseBalloonGroup
//Author		Robert Slater
//Date			Mon 11 Sep 2000
//
//Description	Randomly switch elements off in this group
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::InitialiseBalloonGroup(ItemPtr	tmpitem)
{
	SLong	elements = SHAPE.NumInGroup(tmpitem->shape);
	if (elements)
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(tmpitem->shape);
		ULong			rand = (Math_Lib.rnd()<<16) + Math_Lib.rnd();
		UWord			instruction;
		UByteP			instr_ptr;
		DOGROUP_PTR		ptr;
		UWord			theShape;
		animptr			adptr;
		MinAnimData*	mad;

		SHAPE.SetAnimData(tmpitem,0);

		adptr = tmpitem->Anim;

		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		forever
		{
			instruction = UWord(*instr_ptr);
			instr_ptr ++;

			if (instruction != dogroupno)
				break;

			ptr = DOGROUP_PTR(instr_ptr);
				
			theShape = ptr->shapenum;

			mad = (MinAnimData*)adptr;
			if ((rand & 1)==0)
			{
				mad->IsInvisible = 1;
				mad->itemstate = DEAD;
			}

			rand >>= 1;

			adptr += GetElementAnimOffset(ShapeNum(theShape));

			instr_ptr += sizeof(DOGROUP);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakOffTrail
//Author		Robert Slater
//Date			Wed 20 Sep 2000
//
//Description	Detaches trails from dead wings
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::BreakOffTrail(const ItemPtr	itm, const ShapeNum& theShape, animptr&	aptr)
{
	if (itm->Status.size == AIRSTRUCSIZE)
	{
		ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(theShape);//RJS 23Apr99
		int					wpnum;
		WeapAnimData*		weapon;
		MoveGunAnimData*	adptr = (MoveGunAnimData*) aptr;
		int					weapcnt = 1;
		UByte				instsize = sizeof(DOLAUNCHER) + 1;
		DOLAUNCHER_PTR		lptr;
		UByteP				instr_ptr;
		UByteP				base_ptr;
		UWord				instruction;
const	UWord				WING_NONE = 0;
const	UWord				WING_LEFT = 1;
const	UWord				WING_RIGHT = 2;
		UWord				animflag = WING_NONE;

		if (sdptr->AnimDataSize == AIRCRAFTANIM)
		{
			AircraftAnimData*	adptr = (AircraftAnimData*)	aptr;

			if (adptr->LEFTWINGIN == 255)
				animflag |= WING_LEFT;

			if (adptr->RIGHTWINGIN == 255)
				animflag |= WING_RIGHT;
		}
		else
		{
			if (sdptr->AnimDataSize == SIMPLEAIRCRAFTANIM)
			{
				SimpleAircraftAnimData*	adptr = (SimpleAircraftAnimData*)	aptr;

				if (adptr->LEFTWINGIN == 255)
					animflag |= WING_LEFT;

				if (adptr->RIGHTWINGIN == 255)
					animflag |= WING_RIGHT;
			}
		}

		if (animflag != WING_NONE)
		{
			weapcnt = adptr->nolaunchers;

			base_ptr = (UByteP )sdptr + sdptr->LauncherDataSize;

			weapon = &adptr->weaponlaunchers[0];
			for (wpnum = 0; wpnum < weapcnt; wpnum++)
			{
				if (	weapon
					&& ((weapon->LauncherType & LT_MASK)==LT_SMKTRAILS)
					&&	(weapon->hdg > 0)	)
				{
					instr_ptr = base_ptr + (instsize * weapon->launcherIndex);
					instr_ptr++;

					lptr = (DOLAUNCHER_PTR) instr_ptr;
					if (	(	(animflag & WING_LEFT)
							 &&	(lptr->posx < -180)	)
						||	(	(animflag & WING_RIGHT)
							 && (lptr->posx > 180)	)	)
					{
						SHAPE.DetatchVapourStream(weapon->hdg,LIFETIME_VAPOUR);
						weapon->hdg = 0;
					}
				}

				weapon++;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLightingType
//Author		Robert Slater
//Date			Wed 27 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline int	shape::GetLightingType(const UByte&	theType)
{
	int	lflag = LF_AMBIENT;

	switch (theType)
	{
	case STEXT_DULL:
		lflag = LF_LIGHTING;
	break;
	case STEXT_SHINY:
		lflag = LF_SPECULAR;
	break;
	case STEXT_REFLECTIVE:
		lflag = LF_ALPHA;
	break;
	case STEXT_LIGHT:
		lflag = LF_LIGHTSOURCE;
	break;
	}

	return lflag;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		animate_shape_cockpit
//Author		Robert Slater
//Date			Mon 23 Oct 2000
//
//Description	Only for the player...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::animate_shape_cockpit()
{
	Obj3D	theObj;
	
	object_obj3d = &theObj;

	theObj.ItemPtr = Persons2::PlayerSeenAC;
	theObj.AnimPtr = Persons2::PlayerSeenAC->Anim;
	theObj.AngH = Persons2::PlayerSeenAC->hdg;
	theObj.AngC = Persons2::PlayerSeenAC->pitch;
	theObj.AngR = Persons2::PlayerSeenAC->roll;
	theObj.Shape = Persons2::PlayerSeenAC->shape;
	theObj.Body.X.f = 0;
	theObj.Body.Y.f = 0;
	theObj.Body.Z.f = 0;
	theObj.realbz.f = 0;

//DeadCode RJS 7Nov00 	UpdateVapourCoords(Persons2::PlayerSeenAC,Persons2::PlayerSeenAC->Anim,false);
	UpdateVapourCoords(Persons2::PlayerSeenAC,Persons2::PlayerSeenAC->Anim,true);	//RJS 7Nov00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetRearGunner
//Author		Robert Slater
//Date			Tue 24 Oct 2000
//
//Description	Only for the player...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::SetRearGunner(const AirStrucPtr	ac, const SLong& index, const SLong& gunnerNumber)
{
	int					wpindex;
	SLong				wpindex2;
	void*				weaprec = FindWeapRecord(ac->shape,wpindex2);
	SLong				launchindex;
	DOLAUNCHER_PTR		lptr;
	MoveGunAnimData*	adptr = (MoveGunAnimData*)ac->Anim;

	FindWeaponRec(weaprec,LT_BULLET_REAR,wpindex);

	reargunner_launchtime = adptr->weaponlaunchers[index].LaunchTime;
	reargunner_launcher = adptr->weaponlaunchers[index].LauncherType;
	reargunner_index = index;
	reargunner_active = true;
	reargunner_item = ac;
	reargunner_cockpitindex = gunnerNumber;

	GetGunClip(reargunner_launcher,gunner_minHdg,gunner_arcHdg,gunner_minPitch,gunner_arcPitch);

	launchindex = adptr->weaponlaunchers[reargunner_index].launcherIndex;
	lptr = (DOLAUNCHER_PTR)GetLauncherPos(ac->shape,launchindex);

	reargunner_pivotx = lptr->pivotx;
	reargunner_pivoty = lptr->pivoty;
	reargunner_pivotz = lptr->pivotz;

	adptr->weaponlaunchers[index].LauncherType = LT_BULLET_REAR;
	adptr->weaponlaunchers[index].LaunchTime = WeapInfo(wpindex,LT_BULLET_REAR);
}					

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDefaultHdgPitch
//Author		Robert Slater
//Date			Tue 24 Oct 2000
//
//Description
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::GetDefaultHdgPitch(int	launcherType, SWord& hdg, SWord& pitch)
{
	int	masked = launcherType & LT_MASK;

	if (masked == LT_MOVEGUN)										//RJS 24Oct00
	{
		SWord	tmp_minHdg;										//RJS 26Oct00
		SWord	tmp_minPitch;
		SWord	tmp_arcHdg;
		SWord	tmp_arcPitch;

		GetGunClip(launcherType,tmp_minHdg,tmp_arcHdg,tmp_minPitch,tmp_arcPitch);

		hdg = tmp_minHdg + (tmp_arcHdg >> 1);
		pitch = tmp_minPitch + (tmp_arcPitch >> 1);
	}
	else
	{
		hdg = pitch = 0;
	}
}

inline void	shape::TransformSmokePoint(const UByteP	instr_ptr, Coords3D&	pos)
{
	DOLAUNCHER_PTR	ptr = DOLAUNCHER_PTR(instr_ptr);
	SLong			wx = ptr->posx;
	SLong			wy = ptr->posy;
	SLong			wz = ptr->posz;
	MATRIX  		omat;										
	MATRIX_PTR		obj_matrix = &omat;	

	wx <<= shapescale;
 	wy <<= shapescale;
 	wz <<= shapescale;

	_matrix.generate2(	object_obj3d->AngH,
						object_obj3d->AngC,
						object_obj3d->AngR,
						obj_matrix);

	UWord	scaleback = _matrix.transform(obj_matrix,wx,wy,wz);

	wx >>= (16-scaleback);
	wy >>= (16-scaleback);
	wz >>= (16-scaleback);

	pos.X = wx;
	pos.Y = wy;
	pos.Z = wz;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyGroup
//Author		Robert Slater
//Date			Mon 13 Nov 2000
//
//Description	Copy group contents from one shape to another
//				(Assume anim-data is already set up)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	shape::CopyGroup(const ShapeNum	fromShape, const ShapeNum	toShape)
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(fromShape);
	ShapeDescPtr	sdptr2 = SHAPESTUFF.GetShapePtr(toShape);
			
	if (	(SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
		&&	(SHAPESTUFF.GetShapeScale(sdptr2) == SHP_GRP)	)
	{
		UByteP		f_instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		UByteP		t_instr_ptr = (UByteP )sdptr2 + sdptr2->liveshpref;
		UWord		f_instruction, t_instruction;

		forever
		{
			f_instruction = (UWord )*f_instr_ptr;
			f_instr_ptr ++;

			t_instruction = (UWord )*t_instr_ptr;
			t_instr_ptr ++;

			if (	(f_instruction == dogroupno)
				&&	(t_instruction == dogroupno)	)
			{
				*DOGROUP_PTR(t_instr_ptr) = *DOGROUP_PTR(f_instr_ptr);

				f_instr_ptr += sizeof(DOGROUP);
				t_instr_ptr += sizeof(DOGROUP);
			}
			else
				break;
		}
	}
}





//Special anim data stuff......

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAnimDataSizeFlags
//Author		Robert Slater
//Date			Fri 16 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void shape::SetAnimDataFlags(ShapeNum shpno,animptr& adptr, SLong &animflags)
{
	ShapeDescPtr sdptr,newshpp;
	SLong	ret_val;
	SWord	animdatasize;
	SLong	flagstuff = 0;

	sdptr = SHAPESTUFF.GetShapePtr(shpno);
	ShapeNum	newshp;

	if (SHAPESTUFF.GetShapeScale(sdptr)!=SHP_GRP)				
	{
		animdatasize = sdptr->AnimDataSize;
		if (animdatasize > -1)
		{
			//special cases...
			switch (animdatasize)
			{
				case MINANIM:
					flagstuff += 1<<MINANIM;
					break;
				case POLYPITANIM:
					flagstuff += 1<<MINANIM;
					flagstuff += 1<<MOVEGUNANIM;
					flagstuff += 1<<AIRCRAFTANIM;
					flagstuff += 1<<POLYPITANIM;
					break;
				
				case SIMPLEAIRCRAFTANIM:
					flagstuff += 1<<MINANIM;
					flagstuff += 1<<MOVEGUNANIM;
					flagstuff += 1<<SIMPLEAIRCRAFTANIM;
					break;

				case AIRCRAFTANIM:
					flagstuff += 1<<MINANIM;
					flagstuff += 1<<MOVEGUNANIM;
					flagstuff += 1<<AIRCRAFTANIM;
					break;
				case SMOKETRAILANIM:
					flagstuff += 1<<MINANIM;
					flagstuff += 1<<MOVEGUNANIM;
					flagstuff += 1<<SMOKETRAILANIM;
					break;
				case TRUCKANIM:
					flagstuff += 1<<MINANIM;
					flagstuff += 1<<MOVEGUNANIM;
					flagstuff += 1<<TRUCKANIM;
					break;
				case TRAINANIM:
					flagstuff += 1<<MINANIM;
					flagstuff += 1<<MOVEGUNANIM;
					flagstuff += 1<<TRAINANIM;
					break;
				case TWOGUNANIM:										//RJS 27Jun00
					flagstuff += 1<<MINANIM;
					flagstuff += 1<<MOVEGUNANIM;
					flagstuff += 1<<TWOGUNANIM;
					break;
				default:
					flagstuff += 1<<MINANIM;
					flagstuff += 1<<animdatasize;
					break;
			}
		}
		else
			flagstuff = 1<<MINANIM;

		animflags |= flagstuff;
	}
	else
	{
		ShapeNum	newshp;
		SLong		tmp;
		UByteP		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
		SLong		count = 0;

		while (GetGroupElement(instr_ptr,newshp,tmp,tmp,tmp))
		{
			SetAnimDataFlags(newshp,adptr,animflags);
			count++;
		}

		if (!count)												//DAW 23Apr99
			animflags |= 1<<MINANIM;							//DAW 23Apr99
	}

	adptr = (AnimFlagField)animflags;							//RJS 30Nov99
}

UByte&	animptr::operator[] (int a)
{
#ifndef	NDEBUG
	assert(size>a);												//RJS 30Nov99
#endif
	return UByteP(ptr)[a];
}

UByte&	animptr::operator[] (SWord a)
{
#ifndef	NDEBUG
	assert(size>a);												//RJS 30Nov99
#endif
	return UByteP(ptr)[a];
}

UByte&	animptr::operator[] (UWord a)
{
#ifndef	NDEBUG
	assert(size>a);												//RJS 30Nov99
#endif
	return UByteP(ptr)[a];
}

UByte&	animptr::operator[] (UByte a)
{
#ifndef	NDEBUG
	assert(size>a);												//RJS 30Nov99
#endif
	return UByteP(ptr)[a];
}

void	animptr::operator += (int a)
{
	ptr = (void*)((UByteP)ptr + a);
#ifndef	NDEBUG
	assert(size >= a);											//RJS 14Dec99
	size -= ULong(a);											//RJS 14Dec99
	if (!size)	ptr = 0;										//RJS 14Dec99
#endif
}

void	animptr::operator ++ ()
{
	ptr = (void*)((UByteP)ptr + 1);
#ifndef	NDEBUG
	assert(size >= 1);											//RJS 30Nov99
	size -= 1;
	if (!size)	ptr = 0;										//RJS 30Nov99
#endif
}

#ifndef	NDEBUG

animptr::operator MinAnimData*(){assert(flags & (1<<MINANIM)); return (MinAnimData*)ptr;};//RJS 30Nov99
animptr::operator GrpMinAnimData*(){assert(flags & (1<<MINANIM)); return (GrpMinAnimData*)ptr;};//RJS 30Nov99
animptr::operator SunAnimData*(){assert(flags & (1<<SUNANIM)); return (SunAnimData*)ptr;};//RJS 30Nov99
animptr::operator ExplodeAnimData*(){INT3; return (ExplodeAnimData*)ptr;};//RJS 30Nov99
animptr::operator FireAnimData*(){INT3; return (FireAnimData*)ptr;};//RJS 30Nov99
animptr::operator BalloonAnimData*(){assert(flags & (1<<BALLOONANIM)); return (BalloonAnimData*)ptr;};//RJS 15Dec99
animptr::operator BarageAnimData*(){assert(flags & (1<<BARAGEANIM)); return (BarageAnimData*)ptr;};//RJS 30Nov99
animptr::operator TroopAnimData*(){assert(flags & (1<<TROOPANIM)); return (TroopAnimData*)ptr;};//RJS 30Nov99
animptr::operator TrainAnimData*(){assert(flags & (1<<TRAINANIM)); return (TrainAnimData*)ptr;};//RJS 30Nov99
animptr::operator BlokesAnimData*(){assert(flags & (1<<BLOKESANIM)); return (BlokesAnimData*)ptr;};		//RJS 30Nov99
//DeadCode RJS 17Nov99 animptr::operator WeapAnimData*(){assert(size & (1<<WEAPANIM)); return (WeapAnimData*)ptr;};//RJS 30Nov99
animptr::operator MoveGunAnimData*(){assert(flags & (1<<MOVEGUNANIM)); return (MoveGunAnimData*)ptr;};//RJS 30Nov99
animptr::operator TwoGunAnimData*(){assert(flags & (1<<TWOGUNANIM)); return (TwoGunAnimData*)ptr;};	//RJS 27Jun00
animptr::operator AircraftAnimData*(){assert(flags & (1<<AIRCRAFTANIM)); return (AircraftAnimData*)ptr;};//RJS 30Nov99
animptr::operator PolyPitAnimData*(){assert(flags & (1<<POLYPITANIM)); return (PolyPitAnimData*)ptr;};//RJS 30Nov99
animptr::operator LauncherAnimData*(){assert(flags & (1<<LAUNCHERANIM)); return (LauncherAnimData*)ptr;};//RJS 30Nov99
animptr::operator WindsocAnimData*(){assert(flags & (1<<WINDSOCANIM)); return (WindsocAnimData*)ptr;};//RJS 30Nov99
animptr::operator CloneAnimData*(){assert(flags & (1<<CLONEANIM)); return (CloneAnimData*)ptr;};//RJS 30Nov99
animptr::operator FlareAnimData*(){assert(flags & (1<<FLAREANIM)); return (FlareAnimData*)ptr;};//RJS 30Nov99
animptr::operator ParachuteAnimData*(){assert(flags & (1<<PARACHUTEANIM)); return (ParachuteAnimData*)ptr;};//RJS 30Nov99
animptr::operator ThugAnimData*(){assert(flags & (1<<THUGANIM)); return (ThugAnimData*)ptr;};//RJS 30Nov99
animptr::operator MissileAnimData*(){assert(flags & (1<<MISSILEANIM)); return (MissileAnimData*)ptr;};//RJS 30Nov99
animptr::operator DebrisAnimData*(){assert(flags & (1<<DEBRISANIM)); return (DebrisAnimData*)ptr;};//RJS 30Nov99
animptr::operator SmokeTrailAnimData*(){assert(flags & (1<<SMOKETRAILANIM)); return (SmokeTrailAnimData*)ptr;};//RJS 30Nov99
animptr::operator Coords3DList*(){return (Coords3DList*)ptr;};	//RJS 30Nov99
animptr::operator SimpleAircraftAnimData*(){assert(flags & (1<<SIMPLEAIRCRAFTANIM)); return (SimpleAircraftAnimData*)ptr;};//RJS 30Nov99
animptr::operator BirdLauncherAnimData*(){assert(flags & (1<<BIRDLAUNCHERANIM)); return (BirdLauncherAnimData*)ptr;};//RJS 01Dec99
animptr::operator BlastAnimData*(){assert(flags & (1<<BLASTANIM)); return (BlastAnimData*)ptr;};//RJS 13Dec99
animptr::operator void*(){assert(flags & (1<<MINANIM)); return (void*)ptr;};//RJS 30Nov99

#endif

UByteP	animptr::operator & ()
{
#ifndef	NDEBUG
	if (size)													//RJS 30Nov99
		return (UByteP)ptr;
	
	return NULL;
#else
	return (UByteP)ptr;
#endif	
};

int		animptr::operator - (animptr& a)
{
#ifndef	NDEBUG
	int	retval = (int)ptr - (int)a.ptr;

	assert((retval>=0)&&(retval<size));							//RJS 30Nov99

	return (retval);
#else
	return (int)ptr - (int)a.ptr;
#endif
}

ULong	animptr::Offset(void*	a)
{
#ifndef	NDEBUG
	SLong	offset = (UByteP)a - (UByteP)ptr;

	assert ((offset>=0)&&(offset<size));						//RJS 30Nov99

	return ULong(offset);
#else
	return ULong((UByteP)a - (UByteP)ptr);
#endif
}

inline void	animptr::SetItemState(const int theState)
{
#ifndef	NDEBUG
	assert ((ptr!=NULL) && (size!=0));
#endif
	((MinAnimData*)ptr)->itemstate = theState;
}
	
inline int	animptr::GetItemState()
{
#ifndef	NDEBUG
	assert ((ptr!=NULL) && (size!=0));
#endif

	return int(((MinAnimData*)ptr)->itemstate);
}


#ifndef	NDEBUG

typedef struct _MemBlockStruc
{
        _MemBlockStruc*	pBlockHeaderNext;
		_MemBlockStruc*	pBlockHeaderPrev;
		char*			filename;
		ULong			nLine;
		ULong			nDataSize;
		ULong			nBlockUse;
		ULong			lrequest;
		UByte			gap[4];
		UByte			userdata[8];
} _MemBlockStruc;

void	DbgMemTest2(void*	ptr)
{
	if (ptr)
	{
		_MemBlockStruc*	memblock = (_MemBlockStruc*) (int(ptr)-32);
		if (	(memblock->gap[0]!=0xFD)
			||	(memblock->gap[1]!=0xFD)
			||	(memblock->gap[2]!=0xFD)
			||	(memblock->gap[3]!=0xFD)	)
		{
			INT3;
		}

		if (	(memblock->gap[4+memblock->nDataSize]!=0xFD)
			||	(memblock->gap[5+memblock->nDataSize]!=0xFD)
			||	(memblock->gap[6+memblock->nDataSize]!=0xFD)
			||	(memblock->gap[7+memblock->nDataSize]!=0xFD)	)
		{
			INT3;
		}
	}
}

void	animptr::MemTest()
{
	DbgMemTest2(ptr);
}


#endif
