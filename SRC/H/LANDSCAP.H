//------------------------------------------------------------------------------
//Filename       landscap.h
//System
//Author         Paul.
//Date           Mon 6 Nov 1995
//Description
//------------------------------------------------------------------------------
#ifndef	LANDSCAP_Included
#define	LANDSCAP_Included
		#include "enumbits.m"									//PD 04Dec95
		#include "myvector.h"										//PD 06Sep96
		#include "mystack.h"										//PD 18Oct96
#include	"Palette.h"											//ARM 05Aug96
#include	"ImageMap.h"										//ARM 05Aug96
#include	"display.h"											//ARM 05Aug96
#include	"Areatype.h"										//jon

#define	MAX_RECORD_COUNT	256
#define	DEFAULT_LANDSCAP 0
#define TILE_REZ_LIMIT_ITEM 1

#define	MAX_CRATERS	128											//RJS 18Nov99

const	int	CloudsAt5000ft	= 0x028B0A;							//PD 11Oct96
const	int CloudsAt10000ft	= 2*CloudsAt5000ft;					//PD 11Oct96
const	int	CloudsAt15000ft	= 3*CloudsAt5000ft;					//PD 11Oct96

const UByte ITEM_TYPE_SHEEP = 0;										//JON 24Oct00
const UByte ITEM_TYPE_COW = 1;
const UByte ITEM_TYPE_HAYSTACK = 2;

enum	CloudAlt {CH_5Kft=0,CH_10Kft,CH_15Kft};

//new bits-n-pieces for time of day/bad weather effects

#define	MAX_STOMPERS	8										//RJS 30Nov99
																//RJS 30Nov99
struct	StompyMapType											//RJS 30Nov99
{																//RJS 30Nov99
	SWord	imagemap;											//RJS 30Nov99
	SWord	splodge;											//RJS 30Nov99
};																//RJS 30Nov99

class	SmkCloudDesc													//RJS 24May00
{
	friend	class	LandScape;

protected:

	Coords3D	pos;
	SWord		weight;
	SLong		timealive;
	bool		active;
	animptr		animdata;
	SWord		hdg;

	void	Refresh();

public:

	SmkCloudDesc();
	~SmkCloudDesc();

};



const UWord NULLTILEOFFSET = 0xFFFF;
const UByte OFFSCREENRES = 0xFF;

// used for cacheing the landscape tiles...
class TileElement										//JON 4/26/00
{
public:
	HTEXT textHandle;	// image map number (Word value)				2
	UByte currentRes;	// the current resolution (OFFSCREENRES=none)	1
	UByte desiredRes;	// the desired resolution (OFFSCREENRES=none)	1
//DeadCode JON 2Aug00 	UWord age;			// the last seen age							2
	UByte meshRes;		// the detail level for the polygon data		1
	UByte viewRadius;	// distance in tiles from the view				1
	UWord nextLink;		// the next link in one of the lists			2
												// total num of bytes	8
	inline void reset( void )
	{
		currentRes = OFFSCREENRES;
		desiredRes = OFFSCREENRES;
//DeadCode JON 2Aug00 		age = 0;
		nextLink = NULLTILEOFFSET;
		textHandle = HTEXTNULL;
	}
};

// stores lists of tiles at a certain resolution
class TileResList										//JON 4/27/00
{
public:
	static TileElement* theGrid; // must be set to the tile grid

	UWord	newTile;				//	2
	UWord	underResTile;			//	2	4
	UWord	overResTile;			//	2	6
//DeadCode JON 2Aug00 	UWord	offScreenOldest;		//	2	8
//DeadCode JON 2Aug00 	UWord	offScreenRemaining;		//	2	10
	UWord	offScreen;				//	2	8
//DeadCode JON 2Aug00 	UWord	oldestAge;				//	2	12
//DeadCode JON 2Aug00 	UWord	nextOldestAge;			//	2	14
	SLong 	desiredTiles;			//	4	10
	SLong	freeTiles;				//	4	12
	SLong 	totalTiles;				//	4	14
	UWord	numNewTiles;			//	2	16
	SLong	onScreenMax;			//	4	18
	UByte	polyDetailLevel;		//	1	19

	TileResList() // constructor
	{
		newTile = NULLTILEOFFSET;
		underResTile = NULLTILEOFFSET;
		overResTile = NULLTILEOFFSET;
//DeadCode JON 2Aug00 		offScreenOldest = NULLTILEOFFSET;
//DeadCode JON 2Aug00 		offScreenRemaining = NULLTILEOFFSET;
		offScreen = NULLTILEOFFSET;
		desiredTiles = 0;
		totalTiles = 0;
		onScreenMax = 0;
	}

	inline void reset( void ) // resets the lists to being empty - sets the onscreen max's
	{
		newTile = NULLTILEOFFSET;
		underResTile = NULLTILEOFFSET;
		overResTile = NULLTILEOFFSET;
//DeadCode JON 2Aug00 		offScreenOldest = NULLTILEOFFSET;
//DeadCode JON 2Aug00 		offScreenRemaining = NULLTILEOFFSET;
//DeadCode JON 2Aug00 		nextOldestAge = 0xFFFF; // set to
		offScreen = NULLTILEOFFSET;
		freeTiles = totalTiles;
		desiredTiles = 0;
		numNewTiles = 0;
	}

	static inline void add( UWord& list, UWord offsetToAdd )
	{
		if ( list == NULLTILEOFFSET )
		{
			list = offsetToAdd;
			theGrid[offsetToAdd].nextLink = NULLTILEOFFSET;
		} else
		{
			theGrid[offsetToAdd].nextLink = list;
			list = offsetToAdd;
		}
	}

};

struct SLayerRGB
{
	UWord r,g,b;

	UByte red() {return UByte(r>>8);}
	UByte green() {return UByte(g>>8);}
	UByte blue() {return UByte(b>>8);}
	ULong col() {return RGBMake(red(),green(),blue());}
};

struct SLandLight
{
	COORDS3D pos;
	SLayerRGB color;
	SLong	range;
	SWord	timer;
};

struct SLightingRGB
{
//deadcode  	SLayerRGB	horizonBase;		/* horizon fade colour 		*/
//deadcode	SLayerRGB	horizonMid;			/* colour @ the top of the
//deadcode									   lower horizon strip 		*/
//deadcode	SLayerRGB	horizonUnderClouds;	/* colour underneath the
//deadcode									   cloud layer				*/
//deadcode	SLayerRGB	horizonAtClouds;	/* colour @ the cloud layer */
//deadcode	SLayerRGB	horizonAboveClouds;	/* colour above the clouds	*/
//deadcode	SLayerRGB	horizonTop;			/* colour @ highest point of
//deadcode									   the horizon				*/
	SLayerRGB	landAmbientCollo,landAmbientColhi,landAmbientColamb;			/* Ambient lighting value
																				for the landscape polys	*/
	SLayerRGB	shadedAmbientCollo,shadedAmbientColhi,shadedAmbientColamb;		/* Ambient lighting value
																				for light shaded shapes	*/
	SLayerRGB	staticAmbientCollo,staticAmbientColhi,staticAmbientColamb;		/* Ambient lighting value
																				for non-light shaded
																				shapes					*/
//DeadCode JON 2Nov00 	SLayerRGB	cockpitAmbientCollo,cockpitAmbientColhi,cockpitAmbientColamb;	/* Ambient light for internal 
//DeadCode JON 2Nov00 																				cockpit view */
//DeadCode JON 2Nov00 	SLayerRGB	effectsAmbientCollo,effectsAmbientColhi,effectsAmbientColamb;	/* Ambient light for explosions */

	// for the background horizon...
	SLayerRGB	deepestSkyCol,otherSkyColSun,cloudColSun,horizonColSun,fogColSun;	//JON 4/20/00
	SLayerRGB	otherSkyColShade,cloudColShade,horizonColShade,fogColShade;		//JON 11Sep00

	SLayerRGB	sunCol;

	SLayerRGB	specularHighlight;
};

//------------------------------------------------------------------------------
//Author		Paul.   
//Date			Mon 6 Nov 1995
//Modified	
//
//Description	
//
//Inputs		
//------------------------------------------------------------------------------
class CDataBlock;
//DEAD class Heap<landvertex>;
class ViewPoint;
struct PointDef;
struct DataRecord;
struct AltPointsHdr;
struct Rect;
struct SmallPoint;

struct CHorizData;
struct CPointList;

//DEAD typedef	class Heap<landvertex>	LVHeap,*LVHeapP;


struct	HorizGridOffsets
{
	int hx, hz; // horizon grid offsets 4 col data
	int jx, jz; // offsets for the vertex grid
	HorizGridOffsets()
	{
		reInit();
	}
	inline void reInit()
	{
		hx = -1;
		hz = -1;
		jx = -1;
		jz = -1;
	}

	inline bool hasMoved( const int& x, const int& z )
	{
		return ( x != jx || z != jz );
	}

	inline bool hasHorizMoved( const int& x, const int& z )
	{
		return ( x != hx || z != hz );
	}
	
	inline void set( const int& x, const int& z )
	{
		jx = x;
		jz = z;
	}

	inline bool needColMapUpdate( const int& x, const int& z )
	{
		return ( x < hx-4 || x > hx+4 || z<hz-4 || z>hz+4 );
	}

	inline void setColMapCoords( const int& x, const int& z )
	{
		hx = x;
		hz = z;
	}
};

struct	CraterType
{
	Coords3D	pos;
	SWord		size;
};

class LandScape
{

	StompyMapType	stompMap[MAX_STOMPERS];						//RJS 30Nov99
	SLong			stompMapCnt;

	CraterType	craterLog[MAX_CRATERS];							//RJS 18Nov99
	SLong		craterCnt;										//RJS 18Nov99

	SmkCloudDesc*	smkList;									//RJS 23May00
	
	struct fPos
	{
		float x,y,z;
	};

	
public:
	enum MigLandConsts{

#ifndef	__BCPLUSPLUS__
		//General constants...
		_wholeAreaSizeMAX=33,
		_wholeAreaSizeMIN=17,
		_mediumAreaSize=5,	//2,	//8,
		_centralAreaSize=3,	//1,	//3,
		_blockShift=17,
		_blockWidth=131072,
		_halfBlockWidth=_blockWidth>>1,
		_halfAreaSizeMAX=_wholeAreaSizeMAX>>1,
		_halfAreaSizeMIN=_wholeAreaSizeMIN>>1,
		_sortMinMAX=_halfAreaSizeMAX-_centralAreaSize,
		_sortMinMIN=_halfAreaSizeMIN-_centralAreaSize,
		_sortMaxMAX=_halfAreaSizeMAX+_centralAreaSize,
		_sortMaxMIN=_halfAreaSizeMIN+_centralAreaSize,
		_medMinMAX=_halfAreaSizeMAX-_mediumAreaSize,
		_medMinMIN=_halfAreaSizeMIN-_mediumAreaSize,
		_medMaxMAX=_halfAreaSizeMAX+_mediumAreaSize,
		_medMaxMIN=_halfAreaSizeMIN+_mediumAreaSize,
		_maxalt=257000,
//DeadCode JON 31Aug00 		_hirezDrawDist=1181838,//1351838, (trimmed and accounted for the 0.9 far fog)	//JON 31Aug00
		_hirezDrawDist=(_halfAreaSizeMIN*_blockWidth),

		//grid cone constants
		_cornerLengthMAX=_wholeAreaSizeMAX+1,
		_cornerLengthMIN=_wholeAreaSizeMIN+1,
		_cornerBufferSizeMAX=_cornerLengthMAX*_cornerLengthMAX,
		_cornerBufferSizeMIN=_cornerLengthMIN*_cornerLengthMIN,

		// horizonzone constants
		_horizonDist=15,//17 //60
		_horizonAreaSize=(_horizonDist*2)+1,  //121,
		_horizonPoints=_horizonAreaSize+1,

		//Route types...
		_coast=128,
		_wood=129,
		_lake=130,
		_river=131,
		_track=157,
		_rail=158,
		_road=159,

		//Route detail constants...
		_routeMPolySize=3*_blockWidth,
		_routePolySize=(_centralAreaSize)*_blockWidth,
		_routeLineSize=(_halfAreaSizeMAX-1)*_blockWidth,
		_doNowt=0,
		_doLine=1,
		_doPoly=2,
		_doMPoly=3,

		//Ground detail constants...
		_groundHighSize=_centralAreaSize*_blockWidth,
		_groundMedSize=_mediumAreaSize*_blockWidth,
		_groundLowSizeMAX=_halfAreaSizeMAX*_blockWidth,
		_groundLowSizeMIN=_halfAreaSizeMIN*_blockWidth,
		_doLowGround=255,
		_doMedGround=1,
		_doHighGround=0,
		_landscapeTextures=6,
		_landTextureWH=256,
		_snowLine=50000,
		_mistBase=0,
		_mistTop=25000,
		_numBands=7,	//number of vertical segments in
						//the hemisphere
		_numSegs=32		//number of horizontal segments
						//in the hemisphere
						//NOTE: ((_numBands+1)*_numSegs)+1 
						//		must be less than or equal 
						//		to 257
#endif
	};

	enum{_MaxLights=32};

	SLandLight lightList[_MaxLights];

	UWord lightsActive;
	UWord lightMe;
#ifndef	__BCPLUSPLUS__
	struct SLightTable
	{
		UWord numLights;
		UByte lightIndices[_MaxLights];
	}
	lightTable[_wholeAreaSizeMAX];
#endif
public:

	bool	gunnerDead;													//RJS 24Oct00
	bool	strongSun;													//RJS 31Aug00
	bool	haveSunGlare;												//RJS 19Sep00

	raiseSide* SideLookUp;												//JON 5/3/00

	float	sun_screen_x;
	float	sun_screen_y;
	float	sun_glare;

	ImageMapDescPtr horizonImg;

	SLong GroundHuggingAltitude(MobileItem*);
//deadcode JON 19/06/01		void AddLight(SLandLight*);
//deadcode JON 19/06/01		inline void ResetLights();
//DeadCode JON 20Sep00 	void ProcessLights(SLong,SLong);

	void RefreshLandscape();
	void PossibleTeleport();											//JON 9Oct00
	SLightingRGB	currentLighting;
	SLong groundFogBegin,groundFogEnd,skyFogBegin,skyFogEnd;

	void	LogCrater(Coords3D&,SLong);							//RJS 18Nov99
	void	StompImageMap(SWord,SWord);							//RJS 30Nov99
//deadcode JON 19/06/01		void	ProcessStompMap();									//RJS 30Nov99
	void	DrawHorizon( void );								//JON
	void	DistDrawClouds(SLong );
	void	SetFogBand(); // sets the fog distance band to be correct 4 the length of the horizon
	void	InitTextures( CLib3D *lib3d );												//JON 9Aug00
	Bool  BadVision();								//PD 24Jun96

private:

	int landscapeDelay;				//  delay to build landscape JON 20/06/01

	void RenderSheep(const UByte* pDS,ULong sheepCount,const COORDS3D& view, const PointDef* inptDefs);	//JON 24Oct00

	void DrawCloudLayer( const int hx, const int hz, D3DVECTOR* pos, const bool clockWise );	//JON 25Sep00
 
	SLightingRGB	*pDawn, *pDay, *pDusk, *pNite/*, *pBadW, *pMapL*/;	//JON 2Nov00

	HorizGridOffsets gridOffs;
	HorizGridOffsets cloudOffs;											//JON 27Sep00
	ImageMapDescPtr	cloudImg0;
	ImageMapDescPtr	cloudImg1;
	ImageMapDescPtr	cloudImg2;
//jon	SLong treeHeight;
	RaiseFlag raiseFlag;
	SLong hedgeHeight;
//DeadCode JON 4Oct00 	SLong cliffHeight;

	struct RouteData;

		
	RouteData* pRouteData;

//DeadCode JON 12Sep00 	UByte* gridCorners;

	DoPointStruc horizPoint[_horizonPoints*_horizonPoints];
	UByte* gridCone;
	bool *horizCone;
//DeadCode JON 12Sep00 	UByte* lightCone;
//DeadCode JON 12Sep00 	UByte* routeDetail;
//DeadCode JON 3Aug00 	UByte* groundDetail;
//DeadCode JON 12Sep00 	UByte* landRnd;						//for noise generation
//DeadCode JON 5Sep00 	UByte* softGrid;					//for s/w version item tracking

	bool maxResTiles;													//JON 19Jul00
	TileElement* tileCacheGrid;							//JON 4/26/00
	TileResList tileResList[8];							//JON 4/27/00
	UByte*	meshDetailLevel; // the detail leval at each increacing radius from view		//JON 2Aug00
//DEADCODE JON 4/26/00 	UByte* pLastGrid;
//DEADCODE JON 4/27/00 	HTEXT* pHTextureGrid;
	SLong lastPx,lastPz;

	SLong View_Ground_Height;

	SLong land_min_detail;

	//dome horizon variables
	CHorizData* pointList;
	CPointList* polyList;

	bool meshCreated;	//is it done yet?

	Colour topColor;	//color for top of horizon dome
	Colour midColor;	//color for top of horizon texture strip
	Colour botColor;	//color for horizon fade

	//RGB values for 'topColor'

	UByte topR;
	UByte topG;
	UByte topB;

	//RGB values for 'midColor'

	UByte midR;
	UByte midG;
	UByte midB;

	//number of hemisphere segments to wrap the texture over

	int imageVTile;

	FileNum theHorizonStrip;

	DataRecord*	pDataBlocks;

	COORDS3D* tileCoords;

	SLong	max_body_z;

	SLong	gnd_band_start,gnd_band_end,shape_band_start;
	SLong	sky_band_start,sky_band_end;
	SLong	viewer_x,viewer_y,viewer_z,viewer_dy,cviewer_dy;

//DEADCODE JON 4/6/00 	FPMATRIX_PTR fpviewer_matrix;

	//Poly sorting variables
	LandObj3DPtr list_index,start_index,list_header,list_end;
//DeadCode JON 3Aug00 	DoPointStruc* highco;
	ANGLES	viewer_hdg;
	UWord	list_size;
	ANGLES	viewconeangle;
	SWord	minscale;

	FileNum	FilSkyStrip;									//RJS 24Jun98

	bool	drawLowresHoriz;								// jon 08Mar2000

	public:

	void ResetItemLog();
	bool LogItem(ULong vx,ULong vz,COORDS3D& pos);

	ULong	view_dist;										// jon 08Mar2000
	void RenderMirrorLandscape( void );									//JON 4Jul00

	ViewPoint*	View_Point;
	CLib3D 	*g_lpLib3d;

	SLong	cloud_base;
	COORDS3D	cloudset;									//RJS 01Apr98
	SLong	fade_band_start,fade_band_end,fade_band_mid;
	SLong	Cloud_Layer_Height;
//DEADCODE JON 2/1/00 	SLong	view_range;
	SLong	gvisrange,cvisrange;
	SLong	blackingout,redingout,whitingout;

	Bool	texturedclouds,incloudlayer,bAnyLandDrawn;

	bool	mistenabled;

	animptr	CloudAnimP;											//RJS 21Apr99
	bool	smokePlaneOn;										//RJS 15Feb00

	LandScape::LandScape();
	LandScape::~LandScape();

	Bool SetLighting(SLong);									//RJS 15Jun99

	void Init(CLib3D*);
	void Exit();

	void SetLVector(COORDS3D&);
//DeadCode JON 23Oct00 	void SetFogMode(SLong,SLong);
	void CloudLayer(ViewPoint*);									//PD 05Dec96
	void IncDetailLevel();								//PD 12Sep96
	void DecDetailLevel();								//PD 12Sep96
	SLong SetViewDetail();								//RJS 25Jun98
	void RenderLandscape(	CLib3D * );
//DEADCODE JON 4/6/00 ViewPoint* VP,
//DEADCODE JON 4/6/00 							FPMATRIX_PTR,
//DEADCODE JON 4/6/00 							ULong&, ULong&, ULong&,
//DEADCODE JON 4/6/00 							ANGLES);						//PD 07Jan97
	// set up the landscape visibility stuff before each frame is drawn - passed in view point info
	void  SetUpVisibleCones(	CLib3D *lib3d,
								ViewPoint* vp,
								ULong& wx, ULong& wy, ULong& wz,
								ANGLES heading, bool doMaxResTiles = false);		//JON 4/6/00
	// updateds the horizon texture when given an x and a z in tile space
	void	UpdateHorizTexture( const int x, const int z );				//JON 5/5/00
	void	UpdateHorizTextureIfMoved( const int x, const int z );				//JON 5/5/00
	SLong GetGroundLevel(ItemBasePtr ,UByte* pAreaType=NULL,bool fReallyGetData=false);
	SLong GetGroundLevel(COORDS3D& ,UByte* pAreaType=NULL,bool fReallyGetData=false);
	SLong GetCloudLevel(COORDS3D& );						//PD 22Oct96
	SLong GetFadeStart();									//PD 10May96
	SLong GetFadeEnd();									//PD 10May96
	SLong CloudAlt()	{return (cloud_base);}
	void  CalcVisibleRanges(SLong,SLong);					//PD 14Nov96
	void  ScaleInsideHorizon(COORDS3D&);
	void	SetSkyMap(FileNum);							//RJS 24Jun98

	void	DrawSmokeClouds();									//RJS 23May00
	void	AddSmokeCloud(Coords3D&,const SWord& initialWeight=1);//RJS 23May00
	void	ManageSmokeClouds();								//RJS 24May00
	bool	LoadSmokeClouds(bool);									//RJS 10Jul00
	bool	SaveSmokeClouds();									//RJS 10Jul00
	void	WipeSmokeClouds();											//AMM 27Jul00


	protected:
	void UpdateCloseHorizCornerPoints( const int x, const int z );		//JON 3Aug00

	Bool	SelectTexture(Colour, Colour, Colour, Colour);
	void	MakeTextureInfo(Colour&,ImageMapNumber&,UWord&,UWord&,UWord&,UWord&);
	void	MakeTextureInfoPtr(Colour&, UByte *&);
	void	MakeMaskPtr(UWord, UByte *&);
	void	GeneratePointData(void );
	void	RenderPolyList(void );

	//Revamped cone check routines here

	Bool	GroundTileCone(SLong,SLong,SLong,SLong);		//PD 29Jan97

	private:
	ImageMapDescPtr GetDitherTexture( int areatype );					//JON 15Aug00
	void InterpSLightRGB(SLayerRGB&,SLayerRGB&,SLayerRGB&,ULong);
	SWord IntensFromRange(SLong);						//PD 12Jan96
	void  GenerateGroundPoints(	SLong,SLong,		//PD 22May96
								SLong&, SLong&, SLong&, SLong&);//PD 22May96
	void  DomeHorizon(FileNum);							//RJS 24Jun98
	void  StripHorizon();
	void InfiniteStrip( const ANGLES pitch, const ANGLES roll );
	void GStrip(DoPointStruc**,UByte,UByte,UByte,UByte,UByte,UByte);

//DEADCODE JON 3/30/00 	void  GridCone(const SLong,const SLong);
	bool  FillDataGrid(SLong,SLong);
	bool  LVisCheck(SLong x,SLong z);

//DEADCODE JON 4/27/00 	void ScrollGrid(SLong,SLong,UByte*);
//DEADCODE JON 4/27/00 	void ScrollGridDis(SLong,SLong,HTEXT*,Dropped*);
	void ScrollTileGrid(SLong,SLong);
	bool ManageHighLandTextures(SLong,SLong); // returns value saying if all are at required res..
	void MakeSpaceInList( TileResList* curResList, UWord& numDesired, UWord& listToFree, int& reducedRez );	//JON 17Jul00


//DeadCode JON 12Sep00 	inline SLong perm(SLong x) {return landRnd[x&0xFF];}
//DeadCode JON 12Sep00 	inline UByte index2d(SLong x,SLong y) {return (UByte)perm(x+perm(y));}
//DeadCode JON 12Sep00 	inline UByte index3d(SLong x,SLong y,SLong z) {return (UByte)perm(x+perm(y+perm(z)));}

//deadcode JON 19/06/01		void		DoRain(ViewPoint*,SLong);				//RJS 25Jun98

//deadcode JON 19/06/01		void SetMist(DoPointStruc&);
	void PrintDebugs();

//deadcode JON 19/06/01		void DoCloudLayer();
//deadcode JON 19/06/01		void RenderTrees(UByte*,COORDS3D&);
	void HighDetailTileRender(SLong ,SLong );
	void HorizonTile( const int x, const int z );						//JON 28Sep00
	void HiRezTile(
					const UByte*,
					const ULong,
					const COORDS3D&,
					const TileElement& gridElement,
					const ImageMapDescPtr seaptr, 
					SWord seaAnimOffset);
	void _HiRezTile(
					const UByte* pDS,
					const ULong dataLen,
					const COORDS3D& view,
					const HTEXT& hTexture,
					const bool doDither, 
					const bool doRaises, 
					const bool doHirez,
					const ImageMapDescPtr seaptr, 
					const SWord seaAnimOffset,
					const bool doItems);	//JON 26Jul00
	void LoRezTile(UByte*&,ULong&,COORDS3D&,const HTEXT&);
	void DrawCliffFace( const int& startPoint, const int& endPoint, const class AltPointIndexer &); 	//JON 3/24/00
	void AutoScaleFrameRate();
	void GetMinMaxAlt(AirStrucPtr,SLong&,SLong&);

	struct LPolyDef
	{
		enum {Max_Points=5};
		SWord	count;
		DoPointStruc *point[Max_Points];
	};

	struct LPolyList
	{
		enum {Max_Polys=48};
		SWord		count;
		LPolyDef	poly[Max_Polys];
	};

	class CVertexAllocator
	{
	protected:
		UWord count;
		UWord limit;
		DoPointStruc* pdp;
	public:
		CVertexAllocator() {count=0;pdp=NULL;}
		CVertexAllocator(UWord sz,DoPointStruc* ptr)
		{
			count=0;
			limit=sz;
			pdp=ptr;
		}
		DoPointStruc *alloc()
		{
			if (count<limit)
			{
				DoPointStruc *retval=pdp+count;
				count++;
				return retval;
			}
			return NULL;
		}
	};

	typedef struct _LocalVertex
	{
		R3DVALUE	x,y,z;
		R3DVALUE	u,v;
		ULong		clipFlags;
	}
	LOCALVERT,*LPLOCALVERT;

	#define TILE_WH 33
	#define TILE_OFFX ((TILE_WH-1)>>2)
	#define TILE_OFFZ (TILE_OFFX*TILE_WH)
	#define COORDS_SHIFT 12

	#define OLD_TL	0
	#define OLD_TR	1
	#define OLD_BL	TILE_WH
	#define OLD_BR	(TILE_WH+1)

	#define NEW_TL	0
	#define NEW_TM	1
	#define NEW_TR	2
	#define NEW_ML	TILE_WH
	#define NEW_MM	(TILE_WH+1)
	#define NEW_MR	(TILE_WH+2)
	#define NEW_BL	(TILE_WH+TILE_WH)
	#define NEW_BM	(TILE_WH+TILE_WH+1)
	#define NEW_BR	(TILE_WH+TILE_WH+2)

	#define BODY_X	0
	#define BODY_Y	1
	#define BODY_Z	2

	#define ALT_SCALE00 R3DVALUE(100)
	#define ALT_SCALE01 R3DVALUE(50)
	#define ALT_SCALE02 R3DVALUE(15)

	#define WL_LOWER	1
	#define WL_MIDDLE	2
	#define WL_TOP		4

	UWord *pLevels[8];
	COORDS3D scaleBase[8];
	static R3DVALUE layer00table[512];	//normal
	static R3DVALUE layer01table[512];	//normal
	static R3DVALUE layer02table[512];	//normal
	static R3DVALUE layer10table[512];	//inverted
	static R3DVALUE layer11table[512];	//inverted
	static R3DVALUE layer12table[512];	//inverted
	static LOCALVERT vert[TILE_WH<<1];
	inline void Zoom00(UWord*,UWord*,UWord);
	inline void Zoom01(UWord*,UWord*,UWord);
	inline void Zoom02(UWord*,UWord*,UWord);
	inline void Zoom03(UWord*,UWord*,UWord);
	inline void DoubleRez(UWord*,UWord,UWord*&);
	inline void MakeTopLevel(SLong,SLong,UWord*&);
	void InitialiseCloudTables();
//deadcode JON 19/06/01		void RenderLevel00(const COORDS3D&,UWord*,UWord,R3DVALUE*);
//deadcode JON 19/06/01		void RenderACloudLayer(const COORDS3D&,const UWord);
//deadcode JON 19/06/01		void SmokeyCockpit();
	public:
	bool	UpdateTexturesWRTViewPos();
	void	DrawWayPointIcon( const COORDS3D& pos, const ULong viewerx, const ULong viewery, const ULong viewerz, const int type );	//JON 8Nov00

//DeadCode JON 20Oct00 	void MakeATRecs(UByte *);


};

extern class LandScape Land_Scape;

#endif

