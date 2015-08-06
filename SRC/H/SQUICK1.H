/*
//{{AFX_INCLUDES()
#include "redit.h"
#include "rcombo.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_SQUICK1_H__CB7A5325_FA0F_11D1_A5A3_0040052179B6__INCLUDED_)
#define AFX_SQUICK1_H__CB7A5325_FA0F_11D1_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SQuick1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSQuick1 dialog
class	CSQuickLine;
class	CSQuick1;

struct	QuickFields
{
	enum QFD {	//0
				QFD_BRIT_FIGHTER,
				QFD_BRIT_BOMBER_PLAYER_ONLY,	//AREN'T ANY
				QFD_BRIT_BOMBER_AUTO_ONLY,
				QFD_BRIT_PLAYER_AUTO,			//these 2 access the same list
				QFD_BRIT_PLAYER_AUTO_IS_AUTO,	//but flag which is selected
				QFD_BRIT_LONE,
				//6
				QFD_GERM_FIGHTER,				//make this Me109,Me110 player or auto
				QFD_GERM_BOMBER_PLAYER_ONLY,	//make this Ju87,Me109,Me110 player or auto
				QFD_GERM_BOMBER_AUTO_ONLY,
				QFD_GERM_BOMBER_PLAYER_AUTO,			//these 2 access the same list !not used
				QFD_GERM_BOMBER_PLAYER_AUTO_IS_AUTO,	//but flag which is selected
				QFD_GERM_LONE,
				//12
				QFD_FIXED_PLAYER,
				QFD_FIXED_AUTO,
				QFD_FIXED_NUM_PLAYER,
				QFD_FIXED_NUM_AUTO,	
				//16

				QFD_MASK=0x0f,
				QFD_LAST=0x0f,
				QFD_FLAGS=0xf0,
				QFD_ALLOW_ZERO_FL=128,
			

	};
				
	UByte	actype;
	UByte	flights;
	UByte	skill;
	int alt;
	int descID;

	UByte	duty;

	QFD		Duty()	{return (QFD)(duty&QFD_MASK);}
	UByte	DutyFlags()	{return duty;}
//DeadCode AMM 10Aug00 	bool	AllowZero()	{return (duty&QFD_ALLOW_ZERO_FL)!=0;}
	bool	AllowZero();										//AMM 10Aug00
	int	ACPerFlight();
	int	MaxFlights();
	void	SetDuty(QFD v)	{duty=(duty&QFD_FLAGS)|v;}
	CSQuickLine*	dialog;
};
#ifdef	STANDALONE
typedef int	FixString;
#else
enum	FixString	{};
CString LoadResString(FixString);
#endif
struct	QuickDef
{
   	FixString		titlename,missionname,missiondesc;
	QuickFields
		line[2]	//red/blue
			[8]	//waves
			[4];//groups
	char	plside,plwave,plgrp,plac;
	UWord	currmissnum,altmissnum;
	char	weather,	time;
	FixString	targtypeIDs[4];
	UniqueID	targets[4][4];
	UniqueID	target;

	CSQuick1*	parent;
	int	SpareFlights(int squad);
	void	FixOtherLines(int squad);
	void	MakeDeathMatchMission(int index);
	void	MakeTeamPlayMission(int index);
//DeadCode AMM 23Oct00 	void	UpdateAcType();
#ifndef	STANDALONE
	static char** extrastrings;
	static	void	trans(void* &dataarea,ULong& datasize);
#endif

	struct	QuickMissionArray
	{
		const QuickDef	operator[](int index)const;
//DEADCODE RDH 24/03/00 		{
//DEADCODE RDH 24/03/00 			fileblock* fb=new fileblock(FIL_QUICKMISSION_DATA);
//DEADCODE RDH 24/03/00 			QuickDef* qd=(QuickDef*)fb->getdata();
//DEADCODE RDH 24/03/00 			return	QuickMissionIndex(fb,qd[index]); 
//DEADCODE RDH 24/03/00 		}
	};

};
#ifdef	QUICKQUICKQUICK
class CSQuick1
{
public:
	static	QuickDef	quickdef;
#ifdef	STANDALONE
#pragma warnmsg("Defining stand-alone quick-defs")
	static	QuickDef	quickmissions[];
#else
	static	QuickDef::QuickMissionArray	quickmissions;
#endif
	static	int			currquickmiss;
	static	int			currquickfamily;
//DEADCODE JON 05/06/00 #pragma warnmsg("Here!")


} ;
#else
typedef MakeField<QuickFields::QFD,0,QuickFields::QFD_LAST>	QFDField;
class CSQuick1 : public RowanDialog
{
// Construction
public:
	int	targtype,targentry,plflst;
	CSQuick1(CWnd* pParent = NULL);   // standard constructor
	UINT missbrief_timer;
//DEADCODE RDH 09/03/00 	UByte	misslistindex[40];
//DEADCODE RDH 09/03/00 	UByte	misslistbackindex[40];
	int	misslistindex[40];
	int	misslistbackindex[40];
	int	missionfamily[40];
	static int	ACPerFlight(PlaneTypeSelect);
	static int	MaxFlights(PlaneTypeSelect);
	static int	MaxGrFlights(PlaneTypeSelect);
// Dialog Data
	//{{AFX_DATA(CSQuick1)
	enum { IDD = IDDX_SQUICKMISSION };
	CRStatic	m_IDC_SDETAIL1;
	CRStatic	m_IDC_RSTATICCTRL4;
	CRStatic	m_IDC_SDETAIL2;
	CRStatic	m_IDC_RSTATICCTRL24;
	CRStatic	m_IDC_RSTATICCTRL7;
	CRStatic	m_IDC_DISABLEDEMO;
	CRCombo	m_IDC_MISSLISTS;
	CRCombo	m_IDC_FLIGHTNUM;
	CRCombo	m_IDC_ELTNUM;
	CRCombo	m_IDC_WEATHER;
	CRCombo	m_IDC_TARGTYPE;
	CRCombo	m_IDC_TARGNAME;
	CRRadio	m_IDC_RRADIO;
	CRCombo	m_IDC_FAMILYLISTS;
	//}}AFX_DATA

	static	QuickDef	quickdef;

	//make this into 
	//QuickMissionArray	quickmissions;
	//in order to load quickmissions from disk
#ifdef	STANDALONE
#pragma warnmsg("Defining stand-alone quick-defs")
	static	QuickDef	quickmissions[];
#else
	static	QuickDef::QuickMissionArray	quickmissions;
#endif

	static	int			currquickmiss;
	static	int			currquickfamily;
	static	QFDField	nonplayer;
	void	MakeFlightCombo();
	void	ReinitCombo();
	char	flightlines[10][4];
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQuick1)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool	wassingle;
	 void	RefreshMissionCombo();
	bool	MissionAllowed(int i);
	bool	MissionsFound(int i, int	currtitle);


	// Generated message map functions
	//{{AFX_MSG(CSQuick1)
	afx_msg void OnTextChangedMisslists(LPCTSTR text, short index);
	afx_msg void OnTextChangedFlightnum(LPCTSTR text, short index);
	afx_msg void OnTextChangedTargtype(LPCTSTR text, short index);
	afx_msg void OnTextChangedTargname(LPCTSTR text, short index);
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedEltnum(LPCTSTR text, short index);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSelectedRradio(long ButtonNum);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTextChangedFamilylists(LPCTSTR Caption, short index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQUICK1_H__CB7A5325_FA0F_11D1_A5A3_0040052179B6__INCLUDED_)
