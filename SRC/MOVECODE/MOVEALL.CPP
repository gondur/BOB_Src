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
//Filename       moveall.cpp
//System         
//Author         Jim Taylor
//Date           Thu 15 Feb 1996
//Description    The code which moves all the items in the world
//				 This module also manages the lists which move the objects
//------------------------------------------------------------------------------
//DeadCode RJS 11Jul00 #define		DBGMEMTEST

#include	"dosdefs.h"											//JIM 17Nov96
	#define F_COMMON
	#define F_GRAFIX
	#define F_BATTLE
#include	"files.g"  
//TEMPCODE DAW 13/04/00 #include	"textref.h"
#include	"world.h"
#include	"worldinc.h"
#include	"flymodel.h"
#include	"transite.h"
#include	"Files.g"
#include	"persons2.h"
#include	"ai.h"
#include	"ranges.h"
#include	"mymath.h"
#include	"miles.h"
#include	"winmove.h"											//ARM 06Dec96
#include	"replay.h"
#include	"files.g"
#include	"worldinc.h"
#include	"planetyp.h"
#include	"myangles.h"
#include	"enumbits.m"
#include	"mytime.h"											//RDH 25Apr96
//MATHABLE	(ANGLES)
#include	"mymath.h"
#include	"vertex.h"
#include	"matrix.h"											//RDH 23May96
//TEMPCODE DAW 13/04/00 #include	"textref.h"
#include	"viewsel.h"											//PD 19Feb96
#include	"hardpasm.h"										//RDH 14Mar96
#include	"3dcom.h"											//PD 16Apr96
#include	"landscap.h"									//PD 15Mar96
#include	"missman2.h"										//JIM 22Aug96
#include	"savegame.h"
#include	"miles.h"											//DAW 04Jul96
#include	"world.h"											//DAW 04Jul96
#include	"transite.h"										//RDH 26Jul96
#include	"collided.h"										//PD 06Sep96
//DEADCODE DAW 04/02/00 #include	"speed.h"
#include	"ranges.h"
#include	"modvec.h"											//ARM 08Jan97
#include	"model.h"											//ARM 07Jan97
#include	"shapes.h"
#define	 sagmove_REQUIRED	SAGAirstruc:AirStruc
#include "sagmove.h"

#include	"monotxt.h"

//#define DEBUGMOVE

MobileItemPtr	mobileitem::SAGList=NULL;
MobileItemPtr	mobileitem::ACList=NULL;
MobileItemPtr	mobileitem::MobileList=NULL;
TransientItemPtr	TransientItem::TransientList=NULL;
WorldStuff*		mobileitem::currworld=NULL;
UByte	mobileitem::timerseed=0;
int		mobileitem::timeofday=0;


#ifndef	NDEBUG
//#define	_FRAMECOUNT_
#endif

static	bool	checkMemNow = false;

//extern Replay	_Replay;
//extern DPlay _DPlay;

#ifdef	_FRAMECOUNT_
static	int	frameCount = 0;												//RJS 14Aug00

#define AFX_CDECL __cdecl
typedef char CHAR;
#define CONST               const
typedef CONST CHAR *LPCSTR, *PCSTR;
typedef LPCSTR LPCTSTR;
void AFX_CDECL AfxTrace(LPCTSTR lpszFormat, ...);

#endif
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveAll
//Author		Jim Taylor
//Date			Thu 15 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void mobileitem::MoveAll(WorldStuff& world)
{
	for(AirStrucPtr ac = AirStrucPtr(ACList); ac; ac = AirStrucPtr(ac->nextmobile))
		ac->ai.moved = FALSE;

	MoveList(ACList, world);

	SAGAirstruc::MoveAllSAGs(world);

	MoveList(MobileList, world);

#ifdef	_FRAMECOUNT_
	UWord cw=GETFPCW();
	::AfxTrace("Frame: %d\n",frameCount++);
	SETFPCW(cw);	
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveAllTrans
//Author		Martin Alderton
//Date			Wed 20 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransientItem::MoveAllTrans(WorldStuff& world)
{
	MoveTransList(TransientList, world);
}

static UByte dontmove=0;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveList
//Author		Jim Taylor
//Date			Thu 15 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void mobileitem::MoveList(MobileItemPtr entry,WorldStuff& world)
{
#ifdef _OLDWORLD														//CSB 7Aug00
	static bool firstframe = true;
	if(firstframe)					//CSB 7Aug00
	{
		for(MobileItemPtr mob = ACList; mob; mob = mob->nextmobile)		//CSB 7Aug00
		{																//CSB 8Aug00
			mob->OldWorld = mob->World;									//CSB 7Aug00
			mob->OldSector = world.GetSector(mob);						//CSB 8Aug00
		}																//CSB 8Aug00
		for(mob = SAGList; mob; mob = mob->nextmobile)	//CSB 7Aug00
		{																//CSB 8Aug00
			mob->OldWorld = mob->World;									//CSB 7Aug00
			mob->OldSector = world.GetSector(mob);						//CSB 8Aug00
		}																//CSB 8Aug00
		firstframe = false;
	}
#endif																	//CSB 7Aug00

//	static x=0;
	currworld=&world;											//PD 12Jul96

#ifdef DEBUGMOVE
	FILE* fp;
	if (_Replay.Record)
	{
		fp=fopen("record.txt","at");
	}
	else if (_Replay.Playback)
	{
		fp=fopen("playback.txt","at");
	}
	else if (_DPlay.Implemented)
	{
		fp=fopen("commsac.txt","at");
	}
#endif

	while (entry)
	{
		ULong state=_Replay.GetState();

		if (_Replay.IsCampState(state))
		{
// only recycle ac in campaign.....

			if(!(timeofday & 0xff))
				if(entry->Status.size == AIRSTRUCSIZE)
					if(entry != Persons2::PlayerSeenAC)
						if(entry->movecode != AUTO_SPAREAC)
						{
							AirStrucPtr ac = AirStrucPtr(entry);
							MinAnimData* mad = (MinAnimData*)ac->Anim;
							if (	mad->IsInvisible					//RJS 10Oct00
								||	(ac->fly.pModel->CrashTime >= DEADTIMEOUT_RECYCLE)	)	//RJS 10Oct00
								ac->RecycleAC();
						}
		}

		MobileItemPtr	next=entry->nextmobile;
		UWord	oldsector=-1;										  //JIM 17/02/99
		if (entry->movecode!=AUTO_NOPPILOT)								  //JIM 17/02/99
			oldsector=	world.GetSector(*entry);					  //JIM 17/02/99
//DeadCode JIM 3Aug00 		else
//DeadCode JIM 3Aug00 			oldsector=-1;

		assert (entry!=Persons2::PlayerGhostAC)
		if((entry == Persons2::PlayerSeenAC) && (Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW))
		{
// Set fake engine sound...

// should go in here to keep ghostac upto date 

#ifdef DEBUGMOVE
			if (_Replay.Record || _Replay.Playback || _DPlay.Implemented)
			{
				UWord uid=entry->uniqueID.count;
//DeadCode AMM 12May99 				fprintf(fp,"%d X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d (ghost)\n",
				fprintf(fp,"%d ID=%x X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d (ghost)\n",
					_Replay.replayframecount,
					uid,
					Persons2::PlayerGhostAC->World.X,
					Persons2::PlayerGhostAC->World.Y,
					Persons2::PlayerGhostAC->World.Z,
					Persons2::PlayerGhostAC->hdg.a,
					Persons2::PlayerGhostAC->pitch.a,
					Persons2::PlayerGhostAC->roll.a,
					Persons2::PlayerGhostAC->vel_
					);
			}
#endif
			_DPlay.CheckGhost();

//DeadCode AMM 3Aug00 			FILE* g=fopen("preddel.txt","at");
//DeadCode AMM 3Aug00 			fprintf(g,"Prev: X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d\n",
//DeadCode AMM 3Aug00 				Persons2::PlayerGhostAC->World.X,
//DeadCode AMM 3Aug00 				Persons2::PlayerGhostAC->World.Y,
//DeadCode AMM 3Aug00 				Persons2::PlayerGhostAC->World.Z,
//DeadCode AMM 3Aug00 				Persons2::PlayerGhostAC->hdg.a,
//DeadCode AMM 3Aug00 				Persons2::PlayerGhostAC->pitch.a,
//DeadCode AMM 3Aug00 				Persons2::PlayerGhostAC->roll.a,
//DeadCode AMM 3Aug00 				Persons2::PlayerGhostAC->vel_);

			_DPlay.AddDeltas(Persons2::PlayerGhostAC,TRUE,4);
			_DPlay.PredictMove(Persons2::PlayerGhostAC);
			_DPlay.AddDeltas(Persons2::PlayerGhostAC,FALSE,4);
//DeadCode AMM 3Aug00 			fprintf(g,"Pred: X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d\n",
//DeadCode AMM 3Aug00 				Persons2::PlayerGhostAC->World.X,
//DeadCode AMM 3Aug00 				Persons2::PlayerGhostAC->World.Y,
//DeadCode AMM 3Aug00 				Persons2::PlayerGhostAC->World.Z,
//DeadCode AMM 3Aug00 				Persons2::PlayerGhostAC->hdg.a,
//DeadCode AMM 3Aug00 				Persons2::PlayerGhostAC->pitch.a,
//DeadCode AMM 3Aug00 				Persons2::PlayerGhostAC->roll.a,
//DeadCode AMM 3Aug00 				Persons2::PlayerGhostAC->vel_);
//DeadCode AMM 3Aug00 
//DeadCode AMM 3Aug00 			fclose(g);

			_DPlay.BackupGhost();
		}
		else
		{
#ifdef DEBUGMOVE
				if ((_Replay.Record || _Replay.Playback || _DPlay.Implemented) && entry->Status.size==AIRSTRUCSIZE )
				{
					ULong m=entry->movecode;
					ULong man=((AirStrucPtr)entry)->ai.manoeuvre;
					UWord uid=entry->uniqueID.count;
//DeadCode AMM 26Jul00 					UByte inform=((AirStrucPtr)entry)->information;

//DeadCode AMM 12May99 					fprintf(fp,"ID=%d inform=%d move=%d man=%d X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d\n",
//DEADCODE AMM 31/01/00 					fprintf(fp,"ID=%x X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d inform=%d move=%d man=%d\n",

//DeadCode AMM 26Jul00 					if (_Replay.replayframecount==9)
//DeadCode AMM 26Jul00 					{
//DeadCode AMM 26Jul00 						_Replay.DumpModelData((AirStrucPtr)entry);
//DeadCode AMM 26Jul00 					}

//DeadCode AMM 11Jul00 					fprintf(fp,"ID=%x X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d \n",
//DeadCode AMM 11Jul00 					fprintf(fp,"ID=%x if=%d mc=%d man=%d H=%d P=%d R=%d V=%d \n",

//DeadCode AMM 25Jul00 					UWord u=0;
//DeadCode AMM 25Jul00 					
//DeadCode AMM 25Jul00 					if (((AirStrucPtr)entry)->ai.unfriendly)
//DeadCode AMM 25Jul00 						u=entry->uniqueID.count;

//DeadCode AMM 26Jul00 					AirStrucPtr a=((AirStrucPtr)entry);

//DeadCode AMM 25Jul00 					for(PENGINE pEngine = a->fly.pModel->EngineList; pEngine; pEngine = pEngine->List.NextItem())
//DeadCode AMM 25Jul00 					{
//DeadCode AMM 25Jul00 						fprintf(fp,"ptx=%f pty=%f ptz=%f\n",
//DeadCode AMM 25Jul00 							pEngine->Speed);
//DeadCode AMM 25Jul00 					}

					fprintf(fp,"ID=%x MO=%d MA=%d X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d \n",
							uid,
//DeadCode AMM 25Jul00 							u,
//DeadCode AMM 11Jul00 							Math_Lib.rnd(),
//DeadCode AMM 11Jul00 							inform,
							m,
							man,
							entry->World.X,
							entry->World.Y,
							entry->World.Z,
							entry->hdg.a,
							entry->pitch.a,
							entry->roll.a,
							entry->vel_
							);
			}

#endif
			AutoMoveCodeTypeSelect	lastmovecode=entry->movecode;
  			if (entry->uniqueID.commsmove)
 			{
				if (entry->shape!=EMPTY)
				{
// AC with empty shape are not in world, so dont move them

					if (!mobileitem::currworld->vp->Accel())
					{
// not in accel predict 
// make other players ac props turn....

						AirStrucPtr	ac = AirStrucPtr(entry);			//RJS 12Jul00

						ac->fly.rpm = ac->fly.rpm1 = 2000;				//RJS 12Sep00

						ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(ac->shape);
						if (sdptr->AnimDataSize == AIRCRAFTANIM)
						{
							AircraftAnimData*	adptr = (AircraftAnimData*)ac->Anim;
							adptr->acrpm = (ac->fly.rpm * 3)/5;
							adptr->acrpm1 = (ac->fly.rpm1 * 3)/5;
						}
						else
						{
							if (sdptr->AnimDataSize == SIMPLEAIRCRAFTANIM)
							{
								SimpleAircraftAnimData*	adptr = (SimpleAircraftAnimData*)ac->Anim;
								adptr->acrpm = (ac->fly.rpm * 3)/5;
							}
						}

//DeadCode AMM 8Sep00 #ifndef NDEBUG															//CSB 20Jul00
//DeadCode AMM 8Sep00 						_DPlay.CheckPlayer2();
//DeadCode AMM 8Sep00 #endif																	//CSB 20Jul00
						_DPlay.PredictMove((AirStrucPtr)entry);
//DeadCode AMM 8Sep00 #ifndef NDEBUG															//CSB 20Jul00
//DeadCode AMM 8Sep00 						_DPlay.BackupPlayer2();
//DeadCode AMM 8Sep00 #endif																	//CSB 20Jul00
					}
					else
					{
// in accel need to move as no delta packets will arrive

						entry->movecode=AUTO_COMMSACCEL;
						MoveItem(entry,world);
					}

// update model pos.Y so that ac leaves behind contrails?

					AirStrucPtr ac = AirStrucPtr(entry);
					if(ac->fly.pModel)
					{
						ac->fly.pModel->Pos.x = ac->World.X;
						ac->fly.pModel->Pos.y = ac->World.Y;
						ac->fly.pModel->Pos.z = ac->World.Z;
					}
				}
			}
			else
			{
				ANGLES currhdg=entry->hdg;						//AMM 31Jul98

// only need temp checks if we are having gun camera when playing as gunner

				if(entry==Persons2::PlayerSeenAC)
				{
//DeadCode CSB 18Jul00 					_DPlay.CheckSeen();
					_DPlay.UpdateBomberSeen();
					Three_Dee.viewer_oldhdg   = Persons2::PlayerSeenAC->hdg;
					Three_Dee.viewer_oldpitch = Persons2::PlayerSeenAC->pitch;
					Three_Dee.viewer_oldroll  = Persons2::PlayerSeenAC->roll;
//DeadCode CSB 18Jul00 					_DPlay.BackupSeen();
				}


//DeadCode AMM 8Oct00 				if (_Replay.replayframecount==353 && entry->uniqueID.count==0x1300)
//DeadCode AMM 8Oct00 					INT3;

				MoveItem(entry,world);

				if(entry==Persons2::PlayerSeenAC)
				{
					// Fake engine sound for bombers...
					AircraftAnimData*	adptr = (AircraftAnimData*)Persons2::PlayerSeenAC->Anim;	//RJS 11May00
					static EngineInfo	enginedesc;						

					enginedesc.power = (Persons2::PlayerSeenAC->fly.rpm*255)/Persons2::PlayerSeenAC->classtype->maxrpm;
					if (enginedesc.power > 255)	enginedesc.power = 255;

					enginedesc.rpm_engine = Persons2::PlayerSeenAC->fly.rpm;
					enginedesc.rpm_starter = 0;
					enginedesc.rattle = adptr->ENGINELEFT;			
					enginedesc.cockpitnobble = 0;
					enginedesc.velocity = Persons2::PlayerSeenAC->vel_;	//RJS 9Jun00
					enginedesc.xoffset = 0;

					_Miles.PlayEngine(Persons2::PlayerSeenAC,enginedesc,enginedesc);
			 
					int gunnerammo = adptr->weaponlaunchers[SHAPE.GetRearGunner_Index()].LoadedStores;
					OverLay.SetInfoLineVals(Persons2::PlayerSeenAC->vel_ * 0.001, gunnerammo, Persons2::PlayerSeenAC->World.Y * (3.2808 / 100), Persons2::PlayerSeenAC->hdg / 182, Persons2::PlayerSeenAC->fly.thrustpercent); 

//DEADCODE CSB 11Oct00						PolyPitAnimData*	ppadptr = (PolyPitAnimData*)Persons2::PlayerSeenAC->Anim;
//DEADCODE CSB 11Oct00						int		totalammo = ppadptr->actotalammoleft;

//DEADCODE CSB 11Oct00				 		OverLay.SetInfoLineVals(Persons2::PlayerSeenAC->vel_ * 0.001, totalammo, Persons2::PlayerSeenAC->World.Y * (3.2808 / 100), Persons2::PlayerSeenAC->hdg / 182, Persons2::PlayerSeenAC->fly.thrustpercent); 	//RJS 5Oct00
					
					_DPlay.CheckGhost();
					_DPlay.UpdateBomberGhost();
					_DPlay.BackupGhost();
				}

				if (entry->uniqueID.changed)					//AMM 31Jul98
				{												//AMM 31Jul98
					if (entry->Status.size==AirStrucSize)		//AMM 31Jul98
					{											//AMM 31Jul98
						((AirStrucPtr)(entry))->fly.dhdg= (SWord)(entry->hdg - currhdg);			//AMM 31Jul98
					}											//AMM 31Jul98
				}												//AMM 31Jul98
			}
		}
		AutoMoveCodeTypeSelect	nextmovecode=entry->movecode;
#ifndef	NDEBUG
		if(		(!entry->uniqueID.changed) && (entry->movecode != AUTO_SPAREAC)		//AMM 31Jul98	//CSB 10Aug00
			&&	(oldsector != 0xffff) && (oldsector != world.GetSector(*entry))		)	//AMM 31Jul98	//CSB 10Aug00
		{
#ifdef __WATCOMC__
				INT3();
#endif
#ifdef __MSVC__
				INT3;
#endif
		}
#endif
		if (entry->uniqueID.changed && oldsector!=0xFFFF)				  //JIM 17/02/99
		{
			UWord	newsector=	world.GetSector(*entry);
#ifdef NDEBUG
			if (newsector!=oldsector)
#endif			//By not doing this test in debug mode I can track down problems more quickly.
			{
#ifndef NDEBUG
				AirStrucPtr ac = NULL;
				if(entry->Status.size == AIRSTRUCSIZE)
					ac = AirStrucPtr(entry);
#endif
				world.RemoveFromSector(entry,oldsector);
				world.AddToWorld(entry);
			}
			entry->uniqueID.changed = FALSE;						//RDH 26Jun96
		}
		else
			oldsector=oldsector;

#ifdef _OLDWORLD															//CSB 7Aug00
		entry->OldWorld = entry->World;										//CSB 7Aug00
		entry->OldSector = world.GetSector(*entry);							//CSB 8Aug00
		for(MobileItemPtr mob = ACList; mob; mob = mob->nextmobile)			//CSB 7Aug00
			if(mob != Persons2::PlayerGhostAC)								//CSB 7Aug00
			{
				AirStrucPtr ac = AirStrucPtr(mob);							//CSB 8Aug00
				if((mob->OldWorld.X != mob->World.X) || (mob->OldWorld.Z != mob->World.Z))
					INT3;													//CSB 7Aug00
				if(mob->OldSector != world.GetSector(mob))					//CSB 8Aug00
					INT3;													//CSB 8Aug00
			}																//CSB 8Aug00
#endif																		//CSB 7Aug00

		if(entry->Status.size == AIRSTRUCSIZE)							//CSB 12Oct00
			AirStrucPtr(entry)->ai.moved = TRUE;						//CSB 12Oct00

		entry=next;												//RDH 23Feb96
	}
#ifdef DEBUGMOVE
	if (_Replay.Record || _Replay.Playback || _DPlay.Implemented)
	{
		fprintf(fp,"\n");
		fclose(fp);
	}
#endif
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveList
//Author		Jim Taylor
//Date			Thu 15 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE JIM 31/05/00 #ifndef	NDEBUG
//DEADCODE JIM 31/05/00 	  int	Count_SetFlightParams=0;
//DEADCODE JIM 31/05/00 #endif
void mobileitem::MoveItem(MobileItemPtr entry,WorldStuff& world)
{
//DEADCODE JIM 31/05/00 #ifndef	NDEBUG
//DEADCODE JIM 31/05/00 	Count_SetFlightParams=0;
//DEADCODE JIM 31/05/00 #endif

#ifndef NDEBUG
/* TEST CODE CSB 14/07/99 */
/* TEST CODE CSB 14/07/99 */
/* TEST CODE CSB 14/07/99 */
/*
if((entry == Persons2::PlayerGhostAC->follower) || (entry == Persons2::PlayerSeenAC->follower))
	if(((!currworld->vp) || (!currworld->vp->Accel())) && (!(Persons2::PlayerSeenAC->fly.pModel->FrameCount & EVERY256cs)))
	{
		SWord y = 0;
		for(AirStrucPtr lead = Persons2::PlayerGhostAC->FindFormpos0(); lead; lead = lead->fly.nextflight)
			for(AirStrucPtr ac = lead; ac; ac = ac->Follower())
			{
				PrintVar(40, y, "%.0f ", FP(y));
				if(ac->movecode != AUTO_COMBAT)
				{
					PrintVar(43, y, "%.0f  ", FP(ac->movecode));
					PrintString(47, y, "----------------");
				}
				else
				{
					PrintString(43, y, "COM ");
					if((!ac->ai.unfriendly) || (ac->ai.unfriendly->Status.size != AirStrucSize))
						PrintString(47, y, "None ");
					else
						switch(AirStrucPtr(ac->ai.unfriendly)->fly.pModel->Type)
						{
							case AT_SPITFIRE:	PrintString(47, y, "SPIT ");	break;
							case AT_HURRICANE:	PrintString(47, y, "HURR ");	break;
							case AT_BF109:		PrintString(47, y, "M109 ");	break;
							case AT_BF110:		PrintString(47, y, "M110 ");	break;
							case AT_JU87B:		PrintString(47, y, "JU87 ");	break;
							case AT_DEFIANT:	PrintString(47, y, "DEFI ");	break;
							case AT_BLENHIEM:	PrintString(47, y, "BLEN ");	break;
							case AT_JU88:		PrintString(47, y, "JU88 ");	break;
							case AT_HE111:		PrintString(47, y, "H111 ");	break;
							case AT_DO17:		PrintString(47, y, "DO17 ");	break;
							case AT_HE59:		PrintString(47, y, "HE59 ");	break;
						}
					
					switch(ac->ai.manoeuvre)
					{
						case MANOEUVRE_SELECT:				PrintString(52, y, "SELECT ");				break;
						case MANOEUVRE_LOOKROUND:			PrintString(52, y, "LOOKROUND ");			break;
						case MANOEUVRE_WELDEDWINGMAN:		PrintString(52, y, "WELDEDWINGMAN ");		break;
						case MANOEUVRE_BAILOUT:				PrintString(52, y, "BAILOUT ");				break;
						case MANOEUVRE_TOPCOVER:			PrintString(52, y, "TOPCOVER ");			break;
						case MANOEUVRE_LINEABREAST:			PrintString(52, y, "LINEABREAST ");			break;
						case MANOEUVRE_PINCER:				PrintString(52, y, "PINCER ");				break;
						case MANOEUVRE_MULTIWAVE:			PrintString(52, y, "MULTIWAVE ");			break;
						case MANOEUVRE_DIVEANDZOOM:			PrintString(52, y, "DIVEANDZOOM ");			break;
						case MANOEUVRE_LEADPURSUIT:			PrintString(52, y, "LEADPURSUIT ");			break;
						case MANOEUVRE_LAGPURSUIT:			PrintString(52, y, "LAGPURSUIT ");			break;
						case MANOEUVRE_SPLITMANOEUVRE:		PrintString(52, y, "SPLITMANOEUVRE ");		break;
						case MANOEUVRE_HEADON:				PrintString(52, y, "HEADON ");				break;
						case MANOEUVRE_LINEASTERN:			PrintString(52, y, "LINEASTERN ");			break;
						case MANOEUVRE_BARRELROLLATTACK:	PrintString(52, y, "BARRELROLLATTACK ");	break;
						case MANOEUVRE_SCISSORS:			PrintString(52, y, "SCISSORS ");			break;
						case MANOEUVRE_MILDSCISSORS:		PrintString(52, y, "MILDSCISSORS ");		break;
						case MANOEUVRE_TURNINGFIGHT:		PrintString(52, y, "TURNINGFIGHT ");		break;
						case MANOEUVRE_SPLITS:				PrintString(52, y, "SPLITS ");				break;
						case MANOEUVRE_ZOOMANDDROP:			PrintString(52, y, "ZOOMANDDROP ");			break;
						case MANOEUVRE_STRAIGHTANDLEVEL:	PrintString(52, y, "STRAIGHTANDLEVEL ");	break;
						case MANOEUVRE_SPINOUT:				PrintString(52, y, "SPINOUT ");				break;
						case MANOEUVRE_DIVEFORHOME:			PrintString(52, y, "DIVEFORHOME ");			break;
						case MANOEUVRE_GOHOME:				PrintString(52, y, "GOHOME ");				break;
						case MANOEUVRE_MAKEFORFRIENDLY:		PrintString(52, y, "MAKEFORFRIENDLY ");		break;
						case MANOEUVRE_MOVEAWAY:			PrintString(52, y, "MOVEAWAY ");			break;
						case MANOEUVRE_ACCIDENTALSPINOUT:	PrintString(52, y, "ACCIDENTALSPINOUT ");	break;
						case MANOEUVRE_VERTICALLOOP:		PrintString(52, y, "VERTICALLOOP ");		break;
						case MANOEUVRE_IMMELMANNTURN:		PrintString(52, y, "IMMELMANNTURN ");		break;
						case MANOEUVRE_IMMELMANN:			PrintString(52, y, "IMMELMANN ");			break;
						case MANOEUVRE_STAYWITHPREY:		PrintString(52, y, "STAYWITHPREY ");		break;
						case MANOEUVRE_CLIMBFORHOME:		PrintString(52, y, "CLIMBFORHOME ");		break;
						case MANOEUVRE_STRAIGHTDIVE:		PrintString(52, y, "STRAIGHTDIVE ");		break;
						case MANOEUVRE_STANDONTAIL:			PrintString(52, y, "STANDONTAIL ");			break;
						case MANOEUVRE_SHOOTTOFRIGHTEN:		PrintString(52, y, "SHOOTTOFRIGHTEN ");		break;
						case MANOEUVRE_SHOOTTOOEARLY:		PrintString(52, y, "SHOOTTOOEARLY ");		break;
						case MANOEUVRE_GAINHEIGHT:			PrintString(52, y, "GAINHEIGHT ");			break;
						case MANOEUVRE_LAGROLL:				PrintString(52, y, "LAGROLL ");				break;
						case MANOEUVRE_EXTENSION:			PrintString(52, y, "EXTENSION ");			break;
						case MANOEUVRE_DIVINGSPIN:			PrintString(52, y, "DIVINGSPIN ");			break;
						case MANOEUVRE_REVERSETURN:			PrintString(52, y, "REVERSETURN ");			break;
						case MANOEUVRE_SELFASBAIT:			PrintString(52, y, "SELFASBAIT ");			break;
						case MANOEUVRE_JINK:				PrintString(52, y, "JINK ");				break;
						case MANOEUVRE_BREAKTURN:			PrintString(52, y, "BREAKTURN ");			break;
						case MANOEUVRE_LAZYTURN:			PrintString(52, y, "LAZYTURN ");			break;
						case MANOEUVRE_BREAKLOW:			PrintString(52, y, "BREAKLOW ");			break;
						case MANOEUVRE_BREAKHIGH:			PrintString(52, y, "BREAKHIGH ");			break;
						case MANOEUVRE_BREAK90:				PrintString(52, y, "BREAK90 ");				break;
						case MANOEUVRE_HIGBARRELROLL:		PrintString(52, y, "HIGBARRELROLL ");		break;
						case MANOEUVRE_PANICTURN:			PrintString(52, y, "PANICTURN ");			break;
						case MANOEUVRE_UNBALANCEDFLIGHT:	PrintString(52, y, "UNBALANCEDFLIGHT ");	break;
						case MANOEUVRE_LOWALT:				PrintString(52, y, "LOWALT ");				break;
						case MANOEUVRE_TURNTOHDGANDPITCH:	PrintString(52, y, "TURNTOHDGANDPITCH ");	break;
						case MANOEUVRE_HIGHYOYO:			PrintString(52, y, "HIGHYOYO ");			break;
						case MANOEUVRE_ZOOM:				PrintString(52, y, "ZOOM ");				break;
						case MANOEUVRE_LOWYOYO:				PrintString(52, y, "LOWYOYO ");				break;
						case MANOEUVRE_INTERCEPTHIGH:		PrintString(52, y, "INTERCEPTHIGH ");		break;
						case MANOEUVRE_GAINSPEED:			PrintString(52, y, "GAINSPEED ");			break;
						case MANOEUVRE_HEADONATTACK:		PrintString(52, y, "HEADONATTACK ");		break;
						case MANOEUVRE_LUFBERRY:			PrintString(52, y, "LUFBERRY ");			break;
						case MANOEUVRE_STEEPDIVE:			PrintString(52, y, "STEEPDIVE ");			break;
						case MANOEUVRE_UPANDUNDER:			PrintString(52, y, "UPANDUNDER ");			break;
						case MANOEUVRE_STALLTURN:			PrintString(52, y, "STALLTURN ");			break;
						case MANOEUVRE_SLASHINGATTACK:		PrintString(52, y, "SLASHINGATTACK ");		break;
						case MANOEUVRE_CLIMBTURN:			PrintString(52, y, "CLIMBTURN ");			break;
						case MANOEUVRE_ROLL360:				PrintString(52, y, "ROLL360 ");				break;
						case MANOEUVRE_STRAFFE:				PrintString(52, y, "STRAFFE ");				break;
						case MANOEUVRE_FLYTHROUGHCLOUD:		PrintString(52, y, "FLYTHROUGHCLOUD ");		break;
						case MANOEUVRE_SPINRECOVERY:		PrintString(52, y, "SPINRECOVERY ");		break;
						case MANOEUVRE_COLLISIONAVOIDANCE:	PrintString(52, y, "COLLISIONAVOIDANCE ");	break;
						case MANOEUVRE_COLLIDE:				PrintString(52, y, "COLLIDE ");				break;
					}
				}
				y++;
			}
	}
*/			
/*
	if( (entry->Status.size==AIRSTRUCSIZE) && ((entry == Persons2::PlayerGhostAC) || (entry == Persons2::PlayerGhostAC)))
	{
		if(((!currworld->vp) || (!currworld->vp->Accel())) || (!(Persons2::PlayerSeenAC->fly.pModel->FrameCount & EVERY256cs)))
		switch(Persons2::PlayerGhostAC->movecode)
		{
			case AUTO_FOLLOWWP:         PrintString(60, 2, "G AUTO_FOLLOWWP  ");     break;
			case AUTO_NOPPILOT:         PrintString(60, 2, "G AUTO_NOPPILOT  ");     break;
			case AUTO_WAIT4TIME:        PrintString(60, 2, "G AUTO_WAIT4TIME  ");     break;
			case AUTO_TAXI:             PrintString(60, 2, "G AUTO_TAXI  ");     break;
			case AUTO_TAKEOFF:          PrintString(60, 2, "G AUTO_TAKEOFF  ");     break;
			case GROUND_TAXI:		    PrintString(60, 2, "G GROUND_TAXI  ");     break;
			case GROUND_CORNERUPTO:		    PrintString(60, 2, "G GROUND_TAXI  ");     break;
			case GROUND_CORNERTURN:		    PrintString(60, 2, "G GROUND_TAXI  ");     break;
			case AUTO_TELLLEADER:		PrintString(60, 2, "G AUTO_TELLLEADER  ");     break;
															  
			case AUTO_SPIRAL2GROUND:	PrintString(60, 2, "G AUTO_SPIRAL2GROUND  ");     break;
			case AUTO_RESURRECT:		PrintString(60, 2, "G AUTO_RESURRECT  ");     break;
			case AUTO_DEATHSEQUENCE:	PrintString(60, 2, "G AUTO_DEATHSEQUENCE  ");     break;
			case AUTO_TRAININGPREMERGE: PrintString(60, 2, "G AUTO_TRAININGPREMERGE  ");     break;
			case AUTO_TRAININGACM:	    PrintString(60, 2, "G AUTO_TRAININGACM  ");     break;
			case AUTO_CRASHSKID:		PrintString(60, 2, "G AUTO_CRASHSKID  ");     break;
			case AUTO_CRASHROLL:		PrintString(60, 2, "G AUTO_CRASHROLL  ");     break;
															  
			case AUTO_BOMB:             PrintString(60, 2, "G AUTO_BOMB  ");     break;
			case AUTO_COVER:            PrintString(60, 2, "G AUTO_COVER  ");     break;
			case AUTO_STRAFFE:          PrintString(60, 2, "G AUTO_STRAFFE  ");     break;
			case AUTO_BALLOON:          PrintString(60, 2, "G AUTO_BALLOON  ");     break;
			case AUTO_RECONN:           PrintString(60, 2, "G AUTO_RECONN  ");     break;
			case AUTO_ARTSPOT:          PrintString(60, 2, "G AUTO_ARTSPOT  ");     break;
			case AUTO_HITWATER:		    PrintString(60, 2, "G AUTO_HITWATER  ");     break;
															  
			case AUTO_TRACKINGBOGIE:	PrintString(60, 2, "G AUTO_TRACKINGBOGIE  ");     break;
			case AUTO_TRACKINGBANDIT:   PrintString(60, 2, "G AUTO_TRACKINGBANDIT  ");     break;
			case AUTO_PRECOMBAT:		PrintString(60, 2, "G AUTO_PRECOMBAT  ");     break;
			case AUTO_LANDING:          PrintString(60, 2, "G AUTO_LANDING  ");     break;
			case AUTO_FAC:              PrintString(60, 2, "G AUTO_FAC  ");     break;
			case AUTO_CAS:              PrintString(60, 2, "G AUTO_CAS  ");     break;
			case AUTO_ACCELERATE:       PrintString(60, 2, "G AUTO_ACCELERATE  ");     break;
			case AUTO_MISSIONDICETHROW: PrintString(60, 2, "G AUTO_MISSIONDICETHROW  ");     break;
			case AUTO_COMMSACCEL:	    PrintString(60, 2, "G AUTO_COMMSACCEL  ");     break;
			case GROUND_TOGLOBREF:      PrintString(60, 2, "G GROUND_TOGLOBREF  ");     break;
			case AUTO_COMBAT:			PrintString(60, 2, "G AUTO_COMBAT  ");     break;
		}
		switch(Persons2::PlayerSeenAC->movecode)
		{
			case AUTO_FOLLOWWP:         PrintString(60, 3, "S AUTO_FOLLOWWP  ");     break;
			case AUTO_NOPPILOT:         PrintString(60, 3, "S AUTO_NOPPILOT  ");     break;
			case AUTO_WAIT4TIME:        PrintString(60, 3, "S AUTO_WAIT4TIME  ");     break;
			case AUTO_TAXI:             PrintString(60, 3, "S AUTO_TAXI  ");     break;
			case AUTO_TAKEOFF:          PrintString(60, 3, "S AUTO_TAKEOFF  ");     break;
			case GROUND_TAXI:		    PrintString(60, 3, "S GROUND_TAXI  ");     break;
			case AUTO_TELLLEADER:		PrintString(60, 3, "S AUTO_TELLLEADER  ");     break;
															  
			case AUTO_SPIRAL2GROUND:	PrintString(60, 3, "S AUTO_SPIRAL2GROUND  ");     break;
			case AUTO_RESURRECT:		PrintString(60, 3, "S AUTO_RESURRECT  ");     break;
			case AUTO_DEATHSEQUENCE:	PrintString(60, 3, "S AUTO_DEATHSEQUENCE  ");     break;
			case AUTO_TRAININGPREMERGE: PrintString(60, 3, "S AUTO_TRAININGPREMERGE  ");     break;
			case AUTO_TRAININGACM:	    PrintString(60, 3, "S AUTO_TRAININGACM  ");     break;
			case AUTO_CRASHSKID:		PrintString(60, 3, "S AUTO_CRASHSKID  ");     break;
			case AUTO_CRASHROLL:		PrintString(60, 3, "S AUTO_CRASHROLL  ");     break;
															  
			case AUTO_BOMB:             PrintString(60, 3, "S AUTO_BOMB  ");     break;
			case AUTO_COVER:            PrintString(60, 3, "S AUTO_COVER  ");     break;
			case AUTO_STRAFFE:          PrintString(60, 3, "S AUTO_STRAFFE  ");     break;
			case AUTO_BALLOON:          PrintString(60, 3, "S AUTO_BALLOON  ");     break;
			case AUTO_RECONN:           PrintString(60, 3, "S AUTO_RECONN  ");     break;
			case AUTO_ARTSPOT:          PrintString(60, 3, "S AUTO_ARTSPOT  ");     break;
			case AUTO_HITWATER:		    PrintString(60, 3, "S AUTO_HITWATER  ");     break;
															  
			case AUTO_TRACKINGBOGIE:	PrintString(60, 3, "S AUTO_TRACKINGBOGIE  ");     break;
			case AUTO_TRACKINGBANDIT:   PrintString(60, 3, "S AUTO_TRACKINGBANDIT  ");     break;
			case AUTO_PRECOMBAT:		PrintString(60, 3, "S AUTO_PRECOMBAT  ");     break;
			case AUTO_LANDING:          PrintString(60, 3, "S AUTO_LANDING  ");     break;
			case AUTO_FAC:              PrintString(60, 3, "S AUTO_FAC  ");     break;
			case AUTO_CAS:              PrintString(60, 3, "S AUTO_CAS  ");     break;
			case AUTO_ACCELERATE:       PrintString(60, 3, "S AUTO_ACCELERATE  ");     break;
			case AUTO_MISSIONDICETHROW: PrintString(60, 3, "S AUTO_MISSIONDICETHROW  ");     break;
			case AUTO_COMMSACCEL:	    PrintString(60, 3, "S AUTO_COMMSACCEL  ");     break;
			case GROUND_TOGLOBREF:      PrintString(60, 3, "S GROUND_TOGLOBREF  ");     break;
			case AUTO_COMBAT:			PrintString(60, 3, "S AUTO_COMBAT  ");     break;
		}
	}
*/

/*
	if (entry->Status.size == AIRSTRUCSIZE)
	{
		AirStrucPtr currac = (AirStrucPtr)entry;

		SWord acnum = 4 * (currac->formpos & 0x0f) + (currac->formpos & 0xf0) / 16;
		SWord ufnum = -1;
		AirStrucPtr uf = AirStrucPtr(currac->ai.unfriendly);
		if(uf)
			ufnum = 4 * (uf->formpos & 0x0f) + (uf->formpos & 0xf0) / 16;

		if(currac->nationality == NAT_RAF)
		{
			PrintVar(40, acnum, "M %.0f ", FP(currac->movecode));
			PrintVar(45, acnum, "Unf %.0f ", FP(ufnum));
		}
		else
		{
			PrintVar(60, acnum, "M %.0f ", FP(currac->movecode));
			PrintVar(65, acnum, "Unf %.0f ", FP(ufnum));
		}
	}
*/
/*
		if((!currworld->vp) || (!currworld->vp->Accel()))
			if(!(MOD.FrameCount & EVERY256cs) && (currac->fly.callnum <= 25))
			{
				if(currac->PlayerInGroup())
				{
					if(!currac->Status.deadtime) 
						PrintVar(0, currac->fly.callnum, "%.0f ", FP(currac->ai.flyingskill));
					else
						PrintString(0, currac->fly.callnum, "**DEAD**");
				}
				else if(currac->vel)
				{
					if(currac->classtype->visible == SPIT)
						if(!currac->Status.deadtime) 
							PrintVar(10, currac->fly.callnum, "SPIT %.0f ", FP(currac->ai.flyingskill));
						else
							PrintString(10, currac->fly.callnum, "**DEAD**");

					if(currac->classtype->visible == F84)
						if(!currac->Status.deadtime) 
							PrintVar(20, currac->fly.callnum, "F84 %.0f ", FP(currac->ai.flyingskill));
						else
							PrintString(20, currac->fly.callnum, "**DEAD**");

					if(currac->classtype->visible == F80)
						if(!currac->Status.deadtime) 
							PrintVar(30, currac->fly.callnum, "F80 %.0f ", FP(currac->ai.flyingskill));
						else
							PrintString(30, currac->fly.callnum, "**DEAD**");

					if(currac->classtype->visible == F51)
						if(!currac->Status.deadtime) 
							PrintVar(40, currac->fly.callnum, "F51 %.0f ", FP(currac->ai.flyingskill));
						else
							PrintString(40, currac->fly.callnum, "**DEAD**");

					if(currac->classtype->visible == B26)
						if(!currac->Status.deadtime) 
							PrintVar(50, currac->fly.callnum, "B26 %.0f ", FP(currac->ai.flyingskill));
						else
							PrintString(50, currac->fly.callnum, "**DEAD**");

					if(currac->classtype->visible == B29)
						if(!currac->Status.deadtime) 
							PrintVar(60, currac->fly.callnum, "B29 %.0f ", FP(currac->ai.flyingskill));
						else
							PrintString(60, currac->fly.callnum, "**DEAD**");

					if(currac->classtype->visible == MIG15)
						if(!currac->Status.deadtime) 
							PrintVar(70, currac->fly.callnum, "M15 %.0f ", FP(currac->ai.flyingskill));
						else
							PrintString(70, currac->fly.callnum, "**DEAD**");

					if(currac->classtype->visible == CMIG15)
						if(!currac->Status.deadtime) 
							PrintVar(70, currac->fly.callnum, "M15 %.0f ", FP(currac->ai.flyingskill));
						else
							PrintString(70, currac->fly.callnum, "**DEAD**");

					if(currac->classtype->visible == B26)
						PrintVar(57, currac->fly.callnum, "%.0f ", FP(currac->vel * 0.1));
	
				}
			}

		}
*/
/*		if( ((!currworld->vp) || (!currworld->vp->Accel())) && (currac->fly.callnum <= 8))
			if(!(MOD.FrameCount & EVERY8cs) || (currac->Status.deadtime))
				if((currac->PlayerInGroup()) || (	(currac->ai.unfriendly)
												 && (currac->ai.unfriendly->Status.size == AIRSTRUCSIZE)
												 && (AirStrucPtr(currac->ai.unfriendly)->PlayerInGroup())) )
//DEADCODE RDH 23/06/99 		if  (		(		(currac->fly.callname == 3)		//hot shot f86 = 3
//DEADCODE RDH 23/06/99 						||	(currac->fly.callname == 5)		//hot shot mig		
//DEADCODE RDH 23/06/99 					)
//DEADCODE RDH 23/06/99 					&&	(currac->fly.callnum <= 8)
//DEADCODE RDH 23/06/99 			)
		{

			if (currac->ai.unfriendly)
				currac->InterceptandRange (&currac->ai.unfriendly->World);						  //RDH 13/06/99
			else
				Range = 0;
			int grouppos = currac->fly.callnum;
			int line = grouppos + 1;
			if((MOD.Type == AT_MIG15) || (MOD.Type == AT_MIG15BIS) || (MOD.Type == AT_YAK9))
				line += 9;

			if((MOD.Type == AT_MIG15) || (MOD.Type == AT_MIG15BIS) || (MOD.Type == AT_YAK9))
				PrintVar(0, line, "RED %.0f      ", FP(grouppos));
			else
				PrintVar(0, line, "BLU %.0f      ", FP(grouppos));

			if (currac->Status.deadtime )
			{
				PrintString(32, line, "DEAD");

			}else
			{

				if(currac->ai.unfriendly) PrintVar(77, line, "v%.0f", FP(AirStrucPtr(currac->ai.unfriendly)->fly.callnum));
				if(currac->ai.attacker) 
					PrintVar(73, line, "a%.0f", FP(AirStrucPtr(currac->ai.attacker)->fly.callnum));
				else
					PrintVar(73, line, "a%.0f", FP(0));

				PrintVar(10, line, "Vel %.1f      ", FP(currac->vel / 10.0));
				PrintVar(20, line, "Range %.0f      ", FP(currac->Range / 100.0));
				
				if(currac->ai.simpleacm) PrintString(32, line, "simple    ");
				else			 PrintString(32, line, "COMPLEX   ");

				switch (currac->movecode)
				{
					case AUTO_TRACKINGBOGIE:	{ PrintString(40, line, "Track Bogie						");    break; }
					case AUTO_PRECOMBAT:	{ PrintString(40, line, "Precombat						");    break; }
					case AUTO_COMBAT:
					{
						switch (currac->ai.manoeuvre)
						{
							case MANOEUVRE_SELECT:						{ PrintString(40, line, "SELECT						");    break; }
							case MANOEUVRE_LOOKROUND:					{ PrintString(40, line, "LOOKROUND					");    break; }
							case MANOEUVRE_WELDEDWINGMAN:				{ PrintString(40, line, "WELDEDWINGMAN				");    break; }
							case MANOEUVRE_BAILOUT:						{ PrintString(40, line, "BAILOUT					");    break; }
							case MANOEUVRE_TOPCOVER:					{ PrintString(40, line, "TOPCOVER					");    break; }
							case MANOEUVRE_LINEABREAST:					{ PrintString(40, line, "LINEABREAST				");    break; }
							case MANOEUVRE_SCATTER:						{ PrintString(40, line, "SCATTER					");    break; }
							case MANOEUVRE_PINCER:						{ PrintString(40, line, "PINCER						");    break; }
							case MANOEUVRE_MULTIWAVE:					{ PrintString(40, line, "MULTIWAVE					");    break; }
							case MANOEUVRE_DIVEANDZOOM:					{ PrintString(40, line, "DIVEANDZOOM				");    break; }
							case MANOEUVRE_LEADPURSUIT:					{ PrintString(40, line, "LEADPURSUIT				");    break; }
							case MANOEUVRE_LAGPURSUIT:					{ PrintString(40, line, "LAGPURSUIT					");    break; }
							case MANOEUVRE_CIRCUMVENT:					{ PrintString(40, line, "CIRCUMVENT					");    break; }
							case MANOEUVRE_ROUNDABOUT:					{ PrintString(40, line, "ROUNDABOUT					");    break; }
							case MANOEUVRE_SPLITMANOEUVRE:				{ PrintString(40, line, "SPLITMANOEUVRE				");    break; }
							case MANOEUVRE_HEADON:						{ PrintString(40, line, "HEADON						");    break; }
							case MANOEUVRE_LINEASTERN:					{ PrintString(40, line, "LINEASTERN					");    break; }
							case MANOEUVRE_BARRELROLLATTACK:			{ PrintString(40, line, "BARRELROLLATTACK			");    break; }
							case MANOEUVRE_SCISSORS:					{ PrintString(40, line, "SCISSORS					");    break; }
							case MANOEUVRE_MILDSCISSORS:				{ PrintString(40, line, "MILDSCISSORS				");    break; }
							case MANOEUVRE_TURNINGFIGHT:				{ PrintString(40, line, "TURNINGFIGHT				");    break; }
							case MANOEUVRE_SPLITS:						{ PrintString(40, line, "SPLITS						");    break; }
							case MANOEUVRE_ZOOMANDDROP:					{ PrintString(40, line, "ZOOMANDDROP				");    break; }
							case MANOEUVRE_STRAIGHTANDLEVEL:			{ PrintString(40, line, "STRAIGHTANDLEVEL			");    break; }
							case MANOEUVRE_SPINOUT:						{ PrintString(40, line, "SPINOUT					");    break; }
							case MANOEUVRE_DIVEFORHOME:					{ PrintString(40, line, "DIVEFORHOME				");    break; }
							case MANOEUVRE_GOHOME:						{ PrintString(40, line, "GOHOME						");    break; }
							case MANOEUVRE_MAKEFORFRIENDLY:				{ PrintString(40, line, "MAKEFORFRIENDLY			");    break; }
							case MANOEUVRE_MOVEAWAY:					{ PrintString(40, line, "MOVEAWAY					");    break; }
							case MANOEUVRE_ACCIDENTALSPINOUT:			{ PrintString(40, line, "ACCIDENTALSPINOUT			");    break; }
							case MANOEUVRE_VERTICALLOOP:				{ PrintString(40, line, "VERTICALLOOP				");    break; }
							case MANOEUVRE_IMMELMANNTURN:				{ PrintString(40, line, "IMMELMANNTURN				");    break; }
							case MANOEUVRE_HEADONOFFSET:				{ PrintString(40, line, "HEADONOFFSET				");    break; }
							case MANOEUVRE_IMMELMANN:					{ PrintString(40, line, "IMMELMANN					");    break; }
							case MANOEUVRE_STAYWITHPREY:				{ PrintString(40, line, "STAYWITHPREY				");    break; }
							case MANOEUVRE_CLIMBFORHOME:				{ PrintString(40, line, "CLIMBFORHOME				");    break; }
							case MANOEUVRE_STRAIGHTDIVE:				{ PrintString(40, line, "STRAIGHTDIVE				");    break; }
							case MANOEUVRE_STANDONTAIL:					{ PrintString(40, line, "STANDONTAIL				");    break; }
							case MANOEUVRE_SHOOTTOFRIGHTEN:				{ PrintString(40, line, "SHOOTTOFRIGHTEN			");    break; }
							case MANOEUVRE_SHOOTTOOEARLY:				{ PrintString(40, line, "SHOOTTOOEARLY				");    break; }
							case MANOEUVRE_GAINHEIGHT:					{ PrintString(40, line, "GAINHEIGHT					");    break; }
							case MANOEUVRE_LAGROLL:						{ PrintString(40, line, "LAGROLL					");    break; }
							case MANOEUVRE_EXTENSION:					{ PrintString(40, line, "EXTENSION					");    break; }
							case MANOEUVRE_DIVINGSPIN:					{ PrintString(40, line, "DIVINGSPIN					");    break; }
							case MANOEUVRE_REVERSETURN:					{ PrintString(40, line, "REVERSETURN				");    break; }
							case MANOEUVRE_SELFASBAIT:					{ PrintString(40, line, "SELFASBAIT					");    break; }
							case MANOEUVRE_JINK:						{ PrintString(40, line, "JINK						");    break; }
							case MANOEUVRE_BREAKTURN:					{ PrintString(40, line, "BREAKTURN					");    break; }
							case MANOEUVRE_LAZYTURN:					{ PrintString(40, line, "LAZYTURN					");    break; }
							case MANOEUVRE_BREAK180:					{ PrintString(40, line, "BREAK180					");    break; }
							case MANOEUVRE_BREAKLOW:					{ PrintString(40, line, "BREAKLOW					");    break; }
							case MANOEUVRE_BREAKHIGH:					{ PrintString(40, line, "BREAKHIGH					");    break; }
							case MANOEUVRE_BREAK90:						{ PrintString(40, line, "BREAK90					");    break; }
							case MANOEUVRE_HIGBARRELROLL:				{ PrintString(40, line, "HIGBARRELROLL				");    break; }
							case MANOEUVRE_PANICTURN:					{ PrintString(40, line, "PANICTURN					");    break; }
							case MANOEUVRE_UNBALANCEDFLIGHT:			{ PrintString(40, line, "UNBALANCEDFLIGHT			");    break; }
							case MANOEUVRE_LOWALT:						{ PrintString(40, line, "LOWALT						");    break; }
							case MANOEUVRE_SNAPSHOT:					{ PrintString(40, line, "SNAPSHOT					");    break; }
							case MANOEUVRE_STAYONTAIL:					{ PrintString(40, line, "STAYONTAIL					");    break; }
							case MANOEUVRE_TURNTOHDGANDPITCH:			{ PrintString(40, line, "TURNTOHDGANDPITCH			");    break; }
							case MANOEUVRE_HOTSIDELAGPURSUITFIGHT:		{ PrintString(40, line, "HOTSIDELAGPURSUITFIGHT		");    break; }
							case MANOEUVRE_SANDWICHMANOEUVRES:			{ PrintString(40, line, "SANDWICHMANOEUVRES			");    break; }
							case MANOEUVRE_SUSTAINEDTURN:				{ PrintString(40, line, "SUSTAINEDTURN				");    break; }
							case MANOEUVRE_HIGHYOYO:					{ PrintString(40, line, "HIGHYOYO					");    break; }
							case MANOEUVRE_ZOOM:						{ PrintString(40, line, "ZOOM						");    break; }
							case MANOEUVRE_LOWYOYO:						{ PrintString(40, line, "LOWYOYO					");    break; }
							case MANOEUVRE_INTERCEPTHIGH:				{ PrintString(40, line, "INTERCEPTHIGH				");    break; }
							case MANOEUVRE_CLIMBATSUSTAINEDTURNSPEED:	{ PrintString(40, line, "CLIMBATSUSTAINEDTURNSPEED	");    break; }
							case MANOEUVRE_GAINSPEED:					{ PrintString(40, line, "GAINSPEED					");    break; }
							case MANOEUVRE_SPINRECOVERY:				{ PrintString(40, line, "SPINRECOVERY				");    break; }
						}
					}
				}

				if (currac->ai.unfriendly)
				{
					COORDS3D trg = currac->ai.unfriendly->World;
					COORDS3D my  = currac->World;
					FP fAttack = (trg.X - my.X) * currac->velx + (trg.Y - my.Y) * currac->vely + (trg.Z - my.Z) * currac->velz;
					fAttack *= 100.0 / FP(currac->vel * Range);

					PrintVar(59, line, "*%.0f ", fAttack);  
				}

				PrintVar(64, line, "f%.0f ", FP(currac->ai.combatskill));
				PrintVar(68, line, "m%.0f ", FP(currac->ai.morale));  
			}
		}
	}
*/
#endif

/* TEST CODE CSB 01/06/99 */
/* TEST CODE CSB 01/06/99 */
/* TEST CODE CSB 01/06/99 */

#ifndef	NDEBUG
	//Someone has set the movecode for a dead ac!!!
//DeadCode CSB 13/07/99		if (	(entry->movecode != AUTO_NOPPILOT)				//RJS 27Jun99
//DeadCode CSB 13/07/99			&&	(entry->shape == PDEATH)			)
//DeadCode CSB 13/07/99			INT3;
#endif

	switch (entry->movecode)
	{
	case AUTO_TRACKINGBOGIE:
		((AirStrucPtr) *entry)->Move().TrackBogey();
		break;
	case AUTO_TRACKINGBANDIT:
		((AirStrucPtr) *entry)->Move().TrackBandit();
		break;
	case AUTO_PRECOMBAT:
		((AirStrucPtr) *entry)->Move().AutoPreCombat();
		break;
	case AUTO_FOLLOWWP:												  //RDH 13/06/99
	case AUTO_TELLLEADER:										//JIM 03Oct96
		((AirStrucPtr) *entry)->Move().AutoFollowWp();
		break;
	case AUTO_TRAININGTAKEOFF:
		entry->movecode = AUTO_TAKEOFF;
		((AirStrucPtr) *entry)->Move().AutoTakeOff();
		break;
	case AUTO_TRAININGLANDING:
		entry->movecode = AUTO_LANDING;
		((AirStrucPtr) *entry)->Move().AutoLanding();
		break;
	case AUTO_TRAININGFORMATION:
		entry->movecode = AUTO_FOLLOWWP;
		((AirStrucPtr) *entry)->Move().AutoFollowWp();
		break;
//DEADCODE JIM 16/11/99 	case AUTO_FAC:
//DEADCODE JIM 16/11/99 		((AirStrucPtr) *entry)->AutoFAC();
//DEADCODE JIM 16/11/99 		break;
//DEADCODE JIM 16/11/99 	case AUTO_CAS:
//DEADCODE JIM 16/11/99 		((AirStrucPtr) *entry)->AutoCAS();
//DEADCODE JIM 16/11/99 		break;
//rdh 5/1/99	case AUTO_TRAININGPREMERGE:									//RDH 09Sep96
//rdh 5/1/99		((AirStrucPtr) *entry)->AutoTrainingPreMerge();			//RDH 09Sep96
//rdh 5/1/99		break;
//rdh 5/1/99	case AUTO_TRAININGACM:										//RDH 09Sep96
//rdh 5/1/99		((AirStrucPtr) *entry)->AutoTrainingACM();				//RDH 09Sep96
//rdh 5/1/99		break;													//RDH 09Sep96
	case AUTO_FOLLOWTHELEADER:
		((AirStrucPtr)*entry)->Move().AutoFollowTheLeader();			  //CSB 03/02/00
		break;
	case AUTO_CRASHROLL:										//RDH 12Sep96
		((AirStrucPtr) *entry)->Move().AutoCrashRoll();						//RDH 12Sep96
		break;
	case AUTO_CRASHSKID:										//RDH 12Sep96
		((AirStrucPtr) *entry)->Move().AutoCrashSkid();				//RDH 12Sep96
		break;
	case AUTO_CRASHONEWHEEL:
		((AirStrucPtr) *entry)->Move().AutoCrashOneWheel();	
		break;
	case AUTO_CRASHNOSE:
		((AirStrucPtr) *entry)->Move().AutoCrashNose();	
		break;
	case AUTO_CRASHFLIP:
		((AirStrucPtr) *entry)->Move().AutoCrashFlip();	
		break;
	case AUTO_CRASHTUMBLE:
		((AirStrucPtr) *entry)->Move().AutoCrashTumble();	
		break;
	case AUTO_WAIT4TIME:												//CSB 6Jul00
		((AirStrucPtr) *entry)->Move().AutoWait4Time();					//CSB 6Jul00
		break;															//CSB 6Jul00
	case AUTO_TAKEOFF:
		((AirStrucPtr) *entry)->Move().AutoTakeOff();
		break;
	case AUTO_COMBAT:
		((AirStrucPtr) *entry)->AirCombat();
		break;
	case AUTO_NOPPILOT:
//DeadCode AMM 01Dec98 		if (entry=Persons2::PlayerSeenAC)

		
//DEADCODE RDH 28/04/99 		if (entry->uniqueID.count>RedAcBAND && entry->uniqueID.count<BlueAcBANDEND)
//DEADCODE RDH 28/04/99 			UByteP(0xB0000)[2*entry->uniqueID.count&0xfff]='N';
//DeadCode JIM 28Apr99 			UByteP(0xB0000)[2*entry->uniqueID.count&0xfff]='N';

		if (!_Replay.Playback)									//RJS 10Aug00
			entry->vel_ = entry->vel_x = entry->vel_y = entry->vel_z = 0;					//RJS 10Aug00

		if (entry==Persons2::PlayerSeenAC)						//AMM 01Dec98
		{
			_DPlay.ResurrectMe(Persons2::PlayerSeenAC,false);
		}
		break;
	case GROUND_TAXI:
		((FormationItemPtr) *entry)->AutoTaxi();
	break;
	case GROUND_CORNERUPTO:
		((FormationItemPtr) *entry)->AutoTaxiCornerUpTo();
	break;
	case GROUND_CORNERTURN:
		((FormationItemPtr) *entry)->AutoTaxiCornerTurn();
	break;

	case GROUND_TOGLOBREF:
		((FormationItemPtr) *entry)->WaitToTaxi();
		break;
//	case AUTO_TAXI:
//		((AirStrucPtr) *entry)->AutoTaxi();
//		break;
	case AUTO_SPIRAL2GROUND:
		((AirStrucPtr) *entry)->Move().AutoSpiral2Ground(world);		//PD 01May96
		break;
	case AUTO_RESURRECT:
		((AirStrucPtr) *entry)->Move().AutoResurrect((AirStrucPtr)entry);			//ARM 05Dec96
		break;
	case AUTO_DEATHSEQUENCE:
		((AirStrucPtr) *entry)->Move().AutoDeathSequence();			//RDH 10Sep96
		break;
	case AUTO_DEATHGLIDE:
		((AirStrucPtr) *entry)->Move().AutoDeathGlide();
		break;
	case AUTO_LANDING:											//JIM 02Aug96
		((AirStrucPtr) *entry)->Move().AutoLanding();				//JIM 02Aug96
		break;													//JIM 02Aug96
	case AUTO_STRAFFE:
		((AirStrucPtr) *entry)->Move().AutoStraffe();				//JIM 02Aug96
		break;													//JIM 02Aug96
	case AUTO_BOMB:
		((AirStrucPtr) *entry)->Move().AutoBomb();				//JIM 02Aug96
		break;													//JIM 02Aug96
	case AUTO_HITWATER:											//RJS 24Aug98
		((AirStrucPtr) *entry)->Move().AutoCrashSkid();				//RJS 24Aug98
		break;													//RJS 24Aug98
	case AUTO_ACCELERATE:
		((AirStrucPtr) *entry)->Move().AutoAccelerate();
		break;
	case AUTO_MISSIONDICETHROW:
		((AirStrucPtr) *entry)->Move().MoveMissionDiceThrow();
		break;
	case AUTO_COMMSACCEL:
		((AirStrucPtr) *entry)->Move().AutoCommsAccel();
		break;
	case GROUND_BLOKE:											//RJS 10Jan00
	case GROUND_BLOKEFREAK:											//RJS 10Jan00
		((FormationItemPtr) *entry)->AutoBloke();
		break;
	case GROUND_EMERGENCY:
		((FormationItemPtr) *entry)->AutoEmergencyVehicle();
		break;
	case GROUND_HALTTRUCK:
		((FormationItemPtr) *entry)->AutoSlowTaxi();
		break;
	}
//DEADCODE JIM 31/05/00 #ifndef	NDEBUG
//DEADCODE JIM 31/05/00 	if(!Count_SetFlightParams)
//DEADCODE JIM 31/05/00 		int breakpoint = 0;//INT3;
//DEADCODE JIM 31/05/00 	Count_SetFlightParams=0;
//DEADCODE JIM 31/05/00 #endif
	if(entry->Status.size == AIRSTRUCSIZE)
	{
		AirStrucPtr ac = AirStrucPtr(entry);
		ac->weap.ShootDelay = ac->weap.ShootDelay - Timer_Code.FRAMETIME;
		if(ac->weap.ShootDelay < 0)
			ac->weap.ShootDelay = 0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveList
//LastModified:	PD 26Apr96
//Author		Jim Taylor
//Date			Thu 15 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
extern void	CheckE3();
void TransientItem::MoveTransList(TransientItemPtr entry,WorldStuff& world)
{
	currworld=&world;
	while (entry)
	{
		TransientItemPtr	next= entry->nexttrans;
		if (entry->movecode != MOBILE_NOPPILOT)						//RJS 09Dec98
		{
			UWord	oldsector=	world.GetSector(*entry);			//PD 25Jun96
	
			MoveTransItem(entry,world);
	
			if (oldsector!=world.GetSector(*entry))					//PD 25Jun96
			{
				world.RemoveFromSector((TransientItemPtr)entry,oldsector);
				world.AddToWorld((TransientItemPtr)entry);
			}
		}

		entry=next;
	}

// Update smoke clouds...
	Land_Scape.ManageSmokeClouds();								//RJS 24May00
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveList
//Author		Jim Taylor
//Date			Thu 15 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransientItem::MoveTransItem(TransientItemPtr entry,WorldStuff& world)//PD 26Apr96
{
/*#ifdef	DBGMEMTEST
#ifndef	NDEBUG
	TransientItem*	tmpentry = TransientList;
	while (tmpentry)
	{
		DbgMemTest2(tmpentry);
		tmpentry->Anim.MemTest();
		tmpentry = tmpentry->nexttrans;
	}
#endif
#endif*/
	switch (entry->movecode)// & AutoMoveCodeMask)					//RJS 24Nov97
	{
  	case	MOBILE_BURNIT:			Trans_Obj.MobileExplosion(entry,world);	break;//PD 26Apr96
 	case	MOBILE_CRATER:			Trans_Obj.MobileCrater(entry,world);	break;//PD 26Apr96
	case	MOBILE_BULLET:			Trans_Obj.MobileBullet(entry,world); 	break;//PD 26Apr96
	case    MOBILE_DEADACPART:		Trans_Obj.MobileDeadACPart(entry,world);break;//PD 26Apr96
	case 	MOBILE_SMOKETRAIL:		Trans_Obj.MobileSmokeTrail(entry,world);break;//PD 30Apr96
	case 	MOBILE_GANDF:			Trans_Obj.MobileGAndF(entry,world);		break;//PD 30Apr96
	case 	MOBILE_GROUNDEXP:		Trans_Obj.MobileGroundExp(entry,world);	break;//PD 01May96
	case 	MOBILE_DEBRIS:			Trans_Obj.MobileGroundDebris(entry,world);	break;//RJS 21Jun96
	case 	MOBILE_FIRE:			Trans_Obj.MobileFire(entry,world);	break;//RJS 01Jul96
	case 	MOBILE_TROOP:			Trans_Obj.MobileTroop(entry,world);	break;//RJS 01Jul96
	case 	MOBILE_PARACHUTE:		Trans_Obj.MobileParachute(entry,world);	break;//RJS 02Jul96
	case 	MOBILE_BARAGE:			Trans_Obj.MobileBarage(entry,world);	break;//RJS 02Jul96
	case 	MOBILE_DELEXP:			Trans_Obj.MobileDelayedExplosion(entry,world);	break;//RJS 02Jul96
	case 	MOBILE_FLAK:			Trans_Obj.MobileFlak(entry,world);	break;//RJS 02Jul96
	case 	MOBILE_RICOCHET:		Trans_Obj.MobileSparkTrail(entry,world);	break;//RJS 11Dec98
	case 	MOBILE_ATEAM:			Trans_Obj.MobileATeam(entry,world);	break;//RJS 10Jul96
	case 	MOBILE_BOMBDROP:		Trans_Obj.MobileBombDrop(entry,world);	break;//RJS 24Jul96
	case 	MOBILE_BIGEXP:			Trans_Obj.MobileBigExplosion(entry,world);	break;//RJS 12Aug96
	case 	MOBILE_MOVSMK:			Trans_Obj.MobileMovingSmoke(entry,world);	break;//RJS 02Sep96
	case 	MOBILE_STATIONARY:		Trans_Obj.MobileRicochetSmoke(entry,world);	break;//RJS 05Sep96
	case 	MOBILE_PUFFTRAVEL:		Trans_Obj.MobilePuffTravel(entry,world);	break;//RJS 13Oct96
	case 	MOBILE_BIRD:			Trans_Obj.MobileBird(entry,world);	break;//RJS 01Oct97
	case 	MOBILE_AMMODEATH:		Trans_Obj.MobileAmmoBoxes(entry,world);	break;//RJS 17Oct96
	case 	MOBILE_MUSHROOM:		Trans_Obj.MobileDummyBomb(entry,world);	break;//RJS 01Apr99
	case 	MOBILE_ROCKET:			Trans_Obj.MobileRocket(entry,world);	break;//RJS 04Jun97
	case 	MOBILE_CLONEGUN:		Trans_Obj.MobileCloneGun(entry,world);	break;//RJS 01Oct97
	case 	MOBILE_TIMEREXPLOSION:	Trans_Obj.MobileTimerExplosion(entry,world);	break;//RJS 22Jan98
	case 	MOBILE_NAPALM:			Trans_Obj.MobileNapalm(entry,world);	break;//RJS 22Jan98
	case 	MOBILE_DODAMAGE:		Trans_Obj.MobileDoDamage(entry,world);	break;//RJS 18Feb98
	case 	MOBILE_THUG:			Trans_Obj.MobileThuggery(entry,world);	break;//RJS 02Mar98
	case 	MOBILE_SMALLTHUG:		Trans_Obj.MobileSmallThug(entry,world);	break;//RJS 03Dec98
	case 	MOBILE_FUELDROP:		Trans_Obj.MobileFuelDrop(entry,world);	break;//RJS 28May98
	case 	MOBILE_DEADBRIDGE:		Trans_Obj.MobileDeadBridge(entry,world);	break;//RJS 30Oct98
	case 	MOBILE_COLLAPSE:		Trans_Obj.MobileCollapse(entry,world);	break;//RJS 18Nov98
//DeadCode RJS 15Dec99 	case 	MOBILE_CARPETBOMB:		Trans_Obj.MobileCarpetStrike(entry,world);	break;//RJS 31May99
	case 	MOBILE_SCALEFIST:		Trans_Obj.MobileScaleFist(entry,world);	break;//RJS 10Feb99
	case 	MOBILE_CANOPY:			Trans_Obj.MobileCanopy(entry,world);	break;//RJS 23Mar99
	case 	MOBILE_SINK:			Trans_Obj.MobileSink(entry,world);	break;//RJS 13May99
	case 	MOBILE_FLARE:			Trans_Obj.MobileFlare(entry,world);	break;//RJS 17May99
	case 	MOBILE_SUPERBOMB:		Trans_Obj.MobileSuperBomb(entry,world);	break;//RJS 23Nov99
	case 	MOBILE_DEADAC:			Trans_Obj.MobileDeadAC(entry,world);	break;//RJS 25Nov99
	case 	MOBILE_FUELFIRE:		Trans_Obj.MobileFuelFire(entry,world);	break;//RJS 13Dec99
	case 	MOBILE_FIRESMOKE:		Trans_Obj.MobileSmokeBlob(entry,world);	break;//RJS 14Dec99
	case 	MOBILE_DEADBALLOON:		Trans_Obj.MobileDeadBalloon(entry,world);break;//RJS 15Dec99
	case 	MOBILE_PAC:				Trans_Obj.MobilePAC(entry,world);break;//RJS 03Feb00
	case	MOBILE_ENGINESTART:		Trans_Obj.MobileEngineStart(entry,world);break;//RJS 22Feb00
	case	MOBILE_BOMB1STFRAME:	Trans_Obj.MobileBomb1stFrame(entry,world);break;	//RJS 3Oct00

	}
/*#ifdef	DBGMEMTEST
#ifndef	NDEBUG
	tmpentry = TransientList;
	while (tmpentry)
	{
		DbgMemTest2(tmpentry);
		tmpentry->Anim.MemTest();
		tmpentry = tmpentry->nexttrans;
	}
#endif
#endif*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToList
//Author		Jim Taylor
//Date			Thu 15 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::AddToList()
{
	if (uniqueID.count<SagBANDEND)
	{
		nextmobile=SAGList;
		SAGList=*this;
		Art_Int.Add(this);
	}
	else
	{
		nextmobile=ACList;
		ACList=*this;
		if(		(!formpos && movecode != AUTO_SPAREAC)							//JON 22/02/00
			&&	((this != Persons2::PlayerSeenAC) || (!Persons2::PlayerSeenAC->fly.expandedsag))	)	//CSB 27Jul00
			Art_Int.Add(this);
	}
}

void mobileitem::AddToList()
{
	nextmobile=MobileList;
	MobileList=*this;
}

void TransientItem::AddToList()
{
	nexttrans=TransientList;
	TransientList=this;

// transients have ID equal to frame when launched. When a collision occurs the player 
// who processes the collision (owner of transient) send a message indicating that all
// transients with that frame number launched by him should be removed from the world

	this->uniqueID.count=(UniqueID)_DPlay.FrameCount;

// if this was launched by a transient then it inherits its parents flags

	if (Launcher->Status.size==TRANSIENTSIZE)
	{
		this->CollTestEnabled=((TransientItemPtr)Launcher)->CollTestEnabled;
		this->CollSuccessTrans=((TransientItemPtr)Launcher)->CollSuccessTrans;
	}
	else
	if ((Launcher==Persons2::PlayerSeenAC && !_Replay.Playback)
	|| (!_DPlay.Implemented && !_Replay.Record && !_Replay.Playback))
	{
// comms/replay off or player launched 
// if replay is turned on then these bullets will cause collisions to be recorded
// even though bullets are not seen on replay

		this->CollTestEnabled=TRUE;
		this->CollSuccessTrans=TRUE;
	}
	else if (!Launcher->uniqueID.commsmove && Launcher!=Persons2::PlayerSeenAC)
	{
// AI launched - want to test all AI bullets against all other AI planes and against player
// unless in playback, which is dealt with in PossTransmitColl

		this->CollTestEnabled=TRUE;

// if this hits player then collision will be sent if in record or comms. Other collisions do
// not need to be sent as they are AI against AI, or AI against comms player in which case
// that player will send his own collision info packets. 

// if this hits a player then check CommsOwner ID. If it is me then trasmit, otherwise ignore.

		this->CollSuccessTrans=FALSE;
	}
	else
	{
// comms received - dont test for anything just show them. All player collisions are dealt with
// via separate packet info

		this->CollTestEnabled=FALSE;
		this->CollSuccessTrans=FALSE;
	}

//DeadCode JIM 07Oct96  	TransientItemPtr temp = new TransientItem;
//DeadCode JIM 07Oct96   	if (TransientList==NULL)
//DeadCode JIM 07Oct96   	{
//DeadCode JIM 07Oct96   		TransientList=*this;
//DeadCode JIM 07Oct96   	}
//DeadCode JIM 07Oct96   	else
//DeadCode JIM 07Oct96   	{
//DeadCode JIM 07Oct96  		temp=TransientList;
//DeadCode JIM 07Oct96  		TransientList=*this;
//DeadCode JIM 07Oct96  
//DeadCode JIM 07Oct96  		TransientList->nexttrans=temp;
//DeadCode JIM 07Oct96   	}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetWpName
//Author		Jim Taylor
//Date			Thu 5 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//TextSnip0	WayPoint::GetWpName()
//{
//	TextSnip0	retval=TEXT_NULL;
//	if (action!=wpacnoactionno)// && action<16)
//		retval=(_Text.ConvSnip0((TextList)LIST_WPACTIONS0,action));
//	elseif (target)
//		retval=(_Text.ConvSnip0(target->uniqueID.count));
//	if (retval==TEXT_NULL)
//		retval=(TEXT_WPACNOACTIONNO);
//	return(retval);
//}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExecuteWayPointAction
//Author		R. Hyde 
//Date			Mon 19 Feb 1996
//
//Description	Now pseudo recursive. Compiler should optimise to itteration.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	mobileitem::ExecuteWayPointAction ()
{
//TEMP	Persons_2.PossibleEvent(currworld,waypoint,this);
	if (	Status.size==AIRSTRUCSIZE 
		&&	AirStrucPtr(*this)->fly.numinsag>1)
	{
		AirStrucPtr(*this)->SAG().SAGWPAction();
		return;
	}

	AutoMoveCodeTypeSelect	oldmove=movecode;
	WayPointPtr	oldwp=waypoint;
//DeadCode JIM 18Oct96 	if (oldwp)
	//NULL WP MEANS START TO LAND...
	if (waypoint)
		DoWayPointAction(oldmove,oldwp,waypoint->action);
	else
		DoWayPointAction(oldmove,oldwp,wpforcelanding);
	if (Status.size==AIRSTRUCSIZE)
	{
		AirStrucPtr a=*this;
		if((oldwp->wpname == WPNAME_IP) && (a->follower))
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_INITIALPOINT, MSG_FACCONTACT_X, a, NULL, a->Follower()));
		if (	a->ai.eventlog->stage==EventLog::TAKEOFF
			&&	waypoint && waypoint->target
			)
		{
			if	(	waypoint->action==wpbombno
				||	waypoint->action==wpengagetargetno
				||	waypoint->action==wpdivebombstraffeno
//				||	waypoint->action==wpstraffeno
				||	waypoint->action==wpballoonbustno
				)
			{
//TEMP				Persons_2.AddMessage(UserMsg::SIGHTED,TEXT_OBJECTIVESIGHTED,waypoint->target);
				_Miles.SequenceAudible(FIL_MUSIC_OBJECTIVE_SIGHTED);
			}
		}
	}
}

void	mobileitem::DoWayPointAction (AutoMoveCodeTypeSelect	oldmove,WayPointPtr	oldwp,BFieldWaypointActions action)
{
	if(Status.size == AIRSTRUCSIZE)										//CSB 22Aug00
	{
		AirStrucPtr a = AirStrucPtr(this);
		a->information = IF_OUT_POS;					//CSB 22Aug00
		a->manoeuvretime = 0;

		if(Manual_Pilot.controlmode == ManualPilot::AUTOACCEL_WAYPT)
			if((a == Persons2::PlayerSeenAC) || (a == Persons2::PlayerGhostAC))
				OverLay.CancelAccel();

		if((Manual_Pilot.controlmode == ManualPilot::AUTOACCEL_MISS) && (oldwp->wpname == WPNAME_IP))
			if((a == Persons2::PlayerSeenAC) || (a == Persons2::PlayerGhostAC))
				OverLay.CancelAccel();
	}

	if (movecode==oldmove && waypoint==oldwp)
	{
		if (waypoint)
		{
			if (!waypoint->Status.deadtime && this==Manual_Pilot.ControlledAC2)
			{
//				UserMsg::Reason	r=UserMsg::PASSEDWP;
//DEADCODE JIM 25/03/99 				TextSnip0	t=TEXT_NULL;
//				t=waypoint->GetWpName();
//TEMP				Persons_2.AddMessage(r,t,*FindDesPos ());
//DeadCode RDH 15Oct96 				Persons_2.ClrMessage(UserMsg::COURSE);
			}
		}


		switch (action)
		{
		case	wpatakeoffno:
		case	wpacircleno:
		case	wptruckbridge:
		case	wptruckescort:
		case	wpengagetargetno:	//Used for interceptions!			//CSB 18Jul00
				NextWayPoint ();
		break;
//
//	PROPER WAYPOINT ACTIONS START HERE:
//	the ones above fall through to noaction
//
		case	wpacnoactionno:
			{
				NextWayPoint ();
				if(Status.size != AIRSTRUCSIZE)
					break;

				if(AirStrucPtr(this)->formpos)
					break;

				AirStrucPtr AC = *this;
				AirStrucPtr callee = AC->PlayerInGroup();
				if((callee) && (!AC->AcIsPlayer()))
				{
					AirStrucPtr AC = *this;
					AirStrucPtr callee = AC->PlayerInGroup();
					if((callee) && (callee != AC))
					{
						AC->InterceptandRange(AC->waypoint);
						SWord dhdg = SWord(AC->hdg) - SWord(AC->HdgIntercept);
						bool sentmessage = false;
						if(((AC->formation & FORMTYPE_WING) == FTW_SCWARM) || ((AC->formation & FORMTYPE_WING) == FTW_BSCRWARM))
						{
								if(dhdg > ANGLES_45Deg)
								{
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TURNRIGHT, MSG_NEW_HEADING, AC, NULL, callee));
									sentmessage = true;
								}
								else if(-dhdg > ANGLES_45Deg)
								{
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TURNLEFT, MSG_NEW_HEADING, AC, NULL, callee));
									sentmessage = true;
								}
								if(sentmessage)
									for(AirStrucPtr nf = AC; nf; nf = nf->fly.nextflight)
										for(AirStrucPtr f = nf; f; f = f->Follower())
										{
											if((f->formation & FORMTYPE_WING) == FTW_SCWARM)
												f->formation = (f->formation % FORMTYPE_WING) | FTW_BSCRWARM;
											else
												f->formation = (f->formation % FORMTYPE_WING) | FTW_SCWARM;
											f->information = IF_OUT_POS;
//DeadCode CSB 31Oct00 											f->formation = f->formation | FTI_SCWARM_SWAPPING_FLAG;
										}
						}
						if(!sentmessage)
							if((dhdg > ANGLES_20Deg) || (-dhdg > ANGLES_20Deg))
							{
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TURNTONEWWAYPOINT, MSG_NEW_HEADING, AC, waypoint, callee));
								if(waypoint->World.Y <= World.Y)
									_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_LINER, MSG_NEW_SPEED, AC, waypoint, callee));
							}
					}
				}
				break;
			}
		case	wpdmbtrknoactno:
				NextWayPoint ();
				movecode=GROUND_CORNERTURN;
				action=wpretrywp;
		break;
		case	wpcheckfordamage:								//RJS 11Jan0
				movecode=GROUND_CORNERTURN;
				action=wpretrywp;
				EmergencyService();
		break;
		case	wpretrywp:
		//Truck followers come here
		if (movecode==GROUND_TAXI)
			movecode=GROUND_CORNERUPTO;
		break;												//RDH 17Oct96

		case	wpballoonbustno:											//MS 18Jul96
		case	wpdivebombstraffeno:										//MS 18Jul96
//		case	wpstraffeno:												//MS 18Jul96
			StartStraffe();
		break;

		case	wpbombno:													//MS 18Jul96
//DeadCode JIM 18Jul00 		case	wpengagetargetno:	//USED FOR INTERCEPTIONS!
		case	wpattackconvoyno:
			StartBombing();
		break;

		case	wpreccyno:										//JIM 17Dec96
 		case	wpartspotno:									//JIM 17Dec96
				KillItNow();
		break;

		case	wpteleportnext:
			TeleportWayPoint();
		break;

		case	wpstoploopchkno :							//JIM 30Jul96
			action=EndLoopWayPoint();								//JIM 30Jul96
		break;												//JIM 30Jul96

		case	wpbreakloop :							//JIM 30Jul96 //JIM 19/03/99
		case	wpstartloopno:										  //JIM 19/03/99
			action=MidLoopWayPoint();								//JIM 30Jul96
		break;												//JIM 30Jul96
		
		case	wpforcebreakloop:
			ForceBreakLoopWayPoint();
		break;

		case	wpwaituntildeadno :							//JIM 30Jul96
			WaitDeadWayPoint();								//JIM 30Jul96
		break;												//JIM 02Aug96
		case	wpalandingno:								//JIM 02Aug96
			LandingWayPoint();								//JIM 02Aug96
		break;												//JIM 02Aug96
		case	wpdisperseno:
			FormationItemPtr(*this)->DisperseWayPoint();
		break;
		case	WP_fighterlimit:
			FormationItemPtr(*this)->NextWayPoint();					//CSB 25Jul00
			FormationItemPtr(*this)->FighterLimitWayPoint();
		break;


		case	wpdmbtrkstopno:
		case	wpstopno:									//RDH 17Oct96
			vel_x=vel_y=vel_z=0;
			movecode=AUTO_NOPPILOT;

		break;
		case wpforcelanding:
		{
			AirStrucPtr ac = AirStrucPtr(*this);
			if((nationality == NAT_RAF) && (ac->classtype->aerobaticfactor == AEROBATIC_HIGH))
			{
				if(		(waypoint->target->World.X != waypoint->World.X)
					||	(waypoint->target->World.Y != waypoint->World.Y)
					||	(waypoint->target->World.Z != waypoint->World.Z)	)
				{
					SLong totfuel  = 0;
					SLong fuelleft = 0;
					for(SWord i = 0; i < 4; i++)
					{
						totfuel  += ac->classtype->fueltankcap[i];
						fuelleft += ac->fly.fuel_content[i] / 1000;
					}
					if(fuelleft < totfuel / 4)
						waypoint->target->World = waypoint->World;
					else
					{
						const COORDS3D offsetE = { 1000000, 0, -1000000};
						const COORDS3D offsetW = {-1000000, 0, -1000000};
						if(		(waypoint->target->World.X == waypoint->World.X + offsetE.X)
							&&	(waypoint->target->World.Y == waypoint->World.Y + offsetE.Y)
							&&	(waypoint->target->World.Z == waypoint->World.Z + offsetE.Z)	)
						{
							waypoint->target->World.X = waypoint->World.X + offsetW.X;
							waypoint->target->World.Y = waypoint->World.Y + offsetW.Y;
							waypoint->target->World.Z = waypoint->World.Z + offsetW.Z;
						}
						else
						{
							waypoint->target->World.X = waypoint->World.X + offsetE.X;
							waypoint->target->World.Y = waypoint->World.Y + offsetE.Y;
							waypoint->target->World.Z = waypoint->World.Z + offsetE.Z;
						}
						break;
					}
				}
			}
			
//DeadCode CSB 5Oct00 			if((AC == Persons2::PlayerGhostAC) || (AC == Persons2::PlayerSeenAC))
//DeadCode CSB 5Oct00 				OverLay.CancelAccel();
			movecode = AUTO_LANDING;
			if (Anim!=NULL)
				SHAPE.NavigationLightsActive(this, TRUE);
			AirStrucPtr AC = *this;
			AC->ai.ManStep = 0;
			AC->SetManoeuvreTime(0);
			
			if(AC->formpos == 0)
			{
				AirStrucPtr ThePlayer = AC->PlayerInGroup();
				if(/*(ThePlayer) &&*/ (AC != ThePlayer))
				{
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_GIMMEAVECTOR, MSG_STATUSRESPONSE_DELAY_LP_RPT, AC, AC->ai.homebase, AC));

					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_STEER_RANGE, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, AC->ai.homebase, AC));

					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SURFACEWINDREQUEST, MSG_WIND_REQUEST, AC, AC->ai.homebase, AC));

					ScriptTables windrep = SCRIPT_NOWIND;
			 		if(Save_Data.flightdifficulty [FD_WINDEFFECTS])
						if(Save_Data.flightdifficulty [FD_WINDGUSTS])
							windrep = SCRIPT_CALLEE_SURFACEWIND_BEARINGNO_SPEED_GUSTS;
						else
							windrep = SCRIPT_CALLEE_SURFACEWIND_BEARINGNO_SPEED;
					
					_Radio.TriggerMsg(MESSAGE_STRUC(windrep, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, NULL, AC));
				}
			}
			
			if(AC->classtype->aerobaticfactor == AEROBATIC_LOW)
			{
				bool sentmessage = false;
				for(int i = SagBAND; i < SagBANDEND; i++)
				{
					AirStrucPtr as = Persons2::ConvertPtrUID(UniqueID(i));
					if((as) && (as->nationality == AC->nationality) && (as->classtype->aerobaticfactor == AEROBATIC_HIGH))
					{
						if((as->fly.numinsag > 0) && (as->fly.expandedsag))
							as = as->fly.expandedsag;
						if(as->fly.leadflight == AC)
						{
							as->fly.leadflight = NULL;
							if(!sentmessage)
							{
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_THANKSANDGO, MSG_MIGREPORTED, AC, NULL, as));
								sentmessage = true;
							}
						}
					}
				}
			}
				
			break;
		}

		case	wp_start_cas:
//DEADCODE JIM 16/11/99 			NextWayPoint();
//DEADCODE JIM 16/11/99 			if (	(AirStrucPtr(*this)->duty&DUTYMASK)==DC_CAS 
//DEADCODE JIM 16/11/99 				&& (AirStrucPtr(*this)->duty&ACTIONCODE)!=DA_CAP
//DEADCODE JIM 16/11/99 				)
//DEADCODE JIM 16/11/99 				AirStrucPtr(*this)->SetToCAS(true);
		break;

		case	wp_threat_combfriendly:
		case	wp_threat_engfriendly:
		case	wp_threat_firing:
		case	wp_threat_weapon:
		case	wp_threat_danger:
		case	wp_threat_engage:
		case	wp_threat_any:
			assert (Status.size==AIRSTRUCSIZE);
			AirStrucPtr(*this)->ai.threatlevel=tThreatLevel(action-wp_threat_combfriendly);
			NextWayPoint();
		break;


		}
	}

		if (Status.size>=FormationSize)							//JIM 04Aug96
		{	//find a child and recurse down it					//JIM 04Aug96
			FormationItemPtr	f=*this;						//JIM 04Aug96
			if(f->follower)									//JIM 04Aug96
				f->follower->DoWayPointAction(oldmove,oldwp,action);				//JIM 04Aug96
			elseif (Status.size==AirStrucSize)					//JIM 04Aug96
				if(f->leader && ((AirStrucPtr)*f->leader)->fly.nextflight)//JIM 04Aug96
					((AirStrucPtr)*f->leader)->fly.nextflight->DoWayPointAction(oldmove,oldwp,action);		//JIM 04Aug96
				elseif (((AirStrucPtr)*this)->fly.nextflight)
					((AirStrucPtr)*this)->fly.nextflight->DoWayPointAction(oldmove,oldwp,action);		//JIM 04Aug96
		}														//JIM 04Aug96
		//else finished											//JIM 04Aug96

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckManualCourse
//Author		Jim Taylor
//Date			Sun 21 Jul 1996
//
//Description	
//				Basically does equivalents to auto movecode for player
//
//				Checks if manual is on course and has reached waypoints
//				Checks for all break off
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::CheckManualCourse()
{
	if(Status.deadtime)
		return;

//#define PRINT_MANUAL
#ifdef PRINT_MANUAL

#pragma warnmsg("*****  DIRTY HACK ***** GHOST VELOCITY STOMPED *****")
#pragma warnmsg("*****  DIRTY HACK ***** GHOST VELOCITY STOMPED *****")
#pragma warnmsg("*****  DIRTY HACK ***** GHOST VELOCITY STOMPED *****")

	Persons2::PlayerGhostAC->vel_ = Persons2::PlayerSeenAC->vel_;

PrintVar(0, 0, "Movecode %.0f ", FP(movecode));
PrintVar(0, 1, "Waypoint %.0f ", FP(waypoint->wpname));
COORDS3D wp = waypoint->World;
if(waypoint->target)
{	wp.X += waypoint->target->World.X;	wp.Y += waypoint->target->World.Y;	wp.Z += waypoint->target->World.Z;	}
InterceptandRange(&wp);
PrintVar(0, 2, "Dist     %.0f ", FP(Range / 100));
PrintVar(0, 3, "Heading  %.0f ", FP(UWord(HdgIntercept) / 182));

#endif

	switch(movecode)
	{
		case AUTO_TAKEOFF:
		case AUTO_TRAININGTAKEOFF:
		{
			if(World.Y > ai.homebase->World.Y + FT_100)
				movecode = AUTO_FOLLOWWP;
			break;
		}

		case AUTO_FOLLOWWP:
		{
			if(FlyEscortTo())
			{
				AirStrucPtr leadac = Leader();
				if(!leadac)
					leadac = fly.leadflight;

				InterceptandRange(PositionWRTLeader());
				if(Range < METRES100)
					information = IF_NEAR_POS;
				else
				{
					information = IF_OUT_POS;
					leadac->slowdownleader = TRUE;
					if(fly.leadflight)
						fly.leadflight->slowdownleader = TRUE;
					int r = (int)FSqrt(Range / METRES500);				//CSB 07/06/99	
					if(ai.desiredrange)									  //JIM 18/05/99
					if(r > ai.desiredrange)								  //JIM 18/05/99
					{
						if(r < 2)
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CLOSEUP, MSG_FORMATIONFLYING_RPT, leadac, NULL, this));
						else if(r < 4)
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CLOSER, MSG_FORMATIONFLYING_RPT, leadac, NULL, this));
						else if(r < 8)
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_GETBACK, MSG_FORMATIONFLYING_RPT, leadac, NULL, this));
						else
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_GETCLOSER, MSG_FORMATIONFLYING_RPT, leadac, NULL, this));
					}
					ai.desiredrange = r;										  //JIM 18/05/99

				}
	
				if((!(leadac->fly.pModel->FrameCount & 0xFF)) && (leadac->Distance3DSquared(&World) < FP(METRES15) * FP(METRES15)))
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOTTHATCLOSE, MSG_FORMATIONFLYING_RPT, leadac, NULL, this));
			}
			else
			{
				if((fly.leadflight) && (waypoint->NextWP(this) == fly.leadflight->waypoint))
				{
					if(Distance3DSquared(FindDesPos()) < FP(desposrange + METRES10KM) * FP(desposrange + METRES10KM))
						ExecuteWayPointAction();
				}
				else
				{
					COORDS3D thiswpworld = waypoint->World;
					if(waypoint->target)
					{
						thiswpworld.X += waypoint->target->World.X;
//DeadCode CSB 12Sep00 						thiswpworld.Y += waypoint->target->World.Y;
						thiswpworld.Z += waypoint->target->World.Z;	
					}
					thiswpworld.Y = World.Y;
					FP dist2wp = Distance3DSquared(&thiswpworld);

					if(waypoint->range)
					{
						if(dist2wp < FP(waypoint->range) * FP(waypoint->range))
							ExecuteWayPointAction();
					}
					else
					{
						WayPointPtr	nextwp = waypoint->NextWP(this);
						if(nextwp != waypoint)
						{
							COORDS3D nextwpworld = nextwp->World;
							if(nextwp->target)
							{
								nextwpworld.X += nextwp->target->World.X;
	//DeadCode CSB 12Sep00 							nextwpworld.Y += nextwp->target->World.Y;
								nextwpworld.Z += nextwp->target->World.Z;	
							}
							nextwpworld.Y = World.Y;
							FP dist2apart =		FP(nextwpworld.X - thiswpworld.X) * FP(nextwpworld.X - thiswpworld.X)
											+	FP(nextwpworld.Z - thiswpworld.Z) * FP(nextwpworld.Z - thiswpworld.Z);
							FP dist2next = Distance3DSquared(&nextwpworld);
							if(		((dist2wp < dist2apart * 0.05) && (dist2next < dist2apart))
								/*||	(dist2next < dist2wp)*/	) 
								ExecuteWayPointAction();
						}
						else
							if(dist2wp < FP(waypoint->range + METRES1000) * FP(waypoint->range + METRES1000))
								ExecuteWayPointAction();
					}
				}
			}
			break;
		}

		case AUTO_BOMB:
		{
			if((ai.ManStep == 0) && (!formpos))
			{
				for(AirStrucPtr ld = this; ld; ld = ld->fly.nextflight)
					for(AirStrucPtr ac = ld; ac; ac = ac->Follower())
						ac->ai.ManStep = 1;
				ai.ManStep = 3;
			}

			if(ai.ManStep == 15)
			{
				bool exitbomb = true;
				for(AirStrucPtr ld = this; ld; ld = ld->fly.nextflight)
					for(AirStrucPtr ac = ld; ac; ac = ac->Follower())
						if(ac->ai.ManStep != 15)
							exitbomb = false;
				if(exitbomb)
					for(AirStrucPtr ld = this; ld; ld = ld->fly.nextflight)
						for(AirStrucPtr ac = ld; ac; ac = ac->Follower())
						{
							ac->movecode = AUTO_FOLLOWWP;
							ac->waypoint = ac->waypoint->NextWP(ac);
							ac->information = IF_OUT_POS;
							ac->manoeuvretime = 0;
						}
			}
		}
		
		case AUTO_TRAININGFORMATION:
		{
			static bool finished;
			static SLong timeinform;
			const SLong totaltime = 2 * 60 * SECS100;
			const FP gooddist2 = FP(METRES100) * FP(METRES100);
			const FP baddist2  = FP(METRES500) * FP(METRES500);
			const FP goodscore   = 0.8;
			const FP badscore    = 0.5;

			if((!_Replay.Playback) && (Persons2::PlayerSeenAC->fly.pModel->FirstCycle))
			{
				finished = false;
				timeinform = 0;
				SetManoeuvreTime(totaltime);
			}

			AirStrucPtr lead = FindFormpos0();
			if((!finished) && (lead) && (lead != this))
			{
				despos = *PositionWRTLeader();
				FP dist2 = Distance3DSquared(&despos);

	//DEADCODE CSB 02/03/00 PrintVar(60, 20, "Dist %.0f ", FP(FSqrt(dist2) * 0.01));

				if(dist2 > baddist2)
				{
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_WHATHELLDOING, MSG_STATUS, lead, NULL, this));
					finished = true;
				}
				else if(dist2 < gooddist2)
					timeinform += Timer_Code.FRAMETIME;

	//DEADCODE CSB 02/03/00 PrintVar(60, 21, "Good %.0f ", FP(timeinform * 0.01));
	//DEADCODE CSB 02/03/00 PrintVar(60, 22, "Time %.0f ", FP(manoeuvretime * 0.01));

				if(!TimeLeft())
				{
					FP score = timeinform / totaltime;
					if(score > goodscore)
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_GOOD, MSG_STATUS, lead, NULL, this));
					else if(score > badscore)
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOTBAD, MSG_STATUS, lead, NULL, this));
					else
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOTGOOD, MSG_STATUS, lead, NULL, this));

					finished = true;
				}
			}
			break;
		}
	}
}
		
//DeadCode CSB 12Sep00 	ANGLES	currintercept,originalintercept;
//DeadCode CSB 12Sep00 	SLong	range,dprange;
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 	COORDS3D* dp;
//DeadCode CSB 12Sep00 	if (movecode==AUTO_PRECOMBAT)
//DeadCode CSB 12Sep00 		if (ai.unfriendly==NULL)
//DeadCode CSB 12Sep00 			if (formpos)
//DeadCode CSB 12Sep00 			{
//DeadCode CSB 12Sep00 				InterceptandRange (dp=PositionWRTLeader ());
//DeadCode CSB 12Sep00 				range=Range;
//DeadCode CSB 12Sep00 				currintercept=originalintercept=HdgIntercept;
//DeadCode CSB 12Sep00 				dprange=0;
//DeadCode CSB 12Sep00 			}
//DeadCode CSB 12Sep00 			else
//DeadCode CSB 12Sep00 				movecode=AUTO_FOLLOWWP;
//DeadCode CSB 12Sep00 		else
//DeadCode CSB 12Sep00 		{
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 			dp=&ai.unfriendly->World;
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 			dprange=METRES500;
//DeadCode CSB 12Sep00 			InterceptandRange (dp);
//DeadCode CSB 12Sep00 			if (Range>dprange)
//DeadCode CSB 12Sep00 				InterceptandRange (dp=FindCombatPos());
//DeadCode CSB 12Sep00 			else
//DeadCode CSB 12Sep00 				currintercept=originalintercept=HdgIntercept;
//DeadCode CSB 12Sep00 			currintercept=originalintercept=HdgIntercept;
//DeadCode CSB 12Sep00 			range=Range;
//DeadCode CSB 12Sep00 		}
//DeadCode CSB 12Sep00 	elseif (movecode==AUTO_COMBAT)
//DeadCode CSB 12Sep00 	{
//DeadCode CSB 12Sep00 		if (formpos)
//DeadCode CSB 12Sep00 			if (fly.leadflight->movecode!=AUTO_COMBAT)
//DeadCode CSB 12Sep00 			{
//DeadCode CSB 12Sep00 				movecode=(AutoMoveCodeTypeSelect)fly.leadflight->movecode;
//DeadCode CSB 12Sep00 			}
//DeadCode CSB 12Sep00 			elseif (	fly.leadflight->ai.manoeuvre==MANOEUVRE_TOPCOVER
//DeadCode CSB 12Sep00 					&&	ai.manoeuvre!=MANOEUVRE_TOPCOVER
//DeadCode CSB 12Sep00 					)
//DeadCode CSB 12Sep00 			{
//DeadCode CSB 12Sep00 //TEMP			 	Persons_2.AddMessage(UserMsg::GOHOME,TEXT_LEADERGOINGHOME,fly.leadflight);
//DeadCode CSB 12Sep00 				ai.manoeuvre=MANOEUVRE_TOPCOVER;
//DeadCode CSB 12Sep00 				SetUnfriendly(NULL);									//CSB 1Aug00
//DeadCode CSB 12Sep00 //DeadCode CSB 1Aug00 				if (	ai.unfriendly
//DeadCode CSB 12Sep00 //DeadCode CSB 1Aug00 					&&	ai.unfriendly->Status.size==AIRSTRUCSIZE
//DeadCode CSB 12Sep00 //DeadCode CSB 1Aug00 					&&	((AirStrucPtr)ai.unfriendly)->ai.attacker==this
//DeadCode CSB 12Sep00 //DeadCode CSB 1Aug00 					)
//DeadCode CSB 12Sep00 //DeadCode CSB 1Aug00 					((AirStrucPtr)ai.unfriendly)->ai.attacker=NULL;
//DeadCode CSB 12Sep00 //DeadCode CSB 1Aug00 				ai.unfriendly=NULL;
//DeadCode CSB 12Sep00 			}
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 		if (ai.unfriendly)
//DeadCode CSB 12Sep00 		{
//DeadCode CSB 12Sep00 			InterceptandRange (dp=&ai.unfriendly->World);
//DeadCode CSB 12Sep00 			range=Range;
//DeadCode CSB 12Sep00 			currintercept=originalintercept=HdgIntercept;
//DeadCode CSB 12Sep00 			dprange=METRES100;
//DeadCode CSB 12Sep00 		}
//DeadCode CSB 12Sep00 		else
//DeadCode CSB 12Sep00 		{
//DeadCode CSB 12Sep00 			if (	//ai.manoeuvre==MANOEUVRE_TOPCOVER &&			//JIM 03Dec96
//DeadCode CSB 12Sep00 				formpos==0)
//DeadCode CSB 12Sep00 				if (ACMAS().AllOnTopCover())
//DeadCode CSB 12Sep00 				{
//DeadCode CSB 12Sep00 					Art_Int.AllBreakOff(this);									//JIM 16Jul96
//DeadCode CSB 12Sep00 //TEMP				 	Persons_2.AddMessage(UserMsg::GOHOME,TEXT_SQUADRONREGROUPED,NULL);
//DeadCode CSB 12Sep00 				}
//DeadCode CSB 12Sep00 				elseif (ACMAS().AllButLdrNotOnCombat ())
//DeadCode CSB 12Sep00 				{
//DeadCode CSB 12Sep00 					ai.manoeuvre=MANOEUVRE_TOPCOVER;
//DeadCode CSB 12Sep00 				}
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 			return;
//DeadCode CSB 12Sep00 		}
//DeadCode CSB 12Sep00 	}
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 	elseif (movecode==AUTO_BOMB || movecode==AUTO_CAS)
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 	{
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 		if (!ai.unfriendly)
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 		{
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 			if (movecode==AUTO_BOMB)
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 				movecode=AUTO_FOLLOWWP;
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 		}
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 		else
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 		{
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 			if (!SelectedElement(ai.unfriendly,ai.manoeuvre.value))
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 			{
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 				int newelt;
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 				ItemPtr trg=SelectTarget(ai.unfriendly,&newelt);
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 				if (!SelectedElement(trg,newelt))
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 					trg=NULL;
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 				OverLay.DecisionMessage(FACMsg,FAC_BombsAway,this,trg,this,FALSE);	//RJS 09Jun99
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 			}
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 		}
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 		OverLay.CancelAccel();
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 		range = 1;		//CSB 13/07/99	Force it to fail later test
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 		dprange = 0;	//CSB 13/07/99	
//DeadCode CSB 12Sep00 //DEADCODE CSB 14/02/00 	}
//DeadCode CSB 12Sep00 	elseif (!FlyEscortTo())
//DeadCode CSB 12Sep00 	{	//followwp
//DeadCode CSB 12Sep00 		InterceptandRange (dp=FindDesPos ());
//DeadCode CSB 12Sep00 		dprange=desposrange+MILES01;	//make it easy for player
//DeadCode CSB 12Sep00 		if (PitchIntercept>ANGLES_85Deg)
//DeadCode CSB 12Sep00 			Range=0;
//DeadCode CSB 12Sep00 		if (waypoint && !formpos && fly.leadflight && fly.leadflight->waypoint==waypoint->next)
//DeadCode CSB 12Sep00 			dprange+=METRES10KM;			//escortee just gone through. See AutoFollowWP
//DeadCode CSB 12Sep00 		originalintercept=currintercept=HdgIntercept;
//DeadCode CSB 12Sep00 		range=Range;
//DeadCode CSB 12Sep00 		WayPointPtr	wp=fly.backupWP;
//DeadCode CSB 12Sep00 		if (wp==NULL)
//DeadCode CSB 12Sep00 			wp=waypoint;
//DeadCode CSB 12Sep00 		if (movecode==AUTO_TAXI && vel_ > 5*60 * 1000)					//RDH 11Dec96
//DeadCode CSB 12Sep00 			movecode=AUTO_FOLLOWWP;								//RDH 11Dec96
//DeadCode CSB 12Sep00 //TempCode JIM 14Nov96 		if (wp && wp->prev)
//DeadCode CSB 12Sep00 //TempCode JIM 14Nov96 		{
//DeadCode CSB 12Sep00 //TempCode JIM 14Nov96 			InterceptandRange(wp->prev->FindDesPos());
//DeadCode CSB 12Sep00 //TempCode JIM 14Nov96 			originalintercept=(ANGLES)(HdgIntercept+ANGLES_180Deg);	//still have old intercept
//DeadCode CSB 12Sep00 //TempCode JIM 14Nov96 		}
//DeadCode CSB 12Sep00 //TempCode JIM 14Nov96 //complicates dp calculation
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 	}
//DeadCode CSB 12Sep00 	else if(!Status.deadtime)	//CSB 09/06/99	
//DeadCode CSB 12Sep00 	{	//followwp wing
//DeadCode CSB 12Sep00 		AirStrucPtr leadac=Leader();
//DeadCode CSB 12Sep00 		if (!leadac)
//DeadCode CSB 12Sep00 			leadac=fly.leadflight;
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 		InterceptandRange (dp=PositionWRTLeader ());
//DeadCode CSB 12Sep00 		range=Range;
//DeadCode CSB 12Sep00 		currintercept=originalintercept=HdgIntercept;
//DeadCode CSB 12Sep00 		dprange=0;
//DeadCode CSB 12Sep00 		if (range>METRES100)
//DeadCode CSB 12Sep00 		{
//DeadCode CSB 12Sep00 			information=IF_OUT_POS;
//DeadCode CSB 12Sep00 			leadac->slowdownleader=TRUE;
//DeadCode CSB 12Sep00 			if (fly.leadflight)
//DeadCode CSB 12Sep00 				fly.leadflight->slowdownleader=TRUE;
//DeadCode CSB 12Sep00 //DeadCode CSB 07/06/99				int r=range/METRES250;	  //7 bits=12800 metres
//DeadCode CSB 12Sep00 			int r = (int)FSqrt(range/METRES500);				//CSB 07/06/99	
//DeadCode CSB 12Sep00 			if (ai.desiredrange)									  //JIM 18/05/99
//DeadCode CSB 12Sep00 				if (r>ai.desiredrange)								  //JIM 18/05/99
//DeadCode CSB 12Sep00 					if(r < 2)
//DeadCode CSB 12Sep00 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CLOSEUP, MSG_FORMATIONFLYING_RPT, leadac, NULL, this));
//DeadCode CSB 12Sep00 					else if(r < 4)
//DeadCode CSB 12Sep00 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CLOSER, MSG_FORMATIONFLYING_RPT, leadac, NULL, this));
//DeadCode CSB 12Sep00 					else if(r < 8)
//DeadCode CSB 12Sep00 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_GETBACK, MSG_FORMATIONFLYING_RPT, leadac, NULL, this));
//DeadCode CSB 12Sep00 					else
//DeadCode CSB 12Sep00 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_GETCLOSER, MSG_FORMATIONFLYING_RPT, leadac, NULL, this));
//DeadCode CSB 12Sep00 			ai.desiredrange=r;										  //JIM 18/05/99
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 		}
//DeadCode CSB 12Sep00 		else
//DeadCode CSB 12Sep00 			information=IF_NEAR_POS;
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 		if((!(leadac->fly.pModel->FrameCount & EVERY256cs)) && (leadac->Distance3DSquared(&World) < FP(METRES15) * FP(METRES15)))
//DeadCode CSB 12Sep00 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOTTHATCLOSE, MSG_FORMATIONFLYING_RPT, leadac, NULL, this));
//DeadCode CSB 12Sep00 	}
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 	//now what?
//DeadCode CSB 12Sep00 	if (range<dprange)											//JIM 20Aug96
//DeadCode CSB 12Sep00 	{	//reached waypoint near enough							//JIM 20Aug96
//DeadCode CSB 12Sep00 //DeadCode JIM 03Dec96 		if (waypoint && movecode<AUTO_PRECOMBAT)				//JIM 20Aug96
//DeadCode CSB 12Sep00 		if(		(movecode != AUTO_CRASHSKID)
//DeadCode CSB 12Sep00 			&&	(movecode != AUTO_CRASHROLL)
//DeadCode CSB 12Sep00 			&&	(movecode != AUTO_CRASHONEWHEEL)
//DeadCode CSB 12Sep00 			&&	(movecode != AUTO_CRASHNOSE)
//DeadCode CSB 12Sep00 			&&	(movecode != AUTO_CRASHFLIP)
//DeadCode CSB 12Sep00 			&&	(movecode != AUTO_CRASHTUMBLE)
//DeadCode CSB 12Sep00 			&&	(movecode != AUTO_DEATHSEQUENCE)
//DeadCode CSB 12Sep00 			&&	(movecode != AUTO_FOLLOWTHELEADER)
//DeadCode CSB 12Sep00 			&&	(movecode != AUTO_TRAININGTAKEOFF)
//DeadCode CSB 12Sep00 			&&	(movecode != AUTO_TRAININGLANDING)
//DeadCode CSB 12Sep00 			&&	(movecode != AUTO_PRECOMBAT)
//DeadCode CSB 12Sep00 			&&	(movecode != AUTO_COMBAT)
//DeadCode CSB 12Sep00 			&&	(movecode != AUTO_BOMB)		)
//DeadCode CSB 12Sep00 //DeadCode CSB 22Jun00 		if (movecode<AUTO_PRECOMBAT)				//JIM 20Aug96
//DeadCode CSB 12Sep00 		{														//JIM 20Aug96
//DeadCode CSB 12Sep00 //			UserMsg::Reason	r=UserMsg::PASSEDWP;
//DeadCode CSB 12Sep00 			//tests for special waypoints
//DeadCode CSB 12Sep00 //DeadCode AMM 10Jun98 			if (!waypoint || waypoint->uniqueID.deaded)			//RJS 27Feb98
//DeadCode CSB 12Sep00 //DeadCode AMM 30Nov98 			if (!waypoint || waypoint->uniqueID.commsmove)		//AMM 10Jun98
//DeadCode CSB 12Sep00 			if (!waypoint || waypoint->Status.deaded)			//AMM 30Nov98
//DeadCode CSB 12Sep00 			{
//DeadCode CSB 12Sep00 				ExecuteWayPointAction();
//DeadCode CSB 12Sep00 			}
//DeadCode CSB 12Sep00 			else
//DeadCode CSB 12Sep00 			{
//DeadCode CSB 12Sep00 //DeadCode JIM 06Dec96 				TextSnip0	t=waypoint->GetWpName();
//DeadCode CSB 12Sep00 				ExecuteWayPointAction();
//DeadCode CSB 12Sep00 //DeadCode JIM 06Dec96 				Persons_2.AddMessage(r,t,*FindDesPos ());
//DeadCode CSB 12Sep00 //DeadCode RDH 15Oct96 				Persons_2.ClrMessage(UserMsg::COURSE);
//DeadCode CSB 12Sep00 			}
//DeadCode CSB 12Sep00 		}
//DeadCode CSB 12Sep00 		elseif (movecode==AUTO_PRECOMBAT)
//DeadCode CSB 12Sep00 		{	//switch to engage
//DeadCode CSB 12Sep00 			Art_Int.AllEngage(this);
//DeadCode CSB 12Sep00 		}
//DeadCode CSB 12Sep00 	}
//DeadCode CSB 12Sep00 	elseif (range>METRES500+dprange)
//DeadCode CSB 12Sep00 	{
//DeadCode CSB 12Sep00 //DEADCODE JIM 16/11/99 		despos=*dp;
//DeadCode CSB 12Sep00 //DEADCODE JIM 16/11/99 		if (Math_Lib.AbsSign((SWord)(currintercept-hdg))>ANGLES_30Deg)
//DeadCode CSB 12Sep00 //DEADCODE JIM 16/11/99 //hard:   if (Math_lib.AbsSign(currintercept-originalintercept)>ANGLES_30Deg)
//DeadCode CSB 12Sep00 //DEADCODE JIM 16/11/99 //TEMP			Persons_2.AddMessage(UserMsg::COURSE,TEXT_NULL,despos);
//DeadCode CSB 12Sep00 //DEADCODE JIM 16/11/99 			;
//DeadCode CSB 12Sep00 	}
//DeadCode CSB 12Sep00 	if (movecode != AUTO_COMBAT)
//DeadCode CSB 12Sep00 	{//don't want this message when in combat						  //RDH 30/04/99
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 		ItemBasePtr corner=Persons2::ConvertPtrUID(UID_StNamsanni);
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 		if (corner->World.X>World.X)
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 		{	//sinuiju corner
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 			if ((corner->World.X-World.X)>(corner->World.Z-World.Z))
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 			{
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 				AirStrucPtr buddy=FindBuddy();
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 				if (buddy)
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CROSSRIVER, MSG_CROSSRIVER, buddy, NULL, this));
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 			}
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 		}
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 		else
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 		{	//north korea
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 			if (corner->World.Z<World.Z)
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 			{
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 				AirStrucPtr buddy=FindBuddy();
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 				if (buddy)
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CROSSRIVER, MSG_CROSSRIVER, buddy, NULL, this));
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 			}
//DeadCode CSB 12Sep00 //DEADCODE RJS 16/11/99 		}
//DeadCode CSB 12Sep00 	}
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 	if(movecode == AUTO_TRAININGFORMATION)
//DeadCode CSB 12Sep00 	{
//DeadCode CSB 12Sep00 		static bool finished;
//DeadCode CSB 12Sep00 		static SLong timeinform;
//DeadCode CSB 12Sep00 		const SLong totaltime = 2 * 60 * SECS100;
//DeadCode CSB 12Sep00 		const FP gooddist2 = FP(METRES100) * FP(METRES100);
//DeadCode CSB 12Sep00 		const FP baddist2  = FP(METRES500) * FP(METRES500);
//DeadCode CSB 12Sep00 		const FP goodscore   = 0.8;
//DeadCode CSB 12Sep00 		const FP badscore    = 0.5;
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 		if((!_Replay.Playback) && (Persons2::PlayerSeenAC->fly.pModel->FirstCycle))
//DeadCode CSB 12Sep00 		{
//DeadCode CSB 12Sep00 			finished = false;
//DeadCode CSB 12Sep00 			timeinform = 0;
//DeadCode CSB 12Sep00 			SetManoeuvreTime(totaltime);
//DeadCode CSB 12Sep00 		}
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 		AirStrucPtr lead = FindFormpos0();
//DeadCode CSB 12Sep00 		if((!finished) && (lead) && (lead != this))
//DeadCode CSB 12Sep00 		{
//DeadCode CSB 12Sep00 			despos = *PositionWRTLeader();
//DeadCode CSB 12Sep00 			FP dist2 = Distance3DSquared(&despos);
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 //DEADCODE CSB 02/03/00 PrintVar(60, 20, "Dist %.0f ", FP(FSqrt(dist2) * 0.01));
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 			if(dist2 > baddist2)
//DeadCode CSB 12Sep00 			{
//DeadCode CSB 12Sep00 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_WHATHELLDOING, MSG_STATUS, lead, NULL, this));
//DeadCode CSB 12Sep00 				finished = true;
//DeadCode CSB 12Sep00 			}
//DeadCode CSB 12Sep00 			else if(dist2 < gooddist2)
//DeadCode CSB 12Sep00 				timeinform += Timer_Code.FRAMETIME;
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 //DEADCODE CSB 02/03/00 PrintVar(60, 21, "Good %.0f ", FP(timeinform * 0.01));
//DeadCode CSB 12Sep00 //DEADCODE CSB 02/03/00 PrintVar(60, 22, "Time %.0f ", FP(manoeuvretime * 0.01));
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 			if(!TimeLeft())
//DeadCode CSB 12Sep00 			{
//DeadCode CSB 12Sep00 				FP score = timeinform / totaltime;
//DeadCode CSB 12Sep00 				if(score > goodscore)
//DeadCode CSB 12Sep00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_GOOD, MSG_STATUS, lead, NULL, this));
//DeadCode CSB 12Sep00 				else if(score > badscore)
//DeadCode CSB 12Sep00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOTBAD, MSG_STATUS, lead, NULL, this));
//DeadCode CSB 12Sep00 				else
//DeadCode CSB 12Sep00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOTGOOD, MSG_STATUS, lead, NULL, this));
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 				finished = true;
//DeadCode CSB 12Sep00 			}
//DeadCode CSB 12Sep00 		}
//DeadCode CSB 12Sep00 	}
//DeadCode CSB 12Sep00 }

