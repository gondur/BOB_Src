/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rbutton.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_RAFMSSFR_H__9FF3FD20_9B51_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_RAFMSSFR_H__9FF3FD20_9B51_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RAFMssFr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RAFMissionFolder dialog

class RAFMissionFolder : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	RAFMissionFolder(CWnd* pParent = NULL);   // standard constructor
	 	enum	{MAX_PACKLIST = 300};

	int currpack;
 
	struct	Pack
	{
		UWord	pack;
		SByte	target;
		UByte	method;
		UWord	numofac;
		UWord squadron;
		int		takeofftime;
		int		sqnum;
	};
  	Pack	packlist[MAX_PACKLIST+1];
	int currpacklist;


// Dialog Data
	//{{AFX_DATA(RAFMissionFolder)
	enum { IDD = IDD_RAFMISSIONFOLDER };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRButton m_IDC_RBUTTONTASK;
	CRButton m_IDC_RBUTTONROUTE;
	CRButton m_IDC_RBUTTONRTB;
	CRButton m_IDC_RBUTTONSQUADRON;
	CRButton m_IDC_RBUTTONINTELL;
	CRButton m_IDC_RBUTTONDELETE;
	CRButton	m_IDC_PLANNED;
	CRButton	m_IDC_ENGAGING;
	CRButton	m_IDC_INCOMING;
	CRButton	m_IDC_LANDED;
	CRButton	m_IDC_OUTGOING;
	CRButton	m_IDC_RBUTTONFRAG;
	CRButton	m_IDC_INTERCEPTS;
	CRButton	m_IDC_PATROLS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RAFMissionFolder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
		void FindPackages();
	void FillPackList(UWord	pack, UByte	target, UByte method, UWord numofac, int takeofftime, UWord squadron, int sqnum);
	void RefreshList();
	void RefreshButtons();
	void FindHiLight();
	void RefreshTickBoxes();
	void TotalRefresh();
	void ChildDialClosed(int dialnum,RDialog*,int rv);
 	void RefreshData(int childnum);


	// Generated message map functions
	//{{AFX_MSG(RAFMissionFolder)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedRbuttonroute();
	afx_msg void OnClickedRbuttontask();
	afx_msg void OnClickedRbuttondelete();
	afx_msg void OnClickedRbuttonintell();
	afx_msg void OnClickedRbuttonsquadron();
	afx_msg void OnClickedRbuttonrtb();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnClickedOutgoing();
	afx_msg void OnClickedLanded();
	afx_msg void OnClickedIncoming();
	afx_msg void OnClickedEngaging();
	afx_msg void OnClickedPlanned();
	afx_msg void OnClickedRbuttonfrag();
	afx_msg void OnClickedPatrols();
	afx_msg void OnClickedIntercepts();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAFMSSFR_H__9FF3FD20_9B51_11D3_8ADC_00A0D21BD395__INCLUDED_)
