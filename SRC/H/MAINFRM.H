#if !defined(AFX_MAINFRM_H__DB03429D_1B07_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_MAINFRM_H__DB03429D_1B07_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//DEADCODE DAW 24/11/99 #include "RDlgBar.h"
#include "SysBox.h"	// Added by ClassView
//DEADCODE DAW 24/11/99 #include "ButonBar.h"
#include <afxtempl.h>
//#include "rtoolbar.h"
#include "scalebar.h"
#include "maintbar.h"
#include "mapfltrs.h"
#include "msctlbr.h"
//DEADCODE DAW 24/11/99 #include "dbrftlbr.h"
#include "statbar.h"
#include "teletype.h"

class CMIGView;
class CMIGDoc;


class CMainFrame : public CFrameWnd
{
//protected: // create from serialization only

// Attributes
public:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
	bool	havedrawn,havesafe;
	bool	bAppMinimized;
	int		disablehelp;	//1=disabletabs 2=disablepanels
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void	InitialiseSafe();
	void	PositionSysBox(); 
	bool	MakeToolMenu(CPoint point,int helpdialindex);
	void ShowToolbars(bool firsttime);
	void HideToolbars();
	BOOL m_bHideToolbars;
//DeadCode AMM 7Aug00 	Bool m_oldindebrief;
	typedef CList<CRToolBar*,CRToolBar*> ToolBarList;
	ToolBarList m_left;
	ToolBarList m_top;
	ToolBarList m_right;
	ToolBarList m_bottom;
	CRect m_borderRect;
#ifndef	BOB_DEMO_VER
	CMapFilters m_toolbar1;
	CMainToolbar m_toolbar2;
	CMiscToolbar m_toolbar3;
	CScaleBar m_toolbar4;
	TitleBar	m_titlebar;
	TeleType	m_reportbar;
	TeleType	m_commsbar;
	StatusBar	m_statusbar;
//	CDebriefToolbar m_toolbar5;
	CRToolBar	m_spacebar;


	static	CRToolBar*	toolbars[];
	void	CloseToolChildren(RDialog* skipthis=NULL);
	void	UpdateToolbars(bool	hideall);

//DeadCode RJS 27Jul00 	void CMainFrame::WinHelp(DWORD dwData, UINT nCmd);

	CSystemBox* m_wndSystemBox;
#endif

	void CMainFrame::WinHelp(DWORD dwData, UINT nCmd);

	int m_doIExist;
//DEADCODE DAW 07/05/99 	CResizableDlgBar m_wndDialogBar;
//DeadCode RDH 11Jul99 	CSystemBox* m_wndSystemBox;
	virtual ~CMainFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	void	Initialise();
//	CStatusBar  m_wndStatusBar;
//	CButtonBar    m_wndToolBar;

// Generated message map functions
protected:
public:
	void	ExitCampaign();												//RJS 1Sep00
	void	RePositionLayout(int dx,int dy);
	void	RePositionLayout(int dx,int dy,ToolBarList* toollist);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnHelp();
	afx_msg void OnHelpFinder();
	afx_msg void OnContextHelp();
	afx_msg void OnSize(UINT,int,int);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg void OnDevModeChange(LPTSTR lpDeviceName);
	//}}AFX_MSG
	afx_msg void OnGoBig();
	afx_msg void OnBye();
	afx_msg void OnGoNormal();
	afx_msg void OnGoSmall();
//TEMPCODE JIM 04/04/00 	void ShowToolbars(bool firsttime);
//TEMPCODE JIM 04/04/00 	void HideToolbars();
//TEMPCODE JIM 04/04/00 	RDialog*	m_wndSystemBox;

	afx_msg LRESULT OnCommandHelp(WPARAM, LPARAM lParam);
	MSG2_2(OnCommandHelp);
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
#ifndef	BOB_DEMO_VER
#ifdef	MAINTBAR_INCLUDED
inline CMainToolbar&	MainToolBar()
{
	CMainFrame* pmainwnd=(CMainFrame*)AfxGetMainWnd();
	return pmainwnd->m_toolbar2;
}
//DEADCODE RDH 08/11/99 inline CDebriefToolbar&	DebriefToolBar()
//DEADCODE RDH 08/11/99 {
//DEADCODE RDH 08/11/99 	CMainFrame* pmainwnd=(CMainFrame*)AfxGetMainWnd();
//DEADCODE RDH 08/11/99 	return pmainwnd->m_toolbar5;
//DEADCODE RDH 08/11/99 }
inline	CMiscToolbar& MiscToolBar()
{
	CMainFrame* pmainwnd=(CMainFrame*)AfxGetMainWnd();
	return pmainwnd->m_toolbar3;
}
inline	TitleBar& TitleBarPtr()
{
	CMainFrame* pmainwnd=(CMainFrame*)AfxGetMainWnd();
	return pmainwnd->m_titlebar;
}

#endif
#endif
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__DB03429D_1B07_11D1_A1F0_444553540000__INCLUDED_)


