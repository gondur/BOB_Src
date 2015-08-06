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
//Filename       formatn.cpp
//System         
//Author         R. Hyde 
//Date           Wed 17 Jan 1996
//Description
//
//For FC:	Each in-flight formation needs 5 followers.
//			Each interflight formation needs a leader and 4 followers
//
//For MiG:	
//	For Blues	- max 4 flights of [2 elts of 2 ac]
//		Each in-flight form has 3 followers
//		Follower position 3 is relative to position 2 while (2) is alive
//			then is relative to the leader
//		Each inter-flight form needs 7 followers and a leader escort pos
//	For Reds	- max 25 aircraft - max 8 fl and max 8 aircraft per flight?
//		Each in flight form needs 7 followers
//		Each interflight form needs 1 for leader & 7 followers
//	If the migs are going to throw a ruse, 
//		the ruse aircraft are a second group.
//
//Special:
//	If 1 or 2 groups are escorting others of the same aircraft type, 
//	and the same formation type,
//	then I want them to all fly in formation with each other, 
//	not in escort formation.
//
//For BoB:
//	Each squadron flies in a formation as before, But extra bits in the formation define 
//	how the squadron files as a group with other squadrons.
//	The following fields work together to define how the squadron forms up together
//		FORMTYPE_WING	=	0x0007,
//		FORMTYPE_SQUAD	=	0x0038,
//	These 2 fields define how a second squadron forms in an 'escort' position
//		FORMTYPE_INTER	=	0x0180,
//		FORMTYPE_INTERCHILD=0x0040,	//first or second child position
//	The remaining fields describe how the squadron flies between waypoints so that
//	it doesn't perform a midair passenger exchange:
//		FORMTYPE_COURSESEL=	0x0e00,
//		FORMTYPE_COURSEPOS=	0xf000,
//	NOTE: These do not need to be unique... it was just simplest for me to make them unique for now!
//
//	FIELDS ARE:	RANGE,	BEARING,	ALTITUDE
//------------------------------------------------------------------------------


//DeadCode DAW 29Feb96 #include	"dosdefs.h"
//DeadCode DAW 29Feb96 #include	"Files.G"
//DeadCode DAW 29Feb96 #include	"uniqueid.g"
//DeadCode JIM 16Nov95 #include	"text.G"
//#include	"miss_man.h"
//#undef	MISS_MAN_Included
//------------------------------------------------------------------------------


//DeadCode JIM 30Apr96 #include	"miss_man.h"
//#include	"ui.h"												//JIM 30Apr96
//LastModified:	JIM 24Jul96

#include	"dosdefs.h"
#include	"files.g"
//DEADCODE JIM 09/02/00 #include	"text.h"
#include	"ranges.h"
#include	"mytime.h"											//RDH 12Jan96
#include	"uniqueid.h"
#include	"worldinc.h"
#include	"bitfield.h"
#include	"misssub.h"
#include	"mymath.h"

//		FORMTYPE_WING	=	0x0007,	//Total A/C
//			FTW_RAFVIC	=	0x0000,	//3
//			FTW_LWVIC	=	0x0001,	//3/5
//			FTW_FLAT5	=	0x0002,	//5
//			FTW_SCWARM	=	0x0003,	//4
//			FTW_BSCRWARM=	0x0004,	//4
//			FTW_FINGER	=	0x0005,	//4	  originalformpos
//			FTW_RAFTAIL	=	0x0006,	//3
//			FTW_MAL		=	0x0007,	//3/4 undecided
//LW Vics can be 3s or 5s based on total original aircraft:
//3:	3s
//5:	5s
//6:	3s
//9:	3s
//10:	5s
//12:	3s
//15:	5s
//

static FormationType 
//PASS2
Form_RAFVIC =
{
	3,//	/*name*/		(TextRef)TEXT_FLATV,
	{
		{	FT_63,ANGLES_120Deg,METRES00},
		{	FT_63,ANGLES_240Deg,METRES00},
	}
},

//PASS2
Form_LWVIC =
{
//TempCode MS 31May00 	35,//	/*name*/		(TextRef)TEXT_FLATV,
	35,//	/*name*/		(TextRef)TEXT_FLATV,
	{
//DeadCode MS 25Jan00 		{	FT_90,ANGLES_135Deg,METRES00},
//DeadCode MS 25Jan00 		{	FT_90,ANGLES_225Deg,METRES00},
//DeadCode MS 25Jan00 		{	FT_180,ANGLES_135Deg,METRES00},
//DeadCode MS 25Jan00 		{	FT_180,ANGLES_225Deg,METRES00},
		{	FT_150,ANGLES_120Deg,FT_10},
		{	FT_150,ANGLES_240Deg,FT_10},
		{	FT_300,ANGLES_120Deg,FT_20},
		{	FT_300,ANGLES_240Deg,FT_20},
	}
},
//PASS0
Form_FLAT5 =
{
//TempCode MS 31May00 	5,//	/*name*/		(TextRef)TEXT_FLATV,
	35,//	/*name*/		(TextRef)TEXT_FLATV,
	{
//TempCode MS 01Jun00 		{	FT_300,ANGLES_120Deg,METRES00},
//TempCode MS 01Jun00 		{	FT_300,ANGLES_240Deg,METRES00},
//TempCode MS 01Jun00 		{	FT_300,ANGLES_240Deg,METRES00},
//TempCode MS 01Jun00 		{	FT_600,ANGLES_120Deg,METRES00},
		{	FT_100,ANGLES_120Deg,METRES00},
		{	FT_100,ANGLES_240Deg,METRES00},
		{	FT_200,ANGLES_120Deg,METRES00},
		{	FT_200,ANGLES_240Deg,METRES00},
	}
},
//PASS0
Form_SCWARM =
{
	204,//	/*name*/		(TextRef)TEXT_FLATV,
	{
		{	FT_750,ANGLES_240Deg,METRES00},
		{	FT_750,ANGLES_110Deg,FT_200},
		{	FT_1000,ANGLES_120Deg,FT_200},
		//THIS EXTRA ENTRY IS FOR FINGER4-PAIR
		//While the other entries are relative to the flight leader,
		//In finger 4 the second wingman is relative to the lead wingman!!!
		{	FT_750,ANGLES_110Deg,METRES00},	
	}
},
//PASS1
Form_BSCRWARM =			//mirror
{
	204,//	/*name*/		(TextRef)TEXT_FLATV,
	{
		{	FT_750,ANGLES_120Deg,METRES00},
		{	FT_750,ANGLES_240Deg,FT_200},
		{	FT_1000,ANGLES_240Deg,FT_200},
		//THIS EXTRA ENTRY IS FOR FINGER4-PAIR
		//While the other entries are relative to the flight leader,
		//In finger 4 the second wingman is relative to the lead wingman!!!
		{	FT_750,ANGLES_240Deg,METRES00},
	}
},
//PASS1
Form_FINGER =
{
	204,//	/*name*/		(TextRef)TEXT_FLATV,
	{
		{	FT_200,ANGLES_240Deg,FT_10},
		{	FT_200,ANGLES_110Deg,FT_10},
		{	FT_400,ANGLES_120Deg,FT_20},
		//THIS EXTRA ENTRY IS FOR FINGER4-PAIR
		//While the other entries are relative to the flight leader,
		//In finger 4 the second wingman is relative to the lead wingman!!!
		{	FT_300,ANGLES_240Deg,0},
	}
},
//Not using
Form_RAFTAIL =	//???? may dump
{
	3,//	/*name*/		(TextRef)TEXT_FLATV,
	{
		{	FT_300,ANGLES_120Deg,METRES00},
		{	FT_300,ANGLES_240Deg,METRES00},
	}
},
//Not using
Form_MAL	 =	//will dump
{
	3,//	/*name*/		(TextRef)TEXT_FLATV,
	{
		{	FT_300,ANGLES_120Deg,METRES00},
		{	FT_300,ANGLES_240Deg,METRES00},
	}
},

//		FORMTYPE_WING	=	0x0007,
//			FTW_RAFVIC	=	0x0000,		RAFVIC	=
//			FTW_LWVIC	=	0x0001,		LWVIC	=
//			FTW_FLAT5	=	0x0002,		FLAT5	=
//			FTW_SCWARM	=	0x0003,		SCWARM	=
//			FTW_BSCRWARM=	0x0004,		BSCRWARM=
//			FTW_FINGER	=	0x0005,		FINGER	=
//			FTW_RAFTAIL	=	0x0006,		RAFTAIL	=
//			FTW_MAL		=	0x0007,		MAL		=
//		FORMTYPE_SQUAD	=	0x0038,
//			FTS_VIC		=	0x0000,		VIC		=
//			FTS_ECHL	=	0x0008,		ECHL	=
//			FTS_ECHR	=	0x0010,		ECHR	=
//			FTS_ABREST	=	0x0018,		ABREST	=
//			FTS_ASTERN	=	0x0020,		ASTERN	=
//			FTS_DIAMOND	=	0x0028,		DIAMOND	=
//			FTS_BOX		=	0x0030,		BOX		=
//			FTS_WEAVE	=	0x0038,		WEAVE	=
//
//PASS2
VForm_RAFVIC_VIC =
{
	4,
	{
//TempCode MS 19Jun00 		{	FT_200,ANGLES_240Deg,FT_10},
//TempCode MS 19Jun00 		{	FT_200,ANGLES_120Deg,FT_10},
//TempCode MS 19Jun00 		{	FT_400,ANGLES_120Deg,FT_20},
		{	FT_200,ANGLES_250Deg,FT_10},
		{	FT_200,ANGLES_110Deg,FT_10},
		{	FT_400,ANGLES_110Deg,FT_20},
	}
},
//PASS1
VForm_RAFVIC_ECHL =
{
	4,
	{
		{	FT_200,ANGLES_240Deg,METRES00},
		{	FT_400,ANGLES_240Deg,METRES00},
		{	FT_600,ANGLES_240Deg,METRES00},
	}
},
//PASS1
VForm_RAFVIC_ECHR =
{
	4,
	{
		{	FT_200,ANGLES_120Deg,METRES00},
		{	FT_400,ANGLES_120Deg,METRES00},
		{	FT_600,ANGLES_120Deg,METRES00},
	}
},
//PASS1
VForm_RAFVIC_ABREST =
{
	4,
	{
		{	FT_200,ANGLES_90Deg,METRES00},
		{	FT_200,ANGLES_270Deg,METRES00},
		{	FT_400,ANGLES_90Deg,METRES00},
	}
},
//PASS1
VForm_RAFVIC_ASTERN =
{
	4,
	{
		{	FT_200,ANGLES_180Deg,METRES00},
		{	FT_400,ANGLES_180Deg,METRES00},
		{	FT_600,ANGLES_180Deg,METRES00},
	}
},
//Not using?
VForm_RAFVIC_DIAMOND =
{
	4,
	{
		{	FT_200,ANGLES_240Deg,METRES00},
		{	FT_200,ANGLES_120Deg,METRES00},
		{	FT_400,ANGLES_120Deg,METRES00},
	}
},
//Not using
VForm_RAFVIC_BOX =
{
	4,
	{
		{	FT_200,ANGLES_240Deg,METRES00},
		{	FT_200,ANGLES_120Deg,METRES00},
		{	FT_400,ANGLES_120Deg,METRES00},
	}
},
//PASS0 Not using
VForm_RAFVIC_WEAVE =
{
	4,
	{
		{	FT_200,ANGLES_240Deg,METRES00},
		{	FT_200,ANGLES_120Deg,METRES00},
		{	FT_400,ANGLES_120Deg,METRES00},
	}
},
//////////
//PASS3
VForm_LWVIC_VIC=
{
	5,
	{
//TempCode MS 11Jul00 		{	FT_300,ANGLES_120Deg,FT_50},
//TempCode MS 11Jul00 		{	FT_300,ANGLES_240Deg,FT_50},
//TempCode MS 11Jul00 		{	FT_600,ANGLES_120Deg,FT_100},
//TempCode MS 11Jul00 		{	FT_600,ANGLES_240Deg,FT_100},
		{	FT_450,ANGLES_120Deg,FT_50},
		{	FT_450,ANGLES_240Deg,FT_50},
		{	FT_900,ANGLES_120Deg,FT_100},
		{	FT_900,ANGLES_240Deg,FT_100},
	}
},
//PASS3		
VForm_LWVIC_ECHL=
{
	4,
	{
		{	FT_300,ANGLES_240Deg,FT_50},
		{	FT_600,ANGLES_240Deg,FT_100},
		{	FT_900,ANGLES_240Deg,FT_150},
	}
},
//PASS1
VForm_LWVIC_ECHR=
{
	4,
	{
		{	FT_300,ANGLES_120Deg,FT_50},
		{	FT_600,ANGLES_120Deg,FT_100},
		{	FT_900,ANGLES_120Deg,FT_150},
	}
},
//PASS1
VForm_LWVIC_ABREST=
{
	4,
	{
		{	FT_400,ANGLES_90Deg,FT_25},
		{	FT_400,ANGLES_270Deg,FT_25},
		{	FT_800,ANGLES_90Deg,FT_50},
	}
},
//PASS3		COMPLETE
VForm_LWVIC_ASTERN=
{
	4,
	{
		{	FT_300,ANGLES_180Deg,FT_50},
		{	FT_600,ANGLES_180Deg,FT_100},
		{	FT_900,ANGLES_180Deg,FT_150},
	}
},
//PASS3
VForm_LWVIC_DIAMOND=
{
	4,
	{
		{	FT_300,ANGLES_135Deg,FT_50},
		{	FT_300,ANGLES_225Deg,FT_50},
		{	FT_500,ANGLES_180Deg,FT_100},
	}
},
//PASS0
VForm_LWVIC_BOX=
{
	4,
	{	//JIM 22Feb100
		{	FT_400,ANGLES_90Deg,METRES00},
		{	FT_700,ANGLES_135Deg,METRES00},
		{	FT_500,ANGLES_180Deg,METRES00},
	}
},
//Not using
VForm_LWVIC_WEAVE=
{
	4,
	{
		{	FT_300,ANGLES_120Deg,FT_50},
		{	FT_300,ANGLES_240Deg,FT_50},
		{	FT_600,ANGLES_240Deg,FT_50},
	}
},

//FLAT 5 IS SUPPOSED TO BE A FLIGHT ARRANGED ABREAST. NOT GONNA USE THIS SO VIC FORMATIONS WILL BE COPIED IN

//PASS0
VForm_FLAT5_VIC=
{
	4,
	{
		{	FT_300,ANGLES_120Deg,0},
		{	FT_300,ANGLES_240Deg,0},
		{	FT_600,ANGLES_240Deg,0},
	}
},
//PASS0
VForm_FLAT5_ECHL=
{
	4,
	{
		{	FT_300,ANGLES_240Deg,METRES00},
		{	FT_600,ANGLES_240Deg,METRES00},
		{	FT_900,ANGLES_240Deg,METRES00},
	}
},
//PASS0
VForm_FLAT5_ECHR=
{
	4,
	{
		{	FT_300,ANGLES_120Deg,METRES00},
		{	FT_600,ANGLES_120Deg,METRES00},
		{	FT_900,ANGLES_120Deg,METRES00},
	}
},
//PASS0
VForm_FLAT5_ABREST=
{
	4,
	{
		{	FT_300,ANGLES_90Deg,METRES00},
		{	FT_300,ANGLES_270Deg,METRES00},
		{	FT_600,ANGLES_90Deg,METRES00},
	}
},
//PASS0
VForm_FLAT5_ASTERN=
{
	4,
	{
		{	FT_300,ANGLES_180Deg,FT_100},
		{	FT_600,ANGLES_180Deg,FT_200},
		{	FT_900,ANGLES_180Deg,FT_300},
	}
},
//PASS0
VForm_FLAT5_DIAMOND=
{
	4,
	{
		{	FT_300,ANGLES_120Deg,FT_50},
		{	FT_300,ANGLES_240Deg,FT_50},
		{	FT_600,ANGLES_240Deg,FT_50},
	}
},
//PASS0
VForm_FLAT5_BOX=
{
	4,
	{
		{	FT_500,ANGLES_90Deg,METRES00},
		{	FT_700,ANGLES_135Deg,METRES00},
		{	FT_500,ANGLES_180Deg,METRES00},
	}
},
//Not using
VForm_FLAT5_WEAVE=
{
	4,
	{
		{	FT_300,ANGLES_120Deg,FT_50},
		{	FT_300,ANGLES_240Deg,FT_50},
		{	FT_600,ANGLES_240Deg,FT_50},
	}
},
//PASS1
VForm_SCWARM_VIC=
{
	4,
	{
		{	FT_600,ANGLES_120Deg,METRES00},
		{	FT_600,ANGLES_240Deg,METRES00},
		{	FT_1200,ANGLES_240Deg,METRES00},
	}
},
//PASS1
VForm_SCWARM_ECHL=
{
	4,
	{
		{	FT_600,ANGLES_240Deg,METRES00},
		{	FT_1200,ANGLES_240Deg,METRES00},
		{	FT_1800,ANGLES_240Deg,METRES00},
	}
},
//PASS1
VForm_SCWARM_ECHR=
{
	4,
	{
		{	FT_600,ANGLES_120Deg,METRES00},
		{	FT_1200,ANGLES_120Deg,METRES00},
		{	FT_1800,ANGLES_120Deg,METRES00},
	}
},
//PASS1
VForm_SCWARM_ABREST=
{
	4,
	{
		{	FT_600,ANGLES_90Deg,METRES00},
		{	FT_600,ANGLES_270Deg,METRES00},
		{	FT_1200,ANGLES_270Deg,METRES00},
	}
},
//PASS1
VForm_SCWARM_ASTERN=
{
	4,
	{
		{	FT_600,ANGLES_180Deg,METRES00},
		{	FT_1200,ANGLES_180Deg,METRES00},
		{	FT_1800,ANGLES_180Deg,METRES00},
	}
},
//PASS0
VForm_SCWARM_DIAMOND=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//PASS0
VForm_SCWARM_BOX=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//Not using
VForm_SCWARM_WEAVE=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//PASS1
VForm_BSCRWARM_VIC=
{
	4,
	{
		{	FT_600,ANGLES_120Deg,METRES00},
		{	FT_600,ANGLES_240Deg,METRES00},
		{	FT_1200,ANGLES_240Deg,METRES00},
	}
},
//PASS1
VForm_BSCRWARM_ECHL=
{
	4,
	{
		{	FT_600,ANGLES_240Deg,METRES00},
		{	FT_1200,ANGLES_240Deg,METRES00},
		{	FT_1800,ANGLES_240Deg,METRES00},
	}
},
//PASS1
VForm_BSCRWARM_ECHR=
{
	4,
	{
		{	FT_600,ANGLES_120Deg,METRES00},
		{	FT_1200,ANGLES_120Deg,METRES00},
		{	FT_1800,ANGLES_120Deg,METRES00},
	}
},
//PASS1
VForm_BSCRWARM_ABREST=
{
	4,
	{
		{	FT_600,ANGLES_90Deg,METRES00},
		{	FT_600,ANGLES_270Deg,METRES00},
		{	FT_1200,ANGLES_270Deg,METRES00},
	}
},
//PASS1
VForm_BSCRWARM_ASTERN=
{
	4,
	{
		{	FT_600,ANGLES_180Deg,METRES00},
		{	FT_1200,ANGLES_180Deg,METRES00},
		{	FT_1800,ANGLES_180Deg,METRES00},
	}
},
//PASS0
VForm_BSCRWARM_DIAMOND=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//PASS0
VForm_BSCRWARM_BOX=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//Not using
VForm_BSCRWARM_WEAVE=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//PASS1
VForm_FINGER_VIC=
{
	4,
	{
		{	FT_500,ANGLES_120Deg,FT_100},
		{	FT_500,ANGLES_240Deg,FT_100},
		{	FT_1000,ANGLES_240Deg,FT_200},
	}
},
//PASS1
VForm_FINGER_ECHL=
{
	4,
	{
		{	FT_250,ANGLES_240Deg,METRES00},
		{	FT_500,ANGLES_240Deg,METRES00},
		{	FT_750,ANGLES_240Deg,METRES00},
	}
},
//PASS1
VForm_FINGER_ECHR=
{
	4,
	{
		{	FT_250,ANGLES_120Deg,METRES00},
		{	FT_500,ANGLES_120Deg,METRES00},
		{	FT_750,ANGLES_120Deg,METRES00},
	}
},
//PASS1
VForm_FINGER_ABREST=
{
	4,
	{
		{	FT_250,ANGLES_90Deg,METRES00},
		{	FT_250,ANGLES_270Deg,METRES00},
		{	FT_500,ANGLES_90Deg,METRES00},
	}
},
//PASS1
VForm_FINGER_ASTERN=
{
	4,
	{
		{	FT_250,ANGLES_180Deg,FT_100},
		{	FT_500,ANGLES_180Deg,FT_200},
		{	FT_750,ANGLES_180Deg,FT_300},
	}
},
//PASS0
VForm_FINGER_DIAMOND=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//PASS0
VForm_FINGER_BOX=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//Not using
VForm_FINGER_WEAVE=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_RAFTAIL_VIC=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_RAFTAIL_ECHL=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_RAFTAIL_ECHR=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_RAFTAIL_ABREST=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_RAFTAIL_ASTERN=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_RAFTAIL_DIAMOND=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_RAFTAIL_BOX=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_RAFTAIL_WEAVE=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_MAL_VIC=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_MAL_ECHL=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_MAL_ECHR=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_MAL_ABREST=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_MAL_ASTERN=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_MAL_DIAMOND=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_MAL_BOX=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//??
VForm_MAL_WEAVE=
{
	4,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
///////////////////////
//ignore wing type, 2 escort positions
//perhaps it would be better to ignore form type?
EForm_DEFVIC	=	//Default escort if a V of flights is as a vic, or astern
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,FT_200},
		{	FT_1000,ANGLES_240Deg,FT_200},
//TempCode MS 09Jun00 		{	FT_1500,ANGLES_180Deg,FT_300},
//TempCode MS 09Jun00 		{	FT_3000,ANGLES_180Deg,FT_600},
	}
},
EForm_DEFECHL	=	//Default for echelon left of flights is probably above and behind
{
	3,
	{
		{	FT_1000,ANGLES_240Deg,METRES00},
		{	FT_2000,ANGLES_240Deg,METRES00},
	}
},
EForm_DEFECHR=	//Default for echelon left of flights is probably above and behind
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_2000,ANGLES_120Deg,METRES00},
	}
},
EForm_DEFABREST=	//behind
{
	3,
	{
		{	FT_1000,ANGLES_270Deg,METRES00},
		{	FT_1000,ANGLES_90Deg,METRES00},
	}
},
EForm_DEFASTERN=	//abrest or further astern
{
	3,
	{
		{	FT_1000,ANGLES_180Deg,METRES50},
		{	FT_2000,ANGLES_180Deg,METRES100},
	}
},
EForm_DEFDIAMOND=	//v
{
	3,
	{
		{	FT_1000,ANGLES_135Deg,METRES200},
		{	FT_1000,ANGLES_325Deg,METRES200},
	}
},
EForm_DEFBOX=		//above/below to make a cube
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_DEFWEAVE	=	
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
//the following are primarily for fighter escort, although I do need to thread
//40 bomber in.
EForm_ASTERNVIC=
{
	3,
	{
		{	FT_1000,ANGLES_180Deg,FT_100},
		{	FT_2000,ANGLES_180Deg,FT_200},
//TempCode MS 25Oct00 		{	FT_1000,ANGLES_180Deg,0},
//TempCode MS 25Oct00 		{	FT_1000,ANGLES_0Deg,0},
	}
},
EForm_ASTERNECHL=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_ASTERNECHR=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_ASTERNABREST=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_ASTERNASTERN=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_LWV_A_A=
{
	3,
	{
		{	FT_1000,ANGLES_180Deg,METRES00},
		{	FT_2000,ANGLES_180Deg,METRES00},							//MS 16/03/00
	}
},

EForm_ASTERNDIAMOND=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_ASTERNBOX=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_ASTERNWEAVE	=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_ABRESTVIC=
{
	3,
	{
//TempCode MS 30May00 		{	FT_1000,ANGLES_120Deg,FT_300},
//TempCode MS 30May00 		{	FT_1000,ANGLES_240Deg,FT_300},
//DeadCode MS 19Jun00 		{	FT_1000,ANGLES_120Deg,FT_100},
//DeadCode MS 19Jun00 		{	FT_1000,ANGLES_240Deg,FT_100},
		{	FT_1000,ANGLES_90Deg,0},//FT_100},
		{	FT_1000,ANGLES_270Deg,0},//FT_100},
	}
},
EForm_ABRESTECHL=
{
	3,
	{
		{	FT_1000,ANGLES_240Deg,FT_400},
		{	FT_1000,ANGLES_240Deg,FT_400},
	}
},
EForm_ABRESTECHR=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,FT_400},
		{	FT_1000,ANGLES_240Deg,FT_400},
	}
},
EForm_ABRESTABREST=
{
	3,
	{
		{	FT_1000,ANGLES_270Deg,FT_400},
		{	FT_1000,ANGLES_90Deg,FT_400},
	}
},
EForm_ABRESTASTERN=
{
	3,
	{
		{	FT_1000,ANGLES_270Deg,FT_200},
		{	FT_1000,ANGLES_90Deg,FT_200},
	}
},
EForm_ABRESTDIAMOND=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_ABRESTBOX=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_ABRESTWEAVE	=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_ABOVEVIC=
{
	3,
	{
		{	FT_750,ANGLES_180Deg,FT_500},
		{	FT_1500,ANGLES_180Deg,FT_1000},
//TempCode MS 25Oct00 		{	FT_750,ANGLES_180Deg,FT_1000},
//TempCode MS 25Oct00 		{	FT_1500,ANGLES_180Deg,-FT_1000},
	}
},
EForm_ABOVEECHL=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_ABOVEECHR=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_ABOVEABREST=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_ABOVEASTERN=
{
	3,
	{
		{	FT_0,ANGLES_0Deg,FT_1000},
		{	FT_1000,ANGLES_180Deg,FT_1000},
	}
},
EForm_ABOVEDIAMOND=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_ABOVEBOX=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_ABOVEWEAVE=
{
	3,
	{
		{	FT_1000,ANGLES_120Deg,METRES00},
		{	FT_1000,ANGLES_240Deg,METRES00},
	}
},
EForm_MT_LEFTRIGHT=
{
	3,
	{
		{	METRES500,ANGLES_270Deg,FT_50},
		{	METRES500,ANGLES_90Deg,FT_50},
//TempCode MS 27Oct00 		{	FT_750,ANGLES_270Deg,FT_100},
//TempCode MS 27Oct00 		{	FT_750,ANGLES_90Deg,-FT_100},
	}
},
EForm_MT_BACKFRONT=
{
	3,
	{
		{	METRES500,ANGLES_180Deg,FT_50},
		{	METRES500,ANGLES_0Deg,FT_50},
	}
},
EForm_MT_ABOVEBELOW=
{
	3,
	{
		{	METRES100,ANGLES_180Deg,FT_1000},
		{	METRES100,ANGLES_0Deg,-FT_1000},
//TempCode MS 27Oct00 		{	METRES200,ANGLES_180Deg,FT_1000},
//TempCode MS 27Oct00 		{	METRES200,ANGLES_0Deg,-FT_1000},
	}
},
EForm_MT_LR_CLOSE=
{
	3,
	{
		{	METRES200,ANGLES_270Deg,FT_50},
		{	METRES200,ANGLES_90Deg,FT_50},
	}
},
EForm_MT_BF_CLOSE=
{
	3,
	{
		{	METRES200,ANGLES_180Deg,FT_50},
		{	METRES200,ANGLES_0Deg,FT_50},
	}
},
EForm_MT_AB_CLOSE=
{
	3,
	{
		{	METRES200,ANGLES_180Deg,FT_1000},
		{	METRES200,ANGLES_0Deg,-FT_1000},
	}
},
EForm_MT_LR_FAR=
{
	3,
	{
		{	METRES900,ANGLES_270Deg,FT_50},
		{	METRES900,ANGLES_90Deg,FT_50},
	}
},
EForm_MT_BF_FAR=
{
	3,
	{
		{	METRES800,ANGLES_180Deg,FT_50},
		{	METRES800,ANGLES_0Deg,FT_50},
	}
},
EForm_MT_AB_FAR=
{
	3,
	{
		{	METRES800,ANGLES_180Deg,FT_1000},
		{	METRES800,ANGLES_0Deg,-FT_1000},
	}
},
EForm_BRITVIC	=	
{
	3,
	{										//leader index is irrelivent  
		{	FT_750,ANGLES_110Deg,FT_200},	//index 0                     
		{	FT_750,ANGLES_250Deg,FT_200},	//index 1                     
	}
},
EForm_BRITVIC2	=	
{
	3,
	{										//leader index is irrelivent  
		{	FT_1500,ANGLES_110Deg,FT_400},	//index 0                     
		{	FT_1500,ANGLES_250Deg,FT_400},	//index 1                     
	}
},
EForm_BRITVIC3	=	
{
	3,
	{										//leader index is irrelivent  
		{	FT_500,ANGLES_180Deg,FT_400},	//index 0                     
		{	FT_1000,ANGLES_180Deg,FT_400},	//index 1                     
	}
},
EForm_BRITVIC4	=	
{
	3,
	{										//leader index is irrelivent  
		{	FT_1500,ANGLES_145Deg,FT_500},	//index 0                     
		{	FT_1500,ANGLES_235Deg,FT_500},	//index 1                     
	}
},
//DeadCode JIM 15Sep00 EForm_BRITASTERN=
//DeadCode JIM 15Sep00 {
//DeadCode JIM 15Sep00 	3,
//DeadCode JIM 15Sep00 	{
//DeadCode JIM 15Sep00 		{	FT_1000,ANGLES_180Deg,FT_100},
//DeadCode JIM 15Sep00 		{	FT_2000,ANGLES_180Deg,FT_200},
//DeadCode JIM 15Sep00 	}
//DeadCode JIM 15Sep00 },
//DeadCode JIM 15Sep00 EForm_BRITABREST=
//DeadCode JIM 15Sep00 {
//DeadCode JIM 15Sep00 	3,
//DeadCode JIM 15Sep00 	{											
//DeadCode JIM 15Sep00 		{	FT_1000,ANGLES_90Deg,FT_100},		
//DeadCode JIM 15Sep00 		{	FT_1000,ANGLES_270Deg,FT_100},		
//DeadCode JIM 15Sep00 	}
//DeadCode JIM 15Sep00 },
//DeadCode JIM 15Sep00 EForm_BRITABOVE=
//DeadCode JIM 15Sep00 {
//DeadCode JIM 15Sep00 	3,
//DeadCode JIM 15Sep00 	{
//DeadCode JIM 15Sep00 		{	FT_750,ANGLES_180Deg,FT_500},
//DeadCode JIM 15Sep00 		{	FT_1500,ANGLES_180Deg,FT_1000},
//DeadCode JIM 15Sep00 	}
//DeadCode JIM 15Sep00 },

///////////////////////
ENDLIST={0};

ExtFormationType	 
TakeOff_FormationWing=
{
	20435,
	{
		{	FT_188,ANGLES_95Deg,0},
		{	FT_188,ANGLES_265Deg,0},
		{	FT_375,ANGLES_95Deg,0},
		{	FT_375,ANGLES_265Deg,0},
//DEADCODE JIM 25/05/00 	},
//DEADCODE JIM 25/05/00 	{
		//Pairs
		{	FT_375,ANGLES_270Deg,0},
		{	FT_750,ANGLES_270Deg,0},
	}

},
TakeOff_FormationSquad=
{
	4,
	{
		{	FT_145,ANGLES_220Deg,0},
		{	FT_235,ANGLES_190Deg,0},
		{	FT_350,ANGLES_170Deg,0},
	}
},
TakeOff_RefuelSpots=
{
	4,
	{
		{	FT_345,ANGLES_155Deg},
		{	FT_310,ANGLES_205Deg},
		{	FT_205,ANGLES_245Deg},
		{	FT_105,ANGLES_120Deg}
	}
}

;
static ExtFormationType
Truck_VFormation=
{
	15,
	{
		{	FT_10,ANGLES_100Deg,0},
		{	FT_10,ANGLES_260Deg,0},
		{	FT_20,ANGLES_100Deg,0},
		{	FT_20,ANGLES_260Deg,0},
//DEADCODE JIM 25/05/00 	},
//DEADCODE JIM 25/05/00 	{
		{	FT_30,ANGLES_100Deg,0},
		{	FT_30,ANGLES_260Deg,0},
		{	FT_40,ANGLES_100Deg,0},
		{	FT_40,ANGLES_260Deg,0},
		{	FT_50,ANGLES_100Deg,0},
		{	FT_50,ANGLES_260Deg,0},
		{	FT_60,ANGLES_100Deg,0},
		{	FT_60,ANGLES_260Deg,0},
		{	FT_70,ANGLES_100Deg,0},
		{	FT_70,ANGLES_260Deg,0}
	}
	
	
},
Truck_LineFormation=
{
	15,
	{
		{	FT_50,ANGLES_180Deg,0},
		{	FT_100,ANGLES_180Deg,0},
		{	FT_150,ANGLES_180Deg,0},
		{	FT_200,ANGLES_180Deg,0},
//DEADCODE JIM 25/05/00 	},
//DEADCODE JIM 25/05/00 	{
		{	FT_250,ANGLES_180Deg,0},
		{	FT_300,ANGLES_180Deg,0},
		{	FT_350,ANGLES_180Deg,0},
		{	FT_400,ANGLES_180Deg,0},
		{	FT_450,ANGLES_180Deg,0},
		{	FT_500,ANGLES_180Deg,0},
		{	FT_550,ANGLES_180Deg,0},
		{	FT_600,ANGLES_180Deg,0},
		{	FT_650,ANGLES_180Deg,0},
		{	FT_700,ANGLES_180Deg,0},
	}
},
Ship_Formation1=
{
	15,
	{
//DeadCode MS 26Jun00 		{	FT_500,ANGLES_120Deg,0},
//DeadCode MS 26Jun00 		{	FT_500,ANGLES_225Deg,0},
//DeadCode MS 26Jun00 		{	FT_1000,ANGLES_180Deg,0},
//DeadCode MS 26Jun00 		{	FT_1500,ANGLES_160Deg,0},
//DeadCode MS 26Jun00 //DEADCODE JIM 25/05/00 	},
//DeadCode MS 26Jun00 //DEADCODE JIM 25/05/00 	{
//DeadCode MS 26Jun00 		{	FT_1500,ANGLES_210Deg,0},
//DeadCode MS 26Jun00 		{	FT_2000,ANGLES_180Deg,0},
//DeadCode MS 26Jun00 		{	FT_2500,ANGLES_170Deg,0},
//DeadCode MS 26Jun00 		{	FT_2500,ANGLES_190Deg,0},
//DeadCode MS 26Jun00 		{	FT_3000,ANGLES_180Deg,0},
//DeadCode MS 26Jun00 		{	FT_3500,ANGLES_180Deg,0},
//DeadCode MS 26Jun00 		{	FT_3500,ANGLES_175Deg,0},
//DeadCode MS 26Jun00 		{	FT_4000,ANGLES_180Deg,0},
//DeadCode MS 26Jun00 		{	FT_4000,ANGLES_175Deg,0},
//DeadCode MS 26Jun00 		{	FT_4300,ANGLES_180Deg,0}
		{	METRES500,ANGLES_140Deg,0},		//300,-400
		{	METRES550,ANGLES_220Deg,0},		//-300,-400
		{	METRES800,ANGLES_175Deg,0},		//50,-800
		{	METRES1250,ANGLES_165Deg,0},		//350,-1200
		{	METRES1250,ANGLES_195Deg,0},		//-350,-1200
		{	METRES1600,ANGLES_180Deg,0},		//-50,-1600
		{	METRES2000,ANGLES_170Deg,0},		//250,-2000
		{	METRES2050,ANGLES_190Deg,0},		//-400,-2000
		{	METRES2400,ANGLES_179Deg,0},		//100,-2400
		{	METRES2800,ANGLES_170Deg,0},		//400,-2800
		{	METRES2800,ANGLES_185Deg,0},		//-250,-2800
		{	METRES3200,ANGLES_179Deg,0},		//-100,-3200
		{	METRES3600,ANGLES_180Deg,0},
		{	METRES4000,ANGLES_180Deg,0}
	}
}

;
SingleFormation	Ground_Formations [] =
{
	&Truck_VFormation.formationtype,	
	&Truck_LineFormation.formationtype,	
	&Ship_Formation1.formationtype,
	&Truck_LineFormation.formationtype	
};


//the list here is matched to the flight list					//RDH 15Aug96
//MAXSQUAD_FORMS_NUM in missman.h needs to be updated			//RDH 18Aug96
SingleFormation	Aircraft_Formations [] =

	{	&Form_RAFVIC,
		&Form_LWVIC,
		&Form_FLAT5,
		&Form_SCWARM,
		&Form_BSCRWARM,
		&Form_FINGER,
		&Form_RAFTAIL,
		&Form_MAL
	};


//when a formation is added here, add an equate in flyinit.h
//the list here is matched to the squadron list					//RDH 15Aug96
//also MAXFLIGHT_FORMS_NUM in missman.h needs to be updated
SingleFormation	Squadron_Formations [] =
{
&VForm_RAFVIC_VIC,		&VForm_LWVIC_VIC,			&VForm_FLAT5_VIC,		&VForm_SCWARM_VIC,
	&VForm_BSCRWARM_VIC,		&VForm_FINGER_VIC,		&VForm_RAFTAIL_VIC,		&VForm_MAL_VIC,	
&VForm_RAFVIC_ECHL,		&VForm_LWVIC_ECHL,			&VForm_FLAT5_ECHL,		&VForm_SCWARM_ECHL,
	&VForm_BSCRWARM_ECHL,		&VForm_FINGER_ECHL,		&VForm_RAFTAIL_ECHL,	&VForm_MAL_ECHL,
&VForm_RAFVIC_ECHR,		&VForm_LWVIC_ECHR,			&VForm_FLAT5_ECHR,		&VForm_SCWARM_ECHR,
	&VForm_BSCRWARM_ECHR,		&VForm_FINGER_ECHR,		&VForm_RAFTAIL_ECHR,	&VForm_MAL_ECHR,
&VForm_RAFVIC_ABREST,	&VForm_LWVIC_ABREST,		&VForm_FLAT5_ABREST,	&VForm_SCWARM_ABREST,
	&VForm_BSCRWARM_ABREST,		&VForm_FINGER_ABREST,	&VForm_RAFTAIL_ABREST,	&VForm_MAL_ABREST,
&VForm_RAFVIC_ASTERN,	&VForm_LWVIC_ASTERN,		&VForm_FLAT5_ASTERN,	&VForm_SCWARM_ASTERN,
	&VForm_BSCRWARM_ASTERN,		&VForm_FINGER_ASTERN,	&VForm_RAFTAIL_ASTERN,	&VForm_MAL_ASTERN,
&VForm_RAFVIC_DIAMOND,	&VForm_LWVIC_DIAMOND,		&VForm_FLAT5_DIAMOND,	&VForm_SCWARM_DIAMOND,
	&VForm_BSCRWARM_DIAMOND,	&VForm_FINGER_DIAMOND,	&VForm_RAFTAIL_DIAMOND,	&VForm_MAL_DIAMOND,
&VForm_RAFVIC_BOX,		&VForm_LWVIC_BOX,			&VForm_FLAT5_BOX,		&VForm_SCWARM_BOX,
	&VForm_BSCRWARM_BOX,		&VForm_FINGER_BOX,		&VForm_RAFTAIL_BOX,		&VForm_MAL_BOX,	
&VForm_RAFVIC_WEAVE,	&VForm_LWVIC_WEAVE,			&VForm_FLAT5_WEAVE,		&VForm_SCWARM_WEAVE,
	&VForm_BSCRWARM_WEAVE,		&VForm_FINGER_WEAVE,	&VForm_RAFTAIL_WEAVE,	&VForm_MAL_WEAVE	
};

//
SingleFormation	Escort_Formations[]	= //Now 3dimensional
{	//Across index is FORMTYPE_WING
//FTI_DEFAULT//	FTW_RAFVIC				FTW_LWVIC				FTW_FLAT5				FTW_SCWARM				FTW_BSCRWARM			FTW_FINGER				FTW_RAFTAIL				FTW_MAL
/*FTS_VIC*/		&EForm_BRITVIC,			&EForm_DEFVIC, 			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			
/*FTS_ECHL*/	&EForm_BRITVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFECHL,			&EForm_DEFECHL,			&EForm_DEFECHL,			&EForm_DEFECHL,			&EForm_DEFECHL,			
/*FTS_ECHR*/	&EForm_BRITVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFECHR,			&EForm_DEFECHR,			&EForm_DEFECHR,			&EForm_DEFECHR,			&EForm_DEFECHR,			
/*FTS_ABREST*/	&EForm_BRITVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFABREST,		&EForm_DEFABREST,		&EForm_MT_LEFTRIGHT,	&EForm_DEFABREST,		&EForm_DEFABREST,		
/*FTS_ASTERN*/	&EForm_BRITVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFASTERN,		&EForm_DEFASTERN,		&EForm_MT_BACKFRONT,	&EForm_DEFASTERN,		&EForm_DEFASTERN,		
/*FTS_DIAMOND*/	&EForm_BRITVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFDIAMOND,		&EForm_DEFDIAMOND,		&EForm_DEFDIAMOND,		&EForm_DEFDIAMOND,		&EForm_DEFDIAMOND,		
/*FTS_BOX*/		&EForm_BRITVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFBOX,			&EForm_DEFBOX,			&EForm_DEFBOX,			&EForm_DEFBOX,			&EForm_DEFBOX,			
/*FTS_WEAVE*/	&EForm_BRITVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFWEAVE,		&EForm_DEFWEAVE,		&EForm_DEFWEAVE,		&EForm_DEFWEAVE,		&EForm_DEFWEAVE,		

//FTI_ASTERN//	FTW_RAFVIC				FTW_LWVIC				FTW_FLAT5				FTW_SCWARM				FTW_BSCRWARM			FTW_FINGER				FTW_RAFTAIL				FTW_MAL
/*FTS_VIC*/		&EForm_BRITVIC2,		&EForm_ASTERNVIC,		&EForm_ASTERNVIC,		&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_ASTERNVIC,		&EForm_ASTERNVIC,	
/*FTS_ECHL*/	&EForm_BRITVIC2,		&EForm_ASTERNVIC,		&EForm_ASTERNVIC,		&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_ASTERNECHL,		&EForm_ASTERNECHL,	
/*FTS_ECHR*/	&EForm_BRITVIC2,		&EForm_ASTERNVIC,		&EForm_ASTERNVIC,		&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_ASTERNECHR,		&EForm_ASTERNECHR,		
/*FTS_ABREST*/	&EForm_BRITVIC2,		&EForm_ASTERNVIC,		&EForm_ASTERNVIC,		&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_ASTERNABREST,	&EForm_ASTERNABREST,	
/*FTS_ASTERN*/	&EForm_BRITVIC2,		&EForm_ASTERNVIC,		&EForm_ASTERNVIC,		&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_ASTERNASTERN,	&EForm_ASTERNASTERN,	
/*FTS_DIAMOND*/	&EForm_BRITVIC2,		&EForm_ASTERNVIC,		&EForm_ASTERNVIC,		&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_ASTERNDIAMOND,	&EForm_ASTERNDIAMOND,	
/*FTS_BOX*/		&EForm_BRITVIC2,		&EForm_ASTERNVIC,		&EForm_ASTERNVIC,		&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_ASTERNBOX,		&EForm_ASTERNBOX,		
/*FTS_WEAVE*/	&EForm_BRITVIC2,		&EForm_ASTERNVIC,		&EForm_ASTERNVIC,		&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_MT_BACKFRONT,	&EForm_ASTERNWEAVE,		&EForm_ASTERNWEAVE,		

//FTI_ABREST//	FTW_RAFVIC				FTW_LWVIC				FTW_FLAT5				FTW_SCWARM				FTW_BSCRWARM			FTW_FINGER				FTW_RAFTAIL				FTW_MAL
/*FTS_VIC*/		&EForm_BRITVIC3,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		&EForm_MT_LR_FAR,		&EForm_MT_LR_FAR,		&EForm_MT_LR_FAR,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		
/*FTS_ECHL*/	&EForm_BRITVIC3,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		&EForm_MT_LR_FAR,   	&EForm_MT_LR_FAR,		&EForm_MT_LEFTRIGHT,	&EForm_ABRESTECHL,		&EForm_ABRESTECHL,		
/*FTS_ECHR*/	&EForm_BRITVIC3,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		&EForm_MT_LR_FAR,		&EForm_MT_LR_FAR,		&EForm_MT_LEFTRIGHT,	&EForm_ABRESTECHR,		&EForm_ABRESTECHR,		
/*FTS_ABREST*/	&EForm_BRITVIC3,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		&EForm_MT_LR_FAR,		&EForm_MT_LR_FAR,		&EForm_MT_LEFTRIGHT,	&EForm_ABRESTABREST,	&EForm_ABRESTABREST,	
/*FTS_ASTERN*/	&EForm_BRITVIC3,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		&EForm_MT_LEFTRIGHT,	&EForm_MT_LEFTRIGHT,	&EForm_MT_LEFTRIGHT,	&EForm_ABRESTASTERN,	&EForm_ABRESTASTERN,	
/*FTS_DIAMOND*/	&EForm_BRITVIC3,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		&EForm_MT_LR_FAR,		&EForm_MT_LR_FAR,		&EForm_MT_LEFTRIGHT,	&EForm_ABRESTDIAMOND,	&EForm_ABRESTDIAMOND,	
/*FTS_BOX*/		&EForm_BRITVIC3,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		&EForm_MT_LR_FAR,		&EForm_MT_LR_FAR,		&EForm_MT_LEFTRIGHT,	&EForm_ABRESTBOX,		&EForm_ABRESTBOX,		
/*FTS_WEAVE*/	&EForm_BRITVIC3,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		&EForm_MT_LR_FAR,		&EForm_MT_LR_FAR,		&EForm_MT_LEFTRIGHT,	&EForm_ABRESTWEAVE,		&EForm_ABRESTWEAVE,		

//FTI_ABOVE//	FTW_RAFVIC				FTW_LWVIC				FTW_FLAT5				FTW_SCWARM				FTW_BSCRWARM			FTW_FINGER				FTW_RAFTAIL				FTW_MAL
/*FTS_VIC*/		&EForm_BRITVIC4,		&EForm_ABOVEVIC,		&EForm_ABOVEVIC,		&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_ABOVEVIC,		&EForm_ABOVEVIC,	
/*FTS_ECHL*/	&EForm_BRITVIC4,		&EForm_ABOVEVIC,		&EForm_ABOVEVIC,		&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_ABOVEECHL,		&EForm_ABOVEECHL,		
/*FTS_ECHR*/	&EForm_BRITVIC4,		&EForm_ABOVEVIC,		&EForm_ABOVEVIC,		&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_ABOVEECHR,		&EForm_ABOVEECHR,		
/*FTS_ABREST*/	&EForm_BRITVIC4,		&EForm_ABOVEVIC,		&EForm_ABOVEVIC,		&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_ABOVEABREST,		&EForm_ABOVEABREST,		
/*FTS_ASTERN*/	&EForm_BRITVIC4,		&EForm_ABOVEVIC,		&EForm_ABOVEVIC,		&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_ABOVEASTERN,		&EForm_ABOVEASTERN,		
/*FTS_DIAMOND*/	&EForm_BRITVIC4,		&EForm_ABOVEVIC,		&EForm_ABOVEVIC,		&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_ABOVEDIAMOND,	&EForm_ABOVEDIAMOND,	
/*FTS_BOX*/		&EForm_BRITVIC4,		&EForm_ABOVEVIC,		&EForm_ABOVEVIC,		&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_ABOVEBOX,		&EForm_ABOVEBOX,		
/*FTS_WEAVE*/	&EForm_BRITVIC4,		&EForm_ABOVEVIC,		&EForm_ABOVEVIC,		&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_MT_ABOVEBELOW,	&EForm_ABOVEWEAVE,		&EForm_ABOVEWEAVE,		

//
//TempCode MS 30May00 SingleFormation	Escort_Formations[]	= //Now 3dimensional
//TempCode MS 30May00 {	//Across index is FORMTYPE_WING
//TempCode MS 30May00 //FTI_DEFAULT//FTW_RAFVIC			FTW_LWVIC				FTW_FLAT5				FTW_SCWARM				FTW_BSCRWARM			FTW_FINGER				FTW_RAFTAIL				FTW_MAL
//TempCode MS 30May00 /*FTS_VIC*/	&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			&EForm_DEFVIC,			
//TempCode MS 30May00 /*FTS_ECHL*/	&EForm_DEFECHL,			&EForm_DEFECHL,			&EForm_DEFECHL,			&EForm_DEFECHL,			&EForm_DEFECHL,			&EForm_DEFECHL,			&EForm_DEFECHL,			&EForm_DEFECHL,			
//TempCode MS 30May00 /*FTS_ECHR*/		&EForm_DEFECHR,			&EForm_DEFECHR,			&EForm_DEFECHR,			&EForm_DEFECHR,			&EForm_DEFECHR,			&EForm_DEFECHR,			&EForm_DEFECHR,			&EForm_DEFECHR,			
//TempCode MS 30May00 /*FTS_ABREST*/			&EForm_DEFABREST,		&EForm_DEFABREST,		&EForm_DEFABREST,		&EForm_DEFABREST,		&EForm_DEFABREST,		&EForm_DEFABREST,		&EForm_DEFABREST,		&EForm_DEFABREST,		
//TempCode MS 30May00 /*FTS_ASTERN*/				&EForm_DEFASTERN,		&EForm_DEFASTERN,		&EForm_DEFASTERN,		&EForm_DEFASTERN,		&EForm_DEFASTERN,		&EForm_DEFASTERN,		&EForm_DEFASTERN,		&EForm_DEFASTERN,		
//TempCode MS 30May00 /*FTS_DIAMOND*/					&EForm_DEFDIAMOND,		&EForm_DEFDIAMOND,		&EForm_DEFDIAMOND,		&EForm_DEFDIAMOND,		&EForm_DEFDIAMOND,		&EForm_DEFDIAMOND,		&EForm_DEFDIAMOND,		&EForm_DEFDIAMOND,		
//TempCode MS 30May00 /*FTS_BOX*/							&EForm_DEFBOX,			&EForm_DEFBOX,			&EForm_DEFBOX,			&EForm_DEFBOX,			&EForm_DEFBOX,			&EForm_DEFBOX,			&EForm_DEFBOX,			&EForm_DEFBOX,			
//TempCode MS 30May00 /*FTS_WEAVE*/							&EForm_DEFWEAVE,		&EForm_DEFWEAVE,		&EForm_DEFWEAVE,		&EForm_DEFWEAVE,		&EForm_DEFWEAVE,		&EForm_DEFWEAVE,		&EForm_DEFWEAVE,		&EForm_DEFWEAVE,		
//TempCode MS 30May00 
//TempCode MS 30May00 //FTI_ASTERN//FTW_RAFVIC			FTW_LWVIC				FTW_FLAT5				FTW_SCWARM				FTW_BSCRWARM			FTW_FINGER				FTW_RAFTAIL				FTW_MAL
//TempCode MS 30May00 /*FTS_VIC*/	&EForm_ASTERNVIC,		&EForm_ASTERNVIC,		&EForm_ASTERNVIC,		&EForm_ASTERNVIC,		&EForm_ASTERNVIC,		&EForm_ASTERNVIC,		&EForm_ASTERNVIC,		&EForm_ASTERNVIC,	
//TempCode MS 30May00 /*FTS_ECHL*/	&EForm_ASTERNECHL,		&EForm_ASTERNECHL,		&EForm_ASTERNECHL,		&EForm_ASTERNECHL,		&EForm_ASTERNECHL,		&EForm_ASTERNECHL,		&EForm_ASTERNECHL,		&EForm_ASTERNECHL,	
//TempCode MS 30May00 /*FTS_ECHR*/		&EForm_ASTERNECHR,		&EForm_ASTERNECHR,		&EForm_ASTERNECHR,		&EForm_ASTERNECHR,		&EForm_ASTERNECHR,		&EForm_ASTERNECHR,		&EForm_ASTERNECHR,		&EForm_ASTERNECHR,		
//TempCode MS 30May00 /*FTS_ABREST*/			&EForm_ASTERNABREST,	&EForm_ASTERNABREST,	&EForm_ASTERNABREST,	&EForm_ASTERNABREST,	&EForm_ASTERNABREST,	&EForm_ASTERNABREST,	&EForm_ASTERNABREST,	&EForm_ASTERNABREST,	
//TempCode MS 30May00 /*FTS_ASTERN*/				&EForm_ASTERNASTERN,	&EForm_LWV_A_A,			&EForm_ASTERNASTERN,	&EForm_ASTERNASTERN,	&EForm_ASTERNASTERN,	&EForm_ASTERNASTERN,	&EForm_ASTERNASTERN,	&EForm_ASTERNASTERN,	
//TempCode MS 30May00 /*FTS_DIAMOND*/					&EForm_ASTERNDIAMOND,	&EForm_ASTERNDIAMOND,	&EForm_ASTERNDIAMOND,	&EForm_ASTERNDIAMOND,	&EForm_ASTERNDIAMOND,	&EForm_ASTERNDIAMOND,	&EForm_ASTERNDIAMOND,	&EForm_ASTERNDIAMOND,	
//TempCode MS 30May00 /*FTS_BOX*/							&EForm_ASTERNBOX,		&EForm_ASTERNBOX,		&EForm_ASTERNBOX,		&EForm_ASTERNBOX,		&EForm_ASTERNBOX,		&EForm_ASTERNBOX,		&EForm_ASTERNBOX,		&EForm_ASTERNBOX,		
//TempCode MS 30May00 /*FTS_WEAVE*/							&EForm_ASTERNWEAVE,		&EForm_ASTERNWEAVE,		&EForm_ASTERNWEAVE,		&EForm_ASTERNWEAVE,		&EForm_ASTERNWEAVE,		&EForm_ASTERNWEAVE,		&EForm_ASTERNWEAVE,		&EForm_ASTERNWEAVE,		
//TempCode MS 30May00 
//TempCode MS 30May00 //FTI_ABREST//FTW_RAFVIC			FTW_LWVIC				FTW_FLAT5				FTW_SCWARM				FTW_BSCRWARM			FTW_FINGER				FTW_RAFTAIL				FTW_MAL
//TempCode MS 30May00 /*FTS_VIC*/	&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		&EForm_ABRESTVIC,		
//TempCode MS 30May00 /*FTS_ECHL*/	&EForm_ABRESTECHL,		&EForm_ABRESTECHL,		&EForm_ABRESTECHL,		&EForm_ABRESTECHL,		&EForm_ABRESTECHL,		&EForm_ABRESTECHL,		&EForm_ABRESTECHL,		&EForm_ABRESTECHL,		
//TempCode MS 30May00 /*FTS_ECHR*/		&EForm_ABRESTECHR,		&EForm_ABRESTECHR,		&EForm_ABRESTECHR,		&EForm_ABRESTECHR,		&EForm_ABRESTECHR,		&EForm_ABRESTECHR,		&EForm_ABRESTECHR,		&EForm_ABRESTECHR,		
//TempCode MS 30May00 /*FTS_ABREST*/			&EForm_ABRESTABREST,	&EForm_ABRESTABREST,	&EForm_ABRESTABREST,	&EForm_ABRESTABREST,	&EForm_ABRESTABREST,	&EForm_ABRESTABREST,	&EForm_ABRESTABREST,	&EForm_ABRESTABREST,	
//TempCode MS 30May00 /*FTS_ASTERN*/				&EForm_ABRESTASTERN,	&EForm_ABRESTASTERN,	&EForm_ABRESTASTERN,	&EForm_ABRESTASTERN,	&EForm_ABRESTASTERN,	&EForm_ABRESTASTERN,	&EForm_ABRESTASTERN,	&EForm_ABRESTASTERN,	
//TempCode MS 30May00 /*FTS_DIAMOND*/					&EForm_ABRESTDIAMOND,	&EForm_ABRESTDIAMOND,	&EForm_ABRESTDIAMOND,	&EForm_ABRESTDIAMOND,	&EForm_ABRESTDIAMOND,	&EForm_ABRESTDIAMOND,	&EForm_ABRESTDIAMOND,	&EForm_ABRESTDIAMOND,	
//TempCode MS 30May00 /*FTS_BOX*/							&EForm_ABRESTBOX,		&EForm_ABRESTBOX,		&EForm_ABRESTBOX,		&EForm_ABRESTBOX,		&EForm_ABRESTBOX,		&EForm_ABRESTBOX,		&EForm_ABRESTBOX,		&EForm_ABRESTBOX,		
//TempCode MS 30May00 /*FTS_WEAVE*/							&EForm_ABRESTWEAVE,		&EForm_ABRESTWEAVE,		&EForm_ABRESTWEAVE,		&EForm_ABRESTWEAVE,		&EForm_ABRESTWEAVE,		&EForm_ABRESTWEAVE,		&EForm_ABRESTWEAVE,		&EForm_ABRESTWEAVE,		
//TempCode MS 30May00 
//TempCode MS 30May00 //FTI_ABOVE//FTW_RAFVIC			FTW_LWVIC				FTW_FLAT5				FTW_SCWARM				FTW_BSCRWARM			FTW_FINGER				FTW_RAFTAIL				FTW_MAL
//TempCode MS 30May00 /*FTS_VIC*/	&EForm_ABOVEVIC,	&EForm_ABOVEVIC,	&EForm_ABOVEVIC,	&EForm_ABOVEVIC,	&EForm_ABOVEVIC,	&EForm_ABOVEVIC,	&EForm_ABOVEVIC,	&EForm_ABOVEVIC,	
//TempCode MS 30May00 /*FTS_ECHL*/	&EForm_ABOVEECHL,		&EForm_ABOVEECHL,		&EForm_ABOVEECHL,		&EForm_ABOVEECHL,		&EForm_ABOVEECHL,		&EForm_ABOVEECHL,		&EForm_ABOVEECHL,		&EForm_ABOVEECHL,		
//TempCode MS 30May00 /*FTS_ECHR*/		&EForm_ABOVEECHR,		&EForm_ABOVEECHR,		&EForm_ABOVEECHR,		&EForm_ABOVEECHR,		&EForm_ABOVEECHR,		&EForm_ABOVEECHR,		&EForm_ABOVEECHR,		&EForm_ABOVEECHR,		
//TempCode MS 30May00 /*FTS_ABREST*/			&EForm_ABOVEABREST,		&EForm_ABOVEABREST,		&EForm_ABOVEABREST,		&EForm_ABOVEABREST,		&EForm_ABOVEABREST,		&EForm_ABOVEABREST,		&EForm_ABOVEABREST,		&EForm_ABOVEABREST,		
//TempCode MS 30May00 /*FTS_ASTERN*/				&EForm_ABOVEASTERN,		&EForm_ABOVEASTERN,		&EForm_ABOVEASTERN,		&EForm_ABOVEASTERN,		&EForm_ABOVEASTERN,		&EForm_ABOVEASTERN,		&EForm_ABOVEASTERN,		&EForm_ABOVEASTERN,		
//TempCode MS 30May00 /*FTS_DIAMOND*/					&EForm_ABOVEDIAMOND,	&EForm_ABOVEDIAMOND,	&EForm_ABOVEDIAMOND,	&EForm_ABOVEDIAMOND,	&EForm_ABOVEDIAMOND,	&EForm_ABOVEDIAMOND,	&EForm_ABOVEDIAMOND,	&EForm_ABOVEDIAMOND,	
//TempCode MS 30May00 /*FTS_BOX*/							&EForm_ABOVEBOX,		&EForm_ABOVEBOX,		&EForm_ABOVEBOX,		&EForm_ABOVEBOX,		&EForm_ABOVEBOX,		&EForm_ABOVEBOX,		&EForm_ABOVEBOX,		&EForm_ABOVEBOX,		
//TempCode MS 30May00 /*FTS_WEAVE*/							&EForm_ABOVEWEAVE,		&EForm_ABOVEWEAVE,		&EForm_ABOVEWEAVE,		&EForm_ABOVEWEAVE,		&EForm_ABOVEWEAVE,		&EForm_ABOVEWEAVE,		&EForm_ABOVEWEAVE,		&EForm_ABOVEWEAVE,		
//TempCode MS 30May00 

};
FormationType*	GetEscortTable(FormationTypeIndex formationtype)
{
	int thisformationtype= (((formationtype&FORMTYPE_INTER)>>(FORMTYPE_INTER_SH-FORMTYPE_INTERCHILD_SH))+(formationtype&FORMTYPE_WINGSQUAD))>> FORMTYPE_WING_SH;
		FormationType* formtype=Escort_Formations [thisformationtype];
	return formtype;
}

//assume bomber cruise of 100 m/s
//delta: time, horiz, vert 
//POSITIVE delta time means arrive that much EARLY
static	
struct WayPointOffsetBigTable
{
	WayPointOffset	list;
#pragma warning( disable: 4200)
	WaypointOffsetSub	rest[];
#pragma warning( default: 4200)
}
WPO_ESCFLIGHT=
{{	{
	{0,0,						0},
	{0,0,						0+FT_500 },
	{0,0,						0+FT_1000},                   
	{0,METRES2000,				0},
	{0,METRES2000,				0+FT_500 },
	{0,METRES2000,				0+FT_1000},                   
	{0,-METRES2000,				0},	
	{0,-METRES2000,				0+FT_500 },
	{0,-METRES2000,				0+FT_1000}, 
	
	{-5*SECS100,0,				FT_500},
	{-5*SECS100,0,				FT_500+FT_500 },
	{-5*SECS100,0,				FT_500+FT_1000},              
	{-5*SECS100,METRES2000,				FT_500},
	{-5*SECS100,METRES2000,				FT_500+FT_500 },
	{-5*SECS100,METRES2000,				FT_500+FT_1000},      
	{-5*SECS100,-METRES2000,				FT_500},
}},
{
	{-5*SECS100,-METRES2000,				FT_500+FT_500 },
	{-5*SECS100,-METRES2000,				FT_500+FT_1000},  

	{-10*SECS100,0,				FT_1000},
	{-10*SECS100,0,				FT_1000+FT_500 },
	{-10*SECS100,0,				FT_1000+FT_1000},             
	{-10*SECS100,METRES2000,				FT_1000},
	{-10*SECS100,METRES2000,				FT_1000+FT_500 },
	{-10*SECS100,METRES2000,				FT_1000+FT_1000}, 
	{-10*SECS100,-METRES2000,				FT_1000},
	{-10*SECS100,-METRES2000,				FT_1000+FT_500 },
	{-10*SECS100,-METRES2000,				FT_1000+FT_1000}, 

	{-15*SECS100,0,				FT_1500},
	{-15*SECS100,0,				FT_1500+FT_500 },
	{-15*SECS100,0,				FT_1500+FT_1000},             
	{-15*SECS100,METRES2000,				FT_1500},
	{-15*SECS100,METRES2000,				FT_1500+FT_500 },
	{-15*SECS100,METRES2000,				FT_1500+FT_1000}, 
	{-15*SECS100,-METRES2000,				FT_1500},
	{-15*SECS100,-METRES2000,				FT_1500+FT_500 },
	{-15*SECS100,-METRES2000,				FT_1500+FT_1000}, 
													                                                                                                             
	{-20*SECS100,0,				FT_2000},
	{-20*SECS100,0,				FT_2000+FT_500 },
	{-20*SECS100,0,				FT_2000+FT_1000},             
	{-20*SECS100,METRES2000,				FT_2000},
	{-20*SECS100,METRES2000,				FT_2000+FT_500 },
	{-20*SECS100,METRES2000,				FT_2000+FT_1000}, 
	{-20*SECS100,-METRES2000,				FT_2000},
	{-20*SECS100,-METRES2000,				FT_2000+FT_500 },
	{-20*SECS100,-METRES2000,				FT_2000+FT_1000}, 

	{-25*SECS100,0,				FT_2500},
	{-25*SECS100,0,				FT_2500+FT_500 },
	{-25*SECS100,0,				FT_2500+FT_1000},             
	{-25*SECS100,METRES2000,				FT_2500},
	{-25*SECS100,METRES2000,				FT_2500+FT_500 },
	{-25*SECS100,METRES2000,				FT_2500+FT_1000},             
	{-25*SECS100,-METRES2000,				FT_2500},
	{-25*SECS100,-METRES2000,				FT_2500+FT_500 },
	{-25*SECS100,-METRES2000,				FT_2500+FT_1000},          
	{0,0,				FT_2500},	//64 entries
}};

//These guesses are off by 2 or 3 times.
//The 16 gruppen of bombers should be spread over at least 4km wide and 4km deep (@150m/s=25 seconds)
static	WayPointOffset
WPO_MAINFL=
{{
//TempCode MS 31May00 	{0,0,						0},
//TempCode MS 31May00 	{+10*SECS100,0,				-METRES50},
//TempCode MS 31May00 	{-10*SECS100,0,				METRES50},
//TempCode MS 31May00 	{-20*SECS100,METRES300,	METRES100},
//TempCode MS 31May00 	{-20*SECS100,-METRES300,	METRES100},
//TempCode MS 31May00 	{-30*SECS100,METRES500,	-METRES80},
//TempCode MS 31May00 	{-30*SECS100,METRES100,	-METRES80},
//TempCode MS 31May00 	{-30*SECS100,-METRES400,	-METRES80},
//TempCode MS 31May00 	{-30*SECS100,METRES900,	-METRES80},
//TempCode MS 31May00 	{-30*SECS100,-METRES900,	-METRES80},
//TempCode MS 31May00 	{-20*SECS100,METRES600,	METRES100},
//TempCode MS 31May00 	{-20*SECS100,-METRES600,	METRES100},
//TempCode MS 31May00 	{+10*SECS100,METRES1000,	-METRES50},
//TempCode MS 31May00 	{+10*SECS100,-METRES1000,	-METRES50},
//TempCode MS 31May00 	{-10*SECS100,METRES1000,	METRES50},
//TempCode MS 31May00 	{-10*SECS100,-METRES1000,	METRES50},

//TempCode MS 01Jun00 	{0,0,						0},
//TempCode MS 01Jun00 	{-5*SECS100,METRES1000,				FT_500},
//TempCode MS 01Jun00 	{-5*SECS100,-METRES1000,				FT_500},
//TempCode MS 01Jun00 	{-10*SECS100,0,				FT_1000},
//TempCode MS 01Jun00 	{-15*SECS100,METRES1000,				FT_1500},
//TempCode MS 01Jun00 	{-15*SECS100,-METRES1000,				FT_1500},
//TempCode MS 01Jun00 	{-20*SECS100,0,				FT_2000},
//TempCode MS 01Jun00 	{-25*SECS100,METRES1000,				FT_2500},
//TempCode MS 01Jun00 	{-25*SECS100,-METRES1000,				FT_2500},
//TempCode MS 01Jun00 	{-30*SECS100,0,				FT_3000},
//TempCode MS 01Jun00 	{-35*SECS100,METRES1000,				FT_3500},
//TempCode MS 01Jun00 	{-35*SECS100,-METRES1000,				FT_3500},
//TempCode MS 01Jun00 	{-40*SECS100,0,				FT_4000},
//TempCode MS 01Jun00 	{-45*SECS100,METRES1000,				FT_4000},
//TempCode MS 01Jun00 	{-45*SECS100,-METRES1000,				FT_4000},
//TempCode MS 01Jun00 	{-50*SECS100,0,				FT_5000},

//THIS IS THE ORIGINAL BEFORE I STARTED CHANGING!!!!
//TempCode MS 24Oct00 	{0,				0,						0},
//TempCode MS 24Oct00 	{0,				METRES2000,				0},
//TempCode MS 24Oct00 	{0,				-METRES2000,			0},
//TempCode MS 24Oct00 	{-5*SECS100,	0,						FT_500},
//TempCode MS 24Oct00 	{-5*SECS100,	METRES2000,				FT_500},
//TempCode MS 24Oct00 	{-5*SECS100,	-METRES2000,			FT_500},
//TempCode MS 24Oct00 	{-10*SECS100,	0,						FT_1000},
//TempCode MS 24Oct00 	{-10*SECS100,	METRES2000,				FT_1000},
//TempCode MS 24Oct00 	{-10*SECS100,	-METRES2000,			FT_1000},
//TempCode MS 24Oct00 	{-15*SECS100,	0,						FT_1500},
//TempCode MS 24Oct00 	{-15*SECS100,	METRES2000,				FT_1500},
//TempCode MS 24Oct00 	{-15*SECS100,	-METRES2000,			FT_1500},
//TempCode MS 24Oct00 	{-20*SECS100,	0,						FT_2000},
//TempCode MS 24Oct00 	{-20*SECS100,	METRES2000,				FT_2000},
//TempCode MS 24Oct00 	{-20*SECS100,	-METRES2000,			FT_2000},
//TempCode MS 24Oct00 	{-25*SECS100,	0,						FT_2500},

//DeadCode MS 24Oct00 	{0,				0,						0},
//DeadCode MS 24Oct00 	{-20*SECS100,	METRES500,				FT_500},
//DeadCode MS 24Oct00 	{-10*SECS100,	0,						FT_1000},
//DeadCode MS 24Oct00 	{-25*SECS100,	-METRES500,				FT_1500},
//DeadCode MS 24Oct00 	{-15*SECS100,	0,						FT_2000},
//DeadCode MS 24Oct00 	{-30*SECS100,	METRES500,				FT_2500},
//DeadCode MS 24Oct00 	{-20*SECS100,	0,						FT_2500},
//DeadCode MS 24Oct00 	{-35*SECS100,	-METRES500,				FT_2500},
//DeadCode MS 24Oct00 	{-25*SECS100,	0,						FT_2500},
//DeadCode MS 24Oct00 	{-40*SECS100,	METRES500,				FT_2500},
//DeadCode MS 24Oct00 	{-30*SECS100,	0,						FT_2500},
//DeadCode MS 24Oct00 	{-45*SECS100,	-METRES500,				FT_2500},
//DeadCode MS 24Oct00 	{-35*SECS100,	0,						FT_2500},
//DeadCode MS 24Oct00 	{-50*SECS100,	METRES500,				FT_2500},
//DeadCode MS 24Oct00 	{-40*SECS100,	0,						FT_2500},
//DeadCode MS 24Oct00 	{-55*SECS100,	-METRES500,				FT_2500},

//TempCode MS 25Oct00 	{0,				0,						0},
//TempCode MS 25Oct00 	{-10*SECS100,	0,						FT_500},
//TempCode MS 25Oct00 	{-20*SECS100,	0,						FT_1000},
//TempCode MS 25Oct00 	{-20*SECS100,	-METRES1000,			FT_500},
//TempCode MS 25Oct00 	{-30*SECS100,	-METRES1000,			FT_1000},
//TempCode MS 25Oct00 	{-40*SECS100,	-METRES1000,			FT_1500},
//TempCode MS 25Oct00 	{-30*SECS100,	METRES1000,				FT_500},
//TempCode MS 25Oct00 	{-40*SECS100,	METRES1000,				FT_1000},
//TempCode MS 25Oct00 	{-50*SECS100,	METRES1000,				FT_1500},
//TempCode MS 25Oct00 	{-60*SECS100,	0,						FT_1000},
//TempCode MS 25Oct00 	{-70*SECS100,	0,						FT_1500},
//TempCode MS 25Oct00 	{-80*SECS100,	0,						FT_2000},
//TempCode MS 25Oct00 	{-90*SECS100,	0,						FT_1500},
//TempCode MS 25Oct00 	{-100*SECS100,	0,						FT_2000},
//TempCode MS 25Oct00 	{-110*SECS100,	0,						FT_2500},
//TempCode MS 25Oct00 	{-120*SECS100,	0,						FT_3000},

//TempCode MS 25Oct00 	{0,				0,						0},
//TempCode MS 25Oct00 	{-5*SECS100,	0,						0},
//TempCode MS 25Oct00 	{-10*SECS100,	0,						0},
//TempCode MS 25Oct00 	{-15*SECS100,	0,						0},
//TempCode MS 25Oct00 	{-20*SECS100,	0,						0},
//TempCode MS 25Oct00 	{-25*SECS100,	0,						0},
//TempCode MS 25Oct00 	{-30*SECS100,	0,						0},
//TempCode MS 25Oct00 	{-35*SECS100,	0,						0},
//TempCode MS 25Oct00 	{-40*SECS100,	0,						0},
//TempCode MS 25Oct00 	{-45*SECS100,	0,						0},
//TempCode MS 25Oct00 	{-50*SECS100,	0,						0},
//TempCode MS 25Oct00 	{-55*SECS100,	0,						FT_5000},
//TempCode MS 25Oct00 	{-60*SECS100,	0,						FT_6000},
//TempCode MS 25Oct00 	{-65*SECS100,	0,						FT_6500},
//TempCode MS 25Oct00 	{-70*SECS100,	0,						FT_7000},
//TempCode MS 25Oct00 	{-75*SECS100,	0,						FT_7500},

//THIS IS A GOOD ONE

//TempCode MS 25Oct00 	{0,				0,						0},
//TempCode MS 25Oct00 	{-10*SECS100,	0,						FT_500},
//TempCode MS 25Oct00 	{-20*SECS100,	0,						FT_1000},
//TempCode MS 25Oct00 
//TempCode MS 25Oct00 	{-35*SECS100,	0,						FT_1000},
//TempCode MS 25Oct00 	{-45*SECS100,	0,						FT_1500},
//TempCode MS 25Oct00 	{-55*SECS100,	0,						FT_2000},
//TempCode MS 25Oct00 
//TempCode MS 25Oct00 	{-70*SECS100,	0,						FT_2000},
//TempCode MS 25Oct00 	{-80*SECS100,	0,						FT_2500},
//TempCode MS 25Oct00 	{-90*SECS100,	0,						FT_3000},
//TempCode MS 25Oct00 
//TempCode MS 25Oct00 	{-105*SECS100,	0,						FT_3000},
//TempCode MS 25Oct00 	{-115*SECS100,	0,						FT_3500},
//TempCode MS 25Oct00 	{-125*SECS100,	0,						FT_4000},
//TempCode MS 25Oct00 
//TempCode MS 25Oct00 	{-140*SECS100,	0,						FT_4000},
//TempCode MS 25Oct00 	{-150*SECS100,	0,						FT_4500},
//TempCode MS 25Oct00 	{-160*SECS100,	0,						FT_5000},
//TempCode MS 25Oct00 
//TempCode MS 25Oct00 	{-175*SECS100,	0,						FT_5000},

	{0,				0,						0},
	{-15*SECS100,	0,						FT_500},
	{-30*SECS100,	0,						FT_1000},

	{-50*SECS100,	0,						FT_1000},
	{-65*SECS100,	0,						FT_1500},
	{-80*SECS100,	0,						FT_2000},

	{-100*SECS100,	0,						FT_2000},
	{-115*SECS100,	0,						FT_2500},
	{-130*SECS100,	0,						FT_3000},

	{-150*SECS100,	0,						FT_3000},
	{-165*SECS100,	0,						FT_3500},
	{-180*SECS100,	0,						FT_4000},

	{-200*SECS100,	0,						FT_4000},
	{-215*SECS100,	0,						FT_4500},
	{-230*SECS100,	0,						FT_5000},

	{-250*SECS100,	0,						FT_5000},

//TempCode MS 02Jun00 	{0,0,						0},
//TempCode MS 02Jun00 	{0,METRES1000,				FT_500},
//TempCode MS 02Jun00 	{0,-METRES1000,				FT_500},
//TempCode MS 02Jun00 	{0,METRES2000,				FT_1000},
//TempCode MS 02Jun00 	{0,-METRES2000,				FT_1500},
//TempCode MS 02Jun00 	{0,METRES3000,				FT_1500},
//TempCode MS 02Jun00 	{0,-METRES3000,				FT_2000},
//TempCode MS 02Jun00 	{0,METRES4000,				FT_2500},
//TempCode MS 02Jun00 	{0,-METRES4000,				FT_2500},
//TempCode MS 02Jun00 	{0,METRES5000,				FT_3000},
//TempCode MS 02Jun00 	{0,-METRES5000,				FT_3500},
//TempCode MS 02Jun00 	{0,METRES6000,				FT_3500},
//TempCode MS 02Jun00 	{0,-METRES6000,				FT_4000},
//TempCode MS 02Jun00 	{0,METRES8000,				FT_4000},
//TempCode MS 02Jun00 	{0,-METRES8000,				FT_4000},
//TempCode MS 02Jun00 	{0,METRES8000,				FT_5000},

}},
WPO_RAF=
{{
	{0,0,0},
	{+10*SECS100,0,-METRES50},
	{-10*SECS100,0,METRES50},
	{-20*SECS100,METRES300,METRES100},
	{-20*SECS100,-METRES300,METRES100},
	{-30*SECS100,METRES500,-METRES80},
	{-30*SECS100,METRES100,-METRES80},
	{-30*SECS100,-METRES400,-METRES80},
	{-30*SECS100,METRES900,-METRES80},
	{-30*SECS100,-METRES900,-METRES80},
	{-20*SECS100,METRES600,METRES100},
	{-20*SECS100,-METRES600,METRES100},
	{+10*SECS100,METRES1000,-METRES50},
	{+10*SECS100,-METRES1000,-METRES50},
	{-10*SECS100,METRES1000,METRES50},
	{-10*SECS100,-METRES1000,METRES50},
}},
WPO_CEILING=
{{
	{0,0,						METRES5000},
	{+10*SECS100,0,				METRES5000},
	{-10*SECS100,0,				METRES5000},
	{-20*SECS100,METRES300,	METRES5000},
	{-20*SECS100,-METRES300,	METRES5000},
	{-30*SECS100,METRES500,	METRES5000},
	{-30*SECS100,METRES100,	METRES5000},
	{-30*SECS100,-METRES400,	METRES5000},
	{-30*SECS100,METRES900,	METRES5000},
	{-30*SECS100,-METRES900,	METRES5000},
	{-20*SECS100,METRES600,	METRES5000},
	{-20*SECS100,-METRES600,	METRES5000},
	{+10*SECS100,METRES1000,	METRES5000},
	{+10*SECS100,-METRES1000,	METRES5000},
	{-10*SECS100,METRES1000,	METRES5000},
	{-10*SECS100,-METRES1000,	METRES5000},
}},
WPO_HIGH=
{{
//TempCode MS 11Oct00 	{0,0,						METRES900},
//TempCode MS 11Oct00 	{+10*SECS100,0,				METRES900},
//TempCode MS 11Oct00 	{-10*SECS100,0,				METRES1000},
//TempCode MS 11Oct00 	{-20*SECS100,METRES300,	METRES1100},
//TempCode MS 11Oct00 	{-20*SECS100,-METRES300,	METRES1100},
//TempCode MS 11Oct00 	{-30*SECS100,METRES500,	METRES1000},
//TempCode MS 11Oct00 	{-30*SECS100,METRES100,	METRES1000},
//TempCode MS 11Oct00 	{-30*SECS100,-METRES400,	METRES1000},
//TempCode MS 11Oct00 	{-30*SECS100,METRES900,	METRES1200},
//TempCode MS 11Oct00 	{-30*SECS100,-METRES900,	METRES1200},
//TempCode MS 11Oct00 	{-20*SECS100,METRES600,	METRES1100},
//TempCode MS 11Oct00 	{-20*SECS100,-METRES600,	METRES1100},
//TempCode MS 11Oct00 	{+10*SECS100,METRES1000,	METRES1000},
//TempCode MS 11Oct00 	{+10*SECS100,-METRES1000,	METRES1000},
//TempCode MS 11Oct00 	{-10*SECS100,METRES1000,	METRES1000},
//TempCode MS 11Oct00 	{-10*SECS100,-METRES1000,	METRES1000},
	{0,0,						FT_10000},
	{-5*SECS100,0,				FT_10000},
	{-10*SECS100,0,				FT_10000},
	{-20*SECS100,METRES300,	METRES1100},
	{-20*SECS100,-METRES300,	METRES1100},
	{-30*SECS100,METRES500,	METRES1000},
	{-30*SECS100,METRES100,	METRES1000},
	{-30*SECS100,-METRES400,	METRES1000},
	{-30*SECS100,METRES900,	METRES1200},
	{-30*SECS100,-METRES900,	METRES1200},
	{-20*SECS100,METRES600,	METRES1100},
	{-20*SECS100,-METRES600,	METRES1100},
	{+10*SECS100,METRES1000,	METRES1000},
	{+10*SECS100,-METRES1000,	METRES1000},
	{-10*SECS100,METRES1000,	METRES1000},
	{-10*SECS100,-METRES1000,	METRES1000},

}},
WPO_FWDHIGH=
{{
	{200*SECS100,0,						METRES900},
	{210*SECS100,0,				METRES900},
	{200*SECS100,0,				METRES1000},
	{190*SECS100,METRES300,	METRES1100},
	{190*SECS100,-METRES300,	METRES1100},
	{180*SECS100,METRES500,	METRES1000},
	{180*SECS100,METRES100,	METRES1000},
	{180*SECS100,-METRES400,	METRES1000},
	{180*SECS100,METRES900,	METRES1200},
	{180*SECS100,-METRES900,	METRES1200},
	{190*SECS100,METRES600,	METRES1100},
	{190*SECS100,-METRES600,	METRES1100},
	{200*SECS100,METRES1000,	METRES1000},
	{200*SECS100,-METRES1000,	METRES1000},
	{210*SECS100,METRES1000,	METRES1000},
	{210*SECS100,-METRES1000,	METRES1000},
}},
WPO_FWDLVL=
{{
	{300*SECS100,0,						0},
	{310*SECS100,0,				-METRES50},
	{290*SECS100,0,				METRES50},
	{280*SECS100,METRES300,	METRES100},
	{280*SECS100,-METRES300,	METRES100},
	{270*SECS100,METRES500,	-METRES80},
	{270*SECS100,METRES100,	-METRES80},
	{270*SECS100,-METRES400,	-METRES80},
	{270*SECS100,METRES900,	-METRES80},
	{270*SECS100,-METRES900,	-METRES80},
	{280*SECS100,METRES600,	METRES100},
	{280*SECS100,-METRES600,	METRES100},
	{310*SECS100,METRES1000,	-METRES50},
	{310*SECS100,-METRES1000,	-METRES50},
	{290*SECS100,METRES1000,	METRES50},
	{290*SECS100,-METRES1000,	METRES50},
}},
WPO_FWDLOW=
{{
	{400*SECS100,0,						0-METRES300},
	{410*SECS100,0,				-METRES50-METRES300},
	{390*SECS100,0,				METRES50-METRES300},
	{380*SECS100,METRES300,	METRES100-METRES300},
	{380*SECS100,-METRES300,	METRES100-METRES300},
	{370*SECS100,METRES500,	-METRES80-METRES300},
	{370*SECS100,METRES100,	-METRES80-METRES300},
	{370*SECS100,-METRES400,	-METRES80-METRES300},
	{370*SECS100,METRES900,	-METRES80-METRES300},
	{370*SECS100,-METRES900,	-METRES80-METRES300},
	{380*SECS100,METRES600,	METRES100-METRES300},
	{380*SECS100,-METRES600,	METRES100-METRES300},
	{410*SECS100,METRES1000,	-METRES50-METRES300},
	{410*SECS100,-METRES1000,	-METRES50-METRES300},
	{390*SECS100,METRES1000,	METRES50-METRES300},
	{390*SECS100,-METRES1000,	METRES50-METRES300},
}},
WPO_LATE=
{{
	{-100*SECS100,0,						0},
	{-90*SECS100,0,				-METRES50},
	{-110*SECS100,0,				METRES50},
	{-120*SECS100,METRES300,	METRES100},
	{-120*SECS100,-METRES300,	METRES100},
	{-130*SECS100,METRES500,	-METRES80},
	{-130*SECS100,METRES100,	-METRES80},
	{-130*SECS100,-METRES400,	-METRES80},
	{-130*SECS100,METRES900,	-METRES80},
	{-130*SECS100,-METRES900,	-METRES80},
	{-120*SECS100,METRES600,	METRES100},
	{-120*SECS100,-METRES600,	METRES100},
	{-90*SECS100,METRES1000,	-METRES50},
	{-90*SECS100,-METRES1000,	-METRES50},
	{-110*SECS100,METRES1000,	METRES50},
	{-110*SECS100,-METRES1000,	METRES50},
}};
WayPointOffset		
WayPointOffsets_Escort=
{{	//A plus time means "ahead by"
	{0,+METRES10,0},				//FTIP_GRUPII	=	0x0000,
	{0,0,0},						//FTIP_GRUPIII&lead group=0x0040,
	{+10*SECS100,0,METRES10},		//FTIP_ASTERN	=	0x0080,	//escort positions and alternate formation
	{-10*SECS100,0,-METRES10},		//FTIP_AHEAD	=	0x00c0,	   
	{0,-METRES200,0},				//FTIP_LEFT	=	0x0100,
	{0,+METRES200,0},				//FTIP_RIGHT	=	0x0140,
	{0,0,+METRES50},				//FTIP_ABOVE	=	0x0180,
	{0,0,-METRES50},				//FTIP_BELOW	=	0x01c0,
}},

*WayPointOffsets_CourseSel[]=
{
	&WPO_MAINFL,
	&WPO_RAF	,
	&WPO_CEILING,
	&WPO_HIGH,
	&WPO_FWDHIGH,
	&WPO_FWDLVL,
	&WPO_FWDLOW,
	&WPO_LATE
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFollower_xyz
//Author		R. Hyde 
//Date			Mon 26 Feb 1996
//
//Description	Fills despos with desired location
//				THIS MUST BE BASED ON WING LEADER, NOT SQUAD LEADER//JIM 02Aug96
//				Otherwise, in 2 wings that are trying to come 
//				together the followers will stay loose.
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	//Want no effect to F86 which has 52 in this shape size field.
	//These sizes are too big for bigger bombers. Want to keep F86 the same
	//Was: 32K*52/ShpSize	- where shpsize for f86 is 52
	//The smaller the value, the wider spaced
	//Putting a minimum value of 32K/5 means a max spread of *5 ==> 250ft becomes 1200ft


void	formationitem::GetFollower_xyz (FormationTypeIndex	formationtype, FormationItemPtr leader)
{
	int formationpos = (formpos&InWingMAX) - 1;
	int thisformationtype= (formationtype&FORMTYPE_WINGSQUAD)>> FORMTYPE_WING_SH;
	FormationType* formtype=Ground_Formations [thisformationtype];

	if(leader == NULL)
	{
		leader=*this->leader;
//DEADCODE DAW 17/03/00 		if (!leader)
//DEADCODE DAW 17/03/00 			leader=AirStrucPtr(*this)->fly.leadelt();
	}
//DEADCODE DAW 17/03/00 	if (leader->follower==this && formationpos>0)
//DEADCODE DAW 17/03/00 	{
//DEADCODE DAW 17/03/00 		formationpos=formationpos/2+formtype->numentries-1;	//pilot3=formatoionpos2 ==>4
//DEADCODE DAW 17/03/00 	}
	Formation_xyz(leader->hdg,formtype,formationpos);
	despos += leader->World;
}

void	AirStruc::GetFollower_xyz (FormationTypeIndex	formationtype, AirStrucPtr leader)
{
	int formationpos = (formpos&InWingMAX) - 1;
	int thisformationtype= (formationtype&FORMTYPE_WING)>> FORMTYPE_WING_SH;
	FormationType* formtype=Aircraft_Formations [thisformationtype];

	if(leader == NULL)
	{
		leader=Leader();
		if (!leader)
			leader=this->fly.leadelt();
	}
	if (!Leader() && leader->follower==this && formationpos>1)			//AMM 16Aug00
	{
		formationpos=formationpos/2+(formtype->numentries%10)-2;	//pilot3=formatoionpos2 ==>4	//CSB 12Jul00
	}
	Formation_xyz(leader->hdg,formtype,formationpos);
	despos += leader->World;
}

//DEADCODE JIM 11/02/00 #define SIZEDIV32K(who)	((ANGLES_FRACT/5)+(ANGLES_FRACT*4*52/5)/SHAPESTUFF.GetShapePtr( who )->Size)
COORDS3D*	Item::Formation_xyz(ANGLES hdg,FormationType* formtype,int formindex)
{
	ANGLES	brg=hdg+formtype->wingpos [formindex].bearing;

	Float	sinbearing,cosbearing;
	Math_Lib.high_sin_cos(brg,sinbearing,cosbearing);
	SLong	range;
	range = formtype->wingpos [formindex].range;
	{
		despos.X = sinbearing*range;
		despos.Z = cosbearing*range;
		despos.Y = formtype->wingpos [formindex].delta_alt;
	}

	return &despos;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFlightLeader_xyz
//Author		R. Hyde 
//Date			Mon 26 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::GetFlightLeader_xyz (FormationTypeIndex	formationtype, FormationItemPtr leader)

{
	int formationpos = (formpos&InFormMAX) - 1;
	int thisformationtype= (formationtype&(FORMTYPE_WING+FORMTYPE_SQUAD))>> FORMTYPE_WING_SH;
	FormationType* formtype=Squadron_Formations [thisformationtype];

	if(leader == NULL)
	{
		leader=fly.leadflight;
	}
	Formation_xyz(leader->hdg,formtype,formationpos);
	despos += leader->World;
}

void AirStruc::GetEscort_xyz (FormationTypeIndex	formationtype, FormationItemPtr leader)

{
	int formationpos = (formationtype&(FORMTYPE_INTERCHILD))>> FORMTYPE_INTERCHILD_SH;
	FormationType* formtype=GetEscortTable(formationtype);

	if(leader == NULL)
	{
		leader=fly.leadflight;
	}
	Formation_xyz(leader->hdg,formtype,formationpos);
	despos += leader->World;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    GenWaypointOffsetSub
// Date:		19/07/00
// Author:		JIM
//
//Description: 	Sets up the waypoint arrival info for this flight
//
//////////////////////////////////////////////////////////////////////
void	AirStruc::GenWaypointOffsetSub(FormationTypeIndex formation,WaypointOffsetSub& wos,bool isescort)
{
	if (isescort)
	{	//Escorts that are not in formation use their own table:
		int courseselindex=((formation&FORMTYPE_COURSEPAIR)>>FORMTYPE_COURSESEL_SH);
		if (courseselindex>=48)
		{
			INT3;
			courseselindex&=31;
		}
		WaypointOffsetSub*	coursesel=WPO_ESCFLIGHT.list.members+courseselindex;
		WaypointOffsetSub*	escortsel=
			WayPointOffsets_Escort.members+((formation&FORMTYPE_INTERPAIR)>>FORMTYPE_INTERPAIR_SH);
		wos.deltahori=coursesel->deltahori+escortsel->deltahori;
		wos.deltatime=coursesel->deltatime+escortsel->deltatime;
		wos.deltavert=coursesel->deltavert+escortsel->deltavert;
	}
	else
	{
		WayPointOffset*		table=WayPointOffsets_CourseSel[(formation&FORMTYPE_COURSESEL)>>FORMTYPE_COURSESEL_SH];
		WaypointOffsetSub*	coursesel=table->members+((formation&FORMTYPE_COURSEPOS)>>FORMTYPE_COURSEPOS_SH);
		wos=*coursesel;
	}
}

