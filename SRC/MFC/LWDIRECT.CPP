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

// RowanDialog: // LWDirect.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "LWDirect.h"
#include "mytime.h"
#include "mymath.h"
static const Float truncingfix=0.000001;
#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

BITABLE(Profile::BetterRule);
ADDORABLE(Profile::BetterRule);
/////////////////////////////////////////////////////////////////////////////
// LWDirectives dialog

//NOTE
//NOTE		The first mission type was initially reconn. This was allocated slot 0
//NOTE		Slots now start at 1										//RDH 27/04/00
//NOTE
//NOTE
//NOTE
//NOTE
//NOTE
//NOTE
RDialog*	LWDirectives::Make(LWDirectivesResults* dirres)
{


	
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_LWDIRECTIVES,new LWDirectives(dirres))
			);
}

//DeadCode RDH 08Feb00 struct	LWDirectives::Targets
//DeadCode RDH 08Feb00 {
//DeadCode RDH 08Feb00 	LWDirectivesResultsTargetList target[LWDirectivesResultsTargetList::MAX_TARGETS];
//DeadCode RDH 08Feb00 	LWDirectivesResultsTargetList& operator[](int i) {return target[i];}
//DeadCode RDH 08Feb00 };

LWDirectives::LWDirectives(LWDirectivesResults* dirres, CWnd* pParent /*=NULL*/)
	: RowanDialog(LWDirectives::IDD, pParent)
//DeadCode RDH 08Feb00 		,
//DeadCode RDH 08Feb00 	target(*new Targets),
//DeadCode RDH 08Feb00 	trgarray(new Targets[8])
{
	//{{AFX_DATA_INIT(LWDirectives)
	//}}AFX_DATA_INIT
	dr = dirres; 
	if (dr == NULL)
	{
		dr = new LWDirectivesResults;
		dr->tempdir = MMC.directives.lw.current; 
	}
//DeadCode JIM 10Oct00 	if (MMC.currtime>AFTERNOONPERIODSTART)
//DeadCode JIM 10Oct00 		MMC.currperiodtime  = AFTERNOONPERIODSTART;
//DeadCode JIM 10Oct00 	else if (MMC.currtime > MIDDAYPERIODSTART)
//DeadCode JIM 10Oct00 		MMC.currperiodtime = MIDDAYPERIODSTART;
//DeadCode JIM 10Oct00 	else
//DeadCode JIM 10Oct00 		MMC.currperiodtime = MORNINGPERIODSTART;
	ininitdialog=false;

}
LWDirectives::~LWDirectives()
{
	if (dr)
		delete dr;
//DeadCode RDH 08Feb00 	delete	&target;
//DeadCode RDH 08Feb00 	delete []trgarray;
}

void LWDirectives::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LWDirectives)
	DDX_Control(pDX,IDC_RCOMBO_TIMING,m_IDC_RCOMBO_TIMING);
	DDX_Control(pDX,IDC_RSPINBUT_MORN,m_IDC_RSPINBUT_MORN);
	DDX_Control(pDX,IDC_RSPINBUT_MID,m_IDC_RSPINBUT_MID);
	DDX_Control(pDX, IDC_RSPINBUT_JU870, m_IDC_RSPINBUT_JU870);
	DDX_Control(pDX, IDC_RSPINBUT_JU871, m_IDC_RSPINBUT_JU871);
	DDX_Control(pDX, IDC_RSPINBUT_JU872, m_IDC_RSPINBUT_JU872);
	DDX_Control(pDX, IDC_RSPINBUT_JU873, m_IDC_RSPINBUT_JU873);
	DDX_Control(pDX, IDC_RSPINBUT_JU874, m_IDC_RSPINBUT_JU874);
	DDX_Control(pDX, IDC_RSPINBUT_JU875, m_IDC_RSPINBUT_JU875);
	DDX_Control(pDX, IDC_RSPINBUT_JU876, m_IDC_RSPINBUT_JU876);
	DDX_Control(pDX, IDC_RSPINBUT_JU877, m_IDC_RSPINBUT_JU877);
	DDX_Control(pDX, IDC_RSPINBUT_JU878, m_IDC_RSPINBUT_JU878);
	DDX_Control(pDX, IDC_RSPINBUT_JU88_0, m_IDC_RSPINBUT_JU88_0);
	DDX_Control(pDX, IDC_RSPINBUT_JU88_1, m_IDC_RSPINBUT_JU88_1);
	DDX_Control(pDX, IDC_RSPINBUT_JU88_2, m_IDC_RSPINBUT_JU88_2);
	DDX_Control(pDX, IDC_RSPINBUT_JU88_3, m_IDC_RSPINBUT_JU88_3);
	DDX_Control(pDX, IDC_RSPINBUT_JU88_4, m_IDC_RSPINBUT_JU88_4);
	DDX_Control(pDX, IDC_RSPINBUT_JU88_5, m_IDC_RSPINBUT_JU88_5);
	DDX_Control(pDX, IDC_RSPINBUT_JU88_6, m_IDC_RSPINBUT_JU88_6);
	DDX_Control(pDX, IDC_RSPINBUT_JU88_7, m_IDC_RSPINBUT_JU88_7);
	DDX_Control(pDX, IDC_RSPINBUT_JU88_8, m_IDC_RSPINBUT_JU88_8);
	DDX_Control(pDX, IDC_RSPINBUT_HE1110, m_IDC_RSPINBUT_HE1110);
	DDX_Control(pDX, IDC_RSPINBUT_HE1111, m_IDC_RSPINBUT_HE1111);
	DDX_Control(pDX, IDC_RSPINBUT_HE1112, m_IDC_RSPINBUT_HE1112);
	DDX_Control(pDX, IDC_RSPINBUT_HE1113, m_IDC_RSPINBUT_HE1113);
	DDX_Control(pDX, IDC_RSPINBUT_HE1114, m_IDC_RSPINBUT_HE1114);
	DDX_Control(pDX, IDC_RSPINBUT_HE1115, m_IDC_RSPINBUT_HE1115);
	DDX_Control(pDX, IDC_RSPINBUT_HE1116, m_IDC_RSPINBUT_HE1116);
	DDX_Control(pDX, IDC_RSPINBUT_HE1117, m_IDC_RSPINBUT_HE1117);
	DDX_Control(pDX, IDC_RSPINBUT_HE1118, m_IDC_RSPINBUT_HE1118);
	DDX_Control(pDX, IDC_RSPINBUT_DO17_0, m_IDC_RSPINBUT_DO17_0);
	DDX_Control(pDX, IDC_RSPINBUT_DO17_1, m_IDC_RSPINBUT_DO17_1);
	DDX_Control(pDX, IDC_RSPINBUT_DO17_2, m_IDC_RSPINBUT_DO17_2);
	DDX_Control(pDX, IDC_RSPINBUT_DO17_3, m_IDC_RSPINBUT_DO17_3);
	DDX_Control(pDX, IDC_RSPINBUT_DO17_4, m_IDC_RSPINBUT_DO17_4);
	DDX_Control(pDX, IDC_RSPINBUT_DO17_5, m_IDC_RSPINBUT_DO17_5);
	DDX_Control(pDX, IDC_RSPINBUT_DO17_6, m_IDC_RSPINBUT_DO17_6);
	DDX_Control(pDX, IDC_RSPINBUT_DO17_7, m_IDC_RSPINBUT_DO17_7);
	DDX_Control(pDX, IDC_RSPINBUT_DO17_8, m_IDC_RSPINBUT_DO17_8);
	DDX_Control(pDX, IDC_RSPINBUT_ME109_0, m_IDC_RSPINBUT_ME109_0);
	DDX_Control(pDX, IDC_RSPINBUT_ME109_1, m_IDC_RSPINBUT_ME109_1);
	DDX_Control(pDX, IDC_RSPINBUT_ME109_2, m_IDC_RSPINBUT_ME109_2);
	DDX_Control(pDX, IDC_RSPINBUT_ME109_3, m_IDC_RSPINBUT_ME109_3);
	DDX_Control(pDX, IDC_RSPINBUT_ME109_4, m_IDC_RSPINBUT_ME109_4);
	DDX_Control(pDX, IDC_RSPINBUT_ME109_5, m_IDC_RSPINBUT_ME109_5);
	DDX_Control(pDX, IDC_RSPINBUT_ME109_6, m_IDC_RSPINBUT_ME109_6);
	DDX_Control(pDX, IDC_RSPINBUT_ME109_7, m_IDC_RSPINBUT_ME109_7);
	DDX_Control(pDX, IDC_RSPINBUT_ME109_8, m_IDC_RSPINBUT_ME109_8);
	DDX_Control(pDX, IDC_RSPINBUT_ME1100, m_IDC_RSPINBUT_ME1100);
	DDX_Control(pDX, IDC_RSPINBUT_ME1101, m_IDC_RSPINBUT_ME1101);
	DDX_Control(pDX, IDC_RSPINBUT_ME1102, m_IDC_RSPINBUT_ME1102);
	DDX_Control(pDX, IDC_RSPINBUT_ME1103, m_IDC_RSPINBUT_ME1103);
	DDX_Control(pDX, IDC_RSPINBUT_ME1104, m_IDC_RSPINBUT_ME1104);
	DDX_Control(pDX, IDC_RSPINBUT_ME1105, m_IDC_RSPINBUT_ME1105);
	DDX_Control(pDX, IDC_RSPINBUT_ME1106, m_IDC_RSPINBUT_ME1106);
	DDX_Control(pDX, IDC_RSPINBUT_ME1107, m_IDC_RSPINBUT_ME1107);
	DDX_Control(pDX, IDC_RSPINBUT_ME1108, m_IDC_RSPINBUT_ME1108);
	DDX_Control(pDX, IDC_RSPINBUT_FREE_0, m_IDC_RSPINBUT_FREE_0);
	DDX_Control(pDX, IDC_RSPINBUT_FREE_1, m_IDC_RSPINBUT_FREE_1);
	DDX_Control(pDX, IDC_RSPINBUT_FREE_2, m_IDC_RSPINBUT_FREE_2);
	DDX_Control(pDX, IDC_RSPINBUT_FREE_3, m_IDC_RSPINBUT_FREE_3);
	DDX_Control(pDX, IDC_RSPINBUT_FREE_4, m_IDC_RSPINBUT_FREE_4);
	DDX_Control(pDX, IDC_RSPINBUT_FREE_5, m_IDC_RSPINBUT_FREE_5);
	DDX_Control(pDX, IDC_RSPINBUT_FREE_6, m_IDC_RSPINBUT_FREE_6);
	DDX_Control(pDX, IDC_RSPINBUT_FREE_7, m_IDC_RSPINBUT_FREE_7);
	DDX_Control(pDX, IDC_RSPINBUT_FREE_8, m_IDC_RSPINBUT_FREE_8);
	DDX_Control(pDX, IDC_RSPINBUT_TIED_0, m_IDC_RSPINBUT_TIED_0);
	DDX_Control(pDX, IDC_RSPINBUT_TIED_1, m_IDC_RSPINBUT_TIED_1);
	DDX_Control(pDX, IDC_RSPINBUT_TIED_2, m_IDC_RSPINBUT_TIED_2);
	DDX_Control(pDX, IDC_RSPINBUT_TIED_3, m_IDC_RSPINBUT_TIED_3);
	DDX_Control(pDX, IDC_RSPINBUT_TIED_4, m_IDC_RSPINBUT_TIED_4);
	DDX_Control(pDX, IDC_RSPINBUT_TIED_5, m_IDC_RSPINBUT_TIED_5);
	DDX_Control(pDX, IDC_RSPINBUT_TIED_6, m_IDC_RSPINBUT_TIED_6);
	DDX_Control(pDX, IDC_RSPINBUT_TIED_7, m_IDC_RSPINBUT_TIED_7);
	DDX_Control(pDX, IDC_RSPINBUT_TIED_8, m_IDC_RSPINBUT_TIED_8);
	DDX_Control(pDX, IDC_RSPINBUT_SIZE_0, m_IDC_RSPINBUT_SIZE_0);
	DDX_Control(pDX, IDC_RSPINBUT_SIZE_1, m_IDC_RSPINBUT_SIZE_1);
	DDX_Control(pDX, IDC_RSPINBUT_SIZE_2, m_IDC_RSPINBUT_SIZE_2);
	DDX_Control(pDX, IDC_RSPINBUT_SIZE_3, m_IDC_RSPINBUT_SIZE_3);
	DDX_Control(pDX, IDC_RSPINBUT_SIZE_4, m_IDC_RSPINBUT_SIZE_4);
	DDX_Control(pDX, IDC_RSPINBUT_SIZE_5, m_IDC_RSPINBUT_SIZE_5);
	DDX_Control(pDX, IDC_RSPINBUT_SIZE_6, m_IDC_RSPINBUT_SIZE_6);
	DDX_Control(pDX, IDC_RSPINBUT_SIZE_7, m_IDC_RSPINBUT_SIZE_7);
	DDX_Control(pDX, IDC_RSPINBUT_SIZE_8, m_IDC_RSPINBUT_SIZE_8);
	DDX_Control(pDX, IDC_RSTATIC_MISSIONS_0, m_IDC_RSTATIC_MISSIONS_0);
	DDX_Control(pDX, IDC_RSTATIC_MISSIONS_1, m_IDC_RSTATIC_MISSIONS_1);
	DDX_Control(pDX, IDC_RSTATIC_MISSIONS_2, m_IDC_RSTATIC_MISSIONS_2);
	DDX_Control(pDX, IDC_RSTATIC_MISSIONS_3, m_IDC_RSTATIC_MISSIONS_3);
	DDX_Control(pDX, IDC_RSTATIC_MISSIONS_4, m_IDC_RSTATIC_MISSIONS_4);
	DDX_Control(pDX, IDC_RSTATIC_MISSIONS_5, m_IDC_RSTATIC_MISSIONS_5);
	DDX_Control(pDX, IDC_RSTATIC_MISSIONS_6, m_IDC_RSTATIC_MISSIONS_6);
	DDX_Control(pDX, IDC_RSTATIC_MISSIONS_7, m_IDC_RSTATIC_MISSIONS_7);
	DDX_Control(pDX, IDC_RSTATIC_MISSIONS_8, m_IDC_RSTATIC_MISSIONS_8);
	DDX_Control(pDX, IDC_BOMBER_AFTER, m_IDC_BOMBER_AFTER);
	DDX_Control(pDX, IDC_ALLOW2_0, m_IDC_ALLOW2_0);
	DDX_Control(pDX, IDC_ALLOW2_1, m_IDC_ALLOW2_1);
	DDX_Control(pDX, IDC_ALLOW2_2, m_IDC_ALLOW2_2);
	DDX_Control(pDX, IDC_ALLOW2_3, m_IDC_ALLOW2_3);
	DDX_Control(pDX, IDC_ALLOW2_4, m_IDC_ALLOW2_4);
	DDX_Control(pDX, IDC_ALLOW2_5, m_IDC_ALLOW2_5);
	DDX_Control(pDX, IDC_ALLOW2_6, m_IDC_ALLOW2_6);
	DDX_Control(pDX, IDC_ALLOW2_7, m_IDC_ALLOW2_7);
	DDX_Control(pDX, IDC_STRAF_0, m_IDC_STRAF_0);
	DDX_Control(pDX, IDC_STRAF_1, m_IDC_STRAF_1);
	DDX_Control(pDX, IDC_STRAF_2, m_IDC_STRAF_2);
	DDX_Control(pDX, IDC_STRAF_3, m_IDC_STRAF_3);
	DDX_Control(pDX, IDC_STRAF_4, m_IDC_STRAF_4);
	DDX_Control(pDX, IDC_STRAF_5, m_IDC_STRAF_5);
	DDX_Control(pDX, IDC_STRAF_6, m_IDC_STRAF_6);
	DDX_Control(pDX, IDC_STRAF_7, m_IDC_STRAF_7);
	DDX_Control(pDX, IDC_TICK_A0, m_IDC_TICK_A0);
	DDX_Control(pDX, IDC_TICK_A1, m_IDC_TICK_A1);
	DDX_Control(pDX, IDC_TICK_A2, m_IDC_TICK_A2);
	DDX_Control(pDX, IDC_TICK_A3, m_IDC_TICK_A3);
	DDX_Control(pDX, IDC_TICK_A4, m_IDC_TICK_A4);
	DDX_Control(pDX, IDC_TICK_A5, m_IDC_TICK_A5);
	DDX_Control(pDX, IDC_TICK_D0, m_IDC_TICK_D0);
	DDX_Control(pDX, IDC_TICK_D1, m_IDC_TICK_D1);
	DDX_Control(pDX, IDC_TICK_D2, m_IDC_TICK_D2);
	DDX_Control(pDX, IDC_TICK_D3, m_IDC_TICK_D3);
	DDX_Control(pDX, IDC_TICK_D4, m_IDC_TICK_D4);
	DDX_Control(pDX, IDC_TICK_D5, m_IDC_TICK_D5);
	DDX_Control(pDX, IDC_RSPINBUT_RECONN_MISSIONS, m_IDC_RSPINBUT_RECONN_MISSIONS);
	DDX_Control(pDX, IDC_RSPINBUT_RECONN_AIRCRAFT, m_IDC_RSPINBUT_RECONN_AIRCRAFT);
	DDX_Control(pDX, IDC_RECONN_AMONLY, m_IDC_RECONN_AMONLY);
	DDX_Control(pDX, IDC_RECONN_ESCORT, m_IDC_RECONN_ESCORT);
	DDX_Control(pDX, IDC_RSTATIC_RECONN_MISSIONS, m_IDC_RSTATIC_RECONN_MISSIONS);
	DDX_Control(pDX, IDC_ESCORT_PROPORTION, m_IDC_ESCORT_PROPORTION);
	DDX_Control(pDX, IDC_JU87_PERIOD, m_IDC_JU87_PERIOD);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LWDirectives, CDialog)
	//{{AFX_MSG_MAP(LWDirectives)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LWDirectives message handlers

BEGIN_EVENTSINK_MAP(LWDirectives, CDialog)
    //{{AFX_EVENTSINK_MAP(LWDirectives)
	ON_EVENT(LWDirectives, IDC_RSPINBUT_MORN, 1 /* TextChanged */, OnTextChangedMorn, VTS_BSTR VTS_I2)
	ON_EVENT(LWDirectives, IDC_RSPINBUT_MID, 1 /* TextChanged */, OnTextChangedMid, VTS_BSTR VTS_I2)
	ON_EVENT(LWDirectives, IDC_RCOMBO_TIMING, 1 /* TextChanged */, OnTextChangedRcomboTiming, VTS_BSTR VTS_I2)
	ON_EVENT(LWDirectives, IDC_RSPINBUT_RECONN_AIRCRAFT, 1 /* TextChanged */, OnTextChangedRspinbutReconnAircraft, VTS_BSTR VTS_I2)
	ON_EVENT(LWDirectives, IDC_RSPINBUT_RECONN_MISSIONS, 1 /* TextChanged */, OnTextChangedRspinbutReconnMissons, VTS_BSTR VTS_I2)
	ON_EVENT(LWDirectives, IDC_RECONN_AMONLY, 1 /* Clicked */, OnClickedReconnAmonly, VTS_NONE)
	ON_EVENT(LWDirectives, IDC_RECONN_ESCORT, 1 /* Clicked */, OnClickedReconnEscort, VTS_NONE)
	ON_EVENT(LWDirectives, IDC_RBUTTONREST, 1 /* Clicked */, OnClickedRbuttonrest, VTS_NONE)
	ON_EVENT(LWDirectives, IDC_ESCORT_PROPORTION, 1 /* TextChanged */, OnTextChangedEscortProportion, VTS_BSTR VTS_I2)
	ON_EVENT(LWDirectives, IDC_JU87_PERIOD, 1 /* TextChanged */, OnTextChangedJu87Period, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
 	ON_EVENT_RANGE(LWDirectives, IDC_ALLOW2_0, IDC_ALLOW2_7,1 /* Clicked */, OnTextChangedRspinbutAllow2, VTS_I4 VTS_BSTR VTS_I2 )
	ON_EVENT_RANGE(LWDirectives, IDC_STRAF_0, IDC_STRAF_7,1 /* Clicked */, OnClickedStraf, VTS_I4 )
	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_DO17_0, IDC_RSPINBUT_DO17_8,1 /* TextChanged */, OnTextChangedRspinbutDo17, VTS_I4 VTS_BSTR VTS_I2)
	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_HE1110,IDC_RSPINBUT_HE1118, 1 /* TextChanged */, OnTextChangedRspinbutHe111, VTS_I4 VTS_BSTR VTS_I2)
	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_JU870,IDC_RSPINBUT_JU878, 1 /* TextChanged */, OnTextChangedRspinbutJu87, VTS_I4 VTS_BSTR VTS_I2)
	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_JU88_0,IDC_RSPINBUT_JU88_8, 1 /* TextChanged */, OnTextChangedRspinbutJu88, VTS_I4 VTS_BSTR VTS_I2)
	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_ME109_0,IDC_RSPINBUT_ME109_8, 1 /* TextChanged */, OnTextChangedRspinbutMe109, VTS_I4 VTS_BSTR VTS_I2)
	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_ME1100,IDC_RSPINBUT_ME1108, 1 /* TextChanged */, OnTextChangedRspinbutMe110, VTS_I4 VTS_BSTR VTS_I2)
	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_TIED_0,IDC_RSPINBUT_TIED_7, 1 /* TextChanged */, OnTextChangedRspinbutTied, VTS_I4 VTS_BSTR VTS_I2)
	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_FREE_0,IDC_RSPINBUT_FREE_7, 1 /* TextChanged */, OnTextChangedRspinbutFree, VTS_I4 VTS_BSTR VTS_I2)
	ON_EVENT_RANGE(LWDirectives, IDC_TICK_A0, IDC_TICK_A5,1 /* Clicked */, OnClickedAttached, VTS_I4 )
	ON_EVENT_RANGE(LWDirectives, IDC_TICK_D0, IDC_TICK_D5,1 /* Clicked */, OnClickedDetached, VTS_I4 )
	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_SIZE_0, IDC_RSPINBUT_SIZE_7,1 /* TextChanged */, OnTextChangedRspinbutSize, VTS_I4  VTS_BSTR VTS_I2)
END_EVENTSINK_MAP()

static float	escortusage[]={0.33,0.50,0.67,0.80};
BOOL LWDirectives::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GETDLGITEM(IDC_JU87_PERIOD)	->AddString(RESSTRING(NO_AIRCRAFT));
	GETDLGITEM(IDC_JU87_PERIOD)	->AddString(RESSTRING(L_MORNING));
	GETDLGITEM(IDC_JU87_PERIOD)	->AddString(RESSTRING(NOON));
	GETDLGITEM(IDC_JU87_PERIOD)	->AddString(RESSTRING(AFTERNOONa));
	GETDLGITEM(IDC_JU87_PERIOD)	->AddString(RESSTRING(MAINTAINPERCENTAGE));
	GETDLGITEM(IDC_JU87_PERIOD)	->SetIndex(dr->tempdir.ju87usage);
	GETDLGITEM(IDC_ESCORT_PROPORTION)	->AddString("1:2");
	GETDLGITEM(IDC_ESCORT_PROPORTION)	->AddString("1:1");
	GETDLGITEM(IDC_ESCORT_PROPORTION)	->AddString("2:1");
	GETDLGITEM(IDC_ESCORT_PROPORTION)	->AddString("3:1");
	GETDLGITEM(IDC_ESCORT_PROPORTION)	->SetIndex(int(dr->tempdir.escortproportion/.19)-1);


	LWDirectivesResults::FillTargetLists(dr);
	ininitdialog=true;
	Refresh();
	ininitdialog=false;

	CRStatic*   s;
  	CRSpinBut* spinbut;


	
//TEMPCODE MS 02/02/00 	for(int i =0; i<9;i++)
//TEMPCODE MS 02/02/00 	{
//TEMPCODE MS 02/02/00 		FillSpins(GETDLGITEM(IDC_RSPINBUT_JU87_0+i));
//TEMPCODE MS 02/02/00 		FillSpins(GETDLGITEM(IDC_RSPINBUT_JU88_0+i));
//TEMPCODE MS 02/02/00 		FillSpins(GETDLGITEM(IDC_RSPINBUT_HE111_0+i));
//TEMPCODE MS 02/02/00 		FillSpins(GETDLGITEM(IDC_RSPINBUT_DO17_0+i));
//TEMPCODE MS 02/02/00 		FillSpins(GETDLGITEM(IDC_RSPINBUT_ME109_0+i));
//TEMPCODE MS 02/02/00 		FillSpins(GETDLGITEM(IDC_RSPINBUT_ME110_0+i));
//TEMPCODE MS 02/02/00 		spinbut=GETDLGITEM(IDC_RSPINBUT_PERCENTIN_0+i);
//TEMPCODE MS 02/02/00 		spinbut->Clear()->MakeNumList(10,0,10)->SetIndex(7);
//TEMPCODE MS 02/02/00  		spinbut=GETDLGITEM(IDC_RSPINBUT_PERCENTTIED_0+i);
//TEMPCODE MS 02/02/00 		spinbut->Clear()->MakeNumList(10,0,10)->SetIndex(7);
//TEMPCODE MS 02/02/00  		FillSpins(GETDLGITEM(IDC_RSPINBUT_SIZE_0+i));
//TEMPCODE MS 02/02/00 
//TEMPCODE MS 02/02/00 
//TEMPCODE MS 02/02/00 		s=GETDLGITEM(IDC_RSTATIC_MISSIONS_0+i);
//TEMPCODE MS 02/02/00 		s->SetString("2");
//TEMPCODE MS 02/02/00 
//TEMPCODE MS 02/02/00 
//TEMPCODE MS 02/02/00 
//TEMPCODE MS 02/02/00 
//TEMPCODE MS 02/02/00 	}
//TEMPCODE MS 02/02/00 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//DeadCode RDH 20Jun00  	ON_EVENT_RANGE(LWDirectives, IDC_ALLOW2_0, IDC_ALLOW2_7,1 /* Clicked */, OnTextChangedRspinbutAllow2, VTS_I4 VTS_BSTR VTS_I2 )
//DeadCode RDH 20Jun00 	ON_EVENT_RANGE(LWDirectives, IDC_STRAF_0, IDC_STRAF_7,1 /* Clicked */, OnClickedStraf, VTS_I4 )
//DeadCode RDH 20Jun00 	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_DO17_0, IDC_RSPINBUT_DO17_8,1 /* TextChanged */, OnTextChangedRspinbutDo17, VTS_I4 VTS_BSTR VTS_I2)
//DeadCode RDH 20Jun00 	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_HE1110,IDC_RSPINBUT_HE1118, 1 /* TextChanged */, OnTextChangedRspinbutHe111, VTS_I4 VTS_BSTR VTS_I2)
//DeadCode RDH 20Jun00 	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_JU870,IDC_RSPINBUT_JU878, 1 /* TextChanged */, OnTextChangedRspinbutJu87, VTS_I4 VTS_BSTR VTS_I2)
//DeadCode RDH 20Jun00 	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_JU88_0,IDC_RSPINBUT_JU88_8, 1 /* TextChanged */, OnTextChangedRspinbutJu88, VTS_I4 VTS_BSTR VTS_I2)
//DeadCode RDH 20Jun00 	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_ME109_0,IDC_RSPINBUT_ME109_8, 1 /* TextChanged */, OnTextChangedRspinbutMe109, VTS_I4 VTS_BSTR VTS_I2)
//DeadCode RDH 20Jun00 	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_ME1100,IDC_RSPINBUT_ME1108, 1 /* TextChanged */, OnTextChangedRspinbutMe110, VTS_I4 VTS_BSTR VTS_I2)
//DeadCode RDH 20Jun00 	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_TIED_0,IDC_RSPINBUT_TIED_7, 1 /* TextChanged */, OnTextChangedRspinbutTied, VTS_I4 VTS_BSTR VTS_I2)
//DeadCode RDH 20Jun00 	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_FREE_0,IDC_RSPINBUT_FREE_7, 1 /* TextChanged */, OnTextChangedRspinbutFree, VTS_I4 VTS_BSTR VTS_I2)
//DeadCode RDH 20Jun00 	ON_EVENT_RANGE(LWDirectives, IDC_TICK_A0, IDC_TICK_A5,1 /* Clicked */, OnClickedAttached, VTS_I4 )
//DeadCode RDH 20Jun00 	ON_EVENT_RANGE(LWDirectives, IDC_TICK_D0, IDC_TICK_D5,1 /* Clicked */, OnClickedDetached, VTS_I4 )
//DeadCode RDH 20Jun00 	ON_EVENT_RANGE(LWDirectives, IDC_RSPINBUT_SIZE_0, IDC_RSPINBUT_SIZE_7,1 /* TextChanged */, OnTextChangedRspinbutSize, VTS_I4  VTS_BSTR VTS_I2)

void LWDirectives::FillSpins(CRSpinBut* spinbut, int actype, int trgtype, int indexgrp, int maxgrp)
{
//DEADCODE  17/02/00 	int acindex = actype-PT_GER_FLYABLE;
//DEADCODE  17/02/00 
//DEADCODE  17/02/00 	float	indexgrp = dr->tempdir.targetlines[trgtype][actype];
//DEADCODE  17/02/00 	float	max = indexgrp + dr->tempdir.targetlines[Directives::LW::Targ::RESTING][actype];
//DEADCODE  17/02/00 	float maxgrp = max * dr->LWGrAvail[acindex];
//DEADCODE  17/02/00 	indexgrp = indexgrp * dr->LWGrAvail[acindex];
//DEADCODE  17/02/00 
//DEADCODE  17/02/00 //TEMPCODE RDH 02/02/00 	//resting takes up the slack
//TEMPCODE RDH 02/02/00 	if(trgtype == Directives::LW::Targ::RESTING)
//TEMPCODE RDH 02/02/00 	{
//TEMPCODE RDH 02/02/00 		int intind = 0;
//TEMPCODE RDH 02/02/00 		for (int j = 0; j < Directives::LW::Targ::RESTING;j++)
//TEMPCODE RDH 02/02/00 		{
//TEMPCODE RDH 02/02/00 			float ind = dr->tempdir.targetlines[j][actype];
//TEMPCODE RDH 02/02/00 			ind = ind * LWGrAvail[actype -  PT_GER_FLYABLE];
//TEMPCODE RDH 02/02/00 			intind = intind + (int)ind;
//TEMPCODE RDH 02/02/00 		}
//TEMPCODE RDH 02/02/00 		maxgrp = LWGrAvail[actype -  PT_GER_FLYABLE] - intind;
//TEMPCODE RDH 02/02/00 		indexgrp = maxgrp;	
//TEMPCODE RDH 02/02/00 
//TEMPCODE RDH 02/02/00 	}
//TEMPCODE RDH 02/02/00 
//DEADCODE  17/02/00 
//DEADCODE  17/02/00 	if(trgtype == Directives::LW::Targ::RESTING)
//DEADCODE  17/02/00 	{
//DEADCODE  17/02/00 		int rest,total = 0;
//DEADCODE  17/02/00 		for(int ttype =0; ttype<8;ttype++)
//DEADCODE  17/02/00 		{
//DEADCODE  17/02/00 			total += dr->tempdir.targetlines[ttype][actype] * dr->LWGrAvail[acindex];
//DEADCODE  17/02/00 		}
//DEADCODE  17/02/00 		//rest
//DEADCODE  17/02/00 		rest = dr->LWGrAvail[acindex] - total;
//DEADCODE  17/02/00 		if (rest < 0)
//DEADCODE  17/02/00 			rest = 0;
//DEADCODE  17/02/00 		float newrest = rest; 
//DEADCODE  17/02/00 			newrest = newrest / dr->LWGrAvail[acindex];
//DEADCODE  17/02/00 		if (newrest >  1)
//DEADCODE  17/02/00 				newrest = 1;
//DEADCODE  17/02/00 //		dr->tempdir.targetlines[trgtype][actype] = newrest;
//DEADCODE  17/02/00 		maxgrp = indexgrp = rest;
//DEADCODE  17/02/00 	}
//DEADCODE  17/02/00 

	spinbut->Clear();
	int i =0;
	while  (i <= maxgrp)
	{
		spinbut->AddString(CSprintf("%i", i));
		i++;
	}
	spinbut->SetIndex(indexgrp);

}
//DeadCode RDH 08Feb00 void LWDirectives::FindAcAvail()
//DeadCode RDH 08Feb00 {
//DeadCode RDH 08Feb00 	for (int actype = PT_GER_FLYABLE; actype < PT_VEHICLES;actype++)
//DeadCode RDH 08Feb00 		LWGrAvail[actype - PT_GER_FLYABLE] = 0;
//DeadCode RDH 08Feb00 
//DeadCode RDH 08Feb00 	int j = 0;
//DeadCode RDH 08Feb00 	while (Node_Data.gruppe[j].squadron != SQ_ZERO)
//DeadCode RDH 08Feb00 	{
//DeadCode RDH 08Feb00 		Squadron* sq  = Node_Data[Node_Data.gruppe[j].squadron];
//DeadCode RDH 08Feb00 		if  (!sq->Busy())
//DeadCode RDH 08Feb00 		{
//DeadCode RDH 08Feb00 			int type = sq->AcType();
//DeadCode RDH 08Feb00 			type = type - PT_GER_FLYABLE;
//DeadCode RDH 08Feb00 			LWGrAvail[type] ++;		//= sq->acavail;
//DeadCode RDH 08Feb00 		}
//DeadCode RDH 08Feb00 		j++;
//DeadCode RDH 08Feb00 	}
//DeadCode RDH 08Feb00 }
void LWDirectives::RefreshAcSplit()		 
{
	//index is a number between 0 and 10, 10 means allocate all to session
	//ie 100%, so if the max squads allowed is 96
	//and there are 192 available(maxsquads)
	// maxindex = 10* 96/maxsquads

	float maxindexfl=100.0;
	if (maxsquads>=10)
		maxindexfl = Profile::MAXLWPLANNEDSTAFFELN * 10.0 / maxsquads;		//max squads planned or flying is 96
	if (maxindexfl>10.0)
		maxindexfl=10.0;
	int maxindex = (int)maxindexfl; //SHOULD **NOT** BE /10				//JIM 7Sep00
	CRSpinBut* spinbut;
	spinbut=GETDLGITEM(IDC_RSPINBUT_MORN);
	int indexmorn = (0.00001+dr->tempdir.morningquota) *10; 				//JIM 7Sep00
	int indexmid = (0.00001+dr->tempdir.middayquota) *10; 				//JIM 7Sep00

	if (indexmorn >= maxindex)
	{
		indexmorn = maxindexfl;
		dr->tempdir.morningquota = maxindexfl/10;						//JIM 31Jul00
	}

	if (indexmid >= maxindex)
	{
		if (dr->tempdir.morningquota+maxindexfl*0.1>=1.0)					//JIM 31Jul00
			maxindexfl=10.0-10.0*dr->tempdir.morningquota;
		indexmid = maxindexfl;
		dr->tempdir.middayquota = maxindexfl/10;
	}

	int index = 10 - (indexmorn + indexmid);
	if (index > maxindex)
		index = maxindex;

	spinbut->Clear()->MakeNumList(indexmorn+index+1,0,10)->SetIndex(indexmorn);
	if (MMC.currtime  >= MIDDAYPERIODSTART)
		spinbut->EnableWindow(false);
	else
		spinbut->EnableWindow(true);
	spinbut=GETDLGITEM(IDC_RSPINBUT_MID);

	spinbut->Clear()->MakeNumList(indexmid+index+1,0,10)->SetIndex(indexmid);
	if (MMC.currtime  >= AFTERNOONPERIODSTART)
		spinbut->EnableWindow(false);
	else
		spinbut->EnableWindow(true);

	CRStatic*   s;
	s=GETDLGITEM(IDC_BOMBER_AFTER);
	s->SetString(CSprintf("%i", index*10));


	CRCombo* combo;
	index = 0;
	if (dr->tempdir.arrivalminsseperation <= 2)
		index = 1;
	combo=GETDLGITEM(IDC_RCOMBO_TIMING);
	combo->Clear()->RESCOMBO(CONSEC,2)->
					SetIndex(index);




}
void LWDirectives::RefreshGruppe()
{
	for (int actype = PT_GER_FLYABLE; actype < PT_VEHICLES;actype++)
	{
		RefreshGruppe(PlaneTypeSelect(actype));
	}
}
void LWDirectives::RefreshGruppe(PlaneTypeSelect actype)
{
		float rest;
		int	total = 0;
		int acindex = actype-PT_GER_FLYABLE;

		//start at 1
		for(int ttype =1; ttype<8;ttype++)
		{//only take the whole numbers
			total += (truncingfix + dr->tempdir.targetlines[ttype][actype] * dr->LWGrAvail[acindex]);
		}
		//rest
		rest = dr->LWGrAvail[acindex] - total;
		if (rest < 0)
			rest = 0;
		int maxgrp;

		for(int trgtype =1; trgtype<9;trgtype++)
		{
			int acindex = actype-PT_GER_FLYABLE;
			int indexgrp;
			float	index = dr->tempdir.targetlines[trgtype][actype];
			index = index * dr->LWGrAvail[acindex];		//display gruppe
			indexgrp = index + truncingfix;
			maxgrp = indexgrp;
			maxgrp = maxgrp + rest;	//only take whole numbers
			if (trgtype == 8)
				indexgrp = rest;
				int butt;
			switch (actype)
			{
				case	PT_ME109:
				{
					FillSpins(GETDLGITEM(IDC_RSPINBUT_ME109_0+trgtype), actype, trgtype, indexgrp, maxgrp);
					break;
				}
				case	PT_ME110:
				{
					FillSpins(GETDLGITEM(IDC_RSPINBUT_ME1100+trgtype), actype, trgtype, indexgrp, maxgrp);
					break;
				}
				case	PT_JU87:
				{
					FillSpins(GETDLGITEM(IDC_RSPINBUT_JU870+trgtype), actype, trgtype, indexgrp, maxgrp);
					break;
				}
				case	PT_DO17:
				{
					FillSpins(GETDLGITEM(IDC_RSPINBUT_DO17_0+trgtype), actype, trgtype, indexgrp, maxgrp);
					break;
				}
				case	PT_JU88:
				{
					FillSpins(GETDLGITEM(IDC_RSPINBUT_JU88_0+trgtype), actype, trgtype, indexgrp, maxgrp);
					break;
				}
				case	PT_HE111:
					{					 
					FillSpins(GETDLGITEM(IDC_RSPINBUT_HE1110+trgtype), actype, trgtype, indexgrp, maxgrp);
					break;
				}

			}
		}

}
void LWDirectives::RefreshEscort()		 
{
		for(int trgtype =1; trgtype<8;trgtype++)
		{
			RefreshEscort(trgtype);
		}
}
void LWDirectives::RefreshEscort(int trgtype)
{		 
	CRSpinBut* spinbut;

	float	tied = dr->tempdir.targetlines[trgtype].attached;
	tied = tied*10+0.1;
	float	free = dr->tempdir.targetlines[trgtype].detached;
	free = free*10+0.1;
	spinbut=GETDLGITEM(IDC_RSPINBUT_FREE_0+trgtype);
	spinbut->Clear()->MakeNumList(11,0,10)->SetIndex(free);

	spinbut=GETDLGITEM(IDC_RSPINBUT_TIED_0+trgtype);
	spinbut->Clear()->MakeNumList(11,0,10)->SetIndex(tied);


}
enum	{MTBF_DONTADDUP=0x10000,MTBF_ME110=0x20000,MTBF_NOESCORT=0x40000,MTBF_MISSIONS=0xFFFF};
void LWDirectives::RefreshMissions(int rownum)
{
	int miss=RefreshInternalMissions(rownum);
	RefreshMission(rownum, miss);

}
void LWDirectives::RefreshMissions()
{
	int k=0;
	int missions;

	k = LWDirectivesResults::FillReconnDirectivesLine(dr,k);

	for (int i = 1; i<8;i++)
	{
		k = LWDirectivesResults::FillOneDirectivesLine(dr, i, k, missions);
		RefreshMission(i, missions);

	}

	dr->dirresults[k].targets[0] = UID_NULL;

}

int	LWDirectives::RefreshInternalMissions(int rownumtoreport)
{	//doesn't cause display refresh...
	int k=0;
	int missions;
	int rv=0;
	k = LWDirectivesResults::FillReconnDirectivesLine(dr,k);

	for (int i = 1; i<8;i++)
	{
		k = LWDirectivesResults::FillOneDirectivesLine(dr, i, k, missions);
		if (i==rownumtoreport)
			rv=missions;
	}

	dr->dirresults[k].targets[0] = UID_NULL;
	return rv;
}

void LWDirectives::RefreshMission(int i,  int missions)
{
#ifndef BOB_DEMO_VER
	CRSpinBut* spinbut;
	spinbut=GETDLGITEM(IDC_RSPINBUT_SIZE_0 + i);

	int	staffelperraid = dr->tempdir.targetlines[i].bombersperraid;
	staffelperraid = (3+staffelperraid)/10;	//3+ is a rounding factor...
	if (ininitdialog)
	for(int entry = 0;entry< LWTaskSummary::SQUADSENSIBLEMAX;entry++)						//JIM 5Sep00
	{
		spinbut->AddString(CSprintf("%i %s", LWTaskSummary::squadinfo[entry].number, LoadResString(LWTaskSummary::squadinfo[entry].name)));
		int ac = LWTaskSummary::squadinfo[entry].numofsquads;
		if  (	(staffelperraid  == ac )
			)
				spinbut->SetIndex(entry);

	}

	CRStatic*   s;
	s=GETDLGITEM(IDC_RSTATIC_MISSIONS_0+i);
	int	missflags=missions;
	missions&=MTBF_MISSIONS;
	missflags-=missions;
	if (missflags==0)
		if (missions)
			s->SetForeColor(RGB(255,255,80));
		else
			s->SetForeColor(RGB(200,200,20));
	else
		if (missflags==MTBF_DONTADDUP)
			s->SetForeColor(RGB(255,0,0));
		else
			if (missflags==MTBF_NOESCORT)
				s->SetForeColor(RGB(255,160,50));
			else
				if (missions)
					s->SetForeColor(RGB(255,160,50));
				else
					s->SetForeColor(RGB(255,0,0));

	s->SetString(CSprintf("%i", missions));
#endif
 
}
void LWDirectives::RefreshReconn()
{
	CRSpinBut* spinbut;
	spinbut=GETDLGITEM(IDC_RSPINBUT_RECONN_AIRCRAFT);
	if (dr->tempdir.reconn.ac <1)
		dr->tempdir.reconn.ac =1;
	if (dr->tempdir.reconn.ac > 3)
		dr->tempdir.reconn.ac = 3;
	spinbut->Clear()->MakeNumList(3,1,1)->SetIndex(dr->tempdir.reconn.ac-1);

	int j = 0;
	int maxreconn = 0;
	while (Node_Data.gruppe[j].squadron != SQ_ZERO)
	{
		Gruppen* g  = Node_Data[Node_Data.gruppe[j].squadron];
		if  (!g->Busy())
		{
			if (Node_Data.geschwader[g->wadernum].reconn)
				maxreconn++;
		}
		j++;
	}
	if (maxreconn)
	{
		if (!dr->tempdir.reconn.morningonly)
			maxreconn = maxreconn/3;
		if (maxreconn <= 1)
			maxreconn = 1;

	}

	spinbut=GETDLGITEM(IDC_RSPINBUT_RECONN_MISSIONS);
	if (dr->tempdir.reconn.missions > maxreconn)
		dr->tempdir.reconn.missions = maxreconn;


//DeadCode JIM 10Sep00 	CRStatic*   s;
//DeadCode JIM 10Sep00 	s=GETDLGITEM(IDC_RSTATIC_RECONN_MISSIONS);
	
	if (maxreconn)
	{
//DeadCode JIM 10Sep00 		s->ShowWindow(false);
		spinbut->EnableWindow(true);
		spinbut->Clear()->MakeNumList(maxreconn+1,0,1)->SetIndex(dr->tempdir.reconn.missions);
	}else
	{
		spinbut->EnableWindow(false);
		spinbut->Clear()->MakeNumList(1,0,1)->SetIndex(0);
	}


	CRButton* b;
	b = GETDLGITEM(IDC_RECONN_AMONLY);
	b->SetPressed(dr->tempdir.reconn.morningonly);

	b = GETDLGITEM(IDC_RECONN_ESCORT);
	b->SetPressed(dr->tempdir.reconn.escort);
							
}
void LWDirectives::Refresh()		 
{
	maxsquads = LWDirectivesResults::FindMaxSquads(dr);
 	RefreshAcSplit();
	LWDirectivesResults::FindAcAvail(dr);
	RefreshReconn();
	RefreshGruppe();
 	RefreshEscort();
 	RefreshFlags();
	RefreshMissions();



}
void LWDirectives::RefreshFlags()		 
{
	CRButton* b;
	for(int trgtype =1; trgtype<8;trgtype++)
	{
//DeadCode JIM 20Oct00 		int	tied = dr->tempdir.targetlines[trgtype].attached;

//DEADCODE RDH 20/03/00 		b = GETDLGITEM(IDC_ALLOW2_0+trgtype);
//DEADCODE RDH 20/03/00 		b->SetPressed(dr->tempdir.targetlines[trgtype].flags  & Directives::LW::Targ::SECONDARIESALLOWED);
	  	CRSpinBut* spinbut;

		spinbut= GETDLGITEM(IDC_ALLOW2_0+trgtype);
		spinbut->Clear()->MakeNumList(6,0,1)->SetIndex(dr->tempdir.targetlines[trgtype].secondarytargets);


		b = GETDLGITEM(IDC_STRAF_0+trgtype);
		b->SetPressed(dr->tempdir.targetlines[trgtype].flags & Directives::LW::Targ::FIGHTERSSTRAFFE);
	}

	for (int i = 0; i < 6; i++)
	{
		b = GETDLGITEM(IDC_TICK_A0+i);
		int am = Profile::AM_ATTACHED+1+i;
		b->SetPressed(dr->tempdir.escortmethods[(Profile::AttackMethod)am]);
		b = GETDLGITEM(IDC_TICK_D0+i);
		am = Profile::AM_DETACHED+1+i;
		b->SetPressed(dr->tempdir.escortmethods[(Profile::AttackMethod)am]);
	}
		

}
//DEADCODE  08/02/00 void LWDirectives::FillTargetLists()
//DEADCODE  08/02/00 {
//DEADCODE  08/02/00 	for (int i=0 ; i < 8; i++)
//DEADCODE  08/02/00 	{
//DEADCODE  08/02/00 		int uidbandstart, uidbandend;
//DEADCODE  08/02/00 		int panel = Target::TT_DUMMY0;
//DEADCODE  08/02/00 
//DEADCODE  08/02/00 		switch (i)
//DEADCODE  08/02/00 		{
//DEADCODE  08/02/00 		case	Directives::LW::Targ::RECON:
//DEADCODE  08/02/00 			{
//DEADCODE  08/02/00 				uidbandstart = 	RAF_FighterAFBAND;
//DEADCODE  08/02/00 				uidbandend =  CLRadarBAND;
//DEADCODE  08/02/00 				break;
//DEADCODE  08/02/00 			}
//DEADCODE  08/02/00 		case	Directives::LW::Targ::AIRFIELDS:
//DEADCODE  08/02/00 			{//AIRFIELDS
//DEADCODE  08/02/00 				uidbandstart = 	RAF_FighterAFBAND;
//DEADCODE  08/02/00 				uidbandend =  CLRadarBAND;
//DEADCODE  08/02/00 				break;
//DEADCODE  08/02/00 			}
//DEADCODE  08/02/00 		case	Directives::LW::Targ::DOCKS:
//DEADCODE  08/02/00 			{//DOCKS
//DEADCODE  08/02/00 				uidbandstart = 	DocksBAND;
//DEADCODE  08/02/00 				uidbandend =  PortBAND;
//DEADCODE  08/02/00 				break;
//DEADCODE  08/02/00 			}
//DEADCODE  08/02/00 		case	Directives::LW::Targ::RADARS:
//DEADCODE  08/02/00 			{//RADARS
//DEADCODE  08/02/00 				uidbandstart = 	CLRadarBAND;
//DEADCODE  08/02/00 				uidbandend =  LUF_FighterLF2BAND;
//DEADCODE  08/02/00 				break;
//DEADCODE  08/02/00 			}
//DEADCODE  08/02/00 		case	Directives::LW::Targ::CONVOYS:
//DEADCODE  08/02/00 			{//CONVOYS
//DEADCODE  08/02/00 				uidbandstart = 	BritBoatBAND;
//DEADCODE  08/02/00 				uidbandend =  GermBoatBAND;
//DEADCODE  08/02/00 				break;
//DEADCODE  08/02/00 			}
//DEADCODE  08/02/00 		case	Directives::LW::Targ::LONDON:
//DEADCODE  08/02/00 			{//LONDON
//DEADCODE  08/02/00 				uidbandstart = 	PowerStationBAND;
//DEADCODE  08/02/00 				uidbandend =  DocksBAND;
//DEADCODE  08/02/00 				panel = Target::TT_LONDON;
//DEADCODE  08/02/00 				break;
//DEADCODE  08/02/00 			}
//DEADCODE  08/02/00 		case	Directives::LW::Targ::FACTORIES:
//DEADCODE  08/02/00 			{//FACTORIES
//DEADCODE  08/02/00 				uidbandstart = 	PowerStationBAND;
//DEADCODE  08/02/00 				uidbandend =  DocksBAND;
//DEADCODE  08/02/00 				break;
//DEADCODE  08/02/00 			}
//DEADCODE  08/02/00  		case	Directives::LW::Targ::SWEEPSNDECOYS:
//DEADCODE  08/02/00 			{//SWEEPSNDECOYS
//DEADCODE  08/02/00 				uidbandstart = 	PowerStationBAND;
//DEADCODE  08/02/00 				uidbandend =  DocksBAND;
//DEADCODE  08/02/00 				break;
//DEADCODE  08/02/00 			}
//DEADCODE  08/02/00    
//DEADCODE  08/02/00 		}
//DEADCODE  08/02/00 
//DEADCODE  08/02/00 		LWDirectivesResults::FillTargetList(target.target,uidbandstart, uidbandend, panel);
//DEADCODE  08/02/00 
//DEADCODE  08/02/00 		for (int j = 0; j <LWDirectivesResultsTargetList::MAX_TARGETS; j++)
//DEADCODE  08/02/00 		{
//DEADCODE  08/02/00 			trgarray[i].target[j] = target[j];
//DEADCODE  08/02/00 		}
//DEADCODE  08/02/00 	}
//DEADCODE  08/02/00 }

bool LWDirectives::ResetProportions(int actype, int line, int index)
{
	bool rv=false;
	if (index)
		if (actype == PT_JU87)
		{
			if (dr->tempdir.targetlines[line][PT_DO17])
			{
				dr->tempdir.targetlines[Directives::LW::Targ::RESTING][PT_DO17] +=
					dr->tempdir.targetlines[line][PT_DO17];
				dr->tempdir.targetlines[line][PT_DO17] = 0;
				rv=true;
			}
			if (dr->tempdir.targetlines[line][PT_HE111])
			{
				dr->tempdir.targetlines[Directives::LW::Targ::RESTING][PT_HE111] +=
					dr->tempdir.targetlines[line][PT_HE111];
				dr->tempdir.targetlines[line][PT_HE111] = 0;
				rv=true;
			}
			if (dr->tempdir.targetlines[line][PT_JU88])
			{
				dr->tempdir.targetlines[Directives::LW::Targ::RESTING][PT_JU88] +=
					dr->tempdir.targetlines[line][PT_JU88];
				dr->tempdir.targetlines[line][PT_JU88] = 0;
				rv=true;
			}

		}
		else
 		if (actype>PT_JU87)
		{
			if (dr->tempdir.targetlines[line][PT_JU87])
			{
				dr->tempdir.targetlines[Directives::LW::Targ::RESTING][PT_JU87] +=
					dr->tempdir.targetlines[line][PT_JU87];
				dr->tempdir.targetlines[line][PT_JU87] = 0;
				rv=true;
			}

		}

	float acavail = dr->LWGrAvail[actype -  PT_GER_FLYABLE];
	float newprop = index/(acavail);	//get back to group
	float oldprop = dr->tempdir.targetlines[line][actype];
	float change = newprop -oldprop;

	dr->tempdir.targetlines[line][actype] = newprop;
	dr->tempdir.targetlines[Directives::LW::Targ::RESTING][actype] -=
																  change;
	if(dr->tempdir.targetlines[Directives::LW::Targ::RESTING][actype] < 0.0)
		dr->tempdir.targetlines[Directives::LW::Targ::RESTING][actype] = 0.0;
	if(dr->tempdir.targetlines[Directives::LW::Targ::RESTING][actype] > 1.0)	
		dr->tempdir.targetlines[Directives::LW::Targ::RESTING][actype] = 1.0;

	return rv;
}

void LWDirectives::OnTextChangedRspinbutJu87(int id, LPCTSTR caption, short Index) 
{
	if (ResetProportions(PT_JU87, id - IDC_RSPINBUT_JU870, Index))
	{
		RefreshGruppe(PT_DO17);
		RefreshGruppe(PT_JU88);
		RefreshGruppe(PT_HE111);
	}
	RefreshMissions(id-IDC_RSPINBUT_JU870);
	RefreshGruppe(PT_JU87);
}

void LWDirectives::OnTextChangedRspinbutAllow2(int id, LPCTSTR caption, short Index) 
{
	dr->tempdir.targetlines[id - IDC_ALLOW2_0].secondarytargets = Index;
	RefreshMissions(id - IDC_ALLOW2_0);
//DeadCode JIM 7Sep00 	RefreshGruppe();
}
void LWDirectives::OnTextChangedRspinbutDo17(int id, LPCTSTR caption, short Index) 
{
	if (ResetProportions(PT_DO17, id - IDC_RSPINBUT_DO17_0, Index))
		RefreshGruppe(PT_JU87);
	RefreshMissions(id - IDC_RSPINBUT_DO17_0);
	RefreshGruppe(PT_DO17);
}	


void LWDirectives::OnTextChangedRspinbutHe111(int id, LPCTSTR caption, short Index) 
{
	if (ResetProportions(PT_HE111, id - IDC_RSPINBUT_HE1110, Index))
		RefreshGruppe(PT_JU87);
	RefreshMissions(id - IDC_RSPINBUT_HE1110);
	RefreshGruppe(PT_HE111);
}	

void LWDirectives::OnTextChangedRspinbutJu88(int id, LPCTSTR caption, short Index) 
{
	if (ResetProportions(PT_JU88, id - IDC_RSPINBUT_JU88_0, Index))
		RefreshGruppe(PT_JU87);
	RefreshMissions(id - IDC_RSPINBUT_JU88_0);
	RefreshGruppe(PT_JU88);
	
}
void LWDirectives::OnTextChangedRspinbutMe109(int id, LPCTSTR caption, short Index) 
{
	ResetProportions(PT_ME109, id - IDC_RSPINBUT_ME109_0, Index);
	RefreshMissions(id - IDC_RSPINBUT_ME109_0);
	RefreshGruppe(PT_ME109);
	
}

void LWDirectives::OnTextChangedRspinbutMe110(int id, LPCTSTR caption, short Index) 
{
	ResetProportions(PT_ME110, id - IDC_RSPINBUT_ME1100, Index);
	RefreshMissions(id - IDC_RSPINBUT_ME1100);
	RefreshGruppe(PT_ME110);
	
}
 
void LWDirectives::OnTextChangedRspinbutTied(int id, LPCTSTR caption, short Index) 
{
	id = id - IDC_RSPINBUT_TIED_0;
	float tied = Index;
	tied = tied / 10;

	dr->tempdir.targetlines[id].attached = tied;
	if ((tied + dr->tempdir.targetlines[id].detached) > 1)
		dr->tempdir.targetlines[id].detached = 1 - tied;
	RefreshInternalMissions();
	RefreshEscort(id);
//DeadCode JIM 7Sep00 	Refresh();
	
}
void LWDirectives::OnTextChangedRspinbutFree(int id, LPCTSTR caption, short Index) 
{
	id = id - IDC_RSPINBUT_FREE_0;
	float free = Index; 
	free = free	/ 10;
	dr->tempdir.targetlines[id].detached = free;
	if ((free + dr->tempdir.targetlines[id].attached) > 1)
		dr->tempdir.targetlines[id].attached = 1 - free;
	RefreshInternalMissions();
	RefreshEscort(id);
//DeadCode JIM 7Sep00 	Refresh();
	
}

//DEADCODE RDH 20/03/00 void LWDirectives::OnClickedAllow2(int id) 
//DEADCODE RDH 20/03/00 {
//DEADCODE RDH 20/03/00 	id = id - IDC_ALLOW2_0;
//DEADCODE RDH 20/03/00 	if (dr->tempdir.targetlines[id].flags & Directives::LW::Targ::SECONDARIESALLOWED)
//DEADCODE RDH 20/03/00 			dr->tempdir.targetlines[id].flags %= Directives::LW::Targ::SECONDARIESALLOWED;
//DEADCODE RDH 20/03/00 	else
//DEADCODE RDH 20/03/00 			dr->tempdir.targetlines[id].flags |= Directives::LW::Targ::SECONDARIESALLOWED;
//DEADCODE RDH 20/03/00 	RefreshFlags();		 
//DEADCODE RDH 20/03/00 
//DEADCODE RDH 20/03/00 }

void LWDirectives::OnClickedStraf(int id) 
{
	id = id - IDC_STRAF_0;
	if (dr->tempdir.targetlines[id].flags & Directives::LW::Targ::FIGHTERSSTRAFFE)
			dr->tempdir.targetlines[id].flags = dr->tempdir.targetlines[id].flags & (~Directives::LW::Targ::FIGHTERSSTRAFFE);
	else
			dr->tempdir.targetlines[id].flags |= Directives::LW::Targ::FIGHTERSSTRAFFE;
//DeadCode JIM 7Sep00 	RefreshFlags();		 
	RefreshInternalMissions();

}

void LWDirectives::OnTextChangedRcomboTiming(LPCTSTR Caption, short index) 
{
	if (index == 0)
		dr->tempdir.arrivalminsseperation = 15;							//RDH 9Aug00
	else
		dr->tempdir.arrivalminsseperation = 2;
//DeadCode JIM 7Sep00 	RefreshAcSplit();	
	RefreshInternalMissions();
}
void LWDirectives::OnTextChangedMorn(LPCTSTR Caption, short index) 
{
	float i = index;
	dr->tempdir.morningquota = i/10;
	Refresh();	
}
void LWDirectives::OnTextChangedMid(LPCTSTR Caption, short index) 
{
	float i = index;
	dr->tempdir.middayquota = i/10;
	Refresh();	
}


void LWDirectives::OnOK() 
{
#ifndef	BOB_DEMO_VER

	//to reset reconn priorities
	LWDirectivesResults::FillTargetLists(dr);


	if (dr->dirresults[0].targets[0])
	{
		MiscToolBar().OpenDirectiveResultsToggle(dr);
		dr = NULL;
	}
	else
	{	
		MMC.directives.lw.current=dr->tempdir;
		MiscToolBar().OpenEmptyDirectiveResults();
	}
	
//	LogChild(0,DirectiveResults::Make(dr));

#endif

	CDialog::OnOK();
}
void LWDirectives::OnCancel() 
{
	// TODO: Add your message handler code here and/or call default
#ifndef	BOB_DEMO_VER
	if (m_pView->m_currentpage==0)
		MiscToolBar().OpenEmptyDirectiveResults();
	CDialog::OnCancel();
#endif
}
void LWDirectives::OnClickedAttached(int id) 
{
	id = id - IDC_TICK_A0;
	int am = Profile::AM_ATTACHED+1+id;

	if	(dr->tempdir.escortmethods[(Profile::AttackMethod)am])
	   dr->tempdir.escortmethods %= (Profile::AttackMethod)am;
	else
	   dr->tempdir.escortmethods |= (Profile::AttackMethod)am;
//DeadCode JIM 7Sep00 	RefreshFlags();
	RefreshInternalMissions();

}
void LWDirectives::OnClickedDetached(int id) 
{
	id = id - IDC_TICK_D0;
	int am = Profile::AM_DETACHED+1+id;
	if	(dr->tempdir.escortmethods[(Profile::AttackMethod)am])
	   dr->tempdir.escortmethods %= (Profile::AttackMethod)am;
	else
	   dr->tempdir.escortmethods |= (Profile::AttackMethod)am;

	RefreshInternalMissions();

}
void LWDirectives::OnTextChangedRspinbutSize(int id, LPCTSTR caption, short Index) 
{
#ifndef BOB_DEMO_VER
	id = id - IDC_RSPINBUT_SIZE_0;
	dr->tempdir.targetlines[id].bombersperraid =
				LWTaskSummary::squadinfo[Index].numofsquads * 10;

	RefreshMissions(id); 
//DEADCODE RDH 06/06/00 	RefreshGruppe();
//DEADCODE RDH 06/06/00  	RefreshEscort();
//DEADCODE RDH 06/06/00  	RefreshFlags();
//DEADCODE RDH 06/06/00 	RefreshMissions();
#endif
}
int	LWDirectivesResults::HowManyReconEscortRequiredThisPeriod(LWDirectivesResults* dr)
{
	if (dr->tempdir.reconn.escort)
		if (MMC.currtime  < MIDDAYPERIODSTART)
			return 	dr->tempdir.reconn.missions;
		else
			if (!dr->tempdir.reconn.morningonly)
				return 	dr->tempdir.reconn.missions;
	return 0;
}

int LWDirectivesResults::FindMaxSquads(LWDirectivesResults* dr)
{//also fills in dr->LWGrAvail

	for (int actype = PT_GER_FLYABLE; actype < PT_VEHICLES;actype++)
		dr->LWGrAvail[actype - PT_GER_FLYABLE] = 0;


	int j = 0;
	int maxsquads = 0;
	//Get total avail for rest of day (assuming no revivals)
	while (Node_Data.gruppe[j].squadron != SQ_ZERO)
	{
		Gruppen* sq  = Node_Data[Node_Data.gruppe[j].squadron];
		if  (		(!sq->Busy())
				&&	(!Node_Data.geschwader[sq->wadernum].reconn)
				&&	(sq->acavail >= Gruppen::MIN_GRUPPEAC)
			)
		{
			int type = sq->AcType();
			if (type>=PT_JU87 || sq->acavail>=Gruppen::MIN_GRUPPEFIGHTERS)
			{
				type = type - PT_GER_FLYABLE;
				dr->LWGrAvail[type] ++;		//= sq->acavail;	
				maxsquads += 3;
			}
		}
		j++;
	}
	int multiplier;
	if (MMC.currtime  < MIDDAYPERIODSTART)
		multiplier = 3;
	else if (MMC.currtime  < AFTERNOONPERIODSTART)
		multiplier = 2;
	else
		multiplier = 1;

	//Zero JU87 count if not wanted in this period!
	if (dr->tempdir.ju87usage!=Directives::LW::JU_ANY)
		if (dr->tempdir.ju87usage+multiplier!=Directives::LW::JU_ANY)
		{
			maxsquads-=dr->LWGrAvail[PT_JU87-PT_GER_FLYABLE]*3;
			dr->LWGrAvail[PT_JU87-PT_GER_FLYABLE]=0;
		}


	if (int reconescortrequired=HowManyReconEscortRequiredThisPeriod(dr))
	{//need to remove some escort gruppe from main missions

		//first work out fighters that have to be put aside for escort
		int escortreq ;
		if (dr->tempdir.reconn.morningonly)
			escortreq = reconescortrequired;
		else
		{
			escortreq = reconescortrequired * multiplier;
		}
		//now remove fighters
		int actype = dr->tempdir.reconn.escortactype;
		int escortavail = dr->LWGrAvail[actype -  PT_GER_FLYABLE];
		if (escortavail >= escortreq)
		{
			dr->LWGrAvail[actype -  PT_GER_FLYABLE] -= escortreq;
		}else
		{
			dr->LWGrAvail[actype -  PT_GER_FLYABLE] = 0;
			if (actype ==  PT_ME109)
				actype = PT_ME110;
			else
				actype = PT_ME109;
			escortreq -= escortavail; 
			dr->LWGrAvail[actype -  PT_GER_FLYABLE] -= escortreq;
			if (dr->LWGrAvail[actype -  PT_GER_FLYABLE] < 0)
				dr->LWGrAvail[actype -  PT_GER_FLYABLE] = 0;

		}


	}
	return (maxsquads);
}
void LWDirectivesResults::FindAcAvail(LWDirectivesResults* dr)
{

	FindMaxSquads(dr);		//also fills in LWGrAvail

	float quota;
	if (MMC.currtime  < MIDDAYPERIODSTART)
	{
		quota = dr->tempdir.morningquota;
		if  (	(quota > 0.29)
			&&	(quota < 0.35)
			)															//RDH 14/04/00
			quota = 0.3334;
	}
	else
	if (	MMC.currtime  < AFTERNOONPERIODSTART	&&	dr->tempdir.morningquota!=1.00		)	//JIM 10Sep00
		quota = dr->tempdir.middayquota/(1 - dr->tempdir.morningquota);
	else
		quota = 1.0;
	if (quota>1.0)
		quota=1.0;
//DeadCode JIM 20Oct00 	int	totalflights=0;
//			PT_GER_FLYABLE,
//			PT_ME109=PT_GER_FLYABLE,
//			PT_ME110,PT_JU87, PT_LW_BOMBERS = PT_JU87,
//			PT_GER_NONFLY,
//			PT_DO17=PT_GER_NONFLY,PT_JU88,PT_HE111,
//			PT_HE59,

	//fix for JU87 in 1 period only...
	if (dr->tempdir.ju87usage!=Directives::LW::JU_ANY)
		dr->LWGrAvail[PT_JU87-PT_GER_FLYABLE]/=quota;

	int totalgrupp=0;
	{for(int ttype =0; ttype<PT_GERMCOUNT;ttype++)
		totalgrupp+=dr->LWGrAvail[ttype];
	}

	if (totalgrupp*quota>32)
		quota=32.0/totalgrupp;

	{for(int ttype =0; ttype<PT_GERMCOUNT;ttype++)
		dr->LWGrAvail[ttype] = dr->LWGrAvail[ttype] * quota;
	}
	if (totalgrupp>32)	//this is yet another fix to get the full complement when you wind the percentages.
	{
		int periodgrupp=0;double periodgruppf=0.0;
		{for(int ttype =0; ttype<PT_GERMCOUNT;ttype++)
		{

			periodgruppf+=dr->LWGrAvail[ttype];
			periodgrupp+=dr->LWGrAvail[ttype];
		}}
		if (periodgruppf>31.5)
			while (periodgrupp<31)
			{
				double highestnext=0.0;
				int highesttype=0;
				{for(int ttype =0; ttype<PT_GERMCOUNT;ttype++)
				{
					double rounding=dr->LWGrAvail[ttype]-int(dr->LWGrAvail[ttype]);
					if (rounding>highestnext)
					{
						highestnext=rounding;
						highesttype=ttype;
					}
				}}
				dr->LWGrAvail[highesttype]=(int)dr->LWGrAvail[highesttype]+1.00001;
				periodgrupp++;
			}
	}
	{for(int ttype =0; ttype<PT_GERMCOUNT;ttype++)
		dr->LWGrAvail[ttype]=(int)(dr->LWGrAvail[ttype]+0.00001)+0.00001;
	}
			



	//reset numbers so that we get some action
	for (int actype = PT_GER_FLYABLE; actype < PT_VEHICLES;actype++)
	{
		int total = 0;
		int acindex = actype-PT_GER_FLYABLE;
	 	if		(	(dr->LWGrAvail[acindex])
				&&	(dr->tempdir.targetlines[Directives::LW::Targ::RESTING][actype] < 0.99)	//if all at rest don't make missions
				)
		{
			float subtotal = 0, maxsubtotal = 0;
			int	maxttype= 1;
			for(int ttype =1; ttype<8;ttype++)
			{//only take the whole numbers
				subtotal = dr->tempdir.targetlines[ttype][actype] * dr->LWGrAvail[acindex];
				if (subtotal > maxsubtotal)
				{
					maxsubtotal = subtotal;
					maxttype = ttype;
				}
				total += subtotal;
			}
			if (total == 0)
			{//no action right now and so reassign a/c
				float newalloc =  0.001 +	 1/dr->LWGrAvail[acindex];
//this code may be needed to force gruppe to be used early in day rather than later
//TEMPCODE RDH 28/04/00 				if (newalloc > 1.01)
//TEMPCODE RDH 28/04/00 				{
//TEMPCODE RDH 28/04/00 					if (	(dr->LWGrAvail[acindex] > 0.33) etc
//TEMPCODE RDH 28/04/00 
//TEMPCODE RDH 28/04/00 					{//there is at least one gruppe avail so use it
//TEMPCODE RDH 28/04/00 						dr->LWGrAvail[acindex] = 1;
//TEMPCODE RDH 28/04/00 
//TEMPCODE RDH 28/04/00 					}
//TEMPCODE RDH 28/04/00 				}else 
				if (newalloc > 1)
					newalloc = 1;
				float readjust = newalloc - dr->tempdir.targetlines[maxttype][actype];
				dr->tempdir.targetlines[maxttype][actype] = newalloc;
				for(int ttype =0; ttype<8;ttype++)
				{//go through each and reduce alloc until all new reassignment is done
					//crude routine, first options always get hit, better to do fraction 
					//off all
					if (	(ttype != maxttype)	&&	(readjust > 0))
					{
						if (readjust > dr->tempdir.targetlines[ttype][actype])
						{
							readjust -=  dr->tempdir.targetlines[ttype][actype];
							dr->tempdir.targetlines[ttype][actype] = 0;
						}else
						{
							readjust = 0;
							dr->tempdir.targetlines[ttype][actype] = readjust;
						}

					}
				}


			}
		}
	}

}
int	LWDirectivesResults::FillReconnDirectivesLine(LWDirectivesResults* dr, int k)
{
	//find better rule to ensure correct ac type chosen
	int j = 0;
	Profile::BetterRule br =  Profile::BR_NONE;
	while (Node_Data.gruppe[j].squadron != SQ_ZERO)
	{
		Gruppen* g  = Node_Data[Node_Data.gruppe[j].squadron];
		if  (!g->Busy())
		{
			if (Node_Data.geschwader[g->wadernum].reconn)
			{
			 	switch(g->AcType())
				{
		 			case	PT_ME110:
					{
						br |=  Profile::BR_R_110BONLY;
						break;
					}
					case	PT_DO17:
					{
						br |= Profile::BR_R_DO17ONLY;
						break;
					}
					case	PT_JU88:
					{
						br |= Profile::BR_R_JU88ONLY;
						break;
					}
					default:
					{
						break;
					}
				}
			}
		}
		j++;
	}

 	//set up missions
	j = 0;
	int	msn = dr->tempdir.reconn.missions;
	if	(		(!dr->tempdir.reconn.morningonly)
			||	(		(dr->tempdir.reconn.morningonly)
					&&	(MMC.currtime  < MIDDAYPERIODSTART)
				)
		)
	{
		while (	(msn > 0) && (dr->trgarray[0].target[j].target != IllegalBAND))
		{
			dr->dirresults[k].usesquadsavail=NULL;
			dr->dirresults[k].mission = MMC.directives.lw.userprofiles[Directives::LW::RECON];
   			dr->dirresults[k].targets[0] = dr->trgarray[0].target[j].target;
			int target = 1;
			while(target <= Directives::LW::OneDirResult::MAXTARGETS)
			{
				dr->dirresults[k].targets[target]  =   UID_NULL;
				target++;
			}
 			dr->dirresults[k].mission.bombers = dr->tempdir.reconn.ac;
			dr->dirresults[k].mission.bomberattackmethod = MMC.directives.lw.userprofiles[Directives::LW::RECON].bomberattackmethod;
			dr->dirresults[k].mission.escortmethods	=  Profile::AM_HIGH;
			dr->dirresults[k].mission.retfighters =	0;
			if 	(dr->tempdir.reconn.escort)
				dr->dirresults[k].mission.attfighters =	-1;
			else
				dr->dirresults[k].mission.attfighters =	0;
			dr->dirresults[k].mission.detfighters =	0;

			dr->dirresults[k].mission.acselectionrules = br;
 			j++;
			k++;
			msn--;
		}
	}
	return(k);
}
void	LWDirectivesResults::FillDirectivesResults(LWDirectivesResults* dr)
{
	int k=0;
	int missions ;
	
	k = FillReconnDirectivesLine(dr,k);

	for (int i = 1; i<8;i++)
		k = FillOneDirectivesLine(dr, i, k, missions);

	dr->dirresults[k].targets[0] = UID_NULL;

}
int	LWDirectivesResults::FillOneDirectivesLine(LWDirectivesResults* dr,int i, int k, int& missions)
{
	//find bombers
	int group = 0; 														//RDH 9Aug00was float and 1.6+3.6 gave 5 missions instead of 4
	int	missionstopbitflags=0;
	float gr; 
	bool me110bombing = false;
	Profile::BetterRule br = Profile::BR_NONE;

	for (int actype = PT_JU87; actype < PT_VEHICLES;actype++)
	{
		gr = dr->tempdir.targetlines[i][actype]* dr->LWGrAvail[actype -  PT_GER_FLYABLE]+truncingfix;
		if (gr >= 1.0)
		{
			if (actype == PT_JU87)
			{
				dr->dirresults[k].squadsavail[PT_JU87]	= (gr)*3;
				br = (Profile::BetterRule)(br+ Profile::BR_R_JU87ONLY);
				MMC.directives.lw.userprofiles[Directives::LW::ATTACK].bomberattackmethod =  Profile::AM_DIVEBOMB;
			}
			if (actype == PT_JU88)
			{
				dr->dirresults[k].squadsavail[PT_JU88]	= (gr)*3;
				MMC.directives.lw.userprofiles[Directives::LW::ATTACK].bomberattackmethod =  Profile::AM_LEVELBOMB;
				br = (Profile::BetterRule)(br + Profile::BR_R_JU88ONLY);
			}
			if (actype == PT_DO17)
			{
				dr->dirresults[k].squadsavail[PT_DO17]	= (gr)*3;
				MMC.directives.lw.userprofiles[Directives::LW::ATTACK].bomberattackmethod =  Profile::AM_LEVELBOMB;
				br = (Profile::BetterRule)(br + Profile::BR_R_DO17ONLY);
			}
			if (actype == PT_HE111)
			{
				dr->dirresults[k].squadsavail[PT_HE111]	= (gr)*3;
				MMC.directives.lw.userprofiles[Directives::LW::ATTACK].bomberattackmethod =  Profile::AM_LEVELBOMB;
				br = (Profile::BetterRule)(br  + Profile::BR_R_HE111ONLY);
			}


		}
		group += gr;
	}
	
	if (group < 1.0)
	{//only count me110 if no other bomber there
		me110bombing = true;
		actype =PT_ME110;
		group = dr->tempdir.targetlines[i][actype]* dr->LWGrAvail[actype -  PT_GER_FLYABLE]+truncingfix;
		br = (Profile::BetterRule)(br + Profile::BR_R_110BONLY); 
		dr->dirresults[k].squadsavail[PT_ME110]	= (group)*3;
		if (group>=1.0 || dr->tempdir.targetlines[i][PT_ME109]* dr->LWGrAvail[PT_ME109 -  PT_GER_FLYABLE]>=1.0)
			missionstopbitflags=MTBF_ME110;
	}
	if (group >= 1)
	{
		float groupperraid = 1;
		if (dr->tempdir.targetlines[i].bombersperraid >= 30)
			groupperraid = dr->tempdir.targetlines[i].bombersperraid/30;

		missions = (group)/(groupperraid * (1+dr->tempdir.targetlines[i].secondarytargets));
		if (missions<1)
	 		missionstopbitflags=MTBF_DONTADDUP;
		else
			if (	dr->tempdir.targetlines[i][PT_ME110]* dr->LWGrAvail[PT_ME110 -  PT_GER_FLYABLE]<1.0-truncingfix
				&&	dr->tempdir.targetlines[i][PT_ME109]* dr->LWGrAvail[PT_ME109 -  PT_GER_FLYABLE]<1.0-truncingfix)
				missionstopbitflags=MTBF_NOESCORT;
	}else
		missions =0;
	//find fighters
	int lastac = PT_ME110;
	if (me110bombing)
		lastac = PT_ME109;

	float fightergroups = 0;
	for (int actypeind = PT_ME109; actypeind <= lastac; actypeind++)
	{//only use whole numbers because they are the ones the user sees

		int grpavail =  int( truncingfix + dr->tempdir.targetlines[i][actypeind]* dr->LWGrAvail[actypeind -  PT_GER_FLYABLE]);
		fightergroups += grpavail;
		if (grpavail)
		{
			if (actypeind == PT_ME109)
			{
				dr->dirresults[k].squadsavail[PT_ME109]	= (grpavail)*3;
				br = (Profile::BetterRule)(br + Profile::BR_R_109FONLY);
			}else
			{
				br = (Profile::BetterRule)(br + Profile::BR_R_110FONLY);
				dr->dirresults[k].squadsavail[PT_ME110]	= (grpavail)*3;
			}
 		}
	}
	int fightergroupremainder = 0;
	if (	(missions == 0)	|| (fightergroups == 0))
	{
		dr->otherraids.ret = 0;
		dr->otherraids.att = 0;
		dr->otherraids.det = 0;

		dr->firstraids.ret = 0;
		dr->firstraids.att = 0;
		dr->firstraids.det = 0;

	}else
	{
//DeadCode RDH 30Sep00 		float fightergroupsperraid = fightergroups/missions;
//DeadCode RDH 30Sep00 		float fightergroupsfirstraid = fightergroups - fightergroupsperraid * (missions -1);
//DeadCode RDH 30Sep00 	//	attfighters,detfighters,retfighters
//DeadCode RDH 30Sep00 
//DeadCode RDH 30Sep00 		float retescort = 1 - dr->tempdir.targetlines[i].detached - dr->tempdir.targetlines[i].attached;
//DeadCode RDH 30Sep00 		
//DeadCode RDH 30Sep00 		dr->otherraids.ret = int(retescort * fightergroupsperraid);
//DeadCode RDH 30Sep00 		dr->otherraids.att = int(dr->tempdir.targetlines[i].attached * fightergroupsperraid);
//DeadCode RDH 30Sep00 		dr->otherraids.det = fightergroupsperraid - dr->otherraids.ret - dr->otherraids.att;
//DeadCode RDH 30Sep00 
//DeadCode RDH 30Sep00 		dr->firstraids.ret = int(retescort * fightergroupsfirstraid);
//DeadCode RDH 30Sep00 		dr->firstraids.att = int(dr->tempdir.targetlines[i].attached * fightergroupsfirstraid);
//DeadCode RDH 30Sep00 		dr->firstraids.det = fightergroupsfirstraid - dr->firstraids.ret - dr->firstraids.att;

//previous system gave first raid remainder, we want to spread remainder out	//RDH 30Sep00
		int minfightergroupsperraid = fightergroups/missions;

		float retescort = 1 - dr->tempdir.targetlines[i].detached - dr->tempdir.targetlines[i].attached;
		
		dr->otherraids.ret = int(retescort * minfightergroupsperraid);
		dr->otherraids.att = int(dr->tempdir.targetlines[i].attached * minfightergroupsperraid);
		dr->otherraids.det = minfightergroupsperraid - dr->otherraids.ret - dr->otherraids.att;

		fightergroupremainder = fightergroups - minfightergroupsperraid * missions; 

		int maxfightergroupsperraid = minfightergroupsperraid + 1;
		dr->firstraids.ret = int(retescort * maxfightergroupsperraid);
		dr->firstraids.att = int(dr->tempdir.targetlines[i].attached * maxfightergroupsperraid);
		dr->firstraids.det = maxfightergroupsperraid - dr->firstraids.ret - dr->firstraids.att;

	
	}
	int j = 0;
	int* usesquadsavail=dr->dirresults[k].squadsavail;
	int	msn = missions;
	if (msn > 0)
	{//a mission means commander has shown some interest here and so up priority
		dr->tempdir.targetlines[i].lastdateandtimeused = MMC.currtime;
	}
	dr->dirresults[k].squadsavail[PT_SPIT_A] = 0;
	while (	(msn > 0) && (dr->trgarray[i].target[j].target != IllegalBAND))
	{
		dr->dirresults[k].usesquadsavail=usesquadsavail;
		if (i == Directives::LW::Targ::RECON)
		{	INT3;	//This should not happen. Recon done differently, now
			dr->dirresults[k].mission =	MMC.directives.lw.userprofiles[Directives::LW::RECON];
//DeadCode JIM 18Aug00 			dr->dirresults[k].mission.bomberattackmethod =	MMC.directives.lw.userprofiles[Directives::LW::RECON].bomberattackmethod;
//DeadCode JIM 18Aug00 			dr->dirresults[k].mission.mainalt =				MMC.directives.lw.userprofiles[Directives::LW::RECON].mainalt;
//DeadCode JIM 18Aug00 			for (int i  = 0; i <4; i++)									//RDH 9Aug00
//DeadCode JIM 18Aug00 				dr->dirresults[k].mission.formations[i] =	MMC.directives.lw.userprofiles[Directives::LW::RECON].formations[i];	//RDH 9Aug00
																		//RDH 9Aug00
		}else if	(i == Directives::LW::Targ::SWEEPSNDECOYS) 
		{	INT3;	//This should not happen. Patrols removed.
			dr->dirresults[k].mission =	MMC.directives.lw.userprofiles[Directives::LW::PATROL];
//DeadCode JIM 18Aug00 			dr->dirresults[k].mission.bomberattackmethod =	MMC.directives.lw.userprofiles[Directives::LW::PATROL].bomberattackmethod;
//DeadCode JIM 18Aug00 			dr->dirresults[k].mission.mainalt =				MMC.directives.lw.userprofiles[Directives::LW::PATROL].mainalt;
//DeadCode JIM 18Aug00 			for (int i  = 0; i <4; i++)									//RDH 9Aug00
//DeadCode JIM 18Aug00 				dr->dirresults[k].mission.formations[i] =	MMC.directives.lw.userprofiles[Directives::LW::PATROL].formations[i];	//RDH 9Aug00
																		//RDH 9Aug00
		}else
		{
			dr->dirresults[k].mission =	MMC.directives.lw.userprofiles[Directives::LW::ATTACK];
//DeadCode JIM 18Aug00 			dr->dirresults[k].mission.bomberattackmethod =	MMC.directives.lw.userprofiles[Directives::LW::ATTACK].bomberattackmethod;
//DeadCode JIM 18Aug00 			dr->dirresults[k].mission.mainalt =				MMC.directives.lw.userprofiles[Directives::LW::ATTACK].mainalt;
//DeadCode JIM 18Aug00 			for (int i  = 0; i <4; i++)									//RDH 9Aug00
//DeadCode JIM 18Aug00 				dr->dirresults[k].mission.formations[i] =	MMC.directives.lw.userprofiles[Directives::LW::ATTACK].formations[i];	//RDH 9Aug00
//DeadCode JIM 18Aug00 																		//RDH 9Aug00
		}

		dr->dirresults[k].targets[0] = dr->trgarray[i].target[j].target;

		
		//set up the secondary targets
		int maxtrg = dr->tempdir.targetlines[i].secondarytargets;	//secondary we want to hit
		if (maxtrg>5)
			maxtrg=5;
		int target = 1;
		int actualtarget = 1;
		TargetGroup* trg = Node_Data[dr->trgarray[i].target[j].target];

		while(	(target <= maxtrg)	&&	(trg->secondaries[target-1]))
		{
			TargetNoDetail* sectrg = Node_Data[trg->secondaries[target-1]];	//RDH 9Sep00
			if (sectrg)
			{
				int status = sectrg->PlayerStatus();						//RDH 9Sep00
				if (		(status == Target::TS_FLAG_UNKNOWN)				//RDH 9Sep00
						||	(status < Target::TS_BADDAMAGE)
					)
				{
					 dr->dirresults[k].targets[actualtarget++]  =   trg->secondaries[target-1];
				}															//RDH 9Sep00
			}

			target++;
		}
		int settargets = actualtarget;
		while(	(actualtarget <= Directives::LW::OneDirResult::MAXTARGETS))
		{
			dr->dirresults[k].targets[actualtarget]  =   UID_NULL;
			actualtarget++;
		}


		dr->dirresults[k].mission.bombers = -(settargets * dr->tempdir.targetlines[i].bombersperraid/10);
		if (j < fightergroupremainder)
		{
			dr->dirresults[k].mission.retfighters =	dr->firstraids.ret;
			dr->dirresults[k].mission.attfighters =	dr->firstraids.att;
			dr->dirresults[k].mission.detfighters =	dr->firstraids.det;

		}else
		{
			dr->dirresults[k].mission.retfighters =	dr->otherraids.ret;
			dr->dirresults[k].mission.attfighters =	dr->otherraids.att;
			dr->dirresults[k].mission.detfighters =	dr->otherraids.det;

		}
		dr->dirresults[k].mission.escortmethods	= dr->tempdir.escortmethods; 

//DEADCODE RDH 10/03/00 		Profile::BetterRule br = Profile::BR_NONE;
		if (dr->tempdir.targetlines[i].flags & Directives::LW::Targ::FIGHTERSSTRAFFE)
		{
			 br = (Profile::BetterRule)(br | Profile::BR_R_ASTRAFE | Profile::BR_R_DSTRAFE);
		}
//DeadCode JON 19Jun00 		if (me110bombing)
//DeadCode JON 19Jun00 			br = (Profile::BetterRule)(br + Profile::BR_R_110BONLY);
//DeadCode JON 19Jun00 		else
//DeadCode JON 19Jun00 			br = (Profile::BetterRule)(br + Profile::BR_R_REALBOMB);



		dr->dirresults[k].mission.acselectionrules = br;


		j++;
		k++;
		dr->dirresults[k].squadsavail[PT_SPIT_A] = -1;

		msn--;
	}
	
	missions+=missionstopbitflags;
	return (k);

}

void	LWDirectivesResults::FillTargetLists(LWDirectivesResults* dr)
{
#ifndef BOB_DEMO_VER
	for (int i=1 ; i < 8; i++)
	{
		int uidbandstart, uidbandend;
		int panel = Target::TT_DUMMY0;

		switch (i)
		{
//DEADCODE RDH 11/05/00 		case	Directives::LW::Targ::RECON:
//DEADCODE RDH 11/05/00 			{
//DEADCODE RDH 11/05/00 				uidbandstart = 	RAF_FighterAFBAND;
//DEADCODE RDH 11/05/00 				uidbandend =  RAF_BomberAFBAND;
//DEADCODE RDH 11/05/00 				break;
//DEADCODE RDH 11/05/00 			}
		case	Directives::LW::Targ::AIRFIELDS:
			{//AIRFIELDS
				uidbandstart = 	RAF_FighterAFBAND;
				uidbandend =  RAF_CoastalAFBAND;						//MS 15Nov00
				break;
			}
		case	Directives::LW::Targ::DOCKS:
			{//DOCKS
				uidbandstart = 	DocksBAND;
				uidbandend =  CityBAND;							//JIM 16Oct00
//DeadCode JIM 16Oct00 				uidbandend =  PortBAND;
				break;
			}
		case	Directives::LW::Targ::RADARS:
			{//RADARS
				uidbandstart = 	CLRadarBAND;
				uidbandend =  LUF_FighterLF2BAND;
				break;
			}
		case	Directives::LW::Targ::CONVOYS:
			{//CONVOYS
				uidbandstart = 	BritBoatBAND;
				uidbandend =  GermBoatBAND;
				break;
			}
		case	Directives::LW::Targ::LONDON:
			{//LONDON
				uidbandstart = 	PowerStationBAND;
				uidbandend =  PortBAND;
				panel = Target::TT_LONDON;
				break;
			}
		case	Directives::LW::Targ::FACTORIES:
			{//FACTORIES
				uidbandstart = 	PowerStationBAND;
				uidbandend =  DocksBAND;
				break;
			}
 		case	Directives::LW::Targ::SWEEPSNDECOYS:
			{//SWEEPSNDECOYS
				uidbandstart = 	RAF_FighterAFBAND;
				uidbandend =  RAF_BomberAFBAND;
				break;
			}
		default_neverreferenced; 
   
		}
		//add target from uid band to array in priority order
		FillTargetList(dr->target,uidbandstart, uidbandend, panel);

		for (int j = 0; j <LWDirectivesResults::MAX_TARGETS; j++)
		{
			dr->trgarray[i].target[j] = dr->target[j];
		}
	}
	//set up reconn requirement
	//
	int recon = 0;
	//simple sort to get reconn done in order of last target categories 
	//in which missions were set in directives
	dr->reconntrg[0] =1;
	dr->reconntrg[1] =2;
	if (dr->tempdir.targetlines[1].lastdateandtimeused < dr->tempdir.targetlines[2].lastdateandtimeused)
	{
		dr->reconntrg[0] =2;
		dr->reconntrg[1] =1;
	}
	//place radar
	if (dr->tempdir.targetlines[3].lastdateandtimeused > dr->tempdir.targetlines[dr->reconntrg[0]].lastdateandtimeused)
	{
		dr->reconntrg[2] =dr->reconntrg[1];
		dr->reconntrg[1] =dr->reconntrg[0];
		dr->reconntrg[0] =3;

	}else if (dr->tempdir.targetlines[3].lastdateandtimeused > dr->tempdir.targetlines[dr->reconntrg[1]].lastdateandtimeused)
	{
		dr->reconntrg[2] =dr->reconntrg[1];
		dr->reconntrg[1] =3;
	}else
		dr->reconntrg[2] =3;
	//place factories
	if (dr->tempdir.targetlines[5].lastdateandtimeused > dr->tempdir.targetlines[dr->reconntrg[0]].lastdateandtimeused)
	{
		dr->reconntrg[3] =dr->reconntrg[2];
		dr->reconntrg[2] =dr->reconntrg[1];
		dr->reconntrg[1] =dr->reconntrg[0];
		dr->reconntrg[0] =5;

	}else	if (dr->tempdir.targetlines[5].lastdateandtimeused > dr->tempdir.targetlines[dr->reconntrg[1]].lastdateandtimeused)
	{
		dr->reconntrg[3] =dr->reconntrg[2];
		dr->reconntrg[2] =dr->reconntrg[1];
		dr->reconntrg[1] =5;

	}else if (dr->tempdir.targetlines[5].lastdateandtimeused > dr->tempdir.targetlines[dr->reconntrg[2]].lastdateandtimeused)
	{
		dr->reconntrg[3] =dr->reconntrg[2];
		dr->reconntrg[2] =5;
	}else
		dr->reconntrg[3] =5;

	i = 0;
	while 	(i < LWDirectivesResults::MAX_TARGETS)
	{
		dr->trgarray[0].target[i++].target = (UniqueID)IllegalBAND;
	}

	for (i = 0; i < 4; i++)	//airfields to factories above
	{
		for (int t = 0; t <LWDirectivesResults::MAX_TARGETS; t++)
		{
			UniqueID uid = 	(UniqueID)dr->trgarray[dr->reconntrg[i]].target[t].target;
			TargetNoDetail* trg = Node_Data[uid];
			if (trg)
			{
//DeadCode JIM 3Jul00 				int dstatus = trg->knownstatus - trg->truestatus;
//DeadCode JIM 3Jul00 				if (dstatus < 0)
//DeadCode JIM 3Jul00 				dstatus = -dstatus;
//DeadCode JIM 3Jul00 				if (dstatus > 8)
				if (trg->ReconAdvised())
					dr->trgarray[0].target[recon++].target = uid;
				if (recon >= LWDirectivesResults::MAX_TARGETS)
					break;
			}

		}

	}
#endif
}
void	LWDirectivesResults::AutoLWPackages()
{
#ifndef BOB_DEMO_VER

	
	MMC.directives.lw.userprofiles[Directives::LW::RECON].mainalt = METRES2000 + METRES1000*Math_Lib.rnd(4);
	MMC.directives.lw.userprofiles[Directives::LW::ATTACK].mainalt= METRES3000 + METRES1000*Math_Lib.rnd(4);


	Directives::LW::SetUpReconn();
	LWDirectivesResults*	dr = new LWDirectivesResults;
	dr->tempdir = MMC.directives.lw.current; 
	FillTargetLists(dr);
	FindAcAvail(dr);
	FillDirectivesResults(dr);
	MakeLWPackages(dr, false);
	if (dr)
		delete dr;
#endif


}
bool	NodeData::GotBadWeatherPeriod(bool& alldayreturn,bool& informreturn)
{
	bool	alldaylocal;
	bool &badweatherallday=(&alldayreturn==NULL)?alldaylocal:alldayreturn;
	bool &infoofbadweather=(&informreturn==NULL)?alldaylocal:informreturn;
	badweatherallday = false;
	infoofbadweather=false;
	bool badweather = false;

	int daynum= (MMC.currdate-JUL10th1940)/SECSPERDAY;

	HistoricInfo::WeatherType weather;
	if (MMC.currtime<MIDDAYPERIODSTART)
	{
		weather = historicinfo.day[daynum].morning;
		if	(weather== HistoricInfo::NOFLY)
		{
			badweather = true;
			infoofbadweather = true;
			if (		(historicinfo.day[daynum].midday == HistoricInfo::NOFLY)
					&&	(historicinfo.day[daynum].afternoon == HistoricInfo::NOFLY)
				)
				badweatherallday = true;
		}

	}else if (	(MMC.currtime>MIDDAYPERIODSTART && MMC.currtime < AFTERNOONPERIODSTART)	)
	{
		weather = historicinfo.day[daynum].midday;
		if	(weather== HistoricInfo::NOFLY)
		{
				badweather = true;
				if	(historicinfo.day[daynum].morning != HistoricInfo::NOFLY)
					infoofbadweather = true;
		}

	}
	else if (MMC.currtime>AFTERNOONPERIODSTART 	)
	{
		weather = historicinfo.day[daynum].afternoon;
		if	(weather== HistoricInfo::NOFLY)
		{
			badweather = true;
			if	(		(historicinfo.day[daynum].midday !=  HistoricInfo::NOFLY)
				)
				infoofbadweather = true;
		}
	}

	return	badweather;

}

bool	NodeData::BadWeatherCheck()
{
	bool badweatherallday;
	bool infoofbadweather;
	bool badweather = GotBadWeatherPeriod(badweatherallday,infoofbadweather);
#ifndef	BOB_DEMO_VER
	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
	main->m_titlebar.Redraw();	//this forces the clock to show the start time for the period.
								//It should be good enough for pilot mode as well.	
	if	(badweatherallday)
	{
		if (RDialog::RMessageBox(IDS_BADWEATHER, IDS_NOFLYTODAY,IDS_SKIP_PERIOD,IDS_CONTINUE)==1)
			badweather=false;
	}
   	elseif	(badweather)
	{
		if (RDialog::RMessageBox(IDS_BADWEATHER, IDS_NOFLYSESSION,IDS_SKIP_PERIOD,IDS_CONTINUE)==1)
			badweather=false;
	}
	else
		if (MMC.phasechanged)
			MMC.phasechanged++;
#endif
	return(badweather);
}
//////////////////////////////////////////////////////////////////////
//
// Function:    IsPlayerUsedInDirectives
// Date:		31/03/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	PackageList::IsPlayerUsedInDirectives()
{	//Is the prefered squadron used in the directives?
	//If not, skip the period!
	//NOTE THAT THIS TURNS RECURSIVE!!!!!!
#ifndef	BOB_DEMO_VER
	SquadNum	playerslot[3]={SquadNum(MMC.fav.squadron)};
	if (localplayer==NAT_LUF)
		if (MMC.fav.geschwader>=0)	  //Don't skip periods if above geschwader level!
		{
			//find package that has current wadernum
//DeadCode JIM 20Oct00 			int	grn=0;
			if (MMC.fav.gruppe>=0)
				playerslot[0]=Node_Data.gruppe[MMC.fav.geschwader*3+MMC.fav.gruppe].squadron;
			else
			{
				playerslot[0]=Node_Data.gruppe[MMC.fav.geschwader*3].squadron;
				playerslot[1]=Node_Data.gruppe[MMC.fav.geschwader*3+1].squadron;
				playerslot[2]=Node_Data.gruppe[MMC.fav.geschwader*3+2].squadron;

			}

		}

	int	package=-1;
	if (playerslot[0] && !GetSquadEntry(playerslot[0],package) && !GetSquadEntry(playerslot[1],package) && !GetSquadEntry(playerslot[2],package))
	{	//player NOT in 3D!!!
		int	rv=RDialog::RMessageBox(IDS_AIRCRAFTALLOCATION, IDS_SQUADNOTFLYING,IDS_SKIP_PERIOD,IDS_TRANSFER,IDS_CONTINUE);
		if (rv==0)
		{
			int period;
			while ((period=Node_Data.PerformMoveCycle())==0)
				MMC.accumulator=SECSPERSAGFRAME;
			Node_Data.PerformNextPeriod(period);
		}
		else
			if (rv==1)
				TitleBarPtr().OpenTimeControl(1);
	}
#endif
}

void	LWDirectivesResults::LaunchDirectiveMissions()
{
#ifndef	BOB_DEMO_VER

		if (Math_Lib.rnd(RndValMAX) < RND50PC)
			MMC.directives.lw.current.reconn.escortactype = PT_ME109;
		else
			MMC.directives.lw.current.reconn.escortactype = PT_ME110;

		if (Todays_Packages.localplayer==NAT_RAF)
		{
			AutoLWPackages();
			if (Todays_Packages.britishisauto)
			{
				Node_Data.SetRAFReadiness();
				Directives::RAF::SessionAI();
				RAFDirectivesResults::AutoRAFPatrols();
				Todays_Packages.IsPlayerUsedInDirectives();
			}
			else
			if (!MMC.directivespopup)
				MiscToolBar().OpenRAFDirectivetoggle(NULL);
		}else
		{
			Node_Data.SetRAFReadiness();
			Directives::RAF::SessionAI();
			RAFDirectivesResults::AutoRAFPatrols();
			if (Todays_Packages.germanisauto)
			{
				AutoLWPackages();
				Todays_Packages.IsPlayerUsedInDirectives();
			}
			else
			if (!MMC.directivespopup)
				MiscToolBar().OpenDirectivetoggle(NULL);

		}
#endif
}
void	LWDirectivesResults::SetUpLWDirectives(Directives::LW::HistTypes dirtype)
{
	MMC.directives.lw.current = MMC.directives.lw.histdir[dirtype];

	switch (dirtype)
	{												   
		case	Directives::LW::HistTypes::LWHISTORICALPHASE1A:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_HIGH;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE1B:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_HIGH;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE1C:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_FORWARD_LOW;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE1D:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_FORWARD_LOW;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE2A:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_HIGH;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE2B:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_HIGH;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE2C:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_HIGH;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE2D:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_HIGH;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE3A:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_HIGH;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE3B:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_HIGH;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE3C:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_HIGH;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE3D:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_HIGH;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE4A:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_HIGH;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			MMC.directives.lw.current.escortmethods |= Profile::AM_PORT;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE4B:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_HIGH;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			MMC.directives.lw.current.escortmethods |= Profile::AM_PORT;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE4C:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_HIGH;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			MMC.directives.lw.current.escortmethods |= Profile::AM_PORT;
			break;
		}
		case	Directives::LW::HistTypes::LWHISTORICALPHASE4D:
		{
			MMC.directives.lw.current.escortmethods |= Profile::AM_HIGH;
			MMC.directives.lw.current.escortmethods |= Profile::AM_ABOVE;
			MMC.directives.lw.current.escortmethods |= Profile::AM_PORT;
			break;
		}

	}
}

void LWDirectives::OnTextChangedRspinbutReconnAircraft(LPCTSTR caption, short Index) 
{
	dr->tempdir.reconn.ac = Index+1;	
}

void LWDirectives::OnTextChangedRspinbutReconnMissons(LPCTSTR caption, short Index) 
{
	dr->tempdir.reconn.missions = Index;	
	Refresh();

}

void LWDirectives::OnClickedReconnAmonly() 
{
	if (dr->tempdir.reconn.morningonly)
		dr->tempdir.reconn.morningonly = false;		
	else
		dr->tempdir.reconn.morningonly = true;
	Refresh();
}

void LWDirectives::OnClickedReconnEscort() 
{
	if (dr->tempdir.reconn.escort)
		dr->tempdir.reconn.escort = false;		
	else
		dr->tempdir.reconn.escort = true;
	Refresh();

}
void	Directives::LW::SetUpReconn()
{
	if (Math_Lib.rnd(RndValMAX) >= RND90PC)
		MMC.directives.lw.current.reconn.morningonly = false;
	else
		MMC.directives.lw.current.reconn.morningonly = true;

	if (Math_Lib.rnd(RndValMAX) >= RND90PC)
		MMC.directives.lw.current.reconn.ac = 2;
	else
		MMC.directives.lw.current.reconn.ac = 1;

	if (Math_Lib.rnd(RndValMAX) >= RND75PC)
		MMC.directives.lw.current.reconn.missions = 1;
	else
		MMC.directives.lw.current.reconn.missions = 2;

	if (MMC.thisweekreview.DecayingLossRate(PT_DO17))	//##
	   MMC.directives.lw.current.reconn.escort = true;
	else
	   MMC.directives.lw.current.reconn.escort = false;

//############debug only						 rdh 14/7/00
//DeadCode rdh 17Jul00 	MMC.directives.lw.current.reconn.ac = 0;
//DeadCode rdh 17Jul00 	MMC.directives.lw.current.reconn.missions = 0;
//DeadCode rdh 17Jul00 	MMC.directives.lw.current.reconn.escort = false;

//############debug only

}
void	Directives::LW::AI()
{
	 Directives::LW::HistTypes olddir = MMC.lwdir;


//DeadCode MS 09Nov00  	switch (olddir)
//DeadCode MS 09Nov00 	{
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE1A:
//DeadCode MS 09Nov00 		{
//DeadCode MS 09Nov00 			if (MMC.currdate >= JUL15th1940)
//DeadCode MS 09Nov00 			   	 MMC.lwdir =  LWHISTORICALPHASE1B;
//DeadCode MS 09Nov00 			break;
//DeadCode MS 09Nov00 		}
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE1B:
//DeadCode MS 09Nov00 		{
//DeadCode MS 09Nov00 			if (MMC.currdate >= JUL20th1940)
//DeadCode MS 09Nov00 		   		MMC.lwdir =  LWHISTORICALPHASE1C;
//DeadCode MS 09Nov00 			break;
//DeadCode MS 09Nov00 		}
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE1C:
//DeadCode MS 09Nov00 		{
//DeadCode MS 09Nov00 			if (MMC.currdate >= JUL25th1940)
//DeadCode MS 09Nov00 		   		MMC.lwdir =  LWHISTORICALPHASE1D;
//DeadCode MS 09Nov00 			break;
//DeadCode MS 09Nov00 		}
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE1D:
//DeadCode MS 09Nov00 		{
//DeadCode MS 09Nov00 			if	(Save_Data.gamedifficulty[GD_LWTACTICS])
//DeadCode MS 09Nov00 			{
//DeadCode MS 09Nov00 				if (MMC.currdate >= JUL31st1940)
//DeadCode MS 09Nov00 					MMC.lwdir =  LWHISTORICALPHASE2A;
//DeadCode MS 09Nov00 			}else
//DeadCode MS 09Nov00 			{
//DeadCode MS 09Nov00 				if (MMC.currdate >= AUG12th1940)
//DeadCode MS 09Nov00 					MMC.lwdir =  LWHISTORICALPHASE2A;
//DeadCode MS 09Nov00 			}
//DeadCode MS 09Nov00 			   	 
//DeadCode MS 09Nov00 			break;
//DeadCode MS 09Nov00 		}
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE2A:
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE2B:
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE2C:
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE2D:
//DeadCode MS 09Nov00 		{
//DeadCode MS 09Nov00 			if	(Save_Data.gamedifficulty[GD_LWTACTICS])
//DeadCode MS 09Nov00 			{
//DeadCode MS 09Nov00 				if (		(Node_Data.LWFindPercentAvail(CLRadarBAND, LUF_FighterLF2BAND, Target::TP_RADAR_HP, Target::TP_RADAR) > 80)
//DeadCode MS 09Nov00 						||	(MMC.currdate >= AUG23rd1940)
//DeadCode MS 09Nov00 				   )
//DeadCode MS 09Nov00 				   	 MMC.lwdir =  LWHISTORICALPHASE3A;
//DeadCode MS 09Nov00 			}else
//DeadCode MS 09Nov00 			{
//DeadCode MS 09Nov00 				if 	(MMC.currdate >= AUG23rd1940)
//DeadCode MS 09Nov00 				   	 MMC.lwdir =  LWHISTORICALPHASE3A;
//DeadCode MS 09Nov00 			}
//DeadCode MS 09Nov00 	  		if (		(Node_Data.LWFindPercentAvail(RAF_FighterAFBAND, CLRadarBAND, Target::TP_PRIMARYCOASTALAF, Target::TP_SECONDARYCOASTALAF) < 50)
//DeadCode MS 09Nov00 					||	(MMC.currdate >= AUG16th1940)
//DeadCode MS 09Nov00 			   )
//DeadCode MS 09Nov00 			   	 MMC.lwdir =  LWHISTORICALPHASE2B;
//DeadCode MS 09Nov00 			else
//DeadCode MS 09Nov00 			   	 MMC.lwdir =  LWHISTORICALPHASE2A;
//DeadCode MS 09Nov00 	
//DeadCode MS 09Nov00 	
//DeadCode MS 09Nov00 			break;
//DeadCode MS 09Nov00 		}
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE3A:
//DeadCode MS 09Nov00 		{
//DeadCode MS 09Nov00 			if	(Save_Data.gamedifficulty[GD_LWTACTICS])
//DeadCode MS 09Nov00 			{
//DeadCode MS 09Nov00 				if (		(Node_Data.LWFindPercentAvail(CLRadarBAND, LUF_FighterLF2BAND, Target::TP_RADAR_HP, Target::TP_RADAR) < 70)
//DeadCode MS 09Nov00 						&&	(MMC.currdate >= AUG26th1940)
//DeadCode MS 09Nov00 						&&	(MMC.currdate < AUG30th1940)
//DeadCode MS 09Nov00 				   )
//DeadCode MS 09Nov00 				   	 MMC.lwdir =  LWHISTORICALPHASE3B;
//DeadCode MS 09Nov00 				if 	(MMC.currdate >= SEP10th1940)
//DeadCode MS 09Nov00 				   	 MMC.lwdir =  LWHISTORICALPHASE4A;
//DeadCode MS 09Nov00 		  		if	(		(Node_Data.LWFindPercentAvail(RAF_FighterAFBAND, CLRadarBAND, Target::TP_PRIMARYCOASTALAF, Target::TP_SECONDARYINLANDAF) > 90)
//DeadCode MS 09Nov00 					&&	(MMC.currdate >= AUG28th1940)
//DeadCode MS 09Nov00 				)
//DeadCode MS 09Nov00 				   	 MMC.lwdir =  LWHISTORICALPHASE4A;
//DeadCode MS 09Nov00 
//DeadCode MS 09Nov00 			}else
//DeadCode MS 09Nov00 			{
//DeadCode MS 09Nov00 				if 	(MMC.currdate >= SEP7th1940)
//DeadCode MS 09Nov00 				   	 MMC.lwdir =  LWHISTORICALPHASE4A;
//DeadCode MS 09Nov00 			}
//DeadCode MS 09Nov00 	  		if	(		(Node_Data.LWFindPercentAvail(RAF_FighterAFBAND, CLRadarBAND, Target::TP_PRIMARYCOASTALAF, Target::TP_SECONDARYINLANDAF) > 50)
//DeadCode MS 09Nov00 					&&	(MMC.currdate >= AUG28th1940)
//DeadCode MS 09Nov00 				)
//DeadCode MS 09Nov00 				   	 MMC.lwdir =  LWHISTORICALPHASE3C;
//DeadCode MS 09Nov00 
//DeadCode MS 09Nov00 			break;
//DeadCode MS 09Nov00 		}
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE3B:
//DeadCode MS 09Nov00 		{//only for optimum tactics
//DeadCode MS 09Nov00 			if (Node_Data.LWFindPercentAvail(CLRadarBAND, LUF_FighterLF2BAND, Target::TP_RADAR_HP, Target::TP_RADAR) > 85)
//DeadCode MS 09Nov00 		   		MMC.lwdir =  LWHISTORICALPHASE3A;
//DeadCode MS 09Nov00 			break;
//DeadCode MS 09Nov00 		}
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE3C:
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE3D:
//DeadCode MS 09Nov00 		{
//DeadCode MS 09Nov00 			if	(Save_Data.gamedifficulty[GD_LWTACTICS])
//DeadCode MS 09Nov00 			{
//DeadCode MS 09Nov00 				if 	(MMC.currdate >= SEP10th1940)
//DeadCode MS 09Nov00 				   	 MMC.lwdir =  LWHISTORICALPHASE4A;
//DeadCode MS 09Nov00 			}else
//DeadCode MS 09Nov00 			{
//DeadCode MS 09Nov00 				if 	(MMC.currdate >= SEP7th1940)
//DeadCode MS 09Nov00 				   	 MMC.lwdir =  LWHISTORICALPHASE4A;
//DeadCode MS 09Nov00 			}
//DeadCode MS 09Nov00 	  		if	(		(Node_Data.LWFindPercentAvail(RAF_FighterAFBAND, CLRadarBAND, Target::TP_PRIMARYCOASTALAF, Target::TP_SECONDARYINLANDAF) < 25)
//DeadCode MS 09Nov00 				)
//DeadCode MS 09Nov00 				   	 MMC.lwdir =  LWHISTORICALPHASE3A;
//DeadCode MS 09Nov00 			break;
//DeadCode MS 09Nov00 		}
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE4A:
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE4B:
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE4C:
//DeadCode MS 09Nov00 		case	LWHISTORICALPHASE4D:
//DeadCode MS 09Nov00 		{
//DeadCode MS 09Nov00 			if	(Save_Data.gamedifficulty[GD_LWTACTICS])
//DeadCode MS 09Nov00 			{
//DeadCode MS 09Nov00  		  		if	(		(Node_Data.LWFindPercentAvail(RAF_FighterAFBAND, CLRadarBAND, Target::TP_PRIMARYCOASTALAF, Target::TP_SECONDARYINLANDAF) < 25)
//DeadCode MS 09Nov00 					)
//DeadCode MS 09Nov00 				   	 MMC.lwdir =  LWHISTORICALPHASE3A;
//DeadCode MS 09Nov00 
//DeadCode MS 09Nov00 			}
//DeadCode MS 09Nov00 			if 	(MMC.currdate >= SEP15th1940)					//JIM 16Oct00
//DeadCode MS 09Nov00 				   	 MMC.lwdir =  LWHISTORICALPHASE4B;					//RDH 12Oct00
//DeadCode MS 09Nov00 //this line doesn't make any sense										//RDH 12Oct00
//DeadCode MS 09Nov00 //DeadCode JIM 16Oct00 		   	 MMC.lwdir =  LWHISTORICALPHASE1B;
//DeadCode MS 09Nov00 			break;
//DeadCode MS 09Nov00 		}
 	switch (olddir)
	{
		case	LWHISTORICALPHASE1A:
		{
			if	(Save_Data.gamedifficulty[GD_LWTACTICS])
			{
				if (MMC.currdate >= JUL15th1940)
					MMC.lwdir =  LWHISTORICALPHASE1D;
			}else
			{
			if (MMC.currdate >= JUL15th1940)
			   	 MMC.lwdir =  LWHISTORICALPHASE1B;
			}
			break;
		}
		case	LWHISTORICALPHASE1B:
		{
			if (MMC.currdate >= JUL20th1940)
		   		MMC.lwdir =  LWHISTORICALPHASE1C;
			break;
		}
		case	LWHISTORICALPHASE1C:
		{
			if (MMC.currdate >= JUL25th1940)
		   		MMC.lwdir =  LWHISTORICALPHASE1D;
			break;
		}
		case	LWHISTORICALPHASE1D:
		{
			if	(Save_Data.gamedifficulty[GD_LWTACTICS])
			{
				if (MMC.currdate >= JUL31st1940)
					MMC.lwdir =  LWHISTORICALPHASE2B;
			}else
			{
				if (MMC.currdate >= AUG12th1940)
					MMC.lwdir =  LWHISTORICALPHASE2A;
			}
			   	 
			break;
		}
		case	LWHISTORICALPHASE2A:	//Stukas on airfields and radar, Level bombers on docks
		case	LWHISTORICALPHASE2B:	//All stukas on radar, all bombers on airfields
		case	LWHISTORICALPHASE2C:
		case	LWHISTORICALPHASE2D:
		{
			if	(Save_Data.gamedifficulty[GD_LWTACTICS])
			{
				if 
				(		(Node_Data.LWFindPercentAvail(CLRadarBAND, LUF_FighterLF2BAND, Target::TP_RADAR_HP, Target::TP_RADAR) > 50)
						||	(MMC.currdate >= AUG23rd1940)
				)
				   	 MMC.lwdir =  LWHISTORICALPHASE3C;
				else
				   	 MMC.lwdir =  LWHISTORICALPHASE2B;
					
			}else
			{
				if 	(MMC.currdate >= AUG15th1940)
				   	 MMC.lwdir =  LWHISTORICALPHASE2B;
				if 	(MMC.currdate >= AUG23rd1940)
				   	 MMC.lwdir =  LWHISTORICALPHASE3A;
			}
			break;
		}
		case	LWHISTORICALPHASE3A:	//Most on Airfields with 2ndarys, some on factories. close escort. 
		{
			if	(Save_Data.gamedifficulty[GD_LWTACTICS])
			{
				if (		(Node_Data.LWFindPercentAvail(CLRadarBAND, LUF_FighterLF2BAND, Target::TP_RADAR_HP, Target::TP_RADAR) < 40)
						&&	(MMC.currdate >= AUG26th1940)
						&&	(MMC.currdate < AUG30th1940)
				   )
				   	 MMC.lwdir =  LWHISTORICALPHASE3B;
//DeadCode MS 16Nov00 		  		if	(		(Node_Data.LWFindPercentAvail(RAF_FighterAFBAND, CLRadarBAND, Target::TP_PRIMARYCOASTALAF, Target::TP_SECONDARYINLANDAF) > 90)
//DeadCode MS 16Nov00 					&&	(MMC.currdate >= SEP10th1940)
//DeadCode MS 16Nov00 				)
//DeadCode MS 16Nov00 				   	 MMC.lwdir =  LWHISTORICALPHASE4A;
//DeadCode MS 16Nov00 		  		if	(		(Node_Data.LWFindPercentAvail(RAF_FighterAFBAND, CLRadarBAND, Target::TP_PRIMARYCOASTALAF, Target::TP_SECONDARYINLANDAF) > 50)
//DeadCode MS 16Nov00 					&&	(MMC.currdate < AUG30th1940)
//DeadCode MS 16Nov00 				)
//DeadCode MS 16Nov00 				   	 MMC.lwdir =  LWHISTORICALPHASE3C;
		  		if	(MMC.currdate < AUG28th1940)
				  	 MMC.lwdir =  LWHISTORICALPHASE3C;

			}else
			{
				if 	(MMC.currdate >= SEP7th1940)
				   	 MMC.lwdir =  LWHISTORICALPHASE4A;
			}
	  		if	(		(Node_Data.LWFindPercentAvail(RAF_FighterAFBAND, CLRadarBAND, Target::TP_PRIMARYCOASTALAF, Target::TP_SECONDARYINLANDAF) > 90)
					&&	(MMC.currdate >= AUG28th1940)
				)
				   	 MMC.lwdir =  LWHISTORICALPHASE3C;

			break;
		}
		case	LWHISTORICALPHASE3B:	//Opt only. Afs, no 2darys. Stukas and 110s to radar 
		{//only for optimum tactics
			if (	(Node_Data.LWFindPercentAvail(CLRadarBAND, LUF_FighterLF2BAND, Target::TP_RADAR_HP, Target::TP_RADAR) > 50)
					|| (MMC.currdate >= AUG30th1940)
				)
		   		MMC.lwdir =  LWHISTORICALPHASE3A;
			break;
		}
		case	LWHISTORICALPHASE3C:	//Half on Afs, Half Factories. No 2ndarys
		case	LWHISTORICALPHASE3D:
		{
			if	(Save_Data.gamedifficulty[GD_LWTACTICS])
			{
				if 	(MMC.currdate >= SEP15th1940)
				   	 MMC.lwdir =  LWHISTORICALPHASE4B;
		  		if	(		(Node_Data.LWFindPercentAvail(RAF_FighterAFBAND, CLRadarBAND, Target::TP_PRIMARYCOASTALAF, Target::TP_SECONDARYINLANDAF) < 45)
						||	(MMC.currdate >= AUG28th1940)
					)
				   	 MMC.lwdir =  LWHISTORICALPHASE3A;
			}else
			{
				if 	(MMC.currdate >= SEP7th1940)
				   	 MMC.lwdir =  LWHISTORICALPHASE4A;
			}
			break;
		}
		case	LWHISTORICALPHASE4A:
		case	LWHISTORICALPHASE4B:
		case	LWHISTORICALPHASE4C:
		case	LWHISTORICALPHASE4D:
		{
			if	(Save_Data.gamedifficulty[GD_LWTACTICS])
			{
 		  		if	(		(Node_Data.LWFindPercentAvail(RAF_FighterAFBAND, CLRadarBAND, Target::TP_PRIMARYCOASTALAF, Target::TP_SECONDARYINLANDAF) < 25)
					)
				   	 MMC.lwdir =  LWHISTORICALPHASE3A;

			}
			if 	(MMC.currdate >= SEP15th1940)					//JIM 16Oct00
				   	 MMC.lwdir =  LWHISTORICALPHASE4B;					//RDH 12Oct00
//this line doesn't make any sense										//RDH 12Oct00
//DeadCode JIM 16Oct00 		   	 MMC.lwdir =  LWHISTORICALPHASE1B;
			break;
		}

	}



	if (olddir  != MMC.lwdir)
	{
		 MMC.phasechanged = 1;
		 LWDirectivesResults::SetUpLWDirectives(MMC.lwdir);
	}
	

}


void LWDirectives::OnClickedRbuttonrest() 
{
	for (int actype = PT_GER_FLYABLE; actype < PT_VEHICLES;actype++)
	{
		for(int ttype =1; ttype<Directives::LW::Targ::RESTING;ttype++)
			dr->tempdir.targetlines[ttype][actype] = 0;
		dr->tempdir.targetlines[Directives::LW::Targ::RESTING][actype] = 1;
		
	}	
	RefreshGruppe();
	RefreshMissions();
	
}

void LWDirectives::OnTextChangedEscortProportion(LPCTSTR Caption, short index) 
{
	// TODO: Add your control notification handler code here
	dr->tempdir.escortproportion=escortusage[index];	
	Refresh();
}

void LWDirectives::OnTextChangedJu87Period(LPCTSTR Caption, short index) 
{
	// TODO: Add your control notification handler code here
	dr->tempdir.ju87usage=(Directives::LW::Ju87Usage)index;
	Refresh();
}
