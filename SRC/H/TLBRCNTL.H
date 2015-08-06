/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rbutton.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_TLBRCNTL_H__29B9D060_9680_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_TLBRCNTL_H__29B9D060_9680_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TlBrCntl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ToolBarControl dialog

class ToolBarControl : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	ToolBarControl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ToolBarControl)
	enum { IDD = IDD_TOOLBARCONTROL };
	CRButton	m_IDC_TB_TITLE;
//DEADCODE RDH 06/01/00 	CRButton	m_IDC_TB_COMMS;
	CRButton	m_IDC_TB_MAIN;
	CRButton	m_IDC_TB_MAPTOOLS;
	CRButton	m_IDC_TB_MESSAGES;
//DEADCODE RDH 06/01/00 	CRButton	m_IDC_TB_OVERVIEW;
	CRButton	m_IDC_TB_MAPSCALE;
	CRButton	m_IDC_TB_ALL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ToolBarControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	ToolBarsField	testall;
	void	Redraw();
	// Generated message map functions
	//{{AFX_MSG(ToolBarControl)
	virtual BOOL OnInitDialog();
//DEADCODE RDH 06/01/00 	afx_msg void OnClickedTbComms();
	afx_msg void OnClickedTbMain();
	afx_msg void OnClickedTbMaptools();
	afx_msg void OnClickedTbMessages();
//DEADCODE RDH 06/01/00 	afx_msg void OnClickedTbOverview();
	afx_msg void OnClickedTbTitle();
	afx_msg void OnClickedTbMapscale();
	afx_msg void OnClickedTbAll();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TLBRCNTL_H__29B9D060_9680_11D3_8ADC_00A0D21BD395__INCLUDED_)
