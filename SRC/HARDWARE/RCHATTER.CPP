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
//Filename       rchatter.cpp
//System         
//Author         Robert Slater
//Date           Mon 8 Jun 1998
//Description    
//------------------------------------------------------------------------------

#ifndef	NDEBUG
//#define	_NO_CHATTER_
//#define	_NO_SAMPLES_
//#define	CHATTERTRACE
#define		_CHECK_SAMPLES_AT_RUNTIME_
//#define		_VOICE_DEBUG_
#define		_SCAN_SCRIPT_
#endif

#include 	"dosdefs.h"
#include 	<string.h>
#define 	F_GRAFIX
#include	"files.g"
#include	"fileman.h"
#include	"worldinc.h"
#include	"miles.h"
#include	"mymath.h"
#include	"world.h"
#include	"worldinc.h"
#include	"savegame.h"
#include	"rchatter.h"
#include	"..\mfc\resource.h"
#include	"radioxtr.g"
#include	"messengn.h"
#include	"flyinit.h"										//RJS 10Feb99
#include	"missman2.h"
#include	"cstring.h"
#include	"replay.h"											//AMM 14Apr99
#include	"grid.h"											//RJS 29Feb00
#include	"fastmath.h"										//RJS 29Feb00
#include	"uniqueid.h"
#include	"package.h"
#include	"nodebob.h"
#include	"ai.h"
#include	"sqddiary.h"

RadioChatter	_Radio;

//static	ULong	totmess = 0;

#ifdef	CHATTERTRACE
static	int	dbgCurrentPhrase = 0;
#endif


const	SLong	SQUAD_COLOUR_MAX = 13;									//RJS 22Oct00

// Fake phrase table (the fake phrases are defined in rchatter.h)
static	ULong	IDSFudgeTable[]=
{
	IDS_NONE,
	IDS_L_CPS_QUIT,				//PHRASE_TEXT_QUIT
	IDS_QUITGAME,				//PHRASE_TEXT_QUITGAME
	IDS_MAP_EXIT,				//PHRASE_TEXT_EXIT
	IDS_CONTINUE,				//PHRASE_TEXT_CONTINUE
	IDS_GAMECONTINUES			//PHRASE_TEXT_GAMECONTINUES
};





#ifndef	NDEBUG
bool	naughtynaughty = false;											//RJS 8Nov00
#endif

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RadioChatter
//Author		Robert Slater
//Date			Tue 9 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
RadioChatter::RadioChatter()
{
	int	count,count2;
	RadioSampleRec	*RPtr;

	for (count2 = 0; count2 < VOICE_MAX; count2++)
	{
		for (count=0; count < MaxSamples;count++)
		{
			RPtr = &radiosamples[count][count2];

			RPtr->blockptr = NULL;
			RPtr->size = 0;
			RPtr->offsetptr = NULL;
			RPtr->headerptr = NULL;
			RPtr->noFiles = 0;
		}
	}

	RootMessPtr = NULL;

	theSectors.theblock = NULL;
	theSectors.PlaceNames = NULL;
	theSectors.noelements = 0;

//	Save_Data.vol.rchat = 127;

 	MessageCount = 0;

	timesincelast = 0;
	timesincestart = 0;

	theScripts.theblock = NULL;
	theScripts.ScriptTable = NULL;
	theScripts.voiceBlock = NULL;										//RJS 16Aug00
	theScripts.voicePtr = NULL;											//RJS 16Aug00

	windHeightSet = 0;											//RJS 10Feb99
	windSpeedSet = -1;											//RJS 10Feb99

	totmess = 0;

	View_Point= NULL;

	voicechoiceFAC = 0;											//RJS 17May99
	voicechoiceTOWER = 0;										//RJS 17May99
	voicechoiceV2 = 0;											//RJS 08Jun99

	hipriSet = false;											//RJS 25May99
	lockout = false;											//RJS 04Jun99

	phrase_groundcontroller = 0;								//RJS 21Jan00
	in3D = false;

	ThrowOutMask[VOICE_PLAYER] = (1<<VOICE_PLAYER) + (1<<VOICE_XPLAYER) + (1<<VOICE_REST) + (1<<VOICE_XREST) + (1<<VOICE_SILENT);
	ThrowOutMask[VOICE_XPLAYER] = (1<<VOICE_PLAYER) + (1<<VOICE_XPLAYER) + (1<<VOICE_REST) + (1<<VOICE_XREST) + (1<<VOICE_SILENT);
	ThrowOutMask[VOICE_LWPLAYER] = (1<<VOICE_LWPLAYER) + (1<<VOICE_LWXPLAYER) + (1<<VOICE_LWREST) + (1<<VOICE_LWXREST) + (1<<VOICE_SILENT);
	ThrowOutMask[VOICE_LWXPLAYER] = (1<<VOICE_LWPLAYER) + (1<<VOICE_LWXPLAYER) + (1<<VOICE_LWREST) + (1<<VOICE_LWXREST) + (1<<VOICE_SILENT);
	ThrowOutMask[VOICE_REST] = (1<<VOICE_PLAYER) + (1<<VOICE_XPLAYER) + (1<<VOICE_REST) + (1<<VOICE_XREST) + (1<<VOICE_SILENT);
	ThrowOutMask[VOICE_XREST] = (1<<VOICE_PLAYER) + (1<<VOICE_XPLAYER) + (1<<VOICE_REST) + (1<<VOICE_XREST) + (1<<VOICE_SILENT);
	ThrowOutMask[VOICE_LWREST] = (1<<VOICE_LWPLAYER) + (1<<VOICE_LWXPLAYER) + (1<<VOICE_LWREST) + (1<<VOICE_LWXREST) + (1<<VOICE_SILENT);
	ThrowOutMask[VOICE_LWXREST] = (1<<VOICE_LWPLAYER) + (1<<VOICE_LWXPLAYER) + (1<<VOICE_LWREST) + (1<<VOICE_LWXREST) + (1<<VOICE_SILENT);
	ThrowOutMask[VOICE_GROUND] = (1<<VOICE_GROUND) + (1<<VOICE_SILENT);
	ThrowOutMask[VOICE_FEMALE] = (1<<VOICE_FEMALE) + (1<<VOICE_SILENT);
	ThrowOutMask[VOICE_TOWER] = (1<<VOICE_TOWER) + (1<<VOICE_SILENT);
	ThrowOutMask[VOICE_LWTOWER] = (1<<VOICE_LWTOWER) + (1<<VOICE_SILENT);
	ThrowOutMask[VOICE_VOICE2] = (1<<VOICE_VOICE2) + (1<<VOICE_LWVOICE2) + (1<<VOICE_SILENT);
	ThrowOutMask[VOICE_LWVOICE2] = (1<<VOICE_VOICE2) + (1<<VOICE_LWVOICE2) + (1<<VOICE_SILENT);
	ThrowOutMask[VOICE_SILENT] = 1<<VOICE_SILENT;

#ifndef	_NO_SAMPLES_
	samplesAllowed = true;
#else
	samplesAllowed = false;
#endif
}

void	RadioChatter::SetUpRandomVoices()
{
#ifndef	NDEBUG
	naughtynaughty = true;
#endif

	int	count2,count;
	RadioSampleRec	*RPtr;
	for (count2 = 0; count2 < VOICE_MAX; count2++)
	{
		for (count=0; count < MaxSamples; count++)
		{
			RPtr = &radiosamples[count][count2];
			if (RPtr->blockptr)
				delete RPtr->blockptr;

			RPtr->blockptr = NULL;
			RPtr->size = 0;
			RPtr->offsetptr = NULL;
			RPtr->headerptr = NULL;
			RPtr->noFiles = 0;
		}
	}

	ClearOldMessage();														//RJS 29Sep00

	if (FILEMAN.getTotalMem() <= RADIO_MEMORY_MIN)									//RJS 08Jun99
	{
		//this is the cheapest combination...	16,957,157	bytes
		// we might have to load an alternate DENTIST PLACENAMES table (same trick as V2)
		voicechoiceFAC = 0;				
		voicechoiceTOWER = 1;
		voicechoiceV2= 0;
	}
	else
	{
		voicechoiceFAC = Math_Lib.rnd(2);
		voicechoiceTOWER = Math_Lib.rnd(3);
		voicechoiceV2 = Math_Lib.rnd(2);
	}

	_Miles.SetUpRandomVoices(voicechoiceFAC,voicechoiceTOWER,voicechoiceV2);

	//Random frequencies...										//RJS 06Jul99
	for (count = 0; count < MaxPilots; count++)					//RJS 06Jul99
		randomvoice[count] = Math_Lib.rnd(1000) - 750;			//RJS 06Jul99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RadioChatter
//Author		Robert Slater
//Date			Tue 9 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
RadioChatter::~RadioChatter()
{
	int	count,count2;
	RadioSampleRec	*RPtr;
//DeadCode RJS 20Oct00 	RadioMessageP	MessPtr = RootMessPtr;
	RadioMessageP	TmpMessPtr;

	for (count2 = 0; count2 < VOICE_MAX; count2++)
	{
		for (count=0; count < MaxSamples; count++)
		{
			RPtr = &radiosamples[count][count2];
			if (RPtr->blockptr)
				delete RPtr->blockptr;

			RPtr->blockptr = NULL;
			RPtr->size = 0;
			RPtr->offsetptr = NULL;
			RPtr->headerptr = NULL;
			RPtr->noFiles = 0;
		}
	}

	ClearOldMessage();														//RJS 29Sep00

	delete theSectors.theblock;
	delete theScripts.theblock;
	delete theScripts.voiceBlock;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayMessage
//Author		Robert Slater
//Date			Mon 8 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode RJS 27Jan99 void	RadioChatter::PlayMessage(	int		Scriptno,
//DeadCode RJS 27Jan99 									TargetIndexes&	tstruc,
//DeadCode RJS 27Jan99 									ItemPtr	Caller,
//DeadCode RJS 27Jan99 									ItemPtr	Trg,
//DeadCode RJS 27Jan99 									ItemPtr	Callee,
//DeadCode RJS 27Jan99 									Bool	noCaller	)
//DeadCode RJS 27Jan99 {
//DeadCode RJS 27Jan99 	if (Save_Data.vol.rchat)
//DeadCode RJS 27Jan99 	{
//DeadCode RJS 27Jan99 		RadioMessageP	MessPtr = CreateMessage((mobileitem*)Caller,
//DeadCode RJS 27Jan99 												(mobileitem*)Trg,
//DeadCode RJS 27Jan99 												(mobileitem*)Callee,
//DeadCode RJS 27Jan99 												tstruc	);
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 		if (MessPtr)
//DeadCode RJS 27Jan99 		{
//DeadCode RJS 27Jan99 			if (!noCaller)
//DeadCode RJS 27Jan99 			{
//DeadCode RJS 27Jan99 				ComposeSample(MessPtr,PHRASE_THISCALLER);
//DeadCode RJS 27Jan99 				ComposeSample(MessPtr,PHRASE_COMMA);
//DeadCode RJS 27Jan99 			}
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 			DecomposeScript(MessPtr,Scriptno);
//DeadCode RJS 27Jan99 		}
//DeadCode RJS 27Jan99 	}
//DeadCode RJS 27Jan99 }
//DeadCode RJS 27Jan99 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecomposeScript
//Author		Robert Slater
//Date			Mon 8 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::DecomposeScript(RadioMessageP	MessPtr,int Scriptno)
{
	UWordP			ScriptPtr;
	PhraseTables	ThePhrase;
	ULong	nochoices = Scriptno & 0xFFFF0000;

	if (nochoices)
	{
		Scriptno &= 0xFFFF;

		ScriptPtr = GetScript(Scriptno,MessPtr,ThePhrase);		//RJS 12Apr99
		if (ScriptPtr)
		{
			ThePhrase = (PhraseTables) *ScriptPtr;
			while (ThePhrase != PHRASE_NULL)
			{
				ComposeSample(MessPtr,ThePhrase);
				ScriptPtr++;

				lastPhrase = ThePhrase;
				ThePhrase = (PhraseTables) *ScriptPtr;
			}
		}
		else
		{
			if ((ThePhrase&0xFF00) == PHRASE_VOICE2)					//AM 21Aug00
			{
				if (MessPtr->caller->nationality == NAT_RAF)			//RJS 6Sep00
	 				MessPtr->theVoice = VOICE_VOICE2;
				else
	 				MessPtr->theVoice = VOICE_LWVOICE2;
			}

			ComposeSample(MessPtr,ThePhrase);
		}
	}
	else
	{
		if ((Scriptno&0xFF00) == PHRASE_VOICE2)							//AM 21Aug00
		{
			if (MessPtr->caller->nationality == NAT_RAF)			//RJS 6Sep00
 				MessPtr->theVoice = VOICE_VOICE2;
			else
 				MessPtr->theVoice = VOICE_LWVOICE2;
		}

		ComposeSample(MessPtr,Scriptno);
	}

	if (!MessPtr->BuildMessageAsSamples())
	{
		// Set up a fake one...
		timesincelast = 0;
		timesincestart = 0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateMessage
//Author		Robert Slater
//Date			Mon 8 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
RadioMessageP	RadioChatter::CreateMessage(ItemPtr	caller,
											ItemPtr	target,
											ItemPtr	callee,
											UWord	randno,
											const TargetIndexes&	tstruc,
											VoiceType		vox,
											PhraseBuffer	*fbuffp,
											SWord			vol,
											VoiceState		voxstate)
{
	RadioMessageP	NewMessagePtr = NULL;
	// If there is no queue...
	if (RootMessPtr == NULL)									//RJS 27Jan99
	{
		NewMessagePtr = new RadioMessage(RootMessPtr,caller,target,callee,vol,tstruc,fbuffp,vox,in3D);//RJS 27Jan99
		if (NewMessagePtr)
		{
			if (voxstate == VOXSTATE_EXCITED)
				NewMessagePtr->IsExcited = 1;

			NewMessagePtr->masterrandom = randno<<16;
			NewMessagePtr->masterrandom |= randno;

			if (	(	(vox >= VOICE_REST)						//RJS 29Feb00
 					&&	(vox < VOICE_GROUND)	)				//RJS 29Feb00
 				&& caller												//RJS 8Sep00
				&&	(caller->Status.size == AIRSTRUCSIZE)	)			//RJS 8Sep00
			{
				int	callnum;
				
				if (AirStrucPtr(caller)->ai.diaryptr)
					callnum=AirStrucPtr(caller)->ai.diaryptr->squadnum;
				else
					callnum=SQ_BR_START;

				if (callnum > SQ_LW_START)
					callnum -= SQ_LW_START;
				else
					callnum -= SQ_BR_START;

				if (callnum < MaxPilots)			
 					NewMessagePtr->theFrequency += randomvoice[callnum];
			}

			MessageCount++;
		}
	}

	lastPhrase = PHRASE_NULL;
	RelativeToPilot = FALSE;
	DigRange = FALSE;

	return(NewMessagePtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PhraseFactors
//Author		Robert Slater
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
RadioOnz*	RadioChatter::PhraseFactors(int	thePhrase)
{
	thePhrase &= 0xFF00;
	thePhrase >>= 8;

	return &PhraseToFile[thePhrase];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ComposeSample
//Author		Robert Slater
//Date			Mon 8 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ComposeSample(RadioMessageP	MessPtr,int phrase)
{
//Old_Code RJS 18Jan00 	if (phrase != PHRASE_NULL)									//RJS 12Feb99
//Old_Code RJS 18Jan00 	{
//Old_Code RJS 18Jan00 		int			ptype = phrase & 0xFF00;
//Old_Code RJS 18Jan00 		int			pelement = phrase & 0xFF;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 		if (pelement)
//Old_Code RJS 18Jan00 		{
//Old_Code RJS 18Jan00 			if (MessPtr->isAudio)
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				RadioSampleRec*	RSamplePtr;
//Old_Code RJS 18Jan00 				int				StartOffset;
//Old_Code RJS 18Jan00 				int				SampleSize;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				if (ptype == PHRASE_VOICE2_ONLY)								//RJS 08Jun99
//Old_Code RJS 18Jan00 					MessPtr->IsExcited = voicechoiceV2;							//RJS 08Jun99
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				RSamplePtr = LoadSample(MessPtr,phrase,StartOffset,SampleSize);
//Old_Code RJS 18Jan00 				if (RSamplePtr)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					if ((ptype == PHRASE_PUNCTUATION) || ((lastPhrase & 0xFF00) == PHRASE_PUNCTUATION))
//Old_Code RJS 18Jan00 						MessPtr->phraselist[MessPtr->nophrases].noCrossFade = 1;
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 						MessPtr->phraselist[MessPtr->nophrases].noCrossFade = 0;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					MessPtr->AddSample(RSamplePtr->dataptr,StartOffset,SampleSize);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			else
//Old_Code RJS 18Jan00 				MessPtr->AddPhrase(phrase);
//Old_Code RJS 18Jan00 		}
//Old_Code RJS 18Jan00 		else
//Old_Code RJS 18Jan00 		{
//Old_Code RJS 18Jan00 			RadioOnz*		phraseControl = &PhraseToFile[ptype>>8];
//Old_Code RJS 18Jan00 			PhraseTables	compositePhrase;
//Old_Code RJS 18Jan00 			int				pilotno;
//Old_Code RJS 18Jan00 			int				squadron;
//Old_Code RJS 18Jan00 			int				punctuate = PHRASE_COMMA;
//Old_Code RJS 18Jan00 			UniqueID		commsname = (UniqueID) 0;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 			switch (ptype)
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 			case PHRASE_CALLERGROUP:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				AirStrucPtr	ac = (AirStrucPtr) MessPtr->caller;
//Old_Code RJS 18Jan00 				if (ac)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					squadron = ac->fly.callname;
//Old_Code RJS 18Jan00 					if (squadron)
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_CALLGROUPS+squadron);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_CALLEEGROUP:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				AirStrucPtr	ac = (AirStrucPtr) MessPtr->callee;
//Old_Code RJS 18Jan00 				if (ac)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					squadron = ac->fly.callname;
//Old_Code RJS 18Jan00 					if (squadron)
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_CALLGROUPS+squadron);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_CALLERSTOP:
//Old_Code RJS 18Jan00 				punctuate = PHRASE_STOP;
//Old_Code RJS 18Jan00 			case PHRASE_THISCALLER:
//Old_Code RJS 18Jan00 			case PHRASE_CALLER:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 //DeadCode RDH 12Apr99 				if (MessPtr->isAudio)			//RJS 01Apr99
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					AirStrucPtr	ac = (AirStrucPtr) MessPtr->caller;//RJS 13Jan99
//Old_Code RJS 18Jan00 					if (ac)
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						pilotno = ac->fly.callnum;		
//Old_Code RJS 18Jan00 						squadron = ac->fly.callname;
//Old_Code RJS 18Jan00 						Bool	fixlater = FALSE;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 						if (squadron)
//Old_Code RJS 18Jan00 						{
//Old_Code RJS 18Jan00 							if (ptype == PHRASE_THISCALLER)				//RJS 15Jan99
//Old_Code RJS 18Jan00 							{
//Old_Code RJS 18Jan00 								punctuate = PHRASE_STOP;
//Old_Code RJS 18Jan00 								if (!MessPtr->Random(2))		//RDH 04May99
//Old_Code RJS 18Jan00 									ComposeSample(MessPtr,PHRASE_THISIS);	//RJS 15Jan99
//Old_Code RJS 18Jan00 								else
//Old_Code RJS 18Jan00 									fixlater = TRUE;				//RJS 10Feb99
//Old_Code RJS 18Jan00 							}
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 							ComposeSample(MessPtr,PHRASE_CALLSIGNS_N+squadron);
//Old_Code RJS 18Jan00 							if (pilotno && (ac->fly.callname < Call_FAC0))	//RJS 20May99
//Old_Code RJS 18Jan00 							{
//Old_Code RJS 18Jan00 								if ((pilotno == 1) && (fixlater==FALSE))
//Old_Code RJS 18Jan00 								{
//Old_Code RJS 18Jan00 									if (MessPtr->Random(1))		//RDH 04May99
//Old_Code RJS 18Jan00 										ComposeSample(MessPtr,PHRASE_LEAD);
//Old_Code RJS 18Jan00 									else
//Old_Code RJS 18Jan00 										ComposeSample(MessPtr,PHRASE_LEAD2);
//Old_Code RJS 18Jan00 								}
//Old_Code RJS 18Jan00 								else
//Old_Code RJS 18Jan00 									ComposeSample(MessPtr,PHRASE_NUMTABLE1_N+pilotno+1);
//Old_Code RJS 18Jan00 							}
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 							if (fixlater)
//Old_Code RJS 18Jan00 								ComposeSample(MessPtr,PHRASE_HERE);	//RJS 10Feb99
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 							ComposeSample(MessPtr,punctuate);			//RJS 08Mar99
//Old_Code RJS 18Jan00 						}
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_SUBJECT:
//Old_Code RJS 18Jan00 			case PHRASE_CALLEE:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				AirStrucPtr	ac;												//RJS 04May99
//Old_Code RJS 18Jan00 				if (ptype == PHRASE_SUBJECT)								//RJS 04May99
//Old_Code RJS 18Jan00 					ac = (AirStrucPtr) MessPtr->target;						//RJS 04May99
//Old_Code RJS 18Jan00 				else														//RJS 04May99
//Old_Code RJS 18Jan00 					ac = (AirStrucPtr) MessPtr->callee;						//RJS 04May99
//Old_Code RJS 18Jan00 				if (ac)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					pilotno = ac->fly.callnum;			
//Old_Code RJS 18Jan00 					squadron = ac->fly.callname;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (squadron)
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 //DeadCode RDH 04May99 						UWord	randy = Math_Lib.rnd();
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_CALLSIGNS_N+squadron);
//Old_Code RJS 18Jan00 						if (pilotno && (ac->fly.callname < Call_FAC0))		//RJS 20May99
//Old_Code RJS 18Jan00 						{
//Old_Code RJS 18Jan00 							if (pilotno == 1)
//Old_Code RJS 18Jan00 							{
//Old_Code RJS 18Jan00  								if (!MessPtr->Random(2))		//RDH 04May99
//Old_Code RJS 18Jan00  									ComposeSample(MessPtr,PHRASE_LEAD);
//Old_Code RJS 18Jan00  								else
//Old_Code RJS 18Jan00 									ComposeSample(MessPtr,PHRASE_LEAD2);
//Old_Code RJS 18Jan00 							}
//Old_Code RJS 18Jan00 							else
//Old_Code RJS 18Jan00 								ComposeSample(MessPtr,PHRASE_NUMTABLE1_N+pilotno+1);
//Old_Code RJS 18Jan00 						}
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_SMLRANGESKM:
//Old_Code RJS 18Jan00 			case PHRASE_SMLRANGESIMP:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				SLong	dist = MessPtr->distance;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				dist += phraseControl->subFactor;
//Old_Code RJS 18Jan00 				dist /= phraseControl->divFactor;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				ComposeSample(MessPtr,PHRASE_SMALLRANGES+dist);
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_BIGRANGESKM:
//Old_Code RJS 18Jan00 			case PHRASE_BIGRANGESIMP:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				SLong	dist = MessPtr->distance;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				dist += phraseControl->subFactor;				//RJS 12Feb99
//Old_Code RJS 18Jan00 				dist /= phraseControl->divFactor;				//RJS 12Feb99
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				dist += PHRASE_NUMTABLE25_N;
//Old_Code RJS 18Jan00 				if (dist > PHRASE_NUMBER800)
//Old_Code RJS 18Jan00 					dist = PHRASE_NUMBER800;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				ComposeSample(MessPtr,dist);
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_RANGESKM:
//Old_Code RJS 18Jan00 			case PHRASE_RANGESIMP:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				SLong	dist = MessPtr->distance;
//Old_Code RJS 18Jan00 			
//Old_Code RJS 18Jan00 				dist += phraseControl->subFactor;			//RJS 12Feb99
//Old_Code RJS 18Jan00 				dist /= phraseControl->divFactor;			//RJS 12Feb99
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				if (dist > 100)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					// Are we a pilot?
//Old_Code RJS 18Jan00 					if (MessPtr->theVoice < VOICE_FACTAC)
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						// only the leader can say big ranges...
//Old_Code RJS 18Jan00 						if (MessPtr->caller != ((AirStrucPtr)MessPtr->caller)->GroupLeader())
//Old_Code RJS 18Jan00 						{
//Old_Code RJS 18Jan00 //DEADCODE RDH 07/12/99 							ComposeSample(MessPtr,PHRASE_OVER100);
//Old_Code RJS 18Jan00 							break;
//Old_Code RJS 18Jan00 						}
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (ptype == PHRASE_RANGESKM)
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_BIGRANGESKM);
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_BIGRANGESIMP);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 				else
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					SLong	 newphrase = dist + PHRASE_NUMTABLEF;
//Old_Code RJS 18Jan00 					if (newphrase < PHRASE_FNUMBER2)
//Old_Code RJS 18Jan00 						newphrase = PHRASE_FNUMBER2;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (newphrase > PHRASE_FNUMBER16)
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						newphrase -= PHRASE_NUMTABLEF;
//Old_Code RJS 18Jan00 						newphrase += PHRASE_NUMTABLE1_N;
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,newphrase);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_NUMBERCLOCK:
//Old_Code RJS 18Jan00 			case PHRASE_BEARINGS:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->InitROL())
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					UWord	relbearing = UWord(MessPtr->bearing);
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					relbearing -= UWord(MessPtr->callee->hdg);	//RJS 05May99
//Old_Code RJS 18Jan00 					relbearing += phraseControl->subFactor;		//RJS 12Feb99
//Old_Code RJS 18Jan00 					relbearing /= phraseControl->divFactor;		//RJS 12Feb99
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (ptype == PHRASE_BEARINGS)
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						if (!relbearing)
//Old_Code RJS 18Jan00 							relbearing = 1;
//Old_Code RJS 18Jan00 							
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,ptype+relbearing);
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_THEOCLOCK);
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						relbearing += PHRASE_NUMTABLE1_N;
//Old_Code RJS 18Jan00 						if (relbearing < PHRASE_NUMBER1)
//Old_Code RJS 18Jan00 							relbearing = PHRASE_NUMBER12;
//Old_Code RJS 18Jan00 						
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_YOUR);
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,relbearing);
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_TARGDIR:
//Old_Code RJS 18Jan00 			if (MessPtr->InitROL())
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				UWord	relbearing = MessPtr->bearing;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				relbearing += phraseControl->subFactor;		//RJS 12Feb99
//Old_Code RJS 18Jan00 				relbearing /= phraseControl->divFactor;		//RJS 12Feb99
//Old_Code RJS 18Jan00 				if (!relbearing)
//Old_Code RJS 18Jan00 					relbearing = 1;
//Old_Code RJS 18Jan00 					
//Old_Code RJS 18Jan00 				ComposeSample(MessPtr,ptype+relbearing);
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_RELHEIGHTS:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 				// Must cater for relative heights from
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 				// different perspectives!!
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 				//
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 				// ie. caller and target, or callee and target
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 				SLong	rheights = MessPtr->pitch;
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 				if (rheights > 5000)
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 					ComposeSample(MessPtr,PHRASE_HIGH);
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 				else
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 				{
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 					if (rheights < -5000)
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 						ComposeSample(MessPtr,PHRASE_LOW);
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 					else
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 						ComposeSample(MessPtr,PHRASE_OURLEVEL);//RJS 10Feb99
//Old_Code RJS 18Jan00 //DeadCode AMM 05Jul99 				}
//Old_Code RJS 18Jan00 				if (MessPtr->target && MessPtr->callee)			//RJS 05Jul99
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					SLong	rheights = MessPtr->target->World.Y - MessPtr->callee->World.Y;
//Old_Code RJS 18Jan00 					//100m
//Old_Code RJS 18Jan00 					if (rheights > 10000)
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_HIGH);
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						if (rheights < -10000)
//Old_Code RJS 18Jan00 							ComposeSample(MessPtr,PHRASE_LOW);
//Old_Code RJS 18Jan00 						else
//Old_Code RJS 18Jan00 							ComposeSample(MessPtr,PHRASE_OURLEVEL);//RJS 10Feb99
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_HEIGHTSANGELS:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->target)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					MessPtr->realheight = MessPtr->target->World.Y;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					DigRange = TRUE;
//Old_Code RJS 18Jan00 					if (Save_Data.gamedifficulty [GD_UNITS])
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_HEIGHTSM);
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_HEIGHTSFT);
//Old_Code RJS 18Jan00 					DigRange = FALSE;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_ANGELS);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_PLACENAMESNP:
//Old_Code RJS 18Jan00 				lastPhrase = PHRASE_LOST;
//Old_Code RJS 18Jan00 			case PHRASE_PLACENAMES:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				SectorNameP	NamePtr;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 //DeadCode RJS 23May99 				if (lastPhrase == PHRASE_LOST)
//Old_Code RJS 18Jan00 //DeadCode RJS 23May99 				{
//Old_Code RJS 18Jan00 //DeadCode RJS 23May99 					RelativeToPilot = TRUE;
//Old_Code RJS 18Jan00 //DeadCode RJS 23May99 					NamePtr = GetPlaceName(MessPtr->caller);
//Old_Code RJS 18Jan00 //DeadCode RJS 23May99 				}
//Old_Code RJS 18Jan00 //DeadCode RJS 23May99 				else
//Old_Code RJS 18Jan00 				if (MessPtr->target)
//Old_Code RJS 18Jan00 					NamePtr = GetPlaceName(MessPtr->target);
//Old_Code RJS 18Jan00 				else
//Old_Code RJS 18Jan00 					NamePtr = GetPlaceName(MessPtr->TargetStuff.targetname);
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				if (NamePtr)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					if (lastPhrase == PHRASE_NULL)					//RJS 11Feb99
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,NamePtr->prefix);
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						if (lastPhrase != PHRASE_LOST)		//RJS 11Feb99
//Old_Code RJS 18Jan00 						{
//Old_Code RJS 18Jan00 							if (	((NamePtr->prefix >= PHRASE_CENTRAL) && (NamePtr->prefix < PHRASE_OVER))
//Old_Code RJS 18Jan00 								||	(NamePtr->prefix == PHRASE_NULL)	)
//Old_Code RJS 18Jan00 								ComposeSample(MessPtr,PHRASE_OVER);
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 							ComposeSample(MessPtr,NamePtr->prefix);
//Old_Code RJS 18Jan00 						}
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,NamePtr->name);
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,NamePtr->postfix);	//RJS 15Jun99
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_ANAMED_AC:
//Old_Code RJS 18Jan00 			case PHRASE_NAMED_AC:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->target && (MessPtr->target->Status.size==AIRSTRUCSIZE))
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					ClassPtr	clstyp = ((AirStrucPtr)MessPtr->target)->classtype;
//Old_Code RJS 18Jan00 					SLong		pno = 0;						//RJS 01Jul99
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (clstyp->phrasename == PHRASE_MIGS)
//Old_Code RJS 18Jan00 						pno = PHRASE_QMIG - PHRASE_NAMED_AC;
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						if (clstyp->phrasename == PHRASE_F86S)	//RJS 01Jul99
//Old_Code RJS 18Jan00 							pno = PHRASE_QSABRE - PHRASE_NAMED_AC;
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (pno)									//RJS 01Jul99
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,ptype+pno);		//RJS 01Jul99
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_NAMED_ACS:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->target && (MessPtr->target->Status.size==AIRSTRUCSIZE))
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					ClassPtr	clstyp = ((AirStrucPtr)MessPtr->target)->classtype;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,clstyp->phrasename);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_DIRECTIONS_TRAVEL:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->TargetStuff.targetdirection)	//RJS 12Jan99
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_HEADING);
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,ptype+MessPtr->TargetStuff.targetdirection);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 				else
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					ULong	direction;
//Old_Code RJS 18Jan00 					Bool	dirset = FALSE;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (RelativeToPilot == TRUE)
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						if (MessPtr->caller)
//Old_Code RJS 18Jan00 						{
//Old_Code RJS 18Jan00 							direction = MessPtr->caller->hdg;
//Old_Code RJS 18Jan00 							dirset = TRUE;
//Old_Code RJS 18Jan00 						}
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						if (MessPtr->target)
//Old_Code RJS 18Jan00 						{
//Old_Code RJS 18Jan00 							direction = MessPtr->target->hdg;
//Old_Code RJS 18Jan00 							dirset = TRUE;
//Old_Code RJS 18Jan00 						}
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (dirset)
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						direction += phraseControl->subFactor;	//RJS 12Feb99
//Old_Code RJS 18Jan00 						direction /= phraseControl->divFactor;	//RJS 12Feb99
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 //						if (direction == 0)
//Old_Code RJS 18Jan00 //							direction = 1;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_HEADING);
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,ptype+direction);
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 //DeadCode RJS 17Mar99 			case PHRASE_BANDIT_ALERT:
//Old_Code RJS 18Jan00 //DeadCode RJS 17Mar99 			{
//Old_Code RJS 18Jan00 //DeadCode RJS 17Mar99 				ULong	randy = Math_Lib.rnd();
//Old_Code RJS 18Jan00 //DeadCode RJS 17Mar99 
//Old_Code RJS 18Jan00 //DeadCode RJS 17Mar99 				randy += phraseControl->subFactor;				//RJS 12Feb99
//Old_Code RJS 18Jan00 //DeadCode RJS 17Mar99 				randy /= phraseControl->divFactor;				//RJS 12Feb99
//Old_Code RJS 18Jan00 //DeadCode RJS 17Mar99 
//Old_Code RJS 18Jan00 //DeadCode RJS 17Mar99 				ComposeSample(MessPtr,ptype+randy);
//Old_Code RJS 18Jan00 //DeadCode RJS 17Mar99 			}
//Old_Code RJS 18Jan00 //DeadCode RJS 17Mar99 			break;
//Old_Code RJS 18Jan00 			case PHRASE_TARGTYPE:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				compositePhrase = (PhraseTables)MessPtr->TargetStuff.targettype;
//Old_Code RJS 18Jan00 				if ((compositePhrase & 0xFF00)==ptype)
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,compositePhrase);			//RJS 28Apr99
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_TARGNAM:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				compositePhrase = (PhraseTables)MessPtr->TargetStuff.targetname;
//Old_Code RJS 18Jan00 				if ((compositePhrase & 0xFF00)==ptype)
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,compositePhrase);			//RJS 28Apr99
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_TARGMOV:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				compositePhrase = (PhraseTables)MessPtr->TargetStuff.targetmovement;
//Old_Code RJS 18Jan00 				if ((compositePhrase & 0xFF00)==ptype)
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,compositePhrase);		//RJS 28Apr99
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_WEAPONS:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				compositePhrase = (PhraseTables)MessPtr->TargetStuff.weaponset;
//Old_Code RJS 18Jan00 				if ((compositePhrase & 0xFF00)==ptype)
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,compositePhrase);			//RJS 28Apr99
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_HEIGHTSM:
//Old_Code RJS 18Jan00 			case PHRASE_HEIGHTSFT:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				SLong	height = MessPtr->realheight;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				height += phraseControl->subFactor;
//Old_Code RJS 18Jan00 				height /= phraseControl->divFactor;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				if (DigRange)
//Old_Code RJS 18Jan00 					ComposeDigitNumber(MessPtr,height,2);
//Old_Code RJS 18Jan00 				else
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					height += PHRASE_NUMTABLEF;
//Old_Code RJS 18Jan00 					if (height < PHRASE_FNUMBER1)
//Old_Code RJS 18Jan00 						height = PHRASE_FNUMBER1;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (height > PHRASE_FNUMBER16)				//RJS 12Apr99
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						height -= PHRASE_NUMTABLEF;
//Old_Code RJS 18Jan00 						height += PHRASE_NUMTABLE1_N;
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,height);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_HEIGHTS:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->target || MessPtr->TargetStuff.targetheight)//RJS 01Jun99
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					bool	saidheight = false;
//Old_Code RJS 18Jan00 //DeadCode RDH 04May99 					UWord	randy = Math_Lib.rnd();
//Old_Code RJS 18Jan00 					if (MessPtr->Random(3))						//RDH 04May99
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_HEIGHT);
//Old_Code RJS 18Jan00 						saidheight = true;
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						if ((MessPtr->IsExcited == 0) && MessPtr->Random(3))//RDH 04May99
//Old_Code RJS 18Jan00 						{
//Old_Code RJS 18Jan00 							ComposeSample(MessPtr,PHRASE_ESTHEIGHT);
//Old_Code RJS 18Jan00 							saidheight = true;
//Old_Code RJS 18Jan00 						}
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (!saidheight)
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_SPACE);
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (MessPtr->TargetStuff.targetheight)		//RJS 01Jun99
//Old_Code RJS 18Jan00 						MessPtr->realheight = MessPtr->TargetStuff.targetheight;
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 						MessPtr->realheight = MessPtr->target->World.Y;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (Save_Data.gamedifficulty [GD_UNITS])
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_HEIGHTSM);
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_THOUSANDM);
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_HEIGHTSFT);
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_THOUSANDFT);
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_SPEEDS:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->InitROL())
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					ULong	vel;
//Old_Code RJS 18Jan00 					SLong	newphrase;
//Old_Code RJS 18Jan00 					
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 					if (Save_Data.gamedifficulty [GD_UNITS])
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 					{
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 						// metric (m/cm)... but have as knots
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 						vel = Float(MessPtr->speed) * 0.19438;
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 						newphrase = PHRASE_SPEEDSKNOT;
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 					}
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 					else
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 					{
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 						// mph
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 						vel = Float(MessPtr->speed) * 0.225;
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 						newphrase = PHRASE_SPEEDSMPH;
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 					}
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 					MessPtr->speed = vel;
//Old_Code RJS 18Jan00 //DeadCode RJS 18Mar99 					ComposeSample(MessPtr,newphrase);
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					vel = MessPtr->speed;
//Old_Code RJS 18Jan00 					vel += phraseControl->subFactor;
//Old_Code RJS 18Jan00 					vel /= phraseControl->divFactor;
//Old_Code RJS 18Jan00 					if (!vel)	vel = 1;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_SPACE);				//RJS 09May99
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_NUMTABLE25_N+vel); 
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (Save_Data.gamedifficulty [GD_UNITS])
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_CLICKS);
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_KNOTS);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_RANGES:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->InitROL())
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					bool	saidrange = false;
//Old_Code RJS 18Jan00 					if ((MessPtr->distance > 300000) || (MessPtr->IsExcited==0))
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 //DeadCode RDH 04May99 						UWord	randpoo = Math_Lib.rnd();
//Old_Code RJS 18Jan00 						if (MessPtr->Random(1))					//RDH 04May99
//Old_Code RJS 18Jan00 						{
//Old_Code RJS 18Jan00 // At Range can only be said, if no comma precedes it...
//Old_Code RJS 18Jan00 //DeadCode RJS 17Mar99 							if (randpoo > 55000)
//Old_Code RJS 18Jan00 //DeadCode RJS 17Mar99 								ComposeSample(MessPtr,PHRASE_ATRANGE);
//Old_Code RJS 18Jan00 //DeadCode RJS 17Mar99 							else
//Old_Code RJS 18Jan00 							ComposeSample(MessPtr,PHRASE_RANGE);
//Old_Code RJS 18Jan00 							saidrange = true;
//Old_Code RJS 18Jan00 						}
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (!saidrange)
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_SPACE);
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (MessPtr->distance > 250000)
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						if (Save_Data.gamedifficulty [GD_UNITS])
//Old_Code RJS 18Jan00 						{
//Old_Code RJS 18Jan00 							ComposeSample(MessPtr,PHRASE_RANGESKM);
//Old_Code RJS 18Jan00 							ComposeSample(MessPtr,PHRASE_KILOMETRES);
//Old_Code RJS 18Jan00 						}
//Old_Code RJS 18Jan00 						else
//Old_Code RJS 18Jan00 						{
//Old_Code RJS 18Jan00 							ComposeSample(MessPtr,PHRASE_RANGESIMP);
//Old_Code RJS 18Jan00 							ComposeSample(MessPtr,PHRASE_MILES);
//Old_Code RJS 18Jan00 						}
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						// Small ranges...
//Old_Code RJS 18Jan00 						if (Save_Data.gamedifficulty [GD_UNITS])
//Old_Code RJS 18Jan00 						{
//Old_Code RJS 18Jan00 							if (	(MessPtr->theVoice != VOICE_DENTIST)
//Old_Code RJS 18Jan00 								&&	(MessPtr->theVoice != VOICE_TOWER)	)
//Old_Code RJS 18Jan00 							{
//Old_Code RJS 18Jan00 								ComposeSample(MessPtr,PHRASE_SMLRANGESKM);
//Old_Code RJS 18Jan00 								ComposeSample(MessPtr,PHRASE_METRES);
//Old_Code RJS 18Jan00 							}
//Old_Code RJS 18Jan00 							else
//Old_Code RJS 18Jan00 							{
//Old_Code RJS 18Jan00 								ComposeSample(MessPtr,PHRASE_UNDER2);
//Old_Code RJS 18Jan00 								ComposeSample(MessPtr,PHRASE_KILOMETRES);
//Old_Code RJS 18Jan00 							}
//Old_Code RJS 18Jan00 						}
//Old_Code RJS 18Jan00 						else
//Old_Code RJS 18Jan00 						{
//Old_Code RJS 18Jan00 							if (	(MessPtr->theVoice != VOICE_DENTIST)
//Old_Code RJS 18Jan00 								&&	(MessPtr->theVoice != VOICE_TOWER)	)
//Old_Code RJS 18Jan00 							{
//Old_Code RJS 18Jan00 								ComposeSample(MessPtr,PHRASE_SMLRANGESIMP);
//Old_Code RJS 18Jan00 								ComposeSample(MessPtr,PHRASE_YARDS);
//Old_Code RJS 18Jan00 							}
//Old_Code RJS 18Jan00 							else
//Old_Code RJS 18Jan00 							{
//Old_Code RJS 18Jan00 								ComposeSample(MessPtr,PHRASE_UNDER2);
//Old_Code RJS 18Jan00 								ComposeSample(MessPtr,PHRASE_MILES);
//Old_Code RJS 18Jan00 							}
//Old_Code RJS 18Jan00 						}
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_BEARINGNO:								//RJS 18Mar99
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->InitROL())
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					UWord	relbearing = UWord(MessPtr->bearing);//RDH 13Apr99
//Old_Code RJS 18Jan00 					SLong	therel = (relbearing * 360)>>16;	//RDH 13Apr99
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					ComposeDigitNumber(MessPtr,therel,3);		//RDH 30Apr99
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_ALTWINDBEARINGNO:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				windHeightSet = 1061666;	//35,000ft in cm
//Old_Code RJS 18Jan00 				ComposeSample(MessPtr,PHRASE_ALTWIND);
//Old_Code RJS 18Jan00 				ComposeSample(MessPtr,PHRASE_COMMA);
//Old_Code RJS 18Jan00 				ComposeSample(MessPtr,PHRASE_WINDBEARINGNO);
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_SURFACEWINDBEARINGNO:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				windHeightSet = 0;
//Old_Code RJS 18Jan00 				ComposeSample(MessPtr,PHRASE_SURFACEWIND);
//Old_Code RJS 18Jan00 				ComposeSample(MessPtr,PHRASE_COMMA);
//Old_Code RJS 18Jan00 				ComposeSample(MessPtr,PHRASE_WINDBEARINGNO);
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_WINDBEARINGNO:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				SLong	vx,vy,vz;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				// height is set up by prevous wind phrase...
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 				if (MMC.Sky.GetWind(windHeightSet,vx,vy,vz))
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 				{
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 					ANGLES	bearing,pitch;
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 					
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 					Math_Lib.Intercept(vx,vy,vz,windSpeedSet,bearing,pitch);
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					ULong	theBearing;
//Old_Code RJS 18Jan00 					
//Old_Code RJS 18Jan00 					//These values should already be in degrees...
//Old_Code RJS 18Jan00 					if (windHeightSet)
//Old_Code RJS 18Jan00 						theBearing = UWord(MMC.Sky.diralt);
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 						theBearing = UWord(MMC.Sky.dir0);
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 					theBearing *= 360;
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 					theBearing >>= 16;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_THEBEARING);
//Old_Code RJS 18Jan00 					ComposeDigitNumber(MessPtr,SLong(theBearing),3);
//Old_Code RJS 18Jan00 //DEADCODE DAW 04/05/99 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_WINDSPEED:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (windSpeedSet == -1)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 					SLong	vx,vy,vz;
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 					if (MMC.Sky.GetWind(windHeightSet,vx,vy,vz))
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 						windSpeedSet = Math_Lib.distance3d(vx,vy,vz);
//Old_Code RJS 18Jan00 					//Knots...
//Old_Code RJS 18Jan00 					if (windHeightSet)
//Old_Code RJS 18Jan00 						windSpeedSet = UWord(MMC.Sky.windalt);
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 						windSpeedSet = UWord(MMC.Sky.wind0);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				if (windSpeedSet > -1)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 					Float	fspeed;
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 					//Scale & divide by 10!
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 					fspeed = Float(windSpeedSet);
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 					if (Save_Data.gamedifficulty [GD_UNITS])
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 						fspeed *= 0.194261;						//RJS 30Apr99
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 					else
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 						fspeed *= 0.22369;						//RJS 30Apr99
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 			 
//Old_Code RJS 18Jan00 //DeadCode DAW 04May99 					windSpeedSet = SLong(fspeed);
//Old_Code RJS 18Jan00 					windSpeedSet += PHRASE_FNUMBER0;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (windSpeedSet < PHRASE_FNUMBER2)
//Old_Code RJS 18Jan00 						windSpeedSet = PHRASE_FNUMBER2;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					if (windSpeedSet > PHRASE_FNUMBER16)
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						windSpeedSet -= PHRASE_NUMTABLEF;
//Old_Code RJS 18Jan00 						windSpeedSet += PHRASE_NUMTABLE1_N;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 						if (windSpeedSet > PHRASE_NUMBER100)
//Old_Code RJS 18Jan00 							windSpeedSet = PHRASE_NUMBER100;
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_SPACE);
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,windSpeedSet);
//Old_Code RJS 18Jan00 //DEADCODE DAW 05/05/99 					if (Save_Data.gamedifficulty [GD_UNITS])
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_KNOTS);
//Old_Code RJS 18Jan00 //DEADCODE DAW 05/05/99 					else
//Old_Code RJS 18Jan00 //DEADCODE DAW 05/05/99 						ComposeSample(MessPtr,PHRASE_PERHOUR);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				windSpeedSet = -1;
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_FUELLEVEL:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->caller)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					AirStrucPtr	ac = (AirStrucPtr) MessPtr->caller;
//Old_Code RJS 18Jan00 //DEADCODE CSB 05/11/99 					ULong	fueltot = ac->weap.left.int_fuel;
//Old_Code RJS 18Jan00 //DEADCODE CSB 05/11/99 
//Old_Code RJS 18Jan00 //DEADCODE CSB 05/11/99 					fueltot += ac->weap.left.ext_fuel;
//Old_Code RJS 18Jan00 //DEADCODE CSB 05/11/99 					fueltot += ac->weap.right.int_fuel;
//Old_Code RJS 18Jan00 //DEADCODE CSB 05/11/99 					fueltot += ac->weap.right.ext_fuel;
//Old_Code RJS 18Jan00 //DEADCODE CSB 05/11/99 					fueltot += ac->weap.centre.int_fuel;
//Old_Code RJS 18Jan00 //DEADCODE CSB 05/11/99 					fueltot += ac->weap.centre.ext_fuel;
//Old_Code RJS 18Jan00 					ULong fueltot = 0;											//CSB 05/11/99
//Old_Code RJS 18Jan00 					for(SWord i = 0; i < 4; i++)								//CSB 05/11/99
//Old_Code RJS 18Jan00 						fueltot += ac->fly.fuel_content[i];						//CSB 05/11/99
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					fueltot /= 100000;	//kgs
//Old_Code RJS 18Jan00 //DeadCode CSB 30/06/99						fueltot = Float(fueltot) * 0.453597;		//RJS 13May99
//Old_Code RJS 18Jan00 					fueltot = Float(fueltot) * 2.2046;		//CSB 30/06/99	
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_SPACE);		//RJS 13May99
//Old_Code RJS 18Jan00 					ComposeDigitNumber(MessPtr,SLong(fueltot));
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_GALLONS);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_RELPOSITION:							//RJS 25Feb99
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				// split into 4 directions, with 45 degree spread -&+...
//Old_Code RJS 18Jan00 				if (MessPtr->InitROL())
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					UWord	relbearing = MessPtr->bearing;
//Old_Code RJS 18Jan00 					relbearing += phraseControl->subFactor;		//RJS 12Feb99
//Old_Code RJS 18Jan00 					relbearing /= phraseControl->divFactor;		//RJS 12Feb99
//Old_Code RJS 18Jan00 					if (!relbearing)
//Old_Code RJS 18Jan00 						relbearing++;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,ptype+relbearing);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_RANDOMTHINKTIME:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->isAudio)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					RadioSampleRec*	RSamplePtr;
//Old_Code RJS 18Jan00 					int				StartOffset;
//Old_Code RJS 18Jan00 					int				SampleSize;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					RSamplePtr = LoadSample(MessPtr,PHRASE_THINKING,StartOffset,SampleSize);
//Old_Code RJS 18Jan00 					if (RSamplePtr)
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						// Fiddle the sample size to vary pause length...
//Old_Code RJS 18Jan00 						SampleSize >>= 1;
//Old_Code RJS 18Jan00 						SampleSize += Math_Lib.rnd(SampleSize);
//Old_Code RJS 18Jan00 			
//Old_Code RJS 18Jan00 						MessPtr->AddSample(RSamplePtr->dataptr,StartOffset,SampleSize);
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 				else
//Old_Code RJS 18Jan00 					MessPtr->AddPhrase(PHRASE_THINKING);
//Old_Code RJS 18Jan00 //				{
//Old_Code RJS 18Jan00 //					//1.5 secs...
//Old_Code RJS 18Jan00 //					for (int i=0; i < 3; i++)
//Old_Code RJS 18Jan00 //						MessPtr->AddPhrase(PHRASE_THINKING);
//Old_Code RJS 18Jan00 //				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_GUSTTYPE:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				SLong magnitude = MMC.Sky.MaxMagnitude;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				//assume magnitude is 0...6
//Old_Code RJS 18Jan00 				magnitude = (2 * magnitude)/6;		//scale down to 3 possible types...
//Old_Code RJS 18Jan00 				
//Old_Code RJS 18Jan00 				ComposeSample(MessPtr,PHRASE_GUSTLIGHT+magnitude);
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_THISDENTIST:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 //DeadCode RDH 12Apr99 				if (MessPtr->isAudio)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					if (!MessPtr->Random(2))					//RDH 04May99
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_THISIS);
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_DENTIST);
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 					else
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_DENTISTHERE);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_THISDENTISTTO:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 //DeadCode RDH 12Apr99 				if (MessPtr->isAudio)
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_DENTISTTO);
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_DENTISTSTOP:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 //DeadCode RDH 12Apr99 				if (MessPtr->isAudio)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_DENTIST);
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_STOP);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_AIRFIELDS:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->target)									//RJS 05May99
//Old_Code RJS 18Jan00 				{	
//Old_Code RJS 18Jan00 					SLong	uid = MessPtr->target->uniqueID.count;		//RJS 05May99
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					// Find offset...
//Old_Code RJS 18Jan00 					uid -= UID_AF_Abbeville; //RJS 16/11/99
//Old_Code RJS 18Jan00 					uid++;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 					uid += PHRASE_AIRFIELDS;
//Old_Code RJS 18Jan00 					if ((uid > PHRASE_AIRFIELDS) && (uid <= PHRASE_AFJAPAN))
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,uid);
//Old_Code RJS 18Jan00 //Dead(moved to script)						ComposeSample(MessPtr,PHRASE_AIRFIELD);
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_THISCOMMS:
//Old_Code RJS 18Jan00 			case PHRASE_COMMSCALLER:
//Old_Code RJS 18Jan00 				commsname = MessPtr->caller->uniqueID.count;
//Old_Code RJS 18Jan00 			case PHRASE_COMMSTARGET:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (!commsname)
//Old_Code RJS 18Jan00 					commsname = MessPtr->target->uniqueID.count;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				ComposeSample(MessPtr,PHRASE_PLAYERNAME1+_DPlay.GetPlayerNumber(commsname));
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				if (ptype == PHRASE_THISCOMMS)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_COLON);
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_SPACE);
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_USER_DEFINED:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				ULong	messno = 8 * _DPlay.GetPlayerNumber(MessPtr->caller->uniqueID.count);
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				messno += MessPtr->TargetStuff.usermessage;
//Old_Code RJS 18Jan00 				messno++;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 				ComposeSample(MessPtr,ptype+messno);
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_GERMANCALLERSTOP:
//Old_Code RJS 18Jan00 				punctuate = PHRASE_STOP;
//Old_Code RJS 18Jan00 			case PHRASE_GERMANTHISCALLER:
//Old_Code RJS 18Jan00 			case PHRASE_GERMANCALLER:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->isAudio)
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					switch (ptype)
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 					case PHRASE_GERMANCALLERSTOP:
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_CALLERSTOP);
//Old_Code RJS 18Jan00 						break;
//Old_Code RJS 18Jan00 					case PHRASE_GERMANTHISCALLER:
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_THISCALLER);
//Old_Code RJS 18Jan00 						break;
//Old_Code RJS 18Jan00 					case PHRASE_GERMANCALLER:
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_CALLER);
//Old_Code RJS 18Jan00 						break;
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 				else
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					AirStrucPtr	ac = (AirStrucPtr) MessPtr->caller;
//Old_Code RJS 18Jan00 					if (ac)
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						pilotno = ac->fly.callnum;		
//Old_Code RJS 18Jan00 						squadron = ac->fly.callname;
//Old_Code RJS 18Jan00 						Bool	fixlater = FALSE;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 						if (squadron)
//Old_Code RJS 18Jan00 						{
//Old_Code RJS 18Jan00 							if (ptype == PHRASE_GERMANTHISCALLER)
//Old_Code RJS 18Jan00 							{
//Old_Code RJS 18Jan00 								punctuate = PHRASE_STOP;
//Old_Code RJS 18Jan00 								if (!MessPtr->Random(2))
//Old_Code RJS 18Jan00 									ComposeSample(MessPtr,PHRASE_THISIS);
//Old_Code RJS 18Jan00 								else
//Old_Code RJS 18Jan00 								{	
//Old_Code RJS 18Jan00 									ComposeSample(MessPtr,PHRASE_HERE);
//Old_Code RJS 18Jan00 									ComposeSample(MessPtr,PHRASE_SPACE);
//Old_Code RJS 18Jan00 									fixlater = TRUE;
//Old_Code RJS 18Jan00 								}
//Old_Code RJS 18Jan00 							}
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 							ComposeSample(MessPtr,PHRASE_CALLSIGNS_N+squadron);
//Old_Code RJS 18Jan00 							if (pilotno && (ac->fly.callname < Call_FAC0))
//Old_Code RJS 18Jan00 							{
//Old_Code RJS 18Jan00 //DeadCode RJS 15Jun99 								if ((pilotno == 1) && (fixlater==FALSE))
//Old_Code RJS 18Jan00 //DeadCode RJS 15Jun99 								{
//Old_Code RJS 18Jan00 //DeadCode RJS 15Jun99 									if (MessPtr->Random(1))
//Old_Code RJS 18Jan00 //DeadCode RJS 15Jun99 										ComposeSample(MessPtr,PHRASE_LEAD);
//Old_Code RJS 18Jan00 //DeadCode RJS 15Jun99 									else
//Old_Code RJS 18Jan00 //DeadCode RJS 15Jun99 										ComposeSample(MessPtr,PHRASE_LEAD2);
//Old_Code RJS 18Jan00 //DeadCode RJS 15Jun99 								}
//Old_Code RJS 18Jan00 //DeadCode RJS 15Jun99 								else
//Old_Code RJS 18Jan00 									ComposeSample(MessPtr,PHRASE_NUMTABLE1_N+pilotno+1);
//Old_Code RJS 18Jan00 							}
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 							ComposeSample(MessPtr,punctuate);
//Old_Code RJS 18Jan00 						}
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			case PHRASE_GERMANNUMBERCLOCK:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->isAudio)
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_NUMBERCLOCK);
//Old_Code RJS 18Jan00 				else
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					if (MessPtr->InitROL())
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						UWord	relbearing = MessPtr->bearing;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 						relbearing -= UWord(MessPtr->callee->hdg);
//Old_Code RJS 18Jan00 						relbearing += phraseControl->subFactor;
//Old_Code RJS 18Jan00 						relbearing /= phraseControl->divFactor;
//Old_Code RJS 18Jan00 						relbearing += PHRASE_NUMTABLE1_N;
//Old_Code RJS 18Jan00 						if (relbearing < PHRASE_NUMBER1)
//Old_Code RJS 18Jan00 							relbearing = PHRASE_NUMBER12;
//Old_Code RJS 18Jan00 		
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_SPACE);
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,relbearing);
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_YOUR);
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 //DEADCODE RDH 07/12/99 			case PHRASE_COMMSACCEL:
//Old_Code RJS 18Jan00 //DEADCODE RDH 07/12/99 			{
//Old_Code RJS 18Jan00 //DEADCODE RDH 07/12/99 //DeadCode AMM 16Nov99 				int	accelno = _DPlay.GetAccelNumber();
//Old_Code RJS 18Jan00 //DEADCODE RDH 07/12/99 				int accelno=0;
//Old_Code RJS 18Jan00 //DEADCODE RDH 07/12/99 
//Old_Code RJS 18Jan00 //DEADCODE RDH 07/12/99 				ComposeSample(MessPtr,PHRASE_NUMBER0+accelno);
//Old_Code RJS 18Jan00 //DEADCODE RDH 07/12/99 			}
//Old_Code RJS 18Jan00 //DEADCODE RDH 07/12/99 			break;
//Old_Code RJS 18Jan00 			case PHRASE_ITALIANBEARINGS:
//Old_Code RJS 18Jan00 			{
//Old_Code RJS 18Jan00 				if (MessPtr->isAudio)
//Old_Code RJS 18Jan00 					ComposeSample(MessPtr,PHRASE_BEARINGS);
//Old_Code RJS 18Jan00 				else
//Old_Code RJS 18Jan00 				{
//Old_Code RJS 18Jan00 					if (MessPtr->InitROL())
//Old_Code RJS 18Jan00 					{
//Old_Code RJS 18Jan00 						UWord	relbearing = MessPtr->bearing;
//Old_Code RJS 18Jan00 
//Old_Code RJS 18Jan00 						relbearing -= UWord(MessPtr->callee->hdg);
//Old_Code RJS 18Jan00 						relbearing += phraseControl->subFactor;	  
//Old_Code RJS 18Jan00 						relbearing /= phraseControl->divFactor;	  
//Old_Code RJS 18Jan00 						if (!relbearing)
//Old_Code RJS 18Jan00 							relbearing = 1;
//Old_Code RJS 18Jan00 						
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,PHRASE_THEOCLOCK);
//Old_Code RJS 18Jan00 						ComposeSample(MessPtr,ptype+relbearing);
//Old_Code RJS 18Jan00 					}
//Old_Code RJS 18Jan00 				}
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 			break;
//Old_Code RJS 18Jan00 			}
//Old_Code RJS 18Jan00 		}
//Old_Code RJS 18Jan00 	}

	if (phrase != PHRASE_NULL)
	{
		int			ptype = phrase & 0xFF00;
		int			pelement = phrase & 0xFF;


		if (pelement)
			SpeakPhrase(MessPtr,phrase);						//RJS 28Mar00
		else
		{
			RadioOnz*		phraseControl = PhraseFactors(phrase);
			PhraseTables	compositePhrase;
			int				pilotno;
			int				squadron;
//DeadCode RJS 20Oct00 			int				punctuate = PHRASE_COMMA;
//DeadCode RJS 20Oct00 			UniqueID		commsname = (UniqueID) 0;

			switch (ptype)
			{
			case PHRASE_AIRFIELDS:
			case PHRASE_RAF_AIRFIELDS:
			case PHRASE_LUF_FIGHTERLF2BAND:						//RJS 01Mar00
			{
				Airfields(MessPtr,MessPtr->target);
			}
			break;
			case PHRASE_ALTWINDBEARINGNO:
			{
				ALTWINDBEARINGNO(MessPtr);
			}
			break;
			case PHRASE_BANDITSEX:
			{
				BANDITSEX(MessPtr);
			}
			break;
			case PHRASE_BAREBEARINGS:
			{
				BAREBEARINGS(MessPtr);
			}
			break;
			case PHRASE_BEARINGS:
			{
				BEARINGS(MessPtr);
			}
			break;
			case PHRASE_CALLEE_GFIGHTERS:
			{
				CALLEE_GFIGHTERS(MessPtr);
			}
			break;
			case PHRASE_CALLEE_GFLIGHTRAF:
			{
				CALLEE_GFLIGHTRAF(MessPtr);
			}
			break;
			case PHRASE_CALLEE_GL_RAF:
			{
				CALLEE_GL(MessPtr);
			}
			break;
			case PHRASE_CALLEE_GSECTIONRAF:
			{
				CALLEE_GSECTIONRAF(MessPtr);
			}
			break;
			case PHRASE_CALLEE_GSN_RAF:
			{
				CALLEE_GSN(MessPtr);
			}
			break;
			case PHRASE_CALLEE_GSQUADRAF:
			{
				CALLEE_GSQUADRAF(MessPtr);
			}
			break;
			case PHRASE_CALLEE_GWINGRAF:
			{
				CALLEE_GWINGRAF(MessPtr);
			}
			break;
			case PHRASE_CALLEE_SN:
			{
				CALLEE_SN(MessPtr);
			}
			break;
			case PHRASE_CALLEE_SQUADNUMBERLONG:
			{
				CALLEE_SQUADNUMBERLONG(MessPtr);
			}
			break;
			case PHRASE_CALLEE_SQUADNUMBERSHORT:
			{
				CALLEE_SQUADNUMBERSHORT(MessPtr);
			}
			break;
			case PHRASE_CALLER_GFLIGHTRAF:
			{
				CALLER_GFLIGHTRAF(MessPtr);
			}
			break;
			case PHRASE_CALLER_GL_RAF:
			{
				CALLER_GL(MessPtr);
			}
			break;
			case PHRASE_CALLER_GSECTIONRAF:
			{
				CALLER_GSECTIONRAF(MessPtr);
			}
			break;
//DEADCODE MS 28/04/00 			case PHRASE_CALLER_GSN:
//DEADCODE MS 28/04/00 			{
//DEADCODE MS 28/04/00 				CALLER_GSN(MessPtr);
//DEADCODE MS 28/04/00 			}
//DEADCODE MS 28/04/00 			break;
			case PHRASE_CALLER_GSQUADRAF:
			{
				CALLER_GSQUADRAF(MessPtr);
			}
			break;
			case PHRASE_CALLER_GWINGRAF:
			{
				CALLER_GWINGRAF(MessPtr);
			}
			break;
			case PHRASE_CALLER_HDGOCLOCK:
			{
				CALLER_HDGOCLOCK(MessPtr);
			}
			break;
			case PHRASE_CALLER_SN:
			{
				CALLER_SN(MessPtr);
			}
			break;
//DEADCODE RJS 5/3/00 			case PHRASE_COMMS:			//?
//DEADCODE RJS 5/3/00 			{
//DEADCODE RJS 5/3/00 				COMMS(MessPtr);
//DEADCODE RJS 5/3/00 			}
//DEADCODE RJS 5/3/00 			break;
			case PHRASE_COMMSCALLER_SN:	//?
			{
				COMMSCALLER_SN(MessPtr);
			}
			break;
			case PHRASE_COMMSTARGET:	//?
			{
				COMMSTARGET(MessPtr);
			}
			break;
			case PHRASE_LWFIGHTERSABOVE:
			{
				FIGHTERSABOVE(MessPtr);
			}
			break;
			case PHRASE_FUELLEVEL:
			{
				FUELLEVEL(MessPtr);
			}
			break;
			case PHRASE_CALLEE_GROUNDCONTROLLERLW:
			{
				GROUNDCONTROLLERLW(MessPtr);
			}
			break;
			case PHRASE_CALLER_GROUNDCONTROLLERRAF:
			case PHRASE_CALLEE_GROUNDCONTROLLERRAF:
			{
				GROUNDCONTROLLERRAF(MessPtr);
			}
			break;
			case PHRASE_GUSTTYPE:
			{
				GUSTTYPE(MessPtr);
			}
			break;
			case PHRASE_TRG_ANGELS:
			{
				TRG_ANGELS(MessPtr);
			}
			break;
			case PHRASE_TRG_VECTOR:
			{
				TRG_VECTOR(MessPtr);
			}
			break;
			case PHRASE_ONE_AIRCRAFT:
			{
				ONE_AIRCRAFT(MessPtr);
			}
			break;
			case PHRASE_ONE_AIRCRAFT_EXCLAIM:
			{
				ONE_AIRCRAFT_EXCLAIM(MessPtr);
			}
			break;
			case PHRASE_PATROL_PLACE:
			{
				PATROL_PLACE(MessPtr);
			}
			break;
			case PHRASE_PLACENODIST:
			{
				PLACENAMES(MessPtr,MessPtr->target,false);
			}
			break;
			case PHRASE_PLACENAMES:
			{
				PLACENAMES(MessPtr,MessPtr->target);
			}
			break;
			case PHRASE_RAID_ID:
			{
				RAID_ID(MessPtr);
			}
			break;
			case PHRASE_SQUADNUMBERLONG:
			{
				SQUADNUMBERLONG(MessPtr);
			}
			break;
			case PHRASE_SUBJECT_SN:
			{
				SUBJECT_SN(MessPtr,*MessPtr->target);
			}
			break;
			case PHRASE_SURFACEWINDBEARINGNO:
			{
				SURFACEWINDBEARINGNO(MessPtr);
			}
			break;
//DEADCODE MS 28/04/00 			case PHRASE_TRG_1AC:
//DEADCODE MS 28/04/00 			{
//DEADCODE MS 28/04/00 				TRG_1AC(MessPtr);
//DEADCODE MS 28/04/00 			}
//DEADCODE MS 28/04/00 			break;
			case PHRASE_TRG_AC:
			{
				TRG_AC(MessPtr);
			}
			break;
			case PHRASE_TRG_BOMBER2ACS:
			{
				TRG_BOMBER2ACS(MessPtr);
			}
			break;
//DEADCODE MS 28/04/00 			case PHRASE_TRG_BOMBERAC:
//DEADCODE MS 28/04/00 			{
//DEADCODE MS 28/04/00 				TRG_BOMBERAC(MessPtr);
//DEADCODE MS 28/04/00 			}
//DEADCODE MS 28/04/00 			break;
			case PHRASE_TRG_BOMBERACS:
			{
				TRG_BOMBERACS(MessPtr);
			}
			break;
			case PHRASE_TRG_DESC_ESTIMATE:
			{
				TRG_DESC_ESTIMATE(MessPtr);
			}
			break;
			case PHRASE_TRG_HDGCARDINAL:
			{
				TRG_HDGCARDINAL(MessPtr);
			}
			break;
			case PHRASE_HDGOCLOCK:
			case PHRASE_TRG_HDGOCLOCK:
			{
				HdgOClock(MessPtr);
			}
			break;
			case PHRASE_TRG_HEIGHT:
			{
				TRG_HEIGHT(MessPtr);
				THOUSANDUNITS(MessPtr);
			}
			break;
			case PHRASE_GEN_HEIGHTFT:
			case PHRASE_GEN_HEIGHTM:
			{
				Height(MessPtr,phraseControl);
			}
			break;
			case PHRASE_TRG_NEAR:
			{
				TRG_NEAR(MessPtr);
			}
			break;
			case PHRASE_TRG_NUM_ESTIMATE:
			{
				TRG_NUM_ESTIMATE(MessPtr);
			}
			break;
			case PHRASE_TRG_PLACE:
			{
				TRG_PLACE(MessPtr);
			}
			break;
			case PHRASE_TRG_RANGE:
			{
				TRG_RANGE(MessPtr);
			}
			break;
			case PHRASE_RANGESKM:
			case PHRASE_RANGESIMP:
			{
				Gen_LargeRanges(MessPtr,phraseControl);
			}
			break;
			case PHRASE_SMLRANGESKM:
			case PHRASE_SMLRANGESIMP:
			{
				Gen_SmallRanges(MessPtr,phraseControl);
			}
			break;
			case PHRASE_TRG_RELHEIGHT:
			{
				TRG_RELHEIGHT(MessPtr);
			}
			break;
			case PHRASE_USER_DEFINED:
			{
				USER_DEFINED(MessPtr);
			}
			break;
			case PHRASE_WATCHFORESCORT:
			{
				WATCHFORESCORT(MessPtr);
			}
			break;
			case PHRASE_WINDSPEED:
			{
				WINDSPEED(MessPtr);
			}
			break;
			case PHRASE_CALLEE_GLW:
//DEADCODE MS 28/04/00 			case PHRASE_CALLEE_GGRUPPELW:
			{
				ComposeSample(MessPtr,ptype+SquadronName(*MessPtr->callee));
			}
			break;
			case PHRASE_CALLEE_GUNIT:
			{
				Subject_GUnit(MessPtr,MessPtr->callee);
			}
			break;
			case PHRASE_CALLER_AIRFIELD:
			{
				Airfields(MessPtr,MessPtr->caller);
			}
			break;
			case PHRASE_CALLER_GUNIT:
			{
				Subject_GUnit(MessPtr,MessPtr->caller);
			}
			break;
			case PHRASE_GESCHWADERNUMBERLONG:
			{
				SLong	squadnum = MessPtr->TargetStuff.targetname;
				if (squadnum)
				{
					SLong	tmpsnum;

					squadnum -= SQ_LW_START;

					ComposeSample(MessPtr,PHRASE_GESCHWADERTYPE+squadnum);
					ComposeSample(MessPtr,PHRASE_GESCHWADERNUMBERSHORT+squadnum);
					ComposeSample(MessPtr,PHRASE_OPENBRACKET);

					squadnum--;
					tmpsnum = squadnum / 3;
					tmpsnum *= 3;

					squadnum -= tmpsnum;
					squadnum++;

					ComposeSample(MessPtr,PHRASE_ROMANNUMBERS+squadnum);
					ComposeSample(MessPtr,PHRASE_CLOSEBRACKET);
				}
			}
			break;
			case PHRASE_NUMBEROFLOSSES:
			case PHRASE_NUMBEROFKILLS:
			{
				SLong	number = MessPtr->TargetStuff.targetheight;	//RJS 18Apr00

				ComposeDigitNumber(MessPtr,number);
			}
			break;
//DEADCODE RJS 4/18/00 			case PHRASE_NUMBEROFLOSSES:
//DEADCODE RJS 4/18/00 			{
//DEADCODE RJS 4/18/00 #pragma	message(__HERE__ "Jim:  I need number of losses for the day")
//DEADCODE RJS 4/18/00 
//DEADCODE RJS 4/18/00 			}
//DEADCODE RJS 4/18/00 			break;
			case PHRASE_ONLYRAID_ID:
			{
				ComposeSample(MessPtr,PHRASE_W_RAID);
				SayRaidID(MessPtr,MessPtr->target,MessPtr->caller);			//RJS 29Mar00
			}
			break;
			case PHRASE_PLURAL_AIRCRAFT_EXCLAIM:
			{
				ComposeSample(MessPtr,AircraftType(MessPtr,*MessPtr->target));
			}
			break;
			case PHRASE_RELPOSITION:
			{
				if (MessPtr->InitROL())
				{
					UWord	relbearing = MessPtr->bearing;

					relbearing -= UWord(MessPtr->callee->hdg);
					relbearing += phraseControl->subFactor;
 					relbearing /= phraseControl->divFactor;
 					if (!relbearing)
 						relbearing++;
 
 					ComposeSample(MessPtr,ptype+relbearing);
				}
			}
			break;
			case PHRASE_SECTOROPSBAND:
			{
				PLACENAMES(MessPtr,MessPtr->target);
			}
			break;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddSample
//Author		Robert Slater
//Date			Tue 9 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RADIOMESSAGE::AddSample(UByteP	data,int	theOffset, int theSize)	//RJS 22Mar99
{
	if (theSize)
	{
		phraselist[nophrases].size = theSize/4;			// long words
		phraselist[nophrases++].address = data + theOffset;
		samplesize += theSize;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddPhrase
//Author		Robert Slater
//Date			Thu 13 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RADIOMESSAGE::AddPhrase(int phrase)
{
	SLong	visphrase = phrase;

	if (messbuffptr)
	{
#ifdef	CHATTERTRACE
		messbuffptr->master_phrase[messbuffptr->phrase_count] = dbgCurrentPhrase;
#endif
		if (messbuffptr->phrase_count < MaxPhrases)
			messbuffptr->phrase_buffer[messbuffptr->phrase_count++] = visphrase;
	}
	else
		nophrases++;
}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildMessageAsSamples
//Author		Robert Slater
//Date			Mon 8 Jun 1998
//
//Description	
//
//Inputs		
//								     
//Returns	
//
//------------------------------------------------------------------------------
Bool	RADIOMESSAGE::BuildMessageAsSamples()
{
	if (samplesize)
	{
		ULong	longsamplesize = (samplesize+16)>>2;			//RJS 04Jun99
		ULong	newsamplesize = longsamplesize << 2;			//RJS 04Jun99
																//RJS 04Jun99
		sampleptr = new UByte[newsamplesize];					//RJS 04Jun99
		if (sampleptr)
		{
			ULong	*destptr = (ULong*)sampleptr;
			ULong	*srcptr;
			int		count;
			int		sampcnt;
			int		noCrossFade = TRUE;
			ULong	*destptr2 = destptr;
			SByte	sample1,sample2;
			SLong	mixed;
			int		count2;
			SLong	depth = 448;
			SByteP	tmpdestptr;
			SByteP	tmpsrcptr;
			ULong	total;

			ULongP	tmpptr = destptr;							//RJS 04Jun99
			for (count=0; count < longsamplesize; count++)		//RJS 04Jun99
			{													//RJS 04Jun99
				*tmpptr = 0x80808080;									//RJS 7Sep00
				tmpptr++;										//RJS 04Jun99
			}													//RJS 04Jun99

			for (count = 0; count < nophrases; count++)
			{
				srcptr = (ULong*) phraselist[count].address;
				if (noCrossFade)
				{
					for (sampcnt = 0; sampcnt < phraselist[count].size; sampcnt++)
					{
						*destptr = *srcptr;
						destptr++;
						srcptr++;
					}
				}
				else
				{
					for (sampcnt = 0; sampcnt < phraselist[count].size; sampcnt++)
					{
						if (destptr < destptr2)
						{
							tmpdestptr = (SByteP) destptr;
							tmpsrcptr = (SByteP) srcptr;
							for (count2 = 0; count2 < 4; count2++)
							{
								sample1 = *tmpdestptr;
								sample1 -= 128;
								sample2 = *tmpsrcptr;
								sample2 -= 128;

								mixed = (sample1 * depth)/448;
								mixed += (sample2 * (448-depth))/448;

								if (mixed < -128)	mixed = -128;
								else
									if (mixed > 127)	mixed = 127;

								*tmpdestptr = SByte(mixed + 128);

								tmpdestptr++;
								tmpsrcptr++;

								depth--;
							}

							destptr++;
							srcptr++;
						}
						else
						{
							*destptr = *srcptr;
							destptr++;
							srcptr++;
						}
					}
				}

				// Cross-fade (if this or last phrase was not punctuation)
				noCrossFade = phraselist[count].noCrossFade;
				if (!noCrossFade)
				{
					destptr2 = destptr;
					depth = 448;
					destptr -= 112;
				}
			}

			*destptr = 0x80808080;										//RJS 7Sep00
		}
#ifndef	NDEBUG
	DbgMemTest2(sampleptr);
#endif

		return TRUE;
	}

	isAudio = FALSE;			//an empty message...
	fakeplaytime = 250;	//4 secs to read...						//DAW 07Apr99

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitROL
//Author		Robert Slater
//Date			Mon 8 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	RADIOMESSAGE::InitROL()
{
	Bool	retval = FALSE;
	if (target)
	{
		retval = TRUE;
		if (distance == -1)
		{
			SLong	dx, dy, dz;

			if (callee)
			{
				dx = target->World.X - callee->World.X;
				dy = target->World.Y - callee->World.Y;
				dz = target->World.Z - callee->World.Z;

				Math_Lib.Intercept(dx,dy,dz,distance,bearing,pitch);
			}
			else
			{
				retval = FALSE;					//RJS 09May99
				distance = 0;
			}

			if (target->Status.size >= MOBILESIZE)				//RJS 20Jan00
			{													//RJS 20Jan00
				speed = target->vel_ * 10;						//RJS 20Jan00
				heading = target->hdg;							//RJS 20Jan00
			}													//RJS 20Jan00
			else												//RJS 20Jan00
			{													//RJS 20Jan00
				speed = 0;										//RJS 20Jan00
				heading = 0;									//RJS 20Jan00
			}													//RJS 20Jan00
		}
	}
	else
	{
		if (distance > -1)
			retval = TRUE;
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSample
//Author		Robert Slater
//Date			Mon 8 Jun 1998
//
//Description	
//
//				Format:
//							n files		(ULong)
//							offset (ULong),	size (ULong)	* n
//							Samples Header
//							Samples data
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
RadioSampleRec*	RadioChatter::LoadSample(	RadioMessageP	MessPtr,
											int				thephrase,
											int 			&StartOff,
											int 			&SampleSize)
{
#ifndef	NDEBUG
// This means we are trying to play radio chatter during an illegal state in the game
	if (naughtynaughty)
		INT3;
#endif

	RadioSampleRec*	SamplePtr = NULL;

	if (samplesAllowed)
	{
		int				pfile = thephrase>>8;
		int				pelement = thephrase & 0xFF;				//RJS 12Feb99
		SLong			fileindex = PhraseToFile[pfile].mainFileName & FILENUMMASK;//RJS 12Feb99
		SLong			voiceoffset = MessPtr->theVoice + MessPtr->IsExcited + MessPtr->randomvoice;//RJS 17May99
		SLong			thedir = rootChatDir + (voiceoffset<<8);				//RJS 08Apr99
		FileNum			thefile = FileNum(thedir + fileindex);

		StartOff = SampleSize = 0;

		SamplePtr = &radiosamples[fileindex-1][voiceoffset];		//RJS 17Mar99
		if (!SamplePtr->blockptr)
		{
#ifdef	_CHECK_SAMPLES_AT_RUNTIME_
			if (!File_Man.existnumberedfile(thefile))						//RJS 16Aug00
				return NULL;
#endif

			fileblock	*theblock;
			SWAV		*header1;
			void		*tmpaddress;
			ULong		*longaddress;
			SLong		size;
			char		*tmpptr;
			int			count;
			char		id[5];
			int			noSamples;
			ULong		*offlist;
			ULong		ssize = sizeof(SWAV) / 4;

			theblock = new fileblock (thefile);
			if (theblock)
			{
				tmpaddress = getdata(theblock);
				size = getsize(theblock);

				longaddress = (ULong*)tmpaddress;

				noSamples = *longaddress;
				if (pelement <= noSamples)							//RJS 07Apr99
				{
					longaddress++;

					offlist = longaddress;

					SamplePtr->blockptr = theblock;
					SamplePtr->size = size;
					SamplePtr->noFiles = noSamples;
					SamplePtr->offsetptr = (SOffsetList*) offlist;

					longaddress += (noSamples*2); // offlist is 2 longs * nosamples

					tmpptr = (char*) longaddress;

					for (count = 0; count < 4; count ++)
						id[count] = *tmpptr++;

					id[4] = 0;

					if (stricmp(id,"SWAV") == 0)
					{
						header1 = (SWAV*) longaddress;

						longaddress += ssize;

						SamplePtr->headerptr = header1;
						SamplePtr->dataptr = (UByteP) longaddress; 
					}
					else
					{
						SamplePtr->blockptr = NULL;

						delete theblock;

						_Error.EmitSysErr("Unknown sample format");
					}
				}
				else
				{
					SamplePtr->blockptr = NULL;						//DAW 07Apr99
					SamplePtr = NULL;								//DAW 07Apr99
																	//DAW 07Apr99
					delete theblock;								//DAW 07Apr99


					_Error.EmitSysErr("Chatter file size wrong... %d, %d elements!",fileindex,noSamples);//DAW 07Apr99
				}
			}
			else
				SamplePtr = NULL;
		}

		if (pelement)
		{
			pelement--;
			if (pelement < SamplePtr->noFiles)						//RDH 12Apr99
			{
				StartOff = SamplePtr->offsetptr[pelement].offset;		//RJS 27Jul98
				SampleSize = SamplePtr->offsetptr[pelement].size;		//RJS 27Jul98
			}
			else
			{
				_Error.EmitSysErr("Chatter file size wrong... phrase %x, %d elements!",thephrase,SamplePtr->noFiles);
			}

	//DeadCode RJS 27Jul98 		if (pelement)											//RJS 23Jul98
	//DeadCode RJS 27Jul98 			StartOff = SamplePtr->offsetptr[pelement-1];		//RJS 23Jul98
	//DeadCode RJS 27Jul98 															
	//DeadCode RJS 27Jul98 		SampleSize = SamplePtr->offsetptr[pelement] - StartOff;	//RJS 23Jul98
		}
	}

	return(SamplePtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessMessages
//Author		Robert Slater
//Date			Tue 9 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ProcessMessages(SLong frametime)
{
	if (	!lockout											//RJS 11Jun99
		&&	Manual_Pilot.ControlledAC2							//RJS 11Jun99
		&&	!Manual_Pilot.ControlledAC2->weap.Ejected)			//RJS 11Jun99
	{
		//Without internal sample buffer...							//RJS 25May99
		if (!_Replay.Playback && frametime)						//RJS 12Jan00
		{
			RadioMessageP	MessPtr = RootMessPtr;
			MESSAGE_STRUC*	newmess;

			if (MessPtr)
			{
				if (MessPtr->isAudio)
				{
					if (MessPtr->PlayQueue)
					{
						if (_Miles.SampleFinished(MessPtr->PlayQueue,hipriSet))//RJS 25May99
						{
							MessPtr->PlayQueue = NULL;					//RJS 29Sep00

							RootMessPtr = NULL;

							delete[]MessPtr->sampleptr;
							delete MessPtr;
						}											//RJS 25May99
						else
							timesincestart += frametime;		//RJS 01Apr99
					}
					else
					{
//DeadCode RJS 06Jul99 						SLong	frequency = 11025;
//DeadCode RJS 06Jul99 						if (MessPtr->theVoice == VOICE_REST)
//DeadCode RJS 06Jul99 							frequency += Math_Lib.rnd(1000) - 750;

						timesincelast = 0;
						timesincestart = 0;

						MessPtr->PlayQueue = _Miles.PlaySampleRadio(MessPtr->sampleptr,MessPtr->samplesize,MessPtr->VolScale,MessPtr->theFrequency,8);//RJS 06Jul99
					}
				}
				else
				{
					MessPtr->fakeplaytime -= frametime;		//RJS 01Apr99
					if (MessPtr->fakeplaytime <= 0)
					{
						MessPtr->fakeplaytime = 0;

						RootMessPtr = NULL;
						if (MessPtr->sampleptr)				//RJS 18Jun99
							delete[]MessPtr->sampleptr;		//RJS 18Jun99
						delete MessPtr;
					}
					else
						timesincestart += frametime;		//RJS 01Apr99
				}
			}
			else
			{
				hipriSet = false;									//RJS 25May99
				newmess = _MsgBuffer.SayNextMessage(frametime);		//RJS 10May99
				if (newmess)
				{
					//No audio if in accel...						//RJS 27May99
					if (!View_Point->Accel())						//RJS 27May99
						PlayMessage(*newmess);						//RJS 27May99

					_MsgBuffer.nothingatall = false;
					timesincelast = 0;
				}
				else
				{
					timesincelast += frametime;				//RJS 01Apr99
					if (timesincelast > 450)		//display nowt after 4.5secs//DAW 07Apr99
					{
	//DEADCODE DAW 05/05/99 					timesincelast = 450;
						_MsgBuffer.nothingatall = true;
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPlaceName
//Author		Robert Slater
//Date			Tue 14 Jul 1998
//
//Description	
//
//				Converts an item world X & Z coordinate
//				into its equivalent 4-digit landscape block number.
//
//				This is then turned into a 40 x 56 placename location...
//
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord		RadioChatter::GetPlaceNum(Coords3D* WPtr,int noelements)
{
			UWord	location;
			SLong	xof, zof, val;
			UWord	bigx, bigz, x, z;
//DEADCODE JIM 18/03/99 			Coords3D	*WPtr = &itm->World;

			// Sector shift = 21...
			val=WPtr->X>>21;

			x = (val&0x7);
			bigx = (val>>3);

			// Sector shift = 21...
			val=WPtr->Z>>21;

			z = (val&0x7);
			bigz = (val>>3);

			// x vals range from 2 to 6
			// z vals range from 2 to 8

			if (bigx > 6)
				bigx = 6;

			bigx -= 1;
			bigz -= 1;

			xof = (bigx * 8) + x;
			zof = (bigz * 8) + z;

			location = (zof * 40) + xof;
			if (location < noelements)
				return location;
			else
				return 0;
}

//DEADCODE RJS 5/5/00 SectorNameP	RadioChatter::GetPlaceName(UWord location)
//DEADCODE RJS 5/5/00 {
//DEADCODE RJS 5/5/00 	if (LoadSectorNames(FIL_RCHAT_NAMEGRID))
//DEADCODE RJS 5/5/00 		if (location < theSectors.noelements)
//DEADCODE RJS 5/5/00 			return	&theSectors.PlaceNames[location];
//DEADCODE RJS 5/5/00 	return NULL;
//DEADCODE RJS 5/5/00 }
//DEADCODE RJS 5/5/00 
//DEADCODE RJS 5/5/00 SectorNameP	RadioChatter::GetPlaceName(ItemPtr	itm)
//DEADCODE RJS 5/5/00 {
//DEADCODE RJS 5/5/00 	SectorNameP	NamePtr = NULL;
//DEADCODE RJS 5/5/00 	if (LoadSectorNames(FIL_RCHAT_NAMEGRID) && itm)						//RJS 15Jun99
//DEADCODE RJS 5/5/00 	{
//DEADCODE RJS 5/5/00 		UWord location=GetPlaceNum(&itm->World,theSectors.noelements);
//DEADCODE RJS 5/5/00 		return (GetPlaceName(location));
//DEADCODE RJS 5/5/00 	}
//DEADCODE RJS 5/5/00 
//DEADCODE RJS 5/5/00 	return(NamePtr);
//DEADCODE RJS 5/5/00 }
//DeadCode DAW 26Mar99 SectorNameP	RadioChatter::GetPlaceName(ItemPtr	itm)
//DeadCode DAW 26Mar99 {
//DeadCode DAW 26Mar99 	SectorNameP	NamePtr = NULL;
//DeadCode DAW 26Mar99 	if (itm)
//DeadCode DAW 26Mar99 	{
//DeadCode DAW 26Mar99 		if (LoadSectorNames(FIL_RCHAT_NAMEGRID))
//DeadCode DAW 26Mar99 		{
//DeadCode DAW 26Mar99 			UWord	location;
//DeadCode DAW 26Mar99 			SLong	xof, zof, val;
//DeadCode DAW 26Mar99 			UWord	bigx, bigz, x, z;
//DeadCode DAW 26Mar99 			Coords3D	*WPtr = &itm->World;
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			// Sector shift = 21...
//DeadCode DAW 26Mar99 			val=WPtr->X>>21;
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			x = (val&0x7);
//DeadCode DAW 26Mar99 			bigx = (val>>3);
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			// Sector shift = 21...
//DeadCode DAW 26Mar99 			val=WPtr->Z>>21;
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			z = (val&0x7);
//DeadCode DAW 26Mar99 			bigz = (val>>3);
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			// x vals range from 2 to 6
//DeadCode DAW 26Mar99 			// z vals range from 2 to 8
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			if (bigx > 6)
//DeadCode DAW 26Mar99 				bigx = 6;
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			bigx -= 1;
//DeadCode DAW 26Mar99 			bigz -= 1;
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			xof = (bigx * 8) + x;
//DeadCode DAW 26Mar99 			zof = (bigz * 8) + z;
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 			location = (zof * 40) + xof;
//DeadCode DAW 26Mar99 			if (location < theSectors.noelements)
//DeadCode DAW 26Mar99 				NamePtr = &theSectors.PlaceNames[location];
//DeadCode DAW 26Mar99 		}
//DeadCode DAW 26Mar99 	}
//DeadCode DAW 26Mar99 
//DeadCode DAW 26Mar99 	return(NamePtr);
//DeadCode DAW 26Mar99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSectorNames
//Author		Robert Slater
//Date			Tue 14 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SectorNameP	RadioChatter::LoadSectorNames(SLong	thefile)
{
	if (theSectors.theblock == NULL)
	{
		fileblock	*theblock = new fileblock ((FileNum)thefile);
		if (theblock)
		{
			theSectors.theblock = theblock;
			theSectors.PlaceNames = (SectorNameP) getdata(theblock);
			theSectors.noelements = getsize(theblock) / sizeof(SectorName);
		}
	}

	return(theSectors.PlaceNames);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetScript
//Author		Robert Slater
//Date			Thu 28 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWordP	RadioChatter::GetScript(SLong	scriptno,RadioMessageP MessPtr,PhraseTables& singlephrase)
{
	UWordP	ptr = NULL;

//DEADCODE CSB 15/12/99 #ifndef NO_CHATTER_

	singlephrase = PHRASE_NULL;
#ifndef	_NO_CHATTER_
	if (scriptno)
	{
		if (theScripts.theblock == NULL)
		{
			fileblock	*theblock = new fileblock (FIL_RCHAT_SCRIPT_TABLE);
			if (theblock)
			{
				theScripts.theblock = theblock;
				theScripts.ScriptTable = (ULongP) getdata(theblock);
			}
		}
	 	assert(theScripts.ScriptTable);

		ULong	scriptptr = theScripts.ScriptTable[scriptno-1];
		ULong	isscript = scriptptr & 0x80000000;

		if (isscript)											//RJS 12Apr99
		{
			scriptptr -= 0x80000000;
			ptr = (UWordP) ((UByteP)theScripts.ScriptTable + scriptptr);

			MessPtr->MainStrip(ptr);							//RJS 11May99
		}
		else
			singlephrase = (PhraseTables) scriptptr;
	}
#endif

	return(ptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayMessage
//Author		Robert Slater
//Date			Tue 12 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode RJS 27Jan99 void	RadioChatter::PlayMessage(	int		Scriptno,
//DeadCode RJS 27Jan99 									ItemPtr	Caller,
//DeadCode RJS 27Jan99 									ItemPtr	Trg,
//DeadCode RJS 27Jan99 									ItemPtr	Callee,
//DeadCode RJS 27Jan99 									Bool	noCaller	)
//DeadCode RJS 27Jan99 {
//DeadCode RJS 27Jan99 	if (Save_Data.vol.rchat)
//DeadCode RJS 27Jan99 	{
//DeadCode RJS 27Jan99 		TargetIndexes	tripeval;
//DeadCode RJS 27Jan99 
//DeadCode RJS 27Jan99 		PlayMessage(Scriptno,tripeval,Caller,Trg,Callee,noCaller);
//DeadCode RJS 27Jan99 	}
//DeadCode RJS 27Jan99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExpandMessage
//Author		Robert Slater
//Date			Tue 12 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ExpandMessage(PhraseBuffer&	fbuff,
									int		Scriptno,
									UWord&	randno,
									const	TargetIndexes&	tstruc,
									ItemPtr	Caller,
									ItemPtr	Trg,
									ItemPtr	Callee	)
{
	//Block RootMessPtr, so we can view while playing...
	lockout = true;												//RJS 04Jun99
	RadioMessageP	OldRootMessPtr = RootMessPtr;
	RootMessPtr = NULL;
	RadioMessageP	MessPtr = CreateMessage((mobileitem*)Caller,
											(mobileitem*)Trg,
											(mobileitem*)Callee,
											randno,
											tstruc,
											VOICE_SILENT,				//RJS 11Oct00
											&fbuff	);

	if (MessPtr)
		Message_DecomposeScript(MessPtr,Scriptno);

	RootMessPtr = OldRootMessPtr;
	lockout = false;											//RJS 04Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExpandCallsign
//Author		Robert Slater
//Date			Tue 12 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ExpandCallsign(PhraseBuffer&	phbuf, ItemPtr	Caller,const VoiceType& voice)
{
	TargetIndexes	tstruc;
	int				thephrase = 0;
	UWord			tmprand = 0;
	if (Caller)
	{
		if (Caller->Status.size == AIRSTRUCSIZE)
		{
			if (_DPlay.Implemented && Caller->uniqueID.commsmove)		//RJS 12Jul00
				thephrase = PHRASE_COMMSTARGET;							//RJS 12Jul00
			else
				thephrase = PHRASE_CALLEE_GSN_RAF;
//DEADCODE RJS 5/12/00 			if (((AirStrucPtr)Caller)->nationality == NAT_RED)
//DEADCODE RJS 5/12/00 				thephrase = PHRASE_CALLEE_GSN_RAF;
//DEADCODE RJS 5/12/00 			else
//DEADCODE RJS 5/12/00 				thephrase = PHRASE_CALLEE_GSN_RAF;
		}
	}
	else
	{
		// Pick from voice...
		switch (voice)
		{
		case VOICE_TOWER:
			thephrase=PHRASE_S_VOXTOWER;
		break;
		case VOICE_GROUND:
			thephrase=PHRASE_S_VOXGROUND;
		break;
		case VOICE_FEMALE:
			thephrase=PHRASE_S_VOXOPS;
		break;
		}
	}

	ExpandMessage(phbuf,thephrase,tmprand,tstruc,NULL,Caller,Caller);	//RJS 12Jul00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExpandPlace
//Author		Robert Slater
//Date			Tue 12 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ExpandPlacename(PhraseBuffer&	phbuf, ItemPtr	Caller)
{
	if (Caller)
	{
		TargetIndexes	tstruc;
		UWord			tmprand = 0;

		ExpandMessage(phbuf,PHRASE_PLACENAMES,tmprand,tstruc,NULL,Caller,NULL);//RDH 04May99
	}
}

void	RadioChatter::ExpandPlacename(PhraseBuffer&	phbuf, UWord place)
{
	TargetIndexes	tstruc;
	tstruc.targetname=place;
	UWord	tmprand=0;
	ExpandMessage(phbuf,PHRASE_PLACENAMES,tmprand,tstruc,NULL,NULL,NULL);//RDH 04May99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Message_DecomposeScript
//Author		Robert Slater
//Date			Tue 12 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::Message_DecomposeScript(RadioMessageP	MessPtr,int Scriptno)
{
	UWordP			ScriptPtr;
	PhraseTables	ThePhrase;
//DeadCode RJS 20Oct00 	int		count=0;
	ULong	nochoices = Scriptno & 0xFFFF0000;

	if (nochoices)
	{
//DeadCode RJS 12Apr99 		nochoices >>= 16;

		Scriptno &= 0xFFFF;
		ScriptPtr = GetScript(Scriptno,MessPtr,ThePhrase);		//RJS 12Apr99
		if (ScriptPtr)
		{
			ThePhrase = (PhraseTables) *ScriptPtr;
			while (ThePhrase != PHRASE_NULL)
			{
#ifdef	CHATTERTRACE
				dbgCurrentPhrase = ThePhrase;
#endif
				ComposeSample(MessPtr,ThePhrase);
				ScriptPtr++;

				lastPhrase = ThePhrase;
				ThePhrase = (PhraseTables) *ScriptPtr;
			}
		}
		else
		{
#ifdef	CHATTERTRACE
			dbgCurrentPhrase = ThePhrase;
#endif
			ComposeSample(MessPtr,ThePhrase);
		}
	}
	else
	{
#ifdef	CHATTERTRACE
		dbgCurrentPhrase = Scriptno;
#endif
		ComposeSample(MessPtr,Scriptno);
	}

	delete MessPtr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayMessage
//Author		Robert Slater
//Date			Wed 13 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::PlayMessage(const	MESSAGE_STRUC&	radiomessage, SLong vol, bool isChatter)
{
#ifdef CHATTERTRACE
// defined in rchatter.h
	if (damageMessage)
	{
		UWord cw=GETFPCW();
		::AfxTrace("Saying: %08x\n",radiomessage.messagecnt);//radiomessage.scriptno);
		SETFPCW(cw);
	}
#endif
	RadioMessageP	MessPtr = CreateMessage((mobileitem*)radiomessage.caller,
											(mobileitem*)radiomessage.target,
											(mobileitem*)radiomessage.callee,
											radiomessage.randomno,//RDH 04May99
											radiomessage.targetinfo,
											radiomessage.voiceindex,
											NULL,
											vol,
											radiomessage.voxstate);

	if (MessPtr)
	{
 		if (radiomessage.isComms)	MessPtr->isAudio = FALSE;//RJS 22Mar99

//DeadCode RJS 10May99 		if (radiomessage.addThinkTime)
//DeadCode RJS 10May99  			ComposeSample(MessPtr,PHRASE_RANDOMTHINKTIME);
		DecomposeScript(MessPtr,radiomessage.GetScript());				//RJS 15Sep00
	}

	//Expand latest message to string straight away...
	if (!isChatter)													//RJS 15Jun99
		_MsgBuffer.ExpandDirect(radiomessage);						//RJS 15Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExpandMessage
//Author		Robert Slater
//Date			Wed 13 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ExpandMessage(PhraseBuffer&	fbuff, const MESSAGE_STRUC&	radiomessage )
{
	//Block RootMessPtr, so we can view while playing...
	lockout = true;												//RJS 04Jun99
	RadioMessageP	OldRootMessPtr = RootMessPtr;
	RootMessPtr = NULL;
	RadioMessageP	MessPtr = CreateMessage((mobileitem*)radiomessage.caller,
											(mobileitem*)radiomessage.target,
											(mobileitem*)radiomessage.callee,
											radiomessage.randomno,//RDH 04May99
											radiomessage.targetinfo,
											radiomessage.voiceindex,
											&fbuff,
											128,
											radiomessage.voxstate);

	if (MessPtr)
	{
		if (radiomessage.isComms)	MessPtr->isAudio = FALSE;//RJS 22Mar99

		Message_DecomposeScript(MessPtr,radiomessage.GetScript());
	}

	RootMessPtr = OldRootMessPtr;
	lockout = false;											//RJS 04Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TimeOut
//Author		Robert Slater
//Date			Wed 27 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	RadioChatter::TimeOut()
{
	if (timesincelast < TIME_TIMEOUT)
		return (FALSE);

	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RADIOMESSAGE
//Author		Robert Slater
//Date			Wed 27 Jan 1999
//
//Description	constructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
RADIOMESSAGE::RADIOMESSAGE(	RADIOMESSAGE*& 	MessPtr,
							ItemPtr 		from,
							ItemPtr			about,
							ItemPtr			to,
							SWord			vol,
							const TargetIndexes&	tstruc,
							PhraseBuffer*	fbuffp,
							VoiceType		vox,
							const bool&		in3D	)
{
	caller = (mobileitem*) from;
	target = (mobileitem*) about;
	callee = (mobileitem*) to;
	target2 = NULL;														//RJS 16Oct00

	theFrequency = 11025;											//RJS 06Jul99
	if (vox != VOICE_SILENT)											//RJS 11Oct00
	{
		//Even quieter if you want the voice off...					//RJS 30Jun99
		if (	(	(vox >= VOICE_PLAYER)							//RJS 29Feb00
				&&	(vox < VOICE_REST)	)							//RJS 29Feb00
			&&	Save_Data.gamedifficulty[GD_NOPLAYERVOICE]	)		//RJS 30Jun99
			VolScale = 0;											//RJS 30Jun99
		else
		{
			if (from)
			{
				if (	(from->Status.size == AIRSTRUCSIZE)
					&&	(in3D == true)								//RJS 17May00
					&&	(!AirStrucPtr(from)->PlayerInGroup())	)
					VolScale = 96;
				else
					VolScale = vol;
			}
			else
				VolScale = 80;				//Quiet if no caller...	//RJS 30Jun99
		}

		if (	(vox == VOICE_TOWER)							//RJS 14Aug00
			&&	Manual_Pilot.ControlledAC2
			&&	(Manual_Pilot.ControlledAC2->nationality != NAT_RAF)	)
			vox = VOICE_LWTOWER;


		if ((fbuffp==NULL) && (Save_Data.vol.rchat > 0))			//RJS 22Mar99	   
			isAudio = TRUE;				   					   
		else		
			isAudio = FALSE;
	}
	else
	{
		VolScale = 0;
		isAudio = FALSE;
	}

	TargetStuff = tstruc;					
	messbuffptr = fbuffp;
	theVoice = vox;


	next = NULL;
	sampleptr = NULL;
	samplelength = 0;

	bearing = 0;
	distance = -1;
	nophrases = 0;
	samplesize = 0;
	isPlaying = FALSE;
	PlayQueue = NULL;
					
	MessPtr = this;					//RJS 17May00

//DEADCODE RDH 17/05/00 	if ((fbuffp==NULL) && (Save_Data.vol.rchat > 0))			//RJS 22Mar99
//DEADCODE RDH 17/05/00 	{								   
//DEADCODE RDH 17/05/00 		isAudio = TRUE;				   
//DEADCODE RDH 17/05/00 				
//DEADCODE RDH 17/05/00 		MessPtr = this;				   
//DEADCODE RDH 17/05/00 	}								   
//DEADCODE RDH 17/05/00 	else		
//DEADCODE RDH 17/05/00 	{			   
//DEADCODE RDH 17/05/00 		isAudio = FALSE;
//DEADCODE RDH 17/05/00 		MessPtr = this;
//DEADCODE RDH 17/05/00 	}

	IsExcited = 0;												//RJS 18Mar99
	TextNum = FALSE;											//RJS 18Mar99
	fakeplaytime = 0;											//RJS 22Mar99

	randomvoice = 0;											//RJS 17May99
	usedigits = false;											//RJS 21Jan00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindVoiceType
//Author		Robert Slater
//Date			Fri 5 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	MESSAGE_STRUC::SetVoiceType()
{
	voiceindex = VOICE_PLAYER;										  //RDH 11/05/99
	if (caller)
	{
		if (caller->AcIsPlayer())								//RJS 29Feb00
		{														//RJS 29Feb00
			if (caller->nationality == NAT_RAF)					//RJS 10May00
				voiceindex = VOICE_PLAYER;						//RJS 29Feb00
			else												//RJS 29Feb00
				voiceindex = VOICE_LWPLAYER;					//RJS 29Feb00
		}														//RJS 29Feb00
 		else
 		{
			if (caller->nationality == NAT_RAF)					//RJS 10May00
				voiceindex = VOICE_REST;						//RJS 29Feb00
			else												//RJS 29Feb00
				voiceindex = VOICE_LWREST;						//RJS 29Feb00
 		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TriggerMsg
//Author		Robert Slater
//Date			Thu 28 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
#ifdef TriggerMsg
#undef	TriggerMsg
#endif
const MESSAGE_STRUC&	RadioChatter::TriggerMsg(const MESSAGE_STRUC&	msg)
{
#ifndef NO_CHATTER_
	
	//We still want to buffer in accel mode!					//RJS 27May99
	if (!_Replay.Playback)												//RJS 11Oct00
	{
 		ProcessVoice(msg);												//RJS 11Oct00
	
		if (msg.GetScript())											//RJS 11Oct00
		{
			if (!_MsgBuffer.AddToBuffer(msg))
			{
				if (!View_Point->Accel())							//RJS 28May99
				{
					if (TimeOut())			// timeout > 30 secs?
					{
						if (msg.caller && Persons2::PlayerSeenAC)		//RJS 26Oct00
						{
							float	dx = msg.caller->World.X - Persons2::PlayerSeenAC->World.X;	//RJS 26Oct00
							float	dy = msg.caller->World.Y - Persons2::PlayerSeenAC->World.Y;	//RJS 26Oct00
							float	dz = msg.caller->World.Z - Persons2::PlayerSeenAC->World.Z;	//RJS 26Oct00
							float	volScale = fastMath.FastSqrt(dx*dx+dy*dy+dz*dz);

							volScale *= 105.;
							volScale /= 500*1000;

							volScale = 105. - volScale;
							if (volScale > 10.)
							{
								SLong	theVol;

								fastMath.FloatToInt(&theVol,volScale);

								PlayMessage(msg,theVol,true);			//RJS 2Oct00
							}
						}
//DeadCode RJS 7Nov00 						else
//DeadCode RJS 7Nov00 						{
//DeadCode RJS 7Nov00 							if (msg.caller)								//RJS 7Nov00
//DeadCode RJS 7Nov00 								PlayMessage(msg,105,true);				//RJS 7Nov00
//DeadCode RJS 7Nov00 						}
					}
				}
			}
			else
			{
				//prioritise!
				if (msg.priority == PRI_MAX)						//RJS 25May99
				{													//RJS 25May99
					hipriSet = true;								//RJS 25May99
					if (	RootMessPtr
						&&	(RootMessPtr->fakeplaytime > 200))		//RJS 25May99
						RootMessPtr->fakeplaytime = 200;			//RJS 25May99
				}													//RJS 25May99
			}
		}
	}

#endif

	return(msg);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ComposeDigitNumber
//Author		Robert Slater
//Date			Wed 10 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ComposeDigitNumber(RadioMessageP	MessPtr, SLong number, SWord nodigits)
{
	if (number >= 0)
	{
		SLong	tmpnumber;
		SLong	digits[32];
		SWord	digitcnt = 0;

		do
		{
			tmpnumber = number;
			number /= 10;

			// extract remainder + 1, cos 0 not valid script..
			digits[digitcnt++] = (tmpnumber-(number*10))+1;
		}
		while (number);

		while (digitcnt < nodigits)		digits[digitcnt++] = 1;					//zero
	
		MessPtr->TextNum = TRUE;								//RJS 18Mar99

		digitcnt--;
		if (digitcnt > -1)
			ComposeSample(MessPtr,PHRASE_NUMBER+digits[digitcnt--]);	//RJS 15Aug00
		else
			ComposeSample(MessPtr,PHRASE_NUM_0);	//zero		//RJS 18Mar99

		while (digitcnt > -1)
		{
			if (MessPtr->isAudio)								//RJS 12Apr99
 				ComposeSample(MessPtr,PHRASE_STOP);				//RJS 12Apr99

			ComposeSample(MessPtr,PHRASE_NUMBER+digits[digitcnt]);
			digitcnt--;
		}

		MessPtr->TextNum = FALSE;								//RJS 18Mar99
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessUserMessage
//Author		Robert Slater
//Date			Thu 11 Feb 1999
//
//Description	Calc delay, repeatable and priority
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	MESSAGE_STRUC::ProcessUserMessage()
{
	// Priority...
	if (messagetype & MSG_LP)
	{
		priority = PRI_LOW;
		if (messagetype & MSG_REPEAT)
			visibility = NOTVIS_2;
		else
			visibility = NOTVIS_1;
   	}
	else
	{
//DEADCODE RDH 02/04/99 		if ((caller == Manual_Pilot.ControlledAC2) || (callee == Manual_Pilot.ControlledAC2))
//DEADCODE RDH 02/04/99 			priority = PRI_MAX;
//DEADCODE RDH 02/04/99 		else
		priority = PRI_MED;
		if (messagetype & MSG_REPEAT)
			visibility = VIS_2;
		else
			visibility = VIS_3;
	}

	if (messagetype & MSG_DELAY)
		timeout = 50 + Math_Lib.rnd(50);						//RJS 13May99
	else
		timeout = 0;

	if (messagetype & MSG_COMMS)
		isComms = TRUE;
	else
		isComms = FALSE;

	if (messagetype & MSG_HIPRIORITY_X)							//RJS 13May99
		priority = PRI_MAX;										//RJS 13May99
	else
	{
		if (messagetype & MSG_MEDHIPRIORITY_X)					//RJS 24Jun99
			priority = PRI_MEDMAX;
	}

	if (	(messagetype & MSG_BLOCKCHATTER)							//RJS 9Nov00
		||	(caller	&& (caller->ai.radiosilent == TRUE)	)	)			//RJS 9Nov00
		blockchatter = TRUE;									//RJS 06Jul99
	else														//RJS 06Jul99
		blockchatter = FALSE;									//RJS 06Jul99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PhraseToResource
//Author		Robert Slater
//Date			Fri 12 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ULong	RadioChatter::PhraseToResource(SLong	thePhrase)
{
	return (PhraseToFile[thePhrase>>8].idsresourcename+(thePhrase&0xFF));
}

ULong	RadioChatter::PanelPhraseToResource(SLong	thePhrase)
{
	if ((thePhrase&0xFF00)==PHRASE_IDSFUDGE)
		return IDSFudgeTable[thePhrase&0xFF];

	return PhraseToResource(thePhrase);
}

static int poodistance = 25000;
static UWord poobearing = 0;
static int	poogust = PHRASE_GUSTLIGHT;
static int	pootargtype = 1;
static int	pootargname = 1;
static int	pootargmove = 1;
static int	pootargweap = 1;
static UWord poobearing2 = 0;
static int  poospeed = 1500;
static int  pooheight = 1;
static int  pooaf = 1;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FiddleROL
//Author		Robert Slater
//Date			Mon 22 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	RADIOMESSAGE::FiddleROL()
{
	distance = poodistance;
	bearing = poobearing;
	pitch = Math_Lib.rnd(32768) - 16384;
	speed = poospeed;

	return(TRUE);
}

void	RadioChatter::ComposeFakeDigitNumber(RadioMessageP	MessPtr, SLong number, SWord nodigits)
{
}

//DeadCode RJS 6Sep00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 6Sep00 //Procedure		ComposeFakeSample
//DeadCode RJS 6Sep00 //Author		Robert Slater
//DeadCode RJS 6Sep00 //Date			Mon 22 Feb 1999
//DeadCode RJS 6Sep00 //
//DeadCode RJS 6Sep00 //Description	
//DeadCode RJS 6Sep00 //
//DeadCode RJS 6Sep00 //Inputs		
//DeadCode RJS 6Sep00 //
//DeadCode RJS 6Sep00 //Returns	
//DeadCode RJS 6Sep00 //
//DeadCode RJS 6Sep00 //------------------------------------------------------------------------------
//DeadCode RJS 6Sep00 void	RadioChatter::ComposeFakeSample(RadioMessageP	MessPtr,int phrase)
//DeadCode RJS 6Sep00 {
//DeadCode RJS 6Sep00 }

static int poolocation;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayAll
//Author		Robert Slater
//Date			Mon 22 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::PlayAll()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFakePlaceName
//Author		Robert Slater
//Date			Thu 25 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SectorNameP	RadioChatter::GetFakePlaceName()
{
	return NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChooseScript
//Author		Robert Slater
//Date			Thu 4 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	MESSAGE_STRUC::ChooseScript(int	sno) const
{
	ULong	realScriptBits = sno & 0xFFFF0000;							//RJS 15Aug00
	if (realScriptBits)							//is it a script or phrase?
	{
		ULong	randChoices = realScriptBits>>16;						//RJS 15Aug00
		ULong	normrand = randChoices & 0x00FF;						//RJS 15Aug00
		ULong	scriptMask = 65536;										//RJS 15Aug00
																//RJS 17Mar99
		sno &= 0xFFFF;											//RJS 17Mar99
		if (sno)												//RJS 05May00
		{
			if (randChoices & 0xFF00)	//is there an excited part?
			{					
				ULong	excitedrand = randChoices>>8;					//RJS 15Aug00
				ULong	excitedoffset = normrand;					//RJS 17May99

				if (normrand)
				{
					// can we do range check?
					if (target && callee)
					{
						float	dx,dy,dz,distance;						//RJS 15Aug00
		
						dx = target->World.X - callee->World.X;
						dy = target->World.Y - callee->World.Y;
						dz = target->World.Z - callee->World.Z;

						distance = fastMath.FastSqrt(dx*dx+dy*dy+dz*dz);	//RJS 15Aug00
						if (distance <= 250000.)	//cms
							voxstate = VOXSTATE_EXCITED;
						else
						{
							excitedrand = 0;
							voxstate = VOXSTATE_NORMAL;
						}
					}
					else
					{
						excitedrand = 0;
						voxstate = VOXSTATE_NORMAL;					//RJS 18Mar99
					}
				}
				else
					voxstate = VOXSTATE_EXCITED;

				if (excitedrand)										//RJS 15Aug00
				{
					normrand = 0;

					if (excitedoffset)									//AM 21Aug00
					{
						sno += excitedoffset;								//RJS 15Aug00
// skip 0th choice (which is a repeat of 1st)
						scriptMask++;										//RJS 15Aug00
					}

					if (excitedrand > 1)								//RJS 15Aug00
						sno += Math_Lib.rnd(excitedrand);				//RJS 15Aug00
				}
			}														//RJS 17Mar99
			else													//RJS 17Mar99
				voxstate = VOXSTATE_NORMAL;							//RJS 17Mar99
																	//RJS 17Mar99
			if (normrand > 1)										//RJS 17Mar99
			{														//RJS 17Mar99
				sno += Math_Lib.rnd(normrand);						//RJS 17Mar99
// skip 0th choice (which is a repeat of 1st)
				scriptMask++;										//RJS 17Mar99
			}

			sno += scriptMask;											//RJS 15Aug00
		}
	}
	else
		voxstate = VOXSTATE_NORMAL;										//RJS 14Sep00

	scriptno = sno;

//DeadCode RJS 15Sep00 #ifndef	NDEBUG
//DeadCode RJS 15Sep00 	_Radio.totmess++;
//DeadCode RJS 15Sep00 	messagecnt = _Radio.totmess;										//JIM 29Apr99
//DeadCode RJS 15Sep00 #endif
//DeadCode RJS 15Sep00 
//DeadCode RJS 15Sep00 	randomno = Math_Lib.rnd();

	if (scriptno)
		_Radio.ScanScript(*this);											//RJS 6Sep00
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StripIsPlayer
//Author		Robert Slater
//Date			Mon 12 Apr 1999
//
//Description	removes any callsign from script, if it is the 1st phrase
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RADIOMESSAGE::StripIsPlayer(UWordP &ScriptPtr)
{
	thePhrase = (PhraseTables) *ScriptPtr;						//RJS 11May99
	while (thePhrase != PHRASE_NULL)
	{
//DeadCode RJS 29Sep100 #pragma	message(__HERE__ " Rob:  Fix caller phrase bandwidth")
		//Assume there is a bandwidth for this...
 		if (	((thePhrase >= PHRASE_CALLER_GL_RAF) && (thePhrase < PHRASE_CALLEE_SQUADNUMBERSHORT))
//DeadCode RJS 29Sep100 			||	((thePhrase & 0xFF00) == PHRASE_CALLEE_GLW)
			||	((thePhrase & 0xFF00) == PHRASE_CALLEE_GL_RAF)
			||	(thePhrase == PHRASE_CALLING)	
			||	(thePhrase == PHRASE_THISIS)	)
 		{
//DeadCode RJS 29Sep100  			DodgyRandomFix();									//RJS 11May99
 			ScriptPtr++;
 		}
 		else
		{
			if (((ULong)thePhrase & 0xFF00) == PHRASE_PUNCTUATION)
				ScriptPtr++;
			else
				break;
		}

		thePhrase = (PhraseTables) *ScriptPtr;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StripCaller
//Author		Robert Slater
//Date			Mon 12 Apr 1999
//
//Description	Just removes caller from script, if it is the 1st phrase
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RADIOMESSAGE::StripCaller(UWordP &ScriptPtr)
{
	thePhrase = (PhraseTables) *ScriptPtr;						//RJS 11May99
	while (thePhrase != PHRASE_NULL)
	{
		//Assume there is a bandwidth for this...
//DeadCode RJS 29Sep100 #pragma	message(__HERE__ " Rob:  Fix caller phrase bandwidth")
 		if (	((thePhrase >= PHRASE_CALLER_GL_RAF) && (thePhrase < PHRASE_CALLEE_SN))
			||	(thePhrase == PHRASE_CALLING)
			||	(thePhrase == PHRASE_THISIS)	)
 		{
//DeadCode RJS 29Sep100  			DodgyRandomFix();									//RJS 11May99
 			ScriptPtr++;
 		}
 		else
		{
			if (((ULong)thePhrase & 0xFF00) == PHRASE_PUNCTUATION)
				ScriptPtr++;
			else
				break;
		}

		thePhrase = (PhraseTables) *ScriptPtr;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Enter3D
//Author		R. Hyde 
//Date			Wed 28 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::Enter3D(bool	inthe3D)
{
	ClearOldMessage();														//RJS 29Sep00

	windHeightSet = 0;
	windSpeedSet = -1;

	in3D = inthe3D;

#ifndef	NDEBUG
	if (in3D)
		naughtynaughty = false;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearOldMessage
//Author		Robert Slater
//Date			Fri 29 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ClearOldMessage()
{
	RadioMessageP	MessPtr = RootMessPtr;
	RadioMessageP	TmpMessPtr;

	// Clean up...
	while (MessPtr)
	{
		TmpMessPtr = MessPtr->next;

		if (MessPtr->sampleptr)
			delete[]MessPtr->sampleptr;

		MessPtr->caller = NULL;
		MessPtr->callee = NULL;
		MessPtr->target = NULL;
		MessPtr->distance = -1;
		MessPtr->samplesize = 0;
		MessPtr->PlayQueue = NULL;										//RJS 29Sep00
		MessPtr->isAudio = FALSE;										//RJS 29Sep00

		delete MessPtr;

		MessPtr = TmpMessPtr;
	}


	RootMessPtr = NULL;

 	MessageCount = 0;

	timesincelast = 0;
	timesincestart = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Random
//Author		R. Hyde 
//Date			Tue 4 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		RADIOMESSAGE::Random(int	numbits)
{
	int	retval = masterrandom & ((1<<numbits)-1);

	masterrandom >>= numbits;

	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MainStrip
//Author		Robert Slater
//Date			Tue 11 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RADIOMESSAGE::MainStrip(UWordP&	ptr)
{
	if (	(caller == callee) 
		&&	(theVoice < VOICE_REST)	)								//RJS 29Sep00
		StripIsPlayer(ptr);						 
	else										 
	{											 
		if (!isAudio)					 
		{
			if (theVoice < VOICE_REST)									//RJS 29Sep00
				StripIsPlayer(ptr);
			else
				StripCaller(ptr);
		}
	}	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DodgyRandomFix
//Author		Robert Slater
//Date			Tue 11 May 1999
//
//Description	This is to ensure that the random seed remains in sync,
//				even when caller/callee phrases are stripped from the
//				message bar.
//
//				Must perform same Random tests as in ComposeSample()
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RADIOMESSAGE::DodgyRandomFix()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearMessages
//Author		Robert Slater
//Date			Mon 31 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ClearMessages(MsgType	messagetype)
{
	_MsgBuffer.ClearMessagesMsg(messagetype);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MsgInQ
//Author		Robert Slater
//Date			Mon 31 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		RadioChatter::MsgInQ()
{
	return _MsgBuffer.noBufferedMessages;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearMessages
//Author		Robert Slater
//Date			Thu 3 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ClearMessages(MsgPriority	priority)
{
	_MsgBuffer.ClearMessagesPri(priority);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearMessages
//Author		Robert Slater
//Date			Mon 14 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ClearMessages(MsgType	messagetype, ItemPtr	theTarget)
{
	_MsgBuffer.ClearMessagesMsg(messagetype,theTarget);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	Alias functions
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴


SLong	RadioChatter::AircraftType(RadioMessageP	MessPtr, ItemBasePtr	aci)
{
	SLong	actype = 1;
	
	if (MessPtr->TargetStuff.targettype)
		actype = MessPtr->TargetStuff.targettype;
	else
	{
		if (aci)
			actype = AirStrucPtr(*aci)->classtype->phrasename;
		else
			INT3;
	}

	actype -= PHRASE_ONE_AIRCRAFT;										//RJS 28Jun00

	return actype;
}

SLong	RadioChatter::SquadronName(AirStrucPtr	ac)
{
	SLong	squadnum =ac->ai.squadnum();

	if (squadnum < SQ_BR_START)									//RJS 02May00
		squadnum = Node_Data[SquadNum(squadnum)].squadron;		//RJS 02May00

// find raf or lw offset
	if (squadnum > SQ_LW_START)
		squadnum -= SQ_LW_START;
	else
	{
		squadnum -= SQ_BR_START;
		//I need a cludge here for the Defiant and Blenheim squads I have added.
		//However we were already 3 callsigns short!
		if (squadnum>50)												//JIM 23Oct00
			squadnum-=10;												//JIM 23Oct00
	}
	return squadnum;
}

SLong	RadioChatter::SquadronNumber(RadioMessageP	MessPtr, ItemBasePtr	aci)
{
	SLong	squadnum;
	if (MessPtr->TargetStuff.targetname)
		squadnum = MessPtr->TargetStuff.targetname;
	else
	{
		squadnum = AirStrucPtr(*aci)->ai.squadnum();
		if (squadnum < SQ_BR_START)								//RJS 03May00
			squadnum = Node_Data[SquadNum(squadnum)].squadron;	//RJS 03May00
	}

// find raf or lw offset
	if (squadnum > SQ_LW_START)
	{
		squadnum -= SQ_LW_START;
		squadnum += PHRASE_GESCHWADERNUMBERSHORT;
	}
	else
	{
		squadnum -= SQ_BR_START;
		squadnum += PHRASE_SQUADRONNUMBER;
	}

	return squadnum;
}

SLong	RadioChatter::SquadronSectionColour(AirStrucPtr	ac)
{
	SLong	theColour = ac->fly.originalformpos & InFormMAX;			//RJS 22Oct00
	if (theColour > SQUAD_COLOUR_MAX)
		theColour -= SQUAD_COLOUR_MAX;

	return theColour+1;													//RJS 22Oct00
}

SLong	RadioChatter::SquadronSectionNumber(AirStrucPtr	ac)
{
	return (ac->fly.originalformpos & InWingMAX)+1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ONE_AIRCRAFT
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ONE_AIRCRAFT(RadioMessageP	MessPtr)
{
	ComposeSample(MessPtr,PHRASE_ONE_AIRCRAFT+AircraftType(MessPtr,*MessPtr->target));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GSQUADRAF
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	//CALLEE_RAFGS00 - CALLEE_RAFGS50
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SUBJECT_GSQUADRAF(RadioMessageP	MessPtr, AirStrucPtr	ac)
{
	ComposeSample(MessPtr,PHRASE_CALLEE_GSQUADRAF+SquadronName(ac));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GWINGRAF
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	CALLEE_RAFGW00- CALLEE_RAFGW50
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SUBJECT_GWINGRAF(RadioMessageP	MessPtr, AirStrucPtr	ac)
{
	ComposeSample(MessPtr,PHRASE_CALLEE_GWINGRAF+SquadronName(ac));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GLW
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	CALLEE_GLW00- CALLEE_GLW0x
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SUBJECT_GLW(RadioMessageP	MessPtr, AirStrucPtr	ac)
{
	ComposeSample(MessPtr,PHRASE_CALLEE_GLW+SquadronName(ac));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GRAF
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	CALLEE_G00- CALLEE_G50
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SUBJECT_GRAF(RadioMessageP	MessPtr, AirStrucPtr	ac)
{
	ComposeSample(MessPtr,PHRASE_CALLEE_GRAF+SquadronName(ac));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GL
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	CALLEE_GL00 - CALLEE_GL50
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SUBJECT_GL(RadioMessageP	MessPtr, AirStrucPtr	ac)
{
	ComposeSample(MessPtr,PHRASE_CALLEE_GL_RAF+SquadronName(ac));//RJS 17Feb00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GFLIGHTRAF
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLEE_GFLIGHTRAF(RadioMessageP	MessPtr)
{
	SUBJECT_GFLIGHTRAF(MessPtr,*MessPtr->callee);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLER_GFLIGHTRAF
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLER_GFLIGHTRAF(RadioMessageP	MessPtr)
{
	SUBJECT_GFLIGHTRAF(MessPtr,*MessPtr->caller);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SUBJECT_GFLIGHTRAF
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	CALLEE_GFL00 - CALLEE_GFL01
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SUBJECT_GFLIGHTRAF(RadioMessageP	MessPtr, AirStrucPtr	ac)
{
	ComposeSample(MessPtr,PHRASE_CALLEE_GFLIGHTRAF+SquadronSectionColour(ac));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GSECTIONRAF
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	CALLEE_S00 - CALLEE_S04
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SUBJECT_GSECTIONRAF(RadioMessageP	MessPtr, AirStrucPtr	ac)
{
	ComposeSample(MessPtr,PHRASE_CALLEE_GSECTIONRAF+SquadronSectionColour(ac));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_SN
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLEE_SN(RadioMessageP	MessPtr)
{
	SUBJECT_SN(MessPtr,*MessPtr->callee);
}

void	RadioChatter::CALLEE_S(RadioMessageP	MessPtr)
{
	SUBJECT_SN(MessPtr,*MessPtr->callee);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PLURAL_AIRCRAFT
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	SPITFIRES1A - DO17S
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::PLURAL_AIRCRAFT(RadioMessageP	MessPtr)
{
	ComposeSample(MessPtr,PHRASE_PLURAL_AIRCRAFT+AircraftType(MessPtr,*MessPtr->target));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_G
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SUBJECT_G(RadioMessageP	MessPtr, AirStrucPtr	ac)
{
	if (ac->nationality == NAT_RED)
		SUBJECT_GRAF(MessPtr,ac);
	else
		SUBJECT_GLW(MessPtr,ac);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GSQUADLW
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	CALLEE_LWGS00 - CALLEE_LWGS0x
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SUBJECT_GSQUADLW(RadioMessageP	MessPtr, AirStrucPtr	ac)
{
	_Error.EmitSysErr("Unused phrase!");

//	ComposeSample(MessPtr,PHRASE_CALLEE_GSQUADLW+SquadronName(ac));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DISTUNITS
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	YARDS|METRES|MILES|KILOMETRES
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::DISTUNITS(RadioMessageP	MessPtr, bool	smallunits)
{
	if (Save_Data.gamedifficulty [GD_UNITS])
	{
		if (smallunits)
			ComposeSample(MessPtr,PHRASE_METRES);
		else
			ComposeSample(MessPtr,PHRASE_KILOMETRES);
	}
	else
	{
		if (smallunits)
			ComposeSample(MessPtr,PHRASE_YARDS);
		else
			ComposeSample(MessPtr,PHRASE_MILES);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FIFTIES
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	FIFTIES_50 - FIFTIES_950
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::FIFTIES(RadioMessageP	MessPtr, SLong	number)
{
	RadioOnz*	phraseControl = PhraseFactors(PHRASE_FIFTIES);

	number += phraseControl->subFactor;
	number /= phraseControl->divFactor;
	if (!number)	number = 1;

	ComposeSample(MessPtr,PHRASE_FIFTIES+number);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NUMBER
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	NUM_0-NUM_29
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::NUMBER(RadioMessageP	MessPtr, int	theNumber)
{
	if (theNumber >= 0)
	{
		if (theNumber < 30)
			ComposeSample(MessPtr,PHRASE_NUM_0+theNumber);
		else
			FIFTIES(MessPtr,theNumber);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SQUADNUMBERSHORT
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SQUADNUMBERSHORT(RadioMessageP	MessPtr, ItemBasePtr	ac)
{
//Dead	ComposeSample(MessPtr,PHRASE_NUMBER+SquadronSectionNumber(ac));
	ComposeSample(MessPtr,SquadronNumber(MessPtr,ac));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TENS
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TENS(RadioMessageP	MessPtr,SLong	number)
{
	number /= 10;
	number *= 10;

	NUMBER(MessPtr,number);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		THOUSANDUNITS
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::THOUSANDUNITS(RadioMessageP	MessPtr)
{
	if (Save_Data.gamedifficulty [GD_UNITS])
		ComposeSample(MessPtr,PHRASE_THOUSANDMETRES);
	else
		ComposeSample(MessPtr,PHRASE_THOUSANDFEET);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VOLUMEUNITS
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	LITRES|GALLONS
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::VOLUMEUNITS(RadioMessageP	MessPtr)
{
//DEADCODE RJS 5/5/00 	if (Save_Data.gamedifficulty [GD_UNITS])
//DEADCODE RJS 5/5/00 		ComposeSample(MessPtr,PHRASE_LITRES);
//DEADCODE RJS 5/5/00 	else
//DEADCODE RJS 5/5/00 		ComposeSample(MessPtr,PHRASE_GALLONS);
#pragma warnmsg("Litres and gallons!!!")
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GROUNDCONTROLLERLW
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	GROUNDCONTROLLERLW00 -GROUNDCONTROLLERLW0x
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::GROUNDCONTROLLERLW(RadioMessageP	MessPtr)
{
	ComposeSample(MessPtr,PHRASE_GROUNDCONTROLLERLW+phrase_groundcontroller);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GROUNDCONTROLLERRAF
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	GROUNDCONTROLLERRAF00- GROUNDCONTROLLERRAF0x
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::GROUNDCONTROLLERRAF(RadioMessageP	MessPtr)
{
	ComposeSample(MessPtr,PHRASE_GROUNDCONTROLLERRAF+phrase_groundcontroller);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GFIGHTERS
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	CALLEE_FIGHTERS00 - CALLEE_FIGHTERS50
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLEE_GFIGHTERS(RadioMessageP	MessPtr)
{
	ComposeSample(MessPtr,PHRASE_CALLEE_GFIGHTERS+SquadronName(*MessPtr->callee));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ONE_AIRCRAFT_EXCLAIM
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	SPITFIRE1AEXCLAIM - DO17EXCLAIM
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ONE_AIRCRAFT_EXCLAIM(RadioMessageP	MessPtr)
{
	ComposeSample(MessPtr,PHRASE_ONE_AIRCRAFT_EXCLAIM+AircraftType(MessPtr,*MessPtr->target));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PLACENAMES
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	More specific placename function,
//				if fails, calls the vague areaname function...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::PLACENAMES(RadioMessageP	MessPtr, ItemPtr	theItem, bool sayRange)
{
	SLong	uid,direction,range;
	SLong	placephrase;

	if (theItem)
	{
		uid = theItem->SGT;
		if (!uid)
			uid = theItem->uniqueID.count;
	}
	else
		uid = MessPtr->TargetStuff.targetname;

// Get uid-band to work out which phrase table we want to use...

	placephrase = GetUIDPhrase(uid);
	if (placephrase)
		ComposeSample(MessPtr,placephrase);
	else
		AREANAMES(MessPtr,theItem,sayRange);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AREANAMES
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	Vague area name function, with bearings...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::AREANAMES(RadioMessageP	MessPtr, ItemPtr	theItem, bool sayRange)
{
	SLong	uid,direction,range;
	SLong	placephrase;
	bool	smallunits=true;

	if (theItem)
		GetPlaceDesc(theItem->World,uid,direction,range);
	else
	{
		uid = MessPtr->TargetStuff.targetname;
		direction = MessPtr->TargetStuff.targetdirection;
		range = MessPtr->TargetStuff.targetheight;
	}

// Get uid-band to work out which phrase table we want to use...

	placephrase = GetUIDPhrase(uid);

	MessPtr->distance = range;
	MessPtr->heading = direction;
	if (sayRange)
	{
		if (MessPtr->distance >= 200000)
		{
			smallunits = false;
			LargeRanges(MessPtr);
		}
		else
			SmallRanges(MessPtr,smallunits);								//RJS 22Aug00

		DISTUNITS(MessPtr,smallunits);
	}
	TRG_HDGCARDINAL(MessPtr);

	ComposeSample(MessPtr,placephrase);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_RELHEIGHT
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	BELOW|ABOVE
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_RELHEIGHT(RadioMessageP	MessPtr)
{
	if (MessPtr->target && MessPtr->callee)
	{
		SLong	rheights = MessPtr->target->World.Y - MessPtr->callee->World.Y;

		if (rheights > 0)
			ComposeSample(MessPtr,PHRASE_ABOVE);
		else
			ComposeSample(MessPtr,PHRASE_BELOW);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HDGOCLOCK
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	HDGO_000- HDGO_330
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::HdgOClock(RadioMessageP	MessPtr)
{
	if (MessPtr->InitROL())
	{
		RadioOnz*	phraseControl = PhraseFactors(PHRASE_HDGOCLOCK);
		UWord		relbearing = UWord(MessPtr->bearing);
		SLong		newphrase = PHRASE_HDGOCLOCK;

		relbearing -= UWord(MessPtr->callee->hdg);
		relbearing += phraseControl->subFactor;
		relbearing /= phraseControl->divFactor;

		if (!relbearing)	relbearing = 1;
	
		newphrase += relbearing;
		if (	(	(newphrase == PHRASE_HDGO_000)
				||	(newphrase == PHRASE_HDGO_360))
			&&	MessPtr->Random(1)					)
			newphrase = PHRASE_POSAHEAD;

		ComposeSample(MessPtr,newphrase);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_DESC_ESTIMATE
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_DESC_ESTIMATE(RadioMessageP	MessPtr)
{
	SLong	forcesize = GetForceSize(MessPtr);

	if (forcesize > 1)													//RJS 18Sep00
	{
		SLong	thePhrase;									//RJS 20Oct00
	
		if (forcesize < 20)
			thePhrase = PHRASE_GAGGLEOF;
		else
			thePhrase = PHRASE_HELLUVAALOT;

		ComposeSample(MessPtr,thePhrase);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		USER_DEFINED
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::USER_DEFINED(RadioMessageP	MessPtr)
{
	ULong	messno = 8 * _DPlay.GetPlayerNumber(MessPtr->caller->uniqueID.count);

	messno += MessPtr->TargetStuff.usermessage;
	messno++;

	ComposeSample(MessPtr,PHRASE_USER_DEFINED+messno);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FIGHTERSABOVE
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	MANYSNAPPERSABOVE| WATCHSNAPPERSABOVE| WATCHTOP| BF109ABOVE| FIGHTERESCORTABOVE
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::FIGHTERSABOVE(RadioMessageP	MessPtr)
{
	UWord	rand = MessPtr->Random(3);
	SLong	phrase = PHRASE_NULL;										//RJS 20Oct00

	switch (rand)
	{
	case 7:
	case 0:
		phrase = PHRASE_MANYSNAPPERSABOVE;
	break;
	case 1:
		phrase = PHRASE_WATCHSNAPPERSABOVE;
	break;
	case 5:
	case 2:
		phrase = PHRASE_WATCHTOP;
	break;
	case 3:
		phrase = PHRASE_BF109ABOVE;
	break;
	case 6:
	case 4:
		phrase = PHRASE_FIGHTERESCORTABOVE;
	break;
	}

	ComposeSample(MessPtr,phrase);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WATCHFORESCORT
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::WATCHFORESCORT(RadioMessageP	MessPtr)
{
	UWord	rand = MessPtr->Random(2);
	SLong	phrase = PHRASE_NULL;										//RJS 20Oct00

	switch (rand)
	{
	case 0:
		phrase = PHRASE_WATCHFORSNAPPERS;
	break;
	case 1:
		phrase = PHRASE_WATCHFORESCORT0;
	break;
	case 2:
		phrase = PHRASE_WATCHFORESCORT1;
	break;
	case 3:
		phrase = PHRASE_WATCHFORESCORT2;
	break;
	}

	ComposeSample(MessPtr,phrase);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GUSTTYPE
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	GUSTLIGHT| GUSTMOD| GUSTSEVERE
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::GUSTTYPE(RadioMessageP	MessPtr)
{
	SLong magnitude = MissManCampSky().MaxMagnitude;

	//assume magnitude is 0...6
	magnitude = (2 * magnitude)/6;		//scale down to 3 possible types...
				
	ComposeSample(MessPtr,PHRASE_GUSTLIGHT+magnitude);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BANDITSEX
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::BANDITSEX(RadioMessageP	MessPtr)
{
//		BANDITSEXCLAIM| FIGHTERS| ENEMYBANDITS| ENEMYFIGHTERSEX
	UWord	rand = MessPtr->Random(2);

	switch (rand)
	{
	case 0:
		ComposeSample(MessPtr,PHRASE_FIGHTERS);
	break;
	case 1:
		ComposeSample(MessPtr,PHRASE_BANDITSEXCLAIM);
	break;
	case 2:
		ComposeSample(MessPtr,PHRASE_ENEMYBANDITS);
	break;
	case 3:
		ComposeSample(MessPtr,PHRASE_ENEMYFIGHTERSEX);
	break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLER_GSECTIONRAF
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLER_GSECTIONRAF(RadioMessageP	MessPtr)
{
	SUBJECT_GSECTIONRAF(MessPtr,*MessPtr->caller);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BEARINGS
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	W_BEARING + DIGITS3
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::BEARINGS(RadioMessageP	MessPtr)
{
	ComposeSample(MessPtr,PHRASE_W_BEARING);
	BAREBEARINGS(MessPtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BAREBEARINGS
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	DIGITS3
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::BAREBEARINGS(RadioMessageP	MessPtr)
{
	if (MessPtr->InitROL())
	{
//DeadCode RJS 20Jan00 		UWord	relbearing = UWord(MessPtr->bearing);
//DeadCode RJS 19Jun00 		UWord	relbearing = UWord(MessPtr->heading);
		UWord	relbearing = UWord(MessPtr->bearing);
		SLong	therel = (relbearing * 360)>>16;

		ComposeDigitNumber(MessPtr,therel,3);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Height
//Author		Robert Slater
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::Height(RadioMessageP	MessPtr, RadioOnz*	phraseControl)
{
	SLong	height = MessPtr->realheight;

	height += phraseControl->subFactor;
	height /= phraseControl->divFactor;

	if (MessPtr->usedigits)
	{
		if (height < 1)
			height = 1;

		ComposeDigitNumber(MessPtr,height,2);
	}
	else
	{
		ComposeSample(MessPtr,PHRASE_SPACE);

		height += PHRASE_NUM_0;
		if (height < PHRASE_NUM_1)
			height = PHRASE_NUM_1;

		if (height > PHRASE_NUM_29)
			height = PHRASE_NUM_29;

		ComposeSample(MessPtr,height);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_HEIGHT
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_HEIGHT(RadioMessageP	MessPtr)
{
	if (MessPtr->target)// || MessPtr->TargetStuff.targetheight)		//RJS 29Sep00
	{
//DeadCode RJS 29Sep00 		if (MessPtr->TargetStuff.targetheight)
//DeadCode RJS 29Sep00 			MessPtr->realheight = MessPtr->TargetStuff.targetheight;
//DeadCode RJS 29Sep00 		else
			MessPtr->realheight = MessPtr->target->World.Y;

		if (Save_Data.gamedifficulty [GD_UNITS])
			ComposeSample(MessPtr,PHRASE_GEN_HEIGHTM);
		else
			ComposeSample(MessPtr,PHRASE_GEN_HEIGHTFT);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FUELLEVEL
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::FUELLEVEL(RadioMessageP	MessPtr)
{
	if (MessPtr->caller)
	{
//#pragma message(__HERE__"CRAIG:  Need to divide fuelcontent by fuelconsumption...")
 		AirStrucPtr	ac = (AirStrucPtr) MessPtr->caller;
 		ULong		fueltot = 0;
 		Float		fuel;
 
 		for(SWord i = 0; i < 4; i++)					
 			fueltot += ac->fly.fuel_content[i];
 
 		fuel = Float(fueltot);
		if (ac->nationality == NAT_RAF)
 			fuel *= 0.000002935;	//cg -> Imperial gallons			//CSB 03/03/00
		else
		{
 			fuel /= ac->classtype->fuelaboff;
			fuel /= 6000;	//cg -> Minutes
		}
 
		ComposeSample(MessPtr,PHRASE_SPACE);							//RJS 24Aug00

 		ComposeDigitNumber(MessPtr,SLong(fuel));

		ComposeSample(MessPtr,PHRASE_MINUTES);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_RANGE
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	W_RANGE +NUMBER+DISTUNITS
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_RANGE(RadioMessageP	MessPtr)
{
	if (MessPtr->InitROL())
	{
		bool	saidrange = false;
		bool	smallunits = true;

		if (!MessPtr->IsExcited)
		{
			ComposeSample(MessPtr,PHRASE_W_RANGE);
			saidrange = true;
		}

		if (!saidrange)
			ComposeSample(MessPtr,PHRASE_SPACE);

		if (MessPtr->distance >= 200000)
		{
			smallunits = false;
			LargeRanges(MessPtr);
		}
		else
			SmallRanges(MessPtr,smallunits);							//RJS 22Aug00

		DISTUNITS(MessPtr,smallunits);
	}	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LargeRanges
//Author		Robert Slater
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::LargeRanges(RadioMessageP	MessPtr)
{
	if (Save_Data.gamedifficulty [GD_UNITS])
		ComposeSample(MessPtr,PHRASE_RANGESKM);
	else
	{
		if (MessPtr->distance < 321860)			// 2 land miles
			MessPtr->distance = 321860;

		ComposeSample(MessPtr,PHRASE_RANGESIMP);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SmallRanges
//Author		Robert Slater
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SmallRanges(RadioMessageP	MessPtr, bool& smallunits)
{
	if (MessPtr->theVoice < VOICE_GROUND)
	{
		if (Save_Data.gamedifficulty [GD_UNITS])
			ComposeSample(MessPtr,PHRASE_SMLRANGESKM);
		else
			ComposeSample(MessPtr,PHRASE_SMLRANGESIMP);
	}
	else
	{
// clip range...
		MessPtr->distance = 200000;
		smallunits = false;

		LargeRanges(MessPtr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Gen_LargeRanges
//Author		Robert Slater
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::Gen_LargeRanges(RadioMessageP	MessPtr, RadioOnz*	phraseControl)
{
	SLong	dist = MessPtr->distance;

// The scale will give us a number between 1 and x
	dist += phraseControl->subFactor;
	dist /= phraseControl->divFactor;

// Since PHRASE_NUM_0 is already index 1, we want to append to that...
	dist += PHRASE_NUM_0;				
	if (dist > PHRASE_NUM_29)
	{
		dist -= PHRASE_NUM_0;									//RJS 05May00

		FIFTIES(MessPtr,dist);
	}
	else
		ComposeSample(MessPtr,dist);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Gen_SmallRanges
//Author		Robert Slater
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::Gen_SmallRanges(RadioMessageP	MessPtr, RadioOnz*	phraseControl)
{
	SLong	dist = MessPtr->distance;

	dist += phraseControl->subFactor;
	dist /= phraseControl->divFactor;
	if (!dist)	dist = 1;

	ComposeSample(MessPtr,PHRASE_RANGESCLOSE+dist);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NUM_VECTOR
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	W_VECTOR+DIGITS3
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::Num_Vector(RadioMessageP	MessPtr, ItemPtr	theItem)
{
	ComposeSample(MessPtr,PHRASE_W_VECTOR);

	if (MessPtr->InitROL())
	{
		UWord	relbearing = UWord(MessPtr->bearing);

		relbearing -= UWord(MessPtr->callee->hdg);

		SLong	therel = (relbearing * 360)>>16;

		ComposeDigitNumber(MessPtr,therel,3);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AIRFIELDSHORT
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::Airfields(RadioMessageP	MessPtr, ItemPtr airfielditem)
{
	if (airfielditem)
	{	
		SLong			uid = airfielditem->uniqueID.count;
		PhraseTables	newphrase = PhraseTables(GetUIDPhrase(uid));

		ComposeSample(MessPtr,newphrase);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_HDGCARDINAL
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_HDGCARDINAL(RadioMessageP	MessPtr)
{
	RadioOnz*	phraseControl = PhraseFactors(PHRASE_HDGCARDINAL);
//DeadCode RJS 9Jun00 	if ((MessPtr->TargetStuff.targetdirection & 0xFF00) == PHRASE_HDGCARDINAL)
//DeadCode RJS 9Jun00 	{
//DeadCode RJS 9Jun00 //		ComposeSample(MessPtr,PHRASE_HEADING);
//DeadCode RJS 9Jun00 		ComposeSample(MessPtr,MessPtr->TargetStuff.targetdirection);
//DeadCode RJS 9Jun00 	}
//DeadCode RJS 9Jun00 	else
	{
		if (MessPtr->InitROL())
		{
			UWord	relbearing = UWord(MessPtr->heading);

			relbearing += phraseControl->subFactor;
			relbearing /= phraseControl->divFactor;

			if (!relbearing)	relbearing = 1;
	
			ComposeSample(MessPtr,PHRASE_HDGCARDINAL+relbearing);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLER_HDGOCLOCK
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLER_HDGOCLOCK(RadioMessageP	MessPtr)
{
	mobileitem*	oldtarget = MessPtr->target;

	MessPtr->target = MessPtr->caller;

	HdgOClock(MessPtr);

	MessPtr->target = oldtarget;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_NUM_ESTIMATE
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_NUM_ESTIMATE(RadioMessageP	MessPtr)
{
	SLong	forcesize = GetForceSize(MessPtr);

//DeadCode RJS 05Sep00 	ComposeSample(MessPtr,PHRASE_PAUSE_SPACE);						//RJS 24Aug00
	ComposeSample(MessPtr,PHRASE_SPACE);						//RJS 05Sep00
	ForceSize(MessPtr,forcesize);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ForceSize
//Author		Robert Slater
//Date			Mon 24 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ForceSize(RadioMessageP	MessPtr, SLong	amount)
{
	if (amount < 5)
		NUMBER(MessPtr,amount);
	else
	{
		if (amount < 10)
			amount = 5;
		else
		{
			if (amount < 60)
				amount = 10;
			else
			{
				if (amount < 100)
				{
					amount /= 20;
					amount *= 20;
				}
			}
		}

		NUMBER(MessPtr,amount);
		ComposeSample(MessPtr,PHRASE_W_PLUS);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RAID_ID
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	(W_RAID + NUMBER)|(W_HOSTILE+NUMBER)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::RAID_ID(RadioMessageP	MessPtr)
{
	if (Todays_Packages.localplayer != NAT_RAF)					
		ComposeSample(MessPtr,PHRASE_W_RAID);
	else
		ComposeSample(MessPtr,PHRASE_W_HOSTILE);

	SayRaidID(MessPtr,MessPtr->target,MessPtr->caller);								//RJS 29Mar00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GSN
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLEE_GSN(RadioMessageP	MessPtr)
{
// Add this is??
	SUBJECT_GSN(MessPtr,*MessPtr->callee);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		USER_NAMES
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	PLAYERNAME1-PLAYERNAME8
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::USER_NAMES(RadioMessageP	MessPtr, ItemPtr	thePlayer)
{
	SLong	commsname = thePlayer->uniqueID.count;

	ComposeSample(MessPtr,PHRASE_PLAYERNAME1+_DPlay.GetPlayerNumber(commsname));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GSQUAD
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLEE_GSQUAD(RadioMessageP	MessPtr)
{
	SUBJECT_GSQUAD(MessPtr,*MessPtr->callee);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SUBJECT_GSQUAD
//Author		Robert Slater
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SUBJECT_GSQUAD(RadioMessageP	MessPtr, AirStrucPtr	ac)
{
	if (ac->nationality == NAT_RED)
		SUBJECT_GSQUADRAF(MessPtr,ac);
	else
		SUBJECT_GSQUADLW(MessPtr,ac);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLER_GL
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLER_GL(RadioMessageP	MessPtr)
{
	SUBJECT_GL(MessPtr,*MessPtr->caller);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLER_GSQUAD
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLER_GSQUAD(RadioMessageP	MessPtr)
{
	SUBJECT_GSQUAD(MessPtr,*MessPtr->caller);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLER_GSQUADRAF
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLER_GSQUADRAF(RadioMessageP	MessPtr)
{
	SUBJECT_GSQUADRAF(MessPtr,*MessPtr->caller);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLER_GWINGRAF
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLER_GWINGRAF(RadioMessageP	MessPtr)
{
	SUBJECT_GWINGRAF(MessPtr,*MessPtr->caller);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLER_GSN
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLER_GSN(RadioMessageP	MessPtr)
{
	SUBJECT_GSN(MessPtr,*MessPtr->caller);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SUBJECT_GSN
//Author		Robert Slater
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SUBJECT_GSN(RadioMessageP	MessPtr, AirStrucPtr	ac)
{
	SUBJECT_G(MessPtr,ac);
	SUBJECT_SN(MessPtr,ac);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLER_SN
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLER_SN(RadioMessageP	MessPtr)
{
	SUBJECT_SN(MessPtr,*MessPtr->caller);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		COMMSCALLER_SN
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	USER_NAMES
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::COMMSCALLER_SN(RadioMessageP	MessPtr)
{
	int	commsname = MessPtr->caller->uniqueID.count;

	ComposeSample(MessPtr,PHRASE_PLAYERNAME1+_DPlay.GetPlayerNumber(commsname));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_GSN
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	CALLER_GSN
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_GSN(RadioMessageP	MessPtr)
{
	SUBJECT_GSN(MessPtr,*MessPtr->target);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SUBJECT_SN
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	Section number (colour + number)
//				CALLEE_SN01 - CALLEE_SN45
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SUBJECT_SN(RadioMessageP	MessPtr, AirStrucPtr	ac)
{
	SLong		colour = SquadronSectionColour(ac)-1;	//1-5
	SLong		number = SquadronSectionNumber(ac);		//1-5
	SLong		position = (colour*5)+number;
	PhraseTables	phraseBase;									//RJS 16May00

	if (ac->nationality == NAT_RAF)
		phraseBase = PHRASE_CALLEE_RAFSN;
	else
		phraseBase = PHRASE_CALLEE_LWSN;

	phraseBase = PhraseTables(phraseBase + position);

	ComposeSample(MessPtr,phraseBase);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_SQUADNUMBERSHORT
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	Need a lookup table for the squadron number
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLEE_SQUADNUMBERSHORT(RadioMessageP	MessPtr)
{
	ComposeSample(MessPtr,SquadronNumber(MessPtr,*MessPtr->callee));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_SQUADNUMBERLONG
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLEE_SQUADNUMBERLONG(RadioMessageP	MessPtr)
{
	CALLEE_SQUADNUMBERSHORT(MessPtr);
	ComposeSample(MessPtr,PHRASE_W_SQUADRON);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SQUADNUMBERLONG
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SQUADNUMBERLONG(RadioMessageP	MessPtr)
{
	SQUADNUMBERSHORT(MessPtr,MessPtr->target);
	ComposeSample(MessPtr,PHRASE_W_SQUADRON);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PATROL_PLACE
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	TOWNBAND| CITYBAND |NAVIGATIONBAND| RAF_FIGHTERAFBAND
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::PATROL_PLACE(RadioMessageP	MessPtr)
{
//DEADCODE RJS 5/5/00 	ComposeSample(MessPtr,PHRASE_PATROL);
	AREANAMES(MessPtr,MessPtr->target);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_PLACE
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_PLACE(RadioMessageP	MessPtr)
{
	PLACENAMES(MessPtr,MessPtr->target);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		COMMSTARGET
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	USER_NAMES
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::COMMSTARGET(RadioMessageP	MessPtr)
{
	SLong	commsname = MessPtr->target->uniqueID.count;

	ComposeSample(MessPtr,PHRASE_PLAYERNAME1+_DPlay.GetPlayerNumber(commsname));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		COMMS
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	USER_NAMES
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::COMMS(RadioMessageP	MessPtr)
{
	COMMSCALLER_SN(MessPtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLER_PLACE
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLER_PLACE(RadioMessageP	MessPtr)
{
	PLACENAMES(MessPtr,MessPtr->caller);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_NEAR
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	(APPROACHING|HEADINGFOR|COMINGINOVER|OVER) + PLACENAMES
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_NEAR(RadioMessageP	MessPtr)
{
	UWord	rand = MessPtr->Random(2);
	SLong	composePhrase = PHRASE_OVER;								//RJS 20Oct00

	switch (rand)
	{
	case 0:
		composePhrase = PHRASE_APPROACHING;
		break;
	case 1:
		composePhrase = PHRASE_HEADINGFOR;
		break;
	case 2:
		composePhrase = PHRASE_COMINGINOVER;
		break;
	case 3:
		composePhrase = PHRASE_OVER;
		break;
	}

	ComposeSample(MessPtr,composePhrase);
	PLACENAMES(MessPtr,MessPtr->target);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_AC
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_AC(RadioMessageP	MessPtr)
{
	SLong forcesize = Art_Int.CountSquadronSize(*MessPtr->target);

	if (forcesize> 1)
		PLURAL_AIRCRAFT(MessPtr);	
	else
		ONE_AIRCRAFT(MessPtr);	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_1AC
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	ONE_AIRCRAFT
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_1AC(RadioMessageP	MessPtr)
{
	ONE_AIRCRAFT(MessPtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_BOMBERACS
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_BOMBERACS(RadioMessageP	MessPtr)
{
	SLong forcesize = Art_Int.CountSquadronSize(*MessPtr->target);		//RJS 16Oct00

	if (forcesize> 1)
		PLURAL_AIRCRAFT(MessPtr);	
	else
		ONE_AIRCRAFT(MessPtr);	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_BOMBER2ACS
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	Should use target2
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_BOMBER2ACS(RadioMessageP	MessPtr)
{
	SLong forcesize = Art_Int.CountSquadronSize(*MessPtr->target);

	if (forcesize> 1)
		PLURAL_AIRCRAFT(MessPtr);	
	else
		ONE_AIRCRAFT(MessPtr);	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_BOMBERAC
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_BOMBERAC(RadioMessageP	MessPtr)
{
	SLong forcesize = Art_Int.CountSquadronSize(*MessPtr->target);

	if (forcesize> 1)
		PLURAL_AIRCRAFT(MessPtr);	
	else
		ONE_AIRCRAFT(MessPtr);	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SURFACEWINDBEARINGNO
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SURFACEWINDBEARINGNO(RadioMessageP	MessPtr)
{
	ComposeSample(MessPtr,PHRASE_W_BEARING);
	WindBearingNo(MessPtr,false);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ALTWINDBEARINGNO
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ALTWINDBEARINGNO(RadioMessageP	MessPtr)
{
	ComposeSample(MessPtr,PHRASE_W_BEARING);
	WindBearingNo(MessPtr,true);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WindBearingNo
//Author		Robert Slater
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::WindBearingNo(RadioMessageP	MessPtr, bool	altitude)
{
	ULong	theBearing;

	if (altitude)
	{
		useAltitude = true;
		theBearing = UWord(MissManCampSky().diralt);
	}
	else
		theBearing = UWord(MissManCampSky().dir0);

	ComposeDigitNumber(MessPtr,SLong(theBearing),3);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WINDSPEED
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::WINDSPEED(RadioMessageP	MessPtr)
{
	//Knots...
	SLong	windSpeed;

	if (useAltitude)
		windSpeed = UWord(MissManCampSky().windalt);
	else
		windSpeed = UWord(MissManCampSky().wind0);

	ComposeDigitNumber(MessPtr,windSpeed,3);
//??	ComposeSample(MessPtr,PHRASE_KNOTS);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FIGHTERSCLOSE
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	MANYSNAPPERS| WATCHSNAPPERS| WATCHESCORT| BF109ESCORT| FIGHTERESCORTINVICINITY
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::FIGHTERSCLOSE(RadioMessageP	MessPtr)
{
/*	UWord	rand = MessPtr->Random(3);
	int		composeSample;

	switch (rand)
	{
		case 0:
		case 1:
			composeSample = PHRASE_MANYSNAPPERS;
			break;
		case 2:
		case 3:
			composeSample = PHRASE_WATCHSNAPPERS;
			break;
		case 4:
		case 5:
			composeSample = PHRASE_WATCHESCORT;
			break;
		case 6:
			composeSample = PHRASE_BF109ESCORT;
			break;
		case 7:
			composeSample = PHRASE_FIGHTERESCORTINVICINITY;
			break;
	}

	ComposeSample(MessPtr,composeSample);*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HEIGHTUNITS
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::HEIGHTUNITS(RadioMessageP	MessPtr)
{
/*	if (Save_Data.gamedifficulty [GD_UNITS])
		ComposeSample(MessPtr,PHRASE_METRES);
	else
		ComposeSample(MessPtr,PHRASE_FEET);*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_ANGELS
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_ANGELS(RadioMessageP	MessPtr)
{
	MessPtr->usedigits = true;

	ComposeSample(MessPtr,PHRASE_W_ANGELS);								//RJS 25Aug00
	TRG_HEIGHT(MessPtr);												//RJS 25Aug00

	MessPtr->usedigits = false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MY_HDGCARDINAL
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::MY_HDGCARDINAL(RadioMessageP	MessPtr)
{
	_Error.EmitSysErr("Unused phrase!");

//		HDGCARDINAL
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_RELCARDINAL
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_RELCARDINAL(RadioMessageP	MessPtr)
{
	_Error.EmitSysErr("Unused phrase!");

//	HDGCARDINAL
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MY_RELCARDINAL
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::MY_RELCARDINAL(RadioMessageP	MessPtr)
{
	_Error.EmitSysErr("Unused phrase!");

//		HDGCARDINAL
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NUM_HDGOCLOCK
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::NUM_HDGOCLOCK(RadioMessageP	MessPtr)
{
	_Error.EmitSysErr("Unused phrase!");
//			HDGOCLOCK
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GS
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLEE_GS(RadioMessageP	MessPtr)
{
	SUBJECT_G(MessPtr,*MessPtr->callee);
	CALLEE_S(MessPtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_GL
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_GL(RadioMessageP	MessPtr)
{
	_Error.EmitSysErr("Unused phrase!");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLER_NEAR
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	(APPROACHING |HEADINGFOR|COMINGINOVER|OVER) + PLACENAMES
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLER_NEAR(RadioMessageP	MessPtr)
{
	UWord	rand = MessPtr->Random(2);
	SLong	composePhrase = PHRASE_OVER;								//RJS 20Oct00

	switch (rand)
	{
	case 0:
		composePhrase = PHRASE_APPROACHING;
		break;
	case 1:
		composePhrase = PHRASE_HEADINGFOR;
		break;
	case 2:
		composePhrase = PHRASE_COMINGINOVER;
		break;
	case 3:
		composePhrase = PHRASE_OVER;
		break;
	}

	ComposeSample(MessPtr,composePhrase);
	PLACENAMES(MessPtr,MessPtr->caller);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_MANYAC
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_MANYAC(RadioMessageP	MessPtr)
{
	PLURAL_AIRCRAFT(MessPtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_BOMBER2AC
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	Should use target2 instead
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_BOMBER2AC(RadioMessageP	MessPtr)
{
	SLong forcesize = Art_Int.CountSquadronSize(*MessPtr->target);

	if (forcesize> 1)
		PLURAL_AIRCRAFT(MessPtr);	
	else
		ONE_AIRCRAFT(MessPtr);	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FIGHTERESCORT
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	FIGHTERSABOVE|FIGHTERSCLOSE
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::FIGHTERESCORT(RadioMessageP	MessPtr)
{
//DeadCode RJS 20Oct00 	UWord	rand = MessPtr->Random(1);

/*	if (rand)*/
		ComposeSample(MessPtr,PHRASE_LWFIGHTERSABOVE);
/*	else
		ComposeSample(MessPtr,PHRASE_FIGHTERSCLOSE);*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_SPEED
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_SPEED(RadioMessageP	MessPtr)
{
	_Error.EmitSysErr("Unused phrase!");
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TRG_VECTOR
//Author		Robert Slater
//Date			Tue 18 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::TRG_VECTOR(RadioMessageP	MessPtr)
{
	Num_Vector(MessPtr,MessPtr->target);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GWINGRAF
//Author		Robert Slater
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLEE_GWINGRAF(RadioMessageP	MessPtr)
{
	SUBJECT_GWINGRAF(MessPtr,*MessPtr->callee);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GSQUADRAF
//Author		Robert Slater
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLEE_GSQUADRAF(RadioMessageP	MessPtr)
{
	SUBJECT_GSQUADRAF(MessPtr,*MessPtr->callee);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GSECTIONRAF
//Author		Robert Slater
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLEE_GSECTIONRAF(RadioMessageP	MessPtr)
{
	SUBJECT_GSECTIONRAF(MessPtr,*MessPtr->callee);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CALLEE_GL
//Author		Robert Slater
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::CALLEE_GL(RadioMessageP	MessPtr)
{
	SUBJECT_GL(MessPtr,*MessPtr->callee);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPlaceDesc
//Author		Robert Slater
//Date			Tue 29 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::GetPlaceDesc(Coords3D& pos, SLong& uid, SLong& dir, SLong& range)
{
	ItemPtr	theTarget;
	dir = range = 0;

	uid = SLong(GetPlaceUID(pos));

	theTarget = Persons2::ConvertPtrUID(UniqueID(uid));
	if (theTarget)
	{
		SLong	dx = pos.X-theTarget->World.X;
		SLong	dy = pos.Y-theTarget->World.Y;
		SLong	dz = pos.Z-theTarget->World.Z;
		Float	fdx = Float(dx);
		Float	fdy = Float(dy);
		Float	fdz = Float(dz);

		fastMath.FloatToInt(&range,fastMath.FastSqrt(float((fdx*fdx)+(fdy*fdy)+(fdz*fdz))));

		dir = Math_Lib.arctan(dx,dz);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPlaceUID
//Author		Robert Slater
//Date			Tue 29 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord	RadioChatter::GetPlaceUID(Coords3D& pos)
{
	fileblock fb( FIL_CLOSEST_UID, Grid_Base::makeGridAt );
	Grid_Word* uidgrid = (Grid_Word*) fb.getdata();

	if (	pos.X < 0 || 				//JON 3Nov00
			pos.Z < 0 || 
			pos.X > LandScape._blockWidth*(639-64)	||
			pos.Z > LandScape._blockWidth*(639-64)	) // off the nearest grid
	{
		return UID_EnglishChannel;
	} else
	{
		return uidgrid->getWorld(pos.X,pos.Z);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPlaceBase
//Author		Robert Slater
//Date			Tue 29 Feb 2000
//
//Description
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	RadioChatter::GetPlaceBase(SLong	uidbase)
{
	SLong	phrase=0;

	switch (uidbase)
	{
	case CityBAND:
		phrase = PHRASE_CITYBAND;
	break;
	case TownBAND:
		phrase = PHRASE_TOWNBAND;
	break;
	case NavigationBAND:
		phrase = PHRASE_NAVIGATIONBAND;
	break;
	case SectorOpsBAND:
		phrase = PHRASE_SECTOROPSBAND;
	break;
	case LUF_FighterLF2BAND:
		phrase = PHRASE_LUF_FIGHTERLF2BAND;
	break;
	case RAF_FighterAFBAND:
		phrase = PHRASE_RAF_FIGHTERAFBAND;
	break;
	case RAF_BomberAFBAND:
		phrase = PHRASE_RAF_BOMBERAFBAND;
	break;
	case DocksBAND:
		phrase = PHRASE_DOCKSBAND;
	break;
	case CLRadarBAND:
		phrase = PHRASE_CLRADARBAND;
	break;
	case CHRadarBAND:
		phrase = PHRASE_CHRADARBAND;
	break;
	case BritBoatBAND:
		phrase = PHRASE_BRITBOATBAND;
	break;
	case PowerStationBAND:
		phrase = PHRASE_POWERSTATIONBAND;
	break;
	case IndustryBAND:
		phrase = PHRASE_INDUSTRYBAND;
	break;
	case AircraftFactoryBAND:
		phrase = PHRASE_AIRCRAFTFACTORYBAND;
	break;
	}

	return phrase;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetUIDPhrase
//Author		Robert Slater
//Date			Tue 29 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	RadioChatter::GetUIDPhrase(SLong uid)
{
	SLong		placephrase;
	SLong		uidband = Persons2::getbandfromUID(UniqueID(uid));
	RadioOnz*	phraseControl;

	placephrase = GetPlaceBase(uidband);
	if (placephrase)
	{
		phraseControl = PhraseFactors(placephrase);
		if (phraseControl->subFactor)
			placephrase += uid - phraseControl->subFactor;
		else
			placephrase = 0;								//there is nothing in this band!
	}
	return placephrase;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Subject_GUnit
//Author		Robert Slater
//Date			Wed 8 Mar 2000
//
//Description	CALLEE_GSQUADRAF | CALLEE_GGRUPPELW
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::Subject_GUnit(RadioMessageP	MessPtr, ItemPtr theItem)
{
	AirStrucPtr	ac = *theItem;
	SLong		phraseBase = 0;
	SLong		index = SquadronName(ac);

	if (ac->nationality == NAT_RED)
	{
		phraseBase = PHRASE_CALLEE_GSQUADRAF;
	}
	else														//RJS 25May00
 		phraseBase = PHRASE_CALLEE_GLW;							//RJS 25May00
 
	ComposeSample(MessPtr,phraseBase+index);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetForceSize
//Author		Robert Slater
//Date			Thu 9 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	RadioChatter::GetForceSize(RadioMessageP	MessPtr)
{
	SLong	forcesize = 0;
	if (MessPtr->TargetStuff.targetheight)
		forcesize = MessPtr->TargetStuff.targetheight;
	else
	{
		if (MessPtr->target->Status.size == AIRSTRUCSIZE)
		{
			AirStrucPtr	ac = (AirStrucPtr)MessPtr->target;

// Call Craig Stuff here...

			forcesize = Art_Int.CountFormationSize(ac);					//JIM 20/03/00
		}
	}


	return forcesize;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SayRaidID
//Author		Robert Slater
//Date			Thu 9 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SayRaidID(RadioMessageP	MessPtr, ItemPtr	theItem,ItemPtr	theOtherItem)
{
	SLong	raidid = 0;
	int		p,s;
	if (theItem==NULL || theItem->uniqueID.count<SagBAND || theItem->uniqueID.count>=RealAcBAND)
		theItem=theOtherItem;

	Todays_Packages.GetACSquadEntry(theItem->uniqueID.count,p,s);
 	raidid = Todays_Packages[p].GetRaidIndFromSquadEntry(s);

//DEADCODE RDH 07/04/00 #pragma warnmsg("Target and callee are valid, need to handle both 16;3;00")
	ComposeDigitNumber(MessPtr,Todays_Packages[p].raidnumentries[raidid].raidnum,3);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExpandLocation
//Author		Robert Slater
//Date			Thu 9 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ExpandLocation(PhraseBuffer&	phbuf, ULong locdesc)
{
	TargetIndexes	tstruc;
	ULong	uid = (locdesc&INT_UID_MASK)>>INT_UID_SHIFT;
	ULong	dir = (locdesc&INT_DIR_MASK)>>INT_DIR_SHIFT;
	ULong	rng = (locdesc&INT_RANGE_MASK)>>INT_RANGE_SHIFT;

	dir <<= 12;					// to 16-bits
	rng *= 100000;				// to cm

	tstruc.targetname = uid;
	tstruc.targetheight = rng;
	tstruc.targetdirection = dir;

	UWord	tmprand=0;
	ExpandMessage(phbuf,PHRASE_PATROL_PLACE,tmprand,tstruc,NULL,NULL,NULL);
}

void	RadioChatter::GetLocationString(CString&	placestring, ULong	locdesc)
{
	PhraseBuffer	phbuf;
	
	placestring = "";

	ExpandLocation(phbuf,locdesc);

	_MsgBuffer.PhraseToString(placestring,phbuf);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MessageFinished
//Author		Robert Slater
//Date			Tue 28 Mar 2000
//
//Description	Non-vocal messages get 2.5 secs of fake play time...
//				Map-screen time intervals are 1 sec.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	RadioChatter::MessageFinished()
{
	bool	noMessage = true;
	RadioMessageP	MessPtr = RootMessPtr;
	if (MessPtr)
	{
		if (MessPtr->isAudio)
		{
			if (MessPtr->PlayQueue)
			{
				if (_Miles.SampleFinished(MessPtr->PlayQueue,false))
				{
					MessPtr->PlayQueue = NULL;

					delete[]MessPtr->sampleptr;
					delete MessPtr;

					MessPtr = RootMessPtr = NULL;
				}
				else
					noMessage = false;
			}
			else
			{
				if (MessPtr->sampleptr)									//RJS 5Sep00
					delete[]MessPtr->sampleptr;

				delete MessPtr;
				MessPtr = RootMessPtr = NULL;
			}
		}
		else
		{
// we only come in here every second
			MessPtr->fakeplaytime -= 100;								//RJS 5Sep00
			if (MessPtr->fakeplaytime <= 0)
			{
				MessPtr->fakeplaytime = 0;

				RootMessPtr = NULL;
				if (MessPtr->sampleptr)
					delete[]MessPtr->sampleptr;
				delete MessPtr;
			}
			else
				noMessage = false;
		}
	}

	return noMessage;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayMessage
//Author		Robert Slater
//Date			Tue 28 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::PlayMessage(UWord*	phrase_buffer, VoiceType	theVoice)
{
	TargetIndexes	dummyTarget;

	RadioMessageP	MessPtr = CreateMessage(NULL,
											NULL,
											NULL,
											0,
											dummyTarget,
											theVoice,
											NULL,
											127,
											VOXSTATE_NORMAL);

	if (MessPtr)
	{
		int	thePhrase = *phrase_buffer++;

//Turn phrases into samples
		lastPhrase = PHRASE_NULL;
		while (thePhrase)
		{
			SpeakPhrase(MessPtr,thePhrase);

			lastPhrase = PhraseTables(thePhrase);
			thePhrase = *phrase_buffer++;
		}

//Concatenate samples
		if (!MessPtr->BuildMessageAsSamples())
		{
			// Set up a fake one...
			timesincelast = 0;
			timesincestart = 0;
		}
		else
		{
//Let's hear it...
			if (!MessPtr->PlayQueue)
				MessPtr->PlayQueue = _Miles.PlaySampleRadio(MessPtr->sampleptr,MessPtr->samplesize,MessPtr->VolScale,MessPtr->theFrequency,8);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpeakPhrase
//Author		Robert Slater
//Date			Tue 28 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::SpeakPhrase(RadioMessageP	MessPtr,int	phrase)
{
	if (MessPtr->isAudio)
	{
		RadioSampleRec*	RSamplePtr;
		int				ptype = phrase & 0xFF00;
		int				StartOffset;
		int				SampleSize;

//DeadCode RJS 21Aug00 		if (ptype == PHRASE_VOICE2)									//RJS 10May00
//DeadCode RJS 21Aug00 			MessPtr->theVoice = VOICE_VOICE2;						//RJS 10May00

		RSamplePtr = LoadSample(MessPtr,phrase,StartOffset,SampleSize);
		if (RSamplePtr)
		{
			if (	(ptype == PHRASE_PUNCTUATION)
				|| ((lastPhrase & 0xFF00) == PHRASE_PUNCTUATION)
				||	(MessPtr->theVoice == VOICE_FEMALE)	)
				MessPtr->phraselist[MessPtr->nophrases].noCrossFade = 1;
			else
				MessPtr->phraselist[MessPtr->nophrases].noCrossFade = 0;

			MessPtr->AddSample(RSamplePtr->dataptr,StartOffset,SampleSize);
		}
	}
	else
		MessPtr->AddPhrase(phrase);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessVoice
//Author		Robert Slater
//Date			Wed 16 Aug 2000
//
//Description	Checks to see if the voice you have asked for is valid
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ProcessVoice(const MESSAGE_STRUC&	msg)
{
	if (!theScripts.voiceBlock)
	{
		fileblock	*theblock = new fileblock (FIL_RCHAT_SCRIPT_VOICES);
		if (theblock)
		{
			theScripts.voiceBlock = theblock;
			theScripts.voicePtr = ULongP(getdata(theblock));
		}
	}
	
	if (msg.GetScript() && (msg.GetScript() & 0xFFFF0000))				//RJS 15Sep00
	{
		ULong	voxMask = theScripts.voicePtr[(msg.GetScript() & 0xFFFF)-1];	//RJS 15Sep00
		if ((voxMask & (1<<VOICE_VOICE2))!=0)							//RJS 6Sep00
		{																//RJS 6Sep00
			msg.voiceindex = VOICE_VOICE2;								//RJS 6Sep00
			if (msg.caller && (msg.caller->nationality != NAT_RAF))		//RJS 3Oct00
				msg.voiceindex = VOICE_LWVOICE2;						//RJS 6Sep00
																		//RJS 6Sep00
			msg.voxstate = VOXSTATE_NORMAL;								//RJS 6Sep00
		}																//RJS 6Sep00
		else
		{
			if ((voxMask & (1<<(msg.voiceindex+msg.voxstate))) == 0)
			{
				VoiceType	realVoice = VoiceType((voxMask>>27)&0xFF);	//RJS 11Oct00
// Whoever triggered this message needs a slap!... 
// ... a radio message is being spoken in the wrong voice... check the "call stack" to
// see who is the offender! Only get Rob if you are completely confused.
				if (in3D)
				{
#ifdef	_VOICE_DEBUG_
					INT3;
#endif
					if ((ThrowOutMask[msg.voiceindex+msg.voxstate] & (1<<realVoice)) == 0)
						msg.SetScript(0);								//RJS 11Oct00
				}

				msg.voxstate = VOXSTATE_NORMAL;							//RJS 11Oct00
				msg.voiceindex = realVoice;								//RJS 11Oct00
			}
		}
	}
}

VoiceType	RadioChatter::GetVoice(const ScriptTables&	theScript, const VoiceType& theVoice)
{
	VoiceType	newVoice = theVoice;

	if (newVoice != VOICE_SILENT)										//RJS 26Oct00
	{
		if (!theScripts.voiceBlock)
		{
			fileblock	*theblock = new fileblock (FIL_RCHAT_SCRIPT_VOICES);
			if (theblock)
			{
				theScripts.voiceBlock = theblock;
				theScripts.voicePtr = ULongP(getdata(theblock));
			}
		}

		if (theScript && (theScript & 0xFFFF0000))
		{
			ULong	voxMask = theScripts.voicePtr[(theScript & 0xFFFF)-1];
			if ((voxMask & (1<<theVoice)) == 0)
				newVoice = VoiceType((voxMask>>27)&0xFF);
		}
	}

	return newVoice;
}

void	RadioChatter::Init()
{
	if (!File_Man.existnumberedfile(FIL_RCHAT_PUNCTUATION))
		samplesAllowed = false;

	_Miles.ChatterStatus(samplesAllowed);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScanScript
//Author		Richard Jones
//Date			Sun 4 Sep 1988
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ScanScript(const MESSAGE_STRUC&	radiomessage)
{
//DeadCode RJS 3Oct00 	PhraseBuffer	fbuff;
	int				Scriptno = radiomessage.GetScript();				//RJS 15Sep00

	lockout = true;					
	RadioMessageP	OldRootMessPtr = RootMessPtr;
	RootMessPtr = NULL;
	RadioMessageP	MessPtr = CreateMessage((mobileitem*)radiomessage.caller,
											(mobileitem*)radiomessage.target,
											(mobileitem*)radiomessage.callee,
											radiomessage.randomno,
											radiomessage.targetinfo,
											radiomessage.voiceindex,
											NULL,//&fbuff,				//RJS 3Oct00
											128,
											radiomessage.voxstate);

	if (MessPtr)
	{
		UWordP			ScriptPtr;
		PhraseTables	ThePhrase;
		ULong			nochoices = Scriptno & 0xFFFF0000;

		if (nochoices)
		{
			MessPtr->isAudio = TRUE;									//RJS 3Oct00

			Scriptno &= 0xFFFF;
			ScriptPtr = GetScript(Scriptno,MessPtr,ThePhrase);
			if (ScriptPtr)
			{
				ThePhrase = (PhraseTables) *ScriptPtr;
				while (ThePhrase != PHRASE_NULL)
				{
					ComposeFakeSample(MessPtr,ThePhrase);
					if (ThePhrase)
					{
						ScriptPtr++;

						lastPhrase = ThePhrase;
						ThePhrase = PhraseTables(*ScriptPtr);
					}
					else
						radiomessage.SetScript(0);
				}
			}
			else
			{
				ComposeFakeSample(MessPtr,ThePhrase);
				if (!ThePhrase)
					radiomessage.SetScript(0);
			}
		}
		else
		{
			lastPhrase = PhraseTables(Scriptno);
			ComposeFakeSample(MessPtr,lastPhrase);
			if (!lastPhrase)
				radiomessage.SetScript(0);
		}

		delete MessPtr;
	}

	RootMessPtr = OldRootMessPtr;
	lockout = false;			
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ComposeFakeSample
//Author		Richard Jones
//Date			Sun 4 Sep 1988
//
//Description	Checks to see if we are trying to look at a NULL pointer
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	RadioChatter::ComposeFakeSample(RadioMessageP	MessPtr, PhraseTables& phrase)
{
	if (phrase != PHRASE_NULL)
	{
		int			ptype = int(phrase) & 0xFF00;
		int			pelement = int(phrase) & 0xFF;

		if (!pelement)
		{
			switch (ptype)
			{
			case PHRASE_CALLEE_GFIGHTERS:
			case PHRASE_CALLEE_GFLIGHTRAF:
			case PHRASE_CALLEE_GL_RAF:
			case PHRASE_CALLEE_GSECTIONRAF:
			case PHRASE_CALLEE_GSN_RAF:
			case PHRASE_CALLEE_GSQUADRAF:
			case PHRASE_CALLEE_GWINGRAF:
			case PHRASE_CALLEE_SN:
			case PHRASE_CALLEE_SQUADNUMBERLONG:
			case PHRASE_CALLEE_SQUADNUMBERSHORT:
			case PHRASE_CALLEE_GLW:
			case PHRASE_CALLEE_GUNIT:
			{
				if (!MessPtr->callee)
				{
#ifdef	_SCAN_SCRIPT_
					INT3;
#endif
					phrase = PHRASE_NULL;						//RJS 3Oct00
				}
			}
			break;
			case PHRASE_CALLER_GFLIGHTRAF:
			case PHRASE_CALLER_GL_RAF:
			case PHRASE_CALLER_GSECTIONRAF:
			case PHRASE_CALLER_GSQUADRAF:
			case PHRASE_CALLER_GWINGRAF:
			case PHRASE_CALLER_HDGOCLOCK:
			case PHRASE_CALLER_SN:
			case PHRASE_CALLER_AIRFIELD:
			case PHRASE_CALLER_GUNIT:
			case PHRASE_ONLYRAID_ID:
			{
				if (!MessPtr->caller)
				{
#ifdef	_SCAN_SCRIPT_
					INT3;
#endif
					phrase = PHRASE_NULL;
				}
			}
			break;
			case PHRASE_AIRFIELDS:
			case PHRASE_RAF_AIRFIELDS:
			case PHRASE_LUF_FIGHTERLF2BAND:
			case PHRASE_PLURAL_AIRCRAFT_EXCLAIM:
			case PHRASE_SECTOROPSBAND:
			case PHRASE_TRG_ANGELS:
			case PHRASE_TRG_VECTOR:
			case PHRASE_ONE_AIRCRAFT:
			case PHRASE_ONE_AIRCRAFT_EXCLAIM:
			case PHRASE_PATROL_PLACE:
			case PHRASE_PLACENODIST:
			case PHRASE_PLACENAMES:
			case PHRASE_SQUADNUMBERLONG:
			case PHRASE_SUBJECT_SN:
			case PHRASE_TRG_AC:
//DeadCode RJS 16Oct00 			case PHRASE_TRG_BOMBER2ACS:
			case PHRASE_TRG_BOMBERACS:
			case PHRASE_TRG_DESC_ESTIMATE:
			case PHRASE_TRG_HDGCARDINAL:
			case PHRASE_HDGOCLOCK:
			case PHRASE_TRG_HDGOCLOCK:
			case PHRASE_TRG_HEIGHT:
			case PHRASE_TRG_NEAR:
			case PHRASE_TRG_PLACE:
			{
				if (!MessPtr->target)
				{
#ifdef	_SCAN_SCRIPT_
					INT3;
#endif
					phrase = PHRASE_NULL;
				}
			}
			break;
			case PHRASE_TRG_BOMBER2ACS:
			{
				if (!MessPtr->target2)
				{
#ifdef	_SCAN_SCRIPT_
					INT3;
#endif
					phrase = PHRASE_NULL;
				}
			}
			break;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessScript
//Author		Robert Slater
//Date			Fri 15 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	MESSAGE_STRUC::ProcessScript(int	scriptno)
{
#ifndef	NDEBUG
	_Radio.totmess++;
	messagecnt = _Radio.totmess;
#endif

	randomno = Math_Lib.rnd();

	ChooseScript(scriptno);
}
