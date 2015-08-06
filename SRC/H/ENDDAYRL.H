/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_ENDDAYRL_H__BF10BF01_F997_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_ENDDAYRL_H__BF10BF01_F997_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EndDayRL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EndOfDayReviewList dialog

class EndOfDayReviewList : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	EndOfDayReviewList(CWnd* pParent = NULL);   // standard constructor
		int currmsg, maxmsg;
	enum {MAXMESSAGES = 20};

	int msglist[MAXMESSAGES];

// Dialog Data
	//{{AFX_DATA(EndOfDayReviewList)
	enum { IDD = IDD_ENDOFDAYREVIEWLIST };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EndOfDayReviewList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
 	void Refresh();
	void FillList();


	// Generated message map functions
	//{{AFX_MSG(EndOfDayReviewList)
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENDDAYRL_H__BF10BF01_F997_11D3_8ADC_00A0D21BD395__INCLUDED_)
