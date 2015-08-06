/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rbutton.h"
#include "rspinbut.h"
#include "rstatic.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_CNTRLACL_H__505DEF40_95BC_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_CNTRLACL_H__505DEF40_95BC_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CntrlAcl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ControlAccel dialog

class ControlAccel : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	ControlAccel(CWnd* pParent = NULL);   // standard constructor
	enum{DIALOGSPDMAXINDEX =6, MAXSPDMAXINDEX =16};

	static int NonRaidSpd[MAXSPDMAXINDEX];
	static int ReconnSpd[MAXSPDMAXINDEX];
	static int RaidSpd[MAXSPDMAXINDEX];
	static int DialogSpd[DIALOGSPDMAXINDEX];

// Dialog Data
	//{{AFX_DATA(ControlAccel)
	enum { IDD = IDD_CONTROLACCEL };
	CRButton	m_IDC_RAIDFORMING;
	CRButton	m_IDC_LOSSES;
	CRButton	m_IDC_GROUNDATTACK;
	CRButton	m_IDC_LANDING;
	CRButton	m_IDC_LARGEENGAGEMENT;
	CRButton	m_IDC_REACHCOAST;
	CRSpinBut	m_IDC_RSPINBUT_NONRAID;
	CRSpinBut	m_IDC_RSPINBUT_RAID;
	CRSpinBut	m_IDC_RSPINBUT_RECONN;
	CRButton	m_IDC_SCRAMBLE;
	CRButton	m_IDC_SMALLENGAGEMENT;
	CRSpinBut	m_IDC_RSPINBUT_DIALOGSPEED;
	CRStatic	m_IDC_RSTATIC_NRS;
	CRStatic	m_IDC_RSTATIC_RECONS;
	CRStatic	m_IDC_RSTATIC_RS;
	CRStatic	m_IDC_DIALOGSPD;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ControlAccel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillSpin(int* spdarray, CRSpinBut* spinbut, int maxindex = MAXSPDMAXINDEX);
	int	 FindIndex(int* spdarray,int spd, int maxindex = MAXSPDMAXINDEX);
	void	FixSpeedsInToRange(int against);

	void	Refresh();
	enum	{ACCEL_MAX=6};
	CRSpinBut*	accelcontrols[ACCEL_MAX];
	int*		acceltables[ACCEL_MAX];
	// Generated message map functions
	//{{AFX_MSG(ControlAccel)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedRaidforming();
	afx_msg void OnClickedScramble();
	afx_msg void OnClickedSmallengagement();
	afx_msg void OnClickedLanding();
	afx_msg void OnClickedGroundattack();
	afx_msg void OnClickedLargeengagement();
	afx_msg void OnClickedLosses();
	afx_msg void OnTextChangedRspinbutNonraid(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutRaid(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutReconn(LPCTSTR caption, short Index);
	afx_msg void OnClickedReachcoast();
	afx_msg void OnOK();
	afx_msg void OnTextChangedRspinbutDialogspeed(LPCTSTR caption, short Index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRLACL_H__505DEF40_95BC_11D3_8ADC_00A0D21BD395__INCLUDED_)
