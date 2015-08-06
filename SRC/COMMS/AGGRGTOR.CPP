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
//Filename       aggrgtor.cpp
//Date           Wed 29 Apr 1998
//------------------------------------------------------------------------------
#include "dosdefs.h"
#include "uniqueid.h"
#include "movement.h"
#include "package.h"
#include	"aggrgtor.h"
#include	<stdio.h>
#include	"comms.h"
#include	"stub3d.h"

//#define 	AGGLOGS

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AggregatorGetPackets
//Date			Thu 20 Mar 1997
//------------------------------------------------------------------------------
void Aggregator::AggregatorGetPackets() //Bool reset, Bool timercall)
{
	LPACPACKET RecPacket;
 	HRESULT	res;
	ULong	n,m;
	bool	SendResult;
	myDPID	from;
	DWORD	BufferLen;
	char* Buffer;

#ifndef NDEBUG
	if (!_DPlay.Host)
		_Error.SayAndQuit("Player processing packets to aggregator!!!!!");
#endif

	if (ResetFlag)
	{
		InitAggregator();

#ifdef AGGLOGS	
		Log("RESET aggregator\n");
#endif
	}
	else
	if (Running)
	{
// calls from timer are every 1/50 sec. Use to determine timeout

		time++;
		clearbuffertime++;

		GetAllMessages();

		MakeAndSendAggPacket();

		if (buffer)
		{
// only resend packets or clear buffers if we are REAL game mode, not whilst
// in resync!!!!!!!!!!!!!

			if (AllowResendOrBurstCatchUp())
			{
				SLong entry=RequireResend();

				if (entry!=-1)
				{
					Resend(entry);
				}
				else if (BurstInBuffer())
				{
					BurstCatchup();
				}
			}
		}
	}
	else
	{
// receive and junk all messages to aggregator as we are not ready for them yet!!!!

		ClearMessageQueue();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitAggArrayBuffer
//Date			Tue 25 Mar 1997
//Description	Initialises the aggregators array buffer to error values
//------------------------------------------------------------------------------
void Aggregator::InitAggArrayBuffer()
{
	ULong n;

	for(n=0;n<MAXPLAYERS;n++)
	{
// possibly dont need to zero, if IDCode is PIDC_PACKETERROR packet is never processed
 		memset(&allpackets.player[n],0,sizeof(ACPACKET));
		allpackets.player[n].IDCode=DPlay::PIDC_PACKETERROR;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetAcks
//Date			Wed 14 Jan 1998
//------------------------------------------------------------------------------
void	Aggregator::SetAcks()
{
	for (ULong n=0;n<MAXPLAYERS;n++)
	{
// want acks from all active players for all packets thankyouverymuch
		if (_DPlay.ActivePlayers&1<<n)
		{
			AggBuffer.GetNext()->Acks[n]=FALSE;
		}
		else
		{
			AggBuffer.GetNext()->Acks[n]=TRUE;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitAggregator
//Date			Wed 29 Apr 1998
//------------------------------------------------------------------------------
void	Aggregator::InitAggregator()
{
	ULong n;

	AggFrameCount=0;										

	AggBuffer.InitBuffer();
	AggBuffer.SetTempCurr();
	do
	{
		for (n=0;n<MAXPLAYERS;n++)
		{
			AggBuffer.GetTemp()->Acks[n]=FALSE;
		}

		memset(&(AggBuffer.GetTemp()->aggpack),0,sizeof(AGGSENDPACKET));
		AggBuffer.GetTemp()->ResendStatus=0;

		AggBuffer.UpdateTemp();
	}
	while (AggBuffer.GetTemp()!=AggBuffer.GetCurr());

	ClearMessageQueue();

	InitReservePackets();
	ResetAcks();
	ResetFlag=false;
	InitAggArrayBuffer();
	time=0;
	clearbuffertime=0;
	buffer=FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopResetAggregator
//Date			Mon 15 Sep 1997
//------------------------------------------------------------------------------
void Aggregator::StopResetAggregator()
{
	ResetFlag=TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetAcks
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
void Aggregator::ResetAcks()
{
	ULong n;

	for (n=0;n<MAXPLAYERS;n++)
	{
		AggBuffer.GetCurr()->Acks[n]=FALSE;
	}

	memset (&(AggBuffer.GetCurr()->aggpack),0,sizeof(AGGSENDPACKET));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckAck
//Date			Thu 13 Aug 1998
//------------------------------------------------------------------------------
void	Aggregator::CheckAck(UByte val, UByte pos)
{
	LPAGGBUFF temp;

	if (val!=0)
	{
		Log("received ack for %d\n",val);

		AggBuffer.SetTempCurr();
		while (AggBuffer.GetTemp()!=AggBuffer.GetNext())
		{
			if (AggBuffer.GetTemp()->aggpack.Count==val)
			{
				Log("found packet %d to ack from player %d\n",val,pos,
					AggBuffer.GetTemp()->aggpack.Count);

				AggBuffer.GetTemp()->Acks[pos]=TRUE;

				Log("Ack[0]=%d Ack[1]=%d\n",AggBuffer.GetTemp()->Acks[0],
					AggBuffer.GetTemp()->Acks[1]);

				break;
			}
			AggBuffer.UpdateTemp();
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateAckBuffer
//Date			Thu 20 Aug 1998
//------------------------------------------------------------------------------
void	Aggregator::UpdateAckBuffer()
{
	Bool update=TRUE;
	ULong n;

	while (update)
	{
		update=TRUE;

		for (n=0;n<MAXPLAYERS;n++)
		{
			if (AggBuffer.GetCurr()->Acks[n]==FALSE)
			{
				update=FALSE;
				break;
			}
		}

		if (update)
		{

			Log("update CurrAggPackPos %d slot0=%d slot1=%d\n",
				AggBuffer.GetCurr()->aggpack.Count,
				AggBuffer.GetCurr()->aggpack.player[0].Count,
				AggBuffer.GetCurr()->aggpack.player[1].Count);

			ResetAcks();
			AggBuffer.UpdateCurr();
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitReservePackets
//Date			Mon 17 Aug 1998
//------------------------------------------------------------------------------
void	Aggregator::InitReservePackets()
{
	ULong n;

	for (n=0;n<MAXPLAYERS;n++)
	{
		ReservePackets[n].InitBuffer();
		ReservePackets[n].SetTempCurr();
		do 
		{
			ReservePackets[n].GetTemp()->IDCode=DPlay::PIDC_PACKETERROR;
			ReservePackets[n].UpdateTemp();
		}
		while (ReservePackets[n].GetTemp()!=ReservePackets[n].GetCurr());
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReceiveMessage
//Date			Thu 13 May 1999
//------------------------------------------------------------------------------
HRESULT	Aggregator::ReceiveMessage(char*&buf,ULong& buflen,ULong& from)
{
	HRESULT res;

	ULong to=_DPlay.aggID,temp;
	from=0;

	while (true)
	{
		temp=AggPacketLength;
		res=_DPlay.lpDP4->Receive(&from,&to,DPRECEIVE_TOPLAYER,AggPacketPtr,&temp);

		if (res==DPERR_BUFFERTOOSMALL)
		{
			delete [] AggPacketPtr;
			AggPacketPtr=NULL;
			AggPacketPtr=new char[temp];
			AggPacketLength=temp;
			if (!AggPacketPtr)
				_Error.EmitSysErr("Out of memory");
		}
		else if (res==DP_OK)
		{
			buf=AggPacketPtr;
			buflen=temp;
			return res;
		}
		else break;
	}
	return res;
}

bool Aggregator::MakeAndSendPacket(LPAGGSENDPACKET packet, Bool buffer)
{
	ULong NumPlayers=0, n, PacketSize;
	bool ok;
	HRESULT res;
	AGGSENDPACKET p;
	UByteP TempPtr=(UByteP)&p;

	PacketSize=sizeof(UByte); // count
	PacketSize+=sizeof(ULong); // player in packet

	*((ULong*)TempPtr)=RecBits;
	TempPtr+=sizeof(ULong);
	*TempPtr=AggFrameCount;
	TempPtr+=sizeof(UByte);

// start filling in players packets

	for (n=0; n<MAXPLAYERS; n++)
	{
		if (RecBits & 1<<n)
		{
// copy player from packet to Packet

			CopyMemory(TempPtr,&packet->player[n],sizeof(ACPACKET));
			TempPtr+=sizeof(ACPACKET);
			PacketSize+=sizeof(ACPACKET);
			NumPlayers++;
		}
	}

#ifndef NDEBUG
	if (_DPlay.LosePackets)
	{
		_DPlay.LosePackets--;
		res=DP_OK;
	}
	else
#endif
	{
		res=_DPlay.lpDP4->SendEx(_DPlay.aggID,_DPlay.playergroupID,DPSEND_ASYNC|DPSEND_NOSENDCOMPLETEMSG ,&p,PacketSize,0,0,NULL,NULL);
	}

	if (!res || res==DPERR_PENDING)
		ok=true;
	else
		ok=false;

// copy packet into buffer if not in sync phase

	if (buffer)
	{
// if we have filled up sent buffer then overwrite last entry.
// If packet has really not been received by a player then it will cause them to 
// initaite a resynch quite soon....!!!!

		if (AggBuffer.NumEntries()==_DPlay.BufferSize)
		{
			ResetAcks();
			AggBuffer.UpdateCurr();
			UpdateAckBuffer();
		}

		AggBuffer.GetNext()->NumPlayersInPacket=NumPlayers;
		AggBuffer.GetNext()->ResendStatus=0;

		for (n=0; n<MAXPLAYERS; n++)
		{
// copy player from packet to Packet

			CopyMemory(&(AggBuffer.GetNext()->aggpack.player[n]),&packet->player[n],sizeof(ACPACKET));
		}
		AggBuffer.GetNext()->aggpack.Count=p.Count;
	}

	return ok;
}

bool Aggregator::ResendAggPacket(SLong entry)
{
	ULong PacketSize;
	HRESULT res;
	bool	ok;

	AggBuffer.SetTempCurr();

#ifndef NDEBUG
	if (entry<0 || entry>_DPlay.BufferSize)
		INT3;
#endif

	while (entry--)
	{
		AggBuffer.UpdateTemp();
	}

	PacketSize=sizeof(ULong);
	PacketSize+=sizeof(UByte);
 	PacketSize+=sizeof(ACPACKET) * AggBuffer.GetTemp()->NumPlayersInPacket;

	res=_DPlay.lpDP4->SendEx(_DPlay.aggID,_DPlay.playergroupID,DPSEND_ASYNC|DPSEND_NOSENDCOMPLETEMSG ,&((AggBuffer.GetTemp())->aggpack),PacketSize,0,0,NULL,NULL);

	AggBuffer.GetTemp()->ResendStatus++;

	if (!res || res==DPERR_PENDING)
		ok=true;
	else
		ok=false;

#ifdef AGGLOGS	
	Log("RESEND packet %d num=%d slot0=%d slot1=%d\n",
		AggBuffer.GetTemp()->aggpack.Count,AggBuffer.NumEntries(),
		AggBuffer.GetTemp()->aggpack.player[0].Count,
		AggBuffer.GetTemp()->aggpack.player[1].Count);

	if (AggBuffer.GetTemp()->Acks[0])
		Log("GOTACK from slot0\n");
	else
		Log("NEEDACK from slot0\n");

	if (AggBuffer.GetTemp()->Acks[1])
		Log("GOTACK from slot1\n");
	else
		Log("NEEDACK from slot1\n");
#endif
	return ok;
}

SLong Aggregator::RequireResend()
{
	ULong num=AggBuffer.NumEntries(),n=0,m;

	AggBuffer.SetTempCurr();

	do
	{
		if ((num-n)>_DPlay.BufferSize/2 && AggBuffer.GetTemp()->ResendStatus<2)
		{
// only resend this packet if someone has not ACKed it

			for (m=0;m<MAXPLAYERS;m++)
			{
				if (!AggBuffer.GetTemp()->Acks[m])
				{
// return index into buffer of packet that needs to be resent

					return n;
				}
			}
		}

		if ((num-n)<1)
			break;

		n++;
		AggBuffer.UpdateTemp();
	}
	while (AggBuffer.GetTemp()!=AggBuffer.GetCurr());
	
// no packets need resending

	return -1;
}

bool Aggregator::AllowResendOrBurstCatchUp()
{
	if (clearbuffertime==((_DPlay.RateDivider*2)-(_DPlay.RateDivider/2)) && !_DPlay.WorldSyncPhase)
	{
		clearbuffertime=0;
		return true;
	}
	return false;
}

void Aggregator::Resend(SLong entry)
{
	bool SendResult;

	SendResult=ResendAggPacket(entry);
}

void Aggregator::BurstCatchup()
{
	ULong n;
	LPACPACKET RecPacket;
	bool SendResult;

// in between every other agg packet

#ifdef AGGLOGS	
	Log("bufsize=%d curr=%d\n",AggBuffer.NumEntries(),AggBuffer.GetCurr()->aggpack.Count);
#endif
// if not resending a packet check if buffers have any entries and if so try 
// and clear by sending an extra packet a frame.

	for (n=0;n<MAXPLAYERS;n++)
	{
		if (ReservePackets[n].NumEntries()>2 && !(RecBits&1<<n))
		{
			RecPacket=ReservePackets[n].GetCurr();
#ifdef AGGLOGS	
			Log("GOT %d from buffer\n",RecPacket->Count);
#endif
			CopyMemory(&allpackets.player[n],RecPacket,sizeof(ACPACKET));
			RecBits|=1<<n;
			ReservePackets[n].GetCurr()->IDCode=DPlay::PIDC_PACKETERROR;
			ReservePackets[n].UpdateCurr();
		}
	}

	if (RecBits)
	{
#ifdef AGGLOGS	
		Log("found packet to send as extra\n");
#endif
//  AggFrameCount filled in MakeAndSendPacket

// aggregator frame starts on 1 not zero. Zero frame used to indicate no Ack in packet

		SendResult=MakeAndSendPacket(&allpackets,buffer);

		RecBits=0;

#ifdef AGGLOGS
		if (SendResult)
			Log("sent and buffered %d OK p0=%d p1=%d\n",AggFrameCount,
				allpackets.player[0].Count,allpackets.player[1].Count);
		else
			Log("error sending %d\n",AggFrameCount);
#endif

		AggFrameCount++;

		if (!AggFrameCount)
			AggFrameCount=1;

		if (AggBuffer.NumEntries()==_DPlay.BufferSize)
		{
			ResetAcks();
			AggBuffer.UpdateCurr();
			UpdateAckBuffer();
		}

		SetAcks();
		AggBuffer.AddEntryAndUpdateNext();
		InitAggArrayBuffer();
	}
}

void	Aggregator::ClearMessageQueue()
{
	myDPID	from;
	DWORD	BufferLen;
	char* Buffer;

	while (ReceiveMessage(Buffer,BufferLen,from)==DP_OK) {}
}

void	Aggregator::GetAllMessages()
{
	myDPID	from;
	DWORD	BufferLen;
	char* Buffer;
	ULong	n,m;
	HRESULT res;
	LPACPACKET RecPacket;

	Log("BEGIN RECEIVE LOOP\n");
// get all packets from Q
	do
	{
		res=ReceiveMessage(Buffer,BufferLen,from);

		if (res==DP_OK)
		{
			if (BufferLen==sizeof(ACPACKET))
			{
				n=_DPlay.DPID2Slot(from);

				if (n!=MAXPLAYERS)
				{
// got a delta packet from player

					RecPacket=(LPACPACKET)Buffer;

					Log("Aggframe=%d : Received %d from %d\n",AggFrameCount,RecPacket->Count,from);

// check for ack'ed packets 

					if (RecPacket->IDCode!=DPlay::PIDC_DUMMYPACKET)
					{
						CheckAck(RecPacket->Ack1,n);
						CheckAck(RecPacket->Ack2,n);
						UpdateAckBuffer();
					}

// put packet in buffer

// check packets in buffer and only add to buffer if this packet number 
// has not already been received - should get rid of huge number of resent packets problem...

					Bool add=TRUE;

					if (ReservePackets[n].NumEntries())
					{
						ReservePackets[n].SetTempCurr();
						do
						{
							if (ReservePackets[n].GetTemp()->Count==RecPacket->Count
							&& ReservePackets[n].GetTemp()->IDCode!=DPlay::PIDC_PACKETERROR)
							{
								add=FALSE;
								Log("IGNORE - packet already in buffer\n");
								break;
							}
							ReservePackets[n].UpdateTemp();
						}
						while (ReservePackets[n].GetTemp()!=ReservePackets[n].GetNext());
					}

					if (add)
					{
// if reserves are full then overwrite oldest packet. If this causes a problem then
// a player will have to initiate a resynch

						if (ReservePackets[n].NumEntries()==_DPlay.BufferSize)
						{
							ReservePackets[n].GetCurr()->IDCode=DPlay::PIDC_PACKETERROR;
							ReservePackets[n].UpdateCurr();
							Log("BUFFER FULL - overwrite old entry ");
						}

						CopyMemory(ReservePackets[n].GetNext(),Buffer,BufferLen);
						ReservePackets[n].AddEntryAndUpdateNext();
						Log("BUFFER packet (entries=%d)\n",ReservePackets[n].NumEntries());
					}
				}
#ifndef NDEBUG
				else
				{
// who cares - not a player
					if (from==0)
						Log("system message ignored (of acpacket size!!)\n");
					else
						Log("acpacket from illegal player ignored\n");
				}
#endif
			}
		}
	}
	while (res==DP_OK);

	Log("END RECEIVE LOOP\n");
}

void	Aggregator::MakeAndSendAggPacket()
{
	LPACPACKET RecPacket;
	ULong	n,m;
	ULong oldrecbits;
	bool	SendResult;

	do
	{
		Log("SEND LOOP\n");

		for (n=0;n<MAXPLAYERS;n++)
		{
			if (!(RecBits&(1<<n)) && ReservePackets[n].NumEntries()>0)
			{
// if we havent got a packet for this player yet and there is one in buffer......

				RecPacket=ReservePackets[n].GetCurr();
						
// wahay, a needed packet...maybe

				bool latencycatch=false;

				if (!buffer)
				{
// still require dummy/init packets in frame order

					Bool gotOK=FALSE;

					do
					{
						RecPacket=ReservePackets[n].GetCurr();

						if (RecPacket->Count==AggFrameCount)
						{
// if we have found packet for this frame copy and continue

							RecBits|=(1<<n);

							CopyMemory(&allpackets.player[n],RecPacket,sizeof(ACPACKET));

							gotOK=TRUE;
						}
						else
						{
// if this packet is wrong check buffer until dummy/init packets are exhausted

							if (ReservePackets[n].GetCurr()->Count==AggFrameCount+1
							&& 	ReservePackets[n].GetCurr()->IDCode==DPlay::PIDC_INITPACK)
							{
// ok, if we are in INITPACK and this packet is actually the next one we want then it is 
// likely that the player who sent this packet has increased his frame count due to there being 
// exactly 6 frames between sending his packet and getting in OK, meaning he will update
// his frame count unnecessarily, so we actually want this packet!!!
// blimey

								latencycatch=true;
								gotOK=TRUE;
							}
							else
							{
								ReservePackets[n].SetTempCurr();
								ReservePackets[n].UpdateTemp();

								if (ReservePackets[n].GetTemp()->IDCode==DPlay::PIDC_DUMMYPACKET
								|| ReservePackets[n].GetTemp()->IDCode==DPlay::PIDC_INITPACK)
								{
									ReservePackets[n].GetCurr()->IDCode=DPlay::PIDC_PACKETERROR;
									ReservePackets[n].UpdateCurr();
								}
								else
								{
	// no more dummy packets
									gotOK=TRUE;
								}
							}
						}
					}
					while (!gotOK);
				}
				else
				{
// we are in 'real packet mode' dont care what frame count on packet is......

					RecBits|=(1<<n);

					CopyMemory(&allpackets.player[n],RecPacket,sizeof(ACPACKET));
				}
				if (!latencycatch)
				{
					ReservePackets[n].GetCurr()->IDCode=DPlay::PIDC_PACKETERROR;
					ReservePackets[n].UpdateCurr();
				}
			}
		}

// is it time to send packet

		oldrecbits=RecBits;

//if a player drops out then for this frame recbits may have that players
//bit set. If use >= then this doesnt matter!
// NO. need to be equal, its bits set not number of players
		if (time==_DPlay.RateDivider || RecBits==_DPlay.ActivePlayers)
		{
			if (time==_DPlay.RateDivider)
			{
				time=0;
			}

#ifdef AGGLOGS
			if (RecBits==_DPlay.ActivePlayers)
				Log("%d: got allpacks\n",AggFrameCount);
			else
				Log("%d: time out\n",AggFrameCount);
#endif
			allpackets.Count=AggFrameCount;

			if (buffer)
			{
// hey, if we're already synched dont send any agregated packets that are empty....

				if (RecBits!=0)
				{
					SendResult=MakeAndSendPacket(&allpackets,buffer);

					SetAcks();

					AggBuffer.AddEntryAndUpdateNext();

#ifdef AGGLOGS
					if (SendResult)
						Log("sent and buffered %d OK p0=%d p1=%d\n",AggFrameCount,
							allpackets.player[0].Count,allpackets.player[1].Count);
					else
						Log("error sending %d\n",AggFrameCount);
#endif
				}
				else
				{
					Log("EMPTY AGG PACKET\n");
				}
			}
			else
			{
// not synched yet, gotta send every 1/50th - even empty packets
// well, not every 1/50th, every send frame!

				SendResult=MakeAndSendPacket(&allpackets,buffer);
				
#ifdef AGGLOGS
				if (SendResult)
			  		Log("sent %d OK\n",AggFrameCount);
				else
			  		Log("error sending %d\n",AggFrameCount);
#endif
				m=0;
				for (n=0;n<MAXPLAYERS;n++)
				{
					if (allpackets.player[n].IDCode==DPlay::PIDC_INITPACK)
					{
						m++;
					}
 				}

				if (m==_DPlay.CurrPlayers)
				{
					Log("EVERYBODY IS READY- START BUFFERS!!!\n",n);
					buffer=TRUE;
					clearbuffertime=0;
				}
			}

			RecBits=0;
			AggFrameCount++;

// when all players are synched and acking packets, treat AggFrame 0 as an empty packet
// so that when a player sends ack 0 it doesnt update buffers

			if (buffer && !AggFrameCount)
				AggFrameCount=1;

			InitAggArrayBuffer();
		}
	}
	while (oldrecbits==_DPlay.ActivePlayers && buffer && false);
}

void	Aggregator::Log(const char *fmt, ...)
{
#ifdef AGGLOGS
	static	char String [256];
	va_list	marker;

	va_start(marker, fmt);
	vsprintf(String, fmt, marker);

	FILE* fp=fopen("aggspack.txt","at");
	fprintf(fp,"%s",String);
	fclose(fp);
#endif
}

bool	Aggregator::BurstInBuffer()
{
	ULong n;
	bool ok=false;

	for (n=0;n<MAXPLAYERS;n++)
	{
		if (_DPlay.ActivePlayers&1<<n)
		{
			if (ReservePackets[n].NumEntries()>2)
			{
				ok=true;
				break;
			}
		}
	}

	return ok;
}

UByte	Aggregator::GetAggFrameCount()
{
	return AggFrameCount;
}

CON		Aggregator::Aggregator()
{
 	AggFrameCount=0;
	RecBits = 0;
	Running=FALSE;
	ResetFlag=false;
	AggPacketPtr=NULL;
	AggPacketLength=0;
	buffer=FALSE;
	time=0;
	clearbuffertime=0;
}

CON		Aggregator::~Aggregator()
{
	delete [] AggPacketPtr;
	AggPacketPtr=NULL;
	AggPacketLength=0;
}
