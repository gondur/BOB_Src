/*
//{{AFX_INCLUDES()
#include "rcombo.h"
#include "rbutton.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_SCONTROL_H__5F830781_4036_11D2_83A5_00004760763D__INCLUDED_)
#define AFX_SCONTROL_H__5F830781_4036_11D2_83A5_00004760763D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SControl.h : header file
//
#ifndef AXIS_USES
#define	AXIS_USES
enum	AxisUses		{	AU_UNASSIGNED=-1,
							AU_AILERON=0,AU_ELEVATOR,AU_RUDDER,AU_THROTTLE,
							AU_UI_X=4,AU_UI_Y,
							AU_COLLECTIVE=6,AU_COOLIEHAT=7,
							AU_VIEWH=8,AU_VIEWP,AU_VIEWR,AU_VIEWZ,
							AU_GUNH=12,AU_GUNP,
						  	AU_WALKSPEED=14,AU_WALKTURN,
							AU_FLAPS=16,AU_BRAKE,AU_TRIM_ELEV,AU_ABSTEPS,
							AU_MIN=0,AU_MAX=31,AU_ILLEGAL=127,
							MAXFORCEAXES=10	//list of FF actuator GUIDs
						};
#endif

/////////////////////////////////////////////////////////////////////////////
// SController dialog

class SController
#ifdef __AFXWIN_H__
	:public RowanDialog
#endif
{
// Construction
public:
	UINT ControlsPref_Timer;

//enum	AssignedTasks {AT_UNASSIGNED=-1,AT_AILERON,AT_ELEVATOR,AT_RUDDER,AT_THROTTLE,AT_PAN,AT_PITCH,AT_ZOOM,AT_MOUSELR,AT_MOUSEUD};
#ifdef __AFXWIN_H__
	SController(CWnd* pParent = NULL);   // standard constructor
	void PreDestroyPanel();
	void	SetEnabled(int newaxis);
// Dialog Data
	//{{AFX_DATA(SController)
	enum { IDD = IDD_SCONTROLLER };
	CRStatic	m_IDC_RSTATICCTRL6;
	CRStatic	m_IDC_RSTATICCTRL9;
	CRStatic	m_IDC_RSTATICCTRL12;
	CRStatic	m_IDC_RSTATICCTRL14;
	CRStatic	m_IDC_RSTATICCTRL16;
	CRCombo	m_IDC_DEVLIST;
	CRCombo	m_IDC_STICKDEV;
	CRCombo	m_IDC_THROTDEV;
	CRCombo	m_IDC_RUDDEV;
	CRCombo	m_IDC_PANDEV;
	CRStatic	m_IDC_RSTATICCTRL17;
	CRStatic	m_IDC_RSTATICCTRL18;
	CRStatic	m_IDC_RSTATICCTRL19;
	CRCombo	m_IDC_PITCHDEV;
	CRCombo	m_IDC_ZOOMDEV;
	CRCombo	m_IDC_MOUSEDEV;
	CRStatic	m_IDC_DEVDESC;
	CREdtBt	m_IDC_CALIB;
	CRStatic	m_IDC_SUPPFF;
	CRButton	m_IDC_SELFF;
	CRStatic	m_IDC_SUPPFF2;
	CRButton	m_IDC_SELPOLL;
	CRButton	m_IDC_FLIP_GUNNER;
	CRButton	m_IDC_FLIP_COCKPIT;
	CRButton	m_IDC_FLIP_PAN;
	CRStatic	m_IDC_RSTATICCTRL7;
	CRStatic	m_IDC_RSTATICCTRL8;
	CRStatic	m_IDC_RSTATICCTRL46;
	CRCombo	m_IDC_CBO_FF_GUNRATTLE;
	CRCombo	m_IDC_CBO_FF_STALL;
	CRCombo	m_IDC_CBO_FF_HIGHSPEED;
	CRCombo	m_IDC_CBO_FF_AIRFRAME;
	CRCombo	m_IDC_CBO_STICKDZ;
	CRCombo	m_IDC_CBO_STICKMODE;
	CRCombo	m_IDC_CBO_RUDDZ;
	CRCombo	m_IDC_CBO_COCKPITDZ;
	CRCombo	m_IDC_CBO_COCKPITMODE;
	CRCombo	m_IDC_CBO_GUNNERDZ;
	CRCombo	m_IDC_CBO_GUNNERMODE;
	CRCombo	m_IDC_CBO_PANDZ;
	CRCombo	m_IDC_CBO_PANMODE;
	CRCombo	m_IDC_CBO_PP2DZ;
	CRCombo	m_IDC_CBO_PPDZ;
	CRCombo	m_IDC_CBO_RUDMODE;
	CRCombo	m_IDC_CBO_ZOOMDZ;
	CRCombo	m_IDC_CBO_ZOOMMODE;
	CRCombo	m_IDC_GUNNER;
	CRCombo	m_IDC_PROPPITCH;
	CRCombo	m_IDC_PROPPITCH2;
	CRCombo	m_IDC_THROTDEV_2;
	CRCombo	m_IDC_CBO_THROT2DZ;
	CRCombo	m_IDC_CBO_THROTDZ;
	CRCombo	m_IDC_INTERACTIVECPIT;
	CRCombo	m_IDC_CBO_FF_AERO;
	CRCombo	m_IDC_CBO_FF_BUFF;
	CRButton	m_IDC_FLIP_PANHORI;
	//}}AFX_DATA

//DeadCode AMM 21Feb100 	bool	SetAxesCombo(CRCombo& ID,AxisUses task,bool xonly,bool analogonly,bool paironly);
//DeadCode AMM 27Jul00 	bool	SetAxesCombo(CRCombo& ID,AxisUses task,bool xonly,bool analogonly,bool paironly,bool notstick, bool notmouse, bool allowshifted);
	bool	SetAxesCombo(CRCombo& ID,AxisUses task,bool xonly,bool analogonly,bool paironly,bool notstick, bool notmouse, bool allowshifted, bool allownormal,AllowAliasing allowaliassing=AA_NONE);
//DeadCode AMM 21Feb100 	int		ChangedAxesCombo(CRCombo& ID,AxisUses task,bool xonly,bool analogonly,bool paironly);
//DeadCode AMM 27Jul00 	int		ChangedAxesCombo(CRCombo& ID,AxisUses task,bool xonly,bool analogonly,bool paironly,bool notstick, bool notmouse, bool allowshifted);
	int		ChangedAxesCombo(CRCombo& ID,AxisUses task,bool xonly,bool analogonly,bool paironly,bool notstick, bool notmouse, bool allowshifted, bool allownormal,AllowAliasing allowaliassing=AA_NONE);
	void	ChangedAxesValue(int newind,AxisUses task);
	void	RemakeAxes();
	void	RemakeDisplay();				  //GetExtFuel

#endif


	static bool	GetAxisConfig(bool setff=false);
//DeadCode AMM 21Feb100 	static void	SetAxisConfig();
	static void	SetAxisConfig(bool, bool);
	static void BuildEnumerationTables();
	static void SetDefaultStickSettings(bool);
#ifdef __AFXWIN_H__
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SController)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SController)
	afx_msg void OnClickedCalib();
	afx_msg void OnTextChangedDevlist(LPCTSTR text, short index);
	afx_msg void OnTextChangedMousedev(LPCTSTR text, short index);
	afx_msg void OnTextChangedPandev(LPCTSTR text, short index);
	afx_msg void OnTextChangedPitchdev(LPCTSTR text, short index);
	afx_msg void OnTextChangedRuddev(LPCTSTR text, short index);
	afx_msg void OnClickedSelff();
	afx_msg void OnClickedSelpoll();
	afx_msg void OnTextChangedStickdev(LPCTSTR text, short index);
	afx_msg void OnTextChangedThrotdev(LPCTSTR text, short index);
	afx_msg void OnTextChangedZoomdev(LPCTSTR text, short index);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnTextChangedCboStickdz(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboStickdmode(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedThrotdev2(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedProppitch2(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedProppitch(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedInteractivecockpit(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedGunner(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboZoommode(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboThrotdz(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboThrot2dz(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboRudmode(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboRuddz(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboPpdz(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboPp2dz(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboPanmode(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboPandz(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboGunnermode(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboGunnerdz(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboCockpitmode(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboFfGunrattle(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboFfBuff(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboFfAirframe(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboFfAero(LPCTSTR Caption, short index);
	afx_msg void OnClickedFlipCockpit();
	afx_msg void OnClickedFlipGunner();
	afx_msg void OnClickedFlipPan();
	afx_msg void OnClickedFlipPanhori();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
#endif	//def __AFXWIN_H__
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCONTROL_H__5F830781_4036_11D2_83A5_00004760763D__INCLUDED_)
