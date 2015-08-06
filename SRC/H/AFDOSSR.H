/*
//{{AFX_INCLUDES()
#include "rbutton.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_AFDOSSR_H__27AE24C0_8E23_11D3_8ADB_00A0D21BD395__INCLUDED_)
#define AFX_AFDOSSR_H__27AE24C0_8E23_11D3_8ADB_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AfDossr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AirfieldDossier dialog

class AirfieldDossier : public RowanDialog
{
// Construction
public:
	static RDialog* Make(int afuid, int gruppe);

	AirfieldDossier(UniqueID afuid, int gruppe, CWnd* pParent = NULL);   // standard constructor
	UniqueID uid;
	int sqgruppe;
// Dialog Data
	//{{AFX_DATA(AirfieldDossier)
	enum { IDD = IDD_AC_DOSSIER };
	CRButton	m_IDJ_TITLE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AirfieldDossier)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AirfieldDossier)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AFDOSSR_H__27AE24C0_8E23_11D3_8ADB_00A0D21BD395__INCLUDED_)
