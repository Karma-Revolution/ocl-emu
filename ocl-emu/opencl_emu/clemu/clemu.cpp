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
For MPEG-2 Encoding Products (those that are �Sold� to end-users, directly or indirectly):
NO LICENSE IS GRANTED HEREIN, BY IMPLICATION OR OTHERWISE, TO YOU OR YOUR CUSTOMERS TO USE MPEG-2 ENCODING PRODUCTS, MPEG-2 DISTRIBUTION ENCODING PRODUCTS,
MPEG-2 ENCODING SOFTWARE, AND/OR MPEG-2 BUNDLED ENCODING SOFTWARE FOR ENCODING OR HAVING ENCODED ONE OR MORE MPEG-2 VIDEO EVENTS FOR RECORDING ON AN MPEG-2 
PACKAGED MEDIUM FOR ANY USE OR DISTRIBUTION OTHER THAN PERSONAL USE OF LICENSEE�S CUSTOMER.
For MPEG-2 Intermediate Products (those that are NOT �Sold� to end-users, directly or indirectly):
NO LICENSE IS GRANTED HEREIN, BY IMPLICATION OR OTHERWISE, TO YOU OR YOUR CUSTOMERS TO USE MPEG-2 INTERMEDIATE PRODUCTS MANUFACTURED OR SOLD BY YOU.
If you use the software (in whole or in part), you shall adhere to all applicable U.S., European, and other export laws, including but not limited to
the U.S. Export Administration Regulations (�EAR�), (15 C.F.R. Sections 730 through 774), and E.U. Council Regulation (EC) No 1334/2000 of 22 June 2000.
Further, pursuant to Section 740.6 of the EAR, you hereby certify that, except pursuant to a license granted by the United States Department
of Commerce Bureau of Industry and Security or as otherwise permitted pursuant to a License Exception under the U.S. Export Administration Regulations ("EAR"),
you will not (1) export, re-export or release to a national of a country in Country Groups D:1, E:1 or E:2 any restricted technology, software, or source code
you receive hereunder, or (2) export to Country Groups D:1, E:1 or E:2 the direct product of such technology or software, if such foreign produced direct product
is subject to national security controls as identified on the Commerce Control List (currently found in Supplement 1 to Part 774 of EAR).  For the most current
Country Group listings, or for additional information about the EAR or your obligations under those regulations, please refer to the U.S. Bureau of Industry and
Security�s website at http://www.bis.doc.gov/. 

------------------------------------------------------------------------------------------------------------------------------------------------------*/

// clemu.cpp : Defines the entry point for the console application.
//


#include "clemu.hpp"

#if _MAIN
#include "stdafx.h"
int callCL(const char * _device_type,
		   int _domainDim,
		   int _domain[],
		   int _group[],
		   const char * _program,
		   const char*_kernel_entry_name,
		   ClKrnlArg _args[])

{
 cl_int status = SDK_SUCCESS;
 int count;
    for( count = 0; (_args[count].m_flags & CL_ARG_LAST) != CL_ARG_LAST; count++)
    {
	}
	count++;
    runCLEMU(_device_type,
		     _domainDim,
		     _domain,
		     _group,
		     _program,
		     _kernel_entry_name,
		     count,
		     _args);

   return(status);   
}


#define _IN_BUFX     512
#define _IN_BUFY     512
#define _DOM_DIMX    256
#define _DOM_DIMY    1
#define _GROUP_DIMX  32
#define _GROUP_DIMY  1
#define _LOCL_MEM_SZ (_GROUP_DIMX*_GROUP_DIMY *4 * 30)


ClKrnlArg __Arg(int _buf_size, void *_buf_ptr, unsigned int _flags  )
{
ClKrnlArg ret;
    ret.m_flags = _flags;
    ret.m_len = _buf_size;
	ret.m_arg.parg = _buf_ptr;
	return(ret);
}

int _tmain(int argc, _TCHAR* argv[])
{
unsigned int * inBuffer;
unsigned int * outBuffer;
int inBufLen = _IN_BUFX*_IN_BUFY*sizeof(unsigned int);
int outBufLen =  _IN_BUFX*_IN_BUFY*sizeof(unsigned int);

    inBuffer = (unsigned int*)malloc(inBufLen);
    outBuffer = (unsigned int*)malloc(outBufLen);

cl_int status;
ClKrnlArg Args[1024];


	_ArgFirst(Args, (CL_ARG_INPUT_PTR | CL_ARG_POPULATE_PTR),unsigned int *,inBuffer, inBufLen);
	_Arg(Args, (CL_ARG_OUTPUT_PTR),unsigned int *,outBuffer, outBufLen);
    _Arg(Args, (CL_ARG_LCL_MEM_SZ), int, _LOCL_MEM_SZ, sizeof(int));
    _ArgLast(Args, (CL_ARG_VALUE), int, 4, sizeof(int));

int globalThreads[] = {_DOM_DIMX, _DOM_DIMY};
int localThreads[] = {_GROUP_DIMX, _GROUP_DIMY};

 
//    status = callCL("gpu_emu", __FILE__, "mykernel", 1, globalThreads, localThreads, gatherArgs);
    status = callCL("gpu_emu", 1, globalThreads, localThreads, __FILE__, "mykernel", Args);


	return 0;
}

#endif
