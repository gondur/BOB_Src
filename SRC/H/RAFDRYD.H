/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rradio.h"
#include "rstatic.h"
#include "rlistbox.h"
#include "rbutton.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_RAFDRYD_H__03B97640_9D10_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_RAFDRYD_H__03B97640_9D10_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RAFDryD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RAFDiaryDetails dialog

class RAFDiaryDetails : public RowanDialog
{
// Construction
public:
	UINT rafdiary_timer;
	static RDialog* Make(SquadNum* squadnumptr, int* currentryptr, SquadronBase**	sqdetailsptr, bool quickmsn);

	RAFDiaryDetails(SquadNum* squadnumptr, int* currentryptr, SquadronBase**	sqdetailsptr, bool quickmsn, CWnd* pParent = NULL);   // standard constructor

	int* currentptr;
	SquadNum* sqnumptr;
	SquadronBase** sqdtlsptr;
	void RefreshData(int effect);
	bool	quickmission;

	enum {PT_LWTOTAL = PT_HE59 - PT_GER_FLYABLE, MAXTYPES = PT_LWTOTAL+1};
	struct	EnemyAc
	{
		int seen;
		int killed;
		int localkilled;
	};

	EnemyAc	enemyac[MAXTYPES];
// Dialog Data
	//{{AFX_DATA(RAFDiaryDetails)
	enum { IDD = IDD_RAFDIARYDETAILS };
	CRButton	m_IDC_RBUTTON_NEXT;
	CRButton	m_IDC_RBUTTON_PREV;
	CRRadio	m_IDC_RRADIODISPLAY;
	CRStatic	m_IDC_RSTATICDIARYDATE;
	CRStatic	m_IDC_RSTATICPERSONNEL;
	CRStatic	m_IDC_RSTATICSTRIKEFORCE;
	CRStatic	m_IDC_RSTATICTASK;
	CRStatic	m_IDC_RSTATICTIME;
	CRStatic	m_IDC_RSTATICDETACHEDFORCE;
	CRStatic	m_IDC_RSTATICDESTROYED;
	CRStatic	m_IDC_RSTATICDAMAGED;
	CRStatic	m_IDC_RSTATICATTACHEDFORCE;
	CRStatic	m_IDC_RSTATICAIRCREW;
	CRListBox	m_IDC_RLISTBOXOTHERS;
	CRStatic	m_IDC_RSTATICINTERCEPT1;
	CRStatic	m_IDC_RSTATICINTERCEPT2;
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRStatic	m_IDC_RSTATICCTRLHURR;
	CRStatic	m_IDC_RSTATICCTRLSPIT;
	CRStatic	m_IDC_RSTATICCTRLTOTAL;
	CRStatic	m_IDC_RSTATICDATE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RAFDiaryDetails)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Refresh();
	void RefreshButtons();
	void TotalUpAc(int& hurr, int& spit, int& total);
	void TotalEncounteredAc();

	// Generated message map functions
	//{{AFX_MSG(RAFDiaryDetails)
	afx_msg void OnSelectedRradiodisplay(long ButtonNum);
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedRbuttonNext();
	afx_msg void OnClickedRbuttonPrev();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnSelectRlistboxothers(long row, long column);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAFDRYD_H__03B97640_9D10_11D3_8ADC_00A0D21BD395__INCLUDED_)
