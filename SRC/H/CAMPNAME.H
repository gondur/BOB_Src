/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "redit.h"
#include "rbutton.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_CAMPNAME_H__9D1016E0_599A_11D4_ADE7_0040052179B6__INCLUDED_)
#define AFX_CAMPNAME_H__9D1016E0_599A_11D4_ADE7_0040052179B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CampName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CampaignEnterName dialog

class CampaignEnterName : public RowanDialog
{
// Construction
public:
	static RDialog* Make(int );

	CampaignEnterName(int whichcamp,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CampaignEnterName)
	enum { IDD = IDD_CAMPNAME };
	CREdit	m_IDC_NAME;
	CRButton	m_IDC_PERIOD;
	CRButton	m_IDC_PERIOD2;
	CRButton	m_IDC_ROLE;
	CRButton	m_IDC_SIDE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CampaignEnterName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int whichcamp;
	// Generated message map functions
	//{{AFX_MSG(CampaignEnterName)
	afx_msg void OnClickedRole();
	afx_msg void OnClickedPeriod2();
	afx_msg void OnClickedPeriod();
	afx_msg void OnTextChangedName(LPTSTR text);
	afx_msg void OnClickedSide();
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMPNAME_H__9D1016E0_599A_11D4_ADE7_0040052179B6__INCLUDED_)
