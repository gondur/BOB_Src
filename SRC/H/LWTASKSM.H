/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rcombo.h"
#include "rspinbut.h"
#include "rstatic.h"
#include "rbutton.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_LWTASKSM_H__F8E7C260_9E65_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_LWTASKSM_H__F8E7C260_9E65_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWTaskSm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWTaskSummary dialog

class LWTaskSummary : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	LWTaskSummary(CWnd* pParent = NULL);   // standard constructor

	void LWTaskSummary::Refresh();

	struct	SquadInfo
	{
		int		numofsquads;
		int		number;
		int		name;
	};
	enum	{FIGHTERMAX = 6, ACMAX = 7, SQUADMAX = 14,SQUADSENSIBLEMAX=9} ;
	static SquadInfo	squadinfo[SQUADMAX];
	static int  AcSpin[ACMAX];
	static int FighterSpin[FIGHTERMAX] ;
	void MakeFighterSpinLists(bool setreq);
	int oldindex;
	Float	attachedfracreq,detachedfracreq,attachedfraccurr,detachedfraccurr;
	Float	stepsize;
	int		totalfighterstaffeln;
// Dialog Data
	//{{AFX_DATA(LWTaskSummary)
	enum { IDD = IDD_LWTASKSUMMARY };
	CRCombo	m_IDC_RCOMBOBOMBERTYPE;
	CRCombo	m_IDC_RCOMBOFIGHTERTYPE;
	CRSpinBut	m_IDC_RSPINBUT_BOMBERS;
	CRSpinBut	m_IDC_RSPINBUT_FIGHTERS;
	CRSpinBut	m_IDC_RSPINBUT_PERCENTFIGHTERS;
	CRSpinBut	m_IDC_RSPINBUT_TARGETS;
	CRSpinBut	m_IDC_SPC_ATTACHED;
	CRSpinBut	m_IDC_SPC_DETACHED;
	CRSpinBut	m_IDC_SPC_RETURNING;
//DeadCode JIM 30Oct00 	CRStatic	m_IDC_PC_ATTACHED;
//DeadCode JIM 30Oct00 	CRStatic	m_IDC_PC_DETACHED;
	CRStatic	m_IDC_PC_FIGHTERS;
//DeadCode JIM 30Oct00 	CRStatic	m_IDC_PC_RETURNING;
	CRStatic	m_IDC_TARGETS;
	CRButton	m_IDC_TICK_MAINTAIN_PC;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWTaskSummary)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int FindAcSpinEntry(int ac);

	// Generated message map functions
	//{{AFX_MSG(LWTaskSummary)
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedRcombobombertype(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRcombofightertype(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRspinbutBombers(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutFighters(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutSpcAttached(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutSpcDetached(LPCTSTR caption, short Index);
	afx_msg void OnClickedTickMaintainPc();
	afx_msg void OnClose();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
			afx_msg	void	OnSelectTab();
	MSG2(OnSelectTab)	{OnSelectTab();return 0;}

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWTASKSM_H__F8E7C260_9E65_11D3_8ADC_00A0D21BD395__INCLUDED_)
