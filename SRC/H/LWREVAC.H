/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_LWREVAC_H__982C4660_A1B4_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_LWREVAC_H__982C4660_A1B4_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWRevAc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWReviewAircraft dialog

class LWReviewAircraft : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	LWReviewAircraft(CWnd* pParent = NULL);   // standard constructor
	enum {TOTAL = 6,MAXTYPES = 7};

// Dialog Data
	//{{AFX_DATA(LWReviewAircraft)
	enum { IDD = IDD_LWREVIEWAIRCRAFT };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWReviewAircraft)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LWReviewAircraft)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWREVAC_H__982C4660_A1B4_11D3_8ADC_00A0D21BD395__INCLUDED_)
