/*
//{{AFX_INCLUDES()
#include "rradio.h"
#include "rcombo.h"
#include "rspinbut.h"
#include "rbutton.h"
#include "rstatic.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_RAFDIRECT_H__BD18E220_8F95_11D3_8ADB_00A0D21BD395__INCLUDED_)
#define AFX_RAFDIRECT_H__BD18E220_8F95_11D3_8ADB_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RAFDirect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RAFDirectives dialog

class RAFDirectives : public RowanDialog
{
// Construction
public:
	static RDialog* Make(RAFDirectivesResults* dires);

	RAFDirectives(RAFDirectivesResults* dires,CWnd* pParent = NULL);   // standard constructor
	~RAFDirectives();
	RAFDirectivesResults* dr;

// Dialog Data
	//{{AFX_DATA(RAFDirectives)
	enum { IDD = IDD_RAFDIRECTIVE };
	CRRadio	m_IDC_RRADIOSIZE;
	CRRadio	m_IDC_RRADIO_CONVOYSUPPORT;
	CRCombo	m_IDC_RCOMBOFRONTLINE;
	CRSpinBut	m_IDC_RSPINBUT_INTERCEPTS;
	CRSpinBut	m_IDC_RSPINBUT_GROUP11AF;
	CRSpinBut	m_IDC_RSPINBUT_ACFACTORIES;
	CRSpinBut	m_IDC_RSPINBUT_SUPPLYFACTORIES; 
	CRSpinBut	m_IDC_RSPINBUT_HOLES; 
	CRSpinBut	m_IDC_RSPINBUT_OVERCONVOYS;
	CRSpinBut	m_IDC_RSPINBUT_COASTAL; 
	CRSpinBut	m_IDC_RSPINBUT_CATBELOW;
	CRSpinBut	m_IDC_RSPINBUT_AVAILAC; 
	CRSpinBut	m_IDC_RSPINBUT_INTERCEPTBEFORE;
	CRButton	m_IDC_RBUTTONPROPOSAL;
	CRStatic	m_IDC_RSTATIC_G1012INT;
	CRStatic	m_IDC_RSTATIC_G11INT;
	CRButton	m_IDC_TICK_SR_0;
	CRButton	m_IDC_TICK_SR_1;
	CRButton	m_IDC_TICK_SR_2;
	CRButton	m_IDC_TICK_SR_3;
	CRButton	m_IDC_TICK_SR_4;
	CRButton	m_IDC_TICK_AUTOSCRAMBLE;
	CRButton	m_IDC_TICK_INTERCEPT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RAFDirectives)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//TEMPCODE JIM 07/02/00 		DirectivesResults::TargetList target[DirectivesResults::MAX_TARGETS];
	void Refresh();
//DeadCode RDH 08Feb00 	void	FindSquadsAvail();

//DeadCode RDH 08Feb00 	struct	AvailSquads
//DeadCode RDH 08Feb00 	{
//DeadCode RDH 08Feb00 
//DeadCode RDH 08Feb00 		int gr11radarpatrol;
//DeadCode RDH 08Feb00 		int gr11convoypatrol;
//DeadCode RDH 08Feb00 		int gr11coastalpatrol;
//DeadCode RDH 08Feb00 		int gr11intercept;
//DeadCode RDH 08Feb00 		int gr11total;
//DeadCode RDH 08Feb00 
//DeadCode RDH 08Feb00 		int gr1012afpat;
//DeadCode RDH 08Feb00 		int	gr1012acfactpat;
//DeadCode RDH 08Feb00 		int gr1012supfactpat;
//DeadCode RDH 08Feb00 		int gr1012intercept;
//DeadCode RDH 08Feb00 		int gr1012total;
//DeadCode RDH 08Feb00 
//DeadCode RDH 08Feb00 	};
//DeadCode RDH 08Feb00 	AvailSquads	availsquads;

	// Generated message map functions
	//{{AFX_MSG(RAFDirectives)
	virtual BOOL OnInitDialog();
	afx_msg void OnOK();
	afx_msg void OnCancel();
	afx_msg void OnTextChangedRcombofrontline(LPCTSTR Caption, short index);
	afx_msg void OnClickedReconn();
	afx_msg void OnSelectedRradioConvoysupport(long ButtonNum);
	afx_msg void OnSelectedRradiosize(long ButtonNum);
	afx_msg void OnTextChangedRspinbutAcfactories(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutAvailac(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutCatbelow(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutCoastal(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutGroup11af(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutHoles(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutInterceptbefore(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutOverconvoys(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutSupplyfactories(LPCTSTR caption, short Index);
	afx_msg void OnClickedTickSr(int id);
	afx_msg void OnClickedAutoScramble();
	afx_msg void OnClickedTickIntercept();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAFDIRECT_H__BD18E220_8F95_11D3_8ADB_00A0D21BD395__INCLUDED_)
