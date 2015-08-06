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
//Filename	missinit.cpp
//System
//Author	 R. Hyde
//Date		Thu 7 Dec 1995
//Description
//------------------------------------------------------------------------------
#include	"dosdefs.h"											//DAW 29Feb96
#define F_SOUNDS												//DAW 05Aug96
#define F_COMMON
#include	"files.g"		//NON-GRAPHICS FILES				//JIM 14May96
//DeadCode JIM 30Apr96 #include	"miss_man.h"										//DAW 17Jan96
//#include	"ui.h"
#include	"uniqueid.h"
//DEADCODE JIM 09/02/00 #include	"text.h"												//JIM 30Apr96
//TEMPCODE DAW 13/04/00 #include	"briefing.h"												//JIM 30Apr96
#include	"package.h"
#include	"missman2.h"	//special double-include
#undef	MISSMAN2_Included	//special double-include
#include	"missman2.h"	//special double-include
#include	"mytime.h"
#include	"mymath.h"											//RDH 04Jan96
#include	"ranges.h"											//RDH 04Jan96
#include	"node.h"
#include	"ENUMBITS.M"
#include "savegame.h"
#include "persons2.h"
#include	"sqddiary.h"
#include "nodebob.h"

Bool	beentomap;												//RDH 29Nov96
//DEADCODE DAW 29/01/00 MATHABLE	(Debrief::Types);
MATHABLE	(SquadSelect);
ATMOSPHERE&	MissManCampSky()	{return Miss_Man.camp.Sky;}
int	MissManDawnTime()			{return Miss_Man.camp.dawntime;}
int	MissManDuskTime()			{return Miss_Man.camp.dusktime;}
int	MissManSunSouth()			{return Miss_Man.camp.sunsouth;}


//enum repeated here because one in missman2.h wasn't accessed by this file?
enum					{MAX_FLIGHT_NUM = 4,MAX_AC_IN_FLIGHT_NUM = 4};
typedef	Profile	AM;
typedef	Profile		BR;
typedef Profile	SM;
typedef	Directives::LW::Targ	Flags;
startinst(CampaignPackages, CampaignConvoy_Def)
	/*garbage*/		sizeof(CampaignPackages),
	/*introsmack*/		FIL_VID_PHASE1BEGINS,
	/*IntroQuarterArt*/	FIL_NULL,
	
	/*playerhomebase*/	UID_AF_Abbeville,							//MS 06Apr99
	/*playertakeoff*/	UID_AF_Abbeville,							//MS 06Apr99
	/*firsttime*/	true,
	/*startdate, in secs +BASECENTURY, 1-5-17*/	JUL10th1940,
	/*ripdate, in secs +BASECENTURY, 1-5-17*/	JUL10th1940,
	/*currdate, in secs +BASECENTURY, 1-5-17*/	JUL10th1940,
	/*lastdate*/								AUG11th1940,

	/*currtime*/		MORNINGPERIODSTART,				//can only be the start time
	/*currperiodtime*/	MORNINGPERIODSTART,
	/*dawntime*/		HR06,
	/*dusktime*/		HR20,
	/*sunsouth*/		SUNELEVDIST,
	/*sl_category*/		1,												//RDH 01/03/00
	/*playerrank*/		SECLIEUTENANT,
	/*MoraleType*/		SKILL_REGULAR1,
	/*acesavail*/		0,
	/*reservesavail*/	12,
	/*currentplayerslot*/	0,
	/*name*/				"Name",
	/*aircraftname*/		"Silver Eagle",
	/*front*/				{UID_NULL},//UID_SdBlPyongtaek,UID_SdRdWonju,UID_StKangnung},//MS 06Apr99
	/*Directives::LW::HistTypes*/	Directives::LW::LWHISTORICALPHASE1A,
	/*Directives::RAF::HistTypes*/	Directives::RAF::HISTORICALSCENARIO_PHASE1,
	/*camp_win_anim*/	 FIL_NULL,
	/*camp_lost_anim*/	 FIL_NULL,
	/*directives*/
	{
		{//LW
			/*userprofiles*/	
			{
				{
					/*escortmethods*/		{0,4,32,32},		//MS 16Nov00
					/*acselectionrules*/	BR::BR_WIDESTPOSSIBLE,
//DeadCode MS 14Nov00 					/*formations*/			{FTS_BOX,FTS_BOX,FTS_BOX,FTS_BOX},	//4
					/*formations*/			{FTS_ASTERN, FTS_ASTERN, FTS_ASTERN, FTS_ASTERN},	//4
					/*bomberattackmethod*/	AM::AM_DECOYPATROL,
					/*bombers,attfighters,detfighters,retfighters*/
					12,12,12,0,
					/*NumTargets*/	1,
					/*mainalt*/	   FT_10000
				},
				{
					/*escortmethods*/		{0,4,32,32},		//MS 16Nov00
					/*acselectionrules*/	BR::BR_WIDESTPOSSIBLE,
//DeadCode MS 14Nov00 					/*formations*/			{FTS_ECHR,FTS_ECHR,FTS_ECHR,FTS_ECHR},	//4
					/*formations*/			{FTS_ASTERN, FTS_ASTERN, FTS_ASTERN, FTS_ASTERN},	//4
					/*bomberattackmethod*/	AM::AM_RECON,
					/*bombers,attfighters,detfighters,retfighters*/
					1,0,0,0,
					/*NumTargets*/		1,
					/*mainalt*/	   FT_15000

				},
				{
					/*escortmethods*/		{0,4,32,32},		//MS 16Nov00
					/*acselectionrules*/	BR::BR_WIDESTPOSSIBLE,
//DeadCode MS 14Nov00 					/*formations*/			{FTS_VIC,FTS_WEAVE,FTS_ABREST,FTS_DIAMOND},	//4
					/*formations*/			{FTS_ASTERN, FTS_ASTERN, FTS_ASTERN, FTS_ASTERN},	//4
					/*bomberattackmethod*/	AM::AM_LEVELBOMB,
					/*bombers,attfighters,detfighters,retfighters*/
					12,12,12,0,
					/*NumTargets*/	1,
					/*mainalt*/	   FT_15000

				}
			},
			/*current*/
			{
 				/*targetlines*/
				{		/*attached,detached, flags,			bombersperraid*/	/*acproportions*/
					{	0.0},
					
				},
				{0}
			},
			/*histdir*/
			{
				{//LWHISTORICALPHASE1A
//TempCode MS 30Aug00  						//targetlines 	
//TempCode MS 30Aug00 						{	/*attached,detached, flags,	  2ndtrg,	bombers*/		/*me109,me110, ju87, do17, ju88, he111,  */
//TempCode MS 30Aug00 /*RECON		*/				{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*CONVOYS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{1.0, 1.0, 1.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*LONDON	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 1.0, 1.0, 1.0}},
//TempCode MS 30Aug00 						},
//TempCode MS 30Aug00 						/*reconn*/			{0,0,false,false,PT_ME110},
//TempCode MS 30Aug00 						/*morningquota*/	0.3,
//TempCode MS 30Aug00 						/*middayquota*/		0.4,
//TempCode MS 30Aug00 						/*escortmethods*/	 {0},		//AM_HIGH
//TempCode MS 30Aug00 						/*arrivalminsseperation*/	15,		//2=coordinated;15 is consecutive.
//TempCode MS 30Aug00 						/*ju87*/			Directives::LW::JU_ANY,
//TempCode MS 30Aug00 						/*escort*/			0.50
 						//targetlines 	
						{	/*attached,detached, flags,	  2ndtrg,	bombers*/		/*me109,me110, ju87, do17, ju88, he111,  */
/*RECON		*/				{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{1.0, 1.0, 1.0, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 1.0, 1.0, 1.0}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.3,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},		//AM_HIGH
						/*arrivalminsseperation*/	15,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_ANY,
						/*escort*/			0.50
				},

				{//LWHISTORICALPHASE1B
 						/*targetlines*/
						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
/*RECON		*/				{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.2, 0.2, 0.2, 0.0, 0.0, 0.0}},
/*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.8, 0.8, 0.8, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 1.0, 1.0, 1.0}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.3,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},		//AM_HIGH
						/*arrivalminsseperation*/	15,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_ANY,
						/*escort*/			0.50
				},
				{//LWHISTORICALPHASE1C
 						/*targetlines*/
						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
/*RECON		*/				{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.5, 0.0, 0.0, 0.0, 0.0, 1.0}},
/*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.5, 0.0, 0.5, 0.0, 0.0}},
/*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.5, 0.5, 1.0, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.5, 0.0, 0.0}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.3,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},		//AM_HIGH
						/*arrivalminsseperation*/	15,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_ANY,
						/*escort*/			0.50
				},
				{//LWHISTORICALPHASE1D
 						/*targetlines*/
						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
/*RECON		*/				{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{1.0, 0.0, 0.6, 0.0, 0.0, 0.0}},
/*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.5, 0.0, 0.5, 0.0, 0.0}},
/*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.5, 0.4, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.3,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},		//AM_HIGH
						/*arrivalminsseperation*/	15,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_ANY,
						/*escort*/			0.50
				},
//TempCode MS 30Aug00 				{//LWHISTORICALPHASE2A
//TempCode MS 30Aug00  						/*targetlines*/
//TempCode MS 30Aug00 						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
//TempCode MS 30Aug00 /*RECON		*/				{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{1.0, 1.0, 1.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*CONVOYS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*LONDON	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 1.0, 1.0, 1.0}},
//TempCode MS 30Aug00 						},
//TempCode MS 30Aug00 						/*reconn*/			{0,0,false,false,PT_ME110},
//TempCode MS 30Aug00 						/*morningquota*/	0.3,
//TempCode MS 30Aug00 						/*middayquota*/		0.4,
//TempCode MS 30Aug00 						/*escortmethods*/	 {0},	//AM_CEILING
//TempCode MS 30Aug00 						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
//TempCode MS 30Aug00 						/*ju87*/			Directives::LW::JU_AM,
//TempCode MS 30Aug00 						/*escort*/			0.50
//TempCode MS 30Aug00 				},
//THIS ONE
				{//LWHISTORICALPHASE2A
 						/*targetlines*/
						{	/*attached,detached, flags,	secondarytrg,bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
/*RECON		*/				{	1.0, 0.0,	  Flags::NONE,0,	1,		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,		{0.3, 0.5, 0.5, 0.0, 0.0, 0.0}},
/*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,		{0.2, 0.0, 0.0, 0.0, 0.0, 0.2}},
/*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,		{0.3, 0.0, 0.5, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,		{0.4, 0.5, 0.0, 1.0, 1.0, 0.8}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.4,
						/*middayquota*/		0.3,
						/*escortmethods*/	 {0},	//AM_CEILING
						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_ANY,
						/*escort*/			0.50
				},

//DeadCode CSB 18Jul00 				{//LWHISTORICALPHASE2A
//DeadCode CSB 18Jul00  						/*targetlines*/
//DeadCode CSB 18Jul00 						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*//*me109,me110, ju87, do17, ju88, he111,  */
//DeadCode CSB 18Jul00 							{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//DeadCode CSB 18Jul00 							{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//DeadCode CSB 18Jul00 							{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//DeadCode CSB 18Jul00 							{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//DeadCode CSB 18Jul00 							{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//DeadCode CSB 18Jul00 							{	1.0, 0.0,	  Flags::NONE,0,	180,				{1.0, 1.0, 0.0, 1.0, 1.0, 1.0}},	//london
//DeadCode CSB 18Jul00 							{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//DeadCode CSB 18Jul00 							{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//DeadCode CSB 18Jul00 							{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 1.0, 0.0, 0.0, 0.0}},
//DeadCode CSB 18Jul00 						},
//DeadCode CSB 18Jul00 						/*reconn*/			{0,0,false,false,PT_ME110},
//DeadCode CSB 18Jul00 						/*morningquota*/	0.6,
//DeadCode CSB 18Jul00 						/*middayquota*/		0.4,
//DeadCode CSB 18Jul00 						/*escortmethods*/	 {0},	//AM_CEILING
//DeadCode CSB 18Jul00 						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
//DeadCode CSB 18Jul00 				},
//TempCode MS 30Aug00 				{//LWHISTORICALPHASE2B
//TempCode MS 30Aug00  						/*targetlines*/
//TempCode MS 30Aug00 						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
//TempCode MS 30Aug00 /*RECON		*/				{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,1,	30,			{0.5, 0.5, 0.0, 1.0, 1.0, 1.0}},
//TempCode MS 30Aug00 /*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.5, 0.5, 1.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*CONVOYS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*LONDON	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 /*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 30Aug00 						},
//TempCode MS 30Aug00 						/*reconn*/			{0,0,false,false,PT_ME110},
//TempCode MS 30Aug00 						/*morningquota*/	0.3,
//TempCode MS 30Aug00 						/*middayquota*/		0.4,
//TempCode MS 30Aug00 						/*escortmethods*/	 {0},	//AM_CEILING
//TempCode MS 30Aug00 						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
//TempCode MS 30Aug00 						/*ju87*/			Directives::LW::JU_AM,
//TempCode MS 30Aug00 						/*escort*/			0.50
//TempCode MS 30Aug00 				},
				{//LWHISTORICALPHASE2B
 						/*targetlines*/
						{	/*attached,detached, flags,	secondarytrg,bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
/*RECON		*/				{	1.0, 0.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	0.5, 0.5,	  Flags::NONE,0,	30,		{0.8, 0.5, 0.0, 1.0, 1.0, 0.5}},
/*DOCKS		*/				{	0.5, 0.5,	  Flags::NONE,0,	30,		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RADARS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,		{0.2, 0.5, 1.0, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	0.5, 0.5,	  Flags::NONE,0,	30,		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	0.5, 0.5,	  Flags::NONE,0,	30,		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*FACTORIES	*/				{	0.5, 0.5,	  Flags::NONE,0,	30,		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*SWEEPS	*/				{	0.5, 0.5,	  Flags::NONE,0,	30,		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RESTING	*/				{	0.5, 0.5,	  Flags::NONE,0,	30,		{0.0, 0.0, 0.0, 0.0, 0.0, 0.5}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.3,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},	//AM_CEILING
						/*arrivalminsseperation*/	8,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_ANY,
						/*escort*/			0.50
				},

				{//LWHISTORICALPHASE2C NOTUSED!!!!!!!!!!!!!!!!!!
 						/*targetlines*/
						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
/*RECON		*/				{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.5, 0.5, 0.0, 1.0, 1.0, 1.0}},
/*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.5, 0.5, 1.0, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.4,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},	//AM_CEILING
						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_AM,
						/*escort*/			0.50
				},
				{//LWHISTORICALPHASE2D	NOTUSED!!!!!!!!!!!!!!!!!!
 						/*targetlines*/
						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
	/*RECON		*/			{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
	/*AIRFIELDS	*/			{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.5, 0.5, 0.0, 1.0, 1.0, 1.0}},
	/*DOCKS		*/			{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
	/*RADARS	*/			{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.5, 0.5, 1.0, 0.0, 0.0, 0.0}},
	/*CONVOYS	*/			{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
	/*LONDON	*/			{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
	/*FACTORIES	*/			{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
	/*SWEEPS	*/			{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
	/*RESTING	*/			{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.4,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},	//AM_CEILING
						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_AM,
						/*escort*/			0.50
				},
				{//LWHISTORICALPHASE3A
//TempCode MS 28Aug00  						/*targetlines*/
//TempCode MS 28Aug00 						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
//TempCode MS 28Aug00 /*RECON		*/				{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 /*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{1.0, 1.0, 0.0, 1.0, 1.0, 1.0}},
//TempCode MS 28Aug00 /*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 /*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 /*CONVOYS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 /*LONDON	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 /*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 /*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 /*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 1.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 						},
//TempCode MS 28Aug00 						/*reconn*/			{0,0,false,false,PT_ME110},
//TempCode MS 28Aug00 						/*morningquota*/	0.4,
//TempCode MS 28Aug00 						/*middayquota*/		0.4,
//TempCode MS 28Aug00 						/*escortmethods*/	 {0},	//AM_CEILING
//TempCode MS 28Aug00 						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
//TempCode MS 28Aug00 						/*ju87*/			Directives::LW::JU_AM,
//TempCode MS 28Aug00 						/*escort*/			0.50
 						/*targetlines*/
						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
/*RECON		*/				{	1.0, 0.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	1.0, 0.0,	  Flags::NONE,1,	30,					{0.9, 1.0, 0.0, 1.0, 0.7, 1.0}},
/*DOCKS		*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RADARS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*FACTORIES	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.1, 0.0, 0.0, 0.0, 0.2, 0.0}},
/*SWEEPS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RESTING	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 1.0, 0.0, 0.0, 0.0}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.2,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},	//AM_CEILING
						/*arrivalminsseperation*/	8,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_NONE,
						/*escort*/			0.50
				},
//TempCode MS 11Sep00 				{//LWHISTORICALPHASE3B
//TempCode MS 11Sep00  						/*targetlines*/
//TempCode MS 11Sep00 						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
//TempCode MS 11Sep00 /*RECON		*/				{	1.0, 0.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 11Sep00 /*AIRFIELDS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.8, 0.8, 0.0, 1.0, 1.0, 1.0}},
//TempCode MS 11Sep00 /*DOCKS		*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 11Sep00 /*RADARS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 1.0, 0.0, 0.0, 0.0}},
//TempCode MS 11Sep00 /*CONVOYS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 11Sep00 /*LONDON	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 11Sep00 /*FACTORIES	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 11Sep00 /*SWEEPS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 11Sep00 /*RESTING	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 11Sep00 						},
//TempCode MS 11Sep00 						/*reconn*/			{0,0,false,false,PT_ME110},
//TempCode MS 11Sep00 						/*morningquota*/	0.4,
//TempCode MS 11Sep00 						/*middayquota*/		0.4,
//TempCode MS 11Sep00 						/*escortmethods*/	 {0},	//AM_CEILING
//TempCode MS 11Sep00 						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
//TempCode MS 11Sep00 						/*ju87*/			Directives::LW::JU_AM,
//TempCode MS 11Sep00 						/*escort*/			0.50
//TempCode MS 11Sep00 				},
				{//LWHISTORICALPHASE3B
 						/*targetlines*/
						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
/*RECON		*/				{	1.0, 0.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	1.0, 0.0,	  Flags::NONE,1,	30,					{1.0, 0.5, 0.0, 1.0, 1.0, 1.0}},
/*DOCKS		*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RADARS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.5, 1.0, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*FACTORIES	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*SWEEPS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RESTING	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.2,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},	//AM_CEILING
						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_AM,
						/*escort*/			0.50
				},
				{//LWHISTORICALPHASE3C
 						/*targetlines*/
						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
/*RECON		*/				{	1.0, 0.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	1.0, 0.0,	  Flags::NONE,0,	40,					{0.0, 1.0, 0.0, 0.0, 0.0, 0.5}},	
/*DOCKS		*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RADARS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*FACTORIES	*/				{	1.0, 0.0,	  Flags::NONE,0,	40,					{1.0, 0.0, 0.0, 1.0, 1.0, 0.5}},
/*SWEEPS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0  , 0  , 0  , 0  , 0  , 0  }},	
/*RESTING	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 1.0, 0.0, 0.0, 0.0}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.4,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},	//AM_CEILING
						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_NONE,
						/*escort*/			0.50
				},
				{//LWHISTORICALPHASE3D !!!!!!!!!!!!!!!!not used!!!!!!!!!!!!!!!!!!!!
 						/*targetlines*/
						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
/*RECON		*/				{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{1.0, 1.0, 1.0, 1.0, 1.0, 1.0}},
/*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.4,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},	//AM_CEILING
						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_AM,
						/*escort*/			0.50
				},
				{//LWHISTORICALPHASE4A
 						/*targetlines*/
						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
//TempCode MS 28Aug00 /*RECON		*/				{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 /*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 /*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 /*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 /*CONVOYS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 /*LONDON	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{1.0, 1.0, 0.0, 1.0, 1.0, 1.0}},
//TempCode MS 28Aug00 /*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 /*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//TempCode MS 28Aug00 /*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 1.0, 0.0, 0.0, 0.0}},
/*RECON		*/				{	1.0, 0.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*DOCKS		*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RADARS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	1.0, 0.0,	  Flags::NONE,3,	30,					{1.0, 1.0, 0.0, 1.0, 1.0, 1.0}},
/*FACTORIES	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*SWEEPS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RESTING	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 1.0, 0.0, 0.0, 0.0}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.2,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},	//AM_CEILING
						/*arrivalminsseperation*/	8,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_NONE,
						/*escort*/			0.50
				},
				{//LWHISTORICALPHASE4B	 //use for sep 15th
//DeadCode RDH 12Oct00  						/*targetlines*/
//DeadCode RDH 12Oct00 						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
//DeadCode RDH 12Oct00 /*RECON		*/				{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//DeadCode RDH 12Oct00 /*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//DeadCode RDH 12Oct00 /*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//DeadCode RDH 12Oct00 /*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//DeadCode RDH 12Oct00 /*CONVOYS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//DeadCode RDH 12Oct00 /*LONDON	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{1.0, 1.0, 0.0, 1.0, 1.0, 1.0}},
//DeadCode RDH 12Oct00 /*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//DeadCode RDH 12Oct00 /*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
//DeadCode RDH 12Oct00 /*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 1.0, 0.0, 0.0, 0.0}},
//DeadCode RDH 12Oct00 						},
//DeadCode RDH 12Oct00 						/*reconn*/			{0,0,false,false,PT_ME110},
//DeadCode RDH 12Oct00 						/*morningquota*/	0.4,
//DeadCode RDH 12Oct00 						/*middayquota*/		0.4,
//DeadCode RDH 12Oct00 						/*escortmethods*/	 {0},	//AM_CEILING
//DeadCode RDH 12Oct00 						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
//DeadCode RDH 12Oct00 						/*ju87*/			Directives::LW::JU_NONE,
//DeadCode RDH 12Oct00 						/*escort*/			0.50
 						/*targetlines*/
						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
/*RECON		*/				{	1.0, 0.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*DOCKS		*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RADARS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	1.0, 0.0,	  Flags::NONE,5,	30,					{1.0, 1.0, 0.0, 1.0, 1.0, 1.0}},
/*FACTORIES	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*SWEEPS	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RESTING	*/				{	1.0, 0.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 1.0, 0.0, 0.0, 0.0}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.1,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},	//AM_CEILING
						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_NONE,
						/*escort*/			0.50
				},
				{//LWHISTORICALPHASE4C	!!!not used!!!
 						/*targetlines*/
						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
/*RECON		*/				{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{1.0, 1.0, 0.0, 1.0, 1.0, 1.0}},
/*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 1.0, 0.0, 0.0, 0.0}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.4,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},	//AM_CEILING
						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_NONE,
						/*escort*/			0.50
				},
				{//LWHISTORICALPHASE4D	!!!not used!!!
 						/*targetlines*/
						{	/*attached,detached, flags,			secondarytrg,			bombersperraid*/		/*me109,me110, ju87, do17, ju88, he111,  */
/*RECON		*/				{	0.0, 1.0,	  Flags::NONE,0,	1,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*AIRFIELDS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*DOCKS		*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RADARS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*CONVOYS	*/				{	0.0, 1.0,	  Flags::FIGHTERSSTRAFFE,0,	30,			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*LONDON	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{1.0, 1.0, 0.0, 1.0, 1.0, 1.0}},
/*FACTORIES	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*SWEEPS	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
/*RESTING	*/				{	0.0, 1.0,	  Flags::NONE,0,	30,					{0.0, 0.0, 1.0, 0.0, 0.0, 0.0}},
						},
						/*reconn*/			{0,0,false,false,PT_ME110},
						/*morningquota*/	0.4,
						/*middayquota*/		0.4,
						/*escortmethods*/	 {0},	//AM_CEILING
						/*arrivalminsseperation*/	2,		//2=coordinated;15 is consecutive.
						/*ju87*/			Directives::LW::JU_NONE,
						/*escort*/			0.50
				},
				},
		},
 		{//RAF
			{/*userprofiles*/
				{//PATROL
						/*acselectionrules*/ BR::BR_B_ANYRAF,
						/*packageattackmethod*/		 AM::AM_PATROL,
						/*mainalt*/			 FT_15000,
					{//hurr
						/*numac*/			0,
						/*what*/			SM::SM_NOTFIGHTERS,
						/*formation*/		FTW_RAFVIC
					},
					{//spit
						/*numac*/			6,
						/*what*/			SM::SM_NOTBOMBERS,
						/*formation*/		FTW_RAFVIC
					},
				},
				{//ANTISWEEP
						/*acselectionrules*/ BR::BR_B_ANYRAF,
						/*packageattackmethod*/		 AM::AM_INTERCEPT,
						/*mainalt*/			 FT_15000,
					{//hurr
						/*numac*/			0,
						/*what*/			SM::SM_NOTFIGHTERS,
						/*formation*/		FTW_RAFVIC
					},
					{//spit
						/*numac*/			12,
						/*what*/			SM::SM_NOTBOMBERS,
						/*formation*/		FTW_RAFVIC
					},
				},
				{//ANTISINGLE
						/*acselectionrules*/ BR::BR_B_ANYRAF,
						/*packageattackmethod*/		 AM::AM_INTERCEPT,
						/*mainalt*/			 FT_15000,
					{//hurr
						/*numac*/			3,
						/*what*/			SM::SM_NOTFIGHTERS,
						/*formation*/		FTW_RAFVIC
					},
					{//spit
						/*numac*/			0,
						/*what*/			SM::SM_NOTBOMBERS,
						/*formation*/		FTW_RAFVIC
					},
				},
				{//ANTIUNESC
						/*acselectionrules*/ BR::BR_B_ANYRAF,
						/*packageattackmethod*/		 AM::AM_INTERCEPT,
						/*mainalt*/			 FT_15000,
					{//hurr
						/*numac*/			12,
						/*what*/			SM::SM_NOTFIGHTERS,
						/*formation*/		FTW_RAFVIC
					},
					{//spit
						/*numac*/			0,
						/*what*/			SM::SM_NOTBOMBERS,
						/*formation*/		FTW_RAFVIC
					},
				},
				{//ANTIESC
						/*acselectionrules*/ BR::BR_B_ANYRAF,
						/*packageattackmethod*/		 AM::AM_INTERCEPT,
						/*mainalt*/			 FT_15000,
					{//hurr
						/*numac*/			12,
						/*what*/			SM::SM_NOTFIGHTERS,
						/*formation*/		FTW_RAFVIC
					},
					{//spit
						/*numac*/			0,	//12			//MS 12Nov00
						/*what*/			SM::SM_NOTBOMBERS,
						/*formation*/		FTW_RAFVIC
					},
			},
//TempCode MS 28Oct00 //WARNING - THIS IS A TEST
//TempCode MS 28Oct00 				{//ANTIESC
//TempCode MS 28Oct00 						/*acselectionrules*/ BR::BR_B_ANYRAF,
//TempCode MS 28Oct00 						/*packageattackmethod*/		 AM::AM_INTERCEPT,
//TempCode MS 28Oct00 						/*mainalt*/			 FT_17000,
//TempCode MS 28Oct00 					{//hurr
//TempCode MS 28Oct00 						/*numac*/			12,
//TempCode MS 28Oct00 						/*what*/			SM::SM_NOTFIGHTERS,
//TempCode MS 28Oct00 						/*formation*/		FTW_RAFVIC
//TempCode MS 28Oct00 					},
//TempCode MS 28Oct00 					{//spit
//TempCode MS 28Oct00 						/*numac*/			0,
//TempCode MS 28Oct00 						/*what*/			SM::SM_NOTBOMBERS,
//TempCode MS 28Oct00 						/*formation*/		FTW_RAFVIC
//TempCode MS 28Oct00 					},
//TempCode MS 28Oct00 				},
				{//ANTIBIG
						/*acselectionrules*/ BR::BR_B_ANYRAF,
						/*packageattackmethod*/		 AM::AM_INTERCEPT,
						/*mainalt*/			 FT_15000,
					{//hurr
//TempCode MS 28Aug00 						/*numac*/			12,
						/*numac*/			12,		//36,		//MS 12Nov00
						/*what*/			SM::SM_NOTFIGHTERS,
						/*formation*/		FTW_RAFVIC
					},
					{//spit
//TempCode MS 28Aug00 						/*numac*/			12,
						/*numac*/			0,		//24,		//MS 12Nov00
						/*what*/			SM::SM_NOTBOMBERS,
						/*formation*/		FTW_RAFVIC
					},
				},
//TempCode MS 28Oct00 //WARNING - THIS IS A TEST
//TempCode MS 28Oct00 				{//ANTIBIG
//TempCode MS 28Oct00 						/*acselectionrules*/ BR::BR_B_ANYRAF,
//TempCode MS 28Oct00 						/*packageattackmethod*/		 AM::AM_INTERCEPT,
//TempCode MS 28Oct00 						/*mainalt*/			 FT_17000,
//TempCode MS 28Oct00 					{//hurr
//TempCode MS 28Oct00 						/*numac*/			12,
//TempCode MS 28Oct00 						/*what*/			SM::SM_NOTFIGHTERS,
//TempCode MS 28Oct00 						/*formation*/		FTW_RAFVIC
//TempCode MS 28Oct00 					},
//TempCode MS 28Oct00 					{//spit
//TempCode MS 28Oct00 						/*numac*/			0,
//TempCode MS 28Oct00 						/*what*/			SM::SM_NOTBOMBERS,
//TempCode MS 28Oct00 						/*formation*/		FTW_RAFVIC
//TempCode MS 28Oct00 					},
//TempCode MS 28Oct00 				},
			},	
			{/*current*/
				/*sanctioned*/												Directives::RAF::MTB_ANTIALL-Directives::RAF::MTB_ANTISWEEP,
				/*approach*/												AM::AM_INTERCEPT,
				/*restifcatbelow,restifavailbelow*/							2,6,
				/*gr11radarpatrol,gr11convoypatrol,gr11coastalpatrol*/		0.3,0.1,0.0,
				/*gr1012afpat,gr1012acfactpat,gr1012supfactpat*/			0.3,0.0,0.0,
				/*convoylevel*/												1.0,
				/*interceptbeforetarget*/									true,
				/*unitsize*/												Directives::RAF::Dir::ONESQ,
			},
			{
				{/*HISTORICALSCENARIO_PHASE1*/
					/*sanctioned*/												Directives::RAF::MTB_ANTIALL-Directives::RAF::MTB_ANTISWEEP,
					/*approach*/												AM::AM_INTERCEPT,
					/*restifcatbelow,restifavailbelow*/							2,6,
					/*gr11radarpatrol,gr11convoypatrol,gr11coastalpatrol*/		0.0,0.3,0.0,//MS 12Nov00
					/*gr1012afpat,gr1012acfactpat,gr1012supfactpat*/			0.0,0.0,0.0,//MS 12Nov00
					/*convoylevel*/												1.0,
					/*interceptbeforetarget*/									true,
					/*unitsize*/												Directives::RAF::Dir::ONESQ,
				},
				{/*HISTORICALSCENARIO_PHASE2*/
					/*sanctioned*/												Directives::RAF::MTB_ANTIALL-Directives::RAF::MTB_ANTISWEEP,
					/*approach*/												AM::AM_INTERCEPT,
					/*restifcatbelow,restifavailbelow*/							2,6,
					/*gr11radarpatrol,gr11convoypatrol,gr11coastalpatrol*/		0.1,0.0,0.0,//MS 16Nov00
					/*gr1012afpat,gr1012acfactpat,gr1012supfactpat*/			0.0,0.0,0.0,//MS 12Nov00
					/*convoylevel*/												1.0,
					/*interceptbeforetarget*/									true,
					/*unitsize*/												Directives::RAF::Dir::ONESQ,
				},
				{/*HISTORICALSCENARIO_PHASE3*/
					/*sanctioned*/												Directives::RAF::MTB_ANTIALL-Directives::RAF::MTB_ANTISWEEP,
					/*approach*/												AM::AM_INTERCEPT,
					/*restifcatbelow,restifavailbelow*/							2,3,
					/*gr11radarpatrol,gr11convoypatrol,gr11coastalpatrol*/		0.0,0.0,0.0,//MS 12Nov00
					/*gr1012afpat,gr1012acfactpat,gr1012supfactpat*/			0.0,0.0,0.0,//MS 12Nov00
					/*convoylevel*/												0.0,
					/*interceptbeforetarget*/									true,
					/*unitsize*/												Directives::RAF::Dir::ONESQ,
				},
				{/*HISTORICALSCENARIO_PHASE4*/
//TempCode MS 28Aug00 					/*sanctioned*/												Directives::RAF::ANTIESC,
					/*sanctioned*/												Directives::RAF::MTB_ANTIALL-Directives::RAF::MTB_ANTISWEEP,
					/*approach*/												AM::AM_INTERCEPT,
					/*restifcatbelow,restifavailbelow*/							2,3,
					/*gr11radarpatrol,gr11convoypatrol,gr11coastalpatrol*/		0.0,0.0,0.0,//MS 12Nov00
					/*gr1012afpat,gr1012acfactpat,gr1012supfactpat*/			0.0,0.0,0.0,//MS 12Nov00
					/*convoylevel*/												0.0,
					/*interceptbeforetarget*/									true,
					/*unitsize*/												Directives::RAF::Dir::BIGW,
				},
				{/*HISTORICALSCENARIO_A*/
					/*sanctioned*/												Directives::RAF::MTB_ANTIALL-Directives::RAF::MTB_ANTISWEEP,
					/*approach*/												AM::AM_INTERCEPT,
					/*restifcatbelow,restifavailbelow*/							2,6,
					/*gr11radarpatrol,gr11convoypatrol,gr11coastalpatrol*/		0.3,0.1,0.0,
					/*gr1012afpat,gr1012acfactpat,gr1012supfactpat*/			0.3,0.0,0.0,
					/*convoylevel*/												1.0,
					/*interceptbeforetarget*/									true,
					/*unitsize*/												Directives::RAF::Dir::ONESQ,
				},
				{/*HISTORICALSCENARIO_B*/
					/*sanctioned*/												Directives::RAF::MTB_ANTIALL-Directives::RAF::MTB_ANTISWEEP,
					/*approach*/												AM::AM_INTERCEPT,
					/*restifcatbelow,restifavailbelow*/							2,6,
					/*gr11radarpatrol,gr11convoypatrol,gr11coastalpatrol*/		0.3,0.1,0.0,
					/*gr1012afpat,gr1012acfactpat,gr1012supfactpat*/			0.3,0.0,0.0,
					/*convoylevel*/												1.0,
					/*interceptbeforetarget*/									true,
					/*unitsize*/												Directives::RAF::Dir::ONESQ,
				},
				{/*HISTORICALSCENARIO_C*/
					/*sanctioned*/												Directives::RAF::MTB_ANTIALL-Directives::RAF::MTB_ANTISWEEP,
					/*approach*/												AM::AM_INTERCEPT,
					/*restifcatbelow,restifavailbelow*/							2,6,
					/*gr11radarpatrol,gr11convoypatrol,gr11coastalpatrol*/		0.3,0.1,0.0,
					/*gr1012afpat,gr1012acfactpat,gr1012supfactpat*/			0.3,0.0,0.0,
					/*convoylevel*/												1.0,
					/*interceptbeforetarget*/									true,
					/*unitsize*/												Directives::RAF::Dir::ONESQ,
				},
				{/*HISTORICALSCENARIO_D*/
					/*sanctioned*/												Directives::RAF::MTB_ANTIALL-Directives::RAF::MTB_ANTISWEEP,
					/*approach*/												AM::AM_INTERCEPT,
					/*restifcatbelow,restifavailbelow*/							2,6,
					/*gr11radarpatrol,gr11convoypatrol,gr11coastalpatrol*/		0.3,0.1,0.0,
					/*gr1012afpat,gr1012acfactpat,gr1012supfactpat*/			0.3,0.0,0.0,
					/*convoylevel*/												1.0,
					/*interceptbeforetarget*/									true,
					/*unitsize*/												Directives::RAF::Dir::ONESQ,
				},
				{/*HISTORICALSCENARIO_E*/
					/*sanctioned*/												Directives::RAF::MTB_ANTIALL-Directives::RAF::MTB_ANTISWEEP,
					/*approach*/												AM::AM_INTERCEPT,
					/*restifcatbelow,restifavailbelow*/							2,6,
					/*gr11radarpatrol,gr11convoypatrol,gr11coastalpatrol*/		0.3,0.1,0.0,
					/*gr1012afpat,gr1012acfactpat,gr1012supfactpat*/			0.3,0.0,0.0,
					/*convoylevel*/												1.0,
					/*interceptbeforetarget*/									true,
					/*unitsize*/												Directives::RAF::Dir::ONESQ,
				},
				{/*HISTORICALSCENARIO_F*/
					/*sanctioned*/												Directives::RAF::MTB_ANTIALL-Directives::RAF::MTB_ANTISWEEP,
					/*approach*/												AM::AM_INTERCEPT,
					/*restifcatbelow,restifavailbelow*/							2,6,
					/*gr11radarpatrol,gr11convoypatrol,gr11coastalpatrol*/		0.3,0.1,0.0,
					/*gr1012afpat,gr1012acfactpat,gr1012supfactpat*/			0.3,0.0,0.0,
					/*convoylevel*/												1.0,
					/*interceptbeforetarget*/									true,
					/*unitsize*/												Directives::RAF::Dir::ONESQ,
				},
				{/*HISTORICALSCENARIO_G*/
					/*sanctioned*/												Directives::RAF::MTB_ANTIALL-Directives::RAF::MTB_ANTISWEEP,
					/*approach*/												AM::AM_INTERCEPT,
					/*restifcatbelow,restifavailbelow*/							2,6,
					/*gr11radarpatrol,gr11convoypatrol,gr11coastalpatrol*/		0.3,0.1,0.0,
					/*gr1012afpat,gr1012acfactpat,gr1012supfactpat*/			0.3,0.0,0.0,
					/*convoylevel*/												1.0,
					/*interceptbeforetarget*/									true,
					/*unitsize*/												Directives::RAF::Dir::ONESQ,
				},
				{/*HISTORICALSCENARIO_H*/
					/*sanctioned*/												Directives::RAF::MTB_ANTIALL-Directives::RAF::MTB_ANTISWEEP,
					/*approach*/												AM::AM_INTERCEPT,
					/*restifcatbelow,restifavailbelow*/							2,6,
					/*gr11radarpatrol,gr11convoypatrol,gr11coastalpatrol*/		0.3,0.1,0.0,
					/*gr1012afpat,gr1012acfactpat,gr1012supfactpat*/			0.3,0.0,0.0,
					/*convoylevel*/												1.0,
					/*interceptbeforetarget*/									true,
					/*unitsize*/												Directives::RAF::Dir::ONESQ,
				},
			}
 		}
	},
endinst(CampaignPackages, CampaignConvoy_Def);
//------------------------------------------------------------------------------
startinst(CampaignStatic, CampaignRadar_Def)
	/*garbage*/		sizeof(CampaignStatic),
	/*introsmack*/		FIL_VID_PHASE2BEGINS,
	/*IntroQuarterArt*/	FIL_NULL,
	
	/*playerhomebase*/	UID_AF_Caffiers,							//MS 19Aug96
	/*playertakeoff*/	UID_AF_Caffiers,							//MS 19Aug96
	/*firsttime*/	true,
	/*startdate, in secs +BASECENTURY, 1-5-17*/	JUL10th1940,
	/*ripdate, in secs +BASECENTURY, 1-5-17*/	AUG12th1940,
	/*currdate, in secs +BASECENTURY, 1-5-17*/	AUG12th1940,
	/*lastdate*/		AUG23rd1940,
	/*currtime*/		MORNINGPERIODSTART,				//can only be the start time
	/*currperiodtime*/	MORNINGPERIODSTART,
	/*dawntime*/		HR06,
	/*dusktime*/		HR18,
	/*sunsouth*/		SUNELEVDIST,
	/*sl_category*/		1,												//RDH 01/03/00
	/*playerrank*/		SECLIEUTENANT,
	/*MoraleType*/		SKILL_REGULAR1,
	/*acesavail*/		0,
	/*reservesavail*/	12,
	/*currentplayerslot*/	0,
	/*name*/				"Name",
	/*aircraftname*/		"Silver Eagle",
//TempCode MS 06Apr99 	/*front*/				{UID_StKimchon,UID_StAndong,UID_StYonghae},//MS 22Apr99
//DeadCode MS 09Jun99 	/*front*/				{UID_SdBlTaejon,UID_StUisong,UID_StYonghae},//MS 22Apr99
/*front*/				{UID_NULL},//UID_StKumi,UID_StAndong,UID_StYonghae},//MS 22Apr99 //RJS 16/11/99
	/*Directives::LW::HistTypes*/	Directives::LW::LWHISTORICALPHASE2A,
	/*Directives::RAF::HistTypes*/	Directives::RAF::HISTORICALSCENARIO_PHASE2,
	/*camp_win_anim*/	 FIL_NULL,
	/*camp_lost_anim*/	 FIL_NULL,

endinst(CampaignStatic, CampaignRadar_Def);
//------------------------------------------------------------------------------
startinst(CampaignStatic, CampaignAirfields_Def)
	/*garbage*/		sizeof(CampaignStatic),
	/*introsmack*/		FIL_VID_PHASE3BEGINS,
	/*IntroQuarterArt*/	FIL_NULL,
	
	/*playerhomebase*/	UID_AF_Caffiers,							//MS 19Aug96
	/*playertakeoff*/	UID_AF_Caffiers,							//MS 19Aug96
	/*firsttime*/	true,
	/*startdate, in secs +BASECENTURY, 1-5-17*/	JUL10th1940,
	/*ripdate, in secs +BASECENTURY, 1-5-17*/	AUG24th1940,
	/*currdate, in secs +BASECENTURY, 1-5-17*/	AUG24th1940,
	/*lastdate*/		SEP6th1940,
	/*currtime*/		MORNINGPERIODSTART,				//can only be the start time
	/*currperiodtime*/	MORNINGPERIODSTART,
	/*dawntime*/		HR06,
	/*dusktime*/		HR18,
	/*sunsouth*/		SUNELEVDIST,
	/*sl_category*/		1,												//RDH 01/03/00
	/*playerrank*/		SECLIEUTENANT,
	/*MoraleType*/		SKILL_REGULAR1,
	/*acesavail*/		0,
	/*reservesavail*/	12,
	/*currentplayerslot*/	0,
	/*name*/				"Name",
	/*aircraftname*/		"Silver Eagle",
	/*front*/				{UID_NULL},//UID_MyBlSeoul,UID_StChuncheon,UID_StKansang},//MS 09Jun99
	/*Directives::LW::HistTypes*/	Directives::LW::LWHISTORICALPHASE3A,
	/*Directives::RAF::HistTypes*/	Directives::RAF::HISTORICALSCENARIO_PHASE3,
	/*camp_win_anim*/	 FIL_NULL,
	/*camp_lost_anim*/	 FIL_NULL,


endinst(CampaignStatic, CampaignAirfields_Def);
//------------------------------------------------------------------------------
startinst(CampaignStatic, CampaignBlitz_Def)
	/*garbage*/		sizeof(CampaignStatic),
	/*introsmack*/		FIL_VID_PHASE4BEGINS,
	/*IntroQuarterArt*/	FIL_NULL,
	
	/*playerhomebase*/	UID_AF_Caffiers,							//MS 19Aug96
	/*playertakeoff*/	UID_AF_Caffiers,							//MS 19Aug96
	/*firsttime*/	true,
	/*startdate, in secs +BASECENTURY, 1-5-17*/	JUL10th1940,
	/*ripdate, in secs +BASECENTURY, 1-5-17*/	SEP7th1940,
	/*currdate, in secs +BASECENTURY, 1-5-17*/	SEP7th1940,
	/*lastdate*/		SEP15th1940,
	/*currtime*/		MORNINGPERIODSTART,				//can only be the start time
	/*currperiodtime*/	MORNINGPERIODSTART,
	/*dawntime*/		HR06,
	/*dusktime*/		HR18,
	/*sunsouth*/		SUNELEVDIST,
	/*sl_category*/		1,												//RDH 01/03/00
	/*playerrank*/		SECLIEUTENANT,
	/*MoraleType*/		SKILL_REGULAR1,
	/*acesavail*/		0,
	/*reservesavail*/	12,
	/*currentplayerslot*/	0,
	/*name*/				"Name",
	/*aircraftname*/		"Silver Eagle",
	/*front*/				{UID_NULL},//UID_MyRdPyongyang,UID_StSamdung,UID_MyRlWonsan},//MS 14May99
	/*Directives::LW::HistTypes*/	Directives::LW::LWHISTORICALPHASE4A,
	/*Directives::RAF::HistTypes*/	Directives::RAF::HISTORICALSCENARIO_PHASE4,
	/*camp_win_anim*/	 FIL_NULL,
	/*camp_lost_anim*/	 FIL_NULL,

endinst(CampaignStatic, CampaignBlitz_Def);
//------------------------------------------------------------------------------
//DEADCODE RDH 03/04/00 startinst(CampaignStatic, CampaignSpring_Def)
//DEADCODE RDH 03/04/00 	/*garbage*/		sizeof(CampaignStatic),
//DEADCODE RDH 03/04/00 	/*introsmack*/		FIL_VID_PHASE4BEGINS,
//DEADCODE RDH 03/04/00 	/*IntroQuarterArt*/	FIL_NULL,
//DEADCODE RDH 03/04/00 	
//DEADCODE RDH 03/04/00 	/*playerhomebase*/	UID_AF_Caffiers,							//MS 19Aug96
//DEADCODE RDH 03/04/00 	/*playertakeoff*/	UID_AF_Caffiers,							//MS 19Aug96
//DEADCODE RDH 03/04/00 	/*firsttime*/	true,
//DEADCODE RDH 03/04/00 	/*startdate, in secs +BASECENTURY, 1-5-17*/	SEP7th1940,
//DEADCODE RDH 03/04/00 	/*ripdate, in secs +BASECENTURY, 1-5-17*/	SEP7th1940,
//DEADCODE RDH 03/04/00 	/*currdate, in secs +BASECENTURY, 1-5-17*/	SEP7th1940,
//DEADCODE RDH 03/04/00 	/*lastdate*/		SEP15th1940,
//DEADCODE RDH 03/04/00 	/*currtime*/		MORNINGPERIODSTART,
//DEADCODE RDH 03/04/00 	/*dawntime*/		HR06,
//DEADCODE RDH 03/04/00 	/*dusktime*/		HR18,
//DEADCODE RDH 03/04/00 	/*sunsouth*/		SUNELEVDIST,
//DEADCODE RDH 03/04/00 	/*sl_category*/		1,												//RDH 01/03/00
//DEADCODE RDH 03/04/00 	/*playerrank*/		SECLIEUTENANT,
//DEADCODE RDH 03/04/00 	/*MoraleType*/		SKILL_REGULAR1,
//DEADCODE RDH 03/04/00 	/*acesavail*/		0,
//DEADCODE RDH 03/04/00 	/*reservesavail*/	12,
//DEADCODE RDH 03/04/00 	/*currentplayerslot*/	0,
//DEADCODE RDH 03/04/00 	/*name*/				"Name",
//DEADCODE RDH 03/04/00 	/*aircraftname*/		"Silver Eagle",
//DEADCODE RDH 03/04/00 
//DEADCODE RDH 03/04/00 //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//DEADCODE RDH 03/04/00 //THIS SECTION WILL BE IN FINAL VERSION, IS COMMENTED OUT WHEN TESTING
//DEADCODE RDH 03/04/00 /*front*/				{UID_NULL},//UID_SdBlPyongtaek,UID_SdRdWonju,UID_StKangnung},
//DEADCODE RDH 03/04/00 
//DEADCODE RDH 03/04/00 	/*camp_win_anim*/	 FIL_NULL,
//DEADCODE RDH 03/04/00 	/*camp_lost_anim*/	 FIL_NULL,
//DEADCODE RDH 03/04/00 
//DEADCODE RDH 03/04/00 endinst(CampaignStatic, CampaignSpring_Def);

startinst(CampaignStatic, CampaignScramble_Def)
	/*garbage*/		sizeof(CampaignStatic),
	/*introsmack*/		FIL_VID_PHASE4BEGINS,
	/*IntroQuarterArt*/	FIL_NULL,
	
	/*playerhomebase*/	UID_AF_Caffiers,							//MS 19Aug96
	/*playertakeoff*/	UID_AF_Caffiers,							//MS 19Aug96
	/*firsttime*/	true,
	/*startdate, in secs +BASECENTURY, 1-5-17*/	JUL10th1940,
	/*ripdate, in secs +BASECENTURY, 1-5-17*/	SEP7th1940,
	/*currdate, in secs +BASECENTURY, 1-5-17*/	SEP7th1940,
	/*lastdate*/		SEP15th1940,
	/*currtime*/		MORNINGPERIODSTART,
	/*currperiodtime*/	MORNINGPERIODSTART,
	/*dawntime*/		HR06,
	/*dusktime*/		HR18,
	/*sunsouth*/		SUNELEVDIST,
	/*sl_category*/		1,												//RDH 01/03/00
	/*playerrank*/		SECLIEUTENANT,
	/*MoraleType*/		SKILL_REGULAR1,
	/*acesavail*/		0,
	/*reservesavail*/	12,
	/*currentplayerslot*/	0,
	/*name*/				"Name",
	/*aircraftname*/		"Silver Eagle",

	/*front*/				{UID_NULL},//UID_SdBlPyongtaek,UID_SdRdWonju,UID_SdRdYangyang},
	/*Directives::LW::HistTypes*/	Directives::LW::LWHISTORICALPHASE1A,
	/*Directives::RAF::HistTypes*/	Directives::RAF::HISTORICALSCENARIO_PHASE1,
	/*camp_win_anim*/	 FIL_NULL,
	/*camp_lost_anim*/	 FIL_NULL,

endinst(CampaignStatic, CampaignScramble_Def);



//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//nasty global!!!!!!!!!!!!!!!!!!!!!!!!!!!
//DeadCode JIM 22Aug96 SpecialEventBitField	specialeventbits;
//DeadCode JIM 22Aug96 NewsEventField			newsevent;

//MARK, this is the list of events structures					//MS 04Mar99

//MARK, this is the list of events structures					//MS 04Mar99

#define FIL(f1,f2)		FIL_##f1,FIL_##f2
#define FIL2(f1)		FIL_##f1,FIL_##f1
#define FILTO(f1)		FIL_##f1,FIL_##f1##_TO

#define BAN(f1,f2)		BANDIT##f1,BANDIT##f2
//DEADCODE DAW 29/01/00 typedef	MigEvent ME;

//MissMan	Miss_Man ;
MissMan::CampaignName	MissMan::currcampaignnum	= MissMan::INTROCAMPAIGN;
CampaignBase			*MissMan::campaigntable[MAXCAMPAIGNNUM]
						={
							&CampaignConvoy_Def,						//RDH 03/04/00
							&CampaignRadar_Def,							//RDH 03/04/00
							&CampaignAirfields_Def,							//RDH 19/03/99
							&CampaignBlitz_Def,							//RDH 19/03/99
//DEADCODE RDH 03/04/00 							&CampaignSpring_Def,							//RDH 05Sep96 //RDH 19/03/99
							&CampaignScramble_Def		//scramble
						 };


Campaign&	Campaign::operator=(CampaignBase*	b)
{
	char	*s=(char*)b,
			*t=(char*)this;

	for (int i=b->garbage;i--;)
		*t++=*s++;
	s=(char*)&CampaignConvoy_Def + b->garbage;
	for (i=CampaignConvoy_Def.garbage-b->garbage;i--;)
		*t++=*s++;
	for (i=sizeof(Campaign)-CampaignConvoy_Def.garbage;i--;)
		*t++=0;
	garbage=sizeof(Campaign);
	CampaignInit();
	return *this;
}
Campaign&	Campaign::operator+=(CampaignBase*	b)
{
	char	*s=(char*)b,
			*t=(char*)this;

	for (int i=b->garbage;i--;)
		*t++=*s++;
	return *this;
}
Campaign&	Campaign::operator=(CampaignZero&	b)
	{
		return operator=(&b);
	}

Campaign&	Campaign::operator+=(CampaignZero&	b)
	{
		return operator+=(&b);
	}


void	Campaign::CampaignInit()
{
	Squad_Diary.EmptyDiary();											//RJS 9Oct00
	strcpy(MMC.PlayerName,Save_Data.CommsPlayerName);

	InitIcons();		//also loads and initialises nodetree!
//DEADCODE RDH 17/03/00 	curracceltype=ACCEL_RECONNSPD;
	curracceltype=ACCEL_RAIDSPD;
	accelrates[ACCEL_PAUSED]=0;
	accelrates[ACCEL_NORMAL]=1;
	accelrates[ACCEL_RAIDSPD]=20;	//600;
	accelrates[ACCEL_RECONNSPD]=40;
	accelrates[ACCEL_NONRAIDSPD]=300;
	accelrates[ACCEL_DIALOGSPEED]=1;
	{for (int i=SQ_BR_START+1;i<SQ_BR_END;i++)
			thisweekreview.Note(Node_Data[SquadNum(i)].AcType(),PeriodReview::AVAILSTART,Node_Data[SquadNum(i)].acavail);
	}
	{for (int i=SQ_LW_START+1;i<SQ_MAX;i++)
		if (GruppenPtr(Node_Data[SquadNum(i)])->periodsuntilready!=Gruppen::BUSY_IN_EUROPE)
			thisweekreview.Note(Node_Data[SquadNum(i)].AcType(),PeriodReview::AVAILSTART,Node_Data[SquadNum(i)].acavail);
	}
//DEADCODE RDH 17/03/00 	curraccelrate=accelrates[curracceltype];
	fav.decelon=0;
	fav.flyon = 0;
	fav.flyon |= AS_SMALL_ENGAGEMENT;
	fav.flyon |= AS_LARGE_ENGAGEMENT;
	fav.flyon |= AS_LOSSES;
	fav.flyon |= AS_TARG;
	fav.flyonfav = 0;
	fav.geschwadertype = 4;	//WN_BETTERRULE;		//this is to get "ANY" to start with
//DEADCODE DAW 24/11/99 	HidSkills s=SKILL_REGULARSKILL_VETERANPOTENTIAL_GOODPOTENTIAL_VERYGOOD;
//DEADCODE DAW 24/11/99 	directives.ResetForNewCampaign();
//DEADCODE JIM 16/11/99 	SupplyTree::ResetForNewCampaign();
	Dead_Stream.ClrWorldDead();	
//TEMPCODE JIM 29/02/00 	Squad_Diary.EmptyDiary();

	Todays_Packages.WipeAll();

	LWDirectivesResults::SetUpLWDirectives(lwdir);
	RAFDirectivesResults::SetUpRAFDirectives(rafdir);

//DEADCODE RDH 13/03/00 	FILT_AUTHENTICPLOTS,
//DEADCODE RDH 13/03/00 	FILT_ESCORTEDBOMBERS,
	if (Todays_Packages.localplayer==NAT_RAF)
	{
		Save_Data.mapfilters|=FILT_RAFINTERCEPTS;
		Save_Data.mapfilters|=FILT_RAFPATROLS;
		Save_Data.mapfilters|=FILT_LWARROWS;
//DEADCODE DAW 01/06/00 		Save_Data.mapfilters|=FILT_RAFTARGETLINES;
		Save_Data.mapfilters%=	FILT_RECONN;
		Save_Data.mapfilters%=FILT_BOMBERS;


	}
	else
	{
		Save_Data.mapfilters%=FILT_RAFINTERCEPTS;
		Save_Data.mapfilters%=FILT_RAFPATROLS;
		Save_Data.mapfilters%=FILT_LWARROWS;
//DEADCODE DAW 01/06/00 		Save_Data.mapfilters%=FILT_RAFTARGETLINES;
		Save_Data.mapfilters|=FILT_RECONN;
		Save_Data.mapfilters|=FILT_BOMBERS;
	}

	Save_Data.mapfilters|=FILT_LWTARGETLINES;
	
	Save_Data.mapfilters|=FILT_RAFSAG;
	Save_Data.mapfilters|=FILT_LWSAG;

//DEADCODE JIM 29/02/00 	Squad_Diary.CreateDailyRaidGroup(currdate);			//RJS 09Feb00

										//DAW 15/05/00
	Sky.SetMissionConditions ();

	playeracnum = 0;
		playersquadron=0;
}
//DEADCODE DAW 29/01/00 void	SG_DirControl::ResetForNewCampaign()
//DEADCODE DAW 29/01/00 {
//DEADCODE DAW 29/01/00 	for (int i =0; i < MAXDIRECTIVES; i++)
//DEADCODE DAW 29/01/00 	{
//DEADCODE DAW 29/01/00 		directives[i].type = i;
//DEADCODE DAW 29/01/00 	}
//DEADCODE DAW 29/01/00 	directives[1].strikeac = 64;
//DEADCODE DAW 29/01/00 	directives[0].fighterac = 32;
//DEADCODE DAW 29/01/00 	autogen = true;
//DEADCODE DAW 29/01/00 	autodisplay = true;
//DEADCODE DAW 29/01/00 }
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 void Campaign::AddDebriefData(Debrief::SquadKills& src, Debrief::SquadKills& dest)
//DEADCODE DAW 29/01/00 {
//DEADCODE DAW 29/01/00 	for (Debrief::Types i = Debrief::REDAC; i < Debrief::TARG_MAX; i++)
//DEADCODE DAW 29/01/00 		for (SquadSelect j = PT_SPIT_A; j < (PT_GER_FLYABLE); j++)
//DEADCODE DAW 29/01/00 			dest[j][i] += src[j][i];
//DEADCODE DAW 29/01/00 }
//DEADCODE DAW 29/01/00 void Campaign::ZeroDebriefData(Debrief::SquadKills& dest)
//DEADCODE DAW 29/01/00 {
//DEADCODE DAW 29/01/00 	for (Debrief::Types i = Debrief::REDAC; i < Debrief::TARG_MAX; i++)
//DEADCODE DAW 29/01/00 		for (SquadSelect j = PT_SPIT_A; j < (PT_GER_FLYABLE); j++)
//DEADCODE DAW 29/01/00 			dest[j][i] = 0;
//DEADCODE DAW 29/01/00 }
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 int Campaign::StoresDestroyedForNodeRoute(SupplyNode* node)
//DEADCODE DAW 29/01/00 {
//DEADCODE DAW 29/01/00 	int stores_destroyed=0;
//DEADCODE DAW 29/01/00 	int i = 0;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	SupplyRoute* currroute=node->forward;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	while	(	(i <= NUM_OF_SUPPLYROUTES)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 			)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	{
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		while (currroute)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		{
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 			stores_destroyed += currroute->stores_destroyed;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 			currroute = currroute->alternateroute;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		}
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		currroute =	node->route[i];	  //accesses the non-existant route[3],but then quits
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		i++;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	}
//DEADCODE DAW 29/01/00 	return (stores_destroyed);
//DEADCODE DAW 29/01/00 }
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 void Campaign::BattleLossesForNode(SupplyNode* node, int& redlosses, int& bluelosses)
//DEADCODE DAW 29/01/00 {
//DEADCODE DAW 29/01/00 	redlosses = 0;
//DEADCODE DAW 29/01/00 	bluelosses = 0;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	TeamDef::Team blueforce;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	if	(node->supplyline->initiative==REDATTACKING)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		blueforce = TeamDef::HOME;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	else
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		blueforce = TeamDef::AWAY;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	for (int i=0;i<node->supplyline->groundbattle.usedteams;i++)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	{
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		if (node->supplyline->groundbattle.teamlist[i].team==blueforce)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 			bluelosses += node->supplyline->groundbattle.teamlist[i].lastlosses;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		else
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 			redlosses += node->supplyline->groundbattle.teamlist[i].lastlosses;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	}
//DEADCODE DAW 29/01/00 }

bool	Campaign::ChkEndCampaign()
{
	bool retval = false;
	wincamp = false;

//DEADCODE JIM 16/11/99 	if (currdate > lastdate)
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99 		retval = true;
//DEADCODE JIM 16/11/99 	}
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99 		int msn = curr_msn;
//DEADCODE JIM 16/11/99 		if (currdate <= lastdate)
//DEADCODE JIM 16/11/99 			msn = curr_msn - 1; //look at last mission except for last mission
//DEADCODE JIM 16/11/99 		if (msn < 0)
//DEADCODE JIM 16/11/99 			msn = 0;
//DEADCODE JIM 16/11/99 //DEADCODE DAW 18/06/99 		SupplyNode* node = SupplyTree::FindSupplyNodeForNodeItem(missions[msn].target);
//DEADCODE JIM 16/11/99 		SupplyTree::Supply2UID rel;
//DEADCODE JIM 16/11/99 		SupplyNode*	node=SupplyTree::FindSupplyNodeForItem(missions[msn].target,&rel);
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 		switch (Miss_Man.currcampaignnum)
//DEADCODE JIM 16/11/99 		{
//DEADCODE JIM 16/11/99 			case MissMan::F80_CAMPAIGN:
//DEADCODE JIM 16/11/99 			{//truck interdiction
//DEADCODE JIM 16/11/99 				curr_score += StoresDestroyedForNodeRoute(node);
//DEADCODE JIM 16/11/99 				if (curr_score >= winscore)
//DEADCODE JIM 16/11/99 				{
//DEADCODE JIM 16/11/99 					/**/wincamp = true;
//DEADCODE JIM 16/11/99 					retval = true;
//DEADCODE JIM 16/11/99 				}
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 				break;
//DEADCODE JIM 16/11/99 			}
//DEADCODE JIM 16/11/99 			case MissMan::F51_CAMPAIGN:
//DEADCODE JIM 16/11/99 			{
//DEADCODE JIM 16/11/99 				int	redlosses;
//DEADCODE JIM 16/11/99 				int bluelosses;
//DEADCODE JIM 16/11/99 				BattleLossesForNode(node, redlosses, bluelosses);
//DEADCODE JIM 16/11/99 				curr_score += redlosses;
//DEADCODE JIM 16/11/99 				if (curr_score >= winscore)
//DEADCODE JIM 16/11/99 				{
//DEADCODE JIM 16/11/99 					/**/wincamp = true;
//DEADCODE JIM 16/11/99 					retval = true;
//DEADCODE JIM 16/11/99 				}
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 				break;
//DEADCODE JIM 16/11/99 			}
//DEADCODE JIM 16/11/99 			case MissMan::F84_CAMPAIGN:
//DEADCODE JIM 16/11/99 			case MissMan::F86_CAMPAIGN:
//DEADCODE JIM 16/11/99 			{
//DEADCODE JIM 16/11/99 				int		currlevel=0;
//DEADCODE JIM 16/11/99 				switch (rel)
//DEADCODE JIM 16/11/99 				{
//DEADCODE JIM 16/11/99 					case SupplyTree::S2U_MAIN:
//DEADCODE JIM 16/11/99 						currlevel=node->attackstats.damagelevel;
//DEADCODE JIM 16/11/99 					break;
//DEADCODE JIM 16/11/99 					case SupplyTree::S2U_AF0:
//DEADCODE JIM 16/11/99 					case SupplyTree::S2U_AF1:
//DEADCODE JIM 16/11/99 					case SupplyTree::S2U_AF2:
//DEADCODE JIM 16/11/99 						currlevel=SupplyTree::FindAirfieldForItem(missions[msn].target)->attackstats.damagelevel;
//DEADCODE JIM 16/11/99 					break;
//DEADCODE JIM 16/11/99 					case SupplyTree::S2U_ROUTE0:
//DEADCODE JIM 16/11/99 					case SupplyTree::S2U_ROUTE1:
//DEADCODE JIM 16/11/99 					case SupplyTree::S2U_ROUTE2:
//DEADCODE JIM 16/11/99 						currlevel=node->route[rel-SupplyTree::S2U_ROUTE0]->attackstats.damagelevel;
//DEADCODE JIM 16/11/99 					break;
//DEADCODE JIM 16/11/99 				}	
//DEADCODE JIM 16/11/99 				if (currlevel >= 40)							
//DEADCODE JIM 16/11/99 					curr_score ++; 
//DEADCODE JIM 16/11/99 				if (curr_score >= winscore)
//DEADCODE JIM 16/11/99 				{
//DEADCODE JIM 16/11/99 					/**/wincamp = true;
//DEADCODE JIM 16/11/99 					retval = true;
//DEADCODE JIM 16/11/99 				}
//DEADCODE JIM 16/11/99 				break;
//DEADCODE JIM 16/11/99 			}
//DEADCODE JIM 16/11/99 			case MissMan::SO51_CAMPAIGN:
//DEADCODE JIM 16/11/99 			{
//DEADCODE JIM 16/11/99 				if	(		(SupplyTree::ChkSpringOffensiveOver())
//DEADCODE JIM 16/11/99 						||	(currdate > lastdate)
//DEADCODE JIM 16/11/99 					)
//DEADCODE JIM 16/11/99 					retval = true;
//DEADCODE JIM 16/11/99 				else
//DEADCODE JIM 16/11/99 					retval = false;
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 				//decided later
//DEADCODE JIM 16/11/99 				break;
//DEADCODE JIM 16/11/99 			}
//DEADCODE JIM 16/11/99 		}
//DEADCODE JIM 16/11/99 	}

	return(retval);
}
//////////////////////////////////////////////////////////////////////
//
// Function:    SetMissionConditions 
// Date:		29/01/00
// Author:		DAW
//
//Description: 	Atmosphere stuff that reads the campaign structure directly
//
//////////////////////////////////////////////////////////////////////
void Atmosphere::SetMissionTemp (SWord month)
{
	int maxt[12] =	{3,5,8,12,20,25,25,25,23,15,10,5};
	int mint[12] =	{-10,-10,-5,0,2,8,10,10,8,6,0,-6};
	int maxtemp, mintemp;
	FP		delta;
	FP		hr12 = SECSPERDAY/2;

	

	maxtemp = maxt[month];
	mintemp = mint[month];

	delta = MMC.currtime - hr12;
	if (delta < 0 )
		delta = - delta;
	delta = hr12 - delta;
	Temp0 = (maxtemp - mintemp) * delta / hr12;
	FP var = Math_Lib.rnd (7);
	var = var - 3;
	TempVar = TempVar + var;
	if (TempVar > 10)
		TempVar = 10;
	if (TempVar < -10)
		TempVar = -10;
	Temp0 = 273 + Temp0 + TempVar + mintemp;

}
void Atmosphere::SetMissionPress (SWord month)
{



	FP delta;
	delta = month - 6;
	if (delta < 0)
		delta = - delta;
	if (delta < 3)
	{//Summer
		Press0 = 1001 + TempVar;
	}else
	{
		Press0 = 999 - TempVar;
	}

	ContrailBandCentre = FEET2CM(32000);		//CSB 10/06/99	
	ContrailBandWidth = FEET2CM(4000);	//CSB 10/06/99	

	FP ChanceBad = 0.5 + 0.5 * FCos(month * 6.2831853 / 12.0);		//CSB 02/07/99	
	ChanceBad = 819.2 + 8192.0 * ChanceBad;						//CSB 02/07/99	
	if(Math_Lib.rnd() > ChanceBad)									//CSB 02/07/99	
//DeadCode CSB 02/07/99		if (Press0 > 1000)
	{
		Conditions = 0;
		Visibility = 4000000;

	}
	else
	{
		Visibility = 4000000;			//##lower vis possible here
		if (Temp0 < 273)
			Conditions = 2;
		else
			Conditions = 1;
	}

	if (		(Press0 < 980)
			&&	(MMC.currtime <  HR09)
		)
		MistInValley = true;
	else
		MistInValley = false;

//this will be a function of temp and press
	CloudLayer = 457200;
}
void Atmosphere::SetMissionConditions ()
{
	FCRD wind_at_zero, wind_at_alt;

  	SWord	month = 0;
	SWord	day = 0,year = 0;
	Math_Lib.DateFromSecs (MMC.currdate, day,month,year);

	SetMissionTemp (month);
	SetMissionPress (month);
	SetMissionDensity();
	SetMissionClouds();

	SetMissionWind(month);
 
	SWord Latitude = 51;												//RDH 25/02/00
	SetMissionDawnDusk(Latitude, MMC.currdate, MMC.dawntime, MMC.dusktime);
}

//////////////////////////////////////////////////////////////////////
//
// Function:    NextMission
// Date:		29/01/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	Campaign::NextMission()
{
//init and test code
//DEADCODE RDH 24/03/99		/**/DisDayEntry(Debrief::NAME, UID_Null, Debrief::D_BritsArrive_H);


//DEADCODE RDH 12/02/99	currtime = HR11;

	Sky.SetMissionConditions ();
//DEADCODE RDH 19/06/99 	UpdateAllDis();
//DeadCode JIM 18Oct00 	UpdatePlayerLog();
//DEADCODE JIM 16/11/99 	SupplyTree::UpDateAttacksStructure();
//DEADCODE JIM 16/11/99 	SupplyTree::RemoveDestroyedStores();
	


//handle debrief counters and data
//DEADCODE DAW 29/01/00 	AddDebriefData(debrief.lastperiod, debrief.cumulative);
//DEADCODE DAW 29/01/00 	AddDebriefData(debrief.lastperiod, debrief.total);
//moved to EndBebrief to avoid date being wrong in debrief		  //RDH 12/06/99
//DEADCODE RDH 12/06/99 	if (debrief.currperiod == 2)
//DEADCODE RDH 12/06/99 	{
//DEADCODE RDH 12/06/99 		debrief.lastday = debrief.cumulative;
//DEADCODE RDH 12/06/99 		ZeroDebriefData(debrief.cumulative);
//DEADCODE RDH 12/06/99 	}
//DEADCODE RDH 12/06/99 	debrief.currperiod++;

//DEADCODE JIM 16/11/99 	if (	SupplyTree::WestRoute.initiative==REDATTACKING
//DEADCODE JIM 16/11/99 		||	SupplyTree::WestRoute.initiative==BLUEATTACKING)
//DEADCODE JIM 16/11/99 		if (SupplyTree::WestRoute.groundbattle.usednodes)
//DEADCODE JIM 16/11/99 		{
//DEADCODE JIM 16/11/99 			SupplyTree::WestRoute.groundbattle.PostAttackDecisions();
//DEADCODE JIM 16/11/99 			SupplyTree::WestRoute.PostAttackReports();
//DEADCODE JIM 16/11/99 //DEADCODE DAW 18/06/99 			SupplyTree::WestRoute.groundbattle.NextAttackDecisions();
//DEADCODE JIM 16/11/99 //DEADCODE DAW 18/06/99 			SupplyTree::WestRoute.NextAttackReports();
//DEADCODE JIM 16/11/99 		}
//DEADCODE JIM 16/11/99 	if (	SupplyTree::CentralRoute.initiative==REDATTACKING
//DEADCODE JIM 16/11/99 		||	SupplyTree::CentralRoute.initiative==BLUEATTACKING)
//DEADCODE JIM 16/11/99 		if (SupplyTree::CentralRoute.groundbattle.usednodes)
//DEADCODE JIM 16/11/99 		{
//DEADCODE JIM 16/11/99 			SupplyTree::CentralRoute.groundbattle.PostAttackDecisions();
//DEADCODE JIM 16/11/99 			SupplyTree::CentralRoute.PostAttackReports();
//DEADCODE JIM 16/11/99 //DEADCODE DAW 18/06/99 			SupplyTree::CentralRoute.groundbattle.NextAttackDecisions();
//DEADCODE JIM 16/11/99 //DEADCODE DAW 18/06/99 			SupplyTree::CentralRoute.NextAttackReports();
//DEADCODE JIM 16/11/99 		}
//DEADCODE JIM 16/11/99 	if (	SupplyTree::EastRoute.initiative==REDATTACKING
//DEADCODE JIM 16/11/99 		||	SupplyTree::EastRoute.initiative==BLUEATTACKING)
//DEADCODE JIM 16/11/99 		if (SupplyTree::EastRoute.groundbattle.usednodes)
//DEADCODE JIM 16/11/99 		{
//DEADCODE JIM 16/11/99 			SupplyTree::EastRoute.groundbattle.PostAttackDecisions();
//DEADCODE JIM 16/11/99 			SupplyTree::EastRoute.PostAttackReports();
//DEADCODE JIM 16/11/99 //DEADCODE DAW 18/06/99 			SupplyTree::EastRoute.groundbattle.NextAttackDecisions();
//DEADCODE JIM 16/11/99 //DEADCODE DAW 18/06/99 			SupplyTree::EastRoute.NextAttackReports();
//DEADCODE JIM 16/11/99 		}

//moved to EndBebrief to avoid date being wrong in debrief		  //RDH 12/06/99
//DEADCODE RDH 12/06/99 	if	(Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
//DEADCODE RDH 12/06/99 	{
//DEADCODE RDH 12/06/99 		if (debrief.currperiod >=3)
//DEADCODE RDH 12/06/99 		{
//DEADCODE RDH 12/06/99 			NextDay();
//DEADCODE RDH 12/06/99 			debrief.currperiod = 0;
//DEADCODE RDH 12/06/99 			debrief.currlogday++;
//DEADCODE RDH 12/06/99 		}
//DEADCODE RDH 12/06/99 	}else
//DEADCODE RDH 12/06/99 	{
//DEADCODE RDH 12/06/99 		NextDay();
//DEADCODE RDH 12/06/99 		debrief.currperiod = 0;
//DEADCODE RDH 12/06/99 		debrief.currlogday++;
//DEADCODE RDH 12/06/99 		currdate -= SECSPERDAY;
//DEADCODE RDH 12/06/99 		if (currdate < lastdate)
//DEADCODE RDH 12/06/99 		{
//DEADCODE RDH 12/06/99 			curr_msn++;
//DEADCODE RDH 12/06/99 			currdate =	 missions[curr_msn].msn_date;
//DEADCODE RDH 12/06/99 
//DEADCODE RDH 12/06/99 		}else
//DEADCODE RDH 12/06/99 			currdate += SECSPERDAY;
//DEADCODE RDH 12/06/99 
//DEADCODE RDH 12/06/99 	}




}
//DEADCODE DAW 24/11/99 void Campaign::SwapPilot(int groupnum, int src,int dest)
//DEADCODE DAW 24/11/99 {
//DEADCODE DAW 24/11/99 //DEADCODE DAW 24/11/99 	PilotType tmppilot;
//DEADCODE DAW 24/11/99 //DEADCODE DAW 24/11/99 	tmppilot = /**/Active_Pilots[24*groupnum+src];
//DEADCODE DAW 24/11/99 //DEADCODE DAW 24/11/99 	/**/Active_Pilots[24*groupnum+src] = /**/Active_Pilots[24*groupnum+dest];
//DEADCODE DAW 24/11/99 //DEADCODE DAW 24/11/99 	/**/Active_Pilots[24*groupnum+dest] = tmppilot;
//DEADCODE DAW 24/11/99 }
//DEADCODE DAW 24/11/99 void Campaign::SwapElement(int groupnum, int src, int dest)
//DEADCODE DAW 24/11/99 {
//DEADCODE DAW 24/11/99 	for (int i = 0;i < 2; i++)
//DEADCODE DAW 24/11/99 		SwapPilot(groupnum, src+i, dest+i);
//DEADCODE DAW 24/11/99 
//DEADCODE DAW 24/11/99 }
//DEADCODE DAW 24/11/99 void Campaign::SwapFlight(int groupnum, int src, int dest)
//DEADCODE DAW 24/11/99 {
//DEADCODE DAW 24/11/99 	for (int i = 0;i < 4; i +=2)
//DEADCODE DAW 24/11/99 		SwapElement(groupnum, src+i, dest+i);
//DEADCODE DAW 24/11/99 
//DEADCODE DAW 24/11/99 }
void	Campaign::ModifySkill(int groupnum, int daysonduty)
{
//DEADCODE DAW 24/11/99 	for (int i = 0;i < 4; i ++)
//DEADCODE DAW 24/11/99 	{
//DEADCODE DAW 24/11/99 		int maxchange = (12 - daysonduty)/4;
//DEADCODE DAW 24/11/99 		if (maxchange < 0)
//DEADCODE DAW 24/11/99 			maxchange = 0;
//DEADCODE DAW 24/11/99 		if (maxchange > 0)
//DEADCODE DAW 24/11/99 		{
//DEADCODE DAW 24/11/99 			PilotType& pilot=/**/Active_Pilots[24*groupnum+i];
//DEADCODE DAW 24/11/99 			FP change = pilot.BigFlyingPotential() - pilot.BigFlyingSkill();
//DEADCODE DAW 24/11/99 			if (change > 0)
//DEADCODE DAW 24/11/99 			{
//DEADCODE DAW 24/11/99 				change = 0.5 + change * pilot.morale/MORALE_TOPMORALE;
//DEADCODE DAW 24/11/99 				pilot.SetBigFlySkill(((int)pilot.BigFlyingSkill() + (int)change));
//DEADCODE DAW 24/11/99 				
//DEADCODE DAW 24/11/99 			}
//DEADCODE DAW 24/11/99 			change = pilot.BigCombatPotential() - pilot.BigCombatSkill();
//DEADCODE DAW 24/11/99 			if (change > 0)
//DEADCODE DAW 24/11/99 			{
//DEADCODE DAW 24/11/99 				change = 0.5 + change * pilot.morale/MORALE_TOPMORALE;
//DEADCODE DAW 24/11/99 				pilot.SetBigCombSkill(pilot.BigCombatSkill() +(int)change);
//DEADCODE DAW 24/11/99 			}
//DEADCODE DAW 24/11/99 
//DEADCODE DAW 24/11/99 		}
//DEADCODE DAW 24/11/99 	}
//DEADCODE DAW 24/11/99 
}
void	Campaign::RotateFlightsCheck()
{
//DEADCODE DAW 24/11/99 	int daysincelastrotate;
//DEADCODE DAW 24/11/99 	for (SquadSelect j = PT_F86A; j < (PT_GER_FLYABLE); j++)
//DEADCODE DAW 24/11/99 	{
//DEADCODE DAW 24/11/99 		daysincelastrotate = currdate - /**/squad[j].lastrotatedate;
//DEADCODE DAW 24/11/99 		daysincelastrotate = daysincelastrotate/SECSPERDAY;
//DEADCODE DAW 24/11/99 		int freq = /**/squad[j].rotatefreq;
//DEADCODE DAW 24/11/99 		if	(		(freq)
//DEADCODE DAW 24/11/99 				&&	(daysincelastrotate >= freq)
//DEADCODE DAW 24/11/99 			)
//DEADCODE DAW 24/11/99 		{
//DEADCODE DAW 24/11/99 			ModifySkill(j, daysincelastrotate*4);
//DEADCODE DAW 24/11/99 			SwapFlight(j, 0, 4);
//DEADCODE DAW 24/11/99 			SwapFlight(j, 4, 8);
//DEADCODE DAW 24/11/99 			SwapFlight(j, 8, 12);
//DEADCODE DAW 24/11/99 			SwapFlight(j, 12, 16);
//DEADCODE DAW 24/11/99 			SwapFlight(j, 16, 20);
//DEADCODE DAW 24/11/99 //DEADCODE JIM 13/07/99 			for (int k=0; k <16;k++)
//DEADCODE DAW 24/11/99 //DEADCODE JIM 13/07/99 				/**/Active_Pilots[24*j+k].dayssincerest++;
//DEADCODE DAW 24/11/99 			for (int k=16; k <23;k++)
//DEADCODE DAW 24/11/99 				/**/Active_Pilots[24*j+k].dayssincerest = 0;
//DEADCODE DAW 24/11/99 
//DEADCODE DAW 24/11/99 			/**/squad[j].lastrotatedate = currdate;
//DEADCODE DAW 24/11/99 
//DEADCODE DAW 24/11/99 		}
//DEADCODE DAW 24/11/99 
//DEADCODE DAW 24/11/99 	}
}
void	Campaign::ReplenishAcStock()
{
//DEADCODE DAW 24/11/99 	int min = 20;
//DEADCODE DAW 24/11/99 	int minsquad;
//DEADCODE DAW 24/11/99 	for (int squad = 0; squad < 5; squad++)
//DEADCODE DAW 24/11/99 	{
//DEADCODE DAW 24/11/99 		if (/**/this->squad[squad].ac_total_avail < min)
//DEADCODE DAW 24/11/99 		{
//DEADCODE DAW 24/11/99 			minsquad = squad;
//DEADCODE DAW 24/11/99 			min = /**/this->squad[squad].ac_total_avail;
//DEADCODE DAW 24/11/99 		}
//DEADCODE DAW 24/11/99 	}
//DEADCODE DAW 24/11/99 	int acrequired = MAX_NUM_AC_IN_SQUADRON - /**/this->squad[minsquad].ac_total_avail;
//DEADCODE DAW 24/11/99 	if (acrequired > 4)
//DEADCODE DAW 24/11/99 		acrequired = 4;
//DEADCODE DAW 24/11/99 	if (acrequired > 0)
//DEADCODE DAW 24/11/99 	{
//DEADCODE DAW 24/11/99 		/**/this->squad[minsquad].ac_total_avail += acrequired;
//DEADCODE DAW 24/11/99 		DisDayEntry(Debrief::NAME, UID_BrRdYalu, Debrief::T_Replenish_H);
//DEADCODE DAW 24/11/99 
//DEADCODE DAW 24/11/99 	}
//DEADCODE DAW 24/11/99 
}
void	Campaign::RotateMiGSquadron(int squad)
{
//DEADCODE DAW 24/11/99 	/**/migsquad[squad] = /**/migsquad[/**/nextsquadtocopy];
//DEADCODE DAW 24/11/99 	/**/nextsquadtocopy++;
//DEADCODE DAW 24/11/99 	if	(/**/nextsquadtocopy >= MAXMIGSQUADRONS)
//DEADCODE DAW 24/11/99 	{
//DEADCODE DAW 24/11/99 		/**/nextsquadtocopy = WRAPMIGSQUADRONS;
//DEADCODE DAW 24/11/99 		//update startdates
//DEADCODE DAW 24/11/99 		//first 3 weeks hence to allow last squadron its fulltime
//DEADCODE DAW 24/11/99 		//then all 2 weeks so they come around a bit faster
//DEADCODE DAW 24/11/99 		/**/migsquad[WRAPMIGSQUADRONS].startdate = currdate + SECSPERDAY *21;
//DEADCODE DAW 24/11/99 		for (int i = (WRAPMIGSQUADRONS+1); i < MAXMIGSQUADRONS;i++)
//DEADCODE DAW 24/11/99 			/**/migsquad[i].startdate = currdate + SECSPERDAY *21 +
//DEADCODE DAW 24/11/99 									(WRAPMIGSQUADRONS+2 - i) * SECSPERDAY * 14;
//DEADCODE DAW 24/11/99 
//DEADCODE DAW 24/11/99 	}
//DEADCODE DAW 24/11/99 //DEADCODE RDH 21/06/99 		if	(/**/migsquad[squad].agglevel == AL_TRAINING)
//DEADCODE DAW 24/11/99 			/**/DisDayEntry(Debrief::NAME, UID_Null, Debrief::T_SquadRotate_H);
}
void	Campaign::ChkRotateMiGSquadrons()
{
//DEADCODE DAW 24/11/99 	if (/**/migsquad[0].aclosses > (/**/migsquad[0].ac_total_avail/2))
//DEADCODE DAW 24/11/99 		RotateMiGSquadron(0);
//DEADCODE DAW 24/11/99 	if (/**/migsquad[1].aclosses > (/**/migsquad[1].ac_total_avail/2))
//DEADCODE DAW 24/11/99 		RotateMiGSquadron(1);
//DEADCODE DAW 24/11/99 	if	(/**/migsquad[/**/nextsquadtocopy].startdate <= currdate)
//DEADCODE DAW 24/11/99 	{
//DEADCODE DAW 24/11/99 		if (/**/migsquad[0].aclosses > /**/migsquad[1].aclosses)
//DEADCODE DAW 24/11/99 			RotateMiGSquadron(0);
//DEADCODE DAW 24/11/99 		else
//DEADCODE DAW 24/11/99 			RotateMiGSquadron(1);
//DEADCODE DAW 24/11/99 
//DEADCODE DAW 24/11/99 	}

}
void	Campaign::ModifyMiGAggressionLevel(int squad)
{
//DEADCODE DAW 24/11/99 	if	(/**/migsquad[squad].agglevel < AL_MAX)
//DEADCODE DAW 24/11/99 	{
//DEADCODE DAW 24/11/99 		int cycleday = (currdate - migsquad[squad].startdate)%(SECSPERDAY*4);
//DEADCODE DAW 24/11/99 		if (	(!cycleday) && (Math_Lib.rnd(2)))
//DEADCODE DAW 24/11/99 			migsquad[squad].agglevel = (tAggressionLevel)((int)migsquad[squad].agglevel + (int)AL_STAGE);
//DEADCODE DAW 24/11/99 	}else if	(		(migsquad[squad].aclosseslast >= 10)
//DEADCODE DAW 24/11/99 			&&	(migsquad[squad].agglevel >	AL_MIN)
//DEADCODE DAW 24/11/99 		 )
//DEADCODE DAW 24/11/99 	{
//DEADCODE DAW 24/11/99 		migsquad[squad].agglevel = (tAggressionLevel)((int)migsquad[squad].agglevel - (int)AL_STAGE);
//DEADCODE DAW 24/11/99 		if	(migsquad[squad].agglevel == AL_TRAINING)
//DEADCODE DAW 24/11/99 			DisDayEntry(Debrief::NAME, UID_Null, Debrief::T_StoodDown_H);
//DEADCODE DAW 24/11/99 	}
}
void	Campaign::NextDay()
{
	currdate += SECSPERDAY;
//DEADCODE RDH 10/01/00 	if (currdate == MAR5th1951)
//DEADCODE RDH 10/01/00 		/**/DisDayEntry(Debrief::NAME, UID_Null, Debrief::D_BritsArrive_H);
//DEADCODE RDH 10/01/00 	if (currdate == (OCT8th1950 + SECSPERDAY))						  //RDH 14/06/99
//DEADCODE RDH 10/01/00 		/**/DisDayEntry(Debrief::NAME, UID_Null, Debrief::D_AlJolson_H);
//DEADCODE RDH 10/01/00 
//DEADCODE RDH 10/01/00 	int i;
//DEADCODE RDH 10/01/00 	ChkRotateMiGSquadrons();
//DEADCODE RDH 10/01/00 	for (i = 0; i < 2; i++)
//DEADCODE RDH 10/01/00 		ModifyMiGAggressionLevel(i);
//DEADCODE RDH 10/01/00 //rdh 9/7 edit to replenish according to campaign
//DEADCODE RDH 10/01/00 	if (Miss_Man.currcampaignnum == MissMan::SO51_CAMPAIGN)
//DEADCODE RDH 10/01/00 	{
//DEADCODE RDH 10/01/00 		int currday = currdate%(SECSPERDAY*2);							  //RDH 21/06/99
//DEADCODE RDH 10/01/00 		if (currday == 0)
//DEADCODE RDH 10/01/00 			ReplenishAcStock();
//DEADCODE RDH 10/01/00 		else
//DEADCODE RDH 10/01/00 		{
//DEADCODE DAW 24/11/99 			bool noaircraft = true;
//DEADCODE DAW 24/11/99 			for (int squad = 0; squad < 5; squad++)
//DEADCODE DAW 24/11/99 			{
//DEADCODE DAW 24/11/99 				if (/**/this->squad[squad].ac_total_avail >= 4)
//DEADCODE DAW 24/11/99 					noaircraft = false;
//DEADCODE DAW 24/11/99 			}
//DEADCODE DAW 24/11/99 			if (noaircraft)
//DEADCODE DAW 24/11/99 				this->squad[PT_F51].ac_total_avail = 4;		//give them 4 mustangs as minimum
//DEADCODE RDH 10/01/00 		}
//DEADCODE RDH 10/01/00 	}else
//DEADCODE RDH 10/01/00 	{
//DEADCODE DAW 25/11/99 		int squad;
//DEADCODE DAW 25/11/99 		switch (Miss_Man.currcampaignnum)
//DEADCODE DAW 25/11/99 		{
//DEADCODE DAW 25/11/99 			case MissMan::F80_CAMPAIGN:
//DEADCODE DAW 25/11/99 			{//truck interdiction
//DEADCODE DAW 25/11/99 				squad = PT_F80;
//DEADCODE DAW 25/11/99 				break;
//DEADCODE DAW 25/11/99 			}
//DEADCODE DAW 25/11/99 			case MissMan::F51_CAMPAIGN:
//DEADCODE DAW 25/11/99 			{
//DEADCODE DAW 25/11/99 				squad = PT_F51;
//DEADCODE DAW 25/11/99 				break;
//DEADCODE DAW 25/11/99 			}
//DEADCODE DAW 25/11/99 			case MissMan::F84_CAMPAIGN:
//DEADCODE DAW 25/11/99 			{
//DEADCODE DAW 25/11/99 				squad = PT_F84;
//DEADCODE DAW 25/11/99 				break;
//DEADCODE DAW 25/11/99 			}
//DEADCODE DAW 25/11/99 			case MissMan::F86_CAMPAIGN:
//DEADCODE DAW 25/11/99 			{
//DEADCODE DAW 24/11/99 				squad = PT_F86A;
//DEADCODE DAW 24/11/99 				if (this->squad[PT_F86E].ac_total_avail < 16)	
//DEADCODE DAW 24/11/99 					this->squad[PT_F86E].ac_total_avail = 16;	
//DEADCODE DAW 25/11/99 				break;
//DEADCODE DAW 25/11/99 			}
//DEADCODE DAW 25/11/99 		}
//DEADCODE DAW 24/11/99 		if (this->squad[squad].ac_total_avail < 16)	
//DEADCODE DAW 24/11/99 			this->squad[squad].ac_total_avail = 16;	
//DEADCODE RDH 10/01/00 	}
//DEADCODE RDH 10/01/00 
//DEADCODE RDH 10/01/00 	RotateFlightsCheck();
//DEADCODE JIM 16/11/99 	SupplyTree::NodeReview (); 
//DEADCODE JIM 16/11/99 	Dead_Stream.ReviveWorld();
//DEADCODE RDH 10/01/00 
//DEADCODE RDH 10/01/00 	if (Miss_Man.currcampaignnum == Miss_Man.F86_CAMPAIGN)							  //RDH 14/06/99
//DEADCODE RDH 10/01/00 	{																  //RDH 14/06/99
//DEADCODE RDH 10/01/00 		directives.B29avail = true;									  //RDH 14/06/99 //RDH 14/06/99
//DEADCODE RDH 10/01/00 	}else															  //RDH 14/06/99
//DEADCODE RDH 10/01/00 	{																  //RDH 14/06/99
//DEADCODE DAW 25/11/99 		int B29casualties=debrief.total[PT_B29].TotalLosses();		  //RDH 14/06/99
//DEADCODE DAW 25/11/99 		if (B29casualties-10>debrief.currlogday)	//stop the B29s
//DEADCODE DAW 25/11/99 		{
//DEADCODE DAW 25/11/99 			if (directives.dayssinceB29>=0)
//DEADCODE DAW 25/11/99 				DisDayEntry(Debrief::NAME, 0, Debrief::T_Bombers00_H);
//DEADCODE DAW 25/11/99 			directives.dayssinceB29=-4;
//DEADCODE DAW 25/11/99 		}
//DEADCODE DAW 25/11/99 		if (directives.B29avail)
//DEADCODE DAW 25/11/99 			directives.dayssinceB29 = 0;
//DEADCODE DAW 25/11/99 		else
//DEADCODE DAW 25/11/99 		{
//DEADCODE DAW 25/11/99 			directives.dayssinceB29++;
//DEADCODE DAW 25/11/99 			if (directives.dayssinceB29==0)
//DEADCODE DAW 25/11/99 			{
//DEADCODE DAW 25/11/99 				directives.dayssinceB29=4;
//DEADCODE DAW 25/11/99 				DisDayEntry(Debrief::NAME, 0, Debrief::T_Bombers01_H);
//DEADCODE DAW 25/11/99 			}
//DEADCODE DAW 25/11/99 		}
//DEADCODE DAW 25/11/99 		if (directives.dayssinceB29>4)
//DEADCODE DAW 25/11/99 			directives.B29avail = true;
//DEADCODE DAW 25/11/99 		else
//DEADCODE DAW 25/11/99 			directives.B29avail = false;
//DEADCODE RDH 10/01/00 	}
//DEADCODE RDH 01/06/99 	for (i=0;i<PILOTABLE_SQUADRONS;i++)
//DEADCODE RDH 01/06/99 	{
//DEADCODE RDH 01/06/99 		if	(squad[i].movetoairfieldindex != -1)
//DEADCODE RDH 01/06/99 		{
//DEADCODE RDH 01/06/99 			squad[i].airfieldindex = /**/squad[i].movetoairfieldindex;
//DEADCODE RDH 01/06/99 			squad[i].movetoairfieldindex = -1;
//DEADCODE RDH 01/06/99 		}
//DEADCODE RDH 01/06/99 	}

//should be later
//	EndDebrief();


}
//DEADCODE DAW 29/01/00 void	Campaign::ZeroDisDay()
//DEADCODE DAW 29/01/00 {
//DEADCODE DAW 29/01/00 	int j = 0;
//DEADCODE DAW 29/01/00 	while	(j < Debrief::DISISITFORTODAY)
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	{
//DEADCODE DAW 29/01/00 		debrief.disday[j].typeflag = 0;
//DEADCODE DAW 29/01/00 		debrief.disday[j].msgowner = 0;
//DEADCODE DAW 29/01/00 		debrief.disday[j].msgtextid = 0;
//DEADCODE DAW 29/01/00 		j++;
//DEADCODE DAW 29/01/00 	}
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 	int pack,wave,group;
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 	bool found=	Todays_Packages.GetPackage(pack,wave,group,MMC.playersquadron,MMC.playeracnum/4);
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 	if (found)
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 	{
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 		int day = MMC.debrief.currlogday;
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 		int period = MMC.debrief.currperiod;
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //DEADCODE DAW 24/11/99 		switch (group)
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //DEADCODE DAW 24/11/99 		{
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //DEADCODE DAW 24/11/99 		case 0:
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 			debrief.playerlog[day][period].role=Todays_Packages[pack].attackmethod;
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //DEADCODE DAW 24/11/99 		break;
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //DEADCODE DAW 24/11/99 		case 1:
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //DEADCODE DAW 24/11/99 			debrief.playerlog[day][period].role=DC_WW;
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //DEADCODE DAW 24/11/99 		break;
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //DEADCODE DAW 24/11/99 		case 2:
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //DEADCODE DAW 24/11/99 			debrief.playerlog[day][period].role=DUTYESCORT;
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //DEADCODE DAW 24/11/99 		break;
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //DEADCODE DAW 24/11/99 		}
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 		debrief.playerlog[day][period].target1=Todays_Packages[pack].packagetarget[0];
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 		debrief.playerlog[day][period].pilotsquad=SquadSelect(MMC.playersquadron);
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 		for (int i=PT_MIG15;i<PT_VEHICLES;i++)
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 		{
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 			debrief.playerqmcounts[SquadSelect(i)]=0;
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 		}	
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 		debrief.playertotals[(SquadSelect)MMC.playersquadron][Debrief::SORTIES]++;	  //JIM 13/07/99
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //		UByte		role;
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //		UByte		dummy;
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //		UByte		kills;	//fill in later....
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //		ONLYFIELD(UByte,	SquadSelect,pilotsquad);
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //		ONLYFIELD(UWord,	UniqueID, 	target1);
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 //		ONLYFIELD(UWord,	UniqueID,	target2);
//DEADCODE DAW 29/01/00 //DEADCODE DAW 25/11/99 	}
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 }
//DEADCODE DAW 29/01/00 void	Campaign::UpdateAllDis()
//DEADCODE DAW 29/01/00 {
//DEADCODE DAW 29/01/00 	{
//DEADCODE DAW 29/01/00 		int i = 0;
//DEADCODE DAW 29/01/00 		while	(		(i < Debrief::DISISALLTOOMUCH)
//DEADCODE DAW 29/01/00 					&&	(debrief.alldis[i].msgtextid != 0)
//DEADCODE DAW 29/01/00 				)
//DEADCODE DAW 29/01/00 				i++;
//DEADCODE DAW 29/01/00 		if (i >= Debrief::DISISALLTOOMUCH)
//DEADCODE DAW 29/01/00 			i = 0;
//DEADCODE DAW 29/01/00 		
//DEADCODE DAW 29/01/00 		if (debrief.currperiod == 0)
//DEADCODE DAW 29/01/00 		{//don't keep adding date heading if no message is added 
//DEADCODE DAW 29/01/00 			int previ = i;
//DEADCODE DAW 29/01/00 			previ--;
//DEADCODE DAW 29/01/00 			if (previ < 0)
//DEADCODE DAW 29/01/00 				previ = Debrief::DISISALLTOOMUCH-1;
//DEADCODE DAW 29/01/00 			if (debrief.alldis[previ].typeflag == Debrief::DATE)
//DEADCODE DAW 29/01/00 				i = previ;
//DEADCODE DAW 29/01/00 			debrief.alldis[i].typeflag = Debrief::DATE;
//DEADCODE DAW 29/01/00 			debrief.alldis[i].msgowner = debrief.currlogday;
//DEADCODE DAW 29/01/00 			debrief.alldis[i].msgtextid = -1;
//DEADCODE DAW 29/01/00 			i++;
//DEADCODE DAW 29/01/00 			if (i >= Debrief::DISISALLTOOMUCH)
//DEADCODE DAW 29/01/00 				i = 0;
//DEADCODE DAW 29/01/00 		}
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 		int j = 0;
//DEADCODE DAW 29/01/00 		while	(		(j < Debrief::DISISITFORTODAY)
//DEADCODE DAW 29/01/00 					&&	(debrief.disday[j].msgtextid != 0)
//DEADCODE DAW 29/01/00 				)
//DEADCODE DAW 29/01/00 		{
//DEADCODE DAW 29/01/00 			if (debrief.disday[j].typeflag != Debrief::DISCARDTARGUID)
//DEADCODE DAW 29/01/00 			{
//DEADCODE DAW 29/01/00 				debrief.alldis[i] = debrief.disday[j];
//DEADCODE DAW 29/01/00 				i++;
//DEADCODE DAW 29/01/00 				if (i >= Debrief::DISISALLTOOMUCH)
//DEADCODE DAW 29/01/00 					i = 0;
//DEADCODE DAW 29/01/00 			}
//DEADCODE DAW 29/01/00 			j++;
//DEADCODE DAW 29/01/00 		}
//DEADCODE DAW 29/01/00 	}
//DEADCODE DAW 29/01/00 }
//DeadCode JIM 18Oct00 void	Campaign::UpdatePlayerLog()
//DeadCode JIM 18Oct00 {
//DeadCode JIM 18Oct00 //DEADCODE DAW 29/01/00 
//DeadCode JIM 18Oct00 //DEADCODE DAW 29/01/00 	{
//DeadCode JIM 18Oct00 //DEADCODE DAW 29/01/00 		int day = MMC.debrief.currlogday;
//DeadCode JIM 18Oct00 //DEADCODE DAW 29/01/00 		int period = MMC.debrief.currperiod;
//DeadCode JIM 18Oct00 //DEADCODE DAW 29/01/00 		for (int i=PT_GER_FLYABLE;i<PT_VEHICLES;i++)
//DeadCode JIM 18Oct00 //DEADCODE DAW 29/01/00 		{
//DeadCode JIM 18Oct00 //DEADCODE DAW 29/01/00 			debrief.playerlog[day][period].kills+=
//DeadCode JIM 18Oct00 //DEADCODE DAW 29/01/00 				debrief.playerqmcounts[SquadSelect(i)];
//DeadCode JIM 18Oct00 //DEADCODE DAW 29/01/00 		}
//DeadCode JIM 18Oct00 //DEADCODE DAW 29/01/00 		if (debrief.playerlog[day][period].kills > 0)				  //JIM 13/07/99
//DeadCode JIM 18Oct00 //DEADCODE DAW 29/01/00 			 debrief.playertotals[(SquadSelect)playersquadron][Debrief::COMBATS]++; //JIM 13/07/99
//DeadCode JIM 18Oct00 //DEADCODE DAW 29/01/00 	}
//DeadCode JIM 18Oct00 }

//DeadCode JIM 18Oct00 FileNum	Campaign::FindSmacker(int index)
//DeadCode JIM 18Oct00 {
//DeadCode JIM 18Oct00 //DEADCODE JIM 16/11/99 	for (int i=0; i < SupplyTree::MAX_DISSMACKERS; i++)
//DeadCode JIM 18Oct00 //DEADCODE JIM 16/11/99 	{
//DeadCode JIM 18Oct00 //DEADCODE JIM 16/11/99 		if (debrief.disday[index].msgtextid == SupplyTree::dissmackers[i].idtext)
//DeadCode JIM 18Oct00 //DEADCODE JIM 16/11/99 			return (SupplyTree::dissmackers[i].file);
//DeadCode JIM 18Oct00 //DEADCODE JIM 16/11/99 	}
//DeadCode JIM 18Oct00 	return (FIL_NULL);
//DeadCode JIM 18Oct00 
//DeadCode JIM 18Oct00 }

//DEADCODE DAW 29/01/00 void	Campaign::DisDayEntry(Debrief::TypeFlag type, int msgowner, int msgtextid)
//DEADCODE DAW 29/01/00 {
//DEADCODE DAW 29/01/00 	int i = 0;
//DEADCODE DAW 29/01/00 	while	(		(i < Debrief::DISISITFORTODAY)
//DEADCODE DAW 29/01/00 				&&	(debrief.disday[i].msgtextid != 0)
//DEADCODE DAW 29/01/00 			)
//DEADCODE DAW 29/01/00 	{
//DEADCODE DAW 29/01/00 		if (	debrief.disday[i].msgtextid==msgtextid 
//DEADCODE DAW 29/01/00 			&&	debrief.disday[i].typeflag == type
//DEADCODE DAW 29/01/00 			&&	debrief.disday[i].msgowner == msgowner)
//DEADCODE DAW 29/01/00 			return;
//DEADCODE DAW 29/01/00 		i++;
//DEADCODE DAW 29/01/00 	}
//DEADCODE DAW 29/01/00 	//make sure we get last one requested							  //RDH 28/05/99
//DEADCODE DAW 29/01/00 	if (i >= Debrief::DISISITFORTODAY)
//DEADCODE DAW 29/01/00 		i = Debrief::DISISITFORTODAY - 1;
//DEADCODE DAW 29/01/00 //DEADCODE RDH 28/05/99 	if (i < Debrief::DISISITFORTODAY)
//DEADCODE DAW 29/01/00 //DEADCODE RDH 28/05/99 	{
//DEADCODE DAW 29/01/00 		debrief.disday[i].typeflag = type;
//DEADCODE DAW 29/01/00 		debrief.disday[i].msgowner = msgowner;
//DEADCODE DAW 29/01/00 		debrief.disday[i].msgtextid = msgtextid;
//DEADCODE DAW 29/01/00 		FileNum smack = FindSmacker(i);
//DEADCODE DAW 29/01/00 		if (smack)
//DEADCODE DAW 29/01/00 		{
//DEADCODE DAW 29/01/00 			msgwithsmacker =  (int)msgtextid;
//DEADCODE DAW 29/01/00 			smacker = smack;
//DEADCODE DAW 29/01/00 		}
//DEADCODE DAW 29/01/00 }
//DeadCode JIM 18Oct00 void Campaign::MakeNewPilot(int pilot)
//DeadCode JIM 18Oct00 {
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 	/**/Active_Pilots[pilot].name.nameref = Math_Lib.rnd(150);
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 	Active_Pilots[pilot].status = NOTFLYING;
//DeadCode JIM 18Oct00 }
//DeadCode JIM 18Oct00 void Campaign::KillPilot(int pilot, pilotstatus status)
//DeadCode JIM 18Oct00 {
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 	
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 	if (/**/dead_pilots[/**/nextdeadpilot].lastdate != 0)
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 			 /**/ripdate = /**/dead_pilots[/**/nextdeadpilot].lastdate;
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 	/**/dead_pilots[/**/nextdeadpilot].name = /**/Active_Pilots[pilot].name;
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 	/**/dead_pilots[/**/nextdeadpilot].kills = /**/Active_Pilots[pilot].kills;
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 	/**/dead_pilots[/**/nextdeadpilot].rank = /**/Active_Pilots[pilot].rank;
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 	/**/dead_pilots[/**/nextdeadpilot].lastdate = /**/currdate;
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 	/**/dead_pilots[/**/nextdeadpilot].status =  status;
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 	MakeNewPilot(pilot);
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 	/**/nextdeadpilot++;
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 	if	(/**/nextdeadpilot >= CASUALTYLIST)
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 		/**/nextdeadpilot = 0;
//DeadCode JIM 18Oct00 }
//DeadCode JIM 18Oct00 
//DeadCode JIM 18Oct00 void	Campaign::MoveDeadPilots()
//DeadCode JIM 18Oct00 {
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 		for(int pilot=0;pilot<119;pilot++)
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 		{  	
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 			if (/**/Active_Pilots[pilot].status >= IS_DEAD)
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 			{
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 				int groupnum = pilot/24;
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 				if (groupnum < 5)
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 					MMC.squad[groupnum].ac_total_avail--;
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 				if (MMC.squad[groupnum].ac_total_avail < 0)
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 					MMC.squad[groupnum].ac_total_avail = 0;
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 				if (pilot != (/**/playersquadron*24+/**/playeracnum))
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 					//don't move the player, picked up later and means an end campaign
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 						 KillPilot(pilot, /**/Active_Pilots[pilot].status);
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 			}
//DeadCode JIM 18Oct00 //DEADCODE DAW 24/11/99 		}
//DeadCode JIM 18Oct00 
//DeadCode JIM 18Oct00 }

//DeadCode JIM 18Oct00 void	Campaign::SetCurrMission (MissionType* newmission)
//DeadCode JIM 18Oct00 {
//DeadCode JIM 18Oct00 
//DeadCode JIM 18Oct00 //	PilotType	temppilot;
//DeadCode JIM 18Oct00 //	SWord i,j;
//DeadCode JIM 18Oct00 //	currmission = newmission;
//DeadCode JIM 18Oct00  //	SWord	sinwind,coswind;
//DeadCode JIM 18Oct00 //rdh	weathernum =	currmission->weathernum;
//DeadCode JIM 18Oct00 //	wind.speed =	currmission->windspeed;
//DeadCode JIM 18Oct00 //	wind.direction =	currmission->winddirection;
//DeadCode JIM 18Oct00 //	Math_Lib.high_sin_cos((ANGLES)(wind.direction + ANGLES_180Deg),sinwind,coswind);
//DeadCode JIM 18Oct00 //	wind.velx = wind.speed * sinwind/ ANGLES_FRACT;
//DeadCode JIM 18Oct00 //	wind.velz = wind.speed * coswind/ ANGLES_FRACT;
//DeadCode JIM 18Oct00 
//DeadCode JIM 18Oct00 //	currdate = currmission->missiondate;
//DeadCode JIM 18Oct00 //	currtime = currmission->timeofday;
//DeadCode JIM 18Oct00 
//DeadCode JIM 18Oct00 //	switch (Miss_Man.currcampaignnum)
//DeadCode JIM 18Oct00 //	{
//DeadCode JIM 18Oct00 //		case MissMan::PEACETALKCAMPAIGN:
//DeadCode JIM 18Oct00 //			{
//DeadCode JIM 18Oct00 //DeadCode RDH 17Feb97				{
//DeadCode JIM 18Oct00 //DeadCode RDH 17Feb97 //DeadCode JIM 06Nov96					dawntime = MAYDAWNTIME;
//DeadCode JIM 18Oct00 //DeadCode RDH 17Feb97 //DeadCode JIM 06Nov96					dusktime = MAYDUSKTIME;
//DeadCode JIM 18Oct00 //DeadCode RDH 17Feb97				}else
//DeadCode JIM 18Oct00 //DeadCode RDH 17Feb97				{
//DeadCode JIM 18Oct00 //					dawntime = OCTOBERDAWNTIME;
//DeadCode JIM 18Oct00 //					dusktime = OCTOBERDUSKTIME;
//DeadCode JIM 18Oct00 //DeadCode RDH 17Feb97				}
//DeadCode JIM 18Oct00 //				break;
//DeadCode JIM 18Oct00 //			}
//DeadCode JIM 18Oct00 //		case MissMan::INTROCAMPAIGN:
//DeadCode JIM 18Oct00 //			{
//DeadCode JIM 18Oct00 //DeadCode JIM 06Nov96				dawntime = MARCHDAWNTIME;
//DeadCode JIM 18Oct00 //DeadCode JIM 06Nov96				dusktime = MARCHDUSKTIME;
//DeadCode JIM 18Oct00 //				break;
//DeadCode JIM 18Oct00 //			}
//DeadCode JIM 18Oct00 //		case MissMan::SO51_CAMPAIGN:
//DeadCode JIM 18Oct00 //			{
//DeadCode JIM 18Oct00 //killed 24/6/98
//DeadCode JIM 18Oct00 //				for (i=0;i<MAX_PACKAGE_NUM;i++)
//DeadCode JIM 18Oct00 //					 package[i].familytype = PFT_NULL;
//DeadCode JIM 18Oct00 
//DeadCode JIM 18Oct00 
//DeadCode JIM 18Oct00 //DeadCode JIM 06Nov96				dawntime = NOVEMBERDAWNTIME;
//DeadCode JIM 18Oct00 //DeadCode JIM 06Nov96				dusktime = NOVEMBERDUSKTIME;
//DeadCode JIM 18Oct00 //				break;
//DeadCode JIM 18Oct00 //			}
//DeadCode JIM 18Oct00 //	}
//DeadCode JIM 18Oct00 //DEAD	playerbfield =	newmission->playerbf;
//DeadCode JIM 18Oct00 
//DeadCode JIM 18Oct00 
//DeadCode JIM 18Oct00 //killed 24/6/98
//DeadCode JIM 18Oct00 //	if (	(Miss_Man.currcampaignnum != MissMan::SO51_CAMPAIGN)//RDH 02Apr97
//DeadCode JIM 18Oct00 //		)														//RDH 02Apr97
//DeadCode JIM 18Oct00 //	{															//RDH 02Apr97
//DeadCode JIM 18Oct00 //		SLong acleft =	newmission->numofsquadronac;
//DeadCode JIM 18Oct00 //		for (j=0;j<MAXPLAYERWINGS;j++)							//RDH 02Apr97
//DeadCode JIM 18Oct00 //		{
//DeadCode JIM 18Oct00 //			for (i=0;i<MAX_FLIGHT_NUM;i++)							//RDH 02Apr97
//DeadCode JIM 18Oct00 //			{														//RDH 02Apr97
//DeadCode JIM 18Oct00 //				if (acleft >= newmission->numofflightac)
//DeadCode JIM 18Oct00 //				{
//DeadCode JIM 18Oct00 //					squad[j].flightnum [i] = newmission->numofflightac;//RDH 02Apr97
//DeadCode JIM 18Oct00 //					acleft -= newmission->numofflightac;
//DeadCode JIM 18Oct00 //				}else
//DeadCode JIM 18Oct00 //				{
//DeadCode JIM 18Oct00 //					squad[j].flightnum [i] = acleft;
//DeadCode JIM 18Oct00 //					acleft = 0;
//DeadCode JIM 18Oct00 //				}
//DeadCode JIM 18Oct00 //
//DeadCode JIM 18Oct00 //				squad[j].formationnum [i] = newmission->formationtypeindex;//RDH 02Apr97
//DeadCode JIM 18Oct00 //			}
//DeadCode JIM 18Oct00 //			 squad[j].squadronform = newmission->formationtypeindex;//RDH 02Apr97
//DeadCode JIM 18Oct00 //		}
//DeadCode JIM 18Oct00 //	}															//RDH 02Apr97
//DeadCode JIM 18Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecayingLossRate
//Author		Jim
//Date			Mon 5 Jun 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
float& LastWeekReview::DecayingLossRate(PlaneTypeSelect	actype)
{
	switch(actype)
	{
	case	PT_SPIT_A:
	case	PT_SPIT_B:	return rafloss[0];
	case	PT_HURR_A:
	case	PT_HURR_B:	return rafloss[1];
	case	PT_ME109:	return lwloss[0];	
	case	PT_ME110:	return lwloss[1];	
	case	PT_JU87:	return lwloss[2];	
	case	PT_DO17:	
	case	PT_JU88:	
	case	PT_HE111:;
	}
	return lwloss[3];
}


//////////////////////////////////////////////////////////////////////
//
// Function:    Note
// Date:		25/05/00
// Author:		JIM
//
//Description: Returns current level of the stat
//
//////////////////////////////////////////////////////////////////////
void LastWeekReview::SetNote(enum PlaneTypeSelect pt,enum PeriodReview::ReviewType rv,int newvalue)
{
	TypeStats* record;
	switch(pt)
	{
	default_neverreferenced;
	case	PT_SPIT_A:
	case	PT_SPIT_B:	record=raf+0;	break;
	case	PT_HURR_A:
	case	PT_HURR_B:	record=raf+1;	break;
	case	PT_ME109:	record=lw+0;	break;
	case	PT_ME110:	record=lw+1;	break;
	case	PT_JU87:	record=lw+2;	break;
	case	PT_DO17:	record=lw+3;	break;
	case	PT_JU88:	record=lw+4;	break;
	case	PT_HE111:	record=lw+5;	break;
	}
	record->totalkills[rv]=newvalue;
}

int LastWeekReview::Note(enum PlaneTypeSelect pt,enum PeriodReview::ReviewType rv,int delta)
{
	if (delta==0)
		return 0;
	TypeStats* record;int offset;
	switch(pt)
	{
	default_neverreferenced;
	case	PT_SPIT_A:
	case	PT_SPIT_B:	record=raf;offset=+0;		break;
	case	PT_HURR_A:
	case	PT_HURR_B:	record=raf;offset=+1;		break;
	case	PT_ME109:	record=lw;offset=+0;		break;
	case	PT_ME110:	record=lw;offset=+1;		break;
	case	PT_JU87:	record=lw;offset=+2;		break;
	case	PT_DO17:	record=lw;offset=+3;		break;
	case	PT_JU88:	record=lw;offset=+4;		break;
	case	PT_HE111:	record=lw;offset=+5;		break;
	}
	switch(rv)
	{
	case DESTROY:
		if (pt>PT_GER_FLYABLE)
		{
			lwtodaylosses+=delta;
			if (offset>2)
				lwloss[2]+=delta;
			else
				lwloss[offset]+=delta;

			lw[offset].totallosses += delta;							//RJS 12Nov00
		}
		else
		{
			raftodaylosses+=delta;
			if (pt>=PT_HURR_A)
				acproductiondelta[1]-=delta;
			else
				acproductiondelta[0]-=delta;
			rafloss[offset]+=delta;

			raf[offset].totallosses += delta;							//RJS 12Nov00
		}
	break;
	case CREATE:
		if (pt<PT_GER_FLYABLE)
			if (pt>=PT_HURR_A)
				acproductiondelta[1]+=delta;
			else
				acproductiondelta[0]+=delta;
	break;
	}
	return (record[offset].totalkills[rv]+=delta);
}

int LastWeekReview::Note(enum PlaneTypeSelect claimer,enum PlaneTypeSelect claim,int delta)
{
	if (delta==0)
		return 0;
	LastWeekReview::ReviewType rv=KILL2;
	switch(claim)
	{
	case	PT_ME109:
	case	PT_SPIT_A:
	case	PT_SPIT_B:	rv=KILL0;	break;
	case	PT_ME110:
	case	PT_HURR_A:
	case	PT_HURR_B:	rv=KILL1;	break;
	default:;
	}
	return Note(claimer,rv,delta);	
}

void	LastWeekReview::ClearToday()
{
//DEADCODE DAW 05/06/00 	int	lwtodaylosses,lwrecordlosses;
//DEADCODE DAW 05/06/00 	int	raftodaylosses,rafrecordlosses;
//DEADCODE DAW 05/06/00 	int	acproductiondelta[2],dayssincedeltapos[2];
	if (lwtodaylosses>=lwrecordlosses)
		lwrecordlosses=lwtodaylosses+5;	//won't report until this delta exceeded
	if (raftodaylosses>=rafrecordlosses)
		rafrecordlosses=raftodaylosses+5;	//won't report until this delta exceeded
	lwtodaylosses=0;
	raftodaylosses=0;
	if (acproductiondelta[0]<0)
		dayssincedeltapos[0]++;
	if (acproductiondelta[1]<0)
		dayssincedeltapos[1]++;
	acproductiondelta[0]=acproductiondelta[1]=0;
	rafloss[0]*=0.90;
	rafloss[1]*=0.90;
	lwloss[0]*=0.90;
	lwloss[1]*=0.90;
	lwloss[2]*=0.90;
}
