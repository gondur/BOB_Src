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
//Filename       savebin.cpp
//System         
//Author         Jim Taylor
//Date           Wed 8 Jul 1998
//Description    Saves the package in binary
//------------------------------------------------------------------------------
#include	"dosdefs.h"
#include	"stdio.h"
#define	F_COMMON
#define F_GRAFIX	
#include	"files.g"
#include	"fileman.h"
//DEADCODE JIM 30/11/99 #include	"node.h"
#include "nodebob.h"
#include	"makebf.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include	"bstream.h"
#include	"sqddiary.h"										//RJS 02Feb00

#define C	(char)

void	PackageList::SaveBin()
{
	File_Man.DiscardDirList(FIL_RUNTIMEPACK0);
	BuildReorderTable();
	FileNum	fnum=FIL_RUNTIMEPACK0;
	for (int packs=0;packs<Profile::MAX_PACKS;packs++)
		if (pack[packs].packagestatus!=Profile::PS_SPARE && pack[packs].wpsused)
		{
			if (Todays_Packages[packs][0].diaryentry == -1)		//RJS 27Jan00
			{
				for (int s=0,max=Todays_Packages[packs].squadlist;s<max;s++)
					MMC.thisweekreview.Note(Todays_Packages[packs][s].Squadron().AcType(),PeriodReview::SORTIES,Todays_Packages[packs][s].numacoriginal);
				Squad_Diary.CreateEntry(Todays_Packages,packs);	//RJS 27Jan00
			}

			BOStream f(File_Man.namenumberedfile(fnum));
			SaveBin(&pack[packs],f);
			fnum=FileNum(fnum+1);
		}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    BuildReorderTable
// Date:		18/01/00
// Author:		JIM
//
//Description: 	Reorder the SAG UIDs before entering the 3D section.
//				If you actually want them to stay the same you must still call this routine, but with FALSE
//
//////////////////////////////////////////////////////////////////////
UniqueID	PackageList::ReorderLookup[MAX_REORDERLOOKUP];
int debugmaxcount;
void	PackageList::BuildReorderTable(bool doreorder)
{
//	UniqueID	*ReorderLookup;
	for (int i=0;i<MAX_REORDERLOOKUP;i++)
		ReorderLookup[i]=UniqueID(SagBAND+i);
	int reorder=SagBAND;
	int	reorderempty=RealAcBAND-1;
	if (doreorder)
		for (int p=0;p<Profile::MAX_PACKS;p++)
			if (pack[p].packagestatus>Profile::PS_PLANNING && pack[p].packagestatus<Profile::PS_COMPLETE)
				for (int s=0,smax=pack[p].squadlist;s<smax;s++)
					if (pack[p][s].numacleft)
						ReorderLookup[pack[p][s].instance-SagBAND]=UniqueID(reorder++);
					else
						ReorderLookup[pack[p][s].instance-SagBAND]=UniqueID(reorderempty--);
	debugmaxcount=reorder;
}
UniqueID	PackageList::Reorder(UniqueID u)
{
	if (u>=SagBAND && u<RealAcBAND)
	{
		assert (ReorderLookup[u-SagBAND]<debugmaxcount);
		return (ReorderLookup[u-SagBAND]);
	}
	else
		return u;
}

UniqueID	PackageList::ReorderZero(UniqueID u)
{
	if (u>=SagBAND && u<RealAcBAND)
	{
		if (ReorderLookup[u-SagBAND]<debugmaxcount)
			return (ReorderLookup[u-SagBAND]);
		else
			return UID_NULL;
	}
	else
		return u;
}

UniqueID	PackageList::ReorderNoCheck(UniqueID u)
{
	if (u>=SagBAND && u<RealAcBAND)
	{
//DeadCode JIM 16Sep00 		assert (ReorderLookup[u-SagBAND]<debugmaxcount);
		return (ReorderLookup[u-SagBAND]);
	}
	else
		INT3;
	return u;
}

//
// Decodes text header into a profile instance
//[newline],wave,group,squad,flights=callname,takeofftime,arrivaltime,[numchars]
//note wave/group screwup.
//DEADCODE DAW 24/11/99 static const char* savegroupstringnew="\nW%iG%iS%iF%i=C%iT%iA%i:";
//DEADCODE DAW 24/11/99 static const char* loadgroupstringold=  "G%iW%iS%iF%i=C%iT%iA%i:%n";
//DEADCODE DAW 24/11/99 static const char* loadgroupstringnew=  "W%iG%iS%iF%i=C%iT%iA%i:%n"; 
//
//DEADCODE DAW 24/11/99 static const Profile::TargetDescript	emptydesc={UID_NULL};
static const char* line1out=	
	"Package battlefield: Duty %i %i, Squads %i, Raids: %i, WPs %i, Takeoff,Target,Dogleg %05x,%05x,%05x, Times %09x,%09x\n";	
static const char* line1in=		
	"Package battlefield: Duty %i %i, Squads %i, Raids: %i, WPs %i, Takeoff,Target,Dogleg %05x,%05x,%05x, Times %09x,%09x%n";
static const char* line2out=	"Secondaries: %05x+%05x %05x+%05x %05x+%05x %05x+%05x %05x+%05x %05x+%05x %05x+%05x %05x+%05x %05x+%05x\n";
static const char* line2in=		"Secondaries: %05x+%05x %05x+%05x %05x+%05x %05x+%05x %05x+%05x %05x+%05x %05x+%05x %05x+%05x %05x+%05x%n";
static const char* linesqout=	"Sq: i%05x s%3i f%05x d%09x n%09x f%03x, Targ %2i %9i %9i, Act %05x %05x %05x %i\n";
static const char* linesqin=	"Sq: i%05x s%3i f%05x d%09x n%09x f%03x, Targ %2i %9i %9i, Act %05x %05x %05x %i%n";
static const char*	linerout=	"Raid: %5i %5i %03x %3i %3i d%09x; %09x %09x %09x; %09x %09x %09x; %09x %09x %09x; %09x %09x %09x\n";
static const char*	linerin=	"Raid: %5i %5i %03x %3i %3i d%09x; %09x %09x %09x; %09x %09x %09x; %09x %09x %09x; %09x %09x %09x%n";
static const char* lollyout="Lolly %08x\n";
static const char* lollyin="Lolly %08x%n";
int	Profile::DecodePackage(string packstr,bool decodeprimary)
{
	int results[10];
	int flights=0;
	int	numraids;
	int offset;
//DeadCode JIM 20Oct00 	bool ptarg=false;

	int argsused=sscanf(packstr,line1in,
			results+0,results+7,results+1,results+2,results+3,
			results+4,results+5,results+6,
			results+8,results+9,
			&offset);
	if (argsused<10)
		return 0;
	packstr+=offset;
	while (*packstr++!='\n')
	{}
	attackmethod=AttackMethod(results[0]);
	flights=results[1];
	numraids=results[2];
	flags=results[3];
	primarytargetETA=results[8];
	playerETAdelta=results[9];
	packagetakeoff=(UniqueID)results[4];
	if (decodeprimary)
		packagetarget[0]=packagetarget[0].SGT=(UniqueID)results[5];
	packagetarget[0].targetwaypoint=UID_NULL;
	packagetarget[0].band=PilotedAcBAND;
	packagetarget[0].bandoff=0;
	doglegloc=(UniqueID)results[6];
	packagestatus=(PackageStatus)results[7];
	int	targets[10];
	int	subtargets[10];
	argsused=sscanf(packstr,line2in,	targets+1,subtargets+1,		targets+2,subtargets+2,
										targets+3,subtargets+3,		targets+4,subtargets+4,
										targets+5,subtargets+5,		targets+6,subtargets+6,
										targets+7,subtargets+7,		targets+8,subtargets+8,
										targets+9,subtargets+9,&offset);
	packstr+=offset;
	while (*packstr++!='\n')
	{}
	for (offset=1;offset<MAX_TARGETS;offset++)
	{
		packagetarget[offset].SGT=UniqueID(targets[offset]);
		packagetarget[offset].band=Persons2::getbandfromUID(UniqueID(subtargets[offset]));
		packagetarget[offset].bandoff=subtargets[offset]-packagetarget[offset].band;
		packagetarget[offset].SetTargetFromSGTBandOff();
	}
	squadlist.DeleteAll();
	for (int f=0;f<flights;f++)
	{
		assert(*(int*)packstr==*(int*)"Sq: ");							//JIM 29Oct00
		packstr+=4;
		Squad squadbuffer;
		ULong* squadptr=(ULong*)&squadbuffer;
		assert (sizeof(Squad)%4==0);
		for (int countdown=sizeof(Squad)/4;countdown;countdown--)
		{
			ULong	p0=*packstr++ - 34,
					p1=*packstr++ - 34,
					p2=*packstr++ - 34,
					p3=*packstr++ - 34,
					p4=*packstr++ - 34;
			p0=p0+90*(p1+90*(p2+90*(p3+90*p4)));
			*squadptr++=p0;
		}
		Squad* squad=squadlist+=UniqueID(squadbuffer.instance);
		*squad=squadbuffer;

		assert(*packstr=='\n');
		packstr++;
//DeadCode CRAIG 30Oct100 		int inst,sq,form,targ,tot,lwt,no,fights,diary,action,subact,status,fuel;
//DeadCode CRAIG 30Oct100 		int params=sscanf(packstr,linesqin,
//DeadCode CRAIG 30Oct100 					&inst,&sq,&form,&diary,&fights,&no,	&targ,&tot,&lwt,	&action,&subact,&status,&fuel,	&offset);
//DeadCode CRAIG 30Oct100 		if (params!=12)
//DeadCode CRAIG 30Oct100 			INT3;
//DeadCode CRAIG 30Oct100 		Squad* squad=squadlist+=UniqueID(inst);
//DeadCode CRAIG 30Oct100 		squad->fightperiods=fights;
//DeadCode CRAIG 30Oct100 		squad->diaryentry=diary;
//DeadCode CRAIG 30Oct100 		squad->squadnum=SquadNum(sq);
//DeadCode CRAIG 30Oct100 		squad->formtype=(FormationTypeIndex)form;
//DeadCode CRAIG 30Oct100 		squad->targetindex=targ;	//temporary...
//DeadCode CRAIG 30Oct100 		squad->lastwptime=lwt;
//DeadCode CRAIG 30Oct100 		squad->takeofftime=tot;
//DeadCode CRAIG 30Oct100 		squad->numbers=no;
//DeadCode CRAIG 30Oct100 		squad->method=AttackMethod(action);
//DeadCode CRAIG 30Oct100 		squad->submethod=SubMethod(subact);
//DeadCode CRAIG 30Oct100 		squad->status=PackageStatus(status);
//DeadCode CRAIG 30Oct100 		squad->fuelleft=fuel;
//DeadCode CRAIG 30Oct100 		packstr+=offset;
//DeadCode CRAIG 30Oct100 		while (*packstr++!='\n')	
//DeadCode CRAIG 30Oct100 		{}
	}
	if (flights==1)
	{
		int lollyval;
		sscanf(packstr,lollyin,&lollyval,&offset);
		squadlist.SetAcBitsFirstSquad(lollyval);
		packstr+=offset;
		while (*packstr++!='\n')	
		{}
	}
	if (raidnumentries)
		delete [] raidnumentries;
	if (numraids)
		raidnumentries=new Profile::RaidNumEntry [numraids+1];
	else
		raidnumentries=NULL;

	for (int r=0;r<numraids;r++)
	{
		assert(*(int*)packstr==*(int*)"Rd: ");							//JIM 29Oct00
		packstr+=4;
		RaidNumEntry raidbuffer;
		ULong* raidptr=(ULong*)&raidbuffer;

 		assert (sizeof(RaidNumEntry)%4==0);
		for (int countdown=sizeof(RaidNumEntry)/4;countdown;countdown--)
		{
			ULong	p0=*packstr++ - 34,
					p1=*packstr++ - 34,
					p2=*packstr++ - 34,
					p3=*packstr++ - 34,
					p4=*packstr++ - 34;
			p0=p0+90*(p1+90*(p2+90*(p3+90*p4)));
			*raidptr++=p0;
		}
		raidnumentries[r]=raidbuffer;

		assert(*packstr=='\n');
		packstr++;
//DeadCode CRAIG 30Oct100 		int	rn,sst,det,dl,num,al;
//DeadCode CRAIG 30Oct100 		int argsused=sscanf(packstr,linerin,&rn,&sst,&al,&det,&dl,&raidnumentries[r].firstsquaddiaryentry,
//DeadCode CRAIG 30Oct100 		&raidnumentries[r].prevpositions[0].X,&raidnumentries[r].prevpositions[0].Y,&raidnumentries[r].prevpositions[0].Z,
//DeadCode CRAIG 30Oct100 		&raidnumentries[r].prevpositions[1].X,&raidnumentries[r].prevpositions[1].Y,&raidnumentries[r].prevpositions[1].Z,
//DeadCode CRAIG 30Oct100 		&raidnumentries[r].prevpositions[2].X,&raidnumentries[r].prevpositions[2].Y,&raidnumentries[r].prevpositions[2].Z,
//DeadCode CRAIG 30Oct100 		&raidnumentries[r].prevpositions[3].X,&raidnumentries[r].prevpositions[3].Y,&raidnumentries[r].prevpositions[3].Z,
//DeadCode CRAIG 30Oct100 		&num);
//DeadCode CRAIG 30Oct100 		if (argsused!=17)
//DeadCode CRAIG 30Oct100 			INT3;
//DeadCode CRAIG 30Oct100 		raidnumentries[r].raidnum=rn;
//DeadCode CRAIG 30Oct100 		raidnumentries[r].squadliststart=sst;
//DeadCode CRAIG 30Oct100 		raidnumentries[r].detector=det;
//DeadCode CRAIG 30Oct100 		raidnumentries[r].detectlatency=dl;
//DeadCode CRAIG 30Oct100 		raidnumentries[r].alertlevel=al;
//DeadCode CRAIG 30Oct100 		packstr+=num;
//DeadCode CRAIG 30Oct100 		char* holdpoint=packstr;
//DeadCode CRAIG 30Oct100 		while (*packstr++!='\n')
//DeadCode CRAIG 30Oct100 		{}
	}
	if (raidnumentries)
	{
		raidnumentries[numraids].squadliststart=Profile::RNEC_LISTVALISLASTREC;
		raidnumentries[numraids].raidnum=numraids;
	}
	return	flights;
}
void	Profile::TargetDesc::SetTargetFromSGTBandOff()
{
	if (band)
	{
		currentid=Persons2::GetNthSGTMember(SGT,band,bandoff);
	}
	else
		currentid=SGT;
}
void	Profile::TargetDesc::SetSGTBandOffFromTarget()
{
	
	ItemPtr p;
	p = NULL;
	if (currentid <= IllegalBAND)
		p =Persons2::ConvertPtrUID(currentid);
	if (!p || !p->SGT)
	{
		SGT=currentid;
		band=PilotedAcBAND;
		bandoff=0;
	}
	else
	{
		SGT=p->SGT;
		band=Persons2::getbandfromUID(currentid);
		bandoff=Persons2::GetNOfSGTMember(SGT,band,currentid);
	}

}
void	Profile::TargetDesc::operator =(UniqueID u)
{
	currentid=u;
	SetSGTBandOffFromTarget();
}

UniqueID Persons2::GetNthSGTMember(UniqueID SGT,UniqueIDBand uidband,int count)
{
	info_itemS *p;
	for (int i=uidband;i<IllegalSepID;i++)
		if ((p=*ConvertPtrUID(UniqueID(i)))!=NULL)
			if (p->SGT==SGT)
				if (!count--)
					return UniqueID(i);
	return SGT;
}

int Persons2::GetNOfSGTMember(UniqueID SGT,UniqueIDBand uidband,UniqueID member)
{
	info_itemS *p;
	int count=0;
	for (int i=uidband;i<member;i++)
		if ((p=*ConvertPtrUID(UniqueID(i)))!=NULL)
			if (p->SGT==SGT)
				count++;
	return count;
}

void	Profile::SetTargetUIDs(bool	fixconvoys)
{	//I want to fix the 10 primary targets at this stage, and attempt to
	//load the takeoff/landing and target waypoint ids.
	//Initially I can't load these as the items haven't been loaded yet.

//DEADCODE RJS 16/11/99 	if (band!=RedTrainBAND && band!=RedTruckBAND)	   //never load these!
	{for (int i=0;i<10;i++)										//JIM 30Nov99
	{
		Node_Data.CheckTargetLoaded(packagetarget[i].SGT);	//JIM 30Nov99
		packagetarget[i].SetTargetFromSGTBandOff();
	}}


}

void	PackageList::SaveBin(Profile* profile,BOStream&file)
{
	if (!profile->route) 
		profile->wpsused=0;
	int numraids=0;
	if (profile->raidnumentries)
	{
		while (profile->raidnumentries[numraids].squadliststart!=Profile::RNEC_LISTVALISLASTREC)
			numraids++;
		numraids=profile->raidnumentries[numraids].raidnum;
	}
	file<<CSprintf(line1out,
		profile->attackmethod,profile->packagestatus,profile->squadlist.Max(),numraids,profile->flags,
		profile->packagetakeoff,Reorder(profile->packagetarget[0]),profile->doglegloc,
		profile->primarytargetETA,profile->playerETAdelta		);

	int	targets[10];
	int	subtargets[10];
	for (int i=1;i<10;i++)
	{
		targets[i]=Reorder(profile->packagetarget[i].SGT);
		subtargets[i]=profile->packagetarget[i].band+profile->packagetarget[i].bandoff;
	}
	file<<CSprintf(line2out,
		targets[1],subtargets[1],	targets[2],subtargets[2],
		targets[3],subtargets[3],	targets[4],subtargets[4],
		targets[5],subtargets[5],	targets[6],subtargets[6],
		targets[7],subtargets[7],	targets[8],subtargets[8],
		targets[9],subtargets[9]);


//DeadCode JIM 20Oct00 	int loopcount=0;	//increase for any fixed fields....
	int maxsq=profile->squadlist;
	for (i=0;i<maxsq;i++)
	{
		Profile::Squad squadbuff=profile->squadlist[i];					//JIM 29Oct00
		if (profile->packagestatus!=Profile::PS_COMPLETE)
			squadbuff.instance=ReorderNoCheck(squadbuff.instance);
		else
			squadbuff.instance=UID_NULL;
		file<<"Sq: ";
		ULong* squadptr=(ULong*)&squadbuff;
		assert (sizeof(Profile::Squad)%4==0);
		for (int countdown=sizeof(Profile::Squad)/4;countdown;countdown--)
		{
			ULong	p0=*squadptr++,
					p1=p0/90,
					p2=p1/90,
					p3=p2/90,
					p4=p3/90;
			char packstr[5];
			packstr[0]=p0%90+34;
			packstr[1]=p1%90+34;
			packstr[2]=p2%90+34;
			packstr[3]=p3%90+34;
			packstr[4]=p4%90+34;
			packstr[5]=0;
			file<<packstr;
		}
		file<<'\n';
//DeadCode CRAIG 30Oct100 		Profile::Squad& squad=profile->squadlist[i];
//DeadCode CRAIG 30Oct100 		if (profile->packagestatus!=Profile::PS_COMPLETE)
//DeadCode CRAIG 30Oct100 			file<<CSprintf(linesqout,
//DeadCode CRAIG 30Oct100 				ReorderNoCheck(squad.instance), +squad.squadnum, +squad.formtype, squad.diaryentry, squad.numbers, squad.fightperiods,
//DeadCode CRAIG 30Oct100 				+squad.targetindex, squad.takeofftime, squad.lastwptime,
//DeadCode CRAIG 30Oct100 				+squad.method, +squad.submethod, +squad.status, squad.fuelleft
//DeadCode CRAIG 30Oct100 
//DeadCode CRAIG 30Oct100 				);
//DeadCode CRAIG 30Oct100 		else
//DeadCode CRAIG 30Oct100 			file<<CSprintf(linesqout,
//DeadCode CRAIG 30Oct100 				0, +squad.squadnum, +squad.formtype, squad.diaryentry, squad.numbers,
//DeadCode CRAIG 30Oct100 				+squad.targetindex, squad.takeofftime, squad.lastwptime,
//DeadCode CRAIG 30Oct100 				+squad.method, +squad.submethod, +squad.status, squad.fuelleft
//DeadCode CRAIG 30Oct100 
//DeadCode CRAIG 30Oct100 				);
//DeadCode CRAIG 30Oct100 
	}
	if (maxsq==1)
	{
		file<<CSprintf(lollyout,profile->squadlist.AcBitsFirstSquad());
	}
	for (i=0;i<numraids;i++)
	{
		file<<"Rd: ";
		ULong* raidptr=(ULong*)&profile->raidnumentries[i];				//JIM 29Oct00
		assert (sizeof(Profile::RaidNumEntry)%4==0);
		for (int countdown=sizeof(Profile::RaidNumEntry)/4;countdown;countdown--)
		{
			ULong	p0=*raidptr++,
					p1=p0/90,
					p2=p1/90,
					p3=p2/90,
					p4=p3/90;
			char packstr[5];
			packstr[0]=p0%90+34;
			packstr[1]=p1%90+34;
			packstr[2]=p2%90+34;
			packstr[3]=p3%90+34;
			packstr[4]=p4%90+34;
			packstr[5]=0;
			file<<packstr;
		}
		file<<'\n';
//DeadCode CRAIG 30Oct100 	file<<CSprintf(linerout,
//DeadCode C		profile->raidnumentries[i].raidnum,	profile->raidnumentries[i].squadliststart,profile->raidnumentries[i].detector,profile->raidnumentries[i].alertlevel,profile->raidnumentries[i].detectlatency,profile->raidnumentries[i].firstsquaddiaryentry,
//DeadCode CRAIG 30Oct100 		profile->raidnumentries[i].prevpositions[0].X,profile->raidnumentries[i].prevpositions[0].Y,profile->raidnumentries[i].prevpositions[0].Z,
//DeadCode CRAIG 30Oct100 		profile->raidnumentries[i].prevpositions[1].X,profile->raidnumentries[i].prevpositions[1].Y,profile->raidnumentries[i].prevpositions[1].Z,
//DeadCode CRAIG 30Oct100 		profile->raidnumentries[i].prevpositions[2].X,profile->raidnumentries[i].prevpositions[2].Y,profile->raidnumentries[i].prevpositions[2].Z,
//DeadCode CRAIG 30Oct100 		profile->raidnumentries[i].prevpositions[3].X,profile->raidnumentries[i].prevpositions[3].Y,profile->raidnumentries[i].prevpositions[3].Z);
	}
	file<<C 26 <<C 0;
	if (profile->wpsused)
	{
		file <<C T_bfsave <<C T_linklist <<C maxsq;
		{
			Profile::Squad& squad=profile->squadlist[0];

			//AirGroup
			// T_inform:	
			// T_inwing:
			// T_duty:	
			// T_form:	
			// T_pos:		
			// T_route:		only leader 
			// T_itemA:
			// T_leader: - new in this position!

			file<<C T_airgrp <<C T_linklist <<C 7;
			SaveRouteBin(profile->route,file);
			profile->SaveAirItemBin(&squad,profile->route,file);
		}
		for (i=1;i<maxsq;i++)
		{
			Profile::Squad& squad=profile->squadlist[i];

			//AirGroup
			// T_inform:	
			// T_inwing:
			// T_duty:	
			// T_form:	
			// T_pos:		
			// T_route:		only leader 
			// T_itemA:
			// T_leader: - new in this position!
			info_airgrp *a=*Persons2::ConvertPtrUID(squad.instance);

			if (a->leader.Evaluate()==ENABLE_COMPLEX_VAL || ReorderZero(UniqueID(a->leader.Evaluate())))
			{
				file<<C T_airgrp <<C T_linklist <<C 7;
				file<<C T_leader; 
				if (a->leader.Evaluate()!=ENABLE_COMPLEX_VAL)
					Expr::putint(ReorderZero(UniqueID(a->leader.Evaluate())),file);
				else
					Expr::putint(0,file);	//NEED TO WORK ON THIS!!!!!
			}
			else
				file<<C T_airgrp <<C T_linklist <<C 6;

			profile->SaveAirItemBin(&squad,profile->route,file);

		}
	}
}


void	PackageList::SaveRouteBin(UniqueID route,BOStream&file)
{
	int loopcount=0;	//increase for any fixed fields....
	UniqueID wp=route;
	while (wp)
	{
		loopcount++;
		info_waypoint* w=*Persons2::ConvertPtrUID(wp);
		wp=w->nextwp;
	}
	file <<C T_route <<C T_linklist <<C loopcount;
	wp=route;
	while (wp)
	{
		info_waypoint* w=*Persons2::ConvertPtrUID(wp);
		SaveWaypointBin(w,file);
		wp=w->nextwp;
	}
}


void	PackageList::SaveWaypointBin(info_waypoint* wp,BOStream&file)
{	//count more of a problem - some fields optional!
//	T_setUID		 	optional - negative indicates key waypoint
//	T_vel/T_start		optional - default = cruise
//	T_pos				NEED
//	T_target			optional - bombing waypoint
//	T_wpact				optional - default = no action
//	T_rangepc/T_range	NEED
//	T_event				never
//	T_applygroup		optional - ocuur in sequence
//	T_applyflight		optional - ocuur in sequence
//	T_applyelt			optional - ocuur in sequence
//	T_applyac			optional - ocuur in sequence
//
	int loopcount=1;

	if (wp->uid.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	if (wp->vel.Evaluate()!=GOT_UNDEFINED_VAL || wp->etas.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	if (wp->target.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	if (wp->wpact.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	if (wp->range.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;

	if (wp->applywave.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	if (wp->applyelt.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	if (wp->applyflight.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	if (wp->applygroup.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;

//DEADCODE CSB 07/06/00 	int timefields=0;
//DEADCODE CSB 07/06/00 	if (wp->etah.Evaluate()!=GOT_UNDEFINED_VAL)
//DEADCODE CSB 07/06/00 		timefields++;
//DEADCODE CSB 07/06/00 	if (wp->etam.Evaluate()!=GOT_UNDEFINED_VAL)
//DEADCODE CSB 07/06/00 		timefields++;
//DEADCODE CSB 07/06/00 	if (wp->etas.Evaluate()!=GOT_UNDEFINED_VAL)
//DEADCODE CSB 07/06/00 		timefields++;
//DEADCODE CSB 07/06/00 	if (timefields)
//DEADCODE CSB 07/06/00 		loopcount++;

	file <<C T_waypoint <<C T_linklist <<C loopcount;

	if (wp->uid.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_setUID;wp->uid.Save(file,NULL);	}
	if (wp->vel.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_vel;wp->vel.Save(file,NULL);	}
//DEADCODE CSB 07/06/00 	if (timefields)
//DEADCODE CSB 07/06/00 	{
//DEADCODE CSB 07/06/00 		file <<C T_start <<C T_linklist <<C timefields;
//DEADCODE CSB 07/06/00 		if (wp->etah.Evaluate()!=GOT_UNDEFINED_VAL)
//DEADCODE CSB 07/06/00 		{	file <<C T_hours;wp->etah.Save(file,NULL);	}
//DEADCODE CSB 07/06/00 		if (wp->etam.Evaluate()!=GOT_UNDEFINED_VAL)
//DEADCODE CSB 07/06/00 		{	file <<C T_mins;wp->etam.Save(file,NULL);	}
//DEADCODE CSB 07/06/00 		if (wp->etas.Evaluate()!=GOT_UNDEFINED_VAL)
//DEADCODE CSB 07/06/00 		{	file <<C T_secs;wp->etas.Save(file,NULL);	}
//DEADCODE CSB 07/06/00 	}

	if (wp->etas.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_start <<C T_secs;wp->etas.Save(file,NULL);	}
	if (wp->target.Evaluate()!=GOT_UNDEFINED_VAL)
		if (wp->target.value==GOT_UNDEFINED_VAL || wp->target.value>RealAcBAND)
		{	file <<C T_target;wp->target.Save(file,NULL);	}
		else
			INT3;

	file<<C T_pos;wp->position.Save(file,NULL);

	if (wp->wpact.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_wpact;wp->wpact.Save(file,NULL);	}
	if (wp->range.Evaluate()!=GOT_UNDEFINED_VAL)
		if (!wp->rangeispercent)
		{	file <<C T_range;wp->range.Save(file,NULL);	}
		else
		{	file <<C T_rangepc;wp->range.Save(file,NULL);	}

	if (wp->applywave.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_applywave;wp->applywave.Save(file,NULL);	}
	if (wp->applyelt.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_applyelt;wp->applyelt.Save(file,NULL);	}
	if (wp->applyflight.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_applyflight;wp->applyflight.Save(file,NULL);	}
	if (wp->applygroup.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_applygroup;wp->applygroup.Save(file,NULL);	}
}


void	Profile::SaveAirItemBin(Profile::Squad* squad,UniqueID route,BOStream&file)
{
	info_airgrp *a=*Persons2::ConvertPtrUID(squad->instance);
// T_route:		done
// T_inform:	
// T_inwing:
// T_duty:	
// T_form:	
// T_position:
// T_waypoint:	numeric index into current route
//DEADCODE DAW 21/02/00 	file <<C (T_inwing);a->inwing.Save(file,NULL);
	file <<C (T_inform);
	if (squad->status==Profile::PS_COMPLETE)
		Expr::putint(0,file);
	else
		Expr::putint(squad->numacleft,file);
	file <<C (T_duty);Expr::putint(squad->method+(squad->submethod<<PACK_AM_SUBMETHOD_SHIFT),file);
	if (a->position.complex==NULL)
	{
		a->position.MakeRelWorldPos(Node_Data[squad->squadnum].homeairfield);	//RDH 18Sep00
	}
	file <<C (T_pos);a->position.Save(file,NULL);
//DEADCODE JIM 14/01/00 	if (a->form.Evaluate()<SQUAD_FLATV)
//DEADCODE JIM 14/01/00 		a->form=SQUAD_FLATV;
	file <<C (T_form);a->form.Save(file,NULL); 

	int i=0;
	UniqueID wpref=a->wpref;
	if (wpref==UID_NULL)
		wpref=squad->takeoffwp;
	for (UniqueID u=route;u!=NULL;)
	{
		breakif(u==wpref);
		i++;
		u=info_waypointPtr(Persons2::ConvertPtrUID(UniqueID(u)))->nextwp;
	}
	file <<C (T_waypoint);Expr::putint(i,file);

// T_itemA:
//	T_setUID:		NEVER
//	T_nation:		ALWAYS
//	T_shape:		NEVER
//	T_type:			ALWAYS - NOW MEANS SQUADRON
//	T_vel:			NEVER
//	T_UIDband:		NEVER
//	T_move:			NEVER
//	T_skill:		NEVER - from pilot skill!
//	T_morale:		NEVER - from pilot skill!
//	T_character:	NEVER - from pilot skill!
//	T_damage:		NEVER - from pilot skill!
//	T_bombs:		ALWAYS = weap package
//	T_target:		NEVER
//	T_attacker:		NEVER
//	T_leader:		now in airgrp!
//	T_follower:		NEVER
//	T_home:			NEVER
//	T_event:		NEVER
//	T_att:			NEVER
//	T_squadron:		NEVER - oops!
//	T_paintscheme	now used for 'originalformpos'
//New in BoB
//	T_damage - fuel
//	T_applywave - target
//					3 fields
//			attmethod,					//NEED TO SAVE if set
//			attpattern,					//NEED TO SAVE
//			radiosilence,				//NEED TO SAVE

	int total=9;
//DEADCODE CSB 30/05/00 	if (a->attmethod.Evaluate()!=GOT_UNDEFINED_VAL)	total++;
//DEADCODE CSB 30/05/00 	if (a->pattern.Evaluate()!=GOT_UNDEFINED_VAL)	total++;
//DEADCODE CSB 30/05/00 	if (a->radiosilence.Evaluate()!=GOT_UNDEFINED_VAL)	total++;
	if (a->movecode.Evaluate()!=GOT_UNDEFINED_VAL)	total++;
	if (a->target.Evaluate()!=GOT_UNDEFINED_VAL && a->target.Evaluate()!=0)	total++;
	if (a->attitude.complex)						total++;
	//AIRITEM
	file <<C T_itemA <<C T_linklist <<C total;

	if (a->attitude.complex)
	{
		file << C T_att << C T_linklist << C 2;
			file << T_pitch ; a->attitude[2].Save(file,NULL);
			file << T_bearing ; a->attitude[1].Save(file,NULL);
	}

	file <<C (T_paintscheme);
	if (squad->squadnum<SQ_LW_START)
	{
		if (&squadlist[0]==squad)
		{
			UWord bits=squadlist.AcBitsFirstSquad();
			int count=0;
			while (!(bits&7))
			{
				bits>>=3;
				count++;
			}
			Expr::putint(count,file);
		}
		else
		{
			Expr::putint(0,file);
		}
	}
	else
	{
		int offset=0;
		for(int i=0;&squadlist[i]!=squad;i++)
			if (squadlist[i].squadnum==squad->squadnum)
				offset+=4;
		Expr::putint(offset,file);                         
	}

	file<<C(T_bombs);
	if (	(squad->method&Profile::AM_GROUPMASK)==Profile::AM_LWPACKS 
		&&	squad->status<Profile::PS_DETAILRAID
		&&	squad->method!=Profile::AM_RECON		)
		Expr::putint(0,file);
	else
		Expr::putint(1,file);

	file <<C (T_setUID);Expr::putint(PackageList::ReorderNoCheck(squad->instance),file);
	file <<C (T_nation);
	if (squad->method<Profile::AM_LWPACKS)
		Expr::putint(NAT_RAF,file);
	else
		Expr::putint(NAT_LUF,file);
	file <<C (T_type);a->type.Save(file,NULL);
	file <<C (T_bombs);a->bombs.Save(file,NULL);
	file <<C (T_squadron);Expr::putint(squad->diaryentry,file);//RJS 18Feb00
	file <<C (T_applywave);Expr::putint(squad->targetindex,file);
	if(squad->fuelleft < 0)												//CSB 25Aug00
		squad->fuelleft = 0;											//CSB 25Aug00
	file <<C (T_damage);Expr::putint((squad->fuelleft/100000)*QMD_LEVEL+QMD_FUELKILOS,file);


	if (a->target.Evaluate()!=GOT_UNDEFINED_VAL && a->target.Evaluate()!=0)
	{	file <<C (T_target);Expr::putint(PackageList::Reorder(UniqueID(a->target.Evaluate())),file);	}
//DEADCODE CSB 30/05/00 	if (a->attmethod.Evaluate()!=GOT_UNDEFINED_VAL)
//DEADCODE CSB 30/05/00 	{	file <<C (T_attmethod);a->attmethod.Save(file,NULL);	}
//DEADCODE CSB 30/05/00 	if (a->pattern.Evaluate()!=GOT_UNDEFINED_VAL)
//DEADCODE CSB 30/05/00 	{	file <<C (T_pattern);a->pattern.Save(file,NULL);	}
//DEADCODE CSB 30/05/00 	if (a->radiosilence.Evaluate()!=GOT_UNDEFINED_VAL)
//DEADCODE CSB 30/05/00 	{	file <<C (T_radiosilence);a->radiosilence.Save(file,NULL);	}
	if (a->movecode.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C (T_move);a->movecode.Save(file,NULL);	}
}
void EventVal::Save(BOStream& f,char*,int,EnumListNames)
{
	if (complex)
		complex->Save(f,NULL);
	else
		Expr::putint(value,f);

}
void Expr::putint(int i,BOStream& f)
{
	f <<C T_int <<(int) i;
}

void GlobRefExpr::	Save( BOStream& f, char *, int, EnumListNames )
{
	f<<C T_mainprog;
	putint(globrefind,f);
	
}
void UIDExpr::		Save( BOStream& f, char *, int, EnumListNames )
{
	f <<C T_target;
//DeadCode MS 26Sep00 	assert (val.complex);												//CSB 30Jul00
	val.Save(f,NULL);													//MS 26Sep00
}
void RndExpr::		Save( BOStream& f, char *, int, EnumListNames )
{
	assert(!"RndExpr::Save");
}
void SelExpr::		Save( BOStream& f, char *, int, EnumListNames )
{
	assert(!"SelExpr::Save");
}
void ListExpr::	Save( BOStream& f, char *, int, EnumListNames )
{
	f<<C T_list <<C T_linklist <<C (1+maxentries);
	index.Save(f,NULL);
	for (int i=0;i<maxentries;i++)
		entries[i].Save(f,NULL);
}
void ListFormExpr::Save( BOStream& f, char *, int, EnumListNames )
{
	f<<C T_list <<C T_linklist <<C (maxentries);
	for (int i=0;i<maxentries;i++)
		entries[i].Save(f,NULL);
}
void WorldExpr::	Save( BOStream& f, char *, int, EnumListNames )
{
	int loopcount=0;
	if (uniqueID.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	XyzExpr* xyz=(XyzExpr*)delta.complex;
	bool anyxyzset=
		(	xyz
		&& 	(	(xyz->X.Evaluate()!=GOT_UNDEFINED_VAL && xyz->X.Evaluate())
			||	(xyz->Y.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Y.Evaluate())
			||	(xyz->Z.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Z.Evaluate())
		)	);
	if (anyxyzset && deltaisabs)
	{
		if (xyz->X.Evaluate()!=GOT_UNDEFINED_VAL && xyz->X.Evaluate())
			loopcount++;
		if (xyz->Y.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Y.Evaluate())
			loopcount++;
		if (xyz->Z.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Z.Evaluate())
			loopcount++;
	}
	if (rotate.complex || (!deltaisabs && anyxyzset))
		loopcount++;
	f<<C T_pos <<C T_linklist <<C loopcount;

	if (uniqueID.Evaluate()!=GOT_UNDEFINED_VAL)
	{	f<<C T_target;	uniqueID.Save(f,NULL);	}

	if (anyxyzset && deltaisabs)
	{
		if (xyz->X.Evaluate()!=GOT_UNDEFINED_VAL && xyz->X.Evaluate())
		{	f<<C T_x;xyz->X.Save(f,NULL);	}
		if (xyz->Y.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Y.Evaluate())
		{	f<<C T_y;xyz->Y.Save(f,NULL);	}
		if (xyz->Z.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Z.Evaluate())
		{	f<<C T_z;xyz->Z.Save(f,NULL);	}
	}
	if (rotate.complex || (!deltaisabs && anyxyzset))
	{
		loopcount=0;
		RotExpr* r=(RotExpr*)rotate.complex;
		if (!deltaisabs && anyxyzset)
		{
			if (xyz->X.Evaluate()!=GOT_UNDEFINED_VAL && xyz->X.Evaluate())
				loopcount++;
			if (xyz->Y.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Y.Evaluate())
				loopcount++;
			if (xyz->Z.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Z.Evaluate())
				loopcount++;
		}
		if (r)
		{
			if (r->icpt.complex)
				loopcount++;
			if (r->range.Evaluate()!=GOT_UNDEFINED_VAL)
				loopcount++;
			if (r->hdg.Evaluate()!=GOT_UNDEFINED_VAL)
				loopcount++;
			if (r->pitch.Evaluate()!=GOT_UNDEFINED_VAL)
				loopcount++;
		}
		f <<C T_rel <<C T_linklist <<C loopcount;
		if (!deltaisabs && anyxyzset)
		{
			if (xyz->X.Evaluate()!=GOT_UNDEFINED_VAL && xyz->X.Evaluate())
			{	f<<C T_x;xyz->X.Save(f,NULL);	}
			if (xyz->Y.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Y.Evaluate())
			{	f<<C T_y;xyz->Y.Save(f,NULL);	}
			if (xyz->Z.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Z.Evaluate())
			{	f<<C T_z;xyz->Z.Save(f,NULL);	}
		}
		if (r)
		{
			if (r->icpt.complex)
			{	f<<C T_icpt;r->icpt.Save(f,NULL);	}
				loopcount++;
			if (r->range.Evaluate()!=GOT_UNDEFINED_VAL)
				if (r->rangeispercent)
				{	f<<C T_rangepc;r->range.Save(f,NULL);	}
				else
				{	f<<C T_range;r->range.Save(f,NULL);	}
			if (r->hdg.Evaluate()!=GOT_UNDEFINED_VAL)
			{	f<<C T_hdg;r->hdg.Save(f,NULL);	}
			if (r->pitch.Evaluate()!=GOT_UNDEFINED_VAL)
			{	f<<C T_pitch;r->pitch.Save(f,NULL);	}
		}
	}
}
void XyzExpr::		Save( BOStream& f, char *, int, EnumListNames ){}
void RotExpr::		Save( BOStream& f, char *, int, EnumListNames ){}
void IcptExpr::	Save( BOStream& f, char *, int, EnumListNames )
{
	f<<C T_linklist <<C 2;
	objA.Save(f,NULL);
	objB.Save(f,NULL);
}
void UIDExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
void WorldExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
void XyzExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
void GlobRefExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)	{}
void RndExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
void SelExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
void ListExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
void ListFormExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)	{}
void RotExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
void IcptExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
