#if !defined(AFX_RLISTBOXCTL_H__90B5EDB4_666F_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RLISTBOXCTL_H__90B5EDB4_666F_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RListBoxCtl.h : Declaration of the CRListBoxCtrl ActiveX Control class.
#include <afxtempl.h>
#include "dosdefs.h"
#include "files.g"

/////////////////////////////////////////////////////////////////////////////
// CRListBoxCtrl : See RListBoxCtl.cpp for implementation.

class CRListBoxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRListBoxCtrl)

// Constructor
public:
	CRListBoxCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRListBoxCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
private:
//Code JW 04Nov98 Woody variables
	FileNum OldArt;
	int		textheight ;
	Bool	m_FirstSweep;
	Bool	m_isIcon;
	Bool	m_maxscrl;											//AMM 10Jul99
	BOOL	m_HorizontalOption;
	short	m_NoColumnsToRepeat ;
	short	m_NoRepeats ;
	short   m_Lines ;
	short	m_ScrlBarOffset ;
	void 	AddSetOfColumns() ;
	short	colwidths[10];
	long		colalignsicons[10];
	int		mousecol,mouserow;bool	mouseneedshint;
	CDialog* phintbox;
protected:
	~CRListBoxCtrl();

	BEGIN_OLEFACTORY(CRListBoxCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CRListBoxCtrl)

	DECLARE_OLETYPELIB(CRListBoxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRListBoxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRListBoxCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CRListBoxCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnScrollVert(long nPos);
	afx_msg void OnScrollHorz(long nPos);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRListBoxCtrl)
	afx_msg BOOL GetIsStripey();
	afx_msg void SetIsStripey(BOOL bNewValue);
	afx_msg OLE_COLOR GetStripeColor();
	afx_msg void SetStripeColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetSelectColor();
	afx_msg void SetSelectColor(OLE_COLOR nNewValue);
	afx_msg BOOL GetLines();
	afx_msg void SetLines(BOOL bNewValue);
	afx_msg OLE_COLOR GetLineColor();
	afx_msg void SetLineColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetDarkStripeColor();
	afx_msg void SetDarkStripeColor(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetDarkBackColor();
	afx_msg void SetDarkBackColor(OLE_COLOR nNewValue);
	afx_msg BOOL GetLockLeftColumn();
	afx_msg void SetLockLeftColumn(BOOL bNewValue);
	afx_msg BOOL GetLockTopRow();
	afx_msg void SetLockTopRow(BOOL bNewValue);
	afx_msg OLE_COLOR GetLockColor();
	afx_msg void SetLockColor(OLE_COLOR nNewValue);
	afx_msg BOOL GetDragAndDrop();
	afx_msg void SetDragAndDrop(BOOL bNewValue);
	afx_msg long GetFontNum();
	afx_msg void SetFontNum(long nNewValue);
	afx_msg BOOL GetBlackboard();
	afx_msg void SetBlackboard(BOOL bNewValue);
	afx_msg long GetFontNum2();
	afx_msg void SetFontNum2(long nNewValue);
	afx_msg BOOL GetLines2();
	afx_msg void SetLines2(BOOL bNewValue);
	afx_msg OLE_COLOR GetHeaderColor();
	afx_msg void SetHeaderColor(OLE_COLOR nNewValue);
	afx_msg BOOL GetSelectWholeRows();
	afx_msg void SetSelectWholeRows(BOOL bNewValue);
	afx_msg long GetFontPtr();
	afx_msg void SetFontPtr(long nNewValue);
	afx_msg long GetParentPointer();
	afx_msg void SetParentPointer(long nNewValue);
	afx_msg long GetHilightRow();
	afx_msg void SetHilightRow(long nNewValue);
	afx_msg long GetHilightCol();
	afx_msg void SetHilightCol(long nNewValue);
	afx_msg BOOL GetBorder();
	afx_msg void SetBorder(BOOL bNewValue);
	afx_msg BOOL GetCentred();
	afx_msg void SetCentred(BOOL bNewValue);
	afx_msg long GetHorzSeperation();
	afx_msg void SetHorzSeperation(long nNewValue);
	afx_msg long GetVertSeperation();
	afx_msg void SetVertSeperation(long nNewValue);
	afx_msg BOOL GetToggleResizableColumns();
	afx_msg void SetToggleResizableColumns(BOOL bNewValue);
	afx_msg short GetScrlBarOffset();
	afx_msg void SetScrlBarOffset(short nNewValue);
	afx_msg long GetA0();
	afx_msg void SetA0(long nNewValue);
	afx_msg long GetA1();
	afx_msg void SetA1(long nNewValue);
	afx_msg long GetA2();
	afx_msg void SetA2(long nNewValue);
	afx_msg long GetA3();
	afx_msg void SetA3(long nNewValue);
	afx_msg long GetA4();
	afx_msg void SetA4(long nNewValue);
	afx_msg long GetA5();
	afx_msg void SetA5(long nNewValue);
	afx_msg long GetA6();
	afx_msg void SetA6(long nNewValue);
	afx_msg long GetA7();
	afx_msg void SetA7(long nNewValue);
	afx_msg long GetA8();
	afx_msg void SetA8(long nNewValue);
	afx_msg long GetC0();
	afx_msg void SetC0(long nNewValue);
	afx_msg long GetC1();
	afx_msg void SetC1(long nNewValue);
	afx_msg long GetC2();
	afx_msg void SetC2(long nNewValue);
	afx_msg long GetC3();
	afx_msg void SetC3(long nNewValue);
	afx_msg long GetC4();
	afx_msg void SetC4(long nNewValue);
	afx_msg long GetC5();
	afx_msg void SetC5(long nNewValue);
	afx_msg long GetC6();
	afx_msg void SetC6(long nNewValue);
	afx_msg long GetC7();
	afx_msg void SetC7(long nNewValue);
	afx_msg long GetC8();
	afx_msg void SetC8(long nNewValue);
	afx_msg long GetI0();
	afx_msg void SetI0(long nNewValue);
	afx_msg long GetI1();
	afx_msg void SetI1(long nNewValue);
	afx_msg long GetI2();
	afx_msg void SetI2(long nNewValue);
	afx_msg long GetI3();
	afx_msg void SetI3(long nNewValue);
	afx_msg long GetI4();
	afx_msg void SetI4(long nNewValue);
	afx_msg long GetI5();
	afx_msg void SetI5(long nNewValue);
	afx_msg long GetI6();
	afx_msg void SetI6(long nNewValue);
	afx_msg long GetI7();
	afx_msg void SetI7(long nNewValue);
	afx_msg long GetI8();
	afx_msg void SetI8(long nNewValue);
	afx_msg OLE_COLOR GetShadowSelectColour();
	afx_msg void SetShadowSelectColour(OLE_COLOR nNewValue);
	afx_msg OLE_COLOR GetShadowLineColor();
	afx_msg void SetShadowLineColor(OLE_COLOR nNewValue);
	afx_msg BOOL GetDrawBackgGound();
	afx_msg void SetDrawBackgGound(BOOL bNewValue);
	afx_msg short GetCount();
	afx_msg void AddString(LPCTSTR text,short index);
	afx_msg void DeleteString(short row,short column);
	afx_msg void Clear();
	afx_msg void AddColumn(long width);
	afx_msg void SetColumnWidth(short index, long width);
	afx_msg void AddPlayerNum(long playerNum);
	afx_msg long DeletePlayerNum(short row);
	afx_msg long ReplacePlayerNum(long playerNum, short row);
	afx_msg void ReplaceString(LPCTSTR text, short row, short col);
	afx_msg long GetString(short row, short col);
	afx_msg long GetPlayerNum(short row);
	afx_msg short GetRowFromY(long y);
	afx_msg void UpdateScrollBar();
	afx_msg long GetListHeight();
	afx_msg void ResizeToFit();
	afx_msg void Shrink();
	afx_msg long GetColumnWidth(long col);
	afx_msg void SetNumberOfRows(long rows);
	afx_msg void InsertRow(long row);
	afx_msg void DeleteRow(long row);
	afx_msg BOOL SelectRecentlyFired();
	afx_msg void AddIconColumn(long width);
	afx_msg void AddIcon(long filenum, short index);
	afx_msg void SetHorizontalOption(short columns);
	afx_msg short GetColFromX(long x);
	afx_msg long GetRowColPlayerNum(long row, long col);
	afx_msg void SetColumnRightAligned(long index, BOOL bNewVal);
	afx_msg void SetRowColour(long row, long RGBcolour);
	afx_msg void SetIcon(long filenum, short row, short column);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CRListBoxCtrl)
	void FireSelect(long row, long column)
		{FireEvent(eventidSelect,EVENT_PARAM(VTS_I4  VTS_I4), row, column);}
	void FireDoubleSelect(long row, long column)
		{FireEvent(eventidDoubleSelect,EVENT_PARAM(VTS_I4  VTS_I4), row, column);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	void DrawClippedBitmap(CDC* pDC,FileNum filenum,int x,int y,CRect cliprect);
bool	ExtTextOut(CDC* pdc,
				   bool shadow,int fontheightforshadow,COLORREF fontcolour,COLORREF shadowcolour,
				   int x,int y,int alignoff,const CRect* cliprect,char* text);
	int m_vert;
	int m_horz;
	long m_horzSeperation;
	long m_vertSeperation;
	BOOL m_bSelectRecentlyFired;
	BOOL m_border;
	HWND m_pParenthWnd;
	FileNum m_artnum;
	CFont* m_pFontPtr;
	static BOOL m_bDrawing;
	long m_offsets;
	BOOL m_bSelectWholeRows;
	OLE_COLOR m_headerColor;
	BOOL m_bBlackboard;
	long m_FontNum2;
	long m_FontNum;
	UINT CF_PLAYER;
	int m_iSeperator;
	BOOL m_bDragAndDrop;
	int m_iOldSize;
	CPoint m_OldPoint;
//	BOOL m_bBothScrollBars;
	OLE_COLOR m_lockColor;
	BOOL m_bLockTopRow;
	BOOL m_bLockLeftColumn;
	BOOL m_LButtonDown;
	BOOL m_lines;
	BOOL m_bLines2;
	long m_lVertScrollPos;
	long m_lHorzScrollPos;
	BOOL m_bInit;
	BOOL m_bCentred;
	CRScrlBar* m_pVertScrollBar;
	CRScrlBar* m_pHorzScrollBar;
	int m_iRowSel;
	int m_iColSel;
	int m_iOldRowSel;
	int m_iOldColSel;
	BOOL m_toggleresizeablecolumns;
	BOOL m_bIsStripey;
	OLE_COLOR m_lineColor;
	OLE_COLOR m_ShadowlineColor;
	OLE_COLOR m_stripeColor;
	OLE_COLOR m_selectColor;
	OLE_COLOR m_ShadowselectColor;
	OLE_COLOR m_darkStripeColor;
	OLE_COLOR m_darkBackColor;
//	CList<char*,char*> m_list;
	CList<CList<char*,char*>*,CList<char*,char*>*> m_list;
	CList<long,long> m_sizeList;
	CList<long,long> m_playerList;
	CList<BOOL,BOOL> m_isPictureList;
	CList<BOOL,BOOL> m_isRightAlignedList;
	CList<COLORREF,COLORREF> m_rowColourList;
	enum {
	//{{AFX_DISP_ID(CRListBoxCtrl)
	dispidIsStripey = 1L,
	dispidStripeColor = 2L,
	dispidSelectColor = 3L,
	dispidLines = 4L,
	dispidLineColor = 5L,
	dispidDarkStripeColor = 6L,
	dispidDarkBackColor = 7L,
	dispidLockLeftColumn = 8L,
	dispidLockTopRow = 9L,
	dispidLockColor = 10L,
	dispidDragAndDrop = 11L,
	dispidFontNum = 12L,
	dispidBlackboard = 13L,
	dispidFontNum2 = 14L,
	dispidLines2 = 15L,
	dispidHeaderColor = 16L,
	dispidSelectWholeRows = 17L,
	dispidFontPtr = 18L,
	dispidParentPointer = 19L,
	dispidHilightRow = 20L,
	dispidHilightCol = 21L,
	dispidBorder = 22L,
	dispidCentred = 23L,
	dispidHorzSeperation = 24L,
	dispidVertSeperation = 25L,
	dispidToggleResizableColumns = 26L,
	dispidScrlBarOffset = 27L,
	dispidA0 = 28L,
	dispidA1 = 29L,
	dispidA2 = 30L,
	dispidA3 = 31L,
	dispidA4 = 32L,
	dispidA5 = 33L,
	dispidA6 = 34L,
	dispidA7 = 35L,
	dispidA8 = 36L,
	dispidC0 = 37L,
	dispidC1 = 38L,
	dispidC2 = 39L,
	dispidC3 = 40L,
	dispidC4 = 41L,
	dispidC5 = 42L,
	dispidC6 = 43L,
	dispidC7 = 44L,
	dispidC8 = 45L,
	dispidI0 = 46L,
	dispidI1 = 47L,
	dispidI2 = 48L,
	dispidI3 = 49L,
	dispidI4 = 50L,
	dispidI5 = 51L,
	dispidI6 = 52L,
	dispidI7 = 53L,
	dispidI8 = 54L,
	dispidGetCount				= 55L,
	dispidAddString				= 56L,
	dispidDeleteString			= 57L,
	dispidClear					= 58L,
	dispidAddColumn				= 59L,
	dispidSetColumnWidth		= 60L,
	dispidAddPlayerNum			= 61L,
	dispidDeletePlayerNum		= 62L,
	dispidReplacePlayerNum		= 63L,
	dispidReplaceString			= 64L,
	dispidGetString				= 65L,
	dispidGetPlayerNum			= 66L,
	dispidGetRowFromY			= 67L,
	dispidUpdateScrollBar		= 68L,
	dispidGetListHeight			= 69L,
	dispidResizeToFit			= 70L,
	dispidGetColumnWidth		= 71L,
	dispidSetNumberOfRows		= 72L,
	dispidInsertRow				= 73L,
	dispidDeleteRow				= 74L,
	dispidShrink				= 75L,
	dispidSelectRecentlyFired	= 76L,
	dispidAddIconColumn			= 77L,
	dispidAddIcon				= 78L,
	dispidSetHorizontalOption	= 79L,
	dispidGetColFromX			= 80L,
	dispidGetRowColPlayerNum	= 81L,
	dispidSetColumnRightAligned	= 82L,
	dispidSetRowColour			= 83L,
	dispidSetIcon				= 84L,
	eventidSelect = 1L,
	eventidDoubleSelect = 2L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RLISTBOXCTL_H__90B5EDB4_666F_11D1_A1F0_444553540000__INCLUDED)
