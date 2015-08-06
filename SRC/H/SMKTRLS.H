//------------------------------------------------------------------------------
//Filename       smktrls.h
//System         
//Author         Robert Slater
//Date           Wed 9 Feb 2000
//Description    
//------------------------------------------------------------------------------
#ifndef	SMKTRLS_Included
#define	SMKTRLS_Included

#define	DEFAULT_SMKTRLS 0

class	CLib3D;
//DEADCODE JON 5/22/00 struct	R3DVERTEX;
class	ViewPoint;

class	TrailInfo												//RJS 09Feb00
{
	CLib3D*			g_lpLib3d;
	DoPointStruc*	newco;
	ViewPoint*		vp;
	Float			v_x, v_y, v_z;

	SWord	bak_vertex0;
	SWord	bak_vertex1;

	MyGroundVectorPtr bak_WCylStartP;
	MyGroundVectorPtr bak_WCylEndP;

	float	bak_xoff0;
	float	bak_yoff0;

	float	bak_xoff1;
	float	bak_yoff1;

	float	bak_oldradius;
	float	bak_radius;

	DoPointStruc	bak_dpfronttrans;
	DoPointStruc	bak_dpbacktrans;

	DoPointStruc	dpfronttrans;
	DoPointStruc	dpbacktrans;

	float	xoff0, xoff1;
	float	yoff0, yoff1;

	DoPointStruc	frontscreen;
	DoPointStruc	backscreen;

	bool	wasLine;
	bool	flipped;

public:

	SLong	pixpercyl;
	SWord	imagemap0;
	SWord	imagemap1;
	SWord	minix0, miniy0;
	SWord	maxix0, maxiy0;
	SWord	minix1, miniy1;
	SWord	maxix1, maxiy1;
	SWord	fadedepth;
	float	oldradius;
	float	radius;
	SLong	visibility;
	SLong	distance;
	SLong	traillength;
	MyGroundVectorPtr	WCylStartP;
	MyGroundVectorPtr	WCylEndP;
	SLong	dist0;
	SLong	dist1;
	SLong	maxradius;
	SWord	vertex0, vertex1;

	void	SetGraphLib(CLib3D*	lib3d){g_lpLib3d = lib3d;}
	void	SetDoPoints(DoPointStruc* coords){newco = coords;}
	void	SetViewPoint(ViewPoint*);
	void	SetVisibility(float,float,float,float);
	void	CalcCylinder();
	void	Init();
	void	Restore();
	void	DuffButNecessary();											//RJS 9Aug00

	void	CheckNearest();
	void	ParticleCylinderImapd();
	void	ParticleStreamImapd();
	void	imaptrailcylWrapped();
	void	DblParticleCylinderImapd();
	void	FadeParticleCylinderImapd();

};

extern	TrailInfo	Smoke_Trails;



#endif
