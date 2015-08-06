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
//Filename       tank.cpp
//System         
//Author         R. Hyde 
//Date           Fri 9 Aug 1996
//Description    Code which sequences the loading of battlefields
//				Decides which file to load next and what globrefs need setting up.
//				This is basically a state engine loop
//				Originally invented to drive the dynamic tank campaign in FC
//------------------------------------------------------------------------------
//Questions
//
//
//	To reduce the number of UIDs needed for storing aircraft, and to ensure they are loaded monotonic increasing, so don't need specifying 
//	I reorder the sparse set of actual flying aircraft to use sequential numbers.
//	Some of the code in this file sees un-reordered targets and some sees reordered targets
//
#define F_GRAFIX
#define F_SOUNDS
#define F_COMMON

//DeadCode JIM 19Aug96 	#include	"bfcommon.h"
			#include	"dosdefs.h"
//TEMPCODE DAW 13/04/00 			#include	"text.h"
			#include	"persons2.h"
			#include	"savegame.h"
			#include	"missman2.h"
			#include	"enumbits.m"
			#include	"mymath.h"
			#include	"Mytime.h"			//CFont
			#include	"myerror.h"	
			#include	"node.h"
#define	QUICKQUICKQUICK
			#include	"squick1.h"
			#include	"globrefs.h"  
			#include	"stub3d.h"
			#include	"rchatter.h"
#include "monotxt.h"							//RJS 15Aug00

MissMan	Miss_Man;
//DeadCode JIM 19Aug96 	enum	BattlefieldType	{MAINWORLDBF = 0, BFMAXCOUNTER = 255,BFTYPE = 256,PLAYERBF = BFTYPE,
//DeadCode JIM 19Aug96 							ROUTEBF = 2*BFTYPE,CONVOYBF = 3*BFTYPE,
//DeadCode JIM 19Aug96 							AAABF =  4*BFTYPE,ENEMYACBF = 5*BFTYPE,
//DeadCode JIM 19Aug96 							CONVOYCOUNT = 6*BFTYPE, AAACOUNT = 7*BFTYPE,
//DeadCode JIM 19Aug96 							FINISHBF = 8*BFTYPE
//DeadCode JIM 19Aug96 							};
//DeadCode JIM 19Aug96 
//extern	ULong GR_WP1;
//extern	ULong GR_WP2;
//extern	ULong GR_ConvoyCount;
//extern	ULong GR_ConvoyUid;
//DeadCode RDH 02Dec96 extern	ULong GR_GunSite;
//extern	ULong GR_AAASite;
//extern	ULong
//
////DeadCode RDH 08Oct96 					GR_bluestrength,
//					GR_MainPosX,
//					GR_MainPosY,
//					GR_MainPosZ,
//					GR_SubPosX,
//					GR_SubPosY,
//					GR_SubPosZ,
//					GR_MainAction,		//RDH 05Dec96
//					GR_SubAction,		//RDH 05Dec96
//					GR_MainObjective,										//MS 21Jun96
//					GR_SubObjective;										//MS 21Jun96
BITABLE(Persons2::BattlefieldType);
MATHABLE(Persons2::BattlefieldType);

#ifndef	NDEBUG
#define	_ALERTFUDGE_
#endif
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetSecondWP
//Author		R. Hyde 
//Date			Thu 17 Oct 1996
//
//Description		Miss_Man.camp.playerbfield==FIL_NULL when entering map
//						When entering map we don't want to increment wps
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADvoid	Persons2::SetSecondWP (WayPointPtr	tmpitem)
//DEAD{
//DEAD	UniqueIDBand	uidband;
//DEAD
//DEAD	if (tmpitem)
//DEAD	{
//DEAD		uidband = getbandfromUID((UniqueID)tmpitem->target->uniqueID.count);
//DEAD		if (uidband == RedMilitaryBAND)
//DEAD		{
//DEAD//DeadCode RDH 22Oct96 			if (tmpitem->target->Status.deadtime != 0)
//DEAD//DeadCode RDH 22Oct96 			{
//DEAD				if (Miss_Man.camp.playerbfield==FIL_NULL)
//DEAD				{
//DEAD					GR_WP2 = GR_WP1;
//DEAD				}else
//DEAD				{
//DEAD//DeadCode RDH 05Dec96 					if (tmpitem->next==NULL)
//DEAD//DeadCode RDH 05Dec96 						_Error.EmitSysErr("second waypoint null");
//DEAD//DeadCode RDH 05Dec96 					GR_WP2 = tmpitem->next->uniqueID.count;
//DEAD					if (tmpitem->next==NULL)					//RDH 05Dec96
//DEAD						GR_WP2 = GR_WP1;						//RDH 05Dec96
//DEAD					else										//RDH 05Dec96
//DEAD						GR_WP2 = tmpitem->next->uniqueID.count;	//RDH 05Dec96
//DEAD				}
//DEAD
//DEAD//DeadCode RDH 22Oct96 			}else
//DEAD//DeadCode RDH 22Oct96 			{
//DEAD//DeadCode RDH 22Oct96 				GR_WP2 = GR_WP1;
//DEAD//DeadCode RDH 22Oct96 			}
//DEAD		}else
//DEAD		{
//DEAD			if (tmpitem->target->Status.deadtime != 0)
//DEAD			{
//DEAD				GR_WP2 = GR_WP1;
//DEAD			}else
//DEAD			{
//DEAD				if (Miss_Man.camp.playerbfield==FIL_NULL)
//DEAD				{
//DEAD					GR_WP2 = GR_WP1;
//DEAD				}else
//DEAD				{
//DEAD//DeadCode RDH 05Dec96 					if (tmpitem->next==NULL)
//DEAD//DeadCode RDH 05Dec96 						_Error.EmitSysErr("second waypoint null");
//DEAD//DeadCode RDH 05Dec96 					GR_WP2 = tmpitem->next->uniqueID.count;
//DEAD					if (tmpitem->next==NULL)					//RDH 05Dec96
//DEAD						GR_WP2 = GR_WP1;						//RDH 05Dec96
//DEAD					else										//RDH 05Dec96
//DEAD						GR_WP2 = tmpitem->next->uniqueID.count;	//RDH 05Dec96
//DEAD				}
//DEAD			}
//DEAD		}
//DEAD	}else
//DEAD	{
//DEAD		GR_WP2 = GR_WP1;
//DEAD	}
//DEAD
//DEAD}
//DEAD
inline UniqueID operator--(UniqueID& u,int) {return u=UniqueID(u-1);}
inline Persons2::BattlefieldType operator +=(Persons2::BattlefieldType& u,int i){return u=Persons2::BattlefieldType(u+i);}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindNextBf
//Author		R. Hyde 
//Date			Fri 9 Aug 1996
//
//Description	
//
//Inputs	nextbftype	- state control variable
//
//Returns	filenumber, or null to skip this one
//			nextbftype updated - set to FINISHBF to quit
//			some globrefs updated
//------------------------------------------------------------------------------
UByte RndSq256()
{
	UWord rv=Math_Lib.rnd();
	rv=rv|(rv>>8);
	return (UByte)rv;
}

int	RndSq256(int v)
{
	return (v*RndSq256())>>8;
}
enum	{MIGDAYSOUTH,MIGDAYDIRECT,MIGDAYLATEBARCAP,MIGDAYALLBARCAP,MIGDAYBIGTRAIN};


FileNum	Persons2::FindNextBf (BattlefieldType &nextbftype)
{
//DeadCode JIM 23Aug100 	_Radio.phrase_groundcontroller = 1;							//RJS 15Aug00


//DEADCODE RJS 15/02/00 	static	UniqueID	playertarget;
//DEADCODE JIM 16/11/99 	static	SupplyNode*	playernode;
//DEADCODE RJS 15/02/00 	static	int			flighttakeoffstep;
//DEADCODE RJS 15/02/00 	static	int			leftval,rightval;
//DEADCODE RJS 15/02/00 	static	int			migdaytype;
//DEADCODE RJS 15/02/00 	static	int		migcapstrength;
//DEADCODE RJS 15/02/00 	static	int		migcaptime;
	GR_movecode=AUTO_FOLLOWWP;
//DEADCODE JIM 16/11/99 	SupplyNode*	playernode2=playernode;
	UniqueIDBand	uidband;								//RDH 05Dec96
	BattlefieldType	n;
	WayPointPtr	tmpitem;
//DEADCODE CSB 07/06/00 	if (Todays_Packages[0].packagestatus!=Profile::PS_SPARE)
//DEADCODE CSB 07/06/00 	{
//DEADCODE CSB 07/06/00 		GR_TruckMoveCode=GROUND_TOGLOBREF;
//DEADCODE CSB 07/06/00 		GR_TakeOffTime = 9*12*60;
//DEADCODE CSB 07/06/00 	}
//DEADCODE CSB 07/06/00 	else
	{
		GR_TruckMoveCode=GROUND_TAXI;
		GR_TakeOffTime = MMC.currtime;
	}
	GR_GlobalSkillMin = SKILL_NOVICE;						//RDH 01Oct96
	GR_GlobalSkillMax = SKILL_MAX;							//CSB 29Oct00
	switch (nextbftype & BFPHASESMASK)
	{
	case	MAINWORLDBF:
	{
		GR_BLUESKILLCONFIG=Save_Data.autopilotskillLW;
		GR_REDSKILLCONFIG=Save_Data.autopilotskillRAF;
//				if (Todays_Packages[0][0][0].uid)
//				if (Todays_Packages[0].packagetarget)
//					nextbftype = ROUTEBF;
//				else
//					nextbftype = SCRAMBF;
//
//DEADCODE RJS 15/02/00 		migcaptime=0;
		nextbftype = CONVOYBF;	//REMOVE MACCAS  IF STATEMENT EDITS HERE!
//
		return(FIL_1_MAINWLD);
	}

	case	PLAYROUTEBF:
	{	//for the player's target area, launch all neighboring battlefields
		FileNum rv=FIL_NULL;
		switch (nextbftype)
		{
		case	PLAYROUTEBF:
		{
			if (Todays_Packages[0].packagestatus!=Profile::PS_SPARE)
			{	//find target[0] from selected package
				Profile* prof=&Todays_Packages[Todays_Packages.hipack];
				int tn=prof->squadlist[Todays_Packages.hisquad].targetindex;
				if (tn<0) tn=0;											//CSB 24/05/00
				GR_Pack_Target[0]=prof->packagetarget[tn].SGT;
				if (GR_Pack_Target[0]>=0x4000)
					GR_Pack_Target[0]=0;
				else
					if (GR_Pack_Target[0]>=SagBAND && GR_Pack_Target[0]<SagBANDEND)
					{
						int pt=GR_Pack_Target[0];
						GR_Pack_Target[0]=UID_NULL;
						for (int p=0;p<Profile::MAX_PACKS;p++)
							for (int s=0,max=Todays_Packages[p].squadlist.Max();s<max;s++)
								if (Todays_Packages[p][s].instance==pt)
								{
									GR_Pack_Target[0]=UniqueID(Todays_Packages[p].packagetarget[0]);
									s=max;
									p=Profile::MAX_PACKS;
								}
					}
				SquadNum sq=SquadNum(prof->squadlist[Todays_Packages.hisquad].squadnum);
				GR_Pack_Target[6]=Node_Data[sq].homeairfield;
				GR_Pack_Target[7]=Node_Data[sq].squadron;
			}
			else
			{
				GR_Pack_Target[0]=CSQuick1::quickdef.target;
				SquadNum sq=SquadNum(CSQuick1::quickdef.line[CSQuick1::quickdef.plside][CSQuick1::quickdef.plwave][CSQuick1::quickdef.plgrp].actype);
				UniqueIDBand	targband=GetBandFromUID(CSQuick1::quickdef.target);
				GR_Pack_Target[6]=Node_Data[sq].homeairfield;
				if (	CSQuick1::quickdef.currmissnum!=CSQuick1::quickdef.altmissnum 
					&& 	(targband==RAF_FighterAFBAND ||	 targband==LUF_FighterLF2BAND) 
					)
					GR_Pack_Target[6]=CSQuick1::quickdef.target;
				GR_Pack_Target[7]=Node_Data[sq].squadron;



			}
			{//context
				_Radio.phrase_groundcontroller=PHRASE_GROUNDCONTROLLERRAF0X-PHRASE_GROUNDCONTROLLERRAF;
				SquadNum sq=SquadNum(GR_Pack_Target[7]);
				if (sq>SQ_LW_START)
					_Radio.phrase_groundcontroller=/*PHRASE_GROUNDCONTROLLERLW+*/Node_Data.geschwader[GruppenPtr(Node_Data[sq])->wadernum].luftflotte;
				else
				{
					TargetPtr trg=&Node_Data[UniqueID(GR_Pack_Target[6])];
					if (trg->IsA(Target::TSS_TargetAirfield))
					{
						TargetSectorField* sf=TargetFighterFieldPtr(*trg)->getsectoraf();
						if (sf->groupname==IDS_GROUP_11)
							if (sf->sectorname<=('f'&0xf))
								_Radio.phrase_groundcontroller=/*PHRASE_GROUNDCONTROLLERRAF+*/sf->sectorname;
					}
				}
			}
			TargetGroup* tg=NULL;
			if (GR_Pack_Target[0])
				tg=Node_Data[UniqueID(GR_Pack_Target[0])];
			if (tg)
			{
				GR_Pack_Target[1]=tg->secondaries[0];
				GR_Pack_Target[2]=tg->secondaries[1];
				GR_Pack_Target[3]=tg->secondaries[2];
				GR_Pack_Target[4]=tg->secondaries[3];
				GR_Pack_Target[5]=tg->secondaries[4];
			}
			else
			{
				GR_Pack_Target[1]=
					GR_Pack_Target[2]=
						GR_Pack_Target[3]=
							GR_Pack_Target[4]=
									GR_Pack_Target[5]=UID_NULL;
			}
		}
		break;
///////////////////////////////////////////////////////////////
		case	TARGETDETBF:
			rv=Node_Data.TargetToBf(UniqueID(GR_Pack_Target[0]),false);
		break;
///////////////////////////////////////////////////////////////
		case	TARGETMOBBF:
			rv=Node_Data.TargetToBf(UniqueID(GR_Pack_Target[0]),true);
		break;
///////////////////////////////////////////////////////////////
		case	TAKEOFFDETBF:
			GR_Pack_Target[0]=GR_Pack_Target[6];
			rv=Node_Data.TargetToBf(UniqueID(GR_Pack_Target[0]),false);
		break;
///////////////////////////////////////////////////////////////
		case	TAKEOFFMOBBF:
			GR_Pack_Target[0]=GR_Pack_Target[6];
			rv=Node_Data.TargetToBf(UniqueID(GR_Pack_Target[0]),true);
		break;
///////////////////////////////////////////////////////////////
		case	TAKEOFFPTSBF:
		{
			GR_Pack_Target[0]=GR_Pack_Target[6];
			if (Node_Data[UniqueID(GR_Pack_Target[0])].IsA(Target::TSS_TargetAirfield))
//DeadCode JIM 14Nov00 			if (GR_Pack_Target[7]<SQ_LW_START)
			{
				TargetFighterField* tg=Node_Data[UniqueID(GR_Pack_Target[0])];
				rv=tg->taxibattlefield;
			}
		}
		break;
///////////////////////////////////////////////////////////////
		case	SECTRG0DETBF:
			GR_Pack_Target[0]=GR_Pack_Target[1];
			rv=Node_Data.TargetToBf(UniqueID(GR_Pack_Target[0]),false);
		break;
///////////////////////////////////////////////////////////////
		case	SECTRG0MOBBF:
			GR_Pack_Target[0]=GR_Pack_Target[1];
			rv=Node_Data.TargetToBf(UniqueID(GR_Pack_Target[0]),true);
		break;
///////////////////////////////////////////////////////////////
		case	SECTRG1DETBF:
			GR_Pack_Target[0]=GR_Pack_Target[2];
			rv=Node_Data.TargetToBf(UniqueID(GR_Pack_Target[0]),false);
		break;
///////////////////////////////////////////////////////////////
		case	SECTRG1MOBBF:
			GR_Pack_Target[0]=GR_Pack_Target[2];
			rv=Node_Data.TargetToBf(UniqueID(GR_Pack_Target[0]),true);
		break;
///////////////////////////////////////////////////////////////
		case	SECTRG2DETBF:
			GR_Pack_Target[0]=GR_Pack_Target[3];
			rv=Node_Data.TargetToBf(UniqueID(GR_Pack_Target[0]),false);
		break;
///////////////////////////////////////////////////////////////
		case	SECTRG2MOBBF:
			GR_Pack_Target[0]=GR_Pack_Target[3];
			rv=Node_Data.TargetToBf(UniqueID(GR_Pack_Target[0]),true);
		break;
///////////////////////////////////////////////////////////////
		case	SECTRG3DETBF:
			GR_Pack_Target[0]=GR_Pack_Target[4];
			rv=Node_Data.TargetToBf(UniqueID(GR_Pack_Target[0]),false);
		break;
///////////////////////////////////////////////////////////////
		case	SECTRG3MOBBF:
			GR_Pack_Target[0]=GR_Pack_Target[4];
			rv=Node_Data.TargetToBf(UniqueID(GR_Pack_Target[0]),true);
		break;
///////////////////////////////////////////////////////////////
		case	SECTRG4DETBF:
			GR_Pack_Target[0]=GR_Pack_Target[5];
			rv=Node_Data.TargetToBf(UniqueID(GR_Pack_Target[0]),false);
		break;
///////////////////////////////////////////////////////////////
		case	SECTRG4MOBBF:
			GR_Pack_Target[0]=GR_Pack_Target[5];
			rv=Node_Data.TargetToBf(UniqueID(GR_Pack_Target[0]),true);
		break;
///////////////////////////////////////////////////////////////
		case	ENDPLAYTARGBF:
		{}
		}
		if (nextbftype==ENDPLAYTARGBF)
		{
			if (Todays_Packages[0].packagestatus==Profile::PS_SPARE)
				nextbftype=SCRAMBF;
			else
				nextbftype=PACKPLAYERBF;
		}
		else
			nextbftype++;
		return rv;
	}
	break;
//////////////////////////////////////////////////////////////////////
//
// Function:    SCRAMBF
// Date:		15/02/00
// Author:		RJS
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
	case	SCRAMBF:
	{	//set up to load the scramble battlefield
		FileNum rv=FIL_NULL;
		switch (nextbftype)
		{
		case SCRAMBF:
		{	//set up to do airfields for all custom squads
		}
		break;
///////////////////////////////////////////////////
		case	SQ0TODETBF:
		case	SQ1TODETBF:
		case	SQ2TODETBF:
		case	SQ3TODETBF:
		case	SQ4TODETBF:
		case	SQ5TODETBF:
		case	SQ6TODETBF:
		case	SQ7TODETBF:
		case	SQ8TODETBF:
		case	SQ9TODETBF:
		case	SQ10TODETBF:
		case	SQ11TODETBF:
		case	SQ12TODETBF:
		{
			Squadron* sq=Node_Data[SquadNum(nextbftype-SQ0TODETBF)];
			if (sq)
			{
				GR_Pack_Target[0]=sq->homeairfield;
				rv=Node_Data.TargetToBf(sq->homeairfield);
			}
		}
		break;
///////////////////////////////////////////////////
		case LOADSCRAMBF:
		{	
			GR_OkToQuit3DNow=0x1000000*100;
			int glind=0;
			for(int s=0;s<2;s++)
				for(int w=0;w<8;w++)
					for(int g=0;g<3;g++)
						if(CSQuick1::quickdef.line[s][w][g].flights || CSQuick1::quickdef.line[s][w][g].AllowZero())
						{
							GR_Scram_Alt[glind]=CSQuick1::quickdef.line[s][w][g].alt;
							//ac count depends on aircraft type...

							int	acperflight=CSQuick1::quickdef.line[s][w][g].ACPerFlight();




							GR_Scram_AC[glind]=CSQuick1::quickdef.line[s][w][g].flights*acperflight;
							GR_Scram_Skill[glind]=CSQuick1::quickdef.line[s][w][g].skill;
							GR_Scram_Squad[glind]=CSQuick1::quickdef.line[s][w][g].actype;
							glind++;
						}
						else
							GR_Scram_AC[glind]=0;
//DEADCODE RJS 15/02/00 				for(int w=0;w<8;w++)
//DEADCODE RJS 15/02/00 					GR_Pack_TakeTime[w][0]=GR_Pack_TakeTime[w][1]=GR_Pack_TakeTime[w][2]=0;
//DeadCode AMM 02Jun99 			for(int sq=0;sq<5;sq++)
			for (int sq=0;sq<=PT_GER_NONFLY;sq++)				//AMM 02Jun99
				GR_Pack_Sq_Used[sq]=0;
//DEADCODE RJS 15/02/00 			for (int squads=0;squads<PT_BRIT_NONFLY;squads++)
//DEADCODE RJS 15/02/00 				GR_Pack_Home[squads]=UID_AF_TANGMERE;//SupplyTree.airfieldinfo[MMC.squad[squads].airfieldindex].airfield;
//DEADCODE RJS 15/02/00 			for (squads=PT_BRIT_NONFLY;squads<8;squads++)
//DEADCODE RJS 15/02/00 				GR_Pack_Home[squads]=UID_AF_Abbeville;

			GR_Pack_Target[0]=CSQuick1::quickdef.target;
			for (int c=0;c<16;c++)
				if (CSQuick1::quickdef.targets[c/4][c%4]==CSQuick1::quickdef.target)
					GR_PackTrgNum=c;
//DeadCode AMM 17Nov98 				Pack_PlayerSquad=MMC.playersquadron;
//DeadCode AMM 17Nov98 				Pack_PlayerPos=MMC.playeracnum;
//DEADCODE RJS 16/02/00 			GR_WaveNum=-1;
			if (CSQuick1::quickdef.plside)
				rv= (FileNum)CSQuick1::quickdef.altmissnum;
			else
				rv= (FileNum)CSQuick1::quickdef.currmissnum;
//DeadCode AMM 5Sep00 // Fix-up Quick-Mission Diary Records...
//DeadCode AMM 5Sep00 
//DeadCode AMM 5Sep00 			Squad_Diary.EmptyDiary();
//DeadCode AMM 5Sep00 			Squad_Diary.CreateQuickEntry(GR_Scram_Alt,GR_Scram_AC,GR_Scram_Squad,glind,CSQuick1::quickdef.target);
//Fudge...
#ifdef	_ALERTFUDGE_
	Trans_Obj.alertfudge = ConvertPtrUID(CSQuick1::quickdef.target);
#endif
		}
		break;
		case  ENDSCRAMBF:
		{
			Diary::RaidGroup*	rptr = Squad_Diary.GetRaidGroup(Manual_Pilot.ControlledAC2->ai.diaryptr);
			Diary::Intercept*	iptr = Squad_Diary.GetFirstIntercept(rptr);
			if (iptr)
				Squad_Diary.UpdateIntercept(iptr,Manual_Pilot.ControlledAC2,iptr->takeofftime);
		}
		break;
		}
		if (nextbftype==ENDSCRAMBF)
			nextbftype=PACKPLAYERBF;
		else
			nextbftype++;
		return rv;
	}
	break;
//////////////////////////////////////////////////////////////////////
//
// Function:    CONVOYBF
// Date:		04/02/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
	case	CONVOYBF:
	if (Todays_Packages[0].packagestatus==Profile::PS_SPARE)
	{
		nextbftype=PLAYROUTEBF;
		return FIL_NULL;
	}
	else
	{
		int convnum=(nextbftype-CONVOYBF);
		TargetConvoy* convoy=Node_Data.convoylist+convnum;
		FileNum rv=FIL_NULL;
		if (convoy->uid==UID_NULL)
			nextbftype=PLAYROUTEBF;
		else
		{
			nextbftype = BattlefieldType(nextbftype+1);
			if (convoy->wpnum!=-1)
			{
				GR_redstrength=convoy->truestatus;
				GR_ItemInfoOverride=convoy->uid;
				GR_ItemWpOverride=convoy->wpnum;
				GR_ItemXOverride=convoy->X;
				GR_ItemZOverride=convoy->Z;
				rv=convoy->detailbattlefield;
			}

		}
		return rv;
	}



//////////////////////////////////////////////////////////////////////
//
// Function:    PLAYERBF
// Date:		04/02/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////

	case	PACKPLAYERBF:
	{	
		switch (nextbftype)
		{
/////////////////////////////////////////////////
		case PACKPLAYERBF:
		{
			GR_PackNum=-1;
			GR_PackFilNum=0; 

		}
		case PACKNEXTPACKBF:	//INTENTIONAL FALL-THROUGH!
		{
			int packnum=GR_PackNum+1;
			while (packnum<Profile::MAX_PACKS && Todays_Packages[packnum].wpsused==0)
				packnum++;
			GR_PackNum=packnum;
			if (packnum<Profile::MAX_PACKS)								//CSB 27Jul00
				if (Todays_Packages[packnum].attackmethod<Profile::AM_LWPACKS)
					if (GR_REDSKILLCONFIG>=2)
						GR_GlobalSkillMin = 3*(GR_REDSKILLCONFIG-2);						//RDH 01Oct96
					else
						GR_GlobalSkillMax = SKILL_HERO-(2-GR_REDSKILLCONFIG)*2;							//RDH 01Oct96
				else
					if (GR_BLUESKILLCONFIG>=2)
						GR_GlobalSkillMin = 3*(GR_BLUESKILLCONFIG-2);						//RDH 01Oct96
					else
						GR_GlobalSkillMax = SKILL_HERO-(2-GR_BLUESKILLCONFIG)*2;							//RDH 01Oct96
			if (packnum==Profile::MAX_PACKS)
				nextbftype=FINISHBF;
			else
				nextbftype=PACKTRGRESETBF;
		}
		return FIL_NULL;
/////////////////////////////////////////////////
		case PACKTRGRESETBF:
		{
			GR_OkToQuit3DNow=MMC.earliestquit3dtimecs;
			GR_PackTrgNum=0;
			nextbftype++;
		}
		//intensional fall-through
/////////////////////////////////////////////////
		case PACKTRGDETBF:
		{
			UniqueID t=Todays_Packages[GR_PackNum].packagetarget[GR_PackTrgNum];
			if (t==UID_NULL)
			{
				nextbftype++;		 //LOOP HERE UNTIL ALL TARGETS PROCESSED
				return FIL_NULL;
			}
			else
			{
				GR_PackTrgNum++;
				return Node_Data.TargetToBf(t,false);
			}
		}
/////////////////////////////////////////////////
		case PACKTORESETBF:		 
		{
			GR_PackTrgNum=0;
			nextbftype++;
		}
		//intensional fall-through
/////////////////////////////////////////////////
		case PACKTODETBF:
		{
			SquadNum sq=SquadNum(Todays_Packages[GR_PackNum][GR_PackTrgNum].squadnum);
			UniqueID t=Node_Data[sq].homeairfield;
			GR_PackTrgNum++;
			if (GR_PackTrgNum==Todays_Packages[GR_PackNum].squadlist)
				nextbftype++;	 //LOOP HERE UNTIL ALL TAKEOFFS PROCESSED
			return Node_Data.TargetToBf(t,false);
		}
/////////////////////////////////////////////////
		case  PACKACBF:
		{
			//The aircraft for each package...
//DeadCode CSB 28Jul00 			if (GR_BLUESKILLCONFIG>=2)
//DeadCode CSB 28Jul00 				GR_GlobalSkillMin = 3*(GR_BLUESKILLCONFIG-2);						//RDH 01Oct96
//DeadCode CSB 28Jul00 			else
//DeadCode CSB 28Jul00 				GR_GlobalSkillMax = SKILL_HERO-(2-GR_BLUESKILLCONFIG)*2;							//RDH 01Oct96

//DeadCode JIM 20Oct00 			FileNum rv=FIL_NULL;
			Todays_Packages[GR_PackNum].SetTargetUIDs(true);
			Todays_Packages[GR_PackNum].SetTargetGlobrefs(true);
			//Zoiks! These targets are pre- the reordering!
			for (int i=0;i<10;i++)
				SetLoc(SGR_Pack_Target+i,Todays_Packages.Reorder(UniqueID(GetLoc(SGR_Pack_Target+i))));
			WipeGlobrefPackVars();										//CSB 01/06/00
			nextbftype++;
			return FileNum(FIL_RUNTIMEPACK0+GR_PackFilNum++);
		}
		//intensional fall-through if run out of packs
/////////////////////////////////////////////////
		}	//end switch
		return FIL_NULL;
	}
	}	//end switch
	return(FIL_NULL);
}

//DEADCODE RJS 15/02/00 FileNum	Persons2::LaunchMigPatrol(SquadSelect squad,int prefsize,UniqueID takeoff,int migdaytype,int migcaptime)
//DEADCODE RJS 15/02/00 {
//DEADCODE RJS 15/02/00 	FileNum rv=FIL_NULL;
//DEADCODE JIM 16/11/99 	int	packnum=Math_Lib.rnd(Profile::MAX_PACKS);
//DEADCODE JIM 16/11/99 	while	(Todays_Packages[packnum][0][0].uid==UID_NULL)
//DEADCODE JIM 16/11/99 		packnum=Math_Lib.rnd(packnum);
//DEADCODE JIM 16/11/99 	UniqueID packtarg=Todays_Packages[packnum].packagetarget;
//DEADCODE JIM 16/11/99 	//pick a good profile for the day
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 	int criteria=-1;
//DEADCODE JIM 16/11/99 	int profilenum=-1;
//DEADCODE JIM 16/11/99 	int	range=0;
//DEADCODE JIM 16/11/99 	if (migdaytype>MIGDAYBIGTRAIN)
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99 	   profilenum=migdaytype;
//DEADCODE JIM 16/11/99 	   criteria=MigEvent::TRAIN_TARGET;
//DEADCODE JIM 16/11/99 	}
//DEADCODE JIM 16/11/99 	else
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 		ItemBasePtr	targitem=ConvertPtrUID(packtarg);
//DEADCODE JIM 16/11/99 		ItemBasePtr takeoffitem=ConvertPtrUID(takeoff);
//DEADCODE JIM 16/11/99 		if (targitem==NULL)											  //JIM 12/04/99
//DEADCODE JIM 16/11/99 		{
//DEADCODE JIM 16/11/99 			SupplyTree::Supply2UID relation;
//DEADCODE JIM 16/11/99 			SupplyNode* node=SupplyTree::FindSupplyNodeForItem(packtarg,&relation);
//DEADCODE JIM 16/11/99 			assert(node);
//DEADCODE JIM 16/11/99 			assert(UWord(relation-SupplyTree::S2U_ROUTE0)<3);
//DEADCODE JIM 16/11/99 			packtarg=node->route[relation-SupplyTree::S2U_ROUTE0]->supplier->associated_item;
//DEADCODE JIM 16/11/99 			targitem=ConvertPtrUID(packtarg);
//DEADCODE JIM 16/11/99 		}															  //JIM 12/04/99
//DEADCODE JIM 16/11/99 		range=Math_Lib.Distance2d(takeoffitem->World.X-targitem->World.X,takeoffitem->World.Z-targitem->World.Z);
//DEADCODE JIM 16/11/99 		//time in seconds... speed 250m/s plus allowance for getting there first 
//DEADCODE JIM 16/11/99 		int	arrivaltime=Todays_Packages[packnum][0].targettime-300-GR_TakeOffTime;
//DEADCODE JIM 16/11/99 		range-=arrivaltime*METRES240;	//actually, migs are doing 241.0
//DEADCODE JIM 16/11/99 		//negative range means delay takeoff
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 		if (Todays_Packages[packnum].duty&DA_CAP)
//DEADCODE JIM 16/11/99 				criteria=MigEvent::BARCAP;
//DEADCODE JIM 16/11/99 		elseif (migdaytype==MIGDAYSOUTH)
//DEADCODE JIM 16/11/99 			criteria=MigEvent::SOUTH_TARGET;
//DEADCODE JIM 16/11/99 		elseif (targitem->World.Z>Persons2::ConvertPtrUID(UID_AfRdSinanju)->World.Z)
//DEADCODE JIM 16/11/99 			criteria=MigEvent::LOCAL_TARGET;
//DEADCODE JIM 16/11/99 		elseif (migdaytype==MIGDAYDIRECT)
//DEADCODE JIM 16/11/99 			criteria=MigEvent::DIRECT_TARGET;
//DEADCODE JIM 16/11/99 		elseif (migdaytype==MIGDAYALLBARCAP)
//DEADCODE JIM 16/11/99 			criteria=MigEvent::DECOY_TARGET;
//DEADCODE JIM 16/11/99 		else
//DEADCODE JIM 16/11/99 		{	//where do we need to be now to intercept the bombers?
//DEADCODE JIM 16/11/99 			if (range>METRES50KM)
//DEADCODE JIM 16/11/99 				criteria=MigEvent::DIRECT_TARGET;
//DEADCODE JIM 16/11/99 			else
//DEADCODE JIM 16/11/99 				criteria=MigEvent::DECOY_TARGET;
//DEADCODE JIM 16/11/99 		}
//DEADCODE JIM 16/11/99 		profilenum=RndSq256(MMC.migsquad[squad-SQ_M15_0].maxevent+1);
//DEADCODE JIM 16/11/99 		int profdelta=0;
//DEADCODE JIM 16/11/99 		while(	(	(profilenum+profdelta>=0 && profilenum+profdelta<=MMC.migsquad[squad-SQ_M15_0].maxevent)
//DEADCODE JIM 16/11/99 				||	(profilenum-profdelta>=0 && profilenum-profdelta<=MMC.migsquad[squad-SQ_M15_0].maxevent)
//DEADCODE JIM 16/11/99 				)
//DEADCODE JIM 16/11/99 			&&	(	MMC.migevents[profilenum+profdelta].minlevel>=MMC.migsquad[squad-SQ_M15_0].agglevel
//DEADCODE JIM 16/11/99 				||	(MMC.migevents[profilenum+profdelta].eventdoes&criteria)!=criteria
//DEADCODE JIM 16/11/99 			)	)
//DEADCODE JIM 16/11/99 			if (profdelta>=0)
//DEADCODE JIM 16/11/99 				profdelta=-profdelta-1;
//DEADCODE JIM 16/11/99 			else
//DEADCODE JIM 16/11/99 				profdelta=-profdelta;
//DEADCODE JIM 16/11/99 				
//DEADCODE JIM 16/11/99 		if (profilenum+profdelta>=0 && profilenum+profdelta<=MMC.migsquad[squad-SQ_M15_0].maxevent)
//DEADCODE JIM 16/11/99 			profilenum=profilenum+profdelta;
//DEADCODE JIM 16/11/99 		else
//DEADCODE JIM 16/11/99 			profilenum=-1;
//DEADCODE JIM 16/11/99 	}
//DEADCODE JIM 16/11/99 	if (profilenum==-1)
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99 		profilenum=MIGEV_SANCPAT;
//DEADCODE JIM 16/11/99 		criteria=MigEvent::LOCAL;
//DEADCODE JIM 16/11/99 	}
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 	GR_WaveNum=-1;								//flag not a package
//DEADCODE JIM 16/11/99 	if (prefsize)
//DEADCODE JIM 16/11/99 		if (MMC.migevents[profilenum].maxformsize>prefsize)
//DEADCODE JIM 16/11/99 			GR_FormSize00=MMC.migevents[profilenum].maxformsize;
//DEADCODE JIM 16/11/99 		elseif (MMC.migevents[profilenum].minformsize>prefsize)
//DEADCODE JIM 16/11/99 			GR_FormSize00=MMC.migevents[profilenum].minformsize;
//DEADCODE JIM 16/11/99 		else
//DEADCODE JIM 16/11/99 			GR_FormSize00=prefsize;
//DEADCODE JIM 16/11/99 	else
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99 		GR_FormSize00=MMC.migevents[profilenum].minformsize
//DEADCODE JIM 16/11/99 						+Math_Lib.rnd(MMC.migevents[profilenum].maxformsize-MMC.migevents[profilenum].minformsize);
//DEADCODE JIM 16/11/99 		if (GR_FormSize00>GR_FormSize03)
//DEADCODE JIM 16/11/99 			GR_FormSize00=GR_FormSize03;
//DEADCODE JIM 16/11/99 		GR_FormSize03-=GR_FormSize00;
//DEADCODE JIM 16/11/99 	}
//DEADCODE JIM 16/11/99 	GR_FormSize01=MMC.migevents[profilenum].minformsize;
//DEADCODE JIM 16/11/99 	GR_FormSize02=GR_FormSize00-GR_FormSize01;
//DEADCODE JIM 16/11/99 	GR_Scram_Squad[0]=squad;
//DEADCODE JIM 16/11/99 	Persons2::SetLoc(SGR_Pack_Takeoff,takeoff);
//DEADCODE JIM 16/11/99 	Persons2::SetLoc(SGR_Pack_Target,packtarg);						  //DAW 13/04/99
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 	//also need to set:
//DEADCODE JIM 16/11/99 	//		Wp0,Wp1			=patrol area			for Decoy and MigCap
//DEADCODE JIM 16/11/99 	GR_WP1=blueswmigcap;
//DEADCODE JIM 16/11/99 	GR_WP2=bluenemigcap;
//DEADCODE JIM 16/11/99 	//		RangeStepSize 	=distance from takeoff	for Direct
//DEADCODE JIM 16/11/99 	//		Pack_TakeTime	=time to takeoff		for MigCap 	
//DEADCODE JIM 16/11/99 	//
//DEADCODE JIM 16/11/99 	GR_Pack_TakeTime[0][0]=0;
//DEADCODE JIM 16/11/99 	GR_RangeStepSize=0;
//DEADCODE JIM 16/11/99 	if (MMC.migevents[profilenum].takeofftime && migcaptime)
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99 		int	rnddeltatime=Math_Lib.rnd(5)*30-60;
//DEADCODE JIM 16/11/99 		GR_Pack_TakeTime[0][0]=migcaptime+MMC.migevents[profilenum].takeofftime+rnddeltatime;
//DEADCODE JIM 16/11/99 	}
//DEADCODE JIM 16/11/99 	else
//DEADCODE JIM 16/11/99 	if (range<0)
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99 		GR_Pack_TakeTime[0][0]=-range/METRES240;
//DEADCODE JIM 16/11/99 		GR_movecode=AUTO_TAKEOFF;
//DEADCODE JIM 16/11/99 	}
//DEADCODE JIM 16/11/99 	else
//DEADCODE JIM 16/11/99 		GR_RangeStepSize=range;
//DEADCODE JIM 16/11/99 	rv=MMC.migevents[profilenum].eventbf;
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 
//DEADCODE RJS 15/02/00 	return rv;
//DEADCODE RJS 15/02/00 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchConvoy
//Author		R. Hyde 
//Date			Fri 9 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Persons2::LaunchConvoy(FileNum bfield,SWord size)


{
//DeadCode RDH 24Feb97 	SWord i = 0,j,k=0;
	Bool	repeatuid,retval = FALSE;
//DeadCode RDH 24Feb97 	SWord	uidcount;
//DeadCode RDH 24Feb97 
//DeadCode RDH 24Feb97 //TempCode RDH 09Aug96 if (hq and relevant tanksite not dead) *****
//DeadCode RDH 24Feb97 //TempCode RDH 09Aug96 {	
//DeadCode RDH 24Feb97 	while (i < MAXCONVOYS)
//DeadCode RDH 24Feb97 	{
//DeadCode RDH 24Feb97 		breakif ( Miss_Man.camp.convoys[i].size == 0);
//DeadCode RDH 24Feb97 		i++;
//DeadCode RDH 24Feb97 	}
//DeadCode RDH 24Feb97 	if (i != MAXCONVOYS)
//DeadCode RDH 24Feb97 	{//set uid to first wp of a route
//DeadCode RDH 24Feb97 			uidcount = 	Math_Lib.rnd(MAXROUTES);
//DeadCode RDH 24Feb97 			uidcount--;
//DeadCode RDH 24Feb97 			// avoid two convoys on same start	
//DeadCode RDH 24Feb97 			do
//DeadCode RDH 24Feb97 			{
//DeadCode RDH 24Feb97 				repeatuid = FALSE;
//DeadCode RDH 24Feb97 				uidcount++;
//DeadCode RDH 24Feb97 				k++;
//DeadCode RDH 24Feb97 				if (uidcount >= MAXROUTES)
//DeadCode RDH 24Feb97 					uidcount =0;
//DeadCode RDH 24Feb97 				j = 0;
//DeadCode RDH 24Feb97 				while ((j < MAXCONVOYS) && (repeatuid == FALSE))
//DeadCode RDH 24Feb97 				{
//DeadCode RDH 24Feb97 					if ( Miss_Man.camp.routesstartuids[uidcount]
//DeadCode RDH 24Feb97 							==	Miss_Man.camp.convoys[j].uid)
//DeadCode RDH 24Feb97 						repeatuid = TRUE;
//DeadCode RDH 24Feb97 					j++;
//DeadCode RDH 24Feb97 				}
//DeadCode RDH 24Feb97 			}while ((repeatuid == TRUE) && k <= MAXROUTES);
//DeadCode RDH 24Feb97 
//DeadCode RDH 24Feb97 			if (k <= MAXROUTES)
//DeadCode RDH 24Feb97 			{
//DeadCode RDH 24Feb97 				Miss_Man.camp.convoys[i].uid = Miss_Man.camp.routesstartuids[uidcount];
//DeadCode RDH 24Feb97 				Miss_Man.camp.convoys[i].bfield = bfield;
//DeadCode RDH 24Feb97 				Miss_Man.camp.convoys[i].size = size;
//DeadCode RDH 24Feb97 				retval = TRUE;
//DeadCode RDH 24Feb97 			}		
//DeadCode RDH 24Feb97 	}
	return (retval);
//DeadCode RDH 24Feb97 //TempCode RDH 09Aug96 }
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTankConvoy
//Author		R. Hyde 
//Date			Fri 9 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons2::LaunchTankConvoy ()
{
//DeadCode RDH 14Jan97 	SWord i = 0,j=0,k;
//DeadCode RDH 14Jan97 	while (	(Miss_Man.camp.Tank_timer > 0)
//DeadCode RDH 14Jan97 		&&	(j < MAXTANKCONVOYS)
//DeadCode RDH 14Jan97 			)
//DeadCode RDH 14Jan97 	{
//DeadCode RDH 14Jan97 		i = 0;
//DeadCode RDH 14Jan97 		while (i < MAXCONVOYS)
//DeadCode RDH 14Jan97 		{
//DeadCode RDH 14Jan97 			if (	( Miss_Man.camp.convoys[i].size != 0)
//DeadCode RDH 14Jan97 			&&	(Miss_Man.camp.convoys[i].bfield == BFTANKSET)
//DeadCode RDH 14Jan97 				)
//DeadCode RDH 14Jan97 				j++;
//DeadCode RDH 14Jan97 			i++;
//DeadCode RDH 14Jan97 		}
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 		if (j < MAXTANKCONVOYS)
//DeadCode RDH 14Jan97 		{
//DeadCode RDH 14Jan97 			k=0;
//DeadCode RDH 14Jan97 			if (Persons_2.ItemStatus(UID_AlTdHavrincourtWd).deadtime == 0)
//DeadCode RDH 14Jan97 				k+=4;
//DeadCode RDH 14Jan97 			if (Persons_2.ItemStatus(UID_AlTdTrescault).deadtime == 0)
//DeadCode RDH 14Jan97 				k+=4;
//DeadCode RDH 14Jan97 			if (	(k == 8)
//DeadCode RDH 14Jan97 				||  (Math_Lib.rnd(k) > 2)
//DeadCode RDH 14Jan97 				)
//DeadCode RDH 14Jan97 			{
//DeadCode RDH 14Jan97 //DeadCode RDH 11Dec96 				if (LaunchConvoy(BFTANKSET,4))
//DeadCode RDH 14Jan97 //DeadCode RDH 11Dec96 				{
//DeadCode RDH 14Jan97 //DeadCode RDH 11Dec96 					Miss_Man.camp.Tank_timer -= INTERVAL_BETWEEN_TANK_LAUNCHES;
//DeadCode RDH 14Jan97 //DeadCode RDH 11Dec96 					Miss_Man.camp.Tank_timer -= Math_Lib.rnd(SECSPERHR/2);
//DeadCode RDH 14Jan97 //DeadCode RDH 11Dec96 				}
//DeadCode RDH 14Jan97 				LaunchConvoy(BFTANKSET,4);						//RDH 11Dec96
//DeadCode RDH 14Jan97 			}													//RDH 11Dec96
//DeadCode RDH 14Jan97 			Miss_Man.camp.Tank_timer -= INTERVAL_BETWEEN_TANK_LAUNCHES;//RDH 11Dec96
//DeadCode RDH 14Jan97 			Miss_Man.camp.Tank_timer -= Math_Lib.rnd(SECSPERHR/2);//RDH 11Dec96
//DeadCode RDH 14Jan97 		}
//DeadCode RDH 14Jan97 	}
//DeadCode RDH 14Jan97 
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTruckConvoyTest
//Author		Jim Taylor
//Date			Thu 17 Oct 1996
//
//Description	
//if gun killed this time launch a truck
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons2::LaunchTruckConvoyTest ()
{

//DeadCode RDH 24Feb97 	UniqueID	tmpUID,EndBand;
//DeadCode RDH 24Feb97 	tmpUID  = RedMilitaryBAND;
//DeadCode RDH 24Feb97 	ItemBasePtr		tmpitem;
//DeadCode RDH 24Feb97 	EndBand = BlueMilitaryBAND;
//DeadCode RDH 24Feb97 	Bool	Launchtruck = TRUE;
//DeadCode RDH 24Feb97 
//DeadCode RDH 24Feb97  while (	(Miss_Man.camp.Tank_timer > 0)
//DeadCode RDH 24Feb97 			&& (Launchtruck == TRUE)
//DeadCode RDH 24Feb97 		)
//DeadCode RDH 24Feb97  { 
//DeadCode RDH 24Feb97 	Launchtruck = FALSE;
//DeadCode RDH 24Feb97 
//DeadCode RDH 24Feb97 	while (	(tmpUID < EndBand)
//DeadCode RDH 24Feb97 			&&	(Launchtruck == FALSE)
//DeadCode RDH 24Feb97 				)
//DeadCode RDH 24Feb97 	{
//DeadCode RDH 24Feb97 		tmpitem=Persons_2.ConvertPtrUID(tmpUID);
//DeadCode RDH 24Feb97 		if (	(tmpitem)
//DeadCode RDH 24Feb97 			&&	(tmpitem->Status.deadtime >= 7)		//temp
//DeadCode RDH 24Feb97 			)
//DeadCode RDH 24Feb97 			Launchtruck = TRUE;
//DeadCode RDH 24Feb97 		tmpUID++;
//DeadCode RDH 24Feb97 
//DeadCode RDH 24Feb97 	}
//DeadCode RDH 24Feb97 	if (	(Launchtruck)
//DeadCode RDH 24Feb97 		&&(tmpUID < EndBand)									//RDH 16Dec96
//DeadCode RDH 24Feb97 		)														//RDH 16Dec96
//DeadCode RDH 24Feb97 			Launchtruck = Persons_2.LaunchTruckConvoy();		//RDH 16Dec96
//DeadCode RDH 24Feb97  }
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTruckConvoy
//Author		R. Hyde 
//Date			Fri 9 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Persons2::LaunchTruckConvoy ()
{
//DeadCode JIM 20Oct00 	SWord i = 0,j=0,k;
	Bool	retval = FALSE;
//DeadCode RDH 14Jan97 	if (Miss_Man.camp.Truck_timer > 0)
//DeadCode RDH 14Jan97 	{
//DeadCode RDH 14Jan97 		i = 0;
//DeadCode RDH 14Jan97 		while (i < MAXCONVOYS)
//DeadCode RDH 14Jan97 		{
//DeadCode RDH 14Jan97 			if (	( Miss_Man.camp.convoys[i].size != 0)
//DeadCode RDH 14Jan97 			&&	(Miss_Man.camp.convoys[i].bfield == BFTRUCKSET)
//DeadCode RDH 14Jan97 				)
//DeadCode RDH 14Jan97 				j++;
//DeadCode RDH 14Jan97 			i++;
//DeadCode RDH 14Jan97 		}
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 		if (j < MAXTRUCKCONVOYS)
//DeadCode RDH 14Jan97 		{
//DeadCode RDH 14Jan97 			k=0;
//DeadCode RDH 14Jan97 			if (Persons_2.ItemStatus(UID_AlTdHavrincourtWd).deadtime == 0)
//DeadCode RDH 14Jan97 				k+=4;
//DeadCode RDH 14Jan97 			if (Persons_2.ItemStatus(UID_AlTdTrescault).deadtime == 0)
//DeadCode RDH 14Jan97 				k+=4;
//DeadCode RDH 14Jan97 			if (	(k == 8)
//DeadCode RDH 14Jan97 				||  (Math_Lib.rnd(k) > 2)
//DeadCode RDH 14Jan97 				)
//DeadCode RDH 14Jan97 			{
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 				if (LaunchConvoy(BFTRUCKSET,1))
//DeadCode RDH 14Jan97 				{
//DeadCode RDH 14Jan97 					Miss_Man.camp.Truck_timer -= INTERVAL_BETWEEN_TRUCK_LAUNCHES;
//DeadCode RDH 14Jan97 					Miss_Man.camp.Truck_timer -= Math_Lib.rnd(SECSPERHR);
//DeadCode RDH 14Jan97 					retval = TRUE;
//DeadCode RDH 14Jan97 				}
//DeadCode RDH 14Jan97 			}
//DeadCode RDH 14Jan97 	}	}
	return (retval);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TankEndMission
//Author		R. Hyde 
//Date			Fri 9 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons2::TankEndMission()
{
//DeadCode RDH 14Jan97 	SWord	i,j;
//DeadCode RDH 14Jan97 	ItemBasePtr		tmpitem;
//DeadCode RDH 14Jan97 	Bool	finishuid;
//DeadCode RDH 14Jan97 		ITEM_STATUS trgstat;
//DeadCode RDH 14Jan97 		UniqueIDBand	uidband;
//DeadCode RDH 14Jan97 		UniqueID	nwptrg;
//DeadCode RDH 14Jan97 		SLong		size=0;
//DeadCode RDH 14Jan97 		Bool	inlist = FALSE;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 //moved to scoring.cpp											//RDH 13Oct96
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 //deal with blue ac
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 //DeadCode JIM 11Oct96 	tmpitem=Persons_2.ConvertPtrUID(UID_AlAfHermies);
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 	if (Persons_2.ItemStatus(UID_AlAfHermies).deadtime != 0)	//JIM 11Oct96
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 		MMC.blueacflying = -1;
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 	MMC.blueacflying++;
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 	if (MMC.blueacflying > 4)
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 		MMC.blueacflying = 4;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 //get info about convoys back from 3d
//DeadCode RDH 14Jan97 	for (i=0;i<MAXCONVOYS;i++)
//DeadCode RDH 14Jan97 	{
//DeadCode RDH 14Jan97 		size=0;
//DeadCode RDH 14Jan97 		inlist = FALSE;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 		if (MMC.convoys[i].size)
//DeadCode RDH 14Jan97 		{
//DeadCode RDH 14Jan97 			trgstat=ConvoyStatus(MMC.convoys[i].uid,MMC.convoys[i].uid,nwptrg,size);
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 			//put gun into bluegun list when truck arrives
//DeadCode RDH 14Jan97 			if (Miss_Man.camp.convoys[i].bfield == BFTRUCKSET)
//DeadCode RDH 14Jan97 			{
//DeadCode RDH 14Jan97 				if (	(trgstat.deadtime != 0)					//JIM 13Dec96
//DeadCode RDH 14Jan97 				 	&&	(Miss_Man.camp.playerbfield != FIL_NULL)	//JIM 13Dec96
//DeadCode RDH 14Jan97 					)											//JIM 13Dec96
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 				{
//DeadCode RDH 14Jan97 					size = 0;
//DeadCode RDH 14Jan97 					j = 0;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 					while 	(j < MAXGUNS)
//DeadCode RDH 14Jan97 					{
//DeadCode RDH 14Jan97 						if (Miss_Man.camp.blueguns[j] == nwptrg)
//DeadCode RDH 14Jan97 							   inlist = TRUE;
//DeadCode RDH 14Jan97 						j++;
//DeadCode RDH 14Jan97 					}
//DeadCode RDH 14Jan97 					if (!(inlist))
//DeadCode RDH 14Jan97 					{
//DeadCode RDH 14Jan97 						j = 0;
//DeadCode RDH 14Jan97 						while (((Miss_Man.camp.blueguns[j]) !=UID_Null)
//DeadCode RDH 14Jan97 							 &&	(j < MAXGUNS)
//DeadCode RDH 14Jan97 							)
//DeadCode RDH 14Jan97 							j++;
//DeadCode RDH 14Jan97 						if (j < MAXGUNS)
//DeadCode RDH 14Jan97 							Miss_Man.camp.blueguns[j] = nwptrg;
//DeadCode RDH 14Jan97 					}
//DeadCode RDH 14Jan97 				}
//DeadCode RDH 14Jan97 			}
//DeadCode RDH 14Jan97 			uidband = Persons_2.getbandfromUID((UniqueID) nwptrg);
//DeadCode RDH 14Jan97 			if (uidband == RedCivilianBAND)
//DeadCode RDH 14Jan97 			{
//DeadCode RDH 14Jan97  				if (trgstat.deadtime == 0 )
//DeadCode RDH 14Jan97 					MMC.specialeventbits |= TANKNEARBRIDGES;
//DeadCode RDH 14Jan97 			}
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 			}else
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 			{
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 				if (Miss_Man.camp.convoys[i].bfield != BFTRUCKSET)
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 				{//kill gun that has been passed by tanks, 6 hrs	//RDH 06Dec96
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 					ItemStatus(nwptrg,SetStatus(24,0));				//RDH 06Dec96
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 																//RDH 06Dec96
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 				}
//DeadCode RDH 14Jan97 //DeadCode RDH 08Dec96 			}
//DeadCode RDH 14Jan97 			MMC.convoys[i].size=size;
//DeadCode RDH 14Jan97 		}
//DeadCode RDH 14Jan97 	}
//DeadCode RDH 14Jan97 //repairing bridges
//DeadCode RDH 14Jan97 		tmpitem=Persons_2.ConvertPtrUID(UID_BrNtNoyelles);
//DeadCode RDH 14Jan97 		if (	(tmpitem->Status.deadscale <1)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  <8)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  != 0)
//DeadCode RDH 14Jan97 			)
//DeadCode RDH 14Jan97 			MMC.specialeventbits |= TANK_BUILDPONTOONBRIDGE;
//DeadCode RDH 14Jan97 		tmpitem=Persons_2.ConvertPtrUID(UID_BrNtCantaing);
//DeadCode RDH 14Jan97 		if (	(tmpitem->Status.deadscale <1)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  <8)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  != 0)
//DeadCode RDH 14Jan97 			)
//DeadCode RDH 14Jan97 			MMC.specialeventbits |= TANK_BUILDPONTOONBRIDGE;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 		tmpitem=Persons_2.ConvertPtrUID(UID_BrNtFontaine);
//DeadCode RDH 14Jan97 		if (	(tmpitem->Status.deadscale <1)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  <8)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  != 0)
//DeadCode RDH 14Jan97 			)
//DeadCode RDH 14Jan97 			MMC.specialeventbits |= TANK_BUILDPONTOONBRIDGE;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 		tmpitem=Persons_2.ConvertPtrUID(UID_BrNtMarcoing);
//DeadCode RDH 14Jan97 		if (	(tmpitem->Status.deadscale <1)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  <8)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  != 0)
//DeadCode RDH 14Jan97 			)
//DeadCode RDH 14Jan97 			MMC.specialeventbits |= TANK_BUILDPONTOONBRIDGE;
//DeadCode RDH 14Jan97 		tmpitem=Persons_2.ConvertPtrUID(UID_BrNtMasnieres);
//DeadCode RDH 14Jan97 		if (	(tmpitem->Status.deadscale <1)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  <8)
//DeadCode RDH 14Jan97 			&& (tmpitem->Status.deadtime  != 0)
//DeadCode RDH 14Jan97 			)
//DeadCode RDH 14Jan97 			MMC.specialeventbits |= TANK_BUILDPONTOONBRIDGE;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 //is campaign lost
//DeadCode RDH 14Jan97 //if convoy.uid (waypoint at this stage == routesend wp
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 	finishuid = FALSE;
//DeadCode RDH 14Jan97 	i = 0;
//DeadCode RDH 14Jan97 	do
//DeadCode RDH 14Jan97 	{
//DeadCode RDH 14Jan97 		j = 0;
//DeadCode RDH 14Jan97 		while ((j < MAXCONVOYS) && (finishuid == FALSE))
//DeadCode RDH 14Jan97 		{
//DeadCode RDH 14Jan97 			if ( Miss_Man.camp.routesenduids[i]
//DeadCode RDH 14Jan97 						==	Miss_Man.camp.convoys[j].uid)
//DeadCode RDH 14Jan97 					finishuid = TRUE;
//DeadCode RDH 14Jan97 			j++;
//DeadCode RDH 14Jan97 		}
//DeadCode RDH 14Jan97 		i++;
//DeadCode RDH 14Jan97 	}while ((finishuid == FALSE) && (i < MAXROUTES));
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 	if (finishuid == TRUE)
//DeadCode RDH 14Jan97 		MMC.specialeventbits |= TANKCAMPAIGNLOST;
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 //if aaa site dead then associated gun goes back to being dead
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 //clear blueaaa list entry
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 	for (i =0;i<MAXGUNS;i++)
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 	{
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 		if (Miss_Man.camp.blueaaa[i] ==UID_Null)
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 		{	
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 			Miss_Man.camp.blueguns[i] = UID_Null;
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 		}
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 		Miss_Man.camp.blueaaa[i] = UID_Null;	
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 	
//DeadCode RDH 14Jan97 //DeadCode RDH 17Oct96 	}
//DeadCode RDH 14Jan97 
//DeadCode RDH 14Jan97 //moved to scoring.cpp											//RDH 13Oct96
//DeadCode RDH 14Jan97 //DeadCode RDH 13Oct96 	LaunchTankConvoy();
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		lowlevel_squadron
//Author		Jim Taylor
//Date			Wed 25 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Persons2::lowlevel_squadron(int snequ)
{
//		if (snequ>SNEQU_LASTACE)
//			if (snequ>SNEQU_SECONDSET)
//				eventloglist->home=_Text.ConvSnip0((TextList)LIST_SQUADS2,snequ-SNEQU_SECONDSET-1);
//			else
//				eventloglist->home=_Text.ConvSnip0((TextList)LIST_SQUADS,snequ-SNEQU_LASTACE-1);
//		else
//		{
//			eventloglist->home=_Text.ConvSnip0((TextList)LIST_ACESQUADS,snequ);
//			eventloglist->name=_Text.ConvSnip0((TextList)LIST_ACES,snequ);
//		}	
		return(FALSE);
}


void	Persons4::PleaseWarnUser(char* msg,char* title)
{
	//bugger off.
}


//////////////////////////////////////////////////////////////////////
//
// Function:    Post3DInfo
// Date:		24/03/00
// Author:		JIM
//
//Description: A temporary arry that holds the latest 3d position of each SAG
//
//////////////////////////////////////////////////////////////////////
struct	Post3DInfo
{
	Coords3D	position;
	UWord		waypoint;
	UWord		fuelkilos;
	UniqueID	unfriendly;
	UWord		movecode;

	Post3DInfo()	{waypoint=0xffff;}
	void		Set(AirStrucPtr a);
#ifdef	PACKAGE_INCLUDED
	int			Get(info_airgrp* a,Profile& pk,int sqnum,UniqueID route);	//returns fuel
#endif
	static		Post3DInfo*	New();
	void		Delete();

};
	enum	{MAX_SAGINVALIDATES=256};
	Post3DInfo* Persons3::post3dinfo=NULL;
//////////////////////////////////////////////////////////////////////
//
// Function:    Post3DInfo::Set
// Date:		24/03/00
// Author:		JIM
//
//Description:	Fill this structure with data from the airstruc
//
//	Coords3D	position;
//	UWord		waypoint;
//	UWord		fuelkilos;

//////////////////////////////////////////////////////////////////////
void		Post3DInfo::Set(AirStrucPtr a)
{
	position=a->World;
	WayPointPtr w=a->waypoint;	//->prev;						//MS 17Nov100
	int c=1000;
	if (w)
		for (c=-1;w;c++)
			w=w->prev;
	waypoint=c;
	fuelkilos=(a->fly.fuel_content[0]+a->fly.fuel_content[1]+a->fly.fuel_content[2]+a->fly.fuel_content[3])/100000;
	if (a->fly.expandedsag)
		movecode=a->fly.expandedsag->movecode;
	else
		movecode=a->movecode;
	ItemPtr	u=NULL;
	if (a->ai.unfriendly)
		u=a->ai.unfriendly;
	else
		if (a->fly.expandedsag && a->fly.expandedsag->ai.unfriendly)
			u=a->fly.expandedsag->ai.unfriendly;
	if (u && u->Status.size<AIRSTRUCSIZE)
		u=NULL;
	if (u && AirStrucPtr(u)->fly.expandedsag && AirStrucPtr(u)->fly.numinsag==0)
		u=AirStrucPtr(u)->fly.expandedsag;
	if (u)
		unfriendly=u->uniqueID.count;
	else
		unfriendly=UID_NULL;




}
//////////////////////////////////////////////////////////////////////
//
// Function:    Post3DInfo::Get
// Date:		24/03/00
// Author:		JIM
//
//Description: Copy data from this structure to the airgrp
//
//////////////////////////////////////////////////////////////////////
int		Post3DInfo::Get(info_airgrp* a,Profile& pack,int sqnum,UniqueID route)
{
	if (waypoint==0xffff)
		return 0;
	Profile::Squad* sq=&pack[sqnum];
	int rv=sq->numacleft;
	a->knownposition=
		a->World=
			position;
	a->position.MakeAbsWorldPos(a->World.Y);
	a->position[0][0]=a->World.X;
	a->position[0][2]=a->World.Z;

	bool	passedip=false;
	for (int c=waypoint;c;c--)
	{
		info_waypoint* w=Persons2::ConvertPtrUID(route);
		if (w->nextwp == UID_Null)										//RJS 15Nov00
			break;
		else
		{
			route=w->nextwp;
			if (w->uid.Evaluate()==-SGR_WPP_Egress)
				passedip=true;
		}
	}
	a->movecode=movecode;
	//generate status from movecode:
	switch (movecode)
	{
	case	AUTOSAG_WAITTAKEOFF:	sq->status=Profile::PS_PLANNED;		return 0;	
	case	AUTOSAG_TAKEOFF:		sq->status=Profile::PS_TAKINGOFF;	return 0;
	case	AUTOSAG_FOLLOWWP:
	case	AUTOSAG_FOLLOWWPHOME:
		if (passedip)				sq->status=Profile::PS_OUTGOING;
		else						sq->status=Profile::PS_INCOMING;	break;
	case	AUTOSAG_LANDING:		sq->status=Profile::PS_LANDING;		break;
	case	AUTOSAG_REFUELLING:		sq->status=Profile::PS_REFUELLING;	break;
	case	AUTOSAG_PRECOMBAT:		sq->status=Profile::PS_ENEMYSIGHTED;break;
	case	AUTOSAG_COMBAT:			sq->status=Profile::PS_ENEMYSIGHTED;break;
	case	AUTOSAG_COMBATCIRCLES:	sq->status=Profile::PS_ENEMYSIGHTED;break;
	case	AUTOSAG_POSTCOMBAT:		sq->status=Profile::PS_ENEMYSIGHTED;break;
	case	AUTOSAG_BOMBAPPROACH:	sq->status=Profile::PS_TARGETAREA;	break;
	case	AUTOSAG_BOMB:			sq->status=Profile::PS_TARGETAREA;	break;
//DeadCode JIM 3Aug00 	case	AUTOSAG_TRACKEXPFOLLOW:	sq->status=PS_TAKINGOFF;	break;
//DeadCode JIM 3Aug00 	case	AUTOSAG_TRACKEXPCOMBAT:	sq->status=PS_TAKINGOFF;	break;

	case	AUTOSAG_DEATHGLIDE:
	case	AUTOSAG_DESTROYED:		
	{
		pack.SquadComplete(sqnum);	//Apply devastating losses if squad wiped out...	
		if (sq->numacleft>0)
		{
// Update Note log...
			int	numacleft = sq->numacleft;								//RJS 12Nov00

			MMC.thisweekreview.Note(sq->Squadron().AcType(),PeriodReview::DESTROY,numacleft / 2);

			numacleft -= (numacleft / 2);								//RJS 12Nov00

			sq->numacditched+=sq->numacleft;
			sq->numacrecoveredmed+=numacleft/2;							//RJS 12Nov00

			MMC.thisweekreview.Note(sq->Squadron().AcType(),PeriodReview::DAMAGE,numacleft / 2);

			numacleft -= (numacleft / 2);

			sq->numacrecoveredbad+=numacleft;							//RJS 12Nov00
			
			MMC.thisweekreview.Note(sq->Squadron().AcType(),PeriodReview::DESTROY,numacleft);

			sq->numpilotslost+=numacleft;								//RJS 12Nov00
			rv=- (int)sq->numacleft;
			sq->numacleft=0;
		}
	}
	break;

	case	AUTOSAG_LAST:			sq->status=Profile::PS_COMPLETE;	break;




	default: INT3;
	}
	a->wpref=route;
	a->target=unfriendly;
	sq->fuelleft=fuelkilos*100000;	
	return rv;	
}



//////////////////////////////////////////////////////////////////////
//
// Function:    Post3DInfo::New
// Date:		24/03/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
Post3DInfo*	Post3DInfo::New()
{
	return	new Post3DInfo[MAX_SAGINVALIDATES];
}
//////////////////////////////////////////////////////////////////////
//
// Function:    Post3DInfo::Delete
// Date:		24/03/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void		Post3DInfo::Delete()
{
	delete	[]	this;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SaveAircraftPositions
// Date:		24/03/00
// Author:		JIM
//
//Description: Saves aircraft position info in the 3d before 3d exits
//	For each SAG 
//			post3dinfo entry is filled
//	For each convoy leader
//			nodedata is filled
//
//////////////////////////////////////////////////////////////////////
void	Persons3::SaveAircraftPositions(Inst3d* inst3d)
{
	if (post3dinfo)
		post3dinfo->Delete();
	FormationItemPtr m;
	GR_TakeOffTime=inst3d->timeofday/100;
	post3dinfo=post3dinfo->New();
	{for (int i=SagBAND,j=0;i<SagBANDEND;i++,j++)
		if ((m=ConvertPtrUID(UniqueID(i)))!=NULL)
		{
			AirStrucPtr a=*m;
			post3dinfo[j].Set(a);
	}	}
	{for (int i=BritBoatBAND;i<PowerStationBAND;i++)
		if ((m=ConvertPtrUID(UniqueID(i)))!=NULL)
		{
			UniqueID u=UniqueID(i);
			if (m->SGT)
				u=m->SGT;
			TargetConvoy* convoy=Node_Data[u];
			if (convoy)
			{
				if (m->leader==NULL)
				{
					convoy->X=m->World.X;
					convoy->Z=m->World.Z;
					WayPointPtr w=m->waypoint;
					int c=100;
					if (w)
						for (c=-1;w;c++)
							w=w->prev;
					convoy->wpnum=c;
				}
				if (m->Status.deadtime)
					if (convoy->truestatus<100)
					{
						convoy->truestatus+=13-convoy->truestatus/8;	//RJS 31Oct00
					}
				convoy->knownstatus=convoy->truestatus;
			}
	}	}
	Dead_Stream.SetWorldDead(inst3d->world);
}
//////////////////////////////////////////////////////////////////////
//
// Function:    RestoreAircraftPositions
// Date:		24/03/00
// Author:		JIM
//
//Description: Restores the aircraft position info onto the map screen
//
//////////////////////////////////////////////////////////////////////
void	Persons3::RestoreAircraftPositions()
{
//DeadCode CSB 11Sep00 	Mono_Text.Print((UByteP)"Restore<");
	if (post3dinfo)
	{	UniqueID instuid;
		Profile::Squad* sq;
		MMC.currtime=GR_TakeOffTime;									//DAW 7Aug00
		for (int p=0;p<Profile::MAX_PACKS;p++)
		{
			int s=0,smax=Todays_Packages[p].squadlist;
			for (;s<smax;s++)
			{
				if ((instuid=Todays_Packages[p][s].instance)!=UID_NULL)
					if (post3dinfo[instuid-SagBAND].Get(ConvertPtrUID(instuid),Todays_Packages[p],s,Todays_Packages[p].route)<0)	//indicates that aircraft were removed to zero.
					{
						Todays_Packages.ChangeMessagesUID(Todays_Packages[p][s].instance,UID_BIT14+((p)<<5)+Todays_Packages[p].GetRaidIndFromSquadEntry(s));
					}

			}
			if (smax)
			{
				Todays_Packages[p].ApplyDiaryLosses();
				Todays_Packages[p].FixPackageStatus();
			}
			else
				assert(Todays_Packages[p].packagestatus==Profile::PS_SPARE);
		}
		post3dinfo->Delete();
		post3dinfo=NULL;
	}
	Node_Data.CheckDamage(Dead_Stream);
//DeadCode CSB 11Sep00 	Mono_Text.Print((UByteP)">Restore");
}

void	Persons2::SetUpDiary()
{
// Fix-up Quick-Mission Diary Records...

	Squad_Diary.EmptyDiary();
	Squad_Diary.CreateQuickEntry(GR_Scram_Alt,GR_Scram_AC,GR_Scram_Squad,0,CSQuick1::quickdef.target);
}
