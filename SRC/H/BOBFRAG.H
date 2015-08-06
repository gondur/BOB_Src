/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rbutton.h"
#include "redit.h"
#include "rcombo.h"
#include "rstatic.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_BOBFRAG_H__CBD16D80_A964_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_BOBFRAG_H__CBD16D80_A964_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BoBFrag.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BoBFrag dialog
struct FragScreenBody
{
	enum	{FE_MAX_PILOTS = 16};
	struct	FragEntry
	{
//DeadCode JIM 24Oct00 		CString AIslotname;
		CString	playerslotname;
		bool	playerallowed;
		bool	playerinslot;
		bool	remoteplayerinslot;
	};
	struct	SquadOptions
	{
		UWord		PilotDead;											//AMM 14Aug00
		bool		playerallowed;
		UByte		startingcolour;		
		//For RAF colour is incremented for each 3 bits clear in squadlist.AcBitsSquad(sqnum)
		//For LW colour is upped by 4 for each previous instance of squadnum in same package.
		ONLYFIELD(UByte,SquadNum,squadnum);
		UByte		acperflight:3;
		UByte		totalac:5;
		UWord		somesortofduty;								//RDH 23/03/00
	};
	struct	FragSide
	{
		int	currsquadoption;
		int	maxsquadoption;
		FragEntry		pilotentries[FE_MAX_PILOTS];
		SquadOptions	squadoptions[1];
	};
	struct	EngSide:FragSide
	{
		enum {MAX=20};
		SquadOptions	moresquadoptions[MAX];
	};
	struct	GerSide:EngSide
	{
		enum {MAX=100,EXTRA=80};
		SquadOptions	moresquadoptions[EXTRA];	//total 100!!!
	};
	GerSide		germanfrag;
	EngSide		britfrag;
	FragSide*	currfrag;
	int		acnuminsquad;

	struct ButtonPos
	{
		enum	CommandPosition	{CP_LEADER, CP_SECOND, CP_OTHER};

		POINT	coords;
		int		callsign;
		CommandPosition	commandposition;
	};
	enum	FormationTypes{FT_RAF, FT_LWESCORT, FT_LWSTRIKEVIC3, FT_LWSTRIKEVIC5, FT_MAX};
	static	ButtonPos	buttonpos[FT_MAX][16];
	
};

class BoBFrag : public RowanDialog
{
// Construction
public:
	UINT bobfrag_timer;
	static RDialog* Make();

	BoBFrag(CWnd* pParent = NULL);   // standard constructor
	~BoBFrag();   // standard constructor
// Dialog Data
	//{{AFX_DATA(BoBFrag)
	enum { IDD = IDD_BOBFRAG };
	CRListBox	m_IDC_RLIST_UNITDETAILS;
	CREdit	m_IDC_PLAYERCHAT;
	CRListBox	m_IDC_RLIST_INCOMING_CHAT;
	CRCombo	m_IDC_COMBO_UNIT;
	CRButton	m_IDC_UNASSIGNFLAG;
	CRStatic	m_IDC_UNASSIGN;
	//}}AFX_DATA

	CREdtBt	m_IDC_PILOT_[15];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BoBFrag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	void	RefreshData(int targetid);
// Implementation
protected:
	 void PositionPilots();
	 void ResetPlayerEntry(int plyrpos);
//DeadCode AMM 08Mar00 	 void ResetRemotePlayerEntry(int plyr);
	 void ResetRemotePlayerEntry();
	 void SetPlayersPosition(int);
	 void SetPlayersPositionCamp(int);
	 void SetPlayersPositionQM(int);
	 int GetSideAndSetFrag();
	int GetPreviousSquadronNumber(int);

	void	GetSquadronAndPos(SLong&, SLong&, ULong);
	SLong	GetSelectedPosition(SLong, SLong);
	 FragScreenBody&	squadinfo;

	 void	FillSquadronsFromQM();
	 void	FillSquadronsFromCamp();
	 void	FillSquadronsFromComms();
	 void	FillPilotFromSquad(int squadline);
	 void	SetSelectedSquadron();
	 void	SetMissSelSquadron(int sel);
	 bool	IsControlledByGroup();
	 int	GetSide();


	// Generated message map functions
	//{{AFX_MSG(BoBFrag)
	virtual BOOL OnInitDialog();
	afx_msg void OnReturnPressedPlayerchat(LPCTSTR text);
	afx_msg void OnSelectRlistUnitdetails(long row, long column);
	afx_msg void OnClickedPilot0(int id);
	afx_msg void OnClickedUnassignflag();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnClickedReturntoplayer();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOBFRAG_H__CBD16D80_A964_11D3_8ADC_00A0D21BD395__INCLUDED_)
