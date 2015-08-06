/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rbutton.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_HOSTILES_H__927E6B40_95C9_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_HOSTILES_H__927E6B40_95C9_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Hostiles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// HostilesList dialog

class HostilesList : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	HostilesList(CWnd* pParent = NULL);   // standard constructor
		int currpack;
 	enum	{MAX_PACKLIST = 300};
	struct	Pack
	{
		UWord	pack;
		UWord	raidline;
		UniqueID	target;
		UByte	method;
		UWord	numofac;
		int strikegruppe;
		int escortgruppe;
		int		takeofftime;
	};
  	Pack	packlist[MAX_PACKLIST+1];
	int currpacklist;

// Dialog Data
	//{{AFX_DATA(HostilesList)
	enum { IDD = IDD_HOSTILESLIST };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRButton	m_IDC_RBUTTONAUTHORISE;
	CRButton	m_IDC_RBUTTONASSIGNPATROL;
	CRButton	m_IDC_RBUTTONINTELL;
	CRButton	m_IDC_RBUTTONMISSIONFOLDER;
	CRButton	m_IDC_ATTARGET;
	CRButton	m_IDC_FORMING;
	CRButton	m_IDC_INCOMING;
	CRButton	m_IDC_RAID_ENGAGED;
	CRButton	m_IDC_ENGAGED;
	CRButton	m_IDC_NORESPONSE;
	CRButton	m_IDC_OUTGOING;
	CRButton	m_IDC_RESPONSES;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HostilesList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FindPackages();
	void FillPackList(UWord	pack, UWord raidline, UniqueID	target, UByte method, UWord numofac, int takeofftime, int strikegruppe, int  escortgruppe);
	void RefreshList();
	void TotalRefresh();
	void RefreshTickBoxes();
	FileNum GetIconFileNum(UniqueID uid);
	void RefreshButtons();
	void FindHiLight();
//DEADCODE RDH 06/06/00 	bool Response(int pack, int firstsq);
	bool CorrectSquad(int pack);
	void FindKillsandAcNumbers(int pack, int raid, int& acleft, int& kills, int& acincoming, int& acengaged, int& acoutgoing);
	int FindNearestPack(int pack,int psmin,int psmax);	//inclusive package statuses
	void RefreshData(int childnum);



	// Generated message map functions
	//{{AFX_MSG(HostilesList)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedRbuttonassignpatrol();
	afx_msg void OnClickedRbuttonauthorise();
	afx_msg void OnClickedRbuttonintell();
	afx_msg void OnClickedRbuttonmissionfolder();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnClickedAttarget();
	afx_msg void OnClickedEngaged();
	afx_msg void OnClickedForming();
	afx_msg void OnClickedIncoming();
	afx_msg void OnClickedNoresponse();
	afx_msg void OnClickedNotengaged();
	afx_msg void OnClickedOutgoing();
	afx_msg void OnClickedResponses();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOSTILES_H__927E6B40_95C9_11D3_8ADC_00A0D21BD395__INCLUDED_)
