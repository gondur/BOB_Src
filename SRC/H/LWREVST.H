/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rstatic.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_LWREVST_H__B7F9E501_A1B0_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_LWREVST_H__B7F9E501_A1B0_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWRevSt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWReviewStrength dialog

class LWReviewStrength : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	LWReviewStrength(CWnd* pParent = NULL);   // standard constructor
//DEADCODE RDH 24/05/00 		enum {TOTAL = 6,MAXTYPES = 7};
//DEADCODE RDH 24/05/00 
//DEADCODE RDH 24/05/00 	struct	StrengthInfo
//DEADCODE RDH 24/05/00 	{
//DEADCODE RDH 24/05/00 		int catA;
//DEADCODE RDH 24/05/00 		int catB;
//DEADCODE RDH 24/05/00 		int catC;
//DEADCODE RDH 24/05/00 		int acready;
//DEADCODE RDH 24/05/00 		int actotal;
//DEADCODE RDH 24/05/00 		int	pilots;
//DEADCODE RDH 24/05/00 	};
//DEADCODE RDH 24/05/00 
//DEADCODE RDH 24/05/00 	StrengthInfo	strengthinfo[MAXTYPES];
//DEADCODE RDH 24/05/00 
// Dialog Data
	//{{AFX_DATA(LWReviewStrength)
	enum { IDD = IDD_LWREVIEWSTRENGTH };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRStatic	m_IDC_RSTATIC_COMMENT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWReviewStrength)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillStrengthInfo();

	// Generated message map functions
	//{{AFX_MSG(LWReviewStrength)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWREVST_H__B7F9E501_A1B0_11D3_8ADC_00A0D21BD395__INCLUDED_)
