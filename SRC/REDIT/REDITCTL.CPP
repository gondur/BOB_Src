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

// REditCtl.cpp : Implementation of the CREditCtrl ActiveX Control class.

#include "stdafx.h"
#include "REdit.h"
#include <afxtempl.h>

#include "REditCtl.h"
#include "REditPpg.h"
#include "messages.h"
#include "fileman.h"
#include "axcolors.h"
#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//DeadCode JON 26Jun00 BOOL CREditCtrl::m_bDrawing = FALSE;
bool	flashon;
enum	{CURSOR_THICK_BORDER=1};
IMPLEMENT_DYNCREATE(CREditCtrl, COleControl)

extern int GetShadow1XOffset(int fontheight);
extern int GetShadow1YOffset(int fontheight);
extern int GetShadow2XOffset(int fontheight);
extern int GetShadow2YOffset(int fontheight);
enum {TIMERNUM = 3474	};
/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CREditCtrl, COleControl)
	//{{AFX_MSG_MAP(CREditCtrl)
	ON_WM_TIMER()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_GETDLGCODE()
	ON_WM_SETCURSOR()
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CREditCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CREditCtrl)
	DISP_PROPERTY_EX(CREditCtrl, "FontNum", GetFontNum, SetFontNum, VT_I4)
	DISP_PROPERTY_EX(CREditCtrl, "Shadow", GetShadow, SetShadow, VT_I4)
	DISP_PROPERTY_EX(CREditCtrl, "Caption", GetCaption, SetCaption, VT_BSTR)
	DISP_STOCKPROP_FORECOLOR()
	DISP_STOCKPROP_ENABLED()
	DISP_STOCKPROP_BACKCOLOR()
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CREditCtrl, COleControl)
	//{{AFX_EVENT_MAP(CREditCtrl)
	EVENT_CUSTOM("ReturnPressed", FireReturnPressed, VTS_BSTR)
	EVENT_CUSTOM("TextChanged", FireTextChanged, VTS_BSTR)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CREditCtrl, 2)
	PROPPAGEID(CREditPropPage::guid)
    PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CREditCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CREditCtrl, "REDIT.REditCtrl.1",
	0x499e2be6, 0xac32, 0x11d6, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CREditCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DREdit =
		{ 0x499e2be4, 0xac32, 0x11d6, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DREditEvents =
		{ 0x499e2be5, 0xac32, 0x11d6, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwREditOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CREditCtrl, IDS_REDIT, _dwREditOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::CREditCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CREditCtrl

BOOL CREditCtrl::CREditCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_REDIT,
			IDB_REDIT,
			afxRegApartmentThreading,
			_dwREditOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("REdit.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1998 Rowan Software";


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::CREditCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CREditCtrl::CREditCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::CREditCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CREditCtrl::CREditCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::CREditCtrl - Constructor

CREditCtrl::CREditCtrl()
{
	InitializeIIDs(&IID_DREdit, &IID_DREditEvents);
	m_timerID=0;
	m_bShowCursor=FALSE;
	m_curPoint=0;
	m_scrollPoint=0;
	m_curPos=INT_MAX;
	m_FirstSweep = TRUE;
	yshift=0;
	linedepth=0;
	currentword=NULL;
	currentwordpos=NULL;
	currentchar=0;
	tabstep=100;
	allowed=-1;	 
	maxcharcount=10000;
	maxlinecount=100;
	currlinecount=0;
	currentwordcharcount=0;
//	partwork=NULL;
//	artworkinfo.bmWidth=0;
}


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::~CREditCtrl - Destructor

CREditCtrl::~CREditCtrl()
{
//	KillTimer(m_timerID); // Just in case (actually it causes an assert)
}


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::OnDraw - Drawing function

void CREditCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
//DeadCode JON 26Jun00 	m_bDisabled = !GetEnabled();
	CRect rc = rcBounds;
	CWnd* parent;
    CFont* pOldFont;
	if (m_hWnd) parent=GetParent();
	if (m_hWnd) 
		pOldFont = pdc->SelectObject((CFont*)parent->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
	else 
		pOldFont = pdc->GetCurrentFont();

	if (m_hWnd && m_FirstSweep != TRUE)
	{
		FileNum	artnum = (FileNum)parent->SendMessage(WM_GETARTWORK,NULL,NULL);
		BYTE* pData;
		if (artnum)
		{
			int	offsets=parent->SendMessage(WM_GETXYOFFSET,NULL,NULL);
			CRect rect;
			this->GetWindowRect(rect);
			CRect parentrect;
			parent->GetWindowRect(parentrect);
			int	offsetx=short(offsets & 0x0000FFFF)+parentrect.left-rect.left;
			int	offsety=short((offsets & 0xFFFF0000)>>16)+parentrect.top-rect.top;
			pData = (BYTE*)parent->SendMessage(WM_GETFILE,artnum,NULL);
			if (pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
			{
				// now render it...
				BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
				BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
				pData+=pFile->bfOffBits;
				VERIFY(SetDIBitsToDevice(pdc->m_hDC,offsetx,offsety,pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
					0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS));

			}
			parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
		}
	}
	m_FirstSweep = FALSE;

    pdc->SetBkMode(TRANSPARENT);
    pdc->SetTextAlign(TA_LEFT | TA_TOP);

	if (m_FontNum<0)
	{
		pdc->SetTextColor(RGB(0,0,0));
		POSITION p=wordlist.GetHeadPosition();
		while (p)
		{
			OneWord& w=wordlist.GetNext(p);
			pdc->TextOut(w.startat.x+1,w.startat.y+1, w.text, strlen(w.text));
			if (w.flags==w.W_SOFTLINE)	//soft newline and no real separator
				pdc->TextOut(w.startat.x+w.pixlen,w.startat.y, "-",1);
		}
	}
	pdc->SetTextColor(TranslateColor(GetForeColor()));
	POSITION p=wordlist.GetHeadPosition();
	if (p)
	{
//TempCode JON 26Jun00 		UByteP(0xb0000)[2+(int)this&0x3fe]++;

		while (p)
		{
			OneWord& w=wordlist.GetNext(p);
			pdc->TextOut(w.startat.x,w.startat.y, w.text, strlen(w.text));
			if (w.flags==w.W_SOFTLINE)	//soft newline and no real separator
				pdc->TextOut(w.startat.x+w.pixlen,w.startat.y, "-",1);
		}
		if (currentword)
		{
			int	localpixx=CharNumToPix(*currentword,currentchar);
			if (flashon)
			{
				CPen pen(PS_SOLID,2,TranslateColor(GetForeColor()));
				CPen* oldpen=pdc->SelectObject(&pen);
				pdc->MoveTo(currentword->startat.x+localpixx,currentword->startat.y);
				pdc->LineTo(currentword->startat.x+localpixx,currentword->startat.y+linedepth);
				pdc->SelectObject(oldpen);
			}
			flashon=(flashon==false);
			SetTimer(TIMERNUM,100,NULL);
		}
	}
	else
	{
//TempCode JON 26Jun00 		UByteP(0xb0000)[2+(int)this&0x3fe]++;
		if (m_hWnd && GetEnabled())
			if (currentwordpos)
			{
				if (flashon)
				{
					CPen pen(PS_SOLID,2,TranslateColor(GetForeColor()));
					CPen* oldpen=pdc->SelectObject(&pen);
					pdc->MoveTo(0,0);
					pdc->LineTo(0,linedepth);
					pdc->SelectObject(oldpen);
				}
				flashon=(flashon==false);
				SetTimer(TIMERNUM,100,NULL);

			}
			else
			{
					CPen pen(PS_SOLID,2,TranslateColor(GetForeColor()));
					CPen* oldpen=pdc->SelectObject(&pen);
					pdc->MoveTo(0,0);
					pdc->LineTo(0,linedepth);
					pdc->SelectObject(oldpen);
			}
	}
//DEADCODE JIM 19/01/00 	if (m_curPos==INT_MAX)
//DEADCODE JIM 19/01/00 	{
//DEADCODE JIM 19/01/00 		m_curPos=InternalGetText().GetLength();
//DEADCODE JIM 19/01/00 		m_curPoint=pdc->GetTextExtent(InternalGetText()).cx;
//DEADCODE JIM 19/01/00 //		if (m_hWnd)
//DEADCODE JIM 19/01/00 //		{
//DEADCODE JIM 19/01/00 //			partwork = (CBitmap*)this->GetParent()->SendMessage(WM_GETARTWORK,NULL,NULL);
//DEADCODE JIM 19/01/00 //			if(partwork)
//DEADCODE JIM 19/01/00 //			{
//DEADCODE JIM 19/01/00 //				partwork->GetBitmap(&artworkinfo);
//DEADCODE JIM 19/01/00 //			}
//DEADCODE JIM 19/01/00 //		}
//DEADCODE JIM 19/01/00 	}
//DEADCODE JIM 19/01/00 	if (m_curPoint-(rc.Width()/2)<m_scrollPoint) m_scrollPoint=max(m_curPoint-(rc.Width()/2),0);
//DEADCODE JIM 19/01/00 	if (m_curPoint-rc.Width()+4>m_scrollPoint) m_scrollPoint=m_curPoint-rc.Width()+4;
//DEADCODE JIM 19/01/00 	long offsetx;
//DEADCODE JIM 19/01/00 	long offsety;
//DEADCODE JIM 19/01/00 	if (m_hWnd)
//DEADCODE JIM 19/01/00 	{
//DEADCODE JIM 19/01/00 		long offsets;
//DEADCODE JIM 19/01/00 		offsets=parent->SendMessage(WM_GETXYOFFSET,NULL,NULL);
//DEADCODE JIM 19/01/00 		CRect rect;
//DEADCODE JIM 19/01/00 		this->GetWindowRect(rect);
//DEADCODE JIM 19/01/00 		CRect parentrect;
//DEADCODE JIM 19/01/00 		parent->GetWindowRect(parentrect);
//DEADCODE JIM 19/01/00 		offsetx=short(offsets & 0x0000FFFF)+parentrect.left-rect.left;
//DEADCODE JIM 19/01/00 		offsety=short((offsets & 0xFFFF0000)>>16)+parentrect.top-rect.top;
//DEADCODE JIM 19/01/00 	}
//DEADCODE JIM 19/01/00 	else
//DEADCODE JIM 19/01/00 	{
//DEADCODE JIM 19/01/00 		offsetx=0;
//DEADCODE JIM 19/01/00 		offsety=0;
//DEADCODE JIM 19/01/00 	}
//DEADCODE JIM 19/01/00     pdc->SetBkMode(TRANSPARENT);
//DEADCODE JIM 19/01/00     pdc->SetTextAlign(TA_LEFT | TA_TOP);
//DEADCODE JIM 19/01/00 
//DEADCODE JIM 19/01/00 //	m_pic.Render(pdc,CRect(offsetx,offsety,hmWidth+offsetx,hmHeight+offsety),rcBounds);
//DEADCODE JIM 19/01/00 //	if ( artworkinfo.bmWidth)
//DEADCODE JIM 19/01/00 //	{
//DEADCODE JIM 19/01/00 //		CDC memDC;
//DEADCODE JIM 19/01/00 //		memDC.CreateCompatibleDC(pdc);
//DEADCODE JIM 19/01/00 //		CBitmap* pOldBitmap;
//DEADCODE JIM 19/01/00 //		pOldBitmap = memDC.SelectObject(partwork);
//DEADCODE JIM 19/01/00 //		pdc->BitBlt(offsetx,offsety,artworkinfo.bmWidth,artworkinfo.bmHeight,&memDC,0,0,SRCCOPY);
//DEADCODE JIM 19/01/00 //		memDC.SelectObject(pOldBitmap);
//DEADCODE JIM 19/01/00 //		memDC.DeleteDC();
//DEADCODE JIM 19/01/00 //	}
//DEADCODE JIM 19/01/00 //	else
//DEADCODE JIM 19/01/00 //	{
//DEADCODE JIM 19/01/00 //		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
//DEADCODE JIM 19/01/00 //	}
//DEADCODE JIM 19/01/00 	FileNum artnum=FIL_NULL;
//DEADCODE JIM 19/01/00 	BOOL X2flag=FALSE;
//DEADCODE JIM 19/01/00 	if (m_hWnd && m_FirstSweep != TRUE)
//DEADCODE JIM 19/01/00 	{
//DEADCODE JIM 19/01/00 		artnum = (FileNum)parent->SendMessage(WM_GETARTWORK,NULL,NULL);
//DEADCODE JIM 19/01/00 		BYTE* pData;
//DEADCODE JIM 19/01/00 		if (artnum)
//DEADCODE JIM 19/01/00 		{
//DEADCODE JIM 19/01/00 			pData = (BYTE*)parent->SendMessage(WM_GETFILE,artnum,NULL);
//DEADCODE JIM 19/01/00 			if (pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
//DEADCODE JIM 19/01/00 			{
//DEADCODE JIM 19/01/00 				// now render it...
//DEADCODE JIM 19/01/00 				BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
//DEADCODE JIM 19/01/00 				BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
//DEADCODE JIM 19/01/00 				pData+=pFile->bfOffBits;
//DEADCODE JIM 19/01/00 				VERIFY(SetDIBitsToDevice(pdc->m_hDC,offsetx,offsety,pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
//DEADCODE JIM 19/01/00 					0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS));
//DEADCODE JIM 19/01/00 			}
//DEADCODE JIM 19/01/00 			parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
//DEADCODE JIM 19/01/00 		}
//DEADCODE JIM 19/01/00 		X2flag=parent->SendMessage(WM_GETX2FLAG,NULL,NULL);
//DEADCODE JIM 19/01/00 	}
//DEADCODE JIM 19/01/00 	if (!artnum && m_FirstSweep != TRUE || !m_hWnd)
//DEADCODE JIM 19/01/00 	{
//DEADCODE JIM 19/01/00 		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
//DEADCODE JIM 19/01/00 	}
//DEADCODE JIM 19/01/00 	m_FirstSweep = FALSE;
//DEADCODE JIM 19/01/00 	if (m_FontNum<0)
//DEADCODE JIM 19/01/00 	{
//DEADCODE JIM 19/01/00 		TEXTMETRIC tm;
//DEADCODE JIM 19/01/00 		pdc->GetTextMetrics(&tm);
//DEADCODE JIM 19/01/00 		pdc->SetTextColor(RGB(0,0,0));
//DEADCODE JIM 19/01/00 		int shadowx=GetShadow1XOffset(tm.tmHeight);
//DEADCODE JIM 19/01/00 		int shadowy=GetShadow1YOffset(tm.tmHeight);
//DEADCODE JIM 19/01/00 	    pdc->ExtTextOut(2-m_scrollPoint+shadowx, 2+shadowy,
//DEADCODE JIM 19/01/00 			ETO_CLIPPED, rc, InternalGetText(), InternalGetText().GetLength(), NULL);
//DEADCODE JIM 19/01/00 		shadowx=GetShadow2XOffset(tm.tmHeight);
//DEADCODE JIM 19/01/00 		shadowy=GetShadow2YOffset(tm.tmHeight);
//DEADCODE JIM 19/01/00 	    pdc->ExtTextOut(2-m_scrollPoint+shadowx, 2+shadowy,
//DEADCODE JIM 19/01/00 			ETO_CLIPPED, rc, InternalGetText(), InternalGetText().GetLength(), NULL);
//DEADCODE JIM 19/01/00 	}
//DEADCODE JIM 19/01/00 	if(m_bDisabled == FALSE)
//DEADCODE JIM 19/01/00 	{
//DEADCODE JIM 19/01/00 		pdc->SetTextColor(TranslateColor(GetForeColor()));
//DEADCODE JIM 19/01/00 	}
//DEADCODE JIM 19/01/00 	else
//DEADCODE JIM 19/01/00 	{
//DEADCODE JIM 19/01/00 		pdc->SetTextColor(RGB(128,128,128));
//DEADCODE JIM 19/01/00 	}
//DEADCODE JIM 19/01/00     pdc->ExtTextOut(2-m_scrollPoint, 2,
//DEADCODE JIM 19/01/00 		ETO_CLIPPED, rc, InternalGetText(), InternalGetText().GetLength(), NULL);
//DEADCODE JIM 19/01/00 	if (m_bShowCursor && m_bDisabled == FALSE)
//DEADCODE JIM 19/01/00 	{
//DEADCODE JIM 19/01/00 		SetFocus();
//DEADCODE JIM 19/01/00 		CPen pen(PS_SOLID,2,TranslateColor(GetForeColor()));
//DEADCODE JIM 19/01/00 		pdc->SelectObject(pen);
//DEADCODE JIM 19/01/00 		pdc->MoveTo(m_curPoint-m_scrollPoint+2,3);
//DEADCODE JIM 19/01/00 		pdc->LineTo(m_curPoint-m_scrollPoint+2,pdc->GetTextExtent("jA").cy+2);
//DEADCODE JIM 19/01/00 	}
//DEADCODE JIM 19/01/00 	CPen BlackPen,WhitePen,pen;
//DEADCODE JIM 19/01/00 	if (!m_hWnd || IsWindowEnabled())
//DEADCODE JIM 19/01/00 	{
//DEADCODE JIM 19/01/00 		BlackPen.CreatePen(PS_SOLID,1,AXC_DARKEDGE);
//DEADCODE JIM 19/01/00 		WhitePen.CreatePen(PS_SOLID,1,AXC_LITEDGE);
//DEADCODE JIM 19/01/00 	}
//DEADCODE JIM 19/01/00 	else
//DEADCODE JIM 19/01/00 	{
//DEADCODE JIM 19/01/00 		BlackPen.CreatePen(PS_SOLID,1,AXC_DISABLEDDARKEDGE);
//DEADCODE JIM 19/01/00 		WhitePen.CreatePen(PS_SOLID,1,AXC_DISABLEDLITEDGE);
//DEADCODE JIM 19/01/00 	}

//TEMPCODE JIM 19/01/00 	if(m_bDisabled == TRUE)
//TEMPCODE JIM 19/01/00 	{
//TEMPCODE JIM 19/01/00 		pen.CreatePen(PS_SOLID,2,RGB(128,128,128));
//TEMPCODE JIM 19/01/00 		CPen* oldpen;
//TEMPCODE JIM 19/01/00 		oldpen=pdc->SelectObject(&pen);
//TEMPCODE JIM 19/01/00 		pdc->MoveTo(rcBounds.right-1,rcBounds.top+1);
//TEMPCODE JIM 19/01/00 		pdc->LineTo(rcBounds.right-1,rcBounds.bottom-1);
//TEMPCODE JIM 19/01/00 		pdc->LineTo(rcBounds.left,rcBounds.bottom-1);
//TEMPCODE JIM 19/01/00 		pdc->LineTo(rcBounds.left,rcBounds.top);
//TEMPCODE JIM 19/01/00 		pdc->LineTo(rcBounds.right,rcBounds.top);
//TEMPCODE JIM 19/01/00 		pdc->SelectObject(oldpen);
//TEMPCODE JIM 19/01/00 		
//TEMPCODE JIM 19/01/00 	}
//TEMPCODE JIM 19/01/00 	else
//TEMPCODE JIM 19/01/00 	{
//TEMPCODE JIM 19/01/00 		CPen* oldpen;
//TEMPCODE JIM 19/01/00 		oldpen=pdc->SelectObject(&WhitePen);
//TEMPCODE JIM 19/01/00 		pdc->MoveTo(rcBounds.right-1,rcBounds.top+1);
//TEMPCODE JIM 19/01/00 		pdc->LineTo(rcBounds.right-1,rcBounds.bottom-1);
//TEMPCODE JIM 19/01/00 		pdc->LineTo(rcBounds.left,rcBounds.bottom-1);
//TEMPCODE JIM 19/01/00 		pdc->SelectObject(&BlackPen);	
//TEMPCODE JIM 19/01/00 		pdc->LineTo(rcBounds.left,rcBounds.top);
//TEMPCODE JIM 19/01/00 		pdc->LineTo(rcBounds.right,rcBounds.top);
//TEMPCODE JIM 19/01/00 		pdc->SelectObject(oldpen);
//TEMPCODE JIM 19/01/00 		
//TEMPCODE JIM 19/01/00 	}	
		pdc->SelectObject(pOldFont);

}


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::DoPropExchange - Persistence support

void CREditCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Long(pPX, _T("FontNum"), m_FontNum, 0);
}


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::OnResetState - Reset control to default state

void CREditCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	SetForeColor(RGB(255,255,255));
}


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl message handlers

void CREditCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
//DeadCode JON 26Jun00 	m_bDisabled = ;
	if (!GetEnabled()) return;
	SetToWordUnderCursor(point);

//DEADCODE JIM 20/01/00 	CDC* pdc;
//DEADCODE JIM 20/01/00 	pdc=GetDC();
//DEADCODE JIM 20/01/00     CFont* pOldFont;
//DEADCODE JIM 20/01/00 	if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
//DEADCODE JIM 20/01/00 	else pOldFont = pdc->GetCurrentFont();
//DEADCODE JIM 20/01/00 	// figure out where the user clicked the cursor
//DEADCODE JIM 20/01/00 	m_curPoint=pdc->GetTextExtent(InternalGetText()).cx;
//DEADCODE JIM 20/01/00 	m_curPos=InternalGetText().GetLength();
//DEADCODE JIM 20/01/00 	for (int i=1;i<=m_curPos;i++)
//DEADCODE JIM 20/01/00 	{
//DEADCODE JIM 20/01/00 		if (point.x-2+m_scrollPoint<pdc->GetTextExtent(InternalGetText().Left(i)).cx)
//DEADCODE JIM 20/01/00 		{
//DEADCODE JIM 20/01/00 			m_curPoint=pdc->GetTextExtent(InternalGetText().Left(i-1)).cx;
//DEADCODE JIM 20/01/00 			m_curPos=i-1;
//DEADCODE JIM 20/01/00 			break;
//DEADCODE JIM 20/01/00 		}
//DEADCODE JIM 20/01/00 	}
//DEADCODE JIM 20/01/00 //	pdc->SelectObject(pOldFont);
//DEADCODE JIM 20/01/00 	this->ReleaseDC(pdc);
//DEADCODE JIM 20/01/00 	SetFocus();
//DEADCODE JIM 20/01/00 	if (m_timerID)
//DEADCODE JIM 20/01/00 	{
//DEADCODE JIM 20/01/00 		m_bShowCursor=TRUE;
//DEADCODE JIM 20/01/00 		InvalidateControl();
//DEADCODE JIM 20/01/00 	}
//DEADCODE JIM 20/01/00     pdc->SelectObject(pOldFont);
//DEADCODE JIM 20/01/00 	ReleaseDC(pdc);
 	COleControl::OnLButtonDown(nFlags, point);
}

void CREditCtrl::OnTimer(UINT nIDEvent) 
{
	if (currentword)
	{
		int	localpixx=CharNumToPix(*currentword,currentchar);
		InvalidateRect(CRect(currentword->startat.x+localpixx-1,currentword->startat.y-1,currentword->startat.x+localpixx+1,currentword->startat.y+linedepth+1),false);
	}
	else
	{
		InvalidateRect(CRect(0-1,0-1,0+1,0+linedepth+1),false);
	}

//DeadCode JON 26Jun00 	if (nIDEvent==m_timerID)
//DeadCode JON 26Jun00 	{
//DeadCode JON 26Jun00 		m_bShowCursor=!m_bShowCursor;
//DeadCode JON 26Jun00 //TEMPCODE JIM 20/01/00 		InvalidateControl();
//DeadCode JON 26Jun00 	}
	COleControl::OnTimer(nIDEvent);
	KillTimer(TIMERNUM);
}

void CREditCtrl::OnKillFocus(CWnd* pNewWnd) 
{
//TempCode JON 26Jun00 //TempCode JON 26Jun00 	UByteP(0xb0000)[(int)this&0x3fe]++;
//TempCode JON 26Jun00 	UByteP(0xb0000)[2+(int)this&0x3fe]='i';
//TempCode JON 26Jun00 	if (currentword)
//TempCode JON 26Jun00 		currentword->flags|=currentword->W_REDRAW;
	OnTimer(TIMERNUM);
	currentword=NULL;
	currentwordpos=NULL;
//TempCode JON 26Jun00 	InvalidateChangedWords();
//TempCode JON 26Jun00 	InvalidateControl();
//TempCode JON 26Jun00 	COleControl::OnKillFocus(pNewWnd);

//TEMPCODE JIM 20/01/00 	if (m_curPos!=INT_MAX)
//TEMPCODE JIM 20/01/00 	{
//TEMPCODE JIM 20/01/00 		KillTimer(m_timerID);
//TEMPCODE JIM 20/01/00 		m_timerID=0;
//TEMPCODE JIM 20/01/00 		m_bShowCursor=FALSE;
//TEMPCODE JIM 20/01/00 		InvalidateControl();
//TEMPCODE JIM 20/01/00 	}
}

void CREditCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	COleControl::OnSetFocus(pOldWnd);
	if (!GetEnabled()) return;
	SetToWordUnderCursor(CPoint(1000,1));
//TEMPCODE JIM 20/01/00 	if (!m_timerID)
//TEMPCODE JIM 20/01/00 	{
//TEMPCODE JIM 20/01/00 		m_timerID=SetTimer(3474,500,NULL);
//TEMPCODE JIM 20/01/00 	}
}

void CREditCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
//DeadCode JON 26Jun00 	m_bDisabled = !GetEnabled();
	if (!GetEnabled()) return;
	if (wordlist.IsEmpty())
	{
			OneWord newword("",OneWord::W_REDRAW);
		wordlist.AddHead(newword);
		currentwordpos=wordlist.GetHeadPosition();
		currentword=&wordlist.GetHead();
		currentchar=0;
	}
	if (!currentword)
	{
		currentwordpos=wordlist.GetHeadPosition();
		currentword=&wordlist.GetHead();
		currentchar=0;
	}
//DEADCODE MS 02/02/00 	TRACE1("virtual: %c\n",nChar);
//DEADCODE JIM 20/01/00 	CDC* pdc;
//DEADCODE JIM 20/01/00 	pdc=GetDC();
//DEADCODE JIM 20/01/00     CFont* pOldFont;
//DEADCODE JIM 20/01/00 	if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
//DEADCODE JIM 20/01/00 	else pOldFont = pdc->GetCurrentFont();
	switch (nChar)
	{
		case VK_BACK:
			if(currentchar)
			{
				strcpy(currentword->text+currentchar-1,currentword->text+currentchar);
				currentchar--;
				CalcWordLen(*currentword);
				RepositionWordList();
				InvalidateChangedWords();
			}
			else
			{	//deleting preceeding space!!!
				POSITION p2=currentwordpos;
				wordlist.GetPrev(p2);
				if (p2)
				{
					OneWord* pw=&wordlist.GetAt(p2);
					int	pwlen=strlen(pw->text);
					if (pw->flags&(OneWord::W_HARDLINE|OneWord::W_TAB))
					{
						pw->flags=OneWord::W_SPACE+OneWord::W_REDRAW;
					}
					else
					{
						if (!(pw->flags&OneWord::W_SPACE))	//no seperator so remove char
							pw->text[strlen(pw->text)-1]=0;
						if (pwlen+strlen(currentword->text)<=OneWord::MAX_CU)
						{	//need to merge words
							strcpy(pw->text+pwlen,currentword->text);
							pw->flags=currentword->flags;
							wordlist.RemoveAt(currentwordpos);
							currentwordpos=p2;
							currentword=pw;
							currentchar=pwlen;
							CalcWordLen(*currentword);
							RepositionWordList();
							InvalidateChangedWords();
						}
						else
						{	//need to remove space and set as new word
							currentwordpos=p2;
							currentword=pw;
							currentchar=pwlen;
							pw->flags&=~OneWord::W_SPACE;
							RepositionWordList();
							InvalidateChangedWords();
						}
					}
				}
				//else no previous word, so ignore
				
			}
			break;
		case VK_DELETE:
			if(currentchar<strlen(currentword->text))
			{
				strcpy(currentword->text+currentchar,currentword->text+currentchar+1);
				CalcWordLen(*currentword);
				RepositionWordList();
				InvalidateChangedWords();
			}
			else
			{
				POSITION p2=currentwordpos;
				wordlist.GetNext(p2);
				if (p2)
				{
					if (currentword->flags&(OneWord::W_HARDLINE|OneWord::W_TAB))
						currentword->flags=OneWord::W_SPACE|OneWord::W_REDRAW;
					else
					{
						OneWord* nw=&wordlist.GetAt(p2);
						if (!(currentword->flags&OneWord::W_SPACE))
							strcpy(nw->text,nw->text+1);
						int	nwlen=strlen(nw->text);
						if (nwlen+strlen(currentword->text)<=OneWord::MAX_CU)
						{	//need to merge words
							strcpy(currentword->text+currentchar,nw->text);
							currentword->flags=nw->flags;
							wordlist.RemoveAt(p2);
							CalcWordLen(*currentword);
							RepositionWordList();
							InvalidateChangedWords();
						}
						else
						{	//need to remove space and set as new word
							currentword->flags&=~(OneWord::W_HARDLINE|OneWord::W_SOFTLINE|OneWord::W_SPACE|OneWord::W_TAB);
							currentwordpos=p2;
							currentword=nw;
							currentchar=0;
							RepositionWordList();
							InvalidateChangedWords();
						}
					}
				}

			}
			break;
		case VK_LEFT:
			if(currentchar)
			{
				currentchar--;
				currentword->flags|=OneWord::W_REDRAW;
			}
			else
			{
				currentword->flags|=OneWord::W_REDRAW;
				POSITION p2=currentwordpos;
				wordlist.GetPrev(p2);
				if (p2)
				{
					currentwordpos=p2;
					currentword=&wordlist.GetAt(currentwordpos);
					currentchar=strlen(currentword->text);
				}
			}
			break;
		case VK_RIGHT:
			if(currentchar<strlen(currentword->text))
			{
				currentchar++;
				currentword->flags|=OneWord::W_REDRAW;
			}
			else
			{
				currentword->flags|=OneWord::W_REDRAW;
				POSITION p2=currentwordpos;
				wordlist.GetNext(p2);
				if (p2)
				{
					currentwordpos=p2;
					currentword=&wordlist.GetAt(currentwordpos);
					currentchar=0;
				}
			}
			break;
		case VK_HOME:
			{
				currentword->flags|=OneWord::W_REDRAW;
				if (currentword->startat.x==0 && currentchar==0)
				{
					OneWord* pw=NULL;
					POSITION p2=currentwordpos;
					wordlist.GetPrev(p2);
					if (p2)
					{
						pw=&wordlist.GetAt(p2);
						if (pw->flags&OneWord::W_HARDLINE)
							pw=NULL;
					}
					if (pw)
					{	//find start of paragraph
						while (p2 && !(pw->flags&OneWord::W_HARDLINE))	
						{
							currentwordpos=p2;
							wordlist.GetPrev(p2);
							pw=&wordlist.GetAt(p2);
						}
						currentword=&wordlist.GetAt(currentwordpos);
						currentchar=0;
					}
					else
					{	//start of text
						currentwordpos=wordlist.GetHeadPosition();
						currentword=&wordlist.GetAt(currentwordpos);
						currentchar=0;
					}
				}
				else
				{	//start of line
					while (currentword->startat.x!=0)
					{
						wordlist.GetPrev(currentwordpos);
						currentword=&wordlist.GetAt(currentwordpos);
					}
					currentchar=0;
				}
			}
			break;
		case VK_END:
			{
				currentword->flags|=OneWord::W_REDRAW;
				if (currentword->flags&(OneWord::W_HARDLINE|OneWord::W_SOFTLINE) && currentchar==strlen(currentword->text))
					if (currentword->flags&OneWord::W_HARDLINE) //& eoword ==> end of text
					{
						currentwordpos=wordlist.GetTailPosition();
						currentword=&wordlist.GetAt(currentwordpos);
						currentchar=strlen(currentword->text);
					}
					else	//softline & eoword	==> end of para
					{
						POSITION p2=currentwordpos;
						wordlist.GetNext(p2);
						while (p2)
						{
							currentwordpos=p2;
	 						currentword=&wordlist.GetAt(currentwordpos);
							breakif(currentword->flags&OneWord::W_HARDLINE);
							wordlist.GetNext(p2);
						}
						currentchar=strlen(currentword->text);
					}
				else
				{	//go to end of this softline or hardline
					POSITION p2=currentwordpos;
					while (p2)
					{
						currentwordpos=p2;
	 					currentword=&wordlist.GetAt(currentwordpos);
						breakif(currentword->flags&(OneWord::W_HARDLINE|OneWord::W_SOFTLINE));
						wordlist.GetNext(p2);
					}
					currentchar=strlen(currentword->text);
				}

			}
			break;
		case VK_UP:
			if (allowed['\v'])
			{
				currentword->flags|=OneWord::W_REDRAW;
				CPoint pos=currentword->startat;
				pos.x+=CharNumToPix(*currentword,currentchar);
				pos.y-=1;
				if (pos.y>0)
					SetToWordUnderCursor(pos);
			}
			break;
		case VK_DOWN:
			if (allowed['\v'])
			{
				currentword->flags|=OneWord::W_REDRAW;
				CPoint pos=currentword->startat;
				pos.x+=CharNumToPix(*currentword,currentchar);
				pos.y+=2*linedepth-1;
				SetToWordUnderCursor(pos);
			}
			break;
		case VK_PRIOR:
			if (allowed['\v'])
			{
				currentword->flags|=OneWord::W_REDRAW;
				POSITION p2=currentwordpos;
				wordlist.GetPrev(p2);
				if (p2 && currentchar==0)
				{
					currentwordpos=p2;
					wordlist.GetPrev(p2);
				}
				while (p2)
				{
					OneWord* wp=&wordlist.GetAt(p2);
					breakif(wp->flags&OneWord::W_HARDLINE);
					currentwordpos=p2;
					wordlist.GetPrev(p2);
				}
				currentword=&wordlist.GetAt(currentwordpos);
				currentchar=0;
			}
			break;
		case VK_NEXT:
			if (allowed['\v'])
			{
				currentword->flags|=OneWord::W_REDRAW;
				POSITION p2=currentwordpos;
				if (currentchar==strlen(currentword->text))
				{
					wordlist.GetNext(p2);
				}
				while (p2)
				{
					OneWord* wp=&wordlist.GetAt(p2);
					currentwordpos=p2;
					breakif(wp->flags&OneWord::W_HARDLINE);
					wordlist.GetNext(p2);
				}
				currentword=&wordlist.GetAt(currentwordpos);
				currentchar=strlen(currentword->text);
			}
			break;
		case VK_SPACE:
			if (allowed[' '])
			{
				currentword->flags|=OneWord::W_REDRAW;
				if (	!(currentword->flags&(OneWord::W_HARDLINE|OneWord::W_HARDLINE)) 
					&&	currentchar==strlen(currentword->text))
				{
					POSITION p2=currentwordpos;
					wordlist.GetNext(p2);
					if (!p2)
						p2=wordlist.InsertAfter(currentwordpos,OneWord("",OneWord::Flags(currentword->flags)));
					currentword->flags=OneWord::W_SPACE+OneWord::W_REDRAW;
					currentwordpos=p2;
					currentword=&wordlist.GetAt(p2);
					currentchar=0;

				}
				else
				{
					POSITION p2=wordlist.InsertAfter(currentwordpos,OneWord(currentword->text+currentchar,OneWord::Flags(currentword->flags)));
					currentword->flags=OneWord::W_SPACE+OneWord::W_REDRAW;
					currentword->text[currentchar]=0;
					CalcWordLen(*currentword);
					currentwordpos=p2;
					currentword=&wordlist.GetAt(p2);
					CalcWordLen(*currentword);
					currentchar=0;
				}
			}
			break;
		case VK_TAB:
			if (allowed['\t'])
			{	//If at end of word & end of word is a space, then change current end to a tab
				//Otherwise split and insert tab
				currentword->flags|=OneWord::W_REDRAW;
				if (	!(currentword->flags&(OneWord::W_HARDLINE)) 
					&&	currentchar==strlen(currentword->text))
				{
					POSITION p2=currentwordpos;
					wordlist.GetNext(p2);
					if (!p2)
						p2=wordlist.InsertAfter(currentwordpos,OneWord("",OneWord::Flags(currentword->flags)));
					currentword->flags=OneWord::W_TAB+OneWord::W_REDRAW;
					currentwordpos=p2;
					currentword=&wordlist.GetAt(p2);
					currentchar=0;

				}
				else
				{
					POSITION p2=wordlist.InsertAfter(currentwordpos,OneWord(currentword->text+currentchar,OneWord::Flags(currentword->flags)));
					currentword->flags=OneWord::W_TAB+OneWord::W_REDRAW;
					currentword->text[currentchar]=0;
					CalcWordLen(*currentword);

					currentwordpos=p2;
					currentword=&wordlist.GetAt(p2);
					currentchar=0;
					CalcWordLen(*currentword);
				}

			}
			break;
		case VK_RETURN:
			if (allowed['\n'])
			{	//If at end of word, then set current end to a hardline
				//Otherwise split and insert hardline
				if (currentchar==0)
				{
					POSITION p2=currentwordpos;
					wordlist.GetPrev(p2);
					if (p2)
					{
 						currentwordpos=p2;
						currentword=&wordlist.GetAt(p2);
						currentchar=strlen(currentword->text);

					}

				}
				currentword->flags|=OneWord::W_REDRAW;
				if (currentchar==strlen(currentword->text))
				{
					POSITION p2=currentwordpos;
					wordlist.GetNext(p2);
					if (!p2)
						p2=wordlist.InsertAfter(currentwordpos,OneWord("",OneWord::Flags(currentword->flags)));
					currentword->flags=OneWord::W_HARDLINE+OneWord::W_REDRAW;
					currentwordpos=p2;
					currentword=&wordlist.GetAt(p2);
					currentchar=0;
				}
				else
				{
					POSITION p2=wordlist.InsertAfter(currentwordpos,OneWord(currentword->text+currentchar,OneWord::Flags(currentword->flags)));
					currentword->flags=OneWord::W_HARDLINE+OneWord::W_REDRAW;
					currentword->text[currentchar]=0;
					CalcWordLen(*currentword);

					currentwordpos=p2;
					currentword=&wordlist.GetAt(p2);
					currentchar=0;
					CalcWordLen(*currentword);
				}


			}
			else
			{
				CString strResult;
				GetString(strResult);
				FireReturnPressed(strResult);
			}
			  ;
			TRACE0("User pressed Enter\n");
			break;
	}
//DEADCODE JIM 20/01/00 	m_curPoint=pdc->GetTextExtent(InternalGetText().Left(m_curPos)).cx;
//DEADCODE JIM 20/01/00 	SetWindowText(InternalGetText());
//DEADCODE JIM 20/01/00 //DeadCode DAW 09Mar99 	FireTextChanged(InternalGetText());
//DEADCODE JIM 20/01/00 	pdc->SelectObject(pOldFont);
//DEADCODE JIM 20/01/00 	ReleaseDC(pdc);
//	FireTextChanged(InternalGetText());
	RepositionWordList();
	InvalidateChangedWords();
	COleControl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CREditCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
//DeadCode JON 26Jun00 	m_bDisabled = !GetEnabled();
	if (!GetEnabled()) return;
	if (nChar>' ' && allowed[nChar])// && nChar!=':' && nChar!='/' && nChar!='\\' && nChar!='$')
	{
		if (strlen(currentword->text)<OneWord::MAX_CU)
		{
			for (int i=strlen(currentword->text);i>=currentchar;i--)
				currentword->text[i+1]=currentword->text[i];
			currentword->text[currentchar++]=nChar;
			CalcWordLen(*currentword);
		}
		else
		{
			OneWord newword(currentword->text+currentchar,OneWord::Flags(currentword->flags));

			POSITION p2=wordlist.InsertAfter(currentwordpos,newword);
			currentword->flags=OneWord::W_REDRAW;
			currentword->text[currentchar]=0;
			CalcWordLen(*currentword);
			if (currentchar==OneWord::MAX_CU)
			{	//this word full, move into next
				currentwordpos=p2;
				currentword=&wordlist.GetAt(p2);
				currentword->text[0]=nChar;
				currentword->text[1]=0;
				currentchar=1;
				CalcWordLen(*currentword);
			}
			else
			{	//this word not full, continue 
				CalcWordLen(wordlist.GetAt(p2));
				currentword->text[currentchar]=nChar;
				currentchar++;
				currentword->text[currentchar]=0;
				CalcWordLen(*currentword);
			}
		}
	}
	RepositionWordList();
	InvalidateChangedWords();
	COleControl::OnChar(nChar, nRepCnt, nFlags);
}

UINT CREditCtrl::OnGetDlgCode() 
{
	return DLGC_WANTARROWS|DLGC_WANTALLKEYS|DLGC_WANTCHARS|DLGC_WANTTAB;
}

BOOL CREditCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_IBEAM));
	return TRUE;
//	return COleControl::OnSetCursor(pWnd, nHitTest, message);
}

int CREditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

long CREditCtrl::GetFontNum() 
{
	if (!m_hWnd && m_FontNum<0)
		return -m_FontNum;
	else
		return m_FontNum;
}

void CREditCtrl::SetFontNum(long nNewValue) 
{
	if (m_FontNum<0 && !m_hWnd)
		m_FontNum=-nNewValue;
	else
		m_FontNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

long CREditCtrl::GetShadow() 
{
	// TODO: Add your property handler here
	if (m_FontNum<0)
		return 1;
	else
		return 0;
}

void CREditCtrl::SetShadow(long nNewValue) 
{
	// TODO: Add your property handler here
	if (m_FontNum<0)
		m_FontNum=-m_FontNum;
	if (nNewValue<0)
		m_FontNum=-m_FontNum;
	InvalidateControl();
	SetModifiedFlag();
}

void CREditCtrl::OnTextChanged() 
{
//	InvalidateControl();
	SetModifiedFlag();	
	COleControl::OnTextChanged();
}

void CREditCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
//	COleControl::OnKeyUp(nChar, nRepCnt, nFlags);
	if (currentword)
	{	//Jim's new code in firetextchanged...
		CString strResult;
		GetString(strResult);
		char*	buffer=new char[strResult.GetLength()+150];
		strcpy	(buffer,strResult);
		FireTextChanged(buffer);
		CPoint cursorpos=currentword->startat;
		cursorpos.x+=CharNumToPix(*currentword,currentchar);
		if (strcmp(strResult,buffer))
		{
			if (strlen(buffer)>strlen(strResult)+50)
				INT3;
			MakeWordList(buffer);
			RepositionWordList();
			InvalidateChangedWords();
			SetToWordUnderCursor(cursorpos);
		}
		delete [] buffer;
	}
}

int	CREditCtrl::MakeWordList(const char* string)
{
	Invalidate();
	wordlist.RemoveAll();
	int	numwords=0;
	if (string[0])
		while (string)
		{
			const UByte* se=(const UByte*)string;
			while (*se>' ')
				se++;
			const UByte* se2=se;
			if (*se2==' ')
				while (se2[1]==' ')
					se2++;
			int	strlen=se-(const UByte*)string;
			while (strlen>OneWord::MAX_CU)
			{
				OneWord tmp (string,OneWord::MAX_CU,OneWord::W_HYPHENOPT);
				CalcWordLen(tmp);
				wordlist.AddTail(tmp);
				string+=OneWord::MAX_CU;
				strlen-=OneWord::MAX_CU;
				numwords++;
			}
			numwords++;
			switch(*se2)
			{
			case '\n':
			{
				OneWord tmp(string,strlen,OneWord::W_HARDLINE);
				CalcWordLen(tmp);
				wordlist.AddTail(tmp);
			}
			break;
			case '\t':
			{
				OneWord tmp(string,strlen,OneWord::W_TAB);
				CalcWordLen(tmp);
				wordlist.AddTail(tmp);
			}
			break;
			case ' ':
			case 0:
			default:
			{
				OneWord tmp(string,strlen,OneWord::W_SPACE);
				CalcWordLen(tmp);
				wordlist.AddTail(tmp);
			}
			break;
			}
			if (*se2)
				while (se2[1]==' ')
					se2++;

			if (*se2)
				if (se2[1]==0)
					string=NULL;
				else
					string=(const char*)se2+1;
			else
				string=NULL;
		}
	else
	{
		currentword=NULL;
	}
	return numwords;
}

int	CREditCtrl::RepositionWordList(POSITION p)
{
	if (!p)
		p=wordlist.GetHeadPosition();
	if (!p)
		return 0;
	CPoint pos=(0,0);
	if (currentword)
		pos=CPoint(currentword->startat.x+CharNumToPix(*currentword,currentchar),currentword->startat.y);

	OneWord& firstword=wordlist.GetAt(p);
	CPoint currpos=firstword.startat;
	CRect wrect;
	GetClientRect(&wrect);
	CSize wh=wrect.Size();
	int	lines=1;
	int halflines=0;
	OneWord*	prevword=NULL;
	OneWord*	clipafterword=NULL;
	bool	prevwaseoln=true;
	while (p)
	{
		OneWord& w=wordlist.GetNext(p);
		if (currpos.x+w.pixlen>wh.cx)
		{
			currpos.x=0;
			currpos.y+=linedepth;
			if (prevword)
				prevword->flags|=w.W_SOFTLINE;
			if (!prevwaseoln)
				prevword->flags|=w.W_REDRAW;
			lines++;
			halflines+=2;
			if (clipafterword==NULL && halflines>=maxlinecount+maxlinecount)
				clipafterword=prevword;
		}
		prevwaseoln=(w.flags&w.W_SOFTLINE)!=0;
		w.flags&=~w.W_SOFTLINE;
		if (w.startat!=currpos)
		{
			w.startat=currpos;
			w.flags|=w.W_REDRAW;
		}
		currpos.x+=w.pixlen;
		if (w.flags&w.W_SPACE)
			currpos.x+=spacewidth;
		if (w.flags&w.W_TAB)
			currpos.x=currpos.x-(currpos.x%tabstep)+tabstep;
		if (w.flags&w.W_HARDLINE)
		{
			currpos.x=0;
			currpos.y+=linedepth+linedepth/2;
			lines++;
			halflines+=3;
			if (clipafterword==NULL && halflines>=maxlinecount+maxlinecount)
				clipafterword=&w;
		}
		prevword=&w;
	}

	if (clipafterword)
	{	//throw away all words after clipped word!
		OneWord* w;
		
		for(p=wordlist.GetTailPosition();(w=&wordlist.GetAt(p))!=clipafterword;p=wordlist.GetTailPosition())
		{
			wordlist.RemoveAt(p);
			if (w==currentword)
				currentword=NULL;
		}
		if (currentword==NULL)
			SetToWordUnderCursor(pos);
	}
	return lines;
}
int CREditCtrl::CalcWordLen(OneWord& w)
{
	int i=strlen(w.text);
	i=CharNumToPix(w,i);
	if (w.pixlen!=i)
		w.flags|=w.W_REDRAW;
	w.pixlen=i;
	return i;
}

int	CREditCtrl::CharNumToPix(OneWord& w,int charnum)
{
	CDC* pdc;
	pdc=GetDC();
    CFont* pOldFont;
	if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
	else pOldFont = pdc->GetCurrentFont();
	if (linedepth==0)
	{
		TEXTMETRIC tm;
		pdc->GetTextMetrics(&tm);
 		linedepth=tm.tmHeight;
		spacewidth=tm.tmAveCharWidth;
	}
	// figure out where the user clicked the cursor
	int m_curPoint=pdc->GetTextExtent(w.text,charnum).cx;
    pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);
	return	m_curPoint;	
}
int	CREditCtrl::PixToCharNum(OneWord& w,int pixels)
{
	if (pixels<=0)
		if (pixels<-spacewidth/2)
			return-1;
		else
			return 0;
	CDC* pdc;
	pdc=GetDC();
    CFont* pOldFont;
	if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
	else pOldFont = pdc->GetCurrentFont();
	// figure out where the user clicked the cursor
	int	l=0,r=0,c;

	for (c=0;w.text[c++];)
	{
		r=pdc->GetTextExtent(w.text,c).cx;
		if (r>pixels)
			break;
		else
			l=r;
	}
	if (pixels<0)
		c=-1;				//prev word
	else
	if (l==r)
	{
		if (pixels<r+spacewidth/2)
			c=w.MAX_CA;		//next word
		else
			c--;
	}
	else
		if (pixels<(l+r)/2)
			c--;			
    pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);
	return c;
}

void	CREditCtrl::InvalidateChangedWords()
{
	CRect r;
	GetClientRect(&r);
	POSITION p=wordlist.GetHeadPosition();
//TempCode JON 26Jun00 	UByteP(0xb0000)[2+(int)this&0x3fe]='I';
	while (p)
	{
		OneWord& w=wordlist.GetNext(p);
		if (w.flags&w.W_REDRAW)
		{	
			if (p==NULL)
			{

				InvalidateControl(&CRect(w.startat.x-CURSOR_THICK_BORDER,w.startat.y-CURSOR_THICK_BORDER,r.right+CURSOR_THICK_BORDER,w.startat.y+linedepth+CURSOR_THICK_BORDER));
				InvalidateControl(&CRect(r.left-CURSOR_THICK_BORDER,w.startat.y+linedepth-CURSOR_THICK_BORDER,r.right+CURSOR_THICK_BORDER,r.bottom+CURSOR_THICK_BORDER));
			}
			else
			if (w.flags&w.W_SOFTLINE)
				InvalidateControl(&CRect(w.startat.x-CURSOR_THICK_BORDER,w.startat.y-CURSOR_THICK_BORDER,r.right+CURSOR_THICK_BORDER,w.startat.y+linedepth+CURSOR_THICK_BORDER));
			else if (w.flags&w.W_HARDLINE)
			{
				InvalidateControl(&CRect(w.startat.x-CURSOR_THICK_BORDER,w.startat.y-CURSOR_THICK_BORDER,r.right+CURSOR_THICK_BORDER,w.startat.y+linedepth+CURSOR_THICK_BORDER));
//DeadCode JON 26Jun00 				if (p)
				InvalidateControl(&CRect(r.left-CURSOR_THICK_BORDER,w.startat.y+linedepth-CURSOR_THICK_BORDER,r.right+CURSOR_THICK_BORDER,w.startat.y+linedepth+linedepth/2+CURSOR_THICK_BORDER));
//DeadCode JON 26Jun00 				else
//DeadCode JON 26Jun00 					InvalidateControl(&CRect(r.left,w.startat.y+linedepth,r.right,r.bottom));
			}
			else if (w.flags&w.W_TAB)
			{
				int x2=w.startat.x+w.pixlen;
				x2=x2-(x2%tabstep)+tabstep;
				InvalidateControl(&CRect(w.startat.x-CURSOR_THICK_BORDER,w.startat.y-CURSOR_THICK_BORDER,x2+CURSOR_THICK_BORDER,w.startat.y+linedepth+CURSOR_THICK_BORDER));
			}
			else
				InvalidateControl(&CRect(w.startat.x-CURSOR_THICK_BORDER,w.startat.y-CURSOR_THICK_BORDER,w.startat.x+w.pixlen+spacewidth+CURSOR_THICK_BORDER,w.startat.y+linedepth+CURSOR_THICK_BORDER));
			w.flags&=~w.W_REDRAW;

		}
	}
}

int	CREditCtrl::GetString(char* string,int max)
{
	POSITION p=wordlist.GetHeadPosition();
	string[0]=0;
	int	outlen=0;
	while (p)
	{
		OneWord& w=wordlist.GetNext(p);
		int len=strlen(w.text);
		if (max<outlen+len)
			return -outlen;
		strcpy(string,w.text);
		string+=len;
		outlen+=len;
		if (w.flags&w.W_SPACE)
		{
			if (max<outlen+1)
				return -outlen;
			strcpy(string++," ");
			outlen++;
		}
		if (w.flags&w.W_HARDLINE)
		{
			if (max<outlen+1)
				return -outlen;
			strcpy(string++,"\n");
			outlen++;
		}
		if (w.flags&w.W_TAB)
		{
			if (max<outlen+1)
				return -outlen;
			strcpy(string++,"\t");
			outlen++;
		}
	}
	return outlen;
}
int	CREditCtrl::GetString(CString &string)
{
	string="";
	int max=32767;
	POSITION p=wordlist.GetHeadPosition();
	int	outlen=0;
	while (p)
	{
		OneWord& w=wordlist.GetNext(p);
		int len=strlen(w.text);
		if (max<outlen+len)
			return -outlen;
		string+=w.text;
		outlen+=len;
		if (w.flags&w.W_SPACE)
		{
			if (max<outlen+1)
				return -outlen;
			if (p)
			{
				string+=" ";
				outlen++;
			}
		}
		if (w.flags&w.W_HARDLINE)
		{
			if (max<outlen+1)
				return -outlen;
			string+="\n";
			outlen++;
		}
		if (w.flags&w.W_TAB)
		{
			if (max<outlen+1)
				return -outlen;
			string+="\t";
			outlen++;
		}
	}
	return outlen;
}

void	CREditCtrl::SetToWordUnderCursor(CPoint p)
{
	POSITION pos=wordlist.GetTailPosition();
//DeadCode JIM 20Oct00 	int	outlen=0;
	if (currentword)
		currentword->flags|=OneWord::W_REDRAW;
	if (pos)
		while (pos)
		{
			OneWord& w=wordlist.GetAt(pos);
			if (p.x>=w.startat.x-spacewidth/2 && p.y>=w.startat.y)
			{
				currentwordpos=pos;
				currentword=&w;
				//get current char from offset p.x-w.startat.x
				currentchar=PixToCharNum(w,p.x-w.startat.x);
				if (currentchar==w.MAX_CA)
					currentchar=strlen(w.text);
				if (currentchar<0)
					currentchar=0;
				w.flags|=w.W_REDRAW;
				InvalidateChangedWords();
				break;

			}
			wordlist.GetPrev(pos);
		}
	else
	{
		currentwordpos=(POSITION)-1;
		OnTimer(0);
	}

}

void	CREditCtrl::SetBlockingKeys(const char* keylist)
{
	if (keylist[0]=='\b')
		if (keylist[2]=='\r')
			maxlinecount=keylist[1];
		else
			maxcharcount=keylist[1];
	else
	{
		allowed=-1;
		while (*keylist)
			allowed%=*keylist++;
	}
}

BSTR CREditCtrl::GetCaption() 
{
	CString strResult;
	// TODO: Add your property handler here
	GetString(strResult);
	return strResult.AllocSysString();
}

void CREditCtrl::SetCaption(LPCTSTR lpszNewValue) 
{
	// TODO: Add your property handler here
//	INT3;
	if (lpszNewValue)
		if (lpszNewValue[0]=='\b')
			SetBlockingKeys(lpszNewValue+1);
		else
		{
			MakeWordList(lpszNewValue);
			RepositionWordList();
			InvalidateChangedWords();
			SetModifiedFlag();
			if ((lpszNewValue==NULL || lpszNewValue[0]=='\0') && linedepth==0 && m_hWnd)
			{
			    CFont* pOldFont;
				CDC* pdc;
				pdc=GetDC();
				pOldFont = pdc->SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
				TEXTMETRIC tm;
				pdc->GetTextMetrics(&tm);
 				linedepth=tm.tmHeight;
				spacewidth=tm.tmAveCharWidth;
				pdc->SelectObject(pOldFont);
				ReleaseDC(pdc);
			}
		}
}


BOOL CREditCtrl::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	KillTimer(TIMERNUM);	
	return COleControl::DestroyWindow();
}
