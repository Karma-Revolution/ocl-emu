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

// clemu.cpp : Defines the entry point for the console application.
//

#include "clemu.hpp"
#include "clemu_cltypes_intrinsics.h"

/*************************************************************************************
INTERNAL
*************************************************************************************/
static VOID 
__stdcall clemu_wavefrontthread_proc ( LPVOID lpParameter )
{
CL_EMU_FIBER *pFiber = (CL_EMU_FIBER *)GetFiberData();
clemuKernelGroup * group = (clemuKernelGroup * )pFiber->m_group_ptr;
//clemuKernelJob *job = (clemuKernelJob *)(group->GetParent());
KERNEL_ENTRY_POINT kernel_entry = 0;
    kernel_entry = group->GetKernel();
//	while(true)
	{
       kernel_entry(lpParameter);
	   clemu_SetEndOfGroup();
       clemu_ScheduleGrpThread();
	}
}

static VOID 
__stdcall clemu_groupthread_proc ( LPVOID lpParameter )
{
clemuKernelGroup *group = (clemuKernelGroup *)lpParameter;
clemuKernelJob *job = (clemuKernelJob *)(group->GetParent());
int curwfid = 0;
//	while(true)
	{
       group->SetCurWF(curwfid);
// PROCESS GROUP HERE
       while(!group->IsEndof() || (job->GetNbrWavefronts() > curwfid) )
       {
            curwfid = group->GetCurWF();
// switch to the first thread of a wavefront
            SwitchToFiber(group->GetTFiber(curwfid, 0)->m_FIBER_id);

// select new wf
			curwfid = (group->IsEndof()) ? (curwfid + 1) : (curwfid + 1) % job->GetNbrWavefronts(); 
            group->SetCurWF(curwfid);

        }

// back to scheduler
        SwitchToFiber(job->GetFiber()->m_FIBER_id);
	}
   

}

void clemu_SetEndOfGroup(void)
{
CL_EMU_FIBER *pFiber = (CL_EMU_FIBER *)GetFiberData();
clemuKernelGroup * group = (clemuKernelGroup * )pFiber->m_group_ptr;
     group->SetEndof(1);

}


void clemu_ScheduleThread(int _group)
{
CL_EMU_FIBER *pFiber = (CL_EMU_FIBER *)GetFiberData();
clemuKernelGroup * group = (clemuKernelGroup * )pFiber->m_group_ptr;
clemuKernelJob *job = (clemuKernelJob *)(group->GetParent());
int wf_sz = job->GetRealWFSz(pFiber->m_wfid);
CL_EMU_FIBER *pNextFiber = 0;
int new_thread = (pFiber->m_wf_tid + 1) % wf_sz;
   if (!_group || (_group && new_thread > 0 ))
   {
// wrap around the wavefront
      pNextFiber = group->GetTFiber(pFiber->m_wfid, new_thread);
   }
   else
   {
// reshcedule wavefront
       pNextFiber = group->GetFiber();
   }

   SwitchToFiber(pNextFiber->m_FIBER_id);

}


void clemu_ScheduleWfThread(void)
{
	clemu_ScheduleThread(0);
}

void clemu_ScheduleGrpThread(void)
{
	clemu_ScheduleThread(1);
}



/*************************************************************************************
clemuGPU
*************************************************************************************/
clemuGPU :: clemuGPU(const char*_class, const char* _name)
{
   m_name[0] = 0;
   m_class[0] = 0;
   if (_name)
   {
	   strcpy_s(m_name,CLEMU_DEV_NAME_SZ,_name);
   }
   if ( m_name[0] == 0 )
   {
	   strcpy_s(m_name,CLEMU_DEV_NAME_SZ,DEFAULT_DEVNAME);
   }
   if (_class)
   {
	   strcpy_s(m_class,CLEMU_DEVCLASS_NAME_SZ,_class);
   }
   if ( m_class[0] == 0)
   {
	   strcpy_s(m_class,CLEMU_DEV_NAME_SZ,DEFAULT_DEVCLASS);
   }


   m_nbr_groupsperSIMD = 2;
   m_nbr_SE = 1;
   m_nbr_SIMD = 1;
   m_wavefront_size = 64;
   m_local_mem_sz = (1 << 15);
   m_nbr_jobs = 0;
   m_job = 0;
   m_init = 0;
   m_localMem = 0;


}
clemuGPU :: ~clemuGPU(void)
{
   cleanupDev();
}


int 
clemuGPU :: attachJob( clemuKernelJob *_job)
{
int ret = CL_EMU_SUCCESS;
// TO DO: GROWING ARRAY
   if ( m_nbr_jobs == 0 )
   {
      m_job = new clemuKernelJob *[1];
      m_job[m_nbr_jobs] = _job;
      m_job[m_nbr_jobs]->SetId(m_nbr_jobs);
      m_job[m_nbr_jobs]->SetDev(this);
      m_nbr_jobs = 1;
   }
   return(ret);
}
int 
clemuGPU :: detachJob( clemuKernelJob *_job)
{
int ret = CL_EMU_SUCCESS;
   m_job[0] = 0;
   m_nbr_jobs = 0;
   return(ret);
}

clemuKernelJob *
clemuGPU :: fundJob( int _id )
{
   return(m_job[0]);
}


int 
clemuGPU :: scheduleNextJob(void)
{
int ret = CL_EMU_SUCCESS;
// TO DO : SELECT JOB
// SELECT SE, SIMD
clemuKernelJob *nextJob = m_job[0];
int cur_gbl_tid;
clemuGPU* dev = (clemuGPU*)(nextJob->GetDev());

   nextJob->m_next_active_group = 0;
   nextJob->m_fiber.m_FIBER_id = ConvertThreadToFiberEx(nextJob,FIBER_FLAG_FLOAT_SWITCH);
   nextJob->m_fiber.m_FLS_index = 0;

// TO DO: NBR GROUPS > SIMDS
// run
   for(int j = 0, grp_id = 0, wf_id = 0; j < nextJob->m_nbr_grpDim[1]; j++)
   {
      for(int i = 0; i < nextJob->m_nbr_grpDim[0]; i++, grp_id++, wf_id += nextJob->m_nbr_wavefronts)
	  {
int active_grp = nextJob->m_next_active_group;
// activate

		  if ( !nextJob->m_groups[active_grp].m_fiber.m_FIBER_id )
		  {
		       nextJob->m_groups[active_grp].m_fiber.m_FIBER_id = 
			               CreateFiberEx( CLEMU_STACKCOMMITSIZE,
                                           CLEMU_STACKRESERVESIZE,
										   FIBER_FLAG_FLOAT_SWITCH,
										   clemu_groupthread_proc,
										   &nextJob->m_groups[active_grp]);

			   assert(nextJob->m_groups[active_grp].m_fiber.m_FIBER_id);
		       nextJob->m_groups[active_grp].m_fiber.m_FLS_index = 0;
		  }

		  if ( !nextJob->m_groups[active_grp].m_td_fibers )
		  {
	           nextJob->m_groups[active_grp].m_td_fibers = new CL_EMU_FIBER[nextJob->GetNbrInstances()];
		       assert(nextJob->m_groups[active_grp].m_td_fibers);
        	   memset(nextJob->m_groups[active_grp].m_td_fibers, 0, sizeof(CL_EMU_FIBER) * nextJob->GetNbrInstances()); 
		  }

		  for(int l = 0, tid = 0; l < nextJob->GetNbrWavefronts(); l++)
		  {
			  int wf_sz = nextJob->GetRealWFSz(l);
			  for(int m = 0; m < wf_sz; m++, tid++)
			  {
				  if ( !nextJob->m_groups[active_grp].m_td_fibers[l*wf_sz + m].m_FIBER_id )
				  {
                     nextJob->m_groups[active_grp].m_td_fibers[l*wf_sz + m].m_FIBER_id = 
						    CreateFiberEx( CLEMU_STACKCOMMITSIZE,
                                           CLEMU_STACKRESERVESIZE,
										   FIBER_FLAG_FLOAT_SWITCH,
						                   clemu_wavefrontthread_proc,
										   &nextJob->m_groups[active_grp].m_td_fibers[l*wf_sz + m]);

					 assert(nextJob->m_groups[active_grp].m_td_fibers[l*wf_sz + m].m_FIBER_id);

				     nextJob->m_groups[active_grp].m_td_fibers[l*wf_sz + m].m_FLS_index = 0; //FlsAlloc(0);
				     nextJob->m_groups[active_grp].m_td_fibers[l*wf_sz + m].m_group_ptr = &nextJob->m_groups[active_grp];
				  }

			  }
		  }



          nextJob->m_groups[active_grp].m_parent = nextJob;
		  nextJob->m_groups[active_grp].m_grpCoord[0] = i;
		  nextJob->m_groups[active_grp].m_grpCoord[1] = j;
		  nextJob->m_groups[active_grp].m_grpCoord[2] = 0;
		  nextJob->m_groups[active_grp].m_group_id = grp_id;
		  nextJob->m_groups[active_grp].m_se_id = 0;
		  nextJob->m_groups[active_grp].m_simd_id = active_grp % dev->GetNbrSIMD();
	      nextJob->m_groups[active_grp].m_first_hwwavefront = wf_id;

		  cur_gbl_tid = grp_id * nextJob->m_actual_nbr_instances;
          nextJob->m_groups[active_grp].m_kernel = nextJob->GetKernel();
		  nextJob->m_groups[active_grp].m_endof_group = 0;
// local memory setup
// EXPLANATION:
// The size comes either from invokation (argument) or from teh kernel declaration.
// if it comes from declaration for teh first group there will be 0 sz which is max size.
// second group will det the correect size and will be separated from teh first group
int local_mem_sz = (nextJob->m_localmem_sz > clemuGetCompiledKernelMemSz(nextJob->m_groups[active_grp].m_kernel)) ? nextJob->m_localmem_sz : clemuGetCompiledKernelMemSz(nextJob->m_groups[active_grp].m_kernel);
		  nextJob->m_groups[active_grp].m_localmem_sz = local_mem_sz;
		  nextJob->m_groups[active_grp].m_localmem_ptr = (unsigned char*)dev->AssignLclMem(nextJob->m_groups[active_grp].m_simd_id,active_grp,local_mem_sz); 
		  if ( nextJob->m_groups[active_grp].m_nmb_arg > 0 )
          {
		       for( int l = 0; l < nextJob->m_groups[active_grp].m_nmb_arg; l++)
		       {
		           if ( (nextJob->m_groups[active_grp].m_args[l].m_flags & CL_ARG_LCL_MEM_SZ) == CL_ARG_LCL_MEM_SZ )
		           {
					   nextJob->m_groups[active_grp].m_args[l].m_flags |= CL_ARG_LDS_PTR;
					   nextJob->m_groups[active_grp].m_args[l].m_arg.parg = nextJob->m_groups[active_grp].m_localmem_ptr;
					   break;
		           }
		       }
          }

//		  nextJob->m_groups[grp_id].m_wf_fibers = new CL_EMU_FIBER[nextJob->m_nbr_wavefronts];
//		  assert(nextJob->m_groups[grp_id].m_wf_fibers);
		  if ( !nextJob->m_groups[active_grp].m_td_fibers )
		  {
	           nextJob->m_groups[active_grp].m_td_fibers = new CL_EMU_FIBER[nextJob->m_actual_nbr_instances];
		       assert(nextJob->m_groups[active_grp].m_td_fibers);
		  }


		  for(int l = 0, tid = 0; l < nextJob->m_nbr_wavefronts; l++)
		  {
			  int wf_sz = nextJob->GetRealWFSz(l);
			  for(int m = 0; m < wf_sz; m++, tid++)
			  {
                  nextJob->m_groups[active_grp].m_td_fibers[l*wf_sz + m].m_grp_tid = l * wf_sz + m;
                  nextJob->m_groups[active_grp].m_td_fibers[l*wf_sz + m].m_gbl_tid = cur_gbl_tid + nextJob->m_groups[active_grp].m_td_fibers[l*wf_sz + m].m_grp_tid;
                  nextJob->m_groups[active_grp].m_td_fibers[l*wf_sz + m].m_wfid = l;
                  nextJob->m_groups[active_grp].m_td_fibers[l*wf_sz + m].m_wf_tid = m;
			  }
		  }

// schedule group
          nextJob->m_curgroup = active_grp;

		  SwitchToFiber(nextJob->m_groups[active_grp].m_fiber.m_FIBER_id);
// free

		  if ( nextJob->m_groups[active_grp].m_td_fibers )
		  {
		       for(int l = 0, tid = 0; l < nextJob->GetNbrWavefronts(); l++)
		       {
			  int wf_sz = nextJob->GetRealWFSz(l);
			       for(int m = 0; m < wf_sz; m++, tid++)
			       {
				       if ( nextJob->m_groups[active_grp].m_td_fibers[l*wf_sz + m].m_FIBER_id )
				       {
                           DeleteFiber(nextJob->m_groups[active_grp].m_td_fibers[l*wf_sz + m].m_FIBER_id);
					       nextJob->m_groups[active_grp].m_td_fibers[l*wf_sz + m].m_FIBER_id = 0;
				        }

			        }
		       }
	           delete [] nextJob->m_groups[active_grp].m_td_fibers;
		       nextJob->m_groups[active_grp].m_td_fibers = 0;
		  }
		  if ( nextJob->m_groups[active_grp].m_fiber.m_FIBER_id )
		  {
		      DeleteFiber(nextJob->m_groups[active_grp].m_fiber.m_FIBER_id);
		      nextJob->m_groups[active_grp].m_fiber.m_FIBER_id = 0;
		  }

          nextJob->m_next_active_group = (active_grp + 1) %  nextJob->m_nbr_active_group;
	  }
   }

   nextJob->FreeJob();

   ConvertFiberToThread();
   nextJob->m_fiber.m_FIBER_id = 0;

   return(ret);

}


int
clemuGPU :: initDevice(void)
{
int ret = CL_EMU_SUCCESS;
   if ( !IsInit())
   {


 char  *env_root;
 size_t var_len;
 char root_location[512];
 char propert_file_location[512];
 FILE * property_file;



      _dupenv_s(&env_root,&var_len, "CLEMU_ROOT");
 
	  assert(var_len > 0);
	  if ( !var_len )
	  {
        return(CL_EMU_FAILURE);
	  }
	  strcpy_s(root_location, 512,env_root);
      if ( root_location[var_len-1] != '\\' )
	  {
         root_location[var_len-1] = '\\';
         root_location[var_len] = 0;
	  }
    
      sprintf_s(propert_file_location,512,"%s%s\\%s.txt", root_location, DEFAULTE_PROPERTY_FOLDER, DEFAULT_EMULATOR_PROPERTIES_NM);
	  property_file = fopen( propert_file_location,"rt");
	  if ( property_file )
	  {
char in_buffer[512];
char data_buffer[512];
char format_buffer[512];
int class_len = strlen("class=");
int found_class, found_device;

          fgets( in_buffer, 512, property_file);
          sscanf(in_buffer, "emu_class=%s\n",  data_buffer);
		  SetDevClass( (const char * )data_buffer);

          fgets( in_buffer, 512, property_file);
          sscanf(in_buffer, "emu_name=%s\n",  data_buffer);
		  SetDevNm( (const char * )data_buffer);

          found_class = 0;
		  while(fgets( in_buffer, 512, property_file))
		  {
             sscanf(in_buffer, "class=%s\n",  data_buffer);
			 if  (!strcmp(data_buffer, m_class))
			 {
                    found_class = 1;
				    break;
			 }
		  }

		  if ( found_class )
		  {
               found_device = 0;
		       while(fgets( in_buffer, 512, property_file))
		       {
                    sscanf(in_buffer, "name=%s\n",  data_buffer);
			        if  (!strcmp(data_buffer, m_name))
			        {
                         found_device = 1;
				         break;
			        }
		       }
			   if ( found_device )
			   {
		    int propery;
/*
   m_nbr_groupsperSIMD = 2;
   m_nbr_SE = 1;
   m_nbr_SIMD = 1;
   m_wavefront_size = 64;
   m_local_mem_sz = (1 << 15);
*/

				   for(int p = 0; emulator_device_properties_nm[p]; p++)
				   {
				      sprintf_s(format_buffer,512,"%s.%s=%%d\n", m_name,emulator_device_properties_nm[p]);
                      fscanf(property_file, format_buffer,  &propery);
                      if ( !strcmp(emulator_device_properties_nm[p], "se" ) )
					  {
                          m_nbr_SE = propery;
					  }
                      if ( !strcmp(emulator_device_properties_nm[p], "SIMD" ) )
					  {
						  m_nbr_SIMD = propery;
					  }
                      if ( !strcmp(emulator_device_properties_nm[p], "width" ) )
					  {
						  m_wavefront_size = propery;
					  }
                      if ( !strcmp(emulator_device_properties_nm[p], "local_memory" ) )
					  {
						  m_local_mem_sz = propery;
					  }
                      if ( !strcmp(emulator_device_properties_nm[p], "groups_per_SIMD" ) )
					  {
						  m_nbr_groupsperSIMD = propery;
					  }

				   }
				   

// ALIGNED??
                    m_localMem = new __int64*[GetNbrSIMD()];
	                assert(m_localMem);
	                for(int i = 0; i < GetNbrSIMD(); i++)
	                {
                        m_localMem[i] = (__int64*)new __int64[GetTotalLclSz()];
	                    assert(m_localMem[i]);
	                }
	                m_init = 1;
			   }
		  }
		fclose(property_file);
	  }
   }
   return(ret);
}

void clemuGPU :: SetDevClass( const char * _devClass)
{
     strcpy_s(m_class,CLEMU_DEVCLASS_NAME_SZ,_devClass);
}

void clemuGPU :: SetDevNm( const char * _devNm)
{
	   strcpy_s(m_name,CLEMU_DEV_NAME_SZ,_devNm);
}



unsigned char * 
clemuGPU :: AssignLclMem(int _simd_id, int _active_group, int _lcl_mem_sz)
{
unsigned char * ret = 0;
int nbrSIMD = GetNbrSIMD();
int simd_group = (_active_group+nbrSIMD-1) / nbrSIMD;
   ret = (unsigned char*)GetLclMem(_simd_id) + simd_group * _lcl_mem_sz;
   return(ret);
}

int 
clemuGPU :: cleanupDev( void)
{
int ret = CL_EMU_SUCCESS;
   if ( m_job )
   {
        for(int i = 0; i < m_nbr_jobs; i++)
        {
	       if ( m_job[i] )
	       {
		       delete m_job[i];
	       }
		}
		m_nbr_jobs = 0;
        delete [] m_job;
		m_job = 0;
   }
   if ( m_localMem )
   {
	   for(int i = 0; i < GetNbrSIMD(); i++)
	   {
		   delete[] m_localMem[i];
	   }
	   delete [] m_localMem;
	   m_localMem = 0;
   }
   return(ret);
}




/*************************************************************************************
clemuKernelJob
*************************************************************************************/
clemuKernelJob :: clemuKernelJob(void)
{
   m_device = 0;
   m_id = -1;
   m_nbr_active_group = 0;
   m_nbr_groups = 0;
   m_groups = 0;
   m_nbr_grpDim[0] = m_nbr_grpDim[1] = m_nbr_grpDim[2] = 1;
   m_kernel_name[0] = 0;
   m_nmb_arg = 0;
   m_kernel = 0;

}

clemuKernelJob :: ~clemuKernelJob(void)
{
	cleanupJob();
}

int 
clemuKernelJob :: initJob(void *_device,
				const char * _program_location,
				const char * _program_nm,
		       const char*_kernel_entry_name,
		       int _domainDim,
			   int _domain[],
			   int _group[],
			   int _nmr_arg,
		       ClKrnlArg _args[])
{
int ret = CL_EMU_SUCCESS;
int actual_nbr_instances = 1;
clemuGPU *dev = (clemuGPU*)_device;
int nbr_wavefronts;

// TO AVOID MEM FAULT
    SetDev(dev);


    for( int i = 0; i < _domainDim; i++)
	{
	     m_nbr_grpDim[i] = (_domain[i] + _group[i] - 1) / _group[i];
		 actual_nbr_instances *= _group[i]; 
	}

	m_nbr_groups = m_nbr_grpDim[0] * m_nbr_grpDim[1] * m_nbr_grpDim[2];

    nbr_wavefronts = (actual_nbr_instances + dev->GetWFSz() - 1) / dev->GetWFSz();
	m_nmr_dim = _domainDim;
    m_grpDim[0] = m_grpDim[1] = m_grpDim[2] = 1;
    m_domainDim[0] = m_domainDim[1] = m_domainDim[2] = 1;
    for(int k = 0; k < _domainDim; k++)
    {
	    m_grpDim[k] = _group[k];
	    m_domainDim[k] = m_nbr_grpDim[k] * _group[k];
    }
	m_actual_nbr_instances = actual_nbr_instances;
    m_nbr_wavefronts = nbr_wavefronts;

    strcpy_s(m_kernel_name,_MAX_KERNEL_NAME,_kernel_entry_name);

// BIND KERNEL
    m_kernel = clemuFindCompiledKernel(_program_location,
		                               _program_nm,
									   _kernel_entry_name);

	m_args = 0;
	m_nmb_arg = _nmr_arg;
	m_localmem_sz = 0;
    if ( m_nmb_arg > 0 )
    {
        m_args = new ClKrnlArg[m_nmb_arg];
	    assert(m_args);
		for( int l = 0; l < m_nmb_arg; l++)
		{
           m_args[l] = _args[l];
		   m_args[l].arg_ptr = &m_args[l].m_arg.iarg;

		   if ( (m_args[l].m_flags & CL_ARG_LCL_MEM_SZ) == CL_ARG_LCL_MEM_SZ )
		   {
			   m_localmem_sz = m_args[l].m_len;
		   }

		}
    }

    m_last_wavesz = actual_nbr_instances % dev->GetWFSz(); 
	m_last_wavesz = (m_last_wavesz == 0 ) ? dev->GetWFSz() : m_last_wavesz;

    assert(m_kernel);
    m_nbr_active_group = dev->GetNbrSIMD() * dev->GetNbrGroupsPerSIMD();

	if ( !m_groups )
	{
	    m_groups = new clemuKernelGroup[m_nbr_active_group];
	    assert(m_groups);
		memset(m_groups, 0, sizeof(clemuKernelGroup)*m_nbr_active_group); 
	}


    for(int j = 0; j < m_nbr_active_group; j++)
	{
          m_groups[j].m_parent = this;
		  m_groups[j].m_kernel = m_kernel;
#if 0
		  if ( !m_groups[j].m_fiber.m_FIBER_id )
		  {
		       m_groups[j].m_fiber.m_FIBER_id = 
			               CreateFiberEx( CLEMU_STACKCOMMITSIZE,
                                           CLEMU_STACKRESERVESIZE,
										   FIBER_FLAG_FLOAT_SWITCH,
										   clemu_groupthread_proc,
										   &m_groups[j]);

			   assert(m_groups[j].m_fiber.m_FIBER_id);
		       m_groups[j].m_fiber.m_FLS_index = 0;
		  }

		  if ( !m_groups[j].m_td_fibers )
		  {
	           m_groups[j].m_td_fibers = new CL_EMU_FIBER[m_actual_nbr_instances];
		       assert(m_groups[j].m_td_fibers);
        	   memset(m_groups[j].m_td_fibers, 0, sizeof(CL_EMU_FIBER) * m_actual_nbr_instances); 
		  }

		  for(int l = 0, tid = 0; l < m_nbr_wavefronts; l++)
		  {
			  int wf_sz = GetRealWFSz(l);
			  for(int m = 0; m < wf_sz; m++, tid++)
			  {
				  if ( !m_groups[j].m_td_fibers[l*wf_sz + m].m_FIBER_id )
				  {
                     m_groups[j].m_td_fibers[l*wf_sz + m].m_FIBER_id = 
						    CreateFiberEx( CLEMU_STACKCOMMITSIZE,
                                           CLEMU_STACKRESERVESIZE,
										   FIBER_FLAG_FLOAT_SWITCH,
						                   clemu_wavefrontthread_proc,
										   &m_groups[j].m_td_fibers[l*wf_sz + m]);

					 assert(m_groups[j].m_td_fibers[l*wf_sz + m].m_FIBER_id);

				     m_groups[j].m_td_fibers[l*wf_sz + m].m_FLS_index = 0; //FlsAlloc(0);
				     m_groups[j].m_td_fibers[l*wf_sz + m].m_group_ptr = &m_groups[j];
				  }

			  }
		  }
#endif
// replicate arguments
		  if ( !m_groups[j].m_args && m_nmb_arg > 0 )
		  {
			  m_groups[j].m_nmb_arg = m_nmb_arg;
              m_groups[j].m_args = new ClKrnlArg[m_nmb_arg];
			  memset(m_groups[j].m_args, 0, sizeof(ClKrnlArg) * m_nmb_arg);
		  }

		  for( int l = 0; l < m_nmb_arg; l++)
		  {
              memcpy(&m_groups[j].m_args[l], &m_args[l], sizeof(ClKrnlArg));
		  }

	}


   return(ret);
}

int 
clemuKernelJob :: FreeJob(void)
{
int ret = CL_EMU_SUCCESS;

    for(int j = 0; j < m_nbr_active_group; j++)
	{
		  if ( m_groups[j].m_td_fibers )
		  {
		      for(int l = 0, tid = 0; l < m_nbr_wavefronts; l++)
		      {
			     int wf_sz = GetRealWFSz(l);
			     for(int m = 0; m < wf_sz; m++, tid++)
			     {
				     if ( m_groups[j].m_td_fibers[l*wf_sz + m].m_FIBER_id )
				     {
                         DeleteFiber(m_groups[j].m_td_fibers[l*wf_sz + m].m_FIBER_id);
					     m_groups[j].m_td_fibers[l*wf_sz + m].m_FIBER_id = 0;
				     }

			     }
		      }
	          delete [] m_groups[j].m_td_fibers;
		      m_groups[j].m_td_fibers = 0;
		  }

		  if ( m_groups[j].m_fiber.m_FIBER_id )
		  {
		      DeleteFiber(m_groups[j].m_fiber.m_FIBER_id);
		      m_groups[j].m_fiber.m_FIBER_id = 0;
		  }

          if ( m_groups[j].m_args )
		  {
			  delete [] m_groups[j].m_args;
			  m_groups[j].m_args = 0;
			  m_groups[j].m_nmb_arg = 0;
		  }

	}

   return(ret);

}

int
clemuKernelJob :: cleanupJob( void)
{
int ret = CL_EMU_SUCCESS;
   if ( m_args )
   {

	   delete [] m_args;
	   m_args = 0;
	   m_nmb_arg = 0;
   }
   if ( m_groups )
   {
	   delete [] m_groups;
	   m_groups = 0;
   }
   m_nbr_active_group = 0;
   m_nbr_groups = 0;
   return(ret);

}

int
clemuKernelJob :: GetNmbrDim(void)
{
   return(m_nmr_dim);
}





/*************************************************************************************
clemuKernelGroup
*************************************************************************************/
CL_EMU_FIBER *
clemuKernelGroup::GetTFiber( int _wf_index, int _td_index)
{
clemuKernelJob *job = (clemuKernelJob * )m_parent;
clemuGPU *dev = (clemuGPU *)(job->GetDev());
int wf_sz = dev->GetWFSz();
   return(&m_td_fibers[_wf_index*wf_sz + _td_index]);
}

int
clemuKernelGroup::GetGrpCoord(int _dim)
{
clemuKernelJob* job = (clemuKernelJob* )GetParent();
	
int ret = (_dim < 0 || _dim > job->GetNmbrDim()) ? 0 : m_grpCoord[_dim];
	return(ret);
}

/*************************************************************************************
 
*************************************************************************************/
//static clemuGPU *sDevices[] = {0}; 
/*************************************************************************************
EXTERNAL
*************************************************************************************/
int getEmuDevParameter( void*_pParam, int _paramId)
{
clemuGPU * clDevice;
cl_int status = SDK_FAILURE;

 clDevice = (clemuGPU * )GetRunTime()->GetActiveDev(0);

    if (clDevice)
	{
      switch( _paramId )
	  {
	  case CLEMU_PARAM_DEV_NAME:
		  (*(const char**)_pParam) = clDevice->GetDevNm();
		  break;
	  }
      status = SDK_SUCCESS;
	}

	return(status);
}

int runCLEMU(const char * _device_type,
		   int _domainDim,
		   int _domain[],
		   int _group[],
		   const char * _program_location,
		   const char * _program_nm,
		   const char*_kernel_entry_name,
		   int _nbr_arg,
		   ClKrnlArg _args[])
{
clemuGPU * clDevice;
 cl_int status = SDK_SUCCESS;

 clDevice = (clemuGPU * )GetRunTime()->GetActiveDev(0);

clemuKernelJob *newJob;
   newJob = new clemuKernelJob;
   assert(newJob);
   newJob->initJob(clDevice,
	               _program_location,
                   _program_nm,
		           _kernel_entry_name,
		           _domainDim,
				   _domain,
				   _group,
				   _nbr_arg,
		           _args);
   clDevice->attachJob(newJob);
   clDevice->scheduleNextJob();

// delete job
clemuKernelJob *oldJob;
   oldJob = clDevice->fundJob(newJob->GetId());
   clDevice->detachJob(oldJob);
   delete oldJob;
   return(status);
}

int cleanupCLEMU(const char * _device_type)
{
cl_int status = SDK_SUCCESS;
// clean run time or/and device?

   return(status);
}


