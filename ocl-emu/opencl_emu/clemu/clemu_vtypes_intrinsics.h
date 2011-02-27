/*--------------------------------------------------------------------------------------------------------------------------------------------------------
Modified BSD License (2011):

Copyright (c) 2011, Advanced Micro Devices, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following are met:

Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software
without specific, prior, written permission. 

You must reproduce the above copyright notice.

You must include the following terms in your license and/or other materials provided with the software. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
Without limiting the foregoing, the software may implement third party technologies (e.g. third party libraries) for which you must obtain licenses from 
parties other than AMD.  You agree that AMD has not obtained or conveyed to you, and that you shall be responsible for obtaining the rights to use and/or
distribute the applicable underlying intellectual property rights related to the third party technologies.  These third party technologies are not licensed hereunder.
Without limiting the foregoing, for MPEG-2 products, the following additional notices are provided:
For MPEG-2 Encoding Products (those that are “Sold” to end-users, directly or indirectly):
NO LICENSE IS GRANTED HEREIN, BY IMPLICATION OR OTHERWISE, TO YOU OR YOUR CUSTOMERS TO USE MPEG-2 ENCODING PRODUCTS, MPEG-2 DISTRIBUTION ENCODING PRODUCTS,
MPEG-2 ENCODING SOFTWARE, AND/OR MPEG-2 BUNDLED ENCODING SOFTWARE FOR ENCODING OR HAVING ENCODED ONE OR MORE MPEG-2 VIDEO EVENTS FOR RECORDING ON AN MPEG-2 
PACKAGED MEDIUM FOR ANY USE OR DISTRIBUTION OTHER THAN PERSONAL USE OF LICENSEE’S CUSTOMER.
For MPEG-2 Intermediate Products (those that are NOT “Sold” to end-users, directly or indirectly):
NO LICENSE IS GRANTED HEREIN, BY IMPLICATION OR OTHERWISE, TO YOU OR YOUR CUSTOMERS TO USE MPEG-2 INTERMEDIATE PRODUCTS MANUFACTURED OR SOLD BY YOU.
If you use the software (in whole or in part), you shall adhere to all applicable U.S., European, and other export laws, including but not limited to
the U.S. Export Administration Regulations (“EAR”), (15 C.F.R. Sections 730 through 774), and E.U. Council Regulation (EC) No 1334/2000 of 22 June 2000.
Further, pursuant to Section 740.6 of the EAR, you hereby certify that, except pursuant to a license granted by the United States Department
of Commerce Bureau of Industry and Security or as otherwise permitted pursuant to a License Exception under the U.S. Export Administration Regulations ("EAR"),
you will not (1) export, re-export or release to a national of a country in Country Groups D:1, E:1 or E:2 any restricted technology, software, or source code
you receive hereunder, or (2) export to Country Groups D:1, E:1 or E:2 the direct product of such technology or software, if such foreign produced direct product
is subject to national security controls as identified on the Commerce Control List (currently found in Supplement 1 to Part 774 of EAR).  For the most current
Country Group listings, or for additional information about the EAR or your obligations under those regulations, please refer to the U.S. Bureau of Industry and
Security’s website at http://www.bis.doc.gov/. 

------------------------------------------------------------------------------------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
// File: clemu_vtypes_intrinsics
//
// Desc: Modeling cl constructs in C++.
//
//-----------------------------------------------------------------------------

#ifndef _CLE_EMU_VTYPES_INTRISICS_H_
#define _CLE_EMU_VTYPES_INTRISICS_H_

//#define AMDGC4XEMU 1


//#include <iostream>
#include <typeinfo.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <memory.h>
#include <assert.h>




#define MAX_VECTOR_DIM 4

#define VEC2(Vec, I0, I1)         Vec((I0),(I1))
#define VEC3(Vec, I0, I1, I2)     Vec((I0),(I1), (I2))
#define VEC4(Vec, I0, I1, I2, I3) Vec((I0),(I1), (I2), (I3))


// UINT

typedef float cl_float;




#include "MathFunctions.ccl"


template < class _T> class clemu_vector2;
template < class _T> class clemu_vector4;
template < class _T> class clemu_vector8;
template < class _T> class clemu_vector16;

template < class _T> class clemu_vector_i2;
template < class _T> class clemu_vector_i4;
template < class _T> class clemu_vector_i8;
template < class _T> class clemu_vector_i16;


/*-----------------------------------------------------------------------------------
NEW OPENCL VECTORS
----------------------------------------------------------------------------------*/

template < class _T> class clemu_vector2 {

protected:
public:

  union{
	  _T s[2];
	  struct {
         _T x;
         _T y;
	  };
	  struct {
         _T s0;
         _T s1;
	  };
	  struct {
		  _T lo;
		  _T hi;
	  };
	  struct {
		  _T even;
		  _T odd;
	  };

	};



/*---------------------------------------------------------------------------------------------------------
  operators []
---------------------------------------------------------------------------------------------------------*/
	_T & operator [] ( int _Indx )
	{
		assert(_Indx >=0 && _Indx < 2 );
		return (s[_Indx]);
	}
template <class _TT>
clemu_vector2<_T> fill(_TT val)
{
	for(int i = 0; i < 2; i++)
	{
		s[i] = (_T)val;
	}
   return(*this);
}

	clemu_vector2<_T>( void )
	{
		fill(0);
	}


/*---------------------------------------------------------------------------------------------------------
  copy constructors
---------------------------------------------------------------------------------------------------------*/
template <class _TT>
    clemu_vector2<_T> ( _TT _From )
	{
		fill(_From);
	}


template <class _TT>
    clemu_vector2<_T> ( const clemu_vector2<_TT> & _From )
	{
		for(int i = 0; i < 2; i++)
		{
			s[i] = (_T)_From.s[i];
		}
	}


/*
=
*/
/*
//template <class _TT>
	 clemu_vector2<_T> & operator=(const clemu_vector2<_T> & _In)
	{
       clemu_vector2<_T> tmp(_In);
	   *this = tmp;
	   return(*this);
	}
*/

template <class _TT>
	 clemu_vector2<_T> & operator=(_TT _In)
	{
       clemu_vector2<_T> tmp(_In);
	   *this = tmp;
	   return(*this);
	}


/*---------------------------------------------------------------------------------------------------------
  operators + 
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector2<_T> operator + (const clemu_vector2<_TT> & _In)
	 {
	   clemu_vector2<_T> tmp;
	      tmp.lo = lo + (_T)_In.lo;
	      tmp.hi = hi + (_T)_In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector2<_T> operator + (_TT _In)
	 {
	 clemu_vector2<_T> tmp;
	 clemu_vector2<_T> tmp1(_In);
	     tmp = *this + tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector2<_T>& operator += (const clemu_vector2<_TT> & _In)
	 {
        *this = *this + _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector2<_T>& operator += (_TT _In)
	 {
	 clemu_vector2<_T> tmp1(_In);
        *this = *this + tmp1;
		return(*this);
	 }

	clemu_vector2<_T>& operator ++ ()
	 {
	 clemu_vector2<_T> tmp1(1);

	    (*this) +=  tmp1;
	     return (*this);
	 }


/*---------------------------------------------------------------------------------------------------------
  operators - 
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector2<_T> operator - (const clemu_vector2<_TT> & _In)
	 {
	   clemu_vector2<_T> tmp;
	      tmp.lo = lo - (_T)_In.lo;
	      tmp.hi = hi - (_T)_In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector2<_T> operator - (_TT _In)
	 {
	 clemu_vector2<_T> tmp;
	 clemu_vector2<_T> tmp1(_In);
	     tmp = *this - tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector2<_T>& operator -= (const clemu_vector2<_TT> & _In)
	 {
        *this = *this - _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector2<_T>& operator -= (_TT _In)
	 {
	 clemu_vector2<_T> tmp1(_In);
        *this = *this - tmp1;
		return(*this);
	 }



	 clemu_vector2<_T>& operator -- ()
	 {
	 clemu_vector2<_T> tmp1(1);

	    (*this) -=  tmp1;
	     return (*this);
	 }


/*---------------------------------------------------------------------------------------------------------
  operators *
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector2<_T> operator * (const clemu_vector2<_TT> & _In)
	 {
	   clemu_vector2<_T> tmp;
	      tmp.lo = lo * (_T)_In.lo;
	      tmp.hi = hi * (_T)_In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector2<_T> operator * (_TT _In)
	 {
	 clemu_vector2<_T> tmp;
	 clemu_vector2<_T> tmp1(_In);
	     tmp = *this * tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector2<_T>& operator *= (const clemu_vector2<_TT> & _In)
	 {
        *this = *this * _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector2<_T>& operator *= (_TT _In)
	 {
	 clemu_vector2<_T> tmp1(_In);
        *this = *this * tmp1;
		return(*this);
	 }



/*---------------------------------------------------------------------------------------------------------
  operators / 
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector2<_T> operator / (const clemu_vector2<_TT> & _In)
	 {
	   clemu_vector2<_T> tmp;
	      tmp.lo = lo / (_T)_In.lo;
	      tmp.hi = hi / (_T)_In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector2<_T> operator / (_TT _In)
	 {
	 clemu_vector2<_T> tmp;
	 clemu_vector2<_T> tmp1(_In);
	     tmp = *this / tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector2<_T>& operator /= (const clemu_vector2<_TT> & _In)
	 {
        *this = *this / _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector2<_T>& operator /= (_TT _In)
	 {
	 clemu_vector2<_T> tmp1(_In);
        *this = *this / tmp1;
		return(*this);
	 }

// SHIFT
/*---------------------------------------------------------------------------------------------------------
  >>
---------------------------------------------------------------------------------------------------------*/

	 clemu_vector2<_T> operator >> (const clemu_vector2<_T> & _In)
	 {
	   clemu_vector2<_T> tmp;
	      tmp.lo = lo >> _In.lo;
	      tmp.hi = hi >> _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector2<_T> operator >> (_TT _In)
	 {
	 clemu_vector2<_T> tmp;
	 clemu_vector2<_T> tmp1(_In);
	     tmp = *this >> tmp1;
         return(tmp);
	 }


	 clemu_vector2<_T>& operator >>= (const clemu_vector2<_T> & _In)
	 {
        *this = *this >> _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector2<_T>& operator >>= (_TT _In)
	 {
	 clemu_vector2<_T> tmp1(_In);
        *this = *this >> tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  <<
---------------------------------------------------------------------------------------------------------*/

	 clemu_vector2<_T> operator << (const clemu_vector2<_T> & _In)
	 {
	   clemu_vector2<_T> tmp;
	      tmp.lo = lo << _In.lo;
	      tmp.hi = hi << _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector2<_T> operator << (_TT _In)
	 {
	 clemu_vector2<_T> tmp;
	 clemu_vector2<_T> tmp1(_In);
	     tmp = *this << tmp1;
         return(tmp);
	 }


	 clemu_vector2<_T>& operator <<= (const clemu_vector2<_T> & _In)
	 {
        *this = *this << _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector2<_T>& operator <<= (_TT _In)
	 {
	 clemu_vector2<_T> tmp1(_In);
        *this = *this << tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  operators % 
---------------------------------------------------------------------------------------------------------*/

	 clemu_vector2<_T> operator % (const clemu_vector2<_T> & _In)
	 {
	   clemu_vector2<_T> tmp;
	      tmp.lo = lo % _In.lo;
	      tmp.hi = hi % _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector2<_T> operator % (_TT _In)
	 {
	 clemu_vector2<_T> tmp;
	 clemu_vector2<_T> tmp1(_In);
	     tmp = *this % tmp1;
         return(tmp);
	 }


	 clemu_vector2<_T>& operator %= (const clemu_vector2<_T> & _In)
	 {
        *this = *this % _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector2<_T>& operator %= (_TT _In)
	 {
	 clemu_vector2<_T> tmp1(_In);
        *this = *this % tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  operators ^
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector2<_T> operator ^ (const clemu_vector2<_T> & _In)
	 {
	   clemu_vector2<_T> tmp;
	      tmp.lo = lo ^ _In.lo;
	      tmp.hi = hi ^ _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector2<_T> operator ^ (_TT _In)
	 {
	 clemu_vector2<_T> tmp;
	 clemu_vector2<_T> tmp1(_In);
	     tmp = *this ^ tmp1;
         return(tmp);
	 }


	 clemu_vector2<_T>& operator ^= (const clemu_vector2<_T> & _In)
	 {
        *this = *this ^ _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector2<_T>& operator ^= (_TT _In)
	 {
	 clemu_vector2<_T> tmp1(_In);
        *this = *this ^ tmp1;
		return(*this);
	 }


/*---------------------------------------------------------------------------------------------------------
  operators &
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector2<_T> operator & (const clemu_vector2<_T> & _In)
	 {
	   clemu_vector2<_T> tmp;
	      tmp.lo = lo & _In.lo;
	      tmp.hi = hi & _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector2<_T> operator & (_TT _In)
	 {
	 clemu_vector2<_T> tmp;
	 clemu_vector2<_T> tmp1(_In);
	     tmp = *this & tmp1;
         return(tmp);
	 }


	 clemu_vector2<_T>& operator &= (const clemu_vector2<_T> & _In)
	 {
        *this = *this & _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector2<_T>& operator &= (_TT _In)
	 {
	 clemu_vector2<_T> tmp1(_In);
        *this = *this & tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  operators |
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector2<_T> operator | (const clemu_vector2<_T> & _In)
	 {
	   clemu_vector2<_T> tmp;
	      tmp.lo = lo | _In.lo;
	      tmp.hi = hi | _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector2<_T> operator | (_TT _In)
	 {
	 clemu_vector2<_T> tmp;
	 clemu_vector2<_T> tmp1(_In);
	     tmp = *this | tmp1;
         return(tmp);
	 }


	 clemu_vector2<_T>& operator |= (const clemu_vector2<_T> & _In)
	 {
        *this = *this | _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector2<_T>& operator |= (_TT _In)
	 {
	 clemu_vector2<_T> tmp1(_In);
        *this = *this | tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  operators ~
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector2<_T> operator ~ (void)
	 {
	   clemu_vector2<_T> tmp;
	      tmp.lo = ~lo;
	      tmp.hi = ~hi;
	      return(tmp);
	 }


/*-------------------------------------------------------------------------------------------------
INTRINSICS
--------------------------------------------------------------------------------------------------*/


/*
BITSELECT
*/
	clemu_vector2<_T> SIMDbitselect(clemu_vector2<_T> _b, clemu_vector2<_T> _c)
	{
	 clemu_vector2<_T> tmp;
	     tmp.lo = bitselect(lo,_b.lo, _c.lo);
	     tmp.hi = bitselect(hi,_b.hi, _c.hi);
         return(tmp);
	}

	 


};



template < class _T> class clemu_vector4 {

protected:
public:

  union{
	  _T s[4];
	  struct {
         _T x;
         _T y;
         _T z;
         _T w;
	  };
	  struct {
         _T s0;
         _T s1;
         _T s2;
         _T s3;
	  };
	  struct {
		  clemu_vector2<_T> lo;
		  clemu_vector2<_T> hi;
	  };
/*
	  struct {
		  clemu_vector2<_T> even;
		  clemu_vector2<_T> odd;
	  };
*/

	};



/*---------------------------------------------------------------------------------------------------------
  operators []
---------------------------------------------------------------------------------------------------------*/
	_T & operator [] ( int _Indx )
	{
		assert(_Indx >=0 && _Indx < 4 );
		return (s[_Indx]);
	}

template <class _TT>
clemu_vector4<_T> fill( _TT val)
{
	for(int i = 0; i < 4; i++)
	{
		s[i] = (_T)val;
	}
   return(*this);
}

	clemu_vector4<_T>( void )
	{
		fill(0);
	}


/*---------------------------------------------------------------------------------------------------------
  copy constructors
---------------------------------------------------------------------------------------------------------*/
template <class _TT>
    clemu_vector4<_T> ( _TT _From )
	{
		fill(_From);
	}


template <class _TT>
    clemu_vector4<_T> ( const clemu_vector4<_TT> & _From )
	{
		for(int i = 0; i < 4; i++)
		{
			s[i] = (_T)_From.s[i];
		}
	}

/*
=
*/
/*
//template <class _TT>
	 clemu_vector4<_T> & operator=(const clemu_vector4<_T> & _In)
	{
       clemu_vector4<_T> tmp(_In);
	   *this = tmp;
	   return(*this);
	}
*/

template <class _TT>
	 clemu_vector4<_T> & operator=(_TT _In)
	{
       clemu_vector4<_T> tmp(_In);
	   *this = tmp;
	   return(*this);
	}


/*---------------------------------------------------------------------------------------------------------
  operators + 
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector4<_T> operator + (const clemu_vector4<_TT> & _In)
	 {
	   clemu_vector4<_T> tmp;
	      tmp.s0 = s0 + (_T)_In.s0;
	      tmp.s1 = s1 + (_T)_In.s1;
	      tmp.s2 = s2 + (_T)_In.s2;
	      tmp.s3 = s3 + (_T)_In.s3;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector4<_T> operator + (_TT _In)
	 {
	 clemu_vector4<_T> tmp;
	 clemu_vector4<_T> tmp1(_In);
	     tmp = *this + tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector4<_T>& operator += (const clemu_vector4<_TT> & _In)
	 {
        *this = *this + _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector4<_T>& operator += (_TT _In)
	 {
	 clemu_vector4<_T> tmp1(_In);
        *this = *this + tmp1;
		return(*this);
	 }

	clemu_vector4<_T>& operator ++ ()
	 {
	 clemu_vector4<_T> tmp1(1);

	    (*this) +=  tmp1;
	     return (*this);
	 }


/*---------------------------------------------------------------------------------------------------------
  operators - 
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector4<_T> operator - (const clemu_vector4<_TT> & _In)
	 {
	   clemu_vector4<_T> tmp;
	      tmp.s0 = s0 - (_T)_In.s0;
	      tmp.s1 = s1 - (_T)_In.s1;
	      tmp.s2 = s2 - (_T)_In.s2;
	      tmp.s3 = s3 - (_T)_In.s3;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector4<_T> operator - (_TT _In)
	 {
	 clemu_vector4<_T> tmp;
	 clemu_vector4<_T> tmp1(_In);
	     tmp = *this - tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector4<_T>& operator -= (const clemu_vector4<_TT> & _In)
	 {
        *this = *this - _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector4<_T>& operator -= (_TT _In)
	 {
	 clemu_vector4<_T> tmp1(_In);
        *this = *this - tmp1;
		return(*this);
	 }



	 clemu_vector4<_T>& operator -- ()
	 {
	 clemu_vector4<_T> tmp1(1);

	    (*this) -=  tmp1;
	     return (*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  operators *
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector4<_T> operator * (const clemu_vector4<_TT> & _In)
	 {
	   clemu_vector4<_T> tmp;
	      tmp.s0 = s0 * (_T)_In.s0;
	      tmp.s1 = s1 * (_T)_In.s1;
	      tmp.s2 = s2 * (_T)_In.s2;
	      tmp.s3 = s3 * (_T)_In.s3;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector4<_T> operator * (_TT _In)
	 {
	 clemu_vector4<_T> tmp;
	 clemu_vector4<_T> tmp1(_In);
	     tmp = *this * tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector4<_T>& operator *= (const clemu_vector4<_TT> & _In)
	 {
        *this = *this * _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector4<_T>& operator *= (_TT _In)
	 {
	 clemu_vector4<_T> tmp1(_In);
        *this = *this * tmp1;
		return(*this);
	 }



/*---------------------------------------------------------------------------------------------------------
  operators / 
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector4<_T> operator / (const clemu_vector4<_TT> & _In)
	 {
	   clemu_vector4<_T> tmp;
	      tmp.s0 = s0 / (_T)_In.s0;
	      tmp.s1 = s1 / (_T)_In.s1;
	      tmp.s2 = s2 / (_T)_In.s2;
	      tmp.s3 = s3 / (_T)_In.s3;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector4<_T> operator / (_TT _In)
	 {
	 clemu_vector4<_T> tmp;
	 clemu_vector4<_T> tmp1(_In);
	     tmp = *this / tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector4<_T>& operator /= (const clemu_vector4<_TT> & _In)
	 {
        *this = *this / _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector4<_T>& operator /= (_TT _In)
	 {
	 clemu_vector4<_T> tmp1(_In);
        *this = *this / tmp1;
		return(*this);
	 }

// SHIFT
/*---------------------------------------------------------------------------------------------------------
  >>
---------------------------------------------------------------------------------------------------------*/

	 clemu_vector4<_T> operator >> (const clemu_vector4<_T> & _In)
	 {
	   clemu_vector4<_T> tmp;
	      tmp.lo = lo >> _In.lo;
	      tmp.hi = hi >> _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector4<_T> operator >> (_TT _In)
	 {
	 clemu_vector4<_T> tmp;
	 clemu_vector4<_T> tmp1(_In);
	     tmp = *this >> tmp1;
         return(tmp);
	 }


	 clemu_vector4<_T>& operator >>= (const clemu_vector4<_T> & _In)
	 {
        *this = *this >> _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector4<_T>& operator >>= (_TT _In)
	 {
	 clemu_vector4<_T> tmp1(_In);
        *this = *this >> tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  <<
---------------------------------------------------------------------------------------------------------*/

	 clemu_vector4<_T> operator << (const clemu_vector4<_T> & _In)
	 {
	   clemu_vector4<_T> tmp;
	      tmp.lo = lo << _In.lo;
	      tmp.hi = hi << _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector4<_T> operator << (_TT _In)
	 {
	 clemu_vector4<_T> tmp;
	 clemu_vector4<_T> tmp1(_In);
	     tmp = *this << tmp1;
         return(tmp);
	 }


	 clemu_vector4<_T>& operator <<= (const clemu_vector4<_T> & _In)
	 {
        *this = *this << _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector4<_T>& operator <<= (_TT _In)
	 {
	 clemu_vector4<_T> tmp1(_In);
        *this = *this << tmp1;
		return(*this);
	 }



/*---------------------------------------------------------------------------------------------------------
  operators % 
---------------------------------------------------------------------------------------------------------*/

	 clemu_vector4<_T> operator % (const clemu_vector4<_T> & _In)
	 {
	   clemu_vector4<_T> tmp;
	      tmp.lo = lo % _In.lo;
	      tmp.hi = hi % _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector4<_T> operator % (_TT _In)
	 {
	 clemu_vector4<_T> tmp;
	 clemu_vector4<_T> tmp1(_In);
	     tmp = *this % tmp1;
         return(tmp);
	 }


	 clemu_vector4<_T>& operator %= (const clemu_vector4<_T> & _In)
	 {
        *this = *this % _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector4<_T>& operator %= (_TT _In)
	 {
	 clemu_vector4<_T> tmp1(_In);
        *this = *this % tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  operators ^
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector4<_T> operator ^ (const clemu_vector4<_T> & _In)
	 {
	   clemu_vector4<_T> tmp;
	      tmp.lo = lo ^ _In.lo;
	      tmp.hi = hi ^ _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector4<_T> operator ^ (_TT _In)
	 {
	 clemu_vector4<_T> tmp;
	 clemu_vector4<_T> tmp1(_In);
	     tmp = *this ^ tmp1;
         return(tmp);
	 }


	 clemu_vector4<_T>& operator ^= (const clemu_vector4<_T> & _In)
	 {
        *this = *this ^ _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector4<_T>& operator ^= (_TT _In)
	 {
	 clemu_vector4<_T> tmp1(_In);
        *this = *this ^ tmp1;
		return(*this);
	 }


/*---------------------------------------------------------------------------------------------------------
  operators &
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector4<_T> operator & (const clemu_vector4<_T> & _In)
	 {
	   clemu_vector4<_T> tmp;
	      tmp.lo = lo & _In.lo;
	      tmp.hi = hi & _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector4<_T> operator & (_TT _In)
	 {
	 clemu_vector4<_T> tmp;
	 clemu_vector4<_T> tmp1(_In);
	     tmp = *this & tmp1;
         return(tmp);
	 }


	 clemu_vector4<_T>& operator &= (const clemu_vector4<_T> & _In)
	 {
        *this = *this & _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector4<_T>& operator &= (_TT _In)
	 {
	 clemu_vector4<_T> tmp1(_In);
        *this = *this & tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  operators |
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector4<_T> operator | (const clemu_vector4<_T> & _In)
	 {
	   clemu_vector4<_T> tmp;
	      tmp.lo = lo | _In.lo;
	      tmp.hi = hi | _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector4<_T> operator | (_TT _In)
	 {
	 clemu_vector4<_T> tmp;
	 clemu_vector4<_T> tmp1(_In);
	     tmp = *this | tmp1;
         return(tmp);
	 }


	 clemu_vector4<_T>& operator |= (const clemu_vector4<_T> & _In)
	 {
        *this = *this | _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector4<_T>& operator |= (_TT _In)
	 {
	 clemu_vector4<_T> tmp1(_In);
        *this = *this | tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  operators ~
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector4<_T> operator ~ (void)
	 {
	   clemu_vector4<_T> tmp;
	      tmp.lo = ~lo;
	      tmp.hi = ~hi;
	      return(tmp);
	 }



/*-------------------------------------------------------------------------------------------------
INTRINSICS
--------------------------------------------------------------------------------------------------*/


/*
BITSELECT
*/
	clemu_vector4<_T> SIMDbitselect(clemu_vector4<_T> _b, clemu_vector4<_T> _c)
	{
	 clemu_vector4<_T> tmp;
	     tmp.lo = bitselect(lo,_b.lo, _c.lo);
	     tmp.hi = bitselect(hi,_b.hi, _c.hi);
         return(tmp);
	}





};



template < class _T> class clemu_vector8 {

protected:
public:

  union{
	  _T s[8];
	  struct {
         _T s0;
         _T s1;
         _T s2;
         _T s3;
         _T s4;
         _T s5;
         _T s6;
         _T s7;
	  };
	  struct {
		  clemu_vector4<_T> lo;
		  clemu_vector4<_T> hi;
	  };
/*
	  struct {
		  clemu_vector4<_T> even;
		  clemu_vector4<_T> hi;
	  };
*/
	};



/*---------------------------------------------------------------------------------------------------------
  operators []
---------------------------------------------------------------------------------------------------------*/
	_T & operator [] ( int _Indx )
	{
		assert(_Indx >=0 && _Indx < 8 );
		return (s[_Indx]);
	}
template <class _TT>
clemu_vector8<_T> fill(_TT val)
{
	for(int i = 0; i < 8; i++)
	{
      s[i] = (_T)val;
	}
   return(*this);
}

	clemu_vector8<_T>( void )
	{
		fill(0);
	}


/*---------------------------------------------------------------------------------------------------------
  copy constructors
---------------------------------------------------------------------------------------------------------*/
template <class _TT>
    clemu_vector8<_T> ( _TT _From )
	{
		fill(_From);
	}


template <class _TT>
    clemu_vector8<_T> ( const clemu_vector8<_TT> & _From )
	{
		(*this).s0 = (_T)_From.s0;
		(*this).s1 = (_T)_From.s1;
		(*this).s2 = (_T)_From.s2;
		(*this).s3 = (_T)_From.s3;
		(*this).s4 = (_T)_From.s4;
		(*this).s5 = (_T)_From.s5;
		(*this).s6 = (_T)_From.s6;
		(*this).s7 = (_T)_From.s7;

	}


/*
=
*/
/*
//template <class _TT>
	 clemu_vector8<_T> & operator=(const clemu_vector8<_T> & _In)
	{
       clemu_vector8<_T> tmp(_In);
	   *this = tmp;
	   return(*this);
	}
*/

template <class _TT>
	 clemu_vector8<_T> & operator=(_TT _In)
	{
       clemu_vector8<_T> tmp(_In);
	   *this = tmp;
	   return(*this);
	}


/*---------------------------------------------------------------------------------------------------------
  operators + 
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector8<_T> operator + (const clemu_vector8<_TT> & _In)
	 {
	   clemu_vector8<_T> tmp;
	      tmp.s0 = s0 + (_T)_In.s0;
	      tmp.s1 = s1 + (_T)_In.s1;
	      tmp.s2 = s2 + (_T)_In.s2;
	      tmp.s3 = s3 + (_T)_In.s3;
	      tmp.s4 = s4 + (_T)_In.s4;
	      tmp.s5 = s5 + (_T)_In.s5;
	      tmp.s6 = s6 + (_T)_In.s6;
	      tmp.s7 = s7 + (_T)_In.s7;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector8<_T> operator + (_TT _In)
	 {
	 clemu_vector8<_T> tmp;
	 clemu_vector8<_T> tmp1(_In);
	     tmp = *this + tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector8<_T>& operator += (const clemu_vector8<_TT> & _In)
	 {
        *this = *this + _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector8<_T>& operator += (_TT _In)
	 {
	 clemu_vector8<_T> tmp1(_In);
        *this = *this + tmp1;
		return(*this);
	 }

	clemu_vector8<_T>& operator ++ ()
	 {
	 clemu_vector8<_T> tmp1(1);

	    (*this) +=  tmp1;
	     return (*this);
	 }


/*---------------------------------------------------------------------------------------------------------
  operators - 
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector8<_T> operator - (const clemu_vector8<_TT> & _In)
	 {
	   clemu_vector8<_T> tmp;
	      tmp.s0 = s0 - (_T)_In.s0;
	      tmp.s1 = s1 - (_T)_In.s1;
	      tmp.s2 = s2 - (_T)_In.s2;
	      tmp.s3 = s3 - (_T)_In.s3;
	      tmp.s4 = s4 - (_T)_In.s4;
	      tmp.s5 = s5 - (_T)_In.s5;
	      tmp.s6 = s6 - (_T)_In.s6;
	      tmp.s7 = s7 - (_T)_In.s7;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector8<_T> operator - (_TT _In)
	 {
	 clemu_vector8<_T> tmp;
	 clemu_vector8<_T> tmp1(_In);
	     tmp = *this - tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector8<_T>& operator -= (const clemu_vector8<_TT> & _In)
	 {
        *this = *this - _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector8<_T>& operator -= (_TT _In)
	 {
	 clemu_vector8<_T> tmp1(_In);
        *this = *this - tmp1;
		return(*this);
	 }


	 clemu_vector8<_T>& operator -- ()
	 {
	 clemu_vector8<_T> tmp1(1);

	    (*this) -=  tmp1;
	     return (*this);
	 }



/*---------------------------------------------------------------------------------------------------------
  operators *
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector8<_T> operator * (const clemu_vector8<_TT> & _In)
	 {
	   clemu_vector8<_T> tmp;
	      tmp.s0 = s0 * (_T)_In.s0;
	      tmp.s1 = s1 * (_T)_In.s1;
	      tmp.s2 = s2 * (_T)_In.s2;
	      tmp.s3 = s3 * (_T)_In.s3;
	      tmp.s4 = s4 * (_T)_In.s4;
	      tmp.s5 = s5 * (_T)_In.s5;
	      tmp.s6 = s6 * (_T)_In.s6;
	      tmp.s7 = s7 * (_T)_In.s7;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector8<_T> operator * (_TT _In)
	 {
	 clemu_vector8<_T> tmp;
	 clemu_vector8<_T> tmp1(_In);
	     tmp = *this * tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector8<_T>& operator *= (const clemu_vector8<_TT> & _In)
	 {
        *this = *this * _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector8<_T>& operator *= (_TT _In)
	 {
	 clemu_vector8<_T> tmp1(_In);
        *this = *this * tmp1;
		return(*this);
	 }



/*---------------------------------------------------------------------------------------------------------
  operators / 
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector8<_T> operator / (const clemu_vector8<_TT> & _In)
	 {
	   clemu_vector8<_T> tmp;
	      tmp.s0 = s0 / (_T)_In.s0;
	      tmp.s1 = s1 / (_T)_In.s1;
	      tmp.s2 = s2 / (_T)_In.s2;
	      tmp.s3 = s3 / (_T)_In.s3;
	      tmp.s4 = s4 / (_T)_In.s4;
	      tmp.s5 = s5 / (_T)_In.s5;
	      tmp.s6 = s6 / (_T)_In.s6;
	      tmp.s7 = s7 / (_T)_In.s7;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector8<_T> operator / (_TT _In)
	 {
	 clemu_vector8<_T> tmp;
	 clemu_vector8<_T> tmp1(_In);
	     tmp = *this / tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector8<_T>& operator /= (const clemu_vector8<_TT> & _In)
	 {
        *this = *this / _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector8<_T>& operator /= (_TT _In)
	 {
	 clemu_vector8<_T> tmp1(_In);
        *this = *this / tmp1;
		return(*this);
	 }

// SHIFT
/*---------------------------------------------------------------------------------------------------------
  >>
---------------------------------------------------------------------------------------------------------*/

	 clemu_vector8<_T> operator >> (const clemu_vector8<_T> & _In)
	 {
	   clemu_vector8<_T> tmp;
	      tmp.lo = lo >> _In.lo;
	      tmp.hi = hi >> _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector8<_T> operator >> (_TT _In)
	 {
	 clemu_vector8<_T> tmp;
	 clemu_vector8<_T> tmp1(_In);
	     tmp = *this >> tmp1;
         return(tmp);
	 }


	 clemu_vector8<_T>& operator >>= (const clemu_vector8<_T> & _In)
	 {
        *this = *this >> _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector8<_T>& operator >>= (_TT _In)
	 {
	 clemu_vector8<_T> tmp1(_In);
        *this = *this >> tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  <<
---------------------------------------------------------------------------------------------------------*/

	 clemu_vector8<_T> operator << (const clemu_vector8<_T> & _In)
	 {
	   clemu_vector8<_T> tmp;
	      tmp.lo = lo << _In.lo;
	      tmp.hi = hi << _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector8<_T> operator << (_TT _In)
	 {
	 clemu_vector8<_T> tmp;
	 clemu_vector8<_T> tmp1(_In);
	     tmp = *this << tmp1;
         return(tmp);
	 }


	 clemu_vector8<_T>& operator <<= (const clemu_vector8<_T> & _In)
	 {
        *this = *this << _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector8<_T>& operator <<= (_TT _In)
	 {
	 clemu_vector8<_T> tmp1(_In);
        *this = *this << tmp1;
		return(*this);
	 }


/*---------------------------------------------------------------------------------------------------------
  operators % 
---------------------------------------------------------------------------------------------------------*/

	 clemu_vector8<_T> operator % (const clemu_vector8<_T> & _In)
	 {
	   clemu_vector8<_T> tmp;
	      tmp.lo = lo % _In.lo;
	      tmp.hi = hi % _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector8<_T> operator % (_TT _In)
	 {
	 clemu_vector8<_T> tmp;
	 clemu_vector8<_T> tmp1(_In);
	     tmp = *this % tmp1;
         return(tmp);
	 }


	 clemu_vector8<_T>& operator %= (const clemu_vector8<_T> & _In)
	 {
        *this = *this % _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector8<_T>& operator %= (_TT _In)
	 {
	 clemu_vector8<_T> tmp1(_In);
        *this = *this % tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  operators ^
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector8<_T> operator ^ (const clemu_vector8<_T> & _In)
	 {
	   clemu_vector8<_T> tmp;
	      tmp.lo = lo ^ _In.lo;
	      tmp.hi = hi ^ _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector8<_T> operator ^ (_TT _In)
	 {
	 clemu_vector8<_T> tmp;
	 clemu_vector8<_T> tmp1(_In);
	     tmp = *this ^ tmp1;
         return(tmp);
	 }


	 clemu_vector8<_T>& operator ^= (const clemu_vector8<_T> & _In)
	 {
        *this = *this ^ _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector8<_T>& operator ^= (_TT _In)
	 {
	 clemu_vector8<_T> tmp1(_In);
        *this = *this ^ tmp1;
		return(*this);
	 }


/*---------------------------------------------------------------------------------------------------------
  operators &
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector8<_T> operator & (const clemu_vector8<_T> & _In)
	 {
	   clemu_vector8<_T> tmp;
	      tmp.lo = lo & _In.lo;
	      tmp.hi = hi & _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector8<_T> operator & (_TT _In)
	 {
	 clemu_vector8<_T> tmp;
	 clemu_vector8<_T> tmp1(_In);
	     tmp = *this & tmp1;
         return(tmp);
	 }


	 clemu_vector8<_T>& operator &= (const clemu_vector8<_T> & _In)
	 {
        *this = *this & _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector8<_T>& operator &= (_TT _In)
	 {
	 clemu_vector8<_T> tmp1(_In);
        *this = *this & tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  operators |
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector8<_T> operator | (const clemu_vector8<_T> & _In)
	 {
	   clemu_vector8<_T> tmp;
	      tmp.lo = lo | _In.lo;
	      tmp.hi = hi | _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector8<_T> operator | (_TT _In)
	 {
	 clemu_vector8<_T> tmp;
	 clemu_vector8<_T> tmp1(_In);
	     tmp = *this | tmp1;
         return(tmp);
	 }


	 clemu_vector8<_T>& operator |= (const clemu_vector8<_T> & _In)
	 {
        *this = *this | _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector8<_T>& operator |= (_TT _In)
	 {
	 clemu_vector8<_T> tmp1(_In);
        *this = *this | tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  operators ~
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector8<_T> operator ~ (void)
	 {
	   clemu_vector8<_T> tmp;
	      tmp.lo = ~lo;
	      tmp.hi = ~hi;
	      return(tmp);
	 }



/*-------------------------------------------------------------------------------------------------
INTRINSICS
--------------------------------------------------------------------------------------------------*/

/*
BITSELECT
*/
	clemu_vector8<_T> SIMDbitselect(clemu_vector8<_T> _b, clemu_vector8<_T> _c)
	{
	 clemu_vector8<_T> tmp;
	     tmp.lo = bitselect(lo,_b.lo, _c.lo);
	     tmp.hi = bitselect(hi,_b.hi, _c.hi);
         return(tmp);
	}





};



template < class _T> class clemu_vector16 {

protected:
public:

  union{
	  _T s[16];
	  struct {
         _T s0;
         _T s1;
         _T s2;
         _T s3;
         _T s4;
         _T s5;
         _T s6;
         _T s7;
         _T s8;
         _T s9;
         _T sa;
         _T sb;
         _T sc;
         _T sd;
         _T se;
         _T sf;
	  };
	  struct {
		  clemu_vector8<_T> lo;
		  clemu_vector8<_T> hi;
	  };
/*
	  struct {
		  clemu_vector8<_T> even;
		  clemu_vector8<_T> odd;
	  };
*/
	};



/*---------------------------------------------------------------------------------------------------------
  operators []
---------------------------------------------------------------------------------------------------------*/
	_T & operator [] ( int _Indx )
	{
		assert(_Indx >=0 && _Indx < 16 );
		return (s[_Indx]);
	}

template <typename _TT>
clemu_vector16<_T> fill(_TT val)
{
	for(int i = 0; i < 16; i++)
	{
		s[i] = (_T)val;
	}
   return(*this);
}


	clemu_vector16<_T>( void )
	{
		fill(0);
	}


/*---------------------------------------------------------------------------------------------------------
  copy constructors
---------------------------------------------------------------------------------------------------------*/
template <class _TT>
    clemu_vector16<_T> ( _TT _From )
	{
		fill(_From);
	}


template <class _TT>
    clemu_vector16<_T> ( const clemu_vector16<_TT> & _From )
	{
		(*this).s0 = (_T)_From.s0;
		(*this).s1 = (_T)_From.s1;
		(*this).s2 = (_T)_From.s2;
		(*this).s3 = (_T)_From.s3;
		(*this).s4 = (_T)_From.s4;
		(*this).s5 = (_T)_From.s5;
		(*this).s6 = (_T)_From.s6;
		(*this).s7 = (_T)_From.s7;
		(*this).s8 = (_T)_From.s8;
		(*this).s9 = (_T)_From.s9;
		(*this).sa = (_T)_From.sa;
		(*this).sb = (_T)_From.sb;
		(*this).sc = (_T)_From.sc;
		(*this).sd = (_T)_From.sd;
		(*this).se = (_T)_From.se;
		(*this).sf = (_T)_From.sf;


	}


/*
=
*/
/*
//template <class _TT>
	 clemu_vector16<_T> & operator=(const clemu_vector16<_T> & _In)
	{
       clemu_vector16<_T> tmp(_In);
	   *this = tmp;
	   return(*this);
	}

*/


template <class _TT>
	 clemu_vector16<_T> & operator=(_TT _In)
	{
       clemu_vector16<_T> tmp(_In);
	   *this = tmp;
	   return(*this);
	}


/*---------------------------------------------------------------------------------------------------------
  operators + 
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector16<_T> operator + (const clemu_vector16<_TT> & _In)
	 {
	   clemu_vector16<_T> tmp;
	      tmp.s0 = s0 + (_T)_In.s0;
	      tmp.s1 = s1 + (_T)_In.s1;
	      tmp.s2 = s2 + (_T)_In.s2;
	      tmp.s3 = s3 + (_T)_In.s3;
	      tmp.s4 = s4 + (_T)_In.s4;
	      tmp.s5 = s5 + (_T)_In.s5;
	      tmp.s6 = s6 + (_T)_In.s6;
	      tmp.s7 = s7 + (_T)_In.s7;
	      tmp.s8 = s8 + (_T)_In.s8;
	      tmp.s9 = s9 + (_T)_In.s9;
	      tmp.sa = sa + (_T)_In.sa;
	      tmp.sb = sb + (_T)_In.sb;
	      tmp.sc = sc + (_T)_In.sc;
	      tmp.sd = sd + (_T)_In.sd;
	      tmp.se = se + (_T)_In.se;
	      tmp.sf = sf + (_T)_In.sf;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector16<_T> operator + (_TT _In)
	 {
	 clemu_vector16<_T> tmp;
	 clemu_vector16<_T> tmp1(_In);
	     tmp = *this + tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector16<_T>& operator += (const clemu_vector16<_TT> & _In)
	 {
        *this = *this + _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector16<_T>& operator += (_TT _In)
	 {
	 clemu_vector16<_T> tmp1(_In);
        *this = *this + tmp1;
		return(*this);
	 }

	clemu_vector16<_T>& operator ++ ()
	 {
	 clemu_vector16<_T> tmp1(1);

	    (*this) +=  tmp1;
	     return (*this);
	 }


/*---------------------------------------------------------------------------------------------------------
  operators - 
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector16<_T> operator - (const clemu_vector16<_TT> & _In)
	 {
	   clemu_vector16<_T> tmp;
	      tmp.s0 = s0 - (_T)_In.s0;
	      tmp.s1 = s1 - (_T)_In.s1;
	      tmp.s2 = s2 - (_T)_In.s2;
	      tmp.s3 = s3 - (_T)_In.s3;
	      tmp.s4 = s4 - (_T)_In.s4;
	      tmp.s5 = s5 - (_T)_In.s5;
	      tmp.s6 = s6 - (_T)_In.s6;
	      tmp.s7 = s7 - (_T)_In.s7;
	      tmp.s8 = s8 - (_T)_In.s8;
	      tmp.s9 = s9 - (_T)_In.s9;
	      tmp.sa = sa - (_T)_In.sa;
	      tmp.sb = sb - (_T)_In.sb;
	      tmp.sc = sc - (_T)_In.sc;
	      tmp.sd = sd - (_T)_In.sd;
	      tmp.se = se - (_T)_In.se;
	      tmp.sf = sf - (_T)_In.sf;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector16<_T> operator - (_TT _In)
	 {
	 clemu_vector16<_T> tmp;
	 clemu_vector16<_T> tmp1(_In);
	     tmp = *this - tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector16<_T>& operator -= (const clemu_vector16<_TT> & _In)
	 {
        *this = *this - _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector16<_T>& operator -= (_TT _In)
	 {
	 clemu_vector16<_T> tmp1(_In);
        *this = *this - tmp1;
		return(*this);
	 }



	 clemu_vector16<_T>& operator -- ()
	 {
	 clemu_vector16<_T> tmp1(1);

	    (*this) -=  tmp1;
	     return (*this);
	 }




/*---------------------------------------------------------------------------------------------------------
  operators *
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector16<_T> operator * (const clemu_vector16<_TT> & _In)
	 {
	   clemu_vector16<_T> tmp;
	      tmp.s0 = s0 * (_T)_In.s0;
	      tmp.s1 = s1 * (_T)_In.s1;
	      tmp.s2 = s2 * (_T)_In.s2;
	      tmp.s3 = s3 * (_T)_In.s3;
	      tmp.s4 = s4 * (_T)_In.s4;
	      tmp.s5 = s5 * (_T)_In.s5;
	      tmp.s6 = s6 * (_T)_In.s6;
	      tmp.s7 = s7 * (_T)_In.s7;
	      tmp.s8 = s8 * (_T)_In.s8;
	      tmp.s9 = s9 * (_T)_In.s9;
	      tmp.sa = sa * (_T)_In.sa;
	      tmp.sb = sb * (_T)_In.sb;
	      tmp.sc = sc * (_T)_In.sc;
	      tmp.sd = sd * (_T)_In.sd;
	      tmp.se = se * (_T)_In.se;
	      tmp.sf = sf * (_T)_In.sf;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector16<_T> operator * (_TT _In)
	 {
	 clemu_vector16<_T> tmp;
	 clemu_vector16<_T> tmp1(_In);
	     tmp = *this * tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector16<_T>& operator *= (const clemu_vector16<_TT> & _In)
	 {
        *this = *this * _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector16<_T>& operator *= (_TT _In)
	 {
	 clemu_vector16<_T> tmp1(_In);
        *this = *this * tmp1;
		return(*this);
	 }



/*---------------------------------------------------------------------------------------------------------
  operators / 
---------------------------------------------------------------------------------------------------------*/

template <class _TT>
	 clemu_vector16<_T> operator / (const clemu_vector16<_TT> & _In)
	 {
	   clemu_vector16<_T> tmp;
	      tmp.s0 = s0 / (_T)_In.s0;
	      tmp.s1 = s1 / (_T)_In.s1;
	      tmp.s2 = s2 / (_T)_In.s2;
	      tmp.s3 = s3 / (_T)_In.s3;
	      tmp.s4 = s4 / (_T)_In.s4;
	      tmp.s5 = s5 / (_T)_In.s5;
	      tmp.s6 = s6 / (_T)_In.s6;
	      tmp.s7 = s7 / (_T)_In.s7;
	      tmp.s8 = s8 / (_T)_In.s8;
	      tmp.s9 = s9 / (_T)_In.s9;
	      tmp.sa = sa / (_T)_In.sa;
	      tmp.sb = sb / (_T)_In.sb;
	      tmp.sc = sc / (_T)_In.sc;
	      tmp.sd = sd / (_T)_In.sd;
	      tmp.se = se / (_T)_In.se;
	      tmp.sf = sf / (_T)_In.sf;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector16<_T> operator / (_TT _In)
	 {
	 clemu_vector16<_T> tmp;
	 clemu_vector16<_T> tmp1(_In);
	     tmp = *this / tmp1;
         return(tmp);
	 }


template <class _TT>
	 clemu_vector16<_T>& operator /= (const clemu_vector16<_TT> & _In)
	 {
        *this = *this / _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector16<_T>& operator /= (_TT _In)
	 {
	 clemu_vector16<_T> tmp1(_In);
        *this = *this / tmp1;
		return(*this);
	 }


// SHIFT
/*---------------------------------------------------------------------------------------------------------
  >>
---------------------------------------------------------------------------------------------------------*/

	 clemu_vector16<_T> operator >> (const clemu_vector16<_T> & _In)
	 {
	   clemu_vector16<_T> tmp;
	      tmp.lo = lo >> _In.lo;
	      tmp.hi = hi >> _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector16<_T> operator >> (_TT _In)
	 {
	 clemu_vector16<_T> tmp;
	 clemu_vector16<_T> tmp1(_In);
	     tmp = *this >> tmp1;
         return(tmp);
	 }


	 clemu_vector16<_T>& operator >>= (const clemu_vector16<_T> & _In)
	 {
        *this = *this >> _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector16<_T>& operator >>= (_TT _In)
	 {
	 clemu_vector16<_T> tmp1(_In);
        *this = *this >> tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  <<
---------------------------------------------------------------------------------------------------------*/

	 clemu_vector16<_T> operator << (const clemu_vector16<_T> & _In)
	 {
	   clemu_vector16<_T> tmp;
	      tmp.lo = lo << _In.lo;
	      tmp.hi = hi << _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector16<_T> operator << (_TT _In)
	 {
	 clemu_vector16<_T> tmp;
	 clemu_vector16<_T> tmp1(_In);
	     tmp = *this << tmp1;
         return(tmp);
	 }


	 clemu_vector16<_T>& operator <<= (const clemu_vector16<_T> & _In)
	 {
        *this = *this << _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector16<_T>& operator <<= (_TT _In)
	 {
	 clemu_vector16<_T> tmp1(_In);
        *this = *this << tmp1;
		return(*this);
	 }


/*---------------------------------------------------------------------------------------------------------
  operators % 
---------------------------------------------------------------------------------------------------------*/

	 clemu_vector16<_T> operator % (const clemu_vector16<_T> & _In)
	 {
	   clemu_vector16<_T> tmp;
	      tmp.lo = lo % _In.lo;
	      tmp.hi = hi % _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector16<_T> operator % (_TT _In)
	 {
	 clemu_vector16<_T> tmp;
	 clemu_vector16<_T> tmp1(_In);
	     tmp = *this % tmp1;
         return(tmp);
	 }


	 clemu_vector16<_T>& operator %= (const clemu_vector16<_T> & _In)
	 {
        *this = *this % _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector16<_T>& operator %= (_TT _In)
	 {
	 clemu_vector16<_T> tmp1(_In);
        *this = *this % tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  operators ^
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector16<_T> operator ^ (const clemu_vector16<_T> & _In)
	 {
	   clemu_vector16<_T> tmp;
	      tmp.lo = lo ^ _In.lo;
	      tmp.hi = hi ^ _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector16<_T> operator ^ (_TT _In)
	 {
	 clemu_vector16<_T> tmp;
	 clemu_vector16<_T> tmp1(_In);
	     tmp = *this ^ tmp1;
         return(tmp);
	 }


	 clemu_vector16<_T>& operator ^= (const clemu_vector16<_T> & _In)
	 {
        *this = *this ^ _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector16<_T>& operator ^= (_TT _In)
	 {
	 clemu_vector16<_T> tmp1(_In);
        *this = *this ^ tmp1;
		return(*this);
	 }


/*---------------------------------------------------------------------------------------------------------
  operators &
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector16<_T> operator & (const clemu_vector16<_T> & _In)
	 {
	   clemu_vector16<_T> tmp;
	      tmp.lo = lo & _In.lo;
	      tmp.hi = hi & _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector16<_T> operator & (_TT _In)
	 {
	 clemu_vector16<_T> tmp;
	 clemu_vector16<_T> tmp1(_In);
	     tmp = *this & tmp1;
         return(tmp);
	 }


	 clemu_vector16<_T>& operator &= (const clemu_vector16<_T> & _In)
	 {
        *this = *this & _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector16<_T>& operator &= (_TT _In)
	 {
	 clemu_vector16<_T> tmp1(_In);
        *this = *this & tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  operators |
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector16<_T> operator | (const clemu_vector16<_T> & _In)
	 {
	   clemu_vector16<_T> tmp;
	      tmp.lo = lo | _In.lo;
	      tmp.hi = hi | _In.hi;
	      return(tmp);
	 }

template <class _TT>
	 clemu_vector16<_T> operator | (_TT _In)
	 {
	 clemu_vector16<_T> tmp;
	 clemu_vector16<_T> tmp1(_In);
	     tmp = *this | tmp1;
         return(tmp);
	 }


	 clemu_vector16<_T>& operator |= (const clemu_vector16<_T> & _In)
	 {
        *this = *this | _In;
		return(*this);
	 }

template <class _TT>
	 clemu_vector16<_T>& operator |= (_TT _In)
	 {
	 clemu_vector16<_T> tmp1(_In);
        *this = *this | tmp1;
		return(*this);
	 }

/*---------------------------------------------------------------------------------------------------------
  operators ~
---------------------------------------------------------------------------------------------------------*/
	 clemu_vector16<_T> operator ~ (void)
	 {
	   clemu_vector16<_T> tmp;
	      tmp.lo = ~lo;
	      tmp.hi = ~hi;
	      return(tmp);
	 }


/*-------------------------------------------------------------------------------------------------
INTRINSICS
--------------------------------------------------------------------------------------------------*/



/*
BITSELECT
*/
	clemu_vector16<_T> SIMDbitselect(clemu_vector16<_T> _b, clemu_vector16<_T> _c)
	{
	 clemu_vector16<_T> tmp;
	     tmp.lo = bitselect(lo,_b.lo, _c.lo);
	     tmp.hi = bitselect(hi,_b.hi, _c.hi);
         return(tmp);
	}



};




// VECTORS
/*---------------------------------------------------------------------------------------------------------

---------------------------------------------------------------------------------------------------------*/
//typedef  vector<float, 4> float4;
//typedef  vector<float, 3> float3;
//typedef  vector<float, 2> float2;
//typedef  vector<float, 1> float1;
//typedef  float float1;
//typedef  vector<int, 4> int4;
//typedef  vector<int, 3> int3;
//typedef  vector<int, 2> int2;
//typedef  vector<int, 1> int1;
//typedef  int int1;

//typedef  vector<unsigned int, 4> uint4;
//typedef  vector<unsigned int, 3> uint3;
//typedef  vector<unsigned int, 2> uint2;
//typedef  vector<int, 1> int1;
//typedef unsigned int uint1;


//typedef  vector<bool, 4> bool4;
//typedef  vector<bool, 3> bool3;
//typedef  vector<bool, 2> bool2;
//typedef  vector<bool, 1> bool1;
//typedef  bool bool1;


//typedef  vector<double, 4> double4;
//typedef  vector<double, 3> double3;
//typedef  vector<double, 2> double2;
//typedef  vector<double, 1> double1;
//typedef  double  double1;


typedef clemu_vector2<uchar> uchar2;
typedef clemu_vector2<char> char2;
typedef clemu_vector2<short> short2;
typedef clemu_vector2<ushort> ushort2;
typedef clemu_vector2<int> int2;
typedef clemu_vector2<uint> uint2;
typedef clemu_vector2<__int64> __LONG2;
typedef clemu_vector2<unsigned __int64> __ULONG2;
typedef clemu_vector2<float> float2;
typedef clemu_vector2<double> double2;


typedef clemu_vector4<uchar> uchar4;
typedef clemu_vector4<char> char4;
typedef clemu_vector4<short> short4;
typedef clemu_vector4<ushort> ushort4;
typedef clemu_vector4<int> int4;
typedef clemu_vector4<uint> uint4;
typedef clemu_vector4<__int64> __LONG4;
typedef clemu_vector4<unsigned __int64> __ULONG4;
typedef clemu_vector4<float> float4;
typedef clemu_vector4<double> double4;


typedef clemu_vector8<uchar> uchar8;
typedef clemu_vector8<char> char8;
typedef clemu_vector8<short> short8;
typedef clemu_vector8<ushort> ushort8;
typedef clemu_vector8<int> int8;
typedef clemu_vector8<uint> uint8;
typedef clemu_vector8<__int64> __LONG8;
typedef clemu_vector8<unsigned __int64> __ULONG8;
typedef clemu_vector8<float> float8;
typedef clemu_vector8<double> double8;


typedef clemu_vector16<uchar> uchar16;
typedef clemu_vector16<char> char16;
typedef clemu_vector16<short> short16;
typedef clemu_vector16<ushort> ushort16;
typedef clemu_vector16<int> int16;
typedef clemu_vector16<uint> uint16;
typedef clemu_vector16<__int64> __LONG16;
typedef clemu_vector16<unsigned __int64> __ULONG16;
typedef clemu_vector16<float> float16;
typedef clemu_vector16<double> double16;





inline uint as_uint( uchar4 a)
{
	return (uint)(a.s0 | (a.s1 << 8) | (a.s2 << 16) | (a.s3 << 24) );
}
inline uint as_uint( ushort2 a)
{
	return (uint)(a.s0 | (a.s1 << 16) );
}


/*---------------------------------------------------------------------------------------------------------
 new OPENCL intrinsics
---------------------------------------------------------------------------------------------------------*/

/*
2
*/

template <class _SRC>
  float2 convert_float2(clemu_vector2<_SRC> src)
  {
  float2 dst;
       dst.x = (float)src.x;
       dst.y = (float)src.y;
	   return dst;
  }

template <class _SRC>
  double2 convert_double2(clemu_vector2<_SRC> src)
  {
  double2 dst;
       dst.x = (double)src.x;
       dst.y = (double)src.y;
	   return dst;
  }


template <class _SRC>
  clemu_vector2<char> convert_char2(clemu_vector2<_SRC> src)
  {
    clemu_vector2<char> dst;
       dst.x = (char)src.x;
       dst.y = (char)src.y;
	   return dst;
  }
template <class _SRC>
  clemu_vector2<char> convert_uchar2(clemu_vector2<_SRC> src)
  {
    clemu_vector2<uchar> dst;
       dst.x = (uchar)src.x;
       dst.y = (uchar)src.y;
	   return dst;
  }

template <class _SRC>
  clemu_vector2<short> convert_short2(clemu_vector2<_SRC> src)
  {
    clemu_vector2<short> dst;
       dst.x = (short)src.x;
       dst.y = (short)src.y;
	   return dst;
  }
template <class _SRC>
  clemu_vector2<ushort> convert_ushort2(clemu_vector2<_SRC> src)
  {
    clemu_vector2<ushort> dst;
       dst.x = (ushort)src.x;
       dst.y = (ushort)src.y;
	   return dst;
  }
template <class _SRC>
  clemu_vector2<int> convert_int2(clemu_vector2<_SRC> src)
  {
    clemu_vector2<int> dst;
       dst.x = (int)src.x;
       dst.y = (int)src.y;
	   return dst;
  }
template <class _SRC>
  clemu_vector2<uint> convert_uint2(clemu_vector2<_SRC> src)
  {
    clemu_vector2<uint> dst;
       dst.x = (uint)src.x;
       dst.y = (uint)src.y;
	   return dst;
  }


template <class _SRC>
  uint2 as_uint2(clemu_vector2<_SRC> src)
  {
    uint2 dst;
       dst.x = as_uint(src.x);
       dst.y = as_uint(src.y);
	   return dst;

  }

template <class _SRC>
  int2 as_int2(clemu_vector2<_SRC> src)
  {
    int2 dst;
       dst.x = as_int(src.x);
       dst.y = as_int(src.y);
	   return dst;

  }

template <class _SRC>
  float2 as_float2(clemu_vector2<_SRC> src)
  {
    float2 dst;
       dst.x = as_float(src.x);
       dst.y = as_float(src.y);
	   return dst;

  }


/*---------------------------------------------------------------------------------------------------------------------
*
* INTEGERS
*
---------------------------------------------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------------------------------------------
*
* abs
*
---------------------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------------------
*
* abs_diff
*
---------------------------------------------------------------------------------------------------------------------*/

template <class _T> 
_T abs_diff(_T x, _T y)
{
_T r;
    r.lo = abs_diff(x.lo, y.lo);
    r.hi = abs_diff(x.hi, y.hi);
    return(r);
}
/*---------------------------------------------------------------------------------------------------------------------
*
* add_sat
*
---------------------------------------------------------------------------------------------------------------------*/
template<class _T>
_T add_sat(_T x, _T y)
{
_T r;
    r.lo = add_sat(x.lo, y.lo);
    r.hi = add_sat(x.hi, y.hi);
    return(r);
}
/*---------------------------------------------------------------------------------------------------------------------
*
* hadd
*
---------------------------------------------------------------------------------------------------------------------*/
template<class _T>
_T hadd(_T x, _T y)
{
_T r;
    r.lo = hadd(x.lo, y.lo);
    r.hi = hadd(x.hi, y.hi);
    return(r);
}
/*---------------------------------------------------------------------------------------------------------------------
*
* rhadd
*
---------------------------------------------------------------------------------------------------------------------*/
template<class _T>
_T rhadd(_T x, _T y)
{
_T r;
    r.lo = rhadd(x.lo, y.lo);
    r.hi = rhadd(x.hi, y.hi);
    return(r);
}

/*---------------------------------------------------------------------------------------------------------------------
*
* clz
*
---------------------------------------------------------------------------------------------------------------------*/

template<class _T>
_T clz(_T x)
{
_T r;
    r.lo = clz(x.lo);
    r.hi = clz(x.hi);
    return(r);
}

/*---------------------------------------------------------------------------------------------------------------------
*
* mad_hi
*
---------------------------------------------------------------------------------------------------------------------*/
template<class _T>
_T mad_hi(_T a, _T b, _T c)
{
_T r;
    r.lo = mad_hi(a.lo, b.lo, c.lo);
    r.hi = mad_hi(a.hi, b.hi, c.hi);
    return(r);
}
/*---------------------------------------------------------------------------------------------------------------------
*
* mad_sat
*
---------------------------------------------------------------------------------------------------------------------*/
template<class _T>
_T mad_sat(_T a, _T b, _T c)
{
_T r;
    r.lo = mad_sat(a.lo, b.lo, c.lo);
    r.hi = mad_sat(a.hi, b.hi, c.hi);
    return(r);
}

/*---------------------------------------------------------------------------------------------------------------------
*
* mul_hi
*
---------------------------------------------------------------------------------------------------------------------*/
template <class _T> 
_T mul_hi(_T x, _T y)
{
_T r;
    r.lo = mul_hi(x.lo, y.lo);
    r.hi = mul_hi(x.hi, y.hi);
    return(r);
}
/*---------------------------------------------------------------------------------------------------------------------
*
* rotate
*
---------------------------------------------------------------------------------------------------------------------*/
template <class _T> 
_T rotate(_T v, _T i)
{
_T r;
    r.lo = rotate(v.lo, i.lo);
    r.hi = rotate(v.hi, i.hi);
    return(r);
}

/*---------------------------------------------------------------------------------------------------------------------
*
* sub_sat
*
---------------------------------------------------------------------------------------------------------------------*/
template <class _T> 
_T sub_sat(_T x, _T y)
{
_T r;
    r.lo = sub_sat(x.lo, y.lo);
    r.hi = sub_sat(x.hi, y.hi);
    return(r);
}
/*---------------------------------------------------------------------------------------------------------------------
*
* upsample
*
---------------------------------------------------------------------------------------------------------------------*/
template <class _T> 
_T upsampleu8(_T hi, _T lo)
{
_T r;
    r.lo = upsampleu8(hi.lo, lo.lo);
    r.hi = upsampleu8(hi.hi, hi.hi);
    return(r);
}
template <class _T> 
_T upsampleu16(_T hi, _T lo)
{
_T r;
    r.lo = upsampleu16(hi.lo, lo.lo);
    r.hi = upsampleu16(hi.hi, hi.hi);
    return(r);
}
template <class _T> 
_T upsampleu32(_T hi, _T lo)
{
_T r;
    r.lo = upsampleu32(hi.lo, lo.lo);
    r.hi = upsampleu32(hi.hi, hi.hi);
    return(r);
}
/*---------------------------------------------------------------------------------------------------------------------
*
* mad24
*
---------------------------------------------------------------------------------------------------------------------*/
template<class _T>
_T mad24(_T a, _T b, _T c)
{
_T r;
    r.lo = mad24(a.lo, b.lo, c.lo);
    r.hi = mad24(a.hi, b.hi, c.hi);
    return(r);
}
/*---------------------------------------------------------------------------------------------------------------------
*
* mul24
*
---------------------------------------------------------------------------------------------------------------------*/
template<class _T>
_T mul24(_T a, _T b)
{
_T r;
    r.lo = mul24(a.lo, b.lo);
    r.hi = mul24(a.hi, b.hi);
    return(r);
}

/************************************************************************
*
* common
*
************************************************************************/
template<class _T>
_T clamp(_T x, _T xmin, _T xmax)
{
_T r;
    r.lo = clamp(x.lo, xmin.lo, xmax.lo);
    r.hi = clamp(x.hi, xmin.hi, xmax.hi);
    return(r);
}

template<class _T>
_T degrees(_T x)
{
_T r;
    r.lo = degrees(x.lo);
    r.hi = degrees(x.hi);
    return(r);
}

template<class _T>
_T mix(_T x, _T y, _T a)
{
_T r;
    r.lo = mix(x.lo, y.lo, a.lo);
    r.hi = mix(x.hi, y.hi, a.hi);
    return(r);
}

template<class _T>
_T radians(_T x)
{
_T r;
    r.lo = radians(x.lo);
    r.hi = radians(x.hi);
    return(r);
}

template <class _T> 
_T step(_T x, _T y)
{
_T r;
    r.lo = step(x.lo, y.lo);
    r.hi = step(x.hi, y.hi);
    return(r);
}

template<class _T>
_T smoothstep(_T a, _T b, _T c)
{
_T r;
    r.lo = smoothstep(a.lo, b.lo, c.lo);
    r.hi = smoothstep(a.hi, b.hi, c.hi);
    return(r);
}

template<class _T, class _TT>
_TT smoothstep(_T x)
{
_TT r;
    r.lo = sign(x.lo);
    r.hi = sign(x.hi);
    return(r);
}


/*
AMD_UNPACK
*/
static
float2 amd_unpack0 (uint2 src)
{
float2 ret;
    ret.lo = amd_unpack0(src.lo);
    ret.hi = amd_unpack0(src.hi);
    return(ret);
}
static
float2 amd_unpack1 (uint2 src)
{
float2 ret;
    ret.lo = amd_unpack1(src.lo);
    ret.hi = amd_unpack1(src.hi);
    return(ret);
}
static
float2 amd_unpack2 (uint2 src)
{
float2 ret;
    ret.lo = amd_unpack2(src.lo);
    ret.hi = amd_unpack2(src.hi);
    return(ret);
}
static
float2 amd_unpack3 (uint2 src)
{
float2 ret;
    ret.lo = amd_unpack3(src.lo);
    ret.hi = amd_unpack3(src.hi);
    return(ret);
}

/*
AMD_BITALIGN
*/
static
uint2 amd_bitalign (uint2 src0, uint2 src1, uint2 src2)
{
uint2 ret;
    ret.lo = amd_bitalign (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_bitalign (src0.hi, src1.hi, src2.hi);
    return(ret);
}
/*
AMD_BYTEALIGN
*/
static
uint2 amd_bytealign (uint2 src0, uint2 src1, uint2 src2)
{
uint2 ret;
    ret.lo = amd_bytealign (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_bytealign (src0.hi, src1.hi, src2.hi);
    return(ret);
}
/*
AMD_LERP
*/
static
uint2 amd_lerp (uint2 src0, uint2 src1, uint2 src2)
{
uint2 ret;
    ret.lo = amd_lerp (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_lerp (src0.hi, src1.hi, src2.hi);
    return(ret);
 }
/*
AMD_SAD
*/


static
uint2 amd_sad (uint2 src0, uint2 src1, uint2 src2)
{
uint2 ret;
    ret.lo = amd_sad (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_sad (src0.hi, src1.hi, src2.hi);
    return(ret);
}

static
uint2 amd_sadhi (uint2 src0, uint2 src1, uint2 src2)
{
uint2 ret;
    ret.lo = amd_sadhi (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_sadhi (src0.hi, src1.hi, src2.hi);
    return(ret);
}



/*------------------------------------------------------------------------------------
* 
* relational
*
* ----------------------------------------------------------------------------------*/


//Returns the component-wise compare of x == y.

static int2 isequal (float2 x, float2 y)
{
int2 r;
     r.lo = -isequal (x.lo, y.lo);
     r.hi = -isequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x != y.
static int2 isnotequal (float2 x, float2 y)
{
int2 r;
     r.lo = -isnotequal (x.lo, y.lo);
     r.hi = -isnotequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x > y.
static int2 isgreater (float2 x, float2 y)
{
int2 r;
     r.lo = -isgreater (x.lo, y.lo);
     r.hi = -isgreater (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x >= y.
static int2 isgreaterequal (float2 x, float2 y)
{
int2 r;
     r.lo = -isgreaterequal (x.lo, y.lo);
     r.hi = -isgreaterequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x < y.
static int2 isless (float2 x, float2 y)
{
int2 r;
     r.lo = -isless (x.lo, y.lo);
     r.hi = -isless (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x <= y.
static int2 islessequal (float2 x, float2 y)
{
int2 r;
     r.lo = -islessequal (x.lo, y.lo);
     r.hi = -islessequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of (x < y) || (x > y)
static int2 islessgreater (float2 x, float2 y)
{
int2 r;
     r.lo = -islessgreater (x.lo, y.lo);
     r.hi = -islessgreater (x.hi, y.hi);
     return(r);
}

static int2 isinf(float2 x)
{
int2 r;
     r.lo = -isinf (x.lo);
     r.hi = -isinf (x.hi);
     return(r);
}


static int2 isfinite(float2 x)
{
int2 r;
     r.lo = -isfinite (x.lo);
     r.hi = -isfinite (x.hi);
     return(r);
}
static int2 isnan(float2 x)
{
int2 r;
     r.lo = -isnan (x.lo);
     r.hi = -isnan (x.hi);
     return(r);
}
static int2 isnormal(float2 x)
{
int2 r;
     r.lo = -isnormal (x.lo);
     r.hi = -isnormal (x.hi);
     return(r);
}

//Test if arguments are ordered. isordered() takes
//arguments x and y, and returns the result
//isequal(x, x) && isequal(y, y).

static int2 isordered (float2 x, float2 y)
{
int2 r;
     r.lo = -isordered (x.lo, y.lo);
     r.hi = -isordered (x.hi, y.hi);
     return(r);
}

//Test if arguments are unordered. isunordered() takes
//arguments x and y, returning non-zero if x or y is NaN,
//and zero otherwise.
static int2 isunordered (float2 x, float2 y)
{
int2 r;
     r.lo = -isunordered (x.lo, y.lo);
     r.hi = -isunordered (x.hi, y.hi);
     return(r);
}

//Test for sign bit. The scalar version of the function
//returns a 1 if the sign bit in the float is set else returns 0.
//The vector version of the function returns the following
//for each component in floatn: a -1 if the sign bit in the
//float is set else returns 0.
static int2 signbit (float2 x)
{
int2 r;
     r.lo = -signbit (x.lo);
     r.hi = -signbit (x.hi);
     return(r);
}



//Returns the component-wise compare of x == y.

static __LONG2 isequal (double2 x, double2 y)
{
__LONG2 r;
     r.lo = -isequal (x.lo, y.lo);
     r.hi = -isequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x != y.
static __LONG2 isnotequal (double2 x, double2 y)
{
__LONG2 r;
     r.lo = -isnotequal (x.lo, y.lo);
     r.hi = -isnotequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x > y.
static __LONG2 isgreater (double2 x, double2 y)
{
__LONG2 r;
     r.lo = -isgreater (x.lo, y.lo);
     r.hi = -isgreater (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x >= y.
static __LONG2 isgreaterequal (double2 x, double2 y)
{
__LONG2 r;
     r.lo = -isgreaterequal (x.lo, y.lo);
     r.hi = -isgreaterequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x < y.
static __LONG2 isless (double2 x, double2 y)
{
__LONG2 r;
     r.lo = -isless (x.lo, y.lo);
     r.hi = -isless (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x <= y.
static __LONG2 islessequal (double2 x, double2 y)
{
__LONG2 r;
     r.lo = -islessequal (x.lo, y.lo);
     r.hi = -islessequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of (x < y) || (x > y)
static __LONG2 islessgreater (double2 x, double2 y)
{
__LONG2 r;
     r.lo = -islessgreater (x.lo, y.lo);
     r.hi = -islessgreater (x.hi, y.hi);
     return(r);
}

static __LONG2 isinf(double2 x)
{
__LONG2 r;
     r.lo = -isinf (x.lo);
     r.hi = -isinf (x.hi);
     return(r);
}


static __LONG2 isfinite(double2 x)
{
__LONG2 r;
     r.lo = -isfinite (x.lo);
     r.hi = -isfinite (x.hi);
     return(r);
}
static __LONG2 isnan(double2 x)
{
__LONG2 r;
     r.lo = -isnan (x.lo);
     r.hi = -isnan (x.hi);
     return(r);
}
static __LONG2 isnormal(double2 x)
{
__LONG2 r;
     r.lo = -isnormal (x.lo);
     r.hi = -isnormal (x.hi);
     return(r);
}

//Test if arguments are ordered. isordered() takes
//arguments x and y, and returns the result
//isequal(x, x) && isequal(y, y).

static __LONG2 isordered (double2 x, double2 y)
{
__LONG2 r;
     r.lo = -isordered (x.lo, y.lo);
     r.hi = -isordered (x.hi, y.hi);
     return(r);
}

//Test if arguments are unordered. isunordered() takes
//arguments x and y, returning non-zero if x or y is NaN,
//and zero otherwise.
static __LONG2 isunordered (double2 x, double2 y)
{
__LONG2 r;
     r.lo = -isunordered (x.lo, y.lo);
     r.hi = -isunordered (x.hi, y.hi);
     return(r);
}

//Test for sign bit. The scalar version of the function
//returns a 1 if the sign bit in the float is set else returns 0.
//The vector version of the function returns the following
//for each component in floatn: a -1 if the sign bit in the
//float is set else returns 0.
static __LONG2 signbit (double2 x)
{
__LONG2 r;
     r.lo = -signbit (x.lo);
     r.hi = -signbit (x.hi);
     return(r);
}



/*
ACOS
*/


static float2 acos( float2 _a)
{
float2 ret;
       ret.lo = acos(_a.lo);
       ret.hi = acos(_a.hi);
	   return ret;
}

static double2 acos( double2 _a)
{
double2 ret;
       ret.lo = acos(_a.lo);
       ret.hi = acos(_a.hi);
	   return ret;
}

// ACOSH

static float2 acosh( float2 _a)
{
float2 ret;
       ret.lo = acosh(_a.lo);
       ret.hi = acosh(_a.hi);
	   return ret;
}

static double2 acosh( double2 _a)
{
double2 ret;
       ret.lo = acosh(_a.lo);
       ret.hi = acosh(_a.hi);
	   return ret;
}

// ACOSPI

static float2 acospi( float2 _a)
{
float2 ret;
       ret.lo = acospi(_a.lo);
       ret.hi = acospi(_a.hi);
	   return ret;
}

static double2 acospi( double2 _a)
{
double2 ret;
       ret.lo = acospi(_a.lo);
       ret.hi = acospi(_a.hi);
	   return ret;
}


// ASIN

static float2 asin( float2 _a)
{
float2 ret;
       ret.lo = asin(_a.lo);
       ret.hi = asin(_a.hi);
	   return ret;
}

static double2 asin( double2 _a)
{
double2 ret;
       ret.lo = asin(_a.lo);
       ret.hi = asin(_a.hi);
	   return ret;
}


// ASINH

static float2 asinh( float2 _a)
{
float2 ret;
       ret.lo = asinh(_a.lo);
       ret.hi = asinh(_a.hi);
	   return ret;
}

static double2 asinh( double2 _a)
{
double2 ret;
       ret.lo = asinh(_a.lo);
       ret.hi = asinh(_a.hi);
	   return ret;
}

// ASINPI

static float2 asinpi( float2 _a)
{
float2 ret;
       ret.lo = asinpi(_a.lo);
       ret.hi = asinpi(_a.hi);
	   return ret;
}

static double2 asinpi( double2 _a)
{
double2 ret;
       ret.lo = asinpi(_a.lo);
       ret.hi = asinpi(_a.hi);
	   return ret;
}


// ATAN

static float2 atan( float2 _a)
{
float2 ret;
       ret.lo = atan(_a.lo);
       ret.hi = atan(_a.hi);
	   return ret;
}

static double2 atan( double2 _a)
{
double2 ret;
       ret.lo = atan(_a.lo);
       ret.hi = atan(_a.hi);
	   return ret;
}

// ATAN2

static float2 atan2( float2 _a, float2 _b)
{
float2 ret;
       ret.lo = atan2(_a.lo, _b.lo);
       ret.hi = atan2(_a.hi, _b.hi);
	   return ret;
}

static double2 atan2( double2 _a, double2 _b)
{
double2 ret;
       ret.lo = atan2(_a.lo, _b.lo);
       ret.hi = atan2(_a.hi, _b.hi);
	   return ret;
}

// ATANH

static float2 atanh( float2 _a)
{
float2 ret;
       ret.lo = atanh(_a.lo);
       ret.hi = atanh(_a.hi);
	   return ret;
}

static double2 atanh( double2 _a)
{
double2 ret;
       ret.lo = atanh(_a.lo);
       ret.hi = atanh(_a.hi);
	   return ret;
}

// ATANPI

static float2 atanpi( float2 _a)
{
float2 ret;
       ret.lo = atanpi(_a.lo);
       ret.hi = atanpi(_a.hi);
	   return ret;
}

static double2 atanpi( double2 _a)
{
double2 ret;
       ret.lo = atanpi(_a.lo);
       ret.hi = atanpi(_a.hi);
	   return ret;
}

// ATAN2

static float2 atan2pi( float2 _a, float2 _b)
{
float2 ret;
       ret.lo = atan2pi(_a.lo, _b.lo);
       ret.hi = atan2pi(_a.hi, _b.hi);
	   return ret;
}

static double2 atan2pi( double2 _a, double2 _b)
{
double2 ret;
       ret.lo = atan2pi(_a.lo, _b.lo);
       ret.hi = atan2pi(_a.hi, _b.hi);
	   return ret;
}

// CBRT
static float2 cbrt( float2 _a)
{
float2 ret;
       ret.lo = cbrt(_a.lo);
       ret.hi = cbrt(_a.hi);
	   return ret;
}

static double2 cbrt( double2 _a)
{
double2 ret;
       ret.lo = cbrt(_a.lo);
       ret.hi = cbrt(_a.hi);
	   return ret;
}



// CEIL
static float2 ceil( float2 _a)
{
float2 ret;
       ret.lo = ceil(_a.lo);
       ret.hi = ceil(_a.hi);
	   return ret;
}

static double2 ceil( double2 _a)
{
double2 ret;
       ret.lo = ceil(_a.lo);
       ret.hi = ceil(_a.hi);
	   return ret;
}




// ATAN2

static float2 copysign( float2 _a, float2 _b)
{
float2 ret;
       ret.lo = copysign(_a.lo, _b.lo);
       ret.hi = copysign(_a.hi, _b.hi);
	   return ret;
}

static double2 copysign( double2 _a, double2 _b)
{
double2 ret;
       ret.lo = copysign(_a.lo, _b.lo);
       ret.hi = copysign(_a.hi, _b.hi);
	   return ret;
}



// COS

static float2 cos( float2 _a)
{
float2 ret;
       ret.lo = cos(_a.lo);
       ret.hi = cos(_a.hi);
	   return ret;
}

static double2 cos( double2 _a)
{
double2 ret;
       ret.lo = cos(_a.lo);
       ret.hi = cos(_a.hi);
	   return ret;
}

// COSH

static float2 cosh( float2 _a)
{
float2 ret;
       ret.lo = cosh(_a.lo);
       ret.hi = cosh(_a.hi);
	   return ret;
}

static double2 cosh( double2 _a)
{
double2 ret;
       ret.lo = cosh(_a.lo);
       ret.hi = cosh(_a.hi);
	   return ret;
}

// COSPI

static float2 cospi( float2 _a)
{
float2 ret;
       ret.lo = cospi(_a.lo);
       ret.hi = cospi(_a.hi);
	   return ret;
}

static double2 cospi( double2 _a)
{
double2 ret;
       ret.lo = cospi(_a.lo);
       ret.hi = cospi(_a.hi);
	   return ret;
}

// ERFC

static float2 erfc( float2 _a)
{
float2 ret;
       ret.lo = erfc(_a.lo);
       ret.hi = erfc(_a.hi);
	   return ret;
}

static double2 erfc( double2 _a)
{
double2 ret;
       ret.lo = erfc(_a.lo);
       ret.hi = erfc(_a.hi);
	   return ret;
}


// ERF


static float2 erf( float2 _a)
{
float2 ret;
       ret.lo = erf(_a.lo);
       ret.hi = erf(_a.hi);
	   return ret;
}

static double2 erf( double2 _a)
{
double2 ret;
       ret.lo = erf(_a.lo);
       ret.hi = erf(_a.hi);
	   return ret;
}





// EXP
static float2 exp( float2 _a)
{
float2 ret;
       ret.lo = exp(_a.lo);
       ret.hi = exp(_a.hi);
	   return ret;
}

static double2 exp( double2 _a)
{
double2 ret;
       ret.lo = exp(_a.lo);
       ret.hi = exp(_a.hi);
	   return ret;
}

// EXP2

static float2 exp2( float2 _a)
{
float2 ret;
       ret.lo = exp2(_a.lo);
       ret.hi = exp2(_a.hi);
	   return ret;
}

static double2 exp2( double2 _a)
{
double2 ret;
       ret.lo = exp2(_a.lo);
       ret.hi = exp2(_a.hi);
	   return ret;
}

// EXP10

static float2 exp10( float2 _a)
{
float2 ret;
       ret.lo = exp10(_a.lo);
       ret.hi = exp10(_a.hi);
	   return ret;
}

static double2 exp10( double2 _a)
{
double2 ret;
       ret.lo = exp10(_a.lo);
       ret.hi = exp10(_a.hi);
	   return ret;
}

// EXPM1
static float2 expm1( float2 _a)
{
float2 ret;
       ret.lo = expm1(_a.lo);
       ret.hi = expm1(_a.hi);
	   return ret;
}

static double2 expm1( double2 _a)
{
double2 ret;
       ret.lo = expm1(_a.lo);
       ret.hi = expm1(_a.hi);
	   return ret;
}


// FABS
static float2 fabs( float2 _a)
{
float2 ret;
       ret.lo = fabs(_a.lo);
       ret.hi = fabs(_a.hi);
	   return ret;
}

static double2 fabs( double2 _a)
{
double2 ret;
       ret.lo = fabs(_a.lo);
       ret.hi = fabs(_a.hi);
	   return ret;
}

// FDIM
static double2 fdim( double2 _a, double2 _b)
{
double2 ret;
       ret.lo = fdim(_a.lo, _b.lo);
       ret.hi = fdim(_a.hi, _b.hi);
	   return ret;
}

static float2 fdim( float2 _a, float2 _b)
{
float2 ret;
       ret.lo = fdim(_a.lo, _b.lo);
       ret.hi = fdim(_a.hi, _b.hi);
	   return ret;
}



// FLOOR

static float2 floor( float2 _a)
{
float2 ret;
       ret.lo = floor(_a.lo);
       ret.hi = floor(_a.hi);
	   return ret;
}

static double2 floor( double2 _a)
{
double2 ret;
       ret.lo = floor(_a.lo);
       ret.hi = floor(_a.hi);
	   return ret;
}

// FMA

static float2 fma( float2 _a, float2 _b, float2 _c)
{
float2 ret;
       ret.lo = fma(_a.lo,_b.lo,_c.lo);
       ret.hi = fma(_a.hi,_b.hi,_c.hi);
	   return(ret);
}


static double2 fma( double2 _a, double2 _b, double2 _c)
{
double2 ret;
       ret.lo = fma(_a.lo,_b.lo,_c.lo);
       ret.hi = fma(_a.hi,_b.hi,_c.hi);
	   return(ret);
}


// FMAX

static float2 fmax( float2 _a, float2 _b)
{
float2 ret;
       ret.lo = fmax(_a.lo,_b.lo);
       ret.hi = fmax(_a.hi,_b.hi);
	   return(ret);
}


static double2 fmax( double2 _a, double2 _b)
{
double2 ret;
       ret.lo = fmax(_a.lo,_b.lo);
       ret.hi = fmax(_a.hi,_b.hi);
	   return(ret);
}

// FMIN

static float2 fmin( float2 _a, float2 _b)
{
float2 ret;
       ret.lo = fmin(_a.lo,_b.lo);
       ret.hi = fmin(_a.hi,_b.hi);
	   return(ret);
}


static double2 fmin( double2 _a, double2 _b)
{
double2 ret;
       ret.lo = fmin(_a.lo,_b.lo);
       ret.hi = fmin(_a.hi,_b.hi);
	   return(ret);
}


// FMOD
static float2 fmod( float2 _a, float2 _b)
{
float2 ret;
       ret.lo = fmod(_a.lo, _b.lo);
       ret.hi = fmod(_a.hi, _b.hi);
	   return ret;
}

static double2 fmod( double2 _a, double2 _b)
{
double2 ret;
       ret.lo = fmod(_a.lo, _b.lo);
       ret.hi = fmod(_a.hi, _b.hi);
	   return ret;
}







// FRAC

static float2 frac( float2 _a)
{
float2 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}

static double2 frac( double2 _a)
{
double2 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}


// FRACT

static float2 fract( float2 _a)
{
float2 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}

static double2 fract( double2 _a)
{
double2 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}

// FREXP

static float2 frexp( float2 _a, int2* _b)
{
float2 ret;
       ret.lo = frexp(_a.lo, &_b->lo);
       ret.hi = frexp(_a.hi, &_b->hi);
	   return ret;
}

static double2 frexp( double2 _a, int2* _b)
{
double2 ret;
       ret.lo = frexp(_a.lo, &_b->lo);
       ret.hi = frexp(_a.hi, &_b->hi);
	   return ret;
}

// HYPOT

static float2 hypot( float2 _a, float2 _b)
{
float2 ret;
       ret.lo = (float)_hypot((double)_a.lo, (double)_b.lo);
       ret.hi = (float)_hypot((double)_a.hi, (double)_b.hi);
	   return ret;
}

static double2 hypot( double2 _a, double2 _b)
{
double2 ret;
       ret.lo = _hypot(_a.lo, _b.lo);
       ret.hi = _hypot(_a.hi, _b.hi);
	   return ret;
}

// ILOGB

static int2 ilogb( float2 _a)
{
int2 ret;
       ret.lo = ilogb(_a.lo);
       ret.hi = ilogb(_a.hi);
	   return ret;
}

static int2 ilogb( double2 _a)
{
int2 ret;
       ret.lo = ilogb(_a.lo);
       ret.hi = ilogb(_a.hi);
	   return ret;
}

// LDEXP

static float2 ldexp( float2 _a, int2 _b)
{
float2 ret;
       ret.lo = ldexp(_a.lo, _b.lo);
       ret.hi = ldexp(_a.hi, _b.hi);
	   return ret;
}

static double2 ldexp( double2 _a, int2 _b)
{
double2 ret;
       ret.lo = ldexp(_a.lo, _b.lo);
       ret.hi = ldexp(_a.hi, _b.hi);
	   return ret;
}

static float2 ldexp( float2 _a, int _b)
{
float2 ret;
       ret = ldexp(_a, (int2)_b);
	   return ret;
}

static double2 ldexp( double2 _a, int _b)
{
double2 ret;
       ret = ldexp(_a, (int2)_b);
	   return ret;
}

// LGAMMA
static float2 lgamma( float2 _a)
{
float2 ret;
       ret.lo = lgamma(_a.lo);
       ret.hi = lgamma(_a.hi);
	   return ret;
}

static double2 lgamma( double2 _a)
{
double2 ret;
       ret.lo = lgamma(_a.lo);
       ret.hi = lgamma(_a.hi);
	   return ret;
}

// LGAMMA_R

static float2 lgamma_r( float2 _a, int2 *psign)
{
float2 ret;
       ret.lo = lgamma_r(_a.lo, &psign->lo);
       ret.hi = lgamma_r(_a.hi, &psign->hi);
	   return ret;
}

static double2 lgamma_r( double2 _a, int2 *psign)
{
double2 ret;
       ret.lo = lgamma_r(_a.lo, &psign->lo);
       ret.hi = lgamma_r(_a.hi, &psign->hi);
	   return ret;
}

// LOG

static float2 log( float2 _a)
{
float2 ret;
       ret.lo = log(_a.lo);
       ret.hi = log(_a.hi);
	   return ret;
}

static double2 log( double2 _a)
{
double2 ret;
       ret.lo = log(_a.lo);
       ret.hi = log(_a.hi);
	   return ret;
}

// LOG2

static float2 log2( float2 _a)
{
float2 ret;
       ret.lo = log2(_a.lo);
       ret.hi = log2(_a.hi);
	   return ret;
}

static double2 log2( double2 _a)
{
double2 ret;
       ret.lo = log2(_a.lo);
       ret.hi = log2(_a.hi);
	   return ret;
}


// LOG10

static float2 log10( float2 _a)
{
float2 ret;
       ret.lo = log10(_a.lo);
       ret.hi = log10(_a.hi);
	   return ret;
}

static double2 log10( double2 _a)
{
double2 ret;
       ret.lo = log10(_a.lo);
       ret.hi = log10(_a.hi);
	   return ret;
}

// LOG1P

static float2 log1p( float2 _a)
{
float2 ret;
       ret.lo = log1p(_a.lo);
       ret.hi = log1p(_a.hi);
	   return ret;
}

static double2 log1p( double2 _a)
{
double2 ret;
       ret.lo = log1p(_a.lo);
       ret.hi = log1p(_a.hi);
	   return ret;
}


// LOGB

static float2 logb( float2 _a)
{
float2 ret;
       ret.lo = logb(_a.lo);
       ret.hi = logb(_a.hi);
	   return ret;
}

static double2 logb( double2 _a)
{
double2 ret;
       ret.lo = logb(_a.lo);
       ret.hi = logb(_a.hi);
	   return ret;
}


// mad

static float2 mad( float2 _a, float2 _b, float2 _c)
{
float2 ret;
       ret.lo = mad(_a.lo, _b.lo, _c.lo);
       ret.hi = mad(_a.hi, _b.hi, _c.hi);
	   return ret;
}

static double2 mad( double2 _a, double2 _b, double2 _c)
{
double2 ret;
       ret.lo = mad(_a.lo, _b.lo, _c.lo);
       ret.hi = mad(_a.hi, _b.hi, _c.hi);
	   return ret;
}


// mogf

static float2 modf( float2 _a, int2* _b)
{
float2 ret;
float b_lo, b_hi;
       ret.lo = modf(_a.lo, &b_lo);
       ret.hi = modf(_a.hi, &b_hi);
	   _b->lo = (int)b_lo;
	   _b->hi = (int)b_hi;
	   return ret;
}

static double2 modf( double2 _a, int2* _b)
{
double2 ret;
double b_lo, b_hi;
       ret.lo = modf(_a.lo, &b_lo);
       ret.hi = modf(_a.hi, &b_hi);
	   _b->lo = (int)b_lo;
	   _b->hi = (int)b_hi;
	   return ret;
}

//NAN
static float2 nan( int2 _b)
{
float2 ret;
       ret.lo = nan(_b.lo);
       ret.hi = nan(_b.hi);
	   return ret;
}
static double2 nan( __LONG2 _b)
{
double2 ret;
       ret.lo = nan(_b.lo);
       ret.hi = nan(_b.hi);
	   return ret;
}

// NEXTAFTER
static float2 nextafter( float2 _a, float2 _b)
{
float2 ret;
       ret.lo = nextafter(_a.lo, _b.lo);
       ret.hi = nextafter(_a.hi, _b.hi);
	   return ret;
}
static double2 nextafter( double2 _a, double2 _b)
{
double2 ret;
       ret.lo = nextafter(_a.lo, _b.lo);
       ret.hi = nextafter(_a.hi, _b.hi);
	   return ret;
}

// POW
static float2 pow( float2 _a, float2 _b)
{
float2 ret;
       ret.lo = pow(_a.lo, _b.lo);
       ret.hi = pow(_a.hi, _b.hi);
	   return ret;
}

static double2 pow( double2 _a, double2 _b)
{
double2 ret;
       ret.lo = pow(_a.lo, _b.lo);
       ret.hi = pow(_a.hi, _b.hi);
	   return ret;
}

// POWN
static double2 pown( double2 _a, int2 _b)
{
double2 ret;
double2 b = convert_double2(_b);
       ret.lo = pow(_a.lo, b.lo);
       ret.hi = pow(_a.hi, b.hi);
	   return ret;
}

static float2 pown( float2 _a, int2 _b)
{
float2 ret;
double2 a = convert_double2(_a);
double2 r = pown(a, _b);

       ret = convert_float2(r);
	   return ret;
}

// POWR
static double2 powr( double2 _a, double2 _b)
{
double2 ret = pow(_a,_b);
	   return ret;
}

static float2 powr( float2 _a, float2 _b)
{
float2 ret = pow(_a,_b);
	   return ret;
}

// REMAINDER
static
float2 remainder(float2 x, float2 p)
{
float2 ret;
        ret.lo = remainder(x.lo, p.lo);
        ret.hi = remainder(x.hi, p.hi);
		return(ret);
}

static
double2 remainder(double2 x, double2 p)
{
double2 ret;
        ret.lo = remainder(x.lo, p.lo);
        ret.hi = remainder(x.hi, p.hi);
		return(ret);
}


// REMQUO
static
float2 remquo(float2 x, float2 p, int2 *pquo)
{
float2 ret;
        ret.lo = remquo(x.lo, p.lo, &pquo->lo);
        ret.hi = remquo(x.hi, p.hi, &pquo->hi);
		return(ret);
}

static
double2 remquo(double2 x, double2 p, int2 *pquo)
{
double2 ret;
        ret.lo = remquo(x.lo, p.lo, &pquo->lo);
        ret.hi = remquo(x.hi, p.hi, &pquo->hi);
		return(ret);
}


// RINT

static float2
rint (float2 x)
{
float2 ret;
       ret.lo = rint(x.lo);
       ret.hi = rint(x.hi);
	   return(ret);
}

static double2
rint (double2 x)
{
double2 ret;
       ret.lo = rint(x.lo);
       ret.hi = rint(x.hi);
	   return(ret);
}


// ROOTN
static float2 rootn( float2 _a, int2 _n)
{
float2 ret;
       ret.lo = rootn(_a.lo, _n.lo);
       ret.hi = rootn(_a.hi, _n.hi);
	   return ret;
}

static double2 rootn( double2 _a, int2 _n)
{
double2 ret;
       ret.lo = rootn(_a.lo, _n.lo);
       ret.hi = rootn(_a.hi, _n.hi);
	   return ret;
}

//ROUND

static float2 round( float2 _a)
{
float2 ret;
       ret.lo = round(_a.lo);
       ret.hi = round(_a.hi);
	   return ret;
}

static double2 round( double2 _a)
{
double2 ret;
       ret.lo = round(_a.lo);
       ret.hi = round(_a.hi);
	   return ret;
}


//RSQRT

static float2 rsqrt( float2 _a)
{
float2 ret;
       ret.lo = rsqrt(_a.lo);
       ret.hi = rsqrt(_a.hi);
	   return ret;
}

static double2 rsqrt( double2 _a)
{
double2 ret;
       ret.lo = rsqrt(_a.lo);
       ret.hi = rsqrt(_a.hi);
	   return ret;
}

//SIN

static float2 sin( float2 _a)
{
float2 ret;
       ret.lo = sin(_a.lo);
       ret.hi = sin(_a.hi);
	   return ret;
}

static double2 sin( double2 _a)
{
double2 ret;
       ret.lo = sin(_a.lo);
       ret.hi = sin(_a.hi);
	   return ret;
}

//SINCOS

static float2 sincos( float2 _a, float2*_b)
{
float2 ret;
       ret.lo = sincos(_a.lo, &_b->lo);
       ret.hi = sincos(_a.hi, &_b->hi);
	   return ret;
}

static double2 sincos( double2 _a, double2*_b)
{
double2 ret;
       ret.lo = sincos(_a.lo, &_b->lo);
       ret.hi = sincos(_a.hi, &_b->hi);
	   return ret;
}

//SINH

static float2 sinh( float2 _a)
{
float2 ret;
       ret.lo = sinh(_a.lo);
       ret.hi = sinh(_a.hi);
	   return ret;
}

static double2 sinh( double2 _a)
{
double2 ret;
       ret.lo = sinh(_a.lo);
       ret.hi = sinh(_a.hi);
	   return ret;
}


//SINPI

static float2 sinpi( float2 _a)
{
float2 ret;
       ret.lo = sinpi(_a.lo);
       ret.hi = sinpi(_a.hi);
	   return ret;
}

static double2 sinpi( double2 _a)
{
double2 ret;
       ret.lo = sinpi(_a.lo);
       ret.hi = sinpi(_a.hi);
	   return ret;
}


//SQRT

static float2 sqrt( float2 _a)
{
float2 ret;
       ret.lo = sqrt(_a.lo);
       ret.hi = sqrt(_a.hi);
	   return ret;
}

static double2 sqrt( double2 _a)
{
double2 ret;
       ret.lo = sqrt(_a.lo);
       ret.hi = sqrt(_a.hi);
	   return ret;
}

//TAN

static float2 tan( float2 _a)
{
float2 ret;
       ret.lo = tan(_a.lo);
       ret.hi = tan(_a.hi);
	   return ret;
}

static double2 tan( double2 _a)
{
double2 ret;
       ret.lo = tan(_a.lo);
       ret.hi = tan(_a.hi);
	   return ret;
}

//TANH

static float2 tanh( float2 _a)
{
float2 ret;
       ret.lo = tanh(_a.lo);
       ret.hi = tanh(_a.hi);
	   return ret;
}

static double2 tanh( double2 _a)
{
double2 ret;
       ret.lo = tanh(_a.lo);
       ret.hi = tanh(_a.hi);
	   return ret;
}

//TANPI

static float2 tanpi( float2 _a)
{
float2 ret;
       ret.lo = tanpi(_a.lo);
       ret.hi = tanpi(_a.hi);
	   return ret;
}

static double2 tanpi( double2 _a)
{
double2 ret;
       ret.lo = tanpi(_a.lo);
       ret.hi = tanpi(_a.hi);
	   return ret;
}




// TGAMMA
static float2 tgamma( float2 _a)
{
float2 ret;
       ret.lo = tgamma(_a.lo);
       ret.hi = tgamma(_a.hi);
	   return ret;
}
static double2 tgamma( double2 _a)
{
double2 ret;
       ret.lo = tgamma(_a.lo);
       ret.hi = tgamma(_a.hi);
	   return ret;
}

// TRUNC

static float2 trunc( float2 _a)
{
float2 ret;
       ret.lo = trunc(_a.lo);
       ret.hi = trunc(_a.hi);
	   return ret;
}

static double2 trunc( double2 _a)
{
double2 ret;
       ret.lo = trunc(_a.lo);
       ret.hi = trunc(_a.hi);
	   return ret;
}

static float2 native_cos( float2 _a)
{
float2 ret;
       ret = cos(_a);
	   return ret;
}

static double2 native_cos( double2 _a)
{
double2 ret;
       ret = cos(_a);
	   return ret;
}


static double2 native_divide( double2 _a, double2 _b)
{
double2 ret;
       ret.lo = _a.lo /_b.lo;
       ret.hi = _a.hi /_b.hi;
	   return ret;
}

static float2 native_divide( float2 _a, float2 _b)
{
float2 ret = convert_float2(native_divide(convert_double2(_a), convert_double2(_b)));
	   return ret;
}

static float2 native_exp( float2 _a)
{
float2 ret;
       ret = exp(_a);
	   return ret;
}

static double2 native_exp( double2 _a)
{
double2 ret;
       ret = exp(_a);
	   return ret;
}

static float2 native_exp2( float2 _a)
{
float2 ret;
       ret = exp2(_a);
	   return ret;
}

static double2 native_exp2( double2 _a)
{
double2 ret;
       ret = exp2(_a);
	   return ret;
}

static float2 native_exp10( float2 _a)
{
float2 ret;
       ret = exp10(_a);
	   return ret;
}

static double2 native_exp10( double2 _a)
{
double2 ret;
       ret = exp10(_a);
	   return ret;
}

static float2 native_log( float2 _a)
{
float2 ret;
       ret = log(_a);
	   return ret;
}

static double2 native_log( double2 _a)
{
double2 ret;
       ret = log(_a);
	   return ret;
}

static float2 native_log2( float2 _a)
{
float2 ret;
       ret = log2(_a);
	   return ret;
}

static double2 native_log2( double2 _a)
{
double2 ret;
       ret = log2(_a);
	   return ret;
}

static float2 native_log10( float2 _a)
{
float2 ret;
       ret = log10(_a);
	   return ret;
}

static double2 native_log10( double2 _a)
{
double2 ret;
       ret = log10(_a);
	   return ret;
}

static float2 native_powr( float2 _a, float2 _b)
{
float2 ret;
       ret = powr(_a, _b);
	   return ret;
}

static double2 native_powr( double2 _a, double2 _b)
{
double2 ret;
       ret = powr(_a, _b);
	   return ret;
}

static float2 native_recip( float2 _a)
{
float2 ret;
       ret = native_divide(1.f,_a);
	   return ret;
}

static double2 native_recip( double2 _a)
{
double2 ret;
       ret = native_divide(1.,_a);
	   return ret;
}

static float2 native_rsqrt( float2 _a)
{
float2 ret;
       ret = rsqrt(_a);
	   return ret;
}

static double2 native_rsqrt( double2 _a)
{
double2 ret;
       ret = rsqrt(_a);
	   return ret;
}

static float2 native_sin( float2 _a)
{
float2 ret;
       ret = sin(_a);
	   return ret;
}

static double2 native_sin( double2 _a)
{
double2 ret;
       ret = sin(_a);
	   return ret;
}

static float2 native_sqrt( float2 _a)
{
float2 ret;
       ret = sqrt(_a);
	   return ret;
}

static double2 native_sqrt( double2 _a)
{
double2 ret;
       ret = sqrt(_a);
	   return ret;
}

static float2 native_tan( float2 _a)
{
float2 ret;
       ret = tan(_a);
	   return ret;
}

static double2 native_tan( double2 _a)
{
double2 ret;
       ret = tan(_a);
	   return ret;
}

// CLAMP
static float2 clamp( float2 _a, float2 _min, float2 _max)
{
float2 ret;
       ret.lo = clamp(_a.lo, _min.lo, _max.lo);
       ret.hi = clamp(_a.hi, _min.hi, _max.hi);
	   return ret;
}

static double2 clamp( double2 _a, double2 _min, double2 _max)
{
double2 ret;
       ret.lo = min(max(_a.lo, _min.lo), _max.lo);
       ret.hi = min(max(_a.hi, _min.hi), _max.hi);
	   return ret;
}

// DEGREES
static double2
degrees(double2 radians)
{
double2 ret;
    ret.lo = degrees(radians.lo);
    ret.hi = degrees(radians.hi);
    return(ret);
}

static float2
degrees(float2 radians)
{
float2 ret;
    ret.lo = degrees(radians.lo);
    ret.hi = degrees(radians.hi);
    return(ret);
}



//MAX
float2
static max(float2 x, float2 y)
{
float2 r;
    r.lo = max(x.lo, y.lo);
    r.hi = max(x.hi, y.hi);
    return(r);
}

double2
static max(double2 x, double2 y)
{
double2 r;
    r.lo = max(x.lo, y.lo);
    r.hi = max(x.hi, y.hi);
    return(r);
}

//MIN
float2
static min(float2 x, float2 y)
{
float2 r;
    r.lo = min(x.lo, y.lo);
    r.hi = min(x.hi, y.hi);
    return(r);
}

double2
static min(double2 x, double2 y)
{
double2 r;
    r.lo = min(x.lo, y.lo);
    r.hi = min(x.hi, y.hi);
    return(r);
}

// MIX
static double2
mix(double2 x, double2 y, double2 a)
{
double2 r;
	r.lo = mix(x.lo, y.lo, a.lo);
	r.hi = mix(x.hi, y.hi, a.hi);
    return(r);
}


static float2
mix(float2 x, float2 y, float2 a)
{
float2 r;
	r.lo = mix(x.lo, y.lo, a.lo);
	r.hi = mix(x.hi, y.hi, a.hi);
    return(r);
}

//RADIANS
static double2
radians(double2 degrees)
{
double2 ret;
    ret.lo = radians(degrees.lo);
    ret.hi = radians(degrees.hi);
    return(ret);
}


static float2
radians(float2 degrees)
{
float2 ret;
    ret.lo = radians(degrees.lo);
    ret.hi = radians(degrees.hi);
    return(ret);
}

//STEP
static double2
step(double2 edge, double2 x)
{
double2 r;
    r.lo = step(edge.lo,x.lo);
    r.hi = step(edge.hi,x.hi);
    return(r);
}

static float2
step(float2 edge, float2 x)
{
float2 r;
    r.lo = step(edge.lo,x.lo);
    r.hi = step(edge.hi,x.hi);
    return(r);
}


// SMOOTHEDGE
static double2
smoothstep(double2 edge0, double2 edge1, double2 x)
{
double2 r;
	r.lo = mix(edge0.lo, edge1.lo, x.lo);
	r.hi = mix(edge0.hi, edge1.hi, x.hi);
    return(r);
}


static float2
smoothstep(float2 edge0, float2 edge1, float2 x)
{
float2 r;
	r.lo = mix(edge0.lo, edge1.lo, x.lo);
	r.hi = mix(edge0.hi, edge1.hi, x.hi);
    return(r);
}


// SIGN
int2
static sign(float2 src)
  {
    int2 ret;
       ret.x = sign(src.x);
       ret.y = sign(src.y);
	   return ret;
  }
int2
static sign(double2 src)
  {
    int2 ret;
       ret.x = sign(src.x);
       ret.y = sign(src.y);
	   return ret;
  }



/*---------------------------------------------------------------------------------------------------------------------
*
* dot
*
---------------------------------------------------------------------------------------------------------------------*/
static float dot(float2 _a, float2 _b)
{
float ret;
      ret = dot(_a.lo,_b.lo) + dot(_a.hi,_b.hi);
	  return(ret);
}

static double dot(double2 _a, double2 _b)
{
double ret;
      ret = dot(_a.lo,_b.lo) + dot(_a.hi,_b.hi);
	  return(ret);
}



/*---------------------------------------------------------------------------------------------------------------------
*
* distance
*
---------------------------------------------------------------------------------------------------------------------*/

static double distance(double2 x, double2 y)
{
double r = 0;
double2 t = x - y;
    r = dot(t,t);
	r = sqrt(r);
    return ( r );
}


static float distance(float2 x, float2 y)
{
float r = 0;
    r= (float)distance(convert_double2(x),convert_double2(y));
    return ( r );
}

/*---------------------------------------------------------------------------------------------------------------------
*
* fast_distance
*
---------------------------------------------------------------------------------------------------------------------*/

static float
fast_distance(float2 x, float2 y)
{
float r = distance(x,y);
    return ( r );
}

static double
fast_distance(double2 x, double2 y)
{
double r = distance(x,y);
    return ( r );
}


/*---------------------------------------------------------------------------------------------------------------------
*
* length
*
---------------------------------------------------------------------------------------------------------------------*/

static double
length(double2 p)
{
double r = 0;
    r = dot(p,p);
	r = sqrt(r);
    return ( r );
}

static float
length(float2 p)
{
float r = (float)length(convert_double2(p));
    return ( r );
}


/*---------------------------------------------------------------------------------------------------------------------
*
* fast_length
*
---------------------------------------------------------------------------------------------------------------------*/

static double
fast_length(double2 p)
{
double r = length(p);
    return ( r );
}


static float
fast_length(float2 p)
{
float r = length(p);
    return ( r );
}


/*---------------------------------------------------------------------------------------------------------------------
*
* normalize
*
---------------------------------------------------------------------------------------------------------------------*/

static double2
normalize(double2 p)
{
double2 r;
double t = dot(p,p);
    r = ( t==0) ? p : p/(double2)sqrt(t); 
    return ( r );
}


static float2
normalize(float2 p)
{
float2 r = convert_float2(normalize(convert_double2(p)));
    return ( r );
}


/*---------------------------------------------------------------------------------------------------------------------
*
* fast_normalize
*
---------------------------------------------------------------------------------------------------------------------*/

static float2
fast_normalize(float2 p)
{
float2 r = 0;
    r = normalize(p);
    return ( r );
}


static double2
fast_normalize(double2 p)
{
double2 r = 0;
    r = normalize(p);
    return ( r );
}



/*
SELECT
*/
template <class _T>
	clemu_vector2<_T> select(clemu_vector2<_T> _a, clemu_vector2<_T> _b, clemu_vector2<char> _c)
	{
	 clemu_vector2<_T> tmp;
	     tmp.lo = isMSBset(_c.lo) ? _b.lo : _a.lo;
	     tmp.hi = isMSBset(_c.hi) ? _b.hi : _a.hi;
         return(tmp);
	}

template <class _T>
	clemu_vector2<_T> select(clemu_vector2<_T> _a, clemu_vector2<_T> _b, clemu_vector2<uchar> _c)
	{
	 clemu_vector2<_T> tmp;
	     tmp.lo = isMSBset(_c.lo) ? _b.lo : _a.lo;
	     tmp.hi = isMSBset(_c.hi) ? _b.hi : _a.hi;
         return(tmp);
	}
template <class _T>
	clemu_vector2<_T> select(clemu_vector2<_T> _a, clemu_vector2<_T> _b, clemu_vector2<short> _c)
	{
	 clemu_vector2<_T> tmp;
	     tmp.lo = isMSBset(_c.lo) ? _b.lo : _a.lo;
	     tmp.hi = isMSBset(_c.hi) ? _b.hi : _a.hi;
         return(tmp);
	}

template <class _T>
	clemu_vector2<_T> select(clemu_vector2<_T> _a, clemu_vector2<_T> _b, clemu_vector2<ushort> _c)
	{
	 clemu_vector2<_T> tmp;
	     tmp.lo = isMSBset(_c.lo) ? _b.lo : _a.lo;
	     tmp.hi = isMSBset(_c.hi) ? _b.hi : _a.hi;
         return(tmp);
	}

template <class _T>
	clemu_vector2<_T> select(clemu_vector2<_T> _a, clemu_vector2<_T> _b, clemu_vector2<int> _c)
	{
	 clemu_vector2<_T> tmp;
	     tmp.lo = isMSBset(_c.lo) ? _b.lo : _a.lo;
	     tmp.hi = isMSBset(_c.hi) ? _b.hi : _a.hi;
         return(tmp);
	}

template <class _T>
	clemu_vector2<_T> select(clemu_vector2<_T> _a, clemu_vector2<_T> _b, clemu_vector2<uint> _c)
	{
	 clemu_vector2<_T> tmp;
	     tmp.lo = isMSBset(_c.lo) ? _b.lo : _a.lo;
	     tmp.hi = isMSBset(_c.hi) ? _b.hi : _a.hi;
         return(tmp);
	}

static float2 select(float2 _a, float2 _b, char2 _c)
	{
	 float2 tmp;
	     tmp.x = isMSBset(_c.lo) ? _b.x : _a.x;
	     tmp.y = isMSBset(_c.hi) ? _b.y : _a.y;
         return(tmp);
	}

static float2 select(float2 _a, float2 _b, uchar2 _c)
	{
	 float2 tmp;
	     tmp.x = isMSBset(_c.lo) ? _b.x : _a.x;
	     tmp.y = isMSBset(_c.hi) ? _b.y : _a.y;
         return(tmp);
	}


static float2 select(float2 _a, float2 _b, short2 _c)
	{
	 float2 tmp;
	     tmp.x = isMSBset(_c.lo) ? _b.x : _a.x;
	     tmp.y = isMSBset(_c.hi) ? _b.y : _a.y;
         return(tmp);
	}

static float2 select(float2 _a, float2 _b, ushort2 _c)
	{
	 float2 tmp;
	     tmp.x = isMSBset(_c.lo) ? _b.x : _a.x;
	     tmp.y = isMSBset(_c.hi) ? _b.y : _a.y;
         return(tmp);
	}

static float2 select(float2 _a, float2 _b, int2 _c)
	{
	 float2 tmp;
	     tmp.x = isMSBset(_c.lo) ? _b.x : _a.x;
	     tmp.y = isMSBset(_c.hi) ? _b.y : _a.y;
         return(tmp);
	}

static float2 select(float2 _a, float2 _b, uint2 _c)
	{
	 float2 tmp;
	     tmp.x = isMSBset(_c.lo) ? _b.x : _a.x;
	     tmp.y = isMSBset(_c.hi) ? _b.y : _a.y;
         return(tmp);
	}

/*
4
*/

template <class _SRC>
  float4 convert_float4(clemu_vector4<_SRC> src)
  {
  float4 dst;
       dst.x = (float)src.x;
       dst.y = (float)src.y;
       dst.z = (float)src.z;
       dst.w = (float)src.w;
	   return dst;
  }

template <class _SRC>
  double4 convert_double4(clemu_vector4<_SRC> src)
  {
  double4 dst;
       dst.lo = convert_double2(src.lo);
       dst.hi = convert_double2(src.hi);
	   return dst;
  }



template <class _SRC>
  clemu_vector4<char> convert_char4(clemu_vector4<_SRC> src)
  {
    clemu_vector4<char> dst;
       dst.lo = convert_char2(src.lo);
       dst.hi = convert_char2(src.hi);
	   return dst;
  }
template <class _SRC>
  clemu_vector4<char> convert_uchar4(clemu_vector4<_SRC> src)
  {
    clemu_vector4<uchar> dst;
       dst.lo = convert_uchar2(src.lo);
       dst.hi = convert_uchar2(src.hi);
	   return dst;
  }

template <class _SRC>
  clemu_vector4<short> convert_short4(clemu_vector4<_SRC> src)
  {
    clemu_vector4<short> dst;
       dst.lo = convert_short2(src.lo);
       dst.hi = convert_short2(src.hi);
	   return dst;
  }
template <class _SRC>
  clemu_vector4<ushort> convert_ushort4(clemu_vector4<_SRC> src)
  {
    clemu_vector4<ushort> dst;
       dst.lo = convert_ushort2(src.lo);
       dst.hi = convert_ushort2(src.hi);
	   return dst;
  }
template <class _SRC>
  clemu_vector4<int> convert_int4(clemu_vector4<_SRC> src)
  {
    clemu_vector4<int> dst;
       dst.lo = convert_int2(src.lo);
       dst.hi = convert_int2(src.hi);
	   return dst;
  }
template <class _SRC>
  clemu_vector4<uint> convert_uint4(clemu_vector4<_SRC> src)
  {
    clemu_vector4<uint> dst;
       dst.lo = convert_uint2(src.lo);
       dst.hi = convert_uint2(src.hi);
	   return dst;
  }


template <class _SRC>
  uint4 as_uint4(clemu_vector4<_SRC> src)
  {
    uint4 dst;
       dst.lo = as_uint2(src.lo);
       dst.hi = as_uint2(src.hi);
	   return dst;

  }

template <class _SRC>
  int4 as_int4(clemu_vector4<_SRC> src)
  {
    int4 dst;
       dst.lo = as_int2(src.lo);
       dst.hi = as_int2(src.hi);
	   return dst;

  }

template <class _SRC>
  float4 as_float4(clemu_vector4<_SRC> src)
  {
    float4 dst;
       dst.lo = as_float2(src.lo);
       dst.hi = as_float2(src.hi);
	   return dst;

  }




/*
AMD_UNPACK
*/
static
float4 amd_unpack0 (uint4 src)
{
float4 ret;
    ret.lo = amd_unpack0(src.lo);
    ret.hi = amd_unpack0(src.hi);
    return(ret);
}
static
float4 amd_unpack1 (uint4 src)
{
float4 ret;
    ret.lo = amd_unpack1(src.lo);
    ret.hi = amd_unpack1(src.hi);
    return(ret);
}
static
float4 amd_unpack2 (uint4 src)
{
float4 ret;
    ret.lo = amd_unpack2(src.lo);
    ret.hi = amd_unpack2(src.hi);
    return(ret);
}
static
float4 amd_unpack3 (uint4 src)
{
float4 ret;
    ret.lo = amd_unpack3(src.lo);
    ret.hi = amd_unpack3(src.hi);
    return(ret);
}

/*
AMD_BITALIGN
*/
static
uint4 amd_bitalign (uint4 src0, uint4 src1, uint4 src2)
{
uint4 ret;
    ret.lo = amd_bitalign (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_bitalign (src0.hi, src1.hi, src2.hi);
    return(ret);
}
/*
AMD_BYTEALIGN
*/
static
uint4 amd_bytealign (uint4 src0, uint4 src1, uint4 src2)
{
uint4 ret;
    ret.lo = amd_bytealign (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_bytealign (src0.hi, src1.hi, src2.hi);
    return(ret);
}
/*
AMD_LERP
*/
static
uint4 amd_lerp (uint4 src0, uint4 src1, uint4 src2)
{
uint4 ret;
    ret.lo = amd_lerp (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_lerp (src0.hi, src1.hi, src2.hi);
    return(ret);
 }
/*
AMD_SAD
*/

static
uint4 amd_sad (uint4 src0, uint4 src1, uint4 src2)
{
uint4 ret;
    ret.lo = amd_sad (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_sad (src0.hi, src1.hi, src2.hi);
    return(ret);
}

static
uint4 amd_sadhi (uint4 src0, uint4 src1, uint4 src2)
{
uint4 ret;
    ret.lo = amd_sadhi (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_sadhi (src0.hi, src1.hi, src2.hi);
    return(ret);
}



static
uint  amd_sad4(uint4 src0, uint4 src1, uint src2)
{
 
   uint dst   = src2   + 
               abs((int)((src0.s0 >>  0) & 0xff) - (int)((src1.s0 >>  0) & 0xff)) +
               abs((int)((src0.s0 >>  8) & 0xff) - (int)((src1.s0 >>  8) & 0xff)) +
               abs((int)((src0.s0 >> 16) & 0xff) - (int)((src1.s0 >> 16) & 0xff)) +
               abs((int)((src0.s0 >> 24) & 0xff) - (int)((src1.s0 >> 24) & 0xff)) +
               abs((int)((src0.s1 >>  0) & 0xff) - (int)((src1.s0 >>  0) & 0xff)) +
               abs((int)((src0.s1 >>  8) & 0xff) - (int)((src1.s1 >>  8) & 0xff)) +
               abs((int)((src0.s1 >> 16) & 0xff) - (int)((src1.s1 >> 16) & 0xff)) +
               abs((int)((src0.s1 >> 24) & 0xff) - (int)((src1.s1 >> 24) & 0xff)) +
               abs((int)((src0.s2 >>  0) & 0xff) - (int)((src1.s2 >>  0) & 0xff)) +
               abs((int)((src0.s2 >>  8) & 0xff) - (int)((src1.s2 >>  8) & 0xff)) +
               abs((int)((src0.s2 >> 16) & 0xff) - (int)((src1.s2 >> 16) & 0xff)) +
               abs((int)((src0.s2 >> 24) & 0xff) - (int)((src1.s2 >> 24) & 0xff)) +
               abs((int)((src0.s3 >>  0) & 0xff) - (int)((src1.s3 >>  0) & 0xff)) +
               abs((int)((src0.s3 >>  8) & 0xff) - (int)((src1.s3 >>  8) & 0xff)) +
               abs((int)((src0.s3 >> 16) & 0xff) - (int)((src1.s3 >> 16) & 0xff)) +
               abs((int)((src0.s3 >> 24) & 0xff) - (int)((src1.s3 >> 24) & 0xff));
        return(dst);

}

/*
AMD_PACK
*/
static
uint amd_pack(float4 src)
{
	return ((((uint)src.x) & 0xFF) << 0) +
           ((((uint)src.y) & 0xFF) << 8) +
           ((((uint)src.z) & 0xFF) << 16) +
           ((((uint)src.w) & 0xFF) << 24);
}


/*------------------------------------------------------------------------------------
* 
* relational
*
* ----------------------------------------------------------------------------------*/

//Returns the component-wise compare of x == y.

static int4 isequal (float4 x, float4 y)
{
int4 r;
     r.lo = isequal (x.lo, y.lo);
     r.hi = isequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x != y.
static int4 isnotequal (float4 x, float4 y)
{
int4 r;
     r.lo = isnotequal (x.lo, y.lo);
     r.hi = isnotequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x > y.
static int4 isgreater (float4 x, float4 y)
{
int4 r;
     r.lo = isgreater (x.lo, y.lo);
     r.hi = isgreater (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x >= y.
static int4 isgreaterequal (float4 x, float4 y)
{
int4 r;
     r.lo = isgreaterequal (x.lo, y.lo);
     r.hi = isgreaterequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x < y.
static int4 isless (float4 x, float4 y)
{
int4 r;
     r.lo = isless (x.lo, y.lo);
     r.hi = isless (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x <= y.
static int4 islessequal (float4 x, float4 y)
{
int4 r;
     r.lo = islessequal (x.lo, y.lo);
     r.hi = islessequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of (x < y) || (x > y)
static int4 islessgreater (float4 x, float4 y)
{
int4 r;
     r.lo = islessgreater (x.lo, y.lo);
     r.hi = islessgreater (x.hi, y.hi);
     return(r);
}

static int4 isinf(float4 x)
{
int4 r;
     r.lo = isinf (x.lo);
     r.hi = isinf (x.hi);
     return(r);
}


static int4 isfinite(float4 x)
{
int4 r;
     r.lo = isfinite (x.lo);
     r.hi = isfinite (x.hi);
     return(r);
}
static int4 isnan(float4 x)
{
int4 r;
     r.lo = isnan (x.lo);
     r.hi = isnan (x.hi);
     return(r);
}
static int4 isnormal(float4 x)
{
int4 r;
     r.lo = isnormal (x.lo);
     r.hi = isnormal (x.hi);
     return(r);
}

//Test if arguments are ordered. isordered() takes
//arguments x and y, and returns the result
//isequal(x, x) && isequal(y, y).

static int4 isordered (float4 x, float4 y)
{
int4 r;
     r.lo = isordered (x.lo, y.lo);
     r.hi = isordered (x.hi, y.hi);
     return(r);
}

//Test if arguments are unordered. isunordered() takes
//arguments x and y, returning non-zero if x or y is NaN,
//and zero otherwise.
static int4 isunordered (float4 x, float4 y)
{
int4 r;
     r.lo = isunordered (x.lo, y.lo);
     r.hi = isunordered (x.hi, y.hi);
     return(r);
}

//Test for sign bit. The scalar version of the function
//returns a 1 if the sign bit in the float is set else returns 0.
//The vector version of the function returns the following
//for each component in floatn: a -1 if the sign bit in the
//float is set else returns 0.
static int4 signbit (float4 x)
{
int4 r;
     r.lo = signbit (x.lo);
     r.hi = signbit (x.hi);
     return(r);
}



//Returns the component-wise compare of x == y.

static __LONG4 isequal (double4 x, double4 y)
{
__LONG4 r;
     r.lo = isequal (x.lo, y.lo);
     r.hi = isequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x != y.
static __LONG4 isnotequal (double4 x, double4 y)
{
__LONG4 r;
     r.lo = isnotequal (x.lo, y.lo);
     r.hi = isnotequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x > y.
static __LONG4 isgreater (double4 x, double4 y)
{
__LONG4 r;
     r.lo = isgreater (x.lo, y.lo);
     r.hi = isgreater (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x >= y.
static __LONG4 isgreaterequal (double4 x, double4 y)
{
__LONG4 r;
     r.lo = isgreaterequal (x.lo, y.lo);
     r.hi = isgreaterequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x < y.
static __LONG4 isless (double4 x, double4 y)
{
__LONG4 r;
     r.lo = isless (x.lo, y.lo);
     r.hi = isless (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x <= y.
static __LONG4 islessequal (double4 x, double4 y)
{
__LONG4 r;
     r.lo = islessequal (x.lo, y.lo);
     r.hi = islessequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of (x < y) || (x > y)
static __LONG4 islessgreater (double4 x, double4 y)
{
__LONG4 r;
     r.lo = islessgreater (x.lo, y.lo);
     r.hi = islessgreater (x.hi, y.hi);
     return(r);
}

static __LONG4 isinf(double4 x)
{
__LONG4 r;
     r.lo = isinf (x.lo);
     r.hi = isinf (x.hi);
     return(r);
}


static __LONG4 isfinite(double4 x)
{
__LONG4 r;
     r.lo = isfinite (x.lo);
     r.hi = isfinite (x.hi);
     return(r);
}
static __LONG4 isnan(double4 x)
{
__LONG4 r;
     r.lo = isnan (x.lo);
     r.hi = isnan (x.hi);
     return(r);
}
static __LONG4 isnormal(double4 x)
{
__LONG4 r;
     r.lo = isnormal (x.lo);
     r.hi = isnormal (x.hi);
     return(r);
}

//Test if arguments are ordered. isordered() takes
//arguments x and y, and returns the result
//isequal(x, x) && isequal(y, y).

static __LONG4 isordered (double4 x, double4 y)
{
__LONG4 r;
     r.lo = isordered (x.lo, y.lo);
     r.hi = isordered (x.hi, y.hi);
     return(r);
}

//Test if arguments are unordered. isunordered() takes
//arguments x and y, returning non-zero if x or y is NaN,
//and zero otherwise.
static __LONG4 isunordered (double4 x, double4 y)
{
__LONG4 r;
     r.lo = isunordered (x.lo, y.lo);
     r.hi = isunordered (x.hi, y.hi);
     return(r);
}

//Test for sign bit. The scalar version of the function
//returns a 1 if the sign bit in the float is set else returns 0.
//The vector version of the function returns the following
//for each component in floatn: a -1 if the sign bit in the
//float is set else returns 0.
static __LONG4 signbit (double4 x)
{
__LONG4 r;
     r.lo = signbit (x.lo);
     r.hi = signbit (x.hi);
     return(r);
}




/*
ACOS
*/


static float4 acos( float4 _a)
{
float4 ret;
       ret.lo = acos(_a.lo);
       ret.hi = acos(_a.hi);
	   return ret;
}

static double4 acos( double4 _a)
{
double4 ret;
       ret.lo = acos(_a.lo);
       ret.hi = acos(_a.hi);
	   return ret;
}

// ACOSH

static float4 acosh( float4 _a)
{
float4 ret;
       ret.lo = acosh(_a.lo);
       ret.hi = acosh(_a.hi);
	   return ret;
}

static double4 acosh( double4 _a)
{
double4 ret;
       ret.lo = acosh(_a.lo);
       ret.hi = acosh(_a.hi);
	   return ret;
}

// ACOSPI

static float4 acospi( float4 _a)
{
float4 ret;
       ret.lo = acospi(_a.lo);
       ret.hi = acospi(_a.hi);
	   return ret;
}

static double4 acospi( double4 _a)
{
double4 ret;
       ret.lo = acospi(_a.lo);
       ret.hi = acospi(_a.hi);
	   return ret;
}


// ASIN

static float4 asin( float4 _a)
{
float4 ret;
       ret.lo = asin(_a.lo);
       ret.hi = asin(_a.hi);
	   return ret;
}

static double4 asin( double4 _a)
{
double4 ret;
       ret.lo = asin(_a.lo);
       ret.hi = asin(_a.hi);
	   return ret;
}


// ASINH

static float4 asinh( float4 _a)
{
float4 ret;
       ret.lo = asinh(_a.lo);
       ret.hi = asinh(_a.hi);
	   return ret;
}

static double4 asinh( double4 _a)
{
double4 ret;
       ret.lo = asinh(_a.lo);
       ret.hi = asinh(_a.hi);
	   return ret;
}

// ASINPI

static float4 asinpi( float4 _a)
{
float4 ret;
       ret.lo = asinpi(_a.lo);
       ret.hi = asinpi(_a.hi);
	   return ret;
}

static double4 asinpi( double4 _a)
{
double4 ret;
       ret.lo = asinpi(_a.lo);
       ret.hi = asinpi(_a.hi);
	   return ret;
}


// ATAN

static float4 atan( float4 _a)
{
float4 ret;
       ret.lo = atan(_a.lo);
       ret.hi = atan(_a.hi);
	   return ret;
}

static double4 atan( double4 _a)
{
double4 ret;
       ret.lo = atan(_a.lo);
       ret.hi = atan(_a.hi);
	   return ret;
}

// ATAN2

static float4 atan2( float4 _a, float4 _b)
{
float4 ret;
       ret.lo = atan2(_a.lo, _b.lo);
       ret.hi = atan2(_a.hi, _b.hi);
	   return ret;
}

static double4 atan2( double4 _a, double4 _b)
{
double4 ret;
       ret.lo = atan2(_a.lo, _b.lo);
       ret.hi = atan2(_a.hi, _b.hi);
	   return ret;
}

// ATANH

static float4 atanh( float4 _a)
{
float4 ret;
       ret.lo = atanh(_a.lo);
       ret.hi = atanh(_a.hi);
	   return ret;
}

static double4 atanh( double4 _a)
{
double4 ret;
       ret.lo = atanh(_a.lo);
       ret.hi = atanh(_a.hi);
	   return ret;
}

// ATANPI

static float4 atanpi( float4 _a)
{
float4 ret;
       ret.lo = atanpi(_a.lo);
       ret.hi = atanpi(_a.hi);
	   return ret;
}

static double4 atanpi( double4 _a)
{
double4 ret;
       ret.lo = atanpi(_a.lo);
       ret.hi = atanpi(_a.hi);
	   return ret;
}

// ATAN2

static float4 atan2pi( float4 _a, float4 _b)
{
float4 ret;
       ret.lo = atan2pi(_a.lo, _b.lo);
       ret.hi = atan2pi(_a.hi, _b.hi);
	   return ret;
}

static double4 atan2pi( double4 _a, double4 _b)
{
double4 ret;
       ret.lo = atan2pi(_a.lo, _b.lo);
       ret.hi = atan2pi(_a.hi, _b.hi);
	   return ret;
}

// CBRT
static float4 cbrt( float4 _a)
{
float4 ret;
       ret.lo = cbrt(_a.lo);
       ret.hi = cbrt(_a.hi);
	   return ret;
}

static double4 cbrt( double4 _a)
{
double4 ret;
       ret.lo = cbrt(_a.lo);
       ret.hi = cbrt(_a.hi);
	   return ret;
}



// CEIL
static float4 ceil( float4 _a)
{
float4 ret;
       ret.lo = ceil(_a.lo);
       ret.hi = ceil(_a.hi);
	   return ret;
}

static double4 ceil( double4 _a)
{
double4 ret;
       ret.lo = ceil(_a.lo);
       ret.hi = ceil(_a.hi);
	   return ret;
}




// ATAN2

static float4 copysign( float4 _a, float4 _b)
{
float4 ret;
       ret.lo = copysign(_a.lo, _b.lo);
       ret.hi = copysign(_a.hi, _b.hi);
	   return ret;
}

static double4 copysign( double4 _a, double4 _b)
{
double4 ret;
       ret.lo = copysign(_a.lo, _b.lo);
       ret.hi = copysign(_a.hi, _b.hi);
	   return ret;
}



// COS

static float4 cos( float4 _a)
{
float4 ret;
       ret.lo = cos(_a.lo);
       ret.hi = cos(_a.hi);
	   return ret;
}

static double4 cos( double4 _a)
{
double4 ret;
       ret.lo = cos(_a.lo);
       ret.hi = cos(_a.hi);
	   return ret;
}

// COSH

static float4 cosh( float4 _a)
{
float4 ret;
       ret.lo = cosh(_a.lo);
       ret.hi = cosh(_a.hi);
	   return ret;
}

static double4 cosh( double4 _a)
{
double4 ret;
       ret.lo = cosh(_a.lo);
       ret.hi = cosh(_a.hi);
	   return ret;
}

// COSPI

static float4 cospi( float4 _a)
{
float4 ret;
       ret.lo = cospi(_a.lo);
       ret.hi = cospi(_a.hi);
	   return ret;
}

static double4 cospi( double4 _a)
{
double4 ret;
       ret.lo = cospi(_a.lo);
       ret.hi = cospi(_a.hi);
	   return ret;
}

// ERFC

static float4 erfc( float4 _a)
{
float4 ret;
       ret.lo = erfc(_a.lo);
       ret.hi = erfc(_a.hi);
	   return ret;
}

static double4 erfc( double4 _a)
{
double4 ret;
       ret.lo = erfc(_a.lo);
       ret.hi = erfc(_a.hi);
	   return ret;
}


// ERF


static float4 erf( float4 _a)
{
float4 ret;
       ret.lo = erf(_a.lo);
       ret.hi = erf(_a.hi);
	   return ret;
}

static double4 erf( double4 _a)
{
double4 ret;
       ret.lo = erf(_a.lo);
       ret.hi = erf(_a.hi);
	   return ret;
}


// EXP
static float4 exp( float4 _a)
{
float4 ret;
       ret.lo = exp(_a.lo);
       ret.hi = exp(_a.hi);
	   return ret;
}

static double4 exp( double4 _a)
{
double4 ret;
       ret.lo = exp(_a.lo);
       ret.hi = exp(_a.hi);
	   return ret;
}

// EXP2

static float4 exp2( float4 _a)
{
float4 ret;
       ret.lo = exp2(_a.lo);
       ret.hi = exp2(_a.hi);
	   return ret;
}

static double4 exp2( double4 _a)
{
double4 ret;
       ret.lo = exp2(_a.lo);
       ret.hi = exp2(_a.hi);
	   return ret;
}

// EXP10

static float4 exp10( float4 _a)
{
float4 ret;
       ret.lo = exp10(_a.lo);
       ret.hi = exp10(_a.hi);
	   return ret;
}

static double4 exp10( double4 _a)
{
double4 ret;
       ret.lo = exp10(_a.lo);
       ret.hi = exp10(_a.hi);
	   return ret;
}

// EXPM1
static float4 expm1( float4 _a)
{
float4 ret;
       ret.lo = expm1(_a.lo);
       ret.hi = expm1(_a.hi);
	   return ret;
}

static double4 expm1( double4 _a)
{
double4 ret;
       ret.lo = expm1(_a.lo);
       ret.hi = expm1(_a.hi);
	   return ret;
}


// FABS
static float4 fabs( float4 _a)
{
float4 ret;
       ret.lo = fabs(_a.lo);
       ret.hi = fabs(_a.hi);
	   return ret;
}

static double4 fabs( double4 _a)
{
double4 ret;
       ret.lo = fabs(_a.lo);
       ret.hi = fabs(_a.hi);
	   return ret;
}

// FDIM
static double4 fdim( double4 _a, double4 _b)
{
double4 ret;
       ret.lo = fdim(_a.lo, _b.lo);
       ret.hi = fdim(_a.hi, _b.hi);
	   return ret;
}

static float4 fdim( float4 _a, float4 _b)
{
float4 ret;
       ret.lo = fdim(_a.lo, _b.lo);
       ret.hi = fdim(_a.hi, _b.hi);
	   return ret;
}



// FLOOR

static float4 floor( float4 _a)
{
float4 ret;
       ret.lo = floor(_a.lo);
       ret.hi = floor(_a.hi);
	   return ret;
}

static double4 floor( double4 _a)
{
double4 ret;
       ret.lo = floor(_a.lo);
       ret.hi = floor(_a.hi);
	   return ret;
}

// FMA

static float4 fma( float4 _a, float4 _b, float4 _c)
{
float4 ret;
       ret.lo = fma(_a.lo,_b.lo,_c.lo);
       ret.hi = fma(_a.hi,_b.hi,_c.hi);
	   return(ret);
}


static double4 fma( double4 _a, double4 _b, double4 _c)
{
double4 ret;
       ret.lo = fma(_a.lo,_b.lo,_c.lo);
       ret.hi = fma(_a.hi,_b.hi,_c.hi);
	   return(ret);
}


// FMAX

static float4 fmax( float4 _a, float4 _b)
{
float4 ret;
       ret.lo = fmax(_a.lo,_b.lo);
       ret.hi = fmax(_a.hi,_b.hi);
	   return(ret);
}


static double4 fmax( double4 _a, double4 _b)
{
double4 ret;
       ret.lo = fmax(_a.lo,_b.lo);
       ret.hi = fmax(_a.hi,_b.hi);
	   return(ret);
}

// FMIN

static float4 fmin( float4 _a, float4 _b)
{
float4 ret;
       ret.lo = fmin(_a.lo,_b.lo);
       ret.hi = fmin(_a.hi,_b.hi);
	   return(ret);
}


static double4 fmin( double4 _a, double4 _b)
{
double4 ret;
       ret.lo = fmin(_a.lo,_b.lo);
       ret.hi = fmin(_a.hi,_b.hi);
	   return(ret);
}


// FMOD
static float4 fmod( float4 _a, float4 _b)
{
float4 ret;
       ret.lo = fmod(_a.lo, _b.lo);
       ret.hi = fmod(_a.hi, _b.hi);
	   return ret;
}

static double4 fmod( double4 _a, double4 _b)
{
double4 ret;
       ret.lo = fmod(_a.lo, _b.lo);
       ret.hi = fmod(_a.hi, _b.hi);
	   return ret;
}







// FRAC

static float4 frac( float4 _a)
{
float4 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}

static double4 frac( double4 _a)
{
double4 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}


// FRACT

static float4 fract( float4 _a)
{
float4 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}

static double4 fract( double4 _a)
{
double4 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}

// FREXP

static float4 frexp( float4 _a, int4* _b)
{
float4 ret;
       ret.lo = frexp(_a.lo, &_b->lo);
       ret.hi = frexp(_a.hi, &_b->hi);
	   return ret;
}

static double4 frexp( double4 _a, int4* _b)
{
double4 ret;
       ret.lo = frexp(_a.lo, &_b->lo);
       ret.hi = frexp(_a.hi, &_b->hi);
	   return ret;
}

// HYPOT

static float4 hypot( float4 _a, float4 _b)
{
float4 ret;
       ret.lo = hypot(_a.lo, _b.lo);
       ret.hi = hypot(_a.hi, _b.hi);
	   return ret;
}

static double4 hypot( double4 _a, double4 _b)
{
double4 ret;
       ret.lo = hypot(_a.lo, _b.lo);
       ret.hi = hypot(_a.hi, _b.hi);
	   return ret;
}

// ILOGB

static int4 ilogb( float4 _a)
{
int4 ret;
       ret.lo = ilogb(_a.lo);
       ret.hi = ilogb(_a.hi);
	   return ret;
}

static int4 ilogb( double4 _a)
{
int4 ret;
       ret.lo = ilogb(_a.lo);
       ret.hi = ilogb(_a.hi);
	   return ret;
}

// LDEXP

static float4 ldexp( float4 _a, int4 _b)
{
float4 ret;
       ret.lo = ldexp(_a.lo, _b.lo);
       ret.hi = ldexp(_a.hi, _b.hi);
	   return ret;
}

static double4 ldexp( double4 _a, int4 _b)
{
double4 ret;
       ret.lo = ldexp(_a.lo, _b.lo);
       ret.hi = ldexp(_a.hi, _b.hi);
	   return ret;
}

static float4 ldexp( float4 _a, int _b)
{
float4 ret;
       ret = ldexp(_a, (int4)_b);
	   return ret;
}

static double4 ldexp( double4 _a, int _b)
{
double4 ret;
       ret = ldexp(_a, (int4)_b);
	   return ret;
}

// LGAMMA
static float4 lgamma( float4 _a)
{
float4 ret;
       ret.lo = lgamma(_a.lo);
       ret.hi = lgamma(_a.hi);
	   return ret;
}

static double4 lgamma( double4 _a)
{
double4 ret;
       ret.lo = lgamma(_a.lo);
       ret.hi = lgamma(_a.hi);
	   return ret;
}

// LGAMMA_R

static float4 lgamma_r( float4 _a, int4 *psign)
{
float4 ret;
       ret.lo = lgamma_r(_a.lo, &psign->lo);
       ret.hi = lgamma_r(_a.hi, &psign->hi);
	   return ret;
}

static double4 lgamma_r( double4 _a, int4 *psign)
{
double4 ret;
       ret.lo = lgamma_r(_a.lo, &psign->lo);
       ret.hi = lgamma_r(_a.hi, &psign->hi);
	   return ret;
}

// LOG

static float4 log( float4 _a)
{
float4 ret;
       ret.lo = log(_a.lo);
       ret.hi = log(_a.hi);
	   return ret;
}

static double4 log( double4 _a)
{
double4 ret;
       ret.lo = log(_a.lo);
       ret.hi = log(_a.hi);
	   return ret;
}

// LOG2

static float4 log2( float4 _a)
{
float4 ret;
       ret.lo = log2(_a.lo);
       ret.hi = log2(_a.hi);
	   return ret;
}

static double4 log2( double4 _a)
{
double4 ret;
       ret.lo = log2(_a.lo);
       ret.hi = log2(_a.hi);
	   return ret;
}


// LOG10

static float4 log10( float4 _a)
{
float4 ret;
       ret.lo = log10(_a.lo);
       ret.hi = log10(_a.hi);
	   return ret;
}

static double4 log10( double4 _a)
{
double4 ret;
       ret.lo = log10(_a.lo);
       ret.hi = log10(_a.hi);
	   return ret;
}

// LOG1P

static float4 log1p( float4 _a)
{
float4 ret;
       ret.lo = log1p(_a.lo);
       ret.hi = log1p(_a.hi);
	   return ret;
}

static double4 log1p( double4 _a)
{
double4 ret;
       ret.lo = log1p(_a.lo);
       ret.hi = log1p(_a.hi);
	   return ret;
}


// LOGB

static float4 logb( float4 _a)
{
float4 ret;
       ret.lo = logb(_a.lo);
       ret.hi = logb(_a.hi);
	   return ret;
}

static double4 logb( double4 _a)
{
double4 ret;
       ret.lo = logb(_a.lo);
       ret.hi = logb(_a.hi);
	   return ret;
}


// mad

static float4 mad( float4 _a, float4 _b, float4 _c)
{
float4 ret;
       ret.lo = mad(_a.lo, _b.lo, _c.lo);
       ret.hi = mad(_a.hi, _b.hi, _c.hi);
	   return ret;
}

static double4 mad( double4 _a, double4 _b, double4 _c)
{
double4 ret;
       ret.lo = mad(_a.lo, _b.lo, _c.lo);
       ret.hi = mad(_a.hi, _b.hi, _c.hi);
	   return ret;
}


// mogf

static float4 modf( float4 _a, int4* _b)
{
float4 ret;
       ret.lo = modf(_a.lo, &_b->lo);
       ret.hi = modf(_a.hi, &_b->hi);
	   return ret;
}

static double4 modf( double4 _a, int4* _b)
{
double4 ret;
       ret.lo = modf(_a.lo, &_b->lo);
       ret.hi = modf(_a.hi, &_b->hi);
	   return ret;
}

//NAN
static float4 nan( int4 _b)
{
float4 ret;
       ret.lo = nan(_b.lo);
       ret.hi = nan(_b.hi);
	   return ret;
}
static double4 nan( __LONG4 _b)
{
double4 ret;
       ret.lo = nan(_b.lo);
       ret.hi = nan(_b.hi);
	   return ret;
}

// NEXTAFTER
static float4 nextafter( float4 _a, float4 _b)
{
float4 ret;
       ret.lo = nextafter(_a.lo, _b.lo);
       ret.hi = nextafter(_a.hi, _b.hi);
	   return ret;
}
static double4 nextafter( double4 _a, double4 _b)
{
double4 ret;
       ret.lo = nextafter(_a.lo, _b.lo);
       ret.hi = nextafter(_a.hi, _b.hi);
	   return ret;
}

// POW
static float4 pow( float4 _a, float4 _b)
{
float4 ret;
       ret.lo = pow(_a.lo, _b.lo);
       ret.hi = pow(_a.hi, _b.hi);
	   return ret;
}

static double4 pow( double4 _a, double4 _b)
{
double4 ret;
       ret.lo = pow(_a.lo, _b.lo);
       ret.hi = pow(_a.hi, _b.hi);
	   return ret;
}

// POWN
static double4 pown( double4 _a, int4 _b)
{
double4 ret;
       ret.lo = pown(_a.lo, _b.lo);
       ret.hi = pown(_a.hi, _b.hi);
	   return ret;
}

static float4 pown( float4 _a, int4 _b)
{
float4 ret;
       ret.lo = pown(_a.lo, _b.lo);
       ret.hi = pown(_a.hi, _b.hi);
	   return ret;
}

// POWR
static double4 powr( double4 _a, double4 _b)
{
double4 ret;
       ret.lo = powr(_a.lo, _b.lo);
       ret.hi = powr(_a.hi, _b.hi);
	   return ret;
}

static float4 powr( float4 _a, float4 _b)
{
float4 ret;
       ret.lo = powr(_a.lo, _b.lo);
       ret.hi = powr(_a.hi, _b.hi);
	   return ret;
}

// REMAINDER
static
float4 remainder(float4 x, float4 p)
{
float4 ret;
        ret.lo = remainder(x.lo, p.lo);
        ret.hi = remainder(x.hi, p.hi);
		return(ret);
}

static
double4 remainder(double4 x, double4 p)
{
double4 ret;
        ret.lo = remainder(x.lo, p.lo);
        ret.hi = remainder(x.hi, p.hi);
		return(ret);
}


// REMQUO
static
float4 remquo(float4 x, float4 p, int4 *pquo)
{
float4 ret;
        ret.lo = remquo(x.lo, p.lo, &pquo->lo);
        ret.hi = remquo(x.hi, p.hi, &pquo->hi);
		return(ret);
}

static
double4 remquo(double4 x, double4 p, int4 *pquo)
{
double4 ret;
        ret.lo = remquo(x.lo, p.lo, &pquo->lo);
        ret.hi = remquo(x.hi, p.hi, &pquo->hi);
		return(ret);
}


// RINT

static float4
rint (float4 x)
{
float4 ret;
       ret.lo = rint(x.lo);
       ret.hi = rint(x.hi);
	   return(ret);
}

static double4
rint (double4 x)
{
double4 ret;
       ret.lo = rint(x.lo);
       ret.hi = rint(x.hi);
	   return(ret);
}

// ROOTN
static float4 rootn( float4 _a, int4 _n)
{
float4 ret;
       ret.lo = rootn(_a.lo, _n.lo);
       ret.hi = rootn(_a.hi, _n.hi);
	   return ret;
}

static double4 rootn( double4 _a, int4 _n)
{
double4 ret;
       ret.lo = rootn(_a.lo, _n.lo);
       ret.hi = rootn(_a.hi, _n.hi);
	   return ret;
}

//ROUND

static float4 round( float4 _a)
{
float4 ret;
       ret.lo = round(_a.lo);
       ret.hi = round(_a.hi);
	   return ret;
}

static double4 round( double4 _a)
{
double4 ret;
       ret.lo = round(_a.lo);
       ret.hi = round(_a.hi);
	   return ret;
}


//RSQRT

static float4 rsqrt( float4 _a)
{
float4 ret;
       ret.lo = rsqrt(_a.lo);
       ret.hi = rsqrt(_a.hi);
	   return ret;
}

static double4 rsqrt( double4 _a)
{
double4 ret;
       ret.lo = rsqrt(_a.lo);
       ret.hi = rsqrt(_a.hi);
	   return ret;
}

//SIN

static float4 sin( float4 _a)
{
float4 ret;
       ret.lo = sin(_a.lo);
       ret.hi = sin(_a.hi);
	   return ret;
}

static double4 sin( double4 _a)
{
double4 ret;
       ret.lo = sin(_a.lo);
       ret.hi = sin(_a.hi);
	   return ret;
}

//SINCOS

static float4 sincos( float4 _a, float4*_b)
{
float4 ret;
       ret.lo = sincos(_a.lo, &_b->lo);
       ret.hi = sincos(_a.hi, &_b->hi);
	   return ret;
}

static double4 sincos( double4 _a, double4*_b)
{
double4 ret;
       ret.lo = sincos(_a.lo, &_b->lo);
       ret.hi = sincos(_a.hi, &_b->hi);
	   return ret;
}

//SINH

static float4 sinh( float4 _a)
{
float4 ret;
       ret.lo = sinh(_a.lo);
       ret.hi = sinh(_a.hi);
	   return ret;
}

static double4 sinh( double4 _a)
{
double4 ret;
       ret.lo = sinh(_a.lo);
       ret.hi = sinh(_a.hi);
	   return ret;
}


//SINPI

static float4 sinpi( float4 _a)
{
float4 ret;
       ret.lo = sinpi(_a.lo);
       ret.hi = sinpi(_a.hi);
	   return ret;
}

static double4 sinpi( double4 _a)
{
double4 ret;
       ret.lo = sinpi(_a.lo);
       ret.hi = sinpi(_a.hi);
	   return ret;
}


//SQRT

static float4 sqrt( float4 _a)
{
float4 ret;
       ret.lo = sqrt(_a.lo);
       ret.hi = sqrt(_a.hi);
	   return ret;
}

static double4 sqrt( double4 _a)
{
double4 ret;
       ret.lo = sqrt(_a.lo);
       ret.hi = sqrt(_a.hi);
	   return ret;
}

//TAN

static float4 tan( float4 _a)
{
float4 ret;
       ret.lo = tan(_a.lo);
       ret.hi = tan(_a.hi);
	   return ret;
}

static double4 tan( double4 _a)
{
double4 ret;
       ret.lo = tan(_a.lo);
       ret.hi = tan(_a.hi);
	   return ret;
}

//TANH

static float4 tanh( float4 _a)
{
float4 ret;
       ret.lo = tanh(_a.lo);
       ret.hi = tanh(_a.hi);
	   return ret;
}

static double4 tanh( double4 _a)
{
double4 ret;
       ret.lo = tanh(_a.lo);
       ret.hi = tanh(_a.hi);
	   return ret;
}

//TANPI

static float4 tanpi( float4 _a)
{
float4 ret;
       ret.lo = tanpi(_a.lo);
       ret.hi = tanpi(_a.hi);
	   return ret;
}

static double4 tanpi( double4 _a)
{
double4 ret;
       ret.lo = tanpi(_a.lo);
       ret.hi = tanpi(_a.hi);
	   return ret;
}





// TGAMMA
static float4 tgamma( float4 _a)
{
float4 ret;
       ret.lo = tgamma(_a.lo);
       ret.hi = tgamma(_a.hi);
	   return ret;
}
static double4 tgamma( double4 _a)
{
double4 ret;
       ret.lo = tgamma(_a.lo);
       ret.hi = tgamma(_a.hi);
	   return ret;
}

// TRUNC

static float4 trunc( float4 _a)
{
float4 ret;
       ret.lo = trunc(_a.lo);
       ret.hi = trunc(_a.hi);
	   return ret;
}

static double4 trunc( double4 _a)
{
double4 ret;
       ret.lo = trunc(_a.lo);
       ret.hi = trunc(_a.hi);
	   return ret;
}

static float4 native_cos( float4 _a)
{
float4 ret;
       ret.lo = native_cos(_a.lo);
       ret.hi = native_cos(_a.hi);
	   return ret;
}

static double4 native_cos( double4 _a)
{
double4 ret;
       ret.lo = native_cos(_a.lo);
       ret.hi = native_cos(_a.hi);
	   return ret;
}


static double4 native_divide( double4 _a, double4 _b)
{
double4 ret;
       ret.lo = native_divide(_a.lo, _b.lo);
       ret.hi = native_divide(_a.hi, _b.hi);
	   return ret;
}

static float4 native_divide( float4 _a, float4 _b)
{
float4 ret;
       ret.lo = native_divide(_a.lo, _b.lo);
       ret.hi = native_divide(_a.hi, _b.hi);
	   return ret;
}

static float4 native_exp( float4 _a)
{
float4 ret;
       ret.lo = native_exp(_a.lo);
       ret.hi = native_exp(_a.hi);
	   return ret;
}

static double4 native_exp( double4 _a)
{
double4 ret;
       ret.lo = native_exp(_a.lo);
       ret.hi = native_exp(_a.hi);
	   return ret;
}

static float4 native_exp2( float4 _a)
{
float4 ret;
       ret.lo = native_exp2(_a.lo);
       ret.hi = native_exp2(_a.hi);
	   return ret;
}

static double4 native_exp2( double4 _a)
{
double4 ret;
       ret.lo = native_exp2(_a.lo);
       ret.hi = native_exp2(_a.hi);
	   return ret;
}

static float4 native_exp10( float4 _a)
{
float4 ret;
       ret.lo = native_exp10(_a.lo);
       ret.hi = native_exp10(_a.hi);
	   return ret;
}

static double4 native_exp10( double4 _a)
{
double4 ret;
       ret.lo = native_exp10(_a.lo);
       ret.hi = native_exp10(_a.hi);
	   return ret;
}

static float4 native_log( float4 _a)
{
float4 ret;
       ret.lo = native_log(_a.lo);
       ret.hi = native_log(_a.hi);
	   return ret;
}

static double4 native_log( double4 _a)
{
double4 ret;
       ret.lo = native_log(_a.lo);
       ret.hi = native_log(_a.hi);
	   return ret;
}

static float4 native_log2( float4 _a)
{
float4 ret;
       ret.lo = native_log2(_a.lo);
       ret.hi = native_log2(_a.hi);
	   return ret;
}

static double4 native_log2( double4 _a)
{
double4 ret;
       ret.lo = native_log2(_a.lo);
       ret.hi = native_log2(_a.hi);
	   return ret;
}

static float4 native_log10( float4 _a)
{
float4 ret;
       ret.lo = native_log10(_a.lo);
       ret.hi = native_log10(_a.hi);
	   return ret;
}

static double4 native_log10( double4 _a)
{
double4 ret;
       ret.lo = native_log10(_a.lo);
       ret.hi = native_log10(_a.hi);
	   return ret;
}

static float4 native_powr( float4 _a, float4 _b)
{
float4 ret;
       ret.lo = native_powr(_a.lo, _b.lo);
       ret.hi = native_powr(_a.hi, _b.hi);
	   return ret;
}

static double4 native_powr( double4 _a, double4 _b)
{
double4 ret;
       ret.lo = native_powr(_a.lo, _b.lo);
       ret.hi = native_powr(_a.hi, _b.hi);
	   return ret;
}

static float4 native_recip( float4 _a)
{
float4 ret;
       ret.lo = native_recip(_a.lo);
       ret.hi = native_recip(_a.hi);
	   return ret;
}

static double4 native_recip( double4 _a)
{
double4 ret;
       ret.lo = native_recip(_a.lo);
       ret.hi = native_recip(_a.hi);
	   return ret;
}

static float4 native_rsqrt( float4 _a)
{
float4 ret;
       ret.lo = native_rsqrt(_a.lo);
       ret.hi = native_rsqrt(_a.hi);
	   return ret;
}

static double4 native_rsqrt( double4 _a)
{
double4 ret;
       ret.lo = native_rsqrt(_a.lo);
       ret.hi = native_rsqrt(_a.hi);
	   return ret;
}

static float4 native_sin( float4 _a)
{
float4 ret;
       ret.lo = native_sin(_a.lo);
       ret.hi = native_sin(_a.hi);
	   return ret;
}

static double4 native_sin( double4 _a)
{
double4 ret;
       ret.lo = native_sin(_a.lo);
       ret.hi = native_sin(_a.hi);
	   return ret;
}

static float4 native_sqrt( float4 _a)
{
float4 ret;
       ret.lo = native_sqrt(_a.lo);
       ret.hi = native_sqrt(_a.hi);
	   return ret;
}

static double4 native_sqrt( double4 _a)
{
double4 ret;
       ret.lo = native_sqrt(_a.lo);
       ret.hi = native_sqrt(_a.hi);
	   return ret;
}

static float4 native_tan( float4 _a)
{
float4 ret;
       ret.lo = native_tan(_a.lo);
       ret.hi = native_tan(_a.hi);
	   return ret;
}

static double4 native_tan( double4 _a)
{
double4 ret;
       ret.lo = native_tan(_a.lo);
       ret.hi = native_tan(_a.hi);
	   return ret;
}



// CLAMP
static float4 clamp( float4 _a, float4 _min, float4 _max)
{
float4 ret;
       ret.lo = clamp(_a.lo, _min.lo, _max.lo);
       ret.hi = clamp(_a.hi, _min.hi, _max.hi);
	   return ret;
}

static double4 clamp( double4 _a, double4 _min, double4 _max)
{
double4 ret;
       ret.lo = clamp(_a.lo, _min.lo, _max.lo);
       ret.hi = clamp(_a.hi, _min.hi, _max.hi);
	   return ret;
}

// DEGREES
static double4
degrees(double4 radians)
{
double4 ret;
    ret.lo = degrees(radians.lo);
    ret.hi = degrees(radians.hi);
    return(ret);
}

static float4
degrees(float4 radians)
{
float4 ret;
    ret.lo = degrees(radians.lo);
    ret.hi = degrees(radians.hi);
    return(ret);
}




//MAX
float4
static max(float4 x, float4 y)
{
float4 r;
    r.lo = max(x.lo, y.lo);
    r.hi = max(x.hi, y.hi);
    return(r);
}

double4
static max(double4 x, double4 y)
{
double4 r;
    r.lo = max(x.lo, y.lo);
    r.hi = max(x.hi, y.hi);
    return(r);
}

//MIN
float4
static min(float4 x, float4 y)
{
float4 r;
    r.lo = min(x.lo, y.lo);
    r.hi = min(x.hi, y.hi);
    return(r);
}

double4
static min(double4 x, double4 y)
{
double4 r;
    r.lo = min(x.lo, y.lo);
    r.hi = min(x.hi, y.hi);
    return(r);
}


// MIX
static double4
mix(double4 x, double4 y, double4 a)
{
double4 r;
	r.lo = mix(x.lo, y.lo, a.lo);
	r.hi = mix(x.hi, y.hi, a.hi);
    return(r);
}


static float4
mix(float4 x, float4 y, float4 a)
{
float4 r;
	r.lo = mix(x.lo, y.lo, a.lo);
	r.hi = mix(x.hi, y.hi, a.hi);
    return(r);
}

//RADIANS
static double4
radians(double4 degrees)
{
double4 ret;
    ret.lo = radians(degrees.lo);
    ret.hi = radians(degrees.hi);
    return(ret);
}


static float4
radians(float4 degrees)
{
float4 ret;
    ret.lo = radians(degrees.lo);
    ret.hi = radians(degrees.hi);
    return(ret);
}

//STEP
static double4
step(double4 edge, double4 x)
{
double4 r;
    r.lo = step(edge.lo,x.lo);
    r.hi = step(edge.hi,x.hi);
    return(r);
}

static float4
step(float4 edge, float4 x)
{
float4 r;
    r.lo = step(edge.lo,x.lo);
    r.hi = step(edge.hi,x.hi);
    return(r);
}


// SMOOTHEDGE
static double4
smoothstep(double4 edge0, double4 edge1, double4 x)
{
double4 r;
	r.lo = mix(edge0.lo, edge1.lo, x.lo);
	r.hi = mix(edge0.hi, edge1.hi, x.hi);
    return(r);
}


static float4
smoothstep(float4 edge0, float4 edge1, float4 x)
{
float4 r;
	r.lo = mix(edge0.lo, edge1.lo, x.lo);
	r.hi = mix(edge0.hi, edge1.hi, x.hi);
    return(r);
}


// SIGN
int4
static sign(float4 src)
  {
    int4 ret;
       ret.x = sign(src.x);
       ret.y = sign(src.y);
	   return ret;
  }
int4
static sign(double4 src)
  {
    int4 ret;
       ret.x = sign(src.x);
       ret.y = sign(src.y);
	   return ret;
  }

/*---------------------------------------------------------------------------------------------------------------------
*
* geometry
*
---------------------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------------------
*
* cross
*
---------------------------------------------------------------------------------------------------------------------*/
static double4
cross(double4 p0, double4 p1)
{
double4 r = 0;
    r.x = (( p0.y * p1.z ) - ( p0.z * p1.y ));
    r.y = (( p0.z * p1.x ) - ( p0.x * p1.z ));
    r.z = (( p0.x * p1.y ) - ( p0.y * p1.x ));
	r.w = 0.0f;

    return ( r );
}
static float4
cross(float4 p0, float4 p1)
{
float4 r = convert_float4(cross(convert_double4(p0), convert_double4(p1)));
    return ( r );
}

/*---------------------------------------------------------------------------------------------------------------------
*
* dot
*
---------------------------------------------------------------------------------------------------------------------*/

static float dot(float4 _a, float4 _b)
{
float ret;
      ret = dot(_a.lo,_b.lo) + dot(_a.hi,_b.hi);
	  return(ret);
}

static double dot(double4 _a, double4 _b)
{
double ret;
      ret = dot(_a.lo,_b.lo) + dot(_a.hi,_b.hi);
	  return(ret);
}



/*---------------------------------------------------------------------------------------------------------------------
*
* distance
*
---------------------------------------------------------------------------------------------------------------------*/

static double distance(double4 x, double4 y)
{
double r = 0;
double4 t = x - y;
    r = dot(t,t);
	r = sqrt(r);
    return ( r );
}


static float distance(float4 x, float4 y)
{
float r = 0;
    r = (float)distance(convert_double4(x),convert_double4(y));
    return ( r );
}

/*---------------------------------------------------------------------------------------------------------------------
*
* fast_distance
*
---------------------------------------------------------------------------------------------------------------------*/

static float
fast_distance(float4 x, float4 y)
{
float r = distance(x,y);
    return ( r );
}

static double
fast_distance(double4 x, double4 y)
{
double r = distance(x,y);
    return ( r );
}


/*---------------------------------------------------------------------------------------------------------------------
*
* length
*
---------------------------------------------------------------------------------------------------------------------*/

static double
length(double4 p)
{
double r = 0;
    r = dot(p,p);
	r = sqrt(r);
    return ( r );
}

static float
length(float4 p)
{
float r = (float)length(convert_double4(p));
    return ( r );
}


/*---------------------------------------------------------------------------------------------------------------------
*
* fast_length
*
---------------------------------------------------------------------------------------------------------------------*/

static double
fast_length(double4 p)
{
double r = length(p);
    return ( r );
}


static float
fast_length(float4 p)
{
float r = length(p);
    return ( r );
}


/*---------------------------------------------------------------------------------------------------------------------
*
* normalize
*
---------------------------------------------------------------------------------------------------------------------*/

static double4
normalize(double4 p)
{
double4 r;
double t = dot(p,p);
    r = ( t==0) ? p : p/(double4)sqrt(t); 
    return ( r );
}


static float4
normalize(float4 p)
{
float4 r = convert_float4(normalize(convert_double4(p)));
    return ( r );
}



/*---------------------------------------------------------------------------------------------------------------------
*
* fast_normalize
*
---------------------------------------------------------------------------------------------------------------------*/

static float4
fast_normalize(float4 p)
{
float4 r = 0;
    r = normalize(p);
    return ( r );
}


static double4
fast_normalize(double4 p)
{
double4 r = 0;
    r = normalize(p);
    return ( r );
}





template <class _T>
	clemu_vector4<_T> select(clemu_vector4<_T> _a, clemu_vector4<_T> _b, clemu_vector4<char> _c)
	{
	 clemu_vector4<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}

template <class _T>
	clemu_vector4<_T> select(clemu_vector4<_T> _a, clemu_vector4<_T> _b, clemu_vector4<uchar> _c)
	{
	 clemu_vector4<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}
template <class _T>
	clemu_vector4<_T> select(clemu_vector4<_T> _a, clemu_vector4<_T> _b, clemu_vector4<short> _c)
	{
	 clemu_vector4<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}

template <class _T>
	clemu_vector4<_T> select(clemu_vector4<_T> _a, clemu_vector4<_T> _b, clemu_vector4<ushort> _c)
	{
	 clemu_vector4<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}

template <class _T>
	clemu_vector4<_T> select(clemu_vector4<_T> _a, clemu_vector4<_T> _b, clemu_vector4<int> _c)
	{
	 clemu_vector4<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}

template <class _T>
	clemu_vector4<_T> select(clemu_vector4<_T> _a, clemu_vector4<_T> _b, clemu_vector4<uint> _c)
	{
	 clemu_vector4<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}


static float4 select(float4 _a, float4 _b, clemu_vector4<char> _c)
	{
	 float4 tmp;
	     tmp.x = isMSBset(_c.x) ? _b.x : _a.x;
	     tmp.y = isMSBset(_c.y) ? _b.y : _a.y;
	     tmp.z = isMSBset(_c.z) ? _b.z : _a.z;
	     tmp.w = isMSBset(_c.w) ? _b.w : _a.w;
         return(tmp);
	}

static float4 select(float4 _a, float4 _b, clemu_vector4<uchar> _c)
	{
	 float4 tmp;
	     tmp.x = isMSBset(_c.x) ? _b.x : _a.x;
	     tmp.y = isMSBset(_c.y) ? _b.y : _a.y;
	     tmp.z = isMSBset(_c.z) ? _b.z : _a.z;
	     tmp.w = isMSBset(_c.w) ? _b.w : _a.w;
        return(tmp);
	}


static float4 select(float4 _a, float4 _b, clemu_vector4<short> _c)
	{
	 float4 tmp;
	     tmp.x = isMSBset(_c.x) ? _b.x : _a.x;
	     tmp.y = isMSBset(_c.y) ? _b.y : _a.y;
	     tmp.z = isMSBset(_c.z) ? _b.z : _a.z;
	     tmp.w = isMSBset(_c.w) ? _b.w : _a.w;
         return(tmp);
	}

static float4 select(float4 _a, float4 _b, clemu_vector4<ushort> _c)
	{
	 float4 tmp;
	     tmp.x = isMSBset(_c.x) ? _b.x : _a.x;
	     tmp.y = isMSBset(_c.y) ? _b.y : _a.y;
	     tmp.z = isMSBset(_c.z) ? _b.z : _a.z;
	     tmp.w = isMSBset(_c.w) ? _b.w : _a.w;
         return(tmp);
	}

static float4 select(float4 _a, float4 _b, clemu_vector4<int> _c)
	{
	 float4 tmp;
	     tmp.x = isMSBset(_c.x) ? _b.x : _a.x;
	     tmp.y = isMSBset(_c.y) ? _b.y : _a.y;
	     tmp.z = isMSBset(_c.z) ? _b.z : _a.z;
	     tmp.w = isMSBset(_c.w) ? _b.w : _a.w;
         return(tmp);
	}

static float4 select(float4 _a, float4 _b, clemu_vector4<uint> _c)
	{
	 float4 tmp;
	     tmp.x = isMSBset(_c.x) ? _b.x : _a.x;
	     tmp.y = isMSBset(_c.y) ? _b.y : _a.y;
	     tmp.z = isMSBset(_c.z) ? _b.z : _a.z;
	     tmp.w = isMSBset(_c.w) ? _b.w : _a.w;
         return(tmp);
	}


/*
8
*/


template <class _SRC>
  float8 convert_float8(clemu_vector8<_SRC> src)
  {
  float8 dst;
       dst.lo = convert_float4(src.lo);
       dst.hi = convert_float4(src.hi);
	   return dst;
  }

template <class _SRC>
  double8 convert_double8(clemu_vector8<_SRC> src)
  {
  double8 dst;
       dst.lo = convert_double4(src.lo);
       dst.hi = convert_double4(src.hi);
	   return dst;
  }



template <class _SRC>
  clemu_vector8<char> convert_char8(clemu_vector8<_SRC> src)
  {
    clemu_vector8<char> dst;
       dst.lo = convert_char4(src.lo);
       dst.hi = convert_char4(src.hi);
	   return dst;
  }
template <class _SRC>
  clemu_vector8<char> convert_uchar8(clemu_vector8<_SRC> src)
  {
    clemu_vector8<uchar> dst;
       dst.lo = convert_uchar4(src.lo);
       dst.hi = convert_uchar4(src.hi);
	   return dst;
  }

template <class _SRC>
  clemu_vector8<short> convert_short8(clemu_vector8<_SRC> src)
  {
    clemu_vector8<short> dst;
       dst.lo = convert_short4(src.lo);
       dst.hi = convert_short4(src.hi);
	   return dst;
  }
template <class _SRC>
  clemu_vector8<ushort> convert_ushort8(clemu_vector8<_SRC> src)
  {
    clemu_vector8<ushort> dst;
       dst.lo = convert_ushort4(src.lo);
       dst.hi = convert_ushort4(src.hi);
	   return dst;
  }
template <class _SRC>
  clemu_vector8<int> convert_int8(clemu_vector8<_SRC> src)
  {
    clemu_vector8<int> dst;
       dst.lo = convert_int4(src.lo);
       dst.hi = convert_int4(src.hi);
	   return dst;
  }
template <class _SRC>
  clemu_vector8<uint> convert_uint8(clemu_vector8<_SRC> src)
  {
    clemu_vector8<uint> dst;
       dst.lo = convert_uint4(src.lo);
       dst.hi = convert_uint4(src.hi);
	   return dst;
  }


template <class _SRC>
  uint8 as_uint8(clemu_vector8<_SRC> src)
  {
    uint8 dst;
       dst.lo = as_uint4(src.lo);
       dst.hi = as_uint4(src.hi);
	   return dst;

  }

template <class _SRC>
  int8 as_int8(clemu_vector8<_SRC> src)
  {
    int8 dst;
       dst.lo = as_int4(src.lo);
       dst.hi = as_int4(src.hi);
	   return dst;

  }

template <class _SRC>
  float8 as_float8(clemu_vector8<_SRC> src)
  {
    float8 dst;
       dst.lo = as_float4(src.lo);
       dst.hi = as_float4(src.hi);
	   return dst;

  }



/*
AMD_UNPACK
*/
static
float8 amd_unpack0 (uint8 src)
{
float8 ret;
    ret.lo = amd_unpack0(src.lo);
    ret.hi = amd_unpack0(src.hi);
    return(ret);
}
static
float8 amd_unpack1 (uint8 src)
{
float8 ret;
    ret.lo = amd_unpack1(src.lo);
    ret.hi = amd_unpack1(src.hi);
    return(ret);
}
static
float8 amd_unpack2 (uint8 src)
{
float8 ret;
    ret.lo = amd_unpack2(src.lo);
    ret.hi = amd_unpack2(src.hi);
    return(ret);
}
static
float8 amd_unpack3 (uint8 src)
{
float8 ret;
    ret.lo = amd_unpack3(src.lo);
    ret.hi = amd_unpack3(src.hi);
    return(ret);
}

/*
AMD_BITALIGN
*/
static
uint8 amd_bitalign (uint8 src0, uint8 src1, uint8 src2)
{
uint8 ret;
    ret.lo = amd_bitalign (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_bitalign (src0.hi, src1.hi, src2.hi);
    return(ret);
}
/*
AMD_BYTEALIGN
*/
static
uint8 amd_bytealign (uint8 src0, uint8 src1, uint8 src2)
{
uint8 ret;
    ret.lo = amd_bytealign (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_bytealign (src0.hi, src1.hi, src2.hi);
    return(ret);
}
/*
AMD_LERP
*/
static
uint8 amd_lerp (uint8 src0, uint8 src1, uint8 src2)
{
uint8 ret;
    ret.lo = amd_lerp (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_lerp (src0.hi, src1.hi, src2.hi);
    return(ret);
 }
/*
AMD_SAD
*/

static
uint8 amd_sad (uint8 src0, uint8 src1, uint8 src2)
{
uint8 ret;
    ret.lo = amd_sad (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_sad (src0.hi, src1.hi, src2.hi);
    return(ret);
}

static
uint8 amd_sadhi (uint8 src0, uint8 src1, uint8 src2)
{
uint8 ret;
    ret.lo = amd_sadhi (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_sadhi (src0.hi, src1.hi, src2.hi);
    return(ret);
}



/*------------------------------------------------------------------------------------
* 
* relational
*
* ----------------------------------------------------------------------------------*/

//Returns the component-wise compare of x == y.

static int8 isequal (float8 x, float8 y)
{
int8 r;
     r.lo = isequal (x.lo, y.lo);
     r.hi = isequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x != y.
static int8 isnotequal (float8 x, float8 y)
{
int8 r;
     r.lo = isnotequal (x.lo, y.lo);
     r.hi = isnotequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x > y.
static int8 isgreater (float8 x, float8 y)
{
int8 r;
     r.lo = isgreater (x.lo, y.lo);
     r.hi = isgreater (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x >= y.
static int8 isgreaterequal (float8 x, float8 y)
{
int8 r;
     r.lo = isgreaterequal (x.lo, y.lo);
     r.hi = isgreaterequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x < y.
static int8 isless (float8 x, float8 y)
{
int8 r;
     r.lo = isless (x.lo, y.lo);
     r.hi = isless (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x <= y.
static int8 islessequal (float8 x, float8 y)
{
int8 r;
     r.lo = islessequal (x.lo, y.lo);
     r.hi = islessequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of (x < y) || (x > y)
static int8 islessgreater (float8 x, float8 y)
{
int8 r;
     r.lo = islessgreater (x.lo, y.lo);
     r.hi = islessgreater (x.hi, y.hi);
     return(r);
}

static int8 isinf(float8 x)
{
int8 r;
     r.lo = isinf (x.lo);
     r.hi = isinf (x.hi);
     return(r);
}


static int8 isfinite(float8 x)
{
int8 r;
     r.lo = isfinite (x.lo);
     r.hi = isfinite (x.hi);
     return(r);
}
static int8 isnan(float8 x)
{
int8 r;
     r.lo = isnan (x.lo);
     r.hi = isnan (x.hi);
     return(r);
}
static int8 isnormal(float8 x)
{
int8 r;
     r.lo = isnormal (x.lo);
     r.hi = isnormal (x.hi);
     return(r);
}

//Test if arguments are ordered. isordered() takes
//arguments x and y, and returns the result
//isequal(x, x) && isequal(y, y).

static int8 isordered (float8 x, float8 y)
{
int8 r;
     r.lo = isordered (x.lo, y.lo);
     r.hi = isordered (x.hi, y.hi);
     return(r);
}

//Test if arguments are unordered. isunordered() takes
//arguments x and y, returning non-zero if x or y is NaN,
//and zero otherwise.
static int8 isunordered (float8 x, float8 y)
{
int8 r;
     r.lo = isunordered (x.lo, y.lo);
     r.hi = isunordered (x.hi, y.hi);
     return(r);
}

//Test for sign bit. The scalar version of the function
//returns a 1 if the sign bit in the float is set else returns 0.
//The vector version of the function returns the following
//for each component in floatn: a -1 if the sign bit in the
//float is set else returns 0.
static int8 signbit (float8 x)
{
int8 r;
     r.lo = signbit (x.lo);
     r.hi = signbit (x.hi);
     return(r);
}



//Returns the component-wise compare of x == y.

static __LONG8 isequal (double8 x, double8 y)
{
__LONG8 r;
     r.lo = isequal (x.lo, y.lo);
     r.hi = isequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x != y.
static __LONG8 isnotequal (double8 x, double8 y)
{
__LONG8 r;
     r.lo = isnotequal (x.lo, y.lo);
     r.hi = isnotequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x > y.
static __LONG8 isgreater (double8 x, double8 y)
{
__LONG8 r;
     r.lo = isgreater (x.lo, y.lo);
     r.hi = isgreater (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x >= y.
static __LONG8 isgreaterequal (double8 x, double8 y)
{
__LONG8 r;
     r.lo = isgreaterequal (x.lo, y.lo);
     r.hi = isgreaterequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x < y.
static __LONG8 isless (double8 x, double8 y)
{
__LONG8 r;
     r.lo = isless (x.lo, y.lo);
     r.hi = isless (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x <= y.
static __LONG8 islessequal (double8 x, double8 y)
{
__LONG8 r;
     r.lo = islessequal (x.lo, y.lo);
     r.hi = islessequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of (x < y) || (x > y)
static __LONG8 islessgreater (double8 x, double8 y)
{
__LONG8 r;
     r.lo = islessgreater (x.lo, y.lo);
     r.hi = islessgreater (x.hi, y.hi);
     return(r);
}

static __LONG8 isinf(double8 x)
{
__LONG8 r;
     r.lo = isinf (x.lo);
     r.hi = isinf (x.hi);
     return(r);
}


static __LONG8 isfinite(double8 x)
{
__LONG8 r;
     r.lo = isfinite (x.lo);
     r.hi = isfinite (x.hi);
     return(r);
}
static __LONG8 isnan(double8 x)
{
__LONG8 r;
     r.lo = isnan (x.lo);
     r.hi = isnan (x.hi);
     return(r);
}
static __LONG8 isnormal(double8 x)
{
__LONG8 r;
     r.lo = isnormal (x.lo);
     r.hi = isnormal (x.hi);
     return(r);
}

//Test if arguments are ordered. isordered() takes
//arguments x and y, and returns the result
//isequal(x, x) && isequal(y, y).

static __LONG8 isordered (double8 x, double8 y)
{
__LONG8 r;
     r.lo = isordered (x.lo, y.lo);
     r.hi = isordered (x.hi, y.hi);
     return(r);
}

//Test if arguments are unordered. isunordered() takes
//arguments x and y, returning non-zero if x or y is NaN,
//and zero otherwise.
static __LONG8 isunordered (double8 x, double8 y)
{
__LONG8 r;
     r.lo = isunordered (x.lo, y.lo);
     r.hi = isunordered (x.hi, y.hi);
     return(r);
}

//Test for sign bit. The scalar version of the function
//returns a 1 if the sign bit in the float is set else returns 0.
//The vector version of the function returns the following
//for each component in floatn: a -1 if the sign bit in the
//float is set else returns 0.
static __LONG8 signbit (double8 x)
{
__LONG8 r;
     r.lo = signbit (x.lo);
     r.hi = signbit (x.hi);
     return(r);
}



/*
ACOS
*/


static float8 acos( float8 _a)
{
float8 ret;
       ret.lo = acos(_a.lo);
       ret.hi = acos(_a.hi);
	   return ret;
}

static double8 acos( double8 _a)
{
double8 ret;
       ret.lo = acos(_a.lo);
       ret.hi = acos(_a.hi);
	   return ret;
}

// ACOSH

static float8 acosh( float8 _a)
{
float8 ret;
       ret.lo = acosh(_a.lo);
       ret.hi = acosh(_a.hi);
	   return ret;
}

static double8 acosh( double8 _a)
{
double8 ret;
       ret.lo = acosh(_a.lo);
       ret.hi = acosh(_a.hi);
	   return ret;
}

// ACOSPI

static float8 acospi( float8 _a)
{
float8 ret;
       ret.lo = acospi(_a.lo);
       ret.hi = acospi(_a.hi);
	   return ret;
}

static double8 acospi( double8 _a)
{
double8 ret;
       ret.lo = acospi(_a.lo);
       ret.hi = acospi(_a.hi);
	   return ret;
}


// ASIN

static float8 asin( float8 _a)
{
float8 ret;
       ret.lo = asin(_a.lo);
       ret.hi = asin(_a.hi);
	   return ret;
}

static double8 asin( double8 _a)
{
double8 ret;
       ret.lo = asin(_a.lo);
       ret.hi = asin(_a.hi);
	   return ret;
}


// ASINH

static float8 asinh( float8 _a)
{
float8 ret;
       ret.lo = asinh(_a.lo);
       ret.hi = asinh(_a.hi);
	   return ret;
}

static double8 asinh( double8 _a)
{
double8 ret;
       ret.lo = asinh(_a.lo);
       ret.hi = asinh(_a.hi);
	   return ret;
}

// ASINPI

static float8 asinpi( float8 _a)
{
float8 ret;
       ret.lo = asinpi(_a.lo);
       ret.hi = asinpi(_a.hi);
	   return ret;
}

static double8 asinpi( double8 _a)
{
double8 ret;
       ret.lo = asinpi(_a.lo);
       ret.hi = asinpi(_a.hi);
	   return ret;
}


// ATAN

static float8 atan( float8 _a)
{
float8 ret;
       ret.lo = atan(_a.lo);
       ret.hi = atan(_a.hi);
	   return ret;
}

static double8 atan( double8 _a)
{
double8 ret;
       ret.lo = atan(_a.lo);
       ret.hi = atan(_a.hi);
	   return ret;
}

// ATAN2

static float8 atan2( float8 _a, float8 _b)
{
float8 ret;
       ret.lo = atan2(_a.lo, _b.lo);
       ret.hi = atan2(_a.hi, _b.hi);
	   return ret;
}

static double8 atan2( double8 _a, double8 _b)
{
double8 ret;
       ret.lo = atan2(_a.lo, _b.lo);
       ret.hi = atan2(_a.hi, _b.hi);
	   return ret;
}

// ATANH

static float8 atanh( float8 _a)
{
float8 ret;
       ret.lo = atanh(_a.lo);
       ret.hi = atanh(_a.hi);
	   return ret;
}

static double8 atanh( double8 _a)
{
double8 ret;
       ret.lo = atanh(_a.lo);
       ret.hi = atanh(_a.hi);
	   return ret;
}

// ATANPI

static float8 atanpi( float8 _a)
{
float8 ret;
       ret.lo = atanpi(_a.lo);
       ret.hi = atanpi(_a.hi);
	   return ret;
}

static double8 atanpi( double8 _a)
{
double8 ret;
       ret.lo = atanpi(_a.lo);
       ret.hi = atanpi(_a.hi);
	   return ret;
}

// ATAN2

static float8 atan2pi( float8 _a, float8 _b)
{
float8 ret;
       ret.lo = atan2pi(_a.lo, _b.lo);
       ret.hi = atan2pi(_a.hi, _b.hi);
	   return ret;
}

static double8 atan2pi( double8 _a, double8 _b)
{
double8 ret;
       ret.lo = atan2pi(_a.lo, _b.lo);
       ret.hi = atan2pi(_a.hi, _b.hi);
	   return ret;
}

// CBRT
static float8 cbrt( float8 _a)
{
float8 ret;
       ret.lo = cbrt(_a.lo);
       ret.hi = cbrt(_a.hi);
	   return ret;
}

static double8 cbrt( double8 _a)
{
double8 ret;
       ret.lo = cbrt(_a.lo);
       ret.hi = cbrt(_a.hi);
	   return ret;
}



// CEIL
static float8 ceil( float8 _a)
{
float8 ret;
       ret.lo = ceil(_a.lo);
       ret.hi = ceil(_a.hi);
	   return ret;
}

static double8 ceil( double8 _a)
{
double8 ret;
       ret.lo = ceil(_a.lo);
       ret.hi = ceil(_a.hi);
	   return ret;
}




// ATAN2

static float8 copysign( float8 _a, float8 _b)
{
float8 ret;
       ret.lo = copysign(_a.lo, _b.lo);
       ret.hi = copysign(_a.hi, _b.hi);
	   return ret;
}

static double8 copysign( double8 _a, double8 _b)
{
double8 ret;
       ret.lo = copysign(_a.lo, _b.lo);
       ret.hi = copysign(_a.hi, _b.hi);
	   return ret;
}



// COS

static float8 cos( float8 _a)
{
float8 ret;
       ret.lo = cos(_a.lo);
       ret.hi = cos(_a.hi);
	   return ret;
}

static double8 cos( double8 _a)
{
double8 ret;
       ret.lo = cos(_a.lo);
       ret.hi = cos(_a.hi);
	   return ret;
}

// COSH

static float8 cosh( float8 _a)
{
float8 ret;
       ret.lo = cosh(_a.lo);
       ret.hi = cosh(_a.hi);
	   return ret;
}

static double8 cosh( double8 _a)
{
double8 ret;
       ret.lo = cosh(_a.lo);
       ret.hi = cosh(_a.hi);
	   return ret;
}

// COSPI

static float8 cospi( float8 _a)
{
float8 ret;
       ret.lo = cospi(_a.lo);
       ret.hi = cospi(_a.hi);
	   return ret;
}

static double8 cospi( double8 _a)
{
double8 ret;
       ret.lo = cospi(_a.lo);
       ret.hi = cospi(_a.hi);
	   return ret;
}

// ERFC

static float8 erfc( float8 _a)
{
float8 ret;
       ret.lo = erfc(_a.lo);
       ret.hi = erfc(_a.hi);
	   return ret;
}

static double8 erfc( double8 _a)
{
double8 ret;
       ret.lo = erfc(_a.lo);
       ret.hi = erfc(_a.hi);
	   return ret;
}


// ERF


static float8 erf( float8 _a)
{
float8 ret;
       ret.lo = erf(_a.lo);
       ret.hi = erf(_a.hi);
	   return ret;
}

static double8 erf( double8 _a)
{
double8 ret;
       ret.lo = erf(_a.lo);
       ret.hi = erf(_a.hi);
	   return ret;
}


// EXP
static float8 exp( float8 _a)
{
float8 ret;
       ret.lo = exp(_a.lo);
       ret.hi = exp(_a.hi);
	   return ret;
}

static double8 exp( double8 _a)
{
double8 ret;
       ret.lo = exp(_a.lo);
       ret.hi = exp(_a.hi);
	   return ret;
}

// EXP2

static float8 exp2( float8 _a)
{
float8 ret;
       ret.lo = exp2(_a.lo);
       ret.hi = exp2(_a.hi);
	   return ret;
}

static double8 exp2( double8 _a)
{
double8 ret;
       ret.lo = exp2(_a.lo);
       ret.hi = exp2(_a.hi);
	   return ret;
}

// EXP10

static float8 exp10( float8 _a)
{
float8 ret;
       ret.lo = exp10(_a.lo);
       ret.hi = exp10(_a.hi);
	   return ret;
}

static double8 exp10( double8 _a)
{
double8 ret;
       ret.lo = exp10(_a.lo);
       ret.hi = exp10(_a.hi);
	   return ret;
}

// EXPM1
static float8 expm1( float8 _a)
{
float8 ret;
       ret.lo = expm1(_a.lo);
       ret.hi = expm1(_a.hi);
	   return ret;
}

static double8 expm1( double8 _a)
{
double8 ret;
       ret.lo = expm1(_a.lo);
       ret.hi = expm1(_a.hi);
	   return ret;
}


// FABS
static float8 fabs( float8 _a)
{
float8 ret;
       ret.lo = fabs(_a.lo);
       ret.hi = fabs(_a.hi);
	   return ret;
}

static double8 fabs( double8 _a)
{
double8 ret;
       ret.lo = fabs(_a.lo);
       ret.hi = fabs(_a.hi);
	   return ret;
}

// FDIM
static double8 fdim( double8 _a, double8 _b)
{
double8 ret;
       ret.lo = fdim(_a.lo, _b.lo);
       ret.hi = fdim(_a.hi, _b.hi);
	   return ret;
}

static float8 fdim( float8 _a, float8 _b)
{
float8 ret;
       ret.lo = fdim(_a.lo, _b.lo);
       ret.hi = fdim(_a.hi, _b.hi);
	   return ret;
}



// FLOOR

static float8 floor( float8 _a)
{
float8 ret;
       ret.lo = floor(_a.lo);
       ret.hi = floor(_a.hi);
	   return ret;
}

static double8 floor( double8 _a)
{
double8 ret;
       ret.lo = floor(_a.lo);
       ret.hi = floor(_a.hi);
	   return ret;
}

// FMA

static float8 fma( float8 _a, float8 _b, float8 _c)
{
float8 ret;
       ret.lo = fma(_a.lo,_b.lo,_c.lo);
       ret.hi = fma(_a.hi,_b.hi,_c.hi);
	   return(ret);
}


static double8 fma( double8 _a, double8 _b, double8 _c)
{
double8 ret;
       ret.lo = fma(_a.lo,_b.lo,_c.lo);
       ret.hi = fma(_a.hi,_b.hi,_c.hi);
	   return(ret);
}


// FMAX

static float8 fmax( float8 _a, float8 _b)
{
float8 ret;
       ret.lo = fmax(_a.lo,_b.lo);
       ret.hi = fmax(_a.hi,_b.hi);
	   return(ret);
}


static double8 fmax( double8 _a, double8 _b)
{
double8 ret;
       ret.lo = fmax(_a.lo,_b.lo);
       ret.hi = fmax(_a.hi,_b.hi);
	   return(ret);
}

// FMIN

static float8 fmin( float8 _a, float8 _b)
{
float8 ret;
       ret.lo = fmin(_a.lo,_b.lo);
       ret.hi = fmin(_a.hi,_b.hi);
	   return(ret);
}


static double8 fmin( double8 _a, double8 _b)
{
double8 ret;
       ret.lo = fmin(_a.lo,_b.lo);
       ret.hi = fmin(_a.hi,_b.hi);
	   return(ret);
}


// FMOD
static float8 fmod( float8 _a, float8 _b)
{
float8 ret;
       ret.lo = fmod(_a.lo, _b.lo);
       ret.hi = fmod(_a.hi, _b.hi);
	   return ret;
}

static double8 fmod( double8 _a, double8 _b)
{
double8 ret;
       ret.lo = fmod(_a.lo, _b.lo);
       ret.hi = fmod(_a.hi, _b.hi);
	   return ret;
}







// FRAC

static float8 frac( float8 _a)
{
float8 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}

static double8 frac( double8 _a)
{
double8 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}


// FRACT

static float8 fract( float8 _a)
{
float8 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}

static double8 fract( double8 _a)
{
double8 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}

// FREXP

static float8 frexp( float8 _a, int8* _b)
{
float8 ret;
       ret.lo = frexp(_a.lo, &_b->lo);
       ret.hi = frexp(_a.hi, &_b->hi);
	   return ret;
}

static double8 frexp( double8 _a, int8* _b)
{
double8 ret;
       ret.lo = frexp(_a.lo, &_b->lo);
       ret.hi = frexp(_a.hi, &_b->hi);
	   return ret;
}

// HYPOT

static float8 hypot( float8 _a, float8 _b)
{
float8 ret;
       ret.lo = hypot(_a.lo, _b.lo);
       ret.hi = hypot(_a.hi, _b.hi);
	   return ret;
}

static double8 hypot( double8 _a, double8 _b)
{
double8 ret;
       ret.lo = hypot(_a.lo, _b.lo);
       ret.hi = hypot(_a.hi, _b.hi);
	   return ret;
}

// ILOGB

static int8 ilogb( float8 _a)
{
int8 ret;
       ret.lo = ilogb(_a.lo);
       ret.hi = ilogb(_a.hi);
	   return ret;
}

static int8 ilogb( double8 _a)
{
int8 ret;
       ret.lo = ilogb(_a.lo);
       ret.hi = ilogb(_a.hi);
	   return ret;
}

// LDEXP

static float8 ldexp( float8 _a, int8 _b)
{
float8 ret;
       ret.lo = ldexp(_a.lo, _b.lo);
       ret.hi = ldexp(_a.hi, _b.hi);
	   return ret;
}

static double8 ldexp( double8 _a, int8 _b)
{
double8 ret;
       ret.lo = ldexp(_a.lo, _b.lo);
       ret.hi = ldexp(_a.hi, _b.hi);
	   return ret;
}

static float8 ldexp( float8 _a, int _b)
{
float8 ret;
       ret = ldexp(_a, (int8)_b);
	   return ret;
}

static double8 ldexp( double8 _a, int _b)
{
double8 ret;
       ret = ldexp(_a, (int8)_b);
	   return ret;
}

// LGAMMA
static float8 lgamma( float8 _a)
{
float8 ret;
       ret.lo = lgamma(_a.lo);
       ret.hi = lgamma(_a.hi);
	   return ret;
}

static double8 lgamma( double8 _a)
{
double8 ret;
       ret.lo = lgamma(_a.lo);
       ret.hi = lgamma(_a.hi);
	   return ret;
}

// LGAMMA_R

static float8 lgamma_r( float8 _a, int8 *psign)
{
float8 ret;
       ret.lo = lgamma_r(_a.lo, &psign->lo);
       ret.hi = lgamma_r(_a.hi, &psign->hi);
	   return ret;
}

static double8 lgamma_r( double8 _a, int8 *psign)
{
double8 ret;
       ret.lo = lgamma_r(_a.lo, &psign->lo);
       ret.hi = lgamma_r(_a.hi, &psign->hi);
	   return ret;
}


// LOG

static float8 log( float8 _a)
{
float8 ret;
       ret.lo = log(_a.lo);
       ret.hi = log(_a.hi);
	   return ret;
}

static double8 log( double8 _a)
{
double8 ret;
       ret.lo = log(_a.lo);
       ret.hi = log(_a.hi);
	   return ret;
}

// LOG2

static float8 log2( float8 _a)
{
float8 ret;
       ret.lo = log2(_a.lo);
       ret.hi = log2(_a.hi);
	   return ret;
}

static double8 log2( double8 _a)
{
double8 ret;
       ret.lo = log2(_a.lo);
       ret.hi = log2(_a.hi);
	   return ret;
}


// LOG10

static float8 log10( float8 _a)
{
float8 ret;
       ret.lo = log10(_a.lo);
       ret.hi = log10(_a.hi);
	   return ret;
}

static double8 log10( double8 _a)
{
double8 ret;
       ret.lo = log10(_a.lo);
       ret.hi = log10(_a.hi);
	   return ret;
}

// LOG1P

static float8 log1p( float8 _a)
{
float8 ret;
       ret.lo = log1p(_a.lo);
       ret.hi = log1p(_a.hi);
	   return ret;
}

static double8 log1p( double8 _a)
{
double8 ret;
       ret.lo = log1p(_a.lo);
       ret.hi = log1p(_a.hi);
	   return ret;
}


// LOGB

static float8 logb( float8 _a)
{
float8 ret;
       ret.lo = logb(_a.lo);
       ret.hi = logb(_a.hi);
	   return ret;
}

static double8 logb( double8 _a)
{
double8 ret;
       ret.lo = logb(_a.lo);
       ret.hi = logb(_a.hi);
	   return ret;
}


// mad

static float8 mad( float8 _a, float8 _b, float8 _c)
{
float8 ret;
       ret.lo = mad(_a.lo, _b.lo, _c.lo);
       ret.hi = mad(_a.hi, _b.hi, _c.hi);
	   return ret;
}

static double8 mad( double8 _a, double8 _b, double8 _c)
{
double8 ret;
       ret.lo = mad(_a.lo, _b.lo, _c.lo);
       ret.hi = mad(_a.hi, _b.hi, _c.hi);
	   return ret;
}


// mogf

static float8 modf( float8 _a, int8* _b)
{
float8 ret;
       ret.lo = modf(_a.lo, &_b->lo);
       ret.hi = modf(_a.hi, &_b->hi);
	   return ret;
}

static double8 modf( double8 _a, int8* _b)
{
double8 ret;
       ret.lo = modf(_a.lo, &_b->lo);
       ret.hi = modf(_a.hi, &_b->hi);
	   return ret;
}

//NAN
static float8 nan( int8 _b)
{
float8 ret;
       ret.lo = nan(_b.lo);
       ret.hi = nan(_b.hi);
	   return ret;
}
static double8 nan( __LONG8 _b)
{
double8 ret;
       ret.lo = nan(_b.lo);
       ret.hi = nan(_b.hi);
	   return ret;
}

// NEXTAFTER
static float8 nextafter( float8 _a, float8 _b)
{
float8 ret;
       ret.lo = nextafter(_a.lo, _b.lo);
       ret.hi = nextafter(_a.hi, _b.hi);
	   return ret;
}
static double8 nextafter( double8 _a, double8 _b)
{
double8 ret;
       ret.lo = nextafter(_a.lo, _b.lo);
       ret.hi = nextafter(_a.hi, _b.hi);
	   return ret;
}


// POW
static float8 pow( float8 _a, float8 _b)
{
float8 ret;
       ret.lo = pow(_a.lo, _b.lo);
       ret.hi = pow(_a.hi, _b.hi);
	   return ret;
}

static double8 pow( double8 _a, double8 _b)
{
double8 ret;
       ret.lo = pow(_a.lo, _b.lo);
       ret.hi = pow(_a.hi, _b.hi);
	   return ret;
}

// POWN
static double8 pown( double8 _a, int8 _b)
{
double8 ret;
       ret.lo = pown(_a.lo, _b.lo);
       ret.hi = pown(_a.hi, _b.hi);
	   return ret;
}

static float8 pown( float8 _a, int8 _b)
{
float8 ret;
       ret.lo = pown(_a.lo, _b.lo);
       ret.hi = pown(_a.hi, _b.hi);
	   return ret;
}

// POWR
static double8 powr( double8 _a, double8 _b)
{
double8 ret;
       ret.lo = powr(_a.lo, _b.lo);
       ret.hi = powr(_a.hi, _b.hi);
	   return ret;
}

static float8 powr( float8 _a, float8 _b)
{
float8 ret;
       ret.lo = powr(_a.lo, _b.lo);
       ret.hi = powr(_a.hi, _b.hi);
	   return ret;
}

// REMAINDER
static
float8 remainder(float8 x, float8 p)
{
float8 ret;
        ret.lo = remainder(x.lo, p.lo);
        ret.hi = remainder(x.hi, p.hi);
		return(ret);
}

static
double8 remainder(double8 x, double8 p)
{
double8 ret;
        ret.lo = remainder(x.lo, p.lo);
        ret.hi = remainder(x.hi, p.hi);
		return(ret);
}


// REMQUO
static
float8 remquo(float8 x, float8 p, int8 *pquo)
{
float8 ret;
        ret.lo = remquo(x.lo, p.lo, &pquo->lo);
        ret.hi = remquo(x.hi, p.hi, &pquo->hi);
		return(ret);
}

static
double8 remquo(double8 x, double8 p, int8 *pquo)
{
double8 ret;
        ret.lo = remquo(x.lo, p.lo, &pquo->lo);
        ret.hi = remquo(x.hi, p.hi, &pquo->hi);
		return(ret);
}


// RINT

static float8
rint (float8 x)
{
float8 ret;
       ret.lo = rint(x.lo);
       ret.hi = rint(x.hi);
	   return(ret);
}

static double8
rint (double8 x)
{
double8 ret;
       ret.lo = rint(x.lo);
       ret.hi = rint(x.hi);
	   return(ret);
}

// ROOTN
static float8 rootn( float8 _a, int8 _n)
{
float8 ret;
       ret.lo = rootn(_a.lo, _n.lo);
       ret.hi = rootn(_a.hi, _n.hi);
	   return ret;
}

static double8 rootn( double8 _a, int8 _n)
{
double8 ret;
       ret.lo = rootn(_a.lo, _n.lo);
       ret.hi = rootn(_a.hi, _n.hi);
	   return ret;
}

//ROUND

static float8 round( float8 _a)
{
float8 ret;
       ret.lo = round(_a.lo);
       ret.hi = round(_a.hi);
	   return ret;
}

static double8 round( double8 _a)
{
double8 ret;
       ret.lo = round(_a.lo);
       ret.hi = round(_a.hi);
	   return ret;
}


//RSQRT

static float8 rsqrt( float8 _a)
{
float8 ret;
       ret.lo = rsqrt(_a.lo);
       ret.hi = rsqrt(_a.hi);
	   return ret;
}

static double8 rsqrt( double8 _a)
{
double8 ret;
       ret.lo = rsqrt(_a.lo);
       ret.hi = rsqrt(_a.hi);
	   return ret;
}

//SIN

static float8 sin( float8 _a)
{
float8 ret;
       ret.lo = sin(_a.lo);
       ret.hi = sin(_a.hi);
	   return ret;
}

static double8 sin( double8 _a)
{
double8 ret;
       ret.lo = sin(_a.lo);
       ret.hi = sin(_a.hi);
	   return ret;
}

//SINCOS

static float8 sincos( float8 _a, float8*_b)
{
float8 ret;
       ret.lo = sincos(_a.lo, &_b->lo);
       ret.hi = sincos(_a.hi, &_b->hi);
	   return ret;
}

static double8 sincos( double8 _a, double8*_b)
{
double8 ret;
       ret.lo = sincos(_a.lo, &_b->lo);
       ret.hi = sincos(_a.hi, &_b->hi);
	   return ret;
}

//SINH

static float8 sinh( float8 _a)
{
float8 ret;
       ret.lo = sinh(_a.lo);
       ret.hi = sinh(_a.hi);
	   return ret;
}

static double8 sinh( double8 _a)
{
double8 ret;
       ret.lo = sinh(_a.lo);
       ret.hi = sinh(_a.hi);
	   return ret;
}


//SINPI

static float8 sinpi( float8 _a)
{
float8 ret;
       ret.lo = sinpi(_a.lo);
       ret.hi = sinpi(_a.hi);
	   return ret;
}

static double8 sinpi( double8 _a)
{
double8 ret;
       ret.lo = sinpi(_a.lo);
       ret.hi = sinpi(_a.hi);
	   return ret;
}


//SQRT

static float8 sqrt( float8 _a)
{
float8 ret;
       ret.lo = sqrt(_a.lo);
       ret.hi = sqrt(_a.hi);
	   return ret;
}

static double8 sqrt( double8 _a)
{
double8 ret;
       ret.lo = sqrt(_a.lo);
       ret.hi = sqrt(_a.hi);
	   return ret;
}

//TAN

static float8 tan( float8 _a)
{
float8 ret;
       ret.lo = tan(_a.lo);
       ret.hi = tan(_a.hi);
	   return ret;
}

static double8 tan( double8 _a)
{
double8 ret;
       ret.lo = tan(_a.lo);
       ret.hi = tan(_a.hi);
	   return ret;
}

//TANH

static float8 tanh( float8 _a)
{
float8 ret;
       ret.lo = tanh(_a.lo);
       ret.hi = tanh(_a.hi);
	   return ret;
}

static double8 tanh( double8 _a)
{
double8 ret;
       ret.lo = tanh(_a.lo);
       ret.hi = tanh(_a.hi);
	   return ret;
}

//TANPI

static float8 tanpi( float8 _a)
{
float8 ret;
       ret.lo = tanpi(_a.lo);
       ret.hi = tanpi(_a.hi);
	   return ret;
}

static double8 tanpi( double8 _a)
{
double8 ret;
       ret.lo = tanpi(_a.lo);
       ret.hi = tanpi(_a.hi);
	   return ret;
}


// TGAMMA
static float8 tgamma( float8 _a)
{
float8 ret;
       ret.lo = tgamma(_a.lo);
       ret.hi = tgamma(_a.hi);
	   return ret;
}
static double8 tgamma( double8 _a)
{
double8 ret;
       ret.lo = tgamma(_a.lo);
       ret.hi = tgamma(_a.hi);
	   return ret;
}

// TRUNC

static float8 trunc( float8 _a)
{
float8 ret;
       ret.lo = trunc(_a.lo);
       ret.hi = trunc(_a.hi);
	   return ret;
}

static double8 trunc( double8 _a)
{
double8 ret;
       ret.lo = trunc(_a.lo);
       ret.hi = trunc(_a.hi);
	   return ret;
}

static float8 native_cos( float8 _a)
{
float8 ret;
       ret.lo = native_cos(_a.lo);
       ret.hi = native_cos(_a.hi);
	   return ret;
}

static double8 native_cos( double8 _a)
{
double8 ret;
       ret.lo = native_cos(_a.lo);
       ret.hi = native_cos(_a.hi);
	   return ret;
}


static double8 native_divide( double8 _a, double8 _b)
{
double8 ret;
       ret.lo = native_divide(_a.lo, _b.lo);
       ret.hi = native_divide(_a.hi, _b.hi);
	   return ret;
}

static float8 native_divide( float8 _a, float8 _b)
{
float8 ret;
       ret.lo = native_divide(_a.lo, _b.lo);
       ret.hi = native_divide(_a.hi, _b.hi);
	   return ret;
}

static float8 native_exp( float8 _a)
{
float8 ret;
       ret.lo = native_exp(_a.lo);
       ret.hi = native_exp(_a.hi);
	   return ret;
}

static double8 native_exp( double8 _a)
{
double8 ret;
       ret.lo = native_exp(_a.lo);
       ret.hi = native_exp(_a.hi);
	   return ret;
}

static float8 native_exp2( float8 _a)
{
float8 ret;
       ret.lo = native_exp2(_a.lo);
       ret.hi = native_exp2(_a.hi);
	   return ret;
}

static double8 native_exp2( double8 _a)
{
double8 ret;
       ret.lo = native_exp2(_a.lo);
       ret.hi = native_exp2(_a.hi);
	   return ret;
}

static float8 native_exp10( float8 _a)
{
float8 ret;
       ret.lo = native_exp10(_a.lo);
       ret.hi = native_exp10(_a.hi);
	   return ret;
}

static double8 native_exp10( double8 _a)
{
double8 ret;
       ret.lo = native_exp10(_a.lo);
       ret.hi = native_exp10(_a.hi);
	   return ret;
}

static float8 native_log( float8 _a)
{
float8 ret;
       ret.lo = native_log(_a.lo);
       ret.hi = native_log(_a.hi);
	   return ret;
}

static double8 native_log( double8 _a)
{
double8 ret;
       ret.lo = native_log(_a.lo);
       ret.hi = native_log(_a.hi);
	   return ret;
}

static float8 native_log2( float8 _a)
{
float8 ret;
       ret.lo = native_log2(_a.lo);
       ret.hi = native_log2(_a.hi);
	   return ret;
}

static double8 native_log2( double8 _a)
{
double8 ret;
       ret.lo = native_log2(_a.lo);
       ret.hi = native_log2(_a.hi);
	   return ret;
}

static float8 native_log10( float8 _a)
{
float8 ret;
       ret.lo = native_log10(_a.lo);
       ret.hi = native_log10(_a.hi);
	   return ret;
}

static double8 native_log10( double8 _a)
{
double8 ret;
       ret.lo = native_log10(_a.lo);
       ret.hi = native_log10(_a.hi);
	   return ret;
}

static float8 native_powr( float8 _a, float8 _b)
{
float8 ret;
       ret.lo = native_powr(_a.lo, _b.lo);
       ret.hi = native_powr(_a.hi, _b.hi);
	   return ret;
}

static double8 native_powr( double8 _a, double8 _b)
{
double8 ret;
       ret.lo = native_powr(_a.lo, _b.lo);
       ret.hi = native_powr(_a.hi, _b.hi);
	   return ret;
}

static float8 native_recip( float8 _a)
{
float8 ret;
       ret.lo = native_recip(_a.lo);
       ret.hi = native_recip(_a.hi);
	   return ret;
}

static double8 native_recip( double8 _a)
{
double8 ret;
       ret.lo = native_recip(_a.lo);
       ret.hi = native_recip(_a.hi);
	   return ret;
}

static float8 native_rsqrt( float8 _a)
{
float8 ret;
       ret.lo = native_rsqrt(_a.lo);
       ret.hi = native_rsqrt(_a.hi);
	   return ret;
}

static double8 native_rsqrt( double8 _a)
{
double8 ret;
       ret.lo = native_rsqrt(_a.lo);
       ret.hi = native_rsqrt(_a.hi);
	   return ret;
}

static float8 native_sin( float8 _a)
{
float8 ret;
       ret.lo = native_sin(_a.lo);
       ret.hi = native_sin(_a.hi);
	   return ret;
}

static double8 native_sin( double8 _a)
{
double8 ret;
       ret.lo = native_sin(_a.lo);
       ret.hi = native_sin(_a.hi);
	   return ret;
}

static float8 native_sqrt( float8 _a)
{
float8 ret;
       ret.lo = native_sqrt(_a.lo);
       ret.hi = native_sqrt(_a.hi);
	   return ret;
}

static double8 native_sqrt( double8 _a)
{
double8 ret;
       ret.lo = native_sqrt(_a.lo);
       ret.hi = native_sqrt(_a.hi);
	   return ret;
}

static float8 native_tan( float8 _a)
{
float8 ret;
       ret.lo = native_tan(_a.lo);
       ret.hi = native_tan(_a.hi);
	   return ret;
}

static double8 native_tan( double8 _a)
{
double8 ret;
       ret.lo = native_tan(_a.lo);
       ret.hi = native_tan(_a.hi);
	   return ret;
}


// CLAMP
static float8 clamp( float8 _a, float8 _min, float8 _max)
{
float8 ret;
       ret.lo = clamp(_a.lo, _min.lo, _max.lo);
       ret.hi = clamp(_a.hi, _min.hi, _max.hi);
	   return ret;
}

static double8 clamp( double8 _a, double8 _min, double8 _max)
{
double8 ret;
       ret.lo = clamp(_a.lo, _min.lo, _max.lo);
       ret.hi = clamp(_a.hi, _min.hi, _max.hi);
	   return ret;
}

// DEGREES
static double8
degrees(double8 radians)
{
double8 ret;
    ret.lo = degrees(radians.lo);
    ret.hi = degrees(radians.hi);
    return(ret);
}

static float8
degrees(float8 radians)
{
float8 ret;
    ret.lo = degrees(radians.lo);
    ret.hi = degrees(radians.hi);
    return(ret);
}


//MAX
float8
static max(float8 x, float8 y)
{
float8 r;
    r.lo = max(x.lo, y.lo);
    r.hi = max(x.hi, y.hi);
    return(r);
}

double8
static max(double8 x, double8 y)
{
double8 r;
    r.lo = max(x.lo, y.lo);
    r.hi = max(x.hi, y.hi);
    return(r);
}

//MIN
float8
static min(float8 x, float8 y)
{
float8 r;
    r.lo = min(x.lo, y.lo);
    r.hi = min(x.hi, y.hi);
    return(r);
}

double8
static min(double8 x, double8 y)
{
double8 r;
    r.lo = min(x.lo, y.lo);
    r.hi = min(x.hi, y.hi);
    return(r);
}

// MIX
static double8
mix(double8 x, double8 y, double8 a)
{
double8 r;
	r.lo = mix(x.lo, y.lo, a.lo);
	r.hi = mix(x.hi, y.hi, a.hi);
    return(r);
}


static float8
mix(float8 x, float8 y, float8 a)
{
float8 r;
	r.lo = mix(x.lo, y.lo, a.lo);
	r.hi = mix(x.hi, y.hi, a.hi);
    return(r);
}

//RADIANS
static double8
radians(double8 degrees)
{
double8 ret;
    ret.lo = radians(degrees.lo);
    ret.hi = radians(degrees.hi);
    return(ret);
}


static float8
radians(float8 degrees)
{
float8 ret;
    ret.lo = radians(degrees.lo);
    ret.hi = radians(degrees.hi);
    return(ret);
}

//STEP
static double8
step(double8 edge, double8 x)
{
double8 r;
    r.lo = step(edge.lo,x.lo);
    r.hi = step(edge.hi,x.hi);
    return(r);
}

static float8
step(float8 edge, float8 x)
{
float8 r;
    r.lo = step(edge.lo,x.lo);
    r.hi = step(edge.hi,x.hi);
    return(r);
}


// SMOOTHEDGE
static double8
smoothstep(double8 edge0, double8 edge1, double8 x)
{
double8 r;
	r.lo = mix(edge0.lo, edge1.lo, x.lo);
	r.hi = mix(edge0.hi, edge1.hi, x.hi);
    return(r);
}


static float8
smoothstep(float8 edge0, float8 edge1, float8 x)
{
float8 r;
	r.lo = mix(edge0.lo, edge1.lo, x.lo);
	r.hi = mix(edge0.hi, edge1.hi, x.hi);
    return(r);
}


// SIGN
int8
static sign(float8 src)
  {
    int8 ret;
       ret.lo = sign(src.lo);
       ret.hi = sign(src.hi);
	   return ret;
  }
int8
static sign(double8 src)
  {
    int8 ret;
       ret.lo = sign(src.lo);
       ret.hi = sign(src.hi);
	   return ret;
  }





template <class _T>
	clemu_vector8<_T> select(clemu_vector8<_T> _a, clemu_vector8<_T> _b, clemu_vector8<char> _c)
	{
	 clemu_vector8<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}

template <class _T>
	clemu_vector8<_T> select(clemu_vector8<_T> _a, clemu_vector8<_T> _b, clemu_vector8<uchar> _c)
	{
	 clemu_vector8<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}
template <class _T>
	clemu_vector8<_T> select(clemu_vector8<_T> _a, clemu_vector8<_T> _b, clemu_vector8<short> _c)
	{
	 clemu_vector8<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}

template <class _T>
	clemu_vector8<_T> select(clemu_vector8<_T> _a, clemu_vector8<_T> _b, clemu_vector8<ushort> _c)
	{
	 clemu_vector8<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}

template <class _T>
	clemu_vector8<_T> select(clemu_vector8<_T> _a, clemu_vector8<_T> _b, clemu_vector8<int> _c)
	{
	 clemu_vector8<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}

template <class _T>
	clemu_vector8<_T> select(clemu_vector8<_T> _a, clemu_vector8<_T> _b, clemu_vector8<uint> _c)
	{
	 clemu_vector8<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}


/*
16
*/

template <class _SRC>
  float16 convert_float16(clemu_vector16<_SRC> src)
  {
  float16 dst;
       dst.lo = convert_float8(src.lo);
       dst.hi = convert_float8(src.hi);
	   return dst;
  }


template <class _SRC>
  double16 convert_double16(clemu_vector16<_SRC> src)
  {
  double16 dst;
       dst.lo = convert_double8(src.lo);
       dst.hi = convert_double8(src.hi);
	   return dst;
  }



template <class _SRC>
  clemu_vector16<char> convert_char16(clemu_vector16<_SRC> src)
  {
    clemu_vector16<char> dst;
       dst.lo = convert_char8(src.lo);
       dst.hi = convert_char8(src.hi);
	   return dst;
  }
template <class _SRC>
  clemu_vector16<char> convert_uchar16(clemu_vector16<_SRC> src)
  {
    clemu_vector16<uchar> dst;
       dst.lo = convert_uchar8(src.lo);
       dst.hi = convert_uchar8(src.hi);
	   return dst;
  }

template <class _SRC>
  clemu_vector16<short> convert_short16(clemu_vector16<_SRC> src)
  {
    clemu_vector16<short> dst;
       dst.lo = convert_short8(src.lo);
       dst.hi = convert_short8(src.hi);
	   return dst;
  }
template <class _SRC>
  clemu_vector16<ushort> convert_ushort16(clemu_vector16<_SRC> src)
  {
    clemu_vector16<ushort> dst;
       dst.lo = convert_ushort8(src.lo);
       dst.hi = convert_ushort8(src.hi);
	   return dst;
  }
template <class _SRC>
  clemu_vector16<int> convert_int16(clemu_vector16<_SRC> src)
  {
    clemu_vector16<int> dst;
       dst.lo = convert_int8(src.lo);
       dst.hi = convert_int8(src.hi);
	   return dst;
  }
template <class _SRC>
  clemu_vector16<uint> convert_uint16(clemu_vector16<_SRC> src)
  {
    clemu_vector16<uint> dst;
       dst.lo = convert_uint8(src.lo);
       dst.hi = convert_uint8(src.hi);
	   return dst;
  }

template <class _SRC>
  uint16 as_uint16(clemu_vector16<_SRC> src)
  {
    uint16 dst;
       dst.lo = as_uint8(src.lo);
       dst.hi = as_uint8(src.hi);
	   return dst;

  }

template <class _SRC>
  int16 as_int4(clemu_vector16<_SRC> src)
  {
    int16 dst;
       dst.lo = as_int8(src.lo);
       dst.hi = as_int8(src.hi);
	   return dst;

  }

template <class _SRC>
  float16 as_float16(clemu_vector16<_SRC> src)
  {
    float16 dst;
       dst.lo = as_float8(src.lo);
       dst.hi = as_float8(src.hi);
	   return dst;

  }


template <class _T>
	clemu_vector16<_T> select(clemu_vector16<_T> _a, clemu_vector16<_T> _b, clemu_vector16<char> _c)
	{
	 clemu_vector16<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}

template <class _T>
	clemu_vector16<_T> select(clemu_vector16<_T> _a, clemu_vector16<_T> _b, clemu_vector16<uchar> _c)
	{
	 clemu_vector16<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}
template <class _T>
	clemu_vector16<_T> select(clemu_vector16<_T> _a, clemu_vector16<_T> _b, clemu_vector16<short> _c)
	{
	 clemu_vector16<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}

template <class _T>
	clemu_vector16<_T> select(clemu_vector16<_T> _a, clemu_vector16<_T> _b, clemu_vector16<ushort> _c)
	{
	 clemu_vector16<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}

template <class _T>
	clemu_vector16<_T> select(clemu_vector16<_T> _a, clemu_vector16<_T> _b, clemu_vector16<int> _c)
	{
	 clemu_vector16<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}

template <class _T>
	clemu_vector16<_T> select(clemu_vector16<_T> _a, clemu_vector16<_T> _b, clemu_vector16<uint> _c)
	{
	 clemu_vector16<_T> tmp;
	     tmp.lo = select(_a.lo,_b.lo,_c.lo);
	     tmp.hi = select(_a.hi,_b.hi,_c.hi);
         return(tmp);
	}






/*
AMD_UNPACK
*/
static
float16 amd_unpack0 (uint16 src)
{
float16 ret;
    ret.lo = amd_unpack0(src.lo);
    ret.hi = amd_unpack0(src.hi);
    return(ret);
}
static
float16 amd_unpack1 (uint16 src)
{
float16 ret;
    ret.lo = amd_unpack1(src.lo);
    ret.hi = amd_unpack1(src.hi);
    return(ret);
}
static
float16 amd_unpack2 (uint16 src)
{
float16 ret;
    ret.lo = amd_unpack2(src.lo);
    ret.hi = amd_unpack2(src.hi);
    return(ret);
}
static
float16 amd_unpack3 (uint16 src)
{
float16 ret;
    ret.lo = amd_unpack3(src.lo);
    ret.hi = amd_unpack3(src.hi);
    return(ret);
}

/*
AMD_BITALIGN
*/
static
uint16 amd_bitalign (uint16 src0, uint16 src1, uint16 src2)
{
uint16 ret;
    ret.lo = amd_bitalign (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_bitalign (src0.hi, src1.hi, src2.hi);
    return(ret);
}
/*
AMD_BYTEALIGN
*/
static
uint16 amd_bytealign (uint16 src0, uint16 src1, uint16 src2)
{
uint16 ret;
    ret.lo = amd_bytealign (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_bytealign (src0.hi, src1.hi, src2.hi);
    return(ret);
}
/*
AMD_LERP
*/
static
uint16 amd_lerp (uint16 src0, uint16 src1, uint16 src2)
{
uint16 ret;
    ret.lo = amd_lerp (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_lerp (src0.hi, src1.hi, src2.hi);
    return(ret);
 }
/*
AMD_SAD
*/

static
uint16 amd_sad (uint16 src0, uint16 src1, uint16 src2)
{
uint16 ret;
    ret.lo = amd_sad (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_sad (src0.hi, src1.hi, src2.hi);
    return(ret);
}
static
uint16 amd_sadhi (uint16 src0, uint16 src1, uint16 src2)
{
uint16 ret;
    ret.lo = amd_sadhi (src0.lo, src1.lo, src2.lo);
    ret.hi = amd_sadhi (src0.hi, src1.hi, src2.hi);
    return(ret);
}



/*------------------------------------------------------------------------------------
* 
* relational
*
* ----------------------------------------------------------------------------------*/

//Returns the component-wise compare of x == y.

static int16 isequal (float16 x, float16 y)
{
int16 r;
     r.lo = isequal (x.lo, y.lo);
     r.hi = isequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x != y.
static int16 isnotequal (float16 x, float16 y)
{
int16 r;
     r.lo = isnotequal (x.lo, y.lo);
     r.hi = isnotequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x > y.
static int16 isgreater (float16 x, float16 y)
{
int16 r;
     r.lo = isgreater (x.lo, y.lo);
     r.hi = isgreater (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x >= y.
static int16 isgreaterequal (float16 x, float16 y)
{
int16 r;
     r.lo = isgreaterequal (x.lo, y.lo);
     r.hi = isgreaterequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x < y.
static int16 isless (float16 x, float16 y)
{
int16 r;
     r.lo = isless (x.lo, y.lo);
     r.hi = isless (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x <= y.
static int16 islessequal (float16 x, float16 y)
{
int16 r;
     r.lo = islessequal (x.lo, y.lo);
     r.hi = islessequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of (x < y) || (x > y)
static int16 islessgreater (float16 x, float16 y)
{
int16 r;
     r.lo = islessgreater (x.lo, y.lo);
     r.hi = islessgreater (x.hi, y.hi);
     return(r);
}

static int16 isinf(float16 x)
{
int16 r;
     r.lo = isinf (x.lo);
     r.hi = isinf (x.hi);
     return(r);
}


static int16 isfinite(float16 x)
{
int16 r;
     r.lo = isfinite (x.lo);
     r.hi = isfinite (x.hi);
     return(r);
}
static int16 isnan(float16 x)
{
int16 r;
     r.lo = isnan (x.lo);
     r.hi = isnan (x.hi);
     return(r);
}
static int16 isnormal(float16 x)
{
int16 r;
     r.lo = isnormal (x.lo);
     r.hi = isnormal (x.hi);
     return(r);
}

//Test if arguments are ordered. isordered() takes
//arguments x and y, and returns the result
//isequal(x, x) && isequal(y, y).

static int16 isordered (float16 x, float16 y)
{
int16 r;
     r.lo = isordered (x.lo, y.lo);
     r.hi = isordered (x.hi, y.hi);
     return(r);
}

//Test if arguments are unordered. isunordered() takes
//arguments x and y, returning non-zero if x or y is NaN,
//and zero otherwise.
static int16 isunordered (float16 x, float16 y)
{
int16 r;
     r.lo = isunordered (x.lo, y.lo);
     r.hi = isunordered (x.hi, y.hi);
     return(r);
}

//Test for sign bit. The scalar version of the function
//returns a 1 if the sign bit in the float is set else returns 0.
//The vector version of the function returns the following
//for each component in floatn: a -1 if the sign bit in the
//float is set else returns 0.
static int16 signbit (float16 x)
{
int16 r;
     r.lo = signbit (x.lo);
     r.hi = signbit (x.hi);
     return(r);
}



//Returns the component-wise compare of x == y.

static __LONG16 isequal (double16 x, double16 y)
{
__LONG16 r;
     r.lo = isequal (x.lo, y.lo);
     r.hi = isequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x != y.
static __LONG16 isnotequal (double16 x, double16 y)
{
__LONG16 r;
     r.lo = isnotequal (x.lo, y.lo);
     r.hi = isnotequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x > y.
static __LONG16 isgreater (double16 x, double16 y)
{
__LONG16 r;
     r.lo = isgreater (x.lo, y.lo);
     r.hi = isgreater (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x >= y.
static __LONG16 isgreaterequal (double16 x, double16 y)
{
__LONG16 r;
     r.lo = isgreaterequal (x.lo, y.lo);
     r.hi = isgreaterequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x < y.
static __LONG16 isless (double16 x, double16 y)
{
__LONG16 r;
     r.lo = isless (x.lo, y.lo);
     r.hi = isless (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of x <= y.
static __LONG16 islessequal (double16 x, double16 y)
{
__LONG16 r;
     r.lo = islessequal (x.lo, y.lo);
     r.hi = islessequal (x.hi, y.hi);
     return(r);
}

//Returns the component-wise compare of (x < y) || (x > y)
static __LONG16 islessgreater (double16 x, double16 y)
{
__LONG16 r;
     r.lo = islessgreater (x.lo, y.lo);
     r.hi = islessgreater (x.hi, y.hi);
     return(r);
}

static __LONG16 isinf(double16 x)
{
__LONG16 r;
     r.lo = isinf (x.lo);
     r.hi = isinf (x.hi);
     return(r);
}


static __LONG16 isfinite(double16 x)
{
__LONG16 r;
     r.lo = isfinite (x.lo);
     r.hi = isfinite (x.hi);
     return(r);
}
static __LONG16 isnan(double16 x)
{
__LONG16 r;
     r.lo = isnan (x.lo);
     r.hi = isnan (x.hi);
     return(r);
}
static __LONG16 isnormal(double16 x)
{
__LONG16 r;
     r.lo = isnormal (x.lo);
     r.hi = isnormal (x.hi);
     return(r);
}

//Test if arguments are ordered. isordered() takes
//arguments x and y, and returns the result
//isequal(x, x) && isequal(y, y).

static __LONG16 isordered (double16 x, double16 y)
{
__LONG16 r;
     r.lo = isordered (x.lo, y.lo);
     r.hi = isordered (x.hi, y.hi);
     return(r);
}

//Test if arguments are unordered. isunordered() takes
//arguments x and y, returning non-zero if x or y is NaN,
//and zero otherwise.
static __LONG16 isunordered (double16 x, double16 y)
{
__LONG16 r;
     r.lo = isunordered (x.lo, y.lo);
     r.hi = isunordered (x.hi, y.hi);
     return(r);
}

//Test for sign bit. The scalar version of the function
//returns a 1 if the sign bit in the float is set else returns 0.
//The vector version of the function returns the following
//for each component in floatn: a -1 if the sign bit in the
//float is set else returns 0.
static __LONG16 signbit (double16 x)
{
__LONG16 r;
     r.lo = signbit (x.lo);
     r.hi = signbit (x.hi);
     return(r);
}



/*
ACOS
*/


static float16 acos( float16 _a)
{
float16 ret;
       ret.lo = acos(_a.lo);
       ret.hi = acos(_a.hi);
	   return ret;
}

static double16 acos( double16 _a)
{
double16 ret;
       ret.lo = acos(_a.lo);
       ret.hi = acos(_a.hi);
	   return ret;
}

// ACOSH

static float16 acosh( float16 _a)
{
float16 ret;
       ret.lo = acosh(_a.lo);
       ret.hi = acosh(_a.hi);
	   return ret;
}

static double16 acosh( double16 _a)
{
double16 ret;
       ret.lo = acosh(_a.lo);
       ret.hi = acosh(_a.hi);
	   return ret;
}

// ACOSPI

static float16 acospi( float16 _a)
{
float16 ret;
       ret.lo = acospi(_a.lo);
       ret.hi = acospi(_a.hi);
	   return ret;
}

static double16 acospi( double16 _a)
{
double16 ret;
       ret.lo = acospi(_a.lo);
       ret.hi = acospi(_a.hi);
	   return ret;
}


// ASIN

static float16 asin( float16 _a)
{
float16 ret;
       ret.lo = asin(_a.lo);
       ret.hi = asin(_a.hi);
	   return ret;
}

static double16 asin( double16 _a)
{
double16 ret;
       ret.lo = asin(_a.lo);
       ret.hi = asin(_a.hi);
	   return ret;
}


// ASINH

static float16 asinh( float16 _a)
{
float16 ret;
       ret.lo = asinh(_a.lo);
       ret.hi = asinh(_a.hi);
	   return ret;
}

static double16 asinh( double16 _a)
{
double16 ret;
       ret.lo = asinh(_a.lo);
       ret.hi = asinh(_a.hi);
	   return ret;
}

// ASINPI

static float16 asinpi( float16 _a)
{
float16 ret;
       ret.lo = asinpi(_a.lo);
       ret.hi = asinpi(_a.hi);
	   return ret;
}

static double16 asinpi( double16 _a)
{
double16 ret;
       ret.lo = asinpi(_a.lo);
       ret.hi = asinpi(_a.hi);
	   return ret;
}


// ATAN

static float16 atan( float16 _a)
{
float16 ret;
       ret.lo = atan(_a.lo);
       ret.hi = atan(_a.hi);
	   return ret;
}

static double16 atan( double16 _a)
{
double16 ret;
       ret.lo = atan(_a.lo);
       ret.hi = atan(_a.hi);
	   return ret;
}

// ATAN2

static float16 atan2( float16 _a, float16 _b)
{
float16 ret;
       ret.lo = atan2(_a.lo, _b.lo);
       ret.hi = atan2(_a.hi, _b.hi);
	   return ret;
}

static double16 atan2( double16 _a, double16 _b)
{
double16 ret;
       ret.lo = atan2(_a.lo, _b.lo);
       ret.hi = atan2(_a.hi, _b.hi);
	   return ret;
}

// ATANH

static float16 atanh( float16 _a)
{
float16 ret;
       ret.lo = atanh(_a.lo);
       ret.hi = atanh(_a.hi);
	   return ret;
}

static double16 atanh( double16 _a)
{
double16 ret;
       ret.lo = atanh(_a.lo);
       ret.hi = atanh(_a.hi);
	   return ret;
}

// ATANPI

static float16 atanpi( float16 _a)
{
float16 ret;
       ret.lo = atanpi(_a.lo);
       ret.hi = atanpi(_a.hi);
	   return ret;
}

static double16 atanpi( double16 _a)
{
double16 ret;
       ret.lo = atanpi(_a.lo);
       ret.hi = atanpi(_a.hi);
	   return ret;
}

// ATAN2

static float16 atan2pi( float16 _a, float16 _b)
{
float16 ret;
       ret.lo = atan2pi(_a.lo, _b.lo);
       ret.hi = atan2pi(_a.hi, _b.hi);
	   return ret;
}

static double16 atan2pi( double16 _a, double16 _b)
{
double16 ret;
       ret.lo = atan2pi(_a.lo, _b.lo);
       ret.hi = atan2pi(_a.hi, _b.hi);
	   return ret;
}

// CBRT
static float16 cbrt( float16 _a)
{
float16 ret;
       ret.lo = cbrt(_a.lo);
       ret.hi = cbrt(_a.hi);
	   return ret;
}

static double16 cbrt( double16 _a)
{
double16 ret;
       ret.lo = cbrt(_a.lo);
       ret.hi = cbrt(_a.hi);
	   return ret;
}



// CEIL
static float16 ceil( float16 _a)
{
float16 ret;
       ret.lo = ceil(_a.lo);
       ret.hi = ceil(_a.hi);
	   return ret;
}

static double16 ceil( double16 _a)
{
double16 ret;
       ret.lo = ceil(_a.lo);
       ret.hi = ceil(_a.hi);
	   return ret;
}


// ATAN2

static float16 copysign( float16 _a, float16 _b)
{
float16 ret;
       ret.lo = copysign(_a.lo, _b.lo);
       ret.hi = copysign(_a.hi, _b.hi);
	   return ret;
}

static double16 copysign( double16 _a, double16 _b)
{
double16 ret;
       ret.lo = copysign(_a.lo, _b.lo);
       ret.hi = copysign(_a.hi, _b.hi);
	   return ret;
}



// COS

static float16 cos( float16 _a)
{
float16 ret;
       ret.lo = cos(_a.lo);
       ret.hi = cos(_a.hi);
	   return ret;
}

static double16 cos( double16 _a)
{
double16 ret;
       ret.lo = cos(_a.lo);
       ret.hi = cos(_a.hi);
	   return ret;
}

// COSH

static float16 cosh( float16 _a)
{
float16 ret;
       ret.lo = cosh(_a.lo);
       ret.hi = cosh(_a.hi);
	   return ret;
}

static double16 cosh( double16 _a)
{
double16 ret;
       ret.lo = cosh(_a.lo);
       ret.hi = cosh(_a.hi);
	   return ret;
}

// COSPI

static float16 cospi( float16 _a)
{
float16 ret;
       ret.lo = cospi(_a.lo);
       ret.hi = cospi(_a.hi);
	   return ret;
}

static double16 cospi( double16 _a)
{
double16 ret;
       ret.lo = cospi(_a.lo);
       ret.hi = cospi(_a.hi);
	   return ret;
}

// ERFC

static float16 erfc( float16 _a)
{
float16 ret;
       ret.lo = erfc(_a.lo);
       ret.hi = erfc(_a.hi);
	   return ret;
}

static double16 erfc( double16 _a)
{
double16 ret;
       ret.lo = erfc(_a.lo);
       ret.hi = erfc(_a.hi);
	   return ret;
}


// ERF


static float16 erf( float16 _a)
{
float16 ret;
       ret.lo = erf(_a.lo);
       ret.hi = erf(_a.hi);
	   return ret;
}

static double16 erf( double16 _a)
{
double16 ret;
       ret.lo = erf(_a.lo);
       ret.hi = erf(_a.hi);
	   return ret;
}



// EXP
static float16 exp( float16 _a)
{
float16 ret;
       ret.lo = exp(_a.lo);
       ret.hi = exp(_a.hi);
	   return ret;
}

static double16 exp( double16 _a)
{
double16 ret;
       ret.lo = exp(_a.lo);
       ret.hi = exp(_a.hi);
	   return ret;
}

// EXP2

static float16 exp2( float16 _a)
{
float16 ret;
       ret.lo = exp2(_a.lo);
       ret.hi = exp2(_a.hi);
	   return ret;
}

static double16 exp2( double16 _a)
{
double16 ret;
       ret.lo = exp2(_a.lo);
       ret.hi = exp2(_a.hi);
	   return ret;
}

// EXP10

static float16 exp10( float16 _a)
{
float16 ret;
       ret.lo = exp10(_a.lo);
       ret.hi = exp10(_a.hi);
	   return ret;
}

static double16 exp10( double16 _a)
{
double16 ret;
       ret.lo = exp10(_a.lo);
       ret.hi = exp10(_a.hi);
	   return ret;
}

// EXPM1
static float16 expm1( float16 _a)
{
float16 ret;
       ret.lo = expm1(_a.lo);
       ret.hi = expm1(_a.hi);
	   return ret;
}

static double16 expm1( double16 _a)
{
double16 ret;
       ret.lo = expm1(_a.lo);
       ret.hi = expm1(_a.hi);
	   return ret;
}


// FABS
static float16 fabs( float16 _a)
{
float16 ret;
       ret.lo = fabs(_a.lo);
       ret.hi = fabs(_a.hi);
	   return ret;
}

static double16 fabs( double16 _a)
{
double16 ret;
       ret.lo = fabs(_a.lo);
       ret.hi = fabs(_a.hi);
	   return ret;
}

// FDIM
static double16 fdim( double16 _a, double16 _b)
{
double16 ret;
       ret.lo = fdim(_a.lo, _b.lo);
       ret.hi = fdim(_a.hi, _b.hi);
	   return ret;
}

static float16 fdim( float16 _a, float16 _b)
{
float16 ret;
       ret.lo = fdim(_a.lo, _b.lo);
       ret.hi = fdim(_a.hi, _b.hi);
	   return ret;
}



// FLOOR

static float16 floor( float16 _a)
{
float16 ret;
       ret.lo = floor(_a.lo);
       ret.hi = floor(_a.hi);
	   return ret;
}

static double16 floor( double16 _a)
{
double16 ret;
       ret.lo = floor(_a.lo);
       ret.hi = floor(_a.hi);
	   return ret;
}

// FMA

static float16 fma( float16 _a, float16 _b, float16 _c)
{
float16 ret;
       ret.lo = fma(_a.lo,_b.lo,_c.lo);
       ret.hi = fma(_a.hi,_b.hi,_c.hi);
	   return(ret);
}


static double16 fma( double16 _a, double16 _b, double16 _c)
{
double16 ret;
       ret.lo = fma(_a.lo,_b.lo,_c.lo);
       ret.hi = fma(_a.hi,_b.hi,_c.hi);
	   return(ret);
}


// FMAX

static float16 fmax( float16 _a, float16 _b)
{
float16 ret;
       ret.lo = fmax(_a.lo,_b.lo);
       ret.hi = fmax(_a.hi,_b.hi);
	   return(ret);
}


static double16 fmax( double16 _a, double16 _b)
{
double16 ret;
       ret.lo = fmax(_a.lo,_b.lo);
       ret.hi = fmax(_a.hi,_b.hi);
	   return(ret);
}

// FMIN

static float16 fmin( float16 _a, float16 _b)
{
float16 ret;
       ret.lo = fmin(_a.lo,_b.lo);
       ret.hi = fmin(_a.hi,_b.hi);
	   return(ret);
}


static double16 fmin( double16 _a, double16 _b)
{
double16 ret;
       ret.lo = fmin(_a.lo,_b.lo);
       ret.hi = fmin(_a.hi,_b.hi);
	   return(ret);
}


// FMOD
static float16 fmod( float16 _a, float16 _b)
{
float16 ret;
       ret.lo = fmod(_a.lo, _b.lo);
       ret.hi = fmod(_a.hi, _b.hi);
	   return ret;
}

static double16 fmod( double16 _a, double16 _b)
{
double16 ret;
       ret.lo = fmod(_a.lo, _b.lo);
       ret.hi = fmod(_a.hi, _b.hi);
	   return ret;
}







// FRAC

static float16 frac( float16 _a)
{
float16 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}

static double16 frac( double16 _a)
{
double16 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}


// FRACT

static float16 fract( float16 _a)
{
float16 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}

static double16 fract( double16 _a)
{
double16 ret;
       ret.lo = frac(_a.lo);
       ret.hi = frac(_a.hi);
	   return ret;
}

// FREXP

static float16 frexp( float16 _a, int16* _b)
{
float16 ret;
       ret.lo = frexp(_a.lo, &_b->lo);
       ret.hi = frexp(_a.hi, &_b->hi);
	   return ret;
}

static double16 frexp( double16 _a, int16* _b)
{
double16 ret;
       ret.lo = frexp(_a.lo, &_b->lo);
       ret.hi = frexp(_a.hi, &_b->hi);
	   return ret;
}

// HYPOT

static float16 hypot( float16 _a, float16 _b)
{
float16 ret;
       ret.lo = hypot(_a.lo, _b.lo);
       ret.hi = hypot(_a.hi, _b.hi);
	   return ret;
}

static double16 hypot( double16 _a, double16 _b)
{
double16 ret;
       ret.lo = hypot(_a.lo, _b.lo);
       ret.hi = hypot(_a.hi, _b.hi);
	   return ret;
}

// ILOGB

static int16 ilogb( float16 _a)
{
int16 ret;
       ret.lo = ilogb(_a.lo);
       ret.hi = ilogb(_a.hi);
	   return ret;
}

static int16 ilogb( double16 _a)
{
int16 ret;
       ret.lo = ilogb(_a.lo);
       ret.hi = ilogb(_a.hi);
	   return ret;
}

// LDEXP

static float16 ldexp( float16 _a, int16 _b)
{
float16 ret;
       ret.lo = ldexp(_a.lo, _b.lo);
       ret.hi = ldexp(_a.hi, _b.hi);
	   return ret;
}

static double16 ldexp( double16 _a, int16 _b)
{
double16 ret;
       ret.lo = ldexp(_a.lo, _b.lo);
       ret.hi = ldexp(_a.hi, _b.hi);
	   return ret;
}

static float16 ldexp( float16 _a, int _b)
{
float16 ret;
       ret = ldexp(_a, (int16)_b);
	   return ret;
}

static double16 ldexp( double16 _a, int _b)
{
double16 ret;
       ret = ldexp(_a, (int16)_b);
	   return ret;
}


// LGAMMA
static float16 lgamma( float16 _a)
{
float16 ret;
       ret.lo = lgamma(_a.lo);
       ret.hi = lgamma(_a.hi);
	   return ret;
}

static double16 lgamma( double16 _a)
{
double16 ret;
       ret.lo = lgamma(_a.lo);
       ret.hi = lgamma(_a.hi);
	   return ret;
}

// LGAMMA_R

static float16 lgamma_r( float16 _a, int16 *psign)
{
float16 ret;
       ret.lo = lgamma_r(_a.lo, &psign->lo);
       ret.hi = lgamma_r(_a.hi, &psign->hi);
	   return ret;
}

static double16 lgamma_r( double16 _a, int16 *psign)
{
double16 ret;
       ret.lo = lgamma_r(_a.lo, &psign->lo);
       ret.hi = lgamma_r(_a.hi, &psign->hi);
	   return ret;
}


// LOG

static float16 log( float16 _a)
{
float16 ret;
       ret.lo = log(_a.lo);
       ret.hi = log(_a.hi);
	   return ret;
}

static double16 log( double16 _a)
{
double16 ret;
       ret.lo = log(_a.lo);
       ret.hi = log(_a.hi);
	   return ret;
}

// LOG2

static float16 log2( float16 _a)
{
float16 ret;
       ret.lo = log2(_a.lo);
       ret.hi = log2(_a.hi);
	   return ret;
}

static double16 log2( double16 _a)
{
double16 ret;
       ret.lo = log2(_a.lo);
       ret.hi = log2(_a.hi);
	   return ret;
}


// LOG10

static float16 log10( float16 _a)
{
float16 ret;
       ret.lo = log10(_a.lo);
       ret.hi = log10(_a.hi);
	   return ret;
}

static double16 log10( double16 _a)
{
double16 ret;
       ret.lo = log10(_a.lo);
       ret.hi = log10(_a.hi);
	   return ret;
}

// LOG1P

static float16 log1p( float16 _a)
{
float16 ret;
       ret.lo = log1p(_a.lo);
       ret.hi = log1p(_a.hi);
	   return ret;
}

static double16 log1p( double16 _a)
{
double16 ret;
       ret.lo = log1p(_a.lo);
       ret.hi = log1p(_a.hi);
	   return ret;
}


// LOGB

static float16 logb( float16 _a)
{
float16 ret;
       ret.lo = logb(_a.lo);
       ret.hi = logb(_a.hi);
	   return ret;
}

static double16 logb( double16 _a)
{
double16 ret;
       ret.lo = logb(_a.lo);
       ret.hi = logb(_a.hi);
	   return ret;
}


// mad

static float16 mad( float16 _a, float16 _b, float16 _c)
{
float16 ret;
       ret.lo = mad(_a.lo, _b.lo, _c.lo);
       ret.hi = mad(_a.hi, _b.hi, _c.hi);
	   return ret;
}

static double16 mad( double16 _a, double16 _b, double16 _c)
{
double16 ret;
       ret.lo = mad(_a.lo, _b.lo, _c.lo);
       ret.hi = mad(_a.hi, _b.hi, _c.hi);
	   return ret;
}


// mogf

static float16 modf( float16 _a, int16* _b)
{
float16 ret;
       ret.lo = modf(_a.lo, &_b->lo);
       ret.hi = modf(_a.hi, &_b->hi);
	   return ret;
}

static double16 modf( double16 _a, int16* _b)
{
double16 ret;
       ret.lo = modf(_a.lo, &_b->lo);
       ret.hi = modf(_a.hi, &_b->hi);
	   return ret;
}

//NAN
static float16 nan( int16 _b)
{
float16 ret;
       ret.lo = nan(_b.lo);
       ret.hi = nan(_b.hi);
	   return ret;
}
static double16 nan( __LONG16 _b)
{
double16 ret;
       ret.lo = nan(_b.lo);
       ret.hi = nan(_b.hi);
	   return ret;
}

// NEXTAFTER
static float16 nextafter( float16 _a, float16 _b)
{
float16 ret;
       ret.lo = nextafter(_a.lo, _b.lo);
       ret.hi = nextafter(_a.hi, _b.hi);
	   return ret;
}
static double16 nextafter( double16 _a, double16 _b)
{
double16 ret;
       ret.lo = nextafter(_a.lo, _b.lo);
       ret.hi = nextafter(_a.hi, _b.hi);
	   return ret;
}

// POW
static float16 pow( float16 _a, float16 _b)
{
float16 ret;
       ret.lo = pow(_a.lo, _b.lo);
       ret.hi = pow(_a.hi, _b.hi);
	   return ret;
}

static double16 pow( double16 _a, double16 _b)
{
double16 ret;
       ret.lo = pow(_a.lo, _b.lo);
       ret.hi = pow(_a.hi, _b.hi);
	   return ret;
}

// POWN
static double16 pown( double16 _a, int16 _b)
{
double16 ret;
       ret.lo = pown(_a.lo, _b.lo);
       ret.hi = pown(_a.hi, _b.hi);
	   return ret;
}

static float16 pown( float16 _a, int16 _b)
{
float16 ret;
       ret.lo = pown(_a.lo, _b.lo);
       ret.hi = pown(_a.hi, _b.hi);
	   return ret;
}

// POWR
static double16 powr( double16 _a, double16 _b)
{
double16 ret;
       ret.lo = powr(_a.lo, _b.lo);
       ret.hi = powr(_a.hi, _b.hi);
	   return ret;
}

static float16 powr( float16 _a, float16 _b)
{
float16 ret;
       ret.lo = powr(_a.lo, _b.lo);
       ret.hi = powr(_a.hi, _b.hi);
	   return ret;
}

// REMAINDER
static
float16 remainder(float16 x, float16 p)
{
float16 ret;
        ret.lo = remainder(x.lo, p.lo);
        ret.hi = remainder(x.hi, p.hi);
		return(ret);
}

static
double16 remainder(double16 x, double16 p)
{
double16 ret;
        ret.lo = remainder(x.lo, p.lo);
        ret.hi = remainder(x.hi, p.hi);
		return(ret);
}


// REMQUO
static
float16 remquo(float16 x, float16 p, int16 *pquo)
{
float16 ret;
        ret.lo = remquo(x.lo, p.lo, &pquo->lo);
        ret.hi = remquo(x.hi, p.hi, &pquo->hi);
		return(ret);
}

static
double16 remquo(double16 x, double16 p, int16 *pquo)
{
double16 ret;
        ret.lo = remquo(x.lo, p.lo, &pquo->lo);
        ret.hi = remquo(x.hi, p.hi, &pquo->hi);
		return(ret);
}


// RINT

static float16
rint (float16 x)
{
float16 ret;
       ret.lo = rint(x.lo);
       ret.hi = rint(x.hi);
	   return(ret);
}

static double16
rint (double16 x)
{
double16 ret;
       ret.lo = rint(x.lo);
       ret.hi = rint(x.hi);
	   return(ret);
}

// ROOTN
static float16 rootn( float16 _a, int16 _n)
{
float16 ret;
       ret.lo = rootn(_a.lo, _n.lo);
       ret.hi = rootn(_a.hi, _n.hi);
	   return ret;
}

static double16 rootn( double16 _a, int16 _n)
{
double16 ret;
       ret.lo = rootn(_a.lo, _n.lo);
       ret.hi = rootn(_a.hi, _n.hi);
	   return ret;
}

//ROUND

static float16 round( float16 _a)
{
float16 ret;
       ret.lo = round(_a.lo);
       ret.hi = round(_a.hi);
	   return ret;
}

static double16 round( double16 _a)
{
double16 ret;
       ret.lo = round(_a.lo);
       ret.hi = round(_a.hi);
	   return ret;
}


//RSQRT

static float16 rsqrt( float16 _a)
{
float16 ret;
       ret.lo = rsqrt(_a.lo);
       ret.hi = rsqrt(_a.hi);
	   return ret;
}

static double16 rsqrt( double16 _a)
{
double16 ret;
       ret.lo = rsqrt(_a.lo);
       ret.hi = rsqrt(_a.hi);
	   return ret;
}

//SIN

static float16 sin( float16 _a)
{
float16 ret;
       ret.lo = sin(_a.lo);
       ret.hi = sin(_a.hi);
	   return ret;
}

static double16 sin( double16 _a)
{
double16 ret;
       ret.lo = sin(_a.lo);
       ret.hi = sin(_a.hi);
	   return ret;
}

//SINCOS

static float16 sincos( float16 _a, float16*_b)
{
float16 ret;
       ret.lo = sincos(_a.lo, &_b->lo);
       ret.hi = sincos(_a.hi, &_b->hi);
	   return ret;
}

static double16 sincos( double16 _a, double16*_b)
{
double16 ret;
       ret.lo = sincos(_a.lo, &_b->lo);
       ret.hi = sincos(_a.hi, &_b->hi);
	   return ret;
}

//SINH

static float16 sinh( float16 _a)
{
float16 ret;
       ret.lo = sinh(_a.lo);
       ret.hi = sinh(_a.hi);
	   return ret;
}

static double16 sinh( double16 _a)
{
double16 ret;
       ret.lo = sinh(_a.lo);
       ret.hi = sinh(_a.hi);
	   return ret;
}


//SINPI

static float16 sinpi( float16 _a)
{
float16 ret;
       ret.lo = sinpi(_a.lo);
       ret.hi = sinpi(_a.hi);
	   return ret;
}

static double16 sinpi( double16 _a)
{
double16 ret;
       ret.lo = sinpi(_a.lo);
       ret.hi = sinpi(_a.hi);
	   return ret;
}


//SQRT

static float16 sqrt( float16 _a)
{
float16 ret;
       ret.lo = sqrt(_a.lo);
       ret.hi = sqrt(_a.hi);
	   return ret;
}

static double16 sqrt( double16 _a)
{
double16 ret;
       ret.lo = sqrt(_a.lo);
       ret.hi = sqrt(_a.hi);
	   return ret;
}

//TAN

static float16 tan( float16 _a)
{
float16 ret;
       ret.lo = tan(_a.lo);
       ret.hi = tan(_a.hi);
	   return ret;
}

static double16 tan( double16 _a)
{
double16 ret;
       ret.lo = tan(_a.lo);
       ret.hi = tan(_a.hi);
	   return ret;
}

//TANH

static float16 tanh( float16 _a)
{
float16 ret;
       ret.lo = tanh(_a.lo);
       ret.hi = tanh(_a.hi);
	   return ret;
}

static double16 tanh( double16 _a)
{
double16 ret;
       ret.lo = tanh(_a.lo);
       ret.hi = tanh(_a.hi);
	   return ret;
}

//TANPI

static float16 tanpi( float16 _a)
{
float16 ret;
       ret.lo = tanpi(_a.lo);
       ret.hi = tanpi(_a.hi);
	   return ret;
}

static double16 tanpi( double16 _a)
{
double16 ret;
       ret.lo = tanpi(_a.lo);
       ret.hi = tanpi(_a.hi);
	   return ret;
}


// TGAMMA
static float16 tgamma( float16 _a)
{
float16 ret;
       ret.lo = tgamma(_a.lo);
       ret.hi = tgamma(_a.hi);
	   return ret;
}
static double16 tgamma( double16 _a)
{
double16 ret;
       ret.lo = tgamma(_a.lo);
       ret.hi = tgamma(_a.hi);
	   return ret;
}

// TRUNC

static float16 trunc( float16 _a)
{
float16 ret;
       ret.lo = trunc(_a.lo);
       ret.hi = trunc(_a.hi);
	   return ret;
}

static double16 trunc( double16 _a)
{
double16 ret;
       ret.lo = trunc(_a.lo);
       ret.hi = trunc(_a.hi);
	   return ret;
}

static float16 native_cos( float16 _a)
{
float16 ret;
       ret.lo = native_cos(_a.lo);
       ret.hi = native_cos(_a.hi);
	   return ret;
}

static double16 native_cos( double16 _a)
{
double16 ret;
       ret.lo = native_cos(_a.lo);
       ret.hi = native_cos(_a.hi);
	   return ret;
}


static double16 native_divide( double16 _a, double16 _b)
{
double16 ret;
       ret.lo = native_divide(_a.lo, _b.lo);
       ret.hi = native_divide(_a.hi, _b.hi);
	   return ret;
}

static float16 native_divide( float16 _a, float16 _b)
{
float16 ret;
       ret.lo = native_divide(_a.lo, _b.lo);
       ret.hi = native_divide(_a.hi, _b.hi);
	   return ret;
}

static float16 native_exp( float16 _a)
{
float16 ret;
       ret.lo = native_exp(_a.lo);
       ret.hi = native_exp(_a.hi);
	   return ret;
}

static double16 native_exp( double16 _a)
{
double16 ret;
       ret.lo = native_exp(_a.lo);
       ret.hi = native_exp(_a.hi);
	   return ret;
}

static float16 native_exp2( float16 _a)
{
float16 ret;
       ret.lo = native_exp2(_a.lo);
       ret.hi = native_exp2(_a.hi);
	   return ret;
}

static double16 native_exp2( double16 _a)
{
double16 ret;
       ret.lo = native_exp2(_a.lo);
       ret.hi = native_exp2(_a.hi);
	   return ret;
}

static float16 native_exp10( float16 _a)
{
float16 ret;
       ret.lo = native_exp10(_a.lo);
       ret.hi = native_exp10(_a.hi);
	   return ret;
}

static double16 native_exp10( double16 _a)
{
double16 ret;
       ret.lo = native_exp10(_a.lo);
       ret.hi = native_exp10(_a.hi);
	   return ret;
}

static float16 native_log( float16 _a)
{
float16 ret;
       ret.lo = native_log(_a.lo);
       ret.hi = native_log(_a.hi);
	   return ret;
}

static double16 native_log( double16 _a)
{
double16 ret;
       ret.lo = native_log(_a.lo);
       ret.hi = native_log(_a.hi);
	   return ret;
}

static float16 native_log2( float16 _a)
{
float16 ret;
       ret.lo = native_log2(_a.lo);
       ret.hi = native_log2(_a.hi);
	   return ret;
}

static double16 native_log2( double16 _a)
{
double16 ret;
       ret.lo = native_log2(_a.lo);
       ret.hi = native_log2(_a.hi);
	   return ret;
}

static float16 native_log10( float16 _a)
{
float16 ret;
       ret.lo = native_log10(_a.lo);
       ret.hi = native_log10(_a.hi);
	   return ret;
}

static double16 native_log10( double16 _a)
{
double16 ret;
       ret.lo = native_log10(_a.lo);
       ret.hi = native_log10(_a.hi);
	   return ret;
}

static float16 native_powr( float16 _a, float16 _b)
{
float16 ret;
       ret.lo = native_powr(_a.lo, _b.lo);
       ret.hi = native_powr(_a.hi, _b.hi);
	   return ret;
}

static double16 native_powr( double16 _a, double16 _b)
{
double16 ret;
       ret.lo = native_powr(_a.lo, _b.lo);
       ret.hi = native_powr(_a.hi, _b.hi);
	   return ret;
}

static float16 native_recip( float16 _a)
{
float16 ret;
       ret.lo = native_recip(_a.lo);
       ret.hi = native_recip(_a.hi);
	   return ret;
}

static double16 native_recip( double16 _a)
{
double16 ret;
       ret.lo = native_recip(_a.lo);
       ret.hi = native_recip(_a.hi);
	   return ret;
}

static float16 native_rsqrt( float16 _a)
{
float16 ret;
       ret.lo = native_rsqrt(_a.lo);
       ret.hi = native_rsqrt(_a.hi);
	   return ret;
}

static double16 native_rsqrt( double16 _a)
{
double16 ret;
       ret.lo = native_rsqrt(_a.lo);
       ret.hi = native_rsqrt(_a.hi);
	   return ret;
}

static float16 native_sin( float16 _a)
{
float16 ret;
       ret.lo = native_sin(_a.lo);
       ret.hi = native_sin(_a.hi);
	   return ret;
}

static double16 native_sin( double16 _a)
{
double16 ret;
       ret.lo = native_sin(_a.lo);
       ret.hi = native_sin(_a.hi);
	   return ret;
}

static float16 native_sqrt( float16 _a)
{
float16 ret;
       ret.lo = native_sqrt(_a.lo);
       ret.hi = native_sqrt(_a.hi);
	   return ret;
}

static double16 native_sqrt( double16 _a)
{
double16 ret;
       ret.lo = native_sqrt(_a.lo);
       ret.hi = native_sqrt(_a.hi);
	   return ret;
}

static float16 native_tan( float16 _a)
{
float16 ret;
       ret.lo = native_tan(_a.lo);
       ret.hi = native_tan(_a.hi);
	   return ret;
}

static double16 native_tan( double16 _a)
{
double16 ret;
       ret.lo = native_tan(_a.lo);
       ret.hi = native_tan(_a.hi);
	   return ret;
}


// CLAMP
static float16 clamp( float16 _a, float16 _min, float16 _max)
{
float16 ret;
       ret.lo = clamp(_a.lo, _min.lo, _max.lo);
       ret.hi = clamp(_a.hi, _min.hi, _max.hi);
	   return ret;
}

static double16 clamp( double16 _a, double16 _min, double16 _max)
{
double16 ret;
       ret.lo = clamp(_a.lo, _min.lo, _max.lo);
       ret.hi = clamp(_a.hi, _min.hi, _max.hi);
	   return ret;
}

// DEGREES
static double16
degrees(double16 radians)
{
double16 ret;
    ret.lo = degrees(radians.lo);
    ret.hi = degrees(radians.hi);
    return(ret);
}

static float16
degrees(float16 radians)
{
float16 ret;
    ret.lo = degrees(radians.lo);
    ret.hi = degrees(radians.hi);
    return(ret);
}


//MAX
float16
static max(float16 x, float16 y)
{
float16 r;
    r.lo = max(x.lo, y.lo);
    r.hi = max(x.hi, y.hi);
    return(r);
}

double16
static max(double16 x, double16 y)
{
double16 r;
    r.lo = max(x.lo, y.lo);
    r.hi = max(x.hi, y.hi);
    return(r);
}

//MIN
float16
static min(float16 x, float16 y)
{
float16 r;
    r.lo = min(x.lo, y.lo);
    r.hi = min(x.hi, y.hi);
    return(r);
}

double16
static min(double16 x, double16 y)
{
double16 r;
    r.lo = min(x.lo, y.lo);
    r.hi = min(x.hi, y.hi);
    return(r);
}

// MIX
static double16
mix(double16 x, double16 y, double16 a)
{
double16 r;
	r.lo = mix(x.lo, y.lo, a.lo);
	r.hi = mix(x.hi, y.hi, a.hi);
    return(r);
}


static float16
mix(float16 x, float16 y, float16 a)
{
float16 r;
	r.lo = mix(x.lo, y.lo, a.lo);
	r.hi = mix(x.hi, y.hi, a.hi);
    return(r);
}

//RADIANS
static double16
radians(double16 degrees)
{
double16 ret;
    ret.lo = radians(degrees.lo);
    ret.hi = radians(degrees.hi);
    return(ret);
}


static float16
radians(float16 degrees)
{
float16 ret;
    ret.lo = radians(degrees.lo);
    ret.hi = radians(degrees.hi);
    return(ret);
}

//STEP
static double16
step(double16 edge, double16 x)
{
double16 r;
    r.lo = step(edge.lo,x.lo);
    r.hi = step(edge.hi,x.hi);
    return(r);
}

static float16
step(float16 edge, float16 x)
{
float16 r;
    r.lo = step(edge.lo,x.lo);
    r.hi = step(edge.hi,x.hi);
    return(r);
}


// SMOOTHEDGE
static double16
smoothstep(double16 edge0, double16 edge1, double16 x)
{
double16 r;
	r.lo = mix(edge0.lo, edge1.lo, x.lo);
	r.hi = mix(edge0.hi, edge1.hi, x.hi);
    return(r);
}


static float16
smoothstep(float16 edge0, float16 edge1, float16 x)
{
float16 r;
	r.lo = mix(edge0.lo, edge1.lo, x.lo);
	r.hi = mix(edge0.hi, edge1.hi, x.hi);
    return(r);
}


// SIGN
int16
static sign(float16 src)
  {
    int16 ret;
       ret.lo = sign(src.lo);
       ret.hi = sign(src.hi);
	   return ret;
  }
int16
static sign(double16 src)
  {
    int16 ret;
       ret.lo = sign(src.lo);
       ret.hi = sign(src.hi);
	   return ret;
  }




#if 1

// ABS

template <class _T>
  _T abs(_T _a)
  {
  _T tmp;
     tmp.lo = abs(_a.lo);
     tmp.hi = abs(_a.hi);
//     return(_a.SIMDabs());
	 return(tmp);
  }

/*
ALL
*/
template <class _T>
  int all(_T _a)
  {
  int tmp = all(_a.lo) & all(_a.hi);
//     return(_a.SIMDall());
  }

/*
ANY
*/
template <class _T>
  int any(_T _a)
  {
  int tmp = any(_a.lo) | any(_a.hi);
     return(tmp);
  }



/*
BITSELECT
*/

template <class _T>
  int bitselect(_T _a,_T _b,_T _c)
  {
     return(_a.SIMDbitselect(_b, _c));
  }




/*
MIN
*/
template <class _T>
  _T min(_T _a, _T _b)
  {
 _T tmp;
     tmp.lo = min(_a.lo, _b.lo);
     tmp.hi = min(_a.hi, _b.hi);
	 return(tmp);
//     return(_a.SIMDmin(_b));
  }
/*
MAX
*/
template <class _T>
  _T max(_T _a, _T _b)
  {
 _T tmp;
     tmp.lo = max(_a.lo, _b.lo);
     tmp.hi = max(_a.hi, _b.hi);
	 return(tmp);
//     return(_a.SIMDmax(_b));
  }

template <class _T, class _TN>
_TN genvload(size_t off, _T *p, int n)
{
_TN ret;
   memcpy(&ret, p+off*n, sizeof(_TN));
   return(ret);
}

template <class _T, class _TN>
_TN genvload(size_t off, _T const*p, int n)
{
_TN ret;
   memcpy(&ret, p+off*n, sizeof(_TN));
   return(ret);
}



template <class _T, class _TN>
void genvstore(_TN data, size_t off, _T *p, int n)
{
   memcpy(p+off*n, &data, sizeof(_TN));
}


template <class _T>
_T vload(size_t off, _T *p)
{
	
_T ret = genvload<_T, _T>(off, p, 1);
   return(ret);
}

template <class _T>
void vstore(_T data, size_t off, _T *p)
{
   genvstore<_T, _T>(data, off, p, 1);
}

template <class _T>
clemu_vector2<_T> vload2(size_t off, _T *p)
{
	
clemu_vector2<_T> ret = genvload<_T, clemu_vector2<_T>>(off, p, 2);
   return(ret);
}

template <class _T>
clemu_vector2<_T> vload2(size_t off, _T const *p)
{
	
clemu_vector2<_T> ret = genvload<_T, clemu_vector2<_T>>(off, p, 2);
   return(ret);
}


template <class _T>
void vstore2(clemu_vector2<_T> data, size_t off, _T *p)
{
   genvstore<_T, clemu_vector2<_T>>(data, off, p, 2);
}



template <class _T>
clemu_vector4<_T> vload4(size_t off, _T *p)
{
	
clemu_vector4<_T> ret = genvload<_T, clemu_vector4<_T>>(off, p, 4);
   return(ret);
}

template <class _T>
clemu_vector4<_T> vload4(size_t off, _T const*p)
{
	
clemu_vector4<_T> ret = genvload<_T, clemu_vector4<_T>>(off, p, 4);
   return(ret);
}


template <class _T>
void vstore4(clemu_vector4<_T> data, size_t off, _T *p)
{
   genvstore<_T, clemu_vector4<_T>>(data, off, p, 4);
}



template <class _T>
clemu_vector8<_T> vload8(size_t off, _T *p)
{
	
clemu_vector8<_T> ret = genvload<_T, clemu_vector8<_T>>(off, p, 8);
   return(ret);
}

template <class _T>
clemu_vector8<_T> vload8(size_t off, _T const*p)
{
	
clemu_vector8<_T> ret = genvload<_T, clemu_vector8<_T>>(off, p, 8);
   return(ret);
}


template <class _T>
void vstore8(clemu_vector8<_T> data, size_t off, _T *p)
{
   genvstore<_T, clemu_vector8<_T>>(data, off, p, 8);
}


template <class _T>
clemu_vector16<_T> vload16(size_t off, _T *p)
{
	
clemu_vector16<_T> ret = genvload<_T, clemu_vector16<_T>>(off, p, 16);
   return(ret);
}

template <class _T>
clemu_vector16<_T> vload16(size_t off, _T const*p)
{
	
clemu_vector16<_T> ret = genvload<_T, clemu_vector16<_T>>(off, p, 16);
   return(ret);
}


template <class _T>
void vstore16(clemu_vector16<_T> data, size_t off, _T *p)
{
   genvstore<_T, clemu_vector16<_T>>(data, off, p, 16);
}


#endif

/*---------------------------------------------------------------------------------------------------------
 intrinsics
---------------------------------------------------------------------------------------------------------*/



// GENERIC VECTOR 
#define VECA2(_Vec, _Arr) VEC2(_Vec, _Arr[0], _Arr[1])
#define VECA3(_Vec, _Arr) VEC3(_Vec, _Arr[0], _Arr[1], _Arr[2])
#define VECA4(_Vec, _Arr) VEC4(_Vec, _Arr[0], _Arr[1], _Arr[2], _Arr[3])



#endif // CALSIMC_HLSL


