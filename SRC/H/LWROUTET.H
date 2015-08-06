/*
//{{AFX_INCLUDES()
#include "rstatic.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_LWROUTET_H__37005B83_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_LWROUTET_H__37005B83_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWRouteT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWRouteTop dialog

class LWRouteTop : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	LWRouteTop(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(LWRouteTop)
	enum { IDD = IDD_LWROUTETOP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWRouteTop)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LWRouteTop)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWROUTET_H__37005B83_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_)
