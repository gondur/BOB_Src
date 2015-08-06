/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rbutton.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_CLOCK_H__FCCEDC20_9B3A_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_CLOCK_H__FCCEDC20_9B3A_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// clock.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Clock dialog

class Clock : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	Clock(CWnd* pParent = NULL);   // standard constructor
	CRect	lastrect;
// Dialog Data
	//{{AFX_DATA(Clock)
	enum { IDD = IDD_CLOCK };
	CRButton	m_IDJ_TITLE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Clock)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Clock)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP() 
	void RefreshData(int childnum);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOCK_H__FCCEDC20_9B3A_11D3_8ADC_00A0D21BD395__INCLUDED_)
