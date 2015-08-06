/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rcombo.h"
#include "rstatic.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_RAFTASKF_H__FEDF9601_9EA3_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_RAFTASKF_H__FEDF9601_9EA3_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RAFTaskF.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RAFTaskFighter dialog

class RAFTaskFighter : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	RAFTaskFighter(int acnum,CWnd* pParent = NULL);   // standard constructor
	int 	attackmethod;
	int tab;
		int maxunits;
		enum	{DISPLAY_SQUADRON, DISPLAY_FLIGHT, DISPLAY_SECTION};
	int unitdisplaylevel;
	enum {MAXSQUADS = 100};
	int UnitList[MAXSQUADS];

// Dialog Data
	//{{AFX_DATA(RAFTaskFighter)
	enum { IDD = IDD_RAFTASKFIGHTER };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRCombo	m_IDC_RCOMBOPREFERREDTARGET;
	CRCombo	m_IDC_RCOMBOATTACKMETHOD;
//DEADCODE RDH 10/04/00 	CRCombo	m_IDC_RCOMBOUNITTYPE;
	CRCombo	m_IDC_RCOMBOFORMATION;
	CRStatic	m_IDC_RSTATICFIGHTERSALLOCATED;
	CRStatic	m_IDC_RSTATICFORMATION;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RAFTaskFighter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Refresh();
	 int FindSquad(long index);
	bool FindAssociatedLWPack(UniqueID raftrg, int& pack, int& sq);
	void FillList();


	// Generated message map functions
	//{{AFX_MSG(RAFTaskFighter)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnTextChangedRcombopreferredtarget(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRcomboattackmethod(LPCTSTR Caption, short index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg	void	OnSelectTab();
	MSG2(OnSelectTab)	{OnSelectTab();return 0;}


	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAFTASKF_H__FEDF9601_9EA3_11D3_8ADC_00A0D21BD395__INCLUDED_)
