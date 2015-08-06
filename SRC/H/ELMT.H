//------------------------------------------------------------------------------
//Filename       elmt.h
//System         
//Author         Andrew McRae
//Date           Thu 24 Apr 1997
//Description    
//------------------------------------------------------------------------------

#ifndef	ELMT_Included
#define	ELMT_Included


// Aircraft Element Types (order specific)
enum ELMT_TYPE
{
	AET_INACTIVE,
	AET_SURFACE,
	AET_MASS,
//CSB	AET_DRAG,
	AET_BLADE,
	AET_THRUST
};

// surface types
enum SURFACE_TYPE
{
	ST_VOID,
	ST_PLANE,
	ST_MAINPLANE,
	ST_DUALMAINPLANE,
	ST_CYLINDER,
	ST_SYMETRICAL
};

enum SURFACE_DESCRIPTION
{
	SD_VOID,
	SD_INNERPORTWING,
	SD_INNERSTBDWING,
	SD_OUTERPORTWING,
	SD_OUTERSTBDWING,
	SD_MAINPLANE,
	SD_PORTWING,
	SD_STBDWING,
	SD_TAILPLANE,
	SD_FIN
};

	

// thrust types
enum THRUST_TYPE
{
	TT_JET,
	TT_PROP
};
///////////////////////////////////////////////////////////////////////////////////

class MainPlane
{

public:

	PMODEL pModel;//

	PTHRUSTPOINT pSlipThrustPoint[2];
	char AmountInSlipstream;

//DeadCode AMM 29Jun99 	ULong cCtrls;
//DeadCode AMM 29Jun99 	PCTRL pCtrls;
	PNEWCTRL pNewCtrls;

	FCRD Pos[2][2];		//CSB 06/11/98	
	FORI Ori[2][2];		//CSB 06/11/98
	FP MaskAngle[2][2];	//CSB 25/11/98	//This is the sideslip angle at which the element
	char MaskArea[2][2];									//is totally within the fuselage wake (Local Coords)

	ULong Area,  wArea[2];//
	SWord Chord, wChord[2];//
	SWord Span,  wSpan[2];

	FP Cdo, k;	//
	FP dCMdq;	//Pitching Moment Coefficient due to Pitch Rate
	FP dCMdp;	//Rolling Moment Coefficient due to Roll Rate
	FP dCMdr;	//Yawing Moment Coefficient due to Yaw Rate

	PCURVE pClCurve;//
	PCURVE pCdCurve;//
	PCURVE pCompCd0Curve;//
	PCURVE pCompKCurve;//
	PCURVE pCmCurve;//

	FP AoaMax,AoaMin;//

	FP aoa [2][2];
	FP fCd0Mach;// reset in header
	FP fKMach;	// reset in header

	FP DownWashAng[2];
//DeadCode AMM 29Jun99 	Bool stalled[2][2];
//DeadCode AMM 29Jun99 	FP StallAoa, UnStallAoa;
	FP buffetAoa0,buffetAoa1;		//Angle of attack for onset and full buffet at M=0
	FP buffetM0,  buffetM1;			//Mach no for onset and full buffet at Alpha=0
	FP BuffetAoaMin;
	FP BuffetAoaMax;

	FP ACMmaxaoa;					//maximum angle of attack allowed by ACM;

	FCRD eForce[2][2];
	FCRD eMoment[2][2];

	MainPlane (PMODEL pmodel,
				int area0,
				SWord chord0,
				SWord span0,
				int area1,
				SWord chord1,
				SWord span1)

	{
		pModel	= pmodel;	
		wArea[0]	= area0;
		wArea[1]	= area1;
		Area		= 2 * (area0 + area1);
		wChord[0]	= chord0;
		wChord[1]	= chord1;
		Chord		= 0.5 * (chord0 + chord1);
		wSpan[0]	= span0;
		wSpan[1]	= span1;
		Span		= 2 * (span0 + span1);
		pClCurve = NULL;
		pCdCurve = NULL;
		pCompCd0Curve = NULL;
		pCompKCurve = NULL;
		pCmCurve = NULL;
		dCMdq = 0;
		dCMdp = 0;
		dCMdr = 0;
		fCd0Mach = 1;
		fKMach   = 1;

//DeadCode AMM 29Jun99 		cCtrls = 0;
//DeadCode AMM 29Jun99 		pCtrls = NULL;
		pNewCtrls = NULL;

//DeadCode AMM 29Jun99 		StallAoa = 0;
//DeadCode AMM 29Jun99 		UnStallAoa = 0;

		for(SWord wing = 0; wing < 2; wing++)
			for(SWord section = 0; section < 2; section++)
			{
				aoa[wing][section] = 0.0;
//DeadCode AMM 29Jun99 				stalled[wing][section] = FALSE;
				NullVec(eForce[wing][section]);
				NullVec(eMoment[wing][section]);
				MaskAngle[wing][section] = 0.0;
				MaskArea[wing][section] = 0;
			}

		pSlipThrustPoint[0] = NULL;
		pSlipThrustPoint[1] = NULL;
		AmountInSlipstream = 0;

		List.Attach (&pModel->MainPlaneList, this);
	}

	~MainPlane ()
	{
//DeadCode AMM 29Jun99 		while (pCtrls != NULL) delete pCtrls;
		while (pNewCtrls != NULL) delete pNewCtrls;
		List.Detach (this);
	}

	LINKEDLIST<MainPlane> List;


	void SetPosition (FP x0, FP y0, FP z0, FP x1, FP y1, FP z1)		//CSB 06/11/98
	{
		Pos[0][0].x = x0;	//Stbd Inn
		Pos[0][0].y = y0;
		Pos[0][0].z = z0;

		Pos[0][1].x = x1;	//Stbd Out
		Pos[0][1].y = y1;
		Pos[0][1].z = z1;

		Pos[1][0].x = -x0;	//Port Inn
		Pos[1][0].y =  y0;
		Pos[1][0].z =  z0;

		Pos[1][1].x = -x1;	//Port Out
		Pos[1][1].y =  y1;
		Pos[1][1].z =  z1;
	}

	// Stbd Values Only
	void SetOrientation (FP x0, FP y0, FP z0, FP x1, FP y1, FP z1)
	{
// Order of rotation z - y - x. In local coords.
		Ori[0][0].x.x = FCos (Degs2Rads (z0));		//Stbd Inn
		Ori[0][0].x.y = FSin (Degs2Rads (z0));
		Ori[0][0].x.z = 0;

		Ori[0][0].y.x = -FSin (Degs2Rads (z0));
		Ori[0][0].y.y =  FCos (Degs2Rads (z0));
		Ori[0][0].y.z =  0;

		Ori[0][0].z.x = 0;
		Ori[0][0].z.y = 0;
		Ori[0][0].z.z = 1;

		RotOriYVec (Ori[0][0], Degs2Rads (y0));
		RotOriXVec (Ori[0][0], Degs2Rads (x0));

//////////////////
		Ori[0][1].x.x = FCos (Degs2Rads (z1));		//Stbd Out
		Ori[0][1].x.y = FSin (Degs2Rads (z1));
		Ori[0][1].x.z = 0;

		Ori[0][1].y.x = -FSin (Degs2Rads (z1));
		Ori[0][1].y.y =  FCos (Degs2Rads (z1));
		Ori[0][1].y.z =  0;

		Ori[0][1].z.x = 0;
		Ori[0][1].z.y = 0;
		Ori[0][1].z.z = 1;

		RotOriYVec (Ori[0][1], Degs2Rads (y1));
		RotOriXVec (Ori[0][1], Degs2Rads (x1));

/////////////////
		Ori[1][0].x.x = FCos (Degs2Rads (-z0));			// Port Inn
		Ori[1][0].x.y = FSin (Degs2Rads (-z0));
		Ori[1][0].x.z = 0;

		Ori[1][0].y.x = -FSin (Degs2Rads (-z0));
		Ori[1][0].y.y =  FCos (Degs2Rads (-z0));
		Ori[1][0].y.z =  0;

		Ori[1][0].z.x = 0;
		Ori[1][0].z.y = 0;
		Ori[1][0].z.z = 1;

		RotOriYVec (Ori[1][0], Degs2Rads (-y0));
		RotOriXVec (Ori[1][0], Degs2Rads (x0));

/////////////////
		Ori[1][1].x.x = FCos (Degs2Rads (-z1));			// Port Out
		Ori[1][1].x.y = FSin (Degs2Rads (-z1));
		Ori[1][1].x.z = 0;

		Ori[1][1].y.x = -FSin (Degs2Rads (-z1));
		Ori[1][1].y.y =  FCos (Degs2Rads (-z1));
		Ori[1][1].y.z =  0;

		Ori[1][1].z.x = 0;
		Ori[1][1].z.y = 0;
		Ori[1][1].z.z = 1;

		RotOriYVec (Ori[1][1], Degs2Rads (-y1));
		RotOriXVec (Ori[1][1], Degs2Rads (x1));
	}

	void SetMaskAngle (FP ang0, FP ang1, char Area0, char Area1)
	{
		MaskAngle[0][0] =  ang0;
		MaskAngle[0][1] =  ang1;
		MaskAngle[1][0] = -ang0;
		MaskAngle[1][1] = -ang1;
		MaskArea[0][0] = Area0;
		MaskArea[1][0] = Area0;
		MaskArea[0][1] = Area1;
		MaskArea[1][1] = Area1;
	}
	
	void Process (AirStrucPtr const ControlledAC);

	void SetCurves (
			char* aircraft_name_ident,
			char* cl_curve_ident,
			char* cd_curve_ident,
			char* compcd0_curve_ident,
			char* compk_curve_ident,
			char* cm_curve_ident)

	{

		pClCurve = NULL;
		pCdCurve = NULL;
		pCompCd0Curve = NULL;
		pCompKCurve = NULL;
		pCmCurve = NULL;

		if (*aircraft_name_ident != 0)
		{
			if (*cl_curve_ident != 0)
				pClCurve = _CurveRsc.FindCurve (aircraft_name_ident, cl_curve_ident);

			if (*cd_curve_ident != 0)
				pCdCurve = _CurveRsc.FindCurve (aircraft_name_ident, cd_curve_ident);

			if (*compcd0_curve_ident != 0)
				pCompCd0Curve = _CurveRsc.FindCurve (aircraft_name_ident, compcd0_curve_ident);

			if (*compk_curve_ident != 0)
				pCompKCurve = _CurveRsc.FindCurve (aircraft_name_ident, compk_curve_ident);

			if (*cm_curve_ident != 0)
				pCmCurve = _CurveRsc.FindCurve (aircraft_name_ident, cm_curve_ident);

			// set AoaMax, AoaMin

			AoaMax = pClCurve->CurveData->index;
			AoaMin = (pClCurve->CurveData + pClCurve->cPoints - 1)->index;

			if (AoaMin > FPIE) AoaMin -= F2PIE;

		}
	}

	void SetDragPolar (FP cdo, FP l)
	{
		Cdo = cdo;
		k = l;
	}

	void SetSlipstream (PTHRUSTPOINT thrust0, PTHRUSTPOINT thrust1, char percentage)
	{ 
		pSlipThrustPoint[0] = thrust0;
		pSlipThrustPoint[1] = thrust1;
		AmountInSlipstream = percentage;
	}


};
typedef class MainPlane MAINPLANE, *PMAINPLANE;


class Surface
{

public:

	PMODEL pModel;

	SURFACE_TYPE Type;

	SURFACE_DESCRIPTION Desc;

	PCTRL pCtrls;

	PNEWCTRL pNewCtrls;

	FCRD Pos;
	FORI Ori;
	FP MaskAngle;	//CSB 25/11/98	//This is the sideslip angle at which the element
	char MaskArea;								//is totally within the fuselage wake (Local Coords)

	FP Area, Span;

	PTHRUSTPOINT pSlipThrustPoint;
	char AmountInSlipstream;

	PCURVE pClCurve;
	PCURVE pCdCurve;

	FCRD Force;
	FCRD Moment;

	Surface (PMODEL pmodel, SURFACE_TYPE type, SURFACE_DESCRIPTION desc,
				FP area, FP span)	//, FP chord)
	{
		pModel = pmodel;	
		Type = type;
		Desc = desc;
		Area = area;
		Span = span;
		MaskAngle = 0.0;
		MaskArea  = 0;
		pClCurve = NULL;
		pCdCurve = NULL;
		pCtrls = NULL;
		pNewCtrls = NULL;
		pSlipThrustPoint = NULL;

		List.Attach (&pModel->SurfaceList, this);
	}

	~Surface ()
	{
		while (pCtrls != NULL) delete pCtrls;
		while (pNewCtrls != NULL) delete pNewCtrls;
		List.Detach (this);
	}

	LINKEDLIST<Surface> List;

	void SetPosition (FP x, FP y, FP z)
	{
		Pos.x = x;
		Pos.y = y;
		Pos.z = z;
	}
	void SetOrientation (FP x, FP y, FP z)
	{
		FORI DefOri;	// no control deflection				//AMM 29Jun99
		// Order of rotation z - y - x. In local coords.
		DefOri.x.x = FCos (Degs2Rads (z));
		DefOri.x.y = -FSin (Degs2Rads (z));
		DefOri.x.z = 0;

		DefOri.y.x = FSin (Degs2Rads (z));
		DefOri.y.y = FCos (Degs2Rads (z));
		DefOri.y.z = 0;

		DefOri.z.x = 0;
		DefOri.z.y = 0;
		DefOri.z.z = 1;

		RotOriYVec (DefOri, Degs2Rads (y));
		RotOriXVec (DefOri, Degs2Rads (x));

		CopyOri (DefOri, Ori);
	}

	void SetMaskAngle (FP ang, char area)
	{
		MaskAngle = ang;
		MaskArea  = area;
	}
		
	void Process (AirStrucPtr const ControlledAC);

	void SetCurves (char* accl, char* cl, char* accd, char* cd)
//DeadCode CSB 25/02/99						char* accm, char* cm, char* accdm, char* cdm)
	{
		if ((*accl != 0) && (*cl != 0))
			pClCurve = _CurveRsc.FindCurve (accl, cl);
		else
			pClCurve = NULL;

		if ((*accd != 0) && (*cd != 0))
			pCdCurve = _CurveRsc.FindCurve (accd, cd);
		else
			pCdCurve = NULL;

//DeadCode CSB 25/02/99			if ((*accm != 0) && (*cm != 0))
//DeadCode CSB 25/02/99				pCmCurve = _CurveRsc.FindCurve (accm, cm);
//DeadCode CSB 25/02/99			else
//DeadCode CSB 25/02/99				pCmCurve = NULL;
//DeadCode CSB 25/02/99	
//DeadCode CSB 25/02/99			if ((*accdm != 0) && (*cdm != 0))
//DeadCode CSB 25/02/99				pCdMCurve = _CurveRsc.FindCurve (accdm, cdm);
//DeadCode CSB 25/02/99			else
//DeadCode CSB 25/02/99				pCdMCurve = NULL;
	}
	void SetSlipstream (PTHRUSTPOINT thrust, char percentage)
	{ 
		pSlipThrustPoint = thrust;
		AmountInSlipstream = percentage;
	}

};
typedef class Surface SURFACE, *PSURFACE;


class Cylinder	//CSB 05/11/98
{

public:

	PMODEL pModel;

	FCRD Pos;
	FORI Ori;

	FP Length;
	FP DiameterX;
	FP DiameterY;

	FCRD Force;

	Cylinder (PMODEL pmodel, FP length, FP diameterx, FP diametery)
	{
		pModel    = pmodel;	
		Length    = length;
		DiameterX = diameterx;
		DiameterY = diametery;
		NullVec(Pos);

		Ori.x.x = 1;	Ori.x.y = 0;	Ori.x.z = 0;
		Ori.y.x = 0;	Ori.y.y = 1;	Ori.y.z = 0;
		Ori.z.x = 0;	Ori.z.y = 0;	Ori.z.z = 1;

		List.Attach (&pModel->CylinderList, this);
	}

	~Cylinder ()
	{
		List.Detach (this);
	}

	LINKEDLIST<Cylinder> List;

	void SetPosition (FP x, FP y, FP z)
	{
		Pos.x = x;
		Pos.y = y;
		Pos.z = z;
	}

	void SetOrientation (FP x, FP y, FP z)
	{
		FORI DefOri;
		// Order of rotation z - y - x. In local coords.
		DefOri.x.x = FCos (Degs2Rads (z));
		DefOri.x.y = -FSin (Degs2Rads (z));
		DefOri.x.z = 0;

		DefOri.y.x = FSin (Degs2Rads (z));
		DefOri.y.y = FCos (Degs2Rads (z));
		DefOri.y.z = 0;

		DefOri.z.x = 0;
		DefOri.z.y = 0;
		DefOri.z.z = 1;

		RotOriYVec (DefOri, Degs2Rads (y));
		RotOriXVec (DefOri, Degs2Rads (x));

		CopyOri (DefOri, Ori);
	}

	void Process (AirStrucPtr const ControlledAC);

};
typedef class Cylinder CYLINDER, *PCYLINDER;


class ThrustPoint
{

public:

	PMODEL pModel;
	THRUST_TYPE Type;

	FCRD Pos;
	FCRD Vec;

	PENGINE pEngine;

	FCRD Force;
	FCRD Moment;

	ThrustPoint (PMODEL pmodel, THRUST_TYPE type, FP x, FP y, FP z, FP pitch, FP yaw)
	{
		pModel = pmodel;
		Type = type;
		Pos.x = x;
		Pos.y = y;
		Pos.z = z;
		Vec.x = 0;
		Vec.y = 0;
		Vec.z = 1;
		RotVecXSC (Vec, Vec, FSin(Degs2Rads(pitch)), FCos(Degs2Rads(pitch)));
		RotVecYSC (Vec, Vec, FSin(Degs2Rads(yaw)), FCos(Degs2Rads(yaw)));
		List.Attach (&pModel->ThrustList, this);
	}

	~ThrustPoint () { List.Detach (this); }

	LINKEDLIST<ThrustPoint> List;

	void SetEngine (PENGINE pengine) { pEngine = pengine; };
	void Process ();
	
};
typedef class ThrustPoint THRUSTPOINT, *PTHRUSTPOINT;


#endif
