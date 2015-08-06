//------------------------------------------------------------------------------
//Filename       music.h
//System         
//Author         Andy McMaster
//Date           Fri 8 Oct 1999
//Description    
//------------------------------------------------------------------------------
#ifndef	MUSIC_Included
#define	MUSIC_Included

#define	DEFAULT_MUSIC 0

#include	"Dmusici.h"
#include	"digdrvr.h"

typedef struct _dmportinfo DMPORTINFO;
typedef struct _dmportinfo* LPDMPORTINFO;

struct _dmportinfo
{
	LPDMPORTINFO next;
	char device[1024];
	GUID port;
	DWORD	ChannelGroups;
};

class Music
{
	int		mastervolume;

public:
	Music::Music();
	Music::~Music();

	bool	Init(DigitalDriver*);
	void	Play(void*,int,bool MusicTest=false);
	void	Stop();
	void	SetMasterVolume(int);
	void	SetVolume(int,int fadetime=0);
	int		GetVolume();
	void	Process();
	bool	CreateAndAddPort(ULong);
	bool	CreateAndAddPort(GUID);
	bool	Playing();
	void	ReleasePort();
	void	Close(Music**	memloc)
	{
		DeletePortList();
		*memloc = NULL;
		delete this;
	}

//DeadCode AMM 22Nov99 	bool	IsMusicDeviceValid();
	bool	AssignDefaultMusicDevice();
	void	TestMusic();
	bool 	ChangeMusicDevice(ULong);

	bool	MDI_valid();


	LPDMPORTINFO PortInfo;
	ULong	index;

private:

// direct music interfaces

	IDirectMusicPerformance*	gpPerf;
	IDirectMusicLoader*			gpLoader;
	IDirectMusicSegment*		gpSegment;
	IDirectMusic*				gpDMusic;
	IDirectMusicPort*			gpPort;

	DigitalDriver*				dig;
	bool						MusicAllowed;
	int							currentvol;
	int							currentfadetime;


	void	CleanUpMusic();

	void	EnumPorts();
	bool	CreateLoader();

	bool	downloaded;

	void	DeletePortList();
	void	AddDefaultPortToList();
	void	AttemptFileOpen(void*,int,bool MusicTest=false);
};


typedef	class Music *HSEQUENCE;

#endif
