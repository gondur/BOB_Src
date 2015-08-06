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
//Filename       savegame.cpp
//System         
//Author         Jim Taylor
//Date           Thu 22 Aug 1996
//Description    Various savegame routines - using overloading of << and >>	Dev Studio ref system don't like overloaded operators.
//_MIGALLEY_GUID						
//------------------------------------------------------------------------------
#include	"dosdefs.h"
#include	"myerror.h"
//#include <afx.h>

	#define F_GRAFIX
	#define F_SOUNDS
	#define F_BATTLE
#include "files.g"
//#include	"ui.h"
#include	"uniqueid.h"
#include	"worldinc.h"
#include	"bitfield.h"
//DEADCODE JIM 09/02/00 #include	"text.h"

#include	"missman2.h"

#include	"bstream.h"
#include	"savegame.h"
#include	"analogue.h"
#include	"persons2.h"
#include	"3dcom.h"
#include	"mytime.h"
#include	"miles.h"
#include	<string.h>
#include	"groupitt.h"
#include	"replay.h"
#include "gameset.h"
#include	"nodebob.h"
#include	"sqddiary.h"										//RJS 28Jan00

SaveData	Save_Data;
DeadStream	Dead_Stream={0};
char	date[]="Rowan Savegame: " __DATE__ ;
char	date2[]="Rowan Savegame: " __DATE__ ;
inline	CString	LoadResString(int resnum)
{
	CString s;
	s.LoadString(resnum);
	return s;
};
extern void GetDriverAndMode(int&,int&,int&,int&);
//DEADCODE PD 03/12/99 extern void Configure(bool,HWND);
#include	"..\mfc\resource.h"

#ifdef NDEBUG
#define AfxTrace
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		analogue
//Author		Jim Taylor
//Date			Tue 27 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	BOStream& operator  <<  (BOStream& bos,RunTimeDevDesc& devdesc)
{
	 bos<<devdesc.devid.Data1;
	 if (devdesc.devid.Data1)
	 {
		 bos<<devdesc.devid.Data2<<devdesc.devid.Data3;
		 bos.write((char*)devdesc.devid.Data4,8);
		 bos<<(char)devdesc.useff;
		 bos<<(char)devdesc.ismouse;
		 bos.write(devdesc.axismaps,devdesc.MAXMAPS);
		 bos.write(devdesc.sh_axismaps,devdesc.MAXMAPS);
		 bos.write(devdesc.hatmaps,devdesc.MAXMAPS);
//DEADCODE RDH 25/05/00 		 bos.write(devdesc.sh_hatmaps,devdesc.MAXMAPS);
	 }
	 return	bos;
}

static	BIStream& operator  >>  (BIStream& bis,RunTimeDevDesc& devdesc)
{
	 bis>>devdesc.devid.Data1;
	 if (devdesc.devid.Data1)
	 {
		 bis>>devdesc.devid.Data2>>devdesc.devid.Data3;
		 bis.read((char*)devdesc.devid.Data4,8);
		 bis>>(char&)devdesc.useff;
		 bis>>(char&)devdesc.ismouse;
		 bis.read(devdesc.axismaps,devdesc.MAXMAPS);
		 bis.read(devdesc.sh_axismaps,devdesc.MAXMAPS);
		 bis.read(devdesc.hatmaps,devdesc.MAXMAPS);
//DEADCODE RDH 25/05/00 		 bis.read(devdesc.sh_hatmaps,devdesc.MAXMAPS);
	 }
	 return bis;
}

BOStream& operator	<<	(BOStream& bos,Analogue::Tuning& tuning)
{
	bos.write((UByte*)&tuning,sizeof(tuning));
	return(bos);
}
BIStream& operator	>>	(BIStream& bis,Analogue::Tuning& tuning)
{
	bis.read((UByte*)&tuning,sizeof(tuning));
	return(bis);
}

	BOStream& operator	<<	(BOStream& bos,Analogue& analogue)
{
	for (int dev=0;dev<20;dev++)
		bos<<analogue.runtimedevices[dev];	
	for (int au=0;au<AU_MAX;au++)
	{
		bos<<analogue.tune[au];
	}
//DeadCode CSB 17Aug00 	bos<<analogue.FFpush.level;
//DeadCode CSB 17Aug00 	bos<<analogue.FFstiff.level;
//DeadCode CSB 17Aug00 	bos<<analogue.FFshake.level;
//DeadCode CSB 17Aug00 	bos<<analogue.FFdamp.level;
	bos<<analogue.FF_gun;												//CSB 17Aug00
	bos<<analogue.FF_buffet;											//CSB 17Aug00
	bos<<analogue.FF_aerodynamic;										//CSB 17Aug00
	bos<<analogue.FF_airframe;											//CSB 17Aug00
	return(bos);

}

	BIStream& operator	>>	(BIStream& bis,Analogue& analogue)
{
	for (int dev=0;dev<20;dev++)
		bis>>analogue.runtimedevices[dev];	
	for (int au=0;au<AU_MAX;au++)
	{
		bis>>analogue.tune[au];
	}
//DeadCode CSB 17Aug00 	bis>>analogue.FFpush.level;
//DeadCode CSB 17Aug00 	bis>>analogue.FFstiff.level;
//DeadCode CSB 17Aug00 	bis>>analogue.FFshake.level;
//DeadCode CSB 17Aug00 	bis>>analogue.FFdamp.level;
	bis>>analogue.FF_gun;
	bis>>analogue.FF_buffet;
	bis>>analogue.FF_aerodynamic;
	bis>>analogue.FF_airframe;
	analogue.LoadGame();
	return(bis);
	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		savedata
//Author		Jim Taylor
//Date			Tue 27 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BOStream& operator	<<	(BOStream& bos,SaveDataSoftware& savedata)
{
	bos.write((char*)&savedata,sizeof(SaveDataSoftware));
	return(bos);
}
BIStream& operator	>>	(BIStream& bos,SaveDataSoftware& savedata)
{
	bos.read((char*)&savedata,sizeof(SaveDataSoftware));
	return(bos);
}
BOStream& operator	<<	(BOStream& bos,SaveData& savedata)
{
	bos<<date2;
	bos.write("\n\0x26\0x04",4);
	bos.write((char*)&savedata,sizeof(SaveDataLoad));
	char z=0;
	bos<<savedata.lastsavegame<<z;
	bos<<savedata.lastreplayname<<z;
	bos<<savedata.lastpackname<<z;
	bos<<_Analogue;
	return(bos);

}
BIStream& operator	>>	(BIStream& bis,SaveData& savedata)
{
	bis>>date;
	int dummy;
	bis>>dummy;
	if (strcmp(date,date2)==0)
	{
		bis.read((char*)&savedata,sizeof(SaveDataLoad));
		char buffer[180];
		char b=-1;
		for (int i=0;b;buffer[i++]=b)
			bis>>b;
		savedata.lastsavegame=buffer;
		for (b=-1,i=0;b;buffer[i++]=b)
			bis>>b;
		savedata.lastreplayname=buffer;
		for (b=-1,i=0;b;buffer[i++]=b)
			bis>>b;
		savedata.lastpackname=buffer;
		bis>>_Analogue;

		_Miles.SetGlobalVolumes(savedata.vol.sfx,savedata.vol.music,savedata.vol.engine,savedata.vol.anim,TRUE);//RJS 29Sep96
		Save_Data.successfulLoad=true;
	}
	else Save_Data.successfulLoad=false;
//DEAD		MessageBox(NULL,LoadResString(IDS_CONFIGIGNORED),LoadResString(IDS_CHOOSEPREFS),MB_OK);

	return(bis);
	
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		deadstream
//Author		Jim Taylor
//Date			Tue 27 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BOStream& operator	<<	(BOStream& bos,DeadStream & deadstream)
{
	bos<<deadstream.olddaytime;
	for (DeadStream::DeadBlock* curr=deadstream.firstblock;curr;curr=curr->nextblock)
	{
		bos<<ULong(curr->SGT);
		bos<<curr->dataused;
		bos.write(curr->data,curr->dataused);
	}
		bos<<-1;
	return(bos);
}
BIStream& operator	>>	(BIStream& bis,DeadStream & deadstream)
{
	deadstream.ClrWorldDead();
	DeadStream::DeadBlock** curr=&deadstream.firstblock;
	bis>>deadstream.olddaytime;
	int uid;
	bis>>uid;
	while (uid!=-1)
	{
		curr[0]=new DeadStream::DeadBlock(UniqueID(uid));
		bis>>curr[0][0].dataused;
		bis.read(curr[0][0].data,curr[0][0].dataused);
		curr=&curr[0][0].nextblock;
		bis>>uid;
	}
	curr[0]=NULL;
	return(bis);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		campaign
//Author		Jim Taylor
//Date			Tue 27 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	BOStream& operator	<<	(BOStream& bos,Campaign& campaign)
{
	bos<<date2;
	bos.write("\n\0x26\0x04",4);
	bos<<campaign.garbage;
	bos.write((char*)&campaign+sizeof(CampaignPtrs),sizeof(Campaign)-sizeof(CampaignPtrs));
 	bos<<Dead_Stream;
	return(bos);

}

static	BIStream& operator	>>	(BIStream& bis,Campaign& campaign)
{
	bis>>date;
	int dummy;
	bis>>dummy;
	if (strcmp(date,date2))
#ifndef NDEBUG
		if (::MessageBox(NULL,"Savegame dates differ: Press OK to load it anyway.\nIf you press OK and the savegame is not compatible then BAD THINGS will happen!\n"
			"I'm sure you're wondering whether I cleared 5 bytes or 6\n"
			"To be honest in all the confusion, I can't remember either\n"
			"But as this is a 500MHz Pentium - the biggest F* up in the world, you may not want to risk it...\n"
			"Do you feel lucky, punk? Well, do you?",date,	MB_OKCANCEL)==IDCANCEL)
#endif
			_Error.ReallyEmitSysErr("Savegame version dates differ %s != %s",date,date2);
	bis>>campaign.garbage;
	bis.read((char*)&campaign+sizeof(CampaignPtrs),sizeof(Campaign)-sizeof(CampaignPtrs));
 	bis>>Dead_Stream;
	strcpy(Save_Data.CommsPlayerName,campaign.PlayerName);
	//Need to fix currmission and dfltmission pointers
	//
	//
//DEAD	switch (Miss_Man.currcampaignnum)
//DEAD	{
//DEAD		case MissMan::PEACETALKCAMPAIGN:
//DEAD		{
//DEAD
//DEAD			Miss_Man.camp.dfltmission = PeaceTalk_Missions [Miss_Man.camp.currmission_no];
//DEAD			Miss_Man.camp.currmission = Miss_Man.camp.dfltmission;
//DEAD			break;
//DEAD		}
//DEAD		case MissMan::SO51_CAMPAIGN:
//DEAD		{
//DEAD			Miss_Man.camp.currmission = Spring51_Missions [Miss_Man.camp.currmission_no];
//DEAD			Miss_Man.camp.dfltmission = Miss_Man.camp.currmission;
//DEAD			break;
//DEAD		}
//DEAD		case MissMan::INTROCAMPAIGN:
//DEAD		{
//DEAD			Miss_Man.camp.currmission = Intro_Missions [Miss_Man.camp.currmission_no];
//DEAD			Miss_Man.camp.dfltmission = Miss_Man.camp.currmission;
//DEAD			break;
//DEAD		}
//DEAD	}
	return(bis);
	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MissMan& miss_man
//Author		Jim Taylor
//Date			Thu 22 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
BOStream& operator	<<	(BOStream& bos,MissMan& miss_man)
{

	strcpy(miss_man.camp.CommsPassword,_DPlay.Password);
	bos<<(SByte&) miss_man.currcampaignnum;
	bos<<miss_man.camp;
	Node_Data.Save(bos);
	bos<<(SaveDataSoftware&)Save_Data;
//DeadCode JIM 2Nov00 	bos<<Dead_Stream;
	Squad_Diary.Save(bos);										//RJS 02Feb00
	Todays_Packages.SaveGame(bos);	//must be last thing in savegame!!!
	return(bos);
}

BIStream& operator	>>	(BIStream& bis,MissMan& miss_man)
{

	if (!_Replay.Playback) // || _Replay.IsCampState(_Replay.PlaybackGameState))
	{
		if (Persons2::pItemSet())
			for (int p=0;p<Profile::MAX_PACKS;p++)
				Todays_Packages.ClearPack(p);
	}

	Persons4::ShutDownMapWorld();
	bis>>(SByte&) miss_man.currcampaignnum;
	bis>>miss_man.camp;
	strcpy(_DPlay.Password,miss_man.camp.CommsPassword);
	Node_Data.BuildTargetTable();
	Node_Data.Load(bis);
	bis>>(SaveDataSoftware&)Save_Data;
//DeadCode JIM 2Nov00 	bis>>Dead_Stream;
	Squad_Diary.Load(bis);										//RJS 02Feb00
	Persons4::StartUpMapWorld();
	Todays_Packages.LoadGame(bis);	//must be last thing in savegame!!!
	Node_Data.SetPlayerInfoLevel();
	return(bis);
}






//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PutInfo
//Author		Jim Taylor
//Date			Mon 2 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------


CON	DeadStream::DeadBlockItterator::DeadBlockItterator
	(DeadBlockPtr& deadbase,UniqueID sgt)
{
	lastuniqueID=UID_NULL;
	base=&deadbase;
	SGT=sgt;
	newpage=false;
	if (!deadbase)
	{
		newpage=true;
		curr=
			deadbase=new DeadBlock(SGT);
	}
	else
		if (sgt==UID_NULL)
		{
			if (deadbase->SGT!=UID_NULL)
			{
				newpage=true;
				curr=new DeadBlock(sgt);
				curr->nextblock=deadbase;
				deadbase=curr;
			}
			else
				curr=deadbase;
		}
		else
		{
			DeadBlock* page=deadbase;
			while(page->nextblock && page->SGT!=sgt)
				page=page->nextblock;
			if (page->SGT==sgt)
				curr=page;
			else
			{
				newpage=true;
				curr=
					page->nextblock=
						new DeadBlock(sgt);
			}
		}
	off=0;
}

DES	DeadStream::DeadBlockItterator::~DeadBlockItterator()
{
	DeleteTempBlock();	//deletes temp block!!!
}

void	DeadStream::DeadBlockItterator::DeleteTempBlock()
{
	//first destructor the existing block...
	if (newpage && off==0)
	{
		if (*base==curr)
		{
			*base=curr->nextblock;
		}
		else
		{
			DeadBlock* tmp=*base;
			while (tmp->nextblock!=curr)
				tmp=tmp->nextblock;
			tmp->nextblock=curr->nextblock;
		}
		DeadBlock* tmp=curr;
		curr=tmp->nextblock;
		delete tmp;
	}
	newpage=false;

}
UniqueID	DeadStream::DeadBlockItterator::NextSGT()
{
	DeleteTempBlock();
	if (!curr)
		return UID_NULL;
	while (curr && curr->SGT==SGT)
		curr=curr->nextblock;
	if (!curr)
		return UID_NULL;
	SGT=curr->SGT;
	off=0;
	lastuniqueID=UID_NULL;
	return SGT;
}

bool	DeadStream::DeadBlockItterator::SkipToSGT(UniqueID sgt)
{
	DeleteTempBlock();
	if (!curr)
		return false;
	while (curr && curr->SGT!=sgt)
		curr=curr->nextblock;
	if (!curr)
		return false;
	SGT=sgt;
	off=0;
	lastuniqueID=UID_NULL;
	return true;
}

bool	DeadStream::DeadBlockItterator::PutInfo(void* src,int count)
{
	if (count+off>maxblocksize)
	{
		off=count;
		DeadBlock* tmp=new DeadBlock(SGT);
		tmp->nextblock=curr->nextblock;
		curr->nextblock=tmp;
		curr=tmp;
		memcpy(tmp->data,src,count);
		tmp->dataused=off;
		return true;
	}
	else
	{
		memcpy(curr->data+off,src,count);
		off+=count;
		curr->dataused=off;
		return false;
	}
}

void	DeadStream::DeadBlockItterator::GetInfo(void* trg,int count)
{
	if (count+off>maxblocksize)
	{
		curr=curr->nextblock;
		assert(SGT==curr->SGT);
		off=0;
	}
	memcpy(trg,curr->data+off,count);
	off+=count;
}

int	DeadStream::DeadBlockItterator::SkipCountedInfo()
{
	int count=GetWord();
	if (count+off>maxblocksize)
	{
		curr=curr->nextblock;
		assert(SGT==curr->SGT);
		off=0;
	}
////////	memcpy(trg,curr->data+off,count);
	off+=count;
	return count;

}

void	DeadStream::DeadBlockItterator::NextDeadElt(UByte&di1b,int&diplc,char*&dipld)
{
	lastnumelts--;
	char firstbyte=GetByte();
	if (((MinAnimData&)firstbyte).IsInvisible)
	{
		((MinAnimData&)firstbyte).IsInvisible=FALSE;
		di1b=firstbyte;
		int count=GetWord();
		if (count+off>maxblocksize)
		{
			curr=curr->nextblock;
			assert(SGT==curr->SGT);
			off=0;
		}
		diplc=count;
		dipld=curr->data+off;
		off+=count;
	}
	else
	{
		di1b=firstbyte;
		diplc=0;
		dipld=NULL;
	}
}

void	DeadStream::DeadBlockItterator::NextEltClearDamage()
{
	char firstbyte=GetByte();
	((MinAnimData&)firstbyte).itemstate=0;
	curr->data[off-1]=firstbyte;
	if (((MinAnimData&)firstbyte).IsInvisible)
		SkipCountedInfo();
}


void	DeadStream::DeadBlockItterator::SetNextDeadElt(char di1b,int diplc,char* dipld)
{
	if (diplc)
	{
		((MinAnimData&)di1b).IsInvisible=TRUE;
		PutByte(di1b);
		PutCountedInfo(dipld,diplc);
	}
	else
	{
		((MinAnimData&)di1b).IsInvisible=FALSE;
		PutByte(di1b);
	}
}
void	DeadStream::DeadBlockItterator::SkipNextDeadElt()
{
	lastnumelts--;
	char firstbyte=GetByte();
	if (((MinAnimData&)firstbyte).IsInvisible)
		SkipCountedInfo();
}

UniqueID	DeadStream::DeadBlockItterator::SkipItem()
{
	if (lastuniqueID)
		while (lastnumelts)
			SkipNextDeadElt();
	else
		if (off)
			return (UniqueID)lastuniqueID;
//DeadCode JIM 20Oct00 	UWord get=
	lastuniqueID=GetWord();
	if (lastuniqueID)
	{
		
		lastStatus=GetWord();
		lastshape=GetWord();
		lastnumelts=GetByte();
	}
	return (UniqueID)lastuniqueID;
}

bool	DeadStream::DeadBlockItterator::SkipToItem(UniqueID trg)
{
	if (trg==lastuniqueID)
		return true;
	do
		SkipItem();
	while (lastuniqueID!=UID_NULL && lastuniqueID!=trg);
	return (trg==lastuniqueID);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClrWorldDead
//Author		Jim Taylor
//Date			Mon 2 Sep 1996
//
//Description	Clear all dead fields
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DeadStream::ClrWorldDead()
{
	DeadBlockPtr tmp=firstblock;
	firstblock=NULL;
	while (tmp)
	{
		DeadBlockPtr tmp2=tmp->nextblock;
		delete tmp;
		tmp=tmp2;
	}
}

bool	DeadStream::ClearForSGT(UniqueID sgt)
{
	DeadBlockPtr* p=&firstblock;
	while (*p && p[0][0].SGT!=sgt)
		p=&p[0][0].nextblock;
	if (*p)
	{
		DeadBlockPtr tmp=*p;
		while (tmp && tmp->SGT==sgt)
		{
			DeadBlockPtr tmp2=tmp->nextblock;
			delete tmp;
			tmp=tmp2;
		}
		*p=tmp;
		return true;
	}
	else
		return false;
}

////////////////////////////////////////////////////////////////////////
//
// Function:    MainWorldBand
// Date:        24/02/99
// Author:      JIM
//
// Description: Flags that these SGT items are kept in the main world indexed directly by their UID
//
////////////////////////////////////////////////////////////////////////
bool	DeadStream::DontRecordBand(UniqueID u)						  //DAW 6/15/99
{
	UniqueIDBand	b=Persons2::getbandfromUID(u);
	return(		b==BritAAASiteBAND
			||	b==BarrageBalloonBAND
		
		);
}
bool	DeadStream::MainWorldBand(UniqueID u)
{
	UniqueIDBand	b=Persons2::getbandfromUID(u);
	return(		b==BritAAALargeBAND
			||	b==BritBridgeBAND
			||	b==RunwaySBAND
			||	b==RunwayEBAND
			//||	b==AfHangarBAND,
			||	b==AfStaffBAND
			||	b==AfStoresBAND
			||	b==AfFieldBAND
			);
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetWorldDead
// Date:		24/03/00
// Author:		JIM
//
//Description: 	Save damage info from 3d items
//
//////////////////////////////////////////////////////////////////////
void	DeadStream::SetWorldDead(WorldStuff* world)
{
	MAKEFIELD(UniqueID,UID_NULL,IllegalSepID);
	UniqueIDField	issgt;
	issgt=0;
	ClearForSGT(UID_NULL);
	{
		DeadBlockItterator b(firstblock,UID_NULL);
		for (int i=0;i<WorldStuff::PITEMTABLESIZE;i++)
			if (world->pItem[i])
			{
				ItemBasePtr t1=world->pItem[i];
				if (t1->Status.size!=WAYPOINTSIZE && t1->Status.size<MOBILESIZE)
				{
					ItemPtr	tmp=*t1;
					if (	tmp->SGT &&	!MainWorldBand(UniqueID(i)))
						issgt|=tmp->SGT;
					else
						if (tmp->Anim != NULL)
						{	//may have to step through every elt in group doing this!
							//but will save some anim space by doing so.
							bool	nonzero=(tmp->Status.deadtime!=0);
							{
								GroupItterator g(tmp->shape,tmp->Anim);
								if (g.NumElts())
								{	nonzero|=(g.status!=0);
									if (!nonzero)
										while(g++) nonzero|=(g.status!=0);	}
							}
							if (nonzero)
							{
								if (tmp->SGT)
									tmp=tmp;
								GroupItterator g(tmp->shape,tmp->Anim);
								int elts=g.NumElts();
								b.PutWord((short)tmp->uniqueID.count); //DAW 09/05/99 as per Jims instructions
								b.PutWord((short&)tmp->Status);
								b.PutWord((short&)tmp->shape);
						if (elts==-1)
							elts=elts;
								b.PutByte(elts);
								if (elts)
									do{
										assert	(elts--);
										b.SetNextDeadElt(g.AnimDataByte(),g.PostLauncherDataSize(),g.PostLauncherDataLoc());
									}while (g++);
								assert(elts==0);
			}	}		}	}
		b.PutWord(0);
	}
	for (int sgt=0;sgt<WorldStuff::PITEMTABLESIZE;sgt++)
		if (issgt[(UniqueID)sgt])
		{
			bool wrote=false;
			int band=0,uidnum=0;
			ClearForSGT(UniqueID(sgt));
			DeadBlockItterator b(firstblock,UniqueID(sgt));
//DEADCODE RJS 16/11/99 			if (Persons2::getbandfromUID(UniqueID(sgt))!=AmberBattleNodeBAND)
			for (int i=0;i<WorldStuff::PITEMTABLESIZE;i++)
				if (world->pItem[i])
				{
					ItemBasePtr t1=world->pItem[i];
					if (t1->Status.size!=WAYPOINTSIZE && t1->Status.size<MOBILESIZE)
					{
						ItemPtr	tmp=*t1;
						if (	tmp->SGT==sgt						  //DAW 6/15/99
							&&	!MainWorldBand(UniqueID(i))			  //DAW 6/15/99
							&&	!DontRecordBand(UniqueID(i))		  //DAW 6/15/99
							)										  //DAW 6/15/99
							if (tmp->Anim != NULL)
							{
								bool	nonzero=(tmp->Status.deadtime!=0);
								{
									GroupItterator g(tmp->shape,tmp->Anim);
									if (g.NumElts())
									{
										nonzero|=(g.status!=0);
										if (!nonzero)
											while(g++)
												nonzero|=(g.status!=0);
									}
								}

								int uidval=Persons2::getbandfromUID(UniqueID(tmp->uniqueID.count));
								if (uidval==band)
									uidnum++;
								else
									uidnum=band=uidval;

								if (nonzero)
								{
									wrote=true;
									b.PutWord(uidnum);
									b.PutWord((short&)tmp->Status);
									b.PutWord((short&)tmp->shape);
									GroupItterator g(tmp->shape,tmp->Anim);
									int elts=g.NumElts();
						if (elts==-1)
							elts=elts;
  									b.PutByte(elts);
									do	b.SetNextDeadElt(g.AnimDataByte(),g.PostLauncherDataSize(),g.PostLauncherDataLoc());
									while (g++);
				}	}		}	}
			if (wrote)
				b.PutWord(0);
		}
}
//////////////////////////////////////////////////////////////////////
//
// Function:    GetWorldDead
// Date:		24/03/00
// Author:		JIM
//
//Description: 	Transfer saved info to 3d items
//
//////////////////////////////////////////////////////////////////////
void	DeadStream::GetWorldDead(WorldStuff* world)
{
	UniqueID SGT=UID_NULL;
	DeadBlockItterator	b(firstblock,UID_NULL);
	int targuid=b.GetWord();
	while(targuid)
	{
		ItemPtr t1=*world->pItem[targuid];
		if (t1 && InfoItemFlagPtr(t1)->Minus1!=-1)
		{
			assert(t1->SGT==UID_NULL || MainWorldBand(UniqueID(targuid)));
			(short&)t1->Status=b.GetWord();
			int shapenum=b.GetWord();
			assert(shapenum==t1->shape);

			int tst;
			if (t1->Anim==NULL)
				tst=SHAPE.SetAnimData(t1,0);			//RDH 23Sep96
			else
				tst=SHAPE.GetAnimDataSize(t1->shape);
			GroupItterator g(t1->shape,t1->Anim);
			char count=b.GetByte();
			do{
				UByte	first;
				int		datalen;
				char*	src;
				b.NextDeadElt(first,datalen,src);
				g.AnimDataByte()=first;
				assert(datalen==0 || g.PostLauncherDataSize()==datalen);
				memcpy(g.PostLauncherDataLoc(),src,datalen);
				assert(count--);
			}while (g++);
		}
		else
		{
			b.GetWord();	//long dead
			b.GetWord();	//shape
			char count=b.GetByte();	//first anim byte
			while (count--)
				b.SkipNextDeadElt();
		}
		targuid=b.GetWord();
	}
	SGT=b.NextSGT();
	while(SGT)
	{
		for (int i=0;i<WorldStuff::PITEMTABLESIZE;i++)
			if (!MainWorldBand(UniqueID(i)))
				if (world->pItem[i])
				{
					ItemBasePtr t1=world->pItem[i];
					if (t1->Status.size!=WAYPOINTSIZE && t1->Status.size!=AIRSTRUCSIZE && InfoItemFlagPtr(t1)->Minus1!=-1)
					{
						ItemPtr	tmp=*t1;
						if (tmp->SGT==SGT)
							break;
					}
				}

		if (i!=WorldStuff::PITEMTABLESIZE)
		{

			int targuid=b.GetWord();
			int band=0,bandcount=0,lastuid=0;
			while(targuid)
			{
				int targband=Persons2::getbandfromUID(UniqueID(targuid));
				int targbandMAX=Persons2::getbandMAXfromUID(UniqueID(targuid));
				targuid-=targband;
				if (targband!=band)
				{
					band=targband;
					bandcount=0;
					lastuid=band;
				}
				ItemPtr p=NULL;
				for (int skip=targuid-bandcount,u=lastuid;skip>=0;u++)
				{
					p=NULL;
					breakif(u==targbandMAX);
					p=*world->pItem[u];
					if (p && p->SGT==SGT)
						skip--;
				}
				if (p && InfoItemFlagPtr(p)->Minus1!=-1)
				{
					(short&)p->Status=b.GetWord();
					int shapenum=b.GetWord();
					assert(shapenum==p->shape);
					int tst;
					if (p->Anim==NULL)
						tst=SHAPE.SetAnimData(p,0);			//RDH 23Sep96
					else
						tst=SHAPE.GetAnimDataSize(p->shape);

					GroupItterator g(p->shape,p->Anim);
					char count=b.GetByte();
					do{
						UByte	first;
						int		datalen;
						char*	src;
						b.NextDeadElt(first,datalen,src);
						g.AnimDataByte()=first;
						assert(datalen==0 ||g.PostLauncherDataSize()==datalen);
						memcpy(g.PostLauncherDataLoc(),src,datalen);
						assert(count--);
					}while (g++);
					lastuid=p->uniqueID.count+1;

				}
				else
				{
					b.GetWord();	//long dead
					b.GetWord();	//shape
					char count=b.GetByte();	//first anim byte
					while (count--)
						b.SkipNextDeadElt();
					lastuid=targbandMAX-1;
				}
				bandcount=targuid+1;
//DEADCODE JIM 10/06/99 				lastuid=p->uniqueID.count+1;
				targuid=b.GetWord();
			}
		}
		SGT=b.NextSGT();
	};
}

static bool	QuickRevivableBand(int	targuid)
{
	return (targuid>=AfFieldBAND && targuid<AfNoScoreBAND);		//JUST FIELD
}
static bool	RevivableBand(int targuid)
{
	return (targuid>=AfStoresBAND && targuid<AfNoScoreBAND);	//FIELD AND FUEL
}
//////////////////////////////////////////////////////////////////////
//
// Function:    ReviveWorld
// Date:		30/04/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	DeadStream::ReviveWorld(const int repairpointsinperiod,int repairbridgepointsinperiod)
{	//have to make second copy of each block as go along
	//second copy has alive items removed, so damage is forgotten.
//DeadCode JIM 16Oct00 	return;
	//"Simplified" Mig Alley repair scheme:
	//	Each super group has a limited number of points of repair per period
	//	Each point is 1 element in a group.
	//  This bit is not done:
	//		If an element is a large shape (>200pts) it is repaired 1 level.
	//		If an element is a medium shape (>100pts) repaired 2 levels
	//		If an element is a small shape (<100pts) repaired 3 levels
	//
	//	The problem I have is in accounting for mainworld and subworld elements of same SGT
	//	as I only want to process the list once!
	//
	//	First job is to get together a list of the UIDs that have been damaged
	//	UniqueIDField costs 16K/8=2Kb
	//	If I spend 4 bytes on each SGT that allows 500 SGTs in the same space.
	//
	//

	// IMPORTANT NOTE:
	//	Each SGT member item that is damaged then repaired MUST stay in the list fully
	//  alive for 1 more session in order for the repair to register.
	//	This means that each MainWorld item must stay for 1 turn, and each subworld SGT
	//  block must stay for 1 turn.
	//
	//	The logic was such that the MainWorld is being kept, but the subworld is not.
	//
	//
	if (repairpointsinperiod>7)
	{
		int rpip=repairpointsinperiod;
		int rpbpip=repairbridgepointsinperiod;
		while (rpip>7)
		{
			if (rpbpip>0)
				ReviveWorld(7,1);
			else
				ReviveWorld(7,0);
			rpip-=7;
			rpbpip-=1;
		}
		if (rpbpip)
 			ReviveWorld(rpip,1);
		else
			ReviveWorld(rpip,0);
		return;
	}


	if (firstblock)
	{

		struct	DamagedSGT
		{
			FIRSTFIELD(ULong,	UniqueID,uniqueid,13)			//UID is 14 bits
				BITFIELD(			ULong,pointsleft,14,17)		//max repair points = 7
				BITFIELD(			ULong,eltsleft,18,24);		//max elts to repair= 512
				LASTFIELD(			ULong,revivableeltsleft,25,31);		//max elts to repair= 512
		};
		enum	{MAX_DAMAGELIST=400};
		int	usedentries=0;
		DamagedSGT	damagelist[MAX_DAMAGELIST];
		{//scan of deadstream to find num of elements in all supergroups
			DeadBlockItterator	src(firstblock,UID_NULL);
			int targuid;
			UniqueID SGT;
			while ((targuid=src.GetWord())!=UID_NULL)
			{
				ItemPtr p=*Persons2::ConvertPtrUID(UniqueID(targuid));
				if (p && p->SGT)
					SGT=p->SGT;
				else
					SGT=(UniqueID)targuid;

				for (int entry=0;entry<usedentries;entry++)
					breakif (damagelist[entry].uniqueid==SGT);
				if (entry==usedentries)
				{
					usedentries++;
					damagelist[entry].uniqueid=SGT;
					damagelist[entry].eltsleft=0;
					damagelist[entry].revivableeltsleft=0;
				}

				UWord status=src.GetWord();
				UWord shape=src.GetWord();
				int	numelts=src.GetByte();
				while (numelts--)
				{	char v=src.GetByte();
					MinAnimData firstbyte=(MinAnimData&)v;
					if (firstbyte.itemstate || QuickRevivableBand(targuid))
					{
						damagelist[entry].eltsleft=damagelist[entry].eltsleft+1;
						if (firstbyte.repair)
							if (	firstbyte.itemstate!=DEAD	||	RevivableBand(targuid)	)
								damagelist[entry].revivableeltsleft=damagelist[entry].revivableeltsleft+1;
					}
					if (firstbyte.IsInvisible)
						src.SkipCountedInfo();
				}
				
			}
			while ((SGT=src.NextSGT())!=UID_NULL)
			{
				for (int entry=0;entry<usedentries;entry++)
					breakif (damagelist[entry].uniqueid==SGT);
				if (entry==usedentries)
				{
					usedentries++;
					damagelist[entry].uniqueid=SGT;
					damagelist[entry].eltsleft=0;
					damagelist[entry].revivableeltsleft=0;
				}
				while ((targuid=src.GetWord())!=UID_NULL)
				{
					//skip rest of info
					UWord status=src.GetWord();
					UWord shape=src.GetWord();
					int	numelts=src.GetByte();
					while (numelts--)
					{	char v=src.GetByte();
						MinAnimData firstbyte=(MinAnimData&)v;
						if (firstbyte.itemstate || QuickRevivableBand(targuid))
						{
							damagelist[entry].eltsleft=damagelist[entry].eltsleft+1;
							if (firstbyte.repair)
								if (	firstbyte.itemstate!=DEAD	||	RevivableBand(targuid)	)
									damagelist[entry].revivableeltsleft=damagelist[entry].revivableeltsleft+1;
								else
									INT3;
						}
						if (firstbyte.IsInvisible)
							src.SkipCountedInfo();
					}
				}
			}
			for (int entry=0;entry<usedentries;entry++)
			{													//DAW 27Jun99
				if (Persons2::getbandfromUID(damagelist[entry].uniqueid)==BritBridgeBAND)
					damagelist[entry].pointsleft=repairbridgepointsinperiod;
				else
					damagelist[entry].pointsleft=repairpointsinperiod;
			}
		}

		//ok.. now step through and repair.

		//
		//A group is fully repaired when all it's elements are cleared.
		//How do I know it is fully repaired, though?
	
		//I WON'T REMOVE AN ITEM UNTIL THE NEXT DAY
		//I won't remove an item unless there are no more damaged elements to follow
		//in the main world
		DeadBlock* newlist=NULL;

		{//scan of deadstream to revive
			DeadBlockItterator	src(firstblock,UID_NULL);
			int targuid;
			UniqueID SGT;
			Math_Lib.ResetRndCount();
			{//mainworld block
				DeadBlockItterator  trg(newlist,UID_NULL);
				bool reallyput=false;
				while ((targuid=src.GetWord())!=UID_NULL)
				{
					ItemPtr p=*Persons2::ConvertPtrUID(UniqueID(targuid));
					if (p && p->SGT)
						SGT=p->SGT;
					else
						SGT=(UniqueID)targuid;

					for (int entry=0;entry<usedentries;entry++)
						breakif (damagelist[entry].uniqueid==SGT);
					if (damagelist[entry].eltsleft==0)
					{	//skip and discard
						UWord status=src.GetWord();
						UWord shape=src.GetWord();
						int	numelts=src.GetByte();
						while (numelts--)
						{
							char v=src.GetByte();
							MinAnimData firstbyte=(MinAnimData&)v;
							if (firstbyte.IsInvisible)
								src.SkipCountedInfo();
						}
					}
					else
					{

						UWord status=src.GetWord();
						UWord shape=src.GetWord();
						int	numelts=src.GetByte();
						reallyput=true;
						trg.PutWord(targuid);
						trg.PutWord(status);
						trg.PutWord(shape);
						if (numelts==-1)
							numelts=numelts;
						trg.PutByte(numelts);

						while (numelts--)
						{
							UByte stat;
							int datalen;
							char* data;
							src.NextDeadElt(stat,datalen,data);
							MinAnimData firstbyte=(MinAnimData&)stat;
							if (firstbyte.itemstate)
							{
								if (!firstbyte.repair && !QuickRevivableBand(targuid))
									firstbyte.repair=1;
								else
									if (firstbyte.itemstate!=DEAD || RevivableBand(targuid))
									{
										if (Math_Lib.rnd()*damagelist[entry].eltsleft<damagelist[entry].pointsleft*65536)
										{
											firstbyte.itemstate--;
											if (QuickRevivableBand(targuid))
												damagelist[entry].pointsleft=0;
											else
												damagelist[entry].pointsleft=damagelist[entry].pointsleft-1;
											stat=(char&)firstbyte;
										}
										damagelist[entry].revivableeltsleft=damagelist[entry].revivableeltsleft-1;
									}
								damagelist[entry].eltsleft=damagelist[entry].eltsleft-1;
							}
							trg.SetNextDeadElt(stat,datalen,data);
						}//while numelts
					}//if eltsleft
				}//while getword
				if (reallyput)
					trg.PutWord(UID_NULL);
			}//mainworld block


			while ((SGT=src.NextSGT())!=UID_NULL)
			{
				for (int entry=0;entry<usedentries;entry++)
					breakif (damagelist[entry].uniqueid==SGT);
				if (damagelist[entry].eltsleft)
				{
					Math_Lib.ResetRndCount();
					DeadBlockItterator  trg(newlist,SGT);
					while ((targuid=src.GetWord())!=UID_NULL)
					{
						if (damagelist[entry].eltsleft==0)
						{	//skip and discard
							UWord status=src.GetWord();
							UWord shape=src.GetWord();
							int	numelts=src.GetByte();
							while (numelts--)
							{
								char v=src.GetByte();
								MinAnimData firstbyte=(MinAnimData&)v;
								if (firstbyte.IsInvisible)
									src.SkipCountedInfo();
							}
						}
						else
						{
							UWord status=src.GetWord();
							UWord shape=src.GetWord();
							int	numelts=src.GetByte();
							trg.PutWord(targuid);
							trg.PutWord(status);
							trg.PutWord(shape);
						if (numelts==-1)
							numelts=numelts;
							trg.PutByte(numelts);

							while (numelts--)
							{
								UByte stat;
								int datalen;
								char* data;
								src.NextDeadElt(stat,datalen,data);
								MinAnimData firstbyte=(MinAnimData&)stat;
								if (firstbyte.itemstate)
								{
									if (!firstbyte.repair&&!QuickRevivableBand(targuid))
										firstbyte.repair=1;
									else
										if (firstbyte.itemstate!=DEAD || RevivableBand(targuid))
										{
											if (Math_Lib.rnd()*damagelist[entry].eltsleft<damagelist[entry].pointsleft*65536)
											{
												firstbyte.itemstate--;
												if (QuickRevivableBand(targuid))
													damagelist[entry].pointsleft=0;
												else
													damagelist[entry].pointsleft=damagelist[entry].pointsleft-1;
												stat=(char&)firstbyte;
											}
											damagelist[entry].revivableeltsleft=damagelist[entry].revivableeltsleft-1;
										}
									damagelist[entry].eltsleft=damagelist[entry].eltsleft-1;
								}
								trg.SetNextDeadElt(stat,datalen,data);
							}//whilenumelts

						}//if eltsleft
					}//while getword
					trg.PutWord(0);							  //JIM 13/05/99
				}//if eltsleft
				else
				{
					if ((targuid=src.GetWord())!=UID_NULL)
					{	//Keep for 1 day only so last of repair gets through!
						DeadBlockItterator  trg(newlist,SGT);
						trg.PutWord(0);							  //JIM 13/05/99
					}
				}
			}//while SGT
		}//block trg
		ClrWorldDead();
		firstblock=newlist;
		olddaytime++;//=newdaytime;
	}
}

bool	DeadStream::DeadBlockItterator::MoveOwnerOfRestOfListToEndOf(DeadStream::DeadBlock* second)
{
	DeleteTempBlock();
	while(second->nextblock)
		second=second->nextblock;
	second->nextblock=curr;
	if (*base==curr)
	{
		*base=NULL;
		return false;
	}
	else
	{
		second=*base;
		while(second->nextblock!=curr)
			second=second->nextblock;
		second->nextblock=NULL;	
		curr=NULL;
		return true;
	}

}

//////////////////////////////////////////////////////////////////////
//
// Function:    FakeDamage
// Date:		17/08/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	DeadStream::FakeDamage(UniqueID targuid,ULong newpercent,bool clearifreducedamage)
{	
	if (newpercent>100)
		newpercent=100;
	newpercent*=7.5;
	static UniqueIDBand	testbands[]=
	{IllegalBAND,AfHangarBAND,AfFieldBAND,AfStaffBAND,AfStoresBAND,NULL_BAND};
	//Need to find all the items in the SG that are damagable 
	//and decide how much damage to give them
	//Only the main item, anything in the same band, 
	//and the 3 AF bands should now count towards damage.
	struct	DamagabeItems
	{	//I was concerned about modifying the SGT tables, but all the bands are in the mainwld.
		UniqueID		instance;
		ShapeNum		shape;
		int				order;
		struct	DL
		{
			UWord	weight:11,
					state:2,
					repair:1;

		};
		DL	damagelevels[64];
	} damagableitems[5][8]={UID_NULL};	//note that there is also a 1:1 lookup later
	int	damagecounts[6]={0};
	int	totaldamagelevel[6]={0};
	int	reqdamagelevel[6]={0};
	{limitscope
		damagableitems[0][0].instance=targuid;
		info_itemSPtr it=Persons2::ConvertPtrUID(targuid);
		if (it->Status.size!=ItemSize)											//MS 10Jul00
			return;														//MS 10Jul00
		damagableitems[0][0].shape=ShapeNum(it->shape.Evaluate());
		reqdamagelevel[0]=newpercent;
	}
	testbands[0]=Persons2::GetBandFromUID(targuid);
	{for (int damagablecount=1,tb=0;testbands[tb];tb++,damagablecount=0)
	{
 
		UniqueIDBand tbv=testbands[tb];
		UniqueIDBand db=tbv;
		if (tb==0)	
			db=NULL_BAND;
//DeadCode JIM 20Oct00 		int	basebandindex=0;
		for (int u=tbv;Persons2::GetBandFromUID(UniqueID(u))==tbv;u++)
		{
			info_itemSPtr it=Persons2::ConvertPtrUID(UniqueID(u));
			if (it && it->SGT==targuid)
			{
				damagableitems[tb][damagablecount].instance=UniqueID(u);
				damagableitems[tb][damagablecount].shape=ShapeNum(it->shape.Evaluate());
				reqdamagelevel[tb]+=newpercent*(0.7+0.003*Math_Lib.rnd(100));
				damagablecount++;
			}
		}

		damagableitems[tb][damagablecount].instance=UID_NULL;
		damagecounts[tb]=damagablecount;
	}}


	//Then need to modify the stream data to match. That will be fun!
	//Each of the 5 possible sections should be damaged to an equal overall level
	//To do that, each of the groups in that section should be hit equally

	//First, we need to assess the current damage for each element
	
	
	{limitscope
	UniqueID s;
	int order=0x10000;
	for (DeadBlockItterator	b(firstblock,UID_NULL);(s=b.SkipItem())!=UID_NULL;)
	{
		int tb,te=0;
		bool mbreak=false;
		for (tb=0;!mbreak && testbands[tb];tb++)
			for (te=0;!mbreak && te<damagecounts[tb];te++)
				if (damagableitems[tb][te].instance==s)
					mbreak=true;
		if (mbreak)
		{
			tb--;
			te--;
			damagableitems[tb][te].order=order;	
			GroupItterator g(ShapeNum(b.lastshape));
			int w;
			int totalweight=0;
			for (w=0;g;w++)
			{
				UByte	di1b;
				int		diplc;
				char*	dipld;

				b.NextDeadElt(di1b,diplc,dipld);

				damagableitems[tb][te].damagelevels[w].state=((MinAnimData&)di1b).itemstate;
				damagableitems[tb][te].damagelevels[w].repair=((MinAnimData&)di1b).repair;
				damagableitems[tb][te].damagelevels[w].weight=g.DamageWeight();
				totalweight+=g.DamageWeight();
				totaldamagelevel[tb]+=((MinAnimData&)di1b).itemstate*g.DamageWeight();
				g++;
			}
			for (;w<64;w++)
				damagableitems[tb][te].damagelevels[w].weight=0;
		 		if (totalweight<256)
  					AfxTrace("Shape under strength (Only %i) Shape %i(%s) UID=%04x(%s)",
   					totalweight,
 					b.lastshape,LoadResString(IDS_SHAPESSTART+b.lastshape),
					targuid,LoadResString(IDS_PLACENAMES_START+targuid));

		}
		order++;
	}}
	{for (int tb=0;testbands[tb];tb++)
		for (int te=0;te<damagecounts[tb];te++)
			if (damagableitems[tb][te].order==0)
			{
				ItemPtr i=Persons2::ConvertPtrUID(damagableitems[tb][te].instance);
				GroupItterator g(i->shape);
				int w;
				int	totalweight=0;
				for (w=0;g;w++)
				{

					damagableitems[tb][te].damagelevels[w].state=0;
					damagableitems[tb][te].damagelevels[w].repair=0;
					damagableitems[tb][te].damagelevels[w].weight=g.DamageWeight();
					totalweight+=g.DamageWeight();

					g++;
				}
				for (;w<64;w++)
					damagableitems[tb][te].damagelevels[w].weight=0;
				if (totalweight<256)
					AfxTrace("Shape under strength (Only %i) Shape %i(%s) UID=%04x(%s)",
						totalweight,
						(ShapeNum)i->shape,LoadResString(IDS_SHAPESSTART+i->shape),
						targuid,LoadResString(IDS_PLACENAMES_START+i->shape));
							
	}		}
	
	//I now have all the existing damage levels and weights, and can compare the total weights
	//I can generate new damage levels to build the required total damage level in each category
	Math_Lib.ResetRndCount();
	{for (int tb=0;testbands[tb];tb++)
	{	
		int	stilldamageable[10]={0,1,2,3,4,5,6,7,8,9};
		int stilldamageablecount=damagecounts[tb];
		if (clearifreducedamage && totaldamagelevel[tb]>reqdamagelevel[tb])
		while (totaldamagelevel[tb]>reqdamagelevel[tb])
		{
			int r=Math_Lib.rnd();
			int ite=((r&0xff00)*stilldamageablecount)>>16;
			int te=stilldamageable[ite];
			int c;		r=r&15;	//get first 16 elements equally. If 15th is fully damaged tends to go sequentially.

			for (c=0;c<64;c++)
			{
				r=(r+1)&63;
				breakif( damagableitems[tb][te].damagelevels[r].weight!=0 && damagableitems[tb][te].damagelevels[r].state!=0);
			}
			if (c!=64)
			{
				damagableitems[tb][te].damagelevels[r].state--;
				totaldamagelevel[tb]-=damagableitems[tb][te].damagelevels[r].weight;
				if (damagableitems[tb][te].order==0)
					damagableitems[tb][te].order=-1;
			}
			else
			{	//can't undamage this item any more - remove from list
				stilldamageablecount--;
				stilldamageable[ite]=stilldamageable[stilldamageablecount];
				assert (stilldamageablecount!=0,"Nothing left to UNdamage in group!!!!!");
			}
		}
		else
		while (totaldamagelevel[tb]<reqdamagelevel[tb])
		{
			int r=Math_Lib.rnd();
			int ite=((r&0xf000)*stilldamageablecount)>>16;
			int te=stilldamageable[ite];
			int c;		
			r=r&0x1ff;	//get first 16 elements equally. If 15th is fully damaged tends to go sequentially.

			do{
				ite=r;
				for (c=0;c<64;c++)
				{
					if (damagableitems[tb][te].damagelevels[c].state!=3)
						r=r-damagableitems[tb][te].damagelevels[c].weight;
					breakif(r<0);

				}
			}while (ite!=r && r>=0);

			if (r<0)
			{
				damagableitems[tb][te].damagelevels[c].state++;
				damagableitems[tb][te].damagelevels[c].repair=1;
				totaldamagelevel[tb]+=damagableitems[tb][te].damagelevels[c].weight;
				if (damagableitems[tb][te].order==0)
					damagableitems[tb][te].order=-1;
			}
			else
			{	//can't damage this item any more - remove from list
				stilldamageablecount--;
				stilldamageable[ite]=stilldamageable[stilldamageablecount];
				if (stilldamageablecount!=0)
				{
					INT3;	//"Nothing left to damage in group!" Put curser here: targuid
					break;
				}
			}
		}
	}}
	//I have now generated new damage levels, and now I must put them back....
	//Order field in damage level can contain 3 possible values:
	//0x10000+: Item already known to damage system
	//0:		Item not known. No damage
	//-1:		Item not known. New damage has occured
	
//	INT3;
	DeadBlock* newlist=NULL;
	{limitscope
		//scan of deadstream to revive
		DeadBlockItterator	src(firstblock,UID_NULL);
		DeadBlockItterator	trg(newlist,UID_NULL);
		UniqueID SGT;
		while ((targuid=UniqueID(src.GetWord()))!=UID_NULL)
		{
			int tb,te;
			bool mbreak=false;
			for (tb=0;!mbreak && testbands[tb];tb++)
				for (te=0;!mbreak && te<damagecounts[tb];te++)
					if (damagableitems[tb][te].instance==targuid)
						mbreak=true;
			if (!mbreak)
			{	//copy over unchanged
					UWord status=src.GetWord();
					UWord shape=src.GetWord();
					int	numelts=src.GetByte();
					trg.PutWord(targuid);
					trg.PutWord(status);
					trg.PutWord(shape);
					if (numelts==-1)
						numelts=numelts;
					trg.PutByte(numelts);

					while (numelts--)
					{
						UByte stat;
						int datalen;
						char* data;
						src.NextDeadElt(stat,datalen,data);
						//no manipulation
						trg.SetNextDeadElt(stat,datalen,data);
					}//while numelts


			}
			else
			{	//copy and modify data based on flags
				tb--;
				te--;
					UWord status=src.GetWord();
					UWord shape=src.GetWord();
					int	numelts=src.GetByte();
					trg.PutWord(targuid);
					trg.PutWord(status);
					trg.PutWord(shape);
					if (numelts==-1)
						numelts=numelts;
					trg.PutByte(numelts);

					for (int eltc=0;eltc<numelts;eltc++)
					{
						UByte stat;
						int datalen;
						char* data;
						src.NextDeadElt(stat,datalen,data);
						MinAnimData& firstbyte=(MinAnimData&)stat;
						firstbyte.itemstate=damagableitems[tb][te].damagelevels[eltc].state;
						firstbyte.repair=damagableitems[tb][te].damagelevels[eltc].repair;
						trg.SetNextDeadElt(stat,datalen,data);
					}//while numelts
			}
		}
		for (int tb=0;testbands[tb];tb++)
			for (int te=0;te<damagecounts[tb];te++)
				if (damagableitems[tb][te].order==-1)
				{	//append items not originally in list
					ITEM_STATUS is;
					is.size=ITEMSIZE;
					targuid=damagableitems[tb][te].instance;
					UWord status=is.overview_BlueLaunch.value;

					UWord shape=damagableitems[tb][te].shape;
					GroupItterator g(damagableitems[tb][te].shape);
					int	numelts=g.NumElts();
					trg.PutWord(targuid);
					trg.PutWord(status);
					trg.PutWord(shape);
					if (numelts==-1)
						numelts=numelts;
					trg.PutByte(numelts);

					for (int eltc=0;eltc<numelts;eltc++)
					{
						UByte stat;

						MinAnimData firstbyte;
						firstbyte.nolaunchers=0;
						firstbyte.itemstate=damagableitems[tb][te].damagelevels[eltc].state;
						firstbyte.repair=damagableitems[tb][te].damagelevels[eltc].repair;
						stat=(UByte&)firstbyte;
						trg.SetNextDeadElt(stat,0,NULL);
					}//while numelts
				}
		trg.PutWord(0);
	}//end scope of itterator
	//reappend SGT member damage stuff
	{limitscope
		DeadBlockItterator	src(firstblock,UID_NULL);
		UniqueID sgtlist=src.NextSGT();
		if (sgtlist)
			src.MoveOwnerOfRestOfListToEndOf(newlist);
	}
	ClrWorldDead();
	firstblock=newlist;

}

//////////////////////////////////////////////////////////////////////
//
// Function:    CheckDamage
// Date:		17/08/00
// Author:		JIM
//
//Description: For every item in the damage data check what effect it has in the 2d
//			All the important damage data is in the main world.
//			I am not going to scan the SGT sections at all!!!!!
//			Note that this would not work well for Mig Alley...
//
//////////////////////////////////////////////////////////////////////
void	NodeData::CheckDamage(DeadStream& ds)
{
	//
	//	First job is to get together a list of the UIDs that have been damaged
	//	UniqueIDField costs 16K/8=2Kb
	//	If I spend 4 bytes on each SGT that allows 500 SGTs in the same space.
	//
	//

	// IMPORTANT NOTE:
	//	Each SGT member item that is damaged then repaired MUST stay in the list fully
	//  alive for 1 more session in order for the repair to register.
	//	This means that each MainWorld item must stay for 1 turn, and each subworld SGT
	//  block must stay for 1 turn.
	//
	//	The logic is such that the MainWorld is being kept, but the subworld is not.
	//
	//


	if (ds.firstblock)
	{

		struct	DamagedSGT
		{
			FIRSTFIELD(ULong,	UniqueID,uniqueid,13)			//UID is 14 bits
				BITFIELD(			ULong,pointsleft,14,18)		//max repair points = 31
				LASTFIELD(			ULong,eltsleft,19,31);		//max elts to repair= 8K
		};
		enum	{MAX_DAMAGELIST=400};
		int	usedentries=0;
		DamagedSGT	damagelist[MAX_DAMAGELIST];
		{//scan of deadstream to find num of elements in all supergroups
			DeadStream::DeadBlockItterator	src(ds.firstblock,UID_NULL);
			int targuid;
			UniqueID SGT;
			while ((targuid=src.GetWord())!=UID_NULL)
			{
				ItemPtr p=*Persons2::ConvertPtrUID(UniqueID(targuid));
				if (p && p->SGT)
					SGT=p->SGT;
				else
					SGT=(UniqueID)targuid;

				for (int entry=0;entry<usedentries;entry++)
					breakif (damagelist[entry].uniqueid==SGT);
				if (entry==usedentries)
				{
					usedentries++;
					damagelist[entry].uniqueid=SGT;
					damagelist[entry].eltsleft=0;
				}

				UWord status=src.GetWord();
				UWord shape=src.GetWord();
				int	numelts=src.GetByte();
				while (numelts--)
				{	char v=src.GetByte();
					MinAnimData firstbyte=(MinAnimData&)v;
					if (firstbyte.itemstate)
						damagelist[entry].eltsleft=damagelist[entry].eltsleft+1;
					if (firstbyte.IsInvisible)
						src.SkipCountedInfo();
				}
				
			}
//DeadCode JIM 13Sep00 			while ((SGT=src.NextSGT())!=UID_NULL)
//DeadCode JIM 13Sep00 			{
//DeadCode JIM 13Sep00 				for (int entry=0;entry<usedentries;entry++)
//DeadCode JIM 13Sep00 					breakif (damagelist[entry].uniqueid==SGT);
//DeadCode JIM 13Sep00 				if (entry==usedentries)
//DeadCode JIM 13Sep00 				{
//DeadCode JIM 13Sep00 					usedentries++;
//DeadCode JIM 13Sep00 					damagelist[entry].uniqueid=SGT;
//DeadCode JIM 13Sep00 					damagelist[entry].eltsleft=0;
//DeadCode JIM 13Sep00 				}
//DeadCode JIM 13Sep00 				while ((targuid=src.GetWord())!=UID_NULL)
//DeadCode JIM 13Sep00 				{
//DeadCode JIM 13Sep00 					//skip rest of info
//DeadCode JIM 13Sep00 					UWord status=src.GetWord();
//DeadCode JIM 13Sep00 					UWord shape=src.GetWord();
//DeadCode JIM 13Sep00 					int	numelts=src.GetByte();
//DeadCode JIM 13Sep00 					while (numelts--)
//DeadCode JIM 13Sep00 					{	char v=src.GetByte();
//DeadCode JIM 13Sep00 						MinAnimData firstbyte=(MinAnimData&)v;
//DeadCode JIM 13Sep00 						if (firstbyte.itemstate)
//DeadCode JIM 13Sep00 							damagelist[entry].eltsleft=damagelist[entry].eltsleft+1;
//DeadCode JIM 13Sep00 						if (firstbyte.IsInvisible)
//DeadCode JIM 13Sep00 							src.SkipCountedInfo();
//DeadCode JIM 13Sep00 					}
//DeadCode JIM 13Sep00 				}
//DeadCode JIM 13Sep00 			}
//DeadCode JIM 13Sep00 			for (int entry=0;entry<usedentries;entry++)
//DeadCode JIM 13Sep00 			{													//DAW 27Jun99
//DeadCode JIM 13Sep00 				if (Persons2::getbandfromUID(damagelist[entry].uniqueid)==BritBridgeBAND)
//DeadCode JIM 13Sep00 					damagelist[entry].pointsleft=repairbridgepointsinperiod;
//DeadCode JIM 13Sep00 				else
//DeadCode JIM 13Sep00 					damagelist[entry].pointsleft=repairpointsinperiod;
//DeadCode JIM 13Sep00 			}
		}
	//Ok.. I have a list of all the damaged SGTs now... Now what????
		bool	oldspeak = Node_Data.intel.stoppedspeaking;

		Node_Data.intel.stoppedspeaking = false;						//RJS 8Nov00

		for (int entry=0;entry<usedentries;entry++)
			CheckDamage(ds,(damagelist[entry].uniqueid));

		Node_Data.intel.stoppedspeaking = oldspeak;							//RJS 8Nov00
	}
}

int	NodeData::GetCheckDamage(DeadStream& ds,UniqueID SGT)
{
	int maindamage=0;
	if (ds.firstblock)
	{
		//count up damage in this shape
		DeadStream::DeadBlockItterator	src(ds.firstblock,UID_NULL);
		if (src.SkipToItem(SGT))
		{
//DeadCode JIM 13Sep00 			UWord status=src.GetWord();
//DeadCode JIM 13Sep00 			UWord shape=src.GetWord();
			GroupItterator g=(ShapeNum(src.lastshape));
			int	numelts=src.lastnumelts;//.GetByte();
			if (numelts==-1)
				numelts=numelts;
			while (numelts--)
			{
				UByte stat;
				int datalen;
				char* data;
				src.NextDeadElt(stat,datalen,data);
				MinAnimData& firstbyte=(MinAnimData&)stat;
				int	points=g.percentdamage*firstbyte.itemstate;
				maindamage+=points;
				g++;
			}//while numelts
			//should make up to 1024 points of damage
		}

	}
	if (maindamage>int(30*7.5) && Node_Data[SGT].IsA(Target::TSS_TargetFactory))
	{
		TargetFactory* tf=Node_Data[SGT];
		if (tf->maxdispersedperweek>0)
		{
//DeadCode JIM 22Sep00 			INT3;	//JIM This is here because the dispersed production is untested
			tf->maxdispersedperweek=-tf->maxdispersedperweek;
			int	datefromstart=(MMC.currdate-MMC.startdate)/SECSPERDAY;
			if (datefromstart>30)
				tf->perweekwhenout+=(datefromstart-30)/5;
//DeadCode JIM 20Sep00 Don't have a message for dispersed production.			Node_Data.intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_LWOPERATIONAL ,gruppe[i].homeairfield,UID_NULL,TargetIndexes(gruppe[i].squadron,gruppe[i].ACTotal()));
		}
		else
		{
			if (tf->perweekwhenout<-tf->maxdispersedperweek)
			tf->perweekwhenout++;
		}


	}
	return maindamage/7.5;
}
int	NodeData::GetCheckDamage(DeadStream& ds,UniqueID SGT,int&a,int&b,int&c,int&d)
{
	int maindamage=0;
	if (ds.firstblock)
	{
		maindamage=GetCheckDamage(ds,SGT);
		TargetGroup* trg=Node_Data[SGT];
		if (trg)
			if (trg->IsA(Target::TSS_TargetAirfield))
			{
//DeadCode JIM 20Oct00 				TargetFighterField* ta=*trg;
				int damagebits[5]={0,0,0,maindamage*7.5,0};
				const UniqueIDBand damagebands[3]={AfStoresBAND,AfFieldBAND,AfStaffBAND};
				DeadStream::DeadBlockItterator	src(ds.firstblock,UID_NULL);
				UniqueID targuid;
				while ((targuid=UniqueID(src.GetWord()))!=UID_NULL)
				{
					ItemPtr p=*Persons2::ConvertPtrUID(UniqueID(targuid));
					int slot=-1;
					if (p && p->SGT==SGT)
					{
						UniqueIDBand tb=Persons2::GetBandFromUID(targuid);
						if (tb==damagebands[0])
							slot=0;
						elseif (tb==damagebands[1])
							slot=1;
						elseif (tb==damagebands[2])
							slot=2;
					}
					if (slot!=-1)
					{
						UWord status=src.GetWord();
						UWord shape=src.GetWord();
						GroupItterator g=(ShapeNum(shape));
						int	numelts=src.GetByte();
						if (numelts==-1)
							numelts=numelts;
						int subdamage=0;
						while (numelts--)
						{
							UByte stat;
							int datalen;
							char* data;
							src.NextDeadElt(stat,datalen,data);
							MinAnimData& firstbyte=(MinAnimData&)stat;
							int	points=g.percentdamage*firstbyte.itemstate;
							subdamage+=points;
							g++;
						}//while numelts
						//should make up to 1024 points of damage
						damagebits[slot]=subdamage;
					}
					else
					{	//not interested
						UWord status=src.GetWord();
						UWord shape=src.GetWord();
						int	numelts=src.GetByte();
						while (numelts--)
						{
							UByte stat;
							int datalen;
							char* data;
							src.NextDeadElt(stat,datalen,data);
						}//while numelts
					}
				}
				a=damagebits[3]/7.5;
				b=damagebits[0]/7.5;
				c=damagebits[1]/7.5;
				d=damagebits[3]/7.5;
				maindamage=(damagebits[0]+damagebits[1]+damagebits[2]+damagebits[3])/30;
			}
			else
				a=b=c=d=0;
	}
	return maindamage;
}

int	NodeData::CheckDamage(DeadStream& ds,UniqueID SGT)
{
	int maindamage=0;
	if (ds.firstblock)
	{
		TargetGroup* trg=Node_Data[SGT];
		if (trg)
			if (trg->IsA(Target::TSS_TargetAirfield))
			{
				int a,b,c,d;
				maindamage=GetCheckDamage(ds,SGT,a,b,c,d);
				TargetFighterFieldPtr(*trg)->ApplyDamage(maindamage,a,b,c,d,IllegalSepID);

			}
			else
			{
				maindamage=GetCheckDamage(ds,SGT);
				trg->ApplyDamage(maindamage,IllegalSepID);
			}
	}
	
	return maindamage;
}
//////////////////////////////////////////////////////////////////////
//
// Function:    DecodeDamage
// Date:		24/03/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
int	DeadStream::DecodeDamage(UniqueID SGT,DamageDef* damagetable)
{	//first find damage for SGT
	int	numreturned=0;
	{
		DeadBlockItterator	b(firstblock,UID_NULL);
		if (b.SkipToItem(SGT))
		{
			damagetable->memberid=SGT;
			damagetable->loadedid=SGT;
			(UWord&)damagetable->status=b.lastStatus;
			damagetable->shape=ShapeNum(b.lastshape);
//			char elts=b.GetByte();
//			while (--elts>=0)
//			{
//				char v=b.GetByte();	//first anim byte
//				if (((MinAnimData&)v).IsInvisible)
//					b.SkipCountedInfo();
//			}
//			{
//				damagetable->animbytesskip=0;
//				damagetable->animbyteslen=0;
//				damagetable->remaininganimbytes=NULL;
//			}
			damagetable++;
			numreturned++;
		}
	}
	{
		UniqueID s;
		for (DeadBlockItterator	b(firstblock,UID_NULL);(s=b.SkipItem())!=UID_NULL;)
			if (ItemPtr(*Persons2::ConvertPtrUID(s))->SGT==SGT)
			{
				Persons2::ConvertPtrUID(s)->Status.deaded=TRUE;
				damagetable->memberid=s;
				damagetable->loadedid=s;
				(UWord&)damagetable->status=b.lastStatus;
				damagetable->shape=ShapeNum(b.lastshape);
				damagetable++;
				numreturned++;
			}
	}

	{
		UniqueID targuid;
		for (DeadBlockItterator	c(firstblock,SGT);(targuid=c.SkipItem())!=UID_NULL;)
		{	//need to convert targuid to correct element uid
			damagetable->memberid=targuid;

			int targband=Persons2::getbandfromUID(targuid);
			ItemPtr p=NULL;
			for (int skip=targuid-targband,u=targband,max=Persons2::getbandMAXfromUID(targuid);skip>=0;u++)
			{
				if (u==max)
				{
					u=0;
					p=NULL;
					break;
				}
				p=*Persons2::ConvertPtrUID(UniqueID(u));
				if (p && p->SGT==SGT)
					skip--;
			}
			if (u && p && p->SGT==SGT)
			{
				damagetable->loadedid=UniqueID(u-1);
				p->Status.deaded=TRUE;
			}
			else
				damagetable->loadedid=UID_NULL;
			(UWord&)damagetable->status=c.lastStatus;
			damagetable->shape=ShapeNum(c.lastshape);

			{
				damagetable->animbytesskip=0;
				damagetable->animbyteslen=0;
				damagetable->remaininganimbytes=NULL;
			}
			damagetable++;
			numreturned++;
		}
	}
	return numreturned;
}
//
// ShapeItterator -- DeadBlockItterator interface
//
//
//
//
 
DeadStream::DeadBlockItterator*	
	GroupItterator::DeadIttCopy(DeadStream::DeadBlockItterator* I)
{
	return new DeadStream::DeadBlockItterator(I); 
}
void	GroupItterator::DeadIttDelete(DeadStream::DeadBlockItterator* I)
{
	delete I;
}
void	GroupItterator::NextDeadIttElt(DeadStream::DeadBlockItterator* I,UByte&di1b,int&diplc,char*&dipld)
{
	I->NextDeadElt(di1b,diplc,dipld);
}


//
// Group -- ShapeItterator interafce dummies
//
//		 ... code in mfc\damage.cpp
//
//DeadCode RJS 15Feb99 bool	GroupItterator::operator++(int)		{status++;return (status<10);}				
//move on to next element? 
//if not NULL Push animptr,grpindexer, and deadstream forward
//DeadCode RJS 15Feb99 GroupItterator::operator bool()		{return (status<10);}	//reached end of group?


//DeadCode RJS 15Feb99 int GroupItterator::NumElts(void)	
//DeadCode RJS 15Feb99 {return 5;}
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 char& GroupItterator::AnimDataByte()
//DeadCode RJS 15Feb99 {
//DeadCode RJS 15Feb99 	static char dummy=5;
//DeadCode RJS 15Feb99 	return dummy;
//DeadCode RJS 15Feb99 }
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 int GroupItterator::PostLauncherDataSize()
//DeadCode RJS 15Feb99 {
//DeadCode RJS 15Feb99 	return 0;
//DeadCode RJS 15Feb99 }
//DeadCode RJS 15Feb99 
//DeadCode RJS 15Feb99 char * GroupItterator::PostLauncherDataLoc()
//DeadCode RJS 15Feb99 {
//DeadCode RJS 15Feb99 	return NULL;
//DeadCode RJS 15Feb99 }

static	DistanceFactors	
Distance[]=
{
	{	//SHORT			//MEDIUM		//far
		10000,			1000,			100000,
		IDS_CM_NAME,	IDS_M_NAME,		IDS_KM_NAME,
		IDS_CM_SH,		IDS_M_SH,		IDS_KM_SH
	},
	{
		25440,				305,		185300,
		IDS_IN_NAME,	IDS_FT_NAME,	IDS_NM_NAME,
		IDS_IN_ABBR,	IDS_FT_ABBR,	IDS_NM_ABBR
	}
};
static	AltitudeFactors
Altitude[]=
{
	{	//SHORT			//MEDIUM		//far
		10000,			1000,			100000,
		IDS_CM_NAME,	IDS_M_NAME,		IDS_KM_NAME,
		IDS_CM_SH,		IDS_M_SH,		IDS_KM_SH,
		//scale
		500,2,16						//could do 16
	},
	{
		25440,			305,			30480,
		IDS_IN_NAME,	IDS_FT_NAME,	IDS_THFT_NAME,
		IDS_IN_ABBR,	IDS_FT_ABBR,	IDS_THFT_ABBR,
		//scale
		1000,2,25		   //was 40		//could do 24
	}
};
static	SpeedFactors
Speed[]=
{
	{	//persec		//permin		//perhr
		0.1,				6.0,		0.36,
		IDS_MPERSEC,	IDS_MPERMIN,	IDS_KMPERHR,
		IDS_MPSEC,		IDS_MPMIN,		IDS_KMPHR
	},
	{
		0.25440,		0.5088,			0.19426,	//0.5147,	//CSB 23/06/99	
		IDS_INPERSEC,	IDS_FTPERMIN,	IDS_KNOTTS,
		IDS_INPS,		IDS_FTPM,		IDS_KTS
	}
};
static	MoneyFactors
Money[]=
{
	{
		100,		//penceperunit;
		100,		//fractionsperunit;
		'.',		//fractionseparator;
		IDS_PENCE,	IDS_POUNDS,	//unitname,
		IDS_PEE,	IDS_PNDS	//unitabbr;
	}
};
static	MassFactors
Mass[]=
{
	{//conversion in grammes
		1000,
		IDS_KG,
		IDS_KG
	},
	{
		454,
		IDS_LBS,
		IDS_LBS
	}
};
void	SetFiltersFromSaveGame();
void SaveData::SetUnits()
{
	if (Save_Data.gamedifficulty [GD_UNITS])
	{
		dist=Distance[METRIC];
		alt=Altitude[METRIC];
		mass = Mass[METRIC];
		speed=Speed[METRIC];
	}else
	{
		dist=Distance[IMPERIAL];
	   	alt=Altitude[IMPERIAL];
		mass = Mass[IMPERIAL];
	   	speed=Speed[IMPERIAL];
	}

}
void SaveData::InitPreferences(int wh)
{
	HWND hWnd=(HWND)wh;

	flightdifficulty=0;
	flightdifficulty |= FD_SPINS;						// done
	flightdifficulty |= FD_WINDEFFECTS;						// done

	gamedifficulty |= GD_VULNERABLE;
	gamedifficulty |= GD_AUTOPADLOCKTOG;
//DeadCode AMM 9Oct00 	gamedifficulty |= GD_GEFFECTS;									  //rdh 14/04/99
//DeadCode AMM 9Oct00 	gamedifficulty |= GD_INJURYEFFECTS;								  //rdh 14/04/99
//DeadCode AMM 9Oct00 	gamedifficulty |= GD_WHITEOUT;									  //rdh 14/04/99
	gamedifficulty |= GD_PERFECTRADARASSISTEDGUNSIGHT;				  //rdh 14/04/99
	gamedifficulty |= GD_PERIPHERALVISION;							  //rdh 14/04/99
	gamedifficulty |= GD_HUDINSTACTIVE;								  //rdh 14/04/99
	gamedifficulty |= GD_AUTOVECTORING;								  //RDH 18/04/99
	gamedifficulty %= GD_VISIBLEMIGSCHEAT;
	gamedifficulty |=  GD_DISPLAYMESSAGES;
	toolbars=-1;
	toolbars%=TB_FILTERS;
	toolbars%=TB_COMMS;
//DEADCODE RDH 28/02/00 	toolbars%=TB_TITLE;
	toolbars%=TB_STATUS;

	keysensitivity=3;													//JON 17Oct00
	if (LoadResString(IDS_SHORT_DIST_ABBR)[0]==LoadResString(IDS_CM_SH)[0])
	{
		dist=Distance[METRIC];
		gamedifficulty |= GD_UNITS;
	}else
	{
	   	dist=Distance[IMPERIAL];
		gamedifficulty %= GD_UNITS;
	}

	if (LoadResString(IDS_SHORT_ALT_ABBR)[0]==LoadResString(IDS_CM_SH)[0])
		alt=Altitude[METRIC];
	else
	   	alt=Altitude[IMPERIAL];
	if  (LoadResString(IDS_MASS_ABBR)[0]==LoadResString(IDS_KG)[0])
		mass = Mass[METRIC];
	else
		mass = Mass[IMPERIAL];
	if (LoadResString(IDS_SHORTPS)[0]==LoadResString(IDS_MPSEC)[0])
		speed=Speed[METRIC];
	else
	   	speed=Speed[IMPERIAL];

	infoLineCount=1;	//want to see messages											  //RDH 20/06/99

	curr=Money[ENGLISH];
	mapfilters= 0;														//RDH 06/03/00
	mapfilters|=FILT_OPERATIONALITEMS;
	mapfilters|=FILT_DAMAGEDITEMS;
	mapfilters|=FILT_DESTROYEDITEMS;
	mapfilters|=FILT_CH;												//RDH 06/03/00
	mapfilters|=FILT_CHL;												//RDH 06/03/00
	mapfilters|=FILT_CONVOYS;											//RDH 06/03/00
	mapfilters|=FILT_LARGEICONS;									//RDH 06/03/00
	mapfilters|=FILT_LWARROWS;											//RDH 13/03/00
	mapfilters|=FILT_RAFSAG;
	mapfilters|=FILT_LWSAG;
	mapfilters|=FILT_AF_FIGHTER;										//RDH 10Sep00
	mapfilters|=FILT_AF_BOMBER;
	mapfilters|=FILT_AF_COASTAL;
	mapfilters|=FILT_FACTORYFIGHTER;
	mapfilters|=FILT_FACTORYBOMBER;
	mapfilters|=FILT_FACTORYOTHER;										//RDH 10Sep00


	lwplots = 	PL_REALISTIC;												//RDH 10/03/00

//DEADCODE RDH 06/01/00 	mapfilters|= FILT_RED_SUPPLY;
//DEADCODE RDH 06/01/00 	mapfilters|= FILT_RED_BRIDGE;
//DEADCODE RDH 06/01/00 	mapfilters|= FILT_MAINWP;
//DEADCODE RDH 06/01/00 	mapfilters|= FILT_BLUE_AIRFIELDS;
//DEADCODE RDH 06/01/00 	mapfilters|= FILT_FRONTLINE;

	_Analogue.tune	[AU_AILERON]	.deadzones = DZ_SMALL;						  //RDH 24/05/99
	_Analogue.tune	[AU_ELEVATOR]	.deadzones = DZ_SMALL;					  //RDH 24/05/99
	_Analogue.tune	[AU_RUDDER]		.deadzones = DZ_SMALL;						  //RDH 24/05/99
									         
	_Analogue.tune	[AU_THROTTLE]	.deadzones = DZ_SMALL;						  //RDH 24/05/99 //RDH 29/11/99
	_Analogue.tune	[AU_THROTTLE2]	.deadzones = DZ_SMALL;					  //RDH 24/05/99 //RDH 29/11/99
	_Analogue.tune	[AU_PROPPITCH]	.deadzones = DZ_SMALL;						  //RDH 24/05/99 //RDH 29/11/99
	_Analogue.tune	[AU_PROPPITCH2]	.deadzones = DZ_SMALL;						  //RDH 24/05/99
									         
 	_Analogue.tune	[AU_VIEWP]		.deadzones = DZ_SMALL;						  //RDH 24/05/99 //RDH 29/11/99
	_Analogue.tune	[AU_VIEWZ]		.deadzones = DZ_SMALL;					  //RDH 24/05/99 //RDH 29/11/99
	_Analogue.tune	[AU_COCKPIT]	.deadzones = DZ_SMALL;						  //RDH 24/05/99 //RDH 29/11/99
	_Analogue.tune	[AU_GUNP]		.deadzones = DZ_SMALL;						  //RDH 24/05/99
									         
	_Analogue.tune	[AU_AILERON]	.mode	 = AM_ARCADE;						  //RDH 24/05/99
	_Analogue.tune	[AU_ELEVATOR]	.mode	 = AM_ARCADE;					  //RDH 24/05/99
	_Analogue.tune	[AU_RUDDER]		.mode	 = AM_ARCADE;						  //RDH 24/05/99
									         
	_Analogue.tune	[AU_THROTTLE]	.mode	 = AM_ARCADE;						  //RDH 24/05/99 //RDH 29/11/99
	_Analogue.tune	[AU_THROTTLE2]	.mode	 = AM_ARCADE;					  //RDH 24/05/99 //RDH 29/11/99
	_Analogue.tune	[AU_PROPPITCH]	.mode	 = AM_ARCADE;						  //RDH 24/05/99 //RDH 29/11/99
	_Analogue.tune	[AU_PROPPITCH2]	.mode	 = AM_ARCADE;						  //RDH 24/05/99
									         
 	_Analogue.tune	[AU_VIEWP]		.mode	 = AM_LOW;						  //RDH 24/05/99 //RDH 29/11/99
	_Analogue.tune	[AU_VIEWH]		.mode	 = AM_LOW;							//AMM 28Mar100
	_Analogue.tune	[AU_VIEWZ]		.mode	 = AM_LOW;					  //RDH 24/05/99 //RDH 29/11/99
	_Analogue.tune	[AU_UI_X]	.mode		 = AM_HIGH;						  //RDH 24/05/99 //RDH 29/11/99
	_Analogue.tune	[AU_UI_Y]	.mode		 = AM_HIGH;						  //RDH 24/05/99 //RDH 29/11/99
	_Analogue.tune	[AU_GUNP]		.mode	 = AM_LOW;						  //RDH 24/05/99
	_Analogue.tune	[AU_GUNH]		.mode	 = AM_LOW;							//AMM 28Mar100

	_Analogue.tune[AU_VIEWP]	.aliased	%=AA_TT_REVERSE;	//=true;
	_Analogue.tune[AU_UI_Y]		.aliased	%=AA_TT_REVERSE;	//=false;
	_Analogue.tune[AU_GUNP]		.aliased	|=AA_TT_REVERSE;	//=false;

	_Analogue.tune[AU_VIEWH]	.aliased	%=AA_TT_REVERSE;	//=false;
	_Analogue.tune[AU_UI_X]		.aliased	%=AA_TT_REVERSE;	//=false;
	_Analogue.tune[AU_GUNH]		.aliased	%=AA_TT_REVERSE;	//=false;


//DEADCODE RDH 30/06/99 	Save_Data.targetsize = TS_LARGE;
	targetsize = TS_MEDIUM;
//DeadCode CSB 27Jul00 	autopilotskillUN  = 2;								  //RDH 09/07/99
//DeadCode CSB 27Jul00 	autopilotskillRED = 2;								  //RDH 09/07/99
	autopilotskillLW  = 2;								  //RDH 09/07/99
	autopilotskillRAF = 2;								  //RDH 09/07/99
	// SFX stuff...
	vol.sfx = 125;
	vol.uisfx = 125;
	vol.uiambient = 64;
	vol.music = 64;
	vol.rchat = 90;
	vol.engine = 64;

	defaultzoom = 2;
	secondzoom = 10;
// initially assign default music device is one is avilable

	if (!InitMusicDevice())
		MusicDevice=GUID_NULL;

// initially Sound Device is default

	SFXDevice=GUID_NULL;

	detail_3d %= DETAIL3D_PADLOCKCHEAT;

//PD 11Feb99 - Dave I moved these up here
//PD 11Feb99 - Dave I moved these up here

	lastsavegame = "Bob";
	lastpackname = "Bob.prf";
	lastreplayname = "Bob.cam";

	strcpy(CommsPlayerName,"Bob");

	nextdialposmem=0;	//This is an array of remembered dialog and tool bar positions
						//JIM 03/04/00

	ui_horizontalres[UIR_SMACKER]=	640;
	ui_horizontalres[UIR_SCRAMBLE]=	1024;		//1024 is same size as artwork
	if (ui_horizontalres[UIR_FIRSTH]<1024)
	{
		ui_horizontalres[UIR_MAP]=		1024;			//0 means use desktop
		ui_horizontalres[UIR_FRAG]=		1024;			//1 can mean use map
	}
	else
	{
		ui_horizontalres[UIR_MAP]=		UIRC_DESK;			//0 means use desktop
		ui_horizontalres[UIR_FRAG]=		UIRC_DESK;			//1 can mean use map
	}
//DeadCode JIM 18Oct00 	ui_horizontalres[UIR_FIRST]=	0;			//First call fills this with desktop
	ui_colourdepth=0;							//Zero means default depth
	ui_winx=0,	
	ui_winy=0,	
	ui_winw=-1,	//zero width means never set up
	ui_winh=-1;	//negative width means start map fullscreen

	Save_Data.gammacorrection=2;
	Save_Data.contourDetail=3;
	Save_Data.textureQuality=3;											//JON 2Aug00
	Save_Data.detail_3d%=DETAIL3D_AUTODETAIL;
	Save_Data.desiredfps=8;
	Save_Data.detail_3d|=DETAIL3D_GROUNDSHADING;
//DeadCode JON 22Sep00 	Save_Data.detail_3d%=DETAIL3D_ITEMSHADING;// this will actually be done as specular is set.
//DeadCode JON 22Sep00 	Save_Data.detail_3d|=DETAIL3D_SPECITEM;
	Save_Data.itemShading = 2; // specular.
	Save_Data.detail_3d|=DETAIL3D_TRANSSMOKE;
	Save_Data.detail_3d|=DETAIL3D_INCONSEQUENTIALS;
	Save_Data.detail_3d|=DETAIL3D_ROUTES;
	Save_Data.detail_3d|=DETAIL3D_AIRCRAFTSHADOWS;
	Save_Data.detail_3d|=DETAIL3D_ITEMSHADOWS;
	Save_Data.detail_3d|=DETAIL3D_HORIZONDIST;
	Save_Data.detail_3d%=DETAIL3D_HORIZONFADE;
	Save_Data.detail_3d|=DETAIL3D_CONTOURDETAIL;
	Save_Data.cockpit3Ddetail%=COCK3D_SKYIMAGES;
	Save_Data.gamedifficulty|=GD_WEATHEREFFECTS;
	Save_Data.filtering=2;

	Save_Data.hardwareconfig |= HW_INJURYEFFECTS;				//RJS 15Nov00
	Save_Data.gamedifficulty |= GD_GROUNDCOLLISIONS;			//RJS 15Nov00

	int	backupres[UIR_MAX];
	{for (int i=UIR_FIRST;i<UIR_MAX;i++)
		backupres[i]=ui_horizontalres[i];
	}
	int backupminsbetweensavegame=minsbetweensavegame;
	//Do initialisation before here!!							//PD 11Feb99
	FileNum	sgfile=File_Man.fakefile(FIL_SAVEGAMEDIR,"settings.cfg");
	if (File_Man.ExistNumberedFile(sgfile))
	{
		BIStream bis(File_Man.NameNumberedFile(sgfile));
		bis>>*this;
		if (!successfulLoad)
		{
			MessageBox(hWnd,LoadResString(IDS_CONFIGIGNORED),LoadResString(IDS_CHOOSEPREFS),MB_OK);
//DEADCODE MS 03/05/00 			HardwareConfigure(true,hWnd);
		}
//		ThreeDeeSound=false;
	}
//DEADCODE MS 03/05/00 	else
//DEADCODE MS 03/05/00 		HardwareConfigure(true,hWnd);

// check to ensure that any music device guid contained in the savegame is still valid
	if (backupminsbetweensavegame)
		minsbetweensavegame=backupminsbetweensavegame;
	if (savegamesecscounter>minsbetweensavegame*3)
		savegamesecscounter=minsbetweensavegame*3;
	if (!LoadedMusicDeviceOK())
	{
		if (!InitMusicDevice())
		{
			MusicDevice=GUID_NULL;
		}
	}

// if sound device in savegame is not available use default

	if (!LoadedSFXDeviceOK())
	{
		SFXDevice=GUID_NULL;
	}
	else
	{
		if (!InitSoundDevice(wh))
			SFXDevice=GUID_NULL;
	}

	{for (int i=UIR_FIRST;i<UIR_MAX;i++)
		ui_horizontalres[i]=backupres[i];
	}

//DeadCode JIM 18Oct00 	ui_horizontalres[UIR_FIRST]=		0;		  //first call needs to fill this in.
	if (gameSettings.m_bBorder)
	{
		ui_horizontalres[UIR_SMACKER]=	UIRC_DESK;
		ui_horizontalres[UIR_SCRAMBLE]=	UIRC_DESK;		//1024 is same size as artwork
		ui_horizontalres[UIR_MAP]=		UIRC_DESK;			//0 means use desktop
		ui_horizontalres[UIR_FRAG]=		UIRC_DESK;			//1 can mean use map
		nextdialposmem=0;
		ui_colourdepth=0;							//Zero means default depth
		ui_winx=0,	
		ui_winy=0,	
		ui_winw=-1,	//zero width means never set up
		ui_winh=-1;	//negative width means start map fullscreen
	}

#ifndef	BOB_DEMO_VER
	SetFiltersFromSaveGame();
#endif

	//Don't put initialisation after this						//PD 11Feb99
}	

void	SaveData::SavePreferences()
{
	FileNum	sgfile=File_Man.fakefile(FIL_SAVEGAMEDIR,"settings.cfg");
	BOStream bos(File_Man.NameNumberedFile(sgfile));
	bos<<Save_Data;
}
/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//static	BOStream& operator	<<	(BOStream& bos,AirFieldInfo& airfieldinfo)
//static	BIStream& operator	>>	(BIStream& bis,AirFieldInfo& airfieldinfo)
//
//
/////////////////////////////////////////////////////////////////////////////////
static	BOStream& operator	<<	(BOStream& bos,Attacks& a)	
{	return bos.write((char*)&a,sizeof(Attacks));return bos;	}
static	BIStream& operator	>>	(BIStream& bis,Attacks& a)	
{	return bis.read((char*)&a,sizeof(Attacks));return bis;	}

extern	char* compiledate; 

//////////////////////////////////////////////////////////////////////
//
// Function:    LoadCleanNodeTree
// Date:		09/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	NodeData::SetPlayerInfoLevel()
{
	if (Todays_Packages.localplayer==NAT_RAF || Save_Data.gamedifficulty[GD_LWINTELL])
	{
		Target::playerpriority=	&Target::truepriority;
		Target::playertype=		&Target::truetargtype;
		Target::playerstatus=	&Target::truestatus;
	}
	else
	{
		Target::playerpriority=	&TargetGroup::falsepriority;
		Target::playertype=		&TargetGroup::falsetargtype;
		Target::playerstatus=	&TargetGroup::knownstatus;
	}
}
void	NodeData::LoadCleanNodeTree()
{
	char buffer[fileman::pathnamesize];
	SetPlayerInfoLevel();

	bool filegood=false;
	{
		BIStream bis(File_Man.namenumberedfile(File_Man.fakefile(FIL_SAVEGAMEDIR,"blank_nt.dat"),buffer));
 		filegood=(bis.is_open()==TRUE);
			if (filegood)
			{
				char buffer[50];
				int len=strlen(compiledate);
				bis.read(buffer,len+4);
				buffer[len]=0;
				if (strcmp(buffer,compiledate))
					filegood=false;
			}
			if (filegood)
			{
				Load(bis);
			}
	}
	if (!filegood)
	{
		BOStream bos(buffer);
		bos.write(compiledate,strlen(compiledate));
		bos.write("\n\032\0\0",4);
		Save(bos);
	}
//DeadCode JIM 3Jul00 	if (Todays_Packages.localplayer==NAT_RAF)
//DeadCode JIM 3Jul00 		for (int i=0;i<IllegalBAND;i++)
//DeadCode JIM 3Jul00 		{
//DeadCode JIM 3Jul00 			TargetGroup* g=operator[](UniqueID(i));
//DeadCode JIM 3Jul00 			if (g)
//DeadCode JIM 3Jul00 				g->FixInitialStatusRAF();
//DeadCode JIM 3Jul00 		}
//DeadCode JIM 3Jul00 	else
		for (int i=0;i<IllegalBAND;i++)
		{
			TargetGroup* g=operator[](UniqueID(i));
			if (g)
				g->FixInitialStatusLW();
		}
}
//DEADCODE JIM 16/11/99 void	SupplyTree::LoadCleanNodeTree()
//DEADCODE JIM 16/11/99 {
//DEADCODE JIM 16/11/99 	char buffer[150];
//DEADCODE JIM 16/11/99 	bool	filegood;
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99 		BIStream bis(File_Man.namenumberedfile(File_Man.fakefile(FIL_SAVEGAMEDIR,"blank_nt.dat"),buffer));
//DEADCODE JIM 16/11/99 		filegood=(bis.is_open()==TRUE);
//DEADCODE JIM 16/11/99 		if (filegood)
//DEADCODE JIM 16/11/99 		{
//DEADCODE JIM 16/11/99 			char buffer[50];
//DEADCODE JIM 16/11/99 			int len=strlen(compiledate);
//DEADCODE JIM 16/11/99 			bis.read(buffer,len+4);
//DEADCODE JIM 16/11/99 			buffer[len]=0;
//DEADCODE JIM 16/11/99 			if (strcmp(buffer,compiledate))
//DEADCODE JIM 16/11/99 				filegood=false;
//DEADCODE JIM 16/11/99 		}
//DEADCODE JIM 16/11/99 		if (filegood)
//DEADCODE JIM 16/11/99 		{
//DEADCODE JIM 16/11/99 			SupplyTree::Load(bis);
//DEADCODE JIM 16/11/99 		}
//DEADCODE JIM 16/11/99 	}
//DEADCODE JIM 16/11/99 	if (!filegood)
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99 		BOStream bos(buffer);
//DEADCODE JIM 16/11/99 		bos.write(compiledate,strlen(compiledate));
//DEADCODE JIM 16/11/99 		bos.write("\n\032\0\0",4);
//DEADCODE JIM 16/11/99 		SupplyTree::Save(bos);
//DEADCODE JIM 16/11/99 	}
//DEADCODE JIM 16/11/99 }
