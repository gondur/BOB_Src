/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rstatic.h"
#include "rcombo.h"
#include "rbutton.h"
//}}AFX_INCLUDES

*/

#if !defined(AFX_LWTASKFR_H__F8E7C263_9E65_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_LWTASKFR_H__F8E7C263_9E65_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWTaskFr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWTaskFighter dialog

class LWTaskFighter : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	LWTaskFighter(int acnum,CWnd* pParent = NULL);   // standard constructor
	int attackmethod;
	int tab;
	int maxunits;
	bool me110bomber;
	int unitdisplaylevel;
//DEADCODE RDH 24/03/00 	enum {DISPLAY_GESCHWADER,DISPLAY_GRUPPE, DISPLAY_STAFFEL};
	enum {MAXSQUADS = 100};
	int UnitList[MAXSQUADS];
	bool straf;
// Dialog Data
	//{{AFX_DATA(LWTaskFighter)
	enum { IDD = IDD_LWTASKFIGHTER };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRStatic	m_IDC_RSTATICFIGHTERSALLOCATED;
	CRCombo	m_IDC_RCOMBOFORMATION;
	CRCombo	m_IDC_RCOMBOUNITTYPE;
	CRStatic	m_IDC_RSTATICCTRL00;
	CRStatic	m_IDC_RSTATICCTRL01;
	CRStatic	m_IDC_RSTATICCTRL02;
	CRStatic	m_IDC_RSTATICCTRL03;
	CRStatic	m_IDC_RSTATICCTRL04;
	CRStatic	m_IDC_RSTATICCTRL05;
	CRButton	m_IDC_STRAFTARGET;
	CRButton	m_IDC_TICK1;
	CRButton	m_IDC_TICK2;
	CRButton	m_IDC_TICK3;
	CRButton	m_IDC_TICK4;
	CRButton	m_IDC_TICK5;
	CRButton	m_IDC_TICK6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWTaskFighter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Refresh();
	void RefreshCombos();
	int FindSquad(long index);
	void	FillList();
	void OnClickedTick(int tick); 


	// Generated message map functions
	//{{AFX_MSG(LWTaskFighter)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTextChangedRcomboformation(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRcombounittype(LPCTSTR Caption, short index);
	afx_msg void OnClickedTick1();
	afx_msg void OnClickedTick2();
	afx_msg void OnClickedTick3();
	afx_msg void OnClickedTick4();
	afx_msg void OnClickedTick5();
	afx_msg void OnClickedTick6();
	afx_msg void OnClickedStraftarget();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
		afx_msg	void	OnSelectTab();
	MSG2(OnSelectTab)	{OnSelectTab();return 0;}


	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWTASKFR_H__F8E7C263_9E65_11D3_8ADC_00A0D21BD395__INCLUDED_)
