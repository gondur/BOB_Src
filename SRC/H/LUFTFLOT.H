/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()

//}}AFX_INCLUDES

*/
#if !defined(AFX_LUFTFLOT_H__76D7D541_B151_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_LUFTFLOT_H__76D7D541_B151_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LuftFlot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LuftFlotte dialog

class LuftFlotte : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	LuftFlotte(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(LuftFlotte)
	enum { IDD = IDD_LUFTFLOTTE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LuftFlotte)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LuftFlotte)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LUFTFLOT_H__76D7D541_B151_11D3_8ADC_00A0D21BD395__INCLUDED_)
