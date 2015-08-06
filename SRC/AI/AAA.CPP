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
//Filename       aaa.cpp
//System         
//Author         Jim Taylor
//Date           Fri 13 Sep 1996
//Description    Anti aircraft artillary and other artillary
//
//	Basic premise is that each AAA gun can spot and shoot at one enemy a/c
//	or ground object.
//
//	Each AAA item contains a number of aaa guns.
//
//	All the AAA items are in a list.
//
//	There will be 2 lists
//
//	AAASleepList	contains all aaa sites this will be processed at a rate so 
//					that each site is processed once per time skip (1/2 sec?).
//					This processing a quick search for a potential target
//					up to 13 miles (2 000 000cm)away. If there is such a target the site is 
//					added to the live list.
//
//	AAALiveList		contains aaa sites that can see things, or nearly see things
//					i.e. there is a target item within a long range.
//					The live AAA sites are processed each second or 1/2.
//
//
//	How are these lists made up?
//			LiveList:
//					link-list of array of 32 entries per link
//					entry number at top
//					same entry in each array is processed each 3cs
//			Sleep list:
//					same link-list structure, but circularised
//------------------------------------------------------------------------------

#include	"dosdefs.h"
extern	void	CheckE3();
#include	"worldinc.h"
#include	"mymath.h"
#include	"ranges.h"
#include	"myangles.h"
#include	"3dcom.h"
	#define F_COMMON
	#define F_GRAFIX
	#define F_BATTLE
#include	"files.g"
#include	"mytime.h"
//DEADCODE JIM 09/02/00 #include	"text.h"
#include	"persons2.h"
#include	"transite.h"
#include	"enumbits.m"
#include	"landscap.h"
#include	"flymodel.h"
#include	"miles.h"
#include	"aaa.h"
#include	"ai.h"
#include	"shpinstr.h"
#include	"globrefs.h"
#include	"rchatter.h"
#include "viewsel.h"
#include "winmove.h"
#include "missman2.h"
#include "sagmove.h"
//DEADCODE DAW 29/01/00 #include "package.h"
#include "sky.h"
#include "model.h"

//DeadCode PD 6Nov97 #pragma dump_object_model AircraftAnimData;

//MATHABLE(ANGLES);
//extern	ULong	GR_NAT_FRIEND;
//extern	ULong	GR_NAT_ENEMY;
#pragma  warning(disable:4355)
CON	LiveList::LiveList(WorldStuff* w):
	sleeplist(*this),sleeplistbackup(*this)
#pragma  warning(default:4355)
{
	WorldSearch world(w);
	ItemPtr i;
	LnchrType	ltype;
	while ((i=world.Next())!=NULL)
	{
		DOLAUNCHER_PTR d=(DOLAUNCHER_PTR)SHAPE.GetLauncherPos(i->shape,0);
		if (d)
		{
// Include test for aircraft weapons...
			ltype = LnchrType(d->lnchrtype & LT_MASK);						//RJS 19Apr00
			if (ltype == LT_WEAPON)
			{
				MoveGunAnimData*	mgad = (MoveGunAnimData*)i->Anim;
				ltype = LnchrType(mgad->weaponlaunchers[0].LauncherType & LT_MASK);
			}

			if (ltype == LT_MOVEGUN)
				sleeplist+=i;
		}
	}
//	sleeplist.AddItemEvents(EventRec::eventbase);
}

DES		AaaMainList::~AaaMainList()
{
	AaaSubList	*tmp,*tmp2;
	tmp=aaalist;
	do
	{
		tmp2=tmp->next;
		delete tmp;
		tmp=tmp2;
	}
	while (tmp!=aaalist);
//DeadCode JIM 06Oct96 	delete tmp;
}


//DEADCODE JIM 17/03/99 void	SleepList::AddItemEvents(EventRec* evlist)
//DEADCODE JIM 17/03/99 {
//DEADCODE JIM 17/03/99 	while (evlist)
//DEADCODE JIM 17/03/99 	{
//DEADCODE JIM 17/03/99 		if (evlist->attitem && (evlist->attitem->Status.size==ITEMSIZE || evlist->attitem->Status.size==MOBILESIZE))
//DEADCODE JIM 17/03/99 			operator+=(*evlist->attitem);
//DEADCODE JIM 17/03/99 		evlist=evlist->eventlink;
//DEADCODE JIM 17/03/99 	}
//DEADCODE JIM 17/03/99 }


bool AaaMainList::operator	+=(ItemPtr i)
{
AaaSubList	*sl=aaalist;
int	index;
bool retval = false;
	for (index=0;index<SUBLISTSIZE;index++)
		if (sl _[index]==NULL)
		{
			break;
		}
	if (index==SUBLISTSIZE && sl->next!=sl)
	do
	{
		sl=sl->next;
		for (index=0;index<SUBLISTSIZE;index++)
			if (sl _[index]==NULL)
			{
				aaalist=sl;
				break;
			}
	}	while	(sl!=aaalist);
	if (index!=SUBLISTSIZE)
	{
		index=(index+Math_Lib.rnd(SUBLISTSIZE-index));
		while (sl _[index])	index--;
	}
	else
	{
		sl=new AaaSubList;
		sl->next=aaalist->next;
		aaalist->next=sl;
		aaalist=sl;
		index=Math_Lib.rnd(SUBLISTSIZE);
	}
	sl _[index]=i;
	retval = true;
	return(retval);
}


bool AaaMainList::operator -=(ItemPtr i)
{
AaaSubList	*sl=aaalist;
int	index;
	for (index=0;index<SUBLISTSIZE;index++)
		if (sl _[index]==i)
		{
			break;
		}
	if (index==SUBLISTSIZE && sl->next!=sl)
	do
	{
		sl=sl->next;
		for (index=0;index<SUBLISTSIZE;index++)
			if (sl [0][index]==i)
			{
				aaalist=sl;
				break;
			}
	}	while	(sl!=aaalist);

	if (index!=SUBLISTSIZE)	
	{
		sl [0][index]=NULL;
		if (sl!=sl->next) //only 1 record
		{
			for (index=0;index<SUBLISTSIZE;index++)
				if (sl _[index])
					return(false);
			//ok.. can delete array record!
			AaaSubList	*s2=sl;
			while (sl->next!=aaalist)
				sl=sl->next;
			sl->next=s2->next;
	 		delete s2;
			aaalist=sl;
			return(true);
		}
	}
	return(false);
}


enum	AaaGunTypes
{
	AAA_HITSTATICS,
	AAA_ANTIAIRCRAFT,
	AAA_ANTIAIRCRAFTNOTSAG,
	AAA_ANTITANK,
	AAA_BARAGE,
	AAA_BARAGEGUN
};

struct	AaaParams
{
	AaaGunTypes				guntype;
	Nationality				nat;
	ANGLESInst					minhdg,hdgrange,
							minpitch,pitchrange;
	ANGLESInst					turnpersec;							//JIM 05Dec96
	SLong					minalt,altrange,flatrange;
	SWord					reloadtime;
//DEADCODE CSB 08/11/99 	UWord					muzzelvel;
	ULong					muzzelvel; //CSB 08/11/99
	SLong					lifetime;
	ShapeNum				shapenum;
	AutoMoveCodeTypeSelect	movecode;
	FileNum					sfx;								//RJS 22Nov96
	Bool					doinaccel;
};

#define	SPECIALLIFE	0x70000000

AaaParams	aaaguntypelist[]=
{
	//	guntype,nat
	//	minhdg,hdgrange,					minpitch,pitchrange,		turnpercs	
	//	minalt,altrange,					flatrange					reloadtime	
	//	muzzvel,lifetime,					shape,movecode				soundfx
	//	doinaccel

//SURFACE TO AIR
//British Hipano Cannon
	{	AAA_ANTIAIRCRAFT, NAT_RAF,
		ANGLES_0Deg, ANGLES_FIDDLEMAX,		ANGLES_30Deg, ANGLES_90Deg,		ANGLES_90Deg,
		METRES500, METRES2000,				METRES2000,						10,
		7500000, 2*100,						BULLET, MOBILE_BULLET,			FIL_SFX_MACHINE_GUN_LOOP2,
		TRUE,
	},

//British 40mm Bofors 2 pounder
	{	AAA_ANTIAIRCRAFT, NAT_RAF,
		ANGLES_0Deg, ANGLES_FIDDLEMAX,		ANGLES_30Deg, ANGLES_90Deg,		ANGLES_60Deg,
		METRES50, METRES2000,				METRES2000,						50,
		7500000, 5*100,						BULLET, MOBILE_BULLET,			FIL_SFX_MIG_CANNON_LOOP1,//RJS 15May00
		TRUE,
	},

//British 3in Gun
	{	AAA_ANTIAIRCRAFT, NAT_RAF,
		ANGLES_0Deg, ANGLES_FIDDLEMAX,		ANGLES_30Deg, ANGLES_90Deg,		ANGLES_30Deg,
		METRES1500, METRES6000,				METRES6000,						300,
		7500000, SPECIALLIFE,				BFLAK, MOBILE_PUFFTRAVEL,		FIL_SFX_GUN_TANK2,
		TRUE,
	},

//British 3.7in Mk IIIA
	{	AAA_ANTIAIRCRAFT, NAT_RAF,
		ANGLES_0Deg, ANGLES_FIDDLEMAX,		ANGLES_20Deg, ANGLES_90Deg,		ANGLES_30Deg,
		FT_2000, FT_18000,					METRES8000,						600,
		7500000, SPECIALLIFE,				BFLAK, MOBILE_PUFFTRAVEL,		FIL_SFX_GUN_TANK2,
		TRUE,
	},

//British 4.5in Gun
	{	AAA_ANTIAIRCRAFT, NAT_RAF,
		ANGLES_0Deg, ANGLES_FIDDLEMAX,		ANGLES_30Deg, ANGLES_90Deg,		ANGLES_30Deg,
		METRES1500, METRES10KM,				METRES10KM,						1200,
		7500000, SPECIALLIFE,				BFLAK, MOBILE_PUFFTRAVEL,		FIL_SFX_GUN_TANK2,
		TRUE,
	},

//British PAC - Parachute & Chain - Rocket launched
	{	AAA_ANTIAIRCRAFT, NAT_RAF,
		ANGLES_0Deg, ANGLES_FIDDLEMAX,		ANGLES_30Deg, ANGLES_90Deg,		ANGLES_180Deg,
		FT_500, FT_2000,					METRES5000,						6000,
		5000000, SPECIALLIFE,				PAK, MOBILE_PAC,				FIL_NULL,
		TRUE,													
	},

//AIR TO AIR
//German nose gunner
	{	AAA_ANTIAIRCRAFTNOTSAG, NAT_LUF,
		-ANGLES_45Deg, ANGLES_90Deg,		-ANGLES_45Deg, ANGLES_90Deg,	ANGLES_45Deg,
		-METRES350, METRES700,				METRES500,						500,
		7470000, 100,						BULLET, MOBILE_BULLET,			FIL_SFX_MACHINE_GUN_BURST_TURRET,//RJS 04Sep00
		TRUE
	},

//German top rear gunner
	{	AAA_ANTIAIRCRAFTNOTSAG, NAT_LUF,
		ANGLES_135Deg, ANGLES_90Deg,		-ANGLES_10Deg, ANGLES_90Deg,	ANGLES_45Deg,
		-METRES100, METRES500,				METRES500,						500,
		7470000, 100,						BULLET, MOBILE_BULLET,			FIL_SFX_MACHINE_GUN_BURST_TURRET,//RJS 04Sep00
		TRUE
	},

//German bottom rear gunner
	{	AAA_ANTIAIRCRAFTNOTSAG, NAT_LUF,
		ANGLES_135Deg, ANGLES_90Deg,		-ANGLES_80Deg, ANGLES_90Deg,	ANGLES_45Deg,
		-METRES500, METRES600,				METRES500,						500,
		7470000, 100,						BULLET, MOBILE_BULLET,			FIL_SFX_MACHINE_GUN_BURST_TURRET,//RJS 04Sep00
		TRUE
	},

//British rear turret
	{	AAA_ANTIAIRCRAFTNOTSAG, NAT_RAF,
		ANGLES_45Deg, ANGLES_270Deg,		-ANGLES_10Deg, ANGLES_90Deg,	ANGLES_45Deg,
		-METRES100, METRES500,				METRES500,						500,
		8110000, 100,						BULLET, MOBILE_BULLET,			FIL_SFX_MACHINE_GUN_BURST_FRONT_RAF,//RJS 04Sep00
		TRUE
	},

//DEADCODE CSB 10/01/00 	{	AAA_ANTIAIRCRAFT,NAT_RED,	//red large bore flak
//DEADCODE CSB 10/01/00 		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_30Deg,ANGLES_60Deg,	ANGLES_30Deg,//MS 11Dec96
//DEADCODE CSB 10/01/00 		METRES1000,FT_25000,				METRES5000,		100*10,
//DEADCODE CSB 10/01/00 		5*1000,SPECIALLIFE,BFLAK,MOBILE_PUFFTRAVEL,			FIL_NULL,
//DEADCODE CSB 10/01/00 		FALSE
//DEADCODE CSB 10/01/00 		},		//life of -1 means use est life
//DEADCODE CSB 10/01/00 
//DEADCODE CSB 10/01/00 	{	AAA_ANTIAIRCRAFT,NAT_RED,	//red large bore flak (short range)
//DEADCODE CSB 10/01/00 		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_30Deg,ANGLES_60Deg,	ANGLES_30Deg,//MS 11Dec96
//DEADCODE CSB 10/01/00 		METRES1000,FT_12000,				METRES5000,		100*10,
//DEADCODE CSB 10/01/00 		5*1000,SPECIALLIFE,WFLAK,MOBILE_PUFFTRAVEL,			FIL_NULL,
//DEADCODE CSB 10/01/00 		FALSE
//DEADCODE CSB 10/01/00 		},		//life of -1 means use est life
//DEADCODE CSB 10/01/00 
//DEADCODE CSB 10/01/00 	{	AAA_ANTIAIRCRAFT,NAT_BLUE,	//blue large bore flak
//DEADCODE CSB 10/01/00 		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_30Deg,ANGLES_60Deg,	ANGLES_30Deg,//MS 11Dec96
//DEADCODE CSB 10/01/00 		METRES1000,METRES3000,				METRES5000,		100*10,
//DEADCODE CSB 10/01/00 		5*1000,SPECIALLIFE,BFLAK,MOBILE_PUFFTRAVEL,			FIL_NULL,
//DEADCODE CSB 10/01/00 		FALSE
//DEADCODE CSB 10/01/00 		},		//life of -1 means use est life
//DEADCODE CSB 10/01/00 
//DEADCODE CSB 10/01/00 	{	AAA_ANTIAIRCRAFT,NAT_RED,	//red small bore flak 12mil
//DEADCODE CSB 10/01/00 		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_0Deg,ANGLES_80Deg,	ANGLES_170Deg,//JIM 05Dec96
//DEADCODE CSB 10/01/00 		FT_100,FT_4000,				FT_5000,		50,
//DEADCODE CSB 10/01/00 		6000,100*4,DSPARK,MOBILE_BULLET,					FIL_SFX_GUN_RIFLE_SHOT1,
//DEADCODE CSB 10/01/00 //TempCode MS 30Mar99 		5*1000,100*4,DSPARK,MOBILE_BULLET,								FIL_SFX_GUN_RIFLE_SHOT1,
//DEADCODE CSB 10/01/00 		FALSE
//DEADCODE CSB 10/01/00 		},
//DEADCODE CSB 10/01/00 
//DEADCODE CSB 10/01/00 	{	AAA_ANTIAIRCRAFT,NAT_RED,	//red small bore flak 37mil
//DEADCODE CSB 10/01/00 		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_0Deg,ANGLES_80Deg,	ANGLES_170Deg,//JIM 05Dec96
//DEADCODE CSB 10/01/00 		FT_100,FT_4300,				FT_5000,		50,
//DEADCODE CSB 10/01/00 		6000,100*4,FLMONN,MOBILE_BULLET,					FIL_SFX_MIG_CANNON_LOOP1,
//DEADCODE CSB 10/01/00 //TempCode MS 30Mar99 		5*1000,100*4,DSPARK,MOBILE_BULLET,								FIL_SFX_GUN_RIFLE_SHOT1,
//DEADCODE CSB 10/01/00 		FALSE
//DEADCODE CSB 10/01/00 		},
//DEADCODE CSB 10/01/00 
//DEADCODE CSB 10/01/00 	{	AAA_ANTIAIRCRAFT,NAT_BLUE,	//blue small bore flak
//DEADCODE CSB 10/01/00 		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_0Deg,ANGLES_60Deg,	ANGLES_170Deg,//JIM 05Dec96
//DEADCODE CSB 10/01/00 		0,FT_12000,				METRES2000,		50,
//DEADCODE CSB 10/01/00 		6000,100*2,DSPARK,MOBILE_BULLET,					FIL_SFX_GUN_RIFLE_SHOT1,
//DEADCODE CSB 10/01/00 		FALSE
//DEADCODE CSB 10/01/00 		},
//DEADCODE CSB 10/01/00 
//DEADCODE CSB 10/01/00 	{	AAA_BARAGE,NAT_RED,			//ground effect (non fatal)	//RJS 31Mar99
//DEADCODE CSB 10/01/00 		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_330Deg,ANGLES_120Deg,	ANGLES_10Deg,	//RJS 05Oct98
//DEADCODE CSB 10/01/00 		-METRES100,METRES200,				METRES500,		500,				//Shoot every 5secs
//DEADCODE CSB 10/01/00 		800,SPECIALLIFE,DSPARK,MOBILE_BULLET,									FIL_SFX_GUN_TANK2,//RJS 05Oct98
//DEADCODE CSB 10/01/00 		FALSE																					//RJS 05Oct98
//DEADCODE CSB 10/01/00 		},
//DEADCODE CSB 10/01/00 
//DEADCODE CSB 10/01/00 	{	AAA_BARAGEGUN,NAT_RED,		//red ground gun (non fatal)																//RJS 09Dec98
//DEADCODE CSB 10/01/00 		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_300Deg,ANGLES_160Deg,	ANGLES_10Deg,
//DEADCODE CSB 10/01/00 		-METRES500,METRES800,				160000,		500,
//DEADCODE CSB 10/01/00 		800,SPECIALLIFE,DSPARK,MOBILE_BOMBDROP,								FIL_SFX_GUN_TANK2,
//DEADCODE CSB 10/01/00 		FALSE
//DEADCODE CSB 10/01/00 		},
//DEADCODE CSB 10/01/00 
//DEADCODE CSB 10/01/00 	{	AAA_BARAGEGUN,NAT_BLUE,		//blue ground gun (non fatal)																//RJS 09Dec98
//DEADCODE CSB 10/01/00 		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_300Deg,ANGLES_160Deg,	ANGLES_10Deg,
//DEADCODE CSB 10/01/00 		-METRES500,METRES800,				160000,		500,
//DEADCODE CSB 10/01/00 		5*800,SPECIALLIFE,DSPARK,MOBILE_BOMBDROP,								FIL_SFX_GUN_TANK2,
//DEADCODE CSB 10/01/00 		FALSE
//DEADCODE CSB 10/01/00 		},
//DEADCODE CSB 10/01/00 
//DEADCODE CSB 10/01/00 //DeadCode RJS 08Apr99 	{	AAA_ANTIAIRCRAFT,NAT_RED,	//rear gunners red
//DEADCODE CSB 10/01/00 //DeadCode RJS 08Apr99 		ANGLES_90Deg,ANGLES_180Deg,		ANGLES_350Deg,ANGLES_50Deg,			ANGLES_150Deg,//JIM 05Dec96
//DEADCODE CSB 10/01/00 //DeadCode RJS 08Apr99 		-METRES50,METRES300,				METRES300,		50,
//DEADCODE CSB 10/01/00 //DeadCode RJS 08Apr99 		5*1200,100*1,BULLET,MOBILE_BULLET,									FIL_SFX_GUN_TANK1,
//DEADCODE CSB 10/01/00 //DeadCode RJS 08Apr99 		TRUE
//DEADCODE CSB 10/01/00 //DeadCode RJS 08Apr99 		},
//DEADCODE CSB 10/01/00 //DeadCode RJS 08Apr99 
//DEADCODE CSB 10/01/00 //DeadCode RJS 08Apr99 	{	AAA_ANTIAIRCRAFT,NAT_BLUE,	//rear gunners blue
//DEADCODE CSB 10/01/00 //DeadCode RJS 08Apr99 		ANGLES_90Deg,ANGLES_180Deg,		ANGLES_350Deg,ANGLES_50Deg,			ANGLES_150Deg,//JIM 05Dec96
//DEADCODE CSB 10/01/00 //DeadCode RJS 08Apr99 		-METRES50,METRES300,				METRES300,		50,
//DEADCODE CSB 10/01/00 //DeadCode RJS 08Apr99 		5*1200,100*1,BULLET,MOBILE_BULLET,									FIL_SFX_GUN_TANK1,
//DEADCODE CSB 10/01/00 //DeadCode RJS 08Apr99 		TRUE
//DEADCODE CSB 10/01/00 //DeadCode RJS 08Apr99 		},
//DEADCODE CSB 10/01/00 
//DEADCODE CSB 10/01/00 	{	AAA_ANTIAIRCRAFT,NAT_BLUE,	//turret gunners top (forward)
//DEADCODE CSB 10/01/00 		-ANGLES_90Deg,ANGLES_180Deg,		ANGLES_350Deg,ANGLES_50Deg,			ANGLES_150Deg,
//DEADCODE CSB 10/01/00 		-METRES50,METRES300,				METRES300,		50,
//DEADCODE CSB 10/01/00 		5*1200,100*1,BULLET,MOBILE_BULLET,									FIL_SFX_MACHINE_GUN_LOOP2,
//DEADCODE CSB 10/01/00 		TRUE
//DEADCODE CSB 10/01/00 		},
//DEADCODE CSB 10/01/00 
//DEADCODE CSB 10/01/00 	{	AAA_ANTIAIRCRAFT,NAT_BLUE,	//turret gunners bottom (forward)
//DEADCODE CSB 10/01/00 		-ANGLES_90Deg,ANGLES_180Deg,		ANGLES_300Deg,ANGLES_50Deg,			ANGLES_150Deg,
//DEADCODE CSB 10/01/00 		-METRES50,METRES300,				METRES300,		50,
//DEADCODE CSB 10/01/00 		5*1200,100*1,BULLET,MOBILE_BULLET,									FIL_SFX_MACHINE_GUN_LOOP2,
//DEADCODE CSB 10/01/00 		TRUE
//DEADCODE CSB 10/01/00 		},
//DEADCODE CSB 10/01/00 
//DEADCODE CSB 10/01/00 	{	AAA_ANTIAIRCRAFT,NAT_BLUE,	//turret gunners top (rear)
//DEADCODE CSB 10/01/00 		ANGLES_90Deg,ANGLES_180Deg,		ANGLES_350Deg,ANGLES_50Deg,			ANGLES_150Deg,
//DEADCODE CSB 10/01/00 		-METRES50,METRES300,				METRES300,		50,
//DEADCODE CSB 10/01/00 		5*1200,100*1,BULLET,MOBILE_BULLET,									FIL_SFX_MACHINE_GUN_LOOP2,
//DEADCODE CSB 10/01/00 		TRUE
//DEADCODE CSB 10/01/00 		},
//DEADCODE CSB 10/01/00 
//DEADCODE CSB 10/01/00 	{	AAA_ANTIAIRCRAFT,NAT_BLUE,	//turret gunners bottom (rear)
//DEADCODE CSB 10/01/00 		ANGLES_90Deg,ANGLES_180Deg,		ANGLES_300Deg,ANGLES_50Deg,			ANGLES_150Deg,
//DEADCODE CSB 10/01/00 		-METRES50,METRES300,				METRES300,		50,
//DEADCODE CSB 10/01/00 		5*1200,100*1,BULLET,MOBILE_BULLET,									FIL_SFX_MACHINE_GUN_LOOP2,
//DEADCODE CSB 10/01/00 		TRUE
//DEADCODE CSB 10/01/00 		},
//DEADCODE CSB 10/01/00 
//DEADCODE CSB 10/01/00 	{	AAA_ANTIAIRCRAFT,NAT_RED,	//turret gunners top (rear)
//DEADCODE CSB 10/01/00 		ANGLES_90Deg,ANGLES_180Deg,		ANGLES_350Deg,ANGLES_50Deg,			ANGLES_150Deg,
//DEADCODE CSB 10/01/00 		-METRES50,METRES300,				METRES300,		50,
//DEADCODE CSB 10/01/00 		5*1200,100*1,BULLET,MOBILE_BULLET,									FIL_SFX_MACHINE_GUN_LOOP2,
//DEADCODE CSB 10/01/00 		TRUE
//DEADCODE CSB 10/01/00 		},
};

class	TrgListProc
{
public:
	AaaGunTypes type;
	AaaMainList::AaaSubList		*base,*base2;		//base+index--> item ptr.: first weap -> nat
	union
	{
		MobileItemPtr	last;		//last->nextmobile --> last: formationitem nationality
		AaaMainList::AaaSubList* start;
		AirStrucPtr*	aclist;
	};
	int	index;
	Nationality	nat;
	CON TrgListProc(AaaGunTypes t,Nationality n,AaaMainList::AaaSubList *s,AaaMainList::AaaSubList *s2)	{ReStart(t,n,s,s2);}
	void ReStart(AaaGunTypes t,Nationality n,AaaMainList::AaaSubList *s,AaaMainList::AaaSubList *s2);
	ItemPtr	Next();
};

void	TrgListProc::ReStart(AaaGunTypes t,Nationality n,AaaMainList::AaaSubList *s,AaaMainList::AaaSubList *s2)
{
	nat=n;
	index=0;
	type=t;
	switch (t)
	{
	case AAA_HITSTATICS:
		base=start=s;
		base2=s2;
		break;
	case AAA_ANTIAIRCRAFT:
	case AAA_ANTIAIRCRAFTNOTSAG:
		base2=base=NULL;
//DeadCode CSB 15Aug00 		aclist=ArtInt::ACArray;
//DeadCode CSB 15Aug00 		index=-1;
		last = mobileitem::ACList;
		break;
	case AAA_ANTITANK:
	case AAA_BARAGE:
	case AAA_BARAGEGUN:
		base2=base=NULL;
		last=mobileitem::MobileList;
		break;
	}
}

ItemPtr	TrgListProc::Next()
{
	ItemPtr retval=NULL;
	switch (type)
	{
	case AAA_HITSTATICS:
		{
			if (index==AaaMainList::SUBLISTSIZE)
			{
				if (base->next==start)
					if (base2)
					{
						start=base=base2;base2=NULL;
					}
					else
						return(NULL);
				index=0;
				base=base->next;
			}

			DOLAUNCHER_PTR dlp;
			while (		base[0][index]==NULL
					||	(	base[0][index]->Status.deadtime!=0
						||	( dlp=(DOLAUNCHER_PTR)SHAPE.GetLauncherPos((base[0][index])->shape,0),
							  dlp	?aaaguntypelist[dlp->lnchrtype-LT_MOVEGUN].nat==nat
									:TRUE
							)
				)		)
	   		{
				index++;
				if (index==AaaMainList::SUBLISTSIZE)
				{
					if (base->next==start)
					{
						if (base2)
						{
							start=base=base2;base2=NULL;
						}
						else
							return(NULL);
					}
					index=0;
					base=base->next;
				}
			}
			retval=base[0][index];
			index++;
		}
		break;
	case AAA_ANTIAIRCRAFT:
	{
		while(last)
		{
			AirStrucPtr ac = AirStrucPtr(last);
			if(		(!ac->Status.deadtime) && (ac->nationality != nat)
				&&	((!ac->fly.numinsag) || (!ac->fly.expandedsag))		)
//DeadCode CSB 22Aug00 				&&	(!ac->ai.attacker)	)
				retval = last;

			if(last->nextmobile)
				last = last->nextmobile;
			else
			{
				if(!ac->fly.numinsag)
					last = mobileitem::SAGList;
				else
					return(NULL);
			}
			if(retval)
				return(retval);
		}
		break;
	}
	case AAA_ANTIAIRCRAFTNOTSAG:
	{
		while(last)
		{
			AirStrucPtr ac = AirStrucPtr(last);
			if(		(!ac->Status.deadtime) && (ac->nationality != nat)
				&&	(!ac->fly.numinsag)		)
				retval = last;

			if(last->nextmobile)
				last = last->nextmobile;
			else
			{
//DeadCode CSB 3Nov00 				if(!ac->fly.numinsag)
//DeadCode CSB 3Nov00 					last = mobileitem::SAGList;
//DeadCode CSB 3Nov00 				else
					return(NULL);
			}
			if(retval)
				return(retval);
		}
		break;
	}
//DeadCode CSB 15Aug00 		{
//DeadCode CSB 15Aug00 			do
//DeadCode CSB 15Aug00 				index++;
//DeadCode CSB 15Aug00 			while (		index<ArtInt::ACARRAYSIZE 
//DeadCode CSB 15Aug00 					&& (	aclist[index]==NULL 
//DeadCode CSB 15Aug00 						||	aclist[index]->nationality==nat
//DeadCode CSB 15Aug00 					)	);
//DeadCode CSB 15Aug00 			if (index<ArtInt::ACARRAYSIZE)
//DeadCode CSB 15Aug00 				return aclist[index];
//DeadCode CSB 15Aug00 			else
//DeadCode CSB 15Aug00 				return NULL;
//DeadCode CSB 15Aug00 
//DeadCode CSB 15Aug00 		}
//DeadCode CSB 15Aug00 		break;
	case AAA_ANTITANK:
	case AAA_BARAGE:
	case AAA_BARAGEGUN:
		{
			while (		last
					&&	(	last->nationality==nat
						||	last->Status.deadtime!=0
					)	)	//add extra fix for in formation
				last=last->nextmobile;
			retval=last;
			if (last)
				last=last->nextmobile;
		}
		break;
	}
	return retval;
}


void	SleepList::Event()
{
	if (++aaaind==SUBLISTSIZE)
	{
		aaaind=0;
		aaalist=aaalist->next;
		if (aaalist==blockradio)
			blockradio=NULL;
	}
//do summat
	ItemPtr eye=aaalist[0][aaaind];
	if( (eye) && (!eye->uniqueID.commsmove) && (!((eye == Persons2::PlayerSeenAC) && (_DPlay.Implemented))) ) 
	{
		AaaGunTypes guntype=AAA_ANTIAIRCRAFT;

		Nationality	nat=(Nationality)GR_NAT_ENEMY;
		int			range=METRES10KM;

		DOLAUNCHER_PTR d=(DOLAUNCHER_PTR)SHAPE.GetLauncherPos(eye->shape,0);
		if (d)
		{
			MoveGunAnimData*	mgad = (MoveGunAnimData*)eye->Anim;

			AaaParams* a = &aaaguntypelist[mgad->weaponlaunchers[0].LauncherType - LT_MOVEGUN];
			guntype=a->guntype;
			nat=a->nat;
//DeadCode CSB 13Jul00 			range=a->flatrange+METRES2000;
			range = a->flatrange + HALFVISIBLERANGE;
//DEADCODE DAW 26/05/99 		}
			TrgListProc	tlp(guntype,nat,aaalist,Live_List.aaalist);
		//for all ac/gmobiles/aaasites - depending on type of gun
			//if on enemy side - depending on type
				//if not in formation (a/c only - if in form then leader only to test)
			ItemPtr trg=tlp.Next();
			while (trg)
			{
				Coords3D* trgpos=_DPlay.GetGoodACPosition(trg);

					//if quick range < 20KM add to livelist and exit
				if(		(Math_Lib.AbsSign(trgpos->X-eye->World.X) < range)
					&&	(Math_Lib.AbsSign(trgpos->Z-eye->World.Z) < range)	)
						{
							//Has altitude been fixed yet?
							if (eye->World.Y == 0)			//RJS 10Dec98
								eye->World.Y = Land_Scape.GetGroundLevel(eye->World);//RJS 10Dec98

							if (eye->Anim==NULL)
								SHAPE.SetAnimData(*eye);
							
							if(OKtoWakeAAA(eye, a->nat))
							{
								operator-=(eye);
								Live_List+=eye;
								Coords3D		weapoff;
								int				weapnum=0;
								ULong			mvel;									//RJS 12Nov99
								UWord			mdelay,mburst;							//RJS 12Nov99
//DeadCode JIM 20Oct00 								bool	targetting=false;
								WeapAnimData*	weapanim=SHAPE.GetWeaponLauncher(eye,0,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN);//RDH 31Jul98
								if (weapanim)											//RJS 24Jun99
									weapanim->LaunchTime=0;								//RJS 24Jun99

	//DeadCode DAW 25Jun99 							weapanim->LaunchTime=0;
//DEADCODE CSB 11/02/00 								if((d->lnchrtype == LT_BRIT_3IN) || (d->lnchrtype == LT_BRIT_3_7IN) || (d->lnchrtype == LT_BRIT_4_5IN))
//DEADCODE CSB 11/02/00 									if (trg->Status.size==AIRSTRUCSIZE)
//DEADCODE CSB 11/02/00 										if (!blockradio)
//DEADCODE CSB 11/02/00 											if (AirStrucPtr(*trg)->IsUsingPilotedAcLog() && trg->World.Y>METRES5000)
//DEADCODE CSB 11/02/00 											{
//DEADCODE CSB 11/02/00 												TargetIndexes	trgindex;
//DEADCODE CSB 11/02/00 												int msgalt=trg->World.Y;
//DEADCODE CSB 11/02/00 												if (msgalt<eye->World.Y+a->minalt+a->altrange)
//DEADCODE CSB 11/02/00 												{
//DEADCODE CSB 11/02/00 													MESSAGE_STRUC	tmpmsg(OLDSCRIPT_FLAKREPORT, MSG_FLAKREPORT, NULL, eye, Persons2::PlayerGhostAC,trgindex.SetHeight(msgalt));//RJS 02Feb00
//DEADCODE CSB 11/02/00 													_Miles.SequenceAudible(FIL_MUSIC_FLAK);
//DEADCODE CSB 11/02/00 													_Radio.TriggerMsg(tmpmsg.SetVoice(VOICE_DENTIST));
//DEADCODE CSB 11/02/00 													blockradio=aaalist;
//DEADCODE CSB 11/02/00 												}
//DEADCODE CSB 11/02/00 											}
							}
							return;/////
						}
				trg=tlp.Next();
			}
		}														//RJS 26May99
//remove from live list if get here (nothing visible)
//DeadCode JIM 15Nov96 	Live_List-=eye;	//should not be in livelist anyway!
	}
}

inline void	WarnSmallBore(MobileItem*weapitem,AirStruc*trg)
{
//DEADCODE CSB 11/02/00 	AirStrucPtr resp=trg->fly.leadflight;
//DEADCODE CSB 11/02/00 	if (!resp)
//DEADCODE CSB 11/02/00 		resp=trg->FindBuddy();
//DEADCODE CSB 11/02/00 	if (resp)
//DEADCODE CSB 11/02/00 	{
//DEADCODE CSB 11/02/00 		if (weapitem->SGT)
//DEADCODE CSB 11/02/00 			_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_FLAKFIRING, MSG_FLAKFIRING, resp, Persons2::ConvertPtrUID(weapitem->SGT), trg));//RJS 02Feb00
//DEADCODE CSB 11/02/00 		else
//DEADCODE CSB 11/02/00 			_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_FLAKFIRING, MSG_FLAKFIRING, resp, weapitem, trg));//RJS 02Feb00
//DEADCODE CSB 11/02/00 	}
//DEADCODE CSB 11/02/00 
}


void	LiveList::Event()
{

//DeadCode JIM 06Jan97 	CheckE3();

	if((Persons2::PlayerGhostAC->movecode == AUTO_TRAININGTAKEOFF) || (Persons2::PlayerGhostAC->movecode == AUTO_TRAININGLANDING))
		return;

	if (++aaaind==SUBLISTSIZE)
	{
		aaaind=0;
		aaalist=aaalist->next;
		sleeplist.Event();
		sleeplist.Event();
		sleeplist.Event();
	}
	int eventtime = 0;
	AaaSubList *list = aaalist;
	for(;;)
	{
		eventtime += Timer_Code.FRAMETIME * SUBLISTSIZE;
		list = list->next;
		if(list == aaalist)
			break;
	}

//do summat
//for each mobile launcher in item

	if (aaalist[0][aaaind])
	{
//DeadCode JIM 06Jan97 	CheckE3();
		ItemPtr		weapitem=aaalist[0][aaaind];
		if (weapitem->World.Y==0)
			weapitem->World.Y=Land_Scape.GetGroundLevel(weapitem);
		Coords3D		weapoff;
		int				weapnum=0;
		ULong			mvel;								//RJS 12Nov99
		UWord			mdelay,mburst;						//RJS 12Nov99
		bool	targetting=false;
		WeapAnimData*	weapanim=SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN);//RDH 31Jul98
//DeadCode JIM 06Jan97 	CheckE3();
		if (weapanim)
		{
			if (!weapanim->target)
				if (weapanim->LaunchTime)
				{
					weapnum=weapanim->LaunchTime;
					weapanim=SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN);//RDH 31Jul98
					if (!weapanim)
					{
						weapnum=0;
						weapanim=SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN);//RDH 31Jul98
						weapanim->LaunchTime=0;
						targetting=true;
					}
				}

			AaaParams* 		aaaparams=&aaaguntypelist[weapanim->LauncherType-LT_MOVEGUN];
//DEADCODE CSB 28/02/00 			TrgListProc		targlist(aaaparams->guntype,aaaparams->nat,sleeplist.aaalist,aaalist);	//assume all a/c use same detect routines
			Bool nothingthere=TRUE;

			if (	aaaparams->doinaccel 
				||	MobileItem::currworld->vp==NULL 
				|| !MobileItem::currworld->vp->Accel()
				)
			while (weapanim!=NULL)
			{
			//if known target 
				if (weapanim->target)
				{
					targetting=true;
					nothingthere=FALSE;
					{
						int t = weapanim->LaunchTime - eventtime;
						if(t > 0)
							weapanim->LaunchTime = t;
						else
							weapanim->LaunchTime = 0;
					}
					ItemPtr	trg = *MobileItem::currworld->ConvertPtrUID((UniqueID)weapanim->target);
					SLong  Range;
					ANGLES HdgIntercept, PitchIntercept;
					ANGLES GlobHdgInt, GlobPitchInt;

					Coords3D Wtarg, Wgun;
					Coords3D Vtarg, Vgun;

					if(trg)
					{
						if (trg->Status.deadtime)
							weapanim->target=UID_Null;
						
						Wgun = weapoff;

						if(trg->Status.size < MOBILESIZE)
							SHAPE.GetLiveElementPos(0, trg, Wtarg.X, Wtarg.Y, Wtarg.Z);
						else
							Wtarg = trg->World;

						//First Quick Throwout - Alt
						if(		(Wtarg.Y - Wgun.Y < aaaparams->minalt - METRES100)
							||	(Wtarg.Y - Wgun.Y > aaaparams->minalt + aaaparams->altrange + METRES100)	)
						{
							weapanim->target = UID_Null;
							trg = *MobileItem::currworld->ConvertPtrUID((UniqueID)weapanim->target);
						}
						else
						{	//Second Quick Throwout - Range
//DEADCODE CSB 17/05/00 							SLong d1 = Wtarg.X - Wgun.X;		if(d1 < 0) d1 *= -1;
//DEADCODE CSB 17/05/00 							SLong d2 = Wtarg.Y - Wgun.Y;		if(d2 < 0) d2 *= -1;
//DEADCODE CSB 17/05/00 							SLong d3 = Wtarg.Z - Wgun.Z;		if(d3 < 0) d3 *= -1;
//DEADCODE CSB 17/05/00 
//DEADCODE CSB 17/05/00 							if(d2 > d1)	{SLong temp = d1;	d1 = d2;	d2 = temp;	}
//DEADCODE CSB 17/05/00 							if(d3 > d1)	{SLong temp = d1;	d1 = d3;	d3 = temp;	}
//DEADCODE CSB 17/05/00 
//DEADCODE CSB 17/05/00 							Range = d1 + (d2 * d2 + d3 * d3) / (2 * d1);	//Max error [ 0% , + 16% ]
							Range = weapitem->Distance3D(&Wgun, &Wtarg);

//DEADCODE CSB 28/02/00 							if(		((weapitem->Status.size == AIRSTRUCSIZE) && (Range > METRES250))
//DEADCODE CSB 28/02/00 								||	(Range > aaaparams->lifetime * aaaparams->muzzelvel / 10000)		)
							FP maxrange = aaaparams->flatrange;
							if(aaaparams->lifetime != SPECIALLIFE)
								maxrange = FP(aaaparams->lifetime) * FP(aaaparams->muzzelvel) * 0.0001;
							if(Range > maxrange)
							{
								weapanim->target = UID_Null;
								trg = *MobileItem::currworld->ConvertPtrUID((UniqueID)weapanim->target);
							}
						}
					}

					if(trg)
					{
						if(weapitem->Status.size < MOBILESIZE)
						{
							Vgun.X = 0;
							Vgun.Y = 0;
							Vgun.Z = 0;
						}
						else
						{
							MobileItemPtr tempmob = *weapitem;
							Vgun.X = tempmob->vel_x;
							Vgun.Y = tempmob->vel_y;
							Vgun.Z = tempmob->vel_z;

							if((weapitem->Status.size == AIRSTRUCSIZE) && (SWord(ANGLES(aaaparams->hdgrange)) <= ANGLES_180Deg))
							{	//Third quick throwout	
								FP dotprop =  FP(Vgun.X) * FP(Wtarg.X - Wgun.X)		//	+ve if target is infront of gun item
											+ FP(Vgun.Y) * FP(Wtarg.Y - Wgun.Y)		//	-ve if target is behind gun item
											+ FP(Vgun.Z) * FP(Wtarg.Z - Wgun.Z);

								if(		((aaaparams->minhdg < ANGLES_0Deg) && (dotprop < 0))	 //Forward Gun - target behind
									||	((aaaparams->minhdg > ANGLES_0Deg) && (dotprop > 0))	)//Rearward Gun - target infront
								{
									weapanim->target = UID_Null;
									trg = *MobileItem::currworld->ConvertPtrUID((UniqueID)weapanim->target);
								}
							}
						}

						if(trg)
							if(trg->Status.size < MOBILESIZE)
							{
								Vtarg.X = 0;
								Vtarg.Y = 0;
								Vtarg.Z = 0;
							}
							else
							{
								MobileItemPtr tempmob = *trg;
								Vtarg.X = tempmob->vel_x;
								Vtarg.Y = tempmob->vel_y;
								Vtarg.Z = tempmob->vel_z;
							}
					}

					if(trg)	//Survived the quick throwouts
					{
						FP dt = FP(Range) / FP(aaaparams->muzzelvel);
						FP aimdt = dt;
						if(weapitem->Status.size == AIRSTRUCSIZE)
						{
//DEADCODE CSB 22/05/00 							AirStrucPtr weapac = AirStrucPtr(weapitem);
//DEADCODE CSB 22/05/00 //DEADCODE CSB 22/05/00 							FP fskill = (weapac->ai.combatskill + Math_Lib.rnd(2 * (255 - weapac->ai.combatskill))) / 255.0;
//DEADCODE CSB 22/05/00 							FP fskill = 5.0 - (4.0 / 256.0) * weapac->ai.combatskill;
//DEADCODE CSB 22/05/00 							dt *= fskill;
//DEADCODE CSB 22/05/00 							aimdt = dt;
						}
						else 
							if((weapanim->LauncherType >= LT_BRIT_BOFORS) && (weapanim->LauncherType <= LT_BRIT_4_5IN))
								aimdt += Math_Lib.rnd(5) * 0.01;	//up to 5 seconds ahead of target

						SLong vx, vy, vz;
						MissManCampSky().GetWind(Wgun.Y, vx, vy, vz);
						Vgun.X += vx;
						Vgun.Y += vy;
						Vgun.Z += vz;

						Wgun.X += Vgun.X * aimdt;
						Wgun.Y += Vgun.Y * aimdt;
						Wgun.Z += Vgun.Z * aimdt;

						MissManCampSky().GetWind(Wtarg.Y, vx, vy, vz);
						Vtarg.X += vx;
						Vtarg.Y += vy;
						Vtarg.Z += vz;

						Wtarg.X += Vtarg.X * aimdt;
						Wtarg.Y += Vtarg.Y * aimdt + (0.5 * 10.0 * 10e5) * dt * dt;	// 1/2 * G * t2						Wtarg.Z += Vtarg.Z * aimdt;
						Wtarg.Z += Vtarg.Z * aimdt;

						if(aaaparams->movecode == MOBILE_PAC)
						{								//Fire 7.5 seconds ahead of aircraft and 150m above it
							Wtarg.X += (Vtarg.X * 75) * 1e-3;
							Wtarg.Y += (Vtarg.Y * 75) * 1e-3 + 15000;
							Wtarg.Z += (Vtarg.Z * 75) * 1e-3;
						}

						Math_Lib.HighIntercept(Wtarg.X - Wgun.X, Wtarg.Y - Wgun.Y, Wtarg.Z - Wgun.Z,
												Range, GlobHdgInt, GlobPitchInt);
						HdgIntercept   = GlobHdgInt;
						PitchIntercept = GlobPitchInt;
						dt = FP(Range) / FP(aaaparams->muzzelvel);

						if(weapitem->Status.size >= MOBILESIZE)	//Simple Transformation
						{
							MobileItemPtr tempmob = *weapitem;
							HdgIntercept   -= tempmob->hdg;
							SWord sin, cos;
							Math_Lib.high_sin_cos(HdgIntercept, sin, cos);
							PitchIntercept -= MULSHSIN(tempmob->pitch, cos, ANGLES_SHIFT);

							if(		(weapitem->Status.size == AIRSTRUCSIZE)
								&&	( SWord(tempmob->roll) > ANGLES_1Deg)
								&&	(-SWord(tempmob->roll) > ANGLES_1Deg))
							{
								//Transform coordinates
								SWord hdgint   = SWord(HdgIntercept);
								SWord pitchint = SWord(PitchIntercept);
								SWord hdgintfor = hdgint;
								if((hdgint > ANGLES_90Deg) || (-hdgint > ANGLES_90Deg))
									hdgintfor += ANGLES_180Deg;
								Float sinr, cosr;
								Math_Lib.high_sin_cos(tempmob->roll, sinr, cosr);
								SWord newhdgint = hdgintfor * cosr - pitchint * sinr;
								if((hdgint > ANGLES_90Deg) || (-hdgint > ANGLES_90Deg))
									newhdgint += ANGLES_180Deg;
								HdgIntercept   = Angles(newhdgint);
								PitchIntercept = Angles(SWord(pitchint * cosr + hdgintfor * sinr));
							}
						}

						if(		(UWord(HdgIntercept   - aaaparams->minhdg)   < UWord(ANGLES(aaaparams->hdgrange)))
							&&	(UWord(PitchIntercept - aaaparams->minpitch) < UWord(ANGLES(aaaparams->pitchrange)))	)
						{	//Target in the guns range of movement so aim and fire
//DeadCode CSB 15Aug00 							ANGLES	tang;					//RJS 09Dec98
							int	turnper;					//RJS 09Dec98
								
							turnper = ((ANGLES)aaaparams->turnpersec * eventtime) / 100;
//DeadCode CSB 15Aug00 							tang = (Angles)turnper;			//RJS 09Dec98
//DeadCode CSB 15Aug00 							if (tang>ANGLES_90Deg)			//RJS 09Dec98
//DeadCode CSB 15Aug00 								turnper=ANGLES_90Deg;		//RJS 09Dec98

							if(turnper > AbsAngle(HdgIntercept-(Angles)weapanim->hdg))
								weapanim->hdg = HdgIntercept;
							else
								weapanim->hdg+=(Angles)Math_Lib.UseSign(turnper,Math_Lib.GetSign(HdgIntercept-(Angles)weapanim->hdg));

							if(turnper > AbsAngle(PitchIntercept-(Angles)weapanim->pitch))
								weapanim->pitch = PitchIntercept;
							else
								weapanim->pitch+=(Angles)Math_Lib.UseSign(turnper,Math_Lib.GetSign(PitchIntercept-(Angles)weapanim->pitch));

							if((!weapanim->LaunchTime) && (weapanim->hdg == SWord(HdgIntercept)) && (weapanim->pitch == SWord(PitchIntercept)))
							{
								if (weapitem->Status.size == AIRSTRUCSIZE)//RJS 09Jul99
								{
//DeadCode DAW 27Oct00 									SWord error = Math_Lib.rnd(1024 - 3 * AirStrucPtr(weapitem)->ai.combatskill);
									SWord error = ((255 - AirStrucPtr(weapitem)->ai.combatskill) * 2) / 1;
									GlobHdgInt   += Angles((-1 + 2 * Math_Lib.rnd(2)) * error);
									GlobPitchInt += Angles((-1 + 2 * Math_Lib.rnd(2)) * error);
								}

								Float sin, cos;
								Math_Lib.high_sin_cos(GlobPitchInt, sin, cos);
								vy = aaaparams->muzzelvel * sin + Vgun.Y;
								FP vh = aaaparams->muzzelvel * cos;
								Math_Lib.high_sin_cos(GlobHdgInt, sin, cos);
								vx = vh * sin + Vgun.X;
								vz = vh * cos + Vgun.Z;

								SLong time = 10000 * dt;
								if(aaaparams->lifetime != SPECIALLIFE)
									time = aaaparams->lifetime;

								if (trg->Status.size==AIRSTRUCSIZE && weapitem->Status.size==FORMATIONSIZE) //JIM 12/04/99
									WarnSmallBore(*weapitem,*trg);											//JIM 12/04/99

								_Miles.PlayOnce(aaaparams->sfx,weapitem);	//RJS 27Sep00
								if (weapitem->Status.size == AIRSTRUCSIZE)//RJS 09Jul99
								{
//DeadCode CSB 30Jun00 									SWord error = 2048 - Math_Lib.rnd(4 * AirStrucPtr(weapitem)->ai.combatskill);
//DeadCode CSB 30Jun00 									GlobHdgInt   += Angles((-1 + 2 * Math_Lib.rnd(2)) * error);
//DeadCode CSB 30Jun00 									GlobPitchInt += Angles((-1 + 2 * Math_Lib.rnd(2)) * error);

									//Launch a bullet every 10th of a second
									Trans_Obj.ClearWeaponChain((mobileitem*)weapitem);
//DEADCODE CSB 05/04/00 									SLong	nobullets = aaaparams->reloadtime / 10;
//DEADCODE CSB 23/05/00 									SLong nobullets = 4;//(Timer_Code.FRAMETIME * SUBLISTSIZE) / aaaparams->reloadtime;
									SLong nobullets = 2;				//CSB 20Jun00
									if(AirStrucPtr(weapitem)->nationality == NAT_RAF)
										nobullets *= 4;
									SLong delaybetweenbullets = 4;		//RJS 24May00
									//Clone gun could potentially be vaped by KillOldest
									Trans_Obj.LaunchSuperLauncher
									(
										weapitem,
										aaaparams->shapenum,
										time,
										aaaparams->movecode,
										weapoff,
										GlobHdgInt,
										GlobPitchInt,
										vx, vy, vz, aaaparams->muzzelvel, aaaparams->nat, //CSB 09/11/99
										weapnum,				//leftgun
										weapnum,				//rightgun
										delaybetweenbullets,			//CSB 20/04/00
										nobullets,
										weapanim->LauncherType,
										*mobileitem::currworld
									);
								}
								else
								{
								//This could potentially be vaped by KillOldest
									Trans_Obj.LaunchUnguidedMissile
									(	weapitem,
										aaaparams->shapenum,
										time,
										aaaparams->movecode,
										weapoff,
										GlobHdgInt,
										GlobPitchInt,
										vx, vy, vz, aaaparams->muzzelvel, aaaparams->nat
									); //CSB 09/11/99
								}

								weapanim->LaunchTime=aaaparams->reloadtime;
							}
//#define PRINT_AAA_TRACKING
#ifdef PRINT_AAA_TRACKING
static SLong tx = 0;
static SLong ty = 0;
static SLong gx = 0;
static SLong gy = 0;
PrintString(tx-1, ty-1,   "   ");
PrintString(tx-3, ty,   "       ");
PrintString(gx-1, gy-1, "   ");
PrintString(gx-2, gy,   " "    );
PrintString(gx+2, gy,       " ");
PrintString(gx-1, gy+1, "   ");

tx =  0 + (80 * SWord(HdgIntercept   - aaaparams->minhdg))   / SWord(ANGLES(aaaparams->hdgrange));
ty = 25 - (25 * SWord(PitchIntercept - aaaparams->minpitch)) / SWord(ANGLES(aaaparams->pitchrange));
PrintString(tx-1, ty-1,   "_|_");
PrintString(tx-3, ty,   "___O___");

gx =  0 + (80 * SWord(Angles(weapanim->hdg)   - aaaparams->minhdg))   / SWord(ANGLES(aaaparams->hdgrange));
gy = 25 - (25 * SWord(Angles(weapanim->pitch) - aaaparams->minpitch)) / SWord(ANGLES(aaaparams->pitchrange));
PrintString(gx-1, gy-1,  "-+-");
PrintString(gx-2, gy,   "+"    );
PrintString(gx+2, gy,       "+");
PrintString(gx-1, gy+1, "-+-");
#endif
						}
						else	//Target outside range of gun movement
							weapanim->target = UID_Null;
					}
				}
				else
				{
//DEADCODE CSB 28/02/00 				//	find target - starting where last launcher left off
//DEADCODE CSB 28/02/00 **************					ItemPtr	trg=targlist.Next();
					TrgListProc		targlist(aaaparams->guntype,aaaparams->nat,sleeplist.aaalist,aaalist);	//assume all a/c use same detect routines
					ItemPtr trg = targlist.Next();
					while (trg)
					{
//DEADCODE DAW 01/06/99 						if (!!(weapitem->World.Y<Land_Scape.CloudAlt())==!!(trg->World.Y<Land_Scape.CloudAlt()))
						if(		(!trg->Status.deadtime)
							&&	(	(weapitem->Status.size == AIRSTRUCSIZE)
								||	(trg->Status.size != AIRSTRUCSIZE)
								||	(!AirStrucPtr(trg)->ai.attacker)	)	)
//DeadCode CSB 22Aug00 								||	(AirStrucPtr(trg)->movecode != AUTO_COMBAT)
//DeadCode CSB 22Aug00 								||	(AirStrucPtr(trg)->ai.unfriendly == NULL)	)	)
						//	look for anything within tracking range + rel hdg bias
						{
							if(trg == Persons2::PlayerSeenAC)
								trg = Persons2::PlayerGhostAC;

							Coords3D* trgpos=_DPlay.GetGoodACPosition(trg);

							if (	(Math_Lib.AbsSign(trgpos->X-weapitem->World.X) < aaaparams->flatrange)
								&&	(Math_Lib.AbsSign(trgpos->Z-weapitem->World.Z) < aaaparams->flatrange)
								&&	(trgpos->Y > weapitem->World.Y + aaaparams->minalt)
								&&	(trgpos->Y < weapitem->World.Y + aaaparams->minalt + aaaparams->altrange)
//DeadCode CSB 14Aug00 								&&	(Math_Lib.rnd() < RND50PC)
								&& !((aaaparams->shapenum == BFLAK) && (trg->Status.size == AIRSTRUCSIZE) && (Art_Int.CountFormationSize(AirStrucPtr(trg)) < 6))	)
							{
								weapitem->InterceptandRange(trgpos);
								SWord hi = weapitem->HdgIntercept;
								SWord pi = weapitem->PitchIntercept;
								if(weapitem->Status.size >= MOBILESIZE)
								{
									MobileItemPtr mob = MobileItemPtr(weapitem);
									hi -= mob->hdg;
									pi -= mob->pitch;
								}
								hi = hi - SWord(ANGLES(aaaparams->minhdg));
								pi = pi - SWord(ANGLES(aaaparams->minpitch));
								if(		((hi > 0) && (hi < UWord(ANGLES(aaaparams->hdgrange))))
									||	(SWord(ANGLES(aaaparams->hdgrange)) == SWord(ANGLES_FIDDLEMAX))	)
									if((pi > 0) && (pi < UWord(ANGLES(aaaparams->pitchrange))))
									{
										nothingthere = FALSE;
										targetting = true;
										weapanim->target = trg->uniqueID.count;
										//clean everything up ready to lock and load...
										weapanim->hdg = aaaparams->minhdg + Angles(ANGLES(aaaparams->hdgrange) / 2);
										weapanim->pitch = aaaparams->minpitch + Angles(ANGLES(aaaparams->pitchrange) / 2);
										weapanim->LaunchTime = 0;
										break;
									}
							}
							else
							if (	(Math_Lib.AbsSign(trgpos->X-weapitem->World.X) < aaaparams->flatrange + HALFVISIBLERANGE)
								&&	(Math_Lib.AbsSign(trgpos->Z-weapitem->World.Z) < aaaparams->flatrange + HALFVISIBLERANGE)	)
									nothingthere=FALSE;
						}
						trg=targlist.Next();
					}
					trg=targlist.Next();
				}

//DEADCODE CSB 28/02/00 if(weapanim->LauncherType == LT_LUF_REARTOP)
//DEADCODE CSB 28/02/00 	PrintVar(55, 3, "AMMO %.0f ", FP(weapanim->LoadedStores));

				weapnum++;
				weapanim=SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN);//RDH 31Jul98
				if (weapanim)
					aaaparams = &aaaguntypelist[weapanim->LauncherType - LT_MOVEGUN];
			}
			if (nothingthere)
			{
				operator-=(weapitem);
				sleeplist+=weapitem;
				targetting=true;
			}
		}
		else
		{	//its an event item
			TrgListProc		targlist(AAA_ANTIAIRCRAFT,(Nationality)GR_NAT_ENEMY,NULL,NULL);	//assume all a/c use same detect routines
			ItemPtr	trg=targlist.Next();
			while (trg)
			{
				weapitem->InterceptandRange(trg);
				if (trg->Range</*METRES*/4000000)						//JIM 15Dec96
				{
//TEMP					Persons_2.PossibleEvent(weapitem,trg);	 //No event items in BOB or MIG
					AaaMainList::operator -=(weapitem);
					sleeplist-=weapitem;
				}
				trg=targlist.Next();
			}
		}
		if (!targetting)
		{
			weapanim=SHAPE.GetWeaponLauncher(weapitem,0,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN);//RDH 31Jul98
			if (weapanim && !weapanim->target)
			{
				weapanim->LaunchTime++;
			}
		}
	}
}



void	TransObj::SeenFlak(TransientItemPtr transit)
{
//DEADCODE RDH 19/04/00 	ItemPtr	l=transit->Launcher;
//DEADCODE RDH 19/04/00 	Nationality	nat=(Nationality)GR_NAT_FRIEND;
//DEADCODE RDH 19/04/00 	DOLAUNCHER_PTR d=(DOLAUNCHER_PTR)SHAPE.GetLauncherPos(l->shape,0);
//DEADCODE RDH 19/04/00 	if (d)
//DEADCODE RDH 19/04/00 	{
//DEADCODE RDH 19/04/00 		AaaParams* a=&aaaguntypelist
//DEADCODE RDH 19/04/00 						[	d->lnchrtype-LT_MOVEGUN	];
//DEADCODE RDH 19/04/00 		nat=a->nat;
//DEADCODE RDH 19/04/00 		l->despos=transit->World;
//DEADCODE RDH 19/04/00 		if (nat==GR_NAT_FRIEND)
//DEADCODE RDH 19/04/00 		{
//DEADCODE RDH 19/04/00 
//DEADCODE RDH 19/04/00 //TEMP			if (nat!=NAT_RED)
//DEADCODE RDH 19/04/00 //TEMP				Persons_2.AddMessage(UserMsg::SIGHTED,TEXT_ALLIEDFLAKSIGHTED,l->despos);
//DEADCODE RDH 19/04/00 //TEMP			else
//DEADCODE RDH 19/04/00 //TEMP				Persons_2.AddMessage(UserMsg::SIGHTED,TEXT_GERMANFLAKSIGHTED,l->despos);
//DEADCODE RDH 19/04/00 			if (Manual_Pilot.ControlledAC2->movecode<AUTO_PRECOMBAT)
//DEADCODE RDH 19/04/00 				_Miles.SequenceAudible(FIL_MUSIC_FLAK);
//DEADCODE RDH 19/04/00 
//DEADCODE RDH 19/04/00 		}
//DEADCODE RDH 19/04/00 	}

}

void	LiveList::BackupSleepList()
{
	sleeplistbackup.aaaind=sleeplist.aaaind;
	AaaSubList	*slp,*slb,*sl;
	sl=sleeplist.aaalist;
	slp=NULL;
	slb=NULL;
	if (sleeplistbackup.aaalist)
	{
		slb=sleeplistbackup.aaalist;
		do{
			AaaSubList	*sl=slb->next;
			delete slb;
			slb=sl;
		}while(slb!=sleeplistbackup.aaalist);
	}
	if (sl)
	do{
		slb=new AaaSubList;
		*slb=*sl;
		sl=sl->next;
		if (!slp)
			sleeplistbackup.aaalist=slb;
		else
			slp->next=slb;
		slp=slb;
	}while (sl && sl!=sleeplist.aaalist);
	if (sl)
		slb->next=sleeplistbackup.aaalist;

}
int		LiveList::ArchiveLiveList(UWord* archive,int archivesize,int skipsize)
{	//for each entry in live list:
	//	Transmit it's ID and all target IDs
	//
	int lastfullsize=0;
	AaaSubList* list=aaalist;
	int listind=0;
	if (list)
	do{
		if (!list[0][listind])
			if (skipsize)
				skipsize-=1;								 //skipping
			else
				if (lastfullsize==archivesize)
					return -lastfullsize;
				else
					archive[lastfullsize++]=0;					//empty slot
		else
		{
			ItemPtr weapitem=list[0][listind];
			Coords3D		weapoff;
			int				weapnum=0;
			ULong			mvel;								//RJS 12Nov99
			UWord			mdelay,mburst;						//RJS 12Nov99

			while (SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN))
				weapnum++;
			if (skipsize)
				skipsize-=weapnum+1;							//skipping
			else
				if (lastfullsize+weapnum+1>archivesize)
					return (-lastfullsize);					//signal list already full
				else
				{											//put entry in list
					archive[lastfullsize++]=weapitem->uniqueID.count;
					WeapAnimData* w;
					weapnum=0;
					for(weapnum=0;((w=SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN))!=NULL);weapnum++)
						archive[lastfullsize++]=w->target;						
				}
		}
		listind++;
		if (listind==SUBLISTSIZE)
		{
			listind=0;
			list=list->next;

		}
	}while (list && (listind || list!= aaalist));
	return lastfullsize;
}
void	LiveList::RestoreSleepList()
{
	AaaSubList	*slp,*slb,*sl;
	sl=sleeplist.aaalist;	//delete main sleep list
	if (sl)
	do{
		slb=sl->next;
		delete sl;
		sl=slb;
	}while (sl && sl!=sleeplist.aaalist);
	sl=aaalist;
	if (sl)				//delete main live list
	do{
		slb=sl->next;
		delete sl;
		sl=slb;
	}while (sl && sl!=aaalist);
	aaalist=new AaaSubList;
	aaaind=0;

	sleeplist.aaaind=sleeplistbackup.aaaind;
	sl=sleeplistbackup.aaalist;
	slp=NULL;
	slb=NULL;
	if (sl==NULL)
	   sleeplist.aaalist=NULL;
	else
	do{
		slb=new AaaSubList;
		*slb=*sl;
		sl=sl->next;
		if (!slp)
			sleeplist.aaalist=slb;
		else
			slp->next=slb;
		slp=slb;
	}while (sl && sl!= sleeplistbackup.aaalist);
	if (sl)
		slb->next=sleeplist.aaalist;
}
void	LiveList::ApplyLiveList(UWord* archive,int archivesize)
{
	//for each item in archive, 
	//	remove from sleep list, 
	//	add to live list
	//	for each weapanim
	//		set target
	//		reset andgles and shootdelay

	while (archivesize)
	{
		if (aaaind==0)
		{
			bool doit=true;
			if (aaalist[0].next==aaalist)
			{
				int check;
				for (check=0;check<SUBLISTSIZE;check++)
					breakif (aaalist[0][check]);
				if (check==SUBLISTSIZE)
					doit=false;
			}
			if (doit)
			{
				aaaind=0;
				AaaSubList* newlist=new AaaSubList;
				newlist->next=aaalist[0].next;
				aaalist[0].next=newlist;
				aaalist=newlist;
			}
		}

		ItemPtr weapitem;
		if (archive[0])
		{
			weapitem=*Persons2::ConvertPtrUID(UniqueID(archive++[0]));
			archivesize--;
			sleeplist-=weapitem;
			WeapAnimData* w;
			Coords3D		weapoff;
			int				weapnum=0;
			ULong			mvel;								//RJS 12Nov99
			UWord			mdelay,mburst;						//RJS 12Nov99
			while ((w=SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN))!=NULL)
			{
				w->target=UniqueID(archive++[0]);
				archivesize--;
				w->hdg=ANGLES_0Deg;
				w->pitch=ANGLES_45Deg;
				weapnum++;
			}
		}
		else
		{
			weapitem=NULL;
			archivesize--;
			archive++;
		}
		aaalist[0][aaaind]=weapitem;
		aaaind++;
		if (aaaind==SUBLISTSIZE)
			aaaind=0;
			
			
	}
}


bool SleepList::OKtoWakeAAA(ItemPtr item, Nationality nat)
{
	if(!item->SGT)
		return(true);

	if(Persons2::getbandfromUID(item->SGT) != AfFieldBAND)
		return(true);

	ItemPtr itemsgt = Persons2::ConvertPtrUID(item->SGT);

	for(int i = 0; i < Art_Int.ACARRAYSIZE; i++)
		if(Art_Int.ACArray[i])
		{
			AirStrucPtr as = Art_Int.ACArray[i];

			if(as->nationality == nat)
			{
				if(as->ai.homebase == itemsgt)
					if((as->movecode == AUTO_TAKEOFF) || (as->movecode == AUTO_LANDING))
						return(false);
			}
			else
				if(as->movecode == AUTO_BOMB)
					if(as->ai.unfriendly == itemsgt)
						return(false);
		}
	return(true);
}
	

void	shape::GetGunClip(	SLong	launcher,
							SWord&	minHdg,
							SWord&  arcHdg,
							SWord&	minPitch,
							SWord&	arcPitch	)
{
	AaaParams* a=&aaaguntypelist[launcher-LT_MOVEGUN];

	minHdg = ANGLES(a->minhdg);
	arcHdg = ANGLES(a->hdgrange);

	minPitch = ANGLES(a->minpitch);
	arcPitch = ANGLES(a->pitchrange);
}
