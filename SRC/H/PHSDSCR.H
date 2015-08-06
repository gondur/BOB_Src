/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rstatic.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_PHSDSCR_H__FF8B6060_92B0_11D3_8ADB_00A0D21BD395__INCLUDED_)
#define AFX_PHSDSCR_H__FF8B6060_92B0_11D3_8ADB_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PhsDscr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PhaseDescription dialog

class PhaseDescription : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	PhaseDescription(int p, CWnd* pParent = NULL);   // standard constructor

	int phase;
// Dialog Data
	//{{AFX_DATA(PhaseDescription)
	enum { IDD = IDD_PHASEDESCRIPTION };
	CRStatic	m_IDC_RSTATICPHASEDESCRIP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PhaseDescription)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PhaseDescription)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHSDSCR_H__FF8B6060_92B0_11D3_8ADB_00A0D21BD395__INCLUDED_)
