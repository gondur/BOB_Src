//DEADCODE PD 03/12/99 //------------------------------------------------------------------------------
//DEADCODE PD 03/12/99 //Filename       WinMain.h
//DEADCODE PD 03/12/99 //System         
//DEADCODE PD 03/12/99 //Author         Andrew McRae
//DEADCODE PD 03/12/99 //Date           Wed 2 Jul 1996
//DEADCODE PD 03/12/99 //Description    
//DEADCODE PD 03/12/99 //------------------------------------------------------------------------------
//DEADCODE PD 03/12/99 #ifndef	main_Included
//DEADCODE PD 03/12/99 #define	main_Included
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 #include	"getset.h"
//DEADCODE PD 03/12/99 #include	"screenxy.h"
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 #define APP_NAME    "MiG Alley"
//DEADCODE PD 03/12/99 #define APP_TITLE   "MIG ALLEY"
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 #define	ID_TIMER	1
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 #define	NOGUID	(LPGUID)-1
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 typedef ULong myDPID;
//DEADCODE PD 03/12/99 typedef ULong* myLPDPID;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 class	Main : public	GetSet
//DEADCODE PD 03/12/99 {
//DEADCODE PD 03/12/99 	public:
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 		void	Main::MainInit(void);
//DEADCODE PD 03/12/99 		void	Main::QuitGame(void );
//DEADCODE PD 03/12/99 		void	Main::RowanMessage();
//DEADCODE PD 03/12/99 		void	Main::DoScreen(Window *);						//JIM 12Dec95
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99  		Bool	Main::InitFileSystem(InitDisplayDef&);
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 		// Windows Params
//DEADCODE PD 03/12/99 		HWND hWnd;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 		// Message Loop Control + task switching bits'n'bobs
//DEADCODE PD 03/12/99 		ScreenRez	prevMode;
//DEADCODE PD 03/12/99 		UINT 		AppActive;
//DEADCODE PD 03/12/99 		Bool 		Minimized;
//DEADCODE PD 03/12/99 		Bool 		GameEnd;
//DEADCODE PD 03/12/99 		Bool 		DDrawInitialised;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 		// Timer Stuff
//DEADCODE PD 03/12/99 		TIMECAPS    tc;
//DEADCODE PD 03/12/99 		UINT        wTimerRes;
//DEADCODE PD 03/12/99 		UINT		uTimerID;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 		// Misc
//DEADCODE PD 03/12/99 		char MyString [256];
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 		// Palette management stuff
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	private:
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	protected:
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 };
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	extern Main _Main;		//For 'EmitSysErr'			//JIM 21Sep95
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 #endif
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 long FAR PASCAL DLLExport WndProc (HWND, UINT, UINT, LONG);
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 VOID MainLoopThread (PVOID pvoid);
//DEADCODE PD 03/12/99 VOID TimerThread (PVOID pvoid);
//DEADCODE PD 03/12/99 void CALLBACK TimeProc (UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 Bool GetCDFile (FileNum, char* Name, ULong Offset);
//DEADCODE PD 03/12/99 void ThreadFunction (void * ptr);
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 //TempCode ARM 09Aug96 // Temporary Debug params
//DEADCODE PD 03/12/99 //TempCode ARM 09Aug96 SLong Count;
//DEADCODE PD 03/12/99 //TempCode ARM 09Aug96 SLong MainLoopCount;
//DEADCODE PD 03/12/99 //TempCode ARM 09Aug96 // Temporary String for Message Boxes
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 // Direct Play Callback Functions
//DEADCODE PD 03/12/99 //TempCode ARM 13Aug96 BOOL FAR PASCAL EnumSP(LPGUID lpSPGuid, LPSTR lpDesc, DWORD dwMajorVersion, DWORD dwMinorVersion, LPVOID lpv);
//DEADCODE PD 03/12/99 //TempCode ARM 13Aug96 BOOL FAR PASCAL EnumSession(LPDPSESSIONDESC lpDPGameDesc, LPVOID lpContext, LPDWORD lpdwTimeOut, DWORD dwFlags);
//DEADCODE PD 03/12/99 //TempCode ARM 13Aug96 BOOL FAR PASCAL EnumPlayer(DPID dpID, LPSTR lpFriendlyName, LPSTR lpFormalName, DWORD dwFlags, LPVOID lpContext);
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 //TempCode ARM 15Aug96 BOOL FAR PASCAL EnumAllPlayers(DPID dpID, LPSTR lpFriendlyName, LPSTR lpFormalName, DWORD dwFlags, LPVOID lpContext)

//DEADCODE RDH 16/11/99 //------------------------------------------------------------------------------
//DEADCODE RDH 16/11/99 //Filename       WinMain.h
//DEADCODE RDH 16/11/99 //System         
//DEADCODE RDH 16/11/99 //Author         Andrew McRae
//DEADCODE RDH 16/11/99 //Date           Wed 2 Jul 1996
//DEADCODE RDH 16/11/99 //Description    
//DEADCODE RDH 16/11/99 //------------------------------------------------------------------------------
//DEADCODE RDH 16/11/99 #ifndef	main_Included
//DEADCODE RDH 16/11/99 #define	main_Included
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 #include	"getset.h"
//DEADCODE RDH 16/11/99 #include	"screenxy.h"
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 #define APP_NAME    "MiG Alley"
//DEADCODE RDH 16/11/99 #define APP_TITLE   "MIG ALLEY"
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 #define	ID_TIMER	1
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 #define	NOGUID	(LPGUID)-1
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 typedef ULong myDPID;
//DEADCODE RDH 16/11/99 typedef ULong* myLPDPID;
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 class	Main : public	GetSet
//DEADCODE RDH 16/11/99 {
//DEADCODE RDH 16/11/99 	public:
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 		void	Main::MainInit(void);
//DEADCODE RDH 16/11/99 		void	Main::QuitGame(void );
//DEADCODE RDH 16/11/99 		void	Main::RowanMessage();
//DEADCODE RDH 16/11/99 		void	Main::DoScreen(Window *);						//JIM 12Dec95
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99  		Bool	Main::InitFileSystem(InitDisplayDef&);
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 		// Windows Params
//DEADCODE RDH 16/11/99 		HWND hWnd;
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 		// Message Loop Control + task switching bits'n'bobs
//DEADCODE RDH 16/11/99 		ScreenRez	prevMode;
//DEADCODE RDH 16/11/99 		UINT 		AppActive;
//DEADCODE RDH 16/11/99 		Bool 		Minimized;
//DEADCODE RDH 16/11/99 		Bool 		GameEnd;
//DEADCODE RDH 16/11/99 		Bool 		DDrawInitialised;
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 		// Timer Stuff
//DEADCODE RDH 16/11/99 		TIMECAPS    tc;
//DEADCODE RDH 16/11/99 		UINT        wTimerRes;
//DEADCODE RDH 16/11/99 		UINT		uTimerID;
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 		// Misc
//DEADCODE RDH 16/11/99 		char MyString [256];
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 		// Palette management stuff
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 	private:
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 	protected:
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 };
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 	extern Main _Main;		//For 'EmitSysErr'			//JIM 21Sep95
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 #endif
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 long FAR PASCAL DLLExport WndProc (HWND, UINT, UINT, LONG);
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 VOID MainLoopThread (PVOID pvoid);
//DEADCODE RDH 16/11/99 VOID TimerThread (PVOID pvoid);
//DEADCODE RDH 16/11/99 void CALLBACK TimeProc (UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 Bool GetCDFile (FileNum, char* Name, ULong Offset);
//DEADCODE RDH 16/11/99 void ThreadFunction (void * ptr);
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 //TempCode ARM 09Aug96 // Temporary Debug params
//DEADCODE RDH 16/11/99 //TempCode ARM 09Aug96 SLong Count;
//DEADCODE RDH 16/11/99 //TempCode ARM 09Aug96 SLong MainLoopCount;
//DEADCODE RDH 16/11/99 //TempCode ARM 09Aug96 // Temporary String for Message Boxes
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 // Direct Play Callback Functions
//DEADCODE RDH 16/11/99 //TempCode ARM 13Aug96 BOOL FAR PASCAL EnumSP(LPGUID lpSPGuid, LPSTR lpDesc, DWORD dwMajorVersion, DWORD dwMinorVersion, LPVOID lpv);
//DEADCODE RDH 16/11/99 //TempCode ARM 13Aug96 BOOL FAR PASCAL EnumSession(LPDPSESSIONDESC lpDPGameDesc, LPVOID lpContext, LPDWORD lpdwTimeOut, DWORD dwFlags);
//DEADCODE RDH 16/11/99 //TempCode ARM 13Aug96 BOOL FAR PASCAL EnumPlayer(DPID dpID, LPSTR lpFriendlyName, LPSTR lpFormalName, DWORD dwFlags, LPVOID lpContext);
//DEADCODE RDH 16/11/99 
//DEADCODE RDH 16/11/99 //TempCode ARM 15Aug96 BOOL FAR PASCAL EnumAllPlayers(DPID dpID, LPSTR lpFriendlyName, LPSTR lpFormalName, DWORD dwFlags, LPVOID lpContext)
//DEADCODE DAW 22/11/99 long FAR PASCAL DLLExport WndProc (HWND, UINT, UINT, LONG);

VOID MainLoopThread (PVOID pvoid);
VOID TimerThread (PVOID pvoid);
void CALLBACK TimeProc (UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

Bool GetCDFile (FileNum, char* Name, ULong Offset);
void ThreadFunction (void * ptr);

//TempCode ARM 09Aug96 // Temporary Debug params
//TempCode ARM 09Aug96 SLong Count;
//TempCode ARM 09Aug96 SLong MainLoopCount;
//TempCode ARM 09Aug96 // Temporary String for Message Boxes

// Direct Play Callback Functions
//TempCode ARM 13Aug96 BOOL FAR PASCAL EnumSP(LPGUID lpSPGuid, LPSTR lpDesc, DWORD dwMajorVersion, DWORD dwMinorVersion, LPVOID lpv);
//TempCode ARM 13Aug96 BOOL FAR PASCAL EnumSession(LPDPSESSIONDESC lpDPGameDesc, LPVOID lpContext, LPDWORD lpdwTimeOut, DWORD dwFlags);
//TempCode ARM 13Aug96 BOOL FAR PASCAL EnumPlayer(DPID dpID, LPSTR lpFriendlyName, LPSTR lpFormalName, DWORD dwFlags, LPVOID lpContext);

//TempCode ARM 15Aug96 BOOL FAR PASCAL EnumAllPlayers(DPID dpID, LPSTR lpFriendlyName, LPSTR lpFormalName, DWORD dwFlags, LPVOID lpContext)


