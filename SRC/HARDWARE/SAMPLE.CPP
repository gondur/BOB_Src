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
//Filename       sample.cpp
//System         
//Author         Andy McMaster
//Date           Mon 11 Oct 1999
//Description    
//------------------------------------------------------------------------------

#include "sample.h"

//////////////////////////////////////////////////////////////////////
//
// Function:    SMP_available
// Date:		20/10/99
// Author:		Macca
//
//Description:  is sample available to be allocated (i.e. unused)
//
//////////////////////////////////////////////////////////////////////
bool Sample::SMP_available() 
{
	if (	!lpdsb
		&&	!isAllocated	)
	{
		isAllocated = true;
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Init
// Date:		20/10/99
// Author:		Macca
//
//Description:  creates direct sound secondary buffer for sample
//				of the correct size and format. If 3d sound has
//				been selected than also create a 3dsound buffer
//
//////////////////////////////////////////////////////////////////////
bool	Sample::Init(WAVEFORMATEX* wavfileheader, int datasize)
{
	bool retval=false;
	bool	using3d = driver->Is3d();				//RJS 09Nov99

	DSBUFFERDESC dsbdesc;

	DSoundRelease();

// set up flags for buffer creation

    ZeroMemory(&dsbdesc,sizeof(DSBUFFERDESC)); 

    dsbdesc.dwSize = sizeof(DSBUFFERDESC); 

    dsbdesc.dwFlags = 
            DSBCAPS_GETCURRENTPOSITION2   // Always a good idea (according to docs)
            | DSBCAPS_GLOBALFOCUS         // Allows background playing
			| DSBCAPS_STATIC				// we know how big sample is so put it into static buffer
			| DSBCAPS_CTRLPOSITIONNOTIFY;	// might as well
//			| DSBCAPS_MUTE3DATMAXDISTANCE ;

// for 3d sound need to specify DSBCAPS_CTRL3D, and DO NOT specify DSBCAPS_CTRLPAN

	if (using3d)
	{
		dsbdesc.dwFlags |= DSBCAPS_MUTE3DATMAXDISTANCE;
		dsbdesc.dwFlags |= DSBCAPS_CTRL3D;
		dsbdesc.dwFlags |= DSBCAPS_CTRLVOLUME;
		dsbdesc.dwFlags |= DSBCAPS_CTRLFREQUENCY;
	}
	else
	{
		dsbdesc.dwFlags |= DSBCAPS_CTRLVOLUME;					//RJS 12Jan00
		dsbdesc.dwFlags |= DSBCAPS_CTRLFREQUENCY;				//RJS 12Jan00
		dsbdesc.dwFlags |= DSBCAPS_CTRLPAN;						//RJS 12Jan00
//DeadCode RJS 12Jan00 		dsbdesc.dwFlags |= DSBCAPS_CTRLDEFAULT ;	// allow control of vol, pan, freq
	}


    dsbdesc.dwBufferBytes = datasize; // size of sample
    dsbdesc.lpwfxFormat = wavfileheader;				// buffer format
 
// IDirectSound::CreateSoundBuffer calls IDirectSoundBuffer::Initialise internally

	HRESULT	res = driver->lpds->CreateSoundBuffer(&dsbdesc, &lpdsb, NULL);
	if (res==DS_OK)
    {
		if (using3d)
		{
// if we have 3d sound then get 3dsound buffer

			if (Init3d())
				retval=true;
		}
		else
		{
			retval=true;
		}
	}

	return retval;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Init3d
// Date:		20/10/99
// Author:		Macca
//
//Description:	Create a 3d cound buffer
//
//////////////////////////////////////////////////////////////////////
bool Sample::Init3d()
{
	HRESULT res;

	res=lpdsb->QueryInterface(
		IID_IDirectSound3DBuffer,
		(LPVOID*)&lpds3db);

	if (res==S_OK)
	{
// when initialising mode can do the change immediately dont need to defer

		res=lpds3db->SetMode(DS3DMODE_NORMAL,DS3D_IMMEDIATE);

		if (res==DS_OK)
		{
			return true;
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Release
// Date:		20/10/99
// Author:		Macca
//
//Description:	Called externally
//
//////////////////////////////////////////////////////////////////////
void	Sample::Release()
{
	DSoundRelease();

	driver=NULL;
	isAllocated=0;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    DSoundRelease
// Date:		09/12/99
// Author:		Rob
//
//Description:	Called internally
//
//////////////////////////////////////////////////////////////////////
void	Sample::DSoundRelease()
{
	if (lpdsb)
	{
		lpdsb->Release();
		lpdsb=NULL;
	}

	if (lpds3db)
	{
		lpds3db->Release();
		lpds3db=NULL;
	}

	loopcount = 0;
	looping=0;
	paused=0;
	loaded=0;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    LoadBuffer
// Date:		20/10/99
// Author:		Macca
//
//Description:	initaliase the buffer and load the sample into it
//
//////////////////////////////////////////////////////////////////////
bool	Sample::LoadBuffer(PCMWAVEFORMAT& wavformat, void* dataptr, int datasize)
{
	if (this)
	{
		WAVEFORMATEX	tmpwf;
		
		*((PCMWAVEFORMAT*)&tmpwf) = wavformat;

		tmpwf.cbSize = 0;
		
// call Init with WAVEFORMATEX

		if (Init(&tmpwf,datasize))
		{
			if (WriteSampleToBuffer(dataptr,datasize))
			{
				return true;
			}
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    LoadBuffer
// Date:		20/10/99
// Author:		Macca
//
//Description:	Create a WAVEFORMATEX structure from drivers sample rate
//				and type of sample to be played, initalise buffer and load
//				sample into it
//
//////////////////////////////////////////////////////////////////////
bool	Sample::LoadBuffer(PCMDataFormat wavformat, void* dataptr, int datasize)
{
// create WAVEFORMATEX from PCMDataFormat

//	DIG_F_MONO_8 = 0,	// 8-bit mono sample
//	DIG_F_MONO_16,		// 16-bit mono sample
//	DIG_F_STEREO_8,		// 8-bit stereo sample
//	DIG_F_STEREO_16		// 16-bit stereo sample

	if (this)
	{
		WAVEFORMATEX wfx;
		ZeroMemory(&wfx, sizeof(WAVEFORMATEX)); 

		wfx.wFormatTag=WAVE_FORMAT_PCM;

		if (wavformat==DIG_F_STEREO_8 || wavformat==DIG_F_STEREO_16)
		{
			wfx.nChannels=2;
		}
		else
		{
			wfx.nChannels=1;
		}

		if (wavformat==DIG_F_MONO_8 || wavformat==DIG_F_STEREO_8)
		{
			wfx.wBitsPerSample=8;
		}
		else
		{
			wfx.wBitsPerSample=16;
		}

		wfx.nSamplesPerSec=driver->SampleRate();

		wfx.nBlockAlign = wfx.wBitsPerSample / 8 * wfx.nChannels;
		wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign; 

	// call Init

		if (Init(&wfx,datasize))
		{
			if (WriteSampleToBuffer(dataptr,datasize))
			{
				return true;
			}
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetVolume
// Date:		20/10/99
// Author:		Macca
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
HRESULT	Sample::SetVolume(int newvolume)
{
	if (lpdsb)
	{
		volume = newvolume;												//RJS 15Sep00
		return (lpdsb->SetVolume(DigitalDriver::GetDecibels(newvolume)));	//RJS 13Nov00
	}
	return DS_OK;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetPan
// Date:		20/10/99
// Author:		Macca
//
//Description:	-511 to 511
//
//////////////////////////////////////////////////////////////////////
HRESULT	Sample::SetPan(int pan)
{
	if (lpdsb)
	{
		bool	leftspeaker = false;
		if (pan)
		{
			if (pan & 0x200)			//is it -'ve					//RJS 14Sep00
			{
				leftspeaker = true;
				pan = -pan;
			}

			pan &= 0x1FF;												//RJS 14Sep00
			pan = 511 - pan;											//RJS 14Sep00
			pan = DigitalDriver::GetDecibels(pan);						//RJS 13Nov00
			if (!leftspeaker)							//RJS 18Jan00
				pan = -pan;
		}

		return (lpdsb->SetPan(pan));
	}
	return DS_OK;
}

HRESULT Sample::SetFrequency(int freq)
{
	if (lpdsb)
	{
		if (freq < 100)
			freq = 100;
		else
		{
			if (freq > 44100)
				freq = 44100;
		}

		return (lpdsb->SetFrequency(freq));
	}
	return DS_OK;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetLooping
// Date:		20/10/99
// Author:		Macca
//
//Description:	0 = infinite, 1..n times
//				in future projects (post BoB) a positive number will
//				represent the number of loops. Will have to implement
//				notification callbacks to do this.
//
//////////////////////////////////////////////////////////////////////
HRESULT	Sample::SetLooping(int loopnum)
{
	if (loopnum)
	{
		if (loopnum == 1)
			loopcount = 0;			//no loop
		else
			loopcount=loopnum;
	}
	else
		loopcount = 1;

	return DS_OK;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Play
// Date:		20/10/99
// Author:		Macca
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
HRESULT	Sample::Play()
{
	if (lpdsb)
	{
		if (loopcount!=0)
			return (lpdsb->Play(0,0,DSBPLAY_LOOPING));
		else
			return (lpdsb->Play(0,0,0));
	}
	return DS_OK;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Stop
// Date:		20/10/99
// Author:		Macca
//
//Description:	When a sample is stopped a Play call will continue the sample
//				from the point at whcih it stopped
//
//////////////////////////////////////////////////////////////////////
HRESULT	Sample::Stop()
{
	if (lpdsb)
	{
		return (lpdsb->Stop());
	}
	return DS_OK;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    End
// Date:		20/10/99
// Author:		Macca
//
//Description:	End causes the sample to stop playing and the start position
//				is returned to the beginning of the sample
//
//////////////////////////////////////////////////////////////////////
HRESULT	Sample::End()
{
	HRESULT res=DS_OK;													//RJS 20Oct00

	if (lpdsb)
	{
		res=lpdsb->Stop();

		if (res==DS_OK)
		{
			res=lpdsb->SetCurrentPosition(0);
		}
	}
	return res;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetPosition
// Date:		20/10/99
// Author:		Macca
//
//Description:	Set the current play position
//
//////////////////////////////////////////////////////////////////////
HRESULT	Sample::SetPosition(ULong sampleposition)
{
	if (lpdsb)
	{
		return (lpdsb->SetCurrentPosition(sampleposition));
	}
	return DS_OK;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    GetPosition
// Date:		20/10/99
// Author:		Macca
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
HRESULT	Sample::GetPosition(ULong& sampleposition)
{
	if (lpdsb)
	{
//DeadCode AMM 22Nov99 		ULong writepos;
//DeadCode AMM 22Nov99 
//DeadCode AMM 22Nov99 		return (lpdsb->GetCurrentPosition(&sampleposition, &writepos));

// write pos can be NULL because we only want read pos

		return (lpdsb->GetCurrentPosition(&sampleposition, NULL));
	}
	sampleposition=0;
	return DS_OK;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Set3DSource
// Date:		20/10/99
// Author:		Macca
//
//Description:	set the source of the sound in 3d space
//
//////////////////////////////////////////////////////////////////////
HRESULT	Sample::Set3DSource(const SubjectStruc	&theSubject)
{
	HRESULT res=DS_OK;

	if (lpds3db)
	{
// defer settings change to after move cycle

		res=lpds3db->SetPosition(theSubject.x,theSubject.y,theSubject.z,DS3D_DEFERRED);

		if (res==DS_OK)
		{
			res=lpds3db->SetVelocity(theSubject.vx,theSubject.vy,theSubject.vz,DS3D_DEFERRED);
			if (res==DS_OK)										//RJS 13Jan00
			{
				res=lpds3db->SetMinDistance(theSubject.mindistance,DS3D_DEFERRED);
				res=lpds3db->SetMaxDistance(theSubject.maxdistance,DS3D_DEFERRED);
			}
		}
	}
	return res;
}


//////////////////////////////////////////////////////////////////////
//
// Function:    WriteSampleToBuffer
// Date:		20/10/99
// Author:		Macca
//
//Description:	lock buffer, write sample data into it and then unlock for use
//
//////////////////////////////////////////////////////////////////////
bool Sample::WriteSampleToBuffer(void* dataptr, int datasize)
{
	HRESULT res;
	VOID            *lpvPtr1, *lpvPtr2;
	DWORD           dwBytes1, dwBytes2;
	bool	retval=false;
		
// must lock buffer before writing to it

	res=lpdsb->Lock(		0,       // Offset of lock start
						datasize,      // Number of bytes to lock
						&lpvPtr1,         // Address of lock start
						&dwBytes1,        // Count of bytes locked
						&lpvPtr2,         // Address of wrap around
						&dwBytes2,        // Count of wrap around bytes
						DSBLOCK_ENTIREBUFFER               // Flags
						);

	if (res==DS_OK)
	{
// write to buffer here

		CopyMemory(lpvPtr1,dataptr,datasize);
		retval=true;
	}

// after writing unlock buffer

	if (lpdsb->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2)!=DS_OK)
	{
		retval=false;
	}

	return retval;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Status
// Date:		20/10/99
// Author:		Macca
//
//Description:	Returns the status of the sample
//
//////////////////////////////////////////////////////////////////////
SMPSTATUS	Sample::Status()
{
	DWORD status;
	HRESULT res;

	if (lpdsb)
	{
		res=lpdsb->GetStatus(&status);

		if (res==DS_OK)
		{
			if (status & DSBSTATUS_BUFFERLOST)
			{
				res=lpdsb->Restore();

				return SMP_LOST;
			}
			else if (status & DSBSTATUS_PLAYING)
			{
				return SMP_PLAYING;
			}
			else
				return SMP_DONE;
		}
	}
	return SMP_ERROR;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetMaxDistance
// Date:		20/10/99
// Author:		Macca
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool	Sample::SetMaxDistance(float distance)
{
	HRESULT res;

	if (lpds3db)
	{
		res=lpds3db->SetMaxDistance(distance,DS3D_IMMEDIATE);

		if (res==DS_OK)
			return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetMinDistance
// Date:		20/10/99
// Author:		Macca
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool	Sample::SetMinDistance(float distance)
{
	HRESULT res;

	if (lpds3db)
	{
		res=lpds3db->SetMinDistance(distance,DS3D_IMMEDIATE);

		if (res==DS_OK)
			return true;
	}
	return false;
}
