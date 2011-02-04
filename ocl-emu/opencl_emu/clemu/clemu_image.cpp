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

