/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rbutton.h"
#include "redit.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_SIDESEL_H__1E804161_91E0_11D3_8ADB_00A0D21BD395__INCLUDED_)
#define AFX_SIDESEL_H__1E804161_91E0_11D3_8ADB_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SideSel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SideSelect dialog

class SideSelect : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	SideSelect(int screen,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SideSelect)
	enum { IDD = IDD_SIDESELECT };
	CRButton	m_IDC_LUFTWAFFE;
	CRButton	m_IDC_RAF;
	CRButton	m_IDC_CANCEL;
	//}}AFX_DATA
	int scrn;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SideSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SideSelect)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedLuftwaffe();
	afx_msg void OnClickedRaf();
	afx_msg void OnClickedCancel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIDESEL_H__1E804161_91E0_11D3_8ADB_00A0D21BD395__INCLUDED_)
