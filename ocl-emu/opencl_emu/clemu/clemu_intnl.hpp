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

// clemu_intnl.hpp : 
//

#ifndef _CLEMU_INTNL_HPP
#define _CLEMU_INTNL_HPP


// RUN_TIME/HW
class clemuRunTime;
clemuRunTime* GetRunTime(void);
KERNEL_ENTRY_POINT clemuFindCompiledKernel(
    const char *_program_location, 
	const char *_program_nm,
	const char *_kernel);
int clemuGetCompiledKernelMemSz(KERNEL_ENTRY_POINT _kernel);
void clemu_SetEndOfGroup(void);
void clemu_ScheduleWaveFront(void);
void clemu_ScheduleWfThread(void);
void clemu_ScheduleGrpThread(void);



#define CL_EMU_SUCCESS                  0
#define CL_EMU_FAILURE                  1


class clemuProcessingDevice;
class clemuGPU;
class clemuKernelJob;
class clemuKernelGroup;



/*************************************************************************************
INTERNAL EMU
*************************************************************************************/

#define CLEMU_STACKCOMMITSIZE    2048
#define CLEMU_STACKRESERVESIZE   4096
#define CLEMU_DEVCLASS_NAME_SZ   128
#define CLEMU_DEV_NAME_SZ        128
#define DEFAULTE_PROPERTY_FOLDER  "properties"
#define DEFAULT_DEVCLASS         "evergreen"
//#define DEFAULT_DEVNAME          "Cedar"
#define DEFAULT_DEVNAME          "Redwood"
#define DEFAULT_PROPERTIES_NM    "device_sheet"
#define DEFAULT_EMULATOR_PROPERTIES_NM    "emulator_device_sheet"



static char  *device_properties_nm[] =
{
"se",
"SIMD",
"width",
"local_memory"
};

static char  *emulator_device_properties_nm[] =
{
"se",
"SIMD",
"width",
"local_memory",
"groups_per_SIMD",
0
};


class clemuProcessingDevice {
public:
	virtual int initDevice(void) { return 1;};
};


class clemuGPU : public clemuProcessingDevice
{
protected :
	char m_class[CLEMU_DEVCLASS_NAME_SZ];
	char m_name[CLEMU_DEV_NAME_SZ];
	int m_nbr_groupsperSIMD;
	int m_nbr_SE;
	int m_nbr_SIMD; 
	int m_wavefront_size;
	int m_local_mem_sz;
	__int64 **m_localMem;
	int m_init;
// jobs
    int m_nbr_jobs;
	clemuKernelJob **m_job;

public:
	clemuGPU(const char*_class = 0, const char* _name = 0);
	~clemuGPU();
	inline int GetNbrGroupsPerSIMD(void)
	{
		return(m_nbr_groupsperSIMD);
	}
	inline int GetNbrSE(void)
	{
		return(m_nbr_SE);
	}
	inline int GetNbrSIMD(void)
	{
		return(m_nbr_SIMD);
	}
	inline int GetWFSz(void)
	{
		return(m_wavefront_size);
	}
	inline int GetTotalLclSz( void)
	{
		return(m_local_mem_sz);
	}
	inline void* GetLclMem(int _simd_id)
	{
		return(m_localMem[_simd_id]);
	}
	inline int IsInit( void)
	{
		return(m_init);
	}

	inline const char* GetDevNm( void)
	{
        return(m_name);
	}

	inline const char* GetDevClass( void)
	{
        return(m_class);
	}

	void SetDevClass( const char * _devClass);
	void SetDevNm( const char * _devNm);
	void SetDevWaveWidth( int _wvftWidth);
	void SetDevLclMemSz( int _lclMemSz);

	virtual int initDevice(void);
	int attachJob( clemuKernelJob *_job);
	int detachJob( clemuKernelJob *_job);
    clemuKernelJob *fundJob( int _id );
	int scheduleNextJob(void);
	unsigned char * AssignLclMem(int _simd_id, int _active_group, int _lcl_mem_sz);


protected:
	int cleanupDev( void);

};

typedef struct _CL_EMU_fiber {
public:
	int m_FLS_index;
	void* m_FIBER_id;
	void *m_group_ptr;
    int m_gbl_tid;
    int m_grp_tid;
    int m_wfid;
    int m_wf_tid;
} CL_EMU_FIBER;

class clemuKernelGroup{
friend class clemuKernelJob;
friend class clemuGPU;

protected:
	void *m_parent;
	int m_se_id;
	int m_simd_id;
	int m_group_id;
    int m_grpCoord[3];
	int m_actual_nbr_instances;
	int m_first_hwwavefront;
    int m_curwfid;
	int m_endof_group; // flush
	void *m_localmem_ptr;
	int m_localmem_sz;
    KERNEL_ENTRY_POINT m_kernel;
    CL_EMU_FIBER m_fiber;
	CL_EMU_FIBER *m_wf_fibers;
	CL_EMU_FIBER *m_td_fibers;
    int m_nmb_arg;
    ClKrnlArg * m_args;

public:
	int GetGrpCoord(int _dim);

	inline int GetId(void)
	{
		return(m_group_id);
	}
	inline void* GetParent( void)
	{
		return(m_parent);
	}

	inline CL_EMU_FIBER *GetFiber( void)
	{
		return(&m_fiber);
	}

	inline CL_EMU_FIBER *GetWFiber( int _wf_index)
	{
		return(&m_wf_fibers[_wf_index]);
	}
	inline int IsEndof( void )
	{
		return(m_endof_group);
	}
	inline void SetEndof( int _endof_group )
	{
		m_endof_group = _endof_group;
	}
	CL_EMU_FIBER *GetTFiber( int _wf_index, int _td_index);
	inline void* GetLclMemPtr(void)
	{
		return(m_localmem_ptr);
	}
	inline int GetCurWF(void)
	{
		return(m_curwfid);
	}
	inline void SetCurWF(int _wfid)
	{
        m_curwfid = _wfid;
	}
	inline ClKrnlArg * GerArg(int _index)
	{
		assert(_index>=0 && _index <m_nmb_arg);
		return(&m_args[_index]);
	}
    inline int GetNbrArgs(void)
	{
		return(m_nmb_arg);
	}
    inline KERNEL_ENTRY_POINT GetKernel( void)
	{
		return(m_kernel);
	}

};

class clemuKernelJob{
friend class clemuGPU;
protected:
   void *m_device;
   int m_id;
   int m_nmr_dim;
   int m_grpDim[3];
   int m_domainDim[3];
   int m_actual_nbr_instances;
   int m_nbr_wavefronts;
   int m_last_wavesz;
   int m_nbr_grpDim[3];
   int m_localmem_sz;
   char m_kernel_name[_MAX_KERNEL_NAME];
   KERNEL_ENTRY_POINT m_kernel;
   int m_nmb_arg;
   ClKrnlArg * m_args;
   int m_curgroup;
   int m_nbr_groups;
   int m_next_active_group;
   int m_nbr_active_group;
   clemuKernelGroup * m_groups;
   CL_EMU_FIBER m_fiber;

public:
   clemuKernelJob();
   ~clemuKernelJob();
   int initJob(void *_device,
			   const char * _program_location,
			   const char * _program_nm,
		       const char*_kernel_entry_name,
		       int _domainDim,
			   int _domain[],
			   int _group[],
			   int _nbr_arg,
		       ClKrnlArg _args[]);
   inline void SetId(int _id)
   {
	   m_id = _id;
   }
   inline int GetId(void)
   {
	   return(m_id);
   }
   inline void SetDev(void *_device)
   {
	   m_device = _device;
   }
   inline void* GetDev(void)
   {
	   return(m_device);
   }
   int GetNmbrDim(void);
   inline int GetDomainSz(int _dim)
   {
	int ret = (_dim > m_nmr_dim - 1 || _dim < 0)? 0:m_domainDim[_dim];
	   return(ret);
   }
   inline int GetGroupSz(int _dim)
   {
	int ret = (_dim > m_nmr_dim - 1 || _dim < 0)? 0:m_grpDim[_dim];
	   return(ret);
   }
   inline int GetNbrGroupSz(int _dim)
   {
	int ret = (_dim > m_nmr_dim - 1 || _dim < 0)? 0:m_nbr_grpDim[_dim];
	   return(ret);
   }

   inline clemuKernelGroup *GetGroup(int _index)
   {
      return(&m_groups[_index]);
   }
   inline int GetNbrGroups(void)
   {
	   return(m_nbr_groups);
   }
	inline CL_EMU_FIBER *GetFiber( void)
	{
		return(&m_fiber);
	}

	inline int GetNbrWavefronts(void)
	{
        return(m_nbr_wavefronts);
	}
	inline ClKrnlArg * GerArg(int _index)
	{
		return(&m_args[_index]);
	}
	inline int GetNbrInstances(void)
	{
		return(m_actual_nbr_instances);
	}
	inline int GetRealWFSz(int _wf_id)
	{
int ret = (_wf_id < GetNbrWavefronts() - 1) ? ((clemuGPU*)GetDev())->GetWFSz() : m_last_wavesz;
		return(ret);
	}

    inline KERNEL_ENTRY_POINT GetKernel( void)
	{
		return(m_kernel);
	}
	
    int  FreeJob(void);
protected:
   int cleanupJob( void);
};



#endif // _CLEMU_INTNL_HPP