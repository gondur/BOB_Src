/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()

//}}AFX_INCLUDES

*/
#if !defined(AFX_TOTETOP_H__37005B80_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_TOTETOP_H__37005B80_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToteTop.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ToteTop dialog

class ToteTop : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	ToteTop(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ToteTop)
	enum { IDD = IDD_TOTETOP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ToteTop)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ToteTop)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOTETOP_H__37005B80_9D93_11D3_8ADC_00A0D21BD395__INCLUDED_)
