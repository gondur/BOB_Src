//------------------------------------------------------------------------------
//Filename       overlay.h
//System         
//Author         Paul    
//Date           Thu 4 Jun 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	OVERLAY_Included
#define	OVERLAY_Included

#include "landscap.h"

#define	DEFAULT_OVERLAY 0

#ifndef	NDEBUG
#define	MaxNames	128
#else
#define	MaxNames	32
#endif

struct	AcNameTable
{
	SWord	x,y;
	ULong	colour;
	char	text[64];
};

struct ICON;
class MESSAGE_STRUC;
class R3DVERTEX;

#define INFOLINESMAX 3

#ifndef LIB3D_Included
class SVertex;
typedef SVertex Lib3DPoint;
#endif

struct GameSettings;

struct MapScr;

enum Key {	SEL_1,		SEL_2,	SEL_3,	SEL_4,		
			SEL_5,		SEL_6,	SEL_7,	SEL_8,		
			SEL_9,		SEL_0,	SEL_PLUS,
			SEL_MINUS,	SEL_ENTER,	SEL_ESC,
			SEL_UP,		SEL_DN,		SEL_LFT,	
			SEL_RGT,	SEL_PAUSE,	SEL_QUIT,
			SEL_BLANK,	SEL_EOL,
			SEL_NONE};

enum KeyFlags {	KF_NULL=0,
				KF_PAUSEON=1<<4,
				KF_PAUSEOFF=2<<4,
				KF_ACCELON=4<<4,
				KF_ACCELOFF=8<<4,
				KF_SLOWACCEL=1,
				KF_FASTACCEL=12,
				KF_BESTACCEL=15,
				KF_FLAGMASK=KF_PAUSEON+KF_PAUSEOFF+KF_ACCELON+KF_ACCELOFF,
				KF_ACCELFRAMESMASK=~KF_FLAGMASK
			};

struct IconEntry
{
	UWord imageMapNo;
	UWord x,y,w,h;
};

struct FRect
{
	Float top,bottom,left,right;
};

struct MapScr
{
	//these are bit flags
	enum {	SCALE_NULL=0,  			// 	no scaling performed on the grid other
									//	than the x2 when the screen resolution
									//	is over 640x480

			SCALE_GRIDORIGIN=1,		//	grid origin position is scaled so that
									//	it always apears at the same position
									//	regardless of the current screen resolution

			SCALE_GRIDELEMENTS=2,	//	elements of the grid are scaled so that
									//	they always cover the same percentage of the
									//	screen area regardless of the screen resolution

			JUSTIFY_CENTRE_SX=4,	//	center the grid horizontally on the screen

			JUSTIFY_CENTRE_SY=8,	//	centre the grid vertically on the screen

			SCALE_GRIDWH=16,		//	scale the wipe area for the grid as the screen
									//	resolution changes

			SCALE_GRIDOFFSETS=32,

			SCALE_DOUBLEIFGT800=64,

			SCALE_DYNAMICSIZE=128,

			FLAG_MOUSEOVERHI=256
		};

	typedef Key (__cdecl MapScr::*InitRtnPtr) (void);
	typedef MapScr* (__cdecl MapScr::*SelRtnPtr) (UByte&,Key);
	typedef void (__cdecl MapScr::*ExtraRtnPtr) (void);
	typedef Key InitRtn (void);
	typedef MapScr* SelRtn (UByte&,Key);
	typedef void ExtraRtn (void);

	UWord 	gridFlags;		//general flags to specify how the screen is to be
							//displayed
	UWord 	windowLeft,		//screen(X,Y) coordinates of the top left corner of the
			windowTop;		//screen defined in PIXELS640

	UWord 	windowWidth,	//screen(W,H) values for the screen area 
			windowHeight;	//to be wiped defined in PIXELS640

	UWord 	gridXOffset,	//(X,Y) offset from the screen(X,Y) coordinates to
			gridYOffset;	//the grid start position

	ULong 	wipeColour,		//background wipe colour (NO_BACKGROUND_WIPE disables)
			textColour,		//colour for displayed text
			hilightColour;	//hilight colour for displayed text

	UWord 	columnWidth,	//Width & height of a single grid element
			rowHeight;		//

	UByte 	numColumns,		//Number of columns of grid elements
			numRows;		//Number of rows of grid elements

	UWord 	highTimer;		//hilight timer for icon based screens. 0==do nothing
							//x=remove hilight from selected option after 'x' frames

	InitRtnPtr initRtn;		//ptr to screen initialisation routine

	ExtraRtnPtr extraRtn;	//ptr to routine called at the end of each draw cycle

	struct OptionList
	{
		UWord resID;
		UByte resIDOffset;
		UByte key;
		SelRtnPtr selRtn;
	}
	optionList[32];

	InitRtn FirstMapInit,
			AccelMapInit,
			WaypointMapInit,
			RadioMapInit,
			CommsMsgMapInit,
			CommsRecipientMapInit,
			CommsMsgOrdersInit,
			CommsRecipientOrdersInit,
			ReplayScreenInit,
			CommsDialogInit,
			Orders3DInit,
			CommsTextInit,
			UserMsgInit,
			UserOptionsInit,
			MapViewScreenInit,
			ContinueQuitInit,											//JON 31Oct00
			UserOptsMapInit;

	SelRtn 	SelectFromFirstMap,
			SelectFromAccelMap,
			SelectFromWaypointMap,
			SelectFromRadioMap,
//DeadCode JON 17Oct00 			SelectFromCommsMsgMap,
//DeadCode JON 17Oct00 			SelectFromCommsRecipientMap,
			SelectFromCommsMsgOrders,
			SelectFromCommsRecipientOrders,
			SelectFromReplayScreen,
			SelectFromCommsDialog,
			
			SelectCommsChat,
			SelectFrom3DOrders,
			SelectFromUserMsg,
			SelectFromUserOptions,
			SelectFromMapViewScreen,
			SelectFromContinueQuit,										//JON 31Oct00
			SelectFromUserOptsMap;

	ExtraRtn	UpdateMessageDisplay,
				UpdateWaypointDisplay,
				HandleUpDnLftRgtToggleKeys,
				ShowPositionIndicators,
				CommsTextUpdateDisplay,
				TimeLimitedDisplay,
//				ShowItemIcons,
				DisplayTargName;

	void	ShowItemIcons(bool);
	void	ShowItemIconsZoomed(bool);

//DeadCode JON 8Nov00 	void	ShowBackgroundMap(COORDS3D&,SWord*,SWord*);
//DeadCode JON 8Nov00 	void	ShowWaypointIcon(SWord,SWord,WayPointPtr);
//DeadCode JON 8Nov00 	void	ShowAircraftRoute(AirStrucPtr,SWord *,SWord *,bool);
//DeadCode JON 29Oct00 	void	ShowAircraftIcon(SWord,SWord,AirStrucPtr);
//DeadCode JON 29Oct00 	void	ShowAircraftIcons(SWord *,SWord *,bool);
//DeadCode JON 29Oct00 	void	ShowTargetLocation(itemptr,SWord *,SWord *);
//DeadCode JON 29Oct00 	void	ShowTargetIcon(SWord,SWord,itemptr);

//DeadCode JON 29Oct00 	void	ShowAircraftIconsZoomed(SLong *,SLong *,bool);
//DeadCode JON 8Nov00 	void	ShowAircraftRouteZoomed(AirStrucPtr,SLong *,SLong *,bool);
};

#define MSBlankLine {0,0xFF,SEL_BLANK,NULL}
#define MSListEnd {0,0xFF,SEL_EOL,NULL}
#define MSEscapeLine(p1) {0,0xFF,SEL_ESC,(p1)}
#define MSAltXLine(p1) {0,0xFF,SEL_QUIT,(p1)}
#define MSPauseLine(p1) {0,0xFF,SEL_PAUSE,(p1)}
class	DecisionAI;
typedef struct 	ImageMap_Desc									//PD 01Aug96
				ImageMapDesc,									//PD 01Aug96
				*ImageMapDescPtr;								//PD 01Aug96
//struct	DoPointStruc;
class	ViewPoint;
class CString;
//DEADCODE JON 5/22/00 struct R3DVERTEX;
//DEADCODE RDH 5/19/00 typedef R3DVERTEX DoPointStruc;
enum	Colour;
class __declspec(dllimport) CLib3D;

struct	ScreenShot
{
	UByte**	framebuffer;
	int		currframe,maxframe;
	int		minframetime,maxfametime;
	int		angledelta,pixeldelta,currpixeloffset;
	struct	tagBITMAPINFOHEADER*	screenformat;
	int		headersize;
	CON		ScreenShot();														//CSB 17Jul00
	bool	SaveScreenShot(CLib3D* g_lpLib3d);
	bool	SaveVideoStream(CLib3D* g_lpLib3d);
	bool	VideoShot(CLib3D* g_lpLib3d);

};
struct 	ImageMap_Desc;
typedef ImageMap_Desc									//PD 01Aug96
				ImageMapDesc,									//PD 01Aug96
				*ImageMapDescPtr;								//PD 01Aug96

class COverlay
{
private:
	int		lastArtHorizOffset;											//JON 13Jun00
	float cheatBoxX;													//JON 4/11/00
	float cheatBoxY;													//JON 4/11/00
	float cheatBoxZ;													//JON 4/11/00
	float cheatBoxScale;												//JON 4/12/00

#ifndef	NDEBUG
	char	diagnosticstring[256];

	float cheatBox2X;													//CSB 14Aug00
	float cheatBox2Y;													//CSB 14Aug00
	float cheatBox2Z;													//CSB 14Aug00
#endif																	//CSB 14Aug00
	bool refreshLandscape;												//JON 9Nov00

public:
	void	SetPossibleLandscapeResfresh(void) { refreshLandscape = true; }	//JON 9Nov00
	void	DoPossibleLandscapeRefresh(void)							//JON 9Nov00
	{
		if ( refreshLandscape )
		{
			refreshLandscape = false;
			Land_Scape.PossibleTeleport();
		}
	}
//JON 9Nov00
#ifndef	NDEBUG
	void	Diagnostic(char*);
#endif
	void CancelAccel();
	void SetupCheatBox( void );											//JON 4/11/00
	volatile	int	accelcountdown;
	SWord	viewee_x,viewtype_x,viewrange_x,viewalt_x,viewbrg_x;
	bool	fTwoLines;

	bool		doInteractiveCockpit;

	AcNameTable	NameTable[MaxNames];
	int			nameTableCnt;

	struct ScrollyText
	{
		enum State 
		{
			WaitingToScroll=0,
			ScrollingToEnd,
			WaitingToScrollBack,
			ScrollingToFront
		};
		enum TimerValues 
		{
			WaitToScrollTime=2*100, // time in milliseconds
			ScrollToEndTime=10*100,
			WaitToScrollBackTime=WaitToScrollTime,
			ScrollToFrontTime=ScrollToEndTime
//DeadCode JON 10Oct00 			WaitToScrollTime=10*100,
//DeadCode JON 10Oct00 			ScrollToEndTime=10*100,
//DeadCode JON 10Oct00 			WaitToScrollBackTime=10*100,
//DeadCode JON 10Oct00 			ScrollToFrontTime=ScrollToEndTime
		};

		SWord timer;
		SWord index;
		SWord targetIndex;
		State state;

		ScrollyText(SWord ti=0):timer(WaitToScrollTime),index(0),state(WaitingToScroll),targetIndex(ti) {}
		SWord CharsToShuffle(SWord ft) 
		{
			if (!targetIndex) return 0;
			SLong toGo;
			toGo=(state==ScrollingToEnd)?targetIndex-index:index;
			if (toGo)
			{
				toGo=toGo*SLong(ft)/SLong(timer);
				if (!toGo) toGo=1;
			}
			else toGo=1;
			return SWord(toGo);
		}
		CString Scroll(CString&,SWord);
	}
	*pScrollyText;

		void Kludge();
	WayPointPtr curr_waypoint;
	AirStrucPtr	message_caller;
	AirStrucPtr	message_callee;
	itemptr		message_target;
	itemptr		target_item;

	int		languagesetbyresources;	//See WINGDI.H //0 or 1 means default, probably English
	int GetTime();
	enum MessageType {PAUSEMESS=0,ACCELMESS,CLEARMESS,SENSMESS,IMPACTONMESS,IMPACTOFFMESS,NOVIEWMESS};
	bool TestMessageText();
	void TriggerMessage(MessageType,UWord val=0);
	bool fZoomedMap;
	SWord messageTimer;
	FileNum loader_art;
	ImageMapDesc* pball;

	CString* msgText;
	CString* otherText;

	CString* blankMsgText;												//JON 24Aug00
	CString* blankOtherText;											//JON 24Aug00

	struct	PBlobStruc
	{
		SWord	sx;
		SWord	sy;
		bool	nat;
	};

	PBlobStruc	pBlob[32];												//RJS 31Jul00
	int			pBlobCnt;												//RJS 31Jul00

//DeadCode RJS 11Oct00 	UByte quit3d;
	void ChopStr(CString&,CString&);
	void MakeDotDotDot(CString&);
	SWord CalcTargIndex(CString&);

	static MapScr 	firstMapScr,
					firstMapScrBomber,
//DeadCode JON 17Oct00 					firstMapScrCOMMS,
					accelMapScr,
					waypointMapScr,
					radioMapScr,
//DeadCode JON 17Oct00 					radioMapScrCOMMS,									//JON 17Oct00
//DeadCode JON 17Oct00 					commsMsgMapScr,
//DeadCode JON 17Oct00 					commsRecipientMapScr,
					continueQuitScr,									//JON 31Oct00
					commsMsgOrdersScr,
					commsRecipientOrdersScr,
					replayScr,
					replayPlayingScr,
					commsDialog,
					orders3dScr,
					userMsgScrCOMMS,
					userMsgScrLead,										//CSB 23/02/00
					userMsgScrLeadBomb,									//CSB 23/02/00
					userMsgScrFoll,										//CSB 23/02/00
					userMsgScrTower,									//CSB 19Sep00
					userOptionsScr,
					mapViewScr,
					userOptsMapScr,
					commsChatDialog;

	MapScr	*pCurScr,*pNewScr;
	Key hilight;
	SWord highTimer;
	UWord commsDialReturn;
	SWord displayTimeLimit;
	char** indirectStringTable;
	CString* targName;
	void DisplayTargName();

	static IconEntry replayIconTable[];
	static IconEntry mapViewIconTable[];
	IconEntry* currIcons;

	void SendMessageAndCall(MESSAGE_STRUC*,DecisionAI*);
	void SetToMapScreen();
	void SetToCommsChatScr();
	void SetToContinueQuitScr();
	void SetToRadioScreen();
	void SetToMapAccelScreen();
	void SetToReplayScreen();
	void SetToMapViewScreen();
	void SetToOrdersScreen();
	void HotKeyTriggerMenu(SWord sel);
	void HotKeyTriggerMessage(SWord sel1,SWord sel2);
	void DecisionMessage(DecisionAI* dec,SWord option,AirStrucPtr caller,ItemBasePtr callee,AirStrucPtr target,Bool sayvox=TRUE);//RJS 09Jun99
	void AccelSelection(UByte hilight,ULong acceltype); //AMM 10/06/99
	UWord DisplayCommsQuitDialog();
	bool SetToUIScreen(MapScr*);
	void ProcessUIScreen();
	void SetGridDimensions(MapScr *);
	void MsgOptionSelected(MESSAGE_STRUC*,SLong);
	void SetTargName(char*);
//DeadCode JON 21Aug00 	void ClippedPutC(R3DVERTEX*,ImageMapDescPtr,FRect&);
	void	PatchFontTable(ImageMapDesc* imap);
	UByte startMarker,endMarker,curPos;

	UByte keyFlags;	//uses kf_ enums

	SWord mouseX,mouseY;
	SWord lastMouseX,lastMouseY;

	bool fIsWide;
	SLong physicalWidth,physicalHeight;
	ViewPoint* pvp;
	CLib3D* g_lpLib3d;
	SWord fontSize;
	char* messageText;
	SLong speed;
	SLong ammocount;
	SLong altitude;
	SLong thrust;
	SLong heading;
	SLong targRange;
	SLong targRelBrg;
	SLong targRelAlt;
	bool hard3D;
	GameSettings* pBackupSettings;

	void DoThreat();
	void DoArtHoriz();
	void DoCheatBox();
	void DrawLine(SWord,SWord,SWord,SWord,Colour);
	void DrawLine(SWord sx,SWord sy,SWord ex,SWord ey,ULong c);
	void DoClippedLine(SWord,SWord,SWord,SWord,Colour,SWord,SWord,SWord,SWord);
	void DrawPeripheralBlobs();

public:
//DEAD	bool isMetric;
	char *shortDistUnitStr,*longDistUnitStr,*heightUnitStr,*speedUnitStr;
	bool fDonePrefs;
	SLong averageFrameRate;
	bool	disableInteractiveMouse;									//RJS 23Aug00

	void DrawWholeScreen();
	void DrawInfoBar();
	void DrawReplayBar();
	void DrawReplayIcons(bool pauseFlag=false);
	void RenderIcon(ICON&,bool clicked=false);
	//SWord ReplayIconHitTest(SWord,SWord);
	void PutC(SWord&,SWord&,unsigned char);
	void PutC2(SWord&,SWord&,unsigned char);							//RJS 22Aug00
	void PrintIcon(SLong,SLong,SLong,SLong,UWord);
	void PrintAt(SWord&,SWord&,const char*,const ULong& theCol=0x00FFFFFF);	//RJS 20Apr00
	void PrintAt2(SWord&,SWord&,const char*,bool noWrap=false);
	void DrawTopText();
	void DrawMessageText();
	void DrawViewText();
	void PreFormatViewText();
	void SetFontSize(SWord fs) {fontSize=fs;}
	void DrawMapPad();
	void InitInfoTexts();
	void ReleaseInfoTexts();
	char* LdStr(SLong);
//DeadCode JON 10Oct00 	SLong StrPixelLen(char*);
//DeadCode JON 10Oct00 	SLong StrPixelLen2(char*);

	void InitMousePos();
	bool UpdateMousePos();
	void DisplayMouseCursor();

	char	hitlinestr[256];
	void	HitLine(Float,Float,Float,Float,Float,Float);

	void	AddPeripheralBlob(const float, const float, bool);
	void	FindLanguage();												//RJS 7Dec00


public:
	COverlay() 
	{	msgText=NULL;
		otherText=NULL;
//DeadCode RJS 11Oct00 		quit3d=0;
		averageFrameRate=0;
		fontSize=16;
		messageText=NULL;
		pvp=NULL;
		g_lpLib3d=NULL;
		hard3D=false;
		pCurScr=pNewScr=NULL;
		pball=NULL;
		messageTimer=0;
		fZoomedMap=false;
		pScrollyText=NULL;
		lastArtHorizOffset=0x7fffffff;
//		loader_art=FIL_LOADERART_800;
		disableInteractiveMouse = false;
		refreshLandscape = false;

#ifndef	NDEBUG
		diagnosticstring[0]=0;
#endif
	};
	~COverlay() 
	{
//#define TESTANDDEL( arg ) if ( arg != NULL ) { delete arg; arg = NULL; }
//		TESTANDDEL( msgText )
//		TESTANDDEL( otherText )
//		TESTANDDEL( messageText )
		if (pball)
			delete[](UByte*)pball;
		pball=NULL;
		if (pScrollyText)
			delete pScrollyText;
		pScrollyText=NULL;
	};
	void SetViewpoint(ViewPoint* vp)									//RJS 23Aug00
	{																	//RJS 23Aug00
		pvp=vp;															//RJS 23Aug00
		nameTableCnt = 0;												//RJS 23Aug00
		pBlobCnt = 0;													//RJS 23Aug00
	}
	void SetScreen(CLib3D *lib3d) {g_lpLib3d=lib3d;}
	void SetInfoLines(SWord l);
	void RenderInfoPanel();
	void StepInfoBarUp();
	void SetMessageText(char* msg) {messageText=msg;}
	void SetInfoLineVals(SLong s,SLong m,SLong a, SLong h,SLong t);
	void RenderMapPad();										//RJS 11Sep98
	void DisplayProfileData(bool );
//DeadCode JON 29Oct00 	void InitPrefs3D();
//DeadCode JON 29Oct00 	void Prefs3D();
//DeadCode JON 29Oct00 	void UpdateSelections();
//DeadCode JON 29Oct00 	void UpdateSelections2();
	void SetViewVals(SLong rng,SLong relB,SLong relA);
	void LoaderScreen(int );
	void CommsWaitingScreen(int);
	void ActionMessage(MESSAGE_STRUC*);
	void CrossHair();
	void GetSurfaceDimensions(SLong& w,SLong& h);
	void PutC(ImageMapDesc*,const Lib3DPoint*,bool forceReload=false);
//DeadCode JON 21Aug00 	void PutA(ImageMapDesc*,R3DVERTEX*);
	void SmokedGlassBox(SLong x,SLong y,SLong width,SLong height);
	void SmokedGlassBox(const SLong x,const SLong y,const SLong width,const SLong height,const ULong col,ULong alpha);
	void	ShapeCheat(char*);
	void	PrintAt(ItemPtr,CString&,const ULong& theCol=0x00FFFFFF);
	void	PrintAt(Coords3D&,CString&,const ULong& theCol=0x00FFFFFF);
	void	PrintCentered(SWord,SWord,const char*,const ULong& theCol=0x00FFFFFF);
	void	PrintCentered(float&,float&,const char*,const ULong& theCol=0x00FFFFFF);
	SLong	StrPixelWidth(const char*);
	SLong	StrPixelWidthPadded(const char*);
	SLong   CharPixelWidth( const char theChar );						//JON 10Oct00
	void	PrintID(ItemPtr);
	ScreenShot screenshot;
	void	SetUp3DUIMouse();											//AMM 13Jul00
	void	RestoreMouse();												//AMM 13Jul00
	UByte	PreviousMouseState;										//AMM 13Jul00
	bool	MouseSet;													//AMM 13Jul00
	bool	MouseRestore;												//AMM 13Jul00
	void	SetInteractiveMode();										//RJS 23Aug00
	void	DrawPoly(const int,const SWord&,const SWord&,const SWord&,const SWord&,const SWord&,const SWord&,const SWord&,const SWord&);	//RJS 1Sep00
	void	PreLoadImageMaps();											//RJS 25Sep00


};


extern class COverlay OverLay;

#endif
