//------------------------------------------------------------------------------
//Filename       time.h
//System         
//Author         R. Hyde 
//Date           Thu 4 Jan 1996
//				 Code now in hardware\dostime&wintime.cpp		//ARM 01Jul96
//Description    
//------------------------------------------------------------------------------
#ifndef	TIME_Included
#define	TIME_Included

#include	"myangles.h"
#define	DEFAULT_TIME 0
enum	Times
{

		SECS100 = 100,							//RDH 20May96
		THIRTYSECS100 = 3000,
		MINS100	=	6000,
		FIVESECS100 = 5*(int)SECS100,							//RDH 20May96

 	SECSPERMIN = 60, 
 	SECSPERHR  = 60 * (int)SECSPERMIN,
 	SECSPERDAY = 24 * (int)SECSPERHR,
	SECSPERWEEK = 7 * (int)SECSPERDAY,
	SECSPERSAGFRAME=20,												  //JIM 03/12/99
 	DAYSPERYEAR = 365,
 	DAYSPERLEAPYEAR = 366,
 	DAYSPER4YEAR = 3 * (int)DAYSPERYEAR + (int)DAYSPERLEAPYEAR,

 	JAN1940 = ((int)SECSPERDAY * (((int)DAYSPER4YEAR * 9 ) + ((int)DAYSPERYEAR*3))),
	JUL1940	= (int)JAN1940 + (int)SECSPERDAY * (31+29+31+30+31+30),
	JUL10th1940 =  (int)JUL1940 + 9 * (int)SECSPERDAY,
	JUL15th1940 =  (int)JUL1940 + 14 * (int)SECSPERDAY,
	JUL20th1940 =  (int)JUL1940 + 19 * (int)SECSPERDAY,
	JUL25th1940 =  (int)JUL1940 + 24 * (int)SECSPERDAY,
	JUL31st1940 =  (int)JUL1940 + 30 * (int)SECSPERDAY,
	AUG1940	= (int)JAN1940 + (int)SECSPERDAY * (31+29+31+30+31+30+31),
	SEP1940	= (int)JAN1940 + (int)SECSPERDAY * (31+29+31+30+31+30+31+31),
	AUG11th1940 =  (int)AUG1940 + 10 * (int)SECSPERDAY,
	AUG12th1940 =  (int)AUG1940 + 11 * (int)SECSPERDAY,
	AUG15th1940 =  (int)AUG1940 + 14 * (int)SECSPERDAY,					//MS 11Nov00
	AUG16th1940 =  (int)AUG1940 + 15 * (int)SECSPERDAY,
	AUG23rd1940 =  (int)AUG1940 + 22 * (int)SECSPERDAY,
	AUG24th1940 =  (int)AUG1940 + 23 * (int)SECSPERDAY,
	AUG26th1940 =  (int)AUG1940 + 25 * (int)SECSPERDAY,
	AUG28th1940 =  (int)AUG1940 + 27 * (int)SECSPERDAY,
	AUG30th1940 =  (int)AUG1940 + 29 * (int)SECSPERDAY,
	SEP2nd1940 =  (int)SEP1940 + 1 * (int)SECSPERDAY,
	SEP4th1940 =  (int)SEP1940 + 3 * (int)SECSPERDAY,
	SEP6th1940 =  (int)SEP1940 + 5 * (int)SECSPERDAY,
	SEP7th1940 =  (int)SEP1940 + 6 * (int)SECSPERDAY,
	SEP10th1940 =  (int)SEP1940 + 9 * (int)SECSPERDAY,
	SEP15th1940 =  (int)SEP1940 + 14 * (int)SECSPERDAY,
 	SEP16th1940 =  (int)SEP1940 + 15 * (int)SECSPERDAY,


//DEADCODE RDH 10/01/00 	JAN1950 = ((int)SECSPERDAY * (((int)DAYSPER4YEAR * 12 ) + (int)DAYSPERYEAR)),
//DEADCODE RDH 10/01/00 	JAN1954 = ((int)SECSPERDAY * (((int)DAYSPER4YEAR * 13 ) + (int)DAYSPERYEAR)),
//DEADCODE RDH 10/01/00 
//DEADCODE RDH 10/01/00 	JUN1950	= (int)JAN1950 + (int)SECSPERDAY * (31+28+31+30+31),
//DEADCODE RDH 10/01/00 	JUN20th1950 =  (int)JUN1950 + 19 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	JUN25th1950 =  (int)JUN1950 + 24 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	JUN27th1950 =  (int)JUN1950 + 26 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	JUN30th1950 =  (int)JUN1950 + 29 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 
//DEADCODE RDH 10/01/00 	JUL1950	= (int)JAN1950 + (int)SECSPERDAY * (31+28+31+30+31+30),
//DEADCODE RDH 10/01/00 	JUL3rd1950 =  (int)JUL1950 + 2 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	JUL8th1950 =  (int)JUL1950 + 7 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 
//DEADCODE RDH 10/01/00 	JUL19th1950 =  (int)JUL1950 + 18 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	JUL20th1950 =  (int)JUL1950 + 19 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 
//DEADCODE RDH 10/01/00 	JUL25th1950 =  (int)JUL1950 + 24 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	JUL27th1950 =  (int)JUL1950 + 26 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	AUG1950	= (int)JAN1950 + (int)SECSPERDAY * (31+28+31+30+31+30+31),
//DEADCODE RDH 10/01/00 	AUG2nd1950 =  (int)AUG1950 + 1 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	AUG10th1950 =  (int)AUG1950 + 9 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	AUG15th1950 =  (int)AUG1950 + 14 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	AUG18th1950 =  (int)AUG1950 + 17 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	AUG19th1950 =  (int)AUG1950 + 18 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	AUG20th1950 =  (int)AUG1950 + 19 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 
//DEADCODE RDH 10/01/00 	SEP1950	= (int)JAN1950 + (int)SECSPERDAY * (31+28+31+30+31+30+31+31),
//DEADCODE RDH 10/01/00 	SEP2nd1950 =  (int)SEP1950 + 1 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	SEP17th1950 =  (int)SEP1950 + 16 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	SEP18th1950 =  (int)SEP1950 + 17 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	SEP20th1950 =  (int)SEP1950 + 19 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	SEP25th1950 =  (int)SEP1950 + 24 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 
//DEADCODE RDH 10/01/00 	OCT1950	= (int)JAN1950 + (int)SECSPERDAY * (31+28+31+30+31+30+31+31+30), //RDH 14/06/99
//DEADCODE RDH 10/01/00 	OCT8th1950 = (int)OCT1950 + 7 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	OCT16th1950 = (int)OCT1950 + 15 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	OCT25th1950 = (int)OCT1950 + 24 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 
//DEADCODE RDH 10/01/00 	NOV1950	= (int)JAN1950 + (int)SECSPERDAY * (31+28+31+30+31+30+31+31+30+31),
//DEADCODE RDH 10/01/00 	NOV2nd1950 = (int)NOV1950 + 1 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	NOV5th1950 = (int)NOV1950 + 4 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	NOV15th1950 = (int)NOV1950 + 14 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	NOV25th1950 = (int)NOV1950 + 24 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 
//DEADCODE RDH 10/01/00 
//DEADCODE RDH 10/01/00 
//DEADCODE RDH 10/01/00 	DEC1950	= (int)JAN1950 + (int)SECSPERDAY * (31+28+31+30+31+30+31+31+30+31+30),
//DEADCODE RDH 10/01/00 	DEC9th1950 = (int)DEC1950 + 8 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	DEC16th1950 = (int)DEC1950 + 15  * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	DEC25th1950 = (int)DEC1950 + 24 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 
//DEADCODE RDH 10/01/00 	JAN1951 =  ((int)SECSPERDAY * (((int)DAYSPER4YEAR * 12 ) + (int)DAYSPERYEAR * 2)),
//DEADCODE RDH 10/01/00 	JAN5th1951 =  (int)JAN1951 + 4 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	FEB1951 =  (int)JAN1951 + ((int)SECSPERDAY * 31),
//DEADCODE RDH 10/01/00 	MAR1951 =  (int)FEB1951 + ((int)SECSPERDAY * 28),
//DEADCODE RDH 10/01/00 	APR1951 =  (int)MAR1951 + ((int)SECSPERDAY * 31),
//DEADCODE RDH 10/01/00 	APR1st1951 = APR1951,
//DEADCODE RDH 10/01/00 	MAY1951 =  (int)APR1951 + ((int)SECSPERDAY * 30),
//DEADCODE RDH 10/01/00 	JUN1951 =  (int)MAY1951 + ((int)SECSPERDAY * 31),
//DEADCODE RDH 10/01/00 	JUL1951 =  (int)JUN1951 + ((int)SECSPERDAY * 30),
//DEADCODE RDH 10/01/00 	MAR5th1951 =  (int)MAR1951 + 4 * (int)SECSPERDAY,
//DEADCODE RDH 10/01/00 	JUN20th1951 =  (int)JUN1951 + 19 * (int)SECSPERDAY,
//DeadCode RDH 17Feb97 	INTERVAL_BETWEEN_TANK_LAUNCHES = SECSPERHR,
//DeadCode RDH 17Feb97 	INTERVAL_BETWEEN_TRUCK_LAUNCHES = SECSPERHR,
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 	MAY1917 =  (SECSPERDAY * ((DAYSPER4YEAR * 4) + 31 + 28 + 31 + 30)),
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		MAY1st1917 =  MAY1917,
//DeadCode RDH 17Feb97 		MAY2nd1917 =  MAY1917 + 1 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY3rd1917 =  MAY1917 + 2 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY4th1917 =  MAY1917 + 3 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY5th1917 =  MAY1917 + 4 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY6th1917 =  MAY1917 + 5 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY7th1917 =  MAY1917 + 6 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY8th1917 =  MAY1917 + 7 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY9th1917 =  MAY1917 + 8 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY10th1917 =  MAY1917 + 9 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY11th1917 =  MAY1917 + 10 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY12th1917 =  MAY1917 + 11 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY13th1917 =  MAY1917 + 12 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY14th1917 =  MAY1917 + 13 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY15th1917 =  MAY1917 + 14 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY16th1917 =  MAY1917 + 15 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY17th1917 =  MAY1917 + 16 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY18th1917 =  MAY1917 + 17 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY19th1917 =  MAY1917 + 18 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY20th1917 =  MAY1917 + 19 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY21st1917 =  MAY1917 + 20 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY22nd1917 =  MAY1917 + 21 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY23rd1917 =  MAY1917 + 22 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY24th1917 =  MAY1917 + 23 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY25th1917 =  MAY1917 + 24 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY26th1917 =  MAY1917 + 25 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY27th1917 =  MAY1917 + 26 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY28th1917 =  MAY1917 + 27 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY29th1917 =  MAY1917 + 28 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY30th1917 =  MAY1917 + 29 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY31st1917 =  MAY1917 + 30 * SECSPERDAY,
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		NOV1917	=	   (SECSPERDAY * ((DAYSPER4YEAR * 4) +
//DeadCode RDH 17Feb97 					31 + 28 + 31 + 30 +
//DeadCode RDH 17Feb97 					31 + 30 + 31 + 31 +
//DeadCode RDH 17Feb97 					30 + 31  )),
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		NOV20th1917 =	NOV1917 + 19 * SECSPERDAY,
//DeadCode RDH 17Feb97 		NOV21st1917 =	NOV1917 + 20 * SECSPERDAY,
//DeadCode RDH 17Feb97 		NOV22nd1917 =	NOV1917 + 21 * SECSPERDAY,
//DeadCode RDH 17Feb97 		FEB1918 =  (SECSPERDAY * ((DAYSPER4YEAR * 4) + DAYSPERYEAR +
//DeadCode RDH 17Feb97 					31)),
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		FEB1st1918 =  FEB1918,
//DeadCode RDH 17Feb97 		FEB2nd1918 =  FEB1918 + 1 * SECSPERDAY,
//DeadCode RDH 17Feb97 		FEB3rd1918 =  FEB1918 + 2 * SECSPERDAY,
//DeadCode RDH 17Feb97 		FEB4th1918 =  FEB1918 + 3 * SECSPERDAY,
//DeadCode RDH 17Feb97 		FEB15th1918 =  FEB1918 + 14 * SECSPERDAY,
//DeadCode RDH 17Feb97 		FEB22nd1918 =  FEB1918 + 21 * SECSPERDAY,
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		MAR1918 =  (SECSPERDAY * ((DAYSPER4YEAR * 4) + DAYSPERYEAR +
//DeadCode RDH 17Feb97 					31+28)),
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		MAR01th1918 =  MAR1918,
//DeadCode RDH 17Feb97 		MAR10th1918 =  MAR1918 + 9 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAR19th1918 =  MAR1918 + 18 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAR20th1918 =  MAR1918 + 19 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAR21st1918 =  MAR1918 + 20 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAR22nd1918 =  MAR1918 + 21 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAR23rd1918 =  MAR1918 + 22 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAR24th1918 =  MAR1918 + 23 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAR25th1918 =  MAR1918 + 24 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAR26th1918 =  MAR1918 + 25 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAR27th1918 =  MAR1918 + 26 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAR28th1918 =  MAR1918 + 27 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAR29th1918 =  MAR1918 + 28 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAR30th1918 =  MAR1918 + 29 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAR31th1918 =  MAR1918 + 30 * SECSPERDAY,
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		APR1918 =  (SECSPERDAY * ((DAYSPER4YEAR * 4) + DAYSPERYEAR +
//DeadCode RDH 17Feb97 					31 + 28 + 31)),
//DeadCode RDH 17Feb97 		MAY1918 =  (SECSPERDAY * ((DAYSPER4YEAR * 4) + DAYSPERYEAR +
//DeadCode RDH 17Feb97 					31 + 28 + 31 + 30)),
//DeadCode RDH 17Feb97 		JUN1918 =  (SECSPERDAY * ((DAYSPER4YEAR * 4) + DAYSPERYEAR +
//DeadCode RDH 17Feb97 					31 + 28 + 31 + 30 + 31)),
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		APR2nd1918 =  APR1918 + 1 * SECSPERDAY,
//DeadCode RDH 17Feb97 		APR4th1918 =  APR1918 + 3 * SECSPERDAY,
//DeadCode RDH 17Feb97 		APR14th1918 =  APR1918 + 13 * SECSPERDAY,
//DeadCode RDH 17Feb97 		APR15th1918 =  APR1918 + 14 * SECSPERDAY,
//DeadCode RDH 17Feb97 		APR20th1918 =  APR1918 + 19 * SECSPERDAY,
//DeadCode RDH 17Feb97 		APR21st1918 =  APR1918 + 20 * SECSPERDAY,
//DeadCode RDH 17Feb97 		APR23rd1918 =  APR1918 + 22 * SECSPERDAY,		//MS 11Jul96
//DeadCode RDH 17Feb97 		APR25th1918 =  APR1918 + 24 * SECSPERDAY,
//DeadCode RDH 17Feb97 		APR30th1918 =  APR1918 + 29 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY7th1918  =  MAY1918 + 6 * SECSPERDAY,		//MS 11Jul96
//DeadCode RDH 17Feb97 		MAY17th1918 =  MAY1918 + 16 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY20th1918 =  MAY1918 + 19 * SECSPERDAY,
//DeadCode RDH 17Feb97 		MAY28th1918 =  MAY1918 + 27 * SECSPERDAY,
//DeadCode RDH 17Feb97 		JUN2nd1918  =  JUN1918 + 1 * SECSPERDAY,
//DeadCode RDH 17Feb97 		JUN12th1918 =  JUN1918 + 11 * SECSPERDAY,
//DeadCode RDH 17Feb97 		JUN24th1918 =  JUN1918 + 23 * SECSPERDAY,
//DeadCode RDH 17Feb97 		JUN25th1918 =  JUN1918 + 24 * SECSPERDAY,
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		SEP1918 =  (SECSPERDAY * ((DAYSPER4YEAR * 4) + DAYSPERYEAR +
//DeadCode RDH 17Feb97 					31 + 28 + 31 + 30 + 31 + 30 + 31 + 31)),
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		SEP3rd1918  =  SEP1918 + 2 * SECSPERDAY,
//DeadCode RDH 17Feb97 		SEP6th1918  =  SEP1918 + 5 * SECSPERDAY,
//DeadCode RDH 17Feb97 		SEP12th1918 =  SEP1918 + 11 * SECSPERDAY,		//MS 11Jul96
//DeadCode RDH 17Feb97 		SEP14th1918 =  SEP1918 + 13 * SECSPERDAY,		//MS 11Jul96
//DeadCode RDH 17Feb97 		SEP15th1918 =  SEP1918 + 14 * SECSPERDAY,
//DeadCode RDH 17Feb97 		SEP20th1918 =  SEP1918 + 19 * SECSPERDAY,		//MS 11Jul96
//DeadCode RDH 17Feb97 		SEP26th1918 =  SEP1918 + 25 * SECSPERDAY,
//DeadCode RDH 17Feb97 		SEP30th1918 =  SEP1918 + 29 * SECSPERDAY,				//MS 15Nov96
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		OCT1918 =  (SECSPERDAY * ((DAYSPER4YEAR * 4) + DAYSPERYEAR +
//DeadCode RDH 17Feb97 					31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30)),
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		NOV1918 =  (SECSPERDAY * ((DAYSPER4YEAR * 4) + DAYSPERYEAR +//MS 17Nov96
//DeadCode RDH 17Feb97 					31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31)),//MS 17Nov96
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		OCT2nd1918 =  OCT1918 + 1 * SECSPERDAY,
//DeadCode RDH 17Feb97 		OCT10th1918 =  OCT1918 + 9 * SECSPERDAY,
//DeadCode RDH 17Feb97 		OCT23rd1918 =  OCT1918 + 22 * SECSPERDAY,
//DeadCode RDH 17Feb97 		OCT27th1918 =  OCT1918 + 26 * SECSPERDAY,
//DeadCode RDH 17Feb97 		OCT28th1918 =  OCT1918 + 27 * SECSPERDAY,
//DeadCode RDH 17Feb97 		OCT30th1918 =  OCT1918 + 29 * SECSPERDAY,
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		OCT31st1918 =  OCT1918 + 31 * SECSPERDAY,
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		NOV1st1918 = NOV1918 + 1 * SECSPERDAY,					//MS 17Nov96
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		Jan1920 =  (SECSPERDAY * ((DAYSPER4YEAR * 4) + DAYSPERYEAR * 3 + 31 + 28 + 31 + 30)),
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97 		MAXEDOUTTIME = Jan1920,
		MIN5		=	5* (int)SECSPERMIN,							  //JIM 19/01/99
		MIN10		= 10 * (int)SECSPERMIN,					//MS 11Jul96
		MIN15		= 15 * (int)SECSPERMIN,					//MS 11Jul96
		MIN20		= 20 * (int)SECSPERMIN,					//MS 11Jul96
		MIN30		= 30 * (int)SECSPERMIN,					//MS 11Jul96
		MIN40		= 40 * (int)SECSPERMIN,
		MIN50		= 50 * (int)SECSPERMIN,					//MS 11Jul96
		HR00		= 0,
		HR01		= 1 * (int)SECSPERHR,
		HR02		= 2 * (int)SECSPERHR,
		HR03		= 3 * (int)SECSPERHR,
		HR04		= 4 * (int)SECSPERHR,
		HR05		= 5 * (int)SECSPERHR,
		HR06		= 6 * (int)SECSPERHR,
		HR07		= 7 * (int)SECSPERHR,
		HR08		= 8 * (int)SECSPERHR,
		HR09		= 9 * (int)SECSPERHR,
		HR10		= 10 *(int) SECSPERHR,
		HR11		= 11 *(int) SECSPERHR,
		HR12		= 12 *(int) SECSPERHR,
		HR13		= 13 *(int) SECSPERHR,
		HR14		= 14 *(int) SECSPERHR,
		HR15		= 15 *(int) SECSPERHR,
		HR16		= 16 *(int) SECSPERHR,
		HR17		= 17 *(int) SECSPERHR,
		HR18		= 18 *(int) SECSPERHR,
		HR19		= 19 *(int) SECSPERHR,
		HR20		= 20 *(int) SECSPERHR,
		HR21		= 21 *(int) SECSPERHR,
		HR22		= 22 *(int) SECSPERHR,
		HR23		= 23 *(int) SECSPERHR,

		HR04MIN30	= 	(int)HR04 + (int)MIN30,							//MS 08Nov96
		HR05MIN40	=	(int)HR05 + (int)MIN40,
		HR08MIN20	=	(int)HR08 + (int)MIN20,
		HR08MIN50	=	(int)HR08 + (int)MIN50,
		HR09MIN50	=	(int)HR09 + (int)MIN50,
		HR09MIN30	=	(int)HR09 + (int)MIN30,							//MS 17Nov96
		HR12MIN10	=	(int)HR12 + (int)MIN10,
		HR12MIN15	=	(int)HR12 + (int)MIN15,
		HR12MIN20	=	(int)HR12 + (int)MIN20,
		HR14MIN20	=	(int)HR14 + (int)MIN20,
		HR14MIN30	=	(int)HR14 + (int)MIN30,
		HR14MIN50	=	(int)HR14 + (int)MIN50,
		HR15MIN20	=	(int)HR15 + (int)MIN20,	
		HR15MIN30	=	(int)HR15 + (int)MIN30,					//MS 11Jul96
		HR16MIN20	=	(int)HR16 + (int)MIN20,
		HR16MIN40	=	(int)HR16 + (int)MIN40,
//DeadCode CSB 15/12/98			SEPTEMBERDAWNTIME =(int) HR06,
//DeadCode CSB 15/12/98			OCTOBERDAWNTIME = (int)HR07,
//DeadCode CSB 15/12/98			OCTOBERDUSKTIME = (int)HR18,
//DeadCode CSB 15/12/98			NOVEMBERDAWNTIME =(int) HR08,
//DeadCode CSB 15/12/98			NOVEMBERDUSKTIME =(int) HR17,
//DeadCode CSB 15/12/98			MARCHDAWNTIME = (int)HR06,
//DeadCode CSB 15/12/98			MARCHDUSKTIME = (int)HR20,
//DeadCode CSB 15/12/98			MAYDAWNTIME = (int)HR05,
//DeadCode CSB 15/12/98			MAYDUSKTIME = (int)HR21,
		CRCEVENING = (int)HR20,
		MIDMORNING = (int)HR10,
		SO_EVENING = (int)HR19,
		STANDARDMORNING = (int)HR10 +(int) MIN30,
		MAYPOSTDAWNTIME = (int)HR05 +(int) MIN15,
		MORNINGPERIODSTART = (int)HR06 +(int) MIN30,
		MIDDAYPERIODSTART = HR11,
		AFTERNOONPERIODSTART = (int)HR15 +(int) MIN30,
		AFTERNOONPERIODEND = (int)HR20,
		TIME_TAKEOFF_ROUNDING	=	MIN5,
		TIME_TAKEOFF_FLIGHT		=	14,
		

	};


//DeadCode DAW 09Aug96 SLong const		MIN10		= 10 * SECSPERMIN;					//MS 11Jul96
//DeadCode DAW 09Aug96 SLong const		MIN20		= 20 * SECSPERMIN;					//MS 11Jul96
//DeadCode DAW 09Aug96 SLong const		MIN30		= 30 * SECSPERMIN;					//MS 11Jul96
//DeadCode DAW 09Aug96 SLong const		MIN40		= 40 * SECSPERMIN;
//DeadCode DAW 09Aug96 SLong const		MIN50		= 50 * SECSPERMIN;					//MS 11Jul96
//DeadCode DAW 09Aug96 SLong const		HR00		= 0;
//DeadCode DAW 09Aug96 SLong const		HR01		= 1 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR02		= 2 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR03		= 3 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR04		= 4 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR05		= 5 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR06		= 6 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR07		= 7 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR08		= 8 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR09		= 9 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR10		= 10 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR11		= 11 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR12		= 12 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR13		= 13 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR14		= 14 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR15		= 15 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR16		= 16 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR17		= 17 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR18		= 18 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR19		= 19 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR20		= 20 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR21		= 21 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR22		= 22 * SECSPERHR;
//DeadCode DAW 09Aug96 SLong const		HR23		= 23 * SECSPERHR;

//DeadCode DAW 09Aug96 SLong const		HR05MIN40	=	HR05 + MIN40;
//DeadCode DAW 09Aug96 SLong const		HR08MIN50	=	HR08 + MIN50;
//DeadCode DAW 09Aug96 SLong const		HR12MIN10	=	HR12 + MIN10;
//DeadCode DAW 09Aug96 SLong const		HR14MIN30	=	HR14 + MIN30;
//DeadCode DAW 09Aug96 SLong const		HR15MIN30	=	HR15 + MIN30;					//MS 11Jul96
//DeadCode DAW 09Aug96 SLong const		HR16MIN40	=	HR16 + MIN40;

///////////////////////////////////////////////////////////////////////
//DeadCode AMM 24Nov99 class	TimerCode												//PD 15Mar96
//DeadCode AMM 24Nov99 {
//DeadCode AMM 24Nov99 volatile ULong	last_tus;		//previous time in time units
//DeadCode AMM 24Nov99 volatile ULong	tus;		 	//Current time in time units
//DeadCode AMM 24Nov99 		int		accelrate;
//DeadCode AMM 24Nov99 		int		csecs;											//ARM 01Jul96
//DeadCode AMM 24Nov99 		int		accelaccum;
//DeadCode AMM 24Nov99 	public:
//DeadCode AMM 24Nov99 		SWord	nextmsgframetime:15;	//tracks behind frametime
//DeadCode AMM 24Nov99 		SWord	msgframeoverflow:1;
//DeadCode AMM 24Nov99 
//DeadCode AMM 24Nov99 //DeadCode ARM 25Jul96 		Bool	wFixedTimeFrame;									//ARM 11Jul96
//DeadCode AMM 24Nov99 
//DeadCode AMM 24Nov99 	friend	class	Miles;
//DeadCode AMM 24Nov99 
//DeadCode AMM 24Nov99 	public:
//DeadCode AMM 24Nov99 		int		msgcounttime;
//DeadCode AMM 24Nov99 
//DeadCode AMM 24Nov99 //	int		FIXEDFRAMETIME;
//DeadCode AMM 24Nov99 
//DeadCode AMM 24Nov99 	enum	{
//DeadCode AMM 24Nov99 			FREQ	=	100,
//DeadCode AMM 24Nov99 			FRAMEMIN	=	3,									//PD 29Aug96 - was 3
//DeadCode AMM 24Nov99 //DEADCODE AMM 24/11/99 			FIXEDFRAMETIME	= 2,					//rdh 8/5/98			//PD 29Aug96 - was 3
//DeadCode AMM 24Nov99 			FIXEDFRAMETIME	= 4,		//AMM 24/11/99
//DeadCode AMM 24Nov99 			COLLIDEFRAMETIME = 12,								//PD 10Sep96
//DeadCode AMM 24Nov99 			FRAMENORM	=	11,
//DeadCode AMM 24Nov99 			FRAMEMAX	=	20,
//DeadCode AMM 24Nov99 			FRAMESILLY	=	100
//DeadCode AMM 24Nov99 			};													//JIM 02Apr96
//DeadCode AMM 24Nov99 
//DeadCode AMM 24Nov99 		Bool	paused;
//DeadCode AMM 24Nov99 		Bool	accel;
//DeadCode AMM 24Nov99 //		UWord	frametime;			//This is 0 when paused
//DeadCode AMM 24Nov99 //		UWord	realframetime;		//This is never 0 even when paused
//DeadCode AMM 24Nov99 		ULong	framenum;	//at 20 fps this can count to 5 years
//DeadCode AMM 24Nov99 //DeadCode RJS 23Mar98 		ANGLES	sunhdg,sunpitch,sunrot;
//DeadCode AMM 24Nov99 //DeadCode RJS 23Mar98 		Coords3D sunpos;
//DeadCode AMM 24Nov99 		int		realtime;
//DeadCode AMM 24Nov99 		SWord	Quit3DTimer;									//RJS 22Oct96
//DeadCode AMM 24Nov99 
//DeadCode AMM 24Nov99 		CON		TimerCode()
//DeadCode AMM 24Nov99 			{
//DeadCode AMM 24Nov99 				framenum=0;accelaccum=0;nextmsgframetime=0;tus=0;last_tus=0;
//DeadCode AMM 24Nov99 				paused=accel=FALSE;accelrate=60;
//DeadCode AMM 24Nov99 //				sunhdg=ANGLES_180Deg;sunpitch=ANGLES_45Deg;
//DeadCode AMM 24Nov99 				realtime=0;
//DeadCode AMM 24Nov99 			}
//DeadCode AMM 24Nov99 
//DeadCode AMM 24Nov99 
//DeadCode AMM 24Nov99 		volatile UWord	TestLoopTime();
//DeadCode AMM 24Nov99 		Bool	TestMsgTime();
//DeadCode AMM 24Nov99 		Bool	GetLoopTime();
//DeadCode AMM 24Nov99 		void	PauseToggle();
//DeadCode AMM 24Nov99 		void	PauseToggle(Bool s);
//DeadCode AMM 24Nov99 		void	GotoAutoAndAccel();
//DeadCode AMM 24Nov99 		void	AccelToggle();
//DeadCode AMM 24Nov99 		void	AccelToggle(Bool s);
//DeadCode AMM 24Nov99 		Bool	AccelSkip();
//DeadCode AMM 24Nov99 		int		TimeSinceLastMove();
//DeadCode AMM 24Nov99 
//DeadCode AMM 24Nov99 		ULong	GetTime () { return tus; }						//ARM 08Nov96
//DeadCode AMM 24Nov99 
//DeadCode AMM 24Nov99 };
//DeadCode AMM 24Nov99 
//DeadCode AMM 24Nov99 //#define	FRAMETIME frametime
//DeadCode AMM 24Nov99 #define	FRAMETIME FIXEDFRAMETIME
//DeadCode AMM 24Nov99 
//DeadCode AMM 24Nov99 struct	DummyTime
//DeadCode AMM 24Nov99 {
//DeadCode AMM 24Nov99 	enum	{
//DeadCode AMM 24Nov99 //			FREQ	=	100,
//DeadCode AMM 24Nov99 //			FRAMEMIN	=	3,									//PD 29Aug96 - was 3
//DeadCode AMM 24Nov99 			FIXEDFRAMETIME	= 4,					//rdh 8/5/98			//PD 29Aug96 - was 3
//DeadCode AMM 24Nov99 			COLLIDEFRAMETIME = 12,								//PD 10Sep96
//DeadCode AMM 24Nov99 //			FRAMENORM	=	11,
//DeadCode AMM 24Nov99 //			FRAMEMAX	=	20,
//DeadCode AMM 24Nov99 //			FRAMESILLY	=	100
//DeadCode AMM 24Nov99 			};													//JIM 02Apr96
//DeadCode AMM 24Nov99 
//DeadCode AMM 24Nov99 };
//DeadCode AMM 24Nov99 extern 	DummyTime	Timer_Code;
//DEADCODE DAW 28/03/99 extern	class TimerCode Timer_Code;

// I have done it like this because of the amount of references to Timer_Code.FRAMETIME,
// if somebody wants to change them all and just have a const value without the TimerCode
// class, then fine. //AMM 25/11/99

class TimerCode
{
public:
	enum
	{
		FRAMETIME = 4
	};
};

extern TimerCode Timer_Code;

#endif
