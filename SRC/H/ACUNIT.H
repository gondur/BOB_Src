/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_ACUNIT_H__4E2C6BE0_A186_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_ACUNIT_H__4E2C6BE0_A186_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AcUnit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AircraftUnit dialog

class AircraftUnit : public RowanDialog
{
// Construction
public:
	enum	TypesToList	{TTL_JU87,TTL_110,TTL_FIGHTER,TTL_BOMBER,TTL_SPITFIRE,TTL_HURRICANE,TTL_RECONN1,TTL_RECONN2,TTL_RECONN3};
	static RDialog* Make(int oldunit, TypesToList typestolist, int tab, int am, int unitdisplaylevel);

	AircraftUnit(int oldunit, TypesToList typestolist, int tab, int am, int unitdisplaylevel, CWnd* pParent = NULL);   // standard constructor
	int oldunit;
	TypesToList	typestolist	;
//DeadCode JIM 14Nov00 	bool acisfighter;
	int newunit;
	int currtab;
	int attackmethod;
//DeadCode JIM 14Nov00 	bool me110isbomber;
	int udisplayl;
// Dialog Data
	//{{AFX_DATA(AircraftUnit)
	enum { IDD = IDD_UNIT };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AircraftUnit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AircraftUnit)
	virtual BOOL OnInitDialog();
	afx_msg void OnOK();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnDoubleSelectRlistboxctrl1(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACUNIT_H__4E2C6BE0_A186_11D3_8ADC_00A0D21BD395__INCLUDED_)
