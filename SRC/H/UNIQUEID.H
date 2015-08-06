//;;------------------------------------------------------------------------------
//;;Filename       uniqueid.g
//;;System         
//;;Author         Jim Taylor
//;;Date           Mon 27 Nov 1995
//;;Description    Unique ID equates. 
//;;				Basic bands input and specific item UIDs output
//		NOTE:	/**/ indicates that external parsers will ignore the rest of the line!
//;;------------------------------------------------------------------------------
//;;This bit is manually editable:

#ifndef	UNIQUEIDBAND_Included
#define	UNIQUEIDBAND_Included
enum	UniqueIDBand
												
	{						 									//MS 14Oct98
		PilotedAcBAND			=	0x0000,	  /**/ NULL_BAND=0x0000,
//DeadCode MS 15Nov99 		RedRailBand				=	0x0800,
//DeadCode MS 15Nov99 		RedRoadBAND				=	0x0C00,
//DeadCode MS 15Nov99 		AmberAirfieldBAND		=	0x1200,		BlueAcBANDEND= AmberAirfieldBAND,		
//DeadCode MS 15Nov99 		RedFakeAcBAND			=	0x1400,		AmberAirfieldBANDEND=RedFakeAcBAND,
//DeadCode MS 15Nov99 		RedAAASiteBAND			=	0x1500,			
//DeadCode MS 15Nov99 		BlueAAASiteBAND			=	0x1700,
//DeadCode MS 15Nov99 		RedAAALargeBAND			=	0x1900,
//DeadCode MS 15Nov99   		AmberCivilianBAND		=	0x1A00,	//needs to be bigger
//DeadCode MS 15Nov99 		AmberSupplyBAND			=	0x2500, 
//DeadCode MS 15Nov99 		RedRepairBAND			=	0x2650,
//DeadCode MS 15Nov99 		AmberBridgeBAND			=	0x2700,
//DeadCode MS 15Nov99 		AmberMYardBAND			=	0x2800,
//DeadCode MS 15Nov99 		AmberBattleNodeBAND		=	0x2880,
//DeadCode MS 15Nov99 		RedTrainBAND			=	0x2B00,		AmberBattleNodeBANDEND=RedTrainBAND,
//DeadCode MS 15Nov99 		RedTruckBAND			=	0x2C00,
//DeadCode MS 15Nov99 		RedTruckParkBAND		=	0x2E00,
//DeadCode MS 15Nov99 		RedTroopBAND			=	0x2F00,
//DeadCode MS 15Nov99 		BlueTroopBAND			=	0x2F20,
//DeadCode MS 15Nov99 		RedArmourBAND			=	0x2F40,
//DeadCode MS 15Nov99 		BlueArmourBAND			=	0x2F60,
//DeadCode MS 15Nov99 		RedArtilleryBAND		=	0x2F80,
//DeadCode MS 15Nov99 		BlueArtilleryBAND		=	0x2FB0,
//DeadCode MS 15Nov99 		RedCombatVehicleBAND 	=	0x2FD0,
//DeadCode MS 15Nov99 		BlueCombatVehicleBAND	=	0x3000,
//DeadCode MS 15Nov99 		EventBAND				=	0x3380,
//DeadCode MS 15Nov99 		GreenVetoedBAND			=	0x3400,
//DeadCode MS 15Nov99 		GreenMobileBAND			=	0x3480,
//DeadCode MS 15Nov99 	  	GreenMiscBAND			=	0x3500,
//DeadCode MS 15Nov99 		RedHQBAND				=	0x3580,
//DeadCode MS 15Nov99 		BlueHQBAND				=	0x3600,
//DeadCode MS 15Nov99 		RedBoatBAND				=	0x3680,
//DeadCode MS 15Nov99 		BlueBoatBAND			=	0x3700,
//DeadCode MS 15Nov99 		GreenBoatBAND			=	0x3780,
//DeadCode MS 15Nov99 		RedStaticAcBAND			=	0x3800,
//DeadCode MS 15Nov99 		BlueStaticACBAND		=	0x3840,
//DeadCode MS 15Nov99 
//DeadCode MS 15Nov99 		RunwaySBAND				=	0x3880,
//DeadCode MS 15Nov99 		RunwayEBAND				=	0x38C0,
//DeadCode MS 15Nov99 
//DeadCode MS 15Nov99 
//DeadCode MS 15Nov99 		AfHangerBAND			=	0x3900,		RunwayEBANDEND=AfHangerBAND, //DAW 16/04/99
//DeadCode MS 15Nov99 		AfRevetmentBAND			=	0x3940,
//DeadCode MS 15Nov99 		AfSupplyBAND			=	0x3980,
//DeadCode MS 15Nov99 		AfRunwayBAND			=	0x3B80,
//DeadCode MS 15Nov99 		AfNoScoreBAND			=	0x3C80,		AfRunwayBANDEND=AfNoScoreBAND,

		WayPointBAND			=	0x0100,			
		MissileBAND				=	0x0B00,	/**/	WayPointBANDEND = MissileBAND,
		LandscapeBAND			=	0x0E00,
		SagBAND					=	0x1200,	//Other tables in game rely on size<=256 (MAX_SAGINVALIDATES)
		RealAcBAND				=	0x1300,	/**/	SagBANDEND=RealAcBAND,
		//space here at 1180
		BritAAASiteBAND			=	0x1700,	/**/	RealAcBANDEND=BritAAASiteBAND,
		GermAAASiteBAND			=	0x1800,
		BritAAALargeBAND		=	0x1900,
  		CivilianBAND			=	0x1A00,	
		BritBridgeBAND			=	0x2800,
		BritHistoricBAND		=	0x2880,
		GermMobileBAND			=	0x2900,
		BritMobileBAND			=	0x2980,
	  	NeutMiscBAND			=	0x2A00,
		BritBoatBAND			=	0x2A80,	
		GermBoatBAND			=	0x2B00,
		PowerStationBAND		=	0x2B80,
		OilRefineryBAND			=	0x2C00,
		IndustryBAND			=	0x2C80,
		AircraftFactoryBAND		=	0x2D00,
		DocksBAND				= 	0x2D80,
		PortBAND				=	0x2E00,
		NavalBaseBAND			=	0x2E80,
		CityBAND				=	0x2F00,
		TownBAND				= 	0x3000,
		VillageBAND				=	0x3100,
		BarrageBalloonBAND		=	0x3200,						//MS 10Feb00
		RAF_FighterAFBAND		=	0x3300,//0x3200,	
		RAF_BomberAFBAND		=	0x3380,//0x3280,		
		RAF_CoastalAFBAND		=	0x3400,//0x3300,
		CLRadarBAND				=	0x3460,//0x3380,
		CHRadarBAND				=	0x3470,//0x3400,
		LUF_FighterLF2BAND		=	0x3480,	 //this band has all LW airfields
		LUF_FighterLF3BAND		=	0x3500,	//empty
		LUF_BomberLF2BAND		=	0x3580,	//empty
		LUF_BomberLF3BAND		=	0x3600,	/**/	 LUF_BomberBANDEND,	 //empty
		RefuellerBAND			=	0x3680,	//Loads of space here!!!
		TaxiBAND				=	0x3880,	/**/	RefuellerBANDEND=TaxiBAND,
		SectorOpsBAND			=	0x38D0,	//38ff=tangmere CC
		AfHangarBAND			=	0x3900,	//none//	RunwayEBANDEND=AfHangarBAND, //DAW 16/04/99
		AfStaffBAND				=	0x3910,	//44 instances
		AfStoresBAND			=	0x3940,	//44
		AfFieldBAND				=	0x3970,	//44
		AfNoScoreBAND			=	0x39A0,	//none//	AfRunwayBANDEND=AfNoScoreBAND,
		EventBAND				=	0x39B0,
		RunwaySBAND				=	0x3A80,	//220
		RunwayEBAND				=	0x3B80,	//173
		BlokeBAND				=	0x3C40,	/**/	RunwayEBANDEND=BlokeBAND,	//RJS 11Aug00
		EmergencyVehicleBAND	=	0x3D40,						//RJS 14Jan00
		NavigationBAND			= 	0x3E80, //3eec=Sheerness	//RJS 14Jan00
		NextBAND				=	0x3F00,						//RJS 14Jan00
		LastBAND				=	0x3f00,
		IllegalBAND				=	0x3fff,
	};
#endif
//;;This bit is auto-generated:	
//This bit is auto-generated:	NOT ANY MORE!!!
#ifndef	UNIQUEIDVALS_Included
#define	UNIQUEIDVALS_Included

enum	UniqueID
	{
		#include	"uidvals.g"
		UID_Null				=	0x000,
		UID_NULL				=	0x000,
		PilotedSepID			=	0x000,
		IllegalSepID			=	0x3fff,
		UID_BIT15				=	0x8000,
		UID_BIT14				=	0x4000,
		AbsolutingSepID			=	0xffff
	};
//;;------------------------------------------------------------------------------
//inline UniqueIDBand	operator+(UniqueID u) {return (UniqueIDBand) u;}
//inline UniqueID	operator+(UniqueIDBand u) {return (UniqueID) u;}
//------------------------------------------------------------------------------


#endif


