/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rbutton.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_DOSSIERB_H__FB17C760_9686_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_DOSSIERB_H__FB17C760_9686_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dossierb.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dossier dialog

class Dossier : public RowanDialog
{
// Construction
public:
	static RDialog* Make(UniqueID item);

	Dossier(UniqueID item, CWnd* pParent = NULL);   // standard constructor
	UniqueID uid;
// Dialog Data
	//{{AFX_DATA(Dossier)
	enum { IDD = IDD_DOSSIER };
	CRButton	m_IDJ_TITLE;
	CRButton	m_IDC_AUTHORISE;
	CRButton	m_IDC_PHOTO;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dossier)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool ReconnRequired();

	// Generated message map functions
	//{{AFX_MSG(Dossier)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedCentre();
	afx_msg void OnClickedAuthorise();
	afx_msg void OnClickedPhoto();
	afx_msg void OnClickedZoomin();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOSSIERB_H__FB17C760_9686_11D3_8ADC_00A0D21BD395__INCLUDED_)
