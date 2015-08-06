/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rbutton.h"
#include "rstatic.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_TOTESECT_H__90C035A0_9C0D_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_TOTESECT_H__90C035A0_9C0D_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToteSect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ToteSector dialog

class ToteSector : public RowanDialog
{
// Construction
public:
	static RDialog* Make(UniqueID uid);

	ToteSector(UniqueID uid,CWnd* pParent = NULL);   // standard constructor

	enum{MAXTOTEOPTIONS = 24};
	static int	readinesslevel[MAXTOTEOPTIONS];
	UniqueID sectoraf;
// Dialog Data
	//{{AFX_DATA(ToteSector)
	enum { IDD = IDD_TOTSECTOR };
	CRButton	m_IDJ_TITLE;
	CRButton	m_IDC_RBUTTON_W0;
	CRButton	m_IDC_RBUTTON_B0;
	CRButton	m_IDC_RBUTTON_W1;
	CRButton	m_IDC_RBUTTON_B1;
	CRButton	m_IDC_RBUTTON_B2;
	CRButton	m_IDC_RBUTTON_B3;
	CRButton	m_IDC_RBUTTON_B4;
	CRButton	m_IDC_RBUTTON_W2;
	CRButton	m_IDC_RBUTTON_W3;
	CRButton	m_IDC_RBUTTON_W4;
	CRStatic	m_IDC_RSTATIC_AC0;
	CRStatic	m_IDC_RSTATIC_PLT0;
	CRStatic	m_IDC_RSTATICSQ0;
	CRStatic	m_IDC_RSTATIC_PLT1;
	CRStatic	m_IDC_RSTATIC_PLT2;
	CRStatic	m_IDC_RSTATIC_PLT3;
	CRStatic	m_IDC_RSTATIC_PLT4;
	CRStatic	m_IDC_RSTATICSQ1;
	CRStatic	m_IDC_RSTATICSQ2;
	CRStatic	m_IDC_RSTATICSQ3;
	CRStatic	m_IDC_RSTATICSQ4;
	CRStatic	m_IDC_RSTATIC_AC1;
	CRStatic	m_IDC_RSTATIC_AC2;
	CRStatic	m_IDC_RSTATIC_AC3;
	CRStatic	m_IDC_RSTATIC_AC4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ToteSector)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RefreshTote();
	void RefreshLights();
	void RefreshData(int childnum);

	// Generated message map functions
	//{{AFX_MSG(ToteSector)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOTESECT_H__90C035A0_9C0D_11D3_8ADC_00A0D21BD395__INCLUDED_)
