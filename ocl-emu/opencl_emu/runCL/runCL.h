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
