//------------------------------------------------------------------------------
//Filename       aggrgtor.h
//System         
//Author         Andy McMaster
//Date           Wed 29 Apr 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	AGGRGTOR_Included
#define	AGGRGTOR_Included

#define	DEFAULT_AGGRGTOR 0

#include	"DOSDefs.h"	
#include	"mytime.h"
#include	"myerror.h"
#include	"dplay.h"
#include	"winmove.h"
#include	"comms.h"
#include	"cbuffer.h"

class Aggregator {

public:
	Aggregator::Aggregator();
	Aggregator::~Aggregator();

//DeadCode AMM 16Nov99 	void 	AggregatorGetPackets(Bool reset,Bool timercall);
	void 	AggregatorGetPackets(); 
	Bool	Running;
	void	StopResetAggregator();
//DEADCODE AMM 24/01/00 	void	ResizeBuffers(ULong);
 	UByte	GetAggFrameCount();
//DeadCode AMM 16Nov99 	UByte	GetAggFrameCount();
//DeadCode AMM 21Aug98  	void	InitRecBits();

//DeadCode AMM 16Nov99 	static int	inaggregator;

private:
	bool	ResetFlag;
	UByte	AggFrameCount;	// aggregators frame count
//DeadCode AMM 16Nov99 	void	SetAcks(LPAGGSENDPACKET packet);
	void	SetAcks();

	CBuffer<AGGBUFF,BUFFERLENGTH> AggBuffer;

// if we receive 2 packets from one player within 1 frame cycle, need to store the 2nd one
// for the next frame. As we have to receive all messages to aggregator at once must buffer
// any bursts of packets.

	CBuffer<ACPACKET, BUFFERLENGTH> ReservePackets[MAXPLAYERS];

//DeadCode AMM 16Nov99 	void	InitAggArrayBuffer(LPAGGSENDPACKET pack);
	void	InitAggArrayBuffer();
	void	InitAggregator();
 	ULong	RecBits;
	void	ResetAcks();
//DeadCode AMM 16Nov99 	void	CheckAck(UByte val, UByte count, UByte pos);
	void	CheckAck(UByte val, UByte pos);
	void	InitReservePackets();
	void	UpdateAckBuffer();

	// 0=not resent, 1=resent 1/4 , 2=resent 1/2
//DeadCode AMM 16Nov99 	UByte	ResendStatus;
//DeadCode AMM 16Nov99 	UByte	ResendPacket;

	char*	AggPacketPtr;
	ULong	AggPacketLength;

	HRESULT	ReceiveMessage(char*&buf, ULong& buflen,ULong& from);

	bool	MakeAndSendPacket(LPAGGSENDPACKET, Bool);
	bool	ResendAggPacket(SLong);

	SLong	RequireResend();
	bool	AllowResendOrBurstCatchUp();

	void	Resend(SLong);
	void	BurstCatchup();
	void	ClearMessageQueue();
	void	Log(const char *, ...);

	Bool	buffer;	// are all players synched. if so buffer packets
	UByte time;	// number of calls by timer, use to determine timeout
	UByte clearbuffertime;;	// try to clear buffers by sending extra agg packets every other agg frame
	AGGSENDPACKET allpackets;	// aggregated packet

	void	GetAllMessages();
	void	MakeAndSendAggPacket();
	bool	BurstInBuffer();
};

extern Aggregator _Agg;


#endif
