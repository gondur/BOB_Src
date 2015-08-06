//------------------------------------------------------------------------------
//Filename       rchatter.h
//System         
//Author         Robert Slater
//Date           Mon 1 Jun 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	RCHATTER_Included
#define	RCHATTER_Included

#define	DEFAULT_RCHATTER 0

#include	"rchatxtr.h"
#include	"raddef.h"
#include	"radio.g"
#include	"radiocht.h"										//RJS 27Mar00

#define	MaxPhrases	48											//RJS 08Dec99
#define	MaxSamples	128
#define	PHRASETYPE_MASK = 0xFF00
#define PHRASEELEMENT_MASK = 0xFF
#define SCRIPT_MASK	= 0xFF0000
#define	TIME_TIMEOUT	800									//RJS 05May99

#ifndef NDEBUG															//CSB 4Jul00
//#define CHATTERTRACE
#endif																	//CSB 4Jul00

class	CString;
struct	RadioOnz;												//RJS 20Jan00
struct	RadioSampleRec;
typedef	SIMPLEWAVHEADER	*SWAV_P;
class	ViewPoint;											//RJS 11May99
enum	SquadNum;
enum	PlaneTypeSelect;
struct	SampListType
{
	UByteP	address;
	int		size:31,											//RJS 13May99
			noCrossFade:1;										//RJS 13May99
};

typedef struct	TargetIndexes									//RJS 13Jan99
{
	mutable	SWord	targettype,
					targetname,
					targetmovement,
					targetdirection,   //THIS IS A ROWAN ANGLE!!!!
					weaponset,									//RJS 22Mar99
					usermessage;								//RJS 22Mar99
	mutable	SLong	targetheight;								//RJS 01Jun99

	TargetIndexes()
	{
		targettype = 0;
		targetname = 0;
		targetmovement = 0;
		targetdirection = 0;
		weaponset = 0;
		usermessage = 0;
		targetheight = 0;										//RJS 01Jun99
	}

	TargetIndexes(SWord	ttype, SWord tname, SWord tmove, SWord tdir, SWord weapset)
	{
		targettype = ttype;
		targetname = tname;
		targetmovement = tmove;
		targetdirection = tdir;
		weaponset = weapset;
		targetheight = 0;										//RJS 01Jun99
	}

	TargetIndexes(SWord	usermsg)
	{
		targettype = 0;
		targetname = 0;
		targetmovement = 0;
		targetdirection = 0;
		weaponset = 0;
		usermessage = usermsg;
		targetheight = 0;										//RJS 01Jun99
	}
	//This TI system will be used heavily on the map screen to represent
	//squadrons that have not taken off, and numbers that can't be printed other ways
	TargetIndexes(SquadNum sq,int numac=0)
	{
		targetname=sq;		//squadron	> SQ_BR_START or > SQ_LW_START
		targetheight=numac;	//number in squadron
	}
	TargetIndexes(PlaneTypeSelect pt,int level)
	{
		targettype=PHRASE_ONE_AIRCRAFT+pt+1;	//aircraft type (generate phrase_ here)
		targetheight=level;	//number in squadron
	}
	void	Init(SWord	ttype, SWord tname, SWord tmove, SWord tdir, SWord weapset)
	{
		targettype = ttype;
		targetname = tname;
		targetmovement = tmove;
		targetdirection = tdir;
		weaponset = weapset;
		targetheight = 0;										//RJS 01Jun99
	}
	const TargetIndexes& SetType(SWord v)	const	{targettype = v;	return *this;}
	const TargetIndexes& SetName(SWord v)	const	{targetname = v;	return *this;}
	const TargetIndexes& SetMove(SWord v)	const	{targetmovement = v;return *this;}
	const TargetIndexes& SetDir (SWord v)	const	{targetdirection = v;return *this;}
	const TargetIndexes& SetWeap(SWord v)	const	{weaponset = v;		return *this;}

	const TargetIndexes& SetWeap(AirStrucPtr v) const;
	const TargetIndexes& SetOneWeap(AirStrucPtr v) const;
	const TargetIndexes& SetDir(ItemBasePtr from,ItemBasePtr delta) const;
	const TargetIndexes& SetHeight(SLong v)	const	{targetheight = v;		return *this;}//RJS 01Jun99
}
TARGET_INDEXES;													//RJS 13Jan99

struct	PhraseBuffer									//RJS 11Feb99
{
	SLong	phrase_buffer[MaxPhrases];
#ifdef	CHATTERTRACE
	SLong	master_phrase[MaxPhrases];
#endif
	SWord	phrase_count;

	PhraseBuffer()
	{
		phrase_count = 0;
	}
};

enum	MsgPriority
{
	GAP = 0,
	PRI_LOW,
	PRI_MED,
	PRI_MEDMAX,
	PRI_MAX
};

enum	VoiceState
{
	VOXSTATE_NORMAL = 0,
	VOXSTATE_EXCITED
};

enum	MsgVisibility
{
	VIS_1 = 0,	 //allow rpt, but not in old buffer
	VIS_2,		// allow rpt, buffer regardless
	VIS_3,		// block rpt, discard if buffered
	NOTVIS_1,	// block rpt, buffered
	NOTVIS_2,	// allow rpt, not buffered
	NOTVIS_3	// allow rpt before said
};

//These voices must be in sync with the directories declared in master.fil
enum	VoiceType
{
	VOICE_PLAYER = 0,			//1st real voice				//RJS 17May00
	VOICE_XPLAYER,
	VOICE_LWPLAYER,												//RJS 29Feb00
	VOICE_LWXPLAYER,											//RJS 29Feb00
	VOICE_REST,
	VOICE_XREST,
	VOICE_LWREST,												//RJS 29Feb00
	VOICE_LWXREST,												//RJS 29Feb00
	VOICE_GROUND,												//RJS 29Feb00
	VOICE_DENTIST = VOICE_GROUND,
 	VOICE_GROUND2,												//RJS 10May00
	VOICE_FEMALE,												//RJS 29Feb00
	VOICE_TOWER,												//RJS 29Feb00
	VOICE_LWTOWER,												//RJS 29Feb00
	VOICE_VOICE2,												//RJS 29Feb00
	VOICE_LWVOICE2,												//RJS 21Aug00
//DeadCode RJS 11Sep00 	VOICE_DENTIST = VOICE_GROUND,								//RJS 10May00
	VOICE_ANY,													//RJS 21Aug00
	VOICE_MAX,													//RJS 08Jun99
	VOICE_SILENT = 31,													//RJS 11Oct00
	VOICE_SUPERMAX													//RJS 11Oct00
};

enum		MsgType
{
	MSG_DELAY = 0x100,			//RJS 22Mar99
	MSG_REPEAT = 0x200,
	MSG_LP = 0x400,
	MSG_COMMS = 0x800,											//RDH 12Apr99
	MSG_HIPRIORITY_X = 0x1000,									//RJS 13May99
	MSG_MEDHIPRIORITY_X = 0x2000,								//RJS 24Jun99
	MSG_BLOCKCHATTER = 0x4000,									//RJS 06Jul99
	MSG_DONTBUFFER = 0x8000,									//RJS 16Aug00

	MSG_NOMSG = 0,				//RJS 22Mar99
	MSG_ADVISEFACFINISHEDREPLY_X,
	MSG_BANDITCALL_X,
	MSG_DENTISTREPORT_X,
	MSG_DISENGAGE_X,
	MSG_FACCONTACTREPLY_X,
	MSG_FACREMARKREPLY_X,
	MSG_GOHOMEREPLY_X,
	MSG_MAYDAYREPLY_X,
	MSG_NOBANDITCALL_X,
	MSG_PERSONALTHREAT_REPLY_X,
	MSG_STATUSREPORT_REPLY_X,
	MSG_STATUSRESPONSE_X,
	MSG_STATUSRESPONSEREPLY_X,
	MSG_WELCOMECLOSERANGEREPLY_X,
//DeadCode RDH 20May99 	MSG_CLEAR_X,
//DeadCode RJS 13May99 	MSG_HIPRIORITY_X,

	MSG_CLEAR,
	MSG_ADVISEATTACK,
	MSG_ADVISEATTACKREPLY,
	MSG_ADVISEFACBINGO,
	MSG_ADVISEFACWINCHESTER,
	MSG_ASSISTFRIENDLIESUNDERATTACK,
	MSG_ATTACK,
	MSG_BINGOFUEL,
	MSG_BOGEYCALL,
	MSG_BOGEYCALLDENTIST,											  //RDH 24/05/99
	MSG_CHOSENMANOEUVRE,
	MSG_CLEARINGAREA,
//DEADCODE RDH 02/04/99 //	MSG_CLEAR_RPT,
	MSG_CONTRAILSREPORTED,
	MSG_COVERME,
	MSG_CROSSRIVER,
	MSG_DAMAGELEVEL1,
	MSG_DAMAGELEVEL1REPLY,										//RJS 19Mar99
	MSG_DAMAGELEVEL2,
	MSG_DAMAGELEVEL2REPLY,											  //RDH 08/03/99
	//added by rod to get spotted compiled								  //RDH 17/02/99
	MSG_SENDTOINVESTIGATE,
	MSG_SPOTTEDBYOTHERS,
	MSG_SPOTTED,
	MSG_FRIENDLIESUNDERATTACK,
	MSG_SPOTTEDASNEWUNFRIENDLY,
	MSG_FOLLOWME,														  //RDH 02/03/99
	MSG_FRIENDLIESNOTUNDERATTACK,										  //RDH 02/03/99
	MSG_PERSONALTHREAT,													  //RDH 03/03/99
	MSG_STATUSREQUEST,													  //RDH 04/03/99
	MSG_INITIALCOMBAT,													  //RDH 04/03/99
	MSG_INITIALCOMBATINFO,													  //RDH 04/03/99 //DAW 28/04/99
	MSG_MIGREPORTED_REPLY,											  //RDH 04/03/99
	MSG_MIGSCOMING,
	MSG_OUTTURN,													  //RDH 04/03/99
	MSG_TOLDTOBREAK,												  //RDH 04/03/99
	MSG_NOTCLEAR_RPT_DELAY,											  //RDH 05/03/99
	MSG_INITIALCOMBATREPLY,
	MSG_BREAKCALL_REPLY_DELAY,										  //RDH 05/03/99
	MSG_STATUSREPORT,
	MSG_DESCRIBEFRIEND,
	MSG_DESCRIBETARGET,
	MSG_EJECTREPLY,
	MSG_ENOUGHHITS,
	MSG_FACCONTACT_X,
	MSG_FACTOOHOT,
	MSG_FAC_CEASEFIRE,
	MSG_FAC_SAYS_DAMAGE,
	MSG_FAC_SAYS_HIT,
	MSG_FLAKFIRING,
	MSG_FLAKREPORT,
	MSG_FORMATIONFLYING,
	MSG_HEADON,
	MSG_INITIALPOINT,
	MSG_KILLREPORT,
	MSG_KILLREPORTREPLY,
	MSG_LAUNCHMIGSREPORTED,
	MSG_MIGREPORTED,
	MSG_MISSTIMEOUT,
	MSG_MORETARGETS,
	MSG_MOVETOACTIVE,
	MSG_NOMORETARGETSREPLY,
	MSG_PLAYERKILLED_X,
	MSG_SECONDRUN,
	MSG_SEESMOKE,
	MSG_SEESMOKEREPLY,
	MSG_SHOOTHIM,
	MSG_SILENCE,
	MSG_STARTINGTRGTRUN,
	MSG_STATUS,
	MSG_TACTOOHOT,
	MSG_TAKEOFFBRAKEMSG,
	MSG_TAKEOFFREADY,
	MSG_TAKEOFFROLLING,
	MSG_TAKEOFFRUNUP,
	MSG_TOOFAST,
	MSG_WATCHROCKETS,
	MSG_WELCOMECLOSERANGE,
	MSG_WELCOMECLOSERANGEREPLYREPLY,
	MSG_WELCOMELONGRANGE,
	MSG_WELCOMELONGRANGEREPLY,
	MSG_WWALLOC,

	MSG_SPOT,
	MSG_SPOT_REPLY,
	MSG_SPOT_ACTION,
	MSG_TOP_COVER,
	MSG_SPLIT_FORCE,
	MSG_ATTACK_METHOD,
	MSG_INITIAL_COMBAT,
	MSG_WARN_HEADING,
	MSG_NEW_HEADING,
	MSG_NEW_SPEED,

	MSG_WIND_REQUEST,
	MSG_WIND_LOW_REPORT,
	MSG_WIND_HIGH_REPORT,

	MSG_BLOWUPREPORT,											//RDH 18May99
	MSG_BLOWUPREPORTREPLY,										//RDH 18May99
	MSG_COVERMEREPLY,										  //RDH 21/05/99
	MSG_COVERMEREPLYDELAY = MSG_COVERMEREPLY+MSG_DELAY,										  //RDH 21/05/99

	MSG_MEDHIPRIORITY = MSG_MEDHIPRIORITY_X + MSG_REPEAT,		//RJS 24Jun99
	MSG_HIPRIORITY = MSG_HIPRIORITY_X + MSG_REPEAT,					//RJS 02Apr99
	MSG_MIGSCOMING_RPT = MSG_MIGSCOMING +  MSG_REPEAT,
	MSG_ADVISEFACFINISHEDREPLY_DELAY_LP_RPT = MSG_ADVISEFACFINISHEDREPLY_X+MSG_DELAY+MSG_LP+MSG_REPEAT,
	MSG_BANDITCALL_DELAY_LP_RPT = MSG_BANDITCALL_X+MSG_DELAY+MSG_LP+MSG_REPEAT,
	MSG_DENTISTREPORT_REPEAT = MSG_DENTISTREPORT_X+MSG_REPEAT,
	MSG_DISENGAGE_DELAY_LP_RPT = MSG_DISENGAGE_X+MSG_REPEAT + MSG_LP+MSG_DELAY,
	MSG_FACCONTACTREPLY_DELAY_LP_RPT = MSG_FACCONTACTREPLY_X+MSG_DELAY+MSG_LP+MSG_REPEAT,
	MSG_FACREMARKREPLY_DELAY_LP_RPT = MSG_FACREMARKREPLY_X+MSG_DELAY+MSG_LP+MSG_REPEAT, 
	MSG_GOHOMEREPLY_DELAY_LP_RPT = MSG_GOHOMEREPLY_X+MSG_DELAY+MSG_LP+MSG_REPEAT,
	MSG_MAYDAYREPLY_DELAY_RPT = MSG_MAYDAYREPLY_X+MSG_DELAY+MSG_REPEAT,
	MSG_NOBANDITCALL_DELAY_LP_RPT = MSG_NOBANDITCALL_X+MSG_DELAY+MSG_LP+MSG_REPEAT,
	MSG_PERSONALTHREAT_REPLY_DELAY = MSG_PERSONALTHREAT_REPLY_X+MSG_DELAY,
	MSG_STATUSREPORT_REPLY_DELAY = MSG_STATUSREPORT_REPLY_X+MSG_DELAY,
	MSG_STATUSRESPONSE_DELAY_LP_RPT = MSG_STATUSRESPONSE_X+MSG_DELAY+MSG_LP+MSG_REPEAT,
	MSG_STATUSRESPONSEREPLY_DELAY_LP_RPT = MSG_STATUSRESPONSEREPLY_X+MSG_DELAY+MSG_LP+MSG_REPEAT,
	MSG_WELCOMECLOSERANGEREPLY_DELAY_RPT = MSG_WELCOMECLOSERANGEREPLY_X+MSG_DELAY+MSG_REPEAT,
	MSG_FACCONTACT_RPT	=MSG_FACCONTACT_X+MSG_REPEAT,
	MSG_STATUSRESPONSE_RPT = MSG_STATUSRESPONSE_X + MSG_REPEAT,			//CSB 03/03/00
	MSG_FORMATIONFLYING_RPT = MSG_FORMATIONFLYING + MSG_REPEAT,			//CSB 12/04/00
	MSG_INITIALCOMBATINFO_DELAY = MSG_INITIALCOMBATINFO + MSG_DELAY,  //DAW 28/04/99
	MSG_PLAYERKILLED = MSG_COMMS + MSG_PLAYERKILLED_X + MSG_REPEAT,			//RJS 02Apr99
//DeadCode DAW 25Jun99 	MSG_CLEAR_RPT = MSG_CLEAR + MSG_REPEAT						//RJS 02Apr99
	MSG_CLEAR_RPT = MSG_CLEAR + MSG_REPEAT,						//RJS 02Apr99

	MSG_PLAYERDAMAGELEVEL1 = MSG_DAMAGELEVEL1 + MSG_MEDHIPRIORITY_X,
	MSG_PLAYERDAMAGELEVEL2 = MSG_DAMAGELEVEL2 + MSG_MEDHIPRIORITY_X,
	MSG_PLAYERLEAKING = MSG_DAMAGELEVEL2 + MSG_MEDHIPRIORITY_X + MSG_DELAY,
	MSG_PLAYERKILLREPORT = MSG_KILLREPORT + MSG_MEDHIPRIORITY_X,
	MSG_PLAYERBLOWUPREPORT = MSG_BLOWUPREPORT + MSG_MEDHIPRIORITY_X,

	MSG_WIND_REQUEST_RPT = MSG_WIND_REQUEST + MSG_REPEAT,
	MSG_WIND_LOW_REPORT_RPT = MSG_WIND_LOW_REPORT + MSG_REPEAT,
	MSG_WIND_HIGH_REPORT_RPT = MSG_WIND_HIGH_REPORT + MSG_REPEAT
};

enum	FudgePhrases													//RJS 18Sep00
{
	PHRASE_IDSFUDGE = 255*256,
	PHRASE_TEXT_QUIT,
	PHRASE_TEXT_QUITGAME,
	PHRASE_TEXT_EXIT,
	PHRASE_TEXT_CONTINUE,
	PHRASE_TEXT_GAMECONTINUES
};

class	DecisionAI;												//RJS 26Jan99
class	fileblock;

class	MESSAGE_STRUC
{
private:

	mutable	int				scriptno;									//RJS 16Aug00

public:
	TARGET_INDEXES	targetinfo;
	mutable AirStrucPtr			caller;
	mutable ItemBasePtr			target;
	mutable AirStrucPtr			callee;
//DeadCode RJS 10May99  	Bool			addThinkTime;								//RJS 11Feb99
	mutable VoiceType		voiceindex;
	MsgType					messagetype;						//RJS 27Jan99
	mutable DecisionAI*		decisionhandler;
	mutable MsgPriority		priority;
	MsgVisibility	visibility;
	mutable VoiceState		voxstate;							//RJS 21Aug00
	Bool			isComms;									//RJS 22Mar99
	Bool			blockchatter;								//RJS 06Jul99
	mutable UByte	timeout;									//RJS 13May99
	UWord	randomno;											//RJS 15Sep00
#ifndef	NDEBUG
	ULong			messagecnt;									//RJS 15Sep00
#endif


	
	void	SetVoiceType();
	void	ProcessUserMessage();
	void	ChooseScript(int) const;									//RJS 15Sep00
	void	ProcessScript(int);											//RJS 15Sep00

	MESSAGE_STRUC(int scrpt,MsgType mtype,MobileItemPtr from,ItemBasePtr about,AirStrucPtr to);
	MESSAGE_STRUC(int scrpt,MsgType mtype,VoiceType vox,ItemBasePtr about,AirStrucPtr to);
	MESSAGE_STRUC(int scrpt,MsgType mtype,MobileItemPtr from,ItemBasePtr about,AirStrucPtr to,const TARGET_INDEXES& tindex);

	// ... const on end means 'this' is constant...
	// Mutable means even though 'this' is a const, it can change...


	const MESSAGE_STRUC& SetVoice(const VoiceType&) const;
	const MESSAGE_STRUC& SetDecision(DecisionAI*) const;
//DeadCode RJS 04Feb99 	const MESSAGE_STRUC& SetCaller(Bool) const;
	const MESSAGE_STRUC& SetPriority(MsgPriority) const;			//RJS 26Jan99
	const MESSAGE_STRUC& CheckCalleePlayer() const;
	const MESSAGE_STRUC& CheckCallerPlayer() const;
	const MESSAGE_STRUC& CheckTargetPlayer() const;
	const MESSAGE_STRUC& SetScript(int) const;							//RJS 16Aug00
	const MESSAGE_STRUC& SetCaller(MobileItemPtr) const;				//RJS 16Aug00

	const int&	GetScript() const;										//RJS 15Sep00

private:

friend class MessageBuffer;

	MESSAGE_STRUC()
	{
		scriptno = 0;
		caller = NULL;
		target = NULL;
		callee = NULL;
		decisionhandler = NULL;
		priority = GAP;
		timeout = 0;
		visibility = VIS_1;										//RJS 30Jun99
		blockchatter = FALSE;									//RJS 06Jul99
		messagetype = MSG_NOMSG;								//RJS 06Jul99
	}

};

typedef struct	RADIOMESSAGE
{
	mobileitem	*caller;
	mobileitem	*callee;
	mobileitem	*target;
	mobileitem	*target2;										//RJS 12Jan99
	SLong		samplelength;
	SLong		distance;
	SWord		bearing;
	SWord		pitch;
	SLong		relheight;
	Bool		isPlaying;
	SWord		VolScale;										//RJS 14Jan99
	VoiceType	theVoice;										//RJS 27Jan99
	SLong		speed;
	SLong		realheight;
	UWord		theFrequency;									//RJS 06Jul99
	SWord		heading;										//RJS 20Jan00
	bool		usedigits;										//RJS 21Jan00

	UByteP			PlayQueue;
	TargetIndexes	TargetStuff;								//RJS 12Jan99
	Bool			isAudio;									//RJS 12Jan99
	PhraseBuffer	*messbuffptr;								//RJS 12Jan99
	UByte			IsExcited;									//RJS 17Mar99
	UByte			randomvoice;								//RJS 17May99
	Bool			TextNum;									//RJS 18Mar99
	SWord			fakeplaytime;								//RJS 22Mar99

	ULong			masterrandom;								//RDH 04May99


	SLong			samplesize;
	SWord			nophrases;
	SampListType	phraselist[MaxPhrases];
	UByteP			sampleptr;
	RADIOMESSAGE	*next;

	PhraseTables	thePhrase;

	Bool	InitROL();
	void	AddSample(UByteP,int,int);							//RJS 22Mar99
	Bool	BuildMessageAsSamples();							//RJS 22Mar99
	void	AddPhrase(int);										//RJS 22Mar99

	int		Random(int	numbits);								//RDH 04May99

	Bool	FiddleROL();

	void	StripIsPlayer(UWordP&);								//RJS 11May99
	void	StripCaller(UWordP&);								//RJS 11May99
	void	DodgyRandomFix();									//RJS 11May99



public:	
	RADIOMESSAGE(RADIOMESSAGE*&,ItemPtr,ItemPtr,ItemPtr,SWord,const TargetIndexes&,PhraseBuffer*,VoiceType,const bool&);//RJS 17May00

	void	MainStrip(UWordP&);												//RJS 11May99
}
RadioMessage,*RadioMessageP;

typedef struct	SECTORNAME										//RJS 14Jul98
{																//RJS 14Jul98
	UWord	prefix;												//RJS 14Jul98
	UWord	name;												//RJS 14Jul98
	UWord	postfix;											//RJS 14Jul98
}																//RJS 14Jul98
SectorName,*SectorNameP;										//RJS 14Jul98

struct	SNFileType												//RJS 14Jul98
{																//RJS 14Jul98
	fileblock	*theblock;										//RJS 14Jul98
  	SectorNameP	PlaceNames;										//RJS 14Jul98
	SLong		noelements;										//RJS 14Jul98
};																//RJS 14Jul98

struct	ScriptFileType											//RJS 28Jan99
{																//RJS 28Jan99
	fileblock	*theblock;										//RJS 28Jan99
  	ULongP		ScriptTable;									//RJS 28Jan99

	fileblock*	voiceBlock;												//RJS 16Aug00
	ULongP		voicePtr;												//RJS 16Aug00
};


#ifndef	NDEBUG

#define AFX_CDECL __cdecl
typedef char CHAR;
#define CONST               const
typedef CONST CHAR *LPCSTR, *PCSTR;
typedef LPCSTR LPCTSTR;
void AFX_CDECL AfxTrace(LPCTSTR lpszFormat, ...);

#endif

#define	MaxPilots	64													//RJS 8Sep00

class	RadioChatter
{
	RadioSampleRec	radiosamples[MaxSamples][VOICE_MAX];
	RadioMessageP	RootMessPtr;
	SNFileType		theSectors;									//RJS 14Jul98
	PhraseTables	lastPhrase;											//RJS 3Oct00
	Bool			RelativeToPilot;							//RJS 27Jul98
 	SWord			MessageCount;								//RJS 14Jan99

	SLong			timesincelast;								//RJS 27Jan99
	SLong			timesincestart;								//RJS 27Jan99

	ScriptFileType	theScripts;									//RJS 28Jan99

	SLong			windHeightSet;								//RJS 10Feb99
	SLong			windSpeedSet;								//RJS 10Feb99

	Bool			DigRange;									//RJS 18Mar99
	bool			hipriSet;									//RJS 25May99
	bool			lockout;									//RJS 04Jun99

	bool			useAltitude;								//RJS 21Jan00
	bool			in3D;										//RJS 17May00

	SWord			randomvoice[MaxPilots];				//RJS 06Jul99

	bool			samplesAllowed;										//RJS 16Aug00

	ULong			ThrowOutMask[VOICE_SUPERMAX];							//RJS 11Oct00

public:
	CON		RadioChatter();
	DES		~RadioChatter();

	ViewPoint*	View_Point;										//RJS 11May99

	UByte			voicechoiceFAC;								//RJS 17May99
	UByte			voicechoiceTOWER;							//RJS 17May99
	UByte			voicechoiceV2;								//RJS 08Jun99

	UByte	phraseused[2000];									//RJS 24Feb99
	ULong	totmess;
	ULong	phrase_groundcontroller;							//RJS 21Jan00

#ifndef	NDEBUG
	bool		damageMessage;											//RJS 26Jun00
#endif

	void	Init();

	void	ExpandLocation(PhraseBuffer&,ULong);				//RJS 09Mar00
	void	ExpandMessage(PhraseBuffer&,int,UWord&,const TargetIndexes&,ItemPtr,ItemPtr trg=NULL,ItemPtr callee=NULL);//RDH 04May99
	void	ExpandMessage(PhraseBuffer&,const MESSAGE_STRUC&);			//RJS 26Jan99
	void	ExpandCallsign(PhraseBuffer&,ItemPtr,const VoiceType&);//PD 04Mar99
	void	ExpandPlacename(PhraseBuffer&,ItemPtr);					//RJS 12Jan99
	void	ExpandPlacename(PhraseBuffer&	phbuf, UWord place);
	ULong	PhraseToResource(SLong);								//RJS 12Feb99

	void	PlayMessage(const MESSAGE_STRUC&,SLong vol=128,bool isChatter=false);//RJS 14Jun99
//DeadCode RJS 27Jan99 	void	PlayMessage(int,const TargetIndexes&,ItemPtr,ItemPtr trg=NULL,ItemPtr callee=NULL,Bool nocaller=FALSE);//RJS 12Jan99
//DeadCode RJS 27Jan99 	void	PlayMessage(int,ItemPtr,ItemPtr trg=NULL,ItemPtr callee=NULL,Bool nocaller=FALSE);
	void	ProcessMessages(SLong);										//RJS 01Apr99
	Bool	TimeOut();											//RJS 27Jan99
	const MESSAGE_STRUC&	TriggerMsg(const MESSAGE_STRUC&);	//RJS 28Jan99

	void	ProcessVoice(const MESSAGE_STRUC&);							//RJS 16Aug00

	void	PlayAll();											//RJS 22Feb99

	void	Enter3D(bool);										//RJS 17May00

	void	SetUpRandomVoices();								//RJS 17May99

	static	UWord	GetPlaceNum(Coords3D* WPtr,int maxnum=40*64);

	void	ClearMessages(MsgType);								//RJS 03Jun99
	void	ClearMessages(MsgPriority);							//RJS 03Jun99
	void	ClearMessages(MsgType,ItemPtr);						//RJS 14Jun99

	int		MsgInQ();											//RJS 31May99

	void	GetPlaceDesc(Coords3D&,SLong&,SLong&,SLong&);		//RJS 29Feb00
	UWord	GetPlaceUID(Coords3D&);								//RJS 29Feb00
	void	GetRelative(SLong,SLong&,SLong&);					//RJS 29Feb00
	SLong	GetUIDPhrase(SLong);

// For UI Screen...

	bool	MessageFinished();									//RJS 28Mar00
	void	PlayMessage(UWord*,VoiceType);						//RJS 28Mar00
	void	SpeakPhrase(RadioMessageP,int);						//RJS 28Mar00

	void	GetLocationString(CString&,ULong);					//RJS 18May00
	VoiceType	GetVoice(const ScriptTables&, const VoiceType&);//RJS 24Aug00

	void	ScanScript(const MESSAGE_STRUC&);					//RJS 06Sep00

	ULong	PanelPhraseToResource(SLong);								//RJS 18Sep00

	void	ClearOldMessage();												//RJS 29Sep00




private:
	RadioMessageP	CreateMessage(ItemPtr,ItemPtr,ItemPtr,UWord,const TargetIndexes&,VoiceType,PhraseBuffer* fbuffp=NULL,SWord vol=128,VoiceState voxstate=VOXSTATE_NORMAL);//RDH 04May99
	void			ComposeSample(RadioMessageP,int);
	void			DecomposeScript(RadioMessageP,int);
	void			Clear();
	RadioSampleRec	*LoadSample(RadioMessageP,int,int&,int&);
	SectorNameP		GetPlaceName(ItemPtr);
	SectorNameP		GetPlaceName(UWord);
	SectorNameP		LoadSectorNames(SLong);
	void			Message_DecomposeScript(RadioMessageP,int);
	UWordP			GetScript(SLong,RadioMessageP,PhraseTables&);//RJS 12Apr99
	void			ComposeDigitNumber(RadioMessageP,SLong,SWord nodigits=0);
	
	SectorNameP		GetFakePlaceName();
	void			ComposeFakeDigitNumber(RadioMessageP,SLong,SWord nodigits=0);
	void			ComposeFakeSample(RadioMessageP,PhraseTables&);
	RadioOnz*		PhraseFactors(int);
	SLong			GetPlaceBase(SLong);




// Alias calls
//If alias can be generated by front end and handles TI, 
//then the input item parameter must not be expanded to AirStruc 
//until it is definitely needed.

	SLong	AircraftType(RadioMessageP,ItemBasePtr aci);
	SLong	SquadronName(AirStrucPtr);
	SLong	SquadronSectionColour(AirStrucPtr);
	SLong	SquadronSectionNumber(AirStrucPtr);
	void	WindBearingNo(RadioMessageP,bool);
	void	HdgOClock(RadioMessageP);
	void	Num_Height(RadioMessageP,SLong);
	void	Num_Place(RadioMessageP,ItemPtr);
	void	Num_Vector(RadioMessageP,ItemPtr);
	void	Height(RadioMessageP, RadioOnz*);
	void	Airfields(RadioMessageP,ItemPtr);
	void	LargeRanges(RadioMessageP);
	void	SmallRanges(RadioMessageP,bool&);							//RJS 22Aug00
	void	Gen_LargeRanges(RadioMessageP,RadioOnz*);
	void	Gen_SmallRanges(RadioMessageP,RadioOnz*);
	void	ForceSize(RadioMessageP,SLong);
	void	Subject_GUnit(RadioMessageP,ItemPtr);
	SLong	SquadronNumber(RadioMessageP,ItemBasePtr aci);
	SLong	GetForceSize(RadioMessageP);
	void	SayRaidID(RadioMessageP,ItemPtr primary,ItemPtr secondary=NULL);









// Purely as functions...

	void	ONE_AIRCRAFT(RadioMessageP);
	void	SUBJECT_GSQUADRAF(RadioMessageP,AirStrucPtr);
	void	SUBJECT_GWINGRAF(RadioMessageP,AirStrucPtr);
	void	SUBJECT_GLW(RadioMessageP,AirStrucPtr);
	void	SUBJECT_GRAF(RadioMessageP,AirStrucPtr);
	void	SUBJECT_GL(RadioMessageP,AirStrucPtr);
	void	SUBJECT_GFLIGHTRAF(RadioMessageP,AirStrucPtr);
	void	SUBJECT_GSECTIONRAF(RadioMessageP,AirStrucPtr);
	void	PLURAL_AIRCRAFT(RadioMessageP);
	void	SUBJECT_G(RadioMessageP,AirStrucPtr);
	void	SUBJECT_GSQUADLW(RadioMessageP,AirStrucPtr);
	void	DISTUNITS(RadioMessageP,bool);
	void	FIFTIES(RadioMessageP,SLong);
	void	HDGCARDINAL(RadioMessageP,SLong);
	void	NUMBER(RadioMessageP,int);
	void	SQUADNUMBERSHORT(RadioMessageP,ItemBasePtr);
	void	TENS(RadioMessageP,SLong);
	void	THOUSANDUNITS(RadioMessageP);
	void	VOLUMEUNITS(RadioMessageP);
	void	SUBJECT_SN(RadioMessageP,AirStrucPtr);
	void	SUBJECT_GSN(RadioMessageP, AirStrucPtr);
	void	SUBJECT_GSQUAD(RadioMessageP,AirStrucPtr);



// Used by phrases...

	void	CALLEE_SN(RadioMessageP);
	void	CALLEE_S(RadioMessageP);
	void	CALLEE_GFLIGHTRAF(RadioMessageP);
	void	CALLER_GFLIGHTRAF(RadioMessageP);
	void	GROUNDCONTROLLERLW(RadioMessageP);
	void	GROUNDCONTROLLERRAF(RadioMessageP);
	void	CALLEE_GFIGHTERS(RadioMessageP);
	void	ONE_AIRCRAFT_EXCLAIM(RadioMessageP);
	void	PLACENAMES(RadioMessageP,ItemPtr,bool sayRange=true);		//RJS 24Aug00
	void	TRG_RELHEIGHT(RadioMessageP);
	void	TRG_DESC_ESTIMATE(RadioMessageP);
	void	USER_DEFINED(RadioMessageP);
	void	FIGHTERSABOVE(RadioMessageP);
	void	WATCHFORESCORT(RadioMessageP);
	void	GUSTTYPE(RadioMessageP);
	void	BANDITSEX(RadioMessageP);
	void	CALLER_GSECTIONRAF(RadioMessageP);
	void	BEARINGS(RadioMessageP);
	void	BAREBEARINGS(RadioMessageP);
	void	TRG_HEIGHT(RadioMessageP);
	void	FUELLEVEL(RadioMessageP);
	void	TRG_RANGE(RadioMessageP);
	void	TRG_HDGCARDINAL(RadioMessageP);
	void	CALLER_HDGOCLOCK(RadioMessageP);
	void	TRG_NUM_ESTIMATE(RadioMessageP);
	void	RAID_ID(RadioMessageP);
	void	CALLEE_GSN(RadioMessageP);
	void	USER_NAMES(RadioMessageP,ItemPtr);
	void	CALLEE_GSQUAD(RadioMessageP);
	void	CALLER_GL(RadioMessageP);
	void	CALLER_GSQUAD(RadioMessageP);
	void	CALLER_GSQUADRAF(RadioMessageP);
	void	CALLER_GWINGRAF(RadioMessageP);
	void	CALLER_GSN(RadioMessageP);
	void	CALLER_SN(RadioMessageP);
	void	COMMSCALLER_SN(RadioMessageP);
	void	TRG_GSN(RadioMessageP);
	void	CALLEE_SQUADNUMBERSHORT(RadioMessageP);
	void	CALLEE_SQUADNUMBERLONG(RadioMessageP);
	void	SQUADNUMBERLONG(RadioMessageP);
	void	PATROL_PLACE(RadioMessageP);
	void	TRG_PLACE(RadioMessageP);
	void	COMMSTARGET(RadioMessageP);
	void	COMMS(RadioMessageP);
	void	CALLER_PLACE(RadioMessageP);
	void	TRG_NEAR(RadioMessageP);
	void	TRG_AC(RadioMessageP);
	void	TRG_1AC(RadioMessageP);
	void	TRG_BOMBERACS(RadioMessageP);
	void	TRG_BOMBER2ACS(RadioMessageP);
	void	TRG_BOMBERAC(RadioMessageP);
	void	SURFACEWINDBEARINGNO(RadioMessageP);
	void	ALTWINDBEARINGNO(RadioMessageP);
	void	WINDSPEED(RadioMessageP);
	void	AREANAMES(RadioMessageP,ItemPtr,bool sayRange=true);		//RJS 24Aug00

// so it will build...

	void	CALLEE_GL(RadioMessageP);
	void	CALLEE_GSECTIONRAF(RadioMessageP);
	void	CALLEE_GSQUADRAF(RadioMessageP);
	void	CALLEE_GWINGRAF(RadioMessageP);

// Unused...
	void	FIGHTERSCLOSE(RadioMessageP);
	void	HEIGHTUNITS(RadioMessageP);
	void	TRG_ANGELS(RadioMessageP);
	void	MY_HDGCARDINAL(RadioMessageP);
	void	TRG_RELCARDINAL(RadioMessageP);
	void	MY_RELCARDINAL(RadioMessageP);
	void	NUM_HDGOCLOCK(RadioMessageP);
	void	CALLEE_GS(RadioMessageP);
	void	TRG_GL(RadioMessageP);
	void	CALLER_NEAR(RadioMessageP);
	void	TRG_MANYAC(RadioMessageP);
	void	TRG_BOMBER2AC(RadioMessageP);
	void	FIGHTERESCORT(RadioMessageP);
	void	TRG_SPEED(RadioMessageP);
	void	TRG_VECTOR(RadioMessageP);



#ifndef	NDEBUG
public:
	RadioChatter& AfxTrace(char* s,int msg)	
	{
		UWord cw=GETFPCW();
#ifdef CHATTERTRACE
		::AfxTrace("Adding: %08x: %s\n",msg,s);
#endif
		SETFPCW(cw);
		return *this;
	}
#endif
};

extern	RadioChatter	_Radio;

#ifndef	NDEBUG
#define	TriggerMsg(param) AfxTrace(#param,_Radio.totmess).TriggerMsg(param)	
#endif

#endif
