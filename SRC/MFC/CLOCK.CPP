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

// RowanDialog: // clock.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "clock.h"
#include	"Mytime.h"
#include	"mymath.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif


/////////////////////////////////////////////////////////////////////////////
// Clock dialog


RDialog*	Clock::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_CLOCK,new Clock())
			);
}


Clock::Clock(CWnd* pParent /*=NULL*/)
	: RowanDialog(Clock::IDD, pParent)
{
	//{{AFX_DATA_INIT(Clock)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Clock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Clock)
	DDX_Control(pDX, IDJ_TITLE, m_IDJ_TITLE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Clock, CDialog)
	//{{AFX_MSG_MAP(Clock)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Clock message handlers
	enum	{CENTREX = 80, CENTREY = 74,THICKNESS=4,RADIUSBH=45,RADIUSSH=30};

BOOL Clock::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_IDJ_TITLE.SetHelpButton(FALSE);
			
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void Clock::RefreshData(int childnum)
{
	InvalidateRect(
		CRect(	CENTREX-RADIUSBH-THICKNESS,CENTREY-RADIUSBH-THICKNESS,
				CENTREX+RADIUSBH+THICKNESS,CENTREY+RADIUSBH+THICKNESS)

		,FALSE);
}

void Clock::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CDialog::DoPaint(&dc);


	LOGBRUSH brush={PS_SOLID,RGB(80,80,80),HS_CROSS};
	CPen penf (PS_GEOMETRIC+PS_SOLID+PS_ENDCAP_ROUND,THICKNESS,&brush,0);
//DEADCODE RDH 07/12/99 	CPen penb (PS_SOLID+PS_ENDCAP_ROUND,4,RGB(100,50,10));
	CPen* oldpen=dc.SelectObject(&penf);

	SLong time, hours_int;
	Float	mins, hours;
	time = Miss_Man.camp.currtime;
	//temp
//	time = 	HR16MIN40;


	mins = time/60.0;
	time = time/60;			//total in mins
	hours_int = time/60;
	hours = mins;
	hours = hours/60.0;
	mins = mins - hours_int*60;
	if (hours > 12)
		hours = hours -12;

//minute hand	
	ANGLES hand;
	Float	sin_ang,cos_ang;
	SLong	radius,x,y;

	lastrect=CRect(CENTREX,CENTREY,CENTREX,CENTREY);

	mins = mins*65536/60;
	hand = (Angles)((SLong)mins) ;

	Math_Lib.high_sin_cos(hand, sin_ang,cos_ang);

	radius = RADIUSBH;
	x = (sin_ang * radius);
	y = (cos_ang * radius);
	x=CENTREX+x;
	y=CENTREY-y;

	dc.MoveTo(CENTREX,CENTREY);
	dc.LineTo(x,y);

//hour hand
	hours = hours*65536/12;
	hand = (Angles)((SLong)hours) ;

	Math_Lib.high_sin_cos(hand, sin_ang,cos_ang);

	radius = RADIUSSH;
	x = (sin_ang * radius);
	y = (cos_ang * radius);
	x=CENTREX+x;
	y=CENTREY-y;

	dc.MoveTo(CENTREX,CENTREY);
	dc.LineTo(x,y);



	dc.SelectObject(oldpen);

	// Do not call CDialog::OnPaint() for painting messages
}
