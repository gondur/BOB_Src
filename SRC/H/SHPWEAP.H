//------------------------------------------------------------------------------
//Filename       shpweap.h
//System         
//Author         Robert Slater
//Date           Wed 16 Apr 1997
//Description    Data relating weapon launcher shapes to aircraft shapes
//
//
//				Weight 	is in 0.01 kg
//				Drag	is in Newtons
//
//		Tip-Tanks are 100lb each
//		
//------------------------------------------------------------------------------
#ifndef	SHPWEAP_Included
#define	SHPWEAP_Included

#define	DEFAULT_SHPWEAP 0

#define MaxWeapTypes	8

typedef struct	weaplist
{
	LnchrType	lnchr;
	UWord		StationShape[2];			// Left & Right		//RJS 17May99
	SLong		Weight;											//RJS 24Apr98
	SLong		Drag;											//RJS 24Apr98
}
WeapListType, *WeapListTypeP;

typedef struct	shptoweaptype
{
	ShapeNum		LchShape;
	WeapListType	LchList[MaxWeapTypes];	
}
ShpToWeapType, *ShpToWeapTypeP;


static ShpToWeapType	ShpToWeap[] =
{
	{SPIT,
	{
	{LT_BULLET_RAF, {{0}, {0}},	1000,	0	},	
	{LT_CONTACT,    {{0}, {0}},	0,		0	}
	}
	},

	{HURR,
	{
	{LT_BULLET_RAF, {{0}, {0}},	1000,	0	},	
	{LT_CONTACT,    {{0}, {0}},	0,		0	}
	}
	},

	{ME109,
	{
	{LT_BULLET_LUF,	{{0}, {0}},	1300,	0	},	
	{LT_CANNON,  	{{0}, {0}},	13500,	0	},	
	{LT_CONTACT,    {{0}, {0}}, 0,		0	}
	}
	},

	{ME110,
	{
	{LT_BULLET_LUF,	{{0}, {0}},			1300,		0	},	
	{LT_CANNON,	    {{0}, {0}},			13500,		0	},	
	{LT_BOMB,	{{LBM110}, {LBM110}},	22679851,	509	},
	{LT_CONTACT,	{{0}, {0}},			0,			0	}
	}
	},

	{JU87,
	{
	{LT_BULLET_LUF,	{{0}, {0}},			1300,		0	},	
	{LT_BOMB,		{{LBMJ87}, {LBMJ87}},	45359702,	905	},	
	{LT_BOMB1000,	{{LBMJ87}, {LBMJ87}},	45359702,	905	},	
	{LT_CONTACT,	{{0}, {0}},			0,			0	}
	}
	},

	{CJU87,
	{
	{LT_BULLET_LUF,	{{0}, {0}},			1300,		0	},	
	{LT_BOMB,		{{LBMJ87}, {LBMJ87}},	45359702,	905	},	
	{LT_BOMB1000,	{{LBMJ87}, {LBMJ87}},	45359702,	905	},	
	{LT_CONTACT,	{{0}, {0}},			0,			0	}
	}
	},

	{JU88,
	{
	{LT_BULLET_REAR,{{0}, {0}},			1300,		0	},	
	{LT_BOMB1000,	{{LBMJ88}, {LBMJ88}},	0,	0	},	
	{LT_CONTACT,{{0}, {0}},				0,	0	}	
	}
	},

	{HE11,
	{
	{LT_BULLET_REAR,{{0}, {0}},			1300,		0	},	
	{LT_BOMB,	{{LBMH11}, {LBMH11}},	0,	0	},	
	{LT_CONTACT,	{{0}, {0}},			0,	0	}
	}
	},

	{DO17,
	{
	{LT_BULLET_REAR,{{0}, {0}},			1300,		0	},	
	{LT_BOMB,	{{LBMDO}, {LBMDO}},	0,	0	},	
	{LT_CONTACT,{{0}, {0}},			0,	0	}
	}
	},

	{(ShapeNum)0,
	{{LT_FUEL, 	{{0},{0}},0,0},									//RJS 15Dec99
	 {LT_ROCKET,{{0},{0}},0,0},									//RJS 15Dec99
	 {LT_NAPALM,{{0},{0}},0,0},									//RJS 15Dec99
	 {LT_BOMB,	{{0},{0}},0,0},									//RJS 15Dec99
	 {LT_BULLET,{{0},{0}},0,0},									//RJS 15Dec99
	 {LT_CONTACT,{{0},{0}},0,	0}}},							//RJS 15Dec99

};


#endif
