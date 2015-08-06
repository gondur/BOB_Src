/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rbutton.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_GAMESELT_H__26F87380_92BC_11D3_8ADB_00A0D21BD395__INCLUDED_)
#define AFX_GAMESELT_H__26F87380_92BC_11D3_8ADB_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameSelt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GameSelect dialog

class GameSelect : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	GameSelect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GameSelect)
	enum { IDD = IDD_GAMESELECT };
	CRButton	m_IDC_COMMANDER;
	CRButton	m_IDC_PILOT;
	CRButton	m_IDC_CANCEL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GameSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GameSelect)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedCommander();
	afx_msg void OnClickedPilot();
	afx_msg void OnClickedCancel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMESELT_H__26F87380_92BC_11D3_8ADB_00A0D21BD395__INCLUDED_)
