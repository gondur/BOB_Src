//------------------------------------------------------------------------------
//Filename       winmove.h
//System         
//Date           Fri 9 Aug 1996
//------------------------------------------------------------------------------
#ifndef	WINMOVE_Included
#define	WINMOVE_Included

#define	DEFAULT_WINMOVE 0

#include	"DOSDefs.h"	
#include	"UniqueID.h"
#include	"savegame.h"
#include	"misssub.h"
#include	"cbuffer.h"		//Winmove is included in everything else, so now

// directX stuff

typedef struct IDirectPlay4			*LPDIRECTPLAY4A;  // directX 6.0
typedef struct IDirectPlayLobby3	*LPDIRECTPLAYLOBBY3A; // directX 6.0

#define	RNDPACKETSIZE 57 // random list size + 2

#define BUFFERLENGTH		128
#define HISTBUFFERLENGTH	BUFFERLENGTH*2

#define	NUMRADIOMESSAGES 8
// actual number displayed is this-1 because need spare entry for new chat
#define NUMBUFFEREDMESSAGES 11
#define MAXCOMMSMESSAGESIZE 1064

// packet required for resynch phase, need abs position
// damage state and score

typedef struct _acstatepacket ACSTATEPACKET;
typedef struct _acstatepacket* LPACSTATEPACKET;

struct _acstatepacket {

	ULong		PacketID;

	COORDS3D	Pos;
	ANGLES		Pitch;
	ANGLES		Heading;
	ANGLES		Roll;

	SLong		Velocity; 

	UByte		MyKills;
	UByte		MyAssists;
	UByte		MyDeaths;

	Bool		alive;
	bool		resurrect;
	bool		joining;
};


// new comms ac packet, designed for prediction purposes and wireplay.
// x, y, z, heading, pitch, roll and velocity are deltas from previous
// values.

// first section used for replay as well, dont need any frame or ack info

typedef struct	_basic_packet BASICPACKET;
typedef struct	_basic_packet* LPBASICPACKET;

struct _basic_packet {


	UByte	Shift:4;
	UByte	Bull:4;
	UByte	Velocity_;

	UByte	X;
	UByte	Y;
	UByte	Z;
	UByte	Heading;
	UByte	Pitch;
	UByte	Roll;
	UByte	IDCode;		// 2bits for additional packet type, 6 bits info
	UByte	byte1;		// extra stuff
	UByte	byte2;		// extra stuff
	UByte	byte3;		// extra stuff
	UByte	byte4;		// extra stuff
	UByte	byte5;		// extra stuff
};

#define EXTRASIZE 6

// for comms need frame and ack info

typedef struct _ac_packet ACPACKET;
typedef struct _ac_packet* LPACPACKET;

struct _ac_packet : public _basic_packet
{

	UByte	Count;		// increments every frame
	UByte	Ack1;		
	UByte	Ack2;		

};

// aggregated packet

typedef struct agg_send_packet AGGSENDPACKET;
typedef struct agg_send_packet* LPAGGSENDPACKET;

struct agg_send_packet {
// bit field represents that player is in this packet

	ULong	PlayersInPacket;
	UByte	Count;
	ACPACKET	player[MAXPLAYERS];
};

// packets sent by player to aggregator
// Done indicates packet has been received back OK and processed

typedef struct send_packet_buff SENDPACKETBUFF;
typedef struct send_packet_buff* LPSENDPACKETBUFF;

struct send_packet_buff {
	ACPACKET	packet;
	Bool		Done;
	UByte		ResendStatus;
};

// aggregated packet sent by aggregator with list of 
// who has acked the packet

typedef struct aggsendpackbuff AGGBUFF;
typedef struct aggsendpackbuff* LPAGGBUFF;

struct aggsendpackbuff {

	UByte			NumPlayersInPacket;
	AGGSENDPACKET 	aggpack;
	Bool	Acks[MAXPLAYERS];
	UByte			ResendStatus;
};

// stores ac positions, used with ACPOSENTRY to keep a
// historical record of ac positions for last 50 frames
// this is used in determining AI and AAA actions

typedef struct acposition ACPOSITION;
typedef struct acposition* LPACPOSITION;

struct acposition {

	ONLYFIELD(UWord,UniqueID,ID);
	COORDS3D	Pos;
	ANGLES		Pitch;
	ANGLES		Heading;
	ANGLES		Roll;
	SLong		Velocity;
	UByte		Frame;

};

typedef struct acposentry ACPOSENTRY;
typedef struct acposentry* LPACPOSENTRY;

struct acposentry : public acposition
{
// used for various things, including indicating that 1st AIACposition packet has been sent
// and next one should be 2nd half
	UByte	extrainfo;
	ONLYFIELD(UWord,UniqueID,Unfriendly);
	LPACPOSENTRY next;
};

// list of who has acked which frames, used to determine which is the
// last frame that all players have received and can therefor be used
// for AI and AAA actions

typedef struct ackbuff ACKBUFF;
typedef struct ackbuff* LPACKBUFF;

struct ackbuff {

	UByte	Frame;
	Bool	Acks[MAXPLAYERS];
};

typedef struct idcode IDCODEPACKET;
typedef struct idcode* LPIDCODEPACKET;

struct idcode
{
	UByte IDCode;
};

// information needed to cause a collision

typedef struct _comms_collision COMMSCOLLISION;
typedef struct _comms_collision* LPCOMMSCOLLISION;

// UID hitter	14 bits
// UID hit		14 bits
// HitterInfo	9 bits	(coltype = 3, colstrength = 6)
// HitData		9 bits

struct _comms_collision : idcode
{
	UWord		id;			// 14-bits
	UWord		offset;		// 9-bits											
	UByte		type;		// 3-bits
	UByte		str;		// 6-bits
	UWord		hitterscorer; // 14bits
};

typedef ULong myDPID;
typedef ULong* myLPDPID;

enum MessageCodes {
	PKILLEDBYP=0,YOUCRASHED,YOUCOLLIDEDWITHP,PCRASHED,PCOLLIDEDWITHP,
	KILLEDBYP,KILLEDP,PLEFTGAME,YOUDIED,PDIED,PCHEATED

};

// record of packets sent to aggregator

typedef struct _delta_record DELTARECORD;
typedef struct _delta_record* LPDELTARECORD;

struct _delta_record {

	COORDS3D	lastpos; // SLongs

	ANGLES		Pitch;
	ANGLES		Heading; // (yaw)
	ANGLES		Roll;

	SLong		Velocity;

	UByte		SpecCode;	// as well as deltas need make sure dont lose
							// any kill or resurrect messages etc...
	UByte		byte1;
	UByte		byte2;
	UByte		byte3;

	UByte		Count;
	Bool		Done;
} ;

// received packets

typedef struct _buffer_pack BUFFPACK;
typedef struct _buffer_pack* LPBUFFPACK;

struct _buffer_pack
{
	UByte	Count;

	ACPACKET	PlayerData[MAXPLAYERS];
	Bool 	Received[MAXPLAYERS];

};

typedef struct _hist_buff	HISTBUFF;
typedef struct _hist_buff*	LPHISTBUFF;

struct _hist_buff 
{
// this position has been received ok

	bool		OK;

// historical position

	COORDS3D	Pos;
	ANGLES		Pitch;
	ANGLES		Heading;
	ANGLES		Roll;
	SLong		Velocity; 
	UByte		Frame;

// deltas for recalculating position

	ACPACKET	deltas;
};

// list of packets received, used to ack packets

typedef struct _reclist RECLIST;
typedef struct _reclist* LPRECLIST;

struct _reclist
{
	UByte	packet;
};

// stores bullet/missile/fuel etc launches

typedef struct _bul_entry BULENTRY;
typedef struct _bul_entry* LPBULENTRY;

struct _bul_entry
{
	ULong num;
	ULong index;
	ULong framelaunched;
};

// dplat service provider list

typedef struct _enum_service ENUMSERVICE;
typedef struct _enum_service* LPENUMSERVICE;

struct _enum_service
{
	GUID	sid; 	//service ID
	char*	sname;	//service name
	UByte*	connection;	//connection info buffer
	ULong	connsize;	//connection info buffer size


	LPENUMSERVICE Next;
};

// dplay session list

typedef struct _enum_session ENUMSESSION;
typedef struct _enum_session* LPENUMSESSION;

struct _enum_session
{
	char*	sname;	//service name

	LPENUMSESSION Next;
};

// visitor book information

typedef struct _visitor_info VISITORINFO;
typedef struct _visitor_info* LPVISITORINFO;

struct _visitor_info
{
	char*	vis_name;	// visitors name
	Bool	vis_status;	// set TRUE if visitor can join game
	LPVISITORINFO	next; // next visitor
};

// any other effect that needs transmitting

typedef struct _special_packet SPECPACKET;
typedef struct _special_packet* LPSPECPACKET;

struct _special_packet : idcode
{
	UByte	spec1;
	UByte	spec2;
	UByte	spec3;
	UByte	spec4;
	UByte	spec5;
};

typedef struct	uidpacket UIDPACKET;
typedef struct	uidpacket* LPUIDPACKET;

struct uidpacket : idcode
{
	ONLYFIELD(UWord,UniqueID, uid1);
	ONLYFIELD(UWord,UniqueID, uid2);
};

typedef struct _chatmessage CHATMESSAGE;
typedef struct _chatmessage* LPCHATMESSAGE;

struct _chatmessage
{
	char	chat[128];
	char	name[32];
};

typedef struct _item_info ITEMINFO;
typedef struct _item_info* LPITEMINFO;

struct _item_info
{
	UniqueID item;
	UByteP	 details;
	UByteP	 anim;
	LPITEMINFO next;
};

typedef struct _dead_info DEADINFO;
typedef struct _dead_info* LPDEADINFO;

struct _dead_info
{
	UByteP	block;
	LPDEADINFO next;
};

typedef struct _playersaggcheck PLAYERAGGCHECK;
typedef struct _playersaggcheck* LPPLAYERAGGCHECK;

struct _playersaggcheck
{
	SWord	Frame;					// aggregator frame number
	bool	acked[MAXPLAYERS];		// which players have acked this agg frame
	SWord	whichframe[MAXPLAYERS];	// players frame numbers in agg packet
	UByte	used[MAXPLAYERS];		// this entry has been found and used to process a packet
};

typedef struct dead_pilot DEADPILOT;
typedef struct dead_pilot* LPDEADPILOT;

struct dead_pilot
{
	int	squadron;
	UByte position;
	bool raf;
	LPDEADPILOT next;
};

struct	H2HPlayerInfo;
struct	H2HPlayer;
class	item			;
class	AirStruc		;
typedef item			Item,*ItemPtr,*itemptr;
typedef	AirStruc		*AirStrucPtr;
enum	ShapeNum;
class	MovingItem		;

class DPlay {

public:

	enum	HostPrefs
	{
		AIR2AIR=0,
		GROUND,
		WEAPON,
		ENGINEMAN
	};

	enum	CommsEntryStage
	{
		STAGE_BFIELDS=0,
		STAGE_RANDOMLIST,
		STAGE_MAX
	};

	enum PlayerType
	{
		PLAYER_HOST=1,
		PLAYER_GUEST
	};

	enum PacketIDCodes {

	// 00 top 2 bits indicate 1st part of bullet packet

			PIDC_BULLET=0,

	// 01 top 2 bits indicate coll effect
	// 2 uids, next 2 top bits= type of packet
	// last 4 bits = part of uid

			PIDC_UIDPACKET=64,
			PIDC_SCORECLAIM=64,		// 01000000
			PIDC_WINGMANCOMMAND=80, // 01010000
			PIDC_NEXT=96,			// 01100000
			PIDC_LASTONE=112,		// 01110000				

	// 10 top 2 bits indicate collision packet

			PIDC_COLLISION=128,

	// 11 top 2 bits indicate collision/special packet

			PIDC_RESURRECTEND=192,
			PIDC_RESURRECT=193,
			PIDC_PACKETERROR=194,
			PIDC_INITPACK=195,
			PIDC_DUMMYPACKET=196,
			PIDC_NEARMISS=197,
			PIDC_LANDEDEFFECT=198,
			PIDC_AERODEVICE=199,
			PIDC_DEATHMOVEEFFECT=201,
			PIDC_OWNERCHANGE=202,
			PIDC_EMPTY=203,
			PIDC_KILLLAUNCHER=204,
			PIDC_PLAYERMESSAGE=205,
			PIDC_EJECT=207,
			PIDC_SHAPECHANGE=208,
			PIDC_ACCELGEARUP=209,
			PIDC_NEWWP=210,
			PIDC_SECONDARYAERODEVICES=213,
			PIDC_DONTSEND=214,
			PIDC_ENGINERPM=215,
			PIDC_ENGINEANIM=216,
	// have these last for checking purposes in StorePacket
			PIDC_AIACPOSITION1=253,
			PIDC_AIACPOSITION2=254,
			PIDC_END=255
	};

	enum PacketType {

		PT_BULLET=0,
		PT_UIDS=1,
		PT_COLLISION=2,			
		PT_SPECIAL=3,			
	};

	enum GameTypes {
		DEATHMATCH=0,
		TEAMPLAY, 
		COMMSQUICKMISSION
	};

	enum	TeamSides {
		TS_NONE=0,
		TS_BLUE,
		TS_RED,
		TS_GREEN,
		TS_UNASSIGNED
	};

	enum CommsTimerIDS {

		TIMER_PAINTSHOP=2364,
		TIMER_ACSELECT,
		TIMER_PREFSGAME,
		TIMER_PREFSFLIGHT,
		TIMER_PREFS3D,
		TIMER_PREFS3D2,
		TIMER_PREFSVIEWS,
		TIMER_PREFSCONTROLS,
		TIMER_PREFSOTHERS,
		TIMER_READYROOM,
		TIMER_VISITORS,
		TIMER_MISSIONBRIEF,
		TIMER_FRAG,
		TIMER_RADIO,
		TIMER_MAP,
		TIMER_VARIANTS,
		TIMER_DEBRIEF

	};

	enum CommsPlayerStatus {

		CPS_NONE=0,
		CPS_PAINTSHOP,
		CPS_PREFS,
		CPS_READYROOM,
		CPS_3D,
		CPS_GAMESTARTUP,	// when host has selected fly
		CPS_MAP,
		CPS_VISITORBOOK,
		CPS_MISSIONBRIEF,
		CPS_FRAG,
		CPS_RADIO,
		CPS_JOINING,		// when a player attempts to join 3d
		CPS_RESYNCING,
		CPS_DEBRIEF,
		CPS_VARIANTS

	};

	DPlay::DPlay ();
	DPlay::~DPlay ();

// direct play specific vars

	LPENUMSERVICE	ServiceList; // list of dplay services with names and ids
	LPENUMSESSION	SessionList; // list of dplay session names
	LPDIRECTPLAY4A lpDP4;				// oo look DirectX 6
	LPGUID	lpAppGuid;					// Global GUID Number

	char* tempdpsessdesc2;

	LPDIRECTPLAYLOBBY3A	lpDPL;		//DirectPlay Lobby

	char* templpDPC;

// direct play specific funcs

	Bool	InitDirectPlay ();
	void	ExitDirectPlay();
	Bool UIMultiPlayInit ();	// Main Menu
	Bool UISelectServiceProvider(char* servicename);
	bool UIGetSessionListUpdate ();
	bool UIAssignServices();
	void DeleteServiceList();
	void DeleteSessionList();

// this players data vars

	Bool	PlayerCreated;		// Ok to send messages (Player Created)
	Bool	Implemented;		// DirectPlay/Session/Player Flag
	Bool	Host;				// True if this machine is host, else guest
	ULong	UIPlayerType;		// Host or Guest, for UI Only
	ULong	MyTeamKills;		
	ULong	MyTeamDeaths;
	ULong	EnemyTeamKills;		
	ULong	EnemyTeamDeaths;
	myDPID	aggID;					// aggregator ID
	myDPID	myDPlayID;				//dplay id/wplay id
	ULong	mySlot;	// players position in h2h_player struc, alloc packet
					// aggregated packet etc (everything in fact)
	myDPID	playergroupID;

// make acks buffer bigger to cope with resent packets

	CBuffer<RECLIST,BUFFERLENGTH*2> RecPackBuffer;
	CBuffer<SENDPACKETBUFF,BUFFERLENGTH> SendPackBuffer;

// game data

// circular buffer to store ac packets. 

	CBuffer<BUFFPACK,BUFFERLENGTH> PacketBuffer;

// historical buffer for AAA

	CBuffer<HISTBUFF, HISTBUFFERLENGTH> HistPosBuffer[MAXPLAYERS];

	void	UpdateHistBuffer(LPACPACKET Packet,ULong slot);
	void	AddPacketToHistBuffer(LPACPACKET Packet,ULong slot);

// this frames deltas

	DELTARECORD	Deltas;

// collision stuff

	CBuffer<COMMSCOLLISION,BUFFERLENGTH> CollBuffer;			

	void	NewCollision2 (UWord id, UWord offset, UByte hitbox, UByte typeandstr, UniqueID hitterscorer);	//RJS 19Jun00

// special packet

	CBuffer<SPECPACKET,BUFFERLENGTH> SpecBuffer;				

	void NewSpecial(ULong id,UByte byte1=0, UByte byte2=0, UByte byte3=0, UByte byte4=0, UByte byte5=0);

// bullet stuff

	void	NewBullet (ULong num, ULong index);
	CBuffer<BULENTRY,BUFFERLENGTH> BulletBuffer;	

// for collision effects (killlauncher calls)

	void	NewKillLauncher(UniqueID id);
	void	ProcessKillLauncherPacket(UByteP);

	CBuffer<UIDPACKET,BUFFERLENGTH> UIDSBuffer;		

// UI vars

	Bool 	FlyNowFlag;

	CBuffer<CHATMESSAGE,NUMBUFFEREDMESSAGES> ChatBuffer;

// UI funcs

	Bool UINetworkSelectFly ();
	Bool UINewPlayer (char*,char*);


		#ifdef	MISSSUB_Included
		void UILeavingMainSheet ();
		void UISendDialogue (char*);
		#ifdef	SAVEGAME_Included
		void UIUpdateMainSheet ();
		Bool UISendPrefs (ULong); 
		#endif
		#endif
	SLong GetNextAvailableSlot();
	void	InitH2HPArray();

// general stuff

	bool	viewtime;
	ULong	deadplayers;		// indicates whether player is dead or alive
	Bool	ResyncPhase;
	Bool	WorldSyncPhase;
	bool	WorldSyncPhaseReady;
	Bool	Initiator;
	char 	SessionName [SESSIONNAMELEN];	// Session Name
	char	ServiceName[256];	//serviceprovider
	char	PlayerName[PLAYERNAMELEN];	//players name
	char	Password[PASSWORDNAMELEN];		//password for session
	char	GameName[256];		//name of battlefield
	char	Messages[MAXPLAYERS][NUMRADIOMESSAGES+1][RADIOMESSAGELEN];		
	UByte	RateDivider;		// data rate divider
	UByte	FrameInc;			// same as data rate divider - number of frames in each send/receive cycle
	Bool	firsttimein;		// used to initialise stuff on entry to 3d
	Bool	realfirsttimein;
	Bool	synched;			// true is all players are synched with aggregator
	bool	csync;	// comms is synched
	GameTypes	GameType;			// co-operative/teamplay/deathmatch
	Bool	Side;				// TRUE if UN, FALSE if red
	bool	SideSelected;
	ULong	CurrPlayers;		// No. of players in the session
	ULong AllocPacket [MAXPLAYERS];	// [n]=UniqueID referenced by mySlot
	ULong	SuicideTime;	// time at which suicide is allowed (5 secs after death)
	Bool	AllowSuicide;
	static H2HPlayerInfo H2H_Player[MAXPLAYERS];	// holds info about players
	UByte	FrameCount;		// Frame count (3 csecs)
	ULong ActivePlayers;

	UWord	damageRandom;												
	UWord	effectRandom;												

	Bool SendPacketToAggregator(LPACPACKET lpAcPacket);
	void SendGonePacket();
	void CommitSuicide();
	void InitRecBits ();
	void ResurrectMe (AirStrucPtr ac, bool suicide);
	void SetScore (AirStrucPtr victim, ItemPtr killer);		
	void ResurrectAircraft (AirStrucPtr, Bool);
	void RepairAircraft (AirStrucPtr);
	void InitResurrect (AirStrucPtr);
 	void ProcessPlayerGone(ULong player,Bool in3d); 
	void PredictMove(AirStruc* ac);
	void AddDeltas(AirStruc* AC, Bool sign,UByte);
	UByte 	MakeShiftValue();
	void	SendNeedResyncMessage();
	void	ResetState();
	void	SendResyncMessage();
	void	BeginSyncPhase();
	Bool	ReceiveSyncPackets();
	Bool	CreateDPlayInterface();

	void	PredictGoodMovement(UWord slot);

	Bool	InitSyncPhase();
	Bool	SecondSyncPhase();
	void	InitGameVars();
	void	MakeAndSendPacket();
	void	SetRandomList();
	
	Bool	ProcessPlayerMessage(char* message,ULong size,ULong from);
	Bool	ProcessSystemMessage(char* message);
	
	void ProcessDeltaPacket (LPACPACKET Packet,ULong playerID);
	void ProcessExtraPacket (LPACPACKET Packet,ULong playerID);
	void ProcessExtraPacket (LPACPACKET, AirStrucPtr, ULong);

	void StorePacket (LPAGGSENDPACKET packet);
	void MakeDeltaPacket (LPBASICPACKET packet);
	void MakeExtraPacket (LPBASICPACKET packet, Bool replay);

	void UpdateDeltas(LPACPACKET lpAcPacket);
 	void UpdatePredictedAC(LPACPACKET lpAcPacket);

	UByte	MakeCollPacket(LPBASICPACKET, UByte);
	UByte	MakeUIDSPacket(LPBASICPACKET, UByte);
	UByte	MakeSpecialPacket(LPBASICPACKET, UByte);
	UByte	MakeBulletPacket(LPBASICPACKET, UByte);
	void	MakeSpecialBulletPacket(LPBASICPACKET);
	void	MakeControlSurfacePacket(LPBASICPACKET);

	void	CountPlayers(bool);
	Bool	UISendFlyNow();
	void	InitMainSheetInfo();

	void	ProcessInfoPackets();

	void	SetUpPlayersAC();
	Bool	JoinGame();
	void	AddPlayerToGame(ULong pid,ULong actype,ULong id);

	Bool	Joining;
	void	SendEnteringGameMessage();

// DPID of player to chat to OR, 0=chat to all, 1=chat to myteam

	ULong	sendtowho; 

	void	InitBuffers();
	void	ResetDeltas();

	UByte	ProcessCollisionPacket(UByteP, AirStrucPtr, ULong);
	UByte	ProcessUIDSPacket(UByteP, ULong);
	UByte	ProcessSpecialPacket(UByteP, AirStrucPtr, ULong);
	UByte	ProcessBulletPacket(UByteP, AirStrucPtr);

	SLong	GetVal(UByte src,UByte shift);
	Bool	Lobbied;

	Bool	LaunchedByLobbyCheck();
	Bool	ConnectToLobby();
	Bool	FinishLobbySetup();

	bool	PossibleLobby;

	void	SetRandomListPos();
	Bool	StartCommsSession();
	Bool	SetUpPlayerInfo(char* name);

	LPVISITORINFO	VisitorsBook;
	void	AddNameToVisitorsBook(char* name);
	void	RemoveNameFromVisitorsBook(char* name);
	void	ToggleVisitorStatus(char* name);
	void	SendUpdateToVisitorsBook(char* name,Bool status);

	Bool	PossTransmitColl(ItemPtr item,ItemPtr target,SLong&);

	void	DeleteLobbyInfo();

	Bool	GameRunning;

	void	DeleteVisitorBook();

	void	NewNearMiss(AirStrucPtr trg, AirStrucPtr hitter);
	void	ProcessNearMiss(UByteP);

	void	CheckPassword(char* pword,char* name,ULong player);
	Bool	SetUpPlayer();
	ULong	AttemptToJoin();

	Bool	SlotFree(int pos,int squadron);
	Bool	AllPlayersHaveSlots();

	void	DisplayChatDialogue(char*, char*);
	void	DisplayPlayerInfo();

	UByte	MainSheetCount;
	Bool	ReceiveNextMessageToMe(char*&Data, ULong& Length, ULong& from,ULong flags);
	void	ProcessAggregatedPacket(char* packet);

	void	CopyPacket (AirStrucPtr, LPACPACKET);

	COORDS3D* GetGoodACPosition(ItemBasePtr ac);



	void	NewAeroDevAction(UByte devID,SWord Attractor);
	void	ProcessPlayerSlotRequest(char* message,ULong from);
	Bool	SendSlotRequest(int, int);
	Bool	ReceiveSlotRequestOK();
	void	ProcessSlotInfoUpdate(char* pack);
	Bool	GetGameDetails();
	void	SendGameDetailsRequest();
	Bool	ReceiveGameDetails();
	void	SendGameDetails(ULong);

	UByte	GameIndex;

	void	FillCSQuickStruc();
	Bool	UpdatePlayerInfo();
	bool	SendMyPlayerInfo(bool request);

	void	ResetDeadPlayers(AirStrucPtr ac);

	void	ProcessPrefsPacket(char* pack);

	void	CheckPacketSizes();
	void	GetBattlePosition(UByte slot);
	Bool	JustJoined;
	Bool	LeaveCommsFlag;
	Bool	HostQuitFlag;

	Bool	SwitchPlayerACToAIAC(AirStrucPtr AC);
	Bool	SwitchAIACToPlayerAC(AirStrucPtr AC, ULong slot);
	void	FillHistBuffer(AirStrucPtr ac, ULong slot);
	Bool	SimulateExitKey;
	bool	hitResurrect;

	void	NewWingmanCommand(UByte decision, UByte command, UniqueID trg);
	UByte	ProcessWingmanCommand(UniqueID id1, UniqueID id2, ULong slot);

	void	Process1stAIACPositionPacket(LPACPACKET,UByte);
	void	Process2ndAIACPositionPacket(LPACPACKET,UByte);
	void	Make1stAIACPositionPacket(LPACPACKET p);
	void	Make2ndAIACPositionPacket(LPACPACKET p);
	void	AddAIACToPositionList(AirStrucPtr AC);
	void	DeleteMyAIACPositionToSendList();
	void	UpdateACFromPositionList(LPACPOSENTRY p);

// used when AI AC has finished combat and a position update is being sent to other players. 
// Possibly more than one AC per player - but only one will be sent at a time (but there could
// be bloody packet loss!!)
	LPACPOSENTRY	AIACPositions[MAXPLAYERS];
	void	DeleteAIACPositionsList();
	void	DeleteEntryFromAIACPositionsList(LPACPOSENTRY p,UByte slot);

// list of AI AC that I need to send positions for.
	LPACPOSENTRY	MyAIACPositionsToSend;

	Bool	UpdateFrag;
	Bool	UpdateMission;
	bool	FragChanged;

	void	SendCSQuickStrucToPlayers(Bool init);
	void	UpdateCSQuick(UByte* pack,ULong num);
	void	SendCS(UByte* info, ULong size, Bool init);
	Bool	GetCS();
	void	SendCSRequest();

	void	SendACDetails();
	Bool	GetACDetails();
	void	SendMobDetails();
	Bool	GetMobDetails();
	Bool	SyncCommsWorld();
	void	MakeAnimPack(ULong num,UByteP pack,ShapeNum shape);
	void	ProcessAnimPack(UByteP pack,ItemPtr item);
	Bool	GetNumAnims(ULong type,ULong& num);
	Bool	GetAllAnims(ULong type, ULong need, ULong& got);
	void	SendNumAnims(ULong num,ULong type);
	void	SendAnimData(ULong type,ULong num,UniqueID id);
	Bool	GetSyncData(ULong type,ULong num,ULong& got);
	void	ProcessACData(UByteP pack);
	void	ProcessMobData(UByteP pack);

	bool	SendMyMessages(bool request);
	void	ReceiveMessages(char*,ULong);
	void	SendGotWorldMessage();
	void	SaveRadioMessages();
	Bool	LoadRadioMessages();	
	void	InitMessages();
	bool	UpdateMessages();

	Bool	DisplayInfo;

	void	OwnerChange(ULong newownerid, AirStrucPtr AIAC);
	void	ProcessOwnerChangePacket(UByteP);
	void	InitialiseOwners();
	void	OwnerChangeDecision(AirStrucPtr me, AirStrucPtr him);
	void	SelectPlayerToChatTo(ULong player);
	void	ResetAllocPacket();

	void	ProcessBFieldInfo(char* info,ULong& bfctrl, FileNum& filelist);
	void	SendBFieldsToPlayers(bool request);

	void	ResetCommsGame();
	void	ExitCommsAndReplay3D();
	void	CommsMessage(unsigned int mess);

	Bool	UpdateMissionConditions();
	Bool	SendMissionConditions(bool request);
	void	ProcessConditionsPacket(char* message);

	void	DisplayPlayerJoiningMessage(ULong slot);

	bool	SendSaveGame(bool score, bool startup);
	bool	ReceiveSaveGame(bool startup,ULong num,ULong size);
	void	UpdateSaveGame(UByte* savegamedata,char* data);
	bool	SaveDummyCommsSaveGame(UByte* data,ULong size);

	void	GetCommsSavename(char* b);
	void	GetLastSaveName(char* b);
	bool	LoadDummySavegame(char* name);

	bool	singlesession;// if service provider is serial/modem or tcp
						// then should be only one session to connect to
						// dont bother enumerating sessions
	Bool	JoinComms();
	Bool	FindGoodSession();

	char*	GetPlayerMessage(ULong index);
	char*	GetPlayerName(ULong);		
	ULong	GetPlayerNumber(ULong);		

	inline ULong DPID2Slot(ULong id);
	inline ULong UID2Slot(UWord id);
	ULong	UID_2Slot(UWord id);

	void	ProcessUIDSPacket(LPBASICPACKET p,ULong slot);
	void	NewUIDSPacket(UniqueID id1,UniqueID id2,UByte code);
	void	GetUIDSFromPacket(UniqueID& id1, UniqueID& id2,UByteP);

	struct	SYNCDATA
	{
		bool	resettime;
		bool	sentinfo;
		ULong	wsmneeded;
		ULong	wsmgot;
		UByte	stage;
		ULong	wsrneeded;
		ULong	wsrgot;

		ULong	itemstage;

		ULong	mobstage;

		ULong	acstage;

		ULong	deadstage;
	};

	SYNCDATA	SyncData;
	void	InitSyncData(bool startup);

	void	CalcVels(UByte slot=0,UByte pframes=0);

	UByte	velcounter;

	void	NewPlayerMessage(UByte message);
	void	ProcessPlayerMessagePacket(UByteP,ULong);
	void	DisplayPlayerMessage(ItemPtr victim, ItemPtr hitter, UByte script_type,UByte messnum=0);

	enum	Script_Type
	{
		ST_PLAYERKILLEDCOMMS=0,
		ST_PLAYERKILLEDPLAYER,
		ST_PLAYERKILLEDFRIENDLY,
		ST_PLAYERKILLEDENEMY,
		ST_PLAYERLEFTGAME,
		ST_PLAYERJOINEDGAME,
		ST_PLAYERJOINING,
		ST_PLAYERSELACCEL,
		ST_PLAYERDESELACCEL,
		ST_PLAYERMESSAGE
	};

	ULong	CommsTimeoutLength; // in ms

	bool	MsgRecipientAll;


	bool	CommsGameSync();

	void	ProcessEjectPacket(AirStrucPtr ac);
	void	ProcessGuestLeavingMessage(ULong from);

	void	NewShapePacket(UWord,UWord);						
	void	ProcessNewShapePacket(UByteP);
	UByte	CommsKiller[MAXPLAYERS];
	void	ProcessResyncPacket(LPACSTATEPACKET,ULong);
	UByte	resyncsgot;
	bool	RestartWorldSync;
	void	SendRestartWorldSyncMessage();
	void	SendDeadStream();
	bool	GetDeadStream();
	void	SendACArray();
	bool	GetACArray();
	void	ProcessACArrayPacket(UByte*);
	bool	GetNumDeadBlocks(ULong& num,int& dtime);
	bool	GetAllDeadBlocks(ULong need, ULong& got);

	void	SendPilotsStatus(bool single,ULong reqfrom=0,int sqnum=0, UByte pos=0);
	bool	GetPilotsStatus();
	void	ProcessPilotStatusPacket(bool single,UByteP p,int size);


	char*	CommsPacketPtr;
	ULong	CommsPacketLength;

	bool	SendCampaignStruc(bool startup);
	bool	ReceiveCampaignStruc();

	void	ClearPackages();
	bool	ResetSync;
	bool	resetreceivesync;
	void	InitialFlagReset();

	void	SendAccelGearUpMessage();
	void	ProcessAccelGearUpPacket();

	enum AccelTypeComms
	{
		ACCEL_NONE=0,
		ACCEL_FORWARD,
		ACCEL_NEXTWP,
		ACCEL_MESSAGESUBJECT,
		ACCEL_MISSIONIP,
		ACCEL_HOME,
		ACCEL_WP_NEXTWP,
		ACCEL_WP_HIGHLIGHTED_WP
	};

	AccelTypeComms	AccelComms;

	void	NewWPMessage(UniqueID wp);
	void	ProcessNewWPPacket(UByteP, AirStrucPtr);

	bool	PlayerSync;


	void	SendAAAList();
	bool	GetAAAList();
	void	ProcessAAAPacket(char* packet);
	void	SendBackupRandomList(bool request);
	void	Process_PM_RandomList(char* packet);
	bool	GetRandomList();
	bool	resurrectend;

	SByte	joiningplayerslot;
	void	ResetCommsSurfaces();						

	bool	resyncbar;

	UByte	PacketLength(ULong ID);
	void	ProcessResurrectPacket(AirStrucPtr);
	void	ProcessResurrectEndPacket(AirStrucPtr);
	void	ProcessLandedEffectPacket(UByteP, AirStrucPtr);
	void	ProcessAeroDevicePacket(UByteP, AirStrucPtr);
	void	ProcessDeathMoveEffectPacket(UByteP);
	void	ProcessSpecialBulletPacket(AirStrucPtr);
	void	MakeEmptyPacket(LPBASICPACKET, UByte);
	void	ClearDeadPlayersPackets(UByte);
	void	ExpandAggPacket(LPAGGSENDPACKET, LPAGGSENDPACKET);
	void	ProcessControlSurfacePacket(UByteP);


	void	SendFlyRequest();
	ULong	FlyRequestTimeout;

	void	Process_PM_RandRequest();
	void	Process_PM_PlayerUpdate(char*);
	void	Process_PM_ImHere(char*,ULong);
	bool	Process_PM_PlayerQuit(ULong);
	void	Process_PM_Message(char*);
	void	Process_PM_DataRequest(ULong);
	void	Process_PM_ScreenChange(ULong,ULong);
	void	Process_PM_PrefsData(char*);
	bool	Process_PM_FlyNow();
	void	Process_PM_PlayerLeavingGame(ULong);
	void	Process_PM_IAmIn(char*,ULong);
	void	Process_PM_Password(char*,ULong);
	void	Process_PM_VisitorUpdate(char*);
	bool	Process_PM_NeedResync();
	void	Process_PM_PrefsRequest(ULong);
	void	Process_PM_BfieldsRequest();
	void	Process_PM_CSQuickRequest(ULong);
	void	Process_PM_SaveGame(char*);
	void	Process_PM_Resync(char*,ULong);
	void	Process_PM_CSStruc(char*,bool);

	void	AddChatMessageToBuffer(char*,char*);
	void	UpdateChatBox();
	Bool 	LobbyConnect();

	inline bool	CommsOrReplay();
	void	MoveSurfacesToZero();
	void	MoveSurfaceToZero(int&);
	void	AttemptToProcessExtraPacket();

	void	SendImHereMessage();
	bool	ValidService(char*);

	void	SendStatusChange(ULong);

	UByte	LosePackets;
	UByte	clearbuffertime;
	bool	ReceivePacketWithReRequest(ULong, ULong, char*&, ULong&, ULong);
	bool	TimeoutReceive(ULong, char*&, ULong&);

	void	CheckForResend();
	bool	SpookyGhostMode;

	ULong	BufferSize;


	void	BackupGhost();
	void	BackupSeen();
	void	CheckGhost();
	void	CheckSeen();

	void	UpdateBomberGhost();	
	void	UpdateBomberSeen();		


	DELTARECORD	DeltasToApply[MAXPLAYERS][3];// 3 is max data rate for BoB
	UByte		DeltaIndex;
	void		ApplyPartialDeltas();
	void		AddDeltasToApply(LPACPACKET, ULong);
	void		CalcAndAddPartialDelta(SLong,ULong, ULong);


	void	CheckSendQueue();
	void	ResetAllAIFields(AirStrucPtr);

	void	NewEngineRPMPacket(UWord);					
	void	ProcessEngineRPMPacket(UByteP);

	void	NewEngineAnimPacket();
	void	ProcessEngineAnimPacket(UByteP, ULong);

	bool	SendMessageToGroup(char*, ULong, bool onego=false);
	bool	SendMessageToPlayer(char*, ULong, ULong, bool onego=false);
	bool	SendCommsMessage(char*, ULong, ULong,bool onego=false);
	bool	SendRequestMessage(char* data, ULong, bool onego=false);

	void	ProcessPlayerMessages();

	UByteP	listptr;

// stage with flags representing 
// [x][0] - I done this stage and have info to send
// [x][1] - I have received a request for this info, send as soon as stage done

	bool	CommsStage[STAGE_MAX][2];

	void	WaitForPlayersUniqueIDs();
	void	SendMyUniqueID(UWord);
	void	Process_PM_UniqueID(char*, ULong);
	bool	GotAllPlayersUniqueIDs();
	void	SendIDRequest();
	void	ProcessIDRequest();


	CBuffer<PLAYERAGGCHECK,BUFFERLENGTH> PlayerAggCheck;
	void	AddPacketToCheckBuffer(LPAGGSENDPACKET);

	UWord	BFieldToProcess;
	void	StoreReceivedBField(char*, ULong);
	bool	ProcessRequiredBFieldPacket(ULong& bfctrl, FileNum& filelist);

	void	JumpToWebSite();
	bool	FirstResurrectFrame;

	UByte	HostCollPrefs;
	void	BackupHostPrefs();
	void	RestoreHostPrefs();

	LPDEADPILOT deadpilotlist;
	void	ClearDeadPilots();
	void	NewDeadPilot(int squadron, UByte position);
	bool	IsPilotDead(int squad, UByte pos);
	void	UpdateDeadPilots(AirStrucPtr);
	void	CheckAnimPack(UByteP);
	
	struct	NiceColours
	{
		bool GEffects;
		bool InjuryEffects;
		bool WhiteOuts;
		bool ACNames;
		bool Clouds;
	};

	NiceColours effects;
	void BombCheck(AirStrucPtr);
	bool GetAllGoResponses();
	void SendGoResponse();
	bool GetHostGo();
	void SendHostGo();
	void EmptyAggregatorQueue();
	bool AllPlayersStillReady();

	bool IsThereKillLauncher();
	UByte  MakeKillLauncherPacket(LPBASICPACKET, UByte);
};

extern DPlay _DPlay;

void SendInitPacket ();
void SendInit2Packet ();

#endif
