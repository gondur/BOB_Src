/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rbutton.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_TELETYPE_H__AE7C8540_96CB_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_TELETYPE_H__AE7C8540_96CB_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TeleType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TeleType dialog

class TeleType : public CRToolBar
{
// Construction
public:
	typedef	 RDialog*	(*MakeRtn)(int msg) ;

	CON	TeleType(MakeRtn maker,CWnd* pParent = NULL);   // standard constructor
	void	FillTextLines( int line,CString str1,CString str2);
	void Refresh(bool force=false);
	int messages[4];

// Dialog Data
	//{{AFX_DATA(TeleType)
	enum { IDD = IDDT_TELETYPE };
	CRButton	m_IDC_LINE1;
	CRButton	m_IDC_LINE2;
	CRButton	m_IDC_LINE3;
	CRButton	m_IDC_ITEM1;
	CRButton	m_IDC_ITEM2;
	CRButton	m_IDC_ITEM3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TeleType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	MakeRtn	makertn;
	// Generated message map functions
	//{{AFX_MSG(TeleType)
	afx_msg void OnClickedLine1();
	afx_msg void OnClickedLine2();
	afx_msg void OnClickedLine3();
	afx_msg void OnClickedName1();
	afx_msg void OnClickedName2();
	afx_msg void OnClickedName3();
	afx_msg void OnInitMenu(CMenu* pMenu);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TELETYPE_H__AE7C8540_96CB_11D3_8ADC_00A0D21BD395__INCLUDED_)
