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

// RComboC.cpp : Implementation of the CRComboCtrl ActiveX Control class.

//#define F_SOUNDS
#define F_BATTLE
#define F_COMMON

//#include "DosDefs.h"
#include "stdafx.h"
#include "RCombo.h"
#include "uiicons.h"

#include "RComboC.h"
#include "RComboP.h"
#include "messages.h"
#include "Fileman.h"
#include "listbx.h"
#include "axcolors.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
#ifndef THIS_FILE_DEFINED
static char THIS_FILE[] = __FILE__;
#endif
#endif


IMPLEMENT_DYNCREATE(CRComboCtrl, COleControl)

BOOL CRComboCtrl::m_bDrawing = FALSE;
Bool CRComboCtrl::m_bDrawOffscreen = FALSE;
extern int GetShadow1XOffset(int fontheight);
extern int GetShadow1YOffset(int fontheight);
extern int GetShadow2XOffset(int fontheight);
extern int GetShadow2YOffset(int fontheight);


struct ComboStyle
{
int	
	cliptextr,clipliner,clipboxr,clipselr;
IconsUI								rhsicon;
int											icondown;	
FixedActiveXColours
	dirk,light,	disd,disl;
bool	
	dorhsline;
int	textalign,margin;float rightfx;
};

ComboStyle	
Combo_Round=
{	22,20,8,22,		ICON_COMBO_BIG_ROUND,	0,
	AXC_CIRCULARCOMBOBOXCOLOR,AXC_CIRCULARCOMBOBOXCOLOR,	AXC_CIRCULARCOMBOBOXCOLOR,AXC_CIRCULARCOMBOBOXCOLOR,
	false,
	TA_LEFT,3,	0.0,
},
Combo_Square=
{	17,1,0,17,			ICON_SPINDOWN,		9,
	AXC_DARKEDGE,AXC_LITEDGE,	AXC_DISABLEDDARKEDGE,AXC_DISABLEDLITEDGE,
	true,
	TA_LEFT,3,	0.0,

},
Combo_SquareC=
{	17,1,0,17,			ICON_SPINDOWN,		9,
	AXC_DARKEDGE,AXC_LITEDGE,	AXC_DISABLEDDARKEDGE,AXC_DISABLEDLITEDGE,
	true,
	TA_CENTER,3,	0.5,

},
Combo_SquareR=
{	17,1,0,17,			ICON_SPINDOWN,		9,
	AXC_DARKEDGE,AXC_LITEDGE,	AXC_DISABLEDDARKEDGE,AXC_DISABLEDLITEDGE,
	true,
	TA_RIGHT,3,	1.0,

},
Combo_Big=
{	25,1,7,25,			ICON_COMBO_BIG_ROUND, 2,
	AXC_DARKEDGE,AXC_LITEDGE,	AXC_DISABLEDDARKEDGE,AXC_DISABLEDLITEDGE,
	true,
	TA_LEFT,5,	0.0,
},
Combo_Art=
{	32,1,5,32,			ICON_NO_ICON,		0,
	AXC_DARKEDGE,AXC_LITEDGE,	AXC_DISABLEDDARKEDGE,AXC_DISABLEDLITEDGE,
	true,
	TA_LEFT,3,	0.0,
},
*combo_styles[]=	{&Combo_Square,&Combo_Round,&Combo_Big,&Combo_SquareC,&Combo_SquareR,&Combo_Art};
enum	ComboStyles	{CS_SQUARE,CS_ROUND,CS_BIG,CS_SQUARE_C,CS_SQUARE_R,CS_ART};

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRComboCtrl, COleControl)
	//{{AFX_MSG_MAP(CRComboCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ENABLE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRComboCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRComboCtrl)
	DISP_PROPERTY_EX(CRComboCtrl, "FontNum", GetFontNum, SetFontNum, VT_I4)
	DISP_PROPERTY_EX(CRComboCtrl, "ListboxLength", GetListboxLength, SetListboxLength, VT_I4)
	DISP_PROPERTY_EX(CRComboCtrl, "CircularStyle", GetCircularStyle, SetCircularStyle, VT_BOOL)
	DISP_PROPERTY_EX(CRComboCtrl, "ShadowColor", GetShadowColor, SetShadowColor, VT_COLOR)
	DISP_PROPERTY_EX(CRComboCtrl, "EndFileNum", GetEndFileNum, SetEndFileNum, VT_I4)
	DISP_PROPERTY_EX(CRComboCtrl, "FileNumMain", GetFileNumMain, SetFileNumMain, VT_I4)
	DISP_PROPERTY_EX(CRComboCtrl, "Style", GetStyle, SetStyle, VT_I4)
	DISP_PROPERTY_EX(CRComboCtrl, "NewJimVar", GetNewJimVar, SetNewJimVar, VT_I4)
	DISP_FUNCTION(CRComboCtrl, "AddString", AddString, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CRComboCtrl, "GetListbox", GetListbox, VT_I4, VTS_NONE)
	DISP_FUNCTION(CRComboCtrl, "SetIndex", SetIndex, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CRComboCtrl, "GetIndex", GetIndex, VT_I4, VTS_NONE)
	DISP_FUNCTION(CRComboCtrl, "Clear", Clear, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CRComboCtrl, "DeleteString", DeleteString, VT_EMPTY, VTS_I4)
	DISP_STOCKPROP_FORECOLOR()
	DISP_STOCKPROP_CAPTION()
	DISP_STOCKPROP_ENABLED()
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRComboCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRComboCtrl)
	EVENT_CUSTOM("TextChanged", FireTextChanged, VTS_BSTR  VTS_I2)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRComboCtrl, 2)
	PROPPAGEID(CRComboPropPage::guid)
    PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CRComboCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRComboCtrl, "RCOMBO.RComboCtrl.1",
	0x737cb0c9, 0xb42b, 0x11d6, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRComboCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRCombo =
		{ 0x737cb0c7, 0xb42b, 0x11d6, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DRComboEvents =
		{ 0x737cb0c8, 0xb42b, 0x11d6, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRComboOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRComboCtrl, IDS_RCOMBO, _dwRComboOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRComboCtrl::CRComboCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRComboCtrl

BOOL CRComboCtrl::CRComboCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_RCOMBO,
			IDB_RCOMBO,
			afxRegApartmentThreading,
			_dwRComboOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("RCombo.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1998 Rowan Software";


/////////////////////////////////////////////////////////////////////////////
// CRComboCtrl::CRComboCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CRComboCtrl::CRComboCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CRComboCtrl::CRComboCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CRComboCtrl::CRComboCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRComboCtrl::CRComboCtrl - Constructor

CRComboCtrl::CRComboCtrl()
{
	InitializeIIDs(&IID_DRCombo, &IID_DRComboEvents);
	blocktextchanged=true;
	m_bInit=TRUE;
	m_index=0;
	m_bCircularStyle=FALSE; // remove if this property is made persistent
	m_ShadowColor = RGB(0,0,0);
	m_FileNum = NULL;
	m_EndFileNum = NULL;
	m_FirstSweep = TRUE;
	S=&Combo_Round;
	phintbox=NULL;
}


/////////////////////////////////////////////////////////////////////////////
// CRComboCtrl::~CRComboCtrl - Destructor

CRComboCtrl::~CRComboCtrl()
{
	// TODO: Cleanup your control's instance data here.
	Clear();
}


bool	ExtTextOut(CDC* pdc,
				   bool shadow,int fontheightforshadow,COLORREF fontcolour,COLORREF shadowcolour,
				   int x,int y,int alignoff,const CRect* cliprect,const char* text)
{
	enum	{MAXTEXT=99};
	int len=strlen(text);
	if (x<cliprect->right)
	{
		char buffer[MAXTEXT+8];
		int pixelsw=cliprect->right-x;
		if (shadow)
			pixelsw-=GetShadow2XOffset(fontheightforshadow);
		if (pdc->GetTextExtent(text,len).cx>=pixelsw)
		{
			if (len>MAXTEXT)
				len=MAXTEXT;
			buffer[0]=buffer[1]=buffer[2]='.';
			memcpy(buffer+3,text,len);
			buffer[len+3]=0;
			INT	numchars;
			SIZE	maxextent;
			GetTextExtentExPoint(*pdc,buffer,len+3,pixelsw,&numchars,NULL,&maxextent);
			*ULongP(buffer+numchars)=*ULongP("...");
			text=buffer+3;
			len=numchars;
		}

		if (shadow)
		{
			pdc->SetTextColor(shadowcolour);
			int shadowx=GetShadow1XOffset(fontheightforshadow);
			int shadowy=GetShadow1YOffset(fontheightforshadow);
			pdc->ExtTextOut(x+shadowx+alignoff,y+shadowy,ETO_CLIPPED,cliprect,text,len,NULL);
			shadowx=GetShadow2XOffset(fontheightforshadow);
			shadowy=GetShadow2YOffset(fontheightforshadow);
			pdc->ExtTextOut(x+shadowx+alignoff,y+shadowy,ETO_CLIPPED,cliprect,text,len,NULL);
		}
		pdc->SetTextColor(fontcolour);
		pdc->ExtTextOut(x+alignoff,y,ETO_CLIPPED,cliprect,text,len,NULL);
		return (text!=buffer+3);
	}
	else
		return false;

}
/////////////////////////////////////////////////////////////////////////////
// CRComboCtrl::OnDraw - Drawing function

void CRComboCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (m_bDrawing || !m_hWnd) return;
	m_bDrawing=TRUE;
	if(m_bDrawOffscreen == TRUE)//global telling to draw offscreen to put in
		m_FirstSweep = FALSE;
	CRect rc = rcBounds;
	CWnd* parent;
	long offsetx;
	long offsety;
	parent=GetParent();
	// we may have a transparent bitmap at the end so use an offscreenDC...
	CDC* pOffScreenDC;
	CBitmap* pOldBitmap=NULL;
	CBitmap bitmap;
	if(m_FirstSweep != TRUE)
	{
		pOffScreenDC=(CDC*)parent->SendMessage(WM_GETOFFSCREENDC,NULL,NULL);	
		bitmap.CreateCompatibleBitmap(pdc,rcBounds.right,rcBounds.bottom);	
		pOldBitmap=pOffScreenDC->SelectObject(&bitmap);
	}
	else
	{
		pOffScreenDC=pdc;
	}

	if (m_list.GetCount())
		if (m_bInit && GetIndex()==-1)
		{
			SetIndex(0);
			m_bInit=FALSE;
		}
	long offsets;
	offsets=parent->SendMessage(WM_GETXYOFFSET,NULL,NULL);
	CRect rect;
	GetWindowRect(rect);
	CRect parentrect;
	parent->GetWindowRect(parentrect);
	offsetx=short(offsets & 0x0000FFFF)+parentrect.left-rect.left;
	offsety=short((offsets & 0xFFFF0000)>>16)+parentrect.top-rect.top;
    CFont* pOldFont;
	pOldFont = pOffScreenDC->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
    pOffScreenDC->SetBkMode(TRANSPARENT);
    pOffScreenDC->SetTextAlign(TA_LEFT | TA_TOP);
    TEXTMETRIC tm;
    pOffScreenDC->GetTextMetrics(&tm);
	FileNum artnum=FIL_NULL;
	BOOL X2flag=FALSE;
	if(m_FirstSweep != TRUE)
	{
		artnum = (FileNum)parent->SendMessage(WM_GETARTWORK,NULL,NULL);
		if (artnum)
			DrawBitmap(artnum,pOffScreenDC,offsetx,offsety);
	}
	X2flag=parent->SendMessage(WM_GETX2FLAG,NULL,NULL);
	if (!artnum && m_FirstSweep != TRUE || !m_hWnd)
	{
		pOffScreenDC->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	}
	if(m_FileNum != NULL)
	{
		DrawBitmap((FileNum)m_FileNum,pOffScreenDC,0,0,rc.right-S->cliptextr);//use drawtransparentbitmap if transparent needed
		DrawBitmap((FileNum)m_EndFileNum,pOffScreenDC,rc.right-S->cliptextr,0);//use drawtransparentbitmap if transparent needed
		
		int indenttexty;
		indenttexty = (m_FontNum * 2);
		if(indenttexty < 0)
			indenttexty = (indenttexty)*(0-1);
		indenttexty = indenttexty+1; 
		if(indenttexty > 5)
			indenttexty = 1;
		// draw the text's shadow
		COLORREF	fontcol=RGB(128,128,128);
		if(GetEnabled())
			fontcol=TranslateColor(GetForeColor());
		pOffScreenDC->SetTextAlign(S->textalign);
		int offset=(rc.right-S->cliptextr)*S->rightfx;
		ExtTextOut(pOffScreenDC,(m_FontNum<0),tm.tmHeight,fontcol,m_ShadowColor,
			  S->margin,2,offset,&CRect(rc.left,rc.top,rc.right-S->cliptextr,rc.bottom),InternalGetText());

//DEADCODE JIM 15/12/99 		if (m_FontNum<0)
//DEADCODE JIM 15/12/99 		{
//DEADCODE JIM 15/12/99 			//pOffScreenDC->SetTextColor(RGB(0,0,0));
//DEADCODE JIM 15/12/99 
//DEADCODE JIM 15/12/99 
//DEADCODE JIM 15/12/99 			pOffScreenDC->SetTextColor(m_ShadowColor);
//DEADCODE JIM 15/12/99 			int shadowx=GetShadow1XOffset(tm.tmHeight);
//DEADCODE JIM 15/12/99 			int shadowy=GetShadow1YOffset(tm.tmHeight);
//DEADCODE JIM 15/12/99 			pOffScreenDC->ExtTextOut(3+shadowx, 2+shadowy,
//DEADCODE JIM 15/12/99 				ETO_CLIPPED, CRect(rc.left,rc.top,rc.right-S->cliptextr,rc.bottom), InternalGetText(), InternalGetText().GetLength(), NULL);
//DEADCODE JIM 15/12/99 			shadowx=GetShadow2XOffset(tm.tmHeight);
//DEADCODE JIM 15/12/99 			shadowy=GetShadow2YOffset(tm.tmHeight);
//DEADCODE JIM 15/12/99 			pOffScreenDC->ExtTextOut(3+shadowx, 2+shadowy,
//DEADCODE JIM 15/12/99 				ETO_CLIPPED, CRect(rc.left,rc.top,rc.right-S->cliptextr,rc.bottom), InternalGetText(), InternalGetText().GetLength(), NULL);
//DEADCODE JIM 15/12/99 		}
//DEADCODE JIM 15/12/99 		if(GetEnabled())
//DEADCODE JIM 15/12/99 		{
//DEADCODE JIM 15/12/99 			 pOffScreenDC->SetTextColor(TranslateColor(GetForeColor()));
//DEADCODE JIM 15/12/99 		}
//DEADCODE JIM 15/12/99 		else
//DEADCODE JIM 15/12/99 		{
//DEADCODE JIM 15/12/99 			pOffScreenDC->SetTextColor(RGB(128,128,128));
//DEADCODE JIM 15/12/99 		}
//DEADCODE JIM 15/12/99 
//DEADCODE JIM 15/12/99 		pOffScreenDC->ExtTextOut(3, 2,
//DEADCODE JIM 15/12/99 			ETO_CLIPPED, CRect(rc.left,rc.top,rc.right-S->cliptextr,rc.bottom), InternalGetText(), InternalGetText().GetLength(), NULL);
	}
	// draw the border and icon at the end
	else
	{
		// draw the text's shadow
		COLORREF	fontcol=RGB(128,128,128);
		if(GetEnabled())
			fontcol=TranslateColor(GetForeColor());
		ExtTextOut(pOffScreenDC,(m_FontNum<0),tm.tmHeight,fontcol,m_ShadowColor,
			  3,2,0,&CRect(rc.left,rc.top,rc.right-S->cliptextr,rc.bottom),InternalGetText());

		CPen BlackPen,WhitePen;
		if (IsWindowEnabled())
		{
			BlackPen.CreatePen(PS_SOLID,1,AXC_DARKEDGE);
			WhitePen.CreatePen(PS_SOLID,1,AXC_LITEDGE);
		}
		else
		{
			BlackPen.CreatePen(PS_SOLID,1,AXC_DISABLEDDARKEDGE);
			WhitePen.CreatePen(PS_SOLID,1,AXC_DISABLEDLITEDGE);
		}
		CPen* oldpen;
		oldpen=pOffScreenDC->SelectObject(&WhitePen);
		if (S->dorhsline)
		{
			pOffScreenDC->MoveTo(rcBounds.right-S->clipliner,rcBounds.top);
			pOffScreenDC->LineTo(rcBounds.right-S->clipliner,rcBounds.bottom-1);
		}
		else
			pOffScreenDC->MoveTo(rcBounds.right-S->clipliner,rcBounds.bottom-1);
		pOffScreenDC->LineTo(rcBounds.left,rcBounds.bottom-1);
		pOffScreenDC->SelectObject(&BlackPen);
		pOffScreenDC->LineTo(rcBounds.left,rcBounds.top);
		pOffScreenDC->LineTo(rcBounds.right-S->clipliner,rcBounds.top);
		DrawTransparentBitmap(S->rhsicon,pOffScreenDC,rc.right-S->cliptextr,S->icondown);
		pOffScreenDC->SelectObject(oldpen);
	}
	pOffScreenDC->SelectObject(pOldFont);
	if(m_FirstSweep != TRUE)
	{
		pdc->BitBlt(0,0,rcBounds.right-rcBounds.left,rcBounds.bottom-rcBounds.top,pOffScreenDC,
						0,0,SRCCOPY); // flips offscreen dc to real dc
		if (pOldBitmap)
			pOffScreenDC->SelectObject(pOldBitmap);
	}
	m_FirstSweep = FALSE;
	m_bDrawing=FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CRComboCtrl::DoPropExchange - Persistence support

void CRComboCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Long(pPX, _T("FontNum"), m_FontNum, 0);
	PX_Long(pPX, _T("ListboxLength"), m_ListboxLength, 100);
	if (pPX->GetVersion()&0x1)
	{
		PX_Long(pPX, _T("Style"), m_Style, 0);

	}
	else
	{
		m_Style=0;
	}
	m_Style&=0xffff;
	S=combo_styles[m_Style];
}


/////////////////////////////////////////////////////////////////////////////
// CRComboCtrl::OnResetState - Reset control to default state

void CRComboCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	SetForeColor(RGB(255,255,255));
	SetShadowColor(RGB(0,0,0)) ;
}


/////////////////////////////////////////////////////////////////////////////
// CRComboCtrl message handlers

void CRComboCtrl::AddString(LPCTSTR text) 
{
	// ***************************************
//	CRListBox* rlistbox=(CRListBox*)m_listbox.GetDlgItem(IDC_RLISTBOXCTRL1);
//	rlistbox->AddString(text,0);
	char* buffer=new char[strlen(text)+1]; // include terminating null character
	strcpy(buffer,text);
	m_list.AddTail(buffer);
}

long CRComboCtrl::GetFontNum() 
{
	if (m_FontNum<0)
		return -m_FontNum;
	else
		return m_FontNum;
}

void CRComboCtrl::SetFontNum(long nNewValue) 
{
	if (!m_hWnd && m_FontNum<0)
		m_FontNum=-nNewValue;
	else
		m_FontNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}
long CRComboCtrl::GetNewJimVar() 
{
	// TODO: Add your property handler here
	if (m_FontNum<0)
		return 1;
	else
		return 0;
}

void CRComboCtrl::SetNewJimVar(long nNewValue) 
{
	// TODO: Add your property handler here
	if (m_FontNum<0)
		m_FontNum=-m_FontNum;
	if (nNewValue<0)
		m_FontNum=-m_FontNum;
	SetModifiedFlag();
}
LARGE_INTEGER	drawtime,spptime;

void CRComboCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (phintbox)
	{
 		if (GetParent())
		{
			phintbox=(CDialog*)GetParent()->SendMessage(WM_GETHINTBOX,NULL,NULL);
			if (phintbox)
			{
				phintbox->ShowWindow(SW_HIDE);
			}
			phintbox=NULL;
		}
		ReleaseCapture();
	}
	COleControl::OnLButtonDown(nFlags, point);
	if (m_list.GetCount()==0)
		return;
	CListBx* pDialog=(CListBx*)GetParent()->SendMessage(WM_GETCOMBODIALOG,NULL,NULL);
	CRListBox* rlistbox=(CRListBox*)GetParent()->SendMessage(WM_GETCOMBOLISTBOX,NULL,NULL);
//TEMPCODE RDH 22/10/99 	rlistbox->SetDrawBackgGound(TRUE); //uncoment this when the list box is done
	CRect rect;
	GetClientRect(rect);
	if (point.x>rect.right-S->clipselr)
	{	//open list box!
		GetParent()->SendMessage(WM_PLAYSOUND,FIL_SFX_OFFICE_PAPERSLIDE,NULL);//DAW 06Apr99

		// first transfer the data from the combobox to the listbox
		pDialog->m_pCombo=this;
		rlistbox->Clear();
//		if(m_bCircularStyle)
//			rlistbox->SetLineColor(AXC_CIRCULARCOMBOBOXCOLOR);
		rlistbox->AddColumn(10);
		int count=m_list.GetCount();
		POSITION position=m_list.GetHeadPosition();
		for (int i=0;i<count;i++)
		{
			 rlistbox->AddString(m_list.GetNext(position),0);
		}
		rlistbox->SetHilightRow(m_index);
		// check if m_ListboxLength is a multiple of the font height
		CDC* pdc=GetDC();
		CFont* pfont=(CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL);
		CFont* poldfont=pdc->SelectObject(pfont);
		TEXTMETRIC tm;
		pdc->GetTextMetrics(&tm);
		tm.tmHeight+=GetShadow2YOffset(tm.tmHeight-rlistbox->GetVertSeperation());
		tm.tmHeight+=rlistbox->GetVertSeperation();
		if ((m_ListboxLength-1)%tm.tmHeight)
			m_ListboxLength+=tm.tmHeight-(m_ListboxLength%tm.tmHeight)+1;
		QueryPerformanceCounter(&spptime);
		rlistbox->SetParentPointer((long)GetParent()->m_hWnd);
		rlistbox->SetFontPtr((long)pfont);
		rlistbox->SetFontNum(m_FontNum);
		long listboxheight=rlistbox->GetListHeight();

		GetWindowRect(rect);	
		CWnd* parent;
		parent=this->GetParent();
		if(parent->SendMessage(WM_GETX2FLAG,NULL,NULL))
			if (listboxheight>m_ListboxLength*2) 
				listboxheight=m_ListboxLength*2;
			else;	//dangling else problem. What dangling else problem?
		else		// try using curly brackets next time
			if (listboxheight>m_ListboxLength) 
				listboxheight=m_ListboxLength;
		CRect parentrect;

		parent->GetWindowRect(parentrect);
		CRect listboxrect;
		CWnd* parent2=parent;
		long artwork=parent->SendMessage(WM_GETARTWORK,NULL,NULL);
		while (parent2->GetParent()->SendMessage(WM_GETARTWORK,NULL,NULL)==artwork)
		{
			parent2=parent2->GetParent();
		}
		CRect parentrect2;
		parent2->GetWindowRect(parentrect2);
		int dy=0;
		if (rect.bottom+listboxheight>parentrect2.bottom)
//			&& rect.top-listboxheight>parentrect.top)
		{
			listboxrect=CRect(rect.left-1,rect.top-listboxheight-4,rect.right+1,rect.top);
		}
		else
		{
			listboxrect=CRect(rect.left-1,rect.bottom,rect.right+1,rect.bottom+listboxheight+4);
			dy=-1;
		}
		listboxrect.right-=S->clipboxr;
		pDialog->MoveWindow(listboxrect);
		rlistbox->MoveWindow(1,dy+1,listboxrect.Width()-2,listboxrect.Height()-2);
		rlistbox->UpdateScrollBar();
		QueryPerformanceCounter(&drawtime);
		pDialog->ShowWindow(SW_SHOW);
		pDialog->BringWindowToTop();
		pdc->SelectObject(poldfont);
		ReleaseDC(pdc);
	}
	else
		if (m_list.GetCount())
		{
			int row=GetIndex();
			row++;
			if (row>=m_list.GetCount()) 
				row=0;
			SetIndex(row);
			GetParent()->SendMessage(WM_PLAYSOUND,FIL_SFX_OFFICE_KEYPRESS1,NULL);//RJS 13Apr99
			FireTextChanged(InternalGetText(),row);
		}
}

long CRComboCtrl::GetListboxLength() 
{
	return m_ListboxLength;
}

void CRComboCtrl::SetListboxLength(long nNewValue) 
{
	m_ListboxLength=nNewValue;
	SetModifiedFlag();
}

long CRComboCtrl::GetListbox() 
{
	return (long)GetParent()->SendMessage(WM_GETCOMBOLISTBOX,NULL,NULL);
}

int CRComboCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	// **************************************************	
//	m_listbox.Create(CListBx::IDD,GetParent());
//	m_listbox.m_pCombo=this;
//	CRListBox* rlistbox=(CRListBox*)m_listbox.GetDlgItem(IDC_RLISTBOXCTRL1);
//	rlistbox->Clear();
//	rlistbox->AddColumn(6);
	return 0;
}
void CRComboCtrl::OnTextChanged() 
{	
	if (!m_bDrawing && m_hWnd) 
	{		
		CRListBox* rlistbox=(CRListBox*)GetParent()->SendMessage(WM_GETCOMBOLISTBOX,NULL,NULL);
		InvalidateControl();
		SetModifiedFlag();
		m_index=rlistbox->GetHilightRow();
		if (!blocktextchanged && rlistbox->SelectRecentlyFired())
		{
			CString string=InternalGetText();
			FireTextChanged(string,m_index);
		}
		blocktextchanged=false;
	}
	COleControl::OnTextChanged();
}

void CRComboCtrl::SetIndex(long row) 
{
	if (row>=m_list.GetCount()||row<0)
		INT3;
	char* buffer=m_list.GetAt(m_list.FindIndex(row));
	if (buffer)
	{
		SetWindowText(buffer);
	}
	m_index=row;
}

long CRComboCtrl::GetIndex() 
{
	return m_index;
//	CRListBox* rlistbox=(CRListBox*)GetParent()->SendMessage(WM_GETCOMBOLISTBOX,NULL,NULL);
//	return rlistbox->GetHilightRow();
}

void CRComboCtrl::Clear() 
{
	// *********************************
//	CRListBox* rlistbox=(CRListBox*)m_listbox.GetDlgItem(IDC_RLISTBOXCTRL1);
//	int w=rlistbox->GetColumnWidth(0);
//	rlistbox->Clear();
//	rlistbox->AddColumn(w);
	int count=m_list.GetCount();
	POSITION position=m_list.GetHeadPosition();
	for (int i=0;i<count;i++)
	{
		 delete [] m_list.GetNext(position);
	}
	m_list.RemoveAll();
	m_index=0;
}

void CRComboCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	OnLButtonDown(nFlags, point);
}

void CRComboCtrl::OnEnable(BOOL bEnable) 
{
	COleControl::OnEnable(bEnable);
	InvalidateControl();
}

void CRComboCtrl::DrawBitmap(FileNum filenum,CDC* pdc,int x,int y)
{
	CWnd* parent;
	parent=GetParent();
	BYTE* pData;
	pData = (BYTE*)parent->SendMessage(WM_GETFILE,filenum,NULL);
	if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
	{
		// now render it...
		BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
		BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
		pData+=pFile->bfOffBits;
		SetDIBitsToDevice(pdc->m_hDC,x,y,pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
			0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS);
	}
	parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
}

void CRComboCtrl::DrawBitmap(FileNum filenum,CDC* pdc,int x,int y,int maxx)
{
	CWnd* parent;
	parent=GetParent();
	BYTE* pData;
	pData = (BYTE*)parent->SendMessage(WM_GETFILE,filenum,NULL);
	if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
	{
		// now render it...
		BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
		BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
		pData+=pFile->bfOffBits;
		SetDIBitsToDevice(pdc->m_hDC,x,y,maxx, pInfo->bmiHeader.biHeight,
			0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS);
	}
	parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
}

void CRComboCtrl::DrawTransparentBitmap(IconsUI iconnum,CDC * pDC, int x, int y)
{
	BYTE* pData;
	CWnd* parent=GetParent();
	pData = (BYTE*)parent->SendMessage(WM_GETFILE,iconnum,NULL);
	IconDescUI* icon=(IconDescUI*)pData;
	icon->MaskIcon(pDC,CPoint(x,y));
}


void CRComboCtrl::DrawTransparentBitmap(FileNum filenum,CDC * pDC, int x, int y)
{
		// note that palette entry 254 is the transparent colour
	BYTE* pData;
	CWnd* parent=GetParent();
	pData = (BYTE*)parent->SendMessage(WM_GETFILE,filenum,NULL);
	if (pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
	{
		// now render it...
		BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
		BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
		pData+=pFile->bfOffBits;
		BYTE* pData2=pData;
		BYTE code;
		int Width=pInfo->bmiHeader.biWidth;
		if (Width%4) Width+=4-Width%4; // DWord alignment
		int Height=pInfo->bmiHeader.biHeight;
		int x2,y2;
		int tempy2;
		RGBQUAD color;
		if(m_FirstSweep == FALSE)//global varialbe tells to of screen
		{//dont do test
			for (y2=Height-1;y2>=0;y2--)
			{
				for (x2=0;x2<Width;x2++)
				{
					code=*pData2++;
					if (code!=254 && x2<pInfo->bmiHeader.biWidth)
					{
						color=pInfo->bmiColors[code];
						pDC->SetPixel(x+x2,y+y2,RGB(color.rgbRed,color.rgbGreen,color.rgbBlue));
					}
				}
			}
		}
		else
		{//do test
			Bool tested = FALSE;
			for (y2=Height-1;y2>=0;y2--)
			{						
				for (x2=0;x2<Width;x2++)
				{
					code=*pData2++;
					if (code!=254 && x2<pInfo->bmiHeader.biWidth)
					{
						color=pInfo->bmiColors[code];		
						COLORREF setval = pDC->GetNearestColor(RGB(color.rgbRed,color.rgbGreen,color.rgbBlue));
						pDC->SetPixel(x+x2,y+y2,setval);
						COLORREF returnval = pDC->GetPixel(x+x2,y+y2);
						tested = TRUE;
						if(setval != returnval)
						{
							//set global variable to draw all editbtc controls offscreen
							//cause control to redraw offscreen
							m_bDrawOffscreen=TRUE;
							m_bDrawing=FALSE;
							InvalidateControl();
						}
						x2++;
						break;
					}
				}
				if(tested == TRUE)
				{
					break;
				}
			}
			if(m_bDrawing==TRUE)
			{
				for (y2;y2>=0;y2--)
				{
					for (x2=0;x2<Width;x2++)
					{
						code=*pData2++;
						if (code!=254)
						{
							color=pInfo->bmiColors[code];
							pDC->SetPixel(x+x2,y+y2,RGB(color.rgbRed,color.rgbGreen,color.rgbBlue));
						}
					}
					x2 = 0;
				}
			}
		}
	}
	parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
}

void CRComboCtrl::DrawTransparentBitmap(FileNum filenum,CDC * pDC, int x, int y,int maxx)
{
	// note that palette entry 254 is the transparent colour
	BYTE* pData;
	CWnd* parent=GetParent();
	pData = (BYTE*)parent->SendMessage(WM_GETFILE,filenum,NULL);
	if (pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
	{
		// now render it...
		BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
		BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
		pData+=pFile->bfOffBits;
		BYTE* pData2=pData;
		BYTE code;
		int Width=pInfo->bmiHeader.biWidth;
		if (Width%4) Width+=4-Width%4; // DWord alignment
		int Height=pInfo->bmiHeader.biHeight;
		int x2,y2;
		RGBQUAD color;
		for (y2=Height-1;y2>=0;y2--)
		{
			for (x2=0;x2<Width;x2++)
			{
				code=*pData2++;
				if ((code!=254) && (x2<pInfo->bmiHeader.biWidth) && ((x + x2) < (maxx)))
				{
					color=pInfo->bmiColors[code];
					pDC->SetPixel(x+x2,y+y2,RGB(color.rgbRed,color.rgbGreen,color.rgbBlue));
				}
			}
		}
	}
	parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
}


void CRComboCtrl::DeleteString(long index) 
{
	POSITION position;
	position=m_list.FindIndex(index);
	delete [] m_list.GetAt(position);
	m_list.RemoveAt(position);
	if (m_index>index) m_index--;
}

BOOL CRComboCtrl::GetCircularStyle() 
{
	return m_bCircularStyle;
}

void CRComboCtrl::SetCircularStyle(BOOL bNewValue) 
{
	m_bCircularStyle=bNewValue;
	S=combo_styles[bNewValue];
	SetModifiedFlag();
	InvalidateControl();
}

OLE_COLOR CRComboCtrl::GetShadowColor() 
{
	return m_ShadowColor;
	//return RGB(0,0,0);
}

void CRComboCtrl::SetShadowColor(OLE_COLOR nNewValue) 
{
	m_ShadowColor = nNewValue;
	SetModifiedFlag();
}

long CRComboCtrl::GetFileNumMain() 
{
	return m_FileNum;
//	return 0;
}

void CRComboCtrl::SetFileNumMain(long nNewValue) 
{
	m_FileNum = nNewValue;
	m_bCircularStyle=CS_ART;
	S=combo_styles[CS_ART];
	SetModifiedFlag();
}

long CRComboCtrl::GetEndFileNum() 
{
	return m_EndFileNum;
//	return 0;
}

void CRComboCtrl::SetEndFileNum(long nNewValue) 
{
	m_EndFileNum = nNewValue;
	m_bCircularStyle=CS_ART;
	S=combo_styles[CS_ART];
	SetModifiedFlag();
}

long CRComboCtrl::GetStyle() 
{
	// TODO: Add your property handler here

	return m_Style;
}

void CRComboCtrl::SetStyle(long nNewValue) 
{
	// TODO: Add your property handler here
	m_Style=nNewValue;
	SetModifiedFlag();
}


void CRComboCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rc;
	GetClientRect(rc);
	CListBx* pDialog=(CListBx*)GetParent()->SendMessage(WM_GETCOMBODIALOG,NULL,NULL);
	if (!(nFlags&MK_LBUTTON))
		if (!pDialog || !pDialog->IsWindowVisible())
			if (point.x<0 || point.y<0 || point.x>rc.right || point.y>rc.bottom)
			{
				if (phintbox)
				{
 					if (GetParent())
					{
						phintbox=(CDialog*)GetParent()->SendMessage(WM_GETHINTBOX,NULL,NULL);
						if (phintbox)
						{
							phintbox->ShowWindow(SW_HIDE);
						}
						phintbox=NULL;
					}
					ReleaseCapture();
				}

			}
			else
			{
				CDC* pdc;
				pdc=GetDC();
				CFont* pOldFont;
				pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
				TEXTMETRIC tm;
				pdc->GetTextMetrics(&tm);
				int dialwidth=rc.right-S->cliptextr-3-GetShadow2XOffset(tm.tmHeight);	
				int textwidth=pdc->GetTextExtent(InternalGetText()).cx;
				if (dialwidth<textwidth)
				{
					SetCapture();
					phintbox=(CDialog*)GetParent()->SendMessage(WM_GETHINTBOX,NULL,NULL);
					if (phintbox)
					{
						CString realhint=CString(' ')+InternalGetText()+' ';
						phintbox->SetWindowText(realhint);
						CDC* pDC=phintbox->GetDC();
						// select in a font here if you want
						CSize textsize=pDC->GetTextExtent(realhint);
						// a good way of getting the screen resolution
						CRect deskrect;
						GetDesktopWindow()->GetWindowRect(deskrect);
						GetWindowRect(rc);

						CPoint hinttopleft=CPoint(rc.left,rc.bottom+5);
						if (hinttopleft.x+textsize.cx>deskrect.right) 
							hinttopleft.x=rc.right-textsize.cx-3;
						if (hinttopleft.y+textsize.cy>deskrect.bottom) 
							hinttopleft.y=rc.top-8-textsize.cy;
						phintbox->MoveWindow(hinttopleft.x,hinttopleft.y,textsize.cx+2,textsize.cy+2);
						phintbox->ShowWindow(SW_SHOW);
						phintbox->ReleaseDC(pDC);
					}
				}

				pdc->SelectObject(pOldFont);
				ReleaseDC(pdc);
			}
	COleControl::OnMouseMove(nFlags, point);
}

BOOL CRComboCtrl::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (phintbox)
	{
 		if (GetParent())
		{
			phintbox=(CDialog*)GetParent()->SendMessage(WM_GETHINTBOX,NULL,NULL);
			if (phintbox)
			{
				phintbox->ShowWindow(SW_HIDE);
			}
			phintbox=NULL;
		}
		ReleaseCapture();
	}
	
	return COleControl::DestroyWindow();
}
