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
//Filename       winmove.cpp
//Date           Mon 5 Aug 1996
//Description    Move all things.
//------------------------------------------------------------------------------

#define IDIRECTPLAY2_OR_GREATER
#define	F_COMMON
#include	"DOSDefs.h"	
#include	"WorldInc.h"
#include	"UniqueID.h"
#include	"flymodel.h"
#include	"ai.h"
#include 	<windows.h>
#include 	<windowsx.h>
#include 	<mmsystem.h>
#include	"dplay.h"
#include	"savegame.h"
#include	"misssub.h"
#include	"comms.h"
#include	"winmove.h"
#include	"persons2.h"
#include	"Keytest.h"
#include	"3dcode.h"
#include	"mytime.h"
#include	"viewsel.h"
#include	<math.h>
#include	"mymath.h"
#include	"myangles.h"
#include	"transite.h"
#include	"3dcom.h"
#include	"3dcode.h"
#include	"lstream.h"											
#include	"aaa.h" 
#include	"collided.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	"ranges.h"
#include	"speed.h"
#include	"monotxt.h"
#include	"keytest.h"
#include	"miles.h"	
#include	"aggrgtor.h"
#include	"replay.h"
#include	"myerror.h"

#include	"monotxt.h"
#include "modvec.h" // To check some #defines
#include "Model.h" // To check some #defines
#include	"globrefs.h"
#include	"ctimeout.h"
#include	"boxcol.h"
#include	"overlay.h"
#include		"rchatter.h"
#include	"mytime.h"
#include	"sqddiary.h"

#define		SPECIAL_KEYMAPS	FALSE
#define		SENDPAUSE 0

//#define TIMERTIME
//#define CVELCHECK
//#define		WINTIME
//#define	SYNCDATA
//#define DETAILS
//#define INITCHECK
//#define 	FILELOGS
//#define 	FILELOGS1
//#define		LOGHIST
//#define HISTTEST
//#define DELTALOG
//#define VIEWGHOSTSAMEFRAME
//#define APPLYDELTASINONEGO
//#define MESSQUEUELOG
//#define DELTACHECK
//#define P_A_CHECK
//#define COLLPACKINFO
//#define COMMSANIMCHECK

//#define	PACKETRESEND 25


//#define ENUMTIMEOUT 1000
//#define	MAXFRAMESOUT 16

AirStruc* Persons2::PlayerGhostAC=NULL;
AirStruc* Persons2::PlayerSeenAC=NULL;


Aggregator	_Agg ; 
Replay	_Replay;

#ifdef TIMERTIME
static ULong Qfreq;
static ULong Qtimertime;
static ULong Qlasttimertime;

static ULong timertime;
static ULong lasttimertime;
FILE* timer;
#endif

#ifndef NDEBUG
	static SByte currghostsign=0;
	static SByte currseensign=0;

#define	DBGMEMTEST

#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CommsGameSync
//Date			Fri 16 Apr 1999
//------------------------------------------------------------------------------
bool	DPlay::CommsGameSync()
{
	if (Implemented)
	{
		if (realfirsttimein)
		{
			realfirsttimein=FALSE;

// Set Active Player Bit field

			ActivePlayers = 0;
			for (int n=0; n<MAXPLAYERS; n++)
			{
				if (DPlay::H2H_Player[n].status==CPS_3D)
					ActivePlayers |= (1 << n);
			}

			if (Joining)
			{
				_DPlay.SendEnteringGameMessage();

				Joining=FALSE;
				Initiator=TRUE;

// ensure that in comms QM AC that player is about to take over is not dead

				if (GameType==COMMSQUICKMISSION)
				{
					int squadnum;
					UByte pltnum;

					squadnum=Persons2::PlayerSeenAC->ai.pilotnum;
					int sqcol,sqnum,numacinflight;

					switch (Persons2::PlayerSeenAC->classtype->planetext)
					{
					case PT_SPIT_A:
					case PT_SPIT_B:
					case PT_HURR_A:
					case PT_HURR_B:
					case PT_DEFIANT:
					case PT_BLEN:
					case PT_JU87:
						numacinflight=3;
						break;

					case PT_ME109:
					case PT_ME110:
						numacinflight=4;
						break;

					case PT_DO17:
					case PT_JU88:
					case PT_HE111:
						numacinflight=5;
						break;
					default:
						numacinflight=0;
						INT3;
						break;
					}

					sqcol=(Persons2::PlayerSeenAC->fly.originalformpos & InFormMAX)+1;
					sqnum=(Persons2::PlayerSeenAC->fly.originalformpos & InWingMAX)+1;

					pltnum=((sqcol-1)*numacinflight)+sqnum;

					if (IsPilotDead(sqnum,pltnum))
					{
						SimulateExitKey=TRUE;
						return false;
					}
				}

				BeginSyncPhase();
				JustJoined=TRUE;
				return false;
			}

 			if (Host && !ResyncPhase)
			{
				_Agg.StopResetAggregator();
				_Agg.Running=TRUE;
			}
		}

		if (ResyncPhase)
		{
			if (!ReceiveSyncPackets())
				return false;

#ifdef SYNCDATA 
			FILE* fp=fopen("resync.txt","at");
			fprintf(fp,"resync OK CP=%d\n",_DPlay.CurrPlayers);
			fclose(fp);
#endif
			Initiator=FALSE;
			ResyncPhase=FALSE;

			if (GameType>TEAMPLAY)
			{
				WorldSyncPhase=TRUE;
				InitSyncData(false);
			}
			else
			{
				InitBuffers();
				if (Host)// && !WorldSyncPhase)
				{
					_Agg.StopResetAggregator();
					_Agg.Running=TRUE;
				}
			}
		}

		if (WorldSyncPhase)
		{
			if (!SyncCommsWorld())
				return false;

#ifdef SYNCDATA 
			FILE* fp=fopen("resync.txt","at");
			fprintf(fp,"worldsyncphase OK CP=%d\n",_DPlay.CurrPlayers);
			fclose(fp);
#endif
			WorldSyncPhase=FALSE;								
			InitBuffers();
			if (Host)
			{
				_Agg.StopResetAggregator();
				_Agg.Running=TRUE;
			}
		}

		if (firsttimein)
		{
			InitGameVars();

#ifdef SYNCDATA 
			FILE* fp=fopen("resync.txt","at");
			fprintf(fp,"initgame vars OK CP=%d\n",_DPlay.CurrPlayers);
			fclose(fp);
#endif
			BackupSeen();
			BackupGhost();

			if (Host)
			{
				_Agg.StopResetAggregator();
				_Agg.Running=TRUE;
			}
		}

		if (!synched)
		{
			if (!InitSyncPhase())
				return false; 
#ifdef SYNCDATA 
			FILE* fp=fopen("resync.txt","at");
			fprintf(fp,"initsyncphase OK CP=%d\n",_DPlay.CurrPlayers);
			fclose(fp);
#endif
		}

		if (!csync && synched)
		{
			if (!SecondSyncPhase())
				return false;
#ifdef SYNCDATA 
			FILE* fp=fopen("resync.txt","at");
			fprintf(fp,"2ndsyncphase OK CP=%d\n",_DPlay.CurrPlayers);
			fclose(fp);
#endif
		}
	}
	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WinMove
//Date			Thu 5 Sep 1996
//Description	Comms talking stuff
//------------------------------------------------------------------------------
void mobileitem::WinMove (int timeofday,WorldStuff* worldref)
{
#ifdef WINTIME	
 	static ULong lasttime=timeGetTime();
	static ULong total=0;
	static ULong num=1;
 	ULong ttime=timeGetTime();

 	FILE* fp=fopen("wtime.txt","at");
 	fprintf(fp,"CALL %d (%d) av=%d (%d)\n",(ttime-lasttime)/10,ttime-lasttime,((total/num)/10),total/num);
 	fclose(fp);
	total+=(ttime-lasttime);
	num++;
 	lasttime=ttime;
#endif
	if (_DPlay.Implemented)
	{
#ifdef TIMERTIME
		LARGE_INTEGER count;
		QueryPerformanceCounter(&count);
		ULong smlcount=count.LowPart;
		ULong Rtime=((smlcount-Qlasttimertime)*1000)/Qfreq;

		fprintf(timer,"%d %d %d Qt%d\n",
			timeGetTime()-timertime,
			timeGetTime()-lasttimertime,
			_DPlay.FrameCount,
			Rtime);

		Qlasttimertime=smlcount;
		lasttimertime=timeGetTime();
#endif
// Set random list position
	
		_DPlay.SetRandomListPos();

// do this after random numbers have been synched!!!

		_DPlay.ProcessInfoPackets();

#ifndef APPLYDELTASINONEGO
		_DPlay.CheckGhost();
		_DPlay.CheckSeen();
 		_DPlay.ApplyPartialDeltas();
		_DPlay.BackupGhost();
#endif

		if (_DPlay.ResyncPhase)
			return;

// need to sync random numbers again as launching weapons will use random numbers 
// differently!

		_DPlay.SetRandomListPos();

// move function 

		DosMove (timeofday,worldref);

		timeofday+=Timer_Code.FRAMETIME; 
		_Replay.SetTimeOfDay(timeofday);

// make packet (if its time to send one)

 		if (++_DPlay.FrameInc==_DPlay.RateDivider)
 		{
 			_DPlay.FrameInc=0;
 			_DPlay.MakeAndSendPacket();
		}

// check send queue to see if it is getting large

#ifndef NDEBUG
		_DPlay.CheckSendQueue();
#endif

	}
	else
	{
// sync random numbers after 3d as well now before collision packets etc get processed

		_DPlay.SetRandomListPos();

		_DPlay.CheckGhost();

		if (_Replay.prefscheck)
		{
			_Replay.prefscheck=false;
			if (_Replay.Record)
			{
				if (!Save_Data.gamedifficulty[GD_GUNCAMERAATSTART])
				{
// been to prefs, turned record off - stop

					_Replay.StopRecord(true);
				}
				else
				{
//been to prefs, still recording - begin new block in case prefs changed

					_DPlay.CheckSeen();
					_DPlay.CheckGhost();

					if (Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW)
					{
						_Replay.BeginNewBlock();
					}

					_DPlay.BackupGhost();
					_DPlay.BackupSeen();
				}
			}
			else if (!_Replay.Playback)
			{
// been to prefs, turned record on

				if (Save_Data.gamedifficulty[GD_GUNCAMERAATSTART])
				{
					if (Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW)
					{
						_Replay.StartRecordFlag=TRUE;
					}
				}
			}
		}

		if (_Replay.Record)
		{
			if (!_Replay.StoreDeltas())
			{
				_Replay.Record=FALSE;
				_Replay.CloseRecordLog();
			}
		}
		else if (_Replay.Playback)
		{
			_Replay.ResetFlags();

 			if (!_Replay.LoadDeltas())
			{
				{
					_Replay.PlaybackPaused=TRUE;		
					OverLay.pCurScr=OverLay.pNewScr=&OverLay.replayScr;
					return; // dont do dosmove if paused......
				}
			}
		}
		else
		{
#ifndef VIEWGHOSTSAMEFRAME
			_Replay.UpdateGhostAC();
#endif
		}

// sync random numbers after packets have been processed as things like launching bullets 
// will cause extra random numbers to be used before AI etc

		_DPlay.BackupGhost();

		_DPlay.SetRandomListPos();

		DosMove (timeofday,worldref);

#ifdef VIEWGHOSTSAMEFRAME
		_DPlay.CheckGhost();
		_Replay.UpdateGhostAC();
		_DPlay.BackupGhost();
#endif

#ifdef _SUPER_FAST_TIME_OF_DAY
		timeofday+=Timer_Code.FRAMETIME*600;
#else
		timeofday+=Timer_Code.FRAMETIME;
#endif
		if ( timeofday > 60*60*24*100 )
			timeofday-=60*60*24*100;
		_Replay.SetTimeOfDay(timeofday);				

// the storing and loading of block headers must be done after the movecycle,
//but before the next set of load/store deltas. This is so that in the record 
//and playback the flow of data is always
//	block header, deltas, move
// if the record was, blockheader, store deltas , movecycle and then later on
// store deltas, block header, movecycle, things become out of step.

		if (_Replay.Record)								
		{
			if (_Replay.StoreHeader)
			{
				_Replay.StoreHeader=false;

				_DPlay.CheckGhost();
				_DPlay.CheckSeen();

				if (!_Replay.StoreBlockHeader())
				{
					_Replay.Record=FALSE;
					_Replay.CloseRecordLog();
				}
				_DPlay.BackupGhost();
				_DPlay.BackupSeen();
			}
		}
		else if (_Replay.Playback)
		{
			if (_Replay.LoadHeader)
			{
				_Replay.LoadHeader=false;

				UByteP temp=_Replay.playbackfilepos;

				_Replay.DoSmokeTrailStuff=FALSE;

				_DPlay.CheckGhost();
				_DPlay.CheckSeen();

				if (!_Replay.LoadBlockHeader())
				{
					_Replay.DoSmokeTrailStuff=TRUE;
					_Replay.playbackfilepos=temp;
					_Replay.PlaybackPaused=TRUE;
					OverLay.pCurScr=OverLay.pNewScr=&OverLay.replayScr;
				}

				_DPlay.BackupGhost();
				_DPlay.BackupSeen();

				_Replay.DoSmokeTrailStuff=TRUE;
			}
		}
		else if (_Replay.StartRecordFlag)
		{
 			_Replay.StartRecordFlag=FALSE;

			if (_Replay.OpenRecordLog())
			{
				if (!_Replay.SuperHeaderStored)
					_Replay.StoreSuperHeader();

				_DPlay.CheckSeen();
				_DPlay.CheckGhost();

				if (_Replay.StoreBlockHeader())
				{
					_Replay.Record=TRUE;
					_Replay.badrecord=false;
					_DPlay.InitBuffers();

// this will ensure weapon packet is in first packet

					if (_Replay.DelayedWeapon>=0)
					{
						_DPlay.NewBullet(1,_Replay.DelayedWeapon);
						_Replay.DelayedWeapon=-1;
					}
					else if (_Replay.DelayedGearUp)
					{
						_Replay.DelayedGearUp=false;
						_DPlay.SendAccelGearUpMessage();
					}
				}

				_DPlay.BackupGhost();
				_DPlay.BackupSeen();
			}
// clean up if something wrong with record

			if (_Replay.DelayedWeapon>=0)
			{
				_DPlay.NewBullet(1,_Replay.DelayedWeapon);
				_Replay.DelayedWeapon=-1;
			}
			if (_Replay.DelayedGearUp)
			{
				_Replay.DelayedGearUp=false;
				_DPlay.SendAccelGearUpMessage();
			}
		}	
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StorePacket
//Description	
//				Store packet in buffer
//------------------------------------------------------------------------------
void DPlay::StorePacket (LPAGGSENDPACKET AggPacket)
{
	SWord	n,diff,m;
	SWord	thispacketcount;
	SWord	targetcount;
	SLong	sub;

	AGGSENDPACKET packet;	

// expand sent packet into full packet

	ExpandAggPacket(&packet, AggPacket);			

#ifdef FILELOGS
			FILE* fp=fopen("aggpack.txt","at");

			fprintf(fp,"PacketFrame %d CurrentFrame %d\n",
				packet.Count,
				FrameCount);

			for (n=0;n<MAXPLAYERS;n++)
			{
				if (ActivePlayers&1<<n)
				{
					fprintf(fp,"%d %d %d %d %d\n",
						packet.player[n].Count,
						packet.player[n].X,
						packet.player[n].Y,
						packet.player[n].Z,
						packet.player[n].IDCode);

					if (packet.player[n].IDCode!=PIDC_PACKETERROR)
					{
						if (packet.player[n].Ack1)
							fprintf(fp,"got ACK for %d from p%d\n",packet.player[n].Ack1,n);
						if (packet.player[n].Ack2)
							fprintf(fp,"got ACK for %d from p%d\n",packet.player[n].Ack2,n);
					}

					fprintf(fp,"add %d for ACK\n",packet.Count);
				}
			}
#endif

// update all ack info, even if I have already received this packet, and send
// acks in case they have got lost


	AddPacketToCheckBuffer(&packet);

// players ack aggregators packets. This is because even if a player is not in an aggregated
// packet, he still wants the other players packets. So if the players were acking their
// own packets, an aggregated packet with a player absent that goes missing will not be acked
// by the player who was absent. This would cause the aggregators buffer to overflow because 
// it expects an ack from all players. 


 	RecPackBuffer.GetNext()->packet=packet.Count;
 	RecPackBuffer.AddEntryAndUpdateNext();

	for (n=0;n<MAXPLAYERS;n++)
	{
		if (packet.player[n].IDCode!=PIDC_PACKETERROR)
		{
// got a real packet from this player

			PacketBuffer.SetTempCurr();

			thispacketcount=packet.player[n].Count;
			targetcount=PacketBuffer.GetCurr()->Count;

			sub=thispacketcount-targetcount;

			if (((thispacketcount>=targetcount && sub<BufferSize)
			|| (thispacketcount<targetcount && abs(sub)>BufferSize)))
			{
// packet is within range I want

				if (thispacketcount>=targetcount)
					diff=sub;
				else
					diff=(sub)+256;

#ifdef FILELOGS
				fprintf(fp,"add to packetbuff.curr=%d updating by %d \n",PacketBuffer.GetCurr()->Count,diff);
				if (diff>=BufferSize)
				{
// buffer about to wrap - not good

					_Error.SayAndQuit("buffer wrap");
				}
#endif

				while (diff--)
					PacketBuffer.UpdateTemp();

				if (!PacketBuffer.GetTemp()->Received[n])
				{
// have not already received this packet

					if (H2H_Player[n].dpid==myDPlayID)
					{
// can sent packet buffer be updated?

						if (packet.player[n].IDCode!=PIDC_INITPACK)
						{
// a real delta packet
							SendPackBuffer.SetTempCurr();

							targetcount=SendPackBuffer.GetCurr()->packet.Count;

							sub=thispacketcount-targetcount;

							if (((thispacketcount>=targetcount && sub<BufferSize)
							|| (thispacketcount<targetcount && abs(sub)>BufferSize)))
							{
// if within range from current up to half buffer

								if (thispacketcount>=targetcount)
									diff=sub;
								else
									diff=(sub)+256;

#ifdef FILELOGS
								fprintf(fp,"sendpackbuff.curr=%d updating by %d \n",SendPackBuffer.GetCurr()->packet.Count,diff);
#endif
								while (diff--)
									SendPackBuffer.UpdateTemp();

// not sure if these checks are needed. I know I want this packet, if counts are not same
// then something has gone badly wrong, and I have already checked about receiving this packet
// so done should always be false.....????

								if (packet.player[n].Count==SendPackBuffer.GetTemp()->packet.Count
								&& (!SendPackBuffer.GetTemp()->Done))
								{
// anyway is this is one I want register as done and see if buffer can be updated

									SendPackBuffer.GetTemp()->Done=TRUE;

									while (SendPackBuffer.GetCurr()->Done)
									{
#ifdef FILELOGS
									fprintf(fp,"update currspb %d\n",SendPackBuffer.GetCurr()->packet.Count);
#endif
										SendPackBuffer.GetCurr()->Done=FALSE;
										SendPackBuffer.GetCurr()->ResendStatus=0;
										SendPackBuffer.UpdateCurr();
									}
								}
							}
						}
					}

// register as received and copy into buffer

					PacketBuffer.GetTemp()->Received[n]=TRUE;
					CopyMemory((char*)&PacketBuffer.GetTemp()->PlayerData[n],(char*)&packet.player[n],sizeof(ACPACKET));

#ifdef FILELOGS
					fprintf(fp,"processing %d\n",packet.player[n].Count);
					fflush(fp);
#endif

// process move packet here, but not anything else. Must wait for all players
// to have all packets from this frame so that AI is on sync when collsions,
// near misses etc occur.

					if (ActivePlayers&(1<<n))
					{
						if (packet.player[n].IDCode<PIDC_AIACPOSITION1)
						{
							CheckGhost();
							ProcessDeltaPacket(&(PacketBuffer.GetTemp()->PlayerData[n]),n);
							BackupGhost();

							UpdateHistBuffer(&PacketBuffer.GetTemp()->PlayerData[n],n);

 							CalcVels(n,PacketBuffer.GetTemp()->PlayerData[n].Count);
						}
						else
						{
// dont process but still add to hist buffer

							AddPacketToHistBuffer(&PacketBuffer.GetTemp()->PlayerData[n],n);
						}
					}
				}
				else
				{
#ifdef FILELOGS
 					fprintf(fp,"packet %d already received temp=%d\n",packet.player[n].Count,PacketBuffer.GetTemp()->Count);
#endif
				}
			}
			else
			{
#ifdef FILELOGS
 			 	fprintf(fp,"packet %d not in range\n",packet.player[n].Count);
#endif
			}
		}
	}

#ifdef FILELOGS
 	fflush(fp);
#endif
	AttemptToProcessExtraPacket();

#ifdef FILELOGS
	fprintf(fp,"\n");
	fclose(fp);
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessDeltaPacket
//Description	Update the predicted ac with new deltas
//Inputs		slot = slot of sender of packet to be processed
//				lpAcPacket is packet to be processed
//------------------------------------------------------------------------------
void DPlay::ProcessDeltaPacket (LPACPACKET lpAcPacket,ULong slot)
{
	UByte RecCode=(lpAcPacket->IDCode)>>6;	// type of packet
	UByte Mess=lpAcPacket->IDCode;
	AirStrucPtr AC;

	AC=*Persons2::ConvertPtrUID((UniqueID)AllocPacket[slot]);

	if (AC)
	{
// Get AirStrucPtr for the Packet's Aircraft

		if (RecCode==PT_SPECIAL)
		{
			switch (Mess)
			{
			case PIDC_PACKETERROR:
			case PIDC_INITPACK:
// packets which dont have valid deltas, ignore 

				break;
			default:
// all the rest do have valid deltas
#ifdef APPLYDELTASINONEGO
 				if (AC==Persons2::PlayerSeenAC)
				{
					UpdatePredictedAC(lpAcPacket);
				}
				else
				{
					CopyPacket (AC, lpAcPacket);
				}
#else

				if (AC==Persons2::PlayerSeenAC)
					UpdatePredictedAC(lpAcPacket);
				else
					AddDeltasToApply(lpAcPacket,slot);
#endif
			}
		}
		else
		{
#ifdef APPLYDELTASINONEGO
			if (AC==Persons2::PlayerSeenAC)
			{
				UpdatePredictedAC(lpAcPacket);
			}
			else
			{
				CopyPacket (AC, lpAcPacket);
			}
#else
			if (AC==Persons2::PlayerSeenAC)
				UpdatePredictedAC(lpAcPacket);
			else
	 			AddDeltasToApply(lpAcPacket,slot);
#endif
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessExtraPacket
//Date			Tue 25 Aug 1998
//Description	Process extra packet info
//------------------------------------------------------------------------------
void DPlay::ProcessExtraPacket (LPACPACKET lpAcPacket,ULong player_slot)
{
	AirStrucPtr AC;

	AC=*Persons2::ConvertPtrUID((UniqueID)AllocPacket[player_slot]);

	if (AC)
	{
		ProcessExtraPacket(lpAcPacket,AC,player_slot);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResurrectMe
//Date			Sat 14 Dec 1996
//
//				Its function is to resurrect an ac and send packet to start resurection
//				for same plane on other machines
//------------------------------------------------------------------------------
void DPlay::ResurrectMe (AirStrucPtr ac,bool suicide)
{
	static ULong time=0;

	if (Implemented)
	{
// set pilot to be dead

		if (GameType>TEAMPLAY)
		{
			SendPilotsStatus(true,0,Persons2::PlayerSeenAC->ai.squadnum(),Persons2::PlayerSeenAC->ai.pilotnum);
		}

		if (viewtime)
		{
			viewtime=false;
			time=timeGetTime()+5000;
		}
		else
		{
			if (timeGetTime()>time || suicide)
			{

// only resurrect if in DEATHMATCH or TEAMPLAY
// otherwise player must exit to ready room and select new ac and rejoin

				if (GameType<COMMSQUICKMISSION)
				{
// remove any bullet packets now that I am dead

					BulletBuffer.InitBuffer();

					if (ac->movecode != AUTO_RESURRECT)
					{
						ResurrectAircraft (ac, TRUE);

// always send
						NewSpecial(PIDC_RESURRECT);
					}
				}
			}
		}
	}	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResurrectAircarft
//Date			Fri 22 Nov 1996
//------------------------------------------------------------------------------
void DPlay::ResurrectAircraft (AirStrucPtr ControlledAC, Bool Forced)
{
	if (Implemented)
	{
		InitResurrect (ControlledAC);
		RepairAircraft (ControlledAC);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RepairAircraft
//Date			Sat 7 Dec 1996
//Description	Repair an Aircraft ready for flight etc,
//------------------------------------------------------------------------------
void DPlay::RepairAircraft (AirStrucPtr ac)
{
	_Miles.StopItemSamples(ac);											
	_Miles.SetEngine();													

	if (ac->Status.size!=AirStrucSize)							
		_Error.SayAndQuit("Repair ac not aircraftsize");		

	ULong n;

	ac->ai.radiosilent=FALSE;

	SHAPE.DetatchAllVapourStreams(ac);
	for (n=0; n<MAXPLAYERS; n++)
	{
		if (AllocPacket [n] == ac->uniqueID.count)
		{
			if (!SHAPE.ResetAnimData_NewShape(ac,ac->_GetDrawShape(),ac->weap.Weapons))	
				_Error.SayAndQuit("Wrong anim data");
		
			break;
		}
	}

	ac->fly.redeffect = 0;	
	Land_Scape.blackingout = 0;
	Land_Scape.whitingout = 0;

	ac->Status.deadtime = 0;

// thrust

	if (ac == Persons2::PlayerSeenAC)
	{
		ac->fly.thrustpercent = 100;

		ac->weap.FuelDumped = FALSE; // allow rip stores again
	}

	MinAnimData* mad = (MinAnimData* )ac->Anim;					
	mad->itemstate = ALIVE;
	mad->IsInvisible=0;

	ac->fly.pModel->CrashTime = 0;								

	Trans_Obj.SetTotalAmmo(ac);									

	int slot=UID2Slot(ac->uniqueID.count);
	if (slot<MAXPLAYERS)
	{
		CommsKiller[slot]=255;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitResurrect
//Date			Sat 7 Dec 1996
//Description	Set up Aircraft to use AUTO_RESURRECT
//------------------------------------------------------------------------------
void DPlay::InitResurrect (AirStrucPtr ac)
{
	if (Implemented)
	{
		hitResurrect = false;

		ac->movecode = AUTO_RESURRECT;	

		if (ac == Persons2::PlayerSeenAC)
		{
			Persons2::PlayerGhostAC->movecode=AUTO_RESURRECT;
			Manual_Pilot.controlmode=ManualPilot::PILOTDEAD;
			Trans_Obj.View_Object->SetToPiloted((itemptr)ac);
		}

 		Key_Tests.KeyPress3d(RESURRECTKEY);
	}
}

#ifndef NDEBUG
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DosMove
//Date			Wed 9 Oct 1996
//------------------------------------------------------------------------------
static char* GetMoveCode(AutoMoveCodeTypeSelect a)
{
	switch (a)
	{
	case AUTO_FOLLOWWP:         return "AUTO_FOLLOWWP=0, ";
	case AUTO_NOPPILOT:         return "AUTO_NOPPILOT, ";
	case AUTO_WAIT4TIME:        return "AUTO_WAIT4TIME, ";
	case AUTO_TAXI:             return "AUTO_TAXI, ";
	case AUTO_TAKEOFF:          return "AUTO_TAKEOFF, ";
	case GROUND_TAXI:		    return "GROUND_TAXI, ";
	case AUTO_TELLLEADER:		return "AUTO_TELLLEADER,	 ";
		                                              
	case AUTO_SPIRAL2GROUND:	return "AUTO_SPIRAL2GROUND,	 ";
	case AUTO_RESURRECT:		return "AUTO_RESURRECT,		 ";
	case AUTO_DEATHSEQUENCE:	return "AUTO_DEATHSEQUENCE,	 ";
	case AUTO_CRASHSKID:		return "AUTO_CRASHSKID,		 ";
	case AUTO_CRASHROLL:		return "AUTO_CRASHROLL,		 ";
		                                              
	case AUTO_BOMB:             return "AUTO_BOMB, ";
	case AUTO_COVER:            return "AUTO_COVER, ";
	case AUTO_STRAFFE:          return "AUTO_STRAFFE, ";
	case AUTO_BALLOON:          return "AUTO_BALLOON, ";
	case AUTO_RECONN:           return "AUTO_RECONN, ";
	case AUTO_ARTSPOT:          return "AUTO_ARTSPOT, ";
	case AUTO_HITWATER:		    return "AUTO_HITWATER,		 ";
		                                              
	case AUTO_TRACKINGBOGIE:	return "AUTO_TRACKINGBOGIE,	 ";
	case AUTO_TRACKINGBANDIT:   return "AUTO_TRACKINGBANDIT, ";
	case AUTO_PRECOMBAT:		return "AUTO_PRECOMBAT,		 ";
	case AUTO_LANDING:          return "AUTO_LANDING, ";
	case AUTO_FAC:              return "AUTO_FAC, ";
	case AUTO_CAS:              return "AUTO_CAS, ";
	case AUTO_ACCELERATE:       return "AUTO_ACCELERATE, ";
	case AUTO_MISSIONDICETHROW: return "AUTO_MISSIONDICETHROW, ";
	case AUTO_COMMSACCEL:	    return "AUTO_COMMSACCEL,	 ";
	case GROUND_TOGLOBREF:      return "GROUND_TOGLOBREF, ";
	case	AUTO_COMBAT:		return "AUTO_COMBAT ";
	}
	return"*** NO VALID MOVECODE ***";
}
#endif
void mobileitem::DosMove (int timeofday,WorldStuff* worldref)
{
// Set fx random numbers...

	if (_DPlay.Implemented)												
	{
		_DPlay.damageRandom = _DPlay.effectRandom = 32768;
	}
	else
	{
		_DPlay.damageRandom = Math_Lib.rnd();
		_DPlay.effectRandom = Math_Lib.rnd();
	}

	timerseed=UByte(timeofday);
	mobileitem::timeofday=timeofday;


	WorldStuff &world = *worldref;

	Art_Int.VisibleCheck();
	Art_Int.CollisionCheck();

#ifndef EMIT_HM_DATA
	mobileitem::MoveAll(world);	
#endif

	if (Three_Dee.livelist)
		Three_Dee.livelist->Event();

	TransientItem::MoveAllTrans(world);

	if (	(Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW)	
		&&	!Persons2::PlayerSeenAC->Status.deadtime								)	
	{
		Persons2::PlayerGhostAC->CheckManualCourse();					  
		//other code may change these in ghost							  
		Persons2::PlayerSeenAC->waypoint=Persons2::PlayerGhostAC->waypoint;
		Persons2::PlayerSeenAC->leader=Persons2::PlayerGhostAC->leader;
		Persons2::PlayerSeenAC->follower=Persons2::PlayerGhostAC->follower;
		Persons2::PlayerSeenAC->fly.nextflight=Persons2::PlayerGhostAC->fly.nextflight;
		Persons2::PlayerSeenAC->fly.leadflight=Persons2::PlayerGhostAC->fly.leadflight;
		Persons2::PlayerSeenAC->ai.unfriendly=Persons2::PlayerGhostAC->ai.unfriendly;
		Persons2::PlayerSeenAC->overview_slowdownleader = Persons2::PlayerGhostAC->overview_slowdownleader;	//CSB 08/07/99
		Persons2::PlayerSeenAC->formation = Persons2::PlayerGhostAC->formation;	
		Persons2::PlayerSeenAC->overview_movecode=Persons2::PlayerGhostAC->overview_movecode;
		Persons2::PlayerSeenAC->formpos=Persons2::PlayerGhostAC->formpos;
		Persons2::PlayerSeenAC->information<<=Persons2::PlayerGhostAC->information;
		Persons2::PlayerSeenAC->ai.manoeuvre<<=Persons2::PlayerGhostAC->ai.manoeuvre;
		Persons2::PlayerSeenAC->ai.ManStep<<=Persons2::PlayerGhostAC->ai.ManStep;
	}

	if (!_Replay.Playback) 
	{
		if(Persons2::PlayerSeenAC->classtype->aerobaticfactor == AEROBATIC_LOW)
		{
		}
		else
		{
			#ifndef EMIT_HM_DATA
			Manual_Pilot.MainManualPilot();
			#endif
		}
	}
	else
 	{
		UWord	oldsector=	world.GetSector(Persons2::PlayerSeenAC);

		_DPlay.CheckSeen();

		Persons2::PlayerSeenAC->World.X=Persons2::PlayerGhostAC->World.X;
		Persons2::PlayerSeenAC->World.Y=Persons2::PlayerGhostAC->World.Y;
		Persons2::PlayerSeenAC->World.Z=Persons2::PlayerGhostAC->World.Z;
		Persons2::PlayerSeenAC->hdg.a=Persons2::PlayerGhostAC->hdg.a;
		Persons2::PlayerSeenAC->pitch.a=Persons2::PlayerGhostAC->pitch.a;
		Persons2::PlayerSeenAC->roll.a=Persons2::PlayerGhostAC->roll.a;
		Persons2::PlayerSeenAC->vel_=Persons2::PlayerGhostAC->vel_;

		_DPlay.BackupSeen();

// set up animations for flaps,brakes

		PAERODEVICE pAeroDevice = Persons2::PlayerSeenAC->fly.pModel->DeviceList;
		while (pAeroDevice != NULL)
		{
			pAeroDevice->Action (Persons2::PlayerSeenAC, AeroDevice::CT_AUTO,FALSE);
			pAeroDevice = pAeroDevice->List.NextItem ();
		}

// do animations for flaps, brakes


		UWord	newsector=	world.GetSector(Persons2::PlayerSeenAC);
		if (newsector!=oldsector)
		{
			world.RemoveFromSector(Persons2::PlayerSeenAC,oldsector);
			world.AddToWorld(Persons2::PlayerSeenAC);
		}
		Persons2::PlayerSeenAC->uniqueID.changed = FALSE;		
	}

// collisions against non-transient items

	if (!_Replay.Playback)					
	{
		Trans_Obj.PilotedACHit();					//make this last - 4 comms
	}

	#ifdef EMIT_HM_DATA
		Persons2::PlayerSeenAC->fly.pModel->EmitHMData(Manual_Pilot.ControlledAC2);
	#endif

	if (!_Replay.Playback)												
	{
		if (Manual_Pilot.controlmode==ManualPilot::MANUAL)				
			Trans_Obj.ControlKeybWeap(Persons2::PlayerSeenAC,world);	
		else
			_Miles.StopShooting();							

		//We do still want to be able to eject when we want to...
		if (Key_Tests.KeyPress3d(EJECTPILOT))				
 		{
			if (!Persons2::PlayerSeenAC->fly.pModel->GearTouched)
			{
				MinAnimData*	mad = (MinAnimData*)Persons2::PlayerSeenAC->Anim;	
				if (	!mad->IsInvisible								
					&&	(mad->itemstate != DEAD)	)					
				{
 					if (_DPlay.Implemented)
					{
						if (_DPlay.GameType>DPlay::TEAMPLAY)
 							_DPlay.NewSpecial(DPlay::PIDC_EJECT);			
					}
					else if (_Replay.Record)
					{
						_DPlay.NewSpecial(DPlay::PIDC_EJECT);			
					}
 					else
	 					Trans_Obj.LaunchCanopyEject(Persons2::PlayerSeenAC,world);
				}
			}

		}
	}
	timerseed=0; 
	//other code (weapons) may change these in seen							  

	if(Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW)	
	{																	
		Persons2::PlayerGhostAC->waypoint=		Persons2::PlayerSeenAC->waypoint;
		Persons2::PlayerGhostAC->leader=		Persons2::PlayerSeenAC->leader;
		Persons2::PlayerGhostAC->follower=		Persons2::PlayerSeenAC->follower;
		Persons2::PlayerGhostAC->fly.nextflight=Persons2::PlayerSeenAC->fly.nextflight;
		Persons2::PlayerGhostAC->fly.leadflight=Persons2::PlayerSeenAC->fly.leadflight;
		Persons2::PlayerGhostAC->ai.unfriendly=Persons2::PlayerSeenAC->ai.unfriendly;
		Persons2::PlayerGhostAC->overview_slowdownleader = Persons2::PlayerSeenAC->overview_slowdownleader;	
		Persons2::PlayerGhostAC->formation = Persons2::PlayerSeenAC->formation;	
		Persons2::PlayerGhostAC->overview_movecode=Persons2::PlayerSeenAC->overview_movecode;
		Persons2::PlayerGhostAC->formpos=Persons2::PlayerSeenAC->formpos;
		Persons2::PlayerGhostAC->information<<=Persons2::PlayerSeenAC->information;
		Persons2::PlayerGhostAC->ai.manoeuvre<<=Persons2::PlayerSeenAC->ai.manoeuvre;
		Persons2::PlayerGhostAC->ai.ManStep<<=Persons2::PlayerSeenAC->ai.ManStep;
	}																	

	Trans_Obj.UpdateRaids();									

	_DPlay.BombCheck(Persons2::PlayerSeenAC);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendPacketToAggregator
//Date			Thu 20 Mar 1997
//------------------------------------------------------------------------------
Bool DPlay::SendPacketToAggregator(LPACPACKET lpAcPacket)
{
	myDPID To=aggID,From=myDPlayID;
	HRESULT res; 

	res=lpDP4->SendEx(From,To,DPSEND_ASYNC|DPSEND_NOSENDCOMPLETEMSG,lpAcPacket,sizeof(ACPACKET),0,0,NULL,NULL);

#ifdef FILELOGS
	if (res!=DP_OK && res!=DPERR_PENDING)
	{
		FILE* fp=fopen("sendpack.txt","at");
		fprintf(fp,"FAILED TO SEND %d error=%d\n",lpAcPacket->Count,res);
		fclose(fp);
	}
#endif

	if (res==DPERR_PENDING || res==DP_OK)
		return TRUE;
	else
		return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendInitPacket
//Date			Thu 5 Sep 1996
//Description	Send First Initialisation Packet
//------------------------------------------------------------------------------
void SendInitPacket ()
{
	_Replay.PlaybackGameState=0;	 //clear flag that we may be playing back on exit
	_Replay.velshifttest=VELSHIFT;

	if (_DPlay.Implemented)
	{
		UWord RndPacket [RNDPACKETSIZE];
		ULong n,From,To;
		HRESULT res;
		char* Buffer;
		ULong BufLen;
		Bool gotone; 

		if (_DPlay.Joining)
		{
			GENERIC p;

			p.PacketID=PID_RANDREQUEST;
			_DPlay.SendMessageToGroup((char*)&p,sizeof(GENERIC));
				
// get initial random numbers

			while (_DPlay.ReceiveNextMessageToMe(Buffer,BufLen,From,DPRECEIVE_TOPLAYER))
			{
				if (From==DPID_SYSMSG)
				{
					_DPlay.ProcessSystemMessage(Buffer);
				}
				else if (From!=_DPlay.aggID)
				{
					if (*(ULong*)Buffer == PID_RANDOMLIST)
					{
						UWord* ptr;
						ptr = (UWord*)Buffer;
						ptr+=sizeof(ULong);// skip PID
						for (n=0; n<RNDPACKETSIZE; n++)
							RndPacket[n] = *ptr++;

						for (n=0; n<(RNDPACKETSIZE - 2); n++)
							Math_Lib.SetRndLookUp(n,RndPacket[n]);

						Math_Lib.Setbval(RndPacket[(RNDPACKETSIZE - 2)]);
						Math_Lib.Setcval(RndPacket[(RNDPACKETSIZE - 1)]);

						break;
					}
					else
					{
						_DPlay.ProcessPlayerMessage(Buffer,BufLen,From);
					}
				}
			}

			for (int sq=0;sq<=PT_GER_NONFLY;sq++)				
				GR_Pack_Sq_Used[sq]=0;

			Math_Lib.ResetRndCount();

			return;
		}

		if (_DPlay.Host)
		{
// Send Random List
			
			for (n=0; n<(RNDPACKETSIZE - 2); n++)
				RndPacket[n] = Math_Lib.GetRndLookUp(n);

			RndPacket[(RNDPACKETSIZE - 2)] = Math_Lib.Getbval();
			RndPacket[(RNDPACKETSIZE - 1)] = Math_Lib.Getcval();

			_DPlay.SendMessageToGroup((char*)&RndPacket,(57*sizeof(UWord)));
			_Replay.BackupGRRandomList();

			_DPlay.CommsStage[DPlay::STAGE_RANDOMLIST][0]=true;
			if (_DPlay.CommsStage[DPlay::STAGE_RANDOMLIST][1])
			{
				_DPlay.SendBackupRandomList(true);
			}
		}
		else
		{
// Receive Random List

			HRESULT res;

			gotone=FALSE;

			ULong now=timeGetTime();

			CommsTimeout time(now,_DPlay.CommsTimeoutLength); 

			while (!gotone)
			{
				now=timeGetTime();

				if (time.TimedOut(now))
					_Error.SayAndQuit("Timed out (SIP)");


				while (_DPlay.ReceiveNextMessageToMe(Buffer,BufLen,From,DPRECEIVE_TOPLAYER))
				{
					if (From==DPID_SYSMSG)
					{
						_DPlay.ProcessSystemMessage(Buffer);
					}
					else if (From!=_DPlay.aggID)
					{
						if (BufLen == (RNDPACKETSIZE * sizeof(UWord)))
						{
							UWord* ptr;
							ptr = (UWord*)Buffer;
							for (n=0; n<RNDPACKETSIZE; n++)
								RndPacket[n] = *ptr++;

							for (n=0; n<(RNDPACKETSIZE - 2); n++)
								Math_Lib.SetRndLookUp(n,RndPacket[n]);

							Math_Lib.Setbval(RndPacket[(RNDPACKETSIZE - 2)]);
							Math_Lib.Setcval(RndPacket[(RNDPACKETSIZE - 1)]);

							gotone=TRUE;

							break;
						}
						else
						{
							_DPlay.ProcessPlayerMessage(Buffer,BufLen,From);
						}
					}
				}
			}
		}

// need to clear squads used here. It is done by host when determining new BField,
// but as guests only process BFields it will not get done, so do it here for all.

		for (int sq=0;sq<=PT_GER_NONFLY;sq++)		
			GR_Pack_Sq_Used[sq]=0;
	}
	else
	{
		_Replay.BackupGRRandomList();
		_Replay.GetInitialGlobRefs();
		_Replay.ResetReplayData();
		_Replay.DelayedWeapon=-1;
		_Replay.DelayedGearUp=false;
		_Replay.StartRecordFlag=FALSE;
		_Replay.StoreHeader=false;
		_Replay.LoadHeader=false;

// set up replay stuff

// need to set these up even if we are not in record in case record is started during game

		_Replay.PlayerSquad=MMC.playersquadron;
		_Replay.PlayerPos=MMC.playeracnum;

		if (_Replay.Playback)
		{
			_Replay.CloseRecordLog();

			_Replay.Playback=FALSE;

			if (_Replay.OpenPlaybackLog())
			{
				if (_Replay.LoadSuperHeaderBeginning())
				{
					_Replay.currentry=_Replay.bfgrlist;
					_Replay.Playback=TRUE;
				}
			}

			if (!_Replay.Playback)
				_Error.EmitSysErr("Error reading playback log");
		}
		else
		if (_Replay.Record)
		{
			_Replay.Record=FALSE;
			if (_Replay.OpenRecordLog())
			{
				if (_Replay.StoreSuperHeaderBeginning())
					_Replay.Record=TRUE;
			}
		}
	}

	_DPlay.SimulateExitKey=FALSE;

// set random list count

	Math_Lib.ResetRndCount();
}

extern int	BAD_RV;

FileNum Persons3::FindCommsNextBf (BattlefieldType& bfctrl)
{
	ClearGlobrefPackVars();

	FileNum filelist;
	char* BFieldPacket;
	char* ptr;
	ULong n,from;
	int val;
	char* RecPacket;
	ULong RecPacketLen=0;

	if (!_DPlay.Implemented)
	{
		if (_Replay.Playback)
		{
			filelist=_Replay.currentry->file;
			bfctrl=(BattlefieldType)_Replay.currentry->bfctrl;
			_Replay.SetGlobRefs(_Replay.currentry->list);
			_Replay.currentry=_Replay.currentry->next;
			_DPlay.SetRandomListPos();	
		}
		else
		{
			if (bfctrl==LOADSCRAMBF)
			{
				Persons2::SetUpDiary();
			}

			filelist=FindNextBf(bfctrl);

			if (!(filelist==FIL_NULL && (int)bfctrl!=(int)FINISHBF))
			{
				_Replay.AddFileAndGlobRefsToList(filelist,bfctrl);
				_DPlay.SetRandomListPos();
			}
		}
	}
	else
	{
		if (_DPlay.Host)
		{
			if (bfctrl==LOADSCRAMBF)
			{
				Persons2::SetUpDiary();
			}
			filelist=FindNextBf(bfctrl);

			if (!(filelist==FIL_NULL && (int)bfctrl!=(int)FINISHBF))
			{
				_Replay.AddFileAndGlobRefsToList(filelist,bfctrl);
				_DPlay.SetRandomListPos();
			}
		}
		else
		{
			if (_DPlay.Joining && !SENT_REQ)
			{
// request bfield packet

				GENERIC packet;

				packet.PacketID=PID_BFIELDREQUEST;
				packet.PlayerID=_DPlay.myDPlayID;

				_DPlay.SendMessageToGroup((char*)&packet,sizeof(GENERIC));

				SENT_REQ=TRUE;
			}

			Bool gotone=FALSE;
			
			ULong now=timeGetTime();
			CommsTimeout time(now,_DPlay.CommsTimeoutLength*6);

			if (_DPlay.ProcessRequiredBFieldPacket((ULong&)bfctrl,filelist))
			{
				_DPlay.BFieldToProcess++;
			}
			else
			{
				while (!gotone)
				{
					now=timeGetTime();
					if (time.TimedOut(now))
						_Error.SayAndQuit("Timed out (FCNB)");

					if (_DPlay.ReceiveNextMessageToMe (RecPacket, RecPacketLen,from,DPRECEIVE_TOPLAYER))
					{
						if (from==DPID_SYSMSG)
						{
							_DPlay.ProcessSystemMessage(RecPacket);
						}
						else if (from!=_DPlay.aggID)
						{
							if(*(ULong*)RecPacket == PID_BFIELDPACKETIDENT)
							{
								_DPlay.StoreReceivedBField(RecPacket,RecPacketLen);

								if (_DPlay.ProcessRequiredBFieldPacket((ULong&)bfctrl,filelist))
								{
									_DPlay.BFieldToProcess++;
									gotone=TRUE;
								}
							}
							else
							{
								_DPlay.ProcessPlayerMessage(RecPacket,RecPacketLen,from);
							}
						}
					}
				}
			}

			_DPlay.SetRandomListPos();
		}
	}
	if (_DPlay.Joining && _DPlay.GameType<DPlay::COMMSQUICKMISSION)
	{
// need to nobble global reference dealing with my ac so that I start with
// one selected, not one originally put in game as dummy!

		GR_Scram_Squad[_DPlay.mySlot]=DPlay::H2H_Player[_DPlay.mySlot].squadron;
	}
	ResetGlobrefPackVars();	 //Waypoints stuff!
	return filelist;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendInit2Packet
//Date			Thu 5 Sep 1996
//Description	Send Second Initialisation Packet
//------------------------------------------------------------------------------
void SendInit2Packet ()
{
	_DPlay.ResetDeltas();
	_DPlay.InitBuffers();
	_DPlay.DeleteMyAIACPositionToSendList();

// set up AI CommsOwners (in replay/single player all AI owners are me)
	
	_DPlay.InitialiseOwners();

	if (_DPlay.Implemented)
	{
		_DPlay.CommsStage[DPlay::STAGE_BFIELDS][0]=true;


// if I am aggregator then receive any packets that have been sent to me as
// a result of sends to ID 0 that I have not removed from message Q

		myDPID from=0;
		char*	Buffer;
		DWORD   BufferLen;

		if(_DPlay.Host)
		{
			while (_DPlay.ReceiveNextMessageToMe(Buffer,BufferLen,from,DPRECEIVE_TOPLAYER))
			{
			}
		}

// before starting send to aggregator remove all packets from aggreagtor to me
// that may be hanging around from a previous game session
// done in initsyncphase

		_DPlay.DeleteAIACPositionsList();
		_DPlay.SetUpPlayersAC();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CopyPacket
//Description	Add contents of an aircraft packet onto AirStruc 
//------------------------------------------------------------------------------
void DPlay::CopyPacket (AirStrucPtr AC, LPACPACKET lpAcPacket)
{
	UWord	oldsector= MobileItem::currworld->GetSector(*AC);
	SLong	val;
	UByte	shift=lpAcPacket->Shift;

// add deltas to ac position

#define ADDDELTAS(src,dest,shift)	\
	{								 \
		if (src>127)					\
		{								 \
			val=-((src-128)<<shift);	  \
		}								   \
		else								\
		{									 \
			val=src<<shift;					  \
		}									   \
		dest+=val;								\
	}

	ADDDELTAS(lpAcPacket->X,AC->World.X,shift)
	ADDDELTAS(lpAcPacket->Y,AC->World.Y,shift)
	ADDDELTAS(lpAcPacket->Z,AC->World.Z,shift)

	if (oldsector!=MobileItem::currworld->GetSector(*AC))
	{
		MobileItem::currworld->RemoveFromSector(*AC,oldsector);
		MobileItem::currworld->AddToWorld(*AC);
	}

// Status ??

 	ADDDELTAS(lpAcPacket->Heading,AC->hdg.a,shift)
	ADDDELTAS(lpAcPacket->Pitch,AC->pitch.a,shift)
	ADDDELTAS(lpAcPacket->Roll,AC->roll.a,shift)

	if (lpAcPacket->Heading>127)
	{								 
		val=-((lpAcPacket->Heading-128)<<shift);	  
	}								   
	else								
	{									 
		val=lpAcPacket->Heading<<shift;					  
	}									   

	AC->fly.dhdg=val/RateDivider;
	AC->fly.cpitch=AC->pitch;

	if(lpAcPacket->Velocity_>127)
	{
		val=-((lpAcPacket->Velocity_-128)<<lpAcPacket->Shift);
	}
	else
	{
		val=+((lpAcPacket->Velocity_)<<lpAcPacket->Shift);
	}

	SLong newvel=abs(val)<<_Replay.velshifttest;

	if (val<0)
		newvel=-newvel;

	AC->vel_+=newvel;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakePacket
//Date			Thu 5 Sep 1996
//Description	construct an Aircraft packet from an AirStruc
//------------------------------------------------------------------------------
void DPlay::MakeDeltaPacket (LPBASICPACKET packet)
{
	UByte	shiftfactor;
	UByte	val;

// want to send deltas from previous position

	shiftfactor=MakeShiftValue();
	packet->Shift=shiftfactor;

#define MAKEDELTAS(src,dest,shift)	  \
	{								   \
		val=(abs(src))>>shift;			\
		if (val!=0 && src<0)			 \
		{								  \
			val|=128;					   \
		}									\
		dest=val;							 \
	}

	MAKEDELTAS(Deltas.lastpos.X,packet->X,shiftfactor);
	MAKEDELTAS(Deltas.lastpos.Y,packet->Y,shiftfactor);
	MAKEDELTAS(Deltas.lastpos.Z,packet->Z,shiftfactor);
	MAKEDELTAS(Deltas.Heading.a,packet->Heading,shiftfactor);
	MAKEDELTAS(Deltas.Pitch.a,packet->Pitch,shiftfactor);
	MAKEDELTAS(Deltas.Roll.a,packet->Roll,shiftfactor);

	MAKEDELTAS((Deltas.Velocity>>_Replay.velshifttest),packet->Velocity_,shiftfactor);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateDeltas
//Date			Wed 26 Aug 1998
//Description	When packet is sent remove sent values from delta record to leave residue
//				of values. These will accumulate to next frame
//------------------------------------------------------------------------------
void DPlay::UpdateDeltas(LPACPACKET lpAcPacket)
{
	UByte	shiftfactor=lpAcPacket->Shift;
	SLong	val;

	val=GetVal(lpAcPacket->X,shiftfactor);
	Deltas.lastpos.X-=val;

	val=GetVal(lpAcPacket->Y,shiftfactor);
	Deltas.lastpos.Y-=val;

	val=GetVal(lpAcPacket->Z,shiftfactor);
	Deltas.lastpos.Z-=val;

	val=GetVal(lpAcPacket->Heading,shiftfactor);
	Deltas.Heading.a-=val;

	val=GetVal(lpAcPacket->Pitch,shiftfactor);
	Deltas.Pitch.a-=val;

	val=GetVal(lpAcPacket->Roll,shiftfactor);

	Deltas.Roll.a-=val;

	val=GetVal(lpAcPacket->Velocity_,shiftfactor);

	SLong newvel=abs(val)<<_Replay.velshifttest;

	if (val<0)
		newvel=-newvel;

	Deltas.Velocity-=newvel;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdatePredictedAC
//Date			Wed 26 Aug 1998
//------------------------------------------------------------------------------
void DPlay::UpdatePredictedAC(LPACPACKET lpAcPacket)
{
	UByte	shiftfactor=lpAcPacket->Shift;
	SLong	val;
	
	val=GetVal(lpAcPacket->X,shiftfactor);

	Persons2::PlayerGhostAC->World.X+=val;

	val=GetVal(lpAcPacket->Y,shiftfactor);
	Persons2::PlayerGhostAC->World.Y+=val;

	val=GetVal(lpAcPacket->Z,shiftfactor);
	Persons2::PlayerGhostAC->World.Z+=val;

	val=GetVal(lpAcPacket->Heading,shiftfactor);
	Persons2::PlayerGhostAC->hdg.a+=val;

	Persons2::PlayerGhostAC->fly.dhdg=val/RateDivider;		

	val=GetVal(lpAcPacket->Pitch,shiftfactor);
	Persons2::PlayerGhostAC->pitch.a+=val;

	val=GetVal(lpAcPacket->Roll,shiftfactor);
	Persons2::PlayerGhostAC->roll.a+=val;

	val=GetVal(lpAcPacket->Velocity_,shiftfactor);

	SLong newvel=abs(val)<<_Replay.velshifttest;

	if (val<0)
		newvel=-newvel;

	Persons2::PlayerGhostAC->vel_+=newvel;


	Persons2::PlayerGhostAC->fly.cpitch=Persons2::PlayerGhostAC->pitch;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeSpecPacket
//------------------------------------------------------------------------------
UByte DPlay::MakeSpecialPacket (LPBASICPACKET packet, UByte index)
{
// info already compacted into extra bytes
// can just copy into packet

	UByteP ptr1=&packet->IDCode;
	UByteP ptr2=(UByteP)(&SpecBuffer.GetCurr()->IDCode);
	UByte len=PacketLength(SpecBuffer.GetCurr()->IDCode),n;

	ptr1+=index;

// fills in id code and extra bytes from special packet buffer

	for (n=0;n<len;n++)
	{
		*ptr1++=*ptr2++;
	}

	SpecBuffer.UpdateCurr();

	while (SpecBuffer.GetCurr()->IDCode==PIDC_DONTSEND && SpecBuffer.GetCurr()!=SpecBuffer.GetNext())
		SpecBuffer.UpdateCurr();

	return len;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeCollPacket
//Date			Mon 20 Jul 1998
//------------------------------------------------------------------------------
UByte	DPlay::MakeCollPacket(LPBASICPACKET packet,UByte index)
{
// new collision packet is:
// UID hitter	14 bits
// UID hit		14 bits
// HitterInfo	9 bits	(coltype = 3, colstrength = 6)
// HitData		9 bits

// strength is in last 6 bits of IDCode
// bottom 8 bits of UID of target in byte1
// top 6 bits of UID if target in byte 2 along with top 2 bits of type
// bottom bit of type in byte 3, along with bottom 7 bits of hitdata
// top 2 bits of hitdata in byte4, along with top 6 bits of shooter
// bottom 8 bits of shooter in byte 5

	UByte ID;
	
#ifndef NDEBUG
	if (CollBuffer.GetCurr()->str>63)
		INT3;
#endif

	ID=CollBuffer.GetCurr()->str;

#ifndef NDEBUG
	if (ID>63)
		INT3;
#endif

	ID|=(PT_COLLISION<<6);


#ifndef NDEBUG
	if (CollBuffer.GetCurr()->type>7)
		INT3;
#endif

	UByteP ptr=&packet->IDCode;

	ptr+=index;
	*ptr++=ID;

 	*ptr++=(UByte)(CollBuffer.GetCurr()->id&0xff);//byte1

 	*ptr=(UByte)((CollBuffer.GetCurr()->id>>8)&0x3f);//byte2
 	*ptr+=(UByte)((CollBuffer.GetCurr()->type<<5)&0xc0);//byte2
	*ptr++;

 	*ptr=(UByte)(CollBuffer.GetCurr()->type&0x01);//byte3
 	*ptr+=(UByte)((CollBuffer.GetCurr()->offset&0x7f)<<1);//byte3
	*ptr++;

 	*ptr=(UByte)((CollBuffer.GetCurr()->offset>>7)&0x03)<<6;//byte4
 	*ptr+=(UByte)((CollBuffer.GetCurr()->hitterscorer>>8)&0x3f);//byte4
 	*ptr++;

 	*ptr++=(UByte)(CollBuffer.GetCurr()->hitterscorer&0xff);//byte5

#ifndef NDEBUG
	UWord uid,shooteruid;
	UWord offset;												
	UByte type;
	UWord temp;

	temp=packet->byte1;
	temp+=(packet->byte2&0x3f)<<8;
	uid=(UniqueID)(temp);

	assert(uid==CollBuffer.GetCurr()->id);

	type=(packet->byte2&0xc0)>>5;
	type+=packet->byte3&0x01;

	assert (type==CollBuffer.GetCurr()->type);

	offset=(packet->byte3>>1)&0x7f;
	offset+=((packet->byte4>>6)&0x03)<<7;

	assert (offset==CollBuffer.GetCurr()->offset);

	shooteruid=(packet->byte4&0x3f)<<8;
	shooteruid+=packet->byte5;

	assert (shooteruid==CollBuffer.GetCurr()->hitterscorer);

	item* test;
	test=Persons2::ConvertPtrUID(UniqueID(uid));
	test=Persons2::ConvertPtrUID(UniqueID(shooteruid));

#endif

#ifdef COLLPACKINFO
	FILE* fp=fopen("collsend.txt","at");
	fprintf(fp,"str=%d type=%d trg=%d offset=%d shooter=%d\n",
		CollBuffer.GetCurr()->str,
		CollBuffer.GetCurr()->type,
		CollBuffer.GetCurr()->id,
		CollBuffer.GetCurr()->offset,
		CollBuffer.GetCurr()->hitterscorer);
	fclose(fp);
#endif

	CollBuffer.UpdateCurr();

	while (CollBuffer.GetCurr()->IDCode==PIDC_DONTSEND && CollBuffer.GetCurr()!=CollBuffer.GetNext())
		CollBuffer.UpdateCurr();

	return (PacketLength(PIDC_COLLISION));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewBullet
//Date			Thu 5 Sep 1996
//Description	Adds a new bullet to a table of bullets for transmission
//------------------------------------------------------------------------------
void	DPlay::NewBullet (ULong num, ULong index)
{
	if (CommsOrReplay())
	{
// instead of causing an error if table is full, overwrite oldest entry ?????

 		if(BulletBuffer.NumEntries()>=BufferSize)			
		{	
			BulletBuffer.UpdateCurr();
		}
		 
 		BulletBuffer.GetNext()->num=num;
 		BulletBuffer.GetNext()->index=index;

		if (Implemented)
			BulletBuffer.GetNext()->framelaunched=FrameCount;
		else
			BulletBuffer.GetNext()->framelaunched=_Replay.replayframecount;

		BulletBuffer.AddEntryAndUpdateNext();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PredictMove
//Date			Mon 24 Feb 1997
//Description	predict move for ac
//------------------------------------------------------------------------------
void DPlay::PredictMove(AirStruc* ac)
{
	SLong bvx,bvy,bvz; 
	bool	store=false;

// backup current vels as the ones that of calculated here are used only for
// prediction purposes, not for anything else.

	if (ac==Persons2::PlayerGhostAC || ac->uniqueID.commsmove)
	{
		store=true;
		bvx=ac->vel_x;
		bvy=ac->vel_y;
		bvz=ac->vel_z;
	}

	ac->CalcXYZVel();
	ac->mobileitem::NewPosition();

	if (store)
	{
		ac->vel_x=bvx;
		ac->vel_y=bvy;
		ac->vel_z=bvz;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PredictGoodMovement
//Date			Mon 21 Dec 1998
//------------------------------------------------------------------------------
void	DPlay::PredictGoodMovement(UWord slot)
{
	AirStruc tempac;

// OK, what is this dudes predicted movement?
// set up tempac with good position and do a dummy predict

	tempac.uniqueID.count=UID_NULL;
	tempac.uniqueID.commsmove=TRUE;
	tempac.World.X=HistPosBuffer[slot].GetNext()->Pos.X;
	tempac.World.Y=HistPosBuffer[slot].GetNext()->Pos.Y;
	tempac.World.Z=HistPosBuffer[slot].GetNext()->Pos.Z;
	tempac.hdg.a=HistPosBuffer[slot].GetNext()->Heading.a;
	tempac.pitch.a=HistPosBuffer[slot].GetNext()->Pitch.a;
	tempac.roll.a=HistPosBuffer[slot].GetNext()->Roll.a;
	tempac.vel_=HistPosBuffer[slot].GetNext()->Velocity;
	tempac.fly.cpitch.a=tempac.pitch.a;

	for (int n=0;n<RateDivider;n++)
		PredictMove(&tempac);

	HistPosBuffer[slot].GetNext()->Pos.X=tempac.World.X;
	HistPosBuffer[slot].GetNext()->Pos.Y=tempac.World.Y;
	HistPosBuffer[slot].GetNext()->Pos.Z=tempac.World.Z;
	HistPosBuffer[slot].GetNext()->Heading.a=tempac.hdg.a;
	HistPosBuffer[slot].GetNext()->Pitch.a=tempac.pitch.a;
	HistPosBuffer[slot].GetNext()->Roll.a=tempac.roll.a;
	HistPosBuffer[slot].GetNext()->Velocity=tempac.vel_;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddDeltas
//Date			Mon 24 Feb 1997
//Description	add (sign=TRUE) or subtract (sign=FALSE) current position
//				from players delta record
//------------------------------------------------------------------------------
void DPlay::AddDeltas(AirStruc* AC, Bool sign, UByte caller)
{
	if(sign)
	{
#ifndef NDEBUG
#ifdef DELTACHECK
		FILE* fp=fopen("deltachk.txt","at");
#endif
		if (AC==Persons2::PlayerGhostAC)
		{
#ifdef DELTACHECK
			fprintf(fp,"ADD Ghost Caller=%d\n",caller);
#endif
			currghostsign++;
			if (currghostsign==2)
				INT3;
		}
		else if (AC==Persons2::PlayerSeenAC)
		{
#ifdef DELTACHECK
			fprintf(fp,"ADD Seen Caller=%d\n",caller);
#endif
			currseensign++;
			if (currseensign==2)
				INT3;
		}
		else
		{
			INT3;
		}
#ifdef DELTACHECK
		fclose(fp);
#endif
#endif

		Deltas.lastpos.X+=AC->World.X;
		Deltas.lastpos.Y+=AC->World.Y;
		Deltas.lastpos.Z+=AC->World.Z;

		Deltas.Heading.a+=AC->hdg.a;

		Deltas.Pitch.a+=AC->pitch.a;

		Deltas.Roll.a+=AC->roll.a;

		Deltas.Velocity+=AC->vel_;

// this is OK, though if the deltas get this large then something has probably
// gone wrong

		if(Deltas.Velocity>2147483647)								  
		{
			INT3;
			Deltas.Velocity-=2147483648;							 
		}
	}
	else
	{
#ifndef NDEBUG
#ifdef DELTACHECK
		FILE* fp=fopen("deltachk.txt","at");
#endif
		if (AC==Persons2::PlayerGhostAC)
		{
#ifdef DELTACHECK
			fprintf(fp,"SUB Ghost Caller=%d\n",caller);
#endif
			currghostsign--;
			if (currghostsign==-2)
				INT3;
		}
		else if (AC==Persons2::PlayerSeenAC)
		{
#ifdef DELTACHECK
			fprintf(fp,"SUB Seen Caller=%d\n",caller);
#endif
			currseensign--;
			if (currseensign==-2)
				INT3;
		}
		else
		{
			INT3;
		}
#ifdef DELTACHECK
		fclose(fp);
#endif
#endif
		Deltas.lastpos.X-=AC->World.X;
		Deltas.lastpos.Y-=AC->World.Y;
		Deltas.lastpos.Z-=AC->World.Z;

		Deltas.Heading.a-=AC->hdg.a;

		Deltas.Pitch.a-=AC->pitch.a;

		Deltas.Roll.a-=AC->roll.a;

		Deltas.Velocity-=AC->vel_;;

		if(Deltas.Velocity<-2147483647)								 
		{
			INT3;
			Deltas.Velocity+=2147483648;							 
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeShiftValue
//Date			Wed 26 Feb 1997
//Description	determines shift byte to apply to deltas
//				this is done by looking at the highest value and detemining
//				how much of a shift is required to bring the most sig. bit 
//				into specified number of bits
//------------------------------------------------------------------------------
UByte DPlay::MakeShiftValue()
{
	ULong	maxnum;
	ULong	highestbit;
	ULong	n;

// get biggest absolute number

 	maxnum=max(abs(Deltas.Velocity>>_Replay.velshifttest),abs(Deltas.Roll.a));

	maxnum=max(maxnum,abs(Deltas.Heading.a));
	maxnum=max(maxnum,abs(Deltas.Pitch.a));
	maxnum=max(maxnum,abs(Deltas.lastpos.Z));
	maxnum=max(maxnum,abs(Deltas.lastpos.X));
	maxnum=max(maxnum,abs(Deltas.lastpos.Y));

// determine highestbit

// if highest number can be represented in 7 bits then no shift required

	if(maxnum<128) return 0;

// shift is represented by 4 bits => max shift=15

	for(n=1;n<16;n++)
	{
		if((maxnum>>n)<128)
		{
#ifdef DELTALOG
	FILE* fp=fopen("deltalog.txt","at");
	FILE* pp=fopen("deltatot.txt","at");

	ULong minnum;
	static vals[2][7];//x,y,z,h,p,r,v

	minnum=min(abs(Deltas.Velocity),abs(Deltas.Roll.a));
	minnum=min(minnum,abs(Deltas.Heading.a));
	minnum=min(minnum,abs(Deltas.Pitch.a));
	minnum=min(minnum,abs(Deltas.lastpos.Z));
	minnum=min(minnum,abs(Deltas.lastpos.X));
	minnum=min(minnum,abs(Deltas.lastpos.Y));

	char min,max;

	if (minnum==abs(Deltas.Velocity))
	{
		min='V';
		vals[0][6]++;
	}
	else if (maxnum==abs(Deltas.Velocity))
	{
		max='V';
		vals[1][6]++;
	}

	if (minnum==abs(Deltas.lastpos.X))
	{
		min='X';
		vals[0][0]++;
	}
	else if (maxnum==abs(Deltas.lastpos.X))
	{
		max='X';
		vals[1][0]++;
	}

	if (minnum==abs(Deltas.lastpos.Y))
	{
		min='Y';
		vals[0][1]++;
	}
	else if (maxnum==abs(Deltas.lastpos.Y))
	{
		max='Y';
		vals[1][1]++;
	}

	if (minnum==abs(Deltas.lastpos.Z))
	{
		min='Z';
		vals[0][2]++;
	}
	else if (maxnum==abs(Deltas.lastpos.Z))
	{
		max='Z';
		vals[1][2]++;
	}

	if (minnum==abs(Deltas.Heading.a))
	{
		min='H';
		vals[0][3]++;
	}
	else if (maxnum==abs(Deltas.Heading.a))
	{
		max='H';
		vals[1][3]++;
	}

	if (minnum==abs(Deltas.Pitch.a))
	{
		min='P';
		vals[0][4]++;
	}
	else if (maxnum==abs(Deltas.Pitch.a))
	{
		max='P';
		vals[1][4]++;
	}

	if (minnum==abs(Deltas.Roll.a))
	{
		min='R';
		vals[0][5]++;
	}
	else if (maxnum==abs(Deltas.Roll.a))
	{
		max='R';
		vals[1][5]++;
	}


	fprintf(fp,"dX=%d dY=%d dZ=%d dH=%d dP=%d dR=%d dV=%d S=%d MIN=%d(%c) MAX=%d(%c)\n",
		Deltas.lastpos.X,
		Deltas.lastpos.Y,
		Deltas.lastpos.Z,
		Deltas.Heading.a,
		Deltas.Pitch.a,
		Deltas.Roll.a,
		Deltas.Velocity,
		n,
		minnum,
		min,
		maxnum,
		max);

	fprintf(pp,"MIN: X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d\n",
		vals[0][0],
		vals[0][1],
		vals[0][2],
		vals[0][3],
		vals[0][4],
		vals[0][5],
		vals[0][6]);

	fprintf(pp,"MAX: X=%d Y=%d Z=%d H=%d P=%d R=%d V=%d\n",
		vals[1][0],
		vals[1][1],
		vals[1][2],
		vals[1][3],
		vals[1][4],
		vals[1][5],
		vals[1][6]);

	fclose(pp);
	fclose(fp);
#endif

			return n;
		}
	}

// in time accel deltas may be very big, so allow return value of 15. May require several
// frames to transmit a large delta, but will be OK in the end.

	return 15;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendGonePacket
//Date			Tue 25 Mar 1997
//Description	Sends a packet containing IDCode IDC_PLAYERGONE to aggregator
//------------------------------------------------------------------------------
void DPlay::SendGonePacket()
{
	myDPID from;
	ULong	n;
	GENERIC p;

	if(!Host)
	{
		p.PacketID=PID_GUESTLEAVING;

	}
	else
	{
// to do this via aggregator would require simulating everybodys packet so that
// it gets processed. This cannot be worked out so use a normal packet saying,
// OK, everybody out

		p.PacketID=PID_HOSTLEAVING;
	}

	SendMessageToGroup((char*)&p,sizeof(GENERIC));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessPlayerGone
//Date			Mon 12 May 1997
//Inputs		dplayID of player who has left, whether player was in 3d
//------------------------------------------------------------------------------
void DPlay::ProcessPlayerGone(ULong playerDPID,Bool in3d) 
{
	ULong n,slot=0;

	if (in3d)
	{
// if I'm not in 3D dont do this 

		if ((H2H_Player+mySlot)->status!=CPS_3D)
			return;												

		slot=DPID2Slot(playerDPID);

		if (slot==MAXPLAYERS)
			return;

// this is necesary												
		if (H2H_Player[slot].status!=CPS_3D)					
			return;												

// ensure that multiple player gone messages dont cause problem

		ActivePlayers&=(ULong)(~(1<<slot));

		if(CurrPlayers)
			CurrPlayers--;

		(H2H_Player+slot)->status=CPS_READYROOM;						

		UniqueID thisid=UID_Null;

		for (n=0; n<MAXPLAYERS; n++)
		{
			if (n == slot)
			{
				thisid = (UniqueID)AllocPacket [n];
				break;
			}
		}

		if (thisid!=UID_Null)
		{
			AirStrucPtr thisac=NULL;
			thisac = (AirStrucPtr)Persons2::ConvertPtrUID (thisid);

			DisplayPlayerMessage(thisac,thisac,ST_PLAYERLEFTGAME,0);

			if (thisac)
			{
				if (GameType<COMMSQUICKMISSION)
				{
// for players who have gone, put aircraft at 20000 feet

					thisac->World.Y = FT_20000;

					MinAnimData* mad = (MinAnimData* )thisac->Anim;
					mad->itemstate = DEAD;
					mad->IsInvisible=1;				

					if (thisac == Persons2::PlayerSeenAC)
						Manual_Pilot.controlmode=ManualPilot::PILOTDEAD;

					thisac->Status.deaded=TRUE;
					thisac->Status.deadtime=1;
				}
				else
				{
// place player AC under AI control

					SwitchPlayerACToAIAC(thisac);
				}
			}
		}
	}
	else
	{
//check to make sure that this player exists in my game before removing

		slot=DPID2Slot(playerDPID);

		if (slot==MAXPLAYERS)
			return;

		if(Host)		
		{
			lpDP4->DestroyPlayer(playerDPID);
		}

		H2H_Player[slot].dpid=0;
		H2H_Player[slot].name[0]=0;
		H2H_Player[slot].status=CPS_NONE;
		H2H_Player[slot].dialogue[0]=0;
		H2H_Player[slot].kills=0;
		H2H_Player[slot].deaths=0;
		H2H_Player[slot].assists=0;
		H2H_Player[slot].position=-1;
		H2H_Player[slot].squadron=-1;
		H2H_Player[slot].MyTeam=TS_UNASSIGNED;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CommitSuicide
//Date			Thu 19 Jun 1997
//Description	If player has been killed, then allow an immediate 
//				resurrect, to stop tedious decent to ground
//------------------------------------------------------------------------------
void	DPlay::CommitSuicide()
{
	if (Implemented)
	{
		if (Persons2::PlayerSeenAC->Status.deaded && AllowSuicide && timeGetTime()>SuicideTime)
		{
			SuicideTime=0;
			AllowSuicide=FALSE;
			viewtime=false;

// in resurrectme flight model is initialised which can cause slight rounding
// errors in deltas

			CheckSeen();
			AddDeltas(Persons2::PlayerSeenAC,FALSE,5); 
			ResurrectMe(Persons2::PlayerSeenAC,true);
			AddDeltas(Persons2::PlayerSeenAC,TRUE,5); 
			BackupSeen();
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendNeedResyncMessage
//Date			Wed 19 Nov 1997
//------------------------------------------------------------------------------
void	DPlay::SendNeedResyncMessage()
{
	GENERIC packet;

	packet.PacketID=PID_NEEDRESYNC;

	SendMessageToGroup((char*)&packet,sizeof(GENERIC));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetState
//Date			Wed 19 Nov 1997
//Description	set frame num to 0
//				clear buffers - packet,damage,collision,bullet
//				reset array latencies
//------------------------------------------------------------------------------
void	DPlay::ResetState()
{
	FrameCount=0;
	firsttimein=TRUE;
	synched=FALSE;
	csync=false;
	ResetDeltas();
	ResetSync=true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendResyncMessage
//Date			Wed 19 Nov 1997
//------------------------------------------------------------------------------
void	DPlay::SendResyncMessage()
{
	ACSTATEPACKET packet;
	ULong num,datasize,n;
	UByteP datapack,temp;
	UWord deltaoffset;
	UByte newbyte;

	AirStrucPtr gac=Persons2::PlayerGhostAC;
	AirStrucPtr sac=Persons2::PlayerSeenAC;

	gac->World.X=sac->World.X;
	gac->World.Y=sac->World.Y;
	gac->World.Z=sac->World.Z;
 
	gac->hdg.a=sac->hdg.a;
	gac->pitch.a=sac->pitch.a;
	gac->roll.a=sac->roll.a;
	gac->vel_=sac->vel_;

	gac->fly.cpitch=sac->pitch;

	packet.PacketID=PID_RESYNC;

	packet.Pos.X=gac->World.X;
	packet.Pos.Y=gac->World.Y;
	packet.Pos.Z=gac->World.Z;

	packet.Heading.a=gac->hdg.a;
	packet.Pitch.a=gac->pitch.a;
	packet.Roll.a=gac->roll.a;
	packet.Velocity=gac->vel_;

	packet.MyKills=(H2H_Player+mySlot)->kills;
	packet.MyAssists=(H2H_Player+mySlot)->assists;
	packet.MyDeaths=(H2H_Player+mySlot)->deaths;

	if (!sac->Status.deaded)
		packet.alive=TRUE;
	else
		packet.alive=FALSE;

	if (resurrectend)
	{
		packet.resurrect=true;
		Persons2::PlayerSeenAC->Status.deaded=FALSE;
	}
	else
		packet.resurrect=false;

	if (JustJoined)
	{
		joiningplayerslot=mySlot;
		packet.joining=true;
	}
	else
		packet.joining=false;

// add anim data to packet

	num=SHAPE.ScanAnimData((ItemPtr)sac);

	datasize=sizeof(ACSTATEPACKET)+sizeof(ULong)+(num*(sizeof(UWord)+sizeof(UByte)));
	datasize+=sizeof(int); //timeofday

	datasize+=sizeof(UWord); // shape

	datapack=new UByte[datasize];
	temp=datapack;

	CopyMemory(temp,&packet,sizeof(ACSTATEPACKET));
	temp+=sizeof(ACSTATEPACKET);

	int time=_Replay.inst->timeofday;
	*(int*)temp=time;
	temp+=sizeof(int);

	MakeAnimPack(num,temp,sac->shape);

	SendMessageToGroup((char*)datapack,datasize);

	delete [] datapack;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BeginSyncPhase
//Date			Wed 19 Nov 1997
//------------------------------------------------------------------------------
void	DPlay::BeginSyncPhase()
{
#ifdef SYNCDATA
	FILE* fp=fopen("resync.txt","at");
	fprintf(fp,"BSP: Initiator=%d\n",Initiator);
	fclose(fp);
#endif

	ResyncPhase=TRUE;
	WorldSyncPhase=FALSE;
	ResetState();
	deadplayers=0;

	if (Initiator)
	{
		SendNeedResyncMessage();
	}
	if (Host)
	{
		_Agg.Running=FALSE;
		_Agg.StopResetAggregator();
	}

// want to reset world sync at beginning of normal sync

	InitSyncData(true);
	resetreceivesync=true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReceiveSyncPackets
//Date			Wed 19 Nov 1997
//------------------------------------------------------------------------------
Bool	DPlay::ReceiveSyncPackets()
{
	static ULong needed=0;
	static ULong now=0;

	char* Buffer;
	ULong	BufLen;
	ULong	from,n;
	LPACSTATEPACKET packet;

#ifdef SYNCDATA
	FILE* fp=fopen("resync.txt","at");
#endif

	if (resetreceivesync)
	{
		resetreceivesync=false;
#ifdef SYNCDATA
		fprintf(fp,"resyncsgot=%d\n",resyncsgot);
#endif
		needed=ActivePlayers^(1<<mySlot);

		SendResyncMessage();
#ifdef SYNCDATA 
		fprintf(fp,"Sent resync message. Needed=%d\n",needed);
#endif
		now=timeGetTime();
	}
	
	while (ReceiveNextMessageToMe(Buffer,BufLen,from,DPRECEIVE_TOPLAYER))
	{
		if (from==DPID_SYSMSG)
		{
			ProcessSystemMessage(Buffer);
		}
		else if (from!=aggID)
		{
			packet=(LPACSTATEPACKET)Buffer;

			if (packet->PacketID==PID_RESYNC) 
			{
// update ac postion etc

				n=DPID2Slot(from);

				if (n!=MAXPLAYERS)
				{
					ProcessResyncPacket(packet,n);
#ifdef SYNCDATA 
					fprintf(fp,"received resync packet from slot %d\n",n);
					fprintf(fp,"resyncsgot=%d\n",resyncsgot);
#endif
				}
			}
			else
			{
				ProcessPlayerMessage(Buffer,BufLen,from);
			}
		}
	}

	if (resyncsgot==needed)
	{
// need to get battle position b4 sending position!!!!!!!!!!!!!!!!
// can work out once all packets have been received
// for player that this is affecting flight model must be updated

		if (joiningplayerslot>=0)
		{
			if (GameType<COMMSQUICKMISSION)							
				GetBattlePosition(joiningplayerslot);

			if (joiningplayerslot==mySlot)
			{
// player could teleport quite a distance, best do landscape update

				Land_Scape.RefreshLandscape();
			}

			joiningplayerslot=-1;
		}
// if initial resync does not work and host begins a new one then joining
// player will not be initiator which doesnt matter - just get position regardless

		resyncsgot=0;
		needed=0;
#ifdef SYNCDATA 
		fprintf(fp,"resync OK\n");
		fclose(fp);
#endif
		return TRUE;
	}

	if (timeGetTime()>now+10000)
	{
// if we have had problems resyncing then quit, and if host start another resync - still need
// to process all messages in Q. If sync packets arrive late it should not matter as they will
// still be the same info.

		if (Host)
		{
#ifdef SYNCDATA 
			fprintf(fp,"timeout\n");
			fflush(fp);
#endif
			resyncsgot=0;
			Initiator=TRUE;
			BeginSyncPhase();
		}
	}
#ifdef SYNCDATA 
		fclose(fp);
#endif

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitH2HPArray
//Date			Wed 10 Dec 1997
//------------------------------------------------------------------------------
void	DPlay::InitH2HPArray()
{
	H2HPlayerInfo* p=H2H_Player;

	for (ULong n=0;n<MAXPLAYERS;n++)
	{
		p->dpid=0;
		p->name[0]=0;
		p->status=CPS_NONE;
		p->dialogue[0]=0;
		p->kills=0;
		p->assists=0;
		p->deaths=0;
		p->MyTeam=TS_UNASSIGNED;

// initially players are unassgined

		p->position=-1;

		if (GameType>TEAMPLAY)
			p->squadron=-1;
		else
			p->squadron=0;

		p++;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitSyncPhase
//Date			Mon 15 Dec 1997
//------------------------------------------------------------------------------
Bool	DPlay::InitSyncPhase()
{
	ACPACKET InitPacket;
	AGGSENDPACKET	packet;
	ULong	n,num,m;
	static ULong 	IgnoreFrameIncs=6;
	DWORD	BufferLen;
	char* Buffer;
	DPID	From=0;
	static first=true;

	if (ResetSync)
	{
		ResetSync=false;
		first=true;
		IgnoreFrameIncs=6;

		From=aggID;

		while (ReceiveNextMessageToMe(Buffer,BufferLen,From,DPRECEIVE_FROMPLAYER))
		{
		}
	}

	bool got=false;

	From=aggID;
	while (ReceiveNextMessageToMe(Buffer,BufferLen,From,DPRECEIVE_TOPLAYER))
	{
		if (From==DPID_SYSMSG)
			ProcessSystemMessage(Buffer);
		else if (From==aggID)
		{
// keep receiving agg packets till we get the last one
// no. check every one, otherwise we may (highly probably actually) end up
// junking packets that we want but are part of a burst or for some other reason

				ExpandAggPacket(&packet,(LPAGGSENDPACKET)Buffer);

				got=true;
				break;
		}
		else
		{
			if (!ProcessPlayerMessage(Buffer,BufferLen,From))
				break;
		}
	}

	if (!got)
		return FALSE;

 	InitPacket.Count=FrameCount;
 	InitPacket.X=myDPlayID;
	InitPacket.Ack1=0;
	InitPacket.Ack2=0;
 	InitPacket.IDCode=PIDC_DUMMYPACKET;
 	InitPacket.byte1=PIDC_DUMMYPACKET;
 	InitPacket.byte2=PIDC_DUMMYPACKET;
 	InitPacket.byte3=PIDC_DUMMYPACKET;
 	InitPacket.byte4=PIDC_DUMMYPACKET;
 	InitPacket.byte5=PIDC_DUMMYPACKET;
 	SendPacketToAggregator(&InitPacket);

#ifdef FILELOGS
	static int lasttime;
 	FILE* fp=fopen("sendpack.txt","at");
 	fprintf(fp,"%d %d %d %d %d %d\n",InitPacket.Count,InitPacket.X,InitPacket.IDCode,timeGetTime(),(timeGetTime()-lasttime)/10,myDPlayID);
 	fclose(fp);
	lasttime=timeGetTime();
#endif

// check to see if all players have sent a dummy packet. If we have received
// a packet then we can send another one, this synchronises with the aggregator
// for now...


#ifdef FILELOGS
	FILE* pp=fopen("aggpack.txt","at");
	fprintf(pp,"Agg frame%d My Frame%d\n",
		packet.Count,FrameCount);

	for (n=0;n<MAXPLAYERS;n++)
	{
		if (ActivePlayers&1<<n)
		{
			fprintf(fp,"%d %d %d %d\n",
				packet.player[n].Count,packet.player[n].X,packet.player[n].IDCode,packet.player[n].Y);
		}
	}
	fclose(pp);
#endif

#ifdef SYNCDATA
	FILE* sp=fopen("resync.txt","at");
	fprintf(sp,"\nGot Agg Packet\n");
#endif
	num=0;
	for (n=0;n<MAXPLAYERS;n++)
	{
		if (packet.player[n].IDCode==PIDC_DUMMYPACKET)	
		{
			num++;
#ifdef SYNCDATA
			fprintf(sp,"received DUMMYPACKET from %d\n",n);
#endif
		}
#ifdef SYNCDATA 
		else
		{
			fprintf(sp,"received %d from %d\n",packet.player[n].IDCode,n);
		}
#endif
	}
#ifdef SYNCDATA
	fprintf(sp,"got %d CP %d\n",num,CurrPlayers);
	fclose(sp);
#endif

	{
		if (num!=CurrPlayers)
		{
// determine if I am in aggregated packet and if not, work out
// new framecount to get me in

			for (n=0;n<MAXPLAYERS;n++)
			{
				if (H2H_Player[n].dpid==myDPlayID)
					break;
			}

			if (packet.player[n].IDCode!=PIDC_DUMMYPACKET)
			{
				if (packet.Count<=FrameCount)
				{
// if we have got too far ahead
// I mean behind!!!! If packet received has a higher frame number than current frame 
// we have no chance of getting in!!

					if ((abs)(FrameCount-packet.Count)>10)
					{
						FrameCount=packet.Count;
						IgnoreFrameIncs=6; 
					}
					else
					{
						if (IgnoreFrameIncs==0)
						{
							FrameCount++;
							IgnoreFrameIncs=6; 
						}
						else
						{
							IgnoreFrameIncs--;
						}
					}
				}
				else
				{
// initial big catchup
					if (first)									
					{											
						first=false;							
						FrameCount=packet.Count+1;				
					}											
					else										
					if (IgnoreFrameIncs==0)
					{
						FrameCount=packet.Count;
						IgnoreFrameIncs=6;
					}
					else
					{
						IgnoreFrameIncs--;
					}
				}
			}
			FrameCount++;
		}
		else
		{
#ifdef FILELOGS
 	FILE* fp=fopen("sendpack.txt","at");
 	fprintf(fp,"INITSYNCPHASE SUCCESSFUL\n");
 	fclose(fp);
#endif
			IgnoreFrameIncs=6; 
			FrameCount++;
			synched=TRUE;

			return TRUE;
		}
	}

	return FALSE;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SecondSyncPhase
//Date			Mon 15 Dec 1997
//------------------------------------------------------------------------------
Bool	DPlay::SecondSyncPhase()
{
// start transmitting null packets until all players dummy packets have
// been through

	ACPACKET InitPacket;
	AGGSENDPACKET	packet;
	ULong n,num;
	DWORD	BufferLen;
	char* Buffer;
	DPID	From=0;

	bool got=false;

	From=aggID;
	while (ReceiveNextMessageToMe(Buffer,BufferLen,From,DPRECEIVE_TOPLAYER))
	{
		if (From==DPID_SYSMSG)
			ProcessSystemMessage(Buffer);
		else if (From==aggID)
		{
// keep receiving agg packets till we get the last one
// NO NO NO NO NO -  if we get PIDC_INITPACK message dont want to receive a data packet
// after which would mean we never sync! i.e. the initpack message would be junked

			ExpandAggPacket(&packet,(LPAGGSENDPACKET)Buffer);

			got=true;
			break;
		}
		else
		{
			if (!ProcessPlayerMessage(Buffer,BufferLen,From))
				break;
		}
	}

	if (!got)
		return FALSE;

	InitPacket.Count=FrameCount;
	InitPacket.IDCode=PIDC_INITPACK;
	InitPacket.byte1=PIDC_INITPACK;
	InitPacket.byte2=PIDC_INITPACK;
	InitPacket.byte3=PIDC_INITPACK;
	InitPacket.byte4=PIDC_INITPACK;
	InitPacket.byte5=PIDC_INITPACK;
	InitPacket.Ack1=0;
	InitPacket.Ack2=0;
	InitPacket.X=0;
	InitPacket.Y=0;
	InitPacket.Z=0;
	InitPacket.Shift=0;
	InitPacket.Bull=0;
	InitPacket.Velocity_=0;
	InitPacket.Heading=0;
	InitPacket.Pitch=0;
	InitPacket.Roll=0;

	SendPacketToAggregator(&InitPacket);

#ifdef FILELOGS
	static int lasttime;
	FILE* fp=fopen("sendpack.txt","at");
	fprintf(fp,"%d %d %d %d %d\n",	InitPacket.Count,InitPacket.X,InitPacket.IDCode,timeGetTime(),(timeGetTime()-lasttime)/10);
	fclose(fp);
	lasttime=timeGetTime();
#endif

#ifdef FILELOGS
	FILE* dp=fopen("aggpack.txt","at");
	fprintf(dp,"Agg frame%d My Frame%d\n",
		packet.Count,FrameCount);
		
	for (n=0;n<MAXPLAYERS;n++)
	{
		if (ActivePlayers&1<<n)
		{
			fprintf(dp,"%d %d %d %d\n",
				packet.player[n].Count,packet.player[n].X,packet.player[n].IDCode,packet.player[n].Y);
		}
	}
	fclose(dp);
#endif

#ifdef SYNCDATA
	FILE* sp=fopen("resync.txt","at");
	fprintf(sp,"\nGot Agg Packet\n");
#endif
	num=0;
	for (n=0;n<MAXPLAYERS;n++)
	{
		if (packet.player[n].IDCode==PIDC_INITPACK)		
		{
			num++;
#ifdef SYNCDATA
			fprintf(sp,"received INITPACK from %d\n",n);
#endif
		}
#ifdef SYNCDATA 
		else
		{
			fprintf(sp,"received %d from %d\n",packet.player[n].IDCode,n);
		}
#endif
	}
#ifdef SYNCDATA
	fprintf(sp,"got %d CP %d\n",num,CurrPlayers);
	fclose(sp);
#endif
	if (num==CurrPlayers)
 	{
// everybody is ready, start gameplay

		FrameCount++;

		PacketBuffer.GetCurr()->Count=packet.Count+1;	

		for (n=0;n<MAXPLAYERS;n++)
		{
			PacketBuffer.GetCurr()->PlayerData[n].Count=packet.Count;
			HistPosBuffer[n].SetTempNext();
			HistPosBuffer[n].TempPrev();
			HistPosBuffer[n].GetTemp()->Frame=packet.Count;
		}

#ifdef TIMERTIME
		timertime=timeGetTime();
		LARGE_INTEGER count;
		QueryPerformanceCounter(&count);
		Qtimertime=count.LowPart;;
		Qlasttimertime=0;
		lasttimertime=0;
		timer=fopen("timertim.txt","at");
		fprintf(timer,"BEGIN\n");

		BOOL res=QueryPerformanceFrequency((LARGE_INTEGER*)(&Qfreq));

		fprintf(timer,"FREQ: %d\n",Qfreq);
#endif
		csync=true;
		resyncbar=false;
		return TRUE;
	}
	FrameCount++;

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitGameVars
//Date			Mon 15 Dec 1997
//------------------------------------------------------------------------------
void	DPlay::InitGameVars()
{
	velcounter=0;

	JustJoined=FALSE;
	ResyncPhase=FALSE;
	Initiator=FALSE;
	WorldSyncPhase=FALSE;

	FrameInc=0;

	Math_Lib.ResetRndCount();

	FrameCount = 0;

	GR_Quit3DNow = 0;

	firsttimein=FALSE;

// start of game or on a resync delete, world will have been transmitted

	DeleteAIACPositionsList();

	clearbuffertime=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeAndSendPacket
//Date			Thu 18 Dec 1997
//------------------------------------------------------------------------------
void	DPlay::MakeAndSendPacket()
{
// if lots of AI AC require their position transmitting then it could be a while before
// a player delta is sent, resulting in warping. Use this flag to indicate that after every
// all packets for a single AI AC have been sent, send a player packet

	static bool GuaranteedDeltaSend=true; 
	ACPACKET	SendPacket;

	ZeroMemory (&SendPacket,sizeof(ACPACKET));

	SendPacket.Count=FrameCount++;

	if (MyAIACPositionsToSend && !GuaranteedDeltaSend)
	{
		switch (MyAIACPositionsToSend->extrainfo)
		{
		case 0:
			Make1stAIACPositionPacket(&SendPacket);
			break;
		case 1:
			Make2ndAIACPositionPacket(&SendPacket);
			GuaranteedDeltaSend=true;
			break;
		default :
			_Error.SayAndQuit("Invalid value for AI AC");
			break;
		}
	}
	else
	{
		GuaranteedDeltaSend=false;

		MakeDeltaPacket ( &SendPacket);

		MakeExtraPacket(&SendPacket,FALSE);

// update deltas with sent values

		UpdateDeltas(&SendPacket);				
	}
// send acks

	SendPacket.Ack1=0;
	SendPacket.Ack2=0;

	if (RecPackBuffer.NumEntries()>0)
	{
 		SendPacket.Ack1=RecPackBuffer.GetCurr()->packet;

		RecPackBuffer.UpdateCurr();

		if (RecPackBuffer.NumEntries()>0)
		{
// problem when a large buffer send 2 resend packets at once and the Acks for these get
// put into the same packet, which then gets lost itself, no more chances. So spread 
// Acks for the same packet over 2 packets to try and get info through

 			if (RecPackBuffer.GetCurr()->packet!=SendPacket.Ack1)
 			{
 				SendPacket.Ack2=RecPackBuffer.GetCurr()->packet;
 
 				RecPackBuffer.UpdateCurr();
 			}
		}
	}

// send packet off to aggregator

	SendPacketToAggregator (&SendPacket);

#ifdef FILELOGS
	FILE* fp=fopen("sendpack.txt","at");
	fprintf(fp,"Sending %d: Ack1=%d Ack2=%d\n",SendPacket.Count,SendPacket.Ack1,SendPacket.Ack2);
	fclose(fp);
#endif

// copy sent packet into buffer

	SendPackBuffer.GetNext()->Done=FALSE;
	SendPackBuffer.AddEntry();

// if send buffer is full then need to initiate a resynch

	if (SendPackBuffer.NumEntries()>BufferSize && !WorldSyncPhase)
	{
		Initiator=TRUE;
		BeginSyncPhase();
	}

	CopyMemory((char*)&SendPackBuffer.GetNext()->packet,(char*)&SendPacket,sizeof(ACPACKET));

	SendPackBuffer.UpdateNext();

	if (!WorldSyncPhase)
		CheckForResend();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessInfoPackets
//Date			Tue 31 Mar 1998
//Description	Get any non aggregated packets and process them 
//------------------------------------------------------------------------------
void	DPlay::ProcessInfoPackets()
{
	DWORD	BufferLen;
	char* Buffer;
	DPID	From=0;

	while (ReceiveNextMessageToMe(Buffer,BufferLen,From,DPRECEIVE_TOPLAYER))
	{
		if (From==DPID_SYSMSG)
			ProcessSystemMessage(Buffer);
		else if (From==aggID)
		{
			ProcessAggregatedPacket(Buffer);

			if (ResyncPhase)
				return;
		}
		else
		{
// need to break out if resync message or something else has arrived

			if (!ProcessPlayerMessage(Buffer,BufferLen,From))
				break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUpPlayersAC
//Date			Wed 15 Apr 1998
//------------------------------------------------------------------------------
void	DPlay::SetUpPlayersAC()
{
	ULong n;
	UniqueID thisid=UID_Null;

	for (n=0;n<MAXPLAYERS;n++)
	{
		if (H2H_Player[n].status!=CPS_3D)
		{
			thisid = (UniqueID)AllocPacket [n];

			if (thisid!=UID_Null)
			{
				AirStrucPtr thisac=NULL;
				thisac = (AirStrucPtr)Persons2::ConvertPtrUID (thisid);

				if (thisac)
				{
					MinAnimData* mad = (MinAnimData* )thisac->Anim;
					mad->itemstate = DEAD;

					mad->IsInvisible=1;
					thisac->Status.deaded=TRUE;

					thisac->Status.deadtime=1;
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		JoinGame
//Date			Wed 15 Apr 1998
//------------------------------------------------------------------------------
Bool	DPlay::JoinGame()
{
	GENERIC packet;
	Bool	got=FALSE;
	ULong from,t,count,n;
	ULong RecPacketLen = 0;
	char* RecPacket;

	if (!PlayerCreated)
		return FALSE;

	CountPlayers(true);

	ResetAllocPacket();

	if ((H2H_Player[mySlot].position==-1 || H2H_Player[mySlot].squadron==-1) && GameType>TEAMPLAY)//DAW 22Jun99
	{
		CommsMessage(IDS_NOTSLOTS);
		return FALSE;
	}

	SimulateExitKey=FALSE;

// get messages

	packet.PacketID=PID_MESSAGESREQUEST;

	SendMessageToGroup((char*)&packet,sizeof(GENERIC));

	if (!UpdateMessages())
		return FALSE;

// get prefs

	packet.PacketID=PID_PREFSREQUEST;

	SendMessageToGroup((char*)&packet,sizeof(GENERIC));

	got=FALSE;

	ULong now=timeGetTime();

	CommsTimeout time(now,CommsTimeoutLength);

	while (!got)
	{
		now=timeGetTime();

		if (time.TimedOut(now))
			return FALSE;

		if (ReceiveNextMessageToMe (RecPacket, RecPacketLen,from,DPRECEIVE_TOPLAYER))
		{
			if (from==DPID_SYSMSG)
			{
				ProcessSystemMessage(RecPacket);
			}
			else if (from!=aggID)
			{
				PUIPLAYERDATA pUIPlayerData = (PUIPLAYERDATA)RecPacket;

				if (pUIPlayerData->PacketID == PID_PREFSDATA)
			   	{
					ProcessPrefsPacket(RecPacket);

					got=TRUE;
		   		}
				else
				{
					ProcessPlayerMessage(RecPacket,RecPacketLen,from);
				}
			}
		}
	}

	packet.PacketID=PID_PLAYERINFOREQUEST;

	SendMessageToGroup((char*)&packet,sizeof(GENERIC));

	count=0;

	time.Init(now,CommsTimeoutLength);

	for (;;)
	{
		if (count == (CurrPlayers - 1))
			break;

		now=1;

		if (time.TimedOut(now))
			return FALSE;

		if (ReceiveNextMessageToMe (RecPacket, RecPacketLen,from,DPRECEIVE_TOPLAYER))
		{
			if (from==DPID_SYSMSG)
			{
				ProcessSystemMessage(RecPacket);
			}
			else if (from!=aggID)
			{
				PUIPLAYERDATA pUIPlayerData = (PUIPLAYERDATA)RecPacket;

				if (pUIPlayerData->PacketID == PID_PLAYERUPDATE)
				{
					count++;

// Put data in H2HPlayer

					n=DPID2Slot(from);
					if (n!=MAXPLAYERS)
					{
						CopyMemory((char*)&H2H_Player[n],(char*)&pUIPlayerData->playerinfo,sizeof(H2HPlayerInfo));
					}
				}
				else
				{
					ProcessPlayerMessage(RecPacket,RecPacketLen,from);
				}
			}
		}
	}

	packet.PacketID=PID_MISSCONDSREQUEST;

	SendMessageToGroup((char*)&packet,sizeof(GENERIC));

	got=FALSE;

	while (!got)
	{
		now=1;

		if (time.TimedOut(now))
			return FALSE;

		if (ReceiveNextMessageToMe (RecPacket, RecPacketLen,from,DPRECEIVE_TOPLAYER))
		{
			if (from==DPID_SYSMSG)
			{
				ProcessSystemMessage(RecPacket);
			}
			else if (from!=aggID)
			{
				PUIPLAYERDATA pUIPlayerData = (PUIPLAYERDATA)RecPacket;

				if (pUIPlayerData->PacketID == PID_MISSIONCONDITIONS)
			   	{
					ProcessConditionsPacket(RecPacket);

					got=TRUE;
		   		}
				else
				{
					ProcessPlayerMessage(RecPacket,RecPacketLen,from);
				}
			}
		}
	}

	ULong	squads[PT_GER_NONFLY+1];	 

	if (GameType<COMMSQUICKMISSION)
	{
		FillCSQuickStruc();

// position 

		for (n=0;n<=PT_GER_NONFLY;n++)
		{
			squads[n]=0;
		}

		for (n=0;n<MAXPLAYERS;n++)
		{
			H2H_Player[n].position=squads[H2H_Player[n].squadron];
			squads[H2H_Player[n].squadron]++;
		}
	}

	if (!SendMyPlayerInfo(false))								
		return FALSE;											
					 
// no need to receive save game, the one initially should still be valid


	MMC.playersquadron=H2H_Player[mySlot].squadron;
	MMC.playeracnum=H2H_Player[mySlot].position;

	H2H_Player[mySlot].status=CPS_3D;

	GR_amberstrength = MAXPLAYERS;

	Joining=TRUE;

	InitialFlagReset();

	return TRUE;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddPlayerToGame
//Date			Wed 15 Apr 1998
//------------------------------------------------------------------------------
void	DPlay::AddPlayerToGame(ULong slot,ULong actype,ULong id)
{
	AirStrucPtr thisac=(AirStrucPtr)Persons2::ConvertPtrUID((UniqueID)id);

	if (!thisac)
		return;

	AllocPacket[slot]=id;
	CurrPlayers++;

	if (GameType<COMMSQUICKMISSION)
	{
// deathmatch/team game

// if actype of new player is different to type already set up then need to get new
// shape/anims - uniqueIDs will be out of sync as well!
// ids will be in sync for deathmatch/teamplay even if different ac types
// are created because they are all created from same id band

// OR set commsmove flag if lots of ac created

		ULong type=(H2H_Player[slot].squadron);

		thisac->classtype=Plane_Type_Translate[type][0];

		MinAnimData* mad = (MinAnimData* )thisac->Anim;
		mad->IsInvisible=0;

		thisac->Status.deaded=FALSE;
		thisac->Status.deadtime=0;

		SHAPE.ResetAnimData_NewShape(thisac,thisac->_GetDrawShape(),thisac->weap.Weapons);	//RJS 12Oct00

		thisac->fly.pModel->Initialise(thisac,FALSE);
	}
	else
	{
// campaign/quickmission

		PlayerSync=true;
		SwitchAIACToPlayerAC(thisac,slot);
	}

// Set Active Player Bit field

	ActivePlayers|=(1<<slot);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendEnteringGameMesssage
//Date			Tue 21 Apr 1998
//------------------------------------------------------------------------------
void	DPlay::SendEnteringGameMessage()
{
// send a PID_IAMIN message to other players

	GENERIC data;

// want to send my uniqueID so other players can set up my AC

	data.Slot=Persons2::PlayerSeenAC->uniqueID.count;

	data.PacketID=PID_IAMIN;

	data.PlayerID=H2H_Player[mySlot].squadron;

	SendMessageToGroup((char*)&data,sizeof(GENERIC));

	PlayerSync=true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitBuffers
//Date			Tue 28 Apr 1998
//------------------------------------------------------------------------------
void	DPlay::InitBuffers()
{
	ULong n,m;

	PacketBuffer.InitBuffer();
	PacketBuffer.SetTempCurr();
	do
	{
		for (n=0;n<MAXPLAYERS;n++)
		{
		 	PacketBuffer.GetTemp()->Received[n]=FALSE;
			PacketBuffer.GetTemp()->PlayerData[n].IDCode=PIDC_PACKETERROR;
		}

		PacketBuffer.UpdateTemp();
	}
	while (PacketBuffer.GetTemp()!=PacketBuffer.GetCurr());

	SendPackBuffer.InitBuffer();
	SendPackBuffer.SetTempCurr();
	do
	{
		SendPackBuffer.GetTemp()->ResendStatus=0;
		SendPackBuffer.GetTemp()->Done=FALSE;
		SendPackBuffer.UpdateTemp();
	}
	while (SendPackBuffer.GetTemp()!=SendPackBuffer.GetCurr());

	RecPackBuffer.InitBuffer();
	CollBuffer.InitBuffer();
	SpecBuffer.InitBuffer();
	BulletBuffer.InitBuffer();
	UIDSBuffer.InitBuffer();

// fill historical buffer with inital position

	AirStrucPtr ac;

	for (n=0;n<MAXPLAYERS;n++)
	{
		if (AllocPacket[n])
		{
			ac=(AirStrucPtr)Persons2::ConvertPtrUID((UniqueID)AllocPacket[n]);

			if (ac)
			{
				HistPosBuffer[n].InitBuffer();
				HistPosBuffer[n].SetTempCurr();
				do 
				{
					HistPosBuffer[n].GetTemp()->Pos.X=ac->World.X;
					HistPosBuffer[n].GetTemp()->Pos.Y=ac->World.Y;
					HistPosBuffer[n].GetTemp()->Pos.Z=ac->World.Z;

					HistPosBuffer[n].GetTemp()->Heading=ac->hdg;
					HistPosBuffer[n].GetTemp()->Pitch=ac->pitch;
					HistPosBuffer[n].GetTemp()->Roll=ac->roll;
					HistPosBuffer[n].GetTemp()->Velocity=ac->vel_;

					HistPosBuffer[n].GetTemp()->OK=false;

					HistPosBuffer[n].UpdateTemp();
				} 
				while (HistPosBuffer[n].GetTemp()!=HistPosBuffer[n].GetCurr());
			}

			m=BufferSize-1;

			while (m--)
				HistPosBuffer[n].UpdateNext();
		}
	}

	for (n=0;n<MAXPLAYERS;n++)
	{
		for (m=0;m<3;m++)
		{
			ZeroMemory(&DeltasToApply[n][m],sizeof(DELTARECORD));
		}
	}
	DeltaIndex=0;

	PlayerAggCheck.InitBuffer();
	PlayerAggCheck.SetTempCurr();
	do
	{
		PlayerAggCheck.GetTemp()->Frame=-1;
		for (n=0;n<MAXPLAYERS;n++)
		{
			PlayerAggCheck.GetTemp()->used[n]=0;
		 	PlayerAggCheck.GetTemp()->acked[n]=false;
			PlayerAggCheck.GetTemp()->whichframe[n]=-1;
		}

		PlayerAggCheck.UpdateTemp();
	}
	while (PlayerAggCheck.GetTemp()!=PlayerAggCheck.GetCurr());

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetDeltas
//Date			Fri 1 May 1998
// Used to reset deltas when game needs resetting or in replay block headers
//------------------------------------------------------------------------------
void	DPlay::ResetDeltas()
{
	Deltas.lastpos.X=0;
	Deltas.lastpos.Y=0;
	Deltas.lastpos.Z=0;
	Deltas.Roll=ANGLES_0Deg;
	Deltas.Pitch=ANGLES_0Deg;
	Deltas.Heading=ANGLES_0Deg;
	Deltas.Velocity=0;
	Deltas.SpecCode=PIDC_EMPTY;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessCollisionPacket
//Date			Tue 5 May 1998
//------------------------------------------------------------------------------
UByte	DPlay::ProcessCollisionPacket(UByteP ptr, AirStrucPtr sender, ULong slot)
{
	UWord uid,shooteruid;
	UWord offset;													
	UByte type;
	UByte str;
	UWord temp;

	UByte IDCode,byte1,byte2,byte3,byte4,byte5;

	IDCode=*ptr++;
	byte1=*ptr++;
	byte2=*ptr++;
	byte3=*ptr++;
	byte4=*ptr++;
	byte5=*ptr;

// Offset = 9 bits
// Hit-type = 3 bits
// Hit-strength = 6 bits

 	str=IDCode&63;

	temp=byte1;
	temp+=(byte2&0x3f)<<8;
	uid=(UniqueID)(temp);

	type=(byte2&0xc0)>>5;
	type+=byte3&0x01;

	offset=(byte3>>1)&0x7f;
	offset+=((byte4>>6)&0x03)<<7;

	shooteruid=(byte4&0x3f)<<8;
	shooteruid+=byte5;

	ItemPtr src=NULL;
	ItemPtr shooter;

	shooter=*Persons2::ConvertPtrUID((UniqueID)shooteruid);

#ifdef COLLPACKINFO
	FILE* fp=fopen("collrcv.txt","at");
	fprintf(fp,"str=%d type=%d trg=%d offset=%d shooter=%d\n",
		str,
		type,
		uid,
		offset,
		shooteruid);
	fclose(fp);
#endif


	if (_DPlay.Implemented)
	{
		if (GameType<COMMSQUICKMISSION)
		{
			src=*sender;
		}
	}

	BoxCol::Col_Shooter=shooter;
	BoxCol::Col_Hitter=NULL;

	UByte trg,hit;

	trg=UID2Slot(uid);
	hit=UID2Slot(shooteruid);

// dont want to have possible assists on yourself!

	if (trg<MAXPLAYERS && hit<MAXPLAYERS && (trg!=hit))
		CommsKiller[trg]=hit;

// in comms game an ac may be killed on one machine and be hit but not killed on
// another. This may result in ac being killed then having damage applied,
// so need to stop any further damage packets if ac is dead. In replay this will not
// happen because packet order is known to be OK.
// have fix for replay just in case!

	item* deaditem=Persons2::ConvertPtrUID((UniqueID)uid);

	if (deaditem)
	{
		if (deaditem->Status.size==AIRSTRUCSIZE)
		{
			AirStrucPtr deadac=(AirStrucPtr)Persons2::ConvertPtrUID((UniqueID)uid);

			if (deadac->shape!=PDEATH && deadac->movecode!=AUTO_RESURRECT)
			{
		  		SHAPE.AddToCollisionList(uid,offset,type,str);
			}
		}
		else 												
		{													
			SHAPE.AddToCollisionList(uid,offset,type,str);
		}												
	}

	if (_DPlay.Implemented && Persons2::PlayerSeenAC->Status.deaded)
	{
// if I have been killed

		if (!SuicideTime)
		{
			SuicideTime=timeGetTime()+5000; // 5 secs from now
		}
	}

	return (PacketLength(PIDC_COLLISION));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessSpecialPacket
//Date			Mon 20 Jul 1998
//Description	Owner determines whether I should process an effect or not.
//				e.g. to want to process my near misses but not my SFX
//------------------------------------------------------------------------------
UByte	DPlay::ProcessSpecialPacket(UByteP ptr, AirStrucPtr AC, ULong slot)
{
	ULong ID=*ptr;

// for these packets no extra info is stored in the IDCode, so the address
// of the 1st extra byte can be passed into the functions

	ptr++;

	switch (ID)
	{
	case PIDC_PACKETERROR:
	case PIDC_DUMMYPACKET:
	case PIDC_INITPACK:
	case PIDC_EMPTY:
		break;

	case PIDC_NEARMISS:
		ProcessNearMiss(ptr);
		break;

	case PIDC_RESURRECT:
		ProcessResurrectPacket(AC);
		break;

	case PIDC_RESURRECTEND:
		ProcessResurrectEndPacket(AC);
		break;

	case PIDC_LANDEDEFFECT:
		ProcessLandedEffectPacket(ptr,AC);
		break;

	case PIDC_AERODEVICE:
		ProcessAeroDevicePacket(ptr,AC);
		break;

	case PIDC_DEATHMOVEEFFECT:
		ProcessDeathMoveEffectPacket(ptr);
		break;				  

	case PIDC_OWNERCHANGE:
		ProcessOwnerChangePacket(ptr);
		break;

	case PIDC_KILLLAUNCHER:
		ProcessKillLauncherPacket(ptr);
		break;

	case PIDC_PLAYERMESSAGE:
		ProcessPlayerMessagePacket(ptr,slot);
		break;

	case PIDC_EJECT:
		ProcessEjectPacket(AC);
		break;

	case PIDC_SHAPECHANGE:
		ProcessNewShapePacket(ptr);
		break;
		
	case PIDC_ACCELGEARUP:
		ProcessAccelGearUpPacket();
		break;

	case PIDC_NEWWP:											
		ProcessNewWPPacket(ptr,AC);							
		break;

	case PIDC_SECONDARYAERODEVICES:
		if (!_DPlay.LosePackets)
			ProcessControlSurfacePacket(ptr);
		break;

	case PIDC_ENGINERPM:
		ProcessEngineRPMPacket(ptr);
		break;

	case PIDC_ENGINEANIM:
		ProcessEngineAnimPacket(ptr,slot);
		break;

#ifndef NDEBUG
	 default:
		_Error.SayAndQuit("Packet ID not used yet %d",ID);
#endif
	}

	return (PacketLength(ID));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetVal
//Date			Mon 11 May 1998
//------------------------------------------------------------------------------
SLong	DPlay::GetVal(UByte src,UByte shift)
{
	SLong retval;

	if (src>127)
		retval=-((src-128)<<shift);
	else
		retval=src<<shift;

	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetRandomListPos
//Date			Tue 19 May 1998
//------------------------------------------------------------------------------
#define MAXRNDINCS 64
void	DPlay::SetRandomListPos()
{
	static x=0;
	UWord rndincs;

//Fixed RND() so it doesn't exceed this limit
	rndincs = Math_Lib.GetRndCount ();							
	if (rndincs > MAXRNDINCS)									
		rndincs = 0;											
	else														
		rndincs = MAXRNDINCS - rndincs;							

	for (;rndincs > 0; rndincs--)
		Math_Lib.rnd();

	Math_Lib.ResetRndCount();

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PossTransmitColl
//Date			Fri 3 Jul 1998
//------------------------------------------------------------------------------
Bool	DPlay::PossTransmitColl(ItemPtr target, ItemPtr hitter,SLong &send)
{
	send = 0;												

	if (_DPlay.CommsOrReplay() || _Replay.Playback)
	{
// bullets only at the moment
						
 		if (hitter && hitter->Status.size==TransientSize)
		{
			TransientItemPtr t=(TransientItemPtr)(hitter);

			if (t->CollTestEnabled)
			{
// only check if active bullet

				if (_Replay.Playback)
				{
// never send packets in playback

// if I am involved in collision then return TRUE so that collision is not processed, 
//but because send is 0 nothing will be done and packet will arrive to deal with me,
// otherwise, do collision as normal

					if (target==Persons2::PlayerSeenAC || t->Launcher==Persons2::PlayerSeenAC)
					{
						return TRUE;
					}
					else
					{
						return FALSE;
					}
				}
				else if (_Replay.Record)
				{
// send packet if bullet is against me or I launched it

					if ((AirStrucPtr)(t->Launcher)==Persons2::PlayerSeenAC
					|| 	(AirStrucPtr)target==Persons2::PlayerSeenAC)
					{
						send=1;
						return TRUE;
					}
					else
					{
						return FALSE;
					}
				}
				else
				{
// comms game
// send packet if bullet is against me or I launched it
// unless bullet against me was launched by an AI AC with a comms owner 
// other than me, in which case that player will send packet

					if ((AirStrucPtr)(t->Launcher)==Persons2::PlayerSeenAC
					|| 	(AirStrucPtr)target==Persons2::PlayerSeenAC)
					{
						if (!t->Launcher->uniqueID.commsmove
						&&	((AirStrucPtr)(t->Launcher))->CommsOwner!=Persons2::PlayerSeenAC->uniqueID.count)
						{
// bullet against me launched by an AI AC controlled by other player. Dont want
// to do collision or send packet, add to log but set send to 0.

							send=0;
							return TRUE;
						}
						send=1;
						return TRUE;
					}
					else
					{
						return FALSE;
					}
				}
			}
			else
			{
// if not active bullet then dont want to send packet, should not have had
// a collision anyway so should never get here

#ifndef NDEBUG
				INT3;
#endif
				return FALSE;
			}
		}
		else
		{
// collision with something else

			// log this collision too...						
			if ((AirStrucPtr)target==Persons2::PlayerSeenAC		
				|| (AirStrucPtr)hitter==Persons2::PlayerSeenAC)	
			{													
				if (!_Replay.Playback)							
				{												
					send = 2;									
				}												
				return TRUE;									
			}													
		}														
	}

	return FALSE;												
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewCollision2
//Date			Sun 5 Jul 1998
//
//Description	Store new collision in collision table to be transmitted
//				as soon as possible
//------------------------------------------------------------------------------
void	DPlay::NewCollision2 (UWord id, UWord offset, UByte type, UByte str, UniqueID hitterscorer)
{
	if (id)
	{
		if (CommsOrReplay())
		{
// instead of causing an error if table is full, overwrite oldest entry ?????

			if(CollBuffer.NumEntries()>=BufferSize)
			{	
				CollBuffer.UpdateCurr();

				while (CollBuffer.GetCurr()->IDCode==PIDC_DONTSEND && CollBuffer.GetCurr()!=CollBuffer.GetNext())
					CollBuffer.UpdateCurr();
			}

#ifndef NDEBUG
			if (type>7)
				INT3;

			if (str>63)
				INT3;
#endif
			CollBuffer.GetNext()->IDCode=PIDC_COLLISION;
			CollBuffer.GetNext()->id=id;
			CollBuffer.GetNext()->offset=offset;
			CollBuffer.GetNext()->type=type;
			CollBuffer.GetNext()->str=str;
			CollBuffer.GetNext()->hitterscorer=hitterscorer;

			CollBuffer.AddEntryAndUpdateNext();
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewNearMiss
//Date			Thu 23 Jul 1998
//Description	add nearmiss entry to special buffer
//------------------------------------------------------------------------------
void	DPlay::NewNearMiss(AirStrucPtr trg, AirStrucPtr hitter)
{
	UByte b1=0,b2=0;

// store uniqueID of whichever ac is not player in byte1 and byte2
// byte3 stores whether that ac is trg or hitter

	ULong	ID=trg->uniqueID.count;

// only store near misses caused by player against AI AC

	b1=ID&0xff;
	b2=ID>>8;

	NewSpecial(PIDC_NEARMISS,b1,b2);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessNearMiss
//Date			Thu 23 Jul 1998
//------------------------------------------------------------------------------
void	DPlay::ProcessNearMiss(UByteP ptr)
{
	UByte byte1,byte2;

	byte1=*ptr++;
	byte2=*ptr;

// get uid of ac and whether it is the trg or hitter

	ULong ID;
	AirStrucPtr ac;

	ID=byte2<<8;
	ID+=byte1;

	ac=(AirStrucPtr)Persons2::ConvertPtrUID((UniqueID)ID);

// now know that all near misses thru hear are caused by player on AI ac
	if (ac)
	{
		Art_Int.PersonalThreat(ac,Persons2::PlayerGhostAC);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeExtraPacket
//Date			Thu 23 Jul 1998
//------------------------------------------------------------------------------
void	DPlay::MakeExtraPacket(LPBASICPACKET packet,Bool replay)
{
// New packet. Fit in as much additional data as possible into the extra 5 bytes
// Priority is: collision, UIDS (wingman command), special, bullet
// Once first lot of data is put into packet, see how many bytes are left and see if 
// more can be added.

	bool more=true;
	UByte bytesleft=EXTRASIZE;
	UByte index=0;
	bool	madebullet=false;
	UByte length=0;

	while (more)
	{
		if (bytesleft>=PacketLength(PIDC_KILLLAUNCHER) && IsThereKillLauncher())
		{
			length=MakeKillLauncherPacket(packet,index);
		}
		else
		if (bytesleft>=PacketLength(PIDC_COLLISION) &&  CollBuffer.NumEntries())
		{
// we have space for a collision packet

			length=MakeCollPacket(packet,index);
		}
		else if (bytesleft>=PacketLength(PIDC_UIDPACKET) && UIDSBuffer.NumEntries())
		{
// space for UIDS packet

			length=MakeUIDSPacket(packet,index);
		}
		else if (bytesleft>=PacketLength(SpecBuffer.GetCurr()->IDCode) && SpecBuffer.NumEntries())
		{
// space for other packet

			length=MakeSpecialPacket(packet,index);
		}
		else if (bytesleft && BulletBuffer.NumEntries())
		{
// only thing left is bullet packet

			length=MakeBulletPacket(packet,index);
			madebullet=true;
		}
		else 
		{
// nothing else will fit in

			if (bytesleft)
			{
				MakeEmptyPacket(packet,index);
			}
			
			more=false;
		}

		bytesleft-=length;
		index+=length;
	}

// if there was no data to send then use packet to send control surface values

	if (bytesleft==EXTRASIZE)
	{
		MakeControlSurfacePacket(packet);
	}

// if we have not sent a bullet packet and there are some avilable then 
// squeeze into 4 spare bits in shiftfactor...

	if (BulletBuffer.NumEntries() && !madebullet)
	{
  		MakeSpecialBulletPacket(packet);
	}

	if (replay)
	{
		ProcessExtraPacket((LPACPACKET)packet,Persons2::PlayerSeenAC,0);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewSpecial
//Date			Fri 24 Jul 1998
//------------------------------------------------------------------------------
void	DPlay::NewSpecial(ULong id,UByte byte1, UByte byte2, UByte byte3, UByte byte4, UByte byte5)
{
	if (CommsOrReplay())
	{
// instead of causing an error if table is full, overwrite oldest entry ?????

		if(SpecBuffer.NumEntries()>=BufferSize)			
		{
			SpecBuffer.UpdateCurr();

			while (SpecBuffer.GetCurr()->IDCode==PIDC_DONTSEND && SpecBuffer.GetCurr()!=SpecBuffer.GetNext())
				SpecBuffer.UpdateCurr();
		}
		 
		SpecBuffer.GetNext()->IDCode=id;
		SpecBuffer.GetNext()->spec1=byte1;
		SpecBuffer.GetNext()->spec2=byte2;
		SpecBuffer.GetNext()->spec3=byte3;
		SpecBuffer.GetNext()->spec4=byte4;
		SpecBuffer.GetNext()->spec5=byte5;

		SpecBuffer.AddEntryAndUpdateNext();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeBulletPacket
//Date			Fri 24 Jul 1998
//------------------------------------------------------------------------------
UByte	DPlay::MakeBulletPacket(LPBASICPACKET packet, UByte index)
{
// bullet packet is IDCode (bits 6,7) + number (bits 4,5) + launcher (bits 0,1,2,3)
// = total of 1 byte

	UByteP ptr=&packet->IDCode;

	ptr+=index;
	*ptr=PT_BULLET<<6;

#ifndef NDEBUG
	if (BulletBuffer.GetCurr()->num>3)
		INT3;
#endif

	*ptr+=((BulletBuffer.GetCurr()->num)&3)<<4;

#ifdef NDEBUG 
	if (BulletBuffer.GetCurr()->index>15)
		INT3;
#endif

	*ptr+=(BulletBuffer.GetCurr()->index)&0xf;

	BulletBuffer.UpdateCurr();

	return (PacketLength(PIDC_BULLET));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessBulletPacket
//Date			Fri 24 Jul 1998
//------------------------------------------------------------------------------
UByte	DPlay::ProcessBulletPacket(UByteP ptr, AirStrucPtr AC)
{
	UByte IDCode;

	if (!((CommsOrReplay()) && AC==Persons2::PlayerSeenAC))
	{
		IDCode=*ptr;

		ULong num,index;
		WeapAnimData* weap;
		ItemPtr item;
		UWord	shape,MuzDel;
		ULong	MuzVel;
		SLong	xpos,ypos,zpos;
		UByte	ltype;
		TransientItem* item2;
		WorldStuff &world = mobileitem::GetWorld();

		num=(IDCode>>4)&0x03;
		index=IDCode&0x0f;;

		item=(ItemPtr)AC; 

		weap=SHAPE.DirectWeaponLauncher(item,index,shape,xpos,ypos,zpos,MuzVel,MuzDel,ltype);
		if (weap)
		{
			if (num > 1)
				item2 = Trans_Obj.LaunchManyGunBullets((mobileitem*)item,MuzVel,num,MuzDel,index,index,(ShapeNum)shape,xpos,ypos,zpos,world,0,ltype);//RJS 26Mar99
			else
			{
				int	oldStores = weap->LoadedStores;

				Trans_Obj.ClearWeaponChain((mobileitem*)item);
				Trans_Obj.LaunchWeapon(true,(AirStrucPtr)item,weap,index,xpos,ypos,zpos,world,MuzVel,MuzDel);

				if (oldStores && !weap->LoadedStores)					
					weap->LoadedStores = weap->Stores;					
			}
		}
	}

	return (PacketLength(PIDC_BULLET));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessAggregatedPacket
//Date			Fri 7 Aug 1998
//------------------------------------------------------------------------------
void	DPlay::ProcessAggregatedPacket(char* packet)
{
// only process aggregated packets if we have synched

	if (csync)
 		StorePacket((LPAGGSENDPACKET)packet);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRealACPosition
//Date			Tue 1 Sep 1998
//------------------------------------------------------------------------------
COORDS3D* DPlay::GetGoodACPosition(ItemBasePtr ac)
{
	ULong n;

	if (ac)
	{
		if (!_DPlay.Implemented)
			return & ac->World;

		if (ac->uniqueID.commsmove)
		{
			for (n=0;n<MAXPLAYERS;n++)
			{
				if (AllocPacket[n]==ac->uniqueID.count)
				{
					return &HistPosBuffer[n].GetCurr()->Pos;
				}
			}
		}
		else
		{
			if (ac==Persons2::PlayerSeenAC)
				return &Persons2::PlayerGhostAC->World;
			else
				return & ac->World;
		}
	}

	return NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetScore
//Date			Tue 1 Sep 1998
//------------------------------------------------------------------------------
void	DPlay::SetScore(AirStrucPtr victim, ItemPtr hitter)
{
	ULong n,m;

	ULong shooterteam,myteam,victimteam;
	Nationality myn=Persons2::PlayerSeenAC->nationality;

	AirStrucPtr shooter=NULL;
	
   	if (hitter)
	{
		shooter=(AirStrucPtr)hitter;
	}

	if (victim==shooter)
		shooter=NULL;

	if (victim)
	{
		UpdateDeadPilots(victim);

		bool commsplayerdead=false;
		for (n=0;n<MAXPLAYERS;n++)
		{
			if (AllocPacket[n]==victim->uniqueID.count)
			{
				commsplayerdead=true;
				ClearDeadPlayersPackets(n);
				break;
			}
		}

		if (commsplayerdead && deadplayers&1<<n)
			return;

		deadplayers|=1<<n;

		if (commsplayerdead)
			(H2H_Player+n)->deaths++;

		if (GameType!=DEATHMATCH)
		{
			if (victim->nationality==myn)
				MyTeamDeaths++;
			else
				EnemyTeamDeaths++;
		}

		if (shooter)
		{
			bool commsplayershooter=false;

			for (n=0;n<MAXPLAYERS;n++)
			{
				if (AllocPacket[n]==shooter->uniqueID.count)
				{
					commsplayershooter=true;
					break;
				}
			}


			if (shooter->nationality!=victim->nationality || GameType==DEATHMATCH)
			{
				if (commsplayershooter)
					(H2H_Player+n)->kills++;

				if (GameType!=DEATHMATCH)
				{
					if (shooter->nationality==myn)
						MyTeamKills++;
					else
						EnemyTeamKills++;
				}
			}

			if (commsplayershooter && commsplayerdead)
			{
				DisplayPlayerMessage((ItemPtr)victim,hitter,ST_PLAYERKILLEDPLAYER);
			}
			else if (commsplayerdead)
			{
				DisplayPlayerMessage((ItemPtr)victim,hitter,ST_PLAYERKILLEDCOMMS);
			}
			else if (commsplayershooter)
			{
				if (shooter->nationality==victim->nationality)
				{
					DisplayPlayerMessage((ItemPtr)victim,hitter,ST_PLAYERKILLEDFRIENDLY);
				}
				else
				{
					DisplayPlayerMessage((ItemPtr)victim,hitter,ST_PLAYERKILLEDENEMY);
				}
			}
		}
		else if (commsplayerdead)
		{
// player has crashed
			DisplayPlayerMessage((ItemPtr)victim,hitter,ST_PLAYERKILLEDCOMMS);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewAeroDevAction
//Date			Sept 1998
//------------------------------------------------------------------------------
void	DPlay::NewAeroDevAction(UByte devID,SWord Attractor)
{
	if (!_Replay.Playback)
	{
		NewSpecial(PIDC_AERODEVICE, devID,((Attractor>>8)&0xff),Attractor&0xff);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessPlayerSlotRequest
//Date			Thu 8 Oct 1998
//------------------------------------------------------------------------------
void	DPlay::ProcessPlayerSlotRequest(char* message,ULong from)
{
	if (Host) 
	{
// step through H2H_Player struc and see if anybody has this slot. If not then fill
// in slot and send a message to all players indicating that player has taken this slot
// in form of a pid_slotinfoupdate message

	LPSLOTPOSPACK p=(LPSLOTPOSPACK)message;

	int pos=p->position;
	int	squadnum=p->squadron;
	ULong i=0;
	bool	slotfree=true;

	while	(		(i < MAXPLAYERS)
			)
	{
		if  (		(H2H_Player[i].squadron == squadnum)
			&&		(H2H_Player[i].position == pos )
			&&		(H2H_Player[i].status!=CPS_NONE)

			)
			{
				slotfree=false;
				break;
			}
		i++;
	}
	
	SLOTPOSPACK s;

	s.PlayerID=from;
	s.PacketID=PID_SLOTINFOUPDATE;
	s.squadron=squadnum;
	s.position=pos;
	
	if (slotfree)
	{
		s.Slot=1;

		i=DPID2Slot(from);

		if (i!=MAXPLAYERS)
		{
			H2H_Player[i].squadron=squadnum;
			H2H_Player[i].position=pos;
		}
		UpdateFrag=TRUE;

// update ready room 

		DisplayInfo=TRUE;
	}
	else
		s.Slot=0;

	SendMessageToPlayer((char*)&s,sizeof(SLOTPOSPACK),0);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendSlotRequest
//Date			Thu 8 Oct 1998
//------------------------------------------------------------------------------
Bool	DPlay::SendSlotRequest(int pos, int squadron)
{
	SLOTPOSPACK p;

	p.squadron=squadron;
	p.position=pos;
	p.PacketID=PID_SLOTREQUEST;
	p.Slot=mySlot;

	if (SendRequestMessage((char*)&p,sizeof(SLOTPOSPACK)))
		 return TRUE;

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReceiveSlotRequestOK
//Date			Thu 8 Oct 1998
//------------------------------------------------------------------------------
Bool	DPlay::ReceiveSlotRequestOK()
{
	char* Buffer;
	ULong	BufLen,From;
	bool	got=FALSE;
	LPSLOTPOSPACK pack;
	ULong now=timeGetTime();
	CommsTimeout time(now,CommsTimeoutLength);

	while (!got)
	{
		now=timeGetTime();
		if (time.TimedOut(now))
			return FALSE;

		while (ReceiveNextMessageToMe(Buffer,BufLen,From,DPRECEIVE_TOPLAYER))
		{
			if (From==DPID_SYSMSG)
			{
				_DPlay.ProcessSystemMessage(Buffer);
			}
			else if (From!=aggID)
			{
				pack=(LPSLOTPOSPACK)Buffer;

				if (pack->PacketID==PID_SLOTINFOUPDATE)
				{
					if (pack->PlayerID==myDPlayID)
					{
						if (pack->Slot)
							return TRUE;
						else
							return FALSE;
					}
				}
				else
				{
					ProcessPlayerMessage(Buffer,BufLen,From);
				}
			}
		}
	}

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SlotFree
//Date			Mon 12 Oct 1998
//------------------------------------------------------------------------------
Bool	DPlay::SlotFree(int pos, int squadron)
{
	ULong i=0;
	if (_DPlay.PlayerCreated)
	{
		if (Host)
		{
			while	(		(i < MAXPLAYERS)
			)
			{
				if  (		(H2H_Player[i].squadron == squadron)
					&&		(H2H_Player[i].position == pos)
					&& 		(H2H_Player[i].status!=CPS_NONE)	 

				)
				{
					return FALSE;
				}
				i++;
			}

			SLOTPOSPACK s;

			s.PacketID=PID_SLOTINFOUPDATE;
			s.squadron=squadron;
			s.position=pos;
			s.PlayerID=myDPlayID;

			SendMessageToGroup((char*)&s,sizeof(SLOTPOSPACK));

			return TRUE;
		}
		else if (SendSlotRequest(pos,squadron))
			if (ReceiveSlotRequestOK())
				return TRUE;
		return FALSE;
	}else
		return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessSlotInfoUpdate
//Date			Mon 12 Oct 1998
//------------------------------------------------------------------------------
void	DPlay::ProcessSlotInfoUpdate(char* pack)
{
	LPSLOTPOSPACK p=(LPSLOTPOSPACK)pack;
	ULong n;

	{
		n=DPID2Slot(p->PlayerID);

		if (n!=MAXPLAYERS)
		{
			H2H_Player[n].squadron=p->squadron;
			H2H_Player[n].position=p->position;
		}
	}
// need to update frag screen

	UpdateFrag=TRUE;

// update ready room 

	DisplayInfo=TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGameDetails
//Date			Tue 13 Oct 1998
//------------------------------------------------------------------------------
Bool	DPlay::GetGameDetails()
{
	SendGameDetailsRequest();

	if (!ReceiveGameDetails())
	{
#ifndef NDEBUG
		CommsMessage(IDS_NOGAMEDETAILS);
#endif
	 	return FALSE;
	}

// this is now more of a "send me beginning info" packet rather than specifically for
// csquick struc

	SendCSRequest();

	{										
		if (!GetCS())
		{
#ifndef NDEBUG
			CommsMessage(IDS_NOCSSTRUC);
#endif
			return FALSE;
		}
	}										

	if (GameType>TEAMPLAY)
	{
		if (!GetPilotsStatus())
		{
#ifndef NDEBUG
			CommsMessage(IDS_NOPILOTSSTATUS);
#endif
			return FALSE;
		}
	}

	if (GameType==COMMSQUICKMISSION)
	{
		if (!ReceiveCampaignStruc())
		{
#ifndef NDEBUG
			CommsMessage(IDS_NOCAMPAIGNSTRUC);
#endif
			return FALSE;
		}
	}

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendGameDetailsRequest
//Date			Tue 13 Oct 1998
//------------------------------------------------------------------------------
void	DPlay::SendGameDetailsRequest()
{
	GAMEDETAILS pack;

	ULong retries=10;

	pack.PacketID=PID_GAMEDETAILSREQUEST;

	while (!SendRequestMessage((char*)&pack,sizeof(GAMEDETAILS)))
	{
		ULong end=timeGetTime()+100; 

		while (timeGetTime()<end)
		{
			Sleep(0);
		}
		retries--;

		if (!retries)
			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReceiveGameDetails
//Date			Tue 13 Oct 1998
//------------------------------------------------------------------------------
Bool	DPlay::ReceiveGameDetails()
{
	char* Buffer;
	ULong	BufLen,From;
	LPGAMEDETAILS pack;

	if (ReceivePacketWithReRequest(PID_GAMEDETAILSINFO,PID_GAMEDETAILSREQUEST,Buffer,BufLen,0))
	{
		pack=(LPGAMEDETAILS)Buffer;
		RateDivider=pack->DataRate;
		GameType=(GameTypes)pack->GameType;
		GameIndex=pack->GameIndex;
		return TRUE;
	}

	return FALSE;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetDeadPlayers
//Date			Tue 20 Oct 1998
//------------------------------------------------------------------------------
void	DPlay::ResetDeadPlayers(AirStrucPtr ac)
{
	ULong n;

	for (n=0;n<MAXPLAYERS;n++)
	{
		if (AllocPacket[n]==ac->uniqueID.count)
		{
			deadplayers&=(ULong)(~(1<<n));
			break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetBattlePosition
//Date			Tue 27 Oct 1998
//Description	If player is joining a game then put ac near others.
//				This is an average of all the other players ac positions
//				plus 10000 above the highest already in so that no 
//				collision occurs.
//------------------------------------------------------------------------------
void	DPlay::GetBattlePosition(UByte joiningslot)
{
	ULong xpos=0,zpos=0,ypos=0,slot;
	UByte num=0;
	AirStrucPtr ac;
	WorldStuff &world = mobileitem::GetWorld();


	for (slot=0;slot<MAXPLAYERS;slot++)
	{
		if (H2H_Player[slot].status==CPS_3D && slot!=joiningslot)
		{
			ac=(AirStrucPtr)Persons2::ConvertPtrUID((UniqueID)AllocPacket[slot]);

			if (ac)
			{
				xpos+=ac->World.X;
				zpos+=ac->World.Z;
				num++;

				if (ac->World.Y>ypos)
					ypos=ac->World.Y;
			}
		}
	}


	ac=(AirStrucPtr)Persons2::ConvertPtrUID((UniqueID)AllocPacket[joiningslot]);

 	UWord	oldsector=	world.GetSector(ac);

	if (num)
	{
		xpos/=num;
		zpos/=num;
		ypos+=2000; // 10K a bit far for WW2

		ac->World.X=xpos;
		ac->World.Y=ypos;
		ac->World.Z=zpos;

		if (ac==Persons2::PlayerSeenAC)
		{
			Persons2::PlayerGhostAC->World.X=xpos;
			Persons2::PlayerGhostAC->World.Y=ypos;
			Persons2::PlayerGhostAC->World.Z=zpos;

// make sure flight model knows whats going on

			Persons2::PlayerSeenAC->fly.pModel->UpdateModel(Persons2::PlayerSeenAC);
		}	
	}

	UWord	newsector=	world.GetSector(ac);

	if (newsector!=oldsector)
	{
		world.RemoveFromSector(ac,oldsector);
		world.AddToWorld(ac);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SwitchPlayerACToAIAC
//Date			Fri 30 Oct 1998
//
//Description	When a player leaves a coop game the AC that he is in
//				must be taken over by the AI.
//------------------------------------------------------------------------------
Bool	DPlay::SwitchPlayerACToAIAC(AirStrucPtr AC)
{
	if (AC->uniqueID.commsmove)
	{
// only switch AC if it is a comms ac
// AC must determine what its best options are at moment of taking control

		AC->movecode=AUTO_FOLLOWWP;
		AC->information = IF_OUT_POS;
		AC->manoeuvretime = 0;
		AC->uniqueID.commsmove=FALSE;
	}
	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SwitchAIACToPlayerAC
//Date			Fri 30 Oct 1998
//------------------------------------------------------------------------------
Bool	DPlay::SwitchAIACToPlayerAC(AirStrucPtr AC, ULong slot)
{
// is this enough? will force ac to go through prediction phase rather than moveitem
// so willl not do any AI stuff.
// NO NO NO NO
//	player needs to set up seenac, ghostac etc
// delete old fmodel?

#ifndef NDEBUG
	if (slot==mySlot)
	{
// player should never get here
		INT3;
	}
#endif
// for both remotes and player

// update alloc packet entry

	AC->uniqueID.commsmove=TRUE;
	AllocPacket[slot]=AC->uniqueID.count;

// need to update historical buffer. just fill up with ac position. it will be the same 
// on all machines and doesnt need to be massively accurate for AAA.

	FillHistBuffer(AC,slot);

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewWingmanCommand
//Date			Sun 1 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::NewWingmanCommand(UByte decision, UByte option, UniqueID trg)
{
	UniqueID id1,id2;

#ifndef NDEBUG 
// decision is 7 bits 0-100 really
// option is 4 bits 0-9

	if (decision>127)
		INT3;

	if (option>9)
		INT3;
#endif

	id1=trg;
	id2=(UniqueID)((option<<7)+decision);

	NewUIDSPacket(id1,id2,PIDC_WINGMANCOMMAND);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessWingmanCommand
//Date			Sun 1 Nov 1998
//------------------------------------------------------------------------------
UByte	DPlay::ProcessWingmanCommand(UniqueID id1, UniqueID id2, ULong slot)
{
	AirStrucPtr caller,callee;

// caller/callee is always ghostac now
	
	if (_DPlay.Implemented)
	{
		AirStrucPtr ac=(AirStrucPtr)Persons2::ConvertPtrUID((UniqueID)AllocPacket[slot]); 
		if (ac==Persons2::PlayerSeenAC) 
			ac=Persons2::PlayerGhostAC; 
		caller=callee=ac;
	}
	else
	{
		caller=callee=(AirStrucPtr)Persons2::PlayerGhostAC;
	}

	item* target=Persons2::ConvertPtrUID(id1);			

	if (target==Persons2::PlayerSeenAC)
		target=Persons2::PlayerGhostAC;

	ULong	decision,option;

	decision=id2&0x7f;
	option=id2>>7;

	DecisionAI* dec=DecisionAI::optiontable[decision];
	DecisionAI::OptionRef* opt=dec->GetMsgOptions();
	opt+=option;

	MESSAGE_STRUC newMsg(opt->saidmsg,MSG_HIPRIORITY,callee,target,callee);
	OverLay.SendMessageAndCall(&newMsg,opt->airesult[0]);

	return (PacketLength(PIDC_WINGMANCOMMAND));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Process2ndAIACPositionPacket
//Date			Mon 2 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::Process2ndAIACPositionPacket(LPACPACKET p,UByte slot)
{
// packet contains
// X,Y			= AC UID
// Z,S,H,P		= AC Z pos
// R,			= bottom 8 bits of roll
// V,b1			= AC Pitch
// b2,b3,b4,b5	= AC Vel

	if (Implemented)
	{
		SLong zpos,vel;
		UWord pitch,botroll,uid;
		AirStrucPtr aiac;

		uid=(p->X<<8)+p->Y;
		zpos=(p->Z<<24)+(p->Bull<<20)+(p->Shift<<16)+(p->Heading<<8)+p->Pitch;
		vel=(p->byte2<<24)+(p->byte3<<16)+(p->byte4<<8)+p->byte5;
		pitch=(p->Velocity_<<8)+p->byte1;
		botroll=p->Roll;

		aiac=*Persons2::ConvertPtrUID((UniqueID)uid);

		if (aiac)
		{
			if (!AIACPositions[slot])
			{
				AIACPositions[slot]=new ACPOSENTRY;
				AIACPositions[slot]->next=NULL;

				AIACPositions[slot]->Pos.Z=zpos;
				AIACPositions[slot]->Velocity=vel;
				AIACPositions[slot]->Roll.a+=botroll;
				AIACPositions[slot]->Pitch.a=pitch;
				AIACPositions[slot]->ID=(UniqueID)uid;
				AIACPositions[slot]->extrainfo=2;
			}
			else if (AIACPositions[slot]->ID==(UniqueID)uid)
			{
				AIACPositions[slot]->Pos.Z=zpos;
				AIACPositions[slot]->Velocity=vel;
				AIACPositions[slot]->Roll.a+=botroll;
				AIACPositions[slot]->Pitch.a=pitch;
				AIACPositions[slot]->ID=(UniqueID)uid;
				AIACPositions[slot]->extrainfo|=2;

				if (AIACPositions[slot]->extrainfo==3)
				{
// we now have a full position, update the ac and delete this entry

					UpdateACFromPositionList(AIACPositions[slot]);
					DeleteEntryFromAIACPositionsList(AIACPositions[slot],slot);
				}
			}
			else
			{
				LPACPOSENTRY p=AIACPositions[slot];

				while (p->next)
				{
					if (p->ID==(UniqueID)uid)
					{
// eh up, this ac's already in here, lets update it

						p->Pos.Z=zpos;
						p->Velocity=vel;
						p->Roll.a+=botroll;
						p->Pitch.a=pitch;
						p->extrainfo|=2;

						if (p->extrainfo==3)
						{
// we now have a full position, update the ac and delete this entry

							UpdateACFromPositionList(p);
							DeleteEntryFromAIACPositionsList(p,slot);
						}
						return;
					}
					p=p->next;
				}

				LPACPOSENTRY temp=new ACPOSENTRY;
				temp->next=NULL;

				temp->Pos.Z=zpos;
				temp->Velocity=vel;
 				temp->Roll.a+=botroll;
				temp->Pitch.a=pitch;
				temp->ID=(UniqueID)uid;
				temp->extrainfo=2;

				p->next=temp;
				temp=NULL;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Process1stAIACPositionPacket
//Date			Mon 2 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::Process1stAIACPositionPacket(LPACPACKET p,UByte slot)
{
// packet contains
//	X,Y			= AC UID
//	Z,S,b1,b2 	= AC X pos
//	H,P,R,V		= AC Y pos
//	b3,b4		= AC Heading
// 	b5			= top 8 bits of roll

	if (Implemented)
	{
		SLong xpos,ypos;
		UWord heading,toproll,uid;
		AirStrucPtr aiac;

		uid=(p->X<<8)+p->Y;
		xpos=(p->Z<<24)+(p->Bull<<20)+(p->Shift<<16)+(p->byte1<<8)+p->byte2;
		ypos=(p->Heading<<24)+(p->Pitch<<16)+(p->Roll<<8)+p->Velocity_;
		heading=(p->byte3<<8)+p->byte4;
		toproll=p->byte5<<8;

		aiac=*Persons2::ConvertPtrUID((UniqueID)uid);

		if (aiac)
		{
			if (!AIACPositions[slot])
			{
				AIACPositions[slot]=new ACPOSENTRY;
				AIACPositions[slot]->next=NULL;

				AIACPositions[slot]->Pos.X=xpos;
				AIACPositions[slot]->Pos.Y=ypos;
				AIACPositions[slot]->Heading.a=heading;
				AIACPositions[slot]->Roll.a=toproll;
				AIACPositions[slot]->ID=(UniqueID)uid;
				AIACPositions[slot]->extrainfo=1;
			}
			else if (AIACPositions[slot]->ID==(UniqueID)uid)
			{
				AIACPositions[slot]->Pos.X=xpos;
				AIACPositions[slot]->Pos.Y=ypos;
				AIACPositions[slot]->Heading.a=heading;
				AIACPositions[slot]->Roll.a=toproll;
				AIACPositions[slot]->ID=(UniqueID)uid;
				AIACPositions[slot]->extrainfo|=1;

				if (AIACPositions[slot]->extrainfo==3)
				{
// we now have a full position, update the ac and delete this entry

					UpdateACFromPositionList(AIACPositions[slot]);
					DeleteEntryFromAIACPositionsList(AIACPositions[slot],slot);
				}
			}
			else
			{
				LPACPOSENTRY p=AIACPositions[slot];

				while (p->next)
				{
					if (p->ID==(UniqueID)uid)
					{
// eh up, this ac's already in here, lets update it

						p->Pos.X=xpos;
						p->Pos.Y=ypos;
						p->Heading.a=heading;
						p->Roll.a=toproll;
						p->extrainfo|=1;

						if (p->extrainfo==3)
						{
// we now have a full position, update the ac and delete this entry

							UpdateACFromPositionList(p);
							DeleteEntryFromAIACPositionsList(p,slot);
						}
						return;
					}
					p=p->next;
				}

				LPACPOSENTRY temp=new ACPOSENTRY;
				temp->next=NULL;

				temp->Pos.X=xpos;
				temp->Pos.Y=ypos;
				temp->Heading.a=heading;
 				temp->Roll.a=toproll;
				temp->ID=(UniqueID)uid;
				temp->extrainfo=1;

				p->next=temp;
				temp=NULL;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Make2ndAIACPositionPacket
//Date			Mon 2 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::Make2ndAIACPositionPacket(LPACPACKET p)
{
// packet contains
// X,Y			= AC UID
// Z,S,H,P		= AC Z pos
// R,			= bottom 8 bits of roll
// V,b1			= AC Pitch
// b2,b3,b4,b5	= AC Vel

	LPACPOSENTRY	aiacentry=MyAIACPositionsToSend;
	AirStrucPtr		aiac=*Persons2::ConvertPtrUID(aiacentry->ID);

	aiacentry->extrainfo=2;

// UID

	p->X=(aiacentry->ID>>8)&0xff;
	p->Y=aiacentry->ID&0xff;

// Z position

	p->Z=(aiac->World.Z>>24)&0xff;
	p->Shift=(aiac->World.Z>>16)&0x0f;
	p->Bull=(aiac->World.Z>>20)&0x0f;
	p->Heading=(aiac->World.Z>>8)&0xff;
	p->Pitch=aiac->World.Z&0xff;

// bottom byte of roll

	p->Roll=(aiac->roll.a)&0xff;

// Pitch

	p->Velocity_=(aiac->pitch.a>>8)&0xff;
	p->byte1=(aiac->pitch.a)&0xff;

// Velocity

	p->byte2=(aiac->vel_>>24)&0xff;
	p->byte3=(aiac->vel_>>16)&0xff;
	p->byte4=(aiac->vel_>>8)&0xff;
	p->byte5=(aiac->vel_)&0xff;

	p->IDCode=PIDC_AIACPOSITION2;

// sent all info now - delete entry

	MyAIACPositionsToSend=aiacentry->next;
	delete aiacentry;
	aiacentry=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Make1stAIACPositionPacket
//Date			Mon 2 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::Make1stAIACPositionPacket(LPACPACKET p)
{
// packet contains
//	X,Y			= AC UID
//	Z,S,b1,b2 	= AC X pos
//	H,P,R,V		= AC Y pos
//	b3,b4		= AC Heading
// 	b5			= top 8 bits of roll

	LPACPOSENTRY	aiacentry=MyAIACPositionsToSend;
	AirStrucPtr		aiac=*Persons2::ConvertPtrUID(aiacentry->ID);

	aiacentry->extrainfo=1;

// UID

	p->X=(aiacentry->ID>>8)&0xff;
	p->Y=aiacentry->ID&0xff;

// X pos

	p->Z=(aiac->World.X>>24)&0xff;
	p->Shift=(aiac->World.X>>16)&0x0f;
	p->Bull=(aiac->World.X>>20)&0x0f;
	p->byte1=(aiac->World.X>>8)&0xff;
	p->byte2=(aiac->World.X)&0xff;

// Y pos

	p->Heading=(aiac->World.Y>>24)&0xff;
	p->Pitch=(aiac->World.Y>>24)&0xff;
	p->Roll=(aiac->World.Y>>24)&0xff;
	p->Velocity_=(aiac->World.Y>>24)&0xff;

// Heading

	p->byte3=(aiac->hdg.a>>8)&0xff;
	p->byte4=(aiac->hdg.a)&0xff;

// top byte of roll

	p->byte5=(aiac->roll.a>>8)&0xff;

	p->IDCode=PIDC_AIACPOSITION1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddAIACToPositionList
//Date			Mon 2 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::AddAIACToPositionList(AirStrucPtr ac)
{
	LPACPOSENTRY	temp=MyAIACPositionsToSend;
	LPACPOSENTRY	acpos=new ACPOSENTRY;

	acpos->ID=ac->uniqueID.count;

// dont add position here, do it when info is about to be sent to that pos is as up to date
// as possible at least on owners machine

	acpos->extrainfo=0;
	acpos->next=NULL;

// if ac is already in list dont add

	if (temp)
	{
		while (temp->next)
		{
			if (acpos->ID==temp->ID)
				return;

			temp=temp->next;
		}

		if (acpos->ID!=temp->ID)
			temp->next=acpos;

		acpos=NULL;
	}
	else
	{
		MyAIACPositionsToSend=acpos;
		acpos=NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteAIACPositionList
//Date			Mon 2 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::DeleteMyAIACPositionToSendList()
{
	LPACPOSENTRY	temp=MyAIACPositionsToSend,temp1;

	while (temp)
	{
		temp1=temp->next;
		delete temp;
		temp=temp1;
	}
	MyAIACPositionsToSend=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteEntryFromAIACPositionsList
//Date			Mon 2 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::DeleteEntryFromAIACPositionsList(LPACPOSENTRY p,UByte slot)
{
	LPACPOSENTRY temp,temp1;

	temp=AIACPositions[slot];

	if (temp->ID==p->ID)
	{
		temp1=AIACPositions[slot]->next;
		delete AIACPositions[slot];
		AIACPositions[slot]=temp1;
	}
	else
	{
		temp1=temp->next;

		while (temp1)
		{
			if (temp1->ID==p->ID)
				break;

			temp1=temp1->next;
			temp=temp->next;
		}
		
		if (temp1)
		{
			temp=temp1->next;

			delete temp1;
			temp1=NULL;
		}
		else
		{
			_Error.SayAndQuit("Entry not in list");
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteAIACPositionsList
//Date			Mon 2 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::DeleteAIACPositionsList()
{
	LPACPOSENTRY temp,temp1;
	ULong n;

	for (n=0;n<MAXPLAYERS;n++)
	{
		temp=AIACPositions[n];

		while (temp)
		{
			temp1=temp->next;
			delete temp;
			temp=temp1;
		}
		AIACPositions[n]=NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateACFromPositionList
//Date			Mon 2 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::UpdateACFromPositionList(LPACPOSENTRY p)
{
	AirStrucPtr ac=(AirStrucPtr)Persons2::ConvertPtrUID(p->ID);

// if ac has been killed whilst delta packets arrived then ignore them

	if (ac)
	{
		if (ac->movecode!=AUTO_NOPPILOT)
		{
			int n;

			WorldStuff &world = mobileitem::GetWorld();
			UWord oldsector=world.GetSector(ac);

			ac->World.X=p->Pos.X;
			ac->World.Y=p->Pos.Y;
			ac->World.Z=p->Pos.Z;
			ac->hdg.a=p->Heading.a;
			ac->pitch.a=p->Pitch.a;
			ac->roll.a=p->Roll.a;
			ac->vel_=p->Velocity;

// do some prediction based on estimated number of frames latency
// for now assume data rate number of frames latency

			for (n=0;n<RateDivider;n++)
				PredictMove(ac);

// update model values

			ac->fly.pModel->UpdateModel(ac);

// reset and let ai re-engage

			ac->movecode=AUTO_FOLLOWWP;		//should not be necessary. Movecode should be valid anyway????
			ac->CommsOwner=UID_NULL;

			ResetAllAIFields(ac);

			_Replay.ResetSecondaryFMValues(ac);

			UWord	newsector=world.GetSector(ac);

			if (newsector!=oldsector)
			{
				world.RemoveFromSector(ac,oldsector);
				world.AddToWorld(ac);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendACDetails
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::SendACDetails()
{
	AirStrucPtr		ac;
	ASPRIMARYVALUES aspv;
	UniqueID		id;
	FMPRIMARYVALUES	fmpv;
	PRIMARYENGINEVALUES eng;
	PRIMARYELMTVALUES	elmt;
	MIPRIMARYVALUES	mipv;
	PENGINE	pEngine;
	PMAINPLANE pMainPlane;
	FP output;
	UByteP temp;
	UByte	pack[1024];
	ULong packsize,numanimpacks=0,num;
	GENERIC c;
	AERODEVVALUES adv;
	PAERODEVICE pAeroDevice;
	PGEAR pGear;

// send all position/data/flight model stuff

	ac=*AirStruc::ACList;

	int sent=0;

	while (ac)
	{
		if (!ac->uniqueID.commsmove || (PlayerSync && ac!=Persons2::PlayerSeenAC))
		{
// determine sizeof packet
// declare buffer big enough to hold all data and determine size as data
// is being filled in

			temp=pack;

			packsize=sizeof(ULong)
					+(2*sizeof(UWord))
					+sizeof(ASPRIMARYVALUES)
					+sizeof(MIPRIMARYVALUES);			

	// put info into packet

			*(ULong*)temp=PID_ACDATA;
			temp+=sizeof(ULong);

			*(UWord*)temp=ac->uniqueID.count;
			temp+=sizeof(UWord);

			*(UWord*)temp=ac->CommsOwner;
			temp+=sizeof(UWord);

			_Replay.GetPrimaryASData(ac,&aspv);

			CopyMemory(temp,&aspv,sizeof(ASPRIMARYVALUES));
			temp+=sizeof(ASPRIMARYVALUES);

			_Replay.GetPrimaryMIData(ac,&mipv);

			CopyMemory(temp,&mipv,sizeof(MIPRIMARYVALUES));
			temp+=sizeof(MIPRIMARYVALUES);

			pAeroDevice=ac->fly.pModel->DeviceList;

			while (pAeroDevice)
			{
				_Replay.GetAeroDevData(&adv,pAeroDevice);

				CopyMemory(temp,&adv,sizeof(AERODEVVALUES));
				temp+=sizeof(AERODEVVALUES);
				packsize+=sizeof(AERODEVVALUES);

				pAeroDevice=pAeroDevice->List.NextItem();
			}

			if (!ac->ai.simpleacm && ac->movecode==AUTO_COMBAT && !ac->Status.deaded)
			{
				_Replay.GetPrimaryFMData(ac,&fmpv);

				CopyMemory(temp,&fmpv,sizeof(FMPRIMARYVALUES));
				temp+=sizeof(FMPRIMARYVALUES);
				packsize+=sizeof(FMPRIMARYVALUES);

				pEngine = ac->fly.pModel->EngineList;

				while (pEngine)
				{
					_Replay.GetPrimaryEngineData(&eng,pEngine);

					CopyMemory(temp,&eng,sizeof(PRIMARYENGINEVALUES));
					temp+=sizeof(PRIMARYENGINEVALUES);
					packsize+=sizeof(PRIMARYENGINEVALUES);

					pEngine=pEngine->List.NextItem();
				}

				pMainPlane = ac->fly.pModel->MainPlaneList;

				while (pMainPlane)
				{
					_Replay.GetPrimaryElmtData(&elmt,pMainPlane);

					CopyMemory(temp,&elmt,sizeof(PRIMARYELMTVALUES));
					temp+=sizeof(PRIMARYELMTVALUES);
					packsize+=sizeof(PRIMARYELMTVALUES);

					pMainPlane=pMainPlane->List.NextItem();
				}

				pGear=ac->fly.pModel->GearList;

				while (pGear)
				{
					output=_Replay.GetSuspensionData(pGear);

					*(FP*)temp=output;
					temp+=sizeof(FP);
					packsize+=sizeof(FP);

					pGear = pGear->List.NextItem();
				}
			}
			else
			{
				*(FP*)temp=ac->fly.pModel->Mass;
				packsize+=sizeof(FP);
			}

			if (packsize>1024)
				_Error.SayAndQuit("AC Details>1024");

			UByteP realpack=new UByte[packsize];

			memcpy(realpack,pack,packsize);

			SendMessageToGroup((char*)realpack,packsize);
			sent++;

			delete [] realpack;

// if we are sending other players positions dont send anim, that will
// have already been sent by player 

			if (!ac->uniqueID.commsmove)
			{
				num=SHAPE.ScanAnimData((ItemPtr)ac);

				if (num!=0)
					numanimpacks++;
			}
		}
		ac=*ac->nextmobile;
	}

// send number of ac anim packs

	Sleep(SENDPAUSE);
 	SendNumAnims(numanimpacks,PID_NUMACANIMS);
	Sleep(SENDPAUSE);

// send anim data 

	ac=*AirStruc::ACList;

	while (ac)
	{
		if (!ac->uniqueID.commsmove)
		{
			num=SHAPE.ScanAnimData(ac);

 			if (num)
			{
				SendAnimData(PID_ACANIM,num,ac->uniqueID.count);
			}
		}
		ac=*ac->nextmobile;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetACDetails
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
Bool	DPlay::GetACDetails()
{
#ifdef SYNCDATA
#ifdef DETAILS
	FILE* fp=fopen("resync.txt","at");
#endif
#endif
	static ULong need;
	static ULong got;

	AirStrucPtr		ac;

	switch (SyncData.acstage)
	{
	case 0:
		ac=*AirStruc::ACList;

		need=0;
		got=0;
		while (ac)
		{
			if (!ac->uniqueID.commsmove || PlayerSync)
			{
				need++;
			}

			ac=*ac->nextmobile;
		}

		if (PlayerSync)
			need--;

		SyncData.acstage++;
		break;

	case 1:

		if (need!=0)
		{
			if (GetSyncData(PID_ACDATA,need,got))
				SyncData.acstage++;
#ifdef SYNCDATA
#ifdef DETAILS
			fprintf(fp,"AC details: need %d got %d\n",need,got);
#endif
#endif
		}
		else
		{
			SyncData.acstage++;
		}

		break;

	case 2:

		if (GetNumAnims(PID_NUMACANIMS,need))
		{
			got=0;
			SyncData.acstage++;
		}
		break;
		 
	case 3:

		if (need!=0)
		{
			if (!GetAllAnims(PID_ACANIM,need,got))
			{
#ifdef SYNCDATA
#ifdef DETAILS
			fprintf(fp,"AC anims: need %d got %d\n",need,got);
#endif
#endif
				break;
			}
		}

		SyncData.acstage=0;
#ifdef SYNCDATA
#ifdef DETAILS
		fclose(fp);
#endif
#endif
		return TRUE;
	}
#ifdef SYNCDATA
#ifdef DETAILS
	fclose(fp);
#endif
#endif

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendMobDetails
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::SendMobDetails()
{
	MobileItemPtr item;
	MIPRIMARYVALUES	mipv;
	ULong num,numanimpacks=0,packsize;
	UByteP pack,temp;

	item=mobileitem::MobileList;

	while (item)
	{
// determine sizeof packet

		packsize=sizeof(ULong)
				+sizeof(UWord)
				+sizeof(MIPRIMARYVALUES);

		pack=new UByte[packsize];
		temp=pack;

// put info into packet

		*(ULong*)temp=PID_MOBDATA;
		temp+=sizeof(ULong);

		*(UWord*)temp=item->uniqueID.count;
		temp+=sizeof(UWord);

		_Replay.GetPrimaryMIData(item,&mipv);

		CopyMemory(temp,&mipv,sizeof(MIPRIMARYVALUES));
		temp+=sizeof(MIPRIMARYVALUES);

		SendMessageToGroup((char*)pack,packsize);

		delete [] pack;

		num=SHAPE.ScanAnimData((ItemPtr)item);

		if (num!=0)
			numanimpacks++;

		item=item->nextmobile;
	}

// send number of mob anim packs

	Sleep(SENDPAUSE);
	SendNumAnims(numanimpacks,PID_NUMMOBANIMS);
	Sleep(SENDPAUSE);

// send anim data

	item=mobileitem::MobileList;

	while (item)
	{
		num=SHAPE.ScanAnimData(item);

 		if (num)
		{
			SendAnimData(PID_MOBANIM,num,item->uniqueID.count);
		}

		item=item->nextmobile;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMobDetails
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
Bool	DPlay::GetMobDetails()
{
#ifdef SYNCDATA
#ifdef DETAILS
	FILE* fp=fopen("resync.txt","at");
#endif
#endif
	static ULong need;
	static ULong got;

	MobileItemPtr	item;

	switch (SyncData.mobstage)
	{
	case 0:
		item=mobileitem::MobileList;

		need=0;
		got=0;
		while (item)
		{
			need++;

			item=*item->nextmobile;
		}
		SyncData.mobstage++;
		break;

	case 1:	 

		if (need!=0)
		{
			if (GetSyncData(PID_MOBDATA,need,got))
				SyncData.mobstage++;
#ifdef SYNCDATA
#ifdef DETAILS
			fprintf(fp,"Mob details: need %d got %d\n",need,got);
#endif
#endif
		}
		else
		{
			SyncData.mobstage++;
		}

		break;

	case 2:	 

		if (GetNumAnims(PID_NUMMOBANIMS,need))
		{
			got=0;
			SyncData.mobstage++;
		}
		break;

	case 3:

		if (need!=0)
		{
			if (!GetAllAnims(PID_MOBANIM,need,got))
			{
#ifdef SYNCDATA
#ifdef DETAILS
			fprintf(fp,"Mob anims: need %d got %d\n",need,got);
#endif
#endif
				break;
			}
		}

		SyncData.mobstage=0;
#ifdef SYNCDATA
#ifdef DETAILS
		fclose(fp);
#endif
#endif
		return TRUE;
	}
#ifdef SYNCDATA
#ifdef DETAILS
		fclose(fp);
#endif
#endif

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSyncData
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
Bool	DPlay::GetSyncData(ULong type,ULong need,ULong& got)
{
	char* buffer;
	ULong	buflen,from;

	while (ReceiveNextMessageToMe(buffer,buflen,from,DPRECEIVE_TOPLAYER))
	{
		if (from==DPID_SYSMSG)
		{
			ProcessSystemMessage(buffer);
		}
		else if (from!=aggID)
		{
			if (*(ULong*)buffer==type)
			{
				switch (type)
				{
				case PID_MOBDATA:
					ProcessMobData((UByteP)buffer);
					break;
				case PID_ACDATA:
					ProcessACData((UByteP)buffer);
					break;
				}

				got++;

				if (got==need)
					return TRUE;
			}
			else 
			{
				ProcessPlayerMessage(buffer,buflen,from);
			}
		}
	}
	if (got==need)
		return TRUE;
	
	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessACData
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::ProcessACData(UByteP pack)
{
	PENGINE	pEngine;
	PMAINPLANE pMainPlane;
	UniqueID id;
	AirStrucPtr ac;
	WorldStuff &world = mobileitem::GetWorld();
	PAERODEVICE pAeroDevice;
	PGEAR pGear;
	FP legpos;

	pack+=sizeof(ULong); // step over PID


		id=(UniqueID)(*(UWord*)pack);
		pack+=sizeof(UWord);
		ac=(AirStrucPtr)Persons2::ConvertPtrUID(id);

#ifndef NDEBUG
	if (!ac)
		INT3;
#endif

	if (!ac)
		return;

	UWord	oldsector=	world.GetSector(ac);

	ac->CommsOwner=(UniqueID)(*(UWord*)pack);
	pack+=sizeof(UWord);

	_Replay.RestorePrimaryASValues(ac,(LPASPRIMARYVALUES)pack);
	pack+=sizeof(ASPRIMARYVALUES);

	_Replay.RestorePrimaryMIValues((MobileItemPtr)ac,(LPMIPRIMARYVALUES)pack);
	pack+=sizeof(MIPRIMARYVALUES);

	pAeroDevice=ac->fly.pModel->DeviceList;
	while (pAeroDevice)
	{
		_Replay.RestoreAeroDevData((LPAERODEVVALUES)pack,pAeroDevice);

		pack+=sizeof(AERODEVVALUES);

		pAeroDevice=pAeroDevice->List.NextItem();
	}

	if (!ac->ai.simpleacm && ac->movecode==AUTO_COMBAT && !ac->Status.deaded)
	{
		_Replay.RestorePrimaryFMData(ac,(LPFMPRIMARYVALUES)pack);
		pack+=sizeof(FMPRIMARYVALUES);

		pEngine = ac->fly.pModel->EngineList;

		while (pEngine)
		{
			_Replay.RestorePrimaryEngineData((LPPRIMARYENGINEVALUES)pack,pEngine);

			pack+=sizeof(PRIMARYENGINEVALUES);

			pEngine=pEngine->List.NextItem();
		}

		pMainPlane = ac->fly.pModel->MainPlaneList;

		while (pMainPlane)
		{
			_Replay.RestorePrimaryElmtData((LPPRIMARYELMTVALUES)pack,pMainPlane);

			pack+=sizeof(PRIMARYELMTVALUES);

			pMainPlane=pMainPlane->List.NextItem();
		}

		pGear=ac->fly.pModel->GearList;

		while (pGear)
		{
			legpos=*(FP*)pack;
			_Replay.RestoreSuspensionData(legpos,pGear);
			pack+=sizeof(FP);

	 		pGear = pGear->List.NextItem();
		}
	}
	else
	{
		ac->fly.pModel->Mass=*(FP*)pack;
		ac->fly.pModel->FirstCycle=TRUE;
	}


	_Replay.ResetSecondaryFMValues(ac);						

	UWord	newsector=world.GetSector(ac);
	if (newsector!=oldsector)
	{
		world.RemoveFromSector(ac,oldsector);
		world.AddToWorld(ac);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessMobData
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::ProcessMobData(UByteP pack)
{
	UniqueID id;
	MobileItemPtr item;
	WorldStuff &world = mobileitem::GetWorld();

	pack+=sizeof(ULong); // step over PID

	id=(UniqueID)(*(UWord*)pack);
	pack+=sizeof(UWord);

	item=(MobileItemPtr)Persons2::ConvertPtrUID(id);

#ifndef NDEBUG
	if (!item)
		INT3;
#endif

	if (!item)
		return;

	UWord	oldsector=	world.GetSector(item);

	_Replay.RestorePrimaryMIValues(item,(LPMIPRIMARYVALUES)pack);

	UWord	newsector=world.GetSector(item);
	if (newsector!=oldsector)
	{
		world.RemoveFromSector(item,oldsector);
		world.AddToWorld(item);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendAnimData
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::SendAnimData(ULong type,ULong num, UniqueID id)
{
	ULong packsize;
	UByteP pack,temp;

	packsize=(2*sizeof(ULong)) // num+packet id
			+sizeof(UWord)
			+num*(sizeof(UWord)+sizeof(UByte));

	packsize+=sizeof(UWord); // shape
	pack=new UByte[packsize];
	temp=pack;

	*(ULong*)temp=type;
	temp+=sizeof(ULong);

	*(UWord*)temp=id;
	temp+=sizeof(UWord);

	ItemPtr i=*Persons2::ConvertPtrUID(id);

	MakeAnimPack(num,temp,i->shape);

	SendMessageToGroup((char*)pack,packsize);

	delete [] pack;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendNumAnims
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::SendNumAnims(ULong num,ULong type)
{
	GENERIC c;

	c.PacketID=type;
	c.PlayerID=num;

	SendMessageToGroup((char*)&c,sizeof(GENERIC));

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAllAnims
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
Bool	DPlay::GetAllAnims(ULong type, ULong need, ULong& got)
{
	char* buffer;
	ULong buflen,from;
	ItemPtr item;
	UByteP pack;
	UniqueID id;

	while (ReceiveNextMessageToMe(buffer,buflen,from,DPRECEIVE_TOPLAYER))
	{
		if (from==DPID_SYSMSG)
		{
			ProcessSystemMessage(buffer);
		}
		else if (from!=aggID)
		{
			if (*(ULong*)buffer==type)
			{
				pack=(UByteP)buffer;
				pack+=sizeof(ULong); // step over PID

				id=(UniqueID)(*(UWord*)pack);
				pack+=sizeof(UWord);

				item=(ItemPtr)Persons2::ConvertPtrUID(id);

				if (item) 
					ProcessAnimPack(pack,item);

				got++;

				if (got==need)
					return TRUE;
			}
			else
			{
				ProcessPlayerMessage(buffer,buflen,from);
			}
		}
	}
	if (got==need)
		return TRUE;

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNumAnims
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
Bool	DPlay::GetNumAnims(ULong type,ULong& num)
{
	char* buffer;
	ULong buflen,from;
	LPGENERIC c;

	while (ReceiveNextMessageToMe(buffer,buflen,from,DPRECEIVE_TOPLAYER))
	{
		if (from==DPID_SYSMSG)
		{
			ProcessSystemMessage(buffer);
		}
		else if (from!=aggID)
		{
			c=(LPGENERIC)buffer;

			if (c->PacketID==type)
			{
				num=c->PlayerID;
				return TRUE;
			}
			else
			{
				ProcessPlayerMessage(buffer,buflen,from);
			}
		}
	}

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeAnimPack
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::MakeAnimPack(ULong num,UByteP temp,ShapeNum shape)
{
#ifdef COMMSANIMCHECK
	FILE* fp=fopen("animsend.txt","at");
	fprintf(fp,"num=%d shape=%d\n",num,shape);
	UByteP temp2=temp;
#endif
	UWord deltaoffset;
	UByte newbyte;
	ULong n;

// send shape in case AC has blown up or crashed etc

	*(UWord*)temp=(UWord)shape;
	temp+=sizeof(UWord);

	*(ULong*)temp=num;
	temp+=sizeof(ULong);

	for (n=0; n < num; n++)
	{
		deltaoffset=SHAPE.AnimDeltaList[n].deltaoffset;
		newbyte=SHAPE.AnimDeltaList[n].newbyte;
#ifdef COMMSANIMCHECK
		fprintf(fp,"do=%d val=%d\n",deltaoffset,newbyte);
#endif
		*(UWord*)temp=deltaoffset;
		temp+=sizeof(UWord);
		*temp=newbyte;
		temp+=sizeof(UByte);
	}
#ifdef COMMSANIMCHECK
	if (GameType<COMMSQUICKMISSION)
	{
		CheckAnimPack(temp2);
		ProcessAnimPack(temp2,Persons2::PlayerSeenAC);
	}
	fclose(fp);
#endif
}

void	DPlay::CheckAnimPack(UByteP p)
{
	UWord	deltaoffset;
	UByte	newbyte;
	ULong	num;
	UWord	newshape;
	ULong check=0;
	UByteP datapack=p;

	newshape=*(UWord*)datapack;
	datapack+=sizeof(UWord);

	num=*(ULong*)datapack;
	datapack+=sizeof(ULong);

	while (num--)
	{
		deltaoffset=*(UWord*)datapack;
		datapack+=sizeof(UWord);
		newbyte=*datapack;
		datapack++;

		check+=deltaoffset;

		if (check>159)
			INT3;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessAnimPack
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::ProcessAnimPack(UByteP datapack,ItemPtr item)
{
#ifdef COMMSANIMCHECK
	FILE* fp=fopen("animrec.txt","at");
#endif
	UWord	deltaoffset;
	UByte	newbyte;
	ULong n,num,index=0;

	UByte	pack;

	UWord newshape;

	newshape=*(UWord*)datapack;
	datapack+=sizeof(UWord);

	item->shape=(ShapeNum)newshape;	 

	if (item->Status.size==AirStrucSize)
		pack=((AirStrucPtr)item)->weap.Weapons;
	else
		pack=0;

	num=*(ULong*)datapack;
	datapack+=sizeof(ULong);

#ifdef COMMSANIMCHECK
	fprintf(fp,"num=%d shape=%d\n",num,newshape);
#endif


// need to set up shape anim
// have to do this because item may have changed shape on other m/c and sent anim for that 
// shape, so set up shape before applying anim

// set up shape as well in case AC has exploded etc

	if (SHAPE.ResetAnimData_NewShape(item,(ShapeNum)newshape,pack))
	{
		while (num--)
		{
			deltaoffset=*(UWord*)datapack;
			datapack+=sizeof(UWord);
			newbyte=*datapack;
			datapack++;

			SHAPE.AnimDeltaList[index].deltaoffset=deltaoffset;
			SHAPE.AnimDeltaList[index++].newbyte=newbyte;
#ifdef COMMSANIMCHECK
			fprintf(fp,"do=%d val=%d\n",deltaoffset,newbyte);
#endif
		}

		SHAPE.PatchAnimData(item,index);
	}
	else
	{
#ifndef NDEBUG
		INT3;
#endif
	}
#ifdef COMMSANIMCHECK
	fclose(fp);
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SyncCommsWorld
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
Bool	DPlay::SyncCommsWorld()
{
#ifdef SYNCDATA
	FILE* fp=fopen("resync.txt","at");
#endif
	static ULong timeout;

	if (SyncData.resettime)
	{
#ifdef SYNCDATA
		fprintf(fp,"set up timeout\n");
#endif
		timeout=(timeGetTime()+20000);
		SyncData.resettime=false;
	}

	if (timeGetTime()>timeout || RestartWorldSync)
	{
#ifdef SYNCDATA
		if (RestartWorldSync)
			fprintf(fp,"RestartWorldSync=true\n");
		if (timeGetTime()>timeout)
			fprintf(fp,"timed out\n");

#endif
		if (!RestartWorldSync)
		{
			SendRestartWorldSyncMessage();
#ifdef SYNCDATA
			fprintf(fp,"send RestartWorldSync message\n");
			fflush(fp);
#endif
		}
		SyncData.resettime=true;
		InitSyncData(true);


#ifdef SYNCDATA
		fclose(fp);
#endif
		return FALSE;
	}

	char* buffer;
	ULong	buflen,from,n;
	LPGENERIC p;

/* need all items in world to be the same on all machines after resync. 
Need: AC positions/data/flight models and anims
	   Mobiles positions/data and anims
	   Items anims.

  All AC and mob positions/data needs to be sent apart from players.
  - Players send their own info, host sends all AI info
  For anims, host counts number of anims in each section (AC,mob,item) and sends this
  followed by anim packets.

  //What about if bfields are out of step?
  //Is it possible to send this info whilst game is still going for other players? then just
  //accomodate player in like deathmatch resync?

  //- Need to send host bfield list, compare with one players have and if different do 
  //something about it, i.e. process battlefields  Only need to do this is quick mission/campaign
  -Dont need to do now, bfields are static

  - Does DeadStream need to be transmitted? Probably!!!!!
*/

	static timein=0;

	if (Host)
	{
		if (!SyncData.sentinfo)
		{
			if (!WorldSyncPhaseReady)
			{
				if (!SyncData.wsrneeded)
				{
					SyncData.wsrneeded=ActivePlayers^(1<<mySlot);
#ifdef SYNCDATA
					fprintf(fp,"Host needs %d acks\n",SyncData.wsrneeded);
#endif
				}

				while (ReceiveNextMessageToMe(buffer,buflen,from,DPRECEIVE_TOPLAYER))
				{
					if (from==DPID_SYSMSG)
					{
						ProcessSystemMessage(buffer);
					}
					else if (from!=aggID)
					{
						if (((LPGENERIC)buffer)->PacketID==PID_READYWORLD)
						{
							SyncData.wsrgot+=1<<DPID2Slot(from);
#ifdef SYNCDATA
							fprintf(fp,"got wsr from %d   wsrgot=%d\n",from,SyncData.wsrgot);
#endif
						}
						else
						{
							ProcessPlayerMessage(buffer,buflen,from);
						}
					}
					if (SyncData.wsrgot==SyncData.wsrneeded)
					{
#ifdef SYNCDATA
						fprintf(fp,"got all wsr messages\n");
						break;
#endif
					}
				}

				if (SyncData.wsrgot==SyncData.wsrneeded)
				{
					WorldSyncPhaseReady=true;
					SyncData.wsrgot=0;
				}
			}
			else
			{
#ifdef SYNCDATA
				fprintf(fp,"Sending world.....\n");
#endif
				SendACDetails();
				Sleep(SENDPAUSE);
				SendMobDetails();
				Sleep(SENDPAUSE);
 				SendAAAList();
				Sleep(SENDPAUSE);

// dead item anims and status are sent in dead stream. Alive items will have
// no anim data, so dont need to transmit - its all done by deadstream

				SendDeadStream();
				Sleep(SENDPAUSE);
				SendACArray();
				Sleep(SENDPAUSE);
				SendBackupRandomList(false);

				SyncData.wsmneeded=ActivePlayers^(1<<mySlot);

				SyncData.wsmgot=0;
				SyncData.sentinfo=true;
#ifdef SYNCDATA 
				fprintf(fp,"Finished sending world\n");
#endif
			}
		}
		else
		{
// need all gotworldmessages

			while (ReceiveNextMessageToMe(buffer,buflen,from,DPRECEIVE_TOPLAYER))
			{
				if (from==DPID_SYSMSG)
				{
					ProcessSystemMessage(buffer);
				}
				else if (from!=aggID)
				{
					if (((LPGENERIC)buffer)->PacketID==PID_GOTWORLD)
					{
						SyncData.wsmgot+=1<<DPID2Slot(from);
#ifdef SYNCDATA
						fprintf(fp,"got from %d wsrgpt=%d\n",from,SyncData.wsmgot);
#endif
					}
					else
					{
						ProcessPlayerMessage(buffer,buflen,from);
					}
				}
			}

			if (SyncData.wsmgot==SyncData.wsmneeded)
			{
#ifdef SYNCDATA
				fprintf(fp,"got all wsmgots\n");
				fclose(fp);
#endif
				SyncData.sentinfo=FALSE;
				WorldSyncPhaseReady=false;
				SyncData.resettime=true;
				PlayerSync=false;
				return TRUE;
			}
		}	
	}
	else
	{
		switch (SyncData.stage)
		{
		case 1:
// send an "I'm ready to receive world" packet

			GENERIC p;

			p.PacketID=PID_READYWORLD;

			SendMessageToGroup((char*)&p,sizeof(GENERIC));

			SyncData.stage++;
#ifdef SYNCDATA
			fprintf(fp,"send ready to receive\n");
#endif
			break;

		case 2:
#ifdef SYNCDATA
			fflush(fp);
#endif
			if (GetACDetails())
			{
#ifdef SYNCDATA
				fprintf(fp,"got ac details\n");
#endif
				SyncData.stage++;
			}

			break;
 
		case 3:
#ifdef SYNCDATA
			fflush(fp);
#endif
			if (GetMobDetails())
			{
#ifdef SYNCDATA
				fprintf(fp,"got mob details\n");
#endif
				SyncData.stage++;
			}

			break;

		case 4:
#ifdef SYNCDATA
			fflush(fp);
#endif
 			if (GetAAAList())
			{
#ifdef SYNCDATA
				fprintf(fp,"got aaa list\n");
#endif
				SyncData.stage++;
			}
			break;

		case 5:
#ifdef SYNCDATA
			fflush(fp);
#endif
			if (GetDeadStream())
			{
#ifdef SYNCDATA
				fprintf(fp,"got deadstream\n");
#endif
				SyncData.stage++;
			}
			break;
		case 6:
			if (GetACArray())
			{
				SyncData.stage++;
			}
			break;
		case 7:
			if (GetRandomList())
			{
#ifdef SYNCDATA
				fprintf(fp,"got randlist and finished.....\n");
				fclose(fp);
#endif
				SendGotWorldMessage();
				WorldSyncPhaseReady=false;
				SyncData.stage=1;
				SyncData.resettime=true;
				PlayerSync=false;
				return TRUE;
			}
		}
	}
#ifdef SYNCDATA
	fclose(fp);
#endif
	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendGotWorldMessage
//Date			Thu 12 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::SendGotWorldMessage()
{
	GENERIC p;

	p.PacketID=PID_GOTWORLD;

	SendMessageToGroup((char*)&p,sizeof(GENERIC));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FillHistBuffer
//Date			Mon 23 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::FillHistBuffer(AirStrucPtr ac, ULong slot)
{
	HistPosBuffer[slot].InitBuffer();
	HistPosBuffer[slot].SetTempCurr();
	do 
	{
		HistPosBuffer[slot].GetTemp()->Pos.X=ac->World.X;
		HistPosBuffer[slot].GetTemp()->Pos.Y=ac->World.Y;
		HistPosBuffer[slot].GetTemp()->Pos.Z=ac->World.Z;

		HistPosBuffer[slot].GetTemp()->Heading=ac->hdg;
		HistPosBuffer[slot].GetTemp()->Pitch=ac->pitch;
		HistPosBuffer[slot].GetTemp()->Roll=ac->roll;
		HistPosBuffer[slot].GetTemp()->Velocity=ac->vel_;

		HistPosBuffer[slot].UpdateTemp();
	} 
	while (HistPosBuffer[slot].GetTemp()!=HistPosBuffer[slot].GetCurr());
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OwnerChange
//Date			Fri 27 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::OwnerChange(ULong newownerid,AirStrucPtr AIAC)
{
	UByte b1,b2,b3;
	ULong n=0;

	if (!AIAC->uniqueID.commsmove)
	{
// byte1 and byte2 contain ID of AIAC who wants to change owner
// byte3 contains slot of player who AIAC wants to be owner

		b1=(AIAC->uniqueID.count)>>8;
		b2=(AIAC->uniqueID.count)&0xff;

		if (newownerid==255)
		{
			b3=255;
		}
		else
		{
			b3=n=UID2Slot(newownerid);
		}

	// if player is bad, keep existing one
		
		if (n!=MAXPLAYERS)
		{
			NewSpecial(PIDC_OWNERCHANGE,b1,b2,b3);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessOwnerChange
//Date			Fri 27 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::ProcessOwnerChangePacket(UByteP ptr)
{
	UByte byte1, byte2, byte3;

	byte1=*ptr++;
	byte2=*ptr++;
	byte3=*ptr;

	UniqueID id;
	UniqueID newowner;
	AirStrucPtr AIAC;
	AirStrucPtr CommsAC;

	id=(UniqueID)(((byte1)<<8)+byte2);

	AIAC=(AirStrucPtr)Persons2::ConvertPtrUID(id);

	if (AIAC)
	{
		newowner=(UniqueID)AllocPacket[byte3];

		if (newowner==UID_NULL)
		{
			AIAC->CommsOwner=UID_NULL;
		}
		else
		{
			CommsAC=(AirStrucPtr)Persons2::ConvertPtrUID(newowner);

			if (CommsAC)
			{
				AIAC->CommsOwner=newowner;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitialiseOwners
//Date			Fri 27 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::InitialiseOwners()
{
	AirStrucPtr ac;

	ac=*AirStruc::ACList;

	while (ac)
	{
		ac->CommsOwner=UID_NULL;
		ac=*ac->nextmobile;
	}

// possibly have ac in players flight starting with player as owner otherwise
// AI ac only get owner when they engage in combat with a player or an ac
// that already has a owner, in which case they inherit that owner
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OwnerChangeDecision
//Date			Fri 27 Nov 1998
//------------------------------------------------------------------------------
void	DPlay::OwnerChangeDecision(AirStrucPtr me, AirStrucPtr him)
{
	if (Implemented)							
	{								
		if (!me->CommsOwner && !me->uniqueID.commsmove)
		{
// only change if I dont have an owner

			if (him->uniqueID.commsmove)					
			{												
// engage with player, he becomes owner

				if (him->uniqueID.count!=me->CommsOwner)		
				{											
					OwnerChange(him->uniqueID.count,me);
				}											
			}
			else if (him->CommsOwner && !me->CommsOwner)
			{
// engage with ac with an owner, inherit his owner

				OwnerChange(him->CommsOwner,me);
			}
			else
			{
// an AI AC with no owner, lets just kick ass
			}
		}													
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessBFieldInfo
//Date			Fri 4 Dec 1998
//------------------------------------------------------------------------------
void	DPlay::ProcessBFieldInfo(char* info,ULong& bfctrl,FileNum& filelist)
{
	char* ptr=info;
	ULong n,val;

	ptr += sizeof (ULong);
	bfctrl = *(ULong*)ptr;
	ptr += sizeof (ULong);
	filelist = *(FileNum*)ptr;
	ptr += sizeof (FileNum);

	n = 0;

	for (;;)
	{
		val = *(int*)ptr;
		if (val!=BAD_RV)
		{
			ptr += sizeof (int);

			Persons2::SetLoc (n, val);
			n++;
		}
		else
			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendBFieldsToPlayers
//Date			Fri 4 Dec 1998
//------------------------------------------------------------------------------
void	DPlay::SendBFieldsToPlayers(bool request)
{
	LPGRLIST	temp=_Replay.bfgrlist;
	ULong PackSize,n,MaxPackSize;
	char *pack,*tpack;
	LPREPGRENTRY vals;
	UWord ordernum=0;

	if (!Host)
		return;

	while (temp)
	{
// get packet size

		MaxPackSize=sizeof(ULong); //packet ID
		MaxPackSize+=sizeof(ULong); //battlefieldtype
		MaxPackSize+=sizeof(UWord); // bfield order num
		MaxPackSize+=sizeof(FileNum);

		PackSize=MaxPackSize;

		vals=temp->list;

		while (vals)
		{
			MaxPackSize+=(sizeof(int)*2);
			vals=vals->next;
		}

// construct packet

		pack=new char[MaxPackSize];
		tpack=pack;

		*(ULong*)tpack=PID_BFIELDPACKETIDENT;
		tpack+=sizeof(ULong);

		*(UWord*)tpack=ordernum++;
		tpack+=sizeof(UWord);

		*(ULong*)tpack=temp->bfctrl;
		tpack+=sizeof(ULong);
		*(FileNum*)tpack=temp->file;
		tpack+=sizeof(FileNum);

		vals=temp->list;

		bool finished=false;
		ULong val;
		ULong m;
		ULong t[8];
		UByte set=0;

		while (!finished && vals)
		{
			for (m=0;m<8;m++)
			{
				val=vals->val;
				vals=vals->next;
				t[m]=val;

				if (t[m]!=0)
					set|=0x1<<m;

				if (t[m]==BAD_RV || !vals)
				{
					finished=TRUE;
					break;
				}
			}

			*(UByte*)tpack=set;
			tpack+=sizeof(UByte);
			PackSize+=sizeof(UByte);

			for (m=0;m<8;m++)
			{
				if (set&0x1<<m)
				{
					*(int*)tpack=t[m];
					tpack+=sizeof(int);
					PackSize+=sizeof(int);
				}
			}
			set=0;
		}

		bool sentok=false;

		while (!sentok)
		{
			if (request)
			{
				sentok=SendMessageToPlayer(pack,PackSize,0);
			}
			else
			{
				sentok=SendMessageToGroup(pack,PackSize);
			}
		}

		delete [] pack;
		pack=NULL;

		temp=temp->next;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExitCommsAndReplay3D
//Date			Fri 11 Dec 1998
//------------------------------------------------------------------------------
void	DPlay::ExitCommsAndReplay3D()
{
	if (Implemented)
	{
#ifdef TIMERTIME
		if (timer)
			fclose(timer);
#endif
		H2H_Player[mySlot].status=CPS_DEBRIEF;					
		_Agg.Running=FALSE;
		SendGonePacket();
		ResetCommsGame();
		FlyNowFlag=FALSE;										
		MainSheetCount=2; // send and receive updates

// for comms build a new list each time

		_Replay.DeleteFileAndGlobRefList(_Replay.bfgrlist); 	

		UByte n;
		for (n=0;n<STAGE_MAX;n++)
		{
			CommsStage[n][0]=false;
			CommsStage[n][1]=false;
		}

		if (Host)
			ClearDeadPilots();
	}
	else if (_Replay.Record)
	{
		_Replay.StopRecord(false);
		_Replay.stopforaccel=false;
	}
	else if (_Replay.Playback)
	{
		_Replay.skipOK=false;
		delete [] _Replay.backupsmoke;
		_Replay.backupsmoke=NULL;
		_Replay.tempbackupsmoke=NULL;

		delete [] _Replay.backupcloud;
		_Replay.backupcloud=NULL;
		_Replay.tempbackupcloud=NULL;
	}
	_Replay.ResetReplayData();
	_DPlay.SpookyGhostMode=false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewKillLauncher
//Date			Fri 15 Jan 1999
//------------------------------------------------------------------------------
void	DPlay::NewKillLauncher(UniqueID id)
{
	if (id)
	{
		if (CommsOrReplay())
		{
			NewSpecial(PIDC_KILLLAUNCHER,(UByte)(id>>8),(UByte)(id&0xff));
		}
	}
}

void	DPlay::ProcessKillLauncherPacket(UByteP ptr)
{
	{
		UByte byte1, byte2, byte3;

		byte1=*ptr++;
		byte2=*ptr;

		UniqueID id;
		ULong	fake;
		AirStrucPtr ac;

		fake=byte1<<8;
		fake+=byte2;

		id=(UniqueID)fake;

		ac=(AirStrucPtr)Persons2::ConvertPtrUID(id);

		if (ac)
		{
			Trans_Obj.KillLauncherComms(ac);

			ac->Status.deaded=TRUE;
			ac->Status.deadtime=1;


			SetScore(ac,NULL);

			int slot=UID2Slot(ac->uniqueID.count);
			if (slot<MAXPLAYERS)
			{
				CommsKiller[slot]=255;
			}

		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPlayerMessage
//Date			Mon 8 Feb 1999
//------------------------------------------------------------------------------
char*	DPlay::GetPlayerMessage(ULong index)
{
	ULong n,m;

// index is ([player]*MAXPLAYERS)+[messnum]

	for (n=0;n<MAXPLAYERS;n++)
	{
		for (m=0;m<NUMRADIOMESSAGES;m++)
		{
			if ((n*MAXPLAYERS)+m==index)
				return Messages[n][m];
		}
	}
	return NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPlayerName
//Date			Mon 8 Feb 1999
//------------------------------------------------------------------------------
char*	DPlay::GetPlayerName(ULong	n)
{
	return H2H_Player[n].name;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPlayerNumber
//Date			Mon 22 Mar 1999
//------------------------------------------------------------------------------
ULong	DPlay::GetPlayerNumber(ULong	id)
{
 	ULong n;
 
 	for (n=0;n<MAXPLAYERS;n++)
 	{
 		if (AllocPacket[n]==id)
 			return n;
 	}

	return 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ID2Slot
//Date			Fri 26 Feb 1999
//------------------------------------------------------------------------------
inline ULong DPlay::DPID2Slot(ULong id)
{
	for (ULong n=0;n<MAXPLAYERS;n++)
		if (H2H_Player[n].dpid==id)
			break;

	return n;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UID2Slot
//Date			Thu 17 Jun 1999
//------------------------------------------------------------------------------
inline ULong DPlay::UID2Slot(UWord id)
{
	for (ULong n=0;n<MAXPLAYERS;n++)
		if (AllocPacket[n]==id)
			break;

	return n;
}

ULong DPlay::UID_2Slot(UWord id)
{
	return UID2Slot(id);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeUIDSPacket
//Date			Thu 11 Mar 1999
//------------------------------------------------------------------------------
UByte	DPlay::MakeUIDSPacket(LPBASICPACKET packet, UByte index)
{
	UByteP ptr=&packet->IDCode;
	UWord id1,id2;
	ULong ID;

	id1=UIDSBuffer.GetCurr()->uid1;
	id2=UIDSBuffer.GetCurr()->uid2;

	ptr+=index;
	ID=UIDSBuffer.GetCurr()->IDCode;
	*ptr=ID;
// dont add PT_UID. This is already included in IDCode
//	*ptr+=(UByte)(PT_UIDS<<6);
	*ptr+=(UByte)(id1&0x0f);
	ptr++;
	*ptr=(UByte)((id1>>4)&0xff);
	ptr++;
	*ptr=(UByte)((id1>>12)&0x03);
	*ptr+=(UByte)((id2&0x3f)<<2);
	ptr++;
	*ptr=(UByte)(id2>>6);

	UIDSBuffer.UpdateCurr();

	while (UIDSBuffer.GetCurr()->IDCode==PIDC_DONTSEND && UIDSBuffer.GetCurr()!=UIDSBuffer.GetNext())
		UIDSBuffer.UpdateCurr();

	return (PacketLength(ID));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessUIDSPacket
//Date			Thu 11 Mar 1999
//------------------------------------------------------------------------------
UByte	DPlay::ProcessUIDSPacket(UByteP ptr, ULong slot)
{
	UniqueID id1,id2;
	UByte size=0;

	GetUIDSFromPacket(id1,id2,ptr);

	switch (*ptr&0xf0)
	{
	case PIDC_WINGMANCOMMAND:
		size=ProcessWingmanCommand(id1,id2,slot);
		break;

	default:
#ifndef NDEBUG
		INT3;
#endif
		break;
	}

	return size;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewUIDSPacket
//Date			Thu 11 Mar 1999
//------------------------------------------------------------------------------
void	DPlay::NewUIDSPacket(UniqueID id1,UniqueID id2,UByte code)
{
	if (CommsOrReplay())
	{
		if(UIDSBuffer.NumEntries()>=BufferSize)
		{	
			UIDSBuffer.UpdateCurr();

			while (UIDSBuffer.GetCurr()->IDCode==PIDC_DONTSEND && UIDSBuffer.GetCurr()!=UIDSBuffer.GetNext())
				UIDSBuffer.UpdateCurr();
		}
		 
		UIDSBuffer.GetNext()->uid1=id1;
		UIDSBuffer.GetNext()->uid2=id2;
		UIDSBuffer.GetNext()->IDCode=code;

		UIDSBuffer.AddEntryAndUpdateNext();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetUIDSFromPacket
//Date			Fri 12 Mar 1999
//------------------------------------------------------------------------------
void	DPlay::GetUIDSFromPacket(UniqueID& id1, UniqueID& id2,UByteP ptr)
{
	UByte IDCode, byte1, byte2, byte3;

	IDCode=*ptr++;
	byte1=*ptr++;
	byte2=*ptr++;
	byte3=*ptr;

	UWord uid1,uid2;

	uid1=IDCode&0x0f;
	uid1+=byte1<<4;
	uid1+=((byte2&0x03)<<12);

	uid2=(byte2>>2)&0x3f;
	uid2+=byte3<<6;

	id1=(UniqueID)uid1;
	id2=(UniqueID)uid2;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitSyncData
//Date			Thu 18 Mar 1999
//------------------------------------------------------------------------------
void	DPlay::InitSyncData(bool startup)
{
#ifdef SYNCDATA 
	FILE* fp=fopen("resync.txt","at");
	fprintf(fp,"InitSyncData startup=%d\n",startup);
	fclose(fp);
#endif
	SyncData.resettime=true;
	SyncData.sentinfo=false;
	SyncData.wsmneeded=0;
	SyncData.wsmgot=0;
	SyncData.stage=1;
	SyncData.wsrneeded=0;
	if (startup)
		SyncData.wsrgot=0;
	RestartWorldSync=false;

	SyncData.itemstage=0;
	SyncData.mobstage=0;
	SyncData.acstage=0;
	SyncData.deadstage=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcVels
//Date			Fri 19 Mar 1999
//------------------------------------------------------------------------------
void	DPlay::CalcVels(UByte slot,UByte pframe)
{
	if (_DPlay.Implemented)
	{
// use comms historical buffer!

		UByte hframe;
		SWord num;
		AirStrucPtr ac=(AirStrucPtr)Persons2::ConvertPtrUID((UniqueID)AllocPacket[slot]);

		if (ac==Persons2::PlayerSeenAC)
			ac=Persons2::PlayerGhostAC;

// go back 2, this is last frame and previous frame. If this is the begining of the buffer then
// the previous frame will be the starting position		

		HistPosBuffer[slot].SetTempNext();
		HistPosBuffer[slot].TempPrev();
		HistPosBuffer[slot].TempPrev();

// get past any aiaipos packets

		while (!(HistPosBuffer[slot].GetTemp()->deltas.IDCode<PIDC_AIACPOSITION1))
		{
			HistPosBuffer[slot].TempPrev();
		}

// get number of frames between current frame and last frame in historical buffer

		hframe=HistPosBuffer[slot].GetTemp()->Frame;

		if (pframe>hframe)
		{
			num=pframe-hframe;
		}
		else
		{
			num=(pframe-hframe)+256;
		}

// multiply number of frames difference by rate divider to get number of
// move frame between positions

// if the number of frames is greater than the number required for accuracy
// i.e. 4, then work out vels, if not then track back if possible a number 
// of frames (should only need to go back 1 in theory) to get 4 move frames
// difference. If we cant track back (because its the start of the buffer) then
// tough, have to use what we've got

		UByte tvel=velcounter;

		while (num<POSBSIZE-1)
		{
			if (--tvel!=0)
			{
				HistPosBuffer[slot].TempPrev();
				if (!(HistPosBuffer[slot].GetTemp()->deltas.IDCode<PIDC_AIACPOSITION1))
				{
// aiacpos packet at start of buffer? Use what weve got already

					HistPosBuffer[slot].UpdateTemp();
					break;
				}
				num++;
			}
			else
				break;
		}

// dodgy catch all 

		if (!num)
			num=1;

		num*=RateDivider;

// calculate vels

		COORDS3D c=HistPosBuffer[slot].GetTemp()->Pos;

		HistPosBuffer[slot].SetTempNext();
		HistPosBuffer[slot].TempPrev();

		COORDS3D thisac=HistPosBuffer[slot].GetTemp()->Pos;

		ac->vel_x = 10000 * (thisac.X - c.X) / (num * Timer_Code.FRAMETIME);
		ac->vel_y = 10000 * (thisac.Y - c.Y) / (num * Timer_Code.FRAMETIME);
		ac->vel_z = 10000 * (thisac.Z - c.Z) / (num * Timer_Code.FRAMETIME);

	}
	else
	{
// use replay buffer!

		Persons2::PlayerGhostAC->vel_x = ((*_Replay.PosBuffer.GetNext()).X-(*_Replay.PosBuffer.GetCurr()).X);
		Persons2::PlayerGhostAC->vel_y = ((*_Replay.PosBuffer.GetNext()).Y-(*_Replay.PosBuffer.GetCurr()).Y);
		Persons2::PlayerGhostAC->vel_z = ((*_Replay.PosBuffer.GetNext()).Z-(*_Replay.PosBuffer.GetCurr()).Z);
		
		FP temp = 10000 / ((POSBSIZE-1) * Timer_Code.FRAMETIME);	  

		Persons2::PlayerGhostAC->vel_x *= temp;
		Persons2::PlayerGhostAC->vel_y *= temp;
		Persons2::PlayerGhostAC->vel_z *= temp;

		SLong wx, wy, wz;												
		MMC.Sky.GetWind(Persons2::PlayerGhostAC->World.Y, wx, wy, wz);	
		Persons2::PlayerGhostAC->vel_x -= wx;							
		Persons2::PlayerGhostAC->vel_y -= wy;							
		Persons2::PlayerGhostAC->vel_z -= wz;							

		_Replay.PosBuffer.UpdateCurr();
		_Replay.PosBuffer.AddEntryAndUpdateNext();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewPlayerMessage
//Date			Mon 22 Mar 1999
//------------------------------------------------------------------------------
void	DPlay::NewPlayerMessage(UByte message)
{
	NewSpecial(PIDC_PLAYERMESSAGE,message,(UByte)MsgRecipientAll);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessPlayerMessage
//Date			Mon 22 Mar 1999
//------------------------------------------------------------------------------
void	DPlay::ProcessPlayerMessagePacket(UByteP ptr, ULong slot)
{
	UByte byte1, byte2;

	byte1=*ptr++;
	byte2=*ptr;

	ItemPtr i=(ItemPtr)Persons2::ConvertPtrUID((UniqueID)AllocPacket[slot]);

// message to everybody or I am on this guys team

	if (byte2 || H2H_Player[mySlot].MyTeam==H2H_Player[slot].MyTeam)
		DisplayPlayerMessage(i,NULL,ST_PLAYERMESSAGE,byte1);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DisplayPlayerMessage
//Date			Mon 22 Mar 1999
//------------------------------------------------------------------------------
void	DPlay::DisplayPlayerMessage(ItemPtr victim, ItemPtr hitterItem, UByte script_type,UByte messnum)//DAW 22Jun99
{
	if (H2H_Player[mySlot].status!=CPS_3D) // no messages unless in 3d
		return;

	if (hitterItem && hitterItem->Status.size!=AIRSTRUCSIZE)
		return;

	MsgType msg=MsgType(MSG_PLAYERKILLED|MSG_HIPRIORITY_X);

	AirStrucPtr hitter=*hitterItem;

	switch (script_type)
	{
	case ST_PLAYERKILLEDCOMMS:
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PLAYERKILLEDCOMMS,msg,hitter,victim,Persons2::PlayerSeenAC));
		break;

	case ST_PLAYERKILLEDPLAYER:
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PLAYERKILLEDPLAYER,msg,hitter,victim,Persons2::PlayerSeenAC));
		break;

	case ST_PLAYERKILLEDFRIENDLY:
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PLAYERKILLEDFRIENDLY,msg,hitter,victim,Persons2::PlayerSeenAC));
		break;

	case ST_PLAYERKILLEDENEMY:
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PLAYERKILLEDPLAYERENEMY,msg,hitter,victim,Persons2::PlayerSeenAC));
		break;

	case ST_PLAYERLEFTGAME:
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PLAYERLEFTGAME,msg,hitter,victim,Persons2::PlayerSeenAC));
		break;

	case ST_PLAYERJOINEDGAME:
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PLAYERJOINEDGAME,msg,hitter,victim,Persons2::PlayerSeenAC));
		break;

	case ST_PLAYERJOINING:
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PLAYERJOINING,msg,hitter,victim,Persons2::PlayerSeenAC));
		break;

	case ST_PLAYERMESSAGE:
 		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLER_USER_MESSAGE,msg,(MobileItemPtr)victim,NULL,Persons2::PlayerSeenAC,TARGET_INDEXES(messnum)));
		break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateHistBuffer
//Date			Tue 23 Mar 1999
//------------------------------------------------------------------------------
void	DPlay::UpdateHistBuffer(LPACPACKET p,ULong slot)
{
	UByte shift;
	SLong val;

	AddPacketToHistBuffer(p,slot);

	while (HistPosBuffer[slot].GetNext()->OK)
	{
		HistPosBuffer[slot].SetTempNext();
		HistPosBuffer[slot].TempPrev();

		HistPosBuffer[slot].GetNext()->Pos.X=HistPosBuffer[slot].GetTemp()->Pos.X;
		HistPosBuffer[slot].GetNext()->Pos.Y=HistPosBuffer[slot].GetTemp()->Pos.Y;
		HistPosBuffer[slot].GetNext()->Pos.Z=HistPosBuffer[slot].GetTemp()->Pos.Z;
		HistPosBuffer[slot].GetNext()->Heading.a=HistPosBuffer[slot].GetTemp()->Heading.a;
		HistPosBuffer[slot].GetNext()->Pitch.a=HistPosBuffer[slot].GetTemp()->Pitch.a;
		HistPosBuffer[slot].GetNext()->Roll.a=HistPosBuffer[slot].GetTemp()->Roll.a;
		HistPosBuffer[slot].GetNext()->Velocity=HistPosBuffer[slot].GetTemp()->Velocity;

// pidc_initpack is from startup sequence, no prediction occured. Can still apply the packets
// as deltas because all deltas wil be zero

		if (HistPosBuffer[slot].GetNext()->deltas.IDCode!=PIDC_INITPACK)
			PredictGoodMovement(slot);

// dont add deltas for aiacpos packets!

		if (HistPosBuffer[slot].GetNext()->deltas.IDCode<PIDC_AIACPOSITION1)
		{
			shift=HistPosBuffer[slot].GetNext()->deltas.Shift;

			val=GetVal(HistPosBuffer[slot].GetNext()->deltas.X,shift);
			HistPosBuffer[slot].GetNext()->Pos.X+=val;

			val=GetVal(HistPosBuffer[slot].GetNext()->deltas.Y,shift);
			HistPosBuffer[slot].GetNext()->Pos.Y+=val;

			val=GetVal(HistPosBuffer[slot].GetNext()->deltas.Z,shift);
			HistPosBuffer[slot].GetNext()->Pos.Z+=val;

			val=GetVal(HistPosBuffer[slot].GetNext()->deltas.Heading,shift);
			HistPosBuffer[slot].GetNext()->Heading.a+=val;

			val=GetVal(HistPosBuffer[slot].GetNext()->deltas.Pitch,shift);
			HistPosBuffer[slot].GetNext()->Pitch.a+=val;

			val=GetVal(HistPosBuffer[slot].GetNext()->deltas.Roll,shift);
			HistPosBuffer[slot].GetNext()->Roll.a+=val;

			val=GetVal(HistPosBuffer[slot].GetNext()->deltas.Velocity_,shift);
			SLong newvel=abs(val)<<_Replay.velshifttest;		
			if (val<0)											
				newvel=-newvel;								
			
			HistPosBuffer[slot].GetNext()->Velocity+=newvel;
		}


// update ghost and players each frame so that order of prediction and 
// delta application does not matter. Otherwise might get deltas, predict,deltas
// on one machine and predict,deltas,deltas on another which would mean a 
// slight difference of position on the 2 machines. This way always have
// predict, deltas, predict, deltas etc. Automatically deals with recalculating
// from resend of missing packets.

		HistPosBuffer[slot].GetNext()->OK=false;
		HistPosBuffer[slot].UpdateNext();
	}

 	CheckGhost();

// Could do this every X frames so that stutter is not so bad all the time...
// Could also move the aircraft not all the way to correct position but an
// amount based on frame time so that no large jumps occur but it is prodded
// into the right position?

	if (FrameCount&(25/RateDivider))
	{
		AirStrucPtr AC=*Persons2::ConvertPtrUID((UniqueID)AllocPacket[slot]);

 		if (AC==Persons2::PlayerSeenAC)
			AC=Persons2::PlayerGhostAC;

		{
			if (AC==Persons2::PlayerGhostAC)
				AddDeltas(Persons2::PlayerGhostAC,TRUE,4);

			HistPosBuffer[slot].SetTempNext();
			HistPosBuffer[slot].TempPrev();

			UWord	oldsector=	MobileItem::currworld->GetSector(AC);

			AC->World.X=HistPosBuffer[slot].GetTemp()->Pos.X;
			AC->World.Y=HistPosBuffer[slot].GetTemp()->Pos.Y;
			AC->World.Z=HistPosBuffer[slot].GetTemp()->Pos.Z;
			AC->hdg.a=HistPosBuffer[slot].GetTemp()->Heading.a;
			AC->pitch.a=HistPosBuffer[slot].GetTemp()->Pitch.a;
			AC->fly.cpitch.a=AC->pitch.a;
			AC->roll.a=HistPosBuffer[slot].GetTemp()->Roll.a;
			AC->vel_=HistPosBuffer[slot].GetTemp()->Velocity;

		// as packets can arrive late, need to predict forward number of frames between
		// packet put into histbuffer and current frame

			int num=FrameCount-p->Count;

			if (num<-128)
				num+=256; // probably a late packet, predict forward
			else
				num=0;	// looks like a machine is slightly behind, dont predict forward loads!

			num+=(RateDivider-1);
			if (num<0)
				num=0;

			for (int i=0;i<num;i++)
				PredictMove(AC);

			UWord	newsector=	MobileItem::currworld->GetSector(AC);
			if (newsector!=oldsector && AC!=Persons2::PlayerGhostAC)
			{
				MobileItem::currworld->RemoveFromSector(AC,oldsector);
				MobileItem::currworld->AddToWorld(AC);
			}

			if (AC==Persons2::PlayerGhostAC)
				AddDeltas(Persons2::PlayerGhostAC,FALSE,4);

 			BackupGhost();
		}
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddPacketToHistBuffer
//Date			Tue 23 Mar 1999
//------------------------------------------------------------------------------
void	DPlay::AddPacketToHistBuffer(LPACPACKET p,ULong slot)
{
	SWord diff,sub;
	SWord	thispacketcount;
	SWord	targetcount;

	HistPosBuffer[slot].SetTempNext();
	HistPosBuffer[slot].TempPrev();

	targetcount=HistPosBuffer[slot].GetTemp()->Frame;
	thispacketcount=p->Count;

	sub=thispacketcount-targetcount;

	if (((thispacketcount>=targetcount && sub<128)
	|| (thispacketcount<targetcount && abs(sub)>128)))
	{
		if (thispacketcount>=targetcount)
			diff=sub;
		else
			diff=(sub)+256;

		while (diff--)
			HistPosBuffer[slot].UpdateTemp();

		CopyMemory(&HistPosBuffer[slot].GetTemp()->deltas,p,sizeof(ACPACKET));
		HistPosBuffer[slot].GetTemp()->OK=true;
		HistPosBuffer[slot].GetTemp()->Frame=p->Count;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessEjectMessage
//Date			Wed 21 Apr 1999
//------------------------------------------------------------------------------
void	DPlay::ProcessEjectPacket(AirStrucPtr AC)
{
	Trans_Obj.LaunchCanopyEject(AC,*mobileitem::currworld);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessGuestLeavingMessage
//Date			Fri 23 Apr 1999
//------------------------------------------------------------------------------
void	DPlay::ProcessGuestLeavingMessage(ULong id)
{
	ProcessPlayerGone(id,TRUE);	 

// if a player leaves whilst a sync is in process need to start again without him
// force a resync anyway because packet sent saying player is out could be out of sync

// hmmm, not entirely sure this is necessary....

	if (Host && H2H_Player[mySlot].status==CPS_3D)
	{
		if (GameType>TEAMPLAY)
		{
			Initiator=TRUE;
			BeginSyncPhase();
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewShapePacket
//Date			Wed 21 Apr 1999
//------------------------------------------------------------------------------
void	DPlay::NewShapePacket(UWord	id, UWord	shape)
{
	UByte b1,b2,b3;

	b1=id&0xff;
	b2=(id>>8)&0x3f;
	b2+=(shape>>2)&0xc0;
	b3=shape&0xff;

#ifndef NDEBUG
	UWord uid;
	UWord oldshape;
	UWord newshape;

	ItemPtr i=(ItemPtr)Persons2::ConvertPtrUID((UniqueID)id);
	oldshape=i->shape;

	uid=b1;
	uid+=(b2&0x3f)<<8;

	newshape=b3+((b2&0xc0)<<2);
	SHAPE.ReplayAnimData_NewShape(uid,newshape);
	SHAPE.ReplayAnimData_NewShape(uid,oldshape);
#endif

	NewSpecial(PIDC_SHAPECHANGE,b1,b2,b3);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessNewShapePacket
//Date			Wed 21 Apr 1999
//------------------------------------------------------------------------------
void	DPlay::ProcessNewShapePacket(UByteP ptr)
{
	UByte byte1, byte2, byte3;

	byte1=*ptr++;
	byte2=*ptr++;
	byte3=*ptr;

	UWord uid,shape;

	uid=byte1;
	uid+=(byte2&0x3f)<<8;

	shape=byte3+((byte2&0xc0)<<2);

	SHAPE.ReplayAnimData_NewShape(uid,shape);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessResyncPacket
//Date			Thu 29 Apr 1999
//------------------------------------------------------------------------------
void	DPlay::ProcessResyncPacket(LPACSTATEPACKET packet, ULong n)
{
	AirStrucPtr AC;

	resyncsgot|=(1<<n);

	AC=(AirStruc*)Persons2::ConvertPtrUID((UniqueID)AllocPacket[n]);

	if (AC)
	{
		if (!PlayerSync || !Host)
		{
// get state data

			WorldStuff &world = mobileitem::GetWorld();
			UWord	oldsector=	world.GetSector(AC);

			AC->World.X=packet->Pos.X;
			AC->World.Y=packet->Pos.Y;
			AC->World.Z=packet->Pos.Z;

			AC->hdg.a=packet->Heading.a;
			AC->pitch.a=packet->Pitch.a;
			AC->roll.a=packet->Roll.a;
			AC->vel_=packet->Velocity;	
			AC->fly.cpitch=AC->pitch;

			UWord	newsector=world.GetSector(AC);
			if (newsector!=oldsector)
			{
				world.RemoveFromSector(AC,oldsector);
				world.AddToWorld(AC);
			}

			if (packet->alive)
			{
				AC->Status.deadtime=0;
				AC->Status.deaded=FALSE;
			}
			else
			{
				deadplayers|=1<<n;
				AC->Status.deaded=TRUE;
				AC->Status.deadtime=1;
			}

			if (packet->resurrect)
			{
				RepairAircraft(AC);
				AC->Status.deaded=FALSE;
			}

			if (packet->joining)
				joiningplayerslot=n;

	// extract anim data
			UByteP	datapack;

			datapack=(UByte*)packet;
			datapack+=sizeof(ACSTATEPACKET);

	// if packet is from host then set timeofday

			if (n==0)
			{
				_Replay.inst->timeofday=*(int*)datapack;
			}
			datapack+=sizeof(int);

			ProcessAnimPack(datapack,(ItemPtr)AC);

			MinAnimData* mad = (MinAnimData* )AC->Anim;			

			if (packet->alive)
				mad->itemstate = ALIVE;

			mad->IsInvisible=0;
		}

		(H2H_Player+n)->kills=packet->MyKills;
		(H2H_Player+n)->assists=packet->MyAssists;
		(H2H_Player+n)->deaths=packet->MyDeaths;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendRestartWorldSyncMessage
//Date			Thu 29 Apr 1999
//------------------------------------------------------------------------------
void	DPlay::SendRestartWorldSyncMessage()
{
	GENERIC p;

	p.PacketID=PID_RESTARTWORLDSYNC;

	SendMessageToGroup((char*)&p,sizeof(GENERIC));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendDeadStream
//Date			Thu 29 Apr 1999
//------------------------------------------------------------------------------
void	DPlay::SendDeadStream()
{
// traverse deadstream finding number of blocks.
// Send number of blocks with olddaytime, 
// followed by block themseleves!

	DeadStream::DeadBlock* block=NULL;
	WorldStuff &world = mobileitem::GetWorld();
	int	temptime;
	ULong num=0;

	DeadStream tempdead;

	tempdead.firstblock=NULL;
	tempdead.SetWorldDead(&world);

	block=tempdead.firstblock;
	temptime=tempdead.olddaytime;

	while (block)
	{
		num++;
		block=block->nextblock;
	}

	GENERIC p;

	p.PacketID=PID_NUMDEADBLOCKS;
	p.PlayerID=num;
	p.Slot=tempdead.olddaytime;

	Sleep(SENDPAUSE);
	SendMessageToGroup((char*)&p,sizeof(GENERIC));
	Sleep(SENDPAUSE);

	block=tempdead.firstblock;

	while (block)
	{
		UByteP pack,temp;
		ULong packsize;

		packsize=sizeof(ULong) // packetid
				+sizeof(UWord) // SGT
				+sizeof(UWord) // dataused
				+(sizeof(UByte)*block->dataused); // data

		pack=new UByte[packsize];
		temp=pack;

		*(ULong*)temp=PID_DEADBLOCKDATA;
		temp+=sizeof(ULong);

		*(UWord*)temp=block->SGT;
		temp+=sizeof(UWord);

		*(UWord*)temp=block->dataused;
		temp+=sizeof(UWord);

		CopyMemory(temp,block->data,block->dataused);

		SendMessageToGroup((char*)pack,packsize);

		delete [] pack;

		block=block->nextblock;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDeadStream
//Date			Thu 29 Apr 1999
//------------------------------------------------------------------------------
bool	DPlay::GetDeadStream()
{
	static ULong need;
	static ULong got;

	switch (SyncData.deadstage)
	{
	case 0:
		int dtime;
		if (GetNumDeadBlocks(need,dtime))
		{
			Dead_Stream.ClrWorldDead();
			Dead_Stream.olddaytime=dtime;
			SyncData.deadstage++;
			got=0;
		}
		break;
	case 1:
		if (need!=0)
		{
			if (!GetAllDeadBlocks(need,got))
			{
#ifdef SYNCDATA
#ifdef DETAILS
				FILE* fp=fopen("resync.txt","at");
				fprintf(fp,"DB: need %d got %d\n",need,got);
				fclose(fp);
#endif
#endif
				break;
			}
		}
		WorldStuff &world = mobileitem::GetWorld();
		Dead_Stream.GetWorldDead(&world);
		SyncData.deadstage=0;
		return true;
	}

	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNumDeadBlocks
//Date			Thu 29 Apr 1999
//------------------------------------------------------------------------------
bool	DPlay::GetNumDeadBlocks(ULong& num,int& dtime)
{
	char* buffer;
	ULong	buflen,from;
	LPGENERIC c;

	while (ReceiveNextMessageToMe(buffer,buflen,from,DPRECEIVE_TOPLAYER))
	{
		if (from==DPID_SYSMSG)
		{
			ProcessSystemMessage(buffer);
		}
		else if (from!=aggID)
		{
			c=(LPGENERIC)buffer;

			if (c->PacketID==PID_NUMDEADBLOCKS)
			{
				num=c->PlayerID;
				dtime=c->Slot;

				return true;
			}
			else
			{
				ProcessPlayerMessage(buffer,buflen,from);
			}
		}
	}
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAllDeadBlocks
//Date			Thu 29 Apr 1999
//------------------------------------------------------------------------------
bool	DPlay::GetAllDeadBlocks(ULong need,ULong& got)
{
	char* buffer;
	ULong buflen,from;
	UByteP pack;

	while (ReceiveNextMessageToMe(buffer,buflen,from,DPRECEIVE_TOPLAYER))
	{
		if (from==DPID_SYSMSG)
		{
			ProcessSystemMessage(buffer);
		}
		else if (from!=aggID)
		{
			if (*(ULong*)buffer==PID_DEADBLOCKDATA)
			{
				pack=(UByteP)buffer;
				pack+=sizeof(ULong);

				DeadStream::DeadBlock* block=new DeadStream::DeadBlock;

				UWord fake=(UWord)*(UWord*)pack;
				block->SGT=(UniqueID)fake;
				pack+=sizeof(UWord);

				block->dataused=(UWord)*(UWord*)pack;
				pack+=sizeof(UWord);

				CopyMemory(&block->data,pack,block->dataused);

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

				got++;

				if (got==need)
					return TRUE;
			}
			else
			{
				ProcessPlayerMessage(buffer,buflen,from);
			}
		}
	}
	if (got==need)
		return true;

	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendPilotsStatus
//Date			Thu 6 May 1999
//------------------------------------------------------------------------------
void	DPlay::SendPilotsStatus(bool single,ULong reqfrom,int sqnum, UByte pos)
{
	if (single)
	{
// when I die send pilot status update

		GENERIC p;

		p.PacketID=PID_SINGLEPILOTSTATUS;
		p.PlayerID=sqnum;
		p.Slot=pos;

		SendMessageToGroup((char*)&p,sizeof(GENERIC));
	}
	else
	{
// when a player joins game send all pilots status


		LPDEADPILOT tempdp=deadpilotlist;
		ULong packlen=4; // PID_ALLPILOTSSTATUS

// get packet size;

		while (tempdp)
		{
			packlen+=(sizeof(int)+sizeof(UByte));
			tempdp=tempdp->next;
		}

		UByteP	pack=new UByte[packlen];
		UByteP	temp=pack;

		*(ULong*)temp=PID_ALLPILOTSSTATUS;
		temp+=sizeof(ULong);

		tempdp=deadpilotlist;
		while (tempdp)
		{
			*(int*)temp=tempdp->squadron;
			temp+=sizeof(int);
			*(UByte*)temp=tempdp->position;
			temp+=sizeof(UByte);
			tempdp=tempdp->next;
		}

		if (reqfrom)
			SendMessageToPlayer((char*)pack,packlen,reqfrom);
		else
			SendMessageToGroup((char*)pack,packlen);

		delete [] pack;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPilotsStatus
//Date			Thu 6 May 1999
//------------------------------------------------------------------------------
bool	DPlay::GetPilotsStatus()
{
	char* Buffer;
	ULong	BufferLen=0;
	bool	Got=false;
	ULong From;

	ULong now=timeGetTime();
	CommsTimeout time(now,CommsTimeoutLength);

	while(!Got)
	{
		now=timeGetTime();

		if (time.TimedOut(now))
			return false;
		
		if (ReceiveNextMessageToMe(Buffer,BufferLen,From,0))
		{
			if (From==DPID_SYSMSG)
			{
				ProcessSystemMessage(Buffer);
			}
			else if (BufferLen!=sizeof(AGGSENDPACKET))
			{
				if (*(ULong*)Buffer==PID_ALLPILOTSSTATUS)
				{
					ProcessPilotStatusPacket(false,(UByte*)Buffer,BufferLen);
					Got=true;
				}
			}
		}
	}

	return Got;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessPilotStatusPacket
//Date			Thu 6 May 1999
//------------------------------------------------------------------------------
void	DPlay::ProcessPilotStatusPacket(bool single,UByteP p,int size)
{
	ULong n;
	UByteP temp=p;
	LPGENERIC c;			

	if (single)
	{
		c=(LPGENERIC)p;

		int sqnum=c->PlayerID;
		UByte pos=c->Slot;

		NewDeadPilot(sqnum,pos);

	}
	else
	{
		size-=4; 
		p+=sizeof(ULong);

		int sq;
		UByte pos;

		ClearDeadPilots();

		while (size)
		{
			sq=*(int*)p;
			p+=sizeof(int);
			size-=sizeof(int);
			pos=*(UByteP)p;
			p+=sizeof(UByte);
			size-=sizeof(UByte);

			LPDEADPILOT temp=new DEADPILOT;

			temp->next=deadpilotlist;
			temp->position=pos;
			temp->squadron=sq;

			deadpilotlist=temp;
			temp=NULL;
		}
	}

	if (H2H_Player[mySlot].status==CPS_FRAG)
		UpdateFrag=TRUE;
}

void	DPlay::SendAccelGearUpMessage()
{
	NewSpecial(PIDC_ACCELGEARUP);
}

void	DPlay::ProcessAccelGearUpPacket()
{
	mobileitem::ResetACGears();					
	AircraftAnimData*	adptr;
	AirStrucPtr ac=Persons2::PlayerSeenAC;
	SHAPE.NavigationLightsActive(ac,FALSE);
	adptr = (AircraftAnimData*) ac->Anim;
	if (adptr)
	{
		adptr->acleglowerl = 255;
		adptr->acleglowerr = 255;
		adptr->acleglowerf = 255;
		adptr->acleglowerb = 255;
		adptr->animtoggle = 1;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewWPMessage
//Date			Thu 10 Jun 1999
//------------------------------------------------------------------------------
void	DPlay::NewWPMessage(UniqueID wp)
{
	UByte b1,b2;

	b1=wp&0xff;
	b2=(wp>>8)&0xff;

	NewSpecial(PIDC_NEWWP,b1,b2);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessNewWPMessage
//Date			Thu 10 Jun 1999
//------------------------------------------------------------------------------
void	DPlay::ProcessNewWPPacket(UByteP ptr, AirStrucPtr AC)
{
	UByte byte1, byte2;

	byte1=*ptr++;
	byte2=*ptr;

	UWord newwp;

	newwp=byte1+(byte2<<8);

	WayPointPtr i=(WayPointPtr)Persons2::ConvertPtrUID((UniqueID)newwp);	

	if (i)
	{
		AC->waypoint=i;

		if (AC==Persons2::PlayerSeenAC)
			Persons2::PlayerGhostAC->waypoint=i;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SendAAAList
//Date			Wed 16 Jun 1999
//------------------------------------------------------------------------------
void	DPlay::SendAAAList()
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

	skipsize=Three_Dee.livelist->ArchiveLiveList(aaa,num,0);
	num2=skipsize;

	assert(num==num2);

	ULong packsize=sizeof(ULong)	// PID
					+sizeof(UWord)	// num
					+(num*sizeof(UWord));		// data
	
    UByteP pack=new UByte[packsize];
	UByteP temp=pack;

	*(ULong*)temp=PID_AAAPACKET;
	temp+=sizeof(ULong);
	*(UWord*)temp=num;
	temp+=sizeof(UWord);

	while (num2--)
	{
		*(UWord*)temp=aaa[num2],sizeof(UWord);
		temp+=sizeof(UWord);
	}

	SendMessageToGroup((char*)pack,packsize);

 	Three_Dee.livelist->RestoreSleepList();
	Three_Dee.livelist->ApplyLiveList(aaa,num);

	delete [] aaa;
	delete [] pack;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAAAList
//Date			Wed 16 Jun 1999
//------------------------------------------------------------------------------
bool	DPlay::GetAAAList()
{
	char* buffer;
	ULong	buflen,from;

	while (ReceiveNextMessageToMe(buffer,buflen,from,DPRECEIVE_TOPLAYER))
	{
		if (from==DPID_SYSMSG)
		{
			ProcessSystemMessage(buffer);
		}
		else if (from!=aggID)
		{
			if (*(ULong*)buffer==PID_AAAPACKET)
			{
				ProcessAAAPacket(buffer);
				return true;
			}
			else 
			{
				ProcessPlayerMessage(buffer,buflen,from);
			}
		}
	}
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessAAAPacket
//Date			Thu 17 Jun 1999
//------------------------------------------------------------------------------
void	DPlay::ProcessAAAPacket(char* packet)
{
	packet+=sizeof(ULong); // get past PID

	UWord num=*(UWord*)packet; // get number of elements
	packet+=sizeof(UWord); 

	UWordP aaa=new UWord[num];

	UWord num2=num;

	while (num2--)
	{
		aaa[num2]=*(UWord*)packet;
		packet+=sizeof(UWord);
	}

	Three_Dee.livelist->RestoreSleepList();
	Three_Dee.livelist->ApplyLiveList(aaa,num);

	delete [] aaa;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRandomList
//Date			Fri 18 Jun 1999
//------------------------------------------------------------------------------
bool	DPlay::GetRandomList()
{
	char* buffer;
	ULong	buflen,from;

	while (ReceiveNextMessageToMe(buffer,buflen,from,DPRECEIVE_TOPLAYER))
	{
		if (from==DPID_SYSMSG)
		{
			ProcessSystemMessage(buffer);
		}
		else if (from!=aggID)
		{
			if (*(ULong*)buffer==PID_RANDOMLIST)
			{
				Process_PM_RandomList(buffer);
				return true;
			}
			else 
			{
				ProcessPlayerMessage(buffer,buflen,from);
			}
		}
	}
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetCommsSurfaces
//Date			Mon 28 Jun 1999
//Description	Reset gear,brakes and flaps after comms resurrect
//------------------------------------------------------------------------------
void	DPlay::ResetCommsSurfaces()
{
	AirStrucPtr ac=Persons2::PlayerSeenAC;
	AircraftAnimData*	adptr;

	if (ac->fly.pModel)
		ac->fly.pModel->ResetGearPos(false);

	SHAPE.NavigationLightsActive(ac,FALSE);

	adptr = (AircraftAnimData*) ac->Anim;
	if (adptr)
	{
		adptr->acleglowerl = 255;
		adptr->acleglowerr = 255;
		adptr->acleglowerf = 255;
		adptr->acleglowerb = 255;
		adptr->animtoggle = 1;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ProcessExtraPacket
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	DPlay::ProcessExtraPacket(LPACPACKET packet, AirStrucPtr ac, ULong slot)
{
	UByte RecCode=PIDC_DUMMYPACKET;
	UByte len=0,size;
	UByteP ptr;

	MoveSurfacesToZero();

	while (RecCode!=PIDC_EMPTY)
	{
		ptr=(UByteP)&packet->IDCode;
		ptr+=len;

		RecCode=*ptr;

		switch (RecCode>>6)
		{
		case PT_COLLISION:
			size=ProcessCollisionPacket(ptr, ac, slot);
			break;

		case PT_UIDS:
			size=ProcessUIDSPacket(ptr, slot);
			break;

		case PT_SPECIAL:
			if (*ptr>=PIDC_AIACPOSITION1)
			{
				switch (*ptr)
				{
				case PIDC_AIACPOSITION1:
					Process1stAIACPositionPacket(packet,slot);
					break;
				case PIDC_AIACPOSITION2:
					Process2ndAIACPositionPacket(packet,slot);
					break;
				}
				size=PacketLength(*ptr);
			}
			else
			{
				size=ProcessSpecialPacket(ptr, ac, slot);
			}
			break;

		case PT_BULLET:
			size=ProcessBulletPacket(ptr, ac);
			break;
		}

		len+=size;

#ifndef NDEBUG
		if (len>EXTRASIZE)
			INT3;
#endif
		if (len>=EXTRASIZE)
			break;
	}

	if (packet->Bull)
	{
		ProcessSpecialBulletPacket(ac);
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    MakeControlSurfacePacket
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	DPlay::MakeControlSurfacePacket(LPBASICPACKET packet)
{
	packet->IDCode=PIDC_SECONDARYAERODEVICES;

	PMODEL p=Persons2::PlayerSeenAC->fly.pModel;
	AirStrucPtr sac=Persons2::PlayerSeenAC;

#ifndef NDEBUG
	if (p->Elevator>32767 || p->Elevator<-32767)
		INT3;
	if (p->Aileron>32767 || p->Aileron<-32767)
		INT3;
	if (p->Rudder>32767 || p->Rudder<-32767)
		INT3;
#endif

// elevator, aileron and rudder are 16bit signed values (SWord)
// sign bit is cleared and rest stored in bottom 7 bits of extra bytes 1-3
// sign bit is then reapplied to extra bytes highest bit.

// elevator - byte1
// aileron - byte2
// rudder - byte3

// values should be taken from the airstruc values NOT the flight model values for
// animation purposes. This is important as the values are different, the model values
// being a lot less than the airstruc values.

	SWord	e,a,r;

	e=sac->fly.elevator;
	a=sac->fly.aileron;
	r=sac->fly.rudder;

	packet->byte1=((abs(e)>>8)&127);
	packet->byte2=((abs(a)>>8)&127);
	packet->byte3=((abs(r)>>8)&127);

	if (e<0) packet->byte1+=128;
	if (a<0) packet->byte2+=128;
	if (r<0) packet->byte3+=128;

//extra bytes 4 and 5 are split between values. Each gets top 5 bits of lowest byte. 1 spare.

// Elevator - top 5 bits of byte4
// Aileron - bottom 3 bits of byte4 and top 2 bits of byte5
// Rudder - bottom 5 bits of byte5

	UByte e1,a1,r1;

	e1=(abs(e)&0xf8)>>3;
	a1=(abs(a)&0xf8)>>3;
	r1=(abs(r)&0xf8)>>3;

	packet->byte4=e1<<3;
	packet->byte4+=(a1>>2);

	packet->byte5=(a1&0x3)<<6;
	packet->byte5+=r1;


}

//////////////////////////////////////////////////////////////////////
//
// Function:    ProcessControlSurfacePacket
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	DPlay::ProcessControlSurfacePacket(UByteP ptr)
{
	if (_Replay.Playback)
	{
		PMODEL p=Persons2::PlayerSeenAC->fly.pModel;

		int b1,b2,b3;
		bool neg_e=false,neg_a=false,neg_r=false;
		UByte e1,a1,r1;

		b1=((*ptr)&127)<<8;
		if ((*ptr++)&128) neg_e=true;
		
		b2=((*ptr)&127)<<8;
		if ((*ptr++)&128) neg_a=true;

		b3=((*ptr)&127)<<8;
		if ((*ptr++)&128) neg_r=true;

// dont need to shift elevator value as it has already been done to fit into
// top 5 bits if byte. It is the actual value we want!

		e1=(*ptr)&0xf8;

		a1=((*ptr++)&0x07)<<2;
		a1+=((*ptr)>>6);

// need to shift aileron value

		a1<<=3;

// shift rudder value

		r1=(*ptr)<<3;

		b1+=e1;
		b2+=a1;
		b3+=r1;

// apply sign 

		if (neg_e) b1=-b1;
		if (neg_a) b2=-b2;
		if (neg_r) b3=-b3;

// might as well bung values into both flight model and airstruc. The airstruc values
// are the important ones in terms of animations, which is all we are interested in for
// playback.

		p->Elevator=b1;
		p->Aileron=b2;
		p->Rudder=b3;

		Persons2::PlayerSeenAC->fly.elevator=p->Elevator;
		Persons2::PlayerSeenAC->fly.aileron=p->Aileron;
		Persons2::PlayerSeenAC->fly.rudder=p->Rudder;

	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    MakeSpecialBulletPacket
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	DPlay::MakeSpecialBulletPacket(LPBASICPACKET packet)
{
// squeeze info into 4 spare bits in shiftfactor

	while (BulletBuffer.NumEntries())
	{
		bool recent=false;
		bool bullet=false;

		ULong fl=BulletBuffer.GetCurr()->framelaunched;

		if (_DPlay.Implemented)
		{
			ULong fps=(100/Timer_Code.FRAMETIME)/RateDivider;
			SLong age=FrameCount-BulletBuffer.GetCurr()->framelaunched;

			if (!(age>fps || (FrameCount<fl && (abs(age)<(256-fps)))))
				recent=true;
		}
		else
		{
			if (!_Replay.replayframecount-fl>(100/Timer_Code.FRAMETIME))
				recent=true;
		}

		if (recent)
		{
			packet->Bull=1;
			bullet=true;
		}
		BulletBuffer.UpdateCurr();

		if (bullet)
			break;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    PacketLength
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
UByte	DPlay::PacketLength(ULong ID)
{
// size include IDCode

	UByte size=0;
	switch (ID)
	{
	case PIDC_DONTSEND:
		size=0;
		break;

	case PIDC_ENGINEANIM:
	case PIDC_BULLET:
	case PIDC_RESURRECTEND:
	case PIDC_RESURRECT:
	case PIDC_PACKETERROR:
	case PIDC_INITPACK:
	case PIDC_DUMMYPACKET:
	case PIDC_EMPTY:
	case PIDC_EJECT:
	case PIDC_ACCELGEARUP:
// size include IDCode
		size=1;
		break;

	case PIDC_ENGINERPM:
	case PIDC_DEATHMOVEEFFECT:
// size include IDCode
		size=2;
		break;

	case PIDC_KILLLAUNCHER:
	case PIDC_AERODEVICE:
	case PIDC_PLAYERMESSAGE:
	case PIDC_NEARMISS:
	case PIDC_NEWWP:
// size include IDCode
		size=3;
		break;

	case PIDC_LANDEDEFFECT:
	case PIDC_UIDPACKET:
	case PIDC_WINGMANCOMMAND:
	case PIDC_OWNERCHANGE:
	case PIDC_SHAPECHANGE:
// size include IDCode
		size=4;
		break;

	case PIDC_COLLISION:
	case PIDC_AIACPOSITION1:
  	case PIDC_AIACPOSITION2:
	case PIDC_SECONDARYAERODEVICES:
// size include IDCode
		size=EXTRASIZE;
		break;

	default:
#ifndef NDEBUG
		INT3;
#endif
		break;

	}
	return size;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ProcessResurrectPacket
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void DPlay::ProcessResurrectPacket(AirStrucPtr AC)
{
	if (Implemented && AC!=Persons2::PlayerSeenAC)
	{
 // stop collisions occurring aginst AC whilst in resurrect

		AC->movecode=AUTO_RESURRECT;

		RepairAircraft(AC);
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ProcessResurrectEndPacket
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void DPlay::ProcessResurrectEndPacket(AirStrucPtr AC)
{
	if (Implemented)
	{
		AC->ai.radiosilent=FALSE;

		if (AC!=Persons2::PlayerSeenAC)
		{
// allow collisions 

			AC->movecode=AUTO_FOLLOWWP;

			RepairAircraft (AC);
		}

// I am now officially not dead (undeaded????)

		AC->Status.deaded=FALSE;
		AC->Status.deadtime=0;										

		ResetDeadPlayers(AC);

		if (AC==Persons2::PlayerSeenAC)
		{
			_Miles.ResetSoundFlags();
			ResetCommsSurfaces();
			resurrectend=false;
		}

		if (AC != Persons2::PlayerSeenAC)				
		{
			SHAPE.NavigationLightsActive(AC,FALSE);

			AircraftAnimData*	adptr;
			adptr = (AircraftAnimData*) AC->Anim;
			adptr->acleglowerl = 255;
			adptr->acleglowerr = 255;
			adptr->acleglowerf = 255;
			adptr->acleglowerb = 255;
			adptr->animtoggle = 1;

			AC->fly.pModel->ResetGearPos(false);			
		}
		else
			AC->fly.pModel->ResetGearPos(true);				
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ProcessLandedEffectPacket
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void DPlay::ProcessLandedEffectPacket(UByteP ptr, AirStrucPtr AC)
{
	UByte byte1, byte2, byte3;

	byte1=*ptr++;
	byte2=*ptr++;
	byte3=*ptr;

	if (!_Replay.Record)
	{
		SLong effect;

		effect=byte1<<8;
		effect+=byte2;

		if (AC==Persons2::PlayerSeenAC)
		{
// if in comms dont playback my crashes

			if (!Implemented) // i.e. playback
			{
// this can cause ac position to change so need to keep track of deltas - not in playback

				Trans_Obj.DummyLandedEffect(AC,effect,byte3);		
			}
			else
			{
				if (GameType<COMMSQUICKMISSION)
				{
					Persons2::PlayerGhostAC->movecode=AUTO_NOPPILOT;
					AC->movecode=AUTO_NOPPILOT; // start resurrection in comms
					Manual_Pilot.controlmode=ManualPilot::PILOTDEAD;
				}
				else
				{
					Art_Int.BreakOff(AC);
				}
			}
		}
		else
		{
// other ac that is not dead, do an effect?

			Trans_Obj.KillLauncherComms(AC);
		}

		if (_DPlay.Implemented)
		{
			SetScore(AC,NULL);

			UByte dead=UID2Slot(AC->uniqueID.count);

			if (dead<MAXPLAYERS)
			{
				if (CommsKiller[dead]!=255)
				{
					(H2H_Player+CommsKiller[dead])->assists++;
					CommsKiller[dead]=255;
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ProcessAeroDevicePacket
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void DPlay::ProcessAeroDevicePacket(UByteP ptr, AirStrucPtr AC)
{
	if (_Replay.Playback || AC!=Persons2::PlayerSeenAC)
	{
		UByte dev=*ptr++;
		SWord Att=((*ptr++)<<8)+*ptr;
		AC->fly.pModel->ProcessAeroPacket(AC, dev,Att);
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ProcessDeathMoveEffectPacket
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void DPlay::ProcessDeathMoveEffectPacket(UByteP ptr)
{
	UByte byte1=*ptr;

	if (_Replay.Playback)			
	{								
		_Replay.ReplayDeathMode = (RDEATH)byte1;
	}		
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ProcessSpecialBulletPacket
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void DPlay::ProcessSpecialBulletPacket(AirStrucPtr ac)
{
	if (!((CommsOrReplay()) && ac==Persons2::PlayerSeenAC))
	{
		WeapAnimData* weap1;
		WeapAnimData* weap2;
		UWord	shape,MuzDel;
		ULong	MuzVel;
		SLong	xpos,ypos,zpos;
		UByte	ltype;
		ItemPtr item;
		WorldStuff &world = mobileitem::GetWorld();
		int index1,index2;

	// launch bullet from first gun

		switch (ac->classtype->planetext)
		{
		case PT_SPIT_A:
		case PT_SPIT_B:
		case PT_HURR_A:
		case PT_HURR_B:
			index1=0;
			index2=1;
			break;
		case PT_ME109:
			index1=2;
			index2=-1;
			break;
		case PT_ME110:
			index1=1;
			index2=-1;
			break;
		case PT_JU87:
			index1=1;
			index2=2;
			break;
		}

		item=(ItemPtr)ac; 

		Trans_Obj.ClearWeaponChain((mobileitem*)item);

		weap1=SHAPE.DirectWeaponLauncher(item,index1,shape,xpos,ypos,zpos,MuzVel,MuzDel,ltype);
		if (weap1)
			Trans_Obj.LaunchWeapon(true,(AirStrucPtr)item,weap1,index1,xpos,ypos,zpos,world,MuzVel,MuzDel);

		if (index2>=0)
		{
			weap2=SHAPE.DirectWeaponLauncher(item,index2,shape,xpos,ypos,zpos,MuzVel,MuzDel,ltype);
			if (weap2)
				Trans_Obj.LaunchWeapon(true,(AirStrucPtr)item,weap2,index2,xpos,ypos,zpos,world,MuzVel,MuzDel);
		}
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    MakeEmptyPacket
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void DPlay::MakeEmptyPacket(LPBASICPACKET packet, UByte index)
{
	UByteP ptr=&packet->IDCode;

	ptr+=index;

	*ptr=PIDC_EMPTY;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ClearDeadPlayersPackets
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void DPlay::ClearDeadPlayersPackets(UByte slot)
{
// remove bullets from dead player
// remove wingman commands from dead player

// remove all dead players updates of waypoints, ejects, aerodev updates
// remove all damage to dead player
// remove kill launchers directed at player

	UWord UID=AllocPacket[slot];

	if (slot==mySlot)
	{
// I am dead, remove all my bullet packets, waypoint changes, ejects, aerodev packets

		BulletBuffer.InitBuffer();

		SpecBuffer.SetTempCurr();

		while (SpecBuffer.GetTemp()!=SpecBuffer.GetNext())
		{
			ULong ThisID=SpecBuffer.GetTemp()->IDCode;

			switch (ThisID)
			{
			case PIDC_NEWWP:
			case PIDC_EJECT:
			case PIDC_AERODEVICE:
			case PIDC_NEARMISS:
			case PIDC_LANDEDEFFECT:
			case PIDC_DEATHMOVEEFFECT:
			case PIDC_OWNERCHANGE:
			case PIDC_KILLLAUNCHER:
			case PIDC_PLAYERMESSAGE:
			case PIDC_SHAPECHANGE:
			case PIDC_ENGINERPM:
			case PIDC_ENGINEANIM:
				SpecBuffer.GetTemp()->IDCode=PIDC_DONTSEND;
				break;
			}

			SpecBuffer.UpdateTemp();
		}

		while (SpecBuffer.GetCurr()->IDCode==PIDC_DONTSEND && SpecBuffer.GetCurr()!=SpecBuffer.GetNext())
			SpecBuffer.UpdateCurr();

// radio messages in buffer? Ideally these would have been sent before player was killed,
// so maybe they should still be sent, even though other AC would think they are coming
// from a dead player. Dunno. Have to test further and see what consequences are.

		UIDSBuffer.SetTempCurr();

		while (UIDSBuffer.GetTemp()!=UIDSBuffer.GetNext())
		{
			ULong ThisID=UIDSBuffer.GetTemp()->IDCode;

			switch (ThisID)
			{
			case PIDC_WINGMANCOMMAND:
				UIDSBuffer.GetTemp()->IDCode=PIDC_DONTSEND;
				break;
			}

			UIDSBuffer.UpdateTemp();
		}

		while (UIDSBuffer.GetCurr()->IDCode==PIDC_DONTSEND && UIDSBuffer.GetCurr()!=UIDSBuffer.GetNext())
			UIDSBuffer.UpdateCurr();
	}
	else
	{
		SpecBuffer.SetTempCurr();

		while (SpecBuffer.GetTemp()!=SpecBuffer.GetNext())
		{
			ULong ThisID=SpecBuffer.GetTemp()->IDCode;

			switch (ThisID)
			{
			case PIDC_KILLLAUNCHER:
				if ((SpecBuffer.GetTemp()->spec1<<8)+SpecBuffer.GetTemp()->spec2==UID)
					SpecBuffer.GetTemp()->IDCode=PIDC_DONTSEND;
				break;
			}

			SpecBuffer.UpdateTemp();
		}

		while (SpecBuffer.GetCurr()->IDCode==PIDC_DONTSEND && SpecBuffer.GetCurr()!=SpecBuffer.GetNext())
			SpecBuffer.UpdateCurr();
	}

// all players remove damage to dead player

	CollBuffer.SetTempCurr();

	while (CollBuffer.GetTemp()!=CollBuffer.GetNext())
	{
		if (CollBuffer.GetTemp()->id==UID)
			CollBuffer.GetTemp()->IDCode=PIDC_DONTSEND;

		CollBuffer.UpdateTemp();
	}

	while (CollBuffer.GetCurr()->IDCode==PIDC_DONTSEND && CollBuffer.GetCurr()!=CollBuffer.GetNext())
		CollBuffer.UpdateCurr();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExpandAggPacket
//Date			Wed 22 Sep 1999
//------------------------------------------------------------------------------
void DPlay::ExpandAggPacket(LPAGGSENDPACKET dest, LPAGGSENDPACKET src)
{
	ULong n;
	UByteP ptr;

	dest->Count=src->Count;
	dest->PlayersInPacket=src->PlayersInPacket;

	ptr=(UByte*)(&src->player[0]);

	for (n=0;n<MAXPLAYERS;n++)
	{
		if (src->PlayersInPacket&1<<n)
		{
			CopyMemory(&dest->player[n], ptr, sizeof(ACPACKET));
			ptr+=sizeof(ACPACKET);
		}
		else
		{
			dest->player[n].IDCode=PIDC_PACKETERROR;
			dest->player[n].byte1=PIDC_PACKETERROR;
			dest->player[n].byte2=PIDC_PACKETERROR;
			dest->player[n].byte3=PIDC_PACKETERROR;
			dest->player[n].byte4=PIDC_PACKETERROR;
			dest->player[n].byte5=PIDC_PACKETERROR;
		}
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    CommsOrReplay
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
inline bool DPlay::CommsOrReplay()
{
	if (Implemented || _Replay.Record)
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    MoveSurfacesToZero
// Date:		12/10/99
// Author:		
//
//Description: Move all control surfaces slowly back to zero(default)
//
//////////////////////////////////////////////////////////////////////
void DPlay::MoveSurfacesToZero()
{
	if (_Replay.Playback)
	{
		PMODEL p=Persons2::PlayerSeenAC->fly.pModel;

		MoveSurfaceToZero(p->Elevator);
		MoveSurfaceToZero(p->Aileron);
		MoveSurfaceToZero(p->Rudder);

		Persons2::PlayerSeenAC->fly.elevator=p->Elevator;
		Persons2::PlayerSeenAC->fly.aileron=p->Aileron;
		Persons2::PlayerSeenAC->fly.rudder=p->Rudder;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    MoveSurfaceToZero
// Date:		28/10/99
//
//Description: Move individual control surface back to zero (default)
//
//////////////////////////////////////////////////////////////////////
void DPlay::MoveSurfaceToZero(int& surface)
{
	if (surface>0)
	{
		surface-=2048;

		if (surface<0)
			surface=0;
	}
	else if (surface<0)
	{
		surface+=2048;

		if (surface>0)
			surface=0;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    AttempToProcessExtraPacket
// Date:		12/10/99
// Author:		
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void DPlay::AttemptToProcessExtraPacket()
{
	bool	gotfullpacket;
	ULong n,m;

#ifdef FILELOGS
	FILE* fp=fopen("aggpack.txt","at");
#endif

	gotfullpacket=true;

	while (gotfullpacket)
	{
		m=0;
		gotfullpacket=false;

		for (n=0;n<MAXPLAYERS;n++)
		{
			if (ActivePlayers&(1<<n))
			{
				if (PacketBuffer.GetCurr()->Received[n])
				{
					m+=1<<n;
				}
			}
		}

#ifdef P_A_CHECK
		FILE* op=fopen("pacheck.txt","at");
		fprintf(op,"Attempt to process %d\n",PacketBuffer.GetCurr()->Count);
#endif
		if (m==ActivePlayers)
		{
			gotfullpacket=true;

// OK, I have received this packet from all players, but need to know if all players 
// have	ACK'ed it so I know that all other players have received all packets for this frame.
// Examine PlayerAggCheck to see what has been acked!

// even check my own acks to ensure they have gone through system correctly

// need to search through aggregator packets for all occurences of this packet number, then
// check to see if all players have acked the relevant packet, and only then can we process
// the packet.

// to maintain the buffer of aggregated packets, set a when a packet is processed saying that 
// this particular packet number has been processed, and only when all packets in an 
// aggregated packet have been processed can we update it.


		}
#ifdef P_A_CHECK
		fclose(op);
#endif

		if (gotfullpacket)
		{
// this is the last frame in which everybody has received the aggregated packet

// can update histposbuffer

			for (n=0;n<MAXPLAYERS;n++)
				HistPosBuffer[n].UpdateCurr();

// number of entries so far updated in buffer for vels purposes

			if (velcounter<POSBSIZE)
				velcounter++;

// now that everybody has got all packets from this frame we can process
// collisions, near misses etc.
#ifdef FILELOGS
		 	fflush(fp);
#endif
			for (n=0;n<MAXPLAYERS;n++)
			{
				if (ActivePlayers&(1<<n))
				{
					ProcessExtraPacket(&(PacketBuffer.GetCurr()->PlayerData[n]),n);
				}
// indicate no packet for this slot

				PacketBuffer.GetCurr()->PlayerData[n].IDCode=PIDC_PACKETERROR;
				PacketBuffer.GetCurr()->Received[n]=FALSE;
			}

// update current packet to process pointer

// this is used to add 1 entry before updating curr, because the way that packets are
// put into the buffer the count of actual packets in it is impossible to keep.

			PacketBuffer.AddEntry(); 

#ifdef FILELOGS
			fprintf(fp,"update packetbuffer.curr %d\n",PacketBuffer.GetCurr()->Count);
#endif

			UByte x;

			x=PacketBuffer.GetCurr()->Count;
			PacketBuffer.UpdateCurr();
			PacketBuffer.GetCurr()->Count=x+1;

		}
	}
#ifdef FILELOGS
	fprintf(fp,"\n");
	fclose(fp);
#endif
}

void DPlay::CheckForResend()
{
// resend on 1/4 and 1/2 length of buffer if needed
// a packet can be resent in between every other frame. This is so
// that the bandwidth is not exceeded because of many resent packets

	ULong num=SendPackBuffer.NumEntries(),n=0;

	clearbuffertime++;

	if (clearbuffertime==((RateDivider*2)-(RateDivider/2)))
	{
		clearbuffertime=0;

		SendPackBuffer.SetTempCurr();

		do
		{
			if (((num-n)>BufferSize/4 && SendPackBuffer.GetTemp()->ResendStatus==0)
			|| ((num-n)>BufferSize/2 && SendPackBuffer.GetTemp()->ResendStatus<2))
			{

				if (!(SendPackBuffer.GetTemp()->Done))
				{
#ifdef FILELOGS
					FILE* fp=fopen("sendpack.txt","at");
					fprintf(fp,"RESEND %d\n",SendPackBuffer.GetTemp()->packet.Count);
					fclose(fp);
#endif				

					SendPacketToAggregator (&(SendPackBuffer.GetTemp()->packet));
					SendPackBuffer.GetTemp()->ResendStatus++;

// have resent a packet this frame, quit because only allowed to sent one per frame max,
// incase bandwidth gets exceeded

					break;
				}
			}

// check to make sure that there are still a number of real packets in the buffer etc

			if ((num-n)<1)
				break;

			n++;
			SendPackBuffer.UpdateTemp();
		}
		while (SendPackBuffer.GetTemp()!=SendPackBuffer.GetCurr());
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BackupGhost
//Date			Tue 30 Nov 1999
//------------------------------------------------------------------------------
void	DPlay::BackupGhost()
{
#ifndef NDEBUG
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BackupSeen
//Date			Tue 30 Nov 1999
//------------------------------------------------------------------------------
void	DPlay::BackupSeen()
{
#ifndef NDEBUG
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckGhost
//Date			Tue 30 Nov 1999
//------------------------------------------------------------------------------
void	DPlay::CheckGhost()
{
#ifndef NDEBUG
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckSeen
//Date			Tue 30 Nov 1999
//------------------------------------------------------------------------------
void	DPlay::CheckSeen()
{
#ifndef NDEBUG
#endif
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateBomberGhost
//Date			Wed 19 Apr 2000
//Description	Updates the movement and AI info so that Heavy Bomber followers 
//				will still work when the leader is occupied by the player
//------------------------------------------------------------------------------
void DPlay::UpdateBomberGhost()
{
	Persons2::PlayerGhostAC->hdg		=		Persons2::PlayerSeenAC->hdg;		//CSB 19/04/00
	Persons2::PlayerGhostAC->pitch		=		Persons2::PlayerSeenAC->pitch;		//CSB 19/04/00
	Persons2::PlayerGhostAC->roll		=		Persons2::PlayerSeenAC->roll;		//CSB 19/04/00
	Persons2::PlayerGhostAC->World.X	=		Persons2::PlayerSeenAC->World.X;	//CSB 19/04/00
	Persons2::PlayerGhostAC->World.Y	=		Persons2::PlayerSeenAC->World.Y;	//CSB 19/04/00
	Persons2::PlayerGhostAC->World.Z	=		Persons2::PlayerSeenAC->World.Z;	//CSB 19/04/00
	Persons2::PlayerGhostAC->vel_		=		Persons2::PlayerSeenAC->vel_;		//CSB 19/04/00
	Persons2::PlayerGhostAC->vel_x		=		Persons2::PlayerSeenAC->vel_x;		//CSB 19/04/00
	Persons2::PlayerGhostAC->vel_y		=		Persons2::PlayerSeenAC->vel_y;		//CSB 19/04/00
	Persons2::PlayerGhostAC->vel_z		=		Persons2::PlayerSeenAC->vel_z;		//CSB 19/04/00
	Persons2::PlayerGhostAC->waypoint	=		Persons2::PlayerSeenAC->waypoint;	//CSB 20/04/00
	Persons2::PlayerGhostAC->movecode	<<=		Persons2::PlayerSeenAC->movecode;	//CSB 20/04/00
	Persons2::PlayerGhostAC->information<<=		Persons2::PlayerSeenAC->information;//CSB 20/04/00
	Persons2::PlayerGhostAC->formation  =		Persons2::PlayerSeenAC->formation;	//CSB 18Jul00
	Persons2::PlayerGhostAC->manoeuvretime=		Persons2::PlayerSeenAC->manoeuvretime;//CSB 07/06/00
	Persons2::PlayerGhostAC->formpos	=		Persons2::PlayerSeenAC->formpos;	//CSB 14Sep00

	Persons2::PlayerGhostAC->leader			=	Persons2::PlayerSeenAC->leader;		//CSB 19/04/00
	Persons2::PlayerGhostAC->follower		=	Persons2::PlayerSeenAC->follower;	//CSB 19/04/00
	Persons2::PlayerGhostAC->fly.nextflight =	Persons2::PlayerSeenAC->fly.nextflight;	//CSB 19/04/00
	Persons2::PlayerGhostAC->fly.leadflight	=	Persons2::PlayerSeenAC->fly.leadflight;	//CSB 19/04/00
	Persons2::PlayerGhostAC->fly.expandedsag=	Persons2::PlayerSeenAC->fly.expandedsag;//CSB 19/04/00
	
	Persons2::PlayerGhostAC->ai.unfriendly			=	Persons2::PlayerSeenAC->ai.unfriendly;		//CSB 19/04/00
	for(int i = 0; i < 4; i++)
	Persons2::PlayerGhostAC->ai.spottedunfriendly[i]=	Persons2::PlayerSeenAC->ai.spottedunfriendly[i];//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.attacker			=	Persons2::PlayerSeenAC->ai.attacker;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.combatskill			=	Persons2::PlayerSeenAC->ai.combatskill;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.ManStep				<<=	Persons2::PlayerSeenAC->ai.ManStep;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.manoeuvre			<<=	Persons2::PlayerSeenAC->ai.manoeuvre;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.radiosilent			<<=	Persons2::PlayerSeenAC->ai.radiosilent;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.simpleacm			<<=	Persons2::PlayerSeenAC->ai.simpleacm;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.beenseen			<<=	Persons2::PlayerSeenAC->ai.beenseen;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.pilotnum			<<=	Persons2::PlayerSeenAC->ai.pilotnum;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.morale				=	Persons2::PlayerSeenAC->ai.morale;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.moraleinc			=	Persons2::PlayerSeenAC->ai.moraleinc;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.threatlevel			=	Persons2::PlayerSeenAC->ai.threatlevel;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.aggressionlevel		=	Persons2::PlayerSeenAC->ai.aggressionlevel;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.firsttactic			=	Persons2::PlayerSeenAC->ai.firsttactic;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.elementtactics		=	Persons2::PlayerSeenAC->ai.elementtactics;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.flighttactics		=	Persons2::PlayerSeenAC->ai.flighttactics;		//CSB 19/04/00
	Persons2::PlayerGhostAC->ai.squadrontactics		=	Persons2::PlayerSeenAC->ai.squadrontactics;		//CSB 19/04/00
}																					//CSB 19/04/00


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateBomberSeen
//Date			Thu 1 Jun 2000
//Description	Updates the movement and AI info so that Heavy Bomber followers 
//				will still work when the player is not the leader
//------------------------------------------------------------------------------
void DPlay::UpdateBomberSeen()
{
	Persons2::PlayerSeenAC->hdg			=		Persons2::PlayerGhostAC->hdg;		//CSB 01/06/00
	Persons2::PlayerSeenAC->pitch		=		Persons2::PlayerGhostAC->pitch;		//CSB 01/06/00
	Persons2::PlayerSeenAC->roll		=		Persons2::PlayerGhostAC->roll;		//CSB 01/06/00
	Persons2::PlayerSeenAC->World.X		=		Persons2::PlayerGhostAC->World.X;	//CSB 01/06/00
	Persons2::PlayerSeenAC->World.Y		=		Persons2::PlayerGhostAC->World.Y;	//CSB 01/06/00
	Persons2::PlayerSeenAC->World.Z		=		Persons2::PlayerGhostAC->World.Z;	//CSB 01/06/00
	Persons2::PlayerSeenAC->vel_		=		Persons2::PlayerGhostAC->vel_;		//CSB 01/06/00
	Persons2::PlayerSeenAC->vel_x		=		Persons2::PlayerGhostAC->vel_x;		//CSB 01/06/00
	Persons2::PlayerSeenAC->vel_y		=		Persons2::PlayerGhostAC->vel_y;		//CSB 01/06/00
	Persons2::PlayerSeenAC->vel_z		=		Persons2::PlayerGhostAC->vel_z;		//CSB 01/06/00
	Persons2::PlayerSeenAC->waypoint	=		Persons2::PlayerGhostAC->waypoint;	//CSB 01/06/00
	Persons2::PlayerSeenAC->movecode	<<=		Persons2::PlayerGhostAC->movecode;	//CSB 01/06/00
	Persons2::PlayerSeenAC->information	<<=		Persons2::PlayerGhostAC->information;//CSB 01/06/00
	Persons2::PlayerSeenAC->formation	=		Persons2::PlayerGhostAC->formation;	//CSB 18Jul00
	Persons2::PlayerSeenAC->manoeuvretime=		Persons2::PlayerGhostAC->manoeuvretime;//CSB 07/06/00
	Persons2::PlayerSeenAC->formpos		=		Persons2::PlayerGhostAC->formpos;	//CSB 14Sep00

	Persons2::PlayerSeenAC->leader			=	Persons2::PlayerGhostAC->leader;			//CSB 01/06/00
	Persons2::PlayerSeenAC->follower		=	Persons2::PlayerGhostAC->follower;			//CSB 01/06/00
	Persons2::PlayerSeenAC->fly.nextflight	=	Persons2::PlayerGhostAC->fly.nextflight;	//CSB 01/06/00
	Persons2::PlayerSeenAC->fly.leadflight	=	Persons2::PlayerGhostAC->fly.leadflight;	//CSB 01/06/00
	Persons2::PlayerSeenAC->fly.expandedsag	=	Persons2::PlayerGhostAC->fly.expandedsag;	//CSB 01/06/00
	
	Persons2::PlayerSeenAC->ai.unfriendly			=	Persons2::PlayerGhostAC->ai.unfriendly;			//CSB 01/06/00
	for(int i = 0; i < 4; i++)
	Persons2::PlayerSeenAC->ai.spottedunfriendly[i]	=	Persons2::PlayerGhostAC->ai.spottedunfriendly[i];//CSB 19/04/00
	Persons2::PlayerSeenAC->ai.attacker				=	Persons2::PlayerGhostAC->ai.attacker;		//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.combatskill			=	Persons2::PlayerGhostAC->ai.combatskill;	//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.ManStep				<<=	Persons2::PlayerGhostAC->ai.ManStep;		//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.manoeuvre			<<=	Persons2::PlayerGhostAC->ai.manoeuvre;		//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.radiosilent			<<=	Persons2::PlayerGhostAC->ai.radiosilent;	//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.simpleacm			<<=	Persons2::PlayerGhostAC->ai.simpleacm;		//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.beenseen				<<=	Persons2::PlayerGhostAC->ai.beenseen;		//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.pilotnum				<<=	Persons2::PlayerGhostAC->ai.pilotnum;		//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.morale				=	Persons2::PlayerGhostAC->ai.morale;			//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.moraleinc			=	Persons2::PlayerGhostAC->ai.moraleinc;		//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.threatlevel			=	Persons2::PlayerGhostAC->ai.threatlevel;	//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.aggressionlevel		=	Persons2::PlayerGhostAC->ai.aggressionlevel;//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.firsttactic			=	Persons2::PlayerGhostAC->ai.firsttactic;	//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.elementtactics		=	Persons2::PlayerGhostAC->ai.elementtactics;	//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.flighttactics		=	Persons2::PlayerGhostAC->ai.flighttactics;	//CSB 01/06/00
	Persons2::PlayerSeenAC->ai.squadrontactics		=	Persons2::PlayerGhostAC->ai.squadrontactics;//CSB 01/06/00
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ApplyPartialDeltas
//Date			Tue 30 Nov 1999
//------------------------------------------------------------------------------
void	DPlay::ApplyPartialDeltas()
{
	ULong n;

	for (n=0;n<MAXPLAYERS;n++)
	{
		if (ActivePlayers & 1<<n)
		{
			if (n!=mySlot)
			{
				AirStrucPtr AC=*Persons2::ConvertPtrUID((UniqueID)AllocPacket[n]);

				if (AC)
				{
					UWord	oldsector= MobileItem::currworld->GetSector(*AC);

					AC->World.X+=DeltasToApply[n][DeltaIndex].lastpos.X;
					AC->World.Y+=DeltasToApply[n][DeltaIndex].lastpos.Y;
					AC->World.Z+=DeltasToApply[n][DeltaIndex].lastpos.Z;

					if (oldsector!=MobileItem::currworld->GetSector(*AC))
					{
						MobileItem::currworld->RemoveFromSector(*AC,oldsector);
						MobileItem::currworld->AddToWorld(*AC);
					}

					AC->hdg.a+=DeltasToApply[n][DeltaIndex].Heading.a;
					AC->fly.dhdg+=DeltasToApply[n][DeltaIndex].Heading.a;

					AC->pitch.a+=DeltasToApply[n][DeltaIndex].Pitch.a;
					AC->fly.cpitch=AC->pitch;

					AC->roll.a+=DeltasToApply[n][DeltaIndex].Roll.a;
					AC->vel_+=DeltasToApply[n][DeltaIndex].Velocity;
				}
			}

			ZeroMemory(&DeltasToApply[n][DeltaIndex],sizeof(DELTARECORD));
		}
	}
	DeltaIndex++;

	if (DeltaIndex>=RateDivider)
		DeltaIndex=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddDeltasToApply
//Date			Tue 30 Nov 1999
//------------------------------------------------------------------------------
void		DPlay::AddDeltasToApply(LPACPACKET packet, ULong slot)
{
	UByte	shiftfactor=packet->Shift;
	SLong	val,valfrac;
	SLong 	frac;
	UByte	TempIndex,n;
	ULong	index;

	val=GetVal(packet->X,shiftfactor);

// yuk, messy

	{
		TempIndex=DeltaIndex;
		valfrac=val/RateDivider;
		frac=(val-(valfrac*RateDivider));

		DeltasToApply[slot][TempIndex].lastpos.X+=frac;
		for (n=0;n<RateDivider;n++)
		{
			DeltasToApply[slot][TempIndex].lastpos.X+=valfrac;

			TempIndex++;

			if (TempIndex>=RateDivider)
				TempIndex=0;
		}
	}

	val=GetVal(packet->Y,shiftfactor);

	{
		TempIndex=DeltaIndex;
		valfrac=val/RateDivider;
		frac=(val-(valfrac*RateDivider));

		DeltasToApply[slot][TempIndex].lastpos.Y+=frac;
		for (n=0;n<RateDivider;n++)
		{
			DeltasToApply[slot][TempIndex].lastpos.Y+=valfrac;

			TempIndex++;

			if (TempIndex>=RateDivider)
				TempIndex=0;
		}
	}

	val=GetVal(packet->Z,shiftfactor);

	{
		TempIndex=DeltaIndex;
		valfrac=val/RateDivider;
		frac=(val-(valfrac*RateDivider));

		DeltasToApply[slot][TempIndex].lastpos.Z+=frac;
		for (n=0;n<RateDivider;n++)
		{
			DeltasToApply[slot][TempIndex].lastpos.Z+=valfrac;

			TempIndex++;

			if (TempIndex>=RateDivider)
				TempIndex=0;
		}
	}

	val=GetVal(packet->Heading,shiftfactor);

	{
		TempIndex=DeltaIndex;
		valfrac=val/RateDivider;
		frac=(val-(valfrac*RateDivider));

		DeltasToApply[slot][TempIndex].Heading.a+=frac;
		for (n=0;n<RateDivider;n++)
		{
			DeltasToApply[slot][TempIndex].Heading.a+=valfrac;

			TempIndex++;

			if (TempIndex>=RateDivider)
				TempIndex=0;
		}
	}

	val=GetVal(packet->Pitch,shiftfactor);

	{
		TempIndex=DeltaIndex;
		valfrac=val/RateDivider;
		frac=(val-(valfrac*RateDivider));

		DeltasToApply[slot][TempIndex].Pitch.a+=frac;
		for (n=0;n<RateDivider;n++)
		{
			DeltasToApply[slot][TempIndex].Pitch.a+=valfrac;

			TempIndex++;

			if (TempIndex>=RateDivider)
				TempIndex=0;
		}
	}

	val=GetVal(packet->Roll,shiftfactor);


	{
		TempIndex=DeltaIndex;
		valfrac=val/RateDivider;
		frac=(val-(valfrac*RateDivider));

		DeltasToApply[slot][TempIndex].Roll.a+=frac;
		for (n=0;n<RateDivider;n++)
		{
			DeltasToApply[slot][TempIndex].Roll.a+=valfrac;

			TempIndex++;

			if (TempIndex>=RateDivider)
				TempIndex=0;
		}
	}


	val=GetVal(packet->Velocity_,shiftfactor);

	SLong newvel=abs(val)<<_Replay.velshifttest;

	if (val<0)
		newvel=-newvel;


	{
		TempIndex=DeltaIndex;
		valfrac=newvel/RateDivider;
		frac=(newvel-(valfrac*RateDivider));

		DeltasToApply[slot][TempIndex].Velocity+=frac;
		for (n=0;n<RateDivider;n++)
		{
			DeltasToApply[slot][TempIndex].Velocity+=valfrac;

			TempIndex++;

			if (TempIndex>=RateDivider)
				TempIndex=0;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcAndAddPartialDelta
//Date			Wed 1 Dec 1999
//Description	Bah
//------------------------------------------------------------------------------
void	DPlay::CalcAndAddPartialDelta(SLong val, ULong slot, ULong index)
{
	UByte	TempIndex=DeltaIndex,n;
	SLong 	valfrac, frac;

	valfrac=val/RateDivider;
	frac=(val-(valfrac*RateDivider));

	UByteP ptr;

	ptr=(UByteP)(&DeltasToApply[slot][TempIndex]);
	ptr+=index;
	(*ptr)+=frac;

	
	for (n=0;n<RateDivider;n++)
	{
		ptr=(UByteP)(&DeltasToApply[slot][TempIndex]);
		ptr+=index;
		(*ptr)+=valfrac;


		TempIndex++;

		if (TempIndex>=RateDivider)
			TempIndex=0;
	}
}

void	DPlay::CheckSendQueue()
{
	HRESULT res;
	DPID from,to;
	DWORD nummess=0,numbytes=0,anummess=0,anumbytes=0;

	from=H2H_Player[mySlot].dpid;
	to=0;

	res=lpDP4->GetMessageQueue(from,to,DPMESSAGEQUEUE_SEND,&nummess,&numbytes);

	if (Host)
	{
		from=aggID;

		res=lpDP4->GetMessageQueue(from,to,DPMESSAGEQUEUE_SEND,&anummess,&anumbytes);
	}

#ifdef MESSQUEUELOG
	FILE* fp=fopen("messQ.txt","at");
	fprintf(fp,"%d: nummess=%d numbytes=%d\n",FrameCount,nummess,numbytes);
	if (Host)
		fprintf(fp,"Agg: %d aggnummess=%d aggnumbytes=%d\n",_Agg.GetAggFrameCount(),anummess,anumbytes);
	fclose(fp);
#endif

	if (nummess || numbytes || anummess || anumbytes)
	{
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetAllAIFields
//Date			Thu 23 Dec 1999
//------------------------------------------------------------------------------
void	DPlay::ResetAllAIFields(AirStrucPtr ac)
{
	ac->ai.unfriendly=NULL;

	for(int i = 0; i < 4; i++)
		ac->ai.spottedunfriendly[i] = NULL;							

	ac->ai.attacker=NULL;

// reset all fields?

	ac->ai.desiredroll=ANGLES_0Deg;
	ac->ai.desiredpitch=ANGLES_0Deg;
	ac->ai.desiredaoa=ANGLES_0Deg;
	ac->ai.oldpitchI=ANGLES_0Deg;

	if (ac->uniqueID.count<SagBANDEND)
		ac->ai.oldoldpitchI=ANGLES_0Deg;

	ac->ai.oldoldoldpitchI=ANGLES_0Deg;
	ac->ai.oldhdgI=ANGLES_0Deg;
	ac->ai.oldoldhdgI=ANGLES_0Deg;
	ac->ai.oldoldoldhdgI=ANGLES_0Deg;
	ac->ai.desiredturn=0;
	ac->ai.desiredpitchrate=0;
	ac->ai.desiredrange=0;
	ac->ai.desiredalt=0;
	ac->ai.deltapitchsum=0;
}

void	DPlay::NewEngineRPMPacket(UWord	rpmlevel)
{
	if (_Replay.Record)
	{
// rpm has been scaled down to 4 levels (may be 5 if overrevving)...

		NewSpecial(PIDC_ENGINERPM,UByte(rpmlevel&0xFF));
	}
}

void	DPlay::ProcessEngineRPMPacket(UByteP ptr)
{
	if (_Replay.Playback)
	{
		UByte b1,b2,b3;

		b1=*ptr;			// we only need 1 byte...

// Set RPM
 		Persons2::PlayerSeenAC->fly.rpm = (b1*Persons2::PlayerSeenAC->classtype->maxrpm)>>2;	
		Persons2::PlayerSeenAC->fly.rpm1 = Persons2::PlayerSeenAC->fly.rpm;
	}
}

void	DPlay::NewEngineAnimPacket()
{
	NewSpecial(PIDC_ENGINEANIM);
}

void	DPlay::ProcessEngineAnimPacket(UByteP ptr, ULong slot)
{
	AirStrucPtr ac;

	if (_DPlay.Implemented)
	{
		ac=*Persons2::ConvertPtrUID((UniqueID)AllocPacket[slot]);
	}
	else
	{
		ac=Persons2::PlayerSeenAC;
	}

	if (ac)
	{
// trigger animation 

		Trans_Obj.LaunchEngineStartup(ac,*mobileitem::currworld,true);
	}
}

void	DPlay::WaitForPlayersUniqueIDs()
{
	HRESULT res;
	char* Buffer;
	ULong BufLen,From;
	ULong now=timeGetTime();
	CommsTimeout time(now,CommsTimeoutLength*6);

	while (!GotAllPlayersUniqueIDs())
	{
		now=timeGetTime();

		if (time.TimedOut(now))
			_Error.EmitSysErr("Timed out waiting for player UIDs");

		while (ReceiveNextMessageToMe(Buffer,BufLen,From,DPRECEIVE_TOPLAYER))
		{
			if (From==DPID_SYSMSG)
			{
				_DPlay.ProcessSystemMessage(Buffer);
			}
			else if (From!=_DPlay.aggID)
			{
				ProcessPlayerMessage(Buffer,BufLen,From);
			}
		}
	}

	int i;
	AirStrucPtr ac;

	for (i=0;i<MAXPLAYERS;i++)
	{
		ac=*Persons2::ConvertPtrUID((UniqueID)AllocPacket[i]);

		if (ac)
		{
			ac->uniqueID.commsmove=TRUE;
		}
	}
}

void	DPlay::SendMyUniqueID(UWord uid)
{
	GENERIC pack;

	pack.PacketID=PID_UNIQUEID;
	pack.PlayerID=uid;

	SendMessageToGroup((char*)&pack,sizeof(GENERIC));
}

void	DPlay::Process_PM_UniqueID(char* message, ULong from)
{
	ULong slot;

	slot=DPID2Slot(from);

	if (slot!=MAXPLAYERS)
	{
		LPGENERIC p=(LPGENERIC)message;

		AllocPacket[slot]=p->PlayerID;

// only host has AC set up at this stage, set commsmove at end
// of bfield phase

	}
}

bool	DPlay::GotAllPlayersUniqueIDs()
{
	ULong n,m=0;

	for (n=0;n<MAXPLAYERS;n++)
	{
		if (AllocPacket[n]!=0)
			m++;
	}

	if (m==CurrPlayers)
		return true;

	return false;
}
void	DPlay::AddPacketToCheckBuffer(LPAGGSENDPACKET packet)
{
	ULong n;

	PlayerAggCheck.GetNext()->Frame=packet->Count;

// check for players acks

#ifdef P_A_CHECK
	FILE* fp=fopen("pacheck.txt","at");
#endif

	for (n=0;n<MAXPLAYERS;n++)
	{
		if (packet->player[n].IDCode!=PIDC_PACKETERROR)
		{
// legit players packet
// update aggregator packet ack buffer

			PlayerAggCheck.GetNext()->whichframe[n]=packet->player[n].Count;
#ifdef P_A_CHECK
			fprintf(fp,"Frame %d: Player %d Ack1=%d Ack2=%d\n",packet->Count,n,packet->player[n].Ack1,packet->player[n].Ack2);
#endif

			PlayerAggCheck.SetTempCurr();

			int offset=0;
			do 
			{
				if (PlayerAggCheck.GetTemp()->Frame==packet->player[n].Ack1
				|| 	PlayerAggCheck.GetTemp()->Frame==packet->player[n].Ack2)
				{
#ifdef P_A_CHECK
					fprintf(fp,"found ack for %d by player %d at offset %d\n",PlayerAggCheck.GetTemp()->Frame,n,offset);
#endif
				 	PlayerAggCheck.GetTemp()->acked[n]=true;
				}
				offset++;

				PlayerAggCheck.UpdateTemp();
			}
			while (PlayerAggCheck.GetTemp()!=PlayerAggCheck.GetCurr());
		}
	}
	PlayerAggCheck.AddEntryAndUpdateNext();
#ifdef P_A_CHECK
	fclose(fp);
#endif
}

void	DPlay::StoreReceivedBField(char* pack, ULong len)
{
	char* ptr=pack;

	LPGRLIST temp=new GRLIST;

	ptr+=sizeof(ULong);

	temp->ordernum=*(UWord*)ptr;
	ptr+=sizeof(UWord);

	temp->bfctrl=*(ULong*)ptr;
	ptr+=sizeof(ULong);

	temp->file=*(FileNum*)ptr;
	ptr+=sizeof(FileNum);

	temp->list=NULL;

// add gr list to entry

	bool finished=false;
	ULong val,m;
	UByte set;

	while (!finished)
	{
		set=*(UByte*)ptr;
		ptr+=sizeof(UByte);

		for (m=0;m<8;m++)
		{
			LPREPGRENTRY tempgr=new REPGRENTRY;
			tempgr->next=NULL;

			if (set&0x1<<m)
			{
				tempgr->val=*(int*)ptr;
				ptr+=sizeof(int);

				if (tempgr->val==BAD_RV)
					finished=true;
			}
			else
			{
				tempgr->val=0;
			}

			if (temp->list)
			{
				LPREPGRENTRY temp2=temp->list;

				while (temp2->next)
					temp2=temp2->next;

				temp2->next=tempgr;
			}
			else
			{
				temp->list=tempgr;
			}
			tempgr=NULL;
		}

	}

// add entry to list

	temp->next=_Replay.bfgrlist;
	_Replay.bfgrlist=temp;

	temp=NULL;
}

bool	DPlay::ProcessRequiredBFieldPacket(ULong& bfctrl, FileNum& filelist)
{
// traverse list and see if bfield with correct order number is present

	LPGRLIST temp=_Replay.bfgrlist;
	ULong n;
	int val;
	bool finished;

	while (temp)
	{
		if (temp->ordernum==BFieldToProcess)
		{
			if (bfctrl==Persons3::LOADSCRAMBF)
			{
				Persons2::SetUpDiary();
			}

			bfctrl=temp->bfctrl;
			filelist=temp->file;

			finished=false;

			n=0;
			LPREPGRENTRY tempgr=temp->list;

			while (!finished)
			{
				if (tempgr)
				{
					val=tempgr->val;

					if (val!=BAD_RV)
					{
						Persons2::SetLoc(n,val);
						n++;
					}
					else
					{
						finished=true;
					}
					tempgr=tempgr->next;
				}
				else
				{
					finished=true;
				}
			}

			return true;
		}
		temp=temp->next;
	}

	return false;
}

void	DPlay::JumpToWebSite()
{
	HINSTANCE hApp;

	hApp = ShellExecute (GetDesktopWindow(), "open",
	"http://www.empireinteractive.com/BOB", NULL, NULL, SW_SHOW);
}

void	DPlay::BackupHostPrefs()
{
	HostCollPrefs=0;

	if (Save_Data.gamedifficulty[GD_VULNERABLE])
		HostCollPrefs|=1<<WEAPON;

	if (Save_Data.gamedifficulty[GD_GROUNDCOLLISIONS])
		HostCollPrefs|=1<<GROUND;

	if (Save_Data.gamedifficulty[GD_COLLISIONS])
		HostCollPrefs|=1<<AIR2AIR;

	if (Save_Data.flightdifficulty[FD_ENGINEMANAGMENT])
		HostCollPrefs|=1<<ENGINEMAN;
}

void	DPlay::RestoreHostPrefs()
{
	if (!(HostCollPrefs&1<<WEAPON))
		Save_Data.gamedifficulty%=GD_VULNERABLE;

	if (!(HostCollPrefs&1<<GROUND))
		Save_Data.gamedifficulty%=GD_GROUNDCOLLISIONS;

	if (!(HostCollPrefs&1<<AIR2AIR))
		Save_Data.gamedifficulty%=GD_COLLISIONS;

	if (!(HostCollPrefs&1<<ENGINEMAN))
		Save_Data.flightdifficulty%=FD_ENGINEMANAGMENT;
}

void	DPlay::ClearDeadPilots()
{
	LPDEADPILOT temp=deadpilotlist,temp1;

	while (temp)
	{
		temp1=temp->next;
		delete temp;
		temp=temp1;
	}
	deadpilotlist=NULL;

}

void	DPlay::NewDeadPilot(int squadron, UByte position)
{
	LPDEADPILOT temp=new DEADPILOT;

	temp->next=deadpilotlist;
	temp->position=position;
	temp->squadron=squadron;

	deadpilotlist=temp;
}

bool DPlay::IsPilotDead(int squad, UByte pos)
{
	LPDEADPILOT temp=_DPlay.deadpilotlist;

	while (temp)
	{
		if (temp->position==pos && temp->squadron==squad)
			return true;

		temp=temp->next;
	}

	return false;
}

void	DPlay::UpdateDeadPilots(AirStrucPtr ac)
{
// update deadpilots for comms quick missions
		
	if (_DPlay.PlayerCreated)
	{
		int squadnum;
		UByte pltnum;

		squadnum=ac->ai.pilotnum;
		
		int sqcol,sqnum,numacinflight;

		switch (ac->classtype->planetext)
		{
		case PT_SPIT_A:
		case PT_SPIT_B:
		case PT_HURR_A:
		case PT_HURR_B:
		case PT_DEFIANT:
		case PT_BLEN:
		case PT_JU87:
			numacinflight=3;
			break;

		case PT_ME109:
		case PT_ME110:
			numacinflight=4;
			break;

		case PT_DO17:
		case PT_JU88:
		case PT_HE111:
			numacinflight=5;
			break;
		default:
			numacinflight=0;
			INT3;
			break;
		}

		sqcol=(ac->fly.originalformpos & InFormMAX)+1;
		sqnum=(ac->fly.originalformpos & InWingMAX)+1;

		pltnum=((sqcol-1)*numacinflight)+sqnum;


		_DPlay.NewDeadPilot(squadnum,pltnum);
	}
}

void DPlay::BombCheck(AirStrucPtr ac)
{
	if((!_DPlay.Implemented) || (_DPlay.GameType == DPlay::COMMSQUICKMISSION))
		return;

	ac->ai.desiredturn += MODEL_DT;
	if (ac->classtype->planetext==PT_ME110)
	{
		if(ac->ai.desiredturn >= 1000)
		{
			Trans_Obj.ReloadBomb(ac);
			ac->ai.desiredturn = 0;
		}
	}
	else if (ac->classtype->planetext==PT_JU87)
	{
		if(ac->ai.desiredturn >= 150)
		{
			Trans_Obj.ReloadBomb(ac);
			ac->ai.desiredturn = 0;
		}
	}
	else
	{
		ac->ai.desiredturn=0;
	}
}

void	DPlay::SendACArray()
{
	UByte count=0;
	int packsize;
	UByteP pack,temp;
	UWord uid;
	int i;

	for(i = 0; i < ArtInt::ACARRAYSIZE; i++)
	{
		if(ArtInt::ACArray[i])
		{
			count++;
		}
	}

	packsize=sizeof(ULong) //PID
			+sizeof(UByte) // num
			+(count*sizeof(UByte)) // data uids
			+(count*sizeof(UWord)); // data uids

	pack=new UByte[packsize];
	temp=pack;

	*(ULong*)temp=PID_ACARRAY;
	temp+=sizeof(ULong);
	*(UByte*)temp=count;
	temp+=sizeof(UByte);

	for(i = 0; i < ArtInt::ACARRAYSIZE; i++)
	{
		if(ArtInt::ACArray[i])
		{
			*(UByte*)temp=i;
			temp+=sizeof(UByte);
			uid=ArtInt::ACArray[i]->uniqueID.count;
			*(UWord*)temp=uid;
			temp+=sizeof(UWord);
		}
	}

	SendMessageToGroup((char*)pack,packsize);

	delete [] pack;
}

bool	DPlay::GetACArray()
{
	char* buffer;
	ULong	buflen,from;

	while (ReceiveNextMessageToMe(buffer,buflen,from,DPRECEIVE_TOPLAYER))
	{
		if (from==DPID_SYSMSG)
		{
			ProcessSystemMessage(buffer);
		}
		else if (from!=aggID)
		{
			if (*(ULong*)buffer==PID_ACARRAY)
			{
				ProcessACArrayPacket((UByte*)buffer);
				return true;
			}
			else 
			{
				ProcessPlayerMessage(buffer,buflen,from);
			}
		}
	}
	return false;
}

void	DPlay::ProcessACArrayPacket(UByte* packet)
{
	UByte index;
	UWord num,uid;

// clear out array first

	for(index = 0; index < ArtInt::ACARRAYSIZE; index++)
	{
		ArtInt::ACArray[index]=NULL;
	}

	packet+=sizeof(ULong); // get past PID

	UByte count=*(UByte*)packet;
	packet+=sizeof(UByte);

	while (count--)
	{
		index=*(UByte*)packet;
		packet+=sizeof(UByte);
		uid=*(UWord*)packet;
		packet+=sizeof(UWord);

		AirStrucPtr ac=*Persons2::ConvertPtrUID(UniqueID(uid));

		ArtInt::ACArray[index]=ac;
	}
}

bool	DPlay::IsThereKillLauncher()
{
// check special packet buffer for a PIDC_KILLLAUNCHER

	SpecBuffer.SetTempCurr();

	UByte entries=SpecBuffer.NumEntries();

	while (entries--)
	{
		if (SpecBuffer.GetTemp()->IDCode==PIDC_KILLLAUNCHER)
			return true;
	}

	return false;
}

UByte	DPlay::MakeKillLauncherPacket(LPBASICPACKET packet, UByte index)
{
	UByteP ptr1=&packet->IDCode;
	UByte len=0,n;
	ptr1+=index;

	SpecBuffer.SetTempCurr();

	UByte entries=SpecBuffer.NumEntries();

	while (entries--)
	{
		if (SpecBuffer.GetTemp()->IDCode==PIDC_KILLLAUNCHER)
		{
			UByteP ptr2=(UByteP)(&SpecBuffer.GetTemp()->IDCode);
			len=PacketLength(SpecBuffer.GetTemp()->IDCode);

// fills in id code and extra bytes from special packet buffer

			for (n=0;n<len;n++)
			{
				*ptr1++=*ptr2++;
			}

			SpecBuffer.GetTemp()->IDCode=PIDC_DONTSEND;

// if this is first entry then update buffer, other entries will be
// sorted out when the previous entry is processed

			if (SpecBuffer.GetCurr()->IDCode==PIDC_DONTSEND)
				SpecBuffer.UpdateCurr();

			break;
		}
	}

	return len;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DPlay
//Date			Tue 3 Dec 1996
//Description	Moved constructor & destructor from winmove.h
//------------------------------------------------------------------------------
CON		DPlay::DPlay ()
{
#ifndef NDEBUG
	CheckPacketSizes();
#endif

	CoInitialize(NULL);

	ULong n,m;

	lpDP4=NULL;
	lpDPL=NULL;

	ServiceList=NULL;

	FrameInc=0;
	RateDivider=1;

	UIPlayerType = 0;
	Implemented = FALSE;
	PlayerCreated = FALSE;
	FlyNowFlag = FALSE;
	FrameCount = 0;
	ActivePlayers = 0;

	for (n=0; n<MAXPLAYERS; n++)
	{
		AIACPositions[n]=NULL;
	}

	Bool	dp_usepaintscheme;
	GameType=DEATHMATCH;
 	MyTeamKills=0;
 	EnemyTeamKills=0;
 	EnemyTeamDeaths=0;
	MyTeamDeaths=0;

	AllowSuicide=TRUE;

	ResyncPhase=FALSE;
	WorldSyncPhase=FALSE;
	WorldSyncPhaseReady=false;
	Initiator=FALSE;


	Joining=FALSE;
	Lobbied=FALSE;
	VisitorsBook=NULL;
	GameRunning=FALSE;

	MainSheetCount=FALSE;

	Password[0]=NULL;
	SessionName[0]=NULL;
	PlayerName[0]=NULL;
	tempdpsessdesc2=NULL;
	SimulateExitKey=FALSE;
	LeaveCommsFlag=FALSE;
	HostQuitFlag=FALSE;
	MyAIACPositionsToSend=NULL;
	UpdateFrag=FALSE;
	UpdateMission=FALSE;
	DisplayInfo=FALSE;
	sendtowho=0;// default is send to all players
	FragChanged=false;
	viewtime=true;
	singlesession=false;
	MsgRecipientAll=true;
	SideSelected=false;
	CommsPacketPtr=NULL;
	CommsPacketLength=0;
	BufferSize=128;
	SpookyGhostMode=false;
	listptr=NULL;
	deadpilotlist=NULL;

	for (n=0;n<STAGE_MAX;n++)
	{																
		CommsStage[n][0]=false;
		CommsStage[n][1]=false;
	}
}

CON DPlay::~DPlay ()
{
	ExitDirectPlay();
	DeleteVisitorBook();

	CoUninitialize(); // OK to call this now, all interfaces have been released
}


