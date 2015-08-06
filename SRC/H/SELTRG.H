/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rcombo.h"
#include "rbutton.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_SELTRG_H__4E2C6BE1_A186_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_SELTRG_H__4E2C6BE1_A186_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelTrg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SelectTarget dialog

class SelectTarget : public RowanDialog
{
// Construction
public:
	static RDialog* Make(int squad, int tab, int unitdisplaylevel, SelectTargetMode selecttargetmode);

	SelectTarget(int squad, int tab,int unitdisplaylevel,SelectTargetMode selecttargetmode,CWnd* pParent = NULL);   // standard constructor

	int currtab, currsquad;
	int currindex;
		void	RefreshData(int targetid);
	int udl;
//DeadCode JIM 28Sep00 	SaveData Save_Data_tmp;
// Dialog Data
	//{{AFX_DATA(SelectTarget)
	enum { IDD = IDD_SELTRG };
	CRCombo	m_IDC_RCOMBOTARGET;
	CRButton	m_IDC_RBUTTONRESET;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelectTarget)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	SetTargetIndex(int trgindex);

	// Generated message map functions
	//{{AFX_MSG(SelectTarget)
	afx_msg void OnClickedRbuttoncancel();
	afx_msg void OnClickedRbuttonreset();
	afx_msg void OnOK();
	afx_msg void OnClose();
	afx_msg void OnTextChangedRcombotarget(LPCTSTR Caption, short index);
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELTRG_H__4E2C6BE1_A186_11D3_8ADC_00A0D21BD395__INCLUDED_)
