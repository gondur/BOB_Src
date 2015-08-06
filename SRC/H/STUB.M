//DEADCODE RDH 02/11/99 //;;------------------------------------------------------------------------------
//DEADCODE RDH 02/11/99 //;;Filename       stub.m
//DEADCODE RDH 02/11/99 //;;System         
//DEADCODE RDH 02/11/99 //;;Author         Jim Taylor
//DEADCODE RDH 02/11/99 //;;Date           Mon 9 Oct 1995
//DEADCODE RDH 02/11/99 //;;Description    Stub model for runtime libraries
//DEADCODE RDH 02/11/99 //;;
//DEADCODE RDH 02/11/99 //;;Each procedure to be stubbed has 2 versions in the class.
//DEADCODE RDH 02/11/99 //;;The public version simply stubs to the private version.
//DEADCODE RDH 02/11/99 //;;It also has a STUBLOADABLE() statement to define some extra hooks.
//DEADCODE RDH 02/11/99 //;;
//DEADCODE RDH 02/11/99 //;;The header for the library and the main program contains:
//DEADCODE RDH 02/11/99 //;;	STUBSTART(classname)
//DEADCODE RDH 02/11/99 //;;	followed by the public stubs
//DEADCODE RDH 02/11/99 //;;	STUBREAL(classname)
//DEADCODE RDH 02/11/99 //;;
//DEADCODE RDH 02/11/99 //;;The main program now defines empty versions of the procedures
//DEADCODE RDH 02/11/99 //;;followed by STUB256() statements.
//DEADCODE RDH 02/11/99 //;;The main program area is terminated by a STUBEND() statement
//DEADCODE RDH 02/11/99 //;;
//DEADCODE RDH 02/11/99 //;;The library defines the procedure bodies. This is also terminated by STUBEND()
//DEADCODE RDH 02/11/99 //;;
//DEADCODE RDH 02/11/99 //;;Thus, the library fixup is made up of 3 linked modules: pub, gap and lib
//DEADCODE RDH 02/11/99 //;;
//DEADCODE RDH 02/11/99 //;;The stub loader code requires the address of classname::stubstart()
//DEADCODE RDH 02/11/99 //;;defined by STUBSTART(). It will then overwrite between STUBSTART and STUBEND.
//DEADCODE RDH 02/11/99 //;;Note: This interface will need a going over if we ever allow virtual memory,
//DEADCODE RDH 02/11/99 //;;but the use of a stub should simplify this work.
//DEADCODE RDH 02/11/99 //;;
//DEADCODE RDH 02/11/99 //;;To load the library call	STUBLOAD(classname)
//DEADCODE RDH 02/11/99 //;;
//DEADCODE RDH 02/11/99 //;;------------------------------------------------------------------------------
//DEADCODE RDH 02/11/99 #ifndef	STUB_Included
//DEADCODE RDH 02/11/99 #define	STUB_Included
//DEADCODE RDH 02/11/99 #include	"files.g"
//DEADCODE RDH 02/11/99 //#ifdef LoadLibrary
//DEADCODE RDH 02/11/99 //#undef LoadLibrary
//DEADCODE RDH 02/11/99 //#endif
//DEADCODE RDH 02/11/99 
//DEADCODE RDH 02/11/99 #define	STUBLOADABLE(staticauto) static	void	stubstart();			\
//DEADCODE RDH 02/11/99 				static	char*	stubstart2();			\
//DEADCODE RDH 02/11/99 				static	void	stubend();				\
//DEADCODE RDH 02/11/99 				static	void	stubreal();				\
//DEADCODE RDH 02/11/99 				staticauto	StubLock	stublock;			
//DEADCODE RDH 02/11/99 
//DEADCODE RDH 02/11/99 #ifdef __WATCOMC__ 
//DEADCODE RDH 02/11/99 #pragma aux	STUBINTRO	=	"db	'ROWANLIB'"
//DEADCODE RDH 02/11/99 #pragma	aux	STUBHEADCODE=	"db	'HEADCODE'"
//DEADCODE RDH 02/11/99 #pragma	aux	STUBREALCODE=	"db	'REALCODE'"
//DEADCODE RDH 02/11/99 #pragma aux	STUBEXIT	=	"db	'EXITOVER'"
//DEADCODE RDH 02/11/99 #pragma aux STUBBYTE	=	0
//DEADCODE RDH 02/11/99 #endif
//DEADCODE RDH 02/11/99 #ifdef __MSVC__
//DEADCODE RDH 02/11/99 inline void STUBINTRO()
//DEADCODE RDH 02/11/99 {
//DEADCODE RDH 02/11/99 	__asm _emit 'R' __asm _emit 'O' __asm _emit 'W' __asm _emit 'A' 
//DEADCODE RDH 02/11/99 	__asm _emit 'N' __asm _emit 'L' __asm _emit 'I' __asm _emit 'B' 
//DEADCODE RDH 02/11/99 }
//DEADCODE RDH 02/11/99 inline void STUBHEADCODE()
//DEADCODE RDH 02/11/99 {
//DEADCODE RDH 02/11/99 	__asm _emit 'H' __asm _emit 'E' __asm _emit 'A' __asm _emit 'D' 
//DEADCODE RDH 02/11/99 	__asm _emit 'C' __asm _emit 'O' __asm _emit 'D' __asm _emit 'E' 
//DEADCODE RDH 02/11/99 }
//DEADCODE RDH 02/11/99 inline void STUBREALCODE()
//DEADCODE RDH 02/11/99 {
//DEADCODE RDH 02/11/99 	__asm _emit 'R' __asm _emit 'E' __asm _emit 'A' __asm _emit 'L' 
//DEADCODE RDH 02/11/99 	__asm _emit 'C' __asm _emit 'O' __asm _emit 'D' __asm _emit 'E' 
//DEADCODE RDH 02/11/99 }
//DEADCODE RDH 02/11/99 inline void STUBEXIT()
//DEADCODE RDH 02/11/99 {
//DEADCODE RDH 02/11/99 	__asm _emit 'E' __asm _emit 'X' __asm _emit 'I' __asm _emit 'T' 
//DEADCODE RDH 02/11/99 	__asm _emit 'O' __asm _emit 'V' __asm _emit 'E' __asm _emit 'R' 
//DEADCODE RDH 02/11/99 }
//DEADCODE RDH 02/11/99 inline void STUBBYTE()
//DEADCODE RDH 02/11/99 {
//DEADCODE RDH 02/11/99 	__asm _emit 0
//DEADCODE RDH 02/11/99 }
//DEADCODE RDH 02/11/99 #endif
//DEADCODE RDH 02/11/99 
//DEADCODE RDH 02/11/99 #ifdef	__DOS__
//DEADCODE RDH 02/11/99 #define STUBWORD()		{STUBBYTE();STUBBYTE();}
//DEADCODE RDH 02/11/99 #define STUBLONG()		{STUBWORD();STUBWORD();}
//DEADCODE RDH 02/11/99 #define STUBDBLE()		{STUBLONG();STUBLONG();}
//DEADCODE RDH 02/11/99 #define STUBPARA()		{STUBDBLE();STUBDBLE();}
//DEADCODE RDH 02/11/99 #define STUB32()		{STUBPARA();STUBPARA();}
//DEADCODE RDH 02/11/99 #define STUB64()		{STUB32();STUB32();}
//DEADCODE RDH 02/11/99 #define STUB128()		{STUB64();STUB64();}
//DEADCODE RDH 02/11/99 #define STUB256()		{STUB128();STUB128();}
//DEADCODE RDH 02/11/99 #endif
//DEADCODE RDH 02/11/99 
//DEADCODE RDH 02/11/99 #ifdef	WIN95
//DEADCODE RDH 02/11/99 #define STUBWORD()		
//DEADCODE RDH 02/11/99 #define STUBLONG()		
//DEADCODE RDH 02/11/99 #define STUBDBLE()		
//DEADCODE RDH 02/11/99 #define STUBPARA()		
//DEADCODE RDH 02/11/99 #define STUB32()		
//DEADCODE RDH 02/11/99 #define STUB64()		
//DEADCODE RDH 02/11/99 #define STUB128()		
//DEADCODE RDH 02/11/99 #define STUB256()		
//DEADCODE RDH 02/11/99 #endif
//DEADCODE RDH 02/11/99 
//DEADCODE RDH 02/11/99 //#undef LoadLibrary
//DEADCODE RDH 02/11/99 class	StubLock
//DEADCODE RDH 02/11/99 {
//DEADCODE RDH 02/11/99 public:
//DEADCODE RDH 02/11/99 	ULong	lockstart;
//DEADCODE RDH 02/11/99 	ULong	locksize;
//DEADCODE RDH 02/11/99 	~StubLock();
//DEADCODE RDH 02/11/99 void	ClearLock();
//DEADCODE RDH 02/11/99 string	LoadJimLib(		void*		targetaddr,		//Address of StubStart
//DEADCODE RDH 02/11/99 						string		keyname,		//Text from stubstart2()
//DEADCODE RDH 02/11/99 						FileNum		sourcefile,		//Caller decision
//DEADCODE RDH 02/11/99 						void*		srcaddr=NULL,
//DEADCODE RDH 02/11/99 						int**		jumpobject=NULL		
//DEADCODE RDH 02/11/99 					);
//DEADCODE RDH 02/11/99 //DeadCode JIM 02May97 string	CopyLibHeader(int newaddr,int oldaddr);
//DEADCODE RDH 02/11/99 };
//DEADCODE RDH 02/11/99 
//DEADCODE RDH 02/11/99 #define	STUBSTATIC(classname)							\
//DEADCODE RDH 02/11/99 StubLock	classname::stublock={0,0};
//DEADCODE RDH 02/11/99 
//DEADCODE RDH 02/11/99 #define	STUBSTART(classname)							\
//DEADCODE RDH 02/11/99 														\
//DEADCODE RDH 02/11/99 char*	STUBNAME="ROWANLIB"	__FILE__ __DATE__;	\
//DEADCODE RDH 02/11/99 														\
//DEADCODE RDH 02/11/99 				char*	classname::stubstart2()	\
//DEADCODE RDH 02/11/99 				{										\
//DEADCODE RDH 02/11/99 					return STUBNAME;					\
//DEADCODE RDH 02/11/99 				}										\
//DEADCODE RDH 02/11/99 														\
//DEADCODE RDH 02/11/99 				void	classname::stubstart()	\
//DEADCODE RDH 02/11/99 				{										\
//DEADCODE RDH 02/11/99 					STUBINTRO();						\
//DEADCODE RDH 02/11/99 					STUBHEADCODE();						\
//DEADCODE RDH 02/11/99 					STUBBYTE();							\
//DEADCODE RDH 02/11/99 				}
//DEADCODE RDH 02/11/99 
//DEADCODE RDH 02/11/99 
//DEADCODE RDH 02/11/99 #define	STUBREAL(classname)								\
//DEADCODE RDH 02/11/99 				void	classname::stubreal()	\
//DEADCODE RDH 02/11/99 				{										\
//DEADCODE RDH 02/11/99 					STUBINTRO();						\
//DEADCODE RDH 02/11/99 					STUBREALCODE();						\
//DEADCODE RDH 02/11/99 					STUBBYTE();							\
//DEADCODE RDH 02/11/99 				}
//DEADCODE RDH 02/11/99 
//DEADCODE RDH 02/11/99 #define	STUBEND(classname)								\
//DEADCODE RDH 02/11/99 				void	classname::stubend()	\
//DEADCODE RDH 02/11/99 				{										\
//DEADCODE RDH 02/11/99 					STUBINTRO();						\
//DEADCODE RDH 02/11/99 					STUBEXIT();							\
//DEADCODE RDH 02/11/99 					STUBBYTE();							\
//DEADCODE RDH 02/11/99 				}										\
//DEADCODE RDH 02/11/99 				void	main	(){}					\
//DEADCODE RDH 02/11/99 				void	StubLock::ClearLock()	{}		\
//DEADCODE RDH 02/11/99 				DES		StubLock::~StubLock()	{}				
//DEADCODE RDH 02/11/99 														
//DEADCODE RDH 02/11/99 #define	STUBENDSPACE(classname)							\
//DEADCODE RDH 02/11/99 				void	classname::stubend()	\
//DEADCODE RDH 02/11/99 				{										\
//DEADCODE RDH 02/11/99 					STUBINTRO();						\
//DEADCODE RDH 02/11/99 					STUBEXIT();							\
//DEADCODE RDH 02/11/99 					STUBBYTE();							\
//DEADCODE RDH 02/11/99 				}
//DEADCODE RDH 02/11/99 														
//DEADCODE RDH 02/11/99 
//DEADCODE RDH 02/11/99 
//DEADCODE RDH 02/11/99 #define	STUBLOAD(classname,filenum)											\
//DEADCODE RDH 02/11/99 		classname##stublock.LoadLibrary((void*)classname##stubstart,						\
//DEADCODE RDH 02/11/99 				classname##stubstart2(),									\
//DEADCODE RDH 02/11/99 				filenum);													\
//DEADCODE RDH 02/11/99 				
//DEADCODE RDH 02/11/99 //
//DEADCODE RDH 02/11/99 // END OF FILE!
//DEADCODE RDH 02/11/99 //
//DEADCODE RDH 02/11/99 
//DEADCODE RDH 02/11/99 #endif
//DEADCODE RDH 02/11/99 
//DEADCODE RDH 02/11/99 