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

// RButtonCtl.cpp : Implementation of the CRButtonCtrl ActiveX Control class.

#define F_BATTLE

#include "DosDefs.h"
#include "stdafx.h"
#include "RButton.h"
#include "RButtonC.h"
#include "RButtonP.h"
#include "messages.h"
#include "..\mfc\resource.h"
#include	"uiicons.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
#ifndef THIS_FILE_DEFINED
static char THIS_FILE[] = __FILE__;
#endif
#endif

BOOL CRButtonCtrl::m_bDrawing = FALSE;
#define ICONWIDTH  26

IMPLEMENT_DYNCREATE(CRButtonCtrl, COleControl)
extern int GetResourceNumberFromID(const char* text);
extern BOOL ConvertResourceID(const char* text, char* output);
extern int GetFileNum(const char* text);
extern int GetShadow1XOffset(int fontheight);
extern int GetShadow1YOffset(int fontheight);
extern int GetShadow2XOffset(int fontheight);
extern int GetShadow2YOffset(int fontheight);
/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRButtonCtrl, COleControl)
	//{{AFX_MSG_MAP(CRButtonCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_HELPINFO()
	ON_WM_KEYDOWN()
	ON_WM_CAPTURECHANGED()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRButtonCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRButtonCtrl)
	DISP_PROPERTY_NOTIFY(CRButtonCtrl, "UpdateCaption", m_updateCaption, OnUpdateCaptionChanged, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "MovesParent", GetMovesParent, SetMovesParent, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "FontNum", GetFontNum, SetFontNum, VT_I4)
	DISP_PROPERTY_EX(CRButtonCtrl, "CloseButton", GetCloseButton, SetCloseButton, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "TickButton", GetTickButton, SetTickButton, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "ShowShadow", GetShowShadow, SetShowShadow, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "ShadowColor", GetShadowColor, SetShadowColor, VT_COLOR)
	DISP_PROPERTY_EX(CRButtonCtrl, "String", GetString, SetString, VT_BSTR)
	DISP_PROPERTY_EX(CRButtonCtrl, "ResourceNumber", GetResourceNumber, SetResourceNumber, VT_I4)
	DISP_PROPERTY_EX(CRButtonCtrl, "NormalFileNum", GetNormalFileNum, SetNormalFileNum, VT_I4)
	DISP_PROPERTY_EX(CRButtonCtrl, "PressedFileNum", GetPressedFileNum, SetPressedFileNum, VT_I4)
	DISP_PROPERTY_EX(CRButtonCtrl, "NormalFileNumString", GetNormalFileNumString, SetNormalFileNumString, VT_BSTR)
	DISP_PROPERTY_EX(CRButtonCtrl, "PressedFileNumString", GetPressedFileNumString, SetPressedFileNumString, VT_BSTR)
	DISP_PROPERTY_EX(CRButtonCtrl, "Pressed", GetPressed, SetPressed, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "Disabled", GetDisabled, SetDisabled, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "HintStringID", GetHintStringID, SetHintStringID, VT_BSTR)
	DISP_PROPERTY_EX(CRButtonCtrl, "HintResourceNumber", GetHintResourceNumber, SetHintResourceNumber, VT_I4)
	DISP_PROPERTY_EX(CRButtonCtrl, "Transparency", GetTransparency, SetTransparency, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "TransparentFileNum", GetTransparentBitMap, SetTransparentBitMap, VT_I4)
	DISP_PROPERTY_EX(CRButtonCtrl, "HelpButton", GetHelpButton, SetHelpButton, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "HintString", GetHintString, SetHintString, VT_BSTR)
	DISP_STOCKPROP_FORECOLOR()
	DISP_STOCKPROP_CAPTION()
	DISP_STOCKPROP_BACKCOLOR()
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRButtonCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRButtonCtrl)
	EVENT_CUSTOM("Clicked", FireClicked, VTS_NONE)
	EVENT_CUSTOM("Cancel", FireCancel, VTS_NONE)
	EVENT_CUSTOM("OK", FireOK, VTS_NONE)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRButtonCtrl, 2)
	PROPPAGEID(CRButtonPropPage::guid)
//	PROPPAGEID(CLSID_CPicturePropPage)
    PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CRButtonCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRButtonCtrl, "RBUTTON.RButtonCtrl.1",
	0x78918646, 0xa917, 0x11d6, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRButtonCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRButton =
		{ 0x78918644, 0xa917, 0x11d6, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DRButtonEvents =
		{ 0x78918645, 0xa917, 0x11d6, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRButtonOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRButtonCtrl, IDS_RBUTTON, _dwRButtonOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::CRButtonCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRButtonCtrl

BOOL CRButtonCtrl::CRButtonCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_RBUTTON,
			IDB_RBUTTON,
			afxRegApartmentThreading,
			_dwRButtonOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("RButton.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1998 Rowan Software";


/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::CRButtonCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CRButtonCtrl::CRButtonCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::CRButtonCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CRButtonCtrl::CRButtonCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::CRButtonCtrl - Constructor

CRButtonCtrl::CRButtonCtrl()
{
	InitializeIIDs(&IID_DRButton, &IID_DRButtonEvents);
	m_LButtonDown=FALSE;
	m_bInit=TRUE;
//	if (!m_hWnd) FILEMAN.InitFileSystem(); // ONLY DO THIS IF AT DESIGN TIME!!!!!!!!
	// disabled for now since design time is so hard to detect...
//	m_bDrawing=FALSE;
	m_bDisabled=FALSE;
	m_b[Pressed]=FALSE;
	m_b[ClosePressed]=FALSE;
	m_b[HelpPressed]=FALSE;
	m_b[TickPressed]=FALSE;
	m_TransparentInnerFileNum=NULL;
	m_BitMapWithTransparencies = FALSE; // Woody Added
	m_FirstSweep = TRUE;
	m_bHelpButton = TRUE;
	gotparentwnd=false;	//not yet tried to get parent wnd
	phintbox=NULL;
	m_nTimer=0;
}

/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::DoPropExchange - Persistence support

void CRButtonCtrl::DoPropExchange(CPropExchange* pPX)
{
	m_ResourceNumber&=0x00ffffff;
	m_ResourceNumber+=m_alignment<<24;

	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Bool(pPX, _T("MovesParent"), m_bMovesParent, FALSE);
	PX_Long(pPX, _T("FontNum"), m_FontNum, 0);
	PX_Bool(pPX, _T("CloseButton"), m_bCloseButton, FALSE);
	PX_Bool(pPX, _T("TickButton"), m_bTickButton, FALSE);
	PX_Bool(pPX, _T("ShowShadow"), m_bShowShadow, FALSE);
	PX_Color(pPX, _T("ShadowColor"), m_ShadowColor, FALSE);
	PX_String(pPX, _T("String"), m_string, _T(""));
	PX_Long(pPX, _T("ResourceNumber"), m_ResourceNumber, 0);
	PX_Long(pPX, _T("NormalFileNum"), m_NormalFileNum, 0);
	PX_Long(pPX, _T("PressedFileNum"), m_PressedFileNum, 7);
	PX_String(pPX, _T("NormalFileNumString"), m_NormalFileNumString, _T(""));
	PX_String(pPX, _T("PressedFileNumString"), m_PressedFileNumString, _T(""));
	if (pPX->GetVersion()&0x1)
	{
		PX_String(pPX, _T("HintString"), m_hintString, _T(""));
		PX_String(pPX, _T("HintStringID"), m_hintStringID, _T(""));
		PX_Long(pPX, _T("HintResourceNumber"), m_hintResourceNumber, 0);
	}
	else
	{


	}
	if (pPX->GetVersion()&0x2)
	{


	}
	else
	{

	}
	m_alignment=m_ResourceNumber>>24;
//DeadCode MS 04May100 	UByteP(0xB0000)[160*5]='0'+m_alignment;
	m_ResourceNumber&=0x00ffffff;

	if (pPX->IsLoading())
	{
		if (GetBackColor()==0)
			SetBackColor(GetForeColor());
		if (m_bCloseButton || m_bTickButton)							  //JIM 21/05/99
			m_bHelpButton=TRUE; // remove this if it becomes a persistent property
		else
			m_bHelpButton=FALSE;
	}
	if (m_PressedFileNum==7)
		m_PressedFileNumString="";

}
//////////////////////////////////////////////////////////////////////
//
// Function:    GetParentWndInfo
// Date:		21/05/99
// Author:		JIM
//
//Description:	Get all the info from the parent that Dallas couldn't be bothered with...
//				This procedure is called at the top of any routine that might try to access
//				one of:
//					caption						m_ResourceNumber==>m_string
//					hint						m_hintResourceNumber==>m_hintString
//					background artwork number???
//					font number???
//
//////////////////////////////////////////////////////////////////////
void	CRButtonCtrl::GetParentWndInfo()
{
	if (!gotparentwnd)
	{
		gotparentwnd=true;
		if (m_hWnd)
		{
			CWnd* parent = GetParent();	//JW 15Dec98
			if (parent)
			{
				char workspace[100];
				workspace[0]=99;
				if (m_ResourceNumber && (m_ResourceNumber&0x00ffffff)!=IDS_NONE)
				{
					int strsize=parent->SendMessage(WM_GETSTRING,m_ResourceNumber,(int)workspace);
					m_string=workspace;
				}
				else
					m_string="";
				workspace[0]=99;
				if (!m_hintStringID.IsEmpty() && m_hintStringID [0]>' ' && m_hintResourceNumber && m_hintResourceNumber!=IDS_NONE)
				{
					int strsize=parent->SendMessage(WM_GETSTRING,m_hintResourceNumber,(int)workspace);
					m_hintString=workspace;
				}
				else
					m_hintString="";
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::~CRButtonCtrl - Destructor

CRButtonCtrl::~CRButtonCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::OnDraw - Drawing function

void CRButtonCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// note that palette entry 254 is the transparent colour//JW 15Dec98
	// TODO: Replace the following code with your own drawing code.
	if (m_bDrawing) 
		return;
	GetParentWndInfo();
	// need to use an offscreenDC soley because we are			//JW 15Dec98
	// using dallas's transparent blit function
	// which leaves pink flashes if not rendered offscreen
	CDC* pOffScreenDC;											//JW 15Dec98
	CWnd* parent ;												//JW 15Dec98
	CBitmap* pOldBitmap=NULL;										//JW 15Dec98
	CBitmap bitmap;												//JW 15Dec98
	m_bDrawing=TRUE;

	if (m_hWnd)					//JW 15Dec98
		parent = GetParent();	//JW 15Dec98
	else						//JW 15Dec98
		parent = NULL ;			//JW 15Dec98

	if (m_bInit)
	{
		m_bInit=FALSE;
//		if (m_bCloseButton || m_bTickButton)
//			m_bHelpButton=TRUE; // remove this if it becomes a persistent property
//		else
//			m_bHelpButton=FALSE;
//DEADCODE JIM 01/06/99 		if(!m_bCloseButton && !m_bTickButton)
//DEADCODE JIM 01/06/99 			m_bHelpButton=FALSE;
		if (m_bCloseButton) 
		{
			m_closeUpIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_BYEUP));
			m_closeDownIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_BYEDOWN));
		}
		if (m_bTickButton) 
		{
			m_tickUpIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_TICKUP));
			m_tickDownIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_TICKDOWN));
		}
		if (m_bHelpButton) 
		{
			m_helpUpIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_HELPUP));
			m_helpDownIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_HELPDOWN));
		}
	}
	long filenum=m_NormalFileNum;
	if (filenum==FIL_NULL)
	{
		m_BitMapWithTransparencies=TRUE;
	}
	if (filenum>=ICON_PAGE_1)
	{
		m_BitMapWithTransparencies=TRUE;
		if 	(m_b[Pressed])
			filenum+=ICON_SELECT_1;
		if (m_bDisabled)
			filenum+=ICON_SELECT_4;
		else if (m_LButtonDown)
			filenum+=ICON_SELECT_2;
	}
	else
	if (m_PressedFileNum<6 && m_PressedFileNum>0)
	{
		if (m_bDisabled && m_PressedFileNum>=4 && !m_b[Pressed])
			filenum=m_NormalFileNum+3;
		else if (m_bDisabled && m_PressedFileNum>=5 && m_b[Pressed])
			filenum=m_NormalFileNum+4;
		else if (m_bDisabled && m_PressedFileNum==4)				  //JIM 14/04/99
			filenum=m_NormalFileNum+3;								  //JIM 14/04/99
		else if (m_LButtonDown && m_PressedFileNum>=2)
			filenum=m_NormalFileNum+1;
		else if (m_b[Pressed] && m_PressedFileNum>=3)
			filenum=m_NormalFileNum+2;
	}
	else if (m_PressedFileNum && m_LButtonDown)
		filenum=m_PressedFileNum;
	int	drawniconwidth=0;
	if (m_hWnd && (m_BitMapWithTransparencies || m_TransparentInnerFileNum)) //JW 15/2/98
	{
		if(m_FirstSweep != TRUE)
		{
			pOffScreenDC = (CDC*)parent->SendMessage(WM_GETOFFSCREENDC,NULL,NULL);
			bitmap.CreateCompatibleBitmap(pdc,rcBounds.right,rcBounds.bottom);
			pOldBitmap=pOffScreenDC->SelectObject(&bitmap);
		}
		else
		{
			pOffScreenDC = pdc;
		}

		FileNum artnum=FIL_NULL; // only need to draw background if we are in transparent mode JW 15Dec98
		if (m_hWnd)
		{
			long offsetx, offsety ;
			long offsets;
			CRect parentrect;
			CRect rect ;
			
			offsets=parent->SendMessage(WM_GETXYOFFSET,NULL,NULL);
			if(m_FirstSweep != TRUE)
				artnum = (FileNum)parent->SendMessage(WM_GETARTWORK,NULL,NULL);

			GetWindowRect(rect);
			parent->GetWindowRect(parentrect);
			offsetx=short(offsets & 0x0000FFFF)+parentrect.left-rect.left;
			offsety=short((offsets & 0xFFFF0000)>>16)+parentrect.top-rect.top;
			BYTE* pData;
			if (artnum)
			{
				pData = (BYTE*)parent->SendMessage(WM_GETFILE,artnum,NULL);
				if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file//JW 15Dec98
				{
					// now render it...
					BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
					BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
					pData+=pFile->bfOffBits;
					VERIFY(SetDIBitsToDevice(pOffScreenDC->m_hDC,offsetx,offsety,pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
						0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS));
				}
				parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);//JW 15Dec98
			}
		}
//		DrawBitmapWTrans((FileNum)filenum,pOffScreenDC);
		drawniconwidth=DrawBitmapWithTransparencies((FileNum)filenum,pOffScreenDC);//JW 15Dec98
	}
	else
	{
		pOffScreenDC = pdc ;									//JW 15Dec98
		DrawBitmap((FileNum)filenum,pOffScreenDC);
	}
    CRect rc = rcBounds;
    CFont* pOldFont;
    TEXTMETRIC tm;
    const CString& strCaption = m_string;

    // Set the ForeColor property color and transparent background mode into the device context
    pOffScreenDC->SetBkMode(TRANSPARENT);

    // Draw the caption using the stock Font and ForeColor properties
	if (m_hWnd)
		pOldFont = pOffScreenDC->SelectObject((CFont*)parent->SendMessage(WM_GETGLOBALFONT,m_FontNum,NULL));
	else
		pOldFont = pOffScreenDC->GetCurrentFont();
    pOffScreenDC->GetTextMetrics(&tm);
	int offset=0;
	if (m_bCloseButton)
	{
		if (m_b[ClosePressed]) 
			pOffScreenDC->DrawIcon(rc.right-ICONWIDTH,rc.top+(rc.Height()/2)-16,m_closeDownIcon);
		else
			pOffScreenDC->DrawIcon(rc.right-ICONWIDTH,rc.top+(rc.Height()/2)-16,m_closeUpIcon);
		offset=ICONWIDTH;
	}
	if (m_bTickButton)
	{
		if (m_b[TickPressed])
			pOffScreenDC->DrawIcon(rc.right-ICONWIDTH-offset,rc.top+(rc.Height()/2)-16,m_tickDownIcon);
		else
			pOffScreenDC->DrawIcon(rc.right-ICONWIDTH-offset,rc.top+(rc.Height()/2)-16,m_tickUpIcon);
		offset+=ICONWIDTH;
	}
	if (m_bHelpButton)
	{
		if (m_b[HelpPressed])
			pOffScreenDC->DrawIcon(rc.right-ICONWIDTH-offset,rc.top+(rc.Height()/2)-16,m_helpDownIcon);
		else
			pOffScreenDC->DrawIcon(rc.right-ICONWIDTH-offset,rc.top+(rc.Height()/2)-16,m_helpUpIcon);
		offset+=ICONWIDTH;
	}
	int newheight=tm.tmHeight;

	if (m_bMovesParent)
	{
		newheight+=4;
	}

	CRect clipbox=rc;
	BOOL bClipped=FALSE;
	pOffScreenDC->SetTextAlign(TA_LEFT | TA_TOP);
	int width=pOffScreenDC->GetTextExtent(strCaption).cx;
	int xoffset=(rc.Width()/2)-(width/2);
	if (m_alignment==1)
		xoffset=3;
	else if (m_alignment==2)
		xoffset=(rc.Width())-(width+3);
	else if (m_alignment==3)
	{	//place to side of icon
		xoffset=drawniconwidth+3;
		width-=xoffset;
	}
	if (strCaption!="" && rc.Width()<width+5 && m_hintString=="")
		m_hintString=strCaption;
	int yoffset=rc.top + (rc.bottom/2)-(newheight/2);
	int fullstopswidth=pOffScreenDC->GetTextExtent("...").cx;
	if (m_bCloseButton || m_bTickButton) // signifies button is a title strip
	{
		if (width && width>rc.Width()-offset-32)
		{
			bClipped=TRUE;
			clipbox=CRect(rc.left,rc.top,rc.right-offset-fullstopswidth,rc.bottom);
		}
		if (xoffset<32 || xoffset+width>rc.Width()-offset-32) 
			xoffset=32;
	}

	if (m_bShowShadow)
	{
	    pOffScreenDC->SetTextColor(TranslateColor(GetShadowColor()));
		int shadowx=GetShadow2XOffset(tm.tmHeight);
		int shadowy=GetShadow2YOffset(tm.tmHeight);
		newheight+=shadowy;
	    pOffScreenDC->ExtTextOut(xoffset+shadowx, yoffset+shadowy,
			ETO_CLIPPED, clipbox, strCaption, strCaption.GetLength(), NULL);
		if (bClipped) 
			pOffScreenDC->TextOut(rc.right-offset-fullstopswidth+shadowx,yoffset+shadowy,"...");
		shadowx=GetShadow1XOffset(tm.tmHeight);
		shadowy=GetShadow1YOffset(tm.tmHeight);
	    pOffScreenDC->ExtTextOut(xoffset+shadowx,yoffset+shadowy,
			ETO_CLIPPED, clipbox, strCaption, strCaption.GetLength(), NULL);
		if (bClipped) 
			pOffScreenDC->TextOut(rc.right-offset-fullstopswidth+shadowx,yoffset+shadowy,"...");
	}
	if (m_b[Pressed]) 
	    pOffScreenDC->SetTextColor(TranslateColor(GetBackColor()));
	else
		pOffScreenDC->SetTextColor(TranslateColor(GetForeColor()));
    pOffScreenDC->ExtTextOut(xoffset, yoffset,
		ETO_CLIPPED, clipbox, strCaption, strCaption.GetLength(), NULL);
	if (bClipped) 
		pOffScreenDC->TextOut(rc.right-offset-fullstopswidth,yoffset,"...");
	pOffScreenDC->SelectObject(pOldFont);
	if (m_hWnd && (m_BitMapWithTransparencies || m_TransparentInnerFileNum)
		&& m_FirstSweep != TRUE) //JW 15/2/98
	{
		//if (m_TransparentInnerFileNum)									//JW 15Dec98 draw transparent fella inside button
		//{
		//	DrawTransparentBitmap(pOffScreenDC,(FileNum)(m_TransparentInnerFileNum)); // just one bitmap now -Woody
		//}
		pdc->BitBlt(0,0,rcBounds.right-rcBounds.left,rcBounds.bottom-rcBounds.top,pOffScreenDC,
						0,0,SRCCOPY); // flips offscreen dc to real dc
		if (pOldBitmap)
			pOffScreenDC->SelectObject(pOldBitmap);
	}    
	m_FirstSweep = FALSE;    
	m_bDrawing=FALSE;
}





/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::OnResetState - Reset control to default state

void CRButtonCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
//	m_picNormal.CreateEmpty();
//	m_picPressed.CreateEmpty();
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl message handlers

CRButtonCtrl::ButtonPos	CRButtonCtrl::GetPressMouseOver(CPoint point)
{
	CRect clientrect;
	GetClientRect(clientrect);
	if (	point.x<clientrect.left
		||	point.x>clientrect.right
		||	point.y<clientrect.top
		||	point.y>clientrect.bottom
		)
		return	NotPressed;

	if (point.x>clientrect.right-ICONWIDTH) // was 32			//JW 09Mar99
	{
		if (m_bCloseButton) 
		{
			return 	ClosePressed;
		}
		else if (m_bTickButton) 
		{
			return	TickPressed;
		}
		else if (m_bHelpButton) 
		{
			return HelpPressed;
		}
	}
	else if (point.x>clientrect.right-ICONWIDTH*2) 				//JW 09Mar99
	{
		if (m_bTickButton && m_bCloseButton)
		{
			return	TickPressed;
		}
		if (m_bHelpButton && (m_bCloseButton || m_bTickButton))
		{
			return HelpPressed;
		}
	}
	else if (point.x>clientrect.right-ICONWIDTH*3) 
	{
		if (m_bHelpButton && m_bTickButton && m_bCloseButton)
		{
			return HelpPressed;
		}
	}
	//not one of the buttons...
	return Pressed;

}

void CRButtonCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	COleControl::OnLButtonDown(nFlags, point);							//JIM 11Oct00
	m_point=point;
	GetParentWndInfo();
	if (m_bDisabled) return;
	m_LButtonDown=TRUE;
	InvalidateControl();
	ButtonPos buttonpresspos=GetPressMouseOver(point);
	m_b[ClosePressed]=FALSE;
	m_b[TickPressed]=FALSE;
	m_b[HelpPressed]=FALSE;
	m_buttonpos=buttonpresspos;
	CRect clientrect;
	GetClientRect(clientrect);
	SetCapture();
	if (buttonpresspos!=Pressed && buttonpresspos!=NotPressed)
	{
		m_b[buttonpresspos]=TRUE;
		return;
	}

	if (m_bMovesParent && buttonpresspos==Pressed)
	{
		CRect rect;
		GetWindowRect(rect);
		CRect parentrect;
		GetParent()->GetClientRect(parentrect);
		GetParent()->ClientToScreen(parentrect);
		point+=rect.TopLeft()-parentrect.TopLeft();
		LPARAM lparam;
		lparam = point.x+(point.y<<16);
//		TRACE0("Sending LBUTTONDOWN\n");
		ReleaseCapture();
		GetParent()->SendMessage(WM_LBUTTONDOWN,nFlags,lparam);
		m_LButtonDown=FALSE;
		return;
	}
}

void CRButtonCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	COleControl::OnLButtonUp(nFlags, point);							//JIM 11Oct00
//DEADCODE DAW 12/04/99 	if (m_bDisabled) return;
	ReleaseCapture();
	InvalidateControl();
	if (phintbox)
	{
		phintbox=(CDialog*)GetParent()->SendMessage(WM_GETHINTBOX,NULL,NULL);
		phintbox->ShowWindow(SW_HIDE);
		phintbox=NULL;
	}
	CRect clientrect;
	GetClientRect(clientrect);

	if (m_LButtonDown && m_buttonpos!=NotPressed && m_buttonpos==GetPressMouseOver(point))
	{
//Button inc:				rbuton\rbuttonc.cpp		XXXX
//	Tick/Help/cross				FIL_SFX_OFFICE_BOOKCLOSE? 1-3			1
//	Toolbar icon				FIL_SFX_OFFICE_BUTTON? 1-3
//	Tickbox						FIL_SFX_OFFICE_TICK						2
//	Dialogue buttons(disable)	FIL_SFX_OFFICE_BUTTON? 1-3			
//	Dialogue buttons(undisblable)
//	Big Dialogue buttons(undisablable)

		m_b[Pressed]=!m_b[Pressed];
		FileNum reqsfx=FIL_SFX_OFFICE_BUTTON1;
		if (m_b[ClosePressed])
			reqsfx=FIL_SFX_OFFICE_BOOKCLOSE1;
		else if (m_b[TickPressed])
			reqsfx=FIL_SFX_OFFICE_DRAWER1;
		else if (m_b[HelpPressed])
			reqsfx=FIL_SFX_OFFICE_BOOKCLOSE3;
		else if (m_bMovesParent)				   //anywhere else on title bar
			reqsfx=FIL_NULL;
		else if (m_NormalFileNum==ICON_TICKBOX1)     //tickbox
			reqsfx=FIL_SFX_OFFICE_TICK;
		else
			if (m_bDisabled)
			{
				if (clientrect.Width()<30)		
					reqsfx=FIL_SFX_OFFICE_BUTTON1;	//small square
				else if (clientrect.Height()>30)
					reqsfx=FIL_SFX_OFFICE_BUTTON3;	//big square
				else 
					reqsfx=FIL_SFX_OFFICE_BUTTON2;	//wide short
			}
			else
			{
				if (clientrect.Width()<30)		
					reqsfx=FIL_SFX_OFFICE_BUTTON1;	//small square
				else if (clientrect.Height()>30)
					reqsfx=FIL_SFX_OFFICE_BUTTON3;	//big square
				else 
					reqsfx=FIL_SFX_OFFICE_BUTTON2;	//wide short
			}

		if (reqsfx)
			GetParent()->SendMessage(WM_PLAYSOUND,reqsfx,NULL);//DAW 06Apr99
	
		if (m_bDisabled) 
			return;										  //DAW 12/04/99

		if (m_b[ClosePressed]) 
		{
			FireCancel();
		}
		else
		if (m_b[TickPressed]) 
		{
			FireOK();
		}
		else
		if (m_b[HelpPressed]) 
		{
			CWnd* oldfocus;
			oldfocus=GetParent()->SetFocus(); // ensures help is for correct dialog
			GetParent()->SendMessage(WM_COMMAND,ID_HELP);
			oldfocus->SetFocus(); // restores the focus to the thing that
								// originally had it (such as an edit box)
		}
		else
			FireClicked();
	}
	m_LButtonDown=FALSE;
	m_b[ClosePressed]=FALSE;
	m_b[TickPressed]=FALSE;
	m_b[HelpPressed]=FALSE;
	m_buttonpos=NotPressed;
}

BOOL CRButtonCtrl::GetMovesParent() 
{
	return m_bMovesParent;
}

void CRButtonCtrl::SetMovesParent(BOOL bNewValue) 
{
	m_bMovesParent=bNewValue;
	SetModifiedFlag();
}

void  CRButtonCtrl::DisplayHint()
{
	SetCapture();
	if (!phintbox)
	{
		phintbox=(CDialog*)GetParent()->SendMessage(WM_GETHINTBOX,NULL,NULL);
		CString realhint=" "+m_hintString+" ";
		phintbox->SetWindowText(realhint);
		CDC* pDC=phintbox->GetDC();
		// select in a font here if you want
		CSize textsize=pDC->GetTextExtent(realhint);
		CRect rect;
		GetWindowRect(rect);
		// a good way of getting the screen resolution
		CRect deskrect;
		GetDesktopWindow()->GetWindowRect(deskrect);
		CPoint hinttopleft=CPoint(rect.left,rect.bottom+5);
		if (hinttopleft.x+textsize.cx>deskrect.right) 
			hinttopleft.x=rect.right-textsize.cx-3;
		if (hinttopleft.y+textsize.cy>deskrect.bottom) 
			hinttopleft.y=rect.top-8-textsize.cy;
		phintbox->MoveWindow(hinttopleft.x,hinttopleft.y,textsize.cx+2,textsize.cy+2);
		phintbox->ShowWindow(SW_SHOW);
		phintbox->ReleaseDC(pDC);
	}
}

void CRButtonCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
//DeadCode JIM 9Aug00 	if (m_LButtonDown&&m_bMovesParent) m_LButtonDown=FALSE;
	GetParentWndInfo();
	
//TempCode JIM 9Aug00 	ButtonPos buttonpresspos=GetPressMouseOver(point);
//TempCode JIM 9Aug00 	if (

	// display hint text if it exists
	if (m_hintString!="")
	{
		CRect rect;
		GetClientRect(rect);
		if (rect.PtInRect(point))
		{  
			bool fasthint=true;
			if (m_string!="")
			{
				if (m_string!=m_hintString)
					fasthint=false;
			}
			else
			{
				CRect rect ;
				GetWindowRect(rect);
				if (rect.Width()<=20 && rect.Height()<=20)
					fasthint=false;

			}

			if (!phintbox && !fasthint)
			{	//Mouse has moved inside so (re)start timer
				if (m_nTimer) KillTimer(m_nTimer);
				m_nTimer=SetTimer(12345,500,NULL);
			}
			else
				DisplayHint();
		}
		else
		{
			ReleaseCapture();
			phintbox=(CDialog*)GetParent()->SendMessage(WM_GETHINTBOX,NULL,NULL);
			phintbox->ShowWindow(SW_HIDE);
			if (m_LButtonDown)
			{
				m_LButtonDown=false;
				InvalidateControl();
			}
			phintbox=NULL;
		}
	}
	else
		if (m_LButtonDown)
		{
			ButtonPos buttonpresspos=GetPressMouseOver(point);
			if (buttonpresspos!=NotPressed && m_buttonpos!=GetPressMouseOver(point))
			{
				buttonpresspos=NotPressed;
				m_LButtonDown=false;
			}


		}
	COleControl::OnMouseMove(nFlags, point);
}

BOOL CRButtonCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	return TRUE;
}

BOOL CRButtonCtrl::OnEraseBkgnd(CDC* pDC) 
{	
	return TRUE;
}

long CRButtonCtrl::GetFontNum() 
{
	if (m_FontNum<0)
		return -m_FontNum;
	else
		return m_FontNum;
}

void CRButtonCtrl::SetFontNum(long nNewValue) 
{
	m_FontNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}
void CRButtonCtrl::SetShowShadow(BOOL bNewValue) 
{
	m_bShowShadow=bNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

OLE_COLOR CRButtonCtrl::GetShadowColor() 
{
	return m_ShadowColor;
}

void CRButtonCtrl::SetShadowColor(OLE_COLOR nNewValue) 
{
	m_ShadowColor=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CRButtonCtrl::OnTextChanged() 
{
	InvalidateControl();
	SetModifiedFlag();	
	COleControl::OnTextChanged();
}

BOOL CRButtonCtrl::GetCloseButton() 
{
	return m_bCloseButton;
}

void CRButtonCtrl::SetCloseButton(BOOL bNewValue) 
{
	m_bCloseButton=bNewValue;
	if (m_bCloseButton) 
	{
		m_closeUpIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_BYEUP));
		m_closeDownIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_BYEDOWN));
	}
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRButtonCtrl::GetTickButton() 
{
	return m_bTickButton;
}

void CRButtonCtrl::SetTickButton(BOOL bNewValue) 
{
	m_bTickButton=bNewValue;
	if (m_bTickButton) 
	{
		m_tickUpIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_TICKUP));
		m_tickDownIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_TICKDOWN));
	}
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRButtonCtrl::GetHelpButton() 
{
	return m_bHelpButton;
}

void CRButtonCtrl::SetHelpButton(BOOL bNewValue) 
{
	m_bHelpButton=bNewValue;
	if (m_bHelpButton) 
	{
		m_helpUpIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_HELPUP));
		m_helpDownIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_HELPDOWN));
	}
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRButtonCtrl::GetShowShadow() 
{
	return m_bShowShadow;
}


BSTR CRButtonCtrl::GetString() 
{
	GetParentWndInfo();
	return m_string.AllocSysString();
}

void CRButtonCtrl::SetString(LPCTSTR lpszNewValue) 
{
	if (m_string==m_hintString)
		m_hintString="";
	GetParentWndInfo();
	m_string=lpszNewValue;
	InvalidateControl();
	SetModifiedFlag();
}


long CRButtonCtrl::GetResourceNumber() 
{
	return m_ResourceNumber&0x00ffffff;
}

void CRButtonCtrl::SetResourceNumber(long nNewValue) 
{
	m_ResourceNumber=nNewValue;
	SetModifiedFlag();
}

long CRButtonCtrl::GetNormalFileNum() 
{
	if (m_hWnd)
		return m_NormalFileNum;
	else
		return m_NormalFileNum&0xffff;
}

void CRButtonCtrl::SetNormalFileNum(long nNewValue) 
{
	if (m_hWnd)
		m_NormalFileNum=nNewValue;
	else
	{
		if (nNewValue!=-1)
			if (m_PressedFileNum==7)
				m_NormalFileNum=nNewValue+0x10000;
			else
				m_NormalFileNum=nNewValue;
	}
	InvalidateControl();
	SetModifiedFlag();
}

long CRButtonCtrl::GetPressedFileNum() 
{
	return m_PressedFileNum;
}

void CRButtonCtrl::SetPressedFileNum(long nNewValue) 
{
	m_PressedFileNum=nNewValue;
	m_PressedFileNumString="";
	InvalidateControl();
	SetModifiedFlag();
}

BSTR CRButtonCtrl::GetNormalFileNumString() 
{
	return m_NormalFileNumString.AllocSysString();
}

void CRButtonCtrl::SetNormalFileNumString(LPCTSTR lpszNewValue) 
{
	m_NormalFileNumString=lpszNewValue;
	m_NormalFileNum=GetFileNum(m_NormalFileNumString);
	InvalidateControl();
	SetModifiedFlag();
}

BSTR CRButtonCtrl::GetPressedFileNumString() 
{
	return m_PressedFileNumString.AllocSysString();
}

void CRButtonCtrl::SetPressedFileNumString(LPCTSTR lpszNewValue) 
{
	m_PressedFileNumString=lpszNewValue;
	m_PressedFileNum=GetFileNum(m_PressedFileNumString);
	if (atoi(m_PressedFileNumString)<6) m_PressedFileNum=atoi(m_PressedFileNumString);
	InvalidateControl();
	SetModifiedFlag();
}

void CRButtonCtrl::OnUpdateCaptionChanged() 
{

	GetParentWndInfo();
	if (InternalGetText().IsEmpty())
	{
		SetString("");
	}
	else
	{
		m_ResourceNumber=GetResourceNumberFromID(InternalGetText());
		if (m_ResourceNumber==-1)
		{
//			this->MessageBox("That was not a valid resource ID","ERROR");
//			SetText(strcat("Invalid ID: ",InternalGetText()));
			SetString("Invalid ID!");
		}
		else
		{
			char output[100];
			if (!ConvertResourceID(InternalGetText(),output))
			{
//				this->MessageBox("That resource ID is not equivalent to anything","ERROR");
				SetString("Invalid ID!");
			}
			else SetString(output);
		}
	

	}
	if (m_hintStringID.IsEmpty())
	{
		SetHintString("");
	}
	else
	{
		m_hintResourceNumber=GetResourceNumberFromID(m_hintStringID);
		if (m_hintResourceNumber==-1)
		{
			SetHintString("Invalid ID!");
		}
		else
		{
			char output[100];
			if (!ConvertResourceID(m_hintStringID,output))
			{
				SetHintString("Invalid ID!");
			}
			else SetHintString(output);
		}
	}
	if (m_PressedFileNumString!="" || m_PressedFileNum!=7)
	{
		SetNormalFileNumString(m_NormalFileNumString);
		SetPressedFileNumString(m_PressedFileNumString);
	}
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRButtonCtrl::GetPressed() 
{
	if (!m_hWnd)
		return	m_alignment&1;
	else
		return m_b[Pressed];
}

void CRButtonCtrl::SetPressed(BOOL bNewValue) 
{
	if (!m_hWnd)
	{
		if (bNewValue)
			m_alignment|=1;
		else
			m_alignment&=~1;
	}
	else
	{
		m_b[Pressed]=bNewValue;
	}
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRButtonCtrl::GetDisabled() 
{
	if (!m_hWnd)
		return	(m_alignment&2)>>1;
	else
		return m_bDisabled;
}

void CRButtonCtrl::SetDisabled(BOOL bNewValue) 
{
	if (!m_hWnd)
	{
		if (bNewValue)
			m_alignment|=2;
		else
			m_alignment&=~2;
	}
	else
		m_bDisabled=bNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CRButtonCtrl::DrawBitmap(FileNum filenum,CDC* pdc)
{
	if (filenum)
		if (m_hWnd)
		{
			BYTE* pData;
			pData = (BYTE*)GetParent()->SendMessage(WM_GETFILE,filenum,NULL);
			if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
			{
				// now render it...
				BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
				BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
				pData+=pFile->bfOffBits;
				SetDIBitsToDevice(pdc->m_hDC,0,0,pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
					0,0/*pInfo->bmiHeader.biHeight*/,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS);
			}
			GetParent()->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
		}
}

BSTR CRButtonCtrl::GetHintString() 
{
	GetParentWndInfo();
	return m_hintString.AllocSysString();
}

void CRButtonCtrl::SetHintString(LPCTSTR lpszNewValue) 
{
	GetParentWndInfo();
	m_hintString=lpszNewValue;
	SetModifiedFlag();
}

BSTR CRButtonCtrl::GetHintStringID() 
{
	GetParentWndInfo();
	return m_hintStringID.AllocSysString();
}

void CRButtonCtrl::SetHintStringID(LPCTSTR lpszNewValue) 
{
	GetParentWndInfo();
	m_hintStringID=lpszNewValue;
	m_hintResourceNumber=GetResourceNumberFromID(m_hintStringID);
	if (m_hintResourceNumber==-1)
	{
		SetHintString("Invalid ID!");
	}
	else
	{
		char output[100];
		if (!ConvertResourceID(m_hintStringID,output))
		{
			SetHintString("Invalid ID!");
		}
		else SetHintString(output);
	}
	SetModifiedFlag();
}

long CRButtonCtrl::GetHintResourceNumber() 
{
	GetParentWndInfo();
	return m_hintResourceNumber;
}

void CRButtonCtrl::SetHintResourceNumber(long nNewValue) 
{
	GetParentWndInfo();
	m_hintResourceNumber=nNewValue;
	SetModifiedFlag();
}

CPoint	IconDescUI::WH()  const
{
//TEMPCODE DAW 02/02/00 	assert(selectedicon!=ICON_NO_ICON);
	return CPoint(iconplace->W*IconPlace::PIXELSPERUNIT,iconplace->H*IconPlace::PIXELSPERUNIT);
}

int CRButtonCtrl::DrawBitmapWithTransparencies(FileNum filenum,CDC* pDC)
{	
	int	rv=0;
	if (m_hWnd && filenum)
	{
		BYTE* pData;
		CWnd* parent;
		parent=GetParent();
		pData = (BYTE*)parent->SendMessage(WM_GETFILE,filenum,NULL);
		if (filenum>=0x10000)
		{
			IconDescUI* icondesc=(IconDescUI*)pData;
			icondesc->MaskIcon(pDC,CPoint(0,0));
			rv= icondesc->WH().x;
		}
		else
		if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
		{
			// now render it...
	//		_asm{int 3}
			BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
			BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
			pData+=pFile->bfOffBits;
			BYTE* pData2=pData;
			BYTE code;
			CRect rect;
			GetClientRect(rect);
		
			//int x=rect.right / 2-pInfo->bmiHeader.biWidth/2; - old code used to draw bitmap in middle - Woody
			int x=rect.left ; 
			int y=rect.top ; //(rect.bottom / 2-pInfo->bmiHeader.biHeight/2) + pressedoffsety ;
			int Width=pInfo->bmiHeader.biWidth;
			if (Width%4) Width+=4-Width%4; // DWord alignment
			int Height=pInfo->bmiHeader.biHeight;
			int x2,y2;
			RGBQUAD color;
			for (y2=Height-1;y2>=0;y2--)
			{
				for ( x2=0 ; x2<Width ; x2++)
				{
					code=*pData2++;
					if (code!=254 && x2<pInfo->bmiHeader.biWidth)
					{
						color=pInfo->bmiColors[code] ;
						pDC->SetPixel(x+x2,y+y2,RGB(color.rgbRed,color.rgbGreen,color.rgbBlue));
					}
				}
			}
			rv=Width;

		}
		parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
	}
	return rv;
}


BOOL CRButtonCtrl::GetTransparency() 
{
	return m_BitMapWithTransparencies ;
}

void CRButtonCtrl::SetTransparency(BOOL bNewValue) 
{
	m_BitMapWithTransparencies = bNewValue ;
	SetModifiedFlag();
}

long CRButtonCtrl::GetTransparentBitMap() 
{
	return m_TransparentInnerFileNum;
}

void CRButtonCtrl::SetTransparentBitMap(long nNewValue) 
{
	// TODO: Add your property handler here
	m_TransparentInnerFileNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CRButtonCtrl::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (m_hintString!="" && phintbox)
	{
		phintbox=(CDialog*)GetParent()->SendMessage(WM_GETHINTBOX,NULL,NULL);
		ReleaseCapture();
		phintbox->ShowWindow(SW_HIDE);
		phintbox=NULL;
	}	
	if (m_nTimer) KillTimer(m_nTimer);
	m_nTimer=0;
	CWnd::OnClose();
}

void CRButtonCtrl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(m_nTimer);
	m_nTimer=0;
	DisplayHint();
	COleControl::OnTimer(nIDEvent);
}

BOOL CRButtonCtrl::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return COleControl::OnHelpInfo(pHelpInfo);
}

void CRButtonCtrl::OnKeyDownEvent(USHORT nChar, USHORT nShiftState) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	COleControl::OnKeyDownEvent(nChar, nShiftState);
}

void CRButtonCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	COleControl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRButtonCtrl::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	if (m_nTimer) KillTimer(m_nTimer);
	m_nTimer=0;
	
	COleControl::OnCaptureChanged(pWnd);
}
