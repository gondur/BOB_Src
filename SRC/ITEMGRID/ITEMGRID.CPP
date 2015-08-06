/*
	 Battle of Britain
	 Copyright (C) 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at bob@rowansoftware.com a
better place to ask is http://www.simhq.com/ or even :-
http://www.simhq.com/cgi-bin/boards/cgi-bin/forumdisplay.cgi?action=topics&forum=Battle+of+Britain&number=40&DaysPrune=20&LastLogin=
*/

// ItemGrid.cpp : Defines the entry point for the console application.
//

#include "dosdefs.h"
#include "myerror.h"
#include "fileman.h"
#include "uniqueid.h"
#include "bfnumber.h"
#include "Persons2.h"
#include "mymath.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "grid.h"
#include "replay.h"

Replay _Replay;
CON Replay::Replay(){}
CON Replay::~Replay(){}

int fakei = 0;
int & __cdecl Persons2::GetLoc(int) { INT3; return fakei; }
void MathLib::high_sin_cos(class ANGLES,short &,short &) { INT3; }
void MathLib::HighIntercept(long,long,long,long &,short &,short &) { INT3; }
void MathLib::Intercept(long,long,long,long &,short &,short &) { INT3; }

Error::Error(void) {}
Error::~Error(void) {}
void fileblock::makefileblock(enum FileNum,void (__cdecl*)(void * &,unsigned long &),unsigned long,unsigned long,bool) {}
void GlobRefExpr::Save(struct _iobuf *,char *,int,enum EnumListNames) {}
ItemBasePtr		WorldStuff::pItem[PITEMTABLESIZE];
class Error & __cdecl Error::SayAndQuit(char const *,...) { return *this; }
class Error & __cdecl Error::Say(char *,...) { return *this; }
class Error &  Error::ExitMode(void) { return *this; }
class Error  _Error;
unsigned long fake = 0;
unsigned long &  GR_TakeOffTime = fake;
void __cdecl SendInitPacket(void) {}
//struct EventLog *  Persons2::TruckLog;
//struct EventLog *  Persons2::TargLog;
//struct EventLog *  Persons2::PlayerLog;
enum FileNum   Persons2::FindNextBf(enum Persons2::BattlefieldType &) {return FIL_NULL;}
fileblock::~fileblock(void) {}
void  GlobRefExpr::Save(class BOStream &,char *,int,enum EnumListNames) {}
void  RndExpr::Save(struct _iobuf *,char *,int,enum EnumListNames) {}
void  RndExpr::Save(class BOStream &,char *,int,enum EnumListNames) {}
void  SelExpr::Save(struct _iobuf *,char *,int,enum EnumListNames) {}
void  SelExpr::Save(class BOStream &,char *,int,enum EnumListNames) {}
void  ListExpr::Save(struct _iobuf *,char *,int,enum EnumListNames) {}
void  ListExpr::Save(class BOStream &,char *,int,enum EnumListNames) {}
void  ListFormExpr::Save(struct _iobuf *,char *,int,enum EnumListNames) {}
void  ListFormExpr::Save(class BOStream &,char *,int,enum EnumListNames) {}
void  UIDExpr::Save(struct _iobuf *,char *,int,enum EnumListNames) {}
void  UIDExpr::Save(class BOStream &,char *,int,enum EnumListNames) {}
void  RotExpr::Save(struct _iobuf *,char *,int,enum EnumListNames) {}
void  RotExpr::Save(class BOStream &,char *,int,enum EnumListNames) {}
void  IcptExpr::Save(struct _iobuf *,char *,int,enum EnumListNames) {}
void  IcptExpr::Save(class BOStream &,char *,int,enum EnumListNames) {}
void  WorldExpr::Save(struct _iobuf *,char *,int,enum EnumListNames) {}
void  WorldExpr::Save(class BOStream &,char *,int,enum EnumListNames) {}
void  XyzExpr::Save(struct _iobuf *,char *,int,enum EnumListNames) {}
void  XyzExpr::Save(class BOStream &,char *,int,enum EnumListNames) {}
void __cdecl ItemBase::operator delete(void *) {}								//
class MathLib  Math_Lib;
enum RndVal   MathLib::rnd(void) { return (RndVal)0; }


void  Persons4::FinishSetPiece(void) {}
void  Persons4::EndSubPiece(void) {}
void  Persons4::InitSubPiece(void) {}
void  Persons4::InitGamePiece(void) {}
void  Persons4::AddRoute(enum UniqueID) {}
enum Bool   Persons4::anyoutstanding(void) { return FALSE; }
void  Persons4::used_globref(int) {}
void  Persons4::make_events(struct info_event * &,class ItemBase *) {}
enum Bool   Persons4::make_agname(char *,int,struct info_airgrp &) { return FALSE; }
enum Bool   Persons4::make_eventname(char *,int,struct info_event &) { return FALSE; }
void  Persons4::make_string(char *,int,enum TokenCode) {}
void  Persons4::make_setval(struct EventVar &) {}
enum UniqueID   Persons4::make_waypoint(struct info_waypoint &) { return UID_NULL; }
void  Persons4::make_gndgrp(struct info_grndgrp &) {}
void  Persons4::make_airgrp(struct info_airgrp &) {}
int  Persons4::make_itemgroupcount(struct EventVal &) { return 32767; }

struct lowresItem
{
	int x, y, uid;
	inline void set( int worldx, int worldy, int uid )
	{
		this->uid = uid;
		x = worldx>>Grid_Base::WORLDSPACEMOD;
		y = worldy>>Grid_Base::WORLDSPACEMOD;
		x+=64;
		y+=64;
	}
	inline int distSq( int toX, int toY ) { return ((x-toX)*(x-toX)) + ((y-toY)*(y-toY)); }
};

int itemListSize = 1000;
int itemListPos = 0;
lowresItem *itemList; 
Grid_Byte radarMap;
int numLowLevel = 0;
int numHighLevel = 0;

void  Persons4::make_itemS(info_itemS &I,bool enabled) 
{
	int uid_v;

	if ((uid_v=I.uid.Evaluate())!=ENABLE_COMPLEX_VAL)
	{
		UniqueIDBand band;
		band = getbandfromUID( (UniqueID) uid_v );

		switch (band)
		{
		case CityBAND:
		case TownBAND:
		case NavigationBAND: 
		case	LUF_FighterLF2BAND:		
		case	LUF_FighterLF3BAND:		
		case	LUF_BomberLF2BAND:		
		case	LUF_BomberLF3BAND:		
			if ( itemListPos == itemListSize )
			{
				printf( "error - run out of space for items, please recompile with a bigger value for itemListSize\n" );
			} else {
				I.position.EvalW(I.World);
				itemList[itemListPos++].set( I.World.X, I.World.Z, uid_v );
			}
		}
		if ( band == CLRadarBAND )
		{ // low level radar
			numLowLevel++;
			I.position.EvalW(I.World);
			radarMap.set( (I.World.X>>Grid_Base::WORLDSPACEMOD)+64,(I.World.Z>>Grid_Base::WORLDSPACEMOD)+64, uid_v - CLRadarBAND + 1);
		}
		if ( band == CHRadarBAND )
		{ // high level radar
			numHighLevel++;
			I.position.EvalW(I.World);
			radarMap.set( (I.World.X>>Grid_Base::WORLDSPACEMOD)+64,(I.World.Z>>Grid_Base::WORLDSPACEMOD)+64, uid_v - CHRadarBAND + 31 );
		}
	}

}

class Persons5: public Persons4
{
public:
	void processData( char* data )
	{
		while (*(data++));
		LoadSubPiece( NULL, data, 0 );
	}
};

int main(int argc, char* argv[])
{
	// load in the file.
	FILE *fp;
//	if ( (fp=fopen( "c:\\bob\\game\\bfields\\MAINMIG.BF", "rb" )) == NULL ) 
//	{
//		printf( "Unable to load bfields\\MAINMIG.BF\n" );
//		return -1; // it hasn't worked 4 some reason...
//	}

	char* fname = "..\\game\\bfields\\MAINWLD.BF";
	char outDir[256] = "c:\\tmp";
	int outSize=6;
	switch (argc)
	{
		case 3:
			strcpy(outDir,argv[2]);
			{ // check 4 trailing \ and remove
				for ( int i=0; outDir[i+1] !=0; i++ )
				{ /*search*/ }
				if ( outDir[i] == '\\' )
					outDir[i--] = 0;
				outSize = i+1;
			}
		case 2:
			fname = argv[1];
		case 1:		
			break;
		default:
			printf( "wrong number of arguments, possible args [inputfile] [outputdir], defaults are present\n");
			return-1;
			break;
	}

	if ( (fp=fopen( fname, "rb" )) == NULL ) 
	{
		printf( "Unable to load %s\n", fname );
		return -1; // it hasn't worked 4 some reason...
	}

	// get file size
	fseek(fp, 0, SEEK_END );
	int fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET );

	// read in entire file
	char *theData = new char[ fsize ];
	fread( theData, 1, fsize, fp );
	fclose( fp );

	itemList = new lowresItem[itemListSize];

	strcpy(&outDir[outSize],"\\sea.grd");
	radarMap.load( outDir );
	
	Persons5 persons;
	persons.processData( theData );
	delete []theData;

	strcpy(&outDir[outSize],"\\radar.grd");
	printf( "found %i lowlevel and %i highlevel radar stations\n"
			"Saving them on grid as %s\n", numLowLevel, numHighLevel, outDir );
	radarMap.save( outDir );

	
	printf( "creating nearest UID map for radiochatter from %i named UID's\n", itemListPos );
	if ( itemListPos == 0 )
	{
		printf( "Error: nothing to work from\n" );
		return -1;
	}

//	printf( "Calculating closest: " );
	Grid_Word theMap; //words should have a great enough difference to hold all UID's
	for ( int x = 0; x<640; x++ )
	{
		for ( int y = 0; y<640; y++ )
		{
			int closest = 0;
			int closeD = itemList[0].distSq( x, y );
			int t;
			for ( int i=0;i<itemListPos; i++ )
			{
				if ( (t=itemList[i].distSq( x, y )) < closeD )
				{
					closeD = t;
					closest = i;
				}
			}
			// found closest - now set.
			theMap.set( x, y, itemList[closest].uid );
		}
		if ( x%16 == 15 )
			printf( "." );
	}

	strcpy(&outDir[outSize],"\\closest.grd");

	printf( "\nSaving %s...\n", outDir );

	theMap.save( outDir );

	return 0;
}

