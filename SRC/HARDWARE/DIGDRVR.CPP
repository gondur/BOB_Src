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
//Filename       digdrvr.cpp
//System         
//Author         Andy McMaster
//Date           Fri 15 Oct 1999
//Description    
//------------------------------------------------------------------------------

#include	"sample.h"
#include	"digdrvr.h"
#include	"volscale.h"										//RJS 08Nov99
#include	"winmove.h"
#include	"miles.h"
#include	"cguid.h"


//DeadCode RJS 08Nov99 DigitalDriver Dig_Driver;

BOOL CALLBACK DSEnumProc(LPGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName, LPVOID lpContext);

//////////////////////////////////////////////////////////////////////
//
// Function:    Lock
// Date:		20/10/99
// Author:		Macca
//
//Description:	locks the sound driver so that no new sounds can be played
//
//////////////////////////////////////////////////////////////////////
void	DigitalDriver::Lock()
{
	if (!isLocked)
	{
		isLocked = true;
		oldValid = valid;
		valid = false;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Unlock
// Date:		20/10/99
// Author:		Macca
//
//Description: unlocks sound driver and allows new sounds to be played
//
//////////////////////////////////////////////////////////////////////
void	DigitalDriver::Unlock()
{
	if (isLocked)
	{
		isLocked = false;
		valid = oldValid;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    DIG_valid
// Date:		20/10/99
// Author:		Macca
//
//Description:  called by every HSAMPLE function, 1st check.
//
//////////////////////////////////////////////////////////////////////
bool	DigitalDriver::DIG_valid()	
{
	bool	retval = false;
	if (this && valid)
		retval = true;

	return retval;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SampleRate
// Date:		20/10/99
// Author:		Macca
//
//Description:	returns sample rate of primary buffer
//
//////////////////////////////////////////////////////////////////////
int	DigitalDriver::SampleRate()
{
	if (this && valid)
		return samplerate;

	return 0;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Init
// Date:		20/10/99
// Author:		Macca
//
//Description:	initalise direct sound
//
//////////////////////////////////////////////////////////////////////
bool	DigitalDriver::Init(WAVEFORMATEX* wavformat,bool have3dsound, int& maxchannels, int& oldVol)
{
	if (this)
	{
// before init ensure everything is released

		Release();

 		samplerate=wavformat->nSamplesPerSec;
//DeadCode RJS 28Sep00 		nochannels=maxchannels;
		nochannelsused=0;
		using3d=have3dsound;

		if (!InitDSound())
		{
			Release();
			return false;
		}

// create 3dListener AFTER Primary buffer has been set up

//DEADCODE AMM 24/11/99 		if (using3d)
//DEADCODE AMM 24/11/99 		{
//DEADCODE AMM 24/11/99 			if (!Create3DListener())
//DEADCODE AMM 24/11/99 			{
//DEADCODE AMM 24/11/99 				Release();
//DEADCODE AMM 24/11/99 				return false;
//DEADCODE AMM 24/11/99 			}
//DEADCODE AMM 24/11/99 		}

		if (!InitPrimaryBuffer(wavformat,oldVol))
		{
			Release();
			return false;
		}

		if (using3d)
		{
			if (!Create3DListener())
			{
				Release();
				return false;
			}

			if (maxchannels >= max3DSoundBuffers)
				maxchannels = max3DSoundBuffers;
		}
		else
		{
			if (maxchannels >= maxSoundBuffers)
				maxchannels = maxSoundBuffers;
		}

// create some sample objects, as many as wanted. If we cant create the number
// that are requested then fail. Caller will have to decide whether he wants to
// recall function with less required samples.

//DeadCode RJS 10Oct00 		if (maxchannels < CHANNELS_MIN)
		if (maxchannels <= 2)
			maxchannels = CHANNELS_MIN;

		ULong n;

		for (n=0;n<maxchannels;n++)
		{
			channeltable[n]=new Sample(this);

			if (!channeltable[n])
			{
				Release();
				return false;
			}
		}

		nochannels=maxchannels;

		isLocked=false;
		valid=true;
		return true;
	}

	return false;
}


//////////////////////////////////////////////////////////////////////
//
// Function:    AllocateSampleHandle
// Date:		20/10/99
// Author:		Macca
//
//Description:	Returns the first available sample, if none are available
//				then return NULL. It is up to caller then to stop a sample
//				and request again.
//
//////////////////////////////////////////////////////////////////////
Sample*	DigitalDriver::AllocateSampleHandle()
{
	if (DIG_valid())
	{
		if (nochannelsused < nochannels)
		{
			ULong n;

			for (n=0;n<nochannels;n++)
			{
				if (channeltable[n]->SMP_available())
				{
					nochannelsused++;
					return channeltable[n];
				}
			}
		}
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetMasterVolume
// Date:		20/10/99
// Author:		Macca
//
//Description: sets volume of primary buffer
//
//////////////////////////////////////////////////////////////////////
HRESULT	DigitalDriver::SetMasterVolume(int volume)
{
	HRESULT res=DSERR_INVALIDPARAM;

	if (DIG_valid())
	{
		if (lpdsbPrimary)
		{
			res=lpdsbPrimary->SetVolume(GetDecibels(volume));
		}
	}
	return res;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Release
// Date:		20/10/99
// Author:		Macca
//
//Description:	release all direct sound objects
//
//////////////////////////////////////////////////////////////////////
void	DigitalDriver::Release()
{
	if (this)
	{
		valid=false;

// release all secondary buffers first

		ULong n;

//DeadCode RJS 28Sep00 		for (n=0;n<nochannelsused;n++)
		for (n=0;n<nochannels;n++)
		{
			if (channeltable[n])
			{
				channeltable[n]->Release();
				delete channeltable[n];
				channeltable[n]=NULL;
			}
		}

// tidy up primary buffer

		if (lpdsbPrimary)
		{
			lpdsbPrimary->Release();
			lpdsbPrimary=NULL;
		}

// release listener

		if (lpds3dListener)
		{
			lpds3dListener->Release();
			lpds3dListener=NULL;
		}

// finally release DirectSound

		if (lpds)
		{
			lpds->Release();
			lpds=NULL;
		}
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Set3DListener
// Date:		20/10/99
// Author:		Macca
//
//Description:  sets the positon and velocity of the listener in 3d space
//
//////////////////////////////////////////////////////////////////////
HRESULT	DigitalDriver::Set3DListener(const ListenerStruc	&viewpoint)
{
	HRESULT res=DSERR_INVALIDPARAM;

	if (DIG_valid())
	{
		if (lpds3dListener)
		{
			lpds3dListener->SetDopplerFactor(0.4,DS3D_DEFERRED);//RJS 26Sep00

			res=lpds3dListener->SetPosition(viewpoint.x,viewpoint.y,viewpoint.z,DS3D_DEFERRED);

			if (res==DS_OK)
			{
				res=lpds3dListener->SetVelocity(viewpoint.vx,viewpoint.vy,viewpoint.vz,DS3D_DEFERRED);
				if (res==DS_OK)								//RJS 12Jan00
				{
					res=lpds3dListener->SetOrientation(	viewpoint.front_vecx,
														viewpoint.front_vecy,
														viewpoint.front_vecz,
														viewpoint.top_vecx,
														viewpoint.top_vecy,
														viewpoint.top_vecz,
														DS3D_DEFERRED		);
				}
			}
		}
	}
	return res;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    DirectSound_Commit
// Date:		20/10/99
// Author:		Macca
//
//Description:	implement all changes to 3d sounds that were deferred to end of movecycle
//
//////////////////////////////////////////////////////////////////////
void	DigitalDriver::DirectSound_Commit()
{
	if (DIG_valid())
	{
		if (lpds3dListener)
		{
			HRESULT res=lpds3dListener->CommitDeferredSettings();

			if (res!=DS_OK)
			{
				switch (res)
				{
				case DSERR_INVALIDPARAM:
					// tum te tum, knackered pointer
					break;
				default:
					break;
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    InitDSound
// Date:		16/07/99
// Author:		AMM
//
//Description: Create the DirectSound object, establish a cooperative 
//level, and set the primary buffer format.
//
// initialise buffers and flags
//
//////////////////////////////////////////////////////////////////////
bool	DigitalDriver::InitDSound()
{
	EnumerateDSoundDevices();

// Create DirectSound
// guid is the sound device
// use default sound driver for direct sound (guid=NULL)

	if (DirectSoundCreate(pguid,&lpds,NULL)!=DS_OK)
		return false;

	DSCAPS	theCaps;
	theCaps.dwSize = sizeof(DSCAPS);
	if (lpds->GetCaps(&theCaps)==DS_OK)
	{
		maxSoundBuffers = theCaps.dwFreeHwMixingAllBuffers;				//RJS 10Oct00
		max3DSoundBuffers = theCaps.dwFreeHw3DAllBuffers;				//RJS 10Oct00
	}

// set co-op level in order to be able set the format of the primary buffer.If
// default format is not changed the output will be 8-bit, 22Khz format regardless
// of input.

// for maximum compatibility with Roger Wilco, the primary buffer cooperative level
// should be set to DSSCL_PRIORITY or DSSCL_NORMAL

	if (IDirectSound_SetCooperativeLevel(lpds,hwnd,DSSCL_PRIORITY)!=DS_OK)
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    EnumerateDSoundDevices
// Date:		20/10/99
// Author:		Macca
//
//Description:	Find a list of devices that can be used for direct sound
//
//////////////////////////////////////////////////////////////////////
void DigitalDriver::EnumerateDSoundDevices()
{
// Enumerate directsound devices
// values currently unused, but useful to see what windows thinks is installed correctly

	DeletePortList();

	DirectSoundEnumerate((LPDSENUMCALLBACK)DSEnumProc,this);

	AddDefaultDeviceToList();

	LPDSPORTINFO temp=PortInfo;

	while (temp)
	{
// do something with values?

		temp=temp->next;
	}

}

//////////////////////////////////////////////////////////////////////
//
// Function:    InitPrimaryBuffer
// Date:		20/10/99
// Author:		Macca
//
//Description:	Create the primary buffer with default format
//
//////////////////////////////////////////////////////////////////////
bool	DigitalDriver::InitPrimaryBuffer(WAVEFORMATEX*	wfx, int& oldVol)
{
	HRESULT res;

// obtain primary buffer
// for 3d buffer need flags DSBCAPS_CTRL3D

	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));

	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;

	if (using3d)
	{
		dsbdesc.dwFlags|=DSBCAPS_CTRL3D;
		dsbdesc.dwFlags|=DSBCAPS_CTRLVOLUME;
	}
	else
		dsbdesc.dwFlags|=DSBCAPS_CTRLVOLUME;

	if (lpds->CreateSoundBuffer(&dsbdesc, &lpdsbPrimary, NULL)!=DS_OK)
        return false;

// set primary buffer format

	res = lpdsbPrimary->SetFormat(wfx); 

	if (res!=DS_OK)
		return false;

	LONG	theOldVol;
	lpdsbPrimary->GetVolume(&theOldVol);

	oldVol = theOldVol;

	return true;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Create3DListener
// Date:		20/10/99
// Author:		Macca
//
//Description:	create 3dlistener object
//
//////////////////////////////////////////////////////////////////////
bool DigitalDriver::Create3DListener()
{
	HRESULT res;

// Get listener interface

    if FAILED(lpdsbPrimary->QueryInterface(IID_IDirectSound3DListener,(LPVOID *)&lpds3dListener))
    {    
		return false;
    }

// set distance factor with our units, cm, which are 0.01 metres (dsound units)

	res=lpds3dListener->SetDistanceFactor(0.01,DS3D_IMMEDIATE);

	if (res!=DS_OK)
	{
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    DSEnumProc
// Date:		20/10/99
// Author:		Macca
//
//Description:	Callback procedure for enumeration of direct sound devices
//
//////////////////////////////////////////////////////////////////////
BOOL CALLBACK DSEnumProc(LPGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName, LPVOID lpContext)
{
	LPDSPORTINFO portinfo=new DSPORTINFO;
	ZeroMemory(portinfo,sizeof(LPDSPORTINFO));

	if (lpGUID)
		portinfo->port=*lpGUID;
	else
		portinfo->port=GUID_NULL;

	strcpy(portinfo->device,lpszDesc);

	portinfo->next=((DigitalDriver*)lpContext)->PortInfo;
	((DigitalDriver*)lpContext)->PortInfo=portinfo;

	portinfo=NULL;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    DeletePortList
// Date:		20/10/99
// Author:		Macca
//
//Description:	free up list of devices
//
//////////////////////////////////////////////////////////////////////
void DigitalDriver::DeletePortList()
{
	if (this)
	{
		LPDSPORTINFO temp1,temp2;

		temp1=PortInfo;

		while (temp1)
		{
			temp2=temp1->next;
			delete temp1;
			temp1=temp2;
		}
		PortInfo=NULL;
	}
}

void DigitalDriver::Test3DSound()
{
	static SByte tog=50;
	static SByte pos=1;

	if (using3d)
	{
		ULong n;
		SubjectStruc s;

		ZeroMemory(&s,sizeof(SubjectStruc));

		if (!tog--)
		{
			tog=50;
			pos=-pos;
		}

		s.x=pos;
		s.z=pos;

		for (n=0;n<nochannelsused;n++)
		{
			if (channeltable[n]->Status()==DSBSTATUS_PLAYING)
				channeltable[n]->Set3DSource(s);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScaleVol
//Author		Robert Slater
//Date			Mon 8 Nov 1999
//
//Description	Scales linear vol 0 - 511 to decibels * 100.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	DigitalDriver::GetDecibels(int	theVol)
{
	return Vol_Table[theVol & 0x1FF];									//RJS 14Sep00
}

//DeadCode AMM 12Oct00 void	DPlay::CommitDodge()
//DeadCode AMM 12Oct00 {
//DeadCode AMM 12Oct00 	ListenerStruc	l;
//DeadCode AMM 12Oct00 
//DeadCode AMM 12Oct00 	ZeroMemory(&l,sizeof(ListenerStruc));
//DeadCode AMM 12Oct00 
//DeadCode AMM 12Oct00 	_Miles.dig->Set3DListener(l);
//DeadCode AMM 12Oct00 	_Miles.dig->Test3DSound();
//DeadCode AMM 12Oct00 //	_Miles.dig->DirectSound_Commit();
//DeadCode AMM 12Oct00 
//DeadCode AMM 12Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddDefaultDeviceToList
//Author		Andy McMaster
//Date			Mon 29 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void DigitalDriver::AddDefaultDeviceToList()
{
	LPDSPORTINFO portinfo=new DSPORTINFO;
//DeadCode RJS 22Oct00 	LPDSPORTINFO temp=PortInfo;

	strcpy(portinfo->device,"Default");
	portinfo->port=GUID_NULL;
	portinfo->next=PortInfo;
	PortInfo=portinfo;
	portinfo=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitSoundDevice
//Author		Andy McMaster
//Date			Mon 29 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool SaveData::InitSoundDevice(int wh)
{
	if (_Miles.dig && _Miles.dig->DIG_valid())
	{
		if (_Miles.InitUI(wh))
			return true;
	}
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadedSFXDeviceOK
//Author		Andy McMaster
//Date			Mon 29 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool SaveData::LoadedSFXDeviceOK()
{
	if (_Miles.dig && _Miles.dig->DIG_valid())
	{
		LPDSPORTINFO temp=_Miles.dig->PortInfo;

		while (temp)
		{
			if (temp->port==SFXDevice)
			{
				return true;
			}

			temp=temp->next;
		}
	}
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetVolumeDirect
//Author		Robert Slater
//Date			Wed 18 Oct 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
HRESULT	DigitalDriver::SetVolumeDirect(int volume)
{
	HRESULT res=DSERR_INVALIDPARAM;

	if (DIG_valid() && lpdsbPrimary)
		res=lpdsbPrimary->SetVolume(LONG(volume));

	return res;
}
