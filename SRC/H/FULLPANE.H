/*
//{{AFX_INCLUDES()

//}}AFX_INCLUDES
*/
#if !defined(AFX_FULLPANE_H__F4F91440_EF0E_11D1_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_FULLPANE_H__F4F91440_EF0E_11D1_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FullPane.h : header file
//
#include "fileman.h"
class RFullPanelDial;
struct	FullScreen;
typedef Bool (RFullPanelDial::*Proc)();
typedef Bool (RFullPanelDial::*SelProc)(FullScreen*&fs);
// Jims full screen panel structure...
struct FullScreen
{
	struct Resolutions
	{
		FileNum artwork; // a resource ID for now until we convert
		enum {DIAL0=0,SMACK,DIAL2};
		struct Dial
		{
			int X;
			int Y;
			enum {X1=0,CENTRE,X2} flags; //default topleft,x1
			FileNum PanelArt;
		} dials[3];
		
		int ListX,ListY;
	} resolutions [6];
	enum Align
	{	
		LEFT=0,RIGHT,CENTRE,ONSPACE,
		VERT=0,HORIZ=4,
		TOP=0,BOT=8,MID=16
	} listalign;
	struct ListSpec
	{
		UINT text;
		FullScreen* nextscreen;
		SelProc onselect;
	} textlists[10];
	typedef	Resolutions::Dial	Dial;
	Proc	InitProc;
	SelProc	OkProc,
			CancelProc;
};

inline FullScreen::Align operator | 
(FullScreen::Align a,FullScreen::Align b)
{return FullScreen::Align(int(a)|int(b));}
inline FullScreen::Align operator + 
(FullScreen::Align a,FullScreen::Align b)
{return (a|b);}

class	SquadronBase;													//RJS 4Sep00
enum	SquadNum;														//RJS 4Sep00
/////////////////////////////////////////////////////////////////////////////
// RFullPanelDial dialog
class	RFullPanelDial;
typedef	bool	(RFullPanelDial::*InterSheetProcZ)(RDialog*,int);
class RFullPanelDial : public RowanDialog
{
// Construction
	bool	enablepanelselfdrawstate;
	int		currDiaryEntry;												//RJS 4Sep00
	SquadronBase*	sqdetails[2];										//RJS 4Sep00
	SquadNum sq;														//RJS 4Sep00

public:
	static	bool	incomms,in3d,specialevent;
	enum	GameStates	{TITLE,QUICK,HOT,MATCH, PILOT, COMMANDER, DIARY};
//DEADCODE RDH 06/04/00 		CAMP,WAR,MATCH, PILOT, COMMANDER, DIARY};
		
	static	GameStates	gamestate;
	enum	GameSide	{SIDE_RAF, SIDE_LW};
	static	GameSide	gameside;
	RFullPanelDial(CWnd* pParent = NULL);   // standard constructor
	RFullPanelDial::~RFullPanelDial();
	FullScreen* m_pStartScreen;	
	void PositionRListBox();
	CRect GetDialPosition(RDialog* dial, UINT dialID);
	void UpdateSize();
	void LaunchScreen(FullScreen* pfullscreen);
	int GetCurrentRes();
	void LaunchSmacker(int dialID,FileNum smackerID);
	void ChangeSmacker(int dialID,FileNum aviID);
	void LaunchDial(RDialog* dial, UINT dialID,FileNum art=FIL_NULL);
	void LaunchDial(UINT dialID,RDialog* dial)
		{LaunchDial(dial,dialID);}
	void LaunchDial(UINT dialID,const DialBox* dial);
	void LaunchMain(FullScreen* startscreen);
	static int resolutions[6];
	void	ScaleHitAreas(int xres=1024);
	UINT m_timerID;
	FullScreen* m_currentscreen;
	RDialog* pdial[3];
	int m_currentres;

	static void	SetTitleText(bool clear=false);
	Bool Launch3d(FullScreen*&fs);
	Bool LaunchMap(FullScreen*&fs, bool firsttime);
	InterSheetProcZ	localnote;
	void ChildDialClosed(int,RDialog*,int);
	CString selectedfile;
	FileNum	pleasestartthissmacker;

// *********** sheet declarations go here:


	static FullScreen 
		demotitle,
		quickmissionflight,
		introsmack,
		endwarreview,
		Blank,
		title,
		replayload,
		replaysave,
		singleplayer,
		gametype,
		campaignselect,
		campaignentername,
		quickmission,
		bobfrag,
		quickmissiondebrief,
		quickmissiondebriefgrnd,
		options3d,
		gameoptions,
		missionoptions,												  //RDH 22/10/99
		options3d2,
		vieweroptions,
		soundoptions,
		twodoptions,
		controloptions,
		multiplayer,
		flightoptions,
		selectservice,
		selectsession,
		visitorsbook,
		singlefrag,
		commsfrag,
		radio,
		campstart,
		commsquick,
		campover,
		enddayreview,													//RDH 14/03/00
		lastdayreview,
		credits,
//DEADCODE RDH 27/01/00 		variants,
		mapspecials,
//DEADCODE RDH 03/04/00 		endcamp,
		deadpilot,
		specialdebrief,												  //RDH 26/06/99
//DEADCODE RDH 03/04/00 		warendcamp,
		addvisitorsbook,
		paintshop,
//		readyroom,
		readyroomhostmatch,
		readyroomguestmatch,
		readyroomhostmatchred,
		readyroomguestmatchred,										  //RDH 25/03/99
		readyroomhostqmission,
		readyroomguestqmission,
		readyroomhostcampaign,
		readyroomguestcampaign,
		readyroomhostqmissionred,
		readyroomguestqmissionred,
		readyroomhostcampaignred,
		readyroomguestcampaignred,
		quickview,
		loadgame,
		loadcommsgame;

// *********** method declarations go here:
	int	whichcamp;
	void	ChangeCamp(int campnum);
	void	ChangeReview(int msgnum);
	void	ChangeFamilyAnim();

	bool	OnFlyingClosed(RDialog*,int);
	Bool RFullPanelDial::QuickMissionBlue();
	Bool RFullPanelDial::QuickMissionRed();
	Bool RFullPanelDial::QuickMissionDesc();
	Bool RFullPanelDial::QuickMissionParameters();


	Bool RFullPanelDial::PaintShopDesc();



	Bool IntroSmackInit();
	Bool IntroSmackInitForCredits();								  //DAW 30/03/99
	Bool TitleInit();
	Bool Options3dInit();
	Bool GameOptionsInit();
	Bool MissionOptionsInit();										  //RDH 22/10/99
	Bool Options3d2Init();
	Bool ViewerOptionsInit();
	Bool SoundOptionsInit();
	Bool TwoDOptionsInit();

	Bool FlightOptionsInit();
	Bool ControlOptionsInit();
	Bool QuickMissionInit();
	Bool BoBFragInit();


	Bool QuickViewInit();
	Bool	SinglePlayerInit();
	Bool	GameTypeInit();


	Bool QuickMissionDebriefInit();
	Bool QuickMissionDebriefGrndInit();
	Bool CampaignSelectInit();
	Bool EndDayReviewInit();
	Bool EndWarInit();
	Bool CampaignOverInit();
	Bool CampaignStartInit();
	Bool ReplayLoadInit();
	Bool ReplaySaveInit();
	Bool LockerRoomInit();
	Bool SelectServiceInit();
	Bool SetUpLoadGame();

	Bool SelectSessionInit();
	Bool VisitorsBookInit();
	Bool FragInit();
	Bool RadioInit();
	Bool PaintShopInit();
	Bool ReadyRoomInit();
	Bool	MapSpecialsInit();
//DEADCODE RDH 03/04/00 	Bool	EndCampInit();
	Bool	DeadPilotInit();
//DEADCODE RJS 3/21/00 	Bool	SpecialsInit();


	Bool StartFlying();
	bool LoadCampaignData();
//DeadCode AMM 21Aug00 	static void SetDefaultPilotPositions();
	bool DuplicateCommsPlayer(int pos, int player, int squadnum);


	bool CommsPlayer(int pos, int& i, int squadnum);

	Bool VariantsInit();
	Bool	CampaignEnterNameInit();

	Bool	StartCampSmacker();
	Bool	StartCampBackground();
	Bool	StartCampObjectives();
	Bool	CheckForDemo(FullScreen*&fs);
	Bool	DoLoadGame(FullScreen*&fs);
	Bool	DoLoadCommsGame(FullScreen*&fs);
	Bool ConfirmExit(FullScreen*&fs);
	Bool QuitFlying(FullScreen*&fs);
	Bool LaunchMapFirstTime(FullScreen*&fs);
	Bool LoadCampaign(FullScreen*&fs);
	Bool SetUpRafLoadGame(FullScreen*&fs);
	Bool SetUpLWLoadGame(FullScreen*&fs);
	Bool ReplayLoad(FullScreen*&fs);
	Bool ReplaySave(FullScreen*&fs);
	Bool ReplayView(FullScreen*&fs);
	Bool StartComms(FullScreen*&fs);
	Bool GetSessions(FullScreen*&fs);
	Bool CreateCommsGame(FullScreen*&fs);
	Bool JoinCommsGame(FullScreen*&fs);
//	Bool VisitorsBook(FullScreen*&fs);
	Bool CreatePlayer(FullScreen*&fs);
	Bool SelectReadyRoom(FullScreen*&fs);
	static	Bool SelectReadyRoomStatic(FullScreen*&fs);
	Bool SelectReadyRoomFromRadio(FullScreen*&fs);
	Bool ResetMessages(FullScreen*&fs);
	Bool SelectRRVariants(FullScreen*&fs);									//AMM 27Jun99

//DeadCode AMM 06Aug98 	Bool RefreshSessions();
	Bool CommsSelectFly(FullScreen*&fs);
	Bool InitReplay(FullScreen*&fs);
	Bool CleanUpComms(FullScreen*&fs);
	Bool	AllowExitFromComms(FullScreen*&fs);
	Bool	StartCampSmacker(FullScreen*&fs);
	Bool	FragFly(FullScreen*&fs);
	Bool	ReturnToMap(FullScreen*&fs);
	Bool	FragBackupOptions(FullScreen*&fs);
	Bool	FragFly2(FullScreen*&fs);									//AMM 10Jul00
	Bool	ReturnToMapAfterReview(FullScreen*&fs);
	Bool	RFullPanelDial::ExitLastDay(FullScreen*&fs);
	Bool	Pseudo3D(FullScreen*&fs);
	Bool	StartCampBackground(FullScreen*&fs);
	Bool	StartCampObjectives(FullScreen*&fs);
	Bool	StartCampBackground2(FullScreen*&fs);
	Bool	StartCampObjectives2(FullScreen*&fs);
	Bool	SetUpHotShot(FullScreen*&fs);
	Bool	SetQuickState(FullScreen*&fs);
//DEADCODE RDH 26/10/99 	Bool	SetCampState(FullScreen*&fs);
//DEADCODE RDH 26/10/99 	Bool	SetUpFullWar(FullScreen*&fs);
	Bool	SetUpLW(FullScreen*&fs);
	Bool	SetUpRAF(FullScreen*&fs);
	Bool	SetUpCommander(FullScreen*&fs);
	Bool	SetUpPilot(FullScreen*&fs);


	Bool	IfCommsToReadyRoom(FullScreen*&fs);
	Bool	ContinueAfterSpecialDebrief(FullScreen*&fs);			  //RDH 26/06/99

	Bool	PreferencesExitPath(FullScreen*&fs);
	Bool	LaunchMapIfAlive(FullScreen*&fs);
	Bool	StartNextCampaign(FullScreen*&fs);
	Bool	ContinueAlthoughDead(FullScreen*&fs);
	Bool	ReloadBecauseDead(FullScreen*&fs);
	void	ResetLoadGameOption();
	void	ResetQuitOption();
//DeadCode AMM 2Oct00 	static	Bool	PrepareForFrag(FullScreen*&fs);
	void	ResetVariantOption();
	Bool	ExitVariant(FullScreen*&fs);
	Bool 	CheckLobby(FullScreen*&fs);
	Bool	CanGuestJoin(FullScreen*&fs);
	Bool	ReInitCommsInterface(FullScreen*&fs);
	Bool	LobbyCheck(FullScreen*&fs);
	Bool	ReplayLoadBack(FullScreen*&fs);
	Bool	ReplaySaveBack(FullScreen*&fs);
	Bool	DebriefReplayCheck(FullScreen*&fs);
	Bool	JumpToWebSite(FullScreen*&fs);

	Bool	CheckForMissingMission(FullScreen*&);						//RJS 30Jul00

	void	CloseVideo();


	// Dialog Data
	//{{AFX_DATA(RFullPanelDial)
	enum { IDD = IDD_FULLPANE };
		// NOTE: the ClassWizard will add data members here
	CRListBox	m_IDC_RLISTBOX;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RFullPanelDial)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL
//DeadCode RJS 03May100 	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

// Implementation
public:


	// Generated message map functions
	//{{AFX_MSG(RFullPanelDial)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSelectRlistbox(long row, long column);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnPaint();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg CFont* OnGetGlobalFont(int fontnum);
	afx_msg FileNum OnGetArt();
	afx_msg void OnMciNotify(int wp,int lp);
	afx_msg void OnMciDidQuit(int wp,int lp);
	MSG2_0(OnGetArt);
	MSG2_1(OnGetGlobalFont);
	MSG2_2v(OnMciNotify);
	MSG2_2v(OnMciDidQuit);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FULLPANE_H__F4F91440_EF0E_11D1_A1F0_0080C8582DE4__INCLUDED_)

