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

// RowanDialog: // TwoDPref.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "TwoDPref.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// TwoDPref dialog

RDialog*	TwoDPref::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new TwoDPref())
			);
}


TwoDPref::TwoDPref(CWnd* pParent /*=NULL*/)
	: RowanDialog(TwoDPref::IDD, pParent)
{
	//{{AFX_DATA_INIT(TwoDPref)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void TwoDPref::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TwoDPref)
	DDX_Control(pDX, IDC_CBO_MAPSCREEN, m_IDC_CBO_MAPSCREEN);
	DDX_Control(pDX, IDC_CBO_COLOURDEPTH, m_IDC_CBO_COLOURDEPTH);
	DDX_Control(pDX, IDC_CBO_INTROART, m_IDC_CBO_INTROART);
	DDX_Control(pDX, IDC_CBO_MAPEVENTS, m_IDC_CBO_MAPEVENTS);
	DDX_Control(pDX, IDC_CBO_OPTIONS, m_IDC_CBO_OPTIONS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TwoDPref, CDialog)
	//{{AFX_MSG_MAP(TwoDPref)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TwoDPref message handlers
void TwoDPref::PreDestroyPanel()
{
//TempCode MS 17Nov100 	if (Save_Data.ui_horizontalres[SaveDataLoad::UIR_FIRST]<1024)
//TempCode MS 17Nov100 	{
//TempCode MS 17Nov100 		Save_Data.ui_horizontalres[SaveDataLoad::UIR_SCRAMBLE]=
//TempCode MS 17Nov100 			Save_Data.ui_horizontalres[SaveDataLoad::UIR_MAP]=
//TempCode MS 17Nov100 				Save_Data.ui_horizontalres[SaveDataLoad::UIR_FRAG]=
//TempCode MS 17Nov100 					1024;
//TempCode MS 17Nov100 	}

	if (RFullPanelDial::gamestate==RFullPanelDial::TITLE)
		Save_Data.ChangeMode(SaveData::UIR_SCRAMBLE);
	else
		Save_Data.ChangeMode(SaveData::UIR_FRAG);
}


BEGIN_EVENTSINK_MAP(TwoDPref, CDialog)
    //{{AFX_EVENTSINK_MAP(TwoDPref)
	ON_EVENT(TwoDPref, IDC_CBO_COLOURDEPTH, 1 /* TextChanged */, OnTextChangedCboColourdepth, VTS_BSTR VTS_I2)
	ON_EVENT(TwoDPref, IDC_CBO_MAPSCREEN, 1 /* TextChanged */, OnTextChangedCboMapscreen, VTS_BSTR VTS_I2)
	ON_EVENT(TwoDPref, IDC_CBO_MAPEVENTS, 1 /* TextChanged */, OnTextChangedCboMapevents, VTS_BSTR VTS_I2)
	ON_EVENT(TwoDPref, IDC_CBO_INTROART, 1 /* TextChanged */, OnTextChangedCboIntroart, VTS_BSTR VTS_I2)
	ON_EVENT(TwoDPref, IDC_CBO_OPTIONS, 1 /* TextChanged */, OnTextChangedCboOptions, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void	TwoDPref::SetOtherCombos() 	
{
	GETDLGITEM(IDC_CBO_INTROART)->Clear();
	GETDLGITEM(IDC_CBO_INTROART)->AddString(CSprintf(desktopstr,possiblemapreses[currdefaultres].horres,possiblemapreses[currdefaultres].vertres));
	GETDLGITEM(IDC_CBO_INTROART)->AddString(CSprintf("%ix%i",possiblemapreses[lowestres].horres,possiblemapreses[lowestres].vertres));
	GETDLGITEM(IDC_CBO_INTROART)->AddString(CSprintf("%ix%i",possiblemapreses[res1024res].horres,possiblemapreses[res1024res].vertres));
	if (Save_Data.ui_horizontalres[SaveData::UIR_SMACKER]==0)
		GETDLGITEM(IDC_CBO_INTROART)->SetIndex(0);
	elseif (Save_Data.ui_horizontalres[SaveData::UIR_SMACKER]<1024)
		GETDLGITEM(IDC_CBO_INTROART)->SetIndex(1);
	else
		GETDLGITEM(IDC_CBO_INTROART)->SetIndex(2);
	
	GETDLGITEM(IDC_CBO_MAPEVENTS)->Clear();
	if (currmapres)
		GETDLGITEM(IDC_CBO_MAPEVENTS)->AddString(CSprintf("%ix%i",possiblemapreses[currmapres].horres,possiblemapreses[currmapres].vertres));
	else
		GETDLGITEM(IDC_CBO_MAPEVENTS)->AddString(CSprintf("%ix%i",possiblemapreses[currdefaultres].horres,possiblemapreses[currdefaultres].vertres));
	GETDLGITEM(IDC_CBO_MAPEVENTS)->AddString(CSprintf("%ix%i",possiblemapreses[res1024res].horres,possiblemapreses[res1024res].vertres));
	if (fragis1024)
		GETDLGITEM(IDC_CBO_MAPEVENTS)->SetIndex(1);
	else
		GETDLGITEM(IDC_CBO_MAPEVENTS)->SetIndex(0);

	GETDLGITEM(IDC_CBO_OPTIONS)->Clear();
	GETDLGITEM(IDC_CBO_OPTIONS)->AddString(CSprintf(desktopstr,possiblemapreses[currdefaultres].horres,possiblemapreses[currdefaultres].vertres));
	GETDLGITEM(IDC_CBO_OPTIONS)->AddString(CSprintf("%ix%i",possiblemapreses[res1024res].horres,possiblemapreses[res1024res].vertres));
	if (Save_Data.ui_horizontalres[SaveData::UIR_SCRAMBLE]==0)
		GETDLGITEM(IDC_CBO_OPTIONS)->SetIndex(0);
	else
		GETDLGITEM(IDC_CBO_OPTIONS)->SetIndex(1);

	CRCombo* combo=GETDLGITEM(IDC_CBO_COLOURDEPTH);
	combo->Clear();
	int availcolours=possiblemapreses[res1024res].canbitsminus8;
	if (currmapres)
		availcolours&=possiblemapreses[currmapres].canbitsminus8;
	else
		availcolours&=possiblemapreses[currdefaultres].canbitsminus8;
	int setind=0;
	if (Save_Data.ui_horizontalres[SaveData::UIR_FIRST_DEPTH]>16)
		combo->AddString(RESSTRING(DEFAULTSPC)+CSprintf(RESSTRING(TRUECOLOUR),Save_Data.ui_horizontalres[SaveData::UIR_FIRST_DEPTH]));
	else
		combo->AddString(RESSTRING(DEFAULTSPC)+CSprintf(RESSTRING(HIGHCOLOUR),Save_Data.ui_horizontalres[SaveData::UIR_FIRST_DEPTH]));
	for (int i=8,b=1,outind=1;i<=32;i++,b+=b)
		if (availcolours&b)
		{
			if (i>16)
				combo->AddString(CSprintf(RESSTRING(TRUECOLOUR),i));
			else
				combo->AddString(CSprintf(RESSTRING(HIGHCOLOUR),i));
			if (Save_Data.ui_colourdepth==i)
				setind=outind;
			outind++;
		}
	combo->SetIndex(setind);
}

BOOL TwoDPref::OnInitDialog() 
{
	CDialog::OnInitDialog();
	possiblemapreses[0].horres=0;
	possiblemapreses[0].canbitsminus8=	PossReses::CB_ALL;
	int	maxpossmodes=1;
	DEVMODE	devmode;
	devmode.dmSize=sizeof(DEVMODE);
	devmode.dmDriverExtra=0;
	for (int imode=0;;imode++)
		if (EnumDisplaySettings(NULL,imode,&devmode))
		{
			devmode.dmSize=sizeof(DEVMODE);
			devmode.dmDriverExtra=0;
			devmode.dmFields=DM_BITSPERPEL+DM_PELSWIDTH+DM_PELSHEIGHT;
			if (ChangeDisplaySettings(&devmode,CDS_TEST)==DISP_CHANGE_SUCCESSFUL)
				if (devmode.dmBitsPerPel>=15  && devmode.dmPelsWidth>=512 && devmode.dmPelsHeight>=384)
				{
					for (int m=1;m<maxpossmodes;m++)
						breakif(possiblemapreses[m].horres==devmode.dmPelsWidth);
					if (m==maxpossmodes && maxpossmodes<PossReses::MAX_RES_MODES)
					{
						maxpossmodes++;
						possiblemapreses[m].horres=devmode.dmPelsWidth;
						possiblemapreses[m].vertres=devmode.dmPelsHeight;
						possiblemapreses[m].canbitsminus8=PossReses::CB_NONE;
					}
					
					if (possiblemapreses[m].vertres!=devmode.dmPelsHeight)
					{
						float	newratio=(4.0/3.0)/(float(devmode.dmPelsWidth)/devmode.dmPelsHeight),
								oldratio=(4.0/3.0)/(float(devmode.dmPelsWidth)/possiblemapreses[m].vertres);
						if (newratio>1.0)
							newratio=1.0/newratio;
						if (oldratio>1.0)
							oldratio=1.0/oldratio;
						if (newratio>oldratio)	//closer to 4:3
						{		//cancel modes found so far and use this mode instead
							possiblemapreses[m].vertres=devmode.dmPelsHeight;
							possiblemapreses[m].canbitsminus8=PossReses::CB_NONE;
						}
						else	//cancel this mode and keep modes found so far
							devmode.dmBitsPerPel=0;
					}
					if (devmode.dmBitsPerPel>=15)
					{
						possiblemapreses[m].canbitsminus8|=1<<(devmode.dmBitsPerPel-8);
					}
				}
			devmode.dmSize=sizeof(DEVMODE);
			devmode.dmDriverExtra=0;
		}
		else
			break;
	maxreses=maxpossmodes;
	if (Save_Data.ui_horizontalres[SaveData::UIR_FIRST]==0)
	{
		DEVMODE	devmode;
		devmode.dmSize=sizeof(DEVMODE);
		devmode.dmDriverExtra=0;
		EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&devmode);
		Save_Data.ui_horizontalres[SaveData::UIR_FIRST]=devmode.dmPelsWidth;
		Save_Data.ui_horizontalres[SaveData::UIR_FIRSTH]=devmode.dmPelsHeight;
		Save_Data.ui_horizontalres[SaveData::UIR_FIRSTFREQ]=devmode.dmDisplayFrequency;
		Save_Data.ui_horizontalres[SaveData::UIR_FIRST_DEPTH]=devmode.dmBitsPerPel;
		Save_Data.ui_horizontalres[SaveData::UIR_FIRST_FLAGS]=devmode.dmDisplayFlags;
	}
	if (Save_Data.ui_horizontalres[SaveDataLoad::UIR_FIRST]<1024)
	{
//TempCode MS 17Nov100 		Save_Data.ui_horizontalres[SaveDataLoad::UIR_SCRAMBLE]=
//TempCode MS 17Nov100 			Save_Data.ui_horizontalres[SaveDataLoad::UIR_MAP]=
//TempCode MS 17Nov100 				Save_Data.ui_horizontalres[SaveDataLoad::UIR_FRAG]=
//TempCode MS 17Nov100 					1024;
		desktopstr=RESSTRING(RESWARNING)+" "+RESSTRING(DESKTOP);
	}
	else
		desktopstr=RESSTRING(DESKTOP);

	currmapres=0;
	currdefaultres=0;
	lowestres=0;
	res1024res=0;
	int lowestsofar=1000000;
	for (int i=1;i<maxpossmodes;i++)
	{
		if (Save_Data.ui_horizontalres[SaveData::UIR_FIRST]==possiblemapreses[i].horres)
			currdefaultres=i;
		if (Save_Data.ui_horizontalres[SaveData::UIR_MAP]==possiblemapreses[i].horres)
			currmapres=i;	
		if (possiblemapreses[i].horres==1024)
			res1024res=i;
		if (possiblemapreses[i].horres<lowestsofar)
		{
			lowestsofar=possiblemapreses[i].horres;
			lowestres=i;
		}
	}
	fragis1024=Save_Data.ui_horizontalres[SaveData::UIR_FRAG]==1024;
	CRCombo* combo=GETDLGITEM(IDC_CBO_MAPSCREEN);
	combo->Clear();
	combo->AddString(CSprintf(desktopstr,possiblemapreses[currdefaultres].horres,possiblemapreses[currdefaultres].vertres));
	int	indcount=res1024res-1;
	while (++indcount<maxreses)
		combo->AddString(CSprintf("%ix%i",possiblemapreses[indcount].horres,possiblemapreses[indcount].vertres));
	if (currmapres)
		combo->SetIndex(currmapres-(res1024res-1));
	else
		combo->SetIndex(0);
	SetOtherCombos();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void TwoDPref::OnTextChangedCboMapscreen(LPCTSTR Caption, short index) 
{
	currmapres=index+res1024res-1;
	if (index==0)
		Save_Data.ui_horizontalres[SaveData::UIR_MAP]=0;
	else
		Save_Data.ui_horizontalres[SaveData::UIR_MAP]=possiblemapreses[currmapres].horres;
	if (GETDLGITEM(IDC_CBO_MAPEVENTS)->GetIndex()==0)
		Save_Data.ui_horizontalres[SaveData::UIR_FRAG]=Save_Data.ui_horizontalres[SaveData::UIR_MAP];
	SetOtherCombos();
}

void TwoDPref::OnTextChangedCboColourdepth(LPCTSTR Caption, short index) 
{
	int availcolours=possiblemapreses[res1024res].canbitsminus8;
	if (currmapres)
		availcolours&=possiblemapreses[currmapres].canbitsminus8;
	else
		availcolours&=possiblemapreses[currdefaultres].canbitsminus8;

	if (index==0)
		Save_Data.ui_colourdepth=0;
	else
	for (int i=8,b=1,outind=1;i<=32;i++,b+=b)
		if (availcolours&b)
		{
			outind++;
			if (outind==index)
				Save_Data.ui_colourdepth=i;
		}
}

void TwoDPref::OnTextChangedCboMapevents(LPCTSTR Caption, short index) 
{
	// TODO: Add your control notification handler code here
	fragis1024=index;
	if (index==0)
		Save_Data.ui_horizontalres[SaveData::UIR_FRAG]=Save_Data.ui_horizontalres[SaveData::UIR_MAP];
	else
		Save_Data.ui_horizontalres[SaveData::UIR_FRAG]=1024;
}

void TwoDPref::OnTextChangedCboIntroart(LPCTSTR Caption, short index) 
{
	// TODO: Add your control notification handler code here
	if (index==0)
		Save_Data.ui_horizontalres[SaveData::UIR_SMACKER]=0;
	elseif (index==1)
		Save_Data.ui_horizontalres[SaveData::UIR_SMACKER]=possiblemapreses[lowestres].horres;
	else
		Save_Data.ui_horizontalres[SaveData::UIR_SMACKER]=1024;
}
void TwoDPref::OnTextChangedCboOptions(LPCTSTR Caption, short index) 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	if (index==0)
		Save_Data.ui_horizontalres[SaveData::UIR_SCRAMBLE]=0;
	else
		Save_Data.ui_horizontalres[SaveData::UIR_SCRAMBLE]=1024;
	
}

static	int abe[]=
		{
			ABE_BOTTOM,	//  Bottom edge.  
			ABE_LEFT,	//  Left edge.  
			ABE_RIGHT,	//  Right edge.  
			ABE_TOP,	//  Top edge.  
		};
void	SaveDataLoad::ChangeMode(ResUI modepoint)
{
    static currmode=UIR_MAX;
	if (ui_horizontalres[UIR_FIRST]==0)
	{
//DeadCode JIM 18Oct00 		if (modepoint==UIR_FIRST)
//DeadCode JIM 18Oct00 			return;
		DEVMODE	devmode;
		devmode.dmSize=sizeof(DEVMODE);
		devmode.dmDriverExtra=0;
		devmode.dmFields=0x1c0000;
		EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&devmode);
		if (devmode.dmPelsWidth<512 || devmode.dmPelsWidth>8200 || devmode.dmBitsPerPel>64)
		{
		//	INT3;
			devmode.dmPelsWidth=0;
		}
		ui_horizontalres[UIR_FIRST]=devmode.dmPelsWidth;
//TempCode MS 17Nov100 		if (ui_horizontalres[UIR_FIRST]<1024)
//TempCode MS 17Nov100 		{
//TempCode MS 17Nov100 			ui_horizontalres[UIR_SCRAMBLE]=ui_horizontalres[UIR_MAP]=ui_horizontalres[UIR_FRAG]=1024;
//TempCode MS 17Nov100 		}
		ui_horizontalres[UIR_FIRSTH]=devmode.dmPelsHeight;
		ui_horizontalres[UIR_FIRSTFREQ]=devmode.dmDisplayFrequency;
		ui_horizontalres[UIR_FIRST_DEPTH]=devmode.dmBitsPerPel;
		ui_horizontalres[UIR_FIRST_FLAGS]=devmode.dmDisplayFlags;
		if (devmode.dmBitsPerPel<15)
		{
			if (ui_colourdepth==0)
				ui_colourdepth=-1;
		}
		ui_horizontalres[UIR_APPBARSIDES_ON]=
			ui_horizontalres[UIR_APPBARSIDES_TOP]=
				0;
		for (int i=0,r=1;i<4;i++,r+=r)
		{
			APPBARDATA pabd={sizeof(APPBARDATA)};
			pabd.uEdge=abe[i];
			HWND w=(HWND)SHAppBarMessage(ABM_GETAUTOHIDEBAR, &pabd);
			if (w)
			{
				ui_horizontalres[UIR_APPBARSIDES_ON]+=r;
				pabd.hWnd=w;
				if (SHAppBarMessage(ABM_GETSTATE, &pabd)==ABS_ALWAYSONTOP+ABS_AUTOHIDE)
				{
					ui_horizontalres[UIR_APPBARSIDES_TOP]+=r;
					pabd.lParam=FALSE;
//DeadCode JIM 18Oct00 					SetWindowPos(w,HWND_BOTTOM,0,0,0,0,SWP_NOMOVE+SWP_NOSIZE+SWP_NOREDRAW+SWP_NOACTIVATE);
				}
			}
		}
	}


	if (modepoint!=currmode)
	{
		if (
			modepoint!=UIR_FIRST && 
			modepoint!=UIR_SMACKER && 
			modepoint!=UIR_MAP && 
			ui_horizontalres[modepoint]<1024 && 
			ui_horizontalres[UIR_FIRST]!=0 && 
			ui_horizontalres[UIR_FIRST]<1024
			)
			_Error.ReallyEmitSysErr(
				"Sorry, your current desktop resolution is TOO LOW to continue!\n"
				"This simulation requires at least 1024x768 HICOLOUR (15 bit),\n"
				"and you have disabled the game's mode changes.\n"
				"If you have just changed the option then your edit will have been discarded.\n"
				"In other cases either:\n"
				"     Temporarily change your desktop, and change the in-game option;\n"
				"or   Delete SAVEGAME\\SETTINGS.CFG and do not use -BORDER."
				);

		if (modepoint!=UIR_FIRST || currmode!=UIR_MAX) 
//DeadCode JON 27Oct00 			if (modepoint==UIR_FIRST || ui_horizontalres[currmode]==ui_horizontalres[modepoint])
			if (modepoint==UIR_FIRST || ui_horizontalres[currmode]!=ui_horizontalres[modepoint])
			{
				if ((ui_colourdepth!=-1 && ui_horizontalres[modepoint]==0) || modepoint==UIR_FIRST)
				{	//DM_BITSPERPEL

					DEVMODE	devmode;
					devmode.dmSize=sizeof(DEVMODE);
					devmode.dmDriverExtra=0;
					devmode.dmPelsWidth=ui_horizontalres[UIR_FIRST];
					devmode.dmPelsHeight=ui_horizontalres[UIR_FIRSTH];
					devmode.dmDisplayFrequency=ui_horizontalres[UIR_FIRSTFREQ];
					devmode.dmBitsPerPel=ui_horizontalres[UIR_FIRST_DEPTH];
					devmode.dmDisplayFlags=ui_horizontalres[UIR_FIRST_FLAGS];
					devmode.dmFields=DM_BITSPERPEL+DM_PELSWIDTH+DM_PELSHEIGHT+DM_DISPLAYFLAGS+DM_DISPLAYFREQUENCY;
					if (devmode.dmPelsWidth!=0)
						ChangeDisplaySettings(&devmode,0); // actually changes disp settings
					else
						ChangeDisplaySettings(NULL,0);
					AfxGetMainWnd()->ShowWindow(SW_SHOWMINIMIZED);
					AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);

					if (modepoint==UIR_FIRST)// && currmode!=UIR_FIRST)
					{	//Reset any taskbars I hid at the back
						for (int i=0,r=1;i<4;i++,r+=r)
						{
							APPBARDATA pabd={sizeof(APPBARDATA)};
							pabd.uEdge=abe[i];
							if (	(ui_horizontalres[UIR_APPBARSIDES_ON]&r) 
								&&	(ui_horizontalres[UIR_APPBARSIDES_TOP]&r)
								)
							{
								pabd.hWnd=(HWND)SHAppBarMessage(ABM_GETAUTOHIDEBAR, &pabd); // win9x message bar stuff
								{
									SetWindowPos(pabd.hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE+SWP_NOSIZE+SWP_NOREDRAW+SWP_NOACTIVATE);
								}
							}
						}


					}
				}
				else
				{
					if (!ui_horizontalres[modepoint])
						modepoint=UIR_FIRST;	//cludge if desktop is 8 bit come through here
					DEVMODE	devmode,bestdevmode={0};
					devmode.dmSize=sizeof(DEVMODE);
					devmode.dmDriverExtra=0;
					float oldratio=1000.0;
					for (int count=0;EnumDisplaySettings(NULL,count,&devmode);count++)
						if (devmode.dmPelsWidth==ui_horizontalres[modepoint])
						{
							float	newratio=(4.0/3.0)/(float(devmode.dmPelsWidth)/devmode.dmPelsHeight);
							if (newratio>1.0)
								newratio=1.0/newratio;
							if (oldratio>1.0)
								oldratio=1.0/oldratio;
							if (newratio>oldratio)	//closer to 4:3
							{		//cancel modes found so far and use this mode instead 
								bestdevmode=devmode;
								oldratio=newratio;
							}
						}
					if (ui_colourdepth==-1)
					{
						int	trials[]={15,16,24,32};
						int i;INT3;	//never tested with low colour depth
						for (i=0;i<4;i++)
						{	
							bestdevmode.dmFields=DM_BITSPERPEL+DM_PELSWIDTH+DM_PELSHEIGHT;
							bestdevmode.dmBitsPerPel=trials[i];
							breakif (ChangeDisplaySettings(&bestdevmode,CDS_FULLSCREEN)==DISP_CHANGE_SUCCESSFUL);
						}
						if (i==4)
							_Error.ReallyEmitSysErr("Sorry, your current desktop resolution colur depth is TOO LOW to continue!\nThis application requires at least HICOLOUR (15 bit),\n and your graphics driver will not accept dynamic desktop colour depth changes.");

					}
					else
					{
						if (ui_colourdepth)
						{
							bestdevmode.dmFields=DM_BITSPERPEL+DM_PELSWIDTH+DM_PELSHEIGHT;
							bestdevmode.dmBitsPerPel=ui_colourdepth;
						}
						else
							bestdevmode.dmFields=DM_PELSWIDTH+DM_PELSHEIGHT;
						if (ChangeDisplaySettings(&bestdevmode,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
						{
							bestdevmode.dmFields=DM_PELSWIDTH+DM_PELSHEIGHT;
							ChangeDisplaySettings(&bestdevmode,CDS_FULLSCREEN);
						}
					}
					AfxGetMainWnd()->ShowWindow(SW_SHOWMINIMIZED);
					AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);
				}
			if (modepoint!=UIR_FIRST)
				for (int i=0,r=1;i<4;i++,r+=r)
				{
					APPBARDATA pabd={sizeof(APPBARDATA)};
					pabd.uEdge=abe[i];
					if (	(ui_horizontalres[UIR_APPBARSIDES_ON]&r)	)
					{
						pabd.hWnd=(HWND)SHAppBarMessage(ABM_GETAUTOHIDEBAR, &pabd);;
						SetWindowPos(pabd.hWnd,HWND_BOTTOM,0,0,0,0,SWP_NOMOVE+SWP_NOSIZE+SWP_NOREDRAW+SWP_NOACTIVATE);
			//DEADCODE JIM 05/04/00 				SHAppBarMessage(ABM_WINDOWPOSCHANGED,&pabd);
					}
				}

		}
		currmode=modepoint;

	}

}

