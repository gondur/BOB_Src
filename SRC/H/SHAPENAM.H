//------------------------------------------------------------------------------
//Filename       shapenam.h
//System         
//Author         Robert Slater
//Date           Fri 20 Nov 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	SHAPENAM_Included
#define	SHAPENAM_Included

#define	DEFAULT_SHAPENAM 0

//#include	"shapenum.g"

#ifndef	NDEBUG

#define AFX_CDECL __cdecl
typedef char CHAR;
#define CONST               const
typedef CONST CHAR *LPCSTR, *PCSTR;
typedef LPCSTR LPCTSTR;
void AFX_CDECL AfxTrace(LPCTSTR lpszFormat, ...);

#endif



const	ShapeNum	MiniExplosionShape	=	SMOKE;				
const	ShapeNum	BigExplosionShape	=	EXPLO;				
const	ShapeNum	GunfireShape		=	BULLET;				
const	ShapeNum	SmokinShape			=	SMOKE;				
const	ShapeNum	BigSmokeShape		=	BSMKE;				
const	ShapeNum	InvisibleLauncher	=	EMPTY;				
const	ShapeNum	GroundExplosionShape=	EXPLO;				
const	ShapeNum	CraterShape			=	CRATER;				
const	ShapeNum	SmallFireShape		=	SMLFIR;				
const	ShapeNum	SmallFlashShape		=	SMFLSH;				
const	ShapeNum	LargeFireShape		=	FIRE;				
const	ShapeNum	FlakShape			=	SMOKE;				
const	ShapeNum	SmallCraterShape	=	DRTSHK;				
const	ShapeNum	HugeExplosionShape	=	BEXP;				
const	ShapeNum	RicochetSmokeShape	=	RSMOKE;				
const	ShapeNum	ShockwaveShape		=	SHCKWV;				//RJS 16Nov99
const	ShapeNum	BoxShape			=	AMMOC;				
const	ShapeNum	BirdShape			=	EMPTY;				
const	ShapeNum	ChickenShape		=	EMPTY;				
const	ShapeNum	DustShape			=	SDUST;				
const	ShapeNum	GermFlakShape		=	EMPTY;				
const	ShapeNum	BritFlakShape		=	EMPTY;				
const	ShapeNum	TrenchShapeBrit		=	EMPTY;				
const	ShapeNum	TroopLauncherShape	=	EMPTY;				
const	ShapeNum	FuelBarrelShape		=	EMPTY;				
const	ShapeNum	TinyFireShape		=	EMPTY;				
const	ShapeNum	TrenchShapeGerm		=	EMPTY;				
const	ShapeNum	SmokeStack1Shape	=	VAPSHP;				//RJS 24May00
const	ShapeNum	VapourStreamShape	=	FIRSMK;				
const	ShapeNum	CloneShape			=	GCLONE;				
const	ShapeNum	MigPuffShape		=	EMPTY;				//RJS 15Dec99
const	ShapeNum	NapalmShape			=	EMPTY;				//RJS 15Dec99

const	ShapeNum	BlokeFlyingShape	=	BLOKE;				
const	ShapeNum	BlokeRunShape		=	BLOKE;				
const	ShapeNum	BlokeFireShape		=	BLOKE;				
const	ShapeNum	BlokeShape			=	BLOKE;				

const	ShapeNum	DebrisDirtShape		=	DEB4;				
const	ShapeNum	DebrisWoodShape		=	DEB1;				
const	ShapeNum	DebrisBrickShape	=	DEB3;				
const	ShapeNum	DebrisMechShape		=	DEB5;				
const	ShapeNum	DebrisStartShape	=	DEB1;				
const	ShapeNum	DebrisEndShape		=	DEB7;				

const	ShapeNum	ExplosionShockShape =	SWAVE;				
const	ShapeNum	NapalmThugShape 	=	FIRTHG;				//RJS 23Nov99
const	ShapeNum	NapalmFingerShape 	=	ROKSHP;				
const	ShapeNum	ExplosionThugShape 	=	EXPFST;				

const	ShapeNum	FireballShape 		=	SMKBIG;
const	ShapeNum	SmallFireballShape 	=	FIRSMK;

const	ShapeNum	SmallScatFireShape	=	CLSFIR;
const	ShapeNum	LargeScatFireShape	=	CLLFIR;

const	ShapeNum	SparkShape	=	SPARKY;

const	ShapeNum	DingyShape			=	DINGY;				//RJS 19Jun00

const	ShapeNum	ExplodeSmokeShape	=	SMKMED;				//RJS 22May00
const	ShapeNum	ExplodeDirtShape	=	DRTMED;				//RJS 22May00

#endif
