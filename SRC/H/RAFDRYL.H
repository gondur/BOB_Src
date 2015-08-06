/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rradio.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_RAFDRYL_H__03B97641_9D10_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_RAFDRYL_H__03B97641_9D10_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RAFDryL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RAFDiaryList dialog
class RAFDiaryList : public RowanDialog
{
// Construction
public:
	static RDialog* Make(SquadNum* squadnumptr, int* currentryptr, SquadronBase**	sqdetailsptr);

	RAFDiaryList(SquadNum* squadnumptr,int* currentryptr, SquadronBase**	sqdetailsptr,CWnd* pParent = NULL);   // standard constructor

		int* currentptr;
	SquadNum* sqnumptr;
	SquadronBase** sqdtlsptr;
	void RefreshData(int effect);

// Dialog Data
	//{{AFX_DATA(RAFDiaryList)
	enum { IDD = IDD_RAFDIARYLIST };
	CRRadio	m_IDC_RRADIODISPLAY;
	CRListBox	m_IDC_RLISTBOXCTRL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RAFDiaryList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Refresh();
	void FindDetails();
	// Generated message map functions
	//{{AFX_MSG(RAFDiaryList)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectedRradiodisplay(long ButtonNum);
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAFDRYL_H__03B97641_9D10_11D3_8ADC_00A0D21BD395__INCLUDED_)
