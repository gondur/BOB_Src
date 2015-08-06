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

//NOT A RowanDialog: // HintBox.cpp : implementation file
//

#include "stdafx.h"
#include "rbutton.h"
#include "HintBox.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef	THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
//DeadCode JIM 11Oct00 #pragma message ("HintBox")
/////////////////////////////////////////////////////////////////////////////
// CHintBox dialog



CHintBox::CHintBox(CWnd* pParent /*=NULL*/)
	: CDialog(CHintBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHintBox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	parentshandle=NULL;
}


void CHintBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHintBox)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHintBox, CDialog)
	//{{AFX_MSG_MAP(CHintBox)
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHintBox message handlers

BOOL CHintBox::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	GetClientRect(rect);
//	pDC->FillSolidRect(CRect(1,1,rect.right-1,rect.bottom-1),RGB(255,255,0));
	pDC->SetBkColor(RGB(255,255,0));
	CString text;
	GetWindowText(text);
	pDC->TextOut(1,1,text);
	CPen* oldpen=(CPen*)pDC->SelectStockObject(BLACK_PEN);
	pDC->MoveTo(0,0);
	pDC->LineTo(rect.right-1,0);
	pDC->LineTo(rect.right-1,rect.bottom-1);
	pDC->LineTo(0,rect.bottom-1);
	pDC->LineTo(0,0);
	if (oldpen)
		pDC->SelectObject(oldpen);
	return TRUE;//CDialog::OnEraseBkgnd(pDC);
}

LRESULT CHintBox::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
#ifndef NDEBUG
	// TODO: Add your specialized code here and/or call the base class
//DeadCode JIM 11Oct00 	if (message>=WM_KEYFIRST && message<=WM_KEYLAST && parentshandle)
//DeadCode JIM 11Oct00 		return ::PostMessage(parentshandle,message,wParam,lParam);
//DeadCode JIM 11Oct00 	else
		return CDialog::WindowProc(message, wParam, lParam);
#else
	return 0;
#endif
}

//DeadCode JIM 11Oct00 BOOL CHintBox::OnHelpInfo(HELPINFO* pHelpInfo) 
//DeadCode JIM 11Oct00 {
//DeadCode JIM 11Oct00 	// TODO: Add your message handler code here and/or call default
//DeadCode JIM 11Oct00 	
//DeadCode JIM 11Oct00 	return CDialog::OnHelpInfo(pHelpInfo);
//DeadCode JIM 11Oct00 }

void CHintBox::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	if (!bShow)
		parentshandle=NULL;
	// TODO: Add your message handler code here
	
}
