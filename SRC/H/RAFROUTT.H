/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()

//}}AFX_INCLUDES

*/
#if !defined(AFX_RAFROUTT_H__84DA9261_9DB3_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_RAFROUTT_H__84DA9261_9DB3_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RAFRoutT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RAFRouteTop dialog

class RAFRouteTop : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	RAFRouteTop(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RAFRouteTop)
	enum { IDD = IDD_RAFROUTETOP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RAFRouteTop)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RAFRouteTop)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAFROUTT_H__84DA9261_9DB3_11D3_8ADC_00A0D21BD395__INCLUDED_)
