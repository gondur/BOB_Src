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

//deadcode JIM 18/06/01	//------------------------------------------------------------------------------
//deadcode JIM 18/06/01	//Filename       node.cpp
//deadcode JIM 18/06/01	//System         
//deadcode JIM 18/06/01	//Author         R. Hyde 
//deadcode JIM 18/06/01	//Date           Wed 19 Feb 1997
//deadcode JIM 18/06/01	//Description    MiG Alley only
//deadcode JIM 18/06/01	//------------------------------------------------------------------------------
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	//jobs:
//deadcode JIM 18/06/01	//
//deadcode JIM 18/06/01	//
//deadcode JIM 18/06/01	//
//deadcode JIM 18/06/01	//
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	#include	"dosdefs.h"
//deadcode JIM 18/06/01	#include	"files.g"
//deadcode JIM 18/06/01	#include	"worldinc.h"
//deadcode JIM 18/06/01	#include	"node.h"
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	enum	{DAYS0 = 0};
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	#define	T SupplyTree
//deadcode JIM 18/06/01	SupplyNode*const	T::FirstNode=&N0_0_Dangdong;
//deadcode JIM 18/06/01	SupplyNode
//deadcode JIM 18/06/01	//this must be the first node
//deadcode JIM 18/06/01	T::N0_0_Dangdong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_1_Sinuiju,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSunan,UID_AfRdAntung,UID_AfRdUiju},
//deadcode JIM 18/06/01				/*associated_item*/	UID_WhRdDangDong,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_MAXSUPPLY,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_MAXSUPPLY,	
//deadcode JIM 18/06/01				/*route[3]*/		{NULL},	
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_0_1Rail0,				//wrong&R0_0_1Rail
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N0_1_Sinuiju =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_2_Yomju,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinuiju,UID_AfRdSinuijuNE,UID_AfRdUiju},
//deadcode JIM 18/06/01				/*associated_item*/	UID_WhRdSinuiju,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_0_1Rail0},					//wrong{&R0_0_1Rail},							
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_1_2Rail0,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},		
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_2_Yomju =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_3_Sonchon,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinuiju,UID_AfRdSinuijuNE,UID_AfRdUiju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SCCYomju,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_1_2Rail0},												
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_2_3Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_3_Sonchon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_4_Chongju,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinuiju,UID_AfRdSinuijuNE,UID_AfRdNamsi},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SdRdSonchon,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_2_3Rail},												
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_3_4Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_4_Chongju =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_4b_Maenjungdong,	//FIXED (was N0_5_Suiho)
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSaamcham,UID_AfRdSinanju,UID_AfRdNamsi},
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChongju,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_3_4Rail},												
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_4_4bRail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_4b_Maenjungdong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_5_Sinaju,	//FIXED (was N0_5_Suiho)
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSaamcham,UID_AfRdSinanju,UID_AfRdNamsi},
//deadcode JIM 18/06/01				/*associated_item*/	UID_StMaenjungdong,				//MS 26Oct98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_4_4bRail},												
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_4b_5Rail0,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_57_Suiho =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_46_Chongsongup,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_HEPSuihu,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_57_46Road},												
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_57_46Road,		//BADLINK PROBLEM
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N0_46_Chongsongup =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_48_Kusong,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChongsongup,//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_57_46Road},												
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_46_48Road,
//deadcode JIM 18/06/01							},			
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_48_Kusong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_44_Namsanni,		//INCORRECT 4 Chongju
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSinanju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKusong,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_46_48Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_48_4Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N0_44_Namsanni =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_45_Sakchu,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StNamsanni,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_44_45Rail},	
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_44_45Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N0_45_Sakchu =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_60_Chosan,		//INCORRECT 48 Kusong
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SCCSakchu,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,																					
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,																					
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_44_45Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_45_48Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_60_Chosan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_59_Chosin,			//INCORRECT
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SCCChosan,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_60_11Road},													
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_60_11Road,			//BADLINK Problem
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N0_59_Chosin =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_51_Pungsan,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_HEPChosin,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_9_59Road},													
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_59_19Road,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_51_Pungsan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_33_Kapsan,	//INCORRECT 37 Purchong
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StPungsan,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_9_51Road},													
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_51_37Road,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N0_33_Kapsan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_32_Hyesan,	//INCORRECT 51 Pungsan
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKapsan,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_32_33Road},													
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_33_51Road,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N0_32_Hyesan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_5_Sinaju,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdAntung,UID_AfRdSinuijuNE,UID_AfRdUiju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StHyesan,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_32_33Road},													
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_32_33Road,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01									
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_5_Sinaju =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_16_Chongjin,		//INCORRECT 6 Sukchon
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinanju,UID_AfRdSaamcham,UID_AfRdPyongni},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StSinanju,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_4b_5Rail0},					
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_5_6Rail,								
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_16_Chongjin =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_56_Kyongsong,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_MyRlChongjin,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_MAXSUPPLY,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_MAXSUPPLY,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_16_56Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_16_56Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_56_Kyongsong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_17_Kilchu,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKyongsong,//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_16_56Rail},				
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_56_17Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_17_Kilchu =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_18_Kimchaek,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKilchu,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_56_17Rail},				
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_17_18Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_18_Kimchaek =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_50_Tanchon,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_MSPKimchaek,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_17_18Rail},				
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_18_50Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_50_Tanchon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_37_Pukchong,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_MSPTanchon,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_18_50Rail},				
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_50_37Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_37_Pukchong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_19_Hamhung,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StPukchong,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_50_37Rail},				
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_37_19Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_19_Hamhung =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_8_Manpo,		//INCORRECT 34 Yonchung
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdNamsi,UID_AfRdTaechon,UID_AfRdSaamcham},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_MyRdHamhung,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_37_19Rail},				
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_19_34Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_8_Manpo =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_9_Kangye,
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinuiju,UID_AfRdSinuijuNE,UID_AfRdUiju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SCCManpo,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_MAXSUPPLY,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_MAXSUPPLY,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_8_9Rail},					//BADLINK
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_8_9Rail,					//BADLINK
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_9_Kangye =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_58_SinmiDo,		//INCORRECT 10 Huichon
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinuiju,UID_AfRdSinuijuNE,UID_AfRdUiju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SCCKangye,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_8_9Rail},				
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_9_10Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N0_58_SinmiDo =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_10_Huichon,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinuiju,UID_AfRdSinuijuNE,UID_AfRdUiju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_FCSinmiDo,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_3_58Road},				
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_3_58Road,		
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_10_Huichon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_11_Kujang,
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinanju,UID_AfRdSaamcham,UID_AfRdTaechon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SCCHuichon,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_9_10Rail},				
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_10_11Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_11_Kujang =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N0_31_Tokchon,
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinanju,UID_AfRdSaamcham,UID_AfRdTaechon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKujang,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_10_11Rail},				
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_11_31Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N0_31_Tokchon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_6_Sukchon,
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinanju,UID_AfRdSaamcham,UID_AfRdTaechon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StTokchon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_11_31Rail},				
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R0_31_13Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	//------------------------------------------------------------------------------
//deadcode JIM 18/06/01	//supply nodes for area 1
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_6_Sukchon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_29_Kangdong,	//INCORRECT	7 Pyongyang
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdYongyu,UID_AfRdSinanju,UID_AfRdPyongni},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_WhRdSukchon,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_6_7Rail},	//BADLINK	&R0_5_6Rail		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_6_7Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_29_Kangdong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_54_YulLi,
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongyangE,UID_AfRdPyongni},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKangdong,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_13_29Rail},				
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_29_54Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_54_YulLi =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_7_Pyongyang,
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongyangE,UID_AfRdPyongni},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StYulLi,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_29_54Rail},				
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_29_54Rail,					
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_7_Pyongyang =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_30_Nampo,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSunan,UID_AfRdAntung,UID_AfRdUiju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_MyRdPyongyang,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_6_7Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_1_W7_UN,	
//deadcode JIM 18/06/01				/*forward*/			&R1_7_49Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_30_Nampo =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_49_Hwangju,	//INCORRECT
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdPyongyangD,UID_AfRdAnak,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_ICMPNampo,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_7_30Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_7_30Rail,	//BADLINK	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_49_Hwangju =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_41_Ichon,	//INCORRECT
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdPyongyangD,UID_AfRdAnak,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StHwangju,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_7_49Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_49_22Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_41_Ichon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_22_Sariwon,	//INCORRECT 28 pyonggang
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,	//INCORRECT	central
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdSinmak,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SdRdIchon,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_25_41Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_41_28Road,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_22_Sariwon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_25_Pyongsan,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSunan,UID_AfRdAntung,UID_AfRdAnak},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StSariwon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_7_49Rail},	//BADLINK	R1_49_22Rail 
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_1_W6_UN,	
//deadcode JIM 18/06/01				/*forward*/			&R1_49_22Rail,	//BADLINK
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_25_Pyongsan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_26_Kumchon,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSunan,UID_AfRdAntung,UID_AfRdAnak},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StPyongsan,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_22_25Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_25_26Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_26_Kumchon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_62_Chaeryong,	//INCORRECT 27 Kaesong
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdAnak,UID_AfRdSunan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SdRdKumchon,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_25_26Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_26_27Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_62_Chaeryong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_24_Haeju,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdAnak,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChaeryong,//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_22_62Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_62_24Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_24_Haeju =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_61_Yonan,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdAnak,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StHaeju,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_62_24Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_24_61Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_61_Yonan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_69_Kalmal, //INCORRECT 27 Kaesong
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdAnak,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StYonan,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_24_61Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_61_27Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_69_Kalmal =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_27_Kaesong, //INCORRECT
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01		   		/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdAnak,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKalmal,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_38_69Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_38_69Road, //BADLINK69 49 b
//deadcode JIM 18/06/01																		   
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_27_Kaesong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_75_Panmunjom,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdAnak,UID_AfRdSariwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SdRdKaesong,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_26_27Rail},	
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_1_W5_Red,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_1_W5_UN,	
//deadcode JIM 18/06/01				/*forward*/			&R1_27_75Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},		
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_75_Panmunjom =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_34_Yonghung,	//INCORRECT 40b Munsan
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdAnak,UID_AfRdSariwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_MyRdPanmunjom,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_27_75Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_75_40Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_34_Yonghung =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_12_Sunchon,		//INCORRECT 20a Kowon
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdAnak,UID_AfRdSariwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StYonghung,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_19_34Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_34_20Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_12_Sunchon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_20_Kowon,		//INCORRECT 7 Pyongyang
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinanju,UID_AfRdPyongni,UID_AfRdSunan},
//deadcode JIM 18/06/01				/*associated_item*/	UID_StSunchon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_11_12Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_12_7Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01			
//deadcode JIM 18/06/01	T::N1_20_Kowon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_21_Wonsan,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdAnak,UID_AfRdSariwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKowon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_34_20Rail},	//BADLINK IN Node.CPP!	
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_20_21Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_21_Wonsan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_52_Kojo,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdAnak,UID_AfRdSariwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_MyRlWonsan,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_20_21Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_21_52Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_52_Kojo =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_35_Kojin ,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSinmak,UID_AfRdAnak,UID_AfRdSariwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKojo,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_21_52Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_52_35Rail,
//deadcode JIM 18/06/01			
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_35_Kojin  =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_64_Sangwon ,		//INCORRECT 35 Kosong
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKojin ,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_52_35Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_35_42Rail,
//deadcode JIM 18/06/01				
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_64_Sangwon  =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_65_Nuang ,			// INCORRECT 54 Yul-li
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdPyongyangE,UID_AfRdKangdong,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StSangwon ,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_7_64Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_64_54Road,
//deadcode JIM 18/06/01				
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_65_Nuang  =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_63_Suan ,   //INCORRECT 54 Yul-li
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdPyongyangE,UID_AfRdKangdong,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StNuang ,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_22_65Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_65_54Road,
//deadcode JIM 18/06/01				
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_63_Suan  =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_66_Singye ,		//INCORRECT 54 Yul-li
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdPyongyangE,UID_AfRdKangdong,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StSuan ,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_25_63Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_63_54Road,
//deadcode JIM 18/06/01				
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_66_Singye  =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_42_Kansang,		//INCORRECT 53 Koksan
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdPyongyangE,UID_AfRdKangdong,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StSingye ,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_25_66Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_66_53Road,
//deadcode JIM 18/06/01				
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_42_Kansang =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_70_Hwachon,		// INCORRECT 36 Yangyang
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKansang,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_35_42Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_42_36Rail,
//deadcode JIM 18/06/01				
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_70_Hwachon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_50_Yongpyong,	//INCORRECT 12 Chunchon
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StHwachon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_38_70Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_70_12Road,
//deadcode JIM 18/06/01				
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_50_Yongpyong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_68_Changdo,  // INCORRECT 12 Chunchon
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StYongpyong,//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_38_50Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_50_12Road,
//deadcode JIM 18/06/01				
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_68_Changdo =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_53_Koksan,		//INCORRECT 38 Kumhwa
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChangdo,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_40_68Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_68_38Road,
//deadcode JIM 18/06/01				
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_53_Koksan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_40_Hoeyang,		// INCORRECT 55 Majon
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKoksan,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_15_53Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_15_55Road,
//deadcode JIM 18/06/01				
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_40_Hoeyang =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_38_Kumhwa,		// INCORRECT 68 Changdo
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StHoeyang,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_39_40Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_40_68Road,
//deadcode JIM 18/06/01				
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_38_Kumhwa =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_36_Yangyang,	//INCORRECT 69 Kalmal
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKumhwa,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_68_38Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_1_C4_Red,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_38_69Road,
//deadcode JIM 18/06/01				
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_36_Yangyang =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_13_Samdung,	//INCORRECT 29 Kangnung
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StYangyang,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_35_42Rail},		//BADLINK 42_36Rail
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_36_29Road,
//deadcode JIM 18/06/01				
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_13_Samdung =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_23_Changyon,	//INCORRECT 14 Wa-Dong
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSaamcham,UID_AfRdPyongni,UID_AfRdSinanju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StSamdung,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R0_31_13Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_13_14Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_23_Changyon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_14_WaDong ,		//INCORRECT
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdAnak,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChangyon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_62_23Rail},	//BADLINK NONE!	
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_62_23Rail,		//BADLINK NONE!
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_14_WaDong  =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_15_Yangdok ,	
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongni,UID_AfRdSunan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_CPWaDong,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_13_14Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_14_15Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_15_Yangdok  =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_39_Kosan ,		//  INCORRECT 20 Kowon	
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongni,UID_AfRdPyongyangE},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StYangdok ,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_14_15Rail},			
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_15_20Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_39_Kosan  =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_67_Sepo ,
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongni,UID_AfRdPyongyangE},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKosan ,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_21_39Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_39_67Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_67_Sepo  =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_71_Inje ,		//INCORRECT 28 Pyonggang
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongni,UID_AfRdPyongyangE},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StSepo ,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_39_67Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_39_67Rail,		//BADLINK 67_28RAIL
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N1_71_Inje  =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_28_Pyonggang ,	//INCORRECT 12 Chunchon
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdKangdong,UID_AfRdPyongni,UID_AfRdPyongyangE},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StInje ,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_42_71Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_71_12Road0,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_28_Pyonggang  =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_43_Chorwon ,
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdSinmak,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StPyonggang ,//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_67_28Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_28_43Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_43_Chorwon  =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N1_55_Kanda ,		 //INCORRECT ????!
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdSinmak,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChorwon ,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_28_43Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_43_56Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_55_Kanda  =	{								//INCORRECT THIS NODE DOES NOT
//deadcode JIM 18/06/01				/*nextnode*/		&N1_56_Yonchon ,	//EXIst
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDREDLINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdSinmak,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKanda ,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_15_55Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_55_21Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N1_56_Yonchon  =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_40_Munsan,		//INCORRECT 11 Uijongbu
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			BATTLEFIELD,
//deadcode JIM 18/06/01				/*status*/			FRONTLINE,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfRdSariwon,UID_AfRdSinmak,UID_AfRdHwangju},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StYonchon ,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_TODISCOURAGEBLUEATTACK,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_TOINITIATEASSAULT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_43_56Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R1_56_11Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	//-------------------------------------------------------------------------------
//deadcode JIM 18/06/01	//Supply Nodes for area 2
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N2_40_Munsan={
//deadcode JIM 18/06/01				/*nextnode*/		&N2_10_Seoul,		
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			BATTLEFIELD,
//deadcode JIM 18/06/01				/*status*/			FRONTLINE,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlChuncheon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_MyBlMunsan,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_TODISCOURAGEBLUEATTACK,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_TOINITIATEASSAULT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_75_40Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_1_W4_Red,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_1_W4_UN,	
//deadcode JIM 18/06/01				/*forward*/			&R2_40_10Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N2_10_Seoul={
//deadcode JIM 18/06/01				/*nextnode*/		&N2_7_Suwon,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_MyBlSeoul,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_40_10Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_1_W3_UN,	
//deadcode JIM 18/06/01				/*forward*/			&R2_10_7Rail,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},		
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N2_7_Suwon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_14_Osan,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlSeoul,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SdBlSuwon,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_10_7Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_7_14Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N2_14_Osan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_29_Kangnung,	// INCORRECT 19 Pyongtaek
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_MyBlOsan,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_7_14Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_1_W2_Red,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_1_W2_UN,	
//deadcode JIM 18/06/01				/*forward*/			&R2_14_19Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N2_29_Kangnung =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_28_Samchok,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSeoul},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKangnung,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_36_29Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_29_28Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N2_28_Samchok =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_49_Pochon,		//INCORRECT 30 Ulhin
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlPohang},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StSamchok,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_29_28Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_28_30Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N2_49_Pochon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_12_Chuncheon,	//INCORRECT 11 Uijongbu
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlPohang},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StPochon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_69_49Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_49_11Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N2_12_Chuncheon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_48_Kuri,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlPohang},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChuncheon,//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_71_12Road0},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_12_48Road0,
//deadcode JIM 18/06/01				/*priority*/		SP_NONE,
//deadcode JIM 18/06/01				/*serviced*/		false,
//deadcode JIM 18/06/01				/*populate*/		FIL_1_Chunchon,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N2_48_Kuri =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_35_Hongchon,		//INCORRECT 10 Seoul
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlPohang},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_MyBlKuri,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_12_48Road0},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_48_10Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N2_35_Hongchon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_23_Hoensong,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SdRdHongchon,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_12_35Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_35_23Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N2_23_Hoensong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_34_Yulchon,		//INCORRECT 6 Wonju
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StHoensong,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_35_23Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_23_6Road,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N2_34_Yulchon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_43_Pyongchang,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StYulchon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_57_34Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_34_43Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N2_43_Pyongchang =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_57_Sangnam,	//INCORRECT 5 Chechon
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StPyongchang,//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_34_43Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_43_5Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N2_57_Sangnam =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_42_Chongson,		//INCORRECT 34 Yulchon
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StSangnam,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R1_71_57Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_57_34Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N2_42_Chongson =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_9_Inchon,		//INCORRECT 28 Samchok
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			BATTLEFIELD,
//deadcode JIM 18/06/01				/*status*/			FRONTLINE,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChongson,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_TODISCOURAGEBLUEATTACK,	
//deadcode JIM 18/06/01				/*maxstores*/		STORES_TOINITIATEASSAULT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_43_42Road},			
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_42_28Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N2_9_Inchon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_39_Kimpo,		// INCORRECT 7 Suwon
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,			// INCORRECT WEST!
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlSuwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StInchon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_10_9Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_10_9Road,		//BADLINK 9-7	
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N2_39_Kimpo	=	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_8_Songnam,		// INCORRECT 10 Seoul
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlSuwon},
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKimpo,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_10_9Road},		//BADLINK 40-39
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_10_9Road,		//BADLINK 39-10			
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N2_8_Songnam =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_41_Ichon,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlSuwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StSongnam,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_10_8Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_8_41Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N2_41_Ichon=	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_11_Uijongbu,	//INCORRECT 26 Changhowon
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKimpo,UID_AfBlSeoul,UID_AfBlSuwon},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StIchon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_8_41Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_41_26Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N2_11_Uijongbu =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_58_Yangpyong,		// INCORRECT 48 or 10
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlPohang},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StUijongbu,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_29_28Road},		//BADLINK!
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_28_30Road,			//BADLINK!
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N2_58_Yangpyong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N2_6_Wonju,		
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlPohang},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StYangpyong,//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_10_58Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_58_6Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N2_6_Wonju =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_19_Pyongtaek,	// INCORRECT 5 Chechon
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlChuncheon,UID_AfBlPohang},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StWonju,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_58_6Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R2_6_5Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//deadcode JIM 18/06/01	//Supply Nodes for area 3
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_19_Pyongtaek =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_3_Chonan,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SdBlPyongtaek,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_14_19Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_19_3Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_3_Chonan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_36_Mokkye,		//INCORRECT 17 Chochiwon
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SdBlChonan,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_19_3Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_1_W1_Red,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_1_W1_UN,	
//deadcode JIM 18/06/01				/*forward*/			&R3_3_17Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_36_Mokkye =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_44_Taepaek,		//INCORRECT 4 Chungju
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StMokkye,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_6_36Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_36_4Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_44_Taepaek =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_62_Noktong,		
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StTaepaek,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_28_44Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_44_62Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_62_Noktong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_20_Yechon,		//INCORRECT 16 Yongju
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StNoktong,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_44_62Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_62_16Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_20_Yechon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_24_Chomchon,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StYechon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_18_20Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_20_24Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_24_Chomchon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_21_Sangju,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChomchon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_24_21Road},		//BADLINK 20_24Road
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_21_22Road,			//BADLINK 24_21Road/Rail
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_21_Sangju =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_2_Chongju,			//INCORRECT 22 Kimchon
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StSangju,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_24_21Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_21_22Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_2_Chongju =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_8_Songnam,			//INCORRECT PROBLEM!
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChongju,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_59_2Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_2_1Rail,			//BADLINK PROBLEM!
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_8_Songnam =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_64_Hongsong,	//INCORRECT 8_41 or 8_7
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlSeoul,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StSongnam,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_59_2Rail},		//BADLINK 8_8 or 10_8
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_2_1Rail,		//BADLINK 8_7
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_64_Hongsong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_65_Hannae,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlTaejon,UID_AfBlPyongtaek},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SdBlHongsong,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_3_64Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_64_65Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_65_Hannae =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_51_Maesan,		//INCORRECT 66 Taechon
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StHannae,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_64_65Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_65_66Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_51_Maesan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_52_Kwangheywan,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StMaesan,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_41_51Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_51_52Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_52_Kwangheywan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_53_Chinchon,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKwangheywan,//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_51_52Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_52_53Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_53_Chinchon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_54_Chungpyong,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChinchon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_52_53Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_53_54Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_54_Chungpyong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_60_Mungyong,   //INCORRECT 2 Chongju
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChungpyong,//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_53_54Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_54_2Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_60_Mungyong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_61_Tanyang,		//INCORRECT 24 Chomchon
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StMungyong,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_4_60Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_60_24Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_61_Tanyang =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_55_Uisong,		//INCORRECT 16 Yongju
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StTanyang,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALVERYSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_4_61Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_61_16Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_55_Uisong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_66_Taechon,		//INCORRECT 37 Kunwi
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKunsan,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StUisong,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_18_55Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_55_37Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_66_Taechon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_45_Nonsan,		//INCORRECT 63 Kunsan
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,			//WEST!
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StTaechon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_65_66Rail},			
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_66_63Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_45_Nonsan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_63_Kunsan,		//INCORRECT 1 Taejon
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,			//WEST!
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StNonsan,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_63_45Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_45_1Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_63_Kunsan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_15_Kongju,		//INCORRECT 45 Nonsan
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlTaejon,UID_AfBlKunsan,UID_AfBlTaegu},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKunsan,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_66_63Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_63_45Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_15_Kongju =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_4_Chungju,	//INCORRECT 1 or 45
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKongju,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_66_63Rail},	//BADLINK 3_15	
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_63_45Rail,		//BADLINK 15_45 or 15_1
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_4_Chungju =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_59_Koesan,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChungju,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_36_4Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_4_59Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_59_Koesan =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_26_Changhowon,		//INCORRECT 2 Chongju
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKoesan,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_4_59Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_59_2Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_26_Changhowon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_17_Chochiwon,	//INCORRECT 4 Chungju
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*tyxpe*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlSuwon,UID_AfBlPyongtaek,UID_AfBlOsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChanghowon,//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_43_5Road},		//BADLINK	41_26	
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_5_47Rail,		//BADLINK   26_57 or 26_4 etc
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_17_Chochiwon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_1_Taejon,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlOsan,UID_AfBlTaejon,UID_AfBlKunsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_MyBlChochiwon,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_3_17Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_17_1Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_1_Taejon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_46_Yongdong,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlOsan,UID_AfBlTaejon,UID_AfBlKunsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SdBlTaejon,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_17_1Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_1_46Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_46_Yongdong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_22_Kimchon,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlOsan,UID_AfBlTaejon,UID_AfBlKunsan},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_SdBlYongdong,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_17_1Rail},		//BADLINK 46_1
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_1_46Rail,		//BADLINK 46_22
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_22_Kimchon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_37_Kumi,
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlTaegu,UID_AfBlTaejon,UID_AfBlTaeguW},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StKimchon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALBIGSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_46_22Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_46_22Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_37_Kumi =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_30_Ulhin,			//INCORRECT NONE!
//deadcode JIM 18/06/01				/*supplyline*/		&WestRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlTaegu,UID_AfBlTaejon,UID_AfBlTaeguW},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_MyBlKumi,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_22_37Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_46_22Road,			//BADLINK PROBLEM!	
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_30_Ulhin =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_31_Yonghae,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlTaegu,UID_AfBlPohang,UID_AfBlTaeguW},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StUlhin,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_28_30Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_30_31Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_31_Yonghae =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_32_Yongdok,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlTaegu,UID_AfBlPohang,UID_AfBlTaeguW},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_MyBlYonghae,
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_28_30Road},	//BADLINK R3_30_31Road
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_31_32Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_32_Yongdok =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_25_Pohang,
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlTaegu,UID_AfBlPohang,UID_AfBlTaeguW},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StYongdok,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_31_32Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_32_25Road,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_25_Pohang =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_5_Chechon,		//INCORRECT 18 Andong
//deadcode JIM 18/06/01				/*supplyline*/		&EastRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlTaegu,UID_AfBlPohang,UID_AfBlTaeguW},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StPohang,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_32_25Road},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_32_25Road,		//BADLINK 25_18Rail
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_5_Chechon =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_47_Punggi,
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlOsan,UID_AfBlPyongtaek},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StChechon,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R2_6_5Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_5_47Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	T::N3_47_Punggi =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_16_Yongju,
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlOsan,UID_AfBlPyongtaek},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StPunggi,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_5_47Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_47_16Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_16_Yongju =	{
//deadcode JIM 18/06/01				/*nextnode*/		&N3_18_Andong,
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlOsan,UID_AfBlPyongtaek},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StYongju,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALSMALLSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_47_16Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_16_18Rail,
//deadcode JIM 18/06/01						
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01					},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::N3_18_Andong =	{
//deadcode JIM 18/06/01				/*nextnode*/		&Last_Node,
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			NOCONTEST,
//deadcode JIM 18/06/01				/*status*/			BEHINDBLUELINES,
//deadcode JIM 18/06/01				/*airfield[3]*/		{UID_AfBlKangnung,UID_AfBlOsan,UID_AfBlPyongtaek},	
//deadcode JIM 18/06/01				/*associated_item*/	UID_StAndong,	//MS 12Jun98
//deadcode JIM 18/06/01				/*currentstores*/	STORES_NIL,
//deadcode JIM 18/06/01				/*maxstores*/		STORES_INITALMEDIUMSETTLEMENT,	
//deadcode JIM 18/06/01				/*route[3]*/		{&R3_16_18Rail},		
//deadcode JIM 18/06/01				/*redfrontBF*/		FIL_NULL,		
//deadcode JIM 18/06/01				/*bluefrontBF*/		FIL_NULL,	
//deadcode JIM 18/06/01				/*forward*/			&R3_18_25Rail,
//deadcode JIM 18/06/01				},
//deadcode JIM 18/06/01	//this must be the last one!
//deadcode JIM 18/06/01	T::Last_Node = 
//deadcode JIM 18/06/01			{
//deadcode JIM 18/06/01				/*nextnode*/		&Last_Node,
//deadcode JIM 18/06/01				/*supplyline*/		&CentralRoute,		
//deadcode JIM 18/06/01				/*type*/			LASTONE,
//deadcode JIM 18/06/01			};
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	//------------------------------------------------------------------------------
//deadcode JIM 18/06/01	//supply routes for area 0
//deadcode JIM 18/06/01	SupplyRoute*const	T::FirstRoute=&WestMainSupply;
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	SupplyRoute
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::WestMainSupply={
//deadcode JIM 18/06/01				/*next*/					&R0_0_1Rail0,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_0_Dangdong,
//deadcode JIM 18/06/01				/*suppliee*/				&N0_0_Dangdong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STORES_MAXSUPPLY,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STORES_MAXSUPPLY,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01							},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_0_1Rail0= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_0_1Rail1,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_0_1Rail1,
//deadcode JIM 18/06/01				/*supplier*/				&N0_0_Dangdong,
//deadcode JIM 18/06/01				/*suppliee*/				&N0_1_Sinuiju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlYalu0,
//deadcode JIM 18/06/01							},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_0_1Rail1= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_0_1Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_0_1Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_0_Dangdong,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_1_Sinuiju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlYalu1,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_0_1Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_1_2Rail0,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_0_Dangdong,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_1_Sinuiju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdYalu,
//deadcode JIM 18/06/01					/*storeslaunched*/			0,
//deadcode JIM 18/06/01				/*stores_destroyed*/		0,
//deadcode JIM 18/06/01				/*totalstores_destroyed*/	0,
//deadcode JIM 18/06/01				/*consecutive_days_attacked*/		0,				
//deadcode JIM 18/06/01							},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_1_2Rail0= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_1_2Rail1,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_1_2Rail1,
//deadcode JIM 18/06/01				/*supplier*/				&N0_1_Sinuiju,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_2_Yomju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlSinuiju0,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_1_2Rail1= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_1_2Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_1_2Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_1_Sinuiju,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_2_Yomju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlSinuiju1,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_1_2Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_32_33Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_1_Sinuiju,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_2_Yomju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdSinuiju,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_32_33Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_3_58Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_32_Hyesan,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_33_Kapsan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_3_58Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_33_51Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_3_Sonchon,				
//deadcode JIM 18/06/01				/*suppliee*/				&N0_58_SinmiDo,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_33_51Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_51_37Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_33_Kapsan,				
//deadcode JIM 18/06/01				/*suppliee*/				&N0_51_Pungsan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_51_37Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_9_19Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_51_Pungsan,				
//deadcode JIM 18/06/01				/*suppliee*/				&N0_37_Pukchong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_9_19Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_9_59Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_9_59Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_9_Kangye,				
//deadcode JIM 18/06/01				/*suppliee*/				&N0_19_Hamhung,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdChangig,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_9_59Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_48_4Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_9_Kangye,				
//deadcode JIM 18/06/01				/*suppliee*/				&N0_59_Chosin,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_48_4Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_59_19Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_48_Kusong,				
//deadcode JIM 18/06/01				/*suppliee*/				&N0_4_Chongju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_59_19Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_11_19Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_59_Chosin,				
//deadcode JIM 18/06/01				/*suppliee*/				&N0_19_Hamhung,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_11_19Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_2_3Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_11_Kujang,				
//deadcode JIM 18/06/01				/*suppliee*/				&N0_19_Hamhung,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_2_3Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_11_12Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_2_3Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_2_Yomju,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_3_Sonchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_11_12Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_2_3Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_11_Kujang,		
//deadcode JIM 18/06/01				/*suppliee*/				&N1_12_Sunchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_2_3Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_3_4Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_2_Yomju,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_3_Sonchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_3_4Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_3_4Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_3_4Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_3_Sonchon,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_4_Chongju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_3_4Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_9_51Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_3_Sonchon,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_4_Chongju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_9_51Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_60_11Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_9_Kangye,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_51_Pungsan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdUngig,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_60_11Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_11_5Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_60_Chosan,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_11_Kujang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdChosan,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_11_5Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_11_5Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_11_5Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_11_Kujang,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_5_Sinaju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_NULL, //WAS UID_BrRlChongchon0,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_11_5Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_4b_5Rail0,	//TOTALLY WRONG!!!!
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_11_Kujang,				
//deadcode JIM 18/06/01				/*suppliee*/				&N0_5_Sinaju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_4_4bRail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_4_4bRoad,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_4_4bRoad,
//deadcode JIM 18/06/01				/*supplier*/				&N0_4_Chongju,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_4b_Maenjungdong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlTaeryong,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_4_4bRoad= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_5_6Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_4_Chongju,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_4b_Maenjungdong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdTaeryong,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_4b_5Rail0= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_4b_5Rail1,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_4b_5Rail1,
//deadcode JIM 18/06/01				/*supplier*/				&N0_4b_Maenjungdong,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_5_Sinaju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlSinanju0,
//deadcode JIM 18/06/01				},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_4b_5Rail1= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_4b_5Rail2,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_4b_5Rail2,
//deadcode JIM 18/06/01				/*supplier*/				&N0_4b_Maenjungdong,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_5_Sinaju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlSinanju1,
//deadcode JIM 18/06/01				},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_4b_5Rail2= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_4b_5Rail2,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_4b_5Rail2,
//deadcode JIM 18/06/01				/*supplier*/				&N0_4b_Maenjungdong,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_5_Sinaju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlSinanju2,
//deadcode JIM 18/06/01				},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_4b_5Rail3= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_4b_5Rail3,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_4b_5Rail3,
//deadcode JIM 18/06/01				/*supplier*/				&N0_4b_Maenjungdong,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_5_Sinaju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlSinanju3,
//deadcode JIM 18/06/01				},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_4b_5Rail4= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_4b_5Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_4b_5Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_4b_Maenjungdong,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_5_Sinaju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlSinanju4,
//deadcode JIM 18/06/01				},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_4b_5Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_5_6Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_4b_Maenjungdong,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_5_Sinaju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdSinanju,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_5_6Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_5_6Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_5_6Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_5_Sinaju,		
//deadcode JIM 18/06/01				/*suppliee*/				&N1_6_Sukchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_5_6Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_16_56Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_5_Sinaju,		
//deadcode JIM 18/06/01				/*suppliee*/				&N1_6_Sukchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_16_56Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_16_56Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_16_56Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_16_Chongjin,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_56_Kyongsong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_16_56Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_56_17Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_16_Chongjin,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_56_Kyongsong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_56_17Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_56_17Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_56_17Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_56_Kyongsong,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_17_Kilchu,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdKyongsong,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_56_17Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_17_18Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_56_Kyongsong,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_17_Kilchu,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdKyongsong,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_17_18Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_17_18Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_17_18Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_17_Kilchu,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_18_Kimchaek,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdKilchu,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_17_18Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_18_50Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_17_Kilchu,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_18_Kimchaek,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_18_50Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_18_50Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_18_50Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_18_Kimchaek,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_50_Tanchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdKimchaek,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_18_50Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_50_37Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_18_Kimchaek,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_50_Tanchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_50_37Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_50_37Road0,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_50_37Road0,
//deadcode JIM 18/06/01				/*supplier*/				&N0_50_Tanchon,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_37_Pukchong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlPuktaechon,	//2 bridges
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_50_37Road0= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_50_37Road1,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_50_37Road1,
//deadcode JIM 18/06/01				/*supplier*/				&N0_50_Tanchon,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_37_Pukchong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdTanchon0,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_50_37Road1= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_37_19Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_50_Tanchon,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_37_Pukchong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdTanchon1,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_37_19Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_37_19Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_37_19Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_37_Pukchong,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_19_Hamhung,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlNamdaechon,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_37_19Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_19_34Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_37_Pukchong,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_19_Hamhung,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_19_34Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_19_34Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_19_34Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_19_Hamhung,		
//deadcode JIM 18/06/01				/*suppliee*/				&N1_34_Yonghung,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlKumjinchon,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_19_34Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_8_9Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_19_Hamhung,		
//deadcode JIM 18/06/01				/*suppliee*/				&N1_34_Yonghung,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_8_9Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_8_9Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_8_9Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_8_Manpo,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_9_Kangye,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlManpo,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_8_9Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_9_10Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_8_Manpo,	
//deadcode JIM 18/06/01				/*suppliee*/				&N0_9_Kangye,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_9_10Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_9_10Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_9_10Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_9_Kangye,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_10_Huichon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlHuichon,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_9_10Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_10_11Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_9_Kangye,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_10_Huichon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_10_11Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_10_11Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_10_11Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_10_Huichon,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_11_Kujang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_10_11Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_11_31Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_10_Huichon,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_11_Kujang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_11_31Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_44_45Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_31_Tokchon,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_11_Kujang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_44_45Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_46_48Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_44_Namsanni,	
//deadcode JIM 18/06/01				/*suppliee*/				&N0_45_Sakchu,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_46_48Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_57_46Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_46_Chongsongup,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_48_Kusong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_57_46Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_45_48Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_57_Suiho,			
//deadcode JIM 18/06/01				/*suppliee*/				&N0_46_Chongsongup,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_45_48Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_48_4Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_46_48Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_45_Sakchu,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_48_Kusong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R0_48_4Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R0_31_13Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			&R0_48_4Road,
//deadcode JIM 18/06/01				/*supplier*/				&N0_48_Kusong,		
//deadcode JIM 18/06/01				/*suppliee*/				&N0_4_Chongju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R0_31_13Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_6_7Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N0_31_Tokchon,		
//deadcode JIM 18/06/01				/*suppliee*/				&N1_13_Samdung,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	//------------------------------------------------------------------------------
//deadcode JIM 18/06/01	//supply routes for area 1
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_6_7Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_6_7Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_6_7Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_6_Sukchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_7_Pyongyang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_6_7Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_7_30Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_6_Sukchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_7_Pyongyang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								
//deadcode JIM 18/06/01				},
//deadcode JIM 18/06/01	T::R1_7_30Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_13_29Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_7_30Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_7_Pyongyang,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_30_Nampo,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_13_29Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_13_29Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_13_Samdung,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_29_Kangdong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlChongchon1,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_13_29Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_29_54Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_13_Samdung,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_29_Kangdong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_29_54Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_49_22Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_13_Samdung,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_54_YulLi,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlNan,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_49_22Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_25_41Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_49_Hwangju,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_22_Sariwon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_25_41Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_7_64Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_25_Pyongsan,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_41_Ichon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_7_64Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_64_54Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_7_Pyongyang,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_64_Sangwon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_64_54Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_22_65Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_64_Sangwon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_54_YulLi,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_22_65Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_65_54Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_22_Sariwon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_65_Nuang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_65_54Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_25_63Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_65_Nuang,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_54_YulLi,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_25_63Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_7_30Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_25_Pyongsan,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_63_Suan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_7_30Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_62_23Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_7_Pyongyang,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_30_Nampo,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_62_23Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_15_53Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_62_Chaeryong,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_23_Changyon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_15_53Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_53_55Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_15_Yangdok,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_53_Koksan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_53_55Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_12_7Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_53_Koksan,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_55_Kanda,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_12_7Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_22_62Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_12_Sunchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_7_Pyongyang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_22_62Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_62_24Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_22_Sariwon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_62_Chaeryong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_62_24Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_24_61Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_62_Chaeryong,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_24_Haeju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_24_61Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_61_27Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_24_Haeju,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_61_Yonan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_61_27Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_12_13Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_61_Yonan,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_27_Kaesong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_12_13Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_7_49Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_12_Sunchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_13_Samdung,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_7_49Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_66_53Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_7_49Road0,
//deadcode JIM 18/06/01				/*supplier*/				&N1_7_Pyongyang,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_49_Hwangju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlPyongyang,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_66_53Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_15_55Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_66_Singye,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_53_Koksan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_15_55Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_63_54Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_15_Yangdok,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_55_Kanda,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_63_54Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_71_57Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_63_Suan,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_54_YulLi,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_71_57Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_42_71Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_71_Inje,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_57_Sangnam,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_42_71Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_55_21Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_42_Kansang,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_71_Inje,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_55_21Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_38_70Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_55_Kanda,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_21_Wonsan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_38_70Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_71_36Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_38_Kumhwa,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_70_Hwachon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_71_36Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_71_12Road0,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_71_Inje,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_36_Yangyang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_71_12Road0= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_71_12Road1,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_71_12Road1,
//deadcode JIM 18/06/01				/*supplier*/				&N1_71_Inje,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_12_Chuncheon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdInje,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_71_12Road1= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_38_50Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_71_Inje,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_12_Chuncheon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_38_50Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_25_66Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_38_Kumhwa,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_50_Yongpyong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_25_66Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_50_12Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_25_Pyongsan,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_66_Singye,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_50_12Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_41_28Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_50_Yongpyong,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_12_Chuncheon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdPukhan1,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_41_28Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_7_49Road0,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_41_Ichon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_28_Pyonggang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_7_49Road0= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_7_49Road1,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_7_49Road1,
//deadcode JIM 18/06/01				/*supplier*/				&N1_7_Pyongyang,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_49_Hwangju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdPyongyang0,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_7_49Road1= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_22_25Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_7_Pyongyang,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_49_Hwangju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdPyongyang1,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_22_25Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_22_25Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_22_25Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_22_Sariwon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_25_Pyongsan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_22_25Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_25_26Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_22_Sariwon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_25_Pyongsan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_25_26Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_25_26Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_25_26Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_25_Pyongsan,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_26_Kumchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_25_26Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_26_27Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_25_Pyongsan,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_26_Kumchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_26_27Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_26_27Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_25_26Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_26_Kumchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_27_Kaesong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_26_27Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_27_75Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_26_Kumchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_27_Kaesong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_27_75Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_27_75Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_27_75Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_27_Kaesong,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_75_Panmunjom,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlYesong,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_27_75Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_75_40Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_27_Kaesong,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_75_Panmunjom,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_75_40Rail=	{
//deadcode JIM 18/06/01				/*next*/					&R1_75_40Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_75_40Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_75_Panmunjom,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_40_Munsan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,  
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01		
//deadcode JIM 18/06/01	T::R1_75_40Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_34_20Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_75_Panmunjom,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_40_Munsan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01							
//deadcode JIM 18/06/01	T::R1_34_20Rail=	{
//deadcode JIM 18/06/01				/*next*/					&R1_34_20Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_34_20Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_20_Kowon,	//INCORRECT &N1_34_Yonghung
//deadcode JIM 18/06/01				/*suppliee*/				&N1_20_Kowon,	
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlTokohig,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01		
//deadcode JIM 18/06/01	T::R1_34_20Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_20_21Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_34_Yonghung,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_20_Kowon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_20_21Rail=	{
//deadcode JIM 18/06/01				/*next*/					&R1_20_21Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_20_21Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_20_Kowon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_21_Wonsan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlKowon,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01		
//deadcode JIM 18/06/01	T::R1_20_21Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_21_52Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_20_Kowon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_21_Wonsan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_21_52Rail=	{
//deadcode JIM 18/06/01				/*next*/					&R1_52_35Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_21_Wonsan,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_52_Kojo,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_52_35Rail=	{
//deadcode JIM 18/06/01				/*next*/					&R1_52_35Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_52_35Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_52_Kojo,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_35_Kojin,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01		
//deadcode JIM 18/06/01	T::R1_52_35Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_35_42Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_52_Kojo,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_35_Kojin,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_35_42Rail=	{
//deadcode JIM 18/06/01				/*next*/					&R1_35_42Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_35_42Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_35_Kojin,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_42_Kansang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01		
//deadcode JIM 18/06/01	T::R1_35_42Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_42_36Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_35_Kojin,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_42_Kansang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_42_36Rail=	{
//deadcode JIM 18/06/01				/*next*/					&R1_36_29Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_42_Kansang,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_36_Yangyang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01		
//deadcode JIM 18/06/01	T::R1_36_29Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_13_14Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_36_Yangyang,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_29_Kangnung,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_13_14Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_13_14Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_13_14Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_13_Samdung,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_14_WaDong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	T::R1_13_14Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_14_15Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_13_Samdung,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_14_WaDong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_14_15Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_14_15Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_14_15Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_14_WaDong,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_15_Yangdok,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	T::R1_14_15Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_15_20Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_14_WaDong,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_15_Yangdok,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_15_20Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_21_39Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_15_Yangdok,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_20_Kowon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_21_39Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_21_39Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_21_39Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_21_Wonsan,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_39_Kosan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_21_39Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_39_40Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_21_Wonsan,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_39_Kosan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	T::R1_39_40Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_40_68Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_39_Kosan,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_40_Hoeyang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	T::R1_40_68Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_70_12Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_40_Hoeyang,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_68_Changdo,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	T::R1_70_12Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_68_38Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_70_Hwachon,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_12_Chuncheon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_68_38Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_38_69Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_68_Changdo,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_38_Kumhwa,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_38_69Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_69_49Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_38_Kumhwa,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_69_Kalmal,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	T::R1_69_49Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_30_7Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_69_Kalmal,		//####
//deadcode JIM 18/06/01				/*suppliee*/				&N2_49_Pochon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_30_7Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_30_7Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_30_7Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_30_Nampo,			
//deadcode JIM 18/06/01				/*suppliee*/				&N1_7_Pyongyang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_30_7Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_39_67Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_30_Nampo,				
//deadcode JIM 18/06/01				/*suppliee*/				&N1_7_Pyongyang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_39_67Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_67_28Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_39_Kosan,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_67_Sepo,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	T::R1_67_28Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_28_43Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_67_Sepo,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_28_Pyonggang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},
//deadcode JIM 18/06/01	T::R1_28_43Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_43_56Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_28_Pyonggang,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_43_Chorwon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01									},		
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_43_56Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_56_11Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_43_Chorwon,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_56_Yonchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01							},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_56_11Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_28_38Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_56_Yonchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_11_Uijongbu,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlImjin,
//deadcode JIM 18/06/01							},		
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_28_38Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_38_70Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_28_38Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_28_Pyonggang,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_38_Kumhwa,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_28_38Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_38_70Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N1_28_Pyonggang,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_38_Kumhwa,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R1_38_70Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R1_70_12Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_38_70Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_38_Kumhwa,
//deadcode JIM 18/06/01				/*suppliee*/				&N1_70_Hwachon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R1_70_12Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_40_10Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			&R1_70_12Road,
//deadcode JIM 18/06/01				/*supplier*/				&N1_70_Hwachon,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_12_Chuncheon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	//-------------------------------------------------------------------------------
//deadcode JIM 18/06/01	//Supply routes for area 2
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_40_10Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_40_10Road0,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_40_10Road0,
//deadcode JIM 18/06/01				/*supplier*/				&N2_40_Munsan,			//####
//deadcode JIM 18/06/01				/*suppliee*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlMunsan,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_40_10Road0= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_40_10Road1,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_40_10Road1,				
//deadcode JIM 18/06/01				/*supplier*/				&N2_40_Munsan,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdMunsan0,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_40_10Road1= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_40_10Road2,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_40_10Road2,
//deadcode JIM 18/06/01				/*supplier*/				&N2_40_Munsan,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdMunsan1,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_40_10Road2= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_10_7Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_40_Munsan,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdMunsan2,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_10_7Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_10_7Road0,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_10_7Road0,
//deadcode JIM 18/06/01				/*supplier*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_7_Suwon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlSeoul,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_10_7Road0= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_6_36Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_10_7Road1,
//deadcode JIM 18/06/01				/*supplier*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_7_Suwon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdSeoul0,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_6_36Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_10_7Road1,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_6_Wonju,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_36_Mokkye,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_10_7Road1= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_10_7Road2,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_10_7Road2,
//deadcode JIM 18/06/01				/*supplier*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_7_Suwon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdSeoul2,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_10_7Road2= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_10_7Road3,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_10_7Road3,
//deadcode JIM 18/06/01				/*supplier*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_7_Suwon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdSeoul3,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_10_7Road3= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_10_7Road4,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_10_7Road4,
//deadcode JIM 18/06/01				/*supplier*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_7_Suwon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdSeoul4,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_10_7Road4= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_10_7Road5,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_10_7Road5,
//deadcode JIM 18/06/01				/*supplier*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_7_Suwon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdSeoul5,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_10_7Road5= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_7_14Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_7_Suwon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdSeoul6,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_7_14Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_7_14Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_7_14Road,
//deadcode JIM 18/06/01				/*supplier*/				&N2_7_Suwon,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_14_Osan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_7_14Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_14_19Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_7_Suwon,				
//deadcode JIM 18/06/01				/*suppliee*/				&N2_14_Osan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_14_19Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_14_19Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_14_19Road,
//deadcode JIM 18/06/01				/*supplier*/				&N2_14_Osan,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_19_Pyongtaek,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_14_19Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_29_28Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_14_Osan,				
//deadcode JIM 18/06/01				/*suppliee*/				&N3_19_Pyongtaek,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_29_28Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_28_30Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_29_Kangnung,				
//deadcode JIM 18/06/01				/*suppliee*/				&N2_28_Samchok,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_28_30Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_11_10Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_28_Samchok,				
//deadcode JIM 18/06/01				/*suppliee*/				&N3_30_Ulhin,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_11_10Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_11_10Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_11_10Road,
//deadcode JIM 18/06/01				/*supplier*/				&N2_11_Uijongbu,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_11_10Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_49_11Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_11_Uijongbu,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_49_11Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_48_10Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_49_Pochon,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_11_Uijongbu,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_48_10Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_12_35Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_48_Kuri,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_12_35Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_35_23Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_12_Chuncheon,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_35_Hongchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_35_23Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_40_11Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_35_Hongchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_23_Hoensong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_40_11Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_42_28Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_40_Munsan,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_11_Uijongbu,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_42_28Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_10_9Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_42_Chongson,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_28_Samchok,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_10_9Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_43_5Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_9_Inchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_43_5Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_23_6Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_43_Pyongchang,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_5_Chechon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_23_6Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_8_41Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_23_Hoensong,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_6_Wonju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_8_41Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_41_26Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_8_Songnam,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_41_Ichon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_41_26Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_34_43Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_41_Ichon,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_26_Changhowon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_34_43Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_43_42Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_34_Yulchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_43_Pyongchang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_43_42Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_10_8Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_43_Pyongchang,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_42_Chongson,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_10_8Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_28_44Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_8_Songnam,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_28_44Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_14_41Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_28_Samchok,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_44_Taepaek,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_14_41Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_7_8Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_14_Osan,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_41_Ichon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_7_8Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_9_7Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_7_Suwon,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_8_Songnam,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_9_7Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_57_34Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_9_Inchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_7_Suwon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_57_34Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_10_58Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_57_Sangnam,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_34_Yulchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_10_58Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_58_6Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_10_Seoul,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_58_Yangpyong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlHan,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_58_6Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_12_48Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_58_Yangpyong,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_6_Wonju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_12_48Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_12_48Road0,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_12_48Road0,
//deadcode JIM 18/06/01				/*supplier*/				&N2_12_Chuncheon,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_48_Kuri,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlPukhan0,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_12_48Road0= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_12_48Road1,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_12_48Road1,
//deadcode JIM 18/06/01				/*supplier*/				&N2_12_Chuncheon,				
//deadcode JIM 18/06/01				/*suppliee*/				&N2_48_Kuri,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdChuncheon0,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_12_48Road1= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_6_5Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_12_Chuncheon,				
//deadcode JIM 18/06/01				/*suppliee*/				&N2_48_Kuri,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdChuncheon1,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_6_5Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_12_35Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_6_Wonju,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_5_Chechon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R2_12_35Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_35_23Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_12_35Road,
//deadcode JIM 18/06/01				/*supplier*/				&N2_12_Chuncheon,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_35_Hongchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_35_23Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R2_23_6Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_35_23Road,
//deadcode JIM 18/06/01				/*supplier*/				&N2_35_Hongchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_23_Hoensong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R2_23_6Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_19_3Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			&R2_23_6Road,
//deadcode JIM 18/06/01				/*supplier*/				&N2_35_Hongchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N2_23_Hoensong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	//-------------------------------------------------------------------------------
//deadcode JIM 18/06/01	//Supply routes for area 3
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_19_3Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_19_3Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R3_19_3Road,
//deadcode JIM 18/06/01				/*supplier*/				&N3_19_Pyongtaek,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_3_Chonan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_19_3Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_3_17Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_19_Pyongtaek,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_3_Chonan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_3_17Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_3_17Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R3_3_17Road,
//deadcode JIM 18/06/01				/*supplier*/				&N3_3_Chonan,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_17_Chochiwon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlChonui,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_3_17Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_17_1Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_3_Chonan,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_17_Chochiwon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_17_1Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_3_64Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			&R3_17_1Road,
//deadcode JIM 18/06/01				/*supplier*/				&N3_17_Chochiwon,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_1_Taejon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRlKum0,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_3_64Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_64_65Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_3_Chonan,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_64_Hongsong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_64_65Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_65_66Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_64_Hongsong,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_65_Hannae,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_65_66Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_4_59Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_65_Hannae,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_66_Taechon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_4_59Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_17_1Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_4_Chungju,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_59_Koesan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_17_1Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_62_16Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_17_Chochiwon,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_1_Taejon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_62_16Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_36_4Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_62_Noktong,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_16_Yongju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_36_4Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_44_62Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_36_Mokkye,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_4_Chungju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdChungju,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_44_62Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_24_21Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_44_Taepaek,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_62_Noktong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_24_21Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_21_22Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_24_Chomchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_21_Sangju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_21_22Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_20_24Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_21_Sangju,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_22_Kimchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_20_24Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_41_51Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_20_Yechon,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_24_Chomchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_41_51Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_60_24Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N2_41_Ichon,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_51_Maesan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_60_24Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_1_46Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_60_Mungyong,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_24_Chomchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_1_46Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_1_46Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R3_1_46Road,
//deadcode JIM 18/06/01				/*supplier*/				&N3_1_Taejon,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_46_Yongdong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_1_46Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_45_1Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_1_Taejon,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_46_Yongdong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_BrRdKum1                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_45_1Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_63_45Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_45_Nonsan,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_1_Taejon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_63_45Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_66_63Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_63_Kunsan,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_45_Nonsan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_66_63Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_55_37Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_66_Taechon,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_63_Kunsan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_55_37Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_18_55Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_55_Uisong,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_37_Kumi,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_18_55Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_61_16Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_18_Andong,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_55_Uisong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_61_16Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_59_2Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_61_Tanyang,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_16_Yongju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_59_2Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_2_1Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_59_Koesan,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_2_Chongju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_2_1Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_4_61Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_2_Chongju,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_1_Taejon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_4_61Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_52_53Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_4_Chungju,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_61_Tanyang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_52_53Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_51_52Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_52_Kwangheywan,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_53_Chinchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_51_52Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_53_54Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_51_Maesan,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_52_Kwangheywan,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_53_54Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_54_2Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_53_Chinchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_54_Chungpyong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_54_2Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_4_60Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_54_Chungpyong,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_2_Chongju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_4_60Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_46_22Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_4_Chungju,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_60_Mungyong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_46_22Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_46_22Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R3_46_22Road,
//deadcode JIM 18/06/01				/*supplier*/				&N3_46_Yongdong,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_22_Kimchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_46_22Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_18_20Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_46_Yongdong,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_22_Kimchon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_18_20Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_22_37Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_18_Andong,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_20_Yechon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_22_37Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_30_31Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_22_Kimchon,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_37_Kumi,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_30_31Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_31_32Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_30_Ulhin,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_31_Yonghae,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_31_32Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_32_25Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_31_Yonghae,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_32_Yongdok,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_32_25Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_5_47Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_32_Yongdok,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_25_Pohang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null                                                                                                                                        ,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_5_47Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_47_16Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_5_Chechon,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_47_Punggi,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_47_16Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_47_16Road,
//deadcode JIM 18/06/01				/*alternateroute*/			&R3_47_16Road,
//deadcode JIM 18/06/01				/*supplier*/				&N3_47_Punggi,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_16_Yongju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_47_16Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_16_18Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_47_Punggi,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_16_Yongju,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_16_18Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_2_17Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_16_Yongju,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_18_Andong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	T::R3_2_17Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_16_18Road,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_2_Chongju,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_17_Chochiwon,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_16_18Road= 	{
//deadcode JIM 18/06/01				/*next*/					&R3_18_25Rail,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_16_Yongju,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_18_Andong,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRUCKSPERDAY*STORES_TRUCK,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::R3_18_25Rail= 	{
//deadcode JIM 18/06/01				/*next*/					&LastRoute,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				&N3_16_Yongju,
//deadcode JIM 18/06/01				/*suppliee*/				&N3_25_Pohang,
//deadcode JIM 18/06/01				/*status*/					SR_ACTIVE,
//deadcode JIM 18/06/01				/*recommision_time*/		DAYS0,
//deadcode JIM 18/06/01				/*redsupplyBF*/				FIL_NULL,
//deadcode JIM 18/06/01				/*storespermobile*/			STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitywinter*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*maxcapacitysummer*/		STD_TRAINSPERDAY*STORES_TRAIN,
//deadcode JIM 18/06/01				/*associated_brdg*/			UID_Null,
//deadcode JIM 18/06/01								},
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::LastRoute= 	{
//deadcode JIM 18/06/01				/*next*/					&LastRoute,
//deadcode JIM 18/06/01				/*alternateroute*/			NULL,
//deadcode JIM 18/06/01				/*supplier*/				NULL,
//deadcode JIM 18/06/01				/*suppliee*/				NULL,
//deadcode JIM 18/06/01				/*status*/					SR_LASTONE,
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01				};	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	//------------------------------------------------------------------------------
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	//------------------------------------------------------------------------------
//deadcode JIM 18/06/01	//
//deadcode JIM 18/06/01	//
//deadcode JIM 18/06/01	//
//deadcode JIM 18/06/01	//
//deadcode JIM 18/06/01	//
//deadcode JIM 18/06/01	SupplyLine
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	T::WestRoute = {
//deadcode JIM 18/06/01				/*AssociatedDepot[2]*/			{UID_RpRdSinuiju,UID_MyRdPyongyang},
//deadcode JIM 18/06/01				/*firstnode*/					&N0_0_Dangdong,
//deadcode JIM 18/06/01				/*splitsAB and BC*/				&N1_22_Sariwon,&N2_10_Seoul,
//deadcode JIM 18/06/01				/*MaxMobiles*/					MAXMOBILESONDOUBLETRACK,
//deadcode JIM 18/06/01				/*TodaysMobiles*/				MAXMOBILESONDOUBLETRACK,
//deadcode JIM 18/06/01				/*CurrMobiles*/					0,
//deadcode JIM 18/06/01				/*frontline*/					&N2_40_Munsan,
//deadcode JIM 18/06/01				/*attackpotential*/				0,
//deadcode JIM 18/06/01				},
//deadcode JIM 18/06/01	T::CentralRoute = {
//deadcode JIM 18/06/01				/*AssociatedDepot[2]*/			{UID_Null,UID_Null},
//deadcode JIM 18/06/01				/*firstnode*/					&N0_8_Manpo,
//deadcode JIM 18/06/01				/*splitsAB and BC*/				&N3_53_Chinchon,&N2_11_Uijongbu,
//deadcode JIM 18/06/01				/*MaxMobiles*/					MAXMOBILESONSINGLETRACK,
//deadcode JIM 18/06/01				/*TodaysMobiles*/				MAXMOBILESONSINGLETRACK,
//deadcode JIM 18/06/01				/*CurrMobiles*/					0,
//deadcode JIM 18/06/01				/*frontline*/					&N1_56_Yonchon,
//deadcode JIM 18/06/01				/*attackpotential*/				0,
//deadcode JIM 18/06/01				},
//deadcode JIM 18/06/01	T::EastRoute = {
//deadcode JIM 18/06/01				/*AssociatedDepot[2]*/			{UID_Null,UID_Null},
//deadcode JIM 18/06/01				/*firstnode*/					&N0_16_Chongjin,
//deadcode JIM 18/06/01				/*splitsAB and BC*/				&N1_21_Wonsan,&N2_28_Samchok,
//deadcode JIM 18/06/01				/*MaxMobiles*/					MAXMOBILESONSINGLETRACK,
//deadcode JIM 18/06/01				/*TodaysMobiles*/				MAXMOBILESONSINGLETRACK,
//deadcode JIM 18/06/01				/*CurrMobiles*/					0,
//deadcode JIM 18/06/01				/*frontline*/					&N2_42_Chongson,
//deadcode JIM 18/06/01				/*attackpotential*/				0,
//deadcode JIM 18/06/01				};
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 WestRoute = {
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 			/*AssociatedDepot[2]*/			{UID_Null,UID_Null},
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 			/*MaxMobiles*/					MAXMOBILESONSINGLEROAD,
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 			/*TodaysMobiles*/				MAXMOBILESONSINGLEROAD,
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 			/*CurrMobiles*/					0,
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 			/*frontline*/					&N1_6_Sukchon,				
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 			/*attackpotential*/				0,
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 			},
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 EastRoute = {
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 			/*AssociatedDepot[2]*/			{UID_Null,UID_Null},
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 			/*MaxMobiles*/					MAXMOBILESONSINGLEROAD,
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 			/*TodaysMobiles*/				MAXMOBILESONSINGLEROAD,
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 			/*CurrMobiles*/					0,
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 			/*frontline*/					&N2_49_Pochon,
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 			/*attackpotential*/				0,
//deadcode JIM 18/06/01	//DeadCode RDH 13Mar97 			};
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	//------------------------------------------------------------------------------
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	AirFieldInfo	T::airfieldinfo[] =
//deadcode JIM 18/06/01	{
//deadcode JIM 18/06/01			{//0
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdSinmak,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N1_22_Sariwon,&N1_25_Pyongsan},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N1_26_Kumchon,&N1_61_Yonan},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_PROPONLY,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//1
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdHwangju,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N1_7_Pyongyang,&N1_49_Hwangju},
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N1_22_Sariwon,&N1_62_Chaeryong},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_PROPONLY,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//2
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdSinuiju,		
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N0_1_Sinuiju,&N0_46_Chongsongup},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N0_2_Yomju,&N0_3_Sonchon},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_JET,
//deadcode JIM 18/06/01				/*capacity*/		3
//deadcode JIM 18/06/01			},		
//deadcode JIM 18/06/01			{//3
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,						
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdSinuijuNE,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N0_1_Sinuiju,&N0_46_Chongsongup},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N0_2_Yomju,&N0_3_Sonchon},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_JET,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//4
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdSunan,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N1_6_Sukchon,&N1_12_Sunchon},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N1_29_Kangdong,&N1_7_Pyongyang},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_LIGHTBOMBER,
//deadcode JIM 18/06/01				/*capacity*/		2
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//5
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdAntung,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N0_1_Sinuiju,&N0_2_Yomju},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N0_1_Sinuiju,&N0_2_Yomju},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_LOADEDJET,
//deadcode JIM 18/06/01				/*capacity*/		3
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//6
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdTaTung,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N0_1_Sinuiju,&N0_2_Yomju},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N0_1_Sinuiju,&N0_2_Yomju},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_LOADEDJET,
//deadcode JIM 18/06/01				/*capacity*/		3
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//7
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdUiju,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N0_57_Suiho,&N0_46_Chongsongup},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N0_1_Sinuiju,&N0_2_Yomju},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_JET,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//8
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdAnak,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N1_30_Nampo,&N1_49_Hwangju},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N1_62_Chaeryong,&N1_22_Sariwon},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_PROPONLY,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//9
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdSariwon,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N1_22_Sariwon,&N1_49_Hwangju},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N1_62_Chaeryong,&N1_25_Pyongsan},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_PROPONLY,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//10
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdYongyu,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N1_6_Sukchon,&N1_12_Sunchon},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N1_29_Kangdong,&N1_7_Pyongyang},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_PROPONLY,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//11
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdSinanju,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N0_4_Chongju,&N0_5_Sinaju},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N1_6_Sukchon,&N1_12_Sunchon},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_PROPONLY,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//12
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdPyongni,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N1_12_Sunchon,&N1_6_Sukchon},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N1_13_Samdung,&N1_7_Pyongyang},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_PROPONLY,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//13
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdTaechon,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N0_48_Kusong,&N0_11_Kujang},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N0_4_Chongju,&N0_5_Sinaju},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_JET,
//deadcode JIM 18/06/01				/*capacity*/		2
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//14
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdNamsi,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N0_2_Yomju,&N0_48_Kusong},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N0_3_Sonchon,&N0_4_Chongju},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_JET,
//deadcode JIM 18/06/01				/*capacity*/		2
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//15
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdSaamcham,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N0_11_Kujang,&N0_4_Chongju},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N0_5_Sinaju,&N0_31_Tokchon},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_JET,
//deadcode JIM 18/06/01				/*capacity*/		2
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//16
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdPyongyangE,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N1_7_Pyongyang,&N1_29_Kangdong},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N1_49_Hwangju,&N1_22_Sariwon},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_PROPONLY,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//17
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdPyongyangM,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N1_7_Pyongyang,&N1_29_Kangdong},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N1_49_Hwangju,&N1_30_Nampo},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_LOADEDJET,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//18
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_RED,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfRdPyongyangD,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N1_7_Pyongyang,&N1_29_Kangdong},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N1_49_Hwangju,&N1_30_Nampo},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_LOADEDJET,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//19
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_BLUE,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfBlKimpo,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N2_39_Kimpo,&N2_40_Munsan},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N2_9_Inchon,&N2_10_Seoul},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_LOADEDJET,
//deadcode JIM 18/06/01				/*capacity*/		3
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//20
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_BLUE,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfBlSeoul,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N2_10_Seoul,&N2_9_Inchon},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N2_7_Suwon,&N2_8_Songnam},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_LOADEDJET,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//21
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_BLUE,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfBlChuncheon,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N2_12_Chuncheon,&N2_48_Kuri},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N2_58_Yangpyong,&N2_35_Hongchon},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_PROPONLY,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//22
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_BLUE,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfBlOsan,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N2_14_Osan,&N2_7_Suwon},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N3_19_Pyongtaek,&N3_3_Chonan},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_PROPONLY,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//23
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_BLUE,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfBlSuwon,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N2_8_Songnam,&N2_7_Suwon},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N3_19_Pyongtaek,&N2_14_Osan},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_LOADEDJET,
//deadcode JIM 18/06/01				/*capacity*/		2
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//24
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_BLUE,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfBlPyongtaek,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N3_19_Pyongtaek,&N2_14_Osan},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N3_3_Chonan,&N3_64_Hongsong},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_PROPONLY,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//25
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_BLUE,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfBlKunsan,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N3_64_Hongsong,&N3_17_Chochiwon},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N3_65_Hannae,&N3_15_Kongju},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_LIGHTBOMBER,
//deadcode JIM 18/06/01				/*capacity*/		2
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//26
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_BLUE,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfBlTaejon,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N3_1_Taejon,&N3_15_Kongju},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N3_45_Nonsan,&N3_46_Yongdong},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_PROPONLY,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//27
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_BLUE,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfBlTaegu,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N3_22_Kimchon,&N3_37_Kumi},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N3_22_Kimchon,&N3_37_Kumi},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_LOADEDJET,
//deadcode JIM 18/06/01				/*capacity*/		2
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//28
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_BLUE,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfBlTaeguW,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N3_22_Kimchon,&N3_37_Kumi},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N3_22_Kimchon,&N3_37_Kumi},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_JET,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//29
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_BLUE,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfBlKangnung,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N2_29_Kangnung,&N1_36_Yangyang},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N2_28_Samchok,&N2_42_Chongson},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_PROPONLY,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01			{//30
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_BLUE,
//deadcode JIM 18/06/01				/*airfield*/		UID_AfBlPohang,
//deadcode JIM 18/06/01				/*northnodes[2]*/	{&N3_25_Pohang,&N3_32_Yongdok},	
//deadcode JIM 18/06/01				/*southnodes[2]*/	{&N3_25_Pohang,&N3_32_Yongdok},
//deadcode JIM 18/06/01				/*AirFieldType*/	AFT_PROPONLY,
//deadcode JIM 18/06/01				/*capacity*/		1
//deadcode JIM 18/06/01			},
//deadcode JIM 18/06/01	//this must be the last one!
//deadcode JIM 18/06/01			{
//deadcode JIM 18/06/01				/*nationality*/	 	NAT_ALIGN,
//deadcode JIM 18/06/01			}
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	};
//deadcode JIM 18/06/01	//DirectivesProfile	T::profilelib[T::MAXPROFILELIBS]	 =
//deadcode JIM 18/06/01	//{
//deadcode JIM 18/06/01	//			 86,86,80,84,51,26,29
//deadcode JIM 18/06/01	//GROUND ATTACK
//deadcode JIM 18/06/01	//-------------
//deadcode JIM 18/06/01	//
//deadcode JIM 18/06/01	//			{16, 0,16,16,0,16, 0},		//P_ALPHASTRIKE
//deadcode JIM 18/06/01	//			{0, 0, 0, 0, 0, 0, 0},		//P_MEDSTRIKE		allocated at runtime	
//deadcode JIM 18/06/01	//			{0, 0, 0, 0, 0, 0, 0},		//P_FBSTRIKE		allocated at runtime
//deadcode JIM 18/06/01	//			{0, 0, 8, 8, 0, 0, 8},		//P_B29CARPETBOMB		
//deadcode JIM 18/06/01	//			{0, 0, 8, 8, 0, 0, 8},		//P_B29PRECISIONBOMB	
//deadcode JIM 18/06/01	//			{0, 0, 0, 0, 0, 8, 0},		//P_B26RAID			
//deadcode JIM 18/06/01	//			{0, 0, 0, 8, 0, 0, 0},		//P_DEEPFBSTRIKE		
//deadcode JIM 18/06/01	//			{0, 0, 8, 0, 0, 0, 0},		//P_NORMALFBSTRIKE		
//deadcode JIM 18/06/01	//			{0, 0, 0, 0, 8, 0, 0},		//P_LOWRISKFBSTRIKE		
//deadcode JIM 18/06/01	//			{0, 0, 0, 8, 0, 0, 0},		//P_HITANDRUN		
//deadcode JIM 18/06/01	//			{0, 0, 8, 8, 8, 0, 0},		//P_MIXEDRAID
//deadcode JIM 18/06/01	////ARMED RECONN PATROLS
//deadcode JIM 18/06/01	////--------------------
//deadcode JIM 18/06/01	//			{0, 0, 0, 0, 4, 0, 0},		//P_ARMEDRECONN		
//deadcode JIM 18/06/01	////MIGCAP
//deadcode JIM 18/06/01	////------
//deadcode JIM 18/06/01	//			{16,16,0, 0, 0, 0, 0},		//P_SABRESCREEN		
//deadcode JIM 18/06/01	////CAS
//deadcode JIM 18/06/01	////---
//deadcode JIM 18/06/01	//			{0, 0, 0, 0, 4, 0, 0},		//P_RAPIDRESPONSE		
//deadcode JIM 18/06/01	//
//deadcode JIM 18/06/01	//
//deadcode JIM 18/06/01	//};
//deadcode JIM 18/06/01										  
//deadcode JIM 18/06/01	T::DisSmacker	T::dissmackers [T::MAX_DISSMACKERS]= 
//deadcode JIM 18/06/01	{
//deadcode JIM 18/06/01		{
//deadcode JIM 18/06/01			/*idtext*/			Debrief::T_ByPassBuilt_H,
//deadcode JIM 18/06/01			/*FIL_NULL*/			FIL_SMACK_CAMP1INTRO
//deadcode JIM 18/06/01		},
//deadcode JIM 18/06/01		{
//deadcode JIM 18/06/01			/*idtext*/			Debrief::T_DeceptionFound00_H,
//deadcode JIM 18/06/01			/*FIL_NULL*/			FIL_SMACK_CAMP2INTRO
//deadcode JIM 18/06/01		},
//deadcode JIM 18/06/01		{
//deadcode JIM 18/06/01			/*idtext*/			-1,
//deadcode JIM 18/06/01			/*FIL_NULL*/			FIL_NULL
//deadcode JIM 18/06/01		},
//deadcode JIM 18/06/01		{
//deadcode JIM 18/06/01			/*idtext*/			-1,
//deadcode JIM 18/06/01			/*FIL_NULL*/			FIL_NULL
//deadcode JIM 18/06/01		},
//deadcode JIM 18/06/01		{
//deadcode JIM 18/06/01			/*idtext*/			-1,
//deadcode JIM 18/06/01			/*FIL_NULL*/			FIL_NULL
//deadcode JIM 18/06/01		},
//deadcode JIM 18/06/01		{
//deadcode JIM 18/06/01			/*idtext*/			-1,
//deadcode JIM 18/06/01			/*FIL_NULL*/			FIL_NULL
//deadcode JIM 18/06/01		},
//deadcode JIM 18/06/01		{
//deadcode JIM 18/06/01			/*idtext*/			-1,
//deadcode JIM 18/06/01			/*FIL_NULL*/			FIL_NULL
//deadcode JIM 18/06/01		},
//deadcode JIM 18/06/01		{
//deadcode JIM 18/06/01			/*idtext*/			-1,
//deadcode JIM 18/06/01			/*FIL_NULL*/			FIL_NULL
//deadcode JIM 18/06/01		},
//deadcode JIM 18/06/01		{
//deadcode JIM 18/06/01			/*idtext*/			-1,
//deadcode JIM 18/06/01			/*FIL_NULL*/			FIL_NULL
//deadcode JIM 18/06/01		},
//deadcode JIM 18/06/01		{
//deadcode JIM 18/06/01			/*idtext*/			-1,
//deadcode JIM 18/06/01			/*FIL_NULL*/			FIL_NULL
//deadcode JIM 18/06/01		},
//deadcode JIM 18/06/01	};
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	//T::DirControl	T::dir_ctrl = 
//deadcode JIM 18/06/01	//{ 
//deadcode JIM 18/06/01	//	/*autogen*/			true,
//deadcode JIM 18/06/01	//	/*autodisplay*/		true,
//deadcode JIM 18/06/01	//	/*B29avail*/		true,
//deadcode JIM 18/06/01	//	/*alphastrikesallowed*/		false,
//deadcode JIM 18/06/01	//	/*dayssinceB29*/	0,
//deadcode JIM 18/06/01	//
//deadcode JIM 18/06/01	//	{
//deadcode JIM 18/06/01	//		   {
//deadcode JIM 18/06/01	//				/*type*/				D_AIRSUPERIORITY,
//deadcode JIM 18/06/01	//				/*strikeac*/			0,
//deadcode JIM 18/06/01	//				/*fighterac*/			16,
//deadcode JIM 18/06/01	//				/*targets*/				0,
//deadcode JIM 18/06/01	//				/*missionsset*/			0
//deadcode JIM 18/06/01	//		   },
//deadcode JIM 18/06/01	//		   {
//deadcode JIM 18/06/01	//				/*type*/				D_CHOKE,
//deadcode JIM 18/06/01	//				/*strikeac*/			64,
//deadcode JIM 18/06/01	//				/*fighterac*/			16,
//deadcode JIM 18/06/01	//				/*targets*/				0,
//deadcode JIM 18/06/01	//				/*missionsset*/			0
//deadcode JIM 18/06/01	//		   },
//deadcode JIM 18/06/01	//		   {
//deadcode JIM 18/06/01	//				/*type*/				D_SUPPLY,
//deadcode JIM 18/06/01	//				/*strikeac*/			0,
//deadcode JIM 18/06/01	//				/*fighterac*/			0,
//deadcode JIM 18/06/01	//				/*targets*/				0,
//deadcode JIM 18/06/01	//				/*missionsset*/			0
//deadcode JIM 18/06/01	//		   },
//deadcode JIM 18/06/01	//		   {
//deadcode JIM 18/06/01	//				/*type*/				D_AIRFIELDS,
//deadcode JIM 18/06/01	//				/*strikeac*/			0,
//deadcode JIM 18/06/01	//				/*fighterac*/			0,
//deadcode JIM 18/06/01	//				/*targets*/				0,
//deadcode JIM 18/06/01	//				/*missionsset*/			0
//deadcode JIM 18/06/01	//		   },
//deadcode JIM 18/06/01	//		   {
//deadcode JIM 18/06/01	//				/*type*/				D_RAIL,
//deadcode JIM 18/06/01	//				/*strikeac*/			0,
//deadcode JIM 18/06/01	//				/*fighterac*/			0,
//deadcode JIM 18/06/01	//				/*targets*/				0,
//deadcode JIM 18/06/01	//				/*missionsset*/			0
//deadcode JIM 18/06/01	//		   },
//deadcode JIM 18/06/01	//		   {
//deadcode JIM 18/06/01	//				/*type*/				D_ROAD,
//deadcode JIM 18/06/01	//				/*strikeac*/			0,
//deadcode JIM 18/06/01	//				/*fighterac*/			0,
//deadcode JIM 18/06/01	//				/*targets*/				0,
//deadcode JIM 18/06/01	//				/*missionsset*/			0
//deadcode JIM 18/06/01	//		   },
//deadcode JIM 18/06/01	//		   {
//deadcode JIM 18/06/01	//				/*type*/				D_ARMY,
//deadcode JIM 18/06/01	//				/*strikeac*/			0,
//deadcode JIM 18/06/01	//				/*fighterac*/			0,
//deadcode JIM 18/06/01	//				/*targets*/				0,
//deadcode JIM 18/06/01	//				/*missionsset*/			0
//deadcode JIM 18/06/01	//		   },
//deadcode JIM 18/06/01	//		   {
//deadcode JIM 18/06/01	//				/*type*/				D_RESTING,
//deadcode JIM 18/06/01	//				/*strikeac*/			0,
//deadcode JIM 18/06/01	//				/*fighterac*/			0,
//deadcode JIM 18/06/01	//				/*targets*/				0,
//deadcode JIM 18/06/01	//				/*missionsset*/			0
//deadcode JIM 18/06/01	//		   }
//deadcode JIM 18/06/01	//	}
//deadcode JIM 18/06/01	//};
