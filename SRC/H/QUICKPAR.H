/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rcombo.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_QUICKPAR_H__8D9853C0_CDC8_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_QUICKPAR_H__8D9853C0_CDC8_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QuickPar.h : header file
//
//#include "rcombo.h"

/////////////////////////////////////////////////////////////////////////////
// QuickParameters dialog

class QuickParameters : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	QuickParameters(CWnd* pParent = NULL);   // standard constructor
	int targtype;
	int targentry;

// Dialog Data
	//{{AFX_DATA(QuickParameters)
	enum { IDD = IDD_QUICKPARAS };
	CRCombo	m_IDC_TARGNAME;
	CRCombo	m_IDC_TARGTYPE;
	CRCombo	m_IDC_TIME;
	CRCombo	m_IDC_CLOUD;
	CREdit	m_IDC_NAME;
	//}}AFX_DATA

	static	void	SetWeather(int index);
	static	void	SetTime(int index);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(QuickParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	ReinitCombo();
	void	TargNameCombo();



	// Generated message map functions
	//{{AFX_MSG(QuickParameters)
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedTargname(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedTargtype(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCloud(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedTime(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedName(LPTSTR text);
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUICKPAR_H__8D9853C0_CDC8_11D3_8ADC_00A0D21BD395__INCLUDED_)
