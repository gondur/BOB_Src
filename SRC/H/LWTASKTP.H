/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()

//}}AFX_INCLUDES

*/
#if !defined(AFX_LWTASKTP_H__F8E7C261_9E65_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_LWTASKTP_H__F8E7C261_9E65_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWTaskTp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWTaskTop dialog

class LWTaskTop : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	LWTaskTop(CWnd* pParent = NULL);   // standard constructor
	void RefreshData(int childnum);
// Dialog Data
	//{{AFX_DATA(LWTaskTop)
	enum { IDD = IDD_LWTASKTOP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWTaskTop)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LWTaskTop)
	virtual BOOL OnInitDialog();
	afx_msg void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWTASKTP_H__F8E7C261_9E65_11D3_8ADC_00A0D21BD395__INCLUDED_)
