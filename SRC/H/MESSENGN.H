//------------------------------------------------------------------------------
//Filename       messengn.h
//System         
//Author         Robert Slater
//Date           Tue 26 Jan 1999
//Description    
//------------------------------------------------------------------------------
#ifndef	MESSENGN_Included
#define	MESSENGN_Included

#define	DEFAULT_MESSENGN 0

//DeadCode RJS 29Sep00 #include	"palette.h"


class	MESSAGE_STRUC;
class	CString;
struct	PhraseBuffer;
class	Sound;															//RJS 29Sep00


class	MessageBuffer
{
	friend class	Sound;												//RJS 29Sep00

	enum	BufferStuffer
	{
		OLDBUFFERSIZE = 50,
		NEWBUFFERSIZE = 30,
		INVALIDMSG = -1,
		INNEWBUFFERFLAG = 64
	};

public:

	CString		*lateststring;									//RJS 14Jun99

	MessageBuffer();
	~MessageBuffer();

	MESSAGE_STRUC*			SayNextMessage(SLong&);
	MESSAGE_STRUC*			CurrMessage();
	void					InitMessageWindow();
	Bool					IncMessageWindow();
	Bool					DecMessageWindow();
//DeadCode RJS 29Sep00 	Colour					MessageColour(SLong);
	CString					Callsign(SLong);
	CString					MessageBody(SLong);
	void					MessageParticipants(SLong,AirStrucPtr&,AirStrucPtr&,itemptr&);
	void					ReSpeakDispMsg();
	void					SetPlayer(AirStrucPtr,AirStrucPtr);
	void					PhraseToString(CString&,PhraseBuffer&);
	Bool					AddToBuffer(const MESSAGE_STRUC&);
	CString					GetPlaceName(Coords3D&);
	CString					GetPlaceName(UWord);
	bool					thereIsANewMessage;
	void					FakePhraseToString(CString&,PhraseBuffer&);//RJS 22Feb99
	void					ClearMessagesMsg(SLong);			//RJS 03Jun99
	void					ClearMessagesPri(SLong);			//RJS 03Jun99
	void					ExpandDirect(const MESSAGE_STRUC&);	//RJS 14Jun99
	void					ClearMessagesMsg(SLong,ItemPtr);	//RJS 14Jun99
	bool ShouldHearMsg(const MESSAGE_STRUC&,Bool&);				//RJS 02May00
	
	bool					nothingatall;						//RDH 01Apr99

	SLong			noBufferedMessages;							//RJS 28May99

protected:

	void					ClearRadio();								//RJS 29Sep00

private:

	MESSAGE_STRUC	*oldbuffer;	//said messages...
	MESSAGE_STRUC	*newbuffer;	//unsaid messages...

	SLong			oldbuffertop;
	SLong			oldbufferbot;
	SLong			newbuffertop;
	SLong			newbufferbot;

	AirStrucPtr		thePlayer,theOtherOne;									//RJS 27Jan99

	//3 message lines...
	// ... notted or flagged = new buffer

	SLong			prevdisplayedmsgindex;
	SLong			displayedmsgindex;
	SLong			nextdisplayedmsgindex;


	SLong			RemoveGaps(MESSAGE_STRUC*,SLong&,SLong);
	void			BufferInit();								//RDH 01Apr99

//DeadCode RJS 12Feb99 	static ULong	PhraseToIDS[];

};

extern	MessageBuffer	_MsgBuffer;



#endif
