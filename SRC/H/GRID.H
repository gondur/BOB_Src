// Grid types header file
// Jon
#ifndef _GRID_H
#define _GRID_H

#include <malloc.h>

#ifdef	FILE_Included // only done if the files are included first - i.e inside bob
class Grid_Byte_File;
#endif

class Grid_Base // an abstract class
{
public:

	enum { WORLDSPACEMOD = 17 };
	enum { TYPE_BIT, TYPE_BYTE, TYPE_WORD, TYPE_LONG };
#undef new
	inline void* operator new( size_t s, void* inplacelocation );
	inline void* operator new []( size_t s ) { return(::operator new(s)); } // equivalent to the normal one
	inline void* operator new( size_t s ) { return(::operator new(s)); } // equivalent to the normal one

	inline void operator delete( void* ,void* inplacelocation ) {}
	inline void operator delete( void* rv ) {::operator delete(rv); } // equivalent to the normal one
	inline void operator delete []( void* rv ) {::operator delete(rv); } // equivalent to the normal one
#ifdef	DEBUG_NEW
	#define	new DEBUG_NEW
#endif
	inline long getMod( const int &x, const int &y ) { return get( x+64, y+64 ); }
	inline long getWorld( ULong x, ULong y ) { return get( (x>>WORLDSPACEMOD)+64, (y>>WORLDSPACEMOD)+64 ); }
	virtual long get( int x, int y ) = 0;		// pure virtual
	inline long getFlip( int x, int y ) { return get( x, 639 - y ); } // get the upside down version...
	virtual bool save( char* filename ) = 0;	// pure virtual
	virtual bool load( char* filename ) = 0;	// pure virtual - loads one back in again
	virtual long type( void ) = 0;				// pure virtual - return the type

	static void makeGridAt( void* &dataarea, ULong& datasize ); // the second parameter is ignored...
	static void makeGridAt( void* dataarea );

	//stuff for within the game so that there is no conflicts on the grids...
#ifdef	FILE_Included // only done if the files are included first - i.e inside bob
	static	void	OpenGridFiles();
	static	void	CloseGridFiles();
	static	void	SetCloudGrid( int layer, UByte cover );
	enum	GridFiles	{GF_CLOUDLAYER0,GF_CLOUDLAYER1,GF_CLOUDLAYER2,GF_RADAR,GF_MINALT,GF_MAXALT,GF_AVEALT,GF_COLOUR,GF_CORNERALT,GF_TABLESIZE};
	static Grid_Byte_File* gridfiles/*[GF_TABLESIZE]*/;
	static fileblock* CloudGrids[3];
#endif
};

#ifdef	FILE_Included
class Grid_Byte;
class Grid_Byte_File
{	
	fileblock *file;
	public:
	static Grid_Byte* blank;
	CON Grid_Byte_File( void )
	{
		file = NULL;
	}

	CON Grid_Byte_File( fileblock* fb )
	{
		file = fb;
	}

//DeadCode JON 28Jul00 	DES ~Grid_Byte_File( void )
//DeadCode JON 28Jul00 	{
//DeadCode JON 28Jul00 		if ( file )
//DeadCode JON 28Jul00 		{
//DeadCode JON 28Jul00 			delete file;
//DeadCode JON 28Jul00 			file = NULL;
//DeadCode JON 28Jul00 		}
//DeadCode JON 28Jul00 	}

	void SetFile( fileblock* fb )
	{
//DeadCode JON 28Jul00 		if ( file )
//DeadCode JON 28Jul00 		{
//DeadCode JON 28Jul00 			delete file;
//DeadCode JON 28Jul00 		}
		file = fb;
	}

	void CloseFile( void )
	{
		if ( file )
		{
			file = NULL;
		}
	}


	void ReallyCloseFile( void )
	{
		if ( file )
		{
			delete file;
			file = NULL;
		}
	}

	Grid_Byte* getdata( void )
	{
		if ( file )
			return (Grid_Byte*) file->getdata();
		else
			return blank;
	}
};
#endif

class Grid_Bit : public Grid_Base
{
private:
	long header[10][10];							// pointer offsets to an 10x10 subgrid of the data
	char data[10*10][64][8];							// 10x10 blocks of data... = 10x64 = 640x640 total grid size
	inline bool compareBlock( long a, long b );

public:
	Grid_Bit( void );						//constructor
	Grid_Bit( int fake ) {}					//fake constructor for inline inplacement

	virtual long get( int x, int y );
	virtual bool save( char* filename );
	virtual bool load( char* filename ) { return false; } // not implemented - only use the general load method.
	virtual long type( void ) { return TYPE_BIT; }

	void set( int x, int y, bool v );
	inline void setFlip( int x, int y, bool v ) { set( x, 639-y, v ); } // set it but upside down...
};


class Grid_Byte : public Grid_Base
{
private:
	long header[80][80];
	UByte data[(80*80)][8][8];
	inline bool compareBlock( long a, long b );
	inline void copyBlock( long from, long to );

public:
	Grid_Byte( void );
	Grid_Byte( int fake ) {}					//fake constructor for inline inplacement

	virtual long get( int x, int y );
	virtual bool save( char* filename );
	virtual bool load( char* filename );// { return false; } // not implemented - only use the general load method.
	virtual long type( void ) { return TYPE_BYTE; }

	void set( int x, int y, UByte v );
	inline void setFlip( int x, int y, UByte v ) { set( x, 639-y, v ); } // set it but upside down...
};

class Grid_Word : public Grid_Base
{
private:
	long header[80][80];
	UWord data[(80*80)][8][8];
	inline bool compareBlock( long a, long b );

public:
	Grid_Word( void );
	Grid_Word( int fake ) {}					//fake constructor for inline inplacement

	virtual long get( int x, int y );
	virtual bool save( char* filename );
	virtual bool load( char* filename ) { return false; } // not implemented - only use the general load method.
	virtual long type( void ) { return TYPE_WORD; }

	void set( int x, int y, UWord v );
	inline void setFlip( int x, int y, UWord v ) { set( x, 639-y, v ); } // set it but upside down...

};

class Grid_Long : public Grid_Base
{
private:
	long header[80][80];
	long data[(80*80)][8][8];
	inline bool compareBlock( long a, long b ); 

public:
	Grid_Long( void );
	Grid_Long( int fake ) {}					//fake constructor for inline inplacement

	virtual long get( int x, int y );
	
	virtual bool save( char* filename );
	virtual bool load( char* filename ) { return false; } // not implemented - only use the general load method.
	virtual long type( void ) { return TYPE_LONG; }

	void set( int x, int y, long v );
	inline void setFlip( int x, int y, long v ) { set( x, 639-y, v ); } // set it but upside down...
	
	void setD( int x, int y, unsigned char v );  // set a value as if the grid was 1280x1280 of bytes not 640x640 longs.
	inline void setDFlip( int x, int y, unsigned char v ) { setD( x, 1279-y, v ); } // set it but upside down...
	
	unsigned char getD( int x, int y ); 			// get a value as if the grid was 1280x1280 of bytes not 640x640 longs.
	inline unsigned char getDFlip( int x, int y ) { return getD( x, 1279-y ); } // get but upside down
	inline UByte getWorldD( ULong x, ULong y ) { return getD( (x>>(WORLDSPACEMOD-1))+128, (y>>(WORLDSPACEMOD-1))+128 ); }
	inline UByte getModD( int x, int y ) { return getD( x+128, y+128 ); }

};


// loads a grid of unspecified type- do NOT modify the returned object in any way...
Grid_Base* loadGrid( char* filename );
//void makeGridAt( void* &dataarea, ULong& datasize ); // the second parameter is ignored...
//void makeGridAt( void* dataarea );

#endif


