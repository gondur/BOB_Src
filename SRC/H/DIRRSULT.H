/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_DIRRSULT_H__90C035A1_9C0D_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_DIRRSULT_H__90C035A1_9C0D_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirRsult.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DirectiveResults dialog

class DirectiveResults : public RowanDialog
{
// Construction
public:
	static RDialog* Make(LWDirectivesResults* dires);

	DirectiveResults(LWDirectivesResults* dires,CWnd* pParent = NULL);   // standard constructor
	~DirectiveResults();   // standard constructor

	LWDirectivesResults* dr;

// Dialog Data
	//{{AFX_DATA(DirectiveResults)
	enum { IDD = IDD_DIRECTIVERESULTS };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DirectiveResults)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	Refresh();

	// Generated message map functions
	//{{AFX_MSG(DirectiveResults)
	virtual BOOL OnInitDialog();
	afx_msg void OnOK();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRRSULT_H__90C035A1_9C0D_11D3_8ADC_00A0D21BD395__INCLUDED_)
