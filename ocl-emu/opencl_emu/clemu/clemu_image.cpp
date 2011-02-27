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

// clemu_image.cpp : 
//

#include "clemu_cltypes_intrinsics.h"



#define CLAMP_LEFT   (1 << 0)
#define CLAMP_TOP    (1 << 1)
#define CLAMP_RIGHT  (1 << 2)
#define CLAMP_BOTTOM (1 << 3)

static 
int NmbrChannels( uint channel_order )
{
int ret  = 0;
	switch(channel_order)
	{
	case CL_R :           
	case CL_A :         
	case CL_INTENSITY : 
	case CL_LUMINANCE : 
		ret = 1;
		break;
	case CL_RG :
	case CL_RA :
	case CL_Rx :
		ret = 2;
		break;
	case CL_RGB :
	case CL_RGx :
		ret = 3;
		break;
	case CL_RGBA :
	case CL_BGRA :
	case CL_ARGB :
	case CL_RGBx :
		ret = 4;
		break;
	}
	return(ret);
}
static 
int BytesPreChannel( uint channel_data_type )
{
int ret  = 0;
    switch (channel_data_type)
	{
	case CL_SNORM_INT8:
	case CL_UNORM_INT8:
	case CL_SIGNED_INT8:
	case CL_UNSIGNED_INT8:
		ret = 1;
		break;
	case CL_SNORM_INT16:
	case CL_UNORM_INT16:
	case CL_SIGNED_INT16:
	case CL_UNSIGNED_INT16:
		ret = 2;
		break;
	case CL_SIGNED_INT32:
	case CL_UNSIGNED_INT32:
	case CL_HALF_FLOAT:
	case CL_FLOAT:
		ret = 4;
		break;

	}
	return(ret);

}

//#define CL_UNORM_SHORT_565                          0x10D4
//#define CL_UNORM_SHORT_555                          0x10D5
//#define CL_UNORM_INT_101010                         0x10D6


static
void ComputeByteOffsetUnnrmCoord2( int* _offset, int *clamp,  const ClImageArg * img, int2 coord, int doclamping = 1)
{
int pixel_stride;
int nbr_channels;
int bytes_per_channel;
int pitch;
    nbr_channels = NmbrChannels(img->image_format.image_channel_order);
    bytes_per_channel = BytesPreChannel(img->image_format.image_channel_data_type);
	pixel_stride = bytes_per_channel * nbr_channels;
	if ( img->image_format.image_channel_data_type == CL_UNORM_SHORT_565 ||
         img->image_format.image_channel_data_type == CL_UNORM_SHORT_555 )
	{
		pixel_stride = 2;
	}
	if ( img->image_format.image_channel_data_type == CL_UNORM_INT_101010 )
	{
		pixel_stride = 4;
	}


	pitch = img->image_row_pitch;

    *clamp = 0;
	if ( doclamping )
	{ 

	    if ( coord.x < 0 )
	    {
            coord.x = 0;
	        *clamp |= CLAMP_LEFT;
	    }

	    if ( coord.x >= img->image_width )
	    {
            coord.x = img->image_width - 1;
	        *clamp |= CLAMP_RIGHT;
     	}

	    if ( coord.y < 0 )
	    {
             coord.y = 0;
	         *clamp |= CLAMP_TOP;
	    }

	    if ( coord.y >= img->image_height )
	    {
             coord.y = img->image_height - 1;
	         *clamp |= CLAMP_BOTTOM;
	    }
	}

	pitch = (pitch == 0)? img->image_width * pixel_stride : pitch;
	*_offset = pitch * coord.y + pixel_stride * coord.x;

}

static
uint4 getUINT4(const ClImageArg * img, int _offset)
{
uint4 ret = 0;
int channel_order = img->image_format.image_channel_order;
int channel_data_type = img->image_format.image_channel_data_type;
unsigned char * data_ptr = (unsigned char * )img->host_ptr + _offset;
   switch(channel_order)
   {

	case CL_RGBA :
		switch(channel_data_type)
		{
           case CL_SIGNED_INT8:
	       case CL_UNSIGNED_INT8:
               ret.x = data_ptr[0];
               ret.y = data_ptr[1];
               ret.z = data_ptr[2];
               ret.w = data_ptr[3];
			   break;
     	  case CL_SIGNED_INT16:
	      case CL_UNSIGNED_INT16:
			  {
              unsigned short * ushort_ptr = (unsigned short * )data_ptr;
			     ret.x = ushort_ptr[0];
			     ret.y = ushort_ptr[1];
			     ret.z = ushort_ptr[2];
			     ret.w = ushort_ptr[3];
			  }
			  break;
      	  case CL_SIGNED_INT32:
	      case CL_UNSIGNED_INT32:
			  {
              unsigned int * uint_ptr = (unsigned int * )data_ptr;
			     ret.x = uint_ptr[0];
			     ret.y = uint_ptr[1];
			     ret.z = uint_ptr[2];
			     ret.w = uint_ptr[3];
			  }
			  break;

	      case CL_FLOAT:
			  {
              float * flt_ptr = (float * )data_ptr;
			     ret.x = as_uint(flt_ptr[0]);
			     ret.y = as_uint(flt_ptr[1]);
			     ret.z = as_uint(flt_ptr[2]);
			     ret.w = as_uint(flt_ptr[3]);
			  }
			  break;
		}
		break;
	case CL_BGRA :
		switch(channel_data_type)
		{
           case CL_SIGNED_INT8:
	       case CL_UNSIGNED_INT8:
               ret.x = data_ptr[2];
               ret.y = data_ptr[1];
               ret.z = data_ptr[0];
               ret.w = data_ptr[3];
			   break;
/*

     	  case CL_SIGNED_INT16:
	      case CL_UNSIGNED_INT16:
			  {
              unsigned short * ushort_ptr = (unsigned short * )data_ptr;
			     ret.x = ushort_ptr[2];
			     ret.y = ushort_ptr[1];
			     ret.z = ushort_ptr[0];
			     ret.w = ushort_ptr[3];
			  }
			  break;
      	  case CL_SIGNED_INT32:
	      case CL_UNSIGNED_INT32:
	      case CL_FLOAT:
			  {
              unsigned int * uint_ptr = (unsigned int * )data_ptr;
			     ret.x = uint_ptr[2];
			     ret.y = uint_ptr[1];
			     ret.z = uint_ptr[0];
			     ret.w = uint_ptr[3];
			  }
*/	    	  break;

		}
		break;
	case CL_ARGB :
		switch(channel_data_type)
		{
           case CL_SIGNED_INT8:
	       case CL_UNSIGNED_INT8:
               ret.x = data_ptr[1];
               ret.y = data_ptr[2];
               ret.z = data_ptr[3];
               ret.w = data_ptr[0];
			   break;


/*
     	  case CL_SIGNED_INT16:
	      case CL_UNSIGNED_INT16:
			  {
              unsigned short * ushort_ptr = (unsigned short * )data_ptr;
			     ret.x = ushort_ptr[1];
			     ret.y = ushort_ptr[2];
			     ret.z = ushort_ptr[3];
			     ret.w = ushort_ptr[0];
			  }
			  break;
      	  case CL_SIGNED_INT32:
	      case CL_UNSIGNED_INT32:
	      case CL_FLOAT:
			  {
              unsigned int * uint_ptr = (unsigned int * )data_ptr;
			     ret.x = uint_ptr[1];
			     ret.y = uint_ptr[2];
			     ret.z = uint_ptr[3];
			     ret.w = uint_ptr[0];
			  }
			  break;
*/

		}


		break;

       
   }

   return (ret);

}

static
int4 getINT4(const ClImageArg * img, int _offset)
{
int4 ret = convert_int4(getUINT4(img, _offset));
    return(ret);
}



static
void setUINT4(const ClImageArg * img, int _offset, uint4 data)
{
int channel_order = img->image_format.image_channel_order;
int channel_data_type = img->image_format.image_channel_data_type;
unsigned char * data_ptr = (unsigned char * )img->host_ptr + _offset;
   switch(channel_order)
   {
	case CL_RGBA :
		switch(channel_data_type)
		{
           case CL_SIGNED_INT8:
	       case CL_UNSIGNED_INT8:
               data_ptr[0] = data.x;
               data_ptr[1] = data.y;
               data_ptr[2] = data.z;
               data_ptr[3] = data.w;
			   break;
     	  case CL_SIGNED_INT16:
	      case CL_UNSIGNED_INT16:
			  {
              unsigned short * ushort_ptr = (unsigned short * )data_ptr;
			     ushort_ptr[0] = data.x;
			     ushort_ptr[1] = data.y;
			     ushort_ptr[2] = data.z;
			     ushort_ptr[3] = data.w;
			  }
			  break;
      	  case CL_SIGNED_INT32:
	      case CL_UNSIGNED_INT32:
	      case CL_FLOAT:
			  {
              unsigned int * uint_ptr = (unsigned int * )data_ptr;
			     uint_ptr[0] = data.x;
			     uint_ptr[1] = data.y;
			     uint_ptr[2] = data.z;
			     uint_ptr[3] = data.w;
			  }
			  break;

		}
		break;
	case CL_BGRA :
		switch(channel_data_type)
		{
           case CL_SIGNED_INT8:
	       case CL_UNSIGNED_INT8:
               data_ptr[2] = data.x;
               data_ptr[1] = data.y;
               data_ptr[0] = data.z;
               data_ptr[3] = data.w;
			   break;
		}

		break;
	case CL_ARGB :
		switch(channel_data_type)
		{
           case CL_SIGNED_INT8:
	       case CL_UNSIGNED_INT8:
               data_ptr[1] = data.x;
               data_ptr[2] = data.y;
               data_ptr[3] = data.z;
               data_ptr[0] = data.w;
			   break;
		}


		break;
       
   }


}

static
void setINT4(const ClImageArg * img, int _offset, int4 data)
{
     setUINT4(img, _offset, convert_uint4(data));
}



static
float unorm8tofloat( unsigned char _uc)
{
float ret = (float)_uc / 255.f;
      return (ret); 
}

static
float unorm10tofloat( unsigned int _ui10)
{
float ret = (float)((_ui10 & 0x3ff) / 1023.f);
      return (ret); 
}


static
float unorm16tofloat( unsigned short _us)
{
float ret = (float)((double)_us / 65535.);
      return (ret); 
}

static
float snorm8tofloat( char _c )
{
float ret = max(-1.0f, (float)_c / 127.0f);
    return(ret);
}

static
float snorm16tofloat( short _s )
{
float ret = max(-1.0f, (float)((double)_s / 32767.));
    return(ret);
}



static
unsigned char float_tounorm8( float _f)
{
unsigned char ret = (unsigned char)(clamp(_f, 0.f, 1.f) * 255.f + 0.5f);
      return (ret); 
}

static
unsigned int float_tounorm10( float _f)
{
unsigned int ret = min((uint)(clamp(_f, 0.f, 1.f) * 1023.f +0.5f), (uint)0x3ff);
      return (ret); 
}


static
unsigned short float_tounorm16( float _f)
{
unsigned short ret = (unsigned short)(clamp(_f, 0.f, 1.f) * 65535.f + 0.5f);
	return (ret); 
}

static
char float_tosnorm8( float _f)
{
char ret = ((char)(abs(clamp(_f, -1.f, 1.f)) * 127.f + 0.5f)) * sign(_f);
      return (ret); 
}

static
short float_tosnorm16( float _f)
{
short ret = ((short)(abs(clamp(_f, -1.f, 1.f)) * 32767.f + 0.5f)) * sign(_f);
      return (ret); 
}



static
uint4 getFLOAT4(const ClImageArg * img, int _offset)
{
float4 ret = 0;
int channel_order = img->image_format.image_channel_order;
int channel_data_type = img->image_format.image_channel_data_type;
unsigned char * data_ptr = (unsigned char * )img->host_ptr + _offset;
   switch(channel_order)
   {

	case CL_RGBA :
		switch(channel_data_type)
		{
	       case CL_UNSIGNED_INT8:
               ret.x = unorm8tofloat(data_ptr[0]);
               ret.y = unorm8tofloat(data_ptr[1]);
               ret.z = unorm8tofloat(data_ptr[2]);
               ret.w = unorm8tofloat(data_ptr[3]);
			   break;
          case CL_SIGNED_INT8:
			  {
              char * cdata_ptr = (char * )img->host_ptr;
                 ret.x = snorm8tofloat(cdata_ptr[0]);
                 ret.y = snorm8tofloat(cdata_ptr[1]);
                 ret.z = snorm8tofloat(cdata_ptr[2]);
                 ret.w = snorm8tofloat(cdata_ptr[3]);
			  }
			   break;
	      case CL_UNSIGNED_INT16:
			  {
              unsigned short * ushort_ptr = (unsigned short * )data_ptr;
			     ret.x = unorm16tofloat(ushort_ptr[0]);
			     ret.y = unorm16tofloat(ushort_ptr[1]);
			     ret.z = unorm16tofloat(ushort_ptr[2]);
			     ret.w = unorm16tofloat(ushort_ptr[3]);
			  }
			  break;
     	  case CL_SIGNED_INT16:
			  {
              short * short_ptr = (short * )data_ptr;
			     ret.x = snorm16tofloat(short_ptr[0]);
			     ret.y = snorm16tofloat(short_ptr[1]);
			     ret.z = snorm16tofloat(short_ptr[2]);
			     ret.w = snorm16tofloat(short_ptr[3]);
			  }

			  break;

	      case CL_FLOAT:
			  {
              float * float_ptr = (float * )data_ptr;
			     ret.x = float_ptr[0];
			     ret.y = float_ptr[1];
			     ret.z = float_ptr[2];
			     ret.w = float_ptr[3];
			  }
			  break;
      	  case CL_SIGNED_INT32:
	      case CL_UNSIGNED_INT32:
			  {
              uint * uint_ptr = (uint * )data_ptr;
			     ret.x = as_float(uint_ptr[0]);
			     ret.y = as_float(uint_ptr[1]);
			     ret.z = as_float(uint_ptr[2]);
			     ret.w = as_float(uint_ptr[3]);
			  }
			  break;

		}
		break;
	case CL_BGRA :
		switch(channel_data_type)
		{
	       case CL_UNSIGNED_INT8:
               ret.x = unorm8tofloat(data_ptr[2]);
               ret.y = unorm8tofloat(data_ptr[1]);
               ret.z = unorm8tofloat(data_ptr[0]);
               ret.w = unorm8tofloat(data_ptr[3]);


			   break;
           case CL_SIGNED_INT8:
			   {
              char * cdata_ptr = (char * )img->host_ptr;
                 ret.x = snorm8tofloat(cdata_ptr[2]);
                 ret.y = snorm8tofloat(cdata_ptr[1]);
                 ret.z = snorm8tofloat(cdata_ptr[0]);
                 ret.w = snorm8tofloat(cdata_ptr[3]);

			   }
               break;

	      case CL_UNSIGNED_INT16:
			  {
              unsigned short * ushort_ptr = (unsigned short * )data_ptr;
			     ret.x = unorm16tofloat(ushort_ptr[2]);
			     ret.y = unorm16tofloat(ushort_ptr[1]);
			     ret.z = unorm16tofloat(ushort_ptr[0]);
			     ret.w = unorm16tofloat(ushort_ptr[3]);


			  }
			  break;
     	  case CL_SIGNED_INT16:
			  {
              short * short_ptr = (short * )data_ptr;
			     ret.x = snorm16tofloat(short_ptr[2]);
			     ret.y = snorm16tofloat(short_ptr[1]);
			     ret.z = snorm16tofloat(short_ptr[0]);
			     ret.w = snorm16tofloat(short_ptr[3]);
			  }
             break;
	      case CL_FLOAT:
			  {
              float * float_ptr = (float * )data_ptr;
			     ret.x = float_ptr[2];
			     ret.y = float_ptr[1];
			     ret.z = float_ptr[0];
			     ret.w = float_ptr[3];
			  }
	    	  break;
      	  case CL_SIGNED_INT32:
	      case CL_UNSIGNED_INT32:
			  {
              uint * uint_ptr = (uint * )data_ptr;
			     ret.x = as_float(uint_ptr[2]);
			     ret.y = as_float(uint_ptr[1]);
			     ret.z = as_float(uint_ptr[0]);
			     ret.w = as_float(uint_ptr[3]);
			  }
			  break;


		}
		break;
	case CL_ARGB :
		switch(channel_data_type)
		{
	       case CL_UNSIGNED_INT8:
               ret.x = unorm8tofloat(data_ptr[1]);
               ret.y = unorm8tofloat(data_ptr[2]);
               ret.z = unorm8tofloat(data_ptr[3]);
               ret.w = unorm8tofloat(data_ptr[0]);

			   break;
           case CL_SIGNED_INT8:
			   {
              char * cdata_ptr = (char * )img->host_ptr;
                 ret.x = snorm8tofloat(cdata_ptr[1]);
                 ret.y = snorm8tofloat(cdata_ptr[2]);
                 ret.z = snorm8tofloat(cdata_ptr[3]);
                 ret.w = snorm8tofloat(cdata_ptr[0]);
			   }

               break;

	      case CL_UNSIGNED_INT16:
			  {
              unsigned short * ushort_ptr = (unsigned short * )data_ptr;
			     ret.x = unorm16tofloat(ushort_ptr[1]);
			     ret.y = unorm16tofloat(ushort_ptr[2]);
			     ret.z = unorm16tofloat(ushort_ptr[3]);
			     ret.w = unorm16tofloat(ushort_ptr[0]);

			  }
			  break;
     	  case CL_SIGNED_INT16:
			  {
              short * short_ptr = (short * )data_ptr;
			     ret.x = snorm16tofloat(short_ptr[1]);
			     ret.y = snorm16tofloat(short_ptr[2]);
			     ret.z = snorm16tofloat(short_ptr[3]);
			     ret.w = snorm16tofloat(short_ptr[0]);
			  }

              break;

	      case CL_FLOAT:
			  {
              float * float_ptr = (float * )data_ptr;
			     ret.x = float_ptr[1];
			     ret.y = float_ptr[2];
			     ret.z = float_ptr[3];
			     ret.w = float_ptr[0];


			  }
			  break;
      	  case CL_SIGNED_INT32:
	      case CL_UNSIGNED_INT32:
			  {
              uint * uint_ptr = (uint * )data_ptr;
			     ret.x = as_float(uint_ptr[1]);
			     ret.y = as_float(uint_ptr[2]);
			     ret.z = as_float(uint_ptr[3]);
			     ret.w = as_float(uint_ptr[0]);
			  }
			  break;



		}

		break;

       
   }

   return (ret);

}


static
void setFLOAT4(const ClImageArg * img, int _offset, float4 data)
{
int channel_order = img->image_format.image_channel_order;
int channel_data_type = img->image_format.image_channel_data_type;
unsigned char * data_ptr = (unsigned char * )img->host_ptr + _offset;
   switch(channel_order)
   {
	case CL_RGBA :
		switch(channel_data_type)
		{
	       case CL_UNSIGNED_INT8:
			   {
                 data_ptr[0] = float_tounorm8(data.x);
                 data_ptr[1] = float_tounorm8(data.y);
                 data_ptr[2] = float_tounorm8(data.z);
                 data_ptr[3] = float_tounorm8(data.w);
			   }
			   break;
          case CL_SIGNED_INT8:
			   {
              char * cdata_ptr = (char * )img->host_ptr;
                 cdata_ptr[0] = float_tosnorm8(data.x);
                 cdata_ptr[1] = float_tosnorm8(data.y);
                 cdata_ptr[2] = float_tosnorm8(data.z);
                 cdata_ptr[3] = float_tosnorm8(data.w);
			   }
			  break;
	      case CL_UNSIGNED_INT16:
			  {
              unsigned short * ushort_ptr = (unsigned short * )data_ptr;
			     ushort_ptr[0] = float_tounorm16(data.x);
			     ushort_ptr[1] = float_tounorm16(data.y);
			     ushort_ptr[2] = float_tounorm16(data.z);
			     ushort_ptr[3] = float_tounorm16(data.w);
			  }
			  break;
     	  case CL_SIGNED_INT16:
			  {
              short * short_ptr = (short * )data_ptr;
			     short_ptr[0] = float_tosnorm16(data.x);
			     short_ptr[1] = float_tosnorm16(data.y);
			     short_ptr[2] = float_tosnorm16(data.z);
			     short_ptr[3] = float_tosnorm16(data.w);
			  }

			  break;
		  case CL_FLOAT:
			  {
              float * flt_ptr = (float * )data_ptr;
			     flt_ptr[0] = data.x;
			     flt_ptr[1] = data.y;
			     flt_ptr[2] = data.z;
			     flt_ptr[3] = data.w;
			  }
			  break;
      	  case CL_SIGNED_INT32:
	      case CL_UNSIGNED_INT32:
			  {
              uint * uint_ptr = (uint * )data_ptr;
			     uint_ptr[0] = as_uint(data.x);
			     uint_ptr[1] = as_uint(data.y);
			     uint_ptr[2] = as_uint(data.z);
			     uint_ptr[3] = as_uint(data.w);
			  }
              break;
		}
		break;
	case CL_BGRA :
		switch(channel_data_type)
		{

	       case CL_UNSIGNED_INT8:
			   {
                 data_ptr[2] = float_tounorm8(data.x);
                 data_ptr[1] = float_tounorm8(data.y);
                 data_ptr[0] = float_tounorm8(data.z);
                 data_ptr[3] = float_tounorm8(data.w);
			   }
			   break;
          case CL_SIGNED_INT8:
			   {
              char * cdata_ptr = (char * )img->host_ptr;
                 cdata_ptr[2] = float_tosnorm8(data.x);
                 cdata_ptr[1] = float_tosnorm8(data.y);
                 cdata_ptr[0] = float_tosnorm8(data.z);
                 cdata_ptr[3] = float_tosnorm8(data.w);
			   }
			  break;
	      case CL_UNSIGNED_INT16:
			  {
              unsigned short * ushort_ptr = (unsigned short * )data_ptr;
			     ushort_ptr[2] = float_tounorm16(data.x);
			     ushort_ptr[1] = float_tounorm16(data.y);
			     ushort_ptr[0] = float_tounorm16(data.z);
			     ushort_ptr[3] = float_tounorm16(data.w);
			  }
			  break;
     	  case CL_SIGNED_INT16:
			  {
              short * short_ptr = (short * )data_ptr;
			     short_ptr[2] = float_tosnorm16(data.x);
			     short_ptr[1] = float_tosnorm16(data.y);
			     short_ptr[0] = float_tosnorm16(data.z);
			     short_ptr[3] = float_tosnorm16(data.w);
			  }

			  break;
		  case CL_FLOAT:
			  {
              float * flt_ptr = (float * )data_ptr;
			     flt_ptr[2] = data.x;
			     flt_ptr[1] = data.y;
			     flt_ptr[0] = data.z;
			     flt_ptr[3] = data.w;
			  }
			  break;
      	  case CL_SIGNED_INT32:
	      case CL_UNSIGNED_INT32:
			  {
              uint * uint_ptr = (uint * )data_ptr;
			     uint_ptr[2] = as_uint(data.x);
			     uint_ptr[1] = as_uint(data.y);
			     uint_ptr[0] = as_uint(data.z);
			     uint_ptr[3] = as_uint(data.w);
			  }
              break;

		}

		break;
	case CL_ARGB :
		switch(channel_data_type)
		{

	       case CL_UNSIGNED_INT8:
			   {
                 data_ptr[1] = float_tounorm8(data.x);
                 data_ptr[2] = float_tounorm8(data.y);
                 data_ptr[3] = float_tounorm8(data.z);
                 data_ptr[0] = float_tounorm8(data.w);
			   }
			   break;
          case CL_SIGNED_INT8:
			   {
              char * cdata_ptr = (char * )img->host_ptr;
                 cdata_ptr[1] = float_tosnorm8(data.x);
                 cdata_ptr[2] = float_tosnorm8(data.y);
                 cdata_ptr[3] = float_tosnorm8(data.z);
                 cdata_ptr[0] = float_tosnorm8(data.w);
			   }
			  break;
	      case CL_UNSIGNED_INT16:
			  {
              unsigned short * ushort_ptr = (unsigned short * )data_ptr;
			     ushort_ptr[1] = float_tounorm16(data.x);
			     ushort_ptr[2] = float_tounorm16(data.y);
			     ushort_ptr[3] = float_tounorm16(data.z);
			     ushort_ptr[0] = float_tounorm16(data.w);
			  }
			  break;
     	  case CL_SIGNED_INT16:
			  {
              short * short_ptr = (short * )data_ptr;
			     short_ptr[1] = float_tosnorm16(data.x);
			     short_ptr[2] = float_tosnorm16(data.y);
			     short_ptr[3] = float_tosnorm16(data.z);
			     short_ptr[0] = float_tosnorm16(data.w);
			  }

			  break;
		  case CL_FLOAT:
			  {
              float * flt_ptr = (float * )data_ptr;
			     flt_ptr[1] = data.x;
			     flt_ptr[2] = data.y;
			     flt_ptr[3] = data.z;
			     flt_ptr[0] = data.w;
			  }
			  break;
      	  case CL_SIGNED_INT32:
	      case CL_UNSIGNED_INT32:
			  {
              uint * uint_ptr = (uint * )data_ptr;
			     uint_ptr[1] = as_uint(data.x);
			     uint_ptr[2] = as_uint(data.y);
			     uint_ptr[3] = as_uint(data.z);
			     uint_ptr[0] = as_uint(data.w);
			  }
              break;

		}


		break;
       
   }


}



/**************************************************************************************
 IMAGE
**************************************************************************************/


float4 read_imagef (image2d_t image,
                    sampler_t sampler,
                    int2 coord)
{
float4 ret = 0;
const ClImageArg * img = (const ClImageArg*)image;
int offset = 0;
int clamp;
//     if ( sampler & CLK_NORMALIZED_COORDS_FALSE )
	 {
		 ComputeByteOffsetUnnrmCoord2(&offset, &clamp, img, coord);
	 }

    ret = getFLOAT4(img, offset);
	 if ((sampler & CLK_ADDRESS_CLAMP) && clamp)
	 {
		 ret = (float4)0;
	 }
    return(ret);
}

float4 read_imagef (image2d_t image,
                    sampler_t sampler,
                    float2 coord)
{
float4 ret = 0;
const ClImageArg * img = (const ClImageArg*)image;

int2 int_coord;    
     int_coord.x = (int)(coord.x * img->image_width);
     int_coord.y = (int)(coord.y * img->image_height);
	 ret = read_imagef (image,
                         sampler,
                         int_coord);

    return(ret);
}

int4 read_imagei (image2d_t image,
                  sampler_t sampler,
                  int2 coord)
{
int4 ret = 0;
const ClImageArg * img = (const ClImageArg*)image;
int offset = 0;
int clamp;
//     if ( sampler & CLK_NORMALIZED_COORDS_FALSE )
	 {
		 ComputeByteOffsetUnnrmCoord2(&offset, &clamp, img, coord);
	 }
	 ret = getINT4(img, offset);
	 if ((sampler & CLK_ADDRESS_CLAMP) && clamp)
	 {
		 ret = (int4)0;
	 }

     return(ret);
}

int4 read_imagei (image2d_t image,
                  sampler_t sampler,
                  float2 coord)
{
int4 ret = 0;
const ClImageArg * img = (const ClImageArg*)image;
int2 int_coord;    
     int_coord.x = (int)(coord.x * img->image_width);
     int_coord.y = (int)(coord.y * img->image_height);
	 ret = read_imagei (image,
                         sampler,
                         int_coord);

     return(ret);
}

uint4 read_imageui (image2d_t image,
                    sampler_t sampler,
                    int2 coord)
{
uint4 ret = 0;
const ClImageArg * img = (const ClImageArg*)image;
int offset = 0;
int clamp;
//     if ( sampler & CLK_NORMALIZED_COORDS_FALSE )
	 {
		 ComputeByteOffsetUnnrmCoord2(&offset, &clamp, img, coord);
	 }
	 ret = getUINT4(img, offset);
	 if ((sampler & CLK_ADDRESS_CLAMP) && clamp)
	 {
		 ret = (uint4)0;
	 }

     return(ret);
}

uint4 read_imageui (image2d_t image,
                    sampler_t sampler,
                    float2 coord)
{
uint4 ret = 0;
ClImageArg * img = (ClImageArg*)image;
int2 int_coord;
      
     int_coord.x = (int)(coord.x * img->image_width);
     int_coord.y = (int)(coord.y * img->image_height);
	 ret = read_imageui (image,
                         sampler,
                         int_coord);

     return(ret);
}

void write_imagef (image2d_t image,
                   int2 coord,
                   float4 color)
{
ClImageArg * img = (ClImageArg*)image;
int offset = 0;
int clamp;

     ComputeByteOffsetUnnrmCoord2(&offset, &clamp, img, coord, 0);
	 setFLOAT4(img, offset, color);
}

void write_imagei (image2d_t image,
                   int2 coord,
                   int4 color)
{
ClImageArg * img = (ClImageArg*)image;
int offset = 0;
int clamp;

     ComputeByteOffsetUnnrmCoord2(&offset, &clamp, img, coord, 0);
	 setINT4(img, offset, color);

}

void write_imageui (image2d_t image,
                    int2 coord,
                    uint4 color)
{
const ClImageArg * img = (const ClImageArg*)image;
int offset = 0;
int clamp;

     ComputeByteOffsetUnnrmCoord2(&offset, &clamp, img, coord, 0);
	 setUINT4(img, offset, color);

}

float4 read_imagef (image3d_t image,
                    sampler_t sampler,
                    int4 coord )
{
float4 ret = 0;
ClImageArg * img = (ClImageArg*)image;
    return(ret);
}

float4 read_imagef (image3d_t image,
                    sampler_t sampler,
                    float4 coord)
{
float4 ret = 0;
ClImageArg * img = (ClImageArg*)image;
    return(ret);
}

int4 read_imagei (image3d_t image,
                  sampler_t sampler,
                  int4 coord)
{
int4 ret = 0;
ClImageArg * img = (ClImageArg*)image;
     return(ret);
}

int4 read_imagei (image3d_t image,
                   sampler_t sampler,
                   float4 coord)
{
int4 ret = 0;
ClImageArg * img = (ClImageArg*)image;
     return(ret);
}

uint4 read_imageui (image3d_t image,
                    sampler_t sampler,
                    int4 coord)
{
uint4 ret = 0;
ClImageArg * img = (ClImageArg*)image;
     return(ret);
}

uint4 read_imageui (image3d_t image,
                     sampler_t sampler,
                     float4 coord)
{
uint4 ret = 0;
ClImageArg * img = (ClImageArg*)image;
     return(ret);
}

