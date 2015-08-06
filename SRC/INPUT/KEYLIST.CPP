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

//
// This module writes the key and joystick mapping to a binary file...
//
//DEADCODE JIM 10/02/00 RECURSION TREE FOR C:\bob\Src\Input\Keylist.cpp
//DEADCODE JIM 10/02/00 "C:\bob\Src\Input\Keylist.cpp"		"C:\bob\Src\Input\Keylist.cpp"
//DEADCODE JIM 10/02/00  "<stdio.h>"		"(SYSTEM)"
//DEADCODE JIM 10/02/00  "DosDefs.h"		"C:\bob\Src\H\Dosdefs.h"
//DEADCODE JIM 10/02/00  "keytest.h"		"C:\bob\Src\H\Keytest.h"
//DEADCODE JIM 10/02/00   "dosdefs.h"		"(REPEATED)"
//DEADCODE JIM 10/02/00   "keymaps.h"		"C:\bob\Src\H\Keymaps.h"
//DEADCODE JIM 10/02/00    "<dinput.h>"		"(SYSTEM)"
	
//
//DEADCODE JIM 10/02/00 #include	<dos.h>
#include <stdio.h>
//#include	"stdafx.h"
//DEADCODE JIM 10/02/00 #include	"DosDefs.h"
typedef	unsigned short	UWord;
//#include	"Files.g"
enum	FileNum;
//DEADCODE JIM 10/02/00 #include	"fileman.h"

//#include	"hardpasm.h"										//ARM 04Jun96
const	TOTALKEYBITFLAGS=768;

#define	SPECIAL_KEYMAPS	1
#include	"keymaps.h"
;

main(int argc,char** argv)
{
	FILE* f=fopen(argv[1],"wb");
	if (f)
	{
		KeyMapping	*Debug3dMapTable=ThisKeyMapping;
		while (Debug3dMapTable->bitflag!=0)
			fwrite(Debug3dMapTable++,sizeof(KeyMapping),1,f);
		fclose(f);
		return 0;
	}

	return 1;
}
