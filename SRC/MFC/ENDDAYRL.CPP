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

// RowanDialog: // EndDayRL.cpp : implementation file
//

#include "stdafx.h"
//DEADCODE RDH 14/03/00 #include "bob.h"
#include "_mfc.h"
#include "mytime.h"
#include "EndDayRL.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// EndOfDayReviewList dialog


RDialog*	EndOfDayReviewList::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new EndOfDayReviewList())
			);
}


EndOfDayReviewList::EndOfDayReviewList(CWnd* pParent /*=NULL*/)
	: RowanDialog(EndOfDayReviewList::IDD, pParent)
{
	//{{AFX_DATA_INIT(EndOfDayReviewList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void EndOfDayReviewList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EndOfDayReviewList)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EndOfDayReviewList, CDialog)
	//{{AFX_MSG_MAP(EndOfDayReviewList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EndOfDayReviewList message handlers

BEGIN_EVENTSINK_MAP(EndOfDayReviewList, CDialog)
    //{{AFX_EVENTSINK_MAP(EndOfDayReviewList)
	ON_EVENT(EndOfDayReviewList, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void EndOfDayReviewList::OnSelectRlistboxctrl1(long row, long column) 
{
#ifndef	BOB_DEMO_VER

	if (row > 0)
	{
		FullPanel()->ChangeReview(msglist[row-1]);
	}

#endif	
}
void EndOfDayReviewList::FillList()
{
	maxmsg = 0;

	if  (		(Node_Data.review.latest != Node_Data.review.B[IntelBuffer::Bwrap])
		)
	{
		int i = 0;
		int msg = Node_Data.review.latest;
		Node_Data.review.B[IntelBuffer::Bviewedupto] = msg;
		while (	(i < MAXMESSAGES)	&&	(msg != Node_Data.review.B[IntelBuffer::Bwrap]))
		{
			msglist[i] = msg;
			i++;
			msg--;
			if (msg < 0)
				msg = 255;
		}
		maxmsg = i;
	}

}
void EndOfDayReviewList::Refresh()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(60);
	rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
	rlistbox->AddString(RESSTRING(DATE),0);
	rlistbox->AddString(RESSTRING(TITLE),1);
	

	CString msgstr;
	for (int i = 0; i < maxmsg; i++)
	{
		rlistbox->AddString(GetDateName(Node_Data.review.messages[msglist[i]].time*SECSPERDAY, DATE_LONG),0);
		msgstr = Node_Data.review.MessageTitleToText(msglist[i]);
		rlistbox->AddString(msgstr,1);
	}

}


BOOL EndOfDayReviewList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FillList();
	Refresh();
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->SetHilightRow(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool	NodeData::GoToEndDayReview()
{
#ifndef	BOB_DEMO_VER
	MainToolBar().EndDayReview();
#endif
	return(true);
}
bool	NodeData::GoToEndDayRouting()
{
#ifndef	BOB_DEMO_VER
	MainToolBar().EndDayRouting();
#endif
	return(true);
}
