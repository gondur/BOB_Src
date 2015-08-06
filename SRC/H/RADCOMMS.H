/*
//{{AFX_INCLUDES()
#include "rlistbox.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_RADCOMMS_H__354A1BA2_8ECF_11D3_8ADB_00A0D21BD395__INCLUDED_)
#define AFX_RADCOMMS_H__354A1BA2_8ECF_11D3_8ADB_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadComms.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RadioComms dialog

class RadioComms : public RowanDialog
{
// Construction
public:
	static RDialog* Make(int msg);

	RadioComms(int msg, CWnd* pParent = NULL);   // standard constructor
	int currmsg;
// Dialog Data
	//{{AFX_DATA(RadioComms)
	enum { IDD = IDD_CHAT };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RadioComms)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RadioComms)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADCOMMS_H__354A1BA2_8ECF_11D3_8ADB_00A0D21BD395__INCLUDED_)
