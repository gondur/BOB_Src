/*
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rstatic.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_GRPGESCH_H__354A1BA1_8ECF_11D3_8ADB_00A0D21BD395__INCLUDED_)
#define AFX_GRPGESCH_H__354A1BA1_8ECF_11D3_8ADB_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrpGesch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GroupGeschwader dialog

class GroupGeschwader : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	GroupGeschwader(int groupgeschwader, CWnd* pParent = NULL);   // standard constructor
	int group;
// Dialog Data
	//{{AFX_DATA(GroupGeschwader)
	enum { IDD = IDD_GROUP_GESCHWADER };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRStatic	m_IDC_RSTATICCTRL7;
	CRStatic	m_IDC_RSTATICCTRL23;
	CRListBox	m_IDC_RLISTBOXCTRL2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GroupGeschwader)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	enum	{MAX_SEC=15,MAX_AF = 10};
	UniqueID Airfields[MAX_SEC][MAX_AF];
	void FindAirfields();
	int FindSatellites(int afindex, int sectorindex);
	void PrintAirFieldInfo(int j, int i);
	void RefreshRAF();
	void RefreshGr13();

	// Generated message map functions
	//{{AFX_MSG(GroupGeschwader)
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistboxctrl2(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRPGESCH_H__354A1BA1_8ECF_11D3_8ADB_00A0D21BD395__INCLUDED_)
