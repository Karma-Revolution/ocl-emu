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


//-----------------------------------------------------------------------------
// File: clemu_cltypes_intrinsics
//
// Desc: Modeling cl constructs in C++.
//
//-----------------------------------------------------------------------------

#ifndef _CL_EMU_CLTYPES_INTRISICS_H_
#define _CL_EMU_CLTYPES_INTRISICS_H_


#ifndef NOMINMAX
#define NOMINMAX
#endif
//#include <Winbase.h>
#include "runCL.h"
#include "runCLintnl.hpp"

typedef unsigned int cl_mem_fence_flags; 
typedef unsigned int size_t; 
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef VOID 
(__stdcall *KERNEL_ENTRY_POINT) ( LPVOID lpParameter );
typedef unsigned int sampler_t;

// CROSS_COMPILER

#define CLK_LOCAL_MEM_FENCE  0
#define CLK_GLOBAL_MEM_FENCE 1

// image
// coord
#define CLK_NORMALIZED_COORDS_FALSE (1 << 0)
#define CLK_NORMALIZED_COORDS_TRUE  (1 << 1)

// clamp
#define CLK_ADDRESS_NONE            (1 << 2)
#define CLK_ADDRESS_CLAMP           (1 << 3)
#define CLK_ADDRESS_CLAMP_TO_EDGE   (1 << 4)
#define CLK_ADDRESS_REPEAT          (1 << 5)
#define CLK_ADDRESS_MIRRORED_REPEAT (1 << 6)
// filtering
#define CLK_FILTER_NEAREST          (1 << 7)
#define CLK_FILTER_LINEAR           (1 << 8)


#define __STATIC  static
#define __kernel
#define constant static
#define __constant const
#define global
#define __global global
#define local
#define __local local
#define private
#define __private
#define __read_only
#define __write_only
#define __CONST
#define __LONG __int64
#define __ULONG unsigned __int64
#define __CL_LONG __int64
#define __CL_ULONG unsigned __int64
#define __DebugStatement( _ARG_ ) _ARG_
#define __DebugBarrier( _ARG_ ) barrier(_ARG_)
#define __SWBarrier( _ARG_ ) barrier(_ARG_)
#define __MAX( a, b ) clemu_max((a),(b))
#define __MIN( a, b ) clemu_min((a),(b))


#include "clemu_intnl.hpp"
#include "clemu_runtime.hpp"
#include "clemu_vtypes_intrinsics.h"





#define CL_KERNEL(NAME)\
static int kernel_id_##NAME; \
static VOID __stdcall clemu_##NAME ( LPVOID  ); \
static clemuKernelEntryPointHelper clemuKernelEntryPointHelper_##NAME(kernel_id_##NAME, __FILE__, #NAME, clemu_##NAME); \
VOID __stdcall  clemu_##NAME(LPVOID)\
{\
int kernel_id_internal = kernel_id_##NAME; \
int clemu_argCnt = 0; \
int clemu_localAccumSz = 0; \
CL_EMU_FIBER *clemu_Fiber = (CL_EMU_FIBER *)GetFiberData(); \
clemuKernelGroup * clemu_group = (clemuKernelGroup * )clemu_Fiber->m_group_ptr; \
char clemu_type_id[256];\
int clemu_type_id_len;



#define CL_GETARG(_TYPE_, NAME) \
_TYPE_ NAME; \
{\
	void* clemu_arg_ptr; \
	unsigned int arg_flags; \
    strcpy_s(clemu_type_id, 256, typeid(NAME).name());\
	clemu_type_id_len = (int)strlen(clemu_type_id); \
	clemu_arg_ptr = clemu_group->GerArg(clemu_argCnt)->arg_ptr;\
	arg_flags = clemu_group->GerArg(clemu_argCnt)->m_flags;\
    if ( clemu_type_id[clemu_type_id_len-1] == '>') \
    {\
char dim[16]; \
char type_nm[64]; \
int idim; \
int emu_c,emu_c2; \
         for(emu_c = clemu_type_id_len-1; emu_c >= 0 && clemu_type_id[emu_c] != ','; emu_c--); \
		 memcpy(dim,&clemu_type_id[emu_c+1],clemu_type_id_len-emu_c-2); \
		 dim[clemu_type_id_len-emu_c-2] = 0; \
		 sscanf_s(dim, "%d", &idim); \
         clemu_type_id[emu_c] = 0; \
         for(emu_c2 = emu_c-1; emu_c2 >= 0 && clemu_type_id[emu_c2] != '<'; emu_c2--); \
		 strcpy_s(type_nm,64, &clemu_type_id[emu_c2 + 1]); \
		 if(!strcmp(type_nm, "float")) \
         {\
			 memcpy(&NAME, &clemu_group->GerArg(clemu_argCnt)->m_arg.v_farg16[0],idim*sizeof(float));\
         }\
		 else if(!strcmp(type_nm, "double")) \
         {\
			 memcpy(&NAME, &clemu_group->GerArg(clemu_argCnt)->m_arg.v_darg16[0],idim*sizeof(double));\
         }\
	     else if(!strcmp(type_nm, "int") || !strcmp(type_nm, "unsigned int")) \
         {\
			 memcpy(&NAME, &clemu_group->GerArg(clemu_argCnt)->m_arg.v_iarg16[0],idim*sizeof(unsigned int));\
         }\
	     else if(!strcmp(type_nm, "__int64") || !strcmp(type_nm, "unsigned __int64")) \
         {\
			 memcpy(&NAME, &clemu_group->GerArg(clemu_argCnt)->m_arg.v_iarg16[0],idim*sizeof(unsigned __int64));\
         }\
    }\
	else if(arg_flags & CL_ARG_IMAGE) \
    {\
	     NAME = *(_TYPE_*)&clemu_arg_ptr; \
    }\
	else \
	{ \
       NAME = *(_TYPE_ *)&clemu_group->GerArg(clemu_argCnt)->m_arg.iarg; \
	} \
}\
clemu_argCnt++;



#define CL_RETURN \
}




/*
// DebugBreak();

#define CL_GETARG_FIRST(_TYPE_, NAME) \
_TYPE_ NAME; \
{\
    strcpy_s(clemu_glbl_type_id, 256, typeid(NAME).name());\
    strcpy_s(clemu_type_id, 256, typeid(NAME).name());\
	clemu_type_id_len = strlen(clemu_type_id); \
    if ( clemu_type_id[clemu_type_id_len-1] == '*') \
	{ \
       NAME = *(_TYPE_ *)&clemu_group->GerArg(clemu_argCnt)->m_arg.parg; \
	} \
	else if(!strcmp(clemu_type_id, "float")) \
	{ \
		NAME = *(_TYPE_ *)&clemu_group->GerArg(clemu_argCnt)->m_arg.farg; \
	} \
	else if(!strcmp(clemu_type_id, "double")) \
	{ \
		NAME = *(_TYPE_ *)&clemu_group->GerArg(clemu_argCnt)->m_arg.darg; \
	} \
	else if(!strcmp(clemu_type_id, "int") || !strcmp(clemu_type_id, "unsigned int")) \
	{ \
		NAME = *(_TYPE_ *)&clemu_group->GerArg(clemu_argCnt)->m_arg.iarg; \
	}\
}\
clemu_argCnt++;
*/

#define CL_LOCAL_ARR(_TYPE_, _NAME_, _SIZE_) \
_TYPE_ * _NAME_ = (_TYPE_ *)((unsigned char*)clemu_group->GetLclMemPtr() + clemu_localAccumSz); \
clemu_localAccumSz += _SIZE_ * sizeof(_TYPE_); \
GetRunTime()->SetCompiledKernelLocalMemSz(kernel_id_internal, clemu_localAccumSz);



#define __Kernel CL_KERNEL
#define __KernelGrpSz2(NAME, GROUP_SZ1, GROUP_SZ2) CL_KERNEL(NAME)
#define __KernelGrpSz1(NAME, GROUP_SZ1) CL_KERNEL(NAME)
#define __Arg CL_GETARG
#define __ArgLast CL_GETARG
#define __ArgFirst CL_GETARG
#define __Return CL_RETURN
#define __Local CL_LOCAL_ARR
#define __ArgNULL





class clemuKernelEntryPointHelper {
public:
   clemuKernelEntryPointHelper(int & _kernel_id, char *_program, char *_name, KERNEL_ENTRY_POINT _entry)
   {
	   _kernel_id = GetRunTime()->AddCompiledKernel(_program, _name, _entry);
   }
};

class clemuKernelLocalMemHelper {
public:
   clemuKernelLocalMemHelper(int _kernel_id, int _local_mem_sz)
   {
	   GetRunTime()->SetCompiledKernelLocalMemSz(_kernel_id, _local_mem_sz);
   }
};



/*************************************************************************************
// intrinsics
*************************************************************************************/
//Returns the number of dimensions in use.
static uint get_work_dim ()
{
uint ret = 0;
CL_EMU_FIBER *pFiber = (CL_EMU_FIBER *)GetFiberData();
clemuKernelGroup * group = (clemuKernelGroup * )pFiber->m_group_ptr;
clemuKernelJob *job = (clemuKernelJob *)(group->GetParent());
   ret = job->GetNmbrDim();
   return(ret);
}
//Returns the number of global work-items
//specified for dimension identified by dimindx.
static size_t get_global_size (uint dimindx)
{
size_t ret = 0;
CL_EMU_FIBER *pFiber = (CL_EMU_FIBER *)GetFiberData();
clemuKernelGroup * group = (clemuKernelGroup * )pFiber->m_group_ptr;
clemuKernelJob *job = (clemuKernelJob *)(group->GetParent());
   ret = job->GetDomainSz(dimindx);
   return(ret);
}
//Returns the unique global work-item ID value
//for dimension identified by dimindx.
static size_t get_global_id (uint dimindx)
{
size_t ret = 0;
CL_EMU_FIBER *pFiber = (CL_EMU_FIBER *)GetFiberData();
clemuKernelGroup * group = (clemuKernelGroup * )pFiber->m_group_ptr;
clemuKernelJob *job = (clemuKernelJob *)(group->GetParent());
int grp_coord;
int t_coord;

   if ((int)dimindx >= 0 && (int)dimindx <= job->GetNmbrDim() - 1)
   {
      grp_coord = group->GetGrpCoord((int)dimindx);
	  t_coord = (dimindx == 0)? pFiber->m_grp_tid%job->GetGroupSz(0) : pFiber->m_grp_tid/job->GetGroupSz(0);
	  ret = grp_coord * job->GetGroupSz(dimindx) + t_coord;
   }

   return(ret);
}
//Returns the number of local work-items
//specified in dimension identified by dimindx.
static size_t get_local_size (uint dimindx)
{
size_t ret = 0;
CL_EMU_FIBER *pFiber = (CL_EMU_FIBER *)GetFiberData();
clemuKernelGroup * group = (clemuKernelGroup * )pFiber->m_group_ptr;
clemuKernelJob *job = (clemuKernelJob *)(group->GetParent());
   ret = job->GetGroupSz(dimindx);
   return(ret);
}
//Returns the unique local work-item ID i.e. a
//work-item within a specific work-group for
//dimension identified by dimindx.
static size_t get_local_id (uint dimindx)
{
size_t ret = 0;
CL_EMU_FIBER *pFiber = (CL_EMU_FIBER *)GetFiberData();
clemuKernelGroup * group = (clemuKernelGroup * )pFiber->m_group_ptr;
clemuKernelJob *job = (clemuKernelJob *)(group->GetParent());
int insts;
   if ((int)dimindx >= 0 && (int)dimindx <= job->GetNmbrDim() - 1)
   {
      insts = pFiber->m_grp_tid;
      ret = (dimindx == 0)? insts%job->GetGroupSz(0) : insts/job->GetGroupSz(0);
   }
   return(ret);
}
//Returns the number of work-groups that will
//execute a kernel for dimension identified by
//dimindx.
static size_t get_num_groups (uint dimindx)
{
size_t ret = 0;
CL_EMU_FIBER *pFiber = (CL_EMU_FIBER *)GetFiberData();
clemuKernelGroup * group = (clemuKernelGroup * )pFiber->m_group_ptr;
clemuKernelJob *job = (clemuKernelJob *)(group->GetParent());
   ret = job->GetNbrGroupSz((int)dimindx);
   return(ret);
}
//returns the work-group ID
//which is a number from 0 ..
//get_num_groups(dimindx) – 1.
static size_t get_group_id (uint dimindx)
{
size_t ret = 0;
CL_EMU_FIBER *pFiber = (CL_EMU_FIBER *)GetFiberData();
clemuKernelGroup * group = (clemuKernelGroup * )pFiber->m_group_ptr;
//clemuKernelJob *job = (clemuKernelJob *)(group->GetParent());
   ret = group->GetGrpCoord((int)dimindx);
   return(ret);
}
//All work-items in a work-group executing the kernel
//on a processor must execute this function before any
//are allowed to continue execution beyond the barrier.
static void barrier (cl_mem_fence_flags flags = 0)
{
   clemu_ScheduleGrpThread();
}

static void mem_fence (cl_mem_fence_flags flags = 0)
{
   clemu_ScheduleGrpThread();
}

static void read_mem_fence (cl_mem_fence_flags flags = 0)
{
   clemu_ScheduleGrpThread();
}

static void write_mem_fence (cl_mem_fence_flags flags = 0)
{
   clemu_ScheduleGrpThread();
}



// ATOMIC
#define CAL_EMU_MIN(a, b) ((a) <= (b)) ? (a) : (b)
#define CAL_EMU_MAX(a, b) ((a) >= (b)) ? (a) : (b)

static int atom_add(int *_old_ptr, int _val)
{
int ret;

    ret = (*_old_ptr);
    *_old_ptr += _val;
//	clemu_ScheduleGrpThread();
	return(ret);
}

static uint atom_add(uint *_old_ptr, uint _val)
{
uint ret;
    ret = *_old_ptr;
    *_old_ptr += _val;
//	clemu_ScheduleGrpThread();
	return(ret);
}
static int atom_sub(int *_old_ptr, int _val)
{
int ret = *_old_ptr;
    *_old_ptr -= _val;
//	clemu_ScheduleGrpThread();
	return(ret);
}
static uint atom_sub(uint *_old_ptr, uint _val)
{
uint ret = *_old_ptr;
    *_old_ptr -= _val;
	clemu_ScheduleGrpThread();
	return(ret);
}

static int atom_xchg(int *_old_ptr, int _val)
{
int ret = *_old_ptr;
    *_old_ptr = _val;
//	clemu_ScheduleGrpThread();
	return(ret);
}

static uint atom_xchg(uint *_old_ptr, uint _val)
{
uint ret = *_old_ptr;
    *_old_ptr = _val;
//	clemu_ScheduleGrpThread();
	return(ret);
}
static float atom_xchg(float *_old_ptr, float _val)
{
float ret = *_old_ptr;
    *_old_ptr = _val;
//	clemu_ScheduleGrpThread();
	return(ret);
}

static int atom_cmpxchg(int *_old_ptr, int _cmp, int _val)
{
int ret;
    ret = (*_old_ptr == _cmp) ? *_old_ptr : _val ;
	*_old_ptr = (*_old_ptr == _cmp) ? _val : *_old_ptr;
//	clemu_ScheduleGrpThread();
	return(ret);
}

static uint atom_cmpxchg(uint *_old_ptr, uint _cmp, uint _val)
{
uint ret;
    ret = (*_old_ptr == _cmp) ? *_old_ptr : _val ;
	*_old_ptr = (*_old_ptr == _cmp) ? _val : *_old_ptr;
//	clemu_ScheduleGrpThread();
	return(ret);
}

static int atom_min(int *_old_ptr, int _val)
{
int ret = *_old_ptr;
    *_old_ptr = CAL_EMU_MIN(*_old_ptr, _val);
//	clemu_ScheduleGrpThread();
	return(ret);
}
static uint atom_min(uint *_old_ptr, uint _val)
{
uint ret = *_old_ptr;
    *_old_ptr = CAL_EMU_MIN(*_old_ptr, _val);
//	clemu_ScheduleGrpThread();
	return(ret);
}
static int atom_max(int *_old_ptr, int _val)
{
int ret = *_old_ptr;
    *_old_ptr = CAL_EMU_MAX(*_old_ptr, _val);
//	clemu_ScheduleGrpThread();
	return(ret);
}
static uint atom_max(uint *_old_ptr, uint _val)
{
uint ret = *_old_ptr;
    *_old_ptr = CAL_EMU_MAX(*_old_ptr, _val);
//	clemu_ScheduleGrpThread();
	return(ret);
}

static int atom_and(int *_old_ptr, int _val)
{
int ret = *_old_ptr;
    *_old_ptr &= _val;
//	clemu_ScheduleGrpThread();
	return(ret);
}
static uint atom_and(uint *_old_ptr, uint _val)
{
uint ret = *_old_ptr;
    *_old_ptr &= _val;
//	clemu_ScheduleGrpThread();
	return(ret);
}

static int atom_or(int *_old_ptr, int _val)
{
int ret = *_old_ptr;
    *_old_ptr |= _val;
//	clemu_ScheduleGrpThread();
	return(ret);
}
static uint atom_or(uint *_old_ptr, uint _val)
{
uint ret = *_old_ptr;
    *_old_ptr |= _val;
//	clemu_ScheduleGrpThread();
	return(ret);
}
static int atom_xor(int *_old_ptr, int _val)
{
int ret = *_old_ptr;
    *_old_ptr ^= _val;
//	clemu_ScheduleGrpThread();
	return(ret);
}
static uint atom_xor(uint *_old_ptr, uint _val)
{
uint ret = *_old_ptr;
    *_old_ptr ^= _val;
//	clemu_ScheduleGrpThread();
	return(ret);
}


/**************************************************************************************
 IMAGE
**************************************************************************************/

typedef ClImage2D* image2d_t;
typedef ClImageArg* image3d_t;


float4 read_imagef (image2d_t image,
                    sampler_t sampler,
                    int2 coord);

float4 read_imagef (image2d_t image,
                    sampler_t sampler,
                    float2 coord);

int4 read_imagei (image2d_t image,
                  sampler_t sampler,
                  int2 coord);

int4 read_imagei (image2d_t image,
                  sampler_t sampler,
                  float2 coord);
uint4 read_imageui (image2d_t image,
                    sampler_t sampler,
                    int2 coord);
uint4 read_imageui (image2d_t image,
                    sampler_t sampler,
                    float2 coord);
void write_imagef (image2d_t image,
                   int2 coord,
                   float4 color);
void write_imagei (image2d_t image,
                   int2 coord,
                   int4 color);
void write_imageui (image2d_t image,
                    int2 coord,
                    uint4 color);
float4 read_imagef (image3d_t image,
                    sampler_t sampler,
                    int4 coord );
float4 read_imagef (image3d_t image,
                    sampler_t sampler,
                    float4 coord);
int4 read_imagei (image3d_t image,
                  sampler_t sampler,
                  int4 coord);
int4 read_imagei (image3d_t image,
                   sampler_t sampler,
                   float4 coord);
uint4 read_imageui (image3d_t image,
                    sampler_t sampler,
                    int4 coord);
uint4 read_imageui (image3d_t image,
                     sampler_t sampler,
                     float4 coord);

inline int get_image_width (image2d_t image)
{
const ClImageArg * img = (const ClImageArg*)image;
    return (img->image_width);
}

inline int get_image_width (image3d_t image)
{
const ClImageArg * img = (const ClImageArg*)image;
    return (img->image_width);
}


inline int get_image_height (image2d_t image)
{
const ClImageArg * img = (const ClImageArg*)image;
    return (img->image_height);
}

inline int get_image_height (image3d_t image)
{
const ClImageArg * img = (const ClImageArg*)image;
    return (img->image_height);
}

inline int get_image_depth (image3d_t image)
{
const ClImageArg * img = (const ClImageArg*)image;
    return (img->image_depth);
}

inline int get_image_channel_data_type (image2d_t image)
{
const ClImageArg * img = (const ClImageArg*)image;
    return ((int)img->image_format.image_channel_data_type);
}

inline int get_image_channel_data_type (image3d_t image)
{
const ClImageArg * img = (const ClImageArg*)image;
    return ((int)img->image_format.image_channel_data_type);
}


inline int get_image_channel_order (image2d_t image)
{
const ClImageArg * img = (const ClImageArg*)image;
    return ((int)img->image_format.image_channel_order);
}

inline int get_image_channel_order (image3d_t image)
{
const ClImageArg * img = (const ClImageArg*)image;
    return ((int)img->image_format.image_channel_order);
}


inline int2 get_image_dim (image2d_t image) 
{
int2 ret;
const ClImageArg * img = (const ClImageArg*)image;

    ret.x = img->image_width;
    ret.y = img->image_height;
	return(ret);
}

inline int4 get_image_dim (image3d_t image)
{
int4 ret;
const ClImageArg * img = (const ClImageArg*)image;

    ret.x = img->image_width;
    ret.y = img->image_height;
    ret.z = img->image_depth;
	return(ret);
}

#endif