/*
//{{AFX_INCLUDES()
#include "rstatic.h"
#include "rbutton.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_AFDETL_H__27AE24C2_8E23_11D3_8ADB_00A0D21BD395__INCLUDED_)
#define AFX_AFDETL_H__27AE24C2_8E23_11D3_8ADB_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AfDetl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AirfieldDetails dialog

class AirfieldDetails : public RowanDialog
{
// Construction
public:
	static RDialog* Make(UniqueID  uid);

	AirfieldDetails(UniqueID  uid, CWnd* pParent = NULL);   // standard constructor
	UniqueID afuid;
// Dialog Data
	//{{AFX_DATA(AirfieldDetails)
	enum { IDD = IDD_AIRFIELD_DETAILS };
	CRStatic	m_IDC_RSTATICFIELD;
	CRStatic	m_IDC_RSTATICHURRSQUAD;
	CRStatic	m_IDC_RSTATICMAXSQUAD;
	CRStatic	m_IDC_RSTATICREFUEL;
	CRStatic	m_IDC_RSTATICREPAIR;
	CRStatic	m_IDC_RSTATICSECTOROPS;
	CRStatic	m_IDC_RSTATICSPITSQUAD;
	CRStatic	m_IDC_DOSSNOTES;
	CRStatic	m_IDC_RSTATICSTAFF;
	CRButton	m_IDC_RBUTTONCENTRE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AirfieldDetails)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AirfieldDetails)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedAuthorise();
	afx_msg void OnClickedRbuttoncentre();
	afx_msg void OnClickedPhoto();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AFDETL_H__27AE24C2_8E23_11D3_8ADB_00A0D21BD395__INCLUDED_)
