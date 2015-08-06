//------------------------------------------------------------------------------
//Filename       aerodev.h
//System         
//Author         Andrew McRae
//Date           Tue 12 Aug 1997
//Description    
//------------------------------------------------------------------------------
#ifndef	AERODEV_Included
#define	AERODEV_Included

#define	DEFAULT_AERODEV 0


class AeroDevice
{

public:

	enum DT_TYPE
	{
		DT_VOID,
		DT_GEAR,
		DT_FLAPS,
		DT_SLATS,
		DT_SPEEDBRAKES,
		DT_DIVEBRAKES,
		DT_CANOPY,
	};

	enum CONTROL_TYPE
	{
		CT_KEYS,
		CT_AUTO
	};

	enum POWER_TYPE
	{
		PT_VOID,
		PT_MANUAL,
		PT_ELECTRIC,
		PT_HYDRAULIC,
		PT_PNEUMATIC
	};

//CONSTANTS
//DeadCode CSB 05/10/99		PMODEL pModel;
//DeadCode CSB 05/10/99	
//DeadCode CSB 05/10/99		DT_TYPE Type;
//DeadCode CSB 05/10/99		FP dCl, dCd, dCm, dAlpha;
//DeadCode CSB 05/10/99	 	SWord Rate;
//DeadCode CSB 05/10/99		KeyVal3D Key;
//DeadCode CSB 05/10/99		UByte	DeviceID;									//RJS 18Sep98
//DeadCode CSB 05/10/99		// For comms and replay....

//NEW CONSTANTS		//CSB 05/10/99	
	AirStrucPtr ControlledAC;
	PMODEL pModel;
	DT_TYPE Type;
	CONTROL_TYPE ControlType;
	POWER_TYPE PowerType;
	FP dCl, dCd, dCm, dAlpha;
	SWord Stages, Rate;
	KeyVal3D UpKey, DownKey;
	SWord BuffetVel;
	UByte	DeviceID;//RJS 18Sep98



//VARIABLES
//DeadCode CSB 05/10/99		SWord Val;
//DeadCode CSB 05/10/99		SWord Attractor;
//DeadCode CSB 05/10/99	// Taken from aerodev.cpp.....
//DeadCode CSB 05/10/99		SWord OldAttractor;									//RJS 29Apr98

//NEW VARIABLES
	SWord Val;
	SWord Attractor;
	SWord OldAttractor;
	SWord ReqVal;
	Bool  Broken;


	AeroDevice (AirStrucPtr const controlledAC,
				PMODEL pmodel,		// parent flight model class
				DT_TYPE type,		// DT_xxxxx
				CONTROL_TYPE controltype,
				POWER_TYPE powertype,
				FP dcl,	  			// delta CL
				FP dcd,				// delta CD
				FP dcm,				// delta CM
				FP dalpha,			// delta Alpha
				SWord stages,
				SWord rate,			// movement rate
				KeyVal3D upkey,		// control key (0 if none)
				KeyVal3D downkey,
				SWord buffetvel,
				UByte* pAnimByte,	// anim byte address
				SLong	minval=0,
				SLong	maxval=16384,
				SLong	Scale=0);		// anim scale

	~AeroDevice ();

	LINKEDLIST<AeroDevice> List;
	void Process ();
	void GearUp ();
	void GearDown ();

	void Action (AirStrucPtr const ControlledAC, CONTROL_TYPE,Bool sendpacket = TRUE);//RJS 21Sep98

} ;

typedef AeroDevice AERODEVICE, *PAERODEVICE;


#endif
//DEADCODE CB 29/10/99 //------------------------------------------------------------------------------
//DEADCODE CB 29/10/99 //Filename       aerodev.h
//DEADCODE CB 29/10/99 //System         
//DEADCODE CB 29/10/99 //Author         Andrew McRae
//DEADCODE CB 29/10/99 //Date           Tue 12 Aug 1997
//DEADCODE CB 29/10/99 //Description    
//DEADCODE CB 29/10/99 //------------------------------------------------------------------------------
//DEADCODE CB 29/10/99 #ifndef	AERODEV_Included
//DEADCODE CB 29/10/99 #define	AERODEV_Included
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 #define	DEFAULT_AERODEV 0
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 class AeroDevice
//DEADCODE CB 29/10/99 {
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 public:
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	enum DT_TYPE
//DEADCODE CB 29/10/99 	{
//DEADCODE CB 29/10/99 		DT_VOID,
//DEADCODE CB 29/10/99 		DT_GEAR,
//DEADCODE CB 29/10/99 		DT_FLAPS,
//DEADCODE CB 29/10/99 		DT_SLATS,
//DEADCODE CB 29/10/99 		DT_SPEEDBRAKES,
//DEADCODE CB 29/10/99 		DT_TANKS
//DEADCODE CB 29/10/99 	};
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	enum CONTROL_TYPE
//DEADCODE CB 29/10/99 	{
//DEADCODE CB 29/10/99 		CT_KEYS,
//DEADCODE CB 29/10/99 		CT_AUTO
//DEADCODE CB 29/10/99 	};
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	PMODEL pModel;
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	DT_TYPE Type;
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	SWord Val;
//DEADCODE CB 29/10/99 	SWord Attractor;
//DEADCODE CB 29/10/99 // Taken from aerodev.cpp.....
//DEADCODE CB 29/10/99 	SWord OldAttractor;									//RJS 29Apr98
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	FP dCl, dCd, dCm, dAlpha;
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	FP scale;
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	SWord Rate;
//DEADCODE CB 29/10/99 	KeyVal3D Key;
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	// For comms and replay....
//DEADCODE CB 29/10/99 	UByte	DeviceID;									//RJS 18Sep98
//DEADCODE CB 29/10/99 	
//DEADCODE CB 29/10/99 //	enum MOVEMENT { STATIONARY=0, MOVEIN=1, MOVEOUT=2, OVERFLOW=3 };
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 //	MOVEMENT Dir;
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	AeroDevice (
//DEADCODE CB 29/10/99 				AirStrucPtr const ControlledAC,
//DEADCODE CB 29/10/99 				PMODEL pmodel,		// parent flight model class
//DEADCODE CB 29/10/99 				DT_TYPE type,		// DT_xxxxx
//DEADCODE CB 29/10/99 				FP dcl,	  			// delta CL
//DEADCODE CB 29/10/99 				FP dcd,				// delta CD
//DEADCODE CB 29/10/99 				FP dcm,				// delta CM
//DEADCODE CB 29/10/99 				FP dalpha,			// delta Alpha
//DEADCODE CB 29/10/99 				SWord rate,			// movement rate
//DEADCODE CB 29/10/99 				KeyVal3D key,		// control key (0 if none)
//DEADCODE CB 29/10/99 				UByte* pAnimByte,	// anim byte address
//DEADCODE CB 29/10/99 				SLong	minval=0,
//DEADCODE CB 29/10/99 				SLong	maxval=16384,
//DEADCODE CB 29/10/99 				SLong	Scale=0);		// anim scale
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	~AeroDevice ();
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	LINKEDLIST<AeroDevice> List;
//DEADCODE CB 29/10/99 	void Process ();
//DEADCODE CB 29/10/99 	void GearUp ();
//DEADCODE CB 29/10/99 	void GearDown ();
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	void Action (AirStrucPtr const ControlledAC, CONTROL_TYPE,Bool sendpacket = TRUE);//RJS 21Sep98
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 } ;
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 typedef AeroDevice AERODEVICE, *PAERODEVICE;
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 #endif
