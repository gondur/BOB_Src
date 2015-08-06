//DeadCode DAW 26Jun00 /*
//DeadCode DAW 26Jun00 //{{AFX_INCLUDES()
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 //}}AFX_INCLUDES
//DeadCode DAW 26Jun00 */
//DeadCode DAW 26Jun00 #if !defined(AFX_FRAGPILT_H__035ACCE1_100C_11D2_A5A3_0040052179B6__INCLUDED_)
//DeadCode DAW 26Jun00 #define AFX_FRAGPILT_H__035ACCE1_100C_11D2_A5A3_0040052179B6__INCLUDED_
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 #if _MSC_VER >= 1000
//DeadCode DAW 26Jun00 #pragma once
//DeadCode DAW 26Jun00 #endif // _MSC_VER >= 1000
//DeadCode DAW 26Jun00 // FragPilt.h : header file
//DeadCode DAW 26Jun00 //
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 /////////////////////////////////////////////////////////////////////////////
//DeadCode DAW 26Jun00 // CFragPilot dialog
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 class CFragPilot : public RowanDialog
//DeadCode DAW 26Jun00 {
//DeadCode DAW 26Jun00 // Construction
//DeadCode DAW 26Jun00 public:
//DeadCode DAW 26Jun00 	CFragPilot(int*pack,CWnd* pParent = NULL);   // standard constructor
//DeadCode DAW 26Jun00 	int squadnum,squadflight;
//DeadCode DAW 26Jun00 	void	PrintPilotNames();									//AMM 17Nov98
//DeadCode DAW 26Jun00 // Dialog Data
//DeadCode DAW 26Jun00 	//{{AFX_DATA(CFragPilot)
//DeadCode DAW 26Jun00 	enum { IDD = IDDX_FRAGPILT };
//DeadCode DAW 26Jun00 		// NOTE: the ClassWizard will add data members here
//DeadCode DAW 26Jun00 	CRStatic	m_IDC_FRAG_ROLE;
//DeadCode DAW 26Jun00 	CRStatic	m_IDC_FRAG_ID;
//DeadCode DAW 26Jun00 	CRStatic	m_IDC_FRAG_WAVE;
//DeadCode DAW 26Jun00 	CRCombo	m_IDC_FRAG_CALLNAME;
//DeadCode DAW 26Jun00 	CREdtBt	m_IDC_PLAYERCHAT;
//DeadCode DAW 26Jun00 	CREdtBt	m_IDC_PLAYERCHAT2;
//DeadCode DAW 26Jun00 	CREdtBt	m_IDC_PLAYERCHAT3;
//DeadCode DAW 26Jun00 	CREdtBt	m_IDC_PLAYERCHAT4;
//DeadCode DAW 26Jun00 	//}}AFX_DATA
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 // Overrides
//DeadCode DAW 26Jun00 	// ClassWizard generated virtual function overrides
//DeadCode DAW 26Jun00 	//{{AFX_VIRTUAL(CFragPilot)
//DeadCode DAW 26Jun00 	protected:
//DeadCode DAW 26Jun00 	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//DeadCode DAW 26Jun00 	//}}AFX_VIRTUAL
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 // Implementation
//DeadCode DAW 26Jun00 protected:
//DeadCode DAW 26Jun00 	void	EndDialog( int nResult );
//DeadCode DAW 26Jun00 //	bool	beenselected;
//DeadCode DAW 26Jun00 	void	FillComboBox();
//DeadCode DAW 26Jun00 	BOOL	UniqueCallNameOrThisGroups(char callname);
//DeadCode DAW 26Jun00 	void	FindCallName(char index);
//DeadCode DAW 26Jun00 	void	OnClickedPlayer(int acinflight);
//DeadCode DAW 26Jun00 //DeadCode AMM 17Nov98 	void	PrintPilotNames();
//DeadCode DAW 26Jun00 	bool	CommsPlayer(int pos, int& i);
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 	// Generated message map functions
//DeadCode DAW 26Jun00 	//{{AFX_MSG(CFragPilot)
//DeadCode DAW 26Jun00 	virtual BOOL OnInitDialog();
//DeadCode DAW 26Jun00 	afx_msg void OnTextChangedFragCallname(LPCTSTR text, short index);
//DeadCode DAW 26Jun00 	afx_msg void OnClickedPlayerchat();
//DeadCode DAW 26Jun00 	afx_msg void OnClickedPlayerchat3();
//DeadCode DAW 26Jun00 	afx_msg void OnClickedPlayerchat2();
//DeadCode DAW 26Jun00 	afx_msg void OnClickedPlayerchat4();
//DeadCode DAW 26Jun00 	DECLARE_EVENTSINK_MAP()
//DeadCode DAW 26Jun00 	//}}AFX_MSG
//DeadCode DAW 26Jun00 	DECLARE_MESSAGE_MAP()
//DeadCode DAW 26Jun00 };
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 //{{AFX_INSERT_LOCATION}}
//DeadCode DAW 26Jun00 // Microsoft Developer Studio will insert additional declarations immediately before the previous line.
//DeadCode DAW 26Jun00 
//DeadCode DAW 26Jun00 #endif // !defined(AFX_FRAGPILT_H__035ACCE1_100C_11D2_A5A3_0040052179B6__INCLUDED_)
//DeadCode DAW 26Jun00 
