//------------------------------------------------------------------------------
//Filename       comms.h
//Date           Mon 23 Sep 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	COMMS_Included
#define	COMMS_Included

#define	DEFAULT_COMMS 0

#define	CHOPPACKETSIZE 500

struct H2HPlayerInfo
{
	ULong	dpid;
	char	name[60];			//name[SaveData::NAMEARRAYSIZE];
	char	squadron;			//0 to 5 of pilotable aircraft, see flyinit.h
	char	position;			//0 to 15 aircraft in flight
	char	dialogue[100];		//dialogue[MAXNUMOFDIALOGUECHARS];
	SWord	status;
	SWord	kills;
	SWord	deaths;
	SWord	assists;
	ULong	MyTeam;				// team number
};

// Fields common to all data packets

typedef struct Generic GENERIC;
typedef struct Generic* LPGENERIC;

struct Generic
{
	ULong	PacketID;	
	ULong	PlayerID;
	ULong	Slot;												//AMM 10Feb97
};


// User Interface Player Details
typedef struct _uiplayerdata UIPLAYERDATA;
typedef struct _uiplayerdata* PUIPLAYERDATA;
struct _uiplayerdata : public Generic
{
	H2HPlayerInfo playerinfo;
};

typedef struct _initinfo INITINFO;
typedef struct _initinfo* PINITINFO;

struct _initinfo : Generic
{
	char	Name[21];
	ULong	ID;
};

typedef struct _password PASSWORDPACK;
typedef struct _password* LPPASSWORDPACK;

struct _password : Generic
{
	char	name[PLAYERNAMELEN];
	char	pword[PASSWORDNAMELEN];
};

typedef struct _slotpos SLOTPOSPACK;
typedef struct _slotpos* LPSLOTPOSPACK;

struct _slotpos : Generic
{
	char	squadron;
	char	position;
};

typedef struct _gamedetails GAMEDETAILS;
typedef struct _gamedetails* LPGAMEDETAILS;

struct _gamedetails : Generic
{
	UByte	DataRate;
	UByte	GameType;
	UByte	GameIndex;
	char	GameName[SESSIONNAMELEN];
};

// this is exact size, want as small packets as possible, no point in
// wasting any bytes

#define CSSIZE 1134

typedef struct _csquickstruc CSQUICKSTRUC;
typedef struct _csquickstruc* LPCSQUICKSTRUC;

struct _csquickstruc : Generic
{
	ULong	newmissionnum;										//AMM 07Dec98
	char	csquick[CHOPPACKETSIZE];
};

typedef struct _savegamep SAVEGAMEPACKET;
typedef struct _savegamep* LPSAVEGAMEPACKET;

struct _savegamep : Generic
{
	ULong	index;
	ULong	size;
	char	data[CHOPPACKETSIZE];
};

typedef struct _csstrucpart CSSTRUCPART;
typedef struct _csstrucpart* LPCSSTRUCPART;

struct _csstrucpart : Generic
{
	ULong	index;
	ULong	size;
	ULong	newmissionnum;
	char	data[CHOPPACKETSIZE];
};

#define COMMSRADIOMESSAGELEN 64

typedef struct _messages MESSAGEPACKET;
typedef struct _messages* LPMESSAGEPACKET;

struct _messages : Generic
{
	char	messages[NUMRADIOMESSAGES+1][COMMSRADIOMESSAGELEN];	// my messages
};

typedef struct _prefs_data UIPREFSDATA;
typedef struct _prefs_data* PUIPREFSDATA;

struct _prefs_data : Generic
{
	FlightDifficultyField	flightdifficulty;
	GameDifficultyField	gamedifficulty;
	TargetSize targetsize;
	SWord	autopilotskillLW;
	SWord	autopilotskillRAF;
	bool	GEffects;
	bool	InjuryEffects;
	bool	WhiteOuts;
	bool	ACNames;
	bool	Clouds;
};

#define CONDSSIZE 131

typedef struct _miss_conds_packet CONDITIONSDATA;
typedef struct _miss_conds_packet* LPCONDITIONSDATA;

struct _miss_conds_packet : Generic
{
	char	conds[CONDSSIZE];
};

typedef struct _gamestuff GAMESTUFF;
typedef struct _gamestuff* LPGAMESTUFF;

struct _gamestuff : Generic
{
	bool 	pwordOK;
	ULong	newslot;
	ULong	groupID;
	ULong	aggID;
};

typedef struct _chat_dialogue CHATDIALOGUE;
typedef struct _chat_dialogue* LPCHATDIALOGUE;

struct _chat_dialogue : Generic
{
	char	chat[64];
};

enum PacketCodes {
	PID_PLAYERUPDATE,		 	// 0x00
	PID_IMHERE,					// 0x01
	PID_PLAYERQUIT,				// 0x02
	PID_MESSAGE,				// 0x03	
 	PID_DATAREQUEST,			// 0x04
	PID_STATUSCHANGE,			// 0x05
	PID_PREFSDATA,				// 0x06
	PID_FLYNOW,					// 0x07
	PID_IAMIN,					// 0x08
	PID_PASSWORD,				// 0x09
	PID_VISITORUPDATE,			// 0x0a
	PID_NEEDRESYNC,				// 0x0b
	PID_PREFSREQUEST,			// 0x0c
	PID_BFIELDREQUEST,			// 0x0d
	PID_SLOTREQUEST,			// 0x0e
	PID_SLOTINFOUPDATE,			// 0x0f
	PID_GAMEDETAILSREQUEST,		// 0x10
	PID_GAMEDETAILSINFO,		// 0x11
	PID_PLAYERINFOREQUEST,		// 0x12
	PID_RESYNC,					// 0x13
	PID_PASSWORDVALID,			// 0x14
	PID_CSQUICKREQUEST,			// 0x15
	PID_HEX16,					// 0x16
	PID_HEX17,					// 0x17
	PID_ACDATA,					// 0x18
	PID_ACANIM,					// 0x19
	PID_MOBDATA,				// 0x1a
	PID_MOBANIM,				// 0x1b
	PID_MESSAGES,				// 0x1c
	PID_MESSAGESREQUEST,		// 0x1d
	PID_GOTWORLD,				// 0x1e
	PID_BFIELDPACKETIDENT,		// 0x1f
	PID_MISSCONDSREQUEST,		// 0x20
	PID_MISSIONCONDITIONS,		// 0x21
	PID_SAVEGAME,				// 0x22
	PID_SAVEGAMEBINARY,			// 0x23
	PID_READYWORLD,				// 0x24
	PID_RESTARTWORLDSYNC,		// 0x25
	PID_GUESTLEAVING,			// 0x26
	PID_NUMDEADBLOCKS,			// 0x27
	PID_DEADBLOCKDATA,			// 0x28
	PID_HOSTLEAVING, 			// 0x29 party pooper  
	PID_SINGLEPILOTSTATUS,		// 0x2a
	PID_ALLPILOTSSTATUS,		// 0x2b
	PID_CAMPAIGNSTRUC,			// 0x2c
	PID_CAMPAIGNSTRUCBINARY,	// 0x2d
	PID_RANDREQUEST,			// 0x2e
	PID_AAAPACKET,				// 0x2f
	PID_RANDOMLIST,				// 0x30
	PID_PLAYERDIALOGUE,			// 0x31 // not used
	PID_UNIQUEID,				// 0x32
	PID_WORLDINFO,				// 0x33
	PID_CSSTRUCINIT,			// 0x34
	PID_CSSTRUCNEW,				// 0x35
	PID_CSSTRUCBINARY,			// 0x36
	PID_ITEMDATA,				// 0x37			
	PID_ITEMANIM,				// 0x38
	PID_NUMACANIMS,				// 0x39
	PID_NUMMOBANIMS,			// 0x3a
	PID_NUMITEMANIMS,			// 0x3b
	PID_IDREQUEST,				// 0x3c	
	PID_ACARRAY,				// 0x3d
	PID_PLAYERLETSGO,			// 0x3e
	PID_HOSTLETSGO				// 0x3f
};

#endif
