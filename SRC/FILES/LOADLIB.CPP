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

//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	//Filename       loadlib.cpp
//deadcode JIM 19/06/01	//System         
//deadcode JIM 19/06/01	//Author         Jim Taylor
//deadcode JIM 19/06/01	//Date           Mon 9 Oct 1995
//deadcode JIM 19/06/01	//Description    Loads a rowan runtime library
//deadcode JIM 19/06/01	//				FC Joystick and graphics card support DLLS!
//deadcode JIM 19/06/01	//The library data starts with the quadword "ROWANLIB"
//deadcode JIM 19/06/01	//We have to find this string in source and destination
//deadcode JIM 19/06/01	//Then comes the filename and date with zero byte separators - they should match
//deadcode JIM 19/06/01	//Then, we copy up to "ROWANLIB" followed by "REALCODE" and date with separators
//deadcode JIM 19/06/01	//These should match in source and destination positions
//deadcode JIM 19/06/01	//Then, we copy until "ROWANLIB" followed by "EXITOVER"
//deadcode JIM 19/06/01	//The "OVER" part of "EXITOVER" should not be copied
//deadcode JIM 19/06/01	//The "ROWANLIB" of the target which has "EXITOVER" after must not be overwritten
//deadcode JIM 19/06/01	//or this means the library is too big!
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	#include	<string.h>
//deadcode JIM 19/06/01	#include	"dosdefs.h"
//deadcode JIM 19/06/01	#include	"files.g"
//deadcode JIM 19/06/01	#include	"fileman.h"
//deadcode JIM 19/06/01	#include	"stub.m"
//deadcode JIM 19/06/01	//#include	"main.h"
//deadcode JIM 19/06/01	#include	"myerror.h"
//deadcode JIM 19/06/01	#include	"hardpasm.h"
//deadcode JIM 19/06/01	#ifdef	WIN95
//deadcode JIM 19/06/01		#include	<windows.h>
//deadcode JIM 19/06/01		#undef LoadLibrary
//deadcode JIM 19/06/01	#else
//deadcode JIM 19/06/01		#include <dos.h>
//deadcode JIM 19/06/01	#endif
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	#ifdef __WATCOMC__
//deadcode JIM 19/06/01	#pragma aux	loadlibflag	= db 'ROWANLIBloadercode'
//deadcode JIM 19/06/01	#else
//deadcode JIM 19/06/01	inline void loadlibflag()
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		__asm _emit 'R' __asm _emit 'O' __asm _emit 'W' __asm _emit 'A' 
//deadcode JIM 19/06/01		__asm _emit 'N' __asm _emit 'L' __asm _emit 'I' __asm _emit 'B' 
//deadcode JIM 19/06/01		__asm _emit 'l' __asm _emit 'o' __asm _emit 'a' __asm _emit 'd' 
//deadcode JIM 19/06/01		__asm _emit 'e' __asm _emit 'r' __asm _emit 'c' __asm _emit 'o' 
//deadcode JIM 19/06/01		__asm _emit 'd' __asm _emit 'e'
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	#endif
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	string	StubLock::LoadJimLib(	void*		targetaddr,		//Address of StubStart
//deadcode JIM 19/06/01									string		keyname,		//Text from stubstart2()
//deadcode JIM 19/06/01									FileNum		sourcefile,		//Caller decision
//deadcode JIM 19/06/01									void*		cmpbase,		//Original fix table
//deadcode JIM 19/06/01									int**		jumpobject		//Current virtual table ptr
//deadcode JIM 19/06/01								)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		if (sourcefile==-2)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			loadlibflag();
//deadcode JIM 19/06/01			return (NULL);
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01		else
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	#ifdef	WIN95
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		{	//Windows is not interested in targetaddr, but does a DLL LOAD
//deadcode JIM 19/06/01			HANDLE	hLibrary=::LoadLibraryA(FILEMAN.namenumberedfile(sourcefile));
//deadcode JIM 19/06/01			locksize=1;
//deadcode JIM 19/06/01			(HANDLE&)lockstart=hLibrary;
//deadcode JIM 19/06/01			typedef char*	(WINAPI *Launcher) (int** object,string stamp);
//deadcode JIM 19/06/01			Launcher l=(Launcher) GetProcAddress(hLibrary,"_DEVICEHOOK@8");
//deadcode JIM 19/06/01			if (l==NULL)
//deadcode JIM 19/06/01				_Error.EmitSysErr("Couldn't get function from dll. File %x",sourcefile);
//deadcode JIM 19/06/01			char* dllret=l(jumpobject,keyname);
//deadcode JIM 19/06/01			if (dllret!=NULL)
//deadcode JIM 19/06/01				_Error.EmitSysErr("Incompatible function from dll. File %x\n%s!=%s?\n",sourcefile,keyname,dllret);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			return (string) targetaddr;
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01	#endif
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	#ifdef __DOS__													//ARM 02Aug96
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01	string	trgptr=(string)	targetaddr;
//deadcode JIM 19/06/01	string	cmpaddr=cmpbase?(string)cmpbase:trgptr;
//deadcode JIM 19/06/01	fileblock	fb(sourcefile);
//deadcode JIM 19/06/01	string	srcptr=(string) getdata(fb);
//deadcode JIM 19/06/01	ULong	fs=getsize(fb);
//deadcode JIM 19/06/01	ULong	llockstart;
//deadcode JIM 19/06/01			//Find "ROWANLIB"
//deadcode JIM 19/06/01			while	(	(	(((ULong*) (srcptr))[0] != *((ULong*) ("ROWA")))
//deadcode JIM 19/06/01				 	 	|| (((ULong*) (srcptr))[1] != *((ULong*) ("NLIB")))
//deadcode JIM 19/06/01						)
//deadcode JIM 19/06/01				 	&& fs--	//this is the only check for file size!
//deadcode JIM 19/06/01					)
//deadcode JIM 19/06/01				srcptr++;
//deadcode JIM 19/06/01			while	(	(((ULong*) (cmpaddr))[0] != *((ULong*) ("ROWA")))
//deadcode JIM 19/06/01				 	|| (((ULong*) (cmpaddr))[1] != *((ULong*) ("NLIB")))
//deadcode JIM 19/06/01					)
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01				cmpaddr++;
//deadcode JIM 19/06/01				trgptr++;
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			if	(lockstart)
//deadcode JIM 19/06/01			{	//unlock existing page
//deadcode JIM 19/06/01				if (lockstart!=(ULong) trgptr)
//deadcode JIM 19/06/01					_Error.EmitSysErr("Target address has moved between calls?");
//deadcode JIM 19/06/01				DPMIregs r;
//deadcode JIM 19/06/01				r.l.eax = 0x0601;							/* DPMI UNlock linear region */
//deadcode JIM 19/06/01				r.l.ebx = ((ULong) lockstart) >> 16;
//deadcode JIM 19/06/01				r.l.ecx = ((ULong) lockstart) & 0xFFFF;
//deadcode JIM 19/06/01				r.l.esi = ((ULong) locksize) >> 16;
//deadcode JIM 19/06/01				r.l.edi = ((ULong) locksize) & 0xFFFF;
//deadcode JIM 19/06/01				ASM_DEXint31(&r);
//deadcode JIM 19/06/01	//DeadCode ARM 04Jun96 			int386 (0x31, &r, &r);
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01	//DeadCode JIM 15Mar96 		else
//deadcode JIM 19/06/01			llockstart=(ULong) trgptr;
//deadcode JIM 19/06/01			srcptr+=8;
//deadcode JIM 19/06/01			cmpaddr+=8;
//deadcode JIM 19/06/01			trgptr+=8;
//deadcode JIM 19/06/01			if 	(	(((ULong*) (srcptr))[0] != *((ULong*) ("HEAD")))
//deadcode JIM 19/06/01			 	||	(((ULong*) (srcptr))[1] != *((ULong*) ("CODE")))
//deadcode JIM 19/06/01				)
//deadcode JIM 19/06/01				_Error.EmitSysErr("Source ROWANLIB file doesn't start HEADCODE. %x %s",
//deadcode JIM 19/06/01					sourcefile,keyname);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			if 	(	(((ULong*) (cmpaddr))[0] != *((ULong*) ("HEAD")))
//deadcode JIM 19/06/01			 	||	(((ULong*) (cmpaddr))[1] != *((ULong*) ("CODE")))
//deadcode JIM 19/06/01				)
//deadcode JIM 19/06/01				_Error.EmitSysErr("Source ROWANLIB file doesn't start HEADCODE. %x %s",
//deadcode JIM 19/06/01					sourcefile,keyname);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			//now pointing past matched header
//deadcode JIM 19/06/01			//copy until "REALCODE" header
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			while	(	(((ULong*) (cmpaddr))[0] != *((ULong*) ("ROWA")))	//comparator header size
//deadcode JIM 19/06/01				 	&&	(((ULong*) (cmpaddr))[1] != *((ULong*) ("NLIB")))
//deadcode JIM 19/06/01					&&	(((ULong*) (trgptr))[0] != *((ULong*) ("ROWA")))	//target run out of space
//deadcode JIM 19/06/01				 	&&	(((ULong*) (trgptr))[1] != *((ULong*) ("NLIB")))
//deadcode JIM 19/06/01					)
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01				*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01				cmpaddr++;
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01			//Check headers match up correctly
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	    	if (	(((ULong*) (cmpaddr))[2] != *((ULong*) ("REAL")))
//deadcode JIM 19/06/01				||	(((ULong*) (cmpaddr))[3] != *((ULong*) ("CODE")))
//deadcode JIM 19/06/01				)
//deadcode JIM 19/06/01				_Error.EmitSysErr("Middle ROWANLIB not REALCODE in target memory");
//deadcode JIM 19/06/01			if (	(((ULong*) (srcptr))[0] != *((ULong*) ("ROWA")))
//deadcode JIM 19/06/01				||	(((ULong*) (srcptr))[1] != *((ULong*) ("NLIB")))
//deadcode JIM 19/06/01				)
//deadcode JIM 19/06/01				_Error.EmitSysErr("Middle ROWANLIB position mismatch - file %x",sourcefile);
//deadcode JIM 19/06/01			if (	(((ULong*) (srcptr))[2] != *((ULong*) ("REAL")))
//deadcode JIM 19/06/01				||	(((ULong*) (srcptr))[3] != *((ULong*) ("CODE")))
//deadcode JIM 19/06/01				)
//deadcode JIM 19/06/01				_Error.EmitSysErr("Middle ROWANLIB not REALCODE in sourcefile %x",sourcefile);
//deadcode JIM 19/06/01	//DeadCode JIM 27Feb96 		if (((ULong*) (srcptr))[4] != ((ULong*) (trgptr))[4])
//deadcode JIM 19/06/01	//DeadCode JIM 27Feb96 			_Error.EmitSysErr("Middle ROWANLIB dates don't match - file %x",sourcefile);
//deadcode JIM 19/06/01	//DeadCode JIM 27Feb96 		if (((ULong*) (srcptr))[5] != ((ULong*) (trgptr))[5])
//deadcode JIM 19/06/01	//DeadCode JIM 27Feb96 			_Error.EmitSysErr("Middle ROWANLIB dates don't match - file %x",sourcefile);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			//CMPADDR HAS DONE ITS JOB!
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			srcptr+=8;
//deadcode JIM 19/06/01			trgptr+=8;
//deadcode JIM 19/06/01			//Ok.. can now copy until next header in either file
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			while 	(	(	(((ULong*) (trgptr))[0] != *((ULong*) ("ROWA")))
//deadcode JIM 19/06/01					 	|| (((ULong*) (trgptr))[1] != *((ULong*) ("NLIB")))
//deadcode JIM 19/06/01					 	|| (((ULong*) (trgptr))[2] != *((ULong*) ("EXIT")))
//deadcode JIM 19/06/01					 	|| (((ULong*) (trgptr))[3] != *((ULong*) ("OVER")))
//deadcode JIM 19/06/01						)
//deadcode JIM 19/06/01				 	&&	(	(((ULong*) (srcptr))[0] != *((ULong*) ("ROWA")))
//deadcode JIM 19/06/01					 	|| (((ULong*) (srcptr))[1] != *((ULong*) ("NLIB")))
//deadcode JIM 19/06/01					 	|| (((ULong*) (srcptr))[2] != *((ULong*) ("EXIT")))
//deadcode JIM 19/06/01					 	|| (((ULong*) (srcptr))[3] != *((ULong*) ("OVER")))
//deadcode JIM 19/06/01						)
//deadcode JIM 19/06/01					)
//deadcode JIM 19/06/01				*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			//Copy ROWANLIB part only, and only if target not full
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			if	 	(	(	(((ULong*) (trgptr))[0] == *((ULong*) ("ROWA")))
//deadcode JIM 19/06/01					 	|| (((ULong*) (trgptr))[1] == *((ULong*) ("NLIB")))
//deadcode JIM 19/06/01					 	|| (((ULong*) (trgptr))[2] == *((ULong*) ("EXIT")))
//deadcode JIM 19/06/01					 	|| (((ULong*) (trgptr))[3] == *((ULong*) ("OVER")))
//deadcode JIM 19/06/01						)
//deadcode JIM 19/06/01				 	&&	(	(((ULong*) (srcptr))[0] == *((ULong*) ("ROWA")))
//deadcode JIM 19/06/01					 	|| (((ULong*) (srcptr))[1] == *((ULong*) ("NLIB")))
//deadcode JIM 19/06/01					 	|| (((ULong*) (srcptr))[2] == *((ULong*) ("EXIT")))
//deadcode JIM 19/06/01					 	|| (((ULong*) (srcptr))[3] == *((ULong*) ("OVER")))
//deadcode JIM 19/06/01						)
//deadcode JIM 19/06/01					)
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01				trgptr+=8;
//deadcode JIM 19/06/01				srcptr+=8;
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01			else
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01		
//deadcode JIM 19/06/01	int			count=8;
//deadcode JIM 19/06/01				while 	(	(	(((ULong*) (trgptr))[0] != *((ULong*) ("ROWA")))
//deadcode JIM 19/06/01						 	|| (((ULong*) (trgptr))[1] != *((ULong*) ("NLIB")))
//deadcode JIM 19/06/01						 	|| (((ULong*) (trgptr))[2] != *((ULong*) ("EXIT")))
//deadcode JIM 19/06/01					 		|| (((ULong*) (trgptr))[3] != *((ULong*) ("OVER")))
//deadcode JIM 19/06/01							)
//deadcode JIM 19/06/01					 	&&	(count--)
//deadcode JIM 19/06/01						)
//deadcode JIM 19/06/01					*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01				//If target is full then error message
//deadcode JIM 19/06/01			
//deadcode JIM 19/06/01				if	(	(((ULong*) (trgptr))[0] == *((ULong*) ("ROWA")))
//deadcode JIM 19/06/01			 		&& (((ULong*) (trgptr))[1] == *((ULong*) ("NLIB")))
//deadcode JIM 19/06/01			 		&& (((ULong*) (trgptr))[2] == *((ULong*) ("EXIT")))
//deadcode JIM 19/06/01			 		&& (((ULong*) (trgptr))[3] == *((ULong*) ("OVER")))
//deadcode JIM 19/06/01					)
//deadcode JIM 19/06/01					_Error.EmitSysErr("Library too big for code space!!! - file %x",sourcefile);
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01			//Now search for ROWANLIB again in source
//deadcode JIM 19/06/01			while	(	(((ULong*) (srcptr))[0] != *((ULong*) ("ROWA")))
//deadcode JIM 19/06/01				 	|| (((ULong*) (srcptr))[1] != *((ULong*) ("NLIB")))
//deadcode JIM 19/06/01					)
//deadcode JIM 19/06/01				srcptr++;
//deadcode JIM 19/06/01			if (strcmp(srcptr,keyname))
//deadcode JIM 19/06/01				_Error.EmitSysErr("Keycode for library did not match. [%s] != [%s]",srcptr,keyname);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01				lockstart=llockstart;
//deadcode JIM 19/06/01				locksize=((ULong) trgptr)-lockstart;
//deadcode JIM 19/06/01				DPMIregs r;
//deadcode JIM 19/06/01				r.l.eax = 0x0600;							/* DPMI lock linear region */
//deadcode JIM 19/06/01				r.l.ebx = ((ULong) lockstart) >> 16;
//deadcode JIM 19/06/01				r.l.ecx = ((ULong) lockstart) & 0xFFFF;
//deadcode JIM 19/06/01				r.l.esi = ((ULong) locksize) >> 16;
//deadcode JIM 19/06/01				r.l.edi = ((ULong) locksize) & 0xFFFF;
//deadcode JIM 19/06/01				ASM_DEXint31(&r);
//deadcode JIM 19/06/01	//DeadCode ARM 04Jun96 			int386 (0x31, &r, &r);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			if (cmpbase && cmpbase!=targetaddr)
//deadcode JIM 19/06/01			{	//new job: build new virtual function table
//deadcode JIM 19/06/01				int delta =(int)targetaddr-(int)cmpbase;
//deadcode JIM 19/06/01				int *builder=(int*)trgptr;
//deadcode JIM 19/06/01				assert(jumpobject);
//deadcode JIM 19/06/01				int *bsrc=*jumpobject;
//deadcode JIM 19/06/01				*jumpobject=builder;
//deadcode JIM 19/06/01				while (*bsrc<(int)cmpaddr && *bsrc>(int)cmpbase)
//deadcode JIM 19/06/01				{
//deadcode JIM 19/06/01					for (int i=4;--i;)
//deadcode JIM 19/06/01					{
//deadcode JIM 19/06/01						if	(	(((ULong*) (trgptr))[0] == *((ULong*) ("ROWA")))
//deadcode JIM 19/06/01					 		&& (((ULong*) (trgptr))[1] == *((ULong*) ("NLIB")))
//deadcode JIM 19/06/01					 		&& (((ULong*) (trgptr))[2] == *((ULong*) ("EXIT")))
//deadcode JIM 19/06/01			 				&& (((ULong*) (trgptr))[3] == *((ULong*) ("OVER")))
//deadcode JIM 19/06/01							)
//deadcode JIM 19/06/01							_Error.EmitSysErr("Run out of space making DLL VFR! (%x,%s)",sourcefile,keyname);
//deadcode JIM 19/06/01						trgptr++;
//deadcode JIM 19/06/01					}
//deadcode JIM 19/06/01					*builder++=*bsrc++ + delta;
//deadcode JIM 19/06/01				}
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01			return(trgptr);
//deadcode JIM 19/06/01		 }
//deadcode JIM 19/06/01	#endif
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//destructor
//deadcode JIM 19/06/01	DES		StubLock::~StubLock()	{ClearLock();}
//deadcode JIM 19/06/01	void	StubLock::ClearLock()
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		if (lockstart && locksize!=-1)
//deadcode JIM 19/06/01	#ifdef WIN95
//deadcode JIM 19/06/01			FreeLibrary((HANDLE&)lockstart);
//deadcode JIM 19/06/01	#endif
//deadcode JIM 19/06/01	#ifdef __DOS__
//deadcode JIM 19/06/01		{	//free the lock
//deadcode JIM 19/06/01			DPMIregs r;
//deadcode JIM 19/06/01			r.l.eax = 0x0601;							/* DPMI lock linear region */
//deadcode JIM 19/06/01			r.l.ebx = ((ULong) lockstart) >> 16;
//deadcode JIM 19/06/01			r.l.ecx = ((ULong) lockstart) & 0xFFFF;
//deadcode JIM 19/06/01			r.l.esi = ((ULong) locksize) >> 16;
//deadcode JIM 19/06/01			r.l.edi = ((ULong) locksize) & 0xFFFF;
//deadcode JIM 19/06/01			ASM_DEXint31(&r);
//deadcode JIM 19/06/01	//DeadCode ARM 04Jun96 		int386 (0x31, &r, &r);
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01	#endif
//deadcode JIM 19/06/01		lockstart=0;
//deadcode JIM 19/06/01		locksize=0;
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 string	StubLock::CopyLibHeader(int newaddr,int oldaddr)
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 {
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 string	trgptr=(string)	newaddr;
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 	if (newaddr!=oldaddr)
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 	{
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 string	srcptr=(string) oldaddr;
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		while	(	(((ULong*) (srcptr))[0] != *((ULong*) ("ROWA")))
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 			 	&&	(((ULong*) (srcptr))[1] != *((ULong*) ("NLIB")))
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 				)
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 			*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		*(trgptr++)=*(srcptr++);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 	}
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 		return (trgptr);
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 #endif
//deadcode JIM 19/06/01	//DeadCode JIM 02May97 }
//deadcode JIM 19/06/01	
