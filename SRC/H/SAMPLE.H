//------------------------------------------------------------------------------
//Filename       sample.h
//System         
//Author         Andy McMaster
//Date           Mon 11 Oct 1999
//Description    
//------------------------------------------------------------------------------
#ifndef	SAMPLE_Included
#define	SAMPLE_Included

#define	DEFAULT_SAMPLE 0

#include "dsound.h"

#define NUMEVENTSPERCHANNEL 2 
#define NUMCHANNELS	16
#define	SOUNDMAXSAMPLES 256
#define	SOUNDPRIORITYFACTOR 8

#define ALLOCATEDCHANNELS 2


struct	FMT
{
	char  FMT_string[4];
	ULong chunk_size;

	PCMWAVEFORMAT	data;
};

struct RIFF
{
   	SByte RIFF_string[4];
   	ULong chunk_size;
   	SByte  ID_string[4];
   	UByte data[1];
};

struct DATA
{
   	char  DATA_string[4];
   	ULong chunk_size;
   	UByte data[1];
};

enum	PCMDataFormat											//RJS 08Nov99
{
	DIG_F_MONO_8 = 0,		// 8-bit mono sample
	DIG_F_MONO_16,		// 16-bit mono sample
	DIG_F_STEREO_8,		// 8-bit stereo sample
	DIG_F_STEREO_16		// 16-bit stereo sample
};

enum	SMPSTATUS			// current status of a sample handle
{
	SMP_ERROR = -1,
	SMP_DONE = 0,
	SMP_PLAYING,
	SMP_LOST
};

struct	SubjectStruc
{
// position
	D3DVALUE	x;
	D3DVALUE	y;
	D3DVALUE	z;
// velocity
	D3DVALUE	vx;
	D3DVALUE	vy;
	D3DVALUE	vz;
// attenuation settings
	D3DVALUE	mindistance;
	D3DVALUE	maxdistance;
	D3DVALUE	rollofffactor;
// sound direction .......... probably not going to be used
	DWORD		insideconeangle;
	DWORD		outsideconeangle;
	D3DVALUE	cone_vecx;
	D3DVALUE	cone_vecy;
	D3DVALUE	cone_vecz;
	LONG		cone_outsidevol;
// sound volume
	int		volume;

	SubjectStruc(const Coords3D& the_pos,
				const D3DVALUE& the_vx, const D3DVALUE& the_vy, const D3DVALUE& the_vz,
				const int& the_vol, const D3DVALUE& the_mindist, const D3DVALUE& the_maxdist	)
	{
		x = the_pos.X;
		y = the_pos.Y;
		z = the_pos.Z;

		vx = the_vx;
		vy = the_vy;
		vz = the_vz;

		mindistance = the_mindist;
		maxdistance = the_maxdist;

		volume = the_vol;
	}

	SubjectStruc(const Coords3D& the_pos)
	{
		x = the_pos.X;
		y = the_pos.Y;
		z = the_pos.Z;

		vx = vy = vz = 0;

		mindistance = 1000;
		maxdistance = 5000000;

		volume = 511;													//RJS 15Sep00
	}

	SubjectStruc()
	{
		x = 0;
		y = 0;
		z = 0;

		vx = vy = vz = 0;

		mindistance = 1000;
		maxdistance = 5000000;

		volume = 127;
	}

};

struct	ListenerStruc
{
	D3DVALUE	x;
	D3DVALUE	y;
	D3DVALUE	z;
	D3DVALUE	vx;
	D3DVALUE	vy;
	D3DVALUE	vz;
	D3DVALUE	front_vecx;
	D3DVALUE	front_vecy;
	D3DVALUE	front_vecz;
	D3DVALUE	top_vecx;
	D3DVALUE	top_vecy;
	D3DVALUE	top_vecz;
	D3DVALUE	doppler_factor;
	D3DVALUE	rolloff_factor;
};


class DigitalDriver;

class	Sample
{
private:

	DigitalDriver*			driver;	// pointer to driver
	LPDIRECTSOUNDBUFFER 	lpdsb;	// secondary buffer
	LPDIRECTSOUND3DBUFFER	lpds3db;
	UByte				paused:1,	// flags
						isAllocated:1,
						loaded:1;
	UByte				looping;
	int					volume;
	UByte				loopcount;
	bool				Init3d();
	bool				Init(WAVEFORMATEX* wavfileheader, int datasize);
	bool				WriteSampleToBuffer(void* dataptr, int datasize);
	void				DSoundRelease();

public:

// Interface to outside world 

	bool		SMP_available();
	SMPSTATUS	Status();
	void	Release();
	bool	LoadBuffer(PCMWAVEFORMAT& wavformat,void* dataptr, int datasize);	//RJS 13Sep00
	bool	LoadBuffer(PCMDataFormat wavformat, void* dataptr, int datasize);	//alternative to the above.
	HRESULT SetFrequency(int freq);
	HRESULT	SetVolume(int volume);
	HRESULT	SetPan(int pan);
	HRESULT	SetLooping(int loopcount);
	HRESULT	Play();
	HRESULT	Stop();
	HRESULT	End();
	HRESULT	SetPosition(ULong sampleposition);
	HRESULT	GetPosition(ULong& sampleposition);
	HRESULT	Set3DSource(const SubjectStruc	&theSubject);
	bool	SetMaxDistance(float distance);
	bool	SetMinDistance(float distance);

	Sample(DigitalDriver*	drvr)
	{
		lpdsb = NULL;
		lpds3db = NULL;
		driver = drvr;
		looping = 0;
		isAllocated = 0;
		paused = 0;
		loaded = 0;
	}

	~Sample()
	{
		Release();
	}
};

typedef	class Sample *HSAMPLE;

#endif
