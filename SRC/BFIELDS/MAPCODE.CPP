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

//
// Battlefield code to do with mig alley map screen
// Sort of global stuff I can't hide anywhere else.
//
//
//
#include	"dosdefs.h"	
#define		F_COMMON  
//DEADCODE JIM 09/02/00 #include	"text.h"
#include	"uniqueID.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include	"world.h"
//DEADCODE DAW 03/02/00 #include	"NODE.H"
#include	"fileman.h"
#include "savegame.h"
#include	"missman2.h"
#include	"mytime.h"
#include	"sky.h"
#include	"bstream.h"
#include	"CString.h"
#include	"Nodebob.h"
#include <stdarg.h>
#include "replay.h"
#include "monotxt.h"

///////////////////////////////////////////////
ItemBasePtr	WorldStuff::pItem[WorldStuff::PITEMTABLESIZE];
ItemBasePtr WorldStuff::pMapItemHead;
///////////////////////////////////////////////
extern CString		CSprintf(const char* format,...);
inline	CString	LoadResString(int resnum)
{
	CString s;
	s.LoadString(resnum);
	return s;
};


//////////////////////////////////////////////////////////////////////
//
// Function:    StartUpMapWorld
// Date:		22/10/00
// Author:		JIM
//
//Description: MUST NOT CALL  BuildTargetTable FROM HERE AS IT SCREWS CONVOYS!!!
//
//////////////////////////////////////////////////////////////////////
void	Persons4::StartUpMapWorld(bool loadpackages, char* name)
{		//do whenever we go to the map screen
//DeadCode CSB 3Oct00 	Mono_Text.Print((UByteP)"StartUpMapWorld(");
	pItem=WorldStuff::pItem;
	{	for (int i=0;i<PITEMTABLESIZE;i++)
		{	delete(pItem[i]);
			pItem[i]=NULL;
		}
	}
	{
		Persons4	Persons_4;
		Persons_4.InitTables();
		Persons_4.LoadSubPiece(NULL,FIL_1_MAINWLD,0,LOAD); //RJS 16/11/99
//TEMPCODE RJS 16/11/99 		Persons_4.LoadSubPiece(NULL,FIL_1_convoy,0,LOAD);
	}
//DeadCode CSB 3Oct00 	Mono_Text.Print((UByteP)"1");
//DeadCode CSB 3Oct00 	Mono_Text.Print((UByteP)"2");
	Node_Data.LoadConvoys();
//DeadCode CSB 3Oct00 	Mono_Text.Print((UByteP)"3");

//DEADCODE JIM 16/11/99 	for (int front=0;front<3;front++)		//JIM EDIT HERE		//JIM 18Feb99
//DEADCODE JIM 16/11/99 //DeadCode DAW 27Jun99 		if (SupplyTree::supplylines[front]->frontline->status==FRONTLINE)
//DEADCODE JIM 16/11/99 		{
//DEADCODE JIM 16/11/99 			FileNum	bf=FIL_NULL;
//DEADCODE JIM 16/11/99 			FileNum	bn=FIL_NULL;
//DEADCODE JIM 16/11/99 			if (	SupplyTree::supplylines[front]->initiative==REDATTACKING
//DEADCODE JIM 16/11/99 				||	SupplyTree::supplylines[front]->initiative==REDINITIATIVE
//DEADCODE JIM 16/11/99 				)
//DEADCODE JIM 16/11/99 			{
//DEADCODE JIM 16/11/99 				bf=SupplyTree::supplylines[front]->frontline->bluefrontBF->bf;
//DEADCODE JIM 16/11/99 				bn=SupplyTree::supplylines[front]->frontline->bluefrontBF->nodetree;
//DEADCODE JIM 16/11/99 			}
//DEADCODE JIM 16/11/99 			else
//DEADCODE JIM 16/11/99 			if (SupplyTree::supplylines[front]->initiative==BLUEATTACKING
//DEADCODE JIM 16/11/99 				||	SupplyTree::supplylines[front]->initiative==BLUEINITIATIVE
//DEADCODE JIM 16/11/99 				)
//DEADCODE JIM 16/11/99 			{
//DEADCODE JIM 16/11/99 				bf=SupplyTree::supplylines[front]->frontline->redfrontBF->bf;
//DEADCODE JIM 16/11/99 				bn=SupplyTree::supplylines[front]->frontline->redfrontBF->nodetree;
//DEADCODE JIM 16/11/99 			}
//DEADCODE JIM 16/11/99 			if (bf)
//DEADCODE JIM 16/11/99 			{
//DEADCODE JIM 16/11/99 				Persons4	Persons_4;
//DEADCODE JIM 16/11/99 				Persons_4.LoadSubPiece(NULL,bf,front+1,LOAD);
//DEADCODE JIM 16/11/99 				SupplyTree::supplylines[front]->groundbattle.LoadBattleNodes(bn);
//DEADCODE JIM 16/11/99 				SupplyTree::supplylines[front]->groundbattle.LinkBattleNodes();
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 #ifndef NDEBUG
//DEADCODE JIM 16/11/99 				CString missingnodes="";
//DEADCODE JIM 16/11/99 				for(int node=0;node<SupplyTree::supplylines[front]->groundbattle.usednodes;node++)
//DEADCODE JIM 16/11/99 				{
//DEADCODE JIM 16/11/99 					SuperBattleNode* bn=&SupplyTree::supplylines[front]->groundbattle.nodelist[node];	
//DEADCODE JIM 16/11/99 					CString onenode="";
//DEADCODE JIM 16/11/99 					if (bn->in.uid && Persons2::ConvertPtrUID(bn->in.uid)==NULL)
//DEADCODE JIM 16/11/99 						onenode+=CSprintf(" I:%04x",bn->in.uid);
//DEADCODE JIM 16/11/99 					if (bn->out.uid && Persons2::ConvertPtrUID(bn->out.uid)==NULL)
//DEADCODE JIM 16/11/99 						onenode+=CSprintf(" O:%04x",bn->out.uid);
//DEADCODE JIM 16/11/99 					if (bn->mainuid && Persons2::ConvertPtrUID(bn->mainuid)==NULL)
//DEADCODE JIM 16/11/99 						onenode+=CSprintf(" M:%04x",bn->mainuid);
//DEADCODE JIM 16/11/99 					if (onenode!="")
//DEADCODE JIM 16/11/99 						missingnodes+=LoadResString(bn->mainids)+onenode+"\n";
//DEADCODE JIM 16/11/99 				}
//DEADCODE JIM 16/11/99 				if (missingnodes!="")
//DEADCODE JIM 16/11/99 					_Error.EmitSysErr(CString("The following nodes are not in the file %s:\n")+missingnodes,File_Man.namenumberedfile(bf));
//DEADCODE JIM 16/11/99 #endif
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 			}
//DEADCODE JIM 16/11/99 		}			   //END OF JIM EDIT
	if(loadpackages)
	{
		char buffer[fileman::pathnamesize];
		if (name && !_Replay.MapPlayback)
		{
			BIStream bis(File_Man.namenumberedfile(
				File_Man.fakefile(FIL_SAVEGAMEDIR,name),buffer));
			if (bis.is_open())
				Todays_Packages.LoadGame(bis);
		}
		else
		{
			BIStream bis(File_Man.namenumberedfile(
				File_Man.fakefile(FIL_SAVEGAMEDIR,"Package.dat"),buffer));
			if (bis.is_open())
				Todays_Packages.LoadGame(bis);
		}
//DeadCode CSB 3Oct00 	Mono_Text.Print((UByteP)"4");
		Persons3::RestoreAircraftPositions();
	}
//DEADCODE DAW 27/03/00 	for (int i=0,f=0;i<Profile::MAX_PACKS;i++)
//DEADCODE DAW 27/03/00 	{
//DEADCODE DAW 27/03/00 		if (Todays_Packages.PreLoad(i))
//DEADCODE DAW 27/03/00 		{
//DEADCODE DAW 27/03/00 			Todays_Packages.PreLoad(i,FIL_RUNTIMEPACK0,NULL,true,true,f);
//DEADCODE DAW 27/03/00 			Todays_Packages.Load(i,FIL_RUNTIMEPACK0,NULL,f);
//DEADCODE DAW 27/03/00 			f++;
//DEADCODE DAW 27/03/00 		}
//DEADCODE DAW 27/03/00 	}
//	Miss_Man.currcampaignnum = MissMan::SCRAMBLECAMPAIGN;		//RDH 16Apr96
//	Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];

//	SupplyTree::NodeReview ();
//init and test code
//	MMC.currtime = HR11;
	
//	MMC.Sky.SetMissionConditions ();
//DeadCode CSB 3Oct00 	Mono_Text.Print((UByteP)")StartUpMapWorld");

}

void	NodeData::LoadConvoys()
{
	const int	daynum=(MMC.currdate-JUL10th1940)/SECSPERDAY;
	int	bfnum=0;
	for (TargetConvoy* convoy=convoylist;convoy->uid;convoy++)
	{
		int dateslot=0;
		if (convoy->keydates[0]!=daynum)
			for (dateslot=1;convoy->keydates[dateslot];dateslot++)
				breakif(convoy->keydates[dateslot]==daynum);
		if (	convoy->keydates[dateslot]==daynum 
			&&	(dateslot==0 || daynum!=0)	)
			{
				Persons4	Persons_4;
				if (convoy->wpnum!=-1)
				{
					GR_ItemInfoOverride=convoy->uid;
					GR_ItemWpOverride=convoy->wpnum;
					GR_ItemXOverride=convoy->X;
					GR_ItemZOverride=convoy->Z;
				}
				else
				{
					GR_ItemInfoOverride=UID_NULL;
				}
				Persons_4.LoadSubPiece(NULL,convoy->detailbattlefield,bfnum++,Persons4::LOAD);
				info_itemSPtr pi=Persons2::ConvertPtrUID(convoy->uid);
				if (convoy->wpnum==-1)
				{
					pi->position.EvalW(pi->World);
					convoy->wpnum=0;
				}
				else
				{
					pi->World.X=convoy->X;
					pi->World.Y=0;
					pi->World.Z=convoy->Z;


				}

			}
		else
			convoy->wpnum=-1;
	}
	assert(bfnum<=Persons2::RELOADABLEBOUNDARY," Too many convoys loaded today");
}

void	Persons4::ShutDownMapWorld()
{		//do whenever we come off the map screen
	if (pItem)
		for (int i=0;i<PITEMTABLESIZE;i++)
			if (pItem[i])
			{
				delete pItem[i];
				pItem[i]=NULL;
			}
	pItem=WorldStuff::pItem;
}


//DeadCode JIM 29Oct00 bool	PackageList::PreLoad(int packnum,FileNum fil,const char* name,bool copyprimary,bool copysecondaries,int filecount)
//DeadCode JIM 29Oct00 {	//need to pre-read package header..
//DeadCode JIM 29Oct00 	if (fil || copyprimary || copysecondaries)
//DeadCode JIM 29Oct00 	{
//DeadCode JIM 29Oct00 		if (!fil)
//DeadCode JIM 29Oct00 			fil=FileNum(FIL_RUNTIMEPACK0+packnum);
//DeadCode JIM 29Oct00 		if (name)
//DeadCode JIM 29Oct00 			fil = File_Man.fakefile(fil,name);
//DeadCode JIM 29Oct00 		fil=FileNum(fil+filecount);
//DeadCode JIM 29Oct00 		fileblock f(fil);
//DeadCode JIM 29Oct00 		pack[packnum].DecodePackage((string)f.getdata(),copyprimary);
//DeadCode JIM 29Oct00 		return true;
//DeadCode JIM 29Oct00 	}
//DeadCode JIM 29Oct00 	else
//DeadCode JIM 29Oct00 		return (pack[packnum].packagestatus!=Profile::PS_SPARE);
//DeadCode JIM 29Oct00 }
//DeadCode JIM 17Aug00 void	PackageList::Load(int packnum,FileNum fil,const char* name,int filecount)
//DeadCode JIM 17Aug00 {
//DeadCode JIM 17Aug00 		Persons4	Persons_4;
//DeadCode JIM 17Aug00 		if (!fil)
//DeadCode JIM 17Aug00 			fil=FileNum(FIL_RUNTIMEPACK0+packnum);
//DeadCode JIM 17Aug00 		if (name)
//DeadCode JIM 17Aug00 			fil = File_Man.fakefile(fil,name);
//DeadCode JIM 17Aug00 		fil=FileNum(fil+filecount);
//DeadCode JIM 17Aug00 
//DeadCode JIM 17Aug00 		pack[packnum].SetTargetUIDs();
//DeadCode JIM 17Aug00 		Persons_4.LoadSubPiece(NULL,fil,Persons4::LOADEDBFS+packnum,Persons4::LOAD);
//DeadCode JIM 17Aug00 		FixupAircraft(packnum);
//DeadCode JIM 17Aug00 		pack[packnum].CountWaypoints();
//DeadCode JIM 17Aug00 }

//DEADCODE JIM 31/03/00 void Profile::SetACTypesFromGeneric()
//DEADCODE JIM 31/03/00 {
//DEADCODE JIM 31/03/00 
//DEADCODE JIM 31/03/00 }


void	PackageList::SaveGame(BOStream& bos)
{
	BuildReorderTable();
	bos<<germanisauto<<britishisauto;
	bos<<(ULong&)localplayer;
	bos<<nextraidnum<<nextsortienum;
 	bos<<oldhipack<<hipack<<oldhisquad<<hisquad;
	bos<<(ULong&)hiwp;

	for (int packs=0;packs<Profile::MAX_PACKS;packs++)
			SaveBin(&pack[packs],bos);
}

void	PackageList::FixupAircraft(int packnum)
{
//DeadCode JIM 20Oct00 		int wave=-1;
		int group;
		int i;
//DeadCode JIM 20Oct00 		UniqueID	baseac=Persons2::assignuid(SagBAND);

		//NOTE: 
			//Coming back from the 3d, the information represented here
			//is not up to date.
			//We need to have recorded the new position, waypoint and strength
			//of each aircraft.
			//This note is repeated in Persons4.cpp


//DeadCode JIM 17Aug00 		UniqueID wpu=UniqueID(GR_lastroutefirstwaypoint);
//DeadCode JIM 17Aug00 		pack[packnum].route=wpu;
	//fix up references to waypoints:
	UniqueID u=pack[packnum].route;
	if (Persons2::ConvertPtrUID(u))
	while (u)
	{
		info_waypoint*	w=Persons2::ConvertPtrUID(u);
		if (	w->target.complex
			&&	w->target.complex->UsesGlobRef()
			&&	w->target.complex->UsesGlobRef()>=SGR_Pack_Target
			&&	w->target.complex->UsesGlobRef()<=SGR_Pack_Target9
			)
			pack[packnum].packagetarget[w->target.complex->UsesGlobRef()-SGR_Pack_Target].targetwaypoint=u;
		else
			if (w->applygroup.Evaluate()!=ENABLE_COMPLEX_VAL)
			{
				if (w->wpact.Evaluate()==wpatakeoffno)
					pack[packnum].squadlist[w->applygroup.Evaluate()].takeoffwp=u;
				else
				if (w->wpact.Evaluate()==wpalandingno)
					pack[packnum].squadlist[w->applygroup.Evaluate()].landingwp=u;
			}
		u=w->nextwp;

	}
	//fix up references to packs:
	{for (int i=0,m=pack[packnum].squadlist;i<m;i++)
	{
		info_airgrpPtr a=Persons2::ConvertPtrUID(pack[packnum].squadlist[i].instance);
		a->knownposition=a->World;
		a->knowntime=a->lasttime=MMC.currtime;
		assert(a," Just loaded. What's going on?");
		a->package=&pack[packnum];
		if (a->wpref)
		{
			info_waypointPtr w=Persons2::ConvertPtrUID(a->wpref);
			if (w->applygroup!=ENABLE_COMPLEX_VAL)
			{
//DeadCode MS 26Sep00 				assert(	w->target.Evaluate()==J->homebase.Evaluate());
				if(	w->target.Evaluate()!=pack[packnum].squadlist[i].Squadron().homeairfield)
					INT3;
			}
		}

	}}
		pack[packnum].RecalcRoutePositions();
}

void	PackageList::LoadGame(BIStream& bis)
{
	bis>>germanisauto>>britishisauto;
	bis>>(ULong&)localplayer;
	bis>>nextraidnum>>nextsortienum;
 	bis>>oldhipack>>hipack>>oldhisquad>>hisquad;
	bis>>(ULong&)hiwp;
	for (int p=0;p<Profile::MAX_PACKS;p++)
		ClearPack(p);
//DEADCODE JIM 20/06/00 	oldhipack = hipack=oldhisquad=hisquad=0;//wave=higroup=0;								  //DAW 24/11/99
//DEADCODE JIM 20/06/00 	hiwp=UID_NULL;

	enum	{SIZ=32*1024,SIZ2=2*SIZ};
	char* buffer=new char[SIZ2];										//JIM 31/05/00
	bis.read(buffer,SIZ2);
	int fsize=bis.gcount();
	bool	fend=(fsize<SIZ2);
	char* ind=buffer;
	char* last=buffer+fsize;
	int packnum=0;
	Persons4	Persons_4;
	while (ind<last)
	{	assert (packnum<Profile::MAX_PACKS);
		pack[packnum].DecodePackage(ind,true);
		while (*ind++)	
		{}
		if (ind>buffer+SIZ && !fend)	   //more than half way through
		{
			int copysize=SIZ2-(ind-buffer);
			memcpy(buffer,ind,copysize);   //not overlapping!			//JIM 19/06/00
			bis.read(buffer+copysize,SIZ2-copysize);
			fsize=bis.gcount();
			fend=(fsize!=SIZ2-copysize);
			last=buffer+copysize+fsize;
			ind=buffer;
		}

		pack[packnum].SetTargetUIDs();
		if (pack[packnum].wpsused)
		{	char* bupind=ind;
			ind=bupind;
			Persons_4.LoadSubPiece(NULL,ind,Persons4::LOADEDBFS+packnum,Persons4::LOAD);
			UniqueID wpu=UniqueID(GR_lastroutefirstwaypoint);
			pack[packnum].route=wpu;
			pack[packnum].CountWaypoints();
		}
		packnum++;
		if (ind>buffer+SIZ && !fend)	   //more than half way through
		{
			int copysize=SIZ2-(ind-buffer);
			memcpy(buffer,ind,copysize);   //not overlapping!			//JIM 19/06/00
			bis.read(buffer+copysize,SIZ2-copysize);
			fsize=bis.gcount();
			fend=(fsize!=SIZ2-copysize);
			last=buffer+copysize+fsize;
			ind=buffer;
		}

	}
	for (packnum=0;packnum<Profile::MAX_PACKS;packnum++)
		if (pack[packnum].wpsused)
			FixupAircraft(packnum);
	Todays_Packages.SetVisibilityFlags();
	delete buffer;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitViewFromMap
//Author		Paul.   
//Date			Thu 11 Mar 1999
//------------------------------------------------------------------------------
static FileNum	targetdetail1,targetdetail2;
void Persons4::InitViewFromMap(UniqueID trg_uid)
{
	WorldStuff::pMapItemHead=NULL;

	if (pItem)
		for (int i=0;i<PITEMTABLESIZE;i++)
			if (pItem[i]!=NULL && pItem[i]->uniqueID.count==trg_uid)
				WorldStuff::pMapItemHead=pItem[i];
	targetdetail1=Node_Data.CheckTargetLoaded( trg_uid,false);
	targetdetail2=Node_Data.CheckTargetLoaded( trg_uid,true);
	if (WorldStuff::pMapItemHead)
	{
		((itemptr)WorldStuff::pMapItemHead)->Next=NULL;
		SLong ix=WorldStuff::pMapItemHead->World.X,
				iz=WorldStuff::pMapItemHead->World.Z;

		//find all other items in a 10km radius
		for (int i=0;i<PITEMTABLESIZE;i++)
		{
			SLong d;
			if (pItem[i]!=NULL && i!=trg_uid &&
				pItem[i]->Status.size!=WAYPOINTSIZE &&
				(d=Math_Lib.Distance2d(pItem[i]->World.X-ix,pItem[i]->World.Z-iz))<1000000)
			{
				((itemptr)pItem[i])->Next=((itemptr)WorldStuff::pMapItemHead)->Next;
				((itemptr)WorldStuff::pMapItemHead)->Next=(itemptr)pItem[i];
			}
		}
	}
	//pMapItemHead now points to a linked list of items within a 10km range
	//of the selected target. The head of the list is the selected item.

	pItem=WorldStuff::pItem;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShutDownViewFromMap
//Author		Paul.   
//Date			Fri 12 Mar 1999
//------------------------------------------------------------------------------
void Persons4::ShutDownViewFromMap()
{
	itemptr ip=itemptr(WorldStuff::pMapItemHead);
	while (ip)
	{
		itemptr np=ip->Next;
		ip->World.Y=0;
		ip->Next=(itemptr)-1;
		ip=np;
	}
	if (targetdetail1)
		DeleteBFItems(targetdetail1);
	if (targetdetail2)
		DeleteBFItems(targetdetail2);
	targetdetail1= targetdetail2 = FIL_NULL;
}
