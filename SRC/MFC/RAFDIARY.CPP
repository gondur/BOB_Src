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

// RowanDialog: // RAFDiary.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include	"sqddiary.h"
#include "RAFDiary.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// RAFDiary dialog


#ifndef	BOB_DEMO_VER
RDialog*	RAFDiary::Make(SquadNum squad)
{
	RAFDiary* rafdiary  = new RAFDiary();

	rafdiary->sqnum = squad;
	rafdiary->sqnumptr = &rafdiary->sqnum;
	rafdiary->currentryptr = &rafdiary->currentry;
	rafdiary->sqdetailsptr = rafdiary->sqdetails; 

	rafdiary->FindGroup();
	rafdiary->FillSquadronDetails(rafdiary->sqnum,NULL,rafdiary->sqdetails,rafdiary->currentry);



	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
//			DialList(DialBox(FIL_NULL,new RAFDiary()),
			DialList(DialBox(FIL_D_SQUADRON_LOGBOOK,rafdiary,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
						DialBox(FIL_D_SQUADRON_LOGBOOK,new RAFDiaryList(rafdiary->sqnumptr, rafdiary->currentryptr, rafdiary->sqdetailsptr)),
						DialBox(FIL_D_SQUADRON_LOGBOOK,new RAFDiaryDetails(rafdiary->sqnumptr, rafdiary->currentryptr, rafdiary->sqdetailsptr, false))
					)
			);
}
#endif

RAFDiary::RAFDiary(CWnd* pParent /*=NULL*/)
	: RowanDialog(RAFDiary::IDD, pParent)
{
	//{{AFX_DATA_INIT(RAFDiary)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
		groupnum=0;

}
void	RAFDiary::RefreshData(int effect)
{
//		for (RowanDialog* ctl=(RowanDialog*)fchild;ctl;ctl=(RowanDialog*)ctl->sibling)
	switch (effect)
	{
		case 0:
		case 1:
		{
			RowanDialog*	dlist=(RowanDialog*)fchild;		//ac num 
			RowanDialog*	ddet=(RowanDialog*)dlist->sibling;		//ac num 
			CRect parentpos;
			GetWindowRect(parentpos);
			CPoint parentoff(parentpos.left,parentpos.top);
			CRect dlistpos;
			dlist->GetWindowRect(dlistpos);
			CRect ddetpos;
			ddet->GetWindowRect(ddetpos);
			dlistpos-=parentoff;
			ddetpos-=parentoff;
			dlist->MoveWindow(ddetpos);
			ddet->MoveWindow(dlistpos);
			if (parentoff.x>0)
				dlist->RefreshData(groupnum);
			else
				ddet->RefreshData(groupnum);

			break;
		}
		case 2:
		{
			FindGroup();
//DeadCode JIM 13Oct00 			FillSquadronDetails();
			Refresh();
			break;
		}
	}

}


void RAFDiary::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RAFDiary)
	DDX_Control(pDX, IDC_RCOMBOSQUAD, m_IDC_RCOMBOSQUAD);
	DDX_Control(pDX, IDC_RCOMBOGROUP, m_IDC_RCOMBOGROUP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RAFDiary, CDialog)
	//{{AFX_MSG_MAP(RAFDiary)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RAFDiary message handlers

void	RAFDiary::FindGroup()
{
	int j=0, i = 0;
	while (		(Node_Data.squadron[i].squadron != SQ_ZERO)
			&&	(j < MAX_SQUAD)			
		  )
	{
//DeadCode JIM 20Oct00 		PlaneTypeSelect	actype = Node_Data.squadron[i].AcType();
		UniqueID uid = Node_Data.squadron[i].homeairfield;
		TargetFighterField* af;
		af = Node_Data[uid];
	 	TargetSectorField*	sectorfield = af->getsectoraf();

		if(*sqnumptr == Node_Data.squadron[i].squadron)
		{
			group = sectorfield->groupname - IDS_GROUP_10;
			break;
		}
	  i++;
	 }



}
void	RAFDiary::FillList()
{
	int j=0, i = 0;
	while (		(Node_Data.squadron[i].squadron != SQ_ZERO)
			&&	(j < MAX_SQUAD)			
		  )
	{
//DeadCode JIM 20Oct00 		PlaneTypeSelect	actype = Node_Data.squadron[i].AcType();
		UniqueID uid = Node_Data.squadron[i].homeairfield;
		TargetFighterField* af;
		af = Node_Data[uid];
	 	TargetSectorField*	sectorfield = af->getsectoraf();
		if	(	(group == 5)
					||
					(sectorfield->groupname == IDS_GROUP_10+group)
					||
					(
						(group == 4)
						&&  (sectorfield->groupname != IDS_GROUP_13)
					)
			)
			
			{
					Squadron[j] = i;
					j++;
			}
	  i++;
	 }
	maxsquads = j;



}





void RAFDiary::Refresh()
{
	
	CRCombo* combo;

	combo=GETDLGITEM(IDC_RCOMBOGROUP);
	combo->Clear()->RESCOMBO(10,6)->
					SetIndex(group);

	combo=GETDLGITEM(IDC_RCOMBOSQUAD);
	combo->Clear();
	
	int index = 0;
	for (int i = 0; i < maxsquads; i++)
	{
		combo->AddString(Node_Data.squadron[Squadron[i]].SubName());
		if(sqnum == Node_Data.squadron[Squadron[i]].squadron)
			index = i;

	}

	combo->SetIndex(index);



}

BOOL RAFDiary::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FillList();

	Refresh();	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(RAFDiary, CDialog)
    //{{AFX_EVENTSINK_MAP(RAFDiary)
	ON_EVENT(RAFDiary, IDC_RCOMBOGROUP, 1 /* TextChanged */, OnTextChangedRcombogroup, VTS_BSTR VTS_I2)
	ON_EVENT(RAFDiary, IDC_RCOMBOSQUAD, 1 /* TextChanged */, OnTextChangedRcombosquad, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void RAFDiary::FillSquadronDetails(SquadNum sqnum,SquadronBase* indexer,SquadronBase** sqdetails,int& currentry)
{
	SquadronBase*	sqentry = Squad_Diary.FindLast(sqnum);

	int i = 0;
	currentry = -1;
 	while (	(i < RAFDiary::MAX_SQDETAILS) && (sqentry))
 	{
 		sqdetails[i] = sqentry;
		if (sqentry==indexer)
			currentry = i;
 		sqentry = Squad_Diary.FindPrev(sqentry);
 		i++;
 	}
	if (currentry==-1 && i>0)
		currentry = 0;
		

//DeadCode JIM 23Oct00  	while (i < RAFDiary::MAX_SQDETAILS)
 	{
 		sqdetails[i++] = NULL;
 	}

}

void RAFDiary::OnTextChangedRcombogroup(LPCTSTR Caption, short index) 
{
	group = index;
	FillList();

	Refresh();
	RowanDialog*	dlist=(RowanDialog*)fchild;		//ac num 
	RowanDialog*	ddet=(RowanDialog*)dlist->sibling;		//ac num 

	sqnum = Node_Data.squadron[Squadron[0]].squadron;	

	FillSquadronDetails(sqnum,NULL,sqdetails,currentry);
	dlist->RefreshData(0);
	ddet->RefreshData(0);
	
}

void RAFDiary::OnTextChangedRcombosquad(LPCTSTR Caption, short index) 
{
	sqnum = Node_Data.squadron[Squadron[index]].squadron;	
	FillSquadronDetails(sqnum,NULL,sqdetails,currentry);

	RowanDialog*	dlist=(RowanDialog*)fchild;		//ac num 
	RowanDialog*	ddet=(RowanDialog*)dlist->sibling;		//ac num 
	dlist->RefreshData(0);
	ddet->RefreshData(0);

}
