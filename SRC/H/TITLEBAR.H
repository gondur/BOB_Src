/*
//{{AFX_INCLUDES()
#include "rbutton.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_TITLEBAR_H__891B54A3_4D5E_11D2_83A5_00004760763D__INCLUDED_)
#define AFX_TITLEBAR_H__891B54A3_4D5E_11D2_83A5_00004760763D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TitleBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TitleBar dialog
enum	SelectTargetMode;
class TitleBar : public CRToolBar
{
	friend class	CMIGView;
// Construction
public:
	TitleBar(CWnd* pParent = NULL);   // standard constructor
	void Redraw(bool setaccel = false);
	enum	{CLOCK, TIMECONTROL,TOTE,
				TASK,COMBATREPORT, ACUNIT, SELTRG

		};
		void OpenTote(UniqueID uid);
	void OpenLWTask();
	void OpenRAFTask();	 
	void OpenTimeControl(int tabnum=0);
 	void OpenCombatReport(int index, bool date);
	void OpenAcUnit(int oldunit, int typestolist, int tab, int am, int unitdisplaylevel); 
	void OpenSelTrg(int squad, int tab, int unitdisplaylevel,SelectTargetMode selecttargetmode); 
	void OpenAcUnitRAF(int unit, bool spitfire,  int tab, int attackmethod); 

	void DialoguesVisible( bool vis);
	void UnPressBtns();
	void UnPressControlBtn();
	void  ClickPause();
	void ClickPlay();


// Dialog Data
	//{{AFX_DATA(TitleBar)
	enum { IDD = IDDT_TITLEBAR };
	CRButton	m_IDC_DATE;
	CRButton	m_IDC_DATETIME;
	CRButton	m_IDC_FASTFORWARD;
	CRButton	m_IDC_CONTROL;
	CRButton	m_IDC_PAUSE;
	CRButton	m_IDC_PLAY;
	//}}AFX_DATA


// Overrides
	void ChildDialClosed(int dialnum,RDialog*,int rv);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TitleBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TitleBar)
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnClickedControl();
	afx_msg void OnClickedDatetime();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClickedPause();
	afx_msg void OnClickedFastforward();
	afx_msg void OnClickedPlay();

	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TITLEBAR_H__891B54A3_4D5E_11D2_83A5_00004760763D__INCLUDED_)
