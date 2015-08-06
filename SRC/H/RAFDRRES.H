/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_RAFDRRES_H__E9069380_DC90_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_RAFDRRES_H__E9069380_DC90_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RAFDrRes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RAFDirectiveResults dialog

class RAFDirectiveResults : public RowanDialog
{
// Construction
public:
	static RDialog* Make(RAFDirectivesResults* dires);

	RAFDirectiveResults(RAFDirectivesResults* dires,CWnd* pParent = NULL);   // standard constructor
	~RAFDirectiveResults();   // standard constructor

	RAFDirectivesResults* dr;

// Dialog Data
	//{{AFX_DATA(RAFDirectiveResults)
	enum { IDD = IDD_RAFDIRECTIVERESULTS };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RAFDirectiveResults)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	Refresh();
//DEADCODE RDH 02/03/00 	static int AirfieldSuitable(int afnum, Target::Location loc0, Target::Location loc1, Target::Location loc2);
//DEADCODE RDH 02/03/00 	static void MoveSquadron(int sqnum, Target::Location loc0, Target::Location loc1, Target::Location loc2);
//DEADCODE RDH 02/06/00 	void MoveSquadron(int sqnum,  int loc0, int loc1, int loc2);
//DEADCODE RDH 02/06/00 	int FindAirfield(int priority, int maxaf);



	// Generated message map functions
	//{{AFX_MSG(RAFDirectiveResults)
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	virtual BOOL OnInitDialog();
	afx_msg void OnOK();
	afx_msg void OnCancel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAFDRRES_H__E9069380_DC90_11D3_8ADC_00A0D21BD395__INCLUDED_)
