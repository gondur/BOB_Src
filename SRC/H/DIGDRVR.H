//------------------------------------------------------------------------------
//Filename       digdrvr.h
//System         
//Author         Andy McMaster
//Date           Fri 15 Oct 1999
//Description    
//------------------------------------------------------------------------------
#ifndef	DIGDRVR_Included
#define	DIGDRVR_Included

#define	DEFAULT_DIGDRVR 0

#include <dsound.h>

class Sample;
struct	ListenerStruc;

typedef struct _dsportinfo DSPORTINFO;
typedef struct _dsportinfo* LPDSPORTINFO;

const	int	CHANNELS_MAX = 32;											//RJS 28Sep00
const	int	CHANNELS_MIN = 16;											//RJS 28Sep00

struct _dsportinfo
{
	LPDSPORTINFO next;
	char device[512];
	GUID port;
//DeadCode AMM 29Nov99 	DWORD	ChannelGroups;
};

class	DigitalDriver
{
	friend class Sample;
	friend class Music;
private:

	LPDIRECTSOUND		lpds;			// Direct Sound object
	DSBUFFERDESC		dsbdesc;		// Buffer description
	LPDIRECTSOUNDBUFFER	lpdsbPrimary;	// Primary buffer
	LPDIRECTSOUND3DLISTENER	lpds3dListener;	// Listener buffer
	HWND 				hwnd;			// Driver's window
	GUID 				*pguid;			// GUID of sound device
	Sample*				channeltable[CHANNELS_MAX];	// Sample Handlers
	int					nochannels;		// Max Sample Handlers
	int					nochannelsused;	// Sample handler count
	bool				valid;		// This driver is valid
	int					samplerate;		// Default sample rate
	bool				using3d;		// Have 3D sound
	bool				isLocked;	// can block all sound calls
	bool				oldValid;	// saved valid, when blocked.
	int					maxSoundBuffers;		//max hardware sound buffers
	int					max3DSoundBuffers;	//max hardware 3D sound buffers

	bool	InitDSound();
	void	EnumerateDSoundDevices();
	bool	InitPrimaryBuffer(WAVEFORMATEX*,int&);
	bool	Create3DListener();
	void	DeletePortList();
	void	AddDefaultDeviceToList();

public:

	LPDSPORTINFO PortInfo;

	HWND	GetWindow() {return hwnd;};
	void	Lock();
	void	Unlock();
	bool	DIG_valid();
	int		SampleRate();
	bool	Is3d() {return using3d;};

// Interface to outside world

	bool	Init(WAVEFORMATEX* wavformat,bool have3dsound, int&, int&);
	Sample*	AllocateSampleHandle();
	HRESULT	SetMasterVolume(int volume);
	HRESULT	SetVolumeDirect(int);										//RJS 18Oct00
	void	Release();
	HRESULT	Set3DListener(const ListenerStruc	&viewpoint);
	void	DirectSound_Commit();
	static  int		GetDecibels(int);									//RJS 13Nov00
	void	Close(DigitalDriver**	memloc)
	{
		DeletePortList();
		*memloc = NULL;
		delete this;
	}

	DigitalDriver(HWND win=NULL,GUID *gui=NULL)
	{
		lpds = NULL;
		lpdsbPrimary = NULL;
		lpds3dListener = NULL;
		hwnd = win;
		pguid = gui;
		valid = false;
		nochannels = 0;
		nochannelsused = 0;
		using3d = false;
		PortInfo=NULL;

		maxSoundBuffers = 16;
		max3DSoundBuffers = 16;
	}

	~DigitalDriver()
	{
		if (this)
			Release();
	}

	void Test3DSound();
};

//DeadCode RJS 08Nov99 extern DigitalDriver Dig_Driver;

#endif
#include "sound.h"
