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
//Filename       replay.cpp
//Date           Wed 29 Apr 1998
//------------------------------------------------------------------------------

#include	"dosdefs.h"
#define F_GRAFIX										
#define F_BATTLE
#define F_COMMON
#undef  F_SOUNDS
#include	"files.g"
#include	<stdlib.h>
#include	"replay.h"
#include	"myerror.h"
#include	"missman2.h"
#include	"planetyp.h"
#include	"viewsel.h"
#include	"persons2.h"
#include	"winmove.h"
#include	"flymodel.h"
#include	"ai.h"
#include	"worldinc.h"
#include	"myangles.h"
#include	"3dcom.h"											
#include	"miles.h"											
#include	"world.h"											
#include	"transite.h"										
#include	"modvec.h"											
#include	"model.h"											
#include	"shapes.h"
#include	"3dcode.h"
#include	"stub3d.h"
#include	"transite.h"
#include	"areatype.h"							
#include	"..\mfc\resource.h"
#include	"savegame.h"
#include	"aaa.h"

//#define VELCHECK
//#define ITEMCOUNT
// for fuel in setflightparam purposes need multiple of 256
#define	FRAMESINBLOCK 512
#define REPLAYFRAMESPERSEC 100/Timer_Code.FRAMETIME
extern BAD_RV;

#define VELSHIFT	6


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OpenRecordLog
//Date			Wed 13 May 1998
//------------------------------------------------------------------------------
Bool	Replay::OpenRecordLog()
{
	DWORD err;

	Record=TRUE;	
	GetReplayFileName();
	Record=FALSE;

	DWORD flags=FILE_ATTRIBUTE_TEMPORARY;

// cant do overlapped io on disk files on Win95/98. Wait until Windows 2000/NT
// is the standard and check it out then!!!!

//	flags|=FILE_FLAG_OVERLAPPED;

	recordstorage=CreateFile(
		&rfilename[0],
			GENERIC_WRITE,
			FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,	// add to any file that is there
			flags,
			NULL);

// instead of deleting file, just truncate to zero 

	if (ResetFileFlag)
	{
		ResetFileFlag=false;
		SetEndOfFile(recordstorage);
	}

	if (recordstorage!=INVALID_HANDLE_VALUE)
	{
		SetFilePointer(recordstorage, 0, NULL, FILE_END); // get to end of file

		Record=TRUE;
		return TRUE;
	}

	err=GetLastError();

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CloseRecordLog
//Date			Wed 13 May 1998
//------------------------------------------------------------------------------
void	Replay::CloseRecordLog()
{
	DWORD err;

	if (recordstorage)
	{
		if (!CloseHandle(recordstorage))
			err=GetLastError();
	}

	recordstorage=NULL;

	Record=FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OpenPlaybackLog
//Date			Wed 29 Apr 1998
//------------------------------------------------------------------------------
Bool	Replay::OpenPlaybackLog()
{
	PlaybackPaused=TRUE;

	if (!RestorePosition)
	{
		Playback=TRUE;
		GetReplayFileName();
		Playback=FALSE;
	}

	playbackstorage=CreateFile(
		&pfilename[0],
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_TEMPORARY,
		NULL);

	if (playbackstorage!=INVALID_HANDLE_VALUE)
	{
		mappedplaybackfile=CreateFileMapping(
			playbackstorage,
			NULL,
			PAGE_READONLY,
			0,
			0,
			NULL);

		if (mappedplaybackfile)
		{

			playbackfilestart=MapViewOfFile(
				mappedplaybackfile,
				FILE_MAP_READ,
				0,
				0,
				0);

			if (playbackfilestart)
			{
				playbackfilepos=(UByteP)playbackfilestart;
				playbackfileend=playbackfilepos+GetFileSize(playbackstorage,NULL);

				if (!RestorePosition)
				{
					endmark.memaddress=(UByteP)playbackfileend;
				}
				Playback=TRUE;
			}
		}
	}

	return Playback;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CloseReplayLog
//Date			Wed 29 Apr 1998
//------------------------------------------------------------------------------
void	Replay::ClosePlaybackLog()
{
	DWORD err;

	if (playbackfilestart)
		if (!UnmapViewOfFile(playbackfilestart))
			err=GetLastError();

	if (mappedplaybackfile)
		if (!CloseHandle(mappedplaybackfile))
			err=GetLastError();

	if (playbackstorage)
		if (!CloseHandle(playbackstorage))
			err=GetLastError();

	playbackfilestart=NULL;
	playbackfilepos=NULL;
	playbackfileend=NULL;

	playbackstorage=NULL;
	mappedplaybackfile=NULL;

	Playback=FALSE;
	PlaybackPaused=FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreDeltas
//Date			Wed 29 Apr 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreDeltas()
{
	SLong	rval;
	UByte	shiftfactor;
	AirStrucPtr gac=Persons2::PlayerGhostAC;

	REPLAYPACKET output;
	ZeroMemory(&output,sizeof(REPLAYPACKET));

	_DPlay.MakeDeltaPacket(&output);

// apply deltas 

	shiftfactor=output.Shift;

	rval=_DPlay.GetVal(output.X,shiftfactor);
	_DPlay.Deltas.lastpos.X-=rval;
	gac->World.X+=rval;

	rval=_DPlay.GetVal(output.Y,shiftfactor);
	_DPlay.Deltas.lastpos.Y-=rval;
	gac->World.Y+=rval;

	rval=_DPlay.GetVal(output.Z,shiftfactor);
	_DPlay.Deltas.lastpos.Z-=rval;
	gac->World.Z+=rval;

	rval=_DPlay.GetVal(output.Heading,shiftfactor);
	_DPlay.Deltas.Heading.a-=rval;
	gac->hdg.a+=rval;

// rate divider is always 1 in replay

	gac->fly.dhdg=rval; ///_DPlay.RateDivider;	

	rval=_DPlay.GetVal(output.Pitch,shiftfactor);
	_DPlay.Deltas.Pitch.a-=rval;
	gac->pitch.a+=rval;

// comms and replay always set cpitch to pitch each frame

	gac->fly.cpitch=gac->pitch;		

	rval=_DPlay.GetVal(output.Roll,shiftfactor);

	_DPlay.Deltas.Roll.a-=rval;
	gac->roll.a+=rval;

	rval=_DPlay.GetVal(output.Velocity_,shiftfactor);

	SLong newvel=abs(rval)<<velshifttest;
	if (rval<0)
		newvel=-newvel;

	_DPlay.Deltas.Velocity-=newvel;
	gac->vel_+=newvel;


	UpdatePosBuffer();									
	_DPlay.CalcVels();									

// check for collision etc

	_DPlay.MakeExtraPacket(&output,TRUE);

	if (!ReplayWrite((UByte*)&output,sizeof(REPLAYPACKET)))
		return FALSE;

#ifdef DEBUGMOVE2
	FILE*fp=fopen("record.txt","at");
	fprintf(fp,"%d: %d\n",replayframecount,output.IDCode);
	fclose(fp);
#endif

	replayframecount++;

	if (replayframecount==FRAMESINBLOCK)
	{
		if (!StoreRealFrameCounts(replayframecount,0,FRAMESINBLOCK-1))
			return FALSE;

// want to begin storing new block after next movecycle

		StoreHeader=true;								
	}

// RPM update
	if (Persons2::PlayerSeenAC)
	{
		UWord	rpmleft = Persons2::PlayerSeenAC->fly.rpm;

 		rpmleft = (rpmleft * 4)/Persons2::PlayerSeenAC->classtype->maxrpm;
		if (!rpmleft && Persons2::PlayerSeenAC->fly.rpm)				
			rpmleft = 1;												

		if (rpmleft != lastRpmLeft)
		{
			lastRpmLeft = rpmleft;
			_DPlay.NewEngineRPMPacket(rpmleft);
		}
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadDeltas
//Date			Fri 15 May 1998
//------------------------------------------------------------------------------
Bool	Replay::LoadDeltas()
{
	REPLAYPACKET input;
	SLong	val;
	AirStrucPtr sac=Persons2::PlayerSeenAC;
	AirStrucPtr gac=Persons2::PlayerGhostAC;
	UByte	RecCode;

	if (emptyblock)
	{
		UByteP temp=playbackfilepos;

		DoSmokeTrailStuff=FALSE;
		if (!LoadBlockHeader())
		{
			DoSmokeTrailStuff=TRUE;
			playbackfilepos=temp;
			return FALSE;
		}
		DoSmokeTrailStuff=TRUE;
	}

	if (replayframecount>thisblockendframe)
	{
// dont want to load any frames that are after end marker in end block

		PlaybackPaused=TRUE;
		return FALSE;
	}

	if (!ReplayRead((UByte*)&input,sizeof(REPLAYPACKET)))
		return FALSE;

	val=_DPlay.GetVal(input.X,input.Shift);
	gac->World.X+=val;

	val=_DPlay.GetVal(input.Y,input.Shift);
	gac->World.Y+=val;

	val=_DPlay.GetVal(input.Z,input.Shift);
	gac->World.Z+=val;

	val=_DPlay.GetVal(input.Heading,input.Shift);
	gac->hdg.a+=val;

// rate divider is always 1 in replay

	gac->fly.dhdg=val; ///_DPlay.RateDivider;			

	val=_DPlay.GetVal(input.Pitch,input.Shift);
	gac->pitch.a+=val;

	val=_DPlay.GetVal(input.Roll,input.Shift);

	gac->roll.a+=val;

	gac->fly.cpitch=gac->pitch;		

	val=_DPlay.GetVal(input.Velocity_,input.Shift);

	SLong newvel=abs(val)<<velshifttest;
	if (val<0)
		newvel=-newvel;

	gac->vel_+=newvel;

	if (sac->fly.pModel)				
	{
		sac->fly.pModel->Pos.y=gac->World.Y;	//Set to allow contrails to appear

//This is so CalcLauncherVel will work...

		sac->fly.pModel->replay_pitch = gac->pitch.a;	
		sac->fly.pModel->replay_hdg = gac->hdg.a;		
		sac->fly.pModel->replay_roll = gac->roll.a;	

// set up old vals so that view does not stutter in replay

		Three_Dee.viewer_oldhdg=gac->hdg;
		Three_Dee.viewer_oldpitch=gac->pitch;
		Three_Dee.viewer_oldroll=gac->roll;

//not sure why this is set up, must be a reason

		if (gac->World.Y < HIGHESTGROUND)		
			sac->fly.pModel->GroundHeight = Land_Scape.GetGroundLevel(gac);
		else
			sac->fly.pModel->GroundHeight = 0;
	}

	UpdatePosBuffer();									
	_DPlay.CalcVels();									

// update seenac vels from ghostac vels for rocket launches etc

	sac->vel_x=gac->vel_x;//*10;
	sac->vel_y=gac->vel_y;//*10;
	sac->vel_z=gac->vel_z;//*10;

	Persons2::PlayerSeenAC->uniqueID.changed = FALSE;

	_DPlay.ProcessExtraPacket((LPACPACKET)&input, Persons2::PlayerSeenAC, 0);

	switch (ReplayDeathMode)								
	{
		case RDEATH_SKID:
			DummyCrashSkid();
			break;
		case RDEATH_ROLL:
			DummyCrashRoll();
			break;
		case RDEATH_DIVE:
			DummyCrashDive();
			break;
	}												

#ifdef DEBUGMOVE2
	FILE*fp=fopen("playback.txt","at");
	fprintf(fp,"%d: %d\n",replayframecount,input.IDCode);
	fclose(fp);
#endif

	replayframecount++;

	if (replayframecount>numframes[currblock-1]-1)
	{
		LoadHeader=true;
	}
	else
	{
		if (replayframecount>thisblockendframe)
		{
// only one block will have dud frames at end and that is end block, so just pause!

			PlaybackPaused=TRUE;
			return FALSE;
		}
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteReplayLog
//Date			Tue 5 May 1998
//------------------------------------------------------------------------------
void	Replay::DeleteReplayLog()
{
// just truncate to zero

	ResetFileFlag=true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreRandomList
//Date			Mon 18 May 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreRandomList()
{
	UWord RndPacket [RNDPACKETSIZE],n;
	
	for (n=0; n<(RNDPACKETSIZE - 2); n++)
		RndPacket[n] = Math_Lib.GetRndLookUp(n);

	RndPacket[(RNDPACKETSIZE - 2)] = Math_Lib.Getbval();
	RndPacket[(RNDPACKETSIZE - 1)] = Math_Lib.Getcval();

	if (!ReplayWrite((UByte*)&RndPacket,RNDPACKETSIZE*sizeof(UWord)))
		return FALSE;

	Math_Lib.ResetRndCount();

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadRandomList
//Date			Mon 18 May 1998
//------------------------------------------------------------------------------
Bool	Replay::LoadRandomList()
{
	UWord RndPacket [RNDPACKETSIZE],n;
	
	if (!ReplayRead((UByte*)&RndPacket,RNDPACKETSIZE*sizeof(UWord)))
		return FALSE;

	for (n=0; n<(RNDPACKETSIZE - 2); n++)
		Math_Lib.SetRndLookUp(n,RndPacket[n]);

	Math_Lib.Setbval(RndPacket[(RNDPACKETSIZE - 2)]);
	Math_Lib.Setcval(RndPacket[(RNDPACKETSIZE - 1)]);

	Math_Lib.ResetRndCount();

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadGlobalRefs
//Date			Tue 19 May 1998
//Description	Read in header bit for next 8 GR's in BFieldGlobalTable. If bit
//				in header is set then values following header will be for those
//				values, otherwise 0.
//------------------------------------------------------------------------------
Bool	Replay::LoadInitialGlobRefs()
{
// load Pack_PlayerSquad and Pack_PlayerPos

	if (!ReplayRead((UByte*)&PlayerSquad,sizeof(int)))
		return FALSE;

	if (!ReplayRead((UByte*)&PlayerPos,sizeof(int)))
		return FALSE;

	DeleteGRList(initgrlist);

	if (!LoadGlobRefList(initgrlist))
		return FALSE;

	SetGlobRefs(initgrlist);

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadGlobRefList
//Date			Tue 15 Sep 1998
//------------------------------------------------------------------------------
Bool	Replay::LoadGlobRefList(LPREPGRENTRY& list)
{
	int val,m;
	UByte set;
	Bool	finished=FALSE;

	while (!finished)
	{
		if (!ReplayRead((UByte*)&set,sizeof(UByte)))
			return FALSE;

// first byte read in is a bit field saying which (if any) of the next 8 values
// have values stored for them, represented by bit set, and which are 0, bit=0

		for (m=0;m<8;m++)
		{
			LPREPGRENTRY temp=new REPGRENTRY;
			temp->next=NULL;

			if (set&0x1<<m)
			{
// bit set, load value for this GR

				if (!ReplayRead((UByte*)&val,sizeof(int)))
					return FALSE;

				temp->val=val;

				if (val==BAD_RV)
				{
					finished=TRUE;
				}
			}
			else
			{
// bit not set, this GR=0

				temp->val=0;
			}

// add new GR to list, put at end

			if (list)
			{
				LPREPGRENTRY temp2=list;

				while (temp2->next)
					temp2=temp2->next;

				temp2->next=temp;
			}
			else
			{
				list=temp;
			}
			temp=NULL;

			if (finished)
				break;
		}
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreDeadItems
//Date			Thu 28 May 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreDeadItems()
{
	DeadStream::DeadBlock* block=NULL;

	WorldStuff &world = mobileitem::GetWorld();

	Replay_Dead_Stream.ClrWorldDead();

	Replay_Dead_Stream.SetWorldDead(&world);

	block=Replay_Dead_Stream.firstblock;

	if (!ReplayWrite((UByte*)&Replay_Dead_Stream.olddaytime,sizeof(int)))
		return FALSE;

	while (block)
	{
// last entry in deadstream list has uniqueID=UID_Null

// valid dead item

		if (!ReplayWrite((UByte*)&(block->SGT),sizeof(UWord)))
			return FALSE;

		if (!ReplayWrite((UByte*)&(block->dataused),sizeof(UWord)))
			return FALSE;

		if (!ReplayWrite((UByte*)&(block->data),block->dataused))
			return FALSE;

		block=block->nextblock;
	}

// use IllegalSepID to indicate end of list

	UWord enduid=IllegalSepID;

	if (!ReplayWrite((UByte*)&enduid,sizeof(UWord)))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadDeadItems
//Date			Thu 28 May 1998
//------------------------------------------------------------------------------
Bool	Replay::LoadDeadItems()
{
// construct a deadstream struc 

	WorldStuff &world = mobileitem::GetWorld();
	Bool	end=FALSE;
	UniqueID	uid;
	UWord		fake;

	Dead_Stream.ClrWorldDead();

	if (!ReplayRead((UByte*)&Dead_Stream.olddaytime,sizeof(int)))
		return FALSE;

	while (!end)
	{
		if (!ReplayRead((UByte*)&fake,sizeof(UWord)))
			return FALSE;

		uid=(UniqueID)fake;

		if (uid==IllegalSepID)
			break;

		DeadStream::DeadBlock* block=new DeadStream::DeadBlock;

		block->SGT=uid;

		if (!ReplayRead((UByte*)&(block->dataused),sizeof(UWord)))
			return FALSE;

		if (!ReplayRead((UByte*)&(block->data),block->dataused))
			return FALSE;

		block->nextblock=NULL;

// add block to list

		if (Dead_Stream.firstblock)
		{
			DeadStream::DeadBlock* tblock=Dead_Stream.firstblock;

			while (tblock->nextblock)
			{
				tblock=tblock->nextblock;
			}
			tblock->nextblock=block;
			block=NULL;
			tblock=NULL;
		}
		else
		{
			Dead_Stream.firstblock=block;
			block=NULL;
		}
	}

	if (!prescan)
		Dead_Stream.GetWorldDead(&world);

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateGhostAC
//Date			Thu 28 May 1998
//------------------------------------------------------------------------------
void	Replay::UpdateGhostAC()
{
	UByte	shiftfactor=_DPlay.MakeShiftValue();
	UByte	val;
	SLong	rval;
	AirStrucPtr gac=Persons2::PlayerGhostAC;


	REPLAYPACKET output;

	output.Shift=shiftfactor;
	output.IDCode=DPlay::PIDC_EMPTY;

#define MAKEDELTAS(src,dest,shift)	  \
	{								   \
		val=(abs(src))>>shift;			\
		if (val!=0 && src<0)			 \
		{								  \
			val|=128;					   \
		}									\
		dest=val;							 \
	}

	MAKEDELTAS(_DPlay.Deltas.lastpos.X,output.X,shiftfactor);
	MAKEDELTAS(_DPlay.Deltas.lastpos.Y,output.Y,shiftfactor);
	MAKEDELTAS(_DPlay.Deltas.lastpos.Z,output.Z,shiftfactor);
	MAKEDELTAS(_DPlay.Deltas.Heading.a,output.Heading,shiftfactor);
	MAKEDELTAS(_DPlay.Deltas.Pitch.a,output.Pitch,shiftfactor);
	MAKEDELTAS(_DPlay.Deltas.Roll.a,output.Roll,shiftfactor);

	MAKEDELTAS((_DPlay.Deltas.Velocity>>_Replay.velshifttest),output.Velocity_,shiftfactor);

	rval=_DPlay.GetVal(output.X,shiftfactor);
	_DPlay.Deltas.lastpos.X-=rval;
	gac->World.X+=rval;

	rval=_DPlay.GetVal(output.Y,shiftfactor);
	_DPlay.Deltas.lastpos.Y-=rval;
	gac->World.Y+=rval;

	rval=_DPlay.GetVal(output.Z,shiftfactor);
	_DPlay.Deltas.lastpos.Z-=rval;
	gac->World.Z+=rval;

	rval=_DPlay.GetVal(output.Heading,shiftfactor);
  	_DPlay.Deltas.Heading.a-=rval;
	gac->hdg+=rval;

	gac->fly.dhdg=rval;											

	rval=_DPlay.GetVal(output.Pitch,shiftfactor);
	_DPlay.Deltas.Pitch.a-=rval;
	gac->pitch+=rval;
	gac->fly.cpitch=gac->pitch;				

	rval=_DPlay.GetVal(output.Roll,shiftfactor);

	_DPlay.Deltas.Roll.a-=rval;
	gac->roll+=rval;


	rval=_DPlay.GetVal(output.Velocity_,shiftfactor);

	SLong newvel=abs(rval)<<velshifttest;
	if (rval<0)
		newvel=-newvel;

	_DPlay.Deltas.Velocity-=newvel;
	gac->vel_+=newvel;



	UpdatePosBuffer();									
	_DPlay.CalcVels();									

#ifdef VELCHECK
	AirStrucPtr sac=Persons2::PlayerSeenAC;
	FILE* fp=fopen("vels.txt","at");
	fprintf(fp,"vx=%d vy=%d vz=%d\n",gac->velx,gac->vely,gac->velz);
	fprintf(fp,"fmvx=%f fmvy=%f fmvz=%f\n\n",sac->fly.pModel->Vel.x,
		sac->fly.pModel->Vel.y,sac->fly.pModel->Vel.z);
	fclose(fp);
#endif
}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadItemAnims
//Date			Tue 9 Jun 1998
//------------------------------------------------------------------------------
Bool	Replay::LoadItemAnims()
{
	MobileItemPtr	item;
	AirStrucPtr		ac,tempac;
	ULong	num,temp;
	UWord	offset;
	UByte	newval;
	ULong	n=0;
	ItemPtr i;
	UWord id=0;

// ac anims first 

	do
	{
// get id

		if (!ReplayRead((UByte*)&id,sizeof(UWord)))
			return FALSE;

		ac=*Persons2::ConvertPtrUID((UniqueID)id);

		if (ac)
		{
			if (!prescan) 
			{
				if (ac->Anim == NULL)			   
				{
// I dont think this should ever happen, maybe in mig super flight?

					SHAPE.SetAnimData(ac,ac->weap.Weapons);
				}
				SHAPE.ResetAnimData_NewShape(ac,ac->shape,ac->weap.Weapons);
			}

			if (!ReplayRead((UByte*)&num,sizeof(ULong)))
				return FALSE;

			temp=num;
			n = 0;	

			while (num--)
			{
				if (!ReplayRead((UByte*)&offset,sizeof(UWord)))
					return FALSE;

				if (!ReplayRead((UByte*)&newval,sizeof(UByte)))
					return FALSE;

				if (!prescan) 
				{
					SHAPE.AnimDeltaList[n].deltaoffset=offset;
					SHAPE.AnimDeltaList[n++].newbyte=newval;
				}
			}

			if (!prescan) 
				SHAPE.PatchAnimData((ItemPtr)ac,n);
		}
	}
	while (id!=0);

	if (!prescan)
	{
		//Stop muzzleflash for player...
		AircraftAnimData*	adptr = (AircraftAnimData*) Persons2::PlayerSeenAC->Anim;
		adptr->gunshooting = 0;											
		adptr->cannonshooting = 0;										
	}

// mobiles

	do 
	{
		if (!ReplayRead((UByte*)&id,sizeof(UWord)))
			return FALSE;

		item=(MobileItemPtr)Persons2::ConvertPtrUID((UniqueID)id);

		if (item)
		{
			if (!prescan)
			{
				if (item->Anim == NULL)		
				{
					SHAPE.SetAnimData(item,0);
				}
				SHAPE.ResetAnimData_NewShape(item,item->shape);
			}

			if (!ReplayRead((UByte*)&num,sizeof(ULong)))
				return FALSE;

			temp=num;
			n = 0;    

			while (num--)
			{
				if (!ReplayRead((UByte*)&offset,sizeof(UWord)))
					return FALSE;

				if (!ReplayRead((UByte*)&newval,sizeof(UByte)))
					return FALSE;

				if (!prescan) 
				{
					SHAPE.AnimDeltaList[n].deltaoffset=offset;
					SHAPE.AnimDeltaList[n++].newbyte=newval;
				}
			}

			if (!prescan)
				SHAPE.PatchAnimData(item,n);
		}
	}
	while (id!=0);

// sags

	AirStrucPtr sag;

	do
	{
// get id

		if (!ReplayRead((UByte*)&id,sizeof(UWord)))
			return FALSE;

		sag=*Persons2::ConvertPtrUID((UniqueID)id);

		if (sag)
		{
			if (sag->Anim == NULL)			
			{
// I dont think this should ever happen, maybe in mig super flight?

				SHAPE.SetAnimData(sag,sag->weap.Weapons);
			}
			SHAPE.ResetAnimData_NewShape(sag,sag->shape,sag->weap.Weapons);	

			if (!ReplayRead((UByte*)&num,sizeof(ULong)))
				return FALSE;

			temp=num;
			n = 0;	

			while (num--)
			{
				if (!ReplayRead((UByte*)&offset,sizeof(UWord)))
					return FALSE;

				if (!ReplayRead((UByte*)&newval,sizeof(UByte)))
					return FALSE;

				if (!prescan) 
				{
					SHAPE.AnimDeltaList[n].deltaoffset=offset;
					SHAPE.AnimDeltaList[n++].newbyte=newval;
				}
			}

			if (!prescan)										
				SHAPE.PatchAnimData((ItemPtr)sag,n);
		}
	}
	while (id!=0);

	if (!prescan)
		Persons2::PlayerSeenAC->DoAllSAGChecks();

// items done by dead stream
// all dead or damaged are in dead stream

	return TRUE;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreItemAnims
//Date			Tue 9 Jun 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreItemAnims()
{
	MobileItemPtr	item;
	AirStrucPtr		ac,tempac;
	ULong	num;
	ULong	n = 0,m;
	ItemPtr i;
	UWord uid;

	ac=*AirStruc::ACList;

	while (ac)
	{
		num=SHAPE.ScanAnimData((ItemPtr)ac);

// only store ac whose anim has changed

		if (num)
		{
			uid=ac->uniqueID.count;

			if (!ReplayWrite((UByte*)&uid,sizeof(UWord)))
				return FALSE;

			if (!ReplayWrite((UByte*)&num,sizeof(ULong)))
				return FALSE;

			for (n=0; n < num; n++)
			{
				if (!ReplayWrite((UByte*)&SHAPE.AnimDeltaList[n].deltaoffset,sizeof(UWord)))
					return FALSE;

				if (!ReplayWrite((UByte*)&SHAPE.AnimDeltaList[n].newbyte,sizeof(UByte)))
					return FALSE;
			}
		}

		ac=*ac->nextmobile;
	}

	uid=0;

	if (!ReplayWrite((UByte*)&uid,sizeof(UWord)))
		return FALSE;

	item=mobileitem::MobileList;

	while (item)
	{
		num=SHAPE.ScanAnimData(item);

// only store mobs whose anim has changed

		if (num)
		{
			uid=item->uniqueID.count;
			if (!ReplayWrite((UByte*)&uid,sizeof(UWord)))
				return FALSE;

			if (!ReplayWrite((UByte*)&num,sizeof(ULong)))
				return FALSE;

			for (n=0; n < num; n++)
			{
				if (!ReplayWrite((UByte*)&SHAPE.AnimDeltaList[n].deltaoffset,sizeof(UWord)))
					return FALSE;

				if (!ReplayWrite((UByte*)&SHAPE.AnimDeltaList[n].newbyte,sizeof(UByte)))
					return FALSE;
			}
		}

		item=item->nextmobile;
	}

// UID_NULL indicates end of data

	uid=0;

	if (!ReplayWrite((UByte*)&uid,sizeof(UWord)))
		return FALSE;

// sags

	for (int x=SagBAND;x!=SagBANDEND;x++)
	{
		AirStrucPtr sag=Persons2::ConvertPtrUID(UniqueID(x));

		if (sag)
		{
			num=SHAPE.ScanAnimData((ItemPtr)sag);

			if (num)
			{
				uid=sag->uniqueID.count;

				if (!ReplayWrite((UByte*)&uid,sizeof(UWord)))
					return FALSE;

				if (!ReplayWrite((UByte*)&num,sizeof(ULong)))
					return FALSE;

				for (n=0; n < num; n++)
				{
					if (!ReplayWrite((UByte*)&SHAPE.AnimDeltaList[n].deltaoffset,sizeof(UWord)))
						return FALSE;

					if (!ReplayWrite((UByte*)&SHAPE.AnimDeltaList[n].newbyte,sizeof(UByte)))
						return FALSE;
				}

#ifndef NDEBUG
				SHAPE.ResetAnimData_NewShape(sag,sag->shape,sag->weap.Weapons);
				SHAPE.PatchAnimData((ItemPtr)sag,num);
#endif
			}
		}
	}

	uid=0;

	if (!ReplayWrite((UByte*)&uid,sizeof(UWord)))
		return FALSE;

// items done by deadstream
// dead stream has all dead or damaged items

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BlockForward
//Date			Wed 1 Jul 1998
//------------------------------------------------------------------------------
Bool	Replay::BlockForward()
{
	SLong n=sizeof(REPLAYPACKET);
	SLong m=numframes[currblock-1];
	UByteP temp=playbackfilepos;

	ResetFlags();

	m-=replayframecount;

	SLong skip=n*m;
	playbackfilepos+=skip;
	
	if (!LoadBlockHeader())
	{
		playbackfilepos=temp;
		SkipToEnd();

		return FALSE;
	}
	ResetReplayView();
	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BlockRewind
//Date			Wed 1 Jul 1998
//------------------------------------------------------------------------------
Bool	Replay::BlockRewind(Bool framerewind)
{
	SLong n=sizeof(REPLAYPACKET);
	SLong m=replayframecount;
	SLong skip=0;
	UByteP temp=playbackfilepos;
	ULong pos=playbackfilepos-(UByteP)playbackfilestart;
	UByte	bskip=0;

	ResetFlags();

// if we are 1 sec or less into block then goto to start of previous block
// rather than start of this one
//actually 2 secs with 100 frames

	if ((replayframecount<100 && !Three_Dee.IsPaused() && !framerewind)
	|| replayframecount==0)
	{
		if (currblock>1)
		{
			skip+=m*n;
			skip+=headlength[currblock-1];

			currblock--;
			bskip=1;
		}
	}

	if (bskip)
	{
		skip+=numframes[currblock-1]*n;
	}
	else
	{
		skip+=(n*m);
	}

	skip+=headlength[currblock-1];

	if (skip>pos)
	{
		skip=pos;
	}

	playbackfilepos-=skip;

	currblock--;
	bskip++;

	if (!LoadBlockHeader())
	{
		playbackfilepos=temp;
		currblock+=bskip;
		SkipToBeginning();
		return FALSE;
	}
	ResetReplayView();
	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreHeaderLength
//Date			Thu 2 Jul 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreHeaderLength(ULong length)
{
	if (!length)
	{
		FlushFileBuffers(recordstorage);
		length=GetFileSize(recordstorage,NULL);
	}

	ULong reallen=length+sizeof(ULong);

	if (!ReplayWrite((UByte*)&reallen,sizeof(ULong)))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadHeaderLength
//Date			Thu 2 Jul 1998
//------------------------------------------------------------------------------
ULong	Replay::LoadHeaderLength()
{
	ULong len;

	if (!ReplayRead((UByte*)&len,sizeof(ULong)))
		return FALSE;

	return len;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteGRList
//Date			Wed 8 Jul 1998
//------------------------------------------------------------------------------
void	Replay::DeleteGRList(LPREPGRENTRY& list)
{
	LPREPGRENTRY temp1,temp2;

	temp1=list;

	while (temp1)
	{
		temp2=temp1->next;
		delete temp1;
		temp1=NULL;
		temp1=temp2;
	}
	list=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReplayRead
//Date			Sun 5 Jul 1998
//------------------------------------------------------------------------------
Bool	Replay::ReplayRead(UByte* dest, ULong size)
{
	LPASPRIMARYVALUES lpas;

	if (playbackfilepos+size>playbackfileend)
	{
		PlaybackPaused=TRUE;
		return FALSE;
	}

	CopyMemory(dest,playbackfilepos,size);
	playbackfilepos+=size;

	lpas=(LPASPRIMARYVALUES)dest;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReplayWrite
//Date			Sun 5 Jul 1998
//------------------------------------------------------------------------------
Bool	Replay::ReplayWrite(UByte* src, ULong size)
{
	ULong num;

 	if (WriteFile(recordstorage,src,size,&num,NULL))
 		return TRUE;

 	return FALSE;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetInitalGlobRefs
//Date			Wed 8 Jul 1998
//------------------------------------------------------------------------------
void	Replay::GetInitialGlobRefs()
{
	ULong	val;
	LPREPGRENTRY	temp1,temp2;

	DeleteGRList(initgrlist);

	GetGlobRefs(initgrlist);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreInitalGlobRefs
//Date			Wed 8 Jul 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreInitialGlobRefs()
{
// store Pack_PlayerSquad and Pack_PlayerPos because these are no longer glob refs

	if (!ReplayWrite((UByte*)&PlayerSquad,sizeof(int)))
		return FALSE;

	if (!ReplayWrite((UByte*)&PlayerPos,sizeof(int)))
		return FALSE;

	if (!StoreGlobRefList(initgrlist))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreGlobRefList
//Date			Tue 15 Sep 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreGlobRefList(LPREPGRENTRY list)
{
	ULong val;
	ULong m;
	ULong t[8];
	UByte set=0;
	Bool finished=FALSE;
	LPREPGRENTRY temp=list;

	while (!finished && temp)
	{
		for (m=0;m<8;m++)
		{
			val=temp->val;
			temp=temp->next;
			t[m]=val;

			if (t[m]!=0)
				set|=0x1<<m;

			if (t[m]==BAD_RV || !temp)
			{
				finished=TRUE;
				break;
			}
		}

// have got 8 values, store header and altered values

		if (!ReplayWrite((UByte*)&set,sizeof(UByte)))
			return FALSE;

		for (m=0;m<8;m++)
		{
			if (set&0x1<<m)
			{
				if (!ReplayWrite((UByte*)&t[m],sizeof(int)))
					return FALSE;
			}
		}
		set=0;
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreHeaderID
//Date			Thu 9 Jul 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreHeaderID()
{
	ULong id=REPLAYHEADBEGINID;

	if (!ReplayWrite((UByte*)&id,sizeof(ULong)))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadHeaderID
//Date			Thu 9 Jul 1998
//------------------------------------------------------------------------------
Bool	Replay::LoadHeaderID()
{
	ULong id=0;

	if (!ReplayRead((UByte*)&id,sizeof(ULong)))
		return FALSE;

	if (id!=REPLAYHEADBEGINID)
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadReplayData
//Date			Fri 10 Jul 1998
//------------------------------------------------------------------------------
Bool	Replay::LoadReplayData(char* name)
{
	strcpy(pfilename,name);
	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SaveReplayData
//Date			Fri 10 Jul 1998
//------------------------------------------------------------------------------
Bool	Replay::SaveReplayData(char* name)
{
	HANDLE file;
	char	buffer[150];
	char	buffer2[150];
	
	if (RestorePosition)
	{
		strcpy(buffer,"tblock.dat");
	}
	else
	{
		strcpy(buffer,"replay.dat");
	}

	strcpy(buffer2,name);

	GetReplayFilename(buffer);
	GetReplayFilename(buffer2);

	if (!RestorePosition)
		strcpy(pfilename,buffer);

	file=CreateFile(
		buffer,
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_TEMPORARY,
		NULL);

	if (file==INVALID_HANDLE_VALUE)
	{
		CloseHandle(file);
		_DPlay.CommsMessage(IDS_NOREPLAY);
		return TRUE;
	}

	CloseHandle(file);

	if (!CopyFile(buffer,buffer2,FALSE))
		_DPlay.CommsMessage(IDS_NOTSAVE);
	else
		_DPlay.CommsMessage(IDS_REPLAYSAVEOK);

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadBFieldNum
//Date			Thu 30 Jul 1998
//------------------------------------------------------------------------------
FileNum	Replay::LoadBFieldNum()
{
	FileNum file=FIL_NULL;

	ReplayRead((UByte*)&file,sizeof(FileNum));

	return file;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreBFieldNum
//Date			Thu 30 Jul 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreBFieldNum(FileNum bf)
{
	if (!ReplayWrite((UByte*)&bf,sizeof(FileNum)))	
		return FALSE;

	return TRUE;
}

ULong	Replay::LoadBFCtrl()
{
	ULong a;

	ReplayRead((UByte*)&a,sizeof(ULong));

	return a;
}

Bool	Replay::StoreBFCtrl(ULong ctrl)
{
	if (!ReplayWrite((UByte*)&ctrl,sizeof(ULong)))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreItemData
//Date			Thu 27 Aug 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreItemData()
{
	MobileItemPtr	item;
	AirStrucPtr		ac;
	FILE* fp;

	ac=*AirStruc::ACList;

// for AC there are 2 sets of data, that which is required for all AC and that
// which is only needed by AC in combat or with complex FMs

#ifdef ITEMCOUNT
	fp=fopen("acdata.txt","at");
#endif
	UWord uid;
	while (ac)
	{
		uid=ac->uniqueID.count;
#ifdef ITEMCOUNT
		fprintf(fp,"AC: %x ",uid);
#endif
// dont use TrashModelData in record or it will hide any problems with values
// not being recorded properly

// airstruc stuff

		if (!StorePrimaryASData(ac))
			return FALSE;

		if (!StorePrimaryMIData((MobileItemPtr)ac))
			return FALSE;

		ac->fly.cpitch=ac->pitch;
		ac->CalcXYZVel();		

// need to store this for anim purposes for all ac

		if (!StoreAeroDevData(ac))
			return FALSE;

		if (ac!=Persons2::PlayerSeenAC && ac->fly.pModel)
		{
			if (!ReplayWrite(UByteP(&ac->fly.pModel->CrashTime),sizeof(UWord)))
				return FALSE;
		}

// flight model stuff

		if (((!ac->ai.simpleacm && ac->movecode==AUTO_COMBAT) || ac->movecode==AUTO_FOLLOWTHELEADER) && !ac->Status.deaded)
		{
			if (ac!=Persons2::PlayerSeenAC)
			{
#ifdef ITEMCOUNT
				fprintf(fp,"full ");
#endif
				if (!StorePrimaryFMData(ac))
					return FALSE;

	 			if (!StorePrimaryEngineData(ac))
					return FALSE;

				if (!StorePrimaryElmtData(ac))
					return FALSE;

				if (!StoreSuspensionData(ac))
					return FALSE;

// thrust points are set up by engine, cylinder and surface can be zeroed

			}
		}
		else
		{
#ifdef ITEMCOUNT
			fprintf(fp,"mass ");
#endif
			if (!StoreFMMass(ac))
				return FALSE;

			if (ac!=Persons2::PlayerSeenAC)
				ac->fly.pModel->FirstCycle=TRUE;
		}

		ResetSecondaryFMValues(ac);

#ifdef ITEMCOUNT
		fprintf(fp,"\n");
#endif
		ac=*ac->nextmobile;
	}

	item=mobileitem::MobileList;

	while (item)
	{
		uid=item->uniqueID.count;
#ifdef ITEMCOUNT
		fprintf(fp,"item: %x\n",uid);
#endif
		if (!StorePrimaryMIData(item))
			return FALSE;

		item->CalcXYZVel();								

		item=item->nextmobile;
	}

// SAGs. Need to store SAG values

	for (int i=SagBAND;i!=SagBANDEND;i++)
	{
		SAGAirstruc* sag=Persons2::ConvertPtrUID(UniqueID(i));

		if (sag)
		{
			uid=((AirStrucPtr)sag)->uniqueID.count;
#ifdef ITEMCOUNT
			fprintf(fp,"SAG: %d ",uid);
#endif

			if (!StorePrimarySAGData(sag))
				return FALSE;

			if (!StorePrimaryASData((AirStrucPtr)sag))
				return FALSE;

			if (!StorePrimaryMIData((MobileItemPtr)sag))
				return FALSE;
		}
	}

#ifdef ITEMCOUNT
	fclose(fp);
#endif

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadItemData
//Date			Thu 27 Aug 1998
//------------------------------------------------------------------------------
Bool	Replay::LoadItemData()
{
	MobileItemPtr	item;
	AirStrucPtr		ac;
	UWord	oldsector,newsector;;
	WorldStuff &world = mobileitem::GetWorld();
	ASPRIMARYVALUES aspv;
	MIPRIMARYVALUES mipv;
	AERODEVVALUES	adv;
	FILE* fp;
	UWord uid;

	ac=*AirStruc::ACList;

#ifdef ITEMCOUNT
	fp=fopen("acdatap.txt","at");
#endif
	while (ac)
	{
		uid=ac->uniqueID.count;
#ifdef ITEMCOUNT
			fprintf(fp,"AC: %x ",uid);
#endif
// this can be debug only for finding all cases where values are not being
// stored correctly. Once this is complete this stage will no longer be necessary

#ifndef NDEBUG
		ac->fly.pModel->TrashModelData(ac);
#endif

		oldsector=world.GetSector((MobileItemPtr)ac);

		if (!ReplayRead((UByte*)&aspv,sizeof(ASPRIMARYVALUES)))
			return FALSE;

		if (!ReplayRead((UByte*)&mipv,sizeof(MIPRIMARYVALUES)))
			return FALSE;

		RestorePrimaryASValues( ac,&aspv);
	
		RestorePrimaryMIValues((MobileItemPtr)ac,&mipv);

		ac->fly.cpitch=ac->pitch;								
		ac->CalcXYZVel();										


		PAERODEVICE pAeroDevice=ac->fly.pModel->DeviceList;

		while (pAeroDevice)
		{
			if (!ReplayRead((UByte*)&adv,sizeof(AERODEVVALUES)))
				return FALSE;

			if (!prescan)
				RestoreAeroDevData(&adv,pAeroDevice);				

			pAeroDevice=pAeroDevice->List.NextItem();
		}

// need crash time even if ac is dead

		if (ac!=Persons2::PlayerSeenAC && ac->fly.pModel)
		{
			if (!ReplayRead(UByteP(&ac->fly.pModel->CrashTime),sizeof(UWord)))
				return FALSE;
		}

		newsector=world.GetSector((MobileItemPtr)ac);

		if (newsector!=oldsector && !ac->fly.numinsag)
		{
			world.RemoveFromSector((MobileItemPtr)ac,oldsector);
			world.AddToWorld((MobileItemPtr)ac);
		}

		if (((!ac->ai.simpleacm && ac->movecode==AUTO_COMBAT) || ac->movecode==AUTO_FOLLOWTHELEADER) && !ac->Status.deaded) 
		{
			if (ac!=Persons2::PlayerSeenAC)
			{
#ifdef ITEMCOUNT
				fprintf(fp,"full ");
#endif
				if (!LoadFMData(ac))
					return FALSE;
			}
		}
		else
		{
#ifdef ITEMCOUNT
			fprintf(fp,"mass ");
#endif
			if (!LoadFMMass(ac))
				return FALSE;

			if (ac!=Persons2::PlayerSeenAC)
				ac->fly.pModel->FirstCycle=TRUE;
		}

#ifdef ITEMCOUNT
		fprintf(fp,"\n");
#endif
		if (!prescan)
			ResetSecondaryFMValues(ac);

		ac=*ac->nextmobile;
	}	

 	item=mobileitem::MobileList;

 	while (item)
 	{
		uid=item->uniqueID.count;
#ifdef ITEMCOUNT
		fprintf(fp,"item: %x\n",uid);
#endif
		oldsector=world.GetSector(item);

		if (!ReplayRead((UByte*)&mipv,sizeof(MIPRIMARYVALUES)))
			return FALSE;

		if (!prescan)
		{
			RestorePrimaryMIValues(item,&mipv);

			newsector=world.GetSector(item);

			if (newsector!=oldsector)
			{
				world.RemoveFromSector(item,oldsector);
				world.AddToWorld(item);
			}
		}

		item->CalcXYZVel();						

 		item=item->nextmobile;
 	}

// SAGs

	SAGPRIMARYVALUES sagpv;

	for (int i=SagBAND;i!=SagBANDEND;i++)
	{
		SAGAirstruc* sag=Persons2::ConvertPtrUID(UniqueID(i));

		if (sag)
		{
			uid=((AirStrucPtr)sag)->uniqueID.count;
#ifdef ITEMCOUNT
			fprintf(fp,"SAG: %d ",uid);
#endif
			oldsector=world.GetSector((MobileItemPtr)sag);

			if (!ReplayRead((UByte*)&sagpv,sizeof(SAGPRIMARYVALUES)))
				return FALSE;

			if (!ReplayRead((UByte*)&aspv,sizeof(ASPRIMARYVALUES)))
				return FALSE;

			if (!ReplayRead((UByte*)&mipv,sizeof(MIPRIMARYVALUES)))
				return FALSE;

			RestorePrimarySAGValues(sag,&sagpv);

			RestorePrimaryASValues( (AirStrucPtr)sag,&aspv);
	
			RestorePrimaryMIValues((MobileItemPtr)sag,&mipv);

			newsector=world.GetSector((MobileItemPtr)sag);

			if (newsector!=oldsector)
			{
				world.RemoveFromSector((MobileItemPtr)sag,oldsector);
				world.AddToWorld((MobileItemPtr)sag);
			}
		}
	}

#ifdef ITEMCOUNT
	fclose(fp);
#endif

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StorePrimaryFlightModelData
//Date			Thu 27 Aug 1998
//------------------------------------------------------------------------------
Bool	Replay::StorePrimaryFMData(AirStrucPtr ac)
{
	FMPRIMARYVALUES	fmpv;

	GetPrimaryFMData(ac,&fmpv);

	if (!ReplayWrite((UByte*)&fmpv,sizeof(FMPRIMARYVALUES)))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPrimaryFMData
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	Replay::GetPrimaryFMData(AirStrucPtr ac, LPFMPRIMARYVALUES fmpv)
{
//model.h

	fmpv->FirstCycle=ac->fly.pModel->FirstCycle;				
	fmpv->RotVel=ac->fly.pModel->RotVel;
	fmpv->Elevator=ac->fly.pModel->Elevator;
	fmpv->Aileron=ac->fly.pModel->Aileron;
	fmpv->Rudder=ac->fly.pModel->Rudder;

	fmpv->ElevatorTrim=ac->fly.pModel->ElevatorTrim;
	fmpv->AileronTrim=ac->fly.pModel->AileronTrim;
	fmpv->RudderTrim=ac->fly.pModel->RudderTrim;

	fmpv->ModelThrottle=ac->fly.pModel->ModelThrottle;
	fmpv->ModelPropSetting=ac->fly.pModel->ModelPropSetting;
	fmpv->LeftWheelBrake=ac->fly.pModel->LeftWheelBrake;
	fmpv->RightWheelBrake=ac->fly.pModel->RightWheelBrake;
	fmpv->Spinning=ac->fly.pModel->Spinning;
	fmpv->TotalBuffet=ac->fly.pModel->TotalBuffet;

// acmmodel.h
	
	fmpv->lastdeltapitch=ac->fly.pAcmModel->lastdeltapitch;
	fmpv->deltapitchsum=ac->fly.pAcmModel->deltapitchsum;
	fmpv->deltarollsum=ac->fly.pAcmModel->deltarollsum;
	fmpv->deltayawsum=ac->fly.pAcmModel->deltayawsum;
	fmpv->maxdeltaforclosework=ac->fly.pAcmModel->maxdeltaforclosework;
	fmpv->OldCtrlRoll=ac->fly.pAcmModel->OldCtrlRoll;
	fmpv->OldCtrlTurnRate=ac->fly.pAcmModel->OldCtrlTurnRate;
	fmpv->OldCtrlYawRate=ac->fly.pAcmModel->OldCtrlYawRate;
	fmpv->desiredRoll=ac->fly.pAcmModel->desiredRoll;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StorePrimaryEngineData
//Date			Tue 29 Sep 1998
//------------------------------------------------------------------------------
Bool	Replay::StorePrimaryEngineData(AirStrucPtr ac)
{
	PRIMARYENGINEVALUES enpv;

// engine.h

	PENGINE pEngine = ac->fly.pModel->EngineList;

	while (pEngine)
	{
		GetPrimaryEngineData(&enpv,pEngine);

		if (!ReplayWrite((UByte*)&enpv,sizeof(PRIMARYENGINEVALUES)))
			return FALSE;

		pEngine=pEngine->List.NextItem();
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPrimaryEngineData
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	Replay::GetPrimaryEngineData(LPPRIMARYENGINEVALUES enpv, PENGINE pEngine)
{
	enpv->Speed=pEngine->Speed;
	enpv->SpeedRpm=pEngine->SpeedRpm;

	enpv->Power0=pEngine->Power0;
	enpv->Power100=pEngine->Power100;
	enpv->Power=pEngine->Power;

	enpv->MaxThrust=pEngine->MaxThrust;

	enpv->Thrust=pEngine->Thrust;
	enpv->Torque=pEngine->Torque;
	enpv->moment=pEngine->moment;

	enpv->PropInc=pEngine->PropInc;
	enpv->PropVel=pEngine->PropVel;
	enpv->SlipVel=pEngine->SlipVel;
	enpv->SlipRot=pEngine->SlipRot;

	enpv->FuelInPipes=pEngine->FuelInPipes;

	enpv->ThrottleSetting=pEngine->ThrottleSetting;				
	enpv->PropSetting=pEngine->PropSetting;						
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StorePrimaryElmtData
//Date			Tue 29 Sep 1998
//------------------------------------------------------------------------------
Bool	Replay::StorePrimaryElmtData(AirStrucPtr ac)
{
	PRIMARYELMTVALUES elpv;

// elmt.h

	PMAINPLANE pMainPlane = ac->fly.pModel->MainPlaneList;

	while (pMainPlane)
	{
		GetPrimaryElmtData(&elpv,pMainPlane);

		if (!ReplayWrite((UByte*)&elpv,sizeof(PRIMARYELMTVALUES)))
			return FALSE;

		pMainPlane=pMainPlane->List.NextItem();
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPrimaryElmtData
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	Replay::GetPrimaryElmtData(LPPRIMARYELMTVALUES elpv,PMAINPLANE pMainPlane)
{
	for(SWord wing = 0; wing < 2; wing++)
	{
		for(SWord section = 0; section < 2; section++)
		{
			elpv->aoa[wing][section]=pMainPlane->aoa[wing][section];
		}
	}

	elpv->DownWashAng[0]=pMainPlane->DownWashAng[0];
	elpv->DownWashAng[1]=pMainPlane->DownWashAng[1];
	elpv->BuffetAoaMin=pMainPlane->BuffetAoaMin;
	elpv->BuffetAoaMax=pMainPlane->BuffetAoaMax;

	elpv->eForce[0][0]=pMainPlane->eForce[0][0];
	elpv->eForce[0][1]=pMainPlane->eForce[0][1];
	elpv->eForce[1][0]=pMainPlane->eForce[1][0];
	elpv->eForce[1][1]=pMainPlane->eForce[1][1];

	elpv->eMoment[0][0]=pMainPlane->eMoment[0][0];
	elpv->eMoment[0][1]=pMainPlane->eMoment[0][1];
	elpv->eMoment[1][0]=pMainPlane->eMoment[1][0];
	elpv->eMoment[1][1]=pMainPlane->eMoment[1][1];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestorePrimaryFMData
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	Replay::RestorePrimaryFMData(AirStrucPtr ac,LPFMPRIMARYVALUES fmpv)
{
//model.h

	ac->fly.pModel->FirstCycle=fmpv->FirstCycle;			
	ac->fly.pModel->RotVel=fmpv->RotVel;
	ac->fly.pModel->Elevator=fmpv->Elevator;
	ac->fly.pModel->Aileron=fmpv->Aileron;
	ac->fly.pModel->Rudder=fmpv->Rudder;

	ac->fly.pModel->ElevatorTrim=fmpv->ElevatorTrim;
	ac->fly.pModel->AileronTrim=fmpv->AileronTrim;
	ac->fly.pModel->RudderTrim=fmpv->RudderTrim;

	ac->fly.pModel->ModelThrottle=fmpv->ModelThrottle;
	ac->fly.pModel->ModelPropSetting=fmpv->ModelPropSetting;
	ac->fly.pModel->LeftWheelBrake=fmpv->LeftWheelBrake;
	ac->fly.pModel->RightWheelBrake=fmpv->RightWheelBrake;
	ac->fly.pModel->Spinning=fmpv->Spinning;
	ac->fly.pModel->TotalBuffet=fmpv->TotalBuffet;

//acmmodel.h

	ac->fly.pAcmModel->lastdeltapitch=fmpv->lastdeltapitch;
	ac->fly.pAcmModel->deltapitchsum=fmpv->deltapitchsum;
	ac->fly.pAcmModel->deltarollsum=fmpv->deltarollsum;
	ac->fly.pAcmModel->deltayawsum=fmpv->deltayawsum;
	ac->fly.pAcmModel->maxdeltaforclosework=fmpv->maxdeltaforclosework;
	ac->fly.pAcmModel->OldCtrlRoll=fmpv->OldCtrlRoll;
	ac->fly.pAcmModel->OldCtrlTurnRate=fmpv->OldCtrlTurnRate;
	ac->fly.pAcmModel->OldCtrlYawRate=fmpv->OldCtrlYawRate;
	ac->fly.pAcmModel->desiredRoll=fmpv->desiredRoll;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestorePrimaryEngineData
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	Replay::RestorePrimaryEngineData(LPPRIMARYENGINEVALUES e, PENGINE pEngine)
{
	pEngine->Speed=e->Speed;
	pEngine->SpeedRpm=e->SpeedRpm;

	pEngine->Power0=e->Power0;
	pEngine->Power100=e->Power100;
	pEngine->Power=e->Power;

	pEngine->MaxThrust=e->MaxThrust;

	pEngine->Thrust=e->Thrust;
	pEngine->Torque=e->Torque;
	pEngine->moment=e->moment;

	pEngine->PropInc=e->PropInc;
	pEngine->PropVel=e->PropVel;
	pEngine->SlipVel=e->SlipVel;
	pEngine->SlipRot=e->SlipRot;

	pEngine->FuelInPipes=e->FuelInPipes;

	pEngine->ThrottleSetting=e->ThrottleSetting;				
	pEngine->PropSetting=e->PropSetting;						
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestorePrimaryElmtData
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	Replay::RestorePrimaryElmtData(LPPRIMARYELMTVALUES elpv,PMAINPLANE pMainPlane)
{
	for(SWord wing = 0; wing < 2; wing++)
	{
		for(SWord section = 0; section < 2; section++)
		{
			pMainPlane->aoa[wing][section]=elpv->aoa[wing][section];
		}
	}

	pMainPlane->DownWashAng[0]=elpv->DownWashAng[0];
	pMainPlane->DownWashAng[1]=elpv->DownWashAng[1];
	pMainPlane->BuffetAoaMin=elpv->BuffetAoaMin;
	pMainPlane->BuffetAoaMax=elpv->BuffetAoaMax;

	pMainPlane->eForce[0][0]=elpv->eForce[0][0];
	pMainPlane->eForce[0][1]=elpv->eForce[0][1];
	pMainPlane->eForce[1][0]=elpv->eForce[1][0];
	pMainPlane->eForce[1][1]=elpv->eForce[1][1];

	pMainPlane->eMoment[0][0]=elpv->eMoment[0][0];
	pMainPlane->eMoment[0][1]=elpv->eMoment[0][1];
	pMainPlane->eMoment[1][0]=elpv->eMoment[1][0];
	pMainPlane->eMoment[1][1]=elpv->eMoment[1][1];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadPrimaryFlightModelData
//Date			Thu 27 Aug 1998
//------------------------------------------------------------------------------
Bool	Replay::LoadFMData(AirStrucPtr ac)
{
	FMPRIMARYVALUES fmpv;

	if (!ReplayRead((UByte*)&fmpv,sizeof(FMPRIMARYVALUES)))
		return FALSE;

	if (!prescan)
		RestorePrimaryFMData(ac,&fmpv);

// engine.h

	PENGINE pEngine = ac->fly.pModel->EngineList;
	PRIMARYENGINEVALUES e;

	while (pEngine)
	{
		if (!ReplayRead((UByte*)&e,sizeof(PRIMARYENGINEVALUES)))
			return FALSE;

		if (!prescan)
			RestorePrimaryEngineData(&e,pEngine);

		pEngine=pEngine->List.NextItem();
	}

// elmt.h

	PMAINPLANE pMainPlane = ac->fly.pModel->MainPlaneList;
	PRIMARYELMTVALUES elpv;

	while (pMainPlane)
	{
		if (!ReplayRead((UByte*)&elpv,sizeof(PRIMARYELMTVALUES)))
			return FALSE;

		if (!prescan)
			RestorePrimaryElmtData(&elpv,pMainPlane);

		pMainPlane=pMainPlane->List.NextItem();
	}

	FP legpos;
	PGEAR pGear=ac->fly.pModel->GearList;

	while (pGear)
	{
		if (!ReplayRead((UByte*)&legpos,sizeof(FP)))
			return FALSE;

		if (!prescan)
			RestoreSuspensionData(legpos,pGear);

	 	pGear = pGear->List.NextItem();
	}

	return TRUE;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetSecondaryFlightModelData
//Date			Thu 27 Aug 1998
//------------------------------------------------------------------------------
void	Replay::ResetSecondaryFMValues(AirStrucPtr ac)
{
	FCRD	backupvel;

	PMODEL p=ac->fly.pModel;
	FCRD	temprotvel=p->RotVel;

	if (ac==Persons2::PlayerSeenAC)
		backupvel=p->Vel;

	if (_Replay.Playback)
	{
		ac->ai.diaryptr=NULL;
	}

// model.h

	p->Gust.Time=0;

	p->Acc.x=0;
	p->Acc.y=0;
	p->Acc.z=0;

	p->CheatAcc.x=32767;
	p->CheatAcc.y=32767;
	p->CheatAcc.z=32767;

// acmmodel.h

	ac->fly.pAcmModel->CtrlThrust=0;
	ac->fly.pAcmModel->CtrlRollRate=0.0;
	ac->fly.pAcmModel->CtrlPitchRate=0.0;
	ac->fly.pAcmModel->CtrlPitch=0.0;
	ac->fly.pAcmModel->CtrlRoll=0.0;
	ac->fly.pAcmModel->CtrlSpeed=0.0;
	ac->fly.pAcmModel->CtrlMach=0.0;
	ac->fly.pAcmModel->CtrlClimbRate=0.0;
	ac->fly.pAcmModel->CtrlTurnRate=0.0;
	ac->fly.pAcmModel->CtrlYawRate=0.0;
	ac->fly.pAcmModel->CtrlHeight=0.0;
	ac->fly.pAcmModel->CtrlMinHeight=0.0;
	ac->fly.pAcmModel->CtrlHeading=0.0;
	ac->fly.pAcmModel->CtrlVector.x=0.0;
	ac->fly.pAcmModel->CtrlVector.y=0.0;
	ac->fly.pAcmModel->CtrlVector.z=0.0;
	ac->fly.pAcmModel->CtrlMaxBank=0.0;
	ac->fly.pAcmModel->CtrlRudder=0;
	ac->fly.pAcmModel->CtrlElevator=0;
	ac->fly.pAcmModel->CtrlAileron=0;
	ac->fly.pAcmModel->CtrlAoA=0.0;
	ac->fly.pAcmModel->OldAoa=0.0;					

// engine.h
	
	// none

// elmt.h

	PMAINPLANE pMainPlane = ac->fly.pModel->MainPlaneList;

	while (pMainPlane)
	{
		pMainPlane->fCd0Mach = 1;
		pMainPlane->fKMach   = 1;
		pMainPlane=pMainPlane->List.NextItem();
	}

	for(PSURFACE pSurface = ac->fly.pModel->SurfaceList; pSurface; pSurface = pSurface->List.NextItem())
	{
		NullVec(pSurface->Force);
		NullVec(pSurface->Moment);
	}

	for(PTHRUSTPOINT pThrust = ac->fly.pModel->ThrustList; pThrust; pThrust = pThrust->List.NextItem())
	{
		NullVec(pThrust->Force);
		NullVec(pThrust->Moment);
	}

	for(PCYLINDER pCylinder = ac->fly.pModel->CylinderList; pCylinder; pCylinder = pCylinder->List.NextItem())
	{
		NullVec(pCylinder->Force);
	}
  

//call updatemodel
//call calcairvel
//call gearcalcs
//call accurategroundaltitude
//call SetAirStrucOrientation - WHY?????
// calc cpitch 
// calc i_a_s - INSTRUMENTS NOT NEEDED
// calc vel_cms

	ac->fly.pModel->UpdateModel(ac);
	ac->fly.pModel->UpdateAirStruc(ac);							
	ac->fly.pModel->UpdateMassInertias(ac);						
	ac->fly.pModel->ACMInstruments(ac);			

// update model resets rotvel, so update it again!

	p->RotVel=temprotvel;

	ac->fly.pModel->CalcAirVel(ac);

	MMC.Sky.Ambient(p->Pos.y,p->AmbDensity,p->AmbTemp,p->AmbPres);


// calc groundlevel

	ac->fly.pModel->GroundHeight = _Collide.LowestSafeAlt(ac,ac->pitch,ac->roll);

	Bool	realplayback=Playback;
	Playback=TRUE;
	ac->SetFlightParams	(false); // sets vel_cms

	if (ac==Persons2::PlayerSeenAC)
		p->Vel=backupvel;

	Playback=realplayback;

	Trans_Obj.ClearWeaponChain(ac);						
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetReplayData
//Date			Tue 15 Sep 1998
//------------------------------------------------------------------------------
void	Replay::ResetReplayData()
{
	replayframecount=0;
	currblock=0;
	numblocks=0;

	ResetFlags();

	ReplayDeathMode = RDEATH_NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddFileAndGLobRefsToList
//Date			Tue 15 Sep 1998
//------------------------------------------------------------------------------
void	Replay::AddFileAndGlobRefsToList(FileNum file,ULong bfctrl)
{
 	LPGRLIST temp=bfgrlist;

	LPGRLIST temp2=new GRLIST;

	temp2->file=file;
	temp2->bfctrl=bfctrl;
	
	temp2->list=NULL;
	GetGlobRefs(temp2->list);
	temp2->next=NULL;

	if (temp)
	{
		while (temp->next)
		{
			temp=temp->next;
		}
		temp->next=temp2;
	}
	else
	{
		bfgrlist=temp2;
	}

	temp2=NULL;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGlobRefs
//Date			Tue 15 Sep 1998
//------------------------------------------------------------------------------
void	Replay::GetGlobRefs(LPREPGRENTRY& list)
{
	Bool	finished=FALSE;
	ULong	n=0;
	int val;
	LPREPGRENTRY	temp1,temp2;

	while (!finished)
	{
		val=Persons2::GetLoc(n++);

		if (val==BAD_RV)
			finished=TRUE;

		temp1=new REPGRENTRY;
		temp1->val=val;
		temp1->next=NULL;


		if (list)
		{
			temp2=list;

			while (temp2->next)
				temp2=temp2->next;

			temp2->next=temp1;
			temp2=NULL;
		}
		else
		{
			list=temp1;
		}
		temp1=NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteFileAndGlobRefList
//Date			Tue 15 Sep 1998
//------------------------------------------------------------------------------
void	Replay::DeleteFileAndGlobRefList(LPGRLIST& list)
{
	LPGRLIST	temp2,temp=list;
	LPREPGRENTRY	t1,t2;

	while (temp)
	{
		temp2=temp->next;
		
		t1=temp->list;

		DeleteGRList(t1);
		t1=NULL;

		delete temp;
		temp=NULL;
		temp=temp2;
	}

	list=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreFileAndGlobRefList
//Date			Tue 15 Sep 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreFileAndGlobRefList()
{
	LPGRLIST	temp=bfgrlist;

	while (temp)
	{
		if (!StoreBFieldNum(temp->file))
			return FALSE;

		if (!StoreBFCtrl(temp->bfctrl))
			return FALSE;

		if (!StoreGlobRefList(temp->list))
			return FALSE;

		temp=temp->next;
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadFileAndGlobRefList
//Date			Tue 15 Sep 1998
//------------------------------------------------------------------------------
Bool	Replay::LoadFileAndGlobRefList()
{
	FileNum file;
	ULong ctrl;

	DeleteFileAndGlobRefList(bfgrlist);

	do
	{
		LPGRLIST temp=new GRLIST;

		temp->next=NULL;
		temp->file=LoadBFieldNum();
		temp->bfctrl=LoadBFCtrl();
		temp->list=NULL;
		file=temp->file;
		ctrl=temp->bfctrl;
		if (!LoadGlobRefList(temp->list))
			return FALSE;

		if (bfgrlist)
		{
			LPGRLIST temp2=bfgrlist;

			while (temp2->next)
				temp2=temp2->next;

			temp2->next=temp;
		}
		else
		{
			bfgrlist=temp;
		}
		temp=NULL;
	}
	while (ctrl!=Persons2::FINISHBF);

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGlobRefs
//Date			Tue 15 Sep 1998
//------------------------------------------------------------------------------
void	Replay::SetGlobRefs(LPREPGRENTRY list)
{
	LPREPGRENTRY temp=list;
	ULong n=0;

	while (temp && temp->val!=BAD_RV)
	{
		Persons2::SetLoc(n,temp->val);
		n++;
		temp=temp->next;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SkipToBeginning
//Date			Wed 16 Sep 1998
//------------------------------------------------------------------------------
void	Replay::SkipToBeginning()
{
	ResetFlags();

	playbackfilepos=(UByteP)playbackfilestart+SuperHeaderSize;
	currblock=0;

	if (!LoadBlockHeader())
	{
		_Error.SayAndQuit("Error: cannot read playback file");
	}

	ResetReplayView();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SkipToEnd
//Date			Wed 16 Sep 1998
//------------------------------------------------------------------------------
void	Replay::SkipToEnd()
{
	SLong n=sizeof(REPLAYPACKET);
	SLong m=replayframecount;
	UByteP temp=playbackfilepos;
	SLong skip;

	PlaybackPaused=TRUE;
	ResetFlags();

// rewind to beginning of this block

	skip=n*m;
	skip+=headlength[currblock-1];
	playbackfilepos-=skip;
	currblock--;

// keep jumping forward till no new headers

	while (LoadBlockHeader())
	{
		m=numframes[currblock-1];
		skip=n*m;
		
		temp=playbackfilepos;
		playbackfilepos+=skip;
	}

// jump to end of last good header, frames will be skipped next

	framestoskip=thisblockendframe+1;
	ReplayFlag=RF_SKIPFRAMES;
	playbackfilepos=temp;
	ResetReplayView();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FrameForward
//Date			Wed 16 Sep 1998
//------------------------------------------------------------------------------
void	Replay::FrameForward()
{
// dont need to do anything !!!!!!!!!!!!!!!!
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FrameRewind
//Date			Wed 16 Sep 1998
//------------------------------------------------------------------------------
ULong	Replay::FrameRewind()
{
	ULong temp=replayframecount,skip=0;

	ResetFlags();


	if (!(temp==0 && currblock==1))
	{
		if (temp==0)
		{
			skip=numframes[currblock-2]-1;
		}
		else
		{
			skip=temp-1;
		}

		if (!BlockRewind(TRUE))
		{
// dont call skip if there are no frames to skip

			return 0;
		}
	}
	else
	{
// at beginning of file, dont do anything
		
	}
	return skip;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreInitFrameCounts
//Date			Thu 17 Sep 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreInitFrameCounts()
{
	UWord	temp=0;

// temporarily write zeros to header, they will be filled in when block is finished

	if (!ReplayWrite((UByte*)&temp,sizeof(UWord)))
		return FALSE;

	if (!ReplayWrite((UByte*)&temp,sizeof(UWord)))
		return FALSE;

	if (!ReplayWrite((UByte*)&temp,sizeof(UWord)))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreRealFrameCounts
//Date			Thu 17 Sep 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreRealFrameCounts(UWord num, UWord start, UWord end)
{
// rewind to correct place and store num of frames etc

	SLong jump=num*sizeof(REPLAYPACKET);

	jump+=sizeof(ULong);
	jump+=sizeof(UWord)*3;
	jump=-jump;

	SetFilePointer(recordstorage,jump,NULL,FILE_CURRENT);

	if (!ReplayWrite((UByte*)&num,sizeof(UWord)))
		return FALSE;

	if (!ReplayWrite((UByte*)&start,sizeof(UWord)))
		return FALSE;

	if (!ReplayWrite((UByte*)&end,sizeof(UWord)))
		return FALSE;

	SetFilePointer(recordstorage,0,NULL,FILE_END);

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadFrameCounts
//Date			Thu 17 Sep 1998
//------------------------------------------------------------------------------
Bool	Replay::LoadFrameCounts()
{
	if (!ReplayRead((UByte*)&thisblocknumframes,sizeof(UWord)))
		return FALSE;

	if (!ReplayRead((UByte*)&thisblockstartframe,sizeof(UWord)))
		return FALSE;

	if (!ReplayRead((UByte*)&thisblockendframe,sizeof(UWord)))
		return FALSE;

	if (thisblocknumframes==0)
		emptyblock=true;
	else
		emptyblock=false;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StorePrimaryASData
//Date			Mon 28 Sep 1998
//------------------------------------------------------------------------------
Bool	Replay::StorePrimaryASData(AirStrucPtr ac)
{
	ASPRIMARYVALUES aspv;

	GetPrimaryASData(ac,&aspv);

	if (!ReplayWrite((UByte*)&aspv,sizeof(ASPRIMARYVALUES)))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPrimaryASData
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	Replay::GetPrimaryASData(AirStrucPtr ac, LPASPRIMARYVALUES aspv)
{
	UniqueID ID;
	AirStrucPtr	tempac;
	int n;

//worldinc.h

// for ai stuff take the ghosts data

	if (ac==Persons2::PlayerSeenAC)
	{
		tempac=Persons2::PlayerSeenAC;
		ac=Persons2::PlayerGhostAC;
	}
	else
	{
		tempac=ac;
	}


// backup seen AI info into ghost info later

	if (ac->ai.homebase)
		ID=ac->ai.homebase->uniqueID.count;
	else
		ID=UID_Null;

	aspv->homebase=ID;

	if (ac->ai.unfriendly)
		ID=ac->ai.unfriendly->uniqueID.count;
	else
		ID=UID_Null;

	aspv->unfriendly=ID;

	if (ac->ai.attacker)
		ID=ac->ai.attacker->uniqueID.count;
	else
		ID=UID_Null;

	aspv->attacker=ID;

	if (ac->fly.expandedsag)
		ID=ac->fly.expandedsag->uniqueID.count;
	else
		ID=UID_Null;

	aspv->expandedsag=ID;

	if(ac->ai.spottedunfriendly[0])	ID = ac->ai.spottedunfriendly[0]->uniqueID.count;
	else							ID = UID_Null;
	aspv->spottedunfriendly0 = ID;
	if(ac->ai.spottedunfriendly[1])	ID = ac->ai.spottedunfriendly[1]->uniqueID.count;
	else							ID = UID_Null;
	aspv->spottedunfriendly1 = ID;
	if(ac->ai.spottedunfriendly[2])	ID = ac->ai.spottedunfriendly[2]->uniqueID.count;
	else							ID = UID_Null;
	aspv->spottedunfriendly2 = ID;
	if(ac->ai.spottedunfriendly[3])	ID = ac->ai.spottedunfriendly[3]->uniqueID.count;
	else							ID = UID_Null;
	aspv->spottedunfriendly3 = ID;

	aspv->numinsag=ac->fly.numinsag;


	aspv->manoeuvre=ac->ai.manoeuvre;
	aspv->ManStep=ac->ai.ManStep;
	aspv->simpleacm=ac->ai.simpleacm;
	aspv->beenseen=ac->ai.beenseen;							
	aspv->morale=ac->ai.morale;
	aspv->moraleinc=ac->ai.moraleinc;
	aspv->desiredroll=ac->ai.desiredroll;
	aspv->desiredpitch=ac->ai.desiredpitch;
	aspv->desiredaoa=ac->ai.desiredaoa;
	aspv->desiredhdg=ac->ai.desiredhdg;
	aspv->desiredturn=ac->ai.desiredturn;
	aspv->desiredpitchrate=ac->ai.desiredpitchrate;
	aspv->desiredrange=ac->ai.desiredrange;
	aspv->desiredalt=ac->ai.desiredalt;
	aspv->deltapitchsum=ac->ai.deltapitchsum;

	ac=tempac;

	UpdateSeenAIData();

// this contains fuel levels

	aspv->rreloadmass=ac->weap.right.reloadmass;
	aspv->creloadmass=ac->weap.centre.reloadmass;
	aspv->lreloadmass=ac->weap.left.reloadmass;

	aspv->rreloaddrag=ac->weap.right.reloaddrag;
	aspv->creloaddrag=ac->weap.centre.reloaddrag;
	aspv->lreloaddrag=ac->weap.left.reloaddrag;

	aspv->rmass=ac->weap.right.mass;
	aspv->cmass=ac->weap.centre.mass;
	aspv->lmass=ac->weap.left.mass;

	aspv->rdrag=ac->weap.right.drag;
	aspv->cdrag=ac->weap.centre.drag;
	aspv->ldrag=ac->weap.left.drag;

	for(n = 0; n < 4; n++)						
		aspv->fuel_cont[n] = ac->fly.fuel_content[n];	

	aspv->shpweapindex=ac->weap.shpweapindex;
	aspv->ShootDelay=ac->weap.ShootDelay;
	aspv->UseIntFuel=ac->weap.UseIntFuel;
	aspv->FuelDumped=ac->weap.FuelDumped;
	aspv->weapforce=ac->weap.weapforce;

	aspv->StoresDumped=ac->weap.StoresDumped;
	aspv->Ejected=ac->weap.Ejected;

	aspv->originalformpos=ac->fly.originalformpos;

	if (ac->fly.nextflight)
		ID=ac->fly.nextflight->uniqueID.count;
	else
		ID=UID_Null;

	aspv->nextflight=ID;

	if (ac->fly.leadflight)
		ID=ac->fly.leadflight->uniqueID.count;
	else
		ID=UID_Null;

	aspv->leadflight=ID;
	aspv->rpm=ac->fly.rpm;
	aspv->thrustpercent=ac->fly.thrustpercent;

	if (ac->fly.backupWP)
		ID=ac->fly.backupWP->uniqueID.count;
	else
		ID=UID_Null;

	aspv->backupWP=ID;
	aspv->gforce=ac->fly.gforce;
	aspv->aileron=ac->fly.aileron;
	aspv->elevator=ac->fly.elevator;
	aspv->rudder=ac->fly.rudder;
	aspv->dhdg=ac->fly.dhdg;

	for (n=0;n<4;n++)
		aspv->use_this_tank[n]=ac->fly.use_this_tank[n];

	aspv->FuelCockPos=ac->fly.FuelCockPos;
	if(ac->fly.pModel)													
		aspv->FrameCount = ac->fly.pModel->FrameCount;				

	aspv->lasthitter=ac->lasthitter;

	aspv->Weapons=ac->weap.Weapons;

	aspv->formpos=ac->formpos;

	aspv->formation=ac->formation;
	aspv->information=ac->information;
	aspv->slowdownleader=ac->slowdownleader;
	aspv->duty=ac->duty;
	aspv->advantage=ac->advantage;
	aspv->disadvantage=ac->disadvantage;

	SetVelsAndOldVals(ac);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateSeenAIData
//Date			Wed 6 Jan 1999
//------------------------------------------------------------------------------
void	Replay::UpdateSeenAIData()
{
	CopyMemory(&Persons2::PlayerSeenAC->ai,&Persons2::PlayerGhostAC->ai,sizeof(ai_info));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StorePrimaryMIData
//Date			Tue 29 Sep 1998
//------------------------------------------------------------------------------
Bool	Replay::StorePrimaryMIData(MobileItemPtr ac) 
{
	MIPRIMARYVALUES mipv;
	
	GetPrimaryMIData(ac, &mipv);

	if (!ReplayWrite((UByte*)&mipv,sizeof(MIPRIMARYVALUES)))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPrimaryMIData
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	Replay::GetPrimaryMIData(MobileItemPtr ac, LPMIPRIMARYVALUES mipv)
{
	UniqueID ID;
	MobileItemPtr seenac;
	MobileItemPtr ghostac;

	if (ac==Persons2::PlayerSeenAC)
	{
		ghostac=(MobileItemPtr)Persons2::PlayerGhostAC;
		seenac=(MobileItemPtr)Persons2::PlayerSeenAC;

		ghostac->Status=seenac->Status;

		ghostac->World.X=seenac->World.X;
		ghostac->World.Y=seenac->World.Y;
		ghostac->World.Z=seenac->World.Z;

		ghostac->hdg.a=seenac->hdg.a;
		ghostac->pitch.a=seenac->pitch.a;
		ghostac->roll.a=seenac->roll.a;

		ghostac->vel_=seenac->vel_;

		ghostac->movecode<<=seenac->movecode;
		ghostac->waypoint=seenac->waypoint;

	}
	else
	{
		seenac=ac;
		ghostac=ac;
	}

	mipv->pos=ghostac->World;

	mipv->Status=seenac->Status;

	mipv->hdg.a=ghostac->hdg.a;
	mipv->pitch.a=ghostac->pitch.a;
	mipv->roll.a=ghostac->roll.a;

	mipv->vel=ghostac->vel_;

	if (seenac->waypoint)
		ID=seenac->waypoint->uniqueID.count;
	else
		ID=UID_Null;

	mipv->waypoint=ID;
	mipv->movecode=seenac->movecode;

	mipv->shape=seenac->shape;

	if (seenac->Status.size>=FORMATIONSIZE)						
	{															
		if (((FormationItemPtr)(seenac))->leader)				
			ID=((FormationItemPtr)(seenac))->leader->uniqueID.count;
		else													
			ID=UID_Null;										
	}															

	mipv->leader=ID;											

	if (seenac->Status.size>=FORMATIONSIZE)						
	{															
		if (((FormationItemPtr)(seenac))->follower)				
			ID=((FormationItemPtr)(seenac))->follower->uniqueID.count;
		else													
			ID=UID_Null;										
		
		mipv->manoeuvretime=((FormationItemPtr)(seenac))->manoeuvretime;
	}															

	mipv->follower=ID;											
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestorePrimaryASValues
//Date			Mon 28 Sep 1998
//------------------------------------------------------------------------------
void	Replay::RestorePrimaryASValues(AirStrucPtr ac, LPASPRIMARYVALUES aspv)
{
	AirStrucPtr tempac;
	int n;

	if (ac==Persons2::PlayerSeenAC)
	{
		tempac=Persons2::PlayerSeenAC;
		ac=Persons2::PlayerGhostAC;
	}
	else
	{
		tempac=ac;
	}

 	ac->ai.homebase=(itemptr)Persons2::ConvertPtrUID(aspv->homebase);

 	ac->ai.unfriendly=(itemptr)Persons2::ConvertPtrUID(aspv->unfriendly);

	if (ac->ai.unfriendly==Persons2::PlayerSeenAC)
		ac->ai.unfriendly=Persons2::PlayerGhostAC;

	ac->ai.attacker=(AirStrucPtr)Persons2::ConvertPtrUID(aspv->attacker);

	if (ac->ai.attacker==Persons2::PlayerSeenAC)
		ac->ai.attacker=Persons2::PlayerGhostAC;

	ac->ai.spottedunfriendly[0] = (AirStrucPtr)Persons2::ConvertPtrUID(aspv->spottedunfriendly0);	
	ac->ai.spottedunfriendly[1] = (AirStrucPtr)Persons2::ConvertPtrUID(aspv->spottedunfriendly1);	
	ac->ai.spottedunfriendly[2] = (AirStrucPtr)Persons2::ConvertPtrUID(aspv->spottedunfriendly2);	
	ac->ai.spottedunfriendly[3] = (AirStrucPtr)Persons2::ConvertPtrUID(aspv->spottedunfriendly3);	

	ac->fly.expandedsag=(AirStrucPtr)Persons2::ConvertPtrUID(aspv->expandedsag);

	if (ac->fly.expandedsag==Persons2::PlayerSeenAC)
		ac->fly.expandedsag=Persons2::PlayerGhostAC;

	ac->fly.numinsag=aspv->numinsag;


	ac->ai.manoeuvre=aspv->manoeuvre;
	ac->ai.ManStep=aspv->ManStep;
	ac->ai.simpleacm=aspv->simpleacm;
	ac->ai.beenseen=aspv->beenseen;									
	ac->ai.morale=aspv->morale;
	ac->ai.moraleinc=aspv->moraleinc;
	ac->ai.desiredroll=aspv->desiredroll;
	ac->ai.desiredpitch=aspv->desiredpitch;
	ac->ai.desiredaoa=aspv->desiredaoa;
	ac->ai.desiredhdg=aspv->desiredhdg;
	ac->ai.desiredturn=aspv->desiredturn;
	ac->ai.desiredpitchrate=aspv->desiredpitchrate;
	ac->ai.desiredrange=aspv->desiredrange;
	ac->ai.desiredalt=aspv->desiredalt;
	ac->ai.deltapitchsum=aspv->deltapitchsum;

	UpdateSeenAIData();

	ac=tempac;

	ac->weap.right.reloadmass=aspv->rreloadmass;
	ac->weap.centre.reloadmass=aspv->creloadmass;
	ac->weap.left.reloadmass=aspv->lreloadmass;

	ac->weap.right.reloaddrag=aspv->rreloaddrag;
	ac->weap.centre.reloaddrag=aspv->creloaddrag;
	ac->weap.left.reloaddrag=aspv->lreloaddrag;

	ac->weap.right.mass=aspv->rmass;
	ac->weap.centre.mass=aspv->cmass;
	ac->weap.left.mass=aspv->lmass;

	ac->weap.right.drag=aspv->rdrag;
	ac->weap.centre.drag=aspv->cdrag;
	ac->weap.left.drag=aspv->ldrag;

	for(n = 0; n < 4; n++)					
		ac->fly.fuel_content[n] = aspv->fuel_cont[n];	

	ac->weap.shpweapindex=aspv->shpweapindex;
	ac->weap.ShootDelay=aspv->ShootDelay;
	ac->weap.UseIntFuel=aspv->UseIntFuel;
	ac->weap.FuelDumped=aspv->FuelDumped;
	ac->weap.weapforce=aspv->weapforce;

	ac->weap.StoresDumped=aspv->StoresDumped;
	ac->weap.Ejected=aspv->Ejected;

	ac->fly.originalformpos=aspv->originalformpos;

	{
		ac->fly.nextflight=(AirStrucPtr)Persons2::ConvertPtrUID(aspv->nextflight);

		if (ac->fly.nextflight==Persons2::PlayerSeenAC)
			ac->fly.nextflight=Persons2::PlayerGhostAC;

		ac->fly.leadflight=(AirStrucPtr)Persons2::ConvertPtrUID(aspv->leadflight);

		if (ac->fly.leadflight==Persons2::PlayerSeenAC)
			ac->fly.leadflight=Persons2::PlayerGhostAC;
	}

	ac->fly.rpm=aspv->rpm;
	ac->fly.thrustpercent=aspv->thrustpercent;
	ac->fly.backupWP=(WayPointPtr)Persons2::ConvertPtrUID(aspv->backupWP);
	ac->fly.gforce=aspv->gforce;
	ac->fly.aileron=aspv->aileron;
	ac->fly.elevator=aspv->elevator;
	ac->fly.rudder=aspv->rudder;
	ac->fly.dhdg=aspv->dhdg;

	for (n=0;n<4;n++)
		ac->fly.use_this_tank[n]=aspv->use_this_tank[n];

	ac->fly.FuelCockPos=aspv->FuelCockPos;
	if(ac->fly.pModel)												
		ac->fly.pModel->FrameCount = aspv->FrameCount;				

	ac->lasthitter=aspv->lasthitter;
	ac->weap.Weapons=aspv->Weapons;
	ac->formpos=aspv->formpos;

	ac->formation=aspv->formation;
	ac->information=aspv->information;
	ac->slowdownleader=aspv->slowdownleader;
	ac->duty=aspv->duty;
	ac->advantage=aspv->advantage;
	ac->disadvantage=aspv->disadvantage;

	SetVelsAndOldVals(ac);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestorePrimaryASValues
//Date			Tue 29 Sep 1998
//------------------------------------------------------------------------------
void	Replay::RestorePrimaryMIValues(MobileItemPtr ac, LPMIPRIMARYVALUES mipv)
{

	ac->World=mipv->pos;

	ac->Status=mipv->Status;

	ac->hdg.a=mipv->hdg.a;
	ac->pitch.a=mipv->pitch.a;
	ac->roll.a=mipv->roll.a;
	ac->vel_=mipv->vel;

	ac->waypoint=(WayPointPtr)Persons2::ConvertPtrUID(mipv->waypoint);

	ac->movecode=mipv->movecode;

	ac->shape=mipv->shape;

	if (ac->Status.size>=FORMATIONSIZE)							
	{															
		FormationItemPtr fip=(FormationItemPtr)ac;				

		fip->leader=(FormationItemPtr)Persons2::ConvertPtrUID(mipv->leader);

		if (fip->leader==Persons2::PlayerSeenAC)				
			fip->leader=Persons2::PlayerGhostAC;				

		fip->follower=(FormationItemPtr)Persons2::ConvertPtrUID(mipv->follower);

		if (fip->follower==Persons2::PlayerSeenAC)				
			fip->follower=Persons2::PlayerGhostAC;				

		fip->manoeuvretime=mipv->manoeuvretime;
	}															

	if (ac==Persons2::PlayerSeenAC)
	{
		AirStrucPtr gac=Persons2::PlayerGhostAC;

		gac->Status=ac->Status;

		gac->World.X=ac->World.X;
		gac->World.Y=ac->World.Y;
		gac->World.Z=ac->World.Z;

		gac->hdg.a=ac->hdg.a;
		gac->pitch.a=ac->pitch.a;
		gac->roll.a=ac->roll.a;

		gac->vel_=ac->vel_;

		gac->movecode=mipv->movecode;
		gac->waypoint=(WayPointPtr)Persons2::ConvertPtrUID(mipv->waypoint);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadGamePrefs
//Date			Thu 1 Oct 1998
//------------------------------------------------------------------------------
Bool	Replay::LoadGamePrefs()
{
	if (!ReplayRead((UByte*)&Save_Data.flightdifficulty,sizeof(FlightDifficultyField)))
		return FALSE;

	if (!ReplayRead((UByte*)&Save_Data.gamedifficulty,sizeof(GameDifficultyField)))
		return FALSE;

	if (!ReplayRead((UByte*)&Save_Data.autopilotskillLW,sizeof(SWord)))
		return FALSE;

	if (!ReplayRead((UByte*)&Save_Data.autopilotskillRAF,sizeof(SWord)))
		return FALSE;

	if (!ReplayRead((UByte*)&Save_Data.targetsize,sizeof(TargetSize)))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreGamePrefs
//Date			Thu 1 Oct 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreGamePrefs()
{
	if (!ReplayWrite((UByte*)&Save_Data.flightdifficulty,sizeof(FlightDifficultyField)))
		return FALSE;

	if (!ReplayWrite((UByte*)&Save_Data.gamedifficulty,sizeof(GameDifficultyField)))
		return FALSE;

	if (!ReplayWrite((UByte*)&Save_Data.autopilotskillLW,sizeof(SWord)))
		return FALSE;

	if (!ReplayWrite((UByte*)&Save_Data.autopilotskillRAF,sizeof(SWord)))
		return FALSE;

	if (!ReplayWrite((UByte*)&Save_Data.targetsize,sizeof(TargetSize)))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreFinalRecordData
//Date			Thu 1 Oct 1998
//------------------------------------------------------------------------------
void	Replay::StoreFinalRecordData()
{
	Record=FALSE;

	StoreSuperHeaderEnd();
		
	if (StoreBlockHeader())
		Record=TRUE;

	if (Record)
		badrecord=false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadFinalPlaybackData
//Date			Thu 1 Oct 1998
//------------------------------------------------------------------------------
void	Replay::LoadFinalPlaybackData()
{
	Playback=FALSE;

	LoadSuperHeaderEnd();

	BackupPrefs(false);

	PreScanReplayFile();										

	if (LoadBlockHeader())
		Playback=TRUE;

	if (!Playback)
		_Error.EmitSysErr("Error reading playback log");

	Manual_Pilot.controlmode=ManualPilot::AUTO;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetAICount
//Date			Mon 5 Oct 1998
//------------------------------------------------------------------------------
void	Replay::ResetAICount()
{
	Art_Int.ACArrayInd=0;
	Art_Int.MemberListInd = -1;						
	Art_Int.CollideListInd = 0;						
	Art_Int.gunstimer=0;							
	Art_Int.exittimer=0;							
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RemoveAllTransients
//Date			Tue 6 Oct 1998
//------------------------------------------------------------------------------
void	Replay::RemoveAllTransients(Bool	totalremove)
{
	TransientItemPtr	temp=TransientItem::TransientList;

	while (temp)
	{
		temp->isOwned = 0;									
		temp->isArmed = 0;									
		Trans_Obj.AddTransientItemToDeadList(temp,true);	

		temp=temp->nexttrans;
	}

	if (totalremove)										
	{
		SHAPE.GenerateProbeTrails();								
		SHAPE.KillVapourStreamDeadList();							

		Trans_Obj.RemoveDeadListFromWorld();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopRecord
//Date			Wed 7 Oct 1998
//------------------------------------------------------------------------------
void	Replay::StopRecord(bool clear)
{
	if (Record)
	{
		if (clear)
			ClearReplayBuffers();
		StoreRealFrameCounts(replayframecount,0,replayframecount-1);
		Record=FALSE;
		CloseRecordLog();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetReplayFileName
//Date			Wed 7 Oct 1998
//------------------------------------------------------------------------------
void	Replay::GetReplayFileName()
{
	if (Record)
	{
		strcpy(rfilename,"replay.dat");

		GetReplayFilename(rfilename);
	}
	else
		GetReplayFilename(pfilename);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreSmkData
//Date			Wed 4 Nov 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreSmkData(LPREPLAYSMOKE smokey,UByteP pointlist)
{
// store each smoke trail in turn
	// Down sample smoke trail...and save...
	ReplaySmkPoint	SmokeList[12];
	Coords3DList*	apoint = (Coords3DList*) pointlist;
	Coords3DList*	npoint;
	SLong			index = 0;
	SLong			divvy = smokey->nopoints / 5;
	if (divvy)
	{
		SLong	howmany = divvy-1;
		SLong	counter = 0;

		while (apoint)
		{
			npoint = apoint;
			apoint = apoint->next;

			if (!apoint || !counter)
			{
				// Save this one...
				counter = howmany;

				if (!npoint->KillMe)
				{
					SmokeList[index].x = npoint->trailpoint.gx;
					SmokeList[index].y = npoint->trailpoint.gy;
					SmokeList[index].z = npoint->trailpoint.gz;
					SmokeList[index].lifeleft = npoint->lifeleft;
					SmokeList[index].radius = npoint->radius;
					SmokeList[index].LifeTime = npoint->LifeTime;
					SmokeList[index].FadeTime = npoint->FadeTime;
					SmokeList[index].KillMe = npoint->KillMe;
					index++;										
				}
			}
			else
				counter--;
		}
	}
	else
	{
		while (apoint)
		{
			//Save...
			if (!apoint->KillMe)								
			{
				SmokeList[index].x = apoint->trailpoint.gx;
				SmokeList[index].y = apoint->trailpoint.gy;
				SmokeList[index].z = apoint->trailpoint.gz;
				SmokeList[index].lifeleft = apoint->lifeleft;
				SmokeList[index].radius = apoint->radius;
				SmokeList[index].LifeTime = apoint->LifeTime;
				SmokeList[index].FadeTime = apoint->FadeTime;
				SmokeList[index].KillMe = apoint->KillMe;
				index++;
			}

			apoint = apoint->next;
		}
	}

	smokey->nopoints = index;
	if (!ReplayWrite((UByte*)smokey,sizeof(REPLAYSMOKE)))
		return FALSE;

	// Write it out backwards....so I can read back in the right order...
	while (index > 0)
	{
		index--;

		if (!ReplayWrite((UByteP)&SmokeList[index],sizeof(ReplaySmkPoint)))
			return FALSE;
	}

	return  TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSmkData
//Date			Wed 4 Nov 1998
//Description	//Need to cater for dummy smoke trails too!!
//------------------------------------------------------------------------------
Bool	Replay::LoadSmkData(LPREPLAYSMOKE smokey, Bool dummy, UByteP	&TrailListPtr)
{
	if (!SmokeRead(smokey,sizeof(REPLAYSMOKE)))
		return FALSE;

	Coords3DList*	apoint;
	Coords3DList*	baseptr = NULL;
	ReplaySmkPoint	smkpoint;
	int	i;
	for (i = 0; i < smokey->nopoints; i++)
	{
		if (!SmokeRead((UByte*)&smkpoint,sizeof(ReplaySmkPoint)))
			return FALSE;

		if (!dummy)
		{
			apoint = new Coords3DList;
			if (apoint)
			{
				apoint->trailpoint.gx = smkpoint.x;
				apoint->trailpoint.gy = smkpoint.y;
				apoint->trailpoint.gz = smkpoint.z;
				apoint->lifeleft = smkpoint.lifeleft;
				apoint->radius = smkpoint.radius;
				apoint->LifeTime = smkpoint.LifeTime;
				apoint->FadeTime = smkpoint.FadeTime;
				apoint->KillMe = smkpoint.KillMe;
				apoint->next = baseptr;

				baseptr = apoint;
			}
		}
	}

	TrailListPtr = (UByteP)baseptr;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreSmkIndexData
//Date			Wed 4 Nov 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreSmkIndexData(ULong index)
{
	if (!ReplayWrite((UByte*)&index,sizeof(ULong)))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSmkIndexData
//Date			Wed 4 Nov 1998
//------------------------------------------------------------------------------
Bool	Replay::LoadSmkIndexData(ULong& index)
{
	if (!SmokeRead(&index,sizeof(ULong)))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MarkBlockBeginning
//Date			Fri 6 Nov 1998
//------------------------------------------------------------------------------
void	Replay::MarkBlockBeginning()
{
	ULong tempb=currblock-1;
	UWord tempf=replayframecount;

	if (tempb==beginmark.blocknum && tempf==beginmark.framenum)
	{
// if this is current marked position

		if (beginmark.blocknum!=0 || (beginmark.blocknum==0 && beginmark.framenum!=0))
		{
// and its not start of replay then remove mark

			RemoveBeginningMark();
		}
	}
	else
	{
// cant put begin mark at end of replay, that would be silly

		if (!(currblock-1==EndBlockNum && replayframecount==EndFrameNum))
		{
// if begin mark is after end mark, end mark becomes eof

			if (currblock-1>endmark.blocknum 
			|| (currblock-1==endmark.blocknum && replayframecount>endmark.framenum))
			{
				RemoveEndMark();
			}

			beginmark.blocknum=currblock-1;
			beginmark.framenum=replayframecount;
			beginmark.memaddress=headmems[0][currblock-1];
		}
	}

	CalcBeginMarkPos();
	CalcEndMarkPos();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MarkBlockEnd
//Date			Fri 6 Nov 1998
//------------------------------------------------------------------------------
void	Replay::MarkBlockEnd()
{
	ULong tempb=currblock-1;
	UWord tempf=replayframecount;

	if (tempb==endmark.blocknum && tempf==endmark.framenum)
	{
// if this is current marked position

		if (endmark.blocknum!=EndBlockNum || (endmark.blocknum==EndBlockNum && endmark.framenum!=EndFrameNum))
		{
// and its not end of replay then remove mark

			RemoveEndMark();
		}
	}
	else
	{
// OY, I said NO, you cannot put an end mark at the beginning of replay!

		if (!(currblock-1==0 && replayframecount==BeginBlockFrame))
		{
// if end mark is before begin mark, remove begin mark

			if (currblock-1<beginmark.blocknum
			|| (currblock-1==beginmark.blocknum && replayframecount<beginmark.framenum))
			{
				RemoveBeginningMark();
			}

			endmark.blocknum=currblock-1;
			endmark.framenum=replayframecount;
			endmark.memaddress=headmems[1][currblock-1];
		}
	}
	CalcBeginMarkPos();
	CalcEndMarkPos();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RemoveMarks
//Date			Wed 11 Nov 1998
//------------------------------------------------------------------------------
void	Replay::RemoveMarks()
{
	RemoveBeginningMark();
	RemoveEndMark();

	CalcBeginMarkPos();
	CalcEndMarkPos();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SaveBlock
//Date			Fri 6 Nov 1998
//------------------------------------------------------------------------------
Bool	Replay::SaveBlock()
{
	HANDLE handy;
	char* newfile=new char[256];
	DWORD numtowrite,numwritten;
	DWORD totaltowrite=0,totalwritten=0;
	Bool	OK=FALSE;

	strcpy (newfile,"tblock.dat");
	GetReplayFilename(newfile);

// save block

	handy=CreateFile(
		newfile,
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,	// overwrite any existing file 
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (handy!=INVALID_HANDLE_VALUE)
	{
// need to save superheader! this is from beginning of recordfile to start
// of first block, which we have memory address for - phew!

		UByteP superstart,superend;
		ULong supersize;

		superstart=(UByteP)playbackfilestart;
		superend=headmems[0][0];

		supersize=superend-superstart;

		WriteFile(
			handy,
			superstart,
			supersize,
			&numwritten,
			NULL);

		totaltowrite=supersize;
		totalwritten=numwritten;

// need to alter start and end frames in block headers for this section and then restore
// after saving
// cant alter file, so copy file up to address to alter, write out new value, copy up till
// next alterable address, write value, then copy rest of file
// 5 sections
// 1st: copy file up to address that needs altering
// 2nd: write out new begin frame value
// 3rd: copy file from address after begin frame to address of new last frame value
// 4th: write out new last frame value
// 5th: copy file up to end address.

// get addresses that need altering

		UByteP here,start,end,src;

// end of block - headlength(ULong) - endframenum (UWord) - beginframenum (UWord)

		here=beginmark.memaddress+(headlength[beginmark.blocknum]-(sizeof(ULong)+(2*sizeof(UWord))));
		start=here;

// end of block - headlength(ULong) - endframenum (UWord)

		here=endmark.memaddress-((sizeof(ULong)+sizeof(UWord))+(numframes[endmark.blocknum]*sizeof(REPLAYPACKET)));
		end=here;

// 1st section

		src=beginmark.memaddress;
		numtowrite=start-beginmark.memaddress;

		WriteFile(
			handy,
			src,
			numtowrite,
			&numwritten,
			NULL);

		totaltowrite+=numtowrite;
		totalwritten+=numwritten;

// 2nd section

		src=(UByteP)&beginmark.framenum;
		numtowrite=sizeof(UWord);

		WriteFile(
			handy,
			src,
			numtowrite,
			&numwritten,
			NULL);

		totaltowrite+=numtowrite;
		totalwritten+=numwritten;

// 3rd section

		src=start+sizeof(UWord);
		numtowrite=end-src;

		WriteFile(
			handy,
			src,
			numtowrite,
			&numwritten,
			NULL);

		totaltowrite+=numtowrite;
		totalwritten+=numwritten;

// 4th section

		src=(UByteP)&endmark.framenum;
		numtowrite=sizeof(UWord);

		WriteFile(
			handy,
			src,
			numtowrite,
			&numwritten,
			NULL);

		totaltowrite+=numtowrite;
		totalwritten+=numwritten;

// 5th section

		src=end+sizeof(UWord);;
		numtowrite=endmark.memaddress-src;

		WriteFile(
			handy,
			src,
			numtowrite,
			&numwritten,
			NULL);

		CloseHandle(handy);

		totaltowrite+=numtowrite;
		totalwritten+=numwritten;

		if (totalwritten!=totaltowrite)
		{
			DeleteFile(newfile);
			_DPlay.CommsMessage(IDS_NOTWRITE);
		}
		else
		{
			OK=TRUE;
		}
	}

	delete [] newfile;

	if (OK)
		return TRUE;
	else
		return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetFlags
//Date			Wed 11 Nov 1998
//------------------------------------------------------------------------------
void	Replay::ResetFlags()
{
	ReplayFlag=RF_NONE;
	framestoskip=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DummyCrashSkid
//Date			Wed 28 Oct 1998
//------------------------------------------------------------------------------
void	Replay::DummyCrashSkid()
{
	AirStrucPtr			sac=Persons2::PlayerSeenAC;
	Bool				onWater = FALSE;
	AreaType			theArea;
	UByte				slowshift = 0;
	AircraftAnimData	*adptr = (AircraftAnimData*) sac->Anim;
	SLong				groundlevel = Land_Scape.GetGroundLevel(sac);
	WorldStuff &currworld = mobileitem::GetWorld();

	theArea = (AreaType)Three_Dee.GetLandType();
	if ( IsWater( theArea ) )
	{
		onWater = TRUE;
		slowshift = 2;
	}

	if (sac->vel_ <= 0)
	{
		_Miles.StopEngine();						

		SHAPE.DetatchAllVapourStreams(sac,0);
		adptr->hasdust = FALSE;

		if (onWater)
		{
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(sac->shape);
			SLong			size = sdptr->Size << 4;
			SLong			dist = sac->World.Y - groundlevel;

			//Sink...
			if (dist > -size)
			{
				if (dist < 0)
				{
					dist = size + dist;
				}
				else
					dist = size;

				Trans_Obj.LaunchBubbles(sac,dist,currworld);
			}
			else
				ReplayDeathMode = RDEATH_NULL;
		}
		else
		{
			// The end...
			ReplayDeathMode = RDEATH_NULL;
		}
	}
	else
	{
		if (onWater)
		{
			// Give it 4 seconds to knacker totally...
			UWord	damage = (BS_DEAD * sac->fly.pModel->CrashTime)/400;

			if (damage > BS_DEAD) damage = BS_DEAD;

			if (Math_Lib.rnd() > 32767)
			{
				if ((adptr->LEFTWINGIN < BS_DAMLV1) && (damage >= BS_DAMLV1))
					SHAPE.ForceDamage(sac,sac,&adptr->LEFTWINGIN,BS_DAMLV1);
				else
				{
					if ((adptr->LEFTWINGIN < BS_DAMLV2) && (damage >= BS_DAMLV2))
						SHAPE.ForceDamage(sac,sac,&adptr->LEFTWINGIN,BS_DAMLV2);
					else
					{
						if ((adptr->LEFTWINGIN < BS_DEAD) && (damage >= BS_DEAD))
							SHAPE.ForceDamage(sac,sac,&adptr->LEFTWINGIN,BS_DEAD);
					}
				}
			}
			else
			{
				if ((adptr->RIGHTWINGIN < BS_DAMLV1) && (damage >= BS_DAMLV1))
					SHAPE.ForceDamage(sac,sac,&adptr->RIGHTWINGIN,BS_DAMLV1);
				else
				{
					if ((adptr->RIGHTWINGIN < BS_DAMLV2) && (damage >= BS_DAMLV2))
						SHAPE.ForceDamage(sac,sac,&adptr->RIGHTWINGIN,BS_DAMLV2);
					else
					{
						if ((adptr->RIGHTWINGIN < BS_DEAD) && (damage >= BS_DEAD))
							SHAPE.ForceDamage(sac,sac,&adptr->RIGHTWINGIN,BS_DEAD);
					}
				}
			}
		}
	}

	sac->fly.pModel->CrashTime += Timer_Code.FRAMETIME;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DummyCrashRoll
//Date			Wed 28 Oct 1998
//------------------------------------------------------------------------------
void	Replay::DummyCrashRoll()
{
	AirStrucPtr			sac=Persons2::PlayerSeenAC;
	Bool				onWater = FALSE;
	AreaType			theArea;
	UByte				slowshift;
	AircraftAnimData	*adptr = (AircraftAnimData*) sac->Anim;
	Bool				rolldone, pitchdone;
	WorldStuff &currworld = mobileitem::GetWorld();


	slowshift = 4;
	theArea = (AreaType)Three_Dee.GetLandType();
	if ( IsWater( theArea ) )
	{
		onWater = TRUE;
		slowshift += 6;
	}

	SWord	tmproll, tmppitch;

	if (sac->vel_ > 0)
	{
		if (adptr->RIGHTWINGIN == BS_DEAD)						
		{
			tmproll = sac->roll;
			if (tmproll < -ANGLES_90Deg)
				SHAPE.ForceDamage(sac,sac,&adptr->LEFTWINGOUT,BS_DEAD);
		}
		else
		{
			if (adptr->LEFTWINGIN == BS_DEAD)						
			{
				tmproll = sac->roll;
				if (tmproll > ANGLES_90Deg)
					SHAPE.ForceDamage(sac,sac,&adptr->RIGHTWINGOUT,BS_DEAD);
			}
		}
	}
	else
	{
		SWord	maxangle = ANGLES_170Deg;
		bool	tipleft = false;

		_Miles.StopEngine();				

		SHAPE.DetatchAllVapourStreams(sac,0);			
		adptr->hasdust = FALSE;

		tmproll = sac->roll;
		tmppitch = sac->pitch;

		//Feeble gravity effect...
		//The bigger the angle, the slower it tips...

		if ((adptr->RIGHTWINGIN == BS_DEAD) && (tmproll < ANGLES_45Deg))
		{
			maxangle = ANGLES_0Deg;
			tipleft = true;
		}
		else
		{
			if ((adptr->LEFTWINGIN == BS_DEAD) && (tmproll > -ANGLES_45Deg))
				maxangle = ANGLES_0Deg;
			else
				tipleft = true;
		}

		if (tipleft == false)
		{
			if (tmproll >= maxangle)
				rolldone = TRUE;
			else
				rolldone = FALSE;
		}
		else
		{
			if (tmproll <= -maxangle)
				rolldone = TRUE;
			else
				rolldone = FALSE;
		}

		if (tmppitch < ANGLES_170Deg)
			pitchdone = FALSE;
		else
			pitchdone = TRUE;

		if (rolldone && pitchdone)
		{
			Trans_Obj.LaunchDirtMedium(sac,currworld);

			ReplayDeathMode = RDEATH_NULL;
		}
		else
			sac->fly.pModel->CrashTime += Timer_Code.FRAMETIME;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DummyCrashDive
//Date			Wed 28 Oct 1998
//------------------------------------------------------------------------------
void	Replay::DummyCrashDive()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreDeathMoveState
//Date			Thu 29 Oct 1998
//------------------------------------------------------------------------------
Bool	Replay::StoreDeathMoveState()
{
	UByte		effect = RDEATH_NULL;
	AirStrucPtr sac=Persons2::PlayerSeenAC;

	switch (sac->movecode)
	{
		case AUTO_HITWATER:
		case AUTO_CRASHSKID:
			effect = RDEATH_SKID;
			break;
		case AUTO_CRASHROLL:
			effect = RDEATH_ROLL;
			break;
		case AUTO_SPIRAL2GROUND:
		case AUTO_DEATHSEQUENCE:
			effect = RDEATH_DIVE;
			break;
	}

	// a byte......

	if (!ReplayWrite((UByte*)&effect,sizeof(UByte)))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadDeathMoveState
//Date			Thu 29 Oct 1998
//------------------------------------------------------------------------------
Bool	Replay::LoadDeathMoveState()
{
	UByte		effect = RDEATH_NULL;

	if (!ReplayRead((UByte*)&effect,sizeof(UByte)))
		return FALSE;

	ReplayDeathMode = (RDEATH)effect;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetRecord
//Date			Wed 18 Nov 1998
//------------------------------------------------------------------------------
void	Replay::ResetRecord()
{
	if (!Playback && !_DPlay.Implemented)
	{
		badrecord=true;
		SuperHeaderStored=false;
		DeleteReplayLog();
		if (Record)
		{
			ClearReplayBuffers();
			Record=FALSE;
			CloseRecordLog();
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ToggleRecord
//Date			Wed 18 Nov 1998
//------------------------------------------------------------------------------
void	Replay::ToggleRecord()
{
	if (Record)
	{
		StopRecord(true);
	}
	else
	{
		if (Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW)
		{
			StartRecordFlag=TRUE;
		}
	}
}

bool	Replay::ValidReplayFile()
{
	HANDLE f;
	bool ok=false;
	char	temp[256];

	strcpy(temp,pfilename);
	GetReplayFilename(temp);

	f=CreateFile(
		temp,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_TEMPORARY,
		NULL);

	if (f!=INVALID_HANDLE_VALUE)
		ok=true;

	ULong id=0,numread;

	ReadFile(
		f,
		&id,
		sizeof(ULong),
		&numread,
		NULL);

	if (id!=REPLAYSUPERHEADBEGINID)
		ok=false;

	if (!CloseHandle(f))
		ok=false;

	return ok;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginNewBlock
//Date			Thu 7 Jan 1999
//------------------------------------------------------------------------------
void	Replay::BeginNewBlock()
{
	StoreRealFrameCounts(replayframecount,0,replayframecount-1);
	StopRecord(true);												

	StartRecordFlag=TRUE;										
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreAeroDevData
//Date			Thu 7 Jan 1999
//------------------------------------------------------------------------------
Bool	Replay::StoreAeroDevData(AirStrucPtr ac)
{
	AERODEVVALUES a;

	PAERODEVICE pAeroDevice=ac->fly.pModel->DeviceList;

	while (pAeroDevice)
	{
		GetAeroDevData(&a,pAeroDevice);

		if (!ReplayWrite((UByte*)&a,sizeof(AERODEVVALUES)))
			return FALSE;

		pAeroDevice=pAeroDevice->List.NextItem();
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAeroDevData
//Date			Thu 7 Jan 1999
//------------------------------------------------------------------------------
void	Replay::GetAeroDevData(LPAERODEVVALUES adv,PAERODEVICE pad)
{
	adv->Val=pad->Val;
	adv->Attractor=pad->Attractor;
	adv->OldAttractor=pad->OldAttractor;

	adv->ReqVal=pad->ReqVal;
	adv->Broken=pad->Broken;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestoreAeroDevData
//Date			Thu 7 Jan 1999
//------------------------------------------------------------------------------
void	Replay::RestoreAeroDevData(LPAERODEVVALUES adv,PAERODEVICE pad)
{
	pad->Val=adv->Val;
	pad->Attractor=adv->Attractor;
	pad->OldAttractor=adv->OldAttractor;

	pad->ReqVal=adv->ReqVal;
	pad->Broken=adv->Broken;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreSuspensionData
//Date			Thu 7 Jan 1999
//------------------------------------------------------------------------------
Bool	Replay::StoreSuspensionData(AirStrucPtr ac)
{
	FP legpos;

	PGEAR pGear=ac->fly.pModel->GearList;

	while (pGear)
	{
		legpos=GetSuspensionData(pGear);

		if (!ReplayWrite((UByte*)&legpos,sizeof(FP)))
			return FALSE;

	 	pGear = pGear->List.NextItem();
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSuspensionData
//Date			Thu 7 Jan 1999
//------------------------------------------------------------------------------
FP	Replay::GetSuspensionData(PGEAR pGear)
{
	return pGear->LegPos;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestoreSuspensionData
//Date			Thu 7 Jan 1999
//------------------------------------------------------------------------------
void	Replay::RestoreSuspensionData(FP legpos,PGEAR pGear)
{
	pGear->LegPos=legpos;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSuperHeader
//Date			Tue 12 Jan 1999
//------------------------------------------------------------------------------
Bool	Replay::LoadSuperHeader()
{
	if (!LoadSuperHeaderBeginning())
		return FALSE;

	if (!LoadSuperHeaderEnd())
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSuperHeaderBeginning
//Date			Tue 12 Jan 1999
//------------------------------------------------------------------------------
Bool	Replay::LoadSuperHeaderBeginning()
{
	if (!LoadSuperHeaderID())
		return FALSE;

	if (!LoadSaveGame())												
		return FALSE;													

	if (!LoadGRRandomList())
		return FALSE;

	if (!LoadInitialGlobRefs())
		return FALSE;

	if (!LoadFileAndGlobRefList())
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSuperHeaderEnd
//Date			Tue 12 Jan 1999
//------------------------------------------------------------------------------
Bool	Replay::LoadSuperHeaderEnd()
{
	if (!LoadSuperHeaderEndID())
		return FALSE;

	SuperHeaderSize=playbackfilepos-(UByteP)playbackfilestart;

	if (!RestorePosition)
	{
		CurrPos=0;
		BeginMarkPos=0;
		EndMarkPos=255;
	}

	return TRUE;
}

Bool	Replay::StoreSuperHeader()
{
	if (!StoreSuperHeaderBeginning())
		return FALSE;

	if (!StoreSuperHeaderEnd())
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreSuperHeaderBeginning
//Date			Tue 12 Jan 1999
//------------------------------------------------------------------------------
Bool	Replay::StoreSuperHeaderBeginning()
{
	if (SuperHeaderStored)
		return TRUE;

	if (!StoreSuperHeaderID())
		return FALSE;

	if (!StoreSaveGame())												
		return FALSE;													

	if (!StoreGRRandomList())
		return FALSE;

	if (!StoreInitialGlobRefs())
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreSuperHeaderEnd
//Date			Tue 12 Jan 1999
//------------------------------------------------------------------------------
Bool	Replay::StoreSuperHeaderEnd()
{
	if (SuperHeaderStored)
		return TRUE;

 	if (!StoreFileAndGlobRefList())
		return FALSE;

	if (!StoreSuperHeaderEndID())
		return FALSE;

	SuperHeaderStored=true;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSuperHeaderID
//Date			Tue 12 Jan 1999
//------------------------------------------------------------------------------
Bool	Replay::LoadSuperHeaderID()
{
	ULong id=0;

	if (!ReplayRead((UByte*)&id,sizeof(ULong)))
		return FALSE;

	if (id!=REPLAYSUPERHEADBEGINID)
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreSuperHeaderID
//Date			Tue 12 Jan 1999
//------------------------------------------------------------------------------
Bool	Replay::StoreSuperHeaderID()
{
	ULong id=REPLAYSUPERHEADBEGINID;

	if (!ReplayWrite((UByte*)&id,sizeof(ULong)))
		return FALSE;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreBlockHeader
//Date			Tue 12 Jan 1999
//------------------------------------------------------------------------------
Bool	Replay::StoreBlockHeader()
{
	ULong size1=GetFileSize(recordstorage,NULL),size2,len;
	ULong size3,size4;

	ResetAICount();
	_DPlay.ResetDeltas();											

	SetWaypointData();											

	if (!StoreHeaderID())
		return FALSE;

	if (!StoreACArray())
		return FALSE;

	if (!StoreTimeOfDay())
		return FALSE;

	if (!StoreRandomList())
		return FALSE;

	if (!StoreGamePrefs())
		return FALSE;

	if (!StoreDeadItems())
		return FALSE;

	if (!StoreSagGlobs())
		return FALSE;

	if (!StoreItemData())
		return FALSE;

	if (!StoreItemAnims())
		return FALSE;

	if (!StoreAAAList())												
		return FALSE;												  	

	if (!StoreArmedTransients())								
		return FALSE;											

	if (!StoreDeathMoveState())
		return FALSE;

// smoke trails to...........
	size3=0;
	if (!ReplayWrite((UByte*)&size3,sizeof(ULong)))
		return FALSE;

	size3=GetFileSize(recordstorage,NULL);

	if (!SHAPE.SampleTrailList())
		return FALSE;

	size4=GetFileSize(recordstorage,NULL);
	len=size4-size3;

	if (!StoreSmokeSize(len))
		return FALSE;
//.............here


// smoke clouds to.........
	size3=0;
	if (!ReplayWrite((UByte*)&size3,sizeof(ULong)))
		return FALSE;

	size3=GetFileSize(recordstorage,NULL);

	if (!StoreSmokeClouds())
		return FALSE;

	size4=GetFileSize(recordstorage,NULL);
	len=size4-size3;

	if (!StoreSmokeSize(len))
		return FALSE;
//........here

	if (!StorePrevPosBuffer())
		return FALSE;

	if (!StoreHeaderEndID())
		return FALSE;

// NOTE:: these must be stored last because when block ends file pointer is rewound to position
// and frame counts filled in, if there is data after them then I dont know how far to rewind

	if (!StoreInitFrameCounts())
		return FALSE;

	size2=GetFileSize(recordstorage,NULL);

	len=size2-size1;

	if (!StoreHeaderLength(len))
		return FALSE;

	replayframecount=0;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadBlockHeader
//Date			Tue 12 Jan 1999
//------------------------------------------------------------------------------
Bool	Replay::LoadBlockHeader()
{
	ULong n;

	ResetAICount();
	_DPlay.ResetDeltas();											  

	SetWaypointData();												

	headmems[0][currblock]=playbackfilepos;

	if (!LoadHeaderID())
		return FALSE;

	if (!LoadACArray())
		return FALSE;

	if (DoSmokeTrailStuff)
		UpdateLandscape=true;

	if (!LoadTimeOfDay())
		return FALSE;

// OK, in alot of places when skipping about the transients need to be removed from world
// before new smoke trails etc can be launched. The only time this should not happen is
// during normal playback in which case smoke trail stuff is not done

	if (DoSmokeTrailStuff)		
	{
		RemoveAllTransients();
		Land_Scape.WipeSmokeClouds();
	}

	if (!LoadRandomList())
		return FALSE;
			   
	if (!LoadGamePrefs())
		return FALSE;

	if (DoSmokeTrailStuff)		
		ResetItemAnim();		

	if (!LoadDeadItems())
		return FALSE;

	if (!LoadSagGlobs())
		return FALSE;

	if (!LoadItemData())
		return FALSE;

	if (!LoadItemAnims())
		return FALSE;

	if (!LoadAAAList())									
		return FALSE;									

	if (!LoadArmedTransients())							
		return FALSE;									

	if (!LoadDeathMoveState())
		return FALSE;

	if (!BackupSmokeInfo())
		return FALSE;

	if (DoSmokeTrailStuff)
	{
		processsmokes=true;
	}
	else
	{
		if (!SHAPE.GetSmokeTrailList(TRUE))
			return FALSE;
	}

	if (!BackupCloudInfo())
		return FALSE;

	if (!DoSmokeTrailStuff)
	{
		if (!LoadSmokeClouds(true))
			return FALSE;
	}

	if (!LoadPrevPosBuffer())
		return FALSE;

	if (!LoadHeaderEndID())
		return FALSE;

	if (!LoadFrameCounts())
		return FALSE;

	n=LoadHeaderLength();

	if (n==0)
		return FALSE;

	currblock++;

	if (currblock>numblocks)
	{

		if (emptyblock)
		{
			numframes[numblocks]=0;
			headmems[1][currblock-1]=playbackfilepos;
			markers[0][currblock-1]=0;
			markers[1][currblock-1]=0;
		}
		else
		{
			markers[0][currblock-1]=thisblockstartframe;
			markers[1][currblock-1]=thisblockendframe;
			numframes[numblocks]=thisblocknumframes;
			headmems[1][currblock-1]=(playbackfilepos+(thisblocknumframes*sizeof(REPLAYPACKET)));
		}
		headlength[numblocks++]=n;
	}

	replayframecount=0;

	if (thisblockstartframe!=0)
	{
		ReplayFlag=RF_SKIPFRAMES;			
		framestoskip=thisblockstartframe;
	}

	_DPlay.BackupSeen();
	_DPlay.BackupGhost();

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BackupPlaybackPosition
//Date			Mon 18 Jan 1999
//------------------------------------------------------------------------------
void	Replay::BackupPlaybackPosition()
{
	backupblock=currblock-1;
	backupframe=replayframecount;
	RestorePosition=true;
	backupstate=GetState();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestorePlaybackPosition
//Date			Mon 18 Jan 1999
//------------------------------------------------------------------------------
void	Replay::RestorePlaybackPosition()
{
	ULong n;

	RestorePosition=false;

	for (n=0;n<backupblock;n++)
	{
		BlockForward();
	}

	framestoskip=backupframe;
	ReplayFlag=RF_SKIPFRAMES;

	SetState(backupstate);

	_DPlay.BackupGhost();
	_DPlay.BackupSeen();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSaveGame
//Date			Mon 18 Jan 1999
//------------------------------------------------------------------------------
bool	Replay::LoadSaveGame()
{
	ULong size,temp;
	char	dummyname[150];
	HANDLE	dummyfile;
	bool retval;
	ULong	tempstate;

	if (!ReplayRead((UByte*)&tempstate,sizeof(ULong)))
		return FALSE;

	PlaybackGameState=GetState();

	if (!IsCampState(tempstate))
	{
		if (!LoadCampaignStruc())
			return FALSE;
		return TRUE;
	}

	if (!ReplayRead((UByte*)&size,sizeof(ULong)))
		return FALSE;

	UByteP	savedata=new UByte[size];

	if (ReplayRead(savedata,size))
	{
		strcpy(dummyname,replaysavebackup);

		_DPlay.GetCommsSavename(dummyname);

		dummyfile=CreateFile(
			dummyname,
			GENERIC_WRITE,
			FILE_SHARE_WRITE,
			NULL,
			CREATE_ALWAYS,
			NULL,
			NULL);

		if (dummyfile!=INVALID_HANDLE_VALUE)
		{
			WriteFile(
				dummyfile,
				savedata,
				size,
				&temp,
				NULL);

			CloseHandle(dummyfile);

// load game here

			Persons4::ShutDownMapWorld();
			retval=_DPlay.LoadDummySavegame(replaysavebackup);
			Todays_Packages.SaveBin();
			Persons4::ShutDownMapWorld();
		}
		else
			retval=FALSE;

	}
	else 
		retval=FALSE;

	delete savedata;

	Todays_Packages.BuildReorderTable();

	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreSaveGame
//Date			Mon 18 Jan 1999
//------------------------------------------------------------------------------
Bool	Replay::StoreSaveGame()
{
	ULong	savesize,numread;
	char savedgamename[150];
	HANDLE	savegame;
	Bool	retval=FALSE;
	ULong	tempstate;

	tempstate=GetState();

	if (!ReplayWrite((UByte*)&tempstate,sizeof(ULong)))
		return FALSE;

	if (!IsCampState(tempstate))
	{
		if (!StoreCampaignStruc())
			return FALSE;
		return TRUE;
	}

	strcpy(savedgamename,replaysavebackup);
	_DPlay.GetCommsSavename(savedgamename);

	savegame=CreateFile(
		savedgamename,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL);

	if (savegame!=INVALID_HANDLE_VALUE)
	{
		savesize=GetFileSize(savegame,NULL);

		if (ReplayWrite((UByte*)&savesize,sizeof(ULong)))
		{
			UByteP save=new UByte[savesize];

			ReadFile(
				savegame,
				save,
				savesize,
				&numread,
				NULL);

			if (ReplayWrite(save,savesize))
			{
				retval=TRUE;
			}
			
			delete [] save;
		}
		CloseHandle(savegame);
	}

	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BackupSaveGame
//Date			Fri 22 Jan 1999
//------------------------------------------------------------------------------
bool	Replay::BackupSaveGame()
{
	return (SaveTempSaveGame("rbackup.dat"));//,true));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestoreSaveGame
//Date			Fri 22 Jan 1999
//------------------------------------------------------------------------------
bool	Replay::RestoreSaveGame()
{
	ULong	tempstate;

	tempstate=GetState();

	if (IsCampState(tempstate))
	{
		return (_DPlay.LoadDummySavegame("rbackup.dat"));
	}

	return true;
}

void	Replay::ResetReplayView()
{
	Trans_Obj.View_Object->SetToPiloted((itemptr)Persons2::PlayerSeenAC,true);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetVelsAndOldVals
//Date			Mon 8 Feb 1999
//------------------------------------------------------------------------------
void	Replay::SetVelsAndOldVals(AirStrucPtr ac)
{
	ac->ai.oldpitchI=ANGLES_0Deg;

	if (ac->uniqueID.count<SagBANDEND)
		ac->ai.oldoldpitchI=ANGLES_0Deg;

	ac->ai.oldoldoldpitchI=ANGLES_0Deg;
	ac->ai.oldhdgI=ANGLES_0Deg;
	ac->ai.oldoldhdgI=ANGLES_0Deg;
	ac->ai.oldoldoldhdgI=ANGLES_0Deg;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SkipToBeginningMark
//Date			Wed 17 Feb 1999
//------------------------------------------------------------------------------
void	Replay::SkipToBeginningMark()
{
	ULong n;

	currblock=0;
	playbackfilepos=(UByteP)playbackfilestart+SuperHeaderSize;
	LoadBlockHeader();

	for (n=0;n<beginmark.blocknum;n++)
	{
		BlockForward();
	}

	framestoskip=beginmark.framenum;
	ReplayFlag=RF_SKIPFRAMES;
	ResetReplayView();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SkipToEndMark
//Date			Wed 17 Feb 1999
//------------------------------------------------------------------------------
void	Replay::SkipToEndMark()
{
	ULong n;

	currblock=0;
	playbackfilepos=(UByteP)playbackfilestart+SuperHeaderSize;
	LoadBlockHeader();

	for (n=0;n<endmark.blocknum;n++)
	{
		BlockForward();
	}

	framestoskip=endmark.framenum;
	ReplayFlag=RF_SKIPFRAMES;
	ResetReplayView();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RemoveBeginningMark
//Date			Wed 17 Feb 1999
//------------------------------------------------------------------------------
void	Replay::RemoveBeginningMark()
{
// 1st block beginning becomes start of marked block

	beginmark.memaddress=(UByteP)playbackfilestart+SuperHeaderSize;
	beginmark.blocknum=0;
	beginmark.framenum=BeginBlockFrame;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RemoveEndMark
//Date			Wed 17 Feb 1999
//------------------------------------------------------------------------------
void	Replay::RemoveEndMark()
{
// end block end becomes end of marked block

	endmark.memaddress=(UByteP)playbackfileend;
	endmark.blocknum=EndBlockNum;
	endmark.framenum=EndFrameNum;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreScanReplayFile
//Date			Wed 17 Feb 1999
//------------------------------------------------------------------------------
void	Replay::PreScanReplayFile()
{
/* Info needed:

	1: Total number of frames in replay file
	2: Total number of blocks
	3: Number of frames in last block
*/

	ULong n=0,skip;
	UByteP here=playbackfilepos;

	prescan=true;

	TotalFrames=0;

	if (!RestorePosition)
	{
		beginmark.memaddress=here;
		beginmark.blocknum=0;
	}

	DoSmokeTrailStuff=FALSE;

	while (LoadBlockHeader())
	{
		if (!n)
		{
			BeginBlockFrame=thisblockstartframe;

			if (!RestorePosition)
			{
				beginmark.framenum=thisblockstartframe;
			}
		}

		EndBlockNum=n;
		EndFrameNum=thisblockendframe+1;
		if (!emptyblock)
		{
			TotalFrames+=(numframes[n]-thisblockstartframe)-(numframes[n]-thisblockendframe);
			skip=sizeof(REPLAYPACKET)*numframes[n];

// skip to next block

			playbackfilepos+=skip;
		}
		n++;
	}
	
	prescan=false;
	
// should never happen, but best to be sure

	if (!TotalFrames)
		TotalFrames=1; 

	if (!RestorePosition)
	{
		endmark.memaddress=(UByteP)playbackfileend;
		endmark.blocknum=EndBlockNum;
		endmark.framenum=EndFrameNum;
	}

	playbackfilepos=here;
	currblock=0;

	DoSmokeTrailStuff=TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SkipToPreviousMark
//Date			Thu 18 Feb 1999
//------------------------------------------------------------------------------
void	Replay::SkipToPreviousMark()
{
/*
1: if position is at end of file and end marker is at end skip to begin mark
2: if position is at end of file and end marker is not at end skip to end mark
3: if position is between end mark and end of file skip to end mark
4: if position is at end mark skip to begin mark
5: if position is between begin mark and end mark skip to begin mark
6: if position is at begin mark skip to beginning of file
7: if position is between beginning of file and begin mark skip to beginning of file
8: if position is at beginning of file ignore

9: if position is up to 1 sec after end mark skip to beginning mark
10:if position is up to 1 sec after begin mark skip to beginning
*/

	if ((currblock-1)<beginmark.blocknum 
	|| ((currblock-1)==beginmark.blocknum && replayframecount<=beginmark.framenum+1))
	{
		SkipToBeginning();
	}
	else if ((currblock-1)<endmark.blocknum
	|| ((currblock-1)==endmark.blocknum && replayframecount<=endmark.framenum+1))
	{
// after begin mark and before end mark
// if up to 1 sec after begin mark then skip to begining else to begin mark

		ULong framediff=0;
		if (currblock-1==beginmark.blocknum)
		{
			framediff=replayframecount-beginmark.framenum+1;
		}
		else
		{
			ULong block=beginmark.blocknum;

			framediff=markers[1][beginmark.blocknum]-beginmark.framenum+1;
			block++;

			while (block!=currblock-1)
			{
// intermediate blocks between beginmark and currentposition

				framediff+=numframes[currblock-1]
					-(markers[1][block]-markers[0][block]);
				block++;
			}

			framediff+=replayframecount-markers[0][block];
		}

		if (framediff<50) // less than 1 sec after begin mark
			SkipToBeginning();
		else
			SkipToBeginningMark();
	}
	else if ((currblock-1)>endmark.blocknum
	|| (currblock-1==endmark.blocknum && replayframecount>endmark.framenum+1))
	{
// after end mark
// if up to 1 sec after end mark skip to begin mark else end mark

		ULong framediff=0;
		if (currblock-1==endmark.blocknum)
		{
			framediff=replayframecount-endmark.framenum+1;
		}
		else
		{
			ULong block=endmark.blocknum;

			framediff=markers[1][endmark.blocknum]-endmark.framenum+1;
			block++;

			while (block!=currblock-1)
			{
// intermediate blocks between endmark and currentposition

				framediff+=numframes[currblock-1]
					-(markers[1][block]-markers[0][block]);
				block++;
			}

			framediff+=replayframecount-markers[0][block];
		}

		if (framediff<50) // less than 1 sec after end mark
			SkipToBeginningMark();
		else
			SkipToEndMark();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SkipToEndMark
//Date			Thu 18 Feb 1999
//------------------------------------------------------------------------------
void	Replay::SkipToNextMark()
{
// reverse of above

	if ((currblock-1)>endmark.blocknum
	|| ((currblock-1)==endmark.blocknum && replayframecount>=endmark.framenum))
	{
		SkipToEnd();
	}
	else if ((currblock-1)>beginmark.blocknum
	|| ((currblock-1)==beginmark.blocknum && replayframecount>=beginmark.framenum))
	{
		SkipToEndMark();
	}
	else
	{
		SkipToBeginningMark();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcBeginMarkPos
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
void	Replay::CalcBeginMarkPos()
{
	ULong n,total=0;
	SLong temp;

	for (n=0;n<beginmark.blocknum;n++)
	{
		if (numframes[n])
			total+=(numframes[n]-((markers[1][n]+1)-numframes[n])-markers[0][n]);
	}

	total+=beginmark.framenum-markers[0][n];

	temp=(total*255)/TotalFrames;

	if (temp<0)
		temp=0;
	else if (temp>255)
		temp=255;

	BeginMarkPos=temp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcEndMarkPos
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
void	Replay::CalcEndMarkPos()
{
	ULong n,total=0;
	SLong temp;

	for (n=0;n<endmark.blocknum;n++)
	{
		if (numframes[n])
			total+=(numframes[n]-((markers[1][n]+1)-numframes[n])-markers[0][n]);
	}

	total+=endmark.framenum-markers[0][n];

	temp=(total*255)/TotalFrames;

	if (temp<0)
		temp=0;
	else if (temp>255)
		temp=255;

	EndMarkPos=temp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcCurrPos
//Date			Fri 19 Feb 1999
//------------------------------------------------------------------------------
void	Replay::CalcCurrPos()
{
	ULong n,total=0;
	SLong	temp;

	for (n=0;n<currblock-1;n++)
	{
		if (numframes[n])
			total+=(numframes[n]-((markers[1][n]+1)-numframes[n])-markers[0][n]);
	}

	total+=replayframecount-markers[0][currblock-1];

	temp=(total*255)/TotalFrames;

	if (temp<0)
		temp=0;
	else if (temp>255)
		temp=255;

	CurrPos=temp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreSmlSmkData
//Date			Thu 18 Feb 1999
//------------------------------------------------------------------------------
Bool	Replay::StoreSmlSmkData(ReplaySmlSmkStruc *smokey,UByteP pointlist)
{
	ReplaySmkPoint	*SmokeList = new ReplaySmkPoint[smokey->nopoints];
	Coords3DList*	apoint = (Coords3DList*) pointlist;
	SLong			index = 0;
	Bool			retval = TRUE;

	while (apoint)
	{
		SmokeList[index].x = apoint->trailpoint.gx;
		SmokeList[index].y = apoint->trailpoint.gy;
		SmokeList[index].z = apoint->trailpoint.gz;
		SmokeList[index].lifeleft = apoint->lifeleft;
		SmokeList[index].radius = apoint->radius;
		SmokeList[index].LifeTime = apoint->LifeTime;
		SmokeList[index].FadeTime = apoint->FadeTime;
		SmokeList[index].KillMe = apoint->KillMe;
		index++;

		apoint = apoint->next;
	}

	if (!ReplayWrite((UByte*)smokey,sizeof(ReplaySmlSmkStruc)))
		retval = FALSE;
	else
	{
		// Write it out backwards....so I can read back in the right order...
		while (index > 0)
		{
			index--;
			if (!ReplayWrite((UByteP)&SmokeList[index],sizeof(ReplaySmkPoint)))
			{
				retval = FALSE;
				break;
			}
		}
	}

	delete[]SmokeList;

	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSmlSmkData
//Date			Thu 18 Feb 1999
//------------------------------------------------------------------------------
Bool	Replay::LoadSmlSmkData(ReplaySmlSmkStruc *smokey, Bool dummy, UByteP	&TrailListPtr, Coords3D& cpos)
{
	if (!SmokeRead((UByte*)smokey,sizeof(ReplaySmlSmkStruc)))
		return FALSE;

	Coords3DList*	apoint;
	Coords3DList*	baseptr = NULL;
	ReplaySmkPoint	smkpoint;
	int	i;

	cpos.X = cpos.Y = cpos.Z = 0;

	for (i = 0; i < smokey->nopoints; i++)
	{
		if (!SmokeRead((UByte*)&smkpoint,sizeof(ReplaySmkPoint)))
			return FALSE;

		if (!dummy)
		{
			apoint = new Coords3DList;
			if (apoint)
			{
				cpos.X += smkpoint.x;
				cpos.Y += smkpoint.y;
				cpos.Z += smkpoint.z;

				apoint->trailpoint.gx = smkpoint.x;
				apoint->trailpoint.gy = smkpoint.y;
				apoint->trailpoint.gz = smkpoint.z;
				apoint->lifeleft = smkpoint.lifeleft;
				apoint->radius = smkpoint.radius;
				apoint->LifeTime = smkpoint.LifeTime;
				apoint->FadeTime = smkpoint.FadeTime;
				apoint->KillMe = smkpoint.KillMe;
				apoint->next = baseptr;

				baseptr = apoint;
			}
		}
	}

	TrailListPtr = (UByteP)baseptr;
	if (smokey->nopoints)
	{
		cpos.X /= smokey->nopoints;
		cpos.Y /= smokey->nopoints;
		cpos.Z /= smokey->nopoints;
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateSmokes
//Date			Thu 25 Feb 1999
//------------------------------------------------------------------------------
void	Replay::UpdateSmokes()
{
	UWord sector=MobileItem::currworld->GetSector(Persons2::PlayerSeenAC);

	ItemPtr next=MobileItem::currworld->getfirstitem(sector);

	while (next)
	{
		SHAPE.replay_animate_shape(next);
		next=next->Next;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadFMMass
//Date			Fri 5 Mar 1999
//------------------------------------------------------------------------------
bool	Replay::LoadFMMass(AirStrucPtr ac)
{
	FP m;

	if (!ReplayRead((UByteP)&m,sizeof(FP)))
		return false;

	if (!prescan)
		ac->fly.pModel->Mass=m;

	return true; 
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreFMMass
//Date			Fri 5 Mar 1999
//------------------------------------------------------------------------------
bool	Replay::StoreFMMass(AirStrucPtr ac)
{
	FP m=ac->fly.pModel->Mass;

	if (!ReplayWrite((UByteP)&m,sizeof(FP)))
		return false;

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearReplayBuffers
//Date			Wed 17 Mar 1999
//------------------------------------------------------------------------------
void	Replay::ClearReplayBuffers()
{
	BASICPACKET packet;
	UByteP ptr;

	while (_DPlay.CollBuffer.NumEntries())
	{
		_DPlay.MakeCollPacket (&packet, 0);

		ptr=(UByteP)&packet.IDCode;

	 	_DPlay.ProcessCollisionPacket(ptr,Persons2::PlayerSeenAC,0);
	}

	while (_DPlay.UIDSBuffer.NumEntries())
	{
		_DPlay.MakeUIDSPacket(&packet,0);

		ptr=(UByteP)&packet.IDCode;

		_DPlay.ProcessUIDSPacket(ptr,0);
	}

	while (_DPlay.SpecBuffer.NumEntries())
	{
		_DPlay.MakeSpecialPacket(&packet,0);

		ptr=(UByteP)&packet.IDCode;

		_DPlay.ProcessSpecialPacket(ptr,Persons2::PlayerSeenAC,0);
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitPosBuffer
//Date			Fri 19 Mar 1999
//------------------------------------------------------------------------------
void	Replay::InitPosBuffer()
{
// initial last position are starting position

	PosBuffer.InitBuffer();
	PosBuffer.SetTempCurr();

	SWord num=POSBSIZE-1;
	SLong vx=Persons2::PlayerGhostAC->vel_x; 
	SLong vy=Persons2::PlayerGhostAC->vel_y; 
	SLong vz=Persons2::PlayerGhostAC->vel_z; 

	SLong wx, wy, wz;												
	MMC.Sky.GetWind(Persons2::PlayerGhostAC->World.Y, wx, wy, wz);	
	vx += wx;														
	vy += wy;														
	vz += wz;														

	COORDS3D	pos;
	COORDS3D	acpos=Persons2::PlayerGhostAC->World;

	do
	{
		pos.X=acpos.X-((num*vx)/5000);
		pos.Y=acpos.Y-((num*vy)/5000);
		pos.Z=acpos.Z-((num*vz)/5000);
		num--;

		*PosBuffer.GetTemp()=pos;

		PosBuffer.UpdateTemp();
	}
	while (PosBuffer.GetTemp()!=PosBuffer.GetCurr());

// get to last pos in buffer

	for (int n=0;n<POSBSIZE-1;n++)
		PosBuffer.UpdateNext();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StorePrevPosBuffer
//Date			Fri 19 Mar 1999
//------------------------------------------------------------------------------
bool	Replay::StorePrevPosBuffer()
{
	PosBuffer.SetTempCurr();

	do
	{
		if (!ReplayWrite((UByte*)&(*PosBuffer.GetTemp()),sizeof(COORDS3D)))
			return false;

		PosBuffer.UpdateTemp();
	}
	while (PosBuffer.GetTemp()!=PosBuffer.GetCurr());

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadPrevPosBuffer
//Date			Fri 19 Mar 1999
//------------------------------------------------------------------------------
bool	Replay::LoadPrevPosBuffer()
{
	PosBuffer.InitBuffer();									

	for (int n=0;n<POSBSIZE-1;n++)							
		PosBuffer.UpdateNext();								

	PosBuffer.SetTempCurr();

	do
	{
		if (!ReplayRead((UByte*)&(*PosBuffer.GetTemp()),sizeof(COORDS3D)))
			return false;

		PosBuffer.UpdateTemp();
	}
	while (PosBuffer.GetTemp()!=PosBuffer.GetCurr());

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdatePosBuffer
//Date			Fri 19 Mar 1999
//------------------------------------------------------------------------------
void	Replay::UpdatePosBuffer()
{
	*PosBuffer.GetNext()=Persons2::PlayerGhostAC->World;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreHeaderEndID
//Date			Wed 31 Mar 1999
//------------------------------------------------------------------------------
bool	Replay::StoreHeaderEndID()
{
	ULong id=REPLAYHEADENDID;

	if (!ReplayWrite((UByte*)&id,sizeof(ULong)))
		return false;

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreSuperHeaderEndID
//Date			Wed 31 Mar 1999
//------------------------------------------------------------------------------
bool	Replay::StoreSuperHeaderEndID()
{
	ULong id=REPLAYSUPERHEADENDID;

	if (!ReplayWrite((UByte*)&id,sizeof(ULong)))
		return false;

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadHeaderEndID
//Date			Wed 31 Mar 1999
//------------------------------------------------------------------------------
bool	Replay::LoadHeaderEndID()
{
	ULong id=0;

	if (!ReplayRead((UByte*)&id,sizeof(ULong)))
		return false;

	if (id!=REPLAYHEADENDID)
		return false;

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSuperHeaderEndID
//Date			Wed 31 Mar 1999
//------------------------------------------------------------------------------
bool	Replay::LoadSuperHeaderEndID()
{
	ULong id=0;

	if (!ReplayRead((UByte*)&id,sizeof(ULong)))
		return false;

	if (id!=REPLAYSUPERHEADENDID)
		return false;

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BackupSmokeInfo
//Date			Tue 20 Apr 1999
//------------------------------------------------------------------------------
bool	Replay::BackupSmokeInfo()
{
	ULong smokesize;

	if (!ReplayRead((UByte*)&smokesize,sizeof(ULong)))
		return false;

	delete [] backupsmoke;
	backupsmoke=NULL;

	backupsmoke=new UByte[smokesize];
	tempbackupsmoke=backupsmoke;

	if (!backupsmoke)
		return false;

	if (!ReplayRead(backupsmoke,smokesize))
		return false;

	return true;
}

bool	Replay::BackupCloudInfo()
{
	ULong cloudsize;

	if (!ReplayRead((UByte*)&cloudsize,sizeof(ULong)))
		return false;

	delete [] backupcloud;
	backupcloud=NULL;

	backupcloud=new UByte[cloudsize];
	tempbackupcloud=backupcloud;

	if (!backupcloud)
		return false;

	if (!ReplayRead(backupcloud,cloudsize))
		return false;

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateSmokeyInfo
//Date			Tue 20 Apr 1999
//------------------------------------------------------------------------------
void	Replay::UpdateSmokeInfo()
{
	ULong n;

	SHAPE.DeleteAllSmokeTrails();

	SHAPE.GetSmokeTrailList(FALSE);

	_Replay.LoadSmokeClouds(false);

	processsmokes=false;

	delete [] backupsmoke;
	backupsmoke=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SmokeRead
//Date			Tue 20 Apr 1999
//------------------------------------------------------------------------------
bool	Replay::SmokeRead(void* dest, ULong size)
{
	CopyMemory(dest,tempbackupsmoke,size);
	tempbackupsmoke+=size;

	return true;
}

bool	Replay::CloudRead(void* dest, ULong size)
{
	CopyMemory(dest,tempbackupcloud,size);
	tempbackupcloud+=size;

	return true;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreSmokeSize
//Date			Tue 20 Apr 1999
//------------------------------------------------------------------------------
bool	Replay::StoreSmokeSize(ULong size)
{
	SLong jump=size+sizeof(ULong);

	jump=-jump;

	SetFilePointer(recordstorage,jump,NULL,FILE_CURRENT);

	if (!ReplayWrite((UByte*)&size,sizeof(ULong)))
		return false;

	SetFilePointer(recordstorage,0,NULL,FILE_END);

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BackupPrefs
//Date			Fri 7 May 1999
//------------------------------------------------------------------------------
void	Replay::BackupPrefs(bool incomms)
{
	ReplayPrefs.flightdifficulty=Save_Data.flightdifficulty;
	ReplayPrefs.gamedifficulty=Save_Data.gamedifficulty;
	ReplayPrefs.autopilotskillLW=Save_Data.autopilotskillLW;
	ReplayPrefs.autopilotskillRAF=Save_Data.autopilotskillRAF;
	ReplayPrefs.targetsize=Save_Data.targetsize;

	if (incomms)
	{
		_DPlay.effects.GEffects=Save_Data.hardwareconfig[HW_GEFFECTS];
		_DPlay.effects.InjuryEffects=Save_Data.hardwareconfig[HW_INJURYEFFECTS];
		_DPlay.effects.WhiteOuts=Save_Data.hardwareconfig[HW_WHITEOUT];
		_DPlay.effects.ACNames=Save_Data.detail_3d[DETAIL3D_PADLOCKCHEAT];
		_DPlay.effects.Clouds=Save_Data.hardwareconfig[HW_FLUFFYCLOUDS];
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestorePrefs
//Date			Fri 7 May 1999
//------------------------------------------------------------------------------
void	Replay::RestorePrefs(bool incomms)
{
	Save_Data.flightdifficulty=ReplayPrefs.flightdifficulty;
	Save_Data.gamedifficulty=ReplayPrefs.gamedifficulty;
	Save_Data.autopilotskillLW=ReplayPrefs.autopilotskillLW;
	Save_Data.autopilotskillRAF=ReplayPrefs.autopilotskillRAF;
	Save_Data.targetsize=ReplayPrefs.targetsize;

	if (incomms)
	{
		if (_DPlay.effects.GEffects)
			Save_Data.hardwareconfig|=HW_GEFFECTS;
		else
			Save_Data.hardwareconfig%=HW_GEFFECTS;

		if (_DPlay.effects.InjuryEffects)
			Save_Data.hardwareconfig|=HW_INJURYEFFECTS;
		else
			Save_Data.hardwareconfig%=HW_INJURYEFFECTS;

		if (_DPlay.effects.WhiteOuts)
			Save_Data.hardwareconfig|=HW_WHITEOUT;
		else
			Save_Data.hardwareconfig%=HW_WHITEOUT;

		if (_DPlay.effects.ACNames)
			Save_Data.detail_3d|=DETAIL3D_PADLOCKCHEAT;
		else
			Save_Data.detail_3d%=DETAIL3D_PADLOCKCHEAT;

		if (_DPlay.effects.Clouds)
			Save_Data.hardwareconfig|=HW_FLUFFYCLOUDS;
		else
			Save_Data.hardwareconfig%=HW_FLUFFYCLOUDS;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreTimeOfDay
//Date			Tue 11 May 1999
//------------------------------------------------------------------------------
bool	Replay::StoreTimeOfDay()
{
	int	time=inst->timeofday;

	if (!ReplayWrite((UByte*)&time,sizeof(int)))
		return false;

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadTimeOfDay
//Date			Tue 11 May 1999
//------------------------------------------------------------------------------
bool	Replay::LoadTimeOfDay()
{
	int time;

	if (!ReplayRead((UByte*)&time,sizeof(int)))
		return false;

// check to see if block follows on timewise from previous

	if (abs(time-inst->timeofday)>100)
		UpdateLandscape=true;

	inst->timeofday=time;

	return true;
}

void	Replay::SetTimeOfDay(int time)					
{														
	inst->timeofday=time;								
}														

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreCampaignStruc
//Date			Wed 12 May 1999
//------------------------------------------------------------------------------
bool	Replay::StoreCampaignStruc()
{
	if (!ReplayWrite((UByte*)&MMC,sizeof(Campaign)))
		return false;

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadCampaignStruc
//Date			Wed 12 May 1999
//------------------------------------------------------------------------------
bool	Replay::LoadCampaignStruc()
{
	if (!ReplayRead((UByte*)&MMC,sizeof(Campaign)))
		return false;

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BackupGRRandomList
//Date			Wed 26 May 1999
//------------------------------------------------------------------------------
void	Replay::BackupGRRandomList()
{
	for (int n=0; n<(RNDPACKETSIZE - 2); n++)
		BackupRndPacket[n] = Math_Lib.GetRndLookUp(n);

	BackupRndPacket[(RNDPACKETSIZE - 2)] = Math_Lib.Getbval();
	BackupRndPacket[(RNDPACKETSIZE - 1)] = Math_Lib.Getcval();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadGRRandomList
//Date			Wed 26 May 1999
//------------------------------------------------------------------------------
bool	Replay::LoadGRRandomList()
{
	UWord RndPacket [RNDPACKETSIZE],n;
	
	if (!ReplayRead((UByte*)&RndPacket,RNDPACKETSIZE*sizeof(UWord)))
		return FALSE;

	for (n=0; n<(RNDPACKETSIZE - 2); n++)
		Math_Lib.SetRndLookUp(n,RndPacket[n]);

	Math_Lib.Setbval(RndPacket[(RNDPACKETSIZE - 2)]);
	Math_Lib.Setcval(RndPacket[(RNDPACKETSIZE - 1)]);

	Math_Lib.ResetRndCount();

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreGRRandomList
//Date			Wed 26 May 1999
//------------------------------------------------------------------------------
bool	Replay::StoreGRRandomList()
{
	if (!ReplayWrite((UByte*)&BackupRndPacket,RNDPACKETSIZE*sizeof(UWord)))
		return FALSE;

	Math_Lib.ResetRndCount();

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreAAAList
//Date			Mon 14 Jun 1999
//------------------------------------------------------------------------------
bool	Replay::StoreAAAList()
{
	UWord array[40]; //32 may not be enough if every element in group is gun...

	UWord	num=0,num2;
	SWord	skipsize=-1;

	while (skipsize<0)		//returns negative until end of list
	{
		skipsize=Three_Dee.livelist->ArchiveLiveList(array,40,num);
		num-=skipsize;
	}
	num+=skipsize+skipsize;	//total size is positive

	UWordP aaa=new UWord[num];

	if (aaa)
	{
		skipsize=Three_Dee.livelist->ArchiveLiveList(aaa,num,0);
		num2=skipsize;

		assert(num==num2);

		if (!ReplayWrite((UByteP)&num,sizeof(UWord)))
		{
			delete [] aaa;
			return false;
		}

		while (num2--)
		{
			if (!ReplayWrite((UByteP)&aaa[num2],sizeof(UWord)))
			{
				delete [] aaa;
				return false;
			}
		}

 		Three_Dee.livelist->RestoreSleepList();
		Three_Dee.livelist->ApplyLiveList(aaa,num);

		delete [] aaa;

		return true;
	}
	else
		return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadAAAList
//Date			Mon 14 Jun 1999
//------------------------------------------------------------------------------
bool	Replay::LoadAAAList()
{
	UWord num,num2;

	if (!ReplayRead((UByteP)&num,sizeof(UWord)))
		return false;

	UWordP aaa=new UWord[num];

	num2=num;

	while (num2--)
	{
		if (!ReplayRead((UByteP)&aaa[num2],sizeof(UWord)))
		{
			delete [] aaa;
			return false;
		}
	}

	if (!prescan)
	{
		Three_Dee.livelist->RestoreSleepList();
		Three_Dee.livelist->ApplyLiveList(aaa,num);
	}

	delete [] aaa;
	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetItemAnim
//Date			Wed 23 Jun 1999
//------------------------------------------------------------------------------
void	Replay::ResetItemAnim()
{
	ItemPtr i;

	if (prescan)
		return;

	for (int n=0;n<WorldStuff::PITEMTABLESIZE;n++)
	{
		if (Persons2::pItem[n])
		{
			i=(ItemPtr)Persons2::pItem[n];

			if (i->Status.size==ItemSize) // all other type should be covered by AC or Mob
			{
				SHAPE.ResetAnimData_NewShape(i,i->shape);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StoreArmedTransients
//Date			Wed 23 Jun 1999
//------------------------------------------------------------------------------
bool	Replay::StoreArmedTransients()
{
	TransientItemPtr	temp=TransientItem::TransientList;
	ArmedTransient at;
	SLong		hitstrength;

	while (temp)
	{
		if (temp->isArmed)
		{
			at.Pos.X=temp->World.X;
			at.Pos.Y=temp->World.Y;
			at.Pos.Z=temp->World.Z;

			at.hdg=temp->hdg;									
			at.pitch=temp->pitch;								

			at.vel_x=temp->vel_x;
			at.vel_y=temp->vel_y;
			at.vel_z=temp->vel_z;

			at.lifetime=(UWord)(temp->LaunchTime);
			at.movecode=(UByte)(temp->movecode);
			at.launcher=(UWord)(temp->Launcher->uniqueID.count);

			if (temp->Status.deadtime)	at.deadtime = 1;		
			else at.deadtime=0;
			at.transrandom = temp->TransRandom;					
			at.trailindex = 0;									

			hitstrength = 0;
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(temp->shape);
			if (sdptr->AnimDataSize == MISSILEANIM)
			{
				MissileAnimData*	adptr = (MissileAnimData*)temp->Anim;
				hitstrength = adptr->hitstrength;
			}
			else												
			{													
				if (sdptr->AnimDataSize == MOVEGUNANIM)			
				{												
					MoveGunAnimData*	adptr = (MoveGunAnimData*)temp->Anim;
					at.trailindex = adptr->weaponlaunchers[0].hdg;
				}												
			}													
			
			at.shape = temp->shape;
			at.strength=hitstrength;

			if (!ReplayWrite((UByte*)&at,sizeof(ArmedTransient)))
				return FALSE;

			if (!SHAPE.WriteReplayGroup(temp))						
				return false;										
		}
		temp=temp->nexttrans;
	}

	//End....
	at.shape = 0;

	if (!ReplayWrite((UByte*)&at,sizeof(ArmedTransient)))
		return FALSE;

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadArmedTransients
//Date			Wed 23 Jun 1999
//------------------------------------------------------------------------------
bool	Replay::LoadArmedTransients()
{
// load armed transients

	bool end=false;
	ArmedTransient at;
	UByte	noInGroup;													
	ReplayGroupInfo	tmpGrpInfo;											

	while (!end)
	{
		if (!ReplayRead((UByte*)&at,sizeof(ArmedTransient)))
			return FALSE;

// the break appears without noInGroup being set after it...
		if (at.shape==0)
			break;

		if (!ReplayRead(&noInGroup,sizeof(UByte)))						
			return FALSE;

		if (DoSmokeTrailStuff)
		{
// only process if block jump

			if (!Trans_Obj.LaunchReplayWeapon((UByte*)&at,noInGroup))	
				return false;											
		}
		else
		{
// skip group info...
			while (noInGroup)											
			{
				if (!ReplayRead(UByteP(&tmpGrpInfo),sizeof(ReplayGroupInfo)))
					return FALSE;

				noInGroup--;
			}
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Forward_X_Frames
// Date:		21/10/99
//////////////////////////////////////////////////////////////////////
void	Replay::Forward_X_Frames(ULong num)
{
	ULong n=sizeof(BASICPACKET);
	bool ok=true;
	UByteP temp;

// while there are more frames to jump than there are in the current block minus
// any unviewable frames (only jump through viewable footage) then jump to next block and
// reduce the amount to jump by the number of frames between the current position and the
// end of the of the block minus unviewable frames

	while (num>=(markers[1][currblock-1]-replayframecount))
	{
		num-=(markers[1][currblock-1]-replayframecount);

// set file position to end of this block ready to load next

		ULong skip;

		skip=numframes[currblock-1]-replayframecount;
		skip*=n;

		temp=playbackfilepos;
		playbackfilepos+=skip;

		if (!LoadBlockHeader())
		{
// trying to jump too far, goto end of replay file

			playbackfilepos=temp;
			num=0;
			ok=false;
			SkipToEnd();
			break;
		}

// at this point not processing frames so set current frame to beginning of viewable
// frames for calculations

		replayframecount=markers[0][currblock-1];
		playbackfilepos+=(replayframecount*n);
	}

	if (ok)
	{
// number of frames left to jump is less than viewable length of this block, just do
// a skip forward by number of frames left

		framestoskip=num;
		ReplayFlag=RF_SKIPFRAMES;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Rewind_X_Frames
// Date:		21/10/99
//////////////////////////////////////////////////////////////////////
void	Replay::Rewind_X_Frames(ULong num)
{
	ULong n=sizeof(BASICPACKET);
	UByteP temp;
	ULong skip;
	bool ok=true;

// while there are more frames to rewind than there are in current block minus any
// unviewable frame at beginning then rewind to previous block, set the position to 
// end of block minus and unviewable frames and reduce number left to rewind by 
// number of frames jumped minus number of unviewable frames

	while (num>replayframecount-markers[0][currblock-1])
	{
// rewind and set pos to end frame of block

		if (currblock>1)
		{
// set amount to skip to beginning of this block

			skip=((replayframecount*n)+headlength[currblock-1]);

// actual number skipped is current position minus any unviewable frames
// at the beginning

			num-=(replayframecount-markers[0][currblock-1]);

// add skip to beginning of previous block

			currblock--; 

			skip+=(numframes[currblock-1]*n);
			skip+=headlength[currblock-1];

// going to previous block then loading header

			currblock--;

// set file pointer to the start of the previous block

			temp=playbackfilepos;
			playbackfilepos-=skip;

// lets load block

			if (!LoadBlockHeader())
			{
				playbackfilepos=temp;
				SkipToBeginning();
				ok=false;
				break;
			}

// set position to end of this block

			replayframecount=markers[1][currblock-1];
			playbackfilepos+=(replayframecount*n);
		}
		else
		{
// bad values - get to beginning

			SkipToBeginning();
			ok=false;
			break;
		}
	}

	if (ok)
	{
// rewind inside this block

// skip to beginning of block

		skip=((replayframecount*n)+headlength[currblock-1]);
		temp=playbackfilepos;
		playbackfilepos-=skip;
		currblock--;
		num=replayframecount-num;

		if (!LoadBlockHeader())
		{
			playbackfilepos=temp;
			SkipToBeginning();
		}
		else
		{
			framestoskip=num;
			ReplayFlag=RF_SKIPFRAMES;
		}
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    AtEnd
// Date:		14/10/99
//
//Description: Checks whether the replay file is at the end or not
//
//////////////////////////////////////////////////////////////////////
bool	Replay::AtEnd()
{
	if (currblock==numblocks && replayframecount==markers[1][currblock-1]+1)
		return true;

	return false;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Forward30secs
// Date:		21/10/99
//////////////////////////////////////////////////////////////////////
void	Replay::Forward30secs()
{
	Forward_X_Frames(30*REPLAYFRAMESPERSEC);
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Rewind30secs
// Date:		21/10/99
//////////////////////////////////////////////////////////////////////
void	Replay::Rewind30secs()
{
	Rewind_X_Frames(30*REPLAYFRAMESPERSEC);
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Forward1sec
// Date:		21/10/99
//
//////////////////////////////////////////////////////////////////////
void	Replay::Forward1sec()
{
	Forward_X_Frames(REPLAYFRAMESPERSEC);
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Rewind1sec
// Date:		21/10/99
//////////////////////////////////////////////////////////////////////
void	Replay::Rewind1sec()
{
	Rewind_X_Frames(REPLAYFRAMESPERSEC);
}

void	Replay::SetPreviousPos()
{
	PrevPos=Persons2::PlayerGhostAC->World;
}

Bool	Replay::StoreSurfaceData(AirStrucPtr ac)
{
	SURFACEVALUES s;

	PSURFACE	pSurface=ac->fly.pModel->SurfaceList;

	while (pSurface)
	{
		GetSurfaceData(&s,pSurface);

		if (!ReplayWrite((UByte*)&s,sizeof(SURFACEVALUES)))
			return FALSE;

		pSurface=pSurface->List.NextItem();
	}

	return TRUE;
}

void	Replay::GetSurfaceData(LPSURFACEVALUES sv, PSURFACE ps)
{
	sv->Force=ps->Force;
	sv->Moment=ps->Moment;
}

void	Replay::RestoreSurfaceData(LPSURFACEVALUES sv, PSURFACE ps)
{
	ps->Force=sv->Force;
	ps->Moment=sv->Moment;
}

Bool	Replay::StoreThrustData(AirStrucPtr ac)
{
	THRUSTVALUES t;

	PTHRUSTPOINT pThrust=ac->fly.pModel->ThrustList;

	while (pThrust)
	{
		GetThrustData(&t,pThrust);

		if (!ReplayWrite((UByte*)&t,sizeof(THRUSTVALUES)))
			return FALSE;

		pThrust=pThrust->List.NextItem();
	}

	return TRUE;
}

void	Replay::GetThrustData(LPTHRUSTVALUES tv, PTHRUSTPOINT pt)
{
	tv->Force=pt->Force;
	tv->Moment=pt->Moment;
}

void	Replay::RestoreThrustData(LPTHRUSTVALUES tv, PTHRUSTPOINT pt)
{
	pt->Force=tv->Force;
	pt->Moment=tv->Moment;
}

Bool	Replay::StoreCylinderData(AirStrucPtr ac)
{
	CYLINDERVALUES c;

	PCYLINDER	pCylinder=ac->fly.pModel->CylinderList;

	while (pCylinder)
	{
		GetCylinderData(&c,pCylinder);

		if (!ReplayWrite((UByte*)&c,sizeof(CYLINDERVALUES)))
			return FALSE;

		pCylinder=pCylinder->List.NextItem();
	}

	return TRUE;
}

void	Replay::GetCylinderData(LPCYLINDERVALUES cv, PCYLINDER pc)
{
	cv->Force=pc->Force;
}

void	Replay::RestoreCylinderData(LPCYLINDERVALUES cv, PCYLINDER pc)
{
	pc->Force=cv->Force;
}

void	Replay::RestorePrimarySAGValues(SAGAirstruc* sag, LPSAGPRIMARYVALUES sagpv)
{

	((AirStrucPtr)sag)->fly.expandedsag=(AirStrucPtr)Persons2::ConvertPtrUID(sagpv->expandedsag);

	if (((AirStrucPtr)sag)->fly.expandedsag==Persons2::PlayerSeenAC)
		((AirStrucPtr)sag)->fly.expandedsag=Persons2::PlayerGhostAC;


	((AirStrucPtr)sag)->fly.numinsag=sagpv->numinsag;

}

void	Replay::GetPrimarySAGValues(SAGAirstruc* sag, LPSAGPRIMARYVALUES sagpv)
{
	UniqueID ID;
	int n;

	if (((AirStrucPtr)sag)->fly.expandedsag)
		ID=((AirStrucPtr)sag)->fly.expandedsag->uniqueID.count;
	else
		ID=UID_Null;

	sagpv->expandedsag=ID;

	sagpv->numinsag=((AirStrucPtr)sag)->fly.numinsag;

}

bool	Replay::StorePrimarySAGData(SAGAirstruc* sag)
{
	SAGPRIMARYVALUES sagpv;

	GetPrimarySAGValues(sag,&sagpv);

	if (!ReplayWrite((UByte*)&sagpv,sizeof(SAGPRIMARYVALUES)))
		return false;

	return true;
}

void	Replay::StoreTempID()
{
	ULong t=TempID;

	ReplayWrite((UByte*)&t,sizeof(ULong));
}

void	Replay::LoadTempID()
{
	ULong t;

	ReplayRead((UByte*)&t,sizeof(ULong));

	if (t!=TempID)
		INT3;
}

bool	Replay::LoadSmokeClouds(bool dummy)
{
	if (!Land_Scape.LoadSmokeClouds(dummy))
		return false;

	return true;
}

bool	Replay::StoreSmokeClouds()
{
	if (!Land_Scape.SaveSmokeClouds())
		return false;

	return true;
}


void	Replay::SetWaypointData()
{
	int i;

	for (i=WayPointBAND;i<WayPointBANDEND;i++)
	{
		WayPointPtr w=Persons2::ConvertPtrUID((UniqueID)i);
		if (w)
		{
			w->ETA=0;
		}
	}
}

void	Replay::SetWaypointTargetAlt()
{
	int i;
	for (i=WayPointBAND;i<WayPointBANDEND;i++)
	{
		WayPointPtr w=Persons2::ConvertPtrUID((UniqueID)i);
		if (w)
		{
			if (w->target)
			{
				w->target->World.Y=_Collide.AccurateGroundAltitude(w->target->World);
			}
		}
	}
}

void	Replay::DumpData(char* name)
{
// output whatever here..........
}

bool	Replay::StoreSagGlobs()
{
	SAGGLOBS sags;
	int i;

	for (i=PT_BRIT_FLYABLE;i<=PT_GER_NONFLY;i++)
	{
		sags.mintriggerrange=Persons3::sagexpcounts[i].mintriggerrange;
		sags.maxtriggerrange=Persons3::sagexpcounts[i].maxtriggerrange;
		sags.currenttriggerrange=Persons3::sagexpcounts[i].currenttriggerrange;
		sags.basenum=Persons3::sagexpcounts[i].basenum;
		sags.numavailable=Persons3::sagexpcounts[i].numavailable;
		sags.numactive=Persons3::sagexpcounts[i].numactive;
		sags.reservedactive=Persons3::sagexpcounts[i].reservedactive;
		sags.SAGsoftype=Persons3::sagexpcounts[i].SAGsoftype;
		sags.SAGsexpanded=Persons3::sagexpcounts[i].SAGsexpanded;

		if (!ReplayWrite((UByte*)&sags,sizeof(SAGGLOBS)))
			return false;
	}	

	if (!ReplayWrite((UByte*)&Persons3::SagExpansionCounter::totalexpanded,sizeof(int)))
		return false;

	if (!ReplayWrite((UByte*)&Persons3::SagExpansionCounter::highdemandrange,sizeof(int)))
		return false;

	return true;
}

bool	Replay::LoadSagGlobs()
{
	SAGGLOBS sags;
	int i;

	for (i=PT_BRIT_FLYABLE;i<=PT_GER_NONFLY;i++)
	{
		if (!ReplayRead((UByte*)&sags,sizeof(SAGGLOBS)))
			return false;

		Persons3::sagexpcounts[i].mintriggerrange=sags.mintriggerrange;
		Persons3::sagexpcounts[i].maxtriggerrange=sags.maxtriggerrange;
		Persons3::sagexpcounts[i].currenttriggerrange=sags.currenttriggerrange;
		Persons3::sagexpcounts[i].basenum=sags.basenum;
		Persons3::sagexpcounts[i].numavailable=sags.numavailable;
		Persons3::sagexpcounts[i].numactive=sags.numactive;
		Persons3::sagexpcounts[i].reservedactive=sags.reservedactive;
		Persons3::sagexpcounts[i].SAGsoftype=sags.SAGsoftype;
		Persons3::sagexpcounts[i].SAGsexpanded=sags.SAGsexpanded;
	}

	if (!ReplayRead((UByte*)&Persons3::SagExpansionCounter::totalexpanded,sizeof(int)))
		return false;

	if (!ReplayRead((UByte*)&Persons3::SagExpansionCounter::highdemandrange,sizeof(int)))
		return false;

	return true;
}

bool	Replay::StoreACArray()
{
	for(int i = 0; i < ArtInt::ACARRAYSIZE; i++)
	{
		if(ArtInt::ACArray[i])
		{
			if (!ReplayWrite((UByte*)&i,sizeof(int)))
				return false;

			UWord uid=ArtInt::ACArray[i]->uniqueID.count;

			if (!ReplayWrite((UByte*)&uid,sizeof(UWord)))
				return false;
		}
	}

	int end=-1;

	if (!ReplayWrite((UByte*)&end,sizeof(int)))
		return false;

	return true;
}

bool	Replay::LoadACArray()
{
	int index;

// clear out array first

	for(index = 0; index < ArtInt::ACARRAYSIZE; index++)
	{
		ArtInt::ACArray[index]=NULL;
	}

	do 
	{
		if (!ReplayRead((UByte*)&index,sizeof(int)))
			return false;

		if (index!=-1)
		{
			UWord uid;

			if (!ReplayRead((UByte*)&uid,sizeof(UWord)))
				return false;

			AirStrucPtr ac=*Persons2::ConvertPtrUID(UniqueID(uid));

			ArtInt::ACArray[index]=ac;
		}
	}
	while (index!=-1);

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Replay
//Date			Tue 5 May 1998
//------------------------------------------------------------------------------
CON	Replay::Replay()
{
	ULong n;

	strcpy(rfilename,"replay.dat");
	strcpy(pfilename,"replay.dat");
	strcpy(RealFilename,"");;
	strcpy(replaysavebackup,"dreplay.dat");
	Record=FALSE;
	Playback=FALSE;

	playbackfilestart=NULL;
	playbackfilepos=NULL;

	ResetReplayData();

	for (n=0;n<256;n++)
	{
		headlength[n]=0;
		numframes[n]=0;
	}

	initgrlist=NULL;
	bfgrlist=NULL;
 	currentry=NULL;

	recordstorage=NULL;
	playbackstorage=NULL;

	ReplayDeathMode = RDEATH_NULL;
	DoSmokeTrailStuff=TRUE;

	framestoskip=0;
	ResetFileFlag=false;
	guncameradelay=0;
	SuperHeaderStored=false;
	RestorePosition=false;
	MenuViewPlayback=false;
	ReplayFlag=RF_NONE;
 	MapPlayback=false;
	QMPlayback=false;
	badrecord=true;
	prefscheck=false;
	skipOK=false;
	prescan=false;
	stopforaccel=false;
	setpaused=0;
	emptyblock=false;
	processsmokes=false;
	backupsmoke=NULL;
	tempbackupsmoke=NULL;
	backupcloud=NULL;
	tempbackupcloud=NULL;
}

CON	Replay::~Replay()
{
	Playback=FALSE;
	Record=FALSE;
	CloseRecordLog();
	ClosePlaybackLog();
	DeleteGRList(initgrlist);
	DeleteFileAndGlobRefList(bfgrlist);
}


