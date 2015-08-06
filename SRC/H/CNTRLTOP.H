/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()

//}}AFX_INCLUDES

*/
#if !defined(AFX_CNTRLTOP_H__505DEF42_95BC_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_CNTRLTOP_H__505DEF42_95BC_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CntrlTop.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ControlTopLevel dialog

class ControlTopLevel : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	ControlTopLevel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ControlTopLevel)
	enum { IDD = IDD_CONTROLTOP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ControlTopLevel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ControlTopLevel)
	afx_msg void OnOK();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRLTOP_H__505DEF42_95BC_11D3_8ADC_00A0D21BD395__INCLUDED_)
