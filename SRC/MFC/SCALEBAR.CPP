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

// RowanDialog: // ScaleBar.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "ScaleBar.h"
#include "migview.h"
#include "mainfrm.h"
#include "savegame.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CScaleBar dialog


CScaleBar::CScaleBar(CWnd* pParent /*=NULL*/)
	: CRToolBar(pParent)
{
	//{{AFX_DATA_INIT(CScaleBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_RButtonDown=FALSE;
}


void CScaleBar::DoDataExchange(CDataExchange* pDX)
{
	CRToolBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScaleBar, CRToolBar)
	//{{AFX_MSG_MAP(CScaleBar)
//DEADCODE JIM 28/01/00 	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScaleBar message handlers
enum	{SCALESTARTPIX=25,DRAWSTARTPIX=30,TEXTSTARTPIX=35,TEXTSTARTDELTA=1,MARGINSTARTPIX=5};
//DEADCODE JIM 28/01/00 BOOL CScaleBar::OnEraseBkgnd(CDC* pDC) 
//DEADCODE JIM 28/01/00 {
//DEADCODE JIM 28/01/00 	return TRUE;
//DEADCODE JIM 28/01/00 }
FileNum  CScaleBar::OnGetArt()
{
//DEADCODE JIM 28/01/00 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
//DEADCODE JIM 28/01/00 	{
//DEADCODE JIM 28/01/00 		if (m_bHorzAlign) 
//DEADCODE JIM 28/01/00 			return FIL_TOOL_HORIZONTAL_LW;
//DEADCODE JIM 28/01/00 		else
//DEADCODE JIM 28/01/00 			return FIL_TOOL_VERTICAL_LW;
//DEADCODE JIM 28/01/00 	}else
	{
		if (m_align&1) 
			return FIL_TOOL_TOPRULE;
		else
			return FIL_TOOL_SIDERULE;
	}
}

void CScaleBar::OnSize(UINT nType, int cx, int cy) 
{
	CRToolBar::OnSize(nType, cx, cy);
	Invalidate();
}

enum	RPointEntry{RP_SCALEEDGE,RP_SMALLSCALE,RP_MEDSCALE,RP_BIGSCALE,RP_NUMBER,RP_UNIT,RP_MAX};
class	RPoint
{
public:
	typedef	int	RPointPos[RP_MAX];
	virtual	CPoint	operator()(int along,RPointEntry across)=0;
	int	maxalong;
};

class	RPointTop :public RPoint
{
	static RPointPos	indexes;
	CPoint		operator()(int along,RPointEntry across)
	{	return CPoint(along,indexes[across]);	}
} R_PointTop;
class	RPointBot:public RPoint
{
	static RPointPos	indexes;
	CPoint		operator()(int along,RPointEntry across)
	{	return CPoint(along,indexes[across]);	}
} R_PointBot;

//enum	RPointEntry{RP_SCALEEDGE,RP_SMALLSCALE,RP_MEDSCALE,RP_BIGSCALE,RP_NUMBER,RP_UNIT,RP_MAX};
enum	{M_WIDTH=48};
//DEADCODE RDH 13/04/00 RPoint::RPointPos	RPointTop::indexes=		{2,10,12,14,30,45};
//DEADCODE RDH 13/04/00 RPoint::RPointPos	RPointBot::indexes=		{M_WIDTH-2,M_WIDTH-10,M_WIDTH-12,M_WIDTH-14,15,30};
RPoint::RPointPos	RPointTop::indexes=		{2,8,10,14,25,40};
RPoint::RPointPos	RPointBot::indexes=		{M_WIDTH-2,M_WIDTH-10,M_WIDTH-12,M_WIDTH-14,35,10};

class	RPointLeft:public RPoint
{
	static RPointPos	indexes;
	CPoint		operator()(int along,RPointEntry across)
	{	return CPoint(indexes[across],along);	}
} R_PointLeft;
class	RPointRight:public RPoint
{
	static RPointPos	indexes;
	CPoint		operator()(int along,RPointEntry across)
	{	return CPoint(indexes[across],along);	}
} R_PointRight;

//DEADCODE RDH 13/04/00 RPoint::RPointPos	RPointLeft::indexes=	{2,10,12,14,M_WIDTH-2,M_WIDTH-2};
RPoint::RPointPos	RPointLeft::indexes=	{2,10,12,14,M_WIDTH-10,M_WIDTH-10};
//DEADCODE RDH 13/04/00 RPoint::RPointPos	RPointRight::indexes=	{M_WIDTH-2,M_WIDTH-10,M_WIDTH-12,M_WIDTH-14,30,30};
RPoint::RPointPos	RPointRight::indexes=	{M_WIDTH-2,M_WIDTH-10,M_WIDTH-12,M_WIDTH-14,40,40};


void	PointTextOut(CDC* pDC,CPoint p,CString s)
{
	pDC->TextOut(p.x,p.y,s);
}

void CScaleBar::OnPaint() 
{
	if (m_init) return;
	PAINTSTRUCT paintstruct;
	CDC* pDC;
	pDC=this->BeginPaint(&paintstruct);
    pDC->SetBkMode(TRANSPARENT);
//DEADCODE RDH 13/04/00     pDC->SetTextColor(RGB(255,255,255));
    pDC->SetTextColor(RGB(0,0,0));
	CPen* originalpen=(CPen*)pDC->SelectStockObject(BLACK_PEN);
	CRect rect;
	this->GetClientRect(rect);
//TEMPCODE JIM 06/12/99 	if (m_bHorzAlign) rect.left+=SCALESTARTPIX;
//TEMPCODE JIM 06/12/99 	else rect.top+=SCALESTARTPIX;
//	m_pView->m_pDialogBar = this;
	int counter;
	char string[10];
	#define zoom m_pView->m_zoom
	// a nice black background
//DEADCODE JIM 28/01/00 	pDC->FillRect(rect, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	float grad_10 = zoom * (Save_Data.dist.longcm/MAPSCALE) * 10 /65536;
	float grad_1 = grad_10/10;
	float grad_tenth = grad_10/ 100;
	RPoint*	CP;
	switch (m_align)
	{
	default_neverreferenced;
	case	1:	CP=&R_PointBot;		CP->maxalong=rect.right-5;	break;
	case	3:	CP=&R_PointTop;		CP->maxalong=rect.right-5;	break;
	case	2:	CP=&R_PointLeft;	CP->maxalong=rect.bottom-5;	break;
	case	4:	CP=&R_PointRight;	CP->maxalong=rect.bottom-5;	break;
	}
	RPoint&	CPoint=*CP;
	pDC->SetTextAlign(TA_RIGHT | TA_BASELINE | TA_NOUPDATECP);
//DEADCODE JIM 06/12/99 	switch (m_align)
//DEADCODE JIM 06/12/99 	{
//DEADCODE JIM 06/12/99 	case	1:
		PointTextOut(pDC,CPoint(TEXTSTARTPIX+10,RP_UNIT),LoadResString(Save_Data.dist.longabbr));	
//DEADCODE JIM 06/12/99 		break;
//DEADCODE JIM 06/12/99 	case	3:	PointTextOut(pDC,CPoint(TEXTSTARTPIX+10,RP_UNIT),LoadResString(Save_Data.dist.longabbr));	break;
//DEADCODE JIM 06/12/99 	case	2:	PointTextOut(pDC,CPoint(TEXTSTARTPIX+10,RP_UNIT),LoadResString(Save_Data.dist.longabbr));	break;
//DEADCODE JIM 06/12/99 	case	4:	PointTextOut(pDC,CPoint(TEXTSTARTPIX+10,RP_UNIT),LoadResString(Save_Data.dist.longabbr));	break;
//DEADCODE JIM 06/12/99 	}
	pDC->MoveTo(CPoint(DRAWSTARTPIX,RP_SCALEEDGE));
	pDC->LineTo(CPoint(CPoint.maxalong,RP_SCALEEDGE)); // line at top of scale
	// first draw in 10 mile seperators these are always present
	counter=0;
	for (float x=DRAWSTARTPIX;x<CPoint.maxalong;x+=grad_10)
	{
		pDC->MoveTo(CPoint(x,RP_SCALEEDGE));
		pDC->LineTo(CPoint(x,RP_BIGSCALE));
		// and the corresponding number
		if (counter%5==0)
		{
			if (	counter%20==0					//200
				|| (counter%10==0 && zoom>0.3)		//100
				|| zoom>=1.1)						//50
			{
//DEADCODE DAW 07/05/99 					if (counter==0)
//DEADCODE DAW 07/05/99 						sprintf(string,"0 %s",);
//DEADCODE DAW 07/05/99 					else
				PointTextOut(pDC,CPoint(x+TEXTSTARTDELTA,RP_NUMBER),CSprintf("%d",counter*10));	//HUNDREDS
			}
		}
		counter++;
	}
	

	// now 1 mile seperators
	if (m_pView->m_zoom>=3)	//4)
	{
		counter=0;
		for (float x=DRAWSTARTPIX;x<CPoint.maxalong;x+=grad_1)
		{
			if (counter%10>0)
			{
				pDC->MoveTo(CPoint(x,RP_SCALEEDGE));
				pDC->LineTo(CPoint(x,RP_MEDSCALE));
			}
			if (	counter%10==0				//10
				|| (counter%5==0 && zoom>=6))	//5
			{
				if (counter%50>0)
				{
					PointTextOut(pDC,CPoint(x+TEXTSTARTDELTA,RP_NUMBER),CSprintf("%d",counter));
				}
			}
			counter++;
		}
	}
	// now 1/10 mile seperators
	if (m_pView->m_zoom>=25)	//32)
	{
		counter=0;
		for (float x=DRAWSTARTPIX;x<CPoint.maxalong;x+=grad_tenth)
		{
			if (counter%10>0)
			{
				pDC->MoveTo(CPoint(x,RP_SCALEEDGE));
				pDC->LineTo(CPoint(x,RP_SMALLSCALE));
			}
			else if (counter%50>0)				//1
			{
				PointTextOut(pDC,CPoint(x+TEXTSTARTDELTA,RP_NUMBER),CSprintf("%d",counter/10));
			}
			counter++;
		}
	}
	if (m_RButtonDown)
	{
		CPen green (PS_SOLID,4,RGB(100,255,100));
		CPen red	(PS_SOLID,4,RGB(255,100,100));
		pDC->SelectObject(green);
		int x;
		//find end of proportional scale
		//code to find zoom is:
		//	m_pView->m_zoom=((point.x-DRAWSTARTPIX)*m_oldzoom)/(m_oldPoint.x-DRAWSTARTPIX);
		// (m_zoom<ZOOMTHRESHOLD3)
		// so
		//	ZOOMTHRESHOLD3*(m_oldPoint.x-DRAWSTARTPIX)/m_oldzoom+DRAWSTARTPIX=X
		int	oldpointx=m_oldPoint.x;
		if (!(m_align&1))
			oldpointx=m_oldPoint.y;
		x=ZOOMTHRESHOLD3*(oldpointx-DRAWSTARTPIX)/m_oldzoom+DRAWSTARTPIX;
		if (x<CPoint.maxalong)
		{
			pDC->MoveTo(CPoint(CPoint.maxalong,RP_SCALEEDGE));
			pDC->LineTo(CPoint(x,RP_SCALEEDGE));
		}

		pDC->SelectObject(red);
		for (float scale=0.5;;scale*=2)
		{
			x=scale*(oldpointx-DRAWSTARTPIX)/m_oldzoom+DRAWSTARTPIX;
			breakif(x>CPoint.maxalong|| scale>ZOOMTHRESHOLD3);
			pDC->MoveTo(CPoint(x,RP_SCALEEDGE));
			pDC->LineTo(CPoint(x,RP_SMALLSCALE));
		}
	}
	if (originalpen)
		pDC->SelectObject(originalpen);
	this->EndPaint(&paintstruct);
}

void CScaleBar::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CRToolBar::OnRButtonDown(nFlags, point);
}

void CScaleBar::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CRToolBar::OnRButtonUp(nFlags, point);
}

void CScaleBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_RButtonDown)
	{
		double oldzoom=m_pView->m_zoom;
		if (m_bHorzAlign)
			m_pView->m_zoom=((point.x-DRAWSTARTPIX)*m_oldzoom)/(m_oldPoint.x-DRAWSTARTPIX);
		else
			m_pView->m_zoom=((point.y-DRAWSTARTPIX)*m_oldzoom)/(m_oldPoint.y-DRAWSTARTPIX);
//TEMPCODE JIM 06/12/99 		if (m_pView->m_zoom<ZOOMTHRESHOLD3)
//TEMPCODE JIM 06/12/99 		{
//TEMPCODE JIM 06/12/99 			double newzoom=0.25;
//TEMPCODE JIM 06/12/99 			double oldzoom=m_pView->m_zoom;
//TEMPCODE JIM 06/12/99 			while (oldzoom>0.4)
//TEMPCODE JIM 06/12/99 			{
//TEMPCODE JIM 06/12/99 				newzoom*=2;
//TEMPCODE JIM 06/12/99 				oldzoom/=2;
//TEMPCODE JIM 06/12/99 			}
//TEMPCODE JIM 06/12/99 			m_pView->m_zoom=newzoom;
//TEMPCODE JIM 06/12/99 		}
		if (m_pView->m_zoom<ZOOMMIN) 
			m_pView->m_zoom=ZOOMMIN;
		else 
			if (m_pView->m_zoom>ZOOMMAX) 
				m_pView->m_zoom=ZOOMMAX;
//		TRACE1("Redrawing! %f!",m_pView->m_zoom);
	CRect rect;														  //JIM 08/05/99
	m_pView->GetClientRect(rect);
	if (m_pView->m_zoom!=oldzoom)
		m_pView->Zoom(CPoint(rect.right/2,rect.bottom/2),false);
	if (m_pView->m_zoom!=oldzoom)
		Invalidate();

	}
	CRToolBar::OnMouseMove(nFlags, point);
}

void CScaleBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ((m_bHorzAlign && point.x<SCALESTARTPIX) ||
		(!m_bHorzAlign && point.y<SCALESTARTPIX))
	{
		CRToolBar::OnLButtonDown(nFlags, point);
	}
	else
	{
		m_RButtonDown=TRUE;
		this->SetCapture();
		m_oldPoint=point;
		m_oldzoom=m_pView->m_zoom;
		Invalidate();
	}
}

void CScaleBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_RButtonDown=FALSE;
	ReleaseCapture(); 	
	CRect rect;
	m_pView->GetClientRect(rect);
	m_pView->Zoom(CPoint(rect.right/2,rect.bottom/2));
	Invalidate();
	CRToolBar::OnLButtonUp(nFlags, point);
}
