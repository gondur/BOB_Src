/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rcombo.h"
#include "rstatic.h"
//}}AFX_INCLUDES

*/


#if !defined(AFX_LWTASKAC_H__F8E7C262_9E65_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_LWTASKAC_H__F8E7C262_9E65_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWTaskAc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWTaskAircraft dialog

class LWTaskAircraft : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	LWTaskAircraft(int acnum,CWnd* pParent = NULL);   // standard constructor
 	int attackmethod;
	int maxunits;
	int unitdisplaylevel;
	enum {DISPLAY_GESCHWADER,DISPLAY_GRUPPE, DISPLAY_STAFFEL};
	bool me110bomber;
	enum {MAXSQUADS = 100};
	int UnitList[MAXSQUADS];
// Dialog Data
	//{{AFX_DATA(LWTaskAircraft)
	enum { IDD = IDD_LWTASKAIRCRAFT };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRCombo	m_IDC_RCOMBOATTACKMETHOD;
	CRCombo	m_IDC_RCOMBOBOMBERTYPE;
	CRStatic	m_IDC_RSTATICBOMBERSALLOCATED;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWTaskAircraft)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	 int FindSquad(long index);
	 	void Refresh();
	void	FillList();

	// Generated message map functions
	//{{AFX_MSG(LWTaskAircraft)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnTextChangedRcombobombertype(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRcomboattackmethod(LPCTSTR Caption, short index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
		afx_msg	void	OnSelectTab();
	MSG2(OnSelectTab)	{OnSelectTab();return 0;}


	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWTASKAC_H__F8E7C262_9E65_11D3_8ADC_00A0D21BD395__INCLUDED_)
