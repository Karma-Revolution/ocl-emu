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


#ifndef RUNCLINTNL_H_
#define RUNCLINTNL_H_


#include "runCL.h"
#include <SDKUtil/SDKCommon.hpp>
#include <SDKUtil/SDKApplication.hpp>
#include <SDKUtil/SDKCommandArgs.hpp>
#include <SDKUtil/SDKFile.hpp>


// INTERNAL
#define CL_ARG_NOT_INIT             0
#define CL_ARG_LDS_PTR              0x40000000

#define _INIT_NMBR_PROGRAMS 32
#define _INIT_NMBR_KERNELS  32

class ClRunnable;






typedef struct _ClKrnlArgIntnl {
	ClKrnlArg m_extarg;
	cl_mem m_resource;
} ClKrnlArgIntnl;


typedef streamsdk::SDKCommon commonEnv; 
class ClRunInstance {
protected:
	ClRunnable         *m_parent;
    cl_program          m_program;
	char                m_kernel_name[_MAX_KERNEL_NAME];
    cl_kernel           m_kernel;
	size_t              m_nbr_dim;
    size_t              m_domainSize[3];                   /**< domain size */
    size_t              m_groupSize[3];                   /**< Work-Group size */
	int                 m_nbr_args;
    ClKrnlArgIntnl      *m_args;
public:
	ClRunInstance(ClRunnable *_parent, cl_program _program, cl_kernel _kernel, size_t _nbr_dim, size_t _domainSize[3], size_t _groupSize[3], int _nbr_args, ClKrnlArg *_args)
	{
	   setupInstance(_parent, _program, _kernel, _nbr_dim, _domainSize, _groupSize, _nbr_args, _args);
	}
	~ClRunInstance();
	ClRunInstance()
	{
	   m_parent = 0;
	   m_program = 0;
	   m_kernel_name[0] = 0;
       m_kernel = 0;
	   m_nbr_args = 0;
       m_args = 0;
	   m_groupSize[0] = m_groupSize[1] = m_groupSize[2] = 0;
	   m_domainSize[0] = m_domainSize[1] = m_domainSize[2] = 0;
	   m_nbr_dim = 0;

	}
	inline void setRunnable( ClRunnable *_parent )
	{
		m_parent = _parent;
	}
	int setupInstance(ClRunnable *_parent, cl_program _program, cl_kernel _kernel, size_t _nbr_dim, size_t _domainSize[3], size_t _groupSize[3], int _nbr_args, ClKrnlArg *_args);
	int runInstance( void );
	int cleanupInstance( void );
	int cleanupInstanceArgs( void );


	inline  void SetKrnlName( const char * _name )
	{
		strcpy_s(m_kernel_name,_MAX_KERNEL_NAME,_name);
	}

	inline  const char * GetKrnlName( void )
	{
		return(m_kernel_name);
	}

	inline  void SetProgr( cl_program _program )
	{
		m_program = _program;
	}


	inline  cl_program GetProgr( void )
	{
		return(m_program);
	}

	inline  void SetKrnl( cl_kernel _kernel )
	{
		m_kernel = _kernel;
	}


	inline  cl_kernel GetKrnl( void )
	{
		return(m_kernel);
	}
protected:
	int releaseBuf(ClKrnlArgIntnl * _buf_arg);

};


class ClRunnableProgram {
public:

	char m_program_loc[_MAX_PROGRAM_NAME];
    cl_program          m_program;
	int                 m_max_kernels;
	int                 m_nbr_kernels;
	ClRunInstance       *m_kernels;
	ClRunInstance       *m_cachedkernel;

	ClRunnableProgram();
    ~ClRunnableProgram();
	int InstKernelCL(ClRunInstance**_run_kernel,  const char* _kernel_entry_name);
	int FindKernel(const char* _kernel_name, ClRunInstance** _kernel_instance );
	int AddKernel(const char* _kernel_name, cl_kernel _kernel);
	int ResetCache(void);

	inline const char* GetProgramLocation(void)
	{
		return(m_program_loc);
	}

	inline cl_program GetBuiltProgram(void)
	{
		return(m_program);
	}
	inline ClRunInstance *GetLastKernel(void)
	{
		return(m_cachedkernel);
	}
	inline void SetLastKernel(ClRunInstance *_kernel)
	{
		m_cachedkernel = _kernel;
	}

};

class ClRunnable : public SDKSample
{

protected:

	char                m_dev_type[64];
// TEMP
	int                 m_cntxt_counter;


//	ClRunInstance       m_running_instance;
    cl_context          m_context;
    cl_device_id        *m_devices;
    cl_command_queue    m_commandQueue;
	int                 m_max_programs;
	int                 m_nbr_programs;
	ClRunnableProgram   *m_Programs;
	ClRunnableProgram   *m_cachedprogram;


    int                 m_iterations;


    cl_double           m_setupTime;                /**< time taken to setup OpenCL resources and building kernel */
    cl_double           m_kernelTime;               /**< time taken to run kernel and read result back */

    char                m_DeviceName[128];
    size_t              m_maxWorkGroupSize;            /**< Max allowed work-items in a group */
    cl_uint             m_maxDimensions;              /**< Max group dimensions allowed */
    size_t*             m_maxWorkItemSizes;           /**< Max work-items sizes in each dimensions */
    cl_ulong            m_totalLocalMemory;          /**< Max local memory allowed */
    cl_ulong            m_usedLocalMemory;           /**< Used local memory */

public:
    /** 
    * Constructor 
    * Initialize member variables
    * @param name name of sample (const char*)
    */
    explicit ClRunnable(std::string name)
        : SDKSample(name),
	    m_cntxt_counter(0),
        m_setupTime(0),
        m_kernelTime(0),
        m_devices(NULL),
		m_context(0),
		m_commandQueue(0),
		m_cachedprogram(0),
        m_maxWorkItemSizes(NULL),
        m_iterations(1)
	{
		deviceType = name;
		strcpy_s(m_dev_type,64,deviceType.c_str()); 
	    sampleCommon = new streamsdk::SDKCommon();
		m_DeviceName[0] = 0;

	}
    explicit ClRunnable(const char* name)
        : SDKSample(name),
	    m_cntxt_counter(0),
        m_setupTime(0),
        m_kernelTime(0),
        m_devices(NULL),
		m_context(0),
		m_commandQueue(0),
		m_cachedprogram(0),
        m_maxWorkItemSizes(NULL),
        m_iterations(1)
	{
		if ( name )
		{
		   deviceType = name;
		}
		else
		{
			deviceType = "cpu";
		}
		strcpy_s(m_dev_type,64,deviceType.c_str()); 
	    sampleCommon = new streamsdk::SDKCommon();
		m_DeviceName[0] = 0;

	}

	~ClRunnable();
    /**
     * Override from SDKSample, Generate binary image of given kernel 
     * and exit application
     */
    int genBinaryImage()
	{
		return 1;
	};

	inline int IsInit( void )
	{
		return (m_cntxt_counter);
	}

	inline const char* GetDevType(void)
	{
		return(m_dev_type);
	}
	inline commonEnv* GetCommonEnv(void)
	{
        return(sampleCommon);
	}
	inline cl_context GetCntxt( void)
	{
		return m_context;
	}
	inline cl_device_id * GetDevices(void)
	{
		return(m_devices);
	}
	inline cl_command_queue GetCmmdQue( void )
	{
		return(m_commandQueue);
	}

	inline size_t GetMaxWkGrpSz( void)
	{
		return(m_maxWorkGroupSize);
	}
	inline cl_uint GetMaxDim( void)
	{
		return(m_maxDimensions);              /**< Max group dimensions allowed */
	}
    inline size_t* GetMaxWorkItmeSzs(void)
	{
		return(m_maxWorkItemSizes);           /**< Max work-items sizes in each dimensions */
	}
    inline cl_ulong GetTotalLclMem(void)
	{
		return(m_totalLocalMemory);          /**< Max local memory allowed */
	}
    inline ClRunnableProgram  * GetLastProgram(void)
	{
		return(m_cachedprogram);
	}
    inline void SetLastProgram(ClRunnableProgram  * _program)
	{
		m_cachedprogram = _program;
	}

	int ResetCache(void);

	int GetDeviceInfo(cl_device_info param_name,
                      void *param_value);
	int FindProgram(cl_program _program,
		             ClRunnableProgram** _runnable_program );
	int FindProgram(const char* _program_location,
                    const char* _program,
		            ClRunnableProgram** _runnable_program);
	int AddProgram(const char* _program_location,
                    const char* _program_nm,
		           cl_program _program);
	int buildProgramCL(const char* _program_location,
					const char* _program
		            );

    int setupCL(const char *_dev_type = NULL);
    int cleanupCL(void);
    int instKernelCL(ClRunInstance**run_kernel,  ClRunnableProgram *run_program, const char* _kernel_entry_name);
	int setupInstKernelCL(cl_program _program, cl_kernel _kernel, size_t _nbr_dim, size_t _domainSize[3], size_t _groupSize[3], int _nbr_args, ClKrnlArg *_args);
	int runInstKernelCL(const char* _device_name,		                 
		                const char * _kernel_location,
		                const char * _program,
						const char *_kernel_entry_name,
						size_t _nbr_dim,
						size_t _domainSize[3],
						size_t _groupSize[3],
						int _nbr_args,
						ClKrnlArg *_args);

	virtual int initialize()
	{
		return 1;
	};
	virtual int run()
	{
		return 1;
	};
	virtual int cleanup()
	{
		return 1;
	};
	virtual int setup()
	{
		return 1;
	};
	virtual int verifyResults()	
	{
		return 1;
	};

};
#endif // RUNCLINTNL_H_
