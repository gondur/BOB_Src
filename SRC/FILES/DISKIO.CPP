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
//Filename       diskio.cpp
//System         
//Author         Paul.   
//Date           Thu 6 Jul 1995
//Description    Wow! This is old!
//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	#define	InDiskIO	"Yes"
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	#include	<stdlib.h>
//deadcode JIM 19/06/01	#include	<io.h>
//deadcode JIM 19/06/01	#include	<dos.h>
//deadcode JIM 19/06/01	#include	<fcntl.h>
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	#include	"DOSDefs.h"
//deadcode JIM 19/06/01	#include	"DiskIO.H"
//deadcode JIM 19/06/01	//DeadCode DAW 15Apr96 #include	"Screen.H"
//deadcode JIM 19/06/01	//DeadCode DAW 19Mar96 #include	"GetSet.H"
//deadcode JIM 19/06/01	#include	"myAngles.h"
//deadcode JIM 19/06/01	#include	"Worldinc.h"
//deadcode JIM 19/06/01	#include	"World.h"
//deadcode JIM 19/06/01	#include	"Main.H"
//deadcode JIM 19/06/01	#include 	"myError.h"
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	extern	Main	_Main;
//deadcode JIM 19/06/01	extern 	Error	_Error;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	DiskIO	_DiskIO;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//Old_Code DAW 15Nov95 const	char	*FileList[] =
//deadcode JIM 19/06/01	//Old_Code DAW 15Nov95 	{
//deadcode JIM 19/06/01	//Old_Code DAW 15Nov95 		#include	"MastFile.H"
//deadcode JIM 19/06/01	//Old_Code DAW 15Nov95 	};
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//deadcode JIM 19/06/01	//Procedure	DiskIO::LoadNumberedFile
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	//Author		Paul.   
//deadcode JIM 19/06/01	//Date		Thu 6 Jul 1995
//deadcode JIM 19/06/01	//Modified	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Description	Temporary version that just uses an equate to index into a list 
//deadcode JIM 19/06/01	//			of filenames.
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Inputs		File number
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Returns	Address where file has been loaded
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Externals
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	char *DiskIO::LoadNumberedFile(short FileNumber)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		int	handle;
//deadcode JIM 19/06/01		unsigned int	readlength;
//deadcode JIM 19/06/01		long	filesize;
//deadcode JIM 19/06/01		char	*buffer;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		if(_dos_open(FileList[FileNumber],O_RDONLY,&handle) !=0)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			_Error.EmitSysErr(__FILE__":Can't open %s",FileList[FileNumber]);
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		if((filesize = filelength(handle))==-1)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			_Error.EmitSysErr(__FILE__":Error getting length of %s",FileList[FileNumber]);
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		readlength = filesize;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		buffer = new char [readlength];
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		if(_dos_read(handle,buffer,readlength,&readlength) !=0)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			_Error.EmitSysErr(__FILE__":Error reading %s",FileList[FileNumber]);
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		if(_dos_close(handle) !=0)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			_Error.EmitSysErr(__FILE__":Error closing %s",FileList[FileNumber]);
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01		return(buffer);
//deadcode JIM 19/06/01	}	
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01	//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//deadcode JIM 19/06/01	//Procedure	DiskIO::SaveNumberedFile
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	//Author	Paul.   
//deadcode JIM 19/06/01	//Date		Thu 6 Jul 1995
//deadcode JIM 19/06/01	//Modified	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Description	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Inputs	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Returns	
//deadcode JIM 19/06/01	//
//deadcode JIM 19/06/01	//Externals
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	//------------------------------------------------------------------------------
//deadcode JIM 19/06/01	void DiskIO::SaveNumberedFile(short FileNumber, char *Buffer, short FileLength)
//deadcode JIM 19/06/01	{
//deadcode JIM 19/06/01		int	handle;
//deadcode JIM 19/06/01		unsigned int BytesWritten;
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		if(_dos_creat(FileList[FileNumber],_A_NORMAL,&handle) !=0)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			_Error.EmitSysErr(__FILE__":Can't open %s for output",FileList[FileNumber]);
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		if(_dos_write(handle,Buffer,FileLength,&BytesWritten) !=0)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01			_Error.EmitSysErr(__FILE__":Error writing %s",FileList[FileNumber]);
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01	
//deadcode JIM 19/06/01		if(_dos_close(handle) !=0)
//deadcode JIM 19/06/01		{
//deadcode JIM 19/06/01		 	_Error.EmitSysErr(__FILE__":Error closing %s",FileList[FileNumber]);
//deadcode JIM 19/06/01		}
//deadcode JIM 19/06/01	}
//deadcode JIM 19/06/01	
