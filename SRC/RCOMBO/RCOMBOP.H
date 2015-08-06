#if !defined(AFX_RCOMBOP_H__737CB0D8_B42B_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RCOMBOP_H__737CB0D8_B42B_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RComboP.h : Declaration of the CRComboPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRComboPropPage : See RComboP.cpp.cpp for implementation.

class CRComboPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRComboPropPage)
	DECLARE_OLECREATE_EX(CRComboPropPage)

// Constructor
public:
	CRComboPropPage();

// Dialog Data
	//{{AFX_DATA(CRComboPropPage)
	enum { IDD = IDD_PROPPAGE_RCOMBO };
	CComboBox	m_ComboFont;
	long	m_ListboxLength;
	int		m_Style;
	int		m_FontNum;
	BOOL	m_NewJimVar;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRComboPropPage)
	afx_msg void OnSelchangeStylecombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RCOMBOP_H__737CB0D8_B42B_11D1_A1F0_444553540000__INCLUDED)
