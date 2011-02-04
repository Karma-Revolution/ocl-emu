/* ============================================================

Copyright (c) 2010 Advanced Micro Devices, Inc.  All rights reserved.

Redistribution and use of this material is permitted under the following 
conditions:

Redistributions must retain the above copyright notice and all terms of this 
license.

In no event shall anyone redistributing or accessing or using this material 
commence or participate in any arbitration or legal action relating to this 
material against Advanced Micro Devices, Inc. or any copyright holders or 
contributors. The foregoing shall survive any expiration or termination of 
this license or any agreement or access or use related to this material. 

ANY BREACH OF ANY TERM OF THIS LICENSE SHALL RESULT IN THE IMMEDIATE REVOCATION 
OF ALL RIGHTS TO REDISTRIBUTE, ACCESS OR USE THIS MATERIAL.

THIS MATERIAL IS PROVIDED BY ADVANCED MICRO DEVICES, INC. AND ANY COPYRIGHT 
HOLDERS AND CONTRIBUTORS "AS IS" IN ITS CURRENT CONDITION AND WITHOUT ANY 
REPRESENTATIONS, GUARANTEE, OR WARRANTY OF ANY KIND OR IN ANY WAY RELATED TO 
SUPPORT, INDEMNITY, ERROR FREE OR UNINTERRUPTED OPERA TION, OR THAT IT IS FREE 
FROM DEFECTS OR VIRUSES.  ALL OBLIGATIONS ARE HEREBY DISCLAIMED - WHETHER 
EXPRESS, IMPLIED, OR STATUTORY - INCLUDING, BUT NOT LIMITED TO, ANY IMPLIED 
WARRANTIES OF TITLE, MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, 
ACCURACY, COMPLETENESS, OPERABILITY, QUALITY OF SERVICE, OR NON-INFRINGEMENT. 
IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. OR ANY COPYRIGHT HOLDERS OR 
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, PUNITIVE,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, REVENUE, DATA, OR PROFITS; OR 
BUSINESS INTERRUPTION) HOWEVER CAUSED OR BASED ON ANY THEORY OF LIABILITY 
ARISING IN ANY WAY RELATED TO THIS MATERIAL, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE. THE ENTIRE AND AGGREGATE LIABILITY OF ADVANCED MICRO DEVICES, 
INC. AND ANY COPYRIGHT HOLDERS AND CONTRIBUTORS SHALL NOT EXCEED TEN DOLLARS 
(US $10.00). ANYONE REDISTRIBUTING OR ACCESSING OR USING THIS MATERIAL ACCEPTS 
THIS ALLOCATION OF RISK AND AGREES TO RELEASE ADVANCED MICRO DEVICES, INC. AND 
ANY COPYRIGHT HOLDERS AND CONTRIBUTORS FROM ANY AND ALL LIABILITIES, 
OBLIGATIONS, CLAIMS, OR DEMANDS IN EXCESS OF TEN DOLLARS (US $10.00). THE 
FOREGOING ARE ESSENTIAL TERMS OF THIS LICENSE AND, IF ANY OF THESE TERMS ARE 
CONSTRUED AS UNENFORCEABLE, FAIL IN ESSENTIAL PURPOSE, OR BECOME VOID OR 
DETRIMENTAL TO ADVANCED MICRO DEVICES, INC. OR ANY COPYRIGHT HOLDERS OR 
CONTRIBUTORS FOR ANY REASON, THEN ALL RIGHTS TO REDISTRIBUTE, ACCESS OR USE 
THIS MATERIAL SHALL TERMINATE IMMEDIATELY. MOREOVER, THE FOREGOING SHALL 
SURVIVE ANY EXPIRATION OR TERMINATION OF THIS LICENSE OR ANY AGREEMENT OR 
ACCESS OR USE RELATED TO THIS MATERIAL.

NOTICE IS HEREBY PROVIDED, AND BY REDISTRIBUTING OR ACCESSING OR USING THIS 
MATERIAL SUCH NOTICE IS ACKNOWLEDGED, THAT THIS MATERIAL MAY BE SUBJECT TO 
RESTRICTIONS UNDER THE LAWS AND REGULATIONS OF THE UNITED STATES OR OTHER 
COUNTRIES, WHICH INCLUDE BUT ARE NOT LIMITED TO, U.S. EXPORT CONTROL LAWS SUCH 
AS THE EXPORT ADMINISTRATION REGULATIONS AND NATIONAL SECURITY CONTROLS AS 
DEFINED THEREUNDER, AS WELL AS STATE DEPARTMENT CONTROLS UNDER THE U.S. 
MUNITIONS LIST. THIS MATERIAL MAY NOT BE USED, RELEASED, TRANSFERRED, IMPORTED,
EXPORTED AND/OR RE-EXPORTED IN ANY MANNER PROHIBITED UNDER ANY APPLICABLE LAWS, 
INCLUDING U.S. EXPORT CONTROL LAWS REGARDING SPECIFICALLY DESIGNATED PERSONS, 
COUNTRIES AND NATIONALS OF COUNTRIES SUBJECT TO NATIONAL SECURITY CONTROLS. 
MOREOVER, THE FOREGOING SHALL SURVIVE ANY EXPIRATION OR TERMINATION OF ANY 
LICENSE OR AGREEMENT OR ACCESS OR USE RELATED TO THIS MATERIAL.

NOTICE REGARDING THE U.S. GOVERNMENT AND DOD AGENCIES: This material is 
provided with "RESTRICTED RIGHTS" and/or "LIMITED RIGHTS" as applicable to 
computer software and technical data, respectively. Use, duplication, 
distribution or disclosure by the U.S. Government and/or DOD agencies is 
subject to the full extent of restrictions in all applicable regulations, 
including those found at FAR52.227 and DFARS252.227 et seq. and any successor 
regulations thereof. Use of this material by the U.S. Government and/or DOD 
agencies is acknowledgment of the proprietary rights of any copyright holders 
and contributors, including those of Advanced Micro Devices, Inc., as well as 
the provisions of FAR52.227-14 through 23 regarding privately developed and/or 
commercial computer software.

This license forms the entire agreement regarding the subject matter hereof and 
supersedes all proposals and prior discussions and writings between the parties 
with respect thereto. This license does not affect any ownership, rights, title,
or interest in, or relating to, this material. No terms of this license can be 
modified or waived, and no breach of this license can be excused, unless done 
so in a writing signed by all affected parties. Each term of this license is 
separately enforceable. If any term of this license is determined to be or 
becomes unenforceable or illegal, such term shall be reformed to the minimum 
extent necessary in order for this license to remain in effect in accordance 
with its terms as modified by such reformation. This license shall be governed 
by and construed in accordance with the laws of the State of Texas without 
regard to rules on conflicts of law of any state or jurisdiction or the United 
Nations Convention on the International Sale of Goods. All disputes arising out 
of this license shall be subject to the jurisdiction of the federal and state 
courts in Austin, Texas, and all defenses are hereby waived concerning personal 
jurisdiction and venue of these courts.

============================================================ */


#ifndef _MATHFUNCTIONS_HCLL_
#define _MATHFUNCTIONS_HCLL_

#define _SCHAR_MAX              127
#define _SCHAR_MIN              (-1)+(-127)
#define _SCHAR_SIGN             0x80
#define _SCHAR_BITMASK          0x7f
#define _SCHAR_BITS             7
#define _SCHAR_MSB_BITS         0x40
#define _CHAR_MAXBITS           8
#define _CHAR_MAX               _SCHAR_MAX
#define _CHAR_MIN               _SCHAR_MIN
#define _UCHAR_MAX              255
#define _UCHAR_MIN              0
#define _UCHAR_BITMASK          0xff
#define _UCHAR_BITS             8 
#define _UCHAR_MAXBITS          8
#define _UCHAR_MSB_BIT         0x80
#define _SHRT_MAX               SHRT_MAX
#define _SHRT_MIN               SHRT_MIN
#define _SHRT_SIGN              0x8000
#define _SHRT_BITMASK           0x7fff
#define _SHRT_BITS              15
#define _SHRT_MAXBITS           16
#define _SHRT_MSB_BITS          0x4000
#define _USHRT_MAX              USHRT_MAX
#define _USHRT_MIN              0
#define _USHRT_BITMASK          USHRT_MAX
#define _USHRT_BITS             16
#define _USHRT_MAXBITS          16
#define _USHRT_MSB_BIT         0x8000
#define _INT_MAX                INT_MAX
#define _INT_MIN                INT_MIN
#define _INT_MAX64              0x7fffffffULL
#define _INT_MIN64              0xffffffff80000001LL
#define _INT_SIGN               0x80000000
#define _INT_BITMASK            0x7fffffff
#define _INT_BITS               31
#define _INT_MAXBITS            32
#define _INT_MSB_BITS           0x40000000
#define _UINT_MAX               UINT_MAX
#define _UINT_MIN               0
#define _UINT_BITMASK           UINT_MAX
#define _UINT_BITS              32
#define _UINT_MAXBITS           32
#define _UINT_MSB_BIT          0x80000000

#ifndef LLONG_MAX
#define LLONG_MAX     9223372036854775807ULL       /* maximum signed __LONG __LONG int value */
#define LLONG_MIN   (-9223372036854775807LL - 1)  /* minimum signed __LONG __LONG int value */
#define ULLONG_MAX    0xffffffffffffffffULL       /* maximum unsigned __LONG __LONG int value */
#endif

#define _LONG_MAX              LLONG_MAX
#define _LONG_MIN              LLONG_MIN
#define _LONG_SIGN             0x8000000000000000ULL
#define _LONG_BITMASK          0x7fffffffffffffffLL
#define _LONG_BITS                      63
#define _LONG_MAXBITS                   64
#define _LONG_MSB_BITS         0x4000000000000000LL
#define _ULONG_MAX             0xffffffffffffffffULL
#define _ULONG_MIN             0
#define _ULONG_BITMASK         0xffffffffffffffffULL
#define _ULONG_BITS                      64
#define _ULONG_MAXBITS                   64
#define _ULONG_MSB_BITS        0x8000000000000000ULL

#define _CL_MAX(x, y) ((x) > (y))? (x) : (y)
#define _CL_MIN(x, y) ((x) < (y))? (x) : (y)


#define SIGNBIT_DP64      0x8000000000000000ULL
#define EXPBITS_DP64      0x7ff0000000000000ULL
#define MANTBITS_DP64     0x000fffffffffffffULL
#define ONEEXPBITS_DP64   0x3ff0000000000000ULL
#define TWOEXPBITS_DP64   0x4000000000000000ULL
#define HALFEXPBITS_DP64  0x3fe0000000000000ULL
#define IMPBIT_DP64       0x0010000000000000ULL
#define QNANBITPATT_DP64  0x7ff8000000000000ULL
#define INDEFBITPATT_DP64 0xfff8000000000000ULL
#define PINFBITPATT_DP64  0x7ff0000000000000ULL
#define NINFBITPATT_DP64  0xfff0000000000000ULL
#define EXPBIAS_DP64      1023
#define EXPSHIFTBITS_DP64 52
#define BIASEDEMIN_DP64   1
#define EMIN_DP64         -1022
#define BIASEDEMAX_DP64   2046
#define EMAX_DP64         1023
#define LAMBDA_DP64       1.0e300
#define MANTLENGTH_DP64   53
#define BASEDIGITS_DP64   15

/* These definitions, used by float functions,
   are for both 32 and 64 bit machines */
#define SIGNBIT_SP32      0x80000000U
#define EXPBITS_SP32      0x7f800000U
#define MANTBITS_SP32     0x007fffffU
#define ONEEXPBITS_SP32   0x3f800000U
#define TWOEXPBITS_SP32   0x40000000U
#define HALFEXPBITS_SP32  0x3f000000U
#define IMPBIT_SP32       0x00800000U
#define QNANBITPATT_SP32  0x7fc00000U
#define INDEFBITPATT_SP32 0xffc00000U
#define PINFBITPATT_SP32  0x7f800000U
#define NINFBITPATT_SP32  0xff800000U
#define EXPBIAS_SP32      127
#define EXPSHIFTBITS_SP32 23
#define BIASEDEMIN_SP32   1
#define EMIN_SP32         -126
#define BIASEDEMAX_SP32   254
#define EMAX_SP32         127
#define LAMBDA_SP32       1.0e30
#define MANTLENGTH_SP32   24
#define BASEDIGITS_SP32   7
//static double CLEMU_PI = 3.14159265358979323846;
#ifndef M_PI
    #define M_PI    3.14159265358979323846264338327950288
#endif

#ifndef M_PI_4
    #define M_PI_4 (M_PI/4)
#endif

#define EVALUATE( x )       x
#define CONCATENATE(x, y)  x ## EVALUATE(y)



//#ifndef islessgreater
    // Note: Non-C99 conformant. This will trigger floating point exceptions. We don't care about that here.
//    #define islessgreater( _x, _y )     ( (_x) < (_y) || (_x) > (_y) )
//#endif

//#define infnan(x)  ( sizeof (x) == sizeof(float )	?	as_float(QNANBITPATT_SP32)  	\
//                        : as_double(QNANBITPATT_DP64))


float as_float( uint _A);
double as_double( __int64 _A);

// Declare Classification macros for non-C99 platforms

inline int isinf(float x) 
{
float INFINITY = as_float(PINFBITPATT_SP32);
   return(fabsf(x) == INFINITY);
}  	
inline int isinf(double x) 
{
double DBL_INFINITY = as_double(PINFBITPATT_DP64);
    return( fabs(x) == DBL_INFINITY);
}

inline int isfinite(float x)
{ 
float INFINITY = as_float(PINFBITPATT_SP32);
   return(fabsf(x) < INFINITY);
}
inline int isfinite(double x)
{ 
double DBL_INFINITY = as_double(PINFBITPATT_DP64);
   return(fabs(x) < DBL_INFINITY);
}

inline int isnan(float _a)
{
    return(( (_a) != (_a) ));
}
inline int isnan(double _a)
{
    return(( (_a) != (_a) ));
}


inline int isnormal(float x)
{
float INFINITY = as_float(PINFBITPATT_SP32);
   return(fabsf(x) < INFINITY && fabsf(x) >= FLT_MIN);
}
inline int isnormal(double x)
{
double DBL_INFINITY = as_double(PINFBITPATT_DP64);
   return(fabs(x) < DBL_INFINITY && fabs(x) >= DBL_MIN);
}


static int
finite(double x )
{
  return((int)isfinite(x));
}

static int
finite(float x )
{
  return((int)isfinite(x));
}


int
static isMSBset( char x )
{
int r = 0;
    r = (x & _UCHAR_MSB_BIT) ? 1 : 0;
	return(r);
}

int
static isMSBset( uchar x )
{
int r = 0;
    r = (x & _UCHAR_MSB_BIT) ? 1 : 0;
	return(r);
}


int 
static isMSBset( short x )
{
int r = 0;
    r = (x & _USHRT_MSB_BIT)? 1 : 0;
	return(r);
}

int 
static isMSBset( ushort x )
{
int r = 0;
    r = (x & _USHRT_MSB_BIT)? 1 : 0;
	return(r);
}

int 
static isMSBset( int x )
{
int r = 0;
    r = (x & _UINT_MSB_BIT)? 1 : 0;
	return(r);
}

int 
static isMSBset( uint x )
{
int r = 0;
    r = (x & _UINT_MSB_BIT)? 1 : 0;
	return(r);
}


inline float asfloat( int _A)
{
	return (*(float*)&_A);
}

inline float as_float( int _A)
{
	return (asfloat(_A));
}

inline float asfloat( uint _A)
{
	return (*(float*)&_A);
}


static float as_float( uint _A)
{
	return (asfloat(_A));
}

static int asint( float _A)
{
	return (*(int*)&_A);
}

static double as_double( __int64 _A)
{
	return (*(double*)(&_A));
}

static double as_double( unsigned __int64 _A)
{
	return (*(double*)(&_A));
}


inline int as_int( float _A)
{
	return (*(int*)&_A);
}


inline uint as_uint( float _A)
{
	return (*(uint*)&_A);
}

inline int as_int( uint _A)
{
	return ((int)_A);
}


inline uint as_uint( int _A)
{
	return ((uint)_A);
}



inline int sign( float _A)
{
    return ((_A > 0) ? 1 : (_A < 0) ? -1 : 0);
}

inline int sign( double _A)
{
    return ((_A > 0) ? 1 : (_A < 0) ? -1 : 0);
}


static float mmfFREXP( float x, int * expon)
{
float ret = 0;
float abs_x = abs(x);
int in_exp = as_int(abs_x) & 0x7f800000;
int in_mant = as_int(abs_x) & 0x007fffff;
// make mantissa into 0.5:
    in_mant |= 0x3f000000;
// remove bias + 1
	in_exp += 0xc1000000;
// shift into low bits
	in_exp >>= 23;
	ret = ( x < 0) ? -as_float(in_mant) : as_float(in_mant);
	*expon = in_exp;
    return(ret);
}



static int
clCntZeros16f( uint x )
{
int r = _USHRT_MAXBITS;
   x &= _USHRT_BITMASK;
   if ( x  )
   {
// use float normalization hw for bit counting
float t = as_float( ONEEXPBITS_SP32 | x );
      t -= 1.f;
uint it_exp = (as_int(t) &  EXPBITS_SP32);
uint tr = (((ONEEXPBITS_SP32 - it_exp) & EXPBITS_SP32) >> EXPSHIFTBITS_SP32);
// 1 is from normalized float
// 23 - 16 =7 + 1 = 8
      r = tr - 8;
   }
   return (r);
}

static int
clCntZeros23f( uint x, int max_bits )
{
int r = max_bits;

   {
// use float normalization hw for bit counting
float t = as_float( ONEEXPBITS_SP32 | x );
      t -= 1.f;
uint it_exp = (as_int(t) &  EXPBITS_SP32);
uint tr = (((ONEEXPBITS_SP32 - it_exp) & EXPBITS_SP32) >> EXPSHIFTBITS_SP32);

      r = tr - (23 - max_bits);
   }
   r = ( x == 0 ) ? max_bits : r;
   return (r);
}


static int
clCntZeros32f( uint x )
{
int r, r0, r1;
uint x_half = (x >> 16);
   r0 = clCntZeros16f(x_half);
   r1 = clCntZeros16f(x);
   r = r0;
   r = ( r0 == 16 ) ? r0 + r1: r;
   return (r);
}

static int
clCntZeros64f( __ULONG x )
{
int r, r0, r1, r2;
uint x_hi, x_lo;
uint bits23_0,bits23_1,bits18_2;
   x_lo = (uint)(x & 0xffffffffULL);
   x_hi = (uint)(( x >> 32) & 0xffffffffULL);
   bits23_0 = (x_hi >> 9);
   bits23_1 = (x_hi << 14) | (x_lo >> 18) ;
   bits23_1 &= MANTBITS_SP32;
   bits18_2 = x_lo & 0x3ffff;
   r0 = clCntZeros23f(bits23_0,23);
   r1 = clCntZeros23f(bits23_1,23);
   r2 = clCntZeros23f(bits18_2,18);
   r = r0;
   r = ( r0 == 23 ) ? r0 + r1: r;
   r = ( r0 + r1 == 46 ) ? r0 + r1 + r2: r;
   return (r);
}


static void
multiply_unsigned_64_by_64( __ULONG A, __ULONG B, __ULONG *destLo, __ULONG *destHi )
{
	__ULONG lowA, lowB;
	__ULONG highA, highB;

	// Split up the values
	lowA = A & 0xffffffff;
	highA = A >> 32;
	lowB = B & 0xffffffff;
	highB = B >> 32;

	// Note that, with this split, our multiplication becomes:
	//     ( a * b )
	// = ( ( aHI << 32 + aLO ) * ( bHI << 32 + bLO ) ) >> 64
	// = ( ( aHI << 32 * bHI << 32 ) + ( aHI << 32 * bLO ) + ( aLO * bHI << 32 ) + ( aLO * bLO ) ) >> 64
	// = ( ( aHI * bHI << 64 ) + ( aHI * bLO << 32 ) + ( aLO * bHI << 32 ) + ( aLO * bLO ) ) >> 64
	// = ( aHI * bHI ) + ( aHI * bLO >> 32 ) + ( aLO * bHI >> 32 ) + ( aLO * bLO >> 64 )

	// Now, since each value is 32 bits, the max size of any multiplication is:
	// ( 2 ^ 32 - 1 ) * ( 2 ^ 32 - 1 ) = 2^64 - 4^32 + 1 = 2^64 - 2^33 + 1, which fits within 64 bits
	// Which means we can do each component within a 64-bit integer as necessary (each component above marked as AB1 - AB4)
	__ULONG aHibHi = highA * highB;
	__ULONG aHibLo = highA * lowB;
	__ULONG aLobHi = lowA * highB;
	__ULONG aLobLo = lowA * lowB;

    // Assemble terms.
    //  We note that in certain cases, sums of products cannot overflow:
    //
    //      The maximum product of two N-bit unsigned numbers is
    //
    //          (2**N-1)^2 = 2**2N - 2**(N+1) + 1
    //
    //      We note that we can add the maximum N-bit number to the 2N-bit product twice without overflow:
    //
    //          (2**N-1)^2 + 2*(2**N-1) = 2**2N - 2**(N+1) + 1 + 2**(N+1) - 2 = 2**2N - 1
    //
    //  If we breakdown the product of two numbers a,b into high and low halves of partial products as follows:
    //
    //                                              a.hi                a.lo
    // x                                            b.hi                b.lo
    //===============================================================================
    //  (b.hi*a.hi).hi      (b.hi*a.hi).lo
    //                      (b.lo*a.hi).hi      (b.lo*a.hi).lo
    //                      (b.hi*a.lo).hi      (b.hi*a.lo).lo
    // +                                        (b.lo*a.lo).hi      (b.lo*a.lo).lo
    //===============================================================================
    //
    // The (b.lo*a.lo).lo term cannot cause a carry, so we can ignore them for now.  We also know from above, that we can add (b.lo*a.lo).hi
    // and (b.hi*a.lo).lo to the 2N bit term [(b.lo*a.hi).hi + (b.lo*a.hi).lo] without overflow.  That takes care of all of the terms
    // on the right half that might carry.  Do that now.
    //
    __ULONG aLobLoHi = aLobLo >> 32;
    __ULONG aLobHiLo = aLobHi & 0xFFFFFFFFULL;
    aHibLo += aLobLoHi + aLobHiLo;

    // That leaves us with these terms:
    //
    //                                              a.hi                a.lo
    // x                                            b.hi                b.lo
    //===============================================================================
    //  (b.hi*a.hi).hi      (b.hi*a.hi).lo
    //                      (b.hi*a.lo).hi
    //                    [ (b.lo*a.hi).hi + (b.lo*a.hi).lo + other ]
    // +                                                                (b.lo*a.lo).lo
    //===============================================================================

    // All of the overflow potential from the right half has now been accumulated into the [ (b.lo*a.hi).hi + (b.lo*a.hi).lo ] 2N bit term.
    // We can safely separate into high and low parts. Per our rule above, we know we can accumulate the high part of that and (b.hi*a.lo).hi
    // into the 2N bit term (b.lo*a.hi) without carry.  The low part can be pieced together with (b.lo*a.lo).lo, to give the final low result

    *destHi = aHibHi + (aHibLo >> 32 ) + (aLobHi >> 32);             // Cant overflow
    *destLo = (aHibLo << 32) | ( aLobLo & 0xFFFFFFFFULL );
}

static void
multiply_signed_64_by_64( __LONG A, __LONG B, __ULONG *destLo, __LONG *destHi )
{
    // Find sign of result
    __LONG aSign = (A >> _LONG_BITS);
    __LONG bSign = (B >> _LONG_BITS);
    __LONG resultSign = aSign ^ bSign;

    // take absolute values of the argument
    A = (A ^ aSign) - aSign;
    B = (B ^ bSign) - bSign;

    __ULONG hi;
    multiply_unsigned_64_by_64( (__ULONG) A, (__ULONG) B, destLo, &hi );

    // Fix the sign
    if( resultSign )
    {
        *destLo ^= resultSign;
        hi  ^= resultSign;
        *destLo -= resultSign;

        //carry if necessary
        if( 0 == *destLo )
            hi -= resultSign;
    }

    *destHi = (__LONG) hi;
}

static double copysign( double _a, double _b);

typedef union {
  double d;
  struct{
    int lo;
    int hi;
  };
} fd_twoints;

#define __HI( x ) x.hi
#define __LO( x ) x.lo

static const double
two54   =  1.80143985094819840000e+16, /* 0x43500000, 0x00000000 */
twom54  =  5.55111512312578270212e-17, /* 0x3C900000, 0x00000000 */
really_big   = 1.0e+300,
tiny   = 1.0e-300;

static
double scalb (double x, int n)
{
        fd_twoints u;
        int  k,hx,lx;
        u.d = x;
        hx = __HI(u);
        lx = __LO(u);
        k = (hx&0x7ff00000)>>20;                /* extract exponent */
        if (k==0) {                             /* 0 or subnormal x */
            if ((lx|(hx&0x7fffffff))==0) return x; /* +-0 */
            x *= two54;
            u.d = x;
            hx = __HI(u);
            k = ((hx&0x7ff00000)>>20) - 54;
            if (n< -50000) return tiny*x;       /*underflow*/
            }
        if (k==0x7ff) return x+x;               /* NaN or Inf */
        k = k+n;
        if (k >  0x7fe) return really_big*copysign(really_big,x); /* overflow  */
        if (k > 0)                              /* normal result */
            {u.d = x; __HI(u) = (hx&0x800fffff)|(k<<20); x = u.d; return x;}
        if (k <= -54) {
            if (n > 50000)      /* in case integer overflow in n+k */
                return really_big*copysign(really_big,x);    /*overflow*/
            else return tiny*copysign(tiny,x);       /*underflow*/
        }
        k += 54;                                /* subnormal result */
        u.d = x;
        __HI(u) = (hx&0x800fffff)|(k<<20);
        x = u.d;
        return x*twom54;
}


static const double
TWO52[2]={
  4.50359962737049600000e+15, /* 0x43300000, 0x00000000 */
 -4.50359962737049600000e+15, /* 0xC3300000, 0x00000000 */
};
static
double rint(double x)
{
        int i0,j0,sx;
        unsigned i,i1;
        double w,t;
        fd_twoints u;

        u.d = x;
        i0 =  __HI(u);
        sx = (i0>>31)&1;
        i1 =  __LO(u);
        j0 = ((i0>>20)&0x7ff)-0x3ff;
        if(j0<20) {
            if(j0<0) {
                if(((i0&0x7fffffff)|i1)==0) return x;
                i1 |= (i0&0x0fffff);
                i0 &= 0xfffe0000;
                i0 |= ((i1|-(int)i1)>>12)&0x80000;
                u.d = x;
                __HI(u)=i0;
                x = u.d;
                w = TWO52[sx]+x;
                t =  w-TWO52[sx];
                u.d = t;
                i0 = __HI(u);
                __HI(u) = (i0&0x7fffffff)|(sx<<31);
                t = u.d;
                return t;
            } else {
                i = (0x000fffff)>>j0;
                if(((i0&i)|i1)==0) return x; /* x is integral */
                i>>=1;
                if(((i0&i)|i1)!=0) {
                    if(j0==19) i1 = 0x40000000; else
                    i0 = (i0&(~i))|((0x20000)>>j0);
                }
            }
        } else if (j0>51) {
            if(j0==0x400) return x+x;   /* inf or NaN */
            else return x;              /* x is integral */
        } else {
            i = ((unsigned)(0xffffffff))>>(j0-20);
            if((i1&i)==0) return x;     /* x is integral */
            i>>=1;
            if((i1&i)!=0) i1 = (i1&(~i))|((0x40000000)>>(j0-20));
        }
        u.d = x;
        __HI(u) = i0;
        __LO(u) = i1;
        x = u.d;
        w = TWO52[sx]+x;
        return w-TWO52[sx];
}



static double nextafter(double x, double y)
{
        int     hx,hy,ix,iy;
        unsigned lx,ly;
        fd_twoints ux, uy;

        ux.d = x; uy.d = y;
        hx = __HI(ux);          /* high word of x */
        lx = __LO(ux);          /* low  word of x */
        hy = __HI(uy);          /* high word of y */
        ly = __LO(uy);          /* low  word of y */
        ix = hx&0x7fffffff;             /* |x| */
        iy = hy&0x7fffffff;             /* |y| */

        if(((ix>=0x7ff00000)&&((ix-0x7ff00000)|lx)!=0) ||   /* x is nan */
           ((iy>=0x7ff00000)&&((iy-0x7ff00000)|ly)!=0))     /* y is nan */
           return x+y;
        if(x==y) return x;              /* x=y, return x */
        if((ix|lx)==0) {                        /* x == 0 */
            ux.d = x;
            __HI(ux) = hy&0x80000000;   /* return +-minsubnormal */
            __LO(ux) = 1;
            x = ux.d;
            y = x*x;
            if(y==x) return y; else return x;   /* raise underflow flag */
        }
        if(hx>=0) {                             /* x > 0 */
            if(hx>hy||((hx==hy)&&(lx>ly))) {    /* x > y, x -= ulp */
                if(lx==0) hx -= 1;
                lx -= 1;
            } else {                            /* x < y, x += ulp */
                lx += 1;
                if(lx==0) hx += 1;
            }
        } else {                                /* x < 0 */
            if(hy>=0||hx>hy||((hx==hy)&&(lx>ly))){/* x < y, x -= ulp */
                if(lx==0) hx -= 1;
                lx -= 1;
            } else {                            /* x > y, x += ulp */
                lx += 1;
                if(lx==0) hx += 1;
            }
        }
        hy = hx&0x7ff00000;
        if(hy>=0x7ff00000) return x+x;  /* overflow  */
        if(hy<0x00100000) {             /* underflow */
            y = x*x;
            if(y!=x) {          /* raise underflow flag */
                uy.d = y;
                __HI(uy) = hx; __LO(uy) = lx;
                y = uy.d;
                return y;
            }
        }
        ux.d = x;
        __HI(ux) = hx; __LO(ux) = lx;
        x = ux.d;
        return x;
}


//-----------------------------------------------------------------------------
// File: nextafter.cl
//-----------------------------------------------------------------------------

static float nextafter( float _x, float _y)
{
float x = _x;
float y = _y;

uint uax, uay;
int ix, iy;
    ix = as_int(x);
	iy = as_int(y);
    uax = ix & ~SIGNBIT_SP32; 
    uay = iy & ~SIGNBIT_SP32; 

/* x > 0 */
/* x > y, x -= ulp */
/* x < y, x += ulp */
/* x < 0 */
/* x < y, x -= ulp */
/* x > y, x += ulp */

int step = -1;
    step = ((ix > 0 && ix < iy) || (ix < 0 && iy < 0 && ix < iy)) ? 1 : step;
int next = ix + step;
float ret = as_float(next);
// special cases
// +- 0
    ret = (uax==0 && uax!=uay ) ? as_float((iy & 0x80000000) | 1) : ret;
// x == y
    ret = (ix == iy || (uax==0 && uax==uay)) ? y : ret;
// x || y == NAN
	ret = ( uax > PINFBITPATT_SP32) ? _x :  ret;
	ret = ( uay > PINFBITPATT_SP32) ? _y :  ret;
    return(ret);
}

//-----------------------------------------------------------------------------
// File: nan.cl
//-----------------------------------------------------------------------------

static float nan( int _InNANCode)
{
int nan_code = (_InNANCode & MANTBITS_SP32);
float ret = as_float(QNANBITPATT_SP32 | nan_code );
   return(ret);
}

static double nan( __LONG _InNANCode)
{
__LONG nan_code = (_InNANCode & MANTBITS_DP64);
double ret = as_double( QNANBITPATT_DP64 | nan_code);
   return(ret);
}


#endif //_MATHFUNCTIONS_HCL_

