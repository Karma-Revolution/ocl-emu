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

// clemu_runtime.cpp : 
//

#include "clemu_cltypes_intrinsics.h"

/*************************************************************************************
   RUNNABLE
*************************************************************************************/
#if 0
template< class T > T atom_add(T *_old_ptr, T _val)
{
T ret = *_old_ptr;
    *_old_ptr += _val;
	clemu_ScheduleWfThread();
	return(ret);
}
#endif


/*************************************************************************************
   RUN_TIME
*************************************************************************************/

static clemuRunTime* sRunTime = 0;
clemuRunTime* GetRunTime(void)
{
	if (!sRunTime)
	{
		sRunTime = new clemuRunTime;
        assert(sRunTime);
		sRunTime->initRunTime();
	}
	return(sRunTime);
}

KERNEL_ENTRY_POINT clemuFindCompiledKernel(const char *_program_location,
	                                       const char *_program_nm,
										   const char *_kernel)
{
KERNEL_ENTRY_POINT ret = 0;
int kernel_index = GetRunTime()->FindCompiledKernelIndex(_program_location,
														 _program_nm,
														 _kernel);
    assert(kernel_index != -1);
	ret = GetRunTime()->GeCompiledKernel(kernel_index);
    return(ret);
}

int clemuGetCompiledKernelMemSz(KERNEL_ENTRY_POINT _kernel)
{
int ret = 0;
int kernel_index = GetRunTime()->GetCompiledKernelByPtr(_kernel);
    assert(kernel_index != -1);
	ret = GetRunTime()->GetCompiledKernelLocalMemSz(kernel_index);
    return(ret);
}


/*************************************************************************************
   clemuRunTime
*************************************************************************************/

clemuRunTime :: clemuRunTime(void)
{
      m_nbr_kernels = 0;
      m_max_nbr_kernels = 0;
      m_compiled_kernels = 0;
      m_active_proc_devs = 0;
}

clemuRunTime :: ~clemuRunTime(void)
{
}

int 
clemuRunTime :: initRunTime(void)
{
int ret = CL_EMU_SUCCESS;

   memset(m_Devices, 0, _MAX_DEVICES * sizeof(clemuProcessingDevice *));

   if (!m_compiled_kernels )
   {
      m_nbr_kernels = 0;
      m_max_nbr_kernels = _INIT_NMBR_PROGRAMS * _INIT_NMBR_KERNELS;
      m_compiled_kernels = new clemuCompiledKernel[m_max_nbr_kernels];
      assert(m_compiled_kernels);
      memset(m_compiled_kernels, 0, sizeof(clemuCompiledKernel) * m_max_nbr_kernels);
   }
   return(ret);
}

int 
clemuRunTime :: cleanupRunTime(void)
{
int ret = CL_EMU_SUCCESS;
   for( int i = 0; i < m_active_proc_devs; i++)
   {
	   if (m_Devices[i] )
	   {
		   delete m_Devices[i];
		   m_Devices[i] = 0;
	   }
   }

   if ( m_compiled_kernels )
   {
	   delete [] m_compiled_kernels;
	   m_compiled_kernels = 0;
	   m_nbr_kernels = 0;
	   m_max_nbr_kernels = 0;
   }

   return(ret);
}

clemuProcessingDevice * 
clemuRunTime ::GetActiveDev(int _index)
{
      clemuProcessingDevice * ret = 0;
	     if ( _index >= 0 && (_index < m_active_proc_devs  -  1 || m_active_proc_devs == 0))
		 {
             m_Devices[_index] = new clemuGPU;
			 assert(m_Devices[_index]);
			 m_Devices[_index]->initDevice();

			 m_active_proc_devs++;
		 }
	     if ( _index >= 0 && _index < m_active_proc_devs)
		 {
			 ret = m_Devices[_index];
		 }
		 return (ret);
}


int 
clemuRunTime :: CompileKernel(
			   const char * _program,
		       const char*_kernel_entry_name
			   )
{
int ret = CL_EMU_SUCCESS;
   return(ret);
}

int 
clemuRunTime :: AddCompiledKernel(
			   const char * _program,
		       const char*_kernel_entry_name,
			   KERNEL_ENTRY_POINT _kernel
			   )
{
int ret = -1;
   if (_kernel_entry_name && _kernel && m_nbr_kernels < m_max_nbr_kernels)
   {
	   ret = m_nbr_kernels;
	   strcpy_s(m_compiled_kernels[m_nbr_kernels].m_kernel_name,_MAX_KERNEL_NAME,_kernel_entry_name);
//	   strcpy(m_compiled_kernels[m_nbr_kernels].m_program_loc,_program);
	   m_compiled_kernels[m_nbr_kernels].m_entry = _kernel;
	   m_nbr_kernels++;
   }
   return(ret);
}

int 
clemuRunTime :: FindCompiledKernelIndex(
               const char * _program_location,
			   const char * _program_nm,
		       const char*_kernel_entry_name
			   )
{
int ret = -1;
//  if ( _program && _kernel_entry_name )

  if ( _kernel_entry_name )
  {
       for( int i = 0; i < m_nbr_kernels; i++)
	   {
//	    	if (!strcmp(_program,m_compiled_kernels[i].m_program_loc) && !strcmp(_kernel_entry_name,m_compiled_kernels[i].m_kernel_name))
	    	if (!strcmp(_kernel_entry_name,m_compiled_kernels[i].m_kernel_name))
			{
				ret = i;
				break;
			}
	   }
  }
  return (ret);
}

KERNEL_ENTRY_POINT
clemuRunTime :: GeCompiledKernel( int _index)
{
KERNEL_ENTRY_POINT ret = 0;
    if ( _index >= 0 && _index < m_nbr_kernels )
	{
		ret = m_compiled_kernels[_index].m_entry;
	}
    return(ret);
}


int
clemuRunTime :: GetCompiledKernelByPtr( KERNEL_ENTRY_POINT _ptr)
{
int ret = -1;
    for( int i = 0; i < m_nbr_kernels; i++)
	{
		if ( m_compiled_kernels[i].m_entry == _ptr )
		{
			ret = i;
			break;
		}
	}
    return(ret);
}

int 
clemuRunTime :: SetCompiledKernelLocalMemSz(int _index, int _local_mem_sz)
{
    if ( _index >= 0 && _index < m_nbr_kernels )
	{
        m_compiled_kernels[_index].local_mem_sz = _local_mem_sz;
	}
	return 1;
}


int 
clemuRunTime :: GetCompiledKernelLocalMemSz(int _index)
{
int ret = 0;
    if ( _index >= 0 && _index < m_nbr_kernels )
	{
         ret =  m_compiled_kernels[_index].local_mem_sz;
	}
	return ret;
}

