/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rcombo.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_TWODPREF_H__0CECB560_A35A_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_TWODPREF_H__0CECB560_A35A_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TwoDPref.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TwoDPref dialog

class TwoDPref : public RowanDialog
{
// Construction
public:
	static RDialog* Make();
		void PreDestroyPanel();

	TwoDPref(CWnd* pParent = NULL);   // standard constructor
	struct	PossReses
	{
		int	horres:16;
		int	vertres:16;
		enum	{	CBS_15=7,	CB_15=	0x00080,
					CBS_16=8,	CB_16=	0x00100,
					CBS_24=16,	CB_24=	0x01000,
					CBS_32=24,	CB_32=	0x10000,
					CB_NONE=0,	CB_ALL=	0x11180,
					MAX_RES_MODES=32

				};

		ULong	canbitsminus8;
	};
	PossReses	possiblemapreses[PossReses::MAX_RES_MODES];
	int	maxreses,currmapres,currdefaultres,lowestres,res1024res,fragis1024;
	CString desktopstr;

// Dialog Data
	//{{AFX_DATA(TwoDPref)
	enum { IDD = IDD_2D };
	CRCombo	m_IDC_CBO_MAPSCREEN;
	CRCombo	m_IDC_CBO_COLOURDEPTH;
	CRCombo	m_IDC_CBO_INTROART;
	CRCombo	m_IDC_CBO_MAPEVENTS;
	CRCombo	m_IDC_CBO_OPTIONS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TwoDPref)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	SetOtherCombos();
	// Generated message map functions
	//{{AFX_MSG(TwoDPref)
	afx_msg void OnTextChangedCboColourdepth(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboMapscreen(LPCTSTR Caption, short index);
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedCboMapevents(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboIntroart(LPCTSTR Caption, short index);
	afx_msg void OnTextChangedCboOptions(LPCTSTR Caption, short index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TWODPREF_H__0CECB560_A35A_11D3_8ADC_00A0D21BD395__INCLUDED_)
