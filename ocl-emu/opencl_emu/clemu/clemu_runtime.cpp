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

