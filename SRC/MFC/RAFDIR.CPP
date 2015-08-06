/*
	 Battle of Britain
	 Copyright (C) 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at bob@rowansoftware.com a
better place to ask is http://www.simhq.com/ or even :-
http://www.simhq.com/cgi-bin/boards/cgi-bin/forumdisplay.cgi?action=topics&forum=Battle+of+Britain&number=40&DaysPrune=20&LastLogin=
*/

// RowanDialog: // RAFDirect.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "RAFDir.h"
#include "persons2.h"
#include	"mytime.h"
#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
BITABLE(Profile::BetterRule);
ADDORABLE(Profile::BetterRule);

/////////////////////////////////////////////////////////////////////////////
// RAFDirectives dialog


RDialog*	RAFDirectives::Make(RAFDirectivesResults* dirres)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_RAFDIRECTIVES,new RAFDirectives(dirres))
			);
}


RAFDirectives::RAFDirectives(RAFDirectivesResults* dirres, CWnd* pParent /*=NULL*/)
	: RowanDialog(RAFDirectives::IDD, pParent)
{
	//{{AFX_DATA_INIT(RAFDirectives)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
		dr = dirres; 
	if (dr == NULL)
	{
		dr = new RAFDirectivesResults;
		dr->tempdir = MMC.directives.raf.current; 
	}

}
RAFDirectives::~RAFDirectives()
{
	if (dr)
		delete dr;
}
void RAFDirectives::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RAFDirectives)
	DDX_Control(pDX,IDC_RRADIOSIZE,m_IDC_RRADIOSIZE);
	DDX_Control(pDX, IDC_RRADIO_CONVOYSUPPORT, m_IDC_RRADIO_CONVOYSUPPORT);
	DDX_Control(pDX, IDC_RCOMBOFRONTLINE, m_IDC_RCOMBOFRONTLINE);
	DDX_Control(pDX, IDC_RSPINBUT_INTERCEPTS, m_IDC_RSPINBUT_INTERCEPTS);
	DDX_Control(pDX, IDC_RSPINBUT_GROUP11AF, m_IDC_RSPINBUT_GROUP11AF);
	DDX_Control(pDX, IDC_RSPINBUT_ACFACTORIES, m_IDC_RSPINBUT_ACFACTORIES);
	DDX_Control(pDX, IDC_RSPINBUT_SUPPLYFACTORIES,m_IDC_RSPINBUT_SUPPLYFACTORIES); 
	DDX_Control(pDX, IDC_RSPINBUT_HOLES,m_IDC_RSPINBUT_HOLES); 
	DDX_Control(pDX, IDC_RSPINBUT_OVERCONVOYS,m_IDC_RSPINBUT_OVERCONVOYS);
	DDX_Control(pDX, IDC_RSPINBUT_COASTAL,m_IDC_RSPINBUT_COASTAL); 
	DDX_Control(pDX, IDC_RSPINBUT_CATBELOW,m_IDC_RSPINBUT_CATBELOW);
	DDX_Control(pDX, IDC_RSPINBUT_AVAILAC,m_IDC_RSPINBUT_AVAILAC); 
	DDX_Control(pDX, IDC_RSPINBUT_INTERCEPTBEFORE,m_IDC_RSPINBUT_INTERCEPTBEFORE);
	DDX_Control(pDX, IDC_RBUTTONPROPOSAL, m_IDC_RBUTTONPROPOSAL);
	DDX_Control(pDX, IDC_RSTATIC_G1012INT, m_IDC_RSTATIC_G1012INT);
	DDX_Control(pDX, IDC_RSTATIC_G11INT, m_IDC_RSTATIC_G11INT);
	DDX_Control(pDX, IDC_TICK_SR_0, m_IDC_TICK_SR_0);
	DDX_Control(pDX, IDC_TICK_SR_1, m_IDC_TICK_SR_1);
	DDX_Control(pDX, IDC_TICK_SR_2, m_IDC_TICK_SR_2);
	DDX_Control(pDX, IDC_TICK_SR_3, m_IDC_TICK_SR_3);
	DDX_Control(pDX, IDC_TICK_SR_4, m_IDC_TICK_SR_4);
	DDX_Control(pDX, IDC_TICK_AUTOSCRAMBLE, m_IDC_TICK_AUTOSCRAMBLE);
	DDX_Control(pDX, IDC_TICK_INTERCEPT, m_IDC_TICK_INTERCEPT);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RAFDirectives, CDialog)
	//{{AFX_MSG_MAP(RAFDirectives)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RAFDirectives message handlers
int RAFDirectivesResults::FindAfUsage()
{
	int loc = RAFDirectivesResults::NORTHLONDON;
	int i = 0;
	while (		(Node_Data.squadron[i].squadron != SQ_ZERO)
		  )
	{
		UniqueID uid = Node_Data.squadron[i].homeairfield;
		TargetFighterField* af;
		af = Node_Data[uid];
		if (af->location == Target::LOC_COAST)
			loc = COASTAL;
		else if (		(loc != COASTAL)								//RDH 9Sep00
					&&	(af->location == Target::LOC_S_LON)
				)
			loc = SOUTHLONDON;
		i++;
	}
	return (loc);
}

void RAFDirectives::Refresh()		 
{
	RAFDirectivesResults::FindSquadsAvail(dr);

	CRSpinBut* spinbut;

 	spinbut=GETDLGITEM(IDC_RSPINBUT_CATBELOW);
	spinbut->Clear();
	spinbut->AddString("C");
	spinbut->AddString("B");
	spinbut->AddString("A");
	int index = 2 - dr->tempdir.restifcatbelow;
	if (index < 0)
		index = 0;
	if (index > 2)
		index = 2;

	spinbut->SetIndex(index);

	spinbut=GETDLGITEM(IDC_RSPINBUT_AVAILAC);
	spinbut->Clear()->MakeNumList(20,0,1)->SetIndex(dr->tempdir.restifavailbelow);


	index = dr->FindAfUsage();
	dr->oldfrontlinefields = index;
	dr->newfrontlinefields = index;

	CRCombo* combo;
	combo=GETDLGITEM(IDC_RCOMBOFRONTLINE);
	combo->Clear()->RESCOMBO(COASTAL,3)->
					SetIndex(index);


	int totalpatrols = 	 dr->availsquads.gr11radarpatrol +
						 dr->availsquads.gr11convoypatrol + 
						 dr->availsquads.gr11coastalpatrol + 
						 dr->availsquads.gr1012afpat + 
						 dr->availsquads.gr1012acfactpat+
						 dr->availsquads.gr1012supfactpat;

	int maxinc = Profile::MAXRAFPATROLS-totalpatrols;
	if (dr->availsquads.gr11intercept < maxinc)
		maxinc = dr->availsquads.gr11intercept;
	if (maxinc<0)
		INT3;
	spinbut=GETDLGITEM(IDC_RSPINBUT_HOLES);
	int temp =1+maxinc +dr->availsquads.gr11radarpatrol;
	spinbut->Clear()->MakeNumList(temp,0,1)->SetIndex(dr->availsquads.gr11radarpatrol);

	spinbut=GETDLGITEM(IDC_RSPINBUT_OVERCONVOYS);
	temp = 1+maxinc+dr->availsquads.gr11convoypatrol; 
	spinbut->Clear()->MakeNumList(temp,0,1)->SetIndex(dr->availsquads.gr11convoypatrol);

	temp = 1+maxinc+dr->availsquads.gr11coastalpatrol; 
	spinbut=GETDLGITEM(IDC_RSPINBUT_COASTAL);
	spinbut->Clear()->MakeNumList(temp,0,1)->SetIndex(dr->availsquads.gr11coastalpatrol);



	CRStatic*   s;
	s=GETDLGITEM(IDC_RSTATIC_G11INT);
	s->SetString(CSprintf("%i", dr->availsquads.gr11intercept));

	if (maxinc<0)
		INT3;
	maxinc = Profile::MAXRAFPATROLS-totalpatrols;
	if (dr->availsquads.gr1012intercept < maxinc)
		maxinc = dr->availsquads.gr1012intercept;


	spinbut=GETDLGITEM(IDC_RSPINBUT_GROUP11AF);
	spinbut->Clear()->MakeNumList((1+maxinc+dr->availsquads.gr1012afpat),0,1)->SetIndex(dr->availsquads.gr1012afpat);
	spinbut=GETDLGITEM(IDC_RSPINBUT_ACFACTORIES);
	spinbut->Clear()->MakeNumList((1+maxinc+dr->availsquads.gr1012acfactpat),0,1)->SetIndex(dr->availsquads.gr1012acfactpat);
	spinbut=GETDLGITEM(IDC_RSPINBUT_SUPPLYFACTORIES);
	spinbut->Clear()->MakeNumList((1+maxinc+dr->availsquads.gr1012supfactpat),0,1)->SetIndex(dr->availsquads.gr1012supfactpat);

	s=GETDLGITEM(IDC_RSTATIC_G1012INT);
	s->SetString(CSprintf("%i", dr->availsquads.gr1012intercept));
 
	CRButton* b;
	for (int i = 0; i < 5; i++)
	{
		b = GETDLGITEM(IDC_TICK_SR_0+i);

		int sr = Directives::RAF::MissTypes::ANTISWEEP+i;
		bool state = dr->tempdir.sanctioned[(Directives::RAF::MissTypes)sr];
		b->SetPressed(state);
	}

		b = GETDLGITEM(IDC_TICK_AUTOSCRAMBLE);
		b->SetPressed(MMC.autoscramble);




	CRRadio* pradio;

	pradio=GETDLGITEM(IDC_RRADIOSIZE);
//DeadCode RDH 2Aug00 	pradio->AddButton(RESSTRING(L_SQUADRONORLESS));
//DeadCode RDH 2Aug00 	pradio->AddButton(RESSTRING(PAIREDSQUADRONS));
//DeadCode RDH 2Aug00 	pradio->AddButton(RESSTRING(L_BIGWING));
//DeadCode RDH 2Aug00 
	pradio->SetCurrentSelection(dr->tempdir.unitsize);

 	pradio=GETDLGITEM(IDC_RRADIO_CONVOYSUPPORT);
//DeadCode RDH 2Aug00 	pradio->AddButton(RESSTRING(L_NORESPONSE));
//DeadCode RDH 2Aug00 	pradio->AddButton(RESSTRING(30RESPONSE));
//DeadCode RDH 2Aug00 	pradio->AddButton(RESSTRING(60RESPONSE));
//DeadCode RDH 2Aug00 	pradio->AddButton(RESSTRING(MATCHEDRESPONSE));
//DeadCode RDH 2Aug00 
	float ind = dr->tempdir.convoylevel * 3.1;
	pradio->SetCurrentSelection((int)ind);


//TEMPCODE RDH 11/05/00 	float sq  = dr->tempdir.interceptbeforetarget;
//TEMPCODE RDH 11/05/00 	sq = sq*20;
//TEMPCODE RDH 11/05/00 
//DEADCODE RDH 11/05/00 	spinbut=GETDLGITEM(IDC_RSPINBUT_INTERCEPTBEFORE);
//DEADCODE RDH 11/05/00 	spinbut->Clear()->MakeNumList(21,0,5)->SetIndex(sq);
//DEADCODE RDH 11/05/00 
	b = GETDLGITEM(IDC_TICK_INTERCEPT);
	b->SetPressed(dr->tempdir.interceptbeforetarget);


}
BOOL RAFDirectives::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRRadio* pradio;

	pradio=GETDLGITEM(IDC_RRADIOSIZE);
	pradio->AddButton(RESSTRING(L_SQUADRONORLESS));
	pradio->AddButton(RESSTRING(PAIREDSQUADRONS));
	pradio->AddButton(RESSTRING(L_BIGWING));


 	pradio=GETDLGITEM(IDC_RRADIO_CONVOYSUPPORT);
	pradio->AddButton(RESSTRING(L_NORESPONSE));
	pradio->AddButton(RESSTRING(30RESPONSE));
	pradio->AddButton(RESSTRING(60RESPONSE));
	pradio->AddButton(RESSTRING(MATCHEDRESPONSE));

	Refresh();
	 


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(RAFDirectives, CDialog)
    //{{AFX_EVENTSINK_MAP(RAFDirectives)
	ON_EVENT(RAFDirectives, IDC_RCOMBOFRONTLINE, 1 /* TextChanged */, OnTextChangedRcombofrontline, VTS_BSTR VTS_I2)
	ON_EVENT(RAFDirectives, IDC_RECONN, 1 /* Clicked */, OnClickedReconn, VTS_NONE)
	ON_EVENT(RAFDirectives, IDC_RRADIO_CONVOYSUPPORT, 1 /* Selected */, OnSelectedRradioConvoysupport, VTS_I4)
	ON_EVENT(RAFDirectives, IDC_RRADIOSIZE, 1 /* Selected */, OnSelectedRradiosize, VTS_I4)
	ON_EVENT(RAFDirectives, IDC_RSPINBUT_ACFACTORIES, 1 /* TextChanged */, OnTextChangedRspinbutAcfactories, VTS_BSTR VTS_I2)
	ON_EVENT(RAFDirectives, IDC_RSPINBUT_AVAILAC, 1 /* TextChanged */, OnTextChangedRspinbutAvailac, VTS_BSTR VTS_I2)
	ON_EVENT(RAFDirectives, IDC_RSPINBUT_CATBELOW, 1 /* TextChanged */, OnTextChangedRspinbutCatbelow, VTS_BSTR VTS_I2)
	ON_EVENT(RAFDirectives, IDC_RSPINBUT_COASTAL, 1 /* TextChanged */, OnTextChangedRspinbutCoastal, VTS_BSTR VTS_I2)
	ON_EVENT(RAFDirectives, IDC_RSPINBUT_GROUP11AF, 1 /* TextChanged */, OnTextChangedRspinbutGroup11af, VTS_BSTR VTS_I2)
	ON_EVENT(RAFDirectives, IDC_RSPINBUT_HOLES, 1 /* TextChanged */, OnTextChangedRspinbutHoles, VTS_BSTR VTS_I2)
	ON_EVENT(RAFDirectives, IDC_RSPINBUT_INTERCEPTBEFORE, 1 /* TextChanged */, OnTextChangedRspinbutInterceptbefore, VTS_BSTR VTS_I2)
	ON_EVENT(RAFDirectives, IDC_RSPINBUT_OVERCONVOYS, 1 /* TextChanged */, OnTextChangedRspinbutOverconvoys, VTS_BSTR VTS_I2)
	ON_EVENT(RAFDirectives, IDC_RSPINBUT_SUPPLYFACTORIES, 1 /* TextChanged */, OnTextChangedRspinbutSupplyfactories, VTS_BSTR VTS_I2)
	ON_EVENT_RANGE(RAFDirectives, IDC_TICK_SR_0, IDC_TICK_SR_4,1 /* Clicked */, OnClickedTickSr, VTS_I4)
	ON_EVENT(RAFDirectives, IDC_TICK_AUTOSCRAMBLE,1 /* Clicked */, OnClickedAutoScramble, VTS_NONE)
	ON_EVENT(RAFDirectives, IDC_TICK_INTERCEPT, 1 /* Clicked */, OnClickedTickIntercept, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()
	
//TEMPCODE RDH 11/05/00 	ON_EVENT_RANGE(RAFDirectives, IDC_TICK_SR_0, IDC_TICK_SR_4,1 /* Clicked */, OnClickedTickSr, VTS_I4)

void RAFDirectivesResults::FindSquadsAvail(RAFDirectivesResults* dr) 
{
	dr->availsquads.gr11total = 0;	
	dr->availsquads.gr1012total = 0;	

	int i = 0;
	while (		(Node_Data.squadron[i].squadron != SQ_ZERO)
		  )
	{
//DeadCode JIM 20Oct00 		PlaneTypeSelect	actype = Node_Data.squadron[i].AcType();

		UniqueID uid = Node_Data.squadron[i].homeairfield;
		TargetFighterField* af;
		af = Node_Data[uid];
	 	TargetSectorField*	sectorfield = af->getsectoraf();

		if (		( Node_Data.squadron[i].pilotsavail >= dr->tempdir.restifavailbelow)	//JIM 19Sep00 //THIS WAS no it used MMC.sl_min_pilot
				&&	(Node_Data.squadron[i].acavail >= dr->tempdir.restifavailbelow)
				&&	(Node_Data.squadron[i].Category() <= dr->tempdir.restifcatbelow)
		   )
		{
			if (		(sectorfield->groupname == IDS_GROUP_10)
					||	(sectorfield->groupname == IDS_GROUP_12)
				)
				dr->availsquads.gr1012total++;
		
			if 	(sectorfield->groupname == IDS_GROUP_11)
				dr->availsquads.gr11total++;	
		}
		i++;
	 }

	float temp;
	int	gr11total=dr->availsquads.gr11total;
	int	gr1012total=dr->availsquads.gr1012total;

//DeadCode JON 17Nov00 	if (dr->availsquads.gr11total+dr->availsquads.gr1012total>Profile::MAXRAFPATROLS)
//DeadCode JON 17Nov00 	{
//DeadCode JON 17Nov00 		gr11total=gr11total*Profile::MAXRAFPATROLS/(dr->availsquads.gr11total+dr->availsquads.gr1012total);
//DeadCode JON 17Nov00 		gr1012total=gr1012total*Profile::MAXRAFPATROLS/(dr->availsquads.gr11total+dr->availsquads.gr1012total);
//DeadCode JON 17Nov00 
//DeadCode JON 17Nov00 	}
	temp = dr->availsquads.gr11total;
	temp = dr->availsquads.gr1012total;
	if ((temp=dr->tempdir.gr11radarpatrol+ dr->tempdir.gr11convoypatrol+dr->tempdir.gr11coastalpatrol)>1.0)
	{
		dr->tempdir.gr11radarpatrol/=temp;
		dr->tempdir.gr11convoypatrol/=temp;
		dr->tempdir.gr11coastalpatrol/=temp;
	}
	if ((temp=dr->tempdir.gr1012afpat+dr->tempdir.gr1012acfactpat+dr->tempdir.gr1012supfactpat)>1.0)
	{
		dr->tempdir.gr1012afpat/=temp;
		dr->tempdir.gr1012acfactpat/=temp;
		dr->tempdir.gr1012supfactpat/=temp;
	}

	temp=gr11total*( dr->tempdir.gr11radarpatrol+ dr->tempdir.gr11convoypatrol+dr->tempdir.gr11coastalpatrol)
		+gr1012total*(dr->tempdir.gr1012afpat+dr->tempdir.gr1012acfactpat+dr->tempdir.gr1012supfactpat);
	int tempI=
		int(0.00001+gr11total* dr->tempdir.gr11radarpatrol)
		+int(0.00001+gr11total* dr->tempdir.gr11convoypatrol)
		+int(0.00001+gr11total* dr->tempdir.gr11coastalpatrol)
		+int(0.00001+gr1012total* dr->tempdir.gr1012afpat)
		+int(0.00001+gr1012total* dr->tempdir.gr1012acfactpat)
		+int(0.00001+gr1012total* dr->tempdir.gr1012supfactpat);

	if (tempI>Profile::MAXRAFPATROLS)
	{
		temp=Profile::MAXRAFPATROLS/temp;
		dr->tempdir.gr11radarpatrol*=temp;
		dr->tempdir.gr11convoypatrol*=temp;
		dr->tempdir.gr11coastalpatrol*=temp;
		dr->tempdir.gr1012afpat*=temp;
		dr->tempdir.gr1012acfactpat*=temp;
		dr->tempdir.gr1012supfactpat*=temp;


//DeadCode MS 18Nov00 		gr11total=gr11total*Profile::MAXRAFPATROLS/temp;
//DeadCode MS 18Nov00 		gr1012total=gr1012total*Profile::MAXRAFPATROLS/temp;
	}
	dr->availsquads.gr11maxtotal=gr11total;
	dr->availsquads.gr1012maxtotal=gr1012total;

	temp = 0.00001 + dr->tempdir.gr11radarpatrol * gr11total;
	dr->availsquads.gr11radarpatrol = temp;

	temp = 0.00001 + dr->tempdir.gr11convoypatrol  * gr11total;
	dr->availsquads.gr11convoypatrol = temp;

	temp = 0.00001 + dr->tempdir.gr11coastalpatrol  * gr11total;
	dr->availsquads.gr11coastalpatrol = temp;

	temp = 0.00001 + dr->availsquads.gr11total - dr->availsquads.gr11radarpatrol - dr->availsquads.gr11convoypatrol - dr->availsquads.gr11coastalpatrol;
	dr->availsquads.gr11intercept = temp;

	temp = 0.00001 + dr->tempdir.gr1012afpat * gr1012total;
	dr->availsquads.gr1012afpat = temp;

	temp = 0.00001 + dr->tempdir.gr1012acfactpat * gr1012total;
	dr->availsquads.gr1012acfactpat = temp;

	temp = 0.00001 + dr->tempdir.gr1012supfactpat * gr1012total;
	dr->availsquads.gr1012supfactpat = temp;

	temp = 0.00001 + dr->availsquads.gr1012total - dr->availsquads.gr1012afpat - dr->availsquads.gr1012acfactpat - dr->availsquads.gr1012supfactpat;
	dr->availsquads.gr1012intercept = temp;


}



void RAFDirectives::OnOK() 
{
#ifndef	BOB_DEMO_VER

	RAFDirectivesResults::SetDirectivesResults(dr);

	if (dr->dirresults[0].target)
	{
		MiscToolBar().OpenRAFDirectiveResultsToggle(dr);
		dr = NULL;
	}
	else
	{
		MMC.directives.raf.current=dr->tempdir;
	 	Node_Data.SetRAFReadiness();
		MiscToolBar().OpenEmptyDirectiveResults();
	}

#endif

	CDialog::OnOK();
}
void RAFDirectives::OnCancel() 
{
#ifndef	BOB_DEMO_VER
	if (m_pView->m_currentpage==0)
		MiscToolBar().OpenEmptyDirectiveResults();
	
	CDialog::OnCancel();
#endif
}

void RAFDirectives::OnTextChangedRcombofrontline(LPCTSTR Caption, short index) 
{
	dr->newfrontlinefields = index;
	
}

void RAFDirectives::OnClickedReconn() 
{
	// TODO: Add your control notification handler code here
	
}

void RAFDirectives::OnSelectedRradioConvoysupport(long ButtonNum) 
{
	float support = ButtonNum;
	dr->tempdir.convoylevel = support/3;	
}

void RAFDirectives::OnSelectedRradiosize(long ButtonNum) 
{
	dr->tempdir.unitsize = (Directives::RAF::Dir::GeneralSize)ButtonNum;	
}

void RAFDirectives::OnTextChangedRspinbutAcfactories(LPCTSTR caption, short Index) 
{
	float sq = Index;
	dr->tempdir.gr1012acfactpat = sq/dr->availsquads.gr1012maxtotal;
	Refresh();	
	
}

void RAFDirectives::OnTextChangedRspinbutAvailac(LPCTSTR caption, short Index) 
{
	dr->tempdir.restifavailbelow =Index;
	Refresh();
}

void RAFDirectives::OnTextChangedRspinbutCatbelow(LPCTSTR caption, short Index) 
{
	dr->tempdir.restifcatbelow = 2 - Index;
	Refresh();	
}

void RAFDirectives::OnTextChangedRspinbutCoastal(LPCTSTR caption, short Index) 
{
	float sq = Index;
	dr->tempdir.gr11coastalpatrol = sq/dr->availsquads.gr11maxtotal;
	Refresh();	
	
}

void RAFDirectives::OnTextChangedRspinbutGroup11af(LPCTSTR caption, short Index) 
{
	float sq = Index;
	dr->tempdir.gr1012afpat = sq/dr->availsquads.gr1012maxtotal;
	Refresh();	
	
}

void RAFDirectives::OnTextChangedRspinbutHoles(LPCTSTR caption, short Index) 
{
	float sq = Index;
	dr->tempdir.gr11radarpatrol = sq/dr->availsquads.gr11maxtotal;
	Refresh();	
	
}

void RAFDirectives::OnTextChangedRspinbutInterceptbefore(LPCTSTR caption, short Index) 
{
//DEADCODE RDH 11/05/00 	float sq = Index;
//DEADCODE RDH 11/05/00 	dr->tempdir.interceptbeforetarget = sq/20;
//DEADCODE RDH 11/05/00 	Refresh();	
	
}




void RAFDirectives::OnTextChangedRspinbutOverconvoys(LPCTSTR caption, short Index) 
{
	float sq = Index;
	dr->tempdir.gr11convoypatrol = sq/dr->availsquads.gr11maxtotal;
	Refresh();	
	
}

void RAFDirectives::OnTextChangedRspinbutSupplyfactories(LPCTSTR caption, short Index) 
{
	float sq = Index;
	dr->tempdir.gr1012supfactpat = sq/dr->availsquads.gr1012maxtotal;
	Refresh();	
	
}
void RAFDirectives::OnClickedAutoScramble() 
{
	if (MMC.autoscramble)
		MMC.autoscramble = false;
	else
		MMC.autoscramble = true;
}

void RAFDirectives::OnClickedTickSr(int id) 
{
	id = id - IDC_TICK_SR_0;
	int sr = Directives::RAF::MissTypes::ANTISWEEP+id;



	if	(dr->tempdir.sanctioned[(Directives::RAF::MissTypes)sr])
	   dr->tempdir.sanctioned %= (Directives::RAF::MissTypes)sr;
	else
	   dr->tempdir.sanctioned |= (Directives::RAF::MissTypes)sr;
	Refresh();	


	
}
void	RAFDirectivesResults::SetDirectivesResults(RAFDirectivesResults* dr)
{
	int patrols, k = 0;

//DeadCode JIM 20Oct00 	Profile::BetterRule br = Profile::BR_NONE;


//coastal, use radar
	patrols = dr->availsquads.gr11coastalpatrol/(dr->tempdir.unitsize+1);
	if (	(dr->availsquads.gr11coastalpatrol != 0) && (patrols < 1))
		patrols = 1;
	SetStdPatrolTargets(dr, CLRadarBAND, LUF_FighterLF2BAND, true);
	k = SetPatrols(dr, patrols, k, Profile::BR_B_EITHERWL_ALLOW11);
//dead radar
	patrols = dr->availsquads.gr11radarpatrol/(dr->tempdir.unitsize+1);
	if (	(dr->availsquads.gr11radarpatrol != 0) && (patrols < 1))
		patrols = 1;
	SetStdPatrolTargets(dr, CLRadarBAND, LUF_FighterLF2BAND, false);
	k = SetPatrols(dr, patrols, k, Profile::BR_B_EITHERWL_ALLOW11);

//convoys
	patrols = dr->availsquads.gr11convoypatrol/(dr->tempdir.unitsize+1);
	if (	(dr->availsquads.gr11convoypatrol != 0) && (patrols < 1))
		patrols = 1;
	SetStdPatrolTargets(dr, BritBoatBAND, GermBoatBAND, true);
	k = SetPatrols(dr, patrols, k, Profile::BR_B_EITHERWL_ALLOW11);

//airfield patrols	
	patrols = dr->availsquads.gr1012afpat/(dr->tempdir.unitsize+1);
	if (	(dr->availsquads.gr1012afpat != 0) && (patrols < 1))
		patrols = 1;
	SetAfPatrolTargets(dr);
	k = SetPatrols(dr, patrols, k, Profile::BR_B_EITHERWL);
//supply factory patrols
//DeadCode RDH 10Sep00 	patrols = dr->availsquads.gr1012supfactpat/(dr->tempdir.unitsize+1);
//DeadCode RDH 10Sep00 	if (	(dr->availsquads.gr1012supfactpat != 0) && (patrols < 1))
//DeadCode RDH 10Sep00 		patrols = 1;
//DeadCode RDH 10Sep00 
//DeadCode RDH 10Sep00 	
//DeadCode RDH 10Sep00 	SetStdPatrolTargets(dr, PowerStationBAND, AircraftFactoryBAND, true);
//DeadCode RDH 10Sep00 
//DeadCode RDH 10Sep00 
//DeadCode RDH 10Sep00 	k = SetPatrols(dr, patrols, k, Profile::BR_B_EITHERWL);

	//a/c factory patrols												//RDH 16Sep00
	patrols = dr->availsquads.gr1012acfactpat/(dr->tempdir.unitsize+1);
	if (	( dr->availsquads.gr1012acfactpat != 0) && (patrols < 1))
		patrols = 1;
	SetFactPatrolTargets(dr,  true);	
	k = SetPatrols(dr, patrols, k, Profile::BR_B_EITHERWL);


	
	patrols = dr->availsquads.gr1012supfactpat/(dr->tempdir.unitsize+1);
	if (	( dr->availsquads.gr1012supfactpat != 0) && (patrols < 1))
		patrols = 1;
	SetFactPatrolTargets(dr, false);	
	k = SetPatrols(dr, patrols, k, Profile::BR_B_EITHERWL);
																		//RDH 16Sep00
	dr->dirresults[k].target = UID_NULL;

}
int RAFDirectivesResults::SetPatrols(RAFDirectivesResults* dr, int patrols, int k, Profile::BetterRule br)
{

	if (dr->target[0].target == IllegalBAND)
		return k;
	int j = 0;
	int targets=0;
	while (	(dr->target[targets].target != IllegalBAND))
		targets++;

	int ETA=HR01;
	if ((br&Profile::BR_B_ALLOWGRP11) && targets>patrols)
		ETA=HR02;
	if (targets*2<patrols)	
		ETA=MIN30;
	if (targets*3<patrols)
		patrols=targets*3;

	while (	(patrols > 0))
	{
		dr->dirresults[k].target = dr->target[j].target;
		dr->dirresults[k].unitsize = dr->tempdir.unitsize;
		dr->dirresults[k].ETA=ETA;
		dr->dirresults[k].mission = MMC.directives.raf.userprofiles[Directives::RAF::MissTypes::PATROL];	//JIM 18Aug00
		dr->dirresults[k].mission.acselectionrules = br; 
		dr->dirresults[k].mission.hurr.numac =  (dr->dirresults[k].unitsize+1)*12;
		dr->dirresults[k].mission.spit.numac =  0;
		dr->dirresults[k].mission.packageattackmethod = Profile::AM_PATROL;
		patrols--;
		j++;
		k++;
		if (dr->target[j].target == IllegalBAND)
		{
			j=0;
			ETA+=HR01+MIN15;

		}
	}
	return(k);
}

void	RAFDirectivesResults::SetStdPatrolTargets(RAFDirectivesResults* dr,int uidbandstart, int uidbandend,bool patrolifalive)
{


	int i = 0, uid= uidbandstart, currtrg = 0;
	while 	(i < MAX_TARGETS)
	{
		dr->target[i].priority = 30000;	//Target::TP_MAX;
		dr->target[i++].target = (UniqueID)IllegalBAND;

	}


	while (		(uid < uidbandend)
			&&	(currtrg < MAX_TARGETS)
		   )
	{
		TargetGroup* trg;
		trg = Node_Data[(UniqueID)uid];
		ItemBasePtr p;
		p=Persons2::ConvertPtrUID(UniqueID(uid));

		if ((trg && p)	&&	(		((p->Status.deaded)	&& (!patrolifalive))
								||	(!(p->Status.deaded)	&& (patrolifalive))
							)
			)
		{
			currtrg = InsertTarget(dr->target,(UniqueID)uid, currtrg);
		}
		uid++;
	}




}
void	RAFDirectivesResults::SetFactPatrolTargets(RAFDirectivesResults* dr, bool acfact)
{
	int uidbandstart = AircraftFactoryBAND;
	int uidbandend = DocksBAND;

	int i = 0, uid= uidbandstart, currtrg = 0;
	while 	(i < MAX_TARGETS)
	{
		dr->target[i].priority = 30000;	//Target::TP_MAX;
		dr->target[i++].target = (UniqueID)IllegalBAND;

	}


	while (		(uid < uidbandend)
			&&	(currtrg < MAX_TARGETS)
		   )
	{
		TargetGroup* trg;
		trg = Node_Data[(UniqueID)uid];
		ItemBasePtr p;
		p=Persons2::ConvertPtrUID(UniqueID(uid));

		if	((trg && p)	&&	(!p->Status.deaded)
			)
		{
			if (	(		(trg->truetargtype == Target::TT_SPITASSEMBLY)
						||	(trg->truetargtype == Target::TT_HURRASSEMBLY)
					)
					&&
					(
						(acfact)
					)
				||
					(		(trg->truetargtype == Target::TT_SPITPARTS)
						||	(trg->truetargtype == Target::TT_HURRPARTS)
						||	(trg->truetargtype == Target::TT_ARMAMENTS)
					)
					&&
					(
						(!acfact)
					)
				)
			   	currtrg = InsertTarget(dr->target,(UniqueID)uid, currtrg);
		}
		uid++;
	}

}




void	RAFDirectivesResults::SetAfPatrolTargets(RAFDirectivesResults* dr)
{
	int  uidbandstart = RAF_FighterAFBAND;
	int uidbandend = RAF_BomberAFBAND;

	int i = 0, uid= uidbandstart, currtrg = 0;
	while 	(i < MAX_TARGETS)
	{
		dr->target[i].priority = 30000;	//Target::TP_MAX;
		dr->target[i++].target = (UniqueID)IllegalBAND;

	}


	while (		(uid < uidbandend)
			&&	(currtrg < MAX_TARGETS)
		   )
	{
		TargetFighterField* af;
		af = Node_Data[(UniqueID)uid];
		if (af)
		{
		 	TargetSectorField*	sectorfield = af->getsectoraf();
			if  (		(sectorfield->groupname == IDS_GROUP_11)
					&&	(af->location != Target::LOC_COAST)				//RDH 12Oct00
				)
			{
				currtrg = InsertTarget(dr->target,(UniqueID)uid, currtrg);
			}
		}
		uid++;
	}

}
int	RAFDirectivesResults::InsertTarget(TargetList* target, UniqueID uid, int currtrg)
{
	int i = 0, trgpriority;
	TargetGroup*	tg = Node_Data[uid];

	trgpriority = tg->truepriority;

	while  (		(i < currtrg)
				&&	(target[i].priority  < 
						trgpriority
					)
			)
		i++;

	for (int j = MAX_TARGETS-1; j > i;j--)
		target[j] = target[j-1];

	
	target[i].target = uid;
	target[i].priority = trgpriority;

	currtrg++;
	return(currtrg);
}

void RAFDirectives::OnClickedTickIntercept() 
{
	if (dr->tempdir.interceptbeforetarget)
		dr->tempdir.interceptbeforetarget = false;
	else
		dr->tempdir.interceptbeforetarget = true;
	Refresh();
}
void	Directives::RAF::SessionAI()
{
	Node_Data.FillRAFStrengthInfo(false);
	RAFDirectivesResults* dr = new RAFDirectivesResults;

	dr->oldfrontlinefields = dr->FindAfUsage();

	if (Node_Data.RAFstrengthinfo[Node_Data.RAFTOTAL].catA < 20)
		dr->newfrontlinefields = 
			RAFDirectivesResults::NORTHLONDON;

	else if (Node_Data.RAFstrengthinfo[Node_Data.RAFTOTAL].catA < 30)
		dr->newfrontlinefields = 
			RAFDirectivesResults::SOUTHLONDON;
	else if (Node_Data.RAFFindPercentAvail(CLRadarBAND, LUF_FighterLF2BAND, Target::TP_RADAR_HP, Target::TP_RADAR) >50) //< 40)	//MS 17Nov00
		dr->newfrontlinefields = 
				RAFDirectivesResults::SOUTHLONDON;
	else
		dr->newfrontlinefields = 
				RAFDirectivesResults::COASTAL;

	if (dr->oldfrontlinefields != dr->newfrontlinefields)
		dr->MoveSquadronswrtFrontLine();

	Node_Data.SwapSquadron();
	delete dr;
}
void	Directives::RAF::ModifyPatrols()
{
//DeadCode RDH 10Sep00 	float fractionpatrolsused= MMC.directives.raf.current.gr1012supfactpat 
//DeadCode RDH 10Sep00 									   +MMC.directives.raf.current.gr1012afpat
//DeadCode RDH 10Sep00 									   +MMC.directives.raf.current.gr1012acfactpat;

	RAFDirectivesResults* dr = new RAFDirectivesResults;
	dr->tempdir = MMC.directives.raf.current; 
	
	RAFDirectivesResults::FindSquadsAvail(dr);

	int msnaf, msnsupfact, msnacfact;

	msnaf = 0;
	msnsupfact = 0;
	msnacfact = 0;


	int pack=0;
	while (pack < Profile::MAX_PACKS)
	{
   	 	Profile& pk = Todays_Packages.pack[pack];
		if  (		(pk.attackmethod >= Profile::AM_LWPACKS)
				&&	(Todays_Packages.pack[pack].packagestatus!=Profile::PS_SPARE)
			)
		{
			
			int uidband;
			uidband=Persons2::getbandfromUID(pk.packagetarget[0].currentid);
	   		switch (uidband)
			{
				case		RAF_FighterAFBAND:
				case		RAF_BomberAFBAND:
				case		RAF_CoastalAFBAND:
				{
					msnaf++;
					break;
				}
 				case	AircraftFactoryBAND:
				{
					TargetGroup* g=Node_Data[pk.packagetarget[0].currentid];
					if (g)
					switch (g->truetargtype)
					{
						case Target::TT_SPITASSEMBLY:
						case Target::TT_HURRASSEMBLY:
						{
							msnacfact++;
							break;
						}
						case Target::TT_SPITPARTS:
						case Target::TT_HURRPARTS:
						case Target::TT_ARMAMENTS:
						{
							msnsupfact++;
							break;
						}
					}
				}
			}


		}
		pack++;
	}



	if  (		(msnaf == 0)
			&&	(dr->availsquads.gr1012afpat)
		)
	{
		dr->availsquads.gr1012afpat--;
		dr->availsquads.gr1012intercept++;
	}
	if  (		(msnacfact == 0)
			&&	(dr->availsquads.gr1012acfactpat)
		)
	{
		dr->availsquads.gr1012acfactpat--;
		dr->availsquads.gr1012intercept++;
	}
	if  (		(msnsupfact == 0)
			&&	(dr->availsquads.gr1012supfactpat)
		)
	{
		dr->availsquads.gr1012supfactpat--;
		dr->availsquads.gr1012intercept++;
	}

	if (msnaf > 3)
		msnaf = 3;
	if 	(dr->availsquads.gr1012intercept < msnaf)
		msnaf = dr->availsquads.gr1012intercept;
	 dr->availsquads.gr1012intercept -= msnaf;
	 dr->availsquads.gr1012afpat += msnaf;


	if (msnacfact > 3)
		msnacfact = 3;
	if 	(dr->availsquads.gr1012intercept < msnacfact)
		msnacfact = dr->availsquads.gr1012intercept;
	 dr->availsquads.gr1012intercept -= msnacfact;
	 dr->availsquads.gr1012acfactpat += msnacfact;


 	if (msnsupfact > 3)
		msnsupfact = 3;
	if 	(dr->availsquads.gr1012intercept < msnsupfact)
		msnsupfact = dr->availsquads.gr1012intercept;
	 dr->availsquads.gr1012intercept -= msnsupfact;
	 dr->availsquads.gr1012supfactpat += msnsupfact;


	float sqnum = dr->availsquads.gr1012afpat;
	dr->tempdir.gr1012afpat = sqnum/dr->availsquads.gr1012total;

	sqnum = dr->availsquads.gr1012acfactpat;
	dr->tempdir.gr1012acfactpat = sqnum/dr->availsquads.gr1012total;

	sqnum = dr->availsquads.gr1012supfactpat;
	dr->tempdir.gr1012supfactpat = sqnum/dr->availsquads.gr1012total;



	MMC.directives.raf.current = dr->tempdir;
	if (dr)
		delete dr;

}
 void	Directives::RAF::AI()
{
	 ModifyPatrols();

	Directives::RAF::HistTypes olddir = MMC.rafdir;

	//need to change MMC.rafdir here when necessary
	//when and if implemented need to only do for pilot

 	if (olddir  != MMC.rafdir)
	{
		 MMC.phasechanged = 1;
		 RAFDirectivesResults::SetUpRAFDirectives(MMC.rafdir);
	}

 }
