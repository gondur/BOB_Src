/*
//{{AFX_INCLUDES()
#include "rstatic.h"
#include "rbutton.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_TOOFF_H__37005B82_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_TOOFF_H__37005B82_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TOOff.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TakeOverOffered dialog

class TakeOverOffered : public RowanDialog
{
// Construction
public:
	static RDialog* Make(int packf, int sqf, int latest);
	UINT	maptimer;
	int		countdown;
	TakeOverOffered(int packf, int sqf, int latest, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(TakeOverOffered)
	enum { IDD = IDD_TAKEOVEROFFERED };
	CRStatic	m_IDC_RSTATICTAKEOVEROFFERED;
	CRButton	m_IDC_PAUSE;
	CRButton	m_IDC_NORMALTIME;
	CRButton	m_IDC_CANCEL;
	//}}AFX_DATA
	 int packnum;
	 int sqnum;
	 int latestmsg;
	void	ClickPause();
	void	ClickPlay();
	void OnOK();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TakeOverOffered)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TakeOverOffered)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedPause();
	afx_msg void OnClickedNormaltime();
	afx_msg void OnClickedFly();
	afx_msg void OnClickedCancel();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOFF_H__37005B82_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_)
