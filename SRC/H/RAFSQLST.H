/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rcombo.h"
#include "rspinbut.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_RAFSQLST_H__F3F730E0_9769_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_RAFSQLST_H__F3F730E0_9769_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RAFSqLst.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RAFSquadList dialog

class RAFSquadList : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	RAFSquadList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RAFSquadList)
	enum { IDD = IDD_RAFSQUADLIST };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRCombo	m_IDC_RCOMBOAIRCRAFT;
	CRCombo	m_IDC_RCOMBOGROUP;
	CRCombo	m_IDC_RCOMBOREADINESS;
	CRSpinBut	m_IDC_RSPINBUT_MINAC;
	CRSpinBut	m_IDC_RSPINBUT_MINPILOTS;
	CRSpinBut	m_IDC_RSPINBUT_CAT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RAFSquadList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	enum	{MAX_SQUAD = 100};
	void	RefreshOneLine(int i);
	void	RefreshList();
	int		Squadron[MAX_SQUAD];
	int maxsquads;
  	void	FillList();

	// Generated message map functions
	//{{AFX_MSG(RAFSquadList)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnTextChangedRcomboaircraft(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRcombogroup(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRcomboreadiness(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRspinbutMinac(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutMinpilots(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutCat(LPCTSTR caption, short Index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAFSQLST_H__F3F730E0_9769_11D3_8ADC_00A0D21BD395__INCLUDED_)
