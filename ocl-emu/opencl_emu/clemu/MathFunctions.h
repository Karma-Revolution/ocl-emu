#ifndef _MATHFUNCTIONS_HL_
#define _MATHFUNCTIONS_HL_

#pragma OPENCL EXTENSION cl_khr_fp64 : enable

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
#define _UCHAR_MSB_BITS         0x80
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
#define _USHRT_MSB_BITS         0x8000
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
#define _UINT_MSB_BITS          0x80000000

#ifndef LLONG_MAX
#define LLONG_MAX     9223372036854775807ULL       /* maximum signed long long int value */
#define LLONG_MIN   (-9223372036854775807LL - 1)  /* minimum signed long long int value */
#define ULLONG_MAX    0xffffffffffffffffULL       /* maximum unsigned long long int value */
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



static int
clIsnan( float x )
{
int r = ((as_int(x) & ~SIGNBIT_SP32) > (int)PINFBITPATT_SP32);
   return(r);
}

static int
clIsinf( float x )
{
int r = ((as_int(x) & ~SIGNBIT_SP32) == (int)PINFBITPATT_SP32);
   return(r);
}

static int
clIsfinite( float x )
{
  return (!clIsnan(x) && !clIsinf(x));
}

static float
clMakenan( )
{
   return (as_float(((int)PINFBITPATT_SP32 + 1)));
}

static float
clMakenan2( float x )
{
int ix = as_int(x);
float r = as_float(ix | ((int)PINFBITPATT_SP32 + 1));
   return (r);
}


static float
clMakepinf( )
{
   return (as_float((int)PINFBITPATT_SP32));
}

static float
clMakeninf( )
{
   return (as_float((int)NINFBITPATT_SP32));
}

static float
clMakenindf( )
{
   return (as_float((int)INDEFBITPATT_SP32));
}

static float
clMakenindf2( float x )
{
int ix = as_int(x);
float r = as_float(ix | INDEFBITPATT_SP32);
   return (r);
}

static int
clFabsi( float x )
{
int r = (as_int(x) & ~SIGNBIT_SP32);
   return(r);
}

static float
clFabs( float x )
{
float r = as_float(clFabsi(x));
   return(r);
}

static int
clSignbit( float x )
{
int r = (as_int(x) & SIGNBIT_SP32);
   return(r);
}



static ulong
clMakeULONG( uint _hi, uint _lo)
{
union {
   struct {
       uint lo;
       uint hi;
     } uint_struct;
     ulong combined;
  } ulong_union;
   ulong_union.uint_struct.lo = _lo;
   ulong_union.uint_struct.hi = _hi;
   return(ulong_union.combined);
}

static long
clMakeLONG( int _hi, uint _lo)
{
union {
   struct {
       uint lo;
       int hi;
     } int_struct;
     long combined;
  } long_union;
   long_union.int_struct.lo = _lo;
   long_union.int_struct.hi = _hi;
   return(long_union.combined);
}

static void
clSplitULONG( uint *_hi, uint *_lo, ulong _arg)
{
union {
   struct {
       uint lo;
       uint hi;
     } uint_struct;
     ulong combined;
  } ulong_union;
  ulong_union.combined = _arg;
   *_lo = ulong_union.uint_struct.lo;
   *_hi = ulong_union.uint_struct.hi;
}

static void
clSplitLONG( int *_hi, uint *_lo, long _arg)
{
union {
   struct {
       uint lo;
       int hi;
     } int_struct;
     long combined;
  } long_union;
  long_union.combined = _arg;
   *_lo = long_union.int_struct.lo;
   *_hi = long_union.int_struct.hi;
}

static int
clUpsampleCHAR(uchar _arg)
{
int r = 0;
   r = (_arg & 0x80) ? (int)((uint)0xffffff | (uint)_arg) : (uint)_arg;
   return(r); 
}

static int
clUpsampleSHORT(ushort _arg)
{
int r = 0;
   r = (_arg & 0x8000) ? (int)((uint)0xffff | (uint)_arg) : (uint)_arg;
   return(r); 
}

static uchar
clDownsampleToCHAR(uint _arg)
{
    return(_arg & 0xff);
}

static ushort
clDownsampleToSHORT(uint _arg)
{
    return(_arg & 0xffff);
}

static ulong
_CL_MAXU64( ulong x, ulong y )
{
ulong r;
uint hi_x, lo_x, hi_y, lo_y;
int x_larger;
    clSplitULONG( &hi_x, &lo_x, x);
    clSplitULONG( &hi_y, &lo_y, y);
    x_larger = (hi_x > hi_y || (hi_x == hi_y &&  lo_x >= lo_y))? 1 : 0;
    r = (x_larger)?clMakeULONG( hi_x, lo_x):clMakeULONG( hi_y, lo_y);
    return(r);
}

static ulong
_CL_MINU64( ulong x, ulong y )
{
ulong r;
uint hi_x, lo_x, hi_y, lo_y;
int x_smaller;
    clSplitULONG( &hi_x, &lo_x, x);
    clSplitULONG( &hi_y, &lo_y, y);
    x_smaller = (hi_x < hi_y || (hi_x == hi_y &&  lo_x < lo_y))? 1 : 0;
    r = (x_smaller)?clMakeULONG( hi_x, lo_x):clMakeULONG( hi_y, lo_y);
    return(r);
}

static long
_CL_MAXI64( long x, long y )
{
long r = 0;
int the_same_sign;
uint hi_x, lo_x, hi_y, lo_y;
int x_larger;
    clSplitULONG( &hi_x, &lo_x, x);
    clSplitULONG( &hi_y, &lo_y, y);
    hi_x = (hi_x == 0x80000000 && lo_x == 0 ) ? 0 : hi_x;
    hi_y = (hi_y == 0x80000000 && lo_y == 0 ) ? 0 : hi_y;
    x_larger = (hi_x > hi_y || (hi_x == hi_y &&  lo_x >= lo_y))? 1 : 0;
    the_same_sign = ((hi_x ^ hi_y) >> 31);
    r = (!the_same_sign && (hi_x & 0x80000000)) ? y : x;
    r = (the_same_sign&& (hi_x & 0x80000000) && x_larger) ? y : x;
    return(r);
}

static long
_CL_MINI64( long x, long y )
{
long r = 0;
int the_same_sign;
uint hi_x, lo_x, hi_y, lo_y;
int x_larger;
    clSplitULONG( &hi_x, &lo_x, x);
    clSplitULONG( &hi_y, &lo_y, y);
    hi_x = (hi_x == 0x80000000 && lo_x == 0 ) ? 0 : hi_x;
    hi_y = (hi_y == 0x80000000 && lo_y == 0 ) ? 0 : hi_y;
    x_larger = (hi_x > hi_y || (hi_x == hi_y &&  lo_x >= lo_y))? 1 : 0;
    the_same_sign = ((hi_x ^ hi_y) >> 31);
    r = (!the_same_sign && (hi_x & 0x80000000)) ? x : y;
    r = (the_same_sign&& (hi_x & 0x80000000)&& x_larger) ? x : y;
    return(r);
}


// Add a + b. If the result modulo overflowed, write 1 to *carry, otherwise 0
static uint
cl_add_carryu32( uint a, uint b, uint *carry )
{
uint result = a + b;
    *carry = (result < a);
    return result;
}

// Subtract a - b. If the result modulo overflowed, write 1 to *carry, otherwise 0
static uint  
cl_sub_carryu32( uint a, uint b, uint *carry )
{
uint result = a - b;
    *carry = (result > a);
    return result;
}


// Add two 64 bit 

static void
cl_addu64( uint *_carry, uint *_oHi, uint *_oLo, uint _Hi0, uint _Lo0, uint _Hi1, uint _Lo1  )
{
uint carry32;
uint carry0,carry;

    *_oLo = cl_add_carryu32(_Lo0, _Lo1, &carry32);
// if carry is here 
	*_oHi = cl_add_carryu32(_Hi0,carry32,&carry0);
// it won't be here
	*_oHi = cl_add_carryu32(_Hi1,*_oHi,&carry);
    carry |= carry0;
    *_carry = carry;
}

// Subtract two 64 bit 
static void subu64( uint *_carry,
                   uint *_oHi,
				   uint *_oLo,
				   uint _Hi0,
				   uint _Lo0,
				   uint _Hi1,
				   uint _Lo1)
{
uint carry32;
uint carry0, carry;
    
    *_oLo = cl_sub_carryu32(_Lo0, _Lo1, &carry32);
// if carry is here 
	*_oHi = cl_sub_carryu32(_Hi0,carry32,&carry0);
// it won't be here
	*_oHi = cl_sub_carryu32(*_oHi,_Hi1,&carry);

	carry |= carry0;
	
	*_carry = carry;
}




static
void GET_BITS_SP32(float x, uint *ux)
{
union {float f; uint i;} _bitsy;
    _bitsy.f = (x);
    *ux = _bitsy.i;
}



static
void PUT_BITS_SP32(uint ux, float *x)
{
 union {float f; uint i;} _bitsy;
    _bitsy.i = (ux);
     *x = _bitsy.f;
}

 #if 1


static
void GET_BITS_DP64(double x, ulong *ux)
  {
union {double d; ulong i;} _bitsy;
    _bitsy.d = (x);
    *ux = _bitsy.i;
  }
  
 
static
void PUT_BITS_DP64(ulong ux, double *x)
  {
    union {double d; ulong i;} _bitsy;
    _bitsy.i = (ux);
    *x = _bitsy.d;
  }



static void
_EXTRACT_WORDS(uint *ix, uint *lx, double x)
{
ulong macro_t;
  GET_BITS_DP64( x,&macro_t );
  *lx = (uint) (macro_t & 0xffffffff);
  *ix = (uint)(macro_t >> 32);
}


//


static void
_INSERT_WORDS(double *x, uint i0, uint i1)
{
ulong macro_t = (ulong)i0;
    macro_t = ((ulong)macro_t << 32) | (ulong)i1;
	PUT_BITS_DP64(macro_t, x);
}

static void
_SET_HIGH_WORD(double *x, int ix )
{
int ixt, lx;
  _EXTRACT_WORDS((uint*)&ixt,(uint*)&lx, (*x));
  _INSERT_WORDS(x,ix,lx);
}

static void
_GET_HIGH_WORD(int *ix, double x)
{
int lx;
  _EXTRACT_WORDS((uint*)ix,(uint*)&lx,x);
}

static void
_SET_LOW_WORD(double *x, int lx)
{
int ix, lxt;
  _EXTRACT_WORDS((uint*)&ix,(uint*)&lxt, (*x));
  _INSERT_WORDS(x,ix,lx);
}

static void
_GET_LOW_WORD(int *lx, double x)
{
int ix;
  _EXTRACT_WORDS((uint*)&ix,(uint*)lx,x);
}

/* Scales the double x by 2.0**n.
   Assumes EMIN <= n <= EMAX, though this condition is not checked. */
static double 
scaleDouble_1(double x, int n)
{
  double t;
  /* Construct the number t = 2.0**n */
  PUT_BITS_DP64(((long)n + EXPBIAS_DP64) << EXPSHIFTBITS_DP64, &t);
  return x*t;
}

/* Scales the double x by 2.0**n.
   Assumes 2*EMIN <= n <= 2*EMAX, though this condition is not checked. */
static double 
scaleDouble_2(double x, int n)
{
  double t1, t2;
  int n1, n2;
  n1 = n / 2;
  n2 = n - n1;
  /* Construct the numbers t1 = 2.0**n1 and t2 = 2.0**n2 */
  PUT_BITS_DP64(((long)n1 + EXPBIAS_DP64) << EXPSHIFTBITS_DP64, &t1);
  PUT_BITS_DP64(((long)n2 + EXPBIAS_DP64) << EXPSHIFTBITS_DP64, &t2);
  return (x*t1)*t2;
}




/* Scales the double x by 2.0**n.
   Assumes 3*EMIN <= n <= 3*EMAX, though this condition is not checked. */
static double 
scaleDouble_3(double x, int n)
{
  double t1, t2, t3;
  int n1, n2, n3;
  n1 = n / 3;
  n2 = (n - n1) / 2;
  n3 = n - n1 - n2;
  /* Construct the numbers t1 = 2.0**n1, t2 = 2.0**n2 and t3 = 2.0**n3 */
  PUT_BITS_DP64(((long)n1 + EXPBIAS_DP64) << EXPSHIFTBITS_DP64, &t1);
  PUT_BITS_DP64(((long)n2 + EXPBIAS_DP64) << EXPSHIFTBITS_DP64, &t2);
  PUT_BITS_DP64(((long)n3 + EXPBIAS_DP64) << EXPSHIFTBITS_DP64, &t3);
  return ((x*t1)*t2)*t3;
}

/* Computes the exact product of x and y, the result being the
   nearly doublelength number (z,zz) */ 
static void 
mul12d(double x, double y, double *z, double *zz)
{
  double hx, tx, hy, ty;
  // Split x into hx (head) and tx (tail). Do the same for y.
  ulong u;
  GET_BITS_DP64(x, &u);
  u &= 0xfffffffff8000000ULL;
  PUT_BITS_DP64(u, &hx);
  tx = x - hx;
  GET_BITS_DP64(y, &u);
  u &= 0xfffffffff8000000ULL;
  PUT_BITS_DP64(u, &hy);
  ty = y - hy;
  *z = x * y;
  *zz = (((hx * hy - *z) + hx * ty) + tx * hy) + tx * ty;
}


/* Computes the doublelength product of (x,xx) and (y,yy), the result
   being the doublelength number (z,zz) */
static void 
mul2d(double x, double xx, double y, double yy, double *z, double *zz)
{
  double c, cc;
  mul12d(x, y, &c, &cc);
  cc = x * yy + xx * y + cc;
  *z = c + cc;
  *zz = (c - *z) + cc;
}

static void 
dekker_mul12d(double x, double y, double *z, double *zz)
{
  double hx, tx, hy, ty;
  /* Split x into hx (head) and tx (tail). Do the same for y. */
  ulong u;
  GET_BITS_DP64(x, &u);
  u &= 0xfffffffff8000000ULL;
  PUT_BITS_DP64(u, &hx);
  tx = x - hx;
  GET_BITS_DP64(y, &u);
  u &= 0xfffffffff8000000ULL;
  PUT_BITS_DP64(u, &hy);
  ty = y - hy;
  *z = x * y;
  *zz = (((hx * hy - *z) + hx * ty) + tx * hy) + tx * ty;
}


#endif

static void
_SET_FLOAT_WORD(float *x, int i0)
{
	*x = as_float(i0);
}

static void
_GET_FLOAT_WORD(int *i0, float x)
{
	*i0 = as_int(x);
}



/* Scales the float x by 2.0**n.
   Assumes EMIN <= n <= EMAX, though this condition is not checked. */
static float
scaleFloat_1(float x, int n)
{
  float t;
  /* Construct the number t = 2.0**n */
  PUT_BITS_SP32((n + EXPBIAS_SP32) << EXPSHIFTBITS_SP32, &t);
  return x*t;
}



/* Scales the float x by 2.0**n.
   Assumes 2*EMIN <= n <= 2*EMAX, though this condition is not checked. */
static float 
scaleFloat_2(float x, int n)
{
  float t1, t2;
  int n1, n2;
  n1 = n / 2;
  n2 = n - n1;
  /* Construct the numbers t1 = 2.0**n1 and t2 = 2.0**n2 */
  PUT_BITS_SP32((n1 + EXPBIAS_SP32) << EXPSHIFTBITS_SP32, &t1);
  PUT_BITS_SP32((n2 + EXPBIAS_SP32) << EXPSHIFTBITS_SP32, &t2);
  return (x*t1)*t2;
}







/* Computes the exact product of x and y, the result being the
   nearly double length number (z,zz) */ 
static void 
mul12f(float x, float y, float *z,float *zz)
{
  float hx, tx, hy, ty;
  // Split x into hx (head) and tx (tail). Do the same for y.
  uint u;
  GET_BITS_SP32(x, &u);
  u &= 0xfffff000;
  PUT_BITS_SP32(u, &hx);
  tx = x - hx;
  GET_BITS_SP32(y, &u);
  u &= 0xfffff000;
  PUT_BITS_SP32(u, &hy);
  ty = y - hy;
  *z = x * y;
  *zz = (((hx * hy - *z) + hx * ty) + tx * hy) + tx * ty;
}


/* Computes the doublelength product of (x,xx) and (y,yy), the result
   being the doublelength number (z,zz) */
static void 
mul2f(float x, float xx, float y, float yy, float *z, float *zz)
{
  float c, cc;
  mul12f(x, y, &c, &cc);
  cc = x * yy + xx * y + cc;
  *z = c + cc;
  *zz = (c - *z) + cc;
}


static
void add2f( float a, float b, float *r, float *s )
{
  *r = a + b;

  if (clFabs(a) > clFabs(b))
    *s = ((a - *r) + b);
  else
    *s = ((b - *r) + a);
}

/* Scales down a double whose bit pattern is given as ux by 2**k.
   There are no checks that the input number is scalable by that amount. */
static void 
scaleDownDouble(ulong ux, int k, ulong *ur)
{
  ulong uy, uk, ax, xsign;
  int n, shift;
  xsign = ux & SIGNBIT_DP64;
  ax = ux & ~SIGNBIT_DP64;
  n = (int)((ax & EXPBITS_DP64) >> EXPSHIFTBITS_DP64) - k;
  if (n > 0)
    {
      uk = (ulong)n << EXPSHIFTBITS_DP64;
      uy = (ax & ~EXPBITS_DP64) | uk;
    }
  else
    {
      uy = (ax & ~EXPBITS_DP64) | 0x0010000000000000ULL;
      shift = (1 - n);
      if (shift > MANTLENGTH_DP64 + 1)
        /* Sigh. Shifting works mod 64 so be careful not to shift too much */
        uy = 0;
      else
        {
          /* Make sure we round the result */
          uy >>= shift - 1;
          uy = (uy >> 1) + (uy & 1);
        }
    }
  *ur = uy | xsign;
}




static int
clCntZeros16( uint x )
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
clCntZeros23( uint x, int max_bits )
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
   r0 = clCntZeros16(x_half);
   r1 = clCntZeros16(x);
   r = r0;
   r = ( r0 == 16 ) ? r0 + r1: r;
   return (r);
}

static int
clCntZeros64f( ulong x )
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
   r0 = clCntZeros23(bits23_0,23);
   r1 = clCntZeros23(bits23_1,23);
   r2 = clCntZeros23(bits18_2,18);
   r = r0;
   r = ( r0 == 23 ) ? r0 + r1: r;
   r = ( r0 + r1 == 46 ) ? r0 + r1 + r2: r;
   return (r);
}

// due to HW sub-normal behaviour
// x*y ==0, when x or y is sub-normal
static float subnormalMultiply1( int _unnorm, float _norm )
{
int mantx = _unnorm;
float fmantx = (float)mantx;
float norm_scaled = _norm;
float tr = fmantx*norm_scaled;
int i_tr = as_int(tr);
int exp_delta;
     exp_delta = ((i_tr & EXPBITS_SP32) >> EXPSHIFTBITS_SP32);
     i_tr &= MANTBITS_SP32;
     i_tr |= IMPBIT_SP32;
int shift = (150 - exp_delta);
int i_r;
	 i_r = ( shift > 0 ) ? i_tr >> shift : i_tr + ((-shift) << EXPSHIFTBITS_SP32);
float r = as_float(i_r);
     return(r);
}

// signed
// due to HW sub-normal behaviour
// x*y ==0, when x or y is sub-normal
static float s_subnormalMultiply1( int _unnorm, float _norm )
{
float r = 0;
int signx = _unnorm & SIGNBIT_SP32;
int signy = as_int(_norm) & SIGNBIT_SP32;
int mantx = _unnorm & ~SIGNBIT_SP32;
float abs_norm = fabs(_norm);
	 r = subnormalMultiply1(mantx, abs_norm );
     r = as_float(as_int(r) | (signx^signy));
     return(r);
}


// due to HW sub-normal behaviour
// x*y ==0, when x or y is sub-normal
static float subNormalScale1( int _unnorm, int _scale )
{
int mantx;
int i_tr;
int exp_delta;
     mantx = _unnorm;
     i_tr = as_int((float)mantx);
     exp_delta = ((i_tr & EXPBITS_SP32) >> EXPSHIFTBITS_SP32) + _scale;
     i_tr &= MANTBITS_SP32;
     i_tr |= IMPBIT_SP32;
int shift = (150 - exp_delta);
int i_r;
     shift = (shift > 23 )? 24 : shift;
	 i_r = ( shift > 0 ) ? i_tr >> shift : i_tr + ((-shift) << EXPSHIFTBITS_SP32);
float r = as_float(i_r);
     return(r);
}



static float scaleFullRangef32(float y, float t)
{
float r = 0;
int k;
float ay;
int iiy, iy;
int exp_iy0;
int exp_iy;
int manty;
int signy;
int miy;    
    k = (clFabs(t ) > 1024)? 1024 : (int)clFabs(t)  ;
	k = ( t < 0 ) ? -k : k;
	t = (float)k;
    iiy = as_int(y);
    iy = (iiy & ~SIGNBIT_SP32);
	signy = (iiy & SIGNBIT_SP32);
    ay = as_float(iy);
    exp_iy0 = (iy&EXPBITS_SP32);
    manty = (iy & MANTBITS_SP32);
//sub-normal
float ty = (exp_iy0 == 0)? (float)manty : as_float(iy);
    k = (exp_iy0 == 0)? k - 149 : k;
	ay = ty;
    iy = as_int(ay);
    exp_iy0 = (iy&EXPBITS_SP32);
    exp_iy = ((exp_iy0 >> EXPSHIFTBITS_SP32) - EXPBIAS_SP32);
	// add k to y's exponent
    r = as_float(iy + (k << EXPSHIFTBITS_SP32));
	r = ((exp_iy + k) > 127)? as_float(PINFBITPATT_SP32) : r;
// add k to y's exponent
int delta = -126 - (exp_iy + k);
int shift;
// sub-normal
    miy = (iy & MANTBITS_SP32);
    miy |= IMPBIT_SP32;
	shift = (delta > 23 ) ? 24 : delta;
	shift = (delta < 0 ) ? 0 : shift;
	miy >>= shift;
	r = ( delta > 0 ) ? as_float(miy) : r;
    r = ( t > (float)(2*EMAX_SP32) ) ?  as_float(PINFBITPATT_SP32) : r;
int ir = as_int(r);
    r = (ir <= PINFBITPATT_SP32) ? as_float(as_int(r) | signy) : r;
	return(r);
}




uint clintr_add_sat_u32(uint x, uint y);

static void
multiply_unsigned_64_by_64( ulong A, ulong B, ulong *destLo, ulong *destHi )
{
	ulong lowA, lowB;
	ulong highA, highB;

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
	ulong aHibHi = highA * highB;
	ulong aHibLo = highA * lowB;
	ulong aLobHi = lowA * highB;
	ulong aLobLo = lowA * lowB;

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
    ulong aLobLoHi = aLobLo >> 32;
    ulong aLobHiLo = aLobHi & 0xFFFFFFFFULL;
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
multiply_signed_64_by_64( long A, long B, ulong *destLo, long *destHi )
{
    // Find sign of result
    long aSign = (A >> _LONG_BITS);
    long bSign = (B >> _LONG_BITS);
    long resultSign = aSign ^ bSign;

    // take absolute values of the argument
    A = (A ^ aSign) - aSign;
    B = (B ^ bSign) - bSign;

    ulong hi;
    multiply_unsigned_64_by_64( (ulong) A, (ulong) B, destLo, &hi );

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

    *destHi = (long) hi;
}

#endif //_MATHFUNCTIONS_HL_

