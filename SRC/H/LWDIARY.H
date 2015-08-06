/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rcombo.h"
#include "rspinbut.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_LWDIARY_H__59BE6901_9C3F_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_LWDIARY_H__59BE6901_9C3F_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWDiary.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWDiary dialog
class	SquadronBase;

class LWDiary : public RowanDialog
{
// Construction
public:
	static RDialog* Make(SquadNum squad);

	LWDiary(CWnd* pParent = NULL);   // standard constructor


		enum	{MAX_SQDETAILS = 256};
	int currentry;
	int* currentryptr;
	SquadNum* grnumptr;
	SquadNum grnum;
	SquadronBase*	grdetails[MAX_SQDETAILS];
	SquadronBase**	grdetailsptr;	
	int geschwadertype;
	enum	{MAX_GRUPPE = 100};
	int		Gruppe[MAX_GRUPPE];
	int maxsquads;
  	void	FillList();


// Dialog Data
	//{{AFX_DATA(LWDiary)
	enum { IDD = IDD_LWDIARY };
	CRCombo	m_IDC_RCOMBOGROUP;
	CRCombo	m_IDC_RCOMBOGESCHWADER;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWDiary)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void	RefreshData(int effect);
	void	FindGeschwader();
	void	Refresh();
public:
	static  void	FillGruppeDetails(SquadNum SquadNum,SquadronBase* currrecord,SquadronBase** table,int& currentry);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LWDiary)
	virtual BOOL OnInitDialog();
	afx_msg void OnTextChangedRcombogroup(LPCTSTR text, short index);
	afx_msg void OnTextChangedRcombogeschwader(LPCTSTR Caption, short index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWDIARY_H__59BE6901_9C3F_11D3_8ADC_00A0D21BD395__INCLUDED_)
