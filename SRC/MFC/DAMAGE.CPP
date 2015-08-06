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

// RowanDialog: // Damage.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Damage.h"
#include "savegame.h"
#include "animdata.h"
#include	"worldinc.h"
#include	"bfnumber.h"
#include "persons2.h"

#include	"bstream.h"
#include	"savegame.h"
#include	"groupitt.h"
#include	"shpinstr.h"										//RJS 15Feb99
#include	"3dcom.h"											//RJS 15Feb99
#include	"shapes.h"
#include	"replay.h"
#include "rchatter.h"
#include "globrefs.h"
#include "ai.h"
#include "planetyp.h"

//hole... no item   void		MaxKillTime(ITEM_STATUS&);	//highest value for howlongdead.



#ifdef _DEBUG
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif


/////////////////////////////////////////////////////////////////////////////
// CDamage dialog


CDamage::CDamage(int sgt,int uid,CWnd* pParent /*=NULL*/)
	: RowanDialog(CDamage::IDD, pParent)
{
	//{{AFX_DATA_INIT
//	info_base* i=*Persons2::ConvertPtrUID(UniqueID(uid));
//	if (i->SGT)
//	{
		specificelt=UniqueID(uid);
//		uid=i->SGT;
//	}
	//}}AFX_DATA_INIT
	SetProjSpecific(-1,sgt,uid);  
	Node_Data.CheckTargetLoaded(UniqueID(sgt));
	damagedelements=new DamageDef[100];
	numdamagedelts=Dead_Stream.DecodeDamage(UniqueID(sgt),damagedelements);
}

CDamage::~CDamage()
{
	delete [] damagedelements;
}


void CDamage::DoDataExchange(CDataExchange* pDX)
{
	char*	fractionformat=":    %i/%i";
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDamage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_LIST_ELEMENTS,m_IDC_LIST_ELEMENTS);
	DDX_Control(pDX,IDC_COMBO_ELEMENTS,m_IDC_COMBO_ELEMENTS);
	//}}AFX_DATA_MAP
	int	line=0;
	int	selline=-1;
	internalUIDmax=0;
	CString	displayline;
	{														  //RDH 28/04/99
		info_itemS* p = *Persons2::SlowConvertPtrUID(UniqueID(wavenum));
		if (p->Status.size>=MOBILESIZE)
		{
			CString  str = GetShapeName(ShapeNum(p->shape.Evaluate()));
			if (str.IsEmpty() || str[0]=='_')
				str=GetTargName(UniqueID(wavenum));
			if (str.IsEmpty() || str[0]==0)
				str=RESSTRING(ASSET);
			displayline=str;//l->AddString(str,0);
			int damagelevel=Node_Data[UniqueID(wavenum)].truestatus;
			int	members=(info_grndgrpPtr(*p)->inform);
			if (damagelevel>100)
				damagelevel=100;
			damagelevel=damagelevel*(members+6)*(members+6)/100;
			int deadmembers=6;
			for (;deadmembers*deadmembers<damagelevel;deadmembers++)
			{}
			displayline=RESSTRING(DAMAGED)+CSprintf(fractionformat,deadmembers-6,members);
		}
		else
		{
			{
			CString  str = GetShapeName(ShapeNum(p->shape.Evaluate()));
			if (str.IsEmpty() || str[0]=='_')
				str=GetTargName(UniqueID(wavenum));
			displayline=str;//l->AddString(str,0);
			}
			if (damagedelements[0].loadedid==wavenum)
			{
				DeadStream::DeadBlockItterator itt(Dead_Stream.firstblock,UID_NULL);
				itt.SkipToItem(UniqueID(wavenum));
				int damagedeltc=0,totaleltc=0,damagedpoints=0;
				for (GroupItterator si(damagedelements[0].shape,&itt);si;si++)
					if (si.AnimDataMAD().itemstate>0)
					{
						if (si.DamageWeight()>IGNOREDAMAGEBELOWTHIS)
						{
							damagedeltc++;
							totaleltc++;
						}
						damagedpoints+=si.AnimDataMAD().itemstate*si.DamageWeight();
					}
					else
						if (si.DamageWeight()>IGNOREDAMAGEBELOWTHIS)
							totaleltc++;
				displayline+=CSprintf(fractionformat,damagedeltc,totaleltc);
			}
			else
			{
				int totaleltc=0;

				info_itemS* p = *Persons2::SlowConvertPtrUID(UniqueID(wavenum));
				if (p)
					for (GroupItterator si(ShapeNum(p->shape.Evaluate()));si;si++)
						if (si.DamageWeight()>IGNOREDAMAGEBELOWTHIS)
							totaleltc++;
				displayline+=CSprintf(fractionformat,0,totaleltc);

		//DEADCODE DAW 02/02/00 		l->AddString(RESSTRING(FULLY_F),1);
		//DEADCODE DAW 02/02/00 		l->AddString(RESSTRING(F_FUNCTIONAL),2);
			}
		}
	}
	internalUIDList[internalUIDmax++]=UniqueID(wavenum);
	GETDLGITEM(IDC_COMBO_ELEMENTS)->AddString(displayline);
	if (groupnum==UID_NULL || groupnum==wavenum)
		selline=line;
	line++;
	info_itemS*	p;
	UniqueIDBand band;
	for (int i=CivilianBAND;i<WorldStuff::PITEMTABLESIZE;i++)
		if (	((p=Persons2::ConvertPtrUID(UniqueID(i)))!=NULL)
			&&	(p->SGT==wavenum && p->shape.Evaluate()!=EMPTY && p->shape.Evaluate()!=EMPTY2 &&p->Status.size<MOBILESIZE)
			&&	(band=Persons2::getbandfromUID(UniqueID(i)))!=0
			&&	band!=LandscapeBAND
			)
		{
			displayline=GetShapeName(ShapeNum(p->shape.Evaluate()))+" "+GetRelativeName(p->SGT,&p->World);
			int de=numdamagedelts;
			while(de-->0)
				breakif (damagedelements[de].loadedid==i);
			if (de>=0)
			{
				UniqueID startpoint=UID_NULL;
				UniqueID findpoint=(UniqueID)wavenum;
//DEADCODE JIM 07/06/99 							if (wavenum!=groupnum)
				{
					if (!DeadStream::MainWorldBand(UniqueID(i)))
						startpoint=findpoint;
					findpoint=damagedelements[de].memberid;
				}
				DeadStream::DeadBlockItterator itt(Dead_Stream.firstblock,startpoint);
				itt.SkipToItem(findpoint);

				int damagedeltc=0,totaleltc=0,damagedpoints=0;
				for (GroupItterator si(damagedelements[de].shape,&itt);si;si++)
					if (si.AnimDataMAD().itemstate>0)
					{
						if (si.DamageWeight()>IGNOREDAMAGEBELOWTHIS)
						{
							damagedeltc++;
							totaleltc++;
						}
						damagedpoints+=si.AnimDataMAD().itemstate*si.DamageWeight();
					}
					else
						if (si.DamageWeight()>IGNOREDAMAGEBELOWTHIS)
							totaleltc++;
				displayline+=CSprintf(fractionformat,damagedeltc,totaleltc);
			}
			else
			{
				int	totaleltc=0;
				info_itemS* p = *Persons2::SlowConvertPtrUID(UniqueID(i));
				if (p)
					for (GroupItterator si(ShapeNum(p->shape.Evaluate()));si;si++)
						if (si.DamageWeight()>IGNOREDAMAGEBELOWTHIS)
							totaleltc++;
				displayline+=CSprintf(fractionformat,0,totaleltc);


			}
			internalUIDList[internalUIDmax++]=UniqueID(i);
			GETDLGITEM(IDC_COMBO_ELEMENTS)->AddString(displayline);
			if (groupnum==i)
				selline=line;
			line++;
		}
 	GETDLGITEM(IDC_COMBO_ELEMENTS)->SetIndex(selline);
	FillList();

}





void	CDamage::FillList()
{
//DeadCode JIM 20Oct00 	int setindex=-1;
//DeadCode JIM 20Oct00 	int listlen=0;
	CRListBox*	l=GETDLGITEM(IDC_LIST_ELEMENTS);
	l->Clear();
	//Find damage info for group
	int de=numdamagedelts;
	while(de-->0)
		breakif (damagedelements[de].loadedid==groupnum);

	if (de>=0)
	{
		int specificeltdamage=de;
		UniqueID startpoint=UID_NULL;
		UniqueID findpoint=(UniqueID)wavenum;
		if (wavenum!=groupnum)
		{
			if (!DeadStream::MainWorldBand(UniqueID(groupnum)))
				startpoint=findpoint;
			findpoint=damagedelements[specificeltdamage].memberid;
		}
		DeadStream::DeadBlockItterator itt(Dead_Stream.firstblock,startpoint);
		itt.SkipToItem(findpoint);
		//list elements
		l->AddColumn(TARGETFIELDWIDTH+50);
		l->AddColumn(50);
		for (GroupItterator si(damagedelements[specificeltdamage].shape,&itt);si;si++)
		{
			if (si.DamageWeight()>IGNOREDAMAGEBELOWTHIS && si.shape!=CTRPTC && si.shape!=CRKPTC)
			{
				l->AddString(GetShapeName(si.shape)+" "+GetEltDeltaName(si.delta),0);
				l->AddString(RESLIST(DAMAGESTAT_ALIVE,((MinAnimData&)si.AnimDataByte()).itemstate),1);
			}
		}
	}
	else
	{
		l->AddColumn(TARGETFIELDWIDTH+100);
		info_itemS* p = *Persons2::SlowConvertPtrUID(UniqueID(groupnum));
		if (p)
			if (p->Status.size>=MOBILESIZE)
			{
				EventVal& type=p->shape;
				int max=(info_grndgrpPtr(*p)->inform);
				for (int i=0;i<max;i++)
					l->AddString(GetShapeName(ShapeNum(type.Evaluate(i))),0);
			}
			else
				for (GroupItterator si(ShapeNum(p->shape.Evaluate()));si;si++)
				{
					if (si.DamageWeight()>IGNOREDAMAGEBELOWTHIS && si.shape!=CTRPTC && si.shape!=CRKPTC)
					{
						l->AddString(GetShapeName(si.shape)+" "+GetEltDeltaName(si.delta),0);
					}
				}

	}
}


BEGIN_MESSAGE_MAP(CDamage, CDialog)
	//{{AFX_MSG_MAP(CDamage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CDamage, CDialog)
    //{{AFX_EVENTSINK_MAP(CDamage)
	ON_EVENT(CDamage, IDC_COMBO_ELEMENTS, 1 /* TextChanged */, OnTextChangedComboElements, VTS_BSTR VTS_I2)
//DEADCODE DAW 02/02/00 	ON_EVENT(CDamage, IDC_LIST_ELEMENTS, 1 /* Select */, OnSelectListElements, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDamage::OnTextChangedComboElements(LPCTSTR text, short index) 
{
	// TODO: Add your control notification handler code here
  	CRCombo* combo;
	combo=GETDLGITEM(IDC_COMBO_ELEMENTS);
	int comboindex = combo->GetIndex();	
//DEADCODE RDH 16/05/00 	if (comboindex==0)
		groupnum=internalUIDList[comboindex];
//DEADCODE RDH 16/05/00 	else
//DEADCODE RDH 16/05/00 	{
//DEADCODE RDH 16/05/00 		internalUIDList
//DEADCODE RDH 16/05/00 		info_itemS*	p;
//DEADCODE RDH 16/05/00 		UniqueIDBand band;
//DEADCODE RDH 16/05/00 		for (int i=BritAAASiteBAND;i<WorldStuff::PITEMTABLESIZE;i++)
//DEADCODE RDH 16/05/00 			if (	((p=Persons2::ConvertPtrUID(UniqueID(i)))!=NULL)
//DEADCODE RDH 16/05/00 				&&	(p->SGT==wavenum && p->shape.Evaluate()!=EMPTY)
//DEADCODE RDH 16/05/00 				&&	(band=Persons2::getbandfromUID(UniqueID(i)))!=0
//DEADCODE RDH 16/05/00 				&&	band!=LandscapeBAND
//DEADCODE RDH 16/05/00 				)
//DEADCODE RDH 16/05/00 				if (--comboindex==0)
//DEADCODE RDH 16/05/00 					groupnum=i;
//DEADCODE RDH 16/05/00 	}
	m_pView->m_mapdlg.ResetIcon(UniqueID(groupnum));
	FillList();
}

void CDamage::OnSelectListElements(long row, long column) 
{
//DEADCODE DAW 02/02/00 	// TODO: Add your control notification handler code here
//DEADCODE DAW 02/02/00 
//DEADCODE DAW 02/02/00 //	m_pView->m_mapdlg.ResetIcon(damagedelements[row-1].loadedid);
//DEADCODE DAW 02/02/00 	row--;
//DEADCODE DAW 02/02/00 	UniqueID rv=UID_NULL;
//DEADCODE DAW 02/02/00 	if (mode==M_ALL)
//DEADCODE DAW 02/02/00 	{
//DEADCODE DAW 02/02/00 		if (row==0)
//DEADCODE DAW 02/02/00 			rv=UniqueID(wavenum);
//DEADCODE DAW 02/02/00 		else
//DEADCODE DAW 02/02/00 		{
//DEADCODE DAW 02/02/00 			info_itemS*	p;
//DEADCODE DAW 02/02/00 			for (int i=0;i<WorldStuff::PITEMTABLESIZE;i++)
//DEADCODE DAW 02/02/00 				if ((p=*Persons2::ConvertPtrUID(UniqueID(i)))!=NULL)
//DEADCODE DAW 02/02/00 					if (p->SGT==wavenum && p->shape.Evaluate()!=EMPTY) //DAW 07/06/99
//DEADCODE DAW 02/02/00 						if (!--row)
//DEADCODE DAW 02/02/00 							rv=UniqueID(i);
//DEADCODE DAW 02/02/00 		}
//DEADCODE DAW 02/02/00 	}
//DEADCODE DAW 02/02/00 	else
//DEADCODE DAW 02/02/00 	if (mode==M_DAMAGED)
//DEADCODE DAW 02/02/00 	{
//DEADCODE DAW 02/02/00 		if (numdamagedelts)
//DEADCODE DAW 02/02/00 			rv=damagedelements[row].loadedid;
//DEADCODE DAW 02/02/00 	}
//DEADCODE DAW 02/02/00 	if (rv)
//DEADCODE DAW 02/02/00 		m_pView->m_mapdlg.ResetIcon(rv);
}

/////////////////////////////////////////////////////
////
////
//// OTHER damage related stuff.
////
////
/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//
// Function:    EnoughDamage3D
// Date:		08/06/99
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool	FormationItem::EnoughDamage3D(ItemPtr currtarget)
{
//DEADCODE JIM 22/03/00 	if ((duty&DUTYMASK)==DC_WW)
//DEADCODE JIM 22/03/00 		return (currtarget->Status.deadtime!=0);
//DEADCODE JIM 22/03/00 	else
	if (!currtarget)
		return	true;
	else
	if (currtarget->Status.size>=FORMATIONSIZE)
	{
		FormationItemPtr curr=*currtarget;
		if (curr->Status.deadtime && !curr->leader)
			return false;
		else
			return true;
	}
	else
	{
		UniqueID SGT=currtarget->SGT;
		if (SGT==UID_NULL)
			SGT=currtarget->uniqueID.count;
		ItemPtr	test=*Persons2::ConvertPtrUID(SGT);
//DeadCode JIM 20Oct00 		int	lowestdamage=900;
		int	scan=-1;
		int	totaltokens=0,deadtokens=0;
		int	totalpoints=0,deadpoints=0;
		if (!test)
			return	false;
		else
		{
			do{
				totalpoints+=500;									  //MS 06/05/99
				for (GroupItterator gi(test->shape,test->Anim);gi;gi++)
				{
					if (gi.AnimDataMAD().itemstate)
					{
						deadpoints+=gi.DamageWeight()*gi.AnimDataMAD().itemstate;
						if (gi.IsStoresToken())
							deadtokens++;
					}
					if (gi.IsStoresToken())
						totaltokens++;
				}
				while (++scan<IllegalSepID)
				{
					if (scan<WayPointBAND || scan>=WayPointBANDEND) 
						if ((test=*Persons2::ConvertPtrUID(UniqueID(scan)))!=NULL)
							if (test->SGT==SGT && test->shape!=EMPTY)
								if (Persons2::getbandfromUID(UniqueID(scan))!=BritAAASiteBAND)
									break;
				}
			}while (scan<IllegalSepID);
			if (totaltokens)
				if (totaltokens*2<deadtokens*3)
					return true;
				else
					return false;
			else
				if (totalpoints<deadpoints)
					return true;
				else
					return false;

		}


	}
}
////////////////////////////////////////////////////////////////////////
//
// Function:    SelectTarget
// Date:        04/03/99
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
ItemPtr	FormationItem::SelectTarget(ItemPtr currtarget,int* selectedelt,int counter/*=0*/)
{
	ItemPtr rv=NULL;
	if (currtarget)
		if (currtarget->Status.size>=FORMATIONSIZE)
		{
			FormationItemPtr curr=*currtarget;
			while (curr->leader)
				curr=curr->Leader();
			rv=curr;
			if (rv && selectedelt)
				*selectedelt=counter;
		}
		else
		{
			//count up damage
			//count up live tokens
			//if (damage-100*livetokens>700)
			//		pick another target
//DEADCODE DAW 01/07/99 			Bool	bombableSGT=CheckForWeapon(LT_BOMB);			  //DAW 01/07/99
			UniqueID SGT=currtarget->SGT;
			if (SGT==UID_NULL)
				SGT=currtarget->uniqueID.count;
			
//DeadCode DAW 01Jul99 			if (!bombableSGT && Persons2::getbandfromUID(SGT)!=AmberAirfieldBAND && Persons2::getbandfromUID(SGT)!=AmberBridgeBAND)
//DeadCode DAW 01Jul99 				bombableSGT=TRUE;

			int damage=0,livetokens=0;
//DeadCode DAW 01Jul99 			if (!bombableSGT && !currtarget->SGT)
//DeadCode DAW 01Jul99 				damage=800;
//DeadCode DAW 01Jul99 			else
			if (currtarget->shape==EMPTY)
				damage=1000;
			else
				for (GroupItterator gi(currtarget->shape,currtarget->Anim);gi;gi++)
					if (gi.AnimDataMAD().itemstate)
						damage+=gi.DamageWeight()*gi.AnimDataMAD().itemstate;
					else
						if (gi.IsStoresToken())
							livetokens++;
//DEADCODE JIM 22/03/00 			if ((duty&DUTYMASK)==DC_WW)
//DEADCODE JIM 22/03/00 			{
//DEADCODE JIM 22/03/00 				if (selectedelt)
//DEADCODE JIM 22/03/00 					*selectedelt=SelectElement(rv,counter);
//DEADCODE JIM 22/03/00 				rv=currtarget;
//DEADCODE JIM 22/03/00 			}
//DEADCODE JIM 22/03/00 			else
			if (damage-livetokens*100<700)
				rv=currtarget;
			else
			{
//DeadCode DAW 27Jun99 				UniqueID SGT=currtarget->SGT;
//DeadCode DAW 27Jun99 				if (SGT==UID_NULL)
//DeadCode DAW 27Jun99 					SGT=currtarget->uniqueID.count;
				ItemPtr	test=*Persons2::ConvertPtrUID(SGT);
				int	lowestdamage=900;
				int	scan=-1;
				if (test)
					do{
						damage=0;livetokens=0;
//DeadCode DAW 01Jul99 						if (!bombableSGT)
//DeadCode DAW 01Jul99 							damage=1000;
//DeadCode DAW 01Jul99 						else

						if (currtarget->shape==EMPTY)
							damage=1000;
						else
							for (GroupItterator gi(test->shape,test->Anim);gi;gi++)
							{
								if (gi.AnimDataMAD().itemstate)
									damage+=gi.DamageWeight()*gi.AnimDataMAD().itemstate;
								else
									if (gi.IsStoresToken())
										livetokens++;
							}
//DeadCode DAW 01Jul99 						bombableSGT=TRUE;
						if (damage-livetokens*200<lowestdamage)
						{
							rv=test;
							lowestdamage=damage-livetokens*200;
						}
						while (++scan<IllegalSepID)
						{
							if (scan<WayPointBAND || scan>=WayPointBANDEND)
								if ((test=*Persons2::ConvertPtrUID(UniqueID(scan)))!=NULL)
									if (test->SGT==SGT && test->shape!=EMPTY)
										break;
						}
					}while (scan<IllegalSepID);
			}
			if (rv && selectedelt)												//DAW 27Jun99
				*selectedelt=SelectElement(rv,counter);			//DAW 27Jun99
		}
//DeadCode DAW 27Jun99 	if (rv && selectedelt)
//DeadCode DAW 27Jun99 		if (rv->Status.size>=FORMATIONSIZE)
//DeadCode DAW 27Jun99 		{
//DeadCode DAW 27Jun99 			selectedelt=0;
//DeadCode DAW 27Jun99 			rv=SelectConvoyMember(*rv,counter);
//DeadCode DAW 27Jun99 		}
//DeadCode DAW 27Jun99 		else
	if(!rv)
		return currtarget;
	return	rv;
}

//DeadCode DAW 27Jun99 FormationItemPtr	FormationItem::SelectConvoyMember(FormationItemPtr curr,int count)
//DeadCode DAW 27Jun99 {
//DeadCode DAW 27Jun99 	if (count)
//DeadCode DAW 27Jun99 	{
//DeadCode DAW 27Jun99 		if (curr->Leader())
//DeadCode DAW 27Jun99 		{
//DeadCode DAW 27Jun99 			count--;
//DeadCode DAW 27Jun99 			curr=curr->Leader();
//DeadCode DAW 27Jun99 		}
//DeadCode DAW 27Jun99 		while (count)
//DeadCode DAW 27Jun99 		{
//DeadCode DAW 27Jun99 			if (curr->follower)
//DeadCode DAW 27Jun99 				curr=curr->Follower();
//DeadCode DAW 27Jun99 			else
//DeadCode DAW 27Jun99 				if (curr->Leader())
//DeadCode DAW 27Jun99 					curr=curr->Leader();	//make it loop....
//DeadCode DAW 27Jun99 			count--;
//DeadCode DAW 27Jun99 		}
//DeadCode DAW 27Jun99 	}
//DeadCode DAW 27Jun99 	return curr;
//DeadCode DAW 27Jun99 }

bool	FormationItem::SelectedElement(ItemPtr currtarget,int counter/*=0*/,Coords3D* coords/*=&despos*/)
{
	if (currtarget->shape==EMPTY)									  //DAW 16/06/99
		return false;												  //DAW 16/06/99
	else
	if (currtarget->Status.size>=FORMATIONSIZE)
	{
		FormationItemPtr curr=*currtarget;
		int count=counter;
		if (count)
		{
			if (curr->Leader())
			{
				count--;
				curr=curr->Leader();
			}
			while (count)
			{
				if (curr->follower)
					curr=curr->Follower();
				else
					if (curr->Leader())
						curr=curr->Leader();	//make it loop....
				count--;
			}
		}
		*coords=curr->World;
		return (curr->Status.deadtime==0);
	}
	else
	{
		GroupItterator gi(currtarget->shape,currtarget->Anim);
		for (;counter;gi++,counter--)
		{}	
		*coords=gi.delta;
		*coords+=currtarget->World;
		return gi.AnimDataMAD().itemstate!=DEAD;
	}
}

int		FormationItem::SelectElement(ItemPtr currtarget,int counter/*=0*/)
{
	const int maxscores=40;
	UByte scores[maxscores];
	int	slot=0;
	if (currtarget)
	{
		if (currtarget->Status.size>=FORMATIONSIZE)
			return counter;											  //RDH 27/06/99
		for (GroupItterator gi(currtarget->shape,currtarget->Anim);gi&&slot<maxscores;gi++,slot++)
		{
			if (gi.AnimDataMAD().itemstate!=ALIVE)
				if (gi.AnimDataMAD().itemstate!=DEAD)
					scores[slot]=2+gi.DamageWeight()/(gi.AnimDataMAD().itemstate+1);
				else
					scores[slot]=2;	//so zero is lower...
			else
				if (gi.IsStoresToken())
					scores[slot]=255;
				else
					scores[slot]=2+gi.DamageWeight();
		}
		int	bestslot=0;
		counter++;
		while (--counter>-1)
		{
			int	bestscore=0;

			for (int sl=0;sl<slot;sl++)
				if (scores[sl]>bestscore)
				{
					bestslot=sl;
					bestscore=scores[sl];
				}
			if (bestscore==1)
				scores[bestslot]=0;
			else
				scores[bestslot]=1;
		}
		return bestslot;
	}
	else
		return	-1;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitGroupFields
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	GroupItterator::InitGroupFields()
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(group);

	baseanimdata = animdata;
	noelements = 0;
	totalpoints = 0;
	hitlimit = false;
	status = 0;


	if (SHAPESTUFF.GetShapeScale(sdptr)==SHP_GRP)
	{
		UByteP			instr_ptr;
		DOGROUP_PTR		ptr;
		SWord			instruction;


		instr_ptr = (UByteP)sdptr + sdptr->liveshpref;

		forever
		{
			instruction = *instr_ptr;
			instr_ptr++;

			if (instruction == dogroupno)
			{
				ptr = (DOGROUP_PTR) instr_ptr;

				if (!noelements)
				{
					shape = (ShapeNum) ptr->shapenum;

					delta.X = ptr->xoffset;
					delta.Y = ptr->yoffset;
					delta.Z = ptr->zoffset;

					grpindexer = basegrpindexer = (char*)instr_ptr;
					
					if (animdata != NULL)
					{
						MinAnimData*	mad = (MinAnimData*) animdata;
						status = mad->itemstate;
						deadittfirstbyteptr=&animdata[0];		//RJS 27Apr99 //CSB 04/06/99
//DEADCODE DAW 26/04/99 #pragma message ("Deadbits need fixing Robert")
//DEADCODE DAW 26/04/99 						deadittfirstbyte=*animptr;
//DEADCODE DAW 26/04/99 						status = ((MinAnimData*)animdata)->itemstate;
//DeadCode DAW 26Apr99 						status = ((MinAnimData*)animptr)->itemstate;
					}
					percentdamage=ptr->element_number;
				}

				totalpoints += ptr->element_number;
				noelements++;

				instr_ptr += sizeof(DOGROUP);
			}
			else
				break;
		}
		if (noelements<2)
			hitlimit=true;
	}
	else
	{	//get same info for simple item, please!	//CSB 02/04/99	
		delta.X=delta.Y=delta.Z=0;
		shape=group;
		noelements=1;
		totalpoints=100;
		if (animdata != NULL)
		{
			MinAnimData*	mad = (MinAnimData*) animdata;
			status = mad->itemstate;

			deadittfirstbyteptr=&animdata[0];		//RJS 27Apr99	  //CSB 04/06/99
//DEADCODE DAW 26/04/99 			status = ((MinAnimData*)animdata)->itemstate;
		}
		percentdamage=300;

//DEADCODE RDH 20/05/99 		hitlimit=true;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NumElts
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	GroupItterator::NumElts()
{
	return(noelements);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EltAnimDataSize
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	GroupItterator::EltAnimDataSize()
{
//	if (animdata)
	return(SHAPE.GetAnimDataSize(shape));

	return(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NextElement
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	GroupItterator::NextElement()
{
	if (!hitlimit)
	{
		DOGROUP_PTR		ptr;
		UByteP			instr_ptr;
		SWord			instruction;

		instr_ptr = (UByteP)grpindexer;
		instr_ptr += sizeof(DOGROUP);

		instruction = *instr_ptr;
		if (instruction == dogroupno)
		{
			ShapeNum	newshp;

			instr_ptr++;

			ptr = (DOGROUP_PTR) instr_ptr;

			newshp = (ShapeNum) ptr->shapenum;

			if (animdata != NULL)
			{
				animdata += SHAPE.GetElementAnimOffset(shape);
			 
				status = ((MinAnimData*)animdata)->itemstate;
				deadittfirstbyteptr=&animdata[0];
			}

			shape = newshp;

			delta.X = ptr->xoffset;
			delta.Y = ptr->yoffset;
			delta.Z = ptr->zoffset;

			percentdamage = ptr->element_number;

			grpindexer = (char*)instr_ptr;

			return(true);
		}
		else
			hitlimit = true;
	}

	return(false);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IsStoresToken
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	GroupItterator::IsStoresToken()
{
	if (shape==group) return false;	
	return (((DOGROUP_PTR)grpindexer)->tokenflag >= GRP_TKN_INVIS_DEP);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DamageWeight
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		GroupItterator::DamageWeight()
{
	return(percentdamage);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MaxDamagePoints
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		GroupItterator::MaxDamagePoints()
{
	return(totalpoints);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AnimDataByte
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByte&	GroupItterator::AnimDataByte()
{
	if (deadittfirstbyteptr)
		return	*deadittfirstbyteptr;
	else
		_Error.EmitSysErr(__FILE__": deadittfirstbyteptr is bollocks!");

static	UByte	retval = 0;

	return retval;
}
MinAnimData&	GroupItterator::AnimDataMAD()	
{return	(MinAnimData&) AnimDataByte();}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EltLauncherDataSize
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		GroupItterator::EltLauncherDataSize(animptr&	adptr)
{
	if (adptr != NULL)
	{
		MinAnimData*	mad = (MinAnimData*) adptr;

		return(mad->nolaunchers * sizeof(DOLAUNCHER)+sizeof(MinAnimData));
	}

	return(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PostLauncherDataSize
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		GroupItterator::PostLauncherDataSize()
{
	return(EltAnimDataSize()-EltLauncherDataSize(animdata));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PostLauncherDataLoc
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
char*	GroupItterator::PostLauncherDataLoc()
{
	if (animdata != NULL)
	{
		animptr	newanimdata = animdata;

		newanimdata += EltLauncherDataSize(newanimdata);	//RJS 27Apr99
//DEADCODE DAW 28/04/99 Now in ELDS
//DEADCODE DAW 28/04/99 		newanimdata += sizeof(MinAnimData);

		return((char*)&newanimdata);
	}

	return(0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetLaunchers
//Author		Robert Slater
//Date			Mon 15 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	GroupItterator::ResetLaunchers()
{
	if (animdata != NULL)
	{
//DeadCode RJS 21Apr99 		animptr			mad = animdata;
		MinAnimData*	madold = (MinAnimData*) animdata;

		UByte	oldinvisible = madold->IsInvisible;

		SHAPE.InitGlobalItem();
//DeadCode RJS 21Apr99 		SHAPE.InitItemAnim(mad,shape);
		SHAPE.InitItemAnim(animdata,shape);						//RJS 21Apr99

		madold->IsInvisible = oldinvisible;
	}
}
