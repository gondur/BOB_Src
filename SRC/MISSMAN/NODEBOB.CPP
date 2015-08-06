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

//////////////////////////////////////////////////////////////////////
//
// Module:      nodebob.cpp
//
// Created:     17/11/99 by DAW
//
// Description: 
//
//////////////////////////////////////////////////////////////////////
#include	"dosdefs.h"											//DAW 29Feb96
#define F_SOUNDS												//DAW 05Aug96
#define F_COMMON
#include	"files.g"		//NON-GRAPHICS FILES				//JIM 14May96
//DeadCode JIM 30Apr96 #include	"miss_man.h"										//DAW 17Jan96
//#include	"ui.h"
#include	"uniqueid.h"  
#include "flyinit.h"													//RDH 07/03/00
#include "cstring.h"
#include "..\mfc\resource.h"

#include "movement.h"
#include "package.h"
#include "nodebob.h"
#undef	nodebob_DEFINED_17_11_1999
#include "nodebob.h"

#include "myerror.h"
//#include "rcombox.h"
#include	"bstream.h"
#include "savegame.h"

#include "missman2.h"
#include "mytime.h"	
#include "persons2.h"
#include "mymath.h"	
#include "globrefs.h"
#include "rchatter.h"
#include	"sqddiary.h"
	Target::TargPriority	Target::*	Target::playerpriority=NULL;
	Target::TargType		Target::*	Target::playertype=NULL;
	UByte			Target::*	Target::playerstatus=NULL;

//note: relying on D_ to handle missing date
#define DAM(level,date,day)	day+DL_##level+D_##date-D_
#define	DATE(date,day)	day+D_##date
//note: set AAA and BALL levels.
#define AB(a,b)	Defenses(AAA_##a+BALL_##b)
#define	AAA_	0
#define	BAL_	0
#define LON(a,b)	Defenses(DEF_LONDON+AAA_##a+BALL_##b)

const	UniqueID

UID_FA_CastleBromwich		=UID_FA_BrooklandsVickers,
//DeadCode MS 04Feb00 UID_AF_NEWCASTLE	=UID_NB_Portsmouth,
//DeadCode MS 04Feb00 UID_AF_STEVAL			=UID_NB_Portsmouth,	
UID_DUMMY	=UID_NULL;



	enum	{	IDS_SECTOR_NONE,
				IDS_SECTOR_A,
				IDS_SECTOR_B,
				IDS_SECTOR_C,
				IDS_SECTOR_D,
				IDS_SECTOR_E,
				IDS_SECTOR_F,
				IDS_SECTOR_G,
				IDS_SECTOR_H,
				IDS_SECTOR_I,
				IDS_SECTOR_J,
				IDS_SECTOR_K,
				IDS_SECTOR_L,
				IDS_SECTOR_M,
				IDS_SECTOR_N,
				IDS_SECTOR_O,
				IDS_SECTOR_P,
				IDS_SECTOR_Q,
				IDS_SECTOR_R,
				IDS_SECTOR_S,
				IDS_SECTOR_T,
				IDS_SECTOR_U,
				IDS_SECTOR_V,
				IDS_SECTOR_W,
				IDS_SECTOR_X,
				IDS_SECTOR_Y,
				IDS_SECTOR_Z,
	};
	//DEADCODE RDH 09/12/99 enum	{	IDS_GROUP_10,IDS_GROUP_11,IDS_GROUP_12,IDS_GROUP_13	};




	struct	DamageRate
	{	//repair and damage rating
		UByte	repairptsperhour;
		UByte	damagescoretenths;
	};

	DamageRate	 DR_LargeAF={50,10},
			 	DR_SmallAF={30,12},	
			 	DR_LargeFactory={10,8},
			 	DR_Normal={15,10},
			 	DR_SmallRadar={5,20},
			 	DR_Convoy={100,1},
			 	DR_dummy;

	II_Target	mytargets=
	{{UID_NULL}};


	II_TargetSateliteField	NodeData::satelites[]=
	{

	//----------------------------------
	//TANGMERE SECTOR SATELLITES

	/*name*/{UID_AF_WESTHAMPNETT,
	/*real*/	TT_FIGHTERAF,TP_SECONDARYCOASTALAF,0,AB(LOW,NONE),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYCOASTALAF,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_AF_TANGMERE,UID_AF_THORNEYISLAND,UID_AF_FORD,UID_AF_GOSPORT,UID_AF_SHOREHAM},
	/*damage*/  &DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_AFWESTHA,
	/*detail*/	{FIL_1_M1WESTHA},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_1_TXWESTHA,
	/*maxonaf*/	1,
	/*nextsat*/	UID_NULL,
	/*loc*/		LOC_COAST,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_TANGMERE,
			},



	//----------------------------------
	//BIGGIN HILL SECTOR SATELLITES


	/*name*/{UID_AF_GRAVESEND,
	/*real*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,0,AB(MED,LOW),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,-1,
	/*turn pt*/	{UID_NV_NORTHGOODWIN,UID_NV_SOUTHFORELAND,UID_CV_TUNBRIDGEWELLS},
	/*sec trg*/	{UID_AF_HORNCHURCH,UID_AF_BIGGINHILL,UID_AF_ROCHFORD,UID_AF_KENLEY,UID_AF_CROYDON},
	/*damage*/  &DR_SmallAF,
//TempCode MS 05Oct00 	/*dates*/	{DAM(LOW,0Aug,16),DAM(NONE,0Aug,17)},
	/*dates*/	{DAM(LOW,0Sept,4)},
	/*bfield*/	 FIL_1_AFGRAVES,
	/*detail*/	{FIL_1_M1GRAVES},
	/*detail2*/	{FIL_1_M2GRAVES},
	/*taxi*/	FIL_1_TXGRAVES,
	/*maxonaf*/	1,
	/*nextsat*/	UID_AF_WESTMALLING,
	/*loc*/		LOC_S_LON,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_BIGGINHILL,
			},

	/*name*/{UID_AF_WESTMALLING,
	/*real*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,0,AB(LOW,NONE),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_AF_DETLING,UID_AF_GRAVESEND,UID_IN_Maidstone,UID_FA_Pobjoy,UID_FA_ShortsBros},
	/*damage*/  &DR_SmallAF,
//TempCode MS 05Oct00 	/*dates*/	{DAM(LOW,0Aug,15),DAM(OUT,0Aug,16),DAM(LOW,0Aug,20),DAM(NONE,0Aug,22)},
	/*dates*/	{DAM(LOW,0Aug,10),DAM(OUT,0Aug,15),DAM(MED,0Aug,16),DAM(MED,0Aug,18),DAM(MED,0Sept,3)},
	/*bfield*/	 FIL_1_AFWESTMA,
	/*detail*/	{FIL_1_M1WESTMA},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_1_TXWESTMA,
	/*maxonaf*/	1,
	/*nextsat*/	UID_AF_LYMPNE,
	/*loc*/		LOC_S_LON,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_BIGGINHILL,
			},

	/*name*/{UID_AF_LYMPNE,
	/*real*/	TT_FIGHTERAF,TP_SECONDARYCOASTALAF,0,AB(LOW,NONE),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYCOASTALAF,-1,
	/*turn pt*/	{UID_CV_RYE,UID_NV_SOUTHFORELAND,UID_NV_VARNELIGHTSHIP},
	/*sec trg*/	{UID_AF_HAWKINGE,UID_CH_Rye,UID_CH_Dover,UID_DK_Dover},
	/*damage*/	&DR_SmallAF,
//TempCode MS 05Oct00 	/*dates*/	{DAM(MED,0Aug,12),DAM(OUT,0Aug,15),DAM(LOW,0Aug,17),DAM(LOW,0Sept,1),DAM(LOW,0Sept,4)},
	/*dates*/	{DAM(MED,0Aug,12),DAM(OUT,0Aug,15),DAM(MED,0Aug,17),DAM(LOW,0Sept,1),DAM(LOW,0Sept,4)},
	/*bfield*/	 FIL_1_AFLYMPNE,
	/*detail*/	{FIL_1_M1LYMPNE},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_1_TXLYMPNE,
	/*maxonaf*/	1,
	/*nextsat*/	UID_AF_MANSTON,
	/*loc*/		LOC_COAST,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_BIGGINHILL,
			},

	/*name*/{UID_AF_MANSTON,
	/*real*/	TT_FIGHTERAF,TP_PRIMARYCOASTALAF,0,AB(MED,NONE),
	/*false*/	TT_FIGHTERAF,TP_PRIMARYCOASTALAF,-1,
	/*turn pt*/	{UID_NV_SOUTHFORELAND,UID_NV_EASTGOODWIN,UID_NV_NORTHGOODWIN},
	/*sec trg*/	{UID_CL_Foreness,UID_AF_EASTCHURCH,UID_DK_Sheerness,UID_CL_Whitstable,UID_CH_Dunkirk,},
	/*damage*/ 	&DR_SmallAF,
//TempCode MS 05Oct00 	/*dates*/	{DAM(OUT,0Aug,12),DAM(LOW,0Aug,14),DAM(MED,0Aug,15),DAM(LOW,0Aug,16),DAM(LOW,0Aug,18),DAM(MED,0Aug,22),DAM(OUT,0Aug,24)},
	/*dates*/	{DAM(OUT,0Aug,12),DAM(MED,0Aug,14),DAM(OUT,0Aug,24),DAM(MED,0Sept,6)},
	/*bfield*/	 FIL_1_AFMANSTO,
	/*detail*/	{FIL_1_M1MANSTO},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_1_TXMANSTO,
	/*maxonaf*/	1,
	/*nextsat*/	UID_AF_HAWKINGE,
	/*loc*/		LOC_COAST,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_BIGGINHILL,
			},

	/*name*/{UID_AF_HAWKINGE,
	/*real*/	TT_FIGHTERAF,TP_PRIMARYCOASTALAF,0,AB(MED,NONE),
//DeadCode MS 15Nov00 	/*false*/	TT_FIGHTERAF,TP_SECONDARYCOASTALAF,-1,
	/*false*/	TT_FIGHTERAF,TP_PRIMARYCOASTALAF,-1,
	/*turn pt*/	{UID_NV_DUNGENESS,UID_NV_SOUTHGOODWIN,UID_NV_VARNELIGHTSHIP},
	/*sec trg*/	{UID_AF_LYMPNE,UID_CH_Rye,UID_CH_Dover,UID_DK_Dover,UID_CL_Foreness},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/	{DAM(MED,0Aug,12),DAM(MED,0Aug,15)},
	/*bfield*/	 FIL_1_AFHAWKIN,
	/*detail*/	{FIL_1_M1HAWKIN},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_1_TXHAWKIN,
	/*maxonaf*/	2,
	/*nextsat*/	UID_NULL,
	/*loc*/		LOC_COAST,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_BIGGINHILL,
			},

	//------------------------
	//NORTH WEALD SECTOR SATELLITES


	/*name*/{UID_AF_MARTLESHAM,
	/*real*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,0,AB(LOW,NONE),
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,-1,
	/*turn pt*/	{UID_NV_TONGUE,UID_CV_SOUTHENDONSEA,UID_Kelvedon},
	/*sec trg*/	{UID_CH_Bawdsey,UID_CH_Darsham,UID_CL_Dunwich},
	/*damage*/ 	&DR_SmallAF,
//TempCode MS 05Oct00 	/*dates*/	{DAM(LOW,0Aug,18),DAM(MED,0Aug,24),DAM(MED,0Sept,3)},
	/*dates*/	{DAM(LOW,0Aug,18),DAM(MED,0Sept,3)},
	/*bfield*/	 FIL_1_AFMARTLE,
	/*detail*/	{FIL_1_M1MARTLE},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_1_TXMARTLE,
	/*maxonaf*/	2,
	/*nextsat*/	UID_AF_STAPLEFORD,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_NORTHWEALD,
			},

	/*name*/{UID_AF_STAPLEFORD,
	/*real*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,0,AB(LOW,NONE),
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,-1,
	/*turn pt*/	{UID_Northfleet,UID_Basildon,UID_AF_CROYDON},
	/*sec trg*/	{UID_AF_NORTHWEALD},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/	{DAM(NONE)},
	/*bfield*/	 FIL_1_AFSTAPLE,
	/*detail*/	{FIL_1_M1STAPLE},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_1_TXSTAPLE,
	/*maxonaf*/	1,
	/*nextsat*/	UID_NULL,
	/*loc*/		LOC_COAST,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_NORTHWEALD,
			},

	//------------------------
	//KENLEY SECTOR SATELLITES


	/*name*/{UID_AF_CROYDON,
	/*real*/	TT_FIGHTERAF,TP_PRIMARYINLANDAF,0,AB(MED,LOW),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,-1,
	/*turn pt*/	{UID_Crawley,UID_CV_TUNBRIDGEWELLS,UID_CV_MAIDSTONE},//MS 10Mar00
	/*sec trg*/	{UID_AF_KENLEY,UID_AF_BIGGINHILL,UID_FA_KingstonHawker},
	/*damage*/ 	&DR_SmallAF,
//TempCode MS 05Oct00 	/*dates*/	{DAM(OUT,0Aug,15),DAM(MED,0Aug,16),DAM(MED,0Aug,17),DAM(LOW,0Aug,18),DAM(MED,0Aug,31)},
//TempCode MS 15Nov00 	/*dates*/	{DAM(OUT,0Aug,15),DAM(MED,0Aug,18),DAM(LOW,0Aug,23),DAM(MED,0Aug,31),DAM(LOW,0Aug,6)},
	/*dates*/	{DAM(LOW,0Aug,18),DAM(MED,0Aug,31),DAM(LOW,0Aug,6)},
	/*bfield*/	 FIL_1_AFCROYDO,
	/*detail*/	{FIL_1_M1CROYDO},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_1_TXCROYDO,
	/*maxonaf*/	2,
	/*nextsat*/	UID_NULL,
	/*loc*/		LOC_S_LON,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_KENLEY,
			},

	//------------------------
	//HORNCHURCH SECTOR SATELLITES


	/*name*/{UID_AF_ROCHFORD,
	/*real*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,0,AB(LOW,NONE),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,-1,
	/*turn pt*/	{UID_NV_NORTHGOODWIN,UID_CV_MAIDSTONE,UID_Cranbrook},
	/*sec trg*/	{UID_CH_Canewdon},
	/*damage*/ 	&DR_SmallAF,
//TempCode MS 05Oct00 	/*dates*/	{DAM(OUT,0Aug,15),DAM(NONE,0Aug,18),DAM(MED,0Aug,28),DAM(NONE,0Aug,30)},
//TempCode MS 15Nov00 	/*dates*/	{DAM(OUT,0Aug,15),DAM(LOW,0Aug,18),DAM(MED,0Aug,28),DAM(MED,0Aug,30)},
	/*dates*/	{DAM(LOW,0Aug,18),DAM(MED,0Aug,28),DAM(MED,0Aug,30)},
	/*bfield*/	 FIL_1_AFROCHFO,
	/*detail*/	{FIL_1_M1ROCHFO},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_1_TXROCHFO,
	/*maxonaf*/	1,
	/*nextsat*/	UID_NULL,
	/*loc*/		LOC_COAST,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_HORNCHURCH,
			},

	//------------------------
	//FILTON SECTOR SATELLITES


	/*name*/{UID_AF_COLERNE,
	/*real*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,0,AB(LOW,NONE),
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,-1,
	/*turn pt*/	{UID_CV_Yeovil,UID_CV_Salisbury,UID_CV_BRISTOL},
	/*sec trg*/	{UID_AF_FILTON,UID_FA_BristolAeroplane,UID_FA_BristolAeroEngine,UID_FA_Parnall,UID_DK_Bristol},
	/*damage*/ 	&DR_SmallAF,
//TempCode MS 05Oct00 	/*dates*/	{DAM(LOW,0Aug,14),DAM(NONE,0Aug,16)},
	/*dates*/	{DAM(LOW,0Aug,14)},
	/*bfield*/	 FIL_1_AFCOLERN,
	/*detail*/	{FIL_1_M1COLERN},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_1_TXCOLERN,
	/*maxonaf*/	1,
	/*nextsat*/	UID_AF_PEMBREY,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_FILTON,
			},

	/*name*/{UID_AF_PEMBREY,
	/*real*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,0,AB(LOW,NONE),
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_AFPEMBRE,
	/*detail*/	{FIL_1_M1PEMBRE},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_1_TXPEMBRE,
	/*maxonaf*/	1,
	/*nextsat*/	UID_AF_EXETER,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_FILTON,
			},

	/*name*/{UID_AF_EXETER,
	/*real*/	TT_FIGHTERAF,TP_NON_GR11_PRIMARYAF,0,AB(LOW,NONE),
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_PRIMARYAF,-1,
	/*turn pt*/	{UID_TORQUAY,UID_CL_WestPrawle,UID_NB_Portland},
	/*sec trg*/	{UID_DK_Plymouth},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_AFEXETER,
	/*detail*/	{FIL_1_M1EXETER},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_1_TXEXETER,
	/*maxonaf*/	2,
	/*nextsat*/	UID_NULL,	//UID_AF_STEVAL,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_FILTON,
			},

//DEADCODE DAW 18/02/00 	/*name*/{UID_AF_STEVAL,
//DEADCODE DAW 18/02/00 	/*real*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,0,AB(LOW,MED),
//DEADCODE DAW 18/02/00 	/*false*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,-1,
//DEADCODE DAW 18/02/00 	/*turn pt*/	{UID_NULL},
//DEADCODE DAW 18/02/00 	/*sec trg*/	{UID_CL_DryTree,UID_IN_Falmouth,UID_CL_RameHead,UID_DK_Plymouth,UID_CH_HawksTor},
//DEADCODE DAW 18/02/00 	/*damage*/ 	&DR_SmallAF,
//DEADCODE DAW 18/02/00 	/*dates*/		{DAM(NONE)},
//DEADCODE DAW 18/02/00 	/*bfield*/	 FIL_1_AFSTEVAL,
//DEADCODE DAW 18/02/00 	/*detail*/	{FIL_1_M1STEVAL},
//DEADCODE DAW 18/02/00 	/*detail2*/	{FIL_NULL},
//DEADCODE DAW 18/02/00 	/*taxi*/	FIL_1_TXSTEVAL,
//DEADCODE DAW 18/02/00 	/*maxonaf*/	2,
//DEADCODE DAW 18/02/00 	/*nextsat*/	UID_NULL,
//DEADCODE DAW 18/02/00 	/*loc*/		LOC_N_LON,
//DEADCODE DAW 18/02/00 	/*zeros*/	{0,0,0},
//DEADCODE DAW 18/02/00 	/*main*/	UID_AF_FILTON,
//DEADCODE DAW 18/02/00 			},
//DEADCODE DAW 18/02/00 
//DEADCODE DAW 18/02/00 
	//------------------------
	//MIDDLE WALLOP SECTOR SATELLITES


	/*name*/{UID_AF_WARMWELL,
	/*real*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,0,AB(LOW,NONE),
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,-1,
	/*turn pt*/	{UID_DURISTN,UID_PORTLAND,UID_BOURNEMOUTH},
	/*sec trg*/	{UID_FA_Westland},
	/*damage*/ 	&DR_SmallAF,
//TempCode MS 05Oct00 	/*dates*/	{DAM(LOW,0Aug,13),DAM(NONE,0Aug,15),DAM(LOW,0Aug,25),DAM(NONE,0Aug,27)},
	/*dates*/	{DAM(MED,0Aug,25),DAM(LOW,0Aug,27)},
	/*bfield*/	 FIL_1_AFWARMWE,
	/*detail*/	{FIL_1_M1WARMWE},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_1_TXWARMWE,
	/*maxonaf*/	1,
	/*nextsat*/	UID_NULL,
	/*loc*/		LOC_COAST,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_MIDDLEWALLOP,
			},

	//------------------------
	//DUXFORD SECTOR SATELLITES


	/*name*/{UID_AF_FOWLMERE,
	/*real*/	TT_FIGHTERAF,TP_NON_GR11_PRIMARYAF,0,AB(LOW,NONE),
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_PRIMARYAF,-1,
	/*turn pt*/	{UID_CV_COLCHESTER,UID_CV_HERTFORD,UID_CV_CHELMSFORD},
	/*sec trg*/	{UID_AF_DUXFORD,UID_AF_DEBDEN},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_AFFOWLME,
	/*detail*/	{FIL_1_M1FOWLME},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_1_TXFOWLME,
	/*maxonaf*/	1,
	/*nextsat*/	UID_NULL,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*main*/	UID_AF_DUXFORD,
			},

		//next item:


		{UID_NULL}
	};
	II_TargetSectorField	NodeData::sectors[]=
	{
	/*name*/{UID_AF_TANGMERE,//type,priority,	damage=0/-1,defenses
	/*real*/	TT_FIGHTERAF,TP_PRIMARYCOASTALAF,0,AAA_MED,
	/*false*/	TT_FIGHTERAF,TP_PRIMARYCOASTALAF,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_AF_WESTHAMPNETT,UID_AF_THORNEYISLAND,UID_AF_FORD,UID_CL_Poling,UID_AF_SHOREHAM},
	/*damage*/ 	&DR_LargeAF,
//TempCode MS 05Oct00 	/*dates*/	{DAM(OUT,0Aug,16),DAM(NONE,0Aug,18)},
	/*dates*/	{DAM(MED,0Aug,16)},
	/*bfield*/	 FIL_1_AFTANGME,
	/*detail*/	{FIL_1_M1TANGME},
	/*detail2*/	{FIL_1_M2TANGME,FIL_1_M3TANGME},
	/*taxi*/	FIL_1_TXTANGME,
	/*maxonaf*/	3,												//MS 14Nov00
	/*1stsat*/	UID_AF_WESTHAMPNETT,
	/*loc*/		LOC_COAST,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_TANGMERE,UID_CC_TANGMERE_BACKUP,//ST JAMES SCHOOL
	/*names*/	IDS_SECTOR_A,IDS_GROUP_11,
	/*insect*/	1,4												//MS 14Nov00
			},		

	/*name*/{UID_AF_BIGGINHILL,
	/*real*/	TT_FIGHTERAF,TP_PRIMARYINLANDAF,0,AAA_HIGH,
	/*false*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,-1,
	/*turn pt*/	{UID_CV_TUNBRIDGEWELLS,UID_CV_REDHILL,UID_CV_MAIDSTONE},
	/*sec trg*/	{UID_AF_CROYDON,UID_AF_KENLEY,UID_AF_WESTMALLING},
	/*damage*/ 	&DR_LargeAF,
//TempCode MS 05Oct00 	/*dates*/	{DAM(LOW,0Aug,18),DAM(NONE,0Aug,19),DAM(MED,0Aug,30),DAM(MED,0Aug,31),DAM(OUT,0Sept,1),DAM(MED,0Sept,2)},//,DAM(NONE,0Sept,4),DAM(LOW,0Sept,5),DAM(NONE,0Sept,7)},
	/*dates*/	{DAM(LOW,0Aug,18),DAM(LOW,0Aug,23),DAM(OUT,0Aug,30)},
	/*bfield*/	 FIL_1_AFBIGHIL,
	/*detail*/	{FIL_1_M1BIGGHI},
	/*detail2*/	{FIL_1_M2BIGGHI,FIL_1_M3BIGGHI},
	/*taxi*/	FIL_1_TXBIGGHI,
	/*maxonaf*/	3,
	/*1stsat*/	UID_AF_GRAVESEND,
	/*loc*/		LOC_S_LON,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_BIGGINHILL,UID_CC_BIGGINHILL_BACKUP,	//TOWERFIELD
	/*names*/	IDS_SECTOR_C,IDS_GROUP_11,
	/*insect*/	1,9													//MS 15Nov100
			},

	/*name*/{UID_AF_NORTHWEALD,//type,priority,	damage=0/-1,defenses
	/*real*/	TT_FIGHTERAF,TP_PRIMARYINLANDAF,0,AAA_MED,
	/*false*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,-1,
	/*turn pt*/	{UID_Northfleet,UID_Basildon,UID_AF_CROYDON},
	/*sec trg*/	{UID_AF_STAPLEFORD,UID_AF_HORNCHURCH},
	/*damage*/ 	&DR_LargeAF,
//TempCode MS 05Oct00 	/*dates*/	{DAM(OUT,0Aug,24),DAM(LOW,0Aug,25),DAM(NONE,0Aug,26),DAM(MED,0Aug,31),DAM(NONE,0Sept,1),DAM(OUT,0Sept,3),DAM(LOW,0Sept,4),DAM(NONE,0Sept,5)},
	/*dates*/	{DAM(MED,0Aug,24),DAM(MED,0Aug,31)},
	/*bfield*/	 FIL_1_AFNORTHW,
	/*detail*/	{FIL_1_M1NORTHW},
	/*detail2*/	{FIL_1_M2NORTHW,FIL_1_M3NORTHW},
	/*taxi*/	FIL_1_TXNORTHW,
	/*maxonaf*/	3,
	/*1stsat*/	UID_AF_MARTLESHAM,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_NORTHWEALD,UID_CC_NORTHWEALD_BACKUP,
	/*names*/	IDS_SECTOR_E,IDS_GROUP_11,
	/*insect*/	1,5
			},		

	/*name*/{UID_AF_KENLEY,//type,priority,	damage=0/-1,defenses
	/*real*/	TT_FIGHTERAF,TP_PRIMARYINLANDAF,0,AAA_HIGH,
	/*false*/	TT_FIGHTERAF,TP_PRIMARYINLANDAF,-1,
	/*turn pt*/	{UID_Cuckfield,UID_CV_TUNBRIDGEWELLS,UID_CV_MAIDSTONE},//MS 10Mar00
	/*sec trg*/	{UID_AF_CROYDON,UID_AF_BIGGINHILL},
	/*damage*/ 	&DR_LargeAF,
//TempCode MS 05Oct00 	/*dates*/	{DAM(OUT,0Aug,18),DAM(NONE,0Aug,21),DAM(LOW,0Sept,2),DAM(NONE,0Sept,3)},
//DeadCode MS 15Nov100 	/*dates*/	{DAM(LOW,0Aug,23)},
	/*dates*/	{DAM(NONE)},									//MS 15Nov00
	/*bfield*/	 FIL_1_AFKENLEY,
	/*detail*/	{FIL_1_M1KENLEY},
	/*detail2*/	{FIL_1_M2KENLEY,FIL_1_M3KENLEY},
	/*taxi*/	FIL_1_TXKENLEY,
	/*maxonaf*/	3,
	/*1stsat*/	UID_AF_CROYDON,
	/*loc*/		LOC_S_LON,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_KENLEY,UID_CC_KENLEY_BACKUP,
	/*names*/	IDS_SECTOR_B,IDS_GROUP_11,
	/*insect*/	1,5
			},		
			
	/*name*/{UID_AF_HORNCHURCH,//type,priority,	damage=0/-1,defenses
	/*real*/	TT_FIGHTERAF,TP_PRIMARYINLANDAF,0,AAA_HIGH,
	/*false*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,-1,
	/*turn pt*/	{UID_CV_MAIDSTONE,UID_CV_TUNBRIDGEWELLS,UID_CanveyIsland},
//DeadCode MS 15Oct00 	/*sec trg*/	{UID_AF_STAPLEFORD,UID_AF_NORTHWEALD,UID_IN_Beckton,UID_IN_ThamesHaven,UID_IN_Purfleet},
	/*sec trg*/	{UID_AF_STAPLEFORD,UID_AF_NORTHWEALD},
	/*damage*/ 	&DR_LargeAF,
//TempCode MS 05Oct00 	/*dates*/		{DAM(LOW,0Aug,31),DAM(NONE,0Aug,31),DAM(LOW,0Sept,2),DAM(NONE,0Sept,3)},
	/*dates*/		{DAM(LOW,0Aug,31)},
	/*bfield*/	 FIL_1_AFHORNCH,
	/*detail*/	{FIL_1_M1HORNCH},
	/*detail2*/	{FIL_1_M2HORNCH,FIL_1_M3HORNCH},
	/*taxi*/	FIL_1_TXHORNCH,
	/*maxonaf*/	3,												//MS 14Nov00
	/*1stsat*/	UID_AF_ROCHFORD,
	/*loc*/		LOC_S_LON,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_HORNCHURCH,UID_CC_HORNCHURCH_BACKUP,
	/*names*/	IDS_SECTOR_D,IDS_GROUP_11,
	/*insect*/	1,4												//MS 14Nov00
			},		

	/*name*/{UID_AF_DEBDEN,//type,priority,	damage=0/-1,defenses
	/*real*/	TT_FIGHTERAF,TP_PRIMARYINLANDAF,0,AAA_MED,
	/*false*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,-1,
	/*turn pt*/	{UID_CV_CHELMSFORD,UID_CV_HERTFORD,UID_Basildon},
	/*sec trg*/	{UID_AF_FOWLMERE,UID_AF_DUXFORD},
	/*damage*/ 	&DR_LargeAF,
//TempCode MS 05Oct00 	/*dates*/		{DAM(MED,0Aug,26),DAM(NONE,0Aug,28),DAM(MED,0Aug,31),DAM(NONE,0Sept,2)},
	/*dates*/		{DAM(MED,0Aug,26),DAM(MED,0Aug,31)},
	/*bfield*/	 FIL_1_AFDEBDEN,
	/*detail*/	{FIL_1_M1DEBDEN},
	/*detail2*/	{FIL_1_M2DEBDEN,FIL_1_M3DEBDEN},
	/*taxi*/	FIL_1_TXDEBDEN,
	/*maxonaf*/	3,
	/*1stsat*/	UID_NULL,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_DEBDEN,UID_CC_DEBDEN_BACKUP,
	/*names*/	IDS_SECTOR_F,IDS_GROUP_11,
	/*insect*/	1,3
			},		

	/*name*/{UID_AF_NORTHOLT,//type,priority,	damage=0/-1,defenses
	/*real*/	TT_FIGHTERAF,TP_PRIMARYINLANDAF,0,AAA_MED,
	/*false*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,-1,
	/*turn pt*/	{UID_CV_FARNBOROUGH,UID_CV_REDHILL,UID_AF_CROYDON},
	/*sec trg*/	{UID_AF_STAPLEFORD,UID_AF_NORTHWEALD,UID_AF_GRAVESEND,UID_AF_HORNCHURCH,UID_FA_LangleyHawker},
	/*damage*/ 	&DR_LargeAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_AFNORTHO,
	/*detail*/	{FIL_1_M1NORTHO},
	/*detail2*/	{FIL_1_M2NORTHO,FIL_1_M3NORTHO},
	/*taxi*/	FIL_1_TXNORTHO,
	/*maxonaf*/	3,
	/*1stsat*/	UID_NULL,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_NORTHOLT,UID_CC_NORTHOLT_BACKUP,
	/*names*/	IDS_SECTOR_Z,IDS_GROUP_11,
	/*insect*/	1,3
			},		

	//------------------------
	//GROUP 10 SECTOR STATIONS


	/*name*/{UID_AF_FILTON,//type,priority,	damage=0/-1,defenses
	/*real*/	TT_FIGHTERAF,TP_NON_GR11_PRIMARYAF,0,AAA_MED,
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_PRIMARYAF,-1,
	/*turn pt*/	{UID_Bath,UID_WestonSuperMare,UID_CV_Yeovil},
	/*sec trg*/	{UID_FA_BristolAeroplane,UID_FA_BristolAeroEngine,UID_FA_Parnall,UID_DK_Bristol},
	/*damage*/ 	&DR_LargeAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_AFFILTON,
	/*detail*/	{FIL_1_M1FILTON},
	/*detail2*/	{FIL_1_M2FILTON,FIL_1_M3FILTON},
	/*taxi*/	FIL_1_TXFILTON,
	/*maxonaf*/	1,
	/*1stsat*/	UID_AF_COLERNE,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_FILTON,UID_CC_FILTON_BACKUP,
	/*names*/	IDS_SECTOR_W,IDS_GROUP_10,
	/*insect*/	1,5
			},		

	/*name*/{UID_AF_MIDDLEWALLOP,//type,priority,	damage=0/-1,defenses
	/*real*/	TT_FIGHTERAF,TP_NON_GR11_PRIMARYAF,0,AAA_MED,
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_AF_WORTHYDOWN,UID_AF_BOSCOMBEDOWN,UID_AF_ANDOVER},
	/*damage*/ 	&DR_LargeAF,
//TempCode MS 05Oct00 	/*dates*/		{DAM(MED,0Aug,14),DAM(LOW,0Aug,15),DAM(NONE,0Aug,16)},
	/*dates*/		{DAM(LOW,0Aug,15)},
	/*bfield*/	 FIL_1_AFMIDDLE,
	/*detail*/	{FIL_1_M1MIDDLE},
	/*detail2*/	{FIL_1_M2MIDDLE,FIL_1_M3MIDDLE},
	/*taxi*/	FIL_1_TXMIDDLE,
	/*maxonaf*/	3,
	/*1stsat*/	UID_AF_WARMWELL,
	/*loc*/		LOC_S_LON,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_MIDDLEWALLOP,UID_CC_MIDDLEWALLOP_BACKUP,
	/*names*/	IDS_SECTOR_Y,IDS_GROUP_10,
	/*insect*/	1,4
			},		

	//------------------------
	//GROUP 12 SECTOR STATIONS


	/*name*/{UID_AF_DUXFORD,//type,priority,	damage=0/-1,defenses
	/*real*/	TT_FIGHTERAF,TP_NON_GR11_PRIMARYAF,0,AAA_MED,
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_PRIMARYAF,-1,
	/*turn pt*/	{UID_CV_COLCHESTER,UID_CV_LUTON,UID_CV_CHELMSFORD},
	/*sec trg*/	{UID_AF_FOWLMERE,UID_AF_DEBDEN},
	/*damage*/ 	&DR_LargeAF,
//TempCode MS 05Oct00 	/*dates*/		{DAM(LOW,0Aug,31),DAM(NONE,0Sept,2)},
	/*dates*/		{DAM(LOW,0Aug,31)},
	/*bfield*/	 FIL_1_AFDUXFOR,
	/*detail*/	{FIL_1_M1DUXFOR},
	/*detail2*/	{FIL_1_M2DUXFOR,FIL_1_M3DUXFOR},
	/*taxi*/	FIL_1_TXDUXFOR,
	/*maxonaf*/	2,
	/*1stsat*/	UID_AF_FOWLMERE,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_DUXFORD,UID_CC_DUXFORD_BACKUP,
	/*names*/	IDS_SECTOR_G,IDS_GROUP_12,
	/*insect*/	1,3
			},		

	/*name*/{UID_AF_COLTISHALL,//type,priority,	damage=0/-1,defenses
	/*real*/	TT_FIGHTERAF,TP_NON_GR11_PRIMARYAF,0,AAA_MED,
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_FA_BoultonPaul,UID_CL_Happisburgh,UID_CH_WestBeckham},
	/*damage*/ 	&DR_LargeAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_AFCOLTIS,
	/*detail*/	{FIL_1_M1COLTIS},
	/*detail2*/	{FIL_1_M2COLTIS,FIL_1_M3COLTIS},
	/*taxi*/	FIL_1_TXCOLTIS,
	/*maxonaf*/	3,
	/*1stsat*/	UID_NULL,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_COLTISHALL,UID_CC_COLTISHALL_BACKUP,
	/*names*/	IDS_SECTOR_J,IDS_GROUP_12,
	/*insect*/	1,3
			},		

	/*name*/{UID_AF_WITTERING,//type,priority,	damage=0/-1,defenses
	/*real*/	TT_FIGHTERAF,TP_NON_GR11_PRIMARYAF,0,AAA_MED,
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_LargeAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_AFWITTER,
	/*detail*/	{FIL_1_M1WITTER},
	/*detail2*/	{FIL_1_M2WITTER,FIL_1_M3WITTER},
	/*taxi*/	FIL_1_TXWITTER,
	/*maxonaf*/	3,
	/*1stsat*/	UID_NULL,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_WITTERING,UID_CC_WITTERING_BACKUP,
	/*names*/	IDS_SECTOR_K,IDS_GROUP_12,
	/*insect*/	1,3
			},

	/*name*/{UID_AF_KIRTON,//type,priority,	damage=0/-1,defenses
	/*real*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,0,AAA_MED,
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_AF_DIGBY},
	/*damage*/ 	&DR_LargeAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_AFKIRTON,
	/*detail*/	{FIL_1_M1KIRTON},
	/*detail2*/	{FIL_1_M2KIRTON,FIL_1_M3KIRTON},
	/*taxi*/	FIL_1_TXKIRTON,
	/*maxonaf*/	2,
	/*1stsat*/	UID_NULL,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_KIRTON,UID_CC_KIRTON_BACKUP,
	/*names*/	IDS_SECTOR_M,IDS_GROUP_12,
	/*insect*/	0,2
			},

	/*name*/{UID_AF_DIGBY,//type,priority,	damage=0/-1,defenses
	/*real*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,0,AAA_MED,
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_AF_KIRTON},
	/*damage*/ 	&DR_LargeAF,
	/*dates*/	{DAM(NONE)},
	/*bfield*/	FIL_1_AFDIGBY,
	/*detail*/	{FIL_1_M1DIGBY},
	/*detail2*/	{FIL_1_M2DIGBY,FIL_1_M3DIGBY},
	/*taxi*/	FIL_1_TXDIGBY,
	/*maxonaf*/	3,
	/*1stsat*/	UID_NULL,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_DIGBY,UID_CC_DIGBY_BACKUP,
	/*names*/	IDS_SECTOR_L,IDS_GROUP_12,
	/*insect*/	0,3
			},

			//Group 13 sector station
	/*name*/{UID_AF_NEWCASTLE,//type,priority,	damage=0/-1,defenses
	/*real*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,0,AAA_MED,
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_LargeAF,
	/*dates*/	{DAM(NONE)},
	/*bfield*/	FIL_NULL,
	/*detail*/	{FIL_NULL},
	/*detail2*/	{FIL_NULL},
	/*taxi*/	FIL_NULL,
	/*maxonaf*/	3,
	/*1stsat*/	UID_NULL,
	/*loc*/		LOC_N_LON,
	/*zeros*/	{0,0,0},
	/*centres*/	UID_CC_WITTERING,UID_CC_WITTERING_BACKUP,
	/*names*/	IDS_SECTOR_P,IDS_GROUP_13,
	/*insect*/	10,15
			},		

			//next item:

		{UID_NULL}
	};
	II_TargetNoDetail		NodeData::nodetails[]=
	{


		{UID_NULL}
	};
	II_TargetGroup			NodeData::groups[]=
	{
	//*********************************************************************
	//LUFTWAFFE AIRFIELDS FIGHTER LF2

	/*name*/{UID_AF_Abbeville,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFABBEVI,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Arques,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFARQUES,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Audembert,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFAUDEMB,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Barley,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFBARLEY,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Caffiers,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFCAFFIE,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Cocquelles,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFCOCQUE,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Colombert,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFCOLOMB,
	/*detail*/	{FIL_NULL},
			},

//DeadCode MS 10Mar00 	/*name*/{UID_AF_Crechy,
//DeadCode MS 10Mar00 	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,AB(LOW,HIGH),
//DeadCode MS 10Mar00 	/*false*/	TT_GERMAN,TP_PRIMARYINLANDAF,-1,
//DeadCode MS 10Mar00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*damage*/ 	&DR_SmallAF,
//DeadCode MS 10Mar00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 10Mar00 	/*bfield*/	 FIL_1_GFCRECHY,
//DeadCode MS 10Mar00 	/*detail*/	{FIL_NULL},
//DeadCode MS 10Mar00 			},

	/*name*/{UID_AF_Desvres,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFDESVRE,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Guines,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFGUINES,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Hermelinghen,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFHERMEL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Laval,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SW,  //CHECK POS?
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFLAVAL,
			},

	/*name*/{UID_AF_Marck,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFMARCK,
			},

	/*name*/{UID_AF_Marquise,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFMARQUI,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Peuplingues,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFPEUPLI,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Samer,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFSAMER,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_StOmer,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFSTOMER,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Wissant,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFWISSAN,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Yvrench,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFYVRENC,
	/*detail*/	{FIL_NULL},
			},

//DeadCode MS 10Mar00 	/*name*/{UID_AF_PasdeCalais,
//DeadCode MS 10Mar00 	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,AB(LOW,HIGH),
//DeadCode MS 10Mar00 	/*false*/	TT_GERMAN,TP_PRIMARYINLANDAF,-1,
//DeadCode MS 10Mar00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*damage*/ 	&DR_SmallAF,
//DeadCode MS 10Mar00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 10Mar00 	/*bfield*/	 FIL_1_GFPASDEC,
//DeadCode MS 10Mar00 	/*detail*/	{FIL_NULL},
//DeadCode MS 10Mar00 			},

	/*name*/{UID_AF_Tramecourt,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFTRAMEC,
	/*detail*/	{FIL_NULL},
			},

	//*************************************************************************
	//LUFTWAFFE AIRFIELDS FIGHTER LF3

	/*name*/{UID_AF_Amiens,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFAMIENS,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_BeaumontLeRoger,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFBEAUMO,
	/*detail*/	{FIL_NULL},
			},

//DeadCode MS 10Mar00 	/*name*/{UID_AF_Brest,
//DeadCode MS 10Mar00 	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,AB(LOW,HIGH),
//DeadCode MS 10Mar00 	/*false*/	TT_GERMAN,TP_PRIMARYINLANDAF,-1,
//DeadCode MS 10Mar00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*damage*/ 	&DR_SmallAF,
//DeadCode MS 10Mar00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 10Mar00 	/*bfield*/	 FIL_1_GFBREST,
//DeadCode MS 10Mar00 	/*detail*/	{FIL_NULL},
//DeadCode MS 10Mar00 		},

	/*name*/{UID_AF_Caen,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SW,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFCAEN,
	/*detail*/	{FIL_NULL},
		},

	/*name*/{UID_AF_Carquebut,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SW,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFCARQUE,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Crepon,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SW,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFCREPON,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Dinan,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SW,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFDINAN,
	/*detail*/	{FIL_NULL}
			},

	/*name*/{UID_AF_Guyancourt,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFGUYANC,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_LeHarve,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SW,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFLEHARV,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Plumetot,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SW,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFPLUMET,
	/*detail*/	{FIL_NULL},
			},

//DeadCode MS 10Mar00 	/*name*/{UID_AF_Angers,
//DeadCode MS 10Mar00 	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,AB(LOW,HIGH),
//DeadCode MS 10Mar00 	/*false*/	TT_GERMAN,TP_PRIMARYINLANDAF,-1,
//DeadCode MS 10Mar00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*damage*/ 	&DR_SmallAF,
//DeadCode MS 10Mar00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 10Mar00 	/*bfield*/	 FIL_1_GFANGERS,
//DeadCode MS 10Mar00 	/*detail*/	{FIL_NULL},
//DeadCode MS 10Mar00 			},

	/*name*/{UID_AF_Lannion,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SW,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFLANNIO,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_StMalo,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SW,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFSTMALO,
	/*detail*/	{FIL_NULL},
			},

	//****************************************************************************
	//LUFTWAFFE BOMBERS LF 2

	/*name*/{UID_AF_AmsterdamSchipol,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_NE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFAMSTER,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_AntwerpDeurne,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_NE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFANTWER,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Arras,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFARRAS,
	/*detail*/	{FIL_NULL},
		},

	/*name*/{UID_AF_Beauvais,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFBEAUVA,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Cambrai,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFCAMBRA,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_CormeillesEnVexin,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFCORMEI,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Creil,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFCREIL,
	/*detail*/	{FIL_NULL}
		},

	/*name*/{UID_AF_Eindhoven,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_NE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFEINDHO,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Epinoy,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFEPINOY,
	/*detail*/	{FIL_NULL},
			},

//DeadCode MS 10Mar00 	/*name*/{UID_AF_LeCulot,
//DeadCode MS 10Mar00 	/*real*/	TT_GERMANBOMBERAF,TP_PRIMARYINLANDAF,0,AB(LOW,HIGH),
//DeadCode MS 10Mar00 	/*false*/	TT_GERMANBOMBERAF,TP_PRIMARYINLANDAF,-1,
//DeadCode MS 10Mar00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*damage*/ 	&DR_SmallAF,
//DeadCode MS 10Mar00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 10Mar00 	/*bfield*/	 FIL_1_GFLECULO,
//DeadCode MS 10Mar00 	/*detail*/	{FIL_NULL},
//DeadCode MS 10Mar00 			},

	/*name*/{UID_AF_Lille,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFLILLE,
	/*detail*/	{FIL_NULL}
		},

	/*name*/{UID_AF_Montdidier,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFMONTDI,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_RosieresEnSanterre,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_C,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFROSIER,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_StTrond,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_NE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFSTTRON,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Soesterberg,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_NE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFSOESTE,
	/*detail*/	{FIL_NULL},
			},

	//**************************************************************************
	//LUFTWAFFE AIRFIELDS BOMBERS LF3

	/*name*/{UID_AF_Chateaudun,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFCHATEA,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Chartres,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFCHARTR,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Dinard,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SW,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFDINARD,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Dreux,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFDREUX,
	/*detail*/	{FIL_NULL},
		},

	/*name*/{UID_AF_Etampes,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFETAMPE,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Rennes,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SW,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFRENNES,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Evreaux,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFEVREAU,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_MelunVillaroche,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFMELUNV,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_OrleansBricy,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SW,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFORLEAN,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_Orly,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFORLY,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_AF_StAndreDeLEure,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFSTANDR,
	/*detail*/	{FIL_NULL},
			},

//DeadCode MS 10Mar00 	/*name*/{UID_AF_Tours,
//DeadCode MS 10Mar00 	/*real*/	TT_GERMANBOMBERAF,TP_PRIMARYINLANDAF,0,AB(LOW,HIGH),
//DeadCode MS 10Mar00 	/*false*/	TT_GERMANBOMBERAF,TP_PRIMARYINLANDAF,-1,
//DeadCode MS 10Mar00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*damage*/ 	&DR_SmallAF,
//DeadCode MS 10Mar00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 10Mar00 	/*bfield*/	 FIL_1_GFTOURS,
//DeadCode MS 10Mar00 	/*detail*/	{FIL_NULL}
//DeadCode MS 10Mar00 		},

	/*name*/{UID_AF_Villacoublay,
	/*real*/	TT_GERMAN,TP_PRIMARYINLANDAF,0,DEF_LW_SE,
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,0,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_GFVILLAC,
	/*detail*/	{FIL_NULL},
			},

	//NON-FIGHTER RAF AIRFIELDS ------------------------------------------

	/*name*/{UID_AF_BOSCOMBEDOWN,
	/*real*/	TT_OTHERAF,TP_OTHERAF,0,AB(MED,NONE),
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,-1,
	/*turn pt*/	{UID_CV_WINCHESTER,UID_CV_SOUTHAMPTON,UID_BOURNEMOUTH},
	/*sec trg*/	{UID_AF_MIDDLEWALLOP,UID_AF_ANDOVER},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_AFBOSCOM,
	/*detail*/	{FIL_1_M1BOSCOM},
			},

	/*name*/{UID_AF_DETLING,
	/*real*/	TT_NAVALAF,TP_NAVALAF,0,AB(MED,NONE),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYCOASTALAF,-1,
	/*turn pt*/	{UID_Cranbrook,UID_CV_FOLKESTONE,UID_CV_CANTERBURY},
	/*sec trg*/	{UID_AF_WESTMALLING,UID_AF_GRAVESEND,UID_IN_Maidstone,UID_AF_EASTCHURCH,UID_FA_Pobjoy},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(OUT,0Aug,13),DAM(LOW,0Aug,15),DAM(NONE,0Aug,16),DAM(MED,0Aug,31),DAM(LOW,0Sept,2),DAM(LOW,0Sept,5),DAM(NONE,0Sept,7)},
	/*bfield*/	 FIL_1_AFDETLIN,
	/*detail*/	{FIL_1_M1DETLIN},
			},

	/*name*/{UID_AF_EASTCHURCH,
	/*real*/	TT_NAVALAF,TP_NAVALAF,0,AB(MED,NONE),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYCOASTALAF,-1,
	/*turn pt*/	{UID_NV_TONGUE,UID_CV_CANTERBURY,UID_CV_RYE},
	/*sec trg*/	{UID_DK_Sheerness,UID_CL_Whitstable,UID_AF_ROCHFORD,UID_AF_GRAVESEND,UID_AF_DETLING},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/	{DAM(OUT,0Aug,13),DAM(NONE,0Aug,14),DAM(MED,0Aug,15),DAM(NONE,0Aug,17),DAM(MED,0Aug,28),DAM(LOW,0Aug,31),DAM(MED,0Sept,2),DAM(LOW,0Sept,4)},//,DAM(NONE,0Sept,5)},
	/*bfield*/	 FIL_1_AFEASTCH,
	/*detail*/	{FIL_1_M1EASTCH},
			},

	/*name*/{UID_AF_GOSPORT,
	/*real*/	TT_NAVALAF,TP_NAVALAF,0,AB(MED,NONE),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYCOASTALAF,-1,
	/*turn pt*/	{UID_CV_BOGNORREGIS,UID_CV_ISLEOFWIGHT,UID_CV_CHICHESTER},
	/*sec trg*/	{UID_AF_LEEONSOLENT,UID_NB_Portsmouth,UID_DK_Southampton,UID_AF_THORNEYISLAND,UID_AF_WESTHAMPNETT},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(LOW,0Aug,16),DAM(MED,0Aug,18),DAM(NONE,0Aug,20)},
	/*bfield*/	 FIL_1_AFGOSPOR,
	/*detail*/	{FIL_1_M1GOSPOR},
			},

	/*name*/{UID_AF_THORNEYISLAND,
	/*real*/	TT_NAVALAF,TP_NAVALAF,0,AB(MED,NONE),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYCOASTALAF,-1,
	/*turn pt*/	{UID_CV_BOGNORREGIS,UID_CV_ISLEOFWIGHT,UID_Worthing},
	/*sec trg*/	{UID_AF_GOSPORT,UID_NB_Portsmouth,UID_AF_WESTHAMPNETT,UID_AF_TANGMERE,UID_AF_FORD},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(MED,0Aug,18),DAM(NONE,0Aug,20),DAM(LOW,0Aug,23),DAM(NONE,0Aug,25)},
	/*bfield*/	 FIL_1_AFTHORNE,
	/*detail*/	{FIL_1_M1THORNE},
			},

	/*name*/{UID_AF_ODIHAM,
	/*real*/	TT_OTHERAF,TP_OTHERAF,0,AB(MED,NONE),
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,-1,
	/*turn pt*/	{UID_CV_PETERSFIELD,UID_CV_MIDHURST,UID_Horsham},
	/*sec trg*/	{UID_AF_FARNBOROUGH,UID_FA_Farnborough},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(MED,0Aug,15),DAM(NONE,0Aug,18)},
	/*bfield*/	 FIL_1_AFODIHAM,
	/*detail*/	{FIL_1_M1ODIHAM},
			},

	/*name*/{UID_AF_FARNBOROUGH,
	/*real*/	TT_OTHERAF,TP_OTHERAF,0,AB(MED,NONE),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(LOW,0Aug,16),DAM(NONE,0Aug,19)},
	/*bfield*/	 FIL_1_AFFARNBO,
	/*detail*/	{FIL_1_M1FARNBO},
			},

	/*name*/{UID_AF_LEEONSOLENT,
	/*real*/	TT_NAVALAF,TP_NAVALAF,0,AB(MED,NONE),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYCOASTALAF,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_AF_GOSPORT,UID_NB_Portsmouth,UID_DK_Southampton,UID_AF_THORNEYISLAND,UID_AF_WESTHAMPNETT},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(OUT,0Aug,16),DAM(NONE,0Aug,19)},
	/*bfield*/	 FIL_1_AFLEEONS,
	/*detail*/	{FIL_1_M1LEEONS},
			},

	/*name*/{UID_AF_ANDOVER,
	/*real*/	TT_OTHERAF,TP_OTHERAF,0,AB(MED,NONE),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,-1,
	/*turn pt*/	{UID_CV_Salisbury,UID_CV_WINCHESTER,UID_CV_PORTSMOUTH},
	/*sec trg*/	{UID_AF_BOSCOMBEDOWN},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(LOW,0Aug,13),DAM(NONE,0Aug,15)},
	/*bfield*/	 FIL_1_AFANDOVE,
	/*detail*/	{FIL_1_M1ANDOVE},
			},

	/*name*/{UID_AF_WORTHYDOWN,
	/*real*/	TT_OTHERAF,TP_OTHERAF,0,AB(MED,NONE),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYINLANDAF,-1,
	/*turn pt*/	{UID_CV_ISLEOFWIGHT,UID_CV_PETERSFIELD,UID_CV_SOUTHAMPTON},
	/*sec trg*/	{UID_AF_ANDOVER,UID_AF_BOSCOMBEDOWN,UID_AF_MIDDLEWALLOP},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(LOW,0Aug,15),DAM(NONE,0Aug,18)},
	/*bfield*/	 FIL_1_AFWORTHY,
	/*detail*/	{FIL_1_M1WORTHY},
			},

	/*name*/{UID_AF_BRIZENORTON,
	/*real*/	TT_OTHERAF,TP_OTHERAF,0,AB(MED,NONE),
	/*false*/	TT_FIGHTERAF,TP_NON_GR11_SECONDARYAF,-1,
	/*turn pt*/	{UID_CV_SWINDON,UID_CV_ALTON,UID_CV_OXFORD},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(OUT,0Aug,16),DAM(MED,0Aug,18),DAM(LOW,0Aug,19),DAM(NONE,0Aug,20)},
	/*bfield*/	 FIL_1_AFBRIZEN,
	/*detail*/	{FIL_1_M1BRIZEN},
			},

	/*name*/{UID_AF_SHOREHAM,
	/*real*/	TT_NAVALAF,TP_NAVALAF,0,AB(MED,NONE),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYCOASTALAF,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_AF_FORD,UID_CL_Truleigh,UID_CL_Poling,UID_DK_Brighton,UID_AF_TANGMERE},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_AFSHOREH,
	/*detail*/	{FIL_1_M1SHOREH},
			},

	/*name*/{UID_AF_FORD,
	/*real*/	TT_OTHERAF,TP_OTHERAF,0,AB(MED,NONE),
	/*false*/	TT_FIGHTERAF,TP_SECONDARYCOASTALAF,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_AF_TANGMERE,UID_AF_WESTHAMPNETT,UID_CL_Poling,UID_AF_THORNEYISLAND,UID_AF_SHOREHAM},
	/*damage*/ 	&DR_SmallAF,
	/*dates*/		{DAM(MED,0Aug,18),DAM(NONE,0Aug,21)},
	/*bfield*/	 FIL_1_AFFORD,
	/*detail*/	{FIL_1_M1FORD},
			},
	//LANDMARKS ------------------------------------------
//DeadCode MS 02Feb00 	/*name*/{UID_IN_Thorpe,
//DeadCode MS 02Feb00 	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
//DeadCode MS 02Feb00 	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
//DeadCode MS 02Feb00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 02Feb00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 02Feb00 	/*damage*/ 	&DR_Normal,
//DeadCode MS 02Feb00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 02Feb00 	/*bfield*/	 FIL_1_INTHORPE,
//DeadCode MS 02Feb00 	/*detail*/	{FIL_1_M1THORPE},
//DeadCode MS 02Feb00 			},

	/*name*/{UID_CV_CHICHESTER,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_ISLEOFWIGHT,UID_CV_SOUTHAMPTON,UID_NULL},
	/*sec trg*/	{UID_CV_PORTSMOUTH,UID_CV_BOGNORREGIS,UID_CV_LITTLEHAMPTON},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_LITTLEHAMPTON,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_ISLEOFWIGHT,UID_CV_SOUTHAMPTON,UID_NULL},
	/*sec trg*/	{UID_CV_PORTSMOUTH,UID_CV_CHICHESTER,UID_CV_BOGNORREGIS},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_MIDHURST,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_BOURNEMOUTH,UID_CV_ISLEOFWIGHT,UID_CV_BOGNORREGIS},
	/*sec trg*/	{UID_CV_Salisbury,UID_CV_BASINGSTOKE,UID_CV_ALTON,UID_CV_GUILFORD},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_PETERSFIELD,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_BOURNEMOUTH,UID_CV_BOGNORREGIS,UID_CV_REDHILL},
	/*sec trg*/	{UID_CV_BASINGSTOKE,UID_CV_ALTON,UID_CV_MIDHURST,UID_CV_GUILFORD},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_ALTON,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_BOURNEMOUTH,UID_CV_LEWES,UID_CV_REDHILL},
	/*sec trg*/	{UID_CV_Salisbury,UID_CV_BASINGSTOKE,UID_CV_MIDHURST,UID_CV_GUILFORD},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_WHITCHURCH,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_BOURNEMOUTH,UID_CV_ISLEOFWIGHT,UID_CV_REDHILL},
	/*sec trg*/	{UID_CV_Salisbury,UID_CV_PETERSFIELD,UID_CV_MIDHURST,UID_CV_GUILFORD},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_Salisbury,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_BOGNORREGIS,UID_CV_LEWES,UID_CV_REDHILL},
	/*sec trg*/	{UID_CV_BASINGSTOKE,UID_CV_ALTON,UID_CV_PETERSFIELD},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_Yeovil,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_OXFORD,UID_PORTLAND,UID_CV_Salisbury},
	/*sec trg*/	{UID_CV_BRISTOL,UID_CV_Gloucester,UID_CV_SWINDON},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_Northampton,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LOWESTOFT,UID_CV_IPSWICH,UID_CV_HERTFORD},
	/*sec trg*/	{UID_CV_Bedford,UID_CV_CAMBRIDGE,UID_CV_NEWMARKET,UID_CV_BURYSTEDMUNDS,UID_CV_BRANDON},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_Bedford,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LOWESTOFT,UID_CV_IPSWICH,UID_CV_HERTFORD},
	/*sec trg*/	{UID_CV_Northampton,UID_CV_CAMBRIDGE,UID_CV_NEWMARKET,UID_CV_BURYSTEDMUNDS,UID_CV_BRANDON},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_Leicester,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LOWESTOFT,UID_CV_IPSWICH,UID_CV_HERTFORD},
	/*sec trg*/	{UID_CV_PETERBOROUGH,UID_CV_KINGSLYNN,UID_CV_NORWICH,UID_CV_Birmingham,UID_CV_Coventry},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_Gloucester,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_OXFORD,UID_PORTLAND,UID_CV_Salisbury},
	/*sec trg*/	{UID_CV_Yeovil,UID_CV_BRISTOL,UID_CV_SWINDON},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
//DeadCode MS 12May00 	/*name*/{UID_CV_CROYDON,
//DeadCode MS 12May00 	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
//DeadCode MS 12May00 	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
//DeadCode MS 12May00 	/*turn pt*/	{UID_NV_TONGUE,UID_NV_DUNGENESS,UID_CV_HASTINGS},
//DeadCode MS 12May00 	/*sec trg*/	{UID_CV_REDHILL,UID_CV_TUNBRIDGEWELLS,UID_CV_MAIDSTONE,UID_CV_SOUTHENDONSEA},
//DeadCode MS 12May00 	/*damage*/ 	&DR_Normal,
//DeadCode MS 12May00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 12May00 	/*bfield*/	 FIL_NULL,
//DeadCode MS 12May00 	/*detail*/	{FIL_NULL},
//DeadCode MS 12May00 			},
	/*name*/{UID_CV_BRANDON,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LOWESTOFT,UID_CV_IPSWICH,UID_CV_HERTFORD},
	/*sec trg*/	{UID_CV_Northampton,UID_CV_Bedford,UID_CV_CAMBRIDGE,UID_CV_NEWMARKET,UID_CV_BURYSTEDMUNDS},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_PETERBOROUGH,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LOWESTOFT,UID_CV_IPSWICH,UID_CV_HERTFORD},
	/*sec trg*/	{UID_CV_KINGSLYNN,UID_CV_NORWICH,UID_CV_Birmingham,UID_CV_Coventry,UID_CV_Leicester},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_BRISTOL,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_OXFORD,UID_PORTLAND,UID_CV_Salisbury},
	/*sec trg*/	{UID_CV_Yeovil,UID_CV_Gloucester,UID_CV_SWINDON},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_LUTON,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_AF_CROYDON,UID_CV_CHELMSFORD,UID_CV_GUILFORD},
	/*sec trg*/	{UID_CV_READING,UID_CV_OXFORD,UID_CV_MAIDENHEAD,UID_CV_AYLESBURY,UID_CV_HERTFORD},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_STALBANS,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_AF_CROYDON,UID_CV_CHELMSFORD,UID_CV_GUILFORD},
	/*sec trg*/	{UID_CV_READING,UID_CV_OXFORD,UID_CV_MAIDENHEAD,UID_CV_AYLESBURY,UID_CV_LUTON},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_AYLESBURY,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_AF_CROYDON,UID_CV_CHELMSFORD,UID_CV_GUILFORD},
	/*sec trg*/	{UID_CV_READING,UID_CV_OXFORD,UID_CV_MAIDENHEAD,UID_CV_STALBANS,UID_CV_HERTFORD},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_OXFORD,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_AF_CROYDON,UID_CV_CHELMSFORD,UID_CV_GUILFORD},
	/*sec trg*/	{UID_CV_READING,UID_CV_AYLESBURY,UID_CV_LUTON,UID_CV_STALBANS,UID_CV_HERTFORD},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_READING,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_AF_CROYDON,UID_CV_CHELMSFORD,UID_CV_GUILFORD},
	/*sec trg*/	{UID_CV_MAIDENHEAD,UID_CV_AYLESBURY,UID_CV_LUTON,UID_CV_STALBANS,UID_CV_HERTFORD},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_BURYSTEDMUNDS,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LOWESTOFT,UID_CV_IPSWICH,UID_CV_HERTFORD},
	/*sec trg*/	{UID_CV_Northampton,UID_CV_Bedford,UID_CV_CAMBRIDGE,UID_CV_NEWMARKET,UID_CV_BRANDON},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_NEWMARKET,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LOWESTOFT,UID_CV_IPSWICH,UID_CV_HERTFORD},
	/*sec trg*/	{UID_CV_Northampton,UID_CV_Bedford,UID_CV_CAMBRIDGE,UID_CV_BURYSTEDMUNDS,UID_CV_BRANDON},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_CAMBRIDGE,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LOWESTOFT,UID_CV_IPSWICH,UID_CV_HERTFORD},
	/*sec trg*/	{UID_CV_Northampton,UID_CV_Bedford,UID_CV_NEWMARKET,UID_CV_BURYSTEDMUNDS,UID_CV_BRANDON},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_LOWESTOFT,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_CV_GREATYARMOUTH},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_GREATYARMOUTH,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_CV_LOWESTOFT},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_NORWICH,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LOWESTOFT,UID_CV_IPSWICH,UID_CV_HERTFORD},
	/*sec trg*/	{UID_CV_PETERBOROUGH,UID_CV_KINGSLYNN,UID_CV_Birmingham,UID_CV_Coventry,UID_CV_Leicester},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_KINGSLYNN,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LOWESTOFT,UID_CV_IPSWICH,UID_CV_HERTFORD},
	/*sec trg*/	{UID_CV_PETERBOROUGH,UID_CV_NORWICH,UID_CV_Birmingham,UID_CV_Coventry,UID_CV_Leicester},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_IPSWICH,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_MAIDSTONE,UID_NV_TONGUE},
	/*sec trg*/	{UID_CV_CHELMSFORD,UID_CV_COLCHESTER,UID_CV_FELIXSTOWE},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_CHELMSFORD,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_MAIDSTONE,UID_NV_TONGUE},
	/*sec trg*/	{UID_CV_COLCHESTER,UID_CV_IPSWICH,UID_CV_FELIXSTOWE},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_FELIXSTOWE,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_MAIDSTONE,UID_NV_TONGUE},
	/*sec trg*/	{UID_CV_CHELMSFORD,UID_CV_COLCHESTER,UID_CV_IPSWICH},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_HERTFORD,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_AF_CROYDON,UID_CV_CHELMSFORD,UID_CV_GUILFORD},
	/*sec trg*/	{UID_CV_OXFORD,UID_CV_MAIDENHEAD,UID_CV_AYLESBURY,UID_CV_LUTON,UID_CV_STALBANS},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_MAIDSTONE,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NV_TONGUE,UID_NV_DUNGENESS,UID_CV_HASTINGS},
	/*sec trg*/	{UID_CV_REDHILL,UID_CV_TUNBRIDGEWELLS,UID_AF_CROYDON,UID_CV_SOUTHENDONSEA},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_REDHILL,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NV_TONGUE,UID_NV_DUNGENESS,UID_CV_HASTINGS},
	/*sec trg*/	{UID_CV_REDHILL,UID_CV_TUNBRIDGEWELLS,UID_CV_MAIDSTONE,UID_AF_CROYDON,UID_CV_SOUTHENDONSEA},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_LEWES,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LITTLEHAMPTON,UID_NV_ROYALSOVEREIGN,UID_NV_DUNGENESS},
	/*sec trg*/	{UID_CV_BRIGHTON,UID_CV_SEAFORD,UID_CV_EASTBOURNE,UID_CV_HASTINGS,UID_CV_RYE},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_TUNBRIDGEWELLS,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NV_TONGUE,UID_NV_DUNGENESS,UID_CV_HASTINGS},
	/*sec trg*/	{UID_CV_REDHILL,UID_CV_MAIDSTONE,UID_AF_CROYDON,UID_CV_SOUTHENDONSEA},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_BASINGSTOKE,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_ISLEOFWIGHT,UID_CV_BOGNORREGIS,UID_CV_LEWES},
	/*sec trg*/	{UID_CV_Salisbury,UID_CV_ALTON,UID_CV_PETERSFIELD,UID_CV_MIDHURST},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_FARNBOROUGH,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_BOURNEMOUTH,UID_CV_ISLEOFWIGHT,UID_CV_REDHILL},
	/*sec trg*/	{UID_CV_Salisbury,UID_CV_BASINGSTOKE,UID_CV_ALTON,UID_CV_PETERSFIELD,UID_CV_GUILFORD},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_GUILFORD,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_BOURNEMOUTH,UID_CV_BOGNORREGIS,UID_CV_LEWES},
	/*sec trg*/	{UID_CV_Salisbury,UID_CV_BASINGSTOKE,UID_CV_ALTON,UID_CV_PETERSFIELD},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_ISLEOFWIGHT,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_SOUTHAMPTON,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_BOURNEMOUTH,UID_CV_CHICHESTER},
	/*sec trg*/	{UID_DK_Southampton,UID_FA_Switchgear,UID_FA_Itchen,UID_AF_LEEONSOLENT,UID_AF_GOSPORT},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_WINCHESTER,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_BOURNEMOUTH,UID_CV_LEWES,UID_CV_REDHILL},
	/*sec trg*/	{UID_CV_Salisbury,UID_CV_BASINGSTOKE,UID_CV_MIDHURST,UID_CV_GUILFORD},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_CANTERBURY,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NV_NORTHGOODWIN,UID_NV_TONGUE,UID_NV_SOUTHFORELAND},
	/*sec trg*/	{UID_CL_Foreness,UID_AF_MANSTON,UID_AF_EASTCHURCH,UID_DK_Sheerness,UID_AF_DETLING},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_SOUTHENDONSEA,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NV_TONGUE,UID_NV_DUNGENESS,UID_CV_HASTINGS},
	/*sec trg*/	{UID_CV_REDHILL,UID_CV_TUNBRIDGEWELLS,UID_CV_MAIDSTONE,UID_AF_CROYDON},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_COLCHESTER,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_MAIDSTONE,UID_NV_TONGUE},
	/*sec trg*/	{UID_CV_CHELMSFORD,UID_CV_IPSWICH,UID_CV_FELIXSTOWE},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_BOGNORREGIS,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_ISLEOFWIGHT,UID_CV_SOUTHAMPTON,UID_NULL},
	/*sec trg*/	{UID_CV_PORTSMOUTH,UID_CV_CHICHESTER,UID_CV_LITTLEHAMPTON},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_PORTSMOUTH,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_ISLEOFWIGHT,UID_CV_SOUTHAMPTON,UID_NULL},
	/*sec trg*/	{UID_CV_CHICHESTER,UID_CV_BOGNORREGIS,UID_CV_LITTLEHAMPTON},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_FOLKESTONE,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_FOLKESTONE,UID_NV_SOUTHGOODWIN},
	/*sec trg*/	{UID_AF_HAWKINGE,UID_CH_Dover,UID_CL_Foreness,UID_AF_MANSTON,UID_CH_Dunkirk},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_RAMSGATE,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_DK_Dover,UID_CL_Foreness,UID_CH_Dunkirk,UID_AF_EASTCHURCH,UID_DK_Sheerness},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_HASTINGS,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LITTLEHAMPTON,UID_NV_ROYALSOVEREIGN,UID_NV_DUNGENESS},
	/*sec trg*/	{UID_CV_BRIGHTON,UID_CV_LEWES,UID_CV_NEWHAVEN,UID_CV_SEAFORD,UID_CV_EASTBOURNE},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_RYE,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LITTLEHAMPTON,UID_NV_ROYALSOVEREIGN,UID_NV_DUNGENESS},
	/*sec trg*/	{UID_CV_LEWES,UID_CV_NEWHAVEN,UID_CV_SEAFORD,UID_CV_EASTBOURNE,UID_CV_HASTINGS},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_SEAFORD,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LITTLEHAMPTON,UID_NV_ROYALSOVEREIGN,UID_NV_DUNGENESS},
	/*sec trg*/	{UID_CV_BRIGHTON,UID_CV_LEWES,UID_CV_NEWHAVEN,UID_CV_HASTINGS,UID_CV_RYE},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_EASTBOURNE,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LITTLEHAMPTON,UID_NV_ROYALSOVEREIGN,UID_NV_DUNGENESS},
	/*sec trg*/	{UID_CV_BRIGHTON,UID_CV_LEWES,UID_CV_NEWHAVEN,UID_CV_SEAFORD,UID_CV_RYE},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_NEWHAVEN,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LITTLEHAMPTON,UID_NV_ROYALSOVEREIGN,UID_NV_DUNGENESS},
	/*sec trg*/	{UID_CV_BRIGHTON,UID_CV_LEWES,UID_CV_EASTBOURNE,UID_CV_HASTINGS,UID_CV_RYE},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_BRIGHTON,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LITTLEHAMPTON,UID_NV_ROYALSOVEREIGN,UID_NV_DUNGENESS},
	/*sec trg*/	{UID_CV_NEWHAVEN,UID_CV_SEAFORD,UID_CV_EASTBOURNE,UID_CV_HASTINGS,UID_CV_RYE},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_SWINDON,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_OXFORD,UID_PORTLAND,UID_CV_Salisbury},
	/*sec trg*/	{UID_CV_Yeovil,UID_CV_BRISTOL,UID_CV_Gloucester},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_MAIDENHEAD,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_AF_CROYDON,UID_CV_CHELMSFORD,UID_CV_GUILFORD},
	/*sec trg*/	{UID_CV_READING,UID_CV_OXFORD,UID_CV_LUTON,UID_CV_STALBANS,UID_CV_HERTFORD},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_Birmingham,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LOWESTOFT,UID_CV_IPSWICH,UID_CV_HERTFORD},
	/*sec trg*/	{UID_CV_PETERBOROUGH,UID_CV_KINGSLYNN,UID_CV_NORWICH,UID_CV_Coventry,UID_CV_Leicester},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},
	/*name*/{UID_CV_Coventry,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_CV_LOWESTOFT,UID_CV_IPSWICH,UID_CV_HERTFORD},
	/*sec trg*/	{UID_CV_PETERBOROUGH,UID_CV_KINGSLYNN,UID_CV_NORWICH,UID_CV_Birmingham,UID_CV_Leicester},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

//ADDITIONAL LANDMARKS THAT CHRIS ADDED	//MS 23 Aug

	/*name*/{UID_Newbry,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Northfleet,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Crawley,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Swansea,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Wrexham,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Middlesborough,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Hull,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Rotherham,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Huddersfield,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Bradford,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Oldham,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Bury,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Bolton,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_StHelens,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Stockport,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Bath,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_WestonSuperMare,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Barnstaple,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Dover,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Bexhill,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Worthing,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Plymouth,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Exeter,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_TORQUAY,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_EXMOUTH,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Cranbrook,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Heathfield,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Cuckfield,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Horsham,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Witley,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Cardiff,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Chester,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Sheffield,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Leeds,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Liverpool,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Manchester,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CV_LONDON,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_BOURNEMOUTH,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Kelvedon,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Witham,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Basildon,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Corringham,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_Sheerness,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CanveyIsland,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_EnglishChannel,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_NorthSea,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_SouthernWales,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_NorthWales,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_NV_TONGUE,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_NV_BEACHYHEAD,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_NV_DUNGENESS,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_NV_SOUTHFORELAND,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_NV_ROYALSOVEREIGN,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_NV_NORTHGOODWIN,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_NV_BRAKE,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_NV_EASTGOODWIN,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_NV_SOUTHGOODWIN,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_NV_VARNELIGHTSHIP,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_NV_ROARINGMIDDLE,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_PORTLAND,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_DURISTN,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_NAV1,
	/*real*/	TT_LANDMARK,TP_LANDMARK,0,AAA_NONE,
	/*false*/	TT_LANDMARK,TP_LANDMARK,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Normal,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},


		{UID_NULL}
	};
	II_TargetRadar			NodeData::radars[]=
	{

	/*name*/{UID_CL_BeachyHead,
	/*real*/	TT_CHAINLOW,TP_RADAR_HP,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR_HP,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_CH_Pevensey,UID_CL_Truleigh,UID_CL_FairLight,UID_AF_SHOREHAM,UID_CH_Rye},
	/*damage*/ 	&DR_SmallRadar,
//TempCode MS 05Oct00 	/*dates*/		{DAM(OUT,0Aug,30),DAM(NONE,0Aug,31)},
	/*dates*/		{DAM(OUT,0Aug,30),DAM(LOW,0Aug,31)},
	/*bfield*/	 FIL_1_RDBEACHY,
	/*detail*/	{FIL_NULL},
			},

//DeadCode MS 10Mar00 	/*name*/{UID_CL_Carnanton,
//DeadCode MS 10Mar00 	/*real*/	TT_CHAINLOW,TP_RADAR,0,AB(LOW,NONE),
//DeadCode MS 10Mar00 	/*false*/	TT_AS_KNOWN,TP_RADAR,-1,
//DeadCode MS 10Mar00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*sec trg*/	{UID_IN_Falmouth,UID_CL_DryTree,UID_CL_RameHead},//,UID_AF_STEVAL},
//DeadCode MS 10Mar00 	/*damage*/ 	&DR_SmallRadar,
//DeadCode MS 10Mar00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 10Mar00 	/*bfield*/	 FIL_1_RDCARNAN,
//DeadCode MS 10Mar00 	/*detail*/	{FIL_NULL},
//DeadCode MS 10Mar00 			},

//DeadCode MS 10Mar00 	/*name*/{UID_CL_DryTree,
//DeadCode MS 10Mar00 	/*real*/	TT_CHAINLOW,TP_RADAR,0,AB(LOW,NONE),
//DeadCode MS 10Mar00 	/*false*/	TT_AS_KNOWN,TP_RADAR,-1,
//DeadCode MS 10Mar00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*sec trg*/	{UID_IN_Falmouth,UID_CL_RameHead},//UID_CL_Carnanton,UID_AF_STEVAL,//MS 10Mar00
//DeadCode MS 10Mar00 	/*damage*/ 	&DR_SmallRadar,
//DeadCode MS 10Mar00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 10Mar00 	/*bfield*/	 FIL_1_RDDRYTR,
//DeadCode MS 10Mar00 	/*detail*/	{FIL_NULL},
//DeadCode MS 10Mar00 			},		

	/*name*/{UID_CL_Dunwich,
	/*real*/	TT_CHAINLOW,TP_RADAR,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR,-1,
	/*turn pt*/	{UID_CV_FELIXSTOWE,UID_NV_TONGUE,UID_CV_IPSWICH},
	/*sec trg*/	{UID_CH_Darsham},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDDUNWIC,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CL_FairLight,
	/*real*/	TT_CHAINLOW,TP_RADAR_MP,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR_MP,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_CH_Rye,UID_CH_Pevensey,UID_CL_BeachyHead,UID_DK_Eastbourne,UID_AF_LYMPNE},
	/*damage*/ 	&DR_SmallRadar,
//TempCode MS 05Oct00 	/*dates*/		{DAM(OUT,0Aug,30),DAM(NONE,0Aug,31)},
	/*dates*/		{DAM(OUT,0Aug,30),DAM(LOW,0Aug,31)},
	/*bfield*/	 FIL_1_RDFAIRLI,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CL_Foreness,
	/*real*/	TT_CHAINLOW,TP_RADAR_MP,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR_MP,-1,
	/*turn pt*/	{UID_NV_SOUTHFORELAND,UID_NV_EASTGOODWIN,UID_NV_NORTHGOODWIN},
	/*sec trg*/	{UID_CL_Whitstable,UID_AF_MANSTON,UID_CH_Dunkirk,UID_AF_EASTCHURCH,UID_DK_Sheerness},
	/*damage*/ 	&DR_SmallRadar,
//TempCode MS 05Oct00 	/*dates*/		{DAM(OUT,0Aug,15),DAM(NONE,0Aug,17),DAM(OUT,0Aug,30),DAM(NONE,0Sept,2)},
	/*dates*/		{DAM(OUT,0Aug,15),DAM(MED,0Aug,17),DAM(OUT,0Aug,30),DAM(MED,0Sept,2)},
	/*bfield*/	 FIL_1_RDFORENE,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CL_Happisburgh,
	/*real*/	TT_CHAINLOW,TP_IRRELEVENT,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_IRRELEVENT,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_CH_WestBeckham,UID_AF_COLTISHALL,UID_CH_StokeHolyCross},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDHAPPIS,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CL_Ingoldmeis,
	/*real*/	TT_CHAINLOW,TP_IRRELEVENT,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_IRRELEVENT,-1,
	/*turn pt*/	{UID_CV_PETERBOROUGH,UID_CV_CAMBRIDGE,UID_CV_BRANDON},
	/*sec trg*/	{UID_CH_Steingot},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDINGOLD,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CL_RameHead,
	/*real*/	TT_CHAINLOW,TP_IRRELEVENT,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_IRRELEVENT,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_DK_Plymouth,UID_CH_HawksTor},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDRAMEHE,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CL_Poling,
	/*real*/	TT_CHAINLOW,TP_RADAR_HP,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR_HP,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_CL_Truleigh,UID_AF_FORD,UID_AF_TANGMERE,UID_AF_WESTHAMPNETT,UID_AF_SHOREHAM},
	/*damage*/ 	&DR_SmallRadar,
//TempCode MS 05Oct00 	/*dates*/		{DAM(OUT,0Aug,18),DAM(NONE,0Aug,25)},
	/*dates*/		{DAM(OUT,0Aug,18),DAM(MED,0Aug,23),DAM(LOW,0Aug,29)},
	/*bfield*/	 FIL_1_RDPOLING,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CL_Truleigh,
	/*real*/	TT_CHAINLOW,TP_RADAR_MP,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR_MP,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_CL_Poling,UID_AF_SHOREHAM,UID_CL_BeachyHead,UID_CH_Pevensey,UID_DK_Brighton},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDTRULEI,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CL_Walton,
	/*real*/	TT_CHAINLOW,TP_RADAR,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR,-1,
	/*turn pt*/	{UID_NV_TONGUE,UID_CV_SOUTHENDONSEA,UID_Kelvedon},
	/*sec trg*/	{UID_CH_Bromley,UID_CH_Bawdsey,UID_CH_Darsham,UID_CL_Dunwich,UID_AF_MARTLESHAM},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDWALTON,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CL_WestPrawle,
	/*real*/	TT_CHAINLOW,TP_RADAR,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR,-1,
	/*turn pt*/	{UID_PORTLAND,UID_TORQUAY,UID_CL_Worth},
	/*sec trg*/	{UID_AF_EXETER,UID_FA_Westland},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDWESTPR,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CL_Whitstable,
	/*real*/	TT_CHAINLOW,TP_RADAR_MP,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR_MP,-1,
	/*turn pt*/	{UID_CV_RAMSGATE,UID_CV_FOLKESTONE,UID_NV_DUNGENESS},
	/*sec trg*/	{UID_IN_Faversham,UID_AF_EASTCHURCH,UID_CL_Foreness,UID_DK_Sheerness,UID_AF_MANSTON},
	/*damage*/ 	&DR_SmallRadar,
//TempCode MS 05Oct00 	/*dates*/		{DAM(MED,0Aug,30),DAM(NONE,0Sept,1)},
	/*dates*/		{DAM(MED,0Aug,30),DAM(LOW,0Sept,1)},
	/*bfield*/	 FIL_1_RDWHITST,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CL_Worth,
	/*real*/	TT_CHAINLOW,TP_RADAR_MP,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR_MP,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_AF_WARMWELL,UID_DK_Weymouth,UID_NB_Portland,UID_DK_Bournemouth},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDWORTH,
	/*detail*/	{FIL_NULL},
		},

	//****************************************************************
	//RADAR STATIONS CHAIN HOME

	/*name*/{UID_CH_Bawdsey,
	/*real*/	TT_CHAINHOME,TP_RADAR,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR,-1,
	/*turn pt*/	{UID_NV_TONGUE,UID_CV_SOUTHENDONSEA,UID_Kelvedon},
	/*sec trg*/	{UID_CH_Darsham,UID_CL_Dunwich,UID_AF_MARTLESHAM},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDBAWDSE,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CH_Bromley,
	/*real*/	TT_CHAINHOME,TP_RADAR,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR,-1,
	/*turn pt*/	{UID_NV_TONGUE,UID_CV_SOUTHENDONSEA,UID_Kelvedon},
	/*sec trg*/	{UID_CH_Bawdsey,UID_CH_Darsham,UID_CL_Dunwich,UID_AF_MARTLESHAM},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDBROMLE,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CH_Canewdon,
	/*real*/	TT_CHAINHOME,TP_RADAR,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDCANEWD,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CH_Darsham,
	/*real*/	TT_CHAINHOME,TP_RADAR,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR,-1,
	/*turn pt*/	{UID_CV_FELIXSTOWE,UID_NV_TONGUE,UID_CV_IPSWICH},
	/*sec trg*/	{UID_CL_Dunwich},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDDARSHA,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CH_Dover,
	/*real*/	TT_CHAINHOME,TP_RADAR_HP,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR_HP,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_DK_Dover,UID_AF_HAWKINGE,UID_CL_Foreness,UID_AF_MANSTON,UID_AF_LYMPNE},
	/*damage*/ 	&DR_SmallRadar,
//TempCode MS 05Oct00 	/*dates*/		{DAM(LOW,0Aug,12),DAM(NONE,0Aug,13),DAM(OUT,0Aug,15),DAM(OUT,0Aug,16),DAM(LOW,0Aug,30),DAM(NONE,0Aug,31)},
	/*dates*/		{DAM(LOW,0Aug,12),DAM(OUT,0Aug,15),DAM(MED,0Aug,20),DAM(LOW,0Aug,30)},
	/*bfield*/	 FIL_1_RDDOVER,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CH_Dunkirk,
	/*real*/	TT_CHAINHOME,TP_RADAR_HP,0,AB(LOW,NONE),		//MS 15Nov100
	/*false*/	TT_AS_KNOWN,TP_RADAR_HP,-1,						//MS 15Nov100
	/*turn pt*/	{UID_NV_SOUTHFORELAND,UID_CV_FOLKESTONE,UID_NV_DUNGENESS},
	/*sec trg*/	{UID_CL_Whitstable,UID_IN_Faversham,UID_AF_EASTCHURCH,UID_CL_Foreness,UID_DK_Sheerness},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDDUNKIR,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CH_HawksTor,
	/*real*/	TT_CHAINHOME,TP_IRRELEVENT,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_IRRELEVENT,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_CL_RameHead,UID_DK_Plymouth},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDHAWKST,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CH_Pevensey,
	/*real*/	TT_CHAINHOME,TP_RADAR_HP,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR_HP,-1,
	/*turn pt*/	{UID_CV_NEWHAVEN,UID_CL_FairLight},
	/*sec trg*/	{UID_CL_BeachyHead,UID_CL_Truleigh,UID_DK_Eastbourne,UID_CL_FairLight,UID_CH_Rye},
	/*damage*/ 	&DR_SmallRadar,
//TempCode MS 05Oct00 	/*dates*/		{DAM(OUT,0Aug,12),DAM(NONE,0Aug,13),DAM(OUT,0Aug,30),DAM(NONE,0Aug,31)},
	/*dates*/		{DAM(OUT,0Aug,12),DAM(MED,0Aug,20),DAM(OUT,0Aug,30),DAM(MED,0Aug,31)},
	/*bfield*/	 FIL_1_RDPEVENS,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CH_Rye,
	/*real*/	TT_CHAINHOME,TP_RADAR_HP,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR_HP,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_CL_FairLight,UID_CH_Pevensey,UID_AF_LYMPNE,UID_AF_HAWKINGE,UID_DK_Eastbourne},
	/*damage*/ 	&DR_SmallRadar,
//TempCode MS 05Oct00 	/*dates*/		{DAM(OUT,0Aug,12),DAM(NONE,0Aug,13),DAM(OUT,0Aug,15),DAM(NONE,0Aug,16)},
	/*dates*/		{DAM(OUT,0Aug,12),DAM(MED,0Aug,13),DAM(OUT,0Aug,15),DAM(MED,0Aug,16),DAM(LOW,0Aug,30)},
	/*bfield*/	 FIL_1_RDRYE,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CH_Steingot,
	/*real*/	TT_CHAINHOME,TP_IRRELEVENT,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_IRRELEVENT,-1,
	/*turn pt*/	{UID_CV_PETERBOROUGH,UID_CV_CAMBRIDGE,UID_CV_BRANDON},
	/*sec trg*/	{UID_CL_Ingoldmeis},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDSTEING,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CH_StokeHolyCross,
	/*real*/	TT_CHAINHOME,TP_IRRELEVENT,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_IRRELEVENT,-1,
	/*turn pt*/	{UID_CV_IPSWICH,UID_CV_LOWESTOFT,UID_CV_BURYSTEDMUNDS},
	/*sec trg*/	{UID_CH_WestBeckham,UID_CL_Happisburgh,UID_AF_COLTISHALL,UID_FA_BoultonPaul},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDSTOKEH,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CH_WestBeckham,
	/*real*/	TT_CHAINHOME,TP_IRRELEVENT,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_IRRELEVENT,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_CL_Happisburgh,UID_AF_COLTISHALL,UID_CH_StokeHolyCross},
	/*damage*/ 	&DR_SmallRadar,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_RDWESTBE,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_CH_Ventnor,
	/*real*/	TT_CHAINHOME,TP_RADAR_HP,0,AB(LOW,NONE),
	/*false*/	TT_AS_KNOWN,TP_RADAR_HP,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NB_Portsmouth,UID_AF_LEEONSOLENT,UID_AF_GOSPORT,UID_DK_Southampton,UID_AF_THORNEYISLAND},
	/*damage*/ 	&DR_SmallRadar,
//TempCode MS 05Oct00 	/*dates*/		{DAM(OUT,0Aug,12),DAM(NONE,0Aug,14),DAM(OUT,0Aug,16),DAM(NONE,0Aug,22)},
	/*dates*/		{DAM(OUT,0Aug,12),DAM(MED,0Aug,14),DAM(OUT,0Aug,16),DAM(MED,0Aug,22),DAM(LOW,0Aug,29)},
	/*bfield*/	 FIL_1_RDVENTNO,
	/*detail*/	{FIL_NULL},
			},

		//next item:


		{UID_NULL}
	};

	II_TargetGroup	NodeData::notfacts[]=
	{
//DeadCode MS 02Feb00 	/*name*/{UID_FA_Woolwich,
//DeadCode MS 02Feb00 	/*real*/	TT_ARMAMENTS,TP_FACTORY,0,AB(LOW,NONE),
//DeadCode MS 02Feb00 	/*false*/	TT_ARMAMENTS,TP_FACTORY,-1,
//DeadCode MS 02Feb00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 02Feb00 	/*sec trg*/	{UID_AF_KENLEY,UID_AF_BIGGINHILL,UID_AF_GRAVESEND,UID_AF_WESTMALLING,UID_IN_Maidstone},
//DeadCode MS 02Feb00 	/*damage*/ 	&DR_LargeFactory,
//DeadCode MS 02Feb00 	/*dates*/		{DAM(OUT,0Sept,7)},
//DeadCode MS 02Feb00 	/*bfield*/	 FIL_1_INWOOLWI,
//DeadCode MS 02Feb00 	/*detail*/	{FIL_1_MBWOOLWI},	//No!!!!!
//DeadCode MS 02Feb00 			},

	/*name*/{UID_DK_Bournemouth,
	/*real*/	TT_DOCKS,TP_GR11_PORT_LP,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_GR11_PORT_LP,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_AF_WARMWELL,UID_NB_Portland,UID_DK_Weymouth},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_INBOURNE,
	/*detail*/	{FIL_1_MBBOURNE},
			},

	/*name*/{UID_DK_Brighton,
	/*real*/	TT_DOCKS,TP_GR11_PORT_LP,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_GR11_PORT_LP,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_DK_Eastbourne,UID_CL_Truleigh,UID_AF_SHOREHAM,UID_AF_FORD,UID_CL_Poling},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,//FIL_1_INBRIGHT,aghh 
	/*detail*/	{FIL_1_MBBRIGHT},
			},

	/*name*/{UID_DK_Bristol,
	/*real*/	TT_DOCKS,TP_GRxx_PORT_HP,0,AB(MED,MED),
	/*false*/	TT_AS_KNOWN,TP_GRxx_PORT_HP,-1,
	/*turn pt*/	{UID_NB_Portland,UID_CV_SWINDON},
	/*sec trg*/	{UID_FA_BristolAeroEngine,UID_FA_BristolAeroplane,UID_FA_Parnall,UID_AF_FILTON},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/	{DAM(MED,0July,12)},
	/*bfield*/	 FIL_1_INBRISTO,
	/*detail*/	{FIL_1_MBBRISTO},
			},

	/*name*/{UID_IN_Canterbury,
	/*real*/	TT_INDUSTRY,TP_INDUSTRY,0,AB(MED,MED),
	/*false*/	TT_AS_KNOWN,TP_INDUSTRY,-1,
	/*turn pt*/	{UID_NV_BRAKE,UID_CV_FOLKESTONE,UID_NV_SOUTHFORELAND},
	/*sec trg*/	{UID_IN_Faversham,UID_CL_Whitstable,UID_DK_Sheerness,UID_FA_Pobjoy,UID_FA_ShortsBros},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(LOW,0Aug,18)},
	/*bfield*/	 FIL_1_INCANTER,
	/*detail*/	{FIL_1_MBCANTER},
			},

	/*name*/{UID_DK_Dover,
	/*real*/	TT_DOCKS,TP_GR11_PORT_HP,0,AB(HIGH,HIGH),
	/*false*/	TT_AS_KNOWN,TP_GR11_PORT_HP,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_CH_Dover,UID_AF_HAWKINGE,UID_CL_Foreness,UID_AF_MANSTON,UID_CH_Dunkirk},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(LOW,0July,30),DAM(MED,0Aug,11)},
	/*bfield*/	 FIL_1_INDOVER,
	/*detail*/	{FIL_1_MBDOVER}},

	/*name*/{UID_DK_Eastbourne,
	/*real*/	TT_DOCKS,TP_GR11_PORT_LP,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_GR11_PORT_LP,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_CL_BeachyHead,UID_CH_Pevensey,UID_DK_Brighton,UID_CL_Truleigh,UID_CL_FairLight},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_INEASTBO,
	/*detail*/	{FIL_1_MBEASTBO},
			},

	/*name*/{UID_IN_Faversham,
	/*real*/	TT_INDUSTRY,TP_INDUSTRY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_INDUSTRY,-1,
	/*turn pt*/	{UID_NV_BRAKE,UID_CV_FOLKESTONE,UID_NV_SOUTHFORELAND},
	/*sec trg*/	{UID_IN_Canterbury,UID_CL_Whitstable,UID_DK_Sheerness,UID_FA_Pobjoy,UID_FA_ShortsBros},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_INFAVERS,
	/*detail*/	{FIL_1_MBFAVERS},
			},

	/*name*/{UID_IN_Batersea,
	/*real*/	TT_INDUSTRY,TP_SMALLRESOURCE,0,LON(HIGH,HIGH),
	/*false*/	TT_INDUSTRY,TP_SMALLRESOURCE,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_INBATERS,
	/*detail*/	{FIL_1_MBBATERS},
			},

	/*name*/{UID_DK_Newhaven,
	/*real*/	TT_DOCKS,TP_SMALLRESOURCE,0,LON(HIGH,HIGH),
	/*false*/	TT_AS_KNOWN,TP_SMALLRESOURCE,-1,
	/*turn pt*/	{UID_NV_DUNGENESS,UID_Northfleet,UID_CV_TUNBRIDGEWELLS},
	/*sec trg*/	{UID_DK_Millwall,UID_DK_Surrey,UID_DK_Rotherhithe,UID_DK_Limehouse,UID_IN_Batersea},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_INNEWHAV,
	/*detail*/	{FIL_1_MBNEWHAV},
			},

	/*name*/{UID_DK_Rotherhithe,
	/*real*/	TT_DOCKS,TP_SMALLRESOURCE,0,LON(HIGH,HIGH),
	/*false*/	TT_AS_KNOWN,TP_SMALLRESOURCE,-1,
	/*turn pt*/	{UID_NV_NORTHGOODWIN,UID_NV_TONGUE,UID_NV_SOUTHFORELAND},
	/*sec trg*/	{UID_FA_KingstonHawker,UID_DK_Surrey,UID_DK_WestIndia,UID_DK_Millwall,UID_DK_EASTINDIA},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(MED,0Sept,7)},
	/*bfield*/	 FIL_1_INROTHER,
	/*detail*/	{FIL_1_MBROTHER},
			},

	/*name*/{UID_DK_Limehouse,
	/*real*/	TT_DOCKS,TP_SMALLRESOURCE,0,LON(HIGH,HIGH),
	/*false*/	TT_AS_KNOWN,TP_SMALLRESOURCE,-1,
	/*turn pt*/	{UID_NV_DUNGENESS,UID_Northfleet,UID_CV_TUNBRIDGEWELLS},
//DeadCode MS 15Oct00 	/*sec trg*/	{UID_IN_ThamesHaven,UID_IN_Purfleet,UID_IN_Beckton,UID_FA_Woolwich,UID_DK_RoyalAlbert},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(MED,0Sept,7)},
	/*bfield*/	 FIL_1_INLIMEHO,
	/*detail*/	{FIL_1_MBLIMEHO},
			},

	/*name*/{UID_DK_Millwall,
	/*real*/	TT_DOCKS,TP_LARGERESOURCE,0,LON(HIGH,HIGH),
	/*false*/	TT_AS_KNOWN,TP_LARGERESOURCE,-1,
	/*turn pt*/	{UID_Cranbrook,UID_Northfleet,UID_CV_FOLKESTONE},
	/*sec trg*/	{UID_DK_Surrey,UID_DK_Rotherhithe,UID_DK_Limehouse,UID_IN_Batersea,UID_HS_BATTERSEA},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(MED,0Sept,7)},
	/*bfield*/	 FIL_1_INMILLWA,
	/*detail*/	{FIL_1_MBMILLWA},
			},

	/*name*/{UID_DK_Surrey,
	/*real*/	TT_DOCKS,TP_LARGERESOURCE,0,LON(LOW,HIGH),
	/*false*/	TT_AS_KNOWN,TP_LARGERESOURCE,-1,
	/*turn pt*/	{UID_Heathfield,UID_Northfleet,UID_NV_SOUTHFORELAND},
	/*sec trg*/	{UID_DK_Rotherhithe,UID_DK_Limehouse,UID_IN_Batersea,UID_HS_BATTERSEA},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(OUT,0Sept,7)},
	/*bfield*/	 FIL_1_INSURREY,
	/*detail*/	{FIL_1_MBSURREY},
			},

	/*name*/{UID_IN_Beckton,
	/*real*/	TT_INDUSTRY,TP_INDUSTRY,0,LON(LOW,HIGH),
	/*false*/	TT_AS_KNOWN,TP_INDUSTRY,-1,
	/*turn pt*/	{UID_CV_MAIDSTONE,UID_Northfleet,UID_NV_DUNGENESS},
	/*sec trg*/	{UID_DK_KingGeorgeV,UID_DK_RoyalAlbert,UID_DK_ROYALVICTORIA,UID_IN_WestHam,UID_DK_EASTINDIA},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(MED,0Sept,7)},
	/*bfield*/	 FIL_1_INBECKTO,
	/*detail*/	{FIL_1_MBBECKTO},
			},

	/*name*/{UID_IN_WestHam,
	/*real*/	TT_INDUSTRY,TP_LARGERESOURCE,0,LON(LOW,HIGH),
	/*false*/	TT_INDUSTRY,TP_LARGERESOURCE,-1,
	/*turn pt*/	{UID_CV_TUNBRIDGEWELLS,UID_Northfleet,UID_CV_FOLKESTONE},
	/*sec trg*/	{UID_DK_EASTINDIA,UID_DK_WestIndia,UID_DK_Newhaven,UID_DK_Millwall,UID_DK_Surrey},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(LOW,0Sept,7)},
	/*bfield*/	 FIL_1_INWESTHA,
	/*detail*/	{FIL_1_MBWESTHA},
			},

	/*name*/{UID_DK_WestIndia,
	/*real*/	TT_DOCKS,TP_LARGERESOURCE,0,LON(LOW,HIGH),
	/*false*/	TT_AS_KNOWN,TP_LARGERESOURCE,-1,
	/*turn pt*/	{UID_Cranbrook,UID_Northfleet,UID_NV_SOUTHFORELAND},
	/*sec trg*/	{UID_DK_Newhaven,UID_DK_Millwall,UID_DK_Surrey,UID_DK_Rotherhithe,UID_DK_Limehouse},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_INWESTIN,
	/*detail*/	{FIL_1_MBWESTIN},
			},
//THESE WERE MISSING											//MS 23May00

	/*name*/{UID_DK_RoyalAlbert,
	/*real*/	TT_DOCKS,TP_LARGERESOURCE,0,LON(HIGH,HIGH),
	/*false*/	TT_AS_KNOWN,TP_LARGERESOURCE,-1,
	/*turn pt*/	{UID_Heathfield,UID_Northfleet,UID_NV_DUNGENESS},
	/*sec trg*/	{UID_DK_ROYALVICTORIA,UID_IN_WestHam,UID_DK_EASTINDIA,UID_DK_WestIndia,UID_DK_Newhaven},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_DK_KingGeorgeV,
	/*real*/	TT_DOCKS,TP_LARGERESOURCE,0,LON(HIGH,HIGH),
	/*false*/	TT_AS_KNOWN,TP_LARGERESOURCE,-1,
	/*turn pt*/	{UID_CV_MAIDSTONE,UID_Northfleet,UID_CV_FOLKESTONE},
	/*sec trg*/	{UID_DK_RoyalAlbert,UID_DK_ROYALVICTORIA,UID_IN_WestHam,UID_DK_EASTINDIA,UID_DK_WestIndia},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_DK_ROYALVICTORIA,
	/*real*/	TT_DOCKS,TP_LARGERESOURCE,0,LON(HIGH,HIGH),
	/*false*/	TT_AS_KNOWN,TP_LARGERESOURCE,-1,
	/*turn pt*/	{UID_CV_TUNBRIDGEWELLS,UID_Northfleet,UID_NV_SOUTHFORELAND},
	/*sec trg*/	{UID_IN_WestHam,UID_DK_EASTINDIA,UID_DK_WestIndia,UID_DK_Newhaven,UID_DK_Millwall},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},


//END OF MISSING ONES
	/*name*/{UID_IN_ThamesHaven,
	/*real*/	TT_INDUSTRY,TP_SMALLRESOURCE,0,LON(HIGH,HIGH),
	/*false*/	TT_INDUSTRY,TP_SMALLRESOURCE,-1,
	/*turn pt*/	{UID_NV_DUNGENESS,UID_Northfleet,UID_CV_TUNBRIDGEWELLS},
	/*sec trg*/	{UID_FA_Woolwich,UID_FA_Rootes,UID_IN_Beckton,UID_DK_KingGeorgeV,UID_DK_RoyalAlbert},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(MED,0Sept,5)},
	/*bfield*/	 FIL_1_INTHAMES,
	/*detail*/	{FIL_1_MBTHAMES},
			},

	/*name*/{UID_IN_Maidstone,
	/*real*/	TT_INDUSTRY,TP_INDUSTRY,0,AB(MED,LOW),
	/*false*/	TT_AS_KNOWN,TP_INDUSTRY,-1,
	/*turn pt*/	{UID_Cranbrook,UID_CV_FOLKESTONE,UID_CV_CANTERBURY},
	/*sec trg*/	{UID_FA_Pobjoy,UID_FA_ShortsBros,UID_AF_DETLING,UID_AF_WESTMALLING},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_INMAIDST,
	/*detail*/	{FIL_1_MBMAIDST},
			},

//DeadCode MS 10Mar00 	/*name*/{UID_IN_Thorpe,
//DeadCode MS 10Mar00 	/*real*/	TT_INDUSTRY,TP_SMALLRESOURCE,0,AB(LOW,HIGH),
//DeadCode MS 10Mar00 	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
//DeadCode MS 10Mar00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*damage*/ 	&DR_LargeFactory,
//DeadCode MS 10Mar00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 10Mar00 	/*bfield*/	 FIL_1_INTHORPE,
//DeadCode MS 10Mar00 	/*detail*/	{FIL_1_MBTHORPE},
//DeadCode MS 10Mar00 			},

	/*name*/{UID_NB_Portsmouth,
	/*real*/	TT_NAVALBASE,TP_NAVALBASE,0,AB(MED,MED),
	/*false*/	TT_AS_KNOWN,TP_NAVALBASE,-1,
	/*turn pt*/	{UID_CV_BOGNORREGIS,UID_CV_ISLEOFWIGHT,UID_CV_CHICHESTER},
	/*sec trg*/	{UID_AF_LEEONSOLENT,UID_AF_GOSPORT,UID_AF_THORNEYISLAND,UID_DK_Southampton,UID_AF_WESTHAMPNETT},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(LOW,0July,11),DAM(MED,0Aug,13)},
	/*bfield*/	 FIL_1_INPORTSM,
	/*detail*/	{FIL_1_MBPORTSM},
			},

	/*name*/{UID_NB_Portland,
	/*real*/	TT_NAVALBASE,TP_NAVALBASE,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_NAVALBASE,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_DK_Weymouth,UID_AF_WARMWELL,UID_DK_Bournemouth},
	/*damage*/ 	&DR_LargeFactory,
//DeadCode MS 15Oct00 	/*dates*/		{DAM(MED,0Aug,11),DAM(LOW,0Sept,15)},
	/*dates*/		{DAM(MED,0Aug,11)},
	/*bfield*/	 FIL_1_INPORTLA,
	/*detail*/	{FIL_1_MBPORTLA},
			},

	/*name*/{UID_DK_Plymouth,
	/*real*/	TT_DOCKS,TP_GR11_PORT_HP,0,AB(MED,MED),
	/*false*/	TT_AS_KNOWN,TP_GR11_PORT_HP,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_CL_RameHead,UID_CH_HawksTor},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_INPLYMOU,
	/*detail*/	{FIL_1_MBPLYMOU},
			},

	/*name*/{UID_IN_Purfleet,
	/*real*/	TT_INDUSTRY,TP_SMALLRESOURCE,0,LON(LOW,LOW),
	/*false*/	TT_INDUSTRY,TP_SMALLRESOURCE,-1,
	/*turn pt*/	{UID_NV_NORTHGOODWIN,UID_Sheerness,UID_NV_SOUTHFORELAND},
//TempCode MS 15Oct00 	/*sec trg*/	{UID_IN_ThamesHaven,UID_DK_Limehouse,UID_IN_Beckton,UID_FA_Woolwich,UID_DK_RoyalAlbert},
	/*sec trg*/	{UID_IN_ThamesHaven,UID_IN_Beckton,UID_FA_Woolwich,UID_DK_RoyalAlbert},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_INPURFLE,
	/*detail*/	{FIL_1_MBPURFLE},
			},

	/*name*/{UID_DK_Sheerness,
	/*real*/	TT_DOCKS,TP_GRxx_PORT_LP,0,AB(HIGH,NONE),
	/*false*/	TT_AS_KNOWN,TP_GRxx_PORT_LP,-1,
	/*turn pt*/	{UID_NV_TONGUE,UID_CV_CANTERBURY,UID_CV_RYE},
//TempCode MS 15Oct00 	/*sec trg*/	{UID_CL_Whitstable,UID_AF_ROCHFORD,UID_AF_GRAVESEND,UID_AF_DETLING,UID_DK_TILBURY},
	/*sec trg*/	{UID_CL_Whitstable,UID_AF_ROCHFORD,UID_AF_GRAVESEND,UID_AF_DETLING},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(LOW,0Aug,13)},
	/*bfield*/	 FIL_1_INSHEERN,
	/*detail*/	{FIL_1_MBSHEERN},
			},

	/*name*/{UID_DK_Southampton,
	/*real*/	TT_DOCKS,TP_GR11_PORT_HP,0,AB(HIGH,HIGH),
	/*false*/	TT_AS_KNOWN,TP_GR11_PORT_HP,-1,
	/*turn pt*/	{UID_CV_ISLEOFWIGHT,UID_CV_CHICHESTER,UID_CV_PORTSMOUTH},
	/*sec trg*/	{UID_FA_ThornycroftMotors,UID_FA_Switchgear,UID_AF_MIDDLEWALLOP,UID_AF_BOSCOMBEDOWN,UID_AF_WORTHYDOWN},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(LOW,0Sept,13),DAM(MED,0Sept,14)},
	/*bfield*/	 FIL_1_INSOUTHA,
	/*detail*/	{FIL_1_MBSOUTHA},
			},

	/*name*/{UID_DK_Weymouth,
	/*real*/	TT_DOCKS,TP_GRxx_PORT_HP,0,AB(MED,LOW),
	/*false*/	TT_AS_KNOWN,TP_GRxx_PORT_HP,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NB_Portland,UID_AF_WARMWELL,UID_DK_Bournemouth},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(LOW,0Aug,11)},
	/*bfield*/	 FIL_1_INWEYMOU,
	/*detail*/	{FIL_1_MBWEYMOU},
			},


	/*name*/{UID_DK_EASTINDIA,
	/*real*/	TT_DOCKS,TP_LARGERESOURCE,0,LON(HIGH,HIGH),
	/*false*/	TT_AS_KNOWN,TP_LARGERESOURCE,-1,
	/*turn pt*/	{UID_CV_FOLKESTONE,UID_Northfleet,UID_Cranbrook},
	/*sec trg*/	{UID_DK_WestIndia,UID_DK_Newhaven,UID_DK_Millwall,UID_DK_Surrey,UID_DK_Rotherhithe},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},

	/*name*/{UID_DK_TILBURY,
	/*real*/	TT_DOCKS,TP_SMALLRESOURCE,0,LON(HIGH,LOW),
	/*false*/	TT_AS_KNOWN,TP_SMALLRESOURCE,-1,
	/*turn pt*/	{UID_NV_NORTHGOODWIN,UID_Cranbrook,UID_NV_SOUTHFORELAND},
//DeadCode MS 15Oct00 	/*sec trg*/	{UID_DK_Sheerness,UID_DK_Limehouse,UID_IN_Purfleet,UID_IN_ThamesHaven},
	/*sec trg*/	{UID_DK_Sheerness,UID_IN_Purfleet,UID_IN_ThamesHaven},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
			},


//DeadCode MS 10Mar00 	/*name*/{UID_IN_Falmouth,
//DeadCode MS 10Mar00 	/*real*/	TT_INDUSTRY,TP_LARGERESOURCE,0,AB(LOW,HIGH),
//DeadCode MS 10Mar00 	/*false*/	TT_INDUSTRY,TP_FACTORY,-1,
//DeadCode MS 10Mar00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*sec trg*/	{UID_CL_DryTree,UID_CL_RameHead,UID_DK_Plymouth},//UID_AF_STEVAL,
//DeadCode MS 10Mar00 	/*damage*/ 	&DR_LargeFactory,
//DeadCode MS 10Mar00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 10Mar00 	/*bfield*/	 FIL_1_INFALMOU,
//DeadCode MS 10Mar00 	/*detail*/	{FIL_1_MBFALMOU},
//DeadCode MS 10Mar00 			},

//DeadCode MS 10Mar00 	/*name*/{UID_IN_Rochfield,
//DeadCode MS 10Mar00 	/*real*/	TT_INDUSTRY,TP_SMALLRESOURCE,0,AB(LOW,HIGH),
//DeadCode MS 10Mar00 	/*false*/	TT_INDUSTRY,TP_FACTORY,-1,
//DeadCode MS 10Mar00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*damage*/ 	&DR_LargeFactory,
//DeadCode MS 10Mar00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 10Mar00 	/*bfield*/	 FIL_1_INROCHFI,
//DeadCode MS 10Mar00 	/*detail*/	{FIL_1_MBROCHFI},
//DeadCode MS 10Mar00 			},
//DeadCode MS 10Mar00 	/*name*/{UID_DK_Pembroke,
//DeadCode MS 10Mar00 	/*real*/	TT_DOCKS,TP_SMALLRESOURCE,0,AB(LOW,HIGH),
//DeadCode MS 10Mar00 	/*false*/	TT_INDUSTRY,TP_FACTORY,-1,
//DeadCode MS 10Mar00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*damage*/ 	&DR_LargeFactory,
//DeadCode MS 10Mar00 	/*dates*/		{DAM(LOW,0Aug,19)},
//DeadCode MS 10Mar00 	/*bfield*/	 FIL_1_INPEMBRO,
//DeadCode MS 10Mar00 	/*detail*/	{FIL_1_MBPEMBRO},
//DeadCode MS 10Mar00 			},
		//next item:


		{UID_NULL}
	};


	II_TargetFakeFactory	NodeData::fakefacts[]=
	{
	/*name*/{UID_FA_BrooklandsVickers,
	/*real*/	TT_WELLINGTON,TP_BOMBERFACTORY,0,AB(HIGH,MED),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_Horsham,UID_Crawley,UID_CV_REDHILL},
	/*sec trg*/	{UID_FA_FelthamGeneral,UID_FA_BrooklandsHawker,UID_FA_LangleyHawker,UID_FA_Farnborough,UID_FA_KingstonHawker},
	/*damage*/ 	&DR_LargeFactory,
//TempCode MS 05Oct00 	/*dates*/		{DAM(OUT,0Sept,4),DAM(NONE,0Sept,8)},
	/*dates*/		{DAM(OUT,0Sept,4),DAM(MED,0Sept,8)},
	/*bfield*/	 FIL_1_FTVICKER,
	/*detail*/	{FIL_1_MBVICKER},
	/*per wk*/	45,	//norm,dest,disp
//DeadCode DAW 18Feb00 	/*limits*/			60,	5,	50
			},

	/*name*/{UID_FA_BristolAeroplane,
	/*real*/	TT_BEAUFIGHTER,TP_FACTORY,0,AB(MED,MED),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_Bath,UID_WestonSuperMare,UID_CV_Yeovil},
	/*sec trg*/	{UID_FA_BristolAeroEngine,UID_FA_Parnall,UID_AF_FILTON,UID_DK_Bristol},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTPLANE,
	/*detail*/	{FIL_1_MBPLANE},
	/*per wk*/	45,	//norm,dest,disp
//DeadCode DAW 18Feb00 	/*limits*/			60,	5,	50
			},

	/*name*/{UID_FA_ShortsBros,
	/*real*/	TT_STIRLING,TP_BOMBERFACTORY,0,AB(MED,LOW),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_CV_CANTERBURY,UID_Cranbrook,UID_CV_TUNBRIDGEWELLS},
//DeadCode MS 15Oct00 	/*sec trg*/	{UID_AF_GRAVESEND,UID_DK_TILBURY,UID_DK_Sheerness,UID_AF_ROCHFORD},
	/*sec trg*/	{UID_AF_GRAVESEND,UID_DK_Sheerness,UID_AF_ROCHFORD},
	/*damage*/ 	&DR_LargeFactory,
//TempCode MS 05Oct00 	/*dates*/		{DAM(MED,0Aug,15),DAM(NONE,0Aug,20),DAM(LOW,0Sept,4)},
	/*dates*/		{DAM(MED,0Aug,15),DAM(LOW,0Aug,20),DAM(LOW,0Sept,4)},
	/*bfield*/	 FIL_1_FTSHORTS,
	/*detail*/	{FIL_1_MBSHORTS},
	/*per wk*/	45,	//norm,dest,disp
//DeadCode DAW 18Feb00 	/*limits*/			60,	5,	50
			},

	/*name*/{UID_FA_Parnall,
	/*real*/	TT_BOMBERPARTS,TP_BOMBERFACTORY,0,AB(MED,LOW),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_FA_BristolAeroEngine,UID_FA_BristolAeroplane,UID_DK_Southampton},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTPARNAL,
	/*detail*/	{FIL_1_MBPARNAL},
	/*per wk*/	45,	//norm,dest,disp
//DeadCode DAW 18Feb00 	/*limits*/			60,	5,	50
			},

	/*name*/{UID_FA_Hatfield,
	/*real*/	TT_BOMBERPARTS,TP_BOMBERFACTORY,0,AB(MED,LOW),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_AF_CROYDON,UID_FA_FelthamGeneral,UID_Northfleet},
	/*sec trg*/	{UID_FA_Vauxhall},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTHATFIE,
	/*detail*/	{FIL_1_MBHATFIE},
	/*per wk*/	45,	//norm,dest,disp
//DeadCode DAW 18Feb00 	/*limits*/			60,	5,	50
			},
	/*name*/{UID_FA_Rootes,
	/*real*/	TT_BOMBERPARTS,TP_BOMBERFACTORY,0,AB(HIGH,HIGH),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_NV_SOUTHFORELAND,UID_Northfleet,UID_Heathfield},
	/*sec trg*/	{UID_IN_Beckton,UID_DK_KingGeorgeV,UID_DK_RoyalAlbert,UID_DK_ROYALVICTORIA,UID_IN_WestHam},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTROOTES,
	/*detail*/	{FIL_1_MBROOTES},
	/*per wk*/	45,	//norm,dest,disp
//DeadCode DAW 18Feb00 	/*limits*/			60,	5,	50
			},

	/*name*/{UID_FA_BoultonPaul,
	/*real*/	TT_BOMBERPARTS,TP_BOMBERFACTORY,0,AB(MED,LOW),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_CV_LOWESTOFT,UID_CV_IPSWICH},
	/*sec trg*/	{UID_AF_COLTISHALL,UID_CH_WestBeckham,UID_CL_Happisburgh,UID_FA_BoultonPaul},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_NULL,
	/*detail*/	{FIL_NULL},
	/*per wk*/	45,	//norm,dest,disp
			},

	//Next item...


	  	{UID_NULL}	
	};

	II_TargetFactory		NodeData::factories[]=
	{
//DeadCode MS 10Mar00 	/*name*/{UID_FA_Coventry,
//DeadCode MS 10Mar00 	/*real*/	TT_ARMAMENTS,TP_FACTORY,0,AB(LOW,HIGH),
//DeadCode MS 10Mar00 	/*false*/	TT_UNKNOWNAIRCRAFT,TP_OTHERFACTORY,-1,
//DeadCode MS 10Mar00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 10Mar00 	/*damage*/ 	&DR_LargeFactory,
//DeadCode MS 10Mar00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 10Mar00 	/*bfield*/	 FIL_1_FTDAG,
//DeadCode MS 10Mar00 	/*detail*/	{FIL_1_MBDAG},
//DeadCode MS 10Mar00 	/*per wk*/	45,	//norm,dest,disp
//DeadCode MS 10Mar00 	/*limits*/			60,	5,	50
//DeadCode MS 10Mar00 			},

	/*name*/{UID_FA_Woolwich,
	/*real*/	TT_ARMAMENTS,TP_FACTORY,0,LON(HIGH,MED),
	/*false*/	TT_INDUSTRY,TP_FACTORY,-1,
	/*turn pt*/	{UID_NV_DUNGENESS,UID_Northfleet,UID_CV_MAIDSTONE},
	/*sec trg*/	{UID_FA_Rootes,UID_IN_Beckton,UID_DK_KingGeorgeV,UID_DK_RoyalAlbert,UID_DK_ROYALVICTORIA},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTWOOLWI,
	/*detail*/	{FIL_1_MBWOOLWI},
	/*per wk*/	40,	//norm,dest,disp
	/*limits*/			40,	0,	20
			},

	/*name*/{UID_FA_BrooklandsHawker,
	/*real*/	TT_HURRASSEMBLY,TP_FIGHTERFACTORY,0,AB(MED,MED),
	/*false*/	TT_AS_KNOWN,TP_FIGHTERFACTORY,-1,
	/*turn pt*/	{UID_Horsham,UID_Crawley,UID_CV_REDHILL},
	/*sec trg*/	{UID_FA_FelthamGeneral,UID_FA_BrooklandsVickers,UID_FA_LangleyHawker,UID_FA_Farnborough,UID_FA_KingstonHawker},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(MED,0Sept,2),DAM(NONE,0Sept,4)},
	/*bfield*/	 FIL_1_FTHAWKER,
	/*detail*/	{FIL_1_MBHAWKER},
	/*per wk*/	32,	//norm,dest,disp
	/*limits*/			32,	5,	28
			},

//TempCode DAW 18Feb00 	/*name*/{UID_FA_Coventry,
//TempCode DAW 18Feb00 	/*real*/	TT_HURRPARTS,TP_COMPONENTFACTORY,0,AB(LOW,HIGH),
//TempCode DAW 18Feb00 	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
//TempCode DAW 18Feb00 	/*turn pt*/	{UID_NULL},
//TempCode DAW 18Feb00 	/*sec trg*/	{UID_NULL},
//TempCode DAW 18Feb00 	/*damage*/ 	&DR_LargeFactory,
//TempCode DAW 18Feb00 	/*dates*/		{DAM(NONE)},
//TempCode DAW 18Feb00 	/*bfield*/	 FIL_1_FTCOVENT,
//TempCode DAW 18Feb00 	/*detail*/	{FIL_1_MBCOVENT},
//TempCode DAW 18Feb00 	/*per wk*/	45,	//norm,dest,disp
//TempCode DAW 18Feb00 	/*limits*/			60,	5,	50
//TempCode DAW 18Feb00 			},

	/*name*/{UID_FA_Farnborough,
	/*real*/	TT_ARMAMENTS,TP_FACTORY,0,AB(MED,LOW),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_Horsham,UID_CV_MIDHURST,UID_CV_ALTON},
	/*sec trg*/	{UID_FA_BrooklandsHawker,UID_FA_BrooklandsVickers},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(LOW,0Aug,16),DAM(NONE,0Aug,18)},
	/*bfield*/	 FIL_1_FTFARNBO,
	/*detail*/	{FIL_1_MBFARNBO},
	/*per wk*/	40,	//norm,dest,disp
	/*limits*/			40,	0,	20
			},

	/*name*/{UID_FA_FelthamGeneral,
	/*real*/	TT_SPITPARTS,TP_COMPONENTFACTORY,0,AB(LOW,LOW),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_CV_REDHILL,UID_CV_GUILFORD,UID_Crawley},
	/*sec trg*/	{UID_FA_KingstonHawker,UID_FA_BrooklandsVickers,UID_FA_BrooklandsHawker,UID_FA_LangleyHawker,UID_FA_Farnborough},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTFELTHA,
	/*detail*/	{FIL_1_MBFELTHA},
	/*per wk*/	15,	//norm,dest,disp							//MS 02Nov00
	/*limits*/			15,	2,	10
			},

	/*name*/{UID_FA_BristolAeroEngine,
	/*real*/	TT_SPITPARTS,TP_COMPONENTFACTORY,0,AB(HIGH,MED),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_Bath,UID_WestonSuperMare,UID_CV_Yeovil},
	/*sec trg*/	{UID_FA_BristolAeroplane,UID_FA_Parnall,UID_AF_FILTON,UID_DK_Bristol},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTENGINE,
	/*detail*/	{FIL_1_MBENGINE},
	/*per wk*/	15,	//norm,dest,disp
	/*limits*/			20,	2,	12
			},

	/*name*/{UID_FA_Gloster,
	/*real*/	TT_HURRPARTS,TP_COMPONENTFACTORY,0,AB(LOW,LOW),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_CV_SWINDON,UID_CV_Salisbury,UID_Bath},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTGLOSTE,
	/*detail*/	{FIL_1_MBGLOSTE},
	/*per wk*/	40,	//norm,dest,disp
	/*limits*/			40,	5,	30
			},

	/*name*/{UID_FA_KingstonHawker,
//DeadCode MS 13Oct00 	/*real*/	TT_HURRASSEMBLY,TP_FIGHTERFACTORY,0,LON(LOW,HIGH),
	/*real*/	TT_HURRASSEMBLY,TP_FIGHTERFACTORY,0,AB(MED,LOW),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_CV_REDHILL,UID_Witley,UID_Crawley},
	/*sec trg*/	{UID_FA_FelthamGeneral,UID_FA_BrooklandsVickers,UID_FA_BrooklandsHawker,UID_FA_LangleyHawker,UID_FA_Farnborough},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTKINGST,
	/*detail*/	{FIL_1_MBKINGST},
	/*per wk*/	30,	//norm,dest,disp							//MS 02Nov00
	/*limits*/			30,	5,	25								//MS 02Nov00
			},

	/*name*/{UID_FA_LangleyHawker,
	/*real*/	TT_HURRPARTS,TP_COMPONENTFACTORY,0,AB(LOW,LOW),	//MS 02Nov00
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_CV_REDHILL,UID_Horsham,UID_Witley},
	/*sec trg*/	{UID_FA_FelthamGeneral,UID_FA_BrooklandsVickers,UID_FA_BrooklandsHawker,UID_FA_Farnborough},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTLANGLE,
	/*detail*/	{FIL_1_MBLANGLE},
	/*per wk*/	25,	//norm,dest,disp							//MS 02Nov00
	/*limits*/			25,	5,	15								//MS 02Nov00
			},

	/*name*/{UID_FA_Vauxhall,
//DeadCode MS 13Oct00 	/*real*/	TT_ARMAMENTS,TP_COMPONENTFACTORY,0,LON(LOW,HIGH),
	/*real*/	TT_ARMAMENTS,TP_FACTORY,0,AB(MED,LOW),
	/*false*/	TT_CARS,TP_FACTORY,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_FA_Hatfield},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTVAUXHA,
	/*detail*/	{FIL_1_MBVAUXHA},
	/*per wk*/	40,	//norm,dest,disp
	/*limits*/			40,	0,	20
			},

	/*name*/{UID_FA_Pobjoy,
	/*real*/	TT_SPITPARTS,TP_COMPONENTFACTORY,0,AB(MED,MED),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_CV_CANTERBURY,UID_Cranbrook,UID_CV_TUNBRIDGEWELLS},
//DeadCode MS 15Oct00 	/*sec trg*/	{UID_AF_GRAVESEND,UID_DK_TILBURY,UID_DK_Sheerness,UID_AF_ROCHFORD},
	/*sec trg*/	{UID_AF_GRAVESEND,UID_DK_Sheerness,UID_AF_ROCHFORD},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTPOBJOY,
	/*detail*/	{FIL_1_MBPOBJOY},
	/*per wk*/	10,	//norm,dest,disp
	/*limits*/			10,	2,	6
			},

	/*name*/{UID_FA_Itchen,
	/*real*/	TT_SPITASSEMBLY,TP_FIGHTERFACTORY,0,AB(HIGH,MED),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_CV_ISLEOFWIGHT,UID_CV_CHICHESTER,UID_CV_PORTSMOUTH},
	/*sec trg*/	{UID_DK_Southampton,UID_FA_Switchgear,UID_FA_Woolston,UID_FA_ThornycroftMotors,UID_AF_MIDDLEWALLOP},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTITCHEN,
	/*detail*/	{FIL_1_MBITCHEN},
	/*per wk*/	5,	//norm,dest,disp							//MS 02Nov00
	/*limits*/			5,	1,	3								//MS 02Nov00
			},

	/*name*/{UID_FA_Woolston,
	/*real*/	TT_SPITASSEMBLY,TP_FIGHTERFACTORY,0,AB(HIGH,MED),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_CV_ISLEOFWIGHT,UID_CV_CHICHESTER,UID_CV_PORTSMOUTH},
	/*sec trg*/	{UID_DK_Southampton,UID_FA_Switchgear,UID_FA_Itchen,UID_FA_ThornycroftMotors,UID_AF_MIDDLEWALLOP},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTWOOLST,
	/*detail*/	{FIL_1_MBWOOLST},
	/*per wk*/	28,	//norm,dest,disp							//MS 02Nov00
	/*limits*/			28,	8,	22								//MS 02Nov00
			},

	/*name*/{UID_FA_CastleBromwich,
	/*real*/	TT_SPITASSEMBLY,TP_FIGHTERFACTORY,0,AB(LOW,LOW),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTCASTLE,
	/*detail*/	{FIL_1_MBCASTLE},
	/*per wk*/	0,	//norm,dest,disp							//MS 02Nov00
	/*limits*/			2,	1,	2								//MS 02Nov00
			},

	/*name*/{UID_FA_Switchgear,
	/*real*/	TT_HURRPARTS,TP_COMPONENTFACTORY,0,AB(HIGH,MED),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_CV_ISLEOFWIGHT,UID_CV_CHICHESTER,UID_CV_PORTSMOUTH},
	/*sec trg*/	{UID_DK_Southampton,UID_FA_Itchen,UID_FA_Woolston,UID_FA_ThornycroftMotors,UID_AF_MIDDLEWALLOP},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTSWITCH,
	/*detail*/	{FIL_1_MBSWITCH},
	/*per wk*/	10,	//norm,dest,disp							//MS 02Nov00
	/*limits*/			10,	2,	8								//MS 02Nov00
			},
//DeadCode MS 10Mar00 	/*name*/{UID_FA_Weybridge,
//DeadCode MS 10Mar00 	/*real*/	TT_SPITASSEMBLY,TP_FACTORY,0,AB(LOW,HIGH),
//DeadCode MS 10Mar00 	/*false*/	TT_INDUSTRY,TP_OTHERFACTORY,-1,
//DeadCode MS 10Mar00 	/*turn pt*/	{UID_NULL,UID_CV_GUILFORD,UID_NB_Portsmouth},
//DeadCode MS 10Mar00 	/*sec trg*/	{UID_FA_BrooklandsHawker,UID_FA_BrooklandsHawker,UID_AF_CROYDON,UID_AF_KENLEY,UID_AF_BIGGINHILL},
//DeadCode MS 10Mar00 	/*damage*/ 	&DR_LargeFactory,
//DeadCode MS 10Mar00 	/*dates*/		{DAM(NONE)},
//DeadCode MS 10Mar00 	/*bfield*/	 FIL_1_FTWEYBRI,
//DeadCode MS 10Mar00 	/*detail*/	{FIL_1_MBWEYBRI},
//DeadCode MS 10Mar00 	/*per wk*/	45,	//norm,dest,disp
//DeadCode MS 10Mar00 	/*limits*/			60,	5,	50
//DeadCode MS 10Mar00 			},

	/*name*/{UID_FA_Westland,
	/*real*/	TT_SPITPARTS,TP_COMPONENTFACTORY,0,AB(LOW,LOW),
	/*false*/	TT_UNKNOWNAIRCRAFT,TP_FACTORY,-1,
	/*turn pt*/	{UID_DURISTN,UID_NAV1},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTWESTLA,
	/*detail*/	{FIL_1_MBWESTLA},
	/*per wk*/	10,	//norm,dest,disp
	/*limits*/			10,	2,	6
			},

	/*name*/{UID_FA_ThornycroftMotors,
	/*real*/	TT_SPITPARTS,TP_COMPONENTFACTORY,0,AB(MED,MED),
	/*false*/	TT_CARS,TP_FACTORY,-1,
	/*turn pt*/	{UID_CV_ISLEOFWIGHT,UID_CV_CHICHESTER,UID_CV_PORTSMOUTH},
	/*sec trg*/	{UID_DK_Southampton,UID_FA_Switchgear,UID_FA_Woolston,UID_FA_Itchen,UID_AF_MIDDLEWALLOP},
	/*damage*/ 	&DR_LargeFactory,
	/*dates*/		{DAM(NONE)},
	/*bfield*/	 FIL_1_FTTHORNY,
	/*detail*/	{FIL_1_MBTHORNY},
	/*per wk*/	2,	//norm,dest,disp
	/*limits*/			2,	0,	2
			},

	//next item:


		{UID_NULL}
	};

	II_TargetConvoy			NodeData::convoys[]=
	{
//DEADCODE RJS 03/02/00 	/*name*/{UID_NULL,
//DEADCODE RJS 03/02/00 	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
//DEADCODE RJS 03/02/00 	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
//DEADCODE RJS 03/02/00 	/*turn pt*/	{UID_NULL},
//DEADCODE RJS 03/02/00 	/*sec trg*/	{UID_NULL},
//DEADCODE RJS 03/02/00 	/*damage*/ 	&DR_Convoy,
//DEADCODE RJS 03/02/00 	/*dates*/		{DAM(NONE,0July,12),DAM(NONE,0July,13),DAM(NONE,0July,14)},
//DEADCODE RJS 03/02/00 	/*bfield*/	 FIL_CVY_BREAD
//DEADCODE RJS 03/02/00 			},
//DeadCode MS 24Jul00 	/*name*/{UID_CONV_D1C1,
//DeadCode MS 24Jul00 	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
//DeadCode MS 24Jul00 	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
//DeadCode MS 24Jul00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 24Jul00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 24Jul00 	/*damage*/ 	&DR_Convoy,
//DeadCode MS 24Jul00 	/*dates*/		{DATE(0July,12),DATE(0July,13),DATE(0July,14)},
//DeadCode MS 24Jul00 	/*bfield*/	 FIL_1_D1C1
//DeadCode MS 24Jul00 			},
//DeadCode MS 24Jul00 	/*name*/{UID_CONV_1,
//DeadCode MS 24Jul00 	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
//DeadCode MS 24Jul00 	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
//DeadCode MS 24Jul00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 24Jul00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 24Jul00 	/*damage*/ 	&DR_Convoy,
//DeadCode MS 24Jul00 	/*dates*/		{DATE(0July,11),DATE(0July,12)},
//DeadCode MS 24Jul00 	/*bfield*/	 FIL_1_CVY1
//DeadCode MS 24Jul00 			},
//DeadCode MS 24Jul00 	/*name*/{UID_CONV_2,
//DeadCode MS 24Jul00 	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
//DeadCode MS 24Jul00 	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
//DeadCode MS 24Jul00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 24Jul00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 24Jul00 	/*damage*/ 	&DR_Convoy,
//DeadCode MS 24Jul00 	/*dates*/		{DATE(0July,11),DATE(0July,12)},
//DeadCode MS 24Jul00 	/*bfield*/	 FIL_1_CVY2
//DeadCode MS 24Jul00 			},
//DeadCode MS 24Jul00 	/*name*/{UID_CONV_3,
//DeadCode MS 24Jul00 	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
//DeadCode MS 24Jul00 	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
//DeadCode MS 24Jul00 	/*turn pt*/	{UID_NULL},
//DeadCode MS 24Jul00 	/*sec trg*/	{UID_NULL},
//DeadCode MS 24Jul00 	/*damage*/ 	&DR_Convoy,
//DeadCode MS 24Jul00 	/*dates*/		{DATE(0July,11),DATE(0July,12)},
//DeadCode MS 24Jul00 	/*bfield*/	 FIL_1_CVY3
//DeadCode MS 24Jul00 			},
	/*name*/{UID_CVY_G1_A,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,10),DATE(0July,22),DATE(0July,30)},
	/*bfield*/	 FIL_1_CVY_G1_A
			},
	/*name*/{UID_CVY_G1_B,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,16),DATE(0Aug,22)},
	/*bfield*/	 FIL_1_CVY_G1_B
			},
	/*name*/{UID_CVY_G1_C,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,11),DATE(0July,15)},
//Following line is a test and should be commented out
//TempCode MS 16Aug00 	/*dates*/		{DATE(0July,10),DATE(0July,11),DATE(0July,15)},
	/*bfield*/	 FIL_1_CVY_G1_C
			},
	/*name*/{UID_CVY_G1_D,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,29)},
	/*bfield*/	 FIL_1_CVY_G1_D
			},
	/*name*/{UID_CVY_G1_E,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,24),DATE(0July,31)},
	/*bfield*/	 FIL_1_CVY_G1_E
			},
	/*name*/{UID_CVY_G1_F,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,13),DATE(0July,19)},
	/*bfield*/	 FIL_1_CVY_G1_F
			},
	/*name*/{UID_CVY_G2_A,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,15),DATE(0July,19)},
	/*bfield*/	 FIL_1_CVY_G2_A
			},
	/*name*/{UID_CVY_G2_B,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,19),DATE(0July,26)},
	/*bfield*/	 FIL_1_CVY_G2_B
			},
	/*name*/{UID_CVY_G2_C,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,20),DATE(0July,28),DATE(0Aug,1)},
	/*bfield*/	 FIL_1_CVY_G2_C
			},
	/*name*/{UID_CVY_G2_D,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,14),DATE(0July,19),DATE(0July,22)},
	/*bfield*/	 FIL_1_CVY_G2_D
			},
	/*name*/{UID_CVY_G2_E,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,22)},
	/*bfield*/	 FIL_1_CVY_G2_E
			},
	/*name*/{UID_CVY_G2_F,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,10)},
	/*bfield*/	 FIL_1_CVY_G2_F
			},
	/*name*/{UID_CVY_G3_A,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,13),DATE(0July,14),DATE(0July,30),DATE(0Aug,7)},
	/*bfield*/	 FIL_1_CVY_G3_A
			},
	/*name*/{UID_CVY_G3_B,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,12),DATE(0July,25)},
	/*bfield*/	 FIL_1_CVY_G3_B
			},
	/*name*/{UID_CVY_G3_C,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,12),DATE(0July,27),DATE(0July,31)},
	/*bfield*/	 FIL_1_CVY_G3_C
			},
	/*name*/{UID_CVY_G3_D,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,15),DATE(0July,25),DATE(0July,27),DATE(0July,28),DATE(0Aug,8)},
	/*bfield*/	 FIL_1_CVY_G3_D
			},
	/*name*/{UID_CVY_G3_E,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,19)},
	/*bfield*/	 FIL_1_CVY_G3_E
			},
	/*name*/{UID_CVY_G3_F,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,21),DATE(0Aug,8)},
	/*bfield*/	 FIL_1_CVY_G3_F
			},
	/*name*/{UID_CVY_G4_A,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,21),DATE(0Aug,8)},
	/*bfield*/	 FIL_1_CVY_G4_A
			},
	/*name*/{UID_CVY_G4_B,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,15),DATE(0July,27),DATE(0Aug,5),DATE(0Aug,12)},
	/*bfield*/	 FIL_1_CVY_G4_B
			},
	/*name*/{UID_CVY_G4_C,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,24),DATE(0Aug,12)},
	/*bfield*/	 FIL_1_CVY_G4_C
			},
	/*name*/{UID_CVY_G4_D,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,29),DATE(0Aug,5)},
	/*bfield*/	 FIL_1_CVY_G4_D
			},
	/*name*/{UID_CVY_G4_E,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,26)},
	/*bfield*/	 FIL_1_CVY_G4_E
			},
	/*name*/{UID_CVY_G4_F,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,19)},
	/*bfield*/	 FIL_1_CVY_G4_F
			},
	/*name*/{UID_CVY_G5_A,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,13),DATE(0July,23),DATE(0Aug,1),DATE(0Aug,15)},
	/*bfield*/	 FIL_1_CVY_G5_A
			},
	/*name*/{UID_CVY_G5_B,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,11),DATE(0July,13),DATE(0July,23),DATE(0Aug,10)},
	/*bfield*/	 FIL_1_CVY_G5_B
			},
	/*name*/{UID_CVY_G5_C,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,12),DATE(0July,24),DATE(0Aug,2),DATE(0Aug,5)},
	/*bfield*/	 FIL_1_CVY_G5_C
			},
	/*name*/{UID_CVY_G5_D,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0Aug,2)},
	/*bfield*/	 FIL_1_CVY_G5_D
			},
	/*name*/{UID_CVY_G6_A,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,11),DATE(0July,15),DATE(0July,23),DATE(0July,25),DATE(0Aug,1),DATE(0Aug,9),DATE(0Aug,14)},
	/*bfield*/	 FIL_1_CVY_G6_A
			},
	/*name*/{UID_CVY_G6_B,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,18),DATE(0July,26),DATE(0Aug,1),DATE(0Aug,11)},
	/*bfield*/	 FIL_1_CVY_G6_B
			},
	/*name*/{UID_CVY_G6_C,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,17),DATE(0July,31),DATE(0Aug,4)},
	/*bfield*/	 FIL_1_CVY_G6_C
			},
	/*name*/{UID_CVY_G6_D,
	/*real*/	TT_CONVOY,TP_CONVOY,0,AB(LOW,LOW),
	/*false*/	TT_AS_KNOWN,TP_AS_KNOWN,-1,
	/*turn pt*/	{UID_NULL},
	/*sec trg*/	{UID_NULL},
	/*damage*/ 	&DR_Convoy,
	/*dates*/		{DATE(0July,18),DATE(0July,20),DATE(0Aug,22),DATE(0Aug,3)},
	/*bfield*/	 FIL_1_CVY_G6_D
			},

//next item:


	{UID_NULL}
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		britsquadinst
//Author		Jim
//Date			Tue 23 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
enum	MARKINGLETTERS
{
	ML_A=0,
	ML_B,
	ML_C,
	ML_D,
	ML_E,
	ML_F,
	ML_G,
	ML_H,
	ML_I,
	ML_J,
	ML_K,
	ML_L,
	ML_M,
	ML_N,
	ML_O,
	ML_P,
	ML_Q,
	ML_R,
	ML_S,
	ML_T,
	ML_U,
	ML_V,
	ML_W,
	ML_X,
	ML_Y,
	ML_Z,
	ML_0,
	ML_1,
	ML_2,
	ML_3,
	ML_4,
	ML_5,
	ML_6,
	ML_7,
	ML_8,
	ML_9,	//36 markings
	ML_BLANK,		ML_MGR1=ML_0,
	ML_HORI,		ML_MGR2=ML_1,
	ML_VERT,		ML_MGR3=ML_2,
	ML_PLUS,

	//
	ML_B2I=0, //109 squadrons
	ML_B2II,
	ML_B2III,
	ML_B3I  ,
	ML_B3II ,
	ML_B3III,
	ML_B26I  ,
	ML_B26II ,
	ML_B26III,
	ML_B27I  ,
	ML_B27II ,
	ML_B27III,
	ML_B51I  ,
	ML_B51II ,
	ML_B51III,
	ML_B52I  ,
	ML_B52II ,
	ML_B52III,
	ML_B53I  ,
	ML_B53II ,
	ML_B53III,
	ML_B54I  ,
	ML_B54II ,
	ML_B54III,

	ML_BZ2I  ,
	ML_BZ2II ,
	ML_BZ2III,
	ML_BZ26I  , //110 squadrons
	ML_BZ26II , //110 squadrons
	ML_BZ26III, //110 squadrons
	ML_BZ76I  ,
	ML_BZ76II ,
	ML_BZ76III,

	ML_ONEPLACE=40,
	ML_SKRAF=64000,		//can then add 2 symbols easily
	ML_SKLWB=0,
	ML_SKLWF=ML_0*ML_ONEPLACE+ML_SKRAF
};
//rules:
//The LW bomber markings are 4 letters and numbers mixed. 3 are squadron specific.
//-Encoded as 3 values at *40 intervals
//The RAF markings are 2 letters per squadron then 1 letter for aircraft number 
//-Encoded as 2 values at *40 intervals + 64000
//The LW fighter scheme is 1 badge, then a/c number and gruppen mark
//-Encoded as 64000+gruppmark*40+badge(0-40)
#define	LWB_MARK(x,y,z)	(ML_##x+ML_ONEPLACE*ML_##y+ML_ONEPLACE*ML_ONEPLACE*ML_##z)
#define	RAF_MARK(x,y)	(ML_SKRAF+ML_##x+ML_ONEPLACE*ML_##y)
#define	LWF_MARK(x,y)	(ML_SKRAF+ML_B##x+ML_ONEPLACE*ML_##y)

II_BritSquadron			NodeData::britsquadinst[]=
{
/*squad*/	{SQ_BR_32,
/*leader*/		IDS_32Leader,IDS_32Replace,
/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE,							//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_REGULAR,					//MS 03Nov00
/*airfield*/	UID_AF_BIGGINHILL,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(G,Z),0,
/*type*/		PT_HURR_A,
/*baseno*/		1
			},

/*squad*/	{SQ_BR_610,
/*leader*/		IDS_610Leader,IDS_610Replace,
/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE1,						//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_REGULAR1,					//MS 03Nov00
/*airfield*/	UID_AF_BIGGINHILL		,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(D,W),0,
/*type*/		PT_SPIT_B,
/*baseno*/		2
			},

/*squad*/	{SQ_BR_501,
/*leader*/		IDS_501Leader,IDS_501Replace,
/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE2,						//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_REGULAR2,						//MS 03Nov00
/*airfield*/	UID_AF_GRAVESEND,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(S,D),0,
/*type*/		PT_HURR_A,
/*baseno*/		3
			},

/*squad*/	{SQ_BR_56,
/*leader*/		IDS_56Leader,IDS_56Replace,
/*lead stats*/	MORALE_GOOD,SKILL_VETERAN2,						//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_VETERAN,						//MS 03Nov00
/*airfield*/	UID_AF_NORTHWEALD,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(U,S),0,
/*type*/		PT_HURR_A,
/*baseno*/		4
			},

/*squad*/	{SQ_BR_151,
/*leader*/		IDS_151Leader,IDS_151Replace,
/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE,						//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_VETERAN1,					//MS 03Nov00
/*airfield*/	UID_AF_MANSTON,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(D,Z),0,
/*type*/		PT_HURR_B,
/*baseno*/		5
			},

/*squad*/	{SQ_BR_85,
/*leader*/		IDS_85Leader,IDS_85Replace,
/*lead stats*/	MORALE_EXCELLENT,SKILL_ACE1,					//MS 03Nov00
/*ave stats*/	MORALE_TOPMORALE,SKILL_VETERAN2,				//MS 03Nov00
/*airfield*/	UID_AF_DEBDEN,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(V,Y),0,
/*type*/		PT_HURR_A,
/*baseno*/		6
			},

/*squad*/	{SQ_BR_64,
/*leader*/		IDS_64Leader,IDS_64Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_ACE1,						//MS 03Nov00
/*ave stats*/	MORALE_EXCELLENT,SKILL_ACE,						//MS 03Nov00
/*airfield*/	UID_AF_KENLEY,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(S,H),0,
/*type*/		PT_SPIT_A,
/*baseno*/		7
			},

/*squad*/	{SQ_BR_615,
/*leader*/		IDS_615Leader,IDS_615Replace,
/*lead stats*/	MORALE_GOOD,SKILL_ACE2,							//MS 03Nov00
/*ave stats*/	MORALE_MEDIUM,SKILL_ACE1,						//MS 03Nov00
/*airfield*/	UID_AF_KENLEY,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(K,W),0,
/*type*/		PT_HURR_A,
/*baseno*/		8
			},

/*squad*/	{SQ_BR_111,
/*leader*/		IDS_111Leader,IDS_111Replace,
/*lead stats*/	MORALE_GOOD,SKILL_HERO,							//MS 03Nov00
/*ave stats*/	MORALE_MEDIUM,SKILL_ACE2,						//MS 03Nov00
/*airfield*/	UID_AF_CROYDON,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(J,U),0,
/*type*/		PT_HURR_A,
/*baseno*/		9
			},

/*squad*/	{SQ_BR_1Can,
/*leader*/		IDS_1CanLeader,IDS_1CanReplace,
/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE,							//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_REGULAR,						//MS 03Nov00
/*airfield*/	UID_AF_CROYDON,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(Y,O),0,
/*type*/		PT_HURR_A,
/*baseno*/		10
			},

/*squad*/	{SQ_BR_54,
/*leader*/		IDS_54Leader,IDS_54Replace,
/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE1,						//MS 03Nov00
/*ave stats*/	MORALE_TOPMORALE,SKILL_REGULAR1,				//MS 03Nov00
/*airfield*/	UID_AF_ROCHFORD,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(K,L),0,
/*type*/		PT_SPIT_A,
/*baseno*/		11
			},

/*squad*/	{SQ_BR_65,
/*leader*/		IDS_65Leader,IDS_65Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_ACE2,						//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_REGULAR2,					//MS 03Nov00
/*airfield*/	UID_AF_HORNCHURCH,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(Y,T),0,
/*type*/		PT_SPIT_B,
/*baseno*/		12
			},

/*squad*/	{SQ_BR_74,
/*leader*/		IDS_74Leader,IDS_74Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_VETERAN2,					//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_VETERAN,					//MS 03Nov00
/*airfield*/	UID_AF_HORNCHURCH,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(Z,P),0,
/*type*/		PT_SPIT_A,
/*baseno*/		13
			},

/*squad*/	{SQ_BR_266,
/*leader*/		IDS_266Leader,IDS_266Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_ACE,						//MS 03Nov00
/*ave stats*/	MORALE_MEDIUM,SKILL_VETERAN1,						//MS 03Nov00
/*airfield*/	UID_AF_WITTERING,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(U,O),0,
/*type*/		PT_SPIT_A,
/*baseno*/		14
			},

/*squad*/	{SQ_BR_43,
/*leader*/		IDS_43Leader,IDS_43Replace,
/*lead stats*/	MORALE_GOOD,SKILL_ACE1,							//MS 03Nov00
/*ave stats*/	MORALE_MEDIUM,SKILL_VETERAN2,					//MS 03Nov00
/*airfield*/	UID_AF_TANGMERE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(F,T),0,
/*type*/		PT_HURR_A,
/*baseno*/		15
			},

/*squad*/	{SQ_BR_601,
/*leader*/		IDS_601Leader,IDS_601Replace,
/*lead stats*/	MORALE_GOOD,SKILL_ACE1,							//MS 03Nov00
/*ave stats*/	MORALE_EXCELLENT,SKILL_ACE,						//MS 03Nov00
/*airfield*/	UID_AF_TANGMERE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(U,F),0,
/*type*/		PT_HURR_A,
/*baseno*/		16
			},

/*squad*/	{SQ_BR_145,
/*leader*/		IDS_145Leader,IDS_145Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_ACE2,						//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_ACE1,							//MS 03Nov00
/*airfield*/	UID_AF_WESTHAMPNETT,	//UID_AF_TANGMERE,		//MS 14Nov00
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(S,O),0,
/*type*/		PT_HURR_A,
/*baseno*/		17
			},

/*squad*/	{SQ_BR_17,
/*leader*/		IDS_17Leader,IDS_17Replace,
/*lead stats*/	MORALE_TOPMORALE,SKILL_HERO,					//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_ACE2,						//MS 03Nov00
/*airfield*/	UID_AF_DEBDEN,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(Y,B),0,
/*type*/		PT_HURR_A,
/*baseno*/		18
			},

/*squad*/	{SQ_BR_85x,
/*leader*/		IDS_85xLeader,IDS_85xReplace,
/*lead stats*/	MORALE_GOOD,SKILL_ACE,							//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_REGULAR,					//MS 03Nov00
/*airfield*/	UID_AF_DEBDEN,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(V,Y),0,
/*type*/		PT_HURR_A,
/*baseno*/		19
			},

/*squad*/	{SQ_BR_1,
/*leader*/		IDS_1Leader,IDS_1Replace,
/*lead stats*/	MORALE_GOOD,SKILL_ACE1,							//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_REGULAR1,					//MS 03Nov00
/*airfield*/	UID_AF_HAWKINGE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(J,X),0,
/*type*/		PT_HURR_A,
/*baseno*/		20
			},

/*squad*/	{SQ_BR_257,
/*leader*/		IDS_257Leader,IDS_257Replace,
/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE2,							//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_REGULAR2,						//MS 03Nov00
/*airfield*/	UID_AF_NORTHOLT,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(D,T),0,
/*type*/		PT_HURR_A,
/*baseno*/		21
			},

/*squad*/	{SQ_BR_303,//POLISH
/*leader*/		IDS_303Leader,IDS_303Replace,
/*lead stats*/	MORALE_VERYGOOD,SKILL_VETERAN2,					//MS 03Nov00
/*ave stats*/	MORALE_TOPMORALE,SKILL_VETERAN,					//MS 03Nov00
/*airfield*/	UID_AF_NORTHOLT,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(R,F),0,
/*type*/		PT_HURR_A,
/*baseno*/		22
			},

/*squad*/	{SQ_BR_87,
/*leader*/		IDS_87Leader,IDS_87Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_ACE,						//MS 03Nov00
/*ave stats*/	MORALE_MEDIUM,SKILL_VETERAN1,						//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(L,K),0,
/*type*/		PT_HURR_A,
/*baseno*/		23
			},

/*squad*/	{SQ_BR_213,
/*leader*/		IDS_213Leader,IDS_213Replace,
/*lead stats*/	MORALE_GOOD,SKILL_ACE1,							//MS 03Nov00
/*ave stats*/	MORALE_MEDIUM,SKILL_VETERAN2,					//MS 03Nov00
/*airfield*/	UID_AF_EXETER,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(A,K),0,
/*type*/		PT_HURR_A,
/*baseno*/		24
			},

/*squad*/	{SQ_BR_238,
/*leader*/		IDS_238Leader,IDS_238Replace,
/*lead stats*/	MORALE_GOOD,SKILL_ACE1,							//MS 03Nov00
/*ave stats*/	MORALE_EXCELLENT,SKILL_ACE,						//MS 03Nov00
/*airfield*/	UID_AF_MIDDLEWALLOP,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(V,K),0,
/*type*/		PT_HURR_A,
/*baseno*/		25
			},

/*squad*/	{SQ_BR_609,
/*leader*/		IDS_609Leader,IDS_609Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_ACE2,						//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_ACE1,							//MS 03Nov00
/*airfield*/	UID_AF_MIDDLEWALLOP,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(P,R),0,
/*type*/		PT_SPIT_A,
/*baseno*/		26
			},

/*squad*/	{SQ_BR_152,
/*leader*/		IDS_152Leader,IDS_152Replace,
/*lead stats*/	MORALE_TOPMORALE,SKILL_HERO,					//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_ACE2,						//MS 03Nov00
/*airfield*/	UID_AF_WARMWELL,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(S,N),0,
/*type*/		PT_SPIT_A,
/*baseno*/		27
			},

/*squad*/	{SQ_BR_234,
/*leader*/		IDS_234Leader,IDS_234Replace,
/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE,						//MS 03Nov00
/*ave stats*/	MORALE_EXCELLENT,SKILL_REGULAR,					//MS 03Nov00
/*airfield*/	UID_AF_EXETER,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(A,Z),0,
/*type*/		PT_SPIT_A,
/*baseno*/		28
			},

/*squad*/	{SQ_BR_92,
/*leader*/		IDS_92Leader,IDS_92Replace,
/*lead stats*/	MORALE_TOPMORALE,SKILL_ACE1,					//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_REGULAR1,					//MS 03Nov00
/*airfield*/	UID_AF_PEMBREY,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(Q,J),0,
/*type*/		PT_SPIT_A,
/*baseno*/		29
			},

/*squad*/	{SQ_BR_310,	//CZECH
/*leader*/		IDS_310Leader,IDS_310Replace,
/*lead stats*/	MORALE_EXCELLENT,SKILL_ACE2,					//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_REGULAR2,						//MS 03Nov00
/*airfield*/	UID_AF_DUXFORD,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(N,N),0,
/*type*/		PT_HURR_A,
/*baseno*/		30
			},

/*squad*/	{SQ_BR_19,
/*leader*/		IDS_19Leader,IDS_19Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_VETERAN2,					//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_VETERAN,						//MS 03Nov00
/*airfield*/	UID_AF_FOWLMERE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(Q,V),0,
/*type*/		PT_SPIT_A,
/*baseno*/		31
			},

/*squad*/	{SQ_BR_66,
/*leader*/		IDS_66Leader,IDS_66Replace,
/*lead stats*/	MORALE_TOPMORALE,SKILL_ACE,						//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_VETERAN1,					//MS 03Nov00
/*airfield*/	UID_AF_COLTISHALL,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(L,Z),0,
/*type*/		PT_SPIT_A,
/*baseno*/		32
			},

/*squad*/	{SQ_BR_242,
/*leader*/		IDS_242Leader,IDS_242Replace,
/*lead stats*/	MORALE_VERYGOOD,SKILL_HERO,						//MS 03Nov00
/*ave stats*/	MORALE_EXCELLENT,SKILL_ACE2,				//MS 03Nov00
/*airfield*/	UID_AF_COLTISHALL,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(L,E),0,
/*type*/		PT_HURR_A,
/*baseno*/		33
			},

/*squad*/	{SQ_BR_222,
/*leader*/		IDS_222Leader,IDS_222Replace,
/*lead stats*/	MORALE_TOPMORALE,SKILL_ACE1,					//MS 03Nov00
/*ave stats*/	MORALE_MEDIUM,SKILL_ACE,						//MS 03Nov00
/*airfield*/	UID_AF_KIRTON,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(Z,D),0,
/*type*/		PT_SPIT_A,
/*baseno*/		34
			},

/*squad*/	{SQ_BR_611,
/*leader*/		IDS_611Leader,IDS_611Replace,
/*lead stats*/	MORALE_EXCELLENT,SKILL_ACE2,					//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_ACE1,						//MS 03Nov00
/*airfield*/	UID_AF_DIGBY,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(F,Y),0,
/*type*/		PT_SPIT_A,
/*baseno*/		35
			},

/*squad*/	{SQ_BR_46,
/*leader*/		IDS_46Leader,IDS_46Replace,
/*lead stats*/	MORALE_VERYGOOD,SKILL_HERO,						//MS 03Nov00
/*ave stats*/	MORALE_EXCELLENT,SKILL_ACE2,					//MS 03Nov00
/*airfield*/	UID_AF_DIGBY,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(P,O),0,
/*type*/		PT_HURR_A,
/*baseno*/		36
			},

/*squad*/	{SQ_BR_229,
/*leader*/		IDS_229Leader,IDS_229Replace,
/*lead stats*/	MORALE_TOPMORALE,SKILL_ACE,						//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_REGULAR,					//MS 03Nov00
/*airfield*/	UID_AF_WITTERING,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(K,E),0,
/*type*/		PT_HURR_A,
/*baseno*/		37
			},

/*squad*/	{SQ_BR_72,
/*leader*/		IDS_72Leader,IDS_72Replace,
/*lead stats*/	MORALE_EXCELLENT,SKILL_ACE1,					//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_REGULAR1,						//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(R,N),0,
/*type*/		PT_SPIT_A,
/*baseno*/		38
			},

/*squad*/	{SQ_BR_249,
/*leader*/		IDS_249Leader,IDS_249Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_ACE2,						//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_REGULAR2,						//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(G,N),0,
/*type*/		PT_HURR_A,
/*baseno*/		39
			},

/*squad*/	{SQ_BR_253,
/*leader*/		IDS_253Leader,IDS_253Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_VETERAN2,					//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_VETERAN,						//MS 03Nov00
/*airfield*/	UID_AF_KIRTON,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(S,W),0,
/*type*/		PT_HURR_A,
/*baseno*/		40
			},

/*squad*/	{SQ_BR_605,
/*leader*/		IDS_605Leader,IDS_605Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_ACE,							//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_VETERAN1,					//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(U,P),0,
/*type*/		PT_HURR_A,
/*baseno*/		41
			},

/*squad*/	{SQ_BR_603,
/*leader*/		IDS_603Leader,IDS_603Replace,
/*lead stats*/	MORALE_TOPMORALE,SKILL_ACE1,					//MS 03Nov00
/*ave stats*/	MORALE_MEDIUM,SKILL_VETERAN2,					//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(X,T),0,
/*type*/		PT_SPIT_A,
/*baseno*/		42
			},

/*squad*/	{SQ_BR_41,
/*leader*/		IDS_41Leader,IDS_41Replace,
/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE1,						//MS 03Nov00
/*ave stats*/	MORALE_MEDIUM,SKILL_ACE,						//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(E,B),0,
/*type*/		PT_SPIT_A,
/*baseno*/		43
			},

/*squad*/	{SQ_BR_607,
/*leader*/		IDS_607Leader,IDS_607Replace,
/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE2,						//MS 03Nov00
/*ave stats*/	MORALE_MEDIUM,SKILL_ACE1,						//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(A,F),0,
/*type*/		PT_HURR_A,
/*baseno*/		44
			},

/*squad*/	{SQ_BR_602,
/*leader*/		IDS_602Leader,IDS_602Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_HERO,							//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_ACE2,							//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(L,O),0,
/*type*/		PT_SPIT_A,
/*baseno*/		45
			},

/*squad*/	{SQ_BR_73,
/*leader*/		IDS_73Leader,IDS_73Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_ACE,						//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_REGULAR,						//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(T,P),0,
/*type*/		PT_HURR_A,
/*baseno*/		46
			},

/*squad*/	{SQ_BR_504,
/*leader*/		IDS_504Leader,IDS_504Replace,
/*lead stats*/	MORALE_EXCELLENT,SKILL_ACE1,					//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_REGULAR1,					//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(T,M),0,
/*type*/		PT_HURR_A,
/*baseno*/		47
			},

/*squad*/	{SQ_BR_79,
/*leader*/		IDS_79Leader,IDS_79Replace,
/*lead stats*/	MORALE_GOOD,SKILL_ACE2,							//MS 03Nov00
/*ave stats*/	MORALE_TOPMORALE,SKILL_REGULAR2,				//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(N,V),0,
/*type*/		PT_HURR_A,
/*baseno*/		48
			},

/*squad*/	{SQ_BR_302,//POLISH
/*leader*/		IDS_302Leader,IDS_302Replace,
/*lead stats*/	MORALE_VERYGOOD,SKILL_VETERAN2,					//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_VETERAN,						//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(W,X),0,
/*type*/		PT_HURR_A,
/*baseno*/		49
			},

/*squad*/	{SQ_BR_616,
/*leader*/		IDS_616Leader,IDS_616Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_ACE,						//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_VETERAN1,						//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(Y,Q),0,
/*type*/		PT_SPIT_A,
/*baseno*/		50
			},

/*squad*/	{SQ_BR_3,
/*leader*/		IDS_3Leader,IDS_3Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_ACE1,						//MS 03Nov00
/*ave stats*/	MORALE_GOOD,SKILL_VETERAN2,						//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(Q,O),0,
/*type*/		PT_HURR_B,
/*baseno*/		51
			},

/*squad*/	{SQ_BR_232,
/*leader*/		IDS_232Leader,IDS_232Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_ACE1,							//MS 03Nov00
/*ave stats*/	MORALE_VERYGOOD,SKILL_ACE,						//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(E,F),0,
/*type*/		PT_HURR_A,
/*baseno*/		52
			},

/*squad*/	{SQ_BR_245,
/*leader*/		IDS_245Leader,IDS_245Replace,
/*lead stats*/	MORALE_TOPMORALE,SKILL_ACE2,					//MS 03Nov00
/*ave stats*/	MORALE_MEDIUM,SKILL_ACE1,						//MS 03Nov00
/*airfield*/	UID_AF_NEWCASTLE,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(D,X),0,
/*type*/		PT_HURR_A,
/*baseno*/		53
			},

	{SQ_ZERO},

/*squad*/	{SQ_BR_DEFIENT,
/*leader*/		IDS_232Leader,IDS_232Replace,
/*lead stats*/	MORALE_MEDIUM,SKILL_VETERAN,
/*ave stats*/	MORALE_VERYGOOD,SKILL_REGULAR2,
/*airfield*/	UID_AF_DUXFORD,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(E,F),0,
/*type*/		PT_DEFIANT,
/*baseno*/		52
			},

/*squad*/	{SQ_BR_BLENHEIM,
/*leader*/		IDS_245Leader,IDS_245Replace,
/*lead stats*/	MORALE_TOPMORALE,SKILL_VETERAN1,
/*ave stats*/	MORALE_MEDIUM,SKILL_VETERAN1,
/*airfield*/	UID_AF_DUXFORD,
/*available*/	3+16,16,
/*repairs*/		0,0,
/*lost,tote*/	0,Profile::PS_AT_30,
/*markings*/	Squadron::NO_FLYING,RAF_MARK(D,X),0,
/*type*/		PT_BLEN,
/*baseno*/		53
			},

	{SQ_ZERO},


};
II_Gruppen				NodeData::germsquadinst[]=
{
	/*squad*/	{SQ_JG_3_1,
	/*leader*/		IDS_JG_3_1_Leader,IDS_JG_3_1_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR,				//MS 03Nov00
	/*airfield*/	UID_AF_Colombert,	//UID_AF_Samer,
	/*available*/	3+36,36,		//3+35,30,					//MS 06Nov00
	/*repairs*/	 	2,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(3I,MGR1),
	/*geshwader*/	WN_JG_3,
	/*gruppen*/		GN_1
				},

	/*squad*/	{SQ_JG_3_2,
	/*leader*/		IDS_JG_3_2_Leader,IDS_JG_3_2_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE1,						//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR1,					//MS 03Nov00
	/*airfield*/	UID_AF_Desvres,	//UID_AF_Samer,
	/*available*/	3+36,36,		//3+40,34,					//MS 06Nov00
	/*repairs*/	 	0,2,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(3II,MGR2),
	/*geshwader*/	WN_JG_3,
	/*gruppen*/		GN_2
				},

	/*squad*/	{SQ_JG_3_3,
	/*leader*/		IDS_JG_3_3_Leader,IDS_JG_3_3_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE2,						//MS 03Nov00
	/*ave stats*/	MORALE_VERYGOOD,SKILL_REGULAR2,				//MS 03Nov00
	/*airfield*/	UID_AF_Samer,	//UID_AF_Desvres,
	/*available*/	3+36,36,		//3+40,34,					//MS 06Nov00
	/*repairs*/	 	0,2,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(3III,MGR3),
	/*geshwader*/	WN_JG_3,
	/*gruppen*/		GN_3
				},

	/*squad*/	{SQ_JG_26_1,
	/*leader*/		IDS_JG_26_1_Leader,IDS_JG_26_1_Replace,
	/*lead stats*/	MORALE_VERYGOOD,SKILL_VETERAN2,				//MS 03Nov00
	/*ave stats*/	MORALE_EXCELLENT,SKILL_VETERAN,				//MS 03Nov00
	/*airfield*/	UID_AF_Wissant,	//UID_AF_Audembert,
//TempCode MS 15Sep00 	/*available*/	3+36,36,		//3+40,34,//MS 06Nov00
	/*available*/	2+37,37,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(26I,MGR1),
	/*geshwader*/	WN_JG_26,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_26_2,
	/*leader*/		IDS_JG_26_2_Leader,IDS_JG_26_2_Replace,
	/*lead stats*/	MORALE_TOPMORALE,SKILL_ACE,					//MS 03Nov00
	/*ave stats*/	MORALE_MEDIUM,SKILL_VETERAN1,				//MS 03Nov00
	/*airfield*/	UID_AF_Audembert,	//UID_AF_Marquise,
	/*available*/	3+36,36,		//3+40,35,					//MS 06Nov00
	/*repairs*/	 	0,1,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(26II,MGR2),
	/*geshwader*/	WN_JG_26,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_26_3,
	/*leader*/		IDS_JG_26_3_Leader,IDS_JG_26_3_Replace,
	/*lead stats*/	MORALE_EXCELLENT,SKILL_ACE1,				//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_VETERAN2,					//MS 03Nov00
	/*airfield*/	UID_AF_Marquise,	//UID_AF_Caffiers,
	/*available*/	3+39,39,		//3+40,39,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(26III,MGR3),
	/*geshwader*/	WN_JG_26,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_51_1,
	/*leader*/		IDS_JG_51_1_Leader,IDS_JG_51_1_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE1,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_ACE,						//MS 03Nov00
	/*airfield*/	UID_AF_StOmer,	//UID_AF_Wissant,
//TempCode MS 15Sep00 	/*available*/	3+35,29,
	/*available*/	2+37,37,
	/*repairs*/	 	0,2,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(51I,MGR1),
	/*geshwader*/	WN_JG_51,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_51_2,
	/*leader*/		IDS_JG_51_2_Leader,IDS_JG_51_2_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE2,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_ACE1,						//MS 03Nov00
	/*airfield*/	UID_AF_Arques,	//UID_AF_Wissant,
	/*available*/	3+36,36,		//3+30,25,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(51II,MGR2),
	/*geshwader*/	WN_JG_51,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_51_3,
	/*leader*/		IDS_JG_51_3_Leader,IDS_JG_51_3_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_HERO,						//MS 03Nov00
	/*ave stats*/	MORALE_VERYGOOD,SKILL_ACE2,					//MS 03Nov00
	/*airfield*/	UID_AF_Tramecourt,	//UID_AF_StOmer,
	/*available*/	3+40,39,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(51III,MGR3),
	/*geshwader*/	WN_JG_51,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_52_1,
	/*leader*/		IDS_JG_52_1_Leader,IDS_JG_52_1_Replace,
	/*lead stats*/	MORALE_TOPMORALE,SKILL_ACE,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR,				//MS 03Nov00
	/*airfield*/	UID_AF_Yvrench,	//UID_AF_Cocquelles,
	/*available*/	3+40,40,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(52I,MGR1),
	/*geshwader*/	WN_JG_52,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_52_2,
	/*leader*/		IDS_JG_52_2_Leader,IDS_JG_52_2_Replace,
	/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE1,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR1,				//MS 03Nov00
	/*airfield*/	UID_AF_Abbeville,	//UID_AF_Peuplingues,
	/*available*/	3+36,30,		//3+40,35,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(52II,MGR2),
	/*geshwader*/	WN_JG_52,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_52_3,
	/*leader*/		IDS_JG_52_3_Leader,IDS_JG_52_3_Replace,
	/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE2,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR2,				//MS 03Nov00
	/*airfield*/	UID_AF_Amiens,	//UID_AF_Peuplingues,
	/*available*/	3+36,28,		//3+4,5,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(52III,MGR3),
	/*geshwader*/	WN_JG_52,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_54_1,
	/*leader*/		IDS_JG_54_1_Leader,IDS_JG_54_1_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_VETERAN2,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_VETERAN,					//MS 03Nov00
	/*airfield*/	UID_AF_Caffiers,	//UID_AF_Guines,
//TempCode MS 15Sep00 	/*available*/	3+40,34,
	/*available*/	2+37,37,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(54I,MGR1),
	/*geshwader*/	WN_JG_54,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_54_2,
	/*leader*/		IDS_JG_54_2_Leader,IDS_JG_54_2_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_VETERAN1,					//MS 03Nov00
	/*airfield*/	UID_AF_Guines,	//UID_AF_Hermelinghen,
	/*available*/	3+38,38,									//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(54II,MGR2),
	/*geshwader*/	WN_JG_54,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_54_3,
	/*leader*/		IDS_JG_54_3_Leader,IDS_JG_54_3_Replace,
	/*lead stats*/	MORALE_EXCELLENT,SKILL_ACE1,				//MS 03Nov00
	/*ave stats*/	MORALE_MEDIUM,SKILL_VETERAN2,				//MS 03Nov00
	/*airfield*/	UID_AF_Hermelinghen,	//UID_AF_Guines,
	/*available*/	3+36,36,		//3+40,36,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(54III,MGR3),
	/*geshwader*/	WN_JG_54,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_ZG_26_1,
	/*leader*/		IDS_ZG_26_1_Leader,IDS_ZG_26_1_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE1,						//MS 03Nov00
	/*ave stats*/	MORALE_TOPMORALE,SKILL_ACE,					//MS 03Nov00
	/*airfield*/	UID_AF_Montdidier,	//UID_AF_StOmer,
	/*available*/	3+36,36,		//3+31,31,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(U,8,H),
	/*geshwader*/	WN_ZG_26,
	/*gruppen*/		GN_1
				},

	/*squad*/	{SQ_ZG_26_2,
	/*leader*/		IDS_ZG_26_2_Leader,IDS_ZG_26_2_Replace,
	/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE2,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_ACE1,						//MS 03Nov00
	/*airfield*/	UID_AF_Beauvais,	//UID_AF_StOmer,
	/*available*/	3+36,36,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
//TempCode MS 31Jul00 	/*markings*/	Squadron::NO_FLYING,LWB_MARK(BZ26II,MGR2),
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(U,8,M),
	/*geshwader*/	WN_ZG_26,
	/*gruppen*/		GN_2
				},

	/*squad*/	{SQ_ZG_26_3,
	/*leader*/		IDS_ZG_26_3_Leader,IDS_ZG_26_3_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_HERO,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_ACE2,						//MS 03Nov00
	/*airfield*/	UID_AF_Creil,	//UID_AF_Arques,
	/*available*/	3+36,30,		//3+33,33,					//MS 14Nov00
	/*repairs*/	 	0,0,										//MS 14Nov00
	/*lost,tote*/	0,Profile::PS_AT_30,
//TempCode MS 31Jul00 	/*markings*/	Squadron::NO_FLYING,LWB_MARK(BZ26III,MGR3),
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(U,8,R),
	/*geshwader*/	WN_ZG_26,
	/*gruppen*/		GN_3
				},
	/*squad*/	{SQ_ZG_76_1,
	/*leader*/		IDS_ZG_76_1_Leader,IDS_ZG_76_1_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR,					//MS 03Nov00
	/*airfield*/	UID_AF_CormeillesEnVexin,	//UID_AF_Abbeville,
	/*available*/	3+36,36,		//3+3,3,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
//TempCode MS 31Jul00 	/*markings*/	Squadron::NO_FLYING,LWB_MARK(BZ76I,MGR1),
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(M,8,H),
	/*geshwader*/	WN_ZG_76,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_ZG_76_2,
	/*leader*/		IDS_ZG_76_2_Leader,IDS_ZG_76_2_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE1,						//MS 03Nov00
	/*ave stats*/	MORALE_VERYGOOD,SKILL_REGULAR1,				//MS 03Nov00
	/*airfield*/	UID_AF_Orly,	//UID_AF_Abbeville,
	/*available*/	3+36,30,		//3+30,30,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
//TempCode MS 31Jul00 	/*markings*/	Squadron::NO_FLYING,LWB_MARK(BZ76II,MGR2),
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(M,8,M),
	/*geshwader*/	WN_ZG_76,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_ZG_76_3,
	/*leader*/		IDS_ZG_76_3_Leader,IDS_ZG_76_3_Replace,
	/*lead stats*/	MORALE_TOPMORALE,SKILL_ACE2,				//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR2,				//MS 03Nov00
	/*airfield*/	UID_AF_Villacoublay,	//UID_AF_Yvrench,	//UID_AF_Laval,					  //JIM 07/02/00
	/*available*/	3+36,30,		//3+23,23,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
//TempCode MS 31Jul00 	/*markings*/	Squadron::NO_FLYING,LWB_MARK(BZ76III,MGR3),
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(M,8,R),
	/*geshwader*/	WN_ZG_76,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_1_1,
	/*leader*/		IDS_KG_1_1_Leader,IDS_KG_1_1_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_VETERAN2,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_VETERAN,					//MS 03Nov00
	/*airfield*/	UID_AF_Montdidier,
	/*available*/	3+30,30,				//3+28,28,			//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(V,4,H),
	/*geshwader*/	WN_KG_1,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_1_2,
	/*leader*/		IDS_KG_1_2_Leader,IDS_KG_1_2_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_VETERAN1,					//MS 03Nov00
	/*airfield*/	UID_AF_Amiens,		//UID_AF_StOmer,		//MS 06Nov00
	/*available*/	3+30,30,			//3+30,30,				//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(V,4,M),
	/*geshwader*/	WN_KG_1,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_1_3,
	/*leader*/		IDS_KG_1_3_Leader,IDS_KG_1_3_Replace,
	/*lead stats*/	MORALE_EXCELLENT,SKILL_ACE1,				//MS 03Nov00
	/*ave stats*/	MORALE_MEDIUM,SKILL_VETERAN2,				//MS 03Nov00
	/*airfield*/	UID_AF_RosieresEnSanterre,
	/*available*/	3+30,30,			//3+28,28,				//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(V,4,R),
	/*geshwader*/	WN_KG_1,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_2_1,
	/*leader*/		IDS_KG_2_1_Leader,IDS_KG_2_1_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE1,						//MS 03Nov00
	/*ave stats*/	MORALE_TOPMORALE,SKILL_ACE,					//MS 03Nov00
	/*airfield*/	UID_AF_Epinoy,
	/*available*/	3+30,30,			//3+28,28,				//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(U,5,H),
	/*geshwader*/	WN_KG_2,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_2_2,
	/*leader*/		IDS_KG_2_2_Leader,IDS_KG_2_2_Replace,
	/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE2,					//MS 03Nov00
	/*ave stats*/	MORALE_VERYGOOD,SKILL_ACE1,					//MS 03Nov00
	/*airfield*/	UID_AF_Arras,
	/*available*/	3+34,34,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(U,5,M),
	/*geshwader*/	WN_KG_2,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_2_3,
	/*leader*/		IDS_KG_2_3_Leader,IDS_KG_2_3_Replace,
	/*lead stats*/	MORALE_EXCELLENT,SKILL_HERO,				//MS 03Nov00
	/*ave stats*/	MORALE_TOPMORALE,SKILL_ACE2,				//MS 03Nov00
	/*airfield*/	UID_AF_Cambrai,
	/*available*/	32+1,32,		//3+29,29,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(U,5,R),
	/*geshwader*/	WN_KG_2,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_3_1,
	/*leader*/		IDS_KG_3_1_Leader,IDS_KG_3_1_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE,					//MS 03Nov00
	/*ave stats*/	MORALE_EXCELLENT,SKILL_REGULAR,				//MS 03Nov00
	/*airfield*/	UID_AF_Caen,	//UID_AF_LeCulot,			//MS 10Mar00
	/*available*/	32+1,32,				//3+34,34,			//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(5,K,H),
	/*geshwader*/	WN_KG_3,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_3_2,
	/*leader*/		IDS_KG_3_2_Leader,IDS_KG_3_2_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE1,						//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR1,				//MS 03Nov00
	/*airfield*/	UID_AF_Plumetot,	//UID_AF_AntwerpDeurne,
	/*available*/	3+34,34,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(5,K,M),
	/*geshwader*/	WN_KG_3,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_3_3,
	/*leader*/		IDS_KG_3_3_Leader,IDS_KG_3_3_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE2,						//MS 03Nov00
	/*ave stats*/	MORALE_TOPMORALE,SKILL_REGULAR2,			//MS 03Nov00
	/*airfield*/	UID_AF_LeHarve,//UID_AF_StTrond,	//UID_AF_StTruiden,			//MS 10Mar00
	/*available*/	3+34,34,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(5,K,R),
	/*geshwader*/	WN_KG_3,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_4_1,
	/*leader*/		IDS_KG_4_1_Leader,IDS_KG_4_1_Replace,
	/*lead stats*/	MORALE_VERYGOOD,SKILL_VETERAN2,				//MS 03Nov00
	/*ave stats*/	MORALE_VERYGOOD,SKILL_VETERAN,				//MS 03Nov00
	/*airfield*/	UID_AF_AntwerpDeurne,		//UID_AF_Montdidier,	//UID_AF_Soesterberg,//MS 06Nov00
	/*available*/	32+1,25,				//3+30,30,			//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(5,J,H),
	/*geshwader*/	WN_KG_4,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_4_2,
	/*leader*/		IDS_KG_4_2_Leader,IDS_KG_4_2_Replace,
	/*lead stats*/	MORALE_EXCELLENT,SKILL_ACE,					//MS 03Nov00
	/*ave stats*/	MORALE_TOPMORALE,SKILL_VETERAN1,			//MS 03Nov00
	/*airfield*/	UID_AF_StTrond,		//UID_AF_Beauvais,	//UID_AF_Eindhoven,//MS 06Nov00
	/*available*/	3+30,25,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(5,J,M),
	/*geshwader*/	WN_KG_4,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_4_3,
	/*leader*/		IDS_KG_4_3_Leader,IDS_KG_4_3_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE1,					//MS 03Nov00
	/*ave stats*/	MORALE_EXCELLENT,SKILL_VETERAN2,			//MS 03Nov00
	/*airfield*/	UID_AF_Eindhoven,				//UID_AF_Creil,	//UID_AF_AmsterdamSchipol,
	/*available*/	3+30,24,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(5,J,R),
	/*geshwader*/	WN_KG_4,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_53_1,
	/*leader*/		IDS_KG_53_1_Leader,IDS_KG_53_1_Replace,
	/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE1,					//MS 03Nov00
	/*ave stats*/	MORALE_VERYGOOD,SKILL_ACE,					//MS 03Nov00
	/*airfield*/	UID_AF_Lille,
	/*available*/	32+1,32,				//3+19,19,			//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(A,1,H),
	/*geshwader*/	WN_KG_53,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_53_2,
	/*leader*/		IDS_KG_53_2_Leader,IDS_KG_53_2_Replace,
	/*lead stats*/	MORALE_EXCELLENT,SKILL_ACE2,				//MS 03Nov00
	/*ave stats*/	MORALE_TOPMORALE,SKILL_ACE1,				//MS 03Nov00
	/*airfield*/	UID_AF_Tramecourt,			//UID_AF_Lille,	//MS 06Nov00
	/*available*/	32+1,32,				//3+21,21,			//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(A,1,M),
	/*geshwader*/	WN_KG_53,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_53_3,
	/*leader*/		IDS_KG_53_3_Leader,IDS_KG_53_3_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_HERO,					//MS 03Nov00
	/*ave stats*/	MORALE_EXCELLENT,SKILL_ACE2,				//MS 03Nov00
	/*airfield*/	UID_AF_Barley,								//MS 06Nov00
	/*available*/	32+1,32,				//3+26,26,			//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(A,1,R),
	/*geshwader*/	WN_KG_53,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_76_1,
	/*leader*/		IDS_KG_76_1_Leader,IDS_KG_76_1_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE,						//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR,				//MS 03Nov00
	/*airfield*/	UID_AF_Beauvais,
	/*available*/	3+20,20,	//32+1,32,				//3+9,9,			//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(F,1,H),
	/*geshwader*/	WN_KG_76,
	/*gruppen*/		GN_1
//DEADCODE RDH 27/04/00 	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_76_2,
	/*leader*/		IDS_KG_76_2_Leader,IDS_KG_76_2_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE1,						//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR1,				//MS 03Nov00
	/*airfield*/	UID_AF_Creil,
	/*available*/	3+20,20,	//32+1,32,				//3+7,7,			//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(F,1,M),
	/*geshwader*/	WN_KG_76,
	/*gruppen*/		GN_2
//DEADCODE RDH 27/04/00 	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_76_3,
	/*leader*/		IDS_KG_76_3_Leader,IDS_KG_76_3_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE2,						//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR2,					//MS 03Nov00
	/*airfield*/	UID_AF_CormeillesEnVexin,
	/*available*/	3+20,20,	//32+1,32,				//3+3,3,			//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(F,1,R),
	/*geshwader*/	WN_KG_76,
	/*gruppen*/		GN_3
//DEADCODE RDH 27/04/00 	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_2_1,
	/*leader*/		IDS_JG_2_1_Leader,IDS_JG_2_1_Replace,
	/*lead stats*/	MORALE_VERYGOOD,SKILL_VETERAN2,				//MS 03Nov00
	/*ave stats*/	MORALE_TOPMORALE,SKILL_VETERAN,				//MS 03Nov00
	/*airfield*/	UID_AF_LeHarve,	//UID_AF_BeaumontLeRoger,
//TempCode MS 15Sep00 	/*available*/	3+32,32,
	/*available*/	2+37,37,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(2I,MGR1),
	/*geshwader*/	WN_JG_2,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_2_2,
	/*leader*/		IDS_JG_2_2_Leader,IDS_JG_2_2_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE,					//MS 03Nov00
	/*ave stats*/	MORALE_VERYGOOD,SKILL_VETERAN1,				//MS 03Nov00
	/*airfield*/	UID_AF_Plumetot,	//UID_AF_BeaumontLeRoger,
	/*available*/	3+36,36,		//3+33,33,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(2II,MGR2),
	/*geshwader*/	WN_JG_2,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_2_3,
	/*leader*/		IDS_JG_2_3_Leader,IDS_JG_2_3_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE1,					//MS 03Nov00
	/*ave stats*/	MORALE_VERYGOOD,SKILL_VETERAN2,				//MS 03Nov00
	/*airfield*/	UID_AF_Caen,	//UID_AF_LeHarve,
	/*available*/	3+36,36,		//3+29,29,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(2III,MGR3),
	/*geshwader*/	WN_JG_2,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_27_1,
	/*leader*/		IDS_JG_27_1_Leader,IDS_JG_27_1_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE1,					//MS 03Nov00
	/*ave stats*/	MORALE_MEDIUM,SKILL_ACE,						//MS 03Nov00
	/*airfield*/	UID_AF_StAndreDeLEure,	//UID_AF_Plumetot,
	/*available*/	3+39,39,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(27I,MGR1),
	/*geshwader*/	WN_JG_27,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_27_2,
	/*leader*/		IDS_JG_27_2_Leader,IDS_JG_27_2_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE2,						//MS 03Nov00
	/*ave stats*/	MORALE_MEDIUM,SKILL_ACE1,					//MS 03Nov00
	/*airfield*/	UID_AF_BeaumontLeRoger,	//UID_AF_Crepon,
	/*available*/	3+39,39,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(27II,MGR2),
	/*geshwader*/	WN_JG_27,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_27_3,
	/*leader*/		IDS_JG_27_3_Leader,IDS_JG_27_3_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_HERO,						//MS 03Nov00
	/*ave stats*/	MORALE_EXCELLENT,SKILL_ACE2,				//MS 03Nov00
	/*airfield*/	UID_AF_Evreaux,	//UID_AF_Carquebut,
	/*available*/	3+39,39,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(27III,MGR3),
	/*geshwader*/	WN_JG_27,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_53_1,
	/*leader*/		IDS_JG_53_1_Leader,IDS_JG_53_1_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR,					//MS 03Nov00
	/*airfield*/	UID_AF_Epinoy,	//UID_AF_Rennes,
	/*available*/	3+39,39,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(53I,MGR1),
	/*geshwader*/	WN_JG_53,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_53_2,
	/*leader*/		IDS_JG_53_2_Leader,IDS_JG_53_2_Replace,
	/*lead stats*/	MORALE_TOPMORALE,SKILL_ACE1,				//MS 03Nov00
	/*ave stats*/	MORALE_VERYGOOD,SKILL_REGULAR1,				//MS 03Nov00
	/*airfield*/	UID_AF_Cambrai,	//UID_AF_Dinan,
	/*available*/	3+36,36,		//3+30,30,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(53II,MGR2),
	/*geshwader*/	WN_JG_53,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_JG_53_3,
	/*leader*/		IDS_JG_53_3_Leader,IDS_JG_53_3_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE2,						//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR2,				//MS 03Nov00
	/*airfield*/	UID_AF_RosieresEnSanterre,	//UID_AF_Marck,	//UID_AF_Brest,				//MS 10Mar00
	/*available*/	3+39,39,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWF_MARK(53III,MGR3),
	/*geshwader*/	WN_JG_53,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_SG_1_1,
	/*leader*/		IDS_SG_1_1_Leader,IDS_SG_1_1_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_VETERAN2,					//MS 03Nov00
	/*ave stats*/	MORALE_MEDIUM,SKILL_VETERAN,				//MS 03Nov00
	/*airfield*/	UID_AF_Marck,	//UID_AF_Marck,	//UID_AF_Angers,				  //JIM 07/02/00
	/*available*/	3+36,38,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(A,5,H),
	/*geshwader*/	WN_SG_1,
	/*gruppen*/		GN_1
				},

	/*squad*/	{SQ_SG_1_2,
	/*leader*/		IDS_SG_1_2_Leader,IDS_SG_1_2_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE,						//MS 03Nov00
	/*ave stats*/	MORALE_MEDIUM,SKILL_VETERAN1,					//MS 03Nov00
	/*airfield*/	UID_AF_Cocquelles,	//UID_AF_Marck,	//UID_AF_PasdeCalais,		//MS 10Mar00
	/*available*/	3+36,38,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(A,5,M),
	/*geshwader*/	WN_SG_1,
	/*gruppen*/		GN_2
				},

	/*squad*/	{SQ_SG_1_3,
	/*leader*/		IDS_SG_1_3_Leader,IDS_SG_1_3_Replace,
	/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE1,					//MS 03Nov00
	/*ave stats*/	MORALE_TOPMORALE,SKILL_VETERAN2,			//MS 03Nov00
	/*airfield*/	UID_AF_Peuplingues,	//UID_AF_Colombert,	//UID_AF_Angers,			  //JIM 07/02/00
	/*available*/	38,38,
	/*repairs*/	 	2,2,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(A,5,R),
	/*geshwader*/	WN_SG_1,
	/*gruppen*/		GN_3
				},

	/*squad*/	{SQ_SG_2_1,
	/*leader*/		IDS_SG_2_1_Leader,IDS_SG_2_1_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE1,					//MS 03Nov00
	/*ave stats*/	MORALE_MEDIUM,SKILL_ACE,						//MS 03Nov00
	/*airfield*/	UID_AF_Arras,	//UID_AF_StMalo,
	/*available*/	3+36,38,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(S,2,H),
	/*geshwader*/	WN_SG_2,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_SG_2_2,
	/*leader*/		IDS_SG_2_2_Leader,IDS_SG_2_2_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE2,						//MS 03Nov00
	/*ave stats*/	MORALE_MEDIUM,SKILL_ACE1,					//MS 03Nov00
	/*airfield*/	UID_AF_Barley,	//UID_AF_Lannion,
	/*available*/	3+39,39,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(S,2,M),
	/*geshwader*/	WN_SG_2,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_SG_2_3,
	/*leader*/		IDS_SG_2_3_Leader,IDS_SG_2_3_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_HERO,						//MS 03Nov00
	/*ave stats*/	MORALE_EXCELLENT,SKILL_ACE2,				//MS 03Nov00
	/*airfield*/	UID_AF_Lille,	//UID_AF_Caen,
	/*available*/	3+39,39,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(S,2,R),
	/*geshwader*/	WN_SG_2,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_SG_77_1,
	/*leader*/		IDS_SG_77_1_Leader,IDS_SG_77_1_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR,					//MS 03Nov00
	/*airfield*/	UID_AF_Carquebut,	//UID_AF_Caen,
	/*available*/	3+39,39,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(F,1,H),
	/*geshwader*/	WN_SG_77,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_SG_77_2,
	/*leader*/		IDS_SG_77_2_Leader,IDS_SG_77_2_Replace,
	/*lead stats*/	MORALE_TOPMORALE,SKILL_ACE1,				//MS 03Nov00
	/*ave stats*/	MORALE_VERYGOOD,SKILL_REGULAR1,				//MS 03Nov00
	/*airfield*/	UID_AF_Crepon,	//UID_AF_Caen,
	/*available*/	3+39,39,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(F,1,M),
	/*geshwader*/	WN_SG_77,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_SG_77_3,
	/*leader*/		IDS_SG_77_3_Leader,IDS_SG_77_3_Replace,
	/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE2,					//MS 03Nov00
	/*ave stats*/	MORALE_EXCELLENT,SKILL_REGULAR2,			//MS 03Nov00
	/*airfield*/	UID_AF_StMalo,	//UID_AF_Caen,
	/*available*/	3+38,38,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(F,1,R),
	/*geshwader*/	WN_SG_77,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_ZG_2_1,
	/*leader*/		IDS_ZG_2_1_Leader,IDS_ZG_2_1_Replace,
	/*lead stats*/	MORALE_TOPMORALE,SKILL_VETERAN2,			//MS 03Nov00
	/*ave stats*/	MORALE_MEDIUM,SKILL_VETERAN,				//MS 03Nov00
	/*airfield*/	UID_AF_Guyancourt,	//UID_AF_Amiens,
	/*available*/	3+36,36,		//3+33,33,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
//TempCode MS 31Jul00 	/*markings*/	Squadron::NO_FLYING,LWB_MARK(BZ2I,MGR1),
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(2,S,H),
	/*geshwader*/	WN_ZG_2,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_ZG_2_2,
	/*leader*/		IDS_ZG_2_2_Leader,IDS_ZG_2_2_Replace,
	/*lead stats*/	MORALE_EXCELLENT,SKILL_ACE,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_VETERAN1,					//MS 03Nov00
	/*airfield*/	UID_AF_MelunVillaroche,	//UID_AF_Guyancourt,
	/*available*/	3+36,36,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
//TempCode MS 31Jul00 	/*markings*/	Squadron::NO_FLYING,LWB_MARK(BZ2II,MGR2),
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(2,S,M),
	/*geshwader*/	WN_ZG_2,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_ZG_2_3,
	/*leader*/		IDS_ZG_2_3_Leader,IDS_ZG_2_3_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE1,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_VETERAN2,					//MS 03Nov00
	/*airfield*/	UID_AF_Etampes,	//UID_AF_Guyancourt,
	/*available*/	3+36,36,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
//TempCode MS 31Jul00 	/*markings*/	Squadron::NO_FLYING,LWB_MARK(BZ2III,MGR3),
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(2,S,R),
	/*geshwader*/	WN_ZG_2,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_27_1,
	/*leader*/		IDS_KG_27_1_Leader,IDS_KG_27_1_Replace,
	/*lead stats*/	MORALE_TOPMORALE,SKILL_ACE1,				//MS 03Nov00
	/*ave stats*/	MORALE_VERYGOOD,SKILL_ACE,					//MS 03Nov00
	/*airfield*/	UID_AF_Dinan,		//UID_AF_Chateaudun,	//UID_AF_Tours,				  //JIM 07/02/00//MS 06Nov00
	/*available*/	3+36,36,		//3+30,30,					//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(1,G,H),
	/*geshwader*/	WN_KG_27,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_27_2,
	/*leader*/		IDS_KG_27_2_Leader,IDS_KG_27_2_Replace,
	/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE2,					//MS 03Nov00
	/*ave stats*/	MORALE_EXCELLENT,SKILL_ACE1,				//MS 03Nov00
	/*airfield*/	UID_AF_Dinard,
	/*available*/	3+34,34,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(1,G,M),
	/*geshwader*/	WN_KG_27,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_27_3,
	/*leader*/		IDS_KG_27_3_Leader,IDS_KG_27_3_Replace,
	/*lead stats*/	MORALE_TOPMORALE,SKILL_HERO,				//MS 03Nov00
	/*ave stats*/	MORALE_MEDIUM,SKILL_ACE2,					//MS 03Nov00
	/*airfield*/	UID_AF_StMalo,		//UID_AF_Rennes,		//MS 06Nov00
	/*available*/	32+1,32,				//3+25,25,			//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(1,G,R),
	/*geshwader*/	WN_KG_27,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_51_1,
	/*leader*/		IDS_KG_51_1_Leader,IDS_KG_51_1_Replace,
	/*lead stats*/	MORALE_EXCELLENT,SKILL_ACE,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR,				//MS 03Nov00
	/*airfield*/	UID_AF_StOmer,		//UID_AF_MelunVillaroche,//MS 06Nov00
//TempCode MS 08Sep00 	/*available*/	3+25,25,
	/*available*/	3+33,33,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(9,K,H),
	/*geshwader*/	WN_KG_51,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_51_2,
	/*leader*/		IDS_KG_51_2_Leader,IDS_KG_51_2_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE1,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR1,				//MS 03Nov00
	/*airfield*/	UID_AF_Samer,		//UID_AF_Orly,			//MS 06Nov00
//TempCode MS 08Sep00 	/*available*/	3+25,25,
	/*available*/	3+33,33,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(9,K,M),
	/*geshwader*/	WN_KG_51,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_51_3,
	/*leader*/		IDS_KG_51_3_Leader,IDS_KG_51_3_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_ACE2,						//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR2,					//MS 03Nov00
	/*airfield*/	UID_AF_Desvres,		//UID_AF_Etampes,		//MS 06Nov00
	/*available*/	32+1,32,				//3+27,27,			//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(9,K,R),
	/*geshwader*/	WN_KG_51,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_54_1,
	/*leader*/		IDS_KG_54_1_Leader,IDS_KG_54_1_Replace,
	/*lead stats*/	MORALE_GOOD,SKILL_VETERAN2,					//MS 03Nov00
	/*ave stats*/	MORALE_VERYGOOD,SKILL_VETERAN,				//MS 03Nov00
	/*airfield*/	UID_AF_Guines,			//UID_AF_Evreaux,	//MS 06Nov00
//TempCode MS 08Sep00 	/*available*/	3+29,29,
	/*available*/	4+29,30,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(B,3,H),
	/*geshwader*/	WN_KG_54,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_54_2,
	/*leader*/		IDS_KG_54_2_Leader,IDS_KG_54_2_Replace,
	/*lead stats*/	MORALE_VERYGOOD,SKILL_ACE,					//MS 03Nov00
	/*ave stats*/	MORALE_EXCELLENT,SKILL_VETERAN1,			//MS 03Nov00
	/*airfield*/	UID_AF_Hermelinghen,			//UID_AF_StAndreDeLEure,//MS 06Nov00
	/*available*/	32+1,32,				//3+24,24,			//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(B,3,M),
	/*geshwader*/	WN_KG_54,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_54_3,
	/*leader*/		IDS_KG_54_3_Leader,IDS_KG_54_3_Replace,
	/*lead stats*/	MORALE_TOPMORALE,SKILL_ACE1,				//MS 03Nov00
	/*ave stats*/	MORALE_MEDIUM,SKILL_VETERAN2,				//MS 03Nov00
	/*airfield*/	UID_AF_Caffiers,		//UID_AF_StAndreDeLEure,//MS 06Nov00
	/*available*/	32+1,32,				//10,4,				//MS 06Nov00
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(B,3,R),
	/*geshwader*/	WN_KG_54,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_55_1,
	/*leader*/		IDS_KG_55_1_Leader,IDS_KG_55_1_Replace,
	/*lead stats*/	MORALE_EXCELLENT,SKILL_ACE1,				//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_ACE,						//MS 03Nov00
	/*airfield*/	UID_AF_Dreux,
	/*available*/	3+32,32,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(G,1,H),
	/*geshwader*/	WN_KG_55,
	/*gruppen*/		GN_1,Gruppen::BUSY_IN_EUROPE
				},

	/*squad*/	{SQ_KG_55_2,
	/*leader*/		IDS_KG_55_2_Leader,IDS_KG_55_2_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_ACE2,					//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_ACE1,						//MS 03Nov00
	/*airfield*/	UID_AF_Chartres,
	/*available*/	3+32,32,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(G,1,M),
	/*geshwader*/	WN_KG_55,
	/*gruppen*/		GN_2,Gruppen::BUSY_IN_EUROPE

				},

	/*squad*/	{SQ_KG_55_3,
	/*leader*/		IDS_KG_55_3_Leader,IDS_KG_55_3_Replace,
	/*lead stats*/	MORALE_MEDIUM,SKILL_VETERAN,				//MS 03Nov00
	/*ave stats*/	MORALE_GOOD,SKILL_REGULAR1,					//MS 03Nov00
	/*airfield*/	UID_AF_Villacoublay,
	/*available*/	3+30,24,
	/*repairs*/	 	0,0,
	/*lost,tote*/	0,Profile::PS_AT_30,
	/*markings*/	Squadron::NO_FLYING,LWB_MARK(G,1,R),
	/*geshwader*/	WN_KG_55,
	/*gruppen*/		GN_3,Gruppen::BUSY_IN_EUROPE
				},
	{SQ_ZERO}
};
Geshwader				NodeData::germwaderinst[]=
{	
	//in GroupGeschwader I assume that the different types will stay grouped. //RDH 10/12/99
	//and in same order	
	//J,S,Z,K
	{WN_JG,3,	LF_2,PT_ME109,	D_0July+10},	//real 10th
	{WN_JG,26,	LF_2,PT_ME109,	D_0July+              24},					//
	{WN_JG,51,	LF_2,PT_ME109,	D_0July+   13},								//
	{WN_JG,52,	LF_2,PT_ME109,	D_0July+        18},						//
	{WN_JG,54,	LF_2,PT_ME109,	D_0July+            22},					//
	{WN_ZG,26,	LF_2,PT_ME110,	D_0July+10},								//U8
	{WN_ZG,76,	LF_2,PT_ME110,	D_0July+      16},							//M8
	{WN_KG,1,	LF_2,PT_HE111,	D_0July+    14},							//V1
	{WN_KG,2,	LF_2,PT_DO17,	D_0July+  12},								//U5
	{WN_KG,3,	LF_2,PT_DO17,	D_0July+         19},						//5K
	{WN_KG,4,	LF_2,PT_HE111,	D_0July+           21},						//5J
	{WN_KG,53,	LF_2,PT_HE111,	D_0July+               25},					//A1
	{WN_KG,76,	LF_2,PT_DO17,	D_0July+10,true},							//F1


	{WN_JG,2,	LF_3,PT_ME109,	D_0July+                    30},			//
	{WN_JG,27,	LF_3,PT_ME109,	D_0July+                26},				//
	{WN_JG,53,	LF_3,PT_ME109,	D_0July+                  28},				//
	{WN_SG,1,	LF_3,PT_JU87,	D_0July+10},								//A5 (J9)
	{WN_SG,2,	LF_3,PT_JU87,	D_0July+ 11},								//S2 (T6)
	{WN_SG,77,	LF_3,PT_JU87,	D_0July+     15},							//F1
	{WN_ZG,2,	LF_3,PT_ME110,	D_0July+          20},						//2S
	{WN_KG,27,	LF_3,PT_HE111,	D_0July+		           29},				//1G
	{WN_KG,51,	LF_3,PT_JU88,	D_0July+       17},							//9K
	{WN_KG,54,	LF_3,PT_JU88,	D_0July+			     27},				//B3
	{WN_KG,55,	LF_3,PT_HE111,	D_0July+                     31},			//G1
	{WN_JG,0}
};
ProductionAC	NodeData::production[PT_BADMAX]=
{
//DeadCode MS 02Nov00 	/*spitA*/		{SQ_ZERO,25,25,	93,HR06},
//DeadCode MS 02Nov00 	/*PT_SPIT_B,*/	{SQ_ZERO,0,0,},
//DeadCode MS 02Nov00 	/*PT_HURR_A,*/	{SQ_ZERO,25,25,	123,HR06+MIN10},
//DeadCode MS 02Nov00 	/*PT_HURR_B,*/	{SQ_ZERO,0,0,},
//DeadCode MS 02Nov00 	/*PT_DEFIANT*/	{SQ_ZERO},
//DeadCode MS 02Nov00 	/*PT_BLEN,*/	{SQ_ZERO},
//DeadCode MS 02Nov00 	/*PT_ME109*/	{SQ_ZERO,23,23,	190,HR06+MIN20},
//DeadCode MS 02Nov00 	/*PT_ME110,*/	{SQ_ZERO,35,35,	170,HR06+MIN30},
//DeadCode MS 02Nov00 	/*PT_JU87,*/	{SQ_ZERO},
//DeadCode MS 02Nov00 	/*PT_DO17*/		{SQ_ZERO,15,15,	250,HR06+MIN40},
//DeadCode MS 02Nov00 	/*PT_JU88*/		{SQ_ZERO,35,35,	150,HR06+MIN50},
//DeadCode MS 02Nov00 	/*PT_HE111,*/	{SQ_ZERO,20,20,	200,HR07},
//DeadCode MS 02Nov00 	/*PT_HE59,*/	{SQ_ZERO}

//35 for spit and 62 for Hurricane
//Rate is based on 15 hr days and 7 day weeks= 107*60 = 6400 mins. LW figures are not recalculated
	/*spitA*/		{SQ_ZERO,33,35,	193,HR06},
	/*PT_SPIT_B,*/	{SQ_ZERO,0,0,},
	/*PT_HURR_A,*/	{SQ_ZERO,62,62,	103,HR06},
	/*PT_HURR_B,*/	{SQ_ZERO,0,0,},
	/*PT_DEFIANT*/	{SQ_ZERO},
	/*PT_BLEN,*/	{SQ_ZERO},
	/*PT_ME109*/	{SQ_ZERO,23,23,	278,HR06},
	/*PT_ME110,*/	{SQ_ZERO,35,35,	182,HR06},
	/*PT_JU87,*/	{SQ_ZERO},
	/*PT_DO17*/		{SQ_ZERO,15,15,	360,HR06},	//this also has reconn at 3* delay
	/*PT_JU88*/		{SQ_ZERO,35,35,	179,HR06},
	/*PT_HE111,*/	{SQ_ZERO,20,20,	317,HR06},
	/*PT_HE59,*/	{SQ_ZERO}
};
typedef	   HistoricInfo	HI;
HistoricInfo	NodeData::historicinfo=
{{				  
	{HI::OVERCAST,HI::OVERCAST,HI::CLOUD60}, 			//July 10th
	{HI::NOFLY,HI::CLOUD60,HI::CLOUD60}, 			//July 11th
//	{HI::OVERCAST,HI::CLOUD60,HI::CLOUD60}, 			//July 11th
	{HI::CLOUD60,HI::CLOUD60,HI::CLOUD60}, 			//July 12th
	{HI::NOFLY,HI::OVERCAST,HI::CLOUD60}, 			//July 13th
	{HI::CLEAR,HI::CLEAR,HI::CLEAR}, 				//July 14th
	{HI::OVERCAST,HI::CLOUD60,HI::OVERCAST}, 			//July 15th
	{HI::NOFLY,HI::OVERCAST,HI::OVERCAST}, 			//July 16th
	{HI::NOFLY,HI::OVERCAST,HI::NOFLY}, 			//July 17th
	{HI::NOFLY,HI::OVERCAST,HI::NOFLY}, 			//July 18th
	{HI::CLOUD60,HI::CLOUD30,HI::CLEAR}, 			//July 19th
	{HI::CLOUD30,HI::CLEAR,HI::CLEAR}, 				//July 20th
	{HI::CLOUD30,HI::CLOUD60,HI::NOFLY}, 			//July 21st
	{HI::CLEAR,HI::CLOUD30,HI::CLEAR}, 				//July 22nd
	{HI::CLOUD60,HI::CLOUD30,HI::CLOUD60}, 			//July 23rd
	{HI::CLEAR,HI::CLOUD30,HI::CLOUD60}, 			//July 24th
	{HI::CLEAR,HI::CLEAR,HI::CLOUD30}, 				//July 25th
	{HI::OVERCAST,HI::NOFLY,HI::NOFLY}, 			//July 26th
	{HI::OVERCAST,HI::NOFLY,HI::NOFLY}, 			//July 27th
	{HI::CLOUD30,HI::CLEAR,HI::CLEAR}, 				//July 28th
	{HI::OVERCAST,HI::CLOUD30,HI::CLEAR}, 			//July 29th		
	{HI::NOFLY,HI::NOFLY,HI::OVERCAST}, 			//July 30th
	{HI::OVERCAST,HI::NOFLY,HI::OVERCAST}, 			//July 31st
	{HI::OVERCAST,HI::CLOUD30,HI::CLEAR}, 			//August 1st 
	{HI::OVERCAST,HI::CLOUD60,HI::CLOUD30}, 			//August 2nd
	{HI::CLOUD30,HI::CLOUD60,HI::CLEAR}, 			//August 3rd
	{HI::CLEAR,HI::CLEAR,HI::CLOUD30}, 				//August 4th
	{HI::CLEAR,HI::CLEAR,HI::CLEAR}, 				//August 5th
	{HI::CLOUD30,HI::CLOUD30,HI::CLEAR},			//August 6th
	{HI::CLEAR,HI::CLOUD30,HI::CLOUD60},			//August 7th
	{HI::CLOUD60,HI::CLOUD30,HI::CLOUD60},			//August 8th
	{HI::OVERCAST,HI::CLOUD60,HI::CLOUD30},			//August 9th
	{HI::NOFLY,HI::NOFLY,HI::OVERCAST},				//August 10th
	{HI::CLEAR,HI::CLOUD30,HI::CLOUD60},			//August 11th
	{HI::CLEAR,HI::CLOUD30,HI::CLOUD30},			//August 12th
	{HI::OVERCAST,HI::NOFLY,HI::NOFLY},				//AUG 13
	{HI::NOFLY,HI::CLOUD30,HI::CLOUD60}, 			//AUG 14
	{HI::NOFLY,HI::CLEAR,HI::CLEAR}, 				//AUG 15
	{HI::CLEAR,HI::CLOUD30,HI::CLOUD30},			//August 16th
	{HI::CLEAR,HI::CLEAR,HI::CLEAR},				//August 17th
	{HI::CLEAR,HI::CLOUD30,HI::CLOUD60},			//August 18th
	{HI::OVERCAST,HI::NOFLY,HI::NOFLY},				//August 19th
	{HI::OVERCAST,HI::CLOUD60,HI::OVERCAST},			//August 20th
	{HI::NOFLY,HI::OVERCAST,HI::CLOUD60},			//August 21st
	{HI::OVERCAST,HI::CLOUD60,HI::OVERCAST},			//August 22nd
	{HI::CLOUD30,HI::CLEAR,HI::CLEAR},				//August 23rd
	{HI::CLEAR,HI::CLOUD30,HI::CLEAR},				//August 24th
	{HI::CLEAR,HI::CLOUD30,HI::CLOUD60},			//August 25th
	{HI::OVERCAST,HI::CLOUD60,HI::CLOUD60},			//August 26th
	{HI::OVERCAST,HI::NOFLY,HI::NOFLY},				//August 27th
	{HI::CLOUD60,HI::CLOUD30,HI::CLEAR},			//August 28th
	{HI::OVERCAST,HI::CLEAR,HI::NOFLY},				//August 29th
	{HI::CLEAR,HI::CLOUD30,HI::CLEAR},				//August 30th
	{HI::CLEAR,HI::OVERCAST,HI::CLOUD60},			//August 31st
	{HI::CLEAR,HI::CLEAR,HI::CLEAR}, 				//September 1st
	{HI::CLEAR,HI::CLOUD30,HI::CLEAR}, 				//September 2nd
	{HI::CLOUD30,HI::CLEAR,HI::CLOUD30}, 			//September 3rd
	{HI::CLEAR,HI::CLOUD30,HI::CLOUD30}, 			//September 4th
	{HI::CLOUD30,HI::CLOUD30,HI::CLOUD30}, 			//September 5th
	{HI::CLEAR,HI::CLEAR,HI::CLEAR},				//September 6th
	{HI::CLOUD30,HI::CLEAR,HI::CLEAR}, 		    		//September 7th
	{HI::CLEAR,HI::CLOUD30,HI::CLOUD60}, 			//September 8th
	{HI::NOFLY,HI::NOFLY,HI::OVERCAST}, 			//September 9th
	{HI::OVERCAST,HI::NOFLY,HI::OVERCAST}, 			//September 10th
	{HI::CLOUD60,HI::CLOUD30,HI::CLEAR}, 			//September 11th
	{HI::OVERCAST,HI::OVERCAST,HI::OVERCAST}, 			//September 12th
	{HI::OVERCAST,HI::NOFLY,HI::OVERCAST}, 			//September 13th
	{HI::NOFLY,HI::OVERCAST,HI::NOFLY}, 			//September 14th
	{HI::CLEAR,HI::CLEAR,HI::CLEAR}, 				//September 15th



}};


//////////////////////////////////////////////////////////////////////
//
// Function:    NodeData Functions
// Date:		18/11/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
NodeData	Node_Data;

CON		NodeData::NodeData()
{
	for (int i=0;i<SUBTABLESIZE;i++)
		TargetPointers[i]=NULL;
}

void	NodeData::ClearTargetTable()
{
	for (int i=0;i<SUBTABLESIZE;i++)
		delete[] TargetPointers[i];
	for (i=0;i<SUBTABLESIZE;i++)
		TargetPointers[i]=NULL;
}
DES		NodeData::~NodeData()
{

	ClearTargetTable();
}

Target&	NodeData::GetTarget(UniqueID index)
{
	int indexhi=index/SUBTABLESIZE;
	int	indexlo=index%SUBTABLESIZE;
	TargetPtr*	subtable=TargetPointers[indexhi];
	if (subtable==NULL)
		return	*(Target*)NULL;
	else
		return	subtable[indexlo][0];
}

void	NodeData::AddToTargetTable(Target* t,int tss)
{
	int	index=t->uid;
	t->truedefenses=Target::Defenses(t->truedefenses|tss);
	int indexhi=index/SUBTABLESIZE;
	int	indexlo=index%SUBTABLESIZE;
	TargetPtr*	subtable=TargetPointers[indexhi];
	if (subtable==NULL)
	{
		subtable=new TargetPtr[SUBTABLESIZE];
		for (int i=0;i<SUBTABLESIZE;i++)
			subtable[i]=NULL;
		TargetPointers[indexhi]=subtable;
	}
	subtable[indexlo]=t;
}

void	NodeData::BuildTargetTable()
{
	ClearTargetTable();
	{for (II_TargetNoDetail* t=nodetails;t->Base().uid;t=t->Next())			AddToTargetTable(*t,TSS_SetTargetNoDetail		);}
	{for (II_TargetGroup* t=groups;			t->Base().uid;t=t->Next())		AddToTargetTable(*t,TSS_SetTargetGroup			);}
	{for (II_TargetSateliteField* t=satelites;t->Base().uid;t=t->Next())	AddToTargetTable(*t,TSS_SetTargetSateliteField	);}
	{for (II_TargetSectorField* t=sectors;	t->Base().uid;t=t->Next())		AddToTargetTable(*t,TSS_SetTargetSectorField	);}
	{for (II_TargetRadar* t=radars;			t->Base().uid;t=t->Next())		AddToTargetTable(*t,TSS_SetTargetRadar			);}
	{for (II_TargetGroup* t=notfacts;		t->Base().uid;t=t->Next())		AddToTargetTable(*t,TSS_SetTargetGroup			);}
	{for (II_TargetFakeFactory* t=fakefacts;t->Base().uid;t=t->Next())		AddToTargetTable(*t,TSS_SetTargetFakeFactory	);}
	{for (II_TargetFactory* t=factories;	t->Base().uid;t=t->Next())		AddToTargetTable(*t,TSS_SetTargetFactory		);}
	{for (II_TargetConvoy* t=convoys;		t->Base().uid;t=t->Next())		{AddToTargetTable(*t,TSS_SetTargetConvoy);t->wpnum=-1;}}
	squadron=*britsquadinst;										  //RDH 08/12/99
	gruppe=*germsquadinst;											  //RDH 08/12/99
	geschwader=germwaderinst;										  //RDH 08/12/99
	convoylist=*convoys;
	sectorlist=*sectors;
	factorylist=*factories;
	fakelist=*fakefacts;
	radarlist=*radars;

}


void	TargetGroup::FixInitialStatusLW()
{
	if (falsetargtype==TT_AS_KNOWN)
		falsetargtype=truetargtype;
	else
		knownstatus=TS_FLAG_UNKNOWN;
	if (falsepriority==TP_AS_KNOWN)
		falsepriority=truepriority;
	else
		knownstatus=TS_FLAG_UNKNOWN;

}
//DeadCode JIM 3Jul00 void	TargetGroup::FixInitialStatusRAF()
//DeadCode JIM 3Jul00 {
//DeadCode JIM 3Jul00 	falsetargtype=truetargtype;
//DeadCode JIM 3Jul00 	knownstatus=truestatus;
//DeadCode JIM 3Jul00 	falsepriority=truepriority;
//DeadCode JIM 3Jul00 }
void	TargetGroup::SetDamage(UByte newlevel,bool reduceifnegative,UniqueID reportsuccess)
{	
	//Kill this group
//DEADCODE JON 16/05/00 	Node_Data.CheckTargetLoaded(uid);
	Dead_Stream.FakeDamage(uid,newlevel,reduceifnegative);
	//Set displayed statuses
	if (IsA(TSS_TargetAirfield))
	{
		int a,b,c,d;
		int maindamage=Node_Data.GetCheckDamage(Dead_Stream,uid,a,b,c,d);
		TargetFighterFieldPtr(*this)->ApplyDamage(newlevel,a,b,c,d,reportsuccess);
	}
	else
		ApplyDamage(newlevel,reportsuccess);
	
}

void	NodeData::SkipToDate(int targetdate)
{
	int targetdaynum=targetdate/SECSPERDAY-D_FIRSTDAMAGEDDATE;
	if (targetdaynum<0) targetdaynum=0;
	if (Persons2::pItemSet())
		for (int uidval=UID_NULL;uidval<IllegalSepID;uidval++)
		{
			TargetGroup* g=operator[](UniqueID(uidval));
			if (g && !g->IsA(TargetGroup::TSS_TargetConvoy))
			{
				int le;
				for (le=1;le<TargetGroup::MAXDATES && g->keydates[le];le++)
					breakif((g->keydates[le]&DL_DATEMASK)>=targetdaynum);
				le-=1;
				if (le || (g->keydates[0] && (g->keydates[0]&DL_DATEMASK)<targetdaynum))

				{
					le=(g->keydates[le]>>DL_LEVELSH)*35;
					g->SetDamage(le,true,UID_NULL);
					g->knownstatus=g->truestatus;
					g->falsepriority=g->truepriority;
				}
			}
		}

}


TargetSateliteField*	TargetFighterField::nextsatelite()
{
	if (satelitelist)
		return Node_Data[satelitelist];
	else
		return NULL;
}

TargetSectorField*	TargetFighterField::getsectoraf()
{
	if (truedefenses&TSS_TargetSateliteField)
		return Node_Data[TargetSateliteFieldPtr(*this)->sectorAF];
	else
		return (*this);
}
UniqueID	 TargetFighterField::getsectoruid()
{
	if (truedefenses&TSS_TargetSateliteField)
		return TargetSateliteFieldPtr(*this)->sectorAF;
	else
		return uid;
}
void	NodeData::Load(BIStream&bis)
{
	{for (II_TargetSateliteField* t=satelites;	t->Base().uid;t=t->Next())	bis.Transfer(t);}
	{for (II_TargetSectorField*	t=sectors;		t->Base().uid;t=t->Next())	bis.Transfer(t);}
	{for (II_TargetNoDetail*	t=nodetails;	t->Base().uid;t=t->Next())	bis.Transfer(t);}
	{for (II_TargetGroup*		t=groups;		t->Base().uid;t=t->Next())	bis.Transfer(t);}
	{for (II_TargetRadar*		t=radars;		t->Base().uid;t=t->Next())	bis.Transfer(t);}
	{for (II_TargetGroup*		t=notfacts;		t->Base().uid;t=t->Next())	bis.Transfer(t);}
	{for (II_TargetFakeFactory* t=fakefacts;	t->Base().uid;t=t->Next())	bis.Transfer(t);}
	{for (II_TargetFactory*		t=factories;	t->Base().uid;t=t->Next())	bis.Transfer(t);}
	{for (II_TargetConvoy*		t=convoys;		t->Base().uid;t=t->Next())	bis.Transfer(t);}

	{for (II_BritSquadron*	t=britsquadinst;	t->Base().squadron;t=t->Next())	bis.Transfer(t);}
	{for (II_Gruppen*		t=germsquadinst;	t->Base().squadron;t=t->Next())	bis.Transfer(t);}

	{for (Geshwader*	t=germwaderinst;		t->wadernum;t+=1)				bis.Transfer(t);}
	bis.read((char*)&intel,sizeof(IntelBuffer));
	bis.read((char*)&review,sizeof(ReviewBuffer));

	{for (int i=0;i<PT_HE59;i++)
	{
		production[i].recipient=SQ_ZERO;
		production[i].nextaceta=0;
	}}
}
void	NodeData::Save(BOStream&bos)
{
	{for (II_TargetSateliteField* t=satelites;	t->Base().uid;t=t->Next())		bos.Transfer(t);}
	{for (II_TargetSectorField*	t=sectors;		t->Base().uid;t=t->Next())		bos.Transfer(t);}
	{for (II_TargetNoDetail*	t=nodetails;	t->Base().uid;t=t->Next())		bos.Transfer(t);}
	{for (II_TargetGroup*		t=groups;		t->Base().uid;t=t->Next())		bos.Transfer(t);}
	{for (II_TargetRadar*		t=radars;		t->Base().uid;t=t->Next())		bos.Transfer(t);}
	{for (II_TargetGroup*		t=notfacts;		t->Base().uid;t=t->Next())		bos.Transfer(t);}
	{for (II_TargetFakeFactory* t=fakefacts;	t->Base().uid;t=t->Next())		bos.Transfer(t);}
	{for (II_TargetFactory*		t=factories;	t->Base().uid;t=t->Next())		bos.Transfer(t);}
	{for (II_TargetConvoy*		t=convoys;		t->Base().uid;t=t->Next())		bos.Transfer(t);}

	{for (II_BritSquadron*	t=britsquadinst;	t->Base().squadron;t=t->Next())	bos.Transfer(t);}
	{for (II_Gruppen*		t=germsquadinst;	t->Base().squadron;t=t->Next())	bos.Transfer(t);}

	{for (Geshwader*	t=germwaderinst;		t->wadernum;t+=1)				bos.Transfer(t);}
	bos.write((char*)&intel,sizeof(IntelBuffer));
	bos.write((char*)&review,sizeof(ReviewBuffer));
}

Squadron&	NodeData::operator [](SquadNum sq)
{
	if (sq<SQ_BR_START)
	{
		switch(sq)
		{
		case	SQ_QMSPITA:	return	Node_Data.squadron[SQ_BR_54-SQ_BR_START-1];
		case	SQ_QMSPITB:	return	Node_Data.squadron[SQ_BR_65-SQ_BR_START-1];		
		case	SQ_QMHURRA:	return	Node_Data.squadron[SQ_BR_501-SQ_BR_START-1];
		case	SQ_QMHURRB:	return	Node_Data.squadron[SQ_BR_151-SQ_BR_START-1];
		case	SQ_QMDEF:	return	Node_Data.squadron[SQ_BR_DEFIENT-SQ_BR_START-1];
		case	SQ_QMBLEN:	return	Node_Data.squadron[SQ_BR_BLENHEIM-SQ_BR_START-1];
		case	SQ_QM109:	return	Node_Data.gruppe[SQ_JG_3_1-SQ_LW_START-1];	
		case	SQ_QM110:	return	Node_Data.gruppe[SQ_ZG_26_1-SQ_LW_START-1];
		case	SQ_QM87:	return	Node_Data.gruppe[SQ_SG_1_1-SQ_LW_START-1];	
//DEADCODE AMM 03/03/00 		case	SQ_QM17:	return	Node_Data.gruppe[SQ_KG_3_1-SQ_LW_START-1];
		case	SQ_QM17:	return	Node_Data.gruppe[SQ_KG_2_1-SQ_LW_START-1];
		case	SQ_QM88:	return	Node_Data.gruppe[SQ_KG_51_1-SQ_LW_START-1];
//DEADCODE AMM 03/03/00 		case	SQ_QM111:	return	Node_Data.gruppe[SQ_KG_55_1-SQ_LW_START-1];
		case	SQ_QM111:	return	Node_Data.gruppe[SQ_KG_4_1-SQ_LW_START-1];
		case	SQ_QM59:	return	Node_Data.gruppe[SQ_KG_55_1-SQ_LW_START-1];
		}
	}
	assert(sq<SQ_MAX);
	if (sq>SQ_LW_START)
		return	gruppe[sq-SQ_LW_START-1];				  //RDH 08/12/99
	else
		return	squadron[sq-SQ_BR_START-1];				  //RDH 08/12/99

}
//DEADCODE DAW 18/02/00 Target&	NodeData::operator [](UniqueID uid)
//DEADCODE DAW 18/02/00 {
//DEADCODE DAW 18/02/00 	return GetTarget(uid);
//DEADCODE DAW 18/02/00 }


#define	SUBCALL(routine)	assert(this)	\
	if (squadron>=SQ_LW_START)				 \
		return GruppenPtr(this)->routine;		\
	else									   \
		return BritSquadronPtr(this)->routine;

PlaneTypeSelect	Squadron::AcType()
{
	SUBCALL(AcType())
}
inline	CString	LoadResString(int resnum)
{
	CString s;
	s.LoadString(resnum);
	return s;
};

CString Squadron::CallName()
{
	if (squadron<SQ_LW_START)
		return LoadResString(IDS_PHRASE_CALLEE_GRAF+squadron-SQ_BR_START);
	else
		return LoadResString(IDS_PHRASE_CALLEE_GLW+squadron-SQ_LW_START);	//RDH 23/03/00
}

CString Squadron::SubName()
{
	SUBCALL(SubName())
}

CString Squadron::ShortName()
{
	SUBCALL(ShortName())
}

CString Squadron::FullName()
{
	SUBCALL(FullName())
}
bool Squadron::Busy()
{
	SUBCALL(Busy())
}


PlaneTypeSelect	BritSquadron::AcType()
{
	return PlaneTypeSelect(actype);
}

PlaneTypeSelect	Gruppen::AcType()
{
	return PlaneTypeSelect(Node_Data.geschwader[wadernum].aircrafttype); //RDH 08/12/99
}

#define	RESSTRING(name)	LoadResString(IDS_##name)
#define	RESLIST(name,val)	LoadResString(IDS_L_##name+val)

CString BritSquadron::ShortName()
{
	return SubName();
//DEADCODE RDH 08/12/99 	return ("");
}

CString Gruppen::ShortName()
{
	CString string;
	string.Format("%i", Node_Data.geschwader[wadernum].wadernum);

//DEADCODE RDH 06/01/00 	return	(	RESLIST(JAGD,Node_Data.geschwader[wadernum].wadername)
	return	(	RESLIST(J,Node_Data.geschwader[wadernum].wadername)
//DEADCODE RDH 06/01/00 			+	" "
			+	string
			);
//DEADCODE RDH 08/12/99 	return ("");
	
}

CString BritSquadron::FullName()
{
	return SubName()+" "+RESSTRING(SQUADRON);
//DEADCODE RDH 08/12/99 	return ("");

}

CString Gruppen::FullName()
{
	CString string;
	string.Format("%i", Node_Data.geschwader[wadernum].wadernum);


	return	RESLIST(JAGDGESCH,Node_Data.geschwader[wadernum].wadername)
		+	" "
			+	string
		+	" "
		+	SubName();
//DEADCODE RDH 08/12/99 	return ("");
//DEADCODE RDH 08/12/99 //	return RESSTRING(WADERT_JageG,
}

CString BritSquadron::SubName()
{
	return RESLIST(SQUADNUMBERS,squadron-SQ_BR_START);
}

CString Gruppen::SubName()
{
	return RESLIST(GI,gruppennum);

//DEADCODE RDH 20/12/99 	switch(gruppennum)
//DEADCODE RDH 20/12/99 	{
//DEADCODE RDH 20/12/99 	default:
//DEADCODE RDH 20/12/99 	case 1:	return RESSTRING(GRUPPEI);
//DEADCODE RDH 20/12/99 	case 2:	return RESSTRING(GRUPPEII);
//DEADCODE RDH 20/12/99 	case 3:	return RESSTRING(GRUPPEIII);
//DEADCODE RDH 20/12/99 	}
}
UByte	Squadron::Category()	   //Cat A = 0!
{
	//Rules: 
	//					Cat A requires:			Cat B requires
	//		Morale>=		MORALE_GOOD			
	//		Skill>=			SKILL_REGULAR1
	//		acavail>=		12
	//		pilotsavail>=	16

	if (totestatus==Profile::PS_AIRFIELDOUT)							//JIM 15Aug00
		return 2;															//JIM 15Aug00
		

	float cat;
	cat = (MORALE_GOOD-averagemorale)/50.0;
	if (cat<0)
		cat=cat*0.3;
	if (leaderskill+averageskill-2*SKILL_VETERAN<0)
		cat-=(leaderskill+averageskill-2*SKILL_VETERAN)/200.0;
	else
		cat-=(leaderskill+averageskill-2*SKILL_VETERAN)/100.0;
	if (acavail<12)
		cat+=0.1*(12-acavail);
	if (pilotsavail<16)
		cat+=0.1*(16-pilotsavail);
	cat+=0.5;
	if (cat>=2.0)
		return 2;
	if (cat<1.0)
		return 0;
	return(1);
}

int		NodeData::EstimateProduction(Target::TargType testtargtype)
{
	int	rv=0;
	{for (TargetFakeFactory* f=fakelist;f->uid;f++)
	{
		if (f->falsetargtype==testtargtype)
			if (f->knownstatus<TS_LIGHTDAMAGE)
				rv+=f->currperweek;
	}}
	{for (TargetFactory* f=factorylist;f->uid;f++)
	{
		if (f->falsetargtype==testtargtype)
			if (f->knownstatus<TS_LIGHTDAMAGE)
				rv+=f->maxperweek;
	}}
	return rv;


}
int		NodeData::EstimateProduction(PlaneTypeSelect  testtype)
{
	if (testtype>PT_RAF_NONFLY)
		return production[testtype].acperweek;
	else
	{
		int	spitparts=		EstimateProduction(Target::TT_SPITPARTS),
			spitassembly=	EstimateProduction(Target::TT_SPITASSEMBLY),
			hurrparts=		EstimateProduction(Target::TT_HURRPARTS),//MS 01Nov00
			hurrassembly=	EstimateProduction(Target::TT_HURRASSEMBLY),//MS 01Nov00
			unknownprod=	EstimateProduction(Target::TT_UNKNOWNAIRCRAFT),
			ammoprod=		EstimateProduction(Target::TT_ARMAMENTS) + 20,	//CSB 12Jul00
			totalassembly;

		if (spitassembly>spitparts)
			spitassembly=spitparts;
		if (hurrassembly>hurrparts)
			hurrassembly=hurrparts;

		totalassembly=spitassembly+hurrassembly;
		if (totalassembly>ammoprod)
		{
			spitassembly=spitassembly*ammoprod/totalassembly;
			hurrassembly=hurrassembly*ammoprod/totalassembly;
		}
		spitassembly+=unknownprod/3;
		hurrassembly+=unknownprod/3;
		if (testtype==PT_SPIT_A)
			return	spitassembly;
		else
			return	hurrassembly;

	}

}
int		NodeData::CountProduction(Target::TargType testtargtype)
{
	int	rv=0;
	for (TargetFactory* f=factorylist;f->uid;f++)
	{
		if (f->truetargtype==testtargtype)
			rv+=f->currperweek;
	}
	return rv;
}

void	NodeData::GenerateProductionRates()
{
	int	spitparts=		CountProduction(Target::TT_SPITPARTS),
		spitassembly=	CountProduction(Target::TT_SPITASSEMBLY),
		hurrparts=		CountProduction(Target::TT_HURRPARTS),	//MS 01Nov00
		hurrassembly=	CountProduction(Target::TT_HURRASSEMBLY),	//MS 01Nov00
//DeadCode MS 02Nov00 		ammoprod=		CountProduction(Target::TT_ARMAMENTS) + 20,
		ammoprod=		CountProduction(Target::TT_ARMAMENTS) + 75,//MS 02Nov00
		totalassembly;
	if (spitassembly>spitparts)
		spitassembly=spitparts;
	if (hurrassembly>hurrparts)
		hurrassembly=hurrparts;
	totalassembly=spitassembly+hurrassembly;
	if (totalassembly>ammoprod)
	{
		spitassembly=spitassembly*ammoprod/totalassembly;
		hurrassembly=hurrassembly*ammoprod/totalassembly;
	}
	if ((production[PT_SPIT_A].acperweek/10)>(spitassembly/10))
		intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_ACPRODUCTIONHAMPERED,UID_NULL,UID_NULL,TargetIndexes(PT_SPIT_A,spitassembly));
	if ((production[PT_HURR_A].acperweek/10)>(hurrassembly/10))
		intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_ACPRODUCTIONHAMPERED,UID_NULL,UID_NULL,TargetIndexes(PT_HURR_A,hurrassembly));
	
	production[PT_SPIT_A].acperweek=spitassembly;
	production[PT_HURR_A].acperweek=hurrassembly;
	const int	minsperweek=60*15*7;
	spitassembly=minsperweek/spitassembly;
	hurrassembly=minsperweek/hurrassembly;						//MS 01Nov00
	production[PT_SPIT_A].minsperac=spitassembly;
	production[PT_HURR_A].minsperac=hurrassembly;
}
static int	pilotsrequired[]=
{	//0	1	2	3	4	5	6	7	8	9
	0,	2,	4,	6,	7,	9,	10,	12,	13,	15,		//0-9	aircraft
	16,	17,	18,	19,	20,	21,	22,	22,	23,	24,		//10-19 aircraft
	24,	25,	26,	27,	28,	29,	30,	31,	32,	33,		//20-29 aircraft
	34,	35,	36,	37,	38,	38,	39,	40,	40,	41,		//30-39 aircraft
	41,	42,	43,	44,	44,	45						//40-44 aircraft
};
void	NodeData::IncreasePilotsIfRequired(Squadron* sq)
{
	int	req=pilotsrequired[sq->acavail+sq->acquickrepairable];
	req-=sq->pilotsavail;
	if (req>0)
	{
		if (req>2)	//can't add more than 2 pilots to 1 squad in 4 hr period 
			req=2;
		while (req--)		//ok.. send some pilots
		{
			int	newpilotskill=MMC.newpilotskill;
			int group=0;
			if (sq->squadron>SQ_LW_START)
				newpilotskill=SKILL_REGULAR;
			if (sq->squadron<SQ_LW_START)
				group=TargetFighterFieldPtr(operator[](sq->homeairfield))->getsectoraf()->groupname;
			if (group==IDS_GROUP_13)
			{	//If recipient at Newcastle, then pilot is poorer but doesn't effect quality of next pilot
				newpilotskill-=SKILL_GAINNEWPILOTSPERDAY;
				if (newpilotskill<SKILL_NOVICE)
					newpilotskill=SKILL_NOVICE;
			}
			else
			{	//If recipient is elsewhere, then current best trainee is sent and quality reduces.
				//LW may need a lower rate of degradation. At present all come here. 
				if (newpilotskill>=SKILL_NOVICE1)
					MMC.newpilotskill=SkillType(newpilotskill-SKILL_LOSSPERNEWPILOT);
			}
//CHECK THIS													//MS 01Nov00
			if (sq->pilotsavail)
				newpilotskill+=(sq->pilotsavail-1)*sq->averageskill+sq->leaderskill;
			sq->pilotsavail+=1;
			if (sq->pilotsavail)
				sq->averageskill=newpilotskill/sq->pilotsavail;
		}
	}

}
void	NodeData::DeliverProductionRates(int	secondspassed)
{
	for (int i=PT_BRIT_FLYABLE;i<PT_VEHICLES;i++)
		if (production[i].acperweek)
			while (production[i].nextaceta<MMC.currtime)
			{
				bool	change=true;
				if (production[i].recipient)
				{
					MMC.thisweekreview.Note(PlaneTypeSelect(i),PeriodReview::CREATE,1);
					Squadron* sq=operator[](production[i].recipient);
					sq->acavail++;
					change=(sq->acavail>=production[i].required);
					if (sq->squadron<SQ_LW_START)
						change|=(sq->ACTotal()>=BritSquadron::MAX_AC);
					else
						change|=(sq->ACTotal()>=Gruppen::MAX_AC);
					IncreasePilotsIfRequired(sq);
					if (!change && sq->squadron>SQ_LW_START &&	geschwader[GruppenPtr(*sq)->wadernum].reconn)
						production[i].nextaceta+=production[i].minsperac*180;	//3 times as long as normal for reconn
					else
					if (MMC.currtime-production[i].nextaceta<5*production[i].minsperac*60)
						if (production[i].scrappedaircraft)
						{
							production[i].nextaceta+=production[i].minsperac*45;	//production speedup
							production[i].scrappedaircraft--;
						}
						else
							production[i].nextaceta+=production[i].minsperac*60;
					else
						production[i].nextaceta=MMC.currtime-1;
				}
				else	//didn't use last aircraft made. Try again in a short while...
					production[i].nextaceta=MMC.currtime+production[i].minsperac*(60/4);
				if (change)
				{
					AutoReassignProduction(PlaneTypeSelect(i));
					Squadron* sq=operator[](production[i].recipient);
					if (sq->squadron>SQ_LW_START &&	geschwader[GruppenPtr(*sq)->wadernum].reconn)
						production[i].nextaceta+=production[i].minsperac*120;

				}
			}
}

void	NodeData::AutoReassignProduction(PlaneTypeSelect planetype,bool force13)
{
	bool	dosay=false;
	int	reqstr=0;
	SquadNum	newsq=WhereToReassignProduction(planetype,force13,dosay,reqstr);
	if (dosay)
	{	
		Squadron* sq;
		SquadNum	oldsq=production[planetype].recipient;
		if (oldsq && oldsq!=newsq)
		{
			sq=operator[](oldsq);
			if (oldsq>SQ_LW_START)
				intel.AddMessage(IntelMsg::MED_MANAGEMENT_LW,AS_NOTSWITCH,SCRIPT_LWACPRODUCTIONFULFILLED ,sq->homeairfield,sq->homeairfield,TargetIndexes(oldsq,sq->ACTotal()));
			else
				intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_ACPRODUCTIONFULFILLED ,sq->homeairfield,sq->homeairfield,TargetIndexes(oldsq,sq->ACTotal()));

		}
		if (newsq)
		{
			sq=operator[](newsq);
			if (newsq>SQ_LW_START)
				intel.AddMessage(IntelMsg::MED_MANAGEMENT_LW,AS_NOTSWITCH,SCRIPT_LWACPRODUCTION ,sq->homeairfield,sq->homeairfield,TargetIndexes(newsq,sq->ACTotal()));
			else
				intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_ACPRODUCTION ,sq->homeairfield,sq->homeairfield,TargetIndexes(newsq,sq->ACTotal()));
		}
	}
	production[planetype].recipient=newsq;
	production[planetype].required=reqstr;
}

SquadNum	NodeData::WhereToReassignProduction(PlaneTypeSelect planetype,bool force13,bool&dosay,int&reqstr)
{
	SquadNum	newsq=SQ_ZERO;
	if (planetype<PT_GER_FLYABLE)
	{
		//Find squadron in sector 11
		int pt2=planetype+1;
		int	bestsqweights[4]={100,100,100,100};
		int	totalacforsq[4];
		int	bestsqs[4]={-1,-1,-1,-1};

		for (int sq=0;squadron[sq].squadron;sq++)
		{
			BritSquadron& squad=squadron[sq];
			if (squad.AcType()==planetype || squad.AcType()==pt2)
			{
				int group=TargetFighterFieldPtr(operator[](squad.homeairfield))->getsectoraf()->groupname;
				group-=IDS_GROUP_10;
				if (group<0 || group>3)
					group=3;
				if (squad.acavail<bestsqweights[group] && squad.ACTotal()<BritSquadron::MAX_AC)
					{
						bestsqweights[group]=squad.acavail;
						bestsqs[group]=sq;
						totalacforsq[group]=squad.ACTotal();
					}
			}
		}
		int grouptoup=0;
		if (force13)
			grouptoup=IDS_GROUP_13;
		else
		{
			int band11=bestsqweights[1]/4;
			int	band1012=bestsqweights[0]/4;
			if (bestsqweights[0]>bestsqweights[2])
				band1012=bestsqweights[2]/4;
			if (band11>2 && band11>band1012)
				if (band1012>16)
				{
					grouptoup=IDS_GROUP_13;
					force13=true;
				}
				else
				if (bestsqweights[0]>bestsqweights[2])
					grouptoup=IDS_GROUP_12;
				else
					grouptoup=IDS_GROUP_10;
			else
				grouptoup=IDS_GROUP_11;
		}
		if (bestsqweights[grouptoup-IDS_GROUP_10]<BritSquadron::MAX_AC)
		{
			newsq=squadron[bestsqs[grouptoup-IDS_GROUP_10]].squadron; 
			reqstr=(bestsqweights[grouptoup-IDS_GROUP_10]&~3)+4;
			if (reqstr<12)
				reqstr=12;
			if (totalacforsq[grouptoup-IDS_GROUP_10]-bestsqweights[grouptoup-IDS_GROUP_10]+reqstr>BritSquadron::MAX_AC)
				reqstr=BritSquadron::MAX_AC-(totalacforsq[grouptoup-IDS_GROUP_10]-bestsqweights[grouptoup-IDS_GROUP_10]);
			if (newsq!=production[planetype].recipient)
			{
				if (!production[planetype].recipient)
					dosay=true;
				else
				{
					Squadron* sq=operator[](production[planetype].recipient);
					int group=TargetFighterFieldPtr(operator[](sq->homeairfield))->getsectoraf()->groupname;
					if (group<IDS_GROUP_10||group>IDS_GROUP_13)
						group=IDS_GROUP_13;
					if (group==IDS_GROUP_11 || grouptoup!=group)
						dosay=true;
				}
			}
		}
		else
		{
			if (production[planetype].recipient)
				dosay=true;
		}
	}
	else
	{	//Rewrite of selection logic: Mark doesn't want weakest squads rebuilt, but strongest!
		int	datefromstart=(MMC.currdate-MMC.startdate)/SECSPERDAY;
		int	bestsqweight=-1000,bestsq=-1;
		int reqstr0=10;
		if (planetype<=PT_ME110)
			reqstr0=12;
		for (int i=0;gruppe[i].squadron;i++)
		{
			Geshwader&	gw=geschwader[gruppe[i].wadernum];
			if (	gruppe[i].periodsuntilready != Gruppen::BUSY_IN_EUROPE 
				&&	planetype==gw.aircrafttype
				)
			{
				int	reqstr3=3*reqstr0;
				if (gw.reconn)
					reqstr3=6;
				int	shortfall=reqstr3-gruppe[i].ACTotal();
//DeadCode JIM 6Nov00 				if (gw.reconn)
//DeadCode JIM 6Nov00 					shortfall*=5;
				if (shortfall>0)
					if (gw.reconn)
						shortfall=1000-4*shortfall;	//The 4* is to allow a tuning for reconn
					else
						shortfall=1000-6*shortfall;	//The 4* is to allow a tuning for reconn
				else
					if (gw.reconn)
						shortfall*=8;
				if (shortfall>bestsqweight)
				{
					bestsqweight=shortfall;
					bestsq=i;
				}
			}
		}
		Geshwader&	gw=geschwader[gruppe[bestsq].wadernum];
		if (bestsq!=-1)
		{
			newsq=gruppe[bestsq].squadron;
			if (gw.reconn)	//DeliverProductionRates assumes that we will only make single reconn aircraft
				reqstr=gruppe[bestsq].acavail+1; 
			else
			if (gruppe[bestsq].acavail<12)	
				reqstr=12;				//1 flight
			else
			if (gruppe[bestsq].acavail<24)	
				reqstr=24;				//2 flights
			else
			if (gruppe[bestsq].acavail<27 && planetype>=PT_JU87)	
				reqstr=27;				//3 flights of 10
			else
			if (gruppe[bestsq].acavail<30 && planetype>=PT_JU87)	
				reqstr=30;				//3 flights of 10
			else
			if (gruppe[bestsq].acavail<36)	//3 flights of 12
				reqstr=36;
			else
			if (gruppe[bestsq].acavail<40)	//4 flights of 10
				reqstr=40;
			else
				reqstr=44;				//spares!
			if (gruppe[bestsq].ACTotal()-gruppe[bestsq].acavail+reqstr>Gruppen::MAX_AC)
				reqstr=Gruppen::MAX_AC-(gruppe[bestsq].ACTotal()-gruppe[bestsq].acavail);
		}
		dosay=(newsq!=production[bestsq].recipient);
	}
	return	newsq;
}
void	BritSquadron::UpdateReadiness(ULong periodsperframe)
{
	if (totetimer)
		if (totetimer<=periodsperframe)
		{
			switch 	(totestatus)
			{
			case	Profile::PS_ORDER_30:
				Node_Data.intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_AT30MINS  ,homeairfield,UID_NULL,TargetIndexes(squadron,ACTotal()));
				totestatus=Profile::PS_AT_30;
			break;
			case	Profile::PS_ORDER_5:
				Node_Data.intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_ATREADINESS   ,homeairfield,UID_NULL,TargetIndexes(squadron,ACTotal()));
				totestatus=Profile::PS_AT_5;
			break;
			case	Profile::PS_ORDER_2:
				Node_Data.intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_ATSTANDBY   ,homeairfield,UID_NULL,TargetIndexes(squadron,ACTotal()));
				totestatus=Profile::PS_AT_2;
			break;
			}
			totetimer=0;
		}
		else
			totetimer-=periodsperframe;

}
void	NodeData::UpdateReadiness(int secsperframe)
{
	secsperframe/=SECSPERSAGFRAME;
	for (int sq=0;squadron[sq].squadron;sq++)
		squadron[sq].UpdateReadiness(secsperframe);
}

void	NodeData::UpgradeAircraftTypes()
{
	int	datefromstart=(MMC.currdate-MMC.startdate)/SECSPERDAY;
	//enable LW forces over time
	limitscope
	{
		int stukashortfalltotal=0,stukasquadsshort=0,stukasquadsavail=0;
		int	removestukagrupp=-1,removestukagruppstr=Gruppen::MIN_GRUPPEAC;
		for (int i=0;gruppe[i].squadron;i++)
		{
			if (gruppe[i].periodsuntilready==Gruppen::BUSY_IN_EUROPE && geschwader[gruppe[i].wadernum].startdate<=datefromstart)
			{
				gruppe[i].periodsuntilready=0;
				//SEND MESSAGE THAT SQUADRON HAS ARRIVED IF GRUPPENNUM==1 
				if (gruppe[i].gruppennum==1 && geschwader[gruppe[i].wadernum].startdate==datefromstart)
				{
					intel.AddMessage(IntelMsg::MED_MANAGEMENT_LW,AS_NOTSWITCH,SCRIPT_LWOPERATIONAL ,gruppe[i].homeairfield,UID_NULL,TargetIndexes(gruppe[i].squadron,gruppe[i].ACTotal()));
					MMC.thisweekreview.Note(gruppe[i].AcType(),PeriodReview::CREATE,gruppe[i].acavail);
				}
				else
				{
					MMC.thisweekreview.Note(gruppe[i].AcType(),PeriodReview::AVAILSTART,gruppe[i].acavail);

				}

			}
			else
				if (gruppe[i].AcType()==PT_JU87 && gruppe[i].ACTotal())
				{
					if (gruppe[i].ACTotal()<Gruppen::MIN_GRUPPEAC)
					{
						stukasquadsshort++;
						stukashortfalltotal+=Gruppen::MIN_GRUPPEAC-gruppe[i].ACTotal();
						if (gruppe[i].acavail<removestukagruppstr)
						{
							removestukagrupp=i;
							removestukagruppstr=gruppe[i].acavail;
						}
					}
					else
						stukasquadsavail++;
				}
		}
		if (stukashortfalltotal>=Gruppen::MIN_GRUPPEAC || stukasquadsshort>stukasquadsavail)
		{	//compound the stukas if enough inactive squads or a/c to bother...
			for (int i=0;gruppe[i].squadron;i++)

				if (i!=removestukagrupp && gruppe[i].AcType()==PT_JU87 && gruppe[i].ACTotal())
				{	
					typedef UByte Gruppen::*Field;
					struct Shortfall
					{
						Gruppen	*src,*trg;
						int fall;
						void	Transfer(Field field)
						{
							int	delta=fall;
							if (src->*field<delta)
								delta=src->*field;
							trg->*field+=delta;
							fall-=delta;
							src->*field-=delta;
							if (src->pilotsavail<delta)
								delta=src->pilotsavail;
							src->pilotsavail-=delta;
							trg->pilotsavail+=delta;
						}
					}	Short;
					Short.trg=&gruppe[i];
					Short.src=&gruppe[removestukagrupp];
					Short.fall=Gruppen::MIN_GRUPPEAC-gruppe[i].ACTotal();
					Short.Transfer(&Gruppen::acavail);
					Short.Transfer(&Gruppen::acquickrepairable);
					Short.Transfer(&Gruppen::acslowrepairable);
				}
		}
	}


	//upgrade spitfires and hurricanes
	if (datefromstart>=D_W2)
	{
		PlaneTypeSelect fromtype=PT_SPIT_A,totype=PT_SPIT_B; 
		if (datefromstart&1)
			fromtype=PT_HURR_A,totype=PT_HURR_B; 
		int	lowestac=100,lowestacind=-1;
		for (int i=0;squadron[i].squadron;i++)
		{
			if (squadron[i].actype==fromtype)
				if (squadron[i].acavail<lowestac)
				{
					lowestac=squadron[i].acavail;
					lowestacind=i;
				}
		}
		if (lowestacind!=-1)
		{
			squadron[i].actype=totype;
			//SEND MESSAGE TO SAY SQUADRON UPGRADED
		}
	}


}
//DEADCODE DAW 16/02/00 Various factors improve skill and morale during play:
//DEADCODE DAW 16/02/00 Losing leader:
//DEADCODE DAW 16/02/00 	Ave morale goes down 1 value
//DEADCODE DAW 16/02/00 	On losing first leader, second leader is used, with his skill as listed.
//DEADCODE DAW 16/02/00 	On losing second leader, further leaders are generated with false name and mid-skill between outgoing leader and squad.
//DEADCODE DAW 16/02/00 Improving skill:
//DEADCODE DAW 16/02/00 If squad is in G13 or G12N, skill increases at 5% of diff between leader and squad per day, and morale increases by 0.5 levels per day.
//DEADCODE DAW 16/02/00 If squad is in active location but rested whole day, morale increases by 0.5 levels, skill unchanged.
//DEADCODE DAW 16/02/00 If squad doesn't fly for a period (3 per day) morale increases by minimum point.
//DEADCODE DAW 16/02/00 If squad flys and suffers no losses or kills, morale increases by 2*minimum, ave skill increases by 3% of diff between leader and squad.
//DEADCODE DAW 16/02/00 If leader gets kills, his skill increases by 0.5 levels
//DEADCODE DAW 16/02/00 If squad gets kills, ave skill improves by 2% of diff between leader and squad per kill.
//DEADCODE DAW 16/02/00 If squad gets losses> 0.5 of kills ave morale down 0.3 of value
//DEADCODE DAW 16/02/00 If squad write-off ave morale down 2*minimum
//DEADCODE DAW 16/02/00 Temporarily decreasing skill:
//DEADCODE DAW 16/02/00 Each consecutive period of flying (3 per day) decreases skill and morale by 2*minimum
//DEADCODE DAW 16/02/00 1 period of non-flying clears this effect.
//DEADCODE DAW 16/02/00 3d effect:
//DEADCODE DAW 16/02/00 	Skill of leader is directly translated to lead aircraft.
//DEADCODE DAW 16/02/00 	Remaining aircraft get aveskill+ rnd((leadskill-aveskill)/3)

void	Squadron::ModifyMoraleAcCombat(PeriodStatus periodstatus,int times)
{
	for (int i=times;i>0;i--)
		switch (periodstatus)
		{
		case LEAD_KILLED:
		{
			if (averagemorale>MORALE_STAGE)
				averagemorale-=MORALE_STAGE;
			else
				averagemorale=MORALE_ROCKBOTTOM;
	//DeadCode JIM 1Nov00 		if (replaceleadername)
	//DeadCode JIM 1Nov00 		{
			leadername=replaceleadername;
	//DeadCode JIM 1Nov00 			replaceleadername=0;
	//DeadCode JIM 1Nov00 		}
	//DeadCode JIM 1Nov00 		else
	//DeadCode JIM 1Nov00 		{
			if (squadron>=SQ_LW_START)
				replaceleadername=IDS_JG_3_1_Leader+Math_Lib.rnd(24*3*2);	//150
			else
				replaceleadername=IDS_32Leader+Math_Lib.rnd(50*2);
	//DeadCode JIM 1Nov00 		}
			leaderskill=(leaderskill*2+averageskill)/3;
		}
		break;
		case LEAD_GOTKILL:	//This should be set in 3d on per-kill basis
		{
			if (leaderskill<=SKILL_HERO2-SKILL_SUBSTAGE/2)
				leaderskill+=SKILL_SUBSTAGE/2;
		}
		break;
		case OTHER_GOTKILL:	//This should be set in 3d on per-kill basis
		{
			if (averageskill<SKILL_HERO1 && averageskill<leaderskill)
			{
				int skilldelta=0.7+leaderskill*0.05+averageskill*0.95;
				if (skilldelta==0)
					skilldelta=1;
				averageskill+=skilldelta;
			}
		}
		break;
		case GOT_LOSSES:	//This should be set in 3d on per-kill basis
		{	//should be 0.1 stake per loss
			if (averagemorale>MORALE_STAGE)
				averagemorale-=MORALE_STAGE/10;
		}
		break;
		default:	INT3;

		}
}


void	Squadron::ModifyMoraleNonCombat()
{	//Note that this is written such that only 1 event can occur.
	//However, some of these are prototypes for combat where all skills can change.
	switch (periodstatus)
	{
	case LEAD_KILLED:	INT3;
//DeadCode JIM 1Nov00 	{
//DeadCode JIM 1Nov00 		if (averagemorale>MORALE_STAGE)
//DeadCode JIM 1Nov00 			averagemorale-=MORALE_STAGE;
//DeadCode JIM 1Nov00 		else
//DeadCode JIM 1Nov00 			averagemorale=MORALE_ROCKBOTTOM;
//DeadCode JIM 1Nov00 		if (replaceleadername)
//DeadCode JIM 1Nov00 		{
//DeadCode JIM 1Nov00 			leadername=replaceleadername;
//DeadCode JIM 1Nov00 			replaceleadername=0;
//DeadCode JIM 1Nov00 		}
//DeadCode JIM 1Nov00 		else
//DeadCode JIM 1Nov00 		{
//DeadCode JIM 1Nov00 			if (squadron>=SQ_LW_START)
//DeadCode JIM 1Nov00 				leadername=IDS_JG_3_1_Leader+Math_Lib.rnd(24*3*2);	//150
//DeadCode JIM 1Nov00 			else
//DeadCode JIM 1Nov00 				leadername=IDS_32Leader+Math_Lib.rnd(50*2);
//DeadCode JIM 1Nov00 		}
//DeadCode JIM 1Nov00 		leaderskill=(leaderskill*2+averageskill)/3;
//DeadCode JIM 1Nov00 	}
	break;

	case LEAD_GOTKILL:	INT3;//This should be set in 3d on per-kill basis
//DeadCode JIM 1Nov00 	{
//DeadCode JIM 1Nov00 		if (leaderskill<SKILL_HERO1)
//DeadCode JIM 1Nov00 			leaderskill+=SKILL_SUBSTAGE/2;
//DeadCode JIM 1Nov00 	}
	break;
	case OTHER_GOTKILL:	INT3;//This should be set in 3d on per-kill basis
//DeadCode JIM 1Nov00 	{
//DeadCode JIM 1Nov00 		if (averageskill<SKILL_HERO1 && averageskill<leaderskill)
//DeadCode JIM 1Nov00 			averageskill+=(leaderskill+averageskill*15)/16;
//DeadCode JIM 1Nov00 	}
	break;
	case GOT_LOSSES:	INT3;//This should be set in 3d on per-kill basis
//DeadCode JIM 1Nov00 	{	//should be 0.1 stake per loss
//DeadCode JIM 1Nov00 		if (averagemorale>MORALE_STAGE)
//DeadCode JIM 1Nov00 			averagemorale-=MORALE_STAGE/3;
//DeadCode JIM 1Nov00 	}
	break;

	case GOT_ACTION:
	{	//skills will have modified during game
		if (averageskill<SKILL_HERO1 && averageskill<leaderskill)
			averageskill+=SKILL_SUBSTAGE/5;
		if (leaderskill<SKILL_HERO)
			leaderskill+=SKILL_SUBSTAGE/5;
	}
	break;
	case NO_ACTION:
	{
		averageskill=(leaderskill+averageskill*29)/30+1;
	}
	break;
	case NO_FLYING:
	{
		if (averagemorale<MORALE_EXCELLENT)
			averagemorale+=MORALE_STAGE/10;
	}
	break;
	case ON_LEAVE:
	case BAD_WEATHER:
	{
		if (averagemorale<MORALE_EXCELLENT)
			averagemorale+=MORALE_STAGE/5;
	}
	break;
	case GRP_13:
	{
		if (averagemorale<MORALE_EXCELLENT)
			averagemorale+=MORALE_STAGE/3;
		averageskill=(leaderskill+averageskill*4)/5;
	}
	break;
	}	//end of switch;

	if (homeairfield==UID_AF_NEWCASTLE)
		periodstatus=GRP_13;
	else
		if (totestatus==Profile::PS_OFFBASE)
			periodstatus=ON_LEAVE;
		else
		{
			periodstatus=NO_FLYING;
		}

}
//////////////////////////////////////////////////////////////////////
//
// Function:    NextDay: EndOfDay and StartOfDay
// Date:		16/02/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	NodeData::EndOfDay()
{
	Dead_Stream.ReviveWorld(3);///*CSB*/2);
	Node_Data.CheckDamage(Dead_Stream);
	for (int i=PT_BRIT_FLYABLE;i<PT_VEHICLES;i++)
		if (production[i].acperweek)
		{
			production[i].nextaceta= production[i].nextaceta-MMC.dusktime+MMC.dawntime;
		}
	if (MMC.newpilotskill<SKILL_REGULAR)
		MMC.newpilotskill=SkillType(MMC.newpilotskill+SKILL_GAINNEWPILOTSPERDAY);


	GoToEndDayReview();													//RDH 16Aug00
	MMC.currdate+=SECSPERDAY;
	MMC.currtime=	MORNINGPERIODSTART;						//RDH 06/04/00
	FourHourPeriod(true);

	DirectivesLogic();
	Todays_Packages.WipeAll();
	GoToEndDayRouting();												//RDH 22Aug00
	//Want to go to fullpane at this point. Then, on way back, do StartOfDay call.

//DEADCODE RDH 14/03/00 	StartOfDay();
}


//////////////////////////////////////////////////////////////////////
//
// Function:    DirectivesLogic()

// Date:		24/05/00
// Author:		RDH
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	NodeData::DirectivesLogic()
{
	if (Todays_Packages.localplayer == NAT_RAF)							//RDH 12Oct00
		Directives::LW::AI();
	if (Todays_Packages.localplayer != NAT_RAF)							//RDH 12Oct00
		Directives::RAF::AI();
	UndefendedConvoyChecks();
	UndefendedCriticalTargetChecks();
}


void	NodeData::UndefendedCriticalTargetChecks()
{
#ifndef BOB_DEMO_VER
	bool ctdamagedandunprotected = false;
	int pack=0;
	while (pack < Profile::MAX_PACKS)
	{
	 	Profile& pk = Todays_Packages.pack[pack];
		if  (pk.packagestatus!=Profile::PS_SPARE && pk.attackmethod >= Profile::AM_LWPACKS)	//MS 11Jul00
		{
			UniqueID uid = pk.packagetarget[0].currentid;
			ItemBasePtr p = Persons2::ConvertPtrUID(uid);
			int uidband;
			if (((itemptr)p)->SGT != UID_Null)
				uidband=Persons2::getbandfromUID(((itemptr)p)->SGT);	
			else	
				uidband=Persons2::getbandfromUID(uid);

			if 	(		(uidband == DocksBAND)
					||	(uidband == IndustryBAND)
				)
			{
					TargetNoDetail* trg = Node_Data[pk.packagetarget[0].currentid];
					if (trg->truestatus > Target::TS_LIGHTDAMAGE)
					{
						bool anyloss=false;
						for (int i=0,m=pk.squadlist;i<m;i++)
							if (pk[i].numacditched+pk[i].numacrecoveredlow)
								anyloss=true;
						if (!anyloss)
							ctdamagedandunprotected = true;
					}

			}


		}
		pack++;
	}

	if (ctdamagedandunprotected)	
		MMC.undefendedcriticaltargetlosses++;
	else
		MMC.undefendedcriticaltargetlosses-=2;
	
	if (MMC.undefendedcriticaltargetlosses < 0)
		MMC.undefendedcriticaltargetlosses /= 2;
#endif
}

void	NodeData::UndefendedConvoyChecks()
{
#ifndef BOB_DEMO_VER
	bool convoydamagedandunprotected = false;
	int pack=0;
	while (pack < Profile::MAX_PACKS)
	{
	 	Profile& pk = Todays_Packages.pack[pack];
		if  (pk.packagestatus!=Profile::PS_SPARE && pk.attackmethod >= Profile::AM_LWPACKS)	//MS 11Jul00
		{
			UniqueID uid = pk.packagetarget[0].currentid;
			TargetPtr trg=&operator[](uid);

//DeadCode JIM 24Oct00 			ItemBasePtr p = Persons2::ConvertPtrUID(uid);
//DeadCode JIM 24Oct00 			int uidband;
//DeadCode JIM 24Oct00 			if (((itemptr)p)->SGT != UID_Null)
//DeadCode JIM 24Oct00 				uidband=Persons2::getbandfromUID(((itemptr)p)->SGT);	
//DeadCode JIM 24Oct00 			else	
//DeadCode JIM 24Oct00 				uidband=Persons2::getbandfromUID(uid);

			if 	(		trg->IsA(trg->TSS_TargetConvoy)	|| trg->London() 
					|| trg->truetargtype==trg->TT_DOCKS	||trg->truetargtype==trg->TT_NAVALBASE)
			{
				if (trg->truestatus > Target::TS_NEARPERFECT)
				{
					bool anyloss=false;
					for (int i=0,m=pk.squadlist;i<m;i++)
						if (pk[i].numacditched+pk[i].numacrecoveredlow)
							anyloss=true;
					if (!anyloss)
						convoydamagedandunprotected = true;
				}
			}


		}
		pack++;
	}

	if (convoydamagedandunprotected)	
		MMC.undefendedconvoylosses+=1;
	else
		MMC.undefendedconvoylosses-=2;	//defend one day and get 2 days grace
	
	if (MMC.undefendedconvoylosses < 0)
		MMC.undefendedconvoylosses /= 2;
#endif
}

static PlaneTypeSelect	G_13[]={PT_SPIT_A,PT_SPIT_A,PT_HURR_A,PT_HURR_A,PT_VEHICLES};
//////////////////////////////////////////////////////////////////////
//
// Function:    StartOfDay
// Date:		29/02/00
// Author:		JIM
//
//Description: This is a good place to fix any 'stuck' squadrons
//
//////////////////////////////////////////////////////////////////////
void	NodeData::StartOfDay()
{
#ifndef BOB_DEMO_VER
	MMC.currperiodtime = MORNINGPERIODSTART;
	{for (int i=0;squadron[i].squadron;i++)
	{
		TargetFighterField* tf=Node_Data[squadron[i].homeairfield];	
		if (tf->truestatus>=Target::TS_NEARLYDESTROYED || tf->subdamagelevels[TargetFighterField::SDL_RUNWAY]>=Target::TS_NEARLYDESTROYED)
		{
			if (squadron[i].totestatus!=Profile::PS_OFFBASE)
			{
				squadron[i].totestatus=Profile::PS_AIRFIELDOUT;
				squadron[i].usedacbits=0xfff;
		}	}
		else
		{
			if (squadron[i].totestatus==Profile::PS_AIRFIELDOUT)
			{
				squadron[i].totestatus=Profile::PS_AT_30;				//JIM 26/06/01
			}		//airfield repaired but squadron locked bug fix		//JIM 26/06/01
			squadron[i].usedacbits=0;									//JIM 26/06/01
		}
	}}
	AircraftRepairs4Hour();
	MMC.thisweekreview.ClearToday();

	MMC.Sky.SetMissionConditions();										//JON 28Jul00

	bool	dosay;int reqstr;
	//extra overnight aircraft to group 13
	for (int i=0;G_13[i]!=PT_VEHICLES;i++)
	{
		SquadNum	newsq=WhereToReassignProduction(G_13[i],true,dosay,reqstr);
		if (newsq)
		{
			Squadron* sq=operator[](newsq);
			sq->acavail++;
			IncreasePilotsIfRequired(sq);
		}
	}
 	Squad_Diary.CreateDailyRaidGroup(MMC.currdate);			//RJS 09Feb00
	UpgradeAircraftTypes();
	AssignSecondaryRadars();
	
	if (BadWeatherCheck())
	{
//DEADCODE RDH 31/05/00 		SetRAFReadiness(Profile::PS_SPARE);
		SetRAFPeriodStatus(Squadron::BAD_WEATHER);
		int period;
		while ((period=Node_Data.PerformMoveCycle())==0)
			MMC.accumulator=SECSPERSAGFRAME;
		Node_Data.PerformNextPeriod(period);

	}else
	{
		if (GotBadWeatherPeriod())
			SetRAFPeriodStatus(Squadron::BAD_WEATHER);
		else
		{
			LWDirectivesResults::LaunchDirectiveMissions();
		}
	}
//DEADCODE RDH 06/04/00 	UpgradeAircraftTypes();
}
void NodeData::SetRAFPeriodStatus(Squadron::PeriodStatus ps)
{
	int i = 0;
	while (		(Node_Data.squadron[i].squadron != SQ_ZERO)
		  )
	{
		Node_Data.squadron[i].periodstatus = ps;
		i++;
	}
#endif
}

//////////////////////////////////////////////////////////////////////
//
// Function:    FourHourPeriod
// Date:		16/02/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	NodeData::FourHourPeriod(bool	endofday)
{
#ifndef BOB_DEMO_VER
	if (MMC.currtime>=AFTERNOONPERIODSTART)								//AM 10Oct00
		MMC.currperiodtime  = AFTERNOONPERIODSTART;						//AM 10Oct00
	else																//AM 10Oct00
		MMC.currperiodtime = MIDDAYPERIODSTART;							//AM 10Oct00
	MMC.Sky.SetMissionConditions();										//JON 28Jul00
	Dead_Stream.ReviveWorld(1,0);///*CSB*/1,0);
	CheckDamage(Dead_Stream);
	int i;
	for (i=0;gruppe[i].squadron;i++)
		if (gruppe[i].periodsuntilready)
			if (gruppe[i].periodsuntilready!=gruppe[i].BUSY_IN_EUROPE)
			{
				if (gruppe[i].periodsuntilready>0)
				{
					gruppe[i].periodsuntilready-=1;
					if (gruppe[i].periodsuntilready==0)
					{
						//SEND MESSAGE TO SAY SQUADRON NOW ACTIVE
						intel.AddMessage(IntelMsg::MED_MANAGEMENT_LW,AS_NOTSWITCH,SCRIPT_LWACPRODUCTIONFULFILLED ,gruppe[i].homeairfield,UID_NULL,TargetIndexes(gruppe[i].squadron,gruppe[i].acavail));
					}
				}
				else
					gruppe[i].periodsuntilready+=1;	//don't send message
			}
	for (i=0;gruppe[i].squadron;i++)
		if (gruppe[i].periodsuntilready==0)
		{
			gruppe[i].ModifyMoraleNonCombat();
			IncreasePilotsIfRequired(gruppe[i]);
		}

	for (i=0;squadron[i].squadron;i++)
	{
		if (squadron[i].moveto)
		{	//squadron movements implemented
			Squad_Diary.CreateTransfer(&squadron[i]);
			if (squadron[i].moveto==UID_AF_NEWCASTLE)
				intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_ONMOVEREST,squadron[i].homeairfield,squadron[i].moveto,TargetIndexes(squadron[i].squadron,squadron[i].acavail));
			else
				intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_ONMOVE,squadron[i].homeairfield,squadron[i].moveto,TargetIndexes(squadron[i].squadron,squadron[i].acavail));
			squadron[i].homeairfield=squadron[i].moveto;
			squadron[i].moveto=UID_NULL;
		}

		if (squadron[i].totestatus==Profile::PS_ORDER_30)
			squadron[i].UpdateReadiness();	
		squadron[i].ModifyMoraleNonCombat();
		IncreasePilotsIfRequired(squadron[i]);
		TargetFighterField* tf=Node_Data[squadron[i].homeairfield];	
		if (tf->truestatus>=Target::TS_NEARLYDESTROYED || tf->subdamagelevels[TargetFighterField::SDL_RUNWAY]>=Target::TS_NEARLYDESTROYED)
		{
			if (squadron[i].totestatus!=Profile::PS_OFFBASE)
			{
				squadron[i].totestatus=Profile::PS_AIRFIELDOUT;
				squadron[i].usedacbits=0xfff;
			}
		}
		else
		{
			if (squadron[i].totestatus==Profile::PS_AIRFIELDOUT)
			{
				squadron[i].totestatus=Profile::PS_AT_30;
				squadron[i].usedacbits=0;
			}
		}

	}
	AircraftRepairs4Hour();
	if (!endofday)
	{	
		if (BadWeatherCheck())
		{
//DEADCODE RDH 31/05/00 			SetRAFReadiness(Profile::PS_SPARE);
			SetRAFPeriodStatus(Squadron::BAD_WEATHER);
			int period;
			while ((period=Node_Data.PerformMoveCycle())==0)
				MMC.accumulator=SECSPERSAGFRAME;
			Node_Data.PerformNextPeriod(period);

		}else
		{
			if (GotBadWeatherPeriod())
				SetRAFPeriodStatus(Squadron::BAD_WEATHER);
			else
			{
				LWDirectivesResults::LaunchDirectiveMissions();


//DeadCode JIM 19Sep00 				SetRAFReadiness();
			}
		}
	}


#endif
}


//////////////////////////////////////////////////////////////////////
//
// Function:    GenerateSecondaries
// Date:		29/02/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
int	NodeData::GenerateSecondaries(UniqueID* buffer,int minsize,int maxsize,int currsize)
{
	if (maxsize==0)
		maxsize=minsize;
	assert (minsize<=maxsize);
	int tried=0;
	while (currsize<minsize)
	{
		TargetGroup* g=operator[](buffer[tried]);
		int i,j;
		for (i=0;i<5/*TargetGroup::MAX_SECONDARIES*/;i++)
		{
			UniqueID u=g->secondaries[i];
			breakif(!u);
			for (j=0;j<currsize;j++)
				breakif(buffer[tried]==g->secondaries[i]);
			if (j==currsize)
				buffer[tried++]=g->secondaries[i];
			breakif(currsize==maxsize);
		}
		tried++;
		assert(tried!=currsize);
	}
	return currsize;
}

FileNum	NodeData::CheckTargetLoaded(UniqueID targ,bool	inconsequentials)
{
	FileNum bf=TargetToBf(targ,inconsequentials);
	if (bf)
	{
//DEADCODE DAW 03/02/00 		if (Persons2::loadedBF[0]!=FIL_1_convoy)
//DEADCODE DAW 03/02/00 			_Error.EmitSysErr("Failed to load subworld file %04x. Fell back to map code!",bf);
		Persons4	persons;	
		int slot=0;
		if 	(!persons.GetSpareBFNumber(slot))
			slot=persons.DeleteOldestBF();
		persons.LoadSubPiece(NULL,bf,slot,Persons4::LOAD);
		return bf;
	}
	else
		return FIL_NULL;


}

FileNum NodeData::TargetToBf(UniqueID targ,bool	inconsequentials)
{
	if (targ>IllegalBAND)
		return FIL_NULL;
	TargetGroup* g=operator[](targ);
	FileNum rv=FIL_NULL;
	if (g)
	{
		if (inconsequentials)
			if (*g==TargetGroup::TSS_TargetAirfield)
			{
				rv=g->inconsequentialbattlefield[Math_Lib.rnd(3)];
				if (!rv)
					rv=g->inconsequentialbattlefield[0];
			}
			else
				rv=g->inconsequentialbattlefield[0];
		else
			rv=g->detailbattlefield;
		if (rv)
			if (Persons2::BFLoaded(rv))
				return FIL_NULL;
	}
	return rv;

}


int		NodeData::CountSquadsAtAirfield(UniqueID myhome)
{
	int rv=0;
	for (BritSquadron*	bsp=Node_Data.squadron;bsp->squadron;bsp++)
		if (bsp->homeairfield==myhome)
			rv++;
	return rv;
}

void	NodeData::AircraftRepairs4Hour()
{
	//info for review screen...
	MMC.thisweekreview.SetNote(PT_SPIT_A,PeriodReview::NEWREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_SPIT_A,PeriodReview::POTENTIALREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_SPIT_A,PeriodReview::REPAIRSINSYSTEM,0);
	MMC.thisweekreview.SetNote(PT_HURR_A,PeriodReview::NEWREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_HURR_A,PeriodReview::POTENTIALREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_HURR_A,PeriodReview::REPAIRSINSYSTEM,0);
	MMC.thisweekreview.SetNote(PT_ME109,PeriodReview::NEWREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_ME109,PeriodReview::POTENTIALREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_ME109,PeriodReview::REPAIRSINSYSTEM,0);
	MMC.thisweekreview.SetNote(PT_ME110,PeriodReview::NEWREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_ME110,PeriodReview::POTENTIALREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_ME110,PeriodReview::REPAIRSINSYSTEM,0);
	MMC.thisweekreview.SetNote(PT_JU87,PeriodReview::NEWREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_JU87,PeriodReview::POTENTIALREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_JU87,PeriodReview::REPAIRSINSYSTEM,0);
	MMC.thisweekreview.SetNote(PT_DO17,PeriodReview::NEWREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_DO17,PeriodReview::POTENTIALREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_DO17,PeriodReview::REPAIRSINSYSTEM,0);
	MMC.thisweekreview.SetNote(PT_JU88,PeriodReview::NEWREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_JU88,PeriodReview::POTENTIALREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_JU88,PeriodReview::REPAIRSINSYSTEM,0);
	MMC.thisweekreview.SetNote(PT_HE111,PeriodReview::NEWREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_HE111,PeriodReview::POTENTIALREPAIRS,0);
	MMC.thisweekreview.SetNote(PT_HE111,PeriodReview::REPAIRSINSYSTEM,0);
	

	for (TargetSectorField*	sect=sectorlist;sect->uid;sect++)
	{
		for (TargetFighterField* sat=sect;sat;sat=sat->nextsatelite())
			sat->AircraftRepairs4Hour();
	}
	for (Gruppen* gr=Node_Data.gruppe;gr->squadron;gr++)
	{	//germans can repair 3 points of damaged aircraft per period
		//Either:
			//3 quick repairable
			//1 slow+1quick
			//2 quick
			//1 quick
			//1 slow
		int oldavail=gr->acavail;
		MMC.thisweekreview.Note(gr->AcType(),PeriodReview::POTENTIALREPAIRS,3);
		if (gr->acquickrepairable>=3)
		{
			gr->acavail+=3;
			gr->acquickrepairable-=3;
			MMC.thisweekreview.Note(gr->AcType(),PeriodReview::REPAIR,3);
			MMC.thisweekreview.Note(gr->AcType(),PeriodReview::NEWREPAIRS,3);
		}
		else
		if (gr->acslowrepairable>=1)
		{
			if (gr->acquickrepairable>=1)
			{
				gr->acavail+=2;
				gr->acquickrepairable-=1;
				gr->acslowrepairable-=1;
				MMC.thisweekreview.Note(gr->AcType(),PeriodReview::REPAIR,2);
				MMC.thisweekreview.Note(gr->AcType(),PeriodReview::NEWREPAIRS,2);
			}
			else
			{
				gr->acavail+=1;
				gr->acslowrepairable-=1;
				MMC.thisweekreview.Note(gr->AcType(),PeriodReview::REPAIR,1);
				MMC.thisweekreview.Note(gr->AcType(),PeriodReview::NEWREPAIRS,1);
			}
		}
		else
		{
			MMC.thisweekreview.Note(gr->AcType(),PeriodReview::REPAIR,gr->acquickrepairable);
			MMC.thisweekreview.Note(gr->AcType(),PeriodReview::NEWREPAIRS,gr->acquickrepairable);
			gr->acavail+=gr->acquickrepairable;
			gr->acquickrepairable=0;
		}
			MMC.thisweekreview.Note(gr->AcType(),PeriodReview::REPAIRSINSYSTEM,gr->acquickrepairable+gr->acslowrepairable);

		if (oldavail<30 && gr->acavail>=30)
		{	//Message that squadron is fully active.
			
		}

	}

}
void	TargetFighterField::AircraftRepairs4Hour()
{
	// Each airfield can repair up to 3 minor if no other damage
	// Only sector airfield repairs major damage
	// Sector AF can repair 2 local aircraft per period, or one per satelite
	// If sector airfield has any outstanding repairs then no satelites can be repaired
	// If repairs are damaged then production drops proportionally.
	// If repairs are destroyed then all bad damage is sent to scrap
	int	sparespit=0,sparehurr=0;
	{for (BritSquadron*	bsp=Node_Data.squadron;bsp->squadron;bsp++)
		if (bsp->homeairfield==uid)
			if (bsp->acquickrepairable+bsp->acslowrepairable==0)
				if (bsp->actype<PT_HURR_A)
					sparespit++;
				else
					sparehurr++;
	}

	for (BritSquadron*	bsp=Node_Data.squadron;bsp->squadron;bsp++)
		if (bsp->homeairfield==uid)
			if (bsp->acquickrepairable+bsp->acslowrepairable!=0)
			{
				int quickrate=3;
				int	slowrate=2;
				//decrease slow if satelite
				TargetFighterField* sectaf=getsectoraf();
				if (sectaf!=this)
					slowrate=1;
				//increase quick if spare mechanics
				if (bsp->actype<PT_HURR_A)
					if (--sparespit>0)
						quickrate+=1;
					else
					{}
				else
					if (--sparehurr>0)
						quickrate+=1;
					else
					{}
				//decrease quick if local damage
				if (subdamagelevels[SDL_REPAIR]>=100)
					quickrate=1;
				else
					quickrate=quickrate*(150-subdamagelevels[SDL_REPAIR])/150;	//JIM 4Oct00
				//decrease slow rate if sector damage
				if (sectaf->subdamagelevels[SDL_REPAIR]>=100)
				{	//Scrap the aircraft that would have been repaired
					if (slowrate>bsp->acslowrepairable)
						slowrate=bsp->acslowrepairable;
					bsp->acslowrepairable-=slowrate;
					if (bsp->actype<=PT_SPIT_B)
						Node_Data.production[PT_SPIT_A].scrappedaircraft+=slowrate;
					else
						Node_Data.production[PT_HURR_A].scrappedaircraft+=slowrate;
					MMC.thisweekreview.Note(bsp->actype,PeriodReview::DESTROY,slowrate);

					slowrate=0;
				}
				else
				if (sectaf->subdamagelevels[SDL_REPAIR]>=70)
				{	//reduce repair rate by 1 or 2
					slowrate--;
					if (Math_Lib.rnd()&7)
						slowrate=0;
				}
				else
				if (sectaf->subdamagelevels[SDL_REPAIR]>=30)
					if (Math_Lib.rnd()&3)	//reduce repair rate by 1
						slowrate--;

				MMC.thisweekreview.Note(bsp->actype,PeriodReview::POTENTIALREPAIRS,bsp->acquickrepairable+bsp->acslowrepairable);
				if (quickrate>bsp->acquickrepairable)
				{
					bsp->acavail+=bsp->acquickrepairable;
					MMC.thisweekreview.Note(bsp->actype,PeriodReview::REPAIR,bsp->acquickrepairable);
					MMC.thisweekreview.Note(bsp->actype,PeriodReview::NEWREPAIRS,bsp->acquickrepairable);
					bsp->acquickrepairable=0;
				}
				else
				{
					bsp->acavail+=quickrate;
					MMC.thisweekreview.Note(bsp->actype,PeriodReview::REPAIR,quickrate);
					MMC.thisweekreview.Note(bsp->actype,PeriodReview::NEWREPAIRS,quickrate);
					bsp->acquickrepairable-=quickrate;
				}
				if (slowrate>bsp->acslowrepairable)
				{
					bsp->acavail+=bsp->acslowrepairable;				//JIM 16Sep00
					MMC.thisweekreview.Note(bsp->actype,PeriodReview::REPAIR,bsp->acslowrepairable);
					MMC.thisweekreview.Note(bsp->actype,PeriodReview::NEWREPAIRS,bsp->acslowrepairable);
					bsp->acslowrepairable=0;
				}
				else
				{
					bsp->acavail+=slowrate;
					MMC.thisweekreview.Note(bsp->actype,PeriodReview::REPAIR,slowrate);
					MMC.thisweekreview.Note(bsp->actype,PeriodReview::NEWREPAIRS,slowrate);
					bsp->acslowrepairable-=slowrate;
				}
				MMC.thisweekreview.Note(bsp->actype,PeriodReview::REPAIRSINSYSTEM,bsp->acquickrepairable+bsp->acslowrepairable);
			}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ApplyDamage
// Date:		14/09/00
// Author:		JIM
//
//Description:	Apply the 3d or fake damage level to the 2d.
//				 
//
//////////////////////////////////////////////////////////////////////
void	TargetGroup::ApplyDamage(int newlevel,UniqueID reportsuccess)
{
	if (newlevel>120)
		newlevel=120;
	int oldstatus=PlayerStatus();
	if (reportsuccess)	   //
	{
		if (IsA(Target::TSS_TargetConvoy))
			knownstatus=newlevel;
		else
			if (newlevel>+knownstatus+20)
				knownstatus=(newlevel+100)/2;	//claim MUCH more!
			else
				if (knownstatus==255)										//JIM 16Sep00
					knownstatus=(newlevel+50)/2;
				else
					knownstatus=(newlevel+knownstatus*2)/3;
	}
	truestatus=newlevel;
	if (reportsuccess)
		if (oldstatus==Target::TS_FLAG_UNKNOWN ||  oldstatus<PlayerStatus())
		{
			if (IsA(Target::TSS_TargetFactory))
			{
				TargetFactory* fp=TargetFactoryPtr(this);
				if (newlevel<100)
					fp->currperweek=fp->maxperweek*(100-newlevel)/100;
				else
					fp->currperweek=0;
				if (fp->maxdispersedperweek<0)	//negative means planned dispersal that has not happened yet!
				{
					fp->currperweek+=fp->perweekwhenout;
					if (fp->currperweek>-fp->maxdispersedperweek)
						fp->currperweek=-fp->maxdispersedperweek;	
					if (fp->currperweek>fp->maxperweek)
						fp->currperweek=fp->maxperweek;
				}
			}
			if (reportsuccess!=IllegalSepID)
				if (Todays_Packages.localplayer==NAT_RAF)
				{
					ScriptTables script=SCRIPT_ASSETDESTROYED;
					if (truestatus>Target::TS_LIGHTDAMAGE)
						if (IsA(Target::TSS_TargetRadar))
							if (truestatus<Target::TS_NEARLYDESTROYED)
								script=SCRIPT_TRGDAMAGED;
							else
								script=SCRIPT_RDFDESTROYED;
						else
							if (truestatus>Target::TS_NEARLYDESTROYED && IsA(Target::TSS_TargetAirfield))
								if (IsA(Target::TSS_TargetSectorField))
									script=SCRIPT_LOSTCONTACTSECTOROPS;
								else
									script=SCRIPT_LOSTCONTACTAIRFIELDS;



					if (script==SCRIPT_ASSETDESTROYED)
						if (truestatus<Target::TS_LIGHTDAMAGE)
							script=SCRIPT_TRGUNDAMAGED;
						else
						if (truestatus<Target::TS_BADDAMAGE)
							script=SCRIPT_TRGLITTLEDAMAGED;
						else
						if (truestatus<Target::TS_NEARLYDESTROYED)
							script=SCRIPT_TRGBIGDAMAGED;
					Node_Data.intel.AddMessage(IntelMsg::HIGH_TARGET_WOMAN,AS_TARG,script,reportsuccess,uid);

				}
				else
				{
					ScriptTables script=SCRIPT_TRGDESTROYED;
					if (knownstatus<Target::TS_NEARLYDESTROYED)
						if (knownstatus>Target::TS_LIGHTDAMAGE)
							script=SCRIPT_REPORTSSUCCESS;
						else
							script=SCRIPT_RAIDFAILHITTARGET;
					Node_Data.intel.AddMessage(IntelMsg::HIGH_TARGET_LW,AS_TARG,script,reportsuccess,uid);
				}
		}
		else
		{	//condition improved
	//DeadCode JIM 14Sep00 		if (tg->PlayerStatus()<Target::TS_LIGHTDAMAGE)
	//DeadCode JIM 14Sep00 			rg->missresult=MR_ATTACKNODAMAGE;
	//DeadCode JIM 14Sep00 		else 
	//DeadCode JIM 14Sep00 			if (tg->PlayerStatus()<Target::TS_BADDAMAGE)
	//DeadCode JIM 14Sep00 				rg->missresult=MR_ATTACKSLIGHTDAMAGE;
	//DeadCode JIM 14Sep00 			else
	//DeadCode JIM 14Sep00 				rg->missresult=MR_ATTACKSUCCESS;
			if (PlayerStatus()<Target::TS_BADDAMAGE && oldstatus>Target::TS_BADDAMAGE)
			{
	//DeadCode JIM 14Sep00 			if (IsA(Target::TSS_TargetRadar))
				//the only messages for asset repair are airfields!

			}



		}


}

void	TargetFighterField::ApplyDamage(int totaldamage,int	sdl_repair,int sdl_fuel,int sdl_runway,int sdl_staff,UniqueID reportsuccess)
{
	int diff;
	if ((diff=sdl_repair-subdamagelevels[SDL_REPAIR])>5)
	{	//over 5% damage to repairs. Chance of destroying some repairing aircraft
		for (BritSquadron*	bsp=Node_Data.squadron;bsp->squadron;bsp++)
			if (bsp->homeairfield==uid && bsp->acquickrepairable+bsp->acslowrepairable)
			{
				int	chance=diff+(bsp->acquickrepairable+bsp->acslowrepairable);
				if ((chance=Math_Lib.rnd(chance))!=0)
					if ((chance&1) || !bsp->acslowrepairable)
					{
						bsp->acquickrepairable--;
						bsp->acslowrepairable++;
					}
					else
					{
						bsp->acslowrepairable--;
						if (bsp->actype<=PT_SPIT_B)
							Node_Data.production[PT_SPIT_A].scrappedaircraft++;
						else
							Node_Data.production[PT_HURR_A].scrappedaircraft++;
					}
			}
	}

	if ((diff=sdl_runway-subdamagelevels[SDL_RUNWAY])>5)
	{	//over 5% damage to runway. Chance of destroying some inactive squadrons
		for (BritSquadron*	bsp=Node_Data.squadron;bsp->squadron;bsp++)
			if (bsp->homeairfield==uid) 
			{	
				if  (		(totaldamage > Target::TS_BADDAMAGE)
						&&	(sdl_runway > 80)
					)
					RAFDirectivesResults::MoveSquadron(bsp-Node_Data.squadron, Target::LOC_N_LON, Target::LOC_S_LON, Target::LOC_COAST );

				
				if (bsp->periodstatus>=bsp->NO_FLYING)
				{
					int	chance=diff+bsp->acavail;
 					chance=Math_Lib.rnd(chance)/2;
					if (chance>bsp->acavail)
						chance=bsp->acavail;
					bsp->acavail-=chance;
					bsp->acslowrepairable+=chance/3;
					chance-=chance/3;
					bsp->acquickrepairable+=chance;
					if (reportsuccess)
						Node_Data.intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_CAUGHTONGROUND,uid,uid,TargetIndexes(bsp->squadron,chance));
				}
			}

	}
	

	int oldstatus=PlayerStatus();
	if (totaldamage>120)
		totaldamage=120;
	if (reportsuccess)	   //
	{
		if (totaldamage>+knownstatus+20)
			knownstatus=(totaldamage+100)/2;	//claim MUCH more!
		else
			if (knownstatus==Target::TS_FLAG_UNKNOWN)										//JIM 16Sep00
				knownstatus=(totaldamage+50)/2;
			else
				knownstatus=(totaldamage+knownstatus*2)/3;
	}
	truestatus=totaldamage;
	subdamagelevels	[SDL_REPAIR]=	sdl_repair;
	subdamagelevels	[SDL_FUEL]=		sdl_fuel;
	subdamagelevels	[SDL_RUNWAY]= 	sdl_runway;
	subdamagelevels	[SDL_STAFF]=	sdl_staff;

	if (reportsuccess)
	{  
		if (oldstatus==Target::TS_FLAG_UNKNOWN ||  oldstatus<PlayerStatus())
		{
			if (reportsuccess!=IllegalSepID)
				if (Todays_Packages.localplayer==NAT_RAF)
				{
					ScriptTables script=SCRIPT_ASSETDESTROYED;
					if (truestatus>Target::TS_LIGHTDAMAGE)
//DeadCode JIM 2Nov00 						if (IsA(Target::TSS_TargetRadar))
//DeadCode JIM 2Nov00 							if (truestatus<Target::TS_NEARLYDESTROYED)
//DeadCode JIM 2Nov00 								script=SCRIPT_TRGDAMAGED;
//DeadCode JIM 2Nov00 							else
//DeadCode JIM 2Nov00 								script=SCRIPT_RDFDESTROYED;
//DeadCode JIM 2Nov00 						else
							if (truestatus>Target::TS_NEARLYDESTROYED)
								if (IsA(Target::TSS_TargetSectorField))
									script=SCRIPT_LOSTCONTACTSECTOROPS;
								else
									script=SCRIPT_LOSTCONTACTAIRFIELDS;
					if (script==SCRIPT_ASSETDESTROYED)
						if (truestatus<Target::TS_LIGHTDAMAGE)
							script=SCRIPT_TRGUNDAMAGED;
					Node_Data.intel.AddMessage(IntelMsg::HIGH_TARGET_WOMAN,AS_TARG,script,uid,uid);
				}
				else
				{
					ScriptTables script=SCRIPT_TRGDESTROYED;
					if (knownstatus<Target::TS_NEARLYDESTROYED)
						if (knownstatus>Target::TS_LIGHTDAMAGE)
							script=SCRIPT_REPORTSSUCCESS;
						else
							script=SCRIPT_RAIDFAILHITTARGET;
					Node_Data.intel.AddMessage(IntelMsg::HIGH_TARGET_LW,AS_TARG,script,reportsuccess,uid);

				}
		}
		else
			if (Todays_Packages.localplayer==NAT_RAF)
			{	//AF is repairing...
				if (truestatus<Target::TS_NEARLYDESTROYED  && oldstatus>=Target::TS_NEARLYDESTROYED)
				{
					Node_Data.intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_REGAINEDCONTACT,uid,uid);
				}
			}

	}
}

int	NodeData::SquadsAtField(UniqueID uidaf)
{//counts squadrons actually at the field + the planned moves in and out


	int k=0, numsq = 0;
	while (Node_Data.squadron[k].squadron != SQ_ZERO)
	{
		if  (	(Node_Data.squadron[k].homeairfield == uidaf)
			&&	(	(Node_Data.squadron[k].moveto == UID_NULL)
				)
			)
			numsq++;
		if (Node_Data.squadron[k].moveto == uidaf) //counts all movements in including back to home. ie no move
			numsq++;
		k++;
	}
	return (numsq);
}

int	NodeData::SquadsInSector(TargetFighterField* af)
{
	int squads;
	squads = SquadsAtField(af->uid);
	while ((af = af->nextsatelite())!= NULL)
		squads += SquadsAtField(af->uid);
	return (squads);
}
void	NodeData::FillLWStrengthInfo()
{
	int i;
	for (i = 0; i <LWMAXTYPES; i++)
	{
		LWstrengthinfo[i].catA = 0;
		LWstrengthinfo[i].catB = 0;
		LWstrengthinfo[i].catC = 0;
		LWstrengthinfo[i].acready = 0;
		LWstrengthinfo[i].actotal = 0;
	}

	i = 0;
	int type;
	while (		(Node_Data.gruppe[i].squadron != SQ_ZERO)
		  )
	{
		PlaneTypeSelect	actype = Node_Data.gruppe[i].AcType();
		type = actype - PT_GER_FLYABLE;

		if (type < LWTOTAL)
		{
			if (!Node_Data.gruppe[i].Busy())
			{
				int cat = Node_Data.gruppe[i].Category();
				if (cat  == 0)
				{
					LWstrengthinfo[type].catA++;
					LWstrengthinfo[LWTOTAL].catA++;
				}else 		if (cat  == 1)
				{
					LWstrengthinfo[type].catB++;
					LWstrengthinfo[LWTOTAL].catB++;
				}else 
				{
					LWstrengthinfo[type].catC++;
					LWstrengthinfo[LWTOTAL].catC++;
				}
				LWstrengthinfo[LWTOTAL].actotal += Node_Data.gruppe[i].ACTotal();
				LWstrengthinfo[type].actotal += Node_Data.gruppe[i].ACTotal();
				LWstrengthinfo[LWTOTAL].acready += Node_Data.gruppe[i].acavail;
				LWstrengthinfo[type].acready += Node_Data.gruppe[i].acavail;
			}
		}	

	  i++;
	 }



}


void	NodeData::FillRAFStrengthInfo(bool countallincluding_gr13)
{
	int i;
	for (i = 0; i <RAFMAXTYPES; i++)
	{
		RAFstrengthinfo[i].catA = 0;
		RAFstrengthinfo[i].catB = 0;
		RAFstrengthinfo[i].catC = 0;
		RAFstrengthinfo[i].acready = 0;
		RAFstrengthinfo[i].actotal = 0;
		RAFstrengthinfo[i].pilots = 0;
	}

	i = 0;
	int type;
	while (		(Node_Data.squadron[i].squadron != SQ_ZERO)
		  )
	{
		if (		(Node_Data.squadron[i].homeairfield != UID_AF_NEWCASTLE)
				||	(countallincluding_gr13)
			)
		{
			PlaneTypeSelect	actype = Node_Data.squadron[i].AcType();
			type = HURR;
			if   (		(actype == PT_SPIT_A)
					||	(actype == PT_SPIT_B) 
				 )
				type = SPITS;
			if (Node_Data.squadron[i].totestatus!=Profile::PS_OFFBASE)
			{
				int cat = Node_Data.squadron[i].Category();
				if (cat  == 0)
				{
					RAFstrengthinfo[type].catA++;
					RAFstrengthinfo[RAFTOTAL].catA++;
				}else 		if (cat  == 1)
				{
					RAFstrengthinfo[type].catB++;
					RAFstrengthinfo[RAFTOTAL].catB++;
				}else 
				{
					RAFstrengthinfo[type].catC++;
					RAFstrengthinfo[RAFTOTAL].catC++;
				}
				RAFstrengthinfo[RAFTOTAL].pilots += Node_Data.squadron[i].pilotsavail;
			}
			RAFstrengthinfo[RAFTOTAL].actotal += Node_Data.squadron[i].ACTotal();
			RAFstrengthinfo[type].actotal += Node_Data.squadron[i].ACTotal();
			RAFstrengthinfo[RAFTOTAL].acready += Node_Data.squadron[i].acavail;
			RAFstrengthinfo[type].acready += Node_Data.squadron[i].acavail;
		}

	  i++;
	 }



}

bool	NodeData::AssignSecondaryRadars()
{
	int inactiveradars=0;
	{for (TargetRadar* r=radarlist;r->uid;r++)
	{
		r->mobileunit=false;
		r->patroller=false;
		if (r->truestatus>70)
			inactiveradars++;
	}}
	int	mobileradars=6;
	bool	rv=(mobileradars>=inactiveradars);
	{for (TargetRadar* r=radarlist;r->uid;r++)
	{
		if (r->truestatus>TS_BADDAMAGE)
		{
			if (Math_Lib.rnd(inactiveradars)<mobileradars)
			{
				mobileradars--;
				r->mobileunit=true;
				intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_MOBILE ,r->uid,r->uid);

			}
			inactiveradars--;
		}
	}}
	return rv;
}

int	NodeData::RAFFindPercentAvail(int uidbandstart, int uidbandend, int trgpriority0, int trgpriority1)
{
	int  uid= uidbandstart;
	int destroyed = 0, total = 0;

	while (uid < uidbandend)
	{
		TargetGroup* trg;
		trg = Node_Data[(UniqueID)uid];
		ItemBasePtr p;
		p=Persons2::ConvertPtrUID((UniqueID)uid);
		if (		(trg) && (p)
				&&	(		(trg->truepriority >= trgpriority0)
						&&	(trg->truepriority <= trgpriority1)
					)
			)
		{
			total++;
			if	(trg->truestatus  >= Target::TS_DESTROYED)
				destroyed++;


		}
		uid++;
	}
	destroyed = destroyed * 100;
	destroyed = destroyed/total;
	return (destroyed);

}
int	NodeData::LWFindPercentAvail(int uidbandstart, int uidbandend, int trgpriority0, int trgpriority1)
{
	int  uid= uidbandstart;
	int destroyed = 0, total = 0;

	while (uid < uidbandend)
	{
		TargetGroup* trg;
		trg = Node_Data[(UniqueID)uid];
		ItemBasePtr p;
		p=Persons2::ConvertPtrUID((UniqueID)uid);
		if (		(trg) && (p)
				&&	(		(trg->falsepriority >= trgpriority0)
						&&	(trg->falsepriority <= trgpriority1)
					)
			)
		{
			total++;
//DeadCode MS 15Nov00 			if	(trg->knownstatus  >= Target::TS_DESTROYED)
//DeadCode MS 15Nov00 				destroyed++;
			if	(trg->knownstatus  >= Target::TS_BADDAMAGE && trg->knownstatus < Target::TS_MAXIMUM)
				destroyed++;


		}
		uid++;
	}
	destroyed = destroyed * 100;
	destroyed = destroyed/total;
	return (destroyed);

}
void	NodeData::SwapSquadron()
{
	int k=0;
	int best13sqcat = 3,  best13sq = -1;
	int worstnon13sqcat = -1,  worstnon13sq = -1;

	while (Node_Data.squadron[k].squadron != SQ_ZERO)
	{
		int cat = Node_Data.squadron[k].Category();

 		if (Node_Data.squadron[k].homeairfield == UID_AF_NEWCASTLE)
		{
			if (cat < best13sqcat)
			{
				best13sqcat = cat;
				best13sq = k;
			}
		}else
		{
			if (cat > worstnon13sqcat)
			{
				worstnon13sqcat = cat;
				worstnon13sq = k;
			}

		}

		k++;
	}
	if	(		(best13sq != -1)
			&&	(worstnon13sq != -1)
		)
	{
		Node_Data.squadron[best13sqcat].moveto = Node_Data.squadron[worstnon13sqcat].homeairfield;
		Node_Data.squadron[worstnon13sqcat].moveto = UID_AF_NEWCASTLE;
	}

}

