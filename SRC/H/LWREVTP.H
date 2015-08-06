/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()

//}}AFX_INCLUDES

*/
#if !defined(AFX_LWREVTP_H__B7F9E500_A1B0_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_LWREVTP_H__B7F9E500_A1B0_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWRevTp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWReviewTop dialog

class LWReviewTop : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	LWReviewTop(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(LWReviewTop)
	enum { IDD = IDD_LWREVIEWTOP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWReviewTop)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LWReviewTop)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWREVTP_H__B7F9E500_A1B0_11D3_8ADC_00A0D21BD395__INCLUDED_)
