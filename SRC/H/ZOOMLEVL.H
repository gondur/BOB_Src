/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rspinbut.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_ZOOMLEVL_H__E807FFA0_96BD_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_ZOOMLEVL_H__E807FFA0_96BD_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoomLevl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ZoomLevel dialog

class ZoomLevel : public RowanDialog
{
// Construction

	static float zoomLevel[16];
public:
	static RDialog* Make();

	ZoomLevel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ZoomLevel)
	enum { IDD = IDD_ZOOMLEVEL };
	CRSpinBut	m_IDC_RSPINBUT_DEFAULTZOOM;
	CRSpinBut	m_IDC_RSPINBUT_SECONDZOOM;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZoomLevel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int	 FindIndex(float zoom);
	void FillSpin(CRSpinBut* spinbut);


	// Generated message map functions
	//{{AFX_MSG(ZoomLevel)
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedRspinbutSecondzoom(LPCTSTR text, short index);
	afx_msg void OnTextChangedRspinbutDefaultzoom(LPCTSTR text, short index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMLEVL_H__E807FFA0_96BD_11D3_8ADC_00A0D21BD395__INCLUDED_)
