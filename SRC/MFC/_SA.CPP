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


#include "stdafx.h"
#include "_mfc.h"

#include ".\Damage.cpp"
#include ".\filing.cpp"
#include ".\load.cpp"
#ifndef BOB_DEMO_VER

//DEADCODE DAW 26/11/99 #include ".\Frag.cpp"
//DEADCODE DAW 26/11/99 #include ".\FragPilt.cpp"


//Dangling dialogs
//DEADCODE DAW 29/01/00 #include ".\Career.cpp"
//DEADCODE DAW 29/01/00 #include ".\LstMsnlg.cpp"
//DEADCODE DAW 29/01/00 #include ".\Misn_log.cpp"
//DEADCODE DAW 29/01/00 #include ".\General.cpp"
#include ".\dosbut.cpp"
//DEADCODE DAW 29/01/00 #include ".\Dossier.cpp"
//#include ".\Notes.cpp"
//DEADCODE DAW 29/01/00 #include ".\Plyr_log.cpp"
#include ".\Weather.cpp"


//New sheets
#include "afdossr.cpp"
#include "radcomms.cpp"
#include "acalloc.cpp"
#include "afdetl.cpp"
#include "baseslft.cpp"
#include "dossdetl.cpp"
#include "dossierb.cpp"
#include "grpgesch.cpp"
#include "hostiles.cpp"
#include "mfraids.cpp"
#include "mftarget.cpp"
#include "mftop.cpp"
#include "phsdscr.cpp"
#include "pltlogbk.cpp"
#include "squaddtl.cpp"
#include "tlbrcntl.cpp"
#include "zoomlevl.cpp"
#include "IntelMsg.cpp"
#include "AcUnit.cpp"
#include "Author.cpp"
#include "clock.cpp"
#include "CntrlAcl.cpp"
#include "CntrlFly.cpp"
#include "CntrlTop.cpp"
#include "DirRsult.cpp"
#include "IntOff.cpp"
#include "SelTrg.cpp"
#include "Supply.cpp"
#include "TOOff.cpp"
#include "ToteSect.cpp"
#include "ToteTop.cpp"
#include "WPDialog.cpp"
#include "AcUnitRF.cpp"
#include "mapfltlw.cpp"
#include "dirnores.cpp"

#endif
