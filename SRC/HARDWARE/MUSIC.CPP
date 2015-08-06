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
//Filename       music.cpp
//System         
//Author         Andy McMaster
//Date           Tue 5 Oct 1999
//Description    Everything to do with manipulating a piece of music
//------------------------------------------------------------------------------
//DEADCODE MS 02/02/00 #define		INITGUID

#include	"dosdefs.h"
#include	"music.h"
#include	"digdrvr.h"
//#include	"dmksctrl.h"
#include	"miles.h"

//////////////////////////////////////////////////////////////////////
//
// Function:    InitMusic
// Date:		20/10/99
// Author:		Macca
//
//Description:	set up Direct Music object, performance, loader and 
//				enumerate music devices
//
//////////////////////////////////////////////////////////////////////
bool Music::Init(DigitalDriver* drvr)
{
	if (this && drvr)
	{
		HRESULT res;			

//ensure that a DirectSound object exists, if not then no music

		if (!drvr->lpds)
			return false;

// If an instance already exists, kill it and reset...

		if (MusicAllowed)
			CleanUpMusic();

// set global directmusic performance pointer

		res=CoCreateInstance(
			CLSID_DirectMusicPerformance,
			NULL,
			CLSCTX_INPROC,
			IID_IDirectMusicPerformance,
			(void**)&gpPerf
			);

		if (res!=S_OK)
		{
			gpPerf=NULL;
			return false;
		}

// let performance create DirectMusic object
// link to existing DirectSound object

		res=gpPerf->Init(&gpDMusic,drvr->lpds,NULL);	

		if (res!=S_OK)
		{
// dont CloseDown if Init failed

//			gpPerf->CloseDown();

			gpPerf->Release();
			gpPerf=NULL;
			return false;
		}

// create loader responsible for loading, finding, enumerating and caching DirectMusic objects

		if (!CreateLoader())
			return false;

// get list of devices that we will show to the player

		EnumPorts();

// everything seems OK, allow music

		MusicAllowed=true;
		dig = drvr;												//RJS 09Nov99

		SetVolume(127);										//RJS 09Nov99

		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    EnumPorts
// Date:		20/10/99
// Author:		Macca
//
//Description:	Enumerate all devices that can be used for music and put
//				them into a list
//
//////////////////////////////////////////////////////////////////////
void Music::EnumPorts()
{
	HRESULT res;
	DWORD PortNum=0; // begin at zero and increment each time a port is successfully found
	DMUS_PORTCAPS caps;
	wchar_t name[DMUS_MAX_DESCRIPTION];
	bool error=false;

	DeletePortList();

	while (!error)
	{
		bool dls,soft,dsound;

		dls=false;
		soft=false;
		dsound=false;

		caps.dwSize=sizeof(DMUS_PORTCAPS);

		res=gpDMusic->EnumPort(PortNum,&caps);

		if (res!=S_OK)
			break;

// check out caps

		if (caps.dwClass==DMUS_PC_OUTPUTCLASS)
		{
			if (caps.dwFlags&DMUS_PC_DLS)
				dls=true;

			if (caps.dwFlags&DMUS_PC_SOFTWARESYNTH)
				soft=true;

			if (caps.dwFlags&DMUS_PC_DIRECTSOUND)
				dsound=true;

// if port has features we need then add it to the selectable list

			if (true)
			{
				LPDMPORTINFO portinfo=new DMPORTINFO;

				WideCharToMultiByte(CP_ACP,
									0,
									caps.wszDescription,
									-1,
									portinfo->device,
									sizeof(portinfo->device)/sizeof(portinfo->device[0]),
									0,
									0);


				portinfo->port=caps.guidPort;
				portinfo->next=PortInfo;
				portinfo->ChannelGroups=caps.dwMaxChannelGroups;
				PortInfo=portinfo;
				portinfo=NULL;
			}
		}

		PortNum++;
	}

// default will be the same as one of the enumerated ports

	AddDefaultPortToList();
}

//////////////////////////////////////////////////////////////////////
//
// Function:    StopMIDI
// Date:		20/10/99
// Author:		Macca
//
//Description: stop music and set playback position to beginning
//
//////////////////////////////////////////////////////////////////////
void Music::Stop()
{
	HRESULT res;

	if (MusicAllowed && gpPerf)
	{
		if (gpSegment)
		{
			res=gpPerf->Stop(NULL,NULL,0,0);

			res=gpSegment->SetStartPoint(0);
		}
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ReleasePort
// Date:		20/10/99
// Author:		Macca
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void Music::ReleasePort()
{
	HRESULT res;

	if (gpPort)
	{
		res=gpPort->Activate(FALSE);

		res=gpPerf->RemovePort(gpPort);

		res=gpPort->Release();
		gpPort=NULL;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    CreateAndAddPort
// Date:		20/10/99
// Author:		Macca
//
//Description:	Given an index into the list of music devices, create a port
//				for this device and assign it to the performance ready for 
//				some music to be played on it.
//
//////////////////////////////////////////////////////////////////////
bool Music::CreateAndAddPort(ULong index)
{
//DeadCode AMM 22Nov99 	HRESULT res;
//DeadCode AMM 22Nov99 	DMUS_PORTPARAMS params;

	if (this && MusicAllowed)
	{
		LPDMPORTINFO portinfo=PortInfo;

// find entry in list of ports

		while (index-- && portinfo)
			portinfo=portinfo->next;

		if (portinfo)
			return (CreateAndAddPort(portinfo->port));
	}

	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateAndAddPort
//Author		Andy McMaster
//Date			Mon 22 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool Music::CreateAndAddPort(GUID portguid)
{
	HRESULT res;
	DMUS_PORTPARAMS params;

	if (this && MusicAllowed)
	{
// release any current port

		ReleasePort();

		ZeroMemory(&params,sizeof(DMUS_PORTPARAMS));

		params.dwSize=sizeof(DMUS_PORTPARAMS);

// set up what port parameters we require here
/*	DWORD dwValidParams;	
    DWORD dwVoices;	
    DWORD dwChannelGroups;	
    DWORD dwAudioChannels;	
    DWORD dwSampleRate;	
    DWORD dwEffectFlags;	
    DWORD fShare;	
	
	DMUS_PORTPARAMS_VOICES	
	DMUS_PORTPARAMS_CHANNELGROUPS	
	DMUS_PORTPARAMS_AUDIOCHANNELS	
	DMUS_PORTPARAMS_SAMPLERATE	
	DMUS_PORTPARAMS_EFFECTS	
	DMUS_PORTPARAMS_SHARE 	
*/	

		params.dwChannelGroups=1;
		params.dwValidParams |= DMUS_PORTPARAMS_CHANNELGROUPS;

// create a port with the given port parameters

//DeadCode AMM 22Nov99 	res=gpDMusic->CreatePort(portinfo->port,&params,&gpPort,NULL);
		res=gpDMusic->CreatePort(portguid,&params,&gpPort,NULL);

		if (res!=S_OK)
		{
			_Error.SayAndQuit("Could not create port");
			return false;
		}

// ports are by default inactive when created, must activate to use

		res=gpPort->Activate(TRUE);

		if (res!=S_OK)
		{
			_Error.SayAndQuit("Could not activate port");
			return false;
		}

// assign the port to the performance

		res=gpPerf->AddPort(gpPort);

		if (res!=S_OK)
		{
			_Error.SayAndQuit("Could not add port");
			return false;
		}

// assign a block of 16 performance channels to the performance and map them to
// a port and channel group

		res=gpPerf->AssignPChannelBlock(0,gpPort,1);

		if (res!=S_OK)
		{
			_Error.SayAndQuit("Could not assign channel block");
			return false;
		}

// have a valid port, put it in save game settings

		Save_Data.MusicDevice=portguid;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    AddDefaultPortToList
// Date:		20/10/99
// Author:		Macca
//
//Description:	In the list of music devices we want a "default" entry.
//				This will be the one chosen initially and when there is no
//				valid entry in the savegame file.
//
//////////////////////////////////////////////////////////////////////
void Music::AddDefaultPortToList()
{
	LPDMPORTINFO portinfo=new DMPORTINFO;

	GUID tempguid;
	HRESULT res;

// get guid of default port

	res=gpDMusic->GetDefaultPort(&tempguid);

	if (res==S_OK)
	{
// find which port this is and copy its info

		LPDMPORTINFO temp=PortInfo;

// better default than 0xcdcdcdcd!!!!!
// should find it in list anyway but better safe than crashing

		portinfo->ChannelGroups=0;

		while (temp)
		{
			if (tempguid==temp->port)
			{
				portinfo->ChannelGroups=temp->ChannelGroups;
				break;
			}
			temp=temp->next;
		}

		strcpy(portinfo->device,"Default");
		portinfo->port=tempguid;
		portinfo->next=PortInfo;
		PortInfo=portinfo;
		portinfo=NULL;
	}
	else
	{
		delete portinfo;
		portinfo=NULL;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    CreateLoader
// Date:		20/10/99
// Author:		Macca
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool Music::CreateLoader()
{
	HRESULT res;

// get loader object, it is best to have just a single instance of a loader in order
// to ensure that the finding and caching of objects is done efficiently


	res=CoCreateInstance(
		CLSID_DirectMusicLoader,
		NULL,
		CLSCTX_INPROC,
		IID_IDirectMusicLoader,
		(void**)&gpLoader
		);

	if (res!=S_OK)
	{
		gpLoader=NULL;
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    PlayMIDI
// Date:		20/10/99
// Author:		Macca
//
//Description:	play the piece of music specified
//
//////////////////////////////////////////////////////////////////////
void Music::Play(void*	dataPtr, int	dataLength, bool MusicTest)
{
	HRESULT res;

// dont need to stop MIDI before playing a new piece, it will be stopped automatically
// as soon as new piece begins

	if (this && MusicAllowed)
	{
		AttemptFileOpen(dataPtr,dataLength,MusicTest);

		if (gpPort)
		{
			DMUS_PORTCAPS caps;
			caps.dwSize=sizeof(DMUS_PORTCAPS);

			gpPort->GetCaps(&caps);

			if (caps.dwFlags & DMUS_PC_DLS)
			{
// This parameter must be set for any segment based on a standard MIDI file before 
// any instruments are downloaded

				res=gpSegment->SetParam(GUID_StandardMIDIFile,0xffffffff,0,0,NULL);

				if (res!=S_OK)
				{
					_Error.SayAndQuit("SetParam on StandardMIDI File failed");
				}

				if (downloaded)
				{
// Unload instrument data for the track's bands

					gpSegment->SetParam(GUID_Unload,0xffffffff,0,0,(void*)gpPerf);
					downloaded=false;
				}
			}
			else
			{
				AttemptFileOpen(dataPtr,dataLength,MusicTest);
			}

// Download instrument data for the track's bands

			if (caps.dwFlags & DMUS_PC_DLS && !downloaded)
			{
				if (FAILED(gpSegment->SetParam(GUID_Download,0xffffffff,0,0,(void*)gpPerf)))
				{
					_Error.SayAndQuit("download on segment failed");
				}
				downloaded=true;
			}

// play on beat boundary

			if (FAILED(gpPerf->PlaySegment(gpSegment,DMUS_SEGF_BEAT,0,NULL)))
			{
				_Error.SayAndQuit("playsegment failed");
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AttemptFileOpen
//Author		Andy McMaster
//Date			Wed 20 Oct 1999
//
//Description	Try to load the given file into a segment
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Music::AttemptFileOpen(void*	dataPtr, int	dataLength, bool MusicTest)
{
	HRESULT res;
    IDirectMusicObject  *pObject;
    DMUS_OBJECTDESC ObjDesc;

	if (gpSegment)
	{
		gpPerf->Stop(NULL,NULL,0,0);

		if (downloaded)
		{
// unload any instruments

			gpSegment->SetParam(GUID_Unload,0xffffffff,0,0,(void*)gpPerf);
			downloaded=false;
		}

		if (SUCCEEDED(gpSegment->QueryInterface(IID_IDirectMusicObject,(void**)&pObject)))
		{
			gpLoader->ReleaseObject(pObject);
		}

		gpSegment->Release();
		gpSegment=NULL;
	}

// fill in object description structure
// will want to use DMUS_OBJ_MEMORY flag instead of loading from file
// llMemLength and pbMemData will have to be valid

// get TunePtr from FileNum
// this will have address (TunePtr->theblock) and size (TunePtr->thesize) of music piece

	if (MusicTest)
	{
		ObjDesc.dwSize=sizeof(DMUS_OBJECTDESC);
		ObjDesc.guidClass=CLSID_DirectMusicSegment;
		ObjDesc.dwValidData=
				DMUS_OBJ_CLASS
	 		  | DMUS_OBJ_FILENAME
			  | DMUS_OBJ_FULLPATH;

 		wcscpy( ObjDesc.wszFileName, L"c:\\temp\\relie2.mid");
	}
	else
	{
		ObjDesc.dwSize=sizeof(DMUS_OBJECTDESC);
		ObjDesc.guidClass=CLSID_DirectMusicSegment;
		ObjDesc.dwValidData=
				DMUS_OBJ_CLASS
				| DMUS_OBJ_MEMORY	;
//DeadCode AMM 22Nov99 		  | DMUS_OBJ_FILENAME
//DeadCode AMM 22Nov99 		  | DMUS_OBJ_FULLPATH;
//DeadCode AMM 22Nov99 	wcscpy( ObjDesc.wszFileName, L"c:\\temp\\relie2.mid");
//DeadCode AMM 15Nov99 			DMUS_OBJ_MEMORY	;

		ObjDesc.pbMemData = (LPBYTE)dataPtr;
		ObjDesc.llMemLength = dataLength;
	}

	res=gpLoader->GetObject(&ObjDesc,IID_IDirectMusicSegment, (void**)&gpSegment);

	if (res!=S_OK)
	{
		_Error.SayAndQuit("GetObject failed");
	}
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
void Music::SetVolume(int vol, int fadetime)
{
	HRESULT res;

	if (gpPerf)
	{
		vol &= 0x7f;

		currentvol = vol;
		currentfadetime = fadetime;

//Scale to master volume (0-128)...
		
		vol *= mastervolume;
		vol >>= 7;

		vol = DigitalDriver::GetDecibels(vol);							//RJS 13Nov00

		res=gpPerf->SetGlobalParam(GUID_PerfMasterVolume,&vol,sizeof(vol));
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    CleanUpMusic
// Date:		20/10/99
// Author:		Macca
//
//Description:	release all interfaces 
//
//////////////////////////////////////////////////////////////////////
void Music::CleanUpMusic()
{
	if (gpSegment)
	{
		gpSegment->Release();
		gpSegment=NULL;
	}

	if (gpPerf)
	{
		gpPerf->CloseDown();
		gpPerf->Release();
		gpPerf=NULL;
	}

	if (gpLoader)
	{
		gpLoader->Release();
		gpLoader=NULL;
	}

	if (gpDMusic)
	{
		gpDMusic->Release();
		gpDMusic=NULL;
	}

	if (gpPort)
	{
		gpPort->Release();
		gpPort=NULL;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ProcessMusic
// Date:		20/10/99
// Author:		Macca
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void Music::Process()
{
	HRESULT res;

	if (gpPerf)
	{
		res=gpPerf->IsPlaying(gpSegment,NULL);

		if (res==S_FALSE)
		{
// wibble
		}
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    DeletePortList
// Date:		20/10/99
// Author:		Macca
//
//Description:	clean up device list
//
//////////////////////////////////////////////////////////////////////
void Music::DeletePortList()
{
	if (this)
	{
		LPDMPORTINFO temp1,temp2;

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

//////////////////////////////////////////////////////////////////////
//
// Function:    MusicPlaying
// Date:		20/10/99
// Author:		Macca
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool Music::Playing()
{
	if (gpPerf)
	{
		if (gpPerf->IsPlaying(gpSegment,NULL)==S_OK)
			return true;
	}
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetVolume
//Author		Robert Slater
//Date			Tue 9 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	Music::GetVolume()
{
	return currentvol;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetMasterVolume
//Author		Robert Slater
//Date			Tue 9 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Music::SetMasterVolume(int	theVol)
{
	if (theVol < 0)
		theVol = 0;
	else
	{
		if (theVol > 128)
			theVol = 128;
	}

	mastervolume = theVol;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IsMusicDeviceValid
//Author		Andy McMaster
//Date			Mon 22 Nov 1999
//
//Description	Checks to see if the GUID of the music device in the savegame is
//				valid, i.e. one of the enumerated devices
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 22Nov99 bool	Music::IsMusicDeviceValid()
//DeadCode AMM 22Nov99 {
//DeadCode AMM 22Nov99 	return false;
//DeadCode AMM 22Nov99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AssignDefaultMusicDevice
//Author		Andy McMaster
//Date			Mon 22 Nov 1999
//
//Description	Sets the music device to be used to the default and sets savegame setting
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	Music::AssignDefaultMusicDevice()
{
	if (this && MusicAllowed)
	{
		HRESULT res;
		GUID tempguid;

		res=gpDMusic->GetDefaultPort(&tempguid);

		if (res==S_OK)
		{
			if (CreateAndAddPort(tempguid))
			{
				return true;
			}
		}
	}
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitMusicDevice
//Author		Andy McMaster
//Date			Mon 22 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool SaveData::InitMusicDevice()
{
	if (_Miles.mdi)
	{
		if (!_Miles.mdi->AssignDefaultMusicDevice())
			return false;

		return true;
	}
	return false;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadedMusicDeviceOK
//Author		Andy McMaster
//Date			Mon 22 Nov 1999
//
//
//Description	Checks to see if the GUID of the music device in the savegame is
//				valid, i.e. one of the enumerated devices
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool SaveData::LoadedMusicDeviceOK()
{
	if (_Miles.mdi)
	{
// traverse enumerated music devices and see if GUID from savegame is in list

		LPDMPORTINFO temp=_Miles.mdi->PortInfo;

		while (temp)
		{
			if (temp->port==MusicDevice)
			{
				if (_Miles.mdi->CreateAndAddPort(temp->port))
					return true;
			}

			temp=temp->next;
		}

	}
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestMusic
//Author		Andy McMaster
//Date			Mon 22 Nov 1999
//
//Description	Called when option in prefs is selected to evaluate quality
//				of music device.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Music::TestMusic()
{
	if (this)
	{
		Stop();

// need to choose a good piece of music to play, from which it will be easy to choose
// the best quality music device available.

		Play(NULL,NULL);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChangeMusicDevice
//Author		Andy McMaster
//Date			Mon 22 Nov 1999
//
//Description	Called when music device in preferences is changed
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool Music::ChangeMusicDevice(ULong index)
{
	if (this)
	{
		Stop();
		ReleasePort();
		if (CreateAndAddPort(index))
		{
			return true;
		}
		else
		{
// clean up?
		}
	}
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MDI_valid
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
bool	Music::MDI_valid()
{
	bool	retval = false;
	if (this && MusicAllowed)
		retval = true;

	return retval;
}

CON Music::Music()
{
	MusicAllowed=false;
	PortInfo=NULL;
	index=0;
	downloaded=false;

	gpPerf=NULL;
	gpLoader=NULL;
	gpSegment=NULL;
	gpDMusic=NULL;
	gpPort=NULL;

	dig = NULL;
	currentvol = 0;
	mastervolume = 128;
}

CON Music::~Music()
{
	if (this)
	{
		DeletePortList();
		CleanUpMusic();
	}
}


