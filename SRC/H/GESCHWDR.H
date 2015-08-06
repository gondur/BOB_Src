/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_GESCHWDR_H__76D7D540_B151_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_GESCHWDR_H__76D7D540_B151_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Geschwdr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Geschwader dialog

class Geschwader : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	Geschwader(int geschwader, CWnd* pParent = NULL);   // standard constructor
	int geschwadertype;
// Dialog Data
	//{{AFX_DATA(Geschwader)
	enum { IDD = IDD_GESCHWADER };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Geschwader)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	enum	{ MAX_GESCH = 10};
	void FindGeschwader();
	void RefreshLW();

   	int geschwaderarray[2][4][MAX_GESCH];

	// Generated message map functions
	//{{AFX_MSG(Geschwader)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GESCHWDR_H__76D7D540_B151_11D3_8ADC_00A0D21BD395__INCLUDED_)
