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
//Filename       messengn.cpp
//System         
//Author         Robert Slater
//Date           Tue 26 Jan 1999
//Description    
//------------------------------------------------------------------------------

#include	"dosdefs.h"
#include	"worldinc.h"
#include	"rchatter.h"
#include	"messengn.h"
#include	"cstring.h"
#include	"overlay.h"

#ifndef	NDEBUG
//#define	_PRINTSTRING_
//#define	CHATTERTRACE
#endif

MessageBuffer	_MsgBuffer;

//DeadCode RJS 12Feb99 ULong	MessageBuffer::PhraseToIDS[]=
//DeadCode RJS 12Feb99 {
//DeadCode RJS 12Feb99 #include	"radtxt.g"
//DeadCode RJS 12Feb99 	-1
//DeadCode RJS 12Feb99 };

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetVoice
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
const MESSAGE_STRUC& MESSAGE_STRUC::SetVoice(const VoiceType& voice) const
{
	if (	(voice == VOICE_TOWER)								//RJS 10May00
		&&	(callee && (callee->nationality == NAT_LUF))	)	//RJS 10May00
		voiceindex = VOICE_LWTOWER;								//RJS 10May00
	else														//RJS 10May00
		voiceindex = voice;										//RJS 10May00

	return (*this);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDecision
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
const MESSAGE_STRUC& MESSAGE_STRUC::SetDecision(DecisionAI*	d) const
{
	decisionhandler = d;

	return (*this);
}

const	MESSAGE_STRUC&	MESSAGE_STRUC::SetScript(int	newscript) const
{
	ChooseScript(newscript);

	return (*this);
}
	
const MESSAGE_STRUC& MESSAGE_STRUC::SetCaller(MobileItemPtr	newitem) const
{
	caller = AirStrucPtr(newitem);

	return (*this);
}

const int&	MESSAGE_STRUC::GetScript() const
{
	return scriptno;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCaller
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode RJS 04Feb99 const MESSAGE_STRUC& MESSAGE_STRUC::SetCaller(Bool saythisis) const
//DeadCode RJS 04Feb99 {
//DeadCode RJS 04Feb99 	noCaller = saythisis;
//DeadCode RJS 04Feb99 
//DeadCode RJS 04Feb99 	return (*this);
//DeadCode RJS 04Feb99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetPriority
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
const MESSAGE_STRUC& MESSAGE_STRUC::SetPriority(MsgPriority	pri) const
{
	priority = pri;

	return (*this);
}



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Message buffer stuff.............


#ifdef	_PRINTSTRING_
	FILE*	debfp;
#endif


MessageBuffer::MessageBuffer()
{
	oldbuffer = NULL;
	newbuffer = NULL;

	lateststring = new CString;

	BufferInit();

#ifdef	_PRINTSTRING_
	debfp = fopen("radtest.txt","wt");
#endif
}

void	MessageBuffer::BufferInit()
{
	if (oldbuffer)
		delete []oldbuffer;

	oldbuffer = new MESSAGE_STRUC[OLDBUFFERSIZE];

	if (newbuffer)
		delete []newbuffer;

	newbuffer = new MESSAGE_STRUC[NEWBUFFERSIZE];

	oldbuffertop = OLDBUFFERSIZE-1;
	oldbufferbot = OLDBUFFERSIZE-1;

	newbuffertop = NEWBUFFERSIZE-1;
	newbufferbot = NEWBUFFERSIZE-1;

	thePlayer = 
		theOtherOne=NULL;

	thereIsANewMessage=false;
	nothingatall = false;				//RJS 01Apr99
	noBufferedMessages = 0;										//RJS 28May99

	*lateststring = "";											//RJS 14Jun99

#ifndef	NDEBUG
	_Radio.damageMessage = false;
#endif
}

MessageBuffer::~MessageBuffer()
{
	delete []oldbuffer;
	delete []newbuffer;

	oldbuffer = NULL;
	newbuffer = NULL;

	oldbuffertop = 0;
	oldbufferbot = 0;

	newbuffertop = 0;
	newbufferbot = 0;

	delete lateststring;										//RJS 15Jun99

#ifdef	_PRINTSTRING_
	fclose(debfp);
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToBuffer
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	MessageBuffer::AddToBuffer(const MESSAGE_STRUC&	msg)
{
	Bool 	retval;
	SLong	index,index2;
//DeadCode RJS 20Oct00 	Bool	playerRecipient = FALSE;
	Bool	throwAway;											//RJS 02May00

	if(!ShouldHearMsg(msg,throwAway))							//RJS 02May00
		return throwAway;										//RJS 02May00

	//Block messages to dead blokes
//DEADCODE CSB 07/03/00 	if (msg.callee && msg.callee->Status.deadtime)				//RJS 05May99
//DEADCODE CSB 07/03/00 		return TRUE;											//RJS 05May99

//DEADCODE CSB 07/03/00 	if (msg.caller)
//DEADCODE CSB 07/03/00 	{
//DEADCODE CSB 07/03/00 		if (msg.caller->nationality != Manual_Pilot.ControlledAC2->nationality)
//DEADCODE CSB 07/03/00 			return TRUE;
//DEADCODE CSB 07/03/00 
//DEADCODE CSB 07/03/00 		if (msg.caller->ai.radiosilent)
//DEADCODE CSB 07/03/00 		{
//DEADCODE CSB 07/03/00 			if (msg.caller->AcIsPlayer())						//RJS 24May99
//DEADCODE CSB 07/03/00 			{
//DEADCODE CSB 07/03/00 				MESSAGE_STRUC	tmpmsg(OLDSCRIPT_SILENCE,MSG_SILENCE,NULL,msg.caller,msg.caller);
//DEADCODE CSB 07/03/00 				_Radio.TriggerMsg(tmpmsg.SetVoice(VOICE_REST));
//DEADCODE CSB 07/03/00 			}
//DEADCODE CSB 07/03/00 
//DEADCODE CSB 07/03/00 			return TRUE;									//RJS 24May99
//DEADCODE CSB 07/03/00 		}
//DEADCODE CSB 07/03/00 	}
//DEADCODE CSB 07/03/00 //DeadCode RJS 06Jul99 	else
//DEADCODE CSB 07/03/00 //DeadCode RJS 05Jul99 	{
//DEADCODE CSB 07/03/00 		if (msg.callee)
//DEADCODE CSB 07/03/00 		{
//DEADCODE CSB 07/03/00 			if (msg.callee->nationality != Manual_Pilot.ControlledAC2->nationality)
//DEADCODE CSB 07/03/00 				return TRUE;
//DEADCODE CSB 07/03/00 		}
//DEADCODE CSB 07/03/00 //DeadCode RJS 05Jul99 	}
//DEADCODE CSB 07/03/00 
//DEADCODE CSB 07/03/00 	if ((msg.callee==thePlayer) || (msg.callee==theOtherOne))	//RDH 17May99
//DEADCODE CSB 07/03/00 		playerRecipient = TRUE;									//RDH 17May99

	//Does this message already exist?...
	if(!msg.decisionhandler)											//CSB 07/03/00
	{																	//CSB 07/03/00
		for (index = 0; index < OLDBUFFERSIZE; index++)
		{
			if (	(oldbuffer[index].messagetype == msg.messagetype)
				&&	(oldbuffer[index].target == msg.target)				)
			{
				//is old repeatable?
				if (	(oldbuffer[index].visibility == VIS_3)			//RJS 01Apr99
					||	(oldbuffer[index].visibility == NOTVIS_1)
					||	(oldbuffer[index].visibility == VIS_1))
				{
	//Removed because it became annoying...							//RJS 02Jun99
	//DeadCode RJS 02Jun99 				if (!playerRecipient)							//RDH 17May99
	//DeadCode RJS 02Jun99 					return (FALSE);								//RDH 17May99
	//DeadCode RJS 02Jun99 				else											//RDH 17May99
						return (TRUE);								//RDH 17May99
				}
			}
		}

		for (index = 0; index < NEWBUFFERSIZE; index++)
		{
			if (	(newbuffer[index].messagetype == msg.messagetype)
				&&	(newbuffer[index].target == msg.target)				)
			{
				//is new repeatable?
				if (	(newbuffer[index].visibility == VIS_3)
					||	(newbuffer[index].visibility == NOTVIS_1)	)
				{
	//Removed because it became annoying...							//RJS 02Jun99
	//DeadCode RJS 02Jun99 				if (!playerRecipient)							//RDH 17May99
	//DeadCode RJS 02Jun99 					return (FALSE);								//RDH 17May99
	//DeadCode RJS 02Jun99 				else											//RDH 17May99
						return (TRUE);								//RDH 17May99
				}
			}
		}
	}
	else																//CSB 09/03/00
		msg.priority = PRI_MAX;											//CSB 09/03/00

//DeadCode PD 04Mar99 	//... or not in player group...
//DeadCode PD 04Mar99 	if (	(msg.caller != thePlayer)
//DeadCode PD 04Mar99 		||	(msg.callee != thePlayer)	)
//DeadCode PD 04Mar99 		return (FALSE);
//DEADCODE CSB 07/03/00 	if (!(msg.caller==thePlayer||msg.callee==thePlayer) &&
//DEADCODE CSB 07/03/00 		!(msg.caller==theOtherOne||msg.callee==theOtherOne))		//PD 04Mar99
//DEADCODE CSB 07/03/00 	{
//DEADCODE CSB 07/03/00 		if (!msg.blockchatter)									//RJS 06Jul99
//DEADCODE CSB 07/03/00 		{
//DEADCODE CSB 07/03/00 			AirStrucPtr	checkitem = msg.caller;						//AMM 24Jun99
//DEADCODE CSB 07/03/00 			if (	(msg.voiceindex != VOICE_REST)
//DEADCODE CSB 07/03/00 				&&	(msg.voiceindex != VOICE_PLAYER)	)
//DEADCODE CSB 07/03/00 				checkitem = msg.callee;								//AMM 24Jun99
//DEADCODE CSB 07/03/00 		
//DEADCODE CSB 07/03/00 			if (!checkitem)
//DEADCODE CSB 07/03/00 				return TRUE;
//DEADCODE CSB 07/03/00 
//DEADCODE CSB 07/03/00 			if (	checkitem->PlayerInGroup()
//DEADCODE CSB 07/03/00 				||	checkitem->PlayerInFlight()	)
//DEADCODE CSB 07/03/00 			{
//DEADCODE CSB 07/03/00 				//Overhears leader & fac/tac & dentist & tower...
//DEADCODE CSB 07/03/00 				if (checkitem->AcIsFlightLeader() || checkitem->AcIsGroupLeader())
//DEADCODE CSB 07/03/00 				{
//DEADCODE CSB 07/03/00 					if (noBufferedMessages > 8)
//DEADCODE CSB 07/03/00 						return FALSE;
//DEADCODE CSB 07/03/00 				}
//DEADCODE CSB 07/03/00 				else
//DEADCODE CSB 07/03/00 					return FALSE;
//DEADCODE CSB 07/03/00 			}
//DEADCODE CSB 07/03/00 			else
//DEADCODE CSB 07/03/00 				return FALSE;
//DEADCODE CSB 07/03/00 		}
//DEADCODE CSB 07/03/00 		else
//DEADCODE CSB 07/03/00 			return TRUE;										//RJS 06Jul99
//DEADCODE CSB 07/03/00 	}															//RJS 28May99

//	thereIsANewMessage=true;

#ifdef CHATTERTRACE
// defined in rchatter.h
	if (_Radio.damageMessage)
	{
		UWord cw=GETFPCW();
		::AfxTrace("BUFFERING: %08x\n",msg.messagecnt);
		SETFPCW(cw);
	}
#endif

	noBufferedMessages++;

	if (msg.priority >= PRI_MEDMAX)				//RJS 24Jun99
	{
		newbufferbot--;
		if (newbufferbot < 0)
			newbufferbot = NEWBUFFERSIZE-1;

		newbuffer[newbufferbot] = msg;
	}
	else
	{
		// Is this buffer full?
		if (	(newbufferbot == newbuffertop)
			&&	(newbuffer[newbufferbot].priority != GAP)	)
		{
			SLong	nogaps;

			if (msg.priority != PRI_LOW)
			{
				nogaps = RemoveGaps(newbuffer,newbuffertop,NEWBUFFERSIZE);
				if (nogaps == 0)
				{
					SLong	thisone = -1;

					for (index = newbuffertop; index < NEWBUFFERSIZE; index++)
					{
						if (newbuffer[index].priority == PRI_LOW)
						{
							thisone = index;
							break;
						}
					}

					if (thisone < 0)
					{
						for (index = 0; index < newbuffertop; index++)
						{
							if (newbuffer[index].priority == PRI_LOW)
							{
								thisone = index;
								break;
							}
						}
					}

					if (thisone > 0)
					{
						// Kill 1st low priority one found...

						newbuffer[thisone].priority = GAP;

						RemoveGaps(newbuffer,newbuffertop,NEWBUFFERSIZE);
					}
				}
			}
		}

		// Is this buffer still full?
		if (	(newbufferbot == newbuffertop)
			&&	(newbuffer[newbufferbot].priority != GAP)	)
			return(FALSE);

		newbuffer[newbuffertop] = msg;

		//is this right?....
		newbuffertop++;
		if (newbuffertop >= NEWBUFFERSIZE)
			newbuffertop = 0;
	}

	return (TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CurrMessage
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_STRUC*	MessageBuffer::CurrMessage()
{
	return &oldbuffer[oldbuffertop];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SayNextMessage
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	Called by _Radio... when playing one has finished
//
//
//		... also check to see if user response,
//			cos we don't want to display or play until we are told to
//
//Inputs		
//
//Returns		NULL			... if nothing to play.
//				messageptr
//
//------------------------------------------------------------------------------
MESSAGE_STRUC*	MessageBuffer::SayNextMessage(SLong&	frametime)
{
	MESSAGE_STRUC*	retptr = NULL;

	if ((newbuffertop == newbufferbot) && (newbuffer[newbufferbot].priority == GAP))
		return NULL;

	// Better pause...
	if (newbuffer[newbufferbot].timeout)
	{
		SLong	timeout = newbuffer[newbufferbot].timeout;
		timeout -= frametime;
		if ((timeout > 0) && !_Radio.View_Point->Accel())		//RJS 27May99
		{
			newbuffer[newbufferbot].timeout = timeout;					//RJS 13May99
			return NULL;
		}
		else
			newbuffer[newbufferbot].timeout = 0;
	}

	if (newbuffer[newbufferbot].priority > PRI_LOW)
		retptr = &newbuffer[newbufferbot];
	else
	{
		SLong	index;
		for (index=newbufferbot; index < NEWBUFFERSIZE; index++)
		{
			if (newbuffer[index].priority > PRI_LOW)
			{
				retptr = &newbuffer[index];
				break;
			}
		}

		if (!retptr)
		{
			for (index = 0; index < newbuffertop; index++)
			{
				if (newbuffer[index].priority > PRI_LOW)
				{
					retptr = &newbuffer[index];
					break;
				}
			}
		}

		if (!retptr)
		{
			if (newbuffer[newbufferbot].priority != GAP)		//RJS 30Apr99
				retptr = &newbuffer[newbufferbot];
			else
				return NULL;
		}
	}

//DeadCode DAW 25Jun99 //DeadCode RDH 30Apr99 //	if (retptr->visibility < NOTVIS_2)			//RJS 01Apr99
//DeadCode DAW 25Jun99 //DeadCode RDH 30Apr99 	{
//DeadCode DAW 25Jun99 	if (oldbuffer[oldbuffertop].visibility < NOTVIS_2)	   //RJS 01Apr99
//DeadCode DAW 25Jun99 	{
//DeadCode DAW 25Jun99 		oldbuffertop++;
//DeadCode DAW 25Jun99 		if (oldbuffertop >= OLDBUFFERSIZE)
//DeadCode DAW 25Jun99 			oldbuffertop = 0;
//DeadCode DAW 25Jun99 	}
//DeadCode DAW 25Jun99 
//DeadCode DAW 25Jun99 	oldbuffer[oldbuffertop] = *retptr;
//DeadCode DAW 25Jun99 	if (oldbufferbot == oldbuffertop)
//DeadCode DAW 25Jun99 	{
//DeadCode DAW 25Jun99 		oldbufferbot++;
//DeadCode DAW 25Jun99 		if (oldbufferbot >= OLDBUFFERSIZE)
//DeadCode DAW 25Jun99 			oldbufferbot = 0;
//DeadCode DAW 25Jun99 	}
//DeadCode DAW 25Jun99 //DeadCode RDH 30Apr99 	}

	//If the last message placed in the old buffer was low priority,
	//stomp over it with the new one.
	if (oldbuffer[oldbuffertop].visibility < NOTVIS_1)		//RJS 30Jun99
	{														//RJS 24Jun99
		oldbuffertop++;
		if (oldbuffertop >= OLDBUFFERSIZE)
			oldbuffertop = 0;
	}

	oldbuffer[oldbuffertop] = *retptr;						//RJS 24Jun99
	if (oldbufferbot == oldbuffertop)						//RJS 24Jun99
	{														//RJS 24Jun99
		oldbufferbot++;										//RJS 24Jun99
		if (oldbufferbot >= OLDBUFFERSIZE)					//RJS 24Jun99
			oldbufferbot = 0;								//RJS 24Jun99
	}														//RJS 24Jun99

	retptr->priority = GAP;	//spoken...
	if (retptr == &newbuffer[newbufferbot])
	{
		//Strip to next non-gap									//RJS 18May99
		do														//RJS 18May99
		{														//RJS 18May99
			newbufferbot++;										//RJS 18May99
			if (newbufferbot == NEWBUFFERSIZE)					//RJS 18May99
				newbufferbot = 0;								//RJS 18May99
																//RJS 18May99
			if (newbuffer[newbufferbot].priority != GAP)		//RJS 18May99
				break;											//RJS 18May99
																//RJS 18May99
			if (newbufferbot == newbuffertop)					//RJS 18May99
				break;											//RJS 18May99
		}														//RJS 18May99
		while (true);											//RJS 18May99
	}

	//display UI for a user response to the message (Not actually displayed until the end of the frame)
	if (retptr)
	{
		noBufferedMessages--;									//RJS 28May99
		if (retptr->caller && !retptr->caller->AcIsPlayer())		//RJS 23May99
		{
			if (!retptr->isComms)								//DAW 22Jun99
			{
				MinAnimData*	mad = (MinAnimData*) retptr->caller->Anim;
				if (mad->itemstate == DEAD)
					return NULL;
			}
		}

		thereIsANewMessage=true;
		OverLay.ActionMessage(retptr);
	}

	return(retptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RemoveGaps
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	MessageBuffer::RemoveGaps(MESSAGE_STRUC*	buffer, SLong &topindex, SLong size)
{
	SLong	index,index2,gapcnt,lastgap;
	Bool	doneone;


	lastgap = -1;
	gapcnt = 0;

	// Top body...
	for (index = topindex; index < size; index++)
	{
		if (buffer[index].priority == GAP)
		{
			doneone = FALSE;
			lastgap = index;
			for (index2 = (index+1); index2 < size; index2++)
			{
				if (buffer[index2].priority != GAP)
				{
					doneone = TRUE;
					gapcnt++;
					buffer[index] = buffer[index2];
					buffer[index2].priority = GAP;
					break;
				}
			}

			if (!doneone)
				break;
		}
	}

	// Crossover...
	if (lastgap > -1)
	{
		for (index = lastgap; index < size; index++)
		{
			if (buffer[index].priority == GAP)
			{
				doneone = FALSE;
				for (index2 = 0; index2 < topindex; index2++)
				{
					if (buffer[index2].priority != GAP)
					{
						doneone = TRUE;
						gapcnt++;
						buffer[index] = buffer[index2];
						buffer[index2].priority = GAP;
						break;
					}
				}

				if (!doneone)
					break;
			}
		}
	}

	// Bot body...
	for (index = 0; index < topindex; index++)
	{
		if (buffer[index].priority == GAP)
		{
			doneone = FALSE;
			for (index2 = (index+1); index2 < (topindex-1); index2++)
			{
				if (buffer[index2].priority != GAP)
				{
					doneone = TRUE;
					gapcnt++;
					buffer[index] = buffer[index2];
					buffer[index2].priority = GAP;
					break;
				}
			}

			if (!doneone)
				break;
		}
	}

	topindex -= gapcnt;
	if (topindex < 0)
		topindex += NEWBUFFERSIZE;

	return(gapcnt);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitMessageWindow
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	MessageBuffer::InitMessageWindow()
{
	displayedmsgindex = oldbuffertop;
	prevdisplayedmsgindex = oldbuffertop - 1;
	if (prevdisplayedmsgindex < 0)
		prevdisplayedmsgindex = OLDBUFFERSIZE-1;

//DeadCode AMM 24Jun99 	if (prevdisplayedmsgindex < oldbufferbot)
	if (prevdisplayedmsgindex == oldbufferbot)					//RJS 24Jun99
		prevdisplayedmsgindex = INVALIDMSG;

	nextdisplayedmsgindex = newbufferbot | INNEWBUFFERFLAG;
	// is new buffer empty?
	if (newbuffer[newbufferbot].priority == GAP)
		nextdisplayedmsgindex = INVALIDMSG;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IncMessageWindow
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	MessageBuffer::IncMessageWindow()
{
	if (nextdisplayedmsgindex == INVALIDMSG)
		return (FALSE);

	prevdisplayedmsgindex = displayedmsgindex;
	displayedmsgindex = nextdisplayedmsgindex;

	if (nextdisplayedmsgindex == oldbuffertop)
		nextdisplayedmsgindex = newbufferbot | INNEWBUFFERFLAG;
	else
	{
		// is it in old buffer?
		if ((nextdisplayedmsgindex & INNEWBUFFERFLAG)==0)
		{
			nextdisplayedmsgindex++;
			if (nextdisplayedmsgindex >= OLDBUFFERSIZE)
				nextdisplayedmsgindex = 0;
		}
		else
		{
			SLong	tmpnext = nextdisplayedmsgindex - INNEWBUFFERFLAG;
			while (		(tmpnext != newbuffertop)
					&&	(newbuffer[tmpnext].visibility < NOTVIS_1)	)
			{
				tmpnext++;
				if (tmpnext >= NEWBUFFERSIZE)
					tmpnext = 0;
			}

			nextdisplayedmsgindex = tmpnext | INNEWBUFFERFLAG;
			if (tmpnext == newbuffertop)
				nextdisplayedmsgindex = INVALIDMSG;
		}
	}

	return (TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecMessageWindow
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	MessageBuffer::DecMessageWindow()
{
	if (prevdisplayedmsgindex == INVALIDMSG)
		return (FALSE);

	nextdisplayedmsgindex = displayedmsgindex;
	displayedmsgindex = prevdisplayedmsgindex;

	if (prevdisplayedmsgindex == (newbufferbot | INNEWBUFFERFLAG))
		prevdisplayedmsgindex = oldbuffertop;
	else
	{
		if ((prevdisplayedmsgindex & INNEWBUFFERFLAG) == 0)
		{
			prevdisplayedmsgindex--;
			if (prevdisplayedmsgindex < 0)
				prevdisplayedmsgindex = OLDBUFFERSIZE - 1;

			if (prevdisplayedmsgindex == oldbufferbot)
				prevdisplayedmsgindex = INVALIDMSG;
		}
		else
		{
			SLong	tmpindex = prevdisplayedmsgindex - INNEWBUFFERFLAG;

			tmpindex--;
			if (tmpindex < 0)
				tmpindex = NEWBUFFERSIZE-1;

			prevdisplayedmsgindex = tmpindex | INNEWBUFFERFLAG;
		}
	}

	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MessageColour
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode RJS 29Sep00 Colour	MessageBuffer::MessageColour(SLong	line)
//DeadCode RJS 29Sep00 {
//DeadCode RJS 29Sep00 	Colour	thecol = (Colour) 0;		// invalid col...
//DeadCode RJS 29Sep00 
//DeadCode RJS 29Sep00 	switch (line)
//DeadCode RJS 29Sep00 	{
//DeadCode RJS 29Sep00 	case 0:
//DeadCode RJS 29Sep00 		line = prevdisplayedmsgindex;
//DeadCode RJS 29Sep00 		break;
//DeadCode RJS 29Sep00 	case 1:
//DeadCode RJS 29Sep00 		line = displayedmsgindex;
//DeadCode RJS 29Sep00 		break;
//DeadCode RJS 29Sep00 	case 2:
//DeadCode RJS 29Sep00 		line = nextdisplayedmsgindex;
//DeadCode RJS 29Sep00 		break;
//DeadCode RJS 29Sep00 	}
//DeadCode RJS 29Sep00 
//DeadCode RJS 29Sep00 	if (line != INVALIDMSG)
//DeadCode RJS 29Sep00 	{
//DeadCode RJS 29Sep00 		SLong			realindex = line;
//DeadCode RJS 29Sep00 		MESSAGE_STRUC*	thebuffer;
//DeadCode RJS 29Sep00 
//DeadCode RJS 29Sep00 		if ((realindex & INNEWBUFFERFLAG) == 0)
//DeadCode RJS 29Sep00 			thebuffer = oldbuffer;
//DeadCode RJS 29Sep00 		else
//DeadCode RJS 29Sep00 		{
//DeadCode RJS 29Sep00 			realindex -= INNEWBUFFERFLAG;
//DeadCode RJS 29Sep00 			thebuffer = newbuffer;
//DeadCode RJS 29Sep00 		}
//DeadCode RJS 29Sep00 
//DeadCode RJS 29Sep00 		if (thebuffer[realindex].caller == thePlayer ||
//DeadCode RJS 29Sep00 			thebuffer[realindex].caller == theOtherOne)
//DeadCode RJS 29Sep00 		{
//DeadCode RJS 29Sep00 			if (thebuffer[realindex].callee == thePlayer ||
//DeadCode RJS 29Sep00 				thebuffer[realindex].callee == theOtherOne)
//DeadCode RJS 29Sep00 				thecol = (Colour) 1;		//self
//DeadCode RJS 29Sep00 			else
//DeadCode RJS 29Sep00 				thecol = (Colour) 2;		//outgoing
//DeadCode RJS 29Sep00 		}
//DeadCode RJS 29Sep00 		else
//DeadCode RJS 29Sep00 			thecol = (Colour) 3;	//incoming
//DeadCode RJS 29Sep00 	}
//DeadCode RJS 29Sep00 
//DeadCode RJS 29Sep00 	return (thecol);
//DeadCode RJS 29Sep00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Callsign
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CString	MessageBuffer::Callsign(SLong	line)
{
	PhraseBuffer	phrasebuff;
	CString			thestring = "";

	switch (line)
	{
	case 0:
		line = prevdisplayedmsgindex;
		break;
	case 1:
		line = displayedmsgindex;
		break;
	case 2:
		line = nextdisplayedmsgindex;
		break;
	}

	if (line != INVALIDMSG)
	{
		SLong			realindex = line;
		MESSAGE_STRUC*	thebuffer;

		if ((realindex & INNEWBUFFERFLAG) == 0)
			thebuffer = oldbuffer;
		else
		{
			realindex -= INNEWBUFFERFLAG;
			thebuffer = newbuffer;
		}

		if (thebuffer[realindex].priority != GAP)
		{
			if (thebuffer[realindex].caller != thebuffer[realindex].callee)			//RJS 17May99
			{
				if (thebuffer[realindex].caller == thePlayer ||
					thebuffer[realindex].caller == theOtherOne)
				{
					if (thebuffer[realindex].callee)
					{
						thestring.LoadString(IDS_TO);
						_Radio.ExpandCallsign(phrasebuff,thebuffer[realindex].callee,thebuffer[realindex].voiceindex);//PD 04Mar99
					}
				}
				else
					_Radio.ExpandCallsign(phrasebuff,thebuffer[realindex].caller,thebuffer[realindex].voiceindex);//PD 04Mar99

				if (phrasebuff.phrase_count)
					phrasebuff.phrase_buffer[phrasebuff.phrase_count++] = PHRASE_COLON;

				PhraseToString(thestring,phrasebuff);
			}
		}

//DEADCODE RDH 04/05/99 		PhraseToString(thestring,phrasebuff);
	}

	return (thestring);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MessageBody
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CString	MessageBuffer::MessageBody(SLong	line)
{
	PhraseBuffer	phrasebuff;
	CString			thestring = "";

	switch (line)
	{
	case 0:
		line = prevdisplayedmsgindex;
		break;
	case 1:
		line = displayedmsgindex;
		break;
	case 2:
		line = nextdisplayedmsgindex;
		break;
	}

	if (line != INVALIDMSG)
	{
		SLong			realindex = line;
		MESSAGE_STRUC*	thebuffer;

		if ((realindex & INNEWBUFFERFLAG) == 0)
			thebuffer = oldbuffer;
		else
		{
			realindex -= INNEWBUFFERFLAG;
			thebuffer = newbuffer;
		}

		if (thebuffer[realindex].priority != GAP)
			_Radio.ExpandMessage(phrasebuff,thebuffer[realindex]);

		PhraseToString(thestring,phrasebuff);
	}

	return (thestring);
}

void MessageBuffer::MessageParticipants(SLong line,AirStrucPtr& mcaller,AirStrucPtr& mcallee,itemptr& mtarget)
{
	mcaller=NULL;
	mcallee=NULL;
	mtarget=NULL;

	switch (line)
	{
	case 0:	line=prevdisplayedmsgindex; break;
	case 1: line=displayedmsgindex;		break;
	case 2: line=nextdisplayedmsgindex; break;
	}

	if (line != INVALIDMSG)
	{
		SLong			realindex = line;
		MESSAGE_STRUC*	thebuffer;

		if ((realindex & INNEWBUFFERFLAG) == 0)
			thebuffer = oldbuffer;
		else
		{
			realindex -= INNEWBUFFERFLAG;
			thebuffer = newbuffer;
		}
		mcaller=thebuffer->caller;
		mcallee=thebuffer->callee;
		mtarget=(itemptr)thebuffer->target;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReSpeakDispMsg
//Author		Robert Slater
//Date			Tue 26 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	MessageBuffer::ReSpeakDispMsg()
{
	SLong	line = displayedmsgindex;

	if (line != INVALIDMSG)
	{
		SLong			realindex = line;
		MESSAGE_STRUC*	thebuffer;

		if ((realindex & INNEWBUFFERFLAG) == 0)
			thebuffer = oldbuffer;
		else
		{
			realindex -= INNEWBUFFERFLAG;
			thebuffer = newbuffer;
		}

		_Radio.PlayMessage(thebuffer[realindex],96);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetPlayer
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
void	MessageBuffer::SetPlayer(AirStrucPtr	ac1,AirStrucPtr	ac2)
{
	BufferInit();				//RJS 01Apr99

	thePlayer = ac1;
	theOtherOne = ac2;

//DEADCODE RDH 17/05/00 	_Radio.Enter3D();											//RJS 28Apr99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PhraseToString
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
void	MessageBuffer::PhraseToString(CString &thestring, PhraseBuffer&	thebuff)
{
	PhraseTables	thePhrase;
	ULong			count = 0;
	CString			tmpstring;

//DEADCODE RDH 04/05/99 	thestring = "";
	while (count < thebuff.phrase_count)
	{
		thePhrase = PhraseTables(thebuff.phrase_buffer[count]);

		if ((thePhrase & 0xff00) == PHRASE_USER_DEFINED)
			tmpstring = CString(_DPlay.GetPlayerMessage(thePhrase-PHRASE_USER11));
		else
		{
			if ((thePhrase & 0xff00) == PHRASE_PLAYERNAMES)
				tmpstring = CString(_DPlay.GetPlayerName(thePhrase-PHRASE_PLAYERNAME1));
			else
				tmpstring.LoadString(_Radio.PhraseToResource(thePhrase));
		}

#ifdef	CHATTERTRACE
		if (tmpstring.CompareNoCase("not defined")==0)
		{
			UWord cw=GETFPCW();
			PhraseTables	tl, lp;

			tl = PhraseTables(thebuff.master_phrase[count]);
			if (count > 0)
				lp = PhraseTables(thebuff.phrase_buffer[count-1]);

			::AfxTrace("MISSING:\t%08x\t%08x\t%08x\n",tl,thePhrase,lp);
			SETFPCW(cw);
		}
#endif

		count++;

		thestring += tmpstring;
	}

#ifdef	_PRINTSTRING_
	fprintf(debfp,"%s\n",(const char*)thestring);
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetPlaceName
//Author		Robert Slater
//Date			Thu 11 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CString	MessageBuffer::GetPlaceName(Coords3D&	wpos)
{
	PhraseBuffer	phrasebuff;
	CString			thestring = "";
	item*			tmpitem = new item;

	if (tmpitem)
	{
		tmpitem->World = wpos;

		_Radio.ExpandPlacename(phrasebuff,tmpitem);

		PhraseToString(thestring,phrasebuff);

		delete tmpitem;
	}

	return(thestring);
}

CString	MessageBuffer::GetPlaceName(UWord	wpos)
{
	PhraseBuffer	phrasebuff;
	CString			thestring = "";

	_Radio.ExpandPlacename(phrasebuff,wpos);

	PhraseToString(thestring,phrasebuff);


	return(thestring);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FakePhraseToString
//Author		Robert Slater
//Date			Wed 24 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	MessageBuffer::FakePhraseToString(CString &thestring, PhraseBuffer&	thebuff)
{
	PhraseTables	thePhrase;
	ULong			count = 0;
	CString			tmpstring;
	ULong			poonum;

	thestring = "";
	while (count < thebuff.phrase_count)
	{
		thePhrase = (PhraseTables)thebuff.phrase_buffer[count++];

		poonum = _Radio.PhraseToResource(thePhrase);

		tmpstring.LoadString(poonum);

		poonum -= _Radio.PhraseToResource(0);

		if (_Radio.phraseused[poonum])
			thestring += tmpstring;
		else
		{
			thestring += "[";
			thestring += tmpstring;
			thestring += "]";

			_Radio.phraseused[poonum] = 1;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearMessageMsg
//Author		Robert Slater
//Date			Thu 13 May 1999
//
//Description	Looks for new messages of a particular type
//				and dumps them.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	MessageBuffer::ClearMessagesMsg(SLong	messagetype)
{
	SLong	index;
	for (index = 0; index < NEWBUFFERSIZE; index++)
	{
		if (	(newbuffer[index].priority != GAP)
			&&	(newbuffer[index].messagetype == messagetype)	)
		{
			newbuffer[index].priority = GAP;
			noBufferedMessages--;
		}
//DeadCode DAW 25Jun99 		if (newbuffer[index].messagetype == messagetype)
//DeadCode DAW 25Jun99 			newbuffer[index].priority = GAP;
	}

	RemoveGaps(newbuffer,newbuffertop,NEWBUFFERSIZE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearMessagesPri
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
void	MessageBuffer::ClearMessagesPri(SLong	priority)
{
	if (priority != GAP)										//RJS 24Jun99
	{
		SLong	index;
		for (index = 0; index < NEWBUFFERSIZE; index++)
		{
			if (newbuffer[index].priority == priority)
			{
				newbuffer[index].priority = GAP;
				noBufferedMessages--;
			}
		}

		RemoveGaps(newbuffer,newbuffertop,NEWBUFFERSIZE);
	}
//DeadCode DAW 25Jun99 	SLong	index;
//DeadCode DAW 25Jun99 	for (index = 0; index < NEWBUFFERSIZE; index++)
//DeadCode DAW 25Jun99 	{
//DeadCode DAW 25Jun99 		if (newbuffer[index].priority == priority)
//DeadCode DAW 25Jun99 			newbuffer[index].priority = GAP;
//DeadCode DAW 25Jun99 	}
//DeadCode DAW 25Jun99 
//DeadCode DAW 25Jun99 	RemoveGaps(newbuffer,newbuffertop,NEWBUFFERSIZE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExpandDirect
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
void	MessageBuffer::ExpandDirect(const MESSAGE_STRUC&	msg)
{
	PhraseBuffer	phrasebuff;

	*lateststring = "";
	
	_Radio.ExpandMessage(phrasebuff,msg);

	PhraseToString(*lateststring,phrasebuff);

	if (_Radio.View_Point)										//RJS 09Jul99
		_Radio.View_Point->itemTalkedAbout = msg.target;		//RJS 09Jul99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearMessagesMsg
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
void	MessageBuffer::ClearMessagesMsg(SLong	messagetype, ItemPtr	theTarget)
{
	SLong	index;
	for (index = 0; index < NEWBUFFERSIZE; index++)
	{
		if (	(newbuffer[index].priority != GAP)					//RJS 24Jun99
			&&	(newbuffer[index].messagetype == messagetype)
			&&	(newbuffer[index].target == theTarget)			)
		{
			newbuffer[index].priority = GAP;
			noBufferedMessages--;
		}
//DeadCode DAW 25Jun99 		if (	(newbuffer[index].messagetype == messagetype)
//DeadCode DAW 25Jun99 			&&	(newbuffer[index].target == theTarget)			)
//DeadCode DAW 25Jun99 			newbuffer[index].priority = GAP;
	}

	RemoveGaps(newbuffer,newbuffertop,NEWBUFFERSIZE);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShouldHearMsg
//Author		Craig Beeston
//Date			Tue 07 Mar 2000
//
//Description	throwAway is set to FALSE if we want the message to come through
//				as chatter, but not buffered...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool MessageBuffer::ShouldHearMsg(const MESSAGE_STRUC& msg, Bool& throwAway)
{
	bool retval = false;										//RJS 02May00

	throwAway	= TRUE;

	if (!_Replay.Playback && thePlayer)
	{
// No way...
		if (msg.blockchatter)
			return false;

		if(	(	((msg.caller) && ((msg.caller->nationality != thePlayer->nationality) || (msg.caller->Status.deadtime)))
			||	((msg.callee) && ((msg.callee->nationality != thePlayer->nationality) || (msg.callee->Status.deadtime)))	)
			&& !(_DPlay.Implemented && _DPlay.GameType<DPlay::COMMSQUICKMISSION))	//AMM 22Oct00
			return false;

// Definitely...
		if ((msg.caller == thePlayer) || (msg.caller == theOtherOne))
			return true;

// Special LW check...
		if (	msg.caller && msg.callee && (msg.callee->nationality == NAT_LUF)
			&&	(msg.callee->Distance3DSquared(&msg.caller->World) > (6400000.0 * 6400000.0))	)
				return false;

		if ((msg.callee == thePlayer) || (msg.callee == theOtherOne))
			return true;

// Depends...
		throwAway	= FALSE;
		if (noBufferedMessages <= 8)
		{
// We want to hear leaders...
			if(		((msg.caller) && (msg.caller->PlayerInGroup()) && (!msg.caller->leader))
				||	((msg.callee) && (msg.callee->PlayerInGroup()) && (!msg.callee->leader))	)
				retval = true;
		}
	}

	return retval;
}

MESSAGE_STRUC::MESSAGE_STRUC(int scrpt,MsgType mtype,MobileItemPtr from,ItemBasePtr about,AirStrucPtr to)//RJS 02Apr99
{
	messagetype = mtype;
	caller = *from;
	target = about;
	callee = to;

	decisionhandler = NULL;

//DeadCode AMM 20Oct100 	if (_Replay.Playback)
//DeadCode AMM 20Oct100 	{
//DeadCode AMM 20Oct100 		messagetype = MsgType(MSG_LP | MSG_BLOCKCHATTER);
//DeadCode AMM 20Oct100 		scrpt = 0;
//DeadCode AMM 20Oct100 	}

	SetVoiceType();
	ProcessScript(scrpt);
	ProcessUserMessage();
//DeadCode RJS 29Sep00 	SetVoiceType();
}

MESSAGE_STRUC::MESSAGE_STRUC(int scrpt,MsgType mtype,VoiceType vox,ItemBasePtr about,AirStrucPtr to)//RJS 02Apr99
{
	messagetype = mtype;
	caller = NULL;
	target = about;
	callee = to;

	voiceindex = vox;
	decisionhandler = NULL;

//DeadCode AMM 20Oct100 	if (_Replay.Playback)
//DeadCode AMM 20Oct100 	{
//DeadCode AMM 20Oct100 		messagetype = MsgType(MSG_LP | MSG_BLOCKCHATTER);
//DeadCode AMM 20Oct100 		scrpt = 0;
//DeadCode AMM 20Oct100 	}

	ProcessScript(scrpt);
	ProcessUserMessage();
}

MESSAGE_STRUC::MESSAGE_STRUC(int scrpt,MsgType mtype,MobileItemPtr from,ItemBasePtr about,AirStrucPtr to,const TARGET_INDEXES& tindex)
{
	messagetype = mtype;
	caller = *from;
	target = about;
	callee = to;
	targetinfo = tindex;

	decisionhandler = NULL;

//DeadCode AMM 20Oct100 	if (_Replay.Playback)
//DeadCode AMM 20Oct100 	{
//DeadCode AMM 20Oct100 		messagetype = MsgType(MSG_LP | MSG_BLOCKCHATTER);
//DeadCode AMM 20Oct100 		scrpt = 0;
//DeadCode AMM 20Oct100 	}

	SetVoiceType();
	ProcessScript(scrpt);
	ProcessUserMessage();
//DeadCode RJS 29Sep00 	SetVoiceType();
}

void	MessageBuffer::ClearRadio()
{
	_Radio.ClearOldMessage();
}
