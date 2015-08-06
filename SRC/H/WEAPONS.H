//DeadCode DAW 14Jun00 /*
//DeadCode DAW 14Jun00 //{{AFX_INCLUDES()
//DeadCode DAW 14Jun00 
//DeadCode DAW 14Jun00 //}}AFX_INCLUDES
//DeadCode DAW 14Jun00 */
//DeadCode DAW 14Jun00 #if !defined(AFX_WEAPONS_H__337EE8A1_11DF_11D2_A5A3_0040052179B6__INCLUDED_)
//DeadCode DAW 14Jun00 #define AFX_WEAPONS_H__337EE8A1_11DF_11D2_A5A3_0040052179B6__INCLUDED_
//DeadCode DAW 14Jun00 
//DeadCode DAW 14Jun00 #if _MSC_VER >= 1000
//DeadCode DAW 14Jun00 #pragma once
//DeadCode DAW 14Jun00 #endif // _MSC_VER >= 1000
//DeadCode DAW 14Jun00 // Weapons.h : header file
//DeadCode DAW 14Jun00 //
//DeadCode DAW 14Jun00 
//DeadCode DAW 14Jun00 /////////////////////////////////////////////////////////////////////////////
//DeadCode DAW 14Jun00 // CWeapons dialog
//DeadCode DAW 14Jun00 struct	lchpak;
//DeadCode DAW 14Jun00 class CWeapons : public RowanDialog
//DeadCode DAW 14Jun00 {
//DeadCode DAW 14Jun00 // Construction
//DeadCode DAW 14Jun00 	static lchpak*	CWeapons::GetWeapList(int pack,int wave,int grp,int flight);
//DeadCode DAW 14Jun00 	static int		CWeapons::GetWeapIndex(int pack,int wave,int grp,int flight);
//DeadCode DAW 14Jun00 
//DeadCode DAW 14Jun00 public:
//DeadCode DAW 14Jun00 	CWeapons(int pack,int wave,int grp,int flight,CWnd* pParent = NULL);   // standard constructor
//DeadCode DAW 14Jun00 	lchpak*	thisacweaps;
//DeadCode DAW 14Jun00 	bool		currgotfuel;
//DeadCode DAW 14Jun00 	static int		CWeapons::GetWeapName(int pack,int wave,int grp,int flight);
//DeadCode DAW 14Jun00  	static	int		CWeapons::GetExtFuel(int pack,int wave,int grp,int flight);
//DeadCode DAW 14Jun00 
//DeadCode DAW 14Jun00 
//DeadCode DAW 14Jun00 
//DeadCode DAW 14Jun00 // Dialog Data
//DeadCode DAW 14Jun00 	//{{AFX_DATA(CWeapons)
//DeadCode DAW 14Jun00 	enum { IDD = IDD_PAYLOAD };
//DeadCode DAW 14Jun00 		// NOTE: the ClassWizard will add data members here
//DeadCode DAW 14Jun00 	CRListBox	m_IDC_WEAPLIST;
//DeadCode DAW 14Jun00 	CRStatic	m_IDC_TSQUAD; 
//DeadCode DAW 14Jun00 	CRStatic	m_IDC_TSQUAD2;
//DeadCode DAW 14Jun00 	CRStatic	m_IDC_TSQUAD3;
//DeadCode DAW 14Jun00  	CRButton	m_IDJ_TITLE;
//DeadCode DAW 14Jun00 
//DeadCode DAW 14Jun00 	//}}AFX_DATA
//DeadCode DAW 14Jun00 
//DeadCode DAW 14Jun00 
//DeadCode DAW 14Jun00 // Overrides
//DeadCode DAW 14Jun00 	// ClassWizard generated virtual function overrides
//DeadCode DAW 14Jun00 	//{{AFX_VIRTUAL(CWeapons)
//DeadCode DAW 14Jun00 	protected:
//DeadCode DAW 14Jun00 	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//DeadCode DAW 14Jun00 	//}}AFX_VIRTUAL
//DeadCode DAW 14Jun00 
//DeadCode DAW 14Jun00 // Implementation
//DeadCode DAW 14Jun00 protected:
//DeadCode DAW 14Jun00 	void	ParentDialClosed(RDialog*,int rv);
//DeadCode DAW 14Jun00 
//DeadCode DAW 14Jun00 	// Generated message map functions
//DeadCode DAW 14Jun00 	//{{AFX_MSG(CWeapons)
//DeadCode DAW 14Jun00 	afx_msg void OnSelectWeaplist(long row, long column);
//DeadCode DAW 14Jun00 	DECLARE_EVENTSINK_MAP()
//DeadCode DAW 14Jun00 	virtual BOOL OnInitDialog();
//DeadCode DAW 14Jun00 	//}}AFX_MSG
//DeadCode DAW 14Jun00 	DECLARE_MESSAGE_MAP()
//DeadCode DAW 14Jun00 	void	OnOK();
//DeadCode DAW 14Jun00 };
//DeadCode DAW 14Jun00 
//DeadCode DAW 14Jun00 //{{AFX_INSERT_LOCATION}}
//DeadCode DAW 14Jun00 // Microsoft Developer Studio will insert additional declarations immediately before the previous line.
//DeadCode DAW 14Jun00 
//DeadCode DAW 14Jun00 #endif // !defined(AFX_WEAPONS_H__337EE8A1_11DF_11D2_A5A3_0040052179B6__INCLUDED_)
//DeadCode DAW 14Jun00 
