#if !defined(AFX_MAPDLG_H__DED33C01_22B7_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_MAPDLG_H__DED33C01_22B7_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MapDlg.h : header file
//
#ifndef	NDEBUG
struct	DebugLineStats
{
	int	debuglineRGB[8];
	int	lastline,lastbox;

	struct	DebugBoxMem
	{
		SWord	sx,ex;
		SLong	sy:12,ey:12,
				linenum:3,
				spare:5;
	}
	boxmem[300+1];
	void	Set(CRect& rect)
	{
		boxmem[lastbox].sx=rect.left;boxmem[lastbox].ex=rect.right;
		boxmem[lastbox].sy=rect.top;boxmem[lastbox].ey=rect.bottom;
		boxmem[lastbox].linenum=lastline;
		if (lastbox<300)	lastbox++;
	}
};
extern	DebugLineStats	debugboxmem;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapDlg dialog
enum	IconsUI;
class CMapDlg : public CDialog
{
// Construction
public:
	UINT	maptimer;
//DeadCode JIM 9Nov00 	enum	{MAX_SAGINVALIDATES=256};
//DeadCode JIM 8Nov00 	Coords3D	itemrefreshrequests[MAX_SAGINVALIDATES];
	bool	InvalidateAnotherItem();
	void InvalidateLine(CPoint point1,CPoint point2);
	void InvalidateMovedLine(UniqueID thiswp,UniqueID nextwp,BOOL japanwp=FALSE);
	void InvalidateLine(UniqueID thiswp,UniqueID nextwp);
	void InvalidateMobiles(bool newposition,bool clockingrefresh);
	void InvalidateRoutes(UniqueID onlythrough=UID_NULL); 
	void	RefreshTargettingWaypoints(UniqueID trg);
	void	InvalidateDraggingRoutes(UniqueID through);
	int		FindMapItem(CPoint point);
	bool	OverMapItem(UniqueID i,CPoint point);
	bool	InsideIcon(IconsUI i,ItemBasePtr p,CPoint mousexy);
	bool	InsideIconExtra(IconsUI i,ItemBasePtr p,CPoint mousexy);
	void	InvalidateIconText(CDC* pDC,int px,int py,UniqueID u);
	void	InvalidateDragIcon(int ox,int oy,int px,int py,IconsUI i);
	void	InvalidateIcon(ItemBasePtr p);
	void	InvalidateIcon(int px,int py,IconsUI i);
	void	InvalidateIconExtra(int px,int py,ItemBasePtr p,IconsUI i);
	void	Invalidate()	{CDialog::Invalidate();}
	CMIGView*	m_view;
	int m_buttonid;
	int m_hintid;
	CPoint m_point;
	CPoint m_oldpoint;
	BOOL m_LButtonDown;
	BOOL m_bDragging;
//	BOOL Create( CWnd* pParentWnd);
	CMapDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMapDlg)
	enum { IDD = IDD_MAP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	void	ResetIcon(UniqueID wpuid);
	void	RedrawIcon(int oldbuttonid);
	RDialog*	TargetSelectSink;
	int			TargetSelectMode;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	virtual LRESULT DefWindowProcA(UINT message, WPARAM wParam, LPARAM lParam);

// Implementation
	bool	AllowDragItem(int buttonid);
	void	OnClickItem(int buttonid);
	void	OnFailClickItem(int m_buttonid);
	void	OnDragItem(int buttonid);
protected:

	// Generated message map functions
	//{{AFX_MSG(CMapDlg)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPDLG_H__DED33C01_22B7_11D1_A1F0_444553540000__INCLUDED_)
