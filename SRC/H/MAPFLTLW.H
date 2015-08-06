/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rradio.h"
#include "rbutton.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_MAPFLTLW_H__CBA55360_F5E2_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_MAPFLTLW_H__CBA55360_F5E2_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapFltLw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MapFiltersRaidsLW dialog

class MapFiltersRaidsLW : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	MapFiltersRaidsLW(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MapFiltersRaidsLW)
	enum { IDD = IDD_MAPFILTERS_RAIDS_LW };
	CRRadio	m_IDC_RRADIO_PLOTS;
	CRButton	m_IDC_LWROUTELINES;
	CRButton	m_IDC_FIGHTERSWEEPS;
	CRButton	m_IDC_BOMBERS;
	CRButton	m_IDC_LWTARGETLINES;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MapFiltersRaidsLW)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void 	Refresh();

	// Generated message map functions
	//{{AFX_MSG(MapFiltersRaidsLW)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedFightersweeps();
	afx_msg void OnClickedLwroutelines();
	afx_msg void OnClickedLwtargetlines();
	afx_msg void OnClickedBombers();
	afx_msg void OnSelectedRradioPlots(long ButtonNum);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPFLTLW_H__CBA55360_F5E2_11D3_8ADC_00A0D21BD395__INCLUDED_)
