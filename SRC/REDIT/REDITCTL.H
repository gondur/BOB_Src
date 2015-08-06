#if !defined(AFX_REDITCTL_H__499E2BF3_AC32_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_REDITCTL_H__499E2BF3_AC32_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// REditCtl.h : Declaration of the CREditCtrl ActiveX Control class.
#include "bitfield.h"
MAKEFIELD(UByte,0,255);

/////////////////////////////////////////////////////////////////////////////
// CREditCtrl : See REditCtl.cpp for implementation.
class	OneWord
{
public:
	enum	{MAX_CA=16,MAX_CU=15};
	char text[MAX_CA];
	enum	Flags	{	
						W_HYPHENOPT=0x000000,
							W_SPACE=0x000001,W_TAB=0x000002,
							W_HARDLINE=0x000004,
						W_LASTWORD=0x000010,
						W_SOFTLINE=0x000100,W_PASTLIMIT=0x000200,
						W_EDITING=0x010000,W_REDRAW=0x020000
			};
	int	flags;
	CPoint	startat;
	int		pixlen;
	OneWord()
	{text[0]=0;pixlen=0;startat=CPoint(0,0);flags=W_SPACE+W_REDRAW;}
	OneWord(const char* newtext,Flags f=W_SPACE)
		{strncpy(text,newtext,MAX_CU);text[MAX_CU]=0;pixlen=0;startat=CPoint(0,0);flags=f+W_REDRAW;}
	OneWord(const char* newtext,int l,Flags f=W_SPACE)
		{strncpy(text,newtext,l);text[l]=0;pixlen=0;startat=CPoint(0,0);flags=f+W_REDRAW;}
};

class CREditCtrl : public COleControl
{
	DECLARE_DYNCREATE(CREditCtrl)

// Constructor
public:
	CREditCtrl();
	int m_curPoint;
	int m_curPos;
	int m_scrollPoint;
	long m_FontNum;
	UINT m_timerID;
	BOOL m_bShowCursor;
//DeadCode JON 26Jun00 	static BOOL m_bDrawing;
	Bool m_FirstSweep;
//DeadCode JON 26Jun00 	BOOL m_bDisabled;
//	CBitmap* partwork;
//	BITMAP	artworkinfo;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CREditCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual void OnTextChanged();
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CREditCtrl();

	BEGIN_OLEFACTORY(CREditCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CREditCtrl)

	DECLARE_OLETYPELIB(CREditCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CREditCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CREditCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CREditCtrl)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CREditCtrl)
	afx_msg long GetFontNum();
	afx_msg void SetFontNum(long nNewValue);
	afx_msg long GetShadow();
	afx_msg void SetShadow(long nNewValue);
	afx_msg BSTR GetCaption();
	afx_msg void SetCaption(LPCTSTR lpszNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CREditCtrl)
	void FireReturnPressed(LPCTSTR text)
		{FireEvent(eventidReturnPressed,EVENT_PARAM(VTS_BSTR), text);}
	void FireTextChanged(LPCTSTR text)
		{FireEvent(eventidTextChanged,EVENT_PARAM(VTS_I4), text);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()
	CList <OneWord,OneWord&> wordlist;
	POSITION	currentwordpos;
	OneWord*	currentword;
	int	yshift,linedepth,spacewidth,currentchar,tabstep;
	int	maxcharcount,currentwordcharcount,maxlinecount,currlinecount;
	int	GetCurrentWordCharCount();
	int	MakeWordList(const char* string);
	int	RepositionWordList(POSITION p=NULL);
	int CalcWordLen(OneWord&);
	int	GetString(char* string,int max=0x1000);	//4k default max seems reasonable...
	int	CREditCtrl::GetString(CString &string);
	void	SetToWordUnderCursor(CPoint p);
	int	CharNumToPix(OneWord&,int );
	int	PixToCharNum(OneWord&,int );
	void	InvalidateChangedWords();
	void	SetBlockingKeys(const char* keylist);
	enum	{UBA_TAB='\t',UBA_ENTER='\n',UBA_SPACE=' ',UBA_UPDOWN='\v'};
	UByteField	allowed;
// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CREditCtrl)
	dispidFontNum = 1L,
	dispidShadow = 2L,
	dispidCaption = 3L,
	eventidTextChanged = 2L,
	eventidReturnPressed = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDITCTL_H__499E2BF3_AC32_11D1_A1F0_444553540000__INCLUDED)
