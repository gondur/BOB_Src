/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rbutton.h"
#include "rcombo.h"
#include "rstatic.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_CNTRLFLY_H__505DEF41_95BC_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_CNTRLFLY_H__505DEF41_95BC_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CntrlFly.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ControlFly dialog

class ControlFly : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	ControlFly(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ControlFly)
	enum { IDD = IDD_CONTROLFLY };
	CRButton	m_IDC_GROUNDATTACK_ALL;
	CRButton	m_IDC_GROUNDATTACK_FAV;
	CRButton	m_IDC_LANDING_FAV;
	CRButton	m_IDC_TO_FAV;
	CRButton	m_IDC_SMALLENGAGEMENT_FAV;
	CRButton	m_IDC_LARGEENGAGEMENT_FAV;
	CRButton	m_IDC_LOSSES_FAV;
	CRButton	m_IDC_TO_ALL;
	CRButton	m_IDC_SMALLENGAGEMENT_ALL;
	CRButton	m_IDC_LARGEENGAGEMENT_ALL;
	CRButton	m_IDC_LOSSES_ALL;
	CRCombo	m_IDC_RCOMBOAIRCRAFT;
	CRCombo	m_IDC_RCOMBOSQUADRON;
	CRCombo	m_IDC_RCOMBOSECTOR;
	CRButton	m_IDC_REACHCOAST_FAV;
	CRButton	m_IDC_REACHCOAST_ALL;
	CRCombo	m_IDC_RCOMBOGROUP;
	CRButton	m_IDC_LANDING_ALL;
	CRStatic	m_IDC_RSTATICCTRL_0;
	CRStatic	m_IDC_RSTATICCTRL_1;
	CRStatic	m_IDC_RSTATICCTRL_2;
	CRStatic	m_IDC_RSTATICCTRL_3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ControlFly)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	enum	{MAX_SQUAD = 100};
	int maxsquads;
    int Favorite[MAX_SQUAD];
    void RefreshSector();
	void RefreshSquadron();
	void RefreshCombos();
	void FindSquadrons();
	void RefreshGeschwader();
	void FindGeschwader();

	// Generated message map functions
	//{{AFX_MSG(ControlFly)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedGroundattackAll();
	afx_msg void OnClickedGroundattackFav();
	afx_msg void OnClickedLandingAll();
	afx_msg void OnClickedLandingFav();
	afx_msg void OnClickedLargeengagementAll();
	afx_msg void OnClickedLargeengagementFav();
	afx_msg void OnClickedLossesAll();
	afx_msg void OnClickedLossesFav();
	afx_msg void OnClickedReachcoastAll();
	afx_msg void OnClickedReachcoastFav();
	afx_msg void OnClickedSmallengagementAll();
	afx_msg void OnClickedSmallengagementFav();
	afx_msg void OnClickedToAll();
	afx_msg void OnClickedToFav();
	afx_msg void OnTextChangedRcomboaircraft(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRcombogroup(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRcombosector(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRcombosquadron(LPCTSTR Caption, short index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRLFLY_H__505DEF41_95BC_11D3_8ADC_00A0D21BD395__INCLUDED_)
