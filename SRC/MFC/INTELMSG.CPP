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

// RowanDialog: // IntellMsg.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "IntelMsg.h"
#include "mytime.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif


/////////////////////////////////////////////////////////////////////////////
// IntellMessages dialog


RDialog*	IntellMessages::Make(int msg)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_BLANK,new IntellMessages(msg))
			);
}


IntellMessages::IntellMessages(int msg, CWnd* pParent /*=NULL*/)
	: RowanDialog(IntellMessages::IDD, pParent)
{
	//{{AFX_DATA_INIT(IntellMessages)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	currmsg = msg;
}

void IntellMessages::RefreshData(int childnum)
{
	if (childnum == -2)
	{
		Refresh();
	}
}

void IntellMessages::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(IntellMessages)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX, IDC_RSTATICCTRL1, m_IDC_RSTATICCTRL1);
	DDX_Control(pDX, IDC_RBUTTONDETAILS, m_IDC_RBUTTONDETAILS);
	DDX_Control(pDX, IDC_RSTATICBODY, m_IDC_RSTATICBODY);
	DDX_Control(pDX, IDC_INTEL_ENGAGEMENT, m_IDC_INTEL_ENGAGEMENT);
	DDX_Control(pDX, IDC_INTEL_FLIGHT, m_IDC_INTEL_FLIGHT);
	DDX_Control(pDX, IDC_INTEL_MANAGEMENT, m_IDC_INTEL_MANAGEMENT);
	DDX_Control(pDX, IDC_INTEL_SPOTTING, m_IDC_INTEL_SPOTTING);
	DDX_Control(pDX, IDC_INTEL_TARGETSTATUS, m_IDC_INTEL_TARGETSTATUS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(IntellMessages, CDialog)
	//{{AFX_MSG_MAP(IntellMessages)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IntellMessages message handlers

void IntellMessages::FillList()
{
	maxmsg = 0;
	currmsgindex = -1;

	if  (		(Node_Data.intel.latest != Node_Data.intel.B[IntelBuffer::Bwrap])
		)
	{
		int i = 0;
		int msg = Node_Data.intel.latest;
		while	(	(i < MAXMESSAGES)	&&	(msg != Node_Data.intel.B[IntelBuffer::Bwrap])	)
		{
			if(msg == currmsg)
				currmsgindex = i;
			if (!MMC.intel[Node_Data.intel.messages[msg].pva.about])
			{
				msglist[i] = msg;
			i++;
			}
			msg--;
			if (msg < 0)
				msg = Node_Data.intel.BUFFERSIZE-1;										//JIM 5Sep00
		}
		maxmsg = i;
	}
	if (currmsgindex == -1)
	{
		if	(maxmsg>0)
		{
			currmsgindex = 0;
			currmsg = msglist[currmsgindex];
		}else
			currmsg = -1;
	}

}
void IntellMessages::RefreshHilight()
{
	CRStatic*   s;
	s=GETDLGITEM(IDC_RSTATICBODY);
	CString msgstr;
	if (currmsg >= 0)
		msgstr = Node_Data.intel.MessageBodyToText(currmsg);
	else
		msgstr ="";
	s->SetString(msgstr);

	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->SetHilightRow(currmsgindex+1);


	CRButton* but;
	but = GETDLGITEM(IDC_RBUTTONDETAILS);
	if (		(currmsg >= 0)	
			&&	(Node_Data.intel.messages[currmsg].what != UID_NULL)
			&&	((Node_Data.intel.messages[currmsg].what&(UID_BIT15+UID_BIT14))==0)
			&&	(currmsgindex < maxmsg)
		)
	{
		but->SetForeColor(RGB(255,255,0));
		but->SetDisabled(false);

	}else
	{
		but->SetForeColor(RGB(80,80,0));
		but->SetDisabled(true);
	}



}
void IntellMessages::Refresh()
{

	CRButton* b;
	//FLIGHT,ENGAGEMENT,SPOTTING,TARGETSTATUS,MANAGEMENT
	b = GETDLGITEM(IDC_INTEL_ENGAGEMENT);
	b->SetPressed(!MMC.intel[IntelMsg::ENGAGEMENT]);
	b = GETDLGITEM(IDC_INTEL_FLIGHT);
	b->SetPressed(!MMC.intel[IntelMsg::FLIGHT]);
	b = GETDLGITEM(IDC_INTEL_MANAGEMENT);
	b->SetPressed(!MMC.intel[IntelMsg::MANAGEMENT]);
	b = GETDLGITEM(IDC_INTEL_SPOTTING);
	b->SetPressed(!MMC.intel[IntelMsg::SPOTTING]);
	b = GETDLGITEM(IDC_INTEL_TARGETSTATUS);
	b->SetPressed(!MMC.intel[IntelMsg::TARGETSTATUS]);


 	FillList();


	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(60);
	rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
	rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
	rlistbox->AddString(RESSTRING(TIME),0);
	rlistbox->AddString(RESSTRING(LOCATION),1);
	rlistbox->AddString(RESSTRING(MESSAGE),2);
	

	CString msgstr;
	for (int i = 0; i < maxmsg; i++)
	{
		rlistbox->AddString(GetTimeName(Node_Data.intel.messages[msglist[i]].time+HR04),0);

		UniqueID uid = Node_Data.intel.messages[msglist[i]].what;
		if (uid)
			rlistbox->AddString(GetTargName(uid),1);
		else
			rlistbox->AddString("",1);
		msgstr = Node_Data.intel.MessageTitleToText(msglist[i]);
		rlistbox->AddString(msgstr,2);
	}

		RefreshHilight();


}


BOOL IntellMessages::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//for currmsg to come through from intel we need to turn on all filters
//DeadCode JIM 9Sep00 	   MMC.intelengagement = false;
//DeadCode JIM 9Sep00 	   MMC.intelflight = false;
//DeadCode JIM 9Sep00 	   MMC.intelmanagement = false;
//DeadCode JIM 9Sep00 	   MMC.intelspotting = false;
//DeadCode JIM 9Sep00  	   MMC.inteltargetstatus = false;



	Refresh();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(IntellMessages, CDialog)
    //{{AFX_EVENTSINK_MAP(IntellMessages)
	ON_EVENT(IntellMessages, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(IntellMessages, IDC_INTEL_ENGAGEMENT, 1 /* Clicked */, OnClickedIntelEngagement, VTS_NONE)
	ON_EVENT(IntellMessages, IDC_INTEL_FLIGHT, 1 /* Clicked */, OnClickedIntelFlight, VTS_NONE)
	ON_EVENT(IntellMessages, IDC_INTEL_MANAGEMENT, 1 /* Clicked */, OnClickedIntelManagement, VTS_NONE)
	ON_EVENT(IntellMessages, IDC_INTEL_SPOTTING, 1 /* Clicked */, OnClickedIntelSpotting, VTS_NONE)
	ON_EVENT(IntellMessages, IDC_INTEL_TARGETSTATUS, 1 /* Clicked */, OnClickedIntelTargetstatus, VTS_NONE)
	ON_EVENT(IntellMessages, IDC_RBUTTONDETAILS, 1 /* Clicked */, OnClickedRbuttondetails, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void IntellMessages::OnSelectRlistboxctrl1(long row, long column) 
{	//Rod will have inverted this code.
	if (row > 0)
		currmsgindex = row -1;
	else
		currmsgindex =0;
	currmsg = msglist[currmsgindex];
	RefreshHilight();




}
 	//FLIGHT,ENGAGEMENT,SPOTTING,TARGETSTATUS,MANAGEMENT

void IntellMessages::OnClickedIntelEngagement() 
{
	if	(MMC.intel[IntelMsg::ENGAGEMENT])
	   MMC.intel[IntelMsg::ENGAGEMENT] = false;
	else
	   MMC.intel[IntelMsg::ENGAGEMENT] = true;
	Refresh();
	
}

void IntellMessages::OnClickedIntelFlight() 
{
	if	(MMC.intel[IntelMsg::FLIGHT])
	   MMC.intel[IntelMsg::FLIGHT] = false;
	else
	   MMC.intel[IntelMsg::FLIGHT] = true;
	Refresh();
	
}

void IntellMessages::OnClickedIntelManagement() 
{
	if	(MMC.intel[IntelMsg::MANAGEMENT])
	   MMC.intel[IntelMsg::MANAGEMENT] = false;
	else
	   MMC.intel[IntelMsg::MANAGEMENT] = true;
	Refresh();
	
}

void IntellMessages::OnClickedIntelSpotting() 
{
	if	(MMC.intel[IntelMsg::SPOTTING])
	   MMC.intel[IntelMsg::SPOTTING] = false;
	else
	   MMC.intel[IntelMsg::SPOTTING] = true;
	Refresh();
	
}

void IntellMessages::OnClickedIntelTargetstatus() 
{
	if	(MMC.intel[IntelMsg::TARGETSTATUS])
	   MMC.intel[IntelMsg::TARGETSTATUS] = false;
	else
	   MMC.intel[IntelMsg::TARGETSTATUS] = true;
	Refresh();
	
}

void IntellMessages::OnClickedRbuttondetails() 
{
#ifndef	BOB_DEMO_VER

	UniqueID item=Node_Data.intel.messages[currmsg].what;
	if (item&(UID_BIT15+UID_BIT14))										//CSB 12Jul00
		return;															//CSB 12Jul00
	UniqueIDBand	uidband=Persons2::getbandfromUID(item);

	if (uidband==SagBAND)
	{
		int packnum,sqline;
		if (Todays_Packages.GetACSquadEntry(item,packnum,sqline))
		{
			RDialog::m_pView->SetHiLightInfo(packnum, sqline,UID_Null);
			Invalidate();
			if (Todays_Packages.localplayer==NAT_RAF)
			{
				if (Todays_Packages[packnum].attackmethod>=Profile::AM_LWPACKS)
				{//lw
					MainToolBar().OnClickedHostileslist();
				}else
				{
					MainToolBar().OnClickedMissionfolder();
				}

			}else
			{
				if (Todays_Packages[packnum].attackmethod>=Profile::AM_LWPACKS)
				{//lw
					MainToolBar().OnClickedMissionfolder();
				}
			}

		}
	}else
		MainToolBar().OpenDossier(item);
#endif	
}
