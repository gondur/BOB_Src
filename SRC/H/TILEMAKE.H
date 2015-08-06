//------------------------------------------------------------------------------
//Filename       tilemake.h
//System         
//Author         Paul.   
//Date           Thu 16 Jul 1998
//Description    
//------------------------------------------------------------------------------
#ifndef	TILEMAKE_Included
#define	TILEMAKE_Included

#define	DEFAULT_TILEMAKE 0

//DeadCode PD 17Apr99 struct ROWANSURFACEDESC
//DeadCode PD 17Apr99 {
//DeadCode PD 17Apr99 	void	*lpSurface;
//DeadCode PD 17Apr99 	ULong	dwWidth,
//DeadCode PD 17Apr99 			dwHeight,
//DeadCode PD 17Apr99 			lPitch,
//DeadCode PD 17Apr99 			dwRGBBitCount;
//DeadCode PD 17Apr99 };

struct DataRecord;

struct Rect
{
	SLong t,b,l,r;
};

const SLong _maxClips=5;

struct ClipInfo
{
	UByte level;
	UByte clipRecIndex;
};

struct SquareClips
{
	UWord count;
	ClipInfo clipInfo[_maxClips];
};

//struct ROWANSURFACEDESC;

class TMake
{
public:
	TMake();
	~TMake();

	void Init(const SLong,const SLong,CLib3D*) const;
	void Reinit(const SLong,const SLong,CLib3D*) const;
	void Exit() const;
	void ChkUpdate(const SLong,const SLong) const;
	DataRecord GetBlock(const SLong x,const SLong z) const;
//DeadCode JON 18Oct00 	void GetSquares(Rect*) const;
//DeadCode JON 18Oct00 	void GetClipRegion(const UByte,Rect&) const;
//DeadCode JON 18Oct00 	void GetTileClipData(SquareClips*&);
//DEADCODE JON 4/14/00 	void BuildShadowList(WorldStuff*,itemptr);
	void FrameInit(WorldStuff *wP,LightVec& sunLight);					//JON 4/14/00
//DEADCODE JON 4/14/00 	void RenderTile2Surface(UByte*,ROWANSURFACEDESC*);
	void Render2Surface(const HTEXT&,UByte,UWord);
	void GetMinMaxAlt(const SLong x,const SLong z,const SWord dir,SLong& min,SLong& max);
//DEADCODE JON 1/27/00 	void GetMinMaxAlt(const SLong x,const SLong z,SLong& min,SLong& max);
//DeadCode JON 18Oct00 	void DoGetTextureScales(SLong&,SLong&,SLong&,SLong&,SLong&,SLong&);
//DEADCODE JON 4/14/00 	ROWANSURFACEDESC* GetRSD(const HTEXT&) const;
//DeadCode JON 18Oct00 	void DoFreeTextures();
//DeadCode JON 18Oct00 	void DoFreeTexture(const HTEXT& ht) const;
//DeadCode JON 18Oct00 	HTEXT DoAllocateTexture(UByte);
	bool CheckCache();
	ImageMapDescPtr GetImageFromArea(UByte);
};

extern TMake* tMake;

#endif
