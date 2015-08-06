/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()

//}}AFX_INCLUDES

*/
#if !defined(AFX_STATBAR_H__9D3CA0C0_962C_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_STATBAR_H__9D3CA0C0_962C_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// StatusBar dialog

class StatusBar : public CRToolBar
{
// Construction
public:
	StatusBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(StatusBar)
	enum { IDD = IDDT_STATUSBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StatusBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(StatusBar)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATBAR_H__9D3CA0C0_962C_11D3_8ADC_00A0D21BD395__INCLUDED_)
