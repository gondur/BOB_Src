/*
//{{AFX_INCLUDES()
#include "rcombo.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_SFLIGHT_H__692F5BC0_F0A0_11D1_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_SFLIGHT_H__692F5BC0_F0A0_11D1_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SFlight.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSFlight dialog

class CSFlight : public RowanDialog
{
// Construction
public:
	CSFlight(CWnd* pParent = NULL);   // standard constructor
	void PreDestroyPanel();
	UINT	FlightPref_Timer;

// Dialog Data
	//{{AFX_DATA(CSFlight)
	enum { IDD = IDD_SFLIGHT };
	CRCombo	m_IDC_CBO_ALL;
	CRStatic	m_IDC_RSTATICCTRL1;
	CRCombo	m_IDC_CBO_POWERBOOST;
	CRStatic	m_IDC_RSTATICCTRL3;
	CRCombo	m_IDC_CBO_RUDDER;
	CRCombo	m_IDC_CBO_WINDGUSTS;
	CRStatic	m_IDC_RSTATICCTRL5;
	CRCombo	m_IDC_CBO_SPINS;
	CRStatic	m_IDC_RSTATICCTRL6;
	CRCombo	m_IDC_CBO_AIRFRAME;
	CRStatic	m_IDC_RSTATICCTRL7;
	CRCombo	m_IDC_CBO_TORQUE;
	CRStatic	m_IDC_RSTATICCTRL9;
	CRCombo	m_IDC_CBO_109FUEL;
	CRStatic	m_IDC_RSTATICCTRL10;
	CRCombo	m_IDC_CBO_WIND0;
	CRStatic	m_IDC_RSTATICCTRL52;
	CRCombo	m_IDC_CBO_ENGINEMANAGEMENT;
	CRCombo	m_IDC_CBO_PROPPITCH;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSFlight)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSFlight)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTextChangedCboAll(LPCTSTR text, short index);
	afx_msg void OnTextChangedCboAirframe(LPCTSTR text, short index);
	afx_msg void OnTextChangedCbo109Fuel(LPCTSTR text, short index);
	afx_msg void OnTextChangedCboPowerboost(LPCTSTR text, short index);
	afx_msg void OnTextChangedCboRudder(LPCTSTR text, short index);
	afx_msg void OnTextChangedCboSpins(LPCTSTR text, short index);
	afx_msg void OnTextChangedCboTorque(LPCTSTR text, short index);
	afx_msg void OnTextChangedCboWind(LPCTSTR text, short index);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTextChangedCboWind0(LPCTSTR text, short index);
	afx_msg void OnTextChangedCboProppitch(LPCTSTR text, short index);
	afx_msg void OnTextChangedCboEnginemanagement(LPCTSTR text, short index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SFLIGHT_H__692F5BC0_F0A0_11D1_A1F0_0080C8582DE4__INCLUDED_)
