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

// RowanDialog: // RAFSqLst.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "RAFSqLst.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// RAFSquadList dialog


RDialog*	RAFSquadList::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_SQUADRONLIST,new RAFSquadList())
			);
}


RAFSquadList::RAFSquadList(CWnd* pParent /*=NULL*/)
	: RowanDialog(RAFSquadList::IDD, pParent)
{
	//{{AFX_DATA_INIT(RAFSquadList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void RAFSquadList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RAFSquadList)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX, IDC_RCOMBOAIRCRAFT, m_IDC_RCOMBOAIRCRAFT);
	DDX_Control(pDX, IDC_RCOMBOGROUP, m_IDC_RCOMBOGROUP);
	DDX_Control(pDX, IDC_RCOMBOREADINESS, m_IDC_RCOMBOREADINESS);
	DDX_Control(pDX, IDC_RSPINBUT_MINAC, m_IDC_RSPINBUT_MINAC);
	DDX_Control(pDX, IDC_RSPINBUT_MINPILOTS, m_IDC_RSPINBUT_MINPILOTS);
	DDX_Control(pDX, IDC_RSPINBUT_CAT, m_IDC_RSPINBUT_CAT);
	//}}AFX_DATA_MAP
 	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->AddString("",0);
}


BEGIN_MESSAGE_MAP(RAFSquadList, CDialog)
	//{{AFX_MSG_MAP(RAFSquadList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RAFSquadList message handlers

void	RAFSquadList:: RefreshOneLine(int i)
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//	Node_Data.squadron[i];
	rlistbox->AddString(Node_Data.squadron[i].SubName(),0);
	rlistbox->AddString(RESLIST(SPIT_A, Node_Data.squadron[i].AcType()),1);
	rlistbox->AddString(GetTargName(Node_Data.squadron[i].homeairfield),2);
	CString chr = (TCHAR)(Node_Data.squadron[i].Category() + 'A');
	rlistbox->AddString(chr,3);
	rlistbox->AddString(RESSTRING(READY),4);
	rlistbox->AddString(CSprintf("%i", Node_Data.squadron[i].acavail),5);
	rlistbox->AddString(CSprintf("%i", Node_Data.squadron[i].pilotsavail),6);

}
void	RAFSquadList::RefreshList()
{
	FillList();

 	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 31Oct00 	rlistbox->AddString("",0);
 	rlistbox->Clear();
	//rlistbox->AddColumn(48);
	//rlistbox->AddColumn(100);										  //RDH 02/06/99
	//rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
	//rlistbox->AddColumn(24);										  //RDH 02/06/99
	//rlistbox->AddColumn(56);										  //RDH 02/06/99
	//rlistbox->AddColumn(44);										  //RDH 02/06/99
	//rlistbox->AddColumn(20);										  //RDH 02/06/99


	rlistbox->AddString(RESSTRING(SQUAD),0);
	rlistbox->AddString(RESSTRING(TYPE),1);
	rlistbox->AddString(RESSTRING(BASE),2);
	rlistbox->AddString(RESSTRING(CAT),3);
	rlistbox->AddString(RESSTRING(READY),4);
	rlistbox->AddString(RESSTRING(AC),5);
	rlistbox->AddString(RESSTRING(PILOTS),6);

	for (int i = 0; i < maxsquads; i++)
		RefreshOneLine(Squadron[i]);



}
void	RAFSquadList::FillList()
{

	int j=0, i = 0;
	while (		(Node_Data.squadron[i].squadron != SQ_ZERO)
			&&	(j < MAX_SQUAD)			
		  )
	{
		PlaneTypeSelect	actype = Node_Data.squadron[i].AcType();
		if  (	(MMC.sl_ac == 2)
				||
				(
					(MMC.sl_ac == 0)
					&&  (		(actype == PT_SPIT_A)
							||	(actype == PT_SPIT_B) 
						)

				)
				||
				(	(MMC.sl_ac == 1)
					&&  (		(actype == PT_HURR_A)
							||	(actype == PT_HURR_B) 
						)
				)
			)
		{
			UniqueID uid = Node_Data.squadron[i].homeairfield;
			TargetFighterField* af;
			af = Node_Data[uid];
		 	TargetSectorField*	sectorfield = af->getsectoraf();
			if	(	(MMC.sl_group == 5)
					||
					(sectorfield->groupname == IDS_GROUP_10+MMC.sl_group)
					||
					(
						(MMC.sl_group == 4)
						&&  (sectorfield->groupname != IDS_GROUP_13)
					)
				)
			{
				if (		(MMC.sl_min_pilot <= Node_Data.squadron[i].pilotsavail)
						&&	(MMC.sl_min_ac <= Node_Data.squadron[i].acavail)
						&&	(MMC.sl_category >= Node_Data.squadron[i].Category())
				   )
				{
					Squadron[j] = i;
					j++;
				}
			}
		}
	  i++;
	 }
	maxsquads = j;



}


BOOL RAFSquadList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//DeadCode RDH 16Dec99 	CRListBox* rlistbox;
//DeadCode RDH 16Dec99 	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 16Dec99 //DEADCODE AMM 15/12/99 	rlistbox->Clear();
//DeadCode RDH 16Dec99 //DEADCODE AMM 15/12/99 	rlistbox->AddColumn(40);
//DeadCode RDH 16Dec99 //DEADCODE AMM 15/12/99 	rlistbox->AddColumn(100);										  //RDH 02/06/99
//DeadCode RDH 16Dec99 //DEADCODE AMM 15/12/99 	rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
//DeadCode RDH 16Dec99 //DEADCODE AMM 15/12/99 	rlistbox->AddColumn(20);										  //RDH 02/06/99
//DeadCode RDH 16Dec99 //DEADCODE AMM 15/12/99 	rlistbox->AddColumn(40);										  //RDH 02/06/99
//DeadCode RDH 16Dec99 //DEADCODE AMM 15/12/99 	rlistbox->AddColumn(30);										  //RDH 02/06/99
//DeadCode RDH 16Dec99 //DEADCODE AMM 15/12/99 	rlistbox->AddColumn(20);										  //RDH 02/06/99
//DeadCode RDH 16Dec99 
//DeadCode RDH 16Dec99 	rlistbox->AddString(RESSTRING(SQUAD),0);
//DeadCode RDH 16Dec99 	rlistbox->AddString(RESSTRING(TYPE),1);
//DeadCode RDH 16Dec99 	rlistbox->AddString(RESSTRING(BASE),2);
//DeadCode RDH 16Dec99 	rlistbox->AddString(RESSTRING(CAT),3);
//DeadCode RDH 16Dec99 	rlistbox->AddString(RESSTRING(READY),4);
//DeadCode RDH 16Dec99 	rlistbox->AddString(RESSTRING(AC),5);
//DeadCode RDH 16Dec99 	rlistbox->AddString(RESSTRING(PILOTS),6);
//DeadCode RDH 16Dec99 
//DeadCode RDH 16Dec99 
//DeadCode RDH 16Dec99 	
//DeadCode RDH 16Dec99 	rlistbox->AddString("222",0);
//DeadCode RDH 16Dec99 	rlistbox->AddString("Spitfire",1);
//DeadCode RDH 16Dec99 	rlistbox->AddString("Biggin Hill",2);
//DeadCode RDH 16Dec99 	rlistbox->AddString("A",3);
//DeadCode RDH 16Dec99 	rlistbox->AddString("12",4);
//DeadCode RDH 16Dec99 	rlistbox->AddString("16",5);
//DeadCode RDH 16Dec99 	rlistbox->AddString("12",6);
//DeadCode RDH 16Dec99 
//DeadCode RDH 16Dec99 		CRSpinBut* spinbut;
//DeadCode RDH 16Dec99 
//DeadCode RDH 16Dec99 	spinbut=GETDLGITEM(IDC_RSPINBUT_MINAC);
//DeadCode RDH 16Dec99 	spinbut->Clear()->MakeNumList(20,0,1)->SetIndex(10);
//DeadCode RDH 16Dec99 
//DeadCode RDH 16Dec99 	spinbut=GETDLGITEM(IDC_RSPINBUT_MINPILOTS);
//DeadCode RDH 16Dec99 	spinbut->Clear()->MakeNumList(20,0,1)->SetIndex(12);
//DeadCode RDH 16Dec99 
//DeadCode RDH 16Dec99  	spinbut=GETDLGITEM(IDC_RSPINBUT_CAT);
//DeadCode RDH 16Dec99 	spinbut->Clear()->MakeNumList(3,0,1)->SetIndex(0);
//DeadCode RDH 16Dec99 
//DeadCode RDH 16Dec99 
//DeadCode RDH 16Dec99 	CRCombo* combo;
//DeadCode RDH 16Dec99 	combo=GETDLGITEM(IDC_RCOMBOAIRCRAFT);
//DeadCode RDH 16Dec99 	combo->Clear()->RESCOMBO(HURRICANE,3)->
//DeadCode RDH 16Dec99 					SetIndex(0);
//DeadCode RDH 16Dec99 
//DeadCode RDH 16Dec99  	combo=GETDLGITEM(IDC_RCOMBOGROUP);
//DeadCode RDH 16Dec99 	combo->Clear()->RESCOMBO(10,6)->
//DeadCode RDH 16Dec99 					SetIndex(2);
//DeadCode RDH 16Dec99 
//DeadCode RDH 16Dec99    	combo=GETDLGITEM(IDC_RCOMBOREADINESS);
//DeadCode RDH 16Dec99 	combo->Clear();

	CRSpinBut* spinbut;

	spinbut=GETDLGITEM(IDC_RSPINBUT_MINAC);
	spinbut->Clear()->MakeNumList(20,0,1)->SetIndex(MMC.sl_min_ac);

	spinbut=GETDLGITEM(IDC_RSPINBUT_MINPILOTS);
	spinbut->Clear()->MakeNumList(20,0,1)->SetIndex(MMC.sl_min_pilot);

 	spinbut=GETDLGITEM(IDC_RSPINBUT_CAT);
	spinbut->Clear();
	spinbut->AddString("C");
	spinbut->AddString("B");
	spinbut->AddString("A");
	int index = 2 - MMC.sl_category;
	if (index < 0)
		index = 0;
	if (index > 2)
		index = 2;


	spinbut->SetIndex(index);		


	CRCombo* combo;
	combo=GETDLGITEM(IDC_RCOMBOAIRCRAFT);
	combo->Clear()->RESCOMBO(SPITFIRE,3)->
					SetIndex(MMC.sl_ac);

 	combo=GETDLGITEM(IDC_RCOMBOGROUP);
	combo->Clear()->RESCOMBO(10,6)->
					SetIndex(MMC.sl_group);

//DeadCode RDH 16Aug00    	combo=GETDLGITEM(IDC_RCOMBOREADINESS);
//DeadCode RDH 16Aug00 	combo->Clear();
//DeadCode RDH 16Aug00 
	RefreshList();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(RAFSquadList, CDialog)
    //{{AFX_EVENTSINK_MAP(RAFSquadList)
	ON_EVENT(RAFSquadList, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(RAFSquadList, IDC_RCOMBOAIRCRAFT, 1 /* TextChanged */, OnTextChangedRcomboaircraft, VTS_BSTR VTS_I2)
	ON_EVENT(RAFSquadList, IDC_RCOMBOGROUP, 1 /* TextChanged */, OnTextChangedRcombogroup, VTS_BSTR VTS_I2)
	ON_EVENT(RAFSquadList, IDC_RCOMBOREADINESS, 1 /* TextChanged */, OnTextChangedRcomboreadiness, VTS_BSTR VTS_I2)
	ON_EVENT(RAFSquadList, IDC_RSPINBUT_MINAC, 1 /* TextChanged */, OnTextChangedRspinbutMinac, VTS_BSTR VTS_I2)
	ON_EVENT(RAFSquadList, IDC_RSPINBUT_MINPILOTS, 1 /* TextChanged */, OnTextChangedRspinbutMinpilots, VTS_BSTR VTS_I2)
	ON_EVENT(RAFSquadList, IDC_RSPINBUT_CAT, 1 /* TextChanged */, OnTextChangedRspinbutCat, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void RAFSquadList::OnSelectRlistboxctrl1(long row, long column) 
{
#ifndef	BOB_DEMO_VER

	if (row > 0)
	{
		UniqueID homeuid = Node_Data.squadron[Squadron[row - 1]].homeairfield;
		int j=1, i = 0;
		do
		{
		  if (Node_Data.squadron[i].homeairfield == homeuid)
		  {
			  j++;
		  }
		  i++;
		}
		while	(		(i <= Squadron[row - 1])
					&&	(Node_Data.squadron[i].squadron != SQ_ZERO)
				);	
		if (Node_Data.squadron[Squadron[row - 1]].homeairfield==UID_AF_NEWCASTLE)
			MainToolBar().OpenACDossier(Node_Data.squadron[Squadron[row - 1]].homeairfield,Node_Data.squadron[Squadron[row - 1]].squadron);	//JIM 29Sep00
		else
			MainToolBar().OpenACDossier(Node_Data.squadron[Squadron[row - 1]].homeairfield,j);
	}

#endif	
}

void RAFSquadList::OnTextChangedRcomboaircraft(LPCTSTR Caption, short index) 
{
	MMC.sl_ac = index;
	RefreshList();

}

void RAFSquadList::OnTextChangedRcombogroup(LPCTSTR Caption, short index) 
{
	MMC.sl_group = index;
	RefreshList();
	
}

void RAFSquadList::OnTextChangedRcomboreadiness(LPCTSTR Caption, short index) 
{
	// TODO: Add your control notification handler code here
	
}

void RAFSquadList::OnTextChangedRspinbutMinac(LPCTSTR caption, short Index) 
{
	MMC.sl_min_ac = Index;	
	RefreshList();

}

void RAFSquadList::OnTextChangedRspinbutMinpilots(LPCTSTR caption, short Index) 
{
	MMC.sl_min_pilot = Index;	
	RefreshList();

}

void RAFSquadList::OnTextChangedRspinbutCat(LPCTSTR caption, short Index) 
{
	MMC.sl_category = 2 - Index ;		
	RefreshList();

}
