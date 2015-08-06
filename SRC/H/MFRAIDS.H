/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rbutton.h"
#include "rradio.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_MFRAIDS_H__929DEE40_9847_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_MFRAIDS_H__929DEE40_9847_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MFRaids.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MapFiltersRaids dialog

class MapFiltersRaids : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	MapFiltersRaids(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MapFiltersRaids)
	enum { IDD = IDD_MAPFILTERS_RAIDS };
	CRButton	m_IDC_LWARROWS;
	CRButton	m_IDC_RAFINTERCEPTS;
	CRButton	m_IDC_RAFPATROLS;
	CRButton	m_IDC_RAFROUTELINES;
	CRRadio	m_IDC_RRADIO_PLOTS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MapFiltersRaids)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void 	Refresh();



	// Generated message map functions
	//{{AFX_MSG(MapFiltersRaids)
	afx_msg void OnClickedLwarrows();
	afx_msg void OnClickedRafintercepts();
	afx_msg void OnClickedRafpatrols();
	afx_msg void OnClickedRafroutelines();
	afx_msg void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectedRradioPlots(long ButtonNum);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFRAIDS_H__929DEE40_9847_11D3_8ADC_00A0D21BD395__INCLUDED_)
