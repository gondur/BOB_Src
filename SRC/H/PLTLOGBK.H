/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_PLTLOGBK_H__1E804160_91E0_11D3_8ADB_00A0D21BD395__INCLUDED_)
#define AFX_PLTLOGBK_H__1E804160_91E0_11D3_8ADB_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PltLogBk.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PilotLogBook dialog

class PilotLogBook : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	PilotLogBook(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PilotLogBook)
	enum { IDD = IDD_PILOTLOGBOOK };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CREdit	m_IDC_NAME;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PilotLogBook)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RAFRefreshList();
	void LWRefreshList();

	// Generated message map functions
	//{{AFX_MSG(PilotLogBook)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnTextChangedName(LPTSTR text);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLTLOGBK_H__1E804160_91E0_11D3_8ADB_00A0D21BD395__INCLUDED_)
