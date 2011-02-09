
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
// File: clemu_opencl.h
//
// Desc: Converting C++ model into OpenCl.
//
// * Copyright (c) 2010 Advanced Micro Devices, Inc. (unpublished). 
// * All rights reserved.
//-----------------------------------------------------------------------------

#ifndef _CLEMU_OPENCL_H_
#define _CLEMU_OPENCL_H_



#ifdef  _GPU_EMU_IMPL

#include "clemu_cltypes_intrinsics.h"

#else

#define __STATIC
#define __CONST const
#define __KernelGrpSz2(NAME, GROUP_SZ1, GROUP_SZ2) __kernel __attribute__((reqd_work_group_size( GROUP_SZ1 , GROUP_SZ2 , 1))) void NAME
#define __KernelGrpSz1(NAME, GROUP_SZ1) __kernel __attribute__((reqd_work_group_size( GROUP_SZ1 , 1, 1))) void NAME
#define __Kernel(NAME) __kernel void NAME
#define __ArgFirst(TYPE, NAME) ( TYPE NAME,
#define __Arg(TYPE, NAME) TYPE NAME,
#define __ArgLast(TYPE, NAME) TYPE NAME )
#define __ArgNULL ()
#define __Return
#define __Local(TYPE, NAME, SIZE) __local TYPE NAME[SIZE]
#define __DebugBarrier( _ARG_ )
#define __LONG long
#define __ULONG unsigned long
#define __CL_LONG long
#define __CL_ULONG unsigned long
#define __DebugStatement( _ARG_ )
#if CPU_IMPL
#define __SWBarrier( _ARG_ ) barrier( _ARG_ )
#endif
#if GPU_IMPL
#define __SWBarrier( _ARG_ )
#endif
#define __MAX( a, b ) max((a),(b))
#define __MIN( a, b ) min((a),(b))




//#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#if GPU_IMPL
#pragma OPENCL EXTENSION cl_amd_media_ops : enable
#endif

#if CPU_IMPL
__STATIC
uint amd_bitalign (uint src0, uint src1, uint src2)
{
  return((uint) (((((__LONG)src0) << 32) | (__LONG)src1) >> (src2 & 31)));
}
__STATIC
uint amd_bytealign (uint src0, uint src1, uint src2)
{
   return((uint) (((((__LONG)src0) << 32) | (__LONG)src1) >> ((src2 & 3)*8)));
}

#endif

#pragma OPENCL EXTENSION cl_amd_printf : enable
#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable 
#pragma OPENCL EXTENSION cl_khr_global_int32_extended_atomics  : enable
#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable 
#pragma OPENCL EXTENSION cl_khr_local_int32_base_atomics : enable 
#pragma OPENCL EXTENSION cl_khr_local_int32_extended_atomics  : enable


#endif // _GPU_EMU_IMPL


#endif // _CLEMU_OPENCL_H_