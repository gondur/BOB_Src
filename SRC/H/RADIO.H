/*
//{{AFX_INCLUDES()

//}}AFX_INCLUDES
*/
#if !defined(AFX_RADIO_H__27646162_0F61_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_RADIO_H__27646162_0F61_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Radio.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRadio dialog

class CRadio : public RowanDialog
{
// Construction
public:
	CRadio(CWnd* pParent = NULL);   // standard constructor
	UINT	radio_timer;

// Dialog Data
	//{{AFX_DATA(CRadio)
	enum { IDD = IDDX_RADIO };
	CREdit	m_IDC_PLAYERMESSAGE1;
	CREdit	m_IDC_PLAYERMESSAGE2;
	CREdit	m_IDC_PLAYERMESSAGE3;
	CREdit	m_IDC_PLAYERMESSAGE4;
	CREdit	m_IDC_PLAYERMESSAGE5;
	CREdit	m_IDC_PLAYERMESSAGE6;
	CREdit	m_IDC_PLAYERMESSAGE7;
	CREdit	m_IDC_PLAYERMESSAGE8;
	CREdit	m_IDC_PLAYERMESSAGE9;
	CREdit	m_IDC_PLAYERMESSAGE10;
		CRCombo	 m_IDC_CURRENTAC;
	CRStatic	m_IDC_CURRENTAIRCRAFT;

	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadio)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRadio)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTextChangedPlayermessage1(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage2(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage3(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage4(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage5(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage6(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage7(LPTSTR text);
	afx_msg void OnTextChangedPlayermessage8(LPTSTR text);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg void OnTextChangedPlayermessage10(LPTSTR text);
	void OnOK();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADIO_H__27646162_0F61_11D2_A5A3_0040052179B6__INCLUDED_)
