
	Formation	SQD_RAFVIC_VIC	= {Select FTW_RAFVIC,FTS_VIC},//MS 20Jan00
	Formation	SQD_RAFVIC_ABREST= {Select FTW_RAFVIC,FTS_ABREST},//MS 20Jan00
	Formation	SQD_RAFVIC_ASTERN	= {Select FTW_RAFVIC,FTS_ASTERN},//MS 20Jan00

	Formation	SQD_SCHWARM_VIC	= {Select FTW_SCWARM,FTS_VIC},//MS 20Jan00

	Formation	SQD_FINGER_VIC	= {Select FTW_FINGER,FTS_VIC},//MS 23Mar00
	Formation	SQD_FINGER_ASTERN= {Select FTW_FINGER,FTS_ASTERN},//MS 14Apr00

	Formation	SQD_LWVIC_VIC	= {Select FTW_LWVIC,FTS_VIC},//MS 26Jan00
	Formation	SQD_LWVIC_ECHL	= {Select FTW_LWVIC,FTS_ECHL},//MS 09Jun00
	Formation	SQD_LWVIC_ECHR	= {Select FTW_LWVIC,FTS_ECHR},//MS 09Jun00
	Formation	SQD_LWVIC_ABREST	= {Select FTW_LWVIC,FTS_ABREST},//MS 09Jun00
	Formation	SQD_LWVIC_ASTERN	= {Select FTW_LWVIC,FTS_ASTERN},//MS 09Jun00
	Formation	SQD_LWVIC_DIAMOND	= {Select FTW_LWVIC,FTS_DIAMOND},//MS 09Jun00
	Formation	SQD_LWVIC_BOX	= {Select FTW_LWVIC,FTS_BOX},//MS 09Jun00

//FTI VIC							//MS 09Jun00

	Formation	GRUP_LWVIC_VIC_VIC	= {Select SQD_LWVIC_VIC,FTIP_GRUPII},//MS 08Feb00
	Formation	GRUP_LWVIC_VIC_VIC2	= {Select SQD_LWVIC_VIC,FTIP_GRUPIII},//MS 08Feb00

	Formation	GRUP_LWVIC_ECHL_VIC	= {Select SQD_LWVIC_ECHL,FTIP_LEFT},//MS 09Jun00
	Formation	GRUP_LWVIC_ECHL_VIC2	= {Select SQD_LWVIC_ECHL,FTIP_RIGHT},//MS 09Jun00

	Formation	GRUP_LWVIC_ECHR_VIC	= {Select SQD_LWVIC_ECHR,FTIP_LEFT},//MS 09Jun00
	Formation	GRUP_LWVIC_ECHR_VIC2	= {Select SQD_LWVIC_ECHR,FTIP_RIGHT},//MS 09Jun00

	Formation	GRUP_LWVIC_ABREST_VIC	= {Select SQD_LWVIC_ABREST,FTIP_LEFT},//MS 08Feb00
	Formation	GRUP_LWVIC_ABREST_VIC2	= {Select SQD_LWVIC_ABREST,FTIP_RIGHT},//MS 08Feb00

	Formation	GRUP_LWVIC_ASTERN_VIC	= {Select SQD_LWVIC_ASTERN,FTIP_GRUPII},//MS 08Aug00
	Formation	GRUP_LWVIC_ASTERN_VIC2	= {Select SQD_LWVIC_ASTERN,FTIP_GRUPIII},//MS 08Aug00

	Formation	GRUP_LWVIC_DIAMOND_VIC	= {Select SQD_LWVIC_DIAMOND,FTIP_LEFT},//MS 08Feb00
	Formation	GRUP_LWVIC_DIAMOND_VIC2	= {Select SQD_LWVIC_DIAMOND,FTIP_RIGHT},//MS 08Feb00

	Formation	GRUP_FINGER_VIC_VIC	= {Select SQD_FINGER_VIC,FTIP_LEFT},//MS 23Mar00
	Formation	GRUP_FINGER_VIC_VIC2	= {Select SQD_FINGER_VIC,FTIP_RIGHT},//MS 23Mar00

//FTI ASTERN

	Formation	GRUP_LWVIC_ASTERN_ASTERN	= {Select SQD_LWVIC_ASTERN,FTI_ASTERN},//MS 08Feb00
	Formation	GRUP_LWVIC_ASTERN_ASTERN2	= {Select SQD_LWVIC_ASTERN,FTIP_ASTERN2},//MS 08Feb00

	Formation	GRUP_LWVIC_VIC_ASTERN	= {Select SQD_LWVIC_VIC,FTI_ASTERN},//MS 22Mar00
	Formation	GRUP_LWVIC_VIC_ASTERN2	= {Select SQD_LWVIC_VIC,FTIP_ASTERN2},//MS 22Mar00
//---------------
//FTI ABOVE

	Formation	GRUP_LWVIC_VIC_ABOVE	= {Select SQD_LWVIC_VIC,FTIP_ABOVE},//MS 19Jun00
	Formation	GRUP_LWVIC_VIC_ABOVE2	= {Select SQD_LWVIC_VIC,FTIP_BELOW},//MS 19Jun00

//---------------
	Formation	GRUP_FINGER_ASTERN_LEFT	= {Select SQD_FINGER_ASTERN,FTIP_LEFT},//MS 14Apr00
	Formation	GRUP_FINGER_ASTERN_RIGHT= {Select SQD_FINGER_ASTERN,FTIP_RIGHT},//MS 14Apr00
	Formation	GRUP_FINGER_ASTERN_ABOVE= {Select SQD_FINGER_ASTERN,FTIP_ABOVE},//MS 14Apr00
	Formation	GRUP_FINGER_ASTERN_BELOW = {Select SQD_FINGER_ASTERN,FTIP_BELOW},//MS 02Jun00
	Formation	GRUP_FINGER_ASTERN_FRONT= {Select SQD_FINGER_ASTERN,FTIP_AHEAD},//MS 25May00
	Formation	GRUP_FINGER_ASTERN_BACK = {Select SQD_FINGER_ASTERN,FTIP_ASTERN},//MS 25May00

	Formation	GRUP_FINGER_VIC_LEFT = {Select SQD_FINGER_VIC,FTIP_LEFT},//MS 25May00
	Formation	GRUP_FINGER_VIC_RIGHT = {Select SQD_FINGER_VIC,FTIP_RIGHT},//MS 25May00
	Formation	GRUP_FINGER_VIC_ABOVE = {Select SQD_FINGER_VIC,FTIP_ABOVE},//MS 25May00
	Formation	GRUP_FINGER_VIC_AHEAD = {Select SQD_FINGER_VIC,FTIP_AHEAD},//MS 06Jul00
	
//---------------

	Formation	GRUP_SCHWARM_VIC_VIC	= {Select SQD_SCHWARM_VIC,FTIP_LEFT},//MS 24Mar00
	Formation	GRUP_SCHWARM_VIC_VIC2	= {Select SQD_SCHWARM_VIC,FTIP_RIGHT},//MS 24Mar00

	Formation	WING_RAFVIC_VIC_VIC	= {Select SQD_RAFVIC_VIC,FTIP_LEFT},//MS 27Mar00
	Formation	WING_RAFVIC_VIC_VIC2	= {Select SQD_RAFVIC_VIC,FTIP_RIGHT},//MS 27Mar00

	Formation	WING_RAFVIC_VIC_ASTERN	= {Select SQD_RAFVIC_VIC,FTI_ASTERN},//MS 22Mar00
	Formation	WING_RAFVIC_VIC_ASTERN2	= {Select SQD_RAFVIC_VIC,FTIP_ASTERN2},//MS 22Mar00

//	Duty	DUTY_DiveSingle = (Select DA_DIVE,DA_SINGLEFILE),//MS 07Jun99
//	Duty	DUTY_DiveIndividual = (Select DA_DIVE,DA_INDIVIDUAL),//MS 07Jun99
//	Duty	DUTY_HighWide = (Select DA_HIGH,DA_WIDE),	//MS 07Jun99

	Shape	SHAPE_TroopDefend	=	EMPTY,		//MS 27Apr99
	Shape	SHAPE_TroopMove		=	EMPTY,		//MS 27Apr99
	Shape	SHAPE_TroopAttack	=	EMPTY,

//DeadCode MS 18Apr00 	Int	VEL_MoveTroop		=	{Select 0, VEL_1MS, 75},//RJS 05Apr00
//DeadCode MS 21Aug00 	Int	VEL_MoveTroop		=	44000,		//MS 18Apr00
	Int	VEL_MoveTroop		=	{Select 0, VEL_1MS, 3},//MS 
	Int	VEL_MoveMortar		=	{Select 0, VEL_1MS, 3},//RJS 05Apr00
	Int	VEL_MoveVehicle		=	{Select 0, VEL_1MS, 30},//RJS 05Apr00
	Int	VEL_MoveTank		=	{Select 0, VEL_1MS, 20},//RJS 05Apr00
	Int	VEL_MoveArtillery	=	{Select 0, VEL_1MS, 10},//RJS 05Apr00

//TempCode MS 23Jun99 	Int	VEL_AttackTroop		=	15,		//MS 10Jun99
//TempCode MS 23Jun99 	Int	VEL_AttackMortar	=	0,		//MS 10Jun99
//TempCode MS 23Jun99 	Int	VEL_AttackVehicle	=	15,		//MS 10Jun99
//TempCode MS 23Jun99 	Int	VEL_AttackTank		=	15,		//MS 10Jun99
//TempCode MS 23Jun99 	Int	VEL_AttackArtillery	=	0,		//MS 10Jun99

	Int	VEL_AttackTroop		=	{Select 0, VEL_1MS, 25},//RJS 05Apr00
	Int	VEL_AttackMortar	=	{Select 0, VEL_1MS, 99},//RJS 05Apr00
	Int	VEL_AttackVehicle	=	{Select 0, VEL_1MS, 99},//RJS 05Apr00
	Int	VEL_AttackTank		=	{Select 0, VEL_1MS, 50},//RJS 05Apr00
	Int	VEL_AttackArtillery	=	{Select 0, VEL_1MS, 99},//RJS 05Apr00

	Int	Weap_Basic	= 0,				
	Int	Weap_Rocket	= 1,
	Int	Weap_RockFuel	= 2,
	Int	Weap_BombFuel	= 3,
	Int	Weap_NapmFuel	= 4,
	Int	Weap_BombRock	= 5,
	Int	Weap_NapmRock	= 6,
	

	Y	FT_TakeOff	=	-50,			//MS 30Sep96

	Int	Encounter00Mod	= 0,				//MS 28Aug96
	Int	EncounterHFMod	= 1,				//MS 28Aug96
	Int	Encounter01Mod	= 2,				//MS 28Aug96
	Int	Encounter01HFMod= 3,				//MS 28Aug96
	Int	Encounter02Mod	= 4,				//MS 28Aug96
	Int	Encounter02HFMod= 5,				//MS 28Aug96
	Int	Encounter03Mod	= 6,				//MS 28Aug96
	Int	Encounter03HFMod= 7,				//MS 28Aug96
	Int	Encounter04Mod	= 8,				//MS 28Aug96

 	Int EncounterList01 = {List	EncounterSize,1,1,1,2,2,3,3,4,4},//MS 28Aug96
 	Int EncounterList02 = {List	EncounterSize,1,1,2,3,4,5,6,7,8},//MS 28Aug96
 	Int EncounterList03 = {List	EncounterSize,1,2,3,5,6,7,9,10,12},//MS 28Aug96
 	Int EncounterList04 = {List	EncounterSize,1,2,4,6,8,10,12,14,16},//MS 28Aug96
 	Int EncounterList05 = {List	EncounterSize,1,3,5,7,10,13,15,17,18},//MS 28Aug96
 	Int EncounterList06 = {List	EncounterSize,1,3,6,9,12,14,18,18,18},//MS 28Aug96
 	Int EncounterList08 = {List	EncounterSize,1,4,8,12,16,18,18,18,18},//MS 28Aug96
 	Int EncounterList10 = {List	EncounterSize,1,5,10,15,18,18,18,18,18},//MS 28Aug96
 	Int EncounterList12 = {List	EncounterSize,1,6,12,18,18,18,18,18,18},//MS 28Aug96

	PaintScheme	COL_E0	=0x00000000;		//from specific image map set
	PaintScheme	COL_E1	=0x00000001;
	PaintScheme	COL_E2	=0x00000002;
	PaintScheme	COL_E3	=0x00000003;
	PaintScheme	COL_E4	=0x00000004;
	PaintScheme	COL_E5	=0x00000005;
	PaintScheme	COL_E6	=0x00000006;
	PaintScheme	COL_E7	=0x00000007;

	PaintScheme	COL_SAME=0x00000010;		//from random set, but all same set
	PaintScheme	COL_VARY=0x00000011;		//each part set randomly

	PaintScheme	COL_BOD	=0x10000000;		//specific body parts
	PaintScheme	COL_TAIL=0x01000000;
	PaintScheme	COL_ELEV=0x00100000;
	PaintScheme	COL_WTOP=0x00010000;
	PaintScheme	COL_WBOT=0x00001000;
	PaintScheme	COL_SIG	=0x00000100;

	PaintScheme	COL_ALL	=0x11111100;

	PaintScheme	COL_BOD_TAIL = {Select	COL_BOD,COL_TAIL};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_BOD_TAIL_SIG = {Select COL_BOD,COL_TAIL,COL_SIG};	//grouped body parts	//MS 30Sep96
	PaintScheme	COL_TAIL_ELEV = {Select	COL_TAIL,COL_ELEV};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_WTOP_WBOT = {Select	COL_WTOP,COL_WBOT};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_BOD_WBOT = {Select	COL_BOD,COL_WBOT};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_WBOT_WTOP = {Select	COL_WBOT,COL_WTOP};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_WTOP_TAIL = {Select	COL_WTOP,COL_TAIL};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_SIG_TAIL = {Select	COL_SIG,COL_TAIL};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_ELEV_WBOT = {Select	COL_ELEV,COL_WBOT};	//grouped body parts//MS 30Sep96
	PaintScheme	COL_SIG_ELEV = {Select	COL_SIG,COL_ELEV};	//grouped body parts//MS 30Sep96

	Int	myval=0x12345678;
	Duty	DUTYMIGCAP=AM_DETACHED;
	Duty	DUTYESCORT=AM_DETACHED;
	Duty	DUTY_DiveSingle=AM_DIVEBOMB;
	Duty	DUTY_DiveIndividual=AM_DIVEBOMB;
	Duty	DA_LEVEL=AM_LEVELBOMB;

	Y NEGFT_0 = 0;
	Y NEGFT_20 = FT_20;					//MS 03Jul96
	Y NEGFT_50 = 0;
	Y NEGFT_100 = FT_100;					//MS 02Jul96
	Y NEGFT_200 = 0;
	Y NEGFT_500 = 0;
	Y NEGFT_1000 = FT_1000;					//MS 02Jul96
	Y NEGFT_1800 = 0;
	Y NEGFT_2000 = FT_2000;	
	Y NEGFT_2500 = 0;	

	Y FT_GRND = FT_10;					//MS 02Jul96

	Y FT_EnterLandingPattern = FT_1000;			//MS 11Nov96

	Y FT_CLOUDBASE = FT_5000;				//MS 21Aug96

	Y FT_SpotAlt = FT_4000;					//MS 02Jul96

	Y FT_ReconAlt = FT_4000;				//MS 02Jul96

	Y FT_BombAlt = FT_4000;

	Y FT_BustAlt = FT_4000;					//MS 04Jul96

	Y FT_BombStraffe = FT_4000;				//MS 04Jul96

	Y FT_Straffe = FT_4000;					//MS 12Dec96

	Y FT_InterceptAlt = FT_8000;
//
  //	Abs	BASELOCATION = {PosAfCpRoucourt};		//JIM 02Jul96

//this Position will be supplied by a 3ds ascii file 



	Posn	POS_1QTR		=	{Abs	{Y 1}},
	Posn	POS_3QTR		=	{Abs	{Y 3}},
	Posn	POS_HALF		=	{Abs	{Y 2}},
	


	Int	NEGMETRES800	=	-80000,


	Int	DistEnterLandingPattern = METRES1000,
	Int	NearEnterLandingPattern = METRES100,

//Keep hold of these 
	Int	IDENTRANGE=	METRES1000,	//METRES2500,	//MS 12Aug96
	Int	TWICEIDENTRANGE=METRES2000,	//METRES5000,	//MS 12Aug96
	Int	HALFIDENTRANGE=	METRES500,	//METRES1000,	//MS 12Aug96
	Int	HALFVISINEDGE=	METRES2000,			//MS 11Oct96
	Int	VISINEDGE=	METRES4000,	//METRES5000,	//MS 12Aug96
	Int	VISINEDGE2=	METRES4500,	//METRES6000,	//MS 12Aug96
	Int	VISOUTEDGE=	METRES5000,	//METRES8000,	//MS 12Aug96
//DeadCode RDH 25Oct96 	Int	VISBOUNDARYSIZE=	1000,	//3000,		//MS 12Aug96
	Int	VISBOUNDARYSIZE=	0,	//MSH 25Oct96 Will make AC appear close as pos
	Int	STANDARDTRIGGER=	METRES4000,	//METRES5000,	//METRES5000,//JIM 07Oct96
	Int	HALFSTANDARDTRIGGER=	METRES2000,	//METRES2500,//JIM 07Oct96
	Int	QTRSTANDARDTRIGGER=	METRES1000,		//MS 04Jul96
	Int	MARGIN=	METRES100,
	Int	MARGIN2=	METRES400,
	Int	CAMERATRIGGER=	METRES20,//10
	Int	CAMERATRIGGER2=	METRES40,//20

	Int	ATTACKBALLOONRANGE = METRES2000,
	Int	BEGINRECONRANGE = METRES2000,
	Int	BEGINSPOTRANGE = METRES2000,
	Int	BEGINBOMBRANGE = METRES2000,	
	Int	BEGINSTRAFFERANGE = METRES2000,
	Int	BEGINBOMBSTRAFFERANGE = METRES2000,		//MS 05Jul96
	Int	BEGINEYEBALLRANGE = METRES4000,			//MS 10Dec96
		
//These are test values

//DeadCode MS 04Oct96 	Int	IDENTRANGE=	METRES500,	//METRES1000,	//METRES2500,	//MS 12Aug96
//DeadCode MS 04Oct96 	Int	TWICEIDENTRANGE=METRES1000,	//METRES2000,	//METRES5000,	//MS 12Aug96
//DeadCode MS 04Oct96 	Int	HALFIDENTRANGE= METRES250,	//METRES500,	//METRES1000,	//MS 12Aug96
//DeadCode MS 04Oct96 	Int	VISINEDGE=	METRES2500,	//METRES5000,	//METRES5000,	//MS 12Aug96
//DeadCode MS 04Oct96 	Int	VISINEDGE2=	METRES2500,	//METRES5500,	//METRES6000,	//MS 12Aug96
//DeadCode MS 04Oct96 	Int	VISOUTEDGE=	METRES3000,	//METRES6000,	//METRES8000,	//MS 12Aug96
//DeadCode MS 04Oct96 	Int	VISBOUNDARYSIZE=	1000,	//3000,		//MS 12Aug96
//DeadCode MS 04Oct96 	Int	STANDARDTRIGGER=	METRES2500,	//METRES5000,	//METRES5000,//MS 12Aug96
//DeadCode MS 04Oct96 	Int	HALFSTANDARDTRIGGER=	METRES1000,	//METRES2500,//MS 12Aug96
//DeadCode MS 04Oct96 	Int	QTRSTANDARDTRIGGER=	METRES250,	//METRES1000		//MS 04Jul96
//DeadCode MS 04Oct96 	Int	MARGIN=	METRES50,
//DeadCode MS 04Oct96 	Int	MARGIN2=	METRES100,
//DeadCode MS 04Oct96 	Int	CAMERATRIGGER=	METRES20,//10
//DeadCode MS 04Oct96 	Int	CAMERATRIGGER2=	METRES40,//20
//DeadCode MS 04Oct96 
//DeadCode MS 04Oct96 	Int	ATTACKBALLOONRANGE = METRES500,
//DeadCode MS 04Oct96 	Int	BEGINRECONRANGE = METRES500,
//DeadCode MS 04Oct96 	Int	BEGINSPOTRANGE = METRES500,
//DeadCode MS 04Oct96 	Int	BEGINBOMBRANGE = METRES500,	
//DeadCode MS 04Oct96 	Int	BEGINSTRAFFERANGE = METRES500,
//DeadCode MS 04Oct96 	Int	BEGINBOMBSTRAFFERANGE = METRES500,		//MS 05Jul96


	Int	JUMPINBAND=	METRES1000,

	Int	CLOSETRIGGER	=	100000,

	Skill	SKILL_MEDIUMTOHIGHMIX=	SKILL_VETERAN,

	Morale	MORALE_HIGH	= MORALE_EXCELLENT,
	Morale	MORALE_LOW	= MORALE_VERYPOOR,

//SPRING OFFENSIVE

//DeadCode MS 20Nov96 	Posn	SO14ROUTE_A =
//DeadCode MS 20Nov96 		{Abs	BASELOCATION, 
//DeadCode MS 20Nov96 		 Rel	{X -100000,  Z -100000}
//DeadCode MS 20Nov96 		},

//Route	ROUTE_BOMBHQ=
//{
//WayPoint	ROUTE_BOMBHQ_A,
//WayPoint	ROUTE_BOMBHQ_B,
//WayPoint	ROUTE_BOMBHQ_C,
//WayPoint	ROUTE_BOMBHQ_D,
//WayPoint	ROUTE_BOMBHQ_E,
//WayPoint	ROUTE_BOMBHQ_F,
//WayPoint	ROUTE_BOMBHQ_G,
//WayPoint	ROUTE_BOMBHQ_H,
//WayPoint	ROUTE_BOMBHQ_I,
//WayPoint	ROUTE_BOMBHQ_J,
//WayPoint	ROUTE_BOMBHQ_K
//};
//									//configured skill           {SKILL_NOVICE,	SKILL_POOR  ,	SKILL_REGULAR,	VETERAN			SKILL_ACE   ,	SKILL_HERO
		   //requested skill
  Skill		GetBlueNoviceSkill=	{List BLUESKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE};
  Skill		GetBluePoorSkill=		{List BLUESKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE1,	SKILL_NOVICE1,	SKILL_NOVICE2,	SKILL_NOVICE2,	SKILL_POOR};
  Skill		GetBlueRegularSkill=	{List BLUESKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE1,	SKILL_NOVICE2,	SKILL_POOR1,	SKILL_POOR2,	SKILL_REGULAR};
  Skill		GetBlueVeteranSkill=	{List BLUESKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR1,	SKILL_REGULAR,	SKILL_REGULAR2,	SKILL_VETERAN};
  Skill		GetBlueAceSkill=		{List BLUESKILLCONFIG,SKILL_NOVICE2,SKILL_POOR1,	SKILL_REGULAR,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetBlueHeroSkill=		{List BLUESKILLCONFIG,SKILL_POOR,	SKILL_REGULAR,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE,		SKILL_HERO};

  Skill		GetRedNoviceSkill=	{List REDSKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE,	SKILL_NOVICE};
  Skill		GetRedPoorSkill=		{List REDSKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE1,	SKILL_NOVICE1,	SKILL_NOVICE2,	SKILL_NOVICE2,	SKILL_POOR};
  Skill		GetRedRegularSkill=	{List REDSKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE1,	SKILL_NOVICE2,	SKILL_POOR1,	SKILL_POOR2,	SKILL_REGULAR};
  Skill		GetRedVeteranSkill=	{List REDSKILLCONFIG,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR1,	SKILL_REGULAR,	SKILL_REGULAR2,	SKILL_VETERAN};
  Skill		GetRedAceSkill=		{List REDSKILLCONFIG,SKILL_NOVICE2,	SKILL_POOR1,	SKILL_REGULAR,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetRedHeroSkill=		{List REDSKILLCONFIG,SKILL_POOR,	SKILL_REGULAR,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE,		SKILL_HERO};

  Skill		GetG0SkillMin=			{List Scram_G0_Skill,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR2,	SKILL_REGULAR1,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetG1SkillMin=			{List Scram_G1_Skill,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR2,	SKILL_REGULAR1,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetG2SkillMin=			{List Scram_G2_Skill,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR2,	SKILL_REGULAR1,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetG3SkillMin=			{List Scram_G3_Skill,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR2,	SKILL_REGULAR1,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetG4SkillMin=			{List Scram_G4_Skill,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR2,	SKILL_REGULAR1,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetG5SkillMin=			{List Scram_G5_Skill,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR2,	SKILL_REGULAR1,	SKILL_VETERAN1,	SKILL_ACE};
  Skill		GetG7SkillMin=			{List Scram_G7_Skill,SKILL_NOVICE,	SKILL_NOVICE2,	SKILL_POOR2,	SKILL_REGULAR1,	SKILL_VETERAN1,	SKILL_ACE};

  Skill		GetG0SkillMax=			{List Scram_G0_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};
  Skill		GetG1SkillMax=			{List Scram_G1_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};
  Skill		GetG2SkillMax=			{List Scram_G2_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};
  Skill		GetG3SkillMax=			{List Scram_G3_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};
  Skill		GetG4SkillMax=			{List Scram_G4_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};
  Skill		GetG5SkillMax=			{List Scram_G5_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};
  Skill		GetG6SkillMax=			{List Scram_G6_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};
  Skill		GetG7SkillMax=			{List Scram_G7_Skill,SKILL_POOR,	SKILL_POOR2,	SKILL_REGULAR2,	SKILL_VETERAN1,	SKILL_ACE1,		SKILL_HERO};



//TrainShapeInst1 is actually used as a formpos driven list
  Side		NatG0FST00=	{List FriendlyScoutType00,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG0Squad=	{List Scram_G0_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG1Squad=	{List Scram_G1_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG2Squad=	{List Scram_G2_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG3Squad=	{List Scram_G3_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG4Squad=	{List Scram_G4_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG5Squad=	{List Scram_G5_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG6Squad=	{List Scram_G6_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
  Side		NatG7Squad=	{List Scram_G7_Squad,
					NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,NAT_BLUE,
					NAT_BLUE,NAT_BLUE,	NAT_RED,NAT_RED				};
//DeadCode MS 15Nov99 AirItem dummynameTrainShapeInst1=
//DeadCode MS 15Nov99 {
//DeadCode MS 15Nov99 	Shape	TrainShapeInst1=	
//DeadCode MS 15Nov99 		{	
//DeadCode MS 15Nov99 			List	TPINC,
//DeadCode MS 15Nov99 				TBACK,
//DeadCode MS 15Nov99 			Shape {	Select	
//DeadCode MS 15Nov99 				{	List {Random 3},
//DeadCode MS 15Nov99 					Shape {	List	{Random 6},
//DeadCode MS 15Nov99 							CART1,
//DeadCode MS 15Nov99 							TANKER,
//DeadCode MS 15Nov99 							TCOAL,
//DeadCode MS 15Nov99 							THAUL,
//DeadCode MS 15Nov99 							SUPPLY,
//DeadCode MS 15Nov99 							SUPPLY
//DeadCode MS 15Nov99 					},
//DeadCode MS 15Nov99 					Shape {	List	{Random 6},
//DeadCode MS 15Nov99 							CRANE,
//DeadCode MS 15Nov99 							TWOOD,
//DeadCode MS 15Nov99 							TROOPC,
//DeadCode MS 15Nov99 							TPIPE,
//DeadCode MS 15Nov99 							SUPPLY,
//DeadCode MS 15Nov99 							SUPPLY
//DeadCode MS 15Nov99 					},
//DeadCode MS 15Nov99 					Shape {	List	{Random 6},
//DeadCode MS 15Nov99 
//DeadCode MS 15Nov99 							TCABLE,
//DeadCode MS 15Nov99 							TEMPTY,
//DeadCode MS 15Nov99 							TROLL,
//DeadCode MS 15Nov99 							TGOODS,
//DeadCode MS 15Nov99 							SUPPLY,
//DeadCode MS 15Nov99 							SUPPLY
//DeadCode MS 15Nov99 					}
//DeadCode MS 15Nov99 		}	}	}//,
//DeadCode MS 15Nov99 
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 AirItem dummynameFlakShapeInst1=
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 {
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 	Shape	FlakShapeInst1=	
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 		{	
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 			List	TPINC,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 				TBACK,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 			Shape {	Select	
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 				{	List {Random 3},
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 					Shape {	List	{Random 6},
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							CART1,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							TANKER,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							TCOAL,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							THAUL,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							SUPPLY,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							SUPPLY
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 					},
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 					Shape {	List	{Random 6},
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							CRANE,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							TWOOD,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							TROOPC,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							TPIPE,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							SUPPLY,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							SUPPLY
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 					},
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 					Shape {	List	{Random 6},
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							TCABLE,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							TEMPTY,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							TROLL,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							TGOODS,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							SUPPLY,
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 							SUPPLY
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 					}
//DeadCode MS 15Nov99 //TempCode MS 08Jun99 		}	}	}
//DeadCode MS 15Nov99 };
