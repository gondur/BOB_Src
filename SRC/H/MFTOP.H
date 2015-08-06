/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()

//}}AFX_INCLUDES

*/
#if !defined(AFX_MFTOP_H__929DEE41_9847_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_MFTOP_H__929DEE41_9847_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MFTop.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MapFiltersTop dialog

class MapFiltersTop : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	MapFiltersTop(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MapFiltersTop)
	enum { IDD = IDD_MAPFILTERS_TOP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MapFiltersTop)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MapFiltersTop)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFTOP_H__929DEE41_9847_11D3_8ADC_00A0D21BD395__INCLUDED_)
