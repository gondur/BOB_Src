//------------------------------------------------------------------------------
//Filename       sky.h
//System         
//Author         Andrew McRae
//Date           Mon 10 Mar 1997
//Description    
//------------------------------------------------------------------------------
#ifndef	SKY_Included
#define	SKY_Included

#define	DEFAULT_SKY 0
#include "modvec.h"


class Gust
{
public:

	Bool ACTIVE;
	FCRD Vec;
	SWord Time;
	Gust ()
	{
		ACTIVE = FALSE;
		Time = 0;
	}

};
typedef class Gust GUST, *PGUST;

class Cloud
{
public:
	SLong AltBase;
	SLong AltTop;
	UByte Cover;
	void NullCloud();
	void SetCloud(SLong base, SLong top, UByte cover);
};
typedef class Cloud CLOUD, *PCLOUD;

//enum	{CLEAR, RAIN, SNOW}:

//#define DEFAULT_CONTRAIL_LEVEL FEET2CM(41000)	// put this in sky class
//DeadCode RJS 09Dec99 #define MAXIMUM_CONTRAIL_DURATION 90000
#define MAXIMUM_CONTRAIL_DURATION 1000	//10 secs...
class AtmosphereData
{
public:
	FP	TempVar;			//K variation in temp last time
	FP	Temp0;				//K	temp at seal level
	FP	Press0;				//millibar
	FP  Density0;			//kg/m3 @ SL	//CSB 27/10/98
	FP	wind0;				//mph
	FP	dir0;				//direction in degrees
	FP	windalt;			//mph
	FP	diralt;				//direction in degrees
	FCRD Wind0;				// wind at zero height
	FCRD WindAlt;			// wind at altitude
	SLong WindAltHeight;		// height of above		//RJS 02Nov98
	SWord MinDuration;		// csecs
	SWord MaxDuration;		// csecs
	FP MinMagnitude;		// 1 = 1 m/s
	FP MaxMagnitude;		// 1 = 1 m/s
	UWord Frequency;		// 0 = always, 65535 = very infrequent
 	//contrails
	FP	ContrailBandCentre;
	FP	ContrailBandWidth;

	FP	Visibility;			// in cm
	FP	Conditions;			//CLEAR, RAIN, SNOW
	FP	CloudLayer;			// bottom layer in cm

	Cloud Layer[3];
	Cloud FluffyCloud;

	bool	MistInValley;

};
class	Curve;
typedef	 Curve CURVE, *PCURVE, **PPCURVE;

class Atmosphere:	public	AtmosphereData 
{
public:

	// *************************************

//DeadCode CSB 27/10/98		// New Stuff
//DeadCode CSB 27/10/98	//Craig will change the code soon so that these will become redundant
//DeadCode CSB 27/10/98		PCURVE pMinTemp;
//DeadCode CSB 27/10/98		PCURVE pMaxTemp;
//DeadCode CSB 27/10/98		PCURVE pMinPressure;
//DeadCode CSB 27/10/98		PCURVE pMaxPressure;
//DeadCode CSB 27/10/98	
//DeadCode CSB 27/10/98		FP TempFrac;
//DeadCode CSB 27/10/98		FP PressureFrac;

	// *************************************

	// conditions
//	FP Temp0;	// Temperature at sea level			   	(288)
//DeadCode CSB 17/11/98		FP Temp1;	// Temperature at 36,089 feet and above	(217)
//	FP Pres0;	// Pressure at sea level 				(101300)
//DeadCode CSB 17/11/98		FP Pres1;
	FP a;

	// wind
//	Bool WIND;
//	FCRD Wind;
	// new wind (variable with height)

	// gusts
//	Bool GUSTS;
//	GUST Gust;
	FP SeaLevelDensity;


//	Atmosphere ();
	
//DeadCode CSB 27/10/98		void SetConditions (FP, FP, FP);
//DeadCode CSB 27/10/98		void SetConditions (FP, FP);
//	void Atmosphere::SetContrails (FP contraillevel);
	void Atmosphere::SetMissionConditions ();
	void Atmosphere::SetMissionTemp (SWord month);
	void Atmosphere::SetMissionPress (SWord month);
	void Atmosphere::SetMissionDensity();
	void Atmosphere::SetMissionClouds(	SLong base0 = -1, SLong top0 = -1, UByte cover0 = 0, 
										SLong base1 = -1, SLong top1 = -1, UByte cover1 = 0,
										SLong base2 = -1, SLong top2 = -1, UByte cover2 = 0,
										SLong baseF = -1, SLong topF = -1, UByte coverF = 0);

	void Atmosphere::SetMissionWind (SWord month);
	void Atmosphere::SetMissionDawnDusk (SWord Latitude, ULong Date, SLong& Dawn, SLong& Dusk);

	UByte Atmosphere::CloudLayerCover(Coords3D* pos);

	Bool Ambient (FP, FP&, FP&, FP&);
	Bool GetWindDirVel (SLong, SWord&, SLong&);							//CSB 10/06/99	
	Bool GetWind (AirStrucPtr const ControlledAC,FCRD&, FP);		// wind and gusts
	FP	 GetWind (SLong, SLong&, SLong&, SLong&); // wind only			//RJS 16Dec99
	void GetWindDirVel (SLong, SWord&, FP&);							//RJS 16/12/99	

//	void SetWind (FP, FP, FP);
	void SetWind (FCRD&, FCRD&, FP);
//	void SetWind (Bool state) { WIND = state; }

	void SetGusts (SWord, SWord, FP, FP, UWord);
//	void SetGusts (Bool state) { GUSTS = state; }

	Bool Contrails (AirStrucPtr, ULong&);

};
class Atmosphere;
typedef Atmosphere ATMOSPHERE, *PATMOSPHERE;


#endif

