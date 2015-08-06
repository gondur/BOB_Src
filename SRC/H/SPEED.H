//------------------------------------------------------------------------------
//Filename       speed.h
//System         
//Author         R. Hyde 
//Date           Wed 19 Jun 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	SPEED_Included
#define	SPEED_Included

#define	DEFAULT_SPEED 0



//speeds in um/cs units //CSB 09/11/99
enum	speeds	{												//JIM 18Dec96 //CSB 08/11/99
				MPH00	=	0,
				MPHHALF	=	2235,
				MPH01	=	VEL_1MPH,
				MPH02	=	VEL_1MPH*2,
				MPH05	=	VEL_1MPH*5,
				MPH10	=	VEL_10MPH,
				MPH15	=	MPH10+MPH05,
				MPH30	=	VEL_10MPH*3,	 
				MPH40	=	VEL_10MPH*4,	 
				MPH45	=	MPH40+MPH05,	 
				MPH50	=	VEL_10MPH*5,	 
				MPH55	=	MPH50+MPH05,
				MPH70	=	VEL_10MPH*7,
				MPH80	=	VEL_10MPH*8,
				MPH100	=	VEL_100MPH,
				MPH140	= 	VEL_100MPH+MPH40,
				MPH200	= 	VEL_100MPH*2,
				MPH250	= 	MPH200+MPH50,
				MPH400	=	VEL_100MPH*4,
				MPH450	=	MPH400+MPH50,

				WINDSTEPSIZE = MPH05,
				MAXWINDSPEED = MPH15,
				BESTCLIMBSPEED = 850000,
				TAKEOFFSPEED = MPH80,
				SPEEDOFBULLET = 8110000, 

				CORNERSPEED = MPH100,
				SUSTAINEDTURNSPEED = MPH100,
				MINIMUMCOMBATSPEED = MPH100
				};			


#endif
