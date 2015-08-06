/*
//{{AFX_INCLUDES()

//}}AFX_INCLUDES
*/
#if !defined(AFX_RMDLDLG_H__8ADE6461_6818_11D2_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_RMDLDLG_H__8ADE6461_6818_11D2_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RMdlDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RMdlDlg dialog

#include "globdefs.h"
#include "files.g"
class fileblock;

class RMdlDlg : public CDialog
{
// Construction
public:
	enum	{m_scalingfactor=1};
	RMdlDlg(CWnd* pParent = NULL);   // standard constructor
	FileNum m_artnum;
	fileblock* m_pfileblock;
	CString m_TitleID;
	CString m_MessageID;
	UINT m_Button0ID;
	UINT m_Button1ID;
	UINT m_Button2ID;
	CPoint m_point;
	BOOL m_lbuttondown;

// Dialog Data
	//{{AFX_DATA(RMdlDlg)
	enum { IDD = IDDS_MODAL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	CRButton	m_IDJ_TITLE;
	CRButton	m_IDC_OK;
	CRButton	m_IDC_CANCEL;
	CRButton	m_IDC_RETRY;
	CRStatic	m_IDC_MESSAGE_TEXT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RMdlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RMdlDlg)
	afx_msg void OnClickedOk();
	afx_msg void OnClickedRetry();
	afx_msg void OnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	#include  "rdialmsg.h"

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMDLDLG_H__8ADE6461_6818_11D2_A1F0_0080C8582DE4__INCLUDED_)
