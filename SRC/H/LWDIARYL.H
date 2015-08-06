/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
#include "rradio.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_LWDIARYL_H__59BE6903_9C3F_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_LWDIARYL_H__59BE6903_9C3F_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWDiaryL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWDiaryList dialog
class	SquadronBase;

class LWDiaryList : public RowanDialog
{
// Construction
public:
	static RDialog* Make(SquadNum* grupnumptr, int* currentryptr, SquadronBase**	grdetailsptr);

	LWDiaryList(SquadNum* grupnumptr, int* currentryptr, SquadronBase**	grdetailsptr,CWnd* pParent = NULL);   // standard constructor
	void	RefreshData(int gruppen);


	int* currentptr;
	SquadNum* grnumptr;
	SquadronBase** grdtlsptr;

// Dialog Data
	//{{AFX_DATA(LWDiaryList)
	enum { IDD = IDD_LWDIARYLIST };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRRadio	m_IDC_RRADIODISPLAY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWDiaryList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Refresh();

	// Generated message map functions
	//{{AFX_MSG(LWDiaryList)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectedRradiosize(long ButtonNum);
	afx_msg void OnSelectedRradiodisplay(long ButtonNum);
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWDIARYL_H__59BE6903_9C3F_11D3_8ADC_00A0D21BD395__INCLUDED_)
