/*
//{{AFX_INCLUDES()
#include "rcombo.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_SMISSION_H__AB7E6B20_8DF1_11D3_8ADB_00A0D21BD395__INCLUDED_)
#define AFX_SMISSION_H__AB7E6B20_8DF1_11D3_8ADB_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SMission.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SMissionConfigure dialog

class SMissionConfigure : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	SMissionConfigure(CWnd* pParent = NULL);   // standard constructor
	void PreDestroyPanel();

// Dialog Data
	//{{AFX_DATA(SMissionConfigure)
	enum { IDD = IDD_SMISSION };
	CRCombo	m_IDC_CBO_LWSKILL;
	CRCombo	m_IDC_CBO_RAFSKILL;
	CRCombo	m_IDC_CBO_AUTOVECTOR;
	CRCombo	m_IDC_CBO_LWTACTICS;
	CRCombo	m_IDC_CBO_MAPPLOTTING;
	CRCombo	m_IDC_CBO_LWINTELL;
	CRCombo	m_IDC_CBO_FLYOPTION;
	CRCombo	m_IDC_CBO_RAFTACTICS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SMissionConfigure)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SMissionConfigure)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMISSION_H__AB7E6B20_8DF1_11D3_8ADB_00A0D21BD395__INCLUDED_)
