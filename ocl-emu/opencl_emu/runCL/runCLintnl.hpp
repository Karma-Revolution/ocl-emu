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
