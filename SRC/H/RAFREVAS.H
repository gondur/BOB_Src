/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_RAFREVAS_H__CDABD340_A197_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_RAFREVAS_H__CDABD340_A197_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RAFRevAs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RAFReviewAsset dialog

class RAFReviewAsset : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	RAFReviewAsset(CWnd* pParent = NULL);   // standard constructor
	~RAFReviewAsset();
	enum	{CHAINHOME, CHAINLOW, KEYINDUSTRY, SUPPORTINDUSTRY, DOCKS,LONDON,
				GR10AF, GR11AF, GR12AF, TOTALAF, MAXTARGETTYPES};
	struct	TrgInfo
	{
		int ok;
		int damaged;
		int destroyed;
		int unknown;
	};

	TrgInfo	trginfo[MAXTARGETTYPES];
// Dialog Data
	//{{AFX_DATA(RAFReviewAsset)
	enum { IDD = IDD_RAFREVIEWASSETS };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RAFReviewAsset)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FillTrgInfoArray();
	LWDirectivesResults*		dr;
	void FillTrgInfo(int out, int in, int cnt);

	// Generated message map functions
	//{{AFX_MSG(RAFReviewAsset)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAFREVAS_H__CDABD340_A197_11D3_8ADC_00A0D21BD395__INCLUDED_)
