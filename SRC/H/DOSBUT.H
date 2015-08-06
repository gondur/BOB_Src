//DEADCODE JIM 09/02/00 /*
//DEADCODE JIM 09/02/00 //{{AFX_INCLUDES()
//DEADCODE JIM 09/02/00 
//DEADCODE JIM 09/02/00 //}}AFX_INCLUDES
//DEADCODE JIM 09/02/00 */
//DEADCODE JIM 09/02/00 #if !defined(AFX_DOSBUT_H__CEB45521_2BB7_11D2_83A5_00004760763D__INCLUDED_)
//DEADCODE JIM 09/02/00 #define AFX_DOSBUT_H__CEB45521_2BB7_11D2_83A5_00004760763D__INCLUDED_
//DEADCODE JIM 09/02/00 
//DEADCODE JIM 09/02/00 #if _MSC_VER >= 1000
//DEADCODE JIM 09/02/00 #pragma once
//DEADCODE JIM 09/02/00 #endif // _MSC_VER >= 1000
//DEADCODE JIM 09/02/00 // DosBut.h : header file
//DEADCODE JIM 09/02/00 //
//DEADCODE JIM 09/02/00 
//DEADCODE JIM 09/02/00 /////////////////////////////////////////////////////////////////////////////
//DEADCODE JIM 09/02/00 // DossierButtons dialog
//DEADCODE JIM 09/02/00 
//DEADCODE JIM 09/02/00 class DossierButtons : public RowanDialog
//DEADCODE JIM 09/02/00 {
//DEADCODE JIM 09/02/00 // Construction
//DEADCODE JIM 09/02/00 public:
//DEADCODE JIM 09/02/00 	DossierButtons(int uid,CWnd* pParent = NULL);   // standard constructor
//DEADCODE JIM 09/02/00 
//DEADCODE JIM 09/02/00 // Dialog Data
//DEADCODE JIM 09/02/00 	//{{AFX_DATA(DossierButtons)
//DEADCODE JIM 09/02/00 	enum { IDD = IDDX_DOSSBUTTONS };
//DEADCODE JIM 09/02/00 	CRButton	m_IDC_AUTHORISE; 
//DEADCODE JIM 09/02/00 	CRButton	m_IDC_CENTRE;    
//DEADCODE JIM 09/02/00 	CRButton	m_IDC_PHOTO;     
//DEADCODE JIM 09/02/00 	CRButton	m_IDC_Zoom;      
//DEADCODE JIM 09/02/00 
//DEADCODE JIM 09/02/00 	//}}AFX_DATA
//DEADCODE JIM 09/02/00 
//DEADCODE JIM 09/02/00 
//DEADCODE JIM 09/02/00 // Overrides
//DEADCODE JIM 09/02/00 	// ClassWizard generated virtual function overrides
//DEADCODE JIM 09/02/00 	//{{AFX_VIRTUAL(DossierButtons)
//DEADCODE JIM 09/02/00 	protected:
//DEADCODE JIM 09/02/00 	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//DEADCODE JIM 09/02/00 	//}}AFX_VIRTUAL
//DEADCODE JIM 09/02/00 
//DEADCODE JIM 09/02/00 // Implementation
//DEADCODE JIM 09/02/00 protected:
//DEADCODE JIM 09/02/00 
//DEADCODE JIM 09/02/00 	// Generated message map functions
//DEADCODE JIM 09/02/00 	//{{AFX_MSG(DossierButtons)
//DEADCODE JIM 09/02/00 	afx_msg void OnClickedAuthorise();
//DEADCODE JIM 09/02/00 	afx_msg void OnClickedCentre();
//DEADCODE JIM 09/02/00 	afx_msg void OnClickedPhoto();
//DEADCODE JIM 09/02/00 	afx_msg void OnClickedZoom();
//DEADCODE JIM 09/02/00 	virtual BOOL OnInitDialog();
//DEADCODE JIM 09/02/00 	DECLARE_EVENTSINK_MAP()
//DEADCODE JIM 09/02/00 	//}}AFX_MSG
//DEADCODE JIM 09/02/00 	DECLARE_MESSAGE_MAP()
//DEADCODE JIM 09/02/00 };
//DEADCODE JIM 09/02/00 
//DEADCODE JIM 09/02/00 //{{AFX_INSERT_LOCATION}}
//DEADCODE JIM 09/02/00 // Microsoft Developer Studio will insert additional declarations immediately before the previous line.
//DEADCODE JIM 09/02/00 
//DEADCODE JIM 09/02/00 #endif // !defined(AFX_DOSBUT_H__CEB45521_2BB7_11D2_83A5_00004760763D__INCLUDED_)
//DEADCODE JIM 09/02/00 