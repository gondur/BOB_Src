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

// RowanDialog: // GWadlist.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "GWadlist.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// GeschwaderList dialog


RDialog*	GeschwaderList::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_GESCHWADER_LIST,new GeschwaderList())
			);
}


GeschwaderList::GeschwaderList(CWnd* pParent /*=NULL*/)
	: RowanDialog(GeschwaderList::IDD, pParent)
{
	//{{AFX_DATA_INIT(GeschwaderList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void GeschwaderList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GeschwaderList)
	DDX_Control(pDX, IDC_RCOMBOGESCHWADER, m_IDC_RCOMBOGESCHWADER);
	DDX_Control(pDX, IDC_RCOMBOFLOTTE, m_IDC_RCOMBOFLOTTE);
	DDX_Control(pDX, IDC_RSPINBUT_MINAC, m_IDC_RSPINBUT_MINAC);
	DDX_Control(pDX, IDC_RSPINBUT_CAT, m_IDC_RSPINBUT_CAT);
	DDX_Control(pDX, IDC_RSPINBUT_MINPILOTS, m_IDC_RSPINBUT_MINPILOTS);
	DDX_Control(pDX, IDC_RCOMBOREADINESS, m_IDC_RCOMBOREADINESS);
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
	GETDLGITEM(IDC_RLISTBOXCTRL1)->AddString("",0);
}


BEGIN_MESSAGE_MAP(GeschwaderList, CDialog)
	//{{AFX_MSG_MAP(GeschwaderList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GeschwaderList message handlers

BEGIN_EVENTSINK_MAP(GeschwaderList, CDialog)
    //{{AFX_EVENTSINK_MAP(GeschwaderList)
	ON_EVENT(GeschwaderList, IDC_RSPINBUT_MINPILOTS, 1 /* TextChanged */, OnTextChangedRspinbutMinpilots, VTS_BSTR VTS_I2)
	ON_EVENT(GeschwaderList, IDC_RSPINBUT_MINAC, 1 /* TextChanged */, OnTextChangedRspinbutMinac, VTS_BSTR VTS_I2)
	ON_EVENT(GeschwaderList, IDC_RSPINBUT_CAT, 1 /* TextChanged */, OnTextChangedRspinbutCat, VTS_BSTR VTS_I2)
	ON_EVENT(GeschwaderList, IDC_RCOMBOREADINESS, 1 /* TextChanged */, OnTextChangedRcomboreadiness, VTS_BSTR VTS_I2)
	ON_EVENT(GeschwaderList, IDC_RCOMBOGESCHWADER, 1 /* TextChanged */, OnTextChangedRcombogeschwader, VTS_BSTR VTS_I2)
	ON_EVENT(GeschwaderList, IDC_RCOMBOFLOTTE, 1 /* TextChanged */, OnTextChangedRcomboflotte, VTS_BSTR VTS_I2)
	ON_EVENT(GeschwaderList, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void GeschwaderList::OnTextChangedRspinbutMinpilots(LPCTSTR caption, short Index) 
{
	MMC.sl_min_pilot = 2*Index;	
	RefreshList();

	
}

void GeschwaderList::OnTextChangedRspinbutMinac(LPCTSTR caption, short Index) 
{
	MMC.sl_min_ac = 2*Index;	
	RefreshList();

	
}

void GeschwaderList::OnTextChangedRspinbutCat(LPCTSTR caption, short Index) 
{
	MMC.sl_category = Index;	
	RefreshList();

	
}

void GeschwaderList::OnTextChangedRcomboreadiness(LPCTSTR Caption, short index) 
{
	// TODO: Add your control notification handler code here
	
}

void GeschwaderList::OnTextChangedRcombogeschwader(LPCTSTR Caption, short index) 
{
	MMC.sl_geschwadertype = index;
	RefreshList();
	
}

void GeschwaderList::OnTextChangedRcomboflotte(LPCTSTR Caption, short index) 
{
	MMC.sl_flotte = index;
	RefreshList();
	
}

void	GeschwaderList:: RefreshOneLine(int i)
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);

	int wader = Node_Data.gruppe[i].wadernum;
	rlistbox->AddString(RESLIST(J, Node_Data.geschwader[wader].wadername) 
							+ CSprintf("%i",	Node_Data.geschwader[wader].wadernum),0
						);	
	rlistbox->AddString(Node_Data.gruppe[i].SubName(),1);
	rlistbox->AddString(RESLIST(SPIT_A, Node_Data.gruppe[i].AcType()),2);
	rlistbox->AddString(GetTargName(Node_Data.gruppe[i].homeairfield),3);
	CString chr = (TCHAR)(Node_Data.gruppe[i].Category() + 'A');
	rlistbox->AddString(chr,4);
	rlistbox->AddString(RESSTRING(READY),5);
	rlistbox->AddString(CSprintf("%i", Node_Data.gruppe[i].acavail),6);
	rlistbox->AddString(CSprintf("%i", Node_Data.gruppe[i].pilotsavail),7);

}
void	GeschwaderList::RefreshList()
{
	FillList();

 	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 31Oct00  	rlistbox->AddString("",0);
	rlistbox->Clear();
	//rlistbox->AddColumn(40);
	//rlistbox->AddColumn(48);
	//rlistbox->AddColumn(60);										  //RDH 02/06/99
	//rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
	//rlistbox->AddColumn(24);										  //RDH 02/06/99
	//rlistbox->AddColumn(48);										  //RDH 02/06/99
	//rlistbox->AddColumn(44);										  //RDH 02/06/99
	//rlistbox->AddColumn(28);										  //RDH 02/06/99


	rlistbox->AddString(RESSTRING(GESCH),0);
	rlistbox->AddString(RESSTRING(GRUPPE),1);
	rlistbox->AddString(RESSTRING(TYPE),2);
	rlistbox->AddString(RESSTRING(BASE),3);
	rlistbox->AddString(RESSTRING(CAT),4);
	rlistbox->AddString(RESSTRING(READY),5);
	rlistbox->AddString(RESSTRING(AC),6);
	rlistbox->AddString(RESSTRING(PILOTS),7);

	for (int i = 0; i < maxsquads; i++)
		RefreshOneLine(Squadron[i]);



}
void	GeschwaderList::FillList()
{

	int j=0, i = 0;
	while (		(Node_Data.gruppe[i].squadron != SQ_ZERO)
			&&	(j < MAX_SQUAD)			
		  )
	{
		int wader = Node_Data.gruppe[i].wadernum;
		if  (	(	(	(MMC.sl_geschwadertype - 1) == 
							Node_Data.geschwader[wader].wadername
					)
					||
					(
						MMC.sl_geschwadertype == 0
					)
				)
				&&
				(
					(MMC.sl_flotte == 2)
					||
					(MMC.sl_flotte == 
						(Node_Data.geschwader[wader].luftflotte- LF_2))
				)
			)
		{
				if (		(MMC.sl_min_pilot <= Node_Data.gruppe[i].pilotsavail)
						&&	(MMC.sl_min_ac <= Node_Data.gruppe[i].acavail)
						&&	(MMC.sl_category >= Node_Data.gruppe[i].Category())
				   )
				{
					Squadron[j] = i;
					j++;
				}
		}
	  i++;
	 }
	maxsquads = j;



}


BOOL GeschwaderList::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
		CRSpinBut* spinbut;

	spinbut=GETDLGITEM(IDC_RSPINBUT_MINAC);
	spinbut->Clear()->MakeNumList(40,0,2)->SetIndex(MMC.sl_min_ac);

	spinbut=GETDLGITEM(IDC_RSPINBUT_MINPILOTS);
	spinbut->Clear()->MakeNumList(40,0,2)->SetIndex(MMC.sl_min_pilot);

 	spinbut=GETDLGITEM(IDC_RSPINBUT_CAT);
	spinbut->Clear();
	spinbut->AddString("A");
	spinbut->AddString("B");
	spinbut->AddString("C");
	spinbut->SetIndex(MMC.sl_category);




	CRCombo* combo;
		combo=GETDLGITEM(IDC_RCOMBOFLOTTE);
		combo->Clear()->RESCOMBO(LUFTFLOTTE2,3)->
					SetIndex(MMC.sl_flotte);
		
		combo=GETDLGITEM(IDC_RCOMBOGESCHWADER);
		combo->Clear()->RESCOMBO(ANY_A,5)->
					SetIndex(MMC.sl_geschwadertype);

//DeadCode RDH 16Aug00       	combo=GETDLGITEM(IDC_RCOMBOREADINESS);
//DeadCode RDH 16Aug00 	combo->Clear();
//DeadCode RDH 16Aug00 

 	RefreshList();


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void GeschwaderList::OnSelectRlistboxctrl1(long row, long column) 
{
#ifndef	BOB_DEMO_VER

	if (row > 0)
	{
	
			MainToolBar().OpenACDossier(Node_Data.gruppe[Squadron[row - 1]].wadernum,
				Node_Data.gruppe[Squadron[row - 1]].gruppennum);
	}
#endif	
}
