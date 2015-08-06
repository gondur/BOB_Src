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

// RowanDialog: // ToteSect.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "ToteSect.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

int	ToteSector::readinesslevel[ToteSector::MAXTOTEOPTIONS] = 
{

		/*PS_OFFBASE*/				0,
		/*PS_ORDER_30*/				1,
		/*PS_AT_30*/				1,
		/*PS_ORDER_5*/				2,
		/*PS_AT_5*/					3,
		/*PS_ORDER_2*/				4,
		/*PS_AT_2*/					5,
		/*PS_PLANNING	*/			5,
		/*PS_ORDER_ONPOSITION,*/	6,
		/*PLAN 30*/					6,
		/*PLAN 5*/					6,
		/*PLAN 2*/					6,
		/*PS_ACTIVE_MIN,*/			6,
		/*PS_TAKINGOFF,*/			7,
		/*PS_FORMING,*/				7,
		/*PS_INCOMING,	*/			7,
		/*PS_INPOSITION*/			8,
		/*PS_DETAILRAID*/			9,
		/*PS_ENEMYSIGHTED,*/		10,
		/*PS_ORDERLAND,*/			11,
		/*PS_ACTIVE_MAX,*/			11,
		/*PS_LANDING,*/				11,
		/*PS_REFUELLING,*/			12,
		/*PS_COMPLETE*/				12,
};

/////////////////////////////////////////////////////////////////////////////
// ToteSector dialog


RDialog*	ToteSector::Make(UniqueID uid)
{
	return
		MakeTopDialog(::Place(POSN_MAX,POSN_MIN),
			DialBox(FIL_D_TOTEBOARD,new ToteSector(uid))
			);
}


ToteSector::ToteSector(UniqueID uid, CWnd* pParent /*=NULL*/)
	: RowanDialog(ToteSector::IDD, pParent)
{
	//{{AFX_DATA_INIT(ToteSector)
	//}}AFX_DATA_INIT
	sectoraf = uid;
}


void ToteSector::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ToteSector)
	DDX_Control(pDX, IDJ_TITLE, m_IDJ_TITLE);
	DDX_Control(pDX, IDC_RBUTTON_W0, m_IDC_RBUTTON_W0);
	DDX_Control(pDX, IDC_RBUTTON_B0, m_IDC_RBUTTON_B0);
	DDX_Control(pDX, IDC_RBUTTON_W1, m_IDC_RBUTTON_W1);
	DDX_Control(pDX, IDC_RBUTTON_B1, m_IDC_RBUTTON_B1);
	DDX_Control(pDX, IDC_RBUTTON_B2, m_IDC_RBUTTON_B2);
	DDX_Control(pDX, IDC_RBUTTON_B3, m_IDC_RBUTTON_B3);
	DDX_Control(pDX, IDC_RBUTTON_B4, m_IDC_RBUTTON_B4);
	DDX_Control(pDX, IDC_RBUTTON_W2, m_IDC_RBUTTON_W2);
	DDX_Control(pDX, IDC_RBUTTON_W3, m_IDC_RBUTTON_W3);
	DDX_Control(pDX, IDC_RBUTTON_W4, m_IDC_RBUTTON_W4);
	DDX_Control(pDX, IDC_RSTATIC_AC0, m_IDC_RSTATIC_AC0);
	DDX_Control(pDX, IDC_RSTATIC_PLT0, m_IDC_RSTATIC_PLT0);
	DDX_Control(pDX, IDC_RSTATICSQ0, m_IDC_RSTATICSQ0);
	DDX_Control(pDX, IDC_RSTATIC_PLT1, m_IDC_RSTATIC_PLT1);
	DDX_Control(pDX, IDC_RSTATIC_PLT2, m_IDC_RSTATIC_PLT2);
	DDX_Control(pDX, IDC_RSTATIC_PLT3, m_IDC_RSTATIC_PLT3);
	DDX_Control(pDX, IDC_RSTATIC_PLT4, m_IDC_RSTATIC_PLT4);
	DDX_Control(pDX, IDC_RSTATICSQ1, m_IDC_RSTATICSQ1);
	DDX_Control(pDX, IDC_RSTATICSQ2, m_IDC_RSTATICSQ2);
	DDX_Control(pDX, IDC_RSTATICSQ3, m_IDC_RSTATICSQ3);
	DDX_Control(pDX, IDC_RSTATICSQ4, m_IDC_RSTATICSQ4);
	DDX_Control(pDX, IDC_RSTATIC_AC1, m_IDC_RSTATIC_AC1);
	DDX_Control(pDX, IDC_RSTATIC_AC2, m_IDC_RSTATIC_AC2);
	DDX_Control(pDX, IDC_RSTATIC_AC3, m_IDC_RSTATIC_AC3);
	DDX_Control(pDX, IDC_RSTATIC_AC4, m_IDC_RSTATIC_AC4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ToteSector, CDialog)
	//{{AFX_MSG_MAP(ToteSector)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ToteSector message handlers
void ToteSector::RefreshData(int childnum)
{
	if (childnum == -2)
	{
		RefreshLights();
	}
}
extern UByte	Bit_Count_Nibble[];

void ToteSector::RefreshLights()
{
  
	CRect parentpos(1,1,0,0);
	GetWindowRect(parentpos);
	parentpos.top=1;
	CPoint parentoff(-parentpos.left,parentpos.top);
	
	
	enum{MAXSQUAD = 4, MAXAIRFIELDS = 10};
	SquadNum	squad[MAXSQUAD];
	UniqueID	Airfields[MAXAIRFIELDS];
	TargetFighterField* af = Node_Data[sectoraf];

	int m = 0;
	Airfields[m++] = sectoraf;
	while (		((af = af->nextsatelite())!= NULL)
				&&	(m < MAXAIRFIELDS)
		  )
	   Airfields[m++]= af->uid;
	while	(m < MAXAIRFIELDS)
		Airfields[m++]= UID_Null;

	int j=0, k = 0;
	m = 0;
	while (Node_Data.squadron[k].squadron != SQ_ZERO)
	{
		for (m = 0; m < MAXAIRFIELDS; m++)
		{
			if (Node_Data.squadron[k].homeairfield == Airfields[m])
			{
			  squad[j++] = Node_Data.squadron[k].squadron;
			}
		}
	  k++;
	}




	BritSquadron* sq;
	int  i =0;
	CRButton* bb;
	CRButton* bw;
	CRStatic*   sn;
	CRStatic*   sp;
	CRStatic*   sa;

	while (i < 5)
	{
		switch(i)
		{
			default_neverreferenced;
			case 0:
			{
				bw = GETDLGITEM(IDC_RBUTTON_W0);
				bb = GETDLGITEM(IDC_RBUTTON_B0);
				sn=GETDLGITEM(IDC_RSTATICSQ0);
				sp=GETDLGITEM(IDC_RSTATIC_PLT0);
				sa=GETDLGITEM(IDC_RSTATIC_AC0);
				break;
			}
			case 1:
			{
				bw = GETDLGITEM(IDC_RBUTTON_W1);
				bb = GETDLGITEM(IDC_RBUTTON_B1);
				sn=GETDLGITEM(IDC_RSTATICSQ1);
				sp=GETDLGITEM(IDC_RSTATIC_PLT1);
				sa=GETDLGITEM(IDC_RSTATIC_AC1);
				break;
			}
			case 2:
			{
				bw = GETDLGITEM(IDC_RBUTTON_W2);
				bb = GETDLGITEM(IDC_RBUTTON_B2);
				sn=GETDLGITEM(IDC_RSTATICSQ2);
				sp=GETDLGITEM(IDC_RSTATIC_PLT2);
				sa=GETDLGITEM(IDC_RSTATIC_AC2);
				break;
			}
			case 3:
			{
				bw = GETDLGITEM(IDC_RBUTTON_W3);
				bb = GETDLGITEM(IDC_RBUTTON_B3);
				sn=GETDLGITEM(IDC_RSTATICSQ3);
				sp=GETDLGITEM(IDC_RSTATIC_PLT3);
				sa=GETDLGITEM(IDC_RSTATIC_AC3);
				break;
			}
			case 4:
			{
				bw = GETDLGITEM(IDC_RBUTTON_W4);
				bb = GETDLGITEM(IDC_RBUTTON_B4);
				sn=GETDLGITEM(IDC_RSTATICSQ4);
				sp=GETDLGITEM(IDC_RSTATIC_PLT4);
				sa=GETDLGITEM(IDC_RSTATIC_AC4);
				break;
			}


		}

				if (i<j)
				{
					sq = Node_Data[squad[i]];

					sn->SetString(sq->SubName());
			
					sp->SetString(CSprintf("%i", sq->pilotsavail));

					sa->SetString(CSprintf("%i", sq->acavail));
				

					bw->ShowWindow(true);
					bb->ShowWindow(true);

					CRect dlistpos;
					bw->GetWindowRect(dlistpos);

					int status = sq->totestatus;
					int index = readinesslevel[status];
					if (index < 9)
						index = 76+ index *28;
					else
						index = 392 + ((index - 9) * 28);
					parentoff.y=parentpos.top+(index)-dlistpos.top;

					SLong hr, mins;
					hr = MMC.currtime / SECSPERHR;
					mins = ((MMC.currtime- (SECSPERHR * hr)) / SECSPERMIN);
					SWord ind = mins %15;
					ind = ind /5;
					ind = 3 - ind;
					if (sq->totestatus<Profile::PS_PLANNED)
					{
						int max=sq->acavail;
						if (max>sq->pilotsavail)
							max=sq->pilotsavail;
						if (max>15)
							max=15;
						max=max/3;
						dlistpos.right=dlistpos.left+(max*10);
						ind=0;
					}
					else
					{
						int availbits=sq->usedacbits;
						int avail = Bit_Count_Nibble[availbits&15];
						avail += Bit_Count_Nibble[(availbits>>4)&15];
						avail += Bit_Count_Nibble[(availbits>>8)&15];
						avail/=3;
						dlistpos.right=dlistpos.left+(avail*10);

					}
					dlistpos+=parentoff;
					bw->MoveWindow(dlistpos);
					
					bb->GetWindowRect(dlistpos);

					bb->SetNormalFileNum(ICON_BTOTE+ind-1);
					parentoff.y=parentpos.top+316+(ind*14)-dlistpos.top;
					dlistpos+=parentoff;
					bb->MoveWindow(dlistpos);
				}else
				{
					bw->ShowWindow(false);
					bb->ShowWindow(false);
					sn->SetString("");
					sp->SetString("");
					sa->SetString("");
				

				}
		i++;
	}

}

void ToteSector::RefreshTote()
{

 	
		RefreshLights();



}

BOOL ToteSector::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRButton* title;
	title = GETDLGITEM(IDJ_TITLE);

	title->SetString(GetTargName(sectoraf));

		
	RefreshTote();



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
