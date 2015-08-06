/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rbutton.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_MFTARGET_H__929DEE42_9847_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_MFTARGET_H__929DEE42_9847_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MFTarget.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MapFiltersTarget dialog

class MapFiltersTarget : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	MapFiltersTarget(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MapFiltersTarget)
	enum { IDD = IDD_MAPFILTERS_TRGT };
	CRButton	m_IDC_OPERATIONALITEMS;
	CRButton	m_IDC_AIRFIELDS;
	CRButton	m_IDC_RBUTTONCOASTAL;
	CRButton	m_IDC_RBUTTONBOMBER;
	CRButton	m_IDC_RBUTTONFIGHTER;
	CRButton	m_IDC_BALLOONZONES;
	CRButton	m_IDC_CH;
	CRButton	m_IDC_STRIKE;
	CRButton	m_IDC_CHL;
	CRButton	m_IDC_CONVOYS;
	CRButton	m_IDC_DAMAGEDITEMS;
	CRButton	m_IDC_DEFENCES;
	CRButton	m_IDC_DESTROYEDITEMS;
	CRButton	m_IDC_DOCKS;
	CRButton	m_IDC_FACTORIES;
	CRButton	m_IDC_FLAKZONES;
	CRButton	m_IDC_LARGEICONS;
	CRButton	m_IDC_NAVPOINTS;
	CRButton	m_IDC_RBUTTON_DOCK_CIV;
	CRButton	m_IDC_RBUTTON_DOCK_NAVAL;
	CRButton	m_IDC_RBUTTON_FACTORYBOMBER;
	CRButton	m_IDC_RBUTTON_FACTORYFIGHTER;
	CRButton	m_IDC_RBUTTON_FACTORYOTHER;
	CRButton	m_IDC_RBUTTON_OIL;
	CRButton	m_IDC_RBUTTON_POWER;
	CRButton	m_IDC_RBUTTONCITY;
	CRButton	m_IDC_RBUTTONLIGHTHOUSES;
	CRButton	m_IDC_RBUTTONTOWN;
	CRButton	m_IDC_RBUTTONTUNNELS;
	CRButton	m_IDC_RBUTTONVILAGES;
	CRButton	m_IDC_RDF;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MapFiltersTarget)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Refresh(bool redrawmap=true);

	// Generated message map functions
	//{{AFX_MSG(MapFiltersTarget)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedOperationalitems();
	afx_msg void OnClickedRbuttonfighter();
	afx_msg void OnClickedRbuttonbomber();
	afx_msg void OnClickedRbuttoncoastal();
	afx_msg void OnClose();
	afx_msg void OnOK();
	afx_msg void OnClickedAirfields();
	afx_msg void OnClickedDamageditems();
	afx_msg void OnClickedDestroyeditems();
	afx_msg void OnClickedDefences();
	afx_msg void OnClickedFlakzones();
	afx_msg void OnClickedBalloonzones();
	afx_msg void OnClickedRdf();
	afx_msg void OnClickedCh();
	afx_msg void OnClickedChl();
	afx_msg void OnClickedDocks();
	afx_msg void OnClickedRbuttonDockCiv();
	afx_msg void OnClickedRbuttonDockNaval();
	afx_msg void OnClickedConvoys();
	afx_msg void OnClickedFactories();
	afx_msg void OnClickedRbuttonFactoryfighter();
	afx_msg void OnClickedRbuttonFactorybomber();
	afx_msg void OnClickedRbuttonFactoryother();
	afx_msg void OnClickedRbuttonOil();
	afx_msg void OnClickedRbuttonPower();
	afx_msg void OnClickedNavpoints();
	afx_msg void OnClickedRbuttoncity();
	afx_msg void OnClickedRbuttontown();
	afx_msg void OnClickedRbuttonvilages();
	afx_msg void OnClickedRbuttonlighthouses();
	afx_msg void OnClickedRbuttontunnels();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFTARGET_H__929DEE42_9847_11D3_8ADC_00A0D21BD395__INCLUDED_)
