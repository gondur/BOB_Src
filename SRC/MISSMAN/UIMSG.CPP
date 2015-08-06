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

//////////////////////////////////////////////////////////////////////
//
// Module:      UIMsg.cpp
//
// Created:     12/01/00 by AMM
//
// Description: User Interface message management
//	This module handles the IntelBuffer structure declared in nodebob.h
//
//////////////////////////////////////////////////////////////////////

#include "dosdefs.h"
#include "rchatter.h"
#include "nodebob.h"
#include	"mapsfx.h"									//RJS 08May00

//////////////////////////////////////////////////////////////////////
//
// Function:    PVA	
// Date:		12/01/00
// Author:		AMM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
const IntelMsg::PVA	
//DEADCODE DAW 10/03/00 IntelMsg::LOW_ENG_PILOT=		{IntelMsg::LOW,	IntelMsg::PILOT	,IntelMsg::ENGAGEMENT		},
IntelMsg::HIGH_SPOTTING_WOMAN=		{IntelMsg::HIGH,IntelMsg::WOMAN		,IntelMsg::SPOTTING,	SFX_AlertRaid		},
IntelMsg::HIGH_FLIGHT_WOMAN=		{IntelMsg::HIGH,IntelMsg::WOMAN		,IntelMsg::FLIGHT,		SFX_PhoneOut		},
IntelMsg::MED_MANAGEMENT_MAN=		{IntelMsg::MED,	IntelMsg::MAN		,IntelMsg::MANAGEMENT,	SFX_TeleType		},
IntelMsg::HIGH_SPOTTING_LW_WOMAN=	{IntelMsg::HIGH,IntelMsg::LWWOMAN	,IntelMsg::SPOTTING,	SFX_PhoneIn		},
IntelMsg::MED_MANAGEMENT_LW_MAN=	{IntelMsg::MED,	IntelMsg::LWMAN		,IntelMsg::MANAGEMENT,	SFX_TeleType		},
IntelMsg::MED_MANAGEMENT_LW=		{IntelMsg::MED,	IntelMsg::LUFT		,IntelMsg::MANAGEMENT,	SFX_TeleType		},
IntelMsg::HIGH_FLIGHT_LW_WOMAN=		{IntelMsg::HIGH,IntelMsg::LWWOMAN	,IntelMsg::FLIGHT			},
IntelMsg::HIGH_FLIGHT_LW=			{IntelMsg::HIGH,IntelMsg::LUFT		,IntelMsg::FLIGHT			},
IntelMsg::HIGH_SPOTTING_LW=			{IntelMsg::HIGH,IntelMsg::LUFT		,IntelMsg::SPOTTING			},
IntelMsg::HIGH_TARGET_LW_WOMAN=		{IntelMsg::HIGH,IntelMsg::LWWOMAN	,IntelMsg::TARGETSTATUS,	SFX_PhoneIn		},
IntelMsg::HIGH_TARGET_LW=			{IntelMsg::HIGH,IntelMsg::LUFT		,IntelMsg::TARGETSTATUS,	SFX_PhoneIn		},
IntelMsg::HIGH_TARGET_WOMAN=		{IntelMsg::HIGH,IntelMsg::WOMAN		,IntelMsg::TARGETSTATUS,	SFX_PhoneIn		},
IntelMsg::HIGH_ENGAGEMENT_WOMAN=	{IntelMsg::HIGH,IntelMsg::WOMAN		,IntelMsg::ENGAGEMENT			},
IntelMsg::HIGH_ENGAGEMENT_LW=		{IntelMsg::HIGH,IntelMsg::LUFT		,IntelMsg::ENGAGEMENT			},
IntelMsg::HIGH_ENGAGEMENT_LW_WOMAN=	{IntelMsg::HIGH,IntelMsg::LWWOMAN	,IntelMsg::ENGAGEMENT			},

//this is the last one. It is used for end-day reports only.
IntelMsg::MED_ANNOUNCEMENT_EXTERNAL={IntelMsg::MED, IntelMsg::EXTERNAL, IntelMsg::ANNOUNCEMENT			};
//////////////////////////////////////////////////////////////////////
//
// Function:    AddMessage
// Date:		12/01/00
// Author:		AMM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
static	ULong WhoAndWhat(UniqueID friendly,UniqueID target)
{
	int	p,sq;
	if (friendly)
		if (Persons2::GetBandFromUID(friendly)==SagBAND)
		{
			Todays_Packages.GetACSquadEntry(friendly,p,sq);
			sq=Todays_Packages[p].GetRaidIndFromSquadEntry(sq);
			p=p+(sq+1)*512+UID_BIT15;
			friendly=UniqueID(p);
		}
	if (target)
		if (Persons2::GetBandFromUID(target)==SagBAND)
		{
			Todays_Packages.GetACSquadEntry(target,p,sq);
			sq=Todays_Packages[p].GetRaidIndFromSquadEntry(sq);
			p=p+(sq+1)*512+UID_BIT15;
			target=UniqueID(p);
		}
   return (friendly+(target<<16));


}

bool	IntelBuffer::AddMessage(
			IntelMsg::PVA pva,AccelSwitches actiontype,ScriptTables script,
			UniqueID friendly,UniqueID target,const TargetIndexes&ti
			)
{
	if (&ti==NULL)
		return AddMessage(pva,actiontype,script,friendly,target,TargetIndexes());
	if 	(pva.voice != IntelMsg::EXTERNAL)
	{
		if (Todays_Packages.localplayer==NAT_RAF)
		{
			if ((pva.voice&~IntelMsg::LUFT)==0)
				return false;
		}
		else
		{
			if ((pva.voice&IntelMsg::LUFT)==0)
				return false;
		}
	}

	_Miles.UIPlayAmbient(pva.sfxTrigger);								//RJS 9Jun00


	ScriptTables	titlescript,bodyscript;
//DeadCode RDH 07Mar00 	bodyscript=ScriptTables(script+1-0x10000);
//DeadCode RDH 07Mar00 	ULong	nochoices = bodyscript & 0xFFFF0000;
//DeadCode RDH 07Mar00 	bodyscript=ScriptTables((bodyscript&0xffff)+0x10000+Math_Lib.rnd(nochoices>>16));
	ULong	nochoices = ((script>>16)&0xFF)-1;	// should be at least 2

	titlescript= ScriptTables((script&0xffff)+0x10001);
	bodyscript = ScriptTables(titlescript+Math_Lib.rnd(nochoices)+1); //scripts 0 & 1 are the title

	PhraseBuffer bodybuffer;
	bodybuffer.phrase_count = 0;
		UWord rndval=0;
	_Radio.ExpandMessage(bodybuffer,titlescript,rndval,ti,NULL,NULL,NULL);
	int title=_Radio.PhraseToResource(bodybuffer.phrase_buffer[0]);
	int	currentwhoandwhat=WhoAndWhat(friendly,target);
	if (title==messages[latest].title)
		if (currentwhoandwhat==lastwhoandwhat)
			title=NULL;

	if (title)
	{
		lastwhoandwhat=currentwhoandwhat;
		bodybuffer.phrase_count = 0;
		latest++;
		if (latest==BUFFERSIZE)
			latest=0;
		int next=latest+1;
		if (next==BUFFERSIZE)
			next=0;
		{for (int i=0;i<Bmaxupto;i++)
			if (B[i]==latest)
				B[i]=next;
		}
		IntelMsg* slot=messages+latest;
		UWord rndval=Math_Lib.rnd();
		ItemPtr callee=NULL,trg=NULL;
		if (friendly)	callee=Persons2::ConvertPtrUID(friendly);
		if (target)		trg=Persons2::ConvertPtrUID(target);

		_Radio.ExpandMessage(bodybuffer,bodyscript,rndval,ti,callee,trg,callee);
		for (int i=0;i<bodybuffer.phrase_count;i++)
			slot->bodyscript[i]= bodybuffer.phrase_buffer[i];
		slot->bodyscript[i]=0;
		slot->pva=pva;
		if (pva.voice  == IntelMsg::EXTERNAL)
			slot->time=MMC.currdate/SECSPERDAY;
		else
			slot->time=MMC.currtime-HR04;									//RDH 14/03/00
		if (target)
			slot->what=target;
		else
			slot->what=friendly;
		slot->title=title;

		VoiceType	theVoice = VoiceType(IVoiceToRVoice(slot->pva.voice));
		slot->pva.voice = IntelMsg::Voice(RVoiceToIVoice(_Radio.GetVoice(bodyscript,theVoice)));

		if (stoppedspeaking)
			SayNextMessage();
	}	//so message doesn't get stored again and accelon repeats previous

	ChangeAccelOn(actiontype,friendly,target, latest);
	return !stoppedspeaking;
}
//////////////////////////////////////////////////////////////////////
//
// Function:    ChangeAccelOn
// Date:		10/03/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	IntelBuffer::ChangeAccelOn(AccelSwitches actiontype,UniqueID friendly,UniqueID target, int		latest)
{
#ifndef	BOB_DEMO_VER
	bool doneone=false;
	if (actiontype)
	{
		Profile::AttackMethod	mysidemethod=Profile::AM_LWPACKS;
		if (Todays_Packages.localplayer==NAT_RAF)
			mysidemethod=Profile::AM_RAF;
		int	packf=-1,packt=-1,sqf,sqt;
		if (friendly && Persons2::ConvertPtrUID(friendly)!=NULL && Persons2::ConvertPtrUID(friendly).Status.size==AIRSTRUCSIZE)
			Todays_Packages.GetACSquadEntry(friendly,packf,sqf);
		if (target && Persons2::ConvertPtrUID(target)!=NULL && Persons2::ConvertPtrUID(target).Status.size==AIRSTRUCSIZE)
			Todays_Packages.GetACSquadEntry(target,packt,sqt);

		if (MMC.fav.decelon[actiontype])
		{
			if (packf!=-1)
				if ((Todays_Packages[packf].attackmethod&Profile::AM_GROUPMASK)==mysidemethod)
				{
//DEADCODE RDH 19/04/00 					MMC.curracceltype=MMC.ACCEL_NORMAL;
//DEADCODE RDH 19/04/00 					MMC.curraccelrate=1;
					ClickPlay();
				}
			if (packt!=-1)
				if ((Todays_Packages[packt].attackmethod&Profile::AM_GROUPMASK)==mysidemethod)
				{
//DEADCODE RDH 19/04/00 					MMC.curracceltype=MMC.ACCEL_NORMAL;
//DEADCODE RDH 19/04/00 					MMC.curraccelrate=1;
					ClickPlay();
				}
		}
		if (MMC.fav.flyon[actiontype])
		{
			if (packf!=-1)
				if ((Todays_Packages[packf].attackmethod&Profile::AM_GROUPMASK)==mysidemethod)
				{
					OpenTakeOffOffered(packf,sqf,	latest);	//launch fly dialogue for packf,sqf
					doneone=true;
				}
			if (!doneone && packt!=-1)
				if ((Todays_Packages[packt].attackmethod&Profile::AM_GROUPMASK)==mysidemethod)
				{
					OpenTakeOffOffered(packf,sqf, latest);	//launch fly dialogue for packt,sqt
					doneone=true;
				}

		}
			
		if (!doneone && MMC.fav.flyonfav[actiontype])
		{
			SquadNum sq[2]={SQ_MAX,SQ_MAX};
			int	psinfo[2][2]={{packf,sqf},{packt,sqt}};
			if (packf!=-1)
				sq[0]=Todays_Packages[packf][sqf].squadnum;
			if (packt!=-1)
				sq[1]=Todays_Packages[packt][sqt].squadnum;
			int pickedone=-1;
			for (int sqind=0;sqind<2;sqind++)
				if (sq[sqind]!=SQ_MAX)
				{
					SquadNum squad=sq[sqind];
					if (squad>SQ_LW_START)
					{
						if (Todays_Packages.localplayer==NAT_LUF)
						{
							Gruppen* g=Node_Data[squad];
							bool gruppeok = false;
							if (		(!MMC.fav.gruppe)
									||	(		(MMC.fav.gruppe)
											&&	(g->gruppennum==(MMC.fav.gruppe-1))
										)
								)
								gruppeok = true;
							if (gruppeok)
							{
								if (MMC.fav.geschwader >= 0)
								{
									if (MMC.fav.geschwader==g->wadernum)
									pickedone=sqind;
								}
								else
								{
									if (MMC.fav.geschwadertype!=WN_BETTERRULE)
									{
										if (MMC.fav.flotte!=LF_DET)
										{
											Geshwader* gesh=&Node_Data.geschwader[g->wadernum];
											if (MMC.fav.geschwadertype==gesh->wadername && MMC.fav.flotte==gesh->luftflotte)
												pickedone=sqind;
										}
										else
										{
											Geshwader* gesh=&Node_Data.geschwader[g->wadernum];
											if (MMC.fav.geschwadertype==gesh->wadername)
												pickedone=sqind;
										}
									}else
									{
										if (MMC.fav.flotte!=LF_DET)
										{
											Geshwader* gesh=&Node_Data.geschwader[g->wadernum];
											if (MMC.fav.flotte==gesh->luftflotte)
												pickedone=sqind;
										}else
											pickedone=sqind;

									}
								}
							}
						}
					}
					else
					{
						if (Todays_Packages.localplayer==NAT_RAF)
						{
							if (MMC.fav.squadron)
							{
								if (squad==MMC.fav.squadron)
									pickedone=sqind;
							}
							else
							{
								BritSquadron* bs=Node_Data[squad];
								if (MMC.fav.ac==0|| MMC.fav.ac== (1+bs->actype/2))
								{
									TargetSectorField* sectfield=
										TargetFighterFieldPtr(Node_Data[bs->homeairfield])->getsectoraf();
	//DEADCODE RDH 25/04/00 not doing sector 								if (MMC.favsector)
	//DEADCODE RDH 25/04/00 								{
	//DEADCODE RDH 25/04/00 									if (MMC.favsector==sectfield->sectorname)
	//DEADCODE RDH 25/04/00 										pickedone=sqind;
	//DEADCODE RDH 25/04/00 								}
	//DEADCODE RDH 25/04/00 								else
										if (MMC.fav.group)
										{
											if ((IDS_GROUP_10+MMC.fav.group-1)==sectfield->groupname)
												pickedone=sqind;
										}else
											pickedone=sqind;
								}
							}
						}
					}
				}
			if (pickedone!=-1)
			{	//launch fly dialogue	with psinfo[pickedone][0],psinfo[pickedone][1]
				OpenTakeOffOffered(psinfo[pickedone][0],psinfo[pickedone][1],	latest);
				doneone=true;//launch fly dialogue for packf,sqf
			} 	
		}
		
		if (!doneone && MMC.fav.forcesquadron)
		{
			if (packf!=-1 && Todays_Packages[packf][sqf].squadnum==MMC.fav.forcesquadron)
			{
				OpenTakeOffOffered(packf,sqf,	latest);	//launch fly dialogue for packf,sqf
				doneone=true;//launch fly dialogue for packf,sqf
			}
			elseif (packt!=-1 && Todays_Packages[packt][sqt].squadnum==MMC.fav.forcesquadron)
			{
				OpenTakeOffOffered(packt,sqt,	latest);	//launch fly dialogue for packf,sqf
				doneone=true;//launch fly dialogue for packf,sqf
			}
		}
		if (doneone && MMC.fav.forcesquadron)
			if (packf!=-1 && Todays_Packages[packf][sqf].squadnum==MMC.fav.forcesquadron)
				MMC.fav.forcesquadron=SQ_ZERO;
			elseif (packt!=-1 && Todays_Packages[packt][sqt].squadnum==MMC.fav.forcesquadron)
				MMC.fav.forcesquadron=SQ_ZERO;
	}
#endif
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SayNextMessage
// Date:		10/03/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool	IntelBuffer::SayNextMessage()
{
	bool saidsomething=false;
	stoppedspeaking=false;
	if (B[Bsaidupto]!=latest)
	{
		int guess=latest,bestguess=-1,bestpriority=IntelMsg::LOWEST;
//DEADCODE RJS 4/6/00 		if (guess==BUFFERSIZE)
		int secondbestguess=-1;
//DEADCODE RJS 4/6/00 			guess=0;
		while (guess!=B[Bsaidupto])
		{
			if (messages[guess].pva.priority>bestpriority)
			{
				bestpriority=messages[guess].pva.priority;
				secondbestguess=bestguess=guess;
			}
			else
				if (messages[guess].pva.priority==bestpriority)
					if (secondbestguess==bestguess)
						secondbestguess=guess;
			if (guess==0)
				guess=BUFFERSIZE;

			guess--;
		}
		B[Bsaidupto]=secondbestguess;
		saidsomething=SayMessage(B[Bsaidupto]);
	}
	if (!saidsomething)
		stoppedspeaking=true;
	return saidsomething;	
}

int	IntelBuffer::IVoiceToRVoice(int	IVoice)
{
	int	theVoice;

	switch (IVoice)				//RJS 28Mar00
	{
	case IntelMsg::MAN:
		theVoice = VOICE_GROUND;
	break;
	case IntelMsg::WOMAN:
		theVoice = VOICE_FEMALE;
	break;
	case IntelMsg::EXTERNAL:											//RJS 26Oct00
		theVoice = VOICE_SILENT;
	break;
	default:
		theVoice = VOICE_REST;
	break;
	}

	return theVoice;
}

int	IntelBuffer::RVoiceToIVoice(int	RVoice)
{
	int	theVoice;

	switch (RVoice)				//RJS 28Mar00
	{
	case VOICE_GROUND:
		theVoice = IntelMsg::MAN;
	break;
	case VOICE_FEMALE:
		theVoice = IntelMsg::WOMAN;
	break;
	case VOICE_SILENT:													//RJS 26Oct00
		theVoice = IntelMsg::EXTERNAL;
	break;
	default:
		theVoice = IntelMsg::PILOT;
	break;
	}

	return theVoice;
}

bool	IntelBuffer::SayMessage(int messagenum)
{
	VoiceType	theVoice;								//RJS 28Mar00

	if (Todays_Packages.localplayer!=NAT_RAF)
		theVoice = VOICE_SILENT;
	else
	{
		switch (messages[messagenum].pva.voice)				//RJS 28Mar00
		{
		default:
		case IntelMsg::PILOT:
			theVoice = VOICE_REST;
		break;
		case IntelMsg::MAN:
			theVoice = VOICE_GROUND;
		break;
		case IntelMsg::WOMAN:
			theVoice = VOICE_FEMALE;
		break;
		case IntelMsg::EXTERNAL:
			theVoice = VOICE_SILENT;
		break;
		}
	}

	_Radio.PlayMessage(messages[messagenum].bodyscript,theVoice);//RJS 28Mar00

//DeadCode RJS 26Oct00 	CString result="";
//DeadCode RJS 26Oct00 	for (int i=0;messages[messagenum].bodyscript[i];i++)
//DeadCode RJS 26Oct00 		result+=LoadResString(_Radio.PhraseToResource(messages[messagenum].bodyscript[i]));
	return true; //return false if didn't speak.
}
CString	IntelBuffer::MessageTitleToText(int messagenum)
{
	return LoadResString(messages[messagenum].title);
}
int	IntelBuffer::MessageTitle(int messagenum)
{
	return (messages[messagenum].title);
}
CString	IntelBuffer::MessageBodyToText(int messagenum)
{
	CString result="";
	for (int i=0;messages[messagenum].bodyscript[i];i++)
		result+=LoadResString(_Radio.PhraseToResource(messages[messagenum].bodyscript[i]));
	return result;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ChangeMessagesUID
// Date:		21/03/00
// Author:		JIM
//
//Description: This UID is about to be deleted replace any references with this dummy UID
//
//////////////////////////////////////////////////////////////////////
void	IntelBuffer::ChangeMessagesUID(UniqueID old,int newid)
{
	for (int i=0;i<BUFFERSIZE;i++)
		if (messages[i].what==old)
			messages[i].what=UniqueID(newid);
}



//DeadCode JIM 13Nov00 ScriptTables ReviewBuffer::unrepeatablescripts[32] =
//DeadCode JIM 13Nov00 {//max 32
//DeadCode JIM 13Nov00 	SCRIPT_RAFPAC,SCRIPT_LUFPAC//,SCRIPT_FIGHTERCOMMANDEXHAUSTED,
//DeadCode JIM 13Nov00 	 //SCRIPT_FIGHTERCOMMANDNEARLYEXHAUSTED, SCRIPT_FIGHTERCOMMANDUNFIT,
//DeadCode JIM 13Nov00 	 SCRIPT_PILOTSHORTAGE, SCRIPT_BIGWINGUSED, SCRIPT_LUFTWAFFEBOMBLONDON,
//DeadCode JIM 13Nov00 	 SCRIPT_RAFBOMBBERLIN, SCRIPT_THOUSANDBOMBER,SCRIPT_BIGESCORT,
//DeadCode JIM 13Nov00 	 SCRIPT_CRITICALSHIPPINGLOSS, SCRIPT_CRITICALTARGETS,SCRIPT_RDFHOLES,
//DeadCode JIM 13Nov00 	 SCRIPT_RAFRADIONET, SCRIPT_RAFRADIONETSUCCESS
//DeadCode JIM 13Nov00 };

bool	ReviewBuffer::IsScriptRepeated(UnrepeatableScripts::Script script)
{
	int i=script;
//DeadCode JIM 13Nov00 	for (i=0; i<32;i++)
//DeadCode JIM 13Nov00 	{
//DeadCode JIM 13Nov00 		breakif (unrepeatablescripts[i] == script);
//DeadCode JIM 13Nov00 	}
	ULong mask = 1<<i;
	ULong rv = 	repeatedscripts &mask;
	return(rv!=0);						
}

bool	ReviewBuffer::SetScriptRepeated(UnrepeatableScripts::Script script)
{
	int i=script;
//DeadCode JIM 13Nov00 	int i;
//DeadCode JIM 13Nov00 	for (i=0; i<32;i++)
//DeadCode JIM 13Nov00 	{
//DeadCode JIM 13Nov00 		breakif (unrepeatablescripts[i] == script);
//DeadCode JIM 13Nov00 	}
	ULong mask = 1<<i;
	ULong rv = 	repeatedscripts &mask;
	repeatedscripts |= mask;

	return(rv!=0);						
}
