/*
//{{AFX_INCLUDES()
#include "rstatic.h"
#include "rbutton.h"
#include "rcombo.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_SQUADDTL_H__27AE24C1_8E23_11D3_8ADB_00A0D21BD395__INCLUDED_)
#define AFX_SQUADDTL_H__27AE24C1_8E23_11D3_8ADB_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SquadDtl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SquadronDetails dialog
enum	SquadNum;
class SquadronDetails : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	SquadronDetails(SquadNum squadnum, CWnd* pParent = NULL);   // standard constructor
	SquadNum sqnum;
	int group;
	int afindex;
	bool movedalready;
// Dialog Data
	//{{AFX_DATA(SquadronDetails)
	enum { IDD = IDD_SQUADRONDETAILS };
	CRStatic	m_IDC_RSTATICLDR;
	CRStatic	m_IDC_RSTATICLDRMORALE;
	CRStatic	m_IDC_RSTATICACTYPE;
	CRStatic	m_IDC_RSTATICACAVAIL;
	CRStatic	m_IDC_RSTATICACTIVITY;
	CRStatic	m_IDC_RSTATICAIRFIELD;
	CRStatic	m_IDC_RSTATICATKPATT;
	CRStatic	m_IDC_RSTATICCR;
	CRStatic	m_IDC_RSTATICFORMATION;
	CRStatic	m_IDC_RSTATICNOPILOTS;
	CRStatic	m_IDC_RSTATICSQUADMORALE;
	CRStatic	m_IDC_RSTATICSQUADSTATUS;
	CRButton	m_IDC_RBUTTONSQUADRON;
	CRStatic	m_IDC_RSTATICCTRL53;
	CRStatic	m_IDC_RSTATICCTRL54;
	CRStatic	m_IDC_RSTATICCTRL70;
	CRStatic	m_IDC_RSTATICCTRL71;
	CRCombo	m_IDC_RCOMBOREQUIRED;
	CRCombo	m_IDC_RCOMBOAIRFIELD;
	CRCombo	m_IDC_RCOMBOGROUP;
	CRStatic	m_IDC_RSTATICMOVETO;
	CRButton	m_IDC_RBUTTONAIRFIELD;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SquadronDetails)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	enum	{MAX_GROUPS = 4, MAX_AF = 100};
	UniqueID Airfields[MAX_AF];
	int		Groups[MAX_GROUPS];

	bool CheckSatellites( int sectorindex, UniqueID afuid);
	int FindAirfieldGroup(UniqueID afuid);
	int FillAirfieldList();
	void Refresh();

	// Generated message map functions
	//{{AFX_MSG(SquadronDetails)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedRbuttonsquadron();
	afx_msg void OnClickedRbuttonairfield();
	afx_msg void OnTextChangedRcomborequired(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRcombogroup(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRcomboairfield(LPCTSTR Caption, short index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
		afx_msg	void	OnSelectTab();
	MSG2(OnSelectTab)	{OnSelectTab();return 0;}

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQUADDTL_H__27AE24C1_8E23_11D3_8ADB_00A0D21BD395__INCLUDED_)
