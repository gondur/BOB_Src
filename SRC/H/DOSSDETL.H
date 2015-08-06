/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rstatic.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_DOSSDETL_H__FB17C761_9686_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_DOSSDETL_H__FB17C761_9686_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DossDetl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DossierDetails dialog

class DossierDetails : public RowanDialog
{
// Construction
public:
	static RDialog* Make(UniqueID);

	DossierDetails(UniqueID,CWnd* pParent = NULL);   // standard constructor
	UniqueID trguid;
// Dialog Data
	//{{AFX_DATA(DossierDetails)
	enum { IDD = IDD_DOSSIERDETAILS };
	CRStatic	m_IDC_DOSSNOTES;
	CRStatic	m_IDC_RSTATICAAA;
	CRStatic	m_IDC_RSTATICBALLOON;
	CRStatic	m_IDC_RSTATICDAMAGE;
	CRStatic	m_IDC_RSTATICNAME;
	CRStatic	m_IDC_RSTATICPROD;
	CRStatic	m_IDC_RSTATICSTATUS;
	CRStatic	m_IDC_RSTATICTYPE;
	CRStatic	m_IDC_RSTATICCTRL_PROD;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DossierDetails)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DosNotes();

	// Generated message map functions
	//{{AFX_MSG(DossierDetails)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOSSDETL_H__FB17C761_9686_11D3_8ADC_00A0D21BD395__INCLUDED_)
