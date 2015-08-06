//------------------------------------------------------------------------------
//Filename       fastmath.h
//System         
//Author         Paul.   
//Date           Mon 8 Nov 1999
//Description    
//------------------------------------------------------------------------------
#ifndef	FASTMATH_Included
#define	FASTMATH_Included

#include <d3dtypes.h>

#define	DEFAULT_FASTMATH 0

#define NUMBITS (sizeof(ULong)*8)
//
// Get the integral form of a float
//
#define FP_BITS(fp) (*(ULong*)&(fp))
//
// Get the absolute value for a float in integral form
//
#define FP_ABS_BITS(fp) (FP_BITS(fp)&~(1<<(NUMBITS-1)))
#define FP_ABS_BITS2(x) ((x)&~(1<<(NUMBITS-1)))
//
// Get the sign bit of a float
//
#define FP_SIGN_BIT(fp) (FP_BITS(fp)&(1<<(NUMBITS-1)))
//
// Get the sign bit of a float in integral form as 0 or 1
//
#define FP_SIGN_BIT2(x) (ULong(x)>>(NUMBITS-1))
//
// Bit pattern for 1.0f
//
#define FP_ONE_BITS 0x3F800000

const double _23_BASE_ADD = 8388608.;	//2^23
const double _52_BASE_ADD = (1024. * 1024. * 1024. * 1024. * 1024. * 4.); //2^52

class FastMath
{
	union
	{
		mutable float in_f;
		ULong out_l;
	};

	union
	{
		mutable double 	in_d;
		ULong	out_dl[2];
	};

public:																	//JON 13Oct00
	static ULong fastSqrtTable[0x10000];
private:
	static SWord tableCode2[257];										//JIM 08/06/00
	static SWord tableCode1[65536];
	typedef union FastSqrtUnion
	{
		R3DVALUE 	f;
		ULong		i;
	}
	FastSqrtUnion;

	R3DVALUE fpSqrt(R3DVALUE num) const
	{
    	__asm	fld 	num;
		__asm	fsqrt;
		__asm	fstp	num;
		return num;
	}

	void BuildSqrtTable()
	{
		ULong i;
		FastSqrtUnion s;
		for (i=0;i<=0x7FFF;i++)
		{
		    // Build a float with the bit pattern i as mantissa
    		// and an exponent of 0, stored as 127
    	    s.i=(i<<8)|(0x7F<<23);
    		s.f=(R3DVALUE)fpSqrt(s.f);
    
		    // Take the square root then strip the first 7 bits of
    		// the mantissa into the table
     		fastSqrtTable[i+0x8000]=(s.i&0x7FFFFF);
    
    		// Repeat the process, this time with an exponent of 1, 
    		// stored as 128
		    s.i=(i<<8)|(0x80<<23);
    		s.f=(R3DVALUE)fpSqrt(s.f);
		    fastSqrtTable[i]=(s.i&0x7FFFFF);
		}
		//
		// not very efficient but only done once
		//
		for (SLong x=0;x<=256;x++)
		{
			R3DVALUE square=R3DVALUE(x);
			square*=square;
			square+=65536.0f;
			square=FastSqrt(square);
			tableCode2[x]=(SWord)square;
		}
		for (x=0;x<256;x++)
			for (SLong z=0;z<256;z++)
			{
				R3DVALUE square=R3DVALUE(x)*R3DVALUE(x)+R3DVALUE(z)*R3DVALUE(z);
				square=FastSqrt(square);
				tableCode1[(x<<8)+z]=(SWord)square;
			}
	}
public:
	FastMath() {BuildSqrtTable();}
	//
	// Approximate but fast 'r=1/p'
	//
	inline R3DVALUE FPInv(const R3DVALUE p) const
	{
		SLong i=2*FP_ONE_BITS-*(SLong*)&p;
	    R3DVALUE r=*(R3DVALUE*)&i;
    	return r*(2.0f-p*r);
	}
	//
	// Fast normal value to byte 
	//
	inline SLong FPNormToByte(const R3DVALUE p) const
	{
	 	R3DVALUE n=p+1.0f;
		SLong i=*(SLong*)&n;
		if (i>=0x40000000)		i=0xFF;
		else if (i<=0x3F800000)	i=0;
		else 					i=(i>>15)&0xFF;
		return i;
	}
	//
	// Fast floating point square root calc
	//
	inline R3DVALUE FastSqrt(R3DVALUE n) const
	{
	 	//Check for sqrt(0)
		if (FP_BITS(n)==0)
			return 0.0f;

		FP_BITS(n)=fastSqrtTable[(FP_BITS(n)>>8)&0xFFFF]|
			((((FP_BITS(n)-0x3F800000)>>1)+0x3F800000)&0x7F800000);

		return n;
	}
	//
	// Fast 2d length calculation for landscape
	//
	inline SWord FastLen(SWord dx,SWord dz)
	{
		if (dx<0) dx=-dx;
		if (dz<0) dz=-dz;
		if (dx==0x100)		return tableCode2[dz];
		else if (dz==0x100)	return tableCode2[dx];
		return tableCode1[(dx<<8)+dz];
	}
	//
	// Fast floating point inverse square root calc
	//
	inline R3DVALUE FastInvSqrt(R3DVALUE n) const
	{
	 	//Check for inv sqrt(0)
		if (FP_BITS(n)==0)
			return 0.0f;
		
		FP_BITS(n)=fastSqrtTable[(FP_BITS(n)>>8)&0xFFFF]|
			((((FP_BITS(n)-0x3F800000)>>1)+0x3F800000)&0x7F800000);
		
		SLong i=2*FP_ONE_BITS-*(SLong*)&n;

		R3DVALUE r=*(R3DVALUE*)&i;

		return r*(2.0f-n*r);
	}
	//
	// Fast floating point to integer conversion
	//
	inline void FloatToInt(SLong *int_pointer,R3DVALUE f) const
	{
	 	__asm	fld		f;
		__asm	mov		edx,int_pointer;
		__asm	frndint;
		__asm	fistp	dword ptr [edx];
	}
	//
	// Fast outcode calc
	//
	inline ULong FastClipTest(const R3DVALUE *v) const
	{
		ULong iwxyz,abs_w;
		ULong diff,t;
		ULong outcode;

		iwxyz=FP_BITS(v[3]);
		abs_w=FP_ABS_BITS2(iwxyz);
		outcode=FP_SIGN_BIT2(iwxyz);

		iwxyz=FP_BITS(v[0]);
		diff=FP_SIGN_BIT2(abs_w-FP_ABS_BITS2(iwxyz));
		t=FP_SIGN_BIT2(iwxyz)+1;
		outcode|=diff<<t;

		iwxyz=FP_BITS(v[1]);
		diff=FP_SIGN_BIT2(abs_w-FP_ABS_BITS2(iwxyz));
		t=FP_SIGN_BIT2(iwxyz)+3;
		outcode|=diff<<t;

		iwxyz=FP_BITS(v[2]);
		diff=FP_SIGN_BIT2(abs_w-FP_ABS_BITS2(iwxyz));
		t=FP_SIGN_BIT2(iwxyz)+5;
		outcode|=diff<<t;

		return outcode;
	}

	//
	// Fast clipped floating point to UByte conversion
	//
	inline UByte FloatToUByte(const float& f) const
	{
		in_f = f + _23_BASE_ADD;
		if ( (out_l&0xFFFFFF00) != (0x4B000000) )
			return (255-(out_l>>16))&0xFF;
	
		return out_l&0xFF;
	}

	//
	// Fast rounded floating point to ULong conversion
	//
	inline ULong DoubleToULong(const double& f) const
	{
		in_d = f + _52_BASE_ADD;

		return out_dl[0];
	}

};

extern FastMath fastMath;

#endif
