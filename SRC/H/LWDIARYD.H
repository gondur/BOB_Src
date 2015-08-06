/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rradio.h"
#include "rlistbox.h"
#include "rstatic.h"
#include "rbutton.h"
//}}AFX_INCLUDES

*/
#if !defined(AFX_LWDIARYD_H__59BE6902_9C3F_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_LWDIARYD_H__59BE6902_9C3F_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LWDiaryD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LWDiaryDetails dialog
class	SquadronBase;
class Diary;


class LWDiaryDetails;
class LWDiaryDetails : public RowanDialog
{
// Construction
public:
//DEADCODE  11/02/00 	cloakref(Diary::RaidGroup,RaidGroup);
	UINT lwdiary_timer;
	static RDialog* Make(SquadNum* grupnumptr, int* currentryptr, SquadronBase**	grdetailsptr, bool quickmsn);

	LWDiaryDetails(SquadNum* grupnumptr, int* currentryptr, SquadronBase**	grdetailsptr, bool quickmsn,CWnd* pParent = NULL);   // standard constructor
	void	RefreshData(int gruppen);

	int* currentptr;
	SquadNum* grnumptr;
	SquadronBase** grdtlsptr;
	bool quickmission;
	
// Dialog Data
	//{{AFX_DATA(LWDiaryDetails)
	enum { IDD = IDD_LWDIARYDETAILS };
	CRRadio	m_IDC_RRADIODISPLAY;
	CRListBox	m_IDC_RLISTBOXCTRL1;
	CRStatic	m_IDC_RSTATICDIARYDATE;
	CRStatic	m_IDC_RSTATICPERSONNEL;
	CRStatic	m_IDC_RSTATICRESULT;
	CRStatic	m_IDC_RSTATICSTRIKEFORCE;
	CRStatic	m_IDC_RSTATICTARGET;
	CRStatic	m_IDC_RSTATICTASK;
	CRStatic	m_IDC_RSTATICTIME;
	CRStatic	m_IDC_RSTATICDETACHEDFORCE;
	CRStatic	m_IDC_RSTATICATTACHEDFORCE;
	CRStatic	m_IDC_RSTATICAIRCRAFT;
	CRListBox	m_IDC_RLISTBOXOTHERS;
	CRStatic	m_IDC_RSTATICDAMAGED;
	CRStatic	m_IDC_RSTATICDESTROYED;
	CRStatic	m_IDC_RSTATICAIRCREW;
	CRButton	m_IDC_RBUTTON_NEXT;
	CRButton	m_IDC_RBUTTON_PREV;
	CRStatic	m_IDC_RSTATICDETACHED;
	CRStatic	m_IDC_RSTATICMAIN;
	CRStatic	m_IDC_RSTATICATTACHED;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LWDiaryDetails)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Refresh();
	void RefreshButtons();
	void TotalUpAc(int& strikeac, int& attachedac, int& detachedac,int& myrole);
	struct	EncounteredAcType
	{
		PlaneTypeSelect type;
		int	encountered,
			localkilled,
			totalkilled;
	};
	void TotalEncounteredAc(EncounteredAcType* array3ofencountered);

	// Generated message map functions
	//{{AFX_MSG(LWDiaryDetails)
	afx_msg void OnSelectedRradiosize(long ButtonNum);
	afx_msg void OnSelectedRradiodisplay(long ButtonNum);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectRlistboxctrl1(long row, long column);
	afx_msg void OnSelectRlistboxothers(long row, long column);
	afx_msg void OnClickedRbuttonNext();
	afx_msg void OnClickedRbuttonPrev();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LWDIARYD_H__59BE6902_9C3F_11D3_8ADC_00A0D21BD395__INCLUDED_)
