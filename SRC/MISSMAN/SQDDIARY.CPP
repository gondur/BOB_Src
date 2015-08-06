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
//Filename       sqddiary.cpp
//System         
//Author         Robert Slater
//Date           Tue 25 Jan 2000
//Description    
//------------------------------------------------------------------------------

#include	"dosdefs.h"
#include	"worldinc.h"
#include	"package.h"
#include	"missman2.h"
#include	"sqddiary.h"
#include	"nodebob.h"
#include	"bstream.h"
#include	"3dcom.h"
#include	"viewsel.h"
#include	"rchatter.h"
#include	"messengn.h"												//RJS 30Oct00

Diary	Squad_Diary;


//Loading & Saving Bit-Stream stuff...

BOStream&	operator<<(BOStream&	bo, Diary::Master* dptr)
{
	bo.write((char*)dptr,sizeof(*dptr));
	bo.write((char*)dptr->gruppentable,dptr->gruppentablemax*sizeof(dptr->gruppentable[0]));
	bo.write((char*)dptr->squadtable,dptr->squadtablemax*sizeof(dptr->squadtable[0]));
	bo.write((char*)dptr->intercepttable,dptr->intercepttablemax*sizeof(dptr->intercepttable[0]));
	bo.write((char*)dptr->raidgrouptable,dptr->raidgroupmax*sizeof(dptr->raidgrouptable[0]));
	bo.write((char*)dptr->raidpacktable,dptr->raidpackmax*sizeof(dptr->raidpacktable[0]));
	bo.write((char*)dptr->playertable,dptr->playertablemax*sizeof(dptr->playertable[0]));
	bo.write((char*)dptr->playerdescspace,dptr->maxplayerdesc*sizeof(dptr->playerdescspace[0]));
	return bo;
}

BIStream&	operator>>(BIStream&	bi, Diary::Master* dptr)
{
	bi.read((char*)dptr,sizeof(*dptr));
	dptr->gruppentable = new Diary::Gruppen[dptr->gruppentablemax];
	if (dptr->gruppentable)
		bi.read((char*)dptr->gruppentable,dptr->gruppentablemax*sizeof(Diary::Gruppen));

	dptr->squadtable = new Diary::Squadron[dptr->squadtablemax];
	if (dptr->squadtable)
		bi.read((char*)dptr->squadtable,dptr->squadtablemax*sizeof(Diary::Squadron));

	dptr->intercepttable = new Diary::Intercept[dptr->intercepttablemax];
	if (dptr->intercepttable)
		bi.read((char*)dptr->intercepttable,dptr->intercepttablemax*sizeof(Diary::Intercept));

	dptr->raidgrouptable = new Diary::RaidGroup[dptr->raidgroupmax];
	if (dptr->raidgrouptable)
		bi.read((char*)dptr->raidgrouptable,dptr->raidgroupmax*sizeof(Diary::RaidGroup));

	dptr->raidpacktable = new Diary::RaidPack[dptr->raidpackmax];
	if (dptr->raidpacktable)
		bi.read((char*)dptr->raidpacktable,dptr->raidpackmax*sizeof(Diary::RaidPack));

	dptr->playertable = new Diary::Player[dptr->playertablemax];
	if (dptr->playertable)
		bi.read((char*)dptr->playertable,dptr->playertablemax*sizeof(Diary::Player));

	dptr->playerdescspace = new char[dptr->maxplayerdesc];
	if (dptr->playerdescspace)
		bi.read((char*)dptr->playerdescspace,dptr->maxplayerdesc*sizeof(char));
	
	return bi;
}



static	int	endStatusLookUp[]=
{
	{IDS_L_EFS_NULL},					//EFS_NULL
	{IDS_EFS_LandedOK},				//EFS_LandedOK,		
	{IDS_EFS_LandedOtherAF},		//EFS_LandedOtherAF,
	{IDS_EFS_LandedField},			//EFS_LandedField,	
	{IDS_EFS_DitchedField},			//EFS_DitchedField,	
//DeadCode RJS 30Oct00 	{IDS_EFS_BadCrashAF},					//EFS_BadCrashAF,		
	{IDS_EFS_ACLOST},			//EFS_ACLOST,			
	{IDS_EFS_KIA},				//EFS_KIA,
	{IDS_EFS_BadCrashAF},			//EFS_BadCrashAF,
	{IDS_EFS_PILOTLOST},			//EFS_PILOTLOST,		
	{IDS_EFS_Parachute}			//EFS_Parachute,		
};


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Load
//Author		Robert Slater
//Date			Fri 28 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::Load(BIStream&	loadfile)
{
	delete diaryptr;

	diaryptr = new Diary::Master;
	if (diaryptr)
		loadfile>>diaryptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Save
//Author		Robert Slater
//Date			Fri 28 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::Save(BOStream&	savefile)
{
	if (diaryptr)
	{
// Give us extra space...

		NewDay_RaidPack();
		NewDay_RaidGroup();
		NewDay_Gruppen();
		NewDay_Intercept();
		NewDay_Squad();
		NewDay_Player();
		NewDay_Desc(D1DAY_PLAYERDESC);

		savefile<<diaryptr;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		New
//Author		Robert Slater
//Date			Fri 28 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::New()
{
	diaryptr = new Diary::Master;
	if (diaryptr)
	{
		NewDay_RaidPack();
		NewDay_RaidGroup();
		NewDay_Gruppen();
		NewDay_Intercept();
		NewDay_Squad();
	}

	NewSession();														//RJS 30Oct00	

	isQuickMission = false;												//RJS 9Nov00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewDay_RaidPack
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::NewDay_RaidPack()
{
	if ((diaryptr->raidpackmax-diaryptr->raidpacknext) < D1DAY_RAIDPACK)
	{
		SLong	newamount = diaryptr->raidpackmax+D1DAY_RAIDPACK;

		RaidPack*	tmpptr = new RaidPack[newamount];
		if (tmpptr)
		{
			RaidPack*	oldptr = diaryptr->raidpacktable;
			SLong		oldmax = diaryptr->raidpackmax;

			diaryptr->raidpacktable = tmpptr;
			diaryptr->raidpackmax = newamount;

			for (int i=0; i < oldmax; i++)
				tmpptr[i] = oldptr[i];

			delete [] oldptr;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewDay_RaidGroup
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::NewDay_RaidGroup()
{
	if ((diaryptr->raidgroupmax-diaryptr->raidgroupnext) < D1DAY_RAIDGRP)
	{
		SLong	newamount = diaryptr->raidgroupmax+D1DAY_RAIDGRP;

		RaidGroup*	tmpptr = new RaidGroup[newamount];
		if (tmpptr)
		{
			RaidGroup*	oldptr = diaryptr->raidgrouptable;
			SLong		oldmax = diaryptr->raidgroupmax;

			diaryptr->raidgrouptable = tmpptr;
			diaryptr->raidgroupmax = newamount;

			for (int i=0; i < oldmax; i++)
				tmpptr[i] = oldptr[i];

			delete [] oldptr;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewDay_Gruppen
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::NewDay_Gruppen()
{
	if ((diaryptr->gruppentablemax-diaryptr->gruppentablenext) < D1DAY_GRUPPEN)
	{
		SLong	newamount = diaryptr->gruppentablemax+D1DAY_GRUPPEN;

		Gruppen*	tmpptr = new Gruppen[newamount];
		if (tmpptr)
		{
			Gruppen*	oldptr = diaryptr->gruppentable;
			SLong		oldmax = diaryptr->gruppentablemax;

			diaryptr->gruppentable = tmpptr;
			diaryptr->gruppentablemax = newamount;

			for (int i=0; i < oldmax; i++)
				tmpptr[i] = oldptr[i];

			delete [] oldptr;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewDay_Intercept
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::NewDay_Intercept()
{
	if ((diaryptr->intercepttablemax-diaryptr->intercepttablenext) < D1DAY_INTERCEPT)
	{
		SLong	newamount = diaryptr->intercepttablemax+D1DAY_INTERCEPT;

		Intercept*	tmpptr = new Intercept[newamount];
		if (tmpptr)
		{
			Intercept*	oldptr = diaryptr->intercepttable;
			SLong		oldmax = diaryptr->intercepttablemax;

			diaryptr->intercepttable = tmpptr;
			diaryptr->intercepttablemax = newamount;

			for (int i=0; i < oldmax; i++)
				tmpptr[i] = oldptr[i];

			delete [] oldptr;
		}
	}	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewDay_Squad
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::NewDay_Squad()
{
	if ((diaryptr->squadtablemax-diaryptr->squadtablenext) < D1DAY_SQUAD)
	{
		SLong	newamount = diaryptr->squadtablemax+D1DAY_SQUAD;

		Squadron*	tmpptr = new Squadron[newamount];
		if (tmpptr)
		{
			Squadron*	oldptr = diaryptr->squadtable;
			SLong		oldmax = diaryptr->squadtablemax;

			diaryptr->squadtable = tmpptr;
			diaryptr->squadtablemax = newamount;

			for (int i=0; i < oldmax; i++)
				tmpptr[i] = oldptr[i];

			delete [] oldptr;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewDay_Player
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::NewDay_Player()
{
	if ((diaryptr->playertablemax-diaryptr->playertablenext) < D1DAY_PLAYER)
	{
		SLong	newamount = diaryptr->playertablemax+D1DAY_PLAYER;

		Player*	tmpptr = new Player[newamount];
		if (tmpptr)
		{
			Player*	oldptr = diaryptr->playertable;
			SLong	oldmax = diaryptr->playertablemax;

			diaryptr->playertable = tmpptr;
			diaryptr->playertablemax = newamount;

			for (int i=0; i < oldmax; i++)
				tmpptr[i] = oldptr[i];

			delete [] oldptr;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewDay_Desc
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		Diary::NewDay_Desc(int	nochars)
{
	if ((diaryptr->maxplayerdesc-diaryptr->nextplayerdesc) < D1DAY_PLAYERDESC)
	{
		if (diaryptr->maxplayerdesc < 65536)
		{
			SLong	newamount = diaryptr->maxplayerdesc+nochars;

			char*	tmpptr = new char[newamount];
			if (tmpptr)
			{
				char*	oldptr = diaryptr->playerdescspace;
				SLong	oldmax = diaryptr->maxplayerdesc;

				diaryptr->playerdescspace = tmpptr;
				diaryptr->maxplayerdesc = newamount;

				for (int i=0; i < oldmax; i++)
					tmpptr[i] = oldptr[i];

				tmpptr[oldmax] = 0;

				delete []oldptr;
			}
		}
		else
			diaryptr->nextplayerdesc = 0;
	}

	return diaryptr->nextplayerdesc;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DiaryEntry_Gruppen
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	Diary::AllocateGruppen(SLong	squadno, UWord raidgroupindex, ULong&	index)
{
	int		realindex;
	bool	retval = false;
	bool	foundone = false;

	for (realindex = diaryptr->raidgrouptable[raidgroupindex].firstgruppenrec; realindex <= diaryptr->gruppentablenext; realindex++)	//RJS 11Sep00
	{
		if (squadno == diaryptr->gruppentable[realindex].squadnum)
		{
			foundone = true;
			break;
		}
	}

	if (!foundone)
	{
		retval = true;

		diaryptr->gruppentablenext++;
	
		realindex = diaryptr->gruppentablenext;
		if (realindex >= diaryptr->gruppentablemax)
			NewDay_Gruppen();

		diaryptr->gruppentable[realindex].diaryraidgroupindex = raidgroupindex;
		diaryptr->gruppentable[realindex].squadnum = squadno;
	}

	index = realindex;

	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DiaryEntry_Squadron
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		Diary::AllocateSquadron(SLong intercept, SLong squadnum)
{
	ULong	realindex;

	diaryptr->squadtablenext++;
	realindex = diaryptr->squadtablenext;

	if (realindex >= diaryptr->squadtablemax)
		NewDay_Squad();

	diaryptr->squadtable[realindex].diaryinterceptindex = UWord(intercept);
	diaryptr->squadtable[realindex].squadnum = squadnum;		//RDH 21Feb00

	return realindex;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllocateIntercept
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		Diary::AllocateIntercept(SLong raidgroup, SLong takeOffTime)
{
	int		index;
//DeadCode RJS 29Aug00 	ULong	raidpackindex = diaryptr->raidgrouptable[raidgroup].diaryraidpackindex;
//DeadCode RJS 29Aug00 	bool	foundone = false;
//DeadCode RJS 29Aug00 
//DeadCode RJS 29Aug00 	for (index=diaryptr->raidpacktable[raidpackindex].firstinterceptrec;index<diaryptr->intercepttablenext;index++)
//DeadCode RJS 29Aug00 	{
//DeadCode RJS 29Aug00 		if (diaryptr->intercepttable[index].diaryraidindex == raidgroup)
//DeadCode RJS 29Aug00 		{
//DeadCode RJS 29Aug00 			foundone = true;
//DeadCode RJS 29Aug00 			break;
//DeadCode RJS 29Aug00 		}
//DeadCode RJS 29Aug00 	}
//DeadCode RJS 29Aug00 
//DeadCode RJS 29Aug00 	if (!foundone)
//DeadCode RJS 29Aug00 	{
//DeadCode RJS 7Sep00 		RaidPack*	packptr = GetRaidPack(&diaryptr->raidgrouptable[raidgroup]);

		diaryptr->intercepttablenext++;
		index = diaryptr->intercepttablenext;

		if (index >= diaryptr->intercepttablemax)
			NewDay_Intercept();

		diaryptr->intercepttable[index].diaryraidindex = UWord(raidgroup);
		diaryptr->intercepttable[index].firstsquadronrec = UWord(diaryptr->squadtablenext+1);
		diaryptr->intercepttable[index].takeofftime = takeOffTime;		//RJS 7Sep00

//DeadCode RJS 7Sep00 		if (packptr)
//DeadCode RJS 7Sep00 			diaryptr->intercepttable[index].takeofftime = packptr->takeofftime;
//DeadCode RJS 29Aug00 	}

	return index;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllocateIntercept
//Author		R. Hyde 
//Date			Mon 21 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		Diary::AllocateIntercept(RaidGroup* groupptr, SLong takeOffTime)
{
	if (groupptr)
	{
		int	rubbishfix = diaryptr->raidpacktable[groupptr->diaryraidpackindex].firstraidgrouprec;

		return AllocateIntercept(rubbishfix,takeOffTime);				//RJS 7Sep00
	}
	
	return -1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllocateRaidPack
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		Diary::AllocateRaidPack()
{
	SLong	index;

	diaryptr->raidpacknext++;
	index = diaryptr->raidpacknext;
	if (index >= diaryptr->raidpackmax)
		NewDay_RaidPack();

	diaryptr->raidpacktable[index].firstraidgrouprec = diaryptr->raidgroupnext+1;
	diaryptr->raidpacktable[index].firstinterceptrec = diaryptr->intercepttablenext+1;

	return index;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllocateRaidGroup
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		Diary::AllocateRaidGroup(SLong	raidpack)
{
	SLong	index;

	diaryptr->raidgroupnext++;
	index = diaryptr->raidgroupnext;
	if (index >= diaryptr->raidgroupmax)
		NewDay_RaidGroup();

	diaryptr->raidgrouptable[index].diaryraidpackindex = UWord(raidpack);
	diaryptr->raidgrouptable[index].firstgruppenrec = DIARY_EMPTYINDEX;	//RJS 14Sep00

	return diaryptr->raidgroupnext;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllocatePlayer
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		Diary::AllocatePlayer(SLong	diaryentry,bool isLW)
{
	SLong	index;

	diaryptr->playertablenext++;
	index = diaryptr->playertablenext;
	if (index >= diaryptr->playertablemax)
		NewDay_Player();

	diaryptr->playerIsGruppen = isLW;			//RJS 18Feb00

	diaryptr->playertable[index].diarysquadindex = UWord(diaryentry&DIARYMASK);
//DeadCode RJS 18Feb00	diaryptr->playertable[index].isGruppen = isLW;
	diaryptr->playertable[index].descriptionstringindex = UWord(AllocateDesc());

	return index;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllocateDesc
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		Diary::AllocateDesc()
{
	SLong	index;

	diaryptr->prevplayerdesc = diaryptr->nextplayerdesc;
	diaryptr->nextplayerdesc += D1DAY_PLAYERDESC;
	index = diaryptr->nextplayerdesc;
	if (index >= diaryptr->maxplayerdesc)
		index = NewDay_Desc(D1DAY_PLAYERDESC);

	return index;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateEntry
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::CreateEntry(PackageList	&packlist, SLong packno)
{
	isQuickMission = false;												//RJS 9Nov00

	if (packlist[packno].attackmethod >= Profile::AM_LWPACKS)
		CreateLWEntry(&packlist[packno]);
	else
		CreateRAFEntry(&packlist[0],packno);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateLWEntry
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::CreateLWEntry(Profile*	theProfile)
{
	if (!_Replay.Playback)												//RJS 21Jun00
	{
		SLong			raidpack = AllocateRaidPack();
		UniqueID		doglegloc = theProfile->doglegloc;
		int				nosquads = theProfile->squadlist;
		Profile::Squad*	squaddy = &theProfile->squadlist[0];
//DeadCode JIM 20Oct00 		SLong			notargets = 0;
		const SLong			maxtargets = Profile::MAX_TARGETS+Profile::MAX_NEGTARGETS;
		SLong			raidgroup;
		SLong			raidgroupsize;
		UWord			raidgroupids[maxtargets];

		diaryptr->raidpacktable[raidpack].doglegpos = UWord(doglegloc);
		diaryptr->raidpacktable[raidpack].date = UWord(MMC.currdate / SECSPERDAY);
		diaryptr->raidpacktable[raidpack].takeofftime = MMC.currtime;

		if (raidgroupids)
		{
			ULong	gruppenindex;
			UWord	raidgroupno;

			for (SLong trgno = 0; trgno < maxtargets; trgno++)
			{
				raidgroupids[trgno]=0xffff;

//DEADCODE DAW 15/05/00 			if (theProfile->packagetarget[trgno].currentid == UID_NULL)
//DEADCODE DAW 15/05/00 				break;
//DEADCODE DAW 15/05/00 			else
//DEADCODE DAW 15/05/00 			{
//DEADCODE DAW 15/05/00 				raidgroupids[trgno] = AllocateRaidGroup(raidpack);
//DEADCODE DAW 15/05/00 				diaryptr->raidgrouptable[raidgroupids[trgno]].target = theProfile->packagetarget[trgno].currentid; 
//DEADCODE DAW 15/05/00 				diaryptr->raidgrouptable[raidgroupids[trgno]].targettime = theProfile->primarytargetETA + theProfile->playerETAdelta;
//DEADCODE DAW 15/05/00 				notargets++;
//DEADCODE DAW 15/05/00 			}
			}

//DEADCODE DAW 15/05/00 		if (notargets)
			{
				for (int squadcnt = 0; squadcnt < nosquads; squadcnt++)
				{
					int trgno=squaddy->targetindex+Profile::MAX_NEGTARGETS;
					if ((squaddy->method & Profile::AM_GROUPMASK) == Profile::AM_DETACHED)	//RJS 16Nov00
						trgno = -2 + Profile::MAX_NEGTARGETS;			//RJS 16Nov00

					raidgroupno = raidgroupids[trgno];
					if (raidgroupno==0xffff)
					{
						raidgroupids[trgno] = 
							raidgroupno =
								AllocateRaidGroup(raidpack);

						diaryptr->raidgrouptable[raidgroupno].target = theProfile->packagetarget[trgno].currentid; 
						diaryptr->raidgrouptable[raidgroupno].targettime = theProfile->primarytargetETA + theProfile->playerETAdelta;
						diaryptr->raidgrouptable[raidgroupno].firstgruppenrec = diaryptr->gruppentablenext + 1;//RJS 14Sep00

// Set it up once...
						MissType	misstype = MT_RECON;				//RJS 20Oct00

						switch (squaddy->method)
						{
						case Profile::AM_PATROL:	//raf only
						case Profile::AM_INTERCEPT:	//raf only
							break;
						case Profile::AM_RECON:
							misstype = MT_RECON;
							break;
						case Profile::AM_DIVEBOMB:
						case Profile::AM_LEVELBOMB:
							misstype = MT_RAID;
							break;
						default:
						{
							if (squaddy->method >= Profile::AM_DETACHED)
							{
								if (squaddy->method < Profile::AM_ATTACHED)
									misstype = MT_ESCORT;
								else
									misstype = MT_CLOSEESCORT;
							}
						}
						break;
						}

						diaryptr->raidgrouptable[raidgroupno].misstype = misstype;
					}
					
					AllocateGruppen(squaddy->squadnum,raidgroupno,gruppenindex);	//RJS 16Nov00
//DeadCode RJS 16Nov00 					if (AllocateGruppen(squaddy->squadnum,raidgroupno,gruppenindex))	//RJS 16Nov00
//DeadCode RJS 16Nov00 					{
//DeadCode RJS 16Nov00 						// New one...
//DeadCode RJS 16Nov00 						MissType	misstype = MT_RECON;				//RJS 20Oct00
//DeadCode RJS 16Nov00 
//DeadCode RJS 16Nov00 						switch (squaddy->method)
//DeadCode RJS 16Nov00 						{
//DeadCode RJS 16Nov00 						case Profile::AM_PATROL:	//raf only
//DeadCode RJS 16Nov00 						case Profile::AM_INTERCEPT:	//raf only
//DeadCode RJS 16Nov00 							break;
//DeadCode RJS 16Nov00 						case Profile::AM_RECON:
//DeadCode RJS 16Nov00 							misstype = MT_RECON;
//DeadCode RJS 16Nov00 							break;
//DeadCode RJS 16Nov00 						case Profile::AM_DIVEBOMB:
//DeadCode RJS 16Nov00 						case Profile::AM_LEVELBOMB:
//DeadCode RJS 16Nov00 							misstype = MT_RAID;
//DeadCode RJS 16Nov00 							break;
//DeadCode RJS 16Nov00 						default:
//DeadCode RJS 16Nov00 						{
//DeadCode RJS 16Nov00 							if (squaddy->method >= Profile::AM_DETACHED)
//DeadCode RJS 16Nov00 							{
//DeadCode RJS 16Nov00 								if (squaddy->method < Profile::AM_ATTACHED)
//DeadCode RJS 16Nov00 									misstype = MT_ESCORT;
//DeadCode RJS 16Nov00 								else
//DeadCode RJS 16Nov00 									misstype = MT_CLOSEESCORT;
//DeadCode RJS 16Nov00 							}
//DeadCode RJS 16Nov00 						}
//DeadCode RJS 16Nov00 						break;
//DeadCode RJS 16Nov00 						}
//DeadCode RJS 16Nov00 
//DeadCode RJS 16Nov00 						diaryptr->raidgrouptable[raidgroupno].misstype = misstype;
//DeadCode RJS 16Nov00 					}

					diaryptr->gruppentable[gruppenindex].noaclaunched += squaddy->numacoriginal;

					squaddy->diaryentry = gruppenindex | GRUPPENMASK;
					squaddy++;
				}
			}
			theProfile->firstsquaddiaryentry=theProfile->squadlist[0].diaryentry;
//DeadCode JIM 16Sep00 			delete [] raidgroupids;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateRAFEntry
//Author		Robert Slater
//Date			Wed 26 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::CreateRAFEntry(Profile*	startProfile, SLong packno)
{
	if (!_Replay.Playback)												//RJS 21Jun00
	{
		Profile*		thisProfile = &startProfile[packno];
		int				nosquads = thisProfile->squadlist;
		int				tmpnosquads;
		Profile::Squad*	squaddy = &thisProfile->squadlist[0];
		Profile::Squad*	tmpSquad;
		Profile*		tmpProfile;
		ULong			gruppenindex;
		UWord			raidgroupno;
		int				interceptno = -1;								//RJS 20Oct00
		int				acIndex = 0;

// Create only 1 instance of the intercept...
		if (nosquads)											//RJS 29Aug00
		{
//DeadCode RJS 5Oct00 			UniqueID	target = thisProfile->packagetarget[squaddy->targetindex];
			UniqueID	target = thisProfile->packagetarget[1];

//DeadCode RJS 20Oct00 			interceptno = -1;
		//	if (target)
			{
				int	lwpack,sqnum;
				UniqueID	trguid = target;

				int uidband=Persons2::getbandfromUID(trguid);	
				if (uidband != SagBAND)
				{
					trguid = thisProfile->packagetarget[0];
					uidband=Persons2::getbandfromUID(trguid);	
				}

				if (uidband == SagBAND)
				{
					if (Todays_Packages.GetACSquadEntry(trguid,lwpack,sqnum))
					{
						Profile& lwpk = Todays_Packages.pack[lwpack];
					
						tmpSquad = &lwpk.squadlist[sqnum];
//DeadCode RJS 5Oct00 					}
//DeadCode RJS 5Oct00 				}
//DeadCode RJS 5Oct00 
//DeadCode RJS 5Oct00 				tmpProfile = startProfile;
//DeadCode RJS 5Oct00 				for (int profcnt=0;profcnt<Profile::MAX_PACKS;profcnt++)
//DeadCode RJS 5Oct00 				{
//DeadCode RJS 5Oct00 					if (	(tmpProfile->packagestatus != Profile::PS_SPARE)
//DeadCode RJS 5Oct00 						&&	(profcnt != packno)								)
//DeadCode RJS 5Oct00 					{
//DeadCode RJS 5Oct00 						tmpnosquads = tmpProfile->squadlist;
//DeadCode RJS 5Oct00 						tmpSquad = &tmpProfile->squadlist[0];
//DeadCode RJS 5Oct00 						for (int tmpsno=0; tmpsno < tmpnosquads; tmpsno++)
//DeadCode RJS 5Oct00 						{
//DeadCode RJS 5Oct00 							if (tmpSquad->instance == target)
//DeadCode RJS 5Oct00 							{
								gruppenindex = tmpSquad->diaryentry;
								if (gruppenindex != 0xFFFFFFFF)
								{
									raidgroupno = diaryptr->gruppentable[gruppenindex&DIARYMASK].diaryraidgroupindex;
									interceptno = AllocateIntercept(raidgroupno,squaddy->takeofftime);	//RJS 7Sep00

									acIndex = lwpk.squadlist.AcBitsFirstSquad();					//RDH 12/05/00
									diaryptr->intercepttable[interceptno].leadthere = ((acIndex&1)==1);	//RDH 12/05/00
								}
//DeadCode RJS 5Oct00 								break;
//DeadCode RJS 5Oct00 							}
//DeadCode RJS 5Oct00 
//DeadCode RJS 5Oct00 							tmpSquad++;
//DeadCode RJS 5Oct00 						}
//DeadCode RJS 5Oct00 
//DeadCode RJS 5Oct00 						if (tmpsno < tmpnosquads)
//DeadCode RJS 5Oct00 							break;
					}
//DeadCode RJS 5Oct00 					tmpProfile++;
				}
			}

			// if we haven't found any baddies to intercept, then just go on the last patrol
			if (interceptno < 0)
			{
				RaidPack*	patrolpack = GetFirstRaidPack(MMC.currdate);
				RaidGroup*	patrolgrp = GetFirstRaidGroup(patrolpack);

				interceptno = AllocateIntercept(patrolgrp,MMC.currtime);	//RJS 7Sep00

				diaryptr->intercepttable[interceptno].waspatrolinitially = true;	//RJS 23Feb00
			}
		}

// Set this intercept for all sqaddies...
		for (int squadcnt = 0; squadcnt < nosquads; squadcnt++)
		{
			squaddy->diaryentry = AllocateSquadron(interceptno,squaddy->squadnum);

			diaryptr->squadtable[squaddy->diaryentry].takeoffairfield = UniqueID(squaddy->Squadron().homeairfield);
			diaryptr->squadtable[squaddy->diaryentry].noaclaunched += squaddy->numacoriginal;

			squaddy++;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GruppenSearch
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SquadronBase*	Diary::GruppenSearch(SquadronBase*	ptr, UWord squadno,DSearchDir sdir)
{
	Gruppen*		gptr = (Gruppen*)ptr;
	SquadronBase*	newgptr = NULL;

	if (sdir == DSEARCH_BACK)
	{
		while (gptr > diaryptr->gruppentable)
		{
			gptr--;
			if (gptr->squadnum == squadno)
			{
				newgptr = (SquadronBase*)gptr;
				break;
			}
		}
	}
	else
	{
		while (gptr <= &diaryptr->gruppentable[diaryptr->gruppentablenext])
		{
			gptr++;
			if (gptr->squadnum == squadno)
			{
				newgptr = (SquadronBase*)gptr;
				break;
			}
		}
	}

	return newgptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SquadronSearch
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SquadronBase*	Diary::SquadronSearch(SquadronBase*	ptr, UWord squadno,DSearchDir sdir)
{
	Squadron*		sptr = (Squadron*)ptr;
	SquadronBase*	newsptr = NULL;

	if (sdir == DSEARCH_BACK)
	{
		while (sptr > diaryptr->squadtable)
		{
			sptr--;
			if (sptr->squadnum == squadno)
			{
				newsptr = (SquadronBase*)sptr;
				break;
			}
		}
	}
	else
	{
		while (sptr <= &diaryptr->squadtable[diaryptr->squadtablenext])
		{
			sptr++;
			if (sptr->squadnum == squadno)
			{
				newsptr = (SquadronBase*)sptr;
				break;
			}
		}
	}

	return newsptr;
}

// User Interface Functions....

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindLast
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SquadronBase*		Diary::FindLast(SquadNum	squadno)
{
	SquadronBase*	newptr = NULL;
	SquadronBase*	ptr;

	if (squadno >= SQ_LW_START)
	{
		ptr = (SquadronBase*)&diaryptr->gruppentable[diaryptr->gruppentablenext+1];

		newptr = GruppenSearch(ptr,squadno);
	}
	else
	{
		ptr = (SquadronBase*)&diaryptr->squadtable[diaryptr->squadtablenext+1];

		newptr = SquadronSearch(ptr,squadno);
	}

	return newptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindPrev
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	previous for same squadno
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SquadronBase*		Diary::FindPrev(SquadronBase*	ptr)
{
	SquadronBase*	newptr = NULL;

	if (ptr)
	{
		if (ptr->squadnum >= SQ_LW_START)
			newptr = GruppenSearch(ptr,ptr->squadnum);
		else
			newptr = SquadronSearch(ptr,ptr->squadnum);
	}

	return newptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFirst
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SquadronBase*		Diary::FindFirst(SquadNum	squadno)
{
	SquadronBase*	newptr = NULL;
	SquadronBase*	ptr;

	if (squadno >= SQ_LW_START)
	{
		ptr = (SquadronBase*)diaryptr->gruppentable;

		newptr = GruppenSearch(ptr,squadno,DSEARCH_FORWARD);
	}
	else
	{
		ptr = (SquadronBase*)diaryptr->squadtable;

		newptr = SquadronSearch(ptr,squadno,DSEARCH_FORWARD);
	}

	return newptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindNext
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SquadronBase*		Diary::FindNext(SquadronBase*	ptr)
{
	SquadronBase*	newptr = NULL;

	if (ptr)
	{
		if (ptr->squadnum >= SQ_LW_START)
			newptr = GruppenSearch(ptr,ptr->squadnum,DSEARCH_FORWARD);
		else
			newptr = SquadronSearch(ptr,ptr->squadnum,DSEARCH_FORWARD);
	}

	return newptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRaidGroup
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::RaidGroup*	Diary::GetRaidGroup(SquadronBase*	ptr)
{
	RaidGroup*	grpptr = NULL;

	if (ptr)
	{
		if (ptr->squadnum >= SQ_LW_START)
			grpptr = &diaryptr->raidgrouptable[((Gruppen*)ptr)->diaryraidgroupindex];
		else
		{
			Intercept*	intptr = &diaryptr->intercepttable[((Squadron*)ptr)->diaryinterceptindex];
			grpptr = &diaryptr->raidgrouptable[intptr->diaryraidindex];
		}
	}
		
	return grpptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRaidPack
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::RaidPack*	Diary::GetRaidPack(Diary::RaidGroup*	ptr)
{
	if (ptr)
		return &diaryptr->raidpacktable[ptr->diaryraidpackindex];

	return NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFirstRaidGroup
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::RaidGroup*	Diary::GetFirstRaidGroup(Diary::RaidPack*	ptr)
{
	if (ptr && (ptr->firstraidgrouprec != DIARY_EMPTYINDEX))
		return &diaryptr->raidgrouptable[ptr->firstraidgrouprec];

	return NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNextRaidGroup
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::RaidGroup*	Diary::GetNextRaidGroup(Diary::RaidGroup*	ptr)
{
	if (ptr)
	{
		UWord	raidpack = ptr->diaryraidpackindex;					//RJS 15May00

		ptr++;
		if (	(ptr->diaryraidpackindex != DIARY_EMPTYINDEX)
			&&	(ptr->diaryraidpackindex == raidpack)			)
			return ptr;
	}	

	return NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFirstIntercept
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Intercept*	Diary::GetFirstIntercept(Diary::RaidGroup*	ptr)
{
	Intercept*	iptr = NULL;
	if (ptr)
	{
		RaidPack*	rpackptr = GetRaidPack(ptr);
		if (rpackptr)
		{
			if (rpackptr->firstinterceptrec != DIARY_EMPTYINDEX)
			{
				iptr = &diaryptr->intercepttable[rpackptr->firstinterceptrec];
				if (iptr->diaryraidindex == DIARY_EMPTYINDEX)
					iptr = NULL;
			}
		}
	}

	return iptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetIntercept
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Intercept*	Diary::GetIntercept(SquadronBase*	ptr)
{
	Intercept*	iptr = NULL;

	if (ptr && (ptr->squadnum < SQ_LW_START))
	{
		Squadron*	sptr = (Squadron*)ptr;
		if (sptr->diaryinterceptindex != DIARY_EMPTYINDEX)
			iptr = &diaryptr->intercepttable[sptr->diaryinterceptindex];
	}

	return iptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNextIntercept
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Intercept*	Diary::GetNextIntercept(Diary::Intercept*	ptr)
{
	if (ptr)
	{
		UWord	raidgrp = ptr->diaryraidindex;

		ptr++;
		if (	(ptr->diaryraidindex != DIARY_EMPTYINDEX)
			&&	(ptr->diaryraidindex == raidgrp)			)
			return ptr;
	}

	return NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFirstSquadron
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Gruppen*		Diary::GetFirstSquadron(Diary::RaidGroup*	ptr)
{
	Gruppen*	gptr = NULL;

	if (ptr && (ptr->firstgruppenrec != DIARY_EMPTYINDEX))
	{
		gptr = &diaryptr->gruppentable[ptr->firstgruppenrec];
		if (gptr->diaryraidgroupindex == DIARY_EMPTYINDEX)
			gptr = NULL;
	}

	return gptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFirstSquadron
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Squadron*	Diary::GetFirstSquadron(Diary::Intercept*	ptr)
{
	Squadron*	sptr = NULL;

	if (ptr && (ptr->firstsquadronrec != DIARY_EMPTYINDEX))
	{
		sptr = &diaryptr->squadtable[ptr->firstsquadronrec];
		if (sptr->diaryinterceptindex == DIARY_EMPTYINDEX)
			sptr = NULL;
	}

	return sptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNextSquadron
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Gruppen*		Diary::GetNextSquadron(Diary::Gruppen*	ptr)
{
	if (ptr)
	{
		UWord	raidgrpno = ptr->diaryraidgroupindex;				//RJS 15May00

		ptr++;
		if (	(ptr->diaryraidgroupindex == DIARY_EMPTYINDEX)
			||	(ptr->diaryraidgroupindex != raidgrpno)	)
			ptr = NULL;
	}

	return ptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNextSquadron
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Squadron*	Diary::GetNextSquadron(Diary::Squadron*	ptr)
{
	if (ptr)
	{
		UWord	interceptno = ptr->diaryinterceptindex;				//RJS 15May00

		ptr++;
		if (	(ptr->diaryinterceptindex == DIARY_EMPTYINDEX)
			||	(ptr->diaryinterceptindex != interceptno)		)
			ptr = NULL;
	}

	return ptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreatePlayer
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Player*	Diary::CreatePlayer(SquadronBase*	sptr)
{
//DEADCODE RDH 17/05/00 	char			index =	tp.hipack;
//DEADCODE RDH 17/05/00 	Player*			playerptr = NULL;
//DEADCODE RDH 17/05/00 	Profile*		packptr = &tp[index];
//DEADCODE RDH 17/05/00 
//DEADCODE RDH 17/05/00 	if (packptr->packagestatus != Profile::PS_SPARE)
//DEADCODE RDH 17/05/00 	{
//DEADCODE RDH 17/05/00 		int				sqindex = tp.hisquad;
//DEADCODE RDH 17/05/00 		SLong			newplayer = -1;
//DEADCODE RDH 17/05/00 		Profile::Squad*	squaddy = &packptr->squadlist[sqindex];
//DEADCODE RDH 17/05/00 
//DEADCODE RDH 17/05/00 		if (squaddy->diaryentry != 0xFFFFFFFF)
//DEADCODE RDH 17/05/00 			newplayer = AllocatePlayer(SLong(squaddy->diaryentry),(squaddy->squadnum>=SQ_LW_START));
//DEADCODE RDH 17/05/00 
//DEADCODE RDH 17/05/00 		if (newplayer != -1)
//DEADCODE RDH 17/05/00 			playerptr = &diaryptr->playertable[diaryptr->playertablenext];
//DEADCODE RDH 17/05/00 
//DEADCODE RDH 17/05/00 		lastplayerstatus = EFS_NULL;
//DEADCODE RDH 17/05/00 	}

	Player*			playerptr = NULL;
	if (!_Replay.Playback)												//RJS 21Jun00
	{
		if (sptr)
		{
			SLong	newplayer;
			ULong	diaryindex;
			bool	isLW = (sptr->squadnum>=SQ_LW_START);

			if (isLW)
			{
				diaryindex = (UByteP(sptr) - UByteP(diaryptr->gruppentable))/sizeof(Gruppen);
				diaryindex |= GRUPPENMASK;
			}
			else
				diaryindex = (UByteP(sptr) - UByteP(diaryptr->squadtable))/sizeof(Squadron);

			newplayer = AllocatePlayer(SLong(diaryindex),isLW);
			if (newplayer > -1)
				playerptr = &diaryptr->playertable[diaryptr->playertablenext];

			lastplayerstatus = EFS_NULL;
		}
	}

	toBeKilled = 0;														//RJS 4Sep00

	return playerptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFirstPlayer
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Player*		Diary::GetFirstPlayer(SquadronBase*	ptr)
{
	Player*	retval = NULL;
	if (ptr)
	{
		Player*			tmpptr = GetFirstPlayer();
		SquadronBase*	tmpsquad;

		while (tmpptr)
		{
			tmpsquad = GetSquadron(tmpptr);
			if (!tmpsquad)
				break;
			else
			{
				if (tmpsquad == ptr)
				{
					retval = tmpptr;
					break;
				}
				else
					tmpptr++;
			}
		}
	}
	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNextPlayerInSq
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Player*		Diary::GetNextPlayerInSq(Diary::Player*	ptr)
{
	Player*	retval = NULL;
	if (ptr)
	{
		SquadronBase* sptr = GetSquadron(ptr);
		if (sptr)
		{
			UWord	squadnum = sptr->squadnum;
			Player*	tmpptr = ptr;

			while (sptr)
			{
				tmpptr++;
				sptr = GetSquadron(tmpptr);
				if (sptr)
				{
					if (sptr->squadnum == squadnum)
					{
						retval = tmpptr;
						break;
					}
				}
			}
		}
	}
	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFirstPlayer
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Player*		Diary::GetFirstPlayer()
{
	Player*	retval = NULL;
	if (diaryptr->nextplayerdesc != -1)
		retval = diaryptr->playertable;

	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFirstPlayerInDay
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Player*		Diary::GetFirstPlayerInDay(int day)
{
	Player*			retval = NULL;
	Player*			tmpptr;
	SquadronBase*	sptr;
	RaidPack*		rptr;

	tmpptr = GetFirstPlayer();
	if (tmpptr)
	{
		do
		{
			sptr = GetSquadron(tmpptr);
			if (sptr)
			{
				rptr = GetRaidPack(GetRaidGroup(sptr));
				if (rptr)
				{
					if (rptr->date == day)
					{
						retval = tmpptr;
						break;
					}
				}
			}
			tmpptr++;
		}
		while (sptr);
	}

	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNextPlayerInDay
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Player*		Diary::GetNextPlayerInDay(Diary::Player*	ptr)
{
	Player*	retval = NULL;
	if (ptr)
	{
		RaidPack*	rptr = GetRaidPack(GetRaidGroup(GetSquadron(ptr)));
		if (rptr)
		{
			int	day = rptr->date;
			while (rptr)
			{
				ptr++;
				rptr = GetRaidPack(GetRaidGroup(GetSquadron(ptr)));
				if (rptr)
				{
					if (rptr->date == day)
					{
						retval = ptr;
						break;
					}
				}
			}
		}
	}
	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetNextPlayerAll
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Player*		Diary::GetNextPlayerAll(Diary::Player*	ptr)
{
	if (ptr)
	{
		ptr++;
		if (ptr->diarysquadindex == DIARY_EMPTYINDEX)
			ptr = NULL;
	}
	return ptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSquadron
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SquadronBase*		Diary::GetSquadron(Diary::Player*	ptr)
{
	SquadronBase*	retval = NULL;
	if (ptr)
	{
		if (ptr->diarysquadindex != DIARY_EMPTYINDEX)
		{
			if (diaryptr->playerIsGruppen)							//RJS 18Feb00
				retval = (SquadronBase*)&diaryptr->gruppentable[ptr->diarysquadindex];
			else
				retval = (SquadronBase*)&diaryptr->squadtable[ptr->diarysquadindex];
		}
	}
	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDiaryText
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
char*		Diary::GetDiaryText(Diary::Player*	ptr)
{
	char*	textptr = NULL;
	if (ptr)
	{
		if (ptr->descriptionstringindex != DIARY_EMPTYINDEX)
			textptr = &diaryptr->playerdescspace[ptr->descriptionstringindex];
	}
	return textptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TextBufferSize
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns		virtual editable buffer size (up to 64k if we are last entry)
//
//------------------------------------------------------------------------------
int	Diary::TextBufferSize(Player*	ptr, int& editablechars)
{
	int		nochars = 0;
	
	editablechars = 0;
	char*	textptr = GetDiaryText(ptr);
	if (textptr)
	{
		if (ptr->descriptionstringindex == diaryptr->nextplayerdesc)
			editablechars = nochars = 0xFFFF - ptr->descriptionstringindex;
		else
		{
			ptr++;
			char*	nexttextptr = GetDiaryText(ptr);
			if (nexttextptr)
				nochars = nexttextptr-textptr;
			else
				editablechars = nochars = 0xFFFF - (textptr-diaryptr->playerdescspace);
		}

		if (nochars < 0)
			nochars = 0;
	}
	return nochars;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DiaryEditable
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	no chars remaining in editable buffer
//
//------------------------------------------------------------------------------
int			Diary::DiaryEditable(Diary::Player*	ptr)
{
	int		nocharsleft = 0;
	int		nocharseditable = 0;

	nocharsleft = TextBufferSize(ptr,nocharseditable);
	if (nocharsleft)
	{
		char*	textptr = GetDiaryText(ptr);
	 	while (*textptr)
	 	{
	 		nocharsleft--;
	 		textptr++;
		}
	}
	if (!nocharseditable)
		nocharsleft = nocharseditable;

	return nocharsleft;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDiaryText
//Author		Robert Slater
//Date			Thu 27 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void		Diary::SetDiaryText(Player* ptr,const char* externalcopy)	//RDH 24/02/00
{
	char*	textptr = GetDiaryText(ptr);
	if (textptr && externalcopy)
	{
		int	nce;
		int buffersize = TextBufferSize(ptr,nce);
		if (buffersize)
		{
			int	nocharsneeded = strlen(externalcopy);
 			if (nocharsneeded >= buffersize)
				nocharsneeded = buffersize-1;

//DEADCODE RDH 24/02/00 			externalcopy[nocharsneeded] = 0;	//RDH 24/02/00

			if (	(buffersize > D1DAY_PLAYERDESC)
				&&	(ptr->descriptionstringindex == diaryptr->nextplayerdesc)	)
			{
// We can extend if we want, cos we are at the end of the buffer....

				int	realbuffersize = diaryptr->maxplayerdesc-diaryptr->nextplayerdesc;
				if (nocharsneeded > realbuffersize)
				{
					int	newsize = nocharsneeded-realbuffersize;
					int	descsize = newsize;
					descsize /= D1DAY_PLAYERDESC;
					descsize *= D1DAY_PLAYERDESC;
					if (descsize < newsize)
						descsize += D1DAY_PLAYERDESC;

					diaryptr->nextplayerdesc += descsize;
					diaryptr->nextplayerdesc = NewDay_Desc(descsize);

					textptr = GetDiaryText(ptr);
 				}
 			}

			memcpy(textptr,externalcopy, nocharsneeded);				//RDH 24/02/00
			textptr[nocharsneeded] = 0;									//RDH 24/02/00
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRaidPack
//Author		Robert Slater
//Date			Wed 09 Feb 2000
//
//Description	Alternative to getting a raid pack, but with a date as index
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::RaidPack*	Diary::GetFirstRaidPack(int	date)
{
	RaidPack*	ptr = NULL;
	int			index;
	int			searchdate = date / SECSPERDAY;

	for (index = 0; index <= diaryptr->raidpacknext; index++)
	{
		if (diaryptr->raidpacktable[index].date == searchdate)
		{
			ptr = &diaryptr->raidpacktable[index];
			break;
		}
	}

	return ptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateDailyRaidGroup
//Author		Robert Slater
//Date			Wed 09 Feb 2000
//
//Description	Creates dummy raid entry for a patrol...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::CreateDailyRaidGroup(int date)
{
	if (!_Replay.Playback)												//RJS 21Jun00
	{
		SLong			raidpack = AllocateRaidPack();
		SLong			raidgroup;

		diaryptr->raidpacktable[raidpack].doglegpos = 0;
		diaryptr->raidpacktable[raidpack].date = UWord(date / SECSPERDAY);
		diaryptr->raidpacktable[raidpack].takeofftime = 0;

		raidgroup = AllocateRaidGroup(raidpack);
		
		diaryptr->raidgrouptable[raidgroup].target = (UniqueID)0; 
		diaryptr->raidgrouptable[raidgroup].targettime = 0;
		diaryptr->raidgrouptable[raidgroup].misstype = MT_PATROL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRaidGroup
//Author		R. Hyde 
//Date			Mon 21 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::RaidGroup*	Diary::GetRaidGroup(Intercept*	ip)
{
	Diary::RaidGroup*	ptr = NULL;

	if (ip)
		ptr = &diaryptr->raidgrouptable[ip->diaryraidindex];

	return ptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDiaryPtr
//Author		Robert Slater
//Date			Fri 18 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SquadronBase*		Diary::GetDiaryPtr(ULong	diaryindex)
{
	SquadronBase*	ptr = NULL;
	if (diaryindex != 0xFFFFFFFF)
	{
		ULong			diaryindexbody = diaryindex&DIARYMASK;

		if (diaryindex & GRUPPENMASK)
			ptr = (SquadronBase*)&diaryptr->gruppentable[diaryindexbody];
		else
			ptr = (SquadronBase*)&diaryptr->squadtable[diaryindexbody];
	}
	return ptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdatePlayerLog
//Author		Robert Slater
//Date			Mon 21 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void		Diary::UpdatePlayerLog(EndFlightStatus	result)
{
// We can override a lower-priority status...
	if (result > lastplayerstatus)
		lastplayerstatus = result;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdatePlayerLog
//Author		Robert Slater
//Date			Mon 21 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void		Diary::UpdatePlayerLog(AirStruc*	ac)
{
	if (ac && !_Replay.Playback)									//RJS 07Jun00
	{
		Player*	pptr = GetFirstPlayer(ac->ai.diaryptr);
		if (pptr)
		{
			ULong			diaryindex = pptr->diarysquadindex&DIARYMASK;
			SquadronBase*	foundptr;

			if (diaryptr->playerIsGruppen)
				foundptr = (SquadronBase*)&diaryptr->gruppentable[diaryindex];
			else
				foundptr = (SquadronBase*)&diaryptr->squadtable[diaryindex];

			if (foundptr == ac->ai.diaryptr)
			{
				AircraftAnimData*	adptr = (AircraftAnimData*)ac->Anim;

				pptr->specificdamage[DIARY_LEFTWING] = (adptr->LEFTWINGOUT+adptr->LEFTWINGIN)>>1;
				pptr->specificdamage[DIARY_RIGHTWING] = (adptr->RIGHTWINGOUT+adptr->RIGHTWINGIN)>>1;
				pptr->specificdamage[DIARY_ENGINE] = (adptr->ENGINELEFT+adptr->ENGINERIGHT)>>1;
				pptr->specificdamage[DIARY_TAIL] = adptr->TAIL + ((adptr->FINLEFT+adptr->FINRIGHT)>>1);
				pptr->specificdamage[DIARY_CANOPY] = adptr->CANOPY;
				pptr->specificdamage[DIARY_FUSELAGE] = adptr->OTHER;

				pptr->howendedmission = lastplayerstatus;
			}
			else
				_Error.EmitSysErr(__FILE__"Player not matched!");
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetAC
//Author		Robert Slater
//Date			Mon 21 Feb 2000
//
//Description	Cannot be invoked from within a SetKilledAC() death
//
//				Should not reset "current_itemstate" from within nested damage
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::SetAC(void*	itm, animptr&	adptr)
{
	if (!toBeKilled)													//RJS 4Sep00
	{
		if (((ItemPtr)itm)->Status.size == AIRSTRUCSIZE)
		{
			if (current_ac != itm)										//RJS 5Sep00
			{
				if (current_ac)
					INT3;

				current_ac = AirStrucPtr(itm);

				MinAnimData*	mad = (MinAnimData*)adptr;				//RJS 21Sep00
				if (mad->IsInvisible)
					current_itemstate = DEAD;
				else
					current_itemstate = mad->itemstate;

				current_adptr = adptr;									//RJS 3Nov00
				current_pilotcount = SHAPE.GetTotalPilots(current_ac,adptr);
			}
		}
		else
			current_ac = NULL;
	}

	current_depth++;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetACState
//Author		Robert Slater
//Date			Mon 4 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::SetACState(int	newState)
{
	if (current_ac)
	{
		MinAnimData*	mad = (MinAnimData*)current_adptr;//current_ac->Anim;	//RJS 3Nov00
		if (mad->itemstate < UByte(newState))
			mad->itemstate = UByte(newState);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetKilledAC
//Author		Robert Slater
//Date			Mon 4 Sep 2000
//
//Description	Cannot be invoked within a normal/collision damage SetAC() death
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::SetKilledAC(void*	itm, animptr&	adptr)
{
	if (!current_ac)
		SetAC(itm,adptr);
	else
		current_depth++;

	toBeKilled++;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateKilledAC
//Author		Robert Slater
//Date			Mon 4 Sep 2000
//
//Description	Must be paired with a SetKilledAC()
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::UpdateKilledAC()
{
	if (toBeKilled)
	{
		toBeKilled--;

		UpdateACDamage();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateACDamage
//Author		Robert Slater
//Date			Mon 21 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::UpdateACDamage()
{
	if (current_ac && !_Replay.Playback && !toBeKilled)					//RJS 4Sep00
	{
		MinAnimData*	mad = (MinAnimData*)current_adptr;//current_ac->Anim;	//RJS 3Nov00
		SquadronBase*	ptr = current_ac->ai.diaryptr;

		if (ptr)
		{
			switch (current_itemstate)
			{
			case ALIVE:
			{
				if (mad->itemstate > ALIVE)
				{
					if (mad->itemstate >= DYING)
						ptr->AddKilled(current_ac,current_pilotcount);	//RJS 21Sep00
					else
						ptr->AddDamage();
				}
			break;
			}
			case DAMMAGED:
			{
				if (mad->itemstate >= DYING)
				{
					if (ptr->numacdamaged > 0)							//RJS 21Sep00
						ptr->numacdamaged--;							//RJS 21Sep00

					ptr->AddKilled(current_ac,current_pilotcount);		//RJS 21Sep00
				}
			break;
			}
			}
		}

		current_itemstate = mad->itemstate;
	}

	if (current_depth)
	{
		current_depth--;
		if (!current_depth)
			current_ac = NULL;
	}
	else
		current_ac = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddKill
//Author		Robert Slater
//Date			Mon 21 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::AddKill(void*	achitter, AirStruc* acHit)
{
	if (achitter && acHit && ((ItemPtr)achitter)->Status.size == AIRSTRUCSIZE && !_Replay.Playback)
	{
		AirStrucPtr		acHitter = (AirStrucPtr)achitter;
		SquadronBase*	ptr = acHitter->ai.diaryptr;
		UByteP			kills;

		if (acHitter->nationality != acHit->nationality)
		{
// Gruppen has 6 types
			SLong	index = acHit->classtype->planetext;

			if (ptr->squadnum >= SQ_LW_START)
			{
				kills = ((Gruppen*)ptr)->kills;
				index -= PT_BRIT_FLYABLE;

// Brit Flyables are duplicated...
				index /= 2;												//RJS 4Sep00
			}
			else
			{
				kills = ((Squadron*)ptr)->kills;
				index -= PT_GER_FLYABLE;
			}

			if (acHitter->AcIsPlayer())
			{
				Player*	pptr = GetFirstPlayer(ptr);
				if (pptr)
					pptr->kills[index]++;
			}

			kills[index]++;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddKilled
//Author		Robert Slater
//Date			Mon 21 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	SquadronBase::AddKilled(AirStruc*	ac, const int&	current_pilotcount)
{
	if (this && ac && !_Replay.Playback)
	{
		numpilotslost+=current_pilotcount;								//RJS 21Sep00
		numlosses++;

		if (ac->fly.originalformpos == 0)
			leaderkilled = LK_1ST;
		else
		{
			if (leaderkilled == LK_NONE)
				leaderkilled = LK_OTHER;
		}

// If Gruppen raid gets wiped out...
		if (	(numlosses >= noaclaunched)
			&&	(squadnum >= SQ_LW_START)	)
		{
			Diary::RaidGroup*	ptr = Squad_Diary.GetRaidGroup(this);
			if (ptr)
				if (ptr->missresult<MR_LOSTLEAVETARG)
					ptr->missresult = MR_LOSTAPPRTARG;
				else
					ptr->missresult = MR_LOSTLEAVETARG;
		}

		_DPlay.UpdateDeadPilots(ac);
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    CreditClaim
// Date:		16/05/00
// Author:		RDH
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	SquadronBase::CreditClaim(PlaneTypeSelect pt,int number)
{
	if (squadnum >= SQ_LW_START)
	{
		Diary::Gruppen* g=(Diary::Gruppen*)this;
		assert(pt<PT_GER_FLYABLE);
		if (pt<PT_BRIT_NONFLY)
			g->kills[pt/2]+=number;
	}
	else
	{
		Diary::Squadron* s=(Diary::Squadron*)this;
		assert(pt>=PT_GER_FLYABLE && pt<PT_VEHICLES);
		s->kills[pt-PT_GER_FLYABLE]+=number;
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddDamage
//Author		Robert Slater
//Date			Mon 21 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	SquadronBase::AddDamage()
{
	if (this)
		numacdamaged++;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddEjected
//Author		Robert Slater
//Date			Mon 21 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	SquadronBase::AddEjected(AirStrucPtr ac, int numpilots)
{
	if (this)
	{
		numpilotslost-=numpilots;									//RJS 13Oct00

		_DPlay.UpdateDeadPilots(ac);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ArrivedAtTarget
//Author		Robert Slater
//Date			Mon 21 Feb 2000
//
//Description	We need one for diaryentry aswell....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::ArrivedAtTarget(AirStruc*	ac, void*	target)
{
	if (ac && target && vp && !_Replay.Playback)						//RJS 21Jun00
	{
		ItemBase*		theTarget = (ItemBase*)target;
		SquadronBase*	ptr = ac->ai.diaryptr;
		RaidGroup*		groupptr = GetRaidGroup(ptr);
		SLong			time = vp->TimeOfDay();

		if (groupptr)
		{
			time /= 100;		//secs
			if (ptr->squadnum >= SQ_LW_START)
			{
				RaidPack*	rpack = GetRaidPack(groupptr);
				if (rpack)
				{
// attack height in metres...
					groupptr->attackheight = theTarget->World.Y / 100;	//RJS 18Oct00
					groupptr->targettime = time;
					groupptr->target = theTarget->uniqueID.count;		//RJS 2Oct00
				}
			}
			else
			{
				Intercept*	iptr = GetIntercept(ptr);
				if (iptr)
				{
					if (	iptr->waspatrolinitially
						&&	theTarget->Status.size == AIRSTRUCSIZE	)
					{
						SquadronBase*	sptr = AirStrucPtr(*theTarget)->ai.diaryptr;
						if (	sptr
							&& (sptr->squadnum >= SQ_LW_START)	)
						{
							iptr->intercepttime = 0;
							iptr->diaryraidindex = ((Gruppen*)sptr)->diaryraidgroupindex;
						}
					}

					UpdateIntercept(iptr,ItemPtr(theTarget),time);		//RJS 25Oct00
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateIntercept
//Author		Robert Slater
//Date			Thu 18 May 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::UpdateIntercept(Intercept*	iptr, ItemPtr	theTarget, const int& interceptTime)
{
	if (iptr && !iptr->intercepttime && theTarget && !_Replay.Playback)	//RJS 21Jun00
	{
		SLong	uid, direction, range;

		iptr->interceptheight = theTarget->World.Y; 
		iptr->intercepttime = interceptTime;

		_Radio.GetPlaceDesc(theTarget->World,uid,direction,range);

		direction >>= 12;		// shrink to 4-bits	(8 points of compass with rounding)
		range /= 100000;		// to km

		iptr->interceptloc = ((uid<<INT_UID_SHIFT)&INT_UID_MASK)
							|((direction<<INT_DIR_SHIFT)&INT_DIR_MASK)
							|((range<<INT_RANGE_SHIFT)&INT_RANGE_MASK);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RaidResult
//Author		Robert Slater
//Date			Wed 23 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::RaidResult(AirStruc* ac, MissResult	theResult)
{
#pragma	message(__HERE__ "Jim: Call RaidResult")
	if (ac->ai.diaryptr && (ac->ai.diaryptr->squadnum >= SQ_LW_START) && !_Replay.Playback)	//RJS 21Jun00
	{
		RaidGroup*		ptr = GetRaidGroup(ac->ai.diaryptr);
		if (ptr)
		{
			if ((theResult != MR_NULL) && (theResult > ptr->missresult))
				ptr->missresult = theResult;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HitTarget
//Author		Robert Slater
//Date			Wed 23 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::HitTarget(void* hitter, void* target, void* groupptr)
{
	ItemPtr	theHitter = (ItemPtr)hitter;	
	if (theHitter && (theHitter->Status.size == AIRSTRUCSIZE) && !_Replay.Playback)	//RJS 21Jun00
	{
		SquadronBase*	sptr = ((AirStrucPtr)theHitter)->ai.diaryptr;
		if (sptr && (sptr->squadnum >= SQ_LW_START))
		{
			RaidGroup*	rptr = GetRaidGroup(sptr);
			ItemPtr		theTarget = (ItemPtr)target;
			int			targUID = theTarget->SGT;						//RJS 31Oct00

			if (!targUID)	targUID = theTarget->uniqueID.count;		//RJS 31Oct00

			if (rptr && (rptr->target == targUID))						//RJS 31Oct00
			{
// Do we want to use the group itterator?
				if (SHAPE.SufficientDamage(theTarget,groupptr))			//RJS 31Oct00
					if (rptr->missresult == MR_ATTACKSLIGHTDAMAGE)
						rptr->missresult = MR_ATTACKSUCCESS;				//JIM 5Jul00
					else
						rptr->missresult = MR_ATTACKSLIGHTDAMAGE;
				else
					if (rptr->missresult<MR_ATTACKNODAMAGE)
						rptr->missresult =MR_ATTACKNODAMAGE;			//JIM 5Jul00
			}
		}
	}
}

void	Diary::EmptyDiary()
{
	delete diaryptr;
	New();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateQuickEntry
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
void	Diary::CreateQuickEntry(ULong*, ULong*, ULong*, int, UWord	target)
{
	if (!_Replay.Playback)												//RJS 21Jun00
	{
		SLong			raidpack = AllocateRaidPack();
		SLong			raidgroup;
		SLong			raidgroup2;
		SLong			raidgroupsize;
		ULong			gruppenindex;
		SLong			interceptno;
		int				squadno;

		diaryptr->raidpacktable[raidpack].doglegpos = target;
		diaryptr->raidpacktable[raidpack].date = UWord(MMC.currdate / SECSPERDAY);
		diaryptr->raidpacktable[raidpack].takeofftime = MMC.currtime;

	//Set up LW first, with raidgroups...
		raidgroup = AllocateRaidGroup(raidpack);
		
		diaryptr->raidgrouptable[raidgroup].target = (UniqueID)target; 
		diaryptr->raidgrouptable[raidgroup].targettime = 0;
		diaryptr->raidgrouptable[raidgroup].misstype = MT_ESCORT;		//RJS 4Sep00
		diaryptr->raidgrouptable[raidgroup].firstgruppenrec = diaryptr->gruppentablenext + 1;//RJS 14Sep00

		interceptno = AllocateIntercept(raidgroup,MMC.currtime);		//RJS 7Sep00

		for (squadno=PT_GER_FLYABLE; squadno < PT_LW_BOMBERS; squadno++)
			AllocateGruppen(Node_Data[SquadNum(squadno)].squadron,raidgroup,gruppenindex);

		//Set up RAF, with intercepts...
		for (squadno=PT_BRIT_FLYABLE; squadno < PT_GER_FLYABLE; squadno++)
			AllocateSquadron(interceptno,Node_Data[SquadNum(squadno)].squadron);

//DeadCode JIM 6Nov00 		raidgroup = AllocateRaidGroup(raidpack);
//DeadCode JIM 6Nov00 		
//DeadCode JIM 6Nov00 		diaryptr->raidgrouptable[raidgroup].target = (UniqueID)target; 
//DeadCode JIM 6Nov00 		diaryptr->raidgrouptable[raidgroup].targettime = 0;
//DeadCode JIM 6Nov00 		diaryptr->raidgrouptable[raidgroup].misstype = MT_RAID;			//RJS 4Sep00
//DeadCode JIM 6Nov00 		diaryptr->raidgrouptable[raidgroup].firstgruppenrec = diaryptr->gruppentablenext + 1;//RJS 14Sep00

		for (squadno=PT_LW_BOMBERS; squadno < PT_VEHICLES; squadno++)
			AllocateGruppen(Node_Data[SquadNum(squadno)].squadron,raidgroup,gruppenindex);
	}

	isQuickMission = true;												//RJS 9Nov00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CreateTransfer
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
void	Diary::CreateTransfer(void*	bsquad)
{
	if (!_Replay.Playback)												//RJS 21Jun00
	{
		BritSquadron*	squaddy = (BritSquadron*)bsquad;
// Create new intercept, patrol-style, and log transfer in squaddiary

		RaidPack*	patrolpack = GetFirstRaidPack(MMC.currdate);
		RaidGroup*	patrolgrp = GetFirstRaidGroup(patrolpack);
		int			interceptno = AllocateIntercept(patrolgrp,MMC.currtime);	//RJS 7Sep00
		int			newentry = AllocateSquadron(interceptno,squaddy->squadron);

		if (newentry != -1)
		{
			diaryptr->squadtable[newentry].noaclaunched = squaddy->ACTotal();
			diaryptr->squadtable[newentry].wastransfer = true;
			diaryptr->squadtable[newentry].takeoffairfield = UniqueID(squaddy->homeairfield);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLandingTime
//Author		Robert Slater
//Date			Tue 29 Feb 2000
//
//Description	This one is called from the 3D
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::SetLandingTime(SquadronBase*	ptr)
{
	if (vp && !_Replay.Playback)										//RJS 21Jun00
		SetLandingTime(ptr,vp->TimeOfDay()/100);						//RJS 7Sep00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLandingTime
//Author		Robert Slater
//Date			Thu 07 Sep 2000
//
//Description	2D & 3D eventually get here
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::SetLandingTime(SquadronBase*	ptr, int landingTime)
{
	if (ptr->squadnum < SQ_LW_START)
	{
		Squadron* sptr = (Squadron*)ptr;

		sptr->landingtime = landingTime;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLandingTime
//Author		Robert Slater
//Date			Thu 07 Sep 2000
//
//Description	This one is called from the campaign 2D
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::SetLandingTime(ULong entry)
{
	SquadronBase*	ptr;
	ULong			base = entry&DIARYMASK;
	if (entry & GRUPPENMASK)
		ptr = &diaryptr->gruppentable[base];
	else
		ptr = &diaryptr->squadtable[base];

	SetLandingTime(ptr,MMC.currtime);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDisperseTime
//Author		Robert Slater
//Date			Tue 29 Feb 2000
//
//Description	2D & 3D eventually get here
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::SetDisperseTime(SquadronBase*	ptr, int timeOfDay)
{
	if (ptr->squadnum >= SQ_LW_START)
	{
		RaidPack* rptr = GetRaidPack(GetRaidGroup(ptr));
	
		rptr->dispersetime= timeOfDay;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDisperseTime
//Author		Robert Slater
//Date			Thu 07 Sep 2000
//
//Description	This one is called from the 3D
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::SetDisperseTime(SquadronBase*	ptr)
{
	if (vp && !_Replay.Playback)
		SetDisperseTime(ptr,vp->TimeOfDay()/100);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDisperseTime
//Author		Robert Slater
//Date			Thu 07 Sep 2000
//
//Description	This one is called from the campaign 2D
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::SetDisperseTime(ULong	entry)
{
	SquadronBase*	ptr;
	ULong			base = entry&DIARYMASK;
	if (entry & GRUPPENMASK)
		ptr = &diaryptr->gruppentable[base];
	else
		ptr = &diaryptr->squadtable[base];

	SetDisperseTime(ptr,MMC.currtime);									//RJS 7Sep00
}

void	SquadronBase::KillPilot()
{
	if (this)
		numpilotslost++;
}

void	Diary::ArrivedAtTarget(ULong	diaryIndex, void*	target)
{
	SquadronBase*	ptr = GetDiaryPtr(diaryIndex);

	if (ptr && target && !_Replay.Playback)						//RJS 21Jun00
	{
		ItemBase*		theTarget = (ItemBase*)target;
		RaidGroup*		groupptr = GetRaidGroup(ptr);
		SLong			time = MMC.currtime;

		if (groupptr)
		{
			if (ptr->squadnum >= SQ_LW_START)
			{
				RaidPack*	rpack = GetRaidPack(groupptr);
				if (rpack)
				{
// attack height in metres
					groupptr->attackheight = theTarget->World.Y / 100;	//RJS 18Oct00
					groupptr->targettime = time;
					groupptr->target = theTarget->uniqueID.count;		//RJS 2Oct00
				}
			}
			else
			{
// Update the RAF intercept...
				Intercept*	iptr = GetIntercept(ptr);					//RJS 5Oct00
				if (iptr)
				{
// Have we intercepted some bad guys?
					if (	iptr->waspatrolinitially
						&&	theTarget->Status.size == AIRSTRUCSIZE	)
					{
						info_airgrp*	iac = (info_airgrp*)theTarget;
						Profile*		pk = iac->package;

						for (int s=0, max=pk->squadlist; s < max; s++)
						{
							if (pk->squadlist[s].instance == theTarget->uniqueID.count)
							{
								SquadronBase*	sptr = GetDiaryPtr(pk->squadlist[s].diaryentry);
								if (sptr->squadnum >= SQ_LW_START)
								{
// Reset the intercept record...
									iptr->intercepttime = 0;
									iptr->diaryraidindex = ((Gruppen*)sptr)->diaryraidgroupindex;
								}

								break;
							}
						}
					}

					UpdateIntercept(iptr,ItemPtr(theTarget),time);
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FillEndOfDayReport
//Author		Robert Slater
//Date			Sun 29 Oct 2000
//
//Description	Only set the text if the report is empty...
//
//Inputs		
//
//Returns
//
//------------------------------------------------------------------------------
void	Diary::FillEndOfDayReport(Player* ptr)
{
//DeadCode RJS 16Nov00 	if (ptr)
//DeadCode RJS 16Nov00 	{
//DeadCode RJS 16Nov00 		if (ptr->descriptionstringindex != DIARY_EMPTYINDEX)
//DeadCode RJS 16Nov00 		{
//DeadCode RJS 16Nov00 			char*	textptr = &diaryptr->playerdescspace[ptr->descriptionstringindex];
//DeadCode RJS 16Nov00 			if (	textptr
//DeadCode RJS 16Nov00 				&&	(textptr[0] == 0)	)
//DeadCode RJS 16Nov00 			{
//DeadCode RJS 16Nov00 				CString	endOfDay = "";
//DeadCode RJS 16Nov00 				CString	concatString;
//DeadCode RJS 16Nov00 
//DeadCode RJS 16Nov00 				if (ptr->howendedmission != EFS_NULL)					//RJS 10Nov00
//DeadCode RJS 16Nov00 					concatString.LoadString(endStatusLookUp[ptr->howendedmission]);
//DeadCode RJS 16Nov00 				else
//DeadCode RJS 16Nov00 					concatString = "";
//DeadCode RJS 16Nov00 
//DeadCode RJS 16Nov00 				if (trainingReport != SCRIPT_NULL)
//DeadCode RJS 16Nov00 				{
//DeadCode RJS 16Nov00 					PhraseBuffer	phrasebuff;
//DeadCode RJS 16Nov00 					UWord			randval = Math_Lib.rnd();
//DeadCode RJS 16Nov00 
//DeadCode RJS 16Nov00 					_Radio.ExpandMessage(phrasebuff,trainingReport,randval,TargetIndexes(),NULL,NULL,NULL);
//DeadCode RJS 16Nov00 
//DeadCode RJS 16Nov00 					_MsgBuffer.PhraseToString(endOfDay,phrasebuff);
//DeadCode RJS 16Nov00 
//DeadCode RJS 16Nov00 					if (ptr->howendedmission != EFS_NULL)
//DeadCode RJS 16Nov00 					{
//DeadCode RJS 16Nov00 						endOfDay += "\n";
//DeadCode RJS 16Nov00 						endOfDay += concatString;
//DeadCode RJS 16Nov00 					}
//DeadCode RJS 16Nov00 				}
//DeadCode RJS 16Nov00 				else
//DeadCode RJS 16Nov00 					endOfDay = concatString;
//DeadCode RJS 16Nov00 
//DeadCode RJS 16Nov00 				SetDiaryText(ptr,(const char*)endOfDay);
//DeadCode RJS 16Nov00 			}
//DeadCode RJS 16Nov00 		}
//DeadCode RJS 16Nov00 	}	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTrainingReport
//Author		Robert Slater
//Date			Mon 30 Oct 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::AddTrainingReport(const int&	theScript)
{
	trainingReport = theScript;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		New3DSession
//Author		Robert Slater
//Date			Mon 30 Oct 2000
//
//Description	This is invoked from the Inst3D constructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::New3DSession()
{
	NewSession();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Enter3D
//Author		Robert Slater
//Date			Mon 30 Oct 2000
//
//Description	This is called when we create a new view
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::Enter3D(ViewPoint* thevp)
{
	vp = thevp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewSession
//Author		Robert Slater
//Date			Mon 30 Oct 2000
//
//Description	Clears variables used during the 3D
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::NewSession()
{
	toBeKilled = 0;													//RJS 4Sep00

	vp = NULL;														//RJS 9Oct00
	current_depth = 0;
	current_ac = NULL;
	current_itemstate = 0;
	current_pilotcount = 1;
	current_adptr = ANIM_NULL;											//RJS 3Nov00

	trainingReport = SCRIPT_NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DamageReport
//Author		Robert Slater
//Date			Thu 09 Nov 2000
//
//Description
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::Player::DamageReport(CString&	theString)
{
	bool acdamage = false;
	int maxdam = 0, maxdamtype;
	for(int i = 0; i < DIARY_MAXDAMAGE; i++)
		if (specificdamage[i] >50)
		{
			acdamage = true;
			if (specificdamage[i] > maxdam)
			{
				maxdam = specificdamage[i];
				maxdamtype = i;
			}
		}

	if (	acdamage
		&&	(howendedmission < EFS_BadCrashAF)	)
	{
		if (maxdam < 200)
			theString.LoadString(IDS_L_DIARYDAM_LEFTWING+maxdamtype);
		else
			theString.LoadString(IDS_L_DIARYDEST_LEFTWING+maxdamtype);
	}
	else
	{
		if (howendedmission != EFS_NULL)
			theString.LoadString(endStatusLookUp[howendedmission]);
		else
			theString = "";
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFirstPlayerInDay
//Author		Robert Slater
//Date			Thu 09 Nov 2000
//
//Description
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Diary::Player*	Diary::GetFirstPlayerInRaid(SquadronBase*	sptr,RaidGroup*	rgrp)
{
	Player*			retval = NULL;
	Player*			tmppptr;
	SquadronBase*	tmpsptr;

	tmppptr = GetFirstPlayer();
	if (tmppptr)
	{
		do
		{
			tmpsptr = GetSquadron(tmppptr);
			if (tmpsptr == sptr)
			{
				if (GetRaidGroup(tmpsptr)==rgrp)
				{
					retval = tmppptr;
					break;
				}
			}
			tmppptr++;
		}
		while (tmpsptr);
	}

	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMissResult
//Author		Robert Slater
//Date			Thu 09 Nov 2000
//
//Description
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Diary::GetMissResult(SquadronBase*	sptr,RaidGroup*	raidgroup, CString& missString)
{
	Player*	pptr = GetFirstPlayerInRaid(sptr,raidgroup);
	if (pptr)
	{
		if (isQuickMission)
		{
			if (pptr->howendedmission != EFS_NULL)
				missString.LoadString(endStatusLookUp[pptr->howendedmission]);
			else
				missString = "";
		}
		else
			missString.LoadString(IDS_L_MR_NULL+raidgroup->missresult);
	}
	else
		missString = "";
}
