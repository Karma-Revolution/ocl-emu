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