/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rbutton.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_LWMSSFR_H__CA1747A0_9C01_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_LWMSSFR_H__CA1747A0_9C01_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWMssFr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWMissionFolder dialog

class LWMissionFolder : public RowanDialog
{
// Construction
public:
	static RDialog* Make(bool specialnotakeoffs=false);

	LWMissionFolder(bool specialnotakeoffs=false,CWnd* pParent = NULL);   // standard constructor
	bool	specialnotakeoffs;	
	int currpack;
 	enum	{MAX_PACKLIST = 300};
	struct	Pack
	{
		UWord	pack;
		SByte	target;
		UByte	method;
		UWord	numofac;
		UWord	numofacleft;
		UWord gruppe;
		int		takeofftime;
	};
  	Pack	packlist[MAX_PACKLIST+1];
	int currpacklist;

// Dialog Data
	//{{AFX_DATA(LWMissionFolder)
	enum { IDD = IDD_LWMISSIONFOLDER };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRButton	m_IDC_RBUTTONROUTE;
	CRButton	m_IDC_RBUTTONSQUADRON;
	CRButton	m_IDC_RBUTTONTASK;
	CRButton	m_IDC_RBUTTONINTELL;
	CRButton	m_IDC_RBUTTONDELETE;
	CRButton	m_IDC_ACTIVE;
	CRButton	m_IDC_ESCORT;
	CRButton	m_IDC_LANDED;
	CRButton	m_IDC_PLANNED;
	CRButton	m_IDC_RECONN;
	CRButton	m_IDC_STRIKE;
	CRButton	m_IDC_SWEEP;
	CRButton	m_IDC_RBUTTONFRAG;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWMissionFolder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FindPackages();
	int FillPackList(UWord	pack, UByte	target, UByte method, UWord numofac, int takeofftime, UWord gruppe, UWord numofacleft);
	void RefreshList();
	void RefreshButtons();
	void FindHiLight();
	void RefreshTickBoxes();
	void TotalRefresh();
	int FindAssociatedRAFPackInfo(UniqueID lwuid, int& acorg, int& acleft);
	void RefreshData(int childnum);


	// Generated message map functions
	//{{AFX_MSG(LWMissionFolder)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedRbuttonintell();
	afx_msg void OnClickedRbuttonroute();
	afx_msg void OnClickedRbuttonsquadron();
	afx_msg void OnClickedRbuttontask();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnClickedRbuttonrespond();
	afx_msg void OnClickedStrike();
	afx_msg void OnClickedSweep();
	afx_msg void OnClickedPlanned();
	afx_msg void OnClickedActive();
	afx_msg void OnClickedEscort();
	afx_msg void OnClickedLanded();
	afx_msg void OnClickedReconn();
	afx_msg void OnClickedRbuttondelete();
	afx_msg void OnClickedRbuttonfrag();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWMSSFR_H__CA1747A0_9C01_11D3_8ADC_00A0D21BD395__INCLUDED_)
