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

///------------------------------------------------------------------------------
//Filename	transite.cpp
//System
//Author	 Martin Alderton
//Date		Thu 22 Feb 1996
//Description	TransientItem routines.
//------------------------------------------------------------------------------
//NOT INITIALISED!!!			lrstate /= 85;										//RJS 21Feb97

#ifndef	NDEBUG
//#define	_NO_RADIOCHATTER_
//#define	_SOUND_TEST_
//#define	DBGMEMTEST
//#define	_CACHE_CHECK_
//#define	_BOMBBUG_
//#define	_DEADGUN_
#endif

#define	ANGLES_MATHABLE
#define F_GRAFIX												//DAW 05Aug96
#define F_BATTLE
#include	"dosdefs.h"
#include	"worldinc.h"

#include	"world.h"											//MGA 27Feb96
#include	"myerror.h"


#include	"transite.h"
#include	"shapes.h"
#include	"myangles.h"
#include	"LandScap.h"										//MGA 29Mar96
#include	"MyTime.h"											//PD 26Apr96
#include	"collided.h"										//PD 29Apr96
//MATHABLE	(ANGLES);
#include	"mymath.h"
#include	"miles.h"											//RJS 05Nov99
#include	"3dcom.h"
#include	"missman2.h"										//RDH 03Oct96
#include	"viewsel.h"											//MGA 22Mar96
#include	"keytest.h"											//PD 29Apr96
//#include	"3dinstr.h"											//PD 01May96
#include	"flymodel.h"										//PD 02May96

#include	"persons2.h"
#include	"files.g"
#include	"deathnum.g"										//RJS 29Jul96
#include "bitfield.h"											//DAW 23Aug96
//#include	"misssub.h"										//RJS 08Aug96
#include	"savegame.h"										//PD 02Sep96
#include	"boxcol.h"										//PD 02Sep96
#include	"ranges.h"										//PD 02Sep96
#include	"Mytime.h"										//PD 02Sep96
#include	"speed.h"											//RJS 15Dec96
#include	"modinst.h"
#include	"model.h"											//RJS 08Apr98
#include	"3dcode.h"
#include	"winmove.h"											//ARM 05Sep96
#include	"ai.h"
#include	"rchatter.h"										//RJS 11Jun98
#include	"globrefs.h"
#include	"shapenam.h"										//RJS 20Nov98
#include	"overlay.h"

#include	"anmradio.h"
#include	"animmove.h"										//RJS 21Dec99
#include	"transxtr.h"										//RJS 17Nov99
//#include	"fastmath.h"										//RJS 14Dec99
#include "airstruc.h"											//RJS 14Dec99
#include	"sqddiary.h"										//RJS 18Feb00	
#include	"fastmath.h"
#include	"replay.h"
#include	"matrix.h"
#include "migland.h"
int firstroll = NULL;								//MGA 03Apr96
//extern	ULong	GR_Quit3DNow,									//JIM 05Dec96
//				GR_NAT_FRIEND									//JIM 05Dec96
				;												//JIM 05Dec96

//DeadCode CSB 10Aug00 inline void	animptr::SetItemState(const int theState)
//DeadCode CSB 10Aug00 {
//DeadCode CSB 10Aug00 #ifndef	NDEBUG
//DeadCode CSB 10Aug00 	assert ((ptr!=NULL) && (size!=0));
//DeadCode CSB 10Aug00 #endif
//DeadCode CSB 10Aug00 	((MinAnimData*)ptr)->itemstate = theState;
//DeadCode CSB 10Aug00 }

//#define	_CHUTEFAIL_

TransObj Trans_Obj;
int	TransientItem::transcount=0;
extern void	CheckE3();


const	UWord	PARACHUTE_MASK = 0xFF00;
const	UWord	PARACHUTE_SHIFT = 8;
const	UWord	PARACHUTE_DEAD = 0xF0;
const	UWord	PARACHUTE_CHUTE_OPEN = 0x01;
const	UWord	PARACHUTE_CHUTE_FAILED = 0x02;
const	UWord	PARACHUTE_CHUTE_ESCAPED = 0x04;
const	UWord	PARACHUTE_PHASE_MASK = 0x00FF;
const	UWord	PARACHUTE_PHASE_1 = 127;
const	UWord	PARACHUTE_PHASE_2 = 0;
const	UWord	PARACHUTE_PHASE_3 = 1;
const	UWord	PARACHUTE_PHASE_4 = 2;
const	UWord	PARACHUTE_PHASE_5 = 0xFF;


// This constant is used as a cut-off point for certain fx when the frame-
// rate dips too low
const	int	desiredFPS = 10;									//RJS 16Jun00


inline void	SetBitsOff(const ShapeNum theShape, animptr& oldaptr, animptr& newaptr, const int aoffset)
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(theShape);
	int				index = sdptr->DamageOffset;
	int				bitsend = SHAPE.GetAnimDataSize(theShape);

	while (index < bitsend)	newaptr[index++] = BS_DEAD;

	newaptr[aoffset] = oldaptr[aoffset];
	oldaptr[aoffset] = BS_DEAD;
}









inline int	WeaponID(int	lnchr)
{
	int	masked = lnchr & LT_MASK;
	if (masked == LT_ANYWEAPON)
	{
		if (lnchr == LT_AWCANNON)		//we just tried bullet
			masked = LT_BULLET;
		else
			masked = LT_CANNON;
	}
	
	return masked;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TransObj
//Author		Martin Alderton
//Date			Tue 5 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransObj::TransObj()
{
	TransToGoList=NULL;											//PD 11May96
	shootdelay = DefaultShootDelay;								//PD 29Apr96
	autobulletcount=0;											//PD 29Apr96
	transientcounter = 0;										//PD 24Jul96
	vapourcount = 0;
	fakeshootdelay = 0;											//RJS 21Apr98

	StaticTrailCnt = 0;											//RJS 18Feb99
	StaticTrailIndex = 0;										//RJS 18Feb99
	trailcounter = 0;											//RJS 06Apr99

	HitTheDeck = false;											//RDH 09May99

	realFPS = 0;														//RJS 21Sep00

	raidCount = 0;

	recycleTimer = 200;													//RJS 13Aug00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		~TransObj
//Author		Martin Alderton
//Date			Tue 5 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransObj::~TransObj()
{
	TransToGoList=NULL;				//MGA 27Feb96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Enter3D
//Author		Robert Slater
//Date			Thu 9 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::Enter3D()
{
	raidCount = 0;

	BoxCol::SetTestState(false);										//AMM 4Jul00
}

void	TransObj::SetViewPoint(MobileItem* vp,ViewPoint* vo)
{
	View_Point=vp;
	View_Object=vo;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTransientItemToWorld
//Author		Martin Alderton
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::AddTransientItemToWorld(TransientItemPtr transitem,WorldStuff& world)
{

//TempCode MGA 07Mar96	World_Stuff.AddToWorld(transitem);
	
	world.AddToWorld((itemptr)transitem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTransientItemToDeadList
//LastModified:	RDH 25Jul96
//Author		Martin Alderton
//Date			Tue 27 Feb 1996
//
//Description	This procedure MUST be called from both movecodes and ClearWorld()
//				when a transient is to be killed.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::AddTransientItemToDeadList(TransientItemPtr transitem, bool novapour)
{
	if (!transitem->isOwned && !transitem->isDeleted)
	{
		SLong	newlife = SHAPE.DetatchAllVapourStreams(transitem,400,novapour);//RJS 19May99
		if (newlife > 0)											//RJS 06Apr99
			transitem->LaunchTime = newlife;
		else
		{
// If anyone is pointing to us, free the pointer...
			if (transitem->Target && (transitem->Target->Status.size == TRANSIENTSIZE))//RJS 06Sep00
			{
				TransientItemPtr	theTarg = TransientItemPtr(transitem->Target);
				if (theTarg->Target == transitem)
				{
					theTarg->Target = NULL;
					transitem->Target = NULL;
				}
			}

// Make sure bully linked list is freed up first...
			if (transitem->movecode == MOBILE_DODAMAGE)					//RJS 5Jun00
			{
				if (SHAPESTUFF.GetShapePtr(transitem->shape)->AnimDataSize == MISSILEANIM)
				{
					MissileAnimData*	adptr = (MissileAnimData*) transitem->Anim;
					DeathTollLink*		pDToll = (DeathTollLink*) adptr->lastmissile;

					if (adptr->hitstrength || adptr->frameno)
						delete pDToll;
					else
						INT3;

					adptr->lastmissile = NULL;
					adptr->pad = 1;										//RJS 11Oct00
				}
			}


			transitem->movecode=MOBILE_NOPPILOT;						//RJS 09Dec98
			transientcounter--;											//PD 24Jul96
			TransientItemPtr temp;
			transitem->transcount--;

			transitem->LaunchTime = 0x7FFFFFFF;					//RJS 04Jun99
			transitem->TimeOfLaunch = 0xFFFFFFFF;				//RJS 04Jun99
			transitem->isDeleted = 1;							//RJS 14May99

//if newlife == -1, then this is a transient trail dying...//RJS 06Apr99
			if (newlife)											//RJS 06Apr99
				trailcounter--;										//RJS 06Apr99

			if (View_Object && (View_Object->trackeditem2 == transitem))	//RJS 13Aug00
				View_Object->trackeditem2 = NULL;						//RJS 13Aug00

			_Miles.HaltItemSound(transitem);							//RJS 13Aug00

			if (TransToGoList==NULL)
			{
				TransToGoList=*transitem;
			}
			else
			{
//Debug code to check whether the item has already been added to the dead list

				temp=TransToGoList;

				for(;;)
				{
					if (temp==transitem)
					{
//DeadCode RJS 13Aug00 						_Miles.HaltItemSound((ItemBasePtr) transitem);
						return;
					}

					if (temp->nexttogo)							//RJS 24Mar98
						temp = temp->nexttogo;
					else
					{
						temp->nexttogo = transitem;
						break;
					}
				}
			}

			transitem->nexttogo = NULL;
//DeadCode RJS 13Aug00 			_Miles.HaltItemSound((ItemBasePtr) transitem);
		}
	}
}

//TempCode MGA 27Mar96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode MGA 27Mar96 //Procedure		gettranslist
//TempCode MGA 27Mar96 //Author		Martin Alderton
//TempCode MGA 27Mar96 //Date			Wed 13 Mar 1996
//TempCode MGA 27Mar96 //
//TempCode MGA 27Mar96 //Description	allows access to protected TransientList by transite functions
//TempCode MGA 27Mar96 //
//TempCode MGA 27Mar96 //Inputs		
//TempCode MGA 27Mar96 //
//TempCode MGA 27Mar96 //Returns	
//TempCode MGA 27Mar96 //
//TempCode MGA 27Mar96 //------------------------------------------------------------------------------
//TempCode MGA 27Mar96 TransientItemPtr TransientItem::gettranslist(void)
//TempCode MGA 27Mar96 {
//TempCode MGA 27Mar96	TransientItemPtr retval = new TransientItem;
//TempCode MGA 27Mar96	retval->Launcher	= TransientList->Launcher;
//TempCode MGA 27Mar96	retval->Target		= TransientList->Target;
//TempCode MGA 27Mar96	retval->LaunchTime	= TransientList->LaunchTime;
//TempCode MGA 27Mar96	retval->shape		= TransientList->shape;
//TempCode MGA 27Mar96	retval->Next		= TransientList->Next;
//TempCode MGA 27Mar96	retval->nexttogo	= TransientList->nexttogo;
//TempCode MGA 27Mar96	retval->nextmobile	= TransientList->nextmobile;
//TempCode MGA 27Mar96	retval->nexttrans	= TransientList->nexttrans;
//TempCode MGA 27Mar96	retval->waypoint	= TransientList->waypoint;
//TempCode MGA 27Mar96	retval->movecode	= TransientList->movecode;
//TempCode MGA 27Mar96	retval->roll		= TransientList->roll;
//TempCode MGA 27Mar96	retval->pitch		= TransientList->pitch;
//TempCode MGA 27Mar96	retval->hdg			= TransientList->hdg;
//TempCode MGA 27Mar96	retval->Next		= TransientList->Next;
//TempCode MGA 27Mar96	retval->World		= TransientList->World;
//TempCode MGA 27Mar96	retval->velx		= TransientList->velx;
//TempCode MGA 27Mar96	retval->velz		= TransientList->velz;
//TempCode MGA 27Mar96	retval->vely		= TransientList->vely;
//TempCode MGA 27Mar96	retval->velhori		= TransientList->velhori;
//TempCode MGA 27Mar96	retval->vel			= TransientList->vel;
//TempCode MGA 27Mar96 //TempCode MGA 27Mar96	retval->Anim		= TransientList->Anim;
//TempCode MGA 27Mar96	retval->Status		= TransientList->Status;
//TempCode MGA 27Mar96	retval->uniqueID	= TransientList->uniqueID;
//TempCode MGA 27Mar96	retval->despos		= TransientList->despos;
//TempCode MGA 27Mar96
//TempCode MGA 27Mar96	//I may not yet have all the options covered here			//MGA 26Mar96
//TempCode MGA 27Mar96
//TempCode MGA 27Mar96	return (retval);
//TempCode MGA 27Mar96 }

//DeadCode JIM 07Oct96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 07Oct96 //Procedure		FindInTransientList
//DeadCode JIM 07Oct96 //Author		Martin Alderton
//DeadCode JIM 07Oct96 //Date			Thu 29 Feb 1996
//DeadCode JIM 07Oct96 //
//DeadCode JIM 07Oct96 //Description	
//DeadCode JIM 07Oct96 //
//DeadCode JIM 07Oct96 //Inputs		
//DeadCode JIM 07Oct96 //
//DeadCode JIM 07Oct96 //Returns	
//DeadCode JIM 07Oct96 //
//DeadCode JIM 07Oct96 //------------------------------------------------------------------------------
//DeadCode JIM 07Oct96 int TransObj::FindInTransientList(TransientItemPtr transit)
//DeadCode JIM 07Oct96 {
//DeadCode JIM 07Oct96	int retval=-1;
//DeadCode JIM 07Oct96	int count=0;
//DeadCode JIM 07Oct96
//DeadCode JIM 07Oct96 //TempCode MGA 13Mar96	TransientItemPtr testlist = mobileitem::TransientList;
//DeadCode JIM 07Oct96
//DeadCode JIM 07Oct96	TransientItemPtr testlist;
//DeadCode JIM 07Oct96 //TempCode MGA 27Mar96	testlist=TransientItem::gettranslist();
//DeadCode JIM 07Oct96	testlist=TransientItem::TransientList;
//DeadCode JIM 07Oct96
//DeadCode JIM 07Oct96
//DeadCode JIM 07Oct96	while (testlist!=NULL)
//DeadCode JIM 07Oct96	{
//DeadCode JIM 07Oct96		if (testlist->uniqueID.count==transit->uniqueID.count)
//DeadCode JIM 07Oct96		{
//DeadCode JIM 07Oct96			retval=count;
//DeadCode JIM 07Oct96		}
//DeadCode JIM 07Oct96		testlist=testlist->nexttrans;
//DeadCode JIM 07Oct96		count++;
//DeadCode JIM 07Oct96	}
//DeadCode JIM 07Oct96	return(retval);
//DeadCode JIM 07Oct96 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillTheDeadList
//Author		Martin Alderton
//Date			Thu 29 Feb 1996
//
//Description	removes the list of dead transients from the transient	list
//				and the world.
//				
//				Must not be performed during 3d-draw (object may get reallocated)
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::RemoveDeadListFromWorld()
{
#ifdef	DBGMEMTEST
	TransientItemPtr	tmpentry = TransientItem::TransientList;
	while (tmpentry)
	{
		DbgMemTest2(tmpentry);
		tmpentry->Anim.MemTest();
		tmpentry = tmpentry->nexttrans;
	}
#endif

	WorldStuff &world=*MobileItem::currworld;
	if (transientcounter>MaxTransients)	KillOldest();			//PD 24Jul96

	TransientItemPtr Ptr = TransientItem::TransientList;
	TransientItemPtr TempPtr = TransToGoList;
	TransientItemPtr NextToGo = NULL;

	TransientItemPtr remove = NULL;
	TransientItemPtr lastitem = NULL;
															
//DeadCode RJS 11Nov98	SHAPE.KillVapourStreamDeadList();							//RJS 09Apr98


	while (TempPtr)
	{
		NextToGo = TempPtr->nexttogo;

		lastitem =
			remove = Ptr;

		while (remove!=TempPtr)
		{
			lastitem = remove;
			remove = remove->nexttrans;
		}

		if (lastitem==remove)
			Ptr = remove->nexttrans;
		else
		{
			lastitem->nexttrans = remove->nexttrans;
		}
		world.RemoveFromWorld((itemptr)remove);

		delete (remove);

		TempPtr = NextToGo;
	}

	TransientItem::TransientList = Ptr;

	TransToGoList=NULL;

// Recycle dead aircraft...

//TempCode RJS 14Aug00 	if (View_Object)
//TempCode RJS 14Aug00 	{
//TempCode RJS 14Aug00 		recycleTimer -= View_Object->FrameTime();							//RJS 13Aug00
//TempCode RJS 14Aug00 		if (recycleTimer <= 0)												//RJS 13Aug00
//TempCode RJS 14Aug00 		{
//TempCode RJS 14Aug00 			recycleTimer = 200;
//TempCode RJS 14Aug00 
//TempCode RJS 14Aug00 			MobileItemPtr	acptr = mobileitem::ACList;
//TempCode RJS 14Aug00 			while (acptr)
//TempCode RJS 14Aug00 			{
//TempCode RJS 14Aug00 				MinAnimData*	mad = (MinAnimData*)acptr->Anim;
//TempCode RJS 14Aug00 	//			if (	mad->IsInvisible
//TempCode RJS 14Aug00 	//				&&	(acptr != Persons2::PlayerSeenAC)
//TempCode RJS 14Aug00 	//				&&	(acptr->movecode != AUTO_NOPPILOT)	)
//TempCode RJS 14Aug00 
//TempCode RJS 14Aug00 				acptr = acptr->nextmobile;
//TempCode RJS 14Aug00 			}
//TempCode RJS 14Aug00 		}
//TempCode RJS 14Aug00 	}

#ifdef	DBGMEMTEST
	tmpentry = TransientItem::TransientList;
	while (tmpentry)
	{
		DbgMemTest2(tmpentry);
		tmpentry->Anim.MemTest();
		tmpentry = tmpentry->nexttrans;
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillOldest
//Author		Paul.
//Date			Wed 24 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::KillOldest()
{
	SLong	trans2kill = transientcounter - MaxTransients;

//DeadCode DAW 19May99 	while (trans2kill--)
//DeadCode DAW 19May99 	{
//DeadCode DAW 19May99 		TransientItemPtr tip,otp;
//DeadCode DAW 19May99 		
//DeadCode DAW 19May99 		tip = otp = TransientItem::TransientList;
//DeadCode DAW 19May99 
//DeadCode DAW 19May99 		tip = tip->nexttrans;
//DeadCode DAW 19May99 
//DeadCode DAW 19May99 		while (tip)
//DeadCode DAW 19May99 		{
//DeadCode DAW 19May99 			if (tip->LaunchTime<otp->LaunchTime)
//DeadCode DAW 19May99 				otp = tip;
//DeadCode DAW 19May99 
//DeadCode DAW 19May99 			tip = tip->nexttrans;
//DeadCode DAW 19May99 		}
//DeadCode DAW 19May99 
//DeadCode DAW 19May99 		otp->LaunchTime = 0x7FFFFFFF;
//DeadCode DAW 19May99 
//DeadCode DAW 19May99 		AddTransientItemToDeadList(otp);
//DeadCode DAW 19May99 	}

	while (trans2kill--)
	{
		TransientItemPtr tip;
		TransientItemPtr oldestdeletable;
		TransientItemPtr oldest;
		
		tip = oldestdeletable = oldest = TransientItem::TransientList;

		tip = tip->nexttrans;

		while (tip)
		{
			if (	!tip->isDeleted	&& !tip->isOwned
				&&	(tip->TimeOfLaunch < oldestdeletable->TimeOfLaunch)	)
			{
				oldest = tip;
				if (!tip->isArmed)
					oldestdeletable = tip;
			}

			tip = tip->nexttrans;
		}

		//Did we find anything to kill???
		if (oldestdeletable == TransientItem::TransientList)		//RJS 02Jul99
			break;
		else
			AddTransientItemToDeadList(oldestdeletable,true);		//RJS 19May99
	}

	//Has to be called after KillOldest!!!!!!!!!!!!!
	SHAPE.GenerateProbeTrails();								//RJS 19May99
	SHAPE.KillVapourStreamDeadList();							//RJS 19May99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CountTheTransients
//Author		Martin Alderton
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int TransObj::CountTheTransients(TransientItemPtr trans)
{
	int counter=0;
	TransientItemPtr translist;
	translist=trans;

	while (translist!=NULL)
	{
		counter++;
		translist=translist->nexttrans;
	}

	translist=NULL;
	return(counter);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CountTheDeadTransients
//Author		Martin Alderton
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int TransObj::CountTheDeadTransients(TransientItemPtr trans)
{
	int counter=0;
	TransientItemPtr translist;
	translist=trans;

	while (translist!=NULL)
	{
		counter++;
		translist=translist->nexttogo;
	}

	translist=NULL;
	return(counter);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteTransientItem
//Author		Martin Alderton
//Date			Thu 22 Feb 1996
//
//Description	for use deleting from master TransientList
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItemPtr TransObj::DeleteTransientItem(TransientItemPtr translist)
{
	TransientItemPtr temp;
	temp = translist->nexttrans;

	delete translist;

	return(temp);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteTransientItem
//Author		Martin Alderton
//Date			Thu 22 Feb 1996
//
//Description	for use with TransToGoList
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItemPtr TransObj::DeleteTempTransientItem(TransientItemPtr translist)
{
	TransientItemPtr temp;

	temp = translist->nexttogo;

//TempCode MGA 27Mar96	delete translist;

	return (temp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteAll
//Author		Martin Alderton
//Date			Thu 22 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::DeleteAll()
{
	//Clear world frees the items so all that needs doing
	//is emptying the list
	TransientItem::transcount=0;
	TransToGoList=NULL;											//PD 11May96
	shootdelay = DefaultShootDelay;								//PD 29Apr96
	autobulletcount=0;											//PD 29Apr96
	transientcounter = 0;										//RJS 21Aug96
	trailcounter = 0;											//RJS 06Apr99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRand
//Author		Martin Alderton
//Date			Tue 2 Apr 1996
//
//Description	gets a rnd from mathlib. returns a no between 1 and 6.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int TransObj::GetRand()
{
	int retval;
	UWord temp;

	temp = Math_Lib.rnd(6);

	retval = temp + 1;

	return(retval);
}
extern	FastMath fastMath;
inline SLong F3DDistance(const SLong& a,const SLong& b,const SLong& c)
{
	SLong	dist;
	Float	fa = Float(a);
	Float	fb = Float(b);
	Float	fc = Float(c);

	fastMath.FloatToInt(&dist,fastMath.FastSqrt(float((fa*fa)+(fb*fb)+(fc*fc))));

	return dist;
}

inline Float F3DDistance(const Float& a,const Float& b,const Float& c)
{
	return fastMath.FastSqrt(float((a*a)+(b*b)+(c*c)));
}

inline	float	DistanceSquared(const SLong& a, const SLong& b, const SLong& c)
{
	float	fa = float(a);
	float	fb = float(b);
	float	fc = float(c);

	return fa*fa+fb*fb+fc*fc;
}

inline	bool	WithinRange(const SLong& a, const SLong& b, const SLong& c, const SLong& range)
{
	return bool(DistanceSquared(a,b,c)<(float(range)*float(range)));
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileCarpetStrike
//Author		Robert Slater
//Date			Mon 31 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileCarpetStrike(TransientItemPtr transit,WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;
	
	if (timeleft > 0)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)		//DAW 31Jul96
			transit->LaunchTime=0;

		timeleft = transit->TransRandom;
		timeleft -= Timer_Code.FRAMETIME;
		if (timeleft <= 0)
		{
			//Explode...
			Coords3D hitcoords;
			Coords3D oldhitcoords;
			UByte	theArea;
			itemptr	hititem;
			int		gindex;
#ifndef NDEBUG
#ifdef CARPETTRACE
// defined in rchatter.h
	UWord cw=GETFPCW();
	::AfxTrace("...strike 0x%x\n",transit);
	SETFPCW(cw);
#endif
#endif
			
			oldhitcoords = transit->World;
			transit->World.X += Math_Lib.rnd(2000) - 1000;
			transit->World.Z += Math_Lib.rnd(2000) - 1000;
			transit->World.Y = GetGroundLevel(transit,theArea) + METRES01;

			hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);
			if (!hititem)
			{
				hitcoords = transit->World;
				DoImpactGround(transit,hitcoords,theArea);
			}

			transit->World = oldhitcoords;
			transit->TransRandom = transit->TmpLaunchTime;
		}
		else
			transit->TransRandom = timeleft;

		if (transit->LaunchTime>0)	
			GAndFriction(transit,0);
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileCrater
//Author		Martin Alderton
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileCrater(TransientItemPtr transit,WorldStuff&)//PD 26Apr96
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		NoGravityAndFriction(transit,RetardedDrag);
//DeadCode RJS 18Jun98		GAndFriction(transit,RetardedDrag,100);

		SLong	groundheight = GetGroundLevel(transit);			//RJS 14Apr99
		if (transit->World.Y <= groundheight)
			transit->World.Y = groundheight;
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileNoExplosion
//Author		Martin Alderton
//Date			Wed 20 Mar 1996
//
//Description	puts unwanted transients in dead list
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileSink(TransientItemPtr transit,WorldStuff& worldptr)
{
	SLong	timeleft = transit->LaunchTime;
//DeadCode RJS 20Oct00 	UWord	roff = transit->TransRandom;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		SWord			roll,pitch;
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(transit->shape);
		SLong			size = sdptr->Size << 4;

//DeadCode RJS 18Sep00 		roll = roff & 0xF000;
//DeadCode RJS 18Sep00 		roll >>= 12;
//DeadCode RJS 18Sep00 		pitch = roll & 3;
//DeadCode RJS 18Sep00 
//DeadCode RJS 18Sep00 		roll >>= 2;

		//after 4 secs, should have tilted 90deg...
//DeadCode RJS 18Sep00 		if (roll < 0)
//DeadCode RJS 18Sep00 			roll--;
//DeadCode RJS 18Sep00 		else
//DeadCode RJS 18Sep00 			roll++;
//DeadCode RJS 18Sep00 
//DeadCode RJS 18Sep00 		roll *= 40;
//DeadCode RJS 18Sep00 
//DeadCode RJS 18Sep00 		if (pitch < 0)
//DeadCode RJS 18Sep00 			pitch--;
//DeadCode RJS 18Sep00 		else
//DeadCode RJS 18Sep00 			pitch++;
//DeadCode RJS 18Sep00 
//DeadCode RJS 18Sep00 		pitch *= 30;

//DeadCode RJS 18Sep00 		transit->roll += (Angles) roll;	

// after 4 secs, should have tilted 90 deg...
// sink destroyer (4960 cm in length) after 10 secs...

		SWord	degreesperframe = (ANGLES_90Deg * Timer_Code.FRAMETIME)/400;	//RJS 18Sep00
		SLong	ysinkperframe = (4960 * Timer_Code.FRAMETIME)/1000;	//RJS 18Sep00

		pitch = transit->pitch;
		if (pitch < ANGLES_80Deg)
			pitch += degreesperframe;
		
		transit->pitch = Angles(pitch);									//RJS 18Sep00
		transit->World.Y -= ysinkperframe;								//RJS 18Sep00

		LaunchBubbles(transit,size,worldptr);
	}
	else
	{
//DeadCode RJS 4Oct00 		// Remove the transient bridge element, and turn on the real bridge element to dead....
//DeadCode RJS 4Oct00 		MinAnimData*	mad;
//DeadCode RJS 4Oct00 		animptr			adptr = transit->Launcher->Anim;
//DeadCode RJS 4Oct00 														
//DeadCode RJS 4Oct00 		adptr += (roff & 0x0FFF);						
//DeadCode RJS 4Oct00 
//DeadCode RJS 4Oct00 		mad = (MinAnimData*) adptr;						
//DeadCode RJS 4Oct00 		mad->IsInvisible = 0;

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDummyExplosion
//Author		Martin Alderton
//Date			Wed 20 Mar 1996
//
//Description	used to initialise TransientList. i.e. does nowt visually
//				and not even used to do this so not much use all round//MGA 29Mar96
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchDummyExplosion(mobileitem input)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDitchEffect
//Author		Martin Alderton
//Date			Thu 29 Feb 1996
//
//Description	sets up a transientitem
//
//Inputs		a rotitem giving initial position
//				does not require a target as target is always same as launcher value
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchDitchEffect(mobileitem input,WorldStuff& worldptr)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchCrater
//Author		Martin Alderton
//Date			Thu 29 Feb 1996
//
//Description	sets up a transientitem
//
//Inputs		a rotitem giving initial position
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchCrater(mobileitem *input,WorldStuff &worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(input,CraterShape,3000,MOBILE_STATIONARY);//RJS 12Jun98

	if (newitem)
	{
		// Make very old, so lowest priority transient...
		newitem->TimeOfLaunch -= 3000;

		newitem->TransRandom = 0;

		AddTransientItemToWorld(newitem,worldptr);
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//				Specific launch code for transients
//
////////////////////////////////////////////////////////////////////////////////


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayGunSound
//Author		R. Hyde
//Date			Thu 18 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::PlayGunSound(mobileitem* launcher,WorldStuff& worldptr)
{
	FormationItemPtr flauncher = *launcher;

	if ((flauncher == Manual_Pilot.ControlledAC2) && !_Replay.Playback)	//RJS 22Apr99
	{
		int	cptIndex = SHAPE.GetCockpitIndex();							//RJS 9Jun00

		if (_Miles.StartShooting(flauncher->classtype->gunsnd[cptIndex],flauncher->classtype->gundelay,flauncher->classtype->gunfrequency))//RJS 31May99
			_Miles.PlayLooped(flauncher->classtype->gunsnd[cptIndex], (ItemBasePtr) launcher, 128, 0, FALSE);//RJS 01Jun99
	}
	else
	{
// Slot 4 is reserved for one-shot mini-loops...
		_Miles.PlayOnce(flauncher->classtype->gunsnd[4], (ItemBasePtr) launcher);	//RJS 31Jul00
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DropOneBomb
//Author		R. Hyde
//Date			Mon 23 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord	TransObj::DropOneBomb (mobileitem* launcher,WorldStuff& world)
{
	SWord	retval =-1;												//RJS 17Jun99
	AirStrucPtr	ac = (AirStrucPtr) *launcher;
	SLong	timeleft = ac->weap.ShootDelay-Timer_Code.FRAMETIME;//RJS 05May99
	if (timeleft<0)
	{
		retval =0;													//RJS 17Jun99

		WeapAnimData*	weapon;										//RJS 29Aug96
		SLong			xpos, ypos, zpos;							//RJS 29Aug96
		UByte			index;										//RJS 29Aug96
		UWord			thisstore;									//RJS 10Sep96
		ULong			mvel;										//RJS 12Nov99
		UWord			mdelay = Timer_Code.FRAMETIME;				//RJS 05May99
		UWord			mburst;										//RDH 31Jul98
		UWord			weaponshape = BOMB;							//MS 20May99
		ShapeDescPtr	sdptr=SHAPESTUFF.GetShapePtr(ac->shape);	//RJS 08Dec99

		if (SHAPESTUFF.GetShapeScale(sdptr) != SHP_GRP)
		{
			for (index = 0; index < MAX_WEAP_LAUNCHERS; index++)	//RJS 15Nov99
			{
				weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BOMB,&weaponshape);//RJS 20May99
				if (weapon)
				{
					timeleft = mdelay;									//RJS 05May99
					if (weapon->LoadedStores > 0)					//RJS 10Sep96
					{
						retval = weapon->LoadedStores;
						if (weapon->stationshape)
						{
							sdptr = SHAPESTUFF.GetShapePtr(weapon->stationshape);
							weaponshape = sdptr->Type.shapenumber;
						}

						LaunchBombDrop((mobileitem*) ac,(ShapeNum)weaponshape,xpos,ypos,zpos,world);//MS 20May99
						if ((	!Save_Data.gamedifficulty [GD_UNLIMITEDARM]
							||	ac!=Manual_Pilot.ControlledAC2			//RJS 13Jul00
							||	ac->classtype->aerobaticfactor == AEROBATIC_LOW	)	//RJS 13Jul00
							&& (!_DPlay.Implemented || (_DPlay.Implemented && ac!=Persons2::PlayerSeenAC)))						//AMM 11Oct00
							weapon->LoadedStores--;						//RJS 10Sep96

						//don't launch bomb stacks in pairs!!!
						if (weapon->LauncherType >= LT_BOMBB29)							//RJS 17Jun99
							break;
					}
					else
					{
						if (ac == Manual_Pilot.ControlledAC2)
							_Miles.PlaySample (FIL_SFX_GUN_CLICK1, (ItemBasePtr) ac,80);//RJS 05Dec96
					}
				}
			}
		}
		else
		{
// Drop Super Bomb Group....
			// How do we know which bomb we are dropping?
			// How do we know how many?

			Coords3D	pos;
			UWord		nodropped;

			weapon = SHAPE.GetSuperLauncher(ac,pos,mdelay,nodropped,LT_BOMB,&weaponshape);
			if (weapon)
			{
				timeleft = mdelay;
				if (weapon->LoadedStores > 0)
				{
					retval = weapon->LoadedStores;
					if (weapon->stationshape)
					{
						sdptr = SHAPESTUFF.GetShapePtr(weapon->stationshape);
						weaponshape = sdptr->Type.shapenumber;
					}

					LaunchSuperBomb(ac,(ShapeNum)weaponshape,pos,world);

					weapon->currGun++;
					weapon->LoadedStores--;
					if (!weapon->LoadedStores)
						SHAPE.AllBombsDropped(ac);
				}
			}
		}
	}

	ac->weap.ShootDelay = timeleft;										//RJS 05May99
	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DropAllStores
//Author		Robert Slater
//Date			Wed 27 May 1998
//
//Description	Dumps all external stores.....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::DropAllStores(mobileitem* ac,WorldStuff& world)
{
//DeadCode RJS 23Oct00 	DumpFuel((AirStrucPtr)ac,world);
	DumpWeapons((AirStrucPtr)ac,world);

//DeadCode RJS 27May98	WeapAnimData*	weapon;										
//DeadCode RJS 27May98	SLong			xpos, ypos, zpos;							
//DeadCode RJS 27May98	UByte			index;										
//DeadCode RJS 27May98	UWord			thisstore;
//DeadCode RJS 27May98	int				retval;
//DeadCode RJS 27May98	UWord			mvel;
//DeadCode RJS 27May98
//DeadCode RJS 27May98	for (index = 0; index < 4; index++)
//DeadCode RJS 27May98	{
//DeadCode RJS 27May98		weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,LT_BOMB);
//DeadCode RJS 27May98		if (weapon)
//DeadCode RJS 27May98		{
//DeadCode RJS 27May98			if (weapon->LoadedStores > 0)				
//DeadCode RJS 27May98			{
//DeadCode RJS 27May98				retval = weapon->LoadedStores;
//DeadCode RJS 27May98				LaunchBombDrop((mobileitem*) ac,BOMB,xpos,ypos,zpos,world,TRUE);//RJS 11Jun97
//DeadCode RJS 27May98				
//DeadCode RJS 27May98				weapon->LoadedStores = 0;
//DeadCode RJS 27May98
//DeadCode RJS 27May98 //rdh 8/5/98: storesweight not used now
//DeadCode RJS 27May98 //				((AirStruc*) *ac)->fly.storesweight -= retval * BOMBWEIGHT;
//DeadCode RJS 27May98 //
//DeadCode RJS 27May98 //				if (((AirStruc*) *ac)->fly.storesweight < 0)
//DeadCode RJS 27May98 //					((AirStruc*) *ac)->fly.storesweight = 0;
//DeadCode RJS 27May98				
//DeadCode RJS 27May98				_Miles.SequenceAudible(FIL_MUSIC_BOMBS_DROPPED);
//DeadCode RJS 27May98			}
//DeadCode RJS 27May98		}
//DeadCode RJS 27May98	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchOneGunBullet
//Author		Paul.
//Date			Fri 26 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItem* TransObj::LaunchOneGunBullet(mobileitem* launcher,SLong MuzVel,ShapeNum	weapshape,SLong xpos, SLong ypos, SLong zpos, WorldStuff& worldptr,const SWord& weapHdg, const SWord& weapPitch)
{
	TransientItem* newitem;

	newitem=LaunchUnguidedMissile(launcher,weapshape,LIFETIME_BULLET,MOBILE_BULLET);//PD 26Jun96
	if (newitem)
	{
		SLong	temp;

		newitem->nationality = Nationality(launcher->nationality);					//RJS 21Aug00
//DeadCode RJS 28Jun00 		newitem->hdg = Angles(newitem->hdg + weapHdg);				//RJS 12May00
//DeadCode RJS 28Jun00 		newitem->pitch = Angles(newitem->pitch + weapPitch);		//RJS 12May00

//DeadCode CSB 3Nov00 		SLong wx, wy, wz;
//DeadCode CSB 3Nov00 		MissManCampSky().GetWind(ypos, wx, wy, wz);
//DeadCode CSB 3Nov00 		wx = wx * Timer_Code.FRAMETIME / 10000;
//DeadCode CSB 3Nov00 		wy = wy * Timer_Code.FRAMETIME / 10000;
//DeadCode CSB 3Nov00 		wz = wz * Timer_Code.FRAMETIME / 10000;

		newitem->World.X = xpos;// + wx;								//RJS 29Aug96
		newitem->World.Y = ypos;// + wy;								//RJS 29Aug96
		newitem->World.Z = zpos;// + wz;								//RJS 29Aug96

//DEADCODE CSB 08/11/99 		SWord	vx,vy,vz,vhori;
		SLong	vx,vy,vz,vhori;

//DeadCode RJS 28Jun00 		if ((!_Replay.Playback || (_Replay.Playback && launcher!=Persons2::PlayerSeenAC))//AMM 07Jul99
//DeadCode RJS 28Jun00 			&& !(_DPlay.Implemented && launcher->uniqueID.commsmove && launcher!=Persons2::PlayerSeenAC))//AMM 07Jul99
		if (	(launcher == Persons2::PlayerSeenAC)
			&&	!_Replay.Playback
			&&	!_DPlay.Implemented	)
		{
			((AirStrucPtr)launcher)->fly.pModel->CalcLauncherVel(MuzVel,vx,vy,vz, xpos, ypos, zpos);	//CSB 4Aug00

			newitem->vel_x = vx;
			newitem->vel_y = vy;
			newitem->vel_z = vz;
//DEADCODE CSB 08/11/99 			newitem->velhori = Math_Lib.distance3d(vx,vz,0);
// This hdg will initially point in the same direction as the launcher,
// and correct itself over time...
//			newitem->hdg = Math_Lib.arctan(vx,vz);

			if (weapHdg || weapPitch)
			{
				newitem->hdg = Math_Lib.arctan(vx - launcher->vel_x, vz - launcher->vel_z);					//RJS 28Jun00	//CSB 16Oct00

				float	fvx = float(vx - launcher->vel_x);								//RJS 28Jun00	//CSB 16Oct00
				float	fvz = float(vz - launcher->vel_z);												//CSB 16Oct00
				ULong	vhori;

				vhori = fastMath.DoubleToULong(Float(fastMath.FastSqrt(fvx*fvx+fvz*fvz)));

				newitem->pitch = Math_Lib.arctan(vy - launcher->vel_y, SLong(vhori));		//RJS 28Jun00	//CSB 16Oct00
			}
		}
		else
		{
			Float	sgx,sgy,sgz,sgh;
			Float	mVel = Float(MuzVel);	

			if (((AirStrucPtr)launcher)->fly.pModel->GetGunOri(sgx,sgy,sgz))
			{
// We need emotional content...

				FPMATRIX		omat;
				FPMATRIX_PTR	obj_matrix = &omat;

				_matrix.generate2(	newitem->hdg,
									newitem->pitch,
									newitem->roll,
									obj_matrix		);

				_matrix.Transform(obj_matrix,sgx,sgy,sgz);

				sgx *= mVel;
				sgy *= mVel;
				sgz *= mVel;
			}
			else
			{
// There is no moveable gun...

				Float	sin_hdg,cos_hdg;
				Float	sin_pitch,cos_pitch;

				Math_Lib.high_sin_cos(newitem->pitch,sin_pitch,cos_pitch);

				sgy = sin_pitch * mVel;
				sgh = cos_pitch * mVel;

				Math_Lib.high_sin_cos(newitem->hdg,sin_hdg,cos_hdg);

				sgx = sgh*sin_hdg;
				sgz = sgh*cos_hdg;
			}

			newitem->vel_x += sgx;
			newitem->vel_y += sgy;
			newitem->vel_z += sgz;

//DeadCode RJS 13Mar00 			Float	mVel = Float(MuzVel);						//RJS 12Nov99
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 			Math_Lib.high_sin_cos((Angles)pitchang,sin_ang,cos_ang);
//DeadCode RJS 13Mar00 //DEADCODE CSB 08/11/99 			temp = (MuzVel * sin_ang)>>ANGLES_SHIFT; newitem->vel_y += (SWord )temp;		
//DeadCode RJS 13Mar00 //DEADCODE CSB 08/11/99 			temp = (MuzVel * cos_ang)>>ANGLES_SHIFT; newitem->velhori += (SWord )temp;
//DeadCode RJS 13Mar00 			
//DeadCode RJS 13Mar00 			sin_ang *= mVel;
//DeadCode RJS 13Mar00 			newitem->vel_y += sin_ang;							//RJS 12Nov99
//DeadCode RJS 13Mar00 				
//DeadCode RJS 13Mar00 			Float	velhori  =  (mVel + Float(newitem->vel_)) * cos_ang;
//DeadCode RJS 13Mar00 
//DeadCode RJS 13Mar00 			Math_Lib.high_sin_cos((ANGLES )newitem->hdg,sin_ang,cos_ang);
//DeadCode RJS 13Mar00 //DEADCODE CSB 08/11/99 			temp = (newitem->velhori * sin_ang)>>ANGLES_SHIFT; newitem->velx = (SWord )temp;
//DeadCode RJS 13Mar00 //DEADCODE CSB 08/11/99 			temp = (newitem->velhori * cos_ang)>>ANGLES_SHIFT; newitem->velz = (SWord )temp;
//DeadCode RJS 13Mar00 			newitem->vel_x = velhori * sin_ang; //CSB 08/11/99
//DeadCode RJS 13Mar00 			newitem->vel_z = velhori * cos_ang; //CSB 08/11/99
		}

 		newitem->isArmed = 1;											//MS 7Jul00
//DeadCode MS 7Jul00 		newitem->isArmed = 0;											//AMM 3Jul00
		AddTransientItemToWorld(newitem,worldptr);
	}
	return newitem;												//ARM 05Sep96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchManyGunBullets
//Author		R. Hyde
//Date			Tue 16 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItem* TransObj::LaunchManyGunBullets(	mobileitem* launcher,
												SLong		MuzVel,
												SWord		nobullets,
												SWord		bdelay,
												SWord		weapindex,
												SWord		weapindex2,
												ShapeNum	weapshape,
												SLong		xpos,
												SLong		ypos,
												SLong		zpos,
												WorldStuff& worldptr,
												SWord		theangle,
												SLong		lnchrtype,
												Bool		isArmed		)
{
	SLong	vel;
	SLong	vely, velx, velz;	
	SLong	temp;
	SWord	headgang = launcher->hdg;	//CSB 11/06/99	
	SWord	pitchang = launcher->pitch + theangle;			//RJS 26May98

	Float	sin_ang,cos_ang;
	Coords3D	xyz;
	TransientItem*	newitem = NULL;

//DeadCode CSB 10/03/99		velhori = launcher->velhori;
//DeadCode CSB 10/03/99		vely = launcher->vely;
//DeadCode CSB 10/03/99	
//DeadCode CSB 10/03/99		Math_Lib.high_sin_cos((Angles)pitchang,sin_ang,cos_ang);
//DeadCode CSB 10/03/99	
//DeadCode CSB 10/03/99		temp = (MuzVel * sin_ang)>>ANGLES_SHIFT; vely += temp;
//DeadCode CSB 10/03/99		temp = (MuzVel * cos_ang)>>ANGLES_SHIFT; velhori += temp;
//DeadCode CSB 10/03/99	
//DeadCode CSB 10/03/99		Math_Lib.high_sin_cos((ANGLES )launcher->hdg,sin_ang,cos_ang);
//DeadCode CSB 10/03/99	
//DeadCode CSB 10/03/99		velx = (velhori * sin_ang)>>ANGLES_SHIFT;
//DeadCode CSB 10/03/99		velz = (velhori * cos_ang)>>ANGLES_SHIFT;

	AirStrucPtr AC = (AirStrucPtr)launcher;	//CSB 11/06/99	
	SWord bhdg, bpitch;//, bvel;						
	AC->CalcBulletVel(MuzVel, xpos, ypos, zpos, velx, vely, velz);
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 	Float	totVel = Float(vel);								//RJS 12Nov99
//DeadCode CSB 11Aug00 	Float	velHori;											//RJS 12Nov99
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 	Math_Lib.high_sin_cos((Angles)pitchang, sin_ang, cos_ang);
//DeadCode CSB 11Aug00 	vely    = totVel * sin_ang;									//RJS 12Nov99
//DeadCode CSB 11Aug00 	velHori = totVel * cos_ang;									//RJS 12Nov99
//DeadCode CSB 11Aug00 	
//DeadCode CSB 11Aug00 	Math_Lib.high_sin_cos((Angles)headgang, sin_ang, cos_ang);
//DeadCode CSB 11Aug00 	velx = velHori * sin_ang;									//RJS 12Nov99
//DeadCode CSB 11Aug00 	velz = velHori * cos_ang;									//RJS 12Nov99
	
//DeadCode CSB 11/06/99		SLong vel = launcher->vel + MuzVel;
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		Math_Lib.high_sin_cos((Angles)pitchang,sin_ang,cos_ang);
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		velhori = vel * cos_ang / 32768;
//DeadCode CSB 11/06/99		vely	= vel * sin_ang / 32768;
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		Math_Lib.high_sin_cos((ANGLES )launcher->hdg,sin_ang,cos_ang);
//DeadCode CSB 11/06/99		velx = velhori * sin_ang / 32768;
//DeadCode CSB 11/06/99		velz = velhori * cos_ang / 32768;

	xyz.X = xpos;
	xyz.Y = ypos;
	xyz.Z = zpos;

	//Reset previous bullet store...
	ClearWeaponChain(launcher);									//RJS 15Nov99

	SLong	lifetime;
	AutoMoveCodeTypeSelect	movecode;

	switch (lnchrtype)
	{
	case LT_BULLET:
	case LT_CANNON:
	{
		if (nobullets > 1)										//RJS 06Jun99
		{
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);
			if (sdptr->AnimDataSize == AIRCRAFTANIM)
			{
				AircraftAnimData*	ladptr= (AircraftAnimData*) launcher->Anim;

				if (lnchrtype == LT_BULLET)								//RJS 12Nov00
				{
					ladptr->gunshooting = 1;
					ladptr->cannonshooting = 0;
				}
				else
				{
					ladptr->gunshooting = 0;							//RJS 12Nov00
					ladptr->cannonshooting = 1;							//RJS 12Nov00
				}
			}
		}

		lifetime = LIFETIME_BULLET+Math_Lib.rnd(30)|3;
		movecode = MOBILE_BULLET;
		break;
	}
	case LT_ROCKET:
		lifetime = LIFETIME_ROCKET;
		movecode = MOBILE_ROCKET;
		break;
	case LT_NAPALM:
		break;
	case LT_BOMB:
		break;
	}

	newitem = LaunchSuperLauncher(	launcher,
									weapshape,
									LIFETIME_BULLET+Math_Lib.rnd(30)|3,
									MOBILE_BULLET,
									xyz,
									(Angles)headgang,	//launcher->hdg,
									(Angles)pitchang,
									velx,
									vely,
									velz,
//DEADCODE CSB 09/11/99 									velhori,
									MuzVel,
									launcher->nationality,
									weapindex,
									weapindex2,
									bdelay,
									nobullets,
									lnchrtype,
									worldptr,
									isArmed);					//RJS 27May99

	return(newitem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchCommsBullet
//Author		Andrew McRae
//Date			Fri 6 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 24Jul98 TransientItem* TransObj::LaunchCommsBullet(AirStrucPtr Me, BULPACKET BulPacket)
//DeadCode AMM 24Jul98 {
//DeadCode AMM 24Jul98	mobileitem* launcher = (mobileitem*)Me;
//DeadCode AMM 24Jul98	TransientItem* newitem;
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98	newitem=LaunchUnguidedMissile(launcher,GunfireShape,LIFETIME_BULLET,MOBILE_BULLET);
//DeadCode AMM 24Jul98	
//DeadCode AMM 24Jul98	if (newitem)
//DeadCode AMM 24Jul98	{
//DeadCode AMM 24Jul98		SWord	sin_ang,cos_ang;
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98		newitem->World.X=BulPacket.PosX;
//DeadCode AMM 24Jul98		newitem->World.Y=BulPacket.PosY;
//DeadCode AMM 24Jul98		newitem->World.Z=BulPacket.PosZ;
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98		newitem->velhori = BulPacket.HorzVel;
//DeadCode AMM 24Jul98		newitem->hdg.a = (Angles)BulPacket.Head.a;
//DeadCode AMM 24Jul98		newitem->velx = 0;
//DeadCode AMM 24Jul98		newitem->vely = BulPacket.VertVel;
//DeadCode AMM 24Jul98		newitem->velz = 0;
//DeadCode AMM 24Jul98		newitem->Status.deadtime = 1;						
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98		Math_Lib.high_sin_cos((ANGLES )newitem->hdg,sin_ang,cos_ang);
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98		newitem->velx = (SWord)((newitem->velhori * sin_ang)/ANGLES_FRACT);
//DeadCode AMM 24Jul98		newitem->velz = (SWord)((newitem->velhori * cos_ang)/ANGLES_FRACT);
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98		newitem->LaunchTime = BulPacket.LaunchTime;
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98		WorldStuff* thisworld = newitem->GetCurrWorld();
//DeadCode AMM 24Jul98		WorldStuff& worldptr = (WorldStuff&)(*thisworld);
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98		AddTransientItemToWorld(newitem,worldptr);
//DeadCode AMM 24Jul98	}
//DeadCode AMM 24Jul98	return newitem;												
//DeadCode AMM 24Jul98 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTrackedBullet
//Author		Robert Slater
//Date			Tue 21 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode RJS 03Dec98 void	TransObj::LaunchTrackedBullet(mobileitem* launcher,WorldStuff& worldptr)
//DeadCode RJS 03Dec98 {
//DeadCode RDH 29Nov98	if (View_Object->PolyPitEnabled())
//DeadCode RDH 29Nov98	{
//DeadCode RDH 29Nov98		SLong			usexpos, useypos, usezpos;
//DeadCode RDH 29Nov98		SLong			xpos, ypos, zpos;
//DeadCode RDH 29Nov98		SLong			index, wpcnt;
//DeadCode RDH 29Nov98		WeapAnimData*	weapon;
//DeadCode RDH 29Nov98		UWord			mvel,mdelay,mburst;						//RDH 31Jul98
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98		usexpos = 0;
//DeadCode RDH 29Nov98		useypos = 0;
//DeadCode RDH 29Nov98		usezpos = 0;
//DeadCode RDH 29Nov98		wpcnt = 0;
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98		index = 0;
//DeadCode RDH 29Nov98		while (index < 3)
//DeadCode RDH 29Nov98		{
//DeadCode RDH 29Nov98			weapon = SHAPE.GetWeaponLauncher(launcher,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BULLET);//RDH 31Jul98
//DeadCode RDH 29Nov98			if (weapon)
//DeadCode RDH 29Nov98			{
//DeadCode RDH 29Nov98				usexpos += xpos;
//DeadCode RDH 29Nov98				useypos += ypos;
//DeadCode RDH 29Nov98				usezpos += zpos;
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98				wpcnt++;
//DeadCode RDH 29Nov98			}
//DeadCode RDH 29Nov98			index++;
//DeadCode RDH 29Nov98		}
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98		if (wpcnt)
//DeadCode RDH 29Nov98		{
//DeadCode RDH 29Nov98			TransientItem* newitem;
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98			newitem=LaunchUnguidedMissile(launcher,EMPTY,LIFETIME_BULLET,MOBILE_TRACKBULLET);
//DeadCode RDH 29Nov98			if (newitem)
//DeadCode RDH 29Nov98			{
//DeadCode RDH 29Nov98				SLong			temp;
//DeadCode RDH 29Nov98				SWord			sin_ang,cos_ang;
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98				newitem->World.X = usexpos/wpcnt;					
//DeadCode RDH 29Nov98				newitem->World.Y = useypos/wpcnt;					
//DeadCode RDH 29Nov98				newitem->World.Z = usezpos/wpcnt;	
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98				Math_Lib.high_sin_cos((ANGLES )newitem->pitch,sin_ang,cos_ang);
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98				temp = (mvel * sin_ang)>>ANGLES_SHIFT; newitem->vely += (SWord )temp;
//DeadCode RDH 29Nov98				temp = (mvel * cos_ang)>>ANGLES_SHIFT; newitem->velhori += (SWord )temp;
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98				AddTransientItemToWorld(newitem,worldptr);
//DeadCode RDH 29Nov98			}
//DeadCode RDH 29Nov98		}
//DeadCode RDH 29Nov98	}
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchMiniExplosion
//Author		Martin Alderton
//Date			Thu 29 Feb 1996
//
//Description	sets up a transientitem
//
//Inputs		a rotitem giving initial position		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchMiniExplosion(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(launcher,MiniExplosionShape,100,MOBILE_STATIONARY);//RJS 10Dec98
	if (newitem)
	{
		newitem->World.Y += 400;
		if ((launcher->Status.size >= MovingSize) && (launcher->Status.size != TransientSize))//RJS 16Nov98
			newitem->Target = launcher;							//RJS 16Nov98

		_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_OILDRUM1+Math_Lib.rnd(5)), newitem);
		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDebris
//Author		Robert Slater
//Date			Fri 21 Jun 1996
//
//Description	catapults debris of any shape into the air....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDebris(mobileitem* launcher,ShapeNum shapeBase,SLong	randcnt, SLong maxbits, WorldStuff& worldptr, Bool nospin)
{
	if (desiredFPS <= realFPS)					//RJS 11Jun99
	{
		TransientItem*	newitem;
		UWord	newhdg;
		SLong	vel;
		SLong	pitch;
		SLong	count;
		SLong	cntrand = maxbits / 2;
		UWord	pitchover,rollover;

		cntrand += Math_Lib.rnd(cntrand);

		if (launcher->Status.size == AirStrucSize)
			pitch = ANGLES_30Deg;
		else
			pitch = 0;

		UWord	shprand;

		for (count = 0; count < cntrand; count++)
		{
			shprand = Math_Lib.rnd(randcnt);								//RJS 1/20/99
			newitem = SimplifiedSpriteLaunch(launcher,			
											(ShapeNum) (shapeBase + shprand), //RJS 1/20/99
											250,MOBILE_DEBRIS);
			if (newitem)
			{
				if ((newitem->shape >= DebrisStartShape) && (newitem->shape <= DebrisEndShape))
				{
					DebrisAnimData*	adptr = (DebrisAnimData*) newitem->Anim;
					adptr->frameno = Math_Lib.rnd(4);
				}
				else
				{
					if (	Anim_Control.SetPlayerAnim(newitem,ANIMATION_AARGH)
						&&	(Math_Lib.rnd() > 32767)	)
					{
						TroopAnimData*	adptr = (TroopAnimData*) newitem->Anim;
						adptr->BITSOFFFLAGS |= 1<<BF_ONFIRE;				
					}
				}

				newhdg = Math_Lib.rnd();

				vel = Math_Lib.rnd(300);						//RJS 29Mar00
				newitem->hdg = (Angles) newhdg;			
				newitem->pitch = Angles(ANGLES_30Deg + Math_Lib.rnd(pitch));//RJS 29Mar00
 				newitem->vel_ = vel*1000;						//RJS 16Nov99
				newitem->CalcVels();							//RJS 16Nov99

//DEADCODE CSB 08/11/99 				newitem->velhori = vel;	
			
				if (!nospin)
				{
//DeadCode RJS 16Dec99					pitchover = (vel << 8)/300;	//greater the vel, the more it spins
//DeadCode RJS 16Dec99					rollover = newhdg>>8;
//DeadCode RJS 16Dec99
//DeadCode RJS 16Dec99					newitem->TransRandom = (rollover<<8) + pitchover;		
					newitem->TransRandom = Math_Lib.rnd();
				}

				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFire
//Author		Robert Slater
//Date			Mon 1 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchFire(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	newitem = SimplifiedSpriteLaunch(	launcher,
										LargeFireShape,
										LIFETIME_GROUNDEXP,MOBILE_GROUNDEXP);//RJS 09Oct96*/
	if (newitem)
	{
		MoveGunAnimData*	adptr = (MoveGunAnimData*)newitem->Anim;
		WeapAnimData*		weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

		SHAPE.InitTrailFields((UByteP)weapon,0,32000,LT_FUEL);	//RJS 12Jan98

		LaunchVapourStream((UByteP)weapon,LargeFireShape,0,1000,64);

		newitem->TransRandom = SmokeLaunchDelay;

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTroop
//Author		Robert Slater
//Date			Mon 1 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchTroops(	item*		launcher,
								ShapeNum	troopshape,
								Coords3D	realpos,
								WorldStuff& worldptr,
								SByte		maxtroops	)
{
//DeadCode RJS 11Jun99 	if (desiredFPS <= realFPS)					//RJS 11Jun99
	{
		if (maxtroops)
		{
			SLong	realmaxtroops = maxtroops;
			if (realmaxtroops > 16)	realmaxtroops = 16;

			if (desiredFPS > realFPS)
				realmaxtroops >>= 1;

			maxtroops = realmaxtroops/2;
			maxtroops += Math_Lib.rnd(maxtroops);
			if (maxtroops)
			{
				TransientItem*	newitem;
				SWord			count;
				SLong			xpos, ypos, zpos,dist;
				SWord			thehdg;
//DeadCode RJS 20Oct00 				Bool			homingtroops = FALSE;
				ShapeDescPtr	sdptr;
				ShapeNum		newshp;
				animptr			adptrtmp;
	//DeadCode RJS 21Apr99			FireAnimData*	adptr2;										
//DeadCode RJS 20Oct00 				Bool			isours = FALSE;
				TroopAnimData*	adptr;
				MinAnimData*	mad;
				SLong			dx,dy,dz;
				SLong			mindist = 10000000;
				Coords3D		placelist[64];
				SLong			placecnt = 0;
				Bool			dim = TRUE;
				SWord			randindex;
//Dead				SLong			groundheight = Land_Scape.GetGroundLevel(realpos);

				sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);
				adptrtmp = launcher->Anim;

				if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
				{
					UByteP		instr_ptr;
					instr_ptr = (UByteP )sdptr + sdptr->liveshpref;

					// Search for nearest strongest....

					while (SHAPE.GetGroupElement(instr_ptr,newshp,xpos,ypos,zpos))
					{
						mad = (MinAnimData*) adptrtmp;
						if (mad->itemstate == ALIVE)
						{
							dx = xpos + launcher->World.X;
							dy = ypos + launcher->World.Y;
							dz = zpos + launcher->World.Z;
							if ((realpos.X != dx) && (realpos.Z != dz))
							{
								dx -= realpos.X;
								dy -= realpos.Y;
								dz -= realpos.Z;

								dist = Math_Lib.distance3d(dx,dy,dz);
								if (dist < mindist)
								{
									mindist = dist;
									placelist[placecnt].X = xpos + launcher->World.X;
									placelist[placecnt].Y = ypos + launcher->World.Y;
									placelist[placecnt++].Z = zpos + launcher->World.Z;
								}
							}
						}

						adptrtmp += SHAPE.GetElementAnimOffset(newshp);//RJS 21Apr99
					}
				}
				else
				{
					// Find nearest alive thing in this sector....
					Coords3D	oldpos = launcher->World;
					ItemPtr		nearestItm;

					launcher->World = realpos;
					nearestItm = Three_Dee.NearestAliveThing(launcher);
					launcher->World = oldpos;

					if (nearestItm)
					{
						placelist[placecnt].X = nearestItm->World.X;
						placelist[placecnt].Y = nearestItm->World.Y;
						placelist[placecnt++].Z = nearestItm->World.Z;
					}
				}

				if (placecnt)
				{
					// Set homing devices....
					SWord	randindex;

					placecnt--;
					dim = FALSE;
				}

				PointBlokes(launcher,troopshape,realpos,maxtroops,placelist,placecnt);
//DeadCode RJS 01Jun99 				for (count = 0; count < maxtroops; count++)
//DeadCode RJS 01Jun99 				{
//DeadCode RJS 01Jun99 					newitem = SimplifiedSpriteLaunch(launcher,troopshape,LIFETIME_TROOP,MOBILE_TROOP);
//DeadCode RJS 01Jun99 					if (newitem)
//DeadCode RJS 01Jun99 					{
//DeadCode RJS 01Jun99 						adptr = (TroopAnimData*) newitem->Anim;
//DeadCode RJS 01Jun99 						if (!dim)
//DeadCode RJS 01Jun99 						{
//DeadCode RJS 01Jun99 							randindex = placecnt-Math_Lib.rnd(maxtroops);
//DeadCode RJS 01Jun99 							if (randindex < 0)
//DeadCode RJS 01Jun99 								randindex = placecnt;
//DeadCode RJS 01Jun99 
//DeadCode RJS 01Jun99 							adptr->xpos = placelist[randindex].X;								
//DeadCode RJS 01Jun99 							adptr->ypos = placelist[randindex].Y;
//DeadCode RJS 01Jun99 							adptr->zpos = placelist[randindex].Z;
//DeadCode RJS 01Jun99 							adptr->oncourse = FALSE;
//DeadCode RJS 01Jun99 
//DeadCode RJS 01Jun99 							// Someone might panic!!!!!... headless chicken code
//DeadCode RJS 01Jun99 							if (Math_Lib.rnd()>50000)
//DeadCode RJS 01Jun99 								adptr->homing = FALSE;
//DeadCode RJS 01Jun99 							else
//DeadCode RJS 01Jun99 								adptr->homing = TRUE;
//DeadCode RJS 01Jun99 						}
//DeadCode RJS 01Jun99 						else
//DeadCode RJS 01Jun99 						{
//DeadCode RJS 01Jun99 							adptr->oncourse = FALSE;
//DeadCode RJS 01Jun99 							adptr->homing = FALSE;
//DeadCode RJS 01Jun99 						}
//DeadCode RJS 01Jun99 	
//DeadCode RJS 01Jun99 						// 5 metre spread around...
//DeadCode RJS 01Jun99 						newitem->World.X = realpos.X + Math_Lib.rnd(1000) - 500;
//DeadCode RJS 01Jun99 						newitem->World.Y = groundheight;								
//DeadCode RJS 01Jun99 						newitem->World.Z = realpos.Z + Math_Lib.rnd(1000) - 500;
//DeadCode RJS 01Jun99 
//DeadCode RJS 01Jun99 						newitem->hdg = (Angles) Math_Lib.rnd();
//DeadCode RJS 01Jun99 						newitem->vely = 0;
//DeadCode RJS 01Jun99 						newitem->velhori = 100 + Math_Lib.rnd(20);
//DeadCode RJS 01Jun99 						newitem->TransRandom = 50;
//DeadCode RJS 01Jun99 
//DeadCode RJS 01Jun99 						AddTransientItemToWorld(newitem, worldptr);
//DeadCode RJS 01Jun99 					}
//DeadCode RJS 01Jun99 				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchParachute
//Author		Robert Slater
//Date			Tue 2 Jul 1996
//
//Description	Jump from side of the plane/balloon at any angle from 0-180 degrees
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchParachute(mobileitem* launcher,Coords3D& pos, SWord relpos, WorldStuff& worldptr, bool trackthis)//RJS 22Dec99
{
	UByteP		canopyPtr = NULL;										//RJS 7Jun00
	UByte		canopyVal = BS_DEAD;									//RJS 7Jun00
	AircraftAnimData*	acadptr = NULL;							//RJS 05Jul00
	AirStrucPtr	ac = NULL;
																		//RJS 7Jun00
	if (SHAPESTUFF.GetShapePtr(launcher->shape)->AnimDataSize == AIRCRAFTANIM)	//RJS 7Jun00
	{
		acadptr = (AircraftAnimData *) launcher->Anim;			//RJS 05Jul00
		canopyVal = acadptr->CANOPY;
		canopyPtr = &acadptr->CANOPY;
	}
	
	Squad_Diary.SetAC(launcher,launcher->Anim);							//RJS 21Sep00
																		//RJS 18Feb98
	// Canopy must have been blown.....									//RJS 18Feb98
	if (canopyVal == BS_DEAD)											//RJS 7Jun00
	{																	//RJS 18Feb98
		if (launcher->Status.size == AIRSTRUCSIZE)				//RJS 31May99
		{														//RJS 31May99
			ac = (AirStrucPtr)*launcher;								//RJS 30Aug00
																//RJS 31May99
			if (!ac->uniqueID.commsmove)								  //AMM 07/07/99
				ac->ai.radiosilent = TRUE;							//RJS 11Jun99

			if (!ac->weap.Ejected)								//RJS 23Feb00
			{
				int	totalpilots = SHAPE.GetTotalPilots(launcher->shape);	//RJS 21Sep00
				if (!totalpilots)	totalpilots = 1;

				ac->weap.Ejected = TRUE;

				ac->ai.diaryptr->AddEjected(ac,totalpilots);			//RJS 21Sep00
			}
		}														//RJS 31May99

		TransientItem*	newitem;										//RJS 18Feb98

		// Turn him off...... give him 2 mins...
		if (acadptr)
	 		acadptr->ejected = 1;								//RJS 05Jul00

		SLong	launchTime;
		if (launcher == Persons2::PlayerSeenAC)
		{
			Persons2::PlayerSeenAC->fly.pModel->Blood = 1;				//RJS 13Jul00
			launchTime = 12000;
		}
		else
		{
			if (transientcounter < MaxTransients)
				launchTime = 1000 + (((MaxTransients-transientcounter)*11000)/MaxTransients);
			else
				launchTime = 1000;
		}

		newitem = SimplifiedSpriteLaunch(launcher,BLOKE,launchTime,MOBILE_PARACHUTE);//RJS 22Dec99
		if (newitem)													//RJS 18Feb98
		{
			TroopAnimData*	adptr = (TroopAnimData*)newitem->Anim;//RJS 22Dec99
			adptr->skydiving = 1;								//RJS 22Dec99
			if (launcher->nationality == NAT_RAF)				//RJS 22May00
				adptr->stripno = CLOTHING_RAFPILOT;
			else
				adptr->stripno = CLOTHING_LWPILOT;

			adptr->BITSOFFFLAGS |= 1<<BF_PARACHUTE;				//RJS 22Dec99
			
			Anim_Control.SetPlayerAnim(newitem,ANIMATION_DIVE);			//RJS 22Dec99

			newitem->World = pos;										//RJS 06Dec99
//DeadCode RJS 06Dec99			_Miles.PlayOnce(FIL_SFX_EJECT_SEAT,launcher);				//RJS 18Feb98
			if (trackthis)
			{
				Manual_Pilot.DeathSequenceOverride(AirStrucPtr(launcher),AUTO_DEATHSEQUENCE);	//RJS 26Jun00

				if (launcher == Manual_Pilot.ControlledAC2)						//RJS 21May98
				{																//RJS 21May98
//DeadCode RJS 29Oct00 					Squad_Diary.UpdatePlayerLog(EFS_Parachute);	//RJS 18Feb00

					View_Object->SetToParachuteView((mobileitem*)newitem);	//RJS 26Jun00
																				//RJS 21May98
					Manual_Pilot.controlmode=ManualPilot::PILOTDEAD;			//RJS 21May98

					_Miles.PlayFlyAway(launcher);								//RJS 21May98

					_Miles.SequenceAudible(FIL_MUSIC_PARACHUTE);	//RJS 17Mar99
				}																//RJS 21May98
				else
				{
					if (launcher->nationality != Manual_Pilot.ControlledAC2->nationality)
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ENEMYEJECT, MSG_EJECTREPLY, launcher , launcher, Manual_Pilot.ControlledAC2));//RJS 31Jan00
					else
					{
						AirStrucPtr	buddy;
						if (((AirStrucPtr)launcher)->PlayerInGroup())
						{
							buddy = Manual_Pilot.ControlledAC2->FindBuddy();
							if (buddy)
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_EJECTREPLY, MSG_EJECTREPLY, buddy , launcher, Manual_Pilot.ControlledAC2));//RJS 31Jan00
						}
					}
				}
			}

			newitem->isOwned = 1;			//cannot remove...					//RJS 22Apr99

//DeadCode RJS 20Oct00 			ClassPtr	clstyp = ((AirStrucPtr)launcher)->classtype;

//DeadCode RJS 10Aug00 	#pragma warnmsg ("RadioChat: phrase_f15s commented out")
//DeadCode RJS 10Aug00 			
//TEMPCODE RDH 07/12/99 			if (clstyp->phrasename != PHRASE_F51S)
//TEMPCODE RDH 07/12/99 			{
//TEMPCODE RDH 07/12/99 				SLong	vx,vy,vz;
//TEMPCODE RDH 07/12/99 
//TEMPCODE RDH 07/12/99 				((AirStrucPtr)launcher)->fly.pModel->CalcParachuteVel(vx,vy,vz,launcher->hdg,launcher->pitch,launcher->roll,launcher->vel_/10000, 40000, launcher->World.Y);	//RJS 10May99	//CSB 13/06/99	
//TEMPCODE RDH 07/12/99 
//TEMPCODE RDH 07/12/99 				newitem->vel_x = vx;
//TEMPCODE RDH 07/12/99 				newitem->vel_y = vy;
//TEMPCODE RDH 07/12/99 				newitem->vel_z = vz;
//TEMPCODE RDH 07/12/99 //DEADCODE CSB 09/11/99 				newitem->velhori = Math_Lib.distance3d(vx,vz,0);
//TEMPCODE RDH 07/12/99 				newitem->pitch = launcher->pitch;
//TEMPCODE RDH 07/12/99 				newitem->roll = launcher->roll;
//TEMPCODE RDH 07/12/99 
//TEMPCODE RDH 07/12/99 //DeadCode CSB 13/06/99					if (((AirStrucPtr)launcher)->AcIsPlayer())		//RJS 13May99
//TEMPCODE RDH 07/12/99 					newitem->hdg = Math_Lib.arctan(vx,vz);		//RJS 13May99
//TEMPCODE RDH 07/12/99 //DeadCode CSB 13/06/99					else											//RJS 13May99
//TEMPCODE RDH 07/12/99 //DeadCode CSB 13/06/99						newitem->hdg = launcher->hdg;				//RJS 13May99
//TEMPCODE RDH 07/12/99 			}
//TEMPCODE RDH 07/12/99 			else
			{
//DeadCode RJS 22Dec99 				ParachuteAnimData* adptr = (ParachuteAnimData*) newitem->Anim;
//DeadCode RJS 22Dec99 				adptr->OTHER = 255;		//dead the rest...

				newitem->vel_x = launcher->vel_x;
				newitem->vel_y = launcher->vel_y;
				newitem->vel_z = launcher->vel_z;
//DEADCODE CSB 09/11/99 				newitem->velhori = 100;
//DeadCode RJS 3Jul00 
//DeadCode RJS 3Jul00 				newitem->vel_y += 100000;

				SWord	angHdg = (Math_Lib.rnd() * ANGLES_45Deg)/ANGLES_180Deg;
				if (angHdg >= 0)
					angHdg -= ANGLES_22Deg;
				else
					angHdg += ANGLES_22Deg;

				newitem->hdg = Angles(launcher->hdg + ANGLES_90Deg + angHdg);

				const	Float	parachute_vel = 25000.;
				Float	sin_ang, cos_ang;
				Float	pvx,pvz;
				SLong	pvy;

				Math_Lib.high_sin_cos(newitem->hdg,sin_ang,cos_ang);

				pvx = parachute_vel*sin_ang;
				pvz = parachute_vel*cos_ang;
				if (relpos > 0)
					pvy = 5000;
				else
					pvy = -5000;

				newitem->vel_x += SLong(pvx);
				newitem->vel_y += pvy;
				newitem->vel_z += SLong(pvz);
				newitem->vel_ = 25000;									//RJS 13Nov00

				newitem->pitch = launcher->pitch;
				newitem->roll = launcher->roll;
			}

			// Inherit launcher ori & speed.
			// Give vel = 20ms (200)
			// Give drag.
			// Launch propellent smoke when eject.
			// Rotate guy in seat to upright position.. eject at -20 ms
			// splat guy on ground
			//... calc drag with air density
			//	(20 - kmheight)/(20 + kmheight)

			newitem->TransRandom = PARACHUTE_PHASE_1;

			UWord			chuteStatus = 0;									//RJS 22Sep00
			EndFlightStatus	theReport = EFS_Parachute;

// Did we eject over enemy territory?...
			if (launcher->Status.size == AIRSTRUCSIZE)
			{
				bool	safeOverFrance = (AirStrucPtr(launcher)->nationality != NAT_RAF);
									
				if (safeOverFrance != newitem->OverFrance())
					chuteStatus |= PARACHUTE_DEAD;
			}

// Will our chute open properly?...
			UWord	openChance = Math_Lib.rnd();
			if (openChance > 8192)
				chuteStatus |= PARACHUTE_CHUTE_OPEN;
			else
			{
				theReport = EFS_PILOTLOST;								//RJS 29Oct00

				chuteStatus |= PARACHUTE_DEAD;

				if (openChance > 4096)
					chuteStatus |= PARACHUTE_CHUTE_ESCAPED;
				else
					chuteStatus |= PARACHUTE_CHUTE_FAILED;
			}

// Is our guy lost?
			if (	(chuteStatus & PARACHUTE_DEAD)
				&&	(launcher->Status.size == AIRSTRUCSIZE)	)
				AirStrucPtr(launcher)->ai.diaryptr->KillPilot();
			
			if (trackthis && launcher == Manual_Pilot.ControlledAC2)	//RJS 29Oct00
				Squad_Diary.UpdatePlayerLog(theReport);					//RJS 29Oct00
			
			newitem->TransRandom |= (chuteStatus << PARACHUTE_SHIFT);
																		//RJS 18Feb98
			AddTransientItemToWorld(newitem, worldptr);					//RJS 18Feb98
		}																//RJS 18Feb98
	}																	//RJS 18Feb98
	else																//RJS 18Feb98
	{																	//RJS 18Feb98
		_Miles.PlayOnce(FIL_SFX_YELP1, launcher);						//RJS 18Feb98
																		//RJS 18Feb98
//		adptr->PILOTLEFT = BS_DEAD;										//RJS 18Feb98
		if (	canopyPtr												//RJS 7Jun00
			&&	(canopyVal < BS_DEAD)	)								//RJS 7Jun00
			*canopyPtr = BS_DAMLV2;										//RJS 7Jun00

		if (launcher == Manual_Pilot.ControlledAC2)						//RJS 18Feb00
		{
			Squad_Diary.UpdatePlayerLog(EFS_PILOTLOST);

			Manual_Pilot.controlmode=ManualPilot::PILOTDEAD;
			Manual_Pilot.DeathSequenceOverride((AirStrucPtr)launcher,AUTO_DEATHSEQUENCE);

			View_Object->SetToDeathView(DEATH_SKID);					//RJS 31May00
		}
	}																	//RJS 18Feb98

	Squad_Diary.UpdateACDamage();								//RJS 23Feb00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBarage
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchBarage(	mobileitem* launcher,
								SLong		launchtime )
{
	SLong			mintime = launchtime / 2;
	SWord			howlong = 0;
	SWord			thistimer;
	SWord			count;
	SLong			groundheight;
	TransientItem*	newitem;
	UWord			totaltime = mintime + Math_Lib.rnd(mintime);//Max of 'launchtime' secs, min of .5 launchtime
	UWord			maxhowmany;
	UWord			howmany;
	SWord			ttime;

	//3 bangs per 1.5 sec max...

	if (Three_Dee.IsItVisible(launcher->World)==true)					//RJS 09Dec98
	{
		maxhowmany = (3 * totaltime)/150;
		howmany = maxhowmany / 2;
		howmany += Math_Lib.rnd(howmany);

		ttime = ((totaltime / howmany)*10) - 167;

		groundheight = GetGroundLevel(launcher);				//RJS 14Apr99

		for (count = 0; count < howmany; count++)
		{
			thistimer = 167 + Math_Lib.rnd(ttime);				//RJS 01Oct98
			howlong += thistimer;								//RJS 25Oct96

			newitem = SimplifiedSpriteLaunch(launcher,ShockwaveShape,howlong/10,MOBILE_BARAGE);
			if (newitem)
			{
				// With a max radius of about 200 metres

				newitem->World.X = launcher->World.X + Math_Lib.rnd(40000) - 20000;//RJS 25Oct96
				newitem->World.Z = launcher->World.Z + Math_Lib.rnd(40000) - 20000;//RJS 25Oct96
				newitem->World.Y = groundheight;						//RJS 23Jul96

				AddTransientItemToWorld(newitem, *newitem->currworld);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDelayedExplosion
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDelayedExplosion(mobileitem* launcher,WorldStuff& worldptr)
{
	SLong			delay;
	TransientItem*	newitem;

	delay = 150 + Math_Lib.rnd(150);

	newitem = LaunchGuidedMissile(launcher,(itemptr) launcher,
									InvisibleLauncher,delay,MOBILE_DELEXP);//RJS 06Dec98

	if (newitem)
	{
		// this means it really will explode...
		newitem->TransRandom = 2;								//RJS 06Dec98

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFlak
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchFlak(mobileitem* launcher,ShapeNum theShape, WorldStuff& worldptr)
{
	LaunchTurbulance(launcher,4,worldptr);								//RJS 21Aug00

	if (WithinVisibleRange(launcher->World,300000))				//RJS 30Apr99
	{
		SLong	count,howlong,newx,newy,newz;

		UWord	killChance = Math_Lib.rnd(64);							//RJS 27Oct00

		howlong = 0;
		for (count = 0; count < 8; count++)
		{
			howlong += Math_Lib.rnd(80);

			TransientItem*	newitem = SimplifiedSpriteLaunch(launcher,theShape,howlong,MOBILE_FLAK);
			if (newitem)
			{
				MinAnimData*	mad = (MinAnimData*)newitem->Anim;			//RJS 06May99
				mad->IsInvisible = 1;
				// Place randomly about that point....

				newx = Math_Lib.rnd(60000) - 30000;						//RJS 15Nov00
				newy = Math_Lib.rnd(60000) - 30000;						//RJS 15Nov00
				newz = Math_Lib.rnd(60000) - 30000;						//RJS 15Nov00

				newitem->World.X += newx;				
				newitem->World.Z += newy;				
				newitem->World.Y += newz;				

				if (killChance == count)								//RJS 27Oct00
					newitem->TransRandom = 1;							//RJS 27Oct00

				AddTransientItemToWorld(newitem, worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchRicochet
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchRicochet(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;
//DeadCode RJS 20Oct00 	UWord			MaxVel = 300;
	UWord			count;
//DeadCode RJS 19Feb98	ExplodeAnimData* adptr;									//PD 10May96

//DeadCode RJS 10Jul96	newitem = SimplifiedSpriteLaunch(launcher,SPURT1,10,MOBILE_RICOCHET);
//DeadCode RJS 10Jul96	if (newitem)
//DeadCode RJS 10Jul96	{
//DeadCode RJS 10Jul96		newitem->hdg = ANGLES_0Deg - View_Point.hdg;
//DeadCode RJS 10Jul96		adptr = (ExplodeAnimData* )newitem->Anim;
//DeadCode RJS 10Jul96		adptr->frameno = Math_Lib.rnd(3);
//DeadCode RJS 10Jul96
//DeadCode RJS 10Jul96		AddTransientItemToWorld(newitem,worldptr);
//DeadCode RJS 10Jul96	}

	newitem = SimplifiedSpriteLaunch(launcher,DustShape,LIFETIME_MINIEX / 6,MOBILE_STATIONARY);//RJS 20Apr98
	if (newitem)
	{
		AddTransientItemToWorld(newitem,worldptr);
		_Miles.PlaySample((FileNum) (FIL_SFX_RICOCHET_SOFT_SURFACE1+Math_Lib.rnd(5)), (ItemBasePtr) newitem);//RJS 22Nov96
	}

	if (desiredFPS <= realFPS)					//RJS 11Jun99
	{
		for (count = 0; count < 3; count++)
		{
			newitem = SimplifiedSpriteLaunch(launcher,SparkShape,//RJS 28May99
											10,MOBILE_RICOCHET);
			if (newitem)
			{
				SLong	vel = 100 + Math_Lib.rnd(100);

				newitem->hdg = (Angles) Math_Lib.rnd();				//RJS 24Jul96
				newitem->pitch = (Angles) Math_Lib.rnd(16000);		//RJS 24Jul96
//DeadCode RJS 29Mar00 				newitem->vel_y = Math_Lib.rnd(vel)*1000;		//RJS 16Nov99
				newitem->vel_ = vel*1000;						//RJS 16Nov99

				newitem->CalcVels();								//RJS 16Nov99
//DEADCODE CSB 09/11/99 				newitem->velhori = 100 + Math_Lib.rnd(100);			//RJS 24Jul96

				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSpark
//Author		Robert Slater
//Date			Wed 24 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchSpark(mobileitem* launcher,WorldStuff& worldptr)
{
	if (	WithinVisibleRange(launcher->World,100000)
		&&	(desiredFPS <= realFPS)		)		//RJS 11Jun99
	{
		TransientItem*	newitem;
		UWord			count;

		for (count = 0; count < 2; count++)
		{
			newitem = SimplifiedSpriteLaunch(launcher,SparkShape,		//RDH 20Dec96
											40,MOBILE_GANDF);	//RJS 28May99
			if (newitem)
			{
				SLong	vel = Math_Lib.rnd(100);			//RJS 16Nov99

				newitem->hdg = (Angles) (launcher->hdg + ANGLES_180Deg - Math_Lib.rnd(ANGLES_120Deg) + ANGLES_60Deg);				
//DeadCode RJS 29Mar00 				newitem->vel_y = (Math_Lib.rnd(vel<<1)-vel)*1000;//RJS 16Nov99
				newitem->pitch = Angles(Math_Lib.rnd(ANGLES_90Deg)-ANGLES_45Deg);//RJS 29Mar00
				newitem->vel_ = vel*1000;						//RJS 16Nov99
				newitem->CalcVels();

//DEADCODE CSB 09/11/99 				newitem->velhori = 100 - newitem->vely;				//RJS 17Nov98
				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchExplosion
//Author		Martin Alderton
//Date			Thu 29 Feb 1996
//
//Description	Launches a big explosion animation,
//				and a fan of debris	
//
//Inputs		a rotitem giving initial position
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchExplosion(mobileitem* launcher,WorldStuff& worldptr,int	strength)
{
	TransientItem*	newitem;
	SLong			dx, dy, dz, dh;
	SLong			distance;
	SWord			thehdg, thehdg1;
	SWord			pitch;
	SLong			radius;
	SWord			sin_ang,cos_ang;
	ShapeDescPtr	sshp;										//RJS 08Nov96

	newitem	= RelativeSpriteLaunch(launcher,launcher->shape,HugeExplosionShape,100,MOBILE_BIGEXP);
	if (newitem)
	{
//DeadCode RJS 26Nov98		sshp = SHAPESTUFF.GetShapePtr(launcher->shape);
//DeadCode RJS 26Nov98		radius = (sshp->Size << 4) + 4;
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		dx = launcher->World.X - View_Point->World.X;
//DeadCode RJS 26Nov98		dy = launcher->World.Y - View_Point->World.Y;
//DeadCode RJS 26Nov98		dz = launcher->World.Z - View_Point->World.Z;
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		Math_Lib.Intercept(dx,dy,dz,distance,thehdg,pitch);
//DeadCode RJS 26Nov98		Math_Lib.high_sin_cos((Angles)pitch,sin_ang,cos_ang);
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		dy = (sin_ang * radius) / ANGLES_FRACT;
//DeadCode RJS 26Nov98		dh = (cos_ang * radius) / ANGLES_FRACT;
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		Math_Lib.high_sin_cos((Angles)thehdg,sin_ang,cos_ang);
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		dx = (sin_ang * dh) / ANGLES_FRACT;
//DeadCode RJS 26Nov98		dz = (cos_ang * dh) / ANGLES_FRACT;
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		newitem->pitch = (Angles) 1;
//DeadCode RJS 26Nov98		newitem->roll = (Angles) 1;
//DeadCode RJS 26Nov98		newitem->hdg = (Angles) 1;
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		newitem->World.Z -= 1;
//DeadCode RJS 26Nov98		newitem->World.X -= 1;
//DeadCode RJS 26Nov98		newitem->World.Y -= 1;
//DeadCode RJS 26Nov98		newitem->TransRandom = 10;
//DeadCode RJS 26Nov98

		AddTransientItemToWorld(newitem, worldptr);
	}

	LaunchSkinDebris(launcher,worldptr);
	LaunchSparkDebris(launcher,worldptr);			
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSparkDebris
//Author		Robert Slater
//Date			Tue 13 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchSparkDebris(mobileitem* launcher, WorldStuff& worldptr)
{
	if (desiredFPS <= realFPS)					//RJS 11Jun99
	{
		int				count;
		TransientItem*	newitem;

		for (count = 0; count < 8; count++)							//DAW 01Sep98
		{
	//DeadCode RJS 23Nov98		newitem = SimplifiedSpriteLaunch(launcher,SPARK,LIFETIME_DEBRISLNCHR,MOBILE_DEBRIS);//RDH 20Dec96
			newitem = LaunchUnguidedMissile(launcher,SparkShape,200,MOBILE_GANDF);//RJS 28May99
			if (newitem)
			{
				SLong	vel = 100 + Math_Lib.rnd(200);			//RJS 16Nov99

				newitem->hdg = (Angles) Math_Lib.rnd();			//RJS 06Aug96
//DeadCode RJS 29Mar00 				newitem->vel_y = (Math_Lib.rnd(vel<<1)-vel)*1000;//RJS 16Nov99
				newitem->pitch = Angles(Math_Lib.rnd(ANGLES_90Deg)-ANGLES_45Deg);//RJS 29Mar00
				newitem->vel_ = vel * 1000;						//RJS 16Nov99
				newitem->CalcVels();
//DEADCODE CSB 09/11/99 				newitem->velhori += 300 - vely;					//RJS 26Nov98

				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSkinDebris
//Author		Robert Slater
//Date			Wed 14 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchSkinDebris(mobileitem* launcher, WorldStuff& worldptr)
{
	if (desiredFPS <= realFPS)					//RJS 11Jun99
	{
		int				count;
		TransientItem*	newitem;
		SLong			tot = 2 + Math_Lib.rnd(4);

		for (count = 0; count < tot; count++)
		{
			newitem = LaunchUnguidedMissile(	launcher,		
												DebrisMechShape,
												300,MOBILE_DEBRIS);//RJS 28May99
			if (newitem)
			{
				SLong	vel = 100 + Math_Lib.rnd(200);

				newitem->hdg = (Angles) Math_Lib.rnd();			
//DeadCode RJS 29Mar00 				newitem->pitch = (Angles) Math_Lib.rnd(16000);	
				newitem->roll = (Angles) Math_Lib.rnd();	
//DeadCode RJS 29Mar00 				newitem->vel_y = (Math_Lib.rnd(vel<<1)-vel)*1000;
				newitem->pitch = Angles(Math_Lib.rnd(ANGLES_90Deg)-ANGLES_45Deg);//RJS 29Mar00
				newitem->vel_ = vel*1000;
				newitem->CalcVels();
//DEADCODE CSB 09/11/99 				newitem->velhori += 300 - vely;			
				newitem->TransRandom = 0;							//RJS 16Aug96

				if ((newitem->shape >= DebrisStartShape) && (newitem->shape <= DebrisEndShape))
				{
					DebrisAnimData*	adptr = (DebrisAnimData*) newitem->Anim;//RJS 20Jan99
					adptr->frameno = Math_Lib.rnd(4);
				}

				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDeadACPart
//Author		Martin Alderton
//Date			Fri 29 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchDeadACPart(AirStruc* launcher,BitFlags bitflag, WorldStuff &worldptr, Bool	blowup)
{
//DeadCode RJS 7Jun00 	TransientItem*	newitem;
//DeadCode RJS 7Jun00 	AircraftAnimData*	adptr2 = (AircraftAnimData* )launcher->Anim;
//DeadCode RJS 7Jun00 
//DeadCode RJS 7Jun00 	newitem = LaunchUnguidedMissile((mobileitem* )launcher,
//DeadCode RJS 7Jun00 									launcher->shape,
//DeadCode RJS 7Jun00 									LIFETIME_ACPART,MOBILE_DEADACPART);
//DeadCode RJS 7Jun00 	if (newitem)
//DeadCode RJS 7Jun00 	{
//DeadCode RJS 7Jun00 		//Set 3D to only draw the dead part
//DeadCode RJS 7Jun00 
//DeadCode RJS 7Jun00 		AircraftAnimData*	adptr = (AircraftAnimData* )newitem->Anim;
//DeadCode RJS 7Jun00 
//DeadCode RJS 7Jun00 //DeadCode RJS 09Jun97		adptr->imagemaptail = adptr2->imagemaptail;
//DeadCode RJS 7Jun00 //DeadCode RJS 09Jun97		adptr->imagemapbtmwing = adptr2->imagemapbtmwing;
//DeadCode RJS 7Jun00 //DeadCode RJS 09Jun97		adptr->imagemapfuselage = adptr2->imagemapfuselage;
//DeadCode RJS 7Jun00 //DeadCode RJS 09Jun97		adptr->imagemapother = adptr2->imagemapother;
//DeadCode RJS 7Jun00 //DeadCode RJS 09Jun97		adptr->imagemaptopwing = adptr2->imagemaptopwing;
//DeadCode RJS 7Jun00 		adptr->imagemapemblem = adptr2->imagemapemblem;
//DeadCode RJS 7Jun00 //DeadCode RJS 27May97		adptr->vapourtrail = 0;
//DeadCode RJS 7Jun00 
//DeadCode RJS 7Jun00 		if (blowup)
//DeadCode RJS 7Jun00 		{
//DeadCode RJS 7Jun00 			SLong	vel = 100+Math_Lib.rnd(200);				//RJS 16Nov99
//DeadCode RJS 7Jun00 
//DeadCode RJS 7Jun00 			newitem->hdg = (Angles) Math_Lib.rnd();			//RJS 06Aug96
//DeadCode RJS 7Jun00 //DeadCode RJS 29Mar00 			newitem->vel_y = (Math_Lib.rnd(vel<<1)-vel)*1000;	//RJS 16Nov99
//DeadCode RJS 7Jun00 			newitem->pitch = Angles(Math_Lib.rnd(ANGLES_90Deg)-ANGLES_45Deg);//RJS 29Mar00
//DeadCode RJS 7Jun00 			newitem->vel_ = vel*1000;							//RJS 16Nov99
//DeadCode RJS 7Jun00 			newitem->CalcVels();
//DeadCode RJS 7Jun00 //DEADCODE CSB 09/11/99 			newitem->velhori = 300 - newitem->vely;			//RJS 06Aug96
//DeadCode RJS 7Jun00 		}
//DeadCode RJS 7Jun00 		else
//DeadCode RJS 7Jun00 			newitem->hdg += ANGLES_180Deg;						//RJS 07Nov96
//DeadCode RJS 7Jun00 
//DeadCode RJS 7Jun00 		UWord	localdamflag;									//RJS 31Oct96
//DeadCode RJS 7Jun00 
//DeadCode RJS 7Jun00 		localdamflag = 0x0FFFF;		//All dead					//RJS 31Oct96
//DeadCode RJS 7Jun00 		localdamflag &= ~(BS_DEAD<<bitflag);					//RJS 31Oct96
//DeadCode RJS 7Jun00 
//DeadCode RJS 7Jun00 //DeadCode RJS 09Jun97		adptr->dammageflags = localdamflag;	//(BS_DEAD<<bitflag) + (BS_DEAD<<BF_TheRest);//RJS 31Oct96
//DeadCode RJS 7Jun00 
//DeadCode RJS 7Jun00 		newitem->TransRandom = Math_Lib.rnd();
//DeadCode RJS 7Jun00 
//DeadCode RJS 7Jun00 		AddTransientItemToWorld(newitem, worldptr);
//DeadCode RJS 7Jun00 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBitsOffPart
//Author		Robert Slater
//Date			Thu 20 Feb 1997
//
//Description	Eject a 'detachable' part from a shape
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchBitsOffPart(	ItemPtr		launcher,
									ShapeNum	theShape,
									animptr&	adptrold,
									UByteP		damageptr,
									WorldStuff&	worldptr,
									UByte		lastdamage,
									UByteP		lastdamptr,
									UWord		blowup,
									Bool		noFlash	)
{
	TransientItem*	newitem;
//DeadCode RJS 14Jun00 	UByteP			flagptr;
//DeadCode RJS 14Jun00 	int				flagend;
//DeadCode RJS 14Jun00 	ShapeDescPtr	sdptr;
 	int				index;
	int				damageoffset;								//RJS 07Jul99
//DeadCode RJS 14Jun00 	animptr			adptrold;									//RJS 21Apr99
	animptr			adptr;										//RJS 21Apr99

//DeadCode RJS 14Jun00 	sdptr = SHAPESTUFF.GetShapePtr(theShape);
	newitem = LaunchUnguidedMissile((mobileitem* )launcher,
									theShape,
									LIFETIME_ACPART,MOBILE_DEADACPART,TRUE);//RJS 13Jul98
	if (newitem)
	{
//DeadCode RJS 14Jun00 		adptrold = launcher->Anim;								//RJS 21Apr99
		adptr = newitem->Anim;									//RJS 21Apr99

		if (launcher->Status.size == TRANSIENTSIZE)				//RJS 25Nov99
			newitem->Launcher = ((TransientItem*)launcher)->Launcher;//RJS 25Nov99


		//Set 3D to only draw the dead part
//DeadCode RJS 27Jul00 #ifndef	NDEBUG
//DeadCode RJS 27Jul00 	if (damageoffset == 157)
//DeadCode RJS 27Jul00 		INT3;
//DeadCode RJS 27Jul00 #endif

		damageoffset = adptrold.Offset(damageptr);
		SetBitsOff(theShape,adptrold,adptr,damageoffset);

		if (damageptr == lastdamptr)
			adptr[damageoffset] = lastdamage;
		else
			adptr[damageoffset] = BS_DAMLV2;

		adptr.SetItemState(DEAD);										//RJS 14Jun00

		if (blowup)
		{
			UWord	newhdg = Math_Lib.rnd();
			UWord	newpitch = (Math_Lib.rnd()*ANGLES_60Deg) >> 16;
			Float	sin_ang, cos_ang;
			SLong	vel = 100 + ((Math_Lib.rnd() * blowup)>>14);
			vel *= 1000; //CSB 09/11/99
			Float	velhori;
			SLong	vely;

			Math_Lib.high_sin_cos((Angles)newpitch,sin_ang,cos_ang);

			Float	fvel = Float(vel);
			vely = fvel * sin_ang;
			velhori = fvel * cos_ang;

			newitem->hdg = (Angles) newhdg;			
			newitem->vel_y = vely;
			Math_Lib.high_sin_cos(newitem->hdg,sin_ang,cos_ang);
			newitem->vel_x = velhori * sin_ang;
			newitem->vel_z = velhori * cos_ang;
		}

		newitem->TransRandom = Math_Lib.rnd();

// Break off relevant smoke trail from the launcher
		SHAPE.BreakOffTrail(newitem->Launcher,theShape,adptrold);	//RJS 20Sep00

		//Make sure this bits-off part can have no smoketrails!!!
		SLong				nolaunchers = ((MinAnimData*)adptr)->nolaunchers;
		MoveGunAnimData*	weap;
		if (nolaunchers)
		{
			weap = (MoveGunAnimData*) newitem->Anim;
			for (index=0; index < nolaunchers; index++)
			{
				weap->weaponlaunchers[index].hdg = 0;
				weap->weaponlaunchers[index].pitch = 0;
				weap->weaponlaunchers[index].Stores = 0;
				weap->weaponlaunchers[index].LoadedStores = 0;
				weap->weaponlaunchers[index].stationshape = 0;
			}
		}

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSmokeTrail
//Author		Paul.
//Date			Tue 30 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchSmokeTrail(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = LaunchGuidedMissile(	launcher,
									(itemptr )launcher,	//launcher==target
									SMKTRL,
									LIFETIME_SMOKETRAIL,MOBILE_SMOKETRAIL);
	if (newitem)
	{
		MoveGunAnimData*	adptr = (MoveGunAnimData*)newitem->Anim;
		WeapAnimData*		weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

		SHAPE.InitTrailFields((UByteP)weapon,0,32000,LT_FUEL);	//RJS 12Jan98

		LaunchVapourStream((UByteP)weapon,SMKTRL);				//RJS 17Sep97

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGroundExplosion
//Author		Paul.
//Date			Wed 1 May 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchGroundExplosion(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;

//DeadCode RJS 01Aug96	_Miles.PlaySample((FileNum) FIL_SFX_FIREBURN_LOOP, (rotitem) View_Point, (ItemBasePtr) launcher);

	newitem = SimplifiedSpriteLaunch(	launcher,
										LargeFireShape,
										LIFETIME_GROUNDEXP,MOBILE_GROUNDEXP);//RJS 09Oct96
	if (newitem)
	{
		_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_OILDRUM1+Math_Lib.rnd(5)), (ItemBasePtr) newitem);//RJS 22Nov96

		SLong	groundlevel;									//MS 07May96

		groundlevel = GetGroundLevel(newitem);					//RJS 14Apr99

//DeadCode RJS 02Oct96		if (newitem->World.Y<groundlevel)						//MS 07May96
			newitem->World.Y=groundlevel;						//MS 07May96

		newitem->TransRandom = SmokeLaunchDelay;

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSmoulder
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
void TransObj::LaunchSmoulder(mobileitem* launcher,WorldStuff& worldptr,Bool	uselch)
{
	TransientItem*	newitem;
	newitem = SimplifiedSpriteLaunch(	launcher,
										SmokeStack1Shape,		//RJS 24May00
										4500,					//RJS 25Jun99
										MOBILE_STATIONARY);

	if (newitem)
	{
		// Use this to say we are a large blob of smoke!		//RJS 24May00
		newitem->TransRandom = 0xFFFF;							//RJS 24May00

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGuidedExplosion
//Author		Robert Slater
//Date			Mon 8 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchGuidedExplosion(mobileitem* launcher,WorldStuff& worldptr)
{
//	TransientItem*	newitem;
//
//	newitem = LaunchGuidedMissile(launcher,(itemptr) launcher,BigExplosionShape,LIFETIME_BIGEXP,MOBILE_MOBEXP);
//
//	if (newitem)
//	{
//		AddTransientItemToWorld(newitem, worldptr);
//		_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_GROUND+Math_Lib.rnd(5)), (ItemBasePtr) newitem);//RJS 22Nov96
//	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGuidedBurning
//Author		Robert Slater
//Date			Mon 8 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchGuidedBurning(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										SmallFireShape,
										LIFETIME_SMALLFIRE,
										MOBILE_FIRE);

	if (newitem)
	{
		if ((launcher->Status.size >= MovingSize) && (launcher->Status.size != TransientSize))
		{
			newitem->Target = launcher;
			newitem->pitch = (Angles)50;
		}

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGuidedFire
//Author		Robert Slater
//Date			Tue 9 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchGuidedFire(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										PLUME1,
										6000,
										MOBILE_STATIONARY);

	if (newitem)
	{
		newitem->TransRandom = 0xFFFF;		// cos we want smoke...
		newitem->TimeOfLaunch -= 3000;		//low priority

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBombDrop
//Author		Robert Slater
//Date			Wed 24 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchBombDrop(mobileitem* launcher,ShapeNum	bombshape,SLong xpos, SLong ypos, SLong zpos,WorldStuff& worldptr,Bool	duff)
{
	TransientItem*	newitem;

//DeadCode AMM 02Jul99 	_Replay.guncameradelay=BOMBDELAY;					//AMM 25Jan99

	if (duff)													//RJS 03Dec96
		newitem = LaunchUnguidedMissile((mobileitem* )launcher,bombshape,LIFETIME_BOMB,MOBILE_MUSHROOM);//RJS 17Nov98
	else													
		newitem = LaunchUnguidedMissile((mobileitem* )launcher,bombshape,LIFETIME_BOMB,MOBILE_BOMB1STFRAME);	//RJS 3Oct00

	if (newitem)
	{
// want to keep recording for a while after bomb has been dropped so that
// people can see robs cool effects and stuff!
		newitem->hdg = Math_Lib.arctan(launcher->vel_x,launcher->vel_z);	//RJS 2Oct00
		if (launcher == Manual_Pilot.ControlledAC2)
		{
//DeadCode RJS 2Oct00 			newitem->hdg = Math_Lib.arctan(launcher->vel_x,launcher->vel_z);			//RJS 04May99
			if (Save_Data.gamedifficulty[GD_GUNCAMERAONTRIGGER] && !_DPlay.Implemented && !_Replay.Record)//RJS 02Jul99
			{													//RJS 02Jul99
				if (Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW)
				{
					_Replay.StartRecordFlag=TRUE;					//RJS 02Jul99
					_Replay.guncameradelay=BOMBDELAY;				//RJS 02Jul99
				}
			}													//RJS 02Jul99
		}

		if (!duff)												//RJS 10Jun99
			newitem->isArmed = 1;								//RJS 19May99

//DeadCode DAW 02Jul99 		if (Save_Data.gamedifficulty[GD_GUNCAMERAONTRIGGER] && !_DPlay.Implemented && !_Replay.Record)//AMM 25Jan99
//DeadCode DAW 02Jul99 		{													//AMM 25Jan99
//DeadCode DAW 02Jul99 			_Replay.StartRecordFlag=TRUE;					//AMM 25Jan99
//DeadCode DAW 02Jul99 		}													//AMM 25Jan99

//		newitem->pitch = ANGLES_0Deg;
		newitem->TransRandom = LIFETIME_BOMB - 150;
		newitem->World.X = xpos;								//RJS 29Aug96
		newitem->World.Y = ypos;								//RJS 29Aug96
		newitem->World.Z = zpos;								//RJS 29Aug96

//DeadCode RJS 17Oct00 		if ((_Replay.Playback || _Replay.Record) && launcher==Persons2::PlayerSeenAC)
//DeadCode RJS 17Oct00 		{
// velhori will be wrong so recalc
//DeadCode RJS 17Oct00 
//DEADCODE CB 09/11/99 			SLong totalvel=Persons2::PlayerSeenAC->vel_;
//DEADCODE CB 09/11/99 			SWord	sin_ang,cos_ang;
//DEADCODE CB 09/11/99 			Math_Lib.high_sin_cos(Persons2::PlayerSeenAC->pitch,sin_ang,cos_ang);
//DEADCODE CSB 09/11/99 			newitem->velhori = (totalvel * cos_ang)>>ANGLES_SHIFT;
//DeadCode RJS 17Oct00 		}

		if (	(launcher->Status.size == AIRSTRUCSIZE)					//RJS 27Jun00
			&&	(AirStrucPtr(launcher)->classtype->phrasename == PHRASE_HE111)	)	//RJS 27Jun00
		{
			newitem->TmpLaunchTime = newitem->LaunchTime;
			newitem->pitch = (Angles)(UWord(ANGLES_60Deg) + Math_Lib.rnd(ANGLES_30Deg));
		}
		else
			newitem->TmpLaunchTime = 0;

#ifdef	_BOMBBUG_
		::AfxTrace("VEL:  %d,%d,%d\n",newitem->vel_x,newitem->vel_y,newitem->vel_z);
#endif

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchVapourStream
//Author		Robert Slater
//Date			Thu 8 Aug 1996
//
//Description	Set up pointer to vapour animation
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord	TransObj::LaunchVapourStream(	UByteP		weapptr,
										ShapeNum	vapshape,
										SWord		velh,
										SWord		vely,
										SWord		resistance,
										UByteP		smkptr	)
{
	UWord			oldindex = 0;								//RJS 08Apr99
#ifndef	_NOSMOKETRAILS_											//RJS 08Apr99
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(vapshape);	//RJS 17Sep97
	WeapAnimData*	weapon = (WeapAnimData*) weapptr;			//RJS 17Sep97
	SByte			index;										//RJS 17Sep97

	if (weapon && sdptr->Type.VapourType)						//RJS 10Mar99
	{
		index = (SByte) weapon->hdg;						//RJS 12Jan98
		if (index < 0)
		{
			oldindex = -index;
//DeadCode RDH 13Apr99			index = 0;
		}

		if (index == 0)
		{
			if (	(weapon->LauncherType == LT_CONTRAIL)
				|| (weapon->LauncherType == LT_MUDDY))
				weapon->pitch = -1;							//RJS 12Jan98

			weapon->hdg = SHAPE.NextFreeVapour(velh,vely,resistance,smkptr);//RJS 09Apr98
		}
	}
#else
	#pragma message (__HERE__ "Smoke-trails disabled!")
#endif
	return(oldindex);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBigExplosion
//Author		Robert Slater
//Date			Mon 12 Aug 1996
//
//Description	For destroying something big, like a balloon
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchBigExplosion(mobileitem* launcher,WorldStuff& worldptr,ShapeNum	groundshape)
{
	TransientItem*	newitem;
	SLong			dx, dy, dz, dh;
	SLong			distance;
	SWord			thehdg, thehdg1;
	SWord			pitch;
	SLong			radius;
	SWord			sin_ang,cos_ang;
	ShapeDescPtr	sdptr;										//RJS 08Nov96
	SWord			shpsize;
	
//DeadCode RJS 20Oct00 	MinAnimData* mad = (MinAnimData* )launcher->Anim;			//RJS 08Nov96

	_Miles.PlayOnce((FileNum) (FIL_SFX_EXPLOSION_GROUND+Math_Lib.rnd(5)),launcher);

	sdptr = (ShapeDescPtr) SHAPESTUFF.GetShapePtr(groundshape);
	shpsize = sdptr->Size << 4;

	SLong	tot2 = (shpsize * 6)/832;
	SLong	totexp = (tot2 + Math_Lib.rnd(tot2))/2;
	SLong	i;

	for (i=0; i < totexp; i++)
	{
		newitem	= RelativeSpriteLaunch(launcher,groundshape,BEXP,Math_Lib.rnd(100),MOBILE_DELEXP);//DAW 03Sep98
		if (newitem)
		{
			MinAnimData*	mad = (MinAnimData*) newitem->Anim;
			mad->IsInvisible = 1;

			thehdg = Math_Lib.rnd();
			radius = Math_Lib.rnd(shpsize);

			Math_Lib.high_sin_cos((Angles)thehdg,sin_ang,cos_ang);		
			dx = (cos_ang * radius) / ANGLES_FRACT;					
			dz = (sin_ang * radius) / ANGLES_FRACT;					

			newitem->World.X += dx;
			newitem->World.Z += dz;
			newitem->World.Y += Math_Lib.rnd(250) - 125;

			AddTransientItemToWorld(newitem, worldptr);
		}
	}

//DeadCode DAW 27Nov98	LaunchSkinDebris(launcher,worldptr);
	LaunchSparkDebris(launcher,worldptr);			
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchMovingSmoke
//Author		Robert Slater
//Date			Mon 2 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchRealShockwave(mobileitem* launcher,UByte strength,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										ShockwaveShape,			//RJS 20Nov96
										54,MOBILE_DODAMAGE);			//RJS 13Aug00
	if (newitem)
	{
		if (launcher->Status.size == TRANSIENTSIZE)							//RJS 12Apr99
			newitem->Launcher = ((TransientItem*)launcher)->Launcher;		//RJS 12Apr99

		MissileAnimData*	adptr = (MissileAnimData*) newitem->Anim;
//DeadCode DAW 23Jun99 		adptr->hitstrength = (3*strength)>>1;								//RJS 1/20/99//RJS 26Feb99
 		adptr->hitstrength = strength;								//RJS 23Jun99

		newitem->isArmed = 1;												//RJS 10Jun99

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchRicochetSmoke
//Author		Robert Slater
//Date			Thu 5 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchRicochetSmoke(mobileitem* launcher,ShapeNum	theShape,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										theShape,
										LIFETIME_SMOKE,MOBILE_STATIONARY);
	if (newitem)
	{
		if (launcher->Status.size >= MOBILESIZE)
		{
			newitem->vel_y = launcher->vel_y;
			newitem->vel_x = launcher->vel_x;
			newitem->vel_z = launcher->vel_z;
			newitem->vel_ = launcher->vel_ ;
			newitem->hdg = launcher->hdg;
//DEADCODE CSB 09/11/99 			newitem->velhori = launcher->velhori;
		}
		SLong	groundlevel;								
//DeadCode RJS 19Feb98		ExplodeAnimData* adptr;

//		groundlevel = GetGroundLevel(newitem);					//RJS 14Apr99
//
//		if (newitem->World.Y<groundlevel)						
//			newitem->World.Y=groundlevel;

//DeadCode RJS 19Feb98		adptr = (ExplodeAnimData* )newitem->Anim;
//DeadCode RJS 19Feb98		adptr->frameno = Math_Lib.rnd(3);						//RJS 06Dec96
		newitem->roll = (Angles) 0;								//RJS 03Dec96
		newitem->pitch = (Angles) 1;							//RJS 06Dec96

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDustRing
//Author		Robert Slater
//Date			Sun 13 Oct 1996
//
//Description	Launches a ring of dust balls around an item
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDustRing(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	newitem = SimplifiedSpriteLaunch(	launcher,
										DRTSHK,					//RJS 15Dec99
										300,MOBILE_STATIONARY);

	if (newitem)
		AddTransientItemToWorld(newitem, worldptr);
}

 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 //Procedure		LaunchShockwave
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
 void	TransObj::LaunchShockwave(mobileitem* launcher,WorldStuff& worldptr)
 {
 	if (desiredFPS <= realFPS)					//RJS 11Jun99
 	{
 		TransientItem*	newitem;
 
 		newitem = SimplifiedSpriteLaunch(	launcher,
 											ExplosionShockShape,
 											100,MOBILE_STATIONARY);//no damage at the mo...
 		if (newitem)
 		{
 			Three_Dee.pMigLand->GetShadowAngles(newitem->World,newitem->hdg,newitem->pitch,newitem->roll);
 			newitem->World.Y += (METRES01*3);						//RJS 21Apr99
 
 			AddTransientItemToWorld(newitem, worldptr);
 		}
 	}
 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBirds
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
void	TransObj::LaunchBirds(mobileitem* launcher,Coords3D&	pos,ShapeNum	birdshape,SLong maxbirds, WorldStuff& worldptr)
{
	if (desiredFPS > realFPS)										//RJS 31Aug00
		maxbirds = 2;													//RJS 31Aug00

	TransientItem*	newitem = NULL;
	SLong			halfmax = maxbirds>>1;
	SLong			nobirds = halfmax + Math_Lib.rnd(halfmax);
	SLong			count;

	if (!birdshape)
		birdshape = BirdShape;

	for (count = 0; count < nobirds; count++)
	{
		newitem = SimplifiedSpriteLaunch(	launcher,		
											birdshape,
											LIFETIME_DEBRISLNCHR*4,MOBILE_BIRD);

		if (newitem)
		{
			SLong	vel = (150 + Math_Lib.rnd(50))*1000;

			newitem->World = pos;
			newitem->hdg = (Angles) Math_Lib.rnd();
			newitem->pitch = Angles(Math_Lib.rnd(ANGLES_30Deg));//RJS 29Mar00
			newitem->vel_ = vel;
//DeadCode RJS 29Mar00 			newitem->vel_y = vel>>2;		//y can only be max of 1/4 total vel
			newitem->CalcVels();

			AddTransientItemToWorld(newitem, worldptr);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchAmmoBoxes
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
void	TransObj::LaunchIgniteAmmoBoxes(mobileitem* launcher,UByte gindex,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	UWord			halfdetonate;
	UWord			detonate;
	ShapeNum		shapehit;
	MyGroundVector	pos;
	MinAnimData*	mad = (MinAnimData*) SHAPE.GetGroupItemAnim(launcher,shapehit,gindex,&pos);
	UWord			animoffset = launcher->Anim.Offset(mad);//((UByteP)mad) - ((UByteP)&launcher->Anim[0]);

	halfdetonate = (DEAD - mad->itemstate)*100;
	detonate = halfdetonate + Math_Lib.rnd(halfdetonate);

	newitem = SimplifiedSpriteLaunch(	launcher,
										ShockwaveShape,
										detonate,MOBILE_AMMODEATH);
	if (newitem)
	{
		SLong	groundlevel;								
		groundlevel = GetGroundLevel(newitem);					//RJS 14Apr99

		newitem->roll = (Angles) CLUSTA;						//RJS 26May99
		newitem->pitch = (Angles) shapehit;
		newitem->TransRandom = animoffset;						//RJS 20Nov98
		newitem->World.Y = groundlevel;

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDustTrail
//Author		Robert Slater
//Date			Thu 31 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDustTrail(	mobileitem* launcher,
									WorldStuff& worldptr,
									SByte	distance)
{
/*	TransientItem*	newitem;
	Bool			isplane = TRUE;								//RDH 08Nov96
	SLong			dx,dz,radius;								//RJS 13Nov96
	ANGLES			direction = launcher->hdg + ANGLES_180Deg;//RJS 13Nov96

	if (launcher->velhori < MPHHALF)							//RJS 15Dec96
		return;

	if (distance > -1)											//RJS 13Nov96
		isplane = FALSE;

	if (isplane)												//RJS 13Nov96
	{
		newitem = SimplifiedSpriteLaunch(	launcher,
											DustShape,
											LIFETIME_RICOCHET,MOBILE_STATIONARY);//RJS 20Apr98

		dx = 0;													//RJS 13Nov96
		dz = 0;													//RJS 13Nov96
	}
	else
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);//RJS 13Nov96
		SWord			sin_ang,cos_ang;						//RJS 13Nov96

		newitem = SimplifiedSpriteLaunch(	launcher,
											DustShape,
											LIFETIME_RICOCHET*2,MOBILE_STATIONARY);//RJS 20Apr98

		radius = sdptr->sz << 4;								//RJS 13Nov96

		Math_Lib.high_sin_cos(direction,sin_ang,cos_ang);		//RJS 13Nov96
		dx = (cos_ang * radius) / ANGLES_FRACT;					//RJS 13Nov96
		dz = (sin_ang * radius) / ANGLES_FRACT;					//RJS 13Nov96
	}

	if (newitem)
	{
//DeadCode RJS 19Nov96		SLong	groundlevel = Land_Scape.GetGroundLevel((itemptr )newitem);//RJS 13Nov96

		if (isplane)
			direction += (Angles)(Math_Lib.rnd(ANGLES_90Deg) - ANGLES_45Deg);//RDH 08Nov96

//DeadCode RJS 19Nov96		newitem->World.Y=groundlevel;
		newitem->World.X += dx;									//RJS 13Nov96
		newitem->World.Z += dz;									//RJS 13Nov96
		newitem->hdg = direction;

		if (!isplane && (distance == 1))						//RJS 13Nov96
			newitem->velhori = 200 + Math_Lib.rnd(200);		
		else
			newitem->velhori = Math_Lib.rnd(200);

		AddTransientItemToWorld(newitem, worldptr);
	}*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDustTrail2
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
void	TransObj::LaunchDustTrail2(	mobileitem* launcher,
									WorldStuff& worldptr	)
{
	TransientItem*	newitem;

	newitem = LaunchGuidedMissile(	launcher,
									(itemptr )launcher,
									DUSSHP,
									LIFETIME_SMOKETRAIL,MOBILE_SMOKETRAIL);
	if (newitem)
	{
		MoveGunAnimData*	adptr = (MoveGunAnimData*)newitem->Anim;
		WeapAnimData*		weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

		SHAPE.InitTrailFields((UByteP)weapon,0,32000,LT_DUST);	//RJS 12Jan98

		LaunchVapourStream((UByteP)weapon,DUSSHP);				//RJS 17Sep97

		if (SHAPESTUFF.GetShapePtr(launcher->shape)->AnimDataSize==AIRCRAFTANIM)
		{
			AircraftAnimData*	aptr = (AircraftAnimData*)launcher->Anim;
			aptr->hasdust = TRUE;
		}

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchMushroomCloud
//Author		Robert Slater
//Date			Wed 6 Nov 1996
//
//Description	Throw several dust shapes into the air
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchMushroomCloud(mobileitem* launcher,SLong impact,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	SLong			count = 0;
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);
	SLong			sx = sdptr->sx<<4;
	SLong			sz = sdptr->sz<<4;
	SLong			sx2 = sx<<1;
	SLong			sz2 = sz<<1;
	SLong			totsize = sdptr->Size << 4;
	SLong			tot = totsize + ((Math_Lib.rnd()*totsize)>>16);

	sdptr = SHAPESTUFF.GetShapePtr(BDUST);
	if (desiredFPS <= realFPS)					//RJS 11Jun99
	{															//RJS 28May99
		tot /= (sdptr->Size << 4);								//RJS 28May99
		tot *= impact;											//RJS 28May99
		tot /= 16;												//RJS 28May99
	}															//RJS 28May99
	else														//RJS 28May99
		tot = 1;												//RJS 28May99

	do
	{
		newitem = RelativeSpriteLaunch(		launcher,
											launcher->shape,
											BDUST,
											500,					//RJS 18May99
											MOBILE_STATIONARY);		//RJS 06Oct98
		if (newitem)
		{
//DeadCode RJS 28May99 			sdptr = SHAPESTUFF.GetShapePtr(BDUST);
//DeadCode RJS 23May00  			newitem->DrawOffset += sdptr->Size << 2;

			newitem->World.X += Math_Lib.rnd(sx2) - sx;
			newitem->World.Z += Math_Lib.rnd(sz2) - sz;
			newitem->World.Y += Math_Lib.rnd(500) - 250;

			AddTransientItemToWorld(newitem, worldptr);
		}
		count++;
	}while (count < tot);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSmokePuff
//Author		Robert Slater
//Date			Thu 14 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchSmokePuff(	mobileitem* launcher,
									ShapeNum	theShape,
									SLong		xpos,
									SLong		ypos,
									SLong		zpos,
									WorldStuff& worldptr)
{
	TransientItem*	newitem;
	newitem = SimplifiedSpriteLaunch(	launcher,
										theShape,
										134,MOBILE_CRATER);
	
	if (newitem)
	{
		UWord	randno = Math_Lib.rnd();
		SWord	heading = ANGLES_180Deg + ((randno>>3) - 4096);
		
		SLong	vel = Math_Lib.rnd()>>12;

		newitem->hdg = (Angles) (launcher->hdg + heading);
		newitem->vel_ = vel*1000;								//RJS 16Nov99
//DEADCODE CSB 09/11/99 		newitem->velhori = Math_Lib.rnd()>>12;
		newitem->World.X = xpos;
		newitem->World.Y = ypos;
		newitem->World.Z = zpos;
		newitem->TransRandom = 0;							//RJS 09Dec96

//DEADCODE CSB 09/11/99 		newitem->vely = 16-newitem->velhori;
		newitem->pitch = ANGLES_90Deg;							//RJS 29Mar00
//DeadCode RJS 29Mar00 		newitem->vel_y = Math_Lib.rnd(vel>>1)*1000;				//RJS 16Nov99
		newitem->CalcVels();

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFuelBarrels
//Author		Robert Slater
//Date			Fri 22 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchFuelBarrels(mobileitem* launcher,WorldStuff& worldptr)
{
	if (desiredFPS <= realFPS)					//RJS 11Jun99
	{
		TransientItemPtr	newitem;						
		UByte			count;

		for (count = 0; count < 4; count++)
		{
			newitem = SimplifiedSpriteLaunch((mobileitem*)launcher,CLUSTF,//RJS 26May99
											LIFETIME_DEBRISLNCHR,MOBILE_DEBRIS);
			if (newitem)
			{
				SLong	vel = 100 + Math_Lib.rnd(150);

//DeadCode RJS 29Mar00 				newitem->vel_y = Math_Lib.rnd(vel) * 1000;		//RJS 16Nov99
				newitem->vel_ = vel*1000;						//RJS 16Nov99
				newitem->hdg = (Angles)Math_Lib.rnd();
				newitem->pitch = Angles(Math_Lib.rnd(ANGLES_60Deg));//RJS 29Mar00
				newitem->CalcVels();
//DEADCODE CSB 09/11/99 				newitem->velhori = 100 + Math_Lib.rnd(100);			//RJS 16Aug96
				newitem->World.Y += 100;						//RJS 03Jun99
				newitem->TransRandom = Math_Lib.rnd();				//RJS 16Aug96
				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchScatteredFire
//Author		Robert Slater
//Date			Fri 6 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchScatteredFire(mobileitem* launcher,ShapeNum	shapehit,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shapehit);
	ShapeDescPtr	sdptr2 = SHAPESTUFF.GetShapePtr(SmallScatFireShape);
	ULong			area_m = (sdptr->sx << 4) * (sdptr->sz << 4);
	ULong			area_s = (sdptr2->sx << 4) * (sdptr2->sz << 4);
	ULong			count = area_m / area_s;
	ULong			i;
	SLong			sx = (sdptr->sx << 4);
	SLong			sz = (sdptr->sz << 4);
	ShapeNum		theshape = SmallScatFireShape;

	if (desiredFPS <= realFPS)					//RJS 11Jun99
	{
		count /= 16;
		count = count + Math_Lib.rnd(count) + 1;
		if (count > 16)
		{
			theshape = LargeScatFireShape;
			count /= 8;
			if (count > 16)
				count = 16;
		}
	}
	else
		count = 1;												//RJS 28May99

	for (i=0; i < count; i++)
	{
		newitem = SimplifiedSpriteLaunch(launcher,theshape,Math_Lib.rnd(1500)+1500,MOBILE_STATIONARY);//RJS 11Jan98
		if (newitem)
		{
			newitem->World.X += ((sx * Math_Lib.rnd())>>15) - sx;
			newitem->World.Z += ((sz * Math_Lib.rnd())>>15) - sz;
			newitem->World.Y = GetGroundLevel(newitem);			//RJS 14Apr99

			AddTransientItemToWorld(newitem,worldptr);
		}
	}

	LaunchGuidedFire(launcher,worldptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchVapourTransient
//Author		Robert Slater
//Date			Tue 27 May 1997
//
//Description	Gives an invisible transient vapour item an already known
//				vapour list....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	TransObj::LaunchVapourTransient(	mobileitem*	launcher,
											SLong			xpos,
											SLong			ypos,
											SLong			zpos,
											int				index,
											int				lifetime,
											WorldStuff&		worldptr,
											ShapeNum		theshape)
{
	Bool	retval = TRUE;										//RJS 13May99
	if (trailcounter >= MaxTrails)								//RJS 06Apr99
		retval = KillOldestTrail(launcher);						//RJS 13May99

	if (retval)
	{
		TransientItemPtr	newitem;
		newitem = SimplifiedSpriteLaunch(	launcher,
											theshape,							//RJS 03Dec97
											lifetime,
											MOBILE_STATIONARY);		//RJS 20Apr98

		if (newitem)
		{
			MoveGunAnimData*	adptr = (MoveGunAnimData*) newitem->Anim;
	
			if (launcher->Status.size == TRANSIENTSIZE)				//RJS 21Apr99
				newitem->Launcher = NULL;							//RJS 21Apr99

			newitem->World.X = xpos;
			newitem->World.Y = ypos;
			newitem->World.Z = zpos;

			adptr->weaponlaunchers[0].hdg = -index;					//RJS 21Jan99
			adptr->weaponlaunchers[0].pitch = -1;					//RJS 28Jan98
			//Don't really care what type, as long as its valid...
			adptr->weaponlaunchers[0].LauncherType = LT_VAPOUR;	//RJS 13Apr99
			AddTransientItemToWorld(newitem, worldptr);

			trailcounter++;											//RJS 06Apr99
		}
		else
			retval = FALSE;
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchRocket
//Author		Robert Slater
//Date			Tue 3 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItem* TransObj::LaunchRocket(mobileitem* launcher,ShapeNum	weapshape,SLong xpos, SLong ypos, SLong zpos, WorldStuff& worldptr)
{
	TransientItem* newitem;

	newitem=LaunchUnguidedMissile(launcher,weapshape,LIFETIME_ROCKET,MOBILE_ROCKET);//RJS 26mAR99

	if (newitem)
	{
		SLong	vx,vy,vz,vhori;									//RJS 10Jun99 //CSB 09/11/99

//DeadCode AMM 18Jun99 		if (launcher == Persons2::PlayerSeenAC)					//RJS 10Jun99
//DeadCode DAW 28Jun99 		if (launcher == Persons2::PlayerSeenAC && !_Replay.Playback)//AMM 18Jun99
		if (launcher == Persons2::PlayerSeenAC && !_Replay.Playback && !_Replay.Record)//AMM 28Jun99
		{
			((AirStrucPtr)launcher)->fly.pModel->CalcLauncherVel(1500,vx,vy,vz);

			newitem->vel_x = vx;
			newitem->vel_y = vy;
			newitem->vel_z = vz;
//DEADCODE CSB 09/11/99 			newitem->velhori = Math_Lib.distance3d(vx,vz,0);
			newitem->hdg = Math_Lib.arctan(vx,vz);
		}
		else
		{
			SLong	temp;
			Float	sin_ang,cos_ang;
			SLong	totVel = launcher->vel_ + 1500000;
			Float	totalvel = Float(totVel);						 //RJS 16Nov99


			Math_Lib.high_sin_cos(launcher->pitch,sin_ang,cos_ang);

			newitem->vel_y = totalvel * sin_ang;
//DEADCODE CSB 09/11/99 			newitem->velhori = (totalvel * cos_ang)>>ANGLES_SHIFT;
			Float	velhori = totalvel * cos_ang; //CSB 09/11/99

			Math_Lib.high_sin_cos(launcher->hdg,sin_ang,cos_ang);

//DEADCODE CSB 09/11/99 			temp = (newitem->velhori * sin_ang)>>ANGLES_SHIFT; newitem->velx = (SWord )temp;
//DEADCODE CSB 09/11/99 			temp = (newitem->velhori * cos_ang)>>ANGLES_SHIFT; newitem->velz = (SWord )temp;
			newitem->vel_x = velhori * sin_ang;						  //CB 09/11/99
			newitem->vel_z = velhori * cos_ang;						  //CB 09/11/99
			newitem->vel_ = totVel;								//RJS 16Nov99
		}

		newitem->World.X = xpos;								
		newitem->World.Y = ypos;								
		newitem->World.Z = zpos;

		//Give it a 3 second burn burst....						//RJS 15Jun99!!
		newitem->TransRandom = 300;								//RJS 15Jun99

		MoveGunAnimData	*adptr = (MoveGunAnimData*)newitem->Anim;
		WeapAnimData*	weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

		adptr->itemstate = DEAD;

		SHAPE.InitTrailFields((UByteP)weapon,0,5000,LT_FUEL);

//DeadCode RJS 14Jun00 		_Miles.PlayOnce(FIL_SFX_MISSILE2, newitem);
		LaunchVapourStream((UByteP)weapon,newitem->shape);

//Dead		if (launcher == Manual_Pilot.ControlledAC2)				//RJS 19May99
			newitem->isArmed = 1;								//RJS 19May99

		AddTransientItemToWorld(newitem,worldptr);
	}
	return newitem;					
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFuelDrop
//Author		Robert Slater
//Date			Tue 10 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItem* TransObj::LaunchFuelDrop(mobileitem* launcher,ShapeNum	weapshape,WeapAnimData*	weapon,SLong xpos, SLong ypos, SLong zpos, WorldStuff& worldptr)
{
	TransientItem*	newitem;
	newitem=LaunchUnguidedMissile(launcher,weapshape,LIFETIME_BOMB,MOBILE_FUELDROP);//RJS 28May98

	if (newitem)
	{
		SLong	temp;
		SWord	sin_ang,cos_ang;
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(weapshape);

		if (sdptr->Type.VapourType)												//RJS 10Mar98
		{
			MoveGunAnimData*	adptr = (MoveGunAnimData*)newitem->Anim;
//DeadCode RJS 20Oct00 			DirectAnimData*		newweapon = (DirectAnimData*) &adptr->weaponlaunchers[0];

			//Inherit leaks...
			adptr->weaponlaunchers[0].hdg = weapon->hdg;
			adptr->weaponlaunchers[0].pitch = weapon->pitch;
		}

		weapon->LoadedStores = 0;

		newitem->World.X = xpos;								
		newitem->World.Y = ypos;								
		newitem->World.Z = zpos;

		newitem->TransRandom = 1;								//RJS 28May98

		SWord	tip = Math_Lib.rnd() >> 5;
//		tip <<= 1;

		newitem->TransRandom += tip;
		newitem->pitch = ANGLES_0Deg;
		if (((AirStrucPtr)launcher)->AcIsPlayer())
		{
			SLong	vx,vy,vz;

//DeadCode DAW 28Jun99 			if (!_Replay.Playback)
			if (!_Replay.Playback && !_Replay.Record)			//AMM 28Jun99
			{
				((AirStrucPtr)launcher)->fly.pModel->CalcParachuteVel(vx,vy,vz,launcher->hdg,launcher->pitch,launcher->roll,launcher->vel_/10000,-10000, launcher->World.Y);	//CSB 13/06/99	

				newitem->vel_x = vx;
				newitem->vel_y = vy;
				newitem->vel_z = vz;
//DEADCODE CSB 09/11/99 				newitem->velhori = Math_Lib.distance3d(vx,vz,0);
				newitem->hdg = Math_Lib.arctan(vx,vz);				//DAW 11May99
				newitem->pitch = launcher->pitch;
				newitem->roll = launcher->roll;
			}
			else
			{
				SLong	temp;
				Float	sin_ang,cos_ang;
				SLong	totalvel = launcher->vel_;

				Math_Lib.high_sin_cos(launcher->pitch,sin_ang,cos_ang);
				newitem->vel_y = totalvel * sin_ang;
//DEADCODE CSB 09/11/99 				newitem->velhori = (totalvel * cos_ang)>>ANGLES_SHIFT;
				SLong velhori = totalvel * cos_ang; //CSB 09/11/99
				Math_Lib.high_sin_cos(launcher->hdg,sin_ang,cos_ang);
//DEADCODE CSB 09/11/99 				temp = (newitem->velhori * sin_ang)>>ANGLES_SHIFT; newitem->velx = (SWord )temp;
//DEADCODE CSB 09/11/99 				temp = (newitem->velhori * cos_ang)>>ANGLES_SHIFT; newitem->velz = (SWord )temp;
				newitem->vel_x = velhori * sin_ang;					  //CB 09/11/99
				newitem->vel_z = velhori * cos_ang;					  //CB 09/11/99

				newitem->hdg=launcher->hdg;
				newitem->pitch = launcher->pitch;
				newitem->roll = launcher->roll;
			}
		}
		else
			newitem->vel_y -= 200000;				//A bit of a push...//RJS 11Dec98 //CSB 09/11/99

		AddTransientItemToWorld(newitem,worldptr);
	}
	return newitem;		
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGunPuff
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
void TransObj::LaunchGunPuff(mobileitem* launcher,SLong xpos, SLong ypos, SLong zpos, WorldStuff& worldptr)
{
	TransientItem*	newitem;
	newitem=LaunchUnguidedMissile(launcher,MigPuffShape,6,MOBILE_GANDF);//RJS 20Apr98

	if (newitem)
	{
		newitem->World.X = xpos;								
		newitem->World.Y = ypos;								
		newitem->World.Z = zpos;								

		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchWeapon
//Author		Robert Slater
//Date			Tue 10 Jun 1997
//
//Description	Launches a weapon depending on the weapon's type.
//				Also will eventually log the weapon for comms...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 09Apr99 void TransObj::LaunchWeapon(AirStrucPtr	ac,
SLong TransObj::LaunchWeapon(bool received,						//AMM 09Apr99
							AirStrucPtr	ac,					//AMM 09Apr99
							WeapAnimData*	weapon,
							ULong			wpIndex,			//RJS 15Nov99
							SLong xpos, SLong ypos, SLong zpos,
							WorldStuff& worldptr,
							SLong		muzvel,
							SLong		muzdelay,
							Bool		unarmed)
{
	LnchrType	wptype = (LnchrType) (weapon->LauncherType & LT_MASK);
//DeadCode RJS 20Oct00 	SLong		itemweight = 0;
	ShapeNum	weaponshape = GunfireShape;
	ULong		failchance;
//DeadCode RJS 12Oct00 	SWord		amount = 1;
	SWord		amount = 0;
	int			virtualBulletsScale = 1;

	if (weapon->stationshape)
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(weapon->stationshape);
		weaponshape = (ShapeNum)sdptr->Type.shapenumber;
	}
	else
		weaponshape = SHAPE.GetWeaponShape(weapon);

//DeadCode RJS 27May98	failchance = weapon->SubDamage * Math_Lib.rnd();

	if (unarmed)												//RJS 27May98
	{
		switch (wptype)
		{
			case LT_BOMB:
			case LT_NAPALM:
			case LT_ROCKET:
				amount = 1;
				LaunchBombDrop(ac,weaponshape,xpos,ypos,zpos,worldptr,unarmed);
				break;
			case LT_FUEL:
				amount = 1;
				LaunchFuelDrop(ac,weaponshape,weapon,xpos,ypos,zpos,worldptr);
				break;
		}
	}
	else
	{
		switch (wptype)
		{
			case LT_BOMB:
				amount = 1;
				LaunchBombDrop(ac,weaponshape,xpos,ypos,zpos,worldptr);
				break;
			case LT_NAPALM:
				amount = 1;
				LaunchBombDrop(ac,weaponshape,xpos,ypos,zpos,worldptr);
				break;
			case LT_ROCKET:
				amount = 1;
				LaunchRocket(ac,weaponshape,xpos,ypos,zpos,worldptr);
				break;
			case LT_FUEL:
				amount = 1;
				LaunchFuelDrop(ac,weaponshape,weapon,xpos,ypos,zpos,worldptr);
				break;
			case LT_CANNON:												//RJS 21Jun00
				virtualBulletsScale = 2;								//RJS 21Jun00
			case LT_BULLET:
			{
				AircraftAnimData*	acadptr = (AircraftAnimData*) ac->Anim;

// dont want muzzle flash in playback or in comms if another player is firing

				if (!_Replay.Playback && (!(_DPlay.Implemented && ac->uniqueID.commsmove && ac!=Persons2::PlayerSeenAC)))					//RJS 17Jun99
				{
					if (wptype == LT_CANNON)							//RJS 25Aug00
						acadptr->cannonshooting = 1;					//RJS 25Aug00
					else
						acadptr->gunshooting = 1;						//RJS 25Aug00
				}

				PlayGunSound((mobileitem* )ac,worldptr);
				TransientItem*	currbul;
				if (wptype == LT_CANNON)								//RJS 21Jun00
				{
					currbul = LaunchOneGunBullet(ac,muzvel,weaponshape,xpos,ypos,zpos,worldptr,weapon->hdg,weapon->pitch);//RJS 29Mar99
					LaunchGunPuff(ac,xpos,ypos,zpos,worldptr);
				}
				else
				{
					currbul = LaunchOneGunBullet(ac,muzvel,weaponshape,xpos,ypos,zpos,worldptr,weapon->hdg,weapon->pitch);//RJS 29Mar99
//TempCode RJS 15Nov99 					if (	!_Miles.CockpitView					//RJS 07Jun99
//TempCode RJS 15Nov99 						&& (desiredFPS <= realFPS)//RJS 11Jun99
//TempCode RJS 15Nov99 						&& (ac->shape == F51)	)
//TempCode RJS 15Nov99 					{
//TempCode RJS 15Nov99 						TransientItem*		newitem;
//TempCode RJS 15Nov99 						newitem = LaunchUnguidedMissile(	ac,
//TempCode RJS 15Nov99 															BULCSE,
//TempCode RJS 15Nov99 															33,
//TempCode RJS 15Nov99 															MOBILE_STATIONARY);
//TempCode RJS 15Nov99 						if (newitem)
//TempCode RJS 15Nov99 						{
//TempCode RJS 15Nov99 							newitem->World.X = xpos;
//TempCode RJS 15Nov99 							newitem->World.Y = ypos;
//TempCode RJS 15Nov99 							newitem->World.Z = zpos;
//TempCode RJS 15Nov99 
//TempCode RJS 15Nov99 							AddTransientItemToWorld(newitem,worldptr);
//TempCode RJS 15Nov99 						}
//TempCode RJS 15Nov99 					}
				}


//DeadCode AMM 09Apr99				if (!_Replay.Playback)						//RJS 08Apr99
				int	noVirtualBullets = ac->classtype->noGuns / virtualBulletsScale;	//RJS 21Jun00
				if (!received)									//AMM 09Apr99
				{
					MissileAnimData*	adptr = (MissileAnimData*) currbul->Anim;
					adptr->lastmissile = weapon->currLink;		//RJS 15Nov99
					adptr->pad = 2;
					adptr->novirtualguns = noVirtualBullets;	//RJS 21Jun00
					adptr->wpIndex = wpIndex;					//RJS 15Nov99
					if (adptr->lastmissile)
					{
						TransientItemPtr	tmpitm = (TransientItemPtr)adptr->lastmissile;
						if (tmpitm->isDeleted)// || tmpitm->Status.deadtime)				//RJS 03Jun99
						{
							adptr->lastmissile = NULL;									//RJS 03Jun99
							adptr->pad = 3;
						}
						else															//RJS 03Jun99
							tmpitm->isOwned = 1;										//RJS 03Jun99
					}
				}
				amount = noVirtualBullets;						//RJS 20Apr99

				weapon->currLink = ULong(currbul);				//RJS 15Nov99
			}
			break;
//			case LT_CANNON:
//				PlayGunSound((mobileitem* )ac,worldptr);
//				LaunchOneGunBullet(ac,muzvel,weaponshape,xpos,ypos,zpos,worldptr,ANGLES_1_67Deg);//RJS 27Jul98
//				LaunchGunPuff(ac,xpos,ypos,zpos,worldptr);
//				break;
		}
	}

	if (weapon->LoadedStores)									//RJS 27May98
	{
		weapon->currGun++;											//RJS 15Nov99

		if (amount > weapon->LoadedStores)							//RJS 11Jun99
		{
			amount = weapon->LoadedStores;								//RJS 6Oct00
			weapon->LoadedStores = 0;								//RJS 11Jun99
		}
		else														//RJS 11Jun99
			weapon->LoadedStores-=amount;							//RJS 11Jun99
	}

	return amount;													//RJS 11Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTrailTail
//Author		Robert Slater
//Date			Mon 16 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchTrailTail( mobileitem*	launcher,
								SLong		xpos,
								SLong		ypos,
								SLong		zpos,
								ShapeNum	globshape,
								WorldStuff&	world)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										globshape,
										LIFETIME_SMOKE>>1,
										MOBILE_GANDF);
	if (newitem)
	{
//DeadCode RJS 19Feb98		ExplodeAnimData*	adptr = (ExplodeAnimData*) newitem->Anim;

		newitem->World.X = xpos;
		newitem->World.Y = ypos;
		newitem->World.Z = zpos;

//DeadCode RJS 19Feb98		adptr->frameno = 52;

		AddTransientItemToWorld(newitem,world);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchClouds
//Author		Robert Slater
//Date			Mon 16 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchClouds()
{
//DeadCode RJS 28May99 	if (	(View_Point->World.Y > Land_Scape.cloud_base)
//DeadCode RJS 28May99 		&&	(CloudTotal < 20)
//DeadCode RJS 28May99 		&&	!Three_Dee.IsPaused()	)							//RJS 27Feb98
//DeadCode RJS 28May99 	{
//DeadCode RJS 28May99 		if (CloudTimer > 0)
//DeadCode RJS 28May99 			CloudTimer -= Timer_Code.FRAMETIME;
//DeadCode RJS 28May99 		else
//DeadCode RJS 28May99 		{
//DeadCode RJS 28May99 			SWord	rndheading, rndpitch;
//DeadCode RJS 28May99 			SLong	xpos, ypos, zpos;
//DeadCode RJS 28May99 			SLong	wx, wy, wz, ccount, noclouds;
//DeadCode RJS 28May99 			SWord	sin_ang,cos_ang,tan_ang;
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			rndheading = Math_Lib.rnd(ANGLES_60Deg) - (SWord)ANGLES_30Deg;
//DeadCode RJS 28May99 			rndpitch = Math_Lib.rnd(ANGLES_60Deg) - (SWord)ANGLES_30Deg;
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			rndheading += (SWord)View_Point->hdg;
//DeadCode RJS 28May99 			rndpitch += (SWord)View_Point->pitch;
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			Math_Lib.high_sin_cos((Angles) -rndheading,sin_ang,cos_ang);
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			// distance away is -65536
//DeadCode RJS 28May99 			xpos = (sin_ang << 16) >> (ANGLES_SHIFT-2);
//DeadCode RJS 28May99 			zpos = (cos_ang << 16) >> (ANGLES_SHIFT-2);
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			Math_Lib.high_sin_cos((Angles) -rndpitch,sin_ang,cos_ang);
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			ypos = (sin_ang << 16) >> (ANGLES_SHIFT-2);
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			wx = xpos + View_Point->World.X;
//DeadCode RJS 28May99 			wy = ypos + View_Point->World.Y;
//DeadCode RJS 28May99 			wz = zpos + View_Point->World.Z;
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			if (wy > (Land_Scape.cloud_base+2000))				//RJS 02Sep97
//DeadCode RJS 28May99 			{
//DeadCode RJS 28May99 				TransientItem*	newitem;
//DeadCode RJS 28May99 				WorldStuff*	world = mobileitem::currworld;
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 				noclouds = Math_Lib.rnd() >> 13;
//DeadCode RJS 28May99 				for (ccount=0; ccount < noclouds; ccount++)
//DeadCode RJS 28May99 				{
//DeadCode RJS 28May99 					newitem = SimplifiedSpriteLaunch(	Manual_Pilot.ControlledAC2,
//DeadCode RJS 28May99 														CLOUD1,
//DeadCode RJS 28May99 														2000,	//RJS 02Sep97
//DeadCode RJS 28May99 														MOBILE_GANDF);
//DeadCode RJS 28May99 					if (newitem)
//DeadCode RJS 28May99 					{
//DeadCode RJS 28May99 						CloudTimer = 300;
//DeadCode RJS 28May99 						CloudTotal++;
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 						newitem->World.X = wx + ((Math_Lib.rnd() - 32768)>>1);
//DeadCode RJS 28May99 						newitem->World.Y = wy + ((Math_Lib.rnd() - 32768)>>1);
//DeadCode RJS 28May99 						newitem->World.Z = wz + ((Math_Lib.rnd() - 32768)>>1);
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 						AddTransientItemToWorld(newitem,*world);
//DeadCode RJS 28May99 					}
//DeadCode RJS 28May99 				}
//DeadCode RJS 28May99 			}
//DeadCode RJS 28May99 		}
//DeadCode RJS 28May99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchCloneGun
//Author		Robert Slater
//Date			Mon 22 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchCloneGun(	mobileitem* launcher,
									mobileitem* bulletlnchr,
									Nationality nat,
									SWord		noclones,
									SWord		weapindex,
									SWord		weapindex2,
									SWord		bulletdelay,
									SWord		lchtype,
									WorldStuff& worldptr)
{
	if (noclones)														//RJS 20Jun00
	{
		TransientItemPtr	newitem;
		newitem = LaunchUnguidedMissile(	bulletlnchr,
											CloneShape,
											bulletdelay - Timer_Code.FRAMETIME,	//CSB 23Jun00
											MOBILE_CLONEGUN );

		if (newitem)
		{
			CloneAnimData*	adptr = (CloneAnimData*) newitem->Anim;

			newitem->nationality = nat;
			newitem->TransRandom = noclones;
			newitem->vel_ = bulletlnchr->vel_;
			newitem->Status.deadtime <<= bulletlnchr->Status.deadtime;//RJS 27May99

			adptr->weapindex = weapindex2;				//Swap indexes around,
			adptr->weapindex2 = weapindex;				//... so as to alternate fire
			adptr->originitm = (ULong) launcher;
			adptr->delay = bulletdelay;
			adptr->shapename = bulletlnchr->shape;
			adptr->lnchtype = lchtype;

			adptr->IsInvisible = 1;				//RJS 27Apr99

// This ensures all shooters fire the same amount of bullets
			newitem->isOwned = 1;										//RJS 12Nov00

			AddTransientItemToWorld(newitem, worldptr);
		}
	}
	else
		ClearGunFlash(launcher);										//RJS 12Nov00
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchNapalmStrike
//Author		Robert Slater
//Date			Thu 22 Jan 1998
//
//Description	Number of secondary napalm spread shapes depends on velocity..
//				and travels in same direction
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchNapalmStrike(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	int				dx, dz, thedist;
	SWord			hdg = launcher->hdg;
	SWord			sin_ang,cos_ang;
	int				i;
	SLong			wx, wz, noblobs;
	SWord			timedelay = 0;
	Bool			isInRange = FALSE;

	wx = launcher->World.X;
	wz = launcher->World.Z;

	thedist = 750;
	
	Math_Lib.high_sin_cos((Angles)hdg,sin_ang,cos_ang);

	dx = (sin_ang * thedist) >> 15;
	dz = (cos_ang * thedist) >> 15;

	if (WithinVisibleRange(launcher->World,400000))				//RJS 30Apr99
	{
		newitem = SimplifiedSpriteLaunch((mobileitem*)launcher,EXPLO,20,MOBILE_STATIONARY);
		if (newitem)
		{
//DeadCode RJS 23May00 			newitem->DrawOffset = 100;
			AddTransientItemToWorld(newitem,worldptr);
		}

		isInRange = TRUE;
	}

//DEADCODE CSB 09/11/99 	noblobs = 1 + (launcher->velhori/160);
	noblobs = 1 + (launcher->vel_/160000); //CSB 09/11/99
	SWord	thetime;

	ItemPtr	realLauncher;
	if (launcher->Status.size == TRANSIENTSIZE)								//RJS 05May99
		realLauncher = ((TransientItemPtr)launcher)->Launcher;			//RJS 05May99
	else
		realLauncher = launcher;

	if (noblobs > 8)
		noblobs = 8;

	SLong	activecnt = 0;										//RJS 13May99
	if (desiredFPS > realFPS)					//RJS 28May99
		noblobs = 1;											//RJS 28May99

	for (i=0; i < noblobs; i++)									//RJS 09Feb98
	{															//RJS 09Feb98
		thetime = 250 - timedelay;
		if (thetime > 0)
		{
			newitem = SimplifiedSpriteLaunch(	launcher,			//RJS 09Feb98
												EMPTY,				//RJS 09Feb98
												timedelay,			//RJS 09Feb98
												MOBILE_NAPALM);		//RJS 09Feb98
			if (newitem)											//RJS 09Feb98
			{														//RJS 09Feb98
				if (!isInRange)
				{
					MinAnimData* mad = (MinAnimData*) newitem->Anim;
					mad->IsInvisible = 1;
				}
				if (i==0)										//RJS 11May99
					newitem->Target = realLauncher;				//RJS 11May99

				activecnt--;									//RJS 13May99
				if (activecnt <= 0)								//RJS 13May99
					activecnt = 2;								//RJS 13May99
				else											//RJS 13May99
					newitem->Status.deadtime = 1;				//RJS 13May99

				newitem->Launcher = realLauncher;					//RJS 05May99
				newitem->pitch = (Angles) thetime;
				newitem->hdg = launcher->hdg;
				newitem->World.X = wx;
				newitem->World.Z = wz;
				newitem->TransRandom = thetime;						//RJS 03Dec98
				AddTransientItemToWorld(newitem,worldptr);			//RJS 09Feb98
			}														//RJS 09Feb98

			wx += dx;
			wz += dz;
			timedelay += 20;
		}
		else
			break;
	}

	LaunchFingersFire(launcher,worldptr);

	if (desiredFPS <= realFPS)					//RJS 11Jun99
	{
		if (WithinVisibleRange(launcher->World,100000))				//RJS 30Apr99
		{
			int				count;
			Float			sin, cos;
			Float			velhori;
			SLong			vely;

			for (count = 0; count < 8; count++)							//DAW 01Sep98
			{
				newitem = SimplifiedSpriteLaunch(launcher,SPARK,250,MOBILE_GANDF);//RJS 28May99
				if (newitem)
				{
					vely = 150000 + (Math_Lib.rnd(150)*1000);//RJS 16Nov99

					newitem->hdg = (Angles) Math_Lib.rnd();			//RJS 06Aug96
					newitem->vel_y = vely;							//RJS 26Nov98
//DEADCODE CB 09/11/99 					newitem->velhori = 300 - vely;					//RJS 26Nov98 //CB 09/11/99
					velhori = 300000. - Float(vely);				//CB 09/11/99

					Math_Lib.high_sin_cos(newitem->hdg, sin, cos);	  //CB 09/11/99
					newitem->vel_x = velhori * sin;					  //CB 09/11/99
					newitem->vel_y = velhori * cos;					  //CB 09/11/99

					AddTransientItemToWorld(newitem,worldptr);
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchCanopyEject
//Author		Robert Slater
//Date			Thu 19 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchCanopyEject(mobileitem* launcher,WorldStuff& worldptr)
{
//DeadCode RJS 20Oct00 	Bool	alreadylaunched = FALSE;
	if (SHAPESTUFF.GetShapePtr(launcher->shape)->AnimDataSize == AIRCRAFTANIM)
	{
		if (	(launcher != Persons2::PlayerSeenAC)			//RJS 06Sep00
			&&	(launcher->World.Y < FT_4000)	)					//RJS 26Sep00
			return;												//RJS 06Sep00

		AirStrucPtr	ac=	NULL;
		Bool	alreadylaunched = FALSE;
		if (launcher->Status.size == TRANSIENTSIZE)
		{
			MinAnimData*	mad = (MinAnimData*)launcher->Anim;	//RJS 19Oct00
			if (mad->repair)
				alreadylaunched = TRUE;
		}
		else
		{
			ac=*launcher;
			alreadylaunched = ac->weap.Ejected;
		}
		if (!alreadylaunched)
		{
			AircraftAnimData	*adptr = (AircraftAnimData*)launcher->Anim;

			if (adptr->CANOPY != BS_DEAD)							//RJS 22Nov99
			{
				SLong				OpenChance = adptr->CANOPY - BS_DAMLV2;

				bool	canopyState=false;									//RJS 28Aug00	//JIM 20Oct00
				if (ac)	
					canopyState = ac->fly.pModel->CanopyOpen();		//RJS 28Aug00

				OpenChance = (OpenChance * Math_Lib.rnd()) >> 16;
				if (	(OpenChance < 32)								//RJS 28Aug00
					||	canopyState										//RJS 28Sep00
					||	(ac->classtype->aerobaticfactor == AEROBATIC_LOW)	)	//RJS 28Sep00
				{
					if (!ac)
					{
						MinAnimData*	mad = (MinAnimData*)launcher->Anim;//RJS 19Oct00
						mad->repair=1;
					}
					else
					{
						if (ac->classtype->aerobaticfactor == AEROBATIC_LOW)	//RJS 28Sep00
							canopyState = true;							//RJS 28Sep00

						ac->weap.Ejected=TRUE;						//RJS 23Feb00
//DeadCode RJS 21Sep00 						ac->ai.diaryptr->AddEjected(ac,totalpilots);	//RJS 21Sep00
					}

					TransientItem*	newitem;

//DeadCode RJS 9Nov00 					if (!canopyState)	_Miles.PlayOnce(FIL_SFX_CANOPY_BLOW, launcher);	//RJS 28Aug00

					newitem=LaunchUnguidedMissile(launcher,launcher->shape,75,MOBILE_CANOPY);
					if (newitem)
					{
						SLong				totalpilots;
						MinAnimData*		mad = (MinAnimData*)newitem->Anim;

						mad->itemstate = DEAD;							//RJS 28Aug00

						//Set 3D to only draw the dead part
						SetBitsOff(launcher->shape,launcher->Anim,newitem->Anim,&adptr->CANOPY-&launcher->Anim);//RJS 14Jun00

						if (canopyState)								//RJS 28Aug00
							mad->IsInvisible = 1;						//RJS 28Aug00

						totalpilots = SHAPE.GetTotalPilots(launcher->shape);		//RJS 06Dec99
						if (!totalpilots)	totalpilots = 1;

						if (ac)											//RJS 21Sep00
							ac->ai.diaryptr->AddEjected(ac,totalpilots);	//RJS 21Sep00

						newitem->TransRandom = totalpilots + (totalpilots<<8);		//RJS 06Dec99
						if (!ac)
						{
							TransientItem*	thelauncher = (TransientItem*)*launcher;
							thelauncher->LaunchTime += (totalpilots*150)+75;
						}

						AddTransientItemToWorld(newitem, worldptr);

						if (launcher == Manual_Pilot.ControlledAC2)						//RJS 21May98
						{																//RJS 21May98
							if (View_Object)											//RJS 21May98
								View_Object->SetToParachuteView(NULL);				//RJS 06Jun99
						}
					}
				}
			}
			else
			{
				UWord	noBlokes = 1;									//RJS 26Jul00

				if (!ac)
				{
					MinAnimData*	mad = (MinAnimData*)launcher->Anim;//RJS 19Oct00
					mad->repair=1;
				}
				else
				{
					ac->weap.Ejected=TRUE;						//RJS 23Feb00
					ac->ai.diaryptr->AddEjected(ac,1);			//RJS 21Feb00
				}

				EjectParachutist(ac,noBlokes,1,worldptr);
			}
		}
	}
}																//RJS 14Dec99

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGroupThug
//Author		Robert Slater
//Date			Mon 2 Mar 1998
//
//Description	Bashes up-to two items in a group
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchGroupThug(	item*		launcher,
									ShapeNum	theshape,
									int			prevgroupno,
									int			prevdep,
									int			nextdep,
									Coords3D	posPrev,
									Coords3D	posNext,
									UWord		panimoff,
									UWord		nanimoff,	
									ItemPtr		theShooter	)	//RJS 05Jul99
{
	TransientItem*	newitem;
	SLong			thetime,t1, t2;
	UByte			disable1, disable2;
	WorldStuff*	worldptr = mobileitem::currworld;
	SLong			tph,tnh;


	prevdep *= 1000;											//RJS 23Dec99
	prevdep /= 127;		
	
	nextdep *= 1000;											//RJS 23Dec99
	nextdep /= 127;

	if (prevdep < 0)
	{
		t1 = -prevdep;
		disable1 = 1;
	}
	else
	{
		disable1 = 0;
		t1 = prevdep;
	}

	if (nextdep < 0)
	{
		disable2 = 1;
		t2 = -nextdep;
	}
	else
	{
		t2 = nextdep;
		disable2 = 0;
	}

	// Vary the times a bit...
	tph = t1>>2;
	tnh = t2>>2;
	t1 = ((3*t1)>>2) + Math_Lib.rnd(tph);
	t2 = ((3*t2)>>2) + Math_Lib.rnd(tnh);

	if (t1 > t2)
		thetime = t1;
	else
		thetime = t2;

	newitem = SimplifiedSpriteLaunch(	launcher,	
										theshape,		
										thetime,	
										MOBILE_THUG);
	
	if (newitem)
	{
		ThugAnimData	*adptr = (ThugAnimData*) newitem->Anim;

		if (adptr)
		{
			adptr->prevcount = t1;
			adptr->nextcount = t2;
			adptr->disableprev = disable1;
			adptr->disablenext = disable2;
			adptr->pXPos = posPrev.X;
			adptr->pYPos = posPrev.Y;
			adptr->pZPos = posPrev.Z;
			adptr->nXPos = posNext.X;
			adptr->nYPos = posNext.Y;
			adptr->nZPos = posNext.Z;
			adptr->panimoff = panimoff;
			adptr->nanimoff = nanimoff;
		}

		newitem->Launcher = theShooter;		//RJS 05Jul99
		newitem->Target = launcher;			//RJS 05Jul99

		AddTransientItemToWorld(newitem,*worldptr);
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//					Common launch code for transients
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimplifiedSpriteLaunch
//Author		Paul.
//Date			Fri 26 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItemPtr
TransObj::SimplifiedSpriteLaunch(	Item* launcher,
									ShapeNum shape,
									SLong lifetime,
									AutoMoveCodeTypeSelect movecode)
{
	if (!launcher)
		INT3;

	TransientItemPtr newitem = new TransientItem;

	if (newitem)
	{
		transientcounter++;										//PD 24Jul96
//DeadCode RJS 23May00 		newitem->DrawOffset = 0;								//RJS 27Nov98
		newitem->Target = NULL;									//RJS 18Feb98
		newitem->Launcher = launcher;
		newitem->nexttogo = NULL;
		newitem->nextmobile = NULL;
		newitem->nexttrans = NULL;
		newitem->waypoint = NULL;

		newitem->hdg =
			newitem->pitch =
			newitem->roll	= ANGLES_0Deg;

		newitem->Next = NULL;

		newitem->World = launcher->World;

//DEADCODE CSB 09/11/99 		newitem->velx =
//DEADCODE CSB 09/11/99 			newitem->vely =
//DEADCODE CSB 09/11/99 			newitem->velz =
//DEADCODE CSB 09/11/99 			newitem->velhori = 0;
		newitem->vel_x =		//CSB 09/11/99
			newitem->vel_y =	//CSB 09/11/99
			newitem->vel_z =    //CSB 09/11/99
			newitem->vel_ = 0;	//RJS 16Nov99

//DeadCode PD 08Oct96		newitem->collisiontime = 0;								//PD 10Sep96

		newitem->shape = shape;

		if (shape<1)// || shape>EMPTY)									//RJS 5Sep00
			_Error.EmitSysErr("Sprite launch (%d)",shape);

		newitem->LaunchTime = lifetime;

		newitem->movecode = movecode;
		newitem->TransRandom = 0;
//DeadCode RJS 16Dec99		newitem->isOwned = 0;									//RJS 29Mar99
		newitem->TimeOfLaunch = View_Object->TimeOfDay();		//RJS 19May99

		(void )SHAPE.SetAnimData(newitem,0);					//RDH 23Sep96

		newitem->TransientItem::AddToList();
	}
	return (newitem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RelativeSpriteLaunch
//Author		Robert Slater
//Date			Fri 27 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItemPtr
TransObj::RelativeSpriteLaunch(	Item* launcher,
								ShapeNum parentshape,
								ShapeNum shape,
								SLong lifetime,
								AutoMoveCodeTypeSelect movecode)
{
	TransientItemPtr newitem = new TransientItem;

	if (newitem)
	{
		transientcounter++;								

//DeadCode RJS 20Oct00 		ShapeDescPtr	sdptr = (ShapeDescPtr) SHAPESTUFF.GetShapePtr(parentshape);
		
//DeadCode RJS 23May00 		newitem->DrawOffset = sdptr->Size<<2;		//make it a quarter size...
		newitem->Launcher = launcher;
		newitem->nexttogo = NULL;
		newitem->nextmobile = NULL;
		newitem->nexttrans = NULL;
		newitem->waypoint = NULL;

		if ((launcher->Status.size >= MovingSize) && (launcher->Status.size != TRANSIENTSIZE))
			newitem->Target = launcher;									
		else
			newitem->Target = NULL;									

		newitem->hdg =
			newitem->pitch =
			newitem->roll	= ANGLES_0Deg;

		newitem->Next = NULL;

		newitem->World = launcher->World;

//DEADCODE CSB 09/11/99 		newitem->velx =
//DEADCODE CSB 09/11/99 			newitem->vely =
//DEADCODE CSB 09/11/99 			newitem->velz =
//DEADCODE CSB 09/11/99 			newitem->velhori = 0;
		newitem->vel_x =			//CSB 09/11/99
			newitem->vel_y =		//CSB 09/11/99
			newitem->vel_z =
			newitem->vel_ = 0;		//CSB 09/11/99

		newitem->shape = shape;

		newitem->LaunchTime = lifetime;

		newitem->movecode = movecode;
		newitem->TransRandom = 0;
//DeadCode RJS 16Dec99		newitem->isOwned = 0;									//RJS 29Mar99
		newitem->TimeOfLaunch = View_Object->TimeOfDay();		//RJS 19May99

		(void )SHAPE.SetAnimData(newitem,0);

		newitem->TransientItem::AddToList();
	}
	return (newitem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchUnguidedMissile
//Author		Paul.
//Date			Fri 26 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItemPtr
TransObj::LaunchUnguidedMissile(	mobileitem* launcher,
									ShapeNum shape,
									SLong lifetime,
									AutoMoveCodeTypeSelect	movecode,
									Bool	inheritanimdata	)
{
	TransientItemPtr newitem = new TransientItem;

	if (newitem)
	{
		transientcounter++;
//DeadCode RJS 23May00 		newitem->DrawOffset = 0;								//RJS 27Nov98
		newitem->Target = NULL;									//RJS 18Feb98
		newitem->Launcher = launcher;
		newitem->nexttogo = NULL;
		newitem->nextmobile = NULL;
		newitem->nexttrans = NULL;
		newitem->waypoint = NULL;

		if (launcher->Status.size >= RotatedSize)
		{
			newitem->hdg = launcher->hdg;
			newitem->pitch = launcher->pitch;
			newitem->roll = launcher->roll;
		}
		else
		{
			newitem->hdg = ANGLES_0Deg;
			newitem->pitch = ANGLES_0Deg;
			newitem->roll = ANGLES_0Deg;
		}

		newitem->Next = NULL;

		newitem->World = launcher->World;

		if (launcher->Status.size >= MobileSize)
		{
			SLong wx = 0, wy = 0, wz = 0;
			if((launcher == Persons2::PlayerSeenAC) && (Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW))
				MissManCampSky().GetWind(launcher->World.Y, wx, wy, wz);
	
			newitem->vel_x = launcher->vel_x + wx;
			newitem->vel_y = launcher->vel_y + wy;
			newitem->vel_z = launcher->vel_z + wz;
			newitem->vel_ = launcher->vel_;
//DEADCODE CSB 09/11/99 			newitem->velhori = launcher->velhori;
		}
		else
		{
			newitem->vel_x = 0;
			newitem->vel_y = 0;
			newitem->vel_z = 0;
			newitem->vel_  = 0;
//DEADCODE CSB 09/11/99 			newitem->velhori = 0;
		}

//DeadCode PD 08Oct96		newitem->collisiontime = 0;								//PD 10Sep96

		newitem->shape = shape;

		newitem->LaunchTime = lifetime;

		newitem->movecode = movecode;
		newitem->TransRandom = 0;
//DeadCode RJS 16Dec99		newitem->isOwned = 0;									//RJS 29Mar99
		newitem->TimeOfLaunch = View_Object->TimeOfDay();		//RJS 19May99

		if (inheritanimdata == FALSE)
			SHAPE.SetAnimData(newitem,0);						//RJS 13Jul98
		else													//RJS 13Jul98
		{														//RJS 13Jul98
			animptr	srcanim = launcher->Anim;					//RJS 21Apr99
			newitem->Anim = launcher->Anim;						//RJS 21Apr99
			newitem->Anim = SHAPE.CopyAnimData(srcanim,shape);	//RJS 21Apr99
		}

		newitem->TransientItem::AddToList();
	}
	return (newitem);
}
///////////////////////////////////////////////////////////////////
//
// This version adds to world as well...
//
//
//
//
TransientItemPtr
TransObj::LaunchUnguidedMissile(	item* launcher,
									ShapeNum shape,
									SLong lifetime,
									AutoMoveCodeTypeSelect	movecode,
									Coords3D	&xyz,
									ANGLES		hdg,
									ANGLES		pitch,
//DEADCODE CSB 09/11/99 									SWord		velx,
//DEADCODE CSB 09/11/99 									SWord		vely,
//DEADCODE CSB 09/11/99 									SWord		velz,
//DEADCODE CSB 09/11/99 									SWord		velh,
//DEADCODE CSB 09/11/99 									SWord		vel,
									SLong		velx,
									SLong		vely,
									SLong		velz,
									SLong		vel,
									Nationality nat
									)
{
	TransientItemPtr newitem = new TransientItem;

	if (newitem)
	{
		transientcounter++;
//DeadCode RJS 23May00 		newitem->DrawOffset = 0;								//RJS 27Nov98
		newitem->Target = NULL;									//RJS 18Feb98
		newitem->nationality = nat;
		newitem->Launcher = launcher;
		newitem->nexttogo = NULL;
		newitem->nextmobile = NULL;
		newitem->nexttrans = NULL;
		newitem->waypoint = NULL;

		newitem->hdg = hdg;
		newitem->pitch = pitch;
		newitem->roll = ANGLES_0Deg;

		newitem->Next = NULL;

		newitem->World = xyz;

		newitem->vel_x = velx;
		newitem->vel_y = vely;
		newitem->vel_z = velz;

//DEADCODE CSB 09/11/99 		newitem->velhori = velh;
		newitem->vel_ = vel;

//DeadCode PD 08Oct96		newitem->collisiontime = 0;								//PD 10Sep96

		newitem->shape = shape;

		newitem->LaunchTime = lifetime;

		newitem->movecode = movecode;
		newitem->TransRandom = 0;
//DeadCode RJS 16Dec99		newitem->isOwned = 0;									//RJS 29Mar99
		newitem->TimeOfLaunch = View_Object->TimeOfDay();		//RJS 19May99

		(void )SHAPE.SetAnimData(newitem);

		switch (movecode)										//RJS 03Feb00
		{														//RJS 03Feb00
		case MOBILE_PUFFTRAVEL:									//RJS 03Feb00
		{
			MinAnimData*	mad = (MinAnimData*)newitem->Anim;	//RJS 03Feb00
			mad->IsInvisible = 1;								//RJS 03Feb00
			break;												//RJS 03Feb00
		}
		case MOBILE_PAC:										//RJS 03Feb00
		{
			// We only want collision & parachute anim when alive...
			MinAnimData*	mad = (MinAnimData*)newitem->Anim;	//RJS 03Feb00
			mad->itemstate = DEAD;								//RJS 03Feb00
			break;												//RJS 03Feb00
		}
		}														//RJS 03Feb00

		newitem->TransientItem::AddToList();

		AddTransientItemToWorld(newitem, *newitem->currworld);				//JIM 25Sep96
	}
	return (newitem);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGuidedMissile
//Author		Paul.
//Date			Fri 26 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItemPtr
TransObj::LaunchGuidedMissile(	mobileitem* launcher,
								itemptr		target,
								ShapeNum	shape,
								SLong		lifetime,
								AutoMoveCodeTypeSelect	movecode)
{
	TransientItemPtr newitem = new TransientItem;

	if (newitem)
	{
		transientcounter++;										//PD 24Jul96
//DeadCode RJS 23May00 		newitem->DrawOffset = 0;								//RJS 27Nov98
		newitem->Launcher = launcher;
		newitem->Target = target;

		newitem->nexttogo = NULL;
		newitem->nextmobile = NULL;
		newitem->nexttrans = NULL;
		newitem->waypoint = NULL;

		newitem->hdg = launcher->hdg;
		newitem->pitch = launcher->pitch;
		newitem->roll = launcher->roll;

		newitem->Next = NULL;

		newitem->World = launcher->World;

		newitem->vel_x = launcher->vel_x;
		newitem->vel_y = launcher->vel_y;
		newitem->vel_z = launcher->vel_z;
		newitem->vel_ = launcher->vel_;							//RJS 16Nov99

//DEADCODE CSB 09/11/99 		newitem->velhori = launcher->velhori;

//DeadCode PD 08Oct96		newitem->collisiontime = 0;								//PD 10Sep96

		newitem->shape = shape;

		newitem->LaunchTime = lifetime;

		newitem->movecode = movecode;
		newitem->TransRandom = 0;
//DeadCode RJS 16Dec99		newitem->isOwned = 0;									//RJS 29Mar99
		newitem->TimeOfLaunch = View_Object->TimeOfDay();		//RJS 19May99

		(void )SHAPE.SetAnimData(newitem,0);					//RDH 23Sep96

		newitem->TransientItem::AddToList();
	}
	return (newitem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSuperLauncher
//Author		Robert Slater
//Date			Mon 22 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItemPtr
TransObj::LaunchSuperLauncher(	item*		launcher,
								ShapeNum	weapshape,
								SLong		lifetime,
								AutoMoveCodeTypeSelect	movecode,
								Coords3D	&xyz,
								ANGLES		hdg,				//PD 13Nov97
								ANGLES		pitch,				//PD 13Nov97
//DEADCODE CSB 09/11/99 								SWord		velx,
//DEADCODE CSB 09/11/99 								SWord		vely,
//DEADCODE CSB 09/11/99 								SWord		velz,
//DEADCODE CSB 09/11/99 								SWord		velh,
//DEADCODE CSB 09/11/99 								SWord		vel,
								SLong		velx,
								SLong		vely,
								SLong		velz,
								SLong		vel,
								Nationality nat,
								SWord		weapindex,
								SWord		weapindex2,
								SWord		bulletdelay,
								SWord		noclones,
								SWord		lchtype,
								WorldStuff	&worldptr,
								Bool		isArmed	)			//RJS 27May99
{
	TransientItemPtr	newitem = new TransientItem;
	if (newitem)
	{
		transientcounter++;
//DeadCode RJS 23May00 		newitem->DrawOffset = 0;								//RJS 27Nov98
		newitem->Target = NULL;									//RJS 18Feb98
		newitem->nationality = nat;
		newitem->Launcher = launcher;
		newitem->nexttogo = NULL;
		newitem->nextmobile = NULL;
		newitem->nexttrans = NULL;
		newitem->waypoint = NULL;

		newitem->hdg = hdg;
		newitem->pitch = pitch;
		newitem->roll = ANGLES_0Deg;

		newitem->Next = NULL;
		newitem->World = xyz;

		newitem->vel_x = velx;
		newitem->vel_y = vely;
		newitem->vel_z = velz;

//DEADCODE CSB 09/11/99 		newitem->velhori = velh;
		newitem->vel_ = vel;

		newitem->shape = weapshape;
		newitem->LaunchTime = lifetime;
		newitem->movecode = movecode;
		newitem->TransRandom = 0;
		newitem->isOwned = 0;								//RJS 29Mar99
		newitem->TimeOfLaunch = View_Object->TimeOfDay();		//RJS 19May99

		(void )SHAPE.SetAnimData(newitem);

		newitem->TransientItem::AddToList();

		AddTransientItemToWorld(newitem, worldptr);

		bool	isAC = false;									//RJS 16Jun99
		if (launcher->Status.size == AIRSTRUCSIZE)						//RJS 10Jul00
		{
			MoveGunAnimData*	ladptr= (MoveGunAnimData*) ((AirStrucPtr)newitem->Launcher)->Anim;
			WeapAnimData*		weapon = &ladptr->weaponlaunchers[weapindex];

			MissileAnimData*	adptr = (MissileAnimData*) newitem->Anim;
			adptr->lastmissile = weapon->currLink;				//RJS 15Nov99
			adptr->pad = 4;
			if (	(weapon->LauncherType == LT_BULLET_REAR)			//RJS 24May00
				||	((weapon->LauncherType & LT_MASK) == LT_MOVEGUN)	)	//RJS 24May00
				adptr->novirtualguns = 0;//bulletdelay / Timer_Code.FRAMETIME;	//CSB 20Jun00
			else														//RJS 24May00
				adptr->novirtualguns = ((AirStrucPtr)newitem->Launcher)->classtype->noGuns;//RJS 29Mar99

			adptr->wpIndex = weapindex;							//RJS 15Nov99
			if (adptr->lastmissile)
			{
				TransientItemPtr	tmpitm = (TransientItemPtr)adptr->lastmissile;
				if (tmpitm->isDeleted)// || tmpitm->Status.deadtime)				//RJS 03Jun99
				{
					adptr->lastmissile = NULL;									//RJS 03Jun99
					adptr->pad = 5;
				}
				else															//RJS 03Jun99
					tmpitm->isOwned = 1;										//RJS 03Jun99
			}

			weapon->currLink = ULong(newitem);					//RJS 15Nov99

			isAC = true;										//RJS 16Jun99
		}

		if (!isArmed)											//RJS 27May99
			newitem->Status.deadtime = 1;						//RJS 27May99
		
		newitem->isArmed = 1;								//RJS 09Jul99	

// LaunchSuperLauncher will always launch at least one bullet,
// so at this level, we want (nobullets-1) clones...
		if (noclones)
			LaunchCloneGun((mobileitem*)launcher,newitem,nat,noclones-1,weapindex,weapindex2,bulletdelay,lchtype,worldptr);//RJS 20Jun00
		else
			ClearGunFlash(launcher);									//RJS 12Nov00
	}
	return (newitem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GeneralItemDamage
//Author		Robert Slater
//Date			Wed 24 Jul 1996
//
//Description	Launches relevant death animation for a shape
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::GeneralItemDamage(mobileitem* launcher,
									mobileitem*	missile,
									WorldStuff&	worldptr,
									SByte	groupindex,
									Bool	accollision)
{
}

////////////////////////////////////////////////////////////////////////////////
//
//						Transient item movecodes
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileBullet
//LastModified:	PD 12Sep96
//Author		Paul.
//Date			Fri 26 Apr 1996									//JIM 29Oct96
//
//Description	Must do collision test before first movement....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileBullet(TransientItemPtr transit,WorldStuff& world)
{

//	if (transit->shape<0 || transit->shape>200)
//		_Error.EmitSysErr("Bad shape number in bullet");

	if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)			//DAW 31Jul96
		transit->LaunchTime=0;
	else
	{
		// While frametime is in 50ths
 		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			Coords3D	hitcoords;
			UByte		theArea;								//RJS 28Apr99
			SLong	groundheight = GetGroundLevel(transit,theArea);//RJS 28Apr99

			if (!transit->Status.deadtime)
			{
				if (transit->World.Y<=groundheight)
				{
//DeadCode RJS 28Apr99					UByte	theArea = Three_Dee.GetLandType();		//MS 30Nov98

					hitcoords = transit->World;						//RJS 10Nov98
					hitcoords.Y = groundheight;						//RJS 10Nov98

					DoImpactGround(transit,hitcoords,theArea);		//MS 30Nov98

					MissileAnimData*	adptr = (MissileAnimData*)transit->Anim;
					adptr->IsInvisible = 1;
					transit->Status.deadtime = 1;

					if (adptr->lastmissile)
					{
						TransientItem*	olditm = (TransientItem*) adptr->lastmissile;

						olditm->isOwned = 0;
						adptr->lastmissile = 0;
						adptr->pad = 6;
					}
				}
				else
				{
					//Test for collision with other
					//items
					itemptr	 hititem;
					int	gindex;										//RJS 10Nov98

					hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);

					if (hititem)	//_Collide.TransCollTest((MovingItemPtr )transit, hititem, hitcoords, gindex))//RDH 26Nov96
					{
						MinAnimData*	mad = (MinAnimData*)transit->Anim;
						mad->IsInvisible = 1;
						transit->Status.deadtime = 1;
					}
				}
			}
//DeadCode DAW 04Jun99 			else
//DeadCode DAW 04Jun99 			 	transit->LaunchTime=0;							//RJS 29Mar99
		}

		if (transit->LaunchTime>0)	
			GAndFriction(transit,0);	//OrdinaryDrag);		//JIM 24Sep96
	}

	if (transit->LaunchTime<=0)
	{
		MissileAnimData*	adptr = (MissileAnimData*) transit->Anim;
		if (adptr->lastmissile)
		{
			TransientItem*	olditm = (TransientItem*) adptr->lastmissile;

			olditm->isOwned = 0;
			adptr->lastmissile = 0;
			adptr->pad = 7;
		}

		if (transit->Launcher)									//RJS 31Aug00
			ClearWeaponChain((mobileitem*)transit->Launcher,ULong(transit),adptr->wpIndex);//RJS 31Aug00
		else
			INT3;

		AddTransientItemToDeadList(transit);
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobilePuffTravel
//Author		Paul.
//Date			Fri 26 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobilePuffTravel(TransientItemPtr transit,WorldStuff& world)
{
	int timeleft=transit->LaunchTime;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)		//DAW 31Jul96
			transit->LaunchTime=0;

		//move the bullet
		GAndFriction(transit,0);
	}
	else
	{
		SLong	groundheight = GetGroundLevel(transit);
		if (transit->World.Y > groundheight)
		{
			SeenFlak(transit);

			LaunchFlak(transit,transit->shape,world);					//RJS 20Oct00
			AddTransientItemToDeadList(transit);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileBombDrop
//Author		Robert Slater
//Date			Wed 24 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileBombDrop(TransientItemPtr transit,WorldStuff& world)
{
	int timeleft=transit->LaunchTime;

	if (timeleft>0)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)		//DAW 31Jul96
			transit->LaunchTime=0;

		if (transit->TransRandom > timeleft)
		{
			_Miles.PlaySample(FIL_SFX_BOMB_WHISTLE, (ItemBasePtr) transit);//RJS 22Nov96
			transit->TransRandom = 0;
		}

		//Test for collision with the ground, but not every move cycle
		// While frametime is in 50ths							//RJS 21Jul98
		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			bool	isArmed;
			if ((LIFETIME_BOMB-timeleft)>125)					//RJS 15Jun99
				isArmed = true;
			else
				isArmed = false;

			Coords3D hitcoords;
			SLong	groundheight;
			UByte	theArea;									//RJS 28Apr99
			groundheight = GetGroundLevel(transit,theArea);		//RJS 28Apr99

			if (transit->World.Y<=groundheight)					//RJS 10Jun99
			{
				hitcoords = transit->World;
				hitcoords.Y = groundheight + METRES01;

				if (isArmed)									//RJS 10Jun99
					DoImpactGround(transit,hitcoords,theArea);	//MS 30Nov98
				else
					LaunchDustRing(transit,world);				//RJS 11Jun99

				transit->World.Y = hitcoords.Y;
				_Miles.StopSample(FIL_SFX_BOMB_WHISTLE,(ItemBasePtr) transit);

				transit->LaunchTime = 0;

//OldCode RJS 15Dec99 				if ((transit->shape == BOMB29) || (transit->shape == BMB129))//RJS 17Jun99
//OldCode RJS 15Dec99 					LaunchCarpetStrike(transit,world);
			}
//DeadCode RJS 23Dec99 			else
//DeadCode RJS 23Dec99 			{
//DeadCode RJS 23Dec99 				//Bomb is armed after 2secs of falling...
//DeadCode RJS 23Dec99 				if (isArmed)
//DeadCode RJS 23Dec99 				{
//DeadCode RJS 23Dec99 					//Test for collision with other
//DeadCode RJS 23Dec99 					//items
//DeadCode RJS 23Dec99 
//DeadCode RJS 23Dec99 					itemptr	 hititem;
//DeadCode RJS 23Dec99 					int	gindex;										//RJS 10Nov98
//DeadCode RJS 23Dec99 					
//DeadCode RJS 23Dec99 					hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);//RDH 26Nov96
//DeadCode RJS 23Dec99 					if (hititem)									//RJS 17May99
//DeadCode RJS 23Dec99 					{
//DeadCode RJS 23Dec99 						//We've hit the item 'hititem' the impact coordinates
//DeadCode RJS 23Dec99 						//are in 'hitvector'
//DeadCode RJS 23Dec99 
//DeadCode RJS 23Dec99 						_Miles.StopSample(FIL_SFX_BOMB_WHISTLE,(ItemBasePtr) transit);//RJS 06Dec96
//DeadCode RJS 23Dec99 
//DeadCode RJS 23Dec99 //Dead					transit->vely=transit->velx=transit->velz=transit->velhori=0;
//DeadCode RJS 23Dec99 
//DeadCode RJS 23Dec99 						transit->LaunchTime = 0;
//DeadCode RJS 23Dec99 						if (SHAPESTUFF.GetShapeDamageType(transit->shape)==DMT_FIRE)	//RJS 19Feb99
//DeadCode RJS 23Dec99 						{
//DeadCode RJS 23Dec99 							Coords3D	oldcoords = transit->World;
//DeadCode RJS 23Dec99 
//DeadCode RJS 23Dec99 							transit->World = hitcoords;
//DeadCode RJS 23Dec99 							LaunchNapalmImpacted(transit,world);
//DeadCode RJS 23Dec99 							transit->World = oldcoords;
//DeadCode RJS 23Dec99 						}
//DeadCode RJS 23Dec99 //DeadCode RJS 15Dec99 						else
//DeadCode RJS 23Dec99 //DeadCode RJS 15Dec99 						{
//DeadCode RJS 23Dec99 //DeadCode RJS 15Dec99 							if ((transit->shape == BOMB29) || (transit->shape == BMB129))//RJS 17Jun99
//DeadCode RJS 23Dec99 //DeadCode RJS 15Dec99 								LaunchCarpetStrike(transit,world);
//DeadCode RJS 23Dec99 //DeadCode RJS 15Dec99 						}
//DeadCode RJS 23Dec99 					}
//DeadCode RJS 23Dec99 				}
//DeadCode RJS 23Dec99 			}
		}

		//move the bomb
		if (transit->LaunchTime>0)	
		{
			GAndFriction(transit,50);									//RJS 27Jun00

			AddWindDrift(transit);									//RJS 16Dec99
			transit->BombPitch();									//RJS 16Dec99
		}
	}
	else
	{
		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileFuelDrop
//Author		Robert Slater
//Date			Thu 28 May 1998
//
//Description	Fuel tank movecode, with realistic tumble dry spin.
//
//				Starts to whistle at 20 m/s
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileFuelDrop(TransientItemPtr transit,WorldStuff& world)
{
	int timeleft=transit->LaunchTime;
	if (timeleft>0)
	{
		SWord	randmask = transit->TransRandom;
		SWord	nosound = randmask & 1;

		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		randmask >>= 1;

		Angles	angdelta = (Angles)randmask;

		transit->pitch += angdelta;

//DeadCode RJS 07Dec98		GAndFrictionFixedPitch(transit,OrdinaryDrag<<1);		//RJS 27Aug98
		GAndFrictionFixedPitch(transit,0);						//RJS 07Dec98

		//Test for collision with the ground, but not every move cycle
		// While frametime is in 50ths							//RJS 21Aug98
		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			UByte	theArea;
			SLong	groundheight = GetGroundLevel(transit,theArea);//RJS 28Apr99

			if (transit->World.Y <= groundheight)				//RJS 21Aug98
			{
//DeadCode RJS 28Apr99				UByte	theArea = Three_Dee.GetLandType();		//MS 30Nov98

				Coords3D	hitpos = transit->World;			//RJS 10Nov98
				hitpos.Y = groundheight + METRES01;				//RJS 10Nov98
																//RJS 10Nov98
				DoImpactGround(transit,hitpos,theArea);			//MS 30Nov98
																//RJS 10Nov98
				_Miles.StopSample(FIL_SFX_BOMB_WHISTLE,transit);//RJS 10Nov98
																//RJS 10Nov98
				transit->LaunchTime = 0;						//RJS 10Nov98
			}
			else
			{
				if (	(nosound == 1)
					&&	(transit->vel_y < -50000)		) //CSB 09/11/99
				{
					_Miles.PlaySample(FIL_SFX_BOMB_WHISTLE,transit);
					transit->TransRandom = 0 + (randmask << 1);
				}
			}
		}
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileDeadACPart
//Author		Paul.
//Date			Mon 29 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileDeadACPart(TransientItemPtr transit,WorldStuff& worldptr)
{
	int timeleft=transit->LaunchTime;

	if (timeleft>0)
	{
		SWord	frametime;

		frametime = Timer_Code.FRAMETIME;						//DAW 31Jul96

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		//move the deadacpart

		UWord	ltrnd;
		SByte	tmp;
		ANGLES	angdelta;

		ltrnd = transit->TransRandom;

		tmp = (ltrnd & 0x03)<<6;

		ltrnd >>=2;

		angdelta = (Angles)(tmp*frametime);

		transit->roll += angdelta;

		tmp = (ltrnd & 0x03)<<6;

		ltrnd >>=2;

		angdelta = (Angles)(tmp*frametime);

		transit->hdg += angdelta;

		tmp = (ltrnd & 0x03)<<6;

		ltrnd >>=2;

		angdelta = (Angles)(tmp*frametime);

		transit->pitch += angdelta;

		GAndFriction(transit,OrdinaryDrag,OrdinaryDrag);		//RJS 12Aug96

		//Test for collision with the ground, but not every move cycle
		// While frametime is in 50ths							//RJS 21Aug98
		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			UByte	theArea;
			SLong	groundheight = GetGroundLevel(transit,theArea);//RJS 28Apr99
			if (transit->World.Y <= groundheight)
			{
				Coords3D	hitpos = transit->World;			//RJS 10Nov98
				hitpos.Y = groundheight;						//RJS 10Nov98

				DoImpactGround(transit,hitpos,theArea);			//MS 30Nov98
				transit->LaunchTime = 0;
			}
			else
			{
				if (BoxCol::NineSectorColPiloted(transit))		//RJS 17May99
					transit->LaunchTime=0;						//RJS 17May99
			}
		}
	}
	else
	{
		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileSmokeTrail
//Author		Paul.
//Date			Tue 30 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileSmokeTrail(TransientItemPtr transit,WorldStuff& world)
{
//DeadCode RJS 20Oct00 	SLong	timeleft=transit->LaunchTime;
//Deadcode	MoveGunAnimData		*adptr2 = (MoveGunAnimData*) transit->Anim;
	if (transit->Target->Status.size == AirStrucSize)
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(transit->Target->shape);
		if (sdptr->AnimDataSize == AIRCRAFTANIM)					//RJS 29Jun00
		{
			AircraftAnimData	*adptr = (AircraftAnimData*) ((ItemPtr)transit->Target)->Anim;

			if (adptr->hasdust == TRUE)								//RJS 16May99
			{
				transit->World = transit->Target->World;		//RJS 16May99
				transit->uniqueID.changed = TRUE;			//RJS 09Dec98
			}
			else
				AddTransientItemToDeadList(transit);
		}
		else
			AddTransientItemToDeadList(transit);
	}
	else
		AddTransientItemToDeadList(transit);

//DeadCode RJS 24Jun97	if (timeleft && (transit->Target->shape != PDEATH) && (transit->Target->shape != WRECK))//RJS 06Nov96
//DeadCode RJS 24Jun97	{
//DeadCode RJS 24Jun97		SWord	frametime;
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		frametime = Timer_Code.FRAMETIME;						//DAW 31Jul96
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		if ((transit->LaunchTime-=frametime)<0)
//DeadCode RJS 24Jun97			transit->LaunchTime=0;
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		//Follow the target
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		transit->World.X = transit->Target->World.X;
//DeadCode RJS 24Jun97		transit->World.Y = transit->Target->World.Y;
//DeadCode RJS 24Jun97		transit->World.Z = transit->Target->World.Z;
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		//Launch a piece of smoke if it's
//DeadCode RJS 24Jun97		//the right time
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		SWord launchtime = (SWord )transit->TransRandom;
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		launchtime-=frametime;
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		if (launchtime<=0)
//DeadCode RJS 24Jun97		{
//DeadCode RJS 24Jun97			//Time to launch some smoke
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97			TransientItem*	newitem;
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97			newitem = LaunchUnguidedMissile(	transit,
//DeadCode RJS 24Jun97												SmokinShape,
//DeadCode RJS 24Jun97												LIFETIME_SMOKE,MOBILE_GANDF);//RJS 29Oct96
//DeadCode RJS 24Jun97			if (newitem)
//DeadCode RJS 24Jun97			{
//DeadCode RJS 24Jun97				newitem->TransRandom = 0;
//DeadCode RJS 24Jun97				newitem->World.X += (Math_Lib.rnd(40) - 20);
//DeadCode RJS 24Jun97				newitem->World.Y += (Math_Lib.rnd(40) - 20);
//DeadCode RJS 24Jun97				newitem->velhori = 0;							//RJS 29Oct96
//DeadCode RJS 24Jun97				newitem->vely = 0;								//RJS 29Oct96
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97				AddTransientItemToWorld(newitem,world);
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97				ExplodeAnimData* adptr;									//PD 08May96
//DeadCode RJS 24Jun97				adptr = (ExplodeAnimData* )newitem->Anim;			//RJS 31Jul96
//DeadCode RJS 24Jun97				adptr->frameno = 0;									//RJS 05Jul96
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97				if (Math_Lib.rnd() <16*1024-TransientItem::transcount*10)
//DeadCode RJS 24Jun97				{
//DeadCode RJS 24Jun97					newitem = LaunchUnguidedMissile(transit,SPARK,
//DeadCode RJS 24Jun97												LIFETIME_SMOKE,MOBILE_RICOCHET);
//DeadCode RJS 24Jun97					
//DeadCode RJS 24Jun97					if (newitem)
//DeadCode RJS 24Jun97					{
//DeadCode RJS 24Jun97						newitem->hdg += (ANGLES) (ANGLES_180Deg - Math_Lib.rnd(ANGLES_45Deg) + ANGLES_20Deg);
//DeadCode RJS 24Jun97						newitem->velhori = 200 + Math_Lib.rnd(200);
//DeadCode RJS 24Jun97						newitem->vely = Math_Lib.rnd(100) - 50;
//DeadCode RJS 24Jun97						AddTransientItemToWorld(newitem,world);
//DeadCode RJS 24Jun97					}
//DeadCode RJS 24Jun97				}
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97			}
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97 //DeadCode RJS 08Jul96			launchtime = SmokeLaunchDelay;
//DeadCode RJS 24Jun97 //DeadCode RJS 31Jul96			launchtime = 12;
//DeadCode RJS 24Jun97			launchtime = (launchtime+3)&3;
//DeadCode RJS 24Jun97			launchtime+=(TransientItem::transcount>>4);	//every 16=1cs	//48=3cs
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		}
//DeadCode RJS 24Jun97		transit->TransRandom = (UWord )launchtime;
//DeadCode RJS 24Jun97	}
//DeadCode RJS 24Jun97	else
//DeadCode RJS 24Jun97	{
//DeadCode RJS 24Jun97		//Kill the launcher here
//DeadCode RJS 24Jun97		
//DeadCode RJS 24Jun97 //DeadCode RJS 12Aug96		KillLauncher(transit->Launcher,world);
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		AddTransientItemToDeadList(transit);
//DeadCode RJS 24Jun97	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileGAndF
//Author		Paul.
//Date			Tue 30 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileGAndF(TransientItemPtr transit,WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)		//DAW 31Jul96
			transit->LaunchTime=0;

//		GAndFriction(transit,OrdinaryDrag);
		GAndFriction(transit,100);
		if (transit->TransRandom == 1)
			transit->pitch = ANGLES_0Deg;

		// While frametime is in 50ths
		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			SLong	groundheight = GetGroundLevel(transit);		//RJS 14Apr99
			if (transit->World.Y <= groundheight)			//RJS 10Dec98
				AddTransientItemToDeadList(transit);		//RJS 10Dec98
		}
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileGroundExp
//Author		Paul.
//Date			Wed 1 May 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileGroundExp(TransientItemPtr transit,WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		_Miles.PlayLooped(FIL_SFX_SMALL_FIRE_LOOP, (ItemBasePtr) transit);//RJS 22Nov96

		SWord	frametime;

		frametime = Timer_Code.FRAMETIME;						//DAW 31Jul96

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		//Launch a piece of smoke if it's
		//the right time

//		SWord launchtime = (SWord )transit->TransRandom;
//
//		launchtime-=frametime;
//
//		if (launchtime<=0)
//		{
//			//Time to launch some smoke
//
//			TransientItem*	newitem;
//
//			newitem = SimplifiedSpriteLaunch(	transit,
//												BigSmokeShape,	//PD 09May96
//												LIFETIME_SMOKE,MOBILE_STATIONARY);//RJS 20Apr98
//			if (newitem)
//			{
//				//Give the smoke particle some vertical velocity
//
//				UWord	randomfactor;
//				SLong	vvel;
//
//				randomfactor = Math_Lib.rnd();
//
//				newitem->vely = SmokeBaseVel + ((randomfactor * SmokeVariableVertVel * 2)>>16);
//				newitem->pitch= ANGLES_90Deg;
//
//				newitem->World.Y += 500;						//RJS 18Sep96
//
//				newitem->hdg = (Angles)(Math_Lib.rnd());
//
//				SWord	sin_ang,cos_ang;
//
////DeadCode RJS 07Feb97				Math_Lib.high_sin_cos((ANGLES )newitem->hdg,sin_ang,cos_ang);
//
//				randomfactor = Math_Lib.rnd();
//
//				newitem->velhori = ((randomfactor * SmokeVariableHorzVel)>>16);

//DeadCode RJS 07Feb97				newitem->velx = (newitem->velhori * sin_ang)/ANGLES_FRACT;
//DeadCode RJS 07Feb97
//DeadCode RJS 07Feb97				newitem->velz = (newitem->velhori * cos_ang)/ANGLES_FRACT;
//
//				AddTransientItemToWorld(newitem,world);
//			}

//DeadCode RJS 11Jul97			//Drive the shape animation								//PD 08May96
//DeadCode RJS 11Jul97
//DeadCode RJS 11Jul97			ExplodeAnimData* adptr;									//PD 08May96
//DeadCode RJS 11Jul97
//DeadCode RJS 11Jul97			adptr = (ExplodeAnimData* )transit->Anim;				//PD 08May96
//DeadCode RJS 11Jul97
//DeadCode RJS 11Jul97			adptr->frameno++;										//PD 08May96
//DeadCode RJS 11Jul97
//DeadCode RJS 11Jul97			if (adptr->frameno>3)									//PD 08May96
//DeadCode RJS 11Jul97				adptr->frameno = 0;									//PD 08May96
//
//			launchtime = SmokeLaunchDelay+((3*TransientItem::transcount)>>4);
//		}
//		transit->TransRandom = (UWord )launchtime;
	}
	else
	{
		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileMovingSmoke
//Author		Robert Slater
//Date			Mon 2 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileMovingSmoke(TransientItemPtr transit,WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;

//DeadCode RJS 16Sep98	if (timeleft && (transit->Launcher->shape != EMPTY))		//RDH 17Dec96
//DeadCode RJS 16Sep98	{
//DeadCode RJS 16Sep98		_Miles.PlayLooped(FIL_SFX_FIREBURN_LOOP, (ItemBasePtr) transit);//RJS 22Nov96
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98		SWord	frametime;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98		frametime = Timer_Code.FRAMETIME;						//DAW 31Jul96
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98		if ((transit->LaunchTime-=frametime)<0)
//DeadCode RJS 16Sep98			transit->LaunchTime=0;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98		//Launch a piece of smoke if it's
//DeadCode RJS 16Sep98		//the right time
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98		SWord launchtime = (SWord )transit->TransRandom;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98		launchtime-=frametime;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98		if (launchtime<=0)
//DeadCode RJS 16Sep98		{
//DeadCode RJS 16Sep98			//Time to launch some smoke
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98			TransientItem*	newitem;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98			newitem = SimplifiedSpriteLaunch(	transit,
//DeadCode RJS 16Sep98												BigSmokeShape,	//PD 09May96
//DeadCode RJS 16Sep98												LIFETIME_SMOKE,MOBILE_GANDF);
//DeadCode RJS 16Sep98			if (newitem)
//DeadCode RJS 16Sep98			{
//DeadCode RJS 16Sep98				UWord	randomfactor;
//DeadCode RJS 16Sep98				SLong	vvel;
//DeadCode RJS 16Sep98				newitem->TransRandom = 0;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98 //DeadCode RJS 19Feb98				ExplodeAnimData* adptr;									//PD 08May96
//DeadCode RJS 16Sep98 //DeadCode RJS 19Feb98				adptr = (ExplodeAnimData* )newitem->Anim;			//RJS 31Jul96
//DeadCode RJS 16Sep98 //DeadCode RJS 19Feb98				adptr->frameno = 0;	
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				newitem->World.X = transit->Launcher->World.X;
//DeadCode RJS 16Sep98				newitem->World.Y = transit->Launcher->World.Y + 50;
//DeadCode RJS 16Sep98				newitem->World.Z = transit->Launcher->World.Z;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				randomfactor = Math_Lib.rnd();
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				newitem->vely = SmokeBaseVel + ((randomfactor * SmokeVariableVertVel)>>16);//RJS 02Sep96
//DeadCode RJS 16Sep98				newitem->pitch= ANGLES_90Deg;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				newitem->hdg = (Angles)(Math_Lib.rnd());
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				SWord	sin_ang,cos_ang;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				Math_Lib.high_sin_cos((ANGLES )newitem->hdg,sin_ang,cos_ang);
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				randomfactor = Math_Lib.rnd();
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				newitem->velhori = ((randomfactor * SmokeVariableHorzVel)>>16);
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				newitem->velx = (newitem->velhori * sin_ang)/ANGLES_FRACT;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				newitem->velz = (newitem->velhori * cos_ang)/ANGLES_FRACT;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				AddTransientItemToWorld(newitem,world);
//DeadCode RJS 16Sep98			}
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98			launchtime = SmokeLaunchDelay;
//DeadCode RJS 16Sep98		}
//DeadCode RJS 16Sep98		transit->TransRandom = (UWord )launchtime+(TransientItem::transcount>>4);
//DeadCode RJS 16Sep98	}
//DeadCode RJS 16Sep98	else
//DeadCode RJS 16Sep98	{
//DeadCode RJS 16Sep98		AddTransientItemToDeadList(transit);
//DeadCode RJS 16Sep98	}

	if (timeleft)
	{
		SWord	frametime = Timer_Code.FRAMETIME;
		SLong	testvel;
		UWord	deadshape = UWord(transit->pitch);

		if ((transit->LaunchTime-=frametime)<0)		//DAW 31Jul96
			transit->LaunchTime=0;

		// Use half the amount of gravitational effect...
		// ... and keep floating...
		if ((transit->LaunchTime & 6)==0)
		{
//			if (transit->vely > (frametime<<2))
//				transit->vely -= (frametime>>1);

			UWord	thistime = UWord(transit->roll);
			if (thistime)
			{
				UWord	timepassed = thistime - timeleft;
				if (timepassed > transit->TransRandom)
				{
					if (deadshape)
					{
						TransientItem*	newitem;
						newitem = LaunchUnguidedMissile(transit,
														(ShapeNum)deadshape,
														800,
														MOBILE_MOVSMK);

						if (newitem)
						{
							newitem->roll = (Angles) 0;
							newitem->pitch = (Angles) 0;
							AddTransientItemToWorld(newitem, world);
						}
					}

					transit->LaunchTime = 0;
				}
			}
			else
			{
//DEADCODE CSB 09/11/99 				if (transit->vely > (frametime<<2))
//DEADCODE CSB 09/11/99 					transit->vely -= (frametime>>1);
				if (transit->vel_y / 1000 > (frametime<<2))	//CSB 09/11/99
					transit->vel_y -= ((frametime*1000)>>1); //CSB 09/11/99
//DIRTY FIX !!!  Not sure what these two lines are supposed to do! //CSB 09/11/99
			}
		}

		if (deadshape == 0)
		{
			// Drag is 1
			Float	dfrac = Float(frametime) * 0.000244140625;
			Float	dvel = Float(transit->vel_);
			Float	dvelx = Float(transit->vel_x);
			Float	dvelz = Float(transit->vel_z);

			dvel *= dfrac;
			dvelx *= dfrac;
			dvelz *= dfrac;
			
			transit->vel_ -= dvel;
			transit->vel_x -= dvelx;
			transit->vel_z -= dvelz;
//DEADCODE CSB 09/11/99 			testvel = (transit->velhori * frametime)>>12;
//DEADCODE CSB 09/11/99 			transit->velhori -= testvel;

//DIRTY FIX !!!  DRAG REMOVED ????? //CSB 09/11/99
		}
		else
		{
/*			if (transit->velhori > 20)
			{
				testvel = (transit->velhori * frametime)>>12;
				transit->velhori -= testvel;
			}*/
		}

		// ApplyVelocities, without pitch nobble
		transit->World.Y += (transit->vel_y * frametime)/10000; //CSB 09/11/99

//DEADCODE CSB 09/11/99 		SLong	temp = (frametime * transit->velhori)/10;
//DEADCODE CSB 09/11/99 		SWord	sin_ang,cos_ang;
//DEADCODE CSB 09/11/99 		Math_Lib.high_sin_cos(transit->hdg,sin_ang,cos_ang);
//DEADCODE CSB 09/11/99 		transit->World.X += (temp*sin_ang)/ANGLES_FRACT;
//DEADCODE CSB 09/11/99 		transit->World.Z += (temp*cos_ang)/ANGLES_FRACT;
		transit->World.X += (transit->vel_x * frametime) / 10000; //CSB 09/11/99
		transit->World.Z += (transit->vel_z * frametime) / 10000; //CSB 09/11/99

		transit->uniqueID.changed = TRUE;
		// ApplyVelocities, without pitch nobble

		AddWindDrift(transit);
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileExplosion
//Author		Paul.
//Date			Wed 1 May 1996
//
//Description	Actually burns whatever it is over
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileExplosion(TransientItemPtr transit,WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		if ((timeleft & 0x04)==0)								//RJS 23Dec99
		{
			_Miles.PlayLooped(FIL_SFX_NAPALM_SIZZLE,transit);
			if (!transit->Status.deadtime)						//RJS 19Feb99
			{
				itemptr		hititem;
				Coords3D	hitcoords;
				int			gindex;

				hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);
				if (hititem)
					LaunchSmallThug(transit,hititem,NapalmThugShape,gindex,timeleft*2);
			}
		}

		UWord	smkdelay = transit->TransRandom >> 8;
		UWord	tottime = transit->TransRandom & 0xFF;
		SWord	smoketime = smkdelay;
		smoketime -= Timer_Code.FRAMETIME;
		if ((smoketime < 0) && tottime)
		{
			SLong	tdist = tottime - timeleft;					//DAW 07Apr99
			if (transit->Status.Drawn)							//DAW 07Apr99
			{
				ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(transit->shape);
				SLong	width,length;
				SLong	area;
				SLong	i,nosmoke;
				SLong	maxx, maxz,minx,minz;
				SWord	sin_ang,cos_ang;
				SLong	xoff,zoff,xoff2,zoff2;
				SLong	currlength,currwidth,rlength,rwidth;
				SLong	clength,cwidth;
				ShapeNum	theShape;							//DAW 07Apr99
				SLong		theMovement;						//DAW 07Apr99

//DeadCode RJS 15Dec99 				if ((timeleft & 0x04)==0)	//RJS 23Dec99
//DeadCode RJS 15Dec99 				{
					theShape = FireballShape;		//distant napalm smoke
					theMovement = MOBILE_MOVSMK;
//DeadCode RJS 15Dec99 				}
//DeadCode RJS 15Dec99 				else
//DeadCode RJS 15Dec99 				{
//DeadCode RJS 15Dec99 					theShape = DSTNAP;		//near napalm smoke
//DeadCode RJS 15Dec99 					theMovement = MOBILE_STATIONARY;
//DeadCode RJS 15Dec99 				}

				width = sdptr->sx<<5;
				length = sdptr->sz<<5;

				// travel the length of the napalm...
				length = (tdist*length) / tottime;
				width = (tdist*width) / tottime;

				clength = length >> 1;
				cwidth = width >> 1;

				TransientItemPtr	newitem;
				newitem = SimplifiedSpriteLaunch(	transit,
													theShape,	//DAW 07Apr99
													550,
													(AutoMoveCodeTypeSelect)theMovement);//DAW 07Apr99

				if (newitem)
				{
//DEADCODE CSB 09/11/99 					newitem->velhori = 0;
					newitem->vel_y = 50000; //CSB 09/11/99
					newitem->World.X += Math_Lib.rnd(width) - cwidth;
					newitem->World.Z += Math_Lib.rnd(length) - clength;
					newitem->World.Y = GetGroundLevel(newitem) + 250;//RJS 14Apr99
					newitem->roll = (Angles) 0;
					newitem->pitch = (Angles) 0;
					AddTransientItemToWorld(newitem, world);
				}
			}

			transit->TransRandom = 0;
			smoketime = 40 - ((40 * tdist) / tottime);
		}

		transit->TransRandom = UWord(smoketime);
		transit->TransRandom <<= 8;
		transit->TransRandom |= tottime;
	}
	else
	{
		TransientItem*	newitem;
		if (WithinVisibleRange(transit->World,300000))				//RJS 30Apr99
		{
			SWord			lifetime = transit->pitch;
			SLong			scatterno,size1;
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(transit->shape);
			ShapeDescPtr	sdptr2 = SHAPESTUFF.GetShapePtr(SmallFireShape);
			SLong			size2 = (sdptr2->sx<<4) * (sdptr2->sz<<4);
//Dead			TransientItem*	newitem;
			SLong			wx,wz;
			SLong			sizex,sizez;
			SLong			sizex2,sizez2;
			SLong			i;

			size1 = (sdptr->sx<<4) * (sdptr->sz<<4);
			scatterno = size1 / size2;
			scatterno = (lifetime * scatterno)/240;

			sizex = sdptr->sx<<4;
			sizez = sdptr->sz<<4;

			sizex2 = (lifetime * sizex) / 240;
			sizez2 = (lifetime * sizez) / 240;

			sizex = sizex2 >> 1;
			sizez = sizez2 >> 1;

			scatterno = (scatterno>>1) + Math_Lib.rnd(scatterno>>1);

			for (i = 0; i < 3; i++)							//RJS 05May99
			{
				newitem = SimplifiedSpriteLaunch(	transit,
													LargeScatFireShape,//DAW 11May99
													1500,
													MOBILE_STATIONARY);//RJS 20Apr98
				if (newitem)
				{
					wx = (sizex*Math_Lib.rnd()) - sizex2;
					wz = (sizez*Math_Lib.rnd()) - sizez2;

					newitem->World.X += wx;
					newitem->World.Z += wz;
					newitem->World.Y = GetGroundLevel(newitem);		//RJS 14Apr99

					AddTransientItemToWorld(newitem, world);
				}
			}
		}

		// Launch scorch mark...
		if (!transit->Status.deadtime && transit->Target)			//RJS 11May99
		{
			//Only really want to add 1...
			newitem = SimplifiedSpriteLaunch(	transit,
												SCORCH,
												6000,
												MOBILE_STATIONARY);
			if (newitem)
			{
				newitem->hdg = transit->hdg;
				newitem->pitch = transit->pitch;
				newitem->roll = transit->roll;

				AddTransientItemToWorld(newitem, world);
			}
		}

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileTimerExplosion
//Author		Robert Slater
//Date			Thu 22 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileTimerExplosion(TransientItemPtr transit,WorldStuff& worldptr)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;
	}
	else
	{
		LaunchMiniExplosion(transit,worldptr);

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileFlare
//Author		Robert Slater
//Date			23Dec99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileFlare(TransientItemPtr transit,WorldStuff& worldptr)
{
	int timeleft=transit->LaunchTime;
	if (timeleft>0)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		//Test for collision with the ground, but not every move cycle
		// While frametime is in 50ths
		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			Coords3D hitcoords;
			SLong	groundheight;
			UByte	theArea;

			groundheight = GetGroundLevel(transit,theArea);

			if (transit->World.Y<=groundheight)
			{
				transit->World.Y = groundheight;
				transit->LaunchTime = 0;

				SLandLight lightDef;
				lightDef.pos=transit->World;
				lightDef.color.r=0xFF00;
				lightDef.color.g=0xFF00;
				lightDef.color.b=0xFF00;
				lightDef.timer=50;	//half a second
				lightDef.range=25000;	//quarter km

//deadcode JON 19/06/01					Land_Scape.AddLight(&lightDef);
				LaunchSmallFlash(transit,worldptr);
				LaunchSmoulder(transit,worldptr);
			}
		}

		//move the bomb
		if (transit->LaunchTime>0)	
			GAndFriction(transit,0);
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileGroundDebris
//Author		Robert Slater
//Date			Fri 21 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileGroundDebris(TransientItemPtr transit, WorldStuff& worldptr)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		if (transit->shape == PLUME2)
		{
			SLong	oldvy = transit->vel_y;

			GAndFriction(transit,OrdinaryDrag);

			if ((transit->vel_y <= 0) && (oldvy > 0))
//DEADCODE CSB 09/11/99 				transit->velhori /= 2;
			{							//CSB 09/11/99
				transit->vel_x /= 2;	//CSB 09/11/99
				transit->vel_z /= 2;	//CSB 09/11/99
			}							//CSB 09/11/99
		}
		else
			GAndFriction(transit,OrdinaryDrag);

		//Test for collision with the ground
		if ((timeleft & 0x04)==0)								//RJS 23Dec99
		{
			SLong	groundheight = GetGroundLevel(transit);		//RJS 14Apr99

			if (transit->World.Y < groundheight)
			{
				transit->World.Y = groundheight;
				if (transit->shape == NapalmFingerShape)				//RJS 09Dec98
					LaunchGuidedBurning(transit,worldptr);
				else
				{
					if (transit->shape != BoxShape)
						_Miles.PlaySample(FileNum(FIL_SFX_DEBRIS_SHOWER1+Math_Lib.rnd(4)), (ItemBasePtr) transit);	//RJS 14Jun00
					else
						_Miles.PlaySample(FileNum(FIL_SFX_DEBRIS_THUD1+Math_Lib.rnd(4)), (ItemBasePtr) transit);//RJS 05Dec96
				}

				AddTransientItemToDeadList(transit);
			}
			else
			{
				UWord	transpants = SWord(transit->TransRandom);
				if (transpants)
				{
					SByte	pitchover = transpants & 0xFF;
					SByte	rollover = (transpants & 0xFF00)>>8;

					// Max spin is roughly 11 degrees/frame
					transit->roll += (Angles)(rollover<<4);
					transit->pitch += (Angles)(pitchover<<4);
				}
				else
				{
// Pitch down normally...
					float	vx = transit->vel_x;						//RJS 31May00
					float	vz = transit->vel_z;
					SLong	vh;
					
					fastMath.FloatToInt(&vh,fastMath.FastSqrt(vx*vx+vz*vz));

					transit->pitch = Math_Lib.arctan(transit->vel_y, vh);
				}
			}
		}
	}
	else
	{
		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileFire
//Author		Robert Slater
//Date			Mon 1 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileFire(TransientItemPtr transit, WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		_Miles.PlayLooped(FIL_SFX_SMALL_FIRE_LOOP, (ItemBasePtr) transit,96);//RJS 10Aug00

		SWord	frametime;
		frametime = Timer_Code.FRAMETIME;		

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		SWord launchtime = (SWord )transit->TransRandom;
		launchtime-=frametime;

		if (transit->Target)
		{
			transit->World.X = transit->Target->World.X + SWord(transit->hdg);
			transit->World.Y = transit->Target->World.Y + SWord(transit->pitch);
			transit->World.Z = transit->Target->World.Z + SWord(transit->roll);
			transit->uniqueID.changed = TRUE;			//RJS 09Dec98
		}

/*		if (launchtime<=0)
		{
			TransientItem*	newitem;

			newitem = SimplifiedSpriteLaunch(	transit,
												SmokinShape,
												LIFETIME_SMOKE,MOBILE_STATIONARY);//RJS 20Apr98
			if (newitem)
			{
				//Give the smoke particle some vertical velocity

				UWord	randomfactor;
				SLong	vvel;

				randomfactor = Math_Lib.rnd();

				newitem->vely = SmokeBaseVel + ((randomfactor * SmokeVariableVertVel * 2)>>16);
				newitem->pitch= ANGLES_90Deg;

				newitem->World.Y += 500;						//RJS 18Sep96

				newitem->hdg = (Angles)(Math_Lib.rnd());

				SWord	sin_ang,cos_ang;

				Math_Lib.high_sin_cos((ANGLES )newitem->hdg,sin_ang,cos_ang);

				randomfactor = Math_Lib.rnd();

				newitem->velhori = ((randomfactor * SmokeVariableHorzVel)>>16);

				AddTransientItemToWorld(newitem,world);
			}

			//Drive the shape animation								//PD 08May96

//DeadCode RJS 19Feb98			ExplodeAnimData* adptr;									//PD 08May96
//DeadCode RJS 19Feb98
//DeadCode RJS 19Feb98			adptr = (ExplodeAnimData* )transit->Anim;				//PD 08May96
//DeadCode RJS 19Feb98			adptr->frameno++;										//PD 08May96
//DeadCode RJS 19Feb98
//DeadCode RJS 19Feb98			if (adptr->frameno>7)									//PD 08May96
//DeadCode RJS 19Feb98				adptr->frameno = 0;									//PD 08May96

			launchtime = SmokeLaunchDelay+(TransientItem::transcount>>4);
		}
		transit->TransRandom = (UWord )launchtime;*/
	}
	else
	{
		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileTroop
//Author		Robert Slater
//Date			Mon 1 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileTroop(TransientItemPtr transit, WorldStuff&)
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		if (transit->Target)
		{
			MinAnimData*	mad = (MinAnimData*)((ItemPtr)transit->Target)->Anim;
			mad->IsInvisible = 1;

			transit->Target = NULL;
		}

		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		MoveBlokeWithBrain(transit,transit->TransRandom);
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileParachute
//Author		Robert Slater
//Date			Tue 2 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileParachute(TransientItemPtr transit, WorldStuff&	world)
{
	SLong			timeleft = transit->LaunchTime;
	SLong			timedist;
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(transit->shape);
	UWord			chutePhase = transit->TransRandom & PARACHUTE_PHASE_MASK;	//RJS 22Sep00
	UWord			chuteStatus = transit->TransRandom >> PARACHUTE_SHIFT;	//RJS 22Sep00

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		//must be the chute...
//DeadCode JIM 28Jun00 		if (!transit->isOwned)
		if (sdptr->AnimDataSize != TROOPANIM)
		{
			TransientItemPtr	transitmaster = (TransientItemPtr) transit->Target;
			if (transitmaster)
			{
				transit->hdg = transitmaster->hdg;
				
				//This is definitely the chute...
				UWord	randno = transitmaster->TransRandom & PARACHUTE_PHASE_MASK;
				if (randno == PARACHUTE_PHASE_5)
				{
					if (chutePhase == PARACHUTE_PHASE_2)
					{
						SHAPE.ResetAnimData_NewShape(transit,CHUTE2);	//This should also reset the morph time...
						transit->TransRandom = (transit->TransRandom & PARACHUTE_MASK) + PARACHUTE_PHASE_4;
						transit->LaunchTime = 300;		//give chute 3 secs to collapse
						transit->World = transitmaster->World;
						transit->uniqueID.changed = TRUE;
						transit->Target = NULL;
						transit->vel_ = transit->vel_x = transit->vel_y = transit->vel_z = 0;

//we don't want it put in the binary tree twice!
						transitmaster->Target = NULL;
					}
				}
			}
			else
			{
				if (chutePhase == PARACHUTE_PHASE_3)
				{
					GAndFriction(transit,5000);
					_Miles.PlayLooped(FIL_SFX_PARACHUTE_LOOP,transit,96);//RJS 10Aug00
				}
			}
		}
		else
		{
			UByte	theArea;
			SLong	groundheight = GetGroundLevel(transit,theArea);

			if (chutePhase != PARACHUTE_PHASE_5)
			{
//DeadCode RJS 11Aug00 				UByte	theArea;
//DeadCode RJS 11Aug00 				SLong	groundheight = GetGroundLevel(transit,theArea);

				if (chutePhase > PARACHUTE_PHASE_3)
				{
					SWord	thepitch = transit->pitch;
					SWord	theroll = transit->roll;
					SWord	reqPitch = -ANGLES_90Deg;
					SWord	reqRoll = ANGLES_0Deg;
					UWord	doneCount = 0;
					SLong	delta;
					ULong	deltaSquare;


					GAndFriction(transit,OrdinaryDrag);

					delta = thepitch - reqPitch;
					deltaSquare = ULong(delta * delta);

					if (deltaSquare < (256*256))
					{
						thepitch = reqPitch;
						doneCount++;
					}
					else
					{
						if (thepitch > reqPitch)
							transit->pitch -= Angles(256);
						else
							transit->pitch += Angles(256);
					}

					delta = theroll - reqRoll;
					deltaSquare = ULong(delta * delta);

					if (deltaSquare < (256*256))
					{
						theroll = reqRoll;
						doneCount++;
					}
					else
					{
						if (theroll > reqRoll)
							transit->roll -= Angles(256);
						else
							transit->roll += Angles(256);
					}

					if ((transit->vel_y < -200000) && (doneCount==2))	//RJS 27Sep00
					{
						if (((AirStrucPtr)transit->Launcher)->AcIsPlayer())	//RJS 18Sep00
							View_Object->Quit3D(2000);					//RJS 18Sep00

						if ((transit->World.Y - groundheight) > FT_200)	//RJS 7Sep00
						{
							Anim_Control.SetPlayerAnim(transit,ANIMATION_PULL_CHUTE);

							transit->roll = ANGLES_0Deg;
							transit->TransRandom = (transit->TransRandom & PARACHUTE_MASK) + PARACHUTE_PHASE_3;
						}
						else
						{
// ejected too low!
							if (	(transit->Launcher->Status.size == AIRSTRUCSIZE)	//RJS 22Sep00
								&&	((chuteStatus & PARACHUTE_DEAD)==0)	)	//RJS 22Sep00
								AirStrucPtr(transit->Launcher)->ai.diaryptr->KillPilot();

							_Miles.PlayOnce(FIL_SFX_VOX_FAILED_CHUTE,transit);

							Anim_Control.SetPlayerAnim(transit,ANIMATION_AARGH);

							transit->Target = NULL;
							transit->TransRandom = (transit->TransRandom & PARACHUTE_MASK) + PARACHUTE_PHASE_2;
						}
					}
					else
					{
						if ((transit->World.Y - groundheight) < FT_200)	//RJS 18Sep00
						{
							if (((AirStrucPtr)transit->Launcher)->AcIsPlayer())	//RJS 18Sep00
								View_Object->Quit3D(2000);					//RJS 18Sep00
// ejected too low!
							if (	(transit->Launcher->Status.size == AIRSTRUCSIZE)	//RJS 22Sep00
								&&	((chuteStatus & PARACHUTE_DEAD)==0)	)	//RJS 22Sep00
								AirStrucPtr(transit->Launcher)->ai.diaryptr->KillPilot();

							_Miles.PlayOnce(FIL_SFX_VOX_FAILED_CHUTE,transit);

							Anim_Control.SetPlayerAnim(transit,ANIMATION_AARGH);

							transit->Target = NULL;
							transit->TransRandom = (transit->TransRandom & PARACHUTE_MASK) + PARACHUTE_PHASE_2;
						}
					}
				}
				else
				{
					if (chutePhase==PARACHUTE_PHASE_2)
					{
						if (transit->Target)
						{
							GAndFriction(transit,2000);

							SWord	pitchDelta = SWord(transit->pitch) / 10;

							transit->pitch -= Angles(pitchDelta);

							_Miles.PlayLooped(FIL_SFX_PARACHUTE_LOOP,transit,96);
						}
						else
						{
							GAndFriction(transit,OrdinaryDrag);

							transit->pitch += ANGLES_5Deg;
							transit->roll += ANGLES_1Deg;
						}
					}
					else
					{
						GAndFriction(transit,OrdinaryDrag);
						if (Anim_Control.Finished(transit,ANIMATION_PULL_CHUTE))
						{
							TroopAnimData*	adptr = (TroopAnimData*)transit->Anim;
							TransientItem*	newitem;

							if (chuteStatus & PARACHUTE_CHUTE_OPEN)		//RJS 22Sep00
							{
								_Miles.PlayOnce(FIL_SFX_PARACHUTE_OPEN,transit,64);

								//Launch the chute...
								newitem = LaunchGuidedMissile(	transit,
																transit,
																PCHUT1,
																transit->LaunchTime,
																MOBILE_PARACHUTE	);
								if (newitem)
								{
									//Place in binary tree seperately!
									MinAnimData*	mad = (MinAnimData*)newitem->Anim;
									mad->IsInvisible = 1;

									//allow both chute and bloke to point to each other...
									transit->Target = newitem;
									transit->isOwned = 1;
									adptr->goodchute = 1;
									adptr->haschute = 1;

									newitem->TransRandom = PARACHUTE_PHASE_2;
									newitem->pitch = ANGLES_0Deg;//RJS 01Jun00
									newitem->roll = ANGLES_0Deg;//RJS 01Jun00
									newitem->isOwned = 1;				//JIM 28Jun00

								//	transit->pitch = ANGLES_0Deg;		//RJS 3Jul00

									AddTransientItemToWorld(newitem, world);
								}
							}
							else
							{
								// Failed chute!!!
								if (chuteStatus & PARACHUTE_CHUTE_ESCAPED)
								{
									_Miles.PlayOnce(FIL_SFX_VOX_FAILED_CHUTE,transit);	//RJS 25Oct00

									// Chute opened, but buggered...
									newitem = LaunchUnguidedMissile(transit,
																	PCHUT1,
																	1000,
																	MOBILE_PARACHUTE);
									if (newitem)
									{
										newitem->TransRandom = PARACHUTE_PHASE_3;
										newitem->pitch = ANGLES_0Deg;//RJS 01Jun00
										newitem->roll = ANGLES_0Deg;//RJS 01Jun00

										AddTransientItemToWorld(newitem, world);
									}
								}
								else
								{
									// Chute didn't open at all...
									_Miles.PlayOnce(FIL_SFX_VOX_FAILED_CHUTE,transit);
								}
							}

							transit->TransRandom = (transit->TransRandom & PARACHUTE_MASK) + PARACHUTE_PHASE_2;
							if (transit->Target)
								Anim_Control.SetPlayerAnim(transit,ANIMATION_GOOD_CHUTE);
							else
								Anim_Control.SetPlayerAnim(transit,ANIMATION_AARGH);//RJS 22Dec99
						}
					}
				}

				AddWindDrift(transit);						

				if (transit->World.Y <= groundheight)
				{
					UWord	randpoo = Math_Lib.rnd();

					transit->World.Y = groundheight;

					if (transit->Target)			//does it have chute?
					{
						_Miles.StopSample(FIL_SFX_PARACHUTE_LOOP,transit);

						Anim_Control.SetPlayerAnim(transit,ANIMATION_LAND_GOOD);//RJS 22Dec99
						_Miles.PlayOnce(FileNum(FIL_SFX_PARACHUTE_OOF1 + (randpoo>>15)),transit);	//RJS 8Nov00
					}
					else
					{
						_Miles.StopSample(FIL_SFX_VOX_FAILED_CHUTE,transit);	//RJS 25Oct00

						Anim_Control.SetPlayerAnim(transit,ANIMATION_LAND_SPLAT);//RJS 22Dec99
						_Miles.PlayOnce(FIL_SFX_YELP5,transit);

						// 1 in 8 chance we'll get real landing ori...
						if (randpoo > 8192)
				 			Three_Dee.pMigLand->GetShadowAngles(transit->World,transit->hdg,transit->pitch,transit->roll);
					}

					SLong	aliveTime = 500;							//RJS 9Oct00
					if ( IsWater( theArea ) )					//RJS 01Jun00
					{
						if (transit->Target && WithinVisibleRange(transit->World,1000000))//RJS 18Sep00
						{
							LaunchDingyChap(transit,world);
							aliveTime = 0;								//RJS 11Aug00
						}

						_Miles.PlayOnce(FIL_SFX_RICOCHET_WATER1,transit);
						LaunchSplashSmall((mobileitem*)transit,world);
					} else {
						_Miles.PlayOnce(FIL_SFX_PARACHUTE_LAND_GROUND,transit);
						LaunchDustRing(transit,world);
					}

					transit->LaunchTime = aliveTime;
					transit->vel_ = transit->vel_x = transit->vel_y = transit->vel_z = 0;
	
					transit->TransRandom = (transit->TransRandom & PARACHUTE_MASK) + PARACHUTE_PHASE_5;
				}
			}
			else
			{
				if ( IsWater( theArea ) )
					transit->World.Y -= Timer_Code.FRAMETIME;
			}
		}
	}
	else
	{
		bool		killnow = true;
		if (sdptr->AnimDataSize == TROOPANIM)		//must be the pilot
		{
			//Does he have an active chute?
			if (transit->Target)
			{
				//Kill the chute...
				TransientItem*	targ = (TransientItem*) *transit->Target;
				targ->Target = NULL;
				targ->LaunchTime = 0;
				targ->isOwned = 0;

				transit->Target = NULL;
			}

			AirStrucPtr	theLauncher = (AirStrucPtr)*transit->Launcher;
			if (theLauncher->AcIsPlayer())
			{
				//Exit the 3d....
				killnow = false;
				View_Object->Quit3D(0);
			}
			else
				transit->isOwned = 0;
		}
		else
		{
			//Does the chute have a pilot?
			if (transit->Target)
			{
				TransientItem*	targ = (TransientItem*) *transit->Target;
			
				killnow = false;

				targ->Target = NULL;
				targ->LaunchTime = 0;

				transit->Target = NULL;
			}

			transit->isOwned = 0;
		}

		if (killnow)
			AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileBarage
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileBarage(TransientItemPtr transit, WorldStuff&	world)
{
	// All re-jigged by ROB											//RJS 05Oct98
	SLong	timeleft = transit->LaunchTime;							//RJS 05Oct98
	SWord	frametime = Timer_Code.FRAMETIME;						//RJS 05Oct98

	if (timeleft)													
	{
		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;
	}
	else
	{
		SLong	groundheight = GetGroundLevel(transit) + METRES01;//RJS 14Apr99

		transit->World.Y = groundheight;						//RDH 29Nov98

		_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_TANK+Math_Lib.rnd(3)), (ItemBasePtr) transit);//RJS 22Nov96
		if (transit->Status.Drawn == 1)							//RJS 05Oct98
		{														//RJS 05Oct98
			if (Math_Lib.rnd() > 32768)							//MS 30Nov98
				LaunchSmallFlash((mobileitem*)transit,world);	//RJS 08Dec98
			else
			{
				LaunchFlash((mobileitem*)transit,0,world);		//MS 30Nov98
				LaunchDirtMedium((mobileitem*)transit,world);	//MS 30Nov98
			}
		}

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileDelayedExplosion
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileDelayedExplosion(TransientItemPtr transit, WorldStuff& worldptr)
{
	SLong	timeleft = transit->LaunchTime;
	SWord	frametime;

	frametime = Timer_Code.FRAMETIME;							//DAW 31Jul96

	if (timeleft && transit->Target)
	{
		transit->World.X = transit->Target->World.X;
		transit->World.Y = transit->Target->World.Y;
		transit->World.Z = transit->Target->World.Z;			//RJS 03Dec96
		transit->uniqueID.changed = TRUE;			//RJS 09Dec98

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		if (!CheckCommsValid(transit->Target))							//RJS 20Sep00
		{
			transit->TransRandom = 1;
			transit->LaunchTime = 0;
	
			AddTransientItemToDeadList(transit);
		}
	}
	else
	{
		// Is it a dummy explosion, or a live explosion?..
		switch (transit->TransRandom)
		{
			case 1:
				AddTransientItemToDeadList(transit);
				break;
			case 2:
			{
				// Launch explosive!!
				TransientItem*	newitem = SimplifiedSpriteLaunch(	transit->Launcher,
																	ExplosionThugShape,
																	0,
																	MOBILE_DELEXP	);
				if (newitem)
				{
					//Inherit old target as well as coords...
					newitem->Target = transit->Target;			//RJS 24Jun99
					newitem->World = transit->Target->World;
					newitem->TransRandom = 3;		//Detonate!!

					AddTransientItemToWorld(newitem,worldptr);
				}

				AddTransientItemToDeadList(transit);
				break;
			}
			case 3:
			{
				// Ignite explosive!!
				BoxCol::SpecificCollision(transit,transit->Target);
				AddTransientItemToDeadList(transit);
			}
			break;
			case 4:
			{
				AirStrucPtr	ac = (AirStrucPtr)*transit->Target;
				if (!_Replay.Playback)
				{
					Squad_Diary.SetKilledAC(ac,ac->Anim);				//RJS 21Sep00

					ac->vel_x = ac->vel_y = ac->vel_z = ac->vel_ = 0;	//RJS 30Aug00
					ExplodeAC(ac,ac,worldptr);

					Squad_Diary.UpdateKilledAC();						//RJS 4Sep00
				}
				else
				{
					LaunchBigExplosion(ac,worldptr,ac->shape);
					LaunchFingers(ac,worldptr);
				}

				if (ac == Persons2::PlayerSeenAC)						//RJS 30Aug00
					_Miles.StopEngine();								//RJS 30Aug00

//DeadCode RJS 31May00 				LaunchFire(ac,worldptr);
				LaunchAircraftFire(ac,ac->World,worldptr);

				AddTransientItemToDeadList(transit);
			}
			break;
			default:
			{
				if (WithinVisibleRange(transit->World,300000))	//RJS 30Apr99
				{
					MinAnimData*	mad = (MinAnimData*) transit->Anim;
					mad->IsInvisible = 0;

					_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_GROUND+Math_Lib.rnd(5)), (ItemBasePtr) transit);//RJS 05Dec96

					transit->LaunchTime = 100;
					transit->TransRandom = 1;

					LaunchSkinDebris(transit,worldptr);
				}
			}
			break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileFlak
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileFlak(TransientItemPtr transit, WorldStuff& worldptr)
{
	//All rewritten by Rob										//RJS 29Apr99
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		AddWindDrift(transit);
	}
	else
	{
//DEADCODE DAW 06/05/99		ShapeNum		theShape = ((TransientItem*)transit->Launcher)->shape;
		TransientItem*	newitem;
		UWord	randno = Math_Lib.rnd();

		if (randno > 16384)
			LaunchSmallFlash(transit,worldptr);

		newitem = SimplifiedSpriteLaunch(transit,transit->shape,400,MOBILE_STATIONARY);//RJS 10Aug00
		if (newitem)
		{
			_Miles.PlaySample((FileNum)(FIL_SFX_FLAK1+((3*randno)>>16)),newitem);

			AddTransientItemToWorld(newitem,worldptr);
		}

// This piece of flak is live!
		if (transit->TransRandom)
		{
			float	distx, disty, distz;
			const float	flakSizeSquared = 1000.f*1000.f;

			ItemPtr	trg = transit->currworld->getfirstitem(transit->currworld->GetSector(transit));
			while (trg)
			{
				if (trg->Status.size == AIRSTRUCSIZE)
				{
					distx = transit->World.X - trg->World.X;
					disty = transit->World.Y - trg->World.Y;
					distz = transit->World.Z - trg->World.Z;

					if ((distx*distx+disty*disty+distz*distz) < flakSizeSquared)
					{
						int	rightWing = NULL;

						ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(trg->shape);
						if (sdptr->AnimDataSize == AIRCRAFTANIM)
						{
							AircraftAnimData*	adptr = (AircraftAnimData*)trg->Anim;
							
							rightWing = &adptr->RIGHTWINGIN - UByteP(adptr);
						}
						else
						{
							if (sdptr->AnimDataSize == SIMPLEAIRCRAFTANIM)
							{
								SimpleAircraftAnimData*	adptr = (SimpleAircraftAnimData*)trg->Anim;

								rightWing = &adptr->RIGHTWINGIN - UByteP(adptr);
							}
						}

						if (rightWing)
							SHAPE.ForceWeaponDamage(trg,transit->Launcher,trg->shape,trg->Anim,-1,rightWing,DMT_BULLET,200);

						break;
					}
				}

				trg=trg->Next;
			}
		}

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileSparkTrail
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileSparkTrail(TransientItemPtr transit, WorldStuff& worldptr)
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		SWord	frametime = Timer_Code.FRAMETIME;
		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		if (transit->TmpLaunchTime && (transit->TmpLaunchTime != 65535))//RJS 19May99
		{														//RJS 14May99
			timeleft = transit->TmpLaunchTime;					//RJS 19May99
			timeleft -= frametime;								//RJS 14May99
			if (timeleft < 0)									//RJS 14May99
				timeleft = 0;									//RJS 14May99
																//RJS 14May99
			transit->TmpLaunchTime = timeleft;					//RJS 19May99
		}														//RJS 14May99

		if (!CheckCommsValid(transit->Target))							//RJS 20Sep00
		{
			transit->LaunchTime = transit->TmpLaunchTime = 0;

			AddTransientItemToDeadList(transit);
		}
	}
	else
	{
		if (transit->Target)
		{
			MinAnimData*	mad;
			mobileitem*		parent = (mobileitem*) transit->Target;

			mad = (MinAnimData*)parent->Anim;

			if (	(parent->movecode == MOBILE_NOPPILOT)		//RJS 28Jun99
				||	(parent->movecode == AUTO_RESURRECT)		//RJS 28Jun99
				||	mad->IsInvisible									//RJS 5Jun00
				||	(transit->TmpLaunchTime==0)				)	//RJS 28Jun99
				AddTransientItemToDeadList(transit);
			else
			{
				if (WithinVisibleRange(parent->World,100000))	//RJS 30Apr99
				{
					UWord	theShape = transit->TransRandom & 0x7FFF;

					// Throw sparks, or dirt...
//DEADCODE CSB 09/11/99 					SLong	maxlife = Math_Lib.rnd(100) * (MPH100 - parent->velhori);
					SLong	maxlife = Math_Lib.rnd(100) * (MPH100 - (parent->vel_/1000)); //RJS 16Nov99
					maxlife /= MPH100;
//DEADCODE CSB 09/11/99 					maxlife += ((MPH100-parent->velhori)*50)/MPH100;
					maxlife += ((MPH100-(parent->vel_/1000))*50)/MPH100; //RJS 16/11/99
					if (maxlife < 0)
						maxlife = Math_Lib.rnd(30);

					transit->LaunchTime = maxlife;

					maxlife = transit->pitch;
					maxlife>>=1;
					maxlife += Math_Lib.rnd(maxlife);

					TransientItemPtr	newitem;
					newitem = SimplifiedSpriteLaunch(	parent,
														(ShapeNum)theShape,
														maxlife,
														MOBILE_GANDF);

					if (newitem)
					{
						if ((transit->TransRandom & 0x8000)==0)
						{
							//we are above ground...
							if (transit->hdg)
							{
								SLong	vel = 100 + Math_Lib.rnd(100);

								newitem->pitch = Angles(Math_Lib.rnd(ANGLES_15Deg));//RJS 29Mar00
//DeadCode RJS 29Mar00 								newitem->vel_y = Math_Lib.rnd(vel)*1000;//RJS 16Nov99
								newitem->vel_ = vel;			//RJS 16Nov99
//DEADCODE CSB 09/11/99 								newitem->velhori = 200 - newitem->vely;
//DIRTY FIX !!!  Needs fixing properly //CSB 09/11/99
								newitem->hdg = (Angles)(Math_Lib.rnd(ANGLES_180Deg) - parent->hdg);

								newitem->CalcVels();
							}
							else
							{
								newitem->vel_ = (100 + Math_Lib.rnd(100))*1000;//RJS 16Nov99
//DEADCODE CSB 09/11/99 								newitem->velhori = Math_Lib.rnd(100);
//DIRTY FIX !!!  Needs fixing properly //CSB 09/11/99
								newitem->hdg = (Angles)(Math_Lib.rnd(ANGLES_90Deg) - parent->hdg - ANGLES_45Deg);
								newitem->movecode = MOBILE_STATIONARY;

								newitem->CalcVels();
							}
						}
						else
						{
							//just let float on the ground...
							newitem->movecode = MOBILE_STATIONARY;
							newitem->World.Y += 200;
						}

						AddTransientItemToWorld(newitem,worldptr);
					}
				}
			}
		}
		else
			AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileRicochetSmoke
//Author		Robert Slater
//Date			Thu 5 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileRicochetSmoke(TransientItemPtr transit, WorldStuff& worldptr)
{
#ifdef	_SOUND_TEST_
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		UWord	rotate = UWord(transit->roll);
		SLong	radius = 5000;
		SWord	sin_ang, cos_ang;
		SLong	xoff,zoff;

		Math_Lib.high_sin_cos((Angles)rotate,sin_ang,cos_ang);

		xoff = (radius * sin_ang)>>ANGLES_SHIFT;
		zoff = (radius * cos_ang)>>ANGLES_SHIFT;

		transit->World = View_Point->World;
		transit->World.X += xoff;
		transit->World.Z += zoff;

		rotate += 256;
		transit->roll = (Angles)rotate;

		_Miles.PlayLooped(FIL_SFX_BARGE_LOOP,transit);
	}
	else
		AddTransientItemToDeadList(transit);
#else
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		if (transit->vel_)								//CSB 09/11/99
			GAndFriction(transit,0);							//RDH 30Mar99
		else
		{
// are we smoke?..
			if (transit->TransRandom == 0xFFFF)
			{
				Coords3D	pos = transit->World;
				pos.Y += 8000 + Math_Lib.rnd(1000);

				Land_Scape.AddSmokeCloud(pos);
			}
		}
	}
	else
	{
		AddTransientItemToDeadList(transit);
	}
#endif
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileEngineStart
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
void TransObj::MobileEngineStart(TransientItemPtr transit, WorldStuff& worldptr)
{
	AircraftAnimData*	adptr = (AircraftAnimData*)transit->Launcher->Anim;

	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		SLong		index, xoffset;
		Coords3D	pos;
		mobileitem*	theLauncher = (mobileitem*)*(transit->Launcher);
		SWord		anglextra;

		adptr->enginestart = 1;
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		transit->TransRandom += Timer_Code.FRAMETIME;
		if (transit->TransRandom > 30)
		{
// Have smoke
			index = 0;
			while (SHAPE.GetLauncherPoint(theLauncher,index,LT_ENGINE,pos,xoffset))
			{
				TransientItem*	newitem;
				newitem = SimplifiedSpriteLaunch(	theLauncher,
													SMKENG,
													50,
													MOBILE_GANDF	);
				if (newitem)
				{
					anglextra = Math_Lib.rnd(ANGLES_30Deg);
					if (xoffset > 0)
						anglextra = -anglextra;

					newitem->vel_ = 1000;
//DeadCode RJS 29Mar00 					newitem->vel_y = Math_Lib.rnd(1000)-500;
					newitem->pitch = Angles(newitem->pitch + Math_Lib.rnd(ANGLES_10Deg));//RJS 29Mar00
					newitem->hdg = Angles(anglextra-SWord(theLauncher->hdg));
					newitem->World = pos;

					newitem->CalcVels();

					AddTransientItemToWorld(newitem,worldptr);
				}
			}
		}
	}
	else
	{
		adptr->enginestart=0;
		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileGuidedBurning
//Author		Robert Slater
//Date			Mon 8 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileGuidedBurning(TransientItemPtr transit, WorldStuff& worldptr)
{
	SLong		timeleft = transit->LaunchTime;					//RJS 16Nov98
	ItemPtr		thetarget = transit->Target;						//RJS 16Nov98
	
	if (timeleft)
	{
		_Miles.PlayLooped(FIL_SFX_SMALL_FIRE_LOOP, (ItemBasePtr) transit);//RJS 22Nov96
		SWord	frametime;

		frametime = Timer_Code.FRAMETIME;						//DAW 31Jul96

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		transit->World.X = thetarget->World.X - 50;					//RJS 23Jul96
		transit->World.Y = thetarget->World.Y + 30;					//RJS 23Jul96
		transit->World.Z = thetarget->World.Z + 70;					//RJS 23Jul96
		transit->uniqueID.changed = TRUE;			//RJS 09Dec98

		//Test for collision with the ground

		SLong	groundheight;

		groundheight = GetGroundLevel(transit);					//RJS 14Apr99

		if (transit->World.Y<groundheight)
			transit->World.Y = groundheight;
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileGuidedFire
//Author		Robert Slater
//Date			Tue 9 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileGuidedFire(TransientItemPtr transit, WorldStuff& worldptr)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft && transit->Target)
	{
		_Miles.PlayLooped((FileNum) FIL_SFX_FIREBURN_LOOP, (ItemBasePtr) transit);//RJS 22Nov96

		SWord	frametime;

		frametime = Timer_Code.FRAMETIME;						//DAW 31Jul96

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		transit->World.X = transit->Target->World.X;
		transit->World.Y = transit->Target->World.Y;
		transit->World.Z = transit->Target->World.Z;
		transit->uniqueID.changed = TRUE;			//RJS 09Dec98

		//Test for collision with the ground

		SLong	groundheight;

		groundheight = GetGroundLevel(transit);					//RJS 14Apr99

		if (transit->World.Y<groundheight)
			transit->World.Y = groundheight;
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileATeam
//Author		Robert Slater
//Date			Wed 10 Jul 1996
//
//Description	Throw an exploded object in the air 'A Team' style
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileATeam(TransientItemPtr transit, WorldStuff& worldptr)
{
	ItemPtr	theLauncher = transit->Launcher;
	UWord	animoff = transit->TransRandom;
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		SWord	frametime = Timer_Code.FRAMETIME;

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		// Are we already on the ground?
		if ((animoff & 0x8000)==0)
		{
			SWord	oldhdg = transit->hdg;

			transit->hdg = (Angles) (transit->vel_x / 1000); //CSB 09/11/99

			GAndFrictionFixedPitch(transit,OrdinaryDrag);

			transit->hdg = (Angles) oldhdg;

			SWord	hdgmag,pitchmag;

			hdgmag = (transit->vel_z / 1000) >> 8; //CSB 09/11/99
//DIRTY FIX !!! //CSB 09/11/99
			pitchmag = transit->vel_z & 0xFF;

			transit->roll += (Angles) hdgmag;
			transit->pitch += (Angles) pitchmag;

			if ((transit->LaunchTime & 0x04)==0)				//RJS 23Dec99
			{
				UByte	theArea;
				SLong	groundheight = GetGroundLevel(transit,theArea);//RJS 28Apr99
				if (transit->World.Y <= groundheight)
				{
//DeadCode RJS 28Apr99					UByte	theArea = Three_Dee.GetLandType();		//RJS 27Nov98

					Coords3D	hitcoords;

					transit->World.Y = groundheight;
					transit->TransRandom |= 0x8000;

					hitcoords = transit->World;

					DoImpactGround(transit,hitcoords,theArea);	//MS 30Nov98

					ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(theLauncher->shape);
					if (SHAPESTUFF.GetShapeScale(sdptr) != SHP_GRP)
					{
						// oooh... we can properly nobble its world coords...
						UWord	oldSector = worldptr.GetSector(*theLauncher);	//AMM 24Oct00

						theLauncher->World = transit->World;	//AMM 24Oct100

						if (oldSector != worldptr.GetSector(*theLauncher))//AMM 24Oct100
						{										//AMM 24Oct100
							worldptr.RemoveFromSector(theLauncher,oldSector);//AMM 24Oct100
							worldptr.AddToWorld(theLauncher);	//AMM 24Oct100
						}


//DeadCode AMM 24Oct100 						theLauncher->World = transit->World;
//DeadCode AMM 24Oct100 						theLauncher->uniqueID.changed = TRUE;
						if (theLauncher->Status.size >= RotatedSize)
						{
							rotitem*	tmpitm = (rotitem*) theLauncher;

							tmpitm->hdg = transit->hdg;
							tmpitm->pitch = transit->pitch;
							tmpitm->roll = transit->roll;
						}

						transit->LaunchTime = 0;	//kill now
					}
				}
			}
		}

//		if ((theLauncher->Status.size >= MovingSize) && (Math_Lib.rnd() > 62000))
//		{
//			TransientItemPtr	newitem;
//			newitem = SimplifiedSpriteLaunch((mobileitem*)transit,SMKFIR,200,MOBILE_STATIONARY);
//			if (newitem)
//				AddTransientItemToWorld(newitem,worldptr);
//		}
	}
	else
	{
		MinAnimData*	mad;
		animptr			adptr = theLauncher->Anim;				//RJS 21Apr99

		adptr += (animoff & 0x7FFF);							//RJS 21Apr99

		mad = (MinAnimData*) adptr;								//RJS 21Apr99
		mad->IsInvisible = 0;	//Turn the element back on...

		// If it can move, it probably still contains fuel...
		if ((mad->itemstate != DEAD) && (theLauncher->Status.size >= MovingSize))
		{
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(theLauncher->shape);

			theLauncher->Status.deadtime = sdptr->DeadTime;
			theLauncher->Status.deadscale = sdptr->DeadScale;
			theLauncher->Status.deaded = TRUE;		//RJS 27Feb98

			LaunchDelayedExplosion((mobileitem*)theLauncher,worldptr);
		}

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileDustRing
//Author		Robert Slater
//Date			Sun 13 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileDustRing(TransientItemPtr transit, WorldStuff& world)
{
//DeadCode RJS 20Apr98	SLong			timeleft=transit->LaunchTime;
//DeadCode RJS 20Apr98	UByte			count;
//DeadCode RJS 20Apr98
//DeadCode RJS 20Apr98	if (timeleft)
//DeadCode RJS 20Apr98	{
//DeadCode RJS 20Apr98		SWord	frametime;
//DeadCode RJS 20Apr98		SLong	groundheight;
//DeadCode RJS 20Apr98
//DeadCode RJS 20Apr98		frametime = Timer_Code.FRAMETIME;						
//DeadCode RJS 20Apr98
//DeadCode RJS 20Apr98		if ((transit->LaunchTime-=frametime)<0)
//DeadCode RJS 20Apr98			transit->LaunchTime=0;
//DeadCode RJS 20Apr98	}
//DeadCode RJS 20Apr98	else
//DeadCode RJS 20Apr98		AddTransientItemToDeadList(transit);
}

//DeadCode JIM 28Nov96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 28Nov96 //Procedure		MobileShockwave
//DeadCode JIM 28Nov96 //Author		Robert Slater
//DeadCode JIM 28Nov96 //Date			Wed 16 Oct 1996
//DeadCode JIM 28Nov96 //
//DeadCode JIM 28Nov96 //Description	Similar to bullet
//DeadCode JIM 28Nov96 //
//DeadCode JIM 28Nov96 //Inputs		
//DeadCode JIM 28Nov96 //
//DeadCode JIM 28Nov96 //Returns	
//DeadCode JIM 28Nov96 //
//DeadCode JIM 28Nov96 //------------------------------------------------------------------------------
//DeadCode JIM 28Nov96 void	TransObj::MobileShockwave(TransientItemPtr transit, WorldStuff& world)
//DeadCode JIM 28Nov96 {
//DeadCode JIM 28Nov96	if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)	
//DeadCode JIM 28Nov96		transit->LaunchTime=0;
//DeadCode JIM 28Nov96	else
//DeadCode JIM 28Nov96	{
//DeadCode JIM 28Nov96		if ((transit->LaunchTime & 0x03)==0)			
//DeadCode JIM 28Nov96		{
//DeadCode JIM 28Nov96			SLong	groundheight;
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96			groundheight = Land_Scape.GetGroundLevel((itemptr)transit);
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96			if (transit->World.Y<=groundheight)
//DeadCode JIM 28Nov96				transit->World.Y = groundheight;
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96			//Test for collision with other
//DeadCode JIM 28Nov96			//items
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96			itemptr	 hititem;
//DeadCode JIM 28Nov96 //DeadCode RDH 26Nov96			vector	 hitvector;
//DeadCode JIM 28Nov96 //DeadCode RDH 26Nov96			SByte	gindex;
//DeadCode JIM 28Nov96			Coords3D	hitcoords;
//DeadCode JIM 28Nov96			int	gindex;
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96		if ((transit->LaunchTime & 0x03)==0)					//PD 08Oct96
//DeadCode JIM 28Nov96			if (!transit->Status.deadtime)
//DeadCode JIM 28Nov96			{
//DeadCode JIM 28Nov96				hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);
//DeadCode JIM 28Nov96				if (hititem)	//_Collide.TransCollTest((MovingItemPtr )transit, hititem, hitvector, gindex))//RDH 26Nov96
//DeadCode JIM 28Nov96				{
//DeadCode JIM 28Nov96					transit->World=hitcoords;
//DeadCode JIM 28Nov96 //DeadCode RDH 26Nov96					transit->World.X = hitvector.a;			
//DeadCode JIM 28Nov96 //DeadCode RDH 26Nov96					transit->World.Y = hitvector.b;			
//DeadCode JIM 28Nov96 //DeadCode RDH 26Nov96					transit->World.Z = hitvector.c;			
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96					MissileHitSomething(hititem,transit,world,gindex);
//DeadCode JIM 28Nov96					transit->velhori >>= 1;
//DeadCode JIM 28Nov96				}
//DeadCode JIM 28Nov96			}												
//DeadCode JIM 28Nov96		}
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96		if (transit->LaunchTime>0)	
//DeadCode JIM 28Nov96			ApplyVelocities(transit);
//DeadCode JIM 28Nov96	}
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96	if (transit->LaunchTime<=0)
//DeadCode JIM 28Nov96		AddTransientItemToDeadList(transit);
//DeadCode JIM 28Nov96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileBird
//Author		Robert Slater
//Date			Thu 17 Oct 1996
//
//Description	Realistic movecode for a bird
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileBird(TransientItemPtr transit, WorldStuff& world)
{
	SLong			timeleft=transit->LaunchTime;
	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			SLong	groundheight = GetGroundLevel(transit);			//RJS 14Apr99

			if (transit->World.Y < groundheight)
			{
				transit->World.Y = groundheight + 50;
				transit->vel_y = 50000 + (Math_Lib.rnd(100)*1000);//RJS 16Nov99
			}

			if (transit->vel_y < -50000)						//CSB 09/11/99
				transit->vel_y = 50000 + (Math_Lib.rnd(100)*1000);//RJS 16Nov99
		}

		if (Math_Lib.rnd() > 62000)
			_Miles.PlayOnce(FIL_SFX_AMB_BIRD_TWEET1,transit);

		GAndFriction(transit,OrdinaryDrag);
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileAmmoBoxes
//Author		Robert Slater
//Date			Thu 17 Oct 1996
//
//Description	Sends sparks, then blows up
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileAmmoBoxes(TransientItemPtr transit, WorldStuff& world)
{
	TransientItemPtr	newitem;						
	SLong			timeleft=transit->LaunchTime;
	UByte			count;

	if (timeleft)
	{
		SWord	frametime;
		SLong	groundheight;
		UWord	triggerspark;

		frametime = Timer_Code.FRAMETIME;						

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		// throw sparks...

//DeadCode RJS 28May99 		triggerspark = Math_Lib.rnd();
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 		if (triggerspark > 60000+(TransientItem::transcount<<4))
		if (desiredFPS <= realFPS)				//RJS 11Jun99
		{
			newitem = SimplifiedSpriteLaunch((mobileitem*)transit,SparkShape,300,MOBILE_DEBRIS);//RJS 28May99
			if (newitem)
			{
				SLong	vel = 100 + Math_Lib.rnd(100);

				newitem->hdg = (Angles) Math_Lib.rnd();			
//DeadCode RJS 29Mar00 				newitem->vel_y = Math_Lib.rnd(vel)*1000;		//RJS 16Nov99
				newitem->pitch = Angles(Math_Lib.rnd(ANGLES_45Deg));//RJS 29Mar00
				newitem->vel_ = vel*1000;						//RJS 16Nov99
//DEADCODE CSB 09/11/99 				newitem->velhori = 100 + Math_Lib.rnd(100);			
//DIRTY FIX !!! //CSB 09/11/99
				newitem->TransRandom = 0;					
				newitem->CalcVels();

				AddTransientItemToWorld(newitem,world);

				_Miles.PlaySample((FileNum) (FIL_SFX_RICOCHET_HARD_SURFACE4+Math_Lib.rnd(4)), (ItemBasePtr) newitem);//RJS 22Nov96
			}
		}
	}
	else
	{
		animptr			duffptr = transit->Launcher->Anim;
		duffptr += transit->TransRandom;

		ShapeNum		shapehit = (ShapeNum) UWord(transit->pitch);	//RJS 20Nov98
		ShapeNum		shapethrow = (ShapeNum) UWord(transit->roll);	//RJS 20Nov98
//		MyGroundVector	gvector;								//RJS 21Nov96
		MinAnimData*	adptr = (MinAnimData* ) duffptr;
//		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shapehit);
//		SLong			halfboxes = ((sdptr->Size << 4) / 176) / 2;
		SLong			noboxes = 2 + Math_Lib.rnd(4);

		adptr->itemstate = DEAD;								//RJS 20Nov98

		LaunchBigExplosion((mobileitem*)transit,world,shapehit);//RJS 08Nov96
		_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_AIR1+Math_Lib.rnd(3)), (ItemBasePtr) transit);//RJS 22Nov96

		if (desiredFPS > realFPS)					//RJS 28May99
			noboxes = 1;										//RJS 28May99

		SLong	vel;
		for (count = 0; count < noboxes; count++)
		{
			newitem = SimplifiedSpriteLaunch(	transit,
												shapethrow,
												LIFETIME_DEBRISLNCHR,
												MOBILE_DEBRIS);
			if (newitem)
			{
				vel = 100 + Math_Lib.rnd(100);

				newitem->hdg = (Angles) Math_Lib.rnd();				//RJS 16Aug96
				newitem->roll = (Angles) Math_Lib.rnd();			//RJS 16Aug96
				newitem->pitch = Angles(Math_Lib.rnd(ANGLES_45Deg));//RJS 29Mar00
//DeadCode RJS 29Mar00 				newitem->vel_y = ((vel>>1) + Math_Lib.rnd(vel>>1))*1000;//RJS 16Nov99
				newitem->vel_ = vel*1000;						//RJS 16Nov99
				newitem->CalcVels();
//DEADCODE CSB 09/11/99 				newitem->velhori = 50 + Math_Lib.rnd(50);			//RJS 16Aug96
//DIRTY FIX !!! //CSB 09/11/99
				newitem->TransRandom = Math_Lib.rnd();				//RJS 16Aug96
				AddTransientItemToWorld(newitem,world);
			}
		}

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileBigExplosion
//Author		Robert Slater
//Date			Mon 12 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileBigExplosion(TransientItemPtr transit, WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;
	ItemPtr	pTarget = transit->Target;

	if (timeleft)
	{
//DeadCode DAW 28Jun99 		_Miles.PlayLooped((FileNum) FIL_SFX_FIREBURN_LOOP, (ItemBasePtr) transit);//RJS 22Nov96

		SWord	frametime = Timer_Code.FRAMETIME;						//RJS 16Nov98

		if ((transit->LaunchTime-=frametime)<=0)				//RJS 07Aug97
			transit->LaunchTime=0;								//RJS 07Aug97

		if (pTarget)											//RJS 16Nov98
		{														//DAW 03Sep98
			transit->World.Y = pTarget->World.Y;				//RJS 16Nov98
			transit->World.X = pTarget->World.X;				//RJS 16Nov98
			transit->World.Z = pTarget->World.Z;				//RJS 16Nov98
			transit->uniqueID.changed = TRUE;			//RJS 09Dec98

//DeadCode RJS 9Oct00 			_Miles.PlayLooped(FIL_SFX_FIREBURN_LOOP, pTarget);//RJS 27Jun99
		}														//DAW 03Sep98
	}
	else
	{
//DeadCode RJS 28Jun99 		if (pTarget)											//RJS 16Nov98
//DeadCode RJS 28Jun99 		{														//RJS 16Nov98
//DeadCode RJS 28Jun99 			if (pTarget->shape == PDEATH)						//RJS 16Nov98
//DeadCode RJS 28Jun99 				LaunchFire((mobileitem*)pTarget,world);			//RJS 16Nov98
//DeadCode RJS 28Jun99 		}														//RJS 16Nov98

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileMushroomCloud
//Author		Robert Slater
//Date			Wed 6 Nov 1996
//
//Description	Nothing to do with mushroom clouds.....
//
//				Is actually a dummy bomb movecode...	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileDummyBomb(TransientItemPtr transit, WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		SWord	frametime = Timer_Code.FRAMETIME;

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

//DeadCode RJS 17Oct00 		GAndFriction(transit,OrdinaryDrag);

		if (transit->TransRandom > timeleft)
		{
			_Miles.PlaySample(FIL_SFX_BOMB_WHISTLE,transit);
			transit->TransRandom = 0;
		}

		// While frametime is in 50ths
		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			//Test for collision with the ground

			SLong	groundheight = GetGroundLevel(transit);		//RJS 14Apr99
			if (transit->World.Y<groundheight)
			{
				transit->World.Y = groundheight;
				transit->LaunchTime = 0;
				_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_TANK+Math_Lib.rnd(3)), (ItemBasePtr) transit);//RJS 03Dec96
				//Launch flash??...
			}
		}

		//move the bomb
		if (transit->LaunchTime>0)	
		{
			GAndFriction(transit,50);

			AddWindDrift(transit);
			transit->BombPitch();
		}
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileVapourTransient
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
void	TransObj::MobileVapourTransient(TransientItemPtr	transit, WorldStuff&	world)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileRocket
//Author		Robert Slater
//Date			Wed 4 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileRocket(TransientItemPtr	transit, WorldStuff&	world)
{
//DeadCode MS 30Nov98	SLong	timeleft = transit->LaunchTime;
//DeadCode MS 30Nov98	if (timeleft)
//DeadCode MS 30Nov98	{
//DeadCode MS 30Nov98		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
//DeadCode MS 30Nov98			transit->LaunchTime = 0;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98		if ((transit->LaunchTime & 0x04)==0)//RJS 23Dec99
//DeadCode MS 30Nov98		{
//DeadCode MS 30Nov98			itemptr		hititem;
//DeadCode MS 30Nov98			Coords3D	hitcoords;
//DeadCode MS 30Nov98			int			gindex;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98			if (transit->Status.deadtime == 0)					
//DeadCode MS 30Nov98			{
//DeadCode MS 30Nov98				hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);
//DeadCode MS 30Nov98				if (hititem)
//DeadCode MS 30Nov98				{
//DeadCode MS 30Nov98					transit->LaunchTime=0;								
//DeadCode MS 30Nov98					transit->TransRandom = 2;
//DeadCode MS 30Nov98				}
//DeadCode MS 30Nov98				else
//DeadCode MS 30Nov98				{
//DeadCode MS 30Nov98					SLong	groundheight = Land_Scape.GetGroundLevel(transit);
//DeadCode MS 30Nov98					if (transit->World.Y<=groundheight)
//DeadCode MS 30Nov98					{
//DeadCode MS 30Nov98						UByte	theArea = Three_Dee.GetLandType();//MS 30Nov98
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98						transit->LaunchTime=0;								
//DeadCode MS 30Nov98						transit->TransRandom = 2;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98						hitcoords = transit->World;
//DeadCode MS 30Nov98						hitcoords.Y = groundheight+METRES01;
//DeadCode MS 30Nov98																			
//DeadCode MS 30Nov98						DoImpactGround(transit,hitcoords,theArea);//MS 30Nov98
//DeadCode MS 30Nov98					}
//DeadCode MS 30Nov98				}
//DeadCode MS 30Nov98			}
//DeadCode MS 30Nov98		}														//RJS 09Nov98
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98		if (transit->LaunchTime)
//DeadCode MS 30Nov98		{
//DeadCode MS 30Nov98			switch (transit->TransRandom)
//DeadCode MS 30Nov98			{
//DeadCode MS 30Nov98				case 0:
//DeadCode MS 30Nov98				case 2:
//DeadCode MS 30Nov98					GAndFriction(transit,OrdinaryDrag);
//DeadCode MS 30Nov98					break;
//DeadCode MS 30Nov98				case 1:
//DeadCode MS 30Nov98					SLong	velx, vely, velz, velhori;
//DeadCode MS 30Nov98					SWord	sin_ang, cos_ang;
//DeadCode MS 30Nov98					SLong	accel = 16;				// crap val
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98					Math_Lib.high_sin_cos((ANGLES )transit->pitch,sin_ang,cos_ang);
//DeadCode MS 30Nov98					vely = (accel * sin_ang)>>15;
//DeadCode MS 30Nov98					velhori = (accel * cos_ang)>>15;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98					transit->vely += vely;
//DeadCode MS 30Nov98					transit->velhori += velhori;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98					Math_Lib.high_sin_cos((ANGLES )transit->hdg,sin_ang,cos_ang);
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98					velx = (transit->velhori * sin_ang)>>15;
//DeadCode MS 30Nov98					velz = (transit->velhori * cos_ang)>>15;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98					transit->velx = velx;
//DeadCode MS 30Nov98					transit->velz = velz;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98					GAndFriction(transit,OrdinaryDrag);
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98					break;
//DeadCode MS 30Nov98			}
//DeadCode MS 30Nov98		}
//DeadCode MS 30Nov98	}
//DeadCode MS 30Nov98	else
//DeadCode MS 30Nov98	{
//DeadCode MS 30Nov98		switch (transit->TransRandom)
//DeadCode MS 30Nov98		{
//DeadCode MS 30Nov98		case 0:
//DeadCode MS 30Nov98		{
//DeadCode MS 30Nov98			MoveGunAnimData	*adptr = (MoveGunAnimData*)transit->Anim;
//DeadCode MS 30Nov98			WeapAnimData*	weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98			SHAPE.InitTrailFields((UByteP)weapon,0,5000,LT_FUEL);
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98			transit->LaunchTime = 500;
//DeadCode MS 30Nov98			transit->TransRandom = 1;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98			_Miles.PlayOnce(FIL_SFX_MISSILE2, transit);
//DeadCode MS 30Nov98			LaunchVapourStream((UByteP)weapon,transit->shape);
//DeadCode MS 30Nov98			break;
//DeadCode MS 30Nov98		}
//DeadCode MS 30Nov98		case 1:
//DeadCode MS 30Nov98		{
//DeadCode MS 30Nov98			transit->LaunchTime = 3000;
//DeadCode MS 30Nov98			transit->TransRandom = 2;
//DeadCode MS 30Nov98			break;
//DeadCode MS 30Nov98		}
//DeadCode MS 30Nov98		default:
//DeadCode MS 30Nov98		{
//DeadCode MS 30Nov98			AddTransientItemToDeadList(transit);
//DeadCode MS 30Nov98			break;
//DeadCode MS 30Nov98		}
//DeadCode MS 30Nov98		}
//DeadCode MS 30Nov98	}

	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime = 0;

		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			itemptr		hititem;
			Coords3D	hitcoords;
			int			gindex;

			if (transit->Status.deadtime == 0)					
			{
				hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);
				if (hititem)
				{
					transit->LaunchTime=0;								
//DeadCode RJS 26Feb99					transit->TransRandom = 2;
				}
				else
				{
					UByte	theArea;
					SLong	groundheight = GetGroundLevel(transit,theArea);//RJS 28Apr99
					if (transit->World.Y<=groundheight)
					{
//DeadCode RJS 28Apr99						UByte	theArea = Three_Dee.GetLandType();//MS 30Nov98

						transit->LaunchTime=0;								
//DeadCode RJS 26Feb99						transit->TransRandom = 2;

						hitcoords = transit->World;
						hitcoords.Y = groundheight+METRES01;
																			
						DoImpactGround(transit,hitcoords,theArea);//MS 30Nov98
					}
				}
			}
		}														//RJS 09Nov98

		SWord	burntime = SWord(transit->TransRandom);			//RJS 26Feb99
		if (!burntime)											//RJS 15Jun99
			GAndFriction(transit,0);							//RJS 26Feb99
		else													//RJS 26Feb99
		{														//RJS 26Feb99
			ApplyVelocities(transit);							//RJS 26Feb99

			burntime -= Timer_Code.FRAMETIME;					//RJS 15Jun99
			if (burntime <= 0)									//RJS 15Jun99
			{													//RJS 15Jun99	
				burntime = 0;									//RJS 15Jun99
				SHAPE.DetatchAllVapourStreams(transit,400);		//RJS 15Jun99
			}													//RJS 15Jun99
			transit->TransRandom = UWord(burntime);				//RJS 26Feb99
		}														//RJS 26Feb99
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴|컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileCloneGun
//Author		Robert Slater
//Date			Mon 22 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileCloneGun(TransientItemPtr transit, WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		//Kill some time....

		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;
	}
	else
	{
		CloneAnimData*		adptr = (CloneAnimData*) transit->Anim;
		mobileitem			*theShooter = (mobileitem*)adptr->originitm;

		if (theShooter->movecode != AUTO_SPAREAC)						//RJS 30Aug00
		{
			SLong	clonesleft = transit->TransRandom;
			if (clonesleft)
			{
				Coords3D			weappos;
				SLong				index = adptr->weapindex;
				SLong				index2 = adptr->weapindex2;
				WeapAnimData*		weapanim;
				ULong				mvel;							//RJS 12Nov99
				UWord				mdelay,mburst;					//RJS 12Nov99
				SLong				velx,vely,velz;					//RJS 16Nov99
				Float				vel,velh;						//RJS 16Nov99
				ANGLES				hdg,pitch;
				AutoMoveCodeTypeSelect	mcode;
				SLong				theLifetime;
				ShapeNum			theShape = (ShapeNum) adptr->shapename;
				SWord				muzPitch = 0;	// Maybe defined in airstruc
				LnchrType			launchmask = (LnchrType)(adptr->lnchtype & LT_MASK);//RJS 09Jul99
				
				vel = transit->vel_;

				switch (launchmask)							//RJS 09Jul99
				{
					case LT_BOMB:
						theLifetime = LIFETIME_BOMB;
						mcode = MOBILE_BOMBDROP;
						break;
					case LT_ROCKET:
						theLifetime = LIFETIME_ROCKET;
						mcode = MOBILE_ROCKET;
						break;

					default:
						theLifetime = LIFETIME_BULLET;
						mcode = MOBILE_BULLET;
						break;
				}

				weapanim = SHAPE.GetWeaponLauncher((itemptr)theShooter,index,weappos.X,weappos.Y,weappos.Z,mvel,mdelay,mburst,launchmask);//RJS 09Jul99
				if (weapanim && (weapanim->LoadedStores > 0))
				{
					//Block for B29 GUNS
					if (	(theShooter->Status.size>=MOBILESIZE)	//RJS 09Jul99
						&&	((weapanim->LauncherType & LT_MASK) != LT_MOVEGUN)	)	//RJS 09Jul99
					{
						if (theShooter->Status.size>=AIRSTRUCSIZE)
						{
							AirStrucPtr AC = (AirStrucPtr)theShooter;
							AC->CalcBulletVel(mvel, weappos.X, weappos.Y, weappos.Z, velx, vely, velz);
							hdg = AC->hdg;
							pitch = AC->pitch;
	//DeadCode CSB 11Aug00 						SWord bhdg, bpitch;
	//DeadCode CSB 11Aug00 						SLong bvel;						
	//DeadCode CSB 11Aug00 						AC->CalcBulletVel(mvel, bhdg, bpitch, bvel);
	//DeadCode CSB 11Aug00 						hdg   = (Angles)bhdg;
	//DeadCode CSB 11Aug00 						pitch = (Angles)bpitch;
	//DeadCode CSB 11Aug00 						vel   = Float(bvel);
	//DeadCode CSB 11Aug00 
	//DeadCode CSB 11Aug00 						Float sin_ang,cos_ang;
	//DeadCode CSB 11Aug00 						Math_Lib.high_sin_cos(pitch,sin_ang,cos_ang);
	//DeadCode CSB 11Aug00 						vely = vel * sin_ang;
	//DeadCode CSB 11Aug00 						velh = vel * cos_ang;
	//DeadCode CSB 11Aug00 
	//DeadCode CSB 11Aug00 						Math_Lib.high_sin_cos(hdg,sin_ang,cos_ang);
	//DeadCode CSB 11Aug00 						velx = velh * sin_ang;
	//DeadCode CSB 11Aug00 						velz = velh * cos_ang;
						}
						else
						{
							Float	sin_ang,cos_ang;
							Float	totalvel = Float(theShooter->vel_ + mvel);

							muzPitch += (SWord) theShooter->pitch;			//RJS 21Jul98

							hdg = theShooter->hdg;
							pitch = (Angles) muzPitch;						//RJS 21Jul98
							Math_Lib.high_sin_cos(pitch,sin_ang,cos_ang);

							vely = totalvel * sin_ang;
							velh = totalvel * cos_ang;

							Math_Lib.high_sin_cos(hdg,sin_ang,cos_ang);

							velx = velh * sin_ang;
							velz = velh * cos_ang;

							vel = totalvel;
						}
					}
					else
					{
	//DEADCODE CSB 09/11/99 					velh = transit->velhori;
						vel = transit->vel_;
						vely = transit->vel_y;
						velx = transit->vel_x;
						velz = transit->vel_z;
						hdg = transit->hdg;
						pitch = transit->pitch;
					}

					Bool	isArmed;								//RJS 27May99
					if (transit->Status.deadtime)					//RJS 27May99
						isArmed = FALSE;							//RJS 27May99
					else											//RJS 27May99
						isArmed = TRUE;								//RJS 27May99

					LaunchSuperLauncher(theShooter,
										theShape,
										theLifetime+Math_Lib.rnd(30)|3,
										mcode,
										weappos,
										hdg,
										pitch,
										velx,
										vely,
										velz,
	//DEADCODE CSB 09/11/99 									velh,
										SLong(vel),
										transit->nationality,
										index,			
										index2,
										adptr->delay,				//RJS 21Jul98
										clonesleft,//-1,						//RJS 20Jun00
										adptr->lnchtype,
										world,
										isArmed);					//RJS 27May99

					if (	(theShooter->Status.size == AIRSTRUCSIZE)			//CSB 20Jun00
						&&	((weapanim->LauncherType & LT_MASK) != LT_MOVEGUN)	)
						weapanim->LoadedStores-=AirStrucPtr(theShooter)->classtype->noGuns;	//CSB 20Jun00
					else													//CSB 20Jun00
						weapanim->LoadedStores--;							//CSB 20Jun00
				}
				else
					ClearGunFlash(theShooter);							//RJS 12Nov00
			}
			else
				ClearGunFlash(theShooter);								//RJS 12Nov00
		}
		else
			ClearGunFlash(theShooter);									//RJS 12Nov00

		transit->isOwned = 0;									//RJS 09Jul99

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileNapalm
//Author		Robert Slater
//Date			Thu 22 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileNapalm(TransientItemPtr transit, WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;
	}
	else
	{
		TransientItemPtr newitem = SimplifiedSpriteLaunch(	transit,
															NAPBLB,			//RJS 15Dec99
															240,
															MOBILE_BURNIT);//RJS 18Nov98

		if (newitem)											//RJS 09Feb98
		{
			Three_Dee.pMigLand->GetShadowAngles(newitem->World,newitem->hdg,newitem->pitch,newitem->roll);

			newitem->Status.deadtime = (UByte)transit->Status.deadtime;//RJS 13May99
			newitem->Target = transit->Target;				//RJS 11May99
			newitem->Launcher = transit->Launcher;			//RJS 05May99
			newitem->pitch = transit->pitch;
			newitem->TransRandom = 50 << 8;
			newitem->TransRandom |= 240;
			newitem->hdg = transit->hdg;
			AddTransientItemToWorld(newitem,world);			//RJS 09Feb98
		}

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileDoDamage
//Author		Robert Slater
//Date			Wed 18 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileDoDamage(TransientItemPtr transit,WorldStuff& world)
{

	if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)			
		transit->LaunchTime=0;
	else
	{
//DeadCode RJS 13Aug00 		transit->TransRandom += Timer_Code.FRAMETIME;
		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			if (transit->Status.deadtime == 0)					
			{
				ItemPtr		hititem;
				Coords3D	hitcoords;
				int		gindex;

				ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(transit->shape);
				if (sdptr->AnimDataSize == MISSILEANIM)
				{
					MissileAnimData*	adptr = (MissileAnimData*) transit->Anim;
					if (adptr->hitstrength)
					{
						adptr->frameno = transit->TransRandom;

						hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);
						if (hititem)
						{
							MinAnimData*	mad = (MinAnimData*) BoxCol::HitAdptr();
							DeathTollLink*	pDToll = (DeathTollLink*) adptr->lastmissile;

							if (mad)
							{
								DeathTollLink*	pNewToll = new DeathTollLink(mad,pDToll);
								if (pNewToll)
								{
									mad->IsBullied = 1;
									adptr->lastmissile = ULong(pNewToll);
									adptr->pad = 8;
								}

								// Full-on impact in 1st frame, so absorb some of the energy...
								if (transit->TransRandom==Timer_Code.FRAMETIME)
								{
									SLong	absorbstrength = (adptr->hitstrength * 3)>>2;

									if (absorbstrength)
										adptr->hitstrength = absorbstrength;
									else
										adptr->hitstrength = 1;
								}
							}
						}
					}
					else
						hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);
				}
				else
					hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);
			}
		}

		transit->TransRandom += Timer_Code.FRAMETIME;					//RJS 13Aug00
	}

	if (transit->LaunchTime<=0)
	{
//DeadCode RJS 5Jun00 		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(transit->shape);
//DeadCode RJS 5Jun00 		if (sdptr->AnimDataSize == MISSILEANIM)
//DeadCode RJS 5Jun00 		{
//DeadCode RJS 5Jun00 			MissileAnimData*	adptr = (MissileAnimData*) transit->Anim;
//DeadCode RJS 5Jun00 			DeathTollLink*		pDToll = (DeathTollLink*) adptr->lastmissile;
//DeadCode RJS 5Jun00 
//DeadCode RJS 5Jun00 			delete pDToll;
//DeadCode RJS 5Jun00 
//DeadCode RJS 5Jun00 			adptr->lastmissile = NULL;
//DeadCode RJS 5Jun00 		}

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileThuggery
//Author		Robert Slater
//Date			Mon 2 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileThuggery(TransientItemPtr transit,WorldStuff& world)
{
	ThugAnimData	*adptr = (ThugAnimData*) transit->Anim;

	if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)			
		transit->LaunchTime=0;
	else
	{
		SWord	ptime, ntime;
		Bool	scared = TRUE;

		ptime = adptr->prevcount;
		ntime = adptr->nextcount;

		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			GrpMinAnimData*	mad=NULL;									//RJS 20Oct00
			ItemPtr			theVictim = (ItemPtr)transit->Target;	//RJS 05Jul99

			// Wait until last half a sec to start hitting...
			if (transit->TransRandom && (ptime < 16))
			{
				transit->uniqueID.changed = TRUE;			//RJS 09Dec98
				transit->World.X = adptr->pXPos;
				transit->World.Y = adptr->pYPos;
				transit->World.Z = adptr->pZPos;
				transit->TransRandom = 0;
				scared = FALSE;

				animptr	tmpanim = theVictim->Anim;	//RJS 05Jul99
//DeadCode AMM 05Jul99 				animptr	tmpanim = transit->Launcher->Anim;
				tmpanim += adptr->panimoff;

				mad = (GrpMinAnimData*) tmpanim;
			}
			else
			{
				// Wait until last half a sec to start hitting...
				if (ntime < 16)
				{
					transit->uniqueID.changed = TRUE;			//RJS 09Dec98
					transit->World.X = adptr->nXPos;
					transit->World.Y = adptr->nYPos;
					transit->World.Z = adptr->nZPos;
					transit->TransRandom = 1;
					scared = FALSE;
				
					animptr	tmpanim = theVictim->Anim;	 //RJS 05Jul99
//DeadCode AMM 05Jul99 					animptr	tmpanim = transit->Launcher->Anim;
					tmpanim += adptr->nanimoff;
		
					mad = (GrpMinAnimData*) tmpanim;
				}
			}

			if (!scared && (mad->itemstate != DEAD))
			{
				itemptr		hititem;

				hititem=BoxCol::SpecificCollision(transit,theVictim);//RJS 05Jul99	
//DeadCode AMM 05Jul99 				hititem=BoxCol::SpecificCollision(transit,transit->Launcher);
			}
		}

		ptime -= Timer_Code.FRAMETIME;
		ntime -= Timer_Code.FRAMETIME;
		if (ptime < 0)
			ptime = 0;

		if (ntime < 0)
			ntime = 0;

		adptr->prevcount = ptime;
		adptr->nextcount = ntime;
	}

	if (transit->LaunchTime<=0)
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileSmallThug
//Author		Robert Slater
//Date			Thu 3 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileSmallThug(TransientItemPtr transit,WorldStuff& world)
{
	ThugAnimData	*adptr = (ThugAnimData*) transit->Anim;

	if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)			
		transit->LaunchTime=0;
	else
	{
		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			animptr	tmpanim = transit->Target->Anim;			//DAW 23Apr99
			tmpanim += adptr->panimoff;							//DAW 23Apr99
																//DAW 23Apr99
			MinAnimData*	mad = (MinAnimData*) tmpanim;		//RJS 26Apr99

			if (mad->itemstate != DEAD)							//RJS 26Apr99
			{
				itemptr		hititem;

				hititem=BoxCol::SpecificCollision(transit,transit->Target);
			}
			else
				transit->LaunchTime = 0;
		}
	}

	if (transit->LaunchTime<=0)
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoSpiral2Ground
//Author		Paul.
//Date			Wed 1 May 1996
//
//Description	A/c death spiral
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MoveAirStruc::AutoSpiral2Ground(WorldStuff& world)
{
//DeadCode RJS 20Oct00 	SWord	frametime = Timer_Code.FRAMETIME;					//DAW 31Jul96
	SLong	groundheight;										//DAW 03Sep98
//DeadCode DAW 03Sep98	if (shape != CRATER)
//DeadCode DAW 03Sep98	{
//DeadCode DAW 03Sep98		SLong	groundheight;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98		Trans_Obj.GAndFriction((mobileitem* )this,OrdinaryDrag);
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98		groundheight = Land_Scape.GetGroundLevel((itemptr)this);
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98		if (World.Y<=groundheight)
//DeadCode DAW 03Sep98		{
//DeadCode DAW 03Sep98			World.Y = groundheight;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			velx =
//DeadCode DAW 03Sep98				vely =
//DeadCode DAW 03Sep98				velz =
//DeadCode DAW 03Sep98				velhori = 0;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			if (shape == WRECK)
//DeadCode DAW 03Sep98			{
//DeadCode DAW 03Sep98				pitch = ANGLES_0Deg;							//RJS 21Nov96
//DeadCode DAW 03Sep98				roll = ANGLES_0Deg;								//RJS 21Nov96
//DeadCode DAW 03Sep98				shape = CRATER;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98				if (this == Manual_Pilot.ControlledAC2)
//DeadCode DAW 03Sep98				{
//DeadCode DAW 03Sep98					_Miles.StopEngine();
//DeadCode DAW 03Sep98					Manual_Pilot.controlmode=Manual_Pilot.PILOTDEAD;
//DeadCode DAW 03Sep98					GR_Quit3DNow=CRASHED_DEAD;
//DeadCode DAW 03Sep98					Trans_Obj.View_Object->SetToDeathView();				//RDH 02Sep98
//DeadCode DAW 03Sep98				}
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98 // in here when burning wreck hits ground, i.e. after collision	//AMM 20Feb97
//DeadCode DAW 03Sep98 // or if plane has burst into flames after being shot			//AMM 20Feb97
//DeadCode DAW 03Sep98 // score has already been set									//AMM 20Feb97
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98				if(_DPlay.Implemented)
//DeadCode DAW 03Sep98				{
//DeadCode DAW 03Sep98 // crash into ground after spiralling to ground
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98					_DPlay.item2place=ST_CRATER;
//DeadCode DAW 03Sep98					_DPlay.SendKill(*this,GR_Quit3DNow,PIDC_FIRECRATER,NULL);//AMM 16Jun97
//DeadCode DAW 03Sep98					_DPlay.ResurrectMe(*this,TRUE);
//DeadCode DAW 03Sep98				}
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98				Trans_Obj.LaunchFire(*this,*currworld);
//DeadCode DAW 03Sep98			}
//DeadCode DAW 03Sep98			else
//DeadCode DAW 03Sep98			{
//DeadCode DAW 03Sep98				if (this == Manual_Pilot.ControlledAC2)			//RJS 12Sep97
//DeadCode DAW 03Sep98				{												//RJS 12Sep97
//DeadCode DAW 03Sep98					_Miles.StopEngine();						//RJS 12Sep97
//DeadCode DAW 03Sep98					GR_Quit3DNow=CRASHED_DEAD;					//RJS 12Sep97
//DeadCode DAW 03Sep98					
//DeadCode DAW 03Sep98					Trans_Obj.View_Object->SetToDeathView();				//RDH 02Sep98
//DeadCode DAW 03Sep98																//RJS 12Sep97
//DeadCode DAW 03Sep98					if(_DPlay.Implemented)						//RJS 12Sep97
//DeadCode DAW 03Sep98					{											//RJS 12Sep97
//DeadCode DAW 03Sep98						_DPlay.item2place=ST_CRATER;			//RJS 12Sep97
//DeadCode DAW 03Sep98						_DPlay.SendKill(*this,GR_Quit3DNow,PIDC_FIRECRATER,NULL);//RJS 12Sep97
//DeadCode DAW 03Sep98						_DPlay.ResurrectMe(*this,TRUE);			//RJS 12Sep97
//DeadCode DAW 03Sep98					}											//RJS 12Sep97
//DeadCode DAW 03Sep98					else										//RJS 12Sep97
//DeadCode DAW 03Sep98						Manual_Pilot.DeathSequenceOverride(*this,AUTO_CRASHROLL);//RDH 02Sep98
//DeadCode DAW 03Sep98 //						Manual_Pilot.ControlledAC2->movecode = AUTO_CRASHROLL;//RJS 12Sep97
//DeadCode DAW 03Sep98				}												//RJS 12Sep97
//DeadCode DAW 03Sep98			}
//DeadCode DAW 03Sep98		}
//DeadCode DAW 03Sep98		else
//DeadCode DAW 03Sep98		{
//DeadCode DAW 03Sep98			AircraftAnimData*	adptr;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			adptr = (AircraftAnimData *)Anim;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			UWord	lcldamflag;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98 //DeadCode RJS 09Jun97			lcldamflag = adptr->dammageflags;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			//Check the state of the wings
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			SWord lrstate=0,tstate=0;			//try initialising variables - it stops bugs
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			// Calculate lift using new damage flags...........
//DeadCode DAW 03Sep98			// In a bit.......
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97			lrstate = adptr->BOTLEFTWING + adptr->TOPLEFTWING;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97 //DeadCode RJS 21Feb97			lrstate = (lcldamflag >> BF_LBWing) & BS_DEAD;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97 //DeadCode RJS 21Feb97			lrstate += (lcldamflag >> BF_LTWing) & BS_DEAD;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97			tstate = lrstate;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97			lrstate -= adptr->BOTRIGHTWING;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97			lrstate -= adptr->TOPRIGHTWING;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97 //DeadCode RJS 21Feb97			lrstate -= (lcldamflag >> BF_RBWing) & BS_DEAD;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97 //DeadCode RJS 21Feb97			lrstate -= (lcldamflag >> BF_RTWing) & BS_DEAD;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97			tstate += adptr->BOTRIGHTWING;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97			tstate += adptr->TOPRIGHTWING;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97 //DeadCode RJS 21Feb97			tstate += (lcldamflag >> BF_RBWing) & BS_DEAD;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97 //DeadCode RJS 21Feb97			tstate += (lcldamflag >> BF_RTWing) & BS_DEAD;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			//if lrstate>0 dammage to the left of the a/c is
//DeadCode DAW 03Sep98			//more severe than the dammage to the right
//DeadCode DAW 03Sep98			//this means more lift on the right and so
//DeadCode DAW 03Sep98			//the aircraft spirals anti-clockwise
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			//also, -6 <= lrstate <= +6
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			//and, 0 <= tstate <= 12
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			//Use lrstate to modify roll
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			// Scale down from 512 to 6 first....
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			//NOT INITIALISED!!!
//DeadCode DAW 03Sep98			lrstate /= 85;										//RJS 21Feb97
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			int	das;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			ANGLES	arse = DeathAngleStep;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			das = arse;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			ANGLES	rollanglestep = (Angles)((lrstate*das*frametime)/10);
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			roll += rollanglestep;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			_Miles.PlayLooped((FileNum) FIL_SFX_FIREBURN_LOOP, (ItemBasePtr) *this);//RJS 22Nov96
//DeadCode DAW 03Sep98		}
//DeadCode DAW 03Sep98	}

	Trans_Obj.GAndFriction((mobileitem* )this,OrdinaryDrag);

	groundheight = Trans_Obj.GetGroundLevel(*this);						//RJS 14Apr99
	if (World.Y<=groundheight)
	{
		World.Y = groundheight;
		Trans_Obj.LandedEffect(*this,_Collide.NOSE_TOUCH);
	}
	else
	{
		SWord	lstate,rstate;	
		UWord	rollstep = ANGLES_5Deg;

		if (SHAPESTUFF.GetShapePtr(this->shape)->AnimDataSize == AIRCRAFTANIM)
		{
			AircraftAnimData*	adptr = (AircraftAnimData *)Anim;

			lstate = adptr->LEFTWINGIN;
			rstate = adptr->RIGHTWINGIN;
		}
		else
		{
			SimpleAircraftAnimData*	adptr = (SimpleAircraftAnimData *)Anim;

			lstate = adptr->LEFTWINGIN;
			rstate = adptr->RIGHTWINGIN;
		}

		if (lstate > rstate)
			rollstep = (rollstep * lstate)/BS_DEAD;
		else
			rollstep = (-rollstep * rstate)/BS_DEAD;

		roll = (Angles) (roll + rollstep);

		_Miles.PlayLooped((FileNum) FIL_SFX_FIREBURN_LOOP, (ItemBasePtr) *this);//RJS 22Nov96
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
//	Common transient move code
//
/////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GAndFriction
//Author		Paul.
//Date			Mon 29 Apr 1996
//				//RDH 23Jul96 modified drag
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::GAndFriction(mobileitem* itm,SWord dragfactor,SWord dragfacy)
{
//DEADCODE CSB 09/11/99 	SWord	frametime;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	frametime = Timer_Code.FRAMETIME;							//DAW 31Jul96
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	//Vertical velocity first
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	SLong	testvel;
//DEADCODE CSB 09/11/99 	SLong	testvely;											//RJS 04Jul96
//DEADCODE CSB 09/11/99 	SLong	fractionpoo = (itm->timeofday<<1)&127;		//RJS 03Jun97
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	SLong	deltax, deltay;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	testvel = itm->vel_y;
//DEADCODE CSB 09/11/99 //rdh	testvel -= 2;	//(frametime * TenMetresPerSec)/100;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 //vel units are mm/cs
//DEADCODE CSB 09/11/99 //frametime is in cs
//DEADCODE CSB 09/11/99 // g = 10m/s/s = 10 * 1000 / (100 * 100) mm/cs/cs = 1 mm/cs/cs
//DEADCODE CSB 09/11/99 // delta vel = frame time in cs * g
//DEADCODE CSB 09/11/99 	testvel -= frametime * 1000; //CSB 09/11/99
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	if (testvel>TerminalVelocity)
//DEADCODE CSB 09/11/99 		itm->vel_y=TerminalVelocity;
//DEADCODE CSB 09/11/99 	else
//DEADCODE CSB 09/11/99 		itm->vel_y = (SWord )testvel;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	//Calculate new horizontal velocity using v = kut
//DEADCODE CSB 09/11/99 	//where k = drag factor
//DEADCODE CSB 09/11/99 	//		t = 1 second
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 //	testvel = (itm->velhori * frametime)/0x1000;				
//DEADCODE CSB 09/11/99 //	testvely = (itm->vely * frametime)/0x90;					//RJS 07Aug96
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	testvel = (itm->velhori * frametime * dragfactor)>>12;		//RJS 22Apr99
//DEADCODE CSB 09/11/99 	testvely = (itm->vely * frametime * dragfacy)/0x90;			//RJS 22Apr99
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	deltax = (itm->velhori * (frametime<<7/10)+fractionpoo)>>7;
//DEADCODE CSB 09/11/99 	deltay = (itm->vely * (frametime<<7/10)+fractionpoo)>>7;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	itm->velhori -= testvel;									//RJS 22Apr99
//DEADCODE CSB 09/11/99 	itm->vely -= testvely;										//RJS 22Apr99


//This applies drag evenly in all directions - ie Dragfacy is not used !!!	 //CSB 09/11/99
//DEADCODE RJS 12/11/99	const FP CONST_DRAG = 1e11;												 //CSB 09/11/99
//DEADCODE RJS 12/11/99	FP temp = itm->vel_x * itm->vel_x * frametime * dragfactor / CONST_DRAG; //CSB 09/11/99
//DEADCODE RJS 12/11/99	if(itm->vel_x > 0) temp *= -1;											 //CSB 09/11/99
//DEADCODE RJS 12/11/99	itm->vel_x += temp;														 //CSB 09/11/99
//DEADCODE RJS 12/11/99																			 //CSB 09/11/99
//DEADCODE RJS 12/11/99	temp = itm->vel_y * itm->vel_y * frametime * dragfactor / CONST_DRAG;	 //CSB 09/11/99
//DEADCODE RJS 12/11/99	if(itm->vel_y > 0) temp *= -1;											 //CSB 09/11/99
//DEADCODE RJS 12/11/99	itm->vel_y += temp - 1000 * frametime;	//Gravity						 //CSB 09/11/99
//DEADCODE RJS 12/11/99																			 //CSB 09/11/99
//DEADCODE RJS 12/11/99	temp = itm->vel_z * itm->vel_z * frametime * dragfactor / CONST_DRAG;	 //CSB 09/11/99
//DEADCODE RJS 12/11/99	if(itm->vel_z > 0) temp *= -1;											 //CSB 09/11/99
//DEADCODE RJS 12/11/99	itm->vel_z += temp;														 //CSB 09/11/99

	if (dragfactor)
	{
		Float	vx = Float(itm->vel_x);									//RJS 12Nov99
		Float	vy = Float(itm->vel_y);
		Float	vz = Float(itm->vel_z);
		Float	temp;
		Float	frametime = Float(Timer_Code.FRAMETIME);
		Float	realdrag = frametime * Float(dragfactor);

		realdrag /= 1e11;	//const_drag

		temp = vx*vx*realdrag;
		if (itm->vel_x > 0)
			temp *= -1.;

		vx += temp;

//!! We need to include y drag here for things like parachutes... !!
		temp = vy*vy*realdrag;
		if (itm->vel_y > 0)
			temp *= -1.;

		vy += temp - (1000.0 * frametime);	//delta - gravity

		temp = vz*vz*realdrag;
		if (itm->vel_z > 0)
			temp *= -1.;

		vz += temp;

		itm->vel_x = vx;	//compiler auto-casts to long...
		itm->vel_y = vy;
		itm->vel_z = vz;											//RJS 12Nov99

//Update itm->vel??

	}
	else
		itm->vel_y -= (1000 * Timer_Code.FRAMETIME);

	ApplyVelocities(itm);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GAndFrictionFixedPitch
//Author		Robert Slater
//Date			Fri 29 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::GAndFrictionFixedPitch(mobileitem* itm,SWord dragfactor,SWord dragfacy)
{
//DeadCode RJS 12Nov99 	ApplyVelocities(itm);
//DeadCode RJS 12Nov99 
//DeadCode RJS 12Nov99 //DIRTY FIX !!! //CSB 09/11/99
//DeadCode RJS 12Nov99 
//DEADCODE CSB 09/11/99 	SWord	frametime = Timer_Code.FRAMETIME;			
//DEADCODE CSB 09/11/99 	SLong	testvel;
//DEADCODE CSB 09/11/99 	SLong	testvely;											
//DEADCODE CSB 09/11/99 	SLong	fractionpoo = (itm->timeofday<<1)&127;	
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	SLong	deltax, deltay;
//DEADCODE CSB 09/11/99 	SWord	sin_ang,cos_ang;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	testvel = itm->vely;
//DEADCODE CSB 09/11/99 	testvel -= 2;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	if (testvel>TerminalVelocity)
//DEADCODE CSB 09/11/99 		itm->vely=TerminalVelocity;
//DEADCODE CSB 09/11/99 	else
//DEADCODE CSB 09/11/99 		itm->vely = (SWord )testvel;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	//Calculate new horizontal velocity using v = kut
//DEADCODE CSB 09/11/99 	//where k = drag factor
//DEADCODE CSB 09/11/99 	//		t = 1 second
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	testvel = (itm->velhori * frametime)>>12;	
//DEADCODE CSB 09/11/99 	testvely = (itm->vely * frametime)/0x90;				
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	deltax = (itm->velhori * (frametime<<7/10)+fractionpoo)>>7;
//DEADCODE CSB 09/11/99 	deltay = (itm->vely * (frametime<<7/10)+fractionpoo)>>7;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	if (dragfactor)
//DEADCODE CSB 09/11/99 		itm->velhori -= (dragfactor*testvel);		
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	if (dragfacy)
//DEADCODE CSB 09/11/99 		itm->vely -= (dragfacy*testvely);
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	itm->World.Y += (itm->vely * frametime)/10;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	testvel = (frametime * itm->velhori)/10;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	if (testvel>TerminalVelocity)	testvel = TerminalVelocity;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	Math_Lib.high_sin_cos((ANGLES )itm->hdg,sin_ang,cos_ang);
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	itm->World.X += (testvel*sin_ang)/ANGLES_FRACT;
//DEADCODE CSB 09/11/99 	itm->World.Z += (testvel*cos_ang)/ANGLES_FRACT;
//DEADCODE CSB 09/11/99 	itm->uniqueID.changed = TRUE;

	SLong ftime = Timer_Code.FRAMETIME;							//RJS 12Nov99
	if (dragfactor)
	{
		Float	vx = Float(itm->vel_x);							//RJS 12Nov99
		Float	vy = Float(itm->vel_y);							//RJS 12Nov99
		Float	vz = Float(itm->vel_z);							//RJS 12Nov99
		Float	temp;											//RJS 12Nov99
		Float	frametime = Float(ftime);						//RJS 12Nov99
		Float	realdrag = frametime * Float(dragfactor);		//RJS 12Nov99
																//RJS 12Nov99
		realdrag /= 1e11;	//const_drag						//RJS 12Nov99
																//RJS 12Nov99
		temp = vx*vx*realdrag;									//RJS 12Nov99
		if (itm->vel_x > 0)										//RJS 12Nov99
			temp *= -1.;										//RJS 12Nov99
																//RJS 12Nov99
		vx += temp;												//RJS 12Nov99

//!! We need to include y drag here for things like parachutes... !!
		temp = vy*vy*realdrag;									//RJS 12Nov99
		if (itm->vel_y > 0)										//RJS 12Nov99
			temp *= -1.;										//RJS 12Nov99
																//RJS 12Nov99
		vy += temp - (1000.0 * frametime);						//RJS 12Nov99
																//RJS 12Nov99
		temp = vz*vz*realdrag;									//RJS 12Nov99
		if (itm->vel_z > 0)										//RJS 12Nov99
			temp *= -1.;										//RJS 12Nov99
																//RJS 12Nov99
		vz += temp;												//RJS 12Nov99
																//RJS 12Nov99
		itm->vel_x = vx;	//compiler auto-casts to long...	//RJS 12Nov99
		itm->vel_y = vy;										//RJS 12Nov99
		itm->vel_z = vz;										//RJS 12Nov99

		frametime *= 0.0001;
		vx *= frametime;
		vy *= frametime;
		vz *= frametime;

		itm->World.X += vx;										//RJS 23Dec99
		itm->World.Y += vy;										//RJS 23Dec99
		itm->World.Z += vz;										//RJS 23Dec99
	}
	else
	{
		// Just apply gravity friend...
		itm->vel_y -= (1000 * ftime);
		itm->World.X += (itm->vel_x * ftime) / 10000;			//RJS 23Dec99
		itm->World.Y += (itm->vel_y * ftime) / 10000;			//RJS 23Dec99
		itm->World.Z += (itm->vel_z * ftime) / 10000;			//RJS 23Dec99
	}
																//RJS 12Nov99
#ifdef	_AUTOHDG_												//RJS 24Nov99
	//This shouldn't need to be done every frame...				//RJS 12Nov99
	itm->hdg   = Math_Lib.arctan(itm->vel_z, itm->vel_x);		//RJS 12Nov99
#endif
}															

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NoGravityAndFriction
//Author		Robert Slater
//Date			Thu 18 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::NoGravityAndFriction(mobileitem* itm,SWord dragfactor)
{
//DIRTY FIX !!! //CSB 09/11/99
	
//DEADCODE CSB 09/11/99 	SWord	frametime = Timer_Code.FRAMETIME;			
//DEADCODE CSB 09/11/99 	SLong	testvel = (itm->velhori * frametime)>>12;					
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	if (dragfactor)
//DEADCODE CSB 09/11/99 		itm->velhori -= (dragfactor*testvel);	

	ApplyVelocities(itm);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddWindDrift
//Author		Robert Slater
//Date			Tue 7 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::AddWindDrift(item* itm)
{
//rdh need to change to MiG Alley wind

//	temp = frametime * MMC.wind.speed;
//	temp /= 10;
//
//	Math_Lib.high_sin_cos((ANGLES )MMC.wind.direction,sin_ang,cos_ang);
//
//	itm->World.X += (temp*sin_ang)/ANGLES_FRACT;
//	itm->World.Z += (temp*cos_ang)/ANGLES_FRACT;

	SLong	height = itm->World.Y;
	SLong	vx, vy, vz;

	if (MissManCampSky().GetWind(height,vx,vy,vz))	//RJS 02Nov98
	{
		itm->World.X += vx * Timer_Code.FRAMETIME / 10000;	//RJS 30Apr99 //CB 18/11/99
//???		itm->World.Y += vy * Timer_Code.FRAMETIME / 10000;	//RJS 30Apr99 //CB 18/11/99
		itm->World.Z += vz * Timer_Code.FRAMETIME / 10000;	//RJS 30Apr99 //CB 18/11/99
	}

	itm->uniqueID.changed = TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ApplyVelocities
//Author		Paul.
//Date			Mon 29 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::ApplyVelocities_HdgPitch(mobileitem* itm)
{
//DIRTY FIX !!!	I don't like using this FSqrt here !! //CSB 09/11/99
	SWord frametime = Timer_Code.FRAMETIME;									 //CSB 09/11/99
																			 //CSB 09/11/99
	itm->World.X += (itm->vel_x * frametime) / 10000;						 //CSB 09/11/99
	itm->World.Y += (itm->vel_y * frametime) / 10000;						 //CSB 09/11/99
	itm->World.Z += (itm->vel_z * frametime) / 10000;						 //CSB 09/11/99
																			 //CSB 09/11/99
#ifdef	_AUTOHDG_												//RJS 24Nov99
	//This shouldn't need to be done every frame...
	itm->hdg   = Math_Lib.arctan(itm->vel_x, itm->vel_z);		//RJS 12Nov99
#endif

#ifdef	_AUTOPITCH_												//RJS 24Nov99
	Float	vx = Float(itm->vel_x);								//RJS 12Nov99
	Float	vz = Float(itm->vel_z);

	vx*=vx;
	vz*=vz;

	SLong	velhori = FSqrt(vx+vz);

	itm->pitch = Math_Lib.arctan(itm->vel_y, velhori);						 //CSB 09/11/99
																			 //CSB 09/11/99
#endif
	itm->uniqueID.changed = TRUE;											 //CSB 09/11/99
	
	
//DEADCODE CSB 09/11/99 	SWord	frametime;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	frametime = Timer_Code.FRAMETIME;							//DAW 31Jul96
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	itm->pitch = Math_Lib.arctan(itm->vely,itm->velhori);
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	itm->World.Y += (itm->vely * frametime)/10;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	SLong	temp;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	temp = (frametime * itm->velhori)/10;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	if (temp>TerminalVelocity)	temp = TerminalVelocity;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	SWord	sin_ang,cos_ang;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	Math_Lib.high_sin_cos((ANGLES )itm->hdg,sin_ang,cos_ang);
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	itm->World.X += (temp*sin_ang)/ANGLES_FRACT;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	itm->World.Z += (temp*cos_ang)/ANGLES_FRACT;
//DEADCODE CSB 09/11/99 
//DEADCODE CSB 09/11/99 	itm->uniqueID.changed = TRUE;

}

void TransObj::ApplyVelocities(mobileitem* itm)
{
	SWord frametime = Timer_Code.FRAMETIME;									 //CSB 09/11/99
																			 //CSB 09/11/99
	itm->World.X += (itm->vel_x * frametime) / 10000;						 //CSB 09/11/99
	itm->World.Y += (itm->vel_y * frametime) / 10000;						 //CSB 09/11/99
	itm->World.Z += (itm->vel_z * frametime) / 10000;						 //CSB 09/11/99

#ifdef	_AUTOPITCH_												//RJS 24Nov99
	Float	vx = Float(itm->vel_x);											//RJS 12Nov99
	Float	vz = Float(itm->vel_z);

	vx*=vx;
	vz*=vz;

	SLong	velhori = FSqrt(vx+vz);

	itm->pitch = Math_Lib.arctan(itm->vel_y, velhori);						 //CSB 09/11/99
#endif															//RJS 24Nov99
	itm->uniqueID.changed = TRUE;
}

/////////////////////////////////////////////////////////////////////////////////
//
//				Item collision with missile code.
//
/////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MissileHitSomething
//Author		Paul.
//Date			Mon 29 Apr 1996
//
//Description
//	
//	NB. All the special effects and damage are taken care of externally RJS 27Feb98
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MissileHitSomething(	itemptr			hititem,
									TransientItemPtr	missile,
									WorldStuff&			world,
									SByte				groupindex)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GeneralAircraftDammage
//Author		Paul.
//Date			Thu 18 Apr 1996
//
//Description	Adds some RANDOM dammage to an aircraft
//
//Inputs		
//
//Returns		TRUE if item is dead,
//				FALSE otherwise
//
//------------------------------------------------------------------------------
MATHABLE(BitStates);
void TransObj::GeneralAircraftDammage(AirStruc* ac,
										WorldStuff& worldptr,
										Bool	blowup,
										itemptr	hitter)
{

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DirectAircraftDamage
//Author		ajhfkjfhskdfh
//Date			Tue 8 Oct 1996
//
//Description	Comms set Aircarft Damage
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::DirectAircraftDamage(AirStruc* ac,WorldStuff& worldptr, BitStates state, BitFlags whichbit)
{
//DeadCode RJS 7Jun00 	SLong		temp;
//DeadCode RJS 7Jun00 	Bool		noanim;
//DeadCode RJS 7Jun00 
//DeadCode RJS 7Jun00 	AircraftAnimData* adptr;
//DeadCode RJS 7Jun00 	
//DeadCode RJS 7Jun00 	adptr = (AircraftAnimData* )ac->Anim;
//DeadCode RJS 7Jun00 
//DeadCode RJS 7Jun00 	if (whichbit < BF_Pilot)
//DeadCode RJS 7Jun00 		noanim = FALSE;
//DeadCode RJS 7Jun00 	else
//DeadCode RJS 7Jun00 		noanim = TRUE;
//DeadCode RJS 7Jun00 
//DeadCode RJS 7Jun00 	if (state!=BS_DEAD)
//DeadCode RJS 7Jun00 	{
//DeadCode RJS 7Jun00 		state++;
//DeadCode RJS 7Jun00 		AcDamageEffects(ac,whichbit,state,worldptr);//RJS 08Aug96
//DeadCode RJS 7Jun00 		SetAircraftDammage(ac,worldptr,whichbit,state,noanim,FALSE,FALSE,FALSE);
//DeadCode RJS 7Jun00 
//DeadCode RJS 7Jun00 		if (state == BS_DEAD)									//RJS 06Sep96
//DeadCode RJS 7Jun00 		{
//DeadCode RJS 7Jun00 			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(ac->shape);
//DeadCode RJS 7Jun00 			ac->Status.deadtime = sdptr->DeadTime;
//DeadCode RJS 7Jun00 			ac->Status.deadscale = sdptr->DeadScale;
//DeadCode RJS 7Jun00 //DeadCode JIM 22Apr97			ac->uniqueID.deaded = TRUE;
//DeadCode RJS 7Jun00 			ac->BreakForm();
//DeadCode RJS 7Jun00 //			if (ac == Manual_Pilot.ControlledAC2)
//DeadCode RJS 7Jun00 //				_Miles.SequenceAudible(FIL_MUSIC_SPIRALLING);
//DeadCode RJS 7Jun00 		}
//DeadCode RJS 7Jun00 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetAircraftDammage
//Author		Paul.
//Date			Thu 18 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::SetAircraftDammage(	AirStruc*	ac,
									WorldStuff& worldptr,
									BitFlags	whichbit,	
									BitStates	whatstate,
									Bool		noanim,
									Bool		nomovecode,
									Bool		blowup,
									Bool		sendpacket)

{
}





//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AcDamageEffects
//Author		Robert Slater
//Date			Fri 2 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::AcDamageEffects(AirStruc*	ac, BitFlags	whichbit, BitStates	whatstate,WorldStuff&	worldptr)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillLauncher
//Author		Paul.
//Date			Wed 1 May 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::KillLauncher(itemptr launcher,ItemPtr killer,WorldStuff& world,SByte	gindex,Coords3D*	hitcoords,Bool	airtoair)//JIM 11Mar99
{
	//Brought back from the dead.....
	if (launcher->Status.size==AirStrucSize)
	{
		AirStrucPtr	ac = (AirStrucPtr) launcher;
		if (!ac->fly.numinsag && (gindex==-1))						//RJS 6Sep00
		{
			if (ac == Persons2::PlayerSeenAC)						//RJS 30Aug00
				_Miles.StopEngine();								//RJS 30Aug00

//DeadCode AMM 23Oct00 			if (!_DPlay.Implemented)								//AMM 31Mar99
//DeadCode AMM 23Oct00 				SHAPE.DetatchAllVapourStreams(ac);
			Squad_Diary.SetKilledAC(ac,ac->Anim);						//RJS 21Sep00

			if (Manual_Pilot.DeathSequenceOverride(ac,AUTO_SPIRAL2GROUND)==TRUE)
			{
//DeadCode AMM 23Oct00  				if (!_DPlay.Implemented)							//AMM 31Mar99
//DeadCode AMM 23Oct00 					ExplodeAC(ac,killer,world);						//JIM 11Mar99

				if (_DPlay.Implemented || _Replay.Record)
				{
				// Send ac_collision packet....

// I think we need to send packets for other ac because otherwise in playback
// they will not explode because they will not collide with player in playback
// but only if players ac is involved in collision

//DeadCode AMM 23Oct00 					if (ac==Persons2::PlayerSeenAC)						//AMM 16Oct00
					if (launcher==Persons2::PlayerSeenAC || killer==Persons2::PlayerSeenAC)
					{
						_DPlay.NewKillLauncher(ac->uniqueID.count);
					}
				}
				else
				{
					SHAPE.DetatchAllVapourStreams(ac);
					ExplodeAC(ac,killer,world);						//JIM 11Mar99
				}
			}
			
			Squad_Diary.UpdateKilledAC();									//RJS 4Sep00
		}
		else
		{
// need this for SAGs...
			ShapeNum	shapehit = ac->shape;
//DeadCode CSB 3Nov00 			MyGroundVector	pos;
//DeadCode CSB 3Nov00 			UWord			ghdg;
//DeadCode CSB 3Nov00 			MinAnimData		*mad = (MinAnimData*) SHAPE.GetGroupItemAnimHdg(ac,shapehit,gindex,&pos,ghdg);
			animptr		adptr = ac->Anim;
			Coords3D	pos;

			SHAPE.SimpleGroupItemAnim(adptr,shapehit,gindex,pos);		//CSB 3Nov00

			Squad_Diary.SetKilledAC(ac,adptr);							//CSB 3Nov00

			Coords3D	oldPos = ac->World;
//DeadCode CSB 3Nov00 			ac->World.X = pos.gx;
//DeadCode CSB 3Nov00 			ac->World.Y = pos.gy;
//DeadCode CSB 3Nov00 			ac->World.Z = pos.gz;
			ac->World = pos;											//CSB 3Nov00

			LaunchBigExplosion(ac,world,shapehit);

			ac->World = oldPos;

			MinAnimData*	mad = (MinAnimData*)adptr;					//CSB 3Nov00
			mad->itemstate = DEAD;
			mad->IsInvisible = 1;

			Squad_Diary.UpdateKilledAC();								//RJS 6Sep00
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////
//
//							Weapons code.
//
/////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RechargeWeapons
//Author		Robert Slater
//Date			Wed 11 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ReloadWeapons(AirStrucPtr	ac)
{
	MoveGunAnimData*	adptr = (MoveGunAnimData*) ac->Anim;
	WeapAnimData*	weapon;
	int				index;

	if (ac->classtype->aerobaticfactor != AEROBATIC_LOW)
	{
// Ordinary flyable...
		weapon = adptr->weaponlaunchers;									//RJS 5Oct00
		for (index=0; index < adptr->nolaunchers; index++)					//RJS 7Jun00
		{
			if (weapon)														//RJS 7Jun00
			{
				if (weapon->LauncherType < LT_FUEL)
					weapon->LoadedStores = weapon->Stores;

				weapon++;
			}
		}
	}
	else
	{
// Bomber...
		weapon = adptr->weaponlaunchers;									//RJS 5Oct00
		for (index=0; index < adptr->nolaunchers; index++)					//RJS 7Jun00
		{
			if (	weapon
				&&	((weapon->LauncherType & LT_MASK)==LT_BULLET)	)
				weapon->LoadedStores = weapon->Stores;

			weapon++;
		}
	}

	if (ac==Persons2::PlayerSeenAC)										//RJS 10Jul00
	{																	//RJS 10Jul00
		PolyPitAnimData*	padptr = (PolyPitAnimData*)ac->Anim;		//RJS 10Jul00
																		//RJS 10Jul00
		for (index=0; index < adptr->nolaunchers; index++)				//RJS 10Jul00
			padptr->prevammo[index] = padptr->weaponlaunchers[index].LoadedStores;

		SetTotalAmmo(ac);												//RJS 5Oct00
	}

	if (!Save_Data.gamedifficulty[GD_UNLIMITEDARM])				//RJS 06May99
		SHAPE.ReloadMassAndDrag(ac);

	ClearGunFlash(ac);												//RJS 29Oct00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DumpFuel
//Author		Robert Slater
//Date			Wed 11 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	TransObj::DumpFuel(AirStrucPtr	ac, WorldStuff& world, Bool byaccident)
{
	SLong	xpos, ypos, zpos;
	AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
	WeapAnimData*	weapon;
	int	index;
	ULong	mvel;												//RJS 12Nov99
	UWord	mdelay,mburst;										//RJS 12Nov99
	int	failchance;
	Bool	alreadydumped = ac->weap.FuelDumped;				//RJS 03Jun99

	for (index=0; index < MAX_WEAP_LAUNCHERS; index++)			//RJS 15Nov99
	{
		weapon = &adptr->weaponlaunchers[index];
		if (weapon && (weapon->LauncherType == LT_FUEL))
		{
			weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_FUEL);//RJS 04Feb99
			if (weapon && weapon->LoadedStores && weapon->stationshape)		//must be external launcher
			{
				if ((ac == Persons2::PlayerSeenAC) || (ac == ac->Leader()))//RJS 04Feb99
					failchance = 0;
				else
					failchance = weapon->SubDamage * Math_Lib.rnd();
	
				if (failchance < 1048544)						//RJS 27May98
				{
					if (ac==Persons2::PlayerSeenAC)
					{
						_DPlay.NewBullet(1,index);
					}

					SHAPE.ReduceLauncherLoad(ac,index);
					ac->weap.UseIntFuel = TRUE;							//RJS 23Jun98
					ac->weap.FuelDumped = TRUE;							//RJS 23Jun98

					_Miles.PlayOnce (FIL_SFX_JETTISON_FUEL, (ItemBasePtr) ac,96);
					LaunchWeapon(false,ac,weapon,index,xpos,ypos,zpos,world,mvel,TRUE);//RJS 15Nov99
					weapon->LoadedStores = 0;										//RDH 03Aug98
				}
				else
				{
					if (!byaccident && ac->PlayerInGroup())
					{
						{}//DEADCODE RDH 07/12/99 						_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_HUNGTANK, MSG_STATUSRESPONSE_X, ac, ac, ac->GroupLeader()));
						{}//DEADCODE RDH 07/12/99 						_Radio.TriggerMsg(MESSAGE_STRUC (OLDSCRIPT_CALLEE_HUNGTANKREPLY, MSG_STATUSRESPONSEREPLY_DELAY_LP_RPT, ac->GroupLeader(), ac, ac));//RDH 18May99
						ac->/*FormationItem::*/BreakForm();		//GO HOME	//CSB 23/05/99	 //JIM 09/09/99
//DeadCode RJS 05Nov99 						ac->FormationItem::BreakForm();		//GO HOME	//CSB 23/05/99	
						ac->waypoint = NULL;							//CSB 23/05/99	
						ac->movecode = AUTO_FOLLOWWP;					//CSB 23/05/99	
						ac->information = IF_OUT_POS;					//CSB 22Aug00
						ac->manoeuvretime = 0;
					}
				}
			}
		}
	}

	return(alreadydumped);										//RJS 03Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DumpWeapons
//Author		Robert Slater
//Date			Wed 11 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::DumpWeapons(AirStrucPtr	ac, WorldStuff& world)
{
	if (ac->fly.numinsag || (ac==Persons2::PlayerGhostAC))				//RJS 23Oct00
		return;															//RJS 23Oct00

	if (	!Save_Data.gamedifficulty[GD_UNLIMITEDARM]
		||	(ac != Persons2::PlayerSeenAC)	)
	{
		SLong	xpos, ypos, zpos;
		AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
		WeapAnimData*	weapon;
		int	index;
		ULong	mvel;											//RJS 12Nov99
		UWord	mdelay,mburst;									//RJS 12Nov99
		int		failchance;
		SLong	noLaunchers = adptr->nolaunchers;				//RJS 15Nov99

		// Dump rockets.....
		for (index=0; index < noLaunchers; index++)				//RJS 15Nov99
		{
			weapon = &adptr->weaponlaunchers[index];
			if (weapon)
			{
				if ((weapon->LauncherType & LT_MASK) == LT_ROCKET)
				{
					failchance = weapon->SubDamage * Math_Lib.rnd();
					if (failchance < 1048544)
					{
						weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_ROCKET);//RDH 31Jul98
						if (weapon && weapon->LoadedStores)
						{
							if (ac==Persons2::PlayerSeenAC)		//AMM 21Apr99
							{									//AMM 21Apr99
								_DPlay.NewBullet(1,index);		//AMM 21Apr99
							}									//AMM 21Apr99

							_Miles.PlayOnce (FIL_SFX_JETTISON_FUEL, (ItemBasePtr) ac,96);

							SHAPE.ReduceLauncherLoad(ac,index,weapon->LoadedStores);
							while (weapon->LoadedStores)
							{
								LaunchWeapon(false,ac,weapon,index,xpos,ypos,zpos,world,mvel,mdelay,TRUE);//RJS 15Nov99
								
								weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_ROCKET);
								if (!weapon)
									break;
							}
							ac->weap.StoresDumped = TRUE;
						}
					}
				}
			}
		}

		// Dump bombs.....
		for (index=0; index < noLaunchers; index++)
		{
			weapon = &adptr->weaponlaunchers[index];
			if (weapon)
			{
				if ((weapon->LauncherType & LT_MASK) == LT_BOMB)
				{
					failchance = weapon->SubDamage * Math_Lib.rnd();
					if (failchance < 1048544)
					{
						weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BOMB);//RDH 31Jul98
						if (weapon && weapon->LoadedStores)
						{
							if (ac==Persons2::PlayerSeenAC)		//AMM 21Apr99
							{									//AMM 21Apr99
								_DPlay.NewBullet(1,index);		//AMM 21Apr99
							}									//AMM 21Apr99

							_Miles.PlayOnce (FIL_SFX_JETTISON_FUEL, (ItemBasePtr) ac,96);

							SHAPE.ReduceLauncherLoad(ac,index,weapon->LoadedStores);
							while (weapon->LoadedStores)
							{
								LaunchWeapon(false,ac,weapon,index,xpos,ypos,zpos,world,mvel,mdelay,TRUE);//RJS 15Nov99
							}
						}
					}
				}
			}
		}

		// Dump napalm.....
		for (index=0; index < noLaunchers; index++)
		{
			weapon = &adptr->weaponlaunchers[index];
			if (weapon)
			{
				if ((weapon->LauncherType & LT_MASK) == LT_NAPALM)
				{
					failchance = weapon->SubDamage * Math_Lib.rnd();
					if (failchance < 1048544)
					{
						weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_NAPALM);//RDH 31Jul98
						if (weapon && weapon->LoadedStores)
						{
							if (ac==Persons2::PlayerSeenAC)		//AMM 21Apr99
							{									//AMM 21Apr99
								_DPlay.NewBullet(1,index);		//AMM 21Apr99
							}									//AMM 21Apr99

							_Miles.PlayOnce (FIL_SFX_JETTISON_FUEL, (ItemBasePtr) ac,96);

							SHAPE.ReduceLauncherLoad(ac,index,weapon->LoadedStores);
							while (weapon->LoadedStores)
							{
								LaunchWeapon(false,ac,weapon,index,xpos,ypos,zpos,world,mvel,mdelay,TRUE);
							}
						}
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReActivateStation
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
SLong	TransObj::ReActivateStation(AirStrucPtr	ac, ULong &muzVel, UWord &ammotot, UWord	&muzdelay, SWord& ammoGone, SWord& cannonGone, WorldStuff& world, Bool isUnarmed)//RJS 16Sep98
{
	SLong	retval=-1;													//RJS 08Dec99	//MS 7Jul00

	ammoGone = cannonGone = 0;											//RJS 17Oct00
	if (ac->weap.weapontype != MINWEAP)
	{
		LnchrType			currentweapon;
		SLong				xpos, ypos, zpos;							
		SLong				usexpos, useypos, usezpos;							
		WeapAnimData*		weapon;
		WeapAnimData*		useweapon;
		AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
		SLong				currindex = adptr->currweapindex;
		SLong				index = -1;								//RJS 16Sep98
//DeadCode RJS 08Dec99	SLong				retval;									//RJS 16Sep98
		SLong				highestammo = 0;
		ULong				mvel;										//RJS 12Nov99
		UWord				mdelay,mburst;						//RDH 31Jul98
		SWord				foundWeap,noAmmo;

		foundWeap = noAmmo = 0;										//RJS 25Jan99
		ammotot = 0;												//RJS 09Sep98
		muzdelay = 5;												//RJS 23Jul98
		muzVel = 0;													//RJS 16Sep98
		useweapon = NULL;
		currentweapon = (LnchrType) (ac->weap.weapontype & LT_MASK);
		if (currentweapon == LT_ANYWEAPON)							//RJS 08Dec99
		{
			if (ac->weap.weapontype == SByte(LT_AWBULLET))
			{
				currentweapon = LT_BULLET;
				ac->weap.weapontype = LT_AWCANNON;
			}
			else
			{
				currentweapon = LT_CANNON;
				ac->weap.weapontype = LT_AWBULLET;
			}
		}

		index = 0;
		while (index < adptr->nolaunchers)							//RJS 15Nov99
		{
			weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,mdelay,mburst,currentweapon);//RDH 31Jul98
			if (weapon)
			{
				foundWeap++;
				ammotot += weapon->LoadedStores;
				if (weapon->LoadedStores > highestammo)	
				{
					highestammo = weapon->LoadedStores;
					useweapon = weapon;
					usexpos = xpos;
					useypos = ypos;
					usezpos = zpos;
					currindex = index;
					muzdelay = mdelay;
					muzVel = mvel;//RJS 16Sep98
				}
				else
					noAmmo++;
			}
			index++;
		}

		if (useweapon)
		{
			if (ac==Persons2::PlayerSeenAC)
			{
				_DPlay.NewBullet(1,currindex);
				if (!_Replay.Record && Save_Data.gamedifficulty[GD_GUNCAMERAONTRIGGER])//AMM 23Apr99
				{													//AMM 23Apr99
	// if next frame we are going to start a record, then first frame will be this
	// weapon launch that initiated it

					_Replay.DelayedWeapon=currindex;				//AMM 23Apr99
				}													//AMM 23Apr99

				//If you're on the ground, no damage.
	//			if (ac->fly.pModel->GearTouched)					//RJS 10Jun99
	//				isUnarmed = TRUE;								//RJS 10Jun99		
			}

	//DeadRJS		ammotot -= 1;											//RJS 09Sep98

			retval = currindex;										//RJS 16Sep98
			ammoGone = LaunchWeapon(false,ac,useweapon,currindex,usexpos,useypos,usezpos,world,muzVel,muzdelay,isUnarmed);	//RJS 10Jul00
			ammotot -= ammoGone;		

			if (currentweapon == LT_CANNON)								//RJS 17Oct00
				cannonGone = ammoGone;									//RJS 17Oct00
		}
		else
		{
			retval = -1;											//RJS 16Sep98
			if (	(noAmmo == foundWeap)
				&&	Save_Data.gamedifficulty[GD_UNLIMITEDARM]	)
//DeadCode RJS 6Oct00 				&&	ac->classtype->aerobaticfactor != AEROBATIC_LOW		)	//RJS 13Jul00
			{
				//Reload...
				if (!(_DPlay.Implemented && ac->weap.weapontype==LT_BOMB))
				{
					ReloadWeapons(ac);
				}
			}
		}

		adptr->currweapindex = currindex;
	}
	else
	{
// Master arm is off...
		retval = -1;
//DeadCode RJS 23Oct00 		_DamageChat.SayWeapon(ac->weap.weapontype);
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WeaponSearch
//Author		Robert Slater
//Date			Tue 10 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::WeaponSearch(AirStrucPtr	ac, WeapSearchType	direction, Bool wrap)
{
	WeapAnimData*	weapon;
	SLong			index, currtype, nextval, thisval;
	SLongP			botptr,topptr;
	AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
	Bool			isOk = FALSE;
	bool			candisarm = false;
	SLong			defaultweap;

	currtype = MINWEAP;											//RJS 08Dec99
	if (direction == Go_Instant)
	{
		currtype = ac->weap.weapontype - 1;
		nextval = ac->weap.weapontype + 1;

		botptr = &currtype;
		topptr = &nextval;
	}
	else
	{
		candisarm = true;
		if (ac->weap.weapontype != MINWEAP)
			currtype = UByte(ac->weap.weapontype);

		if (direction == Go_Forward)
		{
			botptr = &currtype;
			topptr = &nextval;
			nextval = MAXWEAP;									//RJS 07Dec99

			defaultweap = LT_ANYWEAPON;
		}
		else
		{
			botptr = &nextval;
			topptr = &currtype;
			nextval = MINWEAP;									//RJS 07Dec99

			defaultweap = MINWEAP;
		}
	}

	for (index=0; index < MAX_WEAP_LAUNCHERS; index++)			//RJS 15Nov99
	{
		weapon = &adptr->weaponlaunchers[index];
		if (weapon)
		{
			thisval = weapon->LauncherType;
			if (thisval < MAXWEAP)								//RJS 07Dec99
			{
				if (	(thisval > *botptr)
					&&	(thisval < *topptr)	)
					nextval = thisval;
			}
		}
	}

	if (	(nextval > MINWEAP)									//RJS 07Dec99
		&&	(nextval < MAXWEAP)	)								//RJS 07Dec99
		isOk = TRUE;											//RJS 13May99
	else														//RJS 13May99
	{															//RJS 13May99
		if (candisarm)
		{
// Master arm off, or both...
			if (!wrap)
			{
				if (	((currtype & LT_MASK) > LT_BULLET)	// can we possibly have cannons?
					||	(defaultweap==MINWEAP)	)
				{
					isOk = TRUE;										//RJS 08Dec99
					nextval = defaultweap;
				}
			}
			else
			{
				if (	(	((currtype & LT_MASK) > LT_BULLET)	// can we possibly have cannons?
						 &&	(currtype != defaultweap)	)
					||	(defaultweap==MINWEAP)	)
				{
					isOk = TRUE;										//RJS 08Dec99
					nextval = defaultweap;
				}
				else
				{
					if (defaultweap!=MINWEAP)
					{
						int		minVal = LT_MASK;
						
						isOk = TRUE;
						nextval = MINWEAP;

						weapon = adptr->weaponlaunchers;
						for (index=0; index < adptr->nolaunchers; index++)
						{
							if (weapon->LauncherType < minVal)
								minVal = weapon->LauncherType;

							weapon++;
						}

						if (minVal != LT_MASK)
							nextval = minVal;
					}
				}
			}
		}
		else
		{
			if (wrap)												//RJS 13May99
			{														//RJS 13May99
				isOk = TRUE;										//RJS 13May99
				nextval = adptr->weaponlaunchers[0].LauncherType;	//RJS 13May99
			}														//RJS 13May99
		}
	}															//RJS 13May99

	if (isOk)													//RJS 13May99
	{
		ac->weap.weapontype = nextval;

		if (ac == Manual_Pilot.ControlledAC2)					//RJS 09Sep98
		{
			PolyPitAnimData*	ppitanim = (PolyPitAnimData*) adptr;
			UWord				ammoleft = 0;

			// Another search, for rounds total...
			for (index=0; index < MAX_WEAP_LAUNCHERS; index++)	//RJS 07Dec99
			{
				weapon = &adptr->weaponlaunchers[index];
				if (weapon && (weapon->LauncherType == nextval))
					ammoleft += weapon->LoadedStores;
			}

			ppitanim->acgunammoleft = ammoleft;						//RJS 24Nov99
			ppitanim->acprevammoleft = ammoleft;					//RJS 17Jun99

//Dead			_Miles.PlayOnce (FIL_SFX_GUN_CLICK1, (ItemBasePtr) ac,64);//RJS 13May99
			if (direction != Go_Instant)
			{
				_DamageChat.SayWeapon(nextval);
				_Miles.PlaySample(FIL_SFX_OFFICE_BUTTON3,(ItemPtr)NULL,256);
			}

			SetTotalAmmo(ac);
		}									

//DeadCode RJS 5Oct00 		ac->weap.weapontype = nextval;
	}
	else
	{
		if (ac==Manual_Pilot.ControlledAC2)
			_DamageChat.SayWeapon(ac->weap.weapontype);
	}

	ClearGunFlash(ac);
}

#ifndef	NDEBUG
static	rotitem	duff_Launcher;
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ControlKeybWeap
//Author		Paul.
//Date			Mon 29 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::ControlKeybWeap(AirStrucPtr ac,WorldStuff& world)
{
	if (	ac													//RJS 10Jun97
		&& (ac->movecode != AUTO_RESURRECT)	)					//RJS 10Jun97
	{
		WeapAnimData*	weapon;										//RJS 29Aug96
		SLong			xpos, ypos, zpos;							//RJS 29Aug96
		UByte			index;										//RJS 29Aug96
		UWord			thisstore;									//RJS 10Sep96
		SWord			frametime = Timer_Code.FRAMETIME;			//RDH 03Oct96
		PolyPitAnimData*	adptr = (PolyPitAnimData *)ac->Anim;//RJS 10Jun97
//DeadCode RJS 20Oct00 		LnchrType		currentweapon = (LnchrType)ac->weap.weapontype;	//RJS 10Jun97
		UWord			mdelay;											//RJS 23Jul98
		UWord			ammoleft;								//RJS 09Sep98

		if (adptr->itemstate >= DYING)									//CSB 30Jun00
			return;

//DeadCode RJS 03Dec98		if (fakeshootdelay <= 0)
//DeadCode RJS 03Dec98		{
//DeadCode RJS 03Dec98			// Launch fake bullet for gunsight code....
//DeadCode RJS 03Dec98
//DeadCode RJS 03Dec98			fakeshootdelay = 25;
			SHAPE.CalcRadarRange(ac);
//DeadCode MS 30Nov98			LaunchTrackedBullet(ac,world);
//DeadCode RJS 03Dec98		}
//DeadCode RJS 03Dec98		else
//DeadCode RJS 03Dec98			fakeshootdelay -= frametime;	

//DEADCODE CSB 01/11/99 		if (Key_Tests.KeyPress3d(WINGSPANUP) || Key_Tests.KeyHeld3d(WINGSPANUP))
//DEADCODE CSB 01/11/99 			SHAPE.WingSpanUp();
//DEADCODE CSB 01/11/99 
//DEADCODE CSB 01/11/99 		if (Key_Tests.KeyPress3d(WINGSPANDOWN) || Key_Tests.KeyHeld3d(WINGSPANDOWN))
//DEADCODE CSB 01/11/99 			SHAPE.WingSpanDown();
//DEADCODE CSB 01/11/99 
//DEADCODE CSB 01/11/99 		if (Key_Tests.KeyPress3d(GUNRANGEUP) || Key_Tests.KeyHeld3d(GUNRANGEUP))
//DEADCODE CSB 01/11/99 			SHAPE.GunRangeUp();
//DEADCODE CSB 01/11/99 
//DEADCODE CSB 01/11/99 		if (Key_Tests.KeyPress3d(GUNRANGEDOWN) || Key_Tests.KeyHeld3d(GUNRANGEDOWN))
//DEADCODE CSB 01/11/99 			SHAPE.GunRangeDown();


/*		if (Key_Tests.KeyPress3d(DETAILDIALS))
		{
			SHAPE.ForceDamage(Manual_Pilot.ControlledAC2,&adptr->RIGHTWINGIN,BS_DEAD);
			SHAPE.ForceDamage(Manual_Pilot.ControlledAC2,&adptr->LEFTWINGIN,BS_DEAD);
		}*/


//DeadCode RJS 23Mar99		if (Key_Tests.KeyPress3d(CANOPYEJECT))					//RJS 20Apr98
//DeadCode RJS 23Mar99			LaunchCanopyEject(ac,world);						//RJS 19Feb98

//DeadCode RJS 05May99		if (Key_Tests.KeyPress3d(EJECTPILOT))					//RJS 19Feb98
//DeadCode RJS 05May99		{
//DeadCode RJS 05May99			if (_DPlay.Implemented || _Replay.Record)			//AMM 21Apr99
//DeadCode RJS 05May99			{													//AMM 21Apr99
//DeadCode RJS 05May99				_DPlay.NewSpecial(PIDC_EJECT,0,0,0);			//AMM 21Apr99
//DeadCode RJS 05May99			}													//AMM 21Apr99
//DeadCode RJS 05May99			else												//AMM 21Apr99
//DeadCode RJS 05May99				LaunchCanopyEject(ac,world);						//RJS 19Feb98
//DeadCode RJS 05May99 //DeadCode RJS 23Mar99			LaunchParachute(ac,world);							//RJS 19Feb98
//DeadCode RJS 05May99		}

		if (Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW)
		{
			if (Key_Tests.KeyPress3d(LASTWEAPON))					
				WeaponSearch(ac,Go_Backward);

			if (Key_Tests.KeyPress3d(NEXTWEAPON))
				WeaponSearch(ac,Go_Forward);

			if (Key_Tests.KeyPress3d(CYCLETHROUGHWEAPONS))
				WeaponSearch(ac,Go_Forward,TRUE);

			if (Key_Tests.KeyPress3d(DUMPWEAPONS))
				DumpWeapons(ac,world);

#ifndef	NDEBUG													//RJS 02Feb00
			static	bool	poop = false;
			if (!Three_Dee.shapecheat)
			{
#endif
				if(Key_Tests.KeyPress3d(DROPBOMB))							//RJS 4Oct00
				{
//DeadCode AMM 11Oct00 // no bombs in deathmatch or teamplay games
// we now have bombs, cool...... BOOM

//DeadCode AMM 11Oct00 					if (!(_DPlay.Implemented && _DPlay.GameType<DPlay::COMMSQUICKMISSION))
					{
						//Stuka dive bombing system - Automatically resets trim as bomb release buytton is pressed
						if(ac->fly.pModel->BombingPhase == 1)					  //CSB 04/01/00
							ac->fly.pModel->BombingPhase = 2;					  //CSB 04/01/00

						ac->ai.ManStep = 15;								//CSB 21Aug00

						SLong	oldweaptype = ac->weap.weapontype;

						ac->weap.weapontype = LT_BOMB;

						SLong	wpindex = ActivateStation(ac,ammoleft,mdelay,world);
						if (wpindex == -1)
						{
							_Miles.PlaySample (FIL_SFX_GUN_CLICK4, (ItemBasePtr) ac,64);
						}
						else
						{
							if (_DPlay.Implemented && _DPlay.GameType<DPlay::COMMSQUICKMISSION)
							{
// set up re-arm timer for bomb in comms

								ac->ai.desiredturn=0;
							}
							adptr->lastweapindex = wpindex;	
						}

						ac->weap.weapontype = oldweaptype;
					}
				}
#ifndef	NDEBUG
			}
#endif			
		}
			
		AirStrucPtr	buddy;

//DeadCode RJS 17Oct00 		if (Key_Tests.KeyPress3d(DUMPWEAPONS) && (Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW))	//RJS 4Oct00
//DeadCode RJS 17Oct00  			DumpWeapons(ac,world);								//RDH 28Apr99

		if (	Key_Tests.KeyPress3d(RELOADWEAPON))		//RJS 11May99
		{
//DEADCODE RDH 11/05/99			&&	Save_Data.gamedifficulty[GD_RELOADARMS]	)		//RJS 25Jan99
			if (!(_DPlay.Implemented && _DPlay.GameType<DPlay::COMMSQUICKMISSION))
			{
				ReloadWeapons(ac);
			}

#ifdef	_DEADGUN_
			adptr->weaponlaunchers[1].LauncherType = LT_CONTACT;
#endif
		}

		if (Key_Tests.KeyPress3d(VOICETOGGLE))					//RJS 30Jun99
		{														//RJS 30Jun99
			if (Save_Data.gamedifficulty[GD_NOPLAYERVOICE])		//RJS 30Jun99
				Save_Data.gamedifficulty %= GD_NOPLAYERVOICE;	//RJS 30Jun99
			else												//RJS 30Jun99
				Save_Data.gamedifficulty |= GD_NOPLAYERVOICE;	//RJS 30Jun99
		}														//RJS 30Jun99

		//Cludge Yes
		KeyVal3D secondaryfirekey=SHOOT;
		if (SHAPE.UsingRearGunner() && View_Object && View_Object->InCockpit())
			secondaryfirekey=MENUSELECT;


		if (Key_Tests.KeyPress3d(SHOOT) || Key_Tests.KeyPress3d(secondaryfirekey))						//RJS 10Jun97
		{
			ClearWeaponChain(ac);								//RJS 15Nov99
			SLong	timeleft = ac->weap.ShootDelay-frametime;//RJS 10Jun97
			if (timeleft<0)
			{
				if (Save_Data.gamedifficulty[GD_GUNCAMERAONTRIGGER] && !_DPlay.Implemented && !_Replay.Record)//AMM 05Jan99
				{
					if (Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW)
					{
						_Replay.StartRecordFlag=TRUE;					//AMM 05Jan99
						_Replay.guncameradelay=BULLETDELAY;
					}
				}

				SLong	wpindex = ActivateStation(ac,ammoleft,mdelay,world);//RJS 17Jun99
				if (wpindex == -1)									//RJS 17Jun99
				{
	//				_Miles.SequenceAudible(FIL_MUSIC_GOING_BADLY);
					_Miles.PlaySample (FIL_SFX_GUN_CLICK4, (ItemBasePtr) ac,64);
					_Miles.StopShooting();							//RJS 25May99

					if (WeaponID(ac->weap.weapontype) == LT_BULLET)		//RJS 25Aug00
						adptr->gunshooting = 0;							//RJS 25Aug00
					else
						adptr->cannonshooting = 0;						//RJS 25Aug00
				}
				else
				{
// Also handle the fact that we may have two fins...
					adptr->lastweapindex = wpindex;					//RJS 17Jun99
					if (ac->classtype->aerobaticfactor == AEROBATIC_LOW)	//RJS 25Sep00
					{
						SHAPE.ShootFin(ac,&adptr->FINLEFT,false);
						SHAPE.ShootFin(ac,&adptr->FINRIGHT,true);
					}
				}

// in case bomb has dropped - want to keep bomb delay

				if (_Replay.guncameradelay<BULLETDELAY)			//RDH 30Mar99
					_Replay.guncameradelay=BULLETDELAY;			//RDH 30Mar99

//DeadCode RJS 5Oct00 				adptr->actotalammoleft = ammoleft;						//RJS 5Oct00

				adptr->acgunammoleft = ammoleft;					//RJS 24Nov99
				adptr->acprevammoleft = ammoleft;					//RJS 17Jun99
				timeleft = mdelay;									//RJS 25Jan99
			}
			ac->weap.ShootDelay = timeleft;
		}
		else
		{
//DeadCode RJS 23Jul98			if (	(	Key_Tests.KeyHeld3d(SHOOT)				//RJS 10Jun97
//DeadCode RJS 23Jul98					 && ((LT_BULLET & LT_MASK)==currentweapon))	//RJS 10Jun97
//DeadCode RJS 23Jul98				||	autobulletcount								)//RJS 10Jun97
			if (Key_Tests.KeyHeld3d(SHOOT) || Key_Tests.KeyHeld3d(secondaryfirekey))						//RJS 23Jul98
			{
				// cannot drop multiple bombs, causes cock-up
				if ((ac->weap.weapontype & LT_MASK) != LT_BOMB)						//RJS 11May99
				{
					if (Save_Data.gamedifficulty[GD_GUNCAMERAONTRIGGER] && !_DPlay.Implemented && !_Replay.Record)//AMM 05Jan99
					{
						if (Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW)
						{
							_Replay.StartRecordFlag=TRUE;					//AMM 05Jan99
						}
	//					_Replay.guncameradelay=BULLETDELAY;
					}

	// in case bomb has dropped - want to keep bomb delay

					if (_Replay.guncameradelay<BULLETDELAY)						//AMM 25Jan99
						_Replay.guncameradelay=BULLETDELAY;				//AMM 25Jan99

					//Subsequent shots

					SLong	timeleft = ac->weap.ShootDelay-frametime;//RJS 10Jun97
					if (timeleft<0)
					{
						ULong	mvel;										//RJS 12Nov99
						SWord	ammoGone;								//RJS 10Jul00
						SWord	cannonGone;

						if (ReActivateStation(ac,mvel,ammoleft,mdelay,ammoGone,cannonGone,world) == -1)												//RJS 25May99	//RJS 17Oct00
						{
							if (WeaponID(ac->weap.weapontype) == LT_BULLET)		//RJS 25Aug00
								adptr->gunshooting = 0;							//RJS 25Aug00
							else										//RJS 25Aug00
								adptr->cannonshooting = 0;						//RJS 25Aug00

							ReduceBulkStores(ac,(UByteP)adptr);				//RJS 17Jun99

							_Miles.StopShooting();							//RJS 25May99

	//						_Miles.SequenceAudible(FIL_MUSIC_GOING_BADLY);
	//						_Miles.PlaySample (FIL_SFX_GUN_CLICK4, (ItemBasePtr) ac,64);
						}
						else
						{
// Also handle the fact that we may have two fins...
							if (ac->classtype->aerobaticfactor == AEROBATIC_LOW)	//RJS 25Sep00
							{
								SHAPE.ShootFin(ac,&adptr->FINLEFT,false);
								SHAPE.ShootFin(ac,&adptr->FINRIGHT,true);
							}
						}

						adptr->actotalammoleft -= ammoGone;
						adptr->accannonammoleft -= cannonGone;			//RJS 17Oct00

						adptr->acgunammoleft = ammoleft;					//RJS 24Nov99
						timeleft = mdelay;

	//					if (autobulletcount--<0)
	//						autobulletcount=0;
					}
					ac->weap.ShootDelay = timeleft;
				}
			}
			else											//RJS 16Sep98
			{
				ReduceBulkStores(ac,(UByteP)adptr);						//RJS 17Jun99

				adptr->gunshooting = 0;							//RJS 06Jun99
				adptr->cannonshooting = 0;						//RJS 06Jun99

				_Miles.StopShooting();							//RJS 12Apr99
				ac->weap.ShootDelay = 0;						//RJS 20Apr99
				if (ac->weap.weapforce)							//RJS 20Apr98
					ac->SetWeaponForce();						//RJS 16Sep98

				if (_Replay.Record
				&& Save_Data.gamedifficulty[GD_GUNCAMERAONTRIGGER]
				&& !Save_Data.gamedifficulty[GD_GUNCAMERAATSTART])
				{
					if (!_Replay.guncameradelay--)
					{
//DeadCode AMM 02Jul99 						_Replay.clearreplaybuffers=true;
// done in stop record
//DeadCode AMM 08Jul99 						_Replay.ClearReplayBuffers();			//AMM 02Jul99
						_Replay.StopRecord(true);
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestForItem2Kill
//Author		Paul.
//Date			Fri 3 May 1996
//
//Description	Demo routine - tests for a value in uiddeathitem and
//				kills the item using the method set in deathtype
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::TestForItem2Kill(WorldStuff& world)
{
	if (uiddeathitem)
	{
		MinAnimData* adptr;

		UniqueID	tmpuid = (UniqueID )uiddeathitem;

		itemptr		tmpitem;

		mobileitem	launcher;

		tmpitem = (itemptr )MobileItem::currworld->ConvertPtrUID(tmpuid);

		adptr = (MinAnimData *)tmpitem->Anim;

		launcher.World = tmpitem->World;

		switch ((DeathType )deathtype)
		{
			case DT_BigGround:
				LaunchGroundExplosion(launcher,world);
				adptr->itemstate=DEAD;
				break;
			case DT_GroundSmoke:
				LaunchGroundExplosion(launcher,world);
				adptr->itemstate=DEAD;
				break;
			case DT_AirDelay:
				LaunchSmokeTrail((mobileitem* )tmpitem,world);
				break;
			case DT_AirInstant:
				KillLauncher((itemptr )tmpitem,tmpitem,world);	//JIM 11Mar99
				break;
		}
	}
	uiddeathitem = 0;
	deathtype = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PilotedACHit
//Author		Robert Slater
//Date			Mon 14 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::PilotedACHit()
{
	TargetSize	tsz = Save_Data.targetsize;
	Save_Data.targetsize = TS_MIN;

	if (	Save_Data.gamedifficulty[GD_COLLISIONS]				//RJS 25Jan99
		&&	!(Manual_Pilot.ControlledAC2->Status.deadtime)
		&&	(Manual_Pilot.ControlledAC2->classtype->aerobaticfactor != AEROBATIC_LOW)
		&&	(!View_Point ||!((ViewPoint*)View_Point)->Accel())
		&&	(Persons2::PlayerSeenAC->movecode != AUTO_RESURRECT)			//AMM 13Jul00
		)
	{
		BoxCol::NineSectorColThisPiloted(Manual_Pilot.ControlledAC2);//RJS 20May99
	}

	Save_Data.targetsize = tsz;									//PD 29Sep96
}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CommsACHit
//Author		Andrew McRae
//Date			Tue 8 Oct 1996
//
//Description	Comms equivalent of PilotedACHit()
//
//Inputs		Aircraft ptr and hit object.
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 28Apr99 void TransObj::CommsACHit (AirStrucPtr hititem1, itemptr hititem2)
//DeadCode AMM 28Apr99 {
//DeadCode AMM 28Apr99
//DeadCode AMM 28Apr99	WorldStuff&	world = *hititem1->currworld;
//DeadCode AMM 28Apr99
//DeadCode AMM 28Apr99	if (	(hititem1 == Manual_Pilot.ControlledAC2)
//DeadCode AMM 28Apr99		||	(hititem2 == Manual_Pilot.ControlledAC2)	)
//DeadCode AMM 28Apr99		View_Object->SetToDeathView();							//RDH 02Sep98
//DeadCode AMM 28Apr99
//DeadCode AMM 28Apr99	if (	(hititem1->shape != WRECK)
//DeadCode AMM 28Apr99		&&	(hititem1->shape != CRATER)
//DeadCode AMM 28Apr99		&&	(hititem1->shape != PDEATH)	)
//DeadCode AMM 28Apr99		 KillLauncher((itemptr)hititem1,hititem1,world);		//JIM 11Mar99
//DeadCode AMM 28Apr99
//DeadCode AMM 28Apr99	if (	(hititem2->shape != WRECK)
//DeadCode AMM 28Apr99		&&	(hititem2->shape != CRATER)
//DeadCode AMM 28Apr99		&&	(hititem2->shape != PDEATH)	)
//DeadCode AMM 28Apr99		 KillLauncher((itemptr)hititem2,hititem2,world);		//JIM 11Mar99
//DeadCode AMM 28Apr99
//DeadCode AMM 28Apr99
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98 #ifdef LOGENTRY
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98						_DPlay.LogEntry ("CommsACHit");
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98 #endif
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98	WorldStuff&	world = *Me->currworld;
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98	MinAnimData* mad =
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98		(MinAnimData* )Me->Anim;//RJS 05Sep96
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98	if (mad->itemstate != DEAD)
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98		 KillLauncher((itemptr)Me,world);//RJS 05Sep96
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98	mad = (MinAnimData* )hititem->Anim;
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98	if (mad->itemstate != DEAD)
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98		KillLauncher((itemptr)hititem,world);
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98	gindex = gindex;
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98
//DeadCode AMM 28Apr99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExecuteAnimation
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
void	TransObj::ExecuteAnimation(	ItemPtr				itm,
									UWord				hitshape,
									ItemPtr				hitter,
									HitEffectRecord&	hitstruc,
									WorldStuff&		worldptr)
{



}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExecuteAnimation
//Author		Robert Slater
//Date			Thu 27 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ExecuteAnimation(	ItemPtr		itm,
									ItemPtr		theShooter,
									UWord		hitshape,
									Coords3D	hitCoords,
									WorldStuff&	worldptr,
									SLong		val,
									SLong		randval,
									UByteP		weapptr,
									Coords3D	hitterCoords,	//RJS 02Dec98
									Coords3D	grpCoords,		//RJS 02Dec98
									SLong		damagestrength,	//RJS 07Dec98
									SByte		groupindex)
{
	DeathNum	animnum = (DeathNum) val;
	ShapeNum	shapehit = (ShapeNum)hitshape;					//RJS 16Nov98
	Coords3D	oldcoords = itm->World;
	mobileitem*		hitpositm = (mobileitem*) itm;		// Crap fix ... use hitcoords
	SLong		grounddist;
//DeadCode RJS 20Oct00 	Bool		noDirt = FALSE;

	hitpositm->World = hitCoords;								//RJS 02Dec98

	switch ((int)animnum)												//JIM 29/03/99
	{
		case ANIM_BIGEXPLOSION:
			if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
			{
				_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_GROUND+Math_Lib.rnd(5)), (ItemBasePtr) itm);//RJS 05Dec96
				LaunchExplosion(hitpositm,worldptr);
				LaunchExplodePuff(hitpositm,1000,ExplodeSmokeShape,800,worldptr);
			}
			break;
		case ANIM_SMALLEXPLOSION:
		{
			if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
			{
				ShapeNum	oldshape = hitpositm->shape;
				hitpositm->shape = shapehit;
				LaunchSparkDebris(hitpositm,worldptr);		//Temporary...
				LaunchMiniExplosion(hitpositm,worldptr);//rjs 28aug98
				hitpositm->World = grpCoords;
				LaunchScatteredFire(hitpositm,shapehit,worldptr);
				hitpositm->World = hitCoords;
				hitpositm->shape = oldshape;
			}
			else
			{
// We want the fire to be put in the list, regardless of whether it is visible or not...
				Coords3D	firepos = grpCoords;
				firepos.Y += 8000 + Math_Lib.rnd(1000);

				Land_Scape.AddSmokeCloud(firepos,128/Timer_Code.FRAMETIME);//not quite as devastating
			}
			break;
		}
		case ANIM_GROUNDDEBRIS:
			if (WithinVisibleRange(hitCoords,200000))		//RJS 11Jun99
				LaunchDirtyFingers(hitpositm,worldptr);		//RJS 11Jun99
			break;
		case ANIM_SMALLDEBRIS:
		case ANIM_SMALLSPARK:
			if (WithinVisibleRange(hitCoords,50000))		//RJS 11Jun99
				LaunchSpark(hitpositm,worldptr);			//RJS 11Jun99
			break;
		case ANIM_GROUNDRICOCHET:
			if (	WithinVisibleRange(hitCoords,20000)			 //RJS 01Jul99
				||	(theShooter == Manual_Pilot.ControlledAC2)	)//RJS 01Jul99
				LaunchRicochetSmoke(hitpositm,RicochetSmokeShape,worldptr);//RJS 26Apr99
			break;
		case ANIM_WOODRICOCHET:
			if (	WithinVisibleRange(hitCoords,20000)			 //RJS 01Jul99
				||	(theShooter == Manual_Pilot.ControlledAC2)	)//RJS 01Jul99
				LaunchRicochetSmoke(hitpositm,WSMOKE,worldptr);		//RJS 26Apr99
			break;
		case ANIM_SMALLFIRE:
			LaunchGuidedBurning(hitpositm,worldptr);		//RJS 11Jun99
			_Miles.PlaySample(FIL_SFX_WOOD_BREAK1, (ItemBasePtr) hitpositm);
			break;
		case ANIM_BIGFIRE:
			if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
				LaunchGroundExplosion(hitpositm,worldptr);	//RJS 11Jun99
			break;
		case ANIM_ATEAM:
			LaunchDelayedExplosion((mobileitem*)itm,worldptr);
			break;
		case ANIM_BIGIMPACTNODIRT:
		case ANIM_SMALLIMPACTNODIRT:
		{
			if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
			{
				UWord	oldshape = hitpositm->shape;

				hitpositm->shape = (ShapeNum) hitshape;

				_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_TANK+Math_Lib.rnd(3)), hitpositm);
				if (damagestrength > 26)
					LaunchFlash(hitpositm,0,worldptr);
				else
					LaunchSmallFlash(hitpositm,worldptr);

				hitpositm->World.X = grpCoords.X;
				hitpositm->World.Z = grpCoords.Z;

				LaunchMushroomCloud(hitpositm,damagestrength,worldptr);

				hitpositm->shape = (ShapeNum) oldshape;
			}
		}
		break;
		case ANIM_SMALLIMPACTEXPLODE:	
		{
			if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
			{
				SLong	glevel = grpCoords.Y;						//RJS 07Dec98
				UWord	oldshape = hitpositm->shape;
				ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shapehit);

				hitpositm->shape = (ShapeNum) hitshape;
				_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_TANK+Math_Lib.rnd(3)), hitpositm);
				if (damagestrength > 26)
					LaunchFlash(hitpositm,0,worldptr);
				else
					LaunchSmallFlash(hitpositm,worldptr);			//RJS 08Dec98

				hitpositm->World.X = grpCoords.X;
				hitpositm->World.Z = grpCoords.Z;
				LaunchDebris(hitpositm,DebrisDirtShape,2,(damagestrength * sdptr->Size)/100,worldptr);
				LaunchMushroomCloud(hitpositm,damagestrength,worldptr);
				LaunchExplosion(hitpositm,worldptr);				//MS 10Dec98
				hitpositm->shape = (ShapeNum) oldshape;
				grounddist = hitpositm->World.Y - glevel;
				if (grounddist < 300)		// 3 metres
				{
					hitpositm->World.Y = glevel;
					LaunchShockwave(hitpositm,worldptr);
				}
			}
		}
		break;
		case ANIM_DEFAULT:
		case ANIM_SMALLCOLLAPSE:
		{
			if (WithinVisibleRange(hitCoords,160000))		//RJS 11Jun99
			{
				hitpositm->World.Y = grpCoords.Y;
				LaunchDustRing(hitpositm,worldptr);
				LaunchGuidedFire(hitpositm,worldptr);
			}
			else
			{
// We want the fire to be put in the list, regardless of whether it is visible or not...
				Coords3D	firepos = grpCoords;
				firepos.Y += 8000 + Math_Lib.rnd(1000);

				Land_Scape.AddSmokeCloud(firepos,128/Timer_Code.FRAMETIME);	//not quite as devastating
			}
		}
		break;
		case ANIM_BIGIMPACTEXPLODE:
		{
			if (WithinVisibleRange(hitCoords,320000))		//RJS 11Jun99
			{
				SLong	glevel = grpCoords.Y;						//RJS 07Dec98

				_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_TANK+Math_Lib.rnd(3)), hitpositm);
				LaunchFlash(hitpositm,0,worldptr);
				LaunchExplosion(hitpositm,worldptr);
				LaunchDebris(hitpositm,DebrisDirtShape,2,16,worldptr);

				UWord	oldshape = hitpositm->shape;
				hitpositm->shape = shapehit;
				LaunchMushroomCloud(hitpositm,damagestrength,worldptr);
				hitpositm->shape = (ShapeNum)oldshape;

				grounddist = hitpositm->World.Y - glevel;
				if (grounddist < 300)		// 3 metres
				{
					LaunchDirtyBuildingFingers(hitpositm,Math_Lib.rnd(),worldptr);// lets have some dirt//MS 30Nov98
	//DeadCode MS 10Dec98				LaunchDirtLarge(hitpositm,worldptr);

					hitpositm->World.Y = glevel;
					LaunchShockwave(hitpositm,worldptr);
				}
			}
		}
		break;
		case ANIM_BIGCOLLAPSE:
		{
			if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
			{
				hitpositm->World.Y = grpCoords.Y;
				_Miles.PlaySample(FileNum(FIL_SFX_COLLAPSE_BUILDING_LARGE1+Math_Lib.rnd(4)),hitpositm);
				LaunchDustRing(hitpositm,worldptr);	
				LaunchSmoulder(hitpositm,worldptr);
			}
			else
			{
// We want the fire to be put in the list, regardless of whether it is visible or not...
				Coords3D	firepos = grpCoords;
				firepos.Y += 8000 + Math_Lib.rnd(1000);

				Land_Scape.AddSmokeCloud(firepos,250/Timer_Code.FRAMETIME);
			}
		}
		break;											
		case ANIM_AMMOBOXES:										
			LaunchIgniteAmmoBoxes(hitpositm,groupindex,worldptr);//RJS 20Nov98
			break;											
		case ANIM_THROWBOXES:										
			LaunchAmmoBoxes(hitpositm,groupindex,hitterCoords,damagestrength,worldptr);		//RJS 26Apr99
			break;
		case ANIM_FUELBARRELS:									
			LaunchGroundExplosion(hitpositm,worldptr);		
			LaunchFuelBarrels(hitpositm,worldptr);			
			break;											
		case ANIM_CHICKENS:
			if (WithinVisibleRange(hitCoords,100000))		//RJS 11Jun99
			{
				_Miles.PlayOnce(FIL_SFX_HEN_SCUFFLE, (ItemBasePtr) hitpositm);
				LaunchBirds(hitpositm,hitCoords,ChickenShape,8,worldptr);
			}
			break;
		case ANIM_TANKDEATH:
			if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
			{
				if (hitpositm->shape == BOMB)
				{
					_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_DISTANT1+Math_Lib.rnd(2)), (ItemBasePtr) hitpositm);
					LaunchSmoulder(hitpositm,worldptr);
					_Miles.StopSample(FIL_SFX_TANK_LOOP1,itm);
				}
			}
			break;											
		case ANIM_BRIDGEDEATH:									
			hitpositm->World = oldcoords;
			LaunchBridgeElement(itm,grpCoords,groupindex,worldptr);//RJS 26Feb99
			break;
		case ANIM_TRAINDEATH:									
			_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_DISTANT1+Math_Lib.rnd(2)), (ItemBasePtr) hitpositm);
			LaunchSmoulder(hitpositm,worldptr,TRUE);			
			break;
		case ANIM_FUELDAMAGE:
		{
			if (WithinVisibleRange(hitCoords,400000))					//RJS 28Jun00
				LaunchSnapFlash(hitpositm,worldptr);					//RJS 28Jun00

			SLong	fxlevel;
			if (weapptr)											//RJS 26Nov99
			{
				WeapAnimData*	weapon = (WeapAnimData*) weapptr;
				if ((weapon->LauncherType==LT_FUEL) || (weapon->LauncherType==LT_INTFUEL))
					weapon->pitch = -1;
				else
					weapon->pitch = 32767;

				fxlevel = SHAPE.LogFuelDamage(itm,weapptr);				//RJS 26Nov99
				if (fxlevel)
				{
					// If the tank is fairly empty, explode!
					if (fxlevel > 15)									//RJS 26Nov99
						LaunchVapourStream(weapptr,shapehit);			//RJS 26Nov99
					else
					{
						hitpositm->World = oldcoords;
						KillLauncher(hitpositm,theShooter,worldptr,groupindex,&hitCoords);
					}
				}
			}
			else
			{
				fxlevel = SHAPE.LogFuelDamage(itm,NULL,randval);
				if (fxlevel)
				{
					// If the tank is fairly empty, explode!
					if (fxlevel > 15)
						LaunchAircraftFire(hitpositm,hitCoords,worldptr);
					else
					{
						hitpositm->World = oldcoords;
						KillLauncher(hitpositm,theShooter,worldptr,groupindex,&hitCoords);
					}
				}
			}
		}
		break;
		case ANIM_WEAPONDAMAGE:									
			break;
		case ANIM_TURBULANCE:
			if (!_Replay.Playback)
			{
				if (itm->Status.size == AirStrucSize)									//RJS 18Jan99
				{																		//RJS 18Jan99
					AirStrucPtr	ac = (AirStrucPtr) itm;									//RJS 18Jan99
					ac->fly.pModel->SetLocalGust(oldcoords,hitCoords,damagestrength*10);//RJS 29Jun99
				}																		//RJS 18Jan99
				else
				{
					// Ateam effect code... but just move the object, don't throw??

				}
			}
			break;
		case ANIM_DROPGEAR:										//RJS 07Sep98
			SHAPE.KillGear(itm);								//RJS 07Sep98
			break;												//RJS 07Sep98
		case ANIM_TOTALDESTRUCTION:
		{
			if (hitpositm == Manual_Pilot.ControlledAC2)
				Squad_Diary.UpdatePlayerLog(EFS_KIA);

			hitpositm->World = oldcoords;
			KillLauncher(hitpositm,theShooter,worldptr,groupindex,&hitCoords);//JIM 11Mar99
			break;
		}
		case ANIM_NAPALM:
			if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
			{
				// Singe and scatter fires...
				LaunchScatteredFire(hitpositm,shapehit,worldptr);
			}
			break;
		case ANIM_BLOKESEXPLODE:
		{
			if (WithinVisibleRange(hitCoords,100000))		//RJS 11Jun99
			{
				UWord	maxtroops = randval;			//RJS 01Jul99

				_Miles.PlayOnce((FileNum) (FIL_SFX_YELP1 + Math_Lib.rnd(5)),hitpositm);
				LaunchDebris(hitpositm,BlokeFlyingShape,0,maxtroops,worldptr,TRUE);
			}
			break;
		}
		case ANIM_BLOKESNAPALM:
		{
			if (WithinVisibleRange(hitCoords,200000))		//RJS 11Jun99
			{
				UWord	maxtroops = randval;				//RJS 01Jul99

				hitpositm->World = oldcoords;
				_Miles.PlayOnce((FileNum) (FIL_SFX_YELP1 + Math_Lib.rnd(5)),hitpositm);
				LaunchTroops(hitpositm,BlokeFireShape,hitCoords,worldptr,maxtroops);
			}
		}
		break;
		case ANIM_BLOKES:
		{
			if (WithinVisibleRange(hitCoords,200000))		//RJS 11Jun99
			{
				UWord	maxtroops = randval;				//RJS 01Jul99

				hitpositm->World = oldcoords;
				LaunchTroops(hitpositm,BlokeRunShape,hitCoords,worldptr,maxtroops);
			}
		}
		break;
		case ANIM_TOSS:
		{
			if (groupindex == -1)								//RJS 06Dec98
				hitpositm->World = grpCoords;					//RJS 06Dec98

			LaunchTossedShape(hitpositm,groupindex,hitterCoords,damagestrength,worldptr);//RJS 06Dec98
			break;
		}
		case ANIM_DEBRISDIRT:
		{
			if (WithinVisibleRange(hitCoords,100000))		//RJS 11Jun99
			{
				ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(shapehit);
				ULong				size = 4 + ((sdptr->Size << 4) * damagestrength)/6324;//MS 10Dec98

				LaunchDebris(hitpositm,DebrisDirtShape,2,size,worldptr);
			}
		}
		break;
		case ANIM_DEBRISMECH:
		{
			if (WithinVisibleRange(hitCoords,100000))		//RJS 11Jun99
			{
				ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(shapehit);
				ULong				size = 4 + ((sdptr->Size << 4)*damagestrength)/6324;//MS 10Dec98

				LaunchDebris(hitpositm,DebrisMechShape,0,size,worldptr);
			}
		}
		break;
		case ANIM_DEBRISWOOD:
		{
			if (WithinVisibleRange(hitCoords,100000))		//RJS 11Jun99
			{
				ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(shapehit);
				ULong				size = 4 + ((sdptr->Size << 4)*damagestrength)/6324;//MS 10Dec98
		
				LaunchDebris(hitpositm,DebrisWoodShape,2,size,worldptr);
			}
		}
		break;
		case ANIM_DEBRISBRICK:
		{
			if (WithinVisibleRange(hitCoords,100000))		//RJS 11Jun99
			{
				ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(shapehit);
				ULong				size = 4 + ((sdptr->Size << 4)*damagestrength)/6324;//MS 10Dec98

				LaunchDebris(hitpositm,DebrisBrickShape,2,size,worldptr);
				LaunchDirtyBuildingFingers(hitpositm,Math_Lib.rnd(),worldptr);// lets have some dirt
			}
		}
		break;
		case ANIM_TIMEBOMB:
		{
			AircraftAnimData*	adptr = (AircraftAnimData*) hitpositm->Anim;

			ULong	animoffset = ULong(&adptr->ENGINELEFT) - ULong(adptr);

			LaunchTimeBomb(hitpositm,animoffset,worldptr);
		}
		break;
		case ANIM_DUSTCLOUD:
			if (WithinVisibleRange(hitCoords,100000))		//RJS 11Jun99
			{
				ShapeNum	oldshape = hitpositm->shape;			//RJS 18Jun99
				hitpositm->shape = shapehit;

				LaunchMushroomCloud(hitpositm,damagestrength,worldptr);

				hitpositm->shape = oldshape;
			}
			break;
		case ANIM_TUMBLE:									
		{
			hitpositm->World = oldcoords;
			LaunchCollapse(itm,grpCoords,groupindex,worldptr);
		}
		break;
		case ANIM_SMALLFLASH:
			if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
				LaunchSnapFlash(hitpositm,worldptr);		//RJS 28Jun99
			break;
		case ANIM_SINK:
			hitpositm->World = oldcoords;
			LaunchBoatSink(itm,grpCoords,groupindex,worldptr);
			break;
		case ANIM_FUELEXPLOSION:
			if (WithinVisibleRange(hitCoords,200000))		//RJS 11Jun99
			{
				hitpositm->World = grpCoords;
				LaunchFingers(hitpositm,worldptr);
				LaunchTransientTrail(hitpositm,FireballShape,500,FALSE,worldptr,400);
				LaunchExplodePuff(hitpositm,1000,ExplodeSmokeShape,800,worldptr);
			}
			break;
		case ANIM_SAGTRANSIENT:
			if (	(hitpositm->Status.size != TRANSIENTSIZE)
				&&	(hitpositm != Persons2::PlayerSeenAC)		)
				LaunchSAGTransient(hitpositm,shapehit,grpCoords,groupindex,worldptr);
			break;
		case ANIM_BURSTBALLOON:
		{
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shapehit);
			ShapeNum		deadShape = (ShapeNum)sdptr->Type.shapenumber;
			animptr			adptr = itm->Anim;
			Coords3D		pos;
			MinAnimData*	mad;
			ShapeNum		testshape = itm->shape;

			SHAPE.SimpleGroupItemAnim(adptr,testshape,groupindex,pos);

			mad = (MinAnimData*)adptr;
			mad->IsInvisible = 1;
			mad->itemstate = DEAD;

			LaunchDeadBalloon(deadShape,grpCoords,worldptr);
			break;
		}
		case ANIM_SPAZGEAR:									//RJS 17Dec99
		{
			if (itm->Status.size == AIRSTRUCSIZE)
			{
				AirStrucPtr	ac = (AirStrucPtr)itm;
				ac->fly.pModel->DamageGear(hitCoords);
			}
			break;
		}
		case ANIM_ACRICOCHET:								//RJS 14Jan00
		{
			LaunchACRicochet(hitpositm,worldptr);
			break;
		}
		case ANIM_ENGINESMOKE:								//RJS 15Feb00
		{
			if (itm == Persons2::PlayerSeenAC)
				Land_Scape.smokePlaneOn=true;				//RJS 15Feb00
			break;
		}
		case ANIM_SCAREDBIRDS:
		{
			BirdCentralControl(hitpositm,ShapeNum(hitshape),groupindex,worldptr);
			break;
		}
		case ANIM_BLOKESHOT:
		{
			Anim_Control.SetPlayerAnim(hitpositm,ANIMATION_SHOT);//RJS 26Apr00
			break;
		}
		case ANIM_BLOKEDEAD:
		{
			_Miles.PlayOnce(FileNum(FIL_SFX_YELP1 + Math_Lib.rnd(5)),hitpositm);

			TransientItemPtr	newitem;
			newitem = SimplifiedSpriteLaunch(hitpositm,ShapeNum(hitshape),2000,MOBILE_DEBRIS);
			if (newitem)
			{
				SWord	newhdg;
				SLong	vel;

				ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(ShapeNum(hitshape));
				if (sdptr->AnimDataSize == TROOPANIM)
				{
					TroopAnimData*	adptr = (TroopAnimData*)newitem->Anim;
					if (hitpositm->OverFrance())
						adptr->stripno = CLOTHING_LWPILOT;
					else
						adptr->stripno = CLOTHING_RAFPILOT;
				}

				if (theShooter->Status.size >= MOBILESIZE)
					newhdg = Math_Lib.arctan(MobileItemPtr(theShooter)->vel_x,MobileItemPtr(theShooter)->vel_z);
				else
					newhdg = Math_Lib.rnd();

				Anim_Control.SetPlayerAnim(newitem,ANIMATION_AARGH);

				vel = Math_Lib.rnd(100);

				newitem->World = oldcoords;								//RJS 26Oct00
				newitem->hdg = Angles(newhdg);			
				newitem->pitch = ANGLES_30Deg;
 				newitem->vel_ = (100 + vel)*1000;
				newitem->CalcVels();

				AddTransientItemToWorld(newitem,worldptr);
			}

			hitpositm->Status.deadtime = 1;
			MinAnimData*	mad = (MinAnimData*)hitpositm->Anim;
			mad->itemstate = DEAD;
			mad->IsInvisible = 1;
//DeadCode RJS 26Oct00 			Anim_Control.SetPlayerAnim(hitpositm,ANIMATION_SHOTDEAD);//RJS 26Apr00
			break;
		}
		case ANIM_COMEDYBALLOON:
		{
			break;
		}
	}

	hitpositm->World = oldcoords;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSmokeCloud
//Author		Robert Slater
//Date			Fri 3 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchSmokeCloud(mobileitem *launcher,ShapeNum	theShape,COORDS3D	pos,WorldStuff &worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(launcher,theShape,6000,MOBILE_STATIONARY);
	if (newitem)
	{
		newitem->World = pos;
		newitem->TransRandom = 0;

		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDirtSmall
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDirtSmall(mobileitem* launcher,WorldStuff& worldptr, bool dosound)
{
	TransientItem*	newitem = SimplifiedSpriteLaunch(launcher,BULGND,170,MOBILE_STATIONARY);
	if (newitem)
	{
		if (dosound)
			_Miles.PlaySample((FileNum)(FIL_SFX_RICOCHET_SOFT_SURFACE1+Math_Lib.rnd(2)),newitem);

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDirtMedium
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDirtMedium(mobileitem* launcher,WorldStuff& worldptr)
{
	if (	(desiredFPS <= realFPS)
		&&	WithinVisibleRange(launcher->World,400000)	)		//RJS 06Jun00
	{
		TransientItem*	newitem;									//MS 10Dec98
																		//MS 10Dec98
		newitem = SimplifiedSpriteLaunch(launcher,DRTYX,400,MOBILE_STATIONARY);//MS 10Dec98
		if (newitem)												//MS 10Dec98
			AddTransientItemToWorld(newitem, worldptr);				//MS 10Dec98
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDirtLarge
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDirtLarge(mobileitem* launcher,WorldStuff& worldptr)
{
	if (WithinVisibleRange(launcher->World,400000))				//RJS 30Apr99
	{
		TransientItemPtr	newitem;								//MS 10Dec98
		ANGLES				hdg,pitch,roll;							//MS 10Dec98
		hdg=launcher->hdg; //JIM 16/11/99
		Three_Dee.pMigLand->GetShadowAngles(launcher->World,hdg,pitch,roll);//MS 10Dec98
																	//MS 10Dec98
		newitem = SimplifiedSpriteLaunch(launcher,DRTYX,400,MOBILE_STATIONARY);//MS 10Dec98
		if (newitem)												//MS 10Dec98
			AddTransientItemToWorld(newitem, worldptr);				//MS 10Dec98
																	//MS 10Dec98
//DeadCode RJS 13Oct00 		newitem = SimplifiedSpriteLaunch(launcher,MUSHY,400,MOBILE_STATIONARY);//MS 10Dec98
//DeadCode RJS 13Oct00 		if (newitem)												//MS 10Dec98
//DeadCode RJS 13Oct00 		{															//MS 10Dec98
//DeadCode RJS 13Oct00 			newitem->hdg = hdg;										//MS 10Dec98
//DeadCode RJS 13Oct00 			newitem->pitch = pitch;									//MS 10Dec98
//DeadCode RJS 13Oct00 			newitem->roll = roll;									//MS 10Dec98
//DeadCode RJS 13Oct00 																	//MS 10Dec98
//DeadCode RJS 13Oct00 			AddTransientItemToWorld(newitem, worldptr);				//MS 10Dec98
//DeadCode RJS 13Oct00 		}															//MS 10Dec98
																	//MS 10Dec98
		newitem = SimplifiedSpriteLaunch(	launcher,				//MS 10Dec98
											ExplosionShockShape,	//MS 10Dec98
											100,MOBILE_STATIONARY);	//MS 10Dec98
		if (newitem)												//MS 10Dec98
		{															//MS 10Dec98
			newitem->World.Y += METRES01;							//RJS 21Apr99
			newitem->hdg = hdg;										//MS 10Dec98
			newitem->pitch = pitch;									//MS 10Dec98
			newitem->roll = roll;									//MS 10Dec98
																	//MS 10Dec98
			AddTransientItemToWorld(newitem, worldptr);				//MS 10Dec98
		}															//MS 10Dec98
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSplashSmall
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchSplashSmall(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem = SimplifiedSpriteLaunch(launcher,BULWAT,200,MOBILE_STATIONARY);
	if (newitem)
	{
		_Miles.PlaySample(FIL_SFX_RICOCHET_WATER1,newitem);
		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSplashMedium
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchSplashMedium(mobileitem* launcher,WorldStuff& worldptr)
{
	if (WithinVisibleRange(launcher->World,300000))				//RJS 30Apr99
	{
		TransientItem*	newitem = SimplifiedSpriteLaunch(launcher,SPLASH,700,MOBILE_STATIONARY);
		if (newitem)
			AddTransientItemToWorld(newitem, worldptr);

		_Miles.PlayOnce(FIL_SFX_COLLISION_WATER,launcher);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSplashLarge
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchSplashLarge(mobileitem* launcher,WorldStuff& worldptr)
{
	if (WithinVisibleRange(launcher->World,300000))				//RJS 30Apr99
	{
		TransientItem*	newitem;

		newitem = SimplifiedSpriteLaunch(launcher,GNDEXP,400,MOBILE_STATIONARY);
		if (newitem)
			AddTransientItemToWorld(newitem, worldptr);

		_Miles.PlayOnce(FIL_SFX_COLLISION_WATER,launcher);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDustRingBig
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDustRingBig(mobileitem* launcher,WorldStuff& worldptr)
{
	if (WithinVisibleRange(launcher->World,200000))				//RJS 30Apr99
	{
		TransientItem*	newitem;

		newitem = SimplifiedSpriteLaunch(	launcher,
											DRTSHK,					//RJS 15Dec99
											400,MOBILE_STATIONARY);	//RJS 27Apr98

		if (newitem)
		{
			_Miles.PlaySample(FileNum(FIL_SFX_DEBRIS_SHOWER1+Math_Lib.rnd(4)),newitem);	//RJS 14Jun00
			AddTransientItemToWorld(newitem, worldptr);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoImpactGround
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::DoImpactGround(ItemPtr	launcher, Coords3D	impactpos,UByte	areatype)
{
	WorldStuff	*world = mobileitem::currworld;
	UWord		HitStrength = SHAPESTUFF.GetShapeDamageStrength(launcher->shape);//RJS 22Jan98
	UWord		HitDamageType = SHAPESTUFF.GetShapeDamageType(launcher->shape);//RJS 22Jan98
	AreaType	theArea = (AreaType)areatype;								//RJS 27Nov98
	Coords3D	oldpos = launcher->World;

	launcher->World = impactpos;

	SLandLight lightDef;
	lightDef.pos=impactpos;
	lightDef.color.r=0xFF00;
	lightDef.color.g=0xFF00;
	lightDef.color.b=0xFF00;
	lightDef.timer=50;	//half a second
	lightDef.range=25000;	//quarter km

	switch (HitDamageType)
	{
	case DMT_BULLET:
	{
		if (WithinVisibleRange(impactpos,160000))				//RJS 30Apr99
		{
			switch (theArea)
			{
			case AT_sea:
			case AT_stream:
				LaunchSplashSmall((mobileitem*)launcher,*world);
				break;
			case AT_village:
			case AT_denseTown:
			case AT_sparseTown:
			case AT_denseCity:
			case AT_sparseCity:
			case AT_cityBase:
//DeadCode JON 4Sep00 			case AT_coastRock:
			case AT_urbanBuildup:
			case AT_whiteChalk: // does it?
				LaunchDirtSpark((mobileitem*)launcher,*world);	//RJS 06Jul99
				break;
			default:
				LaunchDirtSmall((mobileitem*)launcher,*world);
				break;
			}
		}
	}
	break;
	case DMT_FIRE:
	{
		//Impact toggle...
		if (	View_Object
			&&	(launcher->Status.size == TRANSIENTSIZE)
			&&	(((TransientItemPtr)launcher)->Launcher == Manual_Pilot.ControlledAC2))
			View_Object->PossDirectorAction(launcher->World);	//DAW 22Jun99

//deadcode JON 19/06/01			Land_Scape.AddLight(&lightDef);

		if ( IsWater( theArea ) )
		{
			_Miles.PlayOnce(FIL_SFX_DEBRIS_WATER2,launcher);
			LaunchSplashMedium((mobileitem*)launcher,*world);
		} else 
			LaunchNapalmStrike((mobileitem* )launcher,*world);
	}
	break;
	case DMT_EXPLOSION:
	{
		//Impact toggle...
		if (	View_Object
			&&	(launcher->Status.size == TRANSIENTSIZE)
			&&	(((TransientItemPtr)launcher)->Launcher == Manual_Pilot.ControlledAC2))
			View_Object->PossDirectorAction(launcher->World);	//DAW 22Jun99

//deadcode JON 19/06/01			Land_Scape.AddLight(&lightDef);

// Scale hit strength with the surface type
//
// i.e.  soft surfaces will absorb more of the explosion & cause more dirt.

		LaunchShockwave((mobileitem*)launcher,*world);
		LaunchRealShockwave((mobileitem*)launcher,HitStrength,*world);//RJS 02Dec98

		if (IsWater(theArea))											//RJS 4Oct00
		{
			if (HitStrength > 24)
			{
				_Miles.PlayOnce(FIL_SFX_COLLISION_WATER,launcher);
				LaunchSplashLarge((mobileitem*)launcher,*world);
			}
			else
			{
				_Miles.PlayOnce(FIL_SFX_DEBRIS_WATER2,launcher);
				LaunchSplashMedium((mobileitem*)launcher,*world);
			}
		}
		else
		{
			LaunchExplodePuff((mobileitem*)launcher,1000,ExplodeDirtShape,800,*world);	//RJS 4Oct00

			Land_Scape.LogCrater(launcher->World,HitStrength);	//RJS 18Nov99

//DeadCode RJS 18Nov99 			Land_Scape.AddLight(&lightDef);

			LaunchFlash((mobileitem*)launcher,HitStrength,*world);		//RJS 20Jan99

			_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_TANK+Math_Lib.rnd(3)), launcher);//RJS 10Nov98

			LaunchDirtMedium((mobileitem*)launcher,*world);

			LaunchCrater((mobileitem*)launcher,*world);
		}
	}

	break;
	default:
	{
		if ( IsWater( theArea ) )
			LaunchSplashMedium((mobileitem*)launcher,*world);
		else
		{
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);
			SLong			impactsize = sdptr->Size << 4;

			if (launcher->Status.size == TRANSIENTSIZE)
			{
				TransientItem*	mobptr = (TransientItem*) launcher;
				SLong		vel = mobptr->vel_y;

				if (vel < 0) vel = -vel;

				impactsize *= vel;
				impactsize /= 10000; //CSB 09/11/99
			}

			if (impactsize < 100)
				LaunchDustRing((mobileitem*)launcher,*world);
			else
			{
//deadcode JON 19/06/01					Land_Scape.AddLight(&lightDef);

				LaunchDustRingBig((mobileitem*)launcher,*world);
			}
		}
	}
	break;
	}

	launcher->World = oldpos;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LandedEffect
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
void	TransObj::LandedEffect(AirStrucPtr	ac, SLong	landed,Bool send,bool fromPacket)
{
#ifdef	_CACHE_CHECK_
	File_Man.DebugLog("HIT!");
#endif

	if(ac->fly.numinsag)
	{
		LaunchDirtLarge(ac, *mobileitem::currworld);
		ac->DestroySag();
		ac->Status.deadtime = 1;
		return;
	}

	if((_Analogue.FF_airframe) && (ac == Persons2::PlayerSeenAC))
		switch(landed)
		{
			case _Collide.NOSE_TOUCH:		_Analogue.FFstiff.SetX(30000,  30000);	break;
			case _Collide.TAIL_TOUCH:		_Analogue.FFstiff.SetX(30000, -30000);	break;
			case _Collide.LEFT_WING_TOUCH:	_Analogue.FFstiff.SetZ(30000,  30000);	break;
			case _Collide.RIGHT_WING_TOUCH:	_Analogue.FFstiff.SetZ(30000, -30000);	break;
		}

	UByte		theArea;
	WorldStuff	*world = mobileitem::currworld;
	SLong		gheight = GetGroundLevel(ac,theArea);					//RJS 14Apr99
	ULong		oldmovecode;
	Bool		onWater = FALSE;
	Bool		onSparky = FALSE;								//RJS 11Dec98
	Bool		doEffect = TRUE;
	Bool		doSpecial = Bool(!ac->IsHealthyMovecode(oldmovecode));//RJS 07Jun00
	Bool		haddamage,isPlayer;								//RJS 11Jun99
																//RJS 11Jun99
	if (ac->lasthitter.count)									//RJS 11Jun99
		haddamage = TRUE;										//RJS 11Jun99
	else														//RJS 11Jun99
		haddamage = FALSE;										//RJS 11Jun99

	HitTheDeck = true;											//RDH 09May99

	ac->fly.rpm /= 2;														//RJS 10Jul00
	ac->fly.rpm1 /= 2;			

	if (!fromPacket)											//RJS 07Jun00
	{
//DeadCode CSB 5Sep00 		ac->vel_y = 0;												//RJS 03May00
		if (	(ac==Persons2::PlayerSeenAC)								//RJS 2Jun00
			||	(ac==Persons2::PlayerGhostAC)	)							//RJS 2Jun00
		{
			isPlayer = TRUE;										//RJS 11Jun99
			if (Manual_Pilot.controlmode==ManualPilot::PILOTDEAD)	//RJS 20Apr99
				doSpecial = TRUE;

			if (!Save_Data.gamedifficulty[GD_GROUNDCOLLISIONS])			//RJS 08Jan99
			{
				ac->World.Y = gheight;
				doEffect = FALSE;
				if (!doSpecial)
				{
					AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;

					if (	(!adptr->acleglowerl && !adptr->LEFTWHEEL)//DAW 19May99
						&&	(!adptr->acleglowerr && !adptr->RIGHTWHEEL)	)//DAW 19May99
						ac->World.Y -= ac->fly.pModel->GearList->pos0.y;
					else
						ac->World.Y += ac->classtype->deckshunt;			//CSB 24/02/00
	//DEADCODE CSB 24/02/00 					ac->World.Y += 200;							//DAW 01Jul99
					ac->pitch = ac->classtype->deckangle;
					ac->roll = ANGLES_0Deg;
					ac->fly.pModel->UpdateModel(ac);

//DeadCode CSB 10Nov00 					ac->fly.pModel->Pos.y = ac->World.Y;
				}
			}
		}
		else
			isPlayer = FALSE;										//RJS 11Jun99
	}
	else
	{
		isPlayer = FALSE;										//RJS 07Jun00
		send = FALSE;
	}

	// Block normal ground collisions, but keep special ones (ie. if you are already dead)
	if (!doSpecial && !doEffect)								//RJS 08Jan99
		return;

	if (_DPlay.Implemented || _Replay.Record)					//RJS 29Oct98
	{
		UByte b1,b2;

		b1=(((UWord)landed)>>8)&255;
		b2=((UWord)landed)&255;

		if (send
			&& ac==Persons2::PlayerSeenAC) // AMM01Oct98 etc
			_DPlay.NewSpecial(DPlay::PIDC_LANDEDEFFECT,b1,b2,theArea);
	}

//DEADCODE CSB 14/03/00 	if(ac->fly.numinsag)												//CSB 14/03/00
//DEADCODE CSB 14/03/00 	{																	//CSB 14/03/00
//DEADCODE CSB 14/03/00 		LaunchMushroomCloud(ac, 10, *world);							//CSB 14/03/00
//DEADCODE CSB 14/03/00 		return;															//CSB 14/03/00
//DEADCODE CSB 14/03/00 	}																	//CSB 14/03/00

	switch (theArea)
	{
		case AT_sea:
		case AT_stream:
			onWater = TRUE;
			break;
		case AT_village:
		case AT_denseTown:
		case AT_sparseTown:
		case AT_denseCity:
		case AT_sparseCity:
		case AT_cityBase:
//DeadCode JON 4Sep00 		case AT_coastRock:
		case AT_urbanBuildup:
		case AT_whiteChalk: // does it?
			onSparky = TRUE;									//RJS 11Dec98
			break;												//RJS 11Dec98
	}

	if (!doSpecial)												//RJS 08Jan99
	{
		Squad_Diary.SetAC(ac,ac->Anim);									//RJS 21Sep00

		AircraftAnimData	*adptr = (AircraftAnimData*) ac->Anim;
		if (IsWater(theArea))											//RJS 4Oct00
		{
			adptr->hasdust = TRUE;
//DeadCode CSB 5Sep00 			Manual_Pilot.DeathSequenceOverride(ac,AUTO_HITWATER);

//DeadCode RJS 4Sep00 			if (!ac->Status.deadtime)							//RJS 30Aug00
//DeadCode RJS 4Sep00 				ac->ai.diaryptr->AddKilled(ac);					//RJS 30Aug00

			_Miles.PlayOnce(FIL_SFX_COLLISION_WATER,ac);

			switch (landed)
			{
				case _Collide.PROP_TOUCH:
				{
					Manual_Pilot.DeathSequenceOverride(ac,AUTO_HITWATER);
					LaunchWaterTrail(ac,*world);

					SHAPE.ForceDamage(ac, ac, &adptr->ENGINELEFT, BitStates(254));
					SHAPE.ForceDamage(ac, ac, &adptr->ENGINERIGHT, BitStates(254));

					if (isPlayer)
					{
						View_Object->SetToDeathView(DEATH_SKID);
						Squad_Diary.UpdatePlayerLog(EFS_BadCrashField);
					}
					break;
				}
				case _Collide.NOSE_TOUCH:
				{
					Manual_Pilot.DeathSequenceOverride(ac, AUTO_CRASHTUMBLE);
					KillLauncher(ac,ac,*world);
					if (isPlayer)					//RJS 31May00
					{
						View_Object->SetToDeathView(DEATH_SKID);
						Squad_Diary.UpdatePlayerLog(EFS_ACLOST);		//RJS 2Jun00
					}

					if (!fromPacket)
						ac->vel_ = ac->vel_x = ac->vel_y = ac->vel_z = 0;	//RJS 30Aug00
					break;
				}
				case _Collide.RIGHT_WING_TOUCH:
				{
					Manual_Pilot.DeathSequenceOverride(ac, AUTO_CRASHTUMBLE);
					SHAPE.ForceDamage(ac,ac,&adptr->RIGHTWINGIN,BS_DEAD);//JIM 11Mar99
					LaunchWaterTrail(ac,*world);
					if (isPlayer)					//RJS 31May00
					{
						View_Object->SetToDeathView(DEATH_SKID);
						Squad_Diary.UpdatePlayerLog(EFS_BadCrashField);
					}
					break;
				}
				case _Collide.LEFT_WING_TOUCH:
				{
					Manual_Pilot.DeathSequenceOverride(ac, AUTO_CRASHTUMBLE);
					SHAPE.ForceDamage(ac,ac,&adptr->LEFTWINGIN,BS_DEAD);//JIM 11Mar99
					LaunchWaterTrail(ac,*world);
					if (isPlayer)					//RJS 31May00
					{
						View_Object->SetToDeathView(DEATH_SKID);
						Squad_Diary.UpdatePlayerLog(EFS_BadCrashField);
					}
					break;
				}
				default:
				{
					Manual_Pilot.DeathSequenceOverride(ac, AUTO_HITWATER);
					LaunchWaterTrail(ac,*world);
					if (isPlayer)					//RJS 31May00
					{
						if (haddamage)
							Squad_Diary.UpdatePlayerLog(EFS_BadCrashField);
						else
							Squad_Diary.UpdatePlayerLog(EFS_DitchedField);

						View_Object->SetToDeathView(DEATH_SKID);
					}
					break;
				}
			}

			LaunchSplashMedium(ac,*world);
		}
		else
		{
			if (landed == _Collide.LANDED_OK)
			{
//DeadCode RJS 11Jun99 				// Perhaps throw up a bit of dirt...
//DeadCode RJS 11Jun99 
//DeadCode RJS 11Jun99 				adptr->hasdust = FALSE;
//DeadCode RJS 11Jun99 				if (!adptr->justlanded)
//DeadCode RJS 11Jun99 				{
//DeadCode RJS 11Jun99 					adptr->justlanded = TRUE;
//DeadCode RJS 11Jun99 					_Miles.PlayOnce(FIL_SFX_TYRE_SCREECH1,ac);
//DeadCode RJS 11Jun99 				}
			}
			else
			{
				LaunchExplodePuff(ac,500,DRTSML,450,*world);			//RJS 7Nov00
				if(ac->vel_y < - ac->classtype->landingspeed / 2)
				{
					Manual_Pilot.DeathSequenceOverride(ac, AUTO_NOPPILOT);	//RJS 31May00
					if (!fromPacket)									//RJS 30Aug00
					{													//RJS 30Aug00
						UByte	theArea;								//RJS 30Aug00
																		//RJS 30Aug00
						ac->World.Y = GetGroundLevel(ac,theArea);		//RJS 30Aug00
						ac->vel_ = ac->vel_x = ac->vel_y = ac->vel_z = 0;	//RJS 30Aug00
					}

					ExplodeAC(ac,ac,*world);
//DeadCode RJS 25Sep00 					ac->vel_ = ac->vel_x = ac->vel_y = ac->vel_z = 0;	//CSB 30Aug00
					LaunchMushroomCloud(ac, 10, *world);				//RJS 31May00
				}
				else if (ac->vel_ > 1000000)					//RJS 31May00
				{
					_Miles.PlayOnce(FIL_SFX_COLLISION_GROUND3,ac);
					LaunchFakeDelayedExplosion(ac,*world);
					//Launch trailing dirt??
//DeadCode RJS 7Nov00 					LaunchExplodePuff(ac,500,DRTSML,450,*world);
					LaunchTransientTrail(ac,DRTSML,300,FALSE,*world,200);

//DeadCode RJS 4Sep00 					if (!ac->Status.deadtime)							//RJS 30Aug00
//DeadCode RJS 4Sep00 						ac->ai.diaryptr->AddKilled(ac);					//RJS 30Aug00

					Manual_Pilot.DeathSequenceOverride(ac, AUTO_CRASHTUMBLE);

					if (isPlayer)			//RJS 31May00
					{
						Squad_Diary.UpdatePlayerLog(EFS_PILOTLOST);

 						View_Object->SetToDeathView(DEATH_TUMBLE);
					}
				}
				else
				switch (landed)
				{
					case _Collide.PROP_TOUCH:
					{
						if(((adptr->aclegsuspl != 0) || (adptr->aclegsuspr != 0)) && (ac->vel_ < ac->classtype->landingspeed / 2))
						{
//DeadCode RJS 4Sep00 							if (!ac->Status.deadtime)					//RJS 31Aug00
//DeadCode RJS 4Sep00 								ac->ai.diaryptr->AddDamage();			//RJS 31Aug00

							Manual_Pilot.DeathSequenceOverride(ac, AUTO_CRASHNOSE);

							Squad_Diary.SetACState(DAMMAGED);			//RJS 4Sep00

							if (isPlayer)			//RJS 31May00
							{
								Squad_Diary.UpdatePlayerLog(EFS_DitchedField);

 								View_Object->SetToDeathView(DEATH_SKID);
							}
						}
						else if(adptr->acrpm < 1000)
						{
 							SHAPE.ForceDamage(ac, ac, &adptr->FRONT, BitStates(254));
//DeadCode RJS 12Oct00 							SHAPE.ForceDamage(ac, ac, &adptr->ENGINERIGHT, BitStates(254));
//DeadCode RJS 7Nov00 							LaunchExplodePuff(ac,500,DRTSML,450,*world);
//DeadCode RJS 12Oct00 							LaunchDirtLarge(ac, *world);
						}
						else if(ac->vel_ < ac->classtype->landingspeed)
						{
//DeadCode RJS 4Sep00 							if (!ac->Status.deadtime)					//RJS 31Aug00
//DeadCode RJS 4Sep00 								ac->ai.diaryptr->AddDamage();			//RJS 31Aug00
							Manual_Pilot.DeathSequenceOverride(ac,AUTO_CRASHFLIP);

							Squad_Diary.SetACState(DAMMAGED);			//RJS 4Sep00

							LaunchExplodePuff(ac,500,DRTSML,450,*world);
//DeadCode RJS 12Oct00 							LaunchDirtLarge(ac, *world);
//DEADCODE CSB 01/03/00 							LaunchDustTrail2(ac, *world);
 							if (isPlayer)			//RJS 31May00
							{
								Squad_Diary.UpdatePlayerLog(EFS_DitchedField);

 								View_Object->SetToDeathView(DEATH_SKID);
							}
						}
						else
						{
//DeadCode RJS 4Sep00 							if (!ac->Status.deadtime)							//RJS 30Aug00
//DeadCode RJS 4Sep00 								ac->ai.diaryptr->AddKilled(ac);					//RJS 30Aug00

							Manual_Pilot.DeathSequenceOverride(ac, AUTO_CRASHTUMBLE);
							LaunchDirtLarge(ac, *world);

 							if (isPlayer)			//RJS 31May00
							{
								Squad_Diary.UpdatePlayerLog(EFS_BadCrashField);

 								View_Object->SetToDeathView(DEATH_TUMBLE);
							}

//DEADCODE CSB 01/03/00 							SHAPE.DetatchAllVapourStreams(ac);
//DEADCODE CSB 01/03/00 					
//DEADCODE CSB 01/03/00 							Manual_Pilot.DeathSequenceOverride(ac,AUTO_NOPPILOT);
//DEADCODE CSB 01/03/00 							ExplodeAC(ac,ac,*world);					//JIM 11Mar99
//DEADCODE CSB 01/03/00 
//DEADCODE CSB 01/03/00 							if (View_Object && (ac==Manual_Pilot.ControlledAC2))
//DEADCODE CSB 01/03/00 								View_Object->SetToDeathView(DEATH_NORMAL);
//DEADCODE CSB 01/03/00 
//DEADCODE CSB 01/03/00 							SHAPE.ResetAnimData_NewShape(ac,PDEATH,0,true);//RJS 21Apr99
//DEADCODE CSB 01/03/00 							MinAnimData*	mad = (MinAnimData*)ac->Anim;//RJS 18May99
//DEADCODE CSB 01/03/00 							mad->itemstate = DEAD;						//RJS 28Apr99
//DEADCODE CSB 01/03/00 
//DEADCODE CSB 01/03/00 							LaunchFire(ac,*world);						//RJS 28Jun99
						}
						break;
					}

					case _Collide.NOSE_TOUCH:
					case _Collide.RIGHT_WING_TOUCH:
					case _Collide.LEFT_WING_TOUCH:
					{
//DeadCode RJS 4Sep00 						if (!ac->Status.deadtime)							//RJS 30Aug00
//DeadCode RJS 4Sep00 							ac->ai.diaryptr->AddKilled(ac);					//RJS 30Aug00

						Manual_Pilot.DeathSequenceOverride(ac, AUTO_CRASHTUMBLE);
						LaunchDirtLarge(ac, *world);

						if (isPlayer)			//RJS 31May00
						{
							Squad_Diary.UpdatePlayerLog(EFS_BadCrashField);

							View_Object->SetToDeathView(DEATH_TUMBLE);
						}
						break;
					}
					case _Collide.WHEEL_AND_WING_TOUCH:
					{
						if(ac->vel_ < ac->classtype->landingspeed)
						{
//DeadCode RJS 4Sep00 							if (!ac->Status.deadtime)					//RJS 31Aug00
//DeadCode RJS 4Sep00 								ac->ai.diaryptr->AddDamage();			//RJS 31Aug00

							Manual_Pilot.DeathSequenceOverride(ac, AUTO_CRASHONEWHEEL);

							Squad_Diary.SetACState(DAMMAGED);			//RJS 4Sep00

							LaunchDustTrail2(ac, *world);
							if (isPlayer)			//RJS 31May00
							{
								Squad_Diary.UpdatePlayerLog(EFS_DitchedField);
								View_Object->SetToDeathView(DEATH_TUMBLE);
							}
						}
						else
						{
//DeadCode RJS 4Sep00 							if (!ac->Status.deadtime)							//RJS 30Aug00
//DeadCode RJS 4Sep00 								ac->ai.diaryptr->AddKilled(ac);					//RJS 30Aug00

							Manual_Pilot.DeathSequenceOverride(ac, AUTO_CRASHTUMBLE);
							LaunchDirtLarge(ac, *world);
							if (isPlayer)			//RJS 31May00
							{
								Squad_Diary.UpdatePlayerLog(EFS_BadCrashField);
								View_Object->SetToDeathView(DEATH_TUMBLE);
							}
						}
						break;
					}
					case _Collide.LANDED_BELLY:
					{
						if(ac->vel_ * 10 < 12 * ac->classtype->landingspeed)
						{
//DeadCode RJS 4Sep00 							if (!ac->Status.deadtime)					//RJS 31Aug00
//DeadCode RJS 4Sep00 								ac->ai.diaryptr->AddDamage();			//RJS 31Aug00

							Manual_Pilot.DeathSequenceOverride(ac, AUTO_CRASHSKID);

							Squad_Diary.SetACState(DAMMAGED);			//RJS 4Sep00

							LaunchDustTrail2(ac, *world);
							if (isPlayer)			//RJS 31May00
							{
								Squad_Diary.UpdatePlayerLog(EFS_DitchedField);
								View_Object->SetToDeathView(DEATH_TUMBLE);
							}
						}
						else
						{
//DeadCode RJS 4Sep00 							if (!ac->Status.deadtime)							//RJS 30Aug00
//DeadCode RJS 4Sep00 								ac->ai.diaryptr->AddKilled(ac);					//RJS 30Aug00

							Manual_Pilot.DeathSequenceOverride(ac, AUTO_CRASHTUMBLE);
							LaunchDirtLarge(ac, *world);
							if (isPlayer)			//RJS 31May00
							{
								Squad_Diary.UpdatePlayerLog(EFS_BadCrashField);
								View_Object->SetToDeathView(DEATH_TUMBLE);
							}
						}
						break;
					}
					
					default:
					{
						if (ac->vel_ < MPH100)						//RJS 11Dec98
						{
							_Miles.PlayOnce(FIL_SFX_COLLISION_GROUND4,ac);
							if (onSparky)
								LaunchTransientTrail(ac,SparkShape,4,TRUE,*world,65536,TRUE);
							else
							{
								adptr->hasdust = TRUE;
								LaunchDustTrail2(ac,*world);
							}

							if (isPlayer)		//RJS 31May00
							{
								if (haddamage)
									Squad_Diary.UpdatePlayerLog(EFS_BadCrashField);//RJS 18Feb00
								else
									Squad_Diary.UpdatePlayerLog(EFS_DitchedField);

								View_Object->SetToDeathView(DEATH_SKID);
							}
						}
						else
						{
							if (isPlayer)
								Squad_Diary.UpdatePlayerLog(EFS_BadCrashField);		//RJS 18Feb00

							_Miles.PlayOnce(FIL_SFX_COLLISION_GROUND3,ac);
							LaunchFakeDelayedExplosion(ac,*world);

							SHAPE.DetatchAllVapourStreams(ac);
							if (!onSparky)
							{
								adptr->hasdust = TRUE;
								LaunchDustTrail2(ac,*world);
							}

							LaunchTransientTrail(ac,SmallFireballShape,300,FALSE,*world,65536);
							LaunchCrater(ac,*world);								//RJS 13May99
						}

						Manual_Pilot.DeathSequenceOverride(ac,AUTO_CRASHSKID);
						if (isPlayer)				//RJS 31May00
							View_Object->SetToDeathView(DEATH_SKID);
						break;
					}
					break;
				}
			}
		}

		Squad_Diary.UpdateACDamage();									//RJS 4Sep00
	}
	else
	{
		if (fromPacket)											//RJS 07Jun00
		{
			if (_Replay.Playback)								//RJS 07Jun00
			{
				if (onWater)
				{
					//Put out engine fires...
					if (SHAPESTUFF.GetShapePtr(ac->shape)->AnimDataSize == AIRCRAFTANIM)
					{
						AircraftAnimData	*adptr = (AircraftAnimData*) ac->Anim;

						adptr->ENGINELEFT = BS_DEAD;	
						adptr->ENGINERIGHT = BS_DEAD;	
					}
					else
					{
						SimpleAircraftAnimData	*adptr = (SimpleAircraftAnimData*) ac->Anim;

						adptr->ENGINELEFT = BS_DEAD;
						adptr->ENGINERIGHT = BS_DEAD;
					}

					LaunchSplashMedium(ac,*world);
				}
				else
				{
					KillLauncher(ac,ac,*world);						//JIM 11Mar99
					LaunchFire(ac,*world);
				}

				//Is this really an aircraft??
				if (oldmovecode != 0xFFFFFFFF)
				{
					if (onWater)		//Fiddle movecode dirty, and sink
						_Replay.ReplayDeathMode = RDEATH_SKID;
					else
						_Replay.ReplayDeathMode = RDEATH_NULL;
				}
			}
			else
			{
				if (oldmovecode != AUTO_NOPPILOT)	//Strange if it is!
				{
					ac->pitch = ANGLES_0Deg;							//DAW 03Sep98
					ac->roll = ANGLES_0Deg;								//DAW 03Sep98

					if (onWater)
					{
						if (SHAPESTUFF.GetShapePtr(ac->shape)->AnimDataSize == AIRCRAFTANIM)
						{
							AircraftAnimData	*adptr = (AircraftAnimData*) ac->Anim;

							adptr->ENGINELEFT = BS_DEAD;	
							adptr->ENGINERIGHT = BS_DEAD;	
						}
						else
						{
							SimpleAircraftAnimData	*adptr = (SimpleAircraftAnimData*) ac->Anim;

							adptr->ENGINELEFT = BS_DEAD;
							adptr->ENGINERIGHT = BS_DEAD;
						}

						LaunchSplashMedium(ac,*world);
					}
					else
					{
						KillLauncher(ac,ac,*world);					//JIM 11Mar99
						if (ac==Manual_Pilot.ControlledAC2)					//RJS 31May00
							View_Object->SetToDeathView();				//RDH 02Sep98

//DeadCode CSB 21Oct00 						LaunchFire(ac,*world);
						LaunchDirtMedium(ac,*world);
					}

					//Is this really an aircraft??
					if (oldmovecode != 0xFFFFFFFF)
					{
						ac->vel_ = 0;
						if (onWater)		//Fiddle movecode dirty, and sink
							ac->movecode = AUTO_HITWATER;
						else
						{
							ac->movecode = AUTO_NOPPILOT;
//DeadCode CSB 14Aug00 							ac->RecycleAC();							//CSB 10Aug00
						}
					}
				}
			}
 		}
		else
		{
			if (oldmovecode != AUTO_NOPPILOT)	//Strange if it is!
			{
				ac->pitch = ANGLES_0Deg;							//DAW 03Sep98
				ac->roll = ANGLES_0Deg;								//DAW 03Sep98

				if (onWater)
				{
					if (SHAPESTUFF.GetShapePtr(ac->shape)->AnimDataSize == AIRCRAFTANIM)
					{
						AircraftAnimData	*adptr = (AircraftAnimData*) ac->Anim;

						adptr->ENGINELEFT = BS_DEAD;	
						adptr->ENGINERIGHT = BS_DEAD;	
					}
					else
					{
						SimpleAircraftAnimData	*adptr = (SimpleAircraftAnimData*) ac->Anim;

						adptr->ENGINELEFT = BS_DEAD;
						adptr->ENGINERIGHT = BS_DEAD;
					}

					LaunchSplashMedium(ac,*world);
				}
				else
				{
					//This is if the guy hits the deck but was already fatally wounded...
					MinAnimData*	mad = (MinAnimData*)ac->Anim;
					if (!mad->IsInvisible)
					{
						ExplodeAC(ac,ac,*world);					//RJS 18May99
						LaunchFire(ac,*world);
					}
					else
						LaunchDustRingBig(ac,*world);

					Manual_Pilot.DeathSequenceOverride(ac,AUTO_NOPPILOT);
					if (isPlayer)						//RJS 31May00
						View_Object->SetToDeathView();				//RDH 02Sep98

					SHAPE.ResetAnimData_NewShape(ac,PDEATH,0,true);//RJS 21Apr99
					mad->itemstate = DEAD;							//RJS 18May99
//DeadCode CSB 14Aug00 					ac->RecycleAC();									//CSB 10Aug00
				}

				//Is this really an aircraft??
				if (oldmovecode != 0xFFFFFFFF)
				{
					ac->vel_ = 0;
					if (onWater)		//Fiddle movecode dirty, and sink
						ac->movecode = AUTO_HITWATER;
					else
					{
						ac->movecode = AUTO_NOPPILOT;
//DeadCode CSB 14Aug00 						ac->RecycleAC();									//CSB 10Aug00
					}

				}
			}
		}
	}

	HitTheDeck = false;											//RDH 09May99
	if (!fromPacket)													//RJS 3Nov00
	{
		ac->vel_y = 0;												//RJS 03May00	//CSB 5Sep00
		if(		(ac->movecode != AUTO_CRASHSKID)
			&&	(ac->movecode != AUTO_CRASHROLL) 
			&&	(ac->movecode != AUTO_CRASHONEWHEEL) 
			&&	(ac->movecode != AUTO_CRASHNOSE) 
			&&	(ac->movecode != AUTO_CRASHFLIP) 
			&&	(ac->movecode != AUTO_CRASHTUMBLE) 
			&&	(ac->movecode != AUTO_HITWATER)		)
			ac->vel_ = ac->vel_x = ac->vel_y = ac->vel_z = 0;
	}

	ac->DoAllSAGChecks();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBubbles
//Author		Robert Slater
//Date			Tue 25 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchBubbles(mobileitem* launcher,SLong	dist,WorldStuff& worldptr)
{
	if (WithinVisibleRange(launcher->World,200000))				//RJS 30Apr99
	{
		if (Math_Lib.rnd() > 32000)
		{
			TransientItem*	newitem;
			SLong			rdist;
			ANGLES			theAngle = (Angles)Math_Lib.rnd();
			SLong			xdist, zdist;
			SWord			sin_ang, cos_ang;

			dist = (Math_Lib.rnd() * dist)>>16;

			Math_Lib.high_sin_cos(theAngle,sin_ang,cos_ang);

			xdist = (dist * cos_ang)/ANGLES_FRACT;
			zdist = (dist * sin_ang)/ANGLES_FRACT;

			newitem = SimplifiedSpriteLaunch(	launcher,
												SDUST,
												100,MOBILE_STATIONARY);	//RJS 27Apr98

			if (newitem)
			{
				newitem->World.X += xdist;
				newitem->World.Z += zdist;
				newitem->World.Y = 0;				//Sea level...

				AddTransientItemToWorld(newitem, worldptr);
			}

			_Miles.PlayOnce(FIL_SFX_BUBBLES,launcher);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchWaterTrail
//Author		Robert Slater
//Date			Tue 25 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchWaterTrail(	mobileitem* launcher,
									WorldStuff& worldptr	)
{
	TransientItem*	newitem = LaunchGuidedMissile(	launcher,
													(itemptr )launcher,
													WATSHP,
													LIFETIME_SMOKETRAIL,
													MOBILE_SMOKETRAIL);
	if (newitem)
	{
		MoveGunAnimData*	adptr = (MoveGunAnimData*)newitem->Anim;
		WeapAnimData*		weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

		SHAPE.InitTrailFields((UByteP)weapon,0,32000,LT_DUST);	

		LaunchVapourStream((UByteP)weapon,WATSHP);	

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFingers
//Author		Dave Whiteside
//Date			Thu 3 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchFingers(	mobileitem* launcher,
									WorldStuff& worldptr	)
{
	if (WithinVisibleRange(launcher->World,100000))				//RJS 20May99
	{
		TransientItem*	newitem;
		MoveGunAnimData*	adptr;
		WeapAnimData*		weapon;
		UWord	newhdg;
		UWord	newpitch;
		Float	sin_ang, cos_ang;
//DEADCODE CB 09/11/99 		SWord	sin_ang2, cos_ang2;
		SLong	vel;
		SLong	velhori,vely;
		SLong	temp;
		SLong	count,maxfingers;								//RJS 28May99
		SWord	pitchover;

		if (desiredFPS > realFPS)					//RJS 28May99
			maxfingers = 2;
		else
			maxfingers = 5;


		for (count = 0; count < maxfingers; count++)
		{
			newitem = SimplifiedSpriteLaunch(launcher,			
											FIREB,	
											700,MOBILE_DEBRIS);
			if (newitem)
			{
				adptr = (MoveGunAnimData*)newitem->Anim;
				weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

				SHAPE.InitTrailFields((UByteP)weapon,0,32000,LT_FUEL);

				LaunchVapourStream((UByteP)weapon,FIREB);	

				newhdg = Math_Lib.rnd();
				newpitch = (Math_Lib.rnd()*13653) >> 16;	//75 degrees
				vel = 150000 + (Math_Lib.rnd(250)*1000);		//RJS 16Nov99

				Math_Lib.high_sin_cos((Angles)newpitch,sin_ang,cos_ang);

				Float	fvel,fvelx,fvely,fvelz,fvelh,ftemp;

				fvel = Float(vel);
				ftemp = fvel * sin_ang;	fvely = ftemp;
				ftemp = fvel * cos_ang; fvelh = ftemp;

//Dead				temp = vel * sin_ang;	vely = temp;
//Dead				temp = vel * cos_ang;	velhori = temp;

				newitem->hdg = (Angles) newhdg;			
				newitem->vel_y = fvely;		
				
//DEADCODE CSB 09/11/99 				newitem->velhori = velhori;		
				Math_Lib.high_sin_cos((Angles)newhdg ,sin_ang, cos_ang); //CSB 09/11/99

				fvelx = fvelh * sin_ang;
				fvelz = fvelh * cos_ang;

				newitem->vel_x = fvelx;
				newitem->vel_z = fvelz;
				newitem->vel_ = fvel;
//Dead				newitem->vel_x = velhori * sin_ang;						 //CSB 09/11/99
//Dead				newitem->vel_z = velhori * cos_ang;						 //CSB 09/11/99

				newitem->roll = ANGLES_0Deg;
				newitem->pitch = (Angles) newpitch;

				// max of 70degrees rotation per second (assuming fifty frames/sec)
				pitchover = Math_Lib.rnd()>>8;
				newitem->TransRandom = pitchover;

				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSmokePuff2
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
void	TransObj::LaunchSmokePuff2(mobileitem*	launcher,
									const Coords3D&		posP,			//RJS 6Nov00
									ShapeNum		theShape,
									UWord		deathShape,
									SLong		velhori,
									SLong		vely,
									SWord		hdg,
									SLong		lifetime,
									SLong		maxlife,
									WorldStuff&	worldptr)
{
	TransientItem*	newitem;
	newitem = SimplifiedSpriteLaunch(	launcher,
										theShape,
										lifetime,
										MOBILE_MOVSMK);
	
	if (newitem)
	{
		newitem->World = posP;											//RJS 6Nov00
		newitem->World.Y += 200;
//DEADCODE CSB 09/11/99 		newitem->velhori = velhori;
		Float sin_ang, cos_ang;
		Float	fvelh = Float(velhori);							//RJS 16/11/99
		Math_Lib.high_sin_cos(Angles(hdg), sin_ang, cos_ang);	 //CSB 09/11/99
		newitem->vel_x = (fvelh * sin_ang);						 //CSB 09/11/99
		newitem->vel_z = (fvelh * cos_ang);						 //CSB 09/11/99
		newitem->vel_y = vely;
		newitem->hdg = (Angles) hdg;
		newitem->TransRandom = (maxlife * 6)>>3;
		newitem->roll = (Angles) UWord(lifetime);
		newitem->pitch = (Angles) deathShape;

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ActivateStation
//Author		Robert Slater
//Date			Tue 16 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	TransObj::ActivateStation(AirStrucPtr	ac, UWord &ammotot, UWord	&muzdelay, WorldStuff& world)
{
	SLong	index = -1;												
	ULong	muzVel;													//RJS 12NoV99
//Dead	Bool	retval = FALSE;
	SLong	weapon = ac->weap.weapontype;							//RJS 01Apr99
	SWord	ammoGone,cannonGone;										//RJS 17Oct00

	if ((weapon & LT_MASK) == LT_BULLET)							//RJS 01Apr99
		ac->ACMAS().FrightenBogie();										//RJS 01Apr99
	else
	{

		//drop a pair of bombs always...
		if ((weapon & LT_MASK) == LT_BOMB)									//RJS 11May99
		{
			Bool unArmed;
			if (weapon == LT_NAPALM)
				unArmed = TRUE;
			else
				unArmed = FALSE;

			index = ReActivateStation(ac,muzVel,ammotot,muzdelay,ammoGone,cannonGone,world,unArmed);	//RJS 17Oct00
			if (index > -1)												
			{															
				SLong	massGone = SHAPE.ReduceLauncherLoad(ac,index,ammoGone);	//RJS 10Jul00
																		
				ac->SetWeaponForce(massGone,muzVel,muzdelay);			
//Dead				retval = TRUE;
			}
			else
				return -1;			//allow full reload...
		}
	}

	index = ReActivateStation(ac,muzVel,ammotot,muzdelay,ammoGone,cannonGone,world);	//RJS 17Oct00
	if (index > -1)												
	{															
		//trigger radio message to tell others to drop...
//DEADCODE CSB 11/02/00 		if ((weapon & LT_MASK) != LT_BULLET)							//RJS 01Apr99
//DEADCODE CSB 11/02/00 			OverLay.DecisionMessage(FACMsg,6,ac,ac->ai.unfriendly,ac,FALSE);	//RJS 09Jun99
//DeadCode RJS 10Jul00 
 		SLong	massGone = SHAPE.ReduceLauncherLoad(ac,index,ammoGone);		//RJS 10Jul00
 
 		ac->SetWeaponForce(massGone,muzVel,muzdelay);
		if (ac == Persons2::PlayerSeenAC)								//RJS 10Jul00
		{
			PolyPitAnimData*	padptr = (PolyPitAnimData*)ac->Anim;
			padptr->prevammo[index] -= ammoGone;

			if ((weapon&LT_MASK)!=LT_BOMB)								//RJS 12Oct00
			{
 				padptr->actotalammoleft -= ammoGone;					//RJS 12Oct00
				padptr->accannonammoleft -= cannonGone;
			}
		}
	}				
	
	return(index);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DummyLandedEffect
//Author		Robert Slater
//Date			Wed 28 Oct 1998
//
//Description	For replay... should mirror LandedEffect, but without stuff
//				that could screw up Replay.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::DummyLandedEffect(AirStrucPtr	ac, SLong	landed,UByte atype)
{
	LandedEffect(ac,landed,FALSE,true);							//RJS 07Jun00

//DeadCode RJS 07Jun00 	WorldStuff			*world = mobileitem::currworld;
//DeadCode RJS 07Jun00 	AreaType			theArea = (AreaType)Three_Dee.GetLandType();
//DeadCode RJS 07Jun00 	Bool				onWater = FALSE;
//DeadCode RJS 07Jun00 	AircraftAnimData	*adptr = (AircraftAnimData*) ac->Anim;
//DeadCode RJS 07Jun00 	ULong oldmovecode;
//DeadCode RJS 07Jun00 	Bool		onSparky = FALSE;								//RJS 16May99
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 //	if (theArea!=atype)
//DeadCode RJS 07Jun00 //		_Error.SayAndQuit("Different area types");
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 	theArea=(AreaType)atype;
//DeadCode RJS 07Jun00 	switch (theArea)											//RJS 16May99
//DeadCode RJS 07Jun00 	{															//RJS 16May99
//DeadCode RJS 07Jun00 		case AT_sea:											//RJS 16May99
//DeadCode RJS 07Jun00 		case AT_stream:
//DeadCode RJS 07Jun00 			onWater = TRUE;										//RJS 16May99
//DeadCode RJS 07Jun00 			break;												//RJS 16May99
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 		case AT_village:
//DeadCode RJS 07Jun00 		case AT_denseTown:
//DeadCode RJS 07Jun00 		case AT_sparseTown:
//DeadCode RJS 07Jun00 		case AT_denseCity:
//DeadCode RJS 07Jun00 		case AT_sparseCity:
//DeadCode RJS 07Jun00 		case AT_cityBase:
//DeadCode RJS 07Jun00 		case AT_coastRock:
//DeadCode RJS 07Jun00 		case AT_urbanBuildup:
//DeadCode RJS 07Jun00 		case AT_whiteChalk: // does it?
//DeadCode RJS 07Jun00 			onSparky = TRUE;									//RJS 16May99
//DeadCode RJS 07Jun00 			break;												//RJS 16May99
//DeadCode RJS 07Jun00 	}															//RJS 16May99
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 	if (ac->IsHealthyMovecode(oldmovecode))
//DeadCode RJS 07Jun00 	{
//DeadCode RJS 07Jun00 		if (onWater == TRUE)
//DeadCode RJS 07Jun00 		{
//DeadCode RJS 07Jun00 			adptr->hasdust = TRUE;
//DeadCode RJS 07Jun00 			Manual_Pilot.DeathSequenceOverride(ac,AUTO_HITWATER);
//DeadCode RJS 07Jun00 			_Miles.PlayOnce(FIL_SFX_COLLISION_WATER,ac);
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 			switch (landed)
//DeadCode RJS 07Jun00 			{
//DeadCode RJS 07Jun00 			case _Collide.PROP_TOUCH:
//DeadCode RJS 07Jun00 			case _Collide.NOSE_TOUCH:
//DeadCode RJS 07Jun00 			{
//DeadCode RJS 07Jun00 				KillLauncher(ac,ac,*world);						//JIM 11Mar99
//DeadCode RJS 07Jun00 			}
//DeadCode RJS 07Jun00 			break;
//DeadCode RJS 07Jun00 			case _Collide.RIGHT_WING_TOUCH:
//DeadCode RJS 07Jun00 				SHAPE.ForceDamage(ac,ac,&adptr->RIGHTWINGIN,BS_DEAD);//JIM 11Mar99
//DeadCode RJS 07Jun00 				LaunchWaterTrail(ac,*world);
//DeadCode RJS 07Jun00 			break;
//DeadCode RJS 07Jun00 			case _Collide.LEFT_WING_TOUCH:
//DeadCode RJS 07Jun00 				SHAPE.ForceDamage(ac,ac,&adptr->LEFTWINGIN,BS_DEAD);//JIM 11Mar99
//DeadCode RJS 07Jun00 				LaunchWaterTrail(ac,*world);
//DeadCode RJS 07Jun00 			break;
//DeadCode RJS 07Jun00 			default:
//DeadCode RJS 07Jun00 				LaunchWaterTrail(ac,*world);
//DeadCode RJS 07Jun00 				break;
//DeadCode RJS 07Jun00 			}
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 			LaunchSplashMedium(ac,*world);
//DeadCode RJS 07Jun00 		}
//DeadCode RJS 07Jun00 		else
//DeadCode RJS 07Jun00 		{
//DeadCode RJS 07Jun00 			if (landed == _Collide.LANDED_OK)
//DeadCode RJS 07Jun00 			{
//DeadCode RJS 07Jun00 				// Perhaps throw up a bit of dirt...
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 				adptr->hasdust = FALSE;
//DeadCode RJS 07Jun00 				if (!adptr->justlanded)
//DeadCode RJS 07Jun00 				{
//DeadCode RJS 07Jun00 					adptr->justlanded = TRUE;
//DeadCode RJS 07Jun00 					_Miles.PlayOnce(FIL_SFX_TYRE_SCREECH1,ac);
//DeadCode RJS 07Jun00 				}
//DeadCode RJS 07Jun00 			}
//DeadCode RJS 07Jun00 			else
//DeadCode RJS 07Jun00 			{
//DeadCode RJS 07Jun00 				LaunchMushroomCloud(ac,10,*world);				//RJS 20Apr99
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 				switch (landed)
//DeadCode RJS 07Jun00 				{
//DeadCode RJS 07Jun00 				case _Collide.PROP_TOUCH:
//DeadCode RJS 07Jun00 				case _Collide.NOSE_TOUCH:
//DeadCode RJS 07Jun00 				case _Collide.RIGHT_WING_TOUCH:
//DeadCode RJS 07Jun00 				case _Collide.LEFT_WING_TOUCH:
//DeadCode RJS 07Jun00 				{
//DeadCode RJS 07Jun00 					SHAPE.DetatchAllVapourStreams(ac);
//DeadCode RJS 07Jun00 					LaunchBigExplosion(ac,*world,ac->shape);
//DeadCode RJS 07Jun00 					LaunchFingers(ac,*world);
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 					Manual_Pilot.DeathSequenceOverride(ac,AUTO_NOPPILOT);
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 					LaunchFire(ac,*world);						//RJS 28Jun99
//DeadCode RJS 07Jun00 				}
//DeadCode RJS 07Jun00 				break;
//DeadCode RJS 07Jun00 				default:
//DeadCode RJS 07Jun00 				{
//DeadCode RJS 07Jun00 					if (ac->vel_ < MPH100)						//RJS 11Dec98
//DeadCode RJS 07Jun00 					{
//DeadCode RJS 07Jun00 						if (onSparky)
//DeadCode RJS 07Jun00 							LaunchTransientTrail(ac,SparkShape,4,TRUE,*world,65536,TRUE);
//DeadCode RJS 07Jun00 						else
//DeadCode RJS 07Jun00 						{
//DeadCode RJS 07Jun00 							adptr->hasdust = TRUE;
//DeadCode RJS 07Jun00 							LaunchDustTrail2(ac,*world);
//DeadCode RJS 07Jun00 						}
//DeadCode RJS 07Jun00 					}
//DeadCode RJS 07Jun00 					else
//DeadCode RJS 07Jun00 					{
//DeadCode RJS 07Jun00 						LaunchFakeDelayedExplosion(ac,*world);
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 						SHAPE.DetatchAllVapourStreams(ac);
//DeadCode RJS 07Jun00 						if (!onSparky)
//DeadCode RJS 07Jun00 						{
//DeadCode RJS 07Jun00 							adptr->hasdust = TRUE;
//DeadCode RJS 07Jun00 							LaunchDustTrail2(ac,*world);
//DeadCode RJS 07Jun00 						}
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 						LaunchTransientTrail(ac,SmallFireballShape,300,FALSE,*world,65536);
//DeadCode RJS 07Jun00 						LaunchCrater(ac,*world);								//RJS 13May99
//DeadCode RJS 07Jun00 					}
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 					Manual_Pilot.DeathSequenceOverride(ac,AUTO_CRASHSKID);
//DeadCode RJS 07Jun00 				}
//DeadCode RJS 07Jun00 				break;
//DeadCode RJS 07Jun00 				}
//DeadCode RJS 07Jun00 			}
//DeadCode RJS 07Jun00 		}
//DeadCode RJS 07Jun00 	}
//DeadCode RJS 07Jun00 	else
//DeadCode RJS 07Jun00 	{
//DeadCode RJS 07Jun00 		if (_Replay.Playback)
//DeadCode RJS 07Jun00 		{
//DeadCode RJS 07Jun00 			if (onWater)
//DeadCode RJS 07Jun00 			{
//DeadCode RJS 07Jun00 				AircraftAnimData	*adptr = (AircraftAnimData*) ac->Anim;
//DeadCode RJS 07Jun00 				adptr->ENGINELEFT = BS_DEAD;			//Make fire invisible
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 				LaunchSplashMedium(ac,*world);
//DeadCode RJS 07Jun00 			}
//DeadCode RJS 07Jun00 			else
//DeadCode RJS 07Jun00 			{
//DeadCode RJS 07Jun00 				KillLauncher(ac,ac,*world);						//JIM 11Mar99
//DeadCode RJS 07Jun00 				LaunchFire(ac,*world);
//DeadCode RJS 07Jun00 			}
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 			//Is this really an aircraft??
//DeadCode RJS 07Jun00 			if (oldmovecode != 0xFFFFFFFF)
//DeadCode RJS 07Jun00 			{
//DeadCode RJS 07Jun00 				if (onWater)		//Fiddle movecode dirty, and sink
//DeadCode RJS 07Jun00 					_Replay.ReplayDeathMode = RDEATH_SKID;
//DeadCode RJS 07Jun00 				else
//DeadCode RJS 07Jun00 					_Replay.ReplayDeathMode = RDEATH_NULL;
//DeadCode RJS 07Jun00 			}
//DeadCode RJS 07Jun00 		}
//DeadCode RJS 07Jun00 		else
//DeadCode RJS 07Jun00 		{
//DeadCode RJS 07Jun00 			if (oldmovecode != AUTO_NOPPILOT)	//Strange if it is!
//DeadCode RJS 07Jun00 			{
//DeadCode RJS 07Jun00 				ac->pitch = ANGLES_0Deg;							//DAW 03Sep98
//DeadCode RJS 07Jun00 				ac->roll = ANGLES_0Deg;								//DAW 03Sep98
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 				if (onWater)
//DeadCode RJS 07Jun00 				{
//DeadCode RJS 07Jun00 					AircraftAnimData	*adptr = (AircraftAnimData*) ac->Anim;
//DeadCode RJS 07Jun00 					adptr->ENGINELEFT = BS_DEAD;			//Make fire invisible
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 					LaunchSplashMedium(ac,*world);
//DeadCode RJS 07Jun00 				}
//DeadCode RJS 07Jun00 				else
//DeadCode RJS 07Jun00 				{
//DeadCode RJS 07Jun00 					KillLauncher(ac,ac,*world);					//JIM 11Mar99
//DeadCode RJS 07Jun00 					if (ac==Manual_Pilot.ControlledAC2)					//RJS 31May00
//DeadCode RJS 07Jun00 						View_Object->SetToDeathView();				//RDH 02Sep98
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 					LaunchFire(ac,*world);
//DeadCode RJS 07Jun00 				}
//DeadCode RJS 07Jun00 
//DeadCode RJS 07Jun00 				//Is this really an aircraft??
//DeadCode RJS 07Jun00 				if (oldmovecode != 0xFFFFFFFF)
//DeadCode RJS 07Jun00 				{
//DeadCode RJS 07Jun00 					ac->vel_ = 0;
//DeadCode RJS 07Jun00 					if (onWater)		//Fiddle movecode dirty, and sink
//DeadCode RJS 07Jun00 						ac->movecode = AUTO_HITWATER;
//DeadCode RJS 07Jun00 					else
//DeadCode RJS 07Jun00 						ac->movecode = AUTO_NOPPILOT;
//DeadCode RJS 07Jun00 				}
//DeadCode RJS 07Jun00 			}
//DeadCode RJS 07Jun00 		}
//DeadCode RJS 07Jun00 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBridgeElement
//Author		Robert Slater
//Date			Fri 30 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchBridgeElement(	ItemPtr	launcher,
										Coords3D& noncorrectedgrpcoords,
										SWord	groupindex,
										WorldStuff&	worldptr)
{
	MyGroundVector	pos;
	ShapeNum		shapehit;
	UWord			ghdg;
	MinAnimData		*mad = (MinAnimData*) SHAPE.GetGroupItemAnimHdg(launcher,shapehit,groupindex,&pos,ghdg);
	UWord			animoffset = launcher->Anim.Offset(mad);//((UByteP)mad) - ((UByteP)&launcher->Anim[0]);

	if (mad)
	{
		mad->IsInvisible = 1;//Turn off the original bridge element...

		TransientItem*	newitem;
		newitem = SimplifiedSpriteLaunch(	launcher,
											shapehit,
											1000,
											MOBILE_DEADBRIDGE);
		
		if (newitem)
		{
			newitem->World = noncorrectedgrpcoords;
			newitem->TransRandom = animoffset & 0x0FFF;
			newitem->hdg = (Angles) ghdg;

			SWord	roll,pitch;
			UWord	rp = 0;

			roll = Math_Lib.rnd();
			pitch = Math_Lib.rnd();

			// top 4 bits are for pitch and roll variations...
			if (roll < 0)
			{
				//-ve
				if (roll < -16384)
					rp = 3;			//fast
				else
					rp = 2;			//slow
			}
			else
			{
				//+ve
				if (roll > 16384)
					rp = 1;			//fast
				else
					rp = 0;			//slow

			}

			rp <<= 2;

			if (pitch < 0)
			{
				//-ve
				if (pitch < -16384)
					rp |= 3;			//fast
				else
					rp |= 2;			//slow
			}
			else
			{
				//+ve
				if (pitch > 16384)
					rp |= 1;			//fast
				else
					rp |= 0;			//slow

			}

			newitem->TransRandom |= (rp << 12);

			MinAnimData*	el_mad = (MinAnimData*) newitem->Anim;
			el_mad->itemstate = DEAD;

			AddTransientItemToWorld(newitem, worldptr);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileDeadBridge
//Author		Robert Slater
//Date			Fri 30 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileDeadBridge(TransientItemPtr transit, WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;
	UWord	roff = transit->TransRandom;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		SWord	roll,pitch;
		roll = roff & 0xF000;
		roll >>= 12;
		pitch = roll & 3;

		roll >>= 2;

		//after 4 secs, should have tilted 90deg...
		if (roll < 0)
			roll--;
		else
			roll++;

		roll *= 40;

		if (pitch < 0)
			pitch--;
		else
			pitch++;

		pitch *= 30;

		transit->roll += (Angles) roll;	
		transit->pitch += (Angles) pitch;

		GAndFrictionFixedPitch(transit,RetardedDrag);			//RJS 22Dec99

		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			SLong	groundheight = GetGroundLevel(transit);		//RJS 14Apr99
			if (transit->World.Y <= groundheight)
			{
				transit->World.Y = groundheight;
				transit->LaunchTime=0;

				LaunchSplashLarge(transit,world);
			}
		}
	}
	else
	{
		// Remove the transient bridge element, and turn on the real bridge element to dead....
		MinAnimData*	mad;
		animptr			adptr = transit->Launcher->Anim;		//RJS 21Apr99
																//RJS 21Apr99
		adptr += (roff & 0x0FFF);								//RJS 21Apr99

		mad = (MinAnimData*) adptr;								//RJS 21Apr99
		mad->IsInvisible = 0;//Turn the element back on in its new home splashing about in the water...

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDirtyFingers
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
void	TransObj::LaunchDirtyFingers(mobileitem*	launcher, WorldStuff&	worldptr)
{
	if (desiredFPS <= realFPS)					//RJS 11Jun99
	{
		TransientItem*		newitem;
		MoveGunAnimData*	adptr;
		WeapAnimData*		weapon;
		UWord	newhdg;
		UWord	newpitch;
		SWord	sin_ang, cos_ang;
		SWord	sin_ang2, cos_ang2;
		SLong	vel;
		SLong	velhori,vely;
		SLong	temp;
		SLong	count;
//DeadCode RJS 20Oct00 		SLong	groundheight = GetGroundLevel(launcher) + METRES01;	//RJS 14Apr99
		SLong	fingercnt = 3 + Math_Lib.rnd(4);

		for (count = 0; count < fingercnt; count++)
		{
			newitem = SimplifiedSpriteLaunch(launcher,			
											PLUME2,
											350,MOBILE_DEBRIS);
			if (newitem)
			{
				adptr = (MoveGunAnimData*)newitem->Anim;
				weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

				SHAPE.InitTrailFields((UByteP)weapon,0,-1,LT_MUDDY);

				LaunchVapourStream((UByteP)weapon,PLUME2);	

				newhdg = Math_Lib.rnd();

	//			newitem->World.Y = groundheight;
				newitem->hdg = (Angles) newhdg;			
				newitem->vel_y = 100000 + (Math_Lib.rnd(200)*1000);//RJS 16Nov99
//DEADCODE CSB 09/11/99 				newitem->velhori = 50 + Math_Lib.rnd(70);
				Float velhori = 50000. + Float(Math_Lib.rnd(70)*1000);//RJS 16Nov99
				Float sin_ang, cos_ang;										 //CSB 09/11/99
				Math_Lib.high_sin_cos(Angles(newhdg), sin_ang, cos_ang);	 //CSB 09/11/99
				newitem->vel_x = (velhori * sin_ang);							 //CSB 09/11/99
				newitem->vel_z = (velhori * cos_ang);							 //CSB 09/11/99

				newitem->roll = ANGLES_0Deg;
				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFlash
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
void	TransObj::LaunchFlash(mobileitem*	launcher, UByte	damsize, WorldStuff&	worldptr)
{
	TransientItem*		newitem;
	
//DeadCode MS 30Nov98	newitem = SimplifiedSpriteLaunch((mobileitem*)launcher,EXPLO,3,MOBILE_STATIONARY);
	newitem = SimplifiedSpriteLaunch((mobileitem*)launcher,FLASH,30,MOBILE_STATIONARY);
	if (newitem)
	{
//DeadCode RJS 23May00 		newitem->DrawOffset = 4096;
		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFingersFire
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
void	TransObj::LaunchFingersFire(mobileitem* launcher,
									WorldStuff& worldptr	)
{
	if (WithinVisibleRange(launcher->World,200000))				//RJS 30Apr99
	{
		TransientItem*	newitem;
		UWord	newhdg;
		SLong	vel;
		SLong	vely;
		SLong	count;
		SLong	cntrand = 3 + Math_Lib.rnd(4);
		SLong	groundheight = GetGroundLevel(launcher) + 250;		//RJS 14Apr99

		if (launcher->Status.size == AirStrucSize)
			vely = 150;
		else
			vely = 0;

		if (desiredFPS > realFPS)					//RJS 28May99
			cntrand = 2;										//RJS 28May99

		for (count = 0; count < cntrand; count++)
		{
			newitem = LaunchUnguidedMissile(launcher,			
											NapalmFingerShape,	
											1000,MOBILE_DEBRIS);
			if (newitem)
			{
				WeapAnimData*	weapon;
				MoveGunAnimData* adptr = (MoveGunAnimData*)newitem->Anim;

				weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

				SHAPE.InitTrailFields((UByteP)weapon,0,32000,LT_FUEL);

				LaunchVapourStream((UByteP)weapon,NapalmFingerShape);

				newhdg = Math_Lib.rnd();

				vel = 200000 + (Math_Lib.rnd(150)*1000);		//RJS 16Nov99

				newitem->World.Y = groundheight;
				newitem->hdg = (Angles) newhdg;			
				newitem->vel_y = 350000-vel;		 //CSB 09/11/99
//DEADCODE CSB 09/11/99 				newitem->velhori = vel;		
				Float sin_ang, cos_ang;									 //CSB 09/11/99
				Float	tmpvel = Float(vel);
				Math_Lib.high_sin_cos(Angles(newhdg), sin_ang, cos_ang); //CSB 09/11/99
				newitem->vel_x = (tmpvel * sin_ang);							 //CSB 09/11/99
				newitem->vel_z = (tmpvel * cos_ang);							 //CSB 09/11/99
				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTossedShape
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
void	TransObj::LaunchTossedShape(mobileitem*	launcher, SByte	groupindex,Coords3D hittercoords,SLong strength, WorldStuff&	worldptr)
{
	if (WithinVisibleRange(launcher->World,300000))				//RJS 30Apr99
	{
		if (launcher->Status.size != TransientSize)
		{
			MyGroundVector	pos;
			UWord			realhdg;
			ShapeNum		shapehit;
			MinAnimData		*mad = (MinAnimData*) SHAPE.GetGroupItemAnimHdg(launcher,shapehit,groupindex,&pos,realhdg);
			UWord			animoffset = launcher->Anim.Offset(mad);// ((UByteP)mad) - ((UByteP)&launcher->Anim[0]);
			SLong			shpsize;

			if (mad)
			{
				ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shapehit);
				shpsize = sdptr->Size << 4;

				if (shpsize < 1000)
				{
					SLong	dx,dz,dist;
					SWord	thehdg;

					// Throw from the direction the weapon came from...
					dx = pos.gx - hittercoords.X;
					dz = pos.gz - hittercoords.Z;

					thehdg = Math_Lib.arctan(dz,dx);
					if (dx > 0)
						thehdg = ANGLES_90Deg - thehdg;
					else
						thehdg = ANGLES_270Deg - thehdg;

					//50m is minimum toss damage...
					if (strength > 0)
					{
						SLong	vely,maxvel,thesize;
						SLong	maxtoss;
						SLong	hdgintercept = SWord(UWord(thehdg) - realhdg);
						SLong	pitchintercept;
						SWord	pitchmag,hdgmag,hpmag;

						dist = Math_Lib.distance3d(dx,dz,0);
						dist -= shpsize;
						if (dist < 0)
							dist = 0;

						hdgintercept <<= 8;
						hdgintercept /= ANGLES_90Deg;
						if (hdgintercept > 256)
						{
							hdgintercept = 0;
							pitchintercept = 256 - hdgintercept;
						}
						else
							pitchintercept = 256 - hdgintercept;

						pitchmag = (pitchintercept * 127)>>8;		//max of 90degree flip in 1 sec ish
						hdgmag = (hdgintercept * 127)>>8;

						hpmag = hdgmag << 8;
						hpmag |= pitchmag;

						maxtoss = 5000 - dist;
						thesize = 1000 - shpsize;

						maxvel = (500 * strength) / 31;	//31 is max strength..
						maxvel *= thesize;
//DEADCODE CSB 09/11/99 						maxvel /= 1000;

						if (launcher->Status.size == FORMATIONSIZE)//RJS 23Jun99
						{
 							if (	!launcher->Status.deadtime )
//DeadCode RJS 05Nov99 								&&	(launcher->movecode != AUTO_NOPPILOT)	)//RJS 01Jul99
 								FormationItemPtr(*launcher)->BreakForm(); //JIM 09/09/99
						}

						// 60degree throw max...
						if (maxtoss > 0)
						{
							vely = (maxtoss * maxvel * 6) / 9;
//DEADCODE CSB 09/11/99 							vely /= 5000;
							vely /= 5;
						}
						else
							vely = 0;

						mad->IsInvisible = 1;//Turn off the original element...

						TransientItem*	newitem;
						newitem = SimplifiedSpriteLaunch(	launcher,
															shapehit,
															1000,
															MOBILE_ATEAM);
				
						if (newitem)
						{
							newitem->World.X = pos.gx;
							newitem->World.Y = pos.gy;
							newitem->World.Z = pos.gz;
							newitem->TransRandom = animoffset;
							newitem->hdg = (Angles) realhdg;
							newitem->vel_y = vely;
//DEADCODE CSB 09/11/99 							newitem->velhori = maxvel - vely;
							newitem->vel_x = thehdg * 1000;		 //CSB 09/11/99
							newitem->vel_z = pitchmag * 1000;	 //CSB 09/11/99

							MinAnimData*	el_mad = (MinAnimData*) newitem->Anim;
							el_mad->itemstate = mad->itemstate;

							if (launcher->Status.size >= MobileSize)
							{
								launcher->movecode = AUTO_NOPPILOT;
								if (launcher==Persons2::PlayerSeenAC)	//shouldn't be, but it's late, ok?
									Persons2::PlayerGhostAC->movecode=AUTO_NOPPILOT;
							}

							AddTransientItemToWorld(newitem, worldptr);
						}
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileCollapse
//Author		Robert Slater
//Date			Wed 18 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileCollapse(TransientItemPtr transit, WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;
	UWord	roff = transit->TransRandom;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		SWord	roll,pitch;
		roll = roff & 0xF000;
		roll >>= 12;
		pitch = roll & 3;

		roll >>= 2;

		//after 4 secs, should have tilted 90deg...
		if (roll < 0)
			roll--;
		else
			roll++;

		roll *= 81;

		if (pitch < 0)
			pitch--;
		else
			pitch++;

		pitch *= 60;

		transit->roll += (Angles) roll;	
		transit->pitch += (Angles) pitch;

		GAndFrictionFixedPitch(transit,0);			//RJS 22Dec99

		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			UByte	theArea;
			SLong	groundheight = GetGroundLevel(transit,theArea);//RJS 28Apr99
			if (transit->World.Y <= groundheight)
			{
//DeadCode RJS 28Apr99				UByte	theArea = Three_Dee.GetLandType();		//RJS 27Nov98

				Coords3D	hitcoords;

				transit->World.Y = groundheight;
				transit->LaunchTime=0;

				hitcoords = transit->World;

				DoImpactGround(transit,hitcoords,theArea);
			}
		}
	}
	else
	{
//DeadCode RJS 23Dec99 		MinAnimData*	mad;
//DeadCode RJS 23Dec99 		animptr			adptr = transit->Launcher->Anim;		//RJS 21Apr99
//DeadCode RJS 23Dec99 																//RJS 21Apr99
//DeadCode RJS 23Dec99 		adptr += (roff & 0x0FFF);								//RJS 21Apr99
//DeadCode RJS 23Dec99 																//RJS 21Apr99
//DeadCode RJS 23Dec99 		mad = (MinAnimData*) adptr;								//RJS 21Apr99
//DeadCode RJS 23Dec99 		mad->IsInvisible = 0;//Turn the element back on in its new home splashing about in the water...

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDirtyBuildingFingers
//Author		Mark Shaw (Yeah, right!)
//Date			Mon 30 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDirtyBuildingFingers(mobileitem*	launcher, UWord	direction, WorldStuff&	worldptr)
{
	if (desiredFPS <= realFPS)					//RJS 11Jun99
	{
		if (WithinVisibleRange(launcher->World,300000))				//RJS 30Apr99
		{
			TransientItem*		newitem;
			MoveGunAnimData*	adptr;
			WeapAnimData*		weapon;
			UWord	newhdg;
			UWord	newpitch;
			SWord	sin_ang, cos_ang;
			SWord	sin_ang2, cos_ang2;
			SLong	vel;
			SLong	velhori,vely;
			SLong	temp;
			SLong	count;
			SLong	fingercnt = 3 + Math_Lib.rnd(4);

			for (count = 0; count < fingercnt; count++)
			{
				newitem = SimplifiedSpriteLaunch(launcher,			
												PLUME2,
												350,MOBILE_DEBRIS);
				if (newitem)
				{
					adptr = (MoveGunAnimData*)newitem->Anim;
					weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

					SHAPE.InitTrailFields((UByteP)weapon,0,-1,LT_MUDDY);

					LaunchVapourStream((UByteP)weapon,PLUME2);	

					newhdg = direction + (Math_Lib.rnd(ANGLES_180Deg) - ANGLES_90Deg);

					newitem->hdg = (Angles) newhdg;			
					newitem->vel_y = 100000 + (Math_Lib.rnd(100)*1000);//RJS 16Nov99
//DEADCODE CSB 09/11/99 					newitem->velhori = 150 + Math_Lib.rnd(70);
					Float velhori = 150000. + Float(Math_Lib.rnd(70)*1000);//RJS 16Nov99
					Float sin_ang, cos_ang;									 //CSB 09/11/99
					Math_Lib.high_sin_cos(Angles(newhdg), sin_ang, cos_ang); //CSB 09/11/99
					newitem->vel_x = (velhori * sin_ang);						 //CSB 09/11/99
					newitem->vel_z = (velhori * cos_ang);						 //CSB 09/11/99
					
					newitem->roll = ANGLES_0Deg;
					AddTransientItemToWorld(newitem,worldptr);
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSmallThug
//Author		Robert Slater
//Date			Thu 3 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchSmallThug(	item*		launcher,
									item*		destination,
									ShapeNum	theshape,
									SLong		gindex,
									SLong		lifeleft	)
{
	TransientItem*	newitem;
	WorldStuff*		worldptr = mobileitem::currworld;
	ShapeNum		shapehit;
	MyGroundVector	pos;
	MinAnimData		*mad = (MinAnimData*) SHAPE.GetGroupItemAnim(destination,shapehit,gindex,&pos);
	UWord			animoffset = destination->Anim.Offset(mad);//(UByteP)mad - (UByteP)&destination->Anim[0];

	newitem = SimplifiedSpriteLaunch(	destination,	
										theshape,		
										lifeleft,	
										MOBILE_SMALLTHUG);
	
	if (newitem)
	{
		mad->IsBullied = 1;

		ThugAnimData	*adptr = (ThugAnimData*) newitem->Anim;

		if (adptr)
			adptr->panimoff = animoffset;

		if (launcher->Status.size == TRANSIENTSIZE)								//RJS 18Jun99
			newitem->Launcher = ((TransientItemPtr)launcher)->Launcher;
		else
			newitem->Launcher = launcher;

		newitem->Target = destination;
		newitem->World.X = pos.gx;
		newitem->World.Y = pos.gy;
		newitem->World.Z = pos.gz;

		AddTransientItemToWorld(newitem,*worldptr);
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		RDH 02/03/99
//Date			
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ChooseMusic(AirStrucPtr	ac)
{
	if (ac==Manual_Pilot.ControlledAC2)					
	{
			_Miles.SequenceAudible(MOOD_DOOMED);		//RDH 01/03/99
	}else if (ac->PlayerInGroup())
	{
			_Miles.SequenceAudible(FIL_MUSIC_SAD);		//RDH 01/03/99
	}else
	{
		if (ac->nationality == Manual_Pilot.ControlledAC2->nationality)
			_Miles.SequenceAudible(MOOD_ANGRY);		//RDH 01/03/99
		else
			_Miles.SequenceAudible(MOOD_HOPEFUL);		//RDH 01/03/99
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExplodeAC
//Author		Robert Slater
//Date			Fri 4 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ExplodeAC(AirStrucPtr	ac, ItemPtr killer, WorldStuff&	worldptr,Bool setdamage)
{
//DeadCode RJS 4Sep00 	Float	sin_ang,cos_ang;								
//DeadCode RJS 4Sep00 	SLong	vely, velx, velz;						
//DeadCode RJS 4Sep00 	Float	velhori, vel;

	if (ac == Persons2::PlayerSeenAC)						//RJS 30Aug00
		_Miles.StopEngine();								//RJS 30Aug00

	MinAnimData*	mad = (MinAnimData*) ac->Anim;			//RJS 07Jun00
	if (!mad->IsInvisible && (ac->shape != PDEATH))									//RJS 20May99
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(ac->shape);

		ChooseMusic(ac);

		// Explode!!
		LaunchBigExplosion(ac,worldptr,ac->shape);
		LaunchFingers(ac,worldptr);

		if (WithinVisibleRange(ac->World,200000))
		{
			if (Math_Lib.rnd() > 32767)
				LaunchAircraftFire(ac,ac->World,worldptr);
			else
				LaunchTransientTrail(ac,FireballShape,500,FALSE,worldptr,400);
		}

#ifndef NDEBUG
#ifdef COLTRACE
	UWord cw=GETFPCW();
	::AfxTrace("...EXPLODED!: 0x00%x\n",ac);
	SETFPCW(cw);
#endif
#endif

		if (ac==Manual_Pilot.ControlledAC2)
		{
			if (HitTheDeck)										//RJS 11Jun99
				Squad_Diary.UpdatePlayerLog(EFS_PILOTLOST);				//RJS 29Oct00

//DeadCode RJS 30Aug00 			_Miles.StopEngine();							
															
			if (View_Object)
			{
				SLong	groundheight = GetGroundLevel(ac);		//RJS 14Apr99
				if ((ac->World.Y-groundheight) > 50000) // max height
					View_Object->SetToDeathView(DEATH_AIRTOAIR);
				else
					View_Object->SetToDeathView(DEATH_AIRTOGROUND);
			}
		}

		if (setdamage)
		{
			if (sdptr->AnimDataSize == AIRCRAFTANIM)
			{
				AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;

				SHAPE.ForceDamage(ac,killer,&adptr->TAIL,BS_DEAD,32);//JIM 11Mar99
				SHAPE.ForceDamage(ac,killer,&adptr->FINLEFT,BS_DEAD,32);//JIM 11Mar99
				SHAPE.ForceDamage(ac,killer,&adptr->FINRIGHT,BS_DEAD,32);//JIM 11Mar99
				SHAPE.ForceDamage(ac,killer,&adptr->RIGHTWINGOUT,BS_DEAD,32);//JIM 11Mar99
				SHAPE.ForceDamage(ac,killer,&adptr->LEFTWINGOUT,BS_DEAD,32);//JIM 11Mar99
				SHAPE.ForceDamage(ac,killer,&adptr->LEFTWINGIN,BS_DEAD,32);//JIM 11Mar99
				SHAPE.ForceDamage(ac,killer,&adptr->RIGHTWINGIN,BS_DEAD,32);//JIM 11Mar99
			}
			else if (sdptr->AnimDataSize == SIMPLEAIRCRAFTANIM)
			{
				SimpleAircraftAnimData*	adptr = (SimpleAircraftAnimData*) ac->Anim;

				SHAPE.ForceDamage(ac,killer,&adptr->RIGHTWINGOUT,BS_DEAD,32);//JIM 11Mar99
				SHAPE.ForceDamage(ac,killer,&adptr->LEFTWINGOUT,BS_DEAD,32);//JIM 11Mar99
				SHAPE.ForceDamage(ac,killer,&adptr->LEFTWINGIN,BS_DEAD,32);//JIM 11Mar99
				SHAPE.ForceDamage(ac,killer,&adptr->RIGHTWINGIN,BS_DEAD,32);//JIM 11Mar99
			}
		}

// Kill the bloke aboard ac...
		if (sdptr->AnimDataSize == AIRCRAFTANIM)				//RJS 07Jun00
		{
			AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
			adptr->CANOPY = BS_DEAD;
		}

		if (!_Replay.Playback)									//RJS 07Jun00
		{
			if (ac->nationality == Manual_Pilot.ControlledAC2->nationality)
			{
				if (!HitTheDeck)									//RDH 09May99
					_DamageChat.PlayerSideBlewUp(ac);
				else
					_DamageChat.PlayerSidePiledIn(ac);
			}
			else
			{
				if (killer->Status.size == AIRSTRUCSIZE)		//RJS 23Jun00
					_DamageChat.OtherSideBlewUp((AirStrucPtr)*killer,(AirStrucPtr)*ac,false);//RJS 07Jun00
			}
		}

		mad->IsInvisible = 1;									//RJS 07Jun00
		mad->itemstate = DEAD;											//RJS 4Sep00

		if (_DPlay.Implemented)
		{
			ac->Status.deaded=TRUE;
			if (!ac->Status.deadtime)									//AMM 20Sep00
				ac->Status.deadtime=1;									//AMM 20Sep00
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGunDot
//Author		Robert Slater
//Date			Mon 7 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchGunDot(mobileitem*	launcher, WorldStuff&	worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,	
										SPARK,		
										10,	
										MOBILE_STATIONARY);
	
	if (newitem)
		AddTransientItemToWorld(newitem,worldptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSmallFlash
//Author		Robert Slater
//Date			Tue 8 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchSmallFlash(mobileitem* launcher,WorldStuff& worldptr,Bool heightfix)
{
	TransientItem*	newitem;

	newitem = RelativeSpriteLaunch(launcher,launcher->shape,EXPLO,20,MOBILE_BIGEXP);//RJS 20Apr98
	if (newitem)
	{
		if (heightfix)											//RJS 05May99
			newitem->World.Y += 200;							//RJS 05May99

		if ((launcher->Status.size >= MovingSize) && (launcher->Status.size != TransientSize))//RJS 16Nov98
			newitem->Target = launcher;							//RJS 16Nov98

		_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_OILDRUM1+Math_Lib.rnd(5)), newitem);
		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSparkTrail
//Author		Robert Slater
//Date			Fri 11 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchTransientTrail(mobileitem* launcher,
									ShapeNum	theShape,
									SLong		maxlife,
									Bool		throwit,
									WorldStuff& worldptr,
									SLong		totaltime,
									Bool		onGround	)
{
	TransientItem*	newitem;

	newitem = LaunchGuidedMissile(launcher,launcher,ShockwaveShape,Math_Lib.rnd(50),MOBILE_RICOCHET);
	if (newitem)
	{
		if (totaltime < 65536)									//RJS 14May99
			newitem->TmpLaunchTime = totaltime;					//RJS 19May99
		else													//RJS 14May99
			newitem->TmpLaunchTime = 65535;						//RJS 19May99

		newitem->TransRandom = theShape;	//the shape...
		newitem->hdg = (Angles) throwit;		//We can throw in all directions...
		newitem->pitch = (Angles) maxlife;	//Max lifetime...
		if (onGround)
			newitem->TransRandom |= 0x8000;

		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillLauncherComms
//Author		Andy McMaster
//Date			Fri 8 Jan 1999
//
//Description	Explode effect... once received ac_collision packet.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::KillLauncherComms(AirStrucPtr	ac)
{
	WorldStuff	*world = mobileitem::currworld;

	SHAPE.DetatchAllVapourStreams(ac);

//DeadCode AMM 24Mar99	if (ac==Persons2::PlayerSeenAC)
//DeadCode AMM 24Mar99	{
//DeadCode AMM 12Jul00 	if (!_Replay.Record)
//DeadCode AMM 12Jul00 	{
//DeadCode AMM 12Jul00 //DeadCode AMM 15Apr99		if (Manual_Pilot.DeathSequenceOverride(ac,AUTO_SPIRAL2GROUND,true))
//DeadCode AMM 12Jul00 		{
//DeadCode AMM 12Jul00 			// what is the killer??
//DeadCode AMM 12Jul00 			ExplodeAC(ac,ac,*world,FALSE);						//JIM 11Mar99
//DeadCode AMM 12Jul00 		}
//DeadCode AMM 12Jul00 	}
//DeadCode AMM 12Jul00 	else
//	if (ac==Persons2::PlayerSeenAC)
	{
		ExplodeAC(ac,ac,*world,FALSE);						
	}

	Art_Int.BreakOff(ac);
	ac->BreakForm();


//DeadCode AMM 24Mar99	}
//DeadCode AMM 24Mar99	else
//DeadCode AMM 24Mar99	{
//DeadCode AMM 24Mar99		ExplodeAC(ac,*world,FALSE);
//DeadCode AMM 24Mar99	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchJunk
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
void	TransObj::LaunchJunk(	mobileitem*	launcher,
								ShapeNum	theShape,
								Coords3D&	pos,
								WorldStuff&	worldptr		)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										theShape,
										50,
										MOBILE_GANDF);
	if (newitem)
	{
		newitem->hdg = (Angles) (launcher->hdg + Math_Lib.rnd(ANGLES_30Deg) - ANGLES_15Deg);
		newitem->pitch = (Angles) Math_Lib.rnd();

		newitem->vel_ = launcher->vel_;
		newitem->vel_y = launcher->vel_y;
//DEADCODE CSB 09/11/99 		newitem->velhori = launcher->velhori;
		newitem->vel_x = launcher->vel_x; //CSB 09/11/99
		newitem->vel_z = launcher->vel_z; //CSB 09/11/99

		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTimeBomb
//Author		Robert Slater
//Date			Wed 10 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchTimeBomb(ItemPtr	launcher,ULong animoffset,WorldStuff& worldptr)
{
	animptr	AnimPtr = launcher->Anim;
	ULong	currdam = AnimPtr[(int)animoffset];
	ULong	maxtime = (15000*(BS_DEAD-currdam))/(BS_DEAD-BS_DAMLV2);//5 mins...

	TransientItem*	newitem;
	newitem = SimplifiedSpriteLaunch(	launcher,
										EMPTY,
										maxtime + Math_Lib.rnd(maxtime),
										MOBILE_SCALEFIST	);
	if (newitem)
	{
		MinAnimData*	mad = (MinAnimData*) newitem->Anim;
		mad->IsInvisible = 1;

		newitem->TransRandom = animoffset;
 		newitem->DrawOffset = (newitem->LaunchTime / 2);

		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileScaleFist
//Author		Robert Slater
//Date			Wed 10 Feb 1999
//
//Description	Hits a specific damage anim byte over a period of time...
//				(at the moment, twice...)
//				(assumes it has been triggered at BS_DAMLV2)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileScaleFist(TransientItemPtr transit,WorldStuff&)
{
	SWord	frametime = Timer_Code.FRAMETIME;

	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		transit->LaunchTime -= frametime;
		if (transit->LaunchTime <= transit->DrawOffset)
		{
			animptr	animPtr = transit->Launcher->Anim;
			UWord	damval = animPtr[transit->TransRandom];

			damval += ((BS_DEAD-BS_DAMLV2)/2);

			transit->DrawOffset = 0;

			SHAPE.ForceDamage(transit->Launcher,transit->Launcher,&animPtr[transit->TransRandom],(BitStates)damval,32);//JIM 11Mar99
		}
	}
	else
	{
		animptr	animPtr = transit->Launcher->Anim;				//RJS 21Apr99

		SHAPE.ForceDamage(transit->Launcher,transit->Launcher,&animPtr[transit->TransRandom],BS_DEAD,32);//RJS 21Apr99

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTransientItemToTrailList
//Author		Robert Slater
//Date			Thu 18 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::AddTransientItemToTrailList(TransientItemPtr	newitem)
{
	SLong				newslot = StaticTrailIndex;
//Dead	TransientItemPtr	slist = StaticTrailList[newslot];

	while (StaticTrailList[newslot].item)						//RJS 13May99
	{
		if (newslot < MaxTrails)								//RJS 06Apr99
			newslot++;
		else
			break;
	}

	while (StaticTrailList[newslot].item)						//RJS 13May99
	{
		if (newslot > 0)
			newslot--;
		else
			break;
	}
#ifndef NDEBUG
#pragma message("AddTransientItemToTrailList debug!!")
	for (int index=0; index < MaxTrails; index++)
	{
		//Should NEVER get here!!!!
		if (StaticTrailList[index].item==newitem)				//RJS 13May99
			INT3;
	}
#endif

	StaticTrailIndex = newslot;
	if (StaticTrailList[StaticTrailIndex].item==NULL)			//RJS 13May99
	{
		StaticTrailList[StaticTrailIndex].item = newitem;		//RJS 13May99
		StaticTrailList[StaticTrailIndex].time = View_Object->TimeOfDay();//RJS 13May99
		StaticTrailCnt++;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RemoveTransientItemFromTrailList
//Author		Robert Slater
//Date			Thu 18 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::RemoveTransientItemFromTrailList(TransientItemPtr	deaditem)
{
	SLong	index;
	for (index=0; index < MaxTrails; index++)					//RJS 08Apr99
	{
		if (StaticTrailList[index].item == deaditem)			//RJS 13May99
		{
			StaticTrailList[index].item = NULL;					//RJS 13May99
			StaticTrailList[index].time = 0xFFFFFFFF;			//RJS 13May99
			StaticTrailIndex = index;			//next free slot...
			StaticTrailCnt--;					
			break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CleanUpTrailList
//Author		Robert Slater
//Date			Thu 18 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::CleanUpTrailList()
{
	SmokeTrailAnimData*		adptr;
	SLong	index;
	for (index=0; index < MaxTrails; index++)					//RJS 06Apr99
	{
//DeadCode DAW 21Jun99 		if (StaticTrailList[index].item)						//RJS 13Jun99
//DeadCode DAW 21Jun99 		{
//DeadCode DAW 21Jun99 			Coords3DList*	apoint;
//DeadCode DAW 21Jun99 #ifndef	NDEBUG
//DeadCode DAW 21Jun99 #ifdef	MEMTRACE
//DeadCode DAW 21Jun99 	UWord cw=GETFPCW();
//DeadCode DAW 21Jun99 	::AfxTrace("TRANSKILL:\n");
//DeadCode DAW 21Jun99 	SETFPCW(cw);
//DeadCode DAW 21Jun99 #endif
//DeadCode DAW 21Jun99 #endif
//DeadCode DAW 21Jun99 			adptr = (SmokeTrailAnimData*) StaticTrailList[index].item->Anim;
//DeadCode DAW 21Jun99 			apoint = (Coords3DList*) adptr->thelist;
//DeadCode DAW 21Jun99 			apoint->Wipe();
//DeadCode DAW 21Jun99 
//DeadCode DAW 21Jun99 			adptr->thelist = NULL;
//DeadCode DAW 21Jun99 		}

		StaticTrailList[index].item = NULL;						//RJS 13May99
		StaticTrailList[index].time = 0xFFFFFFFF;				//RJS 13May99
	}

	StaticTrailCnt = 0;											//RJS 18Feb99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScanTrailListAndSave
//Author		Robert Slater
//Date			Thu 18 Feb 1999
//
//Description	For replay blocks...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ScanTrailListAndSave()
{
//DeadCode DAW 06Apr99	SLong	index;
//DeadCode DAW 06Apr99	for (index=0; index < MaxTransients; index++)
//DeadCode DAW 06Apr99	{
//DeadCode DAW 06Apr99
//DeadCode DAW 06Apr99
//DeadCode DAW 06Apr99	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchReplayTrail
//Author		Robert Slater
//Date			Thu 18 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchReplayTrail(Coords3D&			cpos,
									UByteP				usmkptr,
									UByteP				thelist	)
{
	ReplaySmlSmkStruc*	smkptr = (ReplaySmlSmkStruc*) usmkptr;
	TransientItemPtr	newitem;
	newitem = SimplifiedSpriteLaunch(	(MobileItemPtr)Persons2::ConvertPtrUID((UniqueID)smkptr->uniqueid),
										SMKSHP,	
										smkptr->lifetime,
										MOBILE_STATIONARY);

	if (newitem)
	{
		WorldStuff*			worldptr = mobileitem::currworld;
		SmokeTrailAnimData*	adptr = (SmokeTrailAnimData*) newitem->Anim;

		newitem->World.X = cpos.X;
		newitem->World.Y = cpos.Y;
		newitem->World.Z = cpos.Z;

		adptr->weaponlaunchers[0].hdg = -1;
		adptr->weaponlaunchers[0].pitch = -1;
		adptr->weaponlaunchers[0].LauncherType = LT_VAPOUR;	//RJS 13Apr99
		adptr->nopoints = smkptr->nopoints;
		adptr->thelist = (ULong) thelist;
		adptr->lifetime = smkptr->lifetime;
		adptr->SmkDescIndex = smkptr->smkindex;
		adptr->currTime = smkptr->currTime;						//RJS 16Jun99

		AddTransientItemToTrailList(newitem);
		AddTransientItemToWorld(newitem,*worldptr);

		trailcounter++;											//DAW 06Apr99
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchNapalmImpacted
//Author		Robert Slater
//Date			Fri 19 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchNapalmImpacted(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	int				dx, dz, thedist;
//DeadCode RJS 20Oct00 	SWord			hdg = launcher->hdg;
//DEADCODE CB 09/11/99 	SWord			sin_ang,cos_ang;
	int				i;
	SLong			wx, wz, noblobs;
//DeadCode RJS 20Oct00 	SWord			timedelay = 0;

	wx = launcher->World.X;
	wz = launcher->World.Z;

	thedist = 750;
	
//DEADCODE CB 09/11/99 	Math_Lib.high_sin_cos((Angles)hdg,sin_ang,cos_ang);

	newitem = SimplifiedSpriteLaunch((mobileitem*)launcher,EXPLO,20,MOBILE_STATIONARY);
	if (newitem)
	{
//DeadCode RJS 23May00 		newitem->DrawOffset = 100;
		AddTransientItemToWorld(newitem,worldptr);
	}

	newitem = SimplifiedSpriteLaunch(	launcher,			
										NAPBLB,									//RJS 15Dec99
										240,			
										MOBILE_BURNIT);		
	if (newitem)											
	{
//DeadCode RJS 21Apr99		newitem->World.Y = GetGroundLevel(newitem);				//RJS 14Apr99

		Three_Dee.pMigLand->GetShadowAngles(newitem->World,newitem->hdg,newitem->pitch,newitem->roll);

		newitem->Status.deadtime = 1;	// no collision...

		newitem->TransRandom = 50 << 8;
		newitem->TransRandom |= 240;

		if (launcher->Status.size == TRANSIENTSIZE)								//RJS 05May99
			newitem->Launcher = ((TransientItemPtr)launcher)->Launcher;			//RJS 05May99

		AddTransientItemToWorld(newitem,worldptr);			
	}

//	LaunchFingersFire(launcher,worldptr);

	if (desiredFPS <= realFPS)					//RJS 11Jun99
	{
		int				count;
		for (count = 0; count < 8; count++)			
		{
			newitem = SimplifiedSpriteLaunch(launcher,SPARK,LIFETIME_DEBRISLNCHR,MOBILE_GANDF);//RJS 23Nov98
			if (newitem)
			{
				SLong	vely = 150000 + (Math_Lib.rnd(150)*1000);//RJS 16Nov99

				newitem->hdg = (Angles) Math_Lib.rnd();			
				newitem->vel_y = vely;							
//DEADCODE CSB 09/11/99 				newitem->velhori = 300 - vely;					
				Float	velhori = 300000. - Float(vely);				 //RJS 16/11/99
				Float sin_ang, cos_ang;									 //CSB 09/11/99
				Math_Lib.high_sin_cos(newitem->hdg, sin_ang, cos_ang);	 //CSB 09/11/99
				newitem->vel_x = velhori * sin_ang;						 //CSB 09/11/99
				newitem->vel_z = velhori * cos_ang;						 //CSB 09/11/99

				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileCanopy
//Author		Robert Slater
//Date			Tue 23 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileCanopy(TransientItemPtr transit, WorldStuff&	world)
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		SWord	pitch = transit->pitch + 100;

		transit->pitch = (Angles) pitch;

		
	}
	else
	{
		UWord	blokesleft = transit->TransRandom & 0xFF;
		UWord	totblokes = transit->TransRandom>>8;

		if (blokesleft && (MobileItemPtr(transit->Launcher)->movecode != AUTO_SPAREAC))//RJS 30Aug00
		{
//DeadCode RJS 26Jul00 
//DeadCode RJS 26Jul00 			Coords3D	pos;
//DeadCode RJS 26Jul00 			SWord		relypos;
//DeadCode RJS 26Jul00 			mobileitem*	theLauncher=(mobileitem*)transit->Launcher;
//DeadCode RJS 26Jul00 			bool		trackthis = false;
//DeadCode RJS 26Jul00 
//DeadCode RJS 26Jul00 			SHAPE.GetPilotPos(theLauncher,totblokes-blokesleft,pos,relypos);
//DeadCode RJS 26Jul00 
//DeadCode RJS 26Jul00 			blokesleft--;
//DeadCode RJS 26Jul00 			if (blokesleft == (totblokes>>1))
//DeadCode RJS 26Jul00 				trackthis = true;
//DeadCode RJS 26Jul00 
//DeadCode RJS 26Jul00 			LaunchParachute(theLauncher,pos,relypos,world,trackthis);

			EjectParachutist(MobileItemPtr(transit->Launcher),blokesleft,totblokes,world);	//RJS 26Jul00

			transit->TransRandom = (totblokes<<8) + blokesleft;

			if (!blokesleft)
				transit->LaunchTime = 250;
			else
				transit->LaunchTime = 50 + Math_Lib.rnd(50);	//RJS 22Dec99
		}
		else
			AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchCollapse
//Author		Robert Slater
//Date			Mon 15 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchCollapse(	ItemPtr	launcher,
									Coords3D& noncorrectedgrpcoords,
									SWord	groupindex,
									WorldStuff&	worldptr)
{
	MyGroundVector	pos;
	ShapeNum		shapehit;
	UWord			ghdg;
	MinAnimData		*mad = (MinAnimData*) SHAPE.GetGroupItemAnimHdg(launcher,shapehit,groupindex,&pos,ghdg);
	UWord			animoffset = launcher->Anim.Offset(mad);//((UByteP)mad) - ((UByteP)&launcher->Anim);

	if (mad)
	{
		mad->IsInvisible = 1;//Turn off the original bridge element...

		TransientItem*	newitem;
		newitem = SimplifiedSpriteLaunch(	launcher,
											shapehit,
											1000,
											MOBILE_COLLAPSE);
		
		if (newitem)
		{
			newitem->World = noncorrectedgrpcoords;
			newitem->TransRandom = animoffset & 0x0FFF;
			newitem->hdg = (Angles) ghdg;

			SWord	roll,pitch;
			UWord	rp = 0;
			SLong	velx = 10000;		//0.5 ms
			SLong	velz = 10000;

			roll = Math_Lib.rnd();
			pitch = Math_Lib.rnd();

			// top 4 bits are for pitch and roll variations...
			if (roll < 0)
			{
				rp = 2;			//slow
				velx *= -1;
			}
			else
			{
				//+ve
				if (roll > 16384)
					rp = 0;			//slow
			}

			rp <<= 2;

			if (pitch < 0)
			{
				rp |= 2;			//slow
				velz *= -1;
			}
			else
			{
				rp |= 0;			//slow
			}

			newitem->TransRandom |= (rp << 12);
			newitem->vel_x = velx;
			newitem->vel_z = velz;

			MinAnimData*	el_mad = (MinAnimData*) newitem->Anim;
			el_mad->itemstate = DEAD;

			AddTransientItemToWorld(newitem, worldptr);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroundLevel
//Author		Robert Slater
//Date			Wed 14 Apr 1999
//
//Description	Used for transient items
//
//				... with a max height test optimisation
//				Added repeat location optimisation.						//JIM 23/04/99
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static int lastsector=0;
static int lastheight=0;
SLong	TransObj::GetGroundLevel(ItemBase*	itm)
{
	SLong	height = 0;	//HIGHESTGROUND;
//DeadCode DAW 01Jul99 	int newsect=0;
//DeadCode DAW 01Jul99 	//landscape block size = 512*256 cm= 128Kcm= 1.3km
//DeadCode DAW 01Jul99 	int sectx=itm->World.X>>17;
//DeadCode DAW 01Jul99 	int sectz=itm->World.Z&0xfffe0000;
//DeadCode DAW 01Jul99 	newsect=sectx+sectz;
//DeadCode DAW 01Jul99 	if (newsect==lastsector && lastheight<itm->World.Y + METRES500)
//DeadCode DAW 01Jul99 	{
//DeadCode DAW 01Jul99 //		return lastheight;
//DeadCode DAW 01Jul99 	}
	if (itm->World.Y < HIGHESTGROUND)
		height = Land_Scape.GetGroundLevel(itm->World);
//DEADCODE DAW 05/05/99	else
//DEADCODE DAW 05/05/99		height=HIGHESTGROUND;
//DeadCode DAW 01Jul99 	lastsector=newsect;
//DeadCode DAW 01Jul99 	lastheight=height;
	return (height);
}

SLong	TransObj::GetGroundLevel(ItemBase*	itm,UByte&	theArea)
{
	SLong	height = 0;	//HIGHESTGROUND;
//DeadCode DAW 01Jul99 	int newsect=0;
//DeadCode DAW 01Jul99 	//landscape block size = 512*256 cm= 128Kcm= 1.3km
//DeadCode DAW 01Jul99 	int sectx=itm->World.X>>17;
//DeadCode DAW 01Jul99 	int sectz=itm->World.Z&0xfffe0000;
//DeadCode DAW 01Jul99 	newsect=sectx+sectz;
//DeadCode DAW 01Jul99 	if (newsect==lastsector && lastheight<itm->World.Y + METRES500)
//DeadCode DAW 01Jul99 	{
//DeadCode DAW 01Jul99 //		return lastheight;
//DeadCode DAW 01Jul99 	}
	if (itm->World.Y < HIGHESTGROUND)
	{
		height = Land_Scape.GetGroundLevel(itm->World,&theArea);//DAW 04May99
		theArea &= AT_MASK;
	}

//DeadCode DAW 01Jul99 	lastsector=newsect;
//DeadCode DAW 01Jul99 	lastheight=height;
	return (height);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchAmmoBoxes
//Author		Robert Slater
//Date			Mon 26 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchAmmoBoxes(mobileitem* launcher,UByte gindex,Coords3D &hittercoords,SLong strength,WorldStuff& worldptr)
{
	MyGroundVector	pos;
	ShapeNum		shapehit;
	TransientItem*	newitem;
	UWord			realhdg;
	MinAnimData*	mad = (MinAnimData*) SHAPE.GetGroupItemAnimHdg(launcher,shapehit,gindex,&pos,realhdg);
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shapehit);
	SLong			halfboxes = ((sdptr->Size << 4) / 176) / 2;
	SLong			noboxes = halfboxes + Math_Lib.rnd(halfboxes);
	SLong			count;
	SLong			shpsize = sdptr->Size << 4;
	SLong			dx,dz,dist;
	SWord			thehdg;

	// Throw from the direction the weapon came from...
	dx = pos.gx - hittercoords.X;
	dz = pos.gz - hittercoords.Z;

	thehdg = Math_Lib.arctan(dz,dx);
	if (dx > 0)
		thehdg = ANGLES_90Deg - thehdg;
	else
		thehdg = ANGLES_270Deg - thehdg;

	mad->itemstate = DEAD;

	//50m is minimum toss damage...
	if (strength > 0)
	{
		SLong	vely,maxvel,thesize;
		SLong	maxtoss;
		SLong	hdgintercept = SWord(UWord(thehdg) - realhdg);
		SLong	pitchintercept;
		SWord	pitchmag,hdgmag,hpmag;

		dist = Math_Lib.distance3d(dx,dz,0);
		dist -= shpsize;
		if (dist < 0)
			dist = 0;

		hdgintercept <<= 8;
		hdgintercept /= ANGLES_90Deg;
		if (hdgintercept > 256)
		{
			hdgintercept = 0;
			pitchintercept = 256 - hdgintercept;
		}
		else
			pitchintercept = 256 - hdgintercept;

		pitchmag = (pitchintercept * 127)>>8;		//max of 90degree flip in 1 sec ish
		hdgmag = (hdgintercept * 127)>>8;

		hpmag = hdgmag << 8;
		hpmag |= pitchmag;

		maxtoss = 5000 - dist;
		thesize = 1000 - shpsize;

		maxvel = (500 * strength) / 31;	//31 is max strength..
		maxvel *= thesize;
//DEADCODE CSB 09/11/99 		maxvel /= 1000;

		// 60degree throw max...
		if (maxtoss > 0)
		{
			vely = (maxtoss * maxvel * 6) / 9;
//DEADCODE CSB 09/11/99 			vely /= 5000;
			vely /= 5; //CSB 09/11/99
		}
		else
			vely = 0;

		if (desiredFPS > realFPS)					//RJS 28May99
			noboxes = 2;

		for (count = 0; count < noboxes; count++)
		{
			newitem = SimplifiedSpriteLaunch(	launcher,
												CLUSTA,					//RJS 26May99
												LIFETIME_DEBRISLNCHR,
												MOBILE_DEBRIS);
			if (newitem)
			{
				newitem->World.X = pos.gx;
				newitem->World.Y = pos.gy;
				newitem->World.Z = pos.gz;

				newitem->TransRandom = Math_Lib.rnd();
				newitem->hdg = (Angles) (thehdg + Math_Lib.rnd(ANGLES_90Deg) - ANGLES_45Deg);
				newitem->vel_y = vely;
//DEADCODE CSB 09/11/99 				newitem->velhori = maxvel - vely;
				Float velhori = Float((maxvel - vely)*1000);			 //RJS 16Nov99
				Float sin_ang, cos_ang;									 //CSB 09/11/99
				Math_Lib.high_sin_cos(newitem->hdg, sin_ang, cos_ang);	 //CSB 09/11/99
				newitem->vel_x = velhori * sin_ang;						 //CSB 09/11/99
				newitem->vel_z = velhori * cos_ang;						 //CSB 09/11/99

				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WithinVisibleRange
//Author		Robert Slater
//Date			Fri 30 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	TransObj::WithinVisibleRange(Coords3D&	pos, SLong maxrange)
{
	if (View_Point)												//RJS 05May99
	{
		float	deltax = float(pos.X - View_Point->World.X);
		float	deltay = float(pos.Y - View_Point->World.Y);
		float	deltaz = float(pos.Z - View_Point->World.Z);
		float	frange = float(maxrange);

		if ((deltax*deltax+deltay*deltay+deltaz*deltaz) < (frange*frange))
			return TRUE;

//DeadCode RJS 24May00 		SLong	deltax = pos.X - View_Point->World.X;
//DeadCode RJS 24May00 		SLong	deltay = pos.Y - View_Point->World.Y;
//DeadCode RJS 24May00 		SLong	deltaz = pos.Z - View_Point->World.Z;
//DeadCode RJS 24May00 
//DeadCode RJS 24May00 		deltax = (deltax<0)?-deltax:deltax;
//DeadCode RJS 24May00 		deltay = (deltay<0)?-deltay:deltay;
//DeadCode RJS 24May00 		deltaz = (deltaz<0)?-deltaz:deltaz;
//DeadCode RJS 24May00 
//DeadCode RJS 24May00 		if (	(deltax < maxrange)
//DeadCode RJS 24May00 			&&	(deltay < maxrange)
//DeadCode RJS 24May00 			&&	(deltaz < maxrange)	)
//DeadCode RJS 24May00 			return TRUE;
	}

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBoatSink
//Author		Robert Slater
//Date			Thu 13 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchBoatSink(ItemPtr		launcher,
								 Coords3D&		noncorrectedgrpcoords,
								 SWord		groupindex,
								 WorldStuff&	worldptr)
{
	MyGroundVector	pos;
	ShapeNum		shapehit;
	UWord			ghdg;
	MinAnimData		*mad = (MinAnimData*) SHAPE.GetGroupItemAnimHdg(launcher,shapehit,groupindex,&pos,ghdg);
	UWord			animoffset = launcher->Anim.Offset(mad);

	if (mad)
	{
		mad->IsInvisible = 1;

		TransientItem*	newitem;
		newitem = SimplifiedSpriteLaunch(	launcher,
											shapehit,
											1000,
											MOBILE_SINK);
		
		if (newitem)
		{
			newitem->World = noncorrectedgrpcoords;
			newitem->TransRandom = animoffset & 0x0FFF;
			newitem->hdg = (Angles) ghdg;

			SWord	pitch;
			UWord	rp = 0;

//DeadCode RJS 18Sep00 			roll = Math_Lib.rnd();
			pitch = Math_Lib.rnd();

			// top 4 bits are for pitch and roll variations...
//DeadCode RJS 18Sep00 			if (roll < 0)
//DeadCode RJS 18Sep00 			{
//DeadCode RJS 18Sep00 				//-ve
//DeadCode RJS 18Sep00 				if (roll < -16384)
//DeadCode RJS 18Sep00 					rp = 3;			//fast
//DeadCode RJS 18Sep00 				else
//DeadCode RJS 18Sep00 					rp = 2;			//slow
//DeadCode RJS 18Sep00 			}
//DeadCode RJS 18Sep00 			else
//DeadCode RJS 18Sep00 			{
//DeadCode RJS 18Sep00 				//+ve
//DeadCode RJS 18Sep00 				if (roll > 16384)
//DeadCode RJS 18Sep00 					rp = 1;			//fast
//DeadCode RJS 18Sep00 				else
//DeadCode RJS 18Sep00 					rp = 0;			//slow
//DeadCode RJS 18Sep00 
//DeadCode RJS 18Sep00 			}

			rp <<= 2;

			if (pitch < 0)
			{
				//-ve
				if (pitch < -16384)
					rp |= 3;			//fast
				else
					rp |= 2;			//slow
			}
			else
			{
				//+ve
				if (pitch > 16384)
					rp |= 1;			//fast
				else
					rp |= 0;			//slow

			}

			newitem->TransRandom |= (rp << 12);

			MinAnimData*	el_mad = (MinAnimData*) newitem->Anim;
			el_mad->itemstate = DEAD;

			AddTransientItemToWorld(newitem, worldptr);
		}

// Scatter some dingys...
		if (WithinVisibleRange(launcher->World,1000000))				//RJS 18Sep00
		{
			SLong		index;
			Coords3D	backuppos = launcher->World;
			SLong		randxz;
			SLong		maxdingys = Math_Lib.rnd(5);

			for (index = 0; index < maxdingys; index++)
			{
				randxz = Math_Lib.rnd(5000) - 2500;

				launcher->World = noncorrectedgrpcoords;
				launcher->World.X += randxz;
				launcher->World.Z += randxz;

				LaunchDingyChap(MobileItemPtr(launcher),worldptr);
			}

			launcher->World = backuppos;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillOldestTrail
//Author		Robert Slater
//Date			Thu 13 May 1999
//
//Description	We only care if the launcher is an ac
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	TransObj::KillOldestTrail(ItemPtr	itm)
{
	if (itm->Status.size == AIRSTRUCSIZE)
	{
		SLong	index;
		ULong	oldest = 0xFFFFFFFF;
		SLong	killindex = -1;

		for (index=0; index < MaxTrails; index++)
		{
			if (StaticTrailList[index].time < oldest)
			{
				oldest = StaticTrailList[index].time;
				killindex = index;
			}
		}

		if (killindex > -1)
		{
			AddTransientItemToDeadList(StaticTrailList[killindex].item);
			StaticTrailList[killindex].time = 0xFFFFFFFF;
			return TRUE;
		}
	}

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFakeDelayedExplosion
//Author		Robert Slater
//Date			Sun 16 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchFakeDelayedExplosion(mobileitem*	launcher, WorldStuff&	worldptr	)
{
	SLong			delay;
	TransientItem*	newitem;

	delay = 150 + Math_Lib.rnd(150);

	newitem = LaunchGuidedMissile(launcher,launcher,
									InvisibleLauncher,delay,MOBILE_DELEXP);

	if (newitem)
	{
		// this means it really will explode...
		newitem->TransRandom = 4;		

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchCarpetStrike
//Author		Robert Slater
//Date			Mon 31 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchCarpetStrike(mobileitem*	launcher, WorldStuff&	worldptr	)
{
// Temporarily disabled...
/*	ShapeNum	theShape;											//RJS 17Jun99
	SLong		strikecnt;
	SLong		lifetime;
	if (launcher->shape == BOMB29)									//RJS 17Jun99
	{
		//500lb strike
		theShape = BMB100;
		strikecnt = 16;
		lifetime = 300;
	}
	else
	{
		//1000lb strike
		theShape = BMB500;
		strikecnt = 8;
		lifetime = 150;
	}

	TransientItem*	newitem;
	newitem = LaunchUnguidedMissile(	launcher,				
										theShape,					//RJS 17Jun99
										lifetime,					//RJS 17Jun99
										MOBILE_CARPETBOMB	);

	if (newitem)
	{
		MinAnimData*	mad = (MinAnimData*) newitem->Anim;
		mad->IsInvisible = 1;

		if (launcher->Status.size == TRANSIENTSIZE)
			newitem->Launcher = ((TransientItem*)launcher)->Launcher;

		newitem->TmpLaunchTime = lifetime / strikecnt;	  //means each bomber has dropped 34 bombs
		newitem->TransRandom = newitem->TmpLaunchTime;
		newitem->isArmed = 1;												//RJS 10Jun99

		AddTransientItemToWorld(newitem, worldptr);
	}*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PointBlokes
//Author		Robert Slater
//Date			Tue 1 Jun 1999
//
//Description	Actually sets blokes going.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::PointBlokes(ItemPtr	launcher, ShapeNum troopshape, Coords3D&	realpos, SLong	maxtroops, Coords3D*	placelist, SLong placecnt)
{
	bool	lowpriority = false;								//RJS 11Jun99
	if (desiredFPS > realFPS)					//RJS 11Jun99
	{															//RJS 11Jun99
		maxtroops = 1 + (maxtroops>>1);							//RJS 11Jun99
		lowpriority = true;										//RJS 11Jun99
	}															//RJS 11Jun99

	SLong			count;
	TroopAnimData*	adptr;
	Bool			dim;
	SLong			groundheight = Land_Scape.GetGroundLevel(realpos);
	TransientItem*	newitem;
	SLong			randindex;

	if (placecnt && placelist)
		dim = FALSE;
	else
		dim = TRUE;

	int	stripno;
	if (launcher->OverFrance())											//RJS 25Oct00
		stripno = CLOTHING_LWPILOT;
	else
		stripno = CLOTHING_RAFPILOT;

	for (count = 0; count < maxtroops; count++)
	{
		newitem = SimplifiedSpriteLaunch(launcher,troopshape,LIFETIME_TROOP,MOBILE_TROOP);
		if (newitem)
		{
//DEADCODE RJS 4/17/00 			Anim_Control.SetPlayerAnim(newitem,ANIMATION_RUN);		//RJS 22Dec99

			adptr = (TroopAnimData*) newitem->Anim;
			adptr->oncourse = FALSE;								//RJS 10Jun99
			adptr->homing = FALSE;									//RJS 10Jun99
			adptr->stripno = stripno;									//RJS 25Oct00
			if (!dim)
			{
				randindex = placecnt-Math_Lib.rnd(maxtroops);
				if (randindex < 0)
					randindex = placecnt-1;

				adptr->xpos = placelist[randindex].X;								
				adptr->ypos = placelist[randindex].Y;
				adptr->zpos = placelist[randindex].Z;
//DeadCode RJS 11Jun99 					adptr->oncourse = FALSE;

				// Someone might panic!!!!!... headless chicken code
				if (Math_Lib.rnd()<60000)							//RJS 10Jun99
				{
					Anim_Control.SetPlayerAnim(newitem,ANIMATION_RUN);		//RJS 17Apr00
					adptr->homing = TRUE;							//RJS 10Jun99
				}
				else
					Anim_Control.SetPlayerAnim(newitem,ANIMATION_RUNCHICKEN);//RJS 17Apr00
			}
			else
				Anim_Control.SetPlayerAnim(newitem,ANIMATION_RUNCHICKEN);	//RJS 17Apr00

	
			// 5 metre spread around...
			newitem->World.X = realpos.X + Math_Lib.rnd(1000) - 500;
			newitem->World.Y = groundheight;								
			newitem->World.Z = realpos.Z + Math_Lib.rnd(1000) - 500;

			// Run velocity = 6ms to 9ms
			UWord		randval = Math_Lib.rnd();				//RJS 10Jun99
			Float		vel = 60000. + (Float(randval)*0.457763671875);//RJS 22Dec99

			newitem->hdg = (Angles) randval;					//RJS 10Jun99
			newitem->vel_y = 0;

			Float sin_ang, cos_ang;									 //CSB 09/11/99
			Math_Lib.high_sin_cos(newitem->hdg, sin_ang, cos_ang);	 //CSB 09/11/99
			newitem->vel_x = vel * sin_ang;						 //RJS 22Dec99
			newitem->vel_z = vel * cos_ang;						 //RJS 22Dec99
			newitem->vel_ = vel;								//RJS 22Dec99


			newitem->TransRandom = 50;

			if (lowpriority)									//RJS 11Jun99
				newitem->TimeOfLaunch -= 3000;	//30 secs older	//RJS 11Jun99

			AddTransientItemToWorld(newitem, *newitem->currworld);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReduceBulkStores
//Author		Robert Slater
//Date			Thu 17 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ReduceBulkStores(AirStrucPtr	ac, UByteP	aptr)
{
	if (!Save_Data.gamedifficulty[GD_UNLIMITEDARM])
	{
		PolyPitAnimData*	adptr = (PolyPitAnimData*) aptr;
		SLong	loss = adptr->acprevammoleft - adptr->acgunammoleft;	//RJS 24Nov99
		if (loss > 0)												//RJS 21Jun99
		{
			SLong		lastknownstation = adptr->lastweapindex;
			SLong		count;
			SLong		index;
			LnchrType	currentweapon = (LnchrType) (adptr->weaponlaunchers[lastknownstation].LauncherType & LT_MASK);
			SLong		massGone;
			SLong		stationpass[8];
//DeadCode RJS 20Oct00 			SLong		tmpstation = lastknownstation;
			SLong		stationlist[8];
//DeadCode RJS 20Oct00 			SLong		stationcnt = 0;
			SLong		tmpstatcnt;

			adptr->acprevammoleft = adptr->acgunammoleft;		//RJS 24Nov99

//DeadCode RJS 10Jul00 			for (index = 0; index < MAX_WEAP_LAUNCHERS; index++)//RJS 15Nov99
//DeadCode RJS 10Jul00 			{
//DeadCode RJS 10Jul00 				stationpass[index] = 0;
//DeadCode RJS 10Jul00 				if ((adptr->weaponlaunchers[index].LauncherType & LT_MASK) == currentweapon)
//DeadCode RJS 10Jul00 					stationlist[stationcnt++] = index;
//DeadCode RJS 10Jul00 			}
//DeadCode RJS 10Jul00 
//DeadCode RJS 10Jul00 			count = 0;
//DeadCode RJS 10Jul00 			if (stationcnt)											//RJS 21Jun99
//DeadCode RJS 10Jul00 			{
//DeadCode RJS 10Jul00 #ifndef	NDEBUG
//DeadCode RJS 10Jul00 	int stuckCnt= 0;
//DeadCode RJS 10Jul00 #endif
//DeadCode RJS 10Jul00 				while (count < loss)
//DeadCode RJS 10Jul00 				{
//DeadCode RJS 10Jul00 					for (tmpstatcnt = 0; tmpstatcnt < stationcnt; tmpstatcnt++)
//DeadCode RJS 10Jul00 					{
//DeadCode RJS 10Jul00 						index = stationlist[tmpstatcnt];
//DeadCode RJS 10Jul00 						if (index == tmpstation)	 //already deducted	on 1st pass
//DeadCode RJS 10Jul00 							tmpstation = -1;
//DeadCode RJS 10Jul00 						else
//DeadCode RJS 10Jul00 						{
//DeadCode RJS 10Jul00 							if (index > tmpstation)
//DeadCode RJS 10Jul00 							{
//DeadCode RJS 10Jul00 								stationpass[index]++;
//DeadCode RJS 10Jul00 								count++;
//DeadCode RJS 10Jul00 								if (count == loss)
//DeadCode RJS 10Jul00 									break;
//DeadCode RJS 10Jul00 							}
//DeadCode RJS 10Jul00 						}
//DeadCode RJS 10Jul00 					}
//DeadCode RJS 10Jul00 #ifndef	NDEBUG
//DeadCode RJS 10Jul00 // something has severely cocked-up!
//DeadCode RJS 10Jul00 	stuckCnt++;
//DeadCode RJS 10Jul00 	if (stuckCnt > loss)
//DeadCode RJS 10Jul00 		INT3;
//DeadCode RJS 10Jul00 #endif
//DeadCode RJS 10Jul00 				}
//DeadCode RJS 10Jul00 
//DeadCode RJS 10Jul00 				for (tmpstatcnt = 0; tmpstatcnt < stationcnt; tmpstatcnt++)
//DeadCode RJS 10Jul00 				{
//DeadCode RJS 10Jul00 					index = stationlist[tmpstatcnt];
//DeadCode RJS 10Jul00 					count = stationpass[index];
//DeadCode RJS 10Jul00 					if (count)
//DeadCode RJS 10Jul00 					{
//DeadCode RJS 10Jul00 						//Deduct this amount of stores from this station...
//DeadCode RJS 10Jul00 
//DeadCode RJS 10Jul00 						SHAPE.ReduceLauncherLoad(ac,index,count);
//DeadCode RJS 10Jul00 					}
//DeadCode RJS 10Jul00 				}
//DeadCode RJS 10Jul00 			}

			for (index = 0; index < adptr->nolaunchers; index++)
			{
				if ((adptr->weaponlaunchers[index].LauncherType & LT_MASK) == currentweapon)
				{
					count = adptr->prevammo[index] - adptr->weaponlaunchers[index].LoadedStores;
					if (count > 0)
						SHAPE.ReduceLauncherLoad(ac,index,count);

					adptr->prevammo[index] = adptr->weaponlaunchers[index].LoadedStores;
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchReplayWeapon
//Author		Andy McMaster
//Date			Wed 23 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	TransObj::LaunchReplayWeapon(UByteP	armeddata, UByte	noInGroup)
{
	ArmedTransient*		at = (ArmedTransient*)armeddata;
	TransientItemPtr	newitem;
//DeadCode AMM 24Aug00 	mobileitem*			launcher = (mobileitem*) Persons2::ConvertPtrUID((UniqueID)at->launcher);
	item*				launcher = (item*) Persons2::ConvertPtrUID((UniqueID)at->launcher);	//AMM 24Aug00
	bool				retval = true;


 	newitem = SimplifiedSpriteLaunch(	launcher,
										(ShapeNum)at->shape,
										at->lifetime,
										(AutoMoveCodeTypeSelect)at->movecode);
	if (newitem)
	{
		newitem->World.X = at->Pos.X;
		newitem->World.Y = at->Pos.Y;
		newitem->World.Z = at->Pos.Z;

		newitem->hdg=at->hdg;									//AMM 24Jun99
		newitem->pitch=at->pitch;								//AMM 24Jun99

		newitem->vel_x = at->vel_x;
		newitem->vel_y = at->vel_y;
		newitem->vel_z = at->vel_z;
//DEADCODE CSB 09/11/99 		newitem->velhori = at->velhori;
		newitem->isArmed = 1;
		if (at->strength)
		{
			MissileAnimData*	adptr = (MissileAnimData*)newitem->Anim;
			adptr->hitstrength = at->strength;

			newitem->TransRandom = 50 - at->lifetime;
		}
		else													//AMM 24Jun99
		{														//AMM 24Jun99
			newitem->TransRandom = at->transrandom;				//AMM 24Jun99
			if (at->trailindex)									//AMM 24Jun99
			{													//AMM 24Jun99
				MoveGunAnimData*	adptr = (MoveGunAnimData*)newitem->Anim;//AMM 24Jun99
				adptr->weaponlaunchers[0].hdg = at->trailindex;	//AMM 24Jun99
				adptr->weaponlaunchers[0].pitch = -1;			//AMM 24Jun99
				adptr->weaponlaunchers[0].LauncherType = LT_FUEL;//AMM 24Jun99
			}													//AMM 24Jun99
		}														//AMM 24Jun99

		newitem->Status.deadtime = at->deadtime;

		if (noInGroup)													//RJS 1Sep00
			retval = SHAPE.ReadReplayGroup(newitem,noInGroup);			//RJS 1Sep00

		AddTransientItemToWorld(newitem,*newitem->currworld);
	}

	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSnapFlash
//Author		Robert Slater
//Date			Tue 29 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchSnapFlash(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = RelativeSpriteLaunch(launcher,launcher->shape,SMFLSH,20,MOBILE_BIGEXP);
	if (newitem)
	{
		if ((launcher->Status.size >= MovingSize) && (launcher->Status.size != TransientSize))
			newitem->Target = launcher;

		_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_OILDRUM1+Math_Lib.rnd(5)), newitem);
		AddTransientItemToWorld(newitem,worldptr);
	}

	LaunchSparkDebris(launcher,worldptr);
	LaunchDebris(launcher,ACBTS0,4,8,worldptr);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDirtSpark
//Author		Robert Slater
//Date			Tue 6 Jul 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchDirtSpark(mobileitem* launcher,WorldStuff& worldptr, bool dosound)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(launcher,RicochetSmokeShape,30,MOBILE_STATIONARY);
	if (newitem)
		AddTransientItemToWorld(newitem,worldptr);

	newitem = SimplifiedSpriteLaunch(launcher,BULGND,170,MOBILE_STATIONARY);
	if (newitem)
	{
		if (dosound)
			_Miles.PlaySample((FileNum)(FIL_SFX_RICOCHET_HARD_SURFACE1+Math_Lib.rnd(4)),newitem);
		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcVels
//Author		Robert Slater
//Date			Fri 12 Nov 1999
//
//Description	Calc velx & velz from given hdg, pitch etc...
//
//				All velocities that come in here should be relative to the
//				launcher...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransientItem::CalcVels()
{
//DEADCODE RJS 3/29/00 	Float	vx, vz, vh, vy, vel;
//DEADCODE RJS 3/29/00 	Float	sin_ang, cos_ang;
//DEADCODE RJS 3/29/00 
//DEADCODE RJS 3/29/00 	if (vel_ >= vel_y)
//DEADCODE RJS 3/29/00 	{
//DEADCODE RJS 3/29/00 		if (vel_ == vel_y)
//DEADCODE RJS 3/29/00 			vh = 0;
//DEADCODE RJS 3/29/00 		else
//DEADCODE RJS 3/29/00 		{
//DEADCODE RJS 3/29/00 			vel = Float(vel_);
//DEADCODE RJS 3/29/00 			vy = Float(vel_y);
//DEADCODE RJS 3/29/00 
//DEADCODE RJS 3/29/00 // Calc velhori...
//DEADCODE RJS 3/29/00 
//DEADCODE RJS 3/29/00 			vel *= vel;
//DEADCODE RJS 3/29/00 			vy *= vy;
//DEADCODE RJS 3/29/00 
//DEADCODE RJS 3/29/00 			vh = vel - vy;
//DEADCODE RJS 3/29/00 			vh = fastMath.FastSqrt(float(vh));
//DEADCODE RJS 3/29/00 //DeadCode RJS11Feb00			_asm
//DEADCODE RJS 3/29/00 //DeadCode RJS11Feb00			{
//DEADCODE RJS 3/29/00 //DeadCode RJS11Feb00				fld vh; 
//DEADCODE RJS 3/29/00 //DeadCode RJS11Feb00				fsqrt; 
//DEADCODE RJS 3/29/00 //DeadCode RJS11Feb00				fstp vh;
//DEADCODE RJS 3/29/00 //DeadCode RJS11Feb00			}
//DEADCODE RJS 3/29/00 		}
//DEADCODE RJS 3/29/00 	}
//DEADCODE RJS 3/29/00 	else
//DEADCODE RJS 3/29/00 		vh = Float(vel_y);

	Float	vx, vz, vh, vy, vel;
 	Float	sin_ang, cos_ang;

	if (vel_)
	{
		vel = Float(vel_);

		Math_Lib.high_sin_cos(pitch, sin_ang, cos_ang);

		vy = vel * sin_ang;
		vh = vel * cos_ang;

		Math_Lib.high_sin_cos(hdg, sin_ang, cos_ang);

		vx = vh * sin_ang;
		vz = vh * cos_ang;

		vel_x = vx;
		vel_y = vy;
		vel_z = vz;
	}
	else
		vel_x = vel_y = vel_z = 0;

	// Add the launcher's velocity...
	if (Launcher->Status.size >= MOBILESIZE)
	{
		mobileitem*	daddy = (mobileitem*)Launcher;

		vel_x += daddy->vel_x;
		vel_y += daddy->vel_y;
		vel_z += daddy->vel_z;
		vel_ += daddy->vel_;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearWeaponChain
//Author		Robert Slater
//Date			Mon 15 Nov 1999
//
//Description	Reset weapon link chain with previously launched transients
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ClearWeaponChain(mobileitem*	launcher, ULong	lastbullet, ULong wpIndex)
{
	if (launcher->Status.size == AIRSTRUCSIZE)
	{
		MoveGunAnimData*	ladptr = (MoveGunAnimData*) launcher->Anim;

		if (lastbullet)
		{
			//Explicit...
			if (ladptr->weaponlaunchers[wpIndex].currLink == lastbullet)
				ladptr->weaponlaunchers[wpIndex].currLink = NULL;
		}
		else
		{
			//Clear all...
			SLong	lIndex;

			for (lIndex=0; lIndex < ladptr->nolaunchers; lIndex++)
				ladptr->weaponlaunchers[lIndex].currLink = NULL;
		}
	}
}

DeathTollLink::DeathTollLink(MinAnimData*	mad, DeathTollLink*	pLast)
{
	adptr = mad;
	next = pLast;
}

DeathTollLink::~DeathTollLink()
{
// the deathtoll delete must be done BEFORE the world is emptied...
	if (this)
	{
		adptr->IsBullied = 0;

		delete next;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileSuperBomb
//Author		Robert Slater
//Date			Tue 23 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileSuperBomb(TransientItemPtr	transit, WorldStuff&	world)
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		UWord	currelmt = transit->TransRandom;
		SLong	countdown = SLong(currelmt & 0xFF);

		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		if (!countdown)
		{
			if (transit->World.Y < HIGHESTGROUND)
			{
				ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(transit->shape);
				if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
				{
					UByteP		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
					SLong		xpos,ypos,zpos;
					ShapeNum	newshp;
					MinAnimData*	mad;
					animptr		adptr = transit->Anim;
					SLong		index;
					SLong		gheight;
					UByte		theArea;
					Coords3D	coords;
										
					currelmt >>= 8;
					if (currelmt)
					{
//We want to test for one specific element...
						index = 1;

						while (SHAPE.GetGroupElement(instr_ptr,newshp,xpos,ypos,zpos))
						{
							if (index == currelmt)
							{
								coords = transit->World;
								coords.X += xpos;
								coords.Y += ypos;
								coords.Z += zpos;

								gheight = Land_Scape.GetGroundLevel(coords,&theArea);
								if (coords.Y <= gheight)
								{
									mad = (MinAnimData*) adptr;
									mad->IsInvisible = 1;
		
									coords.Y = gheight + METRES01;
			
									theArea &= AT_MASK;

									DoImpactGround(transit,coords,theArea,newshp,adptr);

									transit->TransRandom = 0;
								}

								break;
							}
							else
							{
								index++;
								adptr += SHAPE.GetElementAnimOffset(newshp);
							}
						}
					}
					else
					{
// We want to test all elements and find the one nearest the ground...
						SLong		closestground, gdiff;
						bool		hitonce = false;
						SLong		element;

						element = 0;
						index = 1;

						closestground = HIGHESTGROUND;

						while (SHAPE.GetGroupElement(instr_ptr,newshp,xpos,ypos,zpos))
						{
							mad = (MinAnimData*) adptr;
							if (!mad->IsInvisible)
							{
								coords = transit->World;
								coords.X += xpos;
								coords.Y += ypos;
								coords.Z += zpos;

								gheight = Land_Scape.GetGroundLevel(coords,&theArea);
								gdiff = coords.Y - gheight;
								if (gdiff < closestground)
								{
									if (gdiff <= 0)
									{
//DEADCODE JON 05/06/00 										if (!hitonce)
//DEADCODE JON 05/06/00 										{
											mad->IsInvisible = 1;
											coords.Y = gheight + METRES01;
			
											theArea &= AT_MASK;

											DoImpactGround(transit,coords,theArea,newshp,adptr);

											hitonce = true;
//DEADCODE JON 05/06/00 										}
									}
									else
									{
										closestground = gdiff;
										element = index;
									}
								}
							}

							index++;
							adptr += SHAPE.GetElementAnimOffset(newshp);
						}

						if (closestground==HIGHESTGROUND)
						{
							// We have all hit...

							transit->TransRandom = 0;
							transit->LaunchTime = 0;
						}
						else
						{
							SLong	vely = transit->vel_y / 1000;
							if (vely)
							{
								SLong	time = closestground / vely;

								if (time > 200)
									transit->TransRandom = 100;
								else
									transit->TransRandom = element<<8;
							}
							else
								transit->TransRandom = 100;
						}
					}
				}
			}
		}
		else
		{
			countdown -= Timer_Code.FRAMETIME;
			if (countdown < 0)
				countdown = 0;

			transit->TransRandom = (currelmt & 0xFF00) + UWord(countdown);
		}

		// What do we want to do about pitch??
		// is this a hard nobble?
		if (transit->LaunchTime)
		{
			GAndFriction(transit,50);		//friction?
			AddWindDrift(transit);
		}

// Real pitch
		transit->BombPitch();									//RJS 16Dec99
//DeadCode RJS 16Dec99 		SLong	timeleft = transit->TmpLaunchTime - transit->LaunchTime;
//DeadCode RJS 16Dec99 		if (timeleft > 0)
//DeadCode RJS 16Dec99 		{
//DeadCode RJS 16Dec99 			// Swing...
//DeadCode RJS 16Dec99 			Float	sin_ang, cos_ang;
//DeadCode RJS 16Dec99 			SWord	fakeangle = timeleft*950;
//DeadCode RJS 16Dec99 			Math_Lib.high_sin_cos((Angles)fakeangle, sin_ang, cos_ang);
//DeadCode RJS 16Dec99 
//DeadCode RJS 16Dec99 			Float deltapitch = -1000.0 * Float(TimerCode.FRAMETIME) * sin_ang;
//DeadCode RJS 16Dec99 			deltapitch *= 1.0 - (Float(timeleft) * 0.002);
//DeadCode RJS 16Dec99 			transit->pitch += SWord(deltapitch);
//DeadCode RJS 16Dec99 
//DeadCode RJS 16Dec99 			if (timeleft > 500)
//DeadCode RJS 16Dec99 				transit->TmpLaunchTime = 0;
//DeadCode RJS 16Dec99 		}
//DeadCode RJS 16Dec99 		else
//DeadCode RJS 16Dec99 		{
//DeadCode RJS 16Dec99 			// Pitch down normally...
//DeadCode RJS 16Dec99 			float	vx = float(transit->vel_x);
//DeadCode RJS 16Dec99 			float	vz = float(transit->vel_z);
//DeadCode RJS 16Dec99 			float	totvel;
//DeadCode RJS 16Dec99 			Float	velhori,vely;
//DeadCode RJS 16Dec99 			Float	sin_ang,cos_ang;
//DeadCode RJS 16Dec99 
//DeadCode RJS 16Dec99 			vx *= vx;
//DeadCode RJS 16Dec99 			vz *= vz;
//DeadCode RJS 16Dec99 
//DeadCode RJS 16Dec99 			totvel = vx+vz;
//DeadCode RJS 16Dec99 			
//DeadCode RJS 16Dec99 //			velhori = Float(fastMath.FastSqrt(totvel));
//DeadCode RJS 16Dec99 			velhori = FSqrt(Float(totvel));
//DeadCode RJS 16Dec99 			vely = Float(transit->vel_y);
//DeadCode RJS 16Dec99 			vely /= velhori;
//DeadCode RJS 16Dec99 
//DeadCode RJS 16Dec99 			Math_Lib.high_sin_cos(transit->pitch,sin_ang,cos_ang);
//DeadCode RJS 16Dec99 
//DeadCode RJS 16Dec99 			if (sin_ang > (cos_ang*vely))	//pitchdown
//DeadCode RJS 16Dec99 				transit->pitch -= (Angles)Timer_Code.FRAMETIME*10;
//DeadCode RJS 16Dec99 			else
//DeadCode RJS 16Dec99 				transit->pitch += (Angles)Timer_Code.FRAMETIME*10;
//DeadCode RJS 16Dec99 		}
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoImpactGround
//Author		Robert Slater
//Date			Tue 23 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::DoImpactGround(TransientItem* transit, Coords3D& coords, UByte theArea, ShapeNum newshp, animptr adptr)
{
	TransientItem*	tmpitem = new TransientItem;
	if (tmpitem)
	{
		*tmpitem = *transit;

		tmpitem->shape = newshp;
		tmpitem->Anim = adptr;
		tmpitem->World = coords;

		DoImpactGround(tmpitem,coords,theArea);

		tmpitem->Anim = ANIM_NULL;

		delete tmpitem;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSuperBomb
//Author		Robert Slater
//Date			Tue 23 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchSuperBomb(mobileitem*	launcher, ShapeNum theShape, Coords3D& pos, WorldStuff&	worldptr)
{
	ShapeNum	bombShape = (ShapeNum)(SBG00+launcher->shape-SAG00);	//RJS 08Dec99
	TransientItem*	newitem;
	newitem = LaunchUnguidedMissile(	launcher,				
										bombShape,
										LIFETIME_BOMB,
										MOBILE_SUPERBOMB	);

	if (newitem)
	{
		// Add launcher offset from ac...
		newitem->World.X += pos.X;
		newitem->World.Y += pos.Y;
		newitem->World.Z += pos.Z;

		if (launcher->Status.size == TRANSIENTSIZE)
			newitem->Launcher = ((TransientItem*)launcher)->Launcher;
		
		if (AirStrucPtr(*launcher)->fly.numinsag && AirStrucPtr(*launcher)->fly.expandedsag)
			SHAPE.GroupMemberInherit(launcher,bombShape,theShape,newitem->Anim);
		else
			SHAPE.GroupAnimInherit(launcher->shape,bombShape,theShape,launcher->Anim,newitem->Anim);

		if (launcher->Status.size == AIRSTRUCSIZE)
		{
			AirStrucPtr	ac = (AirStrucPtr)launcher;
#ifndef	_NO_RADIOCHATTER_			
			if (ac->classtype->phrasename == PHRASE_HE111)
			{
#endif
				newitem->TmpLaunchTime = newitem->LaunchTime;			//RJS 16Dec99
				newitem->pitch = (Angles)(UWord(ANGLES_60Deg) + Math_Lib.rnd(ANGLES_30Deg));
#ifndef	_NO_RADIOCHATTER_			
			}
			else
				newitem->TmpLaunchTime = 0;
#endif
		}

		newitem->isArmed = 1;

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSAGTransient
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
void	TransObj::LaunchSAGTransient(mobileitem*	launcher, ShapeNum theShape, Coords3D&	grpCoords, int groupindex, WorldStuff& worldptr)
{
	MyGroundVector	pos;											//RJS 20Dec99
	ShapeNum		shapehit;
	UWord			ghdg;
	UByteP			adptr = (UByteP)SHAPE.GetGroupItemAnimHdg(launcher,shapehit,groupindex,&pos,ghdg);
	MinAnimData*	mad = (MinAnimData*) adptr;

	if (SHAPESTUFF.GetShapePtr(shapehit)->AnimDataSize == SIMPLEAIRCRAFTANIM)	//RJS 26Jul00
	{
		SimpleAircraftAnimData*	sadptr = (SimpleAircraftAnimData*) adptr;
		if (sadptr->OTHER == 255)
			sadptr->OTHER = 254;
	}

	if (!mad->IsInvisible)
	{
		TransientItem*	newitem;
		newitem = LaunchUnguidedMissile(	launcher,				
											shapehit,
											3000,
											MOBILE_DEADAC	);

		if (newitem)
		{
			SLong			size = SHAPE.GetAnimDataSize(shapehit);
			UByteP			from = adptr;
			UByteP			to = &newitem->Anim;

			memcpy(to,from,size);

			mad->itemstate = DEAD;
			mad->IsInvisible = 1;

			mad = (MinAnimData*)newitem->Anim;
			mad->itemstate = DYING;										//RJS 31Aug00

			// Cannot be used as a weapon!!!!!
			newitem->Launcher = NULL;

			if (Math_Lib.rnd() > 48000)
			{
				TransientItemPtr	fireitem = TransientItemPtr(LaunchAircraftFire(newitem,newitem->World,worldptr));
				if (fireitem)
				{
					fireitem->Target = newitem;

					newitem->Target = fireitem;
					newitem->isOwned = 1;
				}
			}

			AddTransientItemToWorld(newitem, worldptr);
		}
	}
	else
		mad->itemstate = DEAD;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileDeadAC
//Author		Robert Slater
//Date			Thu 25 Nov 1999
//
//Description	Stolen from AutoDeathSequence
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileDeadAC(TransientItemPtr	transit, WorldStuff& world)
{
	int timeleft=transit->LaunchTime;

	if (timeleft)
	{
		if (transit->Launcher && (transit->Launcher->Status.size == AIRSTRUCSIZE))//RJS 20Dec99
		{														//RJS 20Dec99
			AirStrucPtr		ac = (AirStrucPtr)transit->Launcher;//RJS 20Dec99
			MinAnimData*	madness = (MinAnimData*)ac->Anim;	//RJS 20Dec99
																//RJS 20Dec99
			ac->fly.pModel->CrashTime = DEADTIMEOUT_RECYCLE;			//RJS 10Oct00
			madness->IsInvisible = 1;							//RJS 20Dec99
			madness->itemstate = DEAD;							//RJS 20Dec99

//DeadCode RJS 22Aug00 			if (View_Object->trackeditem2 == ac)						//CSB 16Jun00
//DeadCode RJS 22Aug00 				View_Object->trackeditem2 = transit;					//RJS 13Aug00
																//RJS 20Dec99
			transit->Launcher = NULL;							//RJS 20Dec99

			ac->movecode = AUTO_NOPPILOT;								//CSB 14Aug00
//DeadCode CSB 14Aug00 			ac->RecycleAC();											//CSB 10Aug00
		}														//RJS 20Dec99

		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		if ((transit->LaunchTime & 0x04)==0)					//RJS 23Dec99
		{
			UByte	theArea;
			SLong	groundheight = GetGroundLevel(transit,theArea);
			if (transit->World.Y <= groundheight + 150)					//CSB 31Oct00
			{
				MinAnimData	*mad = (MinAnimData*)transit->Anim;

				transit->Status.deadtime = true;						//RJS 27Jul00

				Coords3D	hitpos = transit->World;			
				hitpos.Y = groundheight;						

				if (!mad->IsInvisible)								//RJS 20Dec99
				{													//RJS 20Dec99
					DoImpactGround(transit,hitpos,theArea);			//RJS 20Dec99
					LaunchBigExplosion(transit,world,transit->shape);//RJS 20Dec99
				}													//RJS 20Dec99
				transit->LaunchTime = 0;
			}
			else
			{
				// Maybe not...
//DeadCode RJS 20Dec99 				if (BoxCol::NineSectorColPiloted(transit))		
//DeadCode RJS 20Dec99 					transit->LaunchTime=0;						
			}
		}

		if (transit->LaunchTime)
			MobileMoveDeadAC(transit);
	}
	else
	{
// Do we have a fire?
		if (transit->isOwned)
		{
			TransientItemPtr	targ = TransientItemPtr(transit->Target);
		 	if (targ)
			{
				targ->Target = NULL;		//pointed to this
				targ->Launcher = NULL;		//stops the fire

				transit->Target = NULL;
			}

			transit->isOwned = 0;
		}
		
		if (!transit->Status.deadtime)
		{
			// Explode!!
			LaunchBigExplosion(transit,world,transit->shape);				//RJS 26Jul00
			if (desiredFPS <= realFPS)								//RJS 26Jul00
				LaunchFingers(transit,world);								//RJS 26Jul00
		}

		AddTransientItemToDeadList(transit);
	}
}

			
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileMoveDeadAC
//Author		Robert Slater
//Date			Thu 25 Nov 1999
//
//Description	Stolen from AutoDeathSequence
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileMoveDeadAC(mobileitem* item)
{
	UByte	lwing, rwing, tail, canopy, engine;
 	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(item->shape);
	if (sdptr->AnimDataSize == AIRCRAFTANIM)
	{
		AircraftAnimData*	adptr = (AircraftAnimData *)item->Anim;
		lwing = adptr->LEFTWINGOUT;
		rwing = adptr->RIGHTWINGOUT;
		tail = adptr->TAIL;
		canopy = adptr->CANOPY;
		engine = adptr->ENGINELEFT;
	}
	else
	{
		SimpleAircraftAnimData*	adptr = (SimpleAircraftAnimData *)item->Anim;
		lwing = adptr->LEFTWINGOUT;
		rwing = adptr->RIGHTWINGOUT;
		tail = 32;
		canopy = 0;
		engine = 255;
	}

	SWord PitchIntercept = ANGLES_345Deg - (lwing * 15 + rwing * 15 + tail * 30);
	SWord DesRoll  = 60 * (rwing - lwing);

//DeadCode CSB 19Jun00 	SWord PitchIntercept = ANGLES_350Deg;
//DeadCode CSB 19Jun00 	SWord DesRoll  = ANGLES_0Deg;
//DeadCode CSB 19Jun00 	for(;;)
//DeadCode CSB 19Jun00 	{
//DeadCode CSB 19Jun00 		if( (lwing > BS_DAMLV2) && (rwing > BS_DAMLV2) && (tail > BS_DAMLV2) )
//DeadCode CSB 19Jun00 		{	
//DeadCode CSB 19Jun00 			PitchIntercept = ANGLES_270Deg;
//DeadCode CSB 19Jun00 			DesRoll = ANGLES_80Deg;
//DeadCode CSB 19Jun00 			if(item->roll < ANGLES_0Deg) DesRoll = -DesRoll;
//DeadCode CSB 19Jun00 			break;
//DeadCode CSB 19Jun00 		}
//DeadCode CSB 19Jun00 
//DeadCode CSB 19Jun00 		if( (lwing > BS_DAMLV2) && (rwing > BS_DAMLV2) )
//DeadCode CSB 19Jun00 		{
//DeadCode CSB 19Jun00 			PitchIntercept = ANGLES_285Deg;
//DeadCode CSB 19Jun00 			DesRoll = ANGLES_85Deg;
//DeadCode CSB 19Jun00 			if(item->roll < ANGLES_0Deg) DesRoll = -DesRoll;
//DeadCode CSB 19Jun00 			break;
//DeadCode CSB 19Jun00 		}
//DeadCode CSB 19Jun00 		
//DeadCode CSB 19Jun00 		if( (lwing > BS_DAMLV2) && (rwing < BS_DAMLV2) )
//DeadCode CSB 19Jun00 		{
//DeadCode CSB 19Jun00 			PitchIntercept = ANGLES_300Deg;
//DeadCode CSB 19Jun00 			DesRoll =  ANGLES_90Deg;
//DeadCode CSB 19Jun00 			DesRoll -= ANGLES_1Deg;
//DeadCode CSB 19Jun00 			DesRoll = -DesRoll;
//DeadCode CSB 19Jun00 			break;
//DeadCode CSB 19Jun00 		}
//DeadCode CSB 19Jun00 
//DeadCode CSB 19Jun00 		if( (lwing < BS_DAMLV2) && (rwing > BS_DAMLV2) )
//DeadCode CSB 19Jun00 	 	{
//DeadCode CSB 19Jun00 			PitchIntercept = ANGLES_300Deg;
//DeadCode CSB 19Jun00 			DesRoll =  ANGLES_90Deg;
//DeadCode CSB 19Jun00 			DesRoll -= ANGLES_1Deg;
//DeadCode CSB 19Jun00 			break;
//DeadCode CSB 19Jun00 		}
//DeadCode CSB 19Jun00  
//DeadCode CSB 19Jun00 		if(tail > BS_DAMLV2)
//DeadCode CSB 19Jun00 		{
//DeadCode CSB 19Jun00 			PitchIntercept = ANGLES_270Deg;
//DeadCode CSB 19Jun00 			DesRoll = ANGLES_45Deg;
//DeadCode CSB 19Jun00 			if(item->roll < ANGLES_0Deg) DesRoll = -DesRoll;
//DeadCode CSB 19Jun00 			break;
//DeadCode CSB 19Jun00 		}
//DeadCode CSB 19Jun00 
//DeadCode CSB 19Jun00 		if(canopy == BS_DEAD)					//RJS 17Nov99
//DeadCode CSB 19Jun00 		{
//DeadCode CSB 19Jun00 			PitchIntercept =  ANGLES_340Deg;
//DeadCode CSB 19Jun00 //DEADCODE RJS 5/4/00 			PitchIntercept += ANGLES_30Deg * FP(item->vel_) / 500000;
//DeadCode CSB 19Jun00 
//DeadCode CSB 19Jun00 			DesRoll = ANGLES_30Deg;
//DeadCode CSB 19Jun00 
//DeadCode CSB 19Jun00 			SWord sin, cos;
//DeadCode CSB 19Jun00 			Math_Lib.high_sin_cos(Angles(SWord(View_Object->TotalDrawFrameTime() * 100)), sin, cos);
//DeadCode CSB 19Jun00 			DesRoll += sin / 100;
//DeadCode CSB 19Jun00 			break;
//DeadCode CSB 19Jun00 		}
//DeadCode CSB 19Jun00 
//DeadCode CSB 19Jun00 		if(engine > BS_DAMLV2)
//DeadCode CSB 19Jun00 		{
//DeadCode CSB 19Jun00 			PitchIntercept = ANGLES_350Deg;
//DeadCode CSB 19Jun00 			DesRoll = ANGLES_0Deg;
//DeadCode CSB 19Jun00 			break;
//DeadCode CSB 19Jun00 		}
//DeadCode CSB 19Jun00 
//DeadCode CSB 19Jun00 		break;
//DeadCode CSB 19Jun00 	}

	if(SWord(PitchIntercept) < SWord(item->pitch)) item->pitch -= Timer_Code.FRAMETIME * 20;
	if(SWord(PitchIntercept) > SWord(item->pitch)) item->pitch += Timer_Code.FRAMETIME * 20;

	SWord deltaroll = DesRoll - item->roll;
	if(deltaroll > 0) item->roll += Timer_Code.FRAMETIME * 50;
	if(deltaroll < 0) item->roll -= Timer_Code.FRAMETIME * 50;

	SWord sin, cos;
	Math_Lib.high_sin_cos(item->roll, sin, cos);
	Float DeltaHdg = Float(sin) * Float(-SWord(item->pitch)) * 2.0 * Float(Timer_Code.FRAMETIME) / (Float(SWord(ANGLES_90Deg)) * 200.0);
	item->hdg += SWord(DeltaHdg);

	if(item->vel_ > 1500000)	item->vel_ -= Timer_Code.FRAMETIME * 200;
	if(item->vel_ < 1500000)	item->vel_ += Timer_Code.FRAMETIME * 200;
	
	Float sin_theta, cos_theta;
	Float sin_hdg,  cos_hdg;
	Math_Lib.high_sin_cos(item->pitch, sin_theta, cos_theta);

	Float theVel = Float(item->vel_);
	item->vel_y = theVel * sin_theta;
	Float velhori = theVel * cos_theta;

	Math_Lib.high_sin_cos (item->hdg, sin_hdg, cos_hdg);
	item->vel_x = velhori * sin_hdg;
	item->vel_z = velhori * cos_hdg;

	ApplyVelocities(item);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchAircraftFire
//Author		Robert Slater
//Date			Fri 26 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void*	TransObj::LaunchAircraftFire(mobileitem*	launcher, Coords3D& pos, WorldStuff&	worldptr)
{
	TransientItem*	newitem = NULL;

	if (CheckCommsValid(launcher))
	{
		newitem = LaunchGuidedMissile(launcher,launcher,ShockwaveShape,Math_Lib.rnd(30),MOBILE_FUELFIRE);
		if (newitem)
		{
			SLong	useindex=0;
			SLong	totpoints = SHAPE.GetTotalFuelLaunchers(launcher->shape);
			for (int index=0; index < totpoints; index++)
			{
				Coords3D	holepos;
				SLong		dx,dy,dz;
				SLong		distance;
				float		mindsquared = 100000.*100000.;

				SHAPE.GetFuelPos(launcher,index,holepos,LT_INTFUEL);

				dx = holepos.X - pos.X;
				dy = holepos.Y - pos.Y;
				dz = holepos.Z - pos.Z;

				float	dsquared = DistanceSquared(dx,dy,dz);
				if (dsquared < mindsquared)
				{
					mindsquared = dsquared;
					useindex = index;
				}
			}

			// use the target field for transient ac only...
			newitem->Target = NULL;									//RJS 16Jun00
			newitem->TmpLaunchTime = 6000;
			newitem->TransRandom = 10;		//launch delay time max
			newitem->hdg = (Angles) 0;		//fix launch point
			newitem->pitch = (Angles) 300;	//Max lifetime...
			newitem->roll = (Angles) useindex;

			_Miles.PlayLooped(FIL_SFX_FIREBURN_LOOP,launcher);			//RJS 9Oct00

			AddTransientItemToWorld(newitem,worldptr);
		}
	}

	return newitem;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBalloonFire
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
void	TransObj::LaunchBalloonFire(mobileitem*	launcher, WorldStuff&	worldptr)
{
	TransientItem*	newitem;
	SLong			lifetime;

	//make sure fire goes out before balloon does...
	if (launcher->Status.size == TRANSIENTSIZE)
		lifetime = ((TransientItem*)launcher)->LaunchTime-10;
	else
		lifetime = 6000;

	newitem = LaunchGuidedMissile(launcher,launcher,ShockwaveShape,Math_Lib.rnd(30),MOBILE_FUELFIRE);
	if (newitem)
	{
		SLong	totpoints = SHAPE.GetTotalFuelLaunchers(launcher->shape);

		newitem->TmpLaunchTime = lifetime;		//this is the REAL life-time
		newitem->TransRandom = 10;		//launch delay time max
		newitem->hdg = (Angles) totpoints;
		newitem->pitch = (Angles) 250;	//Max lifetime...
		newitem->roll = ANGLES_0Deg;

		_Miles.PlayLooped(FIL_SFX_FIREBURN_LOOP,launcher);			//RJS 9Oct00

		AddTransientItemToWorld(newitem,worldptr);
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDingyChap
//Author		Robert Slater
//Date			Mon 6 Dec 1999
//
//Description	Put down morphing, inflating dingy,
//				and morphing pool of dye
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDingyChap(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										DingyShape,
										30000,
										MOBILE_STATIONARY);
	if (newitem)
	{
		newitem->World.Y = GetGroundLevel(launcher);			//RJS 19Jun00
		newitem->TimeOfLaunch -= 6000;		//make older 

		AddTransientItemToWorld(newitem,worldptr);
	}

//DeadCode RJS 19Jun00 	newitem = SimplifiedSpriteLaunch(	launcher,
//DeadCode RJS 19Jun00 										DyeShape,
//DeadCode RJS 19Jun00 										30000,
//DeadCode RJS 19Jun00 										MOBILE_STATIONARY);
//DeadCode RJS 19Jun00 	if (newitem)
//DeadCode RJS 19Jun00 		AddTransientItemToWorld(newitem,worldptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileFuelFire
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
void TransObj::MobileFuelFire(TransientItemPtr transit, WorldStuff& worldptr)
{
//DeadCode RJS 9Oct00 	_Miles.PlayLooped(FIL_SFX_FIREBURN_LOOP,transit);

	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		SWord	frametime = Timer_Code.FRAMETIME;
		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		if (transit->TmpLaunchTime && (transit->TmpLaunchTime != 65535))
		{										
			timeleft = transit->TmpLaunchTime;	
			timeleft -= frametime;				
			if (timeleft < 0)					
				timeleft = 0;					
												
			transit->TmpLaunchTime = timeleft;	
		}

		if (!CheckCommsValid(transit->Launcher))						//RJS 20Sep00
		{
			_Miles.StopSample(FIL_SFX_FIREBURN_LOOP,transit->Launcher);	//RJS 9Oct00

			transit->LaunchTime = transit->TmpLaunchTime = 0;

			if (transit->Target && (transit->Target->Status.size == TRANSIENTSIZE))
			{
				TransientItemPtr	targ = TransientItemPtr(transit->Target);
				targ->Target = NULL;		//pointed to this
				targ->isOwned = 0;

				transit->Target = NULL;
			}

			AddTransientItemToDeadList(transit);
		}
	}
	else
	{
		if (transit->Launcher)
		{
			mobileitem*	parent = (mobileitem*) transit->Launcher;

			if (	(parent->movecode == MOBILE_NOPPILOT)	
				||	(parent->movecode == AUTO_RESURRECT)	
				||	(transit->TmpLaunchTime==0)				)
			{
				if (transit->World.Y <= (GetGroundLevel(transit) + 1000))	//RJS 31May00
					LaunchFire(parent,worldptr);						//RJS 31May00

					_Miles.StopSample(FIL_SFX_FIREBURN_LOOP,parent);				//RJS 9Oct00

				if (transit->Target && (transit->Target->Status.size == TRANSIENTSIZE))	//RJS 20Sep00
				{
					TransientItemPtr	targ = TransientItemPtr(transit->Target);
					targ->Target = NULL;		//pointed to this
					targ->isOwned = 0;

					transit->Target = NULL;
				}

				AddTransientItemToDeadList(transit);
			}
			else
			{
				bool	drawit = false;
				ULong	nextlaunch = transit->TransRandom;		//RJS 21Jun00
				if (View_Point)												//RJS 05May99
				{
					SLong	deltax = parent->World.X - View_Point->World.X;	//RJS 08Apr00
					SLong	deltay = parent->World.Y - View_Point->World.Y;	//RJS 08Apr00
					SLong	deltaz = parent->World.Z - View_Point->World.Z;	//RJS 08Apr00
					float	dsquared = DistanceSquared(deltax,deltay,deltaz);//RJS 21Jun00

					if (dsquared < (100000.*100000.))
					{
						drawit = true;
						dsquared /= (100000.*100000.);

						nextlaunch = fastMath.DoubleToULong(Float(10.+(75.*dsquared)));
					}
				}

				if (drawit)
				{
					Coords3D	holepos;
					SLong		nopoints = transit->hdg;
					SLong		usepoint = transit->roll;
					SWord		theShape = FireballShape;// + Math_Lib.rnd(3);
					SLong		maxlife = transit->pitch;

					if (parent->Status.size != AIRSTRUCSIZE)			//RJS 26Sep00
						theShape += Math_Lib.rnd(3);					//RJS 26Sep00

					maxlife = maxlife>>1;
					maxlife += Math_Lib.rnd(maxlife);

					transit->LaunchTime = Math_Lib.rnd(nextlaunch);

					if (nopoints)
						usepoint = Math_Lib.rnd(nopoints);
					 
					SHAPE.GetFuelPos(parent,usepoint,holepos,LT_INTFUEL);

					TransientItemPtr	newitem;
					newitem = SimplifiedSpriteLaunch(	parent,
														(ShapeNum)theShape,
														maxlife,
														MOBILE_FIRESMOKE);

					if (newitem)
					{
						SLong	vel = 150 + Math_Lib.rnd(150);
//DeadCode RJS 29Mar00 						SLong	miny = (vel*2)/3;
//DeadCode RJS 29Mar00 
//DeadCode RJS 29Mar00 						newitem->vel_y = (miny+Math_Lib.rnd(vel-miny))*1000;
						newitem->pitch = Angles(ANGLES_30Deg+Math_Lib.rnd(ANGLES_30Deg));//RJS 29Mar00
						newitem->vel_ = vel*1000;
						newitem->hdg = (Angles)Math_Lib.rnd(ANGLES_180Deg)+parent->hdg;

						newitem->CalcVels();

						newitem->World = holepos;
						newitem->TimeOfLaunch -= 6000;	//make 60secs older, so more disposable

						AddTransientItemToWorld(newitem,worldptr);
					}
				}
			}
		}
		else
		{
			if (transit->Target && (transit->Target->Status.size == TRANSIENTSIZE))	//RJS 20Sep00
			{
				TransientItemPtr	targ = TransientItemPtr(transit->Target);
				targ->Target = NULL;		//pointed to this
				targ->isOwned = 0;

				transit->Target = NULL;
			}

			AddTransientItemToDeadList(transit);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFireLick
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
void	TransObj::LaunchFireLick(mobileitem*	launcher, Coords3D&	pos, WorldStuff& worldptr)
{
	TransientItemPtr	newitem;
	newitem = SimplifiedSpriteLaunch(	launcher,
										SMKBG4,
										20,
										MOBILE_FIRESMOKE);

	if (newitem)
	{
		newitem->vel_x = launcher->vel_x;
		newitem->vel_y = launcher->vel_y;
		newitem->vel_z = launcher->vel_z;

		newitem->World = pos;
		newitem->TimeOfLaunch -= 6000;	//make 60secs older, so more disposable

		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileSmokeBlob
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
void TransObj::MobileSmokeBlob(TransientItemPtr transit,WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		Float	vx = Float(transit->vel_x);
		Float	vy = Float(transit->vel_y);
		Float	vz = Float(transit->vel_z);
		Float	temp;
		Float	frametime = Float(Timer_Code.FRAMETIME);
		Float	realdrag = frametime * 0.00000001;	//1000/1e11

		temp = vx*vx*realdrag;
		if (transit->vel_x > 0)
			temp *= -1.;

		vx += temp;

		temp = vy*vy*realdrag;
		if (transit->vel_y > 0)
			temp *= -1.;

		vy += temp;	//delta - no gravity!

		temp = vz*vz*realdrag;
		if (transit->vel_z > 0)
			temp *= -1.;

		vz += temp;

		transit->vel_x = vx;	//compiler auto-casts to long...
		transit->vel_y = vy;
		transit->vel_z = vz;
		
		frametime *= 0.0001;					//frametime / 10000

		transit->World.X += SLong(vx*frametime);
		transit->World.Y += SLong(vy*frametime);
		transit->World.Z += SLong(vz*frametime);
		transit->uniqueID.changed = TRUE;

		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		AddWindDrift(transit);
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileDeadBalloon
//Author		Robert Slater
//Date			Wed 15 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileDeadBalloon(TransientItemPtr transit,WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		if (!transit->TransRandom)
		{
			transit->vel_y -= 250 * Timer_Code.FRAMETIME;	// 0.5 of gravity

			ApplyVelocities(transit);
			AddWindDrift(transit);

			SWord	thePitch = transit->pitch;
			
			thePitch -= ANGLES_1Deg;
			if (thePitch < -SWord(ANGLES_45Deg))
				thePitch = -ANGLES_45Deg;

			transit->pitch = (Angles)thePitch;

			if ((transit->LaunchTime & 0x04)==0)				//RJS 23Dec99
			{
				UByte	theArea;
				SLong	groundheight = GetGroundLevel(transit,theArea);

				if (transit->World.Y <= groundheight)
				{
					// Splat...
					BalloonAnimData*	adptr = (BalloonAnimData*)transit->Anim;
					adptr->animclock = 0;
					adptr->morphframe = 0;

					transit->TransRandom = 1;
					transit->LaunchTime += 300;		//give balloon 3 secs to collapse

					switch (theArea)
					{
					case AT_sea:
					case AT_stream:
						_Miles.PlayOnce(FIL_SFX_RICOCHET_WATER1,transit);
						LaunchSplashSmall((mobileitem*)transit,world);
						break;
					default:
						_Miles.PlayOnce(FIL_SFX_PARACHUTE_LAND_GROUND,transit);
						LaunchDustRing(transit,world);
						break;
					}
				}
			}
		}
	}
	else
	{
		transit->isOwned = 0;
		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDeadBalloon
//Author		Robert Slater
//Date			Wed 15 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDeadBalloon(ShapeNum theShape, Coords3D& pos, WorldStuff&	worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	Persons2::PlayerSeenAC,
										theShape,
										3000,
										MOBILE_DEADBALLOON		);
	if (newitem)
	{
		newitem->Launcher = NULL;
		newitem->World = pos;
		newitem->isOwned = 1;

		AddTransientItemToWorld(newitem,worldptr);

		LaunchBalloonFire(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BombPitch
//Author		Robert Slater
//Date			Thu 16 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransientItem::BombPitch()
{
	SLong	timeleft = TmpLaunchTime - LaunchTime;
	if (timeleft > 0)
	{
		// Swing...
		Float	sin_ang, cos_ang;
		SWord	fakeangle = timeleft*950;
		Math_Lib.high_sin_cos((Angles)fakeangle, sin_ang, cos_ang);

		Float deltapitch = -1000.0 * Float(TimerCode.FRAMETIME) * sin_ang;
		deltapitch *= 1.0 - (Float(timeleft) * 0.002);
		pitch += SWord(deltapitch);

		if (timeleft > 500)
			TmpLaunchTime = 0;
	}
	else
	{
		// Pitch down normally...
		float	vx = float(vel_x);
		float	vz = float(vel_z);
		float	totvel;
		Float	velhori,vely;
		Float	sin_ang,cos_ang;

		vx *= vx;
		vz *= vz;

		totvel = vx+vz;
			
		velhori = fastMath.FastInvSqrt(totvel);					//RJS 17Oct00
//DeadCode RJS 11Feb00		velhori = FSqrt(Float(totvel));
		vely = Float(vel_y) * velhori;							//RJS 17Oct00
//DeadCode RJS 17Oct00 		vely /= velhori;

		Math_Lib.high_sin_cos(pitch,sin_ang,cos_ang);

		if (sin_ang > (cos_ang*vely))	//pitchdown
			pitch -= (Angles)Timer_Code.FRAMETIME*10;
		else
			pitch += (Angles)Timer_Code.FRAMETIME*10;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchACTransient
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
void	TransObj::LaunchACTransient(mobileitem*	launcher, ShapeNum theShape, WorldStuff& worldptr)
{
	TransientItem*	newitem;
	newitem = LaunchUnguidedMissile(	launcher,				
										theShape,
										3000,
										MOBILE_DEADAC	);

	if (newitem)
	{
// We definitely don't want invisible fuselages!!!!
		AircraftAnimData*	adptr = (AircraftAnimData*)launcher->Anim;	//RJS 13Jul00
		if (adptr->OTHER == 255)										//RJS 13Jul00
			adptr->OTHER = 254;											//RJS 13Jul00

		SHAPE.ACtoSAG((AirStrucPtr)*launcher,newitem->Anim);

		adptr->itemstate = DEAD;		//so it doesn't re-launch from airstruc

		if (	View_Object												//RJS 27Jul00
			&&	(launcher==View_Object->trackeditem2)	)				//RJS 27Jul00
			newitem->LaunchTime += 3000;								//RJS 27Jul00

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoRaidAlert
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
void	TransObj::DoRaidAlert(UWord	uniqueid)				//RJS 09Mar00
{
//DeadCode RJS 09Mar00	UWord			uniqueid = raiditem->uniqueID.count;
	SLong			sector_no;
	ItemPtr			tmpitemptr;
	ItemPtr			firstitemptr;
	UniqueIDBand	uidband;
	Coords3D		location;
	WorldStuff*		worldptr = mobileitem::currworld;
	MinAnimData*	mad;
	mobileitem*		mitem;
	SLong			noSirens = 4;							//RJS 09Mar00

//DeadCode RJS 09Mar00	_Miles.PlayOnce(FIL_SFX_DISTANT_ALARM3,raiditem);

	sector_no = -1;
	while (worldptr->NextItem(sector_no,tmpitemptr))
	{
		if (tmpitemptr->SGT == uniqueid)
		{
			if (tmpitemptr->Status.size >= MOBILESIZE)
			{
				mad = (MinAnimData*)tmpitemptr->Anim;
				if (	!mad->IsInvisible
					&&	(mad->itemstate != DEAD)	)
				{
					mitem = (mobileitem*)tmpitemptr;
					uidband = Persons2::getbandfromUID((UniqueID)tmpitemptr->uniqueID.count);
					switch (uidband)
					{
						case BlokeBAND:
						{
							bool	chicken = false;

							firstitemptr = worldptr->getfirstitem(UWord(sector_no));
							if (!SHAPE.SafestPlace(firstitemptr,tmpitemptr,location))
								chicken = true;

							PointBloke(mitem,location,chicken);

							mitem->movecode = GROUND_BLOKEFREAK;
							FormationItemPtr(mitem)->manoeuvretime = 50;
						}
						break;
						case EmergencyVehicleBAND:
						case GermMobileBAND:
						case BritMobileBAND:
						{
							mitem->movecode = GROUND_HALTTRUCK;
							if (mitem->Status.size == FORMATIONSIZE)
							{
								FormationItem* fitem = (FormationItem*)mitem;
								fitem->manoeuvretime = 100 + Math_Lib.rnd(150);
							}
						}
						break;
					}
				}
			}
			else
			{
				if (noSirens)
				{
					_Miles.PlayOnce(FIL_SFX_DISTANT_ALARM3,tmpitemptr);
					noSirens--;
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoRaidEnd
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
void	TransObj::DoRaidEnd(UWord			uniqueid)			//RJS 09Mar00
{
//DeadCode RJS 09Mar00 	UWord			uniqueid = raiditem->uniqueID.count;
	SLong			sector_no;
	ItemPtr			tmpitemptr;
	ItemPtr			firstitemptr;
	UniqueIDBand	uidband;
	Coords3D		location;
	WorldStuff*		worldptr = mobileitem::currworld;
	MinAnimData*	mad;
	mobileitem*		mitem;


	sector_no = -1;
	while (worldptr->NextItem(sector_no,tmpitemptr))
	{
		if (tmpitemptr->SGT == uniqueid)
		{
			if (tmpitemptr->Status.size >= MOBILESIZE)
			{
				mad = (MinAnimData*)tmpitemptr->Anim;
				if (mad->itemstate != DEAD)
				{
					mitem = (mobileitem*)tmpitemptr;

					uidband = Persons2::getbandfromUID((UniqueID)tmpitemptr->uniqueID.count);
					switch (uidband)
					{
						case BlokeBAND:
						{
							//Jump to next way-point, and restart

							mad->IsInvisible = 0;
							mitem->movecode = GROUND_BLOKE;
							if (mitem->Status.size == FORMATIONSIZE)
							{
								//Wait between 1 - 2 mins before re-starting
								FormationItem* fitem = (FormationItem*)mitem;
								fitem->manoeuvretime = 500 + Math_Lib.rnd(500);
							}
							mitem->World.Y = GetGroundLevel(mitem);
						}
						break;
						case EmergencyVehicleBAND:
						{
							mitem->movecode = GROUND_TAXI;
							if (mitem->Status.size == FORMATIONSIZE)
							{
								//Wait between 5 - 10 mins before re-starting
								FormationItem* fitem = (FormationItem*)mitem;
								fitem->manoeuvretime = Math_Lib.rnd(500);
							}
						}
						break;
						case GermMobileBAND:
						case BritMobileBAND:
						{
							mitem->movecode = GROUND_TAXI;
							if (mitem->Status.size == FORMATIONSIZE)
							{
								//Wait between 5 - 10 mins before re-starting
								FormationItem* fitem = (FormationItem*)mitem;
								fitem->manoeuvretime = 30000 + Math_Lib.rnd(30000);
							}
						}
						break;
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBloke
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
void	TransObj::LaunchBloke(ItemPtr	launcher, Coords3D&	destpos, bool mental, WorldStuff&	world)
{
	bool	lowpriority = false;
	if (desiredFPS > realFPS)
		lowpriority = true;

	TransientItem*	newitem;
	SLong			randindex;

	newitem = LaunchUnguidedMissile((mobileitem*)launcher,
									launcher->shape,
									LIFETIME_TROOP,
									MOBILE_TROOP,
									TRUE);			//inherit animdata
	if (newitem)
	{
		PointBloke(newitem,destpos,mental);

		newitem->TransRandom = 50;

		if (lowpriority)
			newitem->TimeOfLaunch -= 3000;	//30 secs older

		newitem->Target = launcher;

		AddTransientItemToWorld(newitem, world);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchACRicochet
//Author		Robert Slater
//Date			Fri 14 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchACRicochet(mobileitem* launcher,WorldStuff& worldptr)
{
#ifdef	_SOUND_TEST_
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										BALLON,
										60000,MOBILE_STATIONARY);
	if (newitem)
	{
		newitem->TransRandom = 1000;

		AddTransientItemToWorld(newitem, worldptr);
	}
#else
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										SPARK,
										4,MOBILE_STATIONARY);
	if (newitem)
	{
		UWord	random = Math_Lib.rnd();

		AddTransientItemToWorld(newitem, worldptr);
		if (random > 32767)
		{
			random -= 32768;
			if (random > 16383)
			{
// Have sparks
				random -= 16384;

				// Select spark frame...

				random *= 4;
				random >>= 14;

				newitem = SimplifiedSpriteLaunch(	launcher,
													RICSPK,
													4,
													MOBILE_STATIONARY	);
				if (newitem)
				{
					DebrisAnimData*	adptr = (DebrisAnimData*) newitem->Anim;
					adptr->frameno = random;

					AddTransientItemToWorld(newitem, worldptr);
				}
			}
			else
			{
// Have smoke
				newitem = SimplifiedSpriteLaunch(	launcher,
													SMKPFF,
													100,
													MOBILE_STATIONARY	);
				if (newitem)
					AddTransientItemToWorld(newitem, worldptr);

				if (random < 2048)
				{
// Have a/c debris
					random *= 6;
					random >>= 11;

					LaunchDebris(launcher,ACBTS0,4,random,worldptr);
				}
			}
		}
	}
#endif
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobilePAC
//Author		Robert Slater
//Date			Thu 3 Feb 2000
//
//Description	Flies high, then drops & opens its chute,
//				then changes movecode.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobilePAC(TransientItemPtr transit,WorldStuff& worldptr)
{
	int timeleft=transit->LaunchTime;
	if (timeleft>0)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		// While frametime is in 50ths
		if ((transit->LaunchTime & 0x04)==0)
		{
			Coords3D hitcoords;
			SLong	groundheight;
			UByte	theArea;

			groundheight = GetGroundLevel(transit,theArea);

			if (transit->World.Y<=groundheight)
			{
				transit->World.Y = groundheight;
				transit->LaunchTime = 0;

				if (!transit->TransRandom)
				{
					SLandLight lightDef;
					lightDef.pos=transit->World;
					lightDef.color.r=0xFF00;
					lightDef.color.g=0xFF00;
					lightDef.color.b=0xFF00;
					lightDef.timer=50;	//half a second
					lightDef.range=25000;	//quarter km

//deadcode JON 19/06/01						Land_Scape.AddLight(&lightDef);
					LaunchSmallFlash(transit,worldptr);
				}
				else
					LaunchDustRing(transit,worldptr);
			}
			else
			{
				if (transit->TransRandom == 1)
					BoxCol::NineSectorColAircraft(transit);
			}
		}

		if (transit->LaunchTime>0)
		{
			if (!transit->TransRandom)
				GAndFriction(transit,0);		//shoot
			else
				GAndFriction(transit,2000);		//floaty
		}
	}
	else
	{
		if (transit->TransRandom)
			AddTransientItemToDeadList(transit);
		else
		{
// Trigger parachute anim...
			MinAnimData*	mad = (MinAnimData*) transit->Anim;
			mad->itemstate = ALIVE;

			transit->pitch = ANGLES_0Deg;
			transit->LaunchTime = 1000;	//10 secs
			transit->TransRandom = 1;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchEngineStartup
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
void	TransObj::LaunchEngineStartup(mobileitem* launcher,WorldStuff& worldptr, bool isPacket)
{
	if (	((launcher->vel_ < VEL_10MPH) || isPacket)					//RJS 21Jun00
		&&	(SHAPESTUFF.GetShapeScale(SHAPESTUFF.GetShapePtr(launcher->shape))!=SHP_GRP)	)	//RJS 31May00
	{
		TransientItem*	newitem;

		newitem = SimplifiedSpriteLaunch(	launcher,
											EMPTY,
											100,MOBILE_ENGINESTART);
		if (newitem)
		{
			if (	(launcher == Persons2::PlayerSeenAC)		//RJS 21Jun00
				&&	(_Replay.Record || _DPlay.Implemented)
				&&	!isPacket								)			//AMM 13Jul00
				_DPlay.NewEngineAnimPacket();

			newitem->TransRandom = 0;
			AddTransientItemToWorld(newitem, worldptr);
		}

		_Miles.PlayOnce(FIL_SFX_STARTER_ELECTRIC_FIRE,launcher);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchEmergencyDudes
//Author		Robert Slater
//Date			Fri 25 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchEmergencyDudes(mobileitem* launcher, Coords3D& worldPos,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										BLOKE,
										6000,MOBILE_STATIONARY);
	if (newitem)
	{
		SLong	dx = worldPos.X - launcher->World.X;
		SLong	dz = worldPos.Z - launcher->World.Z;
		Float	distance,sinAng,cosAng;
		SWord	hdg;
		SLong	newx,newz;
		UByte	theArea;

		distance = Float(fastMath.FastSqrt(float(dx*dx+dz*dz)));

		hdg = Math_Lib.HighArcTan(dz,dx);

		Math_Lib.high_sin_cos(Angles(hdg),sinAng,cosAng);

		fastMath.FloatToInt(&newx,float(sinAng*distance));
		fastMath.FloatToInt(&newz,float(cosAng*distance));

		newitem->World.X += newx;
		newitem->World.Z += newz;
		newitem->World.Y = GetGroundLevel(newitem,theArea);
		newitem->hdg = Angles(hdg);

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RaidAlert
//Author		Robert Slater
//Date			Thu 9 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::RaidAlert(ItemPtr	raiditem)
{
	if (raiditem)
		NewRaid(raiditem->uniqueID.count,60000);	// 10 mins default to raid end
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewRaid
//Author		Robert Slater
//Date			Thu 9 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::NewRaid(UWord	uid, SLong raidendtime)
{
	if (uid)
	{
		for (SLong index=0; index < raidCount; index++)
		{
			if (raidList[index].uid == uid)
				break;
		}

		if (	(index == raidCount)
			&&	(index < 32)		)
		{
			DoRaidAlert(uid);

			raidList[index].uid = uid;
			raidList[index].timeout = raidendtime;

			raidCount++;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RaidEnd
//Author		Robert Slater
//Date			Thu 9 Mar 2000
//
//Description	Will bump the raid time-out to 3 30 seconds
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::RaidEnd(ItemPtr	raiditem)
{
	if (raiditem)												//RJS 29Sep00
	{
		SLong	index;
		UWord	uid = raiditem->uniqueID.count;

		for (index=0; index < raidCount; index++)
		{
			if (raidList[index].uid == uid)
			{
				raidList[index].timeout = 3000;		// 30 secs to raid end
				break;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateRaids
//Author		Robert Slater
//Date			Thu 9 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::UpdateRaids()
{
	SLong	index;
	SLong	newCount = 0;

	for (index=0; index < raidCount; index++)
	{
		raidList[index].timeout -= Timer_Code.FRAMETIME;
		if (raidList[index].timeout <= 0)
			DoRaidEnd(raidList[index].uid);
		else
		{
			if (newCount != index)
				raidList[newCount] = raidList[index];

			newCount++;
		}
	}

	raidCount = newCount;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearPath
//Author		Robert Slater
//Date			Wed 19 Apr 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	TransObj::ClearPath(Coords3D&	eye, Coords3D& target, Coords3D& object, SLong radius)
{
	Float	et_x, et_y, et_z;
	Float	eo_x, eo_y, eo_z;
	Float	to_x, to_y, to_z;
	Float	radiussquared = Float(radius*radius);	//I don't think this will ever overflow
	Float	det, deo, ratio, dto;

	et_x = target.X - eye.X;
	et_y = target.Y - eye.Y;
	et_z = target.Z - eye.Z;

	eo_x = object.X - eye.X;
	eo_y = object.Y - eye.Y;
	eo_z = object.Z - eye.Z;

	det = et_x*et_x + et_y*et_y + et_z*et_z;
	deo = eo_x*eo_x + eo_y*eo_y + eo_z*eo_z;

	ratio = deo / det;

	et_x *= ratio;
	et_y *= ratio;
	et_z *= ratio;

	et_x += Float(eye.X);
	et_y += Float(eye.Y);
	et_z += Float(eye.Z);

	to_x = Float(target.X) - et_x;
	to_y = Float(target.Y) - et_y;
	to_z = Float(target.Z) - et_z;

	dto = to_x*to_x + to_y*to_y + to_z*to_z;

	if (dto > radiussquared)
		return true;

	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BirdCentralControl
//Author		Robert Slater
//Date			Wed 26 Apr 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::BirdCentralControl(ItemPtr	launcher, ShapeNum launchershape, SLong groupindex, WorldStuff& worldptr)
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(launchershape);
	if (sdptr->AnimDataSize == BIRDLAUNCHERANIM)
	{
		MyGroundVector			pos;
		ShapeNum				shapehit;
		UWord					ghdg;
		BirdLauncherAnimData* 	adptr;
		
		adptr = (BirdLauncherAnimData*) SHAPE.GetGroupItemAnimHdg(launcher,shapehit,groupindex,&pos,ghdg);
		if (	!adptr->IsInvisible
			&&	(adptr->itemstate != DEAD)
			&&	adptr->isPregnant			)
		{
			adptr->isPregnant = 0;

			LaunchBirds((mobileitem*)launcher,launcher->World,ShapeNum(adptr->theShape),8,worldptr);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ControlDummyBloke
//Author		Robert Slater
//Date			Wed 26 Apr 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ControlDummyBloke(ItemPtr	theItem)
{
//DeadCode RJS 20Oct00 	WorldStuff*	worldptr = mobileitem::currworld;
	TroopAnimData* adptr = (TroopAnimData*)theItem->Anim;
	UWord	randfactor = Math_Lib.rnd();
	if (randfactor > 49152)
	{
		if (adptr->hasfriend)
		{
			if (Anim_Control.Finished(theItem,ANIMATION_TALK) || Anim_Control.NeverStarted(theItem,ANIMATION_TALK))
				Anim_Control.SetPlayerAnim(theItem,ANIMATION_TALK);
		}
		else
		{
			if (!adptr->nofriends && (randfactor > 64512))
			{
/*				SLong		thisSector = worldptr->GetSector(theItem);
				Coords3D*	blokeList[128];
				float		blokedistList[128];
				Coords3D*	objList[128];
				float		objdistList[128];
				UWord		objsizeList[128];
				SLong		blokeCnt = 0;
				SLong		objCnt = 0;
				ItemPtr		tmpitem;
				ItemPtr		firstitem;
				UniqueIDBand	uidBand;
				float		dx,dy,dz;
				ShapeDescPtr	sdptr;
				float		nearestbloke = float(SLong(0x7FFFFFFF));
				SLong		nearestIndex = 0;


				// Look for friend...

				tmpitem = firstitem = worldptr->getfirstitem(thisSector);
				while (tmpitem)
				{
					if (tmpitem != theItem)
					{
						uidBand = Persons2::getbandfromUID(UniqueID(tmpitem->uniqueID.count));
						if (uidBand == BlokeBAND)
						{
							if (blokeCnt < 128)
							{
								dx = tmpitem->World.X - theItem->World.X;
								dy = tmpitem->World.Y - theItem->World.Y;
								dz = tmpitem->World.Z - theItem->World.Z;

								blokeList[blokeCnt] = &tmpitem->World;
								blokedistList[blokeCnt] = dx*dx+dy*dy+dz*dz;

								if (blokedistList[blokeCnt] < nearestbloke)
								{
									nearestbloke = blokedistList[blokeCnt];
									nearestIndex = blokeCnt;
								}

								blokeCnt++;
							}
						}
						else
						{
							if (objCnt < 128)
							{
								sdptr = SHAPESTUFF.GetShapePtr(tmpitem->shape);

								dx = tmpitem->World.X - theItem->World.X;
								dy = tmpitem->World.Y - theItem->World.Y;
								dz = tmpitem->World.Z - theItem->World.Z;

								objList[objCnt] = &tmpitem->World;
								objdistList[objCnt] = dx*dx+dy*dy+dz*dz;
								objsizeList[objCnt] = sdptr->Size<<4;

								objCnt++;
							}
						}
					}
				}

				if (blokeCnt && objCnt)
				{
					SLong	blokeIndex;
					SLong	objIndex;
					SLong	hits = 0;
					SLong	cleared = 0;

					if (randfactor > 65000)
						blokeIndex = Math_Lib.rnd(blokeCnt);
					else
						blokeIndex = nearestIndex;

					for (objIndex = 0; objIndex < objCnt; objIndex++)
					{
						if (objdistList[objIndex] < blokedistList[blokeIndex])
						{
							hits++;
							if (ClearPath(theItem->World,*blokeList[blokeIndex],*objList[objIndex],objsizeList[objIndex]))
								cleared++;
						}
					}

					if (hits == cleared)
					{
						// We have the technology....

					}
				}
				else
					adptr->nofriends = 1;*/
			}
			else
			{
				if (Anim_Control.Finished(theItem,ANIMATION_BORED) || Anim_Control.NeverStarted(theItem,ANIMATION_BORED))
					Anim_Control.SetPlayerAnim(theItem,ANIMATION_BORED);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchExplodePuff
//Author		Robert Slater
//Date			Mon 22 May 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchExplodePuff(mobileitem*	launcher, SLong height, ShapeNum theShape, SLong lifetime, WorldStuff& world)
{
	if (	(realFPS > desiredFPS)					
		&&	(Math_Lib.rnd() > 32767)				)
	{
		Coords3D	pos = launcher->World;
		pos.Y += height;

		LaunchSmokePuff2(launcher,pos,theShape,NULL,0,50*1000,0,lifetime,lifetime,world);	//RJS 6Nov00
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveBlokeWithBrain
//Author		Robert Slater
//Date			Mon 22 May 2000
//
//Description	Used by real blokes and transient blokes
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MoveBlokeWithBrain(mobileitem* transit, UWord& timer)
{
	TroopAnimData*	adptr = (TroopAnimData*) transit->Anim;
	UWord			voxrand = Math_Lib.rnd();
	SWord			timedist;

	timedist = SWord(timer);
	timedist -= Timer_Code.FRAMETIME;
	if (timedist < 0)
	{
		timer = 50;

		if (adptr->homing)
		{
			SLong	dx, dy, dz;
			SLong	distance;
			SWord	hdg2;					
			SWord	newhdg;
			SWord	thehdg;

			dx = adptr->xpos - transit->World.X;
			dy = adptr->ypos - transit->World.Y;
			dz = adptr->zpos - transit->World.Z;

			distance = Math_Lib.distance3d(dx,dy,dz);
			thehdg = Math_Lib.arctan(dx,dz);

			if (adptr->oncourse == FALSE)
			{
				hdg2 = transit->hdg;				
				newhdg = (thehdg - hdg2) >> 1;

				if (newhdg == 0)
				{
					adptr->oncourse = TRUE;
					transit->hdg = Angles(thehdg);
				}
				else
				{
					hdg2 += newhdg;
					transit->hdg = Angles(hdg2);
				}
			}

			if (distance < 100)
			{
				if (transit->Status.size == TRANSIENTSIZE)
					TransientItemPtr(transit)->LaunchTime = 0;
				else
					transit->movecode = AUTO_NOPPILOT;
			}
		}
		else
		{
			transit->hdg = (Angles) (transit->hdg + Math_Lib.rnd(ANGLES_10Deg) - ANGLES_5Deg);	//RJS 26Oct00
			timer += ((50*voxrand)>>16);
		}
		
		Float	sin_ang, cos_ang;
		Float	theVel = Float(transit->vel_);
		Math_Lib.high_sin_cos(transit->hdg, sin_ang, cos_ang);
		fastMath.FloatToInt(&transit->vel_x,float(theVel * sin_ang));
		fastMath.FloatToInt(&transit->vel_z,float(theVel * cos_ang));
	}
	else
		timer = UWord(timedist);

	if (voxrand > 65000)
	{
		voxrand = ((65536 - voxrand)*3)/536;
		if ((((adptr->BITSOFFFLAGS>>BF_ONFIRE)&0x01))!=0)
//DeadCode RJS 14Jun00 			_Miles.PlayOnce((FileNum)(FIL_SFX_VOCAL_ENEMY1 + voxrand),transit,48,FIL_SFX_VOCAL_ENEMY1,FIL_SFX_VOCAL_ENEMY4);
//DeadCode RJS 14Jun00 		else
			_Miles.PlayOnce((FileNum)(FIL_SFX_YELP1 + voxrand),transit,48,FIL_SFX_YELP1,FIL_SFX_YELP4);
	}

	ApplyVelocities(transit);

	transit->pitch = ANGLES_0Deg;

	if ((timedist & 0x04)==0)
		transit->World.Y = GetGroundLevel(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PointBloke
//Author		Robert Slater
//Date			Mon 22 May 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::PointBloke(mobileitem*	launcher, Coords3D&	destpos, bool mental)
{
	TroopAnimData*	adptr = (TroopAnimData*) launcher->Anim;
	tAnimation		theAnim;
	UWord			randval = Math_Lib.rnd();

	adptr->oncourse = FALSE;
	adptr->homing = FALSE;
	if (!mental)
	{
		adptr->xpos = destpos.X;								
		adptr->ypos = destpos.Y;
		adptr->zpos = destpos.Z;

		// Someone might panic!!!!!... headless chicken code
		if (Math_Lib.rnd()<60000)
		{
			theAnim = ANIMATION_RUN;
			adptr->homing = TRUE;
		}
		else
		{
			launcher->hdg = Angles(randval);
			theAnim = ANIMATION_RUNCHICKEN;
		}
	}
	else
	{
		launcher->hdg = Angles(randval);
		theAnim = ANIMATION_RUNCHICKEN;
	}

	Anim_Control.SetPlayerAnim(launcher,theAnim);

	// Run velocity = 6ms to 9ms
	Float		vel = 60000. + (Float(randval)*0.457763671875);

	launcher->vel_y = 0;

	Float sin_ang, cos_ang;
	Math_Lib.high_sin_cos(launcher->hdg, sin_ang, cos_ang);
	launcher->vel_x = vel * sin_ang;
	launcher->vel_z = vel * cos_ang;
	launcher->vel_ = vel;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBlowCanopy
//Author		Robert Slater
//Date			Wed 14 Jun 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchBlowCanopy(mobileitem* launcher, WorldStuff& worldptr)
{
	if (launcher->Status.size == AIRSTRUCSIZE)
	{
		ShapeDescPtr sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);
		if (sdptr->AnimDataSize == AIRCRAFTANIM)
		{
			AircraftAnimData* adptr = (AircraftAnimData*) launcher->Anim;
			if (adptr->CANOPY != BS_DEAD)
			{
				TransientItemPtr	newitem=LaunchUnguidedMissile(launcher,launcher->shape,75,MOBILE_GANDF);
				if (newitem)
				{
					newitem->Anim.SetItemState(DEAD);

					SetBitsOff(launcher->shape,launcher->Anim,newitem->Anim,&adptr->CANOPY-&launcher->Anim);

					AddTransientItemToWorld(newitem, worldptr);

//DeadCode RJS 9Nov00 					_Miles.PlayOnce(FIL_SFX_CANOPY_BLOW, launcher);
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EjectParachutist
//Author		Robert Slater
//Date			Wed 26 Jul 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::EjectParachutist(mobileitem*	launcher, UWord& blokesleft, UWord totblokes, WorldStuff& world)
{
	Coords3D	pos;
	SWord		relypos;
	bool		trackthis = false;

	SHAPE.GetPilotPos(launcher,totblokes-blokesleft,pos,relypos);

	blokesleft--;
	if (blokesleft == (totblokes>>1))
		trackthis = true;

	LaunchParachute(launcher,pos,relypos,world,trackthis);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTurbulance
//Author		Robert Slater
//Date			Mon 21 Aug 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchTurbulance(mobileitem* launcher,UByte strength,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										TURB,
										54,MOBILE_DODAMAGE);
	if (newitem)
	{
		if (launcher->Status.size == TRANSIENTSIZE)	
			newitem->Launcher = ((TransientItem*)launcher)->Launcher;

		MissileAnimData*	adptr = (MissileAnimData*) newitem->Anim;
 		adptr->hitstrength = strength;				

		newitem->isArmed = 1;					

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckCommsValid
//Author		Robert Slater
//Date			Wed 20 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline	bool	TransObj::CheckCommsValid(const ItemPtr	theItem)
{
	if (theItem && (theItem->Status.size >= MOBILESIZE))
	{
		if (_DPlay.Implemented && MobileItemPtr(theItem)->movecode == AUTO_FOLLOWWP)
			return false;

		if (MobileItemPtr(theItem)->movecode == AUTO_RESURRECT)
			return false;

		return true;
	}

	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchHitGrass
//Author		Robert Slater
//Date			Tue 26 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchHitGrass(mobileitem* launcher, const SLong& gheight, WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										SmallScatFireShape,
										100*60,MOBILE_STATIONARY);
	if (newitem)
	{
		newitem->World.Y = gheight;

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileBomb1stFrame
//Author		Robert Slater
//Date			Tue 03 Oct 2000
//
//Description	We don't want to move the bomb if it's been launched this frame...
//				... otherwise the bomb will move 1 frame ahead of its launcher.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileBomb1stFrame(TransientItemPtr transit,WorldStuff& world)
{
	transit->movecode = MOBILE_BOMBDROP;

	if (	(transit->TimeOfLaunch != View_Object->TimeOfDay())			//RJS 18Oct00
		||	_Replay.Playback	)										//RJS 18Oct00
		MobileBombDrop(transit,world);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTotalAmmo
//Author		Robert Slater
//Date			Thu 05 Oct 2000
//
//Description
//			
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::SetTotalAmmo(AirStrucPtr	ac)
{
// Cannot check for Persons2::PlayerSeenAC, cos it hasn't been set first time through.
	if (ac==Manual_Pilot.ControlledAC2)										//RJS 12Oct00
	{
		int	currentweapon = ac->weap.weapontype & LT_MASK;					//RJS 12Oct00
		if (currentweapon != LT_BOMB)										//RJS 12Oct00
		{
			PolyPitAnimData*	adptr = (PolyPitAnimData*)ac->Anim;
			int					othercurrentweapon = currentweapon;
			int					totalammo = 0;
			int					cannonammo = 0;

			if (currentweapon == LT_ANYWEAPON)
			{
				currentweapon = LT_BULLET;
				othercurrentweapon = LT_CANNON;
			}

			WeapAnimData*	weapon = adptr->weaponlaunchers;
			for (int index=0; index < adptr->nolaunchers; index++)
			{
				if (weapon)
				{
					if (	((weapon->LauncherType & LT_MASK) == currentweapon)
						||	((weapon->LauncherType & LT_MASK) == othercurrentweapon)	)
						totalammo+= weapon->LoadedStores;

					if ((weapon->LauncherType&LT_MASK)==LT_CANNON)		//RJS 17Oct00
						cannonammo += weapon->LoadedStores;				//RJS 17Oct00

					weapon++;
				}
			}

			adptr->actotalammoleft = totalammo;

			adptr->accannonammoleft = cannonammo;
		}
	}
}

void	TransObj::ReloadBomb(AirStrucPtr ac)
{
	MoveGunAnimData*	adptr = (MoveGunAnimData*) ac->Anim;
	WeapAnimData*	weapon;
	int				index;

	if (ac->classtype->aerobaticfactor != AEROBATIC_LOW)
	{
		weapon = adptr->weaponlaunchers;									
		for (index=0; index < adptr->nolaunchers; index++)					
		{
			if (weapon)														
			{
				if ((weapon->LauncherType&LT_MASK) == LT_BOMB)
					weapon->LoadedStores = weapon->Stores;

				weapon++;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearGunFlash
//Author		Robert Slater
//Date			Sun 29 Oct 2000
//
//Description
//			
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ClearGunFlash(const ItemPtr	shooter)
{
	if (shooter)
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shooter->shape);
		if (sdptr->AnimDataSize == AIRCRAFTANIM)
		{
			AircraftAnimData*	adptr = (AircraftAnimData*)shooter->Anim;

			adptr->gunshooting = adptr->cannonshooting = 0;
		}
	}
}
