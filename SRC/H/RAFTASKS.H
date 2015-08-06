/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rspinbut.h"
#include "rstatic.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_RAFTASKS_H__FEDF9602_9EA3_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_RAFTASKS_H__FEDF9602_9EA3_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RAFTaskS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RAFTaskSummary dialog

class RAFTaskSummary : public RowanDialog
{
// Construction
public:
	static RDialog* Make();
	UByte	actypeoptions[4];
	int		rafdirectivemisstype;
	RAFTaskSummary(CWnd* pParent = NULL);   // standard constructor

	enum{ WINGMAX = 3, MIXWINGMAX=6, SQUADMAX = 4};
	struct	WingInfo
	{
		int		numoutput;
		int		number;
		int		name;
	};

	static WingInfo winginfo[MIXWINGMAX];
	struct	SquadInfo
	{
		int		numoutput;
		int		number;
		int		name;
	};

	static SquadInfo squadinfo[SQUADMAX];

// Dialog Data
	//{{AFX_DATA(RAFTaskSummary)
	enum { IDD = IDD_RAFTASKSUMMARY };
	CRSpinBut	m_IDC_RSPINBUT_HURRICANES;
	CRCombo		m_IDC_RSPINBUT_SPITFIRES;
	CRStatic	m_IDC_RSTATICTOTAL;
	CRStatic	m_IDC_TEMPLATE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RAFTaskSummary)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Refresh();

	// Generated message map functions
	//{{AFX_MSG(RAFTaskSummary)
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedRspinbutHurricanes(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutSpitfires(LPCTSTR caption, short Index);
	afx_msg void OnClose();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
		afx_msg	void	OnSelectTab();
	MSG2(OnSelectTab)	{OnSelectTab();return 0;}

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAFTASKS_H__FEDF9602_9EA3_11D3_8ADC_00A0D21BD395__INCLUDED_)
