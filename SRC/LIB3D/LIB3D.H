#ifndef LIB3D_Included
#define LIB3D_Included

#define _NO_VERTEX_SHARING_HDR

// GUID for first implementation of 3D graphics library 08-11-1999
// {11038561-95E1-11d3-8795-0040052C1F45}
//TEMPCODE DAW 29/01/00 #include <objbase.h>
#include <d3dtypes.h>

#ifdef LIB3D_EXPORTS
#define LIB3D_API __declspec(dllexport)
#else
#define LIB3D_API __declspec(dllimport)
#endif

//#define DOUBLE_MATRIXES

const ULong FORCE_TO_BACK_Z = 3;
const ULong NUM_Z_LAYERS = 4;// as above but +1...						//JON 23Oct00

#ifndef DOUBLE_MATRIXES
typedef D3DVALUE R3DMATRIX_VAL;
struct R3DMATRIX
{
	union 
	{
//		D3DMATRIX mat;
		struct {
#pragma warning( disable : 4201)
            D3DVALUE        _11, _12, _13, _14;
            D3DVALUE        _21, _22, _23, _24;
            D3DVALUE        _31, _32, _33, _34;
            D3DVALUE        _41, _42, _43, _44;
        };
		D3DVALUE m[4][4];
	};
    R3DMATRIX() { }
    R3DMATRIX(  D3DVALUE _m00, D3DVALUE _m01, D3DVALUE _m02, D3DVALUE _m03,
                D3DVALUE _m10, D3DVALUE _m11, D3DVALUE _m12, D3DVALUE _m13,
                D3DVALUE _m20, D3DVALUE _m21, D3DVALUE _m22, D3DVALUE _m23,
                D3DVALUE _m30, D3DVALUE _m31, D3DVALUE _m32, D3DVALUE _m33
        )
        {
                m[0][0] = _m00; m[0][1] = _m01; m[0][2] = _m02; m[0][3] = _m03;
                m[1][0] = _m10; m[1][1] = _m11; m[1][2] = _m12; m[1][3] = _m13;
                m[2][0] = _m20; m[2][1] = _m21; m[2][2] = _m22; m[2][3] = _m23;
                m[3][0] = _m30; m[3][1] = _m31; m[3][2] = _m32; m[3][3] = _m33;
        }
	operator const D3DMATRIX() const 
	{
//		return mat;
		const D3DMATRIX* tmp = (D3DMATRIX*)m;
		return *tmp;
	}
	bool operator== ( const R3DMATRIX& other ) const
	{
		for (ULong i=16,*aptr=(ULong*)&_11,*bptr=(ULong*)&other._11;i!=0;aptr++,bptr++)
			if (*aptr!=*bptr) return false;
		return true;
	}

};
#else
typedef double R3DMATRIX_VAL;
struct R3DMATRIX
{
    union {
        struct {
            R3DMATRIX_VAL        _11, _12, _13, _14;
            R3DMATRIX_VAL        _21, _22, _23, _24;
            R3DMATRIX_VAL        _31, _32, _33, _34;
            R3DMATRIX_VAL        _41, _42, _43, _44;
        };
        double m[4][4];
    };
    R3DMATRIX() { }
    R3DMATRIX(  R3DMATRIX_VAL _m00, R3DMATRIX_VAL _m01, R3DMATRIX_VAL _m02, R3DMATRIX_VAL _m03,
                R3DMATRIX_VAL _m10, R3DMATRIX_VAL _m11, R3DMATRIX_VAL _m12, R3DMATRIX_VAL _m13,
                R3DMATRIX_VAL _m20, R3DMATRIX_VAL _m21, R3DMATRIX_VAL _m22, R3DMATRIX_VAL _m23,
                R3DMATRIX_VAL _m30, R3DMATRIX_VAL _m31, R3DMATRIX_VAL _m32, R3DMATRIX_VAL _m33
        )
        {
                m[0][0] = _m00; m[0][1] = _m01; m[0][2] = _m02; m[0][3] = _m03;
                m[1][0] = _m10; m[1][1] = _m11; m[1][2] = _m12; m[1][3] = _m13;
                m[2][0] = _m20; m[2][1] = _m21; m[2][2] = _m22; m[2][3] = _m23;
                m[3][0] = _m30; m[3][1] = _m31; m[3][2] = _m32; m[3][3] = _m33;
        }

	R3DMATRIX( const D3DMATRIX& convert )
	{
		D3DVALUE* pother = (D3DVALUE*)&convert;
		R3DMATRIX_VAL* pv = (R3DMATRIX_VAL*)&_11;
		for ( int i = 0; i<16; i++ )
		{
			*pv++=*pother++;			
		}
	}
	
	operator const D3DMATRIX() const  
	{
		D3DMATRIX t;
		D3DVALUE* pt = (D3DVALUE*)&t;
		R3DMATRIX_VAL* pv = (R3DMATRIX_VAL*)&_11;
		for ( int i = 0; i<16; i++ )
		{
			*pt++=*pv++;			
		}
		return	t;		
	}

	bool operator== ( const R3DMATRIX& other ) const
	{
		for (ULong i=32,*aptr=(ULong*)&_11,*bptr=(ULong*)&other._11;i!=0;aptr++,bptr++)
			if (*aptr!=*bptr) return false;
		return true;
	}

//DeadCode JON 19Sep00     R3DMATRIX_VAL& operator()(int iRow, int iColumn) { return m[iRow][iColumn]; }
//DeadCode JON 19Sep00     const R3DMATRIX_VAL& operator()(int iRow, int iColumn) const { return m[iRow][iColumn]; }
};
#endif

// the following may be used to speed up switch statements add NODEFAULT; after case statements
#ifdef NDEBUG 
#define NODEFAULT   __assume(0)
#else
#ifdef _INSIDE_LIB3D_
#define NODEFAULT   default: INT3; break
#else
#define NODEFAULT	default: assert( 0 && "Default reached that doesn't exist" ); break
#endif
#endif

class F2UL_Round
{
	union
	{
		double f;
		ULong l[2];
	};
public:
	F2UL_Round( const double nf )
	{
		const double _BASE_ADD = (1024. * 1024. * 1024. * 1024. * 1024. * 4.); //2^52
		f=nf+_BASE_ADD;
	}
	inline operator ULong() 
	{
		return l[0];
	}
};

class F2UB_Clip
{
	union
	{
		float f;
		ULong l;
	};
public:
	F2UB_Clip( const float nf )
	{
		const double _BASE_ADD = 8388608.; // 2^23
		f=nf+_BASE_ADD;
	}

	inline operator UByte()
	{
		if ( (l&0xFFFFFF00) != (0x4B000000) )
		{
			return (255-(l>>16))&0xFF;
		} else
		{
			return l&0xFF;
		}
	}
};

class R3DCOLOUR
{
public:
	union
	{
#pragma warning( disable : 4201)
		ULong all;
		struct
		{ // funny order?3
#pragma warning( disable : 4201)
			UByte blue;//alpha;
			UByte green;//red;
			UByte red;//green;
			UByte alpha;//blue;
		};
	};

	inline operator ULong() 
	{
		return all;
	}
	inline operator ULong&() 
	{
		return all;
	}

	inline operator const ULong() const  
	{
		return all;
	}


//	inline operator const ULong&() const  
//	{
//		return all;
//	}

	
	inline void set( UByte r, UByte g, UByte b )
	{
		red = r;
		green = g;
		blue = b;
	}

	inline R3DCOLOUR& operator= (const ULong t)
	{
		all = t;
		return *this;
	}

	// change to linear value frac distance between current col and other col
	// doesn't do alpha
	inline void interpRGB( const R3DCOLOUR other, const double frac)
	{
		red+= UByte(double(other.red-red) * frac);
		green+= UByte(double(other.green-green) * frac);
		blue+= UByte(double(other.blue-blue) * frac);
	}

	inline void interpRGBA( const R3DCOLOUR other, const double frac)
	{
		red+= UByte(double(other.red-red) * frac);
		green+= UByte(double(other.green-green) * frac);
		blue+= UByte(double(other.blue-blue) * frac);
		alpha+= UByte(double(other.alpha-alpha) * frac);
	}

};

enum Angles;
const UWord NULL_LAND_TEXT_REF = 0xFFFF;

typedef ULong HDRIVER;
typedef ULong HMODE;
//deadcode typedef ULong HMATERIAL;
typedef ULong HTEXTUREMAP;
//DeadCode JON 17Sep00 typedef ULong HRENDERTARGET;

enum RENDERTARGET_TYPE
{
	RENDERTARGET_PRIMARY = 0,
	RENDERTARGET_LANDSCAPE,
	RENDERTARGET_MIRROR
};

class HRENDERTARGET
{
	UByte targetType;
	UByte pad;
	UWord targetInstance;
public:
	HRENDERTARGET() {/* default constructor*/}
	HRENDERTARGET( ULong type )
	{
#ifndef NDEBUG
	if ( type == RENDERTARGET_LANDSCAPE )
		INT3; // you need to set a target tile for this...
#endif
		targetType = type;
	}
	HRENDERTARGET( ULong type, UWord instance )
	{
#ifndef NDEBUG
	if ( type != RENDERTARGET_LANDSCAPE )
		INT3; // doh, can't set an instance for these...
#endif
		targetType = RENDERTARGET_LANDSCAPE;
		targetInstance = instance;
	}
	UByte getType() const { return targetType; }
	UWord getInstance() const { return targetInstance; }
};

#define	MAX_DRIVERS		16
#define	MAX_MODES		128
#define	MAX_TEXT_LENGTH	64

//DeadCode JON 17Sep00 #define RENDERTARGET_PRIMARY HRENDERTARGET(0)
//DeadCode JON 17Sep00 #define RENDERTARGET_LANDSCAPE HRENDERTARGET(1)
//DeadCode JON 17Sep00 #define RENDERTARGET_MIRROR HRENDERTARGET(2)

#define NUM_PALETTES	8

typedef enum HMATRIX {MATRIX_PROJECTION,MATRIX_VIEWER,MATRIX_OBJECT} HMATRIX;
typedef enum HAXIS {AXIS_PITCH,AXIS_HEADING,AXIS_ROLL} HAXIS;
typedef enum LIGHTFLAG 
{
	LF_ALPHA,
	LF_LIGHTSOURCE,
	LF_VERTEX,
	LF_FONT,
	LF_DEPTH,
	LF_AMBIENT, // must be in this order at the end so the < test can be done
	LF_LIGHTING,
	LF_SPECULAR,
	LF_MAPCOLBIT = 8, // must be a bit...  (	see SetVertexCol )
	LF_DUMMY = 0xff
} LIGHTFLAG;
typedef enum HINTS 
{
	HINT_TRILINEAR,			HINT_BILINEAR,			HINT_NOBLEND,
	HINT_FULL_RES_TEXTURE,	HINT_HALF_RES_TEXTURE,	HINT_QUARTER_RES_TEXTURE,	HINT_EIGHTH_RES_TEXTURE,
	HINT_ALIASEDGES,		HINT_ALIASNONE,			HINT_CLIPPING_OFF,			HINT_CLIPPING_ON,
	HINT_2DRENDER,			HINT_3DRENDER,
	HINT_MAX_HINT
}
HINTS;
typedef enum TOGGLES 
{
	TOGGLE_GLOBALALPHA=0,
	TOGGLE_GLOBALTRANSPARENCY=TOGGLE_GLOBALALPHA,
	TOGGLE_GLOBALLUMINOSITY=TOGGLE_GLOBALALPHA,
	TOGGLE_GLOBAL2DZDEPTH,
	TOGGLE_TEXTURE_ZBIAS,												//JON 14Aug00
	TOGGLE_TRANSPARENT_ZBIAS,											//JON 3Oct00
	TOGGLE_TEXTURE_QUALITY // only use when texture quality must be forced, otherwise use hint	//JON 19Jul00
}
TOGGLES;
typedef enum TRANSFORMFLAGS
{
	TF_NULL=0,
	TF_NOCOPY
}
TRANSFORMFLAGS;
typedef enum TCFLAGS
{
	TC_NULL			= 0x00000000,
	TC_RENDERTARGET	= 0x00000001
}
TCFLAGS;
typedef struct MAPDESC
{
	UWord		w,h;				//4
	UByteP		body;				//4
	UByteP		alpha;				//4
	UByteP		palette;			//4
	UByte		paletteindex:4,
				isMasked:1,
				blendType:3;
	HTEXTUREMAP	hTextureMap;		//4
									//21
}
MAPDESC;
typedef struct LIGHTINGDESC
{
	ULong		lowRGB;
	ULong		highRGB;
	ULong		ambientRGB;
	R3DCOLOUR	specularRGB;											//JON 11Sep00
	D3DVALUE	lowDot,highDot;
//	D3DVALUE	specularPower; // currently hardcoded...
}
LIGHTINGDESC;
enum TextIdType {
	TIT_LOADED			= 0x0000,			// loaded in by rob's system
//	TIT_DYNAMIC			= 0x4000,			// dynamically built - not used, doh...
	TIT_LANDSCAPE		= 0x8000,			// landscape tiles.
	TIT_PLAIN			= 0xC000,			// plain coloured.
	TIT_MASK_INDEX		= 0x07FF,
	TIT_MASK_TYPE		= 0xC000,
	TIT_MASK_SECONDARY	= 0x3800,
	TIT_BASE_SECONDARY	= 0x0800,
	TIT_NULL			= 0xFFFF
}; // note that if value==0 then the texture needs uploading...

enum { MSK_NONE = 0, MSK_MASKED, MSK_TRANS };
enum	AlphaBlendTypes
{
	BLEND_NULL=0,
	BLEND_SRCALPHA_DESTSOLID,
	BLEND_ADDALPHA = BLEND_SRCALPHA_DESTSOLID,
	BLEND_SRCALPHA_DESTINVSRCALPHA,
	BLEND_AVERAGEALPHA = BLEND_SRCALPHA_DESTINVSRCALPHA,
	BLEND_SRCSOLID_DESTSOLID,
	BLEND_ADD = BLEND_SRCSOLID_DESTSOLID,
	BLEND_SRCRGB_DESTRBG,
	BLEND_MULTIPLY = BLEND_SRCRGB_DESTRBG,
	BLEND_SRCSOLID_DESTINVSRCALPHA,
	BLEND_GAY = BLEND_SRCSOLID_DESTINVSRCALPHA
};
typedef struct Material
{
	MAPDESC *p[3];				//12	//ImageMap ptrs
	float	tsW[3],tsH[3];		//24	//Texture coordinate scale factors
	ULong	isLand;				//4     //if a landscape it's number, else 0;
	UWord	uniqueTextID;		//2		//unique ID for this material
	UByte	materialFlags;		//1
	UByte	c;					//1		//Color index or the alpha value...
	UByte	f;					//1		//Flag 0==plain color, >0 gives number of texture stages for the material
	UByte	isMasked;			//1		//is the top level texture solid, masked or transparent 
	UByte	pad0,pad1;			//2
								//48 == total bytes
	Material(UByte cc) // constructor with a colour index
	{
		c=cc; 
		f=0x00;
		isLand=0;
		isMasked=MSK_NONE;
		uniqueTextID = TIT_PLAIN+cc;
		p[0]=p[1]=p[2]=NULL;
	}
	Material() 
	{
		p[0]=p[1]=p[2]=NULL;
		isMasked=MSK_NONE;
		f=0;
		c=0;
		isLand=0;
		uniqueTextID = TIT_NULL;
	} // blank constructor - check
	Material(MAPDESC *p0,MAPDESC *p1=NULL,MAPDESC *p2=NULL) // construct with imagemaps.
	{
		c=0;
		p[0]=p0; 
		p[1]=p1; 
		p[2]=p2; 
		f=0x00;
//DEADCODE JON 2/16/00 		isMasked=(p[0]->isMasked || p[0]->alpha!=NULL)?0x01:0x00;
		if ( p[0]->isMasked )
		{
			isMasked=MSK_MASKED;
		} else 
		{
			if ( p[0]->alpha!=NULL )
				isMasked=MSK_TRANS;
			else
				isMasked=MSK_NONE;
		}

		isLand=0;
		for (int i=2;i>=0;i--)
			if (p[i]) 
			{
				tsW[i]=1.f/float(p[i]->w);
				tsH[i]=1.f/float(p[i]->h);
				f++;
			}

//		if ( p[1] )
//			uniqueTextID = p[0]->hTextureMap + ((p[1]->hTextureMap<<11)&TIT_MASK_SECONDARY);
//		else
		uniqueTextID = p[0]->hTextureMap;
	}
}
HMATERIAL;

const HMATERIAL NULL_MATERIAL( UByte(0) ); // this can be used when a plain col is drawn using vertexcols or font colour
const HMATERIAL FONTCOL_MATERIAL( UByte(254) ); // this can be used when a plain col is drawn using vertexcols or font colour

inline ULong RGBMake(UByte r,UByte g,UByte b) { return (ULong(r)<<16)+(ULong(g)<<8)+ULong(b); }

//
// vertex structure that is equivalent to
// the D3DVERTEX struct with some overloaded 
// members added to match our DoPointStruc
//
typedef float D3DVALUE, *LPD3DVALUE;

class TextCoords
{
public:
	union {	SWord x;			D3DVALUE u; };		// the x texture coord
	union { SWord y;			D3DVALUE v; };		// the y texture coord  
};

typedef D3DVECTOR R3DVECTOR;

class R3DVERTEX
{
public:
//	typedef union INTFLOAT {D3DVALUE f; SLong i;} INTFLOAT;
			// untransformed	transformed

	union {	D3DVALUE x;			D3DVALUE sx; /*INTFLOAT bodyx;*/};	// xval    
	union {	D3DVALUE y;			D3DVALUE sy; /*INTFLOAT bodyy;*/};	// yval
	union {	D3DVALUE z;			D3DVALUE sz; /*INTFLOAT bodyz;*/};	// zval
	union { D3DVALUE nx;		D3DVALUE rhw; };			// normal x or reciprical of homegenized w
	union { D3DVALUE ny;		R3DCOLOUR color; };			// normal y or vertex col
	union {	D3DVALUE nz; 		R3DCOLOUR specular; };		// normal z or vertex specular
	union 
	{
		struct
		{
#pragma warning( disable : 4201)
			union {	SWord ix;			D3DVALUE tu; };		// the x texture coord
			union { SWord iy;			D3DVALUE tv; };		// the y texture coord  
		};
		TextCoords	t[1];									// will allow array indexing of textcoords
	};
//TEMPCODE JON 5/19/00 	R3DVERTEX& operator = ( const R3DVERTEX &source );
};

//TEMPCODE JON 5/18/00 #ifndef _R3DVERTEX_COPY_OPERATOR_DEFINED
//TEMPCODE JON 5/18/00 #define _R3DVERTEX_COPY_OPERATOR_DEFINED
//TEMPCODE JON 5/18/00 static R3DVERTEX& R3DVERTEX::operator = ( const R3DVERTEX &source ) // 1/2 save...
//TEMPCODE JON 5/18/00 {
//TEMPCODE JON 5/18/00 	memcpy( this, &source, sizeof( R3DVERTEX ) );
//TEMPCODE JON 5/18/00 	return *this;
//TEMPCODE JON 5/18/00 }
//TEMPCODE JON 5/18/00 #endif

class R3DVERTEX2 : public R3DVERTEX
{
public:
	union {D3DVALUE tu1; D3DVALUE dvTU1; SWord ix1;};     
	union {D3DVALUE tv1; D3DVALUE dvTV1; SWord iy1;}; 
};

class _R3DVERTEX3 : public R3DVERTEX2
{
public: // we will steal these 8 bytes as we never use 3 textures
	ULong pad0;
	ULong pad1;
//DeadCode JON 30Oct00 	ULong clipcode;			
//DeadCode JON 30Oct00 	UWord vertIndex;
//DeadCode JON 30Oct00 	UWord uploadPass;
//DeadCode JON 30Oct00 	union {D3DVALUE tu2; D3DVALUE dvTU2; SWord ix2;};     
//DeadCode JON 30Oct00 	union {D3DVALUE tv2; D3DVALUE dvTV2; SWord iy2;}; 
};

#ifndef _NO_VERTEX_SHARING_HDR

const UWord UNIQUE_DOPOINTNUM = 0x0000;
#endif

enum DoPointFlags
{
	ALL_INVALID			= 0x00000000,
	TEXTURE_COUNT1		= 1,//0x00000001, // used to count number of textures needed - comes later	//0
	TEXTURE_COUNT2		= 1<<1,//0x00000002, // used to count number of textures needed - comes later	//1
	LANDSCAPE_TEXTURE	= 1<<2,//0x00000004, // used to flag a landscape texture - comes later			//2
	WORLD_COORDS		= 1<<3,//0x00000008,															//3
	TEXTURE_COORDS		= 1<<4,//0x00000010,															//4
	TEXTURE1_COORDS		= 1<<5,//0x00000020,															//5
//DeadCode JON 30Oct00 	TEXTURE2_COORDS		= 1<<6,//0x00000040,															//6
	LIGHT_NORMAL		= 1<<6,//0x00000080,															//7
	DO_CLIP				= 1<<7,//0x00000100, // added in at a later stage.								//8
	DO_SW_FOG			= 1<<8,//0x00000200, // as above												//9
	ALL_VALID			= (WORLD_COORDS|TEXTURE_COORDS|TEXTURE1_COORDS/*|TEXTURE2_COORDS*/|LIGHT_NORMAL),
	TEXTURE_COUNT_MASK	= (TEXTURE_COUNT1|TEXTURE_COUNT2),
	ALL_TEXT_COORDS		= (TEXTURE_COORDS|TEXTURE1_COORDS/*|TEXTURE2_COORDS*/),

	PLAINCOL_FLAG		= 1<<31,		// used outside... - MUST be top bit...
//	PLAINCOLSHIFT		= 31-7,			// the right shift to go to the lightnormal pos
//	PLAINCOLTEXTSHIFT	= 31-4,			// the right shift to go to the textureflag...
//DeadCode JON 20Sep00 	LIGHTMODE_FLAG		= 1<<30,		// used outside...
//DeadCode JON 20Sep00 	LIGHTMODE_FLAG1		= 1<<29,		// used outside...
//DeadCode JON 20Sep00 	LIGHTMODE_FLAG2		= 1<<28,		// used outside...
//DeadCode JON 20Sep00 	
//DeadCode JON 20Sep00 	LIGHTMODE_MASK		= (LIGHTMODE_FLAG|LIGHTMODE_FLAG1|LIGHTMODE_FLAG2),
//DeadCode JON 20Sep00 	LIGHTMODE_NUM_SHIFT = 28,
//DeadCode JON 20Sep00 	LIGHTMODE_NUM_MASK	= (1<<2)+(1<<1)+1,
//DeadCode JON 20Sep00 	LIGHTMODESHIFT		= 30-7,			// the right shift needed to move from lightmode flag to LIGHT_NORMAL.
//DeadCode JON 20Sep00 	LIGHTMODESHIFT1		= 29-7,			// the right shift needed to move from lightmode flag to LIGHT_NORMAL.
//DeadCode JON 20Sep00 	LIGHTMODESHIFT2		= 28-7,			// the right shift needed to move from lightmode flag to LIGHT_NORMAL.
};

#ifndef _NO_VERTEX_SHARING_HDR
class DoPointManagment
{
private:
	union
	{
#pragma warning( disable : 4201)
		ULong flags;
		struct
		{
#pragma warning( disable : 4201)
			ULong	flagBits:9,
					lightModeCount:22, // ha ha my lazy cheat...
					plainColFlag:1;
		};
	};
	UWord doPointNum;
public:
	DoPointManagment( void ) // constructor - set as a unique point
	{
		setUnique();
	}

	UWord getDoPointNum( void ) const		{ return doPointNum; }
	void setDoPointNum(const UWord newVal)	{ doPointNum = newVal; }

	ULong getFlags( void ) const			{ return flags; }
	ULong getLightModeCount( void ) const		{ return lightModeCount; }
	void setLightModeCount( ULong val )		{ lightModeCount = val; }
	void setUnique( void )					{ memset( this, 0, sizeof(DoPointManagment) ); }//flags = ALL_INVALID; doPointNum = UNIQUE_DOPOINTNUM; }
	void setAllValid( void )				{ flagBits = ALL_VALID; }
	void setAllInvalid( void )				{ flags = ALL_INVALID; }
	bool isAllValid( void ) const			{ return flags==ALL_VALID; }
	void setInvalidWorld( void )			{ flags&=~WORLD_COORDS; }
	void setValidWorld( void )				{ flags|=WORLD_COORDS; }
	ULong isWorldValid( void ) const		{ return flags&WORLD_COORDS; }
	void setInvalidTexture( void )			{ flags&=~TEXTURE_COORDS; }
	ULong isTextureValid( void ) const		{ return flags&TEXTURE_COORDS; }
	void setInvalidTexture1( void )			{ flags&=~TEXTURE1_COORDS; }
	ULong isTexture1Valid( void ) const		{ return flags&TEXTURE1_COORDS; }
//DeadCode JON 30Oct00 	void setInvalidTexture2( void )			{ flags&=~TEXTURE2_COORDS; }
//DeadCode JON 30Oct00 	ULong isTexture2Valid( void ) const		{ return flags&TEXTURE2_COORDS; }
	void setInvalidNormal( void )			{ flags&=~LIGHT_NORMAL; }
	ULong isNormalValid( void ) const		{ return flags&LIGHT_NORMAL; }
	void addToFlags( const int i )			{ flags+= i; }
	void clearLightModeFlags( void )		{ lightModeCount = 0; }
//DeadCode JON 20Sep00 		flags&=~LIGHTMODE_MASK; }

};
#endif

class DoPointStruc : 
#ifndef _INSIDE_LIB3D_
	protected R3DVERTEX2
#else
	public R3DVERTEX2
#endif
{
public:
#ifndef _NO_VERTEX_SHARING_HDR
	// extra stuff for dopoints
	mutable DoPointManagment info;
	UWord uploadPass;// make the vertices of a sensible size
#endif

	DoPointStruc& operator = ( const DoPointStruc& source ) // copy operator... - copy constructor slightly quicker...
	{
		memcpy( this, &source, sizeof( R3DVERTEX2 ) );
#ifndef _NO_VERTEX_SHARING_HDR
		info.setAllInvalid();
#endif
		return *this;
	}
	
//DEADCODE JON 5/24/00 #pragma message ( __HERE__ "sort out this" )
//DEADCODE JON 5/24/00 	R3DVERTEX& operator + () {return *this;}					//RJS 19May00

	const R3DVERTEX2& getR3DVert() const { return *((R3DVERTEX2*)this); }

	// accessor functions
	void setPosition( const D3DVALUE newX, const D3DVALUE newY, const D3DVALUE newZ ) // set the physical position of the vertex
	{
		x = newX;
		y = newY;
		z = newZ;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidWorld();
#endif
	}
	void setPosition( const D3DVALUE newX, const D3DVALUE newY ) // set the phusical pos - sets z to 0 - use for 2d renders
	{
		x = newX;
		y = newY;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidWorld();
#endif
	}
	void getPosition( D3DVALUE &rx, D3DVALUE &ry, D3DVALUE &rz ) const
	{
		rx = x;
		ry = y;
		rz = z;
	}
	D3DVALUE getPosX( void ) const
	{
		return x;
	}
	D3DVALUE getPosY( void ) const
	{
		return y;
	}
	D3DVALUE getPosZ( void ) const
	{
		return z;
	}
	void setPosX( const D3DVALUE nx )
	{
		x = nx;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidWorld();
#endif
	}

	void setPosY( const D3DVALUE ny )
	{
		y = ny;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidWorld();
#endif
	}

	void setPosZ( const D3DVALUE nz )
	{
		z = nz;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidWorld();
#endif
	}

	void incPosX( const D3DVALUE offset )
	{
		x += offset;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidWorld();
#endif
	}

	void incPosY( const D3DVALUE offset )
	{
		y += offset;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidWorld();
#endif
	}

	void incPosZ( const D3DVALUE offset )
	{
		z += offset;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidWorld();
#endif
	}

	void incPos( const D3DVALUE xOff, const D3DVALUE yOff, const D3DVALUE zOff )
	{
		x+=xOff;
		y+=yOff;
		z+=zOff;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidWorld();
#endif
	}

	void setNormal( const R3DVECTOR& newVec )
	{
		memcpy( &nx, &newVec, sizeof( R3DVECTOR ) );
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidNormal();
#endif
	}

	void setNormal( const D3DVALUE newX, const D3DVALUE newY, const D3DVALUE newZ ) // set the normal vector on the vertex (used for lighting)
	{
		nx = newX;
		ny = newY;
		nz = newZ;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidNormal();
#endif
	}
	void setRHW( const D3DVALUE newrhw ) // for pre-transformed matrices
	{
		rhw = newrhw;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidNormal();
#endif
	}
	void getNormal( D3DVALUE &rx, D3DVALUE &ry, D3DVALUE &rz ) const
	{
		rx = nx;
		ry = ny;
		rz = nz;
	}
	void setVertexCol( const R3DCOLOUR newCol ) // set a colour on the vertex - cannot be used in conjunction with normal info
	{
		color = newCol;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidNormal();
#endif
	}

	void setVertexCol( const D3DCOLOR newCol ) // set a colour on the vertex - cannot be used in conjunction with normal info
	{
		color = newCol;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidNormal();
#endif
	}


	D3DVALUE getNormalX( void ) const
	{
		return nx;
	}
	D3DVALUE getNormalY( void ) const
	{
		return ny;
	}
	D3DVALUE getNormalZ( void ) const
	{
		return nz;
	}

//DeadCode JON 30Jun00 	R3DCOLOUR getVertexCol( void ) const // get a colour off a vertex - cannot be used in conjunction with normal info
//DeadCode JON 30Jun00 	{
//DeadCode JON 30Jun00 		return color;
//DeadCode JON 30Jun00 	}	

	D3DCOLOR getVertexCol( void ) const // get a colour off a vertex - cannot be used in conjunction with normal info
	{
		return ULong(color);
	}	


	void setIMapCoords( const SWord newX, const SWord newY ) // set the image map coords for 1st texture
	{
		ix = newX;
		iy = newY;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidTexture();
#endif
	}
	void getIMapCoords( SWord &rx, SWord &ry ) const
	{
		rx = ix;
		ry = iy;
	}
	SWord getIMapX( void  ) const
	{
		return ix;
	}
	SWord getIMapY( void  ) const
	{
		return iy;
	}
	void setIMapCoords1( const SWord newX, const SWord newY ) // set the image map coords for 2nd texture
	{
		ix1 = newX;
		iy1 = newY;
#ifndef _NO_VERTEX_SHARING_HDR
		info.setInvalidTexture1();
#endif
	}
	void getIMapCoords1( SWord &rx, SWord &ry ) const
	{
		rx = ix1;
		ry = iy1;
	}
	SWord getIMapX1( void  ) const
	{
		return ix1;
	}
	SWord getIMapY1( void  ) const
	{
		return iy1;
	}
//DeadCode JON 30Oct00 	void setIMapCoords2( const SWord newX, const SWord newY ) // set the image map coords for 3rd texture
//DeadCode JON 30Oct00 	{
//DeadCode JON 30Oct00 		ix2 = newX;
//DeadCode JON 30Oct00 		iy2 = newY;
//DeadCode JON 30Oct00 #ifndef _NO_VERTEX_SHARING_HDR
//DeadCode JON 30Oct00 		info.setInvalidTexture2();
//DeadCode JON 30Oct00 #endif
//DeadCode JON 30Oct00 	}
//DeadCode JON 30Oct00 	void getIMapCoords2( SWord &rx, SWord &ry ) const
//DeadCode JON 30Oct00 	{
//DeadCode JON 30Oct00 		rx = ix2;
//DeadCode JON 30Oct00 		ry = iy2;
//DeadCode JON 30Oct00 	}
//DeadCode JON 30Oct00 	SWord getIMapX2( void  ) const
//DeadCode JON 30Oct00 	{
//DeadCode JON 30Oct00 		return ix2;
//DeadCode JON 30Oct00 	}
//DeadCode JON 30Oct00 	SWord getIMapY2( void  ) const
//DeadCode JON 30Oct00 	{
//DeadCode JON 30Oct00 		return iy2;
//DeadCode JON 30Oct00 	}

};

class SVertex : public DoPointStruc
{
	friend class CLib3D;
public:
//DEADCODE JON 5/24/00 	union
//DEADCODE JON 5/24/00 	{
//DEADCODE JON 5/24/00 		R3DVERTEX3		r3dvert;
//DEADCODE JON 5/24/00 		R3DVERTEX		d3dtlvert;
//DEADCODE JON 5/24/00 		R3DVERTEX2		d3dtlvert2;
//DEADCODE JON 5/24/00 		R3DVERTEX3		d3dtlvert3; 
//DEADCODE JON 5/24/00 	};
	SVertex *pNext;			
#ifndef _NO_VERTEX_SHARING_HDR
	SVertex *identical;
#endif
	R3DMATRIX_VAL hw;	// the homegenous w
	ULong clipcode;			
	UWord vertIndex;
	static UWord copyCount;
	enum COUNTFLAGS
	{
		ODD_FRAME=1<<15,
		EVEN_FRAME=1<<14,
		FRAME_MASK=ODD_FRAME+EVEN_FRAME,
		COUNT_MASK=~FRAME_MASK
	};


	SVertex( void )	// constuctor
	{
#ifndef _NO_VERTEX_SHARING_HDR
		identical = NULL;
#endif
	}

	bool operator== (const SVertex& o) const // equivalence
	{
		return (
			x	==	o.x		&&
			y	==	o.y		&&
			z	==	o.z		&&
			nx	==	o.nx	&&
			ny	==	o.ny	&&
			nz	==	o.nz	&&
			tu	==	o.tu	&&
			tv	==	o.tv	&&
			tu1	==	o.tu1	&&
			tv1	==	o.tv1	&&
//DeadCode JON 30Oct00 			tu2	==	o.tu2	&&
//DeadCode JON 30Oct00 			tv2	==	o.tv2	&&
			hw	==	o.hw	);
	}
	
	bool operator!= ( const SVertex& o) const
	{
		return ( !(*this==o) );
	}

	SVertex& operator= ( const DoPointStruc& source ) // copy operator...
	{
		memcpy( this, &source, sizeof( DoPointStruc ) );
#ifndef _NO_VERTEX_SHARING_HDR
		source.info.setAllValid();
#endif
		return *this;
	}

	static void CountAndCopyReset( void )
	{
#ifndef _NO_VERTEX_SHARING_HDR
		//		copyCount = 0;
		if ( copyCount&ODD_FRAME ) // was the last frame odd or even?
		{ 
			copyCount=EVEN_FRAME;
		} else
		{
			copyCount=ODD_FRAME;
		}
#endif
	}

	void CountAndCopy( const DoPointStruc& source )
	{
#ifndef _NO_VERTEX_SHARING_HDR

		if ( !( source.info.getDoPointNum() & (copyCount&FRAME_MASK) ) )
		{ // this point hasn't been processed this frame
			source.info.setDoPointNum( ++copyCount );
			source.info.setAllInvalid();
		}
		memcpy( this, &source, sizeof( DoPointStruc ) );
		source.info.setAllValid();
		info.setDoPointNum( info.getDoPointNum()&COUNT_MASK );
#ifndef NDEBUG
		if ( copyCount == 1024 )
			INT3; // overrun the buffer...
#endif
#else
		memcpy( this, &source, sizeof( DoPointStruc ) );
#endif
	}

	void Transform( const R3DMATRIX* mat )
	{
//DEADCODE JON 5/24/00 		D3DVALUE x = r3dvert.x; // temporary store
//DEADCODE JON 5/24/00 		D3DVALUE y = r3dvert.y;
//DEADCODE JON 5/24/00 		D3DVALUE z = r3dvert.z;
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 		r3dvert.x	= mat->_11*x + mat->_21*y + mat->_31*z + mat->_41;
//DEADCODE JON 5/24/00 		r3dvert.y	= mat->_12*x + mat->_22*y + mat->_32*z + mat->_42;
//DEADCODE JON 5/24/00 		r3dvert.z	= mat->_13*x + mat->_23*y + mat->_33*z + mat->_43;
//DEADCODE JON 5/24/00 		hw			= mat->_14*x + mat->_24*y + mat->_34*z + mat->_44;
		R3DMATRIX_VAL tx = x; // temporary store
		R3DMATRIX_VAL ty = y;
		R3DMATRIX_VAL tz = z;

 		x	= mat->_11*tx + mat->_21*ty + mat->_31*tz + mat->_41;
		y	= mat->_12*tx + mat->_22*ty + mat->_32*tz + mat->_42;
		z	= mat->_13*tx + mat->_23*ty + mat->_33*tz + mat->_43;
		hw	= mat->_14*tx + mat->_24*ty + mat->_34*tz + mat->_44;
	}

	void VolumetricSphere( D3DVALUE& radius) // scale the point if it is the center of a sphere - the point should have been transformed by both the view and object matrices.
	{
		// Just bring the sphere forward by the radius...
		//...must be called after the vertex has been transformed to the viewer
//DEADCODE JON 5/24/00 		D3DVALUE	oldZ = r3dvert.z;
//DEADCODE JON 5/24/00 		r3dvert.z -= radius;
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 		D3DVALUE fudgeScale = r3dvert.z/oldZ;
//DEADCODE JON 5/24/00 		radius *= fudgeScale;
//DEADCODE JON 5/24/00 		r3dvert.x *= fudgeScale;
//DEADCODE JON 5/24/00 		r3dvert.y *= fudgeScale;

		D3DVALUE	oldZ = z;
		z -= radius;

		D3DVALUE fudgeScale = z/oldZ;
		radius *= fudgeScale;
		x *= fudgeScale;
		y *= fudgeScale;

	}

};

typedef SVertex Lib3DPoint;

typedef DWORD D3DCOLOR, *LPD3DCOLOR;

//DEADCODE JON 5/24/00 struct R3DTLVERTEX
//DEADCODE JON 5/24/00 {
//DEADCODE JON 5/24/00 	union {D3DVALUE sx; D3DVALUE dvSX;};
//DEADCODE JON 5/24/00 	union {D3DVALUE sy; D3DVALUE dvSY;};
//DEADCODE JON 5/24/00 	union {D3DVALUE sz; D3DVALUE dvSZ;};
//DEADCODE JON 5/24/00 	union {D3DVALUE rhw; D3DVALUE dvRHW;};
//DEADCODE JON 5/24/00 	union {D3DCOLOR color; D3DCOLOR dcColor;};
//DEADCODE JON 5/24/00 	union {D3DVALUE tu; D3DVALUE dvTU; SWord ix;};
//DEADCODE JON 5/24/00 	union {D3DVALUE tv; D3DVALUE dvTV; SWord iy;};
//DEADCODE JON 5/24/00 };
struct _DDCOLORKEY;
typedef _DDCOLORKEY DDCOLORKEY;
struct ROWANSURFACEDESC
{
	ULong	dwSize;
	ULong	dwFlags;
	ULong	dwHeight;
	ULong	dwWidth;
	union	{ULong	lPitch; ULong dwLinearSize;};
	ULong	dwBackBufferCount;
	union	{ULong dwMipMapCount; ULong dwRefreshRate;};
    ULong	dwAlphaBitDepth;
    ULong	dwReserved;
    void*	lpSurface;
	union	{DDCOLORKEY ddckCKDestOverlay; ULong dwEmptyFaceColor;};
    DDCOLORKEY    ddckCKDestBlt;
    DDCOLORKEY    ddckCKSrcOverlay;
    DDCOLORKEY    ddckCKSrcBlt;
    DDPIXELFORMAT ddpfPixelFormat;
    DDSCAPS2      ddsCaps;
	ULong	dwTextureStage;
};
struct UIDrivers
{
	ULong 	size;
	ULong 	numDrivers;

	struct UIDriver
	{
		SByte	name[MAX_TEXT_LENGTH];
		HDRIVER hDriver;
	}
	driver[MAX_DRIVERS];
};

struct UIModes
{
	ULong	size;
	ULong 	numModes;
	struct UIModeInfo
	{
		ULong width,height,bpp;
		HMODE hMode;
	}
	mode[MAX_MODES];
};

class LIB3D_API CLib3D 
{
public:
    //IUnknown methods
    virtual HRESULT	QueryInterface(REFIID,void**)=0;
    virtual ULong	AddRef()=0;
    virtual ULong	Release()=0;

	//Initialisation & configuration routines
	virtual HRESULT	Initialise(const HWND&, const ULong* sqrtTable)=0;
	virtual HRESULT	GetDrivers(UIDrivers&)=0;
	virtual HRESULT	GetModes(const HDRIVER&,UIModes&)=0;
	virtual HRESULT GetDefaultDriverAndMode(HDRIVER&,HMODE&)=0;

	virtual	HRESULT	SetDriverAndMode(const HDRIVER&,const HMODE&,const HWND&)=0;
	virtual HRESULT RestoreDisplayMode()=0;
	virtual HRESULT ChangeDisplaySettings(HWND,SWord,SWord,bool)=0;

	//2D interface methods
	virtual	HRESULT ScreenSwap()=0;
	virtual HRESULT SetPaletteTable(UByte*)=0;
	virtual HRESULT GetSurfaceDesc(ROWANSURFACEDESC*)=0;

	//3D interface methods
	virtual	HRESULT BeginScene(const HRENDERTARGET)=0;
	virtual HRESULT End3DScene()=0;
	virtual HRESULT EndScene()=0;
	virtual HRESULT ClearTargetZ()=0;

	virtual HRESULT PushMatrix(const HMATRIX&)=0;
	virtual HRESULT PopMatrix(const HMATRIX&)=0;
	virtual HRESULT SetMatrix(const HMATRIX&,const R3DMATRIX&)=0;
	virtual HRESULT GetMatrix(const HMATRIX&,R3DMATRIX&)=0;
	virtual HRESULT LoadIdentity(const HMATRIX&)=0;
	virtual HRESULT Rotate(const HMATRIX&,const HAXIS&,const Angles&)=0;
	virtual HRESULT Scale(const HMATRIX&,const D3DVALUE&)=0;
	virtual HRESULT Scale(const HMATRIX&,const D3DVECTOR&)=0;
	virtual HRESULT Translate(const HMATRIX&,const D3DVECTOR&)=0;
	virtual HRESULT BodyToScreen(const R3DVERTEX&,D3DVALUE&,D3DVALUE&,D3DVALUE&,D3DVALUE* distAtZ=NULL)=0;//RJS 07Feb00
	virtual HRESULT Transform(const HMATRIX&,DoPointStruc&)=0;
	virtual HRESULT BackProjectViewCone(COORDS3D*)=0;

	virtual HRESULT VisibleCheck(D3DVECTOR*,ULong,ULong*)=0;
	virtual HRESULT VisibleCheck(D3DVECTOR*,D3DVALUE*,ULong,ULong*)=0;
//DEADCODE JON 5/24/00 	virtual HRESULT VisibleCheck(R3DVERTEX*,ULong,ULong*)=0;
	virtual HRESULT VisibleCheck(DoPointStruc*,ULong,ULong*)=0;

	virtual HRESULT SetProjectionMatrix(const Angles& fov,const D3DVALUE& aspect,const D3DVALUE& zN,const D3DVALUE& zF,const bool noFogInScene = false)=0;
	virtual HRESULT SetProjectionMatrix(const Angles& fov,const D3DVALUE& zN,const D3DVALUE& zF,const bool noFogInScene = false)=0;	//JON 6Oct00
	virtual HRESULT SetFogColour(const ULong&)=0;
	virtual HRESULT SetFontColour(const ULong&)=0;
	virtual void	EnableFogging(bool)=0;


	virtual HRESULT SetAmbientLighting(LIGHTINGDESC)=0;
	virtual HRESULT SetObjectLighting(LIGHTFLAG&)=0;
	virtual HRESULT SetLightVector(D3DVALUE,D3DVALUE,D3DVALUE)=0;
	virtual	HRESULT GetMaxLandDotProduct(D3DVALUE&)=0;

	virtual HRESULT SetGlobal(const TOGGLES&,const ULong)=0; 
	virtual HRESULT SetGlobal(const TOGGLES&,ULong*)=0; 
	virtual HRESULT IncGlobal(const TOGGLES&)=0; 
	virtual HRESULT DecGlobal(const TOGGLES&)=0; 

	virtual	HRESULT CreateTexture(MAPDESC*,const TCFLAGS&)=0;
//DeadCode JON 17Sep00 	virtual HRESULT UploadTexture( const UWord&)=0;
	virtual HRESULT UploadTexture()=0;
	virtual HRESULT ReduceLandQuality(UWord& sourceTextIndex, UWord& destTextIndex )=0;	//JON 6/6/00


	virtual HRESULT AllocateLandscapeTextures()=0;
	virtual HRESULT FreeLandscapeTextures()=0;
	virtual HRESULT GetLandscapeTextureCount(SLong&,SLong&,SLong&,SLong&,
											SLong&,SLong&,SLong&,SLong&)=0;
	virtual HRESULT GetLandscapeTextureOnScreenMax(SLong&,SLong&,SLong&,SLong&,	//JON 31Jul00
											SLong&,SLong&,SLong&,SLong&)=0;

	virtual HRESULT	FreeLandscapeTexture(UWord)=0;
	virtual HRESULT	AllocateLandscapeTexture(UWord,UWord&)=0;

	virtual HRESULT SetMaterial(UWord,MAPDESC *pmap=NULL)=0; // set to use a landscape material
	virtual HRESULT SetMaterial(const HMATERIAL& mat)=0; // set to use a non landscape material

//DEADCODE JON 5/19/00 	virtual HRESULT BeginPoly(const ULong&,R3DVERTEX*&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT BeginPoly(const HMATERIAL&,const ULong&,R3DVERTEX*&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT BeginPoly(const HMATERIAL&,const ULong&,R3DTLVERTEX*&)=0;
	virtual Lib3DPoint* BeginPoly(const ULong&)=0; // assume the material is already set.
	virtual Lib3DPoint* BeginPoly( const HMATERIAL& mat, const ULong& vertexCount )=0;
	virtual HRESULT EndPoly()=0;

//DEADCODE JON 5/19/00 	virtual HRESULT BeginStrip(const ULong&,R3DVERTEX*&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT BeginStrip(const HMATERIAL&,const ULong&,R3DVERTEX*&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT BeginStrip(const HMATERIAL&,const ULong&,R3DTLVERTEX*&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT EndStrip()=0;

//DEADCODE JON 5/19/00 	virtual HRESULT BeginFan(const ULong&,R3DVERTEX*&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT BeginFan(const HMATERIAL&,const ULong&,R3DVERTEX*&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT BeginFan(const HMATERIAL&,const ULong&,R3DTLVERTEX*&)=0;
	virtual Lib3DPoint* BeginFan( const ULong& vertexCount )=0;
	virtual Lib3DPoint* BeginFan( const HMATERIAL& mat, const ULong& vertexCount )=0;
	virtual HRESULT EndFan()=0;

//DEADCODE JON 5/22/00 	virtual HRESULT DrawSphere(const HMATERIAL&,const R3DVERTEX&,const D3DVALUE&,const Angles,const SWord,const SWord,const SWord,const SWord)=0;
	virtual HRESULT DrawSphere(const HMATERIAL&,const DoPointStruc&,const D3DVALUE&,const Angles,const SWord,const SWord,const SWord,const SWord)=0;
	virtual HRESULT DrawTransformedSphere(const HMATERIAL&,const DoPointStruc&,const D3DVALUE&,const Angles,const SWord,const SWord,const SWord,const SWord)=0;//RJS 20Mar00
//DEADCODE JON 5/22/00 	virtual HRESULT DrawLine(const HMATERIAL&,const R3DVERTEX&,const R3DVERTEX&)=0;
//DEADCODE JON 5/19/00 	virtual HRESULT DrawLine(const HMATERIAL&,const R3DTLVERTEX&,const R3DTLVERTEX&)=0;
	virtual HRESULT DrawLine(const HMATERIAL&,const DoPointStruc&,const DoPointStruc&)=0;	
	virtual HRESULT DrawTransformedLine(const HMATERIAL&,const DoPointStruc&,const DoPointStruc&)=0;	
	
//DeadCode JON 19Oct00 	virtual HRESULT DrawPoint(const HMATERIAL&,const DoPointStruc&)=0;

	virtual HRESULT	GiveHint(const HINTS&)=0;

//DEADCODE JON 5/22/00 	virtual HRESULT DrawCylinder(const HMATERIAL&,const R3DVERTEX&,const R3DVERTEX&,
//DEADCODE JON 5/22/00 								const D3DVALUE&,const SWord,const SWord,const SWord,const SWord)=0;//RJS 14Feb00
	virtual HRESULT DrawCylinder(const HMATERIAL&,const DoPointStruc&,const DoPointStruc&,
								const D3DVALUE&,const SWord,const SWord,const SWord,const SWord)=0;//RJS 14Feb00
	virtual	HRESULT CylinderOffsets(const DoPointStruc&,const DoPointStruc&,const D3DVALUE&,D3DVALUE&,D3DVALUE&,DoPointStruc&)=0;
	virtual	HRESULT DrawTransformedCylinder(const HMATERIAL&,const DoPointStruc&,const DoPointStruc&,const D3DVALUE&,const D3DVALUE&,const D3DVALUE&,const D3DVALUE&,const SWord,const SWord,const SWord,const SWord)=0;

	virtual HRESULT TestPoly(const HMATERIAL&)=0;
	virtual HRESULT UnloadTexture( MAPDESC* )=0;
	virtual HRESULT LoadBMP(UByte*)=0;
	virtual void	SetFogValues( const D3DVALUE& FogStart, const D3DVALUE& FogEnd )=0;

	virtual	void	GivePolyCount(int&)=0;						//RJS 23Mar00
	virtual	void	GetTextureRAM(ULong&)=0;					//RJS 24Mar00
	virtual ULong	GetFreeVideoMemory()=0;										//JON 10Jul00

	virtual	HRESULT DoFade( D3DCOLOR fadeCol, UByte fadeDepth )=0;			//JON 4/11/00
	virtual	HRESULT DoWhiteOut( const D3DCOLOR&, const UByte&, const D3DVALUE&,  const D3DVALUE&, const D3DVALUE&)=0;//RJS 20Apr00

	virtual	HRESULT FlushAsBackground( void )=0;							//JON 4/19/00
	virtual	HRESULT GetZDepth( ULong& )=0;									//RJS 3/5/00
	virtual int ScreenShot( BITMAPINFOHEADER* pFile,void* imagebuffer=NULL )=0;//returns output data size

	virtual HRESULT DrawQuadSphere(const HMATERIAL&,const DoPointStruc&,const D3DVALUE&,const Angles,const SWord,const SWord,const SWord,const SWord)=0;//RJS 06Jun00
	virtual HRESULT DrawPivotedSphere(const HMATERIAL&,const DoPointStruc&,const D3DVALUE&,const Angles,const SWord,const SWord,const SWord,const SWord)=0;//RJS 06Jun00

	virtual HRESULT SetMirrorTexture( const HMATERIAL& )=0;						//JON 3Jul00
//DeadCode JON 17Sep00 	HRESULT UploadMirror( void )
//DeadCode JON 17Sep00 	{
//DeadCode JON 17Sep00 		return UploadTexture( /*0*/ );
//DeadCode JON 17Sep00 	}

	virtual HRESULT Wipe( const D3DCOLOR )=0;							//JON 4Jul00

	virtual HRESULT SetGamma( double gammaAmount )=0;					//JON 12Jul00
	virtual HRESULT SetGammaLevel( ULong val )=0;						//JON 12Jul00
	virtual HRESULT UploadAsDitherTexture( MAPDESC *pmap )=0;						//JON 26Jul00
	virtual HRESULT UploadAsMipMapLevel( MAPDESC *destination, MAPDESC *source, int level )=0;		//JON 8Aug00

	virtual void GetDiagnosticString( char* &theString )=0;						//JON 22Aug00

	virtual HRESULT SetNearClipPlane( D3DVALUE dist )=0;								//JON 29Aug00
	virtual HRESULT SetFarClipPlane( D3DVALUE dist )=0;									//JON 29Aug00
	virtual void	SetMasterShading( LIGHTFLAG& lf )=0;							//JON 29Sep00

	virtual HRESULT	DrawPoint( const HMATERIAL&, const DoPointStruc& )=0;				//JON 19Oct00
	virtual HRESULT	DrawTransformedPoint( const HMATERIAL&, const DoPointStruc& )=0;	//JON 19Oct00
	virtual void GetViewPortDimensions( D3DVALUE &sx, D3DVALUE &sy, D3DVALUE &cx, D3DVALUE &cy ) = 0;	//JON 19Oct00
	virtual void ResetClipDistances( void ) = 0;						//JON 23Oct00

	virtual void GetTransformedLightColour( R3DVERTEX& vertex, const LIGHTFLAG lf ) = 0;	//JON 7Nov00
};

LIB3D_API CLib3D *Lib3DCreate(const GUID);

#endif	//LIB3D_Included

#ifdef	INITGUID	
#ifndef warnmsg
	#define _XSTR(x)         #x
	#define TOSTR(x)        _XSTR(x)

	#define __HERE__	__FILE__ "(" TOSTR(__LINE__) "): "
	#define	warnmsg(text)	message(__HERE__ "                 " text)
#endif
#pragma warnmsg("defining GUIDs")
#endif
DEFINE_GUID(IID_ILib3D,0x11038561, 0x95e1, 0x11d3, 0x87, 0x95, 0x0, 0x40, 0x5, 0x2c, 0x1f, 0x45);
