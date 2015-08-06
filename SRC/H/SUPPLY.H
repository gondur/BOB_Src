/*
//{{AFX_INCLUDES()
#include "rbutton.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_SUPPLY_H__7CC731A1_CA3D_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SUPPLY_H__7CC731A1_CA3D_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Supply.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSupply dialog
//DEADCODE  08/02/00 struct	LWDirectivesResultsTargetList;
class CSupply : public RowanDialog
{
// Construction
public:
	CSupply(int index,CWnd* pParent = NULL);   // standard constructor
	~CSupply();
 	int sortindex;
	int currrow;

	int panel;
// Dialog Data
	//{{AFX_DATA(CSupply)
	enum { IDD = IDD_TRG_ASSET_LIST };
	CRStatic	m_IDC_RSTATICCTRL2;
	CRCombo	m_IDC_SORTCOMBO;
	CRListBox	m_IDC_RLISTBOXCTRL1;
//	CRButton	m_IDC_AUTHORISE;
//	CRButton	m_IDC_DOSSIER;
	CRButton	m_IDC_RBUTTONAUTHORISE;
	CRButton	m_IDC_RBUTTONDETAILS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSupply)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//TEMPCODE JIM 07/02/00 	DirectivesResults::TargetList target[DirectivesResults::MAX_TARGETS];
	LWDirectivesResults*		dr;
//DEADCODE  08/02/00 	LWDirectivesResultsTargetList*	target;
//	int	 FillPanel(LWDirectivesResults::TargetList* target, int panel);
	int	 FillPanel(int panel);

//DEADCODE JIM 16/12/99 	void SortSupplyNodes();
//DEADCODE JIM 16/12/99 	void AddSupplyMission(int j, SupplyNode*  currnode);
//DEADCODE JIM 16/12/99 	void SortChokes();
//DEADCODE JIM 16/12/99 	void SortTraffic();
//DEADCODE JIM 16/12/99 	void SortAirfields();
//DEADCODE JIM 16/12/99 	void SortArmy();
//DEADCODE JIM 16/12/99 	void SortIntell();
	void ReDraw(int	numoftargets);
//	int	InsertTarget(UniqueID uid, int currtrg);

//DEADCODE JIM 16/12/99 	void AddChokeMission(int j, SupplyRoute*  currroute);
//DEADCODE JIM 16/12/99 	void AddArmyMission(int j, SupplyNode*  currnode);
//DEADCODE JIM 16/12/99 	void AddAirfieldsMission(int j, int af, int score);
//DEADCODE JIM 16/12/99 	void AddTrafficMission(int j, SupplyRoute*  currroute);
	void ReDrawButtons();



	// Generated message map functions
	//{{AFX_MSG(CSupply)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedDossier();
	afx_msg void OnTextChangedSortcombo(LPCTSTR text, short index);
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnClickedAuthorise();
	afx_msg void OnClose();
	afx_msg void OnClickedRbuttondetails();
	afx_msg void OnClickedRbuttonauthorise();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPPLY_H__7CC731A1_CA3D_11D1_A5A3_0040052179B6__INCLUDED_)
