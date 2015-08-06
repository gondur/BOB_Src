/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_ACUNITRF_H__1AC01FE0_CD9B_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_ACUNITRF_H__1AC01FE0_CD9B_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AcUnitRF.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AcUnitRAF dialog

class AcUnitRAF : public RowanDialog
{
// Construction
public:
	static RDialog* Make(int unit, bool spitfire, int tab,  int am);

	AcUnitRAF(int unit, bool spitfire,  int tab, int am,CWnd* pParent = NULL);   // standard constructor
	int oldunit;
	bool acisspitfire;
	int newunit;
	int currtab;
	int attackmethod;
// Dialog Data
	//{{AFX_DATA(AcUnitRAF)
	enum { IDD = IDD_UNIT_RAF };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	//}}AFX_DATA
	MakeField<SquadNum,0,255> sqlist;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AcUnitRAF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  
	// Generated message map functions
	//{{AFX_MSG(AcUnitRAF)
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDoubleSelectRlistboxctrl1(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACUNITRF_H__1AC01FE0_CD9B_11D3_8ADC_00A0D21BD395__INCLUDED_)
