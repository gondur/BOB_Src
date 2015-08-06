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

////////////////////////////////////////////////////////////////////////
//
// Source File:	Grid.cpp
//
// Original Author:	JON
// Documented Date:	2000
//
// History:
//		
//		
// Description:	
//		
////////////////////////////////////////////////////////////////////////		
// Stuff 4 holding grid info...
// Jon
#ifdef STAND_ALONE
#undef new
void* __cdecl operator new(unsigned int nSize,const char* FileName, int nLine)
{ return operator new (nSize);}
void  __cdecl operator delete(void* v,char const *,int)	
{ operator delete(v);}
#ifdef DEBUG_NEW
#define new DEBUG_NEW
#endif
#endif
#include "dosdefs.h"
#include "mathasm.h"
#include "grid.h"

#include <stdio.h>

// simple conversions to remember
// x>>6 == x/64, x&63 == x%64
// X>>3 == X/8, x&7 == x%8


//////////////////////////////////////////////////////////////////////////
//	Grid_Base functions													//
//////////////////////////////////////////////////////////////////////////
#undef new

inline void* Grid_Base::operator new( size_t, void* inplaceaddress )
{
	return inplaceaddress;
}

void Grid_Base::makeGridAt( void* &dataarea, ULong& datasize ) // the second parameter is ignored...
{
	makeGridAt( dataarea );
}

void Grid_Base::makeGridAt( void* dataarea )
{
	long *type = (long*) dataarea;
	switch (*type)
	{
	case TYPE_BIT:
		new (dataarea) Grid_Bit( 0 );
		break;
	case TYPE_BYTE:
		new (dataarea) Grid_Byte( 0 );
		break; 
	case TYPE_WORD:
		new (dataarea) Grid_Word( 0 );
		break;
	case TYPE_LONG:
		new (dataarea) Grid_Long( 0 );
		break;
	default:
		// the memory area is not a grid...
		break;
	}
}
#ifdef	DEBUG_NEW
	#define	new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//	Grid_Bit functions													//
//////////////////////////////////////////////////////////////////////////
Grid_Bit::Grid_Bit()
{
	long *t = &header[0][0]; // the start of header
	// basic constructor - set all values to 0 and all headers to run consecutivley up..
	for ( int i = 0; i< 10*10; i++ )
		*t++ = i;
	for ( i = 0; i < (10*10*8/4); i++ ) // wipe 
		*t++ = 0;
}

bool Grid_Bit::compareBlock(long a, long b)
{
	if ( a==b )
		return true;
	long *t1 = (long*)&data[a][0][0]; // the start of the data
	long *t2 = (long*)&data[b][0][0];
	long *e = t1+(64*8/4);
	while ( t1 < e )
		if ( *t1++ != *t2++ )
			return false;

	return true;
}

void Grid_Bit::set( int x, int y, bool v )
{
	// dead simple method, compression done at save time
	// get the byte that holds the bit value we are interested in...
	char *row = &data[ header[x>>6][y>>6] ][x&63][0]; 
	if ( v )
		BITSET( row, y&63 );
	else 
		BITRESET( row, y&63 );
}

long Grid_Bit::get( int x, int y )
{
	// get the byte that holds the bit value we are interested in...
	char *row = &data[ header[x>>6][y>>6] ][x&63][0]; 
	return (long)BITTEST( row, y&63 );
}

bool Grid_Bit::save( char *filename )
{
	FILE* fp;
	if((fp=fopen(filename,"wb"))==NULL){
		return false; // it hasn't worked 4 some reason...
	}
	// write the type
	long type = TYPE_BIT;
	fwrite( &type, 4, 1, fp );
	
	// first build a temporary header...
	long temp[10*10];
	long *hdSt = &header[0][0];
	for ( int i = 0; i<10*10; i++ )
		for ( int j = 0; j<=i; j++ )
			if ( compareBlock( i, j ) )
			{
				temp[i] = j;
				break;
			}

	long newHd[10*10];
	int nextFree = 0;
	for ( i = 0; i<10*10; i++ )
		if ( temp[i] < hdSt[i] )
		{
			newHd[i] = newHd[ temp[i] ]; // the blocks are the same
		} else {
			newHd[i] = nextFree++;			
		}

	// now write out the header.
	fwrite( newHd, 4, 10*10, fp );

	// now 4 the data.
	for ( i = 0; i<10*10; i++ )
		if ( temp[i] >= hdSt[i] )
			fwrite( data[ hdSt[i] ], 1, 64*8, fp );			// write out this block (first time seen)

	fclose(fp);

	return true; // we have been sucessfull...
}


//////////////////////////////////////////////////////////////////////////
//	Grid_Byte functions													//
//////////////////////////////////////////////////////////////////////////
Grid_Byte::Grid_Byte()
{
	long *t = &header[0][0]; // the start of header
	// basic constructor - set all values to 0 and all headers to run consecutivley up..
	for ( int i = 0; i< 80*80; i++ )
		*t++ = i;
	for ( i = 0; i < (80*80*8*8/4); i++ )
		*t++ = 0;
}

bool Grid_Byte::compareBlock(long a, long b)
{
	if ( a==b )
		return true;
	for ( int x = 0; x<8; x++ )
		for ( int y = 0; y<8; y++ )
			if ( data[a][x][y] != data[b][x][y] )
				return false;

	return true;
}

void Grid_Byte::copyBlock( long from, long to )
{
	if ( from == to )
		return;
	for ( int x = 0; x<8; x++ )
		for ( int y = 0; y<8; y++ )
			data[to][x][y] = data[from][x][y];

}

void Grid_Byte::set( int x, int y, UByte v )
{
	// dead simple method, compression done at save time
	data[ header[x>>3][y>>3] ][x&7][y&7] = v;
}

long Grid_Byte::get( int x, int y )
{
	return (long) data[ header[x>>3][y>>3] ][x&7][y&7];
}

bool Grid_Byte::load( char *filename )
{
	FILE* fp;
	if((fp=fopen(filename,"rb"))==NULL){
		return false; // it hasn't worked 4 some reason...
	}
	// read the type
	long type;
	fread( &type, 4, 1, fp );
	if ( type != TYPE_BYTE )
		return false;

	// load into a temporary header
	long temp[80*80];
	fread( temp, 4, 80*80, fp );

	// now load the data
	int max_used = 0;
	while ( !feof( fp ) )
	{
		fread( &data[max_used++][0], 1, 8*8, fp );
	}

	// now copy the appropriate data blocks to the right places.
	for ( int i = 80*80-1; i>0; i-- )
	{
		copyBlock( temp[i], i );
	}

	return true;
}

bool Grid_Byte::save( char *filename )
{
	FILE* fp;
	if((fp=fopen(filename,"wb"))==NULL){
		return false; // it hasn't worked 4 some reason...
	}
	// write the type
	long type = TYPE_BYTE;
	fwrite( &type, 4, 1, fp );
	
	// first build a temporary header...
	long temp[80*80];
	long *hdSt = &header[0][0];
	for ( int i = 0; i<80*80; i++ )
		for ( int j = 0; j<=i; j++ )
			if ( compareBlock( i, j ) )
			{
				temp[i] = j;
				break;
			}

	long newHd[80*80];
	int nextFree = 0;
	for ( i = 0; i<80*80; i++ )
		if ( temp[i] < hdSt[i] )
		{
			newHd[i] = newHd[ temp[i] ]; // the blocks are the same
		} else {
			newHd[i] = nextFree++;			
		}

	// now write out the header.
	fwrite( newHd, 4, 80*80, fp );

	// now 4 the data.
	for ( i = 0; i<80*80; i++ )
		if ( temp[i] >= hdSt[i] )
			fwrite( data[ hdSt[i] ], 1, 8*8, fp );			// write out this block (first time seen)

	fclose(fp);

	return true; // we have been sucessfull...
}


//////////////////////////////////////////////////////////////////////////
//	Grid_Word functions												//
//////////////////////////////////////////////////////////////////////////
Grid_Word::Grid_Word()
{
	long *t = &header[0][0]; // the start of header
	// basic constructor - set all values to 0 and all headers to run consecutivley up..
	for ( int i = 0; i< 80*80; i++ )
		*t++ = i;
	for ( i = 0; i < (80*80*8*8/2); i++ )
		*t++ = 0;
}

bool Grid_Word::compareBlock(long a, long b)
{
	if ( a==b )
		return true;
	for ( int x = 0; x<8; x++ )
		for ( int y = 0; y<8; y++ )
			if ( data[a][x][y] != data[b][x][y] )
				return false;

	return true;
}

void Grid_Word::set( int x, int y, UWord v )
{
	// dead simple method, compression done at save time
	data[ header[x>>3][y>>3] ][x&7][y&7] = v;
}

long Grid_Word::get( int x, int y )
{
	return (long) data[ header[x>>3][y>>3] ][x&7][y&7];
}

bool Grid_Word::save( char *filename )
{
	FILE* fp;
	if((fp=fopen(filename,"wb"))==NULL){
		return false; // it hasn't worked 4 some reason...
	}
	// write the type
	long type = TYPE_WORD;
	fwrite( &type, 4, 1, fp );
	
	// first build a temporary header...
	long temp[80*80];
	long *hdSt = &header[0][0];
	for ( int i = 0; i<80*80; i++ )
		for ( int j = 0; j<=i; j++ )
			if ( compareBlock( i, j ) )
			{
				temp[i] = j;
				break;
			}

	long newHd[80*80];
	int nextFree = 0;
	for ( i = 0; i<80*80; i++ )
		if ( temp[i] < hdSt[i] )
		{
			newHd[i] = newHd[ temp[i] ]; // the blocks are the same
		} else {
			newHd[i] = nextFree++;			
		}

	// now write out the header.
	fwrite( newHd, 4, 80*80, fp );

	// now 4 the data.
	for ( i = 0; i<80*80; i++ )
		if ( temp[i] >= hdSt[i] )
			fwrite( data[ hdSt[i] ], 2, 8*8, fp );			// write out this block (first time seen)

	fclose(fp);

	return true; // we have been sucessfull...
}

//////////////////////////////////////////////////////////////////////////
//	Grid_Long functions												//
//////////////////////////////////////////////////////////////////////////
Grid_Long::Grid_Long()
{
	long *t = &header[0][0]; // the start of header
	// basic constructor - set all values to 0 and all headers to run consecutivley up..
	for ( int i = 0; i< 80*80; i++ )
		*t++ = i;
	for ( i = 0; i < (80*80*8*8); i++ )
		*t++ = 0;
}

bool Grid_Long::compareBlock(long a, long b)
{
	if ( a==b )
		return true;
	for ( int x = 0; x<8; x++ )
		for ( int y = 0; y<8; y++ )
			if ( data[a][x][y] != data[b][x][y] )
				return false;

	return true;
}

void Grid_Long::set( int x, int y, long v )
{
	// dead simple method, compression done at save time
	data[ header[x>>3][y>>3] ][x&7][y&7] = v;
}

// set a value as if the grid was 1280x1280 of bytes not 640x640 longs.
void Grid_Long::setD( int x, int y, unsigned char v )
{
	int sx = x>>1;
	int sy = y>>1;
	char* t = (char*)&data[ header[sx>>3][sy>>3] ][sx&7][sy&7];
	t+= (x&1) + (2*(y&1));
	*t = v;
}

// get a value as if the grid was 1280x1280 of bytes not 640x640 longs.
unsigned char Grid_Long::getD( int x, int y )
{
	int sx = x>>1;
	int sy = y>>1;
	char* t = (char*)&data[ header[sx>>3][sy>>3] ][sx&7][sy&7];
	t+= (x&1) + (2*(y&1));
	return *t;
}

long Grid_Long::get( int x, int y )
{
	return data[ header[x>>3][y>>3] ][x&7][y&7];
}

bool Grid_Long::save( char *filename )
{
	FILE* fp;
	if((fp=fopen(filename,"wb"))==NULL){
		return false; // it hasn't worked 4 some reason...
	}
	// write the type
	long type = TYPE_LONG;
	fwrite( &type, 4, 1, fp );
	
	// first build a temporary header...
	long temp[80*80];
	long *hdSt = &header[0][0];
	for ( int i = 0; i<80*80; i++ )
		for ( int j = 0; j<=i; j++ )
			if ( compareBlock( i, j ) )
			{
				temp[i] = j;
				break;
			}

	long newHd[80*80];
	int nextFree = 0;
	for ( i = 0; i<80*80; i++ )
		if ( temp[i] < hdSt[i] )
		{
			newHd[i] = newHd[ temp[i] ]; // the blocks are the same
		} else {
			newHd[i] = nextFree++;			
		}

	// now write out the header.
	fwrite( newHd, 4, 80*80, fp );

	// now 4 the data.
	for ( i = 0; i<80*80; i++ )
		if ( temp[i] >= hdSt[i] )
			fwrite( data[ hdSt[i] ], 4, 8*8, fp );			// write out this block (first time seen)

	fclose(fp);

	return true; // we have been sucessfull...
}



////////////////////////////////////////////////////////////////////////////////////
// loads a grid of unspecified type- do NOT modify the returned object in any way...
Grid_Base* loadGrid( char* filename )
{
	FILE* fp;
	if((fp=fopen(filename,"rb"))==NULL){
		return NULL; // it hasn't worked 4 some reason...
	}
	// get file size
	fseek(fp, 0, SEEK_END );
	int fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET );

	// read in entire file
	char *theGrid = new char[ fsize ];
	fread( theGrid, 1, fsize, fp );
	fclose( fp );

	Grid_Base::makeGridAt( theGrid );
	return (Grid_Base*)theGrid;
}

//stuff for within the game so that there is no conflicts on the grids...
#ifdef	FILE_Included // only done if the files are included first - i.e inside bob
#undef new
static Grid_Byte blankInst;
Grid_Byte* Grid_Byte_File::blank = &blankInst;
#define new DEBUG_NEW
//DeadCode JON 28Jul00 Grid_Byte_File* Grid_Base::gridfiles[GF_TABLESIZE]={ /*NULL*/};
static Grid_Byte_File gridTable[Grid_Base::GF_TABLESIZE];
Grid_Byte_File* Grid_Base::gridfiles = gridTable;
//DeadCode JON 11Aug00 Grid_Byte_File* Grid_Base::gridfiles/*[GF_TABLESIZE]*/=new Grid_Byte_File[GF_TABLESIZE];
fileblock* Grid_Base::CloudGrids[3]={ NULL };

//////////////////////////////////////////////////////////////////////
//
// Function:    OpenGridFiles
// Date:		25/05/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	Grid_Base::OpenGridFiles()
{
	CloseGridFiles();	
//DeadCode JON 28Jul00 	gridfiles[GF_RADAR]=new fileblock(FIL_RADARGRID, makeGridAt );
//DeadCode JON 28Jul00 	gridfiles[GF_COLOUR]=new fileblock( FIL_4COLGRID, makeGridAt );
//DeadCode JON 28Jul00 //DeadCode JON 28Jul00 	gridfiles[GF_LOWCLOUD]=new fileblock( FIL_CLOUDGRID_01, makeGridAt );
//DeadCode JON 28Jul00 	gridfiles[GF_MINALT]=new fileblock( FIL_MINALT, makeGridAt );
	gridfiles[GF_RADAR].SetFile( new fileblock(FIL_RADARGRID, makeGridAt ) );
	gridfiles[GF_COLOUR].SetFile( new fileblock( FIL_4COLGRID, makeGridAt ) );
//DeadCode JON 28Jul00 	gridfiles[GF_LOWCLOUD]=new fileblock( FIL_CLOUDGRID_01, makeGridAt );
	gridfiles[GF_MINALT].SetFile( new fileblock( FIL_MINALT, makeGridAt ) );
	gridfiles[GF_CORNERALT].SetFile( new fileblock( FIL_CORNERALT, makeGridAt ));
	CloudGrids[0]=new fileblock(FIL_CLOUDGRID_00, makeGridAt );
	CloudGrids[1]=new fileblock(FIL_CLOUDGRID_01, makeGridAt );
	CloudGrids[2]=new fileblock(FIL_CLOUDGRID_02, makeGridAt );
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SetCloudGrid

// Date:		28/07/00
// Author:		JON
//
//Description: Initialises a cloud layer with a grid appropriate to the cover.
//
//////////////////////////////////////////////////////////////////////

void	Grid_Base::SetCloudGrid( int layer, UByte cover )
{
//DeadCode JON 28Jul00 	if ( gridfiles[GF_CLOUDLAYER0+layer] != NULL )
//DeadCode JON 28Jul00 	{
//DeadCode JON 28Jul00 		delete gridfiles[GF_CLOUDLAYER0+layer];
//DeadCode JON 28Jul00 		gridfiles[GF_CLOUDLAYER0+layer] = NULL;
//DeadCode JON 28Jul00 	} 
//DeadCode JON 28Jul00 	if ( cover < 64 )
//DeadCode JON 28Jul00 		gridfiles[GF_CLOUDLAYER0+layer]=new fileblock( (void*)new Grid_Byte() );// blank
//DeadCode JON 28Jul00 	else if ( cover < 128 )
//DeadCode JON 28Jul00 		gridfiles[GF_CLOUDLAYER0+layer]=new fileblock( FIL_CLOUDGRID_00, makeGridAt ); // scattered
//DeadCode JON 28Jul00 	else if ( cover < 192 )
//DeadCode JON 28Jul00 		gridfiles[GF_CLOUDLAYER0+layer]=new fileblock( FIL_CLOUDGRID_01, makeGridAt ); // overcast
//DeadCode JON 28Jul00 	else
//DeadCode JON 28Jul00 		gridfiles[GF_CLOUDLAYER0+layer]=new fileblock( FIL_CLOUDGRID_02, makeGridAt ); // heavy
//DeadCode JON 6Sep00 	if ( cover < 64 )
//DeadCode JON 6Sep00 		gridfiles[GF_CLOUDLAYER0+layer].CloseFile();// blank
//DeadCode JON 6Sep00 	else if ( cover < 128 )
//DeadCode JON 6Sep00 		gridfiles[GF_CLOUDLAYER0+layer].SetFile( CloudGrids[0] ); // scattered
//DeadCode JON 6Sep00 	else if ( cover < 192 )
//DeadCode JON 6Sep00 		gridfiles[GF_CLOUDLAYER0+layer].SetFile( CloudGrids[1] ); // overcast
//DeadCode JON 6Sep00 	else
//DeadCode JON 6Sep00 		gridfiles[GF_CLOUDLAYER0+layer].SetFile( CloudGrids[2] ); // heavy
	switch ( cover>>6 )
	{
	case 0: // cover < 64 
		gridfiles[GF_CLOUDLAYER0+layer].CloseFile();// blank
		break;
	case 1: // 64 <= cover < 128 
		gridfiles[GF_CLOUDLAYER0+layer].SetFile( CloudGrids[0] ); // scattered
		break;
	case 2:	 // 128 <= cover < 192 
		gridfiles[GF_CLOUDLAYER0+layer].SetFile( CloudGrids[1] ); // overcast
		break;
	case 3: // 192 <= cover
		gridfiles[GF_CLOUDLAYER0+layer].SetFile( CloudGrids[2] ); // heavy
		break;
	default:
#ifndef NDEBUG
		INT3; // oops
#else
	NODEFAULT;
#endif
		break;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    CloseGridFiles
// Date:		25/05/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	Grid_Base::CloseGridFiles()
{
	for ( int i=0; i<3; i++ )
	{
		if ( CloudGrids[i] !=NULL )
		{
			delete CloudGrids[i];
			CloudGrids[i] = NULL;
		}
		gridfiles[GF_CLOUDLAYER0+i].CloseFile();
	}

	for (i=0;i<GF_TABLESIZE;i++)
	{
		if ( gridfiles[i].getdata() != NULL )
		{
//DeadCode JON 28Jul00 			delete gridfiles[i];
//DeadCode JON 28Jul00 			gridfiles[i]=NULL;
			gridfiles[i].ReallyCloseFile();
		}
	}

}

#endif

