/*
//{{AFX_INCLUDES()
#include "rspinbut.h"
#include "rstatic.h"
#include "rbutton.h"
#include "rcombo.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_LWDIRECT_H__354A1BA3_8ECF_11D3_8ADB_00A0D21BD395__INCLUDED_)
#define AFX_LWDIRECT_H__354A1BA3_8ECF_11D3_8ADB_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWDirect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWDirectives dialog
//DeadCode RDH 08Feb00 struct	LWDirectivesResultsTargetList;
class LWDirectives : public RowanDialog
{
// Construction
public:
	static RDialog* Make(LWDirectivesResults* dires);
	bool ininitdialog;
	LWDirectives(LWDirectivesResults* dirres,CWnd* pParent = NULL);   // standard constructor
	~LWDirectives();
	LWDirectivesResults* dr;
	int maxsquads;
// Dialog Data
	//{{AFX_DATA(LWDirectives)
	enum { IDD = IDD_LWDIRECTIVES };
	CRCombo	m_IDC_RCOMBO_ESCORT;
	CRCombo	m_IDC_RCOMBO_TIMING;
  	CRSpinBut m_IDC_RSPINBUT_MORN;
	CRSpinBut m_IDC_RSPINBUT_MID;
	CRSpinBut	m_IDC_RSPINBUT_JU870;
	CRSpinBut	m_IDC_RSPINBUT_JU871;
	CRSpinBut	m_IDC_RSPINBUT_JU872;
	CRSpinBut	m_IDC_RSPINBUT_JU873;
	CRSpinBut	m_IDC_RSPINBUT_JU874;
	CRSpinBut	m_IDC_RSPINBUT_JU875;
	CRSpinBut	m_IDC_RSPINBUT_JU876;
	CRSpinBut	m_IDC_RSPINBUT_JU877;
	CRSpinBut	m_IDC_RSPINBUT_JU878;
	CRSpinBut	m_IDC_RSPINBUT_JU88_0;
	CRSpinBut	m_IDC_RSPINBUT_JU88_1;
	CRSpinBut	m_IDC_RSPINBUT_JU88_2;
	CRSpinBut	m_IDC_RSPINBUT_JU88_3;
	CRSpinBut	m_IDC_RSPINBUT_JU88_4;
	CRSpinBut	m_IDC_RSPINBUT_JU88_5;
	CRSpinBut	m_IDC_RSPINBUT_JU88_6;
	CRSpinBut	m_IDC_RSPINBUT_JU88_7;
	CRSpinBut	m_IDC_RSPINBUT_JU88_8;
	CRSpinBut	m_IDC_RSPINBUT_HE1110;
	CRSpinBut	m_IDC_RSPINBUT_HE1111;
	CRSpinBut	m_IDC_RSPINBUT_HE1112;
	CRSpinBut	m_IDC_RSPINBUT_HE1113;
	CRSpinBut	m_IDC_RSPINBUT_HE1114;
	CRSpinBut	m_IDC_RSPINBUT_HE1115;
	CRSpinBut	m_IDC_RSPINBUT_HE1116;
	CRSpinBut	m_IDC_RSPINBUT_HE1117;
	CRSpinBut	m_IDC_RSPINBUT_HE1118;
	CRSpinBut	m_IDC_RSPINBUT_DO17_0;
	CRSpinBut	m_IDC_RSPINBUT_DO17_1;
	CRSpinBut	m_IDC_RSPINBUT_DO17_2;
	CRSpinBut	m_IDC_RSPINBUT_DO17_3;
	CRSpinBut	m_IDC_RSPINBUT_DO17_4;
	CRSpinBut	m_IDC_RSPINBUT_DO17_5;
	CRSpinBut	m_IDC_RSPINBUT_DO17_6;
	CRSpinBut	m_IDC_RSPINBUT_DO17_7;
	CRSpinBut	m_IDC_RSPINBUT_DO17_8;
	CRSpinBut	m_IDC_RSPINBUT_ME109_0;
	CRSpinBut	m_IDC_RSPINBUT_ME109_1;
	CRSpinBut	m_IDC_RSPINBUT_ME109_2;
	CRSpinBut	m_IDC_RSPINBUT_ME109_3;
	CRSpinBut	m_IDC_RSPINBUT_ME109_4;
	CRSpinBut	m_IDC_RSPINBUT_ME109_5;
	CRSpinBut	m_IDC_RSPINBUT_ME109_6;
	CRSpinBut	m_IDC_RSPINBUT_ME109_7;
	CRSpinBut	m_IDC_RSPINBUT_ME109_8;
	CRSpinBut	m_IDC_RSPINBUT_ME1100;
	CRSpinBut	m_IDC_RSPINBUT_ME1101;
	CRSpinBut	m_IDC_RSPINBUT_ME1102;
	CRSpinBut	m_IDC_RSPINBUT_ME1103;
	CRSpinBut	m_IDC_RSPINBUT_ME1104;
	CRSpinBut	m_IDC_RSPINBUT_ME1105;
	CRSpinBut	m_IDC_RSPINBUT_ME1106;
	CRSpinBut	m_IDC_RSPINBUT_ME1107;
	CRSpinBut	m_IDC_RSPINBUT_ME1108;
	CRSpinBut	m_IDC_RSPINBUT_FREE_0;
	CRSpinBut	m_IDC_RSPINBUT_FREE_1;
	CRSpinBut	m_IDC_RSPINBUT_FREE_2;
	CRSpinBut	m_IDC_RSPINBUT_FREE_3;
	CRSpinBut	m_IDC_RSPINBUT_FREE_4;
	CRSpinBut	m_IDC_RSPINBUT_FREE_5;
	CRSpinBut	m_IDC_RSPINBUT_FREE_6;
	CRSpinBut	m_IDC_RSPINBUT_FREE_7;
	CRSpinBut	m_IDC_RSPINBUT_FREE_8;
	CRSpinBut	m_IDC_RSPINBUT_TIED_0;
	CRSpinBut	m_IDC_RSPINBUT_TIED_1;
	CRSpinBut	m_IDC_RSPINBUT_TIED_2;
	CRSpinBut	m_IDC_RSPINBUT_TIED_3;
	CRSpinBut	m_IDC_RSPINBUT_TIED_4;
	CRSpinBut	m_IDC_RSPINBUT_TIED_5;
	CRSpinBut	m_IDC_RSPINBUT_TIED_6;
	CRSpinBut	m_IDC_RSPINBUT_TIED_7;
	CRSpinBut	m_IDC_RSPINBUT_TIED_8;
	CRSpinBut	m_IDC_RSPINBUT_SIZE_0;
	CRSpinBut	m_IDC_RSPINBUT_SIZE_1;
	CRSpinBut	m_IDC_RSPINBUT_SIZE_2;
	CRSpinBut	m_IDC_RSPINBUT_SIZE_3;
	CRSpinBut	m_IDC_RSPINBUT_SIZE_4;
	CRSpinBut	m_IDC_RSPINBUT_SIZE_5;
	CRSpinBut	m_IDC_RSPINBUT_SIZE_6;
	CRSpinBut	m_IDC_RSPINBUT_SIZE_7;
	CRSpinBut	m_IDC_RSPINBUT_SIZE_8;
	CRStatic	m_IDC_RSTATIC_MISSIONS_0;
	CRStatic	m_IDC_RSTATIC_MISSIONS_1;
	CRStatic	m_IDC_RSTATIC_MISSIONS_2;
	CRStatic	m_IDC_RSTATIC_MISSIONS_3;
	CRStatic	m_IDC_RSTATIC_MISSIONS_4;
	CRStatic	m_IDC_RSTATIC_MISSIONS_5;
	CRStatic	m_IDC_RSTATIC_MISSIONS_6;
	CRStatic	m_IDC_RSTATIC_MISSIONS_7;
	CRStatic	m_IDC_RSTATIC_MISSIONS_8;
	CRStatic	m_IDC_BOMBER_AFTER;
	CRSpinBut	m_IDC_ALLOW2_0;
	CRSpinBut	m_IDC_ALLOW2_1;
	CRSpinBut	m_IDC_ALLOW2_2;
	CRSpinBut	m_IDC_ALLOW2_3;
	CRSpinBut	m_IDC_ALLOW2_4;
	CRSpinBut	m_IDC_ALLOW2_5;
	CRSpinBut	m_IDC_ALLOW2_6;
	CRSpinBut	m_IDC_ALLOW2_7;
	CRButton	m_IDC_STRAF_0;
	CRButton	m_IDC_STRAF_1;
	CRButton	m_IDC_STRAF_2;
	CRButton	m_IDC_STRAF_3;
	CRButton	m_IDC_STRAF_4;
	CRButton	m_IDC_STRAF_5;
	CRButton	m_IDC_STRAF_6;
	CRButton	m_IDC_STRAF_7;
	CRButton	m_IDC_TICK_A0;
	CRButton	m_IDC_TICK_A1;
	CRButton	m_IDC_TICK_A2;
	CRButton	m_IDC_TICK_A3;
	CRButton	m_IDC_TICK_A4;
	CRButton	m_IDC_TICK_A5;
	CRButton	m_IDC_TICK_D0;
	CRButton	m_IDC_TICK_D1;
	CRButton	m_IDC_TICK_D2;
	CRButton	m_IDC_TICK_D3;
	CRButton	m_IDC_TICK_D4;
	CRButton	m_IDC_TICK_D5;
	CRSpinBut	m_IDC_RSPINBUT_RECONN_MISSIONS;
	CRSpinBut	m_IDC_RSPINBUT_RECONN_AIRCRAFT;
	CRButton	m_IDC_RECONN_AMONLY;
	CRButton	m_IDC_RECONN_ESCORT;
	CRStatic	m_IDC_RSTATIC_RECONN_MISSIONS;
	CRCombo	m_IDC_ESCORT_PROPORTION;
	CRCombo	m_IDC_JU87_PERIOD;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWDirectives)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//TEMPCODE JIM 07/02/00 		DirectivesResults::TargetList target[DirectivesResults::MAX_TARGETS];
	void RefreshReconn();
	void FillSpins(CRSpinBut* spinbut, int actype, int trgtype, int indexgrp, int maxgrp);
	void Refresh();
//DeadCode RDH 08Feb00 	void FindAcAvail();
//DeadCode RDH 08Feb00 		int LWAcAvail[PT_VEHICLES-PT_GER_FLYABLE];
	bool ResetProportions(int actype, int line, int index);
	void RefreshAcSplit();
	void 	RefreshGruppe();
	void	RefreshGruppe(PlaneTypeSelect actype);

	void 	RefreshEscort(int trgtype);
	void 	RefreshEscort();
	void	RefreshFlags();		 
	void	RefreshMissions();
	void	RefreshMissions(int rownum);
	int	RefreshInternalMissions(int linetoreportnummissions=-1);	
	void	RefreshMission(int i,  int missions);

//TEMPCODE JIM 07/02/00 	{
//TEMPCODE JIM 07/02/00 		DirectivesResults::TargetList target[DirectivesResults::MAX_TARGETS];
//TEMPCODE JIM 07/02/00 	};
//DeadCode RDH 08Feb00 	struct	Targets;
//DeadCode RDH 08Feb00 	Targets* trgarray;//[8];
//DeadCode RDH 08Feb00 	Targets&	target;
//DeadCode RDH 08Feb00 	void FillTargetLists();

//DeadCode RDH 08Feb00 	struct FighterSplit
//DeadCode RDH 08Feb00 	{
//DeadCode RDH 08Feb00 		int ret;
//DeadCode RDH 08Feb00 		int att;
//DeadCode RDH 08Feb00 		int det;
//DeadCode RDH 08Feb00 	};
//DeadCode RDH 08Feb00 	FighterSplit	otherraids;
//DeadCode RDH 08Feb00 	FighterSplit	firstraids;


	// Generated message map functions
	//{{AFX_MSG(LWDirectives)
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedRspinbutAllow2(int id, LPCTSTR caption, short Index );
	afx_msg void OnTextChangedRspinbutJu87(int id, LPCTSTR caption, short Index );
	afx_msg void OnTextChangedRspinbutDo17(int id, LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutHe111(int id, LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutJu88(int id, LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutMe109(int id, LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutMe110(int id, LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutTied(int id, LPCTSTR caption, short Index); 
	afx_msg void OnTextChangedRspinbutFree(int id, LPCTSTR caption, short Index); 
	afx_msg void OnClickedStraf(int id);
	afx_msg void OnClickedAttached(int id);
	afx_msg void OnClickedDetached(int id);
	afx_msg void OnClickedSize(int id);
	afx_msg void OnOK();
	afx_msg void OnCancel();
	afx_msg void OnTextChangedRspinbutSize(int id, LPCTSTR caption, short Index); 
	afx_msg void OnTextChangedMorn(LPCTSTR Caption, short index); 
	afx_msg void OnTextChangedMid(LPCTSTR Caption, short index); 
	afx_msg void OnTextChangedRcomboTiming(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedRspinbutReconnAircraft(LPCTSTR caption, short Index);
	afx_msg void OnTextChangedRspinbutReconnMissons(LPCTSTR caption, short Index);
	afx_msg void OnClickedReconnAmonly();
	afx_msg void OnClickedReconnEscort();
	afx_msg void OnClickedRbuttonrest();
	afx_msg void OnTextChangedEscortProportion(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedJu87Period(LPCTSTR Caption, short index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWDIRECT_H__354A1BA3_8ECF_11D3_8ADB_00A0D21BD395__INCLUDED_)
