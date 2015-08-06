#if !defined(AFX_LISTPROP2_H__186D94E4_88B1_11D3_8ADB_00A0D21BD395__INCLUDED_)
#define AFX_LISTPROP2_H__186D94E4_88B1_11D3_8ADB_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListProp2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ListProp2 : Property page dialog

class ListProp2 : public COlePropertyPage
{
	DECLARE_DYNCREATE(ListProp2)
	DECLARE_OLECREATE_EX(ListProp2)

// Constructors
public:
	ListProp2();

// Dialog Data
	//{{AFX_DATA(ListProp2)
	enum { IDD = IDD_PROPPAGE_RLIST_2 };
	CSpinButtonCtrl	m_c0;
	CSpinButtonCtrl	m_c1;
	CSpinButtonCtrl	m_c2;
	CSpinButtonCtrl	m_c3;
	CSpinButtonCtrl	m_c4;
	CSpinButtonCtrl	m_c5;
	CSpinButtonCtrl	m_c6;
	CSpinButtonCtrl	m_c7;
	CSpinButtonCtrl	m_c8;
	CComboBox	m_Icon0;
	CComboBox	m_Icon1;
	CComboBox	m_Icon2;
	CComboBox	m_Icon3;
	CComboBox	m_Icon4;
	CComboBox	m_Icon5;
	CComboBox	m_Icon6;
	CComboBox	m_Icon7;
	CComboBox	m_Icon8;
	int		m_A0;
	int		m_A1;
	int		m_A2;
	int		m_A3;
	int		m_A4;
	int		m_A5;
	int		m_A6;
	int		m_A7;
	int		m_A8;
	int		m_C1;
	int		m_C2;
	int		m_C3;
	int		m_C4;
	int		m_C5;
	int		m_C6;
	int		m_C7;
	int		m_C8;
	int		m_I0;
	int		m_I1;
	int		m_I2;
	int		m_I3;
	int		m_I4;
	int		m_I5;
	int		m_I6;
	int		m_I7;
	int		m_I8;
	int		m_C0;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(ListProp2)
	afx_msg void OnChangeEditcolumn0();
	afx_msg void OnKillfocusEditcolumn0();
	afx_msg void OnUpdateEditcolumn0();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTPROP2_H__186D94E4_88B1_11D3_8ADB_00A0D21BD395__INCLUDED_)
