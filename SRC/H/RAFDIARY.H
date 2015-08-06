/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rcombo.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_RAFDIARY_H__92B1C000_9D0B_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_RAFDIARY_H__92B1C000_9D0B_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RAFDiary.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RAFDiary dialog
class	SquadronBase;

class RAFDiary : public RowanDialog
{
// Construction
public:
	static RDialog* Make(SquadNum squad);

	RAFDiary(CWnd* pParent = NULL);   // standard constructor

		enum	{MAX_SQDETAILS = 100};
	int currentry;
	int* currentryptr;
	SquadNum* sqnumptr;
	SquadNum sqnum;
	SquadronBase*	sqdetails[MAX_SQDETAILS];
	SquadronBase**	sqdetailsptr;	
	int group;
	enum	{MAX_SQUAD = 100};
	int		Squadron[MAX_SQUAD];
	int maxsquads;
  	void	FillList();


// Dialog Data
	//{{AFX_DATA(RAFDiary)
	enum { IDD = IDD_RAFDIARY };
	CRCombo	m_IDC_RCOMBOSQUAD;
	CRCombo	m_IDC_RCOMBOGROUP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RAFDiary)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
   	void	RefreshData(int effect);
	void	FindGroup();
public:
	static void	FillSquadronDetails(SquadNum sqnum,SquadronBase* indexer,SquadronBase** sqdetails,int& currentry);

// Implementation
protected:
	void Refresh();
	// Generated message map functions
	//{{AFX_MSG(RAFDiary)
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedRcombogroup(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRcombosquad(LPCTSTR Caption, short index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAFDIARY_H__92B1C000_9D0B_11D3_8ADC_00A0D21BD395__INCLUDED_)
