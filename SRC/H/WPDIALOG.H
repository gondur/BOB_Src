/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rstatic.h"
#include "rcombo.h"
#include "rbutton.h"
#include "rspinbut.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_WPDIALOG_H__84DA9265_9DB3_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_WPDIALOG_H__84DA9265_9DB3_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WPDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// WayPointDialog dialog

class WayPointDialog : public RowanDialog
{
// Construction
public:
	static RDialog* Make();
	enum	{CURRENTRY=100,TABLELEN=100};
	int timeentries[200];
	int* starttimeentries;

	WayPointDialog(CWnd* pParent = NULL);   // standard constructor
	int startperiod;
	int earliesttrgeta,latesttrgeta,earliestgoodeta;
	int	currenteta;
	int currentetaentry;
	int stepsize;
	int steps;
 	static  void ClickedOnInsert();

	static  void ClickedOnDelete();
	static	UniqueID InsertWaypoint(int packnum,UniqueID insertafter,int squadline=-99,int trgline=-99) ;
	static	bool DeleteWayPoint(int packnum,UniqueID u);
	void	MakeTimeEntries(int ETA);


// Dialog Data
	//{{AFX_DATA(WayPointDialog)
	enum { IDD = IDD_WAYPOINT };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRStatic	m_IDC_RSTATICRNGFROM;
	CRStatic	m_IDC_RSTATICRELTOT;
	CRStatic	m_IDC_RSTATICFUEL;
	CRStatic	m_IDC_RSTATICETA;
	CRStatic	m_IDC_RSTATICESCORTFUEL;
	CRStatic	m_IDC_RSTATICBRGFROM;
	CRCombo	m_IDC_RCOMBOALT;
	CRButton	m_IDJ_TITLE;
	CRSpinBut	m_IDC_RSPINETA;
	CRButton	m_IDC_RBUTTONDELETE;
	CRButton	m_IDC_RBUTTONINSERT;
	CRStatic	m_IDC_RSTATICALT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WayPointDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Refresh(bool remakespin=true);
	void RefreshData(int childnum);




	// Generated message map functions
	//{{AFX_MSG(WayPointDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedRbuttonnext();
	afx_msg void OnClickedRbuttoninsert();
	afx_msg void OnClickedRbuttondelete();
	afx_msg void OnClickedRbuttoncentre();
	afx_msg void OnClickedRbuttonprev();
	afx_msg void OnClickedRbuttonroute();
	afx_msg void OnTextChangedRcomboalt(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRspineta(LPCTSTR caption, short Index);
	afx_msg void OnSpinCompletedRspineta();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WPDIALOG_H__84DA9265_9DB3_11D3_8ADC_00A0D21BD395__INCLUDED_)
