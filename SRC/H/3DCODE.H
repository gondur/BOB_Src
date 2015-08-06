//------------------------------------------------------------------------------
//Filename       3dcode.h
//System         
//Author         Paul.   
//Date           Wed 23 Aug 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	Dcode_Included
#define	Dcode_Included

	#include	"myANGLES.H"
	#include	"ENUMBITS.M"
	#include	"landscap.h"									//PD 01Oct96


class CLib3D;

struct _D3DVECTOR;
typedef struct _D3DVECTOR NormalData;
//struct NormalData
//{
//	Float i,j,k;
//};

/* struct	Obj_3D : public Base_Obj3D	//moved from 3ddefs to cut dependency on worldinc//JIM 14May96
 {
 	itemptr		ItemPtr;
 	animptr		AnimPtr;
 	fpCOORDS3D	Body;
 	UWord		Shape:15,										//RJS 28Aug98
				IsTransient:1;									//RJS 28Aug98
 	ANGLES		AngH,
 				AngC,
 				AngR;
 };*/

enum	DrawRanges												//RJS 04Jun98
{																//RJS 04Jun98
	RANGE_DEFAULT = 800000,										//RJS 04Jun98
	RANGE_AIRCRAFT = 1966080,									//RJS 04Jun98
	RANGE_AIRCRAFT_FLASH = 1966080,								//RJS 25Jun98
	RANGE_RADAR = 1280000,										//RJS 25Jun98
	RANGE_SHADOW = 160000,										//RJS 08Sep98
	RANGE_FLYBYFAST = 95000,									//RJS 04Sep98
	RANGE_FLYBYSLOW = 217800,									//RJS 04Sep98
	RANGE_CONTRAIL = 4200000,									//RJS 22Jan99
	RANGE_FAR_MIRROR = 100*1000*10,//10km //135184				//JON 4Jul00
};																//RJS 04Jun98

enum	PitTypes {UNMASKED=0,MASKED};						//PD 20Jun96
struct	LiveList;												//JIM 22Sep96
class CMigLand;											//PD 18Jan98
class TMake;

//class btree;
//struct btree::ObjectRec;

class	ThreeDee
{
	CLib3D *g_lpLib3d;

	typedef struct	RGBValues
	{
		UByte	rval,gval,bval;
	}RGBINFO, *RGBINFO_PTR;

	ViewPoint*	View_Point;
	class	btree	*aircraft_tree;

//DeadCode RJS 27Mar00 	CockpitBuf	buffetData;										//PD 29Oct98

	ULong	viewer_x,
			viewer_y,
			viewer_z;

	ANGLES	viewer_hdg,
			viewer_pitch,
			viewer_roll;


 	SLong	view_dt;													//RJS 20Sep00
	ULong	draw_time,													//RJS 20Sep00
			last_time;													//CSB 08/03/00

	animptr	DummyAnimP;													//RJS 22May00

	COORDS3D	lastSunPos;

//DeadCode RJS 15Nov00 	struct SPosRec
//DeadCode RJS 15Nov00 	{
//DeadCode RJS 15Nov00 		enum {Max_Recs=32};
//DeadCode RJS 15Nov00 		itemptr ip;
//DeadCode RJS 15Nov00 		COORDS3D pos;
//DeadCode RJS 15Nov00 	}
//DeadCode RJS 15Nov00 //DeadCode RJS 15Nov00 	posRecTable[SPosRec::Max_Recs];
//DeadCode RJS 15Nov00 	SLong cur_rec;
//DeadCode RJS 15Nov00 	void ResetPosRec() {cur_rec=0;}
//DeadCode RJS 15Nov00 	void StoreAcPos(itemptr ip)
//DeadCode RJS 15Nov00 	{	
//DeadCode RJS 15Nov00 		if (cur_rec<SPosRec::Max_Recs)
//DeadCode RJS 15Nov00 		{
//DeadCode RJS 15Nov00 			posRecTable[cur_rec].ip=ip;
//DeadCode RJS 15Nov00 			posRecTable[cur_rec].pos=ip->World;
//DeadCode RJS 15Nov00 			cur_rec++;
//DeadCode RJS 15Nov00 		}
//DeadCode RJS 15Nov00 	}

	ANGLES	staticH,staticP,staticR;							//PD 05Sep97

	ImageMapDescPtr landdata[4];								//PD 06Nov95
	SLong			whereinpal;									//RJS 22Oct96
	SLong			whichpal;									//RJS 22Oct96
	SLong			oldtime;									//RJS 24Oct96
	Bool			aboveclouds;								//RJS 30Oct96
	Bool			resetpit;								//RJS 30Oct96

	SLong  imagemaps[6];										//MGA 21Feb96
	SLong	time_minutes;										//RJS 23Apr98

	int	MaxShapeCount;											//RJS 20May98
	int	MaxShape2Count;											//RJS 20May98
	int MaxGroupCount;											//RJS 20May98
	int MaxGroup2Count;											//RJS 13Dec99
																//RJS 20May98
	SLong	CheatStart[4];										//RJS 13Dec99
	SLong	CheatEnd[4];										//RJS 13Dec99
	SLong	CheatPos;											//RJS 20May98
	ShapeNum	CheatSave;										//RJS 20May98

	animptr		sunanimptr;										//RJS 02Jul98
	SLong		mapdistz;										//RJS 10Sep98
	SLong		mapoffx;
	SLong		mapoffy;

	ItemPtr		supercheatitem;									//RJS 09Nov98
	SByte		supergroupindex;								//RJS 09Nov98

	animptr		lensflareanim;									//RJS 25Feb00
#ifndef	NDEBUG													//RJS 23Mar00
	animptr	CheatAnimSave;
	animptr	CheatAnim;
#endif

	SLong		mistHeight;												//RJS 26May00
	ULong		mistDensity;											//RJS 26May00

	itemptr		sunItemP;												//RJS 30May00

	bool 		mirrorSeen;										//RJS 12Jul00
	SWord		mirrorMaterial;									//RJS 12Jul00
	Coords3D	mirrorPos;										//RJS 12Jul00
	Coords3D	mirrorOri;										//RJS 12Jul00
	Angles		mirrorFoV;										//RJS 12Jul00

	bool		somethingvisible;										//RJS 23Aug00
	bool		includeClippedObjects;									//RJS 23Aug00
	bool		hasBeenMirror;											//RJS 30Aug00

	D3DVALUE	velCorrect_x;											//RJS 25Sep00
	D3DVALUE	velCorrect_y;											//RJS 25Sep00
	D3DVALUE	velCorrect_z;											//RJS 25Sep00

	public:
		bool drawDescText;
//DeadCode JON 31Aug00 		D3DVALUE	clipNearZ;											//RJS 31Jul00
		float		eye_x;													//RJS 23Aug00
		float		eye_y;													//RJS 23Aug00
		float		eye_z;													//RJS 23Aug00


		void SetMirrorSeen( void ) { mirrorSeen = true; }				//JON 3Jul00
		ULong	theZBufferDepth;								//RJS 08May00
		ULong fogCol;												//JON 4/18/00
		Float	fView_dt_frac;									//RJS 31Mar00
		ANGLES	viewer_oldhdg,
				viewer_oldpitch,
				viewer_oldroll;
		SLong	wind_x, wind_y, wind_z;										//CSB 15Sep00

		class	btree	*bt;
		bool nomorereallygetdata;
		NormalData* normalDataPtr;
//deadcode		UByte*		pNormalLookup;
		Bool		b3DRunning;									//PD 10Jun97
		Bool		shapecheat;									//RJS 24Jul96
		Bool		lightson;									//RJS 04Nov96
		CMigLand*	pMigLand;									//PD 18Jan98
		TMake*		pTMake;										//PD 20Jul98
		ImageMapDescPtr	newpalettes;							//RJS 19Nov96
		LightVec	SunLightVector;								//RJS 16Jul97
		RGBINFO_PTR	NewPalettePtr;								//RJS 24Feb98
		UByteP		MasterPalettePtr;							//RJS 24Feb98
		Bool		radarOn;									//RJS 06Nov98
		bool		havematrix;									//RJS 10Dec98
		Bool		groundlockOn;								//RJS 04Jun99
		ULong		cockpitPrefs;								//RJS 24Mar00
		float		cockScale;											//RJS 30May00

		WorldStuff	*current_world;								//PD 24Apr96
		LiveList	*livelist;
		CON	ThreeDee();											//RJS 24Feb98
		DES	~ThreeDee();										//RJS 24Feb98

		FPMATRIX_PTR fpviewer_matrix,
					 fpviewee_matrix,
					 fpinverse_matrix;
		
		inline void GetSunPos(COORDS3D&);

		FILE*	framefp;												//RJS 20Sep00

//DeadCode RJS 15Nov00 		bool GetPosRec(itemptr ip,COORDS3D& pos)
//DeadCode RJS 15Nov00 		{
//DeadCode RJS 15Nov00         	int	i;	//the standard says... you can't access for statement locals outside 
//DeadCode RJS 15Nov00 			for (i=cur_rec-1;i>=0 && posRecTable[i].ip!=ip;i--) {}
//DeadCode RJS 15Nov00 			if (i==-1) return false;
//DeadCode RJS 15Nov00 			pos=posRecTable[i].pos;
//DeadCode RJS 15Nov00 			return true;
//DeadCode RJS 15Nov00 		}
  		void render(CLib3D*,ViewPoint* vp,WorldStuff *);			//PD 22Apr96
		void Init3D(CLib3D*,ViewPoint*);
		void Done3D(void );
		ULong GetDistance(Obj3DPtr );							//PD 13Mar96
		Bool zclipline(Bool,DoPointStruc,DoPointStruc);
		void	SetVP(ViewPoint*);								//RJS 19Nov98

		void InitialiseCache();									//PD 05Aug98
		void DeleteCache();										//PD 19Jan98

//DeadCode RJS 27Mar00 		void SetCockpitBuffet(CockpitBuf*);

		inline	SLong	ViewerX(){return SLong(viewer_x);}
		inline	SLong	ViewerY(){return SLong(viewer_y);}
		inline	SLong	ViewerZ(){return SLong(viewer_z);}

		inline	bool	ConeCheck(const D3DVECTOR&, const SLong&, const SLong&);//RJS 23Aug00

		void	DeleteFor2D();									//RJS 08Sep00


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetObj3D
//Author		Paul.   
//Date			Tue 7 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
		void SetObj3D(	Obj3DPtr 	obj3dptr,
						itemptr 	itmptr,
						IFShare		bx,
						IFShare		by,
						IFShare		bz,
						IFShare		bzoffset)
		{
			bzoffset.f=0;		//causes more trouble than it's worth//PD 07Dec98
/*			obj3dptr->IsTransient = 0;							//RJS 28Aug98
			switch(itmptr->Status.size)
			{
				default:
				case ItemSize:
					obj3dptr->objtype = STATIC_OBJECT;
					break;

				case TransientSize:
					obj3dptr->IsTransient = 1;					//RJS 28Aug98
				case RotatedSize:
				case MovingSize:
				case MobileSize:
				case FormationSize:
				case ShipSize:
				case AirStrucSize:
					obj3dptr->AngR = ((rotitem *)itmptr)->roll;

				case HPSize:
					obj3dptr->AngC = ((hpitem *)itmptr)->pitch;

				case HdgSize:
					obj3dptr->AngH = ((hdgitem *)itmptr)->hdg;
					obj3dptr->objtype = MOBILE_OBJECT;//PD 12Mar96
					break;
			}
			obj3dptr->Body.X.f 	= bx.f;
			obj3dptr->Body.Y.f 	= by.f;
			obj3dptr->Body.Z.f 	=
			obj3dptr->realbz.f 	= bz.f;
			obj3dptr->Shape 	= itmptr->shape;
			obj3dptr->ItemPtr 	= itmptr;*/
		};

		SWord IntensFromRange(SLong& rng, SLong& start, SLong& end);//PD 09Jan96
//DeadCode AMM 16Apr99 		static void PossMoveCycle();
		void ResetPalette(Bool	forceday=FALSE);				//RJS 24Oct96
		void ResetCompass();									//RJS 21Nov96
		void do_object(itemptr);								//RJS 19Jun97
		void do_object_shad(rotitem*,itemptr);							//RJS 26May00
		void CalcLightsOn(SLong );								//RJS 16Dec96
		SLong AddVapourObject(ShapeNum,UByteP,UByteP,UByteP&,UWord);//RJS 17Sep97
		void AddLensObject(DoPointStruc*,ShapeNum,int,int);		//RJS 21Jan98
		Bool	IsPaused();										//RJS 27Feb98
		SLong GetLandType();									//RJS 24Aug98
		void	DoFlyBySound(AirStrucPtr,SLong);				//RJS 04Sep98
//deadrjs11nov98		void	do_smoke_object(ItemPtr,Coords3D*,ShapeNum,SLong,SLong,SWord,SLong);//RJS 15Sep98
		void	do_object_dummy(itemptr,SLong,itemptr fiddle=NULL);//RJS 04Feb00
		ItemPtr	NearestAliveThing(ItemPtr);						//RJS 16Nov98
		bool	IsItVisible(Coords3D&);							//RJS 18May99
		void	StuffInBinaryTree(ItemPtr);						//DAW 23Apr99
		void	AddNewVapourObject(	ShapeNum,void*,UByteP&,Coords3D&,SLong,ItemPtr);	//RJS 12Sep00
		void	InitPalette(CLib3D*);							//JON 15Feb2000
		SLong View_Dt()		{return(view_dt);};							//RJS 20Sep00
		ULong Draw_Time()	{return(draw_time);};						//CSB 08/03/00
		void	StuffInBinaryTree(ItemPtr,Obj3DPtr);			//RJS 26Apr00
		void	AddObject(const ShapeNum&, const D3DVECTOR&, const ANGLES&, const ANGLES&, const ANGLES&);
		void	RenderMirror();									//RJS 20Jun00
		void	UseMirror(SWord,COORDS3D&,SWord,SWord,SWord,Angles);	//RJS 12Jul00
		void	FreeLandscapeTextures();								//RJS 31Jul00

	private:
		void Add_Sun(rotitem*,WorldStuff* );					//RJS 23Mar98
		void LoadLandData(void );					//PD 06Nov95
		void init_scene(WorldStuff *, ViewPoint*);				//PD 22Apr96
		void do_landscape	();									//PD 20Dec95
		void do_objects(void);
		void do_ui_objects(void);								//PD 12Mar99
		void render_scene	();									//PD 20Dec95
		void exit_3D(void);
		void PaletteBlender(SLong );							//RJS 22Oct96


		void generate_matrix(rotitem&);							//PD 22Apr96
		void add_cockpit(rotitem&,PitTypes,ANGLES,ANGLES,ANGLES);//JIM 10Aug96
		void Add_PeripheralVision(const ItemPtr, const D3DVECTOR&);		//RJS 1Sep00

//TempCode PD 05Dec96 		void do_object(itemptr );								//PD 08Mar96
		void do_object_grp(itemptr );							//PD 08Mar96
		void Add_Shadow(AirStrucPtr,bool);						//RJS 04Feb00
		SLong do_object_vapour(rotitem*,UByteP&,UWord);			//RJS 16Apr98
		void add_map(rotitem&,Bool isZoomed=FALSE);				//RJS 08Sep98
  		void render3d(ViewPoint* vp,WorldStuff *);		//RJS 08Sep98
  		void rendermap(ViewPoint* vp,WorldStuff *);	//RJS 08Sep98
  		void renderzoomedmap(ViewPoint* vp,WorldStuff *);//RJS 08Sep98
		void renderAircraftRoute(void);									//JON 8Nov00
		void renderWaypointTargets( const WayPointPtr waypt );			//JON 8Nov00
//DeadCode RJS 27Apr00 		void do_objects_map(Bool);								//RJS 15Sep98
//DeadCode RJS 27Apr00 		void do_map_object(ItemPtr,SLong);						//RJS 14Sep98
  		void renderreplay(ViewPoint* vp,WorldStuff *);	//AMM 20Oct98
		void add_replay(rotitem& viewpoint);					//AMM 20Oct98
		void SuperShapeCheat();									//RJS 09Nov98
		void AddToObjectRec(void*,ItemPtr,SLong,SLong);					//RJS 26May00
		inline void SetObjectAngles(Obj3DPtr);							//RJS 26May00
		void DrawVisibleObjects();								//RJS 07Feb00
		UByteP	StuffIntoVisibleList(ItemPtr,SLong,D3DVECTOR&, const SLong );	//RJS 26May00
		void ExpandGroup(void*,ItemPtr,SLong);					//RJS 15Feb00
		void ExpandPhotoGroup(void*,ItemPtr, SLong);					//RJS 8Nov00

		void	GetMirrorObjects();								//RJS 20Jun00

inline	void	SetFrameTime();									//RJS 19Sep00

	protected:

		Bool RoughCone(IFShare bx, IFShare by, IFShare bz, SLong shpsize)//RJS 20Aug98
		{
			Float	temp = (Float)1.0;

			bz.f += (Float)shpsize;								//RJS 20Aug98
			if (bz.f<temp) return (FALSE);	//Z-Clipped			//RJS 20Aug98

			temp = (bx.f<0?-bx.f:bx.f)-shpsize;					//RJS 08Jul98
			if (temp < 0)										//RJS 08Jul98
				temp = 0;										//RJS 08Jul98

			if (temp>bz.f)	return (FALSE);

			temp = (by.f<0?-by.f:by.f)-shpsize;					//RJS 08Jul98
			if (temp < 0)										//RJS 08Jul98
				temp = 0;										//RJS 08Jul98

			if (temp>bz.f)	return (FALSE);

			return (TRUE);
		};
		void ConstructNormalData();
		void GetVisibleObjects(WorldStuff*); //PD 06/12/99
		void AddVisibleShape(void *objRec,int index,int realscale);//RJS 04Feb00
//DEADCODE RJS 4/28/00 		void AddVisibleGroup(void *objRec,int index);
		void GetVisibleMapObjects(bool isZoomed=false);			//RJS 27Apr00
		void AddMapToObjectRec(ItemPtr,ShapeNum,SLong);	//RJS 27Apr00

		HRENDERTARGET hrtMirror;
		MAPDESC mdMirror;
//DeadCode JON 17Oct00 		void InitMirror();
//DeadCode RJS 12Jul00 		void RenderMirror(SWord,COORDS3D&,SWord,SWord,SWord,Angles);
};

	extern	class	ThreeDee	Three_Dee;

#endif
