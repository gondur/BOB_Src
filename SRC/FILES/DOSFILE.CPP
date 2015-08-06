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
//Filename       dosfile.cpp
//System         
//Author         Paul.   
//Date           Mon 4 Nov 1996
//Description    FC CD stuff for DOS!
//------------------------------------------------------------------------------

//deadcode JIM 19/06/01	#include	"dosdefs.h"
//deadcode JIM 19/06/01	#define		F_GRAFIX
//deadcode JIM 19/06/01	#include	"hardpasm.h"
//deadcode JIM 19/06/01	#include	"myerror.h"
//deadcode JIM 19/06/01	#include 	<stdio.h>
//deadcode JIM 19/06/01	#include 	<conio.h>
//deadcode JIM 19/06/01	#include    <string.h>
//deadcode JIM 19/06/01	#include    <direct.h>
//deadcode JIM 19/06/01	#include	"mymath.h"
//deadcode JIM 19/06/01	#include	"fileman.h"
//deadcode JIM 19/06/01	#include	"mscdex.h"
//deadcode JIM 19/06/01	#include	"myAngles.h"
//deadcode JIM 19/06/01	#include	"worldinc.h"
//deadcode JIM 19/06/01	#include	"world.h"
//deadcode JIM 19/06/01	#include	"main.h"
//deadcode JIM 19/06/01	#include	"Mytime.h"
//deadcode JIM 19/06/01	#include	<new.h>
//deadcode JIM 19/06/01	#define		SPECIAL_KEYMAPS	FALSE
//deadcode JIM 19/06/01	#include	"Keytest.h"
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	extern 		Error 		_Error;
//deadcode JIM 19/06/01	extern 		MathLib		Math_Lib;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	const	int	DOSFILE_SECTSIZE = 2048;							//PD 18Nov96
//deadcode JIM 19/06/01	const	int	DOSFILE_SEEKSTEP = 8*DOSFILE_SECTSIZE;				//PD 18Nov96
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	DPMIMem		int_code,	int_data;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	#ifdef __WATCOMC__
//deadcode JIM 19/06/01	extern		void ASM_strcpy(UByte* src,UByte* dest);
//deadcode JIM 19/06/01	#pragma		aux	 ASM_strcpy = \
//deadcode JIM 19/06/01	"			mov		ebx,esi					"\
//deadcode JIM 19/06/01	"			xor		eax,eax					"\
//deadcode JIM 19/06/01	"			xor		ecx,ecx					"\
//deadcode JIM 19/06/01	"lp1:		mov		al,byte ptr ds:[esi]	"\
//deadcode JIM 19/06/01	"			inc		ecx						"\
//deadcode JIM 19/06/01	"			inc		esi						"\
//deadcode JIM 19/06/01	"			or		eax,eax					"\
//deadcode JIM 19/06/01	"			jnz		short lp1				"\
//deadcode JIM 19/06/01	"ok1:		mov		esi,ebx					"\
//deadcode JIM 19/06/01	"			rep		movsb					"\
//deadcode JIM 19/06/01	parm		[esi] [edi]						\
//deadcode JIM 19/06/01	modify		[eax ebx ecx esi edi]
//deadcode JIM 19/06/01	#else
//deadcode JIM 19/06/01	#ifdef __MSVC__
//deadcode JIM 19/06/01	inline void ASM_strcpy(UByte* src,UByte* dest)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01	    __asm
//deadcode JIM 19/06/01	    {
//deadcode JIM 19/06/01			mov esi,src;
//deadcode JIM 19/06/01			mov edi,dest;
//deadcode JIM 19/06/01			mov		ebx,esi;
//deadcode JIM 19/06/01			xor		eax,eax;
//deadcode JIM 19/06/01			xor		ecx,ecx;
//deadcode JIM 19/06/01	lp1:	mov		al,byte ptr ds:[esi];
//deadcode JIM 19/06/01			inc		ecx;
//deadcode JIM 19/06/01			inc		esi;
//deadcode JIM 19/06/01			or		eax,eax;
//deadcode JIM 19/06/01			jnz		short lp1;
//deadcode JIM 19/06/01	ok1:	mov		esi,ebx;
//deadcode JIM 19/06/01			rep		movsb;
//deadcode JIM 19/06/01	    }
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	#endif
//deadcode JIM 19/06/01	#endif
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	static char fnum=0;
//deadcode JIM 19/06/01	//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//deadcode JIM 19/06/01	//Procedure		CDCommand
//deadcode JIM 19/06/01	//Author		Paul.   
//deadcode JIM 19/06/01	//Date			Tue 29 Oct 1996
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Description	Interface to MSCDEX via int 2Fh funtion 15h subfunction 10h
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Inputs		Request block and command block + size of command block
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Returns		Status after executing the command
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	UWord fileman::CDCommand(RequestHeaderP ioctl,CDCommP command,int cmdsize)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		IOCTLI			*ioctli = (IOCTLI*)ioctl,
//deadcode JIM 19/06/01						*rm_ioctli;
//deadcode JIM 19/06/01		UByte			*commandp,
//deadcode JIM 19/06/01						*rm_command;
//deadcode JIM 19/06/01		unsigned char 	*real_mode_stack;
//deadcode JIM 19/06/01		DPMIregs		regs;
//deadcode JIM 19/06/01		int				REALMODE_STACK_SIZE;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//DeadCode JIM 14Dec96 	*(char*)0xB0702=fnum;///////////////////
//deadcode JIM 19/06/01		regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
//deadcode JIM 19/06/01		regs.l.edi=regs.l.ebp=regs.l.esi=0;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		real_mode_stack = Whole_Screen->real_mode_stack;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		REALMODE_STACK_SIZE = Window::REALMODE_STACK_SIZE;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		//Copy request header and command block to DOS RAM
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		rm_ioctli = (IOCTLI* )real_mode_stack;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		*rm_ioctli = *ioctli;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		rm_ioctli->transferaddr_seg = real_mode_seg;
//deadcode JIM 19/06/01		rm_ioctli->transferaddr_off = sizeof(IOCTLI);				//PD 29Oct96
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		rm_ioctli->bytestotransfer = cmdsize;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		rm_ioctli->status = 0;	//Must be cleared before command is executed
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		rm_command = (UByte* )(real_mode_stack + sizeof(IOCTLI));
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		commandp = (UByte* )command;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		for (int j=0;j<cmdsize;*rm_command++ = *commandp++,j++);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.w.ax = 0x1510;
//deadcode JIM 19/06/01		regs.w.cx = driveletter;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.w.bx = 0;
//deadcode JIM 19/06/01		regs.flags=regs.CLEAR;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//DeadCode JIM 14Dec96 	*(char*)0xB0704=fnum;///////////////////
//deadcode JIM 19/06/01		ASM_DOSvia31(0x2F,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//deadcode JIM 19/06/01	//DeadCode JIM 14Dec96 	*(char*)0xB0706=fnum;///////////////////
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		//copy the modified structures back up from DOS RAM
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		*ioctli = *rm_ioctli;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		rm_command = (UByte* )(real_mode_stack + sizeof(IOCTLI));
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		commandp = (UByte* )command;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		for (j=0;j<cmdsize;*commandp++ = *rm_command++,j++);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//DeadCode JIM 14Dec96 	*(char*)0xB0708=fnum;///////////////////
//deadcode JIM 19/06/01		return(rm_ioctli->status);
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//deadcode JIM 19/06/01	//Procedure		CDSeek
//deadcode JIM 19/06/01	//Author		Paul.   
//deadcode JIM 19/06/01	//Date			Tue 29 Oct 1996
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Description	Interface to MSCDEX via int 2Fh funtion 15h subfunction 10h
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Inputs		Request seek to block 'pos'
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Returns		Status after executing the command
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	UWord fileman::CDSeek(ULong pos)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		DPMIregs		regs;
//deadcode JIM 19/06/01		unsigned char 	*real_mode_stack;
//deadcode JIM 19/06/01		int				REALMODE_STACK_SIZE;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		real_mode_stack = Whole_Screen->real_mode_stack;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		REALMODE_STACK_SIZE = Window::REALMODE_STACK_SIZE;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
//deadcode JIM 19/06/01		regs.l.edi=regs.l.ebp=regs.l.esi=0;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.l.edx 	= pos;
//deadcode JIM 19/06/01		regs.w.ax = 0x0000;		//SEEK
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		ASM_DOSvia31(0x18,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//deadcode JIM 19/06/01		return(regs.w.ax);
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//deadcode JIM 19/06/01	//Procedure		GetDirectoryEntry
//deadcode JIM 19/06/01	//Author		Paul.   
//deadcode JIM 19/06/01	//Date			Wed 30 Oct 1996
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Description	Use int 2Fh function 15h subfunction Fh to fill dir_entry
//deadcode JIM 19/06/01	//				structure.
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Inputs		
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Returns	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	UWord fileman::CDGetDirectoryEntry(DirEntryP direntry,string filename)
//deadcode JIM 19/06/01	{			 
//deadcode JIM 19/06/01		unsigned char 	*real_mode_stack;
//deadcode JIM 19/06/01		DPMIregs		regs;
//deadcode JIM 19/06/01		int				REALMODE_STACK_SIZE;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		DirEntryP		rm_direntry;
//deadcode JIM 19/06/01		UByte*			rm_filename;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
//deadcode JIM 19/06/01		regs.l.edi=regs.l.ebp=regs.l.esi=0;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		real_mode_stack = Whole_Screen->real_mode_stack;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		REALMODE_STACK_SIZE = Window::REALMODE_STACK_SIZE;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		rm_direntry = (DirEntryP)real_mode_stack;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		rm_filename = (UByte* )(real_mode_stack+sizeof(DirEntry)*2);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		ASM_strcpy((UByte*)filename,rm_filename);							//PD 08Nov96
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.w.ax = 0x150F;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.b.cl = driveletter;
//deadcode JIM 19/06/01		regs.b.ch = 0x01;			//Fill generic directory structure
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		//filename string comes straight after the DirEntry structure
//deadcode JIM 19/06/01		//on the real_mode_stack
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		//pointer to DirEntry structure to fill in
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.w.si = real_mode_seg;		
//deadcode JIM 19/06/01		regs.w.di = 0;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		//pointer to NULL terminated filename string
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.s.es = real_mode_seg;
//deadcode JIM 19/06/01		regs.w.bx = sizeof(DirEntry)*2;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		ASM_DOSvia31(0x2F,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		//Copy filled in structure back up from DOS RAM
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		*direntry = *rm_direntry;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		if (regs.flags & DPMIregs::CF)	return (regs.w.ax);	//Error code if carry set
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		return (0);
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//deadcode JIM 19/06/01	//Procedure		CDReadFileBlock
//deadcode JIM 19/06/01	//Author		Paul.   
//deadcode JIM 19/06/01	//Date			Wed 30 Oct 1996
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Description	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Inputs		
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Returns	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	UWord fileman::CDReadFileBlock(ULong seekpos,void* blockdata,ULong datasize)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		DPMIregs		regs;
//deadcode JIM 19/06/01		unsigned char 	*real_mode_stack;
//deadcode JIM 19/06/01		int				REALMODE_STACK_SIZE;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		real_mode_stack = Whole_Screen->real_mode_stack;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		REALMODE_STACK_SIZE = Window::REALMODE_STACK_SIZE;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
//deadcode JIM 19/06/01		regs.l.edi=regs.l.ebp=regs.l.esi=0;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.l.edx 	= seekpos;
//deadcode JIM 19/06/01		regs.w.cx	= real_mode_seg;
//deadcode JIM 19/06/01		regs.w.bx	= 0;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.w.ax = 0x0001;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		ASM_DOSvia31(0x18,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		//Copy the loaded data to the correct data area
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		ULong	*srcp,*destp;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		srcp = (ULong* )real_mode_stack;
//deadcode JIM 19/06/01		destp = (ULong* )blockdata;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		for (int j=0;j<(datasize/4);*destp++=*srcp++,j++);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		return(regs.w.ax);
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//deadcode JIM 19/06/01	//Procedure		CDSetup
//deadcode JIM 19/06/01	//Author		Paul.   
//deadcode JIM 19/06/01	//Date			Mon 28 Oct 1996
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Description	Determines how many CD-ROM drives are attatched. Decides
//deadcode JIM 19/06/01	//				which one (if any ) contain our CD and makes sure the
//deadcode JIM 19/06/01	//				door is closed and locked.
//deadcode JIM 19/06/01	//				(for the moment I just assume that the first CD drive
//deadcode JIM 19/06/01	//				is ours and that the CD is in the drive)
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Inputs		
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Returns		cddir == ?:\FLY where ? is the CD-ROM drive letter for
//deadcode JIM 19/06/01	//						the drive containing our CD
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	void fileman::CDSetup(string cddir)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		DPMIregs	regs;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//DeadCode DAW 13Dec96 	if (Whole_Screen->prevmodeAX==0)
//deadcode JIM 19/06/01	//DeadCode DAW 13Dec96 		printf("Flying Corps CD ?\n");
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
//deadcode JIM 19/06/01		regs.l.edi=regs.l.ebp=regs.l.esi=0;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		unsigned char *real_mode_stack = Whole_Screen->real_mode_stack;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		int	REALMODE_STACK_SIZE = Window::REALMODE_STACK_SIZE;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		//Get number of CD-ROM drive letters
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		cddir[0]='\0';
//deadcode JIM 19/06/01		regs.w.ax = 0x1500;
//deadcode JIM 19/06/01		regs.w.bx=0;
//deadcode JIM 19/06/01		ASM_DOSvia31(0x2F,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//deadcode JIM 19/06/01		if (regs.w.bx==0)
//deadcode JIM 19/06/01			return;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		//Returns 	regs.w.bx = no. of CD-ROM drive letters
//deadcode JIM 19/06/01		//			regs.w.cx = starting drive letter of CD-ROM drive
//deadcode JIM 19/06/01		//						letters
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		real_mode_seg 	= regs.s.ds;
//deadcode JIM 19/06/01		driveletter 	= regs.w.cx;
//deadcode JIM 19/06/01		noofdrives 		= regs.w.bx;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.w.ax = 0x150C;
//deadcode JIM 19/06/01		regs.w.bx=0;
//deadcode JIM 19/06/01		ASM_DOSvia31(0x2F,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//deadcode JIM 19/06/01		if (regs.b.bh<2 || (regs.b.bh==2 && regs.b.bl<0x0a))
//deadcode JIM 19/06/01			return;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		Bool cdisours=FALSE;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		UWord	cmdstatus;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		IOCTLO	ioctlo,*ioctlop=&ioctlo;
//deadcode JIM 19/06/01		IOCTLI	ioctli,*ioctlip=&ioctli;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		struct	Raddr		raddr,		*raddrp=&raddr;
//deadcode JIM 19/06/01		struct	MedChng		medchng,	*medchngp=&medchng;
//deadcode JIM 19/06/01		struct	DevStat 	devstat,	*devstatp=&devstat;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		do
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			for (int disknum=0;disknum<26;disknum++)
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01				regs.w.ax=0x150B;
//deadcode JIM 19/06/01				regs.w.cx=disknum;
//deadcode JIM 19/06/01				ASM_DOSvia31(0x2F,&regs,real_mode_stack,REALMODE_STACK_SIZE,0);
//deadcode JIM 19/06/01				if (regs.w.bx==0xadad && regs.w.ax!=0)
//deadcode JIM 19/06/01				{
//deadcode JIM 19/06/01					driveletter=disknum;
//deadcode JIM 19/06/01					cmdstatus = CDCommand(ioctlip,devstatp,sizeof(DevStat));	//Read drive status
//deadcode JIM 19/06/01					if ((devstatp->deviceparameters & 0x801)==0)	//PD 05Nov96
//deadcode JIM 19/06/01					{
//deadcode JIM 19/06/01						string keyfile = "\\FLY\\LANDSCAP\\DIR.DIR";	
//deadcode JIM 19/06/01						DirEntry direntry,*direntryp=&direntry;
//deadcode JIM 19/06/01						cmdstatus = CDGetDirectoryEntry(direntryp,keyfile);
//deadcode JIM 19/06/01						if (cmdstatus==0)
//deadcode JIM 19/06/01						{
//deadcode JIM 19/06/01							if (Whole_Screen->prevmodeAX==0)
//deadcode JIM 19/06/01								printf("CD-ROM %c:\n",disknum+'A');
//deadcode JIM 19/06/01						 	cdisours=TRUE;
//deadcode JIM 19/06/01							break;
//deadcode JIM 19/06/01						}
//deadcode JIM 19/06/01					}
//deadcode JIM 19/06/01				}
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01			if (disknum==26)
//deadcode JIM 19/06/01				printf("Flying Corps CD-ROM ?\n");
//deadcode JIM 19/06/01			if (!cdisours)
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01				if (Whole_Screen->prevmodeAX==0)
//deadcode JIM 19/06/01					printf("Press any key to retry\n");									//english
//deadcode JIM 19/06/01	//TempCode DAW 06Jan97 				printf("Appuyez sur une touche pour redémarrer\n");					//french
//deadcode JIM 19/06/01	//TempCode DAW 06Jan97 				printf("Pulsa cualquier tecla para volver a intentarlo\n");			//spanish
//deadcode JIM 19/06/01	//TempCode DAW 06Jan97 				printf("Beliebige Taste drücken, um es erneut zu versuchen.\n");	//german
//deadcode JIM 19/06/01				UIKeyEvent	latestrawkey;
//deadcode JIM 19/06/01				while	(!Key_Tests.GetUIKey(latestrawkey)) {}
//deadcode JIM 19/06/01				if (latestrawkey.keycode==1)
//deadcode JIM 19/06/01				{
//deadcode JIM 19/06/01	//TempCode DAW 13Dec96 				if (Whole_Screen->prevmodeAX==0)
//deadcode JIM 19/06/01	//TempCode DAW 13Dec96 					printf("Skipping test...\n");
//deadcode JIM 19/06/01					driveletter=0;
//deadcode JIM 19/06/01					cdisours=TRUE;
//deadcode JIM 19/06/01				}
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01		while (!cdisours);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		struct	LockDoor	lockdoor,	*lockdoorp=&lockdoor;
//deadcode JIM 19/06/01		struct	SectSize	sectsize,	*sectsizep=&sectsize;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		if (driveletter)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			cmdstatus = CDCommand(ioctlip,raddrp,sizeof(Raddr));		//Get device header//JIM 12Nov96
//deadcode JIM 19/06/01			cmdstatus = CDCommand(ioctlip,medchngp,sizeof(MedChng));	//Check for media change//JIM 12Nov96
//deadcode JIM 19/06/01			lockdoor.lockfunction = 1;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			cmdstatus = CDCommand(ioctlop,lockdoorp,sizeof(LockDoor));
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			cmdstatus = CDCommand(ioctlip,sectsizep,sizeof(SectSize));
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			sectorsize = sectsizep->sectorsize;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//DeadCode PD 18Nov96 		direntries[dirnum(DIR_LANDSCAP)].openfile.cdstart=1;		//PD 05Nov96
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01		cddir[0]='A'+driveletter;
//deadcode JIM 19/06/01		cddir[1]=':';
//deadcode JIM 19/06/01		cddir[2]='\\';
//deadcode JIM 19/06/01		cddir[3]='F';
//deadcode JIM 19/06/01		cddir[4]='L';
//deadcode JIM 19/06/01		cddir[5]='Y';
//deadcode JIM 19/06/01		cddir[6]='\0';
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		//Install a new INT 18h handler to handle MSCDEX device
//deadcode JIM 19/06/01		//requests
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		ULong	devheadseg 	= (ULong )&fileman__DeviceHdrSeg - (ULong )&fileman__dosIRstart;
//deadcode JIM 19/06/01		ULong	devheadoff 	= (ULong )&fileman__DeviceHdrOff - (ULong )&fileman__dosIRstart;
//deadcode JIM 19/06/01		ULong	devletter 	= (ULong )&fileman__DriveLetter - (ULong )&fileman__dosIRstart;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		Whole_Screen->GetDOSRAM(int_data,(((ULong) &fileman__dosIRend)-((ULong) &fileman__dosIRstart)),0);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		int_code=int_data;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		//copy DOS IR to the buffer
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		string	fileisr=(string) int_code.flat,
//deadcode JIM 19/06/01				srcisr=(string) fileman__dosIRcode;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		for	(int i=(((ULong) fileman__dosIRend)-((ULong) fileman__dosIRcode));	 i--;)
//deadcode JIM 19/06/01			*(fileisr++)=*(srcisr++);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		*((UWord *)((UByte*)int_code.flat + devheadseg))=raddr.devheaderp_seg;
//deadcode JIM 19/06/01		*((UWord *)((UByte*)int_code.flat + devheadoff))=raddr.devheaderp_off;
//deadcode JIM 19/06/01		*((UWord *)((UByte*)int_code.flat + devletter))=driveletter;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
//deadcode JIM 19/06/01		regs.l.edi=regs.l.ebp=regs.l.esi=0;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.w.ax = 0x0200;
//deadcode JIM 19/06/01		regs.b.bl = 0x18;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		ASM_DEXint31(&regs);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		old_int18h_seg = regs.w.cx;
//deadcode JIM 19/06/01		old_int18h_off = regs.w.dx;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
//deadcode JIM 19/06/01		regs.l.edi=regs.l.ebp=regs.l.esi=0;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.w.ax = 0x0201;
//deadcode JIM 19/06/01		regs.b.bl = 0x18;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.w.cx = int_code.seg;
//deadcode JIM 19/06/01		regs.w.dx = int_code.off;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		ASM_DEXint31(&regs);
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//deadcode JIM 19/06/01	//Procedure		CDCloseDown
//deadcode JIM 19/06/01	//Author		Paul.   
//deadcode JIM 19/06/01	//Date			Tue 29 Oct 1996
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Description	Removes the lock on the CD drive
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Inputs		
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Returns	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	void fileman::CDCloseDown()
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		UWord		cmdstatus;
//deadcode JIM 19/06/01		DPMIregs	regs;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		IOCTLO	ioctlo,*ioctlop=&ioctlo;
//deadcode JIM 19/06/01		IOCTLI	ioctli,*ioctlip=&ioctli;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		struct	Raddr		raddr,		*raddrp=&raddr;
//deadcode JIM 19/06/01		struct	MedChng		medchng,	*medchngp=&medchng;
//deadcode JIM 19/06/01		struct	LockDoor	lockdoor,	*lockdoorp=&lockdoor;
//deadcode JIM 19/06/01		if (driveletter)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			cmdstatus = CDCommand(ioctlip,raddrp,sizeof(Raddr));
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			cmdstatus = CDCommand(ioctlip,medchngp,sizeof(MedChng));
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			lockdoor.lockfunction = 0;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			cmdstatus = CDCommand(ioctlop,lockdoorp,sizeof(LockDoor));
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01		//Restore old int 18h vector
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.l.eax=regs.l.ebx=regs.l.ecx=regs.l.edx=0;
//deadcode JIM 19/06/01		regs.l.edi=regs.l.ebp=regs.l.esi=0;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.w.ax = 0x0201;
//deadcode JIM 19/06/01		regs.b.bl = 0x18;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		regs.w.cx = old_int18h_seg;
//deadcode JIM 19/06/01		regs.w.dx = old_int18h_off;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		ASM_DEXint31(&regs);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		Whole_Screen->FreeDOSRAM(int_data);							//PD 06Nov96
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //Procedure		CDReSeek
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //Author		Paul.   
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //Date			Mon 4 Nov 1996
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //Description	
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //Inputs		
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //Returns	
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //------------------------------------------------------------------------------
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 void fileman::CDReSeek()
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 {
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	if (driveletter)											//PD 05Nov96
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	{															//PD 05Nov96
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		dirindex	di = dirnum(DIR_LANDSCAP);
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		direntries[di].openfile.currfileindex=0x07FFFFFFF;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	}															//PD 05Nov96
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 }
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //Procedure		CDMakeFileBlock
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //Author		Paul.   
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //Date			Mon 4 Nov 1996
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //Description	
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //Inputs		
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //Returns	
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //------------------------------------------------------------------------------
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 void fileman::CDMakeFileBlock(	fileblock* fbp,
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 								fileblocklink* link,
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 								FileNum MyFile,
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 								ULong	blocksize,
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 								ULong	offset)
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 {
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	//direntries.openfile.cdstart = logical block number of the CD file start on the disk
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	//direntries.openfile.currfileindex = current offset into the file
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	//									  if -ve then we are currently seeking to position
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	FILE*		filehandle;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	dirindex	di = dirnum(MyFile);
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	int			realfileindex = direntries[di].openfile.currfileindex;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	if (realfileindex & 0x80000000)
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	{
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		link->datasize=blocksize;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		realfileindex &= 0x7FFFFFFF;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		SLong	deltaseekpos;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		if (realfileindex!=offset)
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		{
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			//Abort the current seek and load the new data now
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			deltaseekpos=0;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		}
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		else
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			deltaseekpos = realfileindex - direntries[di].openfile.actualfileindex;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		if (deltaseekpos<=DOSFILE_SEEKSTEP)
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		{
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			direntries[di].openfile.currfileindex = realfileindex;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			direntries[di].openfile.actualfileindex = realfileindex;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			//close enough to load
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			if ((fbp->fileblockdata = new voidbigblock [link->datasize])==NULL)
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 				_Error.EmitSysErr("Failed to allocate memory for file load "
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 									"(file %x, size %d)",
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 									MyFile,link->datasize);
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			seekfilepos(direntries[di].openfile.handle,realfileindex);
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			readfileblock(direntries[di].openfile.handle,fbp->fileblockdata,link->datasize);
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		}
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		else
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		{
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			//skip read in steps of DOSFILE_SEEKSTEP
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			direntries[di].openfile.actualfileindex += DOSFILE_SEEKSTEP;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			if ((fbp->fileblockdata = new voidbigblock [link->datasize])==NULL)
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 				_Error.EmitSysErr("Failed to allocate memory for file load "
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 									"(file %x, size %d)",
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 									MyFile,link->datasize);
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			seekfilepos(direntries[di].openfile.handle,direntries[di].openfile.actualfileindex);
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			readfileblock(direntries[di].openfile.handle,fbp->fileblockdata,2048);
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			delete (fbp->fileblockdata);
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			fbp->fileblockdata=NULL;			//Flag to say seeking but not found yet
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		}
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	}
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	else
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	{
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		//start a new seek to position
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		if (direntries[di].openfile.number==MyFile)
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		{
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			direntries[di].openfile.currfileindex=offset | 0x80000000;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			link->datasize=blocksize;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			fbp->fileblockdata=NULL;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			if (offset<direntries[di].openfile.actualfileindex)
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			{
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 				direntries[di].openfile.actualfileindex = offset;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 //TempCode PD 17Nov96 				_Error.EmitSysErr("This file system has no reverse gear");
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			}
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		}
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		else
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		{
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			filehandle=opennumberedfile(MyFile);
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			link->datasize=getfilesize(filehandle);
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			if (link->datasize>blocksize)
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			{
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 				if (direntries[di].openfile.number!=INVALIDFILENUM)
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 					closefile(FILEMAN.direntries[di].openfile.handle);
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 				direntries[di].openfile.number=MyFile;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 				direntries[di].openfile.handle=filehandle;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 				direntries[di].openfile.maxfilesize=link->datasize;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 				direntries[di].openfile.currfileindex=offset | 0x80000000;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 				direntries[di].openfile.actualfileindex=offset;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 				if (offset>link->datasize)
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 					_Error.EmitSysErr("Index past end of file");
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 				link->datasize=blocksize;
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 				fbp->fileblockdata=NULL;			//Flag to say seeking but not found yet
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			}
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 			else
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 				assert((offset==0)&&"Can only use offset if buffer smaller than file!");
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 		}
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 	}
//deadcode JIM 19/06/01	//Old_Code PD 18Nov96 }
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 {
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 	//direntries.openfile.cdstart = logical block number of the CD file start on the disk
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 	//direntries.openfile.currfileindex = current offset into the file
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 	//									  if -ve then we are currently seeking to position
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 	UWord		cmdstatus;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 	dirindex	di = dirnum(MyFile);
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 	int			realfileindex = direntries[di].openfile.currfileindex;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 	if (realfileindex & 0x80000000)
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 	{
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		link->datasize=blocksize;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		struct	IOCTLI	ioctli,	*ioctlip=&ioctli;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		struct	LocHead	lochead,*locheadp=&lochead;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		realfileindex &= 0x7FFFFFFF;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		if (realfileindex!=offset)
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		{
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			//Abort the current seek and load the new data now
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			CDgetthedata=TRUE;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		}
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		ULong	reqseekpos = direntries[di].openfile.cdstart + (realfileindex/sectorsize);
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		if (CDgetthedata)
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		{
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			direntries[di].openfile.currfileindex = realfileindex;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			//close enough to load ( <3 sectors away)
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			if ((fbp->fileblockdata = new voidbigblock [link->datasize])==NULL)
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 				_Error.EmitSysErr("Failed to allocate memory for file load "
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 									"(file %x, size %d)",
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 									MyFile,link->datasize);
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			cmdstatus = CDReadFileBlock(reqseekpos,fbp->fileblockdata,2048);
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			cmdstatus = CDReadFileBlock(reqseekpos+1,(void*)((int)fbp->fileblockdata+2048),2048);
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			assert((cmdstatus==0x100)&&("CD Read file block failed"));
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		}
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		else
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		{
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			//check to see if we are close to the requested offset
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			cmdstatus = CDCommand(ioctlip,locheadp,sizeof(LocHead));
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			assert((cmdstatus&0x0100)&&("Request for CD head location failed"));
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			ULong	disttogo = (reqseekpos>=lochead.locofdrivehead)?
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 								reqseekpos-lochead.locofdrivehead:
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 								0x7FFFFFFF;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			if (disttogo==0)
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 				CDgetthedata=TRUE;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			else
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 				fbp->fileblockdata=NULL;			//Flag to say seeking but not found yet
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		}
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 	}
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 	else
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 	{
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		//start a new seek to position
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		DirEntry 	direntry,*direntryp=&direntry;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		CDgetthedata = FALSE;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		if (direntries[di].openfile.number==MyFile)
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		{
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			direntries[di].openfile.currfileindex=offset | 0x80000000;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			link->datasize=blocksize;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			ULong	reqseekpos = direntries[di].openfile.cdstart + (offset/sectorsize);
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			cmdstatus = CDSeek(reqseekpos);
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			assert((cmdstatus & 0x0100)&&("CD seek request failed"));
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			fbp->fileblockdata=NULL;			//Flag to say seeking but not found yet
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		}
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		else
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		{
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			cmdstatus = CDGetDirectoryEntry(direntryp,namenumberedfile(MyFile)+2);
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			assert((cmdstatus==0)&&("CDGetDirectoryEntry failed"));
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			direntries[di].openfile.cdstart=direntry.loc_extent;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			link->datasize = direntry.data_len;								//file size
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			if (link->datasize>blocksize)
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			{
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 				direntries[di].openfile.number=MyFile;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 				direntries[di].openfile.handle=0;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 				direntries[di].openfile.maxfilesize=link->datasize;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 				direntries[di].openfile.currfileindex=offset | 0x80000000;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 				if (offset>link->datasize)
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 					_Error.EmitSysErr("Index past end of file");
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 				link->datasize=blocksize;
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 				ULong	reqseekpos = direntries[di].openfile.cdstart + (offset/sectorsize);
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 				cmdstatus = CDSeek(reqseekpos);
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 				assert((cmdstatus & 0x0100)&&("CD seek request failed"));
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 				fbp->fileblockdata=NULL;			//Flag to say seeking but not found yet
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			}
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 			else
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 				assert((offset==0)&&"Can only use offset if buffer smaller than file!");
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 		}
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 	}
//deadcode JIM 19/06/01	//Old_Code PD 12Nov96 }
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//////////// New version of landscape file manipulation code - should work for Windows too ///////////////
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//deadcode JIM 19/06/01	//Procedure		SetupAreaFiles
//deadcode JIM 19/06/01	//Author		Paul.   
//deadcode JIM 19/06/01	//Date			Mon 18 Nov 1996
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Description	Opens and sets up the data structures required to
//deadcode JIM 19/06/01	//				keep all four landscape data files open
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Inputs		areafiles = ptr to a list of the four area file numbers required
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Returns	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	void fileman::SetupAreaFiles(FileNum* areafiles)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		FILE*		filehandle;
//deadcode JIM 19/06/01		FileNum		myfile;
//deadcode JIM 19/06/01		DirEntry 	direntry,
//deadcode JIM 19/06/01					*direntryp=&direntry;
//deadcode JIM 19/06/01		UWord		cmdstatus;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	  	for (int fileindex=0;fileindex<MAXCDFILEENTRIES;fileindex++)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			myfile = areafiles[fileindex];
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			if (cdfiles[fileindex].number!=myfile)
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01	 			filehandle = opennumberedfile(myfile);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01				if (cdfiles[fileindex].number!=INVALIDFILENUM)
//deadcode JIM 19/06/01					closefile(cdfiles[fileindex].handle);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01				cdfiles[fileindex].number=myfile;
//deadcode JIM 19/06/01				cdfiles[fileindex].handle=filehandle;
//deadcode JIM 19/06/01				cdfiles[fileindex].maxfilesize=getfilesize(filehandle);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01				cmdstatus=CDGetDirectoryEntry(direntryp,namenumberedfile(myfile));
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01				if (cmdstatus==0)
//deadcode JIM 19/06/01					cdfiles[fileindex].filebase=direntry.loc_extent;
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//deadcode JIM 19/06/01	//Procedure		CloseAreaFiles
//deadcode JIM 19/06/01	//Author		Paul.   
//deadcode JIM 19/06/01	//Date			Mon 18 Nov 1996
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Description	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Inputs		
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Returns	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	void fileman::CloseAreaFiles()
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		int	fileindex;
//deadcode JIM 19/06/01		for (fileindex=0;fileindex<MAXCDFILEENTRIES;fileindex++)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			if (cdfiles[fileindex].number!=INVALIDFILENUM)
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01				fclose (cdfiles[fileindex].handle);
//deadcode JIM 19/06/01				cdfiles[fileindex].number = INVALIDFILENUM;
//deadcode JIM 19/06/01				cdfiles[fileindex].handle = NULL;
//deadcode JIM 19/06/01				cdfiles[fileindex].maxfilesize = 0;
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01		cdfile.number = INVALIDFILENUM;
//deadcode JIM 19/06/01		cdfile.handle = NULL;
//deadcode JIM 19/06/01		cdfile.maxfilesize = 0;
//deadcode JIM 19/06/01		cdfile.currindex = 0;
//deadcode JIM 19/06/01		cdfile.actualindex = -1;
//deadcode JIM 19/06/01		cdfile.seekingtoposition=0;
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//deadcode JIM 19/06/01	//Procedure		resetCDfile
//deadcode JIM 19/06/01	//Author		Paul.   
//deadcode JIM 19/06/01	//Date			Mon 18 Nov 1996
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Description	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Inputs		
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Returns	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	void fileman::resetCDfile(FileNum myfile)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		if (cdfile.number!=myfile)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			//requested file is not the current one
//deadcode JIM 19/06/01			//make the requested file the current file
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			for (int fileindex=0;;fileindex++)
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01				if (fileindex==MAXCDFILEENTRIES)
//deadcode JIM 19/06/01					_Error.EmitSysErr("Requested CD file is not in the current area");
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01				if (cdfiles[fileindex].number==myfile)	break;
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			cdfile.number = cdfiles[fileindex].number;
//deadcode JIM 19/06/01			cdfile.handle = cdfiles[fileindex].handle;
//deadcode JIM 19/06/01			cdfile.maxfilesize = cdfiles[fileindex].maxfilesize;
//deadcode JIM 19/06/01			cdfile.filebase = cdfiles[fileindex].filebase;
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01		cdfile.currindex = 0;
//deadcode JIM 19/06/01		cdfile.actualindex = -1;
//deadcode JIM 19/06/01		cdfile.seekingtoposition=0;									//DAW 19Dec96
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//deadcode JIM 19/06/01	//Procedure		loadCDfile
//deadcode JIM 19/06/01	//Author		Paul.   
//deadcode JIM 19/06/01	//Date			Mon 18 Nov 1996
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Description	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Inputs		myfile = CD landscape file number
//deadcode JIM 19/06/01	//				length = length of block to load
//deadcode JIM 19/06/01	//				offset = index into the file to load the block from
//deadcode JIM 19/06/01	//				skipread = 	TRUE means do skip reads and waits (default)
//deadcode JIM 19/06/01	//							FALSE means just load the block immediately	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Returns	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	void* fileman::loadCDfile(FileNum myfile,SLong length,SLong offset,Bool skipread)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		void*	retval = NULL;
//deadcode JIM 19/06/01		fnum++;
//deadcode JIM 19/06/01		if ((offset+length)>cdfile.maxfilesize)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			offset-=cdfile.maxfilesize;
//deadcode JIM 19/06/01			skipread=FALSE;
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		if (myfile!=cdfile.number)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			//not the current CD file
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			if (cdfile.currindex & 0x80000000)
//deadcode JIM 19/06/01				_Error.EmitSysErr("Still seeking in different file");
//deadcode JIM 19/06/01			else
//deadcode JIM 19/06/01				resetCDfile(myfile);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			if (driveletter!=0)
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01				if (skipread==TRUE)
//deadcode JIM 19/06/01				{
//deadcode JIM 19/06/01					ULong	reqseekpos=cdfile.filebase+(offset/sectorsize);
//deadcode JIM 19/06/01					UWord	cmdstatus=CDSeek(reqseekpos);
//deadcode JIM 19/06/01					assert	((cmdstatus&0x0100)&&("CD Seek request failed"));
//deadcode JIM 19/06/01					cdfile.currindex = offset;
//deadcode JIM 19/06/01					cdfile.actualindex = offset;
//deadcode JIM 19/06/01					cdfile.seekingtoposition = 300;					//PD 10Dec96
//deadcode JIM 19/06/01					return	(retval);
//deadcode JIM 19/06/01				}
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01			else
//deadcode JIM 19/06/01				cdfile.actualindex = -1;
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		if (cdfile.seekingtoposition!=0)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			UWord	cmdstatus;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			IOCTLI	ioctli,
//deadcode JIM 19/06/01					*ioctlip=&ioctli;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			struct	LocHead	lochead,
//deadcode JIM 19/06/01							*locheadp=&lochead;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			cmdstatus = CDCommand(ioctlip,locheadp,sizeof(LocHead));
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			assert((cmdstatus&0x0100)&&("Request for CD head location failed"));
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			SLong	disttogo=cdfile.filebase+(cdfile.currindex/sectorsize);
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			disttogo -= lochead.locofdrivehead;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			if (disttogo == 0)										//PD 10Dec96
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01				cdfile.seekingtoposition=0;
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01			else
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01				cdfile.seekingtoposition--;
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01			return (retval);
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		if (skipread==FALSE)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			retval = (void*)new unsigned char[length];
//deadcode JIM 19/06/01			if (retval==NULL)
//deadcode JIM 19/06/01				_Error.EmitSysErr("Failed to allocate memory for file load");
//deadcode JIM 19/06/01			seekfilepos(cdfile.handle,offset);
//deadcode JIM 19/06/01			readfileblock(cdfile.handle,retval,length);
//deadcode JIM 19/06/01			cdfile.currindex = cdfile.actualindex = offset+length;
//deadcode JIM 19/06/01			cdfile.seekingtoposition=0;
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01		else
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			int	realindex = cdfile.currindex;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01			if (realindex & 0x80000000)
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01				//Currently processing an existing request for
//deadcode JIM 19/06/01				//a block of data
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01				realindex &= 0x7FFFFFFF;
//deadcode JIM 19/06/01				int	deltaseekpos;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01				if (realindex!=offset)
//deadcode JIM 19/06/01				{
//deadcode JIM 19/06/01					//Abort the current seek and just load in
//deadcode JIM 19/06/01					//the block that has been requested
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01					deltaseekpos=0;
//deadcode JIM 19/06/01				}
//deadcode JIM 19/06/01				else
//deadcode JIM 19/06/01					deltaseekpos=realindex-cdfile.actualindex;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01				if (deltaseekpos<=DOSFILE_SEEKSTEP)
//deadcode JIM 19/06/01				{
//deadcode JIM 19/06/01					retval = (void*)new unsigned char[length];
//deadcode JIM 19/06/01					if (retval==NULL)
//deadcode JIM 19/06/01						_Error.EmitSysErr("Failed to allocate memory for file load");
//deadcode JIM 19/06/01					seekfilepos(cdfile.handle,realindex);			//PD 21Nov96
//deadcode JIM 19/06/01					readfileblock(cdfile.handle,retval,length);
//deadcode JIM 19/06/01					cdfile.currindex = cdfile.actualindex = realindex + DOSFILE_SEEKSTEP;
//deadcode JIM 19/06/01				}
//deadcode JIM 19/06/01				else
//deadcode JIM 19/06/01				{
//deadcode JIM 19/06/01					//Do the skip reads here
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01					cdfile.actualindex += DOSFILE_SEEKSTEP;
//deadcode JIM 19/06/01					retval = (void*)new unsigned char[DOSFILE_SECTSIZE];
//deadcode JIM 19/06/01					if (retval==NULL)
//deadcode JIM 19/06/01						_Error.EmitSysErr("Failed to allocate memory for skip read");
//deadcode JIM 19/06/01					seekfilepos(cdfile.handle,cdfile.actualindex);
//deadcode JIM 19/06/01					readfileblock(cdfile.handle,retval,DOSFILE_SECTSIZE);
//deadcode JIM 19/06/01					delete ((unsigned char *)retval);
//deadcode JIM 19/06/01					retval = NULL;
//deadcode JIM 19/06/01				}
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01			else
//deadcode JIM 19/06/01			{
//deadcode JIM 19/06/01				//Start off a new seek request here!!
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01				cdfile.currindex = offset | 0x80000000;
//deadcode JIM 19/06/01				if ((offset+length)>=cdfile.maxfilesize)
//deadcode JIM 19/06/01					_Error.EmitSysErr("Seek past end of file");
//deadcode JIM 19/06/01				if (cdfile.actualindex==-1)	//New seek + new file
//deadcode JIM 19/06/01				{
//deadcode JIM 19/06/01					seekfilepos(cdfile.handle,cdfile.actualindex);
//deadcode JIM 19/06/01					cdfile.actualindex = offset;
//deadcode JIM 19/06/01				}
//deadcode JIM 19/06/01			}
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01		return (retval);
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	void fileman::SendCDCommand(UByteP command)					//PD 16Dec96
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//deadcode JIM 19/06/01	//Procedure		pingCD
//deadcode JIM 19/06/01	//Author		R. Hyde 
//deadcode JIM 19/06/01	//Date			Tue 17 Dec 1996
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Description	Read 1 cd block and increment the current head position
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Inputs		
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Returns	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	void fileman::pingCD()
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		void* retval;
//deadcode JIM 19/06/01		//Do the skip reads here
//deadcode JIM 19/06/01		cdfile.actualindex += DOSFILE_SEEKSTEP;
//deadcode JIM 19/06/01		retval = (void*)new unsigned char[DOSFILE_SECTSIZE];
//deadcode JIM 19/06/01		seekfilepos(cdfile.handle,cdfile.actualindex);
//deadcode JIM 19/06/01		readfileblock(cdfile.handle,retval,DOSFILE_SECTSIZE);
//deadcode JIM 19/06/01		delete ((unsigned char *)retval);
//deadcode JIM 19/06/01	}
