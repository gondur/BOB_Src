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

//------------------------------------------------------------------------------
//Filename       error.cpp
//System         
//Author         Martin Alderton   
//Date           Fri 6 Oct 1995
//Description    
//------------------------------------------------------------------------------

#include	<stdio.h>
#include	<stdlib.h>
#include	<stdarg.h>
#include	<conio.h>										//pd 01Nov95
#include	<dos.h>										//pd 01Nov95
#include	<windows.h>
#include	"DosDefs.h"
//DeadCode DAW 01Mar96 #include	"Files.g"
#include	"Palette.h"
//DeadCode DAW 15Apr96 #include	"screen.h"
//#include	"wrapper.h"
#include	"myerror.h"
//DeadCode DAW 19Mar96 #include	"getset.h"
#include	"myAngles.H"	

#include	"WorldInc.H"
#include	"World.h"


//DeadCode ARM 17Sep96 #include	"main.h"

//DeadCode JIM 02Jul96 #include	<assert.h>											//ARM 26Jun96

#include	<windows.h>											//ARM 20Jun96
//#include	"winmain.h"

#include	"stub3d.h"
//extern Main 	_Main;
//DeadCode PD 26Oct95 extern Wrapper	_Wrapper;

Error	_Error;

extern		void	TraceChain(int x);
extern		void	TrackMemUse();


//#define	_TOFILE_


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Error
//Author		Paul.   
//Date			Fri 13 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Error::Error()
{
//DeadCode DAW 10Apr96 	#if	DEBUGGING
//DeadCode DAW 10Apr96 		OpenLog();
//DeadCode DAW 10Apr96 	#endif
	exitmsg="";
//DeadCode DAW 19Dec96 	exitmsg="Program exitted normally";							//ARM 17Sep96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Error
//Author		Paul.   
//Date			Fri 13 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Error::~Error()
{
//DeadCode DAW 10Apr96 	#if	DEBUGGING
//DeadCode DAW 10Apr96 		CloseLog();
//DeadCode DAW 10Apr96 	#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	Error::EmitSysErr
//------------------------------------------------------------------------------
//Author	Martin Alderton   
//Date		Friday 6 Oct 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

Error& Error::ExitMode()	
{
	Master_3d.Stop();
	return this _;
}
Error& Error::Say(char *txt, ...)	
{exitmsg=txt;return this _;}
BOOL IsDebuggerPresent(VOID);
int	Hell_Freezes_Over=0;
Error& Error::SayAndQuit(const char *fmt, ...)
{

// This string has to be BIG!!!!!!!
static	char String [2048];												//RJS 8Nov00

//TempCode ARM 10Dec96 	TraceChain(0);
//TempCode ARM 10Dec96 	TrackMemUse();

	va_list	marker;

	va_start(marker, fmt);



//DeadCode AMM 24Aug00 	Master_3d.QuitGame();
									   
  	vsprintf(String, fmt, marker);
	if (exitmsg==NULL)
		exitmsg="Error: Press Retry to debug";

#ifdef	_TOFILE_
	FILE*	fp = fopen("boberr.txt","wt");
	if (fp)
	{
		fprintf(fp,"%s\n",String);
		fclose(fp);
	}
#endif

//TEMP	DestroyWindow ( _Main.hWnd );
#ifndef NDEBUG
#define MODE	MB_RETRYCANCEL+MB_ICONSTOP+MB_APPLMODAL+MB_DEFBUTTON2
#else
#define MODE	MB_OK+MB_ICONSTOP+MB_APPLMODAL
#endif
	if (MessageBox(NULL,String,exitmsg,MODE)
			==IDRETRY)
	{
		INT3;
		if (Hell_Freezes_Over)
			return *this;
	}
//DeadCode RJS 8Nov00 	else
//DeadCode RJS 8Nov00 		FatalExit(-1);
	exitmsg=String;

//TempCode ARM 20Jun96 	fprintf(stdout, "\n");
//TempCode ARM 10Jul96 	assert(FALSE);
	exit(0);
	return	*(Error*)NULL;

}

	#if	DEBUGGING
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		screenswap
//Author		Paul.   
//Date			Fri 20 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//TempCode ARM 05Aug96 void Error::screenswap(Display *screen)							//JIM 12Dec95
//TempCode ARM 05Aug96 {
//TempCode ARM 05Aug96 	screen->ScreenSwap();								//PD 29Nov95
//TempCode ARM 05Aug96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OpenLog
//Author		Paul.   
//Date			Fri 13 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Error::OpenLog()
{
	if((logfile = fopen("main.log","wt"))==NULL)
		EmitSysErr(__FILE__":Can't open log file.");

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WriteToLog
//Author		Paul.   
//Date			Fri 13 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Error::WriteToLog(char *fmt,...)
{
	va_list marker;

	va_start(marker,fmt);

	vfprintf(logfile,fmt,marker);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CloseLog
//Author		Paul.   
//Date			Fri 13 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Error::CloseLog()
{
	fclose(logfile);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KeyTrap
//Author		Paul.   
//Date			Fri 13 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Error::KeyTrap()
{
	char	c;
	if(kbhit())
	{
		c=getch()&0x00FF;
		if(c==' ')
			INT3;
	}
}

	#endif

