/*
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rbutton.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_LWROUTEM_H__37005B84_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_LWROUTEM_H__37005B84_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWRouteM.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWRouteMain dialog

class LWRouteMain : public RowanDialog
{
// Construction
public:
	static RDialog* Make(int tab);

	LWRouteMain(int t, CWnd* pParent = NULL);   // standard constructor

	enum WpState	{FIRST, FIRSTTAKEOFF, TAKEOFF, INGRESS, TARGETSTRIKE, TARGETESCORT, EGRESS, LANDING, LAST};
	enum	{MAXWPS = 100};
	UniqueID	WpList[MAXWPS];
	int maxentry;
	int tab;	

// Dialog Data
	//{{AFX_DATA(LWRouteMain)
	enum { IDD = IDD_LWROUTEMAIN };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRButton	m_IDC_RBUTTONINSERT;
	CRButton	m_IDC_RBUTTONDELETE;
	CRButton	m_IDC_RBUTTONCENTRE;
	CRButton	m_IDC_RBUTTONNEWDOGLEG;
	CRButton	m_IDC_RBUTTONAPPLYALT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWRouteMain)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	RefreshList();
	void	RefreshButtons();
	void	RefreshWpDialog();
	int	UpdateWpType(info_waypoint* wp, WpState	wpstate);
	void	FillWpList();
	void RefreshData(int childnum);


	// Generated message map functions
	//{{AFX_MSG(LWRouteMain)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnClickedRbuttonnewdogleg();
	afx_msg void OnClickedRbuttoninsert();
	afx_msg void OnClickedRbuttondelete();
	afx_msg void OnClickedRbuttoncentre();
	afx_msg void OnClickedRbuttonapplyalt();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg	void	OnSelectTab();
	MSG2(OnSelectTab)	{OnSelectTab();return 0;}

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWROUTEM_H__37005B84_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_)
