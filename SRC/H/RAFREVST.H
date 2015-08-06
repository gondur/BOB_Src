/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rstatic.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_RAFREVST_H__1D765321_A191_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_RAFREVST_H__1D765321_A191_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RAFRevSt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RAFReviewStrength dialog

class RAFReviewStrength : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	RAFReviewStrength(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(RAFReviewStrength)
	enum { IDD = IDD_RAFREVIEWSTRENGTH };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRStatic	m_IDC_RSTATIC_COMMENT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RAFReviewStrength)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillStrengthInfo();

	// Generated message map functions
	//{{AFX_MSG(RAFReviewStrength)
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAFREVST_H__1D765321_A191_11D3_8ADC_00A0D21BD395__INCLUDED_)
