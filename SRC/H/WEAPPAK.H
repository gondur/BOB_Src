//------------------------------------------------------------------------------
//Filename       weappak.h
//System         
//Author         Robert Slater
//Date           Wed 8 Apr 1998
//Description    
//
//	F86:
//			300 rounds per gun, 3 guns on each side of nose
//------------------------------------------------------------------------------
#ifndef	WEAPPAK_Included
#define	WEAPPAK_Included

#define	DEFAULT_WEAPPAK 0

#define	MaxPackNo	10


typedef struct	lchinfo
{
	LnchrType	lnchrtype;
	SLong		ammocount;
}
LchrInfo, *LchrInfoP;

struct	lchpak;
typedef struct	lchpak
{
	LchrInfo	stationlaunchers[4];
	int			WeapSetName;
	int			StringResources[4][2];
	int			TotalDrag;
}
LchrPak, *LchrPakP;

typedef struct	weappak
{
	ShapeNum	shape;
	LchrPak		weappack[MaxPackNo];
}
WeapPakType, *WeapPakTypeP;

	
#ifndef	MAKE_WEAPPACKS	
extern	WeapPakType	ShpToWeapPak[];
#else
WeapPakType	ShpToWeapPak[] =
{
	{SPIT,	
		{

			{	
				{{LT_BULLET_RAF, 1400},	{LT_CONTACT, 0},	{LT_CONTACT, 0},	{LT_CONTACT, 0}	},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{	
				{{LT_BULLET_RAF, 1400},	{LT_CONTACT, 0},	{LT_CONTACT, 0},	{LT_CONTACT, 0}	},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}}
		}
	},

	{HURR,	
		{
			{	
				{{LT_BULLET_RAF, 1400},	{LT_CONTACT, 0},	{LT_CONTACT, 0},	{LT_CONTACT, 0}	},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{	
				{{LT_BULLET_RAF, 1400},	{LT_CONTACT, 0},	{LT_CONTACT, 0},	{LT_CONTACT, 0}	},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}}
		}
	},

	{ME109,
		{
			{	
				{{LT_CANNON, 60}, {LT_BULLET_LUF, 2000},	{LT_CONTACT, 0},	{LT_CONTACT, 0}	},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{	
				{{LT_CANNON, 60}, {LT_BULLET_LUF, 2000},	{LT_CONTACT, 0},	{LT_CONTACT, 0}	},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}}
		}
	},

	{ME110,														//MS 26Jan00
		{
			{	
				{{LT_LUF_REARTOP, 750},  {LT_BULLET_LUF, 4000},	{LT_CANNON, 360},	{LT_BOMB500, 2} },
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				1018	
			},
			{	
				{{LT_LUF_REARTOP, 750},  {LT_BULLET_LUF, 4000},	{LT_CANNON, 360},	{LT_CONTACT, 0}	},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}}
		}
	},

	{JU87,														//MS 26Jan00
		{
			{	
				{{LT_LUF_REARTOP, 900},  {LT_BULLET_LUF, 500},	{LT_BOMB1000, 1},	{LT_CONTACT, 0}	},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				905	
			},
			{	
				{{LT_LUF_REARTOP, 900},  {LT_BULLET_LUF, 500},	{LT_CONTACT, 0},	{LT_CONTACT, 0}	},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				905	
			},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}}
		}
	},

	{CJU87,														//MS 26Jan00
		{
			{	
				{{LT_LUF_REARTOP, 900},  {LT_BULLET_LUF, 500},	{LT_BOMB1000, 1},	{LT_CONTACT, 0}	},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				905	
			},
			{	
				{{LT_LUF_REARTOP, 900},  {LT_BULLET_LUF, 500},	{LT_CONTACT, 0},	{LT_CONTACT, 0}	},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				905	
			},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}}
		}
	},


	{JU88,														//MS 28Jan00
		{
			{	
				{{LT_LUF_NOSE, 900},{LT_LUF_REARTOP, 900},{LT_LUF_REARBOT, 900},{LT_BOMB1000, 4}},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{	
				{{LT_LUF_NOSE, 900},{LT_LUF_REARTOP, 900},{LT_LUF_REARBOT, 900},{LT_CONTACT, 0}},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}}
		}
	},

	{HE11,														//MS 28Jan00
		{
			{	
				{{LT_LUF_NOSE, 900},{LT_LUF_REARTOP, 900},{LT_LUF_REARBOT, 900},{LT_BOMBPAIR500, 4}},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{	
				{{LT_LUF_NOSE, 900},{LT_LUF_REARTOP, 900},{LT_LUF_REARBOT, 900},{LT_CONTACT, 0}},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}}
		}
	},

	{DO17,														//MS 28Jan00
		{
			{	
				{{LT_LUF_NOSE, 900},{LT_LUF_REARTOP, 900},{LT_LUF_REARBOT, 900},{LT_BOMB500, 2}},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{	
				{{LT_LUF_NOSE, 900},{LT_LUF_REARTOP, 900},{LT_LUF_REARBOT, 900},{LT_CONTACT, 0}},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}}
		}
	},

	{DEF,														//RJS 11Apr00
		{
			{	
				{{LT_RAF_TURRET, 600},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{	
				{{LT_RAF_TURRET, 600},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}}
		}
	},

	{BRISTO,													//RJS 11Apr00
		{
			{	
				{{LT_RAF_TURRET, 350},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{	
				{{LT_RAF_TURRET, 350},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}},
				IDS_WEAPONS,
				{	{IDS_NONE},	{IDS_NONE},	{IDS_NONE},	{IDS_UNITSG}	},
				0	
			},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}},
			{{{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0},{LT_CONTACT,0}}}
		}
	},

	{(ShapeNum)0}
};
#endif


#endif
