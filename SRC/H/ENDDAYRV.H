/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rstatic.h"
#include "rbutton.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_ENDDAYRV_H__BF10BF00_F997_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_ENDDAYRV_H__BF10BF00_F997_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EndDayRv.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EndOfDayReviewText dialog

class EndOfDayReviewText : public RowanDialog
{
// Construction
public:
	static RDialog* Make(int review);

	EndOfDayReviewText(int review,CWnd* pParent = NULL);   // standard constructor
	int msgnum;
// Dialog Data
	//{{AFX_DATA(EndOfDayReviewText)
	enum { IDD = IDD_ENDOFDAYTEXT };
	CRStatic	m_IDC_RSTATICREVIEWTEXT;
	CRButton	m_IDC_RBUTTONTITLE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EndOfDayReviewText)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EndOfDayReviewText)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENDDAYRV_H__BF10BF00_F997_11D3_8ADC_00A0D21BD395__INCLUDED_)
