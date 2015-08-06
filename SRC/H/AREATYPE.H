//------------------------------------------------------------------------------
//Filename       areatype.h
//System         
//Author         Paul
//Date           Thu 13 Aug 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	AREATYPE_Included
#define	AREATYPE_Included

#define	DEFAULT_AREATYPE 0

#include <ImageMap.g>
#include "Ranges.h"
//Landscape area type enums
enum AreaType
{
	AT_darkGrass=0, AT_midGrass,	AT_lightGrass,	AT_garden,
	AT_golfCourse,	AT_field1,		AT_field2,		AT_field3,		
	AT_field4,		AT_field5,		AT_spread1,		AT_spread2,		
	AT_spread3,		AT_spread4,		AT_spread5,		AT_woods,		
	AT_swamp,		AT_rough,		AT_roughGrass,	AT_patchyGrass,	
	AT_sea,			AT_stream,		AT_village,		AT_denseTown,	
	AT_sparseTown,	AT_denseCity,	AT_sparseCity,	AT_cityBase,	
	AT_sand,		AT_whiteChalk,	AT_airField,	AT_urbanBuildup,

	AT_MASK=0x1F,
	AT_ROT0=0x1F,	AT_ROT1=0x3F,	AT_ROT2=	0x5F,	AT_ROT3=0x7F, 
	// OR texture with AT_MASK and then compare to find which rotation of textute.
	RT_Lowest=128,
	RT_ARoad=RT_Lowest,
	RT_BRoad,
	RT_MinorRoad,
	RT_Footpath,
	RT_AirField,

	RT_MajorRail=134,
	RT_MinorRail,

	RT_MajorRiver=140,
	RT_MinorRiver,
	RT_Tributary,

	RT_Coast=148,
	RT_Cliff=149,
	RT_CliffRot=149+32,
	RT_HedgerowThick=150,
	RT_HedgerowThin,

	RT_magic=1,													
	HEDGE_HEIGHT=1500, //15m
//DeadCode JON 4Oct00 	CLIFF_HEIGHT=10000, //100m
	AT_NULL=255, // a null value used for flagging...
	RT_NULL=255,
	FULLHTOFFSET=32, // offset for the full heights in RaiseLookUp
	PT_NULL = 255, // null point value

	// route area's - note all sub RT_LOWEST to get the type so the rot masks can be used 
	RA_AROAD = 128 - RT_Lowest,
	RA_BROAD = 129 - RT_Lowest,
	RA_CROSSING1 = 132 - RT_Lowest,
	RA_CROSSING2 = 133 - RT_Lowest,
	RA_MAJORRAIL = 134 - RT_Lowest,
	RA_MINORRAIL = 135 - RT_Lowest,
	RA_ROADJUNCTION = 136 - RT_Lowest,
	RA_RAILJUNCTION = 137 - RT_Lowest,
	RA_MAJRAILROADJUNCT = 138 - RT_Lowest,
	RA_MINRAILROADJUNCT = 139 - RT_Lowest,
	RA_MAJORRIVER = 140 - RT_Lowest,
	RA_MINORRIVER = 141 - RT_Lowest,
	RA_CROSSING3 = 144 - RT_Lowest,
	RA_CROSSING4 = 145 - RT_Lowest,
	RA_RIVAROADJUNCT = 152 - RT_Lowest,
	RA_RIVBROADJUNCT = 154 - RT_Lowest,
	RA_RIVMINRAILJUNCT = 155 - RT_Lowest,
	RA_RIVMAJRAILJUNCT = 156 - RT_Lowest
};

inline bool IsWidenedCrossing( UByte at, int pointcount ) // note any wide poly wiv 3 points is also a crossing...
{
	if ( pointcount == 3 )
		return true;
	ULong at_shift = 1UL<<(at&AT_MASK);
	const ULong at_shift_mask =
				(1UL<<(RA_CROSSING1)) |
				(1UL<<(RA_CROSSING2)) |
				(1UL<<(RA_ROADJUNCTION)) |
				(1UL<<(RA_RAILJUNCTION)) |
				(1UL<<(RA_MAJRAILROADJUNCT)) |
				(1UL<<(RA_MINRAILROADJUNCT)) |
				(1UL<<(RA_CROSSING3)) |
				(1UL<<(RA_CROSSING4)) |
				(1UL<<(RA_RIVAROADJUNCT)) |
				(1UL<<(RA_RIVBROADJUNCT)) |
				(1UL<<(RA_RIVAROADJUNCT)) |
				(1UL<<(RA_RIVMINRAILJUNCT)) |
				(1UL<<(RA_RIVMAJRAILJUNCT));
	return ( (at_shift&at_shift_mask) != 0 );
//DeadCode JON 4Oct00 	at&=AT_MASK;
//DeadCode JON 4Oct00 	return (	at == RA_CROSSING1 ||
//DeadCode JON 4Oct00 				at == RA_CROSSING2 ||
//DeadCode JON 4Oct00 				at == RA_ROADJUNCTION ||
//DeadCode JON 4Oct00 				at == RA_RAILJUNCTION ||
//DeadCode JON 4Oct00 				at == RA_MAJRAILROADJUNCT ||
//DeadCode JON 4Oct00 				at == RA_MINRAILROADJUNCT ||
//DeadCode JON 4Oct00 				at == RA_CROSSING3 ||
//DeadCode JON 4Oct00 				at == RA_CROSSING4 ||
//DeadCode JON 4Oct00 				at == RA_RIVAROADJUNCT ||
//DeadCode JON 4Oct00 				at == RA_RIVBROADJUNCT ||
//DeadCode JON 4Oct00 				at == RA_RIVMINRAILJUNCT ||
//DeadCode JON 4Oct00 				at == RA_RIVMAJRAILJUNCT
//DeadCode JON 4Oct00 				);
}

inline bool IsWideRotation( UByte at )
{
	at-=RT_Lowest;
	return ( at > AT_ROT0 );
}

inline bool IsWidened( const UByte at )
{
	return (at>=RT_Lowest);
}

enum	RaiseFlag { NORAISE, FULLRAISE/*, SCALEDRAISE*/ }; //jon
const ImageMapNumber NULLIMAGE	=	(ImageMapNumber)    0;

struct raiseTable
{
	ImageMapNumber sideImage;
	SLong rot0Alt;
	SLong rot1Alt;
	SLong rot2Alt;
	SLong rot3Alt;
	UByte rot0index;
	UByte rot1index;
	UByte rot2index;
	UByte rot3index;
};

extern raiseTable RaiseLookUp[];

inline ImageMapNumber GetSideImage(UByte at)
{
	return RaiseLookUp[at&AT_MASK].sideImage; // should return different values for different types
}

inline RaiseFlag PreCalcRaise( const long viewer_y, SLong &hedgeHeight )//, SLong &cliffHeight )
{
	static RaiseFlag oldflg = FULLRAISE;
	RaiseFlag flg;
	if ( viewer_y>FT_10000)		flg = NORAISE;
//DeadCode JON 4Oct00 	else if (viewer_y<FT_5000)	flg = FULLRAISE;
//DeadCode JON 4Oct00 	else						flg = SCALEDRAISE;
	else						flg = FULLRAISE;

	if (flg != oldflg)// || flg == SCALEDRAISE)
	{
		oldflg = flg;
		// recalc the heights...
		switch ( flg )
		{
			case FULLRAISE:
			{
				hedgeHeight = HEDGE_HEIGHT;
//DeadCode JON 4Oct00 				cliffHeight = CLIFF_HEIGHT;
				for ( int i=0; i<FULLHTOFFSET; i++ )
					memcpy( &RaiseLookUp[i].rot0Alt,&RaiseLookUp[i+FULLHTOFFSET].rot0Alt,sizeof( SLong )*4 );
//DeadCode JON 20Sep00 					RaiseLookUp[i]=RaiseLookUp[i+FULLHTOFFSET];	
			}
			break;
//DeadCode JON 4Oct00 			case SCALEDRAISE:
//DeadCode JON 4Oct00 			{
//DeadCode JON 4Oct00 				double raiseScale = double(viewer_y-FT_5000)/double(FT_10000-FT_5000);
//DeadCode JON 4Oct00 				for ( int i=0; i<FULLHTOFFSET; i++ )
//DeadCode JON 4Oct00 				{
//DeadCode JON 4Oct00 					if ( RaiseLookUp[i+FULLHTOFFSET].sideImage == NULLIMAGE )
//DeadCode JON 4Oct00 						continue;
//DeadCode JON 4Oct00 //DeadCode JON 4Oct00 					RaiseLookUp[i]=RaiseLookUp[i+FULLHTOFFSET];
//DeadCode JON 4Oct00 					memcpy( &RaiseLookUp[i],&RaiseLookUp[i+FULLHTOFFSET],sizeof( SLong )*4 );
//DeadCode JON 4Oct00 					RaiseLookUp[i].rot0Alt-=SLong(double(RaiseLookUp[i].rot0Alt)*raiseScale);
//DeadCode JON 4Oct00 					RaiseLookUp[i].rot1Alt-=SLong(double(RaiseLookUp[i].rot1Alt)*raiseScale);
//DeadCode JON 4Oct00 					RaiseLookUp[i].rot2Alt-=SLong(double(RaiseLookUp[i].rot2Alt)*raiseScale);
//DeadCode JON 4Oct00 					RaiseLookUp[i].rot3Alt-=SLong(double(RaiseLookUp[i].rot3Alt)*raiseScale);
//DeadCode JON 4Oct00 					hedgeHeight=HEDGE_HEIGHT-SLong(double(HEDGE_HEIGHT)*raiseScale);
//DeadCode JON 4Oct00 
//DeadCode JON 4Oct00 					
//DeadCode JON 4Oct00 //DeadCode JON 4Oct00 					RaiseLookUp[i].rot0Alt-=RaiseLookUp[i].rot0Alt*(viewer_y-FT_5000)/(FT_10000-FT_5000);
//DeadCode JON 4Oct00 //DeadCode JON 4Oct00 					RaiseLookUp[i].rot1Alt-=RaiseLookUp[i].rot1Alt*(viewer_y-FT_5000)/(FT_10000-FT_5000);
//DeadCode JON 4Oct00 //DeadCode JON 4Oct00 					RaiseLookUp[i].rot2Alt-=RaiseLookUp[i].rot2Alt*(viewer_y-FT_5000)/(FT_10000-FT_5000);
//DeadCode JON 4Oct00 //DeadCode JON 4Oct00 					RaiseLookUp[i].rot3Alt-=RaiseLookUp[i].rot3Alt*(viewer_y-FT_5000)/(FT_10000-FT_5000);
//DeadCode JON 4Oct00 //DeadCode JON 4Oct00 					hedgeHeight=HEDGE_HEIGHT-(HEDGE_HEIGHT*(viewer_y-FT_5000)/(FT_10000-FT_5000));
//DeadCode JON 4Oct00 //DeadCode JON 4Oct00 					cliffHeight=CLIFF_HEIGHT-(CLIFF_HEIGHT*(viewer_y-FT_5000)/(FT_10000-FT_5000));
//DeadCode JON 4Oct00 				}
//DeadCode JON 4Oct00 			}
//DeadCode JON 4Oct00 			break;
			case NORAISE:
			{
				hedgeHeight = 0.0;
				for ( int i=0; i<FULLHTOFFSET; i++ )
				{
					RaiseLookUp[i].rot0Alt=0;
					RaiseLookUp[i].rot1Alt=0;
					RaiseLookUp[i].rot2Alt=0;
					RaiseLookUp[i].rot3Alt=0;
				}
			}
			break;
			default:
			_assume(0); // assume we can never get here
			break;
		}
	}
	return flg;
}

inline long GetUnscaledRaiseHt( UByte at )
{
	long retVal;
	switch (at|AT_MASK)
	{
	case AT_ROT0:
		retVal = RaiseLookUp[(at&AT_MASK)+FULLHTOFFSET].rot0Alt; 
		break;
	case AT_ROT1:
		retVal = RaiseLookUp[(at&AT_MASK)+FULLHTOFFSET].rot1Alt;
		break;
	case AT_ROT2:
		retVal = RaiseLookUp[(at&AT_MASK)+FULLHTOFFSET].rot2Alt;
		break;
	case AT_ROT3:
		retVal = RaiseLookUp[(at&AT_MASK)+FULLHTOFFSET].rot3Alt;
		break;
	default:
		retVal = 0; // must be a widened route..
		break;
	}
	return retVal;
}

inline int GetRaisePtOffset( UByte at )
{
	int ptOffset;
	if ( at == AT_NULL )
		ptOffset = 0;
	else 
	{
		switch (at|AT_MASK)
		{
		case AT_ROT0:
			ptOffset = RaiseLookUp[at&AT_MASK].rot0index;
			break;
		case AT_ROT1:
			ptOffset = RaiseLookUp[at&AT_MASK].rot1index;
			break;
		case AT_ROT2:
			ptOffset = RaiseLookUp[at&AT_MASK].rot2index;
			break;
		case AT_ROT3:
			ptOffset = RaiseLookUp[at&AT_MASK].rot3index;
			break;
		default:
			// big error - shouldn't be possible to get here
//			INT3;
			ptOffset = 0;
			break;
		}
	}
	return ptOffset;
}

// returns the height, passes back the offset to the point index...
inline long GetRaiseInfo( UByte at, int& ptOffset )
{
	long retVal;
	if ( at == AT_NULL )
		retVal = 0;
	else 
	{
		switch (at|AT_MASK)
		{
		case AT_ROT0:
			retVal = RaiseLookUp[at&AT_MASK].rot0Alt; 
			ptOffset = RaiseLookUp[at&AT_MASK].rot0index;
			break;
		case AT_ROT1:
			retVal = RaiseLookUp[at&AT_MASK].rot1Alt;
			ptOffset = RaiseLookUp[at&AT_MASK].rot1index;
			break;
		case AT_ROT2:
			retVal = RaiseLookUp[at&AT_MASK].rot2Alt;
			ptOffset = RaiseLookUp[at&AT_MASK].rot2index;
			break;
		case AT_ROT3:
			retVal = RaiseLookUp[at&AT_MASK].rot3Alt;
			ptOffset = RaiseLookUp[at&AT_MASK].rot3index;
			break;
		default:
			// big error - shouldn't be possible to get here
//			INT3;
			retVal = 0;
			break;
		}
	}
	return retVal;
}

inline long GetRaiseHeight( UByte at )
{
	long retVal;
	if ( at == AT_NULL )
		retVal = 0;
	else 
	{
		switch (at|AT_MASK)
		{
		case AT_ROT0:
			retVal = RaiseLookUp[at&AT_MASK].rot0Alt; 
			break;
		case AT_ROT1:
			retVal = RaiseLookUp[at&AT_MASK].rot1Alt;
			break;
		case AT_ROT2:
			retVal = RaiseLookUp[at&AT_MASK].rot2Alt;
			break;
		case AT_ROT3:
			retVal = RaiseLookUp[at&AT_MASK].rot3Alt;
			break;
		default:
			// big error - shouldn't be possible to get here
//			INT3;
			retVal = 0;
			break;
		}
	}
	return retVal;
}

const int NUM_SIDE_TYPES = 98;

struct raiseSide
{
	UByte lowerAT;
	UByte higherAT;
	raiseSide() {} // default constructor
	raiseSide( UByte low, UByte high ) // constuctor
	{
		lowerAT = low;
		higherAT = high;
	}
	inline bool operator==( const raiseSide &other )
	{
		return (	/*GetUnscaledRaiseHt(lowerAT) == GetUnscaledRaiseHt(other.lowerAT) && */
					GetRaisePtOffset(lowerAT) == GetRaisePtOffset(other.lowerAT) &&		//JON 20Sep00
					higherAT == other.higherAT );
	}
	inline bool isWanted() // returns true if the side is wanted
	{
		return ( GetUnscaledRaiseHt( higherAT ) > GetUnscaledRaiseHt( lowerAT ) );
	}
};

//static raiseSide* SideLookUp = NULL;

inline bool IsCliffBottom(UByte at) 
{
//DeadCode JON 4Oct00 	at&=AT_MASK; 
//DeadCode JON 4Oct00 	return (/*at==AT_coastRock||*/at==AT_sea||at==AT_sand||at==AT_whiteChalk); 
	ULong at_shift = 1UL<<(at&AT_MASK);
	const ULong at_shift_mask =
				(1UL<<(AT_sea)) |
				(1UL<<(AT_sand)) |
				(1UL<<(AT_whiteChalk));
	return ( (at_shift&at_shift_mask) != 0 );

}
inline bool IsRaised(UByte at) 
{
//DeadCode JON 4Oct00 	at&=AT_MASK; 
//DeadCode JON 4Oct00 	return (at==AT_woods||at==AT_denseTown/*||at==AT_sparseTown*/||at==AT_denseCity||at==AT_sparseCity);
	ULong at_shift = 1UL<<(at&AT_MASK);
	const ULong at_shift_mask =
				(1UL<<(AT_denseTown)) |
				(1UL<<(AT_denseCity)) |
				(1UL<<(AT_woods))     |
				(1UL<<(AT_sparseCity));				
return ( (at_shift&at_shift_mask) != 0 );

}
// is the area type hirez?
inline bool IsHirez(UByte at)
{
//DeadCode JON 4Oct00 	at&=AT_MASK;
//DeadCode JON 4Oct00 	return (at==AT_village||at==AT_denseTown||at==AT_sparseTown||at==AT_denseCity||at==AT_sparseCity);
	ULong at_shift = 1UL<<(at&AT_MASK);
	const ULong at_shift_mask =
				(1UL<<(AT_village)) |
				(1UL<<(AT_denseTown)) |
				(1UL<<(AT_sparseTown)) |
				(1UL<<(AT_denseCity)) |
				(1UL<<(AT_sparseCity));
	return ( (at_shift&at_shift_mask) != 0 );

}
inline bool IsWater(UByte at) 
{
//DeadCode JON 4Oct00 	return (at==AT_sea||at==AT_stream );
	ULong at_shift = 1UL<<(at&AT_MASK);
	const ULong at_shift_mask =
				(1UL<<(AT_sea)) |
				(1UL<<(AT_stream));
	return ( (at_shift&at_shift_mask) != 0 );

}
inline bool IsForest(UByte at) {at&=AT_MASK; return (at==AT_woods);}
inline bool IsWooded(UByte at) {return false;}
inline bool IsValidRoute(UByte at) 
{
//DeadCode JON 4Oct00 	return (at==RT_ARoad		|| at==RT_BRoad			|| at==RT_MinorRoad ||
//DeadCode JON 4Oct00 			at==RT_Footpath		|| at==RT_MajorRail		|| at==RT_MinorRail ||
//DeadCode JON 4Oct00 			at==RT_MajorRiver	|| at==RT_MinorRiver	|| at==RT_Tributary || 
//DeadCode JON 4Oct00 			at==RT_HedgerowThick|| at==RT_HedgerowThin	|| at==RT_Coast		|| 
//DeadCode JON 4Oct00 			at==RT_AirField		|| at==RT_Cliff			|| at==RT_CliffRot);
// optimised to:
//	at&=AT_MASK;
	ULong at_shift = 1UL<<(at&AT_MASK);
	const ULong at_shift_mask =
				(1UL<<(RT_ARoad-RT_Lowest)) |
				(1UL<<(RT_BRoad-RT_Lowest)) |
				(1UL<<(RT_MinorRoad-RT_Lowest)) |
				(1UL<<(RT_Footpath-RT_Lowest)) |
				(1UL<<(RT_MajorRail-RT_Lowest)) |
				(1UL<<(RT_MinorRail-RT_Lowest)) |
				(1UL<<(RT_MajorRiver-RT_Lowest)) |
				(1UL<<(RT_MinorRiver-RT_Lowest)) |
				(1UL<<(RT_Tributary-RT_Lowest)) |
				(1UL<<(RT_HedgerowThick-RT_Lowest)) |
				(1UL<<(RT_HedgerowThin-RT_Lowest)) |
				(1UL<<(RT_Coast-RT_Lowest)) |
				(1UL<<(RT_AirField-RT_Lowest)) |
				(1UL<<(RT_Cliff-RT_Lowest));

	return ( (at_shift&at_shift_mask) != 0 );
}

inline bool IsCliffRoute(UByte at)
{
	at-=RT_Lowest;
	at&=AT_MASK;
	at+=RT_Lowest;
	return ( at == RT_Cliff );
}

#endif
