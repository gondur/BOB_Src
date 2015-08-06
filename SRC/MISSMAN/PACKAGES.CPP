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

////////////////////////////////////////////////////////////////////////
//
// Module:      Packages.cpp
//
// Created:     15/12/98 by JIM
//
// Description: 		  SetPredictedPointFromETA
//
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////
// Managing the package list.
//
//	 
//	 SetPredictedPointFromETA
//

#include	"dosdefs.h"
#include	"files.g"
//DEADCODE JIM 09/02/00 #include	"text.h"
#include "myerror.h"
#include	"Worldinc.h"
#include	"node.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include	"mymath.h"
#include	"ranges.h"
#include "winmove.h"
#include "comms.h"
#include "planetyp.h" 
#include "nodebob.h"

#include "..\mfc\resource.h"
#include	"globrefs.h"
#include "myerror.h"

#include "package.h"
#include "bitfield.h"
BITABLE(Profile::BetterRule);
ADDORABLE(Profile::BetterRule);
NOTABLE(Profile::BetterRule,Profile::BR_WIDESTPOSSIBLE);
//SHIFTABLE(Profile::BetterRule,int,Profile::BetterRule);
//DEADCODE JIM 25/02/00 	inline	Profile::BetterRule	operator<<	(Profile::BetterRule	b,const int s)
//DEADCODE JIM 25/02/00 			{return ((Profile::BetterRule) (+b<<+s));}

typedef	Profile::AttackMethod	AttackMethod;
MAKEFIELD (AttackMethod, Profile::AM_FIELD_MIN,Profile::AM_FIELD_MAX);

struct 	SquadList
{
	typedef	Profile::Squad Squad;
	UByte		numsquadrons;
	UByte		squadronsizeentry;
	operator 		int();
	Squad&		operator[](int i)	{return list[i];}

	enum		{MAXENTRIES=1};
	Squad		list[MAXENTRIES];
	static struct	SquadSizes
	{
		int size;
		SquadList*	(*make)();	//These are pointers to the static Squadlist member functions!!!
		void	(*remove)(SquadList*);
	}	squadsizes[];
};

Profile::Squad & Profile::SquadListRef::Squadron(int index)
{
	assert(pointer);
	assert(index<pointer->numsquadrons);
	return(pointer[0][index]);
}

void	Profile::Squad::Clear()
{
	instance=takeoffwp=landingwp=UID_NULL;
	formtype= FTI_SAME;
	squadnum=SQ_ZERO;
	targetindex=0;
	takeofftime=lastwptime=0;
	numbers=0;
	fightperiods=0;
 	diaryentry=-1;
	fightperiods=0;
}
void	Profile::SquadListRef::DeleteAll()
{
	if (pointer)
		SquadList::squadsizes[pointer->squadronsizeentry].remove(pointer);
	pointer=NULL;

}

Profile::Squad * Profile::SquadListRef::InsertEnd(UniqueID uid)
{
	int entry=0;
	if (pointer)
		entry=pointer->squadronsizeentry;
	if (	pointer==NULL 	|| 	pointer->numsquadrons==pointer->squadsizes[entry].size	)
	{	//Run out of space... make list bigger!
		assert(SquadList::squadsizes[entry+1].size);
		SquadList* newlist=SquadList::squadsizes[entry+1].make();
		newlist->squadronsizeentry=entry+1;
		for (int i=0;i<pointer->squadsizes[entry].size;i++)
			newlist[0][i]=pointer[0][i];
		newlist->numsquadrons=pointer->squadsizes[entry].size;
		if (entry)
			SquadList::squadsizes[entry].remove(pointer);
		pointer=newlist;
	}
	//ok now add new one...
	entry=pointer->numsquadrons++;
	pointer[0][entry].Clear();
	pointer[0][entry].instance=uid;
//DEADCODE JIM 14/02/00 	if (uid)
//DEADCODE JIM 14/02/00 	{
//DEADCODE JIM 14/02/00 		info_airgrpPtr a=Persons2::ConvertPtrUID(uid);
//DEADCODE JIM 14/02/00 		a->package=this;
//DEADCODE JIM 14/02/00 	}
	return 	&pointer[0][entry];
}

Profile::Squad*		Profile::InsertSquadAt(int index,UniqueID uid)
{

	Squad*	topsq=squadlist.InsertEnd(UID_NULL);
	int		topind=squadlist.Max()-1;
	while (topind!=index)
	{
		topind--;
		SwapNeighborSquadsAt(topind);
	}
	Squad&	newsq=squadlist[index];
	newsq.Clear();
	newsq.instance=uid;
	if (uid)
	{
		info_airgrpPtr a=Persons2::ConvertPtrUID(uid);
		a->package=this;
	}
	return &newsq;
}

int	Profile::SquadListRef::Max()
{
	if (pointer)
		return pointer->numsquadrons;
	else
		return 0;
}

Profile::SquadListRef::Free()
{
	if (pointer)
		SquadList::squadsizes[pointer->squadronsizeentry].remove(pointer);
	pointer=NULL;
}
struct 	SquadListOneSquad:SquadList
{	//extra info about smaller force sent
	int	acnumfirst;	 //this is actually a bit pattern of used aircraft ids!!!!
//	int	acnumcount;
	static SquadList*	Make()	{return new SquadListOneSquad;}
	static void	Del(SquadList*s){delete (SquadListOneSquad*)s;}
};

struct 	SquadListEscPat:SquadList
{
	enum		{MAXENTRIES=4};
	Squad	morelist[MAXENTRIES- SquadList::MAXENTRIES];
	static SquadList*	Make()	{return new SquadListEscPat;}
	static void	Del(SquadList*s){delete (SquadListEscPat*)(s);}
};

struct 	SquadListSquad:SquadList
{
	enum		{MAXENTRIES=10};
	Squad	morelist[MAXENTRIES- SquadList::MAXENTRIES];
	static SquadList*	Make()	{return new SquadListSquad;}
	static void	Del(SquadList*s){delete (SquadListSquad*)(s);}
};

struct	SquadListBrit:SquadList
{
	enum	{MAXENTRIES=31};
	Squad	morelist[MAXENTRIES- SquadList::MAXENTRIES];
	static SquadList*	Make()	{return new SquadListBrit;}
	static void	Del(SquadList*s){delete (SquadListBrit*)(s);}
};

struct	SquadListGesch:SquadList
{
	enum	{MAXENTRIES=Profile::MAX_SQUADS};
	Squad	morelist[MAXENTRIES-SquadList::MAXENTRIES];
	static SquadList*	Make()	{return new SquadListGesch;}
	static void	Del(SquadList*s){delete (SquadListGesch*)(s);}
};
SquadList::SquadSizes	SquadList::squadsizes[]=
{
	{0},
	{SquadListOneSquad::MAXENTRIES,	SquadListOneSquad::Make,	SquadListOneSquad::Del	},
	{SquadListEscPat::MAXENTRIES,	SquadListEscPat::Make,		SquadListEscPat::Del	},
	{SquadListSquad::MAXENTRIES,	SquadListSquad::Make,		SquadListSquad::Del		},
	{SquadListBrit::MAXENTRIES,		SquadListBrit::Make,		SquadListBrit::Del		},
	{SquadListGesch::MAXENTRIES,	SquadListGesch::Make,		SquadListGesch::Del		},
	{0}
};

int	Profile::SquadListRef::AcBitsSquad(int sqline)
{
	if (sqline!=0)
		return (1<<Squadron(sqline).numacoriginal)-1;
	else
		return 	AcBitsFirstSquad();
}

bool	Profile::SquadListRef::SetAcBitsFirstSquad(int pattern)
{
	if (pointer->squadsizes[pointer->squadronsizeentry].size!=SquadListOneSquad::MAXENTRIES)
		return false;
	else
	{
		((SquadListOneSquad*)pointer)->acnumfirst=pattern;
		return true;
	}

}


int	Profile::SquadListRef::AcBitsFirstSquad()
{
	if (!pointer)
		return	0x0fff;
	if (pointer->squadsizes[pointer->squadronsizeentry].size==SquadListOneSquad::MAXENTRIES)
		return 	((SquadListOneSquad*)pointer)->acnumfirst;
	else
		return (1<<Squadron(0).numacoriginal)-1;
}
void		Profile::DeleteSquadAt(int index)
{
	//remove aircraft itself
	Squad&	delsq=squadlist[index];
	if (delsq.instance)
	{
		info_airgrp *a=*Persons2::ConvertPtrUID(delsq.instance);
		Persons2::delUID(delsq.instance);
		delete a;															//JIM 12Oct00
	}

	SquadNum squadnum=delsq.squadnum;
	//wipe record
	delsq.Clear();
	//Release assigned squad if not in use elsewhere
	int	pack;
	if (!Todays_Packages.GetSquadEntry(squadnum,pack))
		if (attackmethod<AM_LWPACKS)
		{
			BritSquadron*	sq=Node_Data[squadnum];
			if (sq->totestatus>=PS_PLANNING)
				sq->totestatus=PS_AT_5;
			sq->usedacbits=0;

			
		}
		else
		{
			Gruppen*	sq=Node_Data[squadnum];
			sq->totestatus=PS_AT_30;
			sq->periodsuntilready=0;
		}
	else
		if (attackmethod<AM_LWPACKS)
			if (index==0)
			{
				BritSquadron*	sq=Node_Data[squadnum];
				sq->usedacbits&=~squadlist.AcBitsFirstSquad(); 
			}
			else
				INT3
		else
			if (this != &Todays_Packages[pack])
				INT3;
	//remove takeoff/landing waypoints
	UniqueID*	wpref=&route;
	while (*wpref)
	{
		info_waypoint* wp=Persons2::ConvertPtrUID(*wpref);
		if (wp->applygroup.Evaluate()==index)
		{	//fix pointer to this wp to point to next & then delete this wp
			Persons2::delUID(*wpref);		
			*wpref=wp->nextwp;
			info_waypoint* wpnext=Persons2::ConvertPtrUID(*wpref);
			if (wpnext)													//JIM 6Nov00
				wpnext->prevwp=wp->prevwp;
			delete wp;
		}
		else
		{	//move on to pointer to next wp
			wpref=&wp->nextwp;
		}
	}
//DeadCode JIM 20Oct00 	int	maxsq=squadlist;
	for (int i2=index,mi2=squadlist.Max()-1;i2<mi2;i2++)
		SwapNeighborSquadsAt(i2);
	//Try to save squadlist space? 
	//No, but switch to other system when down to 1 squad
	squadlist.pointer->numsquadrons--;
	if (squadlist.Max()==1)
	{
		SquadListOneSquad* newlist=(SquadListOneSquad*)SquadList::squadsizes[1].make();
		newlist->squadronsizeentry=1;
			newlist[0][0]=squadlist[0];
		newlist->numsquadrons=1;
		newlist->acnumfirst=0; 
		SquadList::squadsizes[squadlist.pointer->squadronsizeentry].remove(squadlist.pointer);
		squadlist.pointer=newlist;
		squadlist.SetAcBitsFirstSquad(0xfff);
	}

}

void		Profile::SwapNeighborSquadsAt(int a)
{
	//Physically do the swap
	int	b=a+1;
	Squad&	s0=squadlist[a];
	Squad&	s1=squadlist[b];
	if (s0.squadnum==SQ_ZERO)
	{
		s0=s1;
		s1.Clear();
	}
	else
	if (s1.squadnum==SQ_ZERO)
	{
		s1=s0;
		s0.Clear();
	}
	else
	{
		Squad	spare=s0;
		s0=s1;
		s1=s0;
	}
	//Now fix up the waypoints
	UniqueID*	wpref=&route;
	while (*wpref)
	{
		info_waypoint* wp=Persons2::ConvertPtrUID(*wpref);
		if (wp->applygroup.Evaluate()==a)
			wp->applygroup=b;
		elseif (wp->applygroup.Evaluate()==b)
			wp->applygroup=a;
		wpref=&wp->nextwp;
	}
	//Now fix up the raid
	for (int r=1;raidnumentries[r].squadliststart<=b;r++)				//RJS 6Oct00
		if (raidnumentries[r].squadliststart==a)
			raidnumentries[r].squadliststart=b;
		elseif (raidnumentries[r].squadliststart==b)
			raidnumentries[r].squadliststart=a;
}

MAKEFIELD(UniqueID,UID_NULL,IllegalSepID);
struct PackageList  Todays_Packages={NULL};

//////////////////////////////////////////////////////////////////////
//
// Function:    NextWP
// Date:		02/12/99
// Author:		JIM
//
//Description: Returns the next general waypoint or one which matches the input criteria
//
//////////////////////////////////////////////////////////////////////
enum UniqueID  info_waypoint::NextWP(int squadline,int targetnum)
{
	UniqueID rv=nextwp;
	while (rv)
	{
		info_waypoint* wp=Persons2::ConvertPtrUID(rv);
		if (wp->applywave.Evaluate()!=ENABLE_COMPLEX_VAL)
			if (targetnum==wp->applywave.Evaluate())
				return rv;
			else
			{}
		else
		if (wp->applygroup.Evaluate()!=ENABLE_COMPLEX_VAL)
			if (wp->applygroup.Evaluate()==squadline)
				return rv;
			else
			{}
		else
			return rv;
		rv=wp->nextwp;
	};
	return	rv;											  //DAW 26/11/99
}
void	PackageList::UpDatePackageTimes()
{
//DEADCODE DAW 24/11/99 	int targettime;
//DEADCODE DAW 24/11/99 	int laststartperiodtime=0;
//DEADCODE DAW 24/11/99 	int p=0;
//DEADCODE DAW 24/11/99 	while (p<Profile::MAX_PACKS && Todays_Packages[p][0].firstwp)
//DEADCODE DAW 24/11/99 	{
//DEADCODE DAW 24/11/99 		if (MMC.debrief.currperiod == 0)
//DEADCODE DAW 24/11/99 			laststartperiodtime = AFTERNOONPERIODSTART;
//DEADCODE DAW 24/11/99 		if (MMC.debrief.currperiod == 1)
//DEADCODE DAW 24/11/99 			laststartperiodtime = MORNINGPERIODSTART;
//DEADCODE DAW 24/11/99 		if (MMC.debrief.currperiod == 2)
//DEADCODE DAW 24/11/99 			laststartperiodtime = MIDDAYPERIODSTART;
//DEADCODE DAW 24/11/99 		for (int i=0;i<Profile::MAX_WAVES;i++)
//DEADCODE DAW 24/11/99 		if (Todays_Packages[p][i].firstwp)
//DEADCODE DAW 24/11/99 		{
//DEADCODE DAW 24/11/99 			targettime = Todays_Packages[p][i].targettime - laststartperiodtime + MMC.currtime;
//DEADCODE DAW 24/11/99 			if	(Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
//DEADCODE DAW 24/11/99 			{
//DEADCODE DAW 24/11/99 				if (targettime >	HR16MIN20)							  //RDH 11/06/99
//DEADCODE DAW 24/11/99 					//don't want it too dark in winter
//DEADCODE DAW 24/11/99 					targettime =	HR16MIN20;							  //RDH 11/06/99
//DEADCODE DAW 24/11/99 				if (targettime <	HR08)
//DEADCODE DAW 24/11/99 					//don't want it too dark in winter
//DEADCODE DAW 24/11/99 					targettime =	HR08;							  //RDH 11/06/99
//DEADCODE DAW 24/11/99 			}
//DEADCODE DAW 24/11/99 			SetWaveTimes(p, i, targettime);
//DEADCODE DAW 24/11/99 		}
//DEADCODE DAW 24/11/99 
//DEADCODE DAW 24/11/99 		p++;
//DEADCODE DAW 24/11/99 	}
}
//DEADCODE DAW 24/11/99 void	PackageList::SetWaveTimes(int p, int w, int targettime)
//DEADCODE DAW 24/11/99 {
//DEADCODE DAW 24/11/99 //DEADCODE DAW 24/11/99 	Todays_Packages[p][w].targettime = targettime;
//DEADCODE DAW 24/11/99 	Todays_Packages[p].CalcWPTimes(w);
//DEADCODE DAW 24/11/99 
//DEADCODE DAW 24/11/99 }

//DeadCode JIM 25Oct00 bool	PackageList::PackageHasBeenEdited()
//DeadCode JIM 25Oct00 {
//DeadCode JIM 25Oct00 	int p=0;
//DeadCode JIM 25Oct00 	while (p<Profile::MAX_PACKS && pack[p].route)
//DeadCode JIM 25Oct00 	{
//DeadCode JIM 25Oct00 		if (pack[p].edited) 
//DeadCode JIM 25Oct00 			return (true);
//DeadCode JIM 25Oct00 		p++;
//DeadCode JIM 25Oct00 	}
//DeadCode JIM 25Oct00 	return(false);
//DeadCode JIM 25Oct00 }
static	Profile::BetterRule	Type_To_Rule[]=
{
		Profile::BR_B_SPITWL	,
		Profile::BR_B_SPITWL	,
		Profile::BR_B_HURRWL	,
		Profile::BR_B_HURRWL	,

		Profile::BR_NONE,
		Profile::BR_NONE,

		Profile::BR_R_109FONLY,
		Profile::BR_R_110BONLY+Profile::BR_R_110FONLY,	//dual role

		Profile::BR_R_JU87ONLY	,

		Profile::BR_R_DO17ONLY	,
		Profile::BR_R_JU88ONLY	,
		Profile::BR_R_HE111ONLY
};

Gruppen*	NodeData::FindNearestGruppen(UniqueID closepoint,WaderName wname,int minavailac,Profile::BetterRule br) //MAY NEED MORE RULES...
{	//Always called with WN_BETTERRULE...
	Coords3D	loc=Persons2::ConvertPtrUID(closepoint)->World;
	struct	TypeOrWaderTest
	{	
		int	comparitor;
		virtual bool operator()(Gruppen*)=0;
	};
	struct	WaderTest:TypeOrWaderTest
	{
		WaderTest(WaderName i)	{comparitor=i;}
		bool operator()(Gruppen* grupp)
		{	return (Node_Data.geschwader[grupp->wadernum].wadername==comparitor);	}
	};
	struct	TypeTest:TypeOrWaderTest
	{	//Always uses this method
		TypeTest(Profile::BetterRule i)	{comparitor=i;}
		bool operator()(Gruppen* grupp)
		{	return (Type_To_Rule[Node_Data.geschwader[grupp->wadernum].aircrafttype]&comparitor)!=0;	}
	};

	WaderTest	wadertest(wname);
	TypeTest	typetest(br);
	TypeOrWaderTest* testp=(&wadertest);
	if (wname==WN_BETTERRULE)
		testp=&typetest;
	TypeOrWaderTest& test=*testp;

	Gruppen*		squadron=NULL;
	int			bestrange=0x7fffffff;
	int		rangeaddto109s=METRES30KM;
	if (Save_Data.flightdifficulty[FD_109FUEL])
		rangeaddto109s=0;
	int	mingruppac=Gruppen::MIN_GRUPPEAC,minstaffac=10;
	if (br&Profile::BR_R_ANYFIGHTER)
		mingruppac=Gruppen::MIN_GRUPPEFIGHTERS,minstaffac=12;

	if (minavailac>=60)
	{
		if (minavailac>=90)	  //Nearest Geschwader
		{
			for(Gruppen*	grupp=Node_Data.gruppe;grupp[0].squadron;grupp+=3)
			{
				if (test(grupp))
				if (	grupp[0].acavail>=mingruppac		&&!grupp[0].Busy()
					&&	grupp[1].acavail>=mingruppac		&&!grupp[1].Busy()
					&&	grupp[2].acavail>=mingruppac		&&!grupp[2].Busy()
					)
				{
					Coords3D loc2=Persons2::ConvertPtrUID(grupp[0].homeairfield)->World;
					int range0=Math_Lib.distance3d(loc.X-loc2.X,0,loc.Z-loc2.Z);
					loc2=Persons2::ConvertPtrUID(grupp[1].homeairfield)->World;
					int range1=Math_Lib.distance3d(loc.X-loc2.X,0,loc.Z-loc2.Z);
					loc2=Persons2::ConvertPtrUID(grupp[2].homeairfield)->World;
					int range2=Math_Lib.distance3d(loc.X-loc2.X,0,loc.Z-loc2.Z);
					int	brt=bestrange;
					if (Node_Data.geschwader[grupp->wadernum].aircrafttype==PT_ME109)
						brt-=rangeaddto109s;
					if (range0<brt&& range1<brt&& range2<brt)
					{
						if (range0<range1)
							if (range1<range2)
								bestrange=range2;
							else
								bestrange=range1;
						else
							if (range0<range2)
								bestrange=range2;
							else
								bestrange=range0; 
						if (Node_Data.geschwader[grupp->wadernum].aircrafttype==PT_ME109)
							bestrange+=rangeaddto109s;
						squadron=grupp;
					}
				}
			}
		}
		else		//Pair of grupp
		{
			for(Gruppen*	grupp=Node_Data.gruppe;grupp[1].squadron;grupp++)
			{
				if (test(grupp))
				if (	grupp[0].acavail>=mingruppac		&&!grupp[0].Busy()
					&&	grupp[0].wadernum==grupp[1].wadernum 
					&&	grupp[1].acavail>=mingruppac		&&!grupp[1].Busy()
					)
				{
					Coords3D loc2=Persons2::ConvertPtrUID(grupp[0].homeairfield)->World;
					int range0=Math_Lib.distance3d(loc.X-loc2.X,0,loc.Z-loc2.Z);
					loc2=Persons2::ConvertPtrUID(grupp[1].homeairfield)->World;
					int range1=Math_Lib.distance3d(loc.X-loc2.X,0,loc.Z-loc2.Z);
					int	brt=bestrange;
					if (Node_Data.geschwader[grupp->wadernum].aircrafttype==PT_ME109)
						brt-=rangeaddto109s;
					if (range0<brt&& range1<brt)
					{
						if (range0<range1)
								bestrange=range0;
							else
								bestrange=range1;
						squadron=grupp;
					}
				}
			}
		}
	}
	else			//single grupp
		if (minavailac<6)	//Probable reconn
		{	//Bias against larger formations by using formation size as range multiplier
			for(Gruppen*	grupp=Node_Data.gruppe;grupp->squadron;grupp++)
				if (!grupp->periodsuntilready && grupp->acavail>=minavailac)
					if (test(grupp))
					{
						Coords3D loc2=Persons2::ConvertPtrUID(grupp->homeairfield)->World;
						int range=Math_Lib.distance3d(loc.X-loc2.X,0,loc.Z-loc2.Z);
							if (!Node_Data.geschwader[grupp->wadernum].reconn)
								if (grupp->acavail<=10)
									range+=METRES100KM;
								else
									range+=METRES200KM;
						int	brt=bestrange;
						if (Node_Data.geschwader[grupp->wadernum].aircrafttype==PT_ME109)
							brt-=rangeaddto109s;
						if (range<brt)	//true range max is 500km=50million cm. Max a/c=50
						{
							bestrange=range;
							squadron=grupp;
						}
					}
		}
		else
		{
			if (minavailac>=Gruppen::MIN_GRUPPEAC)	//anything above 30 is asking for 1 gruppen, however it comes!
				minavailac=mingruppac;
			for(Gruppen*	grupp=Node_Data.gruppe;grupp->squadron;grupp++)
				if (!grupp->periodsuntilready && grupp->acavail>=minavailac)
					if (test(grupp))
					{
						Coords3D loc2=Persons2::ConvertPtrUID(grupp->homeairfield)->World;
						int range=Math_Lib.distance3d(loc.X-loc2.X,0,loc.Z-loc2.Z);
						int	brt=bestrange;
						if (Node_Data.geschwader[grupp->wadernum].aircrafttype==PT_ME109)
							brt-=rangeaddto109s;
						if (range<brt)
						{
							bestrange=range;
							squadron=grupp;
						}
					}
		}
	return (squadron);
}

static int Times_Per_Tote[]=
{
	SECSPERHR,		 //PS_SPARE,     
	SECSPERHR,		 //PS_ORDER_30,	
	30*SECSPERMIN,	 //PS_AT_30,	    
	20*SECSPERMIN,	 //PS_ORDER_5,	
	5*SECSPERMIN,	 //PS_AT_5,		
	4*SECSPERMIN,	 //PS_ORDER_2,	
	2*SECSPERMIN,	 //PS_AT_2,
	0,
	0,
	20*SECSPERMIN,	 //PS_ORDER_5,	
	4*SECSPERMIN,	 //PS_ORDER_2,	
	1*SECSPERMIN,	 //PS_AT_2,
};

static	int	Ranges_Per_Tote[]=
{		//using 3 miles per minute as guess...
		MILES1000,	//PS_SPARE,
		MILES1000,	//PS_ORDER_30,	//was off-base
		MILES100,	//PS_AT_30,	
		MILES100,	//PS_ORDER_5,	//was at 30
		MILES15,	//PS_AT_5,		
		MILES10,	//PS_ORDER_2,	//was at 5
		0,				//PS_AT_2,		//no disadvantage
		MILES20,		//planning
		MILES20,		//planned
		MILES100,		//plan 30
		MILES10,		//plan	5
		0,				//plan 2
		MILES40,		//takeoff
		MILES40,		//takeoff
		MILES40,		//takeoff
		MILES40,		//takeoff
		MILES40,		//takeoff
		MILES40,		//takeoff
		MILES40,		//takeoff
		MILES40,		//takeoff
		MILES40,		//takeoff
		MILES40,		//takeoff
		MILES40,		//takeoff

};

UWord	Available_Masks[]=
{
	0x0001,0x0003,0x0007,0x000f,
	0x001f,0x003f,0x007f,0x00ff,
	0x01ff,0x03ff,0x07ff,0x0fff,
	0x0fff,0x0fff,0x0fff,0x0fff,	//could have 20 aircraft but can only fly 12
	0x0fff,0x0fff,0x0fff,0x0fff,	//could have 20 aircraft but can only fly 12
	0x0fff,0x0fff,0x0fff,0x0fff,	//could have 24 aircraft but can only fly 12  AND THE REST!!!
	0x0fff,0x0fff,0x0fff,0x0fff
};
UByte	Bit_Count_Nibble[]=
{
	0,1,1,2,
	1,2,2,3,
	1,2,2,3,
	2,3,3,4
};

BritSquadron*	NodeData::FindNearestBritSquad(UniqueID closepoint,int minavailac,Profile::BetterRule br,SquadNum after)
{
	//this code should take notice of alert status of the squadron in determining best range.
	//Status can be 4 hrs, 30 mins, 5 mins or 2 mins.

	Float trgvelx = 0, trgvelz = 0;
	Coords3D	loc=Persons2::ConvertPtrUID(closepoint)->World;
	if (Persons2::GetBandFromUID(closepoint)==SagBAND)
	{	//choose airfield based on coast crossing point estimate
		const Coords3D corner={35*1024*1024,0,27*1024*1024};
		if (loc.X>corner.X || loc.Z<corner.Z)
		{	//move it to the coast...
			info_itemS* i=Persons2::ConvertPtrUID(closepoint);
			if (i && i->Status.size==AIRSTRUCSIZE)
			{
/*CSB*/			Math_Lib.high_sin_cos(i->hdg, trgvelx, trgvelz);
/*CSB*/			FP deltadist = 100.0 * loc.Y / 10.0;	//target travelling at 100m/s.  Interceptor climbing at 15m/s
/*CSB*/			loc.X += trgvelx * deltadist;
/*CSB*/			loc.Z += trgvelz * deltadist;
					
				Coords3D w;
				if (info_airgrpPtr(*i)->wpref)
					w=Persons2::ConvertPtrUID(info_airgrpPtr(*i)->wpref)->World;
				else
				{
					int tp,ts;
					Todays_Packages.GetACSquadEntry(closepoint,tp,ts);
					UniqueID doglegloc=Todays_Packages[tp].doglegloc;
					w=Persons2::ConvertPtrUID(doglegloc)->World;
				}
				w.X-=loc.X;
				w.Z-=loc.Z;
				Coords3D bottom={loc.X,loc.Y,corner.Z};
				if (w.Z)
					bottom.X+=(float(w.X)/w.Z)*(corner.Z-loc.Z);
				Coords3D right={corner.X,loc.Y,loc.Z};
				if (w.X)
					right.Z+=(float(w.Z)/w.X)*(corner.X-loc.X);
				if (bottom.X<corner.X)
					loc=bottom;
				else
				if (right.Z>corner.Z)
					loc=right;
				else
					loc=corner;
			}
		}
	}
//TEMPCODE JIM 26/02/00		CODING NOT FINISHED, SORRY!!!
	int excludegroup=IDS_GROUP_11;
	if (br&Profile::BR_B_ALLOWGRP11)
		excludegroup=0;
	enum	GroupMatch {GM_SAMEAF,GM_SAMESECT,GM_SAMEGROUP,GM_FOUND,GM_NOTFOUND};
	if (after)
	{	//asking for a squad after the current one
		//If requested, it should be the oposite aircraft type
		if ((br&Profile::BR_B_EITHERWL)==Profile::BR_B_EITHERWL)
			br%=Type_To_Rule[BritSquadronPtr(Node_Data[after])->actype];		 //choose opposite type

		//If possible it should be the same airfield, the same sector, or the same group!
		//leader must be present

		//First get airfield
		GroupMatch	groupmatch=GM_NOTFOUND;
		UniqueID firstaf=Node_Data[after].homeairfield;
		UniqueID firstsector=TargetFighterFieldPtr(Node_Data[firstaf])->getsectoruid();
//DeadCode JIM 20Oct00 		int		firstgroup=TargetSectorFieldPtr(Node_Data[firstsector])->groupname;
		UniqueID testsectaf;
		int				bestrangefound=0x40000000;
		BritSquadronPtr	bestsquadfound=NULL;
		//if anyone else on airfield, pick them
		//if anyone else in sector, pick nearest
		//else pick nearest anyway
		for (BritSquadron*	brsq=Node_Data.squadron;brsq->squadron;brsq++)
			if (brsq->squadron!=after && !brsq->usedacbits && brsq->acavail>=12 && brsq->totestatus>Profile::PS_ORDER_30 && brsq->homeairfield!=UID_AF_NEWCASTLE)
			{
				if ((Type_To_Rule[brsq->actype]&br))
					if (brsq->homeairfield==firstaf)
						return brsq;	//best possible match - stop looking!
					else
						if ((testsectaf=TargetFighterFieldPtr(Node_Data[brsq->homeairfield])->getsectoruid())==firstsector)
						{
			
							Coords3D loc2=Persons2::ConvertPtrUID(brsq->homeairfield)->World;
							int range=Math_Lib.distance3d(loc.X-loc2.X,0,loc.Z-loc2.Z)+Ranges_Per_Tote[brsq->totestatus];
							if (groupmatch>GM_SAMESECT || range<bestrangefound)
							{
								bestrangefound=range;
								groupmatch=GM_SAMESECT;
								bestsquadfound=brsq;
							}
							continue;
						}
				if (groupmatch>GM_SAMESECT)
				{	//this may be the best I can do
					Coords3D loc2=Persons2::ConvertPtrUID(brsq->homeairfield)->World;
					int range=Math_Lib.distance3d(loc.X-loc2.X,0,loc.Z-loc2.Z)+Ranges_Per_Tote[brsq->totestatus];
					if (groupmatch==GM_NOTFOUND || range<bestrangefound)
					{
 						bestrangefound=range;
						groupmatch=GM_FOUND;
						bestsquadfound=brsq;
					}
				}
			}
		if (groupmatch!=GM_NOTFOUND)
			return	bestsquadfound;
	}
	elseif (minavailac>=-1 && minavailac<=12)
	{	//Only 1 squad required
		//Pick nearest available of requested types
		//check if leader must be present
		int bestdist=MILES1000;
		BritSquadron* best=NULL;
		if (minavailac==-1)
			minavailac=12;
		if (br & Profile::BR_B_LEADOPTNL)
		{	//ok... don't need a full squad... How many do I want? 
			//check if that many non-flying bits are available
			//max 12 bits set. Generate mask for num ac available (up to 20)
			for (BritSquadron*	brsq=Node_Data.squadron;brsq->squadron;brsq++)
				if ((Type_To_Rule[brsq->actype]&br) && brsq->totestatus>Profile::PS_ORDER_30 && brsq->homeairfield!=UID_AF_NEWCASTLE)
//DeadCode RDH 17May100 				if (Type_To_Rule[brsq->actype]&br)
					if (excludegroup==0 || TargetFighterFieldPtr(Node_Data[brsq->homeairfield])->getsectoraf()->groupname!=excludegroup)
					{
						ULong	availbits=Available_Masks[brsq->acavail];
						availbits &= ~ brsq->usedacbits;
						int avail = Bit_Count_Nibble[availbits&15];
						avail += Bit_Count_Nibble[(availbits>>4)&15];
						avail += Bit_Count_Nibble[(availbits>>8)&15];
						if (avail>=minavailac)
						{	//OK.... Now we can see if it is nearest!
 							Coords3D loc2=Persons2::ConvertPtrUID(brsq->homeairfield)->World;
							int range=Math_Lib.distance3d(loc.X-loc2.X,0,loc.Z-loc2.Z)+Ranges_Per_Tote[brsq->totestatus];
							if (range<bestdist)
							{
								bestdist=range;
								best=brsq;
							}
						}

					}
		}
		else
		{  //must be a fresh squad
			for (BritSquadron*	brsq=Node_Data.squadron;brsq->squadron;brsq++)
				if ((Type_To_Rule[brsq->actype]&br) && brsq->totestatus>Profile::PS_ORDER_30 && brsq->homeairfield!=UID_AF_NEWCASTLE)
					if (excludegroup==0 || TargetFighterFieldPtr(Node_Data[brsq->homeairfield])->getsectoraf()->groupname!=excludegroup)
					{
						if (brsq->usedacbits==0 && brsq->acavail>minavailac)
						{	//OK.... Now we can see if it is nearest!
 							Coords3D loc2=Persons2::ConvertPtrUID(brsq->homeairfield)->World;
							int range=Math_Lib.distance3d(loc.X-loc2.X,0,loc.Z-loc2.Z)+Ranges_Per_Tote[brsq->totestatus];
							if (range<bestdist)
							{
								bestdist=range;
								best=brsq;
							}
						}


					}

		}
		if (best)
			return best;
	}
	else
	{	//asking for so many squads
		//if more than 1 squad then try to find group at same airfield or same sector, and give first
		int	numspitsqreq=-minavailac;
		if (numspitsqreq<0)
			numspitsqreq=minavailac/10;
		int	numhurrsqreq=0;
		if (br & Profile::BR_B_HURRTEST)
			if (br & Profile::BR_B_SPITTEST)
			{
				numhurrsqreq=numspitsqreq/2;
				numspitsqreq-=numhurrsqreq;
			}
			else
			{
				numhurrsqreq=numspitsqreq;
				numspitsqreq=0;
			}
		int				bestrangesq=MILES1000*4;
		BritSquadron*	bestsq=NULL;
//DeadCode JIM 20Oct00 		GroupMatch	groupmatch=GM_NOTFOUND;
		for (BritSquadron*	brsq=Node_Data.squadron;brsq->squadron;brsq++)
			if (!brsq->usedacbits && brsq->acavail>=12 && (Type_To_Rule[brsq->actype]&br) && brsq->totestatus>Profile::PS_ORDER_30&& brsq->homeairfield!=UID_AF_NEWCASTLE)
				if (excludegroup==0 || TargetFighterFieldPtr(Node_Data[brsq->homeairfield])->getsectoraf()->groupname!=excludegroup)
				{
					int	countsame[2]={0,0};
					int	reqsame[2]={numspitsqreq,numhurrsqreq};
					BritSquadron* selsquads[2][8];
					int			selsqranges[2][8];
					int		worstranges[2]={MILES1000,MILES1000};
					UniqueID	sectbase=TargetFighterFieldPtr(Node_Data[brsq->homeairfield])->getsectoruid();
					for (BritSquadron*	brsqm=brsq;brsqm->squadron;brsqm++)
						if (!brsq->usedacbits && brsq->acavail>=12 && (Type_To_Rule[brsq->actype]&br) && brsq->homeairfield!=UID_AF_NEWCASTLE)
							if (TargetFighterFieldPtr(Node_Data[brsqm->homeairfield])->getsectoruid()==sectbase)
							{
								int	typeind=0;							//RDH 12/04/00
								if (brsq->actype>PT_SPIT_B)				//RDH 12/04/00
									typeind++;							//RDH 12/04/00

 								Coords3D loc2=Persons2::ConvertPtrUID(brsq->homeairfield)->World;
								int range=Math_Lib.distance3d(loc.X-loc2.X,0,loc.Z-loc2.Z)+Ranges_Per_Tote[brsq->totestatus];
								if (countsame[typeind]==reqsame[typeind])
								{	//array is full. If range < worst range then find one to replace
									if (range<worstranges[typeind])
									{
										int	worstrange=worstranges[typeind];
										int overloc;
										for (overloc=0;overloc<reqsame[typeind];overloc++)
											breakif (selsqranges[typeind][overloc]==worstrange);
										selsqranges[typeind][overloc]=range;
										selsquads[typeind][overloc]=brsqm;
										for (overloc=0;overloc<reqsame[typeind];overloc++)
											if (selsqranges[typeind][overloc]>range)
												range=selsqranges[typeind][overloc];
										worstranges[typeind]=range;
									}
								}
								else
								{	//array not full.. Add to end
									selsquads[typeind][countsame[typeind]]=brsqm;
									selsqranges[typeind][countsame[typeind]]=range;
									countsame[typeind]++;
								}
							}
					if (reqsame[0]==countsame[0]&&reqsame[1]==countsame[1])
					{	//this clump is worth watching
						//Find total range
						//Should use worst range, but total range forces clumping
						//As a compromise, add the two worst together...
						int range=worstranges[0]+worstranges[1];
						if (bestrangesq>range)
						{
							bestsq=brsq;
							bestrangesq=range;
						}
					}
				}
		if (bestsq)
			return bestsq;
	}
	//Fall through to this code that simply selects nearest full squad	

	BritSquadron*	squadron=NULL;
	int			bestrange=0x7fffffff;
	if (minavailac > 12)
		minavailac = 12;
	{for (BritSquadron*	brsq=Node_Data.squadron;brsq->squadron;brsq++)
		if (!brsq->usedacbits && brsq->acavail>=minavailac && brsq->totestatus>Profile::PS_ORDER_30 && brsq->homeairfield!=UID_AF_NEWCASTLE)	//THIS TEST NEEDS TO BE BETTER
			if (excludegroup==0 || TargetFighterFieldPtr(Node_Data[brsq->homeairfield])->getsectoraf()->groupname!=excludegroup)
			{
				Coords3D loc2=Persons2::ConvertPtrUID(brsq->homeairfield)->World;
				int range=Math_Lib.distance3d(loc.X-loc2.X,0,loc.Z-loc2.Z);
				if (range<bestrange)
				{
					bestrange=range;
					squadron=brsq;
				}
	}		}
	return (squadron);
}


SquadNum PackageList::FindSquad(Profile::AttackMethod duty,UniqueID doglegloc,UniqueID targetloc,int minavailac,Profile::BetterRule br,SquadNum after)
{
	if (duty<Profile::AM_LWPACKS)
	{
		//need to translate better rule into squad choice...
		Squadron* squad=Node_Data.FindNearestBritSquad(targetloc,minavailac,br,after);
		if (squad)
			return squad->squadron;
		else
			return	SQ_ZERO;
	}
	else
	{
		Profile::BetterRule	acmask;
		if (duty==Profile::AM_DECOYPATROL || duty>=Profile::AM_DETACHED)
			acmask=Profile::BR_R_ANYFIGHTER;
		elseif (duty==Profile::AM_DIVEBOMB)
			acmask=Profile::BR_R_JU87ONLY+Profile::BR_R_110BONLY;
		else
			acmask=Profile::BR_R_FLATBOMB+Profile::BR_R_110BONLY;
		br&=acmask;								//mask out fighter flags from input bomber choice
		acmask%=br+Profile::BR_R_110BONLY;		//remaining sensible bomber choice
		Squadron* grup=Node_Data.FindNearestGruppen(doglegloc,WN_BETTERRULE,minavailac,br);
		if (grup)
			return grup->squadron;
		if (minavailac>Gruppen::MIN_GRUPPEFIGHTERS)
			if (br&Profile::BR_R_ANYFIGHTER)
				grup=Node_Data.FindNearestGruppen(doglegloc,WN_BETTERRULE,Gruppen::MIN_GRUPPEFIGHTERS,br);
			else
				grup=Node_Data.FindNearestGruppen(doglegloc,WN_BETTERRULE,Gruppen::MIN_GRUPPEAC,br);
		if (grup)
			return grup->squadron;

		grup=Node_Data.FindNearestGruppen(doglegloc,WN_BETTERRULE,minavailac,acmask);
		if (grup)
			return grup->squadron;
		if (minavailac>Gruppen::MIN_GRUPPEFIGHTERS)
			if (br&Profile::BR_R_ANYFIGHTER)
				grup=Node_Data.FindNearestGruppen(doglegloc,WN_BETTERRULE,Gruppen::MIN_GRUPPEFIGHTERS,acmask);
			else
				grup=Node_Data.FindNearestGruppen(doglegloc,WN_BETTERRULE,Gruppen::MIN_GRUPPEAC,acmask);
		if (grup)
			return grup->squadron;
		return	SQ_ZERO;
	}
}

int PackageList::FindPackage()
{
	int p=0;
	while (p<Profile::MAX_PACKS && pack[p].packagestatus!=Profile::PS_SPARE)
		p++;
	if (p<Profile::MAX_PACKS)
		return (p);
	p=0;
	while (p<Profile::MAX_PACKS && !pack[p].route)
		p++;
	if (p<Profile::MAX_PACKS)
		return (p);
	return -1;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    GetSquadACCountFromGrupp
// Date:		13/01/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
int	PackageList::GetSquadACCountFromGrupp(int requested,int available,int duty)
{
	if (requested>=10)
		if (duty>=Profile::AM_DETACHED)
			requested=12;
		else
			if (requested>=30)
				if (available<40 && available>=36)
					requested=12;	//3 staffeln of 12
				else
					if (available>=30)
						requested=10;	//3 or 4 of 10
					else
						requested=Gruppen::MIN_STAFFELAC;	//1 staffel of 10
			else
			if (requested>=20)
				if (available>=24)
					requested=12;	//2 staffeln of 12
				else
					if (available>=20)
						requested=10;	//2 staffeln of 10
					else
						requested=Gruppen::MIN_STAFFELAC;	//1 staffel of 10
			else
			if (requested>=10)
				if (available>=12)
					requested=12;	//1 staffel of 12
				else
					if (available>10)
						requested=10;
					else
						requested=Gruppen::MIN_STAFFELAC;	//1 staffel of 10
	return	requested;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Todays_Packages_NewPackage
// Date:		30/03/00
// Author:		JIM
//
//Description: LW and RAF package creation
//
//////////////////////////////////////////////////////////////////////
int	Todays_Packages_NewPackage(UniqueID targ,Directives::RAF::Miss& missiondesc,int targetalt)
{
	//+ve numac means  num of ac, -ve means squad
	int* actypecounts=NULL;
	int	actypecountarr[4];	 //Only RAF aircraft. LW needs full PT_VEHICLES to be safe.

	int	numhurr=missiondesc.hurr.numac;
	int	numspit=missiondesc.spit.numac;
	if (numhurr>=12)
		numhurr=-numhurr/12;
	if (numspit>=12)
		numspit=-numspit/12;
	if (numhurr>0 && numspit!=0)
		numhurr=-1;
	if (numspit>0 && numhurr!=0)
		numspit=-1;


	int numac=numhurr+numspit;
	if (numac==0)
	{
		numac=-1;
	}
	if (numac<0)
	{
		actypecountarr[PT_SPIT_A]=3;	//-numspit;						//JIM 19Oct00
		actypecountarr[PT_HURR_A]=3;	//-numhurr;						//JIM 19Oct00
		actypecounts=actypecountarr;
		//see SquadUsedUpInBetterRules
	}


	int maxsq = Todays_Packages.SquadronsPlanned(NAT_RAF);
	maxsq = Profile::MAXRAFPLANNEDSQUADRONS - maxsq;
	int numsq;
	if (numac  > 0)
	{
		numsq = 1;
	}
	else
		numsq = - numac;

	if (numsq > maxsq)
	{
		numac = -maxsq;
	}
//	 if (numac < 0)
//DeadCode JIM 15Sep00 	numac = -numsq;
//DeadCode JIM 15Sep00 	if (numsq == 0)
//DeadCode JIM 15Sep00 		 numac = 0;
	if (targetalt<missiondesc.mainalt)
		targetalt=missiondesc.mainalt;
	int rv = -1;
	if (numac != 0)
		rv=Todays_Packages.NewPackage(targ,NAT_RAF,missiondesc.packageattackmethod,numac,missiondesc.acselectionrules,targetalt,actypecounts);
	if (rv!=-1)
	{
		Todays_Packages[rv].AddAttackWP(0,missiondesc.packageattackmethod,missiondesc.mainalt);
		Todays_Packages[rv].SetSubMethod(PT_SPIT_A,missiondesc.spit.what,missiondesc.spit.formation);
		Todays_Packages[rv].SetSubMethod(PT_HURR_A,missiondesc.hurr.what,missiondesc.hurr.formation);
		Todays_Packages[rv].ReorderPackage(AttackMethodField::Make());
	}
	return rv;
}

int	Todays_Packages_NewPackage(UniqueID targ,Directives::LW::Miss& missiondesc,UniqueID* secondarytrg, bool Gruppe,int* actypecounts)
{
	//missiondesc numbers:
	//Bombers: +ve number means num of a/c, -ve number is staffel
	//Fighter: if Gruppe is true then means number of gruppe else 
	//			+ve number means num of a/c, -ve number is staffel
	//
	int attfighters, detfighters, retfighters;
	if (Gruppe)
	{
		attfighters = -(3 * missiondesc.attfighters);
		detfighters = -(3 * missiondesc.detfighters);
		retfighters = -(3 * missiondesc.retfighters);
	}else
	{
		attfighters = missiondesc.attfighters;
		detfighters = missiondesc.detfighters;
		retfighters = missiondesc.retfighters;
	}

 	int maxsq = Todays_Packages.SquadronsPlanned(NAT_LUF);
	maxsq = Profile::MAXLWPLANNEDSTAFFELN - maxsq;

	int bmbsq;
	int bombers = missiondesc.bombers;
	if (bombers==0)
		bombers=-1;
	if 	 (missiondesc.bombers < 0)
		bmbsq = - missiondesc.bombers;
	else
		bmbsq = (missiondesc.bombers+9)/10;
//DeadCode MS 17Nov100 	if (bmbsq == 0)
//DeadCode MS 17Nov100 		bmbsq = 1;

	int attsq;
	int detsq;
	int retsq;

	if 	 (attfighters < 0)
		attsq = - attfighters;
	else
		attsq = attfighters/12;

	if 	 (detfighters < 0)
		detsq = - detfighters;
	else
		detsq = detfighters/12;

	if 	 (retfighters < 0)
		retsq = - retfighters;
	else
		retsq = retfighters/12;
	

	int reqsq;
	reqsq =  bmbsq + attsq  + detsq + retsq;
	if (reqsq > maxsq)
	{
//DeadCode JIM 06Nov100 		float strike = maxsq * bmbsq/reqsq;
//DeadCode JIM 06Nov100 		if (strike >= 1)
		if (maxsq!=0)
		{
			maxsq-=1;
			reqsq-=1;
			bmbsq = 1+ maxsq * bmbsq / reqsq;
			attsq = maxsq * attsq / reqsq;
			detsq = maxsq * detsq / reqsq;
			retsq = maxsq * retsq / reqsq;
			bombers = -bmbsq;
			attfighters =  -attsq;
			detfighters =  -detsq;
			retfighters = -retsq;

		}else
		{
			bombers = 0;
			attfighters = 0;
			detfighters = 0;
			retfighters = 0;
		}
	}
	if (bombers<-48) 	bombers=-48;
	int rv=-1;
	if (bombers)
	{
		rv=Todays_Packages.NewPackage(targ,NAT_LUF,missiondesc.bomberattackmethod,bombers,missiondesc.acselectionrules,missiondesc.mainalt,actypecounts);
		if (rv==-1)
		{
			if (missiondesc.bomberattackmethod==Profile::AM_DIVEBOMB)
				missiondesc.bomberattackmethod=Profile::AM_LEVELBOMB;
			else
				missiondesc.bomberattackmethod=Profile::AM_DIVEBOMB;
			rv=Todays_Packages.NewPackage(targ,NAT_LUF,missiondesc.bomberattackmethod,bombers,missiondesc.acselectionrules,missiondesc.mainalt,actypecounts);
		}
	}
 	if (rv!=-1)
	{
		if (secondarytrg)
		{//make some targets?
			Todays_Packages[rv].ShareSecondaries(secondarytrg,missiondesc.mainalt);

		}
		Todays_Packages[rv].AddNumerousEscorts(
					attfighters, detfighters, retfighters,
					missiondesc.acselectionrules,*(AttackMethodField*)&missiondesc.escortmethods,missiondesc.mainalt,actypecounts);
//DEADCODE RDH 03/04/00 no bomber formations			Todays_Packages[rv].SetSubMethod(Profile::AM_LWPACKS,missiondesc.formations[0]);

//DeadCode RDH 9Aug00 #pragma warnmsg("Disabled: formations[] contains garbage")
			Todays_Packages[rv].SetSubMethod(Profile::AM_DETACHED,missiondesc.formations[2]);	//RDH 02/04/00
			Todays_Packages[rv].SetSubMethod(Profile::AM_ATTACHED,missiondesc.formations[1]);	//RDH 02/04/00
			Todays_Packages[rv].SetSubMethod(Profile::AM_RETURNESCORT,missiondesc.formations[3]);
			Todays_Packages[rv].ReorderPackage(missiondesc.escortmethods);
			Todays_Packages[rv].CalcRoutePositionsAndTime();
			if (Todays_Packages[rv].break109)
			{
				Todays_Packages[rv].SetSubMethod(Profile::AM_DETACHED,Profile::SM_ANYA2A);	//RDH 02/04/00
				Todays_Packages[rv].SetSubMethod(Profile::AM_ATTACHED,Profile::SM_ANYA2A);	//RDH 02/04/00
			}

			Todays_Packages[rv].ReorderPackage(missiondesc.escortmethods);
	}
	else
		INT3;		 //could not launch LW directive mission???
	return rv;
}


void	Profile::ShareSecondaries(UniqueID* secondarytrg,int alt)
{
	int secondaries=1;
	while (		(secondaries < TargetGroup::MAXSECONDARIES)
			&&	(secondarytrg[secondaries-1])
		)
	{
		AddAttackWP(secondaries,attackmethod, alt);									//RDH 28Jun00
		packagetarget[secondaries] = secondarytrg[secondaries-1];
		secondaries++;
	}
	ShareSecondaries(secondaries);
}

void	Profile::ReShareSecondaries()
{
	int secondaries=0;
	while (packagetarget[secondaries])
	{
		secondaries++;
	}
	ShareSecondaries(secondaries);

}

void	Profile::ShareSecondaries(int secondaries)
{
	if (attackmethod<AM_LWPACKS)
		return;															//JIM 19Oct00
	int	bombers=0;
	for (int sq=0,max=squadlist;sq<max;sq++)
		if ((squadlist[sq].method&AM_GROUPMASK)==AM_LWPACKS)
			bombers++;
	sq=0;
	while ((squadlist[sq].method&AM_GROUPMASK)!=AM_LWPACKS)
		sq++;
	for (int sec=0;secondaries;secondaries--,sec++)
		for (int bc=0,maxbc=(bombers+secondaries-1)/secondaries;bc<maxbc;bc++)
		{
			squadlist[sq].targetindex=sec;
			if (--bombers)
				do{	sq++;
				}while ((squadlist[sq].method&AM_GROUPMASK)!=AM_LWPACKS);
		}


}
//////////////////////////////////////////////////////////////////////
//
// Function:    NewPackage
// Date:		25/07/00
// Author:		JIM
//
//Description: 	Core package creation
//
//////////////////////////////////////////////////////////////////////
int PackageList::NewPackage(UniqueID targ,Nationality nat, Profile::AttackMethod duty,int initialbombers,Profile::BetterRule br,int mainalt,int* actypecounts)
{
	int firstbomberreq=initialbombers;

	if (firstbomberreq<0)
		if (duty==Profile::AM_PATROL||duty==Profile::AM_INTERCEPT )
			firstbomberreq=12;
		else
			if (firstbomberreq<-9)
				firstbomberreq=90;
			else
				firstbomberreq=30;

	SquadNum sq;
	int p;
	TargetNoDetail*	targp=Node_Data[targ];
	UniqueID dogleg=targ;
	if (	nat!=NAT_RAF
		&&	targp 
		&&	targp->truedefenses&targp->TSS_TargetGroup 
		&& TargetGroupPtr(targp)->doglegs[0]
		)
		dogleg=TargetGroupPtr(targp)->doglegs[0];

//DEADCODE JIM 27/01/00 	int duty=DC_BOMB;
	sq = FindSquad(duty,dogleg,targ,firstbomberreq, br);				//RDH 30/03/00
	if (sq <= 0)
		return -1;
	p = FindPackage();
	if (p < 0)
		return p;
//DeadCode JIM 20Oct00 	Squadron*	squad=&Node_Data[sq];

	pack[p].attackmethod=duty;
//DeadCode JIM 25Oct00 	pack[p].redo = false;
//DeadCode JIM 25Oct00 	pack[p].edited = false;
	pack[p].flags=0;
	int	neededraidnums;
	if (duty==Profile::AM_PATROL||duty==Profile::AM_INTERCEPT || !germanisauto)
		neededraidnums=Profile::RNEC_RAF;
	else
		neededraidnums=Profile::RNEC_LWMAXREQ;
	pack[p].raidnumentries=new Profile::RaidNumEntry[neededraidnums];
	for (int i=1;i<neededraidnums;i++)
	{
		pack[p].raidnumentries[i].squadliststart=Profile::RNEC_LISTVALISLASTREC;
		pack[p].raidnumentries[i].detector=0;							//RDH 14/04/00
		pack[p].raidnumentries[i].raidnum=neededraidnums;
	}
	pack[p].raidnumentries[0].squadliststart=0;
	if (localplayer==nat)
	{
		pack[p].raidnumentries[0].detector=Profile::ACCONTACTBASE;
		if (nat==NAT_RAF)
			pack[p].raidnumentries[0].raidnum=++nextsortienum;
		else
			pack[p].raidnumentries[0].raidnum=++nextraidnum;
	}
	else
	{
		pack[p].raidnumentries[0].detector=0;							//RDH 14/04/00
		pack[p].raidnumentries[0].raidnum=0;
	}

//DEADCODE ROD 17/12/99 	pack[p].duty=(DutyType)duty;
	pack[p].packagestatus=Profile::PS_PLANNED;
//DEADCODE  23/02/00 	pack[p].primarytargetETA = MMC.currtime + (int)HR01; 
	pack[p].packagetarget[0]=targ;				//TEMP FIX!!!! No target info available
	pack[p].doglegloc=dogleg;
//DeadCode JIM 3Jul00 	pack[p].packagetakeoff=squad->homeairfield;
	if (!mainalt)
		mainalt=FT_10000;
	pack[p].route=pack[p].MakePrimaryRoute(mainalt);
	pack[p].CountWaypoints();

//DEADCODE JIM 27/01/00 		if (squad->acavail<40 && squad->acavail>=36)
//DEADCODE JIM 27/01/00 			firstbomberreq=12;
//DEADCODE JIM 27/01/00 		else
//DEADCODE JIM 27/01/00 			firstbomberreq=10;
//DEADCODE JIM 27/01/00 	if (firstbomberreq>=20)
//DEADCODE JIM 27/01/00 		if (squad->acavail>=24)
//DEADCODE JIM 27/01/00 			firstbomberreq=12;	//2 staffeln of 12
//DEADCODE JIM 27/01/00 		else
//DEADCODE JIM 27/01/00 			firstbomberreq=10;	//2 staffeln of 10
//DEADCODE JIM 27/01/00 	pack[p][0].numacleft=
//DEADCODE JIM 27/01/00 		pack[p][0].numacoriginal=firstbomberreq;
//DEADCODE JIM 27/01/00 	if (nat!=NAT_RED)
//DEADCODE JIM 27/01/00 	{	//this needs to take account of a leader already flying...
//DEADCODE JIM 27/01/00 		BritSquadronPtr(*squad)->usedacbits=(2<<firstbomberreq)-1;
//DEADCODE JIM 27/01/00 	}
//DEADCODE JIM 27/01/00 	else
//DEADCODE JIM 27/01/00 		GruppenPtr(*squad)->periodsuntilready=-1;	//busy for 1 period. No message on return.
//DEADCODE JIM 27/01/00 
//DEADCODE JIM 27/01/00 	pack[p][0].method=duty;

//DEADCODE JIM 27/01/00 	a->duty=duty;
//DEADCODE JIM 27/01/00 	a->attmethod=0;
//DEADCODE JIM 27/01/00 	a->pattern=0;
//DEADCODE JIM 27/01/00 	a->radiosilence = 0;
//DEADCODE JIM 27/01/00 	a->form=SQUAD_FLATV;//ListFormExpr(2);								  //JIM 19/05/99//CSB 19May99
//DEADCODE JIM 27/01/00 //	a->form[0]=SQUAD_FLATV;a->form[1]=SQUAD_FLATV;				//CSB 19May99
//DEADCODE JIM 27/01/00 	a->bombs=0;
//DEADCODE JIM 27/01/00 	a->movecode=AUTOSAG_WAITTAKEOFF;
//DEADCODE JIM 27/01/00 	pack[p][0].takeofftime=MMC.currtime+SECSPERMIN;
	pack[p].packagetarget[0]=targ;				//TEMP FIX!!!! No target info available
	pack[p].doglegloc=dogleg;
//DEADCODE DAW 22/11/99 	pack[p].egressloc= FindEgressPoint(targ);
//DEADCODE DAW 25/11/99 		pack[p][0][0].takeoffAF;//=
			//SupplyTree::airfieldinfo[MMC.squad[sq].airfieldindex].airfield;//SquadronInfo							//TEMP
//DEADCODE DAW 25/11/99 	if (		(a->duty == DUTYMIGCAP)											  //RDH 16/03/99 //RDH 26/04/99
//DEADCODE DAW 25/11/99 			||	(a->duty == DUTYBARCAP)								  //RDH 26/04/99
//DEADCODE DAW 25/11/99 		)
//DEADCODE DAW 25/11/99 		pack[p][0].firstwp=pack[p].MakePrimaryRoute(FT_30000);
//DEADCODE DAW 25/11/99 	else
//DEADCODE JON 23/02/00 		pack[p].route=pack[p].MakePrimaryRoute(FT_10000);



//	UniqueID wt,waf,wal,wpf,wpl,wr;
//	Todays_Packages[p][0].GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
//	Todays_Packages[p][0].InsertWpBetween(waf,wal,pack[p].packagetarget,wpbombno,0);
//DEADCODE DAW 25/11/99 	Todays_Packages[p][0][0][0].globrefind=Todays_Packages[p].FindSpareGlobref();

	pack[p].AddNumerousSquadrons(initialbombers,duty,sq,br,actypecounts);
//DEADCODE JIM 14/02/00 	if (duty>Profile::AM_LWPACKS)
//DEADCODE JIM 14/02/00 	{
//DEADCODE JIM 14/02/00 		pack[p].AddNumerousSquadrons(initialfarfighters,Profile::AM_DETACHED,SQ_ZERO,br);
//DEADCODE JIM 14/02/00 		pack[p].AddNumerousSquadrons(initialclosefighters,Profile::AM_ATTACHED,SQ_ZERO,br);
//DEADCODE JIM 14/02/00 		pack[p].AddNumerousSquadrons(initialreturnfighters,Profile::AM_RETURNESCORT,SQ_ZERO,br);
//DEADCODE JIM 14/02/00 		AttackMethodField am;
//DEADCODE JIM 14/02/00 		am=0;
//DEADCODE JIM 14/02/00 		pack[p].FixCloseEscortPositions(Profile::AM_LWPACKS,am);
//DEADCODE JIM 14/02/00 		pack[p].FixCloseEscortPositions(Profile::AM_DETACHED,am);
//DEADCODE JIM 14/02/00 		pack[p].FixCloseEscortPositions(Profile::AM_ATTACHED,am);
//DEADCODE JIM 14/02/00 		pack[p].FixCloseEscortPositions(Profile::AM_RETURNESCORT,am);
//DEADCODE JIM 14/02/00 	}
//DEADCODE JIM 14/02/00 	else
//DEADCODE JIM 14/02/00 	{	if (br==Profile::BR_B_SPITONLY)
//DEADCODE JIM 14/02/00 			pack[p].AddNumerousSquadrons(initialclosefighters,duty,SQ_ZERO,Profile::BR_B_HURRONLY);
//DEADCODE JIM 14/02/00 	}
//DeadCode JIM 29Sep00 	pack[p].wpsused=12;
	return p;
}
void	Profile::AddNumerousEscorts(int initialclosefighters,int initialfarfighters,int initialreturnfighters,Profile::BetterRule br,int* actypecounts)
{
	AddNumerousEscorts(initialclosefighters,initialfarfighters,initialreturnfighters,br,AttackMethodField::Make(),METRES3000,actypecounts);

}
AttackMethodField	Profile::AddNumerousEscorts(int initialclosefighters,int initialfarfighters,int initialreturnfighters,Profile::BetterRule br,AttackMethodField am,int alt,int* actypecounts)
{
	AddAttackWP(0,attackmethod, alt);									//RDH 28Jun00
	if (initialclosefighters||initialfarfighters||initialreturnfighters)
	{
		AddAttackWP(-1,AM_PATROL, alt);									//RDH 28Jun00
	}
	AddNumerousSquadrons(initialclosefighters,Profile::AM_ATTACHED,SQ_ZERO,br,actypecounts);
	AddNumerousSquadrons(initialfarfighters,Profile::AM_DETACHED,SQ_ZERO,br,actypecounts);
	AddNumerousSquadrons(initialreturnfighters,Profile::AM_RETURNESCORT,SQ_ZERO,br,actypecounts);

	SubMethod sm = SM_ANYA2A;
	if (br & BR_R_DSTRAFE)
		sm = SM_DOSTRAFFEGROUND;
	SetSubMethod(Profile::AM_DETACHED, sm);
	sm = SM_ANYA2A;
	if (br & BR_R_ASTRAFE)
		sm = SM_DOSTRAFFEGROUND;
	SetSubMethod(Profile::AM_ATTACHED, sm);

	if (attackmethod>=Profile::AM_LWPACKS)
		am=FixCloseEscortPositions(Profile::AM_LWPACKS,am);
	else
		am=FixCloseEscortPositions(Profile::AM_RAF,am);
	am=FixCloseEscortPositions(Profile::AM_ATTACHED,am);
	am=FixCloseEscortPositions(Profile::AM_DETACHED,am);
	am=FixCloseEscortPositions(Profile::AM_RETURNESCORT,am);
	return am;
}
void Profile::SetSubMethod(Profile::AttackMethod escorttype,FormationTypeIndex formation)
{
	for (int num=squadlist.Max()-1;num>=0;num--)
		if ((squadlist[num].method&AM_GROUPMASK)==escorttype)
		{
			squadlist[num].FormType() =  (squadlist[num].formtype%FORMTYPE_SQUAD)+formation;
		}
}
void Profile::SetSubMethod(Profile::AttackMethod escorttype, Profile::SubMethod sm)
{
	for (int num=squadlist.Max()-1;num>=0;num--)
		if ((squadlist[num].method&AM_GROUPMASK)==escorttype)
		{
			squadlist[num].submethod = sm;
		}
}
void Profile::SetSubMethod(PlaneTypeSelect actype, Profile::SubMethod sm,FormationTypeIndex formation)
{
	for (int num=squadlist.Max()-1;num>=0;num--)
		if ((Node_Data[squadlist[num].squadnum].AcType()&-2)==actype)
		{
			squadlist[num].submethod = sm;
			squadlist[num].FormType() =  (squadlist[num].formtype%FORMTYPE_SQUAD)+formation;
		}
}

static 	 bool	SquadUsedUpInBetterRules(Profile::BetterRule& br,int*	actypecounts,SquadNum sq,int numsquads=1)
{
	if (sq && actypecounts)
	{
		PlaneTypeSelect	pt=PlaneTypeSelect(sq);
		if (sq>=PT_BADMAX)
			pt=Node_Data[sq].AcType();
		if (pt<PT_BRIT_NONFLY)
			pt=PlaneTypeSelect(pt&-2);
		if (actypecounts[pt]<=numsquads)
		{
			br%=Type_To_Rule[pt];
			actypecounts[pt]=0;
			return true;
		}
		else
			actypecounts[pt]-=numsquads;
	}
	return false;
}

int	Profile::AddNumerousSquadrons(int initialbombers,Profile::AttackMethod duty,SquadNum sq,BetterRule br,int* actypecounts)
{  	//request bombers in -ve squadrons/staffel or in +ve numbers of aircraft. Values above 12 are taken as 30+=gruppen, 60+=2 gruppen, 90+=geshwader
	if (initialbombers==0)	return false;
	int totalsquads=1;
	Nationality nat=NAT_RAF;
	if ((duty&Profile::AM_GROUPMASK)!=Profile::AM_RAF)
		nat=NAT_LUF;
	int numspareslots = Todays_Packages.SquadronsPlanned(nat);
	if (nat==NAT_RAF)
		numspareslots = Profile::MAXRAFPLANNEDSQUADRONS - numspareslots;
	else
		numspareslots = Profile::MAXLWPLANNEDSTAFFELN - numspareslots;
	if (numspareslots==0)
		return 0;
	if ((duty&Profile::AM_GROUPMASK)==Profile::AM_RAF)
	{
		if (sq)
			sq=AddSquadron(initialbombers,duty,0,sq);
		else
			sq=AddSquadron(initialbombers,duty,0,br);
		if (!sq) 
			return 0;
		//Ok.. got 1 squadron...
		SquadUsedUpInBetterRules(br,actypecounts,sq);
		if (initialbombers<0)
			for (;sq && initialbombers<-1;initialbombers+=1)
			{
				if (--numspareslots==0)	return totalsquads;
				sq=AddSquadron(-1,duty,0,br,sq);
				SquadUsedUpInBetterRules(br,actypecounts,sq);
				if(sq) totalsquads++;
			}
		else
			for (;sq && initialbombers>19;initialbombers-=10)
			{
				if (--numspareslots==0)	return totalsquads;
				sq=AddSquadron(-1,duty,0,br,sq);
				SquadUsedUpInBetterRules(br,actypecounts,sq);
				if(sq) totalsquads++;
			}
	}
	else
	{
		int	totalbombers=initialbombers;
		if (totalbombers<0)
			totalbombers=-10*totalbombers;
		int	allocatebombers=totalbombers;
		if (allocatebombers>90)
			allocatebombers=90;
		elseif (allocatebombers>=60)
			allocatebombers=60;
		elseif (allocatebombers>30)
			allocatebombers=30;
		if (sq)
		{
//DeadCode JIM 06Nov100 			if (--numspareslots==0)	return totalsquads;
			sq=AddSquadron(allocatebombers,duty,0,sq);
			SquadUsedUpInBetterRules(br,actypecounts,sq);
		}
		else
		{
//DeadCode JIM 06Nov100 			if (--numspareslots==0)	return totalsquads;
			sq=AddSquadron(allocatebombers,duty,0,br);
			SquadUsedUpInBetterRules(br,actypecounts,sq);
			while (allocatebombers>0 && !sq)	//If the above code fails try asking for less!
			{
				allocatebombers-=30;
//DeadCode JIM 06Nov100 			if (--numspareslots==0)	return totalsquads;
				sq=AddSquadron(allocatebombers,duty,0,br);
			}
			if (allocatebombers<=0)
				return 0;
		}
		//Ok.. got 1 squadron...
		Gruppen* g=Node_Data[sq];
		if (allocatebombers>=60)
			if (g->gruppennum==Squadron::GN_3)
				allocatebombers=30;
			elseif (g->gruppennum==Squadron::GN_2)
				allocatebombers=60;
		if (!sq) return false;
		int	acpergrupp=Gruppen::MIN_GRUPPEAC;
		if ((duty&Profile::AM_GROUPMASK)!=AM_LWPACKS)
			acpergrupp=Gruppen::MIN_GRUPPEFIGHTERS;
		if (allocatebombers<30)
		{
			if (allocatebombers>=20)
			{
			if (--numspareslots==0)	return totalsquads;
				AddSquadron(-1,duty,0,sq);
				SquadUsedUpInBetterRules(br,actypecounts,sq);
				totalsquads++;
			}
		}
		else
			do{
				for (int ab=30,cb=2;ab<=allocatebombers;)
				{
					while (--cb>=0)
					{
			if (--numspareslots==0)	return totalsquads;
						AddSquadron(-1,duty,sq);
						SquadUsedUpInBetterRules(br,actypecounts,sq);
					}
			if (--numspareslots==0)	return totalsquads;
					if (AddSquadron(40,duty,sq))
						totalsquads+=1;
					ab+=30;
					cb=3;
					if (ab<=allocatebombers)
					{
						sq=SquadNum(sq+1);
						Gruppen* gr=Node_Data[sq];
						if (gr->periodsuntilready || gr->acavail<acpergrupp)
							allocatebombers-=30;
					}
					
				}
				totalbombers-=allocatebombers;
				if (totalbombers>0)
				{
					while (allocatebombers-30>=totalbombers)
					{
						allocatebombers-=30;
					}
					sq=SQ_ZERO;
					while (!sq && allocatebombers>0)
					{
			if (--numspareslots==0)	return totalsquads;
						sq=AddSquadron(allocatebombers,duty,0,br,sq);
						if (!sq)
							allocatebombers-=30;
						else
						{
							SquadUsedUpInBetterRules(br,actypecounts,sq);
							totalsquads+=1;
						}
					}
				}
			}while (totalbombers>0 && allocatebombers>0);
	}
	return	totalsquads;
}

SquadNum	Profile::AddSquadron(int numac,Profile::AttackMethod duty,SquadNum sn)
{
	return	Profile::AddSquadron(numac,duty,0,sn);
}

SquadNum	Profile::AddSquadron(int numac,Profile::AttackMethod duty,int targnum,BetterRule br,SquadNum after)
{
	if (numac<=0)
	{	//no aircraft supplied... go looking!
		if (duty==AM_PATROL||duty==AM_INTERCEPT)
			numac=12;
		else
			if (numac<-9)
				numac=90;
			else
				numac=30;
	}
	SquadNum sn;
	{	//no squad supplied... go looking!
		sn=PackageList::FindSquad(duty,doglegloc,packagetarget[targnum],numac,br,after);	
	}
	return	Profile::AddSquadron(numac,duty,targnum,sn);
}

SquadNum	Profile::AddSquadron(int numac,Profile::AttackMethod duty,int targnum,SquadNum sn)
{
//DEADCODE RDH 17/05/00 	if (numac<=0)
//DEADCODE RDH 17/05/00 	{	//no aircraft supplied... go looking!
//DEADCODE RDH 17/05/00 		if (duty==AM_PATROL||duty==AM_INTERCEPT)
//DEADCODE RDH 17/05/00 			numac=12;
//DEADCODE RDH 17/05/00 		else
//DEADCODE RDH 17/05/00 			if (numac<-9)
//DEADCODE RDH 17/05/00 				numac=90;
//DEADCODE RDH 17/05/00 			else
//DEADCODE RDH 17/05/00 				numac=30;
//DEADCODE RDH 17/05/00 	}

	if (duty==AM_PATROL||duty==AM_INTERCEPT)
	{
		if ((numac < 0) || (numac> 12))
			numac=12;
	}
	else
	{
		if (numac<-9)
			numac=90;
		else if (numac < 0)
			numac=30;
	}




	if (!sn)
		return SQ_ZERO;
	Squadron *squad=Node_Data[sn];
	if (	numac==40  //using 40 as a special flag that I am trying to create a 4th staffel
		&& (squad->acavail<40 || duty==AM_DECOYPATROL || duty >=AM_DETACHED)
		)
		return SQ_ZERO;
	if (sn>SQ_LW_START)
		numac=PackageList::GetSquadACCountFromGrupp(numac,squad->acavail,duty);

	info_airgrp* a=new info_airgrp;
	a->uniqueID.count=Persons2::assignuid(SagBAND);
	a->package=this;
	Squad* newsquad=
		(squadlist+=a->uniqueID.count);
	Persons2::tabulateUID(a);
	newsquad->SetSquad(sn);
	a->inform=
		newsquad->numacleft=
			newsquad->numacoriginal=numac;

	if ( (sn<SQ_LW_START) == (Todays_Packages.localplayer==NAT_RAF) )
		newsquad->playercansee=true;
	else
		newsquad->playercansee=false;
	newsquad->submethod=SM_ANYA2A;

	if (sn<SQ_LW_START)
	{	//this needs to take account of a leader already flying...
		int	newacmask=0;
		if (BritSquadronPtr(*squad)->usedacbits)
		{
			if (numac<3)
				for (int account=0,masktest=1;account<numac;masktest+=masktest)
				{
					if ((BritSquadronPtr(*squad)->usedacbits&masktest)==0)
					{
						newacmask+=masktest;
						account++;
				}	}
			else
				for (int account=0,masktest=7;account<numac;masktest<<=3)
					if ((BritSquadronPtr(*squad)->usedacbits&masktest)==0)
					{
						newacmask+=masktest;
						account+=3;
					}
		}
		else
			newacmask=(1<<numac)-1;
		BritSquadronPtr(*squad)->usedacbits+=newacmask;
		squadlist.SetAcBitsFirstSquad(newacmask);
	}
	else
	{
		GruppenPtr grupp=*squad;
		if (grupp->periodsuntilready==0)
			if (Node_Data.geschwader[grupp->wadernum].reconn)
				grupp->periodsuntilready=-2;
			else
				grupp->periodsuntilready=-1;
		else
			if (numac>6)
				grupp->periodsuntilready--;	//busy for 1 period. No message on return.
		squadlist.SetAcBitsFirstSquad(0x0fff);
	}

	newsquad->method=duty;

	a->duty=duty;
	a->attmethod=0;
	a->pattern=0;
	a->radiosilence = 0;


	FormationTypeIndex	flightform,interform=FTI_SAME;
	if		(duty>=AM_ATTACHED)
				flightform=FTW_FINGER+FTS_ASTERN;
	else if	(duty>=AM_DETACHED || duty==AM_DECOYPATROL)			
				flightform=FTW_SCWARM+FTS_VIC;
	else if	(duty>=AM_LWPACKS)
		if (numac%5==0)													//CSB 28Jun00
				flightform=FTW_LWVIC+FTS_ASTERN;
		else
				flightform=FTW_LWVIC+FTS_DIAMOND;
	else
				flightform=FTW_RAFVIC+FTS_DIAMOND;
	//need to allocate interpair and serial number next...
	if (duty<AM_ATTACHED)
	{	//need to find out if prev staffel is same gruppen (may not be a previous)
		//if not, start a new count
		int		inccount=-(newsquad-squadlist!=0);
		if (inccount<0)
		{
			Squad* possparent=newsquad-1;
			if (possparent->squadnum!=newsquad->squadnum)
			{
				inccount=0;
				for (possparent=&squadlist[0];possparent!=newsquad;possparent++)
					if ((possparent->method&-8)==(duty&-8))
						inccount=1+((possparent->formtype&FORMTYPE_COURSEPOS)>>FORMTYPE_COURSEPOS_SH);
			}
		}
		if (inccount>=0)
		{
			if (numac==10 && squad->acavail>=40)
							interform=FTIP_LEFTBACK+FTC_MAINFL+FormationTypeIndex(inccount<<FORMTYPE_COURSEPOS_SH);
			else
				if (duty<AM_LWPACKS)
							interform=FTIP_GRUPIII+FORMTYPE_INTERCHILD+FTC_RAF+FormationTypeIndex(inccount<<FORMTYPE_COURSEPOS_SH);
				else
					if (duty<AM_DETACHED)
							interform=FTIP_GRUPIII+FORMTYPE_INTERCHILD+FTC_MAINFL+FormationTypeIndex(inccount<<FORMTYPE_COURSEPOS_SH);
					else
						if ((duty&7)==0)
							interform=FTIP_GRUPIII+FORMTYPE_INTERCHILD+FTC_CEILING+FormationTypeIndex((inccount<<FORMTYPE_COURSEPOS_SH));
						else
							interform=FTIP_GRUPIII+FORMTYPE_INTERCHILD+FormationTypeIndex(FTC_RAF+((duty-AM_DETACHED)<<FORMTYPE_COURSESEL_SH)+(inccount<<FORMTYPE_COURSEPOS_SH));
		}
		else
		{
			Squad* possparent=newsquad-1;
			FormationTypeIndex pft=FormationTypeIndex(possparent->formtype);
			if (pft&FORMTYPE_INTERPAIR==FTIP_LEFTBACK)			//box 4 leader
				interform=(pft%FORMTYPE_INTERPAIR)+FTIP_ASTERN;	//box 4 second
			else
			if (pft&FORMTYPE_INTERPAIR==FTIP_ASTERN)			//box 4 second
				interform=(pft%FORMTYPE_INTERPAIR)+FTIP_LEFT;	//box 4 third
			else
				interform=FormationTypeIndex(pft^FORMTYPE_INTERCHILD);	//lead=true,2nd=false,3rd=true
		}
	}
	else
	{	//need to find escortee & set same position number
		assert(newsquad-squadlist,"Not attached to anything");
		Squad* possparent=NULL;
		int inccount=0;
		for (possparent=newsquad-1;possparent-squadlist;possparent--)
			if ((possparent->method&-8)==(newsquad->method&-8))
				inccount++;
		if ((duty&7)==0)
			interform=FTIP_ASTERN+FTC_FWDLVL+FormationTypeIndex((inccount<<FORMTYPE_COURSEPOS_SH));
		else
			interform=FTIP_GRUPIII+FTC_FWDLVL+FormationTypeIndex(((duty&7)<<FORMTYPE_INTERPAIR_SH)+(inccount<<FORMTYPE_COURSEPOS_SH));
	}


	a->form=flightform+interform;//ListFormExpr(2);								  //JIM 19/05/99//CSB 19May99
	newsquad->FormType() = flightform+interform;			//rdh 23/3/00
	a->bombs=0;
	a->movecode=AUTOSAG_WAITTAKEOFF;
	newsquad->takeofftime=MMC.currtime+5*SECSPERMIN+sn*5;
	newsquad->SetStatus(Profile::PS_PLANNED);
	route=MakeWayPoints(targnum,newsquad-squadlist,duty,sn);

	return sn;
}
AttackMethodField		Profile::FixCloseEscortPositions(AttackMethod escorttype,AttackMethodField amf)
{
	if (escorttype==AM_RAF)
		return	FixRAFPositions(escorttype,amf);

	if (escorttype==AM_LWPACKS || escorttype==AM_DETACHED)
		return	FixIndipendentPositions(escorttype,amf);

	//need to count up main aircraft, and count up escorts of this type (close or return escorts)
	int totalmain=0,totalescort=0;
	for (int num=squadlist.Max()-1;num>=0;num--)
		if ((squadlist[num].method&AM_GROUPMASK)==AM_LWPACKS)
			totalmain++;
		else if ((squadlist[num].method&AM_GROUPMASK)==escorttype)
			totalescort++;

	if (totalescort+totalmain==0)
		return	amf;	
	int	bitsneeded=(totalescort+totalmain-1)/totalmain;
	if (bitsneeded>6)
	{	//all those above the 6 need turning into free escort!
		bitsneeded=6;
		totalescort-=bitsneeded*totalmain;
		for (int num=squadlist.Max()-1;totalescort>0;num--)
			if ((squadlist[num].method&AM_GROUPMASK)==escorttype)
			{
				squadlist[num].method=AM_DETACHED;
				totalescort--;
			}
		totalescort=bitsneeded*totalmain;
	}
	int bitsset=0;
	for (int i=escorttype+6;i!=escorttype;i--)
		bitsset+=amf[AttackMethod(i)];
	if (bitsset<bitsneeded)
		for (int i=escorttype+6;i!=escorttype;i--)
			if (!amf[AttackMethod(i)])
			{
				bitsset++;
				amf|=AttackMethod(i);
				breakif(bitsset==bitsneeded);
			}
	if (bitsset>bitsneeded)
		for (int i=escorttype+6;i!=escorttype;i--)
			if (amf[AttackMethod(i)])
			{
				bitsset--;
				amf%=AttackMethod(i);
				breakif(bitsset==bitsneeded);
			}
	int atfullcount=totalescort-totalmain*(bitsneeded-1);	//we will have to lose 1 escort for remainder
	AttackMethodField amf2=amf;
	int	currbombercounter=0;
	Squad*	bombersquad=&squadlist[0];
	Squad*	fightersquad=&squadlist[0];
//DeadCode JIM 20Oct00 	Squad*	lastsquad=NULL;
	forever	//goes around twice First time up to midway, then to end with 1 less fighter
	{	
		while(currbombercounter<atfullcount)
		{
			//find bomber squad
			while ((bombersquad->method&AM_GROUPMASK)!=AM_LWPACKS)
				bombersquad++;
//DEADCODE JIM 08/02/00 			if (lastsquad==NULL || lastsquad->squadnum!=bombersquad->squadnum)
//DEADCODE JIM 08/02/00 			{
//DEADCODE JIM 08/02/00 				lastsquad=bombersquad;
//DEADCODE JIM 08/02/00 				info_airgrp* a=Persons2::ConvertPtrUID(bombersquad->instance);
//DEADCODE JIM 08/02/00 				a->leader=0;
//DEADCODE JIM 08/02/00 			}
//DEADCODE JIM 08/02/00 			else
//DEADCODE JIM 08/02/00 			{
//DEADCODE JIM 08/02/00 				info_airgrp* a=Persons2::ConvertPtrUID(bombersquad->instance);
//DEADCODE JIM 08/02/00 				a->leader=lastsquad->instance;
//DEADCODE JIM 08/02/00 			}
			for (int i=escorttype+6;i!=escorttype;i--)
				if (amf2[AttackMethod(i)])
				{
					while ((fightersquad->method&AM_GROUPMASK)!=escorttype)
						fightersquad++;
					//ok.. fightersquad will escort bombersquad at location i
					info_airgrp* a=Persons2::ConvertPtrUID(fightersquad->instance);
					a->leader=bombersquad->instance;
					fightersquad->method=AttackMethod(i);								//JIM 28Aug00
					FormationTypeIndex interform=FormationTypeIndex((currbombercounter<<FORMTYPE_COURSESEL_SH)&FORMTYPE_COURSEPAIR);
//DeadCode JIM 19Jul00 					if (currbombercounter<16)
//DeadCode JIM 19Jul00 						interform+=FTC_FWDLVL;
//DeadCode JIM 19Jul00 					else
//DeadCode JIM 19Jul00 						if (currbombercounter<32)
//DeadCode JIM 19Jul00 							interform+=FTC_FWDHIGH;
//DeadCode JIM 19Jul00 						else
//DeadCode JIM 19Jul00 							interform+=FTC_FWDLOW;
					interform+=FormationTypeIndex(FTIP_GRUPIII+((i&7)<<FORMTYPE_INTERPAIR_SH));
					fightersquad->FormType()=interform+(fightersquad->formtype%(FORMTYPE_INTERPAIR+FORMTYPE_COURSEPAIR));
					fightersquad++;
				}
			currbombercounter++;
			bombersquad++;
		}
		if (atfullcount!=totalmain)
		{
			atfullcount=totalmain;
			for (int i=escorttype+6;i!=escorttype;i--)
				if (amf2[AttackMethod(i)])
				{
					amf2%=AttackMethod(i);
					break;
				}
		}
		else
			break;
	}
	return amf;
}
AttackMethodField	Profile::FixRAFPositions(AttackMethod flyingmethod,AttackMethodField amf)
{
	//THE RAF NOW JUST USE THE 8 POSSIBLE SLOTS AS SEQUENTIAL V FORMATION SLOTS
	squadlist[0].FormType()=FTC_RAF;
	UniqueID leader=squadlist[0].instance;
	for (int s=1,max=squadlist,form=FTC_RAF;s<max;s++,form+=FTIP_GRUPIII)
	{
		squadlist[s].FormType()=FormationTypeIndex(form);
		info_airgrp* a=Persons2::ConvertPtrUID(squadlist[s].instance);
		a->leader=leader;
	}
	return amf;
}
AttackMethodField	Profile::FixIndipendentPositions(AttackMethod flyingmethod,AttackMethodField amf)
{
	int totalmain=0,totalbits=1;
	int	squadlistMax=squadlist;
	int previd=-1;
	flyingmethod=AttackMethod(flyingmethod&AM_GROUPMASK);
//DeadCode JIM 20Oct00 	Squadron*	prevsquad=NULL;
	AttackMethodField	optionsset,amfr;
	optionsset=0;
	if (flyingmethod==AM_DETACHED)
	{
		optionsset<<AM_CEILING<<AM_HIGH<<AM_FORWARD_HIGH<<AM_FORWARD<<AM_FORWARD_LOW<<AM_LATE;
		optionsset&=amf;

		totalbits=optionsset.Count();
	}
//count aircraft in gruppen
//divide by options set count
//If > 16 
//	set more bits (assert only for detached)
//apply by rounded up times
//	//
	{for (int num=0;num<squadlistMax;num++)
		if ((squadlist[num].method&AM_GROUPMASK)==flyingmethod)
			if (squadlist[num].squadnum!=previd)
			{
				previd=squadlist[num].squadnum;
				totalmain++;
	}		}

	int	flperbit=17;
	if (totalbits)	
		flperbit=totalmain/totalbits;
	while (flperbit>16)
	{
		assert (flyingmethod==AM_DETACHED,"Only get multiple bits for detached");
		for (int i=AM_CEILING;i<=AM_LATE;i++)
			if (!amf[AttackMethod(i)])
			{
				amf|=AttackMethod(i);
				break;
			}
			assert (i<=AM_LATE," More flights than methods!");
		totalbits++;
		flperbit=totalmain/totalbits;
	}
	if (totalmain==0)
		return	amf;

	int	sqnum=0;
	while (sqnum<squadlistMax && (squadlist[sqnum].method&AM_GROUPMASK)!=flyingmethod)
		sqnum++;
	int	am;
	if (flyingmethod==AM_DETACHED)
		am=AM_CEILING;
	else
		am=squadlist[sqnum].method;
	while (totalbits)
	{
		int	newlayoutcoursesel;
		if (flyingmethod==AM_DETACHED)
		{
			while (!amf[AttackMethod(am)])
				am++;
			newlayoutcoursesel=FTC_CEILING+((am-AM_CEILING)<<FORMTYPE_COURSESEL_SH);
		}
		elseif (flyingmethod==AM_LWPACKS)
			newlayoutcoursesel=FTC_MAINFL;
		else
			newlayoutcoursesel=FTC_RAF;
		flperbit=totalmain/totalbits;
		totalbits--;
		totalmain-=flperbit;
		for (int flnum=0;flnum<flperbit;flnum++)
		{
			while((squadlist[sqnum].method&AM_GROUPMASK)!=flyingmethod)
				sqnum++;

			int	newlayout=(flnum<<FORMTYPE_COURSEPOS_SH)+newlayoutcoursesel;
			int	newescform=squadlist[sqnum].formtype&FORMTYPE_INTERPAIR;
			int	wingsquad=squadlist[sqnum].formtype&FORMTYPE_WINGSQUAD;
			int	previd=squadlist[sqnum].squadnum;
			UniqueID	leadinst=squadlist[sqnum].instance;
			info_airgrp*	a=Persons2::ConvertPtrUID(leadinst);
			if (sqnum==0)
				a->leader=ENABLE_COMPLEX_VAL;
			else
				a->leader=UID_NULL;
//DeadCode JIM 20Oct00 			int	mastersq=sqnum;
			squadlist[sqnum].FormType()=FormationTypeIndex(newlayout+newescform+wingsquad);
			squadlist[sqnum].method=AttackMethod(am);
			for (	sqnum++;
					sqnum<squadlistMax	&&	squadlist[sqnum].squadnum==previd;	
					sqnum++
				)
			{  	
				switch (newescform)
				{
				case	FTIP_GRUPII:	newescform=FTIP_GRUPIII;	break;
				case	FTIP_GRUPIII:	newescform=FTIP_GRUPII;		break;

				case	FTIP_AHEAD:		newescform=FTIP_ASTERN;		break;	//4-way series if leader set to ahead
				case	FTIP_ASTERN:	newescform=FTIP_LEFT;		break;	//3-way series M-L-R if leader set to astern
				case	FTIP_LEFT:		newescform=FTIP_LEFTBACK;	break;	
				case	FTIP_LEFTBACK:	newescform=FTIP_AHEAD;		break;	//Also Right. Set as leader to get M-F-B

				case	FTIP_ABOVE:		newescform=FTIP_BELOW;		break;
				case	FTIP_BELOW:		newescform=FTIP_ABOVE;		break;
				}

				a=Persons2::ConvertPtrUID(squadlist[sqnum].instance);
				a->leader=leadinst;
				squadlist[sqnum].FormType()=FormationTypeIndex(newlayout+newescform+wingsquad);
				squadlist[sqnum].method=AttackMethod(am);
			}

		}
		am++;
	}
	return	amf;
}
bool	PackageList::FlyableAircraftAvailable()
{
	bool	avail = false;
	return(avail);
}





UniqueID	Profile::MakeWayPoints(int targetnum,int squadinpack,Profile::AttackMethod duty,SquadNum sq)
{	//

//DEADCODE DAW 25/11/99  	UniqueID wt,waf,wal,wpf,wpl,wr;
//DEADCODE DAW 25/11/99 	GetKeyTargetWPs(wt,waf,wal,wpf,wpl,wr);
//DEADCODE DAW 25/11/99 	UniqueID targ2=UID_NULL;
//DEADCODE DAW 25/11/99 	UniqueID patrolbeginitem=UID_NULL;
//DEADCODE DAW 25/11/99 	Coords3D wp0;
//DEADCODE DAW 25/11/99 	Coords3D wp1;

	UniqueID	tof,tol,ipf,ipl,ldf,ldl;
	GetKeyMainWPs(tof,tol,ipf,ipl,ldf,ldl);
	UniqueID takeoff=Node_Data[sq].homeairfield;
//UniqueID	Profile::InsertWpBetween(UniqueID&wp1,UniqueID&wp2,UniqueID targetref,BFieldWaypointActions a,int group,SavedGlobrefs setgr)

	squadlist[squadinpack].takeoffwp=InsertWpBetween(tof,tol,takeoff,wpatakeoffno,squadinpack,ENABLE_COMPLEX_VAL, SGR_WPC_TakeOff, METRES00);	//RDH 28Jun00
	squadlist[squadinpack].landingwp=InsertWpBetween(ldf,ldl,takeoff,wpalandingno,squadinpack,ENABLE_COMPLEX_VAL,SGR_WPC_Landing, FT_3000);	//RDH 28Jun00
	info_waypointPtr(Persons2::ConvertPtrUID(squadlist[squadinpack].landingwp))->range=METRES2500;
//DEADCODE  23/02/00 	if ((ipf=FindTargetWpBetween(ipf,ipl,SavedGlobrefs(SGR_Pack_Target+targetnum)))==UID_NULL)
//DEADCODE  23/02/00 	{
//DEADCODE  23/02/00 		UniqueID newwp=AddAttackWP(targetnum,duty);
//DEADCODE  23/02/00 		packagetarget[targetnum].targetwaypoint=newwp;
//DEADCODE  23/02/00 	}
	return tof;
}
UniqueID	Profile::AddAttackWP(int targetnum,Profile::AttackMethod duty,int alt)
{
	UniqueID newwp;
	if (targetnum==-1)
		duty=AM_PATROL;
	switch (duty)
	{
	case	AM_INTERCEPT:
	case	AM_RECON:
	case	AM_DIVEBOMB:
	case	AM_LEVELBOMB:
	case	AM_CHAINBOMB:
		{
			BFieldWaypointActions act=wpbombno;
			switch (duty)
			{
			case	AM_INTERCEPT:	act=wpengagetargetno;alt=METRES500;	break;
			case	AM_RECON:		act=wpreccyno;			break;
			default:				act=wpbombno;			break;	
			}
			UniqueID	tof,tol,ipf,ipl,ldf,ldl;
			GetKeyMainWPs(tof,tol,ipf,ipl,ldf,ldl);
			Coords3D	c3d;
			newwp=InsertWpBetween(ipf,ipl,SavedGlobrefs(SGR_Pack_Target+targetnum),act,ENABLE_COMPLEX_VAL,targetnum,UID_NULL,SGR_WPC_Target,alt);
			info_waypoint*	w=*Persons2::ConvertPtrUID(newwp);
			w->range=METRES7000;
			wpsused++;

	
		}
	break;
	default:
		{
			UniqueID	tof,tol,ipf,ipl,ldf,ldl;
			GetKeyMainWPs(tof,tol,ipf,ipl,ldf,ldl);
			UniqueID newendwp=	InsertWpBetween(ipf,ipl,UID_NULL,wpstartloopno,	ENABLE_COMPLEX_VAL,targetnum,SGR_WPC_PatrolS,alt);
			{
				info_waypoint*	wp1=*Persons2::ConvertPtrUID(newendwp);
				wp1->target=ENABLE_COMPLEX_VAL;
				wp1->position.MakeIcptGRExpr(SGR_WPP_EstPoint,SGR_WPP_IP,false);
				wp1->position[1][1]=alt;	 //alt						//RDH 28Jun00
				wp1->position[2][1]=METRES7000;		//range
				wp1->position[2][2]=ANGLES_100Deg;
			}
			newwp=		InsertWpBetween(newendwp,ipl,UID_NULL,wpstoploopchkno,	ENABLE_COMPLEX_VAL,targetnum,SGR_WPC_PatrolE,alt);
			{
				info_waypoint*	wp0=*Persons2::ConvertPtrUID(newwp);
				wp0->position.MakeIcptGRExpr(SGR_WPP_EstPoint,SGR_WPP_IP,false);
				wp0->target=ENABLE_COMPLEX_VAL;
				wp0->position[1][1]=alt;								//RDH 28Jun00
				wp0->position[2][1]=METRES7000;
				wp0->position[2][2]=ANGLES_260Deg;
			}
			wpsused++;
			wpsused++;
		}
	}
	return	newwp;
}
UniqueID	Profile::MakePrimaryRoute(int Y)
{	//Build a route which links key points in package
	//points are:
	//	H:	primary home-base
	//	T:	target
	//	E:	egress
	//These are the globrefs 
		//Pack_Takeoff
		//Pack_Target
		//Pack_Regroup

	//route contains //These are not the precise figures. Read the code percentages!
	//	Rendevous	(H..T*.2)	- Wave forms up here
	//	Ingress		(H..T*.5)	- Cross front line
	//	Target		(H..T*.9)	- Approaching target - all do different roles
	//	Regroup		(T..E*.1)	- Finished bombing - all form up again
	//	Egress		(T..E*.9)	- exit over sea - B52s go home from here
	//	Disperse	(E..H*.7)	- break formation and fly to home airfields
	UniqueID rv=UID_Null;
	if (attackmethod>AM_LWPACKS)
	{
		rv=MakeInterceptWP(SGR_WPP_Egress,SGR_Pack_Takeoff,			70,rv,SGR_WPP_BombDisperse,Y/2,wpdisperseno);

		rv=MakeInterceptWP(SGR_WPP_Egress,SGR_WPP_BombDisperse,		70,rv,SGR_WPP_EscDisperse,Y,wpdisperseno);
	}
	else
	{
		rv=MakeInterceptWP(SGR_WPP_Egress,SGR_Pack_Takeoff,		70,rv,SGR_WPP_EscDisperse,Y,wpdisperseno);
	}
	rv=MakeInterceptWP(SGR_WPP_EstPoint,SGR_Pack_Takeoff,		METRES15KM,rv,SGR_WPP_Egress,Y);
	if (attackmethod>AM_LWPACKS)
		info_waypointPtr(Persons2::ConvertPtrUID(rv))->position[2][2]=ANGLES_90Deg;
	else
		info_waypointPtr(Persons2::ConvertPtrUID(rv))->position[2][2]=ANGLES_60Deg;
	rv=MakeInterceptWP(SGR_Pack_Target,SGR_Pack_BlankZero,		METRES100,rv,SGR_WPP_Target,Y);
		info_waypointPtr(Persons2::ConvertPtrUID(rv))->applywave=-2;
	//if (moving target)

	rv=MakeInterceptWP(SGR_Pack_Target,SGR_Pack_BlankZero,		70,rv,SGR_WPP_EstPoint,Y);
		info_waypointPtr(Persons2::ConvertPtrUID(rv))->applywave=-2;

	Ranges	iprange=METRES15KM;
	if (attackmethod<=AM_DIVEBOMB)
		iprange=METRES10KM;

	if (doglegloc!=packagetarget[0].currentid)
	{
		rv=MakeInterceptWP(SGR_WPP_EstPoint,SGR_WPP_DogLeg,			iprange,rv,SGR_WPP_IP,Y);
		rv=MakeInterceptWP(SGR_Pack_DogLeg,SGR_Pack_BlankZero,		METRES1000,rv,SGR_WPP_DogLeg,Y);
	}
	else
	{
		rv=MakeInterceptWP(SGR_WPP_EstPoint,SGR_Pack_Takeoff,	iprange,rv,SGR_WPP_IP,Y);
		rv=MakeInterceptWP(SGR_WPP_IP,SGR_Pack_Takeoff,		10,rv,SGR_WPP_DogLeg,Y);
	}

	if (attackmethod>AM_LWPACKS)
	{
		rv=MakeInterceptWP(SGR_WPP_DogLeg,SGR_WPP_BombRendezvous,	50,rv,SGR_WPP_EscRendezvous,Y);
		rv=MakeInterceptWP(SGR_WPP_DogLeg,SGR_Pack_Takeoff,			50,rv,SGR_WPP_BombRendezvous,Y/2);
	}
	else
	{
		rv=MakeInterceptWP(SGR_WPP_DogLeg,SGR_Pack_Takeoff,		60,rv,SGR_WPP_EscRendezvous,Y);
	}
	return	rv;
}

UniqueID	Profile::MakeInterceptWP(SavedGlobrefs a,SavedGlobrefs b,Ranges distance,UniqueID next,SavedGlobrefs as,int deltaalt,BFieldWaypointActions action/*=wpacnoactionno*/)
{
	return 	MakeInterceptWP(a,b,-distance,next,as,deltaalt,action);
}
UniqueID	Profile::MakeInterceptWP(SavedGlobrefs a,SavedGlobrefs b,int percent,	UniqueID next,SavedGlobrefs as,int deltaalt,BFieldWaypointActions action/*=wpacnoactionno*/)
{
	UniqueID rv;
	info_waypoint* wp0=new info_waypoint;
	wp0->range=METRES100;
	if (b)
	{
		wp0->position.MakeIcptGRExpr(a,b,(percent>=0));
		wp0->position[1][1]=deltaalt;
		if (percent<0)
			wp0->position[2][1]=-percent;
		else
			wp0->position[2][1]=percent;
		wp0->position[2][2]=0;
	}
	else
	{
		wp0->position.MakeAngWorldPos(a,deltaalt);
		wp0->position[2][0]=-percent;
//		wp0->target=new GlobRefExpr(a);
	}
//DEADCODE JIM 24/03/99 	wp0->position[2][3]=0;		  //pitch mod!
	wp0->nextwp=next;
	wp0->uniqueID.count=
		rv=Persons2::assignuid(WayPointBAND);
	info_waypoint *wp;
//DEADCODE JIM 03/03/99 	if (rv == 355)	//debug
//DEADCODE JIM 03/03/99 	{
//DEADCODE JIM 03/03/99   		wp = *Persons2::ConvertPtrUID(rv);
//DEADCODE JIM 03/03/99 	}
	if (action!=wpacnoactionno)
		wp0->wpact=action;
	Persons2::tabulateUID(wp0);
	if (as!=SGR_Pack_BlankZero)
		wp0->uid=-as;
	if (next)
	{
		wp0=*Persons2::ConvertPtrUID(next);
		wp0->prevwp=rv;
	}
	return rv;
}

bool	Profile::GetKeyMainWPs(UniqueID& firsttakeoff,UniqueID &takeoffarea,UniqueID& targetarea,UniqueID& regrouparea,UniqueID& landingarea,UniqueID& lastlanding)
{	//if there are no target waypoints then sets TARGET as all 4 and returns false
	UniqueID u=route;
	if (!u) 
		return false;
	info_waypoint* w=*Persons2::ConvertPtrUID(u);
	if (w->applygroup.Evaluate()==ENABLE_COMPLEX_VAL)
	{
		firsttakeoff=UID_NULL;
	}
	else
	{
		firsttakeoff=u;
		while (w->applygroup.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			u=w->NextWP(-1);
			w=*Persons2::ConvertPtrUID(u);
		}
	}
	takeoffarea=u;
	while(w->uid.Evaluate()!=-SGR_WPP_IP)// &&	w->uid.Evaluate()!=-SGR_WPP_IP)
		w=*Persons2::ConvertPtrUID(u=w->nextwp);
	targetarea=u;
	
	do{
		u=w->NextWP(-1);
		w=*Persons2::ConvertPtrUID(u);
	}while (w->applygroup.Evaluate()!=ENABLE_COMPLEX_VAL);

	regrouparea=u;

	while(w->uid.Evaluate()!=-SGR_WPP_BombDisperse && w->uid.Evaluate()!=-SGR_WPP_EscDisperse)
		w=*Persons2::ConvertPtrUID(u=w->nextwp);
	landingarea=u;
	lastlanding=UID_NULL;
	while (w)
	{
		if (w->uid.Evaluate()==-SGR_WPP_BombDisperse)
			landingarea=u;
		else
			if (!w->nextwp)
				lastlanding=u;
		w=*Persons2::ConvertPtrUID(u=w->nextwp);
	}
		
	return true;


}

//DEADCODE DAW 14/03/00 bool	Profile::GetKeyTargetWPs(UniqueID& targetarea,UniqueID& firststartpatrolbomb,UniqueID& laststartpatrolbomb,UniqueID& firstendpatrol,UniqueID& lastendpatrol,UniqueID& regrouparea)
//DEADCODE DAW 14/03/00 {	//if there are no target waypoints then sets TARGET as all 4 and returns false
//DEADCODE DAW 14/03/00 	firststartpatrolbomb=
//DEADCODE DAW 14/03/00 		laststartpatrolbomb=
//DEADCODE DAW 14/03/00 			firstendpatrol=
//DEADCODE DAW 14/03/00 				lastendpatrol=
//DEADCODE DAW 14/03/00 					UID_Null;
//DEADCODE DAW 14/03/00 	UniqueID u=route;
//DEADCODE DAW 14/03/00 	info_waypoint* w=*Persons2::ConvertPtrUID(u);
//DEADCODE DAW 14/03/00 	while(w->uid.Evaluate()!=-SGR_WPP_Target &&	w->uid.Evaluate()!=-SGR_WPC_Target)
//DEADCODE DAW 14/03/00 		w=*Persons2::ConvertPtrUID(u=w->nextwp);
//DEADCODE DAW 14/03/00 	targetarea=u;
//DEADCODE DAW 14/03/00 	while(w->uid.Evaluate()!=-SGR_WPP_Egress)
//DEADCODE DAW 14/03/00 	{
//DEADCODE DAW 14/03/00 		if (w->wpact.Evaluate()!=GOT_UNDEFINED_VAL)
//DEADCODE DAW 14/03/00 			if(		w->wpact.Evaluate()==wpstoploopchkno 
//DEADCODE DAW 14/03/00 				||	w->wpact.Evaluate()==wpsecondaryno)
//DEADCODE DAW 14/03/00 				if (firstendpatrol)
//DEADCODE DAW 14/03/00 					lastendpatrol=u;
//DEADCODE DAW 14/03/00 				else
//DEADCODE DAW 14/03/00 					firstendpatrol=u;
//DEADCODE DAW 14/03/00 			else
//DEADCODE DAW 14/03/00 				if (firststartpatrolbomb)
//DEADCODE DAW 14/03/00 					laststartpatrolbomb=u;
//DEADCODE DAW 14/03/00 				else
//DEADCODE DAW 14/03/00 					firststartpatrolbomb=u;
//DEADCODE DAW 14/03/00 		w=*Persons2::ConvertPtrUID(u=w->nextwp);
//DEADCODE DAW 14/03/00 	}
//DEADCODE DAW 14/03/00 	regrouparea=u;
//DEADCODE DAW 14/03/00 	if (!firststartpatrolbomb)
//DEADCODE DAW 14/03/00 		firststartpatrolbomb=targetarea;
//DEADCODE DAW 14/03/00 	if (!laststartpatrolbomb)
//DEADCODE DAW 14/03/00 		laststartpatrolbomb=firststartpatrolbomb;
//DEADCODE DAW 14/03/00 	if (!firstendpatrol)
//DEADCODE DAW 14/03/00 		firstendpatrol=laststartpatrolbomb;
//DEADCODE DAW 14/03/00 	if (!lastendpatrol)
//DEADCODE DAW 14/03/00 		lastendpatrol=firstendpatrol;
//DEADCODE DAW 14/03/00 	return (lastendpatrol!=targetarea);
//DEADCODE DAW 14/03/00 }

//wpacnoactionno
UniqueID	Profile::FindSquadWpBetween(UniqueID wp1,UniqueID wp2,int group)
{
	UniqueID u=wp1;
	info_waypoint *w=*Persons2::ConvertPtrUID(u);

	forever
	{
		if (group==w->applygroup.Evaluate())
//DEADCODE DAW 25/11/99 			if (	flight==-1	||	w->applyflight.Evaluate()==GOT_UNDEFINED_VAL
//DEADCODE DAW 25/11/99 				||	w->applyflight.Evaluate()==flight)
//DEADCODE DAW 25/11/99 				if (elt==-1 || w->applyelt.Evaluate()==GOT_UNDEFINED_VAL
//DEADCODE DAW 25/11/99 					||	elt==w->applyelt.Evaluate())
					return(u);
		if (u==wp2)	
			return(UID_Null);
		w=*Persons2::ConvertPtrUID(u=w->nextwp);
	}
//	return UID_Null;
}
UniqueID	Profile::FindTargetWpBetween(UniqueID wp1,UniqueID wp2,SavedGlobrefs targnum)
{

	UniqueID u=wp1;
	info_waypoint *w=*Persons2::ConvertPtrUID(u);

	forever
	{
		if (targnum==w->target)
//DEADCODE DAW 25/11/99 			if (	flight==-1	||	w->applyflight.Evaluate()==GOT_UNDEFINED_VAL
//DEADCODE DAW 25/11/99 				||	w->applyflight.Evaluate()==flight)
//DEADCODE DAW 25/11/99 				if (elt==-1 || w->applyelt.Evaluate()==GOT_UNDEFINED_VAL
//DEADCODE DAW 25/11/99 					||	elt==w->applyelt.Evaluate())
					return(u);
		if (u==wp2)	
			return(UID_Null);
		w=*Persons2::ConvertPtrUID(u=w->nextwp);
	}
//	return UID_Null;
}

UniqueID	Profile::FindSquadWpAfter(UniqueID wp1,UniqueID wp2,int group)
{
	UniqueID u=wp1;
	if (!u || u==wp2)
		return UID_Null;
	info_waypoint *w=*Persons2::ConvertPtrUID(u);
	w=*Persons2::ConvertPtrUID(u=w->nextwp);
	forever
	{
		if (group==w->applygroup.Evaluate())
//DEADCODE DAW 25/11/99 			if (	flight==-1	||	w->applyflight.Evaluate()==GOT_UNDEFINED_VAL
//DEADCODE DAW 25/11/99 				||	w->applyflight.Evaluate()==flight)
//DEADCODE DAW 25/11/99 				if (elt==-1 || w->applyelt.Evaluate()==GOT_UNDEFINED_VAL
//DEADCODE DAW 25/11/99 					||	elt==w->applyelt.Evaluate())
					return(u);
		if (u==wp2)	
			return(UID_Null);
		w=*Persons2::ConvertPtrUID(u=w->nextwp);
	}
//	return UID_Null;
}
UniqueID	Profile::FindTargetWpAfter(UniqueID wp1,UniqueID wp2,SavedGlobrefs targnum)
{
	UniqueID u=wp1;
	if (!u || u==wp2)
		return UID_Null;
	info_waypoint *w=*Persons2::ConvertPtrUID(u);
	w=*Persons2::ConvertPtrUID(u=w->nextwp);
	forever
	{
		if (targnum==w->target)
//DEADCODE DAW 25/11/99 			if (	flight==-1	||	w->applyflight.Evaluate()==GOT_UNDEFINED_VAL
//DEADCODE DAW 25/11/99 				||	w->applyflight.Evaluate()==flight)
//DEADCODE DAW 25/11/99 				if (elt==-1 || w->applyelt.Evaluate()==GOT_UNDEFINED_VAL
//DEADCODE DAW 25/11/99 					||	elt==w->applyelt.Evaluate())
					return(u);
		if (u==wp2)	
			return(UID_Null);
		w=*Persons2::ConvertPtrUID(u=w->nextwp);
	}
//	return UID_Null;
}

void	Profile::RemoveWpBetween(UniqueID&wp1,UniqueID&wp2,UniqueID wptoremove)
{
	if (!wptoremove)
		return;
	info_waypoint *w=*Persons2::ConvertPtrUID(wptoremove);
	info_waypoint *wn=*Persons2::ConvertPtrUID(w->nextwp);
	info_waypoint *wp=*Persons2::ConvertPtrUID(w->prevwp);
	wn->prevwp=w->prevwp;
	wp->nextwp=w->nextwp;
	if (wp1==wptoremove)
		if (wp2==wp1)
			wp2=wp1=w->prevwp;
		else
			wp1=w->nextwp;
	else
		if (wp2==wptoremove)
			wp2=w->prevwp;
	delete(w);
	Persons2::delUID(wptoremove);
}

UniqueID	Profile::InsertWpBetween(UniqueID&wp1,UniqueID&wp2,SavedGlobrefs targetref,BFieldWaypointActions a,int group,int wave,UniqueID targetuid,SavedGlobrefs setgr,int alt)
{
//allocate and initialise the new waypoint:
	info_waypoint *w=new info_waypoint;
	UniqueID rv=
		w->uniqueID.count=Persons2::assignuid(WayPointBAND);
	Persons2::tabulateUID(w);

	if (a)
	{
		w->wpact=a;
	}

	if (targetref)
		if (targetref==SGR_WPP_Target || targetref==SGR_WPC_Target || targetref==SGR_WPP_EstPoint)	  //waypoint!!
		{

			w->position.MakeAngWorldPos(targetref,100000);
//DEADCODE JIM 28/06/99 			w->target=new GlobRefExpr(targetref);
		}
		else
		{

			w->position.MakeAbsWorldPos(alt);
			w->target=new GlobRefExpr(targetref);
		}
	else
	if (targetuid)
		if (Persons2::getbandfromUID(targetuid)==WayPointBAND)
			w->position.MakeRelWorldPos(targetuid);
		else
		{
			w->position.MakeAbsWorldPos(alt);
			w->target=targetuid;
		}
	else
	{
		w->position.MakeAbsWorldPos(alt);
		w->target=new GlobRefExpr(SGR_Pack_Target);
	}

	w->range=METRES100;												  //JIM 08/04/99
	if (setgr)
		w->uid=-setgr;
	w->applygroup=group;
	w->applywave=wave;
//mesh the new waypoint in:	
	UniqueID	pu;
	pu=wp1;
	if (wp1==NULL)
	{
		wp1=rv;
		info_waypoint *wp=*Persons2::ConvertPtrUID(wp2);
		wp->prevwp=rv;
		w->nextwp=wp2;
		w->prevwp=UID_NULL;
	}
	else
	if (wp2==NULL)
	{
		info_waypoint *wp=*Persons2::ConvertPtrUID(pu);
		wp->nextwp=rv;
		w->prevwp=wp2;
		w->nextwp=UID_NULL;
		wp2=rv;
	}
	else
	{
		info_waypoint *wp=*Persons2::ConvertPtrUID(pu);
		w->nextwp=wp->nextwp;
		wp->nextwp=rv;
		w->prevwp=pu;
		info_waypoint *wn=*Persons2::ConvertPtrUID(w->nextwp);
		if (wn)
			wn->prevwp=rv;


		if (a && wp1==wp2)
		{	//fix route list delimiters
			if (wp->wpact.Evaluate()==0 || wp->wpact.Evaluate()==GOT_UNDEFINED_VAL)
				wp1=rv;
			wp2=rv;
		}
	}
	return rv;
}
int	Profile::CalcRoutePositionsAndTime(int preferredtime,SavedGlobrefs faketo,bool allowETArecalc)
{
	//This is called from dozens of places and the rules for wether we can faketo are complicated.
	//Only RAF directive generated methods should now actually set faketo.
	//If faketo is clear I am possibly going to set it here.
	if (faketo==SGR_Pack_BlankZero)
	{
		if (packagetarget[1].operator UniqueID()<SagBAND || packagetarget[1].operator UniqueID()>=SagBANDEND)
			if (packagetarget[2].operator UniqueID()<SagBAND || packagetarget[2].operator UniqueID()>=SagBANDEND)
				faketo=SGR_WPP_DogLeg;
	}


	RecalcRoutePositions();
	int absrvtime;
	int slowestsq;
	primarytargetETA = FindEarliestPrimaryTargetETA(absrvtime,slowestsq);
//DeadCode MS 28Oct100 	if (preferredtime > primarytargetETA)
	if (UniqueID(packagetarget[0])<SagBANDEND || preferredtime > primarytargetETA)
	{
		int delta=primarytargetETA-preferredtime; 
		absrvtime-=delta;
		primarytargetETA -=delta; 
	}
	else
		if (preferredtime)
			NOP;
	int slowestsq_totime = CalcWPAbsTimes(absrvtime,slowestsq );
	if(SetPredictedPointFromETA(faketo,!allowETArecalc))
	{
		RecalcRoutePositions();
		bool timingok=CalcWPTimes();
		if(!timingok && packagestatus<PS_TAKINGOFF)
		{
			primarytargetETA=primarytargetETA+MMC.currtime+SECSPERMIN*2-squadlist[slowestsq].takeofftime;
			SetPredictedPointFromETA(faketo,true);
			RecalcRoutePositions();
			timingok=CalcWPTimes();
			while(!timingok)
			{
				primarytargetETA+=SECSPERMIN;
				SetPredictedPointFromETA(faketo,true);
				RecalcRoutePositions();
				timingok=CalcWPTimes();
			}


		}
	}
	int fuel;														//rdh 17Jul00
	SquadNum sq;
	if ((sq=CalcFuel(UID_NULL, fuel, fuel,false))!=SQ_ZERO)
		if (	!Todays_Packages.squelchfuelwarning 
			&& (Todays_Packages.localplayer==NAT_RAF)==(attackmethod<AM_LWPACKS)
			)
		Todays_Packages.MessageBoxFuelWarning(sq);

	return	(slowestsq_totime);	//SHOULD RETURN TIME FOR SLOWEST SQUAD TO BEGIN MOVE
}
void	Profile::RecalcRoutePositionsAndTime()
{
	RecalcRoutePositions();
	CalcWPTimes();


}
void	Profile::RecalcRoutePositions()
{
//DeadCode JIM 3Jul00 	if (Persons2::ConvertPtrUID(route))
//DeadCode JIM 3Jul00 		packagetakeoff=UniqueID(info_waypointPtr(Persons2::ConvertPtrUID(squadlist[0].takeoffwp))->target.Evaluate());
	SetTargetGlobrefs();
	RecalcPrimaryPositions();
//DeadCode RDH 16Mar100 	int t = 0, t1 = 0, t2 = 0;
//DeadCode RDH 16Mar100 	CalcWPTimes(t,t1,t2);

//DEADCODE DAW 25/11/99 	for (int i=1;i<MAX_WAVES;i++)
//DEADCODE DAW 25/11/99 		if (wave[i].firstwp)
//DEADCODE DAW 25/11/99 		{
//DEADCODE DAW 25/11/99 			RecalcSecondaryPositions(i);
//DEADCODE DAW 25/11/99 			CalcWPTimes(i);
//DEADCODE DAW 25/11/99 		}

}

void	Profile::SetTargetGlobrefs(bool fixconvoys)
{
//DEADCODE JON 22/02/00 	if (Persons2::ConvertPtrUID(route))
//DEADCODE JON 22/02/00 		packagetakeoff=UniqueID(info_waypointPtr(Persons2::ConvertPtrUID(squadlist[0].takeoffwp))->target.Evaluate());
//DEADCODE DAW 25/11/99 	packagetakeoff=takeoffAF;
//DEADCODE DAW 22/11/99 	UniqueID targ=packagetarget;
//DEADCODE JIM 16/11/99 	if (Persons2::getbandfromUID(targ)==RedRoadBAND || Persons2::getbandfromUID(targ)==RedRailBand	)				  //JIM 12/04/99
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99 		SupplyNode* node= SupplyTree::FindSupplyNodeForNodeItem(targ);
//DEADCODE JIM 16/11/99 		targ=node->associated_item;
//DEADCODE JIM 16/11/99 	}

//DEADCODE DAW 22/11/99 	Persons2::SetLoc(SGR_Pack_Target,targ);
	Persons2::SetLoc(SGR_Pack_DogLeg,doglegloc);
	Persons2::SetLoc(SGR_Pack_Takeoff,packagetakeoff);
//DEADCODE DAW 22/11/99 	for (int gr=SGR_Pack_Targ_F0_E0;gr<=SGR_Pack_Targ_Fmax_E1;gr++)
//DEADCODE DAW 22/11/99 		Persons2::SetLoc(gr,0);
	for (int gr=0;gr<=9;gr++)
		if (packagetarget[gr])
			Persons2::SetLoc(SGR_Pack_Target+gr,packagetarget[gr]);
		else
			Persons2::SetLoc(SGR_Pack_Target+gr,0);

}

void	Profile::RecalcPrimaryPositions()
{
//TEMPCODE DAW 18/01/00 	packagetakeoff=UniqueID(info_waypointPtr(Persons2::ConvertPtrUID(squadlist[0].takeoffwp))->target.Evaluate());
	{
//DeadCode JIM 3Jul00 		packagetakeoff=UniqueID(info_waypointPtr(Persons2::ConvertPtrUID(squadlist[0].takeoffwp))->target.Evaluate());
		Persons2::SetLoc(SGR_Pack_Takeoff,packagetakeoff);
	}
	SetGlobRefsForRoute(route);
	RepositionSubWaypoints(route);
}
//DEADCODE DAW 25/11/99 void	Profile::RecalcSecondaryPositions(int w)
//DEADCODE DAW 25/11/99 {
//DEADCODE DAW 25/11/99 	SetGlobRefsForRoute(wave[w].firstwp);
//DEADCODE DAW 25/11/99 	RepositionSubWaypoints(wave[w].firstwp);
//DEADCODE DAW 25/11/99 }

void	Profile::SetGlobRefsForRoute(UniqueID wpuidstart)
{
	//first clear all Waypoint globrefs:
	for (int gr=SGR_WPP_TakeOff;gr<=SGR_WPP_Msg9;gr++)
			Persons2::SetLoc(gr,GOT_UNDEFINED_VAL);

	bool donesome,failedsome;
	int	passes=0;
	do{
		passes++;
		donesome=failedsome=false;
		UniqueID wpuid=wpuidstart;
		while (wpuid)
		{
			info_waypoint* w=*Persons2::ConvertPtrUID(wpuid);
			if (w->uid!=GOT_UNDEFINED_VAL && w->uid>-SGR_WPP_Landing)					//don't do it here
				if (Persons2::GetLoc(-w->uid)==GOT_UNDEFINED_VAL)		//already done it here
				{
					w->World.X=w->World.Y=w->World.Z=0;
					UniqueID failiure=w->position.EvalW(w->World);
					if (!failiure)
					{
						if (w->target!=GOT_UNDEFINED_VAL || w->target.complex)
							if (w->target.Evaluate()!=GOT_UNDEFINED_VAL)
							{
								COORDS3D& base=
									Persons2::ConvertPtrUID(UniqueID(w->target.Evaluate()))->World;
								w->World.X+=base.X;
								w->World.Y+=base.Y;
								w->World.Z+=base.Z;
								Persons2::SetLoc(-w->uid,w->uniqueID.count);
								donesome=true;
							}
							else
								failedsome=true;
						else
						{
							Persons2::SetLoc(-w->uid,w->uniqueID.count);
							donesome=true;
						}
					}
					else
						failedsome=true;

				}
			wpuid=w->nextwp;
		}
	}while (donesome);
	if (failedsome)	
		_Error.EmitSysErr("Couldn't fix up recursive waypoints after %i passes",passes); 
}

//TEMPCODE RDH 03/03/00 Float		Profile::InterceptDistance(Coords3D& interceptor,Coords3D& targetstart,Coords3D& targetend,int	interceptorspeed,int targetspeed)
//TEMPCODE RDH 03/03/00 {
//TEMPCODE RDH 03/03/00 
//TEMPCODE RDH 03/03/00 
//TEMPCODE RDH 03/03/00 }
//TEMPCODE RDH 03/03/00 

//////////////////////////////////////////////////////////////////////
//
// Function:    SetPredictedPointFromETA
// Date:		20/09/00
// Author:		JIM
//
//Description: 	returns true if changed...
//
//////////////////////////////////////////////////////////////////////
bool	Profile::SetPredictedPointFromETA(SavedGlobrefs faketo,bool recalcfromETA)
{
	//Cludge number 36:
	//If the isoscilese intercept is not good enough for the RAF
	//then they use the mobileitem code to give a better ETA.
	//
	//
	//
	info_itemSPtr p=Persons2::ConvertPtrUID(packagetarget[0]);
	if (p->Status.size>=MOBILESIZE) 
		if (recalcfromETA || p->Status.size<AIRSTRUCSIZE)
		{	//Convoys. Faketo is effectively a boolean, but now the convoys only travel a few miles in 1 hour, anyway!
			int	ptetadelta=0;
			if (attackmethod==AM_PATROL)
				ptetadelta=30*SECSPERMIN;
			info_grndgrpPtr g=*p;
			Coords3D startpos=p->World;
			int	starttime=MMC.currtime;
			info_waypointPtr w=Persons2::ConvertPtrUID(g->wpref);
			if (!w && p->Status.size==AIRSTRUCSIZE)
			{
				int p,s;
				if (Todays_Packages.GetACSquadEntry(packagetarget[0],p,s))
				{
					w=Persons2::ConvertPtrUID(Todays_Packages[p].route);
					starttime=Todays_Packages[p][s].takeofftime;
				}

			}
			int	sqnum=-10,trgnum=-10;
			if (w)
			{
				if (w->World.Y==0x80000000)
					w->position.EvalW(w->World);
				ULong d;
				UWord hw;
				Math_Lib.InterceptHdg(startpos.X,startpos.Z,w->World.X,w->World.Z,d,hw);
				if (faketo)
					forever
					{
						int	eta=w->etas.Evaluate();
						if ((eta)==ENABLE_COMPLEX_VAL)
						{
							int	vel=w->vel.Evaluate();
		//TEMPCODE RDH 03/03/00 					if (vel==ENABLE_COMPLEX_VAL)
								vel=g->GetCruiseAt(startpos);
							eta=starttime+d/vel;
						}
					breakif (eta>primarytargetETA+ptetadelta);
						starttime=eta;
						startpos=w->World;
						info_waypointPtr w2=w;
						w=Persons2::ConvertPtrUID(w->NextWP(sqnum,trgnum));
						if (w)
						{
							if (w->World.Y==0x80000000)
								w->position.EvalW(w->World);
							Math_Lib.InterceptHdg(startpos.X,startpos.Z,w->World.X,w->World.Z,d,hw);
					breakif (w2->uid== -faketo);	   //never happens for convoys
						}
						else
						{
//DeadCode JIM 13Oct00 							w=w2;	//
							break;
						}

					}

				if (w==NULL && faketo && p->Status.size>=AIRSTRUCSIZE)
				{	//gone past fake point and expected to find it. Go back to start condition


					
					startpos=g->World;
					starttime=MMC.currtime;
					w=Persons2::ConvertPtrUID(g->wpref);
					if (w)
					{
						Math_Lib.InterceptHdg(startpos.X,startpos.Z,w->World.X,w->World.Z,d,hw);
					}
				}
				Angles h=Angles(hw);
				int	time=primarytargetETA+ptetadelta-starttime;
				if (w==NULL || time<0)
					time=0;
				Float sh,ch;
				Math_Lib.high_sin_cos(h,sh,ch);
				int cruisevel=g->GetCruiseAt(startpos);
				int	dist=cruisevel*time;
				if (dist>METRES200KM)
					dist=METRES200KM;
/*CSB*/			if((p->Status.size >= AIRSTRUCSIZE) && (dist > d))
/*CSB*/				dist = d;
				Coords3D	estloc=startpos;							//JIM 13Oct00
				estloc.X+=dist*sh;
				estloc.Z+=dist*ch;
				//now need to find est point waypoint
				UniqueID wu=route;
				info_waypointPtr wp=NULL; 
				while (wu)
				{
					wp=Persons2::ConvertPtrUID(wu);
					breakif(wp->uid.Evaluate()==-SGR_WPP_EstPoint);
					wu=wp->nextwp;
				}
				assert(wu && wp && wp->uid.Evaluate()==-SGR_WPP_EstPoint)
				sh=Math_Lib.DistanceSquared(estloc.X-wp->World.X,estloc.Z-wp->World.Z);
				wp->World.X=estloc.X;
				wp->World.Z=estloc.Z;
				wp->etas=primarytargetETA;
				wp->position.MakeAbsWorldPos();
				wp->position.RecalcDeltasToMatch(estloc);
				return true;	//(sh>METRES100*METRES100);
			}
			else
				return false;
		}
		else
		{	//it is an aircraft we are intercepting
			
			int	sqnum=-10,trgnum=-10;
			info_grndgrpPtr g=*p;
			UniqueID wu=g->wpref;
			int	starttime=MMC.currtime;
			{int p,s;
			if (Todays_Packages.GetACSquadEntry(packagetarget[0],p,s))
			{
				sqnum=s;
				trgnum=Todays_Packages[p][s].targetindex;
				if (!wu)
					wu=(Todays_Packages[p].route);
				if (Todays_Packages[p][s].takeofftime>starttime)
					starttime=Todays_Packages[p][s].takeofftime;
				
			}}
			UniqueID buwu=wu;
			info_waypointPtr w=Persons2::ConvertPtrUID(wu);
			int bustarttime=starttime;
			if (w)
			{
				int	intercepttime;
				Coords3D startpos=p->World;

				if (faketo)
				{
					int	starttime=MMC.currtime;
					ULong d;
					UWord hw;
					Math_Lib.InterceptHdg(startpos.X,startpos.Z,w->World.X,w->World.Z,d,hw);
					int localstarttime=starttime;
					while(wu)
					{
						info_waypointPtr w2=Persons2::ConvertPtrUID(wu);
						int	eta=w2->etas.Evaluate();
						if ((eta)==ENABLE_COMPLEX_VAL)
						{
							int	vel=w2->vel.Evaluate();
		//TEMPCODE RDH 03/03/00 					if (vel==ENABLE_COMPLEX_VAL)
								vel=g->GetCruiseAt(startpos);
							eta=localstarttime+d/vel;
						}
						localstarttime=eta;
						
						wu=w2->NextWP(sqnum,trgnum);
						if (w2->uid.Evaluate()==-faketo)
						{
							startpos=w2->World;
							w=Persons2::ConvertPtrUID(wu);
							Math_Lib.InterceptHdg(startpos.X,startpos.Z,w->World.X,w->World.Z,d,hw);
							starttime=localstarttime;
							break;
						}
						Math_Lib.InterceptHdg(startpos.X,startpos.Z,w2->World.X,w2->World.Z,d,hw);
					}
					if (!wu)	//Cludge number 38: If already past the faketo then need to triangulate!
						faketo=SGR_Pack_BlankZero;
				//Cludge number 37 (but who is counting?):
				//If we are using faketo to generate to intercept 
				//then we should offer the position and ETA of the fake as a first guess
				//
				//
				//
				//
					intercepttime=starttime;
				}
				if (!faketo)
				{	
					wu=buwu;
					w=Persons2::ConvertPtrUID(wu);
					starttime=bustarttime;
					startpos=p->World;

					ULong d;
					UWord hw;
					Math_Lib.InterceptHdg(startpos.X,startpos.Z,w->World.X,w->World.Z,d,hw);

					//Ok.. so target is going from startpos to w, starting at time starttime
					//Interceptor will set off at approx time starttime at approx same speed
					//Resulting triangle defines intercept point
					ANGLES targetheading=Angles(hw);
					int	targetvel=g->GetCruiseAt(startpos);
					//need to use position of lead interceptor squad to determine interceptor's position
					Coords3D		interceptorstartpos;
					info_airgrpPtr	interceptoritem=Persons2::ConvertPtrUID(squadlist[0].instance);
					if (packagestatus>Profile::PS_ACTIVE_MIN)
						interceptorstartpos=interceptoritem->World;
					else
						interceptorstartpos=Persons2::ConvertPtrUID(squadlist[0].Squadron().homeairfield).World;
					ANGLES directheading,directpitch;
					SLong interceptorrange;
					
					Math_Lib.HighIntercept(startpos.X-interceptorstartpos.X,startpos.Y-interceptorstartpos.Y,startpos.Z-interceptorstartpos.Z,interceptorrange,directheading,directpitch);
					directpitch=directpitch+directpitch;	//meeting half-way
					int	interceptorvel=interceptoritem->GetCruiseAt(interceptorstartpos,directpitch);
					ANGLES headingdiff=targetheading-directheading;
					//ok.. get 'half' length	//it would be half if interceptor's climbvel = target's cruise vel
					//Mul by cos of angle
					Float	s,c;
					Math_Lib.high_sin_cos(headingdiff,s,c);
					interceptorrange*=c*targetvel/(Float(targetvel)+interceptorvel);
					if(interceptorrange<0)
						interceptorrange=-interceptorrange;
					//Apply that up route selected 
					Float ratio=Float(interceptorrange)/d;
					startpos.X+=(w->World.X-startpos.X)*ratio;
					startpos.Z+=(w->World.Z-startpos.Z)*ratio;
					intercepttime=starttime+interceptorrange/targetvel;
				}
				UniqueID wu=route;
				info_waypointPtr wp=NULL; 
				while (wu)
				{
					wp=Persons2::ConvertPtrUID(wu);
					breakif(wp->uid.Evaluate()==-SGR_WPP_EstPoint);
					wu=wp->nextwp;
				}
				assert(wu && wp && wp->uid.Evaluate()==-SGR_WPP_EstPoint);
				Float sh=Math_Lib.DistanceSquared(startpos.X-wp->World.X,startpos.Z-wp->World.Z);
				wp->World.X=startpos.X;
				wp->World.Y=startpos.Y;
				wp->World.Z=startpos.Z;
				wp->position.MakeAbsWorldPos();
				wp->position.RecalcDeltasToMatch(startpos);
				primarytargetETA=intercepttime;
				wp->etas=intercepttime;
				return true;//(sh>METRES200*METRES200);
			}
			else
				return false;

		}

	else
		return false;

}

void	Profile::RepositionSubWaypoints(UniqueID wpuid)
{
	while (wpuid)
	{
		info_waypoint* w=*Persons2::ConvertPtrUID(wpuid);
		if (w->uid==GOT_UNDEFINED_VAL || w->uid<-SGR_WPP_Landing)
		{
			w->World.X=w->World.Y=w->World.Z=0;
			w->position.EvalW(w->World);
			if (w->target.Evaluate()!=GOT_UNDEFINED_VAL && w->target.Evaluate()!=UID_NULL)
			{
				COORDS3D& base=
					Persons2::ConvertPtrUID(UniqueID(w->target.Evaluate()))->World;
				w->World.X+=base.X;
				w->World.Y+=base.Y;
				w->World.Z+=base.Z;
			}
		}
		wpuid=w->nextwp;
	}
}
Float Profile::RelDensity(SLong alt)
{
	Float reldensity;
	reldensity = 1 - 8.9117e-7* alt + 2.2625e-13 * alt * alt;

	return(reldensity);
}

//////////////////////////////////////////////////////////////////////
//
// Function:    CalcFuel
// Date:		24/07/00
// Author:		JIM
//
//Description: Returns fuel used by leg,
//				Also modifies last.Y to represent alt at that point.
//////////////////////////////////////////////////////////////////////
int Profile::CalcFuel(struct COORDS3D * last,const struct COORDS3D * wp,int leadtype,int esctype, SWord StoresDrag)	//CSB 18/06/99
{
	//use the leadtype to find the time of travel (use its velocities)
	//use the escort type to find the fuel rates
	SLong horitime, climbtime;
	int newY=CalcHoriAndClimbTime(last, wp, horitime, climbtime, leadtype, esctype, StoresDrag);					//CSB 18/06/99
	int lastY = last->Y;
	int wpY= wp->Y;

	last->Y=newY;														//JIM 24Jul00
//DEADCODE  21/02/00  	if (leadtype != esctype)
//DEADCODE  21/02/00  	{
//DEADCODE  21/02/00  		if (lastY != 0)
//DEADCODE  21/02/00  			lastY =  MMC.Sky.ContrailBandCentre - MMC.Sky.ContrailBandWidth/2 - FT_1000;
//DEADCODE  21/02/00  		if (wpY != 0)
//DEADCODE  21/02/00  			wpY =  MMC.Sky.ContrailBandCentre - MMC.Sky.ContrailBandWidth/2 - FT_1000;
//DEADCODE  21/02/00  	}

	SLong deltaY = wpY - lastY;

	Float FuelUsageRate;
//DEADCODE  21/02/00 	Float reldensity;
	FuelUsageRate = 0.75*1.3;		//1.3*0.75		1.3 fudge factor, 0.75 is throttle setting for cruise
	
	int type=(esctype);
	ClassPtr actype;
	actype = Plane_Type_Translate[type][0];

	SLong alt = lastY;
	if (deltaY > 10000)
		//climb first for fuel economy
		alt = wpY;
//DEADCODE  21/02/00 	reldensity = RelDensity(alt);
	Float usage = FuelUsageRate * horitime * actype->fuelaboff;// * reldensity	;//s * cg/cs
	usage = usage * 100;	//cg

	if (deltaY > 10000)
		  FuelUsageRate = 0.9;
	else if (deltaY < -10000)
		  FuelUsageRate = 0.1;
	else
		FuelUsageRate = 0.75; 

	if(actype->version == 2)
		FuelUsageRate *= 0.65;
//DEADCODE  21/02/00 	reldensity = RelDensity((wpY+lastY)/2);
 	Float climbusage = FuelUsageRate * climbtime * actype->fuelaboff;// * reldensity;//s * cg/cs
	climbusage = climbusage* 100;	//cg


	return	(usage + climbusage);

}
int Profile::CalcHoriAndClimbTime(const struct COORDS3D * last,const struct COORDS3D * wp,SLong& horitime,SLong& climbtime,int type, int esctype, SWord StoresDrag)	//CSB 18/06/99
{//return time in secs
	//workout the horizontal distance
	//split into horidist and climbdist
	//use horivel and climb vel to work out time
	int lastY = last->Y;
	int wpY= wp->Y;


//DEADCODE  21/02/00  	if (type != esctype)
//DEADCODE  21/02/00  	{
//DEADCODE  21/02/00  		if (lastY != 0)
//DEADCODE  21/02/00  			lastY =  MMC.Sky.ContrailBandCentre - MMC.Sky.ContrailBandWidth/2 - FT_1000;
//DEADCODE  21/02/00  		if (wpY != 0)
//DEADCODE  21/02/00  			wpY =  MMC.Sky.ContrailBandCentre - MMC.Sky.ContrailBandWidth/2 - FT_1000;
//DEADCODE  21/02/00  	}

	SLong x = wp->X - last->X;
	SLong y = wpY - lastY;
	SLong z = wp->Z - last->Z;
	SLong dist = Math_Lib.Distance2d(x,z);
//bestclimbpitch
	type=(type);
	ClassPtr actype;
	actype = Plane_Type_Translate[type][0];

	UWord p = (UWord) (actype->bestclimbpitch.a);
	
	p *= (9000 - StoresDrag) / 9000;
	p -= StoresDrag / 10;

	Float pitch = ((Float)p);
	pitch = 0.9 * pitch * (1.0 - 0.5 * (Float(lastY) + Float(wpY)) / Float(actype->abs_ceiling));	//CSB 28Jun00
	pitch = pitch / 10430.37835047;
	Float sinpitch = FSin (pitch);
	Float cospitch = FCos (pitch);
	Float climbdist = y / sinpitch;
	Float  hclimbdist;
	Float  horidist;

	if (climbdist < 0)
		climbdist = - climbdist;

	if (climbdist < dist)
	{
		hclimbdist = (climbdist *  cospitch);
		horidist = dist - hclimbdist;
	}else
	{
		climbdist = dist;
		horidist = 0;
	}
	
	//assume descent time is same as for climb
	climbtime = (100 * climbdist) / (actype->bestclimbvel);

//DeadCode CSB 16/06/99		horitime = horidist / (actype->cruisevel * 10);		//  cm and mm/cs
	
	int ResCruiseVel = actype->cruisevel;

//DEADCODE CSB 10/01/00 	if((actype->visible == F51) || (actype->visible == YAK9))
	{
		FP VelFraction = 1.0 - FP(StoresDrag) * 0.00006;
		FP fMaxVel	   = FP(ResCruiseVel) * VelFraction;
		ResCruiseVel = fMaxVel;
	}
//DEADCODE CSB 10/01/00 	else
//DEADCODE CSB 10/01/00 	{
//DEADCODE CSB 10/01/00 		SLong DeltaVel	 = (175 * StoresDrag) / 1000;
//DEADCODE CSB 10/01/00 		if(DeltaVel > 0)
//DEADCODE CSB 10/01/00 			ResCruiseVel -= DeltaVel;
//DEADCODE CSB 10/01/00 	}

//DeadCode CSB 18/06/99		ResCruiseVel -= (715 * StoresDrag) / 1000;

	SLong MaxAlt = wp->Y;
	if(last->Y > wp->Y) 
		MaxAlt = last->Y;

	if((Save_Data.flightdifficulty [FD_WINDEFFECTS]))// && (MaxAlt > 1036333))		// 34,000 ft	//CSB 28Jun00
	{
		SLong wx, wy, wz;
		MMC.Sky.GetWind(MaxAlt, wx, wy, wz);
		
		FP WindComp = 0;
		if(dist)
			WindComp = ((FP)x * (FP)wx + (FP)z * (FP)wz) / (FP)dist;
		ResCruiseVel += WindComp;
	}


	horitime = (100 * horidist) / (ResCruiseVel);		

	if(last->Y == 0)													//CSB 5Jul00
		climbtime += 120;												//CSB 5Jul00

	int retval = wp->Y;													//CSB 19Jul00
	if((climbdist == dist) && (wp->Y > last->Y))						//CSB 19Jul00
		retval = last->Y + dist * sinpitch;								//CSB 19Jul00
	if(retval < FT_5000) retval = FT_5000;								//CSB 19Jul00
	return(retval);	//Maximum attainable height at waypoint				//CSB 19Jul00
}


int Profile::ValidateTime(CString* buffer, int packnum, int wavenum)
{
	
	int time = 0;
//DEADCODE DAW 29/01/00 		if  (	(buffer->GetLength() > 0 )
//DEADCODE DAW 29/01/00 			&&				(buffer->GetLength() < 6 )			)
//DEADCODE DAW 29/01/00 		{
//DEADCODE DAW 29/01/00 			char	buff[5];
//DEADCODE DAW 29/01/00 			strcpy(buff,*buffer);
//DEADCODE DAW 29/01/00 			char*	hr = buff;
//DEADCODE DAW 29/01/00 			char*	cnt = hr;
//DEADCODE DAW 29/01/00 			char*	min;
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 			while ( (*cnt >= 48) && (*cnt <= 57))
//DEADCODE DAW 29/01/00 				*cnt++;
//DEADCODE DAW 29/01/00 			*cnt++ = 0;
//DEADCODE DAW 29/01/00 			min = cnt;
//DEADCODE DAW 29/01/00 			while ( (*cnt >= 48) && (*cnt <= 57))
//DEADCODE DAW 29/01/00 				*cnt++;
//DEADCODE DAW 29/01/00 			*cnt++ = 0;
//DEADCODE DAW 29/01/00 			time = atoi(min) + 60 * atoi(hr);
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 			int currtime;
//DEADCODE DAW 29/01/00 			if (MMC.debrief.currperiod == 0)
//DEADCODE DAW 29/01/00 				currtime = MORNINGPERIODSTART/60;
//DEADCODE DAW 29/01/00 			if (MMC.debrief.currperiod == 1)
//DEADCODE DAW 29/01/00 				currtime = MIDDAYPERIODSTART/60;
//DEADCODE DAW 29/01/00 			if (MMC.debrief.currperiod == 2)
//DEADCODE DAW 29/01/00 				currtime = AFTERNOONPERIODSTART/60;
//DEADCODE DAW 29/01/00 			if (time < currtime)
//DEADCODE DAW 29/01/00 				time = currtime;
//DEADCODE DAW 29/01/00 			if (time > (currtime + (HR02 + MIN30+ MIN5)/60))
//DEADCODE DAW 29/01/00 				 time = (currtime + (HR02 + MIN30+ MIN5)/60);
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 		}
		return(time);

}
//////////////////////////////////////////////////////////////////////
//
// Function:    CalcTime
// Date:		24/07/00
// Author:		JIM
//
//Description: 	This routine can modify the input field last.Y 
//				to indicate the actual altitude of the aircraft going through the waypoint
//////////////////////////////////////////////////////////////////////
int Profile::CalcTime(struct COORDS3D * last,const struct COORDS3D * wp,int type, int esctype, SWord StoresDrag)	//CSB 18/06/99	

{
	//if not patrol then add 5 minutes around target
	//patrol is handled retrospectively when fuel at end is known 
	SLong horitime, climbtime;
	int newY= CalcHoriAndClimbTime(last, wp, horitime, climbtime, type, esctype, StoresDrag);					//CSB 18/06/99	
	last->Y=newY;

	int time = horitime+climbtime;
	return	(time);
//	return	(1800);

}


//////////////////////////////////////////////////////////////////////
//
// Function:    AcAvailable
// Date:		15/10/00
// Author:		JIM
//
//Description: ONLY USED FOR GERMANS.
//
//
//
//What I need this routine to do:
//	If bomber,	mingrupp = 30 (equated)
//	If fighter,	mingrupp = 36
//	If input value is <3 staffel convert to a/c
//	
//	For each gruppe
//		If	gruppe is interesting type
//		And	gruppe is not busy	
//		And	reconn matches
//			If gruppe has < mingrupp a/c
//			{
//				If stafftotal==0
//					If gruppe has more than currbestac
//							currbestac=gruppe
//			}
//			else
//				add 3 to stafftotal
//	If stafftotal is zero
//		set to currbestac/10
//////////////////////////////////////////////////////////////////////
bool PackageList::AcAvailable(AMType* amtype,int actype, int actype2,int& acnum, int& squadnum, bool includecommitted)
{
	//this function is used for two purposes!
	//in one we just want the free aircraft available
	//in another we want the free plus those already committed to the package
	int	mingruppeac=Gruppen::MIN_GRUPPEAC;// = 30,MIN_GRUPPEFIGHTERS	
	if (actype2==FIGHTER)
		mingruppeac=Gruppen::MIN_GRUPPEFIGHTERS;
	if (includecommitted && (amtype->acnum>0 || amtype->squadnum!=0))
	{
//DeadCode JIM 15Oct00 		acnum = 0;//amtype->acnum;
//DeadCode JIM 15Oct00 		squadnum = amtype->squadnum;
		if (amtype->squadnum<3)
		{
			if ((acnum=Node_Data[SquadNum(amtype->squadtype)].acavail)>=mingruppeac)
			{
				squadnum=3;
				acnum=0;
			}
			else
				squadnum=0;
		}
		else
		{	acnum=0;squadnum=amtype->squadnum;	}

	}
	else
	{
		acnum = 0;
		squadnum = 0;
	}
	int sqcommitted = squadnum+(acnum/10);

	int j = 0;
	ULong acbits=0;
	if (actype2==FIGHTER)
		if (actype==MIXED)
			acbits=(1<<PT_ME109)|(1<<PT_ME110);
		else
			acbits=(1<<actype);
	else
		if (actype==MIXED)
			acbits=(1<<PT_HE111)|(1<<PT_DO17)|(1<<PT_JU88);
		else
			acbits=(1<<actype)|(1<<actype2);

	bool wantreconn=(Todays_Packages.taskdata.attackmethod == Profile::AM_RECON ) && (actype2!=FIGHTER);
	while (Node_Data.gruppe[j].squadron != SQ_ZERO)
	{
		Gruppen* g  = Node_Data[Node_Data.gruppe[j].squadron];

		if  (	((1<<g->AcType())&acbits)
 			&&	(!g->Busy())
			&&	( wantreconn == Node_Data.geschwader[g->wadernum].reconn)
			)
		{
			//if reconn only allow up ot 3 aircraft
			int numingruppe=g->acavail;
			if (numingruppe>=mingruppeac)
				squadnum+=3;
			else
				if (numingruppe>acnum)
					acnum=numingruppe;
		}
		j++;
	}
	if (squadnum)
		acnum=-1;
	else
		if (acnum*3>=mingruppeac)
		{
			squadnum=acnum*3/mingruppeac;
			acnum=-1;
		}
	if (wantreconn)
		if (squadnum || acnum>3)
		{
			squadnum=0;
			acnum=3;
		}

	bool avail = false;
	//compare free aircraft found with required calculated in this routine
	if (amtype->acnum >0)
	{
		if ((acnum > amtype->acnum) ||  (squadnum > 0))
			avail = true;
	}else 
		if (squadnum >= amtype->squadnum)
			avail = true;

	if (acnum == -1)					//RDH 12/05/00
	{	//sqcommitted are squadrons committed to this mission
	 	int maxsq = - sqcommitted + Todays_Packages.SquadronsPlanned(NAT_LUF);
		maxsq = Profile::MAXLWPLANNEDSTAFFELN - maxsq;
		if (squadnum > maxsq)
			squadnum = maxsq;
	}

	return avail;
}
void	PackageList::SetTaskData()
{
	CheckHilightValid();
 	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
	Todays_Packages.taskdata.targetnum = 0;
	while (pk.packagetarget[Todays_Packages.taskdata.targetnum].currentid)
		Todays_Packages.taskdata.targetnum++;

	Todays_Packages.taskdata.strike.acnum = 0;
	Todays_Packages.taskdata.returned.acnum = 0;
	Todays_Packages.taskdata.attached.acnum = 0;
	Todays_Packages.taskdata.detached.acnum = 0;
	Todays_Packages.taskdata.strike.realacnum = 0;
	Todays_Packages.taskdata.returned.realacnum = 0;
	Todays_Packages.taskdata.attached.realacnum = 0;
	Todays_Packages.taskdata.detached.realacnum = 0;
	Todays_Packages.taskdata.strike.squadnum = 0;
	Todays_Packages.taskdata.returned.squadnum = 0;
	Todays_Packages.taskdata.attached.squadnum = 0;
	Todays_Packages.taskdata.detached.squadnum = 0;

	 Todays_Packages.taskdata.attackmethod = pk.attackmethod;

	for (int j = 0; j < STRIKEOPTIONS;j++)
	   Todays_Packages.taskdata.strikeactypes[j] = NOTDEFINED;
	for (j = 0; j < ESCORTOPTIONS;j++)
	   Todays_Packages.taskdata.escortactypes[j] = NOTDEFINED;
	int i=0, gruppe, actype;
	while ( i <  MAX_METHODS)
	{
		Todays_Packages.taskdata.returned.attackmethods[i] = false;
		Todays_Packages.taskdata.attached.attackmethods[i] = false;
		Todays_Packages.taskdata.detached.attackmethods[i] = false;
		i++;
	}

	i = 0;
	while (i < pk.squadlist)
	{
		if (pk[i].method == pk.attackmethod)
		{
				Todays_Packages.taskdata.strike.realacnum +=  pk[i].numacoriginal;
				Todays_Packages.taskdata.strike.squadtype=pk[i].squadnum;
				if (	(Todays_Packages.taskdata.strike.acnum != -1))
				{

					if (pk[i].numacoriginal >= 10)
					{
						Todays_Packages.taskdata.strike.acnum = -1;
						Todays_Packages.taskdata.strike.squadnum++;
					}else if (Todays_Packages.taskdata.strike.acnum)
					{
						Todays_Packages.taskdata.strike.acnum = -1;
						Todays_Packages.taskdata.strike.squadnum += 2;
					}else
						Todays_Packages.taskdata.strike.acnum = pk[i].numacoriginal;
				}else
					Todays_Packages.taskdata.strike.squadnum++;
				gruppe = pk[i].squadnum;
				actype = Node_Data[(SquadNum)gruppe].AcType();
				if (Todays_Packages.taskdata.mixedstrikeset)
				{
					Todays_Packages.taskdata.strikeactypes[0] = MIXED;
				}else
				{
					if 	(	(Todays_Packages.taskdata.strikeactypes[0] == NOTDEFINED)
							||	(Todays_Packages.taskdata.strikeactypes[0] == actype)
						)
						Todays_Packages.taskdata.strikeactypes[0] = Node_Data[(SquadNum)gruppe].AcType();
					else
						Todays_Packages.taskdata.strikeactypes[0] = MIXED;
				}
		}
		if (pk[i].method >= Profile::AM_RETURNESCORT)
		{
				if (!Todays_Packages.taskdata.returned.acnum)
						Todays_Packages.taskdata.returned.formtype = pk[i].formtype;

				Todays_Packages.taskdata.returned.realacnum +=  pk[i].numacoriginal;
					Todays_Packages.taskdata.returned.squadtype=pk[i].squadnum;
				if ((Todays_Packages.taskdata.returned.acnum != -1))
				{
					if (pk[i].numacoriginal >= 10)
					{
						Todays_Packages.taskdata.returned.acnum = -1;
						Todays_Packages.taskdata.returned.squadnum++;
					}else if (Todays_Packages.taskdata.returned.acnum)
					{
						Todays_Packages.taskdata.returned.acnum = -1;
						Todays_Packages.taskdata.returned.squadnum += 2;
					}else
						Todays_Packages.taskdata.returned.acnum = pk[i].numacoriginal;
				}else
					Todays_Packages.taskdata.returned.squadnum++;
				gruppe = pk[i].squadnum;
				actype = Node_Data[(SquadNum)gruppe].AcType();
				if (Todays_Packages.taskdata.mixedescortset)
				{
					Todays_Packages.taskdata.escortactypes[0] = MIXED;
				}else
				{
					if 	(	(Todays_Packages.taskdata.escortactypes[0] == NOTDEFINED)
							||	(Todays_Packages.taskdata.escortactypes[0] == actype)
						)
						Todays_Packages.taskdata.escortactypes[0] = actype;
					else
						Todays_Packages.taskdata.escortactypes[0] = MIXED;
				}
				if ((pk[i].method - Profile::AM_RETURNESCORT)	 < MAX_METHODS)
					Todays_Packages.taskdata.returned.attackmethods[pk[i].method - Profile::AM_RETURNESCORT] = true;
				//attachedgruppe  = pk[i].squadnum;
		}
		else if (pk[i].method >= Profile::AM_ATTACHED)
		{

				if (!Todays_Packages.taskdata.attached.acnum)
						Todays_Packages.taskdata.attached.formtype = pk[i].formtype;
				Todays_Packages.taskdata.attached.realacnum +=  pk[i].numacoriginal;
				Todays_Packages.taskdata.attached.squadtype=pk[i].squadnum;
				if ( (Todays_Packages.taskdata.attached.acnum != -1))
				{
					if (pk[i].numacoriginal >= 10)
					{
						Todays_Packages.taskdata.attached.acnum = -1;
						Todays_Packages.taskdata.attached.squadnum++;
					}else if (Todays_Packages.taskdata.attached.acnum)
					{
						Todays_Packages.taskdata.attached.acnum = -1;
						Todays_Packages.taskdata.attached.squadnum += 2;
					}else
						Todays_Packages.taskdata.attached.acnum = pk[i].numacoriginal;
				}else
					Todays_Packages.taskdata.attached.squadnum++;
 				gruppe = pk[i].squadnum;
				actype = Node_Data[(SquadNum)gruppe].AcType();
				if (Todays_Packages.taskdata.mixedescortset)
				{
					Todays_Packages.taskdata.escortactypes[0] = MIXED;
				}else
				{
					if 	(	(Todays_Packages.taskdata.escortactypes[0] == NOTDEFINED)
							||	(Todays_Packages.taskdata.escortactypes[0] == actype)
						)
						Todays_Packages.taskdata.escortactypes[0] = actype;
					else
						Todays_Packages.taskdata.escortactypes[0] = MIXED;
				}

				
				if ((pk[i].method - Profile::AM_ATTACHED)	 < MAX_METHODS)
					Todays_Packages.taskdata.attached.attackmethods[pk[i].method - Profile::AM_ATTACHED] = true;
				//attachedgruppe  = pk[i].squadnum;
		}
		else if (pk[i].method >= Profile::AM_DETACHED)
		{
				if (!Todays_Packages.taskdata.detached.acnum)
						Todays_Packages.taskdata.detached.formtype = pk[i].formtype;
				Todays_Packages.taskdata.detached.realacnum +=  pk[i].numacoriginal;
				Todays_Packages.taskdata.detached.squadtype=pk[i].squadnum;
				if ( (Todays_Packages.taskdata.detached.acnum != -1))
				{
					if (pk[i].numacoriginal >= 10)
					{
						Todays_Packages.taskdata.detached.acnum = -1;
						Todays_Packages.taskdata.detached.squadnum++;
					}else if (Todays_Packages.taskdata.detached.acnum)
					{
						Todays_Packages.taskdata.detached.acnum = -1;
						Todays_Packages.taskdata.detached.squadnum += 2;
					}else
						Todays_Packages.taskdata.detached.acnum = pk[i].numacoriginal;
				}else
					Todays_Packages.taskdata.detached.squadnum++;

								gruppe = pk[i].squadnum;
					actype = Node_Data[(SquadNum)gruppe].AcType();
				if (Todays_Packages.taskdata.mixedescortset)
				{
					Todays_Packages.taskdata.escortactypes[0] = MIXED;
				}else
				{

						if 	(	(Todays_Packages.taskdata.escortactypes[0] == NOTDEFINED)
								||	(Todays_Packages.taskdata.escortactypes[0] == actype)
							)
							Todays_Packages.taskdata.escortactypes[0] = actype;
						else
							Todays_Packages.taskdata.escortactypes[0] = MIXED;
				}

				if ((pk[i].method - Profile::AM_DETACHED)	 < MAX_METHODS)
					Todays_Packages.taskdata.detached.attackmethods[pk[i].method - Profile::AM_DETACHED] = true;
			
		}
		i++;
	}


	i = 1;
	int acnum, squadnum;
	if (Todays_Packages.taskdata.strikeactypes[0] != MIXED)
		if (Todays_Packages.taskdata.strikeactypes[0]>=PT_GER_NONFLY)
		{
			if (AcAvailable(&Todays_Packages.taskdata.strike, MIXED, NOTDEFINED,acnum, squadnum, true))
				Todays_Packages.taskdata.strikeactypes[i++] = MIXED;
		}
		else
		{
			if(AcAvailable(&Todays_Packages.taskdata.strike, MIXED, NOTDEFINED,acnum, squadnum, false))
				Todays_Packages.taskdata.strikeactypes[i++] = MIXED;
		}		

	if (	(Todays_Packages.taskdata.strikeactypes[0] != PT_DO17)
		&&	(AcAvailable(&Todays_Packages.taskdata.strike, PT_DO17, PT_DO17,acnum, squadnum, false))
		)
		Todays_Packages.taskdata.strikeactypes[i++]	= PT_DO17;

	if (	(Todays_Packages.taskdata.strikeactypes[0] != PT_HE111)
		&&	(AcAvailable(&Todays_Packages.taskdata.strike, PT_HE111, PT_HE111, acnum, squadnum, false))
		)
		Todays_Packages.taskdata.strikeactypes[i++]	= PT_HE111;

	if (	(Todays_Packages.taskdata.strikeactypes[0] != PT_JU87)
		&&	(AcAvailable(&Todays_Packages.taskdata.strike, PT_JU87, PT_JU87, acnum, squadnum, false))
		)
		Todays_Packages.taskdata.strikeactypes[i++]	= PT_JU87;

	if (	(Todays_Packages.taskdata.strikeactypes[0] != PT_JU88)
		&&	(AcAvailable(&Todays_Packages.taskdata.strike, PT_JU88,PT_JU88, acnum, squadnum, false))
		)
		Todays_Packages.taskdata.strikeactypes[i++]	= PT_JU88;

	if (	(Todays_Packages.taskdata.strikeactypes[0] != PT_ME110)
		&&	(AcAvailable(&Todays_Packages.taskdata.strike, PT_ME110, PT_ME110,acnum, squadnum, false))
		)
		Todays_Packages.taskdata.strikeactypes[i++]	= PT_ME110;
//escort options
	AcAvailable(&Todays_Packages.taskdata.strike, Todays_Packages.taskdata.strikeactypes[0], 
				Todays_Packages.taskdata.strikeactypes[0], acnum, squadnum, true); 

	Todays_Packages.taskdata.strike.maxac = acnum;
	Todays_Packages.taskdata.strike.maxsquad = squadnum;
//DEADCODE DAW 07/04/00 	if (		(AcAvailable(&Todays_Packages.taskdata.strike, PT_ME109, PT_ME109,acnum, squadnum, false))
//DEADCODE DAW 07/04/00 			&&	(Todays_Packages.taskdata.escortactypes[0] != PT_ME109)
//DEADCODE DAW 07/04/00 		)
//DEADCODE DAW 07/04/00 		Todays_Packages.taskdata.escortactypes[i++]	= PT_ME109;
//DEADCODE DAW 07/04/00 
//DEADCODE DAW 07/04/00 	if (		(AcAvailable(&Todays_Packages.taskdata.strike, PT_ME110, PT_ME110,acnum, squadnum, false))
//DEADCODE DAW 07/04/00 			&&	(Todays_Packages.taskdata.escortactypes[0] != PT_ME110)
//DEADCODE DAW 07/04/00 		)
//DEADCODE DAW 07/04/00 		Todays_Packages.taskdata.escortactypes[i++]	= PT_ME110;
//DEADCODE DAW 07/04/00 



//DEADCODE RDH 07/04/00 //using these attached fields for general purpose 
//DEADCODE RDH 07/04/00 	int escorttype = Todays_Packages.taskdata.escortactypes[0];
//DEADCODE RDH 07/04/00 	if (escorttype == -1)
//DEADCODE RDH 07/04/00 			escorttype = PT_ME109;

	//work out the total fighter figures
	int fighters = 0;
	int fightersquads = 0;
		
	if (Todays_Packages.taskdata.returned.acnum <= 0)
	{
		fightersquads +=Todays_Packages.taskdata.returned.squadnum;
	}else
		fighters +=Todays_Packages.taskdata.returned.acnum;

	if (Todays_Packages.taskdata.attached.acnum <= 0)
		fightersquads +=Todays_Packages.taskdata.attached.squadnum;
	else
		if (fightersquads || fighters)
			fightersquads++;
		else
			fighters=Todays_Packages.taskdata.attached.acnum;

	if (Todays_Packages.taskdata.detached.acnum <= 0)
		fightersquads +=Todays_Packages.taskdata.detached.squadnum;
	else
		if (fightersquads || fighters)
			fightersquads++;
		else
			fighters +=Todays_Packages.taskdata.detached.acnum;
	if (fighters && fightersquads)
		fightersquads++;
	if (fightersquads)
		fighters = -1;

	Todays_Packages.taskdata.totalfighter.squadnum = fightersquads;
	Todays_Packages.taskdata.totalfighter.acnum = fighters;
	Todays_Packages.taskdata.totalfighter.realacnum = 
		Todays_Packages.taskdata.returned.realacnum +
		Todays_Packages.taskdata.attached.realacnum +
		Todays_Packages.taskdata.detached.realacnum;

	i =1;
	if (Todays_Packages.taskdata.escortactypes[0] != MIXED)
		if (fighters>0 || fightersquads>0)
			Todays_Packages.taskdata.escortactypes[i++] = MIXED;   //this mixed is mix with current fighter type and will always succeed.
		else
			Todays_Packages.taskdata.escortactypes[0]=PT_ME109;
	else
		Todays_Packages.taskdata.mixedescortset=true;
	int othertype=PT_ME109;
	if (Todays_Packages.taskdata.escortactypes[0]==othertype)
		othertype=PT_ME110;
	if (AcAvailable(&Todays_Packages.taskdata.totalfighter, othertype,	FIGHTER, acnum, squadnum, false))
		Todays_Packages.taskdata.escortactypes[i++] = othertype;   //this mixed is mix with current fighter type and will always succeed.
	if (Todays_Packages.taskdata.escortactypes[0] == MIXED)
		if (AcAvailable(&Todays_Packages.taskdata.totalfighter, PT_ME110,	FIGHTER, acnum, squadnum, false))
			Todays_Packages.taskdata.escortactypes[i++] = PT_ME110;   //this mixed is mix with current fighter type and will always succeed.

	

//using these attached fields for general purpose 
	int escorttype = Todays_Packages.taskdata.escortactypes[0];
//DeadCode JIM 15Oct00 	int escorttype2 = Todays_Packages.taskdata.escortactypes[0];
	if ((escorttype == -1))
		escorttype=MIXED;
//DeadCode JIM 15Oct00 	{
//DeadCode JIM 15Oct00 			escorttype = PT_ME109;
//DeadCode JIM 15Oct00 			escorttype2 = PT_ME110;
//DeadCode JIM 15Oct00 	}

	AcAvailable(&Todays_Packages.taskdata.totalfighter, escorttype, 
		FIGHTER, acnum, squadnum, true);
	Todays_Packages.taskdata.attached.maxac = acnum;
	Todays_Packages.taskdata.attached.maxsquad = squadnum;



//DEADCODE RDH 02/04/00 	 Todays_Packages.taskdata.attackmethod = pk.attackmethod - Profile::AM_DIVEBOMB;
	 Todays_Packages.taskdata.attackmethod = pk.attackmethod;
		
}



bool PackageList::RAFAcAvailable(AMType* amtype,int actype, int actype2,int& acnum, int& squadnum, bool includecommitted)
{
	if (includecommitted)
	{
		acnum = amtype->acnum;
		squadnum = amtype->squadnum;
	}
	else
	{
		acnum = 0;
		squadnum = 0;
	}
	int sqcommitted = squadnum;


	int j = 0;
	while (Node_Data.squadron[j].squadron != SQ_ZERO)
	{
		Squadron* sq  = Node_Data[Node_Data.squadron[j].squadron];
		if  (	(		(actype == sq->AcType())
					||	(actype2 == sq->AcType())
					||	(actype == MIXED)
				 )
 			&&	(!sq->Busy())
			)
		{
			if (acnum == 0)
			{
				acnum = sq->acavail;
			}else
			{
				squadnum++;
				acnum = -1;
			}

		}
		j++;
	}
	bool avail = false;
//DeadCode JIM 20Oct00 	if (amtype->acnum != -1)
//DeadCode JIM 20Oct00 	{
//DeadCode JIM 20Oct00 		if ((acnum > amtype->acnum) ||  (squadnum > 0))
//DeadCode JIM 20Oct00 			avail = true;
//DeadCode JIM 20Oct00 	}else if (squadnum >= amtype->squadnum)
//DeadCode JIM 20Oct00 		avail = true;

	if (acnum == -1)					//RDH 12/05/00
	{	//sqcommitted are squadrons committed to this mission
	 	int maxsq = - sqcommitted +Todays_Packages.SquadronsPlanned(NAT_RAF);
		maxsq = Profile::MAXRAFPLANNEDSQUADRONS - maxsq;
		if (squadnum > maxsq)
			squadnum = maxsq;
	}

	return avail;
}
bool	Profile::IncreaseSubSquadronToSquadron(Profile::AttackMethod attackmethod)
{//if player wants spits and hurr in mission, they must be squadrons not flights or less
 	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];

	BetterRule	br;
	if (attackmethod == Profile::AM_DETACHED)
		br = BR_B_SPITONLY;
	else
		br = BR_B_HURRONLY;

	bool sqfound = false;
	int  i = 0, actype;

	int sqnum = 0;
	while (i < pk.squadlist)
	{
		Squadron* sq = Node_Data[(SquadNum)pk[i].squadnum];

		actype = sq->AcType();
		if(
			(
				(		(actype == PT_SPIT_A)
					||	(actype == PT_SPIT_B)
				)
				&&
				(attackmethod == AM_DETACHED)
			)
			||
			(
				(		(actype == PT_HURR_A)
					||	(actype == PT_HURR_B)
				)
				&&
				(attackmethod == AM_ATTACHED)
			)
		)
		{
			sqfound = true;
			sqnum++;
		}
		i++;
	}
	//sqnum now contains the number of squadrons of the required type
	//if number  == 1 then need to make it up to a full sq
	
	if (sqnum ==1)
	{

		i = 0;
		while (i < pk.squadlist)
		{
			Squadron* sq = Node_Data[(SquadNum)pk[i].squadnum];

			actype = sq->AcType();
			if(
				(
					(		(actype == PT_SPIT_A)
						||	(actype == PT_SPIT_B)
					)
					&&
					(attackmethod == AM_DETACHED)
				)
				||
				(
					(		(actype == PT_HURR_A)
						||	(actype == PT_HURR_B)
					)
					&&
					(attackmethod == AM_ATTACHED)
				)
			)
			{
				if (pk[i].numacoriginal < 12)
				{
 					DeleteNumerousSquadrons(br);
 					AddNumerousSquadrons(-1,(Profile::AttackMethod)this->attackmethod,SQ_ZERO,br);
				}
			}
			i++;
		}
	}
	return(sqfound);

}

void	PackageList::SetRAFTaskData()
{
//using these detached fields for spitfire
//using these attached fields for hurricane

 	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];

	Todays_Packages.taskdata.attached.acnum = 0;
	Todays_Packages.taskdata.detached.acnum = 0;
	Todays_Packages.taskdata.attached.squadnum = 0;
	Todays_Packages.taskdata.detached.squadnum = 0;

	int i=0, squadron, actype;
	while ( i <  MAX_METHODS)
	{
		Todays_Packages.taskdata.attached.attackmethods[i] = false;
		Todays_Packages.taskdata.detached.attackmethods[i] = false;
		i++;
	}

	i = 0;
	while (i < pk.squadlist)
	{
//DEADCODE RDH 10/04/00 		squadron = pk[i].squadnum;
//DEADCODE RDH 10/04/00 		actype = Node_Data.squadron[squadron].AcType();
		Squadron* sq = Node_Data[(SquadNum)pk[i].squadnum];

		actype = sq->AcType();
		if	(		(actype == PT_SPIT_A)
				||	(actype == PT_SPIT_B)
			)
		{
			if (	(Todays_Packages.taskdata.detached.acnum != -1))
			{
				if (pk[i].numacoriginal >= 12)
				{
					if (Todays_Packages.taskdata.detached.acnum > 0)
						Todays_Packages.taskdata.detached.squadnum++;

					Todays_Packages.taskdata.detached.acnum = -1;

					Todays_Packages.taskdata.detached.squadnum++;
				}else if (Todays_Packages.taskdata.detached.acnum)
				{
					Todays_Packages.taskdata.detached.acnum = -1;
					Todays_Packages.taskdata.detached.squadnum +=2;
				}else
					Todays_Packages.taskdata.detached.acnum = pk[i].numacoriginal;
			}else
				Todays_Packages.taskdata.detached.squadnum++;

		}else
		{
			if (	(Todays_Packages.taskdata.attached.acnum != -1))
			{
				if (pk[i].numacoriginal >= 12)
				{
					if (Todays_Packages.taskdata.attached.acnum > 0)
						Todays_Packages.taskdata.attached.squadnum++;
					Todays_Packages.taskdata.attached.acnum = -1;
					Todays_Packages.taskdata.attached.squadnum++;
				}else if (Todays_Packages.taskdata.attached.acnum)
				{
					Todays_Packages.taskdata.attached.acnum = -1;
					Todays_Packages.taskdata.attached.squadnum +=2;
				}else
					Todays_Packages.taskdata.attached.acnum = pk[i].numacoriginal;
			}else
				Todays_Packages.taskdata.attached.squadnum++;
		}

		i++;
	}

	int acnum, squadnum;
	RAFAcAvailable(&Todays_Packages.taskdata.detached, PT_SPIT_A, PT_SPIT_B, acnum, squadnum, true);
	Todays_Packages.taskdata.detached.maxac = acnum;
	Todays_Packages.taskdata.detached.maxsquad = squadnum;

	RAFAcAvailable(&Todays_Packages.taskdata.attached, PT_HURR_A, PT_HURR_B, acnum, squadnum, true);
	Todays_Packages.taskdata.attached.maxac = acnum;
	Todays_Packages.taskdata.attached.maxsquad = squadnum;

		
}


void	PackageList::DeletePack(int p)	  //Only called from the delete buttons!
{
	if (pack[p].route)
		InvalidateRoute(&pack[p],true,true);
	if (hipack==p)
		hipack= -1;

	pack[p].DeleteNumerousSquadrons(Profile::AM_RAF);
	pack[p].DeleteNumerousSquadrons(Profile::AM_LWPACKS);
	pack[p].DeleteNumerousSquadrons(Profile::AM_DETACHED);
	pack[p].DeleteNumerousSquadrons(Profile::AM_ATTACHED);
	pack[p].DeleteNumerousSquadrons(Profile::AM_RETURNESCORT);

	pack[p].PackageComplete();
	ClearPack(p);

}






void	PackageList::ClearPack(int p)
{
//	pack[p].packname[0]=0;
//	pack[p].packagetakeoff=	pack[p].packagetarget	=pack[p].regrouploc=UID_NULL;
	delete[] pack[p].raidnumentries;
	pack[p].raidnumentries=NULL;
//DEADCODE ROD 16/12/99 	pack[p].packname[0] = 0;
//DeadCode JIM 25Oct00 	pack[p].redo = false;
//DeadCode JIM 25Oct00 	pack[p].edited = false;
	pack[p].flags=0;
	pack[p].packagetakeoff = UID_NULL;							
	pack[p].packagetarget[0] = UID_NULL;
	pack[p].packagetarget[1] = UID_NULL;
	pack[p].packagetarget[2] = UID_NULL;
	pack[p].packagetarget[3] = UID_NULL;
	pack[p].packagetarget[4] = UID_NULL;
	pack[p].packagetarget[5] = UID_NULL;
	pack[p].packagetarget[6] = UID_NULL;
	pack[p].packagetarget[7] = UID_NULL;
	pack[p].packagetarget[8] = UID_NULL;
	pack[p].packagetarget[9] = UID_NULL;
	pack[p].doglegloc = UID_NULL;
	pack[p].packagestatus=Profile::PS_SPARE;
	pack[p].wpsused=0;
	pack[p].route=UID_NULL;												//JIM 23Aug00
	pack[p].squadlist.Free();


}

void	PackageList::WipeAll()
{
	for (int p=0;p<Profile::MAX_PACKS;p++)
		ClearPack(p);
	nextraidnum=0,nextsortienum=0;
 	oldhipack=0, hipack=0, oldhisquad=0, hisquad=0;
	hiwp=UID_NULL;
}




void Profile::CalcRangeBrgFromPrev(UniqueID wpuid, ULong& range, ULong& brg)
{

	info_waypoint* wp=*Persons2::ConvertPtrUID(wpuid);
	info_waypoint* prevwp=*Persons2::ConvertPtrUID(wp->prevwp);

	if (wp->applygroup.Evaluate()!=ENABLE_COMPLEX_VAL)
		while (prevwp && prevwp->applygroup.Evaluate()!=ENABLE_COMPLEX_VAL && prevwp->applygroup.Evaluate()!=wp->applygroup.Evaluate())
			prevwp=*Persons2::ConvertPtrUID(prevwp->prevwp);
	if (wp->applywave.Evaluate()!=ENABLE_COMPLEX_VAL)
		while (prevwp && prevwp->applywave.Evaluate()!=ENABLE_COMPLEX_VAL && prevwp->applywave.Evaluate()!=wp->applywave.Evaluate())
			prevwp=*Persons2::ConvertPtrUID(prevwp->prevwp);
	UWord sbrg;
	if (prevwp!=NULL)
		Math_Lib.InterceptHdg(prevwp->World.X, prevwp->World.Z, wp->World.X, wp->World.Z, range, sbrg);
	else
	{
		info_waypoint* nextwp=*Persons2::ConvertPtrUID(wp->nextwp);

		if (wp->applygroup.Evaluate()!=ENABLE_COMPLEX_VAL)
			while (nextwp && nextwp->applygroup.Evaluate()!=ENABLE_COMPLEX_VAL && nextwp->applygroup.Evaluate()!=wp->applygroup.Evaluate())
				nextwp=*Persons2::ConvertPtrUID(nextwp->nextwp);
		if (wp->applywave.Evaluate()!=ENABLE_COMPLEX_VAL)
			while (nextwp && nextwp->applywave.Evaluate()!=ENABLE_COMPLEX_VAL && nextwp->applywave.Evaluate()!=wp->applywave.Evaluate())
				nextwp=*Persons2::ConvertPtrUID(nextwp->nextwp);
		if (nextwp!=NULL)
			Math_Lib.InterceptHdg(wp->World.X, wp->World.Z, nextwp->World.X, nextwp->World.Z, range, sbrg);
	}
	range = range/Save_Data.dist.longcm;
	brg = sbrg *360/65536;


}

int Profile::FindEarliestPrimaryTargetETA(int& absrvtime, int& slowestsq)
{
	int i=0;
	int targettime = 0, slowestrvtoeta = 0;
	int rvtime = 0;
	int lastrvtime = 0;
	
	while (i < squadlist)
	{
		CalcWPRelTimes(i, targettime, rvtime);		//these are relative to take-off at midnight

		if (slowestrvtoeta < (targettime - rvtime))
		{
			slowestrvtoeta  = targettime - rvtime;
			slowestsq = i;
		}

		Squadron* sq = Node_Data[(SquadNum)squadlist[i].squadnum];
		int preptime=0;
		if (sq->totestatus<PS_ACTIVE_MIN)
			if (sq->squadron>SQ_LW_START)										//JIM 03/03/00
				preptime=SECSPERMIN*30;
			else
				preptime=Times_Per_Tote[sq->totestatus];

		if ((preptime + rvtime) > lastrvtime)
			lastrvtime = preptime + rvtime;

		i++;
	}

	absrvtime = MMC.currtime +  lastrvtime;
	return(MMC.currtime + lastrvtime + slowestrvtoeta );

}

int	Profile::Squad::FixTakeOffTime(int absrvtime,int rvtime)
{
		WaypointOffsetSub wos;
		AirStruc::GenWaypointOffsetSub(formtype,wos,(method&AM_GROUPMASK)==AM_ATTACHED);
		int waypointdelta=wos.deltatime/100; //+ve means arrive early	//JIM 25Jul00
		int wishtotime=	(absrvtime-rvtime) -waypointdelta ;
		//need to check all other packages for this time...
		UniqueID home=Squadron().homeairfield;
		enum	{WINDOW=5,INSIDE=2};
		int	deltatime=-INSIDE;
		for (bool retry=true;retry;deltatime+=WINDOW)
		{	//guarantee a 2 second gap, but generally will get a 5 second gap
			//At flying speed that is over 100 metres
			//At take-off speed this is as low as 10 metres
			retry=false;
			for (int p=0;p<Profile::MAX_PACKS;p++)
				for (int s=0,ms=Todays_Packages[p].squadlist;s<ms;s++)
					if (&Todays_Packages[p][s]!=this)
						if (Todays_Packages[p][s].Squadron().homeairfield==home)
							if (	Todays_Packages[p][s].takeofftime>wishtotime+deltatime
								&&  Todays_Packages[p][s].takeofftime<wishtotime+deltatime+WINDOW
								)
								retry=true;
		}
		deltatime=deltatime-WINDOW+INSIDE;

		takeofftime = wishtotime+deltatime;	//JIM 24Jul00

		UniqueID wpuid = takeoffwp;
		info_waypoint* wp=Persons2::ConvertPtrUID(wpuid);
		wp->etas = takeofftime;	//etas;				//CSB 26Jul00
		::Squadron&	sq=Squadron();
		rvtime=takeofftime;
		if (sq.totestatus<PS_ACTIVE_MIN)
			if (sq.squadron>SQ_LW_START)										//JIM 03/03/00
				rvtime-=SECSPERMIN*30;
			else
				rvtime-=Times_Per_Tote[sq.totestatus];
	return rvtime;
}

//DeadCode CSB 2Aug00 void	Profile::Squad::FixTakeOffTime(int absrvtime,int rvtime)
//DeadCode CSB 2Aug00 {
//DeadCode CSB 2Aug00 		WaypointOffsetSub wos;
//DeadCode CSB 2Aug00 		AirStruc::GenWaypointOffsetSub(formtype,wos,(method&AM_GROUPMASK)==AM_ATTACHED);
//DeadCode CSB 2Aug00 		int waypointdelta=wos.deltatime/100; //+ve means arrive early	//JIM 25Jul00
//DeadCode CSB 2Aug00 		takeofftime = absrvtime - rvtime-waypointdelta;	//JIM 24Jul00
//DeadCode CSB 2Aug00 
//DeadCode CSB 2Aug00 		UniqueID wpuid = takeoffwp;
//DeadCode CSB 2Aug00 		info_waypoint* wp=*Persons2::ConvertPtrUID(wpuid);
//DeadCode CSB 2Aug00 		wp->etas = takeofftime;	//etas;				//CSB 26Jul00
//DeadCode CSB 2Aug00 }

void Profile::CalcWPRelTimes(int sqnum, int& targettime, int& rvtime)
{
//	UniqueID wpuid = route;
//DeadCode RDH 30Jun00 	UniqueID wpuid = squadlist[sqnum].takeoffwp;
	int i=0;
	COORDS3D last,next;
	int lasttime=0;
		int dtime;

	SWord StoresDrag = 0;
	targettime = 0;

	Squadron* sq = Node_Data[(SquadNum)squadlist[sqnum].squadnum];

	UniqueID	tof,tol,ipf,ipl,ldf,ldl;
	GetKeyMainWPs(tof,tol,ipf,ipl,ldf,ldl);
	WaypointOffsetSub wos;
	AirStruc::GenWaypointOffsetSub(squadlist[sqnum].formtype,wos,(squadlist[sqnum].method&AM_GROUPMASK)==AM_ATTACHED);
	int deltawpalt=wos.deltavert;
	int targindex=squadlist[sqnum].targetindex;
	//takeoff
//DeadCode RDH 30Jun00 	info_waypoint* wp=*Persons2::ConvertPtrUID(wpuid);
//DeadCode RDH 30Jun00 	last=&wp->World;
//DeadCode RDH 30Jun00 	wp->etas = 0;

	UniqueID wpuid = squadlist[sqnum].takeoffwp;

	info_waypoint* wp=*Persons2::ConvertPtrUID(wpuid);
	wp->etas = 0;
	last=wp->World;	 //take-off
	wpuid = wp->NextWP(sqnum,targindex);
	while (wpuid)
	{
		wp=*Persons2::ConvertPtrUID(wpuid);
		if (squadlist[sqnum].method>=AM_ESCORTTYPES)
			if (wp->uid==-SGR_WPP_BombRendezvous)
			{
				wpuid = wp->NextWP(sqnum,targindex);
				wp=*Persons2::ConvertPtrUID(wpuid);
				if (squadlist[sqnum].method>=AM_RETURNESCORT)
				{
					rvtime=targettime=-1;
					while (wp->uid!=-SGR_WPP_EscDisperse)
					{
						wpuid = wp->NextWP(sqnum,targindex);
						wp=*Persons2::ConvertPtrUID(wpuid);
					}
				}
			}
			else if (squadlist[sqnum].method<AM_RETURNESCORT && wp->uid==-SGR_WPP_BombDisperse)
			{
				wpuid = wp->NextWP(sqnum,targindex);
				wp=*Persons2::ConvertPtrUID(wpuid);
			}
		int actype = sq->AcType();
		next=wp->World;
		if (wp->nextwp)
			next.Y+=deltawpalt;
		dtime=Profile::CalcTime(&last,&next,actype,actype,StoresDrag);			//CSB 18/06/99	

		wp->etas = lasttime + dtime;
		if 	(wpuid == ipf)
			targettime = wp->etas;
		if (WPType(wpuid) == IDS_WP_ESCREND)
			rvtime = wp->etas;
		lasttime = wp->etas;
		last.X = wp->World.X;
		last.Z = wp->World.Z;
		i++;
		wpuid = wp->NextWP(sqnum,targindex);
	}
}

int Profile::CalcWPAbsTimes(int absrvtime, int slowestsq)
{

	int i=0;
	int targettime = 0;
	int rvtime = 0;
//set the take-off times (and takeoff wp time except slowest (done below))
	UniqueID	tof,toarea,trguid,regroupuid,ldarea,ldl;
	GetKeyMainWPs(tof,toarea,trguid,regroupuid,ldarea,ldl);

	int maxbodywps=0;
	UniqueID ref=toarea;
	info_waypointPtr wp,ipwp,egwp,trgwp=NULL,estwp;
//			case	AM_INTERCEPT:	act=wpengagetargetno;	break;
//			case	AM_RECON:		act=wpreccyno;			break;
//			default:				act=wpbombno;			break;	
	for (wp=Persons2::ConvertPtrUID(ref);ref!=ldarea;wp=Persons2::ConvertPtrUID(ref=wp->nextwp))
	{
		if (wp->applywave==0 &&	wp->uid==-SGR_WPC_Target)
				trgwp=wp;
		else
		if (wp->uid==-SGR_WPP_EstPoint)
				estwp=wp;
		maxbodywps++;
	}
	ipwp=Persons2::ConvertPtrUID(trguid);
	egwp=Persons2::ConvertPtrUID(regroupuid);
	Coords3D	backupworldpos;
	if (trgwp)
	{
		backupworldpos=trgwp->World;		//Mind the cludge!
		trgwp->World.X=	estwp->World.X;		//If target is a mobile estimate times bombing the estimated pos
		trgwp->World.Z=	estwp->World.Z;		//Rather than the real pos.
	}

	int*	wpdeltas=new int[maxbodywps];
	int*	wpmindeltas=new int[maxbodywps];
	{for (int i=0;i<maxbodywps;i++) wpdeltas[i]=0;}
	{for (int i=0;i<maxbodywps;i++) wpmindeltas[i]=0x70000000;}
	int		trgregroupdelta=0;
	SquadNum lastsquadnum=SQ_ZERO;
	//Find target waypoint 1 and est pos waypoint
	//Temp make the target be at the est pos

	{for (int i=0,max=squadlist;i < max;i++)
		if (squadlist[i].squadnum!=lastsquadnum)
		{
			lastsquadnum=squadlist[i].squadnum;
			int bodywps=0;
			ref=toarea;
			for (wp=Persons2::ConvertPtrUID(ref);ref!=ldarea;wp=Persons2::ConvertPtrUID(ref=wp->nextwp))
				wp->etas=ENABLE_COMPLEX_VAL;
			CalcWPRelTimes(i, targettime, rvtime);
			if (squadlist[i].method<AM_RETURNESCORT)
			{
				ref=toarea;
				wp=Persons2::ConvertPtrUID(ref);
				info_waypointPtr towp=Persons2::ConvertPtrUID(squadlist[i].takeoffwp);
				int	lasttime=wp->etas;
				towp->etas=-wp->etas;	//-ve means from bomb RV
				bodywps=0;
				if (lasttime==ENABLE_COMPLEX_VAL)
				{
					bodywps++;
					wp=Persons2::ConvertPtrUID(ref=wp->nextwp);
					lasttime=wp->etas;
					towp->etas=+wp->etas;	//+ve is from fighter RV
				}
				bool quitloop=false;
				for (wp=Persons2::ConvertPtrUID(ref=wp->nextwp);!quitloop;wp=Persons2::ConvertPtrUID(ref=wp->nextwp))
				{
					quitloop=(ref==ldarea);
					int newtime=wp->etas;
					if (newtime!=ENABLE_COMPLEX_VAL)
					{
						int deltatime=newtime-lasttime;
						if (wpdeltas[bodywps]<deltatime)
							wpdeltas[bodywps]=deltatime;
						if (wpmindeltas[bodywps]>deltatime)
							wpmindeltas[bodywps]=deltatime;
						lasttime=newtime;
					}
					bodywps++;
				}
				towp=Persons2::ConvertPtrUID(squadlist[i].landingwp);
				towp->etas=towp->etas.Evaluate()-lasttime;
				int	deltatrgtime=egwp->etas.Evaluate()-ipwp->etas.Evaluate();
				if (deltatrgtime>trgregroupdelta)
					trgregroupdelta=deltatrgtime;
			}
			else
			{
				ref=toarea;
				wp=Persons2::ConvertPtrUID(ref);
				int	lasttime=wp->etas;
				while (lasttime==ENABLE_COMPLEX_VAL)
				{
					bodywps++;
					wp=Persons2::ConvertPtrUID(ref=wp->nextwp);
					lasttime=wp->etas;
				}
				info_waypointPtr towp=Persons2::ConvertPtrUID(squadlist[i].takeoffwp);
				towp->etas=lasttime;
				wp=Persons2::ConvertPtrUID(ref=wp->nextwp);
				int newtime=wp->etas;
				int deltatime=newtime-lasttime;
				if (wpdeltas[bodywps]<deltatime)
					wpdeltas[bodywps]=deltatime;
				if (wpmindeltas[bodywps]>deltatime)
					wpmindeltas[bodywps]=deltatime;
				towp=Persons2::ConvertPtrUID(squadlist[i].landingwp);
				towp->etas=towp->etas.Evaluate()-newtime;
			}
		}
		else
		{
			info_waypointPtr towp=Persons2::ConvertPtrUID(squadlist[i].takeoffwp);
			towp->etas=ENABLE_COMPLEX_VAL;
	}	}

	{for (int i=0;i<maxbodywps;i++)		wpdeltas[i]=(wpdeltas[i]+wpmindeltas[i])/2;}	//A happy median...
	if (trgwp)							//Mind the cludge!
		trgwp->World=backupworldpos;	//Put proper position back!

	//OK.. at this point I hve worst case delta times for every blooming waypoint in the business!!!
	//The given time is for the fighter RV.
	//For RAF this is the toarea. For LW it is the WP before.
	wp=Persons2::ConvertPtrUID(toarea);
	int	bmbrvtime=absrvtime;
	if (wp->uid.Evaluate()==-SGR_WPP_BombRendezvous)
		bmbrvtime-=wpdeltas[0];	//worst time to get between RVs!

	int currtime=bmbrvtime;
	int	bodywps=0;
	wp=Persons2::ConvertPtrUID(ref=toarea);		//First RV
	wp->etas=currtime;
	for (wp=Persons2::ConvertPtrUID(ref=wp->nextwp);ref!=trguid;wp=Persons2::ConvertPtrUID(ref=wp->nextwp))
	{
		currtime=currtime+wpdeltas[bodywps++];	//do all waypoints up to IP
		wp->etas=currtime;
	}
	currtime=currtime+wpdeltas[bodywps++];	//do IP
	wp->etas=currtime;							
	int	targettimes[15]={0};					//do target area
	int	iptime=currtime;
	for (wp=Persons2::ConvertPtrUID(ref=wp->nextwp);ref!=regroupuid;wp=Persons2::ConvertPtrUID(ref=wp->nextwp))
	{
		int newtargetref=wp->applywave.Evaluate()+5;
		int	newtime;
		if (targettimes[newtargetref]==0)
			newtime=wpdeltas[bodywps++]+iptime;
		else
			newtime=wpdeltas[bodywps++]+targettimes[newtargetref];
		wp->etas=newtime;
		targettimes[newtargetref]=newtime;
	}

	bodywps++;									//do egress point. Don't use bodywps entry
	if (attackmethod == AM_PATROL)
		trgregroupdelta=HR01;
	currtime=iptime+trgregroupdelta;
	wp->etas=currtime;
	for (wp=Persons2::ConvertPtrUID(ref=wp->nextwp);ref!=ldarea;wp=Persons2::ConvertPtrUID(ref=wp->nextwp))
	{
		currtime=currtime+wpdeltas[bodywps++];	//do all waypoints up to disperse
		wp->etas=currtime;
	}
	int prevwptime=currtime;
	currtime=currtime+wpdeltas[bodywps++];	//disperse
	wp->etas=currtime;
	int	lasttotime=-1,lastlandtime=-1;	//want to do landing and take-off "together"
	int	slowestsqtakeofftime=bmbrvtime;
	for (int s=0,m=squadlist;s<m;s++)
	{
		info_waypointPtr	takewp=Persons2::ConvertPtrUID(squadlist[s].takeoffwp);
		info_waypointPtr	landwp=Persons2::ConvertPtrUID(squadlist[s].landingwp);
		if (takewp->etas!=ENABLE_COMPLEX_VAL)
		{
				lasttotime=takewp->etas;
				lastlandtime=landwp->etas;
		}
		int actualtakeofftime;
		if (squadlist[s].method>AM_RETURNESCORT)				//MS 28Oct100
		{
			actualtakeofftime=squadlist[s].FixTakeOffTime(prevwptime,lasttotime);
			landwp->etas=lastlandtime+currtime;
		}
		else													//MS 28Oct100
		if (lasttotime>0)
		{
			actualtakeofftime=squadlist[s].FixTakeOffTime(absrvtime,lasttotime);
			landwp->etas=lastlandtime+prevwptime;
		}
		else
		{
			actualtakeofftime=squadlist[s].FixTakeOffTime(bmbrvtime,-lasttotime);
			landwp->etas=lastlandtime+currtime;
		}
		if (actualtakeofftime<slowestsqtakeofftime)
			slowestsqtakeofftime=actualtakeofftime;
		lastlandtime+=10;	//10 seconds between squads in landing...
	}
	delete[]wpdeltas;
	delete[]wpmindeltas;
   return(slowestsqtakeofftime);
}

bool Profile::CalcWPTimes()	//returns true if given time is valid
{
	int absrvtime;
	int targettime = 0;
	int rvtime = 0;
	int slowestsq;

	int earliesteta=FindEarliestPrimaryTargetETA(absrvtime,  slowestsq);		//find slowest
	CalcWPRelTimes(slowestsq, targettime, rvtime);				//find rvtime for slowest
	absrvtime =  primarytargetETA - targettime + rvtime;
	int earliesttakeoff=CalcWPAbsTimes(absrvtime, slowestsq);
	return (earliesttakeoff>=MMC.currtime);								//JIM 14Nov00

}


//////////////////////////////////////////////////////////////////////
//
// Function:    Remove109ReturnWP
// Function:    Insert109ReturnWP
// Date:		28/06/00
// Author:		RDH
//
//Description: 	Insert a dogleg WP at the given ditance back from the start WP
//				It is inserted relative to dogleg and IP, but at position generated in code below
//
//////////////////////////////////////////////////////////////////////
bool	Profile::Remove109ReturnWP()
{
	UniqueID	udogleg=route;
	info_waypointPtr wp=Persons2::ConvertPtrUID(udogleg);
	while(wp->uid.Evaluate()!=-SGR_WPP_DogLeg)
		wp=Persons2::ConvertPtrUID(udogleg=wp->nextwp);
	UniqueID	uIP=udogleg,ureturn=UID_NULL,preureturn=UID_NULL;
	while(wp->uid.Evaluate()!=-SGR_WPP_IP)
	{	
//		On map screen, World X,Y,Z is absolute!
//		if (wp->target.Evaluate()!=ENABLE_COMPLEX_VAL)
//			lastpos+=(Persons2::ConvertPtrUID(UniqueID(wp->target.Evaluate())).World;
		if (!ureturn)
			preureturn=uIP;
		wp=Persons2::ConvertPtrUID(uIP=wp->nextwp);

		if (wp->uid.Evaluate()==-SGR_WPC_FighterLimit)
			ureturn=uIP;
	}
	break109=false;
	if (ureturn)
	{
		info_waypointPtr	returnwp=Persons2::ConvertPtrUID(ureturn);
		info_waypointPtr wp=Persons2::ConvertPtrUID(preureturn);
		wp->nextwp=returnwp->nextwp;
		wp=Persons2::ConvertPtrUID(returnwp->nextwp);
		wp->prevwp=preureturn;
		Persons2::delUID(ureturn);
		delete returnwp;												//JIM 6Oct00
		wpsused--;
		return true;
	}
	else
		return false;
}
//////////////////////////////////////////////////////////////////////
bool	Profile::Insert109ReturnWP(int reqdistcm)
{	//Find IP and WP before it:
	UniqueID	udogleg=route;
	info_waypointPtr wp=Persons2::ConvertPtrUID(udogleg);
	break109=true;
	while(wp->uid.Evaluate()!=-SGR_WPP_DogLeg)
		wp=Persons2::ConvertPtrUID(udogleg=wp->nextwp);
	int distdogip=0;
	UniqueID	uIP=udogleg,ureturn=UID_NULL,preureturn=UID_NULL;
	while(wp->uid.Evaluate()!=-SGR_WPP_IP)
	{	
		Coords3D	lastpos=wp->World;
//		On map screen, World X,Y,Z is absolute!
//		if (wp->target.Evaluate()!=ENABLE_COMPLEX_VAL)
//			lastpos+=(Persons2::ConvertPtrUID(UniqueID(wp->target.Evaluate())).World;
		if (!ureturn)
			preureturn=uIP;
		wp=Persons2::ConvertPtrUID(uIP=wp->nextwp);
		Coords3D	nextpos=wp->World;
//		if (wp->target.Evaluate()!=ENABLE_COMPLEX_VAL)
//			nextpos+=(Persons2::ConvertPtrUID(UniqueID(wp->target.Evaluate())).World;
		distdogip+=Math_Lib.distance3d(lastpos.X-nextpos.X,lastpos.Z-nextpos.Z,0);

		if (wp->uid.Evaluate()==-SGR_WPC_FighterLimit)
			ureturn=uIP;
	}
//DeadCode RDH 16Aug00 	if (distbackcm<0)
//DeadCode RDH 16Aug00 		distbackcm=METRES500;
//DeadCode RDH 16Aug00 	int reqdistcm=distdogip-distbackcm;
	if (reqdistcm<METRES500)
		reqdistcm=METRES500;
	if (distdogip>METRES1000)											//MS 15Nov00
		distdogip-=METRES500;											//MS 15Nov00
	else																//MS 15Nov00
		distdogip/=2;													//MS 15Nov00
	if (reqdistcm>=distdogip)
		reqdistcm=distdogip;
	info_waypointPtr returnwp;
	if (ureturn)
	{	//unhook existing Wp
		returnwp=Persons2::ConvertPtrUID(ureturn);
		info_waypointPtr wp=Persons2::ConvertPtrUID(preureturn);
		wp->nextwp=returnwp->nextwp;
		wp=Persons2::ConvertPtrUID(returnwp->nextwp);
		wp->prevwp=preureturn;
	}
	else
	{	//create new wp object
		returnwp=new info_waypoint;
		wpsused++;
		ureturn=
			returnwp->uniqueID.count=Persons2::assignuid(WayPointBAND);
		Persons2::tabulateUID(returnwp);
		returnwp->position.MakeIcptGRExpr(SGR_WPP_IP,SGR_WPP_DogLeg,false);
		returnwp->position[2][2]=0;
		returnwp->position[1][1]=0;
		returnwp->position[2][1]=0;
		returnwp->uid=-SGR_WPC_FighterLimit;
		returnwp->wpact=WP_fighterlimit;
		returnwp->range=METRES100;
	}

	//Ok.. now need to work my way through the route until I find the pair of wps that bracket the return range
	UniqueID	uafter=udogleg;
	wp=Persons2::ConvertPtrUID(uafter);
	distdogip=0;
	ANGLES	hdg=ANGLES_0Deg;
	while(distdogip<=reqdistcm)											//MS 15Nov00
	{
		Coords3D	lastpos=wp->World;
//		if (wp->target.Evaluate()!=ENABLE_COMPLEX_VAL)
//			lastpos+=(Persons2::ConvertPtrUID(UniqueID(wp->target.Evaluate())).World;
		preureturn=uafter;
		wp=Persons2::ConvertPtrUID(uafter=wp->nextwp);
		Coords3D	nextpos=wp->World;
//		if (wp->target.Evaluate()!=ENABLE_COMPLEX_VAL)
//			nextpos+=(Persons2::ConvertPtrUID(UniqueID(wp->target.Evaluate())).World;
		distdogip+=Math_Lib.distance3d(lastpos.X-nextpos.X,lastpos.Z-nextpos.Z,0)+1;	//MS 15Nov00
		hdg=Math_Lib.arctan(lastpos.X-nextpos.X,lastpos.Z-nextpos.Z);
	}

	//wp is pointing after our waypoint

	//Insert our wp in the list
	{
		returnwp->nextwp=uafter;
		returnwp->prevwp=preureturn;
		wp->prevwp=ureturn;
		info_waypointPtr wpp=Persons2::ConvertPtrUID(preureturn);
		wpp->nextwp=ureturn;
	}
	//Set the position in World
	{
		returnwp->World=wp->World;
		Float	s,c;
		Math_Lib.high_sin_cos(hdg,s,c);
		distdogip-=reqdistcm;
		returnwp->World.X+=s*distdogip;
		returnwp->World.Z+=c*distdogip;
	}
	//Set expression to match position
	returnwp->position.RecalcDeltasToMatch(returnwp->World);
	return (reqdistcm>METRES500);

}

bool	Profile::RemoveOverExtendedFlights()
{
	//Ok.. this no longer actually removes them... Leave that to launch time...

	int reqfueltime, fueltime;
	int i = 0;
	int goodmain=0;
	int goodesc=0;
	int badones=0;
	SquadNum	badlist[100]={SQ_ZERO};
	SquadNum	lastbad=SQ_ZERO;
	SquadNum	lastbadmain=SQ_ZERO;
	for(;i <squadlist;i++)
	{
		if (squadlist[i].squadnum!=lastbad)
		{
			lastbad=squadlist[i].squadnum;
			if  (CalcFuel(i, -3, UID_NULL, reqfueltime, fueltime))
				if (squadlist[i].method < AM_ESCORTTYPES)
					goodmain++;
				else
					goodesc++;
			else
				if (squadlist[i].method < AM_ESCORTTYPES)
					lastbadmain=
						badlist[badones++]=
							lastbad;
				else
					if (squadlist[i].Squadron().AcType()!=PT_ME109)
						badlist[badones++]=lastbad;
					else
						if (Calc109FuelShortCut(i)>0)
							goodesc++;
						else
							badlist[badones++]=lastbad;
		}
	}
	if (goodmain!=0)
		lastbadmain=SQ_ZERO;
	else
		INT3;					//No acceptable bombers: Package will be bollox!
	//Delete all squadron lines in badlist (execpt cludge lastbadmain)
	for (int bad=0;bad<badones;bad++)
	{
		lastbad=badlist[bad];
		if (lastbad!=lastbadmain)
			for(int i=squadlist.Max()-1;i>=0;i--)
				if (squadlist[i].squadnum==lastbad)
					DeleteSquadAt(i);
	}
	return badones!=0;
}

SquadNum Profile::CalcFuel(UniqueID uid, int& strikereqfueltime, int& escortreqfueltime,bool usetargets)	
{//returns one squad that failed  if there is NOT sufficient fuel for route
 //for allsquads. Don't consider returing escort though
 //reqfueltime returns remaining flying time at specified uid

	SquadNum fuelok = SQ_ZERO;
	bool escortfuelok = true;
	int reqfueltime, fueltime;
	strikereqfueltime = -1;
	escortreqfueltime = -1;
	bool somestrikeok=false;
	int i = 0;
	cancelsquad=SQ_ZERO;
	while (i <squadlist)
	{
		int targnum=-3;
		if (usetargets)
			targnum=squadlist[i].targetindex;

		if  (		!CalcFuel(i,targnum, uid, reqfueltime, fueltime)	
			)
		{
			if (squadlist[i].method < AM_ESCORTTYPES)
			{
				fuelok = squadlist[i].squadnum;
				cancelsquad=fuelok;
			}
			else if (squadlist[i].method < AM_RETURNESCORT)
 				escortfuelok = false;

		}
		else
			if (squadlist[i].method < AM_ESCORTTYPES)
				somestrikeok=true;

//DeadCode JIM 20Oct00 		int trg = squadlist[i].targetindex;
		if (squadlist[i].method < AM_ESCORTTYPES)
		{
			if 	(		(reqfueltime != -1)
					&&
						(		(reqfueltime < strikereqfueltime)
							||	(strikereqfueltime == -1)
						)
				)
			{
				strikereqfueltime = reqfueltime;
//DeadCode RDH 28Jun00 				if (strikereqfueltime < 0)
//DeadCode RDH 28Jun00 					strikereqfueltime = 0;
			}
		}else	
		{
			if 	(		(reqfueltime != -1)
					&&
						(		(reqfueltime < escortreqfueltime)
							||	(escortreqfueltime == -1)
						)
				)
			{
				escortreqfueltime = reqfueltime;
//DeadCode RDH 28Jun00 				if (escortreqfueltime < 0)
//DeadCode RDH 28Jun00 					escortreqfueltime = 0;
			}
		}

		i++;
	}
	if (!somestrikeok)
		cancelsquad=SQ_MAX;
	if (!escortfuelok)
	{
		int lowestreqfueltime = 10000;
		int lowestsq = -1;
		i = 0;
		while (i <squadlist)
		{
			Squadron* sq = Node_Data[(SquadNum)squadlist[i].squadnum];
			int type = sq->AcType();
			if (type == PT_ME109)
			{
				int ti = squadlist[i].targetindex;
//DeadCode JIM 24Oct00 				squadlist[i].targetindex = -10;	//this avoids target area
				CalcFuel(i, -3, uid, reqfueltime, fueltime);
				if (lowestreqfueltime > fueltime)
				{
					lowestreqfueltime = fueltime;
					lowestsq = i;
				}
//DeadCode JIM 24Oct00 				squadlist[i].targetindex = ti; 
			}
			i++;
		}
		if (lowestreqfueltime != 10000)
		{
			Float remainfuel = Calc109FuelShortCut(lowestsq);
			if (remainfuel < 0)
				remainfuel = 0;		//there is no spare fuel
			remainfuel = remainfuel*0.7;	//move back from IP
			ClassPtr actype;
			actype = Plane_Type_Translate[PT_HE111][0];	//They are supposed to be flying escort!
			int distance = actype->cruisevel* 0.60 * remainfuel ;  //vel in cm/cs
			//jim will use the distance, in cm,  to move the low fuel wp
			bool	acceptable=Insert109ReturnWP(distance);
			CalcWPTimes();												//rdh 17Jul00
			//If acceptable is false the distance was too great!
		}
		else
			Remove109ReturnWP();

	}
	else
		Remove109ReturnWP();

   return (fuelok);

}

bool Profile::CalcFuel(int sqnum, UniqueID uid, int& reqfueltime, int& fueltime)
{
	return CalcFuel(sqnum,squadlist[sqnum].targetindex,uid,reqfueltime,fueltime);
}
	
bool Profile::CalcFuel(int sqnum, int trgnum, UniqueID uid, int& reqfueltime, int& fueltime)	
{//returns true if there is sufficient fuel for route
 //reqfueltime returns remaining flying time at specified uid
//DeadCode RDH 30Jun00 		UniqueID wpuid = route;
//DeadCode JIM 20Oct00 	int i=0;
	COORDS3D last;
//DeadCode JIM 20Oct00 	int lasttime=0;
		int dtime;

	SWord StoresDrag = 0;
//DeadCode JIM 20Oct00 	int targettime = 0;

	Squadron* sq = Node_Data[(SquadNum)squadlist[sqnum].squadnum];
	int type = sq->AcType();
	ClassPtr actype;
	actype = Plane_Type_Translate[type][0];


	int fuel = 0;
	fuel = actype->maxintfuel*1000;   //0.01kg->cg
	if (type==PT_ME109 &&  Save_Data.flightdifficulty[FD_109FUEL])
		fuel*=1.75;														//JIM 24Jul00

	//takeoff
//DeadCode RDH 30Jun00 	info_waypoint* wp=*Persons2::ConvertPtrUID(wpuid);
//	last=&wp->World;
	int reqfuel = fuel;
	int orgfuel = reqfuel;

	fuel = fuel - 1000000;//allowance for take-off and landing	

	UniqueID wpuid = squadlist[sqnum].takeoffwp;
  	if (wpuid == uid)
		reqfuel = fuel;
	info_waypoint* wp=*Persons2::ConvertPtrUID(wpuid);
	last=wp->World;
	wpuid = wp->NextWP(sqnum,trgnum);

	type = sq->AcType();
	Coords3D faketarget;
	while (wpuid)
	{
		wp=*Persons2::ConvertPtrUID(wpuid);

		if (wp->uid==-SGR_WPP_BombRendezvous && squadlist[sqnum].method>=AM_ESCORTTYPES)
		{
			wpuid = wp->NextWP(sqnum,trgnum);
			wp=*Persons2::ConvertPtrUID(wpuid);
		}
		if (wp->uid==-SGR_WPP_IP && squadlist[sqnum].targetindex==0)
			faketarget=Persons2::ConvertPtrUID(wp->NextWP(-2,-2)).World;	//Est point world.
		if (wp->uid==-SGR_WPC_Target && squadlist[sqnum].targetindex==0)
		{
			faketarget.Y=wp->World.Y;
 			fuel -=Profile::CalcFuel(&last, &faketarget, type, type, StoresDrag);			//CSB 18/06/99			
		}
		else
 			fuel -=Profile::CalcFuel(&last, &wp->World, type, type, StoresDrag);			//CSB 18/06/99			
 		if (wpuid == uid)
			reqfuel = fuel;

		last.X=wp->World.X;
		last.Z=wp->World.Z;
		wpuid = wp->NextWP(sqnum,trgnum);

	}

	if (orgfuel != reqfuel)
	{
		reqfueltime = reqfuel/(0.75* actype->fuelaboff);		//cg/ (cg/cs)
		reqfueltime = reqfueltime / 6000;	//mins
		if (reqfueltime < 0)
			reqfueltime = 0;
	}else
			reqfueltime = -1;			//uid not found

	fueltime = fuel/(0.75* actype->fuelaboff);		//arround 80 - so div 60
	fueltime = fueltime/6000;						//so div 360000
	fueltime = fueltime - 5;	//safety allowance	//so sub 1800000

//DeadCode RDH 28Jun00 	if (fueltime < 0)
//DeadCode RDH 28Jun00 		fueltime = 0;
//DeadCode RDH 28Jun00 
	if (fueltime > 0)
		return (true);
	else
		return(false);
//DeadCode RDH 28Jun00 	return (fueltime!=0);												//JIM 22/02/00

}


//////////////////////////////////////////////////////////////////////
//
// Function:    Calc109FuelShortCut
// Date:		04/10/00
// Author:		JIM
//
//Description: 	//returns remaining fuel in term of time left in air
//				//If time is negative then this squad couldn't do the run 'straight'
//
//////////////////////////////////////////////////////////////////////
Float Profile::Calc109FuelShortCut(int sqnum)	
{

//DeadCode JIM 20Oct00 	int i=0;
	COORDS3D last;
//DeadCode JIM 20Oct00 	int lasttime=0;
		int dtime;

	SWord StoresDrag = 0;
//DeadCode JIM 20Oct00 	int targettime = 0;

	Squadron* sq = Node_Data[(SquadNum)squadlist[sqnum].squadnum];
	int type = sq->AcType();
	int escortee=type;
	ClassPtr actype;
	actype = Plane_Type_Translate[type][0];


	int fuel = 0;
	fuel = actype->maxintfuel*1000;   //0.01kg->cg
	if (type==PT_ME109 &&  Save_Data.flightdifficulty[FD_109FUEL])
		fuel*=1.75;														//JIM 24Jul00

	fuel = fuel - 1000000;//allowance for take-off and landing	

	UniqueID wpuid = squadlist[sqnum].takeoffwp;
 	info_waypoint* wp=*Persons2::ConvertPtrUID(wpuid);
	last=wp->World;
	wpuid = wp->NextWP(sqnum,-9);
 	wp=*Persons2::ConvertPtrUID(wpuid);
	type = sq->AcType();
	while (wpuid)
	{
//DeadCode RDH 16Aug00 		wp=*Persons2::ConvertPtrUID(wpuid);
		if (wp->uid==-SGR_WPP_BombRendezvous || wp->uid==-SGR_WPP_BombDisperse)  //always do this for 109's
		{
//DeadCode RDH 16Aug00 			if (escortee==type)
//DeadCode RDH 16Aug00 				escortee=PT_HE111;
//DeadCode RDH 16Aug00 			else
//DeadCode RDH 16Aug00 				escortee=type;
			wpuid = wp->NextWP(sqnum,-9);
			wp=*Persons2::ConvertPtrUID(wpuid);
		}

		

 		fuel -=Profile::CalcFuel(&last, &wp->World, escortee, type, StoresDrag);			//CSB 18/06/99			

		last.X=wp->World.X;
		last.Z=wp->World.Z;
//DeadCode RDH 16Aug00 		do
//DeadCode RDH 16Aug00 		{

//TempCode RDH 17Aug00 			if (wp->uid==-SGR_WPP_EscRendezvous)
//TempCode RDH 17Aug00 				escortee=PT_HE111;
			if (wp->uid==-SGR_WPP_DogLeg)
			do{
				escortee=type;
				wpuid = wp->NextWP(sqnum,-9);
				if (wpuid)
					wp=*Persons2::ConvertPtrUID(wpuid);		
			}while (wpuid && wp->uid!=-SGR_WPP_BombDisperse && wp->uid!=-SGR_WPP_EscDisperse);
			else
				wpuid = wp->NextWP(sqnum,-9);
			if (wpuid)
				wp=*Persons2::ConvertPtrUID(wpuid);
//DeadCode RDH 16Aug00 		}while	(		(wp->uid < -SGR_WPP_DogLeg)
//DeadCode RDH 16Aug00 					&&	(wp->uid > -SGR_WPP_EscDisperse)
//DeadCode RDH 16Aug00 				);
//DeadCode RDH 16Aug00 
	}


	Float fueltime = fuel/(0.75* actype->fuelaboff);
	fueltime = fueltime/6000;
	fueltime = fueltime - 10;	//safety allowance

	return(fueltime);
}

bool Profile::GetPackageFromWP(UniqueID req_wpuid,int& pack,int& squad,int& target)
{
//DEADCODE DAW 26/11/99 	g = 0;
 	for (pack=0;pack<Profile::MAX_PACKS;pack++)
	{
		if (Todays_Packages.pack[pack].packagestatus!=PS_SPARE)
		{
			info_waypoint* wp;
			UniqueID u=Todays_Packages.pack[pack].route;
			while (u)
			{
				wp=*Persons2::ConvertPtrUID(u);
				if ( u == req_wpuid)
				{
					if (&squad!=NULL)
						if (wp->applygroup.Evaluate()!=ENABLE_COMPLEX_VAL)
							squad=wp->applygroup.Evaluate();
						else
							squad=-1;
					if (wp->applywave.Evaluate()!=ENABLE_COMPLEX_VAL)
					{
						int t=wp->applywave.Evaluate();
						if (&squad!=NULL && squad==-1)
						{
							for (int i=Todays_Packages.pack[pack].squadlist.Max()-1;i>=0;i--)
								if (Todays_Packages.pack[pack][i].targetindex==t)
									squad=i;
						}
						if (&target!=NULL)
							target=t;
					}
//DEADCODE DAW 26/11/99 					if (wp->applygroup != GOT_UNDEFINED_VAL)
//DEADCODE DAW 26/11/99 						g = wp->applygroup;
					return (true);
				}
	   			u=wp->nextwp;
			}
		}
	}
	return (false);
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetSquad
// Date:		01/03/00
// Author:		CSB
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
UniqueID	Profile::Squad::SetSquad(SquadNum newsquadnum)
{

	squadnum=newsquadnum;
	UniqueID base=Node_Data[newsquadnum].homeairfield;
	if (instance && instance!=IllegalSepID)
	{
		info_airgrpPtr a=Persons2::ConvertPtrUID(instance);
			a->type=squadnum;
			a->knownposition=
				a->World=
					Persons2::ConvertPtrUID(base)->World;
	}
	if (takeoffwp && takeoffwp !=IllegalSepID)
	{
		info_waypointPtr w=Persons2::ConvertPtrUID(takeoffwp);
			w->target=base;
	}
	if (landingwp && landingwp !=IllegalSepID)
	{
		info_waypointPtr w=Persons2::ConvertPtrUID(landingwp);
			w->target=base;
	}

	fuelleft=50000000;	//Should depend on aircraft type...
	//proper fuel found in following code:
	if((instance) && (instance != IllegalSepID))						//CSB 24Aug00
	{																	//CSB 24Aug00
		info_airgrpPtr a = Persons2::ConvertPtrUID(instance);			//CSB 24Aug00
		int	ptype = a->type.Evaluate();									//CSB 24Aug00
		if(ptype > SQ_BR_START)											//CSB 24Aug00
			ptype = Node_Data[SquadNum(ptype)].AcType();				//CSB 24Aug00
		PlaneInit* pi = Plane_Type_Translate[ptype];					//CSB 24Aug00
		WheeledType* wi = (WheeledType*)pi;								//CSB 24Aug00
																		//CSB 24Aug00
		fuelleft = wi->maxintfuel * 1000;								//CSB 24Aug00
		if((Save_Data.flightdifficulty[FD_109FUEL]) && (fuelleft == 29900000))	//CSB 24Aug00
			fuelleft = wi->maxintfuel * 1750;							//CSB 24Aug00
	}																	//CSB 24Aug00

	return base;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    WPType
// Date:		03/12/99
// Author:		JIM
//
//Description:	Returns a string description of a waypoint
//				At this stage I don't have wpname set up, 
//				but I can use setuid in an equivalent manner.
//
//////////////////////////////////////////////////////////////////////
int Profile::WPType(UniqueID u)
{
		int text = IDS_INSERTEDWAYPOINT;
		info_waypoint *wp;
		wp = *Persons2::ConvertPtrUID(u);
		if (wp)
		{
			if (wp->uid == GOT_UNDEFINED_VAL)
			{
				if (		(wp->applygroup != GOT_UNDEFINED_VAL)
						||	(wp->applywave != GOT_UNDEFINED_VAL)
					)
				{
//DEADCODE  21/02/00 					if (wp->applygroup == 0)
//DEADCODE  21/02/00 					{
						int action=wp->wpact.Evaluate();
						if (action==ENABLE_COMPLEX_VAL)
							action=wpacnoactionno;
						if (action != wpacnoactionno)
							text = 	IDS_L_WPACTION_NONE + action;
//DEADCODE  21/02/00 					}else
//DEADCODE  21/02/00 						text = (int)wp->applygroup + IDS_ATTACK;
				}

			}else
			{
				int uid = -(int)wp->uid;
				if (uid>=SGR_WPP_TakeOff && uid<=SGR_WPP_Landing)
				{
					text=(uid-SGR_WPP_TakeOff+IDS_WP_TAKEOFF);
				}
				else
				if (uid>=SGR_WPP_Msg0 && uid<=SGR_WPP_Msg9)
				{
					text=(uid-SGR_WPP_Msg0+IDS_L_WP_MSG0);
				}
				else
				switch (uid)
				{
					case	SGR_WPC_TakeOff:	text=IDS_WP_TAKEOFF;	break;	
					case	SGR_WPC_Target:		text=IDS_WP_TARGET;		break;
					case	SGR_WPC_PatrolS:	text=IDS_WP_PATROLSTART;break;
					case	SGR_WPC_PatrolE:	text=IDS_WP_PATROLEND;	break;
					case	SGR_WPC_Landing:	text=IDS_WP_LAND;		break;
					case	SGR_WPC_FighterLimit:text=IDS_WP_109BREAK;	break;
				}

			}
		}
		return(text);
}




int	Profile::CountWaypoints()
{
	if (!route)
		return 0;
	int	rv=1;
	for (info_waypoint* wp=*Persons2::ConvertPtrUID(route);
			wp->nextwp;wp=*Persons2::ConvertPtrUID(wp->nextwp))
		rv++;
	return rv;
}

int	 PackageList::UsedWaypoints()
{
	int	rv=0;
	for (int packnum=0;packnum<Profile::MAX_PACKS;packnum++)
		rv+=pack[packnum].wpsused;
	return rv;
} 

bool	PackageList::CanAddMoreWaypoints(int	packnum)
{
	if (pack[packnum].wpsused>180)
		return false;
	else
	if (UsedWaypoints()>MaxWaypoints())
		return false;
	else
		return true;
}

void	Profile::PackageComplete()
{

	UniqueID* u=&route;
	if (*u)
		Todays_Packages.InvalidateRoute(this);
	packagestatus=PS_COMPLETE;

	while (*u)
	{
		info_waypoint *w=*Persons2::ConvertPtrUID(*u);
			Persons2::delUID(*u);
			*u=w->nextwp;
			delete w;
	}
	wpsused=0;
	int raidline=0;
	int	raidadd=UID_BIT15;
	if (attackmethod>=AM_LWPACKS)
			raidadd=UID_BIT15+UID_BIT14;
	int	raidalias=raidnumentries[raidline].raidnum+raidadd;
	int	packalias=UID_BIT14+((this-Todays_Packages.pack)<<5);

	for (int i=0,max=squadlist;i<max;i++)
	{
		Todays_Packages.ChangeMessagesUID(squadlist[i].instance,packalias);
		Node_Data.intel.ChangeMessagesUID(squadlist[i].instance,raidalias);
		if (squadlist[i].instance==raidnumentries[raidline+1].squadliststart)
		{
			raidalias=raidnumentries[++raidline].raidnum+raidadd;
			packalias++;
		}
		info_airgrp *a=*Persons2::ConvertPtrUID(squadlist[i].instance);
		Persons2::delUID(squadlist[i].instance);
		squadlist[i].instance=UID_NULL;
		squadlist[i].playercansee=false;						//RJS 12Nov00
		squadlist[i].squaddetected=false;						//RJS 12Nov00
		delete a;
	}
	ApplyFlyingLossesDiary();

}

void	PackageList::ChangeMessagesUID(UniqueID old,int newid)
{
	for (int p=0;p<Profile::MAX_PACKS;p++)
		if (pack[p].packagestatus!=Profile::PS_SPARE)
		{
			for (int t=0;t<Profile::MAX_TARGETS;t++)
				if (pack[p].packagetarget[t]==old)
				{
					pack[p].packagetarget[t]=UniqueID(newid);
					UniqueID wpu=pack[p].route;
					for (info_waypointPtr wp=Persons2::ConvertPtrUID(wpu);wpu;wp=Persons2::ConvertPtrUID(wpu=wp->nextwp))
					{
						if (wp->target.UsesGlobRef(SGR_Pack_Target+t) || wp->position.UsesGlobRef(SGR_Pack_Target+t))
						{
							wp->target=ENABLE_COMPLEX_VAL;
							wp->position.MakeAbsWorldPos(wp->World.Y);
							wp->position[0][0]=wp->World.X;
							wp->position[0][2]=wp->World.Z;
						}
					}
				}
			UniqueID wpu=pack[p].route;
			for (info_waypointPtr wp=Persons2::ConvertPtrUID(wpu);wpu;wp=Persons2::ConvertPtrUID(wpu=wp->nextwp))
			{
	//DeadCode  20Jul00 			if (wp->applywave==-2)
	//DeadCode  20Jul00 				INT3;

				if (wp->target.UsesUID(old) || wp->position.UsesUID(old))
				{
					wp->target=ENABLE_COMPLEX_VAL;
					wp->position.MakeAbsWorldPos(wp->World.Y);
					wp->position[0][0]=wp->World.X;
					wp->position[0][2]=wp->World.Z;
				}
			}
			for (int s=0,max=pack[p].squadlist;s<max;s++)
			{
				info_airgrpPtr ag=Persons2::ConvertPtrUID(pack[p][s].instance);
				if (ag && ag->target.UsesUID(old,true))
				{
//DeadCode MS 15Nov00 					INT3;
					ag->target=0;
				}


			}
		}
		else
		{
			assert (	pack[p].squadlist.pointer==NULL	&&	pack[p].raidnumentries==NULL
					&&	pack[p].route==UID_NULL			&&	pack[p].wpsused==0);

		}
}

void	Profile::Squad::SetStatus(PackageStatus stat)
{
	status=stat;
	if (stat>PS_PLANNING)
	{
		::Squadron& s=Node_Data[squadnum];

		if (stat>PS_ACTIVE_MIN)
		{
			if (s.periodstatus>=Squadron::NO_FLYING)
				s.periodstatus=Squadron::NO_ACTION;
			s.totestatus=stat;
		}
		else
			switch (s.totestatus)
			{
				case	PS_SPARE:
				case	PS_ORDER_30:
				case	PS_AT_30:
				case	PS_PLAN_30:		s.totestatus=PS_PLAN_30;	break;

				case	PS_ORDER_5:
				case	PS_ORDER_2:
				case	PS_AT_5:
				case	PS_PLAN_5:		s.totestatus=PS_PLAN_5;	break;

				case	PS_AT_2:
				case	PS_PLAN_2:		s.totestatus=PS_PLAN_2;	break;


				default:				s.totestatus=PS_PLAN_5;	break;
			}

	}
}

void	Profile::SquadComplete(int sqline)
{
	Todays_Packages.InvalidateIcon(squadlist[sqline].instance);
	SquadNum	squadnum=SquadNum(squadlist[sqline].squadnum);
	squadlist[sqline].status=PS_COMPLETE;
	squadlist[sqline].playercansee=false;						//RJS 12Nov00
	squadlist[sqline].squaddetected=false;						//RJS 12Nov00
	::Squadron*	sq=Node_Data[squadnum];
	//temp hit this squad to see if any others from this squad are in air...
	squadlist[sqline].squadnum=SQ_ZERO;
	int	pack;
	if (!Todays_Packages.GetSquadEntry(squadnum,pack))
	{
		if (squadnum>SQ_LW_START)
			sq->totestatus=PS_COMPLETE;
		else
		{
			sq->totestatus=PS_AT_5;
		}
	}
	squadlist[sqline].squadnum=squadnum;
	UniqueID leadinst=squadlist[sqline].instance,inst;
	for (int i=0,max=squadlist;i<max;i++)
		if ((inst=squadlist[i].instance)!=UID_NULL)
		{
			info_airgrpPtr ag=Persons2::ConvertPtrUID(inst);
			if (ag->leader.Evaluate()==leadinst)
				ag->leader=ENABLE_COMPLEX_VAL;
		}
}
	
bool	PackageList::GetSquadEntry(SquadNum s,int&pk,int&sq)
{
	for (int i=0;i<Profile::MAX_PACKS;i++)
		if (pack[i].packagestatus!=Profile::PS_COMPLETE)							//JIM 31/03/00
		{
			Profile&p=pack[i];
			for (int j=p.squadlist.Max()-1;j>=0;j--)
				if (s==p[j].squadnum)
				{
					pk=i;
					if (&sq!=NULL)
						sq=j;
					return true;
				}
		}
	return false;
}

bool	Profile::GetACSquadEntry(UniqueID ac,int&sq)
{
		for (int j=squadlist.Max()-1;j>=0;j--)
			if (ac==squadlist[j].instance)
			{
				sq=j;
				return true;
			}
		return false;

}
bool	PackageList::GetACSquadEntry(UniqueID ac,int&pk,int&sq)
{
	if (ac&UID_BIT14)
	{
		assert ((ac&UID_BIT15)==0);
		int raid=ac&0x1f;
		int p=(ac>>5)&0x1ff;
		pk=p;
		if (&sq!=NULL)
			sq=pack[p].RaidNumEntriesMinSq(raid);
		return true;
	}
	info_airgrpPtr a=Persons2::ConvertPtrUID(ac);
	if (a)
	{
		Profile* prof=a->package;
		if (prof)
		{
			pk=(prof-pack);
			Profile&p=*prof;
			int j;
			if (p.GetACSquadEntry(ac,j))
			{
				if (&sq!=NULL)
					sq=j;
				return true;
			}
		}
	}
	return false;
}
int		Profile::GetRaidIndFromSquadEntry(int sqentry)
{
	int i;
	for (i=1;raidnumentries[i].squadliststart<=sqentry;i++)
	{}
	return i-1;
}

int		Profile::RaidNumEntriesMaxSq(int entry)
{
	int	rv=raidnumentries[entry+1].squadliststart;
	if (rv>squadlist.Max())
		rv=squadlist.Max();
	return rv-1;
}
int		Profile::CountRaid(int squadentry)
{
	int r=GetRaidIndFromSquadEntry(squadentry);
	int min=RaidNumEntriesMinSq(r);
	int max=RaidNumEntriesMaxSq(r);
	int count=0;
	for (;min<=max;min++)
		if (squadlist[min].playercansee)
			count+=squadlist[min].numacleft;
	return count;
}


bool	PackageList::GetWPTargEntry(UniqueID s,int&pk,int&trg)
{
	for (int i=0;i<Profile::MAX_PACKS;i++)
	{
		Profile&p=pack[i];
		info_waypoint* wp;
		for (UniqueID u=p.route;u;)
		{
			wp=Persons2::ConvertPtrUID(u);
			if (u==s)
			{
				if (&trg!=NULL)
				{
					if (wp->target.Evaluate()!=GOT_UNDEFINED_VAL && wp->target.Evaluate()!=UID_NULL)
					{
						u=UniqueID(wp->target.Evaluate());
						trg=WPTS_LOCALTAKEOFF;
						if (p.doglegloc==u)
							trg=WPTS_DOGLEG;
						if (p.packagetakeoff==u)
							trg=WPTS_MAINTAKEOFF;
						for (int j=0;j<Profile::MAX_TARGETS;j++)
							if (p.packagetarget[j]==u)
								trg=j;
					}
					else
						trg=WPTS_NONE;
				}
				pk=i;
				return true;
			}
			u=wp->nextwp;
		}
	}
	return false;
}

bool	PackageList::GetTargEntry(UniqueID u,int&pk,int&trg)
{
	for (int i=0;i<Profile::MAX_PACKS;i++)
	{
		Profile&p=pack[i];
		for (int j=0;j<Profile::MAX_TARGETS;j++)
			if (p.packagetarget[j]==u)
			{
				pk=i;
				if (&trg!=NULL)
					trg=j;
			}
	}
	return false;
}

bool	Profile::SquadListRef::AllInStatus(PackageStatus s)
{
	bool anyinstatus=false;
	for (int i=Max()-1;i>=0;i--)
		if (Squadron(i).instance)
			if (Squadron(i).status!=s)
				return false;
			else
				anyinstatus=true;
	return anyinstatus;
}
bool	Profile::SquadListRef::AnyInStatus(PackageStatus s)
{
	for (int i=Max()-1;i>=0;i--)
		if (Squadron(i).instance && Squadron(i).status==s)
			return true;
	return false;
}
bool	Profile::SquadListRef::AnyMainInStatus(PackageStatus s)
{
	for (int i=Max()-1;i>=0;i--)
		if (Squadron(i).instance && Squadron(i).method<Profile::AM_ESCORTTYPES && Squadron(i).status==s)
			return true;
	return false;
}
bool	Profile::SquadListRef::AllMainInStatus(PackageStatus s)
{
	bool anyinstatus=false;
	for (int i=Max()-1;i>=0;i--)
		if (Squadron(i).instance && Squadron(i).method<Profile::AM_ESCORTTYPES)
			if (Squadron(i).status!=s)
				return false;
			else
				anyinstatus=true;
	return anyinstatus;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    FixPackageStatus
// Date:		10/09/00
// Author:		JIM
//
//Description: After returning from 3d and after coming out of combat
//				ensure the package's status matches the squad's individual statuses.
//
//////////////////////////////////////////////////////////////////////
void	Profile::FixPackageStatus()
{	//go through each status 
	if (squadlist[0].status<=PS_ACTIVE_MIN && squadlist.AllInStatus(squadlist[0].status))
		packagestatus=squadlist[0].status;
	else
	if (squadlist.AnyInStatus(PS_TAKINGOFF))
		packagestatus=PS_TAKINGOFF;
	else
	if (squadlist.AnyInStatus(PS_FORMING))
		packagestatus=PS_FORMING;
	else
	if (squadlist.AllInStatus(PS_INCOMING))
		packagestatus=PS_INCOMING;
	else
	if (squadlist.AnyInStatus(PS_TARGETAREA))
		packagestatus=PS_TARGETAREA;
	else
	if (squadlist.AnyInStatus(PS_DETAILRAID))
		packagestatus=PS_DETAILRAID;
	else
	if (squadlist.AnyInStatus(PS_ENEMYSIGHTED))
		packagestatus=PS_ENEMYSIGHTED;
	else
	if (squadlist.AnyInStatus(PS_TAKINGOFF))
		packagestatus=PS_TAKINGOFF;
	else
	if (squadlist.AllInStatus(PS_OUTGOING))
		packagestatus=PS_OUTGOING;
	else
	if (squadlist.AnyInStatus(PS_LANDING))
		packagestatus=PS_LANDING;
	else
	if (squadlist.AnyInStatus(PS_REFUELLING))
	{
		packagestatus=PS_REFUELLING;
		//do I need to set up a completion time?
	}
	else
	if (squadlist.AnyInStatus(PS_COMPLETE))
	{
		int r=0;
		for (int s=0,max=squadlist;s<max;s++)
		{
			if (raidnumentries[r+1].squadliststart==s)
				r++;
			if (squadlist[s].Squadron().totestatus!=PS_COMPLETE && squadlist[s].Squadron().totestatus!=PS_AT_5)
			{
				SquadComplete(s);
				Todays_Packages.ChangeMessagesUID(squadlist[s].instance,UID_BIT14+((this-Todays_Packages.pack)<<5)+r);
				if (squadlist[s].Squadron().totestatus==PS_COMPLETE || squadlist[s].Squadron().totestatus==PS_AT_5)
					squadlist[s].ApplyFlyingLosses(squadlist.AcBitsSquad(s));
			}
		}
		if (squadlist.AllInStatus(PS_COMPLETE))
			if (packagestatus!=PS_COMPLETE)
				PackageComplete();

	}
}

Squadron&	Profile::Squad::Squadron()
{
	return Node_Data[SquadNum(squadnum)];

}

//////////////////////////////////////////////////////////////////////
//
// Function:    RemakeRaidList
// Date:		26/01/00
// Author:		DAW
//
//Description:	Separate the package into discrete units
//Assumptions:	I am assuming that the bombers for one target are all together
//				Then the next target and so on.
//				If the close fighters can escort all the way and should straffe the target
//					Then they are placed between the bombers, and will never get seperated
//				If the close fighters can't escort all the way or they patrol at the target area
//					Then they are placed after the bombers, so they can be seperated
//				Then come any loose escorts, which should be grouped by escort type
//				Then come the return cover.
//
//Enhancements:	We may wish to separate a LW package when playing on the LW side so that 
//				the distinct groups can be distinguished.
//
//////////////////////////////////////////////////////////////////////

AttackMethodField	Profile::ReorderPackage(AttackMethodField am)
{	//Orders the package to ensure the above rules
	//First, let's ensure that all escorts are correct
	if (attackmethod>=Profile::AM_LWPACKS)
		am=FixCloseEscortPositions(Profile::AM_LWPACKS,am);
	else
		am=FixCloseEscortPositions(Profile::AM_RAF,am);
	am=FixCloseEscortPositions(Profile::AM_DETACHED,am);
	am=FixCloseEscortPositions(Profile::AM_ATTACHED,am);
	am=FixCloseEscortPositions(Profile::AM_RETURNESCORT,am);
	//now do some reordering...
	//first, assume no reordering...
	
	struct Order
	{
		UByte	fore[MAX_SQUADS],back[MAX_SQUADS];
		int	nextgoodsquad;
		int maxsquad;
		void	WrapUp(int find)
		{
			int b=back[find];
			for (int reorder=find-1;reorder>=nextgoodsquad;reorder--)
			{
				back[reorder+1]=back[reorder];
				fore[back[reorder]]=reorder+1;
			}
			back[nextgoodsquad]=b;
			fore[b]=nextgoodsquad;
			nextgoodsquad++;
		}
	} order;
	order.maxsquad=squadlist;
	for (int i=0;i<order.maxsquad;i++)
		order.fore[i]=order.back[i]=i;
	//next, get all bombers together for each target
	//and all straffing close fighters
	order.nextgoodsquad=0;
	for (int trg=0;trg<MAX_TARGETS;trg++)
	{
		for (int find=order.nextgoodsquad;find<order.maxsquad;find++)
			if (squadlist[order.back[find]].method<AM_DETACHED && squadlist[order.back[find]].targetindex==trg)
				order.WrapUp(find);
		for (find=order.nextgoodsquad;find<order.maxsquad;find++)
			if ((squadlist[order.back[find]].method&AM_GROUPMASK)==AM_ATTACHED && (squadlist[order.back[find]].submethod&SM_DOSTRAFFEGROUND))
			{	//need to find out what attached to and if it is a bomber going for this target then WrapUp()
				info_airgrpPtr ap=Persons2::ConvertPtrUID(squadlist[order.back[find]].instance);
				int leadsq;
				if (!GetACSquadEntry(UniqueID(ap->leader.Evaluate()),leadsq))
					_Error.EmitSysErr("Leader not in squad?");
				if (squadlist[leadsq].targetindex==trg)
				{
					squadlist[order.back[find]].targetindex=trg;
					order.WrapUp(find);
				}
			}
		if (trg==0)
		for (int esctype=AM_DETACHED;esctype<AM_ATTACHED;esctype++)
			for (find=order.nextgoodsquad;find<order.maxsquad;find++)
				if ((squadlist[order.back[find]].method)==esctype && (squadlist[order.back[find]].submethod&SM_DOSTRAFFEGROUND))
				{
					squadlist[order.back[find]].targetindex=trg;
					order.WrapUp(find);
				}

	}
	for (int find=order.nextgoodsquad;find<order.maxsquad;find++)
		if ((squadlist[order.back[find]].method&AM_GROUPMASK)==AM_ATTACHED && !(squadlist[order.back[find]].submethod&SM_DOSTRAFFEGROUND))
		{
			squadlist[order.back[find]].targetindex=-1;
			order.WrapUp(find);
		}
	for (int esctype=AM_DETACHED;esctype<AM_ATTACHED;esctype++)
		for (int find=order.nextgoodsquad;find<order.maxsquad;find++)
			if (squadlist[order.back[find]].method==esctype)
			{
				if (!(squadlist[order.back[find]].submethod&SM_DOSTRAFFEGROUND))
				{
//DeadCode JIM 12Oct00 					squadlist[order.back[find]].targetindex=0;
//DeadCode JIM 12Oct00 				else
					squadlist[order.back[find]].targetindex=-1;
					order.WrapUp(find);
				}
			}
	for (find=order.nextgoodsquad;find<order.maxsquad;find++)
		if ((squadlist[order.back[find]].method&AM_GROUPMASK)==AM_RETURNESCORT)
			{
				squadlist[order.back[find]].targetindex=-3;
				order.WrapUp(find);
			}
	assert(order.nextgoodsquad==order.maxsquad);
	//OK.. so now we have a new ordering.. how to apply it?
	{	Profile::Squad* sqlist=new Profile::Squad[order.maxsquad];
		for (find=0;find<order.maxsquad;find++)
			sqlist[find]=squadlist[order.back[find]];
		for (find=0;find<order.maxsquad;find++)
			squadlist[find]=sqlist[find];
		delete sqlist;
	}
	//Need to reorder the waypoints as well. Need the forward list for that.
	int wpcount=0;
	for (info_waypointPtr wp=Persons2::ConvertPtrUID(route);wp;wp=Persons2::ConvertPtrUID(wp->nextwp))
	{
		wpcount++;
		if (wp->applygroup.Evaluate()!=ENABLE_COMPLEX_VAL)
			wp->applygroup=order.fore[wp->applygroup.Evaluate()];
	}
	wpsused=wpcount;

	RecostRaidList();
	FixTakeOffUID();
	return am;
}

int	Profile::RecostRaidList()
{	//Package is about to take off, so aircraft counts and actions can't be recinded
	//Resize raidlist for worst scenario:
	//1 record per target
	//1 record for near escort
	//1 record for each type of far escort used
	//1 record for return escort if used
	bool	nearescortused=false;
	AttackMethodField		farescorts={0};
	typedef UByte	Targets;
//DEADCODE JIM 21/06/00 	enum	Targets	{};

	MAKEFIELD(Targets,0,15);
	TargetsField	targetsusedbits={0};	
	bool	returnescortused=false;
	for (int i=0,max=squadlist;i<max;i++)
	{
		switch (squadlist[i].method&AM_GROUPMASK)
		{
		case AM_RAF:
		case AM_LWPACKS:
			targetsusedbits|=Targets(squadlist[i].targetindex);	
		break;
		case AM_DETACHED:
			farescorts|=squadlist[i].method;
		break;
		case AM_ATTACHED:
			nearescortused=true;
		break;
		case AM_RETURNESCORT:
			returnescortused=true;
		break;
		}
	}
	int totalraids=targetsusedbits.Count()+farescorts.Count()+nearescortused+returnescortused;
	RaidNumEntry* rne2=new RaidNumEntry[totalraids+1];

	rne2[0].squadliststart=0;
	for (i=0;i<=totalraids;i++)
	{
		rne2[i].squadliststart=RNEC_LISTVALISLASTREC;
		rne2[i].raidnum=totalraids;
		rne2[i].detector=0;												//RDH 14/04/00
		rne2[i].prevpositions[0].Y=-1;
	}
	if (raidnumentries)
	{
//DEADCODE RDH 29/03/00 		for (int i=0;raidnumentries[i].squadliststart!=RNEC_LISTVALISLASTREC;i++)
		rne2[0].raidnum=raidnumentries[0].raidnum;
		rne2[0].detector=raidnumentries[0].detector;
		rne2[0].squadliststart=raidnumentries[0].squadliststart;
	}
	delete [] raidnumentries;
	raidnumentries=rne2;
	return RemakeRaidList(false,false);
}

int	Profile::RemakeRaidList(bool splitbombers,bool splitfighters)
{
	//Initially split raid into:
	//	bombergroup,
	//	AM_CEILING, AM_HIGH, AM_FORWARD_HIGH, AM_FORWARD, AM_FORWARD_LOW, AM_LATE ,
	//	AM_RETURNESCORT
	//If splitbombers set then split each targetindex group of bombers -max 10 targets
	//If splitfighters set then split fighter escort as seperate set
	if (Todays_Packages.localplayer==NAT_RED && attackmethod>=AM_LWPACKS)
	{
		int currentry=0;
		int	lastentry=0;
		int	currtarget=squadlist[0].targetindex;
		bool	gotattached=false;
		bool	doneattdeb=false;
		int maxentries=0;
		for (maxentries=0;raidnumentries[maxentries].squadliststart!=RNEC_LISTVALISLASTREC;maxentries++)
		{}
		if (raidnumentries[maxentries].squadliststart==RNEC_LISTVALISLASTREC)
			maxentries=raidnumentries[maxentries].raidnum;
		else
			INT3;
		AttackMethod	lastescortpos=AM_LWPACKS;
		for (int s=0,sm=squadlist.Max();s<sm;s++)
		{
			Squad& sq=squadlist[s];
			switch (sq.method&AM_GROUPMASK)
			{
			case AM_LWPACKS:
			{
				assert (!doneattdeb,"Allocated a slot for returning fighters, but more bombers");
				if (sq.targetindex!=currtarget)
				{
					currtarget=sq.targetindex;
					currentry++;
					if (splitbombers)
					{
						lastentry=currentry;
						if (raidnumentries[currentry].squadliststart==RNEC_LISTVALISLASTREC)
							raidnumentries[currentry].raidnum=0;
						raidnumentries[currentry].squadliststart=s;
					}
				}
			}
			break;
			case AM_ATTACHED:
			{
				if (sq.targetindex<0 && lastescortpos!= AM_ATTACHED)
					if (splitfighters)
					{	//fighters get a slot filled in now
						doneattdeb=true;
						lastentry++;
						while(lastentry<=currentry)
						{
							raidnumentries[lastentry].raidnum=0;
							raidnumentries[lastentry].squadliststart=s;
							lastentry++;
						}
						currentry++;
						if (raidnumentries[currentry].squadliststart==RNEC_LISTVALISLASTREC)
							raidnumentries[currentry].raidnum=0;
						raidnumentries[currentry].squadliststart=s;
						lastescortpos=AM_ATTACHED;
					}
					else
					{
						lastescortpos=AM_ATTACHED;
						currentry++;		//reserve for fighters if fighters not filled in yet.
					}
			}
			break;
			case AM_DETACHED:
			{
				if (lastescortpos!=sq.method)
				{
					if (lastescortpos==AM_LWPACKS)
					{
//DeadCode RJS 26Oct100 						if (gotattached)
//DeadCode RJS 26Oct100 							currentry++;		//reserve for fighters if fighters not filled in yet.
						lastentry++;
						while(lastentry<=currentry)
						{
							raidnumentries[lastentry].raidnum=0;
							raidnumentries[lastentry].squadliststart=s;
							lastentry++;
						}
					}
					lastescortpos=sq.method;
					currentry++;
					if (raidnumentries[currentry].squadliststart==RNEC_LISTVALISLASTREC)
						raidnumentries[currentry].raidnum=0;
					raidnumentries[currentry].squadliststart=s;
				}
			}
			break;
			case AM_RETURNESCORT:
			{
				if (lastescortpos==AM_LWPACKS)
				{
					if (gotattached)
						currentry++;		//reserve for fighters if fighters not filled in yet.
					lastescortpos=AM_RETURNESCORT;
					lastentry++;
					while(lastentry<=currentry)
					{
						raidnumentries[lastentry].raidnum=0;
						raidnumentries[lastentry].squadliststart=s;
						lastentry++;
					}
				}
				currentry++;
				if (raidnumentries[currentry].squadliststart==RNEC_LISTVALISLASTREC)
					raidnumentries[currentry].raidnum=0;
				raidnumentries[currentry].squadliststart=s;
			}
			break;
			}//case
		}//for
//DeadCode RDH 18Sep00 		lastentry++;													//JIM 18Sep00
//DeadCode RDH 18Sep00 		while(lastentry<=currentry)
//DeadCode RDH 18Sep00 		{
//DeadCode RDH 18Sep00 			raidnumentries[lastentry].raidnum=0;
//DeadCode RDH 18Sep00 			raidnumentries[lastentry].squadliststart=s;
//DeadCode RDH 18Sep00 			lastentry++;
//DeadCode RDH 18Sep00 		}
		if (currentry>maxentries)
			INT3;

		for (int r=0;r<=currentry;r++)
			if (raidnumentries[r].squadliststart<sm)
			{
				raidnumentries[r].firstsquaddiaryentry=squadlist[raidnumentries[r].squadliststart].diaryentry;
			}
		return currentry+1;
	}//if lw pack and raf player
	return 1;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    FixTakeOffUID
// Date:		03/07/00
// Author:		JIM
//
//Description: 	Select the airfield to be the main take-off
//
//////////////////////////////////////////////////////////////////////
UniqueID	Profile::FixTakeOffUID()
{
	if (attackmethod>=AM_LWPACKS)
	{	//luftwaffe
		int	flagsum=0,bombersum=0;
		for (int sq=0,sqmax=squadlist;sq<sqmax;sq++)
			if (squadlist[sq].method<AM_ESCORTTYPES)
				bombersum|=Node_Data[squadlist[sq].Squadron().homeairfield].truedefenses;
			else
				flagsum|=Node_Data[squadlist[sq].Squadron().homeairfield].truedefenses;
		flagsum|=bombersum;
		int	currentbaseflags=0;
		flagsum &=Target::MASK_OTHER;
		currentbaseflags &= Target::MASK_OTHER;
		if (packagetakeoff)
			currentbaseflags=Node_Data[packagetakeoff].truedefenses;
		if (currentbaseflags==Target::DEF_LW_SE)
			return packagetakeoff;	  //If already have SE just return it 

		if (bombersum&Target::DEF_LW_SE)
			flagsum=Target::DEF_LW_SE;
		else
			if (flagsum!=Target::DEF_LW_NE&&flagsum!=Target::DEF_LW_C&&flagsum!=Target::DEF_LW_SW)
				flagsum=0;
		if (flagsum==0)
			packagetakeoff=UID_AF_Amiens;
		else
			if (currentbaseflags!=flagsum)
				for (int sq=0,sqmax=squadlist;sq<sqmax;sq++)
					if (squadlist[sq].method<AM_ESCORTTYPES)
						if (flagsum&Node_Data[squadlist[sq].Squadron().homeairfield].truedefenses)
							return packagetakeoff=squadlist[sq].Squadron().homeairfield;
		return packagetakeoff;
	}
	else
	{	//RAF
		if (!packagetakeoff)
			packagetakeoff=squadlist[0].Squadron().homeairfield;
		return packagetakeoff;
	}


}

bool Profile::UnitIsFighter(int j, bool me110isbomber)
{
	Squadron* sq  = Node_Data[Node_Data.gruppe[j].squadron];
	PlaneTypeSelect actype = sq->AcType(); 
	if  (		(actype == PT_ME109)
			||	((actype == PT_ME110)	&&	(!me110isbomber))
		)
			return (true);
	else
			return(false);

}
bool Profile::UnitIsBomber(int j, bool me110isbomber)
{
	Squadron* sq  = Node_Data[Node_Data.gruppe[j].squadron];
	PlaneTypeSelect actype = sq->AcType(); 
	if  (		(actype == PT_JU88)
			||	((actype == PT_ME110)	&&	(me110isbomber))
			||	(actype == PT_DO17)
			||	(actype == PT_HE111)
			||	(actype == PT_JU87)
		)
			return (true);
	else
			return(false);

}
//DeadCode JIM 14Nov00 bool Profile::SqIsAvail(int j, typestolist)
//DeadCode JIM 14Nov00 {
//DeadCode JIM 14Nov00 	bool avail = false;
//DeadCode JIM 14Nov00 	Squadron* sq  = Node_Data[Node_Data.gruppe[j].squadron];
//DeadCode JIM 14Nov00 	if  (	(	(	(acisfighter) &&	(UnitIsFighter(j, me110isbomber))
//DeadCode JIM 14Nov00 				)
//DeadCode JIM 14Nov00 			||
//DeadCode JIM 14Nov00 				(	(!acisfighter) &&	(UnitIsBomber(j, me110isbomber))
//DeadCode JIM 14Nov00 				)
//DeadCode JIM 14Nov00 			)
//DeadCode JIM 14Nov00 				&&	(!sq->Busy())
//DeadCode JIM 14Nov00 				&&	(sq->acavail >= Gruppen::MIN_GRUPPEAC)
//DeadCode JIM 14Nov00 
//DeadCode JIM 14Nov00 		)
//DeadCode JIM 14Nov00 		avail = true;
//DeadCode JIM 14Nov00 	return (avail);
//DeadCode JIM 14Nov00 }
bool Profile::StraffRequired(int attackmethod)
{
	bool straf = false;
	for (int num= squadlist.Max()-1;num>=0;num--)
		if  (	((squadlist[num].method&Profile::AM_GROUPMASK)==attackmethod)
			&&	(squadlist[num].submethod == Profile::SM_DOSTRAFFEGROUND)
			)
			straf = true;
	return(straf);
}
int Profile::FindAttackMethod(PlaneTypeSelect actype)
{
	int am = 0;
	for (int num= squadlist.Max()-1;num>=0;num--)
		if ((Node_Data[squadlist[num].squadnum].AcType()&-2)==actype)
		{
			 am =squadlist[num].submethod&SM_ATTACKMETHODSALL;
			 if ((am < SM_DIVEANDZOOM)	||	(am > SM_ATTACKMETHODSALL))
				 am = SM_INDIVIDUAL;
			 am =(am - SM_DIVEANDZOOM)/SM_DIVEANDZOOM;
			 break;
		}
	return(am);
}
int Profile::FindPreferredTarget(PlaneTypeSelect actype)
{//term confusion here we are calling the way the aircraft enter combat: attack method
 // also the hurricanes and spits are distinguished in the dialog with attack menhod
	int am = 0;
	for (int num= squadlist.Max()-1;num>=0;num--)
		if ((Node_Data[squadlist[num].squadnum].AcType()&-2)==actype)
		{
			 am =squadlist[num].submethod&SM_ACCHOICE;
			 break;
		}
	return(am);
}
void	Profile::DeleteNumerousSquadrons(Profile::AttackMethod attackmethod, int delsq)
{
	int i =squadlist - 1;
	while (	(i >= 0)	&&	(delsq > 0)	)
	{
		if ((attackmethod&Profile::AM_GROUPMASK) == (squadlist[i].method&Profile::AM_GROUPMASK))
		{
			DeleteSquadAt(i);
			delsq--;
		}
		i--;
	}


}
void	Profile::DeleteNumerousSquadrons(BetterRule	br, int delsq)
{
	int i =squadlist - 1;
	while (	(i >= 0)	&&	(delsq > 0)	)
	{
		Squadron* sq = Node_Data[(SquadNum)squadlist[i].squadnum];
		int actype = sq->AcType();

		if  (	(	(		(actype == PT_SPIT_A)
						||	(actype == PT_SPIT_B)
					)
					&&
					(br & BR_B_SPITTEST)
				)
				||
				(	(		(actype == PT_HURR_A)
						||	(actype == PT_HURR_B)
					)
					&&
					(br & BR_B_HURRTEST)
				)
			)
		{
			DeleteSquadAt(i);
			delsq--;
		}
		i--;
	}


}

int Profile::FirstSquadofMethod(Profile::AttackMethod attackmethod)
{
	int i = 0;
	while	(		(i < squadlist)
				&&	((attackmethod&Profile::AM_GROUPMASK) != (squadlist[i].method&Profile::AM_GROUPMASK))
			)
			i++;
	return(i);
}
int Profile::FirstSquadNotofMethod(Profile::AttackMethod attackmethod)
{
	int i = 0;
	while	(		(i < squadlist)
				&&	((attackmethod&Profile::AM_GROUPMASK) == (squadlist[i].method&Profile::AM_GROUPMASK))
			)
			i++;
	return(i);
}


void Profile::CompleteSquadron(Profile::AttackMethod attackmethod)	
{
	int i = FirstSquadofMethod((Profile::AttackMethod)attackmethod);
	if (i < squadlist)
	{
		SquadNum sqnum = squadlist[i].squadnum;
		attackmethod = squadlist[i].method;
		int index = squadlist[i].targetindex;

 		DeleteSquadAt(i);
		AddSquadron(-1, (Profile::AttackMethod)attackmethod, packagetarget[index].currentid,sqnum);
		Todays_Packages.SetTaskData();
	}

}
void Profile::CompleteGroup(Profile::AttackMethod attackmethod, int currsquads)	
{
	int i = FirstSquadofMethod((Profile::AttackMethod)attackmethod);
	if (i < squadlist)
	{
 		Profile::BetterRule	br = FindBetterRule();
		SquadNum sqnum = squadlist[i].squadnum;
		attackmethod = squadlist[i].method;

 		DeleteNumerousSquadrons((Profile::AttackMethod)attackmethod);
		AddNumerousSquadrons(Gruppen::MIN_STAFFELAC*(currsquads+1),(Profile::AttackMethod)attackmethod,sqnum,br);
		Todays_Packages.SetTaskData();
	}
}

void Profile::ResetAcNumbers(Profile::AttackMethod attackmethod, int orggrp, int reqgrp, int deltaac)
{
	int i = FirstSquadofMethod((Profile::AttackMethod)attackmethod);
	int deltagrp = reqgrp - orggrp;
	BetterRule	br;
	SquadNum sqnum;
	if (i < squadlist)
	{
		sqnum = squadlist[i].squadnum;
		attackmethod = squadlist[i].method;
 		br = FindBetterRule();
	}else
	{
		br = Profile::BR_WIDESTPOSSIBLE;
		sqnum = SQ_ZERO;
	}
	SubMethod reqsubmethod=SM_ANYA2A;
	int am=(attackmethod&AM_GROUPMASK);
	if (attackmethod>AM_ESCORTTYPES)
	{
		for (int s=0,m=squadlist;s<m;s++)
			if ((squadlist[s].method&AM_GROUPMASK)==am)
			{
				reqsubmethod=squadlist[s].submethod;
				break;
			}
	}
	if (orggrp < 1)
		DeleteNumerousSquadrons((Profile::AttackMethod)attackmethod);
	if (deltagrp > 0)
		AddNumerousSquadrons(-(3*deltagrp),(Profile::AttackMethod)attackmethod,SQ_ZERO,br);
	if (deltagrp < 0)
		DeleteNumerousSquadrons((Profile::AttackMethod)attackmethod, -(3 * deltagrp));
	if (reqgrp < 1 && deltaac > 0)
		AddNumerousSquadrons(deltaac,(Profile::AttackMethod)attackmethod,sqnum,br);
	SetSubMethod((Profile::AttackMethod)am,reqsubmethod);	//RDH 02/04/00
	Todays_Packages.CheckHilightValid();
}
void Profile::RAFResetAcNumbers(Profile::BetterRule brattackmethod, int orgsq, int reqsq, int newnumac)
{
	int deltasq = reqsq - orgsq;
	BetterRule	br=brattackmethod;
	SquadNum sqnum;
//DeadCode JIM 19Oct00 	if (attackmethod == Profile::AM_DETACHED)
//DeadCode JIM 19Oct00 		br = BR_B_SPITONLY;
//DeadCode JIM 19Oct00 	else
//DeadCode JIM 19Oct00 		br = BR_B_HURRONLY;

	sqnum = SQ_ZERO;

	if (orgsq < 1)
		DeleteNumerousSquadrons(br);
	int numspitsq=0,numhurrsq=0;
	for (int s=0,m=squadlist;s<m;s++)
		if (squadlist[s].Squadron().AcType()<PT_HURR_A)
			numspitsq++;
		else
			numhurrsq++;
	if ((br&BR_B_EITHERWL)==BR_B_EITHERWL)
		while (deltasq>0)
			if (numspitsq<numhurrsq)
			{
				AddNumerousSquadrons(-1,attackmethod,SQ_ZERO,BR_B_SPITWL+Profile::BR_B_ALLOWGRP11);
				deltasq--;
				numspitsq++;
			}
			else
			{
				AddNumerousSquadrons(-1,attackmethod,SQ_ZERO,BR_B_HURRWL+Profile::BR_B_ALLOWGRP11);
				deltasq--;
				numhurrsq++;
			}
	else
		if (deltasq > 0)
			AddNumerousSquadrons(-deltasq,attackmethod,SQ_ZERO,br);
	if ((br&BR_B_EITHERWL)==BR_B_EITHERWL)
		while (deltasq < 0)
			if (numspitsq>numhurrsq)
			{
				DeleteNumerousSquadrons(BR_B_SPITWL, 1);
				deltasq++;
				numspitsq--;
			}
			else
			{
				DeleteNumerousSquadrons(BR_B_HURRWL, 1);
				deltasq++;
				numhurrsq--;
			}
	else
		if (deltasq<0)
		{
			if ((br&BR_B_EITHERWL)==BR_B_SPITWL && numhurrsq)
				if (numhurrsq> -deltasq)
				{
					DeleteNumerousSquadrons(BR_B_HURRWL,-deltasq);
				}
				else
				{
					DeleteNumerousSquadrons(BR_B_HURRWL,numhurrsq);
					DeleteNumerousSquadrons(br,-deltasq-numhurrsq);
				}
			elseif ((br&BR_B_EITHERWL)==BR_B_HURRWL && numspitsq)
				if (numspitsq> -deltasq)
				{
					DeleteNumerousSquadrons(BR_B_SPITWL,-deltasq);
				}
				else
				{
					DeleteNumerousSquadrons(BR_B_SPITWL,numspitsq);
					DeleteNumerousSquadrons(br,-deltasq-numspitsq);
				}
			else
				DeleteNumerousSquadrons(br,-deltasq);
		}

	if (	(reqsq < 1)	&&	(newnumac >0))
		if (newnumac==1)
			AddNumerousSquadrons(newnumac,(Profile::AttackMethod)this->attackmethod,sqnum,br);
		else
			AddNumerousSquadrons(newnumac,(Profile::AttackMethod)this->attackmethod,sqnum,BetterRule(BR_B_LEADOPTNL+br));
}
Profile::BetterRule	 Profile::FindBetterRule()
{
	BetterRule br =  BR_NONE;
	if (StraffRequired(Profile::AM_DETACHED))
			 br |= BR_R_DSTRAFE;
	if (StraffRequired(Profile::AM_ATTACHED))
			 br |=  BR_R_ASTRAFE;

	int i = 0;
	while	(i < squadlist)
	{
		int	gruppe = squadlist[i].squadnum;
		switch(Node_Data[(SquadNum)gruppe].AcType())
		{
		 	case	PT_ME110:
			{
				if	(AM_LWPACKS == (squadlist[i].method&Profile::AM_GROUPMASK))
					br |=  BR_R_110BONLY;
				else
					br |=  BR_R_110FONLY;
				break;
			}
			case	PT_JU87:
			{
				br |= BR_R_JU87ONLY;
				break;
			}
			case	PT_DO17:
			{
				br |= BR_R_DO17ONLY;
				break;
			}
			case	PT_JU88:
			{
				br |= BR_R_JU88ONLY;
				break;
			}
			case	PT_HE111:
			{
				br |= BR_R_HE111ONLY;
				break;
			}
			case	PT_ME109:
			{
				br |= BR_R_109FONLY;
				break;
			}
			default:
			{
				break;
			}
		}
		i++;

	}
	return (br);
}
Profile::BetterRule	 Profile::RAFFindBetterRule()
{
//			BR_B_LEADOPTNL	=0x00008,		//This should only be applied to 1,2,3 aircraft
//		BR_B_ALLOWGRP11	=0x00004,

	BetterRule br =  Profile::BR_B_ALLOWGRP11;
	int i = 0;
	int count = 0;
	while	(i < squadlist)
	{
		count += squadlist[i].numacoriginal;
		switch(Node_Data[squadlist[i].squadnum].AcType())
		{
		 	case	PT_SPIT_A:
		 	case	PT_SPIT_B:
			{
				br |=  BR_B_SPITWL;
				break;
			}
		 	case	PT_HURR_A:
		 	case	PT_HURR_B:
			{
				br |=  BR_B_HURRWL;
				break;
			}
		}
 		i++;

	}
	if (count != 1)														//JIM 20Oct00
		br |=  BR_B_LEADOPTNL;

	return (br);
}
//////////////////////////////////////////////////////////////////////
//
// Function:    ReassignTo
// Date:		31/03/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	Profile::ReassignTo(UniqueID newtarget,bool immediate)
{	

	//Ignoring non-immediate case for now...
	packagetarget[0]=newtarget;
	//If aircraft is after the IP then set to go to the IP
	UniqueID uw=route,ip=UID_NULL,eg=UID_NULL,revec=UID_NULL,delayvec=UID_NULL,pastta;
	while (uw)
	{
		info_waypointPtr wp=Persons2::ConvertPtrUID(uw);
		if (wp->uid.Evaluate()==-SGR_WPP_IP)
			ip=uw;
		if (wp->uid.Evaluate()==-SGR_WPP_Egress)
			eg=uw;
		if (ip==NULL)	
			revec=uw;
		uw=wp->nextwp;
	}
	pastta=eg;
	if (immediate)
		eg=ip;
	else
	{	//remake patrol area waypoints as fixed waypoints before ip

		uw=ip;
		info_waypointPtr wp=Persons2::ConvertPtrUID(uw);
		do{
			uw=wp->nextwp;
			wp=Persons2::ConvertPtrUID(uw);
		}while (uw!=eg && wp->wpact.Evaluate()!=wpstartloopno);
		if (uw!=eg)
		{
			UniqueID after=revec;
			while (uw!=eg && wp->wpact.Evaluate()!=wpstoploopchkno)
			{
				wp=Persons2::ConvertPtrUID(uw);
				UniqueID ip2=ip;	//InsertWpBetween can modify it's input uids based on strange rules I don't care about right now!
				revec=InsertWpBetween(revec,ip2,SGR_Pack_BlankZero,BFieldWaypointActions(wp->wpact.Evaluate()),ENABLE_COMPLEX_VAL,wp->applywave.Evaluate());
				info_waypoint*	w=*Persons2::ConvertPtrUID(revec);
				w->World=wp->World;
				w->position.MakeAbsWorldPos(wp->World.Y);
				w->position.RecalcDeltasToMatch(wp->World);
				uw=wp->nextwp;
			}
			//Insert 1 more WP to act as delay before patrol can end.
			UniqueID ip2=ip;	//InsertWpBetween can modify it's input uids based on strange rules I don't care about right now!
			delayvec=InsertWpBetween(revec,ip2,UID_NULL,wpacnoactionno,ENABLE_COMPLEX_VAL,ENABLE_COMPLEX_VAL);
			info_waypoint*	w=*Persons2::ConvertPtrUID(delayvec);
			w->World=wp->World;
			w->position.MakeAbsWorldPos(wp->World.Y);
			w->position.RecalcDeltasToMatch(wp->World);

			revec=after;
		}

	}
	for (int sq=0,sqmax=squadlist;sq<sqmax;sq++)
		if (squadlist[sq].status<PS_ACTIVE_MAX)	//Too late: squad is landing
		{
			if (squadlist[sq].status>PS_FORMING)
			{
				info_airgrpPtr a=Persons2::ConvertPtrUID(squadlist[sq].instance);
				uw=a->wpref;
				while (uw && uw!=ip && uw!=eg)
				{
					info_waypointPtr wp=Persons2::ConvertPtrUID(uw);
					uw=wp->nextwp;
				}
				if (!uw)
					a->wpref=ip;
				elseif (uw!=ip)
				{	//a/c is currently patrolling, and it is a delayed revector
					a->wpref=revec;
				}
				a->movecode=AUTOSAG_FOLLOWWP;
				squadlist[sq].status=PS_OUTGOING;
				a->target=UID_NULL;
			}
			squadlist[sq].method=AM_INTERCEPT;
		}
	if (attackmethod==AM_PATROL)
	{	//need to remove old patrol waypoints
		uw=ip;
		info_waypointPtr wp=Persons2::ConvertPtrUID(uw);
		uw=wp->nextwp;
		wp->nextwp=pastta;
		while (uw!=pastta)
		{
			info_waypointPtr wp=Persons2::ConvertPtrUID(uw);
			Persons2::delUID(uw);
			uw=wp->nextwp;
			delete wp;
		}
		//Insert new attack waypoint
		UniqueID newwp=InsertWpBetween(ip,eg,SGR_Pack_BlankZero,wpacnoactionno,ENABLE_COMPLEX_VAL,-2,IllegalSepID,SGR_WPP_EstPoint);
		info_waypoint*	w=*Persons2::ConvertPtrUID(newwp);
		w->target=ENABLE_COMPLEX_VAL;
		info_itemS*	i=*Persons2::ConvertPtrUID(newtarget);
		w->World=i->World;
		w->position.RecalcDeltasToMatch(w->World);
		newwp=InsertWpBetween(ip,eg,SGR_Pack_Target,wpengagetargetno,ENABLE_COMPLEX_VAL,0);
		w=*Persons2::ConvertPtrUID(newwp);w->range=METRES7000;
	}
	attackmethod=AM_INTERCEPT;
	//recalculate waypoint times
	int timetobeginintercept=CalcRoutePositionsAndTime(0,SGR_WPP_DogLeg);
	if (delayvec)
	{
		info_waypointPtr wp=Persons2::ConvertPtrUID(delayvec);
		wp->etas=timetobeginintercept;
	}
	CountWaypoints();
}
//////////////////////////////////////////////////////////////////////
//
// Function:    ReturnHome
// Date:		31/03/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	Profile::ReturnHome()
{	//This routine forces everyone to go home
	//First find correct home waypoints for fighters and bombers
	UniqueID uw=route,escdp=UID_NULL,bombdp=UID_NULL;
	while (uw)
	{
		info_waypointPtr wp=Persons2::ConvertPtrUID(uw);
		if (wp->uid.Evaluate()==-SGR_WPP_EscDisperse)
			escdp=uw;
		elseif (wp->uid.Evaluate()==-SGR_WPP_BombDisperse)
			bombdp=uw;
		uw=wp->nextwp;
	}
	if (escdp==UID_NULL)
		escdp=bombdp;
	if (bombdp==UID_NULL)
		bombdp=escdp;
	assert (escdp!=UID_NULL,"No disperse waypoints?");
	for (int sq=0,sqmax=squadlist;sq<sqmax;sq++)
		if (squadlist[sq].status<PS_ACTIVE_MAX)
			if (squadlist[sq].status<=PS_FORMING)
			{	//set to landing WP
				info_airgrpPtr a=Persons2::ConvertPtrUID(squadlist[sq].instance);
				a->wpref=squadlist[sq].landingwp;
				assert (a->wpref);
				a->movecode=AUTOSAG_FOLLOWWP;
				a->target=UID_NULL;
				squadlist[sq].status=PS_OUTGOING;
			}
			else
			{	//set to disperse if not past it
				info_airgrpPtr a=Persons2::ConvertPtrUID(squadlist[sq].instance);
				a->movecode=AUTOSAG_FOLLOWWP;
				a->target=UID_NULL;
				squadlist[sq].status=PS_OUTGOING;
				for (uw=escdp;uw && uw!=a->wpref;)
				{
					info_waypointPtr wp=Persons2::ConvertPtrUID(uw);
					uw=wp->nextwp;
				}
				if (uw==UID_NULL)
					if (squadlist[sq].method<AM_DETACHED)
						a->wpref=bombdp;
					else
						a->wpref=escdp;
				assert (a->wpref);
			}
}
char*	PackageList::RaidFormatString(int packnum, int raid)
{
	char* raidletter;
	if (pack[packnum].attackmethod>=Profile::AM_LWPACKS)
	{
		if (localplayer!=NAT_RAF)
				raidletter="R%03i";
		else
			if (pack[packnum].raidnumentries[raid].detector)
				raidletter="H%03i";
			else
				raidletter="X%03i";
	}else
	{
		raidletter="F%03i";
	}
	return(raidletter);
}
//DEADCODE RDH 24/05/00 int	PackageList::FindNumSquadsInPack(int p)
//DEADCODE RDH 24/05/00 {
//DEADCODE RDH 24/05/00 //DEADCODE RDH 12/05/00 	Profile& pk = Todays_Packages.pack[p];
//DEADCODE RDH 24/05/00 	int sqplanned = 0;
//DEADCODE RDH 24/05/00 //DEADCODE RDH 12/05/00 	int i=0;
//DEADCODE RDH 24/05/00 //DEADCODE RDH 12/05/00 	while (i < pk.squadlist)
//DEADCODE RDH 24/05/00 //DEADCODE RDH 12/05/00 	{
//DEADCODE RDH 24/05/00 //DEADCODE RDH 12/05/00 	   sqplanned += pk[i++].squadnum;
//DEADCODE RDH 24/05/00 //DEADCODE RDH 12/05/00 	}
//DEADCODE RDH 24/05/00 	return (sqplanned);
//DEADCODE RDH 24/05/00 
//DEADCODE RDH 24/05/00 }
int	PackageList::SquadronsPlanned(int nationality)
{
	int sqplanned = 0;
	int sagplanned = 0;
	for (int p=0;p<Profile::MAX_PACKS;p++)
	{
		if (	(		(pack[p].packagestatus!=Profile::PS_SPARE)
					&&	(pack[p].packagestatus!=Profile::PS_COMPLETE)
				)
				&&
	   			(	(		(pack[p].attackmethod>=Profile::AM_LWPACKS)
						&&	(nationality != NAT_RAF)
					)
					||
					(
							(pack[p].attackmethod < Profile::AM_LWPACKS)
						&&	(nationality == NAT_RAF)
					)
				)
			)
		{
			Profile& pk = pack[p];
			sqplanned += pk.squadlist;
			int m=pk.squadlist;
			if (m)
				sagplanned++;
			if (nationality != NAT_RAF)
				for (int s=1;s<m;s++)
					if (pack[p][s].squadnum!=pack[p][s-1].squadnum)
						sagplanned++;
		}

	}
	if (nationality != NAT_RAF)
		sagplanned*=2;				//Rob has given me more SAG shapes...
	if (nationality != NAT_RAF)
		if (sagplanned>sqplanned)
			sqplanned=sagplanned;
	return (sqplanned);
}
int	PackageList::BiggestRAFSquadronOnDay()
{
	int biggestsq = 0;

	for (int p=0;p<Profile::MAX_PACKS;p++)
	{
		if (	(		(pack[p].packagestatus!=Profile::PS_SPARE)
				)
				&&
	   			(pack[p].attackmethod < Profile::AM_LWPACKS)
			)
		{
			Profile& pk = Todays_Packages.pack[p];
			if (pk.squadlist > biggestsq)
			biggestsq = pk.squadlist;
		}

	}
	return (biggestsq);
}

bool	PackageList::LondonTargetted()
{
	bool londontargetted = false;
	int pack=0;

	while (pack < Profile::MAX_PACKS)
	{
		if 	(Todays_Packages.pack[pack].packagestatus!=Profile::PS_SPARE)
		{
		 	Profile& pk = Todays_Packages.pack[pack];
			if  (		(pk.attackmethod >= Profile::AM_LWPACKS)
				)
			{
				int targetnum = 0;
				while (pk.packagetarget[targetnum].currentid)
				{
					TargetGroup* trg;
					trg = Node_Data[(UniqueID)pk.packagetarget[targetnum].currentid];
					if (trg->London())
						londontargetted = true;
					targetnum++;
				}
			}
		}
		pack++;
	}
	return(londontargetted);
}
bool	PackageList::TargetDamaged(int uidbandstart, int uidbandend)
{
	int trgstatus = TargetStatus(uidbandstart, uidbandend);
	if (		(trgstatus > 25)
			&&	(trgstatus <100)
		)
			return (true);
	else
			return (false);
}
bool	PackageList::TargetDestroyed(int uidbandstart, int uidbandend)
{
	if (TargetStatus(uidbandstart, uidbandend) >= 100)
			return (true);
	else
			return (false);
}
int	PackageList::TargetStatus(int uidbandstart, int uidbandend)
{
	int pack=0;
	int trgstatus = 0;
	while (pack < Profile::MAX_PACKS)
	{
		if 	(Todays_Packages.pack[pack].packagestatus!=Profile::PS_SPARE)
		{
		 	Profile& pk = Todays_Packages.pack[pack];
			if  (		(pk.attackmethod >= Profile::AM_LWPACKS)
				)
			{
				int targetnum = 0;
				while (pk.packagetarget[targetnum].currentid)
				{
					if (		(pk.packagetarget[targetnum].currentid >= uidbandstart)
							&&	(pk.packagetarget[targetnum].currentid > uidbandend)
						)
					{
						TargetGroup* trg;
						trg = Node_Data[(UniqueID)pk.packagetarget[targetnum].currentid];
						if (trg->knownstatus > trgstatus)
							 trgstatus = trg->knownstatus;
					}
					targetnum++;
				}
			}
		}
		pack++;
	}
	return(trgstatus);
}

bool PackageList::ThousandAcRaid(int& escortratio2)
{
	bool thousandac = false;
	escortratio2 = false;
	int pack=0;
	
	while (pack < Profile::MAX_PACKS)
	{
		if (Todays_Packages.pack[pack].packagestatus!=Profile::PS_SPARE)
		{
			int totalac = 0;
			int escortac = 0;
		 	Profile& pk = Todays_Packages.pack[pack];
			if  (pk.attackmethod >= Profile::AM_LWPACKS)
			{
				int i=0;
				while (i < pk.squadlist)
				{
					totalac += pk[i].numacoriginal;						//JIM 28Aug00
					if (pk[i].method != pk.attackmethod)
						escortac += pk[i].numacoriginal;				//JIM 28Aug00
					i++;
				}
			}
			if (totalac >= 1000)
				thousandac = true;
			if (	(totalac/3) < escortac/2)							//JIM 28Aug00
				escortratio2 = true;
		}
		pack++;
	}
	return (thousandac);

}
void	Profile::ChangeStrikeAcType(int actype)
{
	BetterRule br =  BR_NONE;
 	if (StraffRequired(Profile::AM_DETACHED))
			 br |= BR_R_DSTRAFE;
	if (StraffRequired(Profile::AM_ATTACHED))
			 br |=  BR_R_ASTRAFE;

	switch(actype)
	{
	 	case	PT_ME110:
		{
			br |=  BR_R_110BONLY;
			attackmethod = AM_DIVEBOMB;
			break;
		}
		case	PT_JU87:
		{
			br |= BR_R_JU87ONLY;
			attackmethod = AM_DIVEBOMB;
			break;
		}
		case	PT_DO17:
		{
			br |= BR_R_DO17ONLY;
			attackmethod = AM_LEVELBOMB;
			break;
		}
		case	PT_JU88:
		{
			br |= BR_R_JU88ONLY;
			attackmethod = AM_LEVELBOMB;
			break;
		}
		case	PT_HE111:
		{
			br |= BR_R_HE111ONLY;
			attackmethod = AM_LEVELBOMB;
			break;
		}
	}
	int grpreq, acreq=0; 
	if (	(Todays_Packages.taskdata.strike.acnum >=0)	||	(Todays_Packages.taskdata.strike.squadnum <3))
	{
		grpreq = 0;
	}else
		grpreq = Todays_Packages.taskdata.strike.squadnum/3;
	if (grpreq < 1)
	{
		if (Todays_Packages.taskdata.strike.acnum >=0)
			acreq = Todays_Packages.taskdata.strike.acnum;
		else
			acreq = Todays_Packages.taskdata.strike.squadnum * 10 ;		//MS 16Nov00
	}


	DeleteNumerousSquadrons(attackmethod);
	if (grpreq > 0)
		AddNumerousSquadrons(-(3*grpreq),attackmethod,SQ_ZERO,br);
	else
		AddNumerousSquadrons(acreq,attackmethod,SQ_ZERO,br);

	ReShareSecondaries();												//JIM 28Aug00
	AttackMethodField	am=ScanAttackMethods();
	ReorderPackage(am);
	CalcRoutePositionsAndTime(primarytargetETA);
	
}
AttackMethodField	Profile::ScanAttackMethods()
{
	AttackMethodField rv={0};
	if (attackmethod<AM_LWPACKS)
		return rv;

	for (int s=0,m=squadlist;s<m;s++)
		rv|=squadlist[s].method;

	return rv;
}
void	Profile::SquadSetFormType::operator =(FormationTypeIndex newval)
{
	formtype=newval;
	info_airgrpPtr ag=*Persons2::ConvertPtrUID(instance);
	if (ag)
		ag->form=newval;
}


//////////////////////////////////////////////////////////////////////
//
// Function:    HandleLaterEvents
// Date:		30/10/00
// Author:		JIM
//
//Description:	Either creates handlers for packages that have not been detected yet or 
//				estimates when those packages may become visible
//////////////////////////////////////////////////////////////////////
int	PackageList::HandleLaterEvents()
{
	int	earliesttime=0x1000000;

	for (int i=0;i<Profile::MAX_PACKS;i++)
		if (pack[i].packagestatus!=Profile::PS_SPARE && pack[i].packagestatus<Profile::PS_OUTGOING)
		if (pack[i].attackmethod>Profile::AM_LWPACKS && !pack[i].packagehasbeenintercepted)
			if (localplayer!=NAT_RAF || MMC.autoscramble)
			{	//Can launch a handler immediately
				for (int re=0;pack[i].raidnumentries[re].squadliststart!=Profile::RNEC_LISTVALISLASTREC;re++)
					if (pack[i].raidnumentries[re].squadliststart!=pack[i].raidnumentries[re+1].squadliststart)
					{
						Directives::RAF::MissTypes  mt =RAFDirectivesResults::RAFInterceptType(i,0);
						if (MMC.directives.raf.current.sanctioned[mt])
						{
							RAFDirectivesResults::InterceptSanctioned(i,re);
							earliesttime++;
						}
					}
			}
			else
			{
				Directives::RAF::MissTypes  mt =RAFDirectivesResults::RAFInterceptType(i,0);
				if (MMC.directives.raf.current.sanctioned[mt])
				{	//Must generate a best guess exit time
					//Step through the route and see which waypoint is detectable:
					info_waypointPtr wp=Persons2::ConvertPtrUID(pack[i].route);
					info_waypointPtr wpprev=Persons2::ConvertPtrUID(wp->NextWP(-1));
					wp=Persons2::ConvertPtrUID(wpprev->NextWP(-1));
					int unseen;
					while (wpprev->uid!=-SGR_WPP_IP)
					{
						breakif(Node_Data.GroundVisible(wp->World,&unseen) || unseen==IllegalBAND);
						wpprev=wp;
						wp=Persons2::ConvertPtrUID( wp->NextWP(-1) );
						if ( wp == NULL )
							break;
					}
					int ETA=wpprev->etas.Evaluate();
					if ( wp!=NULL )
					{
						Coords3D pickpoint=wpprev->World,pickpoint2=wp->World;
						float range=Math_Lib.DistanceSquared(pickpoint.X-pickpoint2.X,pickpoint.Z-pickpoint2.Z);
						if (	ETA!=wp->etas.Evaluate() 
							&&	wpprev->uid!=-SGR_WPP_IP 
							&&	!Node_Data.GroundVisible(wpprev,&unseen) 
							&&	unseen!=IllegalBAND
							)
						{
							while (range>=METRES5000*METRES5000)
							{
								Coords3D midpick;
								midpick.X=(pickpoint.X+pickpoint2.X)/2;
								midpick.Y=(pickpoint.Y+pickpoint2.Y)/2;
								midpick.Z=(pickpoint.Z+pickpoint2.Z)/2;
								if (Node_Data.GroundVisible(midpick,&unseen) || unseen==IllegalBAND)
									pickpoint2=midpick;
								else
									pickpoint=midpick;
								range=Math_Lib.DistanceSquared(pickpoint.X-pickpoint2.X,pickpoint.Z-pickpoint2.Z);
							}
							if (pickpoint.X-wpprev->World.X!=0)
								ETA+=(wp->etas.Evaluate()-wpprev->etas.Evaluate())
									*Float(pickpoint.X-wpprev->World.X)
									/(wp->World.X-wpprev->World.X);
							elseif (pickpoint.Z-wpprev->World.Z!=0)
								ETA+=(wp->etas.Evaluate()-wpprev->etas.Evaluate())
									*Float(pickpoint.Z-wpprev->World.Z)
									/(wp->World.Z-wpprev->World.Z);
						}
					}
					if (ETA<earliesttime)
						earliesttime=ETA;
				}
			}
	MMC.earliestquit3dtimecs=earliesttime*100;
	return earliesttime&0x3fffffff;
}
