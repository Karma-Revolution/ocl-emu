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


#include "runCLintnl.hpp"
#include "clemu.hpp"
#include<GL/glut.h>
#include <cmath>
#include<malloc.h>


typedef struct _runClDevProperty
{
  char mDeviceName[128];

} runClDevProperty;


inline 
void 
checkErr(cl_int err, const char * name)
{
    if (err != CL_SUCCESS) {
        std::cerr << "ERROR: " <<  name << " (" << err << ")" << std::endl;
        exit(1);
    }
}


int runClGetDeviceInfo(runClDevProperty & retProperty, bool isGpu)
{
    /* Extensions verification flags */
    bool isVistaOrWin7 = false;


#ifdef _WIN32
    // Find the version of Windows
    OSVERSIONINFO vInfo;
    memset(&vInfo, 0, sizeof(vInfo));
    vInfo.dwOSVersionInfoSize = sizeof(vInfo);
    if(!GetVersionEx(&vInfo))
    {
        DWORD dwErr = GetLastError();
        std::cout << "\nERROR : Unable to get Windows version information.\n" << std::endl;
        return 1;
    }

    if(vInfo.dwMajorVersion >= 6)
    {
        isVistaOrWin7 = true;
    }
#endif




    cl_int err;

    // Platform info
    VECTOR_CLASS<cl::Platform> platforms;
    err = cl::Platform::get(&platforms);

    checkErr(
        err && (platforms.size() == 0 ? -1 : CL_SUCCESS),
        "cl::Platform::get()");
    // Now Iteratate over each platform and its devices
    for (VECTOR_CLASS<cl::Platform>::iterator p = platforms.begin(); 
         p != platforms.end(); 
         ++p) {

        std::cout << "  Platform Name:\t\t\t\t\t "     
                  << (*p).getInfo<CL_PLATFORM_NAME>().c_str() 
                  << std::endl; 
 
        VECTOR_CLASS<cl::Device> devices;
        (*p).getDevices(CL_DEVICE_TYPE_ALL, &devices);
    
        std::cout << "Number of devices:\t\t\t\t " << devices.size() << std::endl;
        for (VECTOR_CLASS<cl::Device>::iterator i = devices.begin(); 
             i != devices.end(); 
             ++i) {

            /* Get device name */
			cl::STRING_CLASS deviceName = (*i).getInfo<CL_DEVICE_NAME>();
            cl_device_type dtype = (*i).getInfo<CL_DEVICE_TYPE>();
			if (isGpu && dtype == CL_DEVICE_TYPE_GPU)
			{
                strcpy_s(retProperty.mDeviceName,128,deviceName.c_str());
			}

		}

	}

	return 1;
}


static double sAccumTime = 0;
static int sPass = 0;


/***********************************************************************************************
    ClRunInstance
***********************************************************************************************/
ClRunInstance::~ClRunInstance()
{
	cleanupInstance();
}



int 
ClRunInstance::setupInstance(ClRunnable *_parent, cl_program _program, cl_kernel _kernel, size_t _nbr_dim, size_t _domainSize[3], size_t _groupSize[3], int _nbr_args, ClKrnlArg *_args)
{
cl_int status = CL_SUCCESS;
int b_cleanup = 0;
    
    b_cleanup = (int)( !_args || m_nbr_args != _nbr_args || m_nbr_dim != _nbr_dim);

	if (!b_cleanup)
	{
	    for( unsigned int i = 0; i < _nbr_dim; i++)
	    {
		   b_cleanup |= (int)(m_domainSize[i] != _domainSize[i]);
		   b_cleanup |= (int)(m_groupSize[i] != _groupSize[i]);
		}
	}
	if ( b_cleanup )
	{
// call clean UP here releasing memory
		 cleanupInstanceArgs();
	}

    m_parent = _parent;
	m_program = _program;
    m_kernel = _kernel;
	m_nbr_dim = _nbr_dim;
	for( unsigned int i = 0; i < m_nbr_dim; i++)
	{
		m_domainSize[i] = _domainSize[i];
	    m_groupSize[i] = _groupSize[i];
	}
	for( int i = m_nbr_dim; i < 3; i++)
	{
		m_domainSize[i] = 1;
	    m_groupSize[i] = 1;
	}

	if ( !m_args && _nbr_args > 0)
	{
	   m_args = new ClKrnlArgIntnl[_nbr_args];
       m_nbr_args = _nbr_args;

       for(int i = 0; i < m_nbr_args; i++)
       {
		   m_args[i].m_extarg.m_flags = CL_ARG_NOT_INIT;
	   }
	}


// setup arguments
    for(int i = 0; i < m_nbr_args; i++)
	{
cl_ulong usedLocalMemory;

			if ( m_args[i].m_extarg.m_flags & CL_ARG_VALUE  )
			{

       			    memcpy(&m_args[i].m_extarg, &_args[i], sizeof(ClKrnlArg));
                    m_args[i].m_resource = 0;

				    status = clSetKernelArg(
                              m_kernel,
                              i,
                              m_args[i].m_extarg.m_len,
                              (void *)&m_args[i].m_extarg.m_arg.iarg);
                   if(!m_parent->GetCommonEnv()->checkVal(
                       status,
                       CL_SUCCESS, 
                       "clSetKernelArg failed. (val)"))
                    {
                        return SDK_FAILURE;
                    }
			}
			else if ( m_args[i].m_extarg.m_flags & CL_ARG_LCL_MEM_SZ  )
			{
       			    memcpy(&m_args[i].m_extarg, &_args[i], sizeof(ClKrnlArg));
                    m_args[i].m_resource = 0;

    /* local memory */
                   status = clSetKernelArg(
                            m_kernel,
                            i,
                            m_args[i].m_extarg.m_len,
                            NULL);
                   if(!m_parent->GetCommonEnv()->checkVal(
                      status,
                      CL_SUCCESS, 
                      "clSetKernelArg failed. (local mem sz)"))
                   {
                      return SDK_FAILURE;
                   }

                   status = clGetKernelWorkGroupInfo(m_kernel,
                            m_parent->GetDevices()[0],
                            CL_KERNEL_LOCAL_MEM_SIZE,
                            sizeof(cl_ulong),
                            &usedLocalMemory,
                            NULL);
                  if(!m_parent->GetCommonEnv()->checkVal(
                           status,
                           CL_SUCCESS, 
                           "clGetKernelWorkGroupInfo CL_KERNEL_LOCAL_MEM_SIZE failed."))
                  {
                     return SDK_FAILURE;
                  } 

                  if(usedLocalMemory > m_parent->GetTotalLclMem())
                  {
                      std::cout << "Unsupported: Insufficient"
                      "local memory on device." << std::endl;
                      return SDK_FAILURE;
                  }

			}

/*
			else if ( (m_args[i].m_extarg.m_flags & CL_ARG_DEVICE_PARAM) == CL_ARG_DEVICE_PARAM )
			{
// send one of device info
             unsigned int value;
                       m_parent->GetDeviceInfo((cl_device_info)m_args[i].m_extarg.m_arg.iarg,
                                               (void *)&value);
                   status = clSetKernelArg(
                            m_kernel,
                            i,
                            sizeof(unsigned int),
                            &value);
                   if(!m_parent->GetCommonEnv()->checkVal(
                      status,
                      CL_SUCCESS, 
                      "clSetKernelArg failed. (local mem sz)"))
                   {
                      return SDK_FAILURE;
                   }

			}
*/
			else if ( (m_args[i].m_extarg.m_flags & CL_ARG_BUFFER) ||  (m_args[i].m_extarg.m_flags & CL_ARG_IMAGE))
			{

				if ( m_args[i].m_extarg.m_arg.parg != _args[i].m_arg.parg || m_args[i].m_extarg.m_len != _args[i].m_len )
				{
					 releaseBuf(&m_args[i]);
// release buffer
                     m_args[i].m_extarg.m_flags = CL_ARG_NOT_INIT;
				}

				else
				{
// setup buffer arg
				    status = clSetKernelArg(
                              m_kernel,
                              i,
                              sizeof(cl_mem),
                              (void *)&m_args[i].m_resource);
                   if(!m_parent->GetCommonEnv()->checkVal(
                       status,
                       CL_SUCCESS, 
                       "clSetKernelArg failed. (val)"))
                    {
                        return SDK_FAILURE;
                    }
				}
			}

		if ( m_args[i].m_extarg.m_flags == CL_ARG_NOT_INIT )
		{
			memcpy(&m_args[i].m_extarg, &_args[i], sizeof(ClKrnlArg));
            m_args[i].m_resource = 0;

			if ( m_args[i].m_extarg.m_flags & CL_ARG_VALUE )
			{

				    status = clSetKernelArg(
                              m_kernel,
                              i,
                              m_args[i].m_extarg.m_len,
                              (void *)&m_args[i].m_extarg.m_arg.iarg);
                   if(!m_parent->GetCommonEnv()->checkVal(
                       status,
                       CL_SUCCESS, 
                       "clSetKernelArg failed. (val)"))
                    {
                        return SDK_FAILURE;
                    }
			}
			else if ( m_args[i].m_extarg.m_flags & CL_ARG_LCL_MEM_SZ )
			{
    /* local memory */


                   status = clSetKernelArg(
                            m_kernel,
                            i,
                            m_args[i].m_extarg.m_len,
                            NULL);
                   if(!m_parent->GetCommonEnv()->checkVal(
                      status,
                      CL_SUCCESS, 
                      "clSetKernelArg failed. (local mem sz)"))
                   {
                      return SDK_FAILURE;
                   }
                   status = clGetKernelWorkGroupInfo(m_kernel,
                            m_parent->GetDevices()[0],
                            CL_KERNEL_LOCAL_MEM_SIZE,
                            sizeof(cl_ulong),
                            &usedLocalMemory,
                            NULL);
                  if(!m_parent->GetCommonEnv()->checkVal(
                           status,
                           CL_SUCCESS, 
                           "clGetKernelWorkGroupInfo CL_KERNEL_LOCAL_MEM_SIZE failed."))
                  {
                     return SDK_FAILURE;
                  } 

                  if(usedLocalMemory > m_parent->GetTotalLclMem())
                  {
                      std::cout << "Unsupported: Insufficient"
                      "local memory on device." << std::endl;
                      return SDK_FAILURE;
                  }




			}

/*
			else if ( (m_args[i].m_extarg.m_flags & CL_ARG_DEVICE_PARAM) == CL_ARG_DEVICE_PARAM )
			{
// send one of device info
             unsigned int value;
                       m_parent->GetDeviceInfo((cl_device_info)m_args[i].m_extarg.m_arg.iarg,
                                               (void *)&value);
                   status = clSetKernelArg(
                            m_kernel,
                            i,
                            sizeof(unsigned int),
                            &value);
                   if(!m_parent->GetCommonEnv()->checkVal(
                      status,
                      CL_SUCCESS, 
                      "clSetKernelArg failed. (local mem sz)"))
                   {
                      return SDK_FAILURE;
                   }

			}
*/
			else if ( m_args[i].m_extarg.m_flags & CL_ARG_BUFFER )
			{
// we create buffer
// the output buffer are always written back
// input/inout only if POPULATE is set
            cl_mem_flags create_flags = 0;

				 if ( (m_args[i].m_extarg.m_flags & CL_ARG_INPUT_PTR) == CL_ARG_INPUT_PTR)
				 {
					 create_flags = CL_MEM_READ_ONLY;
				 }
				 else if ( (m_args[i].m_extarg.m_flags & CL_ARG_OUTPUT_PTR) == CL_ARG_OUTPUT_PTR)
				 {
					 create_flags = CL_MEM_WRITE_ONLY;
				 }
			     else if ( (m_args[i].m_extarg.m_flags & CL_ARG_INPUTOUTPUT_PTR) == CL_ARG_INPUTOUTPUT_PTR)
				 {
					 create_flags = CL_MEM_READ_WRITE;
				 }
				 m_args[i].m_resource = clCreateBuffer(m_parent->GetCntxt(),
                                                       create_flags,
                                                       m_args[i].m_extarg.m_len,
                                                       0,
                                                       &status);

// setup buffer arg
				    status = clSetKernelArg(
                              m_kernel,
                              i,
                              sizeof(cl_mem),
                              (void *)&m_args[i].m_resource);
                   if(!m_parent->GetCommonEnv()->checkVal(
                       status,
                       CL_SUCCESS, 
                       "clSetKernelArg failed. (val)"))
                    {
                        return SDK_FAILURE;
                    }


			}

			else if ( m_args[i].m_extarg.m_flags & CL_ARG_IMAGE )
			{
// we create buffer
// the output buffer are always written back
// input/inout only if POPULATE is set
            cl_mem_flags create_flags = 0;
const ClImageArg * img = (const ClImageArg*)m_args[i].m_extarg.arg_ptr;
void *host_ptr = (img->flags & CL_MEM_WRITE_ONLY) ? 0 : img->host_ptr;
    /* Create 2D output image */
                 m_args[i].m_resource = clCreateImage2D(m_parent->GetCntxt(),
                                                        img->flags,
                                                        &img->image_format,
                                                        img->image_width,
                                                        img->image_height,
                                                        0,
                                                        host_ptr,
                                                        &status);


// setup buffer arg
				    status = clSetKernelArg(
                              m_kernel,
                              i,
                              sizeof(cl_mem),
                              (void *)&m_args[i].m_resource);
                   if(!m_parent->GetCommonEnv()->checkVal(
                       status,
                       CL_SUCCESS, 
                       "clSetKernelArg failed. (val)"))
                    {
                        return SDK_FAILURE;
                    }


			}

		}
	}

// setup group size

// TO DO : CL_KERNEL_COMPILE_WORK_GROUP_SIZE
    /* Check group size against group size returned by kernel */
size_t kernelWorkGroupSize;
    status = clGetKernelWorkGroupInfo(m_kernel,
             m_parent->GetDevices()[0],
             CL_KERNEL_WORK_GROUP_SIZE,
             sizeof(size_t),
             &kernelWorkGroupSize,
             0);
    if(!m_parent->GetCommonEnv()->checkVal(
        status,
        CL_SUCCESS, 
        "clGetKernelWorkGroupInfo CL_KERNEL_WORK_GROUP_SIZE failed."))
    {
        return SDK_FAILURE;
    }

    if(m_groupSize[0]*m_groupSize[1]*m_groupSize[2] > kernelWorkGroupSize)
    {
        std::cout << "Out of Resources!" << std::endl;
        std::cout << "Group Size specified : " << m_groupSize[0] << std::endl;
        std::cout << "Max Group Size supported on the kernel : " << 
            kernelWorkGroupSize<<std::endl;
        std::cout << "Falling back to " << kernelWorkGroupSize << std::endl;
        m_groupSize[0] = kernelWorkGroupSize;
		m_groupSize[1] = m_groupSize[2] = 1;
    }

    /* 
    * Enqueue a kernel run call.
    */
// TO DO: all dimensions
     if (m_groupSize[0] > m_parent->GetMaxWorkItmeSzs()[0]
	    || m_groupSize[1] > m_parent->GetMaxWorkItmeSzs()[1]
		|| m_groupSize[2] > m_parent->GetMaxWorkItmeSzs()[2]
        || m_groupSize[0]*m_groupSize[1]*m_groupSize[2] > m_parent->GetMaxWkGrpSz())
     {
          std::cout << "Unsupported: Device"
          "does not support requested number of work items.";
          return SDK_FAILURE;
     }


	return status;
}

int
ClRunInstance::runInstance( void )
{

    cl_int   status;
    cl_event events[1];

// populate input

    for(int i = 0; i < m_nbr_args; i++)
	{

		if ( (m_args[i].m_extarg.m_flags & CL_ARG_BUFFER)
			&& ((m_args[i].m_extarg.m_flags & CL_ARG_INPUT_PTR) || (m_args[i].m_extarg.m_flags & CL_ARG_INPUTOUTPUT_PTR))
			&& (m_args[i].m_extarg.m_flags & CL_ARG_POPULATE_PTR)
			)
		{
    /* Enqueue write  */
              status = clEnqueueWriteBuffer(m_parent->GetCmmdQue(),
                                            m_args[i].m_resource,
                                            CL_TRUE,
                                            0,
                                            m_args[i].m_extarg.m_len,
                                            m_args[i].m_extarg.m_arg.parg,
                                            0,
                                            0,
                                            0);

              if(!m_parent->GetCommonEnv()->checkVal(status,
                               CL_SUCCESS, 
                               "clEnqueueWriteBuffer failed. (seedsBuf)"))
              {
                  return SDK_FAILURE;
              }

              
		}

		if ( (m_args[i].m_extarg.m_flags & CL_ARG_IMAGE)
			&& ((m_args[i].m_extarg.m_flags & CL_MEM_READ_ONLY) || (m_args[i].m_extarg.m_flags & CL_MEM_READ_WRITE))
			&& (m_args[i].m_extarg.m_flags & CL_ARG_POPULATE)
			)
		{
    /* Enqueue Write Image */

const ClImageArg * img = (const ClImageArg*)m_args[i].m_extarg.arg_ptr;
int depth = (img->image_depth == 0)? 1 : img->image_depth;
    size_t origin[] = {0, 0, 0};
    size_t region[] = {img->image_width, img->image_height, depth};

    /* Read output of 2D copy */
               status = clEnqueueWriteImage(m_parent->GetCmmdQue(),
                                          m_args[i].m_resource,
                                          1,
                                          origin,
                                          region,
                                          0,
                                          0,
                                          img->host_ptr,
                                          0, 0, 0);

              if(!m_parent->GetCommonEnv()->checkVal(status,
                               CL_SUCCESS, 
                               "clEnqueueWriteImage failed. (seedsBuf)"))
              {
                  return SDK_FAILURE;
              }

              
		}


	}

//	clFlush(m_parent->GetCmmdQue());
//    clFinish(m_parent->GetCmmdQue());

 int timing = 1;
 int iterations = 1;
 double kernelTime;


          if(timing)
          {
            int timer = m_parent->GetCommonEnv()->createTimer();
               m_parent->GetCommonEnv()->resetTimer(timer);
               m_parent->GetCommonEnv()->startTimer(timer);

               for(int i = 0; i < iterations; ++i)
               {




    /*
     * Enqueue a kernel run call.
     * Each thread generates mulFactor random numbers from given seed.
     */
    status = clEnqueueNDRangeKernel(m_parent->GetCmmdQue(),
                                    m_kernel,
                                    m_nbr_dim,
                                    NULL,
		                            m_domainSize,
	                                m_groupSize,
                                    0,
                                    NULL,
                                    0/*&events[0]*/);

    if(!m_parent->GetCommonEnv()->checkVal(status,
                               CL_SUCCESS,
                               "clEnqueueNDRangeKernel failed."))
    {
		switch((int)status)
		{
       case CL_INVALID_PROGRAM_EXECUTABLE: /*if there is no successfully built program
executable available for device associated with command_queue.*/
       case CL_INVALID_COMMAND_QUEUE: /*if command_queue is not a valid command-queue.*/
       case CL_INVALID_KERNEL: /*if kernel is not a valid kernel object.*/
       case CL_INVALID_CONTEXT: /*if context associated with command_queue and kernel are not
the same or if the context associated with command_queue and events in event_wait_list
are not the same.*/
      case CL_INVALID_KERNEL_ARGS: /*if the kernel argument values have not been specified.*/ 
      case CL_INVALID_WORK_DIMENSION: /*if work_dim is not a valid value (i.e. a value between
1 and 3).*/
      case CL_INVALID_WORK_GROUP_SIZE: /*if local_work_size is specified and number of workitems
specified by global_work_size is not evenly divisable by size of work-group given
by local_work_size or does not match the work-group size specified for kernel using the
__attribute__((reqd_work_group_size(X, Y, Z))) qualifier in program
source.*/
     /* case CL_INVALID_WORK_GROUP_SIZE:*/ /*if local_work_size is specified and the total number
of work-items in the work-group computed as local_work_size[0] * …
local_work_size[work_dim – 1] is greater than the value specified by
CL_DEVICE_MAX_WORK_GROUP_SIZE in table 4.3.*/
      /*case CL_INVALID_WORK_GROUP_SIZE:*/ /*if local_work_size is NULL and the
__attribute__((reqd_work_group_size(X, Y, Z))) qualifier is used to
declare the work-group size for kernel in the program source.*/
      case CL_INVALID_WORK_ITEM_SIZE: /*if the number of work-items specified in any of
local_work_size[0], … local_work_size[work_dim – 1] is greater than the
corresponding values specified by CL_DEVICE_MAX_WORK_ITEM_SIZES[0], ….
CL_DEVICE_MAX_WORK_ITEM_SIZES[work_dim – 1].*/
      case CL_OUT_OF_RESOURCES: /*if there is a failure to queue the execution instance of kernel
on the command-queue because of insufficient resources needed to execute the kernel.
For example, the explicitly specified local_work_size causes a failure to execute the
kernel because of insufficient resources such as registers or local memory. Another
example would be the number of read-only image args used in kernel exceed the
CL_DEVICE_MAX_READ_IMAGE_ARGS value for device or the number of write-only
image args used in kernel exceed the CL_DEVICE_MAX_WRITE_IMAGE_ARGS value
for device or the number of samplers used in kernel exceed
CL_DEVICE_MAX_SAMPLERS for device.*/
     case CL_MEM_OBJECT_ALLOCATION_FAILURE: /*if there is a failure to allocate memory for
data store associated with image or buffer objects specified as arguments to kernel.*/
     case CL_INVALID_EVENT_WAIT_LIST: /*if event_wait_list is NULL and
num_events_in_wait_list > 0, or event_wait_list is not NULL and
num_events_in_wait_list is 0, or if event objects in event_wait_list are not valid events.*/
     case CL_OUT_OF_HOST_MEMORY: /*if there is a failure to allocate resources required by the
OpenCL implementation on the host.*/
     default: ;
		 
		}
        return SDK_FAILURE;
    }

    /* Wait for the kernel call to finish execution */
 //   status = clWaitForEvents(1, &events[0]);
               
	

/*	
    if(!m_parent->GetCommonEnv()->checkVal(status,
                               CL_SUCCESS,
                               "clWaitForEvents failed."))
    {
        return SDK_FAILURE;
    }
    
    clReleaseEvent(events[0]);
*/


			   } // iterations


	clFlush(m_parent->GetCmmdQue());

	
    clFinish(m_parent->GetCmmdQue());

               m_parent->GetCommonEnv()->stopTimer(timer);
        /* Compute kernel time */
               kernelTime = (double)(m_parent->GetCommonEnv()->readTimer(timer)) / iterations;

			   sAccumTime += kernelTime;
#if 0
               printf("N: %d, Time(ms): %lf %lf\n",
                          ++sPass, 
						  (kernelTime * 1000),
                          (sAccumTime * 1000));
#endif
		   }
		   else
		   {

    /*
     * Enqueue a kernel run call.
     * Each thread generates mulFactor random numbers from given seed.
     */
    status = clEnqueueNDRangeKernel(m_parent->GetCmmdQue(),
                                    m_kernel,
                                    m_nbr_dim,
                                    NULL,
		                            m_domainSize,
	                                m_groupSize,
                                    0,
                                    NULL,
                                    &events[0]);

    if(!m_parent->GetCommonEnv()->checkVal(status,
                               CL_SUCCESS,
                               "clEnqueueNDRangeKernel failed."))
    {
		switch((int)status)
		{
       case CL_INVALID_PROGRAM_EXECUTABLE: /*if there is no successfully built program
executable available for device associated with command_queue.*/
       case CL_INVALID_COMMAND_QUEUE: /*if command_queue is not a valid command-queue.*/
       case CL_INVALID_KERNEL: /*if kernel is not a valid kernel object.*/
       case CL_INVALID_CONTEXT: /*if context associated with command_queue and kernel are not
the same or if the context associated with command_queue and events in event_wait_list
are not the same.*/
      case CL_INVALID_KERNEL_ARGS: /*if the kernel argument values have not been specified.*/ 
      case CL_INVALID_WORK_DIMENSION: /*if work_dim is not a valid value (i.e. a value between
1 and 3).*/
      case CL_INVALID_WORK_GROUP_SIZE: /*if local_work_size is specified and number of workitems
specified by global_work_size is not evenly divisable by size of work-group given
by local_work_size or does not match the work-group size specified for kernel using the
__attribute__((reqd_work_group_size(X, Y, Z))) qualifier in program
source.*/
     /* case CL_INVALID_WORK_GROUP_SIZE:*/ /*if local_work_size is specified and the total number
of work-items in the work-group computed as local_work_size[0] * …
local_work_size[work_dim – 1] is greater than the value specified by
CL_DEVICE_MAX_WORK_GROUP_SIZE in table 4.3.*/
      /*case CL_INVALID_WORK_GROUP_SIZE:*/ /*if local_work_size is NULL and the
__attribute__((reqd_work_group_size(X, Y, Z))) qualifier is used to
declare the work-group size for kernel in the program source.*/
      case CL_INVALID_WORK_ITEM_SIZE: /*if the number of work-items specified in any of
local_work_size[0], … local_work_size[work_dim – 1] is greater than the
corresponding values specified by CL_DEVICE_MAX_WORK_ITEM_SIZES[0], ….
CL_DEVICE_MAX_WORK_ITEM_SIZES[work_dim – 1].*/
      case CL_OUT_OF_RESOURCES: /*if there is a failure to queue the execution instance of kernel
on the command-queue because of insufficient resources needed to execute the kernel.
For example, the explicitly specified local_work_size causes a failure to execute the
kernel because of insufficient resources such as registers or local memory. Another
example would be the number of read-only image args used in kernel exceed the
CL_DEVICE_MAX_READ_IMAGE_ARGS value for device or the number of write-only
image args used in kernel exceed the CL_DEVICE_MAX_WRITE_IMAGE_ARGS value
for device or the number of samplers used in kernel exceed
CL_DEVICE_MAX_SAMPLERS for device.*/
     case CL_MEM_OBJECT_ALLOCATION_FAILURE: /*if there is a failure to allocate memory for
data store associated with image or buffer objects specified as arguments to kernel.*/
     case CL_INVALID_EVENT_WAIT_LIST: /*if event_wait_list is NULL and
num_events_in_wait_list > 0, or event_wait_list is not NULL and
num_events_in_wait_list is 0, or if event objects in event_wait_list are not valid events.*/
     case CL_OUT_OF_HOST_MEMORY: /*if there is a failure to allocate resources required by the
OpenCL implementation on the host.*/
     default: ;
		 
		}
        return SDK_FAILURE;
    }

    /* Wait for the kernel call to finish execution */
    status = clWaitForEvents(1, &events[0]);
    if(!m_parent->GetCommonEnv()->checkVal(status,
                               CL_SUCCESS,
                               "clWaitForEvents failed."))
    {
        return SDK_FAILURE;
    }
    
    clReleaseEvent(events[0]);

    clFinish(m_parent->GetCmmdQue());




		   }

// read results

    for(int i = 0; i < m_nbr_args; i++)
	{

		if ( (m_args[i].m_extarg.m_flags & CL_ARG_BUFFER)
			&& ((m_args[i].m_extarg.m_flags & CL_ARG_OUTPUT_PTR)
			||  (m_args[i].m_extarg.m_flags & CL_ARG_INPUTOUTPUT_PTR))
		   )
		{
    /* Enqueue the results to application pointer*/
              status = clEnqueueReadBuffer(m_parent->GetCmmdQue(),
                                 m_args[i].m_resource,
                                 CL_TRUE,
                                 0,
                                 m_args[i].m_extarg.m_len,
                                 m_args[i].m_extarg.m_arg.parg,
                                 0,
                                 0,
								 0);

//                                 &events[0]);
              if(!m_parent->GetCommonEnv()->checkVal(status,
                               CL_SUCCESS,
                               "clEnqueueReadBuffer failed."))
              {
                 return SDK_FAILURE;
              }



		}

		if ( (m_args[i].m_extarg.m_flags & CL_ARG_IMAGE)
			&& ((m_args[i].m_extarg.m_flags & CL_MEM_WRITE_ONLY) || (m_args[i].m_extarg.m_flags & CL_MEM_READ_WRITE))
			&& (m_args[i].m_extarg.m_flags & CL_ARG_POPULATE)
			)
		{
    /* Enqueue Read Image */
const ClImageArg * img = (const ClImageArg*)m_args[i].m_extarg.arg_ptr;
int depth = (img->image_depth == 0)? 1 : img->image_depth;
    size_t origin[] = {0, 0, 0};
    size_t region[] = {img->image_width, img->image_height, depth};

    /* Read output of 2D copy */
               status = clEnqueueReadImage(m_parent->GetCmmdQue(),
                                          m_args[i].m_resource,
                                          1,
                                          origin,
                                          region,
                                          0,
                                          0,
                                          img->host_ptr,
                                          0, 0, 0);

              if(!m_parent->GetCommonEnv()->checkVal(status,
                               CL_SUCCESS, 
                               "clEnqueueWriteImage failed. (seedsBuf)"))
              {
                  return SDK_FAILURE;
              }

              
		}


	}
    return SDK_SUCCESS;
}



int 
ClRunInstance::releaseBuf(ClKrnlArgIntnl * _buf_arg)
{
 cl_int status = CL_SUCCESS;
    if ( _buf_arg->m_resource )
	{
       status = clReleaseMemObject(_buf_arg->m_resource);
      if(!m_parent->GetCommonEnv()->checkVal(
           status,
           CL_SUCCESS,
           "clReleaseMemObject failed."))
       {
          return SDK_FAILURE;
       }
	  _buf_arg->m_resource = 0;
	}
	return status;
}

int 
ClRunInstance::cleanupInstanceArgs( void )
{
 cl_int status = CL_SUCCESS;

  if ( m_parent )
  {
	if ( m_nbr_args )
	{
		for(int i = 0; i < m_nbr_args; i++)
		{
            if ( (m_args[i].m_extarg.m_flags & CL_ARG_BUFFER) == CL_ARG_BUFFER )
			{
                releaseBuf(&m_args[i]);
			}
		}
		delete []m_args;
		m_args = 0;
        m_nbr_args = 0;
	}
  }
  return(status);
}

int 
ClRunInstance::cleanupInstance( void )
{
 cl_int status = CL_SUCCESS;

  if ( m_parent )
  {
	if ( m_nbr_args )
	{
		for(int i = 0; i < m_nbr_args; i++)
		{
            if ( (m_args[i].m_extarg.m_flags & CL_ARG_BUFFER) == CL_ARG_BUFFER )
			{
                releaseBuf(&m_args[i]);
			}
		}
		delete []m_args;
		m_args = 0;
        m_nbr_args = 0;
	}
    if ( m_kernel )
	{
         status = clReleaseKernel(m_kernel);
         if(!m_parent->GetCommonEnv()->checkVal(
            status,
            CL_SUCCESS,
            "clReleaseKernel failed."))
         {
            return SDK_FAILURE;
         }
		 m_kernel = 0;
	}

    m_parent = 0;
  }
	return status;
}

/***********************************************************************************************
    ClRunnableProgram
***********************************************************************************************/
ClRunnableProgram :: ClRunnableProgram()
{
    m_nbr_kernels = 0;
    m_max_kernels = _INIT_NMBR_KERNELS;
	m_kernels = new ClRunInstance[m_max_kernels];
	m_program = 0;
	m_program_loc[0] = 0;
	ResetCache();

}

ClRunnableProgram :: ~ClRunnableProgram()
{
	if ( m_kernels )
	{
		delete []m_kernels;
		m_kernels = 0;
		m_nbr_kernels = 0;
	}
	ResetCache();
}

int 
ClRunnableProgram::InstKernelCL(ClRunInstance**_run_kernel,  const char* _kernel_entry_name)
{
 cl_int status = CL_SUCCESS;
 cl_kernel kernel;

    if ( FindKernel(_kernel_entry_name,_run_kernel) == CL_SUCCESS)
	{
		return(status);
	}

    /* get a kernel object handle for a kernel with the given name */
    kernel = clCreateKernel(
        GetBuiltProgram(),
        _kernel_entry_name,
        &status);
    if(CL_SUCCESS != status)
    {
        return SDK_FAILURE;
    }

	AddKernel(_kernel_entry_name, kernel);
	FindKernel(_kernel_entry_name, _run_kernel);
    SetLastKernel(*_run_kernel);


	return(status);

}


int 
ClRunnableProgram :: FindKernel(const char* _kernel_name, ClRunInstance**_kernel_instance )
{
cl_int status = SDK_FAILURE;

    for( int i = 0; i < m_nbr_kernels; i++)
	{
		if ( !strcmp(m_kernels[i].GetKrnlName(),_kernel_name ))
		{
			*_kernel_instance = &m_kernels[i];
            status = CL_SUCCESS;
			break;
		}
	}
	return status;
}
int 
ClRunnableProgram :: AddKernel(const char* _kernel_name, cl_kernel _kernel)
{
cl_int status = SDK_FAILURE;

    if (m_nbr_kernels < m_max_kernels)
	{
		m_kernels[m_nbr_kernels].SetProgr(GetBuiltProgram());
		m_kernels[m_nbr_kernels].SetKrnlName(_kernel_name);
		m_kernels[m_nbr_kernels].SetKrnl(_kernel);
		m_nbr_kernels++;
        status = CL_SUCCESS;
	}
	return status;
}

int
ClRunnableProgram :: ResetCache(void)
{
	m_cachedkernel = 0;
	return(0);
}


/***********************************************************************************************
    ClRunnable
***********************************************************************************************/


ClRunnable::~ClRunnable()
{
    cleanupCL();
}


int ClRunnable:: GetDeviceInfo(cl_device_info param_name,
                               void *param_value)
{
cl_int status = CL_SUCCESS;
	if ( !IsInit() )
	{
        return(SDK_FAILURE);
	}

    /* Get Device specific Information */
    status = clGetDeviceInfo(
        m_devices[0],
        param_name,
        sizeof(size_t),
        (void*)param_value,
        NULL);

	return(status);

}

int
ClRunnable::setupCL(const char *_dev_type)
{
    cl_int status = CL_SUCCESS;

	if ( m_cntxt_counter > 0 )
	{
        return(status);
	}

// program data base
	m_nbr_programs = 0;
	m_max_programs = _INIT_NMBR_PROGRAMS;
	m_Programs = new ClRunnableProgram[m_max_programs];


    cl_device_type dType;

    if(deviceType.compare("gpu") == 0)
    {
        dType = CL_DEVICE_TYPE_GPU;
    }
    else //deviceType = "cpu" 
    {
        dType = CL_DEVICE_TYPE_CPU;
    }

    /*
     * Have a look at the available platforms and pick either
     * the AMD one if available or a reasonable default.
     */

    cl_uint numPlatforms;
    cl_platform_id platform = NULL;
    status = clGetPlatformIDs(0, NULL, &numPlatforms);
    if(!sampleCommon->checkVal(status,
                               CL_SUCCESS,
                               "clGetPlatformIDs failed."))
    {
        return SDK_FAILURE;
    }
    if (0 < numPlatforms) 
    {
        cl_platform_id* platforms = new cl_platform_id[numPlatforms];
        status = clGetPlatformIDs(numPlatforms, platforms, NULL);
        if(!sampleCommon->checkVal(status,
                                   CL_SUCCESS,
                                   "clGetPlatformIDs failed."))
        {
            return SDK_FAILURE;
        }
        for (unsigned i = 0; i < numPlatforms; ++i) 
        {
            char pbuf[100];
            status = clGetPlatformInfo(platforms[i],
                                       CL_PLATFORM_VENDOR,
                                       sizeof(pbuf),
                                       pbuf,
                                       NULL);

            if(!sampleCommon->checkVal(status,
                                       CL_SUCCESS,
                                       "clGetPlatformInfo failed."))
            {
                return SDK_FAILURE;
            }

            platform = platforms[i];
            if (!strcmp(pbuf, "Advanced Micro Devices, Inc.")) 
            {
                break;
            }
        }
        delete[] platforms;
    }

    /*
     * If we could find our platform, use it. Otherwise pass a NULL and get whatever the
     * implementation thinks we should be using.
     */

    cl_context_properties cps[3] = 
    {
        CL_CONTEXT_PLATFORM, 
        (cl_context_properties)platform, 
        0
    };
    /* Use NULL for backward compatibility */
    cl_context_properties* cprops = (NULL == platform) ? NULL : cps;

    m_context = clCreateContextFromType(
        cprops,
        dType,
        NULL,
        NULL,
        &status);

    if(!sampleCommon->checkVal(
        status,
        CL_SUCCESS,
        "clCreateContextFromType failed."))
    {
        return SDK_FAILURE;
    }

    size_t deviceListSize;

    /* First, get the size of device list data */
    status = clGetContextInfo(
        m_context, 
        CL_CONTEXT_DEVICES, 
        0, 
        NULL, 
        &deviceListSize);
    if(!sampleCommon->checkVal(
        status, 
        CL_SUCCESS,
        "clGetContextInfo failed."))
        return SDK_FAILURE;

    /* Now allocate memory for device list based on the size we got earlier */
    m_devices = (cl_device_id*)malloc(deviceListSize);
    if(m_devices==NULL) {
        sampleCommon->error("Failed to allocate memory (devices).");
        return SDK_FAILURE;
    }

    /* Now, get the device list data */
    status = clGetContextInfo(
        m_context, 
        CL_CONTEXT_DEVICES, 
        deviceListSize, 
        m_devices, 
        NULL);
    if(!sampleCommon->checkVal(
        status,
        CL_SUCCESS, 
        "clGetContextInfo failed."))
        return SDK_FAILURE;


    /* Create command queue */

    m_commandQueue = clCreateCommandQueue(
        m_context,
        m_devices[0],
        0,
        &status);

    if(!sampleCommon->checkVal(
        status,
        CL_SUCCESS,
        "clCreateCommandQueue failed."))
    {
        return SDK_FAILURE;
    }

    /* Get Device specific Information */
    status = clGetDeviceInfo(
        m_devices[0],
        CL_DEVICE_MAX_WORK_GROUP_SIZE,
        sizeof(size_t),
        (void*)&m_maxWorkGroupSize,
        NULL);

    if(!sampleCommon->checkVal(
        status,
        CL_SUCCESS, 
        "clGetDeviceInfo CL_DEVICE_MAX_WORK_GROUP_SIZE failed."))
        return SDK_FAILURE;


    status = clGetDeviceInfo(
        m_devices[0],
        CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
        sizeof(cl_uint),
        (void*)&m_maxDimensions,
        NULL);

    if(!sampleCommon->checkVal(
        status,
        CL_SUCCESS, 
        "clGetDeviceInfo CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS failed."))
        return SDK_FAILURE;


    m_maxWorkItemSizes = (size_t*)malloc(m_maxDimensions * sizeof(size_t));

    status = clGetDeviceInfo(
        m_devices[0],
        CL_DEVICE_MAX_WORK_ITEM_SIZES,
        sizeof(size_t) * m_maxDimensions,
        (void*)m_maxWorkItemSizes,
        NULL);

    if(!sampleCommon->checkVal(
        status,
        CL_SUCCESS, 
        "clGetDeviceInfo CL_DEVICE_MAX_WORK_ITEM_SIZES failed."))
        return SDK_FAILURE;


    status = clGetDeviceInfo(
        m_devices[0],
        CL_DEVICE_LOCAL_MEM_SIZE,
        sizeof(cl_ulong),
        (void *)&m_totalLocalMemory,
        NULL);

    if(!sampleCommon->checkVal(
        status,
        CL_SUCCESS, 
        "clGetDeviceInfo CL_DEVICE_LOCAL_MEM_SIZE failed."))
        return SDK_FAILURE;


    status = clGetDeviceInfo(
        m_devices[0],
        CL_DEVICE_NAME,
        128,
        (void *)m_DeviceName,
        NULL);

    if(!sampleCommon->checkVal(
        status,
        CL_SUCCESS, 
        "clGetDeviceInfo CL_DEVICE_NAME failed."))
        return SDK_FAILURE;

// increase ref count
    m_cntxt_counter++;

	return(status);
}

int 
ClRunnable::FindProgram(cl_program _program,
						ClRunnableProgram** _runnable_program )
{
cl_int status = SDK_FAILURE;
	if ( m_Programs )
	{
		for( int i = 0; i < m_nbr_programs; i++)
		{
			if ( m_Programs[i].m_program == _program )
			{
			    *_runnable_program = &m_Programs[i];
			    status = CL_SUCCESS;
			    break;
			}
		}
	}
    return(status);
}



int
ClRunnable::FindProgram(const char* _program_location,
                    const char* _program_nm,
		            ClRunnableProgram** _runnable_program)

{
cl_int status = SDK_FAILURE;
	if ( m_Programs )
	{
		for( int i = 0; i < m_nbr_programs; i++)
		{
			if ( !strcmp(m_Programs[i].m_program_loc,_program_nm) )
			{
			   *_runnable_program = &m_Programs[i];
			   status = CL_SUCCESS;
			   break;
			}
		}
	}
    return(status);
}

int ClRunnable::AddProgram(const char* _program_location,
                            const char* _program_nm,
						   cl_program _program)
{
 cl_int status = SDK_FAILURE;
 	if ( m_Programs && m_nbr_programs < m_max_programs)
	{

		strcpy_s(m_Programs[m_nbr_programs].m_program_loc,_MAX_PROGRAM_NAME, _program_nm);
	    m_Programs[m_nbr_programs].m_program = _program;
		m_nbr_programs++;
	    status = CL_SUCCESS;
	}
    return(status);
}

int
ClRunnable::buildProgramCL(const char* _program_location,
						   const char* _program_nm
						   )
{
 cl_int status = CL_SUCCESS;
 ClRunnableProgram *run_program;
 cl_program program;
 char program_location[_MAX_PROGRAM_NAME + 1] = {0};
 char  *env_root;
 size_t var_len;
 char root_location[_MAX_PROGRAM_NAME + 1];


	if ( FindProgram(_program_location, _program_nm, &run_program ) == CL_SUCCESS )
	{
        return(status);
	}


    _dupenv_s(&env_root,&var_len, "CLEMU_ROOT");

	if ( !var_len )
	{
        return(SDK_FAILURE);
	}

	strcpy_s(root_location,var_len,env_root);

    if ( root_location[var_len-1] != '\\' && root_location[var_len-1] != '/')
	{
         root_location[var_len-1] = '\\';
         root_location[var_len] = 0;
	}
	strcat_s(root_location, _MAX_PROGRAM_NAME, "clemu");

	if (_program_location)
	{
	    strcpy_s(program_location,_MAX_PROGRAM_NAME,_program_location);
	}
    
int loc_len = strlen(program_location);
    if (loc_len == 0)
	{
		strcpy_s(program_location,_MAX_PROGRAM_NAME,"./");
		loc_len = 2;
	}
    if ( program_location[loc_len-1] != '\\' && program_location[loc_len-1] != '/')
	{
         program_location[loc_len] = '\\';
         program_location[loc_len+1] = 0;
	}
	strcat_s(program_location,_MAX_PROGRAM_NAME,_program_nm);
    /* create a CL program using the kernel source */
    streamsdk::SDKFile kernelFile;
//    kernelFile.open("FaceRecogn_Kernels.cl");
    kernelFile.open(program_location);
    const char * source = kernelFile.source().c_str();
	assert(source);
    size_t sourceSize[] = { strlen(source) };
	assert(sourceSize[0] > 0);
    program = clCreateProgramWithSource(
        m_context,
        1,
        &source,
        sourceSize,
        &status);
    if(!sampleCommon->checkVal(
        status,
        CL_SUCCESS,
        "clCreateProgramWithSource failed."))
        return SDK_FAILURE;

	char Options[1024] = {0};


	sprintf_s(Options,512," -I \"%s\"", root_location);
	if ( _program_location )
	{
		sprintf_s(Options,512,"%s -I \"%s\"", Options, _program_location);
	}

    if (!strcmp(GetDevType(),"cpu"))
	{
  const char* emuDevNm;
        strcat_s(Options, 256, " -DCPU_IMPL=1 ");
		getEmuDevParameter(&emuDevNm,CLEMU_PARAM_DEV_NAME);
		if ( emuDevNm && (!strcmp(emuDevNm, "Cedar") || !strcmp(emuDevNm, "Loveland")))
		{
           strcat_s(Options,256,  " -DCEDAR");
		}
	}
	else if (!strcmp(GetDevType(),"gpu"))
	{
        strcat_s(Options,256,  " -DGPU_IMPL=1 ");

		if (!strcmp(m_DeviceName, "Cedar")
			|| !strcmp(m_DeviceName, "Loveland"))
		{
           strcat_s(Options,256,  " -DCEDAR");
		}

	}

    /* create a cl program executable for all the devices specified */
    status = clBuildProgram(
        program,
        1,
        &m_devices[0],
        Options,
        NULL,
        NULL);
    if(status != CL_SUCCESS)
    {
        if(status == CL_BUILD_PROGRAM_FAILURE)
        {
            cl_int logStatus;
            char * buildLog = NULL;
            size_t buildLogSize = 0;
            logStatus = clGetProgramBuildInfo (program, 
                m_devices[0], 
                CL_PROGRAM_BUILD_LOG, 
                buildLogSize, 
                buildLog, 
                &buildLogSize);
            if(!sampleCommon->checkVal(
                logStatus,
                CL_SUCCESS,
                "clGetProgramBuildInfo failed."))
                return SDK_FAILURE;

            buildLog = (char*)malloc(buildLogSize);
            if(buildLog == NULL)
            {
                sampleCommon->error("Failed to allocate host memory. (buildLog)");
                return SDK_FAILURE;
            }
            memset(buildLog, 0, buildLogSize);

            logStatus = clGetProgramBuildInfo (program, 
                m_devices[0], 
                CL_PROGRAM_BUILD_LOG, 
                buildLogSize, 
                buildLog, 
                NULL);
            if(!sampleCommon->checkVal(
                logStatus,
                CL_SUCCESS,
                "clGetProgramBuildInfo failed."))
            {
                free(buildLog);
                return SDK_FAILURE;
            }

            std::cout << " \n\t\t\tBUILD LOG\n";
            std::cout << " ************************************************\n";
            std::cout << buildLog << std::endl;
            std::cout << " ************************************************\n";
            free(buildLog);
        }

        if(!sampleCommon->checkVal(
            status,
            CL_SUCCESS,
            "clBuildProgram failed."))
            return SDK_FAILURE;
    }
    status = AddProgram(_program_location,
		                _program_nm,
		                 program);
	return(status);
}





int 
ClRunnable::runInstKernelCL(const char* _device_name,
							const char * _kernel_location,
		                    const char * _program,
							const char *_kernel_entry_name,
							size_t _nbr_dim,
							size_t _domainSize[3],
							size_t _groupSize[3],
							int _nbr_args, ClKrnlArg *_args)
{
 cl_int status = SDK_SUCCESS; 
 ClRunnableProgram *run_program = 0;
 ClRunInstance*run_kernel = 0;
 int timing = 0;
 int iterations = 1;
 double kernelTime;

	status = setupCL(_device_name);

	if ( _program  )
	{
	     status = buildProgramCL(_kernel_location, _program);

		 if ( status == SDK_SUCCESS)
		 {
            FindProgram(_kernel_location, _program, &run_program);

	        SetLastProgram(run_program);
		 }
	}
	else
	{
        run_program = GetLastProgram();
	}


    if ( status == SDK_SUCCESS && run_program)
	{
	   run_program->InstKernelCL(&run_kernel, _kernel_entry_name);
	   if ( run_kernel )
	   {
          status = run_kernel->setupInstance(this, run_program->GetBuiltProgram(), run_kernel->GetKrnl(), _nbr_dim, _domainSize, _groupSize, _nbr_args, _args);
          if(timing)
          {
            int timer = GetCommonEnv()->createTimer();
               GetCommonEnv()->resetTimer(timer);
               GetCommonEnv()->startTimer(timer);

               for(int i = 0; i < iterations; ++i)
               {
	              status = run_kernel->runInstance();
               }

               GetCommonEnv()->stopTimer(timer);
        /* Compute kernel time */
               kernelTime = (double)(GetCommonEnv()->readTimer(timer)) / iterations;

			   sAccumTime += kernelTime;
               printf("N: %d, Time(ms): %lf %lf\n",
                          ++sPass, 
						  (kernelTime * 1000),
                          (sAccumTime * 1000)/ iterations);

		  }
		  else
		  {
	              status = run_kernel->runInstance();
		  }
	    }
	 }


	

	return(status);
   
}



int 
ClRunnable:: ResetCache(void)
{
    m_cachedprogram = 0;
	return(0);
}

int
ClRunnable::cleanupCL()
{
    /* Releases OpenCL resources (Context, Memory etc.) */
 cl_int status = SDK_SUCCESS;


    ResetCache();

	if ( m_Programs )
	{
		for( int i = 0; i < m_nbr_programs; i++)
		{
			if ( m_Programs[i].m_program )
			{
               status = clReleaseProgram(m_Programs[i].m_program);
               if(!sampleCommon->checkVal(
                       status,
                       CL_SUCCESS,
                       "clReleaseProgram failed."))
               {
                     return SDK_FAILURE;
               }
			   m_Programs[i].m_program = 0;
			}
		}
		delete [] m_Programs;
		m_Programs = 0;
	}

	if ( m_commandQueue )
	{
       status = clReleaseCommandQueue(m_commandQueue);
       if(!sampleCommon->checkVal(
           status,
           CL_SUCCESS,
           "clReleaseCommandQueue failed."))
       {
          return SDK_FAILURE;
       }
	   m_commandQueue = 0;
	}

	if ( m_context )
	{
       status = clReleaseContext(m_context);
       if(!sampleCommon->checkVal(
           status,
           CL_SUCCESS,
           "clReleaseContext failed."))
       {
          return SDK_FAILURE;
       }
	   m_context = 0;
	}

    if(m_devices)
    {
        free(m_devices);
        m_devices = NULL;
    }


    if(m_maxWorkItemSizes)
    {
        free(m_maxWorkItemSizes);
        m_maxWorkItemSizes = NULL;
    }

    return SDK_SUCCESS;

}

/*********************************************************************************************

EXTERNAL INTERFACE

*********************************************************************************************/


static ClRunnable * sRunnables[] = {0};



int callCL(const char * _device_type,
		   int _domainDim,
		   int _domain[],
		   int _group[],
		   const char * _program_location,
		   const char * _program,
		   const char*_kernel_entry_name,
		   ClKrnlArg* _args)
{
int ret = CL_CALL_SUCCESS;

int count = 0;
   if ( _args )
   {
        for( count = 0; (_args[count].m_flags & CL_ARG_LAST) != CL_ARG_LAST; count++)
		{
		}
		count++;
   }
    if ( !strcmp(_device_type, "gpu_emu"))

	{
		ret = runCLEMU(_device_type,
		               _domainDim,
		               _domain,
		               _group,
					   _program_location,
		               _program,
		               _kernel_entry_name,
					   count,
		               _args);
		return(ret);
	}
  

    if (_program || _kernel_entry_name )
	{
        if (_domainDim < 1 || !_domain || !_group || !_kernel_entry_name || (!_device_type && !sRunnables[0]) )
	    {
           return(CL_CALL_FAILURE);
	    }
		if ( sRunnables[0] && _device_type && strcmp(sRunnables[0]->GetDevType(),_device_type))
		{
// new device
     		if ( sRunnables[0] )
	    	{
		    	delete sRunnables[0];
			   sRunnables[0] = 0;
		    }
		}
// real run
		if ( _device_type && !sRunnables[0] )
		{
			sRunnables[0] = new ClRunnable(_device_type);
		}
size_t globalThreads[3] = {1, 1, 1};
size_t localThreads[3] = {1, 1, 1};
        for(int i = 0; i < _domainDim; i++)
		{
			globalThreads[i] = _domain[i];
			localThreads[i] = _group[i];
		}
        ret = sRunnables[0]->runInstKernelCL(0,_program_location,_program,_kernel_entry_name,_domainDim, globalThreads, localThreads, count, _args);

	}
	else if (_device_type && !_program && !_kernel_entry_name)
	{
		if ( sRunnables[0] )
		{
			delete sRunnables[0];
			sRunnables[0] = 0;
		}

	}

    return(ret);
}




/*****************************************************************************

<device_name>::<program_location>::<kernel_entry_name>
<program_location>::<kernel_entry_name>
<kernel_entry_name>

*****************************************************************************/

/*
int callCL(const char * _cl_name,
		   int _domainDim, int _domain[], int _group[],
		   ClKrnlArg _args[])
{
int ret = CL_CALL_SUCCESS;
    if (_domainDim < 1 || !_domain || !_group)
	{
       return(CL_CALL_FAILURE);
	}
    if (_cl_name)
	{
// run
	}

    return(ret);
}
*/