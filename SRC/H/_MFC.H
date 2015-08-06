#ifndef __MFC_INCLUDED
#define	__MFC_INCLUDED
#pragma optimize( "g", off )
#define	THIS_FILE_DEFINED
#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
#define THIS_FILE __FILE__
#endif
//DEADCODE MS 02/02/00 #include "dosdefs.h"
//DEADCODE MS 02/02/00 #include "files.g"
//DEADCODE MS 02/02/00 
//DEADCODE MS 02/02/00 #include	<afxmt.h>
//DEADCODE MS 02/02/00 #include	<dinput.h>
//DEADCODE MS 02/02/00 #include	<mmsystem.h>
//DEADCODE MS 02/02/00 #include	"stub3d.h" 
//DEADCODE MS 02/02/00 #include "display.h"  
//DEADCODE MS 02/02/00 #include "stdafx.h"
//DEADCODE MS 02/02/00 #include	"flyinit.h"
//DEADCODE MS 02/02/00 #include	"DEBRIEF.h"

MATHABLE(SquadSelect)
//#ifndef	THIS_FILE_DEFINED
//DEADCODE DAW 29/01/00 MATHABLE(Debrief::Types)
//#endif
//DEADCODE DAW 29/01/00 MATHABLE(Debrief::PlayerTypes)
#ifndef _DEBUG
#pragma message(__HERE__ "Non-debug version: global optimisation enabled when safe!")
#pragma optimize( "g", on )
#endif
#define	REALISTIC_SPOTTING_COUNTS
#include "ranges.h"
#include "package.h"
#include "missman2.h"
#include "nodebob.h"
#endif



