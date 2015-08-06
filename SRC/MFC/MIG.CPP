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

// MIG.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MIG.h"

#include "MainFrm.h"
#include "MIGDoc.h"
#include "MIGView.h"
#include "rdemptyd.h"
#include	"stub3d.h"
//#include "Targets.h"
//DEADCODE DAW 23/11/99 #include "WaveTabs.h"
//#include "Wave.h"
//#include "Chain.h"
//#include "Filters.h"
//#include "Title.h"
#include "gameset.h"
//TEMPCODE DAW 13/04/00 #include "smack.h"
#include "listbx.h"
#include "monotxt.h"
#include "uiicons.h"
#include "overlay.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef	THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

//extern inline	int	LockExchange(int* loc,int newval=0);
//inline	int	LockExchange(int* loc,int newval=0)
//{
//	int rv;
//	_asm	{	mov		eax,newval
//				mov		ebx,loc
//				xchg	ds:[ebx],eax
//				mov		rv,eax
//			}
//	return	rv;
//}
/////////////////////////////////////////////////////////////////////////////
// CMIGApp

BEGIN_MESSAGE_MAP(CMIGApp, CWinApp)
	//{{AFX_MSG_MAP(CMIGApp)
//DEADCODE DAW 24/11/99 	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
//DEADCODE DAW 24/11/99 	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
//DEADCODE DAW 24/11/99 	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMIGApp construction

CMIGApp::CMIGApp()
{
	resourceInst=NULL;
	oldhelppath=m_pszHelpFilePath;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

GameSettings gameSettings;

class RCommandLineInfo:public CCommandLineInfo
{
public:
	GameSettings m_gameSettings;
	RCommandLineInfo() {};
	~RCommandLineInfo() {}
	void ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast );
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ParseParam
//Author		Paul.   
//Date			Thu 25 Jun 1998
//------------------------------------------------------------------------------
void RCommandLineInfo::ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast )
{	char* dummy;
	if (bFlag)
	{
		if (stricmp(lpszParam,"BORDER")==0)
		{
			//force use of 16 bit textures
			m_gameSettings.m_bBorder=true;
		}

		if (strnicmp(lpszParam, "DIAGS",strlen("DIAGS"))==0  )								//JON 21/03/01
		{
			// write out AI timing diagnostics
			m_gameSettings.m_bDoTimerDiags=true;

			// check to see if we have a size next;
			if ( strlen( lpszParam ) != strlen( "DIAGS" ) )
			{
				// we've got a buffersize
				m_gameSettings.m_dwTimerBufferSize=strtol( lpszParam+strlen("DIAGS"), &dummy, 10 ); 
			} else
			{
				m_gameSettings.m_dwTimerBufferSize=500;
			}
		} else if (strcmpi(lpszParam,"USE16")==0)
		{
			//force use of 16 bit textures
			m_gameSettings.m_bUse16=true;
		}
		else if (strcmpi(lpszParam,"NOMEM")==0)
		{
			//ignore video RAM test results
			m_gameSettings.m_bBypassMemCheck=true;
		}
		else if (strcmpi(lpszParam,"WINDOWED")==0)
			m_gameSettings.m_bFullScreenMode=false;
		else if (strcmpi(lpszParam,"HOST")==0)
		{
			// lobby host
			_DPlay.UIPlayerType=DPlay::PLAYER_HOST;
		}
		else if (strcmpi(lpszParam,"GUEST")==0)
		{
			// lobby guest
			_DPlay.UIPlayerType=DPlay::PLAYER_GUEST;
		}
		else if (*lpszParam=='0')
			Save_Data.minsbetweensavegame=strtol(lpszParam+1,&dummy,10);
		else CCommandLineInfo::ParseParam(lpszParam,bFlag,bLast);
	}
	else CCommandLineInfo::ParseParam(lpszParam,bFlag,bLast);
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CMIGApp object

CMIGApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMIGApp initialization

CFont* (g_AllFonts[MAXFONTS][4])={{NULL}};
CDC g_OffScreenDC;


enum	FontInitListFlags
{
	FI_4VER=		0x40000000,
	FI_BOLDMASK=	0x0000ffff,
	FI_ITAL=		0x00100000,
	FI_UL=			0x00200000,
	FI_STRIKE=		0x00400000
};
enum	Fonts
{
	FO_ARIAL=0,
	FO_FUSIONBOLD,
	FO_INTEL,
	FO_FC_GLAMOUR_BOLD,
	FO_COURIER,
};

const char*	Fontnames[]=
{
	"Arial",
	"Fusion Bold\nFusion\nArial Black\nArial",
	"Intel\nTimes New Roman\nTimes\nArial",
	"FC-Glamour-Bold\nFC-Glamour\nTimes New Roman Bold\nTimes New Roman\nTimes\nArial",
	"Courier New\nCourier\nArial",
};
CString	Fontcstrings[5];

static struct	FontInitList
{
	int		pointsize;
	Fonts  	fontname;
	int		flags;


} Font_Init_List[]=
{
#include "FontList.h"
	{0}
};
int __stdcall EnumFontFamExProc(
  const LOGFONT *lpelfe,    // logical-font data
  const TEXTMETRIC *lpntme,  // physical-font data
  DWORD FontType,           // type of font
  LPARAM lParam             // application-defined data
)
{
	int* rv=(int*)lParam;
	*rv=true;
	return false;
}

int	LoadFontNamesAndGetCharset()
{
	CString loadtest;
	loadtest=RESSTRING(LANGUAGE_fdwCharSet);
	if (loadtest.IsEmpty() || loadtest[0]<'0' || loadtest[0]>'9')
		return DEFAULT_CHARSET;
	int	rv=0;
	for (int c=0;loadtest[c]>='0' && loadtest[c]<='9';c++)
		rv=rv*10+loadtest[c]-'0';
	for (int i=0;i<5;i++)
		Fontnames[i]=Fontcstrings[i]=RESSTRING(FONT1_ARIAL+i);
	return rv;
}
void ReleaseFontNames()
{
	for (int i=0;i<5;i++)
		Fontcstrings[i].Empty();
}
void CreatePointFont(CDC* pdc,int ind, int point,Fonts fontname,int flags,int charset)
{
	//input is 10ths of a point
	//a point is 1/72 inches
	//units are 1/720 inches
	//96 pixels per inch
	//multiply by 96/720=6*16/3*3*5*16=2/15
	char charsetnamebuffer[30];
	const char*	testnames=Fontnames[fontname];
	LOGFONT testset;
	while (testnames)
	{
		const char* nextname=strchr(testnames,'\n');
		testset.lfCharSet=charset;
		testset.lfPitchAndFamily=0;
		strncpy(testset.lfFaceName,testnames,32);
		if (nextname)
			testset.lfFaceName[nextname-testnames]=0;
		int gotit=0;
		EnumFontFamiliesEx(*pdc,&testset,EnumFontFamExProc,(long)&gotit,0);
		if (gotit)
			break;
		testnames=nextname+1;
	};
	Fontnames[fontname]=testnames;
	const char* name=testnames;
	if (testnames)
		name=testset.lfFaceName;
	enum	{POINT2PIXMUL=2,POINT2PIXDIV=15};
	point*=-POINT2PIXMUL;
	int	weight=flags&FI_BOLDMASK;
	int	italics=(flags&FI_ITAL)?TRUE:FALSE;
	int	underline=(flags&FI_UL)?TRUE:FALSE;
	int	strikeout=(flags&FI_STRIKE)?TRUE:FALSE;
	g_AllFonts[ind][0]=new CFont;
	g_AllFonts[ind][0]->CreateFont(point/POINT2PIXDIV,0,	0,0,	weight,	italics,underline,strikeout,
						charset,OUT_DEFAULT_PRECIS,CLIP_CHARACTER_PRECIS,
						DEFAULT_QUALITY,DEFAULT_PITCH,
						name);
	if (flags&FI_4VER)
	{	//Don't use these fonts...
		g_AllFonts[ind][3]=new CFont;
		g_AllFonts[ind][3]->CreateFont(point*2/POINT2PIXDIV,0,	0,0,	weight,	italics,underline,strikeout,
							charset,OUT_DEFAULT_PRECIS,CLIP_CHARACTER_PRECIS,
							DEFAULT_QUALITY,DEFAULT_PITCH,
							name);
		g_AllFonts[ind][1]=new CFont;
		g_AllFonts[ind][1]->CreateFont((point*4)/(3*POINT2PIXDIV),0,	0,0,	weight,	italics,underline,strikeout,
						charset,OUT_DEFAULT_PRECIS,CLIP_CHARACTER_PRECIS,
						DEFAULT_QUALITY,DEFAULT_PITCH,
						name);
		g_AllFonts[ind][2]=new CFont;
		g_AllFonts[ind][2]->CreateFont((point*5)/(3*POINT2PIXDIV),0,	0,0,	weight,	italics,underline,strikeout,
						charset,OUT_DEFAULT_PRECIS,CLIP_CHARACTER_PRECIS,
						DEFAULT_QUALITY,DEFAULT_PITCH,
						name);
	}
}


BOOL CMIGApp::InitInstance()
{

//	AllocConsole();
//DeadCode JIM 20Oct00 	INT		sysnames[]={COLOR_SCROLLBAR,COLOR_3DDKSHADOW};
//DeadCode JIM 20Oct00 	DWORD	sysvals[]={0x0000ff00,0x00ff0000};
//	SetSysColors(2,sysnames,sysvals);

	TRACE0("InitInstance starting...\n");

	if (!RDialog::actscrw)										//RJS 08Sep98
	{	//1st time in read registry...
		HKEY k;
		DWORD type;
		unsigned char buff[10];
		DWORD size=9;
		RegOpenKeyEx( 
				HKEY_CURRENT_USER,
				"Control Panel\\desktop\\WindowMetrics",
				0, KEY_ALL_ACCESS, &k);
		RegQueryValueEx(k,"ScrollWidth",NULL,&type,buff,&size);
		if (type==REG_SZ)
			RDialog::actscrw=atoi((char*)buff)/12;
		else
			RDialog::actscrw=*(int*)buff/12;
		size=9;
		RegQueryValueEx(k,"ScrollHeight",NULL,&type,buff,&size);
		if (type==REG_SZ)
			RDialog::actscrh=atoi((char*)buff)/12;
		else
			RDialog::actscrh=*(int*)buff/12;
		size=9;
		RegQueryValueEx(k,"ScrollWidth",NULL,&type,buff,&size);
		if (type==REG_SZ)
			RDialog::actscrw=atoi((char*)buff)/12;
		else
			RDialog::actscrw=*(int*)buff/12;
		size=9;
//		RegQueryValueEx(k,"BorderWidth",NULL,&type,buff,&size);
//		if (type==REG_SZ)
//			RDialog::borderwidth=atoi((char*)buff)/15;
//		else
//			RDialog::borderwidth=*(int*)buff/15;
//		RDialog::borderwidth=2-RDialog::borderwidth;
		RegCloseKey(k);
		RegOpenKeyEx( 
				HKEY_CURRENT_CONFIG,
				"Display\\Settings",
				0, KEY_ALL_ACCESS, &k);
		size=9;
		RegQueryValueEx(k,"DPILogicalX",NULL,&type,buff,&size);
		if (type==REG_SZ)
			RDialog::fontdpi=atoi((char*)buff);
		else
			RDialog::fontdpi=*(int*)buff;
		RegCloseKey(k);
	}															//RJS 08Sep98


     // one of the first things in the init code
	//Load alternate language resources
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Rowan Software Ltd"));				
	//This is not being used as we still have a settings.mig :(
	//however - I will use this to indicate that the program is running

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMIGDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMIGView));
	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
//DeadCode JIM 10Oct00 	EnableShellOpen();
//DeadCode JIM 10Oct00 	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	//CCommandLineInfo cmdInfo;
	RCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	gameSettings=cmdInfo.m_gameSettings;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
//	Rtestsh1::tmpinst=new Inst3d;
//	if (!Rtestsh1::tmpview)
//	{
//		Rtestsh1::tmpview=new View3d(Rtestsh1::tmpinst,m_pMainWnd->m_hWnd,m_pMainWnd);
//		Rtestsh1::tmpview->MakeInteractive(WinMode::WIN);
//	}

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ModifyStyle(m_pMainWnd->GetStyle(),WS_THICKFRAME); // Bye bye title bar
//	m_pMainWnd->ModifyStyle(m_pMainWnd->GetStyle(),NULL); // Bye bye title bar and edges
	m_pMainWnd->SetMenu(NULL); // Bye bye menu  Status bar removed in MainFrm.cpp
	m_pMainWnd->SetWindowText(RESSTRING(BOB));
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);


	Master_3d.Init(m_hInstance,m_pMainWnd->m_hWnd);
//#ifndef	NDEBUG
//In normal development, we don't want to load this DLL because of the risk of orphan DLLs
//It is too late in MiG Alley for this sort of garbage;
//If you do get a orphan DLL you will have to exit DevStudio   Actually, it has never been a problem!

//Support for multiple languages
	char buffer[fileman::pathnamesize];				//JIM 19Sep00
 	resourceInst = LoadLibrary(File_Man.NameNumberedFile(FIL_LANGRESOURCEDLL,buffer));
	if (resourceInst != NULL)
		AfxSetResourceHandle(resourceInst);
	else
		_Error.ReallyEmitSysErr("Can't find language file:\n%s\n",buffer);

//#endif
	oldhelppath=m_pszHelpFilePath ;
	if (File_Man.existnumberedfile(FIL_LANGRESOURCEHELPTABSANDPANELS))
	{
		m_pszHelpFilePath =  File_Man.NameNumberedFile(FIL_LANGRESOURCEHELPTABSANDPANELS,helpfilepath);
		((CMainFrame*)(m_pMainWnd))->disablehelp=0;
	}
	else
	if (File_Man.existnumberedfile(FIL_LANGRESOURCEHELPPANELS))
	{
		m_pszHelpFilePath =  File_Man.NameNumberedFile(FIL_LANGRESOURCEHELPPANELS,helpfilepath);
		((CMainFrame*)(m_pMainWnd))->disablehelp=1;
	}
	else
	if (File_Man.existnumberedfile(FIL_LANGRESOURCEHELPSEPARATETABS)) 
	{
		m_pszHelpFilePath =  File_Man.NameNumberedFile(FIL_LANGRESOURCEHELPSEPARATETABS,helpfilepath);
		((CMainFrame*)(m_pMainWnd))->disablehelp=2;
	}
	else
	if (File_Man.existnumberedfile(FIL_LANGRESOURCEHELP)) 
	{
		m_pszHelpFilePath =  File_Man.NameNumberedFile(FIL_LANGRESOURCEHELP,helpfilepath);
		((CMainFrame*)(m_pMainWnd))->disablehelp=3;

	}
	CDC* pdc=m_pMainWnd->GetDC();
	g_OffScreenDC.CreateCompatibleDC(pdc);
	g_OffScreenDC.SetMapMode(MM_TEXT);

	int charset=LoadFontNamesAndGetCharset();
	OverLay.languagesetbyresources=charset;
	for (int i=0;Font_Init_List[i].pointsize;i++)
		CreatePointFont(pdc,i,Font_Init_List[i].pointsize,Font_Init_List[i].fontname,Font_Init_List[i].flags,charset);
	ReleaseFontNames();
	IconDescUI::LoadInstances(*pdc,ICON_SET_1);
	m_pMainWnd->ReleaseDC(pdc);
	OverLay.FindLanguage();										//RJS 07Dec00

	((CMainFrame*)(m_pMainWnd))->InitialiseSafe();
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

//	SetSysColors(2,sysnames,sysvals);

	return TRUE;
}

int CMIGApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class

	return CWinApp::ExitInstance();
}
CMIGApp::~CMIGApp()
{

	m_pszHelpFilePath= oldhelppath;
    if (resourceInst != NULL)
        FreeLibrary(resourceInst);
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


/////////////////////////////////////////////////////////////////////////////
// CMIGApp commands

int CMIGApp::Run() 
{	
	TRACE0("MessageLoop starting...\n");
	// TODO: Add your specialized code here and/or call the base class
///	Master_3d.Init(m_hInstance,m_pMainWnd->m_hWnd);
	for (int i=0;i<Master_3d.NUM_EVENTS;i++)
		Master_3d.htable[i]=CreateEvent(0,0,0,0);

	// Culled from CWinApp::Run() and CWinTread::Run()
	// The following bit is called once in CWinApp::Run()
	if (m_pMainWnd == NULL && AfxOleGetUserCtrl())
	{
		// Not launched /Embedding or /Automation, but has no main window!
		TRACE0("Warning: m_pMainWnd is NULL in CWinApp::Run - quitting application.\n");
		AfxPostQuitMessage(0);
	}


	// Add your specialized code here and/or call the base class
	//
	// The following is adapted from CWinThread::Run()
	// OnIdle()			is called when there are no more messages
	// PumpMessage()	is called when there is a windows message
	//						-returns FALSE after WM_QUIT message.
	//
	// I need to add new code for the message pump when in the 3d.
	// At present, I will just cheat.
	//

 	ASSERT_VALID(this);
	// for tracking the idle time state
	BOOL bIdle = TRUE;
	LONG lIdleCount = 0;


	// acquire and dispatch messages until a WM_QUIT message is received.
	for (;;)
	{

		int result;
		ULong t;;
		if (Inst3d::InThe3D()||!bIdle)
		{
//DeadCode JIM 9Nov00 			Mono_Text.Print(UByteP("i"));
			result=MsgWaitForMultipleObjects(Mast3d::NUM_EVENTS,Master_3d.htable,FALSE,INFINITE,QS_ALLINPUT);//wait - forever!
		}
		else
		{
//DeadCode JIM 9Nov00 			Mono_Text.Print(UByteP("z"));
			result=MsgWaitForMultipleObjects(Mast3d::NUM_EVENTS,Master_3d.htable,FALSE,0,QS_ALLINPUT);//don't wait - ever!
		}
//DEADCODE JIM 21/06/00 		if (result<WAIT_OBJECT_0+Mast3d::NUM_EVENTS)
//DEADCODE JIM 21/06/00 			Mono_Text.Print(result,(UByteP)"Wait object");
		switch (result)
		{
		case WAIT_OBJECT_0+Mast3d::EVENT_KEYS:
			Inst3d::OnKeyInput();

			break;
		case WAIT_OBJECT_0+Mast3d::EVENT_MOUSE:
			break;

		case WAIT_OBJECT_0+Mast3d::EVENT_AGGREGATOR:
//DeadCode AMM 28Oct98 			if (_DPlay.Host)
//DeadCode AMM 28Oct98 			{
//DeadCode AMM 28Oct98 				if (_DPlay.Implemented)
//DeadCode AMM 28Oct98 				{
//DeadCode AMM 28Oct98 					t=1000000;
//DeadCode AMM 28Oct98 					TRACE0("want message lock\n");
//DeadCode AMM 28Oct98 					while (LockExchange(&Aggregator::inaggregator,1))
//DeadCode AMM 28Oct98 					{
//DeadCode AMM 28Oct98 						Sleep(0);
//DeadCode AMM 28Oct98 						if (!t--)
//DeadCode AMM 28Oct98 							_Error.SayAndQuit("run loop exceeds 1000000");
//DeadCode AMM 28Oct98 					};
//DeadCode AMM 28Oct98 					TRACE0("got lock for message\n");
//DeadCode AMM 28Oct98 					_Agg.AggregatorGetPackets(FALSE,FALSE);
//DeadCode AMM 28Oct98 					LockExchange(&Aggregator::inaggregator,0);
//DeadCode AMM 28Oct98 					TRACE0("released lock for message\n");
//DeadCode AMM 28Oct98 				}
//DeadCode AMM 28Oct98 			}
//DeadCode AMM 28Oct98 			else
//DeadCode AMM 28Oct98 				_Error.SayAndQuit("Player receiving aggregator interrupt!!!!");
//DeadCode AMM 28Oct98 
			break;

		case WAIT_OBJECT_0+Mast3d::NUM_EVENTS:
			while (::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE))
			{
//DEADCODE JIM 21/06/00 				Mono_Text.Print(m_msgCur.message,(UByteP)"Message");
				bool fIn3d=Inst3d::InThe3D();
				if ((Rtestsh1::tempblockkeys || fIn3d) && m_msgCur.message>=WM_KEYFIRST &&  m_msgCur.message<=WM_KEYLAST)
				{
					while (::PeekMessage(&m_msgCur, NULL, WM_KEYFIRST, WM_KEYLAST,PM_REMOVE))
					{}
				}
				else
				{
					//The section below is a debug
//DeadCode JIM 19Oct00 					if (m_msgCur.message!=0x000f && m_msgCur.message!=0x0113)
//DeadCode JIM 19Oct00 					{	//messages received:						  //RDH 12/07/99
//DeadCode JIM 19Oct00  						int msgval=short(m_msgCur.hwnd)*0x10000+short(m_msgCur.message);
//DeadCode JIM 19Oct00  						static int col=0;
//DeadCode JIM 19Oct00  						Mono_Text.PrintHexAt(col,0,msgval,8);
//DeadCode JIM 19Oct00  						col+=10;if (col>80*25) col-=80*25;
//DeadCode JIM 19Oct00  						Mono_Text.PrintHexAt(col,0,0,8);
//DeadCode JIM 19Oct00  				}
					//the section above is a debug

					if (!PumpMessage())
					{
						TRACE0("MessageLoop exitting...\n");
						return ExitInstance();
					}
				}
			}
			if (IsIdleMessage(&m_msgCur))
			{
				lIdleCount = 0;
			}
			bIdle = TRUE;
			break;
		default:
			RDialog::m_moving=false;
//			TRACE0("0");
////			*(char*)0xb0A00+=1;
			if (!OnIdle(lIdleCount++))
			{
//DeadCode JIM 9Nov00 			Mono_Text.Print(UByteP("F"));
				bIdle = FALSE; // assume "no idle" state
			}
			else
				NOP;
		}
	}

	ASSERT(FALSE);  // not reachable
}




BOOL CMIGApp::OnIdle(LONG lCount) 
{
	// TODO: Add your specialized code here and/or call the base class
//DeadCode JIM 9Nov00 			Mono_Text.Prin(lCount,UByteP("I"));
	if (CWinApp::OnIdle(lCount))
		return TRUE;		//Do all system processing 'first'
    if (RDialog::m_pView->m_currentpage==0)
		if (RDialog::m_pView->m_mapdlg.InvalidateAnotherItem())
			return TRUE;
		else
			return FALSE;
	else
		return FALSE;

}
