/*
//{{AFX_INCLUDES()
#include "rstatic.h"
#include "rbutton.h"
//}}AFX_INCLUDES
*/

#if !defined(AFX_INTOFF_H__37005B81_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_INTOFF_H__37005B81_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IntOff.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// InterceptOffered dialog

class InterceptOffered : public RowanDialog
{
// Construction
public:
	static RDialog* Make(int pack,int raid);
	UINT	maptimer;
	int		countdown;
	enum	{MAX_REOFFERS=32};
	UWord	ReOffers[MAX_REOFFERS][2];
	int	currreoffer,maxreoffer;
	InterceptOffered(int pack,int raid, CWnd* pParent = NULL);   // standard constructor
	int p, rd;
// Dialog Data
	//{{AFX_DATA(InterceptOffered)
	enum { IDD = IDD_INTERCEPTOFFERED };
	CRStatic	m_IDC_RSTATICINTERCEPTOFFERED;
	CRButton	m_IDC_DONTSHOW;
	CRButton	m_IDC_OK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InterceptOffered)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	CloseOrRedo();
	void	InitDialog();
	void RefreshData(int childnum);
	// Generated message map functions
	//{{AFX_MSG(InterceptOffered)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedDontshow();
	afx_msg void OnClickedFly();
	afx_msg void OnOK();
	afx_msg void OnClickedOk();
	afx_msg void OnClickedCancel();
	afx_msg void OnClickedTask();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTOFF_H__37005B81_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_)
