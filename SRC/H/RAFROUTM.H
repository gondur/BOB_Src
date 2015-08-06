//DeadCode DAW 26Jun00 /* STOP AFX_INCLUDES
//DeadCode DAW 26Jun00 //{{AFX_INCLUDES()
//DeadCode DAW 26Jun00 #include "rlistbox.h"
//DeadCode DAW 26Jun00 #include "rbutton.h"
//DeadCode DAW 26Jun00 //}}AFX_INCLUDES
//DeadCode DAW 26Jun00 */
//DeadCode DAW 26Jun00 #if !defined(AFX_RAFROUTM_H__84DA9262_9DB3_11D3_8ADC_00A0D21BD395__INCLUDED_)
//DeadCode DAW 26Jun00 #define AFX_RAFROUTM_H__84DA9262_9DB3_11D3_8ADC_00A0D21BD395__INCLUDED_
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 #if _MSC_VER > 1000
//DeadCode DAW 26Jun00 #pragma once
//DeadCode DAW 26Jun00 #endif // _MSC_VER > 1000
//DeadCode DAW 26Jun00 // RAFRoutM.h : header file
//DeadCode DAW 26Jun00 //
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 /////////////////////////////////////////////////////////////////////////////
//DeadCode DAW 26Jun00 // RAFRouteMain dialog
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 class RAFRouteMain : public RowanDialog
//DeadCode DAW 26Jun00 {
//DeadCode DAW 26Jun00 // Construction
//DeadCode DAW 26Jun00 public:
//DeadCode DAW 26Jun00 	static RDialog* Make();
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 	RAFRouteMain(CWnd* pParent = NULL);   // standard constructor
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 // Dialog Data
//DeadCode DAW 26Jun00 	//{{AFX_DATA(RAFRouteMain)
//DeadCode DAW 26Jun00 	enum { IDD = IDD_RAFROUTEMAIN };
//DeadCode DAW 26Jun00 	CRListBox	m_IDC_RLISTBOXCTRL1;
//DeadCode DAW 26Jun00 	CRButton	m_IDC_RBUTTONINSERT;
//DeadCode DAW 26Jun00 	CRButton	m_IDC_RBUTTONDELETE;
//DeadCode DAW 26Jun00 	CRButton	m_IDC_RBUTTONCENTRE;
//DeadCode DAW 26Jun00 	CRButton	m_IDC_RBUTTONAPPLYALT;
//DeadCode DAW 26Jun00 	//}}AFX_DATA
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 // Overrides
//DeadCode DAW 26Jun00 	// ClassWizard generated virtual function overrides
//DeadCode DAW 26Jun00 	//{{AFX_VIRTUAL(RAFRouteMain)
//DeadCode DAW 26Jun00 	protected:
//DeadCode DAW 26Jun00 	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//DeadCode DAW 26Jun00 	//}}AFX_VIRTUAL
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 // Implementation
//DeadCode DAW 26Jun00 protected:
//DeadCode DAW 26Jun00 	void	RefreshList();
//DeadCode DAW 26Jun00 	void	RefreshButtons();
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 	// Generated message map functions
//DeadCode DAW 26Jun00 	//{{AFX_MSG(RAFRouteMain)
//DeadCode DAW 26Jun00 	virtual BOOL OnInitDialog();
//DeadCode DAW 26Jun00 	afx_msg void OnSelectRlistboxctrl1(long row, long column);
//DeadCode DAW 26Jun00 	afx_msg void OnClickedRbuttonapplyalt();
//DeadCode DAW 26Jun00 	afx_msg void OnClickedRbuttoncentre();
//DeadCode DAW 26Jun00 	afx_msg void OnClickedRbuttondelete();
//DeadCode DAW 26Jun00 	afx_msg void OnClickedRbuttoninsert();
//DeadCode DAW 26Jun00 	DECLARE_EVENTSINK_MAP()
//DeadCode DAW 26Jun00 	//}}AFX_MSG
//DeadCode DAW 26Jun00 		afx_msg	void	OnSelectTab();
//DeadCode DAW 26Jun00 	MSG2(OnSelectTab)	{OnSelectTab();return 0;}
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 	DECLARE_MESSAGE_MAP()
//DeadCode DAW 26Jun00 };
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 //{{AFX_INSERT_LOCATION}}
//DeadCode DAW 26Jun00 // Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 #endif // !defined(AFX_RAFROUTM_H__84DA9262_9DB3_11D3_8ADC_00A0D21BD395__INCLUDED_)
