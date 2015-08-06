/*
//{{AFX_INCLUDES()

//}}AFX_INCLUDES
*/
#if !defined(AFX_RTOOLBAR_H__95882EC2_D9F5_11D1_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_RTOOLBAR_H__95882EC2_D9F5_11D1_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CRToolBar.h : header file
//
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CRToolBar dialog
class CMainFrame;
class CMIGView;

class CRToolBar : public CDialog
{
	DECLARE_DYNAMIC(CRToolBar);
// Construction
	enum	{m_scalingfactor=1};
public:
	static int	toptoprow,lefttoprow,righttoprow,bottoprow;
	int*	toprow;
	enum	{TOOBAR_THICKNESS=80,TOPBAR_THICKNESS=10,SIDEBAR_THICKNESS=50,SCROLLBAR_THICKNESS=16,BARTHICK_MODULO=10};
	void Float(); // floats a toolbar
	void Replace(CRToolBar* newtoolbar); // replaces this toolbar with newtoolbar
	int		ReAttach(bool	enable,bool resort=true);
	int		ReAttach(bool	enable,bool resort,int m_index);
	DialogLinks	dialoglinks;
	int		LogChild(RDialog*);	//new system for managing intersheet comms
	bool	LogChild(int,RDialog*);	//as Dallas never implemented one!
	int		LoggedChild();
	RDialog*	LoggedChild(int);
	bool	CloseLoggedChild(int);	  //true means still open!!!
	void	CloseLoggedChildren(RDialog* skipthis=NULL);
	void	RefreshChild(int rv);
	virtual void ChildDialClosed(int dialnum,RDialog*,int rv);
	virtual void RefreshData(int childnum);
	void	GlobalRefreshData();
	void	OnOK();
	void	OnCancel();
	void	MakeChildrenVisible(bool);
	bool	hidedrawing;
	void Init();
	int GetDockSide(CPoint point,bool allowsideifgripper=false);
	void Init(CMainFrame* parent,int minlength,int length,int width,UINT nDockBarID = AFX_IDW_DOCKBAR_TOP,int priority=0,UINT dockablesides=CBRS_ALIGN_ANY+CBRS_GRIPPER);
	// the length is always the longer of the two
	// keep the width the same in all of the toolbars
	// a priority of 0 means the toolbar will not resize
	virtual void SetHorzAlign(BOOL bHorzAlign);
	CRToolBar(CWnd* pParent = NULL);   // standard constructor
	~CRToolBar()	{DialExitFix();}
	void	DialExitFix(int rv=0);
	BOOL m_bHorzAlign;
	BOOL m_init;
	UINT m_dockablesides;
	int m_priority;
	int m_align;
	int m_length;
	int m_currentlength;
	int m_minlength;
	int m_width;
	int m_row; // what row we are on if docked
	CMainFrame* m_pFrame;
	CMIGView* m_pView;
	int m_LButtonDown;	//0=not down;1=dragging ctool;2=dragging app
	CPoint m_lastdown;
	fileblock* m_pfileblock;
	CList<CRToolBar*,CRToolBar*>* m_pList;
	int m_index;

	
// Dialog Data
	//{{AFX_DATA(CRToolBar)
	enum { IDD = IDDT_SPACEBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	void	DDX_Control(CDataExchange* pDX,int	dialid,CWnd&	m_dial);
	BOOL Create(UINT nIDTemplate, CWnd* pParentWnd = NULL);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRToolBar)
	public:
	virtual BOOL DestroyWindow();
	virtual int DoModal();
	virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	virtual BOOL OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual void OnFinalRelease();
	virtual void OnSetFont(CFont* pFont);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void Serialize(CArchive& ar);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRToolBar)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnCancelMode();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnClose();
	afx_msg int OnCharToItem(UINT nChar, CListBox* pListBox, UINT nIndex);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	#include  "rdialmsg.h"
	DECLARE_MESSAGE_MAP()
private:
	CRToolBar* FindToolBar(CPoint point); // this is a slightly dodgy function so dont call it
											// unless you KNOW a docked toolbar is inside point
};
#endif
