//DeadCode DAW 09Feb00 /*
//DeadCode DAW 09Feb00 //{{AFX_INCLUDES()
//DeadCode DAW 09Feb00 
//DeadCode DAW 09Feb00 //}}AFX_INCLUDES
//DeadCode DAW 09Feb00 */
//DeadCode DAW 09Feb00 #ifndef SREPLAY_INCLUDED
//DeadCode DAW 09Feb00 #pragma once
//DeadCode DAW 09Feb00 #define SREPLAY_INCLUDED
//DeadCode DAW 09Feb00 //#include "..\h\SREPLAY.H"
//DeadCode DAW 09Feb00 
//DeadCode DAW 09Feb00 /////////////////////////////////////////////////////////////////////////////
//DeadCode DAW 09Feb00 // CReplay dialog
//DeadCode DAW 09Feb00 
//DeadCode DAW 09Feb00 class CSReplay : public RowanDialog
//DeadCode DAW 09Feb00 {
//DeadCode DAW 09Feb00 // Construction
//DeadCode DAW 09Feb00 public:
//DeadCode DAW 09Feb00 	CSReplay(CWnd* pParent = NULL);   // standard constructor
//DeadCode DAW 09Feb00 
//DeadCode DAW 09Feb00 // Dialog Data
//DeadCode DAW 09Feb00 	//{{AFX_DATA(CReplay)
//DeadCode DAW 09Feb00 	enum { IDD = IDDX_SREPLAY };
//DeadCode DAW 09Feb00 		// NOTE: the ClassWizard will add data members here
//DeadCode DAW 09Feb00 	CREdit	m_IDC_REDITCTRL1;
//DeadCode DAW 09Feb00 	//}}AFX_DATA
//DeadCode DAW 09Feb00 
//DeadCode DAW 09Feb00 
//DeadCode DAW 09Feb00 // Overrides
//DeadCode DAW 09Feb00 	// ClassWizard generated virtual function overrides
//DeadCode DAW 09Feb00 	//{{AFX_VIRTUAL(CReplay)
//DeadCode DAW 09Feb00 	protected:
//DeadCode DAW 09Feb00 	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//DeadCode DAW 09Feb00 
//DeadCode DAW 09Feb00 	//}}AFX_VIRTUAL
//DeadCode DAW 09Feb00 
//DeadCode DAW 09Feb00 // Implementation
//DeadCode DAW 09Feb00 protected:
//DeadCode DAW 09Feb00 
//DeadCode DAW 09Feb00 	// Generated message map functions
//DeadCode DAW 09Feb00 	//{{AFX_MSG(CReplay)
//DeadCode DAW 09Feb00 	virtual BOOL OnInitDialog();
//DeadCode DAW 09Feb00 	//}}AFX_MSG
//DeadCode DAW 09Feb00 	DECLARE_MESSAGE_MAP()
//DeadCode DAW 09Feb00 };
//DeadCode DAW 09Feb00 #endif
