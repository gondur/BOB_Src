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

// RowanDialog: // GrpGesch.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "GrpGesch.h"
#include "cstring.h"
#include "..\mfc\resource.h"
#include "persons2.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// GroupGeschwader dialog


RDialog*	GroupGeschwader::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_GROUPS,new GroupGeschwader((SquadNum)0))
			);

}


GroupGeschwader::GroupGeschwader(int groupgeschwader, CWnd* pParent /*=NULL*/)
	: RowanDialog(GroupGeschwader::IDD, pParent)
{
	//{{AFX_DATA_INIT(GroupGeschwader)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	group = groupgeschwader;

}


void GroupGeschwader::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GroupGeschwader)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX, IDC_RSTATICCTRL7, m_IDC_RSTATICCTRL7);
	DDX_Control(pDX, IDC_RSTATICCTRL23, m_IDC_RSTATICCTRL23);
	DDX_Control(pDX, IDC_RLISTBOXCTRL2, m_IDC_RLISTBOXCTRL2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GroupGeschwader, CDialog)
	//{{AFX_MSG_MAP(GroupGeschwader)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GroupGeschwader message handlers

BEGIN_EVENTSINK_MAP(GroupGeschwader, CDialog)
    //{{AFX_EVENTSINK_MAP(GroupGeschwader)
	ON_EVENT(GroupGeschwader, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(GroupGeschwader, IDC_RLISTBOXCTRL2, 1 /* Select */, OnSelectRlistboxctrl2, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void GroupGeschwader::OnSelectRlistboxctrl1(long row, long column) 
{
#ifndef	BOB_DEMO_VER

	if (column == 0)
	{
		if (Airfields[row][0])
			TitleBarPtr().OpenTote(Airfields[row][0]);
	}else
	{
		if (Airfields[row][column])
			MainToolBar().OpenACDossier(Airfields[row][column],0);
	}
#endif
}

void	GroupGeschwader::RefreshGr13()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->ShowWindow(false);

	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL2);
	rlistbox->Clear();
	rlistbox->AddColumn(SQUADRONPLUSFIELDWIDTH);
	rlistbox->AddColumn(SQUADRONPLUSFIELDWIDTH);
		CRStatic*   s;
	
	s=GETDLGITEM(IDC_RSTATICCTRL7);
	s->ShowWindow(false);
	s=GETDLGITEM(IDC_RSTATICCTRL23);
	s->ShowWindow(false);
//RDH 02/06/99

	rlistbox->AddString(RESSTRING(HURRICANES),0);
	rlistbox->AddString(RESSTRING(SPITFIRES),1);

	FindAirfields();
	int k=0, numsq = 0;
	while (Node_Data.squadron[k].squadron != SQ_ZERO)
	{
 		if (Node_Data.squadron[k].homeairfield == Airfields[0][0])
		{
			int actype = Node_Data.squadron[k].AcType();
			int index = 0;
			if	(		(actype == PT_SPIT_A)
					||	(actype == PT_SPIT_B)
				)
				index = 1;
				
			rlistbox->AddString(Node_Data.squadron[k].SubName()+ " "+RESSTRING(SQUADRON),index);
		}

		k++;
	}


}


void	GroupGeschwader::RefreshRAF()
{
		CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL2);
	rlistbox->ShowWindow(false);
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode JIM 25Aug00 	rlistbox->Clear();
//DeadCode JIM 25Aug00 	rlistbox->AddColumn(SQUADRONPLUSFIELDWIDTH);
//DeadCode JIM 25Aug00 	rlistbox->AddColumn(SQUADRONPLUSFIELDWIDTH);										  //RDH 02/06/99
//DeadCode JIM 25Aug00 	rlistbox->AddColumn(SQUADRONPLUSFIELDWIDTH);										  //RDH 02/06/99
//DeadCode JIM 25Aug00 	rlistbox->AddColumn(SQUADRONPLUSFIELDWIDTH);										  //RDH 02/06/99
//DeadCode JIM 25Aug00 	rlistbox->AddColumn(SQUADRONPLUSFIELDWIDTH);										  //RDH 02/06/99

	FindAirfields();

	//print Sectoraf
	int af =0 ;
	while (Airfields[af][1] != UID_NULL)
	{
		TargetSectorField* afield;
		afield = Node_Data[Airfields[af][0]];

	 	CString afstring = "";
		if (Airfields[af][0])
			afstring= CString(TCHAR(afield->sectorname + '@'));//+ ": " + GetTargName(Airfields[af][0]);
		
		rlistbox->AddString(afstring,0);
		int i = 1;
		while (i < 5)
		{
			if (Airfields[af][i] == UID_NULL)
				rlistbox->AddString("",i);
			else
				PrintAirFieldInfo(af, i );
			i++;
		}
		af++;


	}		
	//print others

}

BOOL GroupGeschwader::OnInitDialog() 
{
	CDialog::OnInitDialog();
	


//DEADCODE RDH 09/12/99 	rlistbox->AddString("Northolt (5/6)",0);
//DEADCODE RDH 09/12/99 	rlistbox->AddString("Biggin Hill (5/6)",0);
//DEADCODE RDH 09/12/99 	rlistbox->AddString("Northolt (1/4)",1);
//DEADCODE RDH 09/12/99 	rlistbox->AddString("Heathrow (1/1)",2);
//DEADCODE RDH 09/12/99 	rlistbox->AddString("Hendon (1/2)",3);
//DEADCODE RDH 09/12/99 

	if (group == IDS_GROUP_13)
		RefreshGr13();
	else
		RefreshRAF();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void GroupGeschwader::PrintAirFieldInfo(int j, int i)
{
	TargetFighterField* af;
	af = Node_Data[Airfields[j][i]];
	CString maxstring = CSprintf("%i",af->maxsquads);

	int k=0, numsq = 0;
	while (Node_Data.squadron[k].squadron != SQ_ZERO)
	{
 		if (Node_Data.squadron[k].homeairfield == Airfields[j][i])
			numsq++;
		k++;
	}


 	CString afstring = "("+CSprintf("%i", numsq) +"/"+maxstring+") " + GetTargName(Airfields[j][i]);

	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->AddString(afstring,i);

}
int GroupGeschwader::FindSatellites(int afindex, int sectorindex)
{
	TargetFighterField* af = &Node_Data.sectorlist[sectorindex];
	int i = 1;
	int rowdelta=0;

	for (;af;af = af->nextsatelite())
	{
	   if (i>4)
	   {
		   rowdelta++;
		   i=1;
	   }
	   Airfields[afindex+rowdelta][i++]= af->uid;
	}
	return rowdelta+1;


}
void GroupGeschwader::FindAirfields()
{
	int i = 0;
	int j =0 ;
	while (i < MAX_SEC)
	{
		j = 0;
		while (j < MAX_AF)
		{
			Airfields[i][j++] = UID_NULL;
		}
		i++;
	}

	j = 0;
	i = 0;
	while (Node_Data.sectorlist[i].uid != UID_NULL)
	{
		if (Node_Data.sectorlist[i].groupname == group)
		{
			Airfields[j][0] = Node_Data.sectorlist[i].uid;
			int lines=FindSatellites(j, i);
			j++;
			while (--lines)
			{
				Airfields[j++][0]=UID_NULL;
			}
		}
		i++;
		
	}
	Airfields[j][0] = UID_NULL;
	Airfields[j][1] = UID_NULL;

}

void GroupGeschwader::OnSelectRlistboxctrl2(long row, long column) 
{
#ifndef	BOB_DEMO_VER

	int index =0;
	if (row > 0)
	{
		int k=0, numsq = 0;
		while (Node_Data.squadron[k].squadron != SQ_ZERO)
		{
 			if (Node_Data.squadron[k].homeairfield == Airfields[0][0])
			{
				int actype = Node_Data.squadron[k].AcType();
				int col = 0;
				if	(		(actype == PT_SPIT_A)
						||	(actype == PT_SPIT_B)
					)
					col = 1;
				if (column == col)
					index ++;
			}
		if (index == row)
			break;
		else
			k++;
		}
		if (index == row)
			MainToolBar().OpenACDossier(Airfields[0][0],Node_Data.squadron[k].squadron);
	}
#endif	
}
