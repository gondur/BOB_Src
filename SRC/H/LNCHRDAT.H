//------------------------------------------------------------------------------
//Filename       lnchrdat.h
//System         
//Author         Paul.   
//Date           Mon 1 Apr 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	LNCHRDAT_Included
#define	LNCHRDAT_Included

#define	DEFAULT_LNCHRDAT 0

struct	LaunchInfo
{
	LnchrType	lnchrtype;										//RJS 12May97
	ULong		muzlvel;	//ms * 10000						//RJS 12Nov99
	UByte		firingdelay;	//between each transient launch
	UByte		burstcount;		//total number of transients per gun
	ShapeNum	theShape;										//RJS 27Jul98
};

static LaunchInfo	launcherdata[] =							//RJS 27May99
{																//RJS 27May99
	{LT_BULLET_RAF, 7470000,  8, 8, BULLET},							//CSB 20Jun00
	{LT_BULLET_LUF, 8110000,  8, 8, BULLET},							//CSB 20Jun00
	{LT_BULLET_REAR,8110000,  4, 8, BULLET},							//CSB 20Jun00
	{LT_CANNON,     5490000,  8, 4, CANNON},							//RJS 17Dec99	//CSB 06/03/00
	{LT_BOMB,0,50,0,BOMB},										//RJS 27May99
	{LT_BOMB500,0,50,0,BOMB},									//RJS 08Dec99
	{LT_BOMBPAIR500,0,50,0,BOMB2},								//RJS 11Apr00
	{LT_BOMB1000,0,50,0,BM1000},								//RJS 11Apr00
	{LT_CONTACT,0,0,0}											//RJS 27May99
};																//RJS 27May99

#endif
