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

// RowanDialog: // AfDossr.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "AfDossr.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// AirfieldDossier dialog
										

RDialog*	AirfieldDossier::Make(int item, int gruppe)
{
	DialBox* ND = NULL;
	CString	tabtitle[6];
	int numopts = 0;
	enum{MAXSQUAD = 4};

	UniqueID afuid = (UniqueID) item;
//DEADCODE  11/02/00 	ItemPtr p=Persons2::ConvertPtrUID(afuid);
//DEADCODE  11/02/00 	if (p->SGT)
//DEADCODE  11/02/00 		afuid=p->SGT;

//DEADCODE  09/02/00 	if (Todays_Packages[Todays_Packages.hipack].attackmethod >= Profile::AM_LWPACKS) 
	if (item<Squadron::WN_LAST)	//RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)	//AM 10Oct00
	{	//LW:	item is wadernum(0-3 or 1-4). Gruppe is gruppennum

		tabtitle[0] = RESSTRING(GRUPPEI); 
		tabtitle[1] = RESSTRING(GRUPPEII); 
		tabtitle[2] = RESSTRING(GRUPPEIII);
		int j=0, i = 0;
		UByte	squad[MAXSQUAD];

		while (Node_Data.gruppe[i].squadron != SQ_ZERO)
		{
		  if (Node_Data.gruppe[i].wadernum == item)
		  {
			  squad[numopts++] = Node_Data.gruppe[i].squadron;
		  }
		  i++;
		}


		return
			MakeTopDialog(::Place(POSN_MIN,POSN_MAX),
					DialList(DialBox(FIL_NULL,new AirfieldDossier(afuid, gruppe),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
						HTabBox(FIL_NULL,IdList(tabtitle[0],tabtitle[1],tabtitle[2]),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
							DialBox(FIL_D_GRUPPEDETAILS,new SquadronDetails((SquadNum)squad[0])),
							DialBox(FIL_D_GRUPPEDETAILS,new SquadronDetails((SquadNum)squad[1])),
							DialBox(FIL_D_GRUPPEDETAILS,new SquadronDetails((SquadNum)squad[2]))

										)	)	);
	}else
	{	//RAF:	item is UID, Gruppe is either tab number or squad number
//DeadCode JIM 23Oct00 		UniqueID	gr13;
//DeadCode JIM 23Oct00 		int i =0;
//DeadCode JIM 23Oct00 		while (Node_Data.sectorlist[i].uid != UID_NULL)
//DeadCode JIM 23Oct00 		{
//DeadCode JIM 23Oct00 			if (Node_Data.sectorlist[i].groupname == IDS_GROUP_13)
//DeadCode JIM 23Oct00 				gr13 = Node_Data.sectorlist[i].uid;
//DeadCode JIM 23Oct00 		i++;
//DeadCode JIM 23Oct00 		}

		if ((UniqueID)afuid == UID_AF_NEWCASTLE)
		{

			BritSquadron* sq = Node_Data[(SquadNum)gruppe];
			tabtitle[0] = sq->SubName()+ " "+RESSTRING(SQUADRON);
			numopts = 1;
			return
//DEADCODE  14/02/00 				MakeTopDialog(::Place(POSN_MIN,POSN_MAX),
//DEADCODE  14/02/00 						DialList(DialBox(FIL_NULL,new AirfieldDossier(afuid, gruppe),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//DEADCODE  14/02/00 							HTabBox(FIL_NULL,IdList(tabtitle[0],tabtitle[1],tabtitle[2],tabtitle[3],tabtitle[4],tabtitle[5]),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
//DEADCODE  14/02/00 								DialBox(FIL_D_SQUADDETAILS,new SquadronDetails((SquadNum)gruppe))
//DEADCODE  14/02/00 
//DEADCODE  14/02/00 											)	)	);
				MakeTopDialog(::Place(POSN_MIN,POSN_MAX),
						DialList(DialBox(FIL_NULL,new AirfieldDossier(afuid, gruppe),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
								DialBox(FIL_D_SQUADDETAILS,new SquadronDetails((SquadNum)gruppe))

												)	);
		}else
		{
			ItemPtr p=Persons2::ConvertPtrUID(afuid);
			if (p->SGT)
				afuid=p->SGT;

			SquadNum	squad[MAXSQUAD];
			int j=0, i = 0;
			while ((numopts < MAXSQUAD) && (Node_Data.squadron[i].squadron != SQ_ZERO))
			{
			  if (Node_Data.squadron[i].homeairfield == afuid)
			  {
				  numopts++;
				  squad[j++] = Node_Data.squadron[i].squadron;
			  }
			  i++;
			 }


			tabtitle[0] = RESSTRING(GENERAL); 
			tabtitle[1] = RESSTRING(DAMAGE);

			for (i=0; i<numopts; i++)
			{
				BritSquadron* sq = Node_Data[squad[i]];
				tabtitle[2+i] = sq->SubName();

			}
			return
				MakeTopDialog(::Place(POSN_MIN,POSN_MAX),
						DialList(DialBox(FIL_NULL,new AirfieldDossier(afuid, gruppe),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
							HTabBox(FIL_NULL,IdList(tabtitle[0],tabtitle[1],tabtitle[2],tabtitle[3],tabtitle[4],tabtitle[5]),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
								DialBox(FIL_D_SQUADDETAILS,new AirfieldDetails(afuid)),
								DialBox(FIL_D_DAMAGE,new CDamage(afuid, (UniqueID) item)),
								(numopts>0)?DialBox(FIL_D_SQUADDETAILS,new SquadronDetails(squad[0]), Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)):*ND,
								(numopts>1)?DialBox(FIL_D_SQUADDETAILS,new SquadronDetails(squad[1])):*ND,
								(numopts>2)?DialBox(FIL_D_SQUADDETAILS,new SquadronDetails(squad[2])):*ND,
								(numopts>3)?DialBox(FIL_D_SQUADDETAILS,new SquadronDetails(squad[3])):*ND
											)	)	);

		}
	}
}


AirfieldDossier::AirfieldDossier(UniqueID afuid, int gruppe, CWnd* pParent /*=NULL*/)
	: RowanDialog(AirfieldDossier::IDD, pParent)
{
	//{{AFX_DATA_INIT(AirfieldDossier)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	uid = afuid;
	sqgruppe = gruppe;
}


void AirfieldDossier::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AirfieldDossier)
	DDX_Control(pDX, IDJ_TITLE, m_IDJ_TITLE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AirfieldDossier, CDialog)
	//{{AFX_MSG_MAP(AirfieldDossier)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AirfieldDossier message handlers

BOOL AirfieldDossier::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRButton* title;
	title = GETDLGITEM(IDJ_TITLE);

//DEADCODE  14/02/00 	if (Todays_Packages[Todays_Packages.hipack].attackmethod >= Profile::AM_LWPACKS) 
 	if (uid<Squadron::WN_LAST)	//RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)	//AM 10Oct00
	{
		CString string;
		string =   	RESLIST(JAGDGESCH, Node_Data.geschwader[(int)uid].wadername) +" " 
							+ CSprintf("%i",	Node_Data.geschwader[(int)uid].wadernum); 

	 	title->SetString(string);
	}else
	{
		if (uid == UID_AF_NEWCASTLE)
		{
			BritSquadron* sq = Node_Data[(SquadNum)sqgruppe];
			title->SetString(sq->SubName()+ " "+RESSTRING(SQUADRON));
		}else
		 	title->SetString(GetTargName(uid));
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
