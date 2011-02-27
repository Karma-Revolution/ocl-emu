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


#ifndef RUNCL_H_
#define RUNCL_H_

#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#ifdef __cplusplus
#include <CL/cl.hpp>
#endif

#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//EXTERNAL

#define CL_CALL_SUCCESS                  0
#define CL_CALL_FAILURE                  -1

#define CL_ARG_LAST                 0x80000000
#define CL_ARG_VALUE                0x10000
#define CL_ARG_LCL_MEM_SZ           0x20000
#define CL_ARG_BUFFER               0x40000
#define CL_ARG_IMAGE                0x80000

#ifndef CL_MEM_READ_WRITE
#define CL_MEM_READ_WRITE                           (1 << 0)
#define CL_MEM_WRITE_ONLY                           (1 << 1)
#define CL_MEM_READ_ONLY                            (1 << 2)
#endif

#define CL_ARG_INPUTOUTPUT_PTR      CL_MEM_READ_WRITE
#define CL_ARG_OUTPUT_PTR           CL_MEM_WRITE_ONLY
#define CL_ARG_INPUT_PTR            CL_MEM_READ_ONLY
#define CL_ARG_POPULATE_PTR         0x100000
#define CL_ARG_POPULATE             CL_ARG_POPULATE_PTR
//#define CL_ARG_DEVICE_PARAM         0x800000

#ifndef CL_SUCCESS

typedef unsigned int        cl_uint;
typedef cl_uint             cl_channel_order;
typedef cl_uint             cl_channel_type;

typedef struct _cl_image_format {
    cl_channel_order        image_channel_order;
    cl_channel_type         image_channel_data_type;
} cl_image_format;

/* cl_channel_order */
#define CL_R                                        0x10B0
#define CL_A                                        0x10B1
#define CL_RG                                       0x10B2
#define CL_RA                                       0x10B3
#define CL_RGB                                      0x10B4
#define CL_RGBA                                     0x10B5
#define CL_BGRA                                     0x10B6
#define CL_ARGB                                     0x10B7
#define CL_INTENSITY                                0x10B8
#define CL_LUMINANCE                                0x10B9
#define CL_Rx                                       0x10BA
#define CL_RGx                                      0x10BB
#define CL_RGBx                                     0x10BC

/* cl_channel_type */
#define CL_SNORM_INT8                               0x10D0
#define CL_SNORM_INT16                              0x10D1
#define CL_UNORM_INT8                               0x10D2
#define CL_UNORM_INT16                              0x10D3
#define CL_UNORM_SHORT_565                          0x10D4
#define CL_UNORM_SHORT_555                          0x10D5
#define CL_UNORM_INT_101010                         0x10D6
#define CL_SIGNED_INT8                              0x10D7
#define CL_SIGNED_INT16                             0x10D8
#define CL_SIGNED_INT32                             0x10D9
#define CL_UNSIGNED_INT8                            0x10DA
#define CL_UNSIGNED_INT16                           0x10DB
#define CL_UNSIGNED_INT32                           0x10DC
#define CL_HALF_FLOAT                               0x10DD
#define CL_FLOAT                                    0x10DE
#endif


#define _MAX_PROGRAM_NAME 512
#define _MAX_KERNEL_NAME 256

#define CL_DEVICE_CPU                   0
#define CL_DEVICE_GPU                   1
static const char * sDeviceName[] = {"cpu", "gpu"};


#define SET_CL_ARG_FIRST(arg)\
{ \
int set_cl_arg_counter = 0; 
#define SET_CL_ARG_PTR(arg, flags, size, ptr)\
	arg[set_cl_arg_counter].m_flags = CL_ARG_BUFFER | (flags); \
	arg[set_cl_arg_counter].m_len = (size); \
	arg[set_cl_arg_counter].m_arg.parg = ptr; \
    set_cl_arg_counter++;

#define SET_CL_ARG_VALUE(arg, type, value)\
{\
type set_cl_arg_tmp = value;\
	arg[set_cl_arg_counter].m_flags = CL_ARG_VALUE; \
	arg[set_cl_arg_counter].m_len = sizeof(type); \
	memcpy(&arg[set_cl_arg_counter].m_arg.iarg, &set_cl_arg_tmp, arg[set_cl_arg_counter].m_len); \
}\
    set_cl_arg_counter++;

#define SET_CL_ARG_LCL_MEM(arg, size)\
	arg[set_cl_arg_counter].m_flags = CL_ARG_LCL_MEM_SZ; \
	arg[set_cl_arg_counter].m_len = (size); \
	arg[set_cl_arg_counter].m_arg.parg = 0; \
    set_cl_arg_counter++;

#define SET_CL_ARG_LAST(arg)\
	arg[set_cl_arg_counter-1].m_flags |= CL_ARG_LAST; \
}

#define _Arg(ARG_ARRAY, FLAGS, TYPE, VALUE, SIZE) \
{\
TYPE clcall_arg_tmp_value = (VALUE); \
unsigned int clcall_arg_tmp_flags = (FLAGS); \
int clcall_arg_tmp_size = (SIZE); \
int clcall_arg_tmp_value_size; \
	clcall_arg_tmp_flags |= ((clcall_arg_tmp_flags & CL_ARG_INPUT_PTR) && !(clcall_arg_tmp_flags & CL_ARG_IMAGE))? CL_ARG_BUFFER : 0;\
	clcall_arg_tmp_flags |= ((clcall_arg_tmp_flags & CL_ARG_OUTPUT_PTR) && !(clcall_arg_tmp_flags & CL_ARG_IMAGE))? CL_ARG_BUFFER : 0;\
	clcall_arg_tmp_flags |= ((clcall_arg_tmp_flags & CL_ARG_INPUTOUTPUT_PTR) && !(clcall_arg_tmp_flags & CL_ARG_IMAGE) )? CL_ARG_BUFFER : 0;\
    ARG_ARRAY[clcall_arg_counter].m_flags = clcall_arg_tmp_flags; \
	ARG_ARRAY[clcall_arg_counter].m_len = (((FLAGS) & CL_ARG_LCL_MEM_SZ) == CL_ARG_LCL_MEM_SZ)? *(int*)&clcall_arg_tmp_value : clcall_arg_tmp_size;\
    clcall_arg_tmp_value_size = ((clcall_arg_tmp_flags & CL_ARG_LCL_MEM_SZ) == CL_ARG_LCL_MEM_SZ)? sizeof(int) :  sizeof(TYPE); \
	memcpy(&ARG_ARRAY[clcall_arg_counter].m_arg.iarg, &clcall_arg_tmp_value, clcall_arg_tmp_value_size); \
	ARG_ARRAY[clcall_arg_counter].m_arg.parg = ((clcall_arg_tmp_flags & CL_ARG_LCL_MEM_SZ) == CL_ARG_LCL_MEM_SZ)? 0 : ARG_ARRAY[clcall_arg_counter].m_arg.parg; \
    ARG_ARRAY[clcall_arg_counter].arg_ptr = &ARG_ARRAY[clcall_arg_counter].m_arg.iarg; \
}\
clcall_arg_counter++;


#define _ArgFirst(ARG_ARRAY, FLAGS, TYPE, VALUE, SIZE) \
{ \
int clcall_arg_counter = 0;\
{\
TYPE clcall_arg_tmp_value = (VALUE); \
int clcall_arg_tmp_size = (SIZE); \
unsigned int clcall_arg_tmp_flags = (FLAGS); \
int clcall_arg_tmp_value_size; \
	clcall_arg_tmp_flags |= ((clcall_arg_tmp_flags & CL_ARG_INPUT_PTR) && !(clcall_arg_tmp_flags & CL_ARG_IMAGE))? CL_ARG_BUFFER : 0;\
	clcall_arg_tmp_flags |= ((clcall_arg_tmp_flags & CL_ARG_OUTPUT_PTR)&& !(clcall_arg_tmp_flags & CL_ARG_IMAGE))? CL_ARG_BUFFER : 0;\
	clcall_arg_tmp_flags |= ((clcall_arg_tmp_flags & CL_ARG_INPUTOUTPUT_PTR) && !(clcall_arg_tmp_flags & CL_ARG_IMAGE))? CL_ARG_BUFFER : 0;\
    ARG_ARRAY[clcall_arg_counter].m_flags = clcall_arg_tmp_flags; \
	ARG_ARRAY[clcall_arg_counter].m_len = (((FLAGS) & CL_ARG_LCL_MEM_SZ) == CL_ARG_LCL_MEM_SZ)? *(int*)&clcall_arg_tmp_value : clcall_arg_tmp_size;\
    clcall_arg_tmp_value_size = ((clcall_arg_tmp_flags & CL_ARG_LCL_MEM_SZ) == CL_ARG_LCL_MEM_SZ)? sizeof(int) :  sizeof(TYPE); \
	memcpy(&ARG_ARRAY[clcall_arg_counter].m_arg.iarg, &clcall_arg_tmp_value, clcall_arg_tmp_value_size); \
	ARG_ARRAY[clcall_arg_counter].m_arg.parg = ((clcall_arg_tmp_flags & CL_ARG_LCL_MEM_SZ) == CL_ARG_LCL_MEM_SZ)? 0 : ARG_ARRAY[clcall_arg_counter].m_arg.parg; \
    ARG_ARRAY[clcall_arg_counter].arg_ptr = &ARG_ARRAY[clcall_arg_counter].m_arg.iarg; \
}\
clcall_arg_counter++;

#define _ArgLast(ARG_ARRAY, FLAGS, TYPE, VALUE, SIZE) \
{\
TYPE clcall_arg_tmp_value = (VALUE); \
int clcall_arg_tmp_size = (SIZE); \
unsigned int clcall_arg_tmp_flags = (FLAGS) | CL_ARG_LAST; \
int clcall_arg_tmp_value_size; \
	clcall_arg_tmp_flags |= ((clcall_arg_tmp_flags & CL_ARG_INPUT_PTR) && !(clcall_arg_tmp_flags & CL_ARG_IMAGE) )? CL_ARG_BUFFER : 0;\
	clcall_arg_tmp_flags |= ((clcall_arg_tmp_flags & CL_ARG_OUTPUT_PTR) && !(clcall_arg_tmp_flags & CL_ARG_IMAGE))? CL_ARG_BUFFER : 0;\
	clcall_arg_tmp_flags |= ((clcall_arg_tmp_flags & CL_ARG_INPUTOUTPUT_PTR) && !(clcall_arg_tmp_flags & CL_ARG_IMAGE))? CL_ARG_BUFFER : 0;\
    ARG_ARRAY[clcall_arg_counter].m_flags = clcall_arg_tmp_flags; \
	ARG_ARRAY[clcall_arg_counter].m_len = (((FLAGS) & CL_ARG_LCL_MEM_SZ) == CL_ARG_LCL_MEM_SZ)? *(int*)&clcall_arg_tmp_value : clcall_arg_tmp_size;\
    clcall_arg_tmp_value_size = ((clcall_arg_tmp_flags & CL_ARG_LCL_MEM_SZ) == CL_ARG_LCL_MEM_SZ)? sizeof(int) :  sizeof(TYPE); \
	memcpy(&ARG_ARRAY[clcall_arg_counter].m_arg.iarg, &clcall_arg_tmp_value, clcall_arg_tmp_value_size); \
	ARG_ARRAY[clcall_arg_counter].m_arg.parg = ((clcall_arg_tmp_flags & CL_ARG_LCL_MEM_SZ) == CL_ARG_LCL_MEM_SZ)? 0 : ARG_ARRAY[clcall_arg_counter].m_arg.parg; \
    ARG_ARRAY[clcall_arg_counter].arg_ptr = &ARG_ARRAY[clcall_arg_counter].m_arg.iarg; \
}\
clcall_arg_counter++;\
}

#ifdef __cplusplus
extern "C" {
#endif

// the reason we have 2 structure is 
// a need to sparate 2d and 3d image calls
// by parameter type

typedef struct _ClImage2D {
   cl_uint flags;
   cl_image_format image_format;
   size_t image_width;
   size_t image_height;
   size_t image_row_pitch;
   void *host_ptr;
} ClImage2D;



typedef union _ClImageArg {
   ClImage2D mImg2D;
   struct {
   cl_uint flags;
   cl_image_format image_format;
   size_t image_width;
   size_t image_height;
   size_t image_row_pitch;
   void *host_ptr;
   size_t image_depth;
   size_t image_slice_pitch;
   };
} ClImageArg;




typedef struct _ClKrnlArg {
	unsigned int m_flags;
    int m_len;
	void * arg_ptr;
	union {
	  int iarg;
	  float farg;
	  double darg;
	  __int64 larg;
	  void * parg;
	  int v_iarg16[16];
	  float v_farg16[16];
	  double v_darg16[16];
	  __int64 v_larg16[16];
	  int v_iarg8[8];
	  float v_farg8[8];
	  double v_darg8[8];
	  __int64 v_larg8[8];
	  int v_iarg4[4];
	  float v_farg4[4];
	  double v_darg4[4];
	  __int64 v_larg4[4];
	  int v_iarg2[2];
	  float v_farg2[2];
	  double v_darg2[2];
	  __int64 v_larg2[2];
	  ClImageArg v_img;
	} m_arg;
} ClKrnlArg;



int callCL(const char * _device_type,
		   int _domainDim,
		   int _domain[],
		   int _group[],
		   const char * _program_location,
		   const char * _program,
		   const char*_kernel_entry_name,
		   ClKrnlArg* _args);

#ifdef __cplusplus
}
#endif



#endif // RUNCL_H_
