/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()

//}}AFX_INCLUDES

*/
#if !defined(AFX_ENDDYBMP_H__471309C0_11E5_11D4_943C_00A0D21BCF99__INCLUDED_)
#define AFX_ENDDYBMP_H__471309C0_11E5_11D4_943C_00A0D21BCF99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EndDyBmp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EndofDayReviewBmp dialog

class EndofDayReviewBmp : public RowanDialog
{
// Construction
public:
	static RDialog* Make(int msgnum);

	EndofDayReviewBmp(int msgnum, CWnd* pParent = NULL);   // standard constructor

	int msg;
// Dialog Data
	//{{AFX_DATA(EndofDayReviewBmp)
	enum { IDD = IDD_ENDOFDAYREVIEWBMP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EndofDayReviewBmp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EndofDayReviewBmp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENDDYBMP_H__471309C0_11E5_11D4_943C_00A0D21BCF99__INCLUDED_)
