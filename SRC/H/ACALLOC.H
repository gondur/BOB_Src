/*
//{{AFX_INCLUDES()
#include "rstatic.h"
#include "rcombo.h"
#include "rspinbut.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_ACALLOC_H__B5583A80_8645_11D3_8ADB_00A0D21BD395__INCLUDED_)
#define AFX_ACALLOC_H__B5583A80_8645_11D3_8ADB_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// acalloc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AircraftAllocation dialog

class AircraftAllocation : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	AircraftAllocation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AircraftAllocation)
	enum { IDD = IDD_ACALLOC };
	CRStatic	m_IDC_STATIC_AIRCRAFT0;
	CRStatic	m_IDC_STATIC_AIRCRAFT1;
	CRStatic	m_IDC_STATIC_AIRCRAFT2;
	CRStatic	m_IDC_STATIC_AIRCRAFT3;
	CRStatic	m_IDC_STATIC_AIRCRAFT4;
	CRStatic	m_IDC_STATIC_AIRCRAFT5;
	CRStatic	m_IDC_STATIC_AIRFIELD0;
	CRStatic	m_IDC_STATIC_AIRFIELD1;
	CRStatic	m_IDC_STATIC_AIRFIELD2;
	CRStatic	m_IDC_STATIC_AIRFIELD3;
	CRStatic	m_IDC_STATIC_AIRFIELD4;
	CRStatic	m_IDC_STATIC_AIRFIELD5;
	CRStatic	m_IDC_STATIC_ETA0;
	CRStatic	m_IDC_STATIC_ETA1;
	CRStatic	m_IDC_STATIC_ETA2;
	CRStatic	m_IDC_STATIC_ETA3;
	CRStatic	m_IDC_STATIC_ETA4;
	CRStatic	m_IDC_STATIC_ETA5;
	CRStatic	m_IDC_STATIC_RATE0;
	CRStatic	m_IDC_STATIC_RATE1;
	CRStatic	m_IDC_STATIC_RATE2;
	CRStatic	m_IDC_STATIC_RATE3;
	CRStatic	m_IDC_STATIC_RATE4;
	CRStatic	m_IDC_STATIC_RATE5;
	CRStatic	m_IDC_RSTATICCTRL1;
	CRCombo	m_IDC_COMBO_SQUAD0;
	CRCombo	m_IDC_COMBO_SQUAD1;
	CRCombo	m_IDC_COMBO_SQUAD2;
	CRCombo	m_IDC_COMBO_SQUAD3;
	CRCombo	m_IDC_COMBO_SQUAD4;
	CRCombo	m_IDC_COMBO_SQUAD5;
	CRSpinBut	m_IDC_SPIN_REQUIREMENT0;
	CRSpinBut	m_IDC_SPIN_REQUIREMENT1;
	CRSpinBut	m_IDC_SPIN_REQUIREMENT2;
	CRSpinBut	m_IDC_SPIN_REQUIREMENT3;
	CRSpinBut	m_IDC_SPIN_REQUIREMENT4;
	CRSpinBut	m_IDC_SPIN_REQUIREMENT5;
	CRStatic	m_IDC_STAIC_READY0;
	CRStatic	m_IDC_STAIC_READY1;
	CRStatic	m_IDC_STAIC_READY2;
	CRStatic	m_IDC_STAIC_READY3;
	CRStatic	m_IDC_STAIC_READY4;
	CRStatic	m_IDC_STAIC_READY5;
	CRStatic  m_IDC_STATICPRODUCTIONPAUSED;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AircraftAllocation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	SetSide();
	void FillOneSqCombo(int i);
	void FillSqCombo();
	void RefreshOneLine(int sqd) ;
	void Refresh();



	int actoalloc[6];
	// Generated message map functions
	//{{AFX_MSG(AircraftAllocation)
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedSpinRequirement0(int id, LPCTSTR caption, short Index);
	afx_msg void OnTextChangedComboSquad0(int id, LPCTSTR Caption, short index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACALLOC_H__B5583A80_8645_11D3_8ADB_00A0D21BD395__INCLUDED_)
