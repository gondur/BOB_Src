/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rstatic.h"
#include "rbutton.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_INTELLMSG_H__59BE6900_9C3F_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_INTELLMSG_H__59BE6900_9C3F_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IntellMsg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// IntellMessages dialog

class IntellMessages : public RowanDialog
{
// Construction
public:
	static RDialog* Make(int msg);

	IntellMessages(int msg, CWnd* pParent = NULL);   // standard constructor
	int currmsg, maxmsg, currmsgindex;
	enum {MAXMESSAGES = 250};

	UWord msglist[MAXMESSAGES];
// Dialog Data
	//{{AFX_DATA(IntellMessages)
	enum { IDD = IDD_INTELLMSG };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRStatic	m_IDC_RSTATICCTRL1;
	CRButton	m_IDC_RBUTTONDETAILS;
	CRStatic	m_IDC_RSTATICBODY;
	CRButton	m_IDC_INTEL_ENGAGEMENT;
	CRButton	m_IDC_INTEL_FLIGHT;
	CRButton	m_IDC_INTEL_MANAGEMENT;
	CRButton	m_IDC_INTEL_SPOTTING;
	CRButton	m_IDC_INTEL_TARGETSTATUS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IntellMessages)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Refresh();
	void FillList();
	void RefreshHilight();
	void RefreshData(int childnum);
	

	// Generated message map functions
	//{{AFX_MSG(IntellMessages)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnClickedIntelEngagement();
	afx_msg void OnClickedIntelFlight();
	afx_msg void OnClickedIntelManagement();
	afx_msg void OnClickedIntelSpotting();
	afx_msg void OnClickedIntelTargetstatus();
	afx_msg void OnClickedRbuttondetails();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTELLMSG_H__59BE6900_9C3F_11D3_8ADC_00A0D21BD395__INCLUDED_)
