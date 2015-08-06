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

#include	"dosdefs.h"
#include	<stdio.h>
#define	F_COMMON
#define F_GRAFIX	
#include "uniqueid.h"
#include "ranges.h"
#include	"files.g"
#include	"fileman.h"
#include	"node.h"
#include	"makebf.h"
#include	"bfnumber.h"
#include	"persons2.h"
#define	QUICKQUICKQUICK
		#include	"..\mfc\resource.h"
		#include	"squick1.h"

typedef	 QuickFields	Q;
typedef	 QuickFields::QFD	QFD;
#define BLUE	0
#define	RED		1
int			CSQuick1::currquickmiss=-1;
int			CSQuick1::currquickfamily=-1;
QuickDef	CSQuick1::quickdef;


#ifdef	BOB_DEMO_VER													//RJS 30Jul00
#define	FILDEMO(arg)	FIL_NULL
#else
#define	FILDEMO(arg)	arg
#endif



//
//I have added the following system so that you can add title and description strings 
//without using the resources
//
//
#ifdef	STANDALONE

#define	ES_NULL			\0
#define	ES_HELLOWORLD	\1
#define	ES_ANDAGAIN		\2


#define	ES_MAX			255

#define	ES(name)	TOSTR(\0)TOSTR(ES_##name)
int lookupspace[ES_MAX]={0};
char extrastrings[]=
{	ES(HELLOWORLD) "Hello World"
	ES(ANDAGAIN)	"And again"
	ES(NULL)
};
#undef ES
#define _XCHR(x)         #@x
#define TOCHR(x)        _XCHR(x)

#define ES(name)	TOCHR(ES_##name)

QuickDef	CSQuick1::quickmissions[]=
{	//NOTE: THIS STUFF IS NOW COMPILED EXTERNALLY TO THE PROGRAM AND LOADED ON DEMAND
	//SAVES 39K AND ALLOWS EXTERNAL UPGRADING!

#ifdef	BOB_DEMO_VER

#pragma message(__HERE__ "Mark:  Add your demo missions here...")

//-----------------------------------------------------------------------------
//DEMO MISSION 1
	{
		IDS_DEMOMISSIONS,IDS_QUICK_30,IDS_QUICK_30_DESC,
		{
			{	{	{PT_SPIT_A,4,SKILL_HERO,FT_18000,IDS_UN_CAP,Q::QFD_FIXED_PLAYER} },
				{	{PT_SPIT_B,4,SKILL_HERO,FT_16000,IDS_UN_CAP,Q::QFD_FIXED_PLAYER+Q::QFD_ALLOW_ZERO_FL} }
			},
			{	{	{PT_DO17,2,SKILL_VETERAN,FT_15000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_PLAYER} },
				{	{PT_ME109,3,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_FIXED_PLAYER+Q::QFD_ALLOW_ZERO_FL} },
				{	{PT_DO17,2,SKILL_VETERAN,FT_16000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_PLAYER} },
				{	{PT_ME109,3,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_FIXED_PLAYER+Q::QFD_ALLOW_ZERO_FL} }
			}
		},
		BLUE,0,0,0,
		FIL_QUICKMISSION_33,FIL_QUICKMISSION_33,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_TT_DOCKS},	//IDS_INDUSTRY},
		{	{UID_DK_Southampton}
		},
		UID_DK_Southampton
	},

//DeadCode MS 08Aug00 //-----------------------------------------------------------------------------
//DeadCode MS 08Aug00 //DEMO MISSION 2
//DeadCode MS 08Aug00 	{
//DeadCode MS 08Aug00 		IDS_DEMOMISSIONS,IDS_QUICK_2,IDS_QUICK_2_DESC,
//DeadCode MS 08Aug00 		{	
//DeadCode MS 08Aug00 			{	{	{PT_SPIT_A,1,SKILL_VETERAN,FT_3000,IDS_UN_CAP,Q::QFD_BRIT_LONE} }	},
//DeadCode MS 08Aug00 			{	{	{PT_ME109,1,SKILL_VETERAN,FT_3000,IDS_UN_CAP,Q::QFD_GERM_LONE} }	}
//DeadCode MS 08Aug00 		},
//DeadCode MS 08Aug00 		BLUE,0,0,0,
//DeadCode MS 08Aug00 		FIL_QUICKMISSION_34,FIL_QUICKMISSION_34,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
//DeadCode MS 08Aug00 		{ IDS_GROUP10AF,IDS_SUPPLYPOINT,IDS_CONFIGIGNORED},
//DeadCode MS 08Aug00 		{ 	{UID_AF_TANGMERE,UID_AF_BIGGINHILL,UID_AF_DEBDEN,UID_AF_KENLEY},	
//DeadCode MS 08Aug00 			{UID_AF_Marck,UID_AF_Abbeville,UID_AF_Wissant,UID_AF_LeHarve},
//DeadCode MS 08Aug00 			{UID_AF_HAWKINGE,UID_AF_GRAVESEND},
//DeadCode MS 08Aug00 		},
//DeadCode MS 08Aug00 		UID_AF_TANGMERE
//DeadCode MS 08Aug00 	},
#endif

//-----------------------------------------------------------------------------
//BASIC TRAINING : takeoff

	{
		IDS_MISTYPE_BASICTRAINING,IDS_L_QUICK_1,IDS_QUICK_1_DESC,
		{	
			{	{	{PT_SPIT_A,1,SKILL_VETERAN,0,IDS_UN_CAP,Q::QFD_BRIT_LONE} }	},
			{	{	{PT_ME109,1,SKILL_VETERAN,0,IDS_UN_CAP,Q::QFD_GERM_LONE} }	}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_00),FIL_QUICKMISSION_03,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_GROUP11AF,IDS_SUPPLYPOINT},
		{ 	{UID_AF_TANGMERE,UID_AF_BIGGINHILL,UID_AF_DEBDEN,UID_AF_KENLEY},	
			{UID_AF_Marck,UID_AF_Abbeville,UID_AF_Wissant,UID_AF_LeHarve}
		},
		UID_AF_TANGMERE
	},

//-----------------------------------------------------------------------------
//BASIC TRAINING : landing 
	{
		IDS_MISTYPE_BASICTRAINING,IDS_QUICK_2,IDS_QUICK_2_DESC,
		{	
			{	{	{PT_SPIT_A,1,SKILL_VETERAN,FT_2000,IDS_UN_CAP,Q::QFD_BRIT_LONE} }	},
			{	{	{PT_ME109,1,SKILL_VETERAN,FT_2000,IDS_UN_CAP,Q::QFD_GERM_LONE} }	}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_01),FIL_QUICKMISSION_04,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_GROUP11AF,IDS_SUPPLYPOINT},
		{ 	{UID_AF_TANGMERE,UID_AF_BIGGINHILL,UID_AF_DEBDEN,UID_AF_KENLEY},	
			{UID_AF_Marck,UID_AF_Abbeville,UID_AF_Wissant,UID_AF_LeHarve}
		},
		UID_AF_TANGMERE
	},
//-----------------------------------------------------------------------------
//BASIC TRAINING : circuits
	{
		IDS_MISTYPE_BASICTRAINING,IDS_QUICK_3,IDS_QUICK_3_DESC,
		{	
			{	{	{PT_SPIT_A,1,SKILL_VETERAN,FT_3000,IDS_UN_CAP,Q::QFD_BRIT_LONE} }	},
			{	{	{PT_ME109,1,SKILL_VETERAN,FT_3000,IDS_UN_CAP,Q::QFD_GERM_LONE} }	}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_02),FIL_QUICKMISSION_05,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_GROUP11AF,IDS_SUPPLYPOINT},
		{ 	{UID_AF_TANGMERE,UID_AF_BIGGINHILL,UID_AF_DEBDEN,UID_AF_KENLEY},	
			{UID_AF_Marck,UID_AF_Abbeville,UID_AF_Wissant,UID_AF_LeHarve},
		},
		UID_AF_TANGMERE
	},

//-----------------------------------------------------------------------------
//BASIC TRAINING : squad takeoff
	{	
		IDS_MISTYPE_BASICTRAINING,IDS_QUICK_4,IDS_QUICK_4_DESC,
		{	
			{	{	{PT_SPIT_A,4,SKILL_VETERAN,0,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }	},
			{	{	{PT_ME109,3,SKILL_VETERAN,0,IDS_UN_CAP,Q::QFD_GERM_FIGHTER} }	}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_06),FIL_QUICKMISSION_10,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_GROUP11AF,IDS_SUPPLYPOINT},
		{ 	{UID_AF_TANGMERE,UID_AF_BIGGINHILL,UID_AF_DEBDEN,UID_AF_KENLEY},	
			{UID_AF_Marck,UID_AF_Abbeville,UID_AF_Wissant,UID_AF_LeHarve},
		},
		UID_AF_TANGMERE
	},

//-----------------------------------------------------------------------------
//BASIC TRAINING :  Squadron landing
	{
		IDS_MISTYPE_BASICTRAINING,IDS_QUICK_5,IDS_QUICK_5_DESC,
		{	
			{	{	{PT_SPIT_A,4,SKILL_VETERAN,FT_3000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }	},
			{	{	{PT_ME109,3,SKILL_VETERAN,FT_3000,IDS_UN_CAP,Q::QFD_GERM_FIGHTER} }	}
		},
		BLUE,0,0,2,
		FILDEMO(FIL_QUICKMISSION_07),FIL_QUICKMISSION_11,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_GROUP11AF,IDS_SUPPLYPOINT},
		{ 	{UID_AF_TANGMERE,UID_AF_BIGGINHILL,UID_AF_DEBDEN,UID_AF_KENLEY},	
			{UID_AF_Marck,UID_AF_Abbeville,UID_AF_Wissant,UID_AF_LeHarve},
		},
		UID_AF_TANGMERE
	},


//-----------------------------------------------------------------------------
//FAMILIARISATION : follow leader
	{
		IDS_MISTYPE_FAMILIARISATION,IDS_QUICK_8,IDS_QUICK_8_DESC,
		{	
			{	{	{PT_SPIT_A,1,SKILL_ACE,FT_14000,IDS_UN_CAP,Q::QFD_BRIT_LONE}		}	},
			{	{	{PT_ME109,1,SKILL_ACE,FT_14000,IDS_UN_CAP,Q::QFD_GERM_LONE} }	}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_14),FIL_QUICKMISSION_17,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_GROUP11AF,IDS_SUPPLYPOINT},
		{ 	{UID_AF_TANGMERE,UID_AF_BIGGINHILL,UID_AF_DEBDEN,UID_AF_KENLEY},	
			{UID_AF_Marck,UID_AF_Abbeville,UID_AF_Wissant,UID_AF_LeHarve},
		},
		UID_AF_TANGMERE
	},

//-----------------------------------------------------------------------------
//FAMILIARISATION : formation flying
	{
		IDS_MISTYPE_FAMILIARISATION,IDS_QUICK_9,IDS_QUICK_9_DESC,
		{
			{	{	{PT_SPIT_A,4,SKILL_REGULAR,FT_15000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER}	}	},
			{	{	{PT_ME109,3,SKILL_REGULAR,FT_15000,IDS_UN_CAP,Q::QFD_GERM_FIGHTER}	}	},
		},

		BLUE,0,0,2,
		FILDEMO(FIL_QUICKMISSION_15),FIL_QUICKMISSION_18,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_GROUP11AF,IDS_SUPPLYPOINT},
		{	{UID_AF_NORTHOLT,UID_AF_NORTHWEALD,UID_AF_DEBDEN,UID_AF_HAWKINGE},
			{UID_AF_Marck,UID_AF_Abbeville,UID_AF_Wissant,UID_AF_LeHarve},
		},
		UID_AF_NORTHOLT
	},

//-----------------------------------------------------------------------------
//FAMILIARISATION : Free Flight
	{	//	S	W	G
		IDS_MISTYPE_FAMILIARISATION,IDS_QUICK_10,IDS_QUICK_10_DESC,
		{	
			{	{	{PT_SPIT_A,1,SKILL_REGULAR,FT_1000,IDS_UN_CAP,Q::QFD_BRIT_LONE}	}},
			{	{	{PT_ME109,1,SKILL_REGULAR,FT_1000,IDS_UN_CAP,Q::QFD_GERM_LONE} }	}
		},

		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_16),FIL_QUICKMISSION_19,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
//DeadCode MS 28Mar00 		{ IDS_AIRFIELD,IDS_SUPPLYPOINT,IDS_BRIDGE,IDS_CONVOYS},
//DeadCode MS 28Mar00 //TempCode MS 24Mar00 		{ 	{UID_AF_TANGMERE,UID_AF_BIGGINHILL,UID_AF_NORTHWEALD,UID_AF_KENLEY},	
//DeadCode MS 28Mar00 //TempCode MS 24Mar00 			{UID_AF_HORNCHURCH,UID_AF_DEBDEN,UID_AF_NORTHOLT,UID_AF_FILTON},
//DeadCode MS 28Mar00 //TempCode MS 24Mar00 			{UID_AF_MIDDLEWALLOP,UID_AF_DUXFORD,UID_AF_COLTISHALL,UID_AF_HAWKINGE},
//DeadCode MS 28Mar00 //TempCode MS 24Mar00 			{UID_AF_CROYDON,UID_HS_STPAULS,UID_HS_ROYALALBERT,UID_HS_HOUSESPARLIAMENT},
//DeadCode MS 28Mar00 		{ 	{UID_AF_WESTHAMPNETT,UID_AF_FOWLMERE,UID_AF_WARMWELL,UID_AF_EXETER},	
//DeadCode MS 28Mar00 			{UID_AF_PEMBREY,UID_AF_COLERNE,UID_AF_ROCHFORD,UID_AF_CROYDON},
//DeadCode MS 28Mar00 			{UID_AF_STAPLEFORD,UID_AF_MARTLESHAM,UID_AF_HAWKINGE,UID_AF_MANSTON},
//DeadCode MS 28Mar00 			{UID_AF_LYMPNE,UID_AF_WESTMALLING,UID_HS_ROYALALBERT,UID_HS_HOUSESPARLIAMENT},
//DeadCode MS 28Mar00 		},
//DeadCode MS 28Mar00 		UID_AF_TANGMERE
		{ IDS_COASTAL,IDS_SOUTHLONDON,IDS_NORTHLONDON},
		{ 	{UID_AF_TANGMERE,UID_AF_HAWKINGE,UID_AF_WARMWELL,UID_AF_MANSTON},	
			{UID_AF_KENLEY,UID_AF_BIGGINHILL,UID_AF_GRAVESEND,UID_AF_CROYDON},
			{UID_AF_HORNCHURCH,UID_AF_NORTHWEALD,UID_AF_DUXFORD,UID_AF_DEBDEN}
		},
		UID_AF_TANGMERE
	},

//THESE ARE THE TARGETS TO GO IN FINAL VERSION!!!!				//MS 28Mar00

//TempCode MS 28Mar00 		{ IDS_COASTAL,IDS_SOUTHLONDON,IDS_NORTHLONDON},
//TempCode MS 28Mar00 		{ 	{UID_AF_TANGMERE,UID_AF_HAWKINGE,UID_AF_WARMWELL,UID_AF_MANSTON},	
//TempCode MS 28Mar00 			{UID_AF_KENLEY,UID_AF_BIGGINHILL,UID_AF_GRAVESEND,UID_AF_CROYDON},
//TempCode MS 28Mar00 			{UID_AF_HORNCHURCH,UID_AF_NORTHWEALD,UID_AF_DUXFORD,UID_AF_DEBDEN}
//TempCode MS 28Mar00 		},
//TempCode MS 28Mar00 		UID_AF_TANGMERE

//-----------------------------------------------------------------------------
//FAMILIARISATION : land engine failure

	{
		IDS_MISTYPE_FAMILIARISATION,IDS_QUICK_6,IDS_QUICK_6_DESC,
		{	
			{	{	{PT_SPIT_A,1,SKILL_VETERAN,FT_2000,IDS_UN_CAP,Q::QFD_BRIT_LONE} }	},
			{	{	{PT_ME109,1,SKILL_VETERAN,FT_2000,IDS_UN_CAP,Q::QFD_GERM_LONE} }	}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_08),FIL_QUICKMISSION_12,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_GROUP11AF,IDS_SUPPLYPOINT},
		{ 	{UID_AF_TANGMERE,UID_AF_BIGGINHILL,UID_AF_DEBDEN,UID_AF_KENLEY},	
			{UID_AF_Marck,UID_AF_Abbeville,UID_AF_Wissant,UID_AF_LeHarve},
		},
		UID_AF_TANGMERE
	},

//-----------------------------------------------------------------------------
//FAMILIARISATION : land heavy damage
	{
		IDS_MISTYPE_FAMILIARISATION,IDS_QUICK_7,IDS_QUICK_7_DESC,
		{	
			{	{	{PT_SPIT_A,1,SKILL_VETERAN,FT_2000,IDS_UN_CAP,Q::QFD_BRIT_LONE} }	},
			{	{	{PT_ME109,1,SKILL_VETERAN,FT_2000,IDS_UN_CAP,Q::QFD_GERM_LONE} }	}
		},
		BLUE,0,0,0 ,
		FILDEMO(FIL_QUICKMISSION_09),FIL_QUICKMISSION_13,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_GROUP11AF,IDS_SUPPLYPOINT},
		{ 	{UID_AF_TANGMERE,UID_AF_BIGGINHILL,UID_AF_DEBDEN,UID_AF_KENLEY},	
			{UID_AF_Marck,UID_AF_Abbeville,UID_AF_Wissant,UID_AF_LeHarve},
		},
		UID_AF_TANGMERE
	},

//-----------------------------------------------------------------------------
//COMBAT : turkey
	{
		IDS_MISTYPE_DOGFIGHTING,IDS_QUICK_11,IDS_QUICK_11_DESC,
		{	
			{	{	{PT_SPIT_A,1,SKILL_POOR,FT_10000,IDS_UN_CAP,Q::QFD_BRIT_LONE} }	},
			{	{	{PT_ME109,1,SKILL_POOR,FT_10000,IDS_RED_CAP,Q::QFD_GERM_LONE}	}	}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_20),FIL_QUICKMISSION_25,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_CIVILIAN},
		{	{UID_CV_RAMSGATE,UID_CV_WINCHESTER,UID_CV_GUILFORD,UID_CV_OXFORD}
		},
		UID_CV_RAMSGATE
	},


//-----------------------------------------------------------------------------
//COMBAT : one on one
	{
		IDS_MISTYPE_DOGFIGHTING,IDS_QUICK_12,IDS_QUICK_12_DESC,
		{	
			{	{	{PT_SPIT_A,1,SKILL_VETERAN,FT_12000,IDS_UN_CAP,Q::QFD_BRIT_LONE} }	},
			{	{	{PT_ME109,1,SKILL_VETERAN,FT_12000,IDS_UN_CAP,Q::QFD_GERM_LONE}	}	}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_21),FIL_QUICKMISSION_21,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_CIVILIAN},
		{	{UID_CV_RAMSGATE,UID_CV_WINCHESTER,UID_CV_GUILFORD,UID_CV_OXFORD}
		},
		UID_CV_RAMSGATE
	},

//-----------------------------------------------------------------------------
//COMBAT : random adv
	{
		IDS_MISTYPE_DOGFIGHTING,IDS_QUICK_13,IDS_QUICK_13_DESC,
		{	
			{	{	{PT_SPIT_A,4,SKILL_ACE,FT_12000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }	},
			{	{	{PT_ME109,3,SKILL_ACE,FT_12000,IDS_UN_CAP,Q::QFD_GERM_FIGHTER}	}	}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_22),FIL_QUICKMISSION_22,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_CIVILIAN},
		{	{UID_CV_RAMSGATE,UID_CV_WINCHESTER,UID_CV_GUILFORD,UID_CV_OXFORD}
		},
		UID_CV_RAMSGATE
	},

//-----------------------------------------------------------------------------
//COMBAT : raf advantage
	{
		IDS_MISTYPE_DOGFIGHTING,IDS_QUICK_14,IDS_QUICK_14_DESC,
		{
			{	{	{PT_SPIT_A,4,SKILL_HERO,FT_12000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }	},
			{	{	{PT_ME109,2,SKILL_VETERAN,FT_8000,IDS_UN_CAP,Q::QFD_GERM_FIGHTER}	}	}
		},
		BLUE,0,0,0 ,
		FILDEMO(FIL_QUICKMISSION_23),FIL_QUICKMISSION_23,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_CIVILIAN},
		{	{UID_CV_RAMSGATE,UID_CV_WINCHESTER,UID_CV_GUILFORD,UID_CV_OXFORD}
		},
		UID_CV_RAMSGATE
	},

//-----------------------------------------------------------------------------
//COMBAT: lw adv
	{
		IDS_MISTYPE_DOGFIGHTING,IDS_QUICK_15,IDS_QUICK_15_DESC,
		{
			{	{	{PT_SPIT_A,3,SKILL_VETERAN,FT_8000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }	},
			{	{	{PT_ME109,3,SKILL_VETERAN,FT_12000,IDS_UN_CAP,Q::QFD_GERM_FIGHTER}	}	}
		},
		RED,0,0,0,
		FILDEMO(FIL_QUICKMISSION_24),FIL_QUICKMISSION_24,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_CIVILIAN},
		{	{UID_CV_RAMSGATE,UID_CV_WINCHESTER,UID_CV_GUILFORD,UID_CV_OXFORD}
		},
		UID_CV_RAMSGATE
	},

//-----------------------------------------------------------------------------
//GROUNDWORK : ????
//TempCode MS 25Apr00 	{
//TempCode MS 25Apr00 		IDS_MISTYPE_BOMBING,IDS_QUICK_16,IDS_QUICK_16_DESC,
//TempCode MS 25Apr00 		{	
//TempCode MS 25Apr00 			{	{	{PT_SPIT_A,2,SKILL_HERO,FT_6000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }	},
//TempCode MS 25Apr00 			{	{	{PT_DO17,4,SKILL_VETERAN,FT_5000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_AUTO} }	}
//TempCode MS 25Apr00 		},
//TempCode MS 25Apr00 		BLUE,0,0,0,
//TempCode MS 25Apr00 		FILDEMO(FIL_QUICKMISSION_25),FIL_QUICKMISSION_25,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
//TempCode MS 25Apr00 		{IDS_AIRFIELD},
//TempCode MS 25Apr00 		{	{UID_AF_Abbeville,UID_AF_Abbeville},
//TempCode MS 25Apr00 		},
//TempCode MS 25Apr00 		UID_AF_Abbeville
//TempCode MS 25Apr00 	},

//-----------------------------------------------------------------------------
//GROUNDWORK : dive bomb attack 2
	{
		IDS_MISTYPE_BOMBING,IDS_QUICK_17,IDS_QUICK_17_DESC,
		{	
			{	{	{PT_SPIT_A,4,SKILL_VETERAN,FT_6000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER+Q::QFD_ALLOW_ZERO_FL} }	},
			{	{	{PT_JU87,4,SKILL_VETERAN,FT_9000,IDS_UN_FLAK_DUTY,Q::QFD_GERM_BOMBER_PLAYER_ONLY} },	
				{	{PT_ME109,3,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL} }	}
		},
		RED,0,0,0,
		FILDEMO(FIL_QUICKMISSION_26),FIL_QUICKMISSION_26,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_RADARSTATIONS,IDS_DOCKS,IDS_AIRFIELD},
		{	{UID_CL_FairLight,UID_CL_Poling,UID_CH_Rye,UID_CL_Foreness},
			{UID_DK_Dover,UID_DK_Weymouth,UID_DK_Sheerness,UID_NB_Portland},	//MS 13Apr00
			{UID_AF_TANGMERE,UID_AF_HAWKINGE,UID_AF_EASTCHURCH,UID_AF_LYMPNE}
		},
		UID_CL_FairLight
	},

//NEED MORE QUICK_ strings in table!!!!!!!!!!!!
//-----------------------------------------------------------------------------
//GROUNDWORK : anti shipping
	{
		IDS_MISTYPE_BOMBING,IDS_QUICK_18,IDS_QUICK_18_DESC,
//DeadCode MS 20Jan00 		IDS_QUICK_5,IDS_QUICK_2,IDS_QUICK_16_DESC,
		{	
			{	{	{PT_SPIT_A,4,SKILL_VETERAN,FT_7000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER+Q::QFD_ALLOW_ZERO_FL} }	},
			{	{	{PT_JU87,4,SKILL_VETERAN,FT_9000,IDS_UN_FLAK_DUTY,Q::QFD_GERM_BOMBER_PLAYER_ONLY} },	
				{	{PT_ME109,3,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL} }	}
		},
		RED,0,0,0,
		FILDEMO(FIL_QUICKMISSION_27),FIL_QUICKMISSION_27,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_CONVOYS},
		{	{UID_CVY_G5_A,UID_CVY_G3_A,UID_CVY_G6_A,UID_CVY_G1_C},
		},
		UID_CVY_G5_A
	},

//-----------------------------------------------------------------------------
//GROUNDWORK : low level
	{
		IDS_MISTYPE_BOMBING,IDS_QUICK_19,IDS_QUICK_19_DESC,
//DeadCode MS 20Jan00 		IDS_QUICK_5,IDS_QUICK_3,IDS_QUICK_16_DESC,
		{	
			{	{	{PT_SPIT_A,2,SKILL_VETERAN,0,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }	},
			{	{	{PT_ME110,2,SKILL_VETERAN,0,IDS_UN_FB_STRIKE,Q::QFD_GERM_BOMBER_PLAYER_ONLY} }	}
		},
		RED,0,0,0,
		FILDEMO(FIL_QUICKMISSION_28),FIL_QUICKMISSION_28,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_AIRFIELD},
		{	{UID_AF_MANSTON,UID_AF_KENLEY,UID_AF_TANGMERE,UID_AF_LYMPNE}
		},
		UID_AF_MANSTON
	},

//-----------------------------------------------------------------------------
//
//INTERCEPTS : 1	LONE BOMBER
	{
		IDS_MISTYPE_INTERCEPTS,IDS_QUICK_20,IDS_QUICK_20_DESC,
//DeadCode MS 20Jan00 		IDS_QUICK_6,IDS_QUICK_4,IDS_QUICK_16_DESC,
		{	
			{	{	{PT_SPIT_A,1,SKILL_VETERAN,FT_11000,IDS_RED_CAP,Q::QFD_BRIT_LONE} }	},
			{	{	{PT_DO17,1,SKILL_VETERAN,FT_10000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_NUM_PLAYER} } }	
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_29),FIL_QUICKMISSION_29,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_AIRFIELD,IDS_DOCKS,IDS_LONDON},
		{	{UID_AF_DEBDEN,UID_AF_KENLEY,UID_AF_BIGGINHILL,UID_AF_HORNCHURCH},
			{UID_DK_Southampton,UID_DK_Dover,UID_DK_Plymouth,UID_NB_Portland},
			{UID_DK_WestIndia,UID_DK_Limehouse,UID_DK_Millwall,UID_AF_GRAVESEND},
		},
		UID_AF_DEBDEN
	},
//-----------------------------------------------------------------------------
//INTERCEPTS : 2 close escort
//Close Escort + High Escort - RAF comes in from front 2 sqds in formation
	{
		IDS_MISTYPE_INTERCEPTS,IDS_QUICK_21,IDS_QUICK_21_DESC,
//DeadCode MS 20Jan00 		IDS_QUICK_6,IDS_QUICK_4,IDS_QUICK_16_DESC,
		{	
			{	{	{PT_HURR_A,4,SKILL_VETERAN,FT_12000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER}	},
				{	{PT_SPIT_A,4,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_BRIT_FIGHTER+Q::QFD_ALLOW_ZERO_FL}	}	
			},
			{	{	{PT_DO17,4,SKILL_VETERAN,FT_10000,IDS_UN_FB_STRIKE,Q::QFD_GERM_BOMBER_AUTO_ONLY}	},
				{	{PT_ME109,3,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL}	}, 
				{	{PT_ME109,3,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL} }
			}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_30),FIL_QUICKMISSION_30,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_AIRFIELD,IDS_DOCKS,IDS_LONDON,IDS_FACTORIES},
//WARNING PUT THIS BACK											//MS 08May00
//DeadCode MS 28Jun00 		{	{UID_AF_DEBDEN,UID_AF_HAWKINGE,UID_AF_KENLEY,UID_AF_BIGGINHILL},
//DeadCode MS 28Jun00 			{UID_AF_NORTHWEALD,UID_AF_NORTHOLT,UID_FA_ShortsBros,UID_FA_Pobjoy},
		{	{UID_AF_DEBDEN,UID_AF_KENLEY,UID_AF_BIGGINHILL,UID_AF_HORNCHURCH},
			{UID_DK_Southampton,UID_DK_Dover,UID_DK_Plymouth,UID_NB_Portland},
			{UID_DK_WestIndia,UID_DK_Limehouse,UID_DK_Millwall,UID_AF_GRAVESEND},
			{UID_FA_BrooklandsVickers,UID_FA_Westland,UID_FA_LangleyHawker,UID_FA_BoultonPaul},
		},
		UID_AF_DEBDEN
	},

//-----------------------------------------------------------------------------
//INTERCEPTS : 3 close escort
//Close Escort + High Escort - RAF comes in from behind 2 sqds in formation
	{
		IDS_MISTYPE_INTERCEPTS,IDS_QUICK_22,IDS_QUICK_22_DESC,
//DeadCode MS 20Jan00 		IDS_QUICK_6,IDS_QUICK_17,IDS_QUICK_16_DESC,
		{	
			{	{	{PT_HURR_A,4,SKILL_VETERAN,FT_12000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER}	},
				{	{PT_SPIT_A,4,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_BRIT_FIGHTER+Q::QFD_ALLOW_ZERO_FL}	}	
			},
			{	{	{PT_DO17,4,SKILL_VETERAN,FT_10000,IDS_UN_FB_STRIKE,Q::QFD_GERM_BOMBER_AUTO_ONLY}	},
				{	{PT_ME109,3,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL}	}, 
				{	{PT_ME109,3,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL}	} 
			}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_31),FIL_QUICKMISSION_31,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_AIRFIELD,IDS_DOCKS,IDS_LONDON,IDS_FACTORIES},
		{	{UID_AF_DEBDEN,UID_AF_KENLEY,UID_AF_BIGGINHILL,UID_AF_HORNCHURCH},
			{UID_DK_Southampton,UID_DK_Dover,UID_DK_Plymouth,UID_NB_Portland},
			{UID_DK_WestIndia,UID_DK_Limehouse,UID_DK_Millwall,UID_AF_GRAVESEND},
			{UID_FA_BrooklandsVickers,UID_FA_Westland,UID_FA_LangleyHawker,UID_FA_BoultonPaul}
		},
		UID_AF_DEBDEN
	},

//-----------------------------------------------------------------------------
//INTERCEPTS : 4
//scattered loose escort
	{
		IDS_MISTYPE_INTERCEPTS,IDS_QUICK_23,IDS_QUICK_23_DESC,
//DeadCode MS 20Jan00 		IDS_QUICK_6,IDS_QUICK_17,IDS_QUICK_16_DESC,
		{	
			{	{	{PT_HURR_A,4,SKILL_VETERAN,FT_12000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER}	},
				{	{PT_SPIT_A,4,SKILL_VETERAN,FT_12000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER+Q::QFD_ALLOW_ZERO_FL}	}
			},
			{	{	{PT_DO17,4,SKILL_VETERAN,FT_10000,IDS_UN_FB_STRIKE,Q::QFD_GERM_BOMBER_AUTO_ONLY}	},
				{	{PT_ME109,3,SKILL_VETERAN,FT_11000,IDS_UN_ESCORT_DUTY,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL}	}, 
				{	{PT_ME109,3,SKILL_VETERAN,FT_12000,IDS_UN_ESCORT_DUTY,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL} }
			}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_32),FIL_QUICKMISSION_32,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_AIRFIELD,IDS_DOCKS,IDS_LONDON,IDS_FACTORIES},
		{	{UID_AF_DEBDEN,UID_AF_KENLEY,UID_AF_BIGGINHILL,UID_AF_HORNCHURCH},
			{UID_DK_Southampton,UID_DK_Dover,UID_DK_Plymouth,UID_NB_Portland},
			{UID_DK_WestIndia,UID_DK_Limehouse,UID_DK_Millwall,UID_AF_GRAVESEND},
			{UID_FA_BrooklandsVickers,UID_FA_Westland,UID_FA_LangleyHawker,UID_FA_BoultonPaul}
		},
		UID_AF_DEBDEN
	},

//-----------------------------------------------------------------------------
//INTERCEPTS : 5
//TempCode MS 25Apr00 	{
//TempCode MS 25Apr00 		IDS_MISTYPE_INTERCEPTS,IDS_QUICK_24,IDS_QUICK_24_DESC,
//TempCode MS 25Apr00 //DeadCode MS 20Jan00 		IDS_QUICK_6,IDS_QUICK_17,IDS_QUICK_16_DESC,
//TempCode MS 25Apr00 		{	
//TempCode MS 25Apr00 			{	{	{PT_SPIT_A,2,SKILL_HERO,FT_6000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }	},
//TempCode MS 25Apr00 			{	{	{PT_DO17,4,SKILL_VETERAN,FT_5000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_AUTO} }	}
//TempCode MS 25Apr00 		},
//TempCode MS 25Apr00 		BLUE,0,0,0,
//TempCode MS 25Apr00 		FILDEMO(FIL_QUICKMISSION_33),FIL_QUICKMISSION_33,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
//TempCode MS 25Apr00 		{IDS_AIRFIELD},
//TempCode MS 25Apr00 		{	{UID_AF_Abbeville,UID_AF_Abbeville},
//TempCode MS 25Apr00 		},
//TempCode MS 25Apr00 		UID_AF_Abbeville
//TempCode MS 25Apr00 	},

//-----------------------------------------------------------------------------
//INTERCEPTS : 6
//TempCode MS 25Apr00 	{
//TempCode MS 25Apr00 		IDS_MISTYPE_INTERCEPTS,IDS_QUICK_25,IDS_QUICK_25_DESC,
//TempCode MS 25Apr00 //DeadCode MS 20Jan00 		IDS_QUICK_6,IDS_QUICK_17,IDS_QUICK_16_DESC,
//TempCode MS 25Apr00 		{	
//TempCode MS 25Apr00 			{	{	{PT_SPIT_A,2,SKILL_HERO,FT_6000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }	},
//TempCode MS 25Apr00 			{	{	{PT_DO17,4,SKILL_VETERAN,FT_5000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_AUTO} }	}
//TempCode MS 25Apr00 		},
//TempCode MS 25Apr00 		BLUE,0,0,0,
//TempCode MS 25Apr00 		FILDEMO(FIL_QUICKMISSION_34),FIL_QUICKMISSION_34,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
//TempCode MS 25Apr00 		{IDS_AIRFIELD},
//TempCode MS 25Apr00 		{	{UID_AF_Abbeville,UID_AF_Abbeville},
//TempCode MS 25Apr00 		},
//TempCode MS 25Apr00 		UID_AF_Abbeville
//TempCode MS 25Apr00 	},

//-----------------------------------------------------------------------------
//HISTORIC : 1	Defiant End
	{
		IDS_MISTYPE_HISTORIC,IDS_QUICK_26,IDS_QUICK_26_DESC,
//DeadCode MS 20Jan00 		IDS_QUICK_7,IDS_QUICK_2,IDS_QUICK_16_DESC,
		{	
			{	{	{PT_HURR_A,4,SKILL_REGULAR,FT_6000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} } 	,			
				{	{PT_DEFIANT,4,SKILL_REGULAR,FT_5000,IDS_UN_CAP,Q::QFD_BRIT_BOMBER_AUTO_ONLY} } },
			{	{	{PT_ME109,3,SKILL_VETERAN,FT_7000,IDS_UN_CAP,Q::QFD_GERM_FIGHTER} }	}
		},
		RED,0,0,0,
		FILDEMO(FIL_QUICKMISSION_35),FIL_QUICKMISSION_35,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_CIVILIAN},
		{	{UID_CV_FOLKESTONE},
		},
		UID_CV_FOLKESTONE
	},

//DeadCode MS 05Jul00 //-----------------------------------------------------------------------------
//DeadCode MS 05Jul00 //HISTORIC : 2	AlderTag morning
//DeadCode MS 05Jul00 
//DeadCode MS 05Jul00 
//DeadCode MS 05Jul00 	{
//DeadCode MS 05Jul00 		IDS_MISTYPE_HISTORIC,IDS_QUICK_27,IDS_QUICK_27_DESC,
//DeadCode MS 05Jul00 //DeadCode MS 20Jan00 		IDS_QUICK_7,IDS_QUICK_17,IDS_QUICK_16_DESC,
//DeadCode MS 05Jul00 		{	
//DeadCode MS 05Jul00 			{	{	{PT_SPIT_A,2,SKILL_HERO,FT_6000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }	},
//DeadCode MS 05Jul00 			{	{	{PT_DO17,4,SKILL_VETERAN,FT_5000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_AUTO} }	}
//DeadCode MS 05Jul00 		},
//DeadCode MS 05Jul00 		BLUE,0,0,0,
//DeadCode MS 05Jul00 		FILDEMO(FIL_QUICKMISSION_36),FIL_QUICKMISSION_36,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
//DeadCode MS 05Jul00 		{IDS_AIRFIELD},
//DeadCode MS 05Jul00 		{	{UID_AF_Abbeville,UID_AF_Abbeville},
//DeadCode MS 05Jul00 		},
//DeadCode MS 05Jul00 		UID_AF_Abbeville
//DeadCode MS 05Jul00 	},

//-----------------------------------------------------------------------------
//HISTORIC : 3 	Aldertag Afternoon
	{
		IDS_MISTYPE_HISTORIC,IDS_QUICK_28,IDS_QUICK_28_DESC,
//DeadCode MS 20Jan00 		IDS_QUICK_7,IDS_QUICK_17,IDS_QUICK_16_DESC,
		{	
			{	
				{	{PT_SPIT_A,4,SKILL_VETERAN,FT_12000,IDS_UID_NB_Portland,Q::QFD_BRIT_FIGHTER} },
				{	{PT_HURR_A,4,SKILL_VETERAN,FT_12000,IDS_UID_NB_Portland,Q::QFD_BRIT_FIGHTER} },
				{	{PT_SPIT_B,4,SKILL_VETERAN,FT_12000,IDS_UID_AF_MIDDLEWALLOP,Q::QFD_BRIT_FIGHTER} },
				{	{PT_HURR_B,4,SKILL_VETERAN,FT_12000,IDS_UID_DK_Southampton,Q::QFD_BRIT_FIGHTER} }
			},
			{	
				{	{PT_JU88,3,SKILL_VETERAN,FT_12000,IDS_UID_NB_Portland,Q::QFD_GERM_BOMBER_AUTO_ONLY}	},
				{	{PT_ME110,3,SKILL_VETERAN,FT_14000,IDS_UID_NB_Portland,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL}	},
				{	{PT_JU88,3,SKILL_VETERAN,FT_12000,IDS_UID_DK_Southampton,Q::QFD_GERM_BOMBER_AUTO_ONLY}	},
				{	{PT_JU87,4,SKILL_VETERAN,FT_8000,IDS_UID_AF_MIDDLEWALLOP,Q::QFD_GERM_BOMBER_PLAYER_ONLY}	}
			}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_37),FIL_QUICKMISSION_37,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_DOCKS},
		{	{UID_DK_Southampton},
		},
		UID_DK_Southampton
	},

//DeadCode MS 05Jul00 //-----------------------------------------------------------------------------
//DeadCode MS 05Jul00 //HISTORIC : 4	BIG WING BATTLE OF BRITAIN DAY
//DeadCode MS 05Jul00 	{
//DeadCode MS 05Jul00 		IDS_MISTYPE_HISTORIC,IDS_QUICK_29,IDS_QUICK_29_DESC,
//DeadCode MS 05Jul00 		{	
//DeadCode MS 05Jul00 			{	
//DeadCode MS 05Jul00 				{	{PT_HURR_A,4,SKILL_HERO,FT_10000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER}
//DeadCode MS 05Jul00 				},
//DeadCode MS 05Jul00 				{	{PT_HURR_B,4,SKILL_HERO,FT_14000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER},
//DeadCode MS 05Jul00 					{PT_SPIT_B,4,SKILL_HERO,FT_20000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER+Q::QFD_ALLOW_ZERO_FL}
//DeadCode MS 05Jul00 				},
//DeadCode MS 05Jul00 			},
//DeadCode MS 05Jul00 			//GERMANS
//DeadCode MS 05Jul00 			{	
//DeadCode MS 05Jul00 				{	{PT_DO17,3,SKILL_VETERAN,FT_10000,IDS_UN_FB_STRIKE,Q::QFD_GERM_BOMBER_AUTO_ONLY},
//DeadCode MS 05Jul00 					{PT_DO17,3,SKILL_VETERAN,FT_11000,IDS_UN_FB_STRIKE,Q::QFD_GERM_BOMBER_AUTO_ONLY+Q::QFD_ALLOW_ZERO_FL},
//DeadCode MS 05Jul00 					{PT_ME109,3,SKILL_ACE,FT_10000,IDS_RED_CAP,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL}		
//DeadCode MS 05Jul00 				}
//DeadCode MS 05Jul00 
//DeadCode MS 05Jul00 //TempCode MS 27Mar00 				{	
//DeadCode MS 05Jul00 //TempCode MS 27Mar00 					{PT_DO17,3,SKILL_ACE,FT_6000,IDS_RED_CAP,Q::QFD_FIXED_AUTO},	
//DeadCode MS 05Jul00 //TempCode MS 27Mar00 					{PT_DO17,3,SKILL_ACE,FT_6000,IDS_RED_CAP,Q::QFD_FIXED_AUTO},
//DeadCode MS 05Jul00 //TempCode MS 27Mar00  					{PT_DO17,3,SKILL_ACE,FT_6000,IDS_RED_CAP,Q::QFD_FIXED_AUTO}
//DeadCode MS 05Jul00 //TempCode MS 27Mar00 				}
//DeadCode MS 05Jul00 			}
//DeadCode MS 05Jul00 		},
//DeadCode MS 05Jul00 		BLUE,0,0,0,
//DeadCode MS 05Jul00 		FILDEMO(FIL_QUICKMISSION_38),FIL_QUICKMISSION_38,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
//DeadCode MS 05Jul00 		{IDS_DOCKS},
//DeadCode MS 05Jul00 		{	{UID_DK_WestIndia,UID_AF_GRAVESEND,UID_AF_MANSTON},
//DeadCode MS 05Jul00 		},
//DeadCode MS 05Jul00 		UID_DK_WestIndia
//DeadCode MS 05Jul00 	},

//DeadCode MS 05Jul00 //-----------------------------------------------------------------------------
//DeadCode MS 05Jul00 //HISTORIC : 5	Afternoon
//DeadCode MS 05Jul00 	{
//DeadCode MS 05Jul00 		IDS_MISTYPE_HISTORIC,IDS_QUICK_30,IDS_QUICK_30_DESC,
//DeadCode MS 05Jul00 //DeadCode MS 20Jan00 		IDS_QUICK_7,IDS_QUICK_17,IDS_QUICK_16_DESC,
//DeadCode MS 05Jul00 		{	
//DeadCode MS 05Jul00 			{	{	{PT_SPIT_A,2,SKILL_HERO,FT_6000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }	},
//DeadCode MS 05Jul00 			{	{	{PT_JU88,4,SKILL_VETERAN,FT_5000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_AUTO} }	}
//DeadCode MS 05Jul00 		},
//DeadCode MS 05Jul00 		BLUE,0,0,0,
//DeadCode MS 05Jul00 		FILDEMO(FIL_QUICKMISSION_39),FIL_QUICKMISSION_39,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
//DeadCode MS 05Jul00 		{IDS_AIRFIELD},
//DeadCode MS 05Jul00 		{	{UID_AF_Abbeville,UID_AF_Abbeville},
//DeadCode MS 05Jul00 		},
//DeadCode MS 05Jul00 		UID_AF_Abbeville
//DeadCode MS 05Jul00 	},


//-----------------------------------------------------------------------------
//HISTORIC : 7 Black Thursday Morning
	{
		IDS_MISTYPE_HISTORIC,IDS_QUICK_32,IDS_QUICK_32_DESC,
		{	
			{	
				{	{PT_HURR_A,4,SKILL_REGULAR,FT_5000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} },
				{	{PT_SPIT_A,4,SKILL_REGULAR,FT_10000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} } 
			},			
			{	
				{	{PT_JU87,3,SKILL_REGULAR,FT_7000,IDS_UN_FLAK_DUTY,Q::QFD_GERM_BOMBER_PLAYER_ONLY} },
				{	{PT_ME109,3,SKILL_REGULAR,FT_14000,IDS_UN_CAP,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL} },
				{	{PT_JU87,3,SKILL_REGULAR,FT_7000,IDS_UN_FLAK_DUTY,Q::QFD_GERM_BOMBER_PLAYER_ONLY} },
				{	{PT_ME109,3,SKILL_REGULAR,FT_14000,IDS_UN_CAP,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL} }
			},
		},
		RED,0,0,0,
		FILDEMO(FIL_QUICKMISSION_41),FIL_QUICKMISSION_41,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_AIRFIELD},
		{	{UID_AF_HAWKINGE},
		},
		UID_AF_HAWKINGE
	},

//-----------------------------------------------------------------------------
//HISTORIC : 8 Black Thursday Afternoon 15th AUG
	{
		IDS_MISTYPE_HISTORIC,IDS_QUICK_33,IDS_QUICK_33_DESC,
		{	
			{	{	{PT_SPIT_A,4,SKILL_VETERAN,FT_18000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} },
				{	{PT_HURR_A,4,SKILL_VETERAN,FT_16000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER+Q::QFD_ALLOW_ZERO_FL} },
				{	{PT_HURR_B,4,SKILL_VETERAN,FT_16000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER+Q::QFD_ALLOW_ZERO_FL} }
			},
			{	{	{PT_DO17,3,SKILL_VETERAN,FT_15000,IDS_UN_FB_STRIKE,Q::QFD_GERM_BOMBER_AUTO_ONLY} },
				{	{PT_ME109,3,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL} },
				{	{PT_DO17,3,SKILL_VETERAN,FT_16000,IDS_UN_FB_STRIKE,Q::QFD_GERM_BOMBER_AUTO_ONLY} },
				{	{PT_ME109,3,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL} }
			}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_42),FIL_QUICKMISSION_42,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_TT_INDUSTRY},
		{	{UID_IN_Faversham}
		},
		UID_IN_Faversham
	},

//-----------------------------------------------------------------------------
//DeadCode MS 06Jul00 //HISTORIC : 6	Malan Vs Molders	Pg176 fighter hardback   196 b over b
//HISTORIC : 6	September 9th
	{
//DeadCode MS 06Jul00 		IDS_MISTYPE_HISTORIC,IDS_QUICK_31,IDS_QUICK_31_DESC,
//DeadCode MS 06Jul00 //DeadCode MS 20Jan00 		IDS_QUICK_7,IDS_QUICK_17,IDS_QUICK_16_DESC,
//DeadCode MS 06Jul00 		{	
//DeadCode MS 06Jul00 			{	{	{PT_SPIT_A,3,SKILL_HERO,FT_8000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} },
//DeadCode MS 06Jul00 				{	{PT_HURR_A,3,SKILL_HERO,FT_6000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} },	
//DeadCode MS 06Jul00 				{	{PT_HURR_B,3,SKILL_HERO,FT_6000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }
//DeadCode MS 06Jul00 			},
//DeadCode MS 06Jul00 			//GERMANS
//DeadCode MS 06Jul00 			{	
//DeadCode MS 06Jul00 //DeadCode MS 24Mar00 				{	{PT_JU88,3,SKILL_VETERAN,FT_5000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_AUTO},
//DeadCode MS 06Jul00 //DeadCode MS 24Mar00  					{PT_JU88,3,SKILL_VETERAN,FT_5000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_AUTO},
//DeadCode MS 06Jul00 //DeadCode MS 24Mar00 					{PT_JU88,3,SKILL_VETERAN,FT_5000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_AUTO}
//DeadCode MS 06Jul00 //DeadCode MS 24Mar00 				},
//DeadCode MS 06Jul00 //TempCode MS 24Mar00 				//Bomber 2
//DeadCode MS 06Jul00 //TempCode MS 24Mar00 				{	{PT_JU88,3,SKILL_VETERAN,FT_5000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_AUTO},
//DeadCode MS 06Jul00 //TempCode MS 24Mar00 					{PT_JU88,3,SKILL_VETERAN,FT_5000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_AUTO}
//DeadCode MS 06Jul00 //TempCode MS 24Mar00 				},
//DeadCode MS 06Jul00 				//JG 51, I, 
//DeadCode MS 06Jul00 				{	{PT_ME109,3,SKILL_ACE,FT_6000,IDS_RED_CAP,Q::QFD_GERM_FIGHTER},	
//DeadCode MS 06Jul00 					{PT_ME109,3,SKILL_ACE,FT_6000,IDS_RED_CAP,Q::QFD_GERM_FIGHTER} 
//DeadCode MS 06Jul00 				},
//DeadCode MS 06Jul00 				//JG 51, II, 
//DeadCode MS 06Jul00 				{	{PT_ME109,3,SKILL_ACE,FT_6000,IDS_RED_CAP,Q::QFD_GERM_FIGHTER},	
//DeadCode MS 06Jul00 					{PT_ME109,3,SKILL_ACE,FT_6000,IDS_RED_CAP,Q::QFD_GERM_FIGHTER} 
//DeadCode MS 06Jul00 				}
//DeadCode MS 06Jul00 			}
//DeadCode MS 06Jul00 		},
//DeadCode MS 06Jul00 		BLUE,0,0,0,
//DeadCode MS 06Jul00 		FILDEMO(FIL_QUICKMISSION_40),FIL_QUICKMISSION_40,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
//DeadCode MS 06Jul00 		{IDS_DOCKS},
//DeadCode MS 06Jul00 		{	{UID_DK_Dover},
//DeadCode MS 06Jul00 		},
//DeadCode MS 06Jul00 		UID_DK_Dover
//DeadCode MS 06Jul00 	},

		IDS_MISTYPE_HISTORIC,IDS_QUICK_31,IDS_QUICK_31_DESC,
		{	
			{	{	{PT_HURR_A,4,SKILL_VETERAN,FT_12000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER}	}, 
				{	{PT_SPIT_A,4,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_BRIT_FIGHTER}	},
				{	{PT_HURR_B,4,SKILL_VETERAN,FT_15000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER}	}, 
				{	{PT_SPIT_B,4,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_BRIT_FIGHTER}	}
			},
			//GERMANS
			{	
				{	{PT_HE111,3,SKILL_VETERAN,FT_12000,IDS_UN_FB_STRIKE,Q::QFD_GERM_BOMBER_AUTO_ONLY}	},
 				{	{PT_ME110,3,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_GERM_FIGHTER}	},
				{	{PT_ME109,3,SKILL_VETERAN,0,IDS_UN_ESCORT_DUTY,Q::QFD_GERM_FIGHTER}	},
				{	{PT_JU88,3,SKILL_VETERAN,FT_12000,IDS_UN_FB_STRIKE,Q::QFD_GERM_BOMBER_AUTO_ONLY}}
			}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_40),FIL_QUICKMISSION_40,0,3,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_TT_INDUSTRY},
		{	{UID_FA_Farnborough},
		},
		UID_FA_Farnborough
	},

//-----------------------------------------------------------------------------
//HISTORIC : 4	BIG WING BATTLE OF BRITAIN DAY
	{
		IDS_MISTYPE_HISTORIC,IDS_QUICK_29,IDS_QUICK_29_DESC,
		{	
			{	
				{	{PT_HURR_A,4,SKILL_ACE,FT_10000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER}	},
				{	{PT_HURR_B,4,SKILL_ACE,FT_14000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER}	},
				{	{PT_SPIT_B,4,SKILL_ACE,FT_20000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER+Q::QFD_ALLOW_ZERO_FL}	}
			},
			//GERMANS
			{	
				{	{PT_DO17,3,SKILL_VETERAN,FT_10000,IDS_UN_FB_STRIKE,Q::QFD_GERM_BOMBER_AUTO_ONLY}	},
				{	{PT_DO17,3,SKILL_VETERAN,FT_11000,IDS_UN_FB_STRIKE,Q::QFD_GERM_BOMBER_AUTO_ONLY}	},
				{	{PT_ME109,3,SKILL_ACE,0,IDS_UN_ESCORT_DUTY,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL}	}	

//TempCode MS 27Mar00 				{	
//TempCode MS 27Mar00 					{PT_DO17,3,SKILL_ACE,FT_6000,IDS_RED_CAP,Q::QFD_FIXED_AUTO},	
//TempCode MS 27Mar00 					{PT_DO17,3,SKILL_ACE,FT_6000,IDS_RED_CAP,Q::QFD_FIXED_AUTO},
//TempCode MS 27Mar00  					{PT_DO17,3,SKILL_ACE,FT_6000,IDS_RED_CAP,Q::QFD_FIXED_AUTO}
//TempCode MS 27Mar00 				}
			}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_38),FIL_QUICKMISSION_38,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_DOCKS},
		{	{UID_DK_WestIndia},
		},
		UID_DK_WestIndia
	},

//-----------------------------------------------------------------------------
//AFTER THIS POINT, ALL DEBUG, NOT FINAL VERSION
//-----------------------------------------------------------------------------
#ifndef NDEBUG
//FIRST CONFIGIGNORED IS USED AS HOTSHOT
//-----------------------------------------------------------------------------
//OOPS USE TO BE HOTSHOT!!!!!!	//FIRST CONFIG IGNORED IS HOTSHOT!!!
//USE THIS ONe to test formations
	{
		IDS_CONFIGIGNORED,IDS_HOTSHOT,IDS_CONFIGIGNORED,
		{	
			{	{	{PT_SPIT_A,4,SKILL_HERO,FT_18000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} },
				{	{PT_HURR_A,4,SKILL_HERO,FT_16000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER+Q::QFD_ALLOW_ZERO_FL} }
			},
			{	{	{PT_DO17,3,SKILL_VETERAN,FT_15000,IDS_UN_FB_STRIKE,Q::QFD_GERM_BOMBER_AUTO_ONLY} },
				{	{PT_DO17,3,SKILL_VETERAN,FT_16000,IDS_UN_FB_STRIKE,Q::QFD_GERM_BOMBER_AUTO_ONLY} },
				{	{PT_ME109,3,SKILL_VETERAN,FT_17000,IDS_UN_CAP,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL} },
				{	{PT_ME109,3,SKILL_VETERAN,FT_18000,IDS_UN_CAP,Q::QFD_GERM_FIGHTER+Q::QFD_ALLOW_ZERO_FL} }
			}
		},
		BLUE,0,1,0,
		FILDEMO(FIL_HOTSHOT),FIL_HOTSHOT,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_AIRFIELD},
		{	{UID_DK_Southampton,UID_HS_HOUSESPARLIAMENT,UID_DK_Weymouth,UID_AF_PEMBREY}
		},
		UID_AF_Abbeville
	},
//-----------------------------------------------------------------------------
//HISTORIC : 2	AlderTag morning


	{
		IDS_CONFIGIGNORED,IDS_QUICK_27,IDS_QUICK_27_DESC,
//DeadCode MS 20Jan00 		IDS_QUICK_7,IDS_QUICK_17,IDS_QUICK_16_DESC,
		{	
			{	{	{PT_SPIT_A,2,SKILL_HERO,FT_6000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }	},
			{	{	{PT_DO17,4,SKILL_VETERAN,FT_5000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_AUTO} }	}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_36),FIL_QUICKMISSION_36,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_AIRFIELD},
		{	{UID_AF_Abbeville,UID_AF_Abbeville},
		},
		UID_AF_Abbeville
	},

//-----------------------------------------------------------------------------
//HISTORIC : 5	Afternoon
	{
		IDS_CONFIGIGNORED,IDS_QUICK_30,IDS_QUICK_30_DESC,
//DeadCode MS 20Jan00 		IDS_QUICK_7,IDS_QUICK_17,IDS_QUICK_16_DESC,
		{	
			{	{	{PT_SPIT_A,2,SKILL_HERO,FT_6000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }	},
			{	{	{PT_JU88,4,SKILL_VETERAN,FT_5000,IDS_UN_FB_STRIKE,Q::QFD_FIXED_AUTO} }	}
		},
		BLUE,0,0,0,
		FILDEMO(FIL_QUICKMISSION_39),FIL_QUICKMISSION_39,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{IDS_AIRFIELD},
		{	{UID_AF_Abbeville,UID_AF_Abbeville},
		},
		UID_AF_Abbeville
	},


//-----------------------------------------------------------------------------

//Mark Test 
	{
		IDS_CONFIGIGNORED,IDS_QUICK_11,IDS_QUICK_11,
		{	
			{	{	{PT_SPIT_A,1,SKILL_VETERAN,FT_2000,IDS_UN_CAP,Q::QFD_BRIT_FIGHTER} }	},
		},
		BLUE,0,0,0,
		FILDEMO(FIL_AFBUZZ00),FIL_AFBUZZ00,0,2,  //currmissnum, altmissnum, weather,time//RDH 27Mar00
		{ IDS_CONFIGIGNORED,IDS_CIVILIAN,IDS_AIRFIELD,IDS_DOCKS},
		{	{UID_HS_HOUSESPARLIAMENT,UID_AF_GRAVESEND},
			{UID_AF_NORTHWEALD,UID_AF_GRAVESEND},
			{UID_HS_HOUSESPARLIAMENT,UID_AF_GRAVESEND}
		},
		UID_AF_GRAVESEND
	},

//-----------------------------------------------------------------------------


//DEADCODE DAW 19/11/99 //IAN 2
//DEADCODE DAW 19/11/99 	{
//DEADCODE DAW 19/11/99 		IDS_AIRFIELD,IDS_AIRFIELD,
//DEADCODE DAW 19/11/99 		{	
//DEADCODE DAW 19/11/99 			{	{	{PT_BLEN,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} }	},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		BLUE,0,0,0,
//DEADCODE DAW 19/11/99 		FILDEMO(FIL_QUICKMISSION_17),FIL_QUICKMISSION_17,0,0,
//DEADCODE DAW 19/11/99 		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
//DEADCODE DAW 19/11/99 		{	{UID_AfRdPyongyangE,UID_AfRdPyongyangM,UID_AfRdPyongyangD,UID_AfBlKimpo},
//DEADCODE DAW 19/11/99 			{UID_AfBlSeoul,UID_AfBlChuncheon,UID_AfBlOsan,UID_AfBlSuwon},
//DEADCODE DAW 19/11/99 			{UID_AfBlPyongtaek,UID_AfBlKunsan,UID_AfBlTaejon,UID_AfBlTaegu},
//DEADCODE DAW 19/11/99 			{UID_AfBlTaeguW,UID_AfBlKangnung,UID_AfBlPohang,UID_StKimchon},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		UID_NODE_sinuiju
//DEADCODE DAW 19/11/99 	},
//DEADCODE DAW 19/11/99 //AMANDA 1
//DEADCODE DAW 19/11/99 	{
//DEADCODE DAW 19/11/99 		IDS_CIVILIAN,IDS_CIVILIAN,
//DEADCODE DAW 19/11/99 		{	
//DEADCODE DAW 19/11/99 			{	{	{PT_BLEN,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} }	},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		BLUE,0,0,0,
//DEADCODE DAW 19/11/99 		FILDEMO(FIL_QUICKMISSION_17),FIL_QUICKMISSION_17,0,0,
//DEADCODE DAW 19/11/99 		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
//DEADCODE DAW 19/11/99 			{	{UID_MyRlChongjin,UID_MSPKimchaek,UID_MSPKimchaek,UID_MyRdHamhung},
//DEADCODE DAW 19/11/99 			{UID_StKowon,UID_MyRlWonsan,UID_StKumhwa,UID_StChorwon},
//DEADCODE DAW 19/11/99 			{UID_SdRdPyonggang,UID_SdRdIchon,UID_SdRdKaesong,UID_StPyongsan},
//DEADCODE DAW 19/11/99 			{UID_SdRdKumchon,UID_ICMPNampo,UID_MyRdPyongyang,UID_WhRdSukchon},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		UID_NODE_sinuiju
//DEADCODE DAW 19/11/99 	},
//DEADCODE DAW 19/11/99 //AMANDA 2
//DEADCODE DAW 19/11/99 	{
//DEADCODE DAW 19/11/99 		IDS_TOWN,IDS_TOWN,
//DEADCODE DAW 19/11/99 		{	
//DEADCODE DAW 19/11/99 			{	{	{PT_BLEN,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} }	},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		BLUE,0,0,0,
//DEADCODE DAW 19/11/99 		FILDEMO(FIL_QUICKMISSION_17),FIL_QUICKMISSION_17,0,0,
//DEADCODE DAW 19/11/99 		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
//DEADCODE DAW 19/11/99 		{	{UID_StSunchon,UID_StKangdong,UID_StYangdok,UID_SdRdSonchon},
//DEADCODE DAW 19/11/99 			{UID_SCCYomju,UID_WhRdDangDong,UID_SCCHuichon,UID_SCCChosan},
//DEADCODE DAW 19/11/99 			{UID_SCCKangye,UID_SCCManpo,UID_SdRdYangyang,UID_MyBlMunsan},
//DEADCODE DAW 19/11/99 			{UID_MyBlSeoul,UID_SdBlSuwon,UID_StInchon,UID_StOsan},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		UID_NODE_sinuiju
//DEADCODE DAW 19/11/99 	},
//DEADCODE DAW 19/11/99 //AMANDA 3
//DEADCODE DAW 19/11/99 	{
//DEADCODE DAW 19/11/99 		IDS_CIVILIAN,IDS_CIVILIAN,
//DEADCODE DAW 19/11/99 		{	
//DEADCODE DAW 19/11/99 			{	{	{PT_BLEN,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} }	},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		BLUE,0,0,0,
//DEADCODE DAW 19/11/99 		FIL_QUICKMISSION_17,FIL_QUICKMISSION_17,0,0,
//DEADCODE DAW 19/11/99 		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
//DEADCODE DAW 19/11/99 		{	{UID_SdBlPyongtaek,UID_StChonan,UID_MyBlChochiwon,UID_SdBlTaejon},
//DEADCODE DAW 19/11/99 			{UID_MyBlKuri,UID_StChuncheon,UID_SdRdHongchon,UID_StHoensong},
//DEADCODE DAW 19/11/99 			{UID_SdRdWonju,UID_StChungju,UID_StSamchok, UID_StYulchon},
//DEADCODE DAW 19/11/99 			{UID_StKusong,UID_StChomchon,UID_StChongju,UID_StChongju},//MS 02May99
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		UID_NODE_sinuiju
//DEADCODE DAW 19/11/99 	},
//DEADCODE DAW 19/11/99 //AMANDA 4
//DEADCODE DAW 19/11/99 	{
//DEADCODE DAW 19/11/99 		IDS_TOWN,IDS_TOWN,
//DEADCODE DAW 19/11/99 		{	
//DEADCODE DAW 19/11/99 			{	{	{PT_BLEN,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} }	},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		BLUE,0,0,0,
//DEADCODE DAW 19/11/99 		FIL_QUICKMISSION_17,FIL_QUICKMISSION_17,0,0,
//DEADCODE DAW 19/11/99 		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
//DEADCODE DAW 19/11/99 		{	{UID_StKujang,UID_StSariwon,UID_StYulLi,UID_StPungsan},
//DEADCODE DAW 19/11/99 			{UID_StKangnung,UID_StHwachon,UID_StYangpyong,UID_StYonchon},
//DEADCODE DAW 19/11/99 			{UID_StUijongbu,UID_StSongnam,UID_MyBlKuri,UID_StKuri},
//DEADCODE DAW 19/11/99 			{UID_StSinanju,UID_StPukchong,UID_StKilchu,UID_StKimchon},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		UID_NODE_sinuiju
//DEADCODE DAW 19/11/99 	},
//DEADCODE DAW 19/11/99 //AMANDA 5
//DEADCODE DAW 19/11/99 	{
//DEADCODE DAW 19/11/99 		IDS_CIVILIAN,IDS_CIVILIAN,
//DEADCODE DAW 19/11/99 		{	
//DEADCODE DAW 19/11/99 			{	{	{PT_BLEN,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} }	},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		BLUE,0,0,0,
//DEADCODE DAW 19/11/99 		FIL_QUICKMISSION_17,FIL_QUICKMISSION_17,0,0,
//DEADCODE DAW 19/11/99 		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
//DEADCODE DAW 19/11/99 		{	{UID_StAndong,UID_StUisong,UID_StChechon,UID_StKanda},
//DEADCODE DAW 19/11/99 			{UID_StPohang,UID_StSamdung,UID_StKumi,UID_StKoksan},
//DEADCODE DAW 19/11/99 			{UID_StSingye,UID_StYonan,UID_StChangdo,UID_StKuri},
//DEADCODE DAW 19/11/99 			{UID_StHongchon,UID_StChomchon,UID_StKimchon,UID_StKimchon},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		UID_StAndong
//DEADCODE DAW 19/11/99 	},
//DEADCODE DAW 19/11/99 //general testing type stuff
//DEADCODE DAW 19/11/99 	{
//DEADCODE DAW 19/11/99 		IDS_UN_CAP,IDS_UN_CAP,
//DEADCODE DAW 19/11/99 		{	
//DEADCODE DAW 19/11/99 			{	{	{PT_BLEN,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} }	},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		BLUE,0,0,0,
//DEADCODE DAW 19/11/99 		FIL_QUICKMISSION_18,FIL_QUICKMISSION_18,0,0,
//DEADCODE DAW 19/11/99 		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
//DEADCODE DAW 19/11/99 		{	{UID_StHoensong,UID_StWonsan,UID_StKusong,UID_StSunchon},
//DEADCODE DAW 19/11/99 			{UID_StYangdok,UID_StPyongyang,UID_StSamdung,UID_BrRlHuichon},
//DEADCODE DAW 19/11/99 			{UID_StSingye,UID_StIchon,UID_StChangdo,UID_StKuri},
//DEADCODE DAW 19/11/99 			{UID_StHongchon,UID_StChomchon,UID_StKimchon,UID_StKimchon},//MS 02May99
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		UID_NODE_sinuiju
//DEADCODE DAW 19/11/99 	},
//DEADCODE DAW 19/11/99 //RICH 1
//DEADCODE DAW 19/11/99 	{
//DEADCODE DAW 19/11/99 		IDS_BRIDGE,IDS_BRIDGE,
//DEADCODE DAW 19/11/99 		{	
//DEADCODE DAW 19/11/99 			{	{	{PT_BLEN,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} }	},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		BLUE,0,0,0,
//DEADCODE DAW 19/11/99 		FIL_QUICKMISSION_17,FIL_QUICKMISSION_17,0,0,
//DEADCODE DAW 19/11/99 		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
//DEADCODE DAW 19/11/99 		{	{UID_BrRdTanchon0,UID_BrRdTanchon1,UID_BrRdChosan,UID_BrRlManpo},
//DEADCODE DAW 19/11/99 			{UID_BrRlYesong,UID_BrRlTokohig,UID_BrRdYalu,UID_BrRlYalu0},
//DEADCODE DAW 19/11/99 			{UID_BrRdSinuiju,UID_BrRlSinuiju0,UID_BrRlNamdaechon,UID_BrRdUngig},
//DEADCODE DAW 19/11/99 			{UID_BrRlNan,UID_BrRlHan,UID_BrRdInje,UID_BrRlPukhan0},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		UID_NODE_sinuiju
//DEADCODE DAW 19/11/99 	},
//DEADCODE DAW 19/11/99 //RICH 2
//DEADCODE DAW 19/11/99 	{
//DEADCODE DAW 19/11/99 		IDS_CHOKE,IDS_CHOKE,
//DEADCODE DAW 19/11/99 		{	
//DEADCODE DAW 19/11/99 			{	{	{PT_BLEN,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} }	},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		BLUE,0,0,0,
//DEADCODE DAW 19/11/99 		FIL_QUICKMISSION_17,FIL_QUICKMISSION_17,0,0,
//DEADCODE DAW 19/11/99 		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
//DEADCODE DAW 19/11/99 		{	{UID_BrRlImjin,UID_BrRlPuktaechon,UID_BrRlKumjinchon,UID_BrRlChonui},
//DEADCODE DAW 19/11/99 			{UID_BrRlHuichon,UID_BrRdChuncheon0,UID_BrRdKilchu,UID_BrRlSeoul},
//DEADCODE DAW 19/11/99 			{UID_BrRdSeoul0,UID_BrRlKowon,UID_BrRlHuichon,UID_BrRlKowon},
//DEADCODE DAW 19/11/99 			{UID_BrRlTaeryong,UID_BrRlPyongyang,UID_BrRdPyongyang1,UID_BrRdPyongyang0},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		UID_NODE_sinuiju
//DEADCODE DAW 19/11/99 	},
//DEADCODE DAW 19/11/99 //RICH 3
//DEADCODE DAW 19/11/99 	{
//DEADCODE DAW 19/11/99 		IDS_BRIDGE,IDS_BRIDGE,
//DEADCODE DAW 19/11/99 		{	
//DEADCODE DAW 19/11/99 			{	{	{PT_BLEN,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} }	},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		BLUE,0,0,0,
//DEADCODE DAW 19/11/99 		FIL_QUICKMISSION_17,FIL_QUICKMISSION_17,0,0,
//DEADCODE DAW 19/11/99 		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
//DEADCODE DAW 19/11/99 		{	{UID_BrRdSinanju,UID_BrRlSinanju0,UID_BrRdTaeryong,UID_BrRlSinanju1},
//DEADCODE DAW 19/11/99 			{UID_BrRlKapyong,UID_BrRlSinanju1,UID_BrRlSinanju1,UID_BrRlSinanju1},
//DEADCODE DAW 19/11/99 			{UID_BrRlSinanju1,UID_BrRlSinanju1,UID_BrRlSinanju1,UID_BrRlSinanju1},
//DEADCODE DAW 19/11/99 			{UID_BrRlSinanju1,UID_BrRlSinanju1,UID_BrRlSinanju1,UID_BrRlSinanju1},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		UID_NODE_sinuiju
//DEADCODE DAW 19/11/99 	},
//DEADCODE DAW 19/11/99 //RICH 4
//DEADCODE DAW 19/11/99 	{
//DEADCODE DAW 19/11/99 		IDS_CHOKE,IDS_CHOKE,
//DEADCODE DAW 19/11/99 		{	
//DEADCODE DAW 19/11/99 			{	{	{PT_BLEN,2,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} }	},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		BLUE,0,0,0,
//DEADCODE DAW 19/11/99 		FIL_QUICKMISSION_17,FIL_QUICKMISSION_17,0,0,
//DEADCODE DAW 19/11/99 		{ IDS_CIVILIAN,IDS_AIRFIELD,IDS_BRIDGE,IDS_SUPPLY},
//DEADCODE DAW 19/11/99 		{	{UID_StHoensong,UID_StWonsan,UID_StKusong,UID_StSunchon},
//DEADCODE DAW 19/11/99 			{UID_StYangdok,UID_StPyongyang,UID_StSamdung,UID_BrRlHuichon},
//DEADCODE DAW 19/11/99 			{UID_StSingye,UID_StIchon,UID_StChangdo,UID_StKuri},
//DEADCODE DAW 19/11/99 			{UID_StHongchon,UID_StChomchon,UID_StKimchon,UID_StKimchon},//MS 02May99
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		UID_NODE_sinuiju
//DEADCODE DAW 19/11/99 	},
//DEADCODE DAW 19/11/99 //DEATH MATCH TESTING
//DEADCODE DAW 19/11/99 	{
//DEADCODE DAW 19/11/99 		IDS_QUICK_6,IDS_QUICK_6,
//DEADCODE DAW 19/11/99 		{	
//DEADCODE DAW 19/11/99 			{	{	{PT_SPIT_A,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} },	
//DEADCODE DAW 19/11/99 				{	{PT_SPIT_A,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} },	
//DEADCODE DAW 19/11/99 				{	{PT_F84,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} },	
//DEADCODE DAW 19/11/99 				{	{PT_F84,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} } },	
//DEADCODE DAW 19/11/99 			{	{	{PT_ME109,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} },
//DEADCODE DAW 19/11/99 				{	{PT_ME109,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} },
//DEADCODE DAW 19/11/99 				{	{PT_ME109,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} },
//DEADCODE DAW 19/11/99 				{	{PT_ME109,1,SKILL_VETERAN,FT_10000,IDS_UN_CAP,Q::QFD_BOMBER_AUTO_ONLY} }	}
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		BLUE,0,0,0,
//DEADCODE DAW 19/11/99 		FIL_deathmatch1,FIL_deathmatch1,0,0,
//DEADCODE DAW 19/11/99 		{ IDS_CIVILIAN,IDS_SUPPLYPOINT,IDS_AIRFIELD},
//DEADCODE DAW 19/11/99 		{	{UID_NODE_sinuiju,UID_StSinanju,UID_StSuihu,UID_StChosan},
//DEADCODE DAW 19/11/99 			{UID_MyRdPyongyang,UID_MyBlMunsan,UID_SdRdSonchon,UID_WhRdSukchon},
//DEADCODE DAW 19/11/99 			{UID_AfRdSinuiju,UID_AfRdPyongyangM,UID_AfRdUiju,UID_StSamchok},
//DEADCODE DAW 19/11/99 		},
//DEADCODE DAW 19/11/99 		UID_NODE_sinuiju
//DEADCODE DAW 19/11/99 	},
#endif
	{NULL,NULL,999}				//terminator!!!!!!!!!!!
};

int	main(int argc,char** argv)
{
	int i;
	for (i=0;CSQuick1::quickmissions[i].titlename;i++)
	{}
	FILE* f=fopen(argv[1],"wb");
	fwrite(CSQuick1::quickmissions,i+1,sizeof(QuickDef),f);
	fwrite(lookupspace,256,4,f);
	fwrite(extrastrings,1,sizeof(extrastrings),f);
	fclose(f);
	return 0;
}
#else
QuickDef::QuickMissionArray	CSQuick1::quickmissions;

void	QuickDef::MakeDeathMatchMission(int index)
{
	currmissnum = FIL_deathmatch0 + index;

}
void	QuickDef::MakeTeamPlayMission(int index)
{
	currmissnum = FIL_teamplay0 + index;


}
//DeadCode AMM 23Oct00 void	QuickDef::UpdateAcType()
//DeadCode AMM 23Oct00 {
//DeadCode AMM 23Oct00 	int i = 0, wave;
//DeadCode AMM 23Oct00 	int bluewave = -1;
//DeadCode AMM 23Oct00 	int redwave = -1;
//DeadCode AMM 23Oct00 	int side;
//DeadCode AMM 23Oct00 //	while	(		(i < _DPlay.CurrPlayers)
//DeadCode AMM 23Oct00 	while	(		(i < MAXPLAYERS)
//DeadCode AMM 23Oct00 			)
//DeadCode AMM 23Oct00 	{
//DeadCode AMM 23Oct00 		if (		(_DPlay.GameType == DPlay::DEATHMATCH)
//DeadCode AMM 23Oct00 				||	(DPlay::H2H_Player[i].squadron < PT_BRIT_NONFLY)
//DeadCode AMM 23Oct00 			)
//DeadCode AMM 23Oct00 		{
//DeadCode AMM 23Oct00 			side = 0;
//DeadCode AMM 23Oct00 			bluewave++;
//DeadCode AMM 23Oct00 			wave = bluewave;
//DeadCode AMM 23Oct00 		}else
//DeadCode AMM 23Oct00 		{
//DeadCode AMM 23Oct00 			side = 1;
//DeadCode AMM 23Oct00 			redwave++;
//DeadCode AMM 23Oct00 			wave = redwave;
//DeadCode AMM 23Oct00 		}
//DeadCode AMM 23Oct00 		CSQuick1::quickdef.line[side][wave][0].duty = 0;
//DeadCode AMM 23Oct00 		CSQuick1::quickdef.line[side][wave][0].flights = 1;
//DeadCode AMM 23Oct00 		CSQuick1::quickdef.line[side][wave][0].actype = DPlay::H2H_Player[i].squadron;
//DeadCode AMM 23Oct00 		for (int grp=1;grp<3;grp++)
//DeadCode AMM 23Oct00 		{
//DeadCode AMM 23Oct00 			CSQuick1::quickdef.line[side][wave][grp].duty = 0;
//DeadCode AMM 23Oct00 			CSQuick1::quickdef.line[side][wave][grp].flights = 0;
//DeadCode AMM 23Oct00 			CSQuick1::quickdef.line[side][wave][grp].actype = 0;
//DeadCode AMM 23Oct00 		}
//DeadCode AMM 23Oct00 		i++;	
//DeadCode AMM 23Oct00 	}	
//DeadCode AMM 23Oct00 	int startwave;
//DeadCode AMM 23Oct00 	for (side = 0; side < 2; side++)
//DeadCode AMM 23Oct00 	{
//DeadCode AMM 23Oct00 		if (side == 0)
//DeadCode AMM 23Oct00 		{
//DeadCode AMM 23Oct00 			bluewave++;
//DeadCode AMM 23Oct00 			startwave = bluewave;
//DeadCode AMM 23Oct00 		}else
//DeadCode AMM 23Oct00 		{
//DeadCode AMM 23Oct00 			redwave++;
//DeadCode AMM 23Oct00 			startwave = redwave;
//DeadCode AMM 23Oct00 		}
//DeadCode AMM 23Oct00 		for (startwave;wave<8;wave++)
//DeadCode AMM 23Oct00 		{
//DeadCode AMM 23Oct00 			for (int grp=0;grp<3;grp++)
//DeadCode AMM 23Oct00 			{
//DeadCode AMM 23Oct00 				CSQuick1::quickdef.line[side][wave][grp].duty = 0;
//DeadCode AMM 23Oct00 				CSQuick1::quickdef.line[side][wave][grp].flights = 0;
//DeadCode AMM 23Oct00 				CSQuick1::quickdef.line[side][wave][grp].actype = 0;
//DeadCode AMM 23Oct00 			}
//DeadCode AMM 23Oct00 		}
//DeadCode AMM 23Oct00 	}
//DeadCode AMM 23Oct00 }
////////////////////////////////////////////////////////////////////////
//
// Function:	QuickDef::trans
// Author:		JIM
// Date:		04/07/01
//
// Description:	Translation that occurs when the file is reloaded
//				Fix up pointers to internal strings
////////////////////////////////////////////////////////////////////////
void	QuickDef::trans(void* &dataarea,ULong& datasize)
{
	QuickDef* qd=(QuickDef*)dataarea;
	int i;
	for (i=0;qd[i].titlename;i++)	{}
	if (qd[i].missiondesc)
	{	//got string table appended
		qd+=i;
		qd++;
		char** tablestart=(char**)qd;
		extrastrings=tablestart;
		int* findtext=(int*)tablestart;
		while (*findtext==0) 
			findtext++;
		char* text=(char*)findtext;
		assert(*text=='\0');
		while (text[1]!=0)
		{
			tablestart[text[1]]=text+2;
			text+=2;
			while (*text)	text++;
		}
	}
}

const QuickDef	QuickDef::QuickMissionArray::operator[](int index)const
{
#ifdef	BOB_DEMO_VER
	fileblock fb(FIL_QUICKMISSIONDEMO_DATA,trans);
#else
	fileblock fb(FIL_QUICKMISSION_DATA,trans);
#endif
	QuickDef* qd=(QuickDef*)fb.getdata();
	return	(qd[index]); 
}
////////////////////////////////////////////////////////////////////////
//
// Function:	LoadResString
// Author:		JIM
// Date:		04/07/01
//
// Description:	Overload for LoadResString so that any occurance of LoadResString 
//				in the program that is dealing with text fields of quick missions *only*
//				will potentially be loaded from the quick mission extra strings
////////////////////////////////////////////////////////////////////////
char**	QuickDef::extrastrings;
CString LoadResString(FixString i)
{
	if (i<256)
		return(QuickDef::extrastrings[i]);
	else
		return LoadResString(+i);


}
#endif
