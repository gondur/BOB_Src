/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rcombo.h"
#include "rspinbut.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_GWADLIST_H__D7431D00_B6D7_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_GWADLIST_H__D7431D00_B6D7_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GWadlist.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GeschwaderList dialog

class GeschwaderList : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	GeschwaderList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GeschwaderList)
	enum { IDD = IDD_LWGESCHWADERLIST };
	CRCombo	m_IDC_RCOMBOGESCHWADER;
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRCombo	m_IDC_RCOMBOFLOTTE;
	CRSpinBut	m_IDC_RSPINBUT_MINAC;
	CRSpinBut	m_IDC_RSPINBUT_CAT;
	CRSpinBut	m_IDC_RSPINBUT_MINPILOTS;
	CRCombo	m_IDC_RCOMBOREADINESS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GeschwaderList)
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
	//{{AFX_MSG(GeschwaderList)
	afx_msg void OnTextChangedRspinbutMinpilots(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutMinac(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutCat(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRcomboreadiness(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRcombogeschwader(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRcomboflotte(LPCTSTR Caption, short index);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GWADLIST_H__D7431D00_B6D7_11D3_8ADC_00A0D21BD395__INCLUDED_)
