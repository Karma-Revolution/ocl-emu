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

// clemu_runtime.hpp : 
//
#ifndef _CLEMU_RUNTIME_HPP
#define _CLEMU_RUNTIME_HPP

#define _MAX_DEVICES 32

/*************************************************************************************
RUN-TIME
*************************************************************************************/

class clemuCompiledKernel {
public:
	char m_program_loc[_MAX_PROGRAM_NAME];
	char m_kernel_name[_MAX_KERNEL_NAME];
	KERNEL_ENTRY_POINT m_entry;
	int local_mem_sz;
};

class clemuRunTime {
protected:
	int m_active_proc_devs;
    clemuProcessingDevice * m_Devices[_MAX_DEVICES];

	int m_nbr_kernels;
	int m_max_nbr_kernels;
	clemuCompiledKernel *m_compiled_kernels;

public:

	clemuRunTime();
    ~clemuRunTime();
	int initRunTime(void);
	int cleanupRunTime(void);
	int CompileKernel(
			   const char * _program,
		       const char*_kernel_entry_name
			   );
    int  AddCompiledKernel(
			   const char * _program,
		       const char*_kernel_entry_name,
			   KERNEL_ENTRY_POINT _kernel
			   );
    int FindCompiledKernelIndex(
               const char * _program_location,
			   const char * _program_nm,
		       const char*_kernel_entry_name
			   );
    KERNEL_ENTRY_POINT GeCompiledKernel( int _index);

	inline int GetNbrActiveDevices(void)
	{
		return(m_active_proc_devs);
	}
	clemuProcessingDevice * GetActiveDev(int _index);
    int GetCompiledKernelByPtr( KERNEL_ENTRY_POINT _ptr);
    int SetCompiledKernelLocalMemSz(int _index, int _local_mem_sz);
 //   int AccumCompiledKernelLocalMemSz(int _index, int _local_mem_sz);
    int GetCompiledKernelLocalMemSz(int _index);

#if 0
	inline int SetActiveDev(clemuProcessingDevice * _pDev)
	{
      int ret = m_active_proc_devs;
		 m_Devices[m_active_proc_devs] = _pDev;
	     m_active_proc_devs++;
		 return (ret);
	}
#endif

};

#endif // _CLEMU_RUNTIME_HPP