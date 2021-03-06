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


#include "NBodyEmu.hpp"
#include<GL/glut.h>
#include <cmath>
#include<malloc.h>


#define DEFAULT_KERNEL_LOCATION "./"


/**************************************************************************************************
   NBody
**************************************************************************************************/
int numBodies;      /**< No. of particles*/
cl_float* pos;      /**< Output position */
void* me;           /**< Pointing to NBody class */
cl_bool display;

float
NBody::random(float randMax, float randMin)
{
    float result;
    result =(float)rand()/(float)RAND_MAX;

    return ((1.0f - result) * randMin + result *randMax);
}

int
NBody::compareArray(const float* mat0,
                    const float* mat1,
                    unsigned int size)
{
    const float epsilon = (float)1e-2;
    for (unsigned int i = 0; i < size; ++i)
    {
        float val0 = mat0[i];
        float val1 = mat1[i];

        float diff = (val1 - val0);
        if (fabs(val1) > epsilon)
        {
            diff /= val0;
        }

        return (fabs(diff) > epsilon);
    }

    return 0;
}

int
NBody::setupNBody()
{
    // make sure numParticles is multiple of group size
    numParticles = (cl_int)(((size_t)numParticles 
        < groupSize) ? groupSize : numParticles);
    numParticles = (cl_int)((numParticles / groupSize) * groupSize);

    numBodies = numParticles;

    initPos = (cl_float*)malloc(numBodies * sizeof(cl_float4));
    if(initPos == NULL)	
    { 
        sampleCommon->error("Failed to allocate host memory. (initPos)");
        return SDK_FAILURE;
    }

    initVel = (cl_float*)malloc(numBodies * sizeof(cl_float4));
    if(initVel == NULL)	
    { 
        sampleCommon->error("Failed to allocate host memory. (initVel)");
        return SDK_FAILURE;
    }

#if defined (_WIN32)
    pos = (cl_float*)_aligned_malloc(numBodies * sizeof(cl_float4), 16);
#else
    pos = (cl_float*)memalign(16, numBodies * sizeof(cl_float4));
#endif
    if(pos == NULL)
    { 
        sampleCommon->error("Failed to allocate host memory. (pos)");
        return SDK_FAILURE;
    }

#if defined (_WIN32)
    vel = (cl_float*)_aligned_malloc(numBodies * sizeof(cl_float4), 16);
#else
    vel = (cl_float*)memalign(16, numBodies * sizeof(cl_float4));
#endif

    if(vel == NULL)
    { 
        sampleCommon->error("Failed to allocate host memory. (vel)");
        return SDK_FAILURE;
    }

    /* initialization of inputs */
    for(int i = 0; i < numBodies; ++i)
    {
        int index = 4 * i;

        // First 3 values are position in x,y and z direction
        for(int j = 0; j < 3; ++j)
        {
            initPos[index + j] = random(3, 50);
        }

        // Mass value
        initPos[index + 3] = random(1, 1000);

        // First 3 values are velocity in x,y and z direction
        for(int j = 0; j < 3; ++j)
        {
            initVel[index + j] = 0.0f;
        }

        // unused
        initVel[3] = 0.0f;
    }

    memcpy(pos, initPos, 4 * numBodies * sizeof(cl_float));
    memcpy(vel, initVel, 4 * numBodies * sizeof(cl_float));

    return SDK_SUCCESS;
}

int
NBody::setupCL()
{
 cl_int status = CL_SUCCESS;
    return SDK_SUCCESS;
}


int 
NBody::setupCLKernels()
{


    return SDK_SUCCESS;
}

int 
NBody::runCLKernels()
{
    cl_int status;
	ClKrnlArg Args[1024];

   /* Set appropriate arguments to the kernel */


    /* Create memory objects for position */
	_ArgFirst(Args, CL_ARG_INPUTOUTPUT_PTR | CL_ARG_POPULATE_PTR,cl_float*,pos, numBodies * sizeof(cl_float4));
    /* Create memory objects for velocity */
	_Arg(Args,CL_ARG_INPUTOUTPUT_PTR | CL_ARG_POPULATE_PTR,cl_float*,vel,numBodies * sizeof(cl_float4));
    /* numBodies */
	_Arg(Args,CL_ARG_VALUE,cl_int,numBodies, sizeof(cl_int));
   /* time step */
	_Arg(Args,CL_ARG_VALUE,cl_float,delT, sizeof(cl_float));
    /* upward Pseudoprobability */
	_ArgLast(Args,CL_ARG_VALUE,cl_float,espSqr, sizeof(cl_float));
    /* local memory */
//	_ArgLast(Args,CL_ARG_LCL_MEM_SZ,int,GROUP_SIZE * 4 * sizeof(float),sizeof(int));


int globalThreads[] = {numBodies};
int localThreads[] = {groupSize};


	status = callCL(deviceType.c_str(), 1, globalThreads, localThreads, DEFAULT_KERNEL_LOCATION, "NBodyEmu_Kernels.cpp", "nbody_sim",  Args);
//	status = callCL("gpu_emu", 1, globalThreads, localThreads, "FaceRecogn_Kernels.cpp", "nbody_sim",  Args);

    return SDK_SUCCESS;
}

/*
* n-body simulation on cpu
*/
void 
NBody::nBodyCPUReference()
{
    //Iterate for all samples
    for(int i = 0; i < numBodies; ++i)
    {
        int myIndex = 4 * i;
        float acc[3] = {0.0f, 0.0f, 0.0f};
        for(int j = 0; j < numBodies; ++j)
        {
            float r[3];
            int index = 4 * j;

            float distSqr = 0.0f;
            for(int k = 0; k < 3; ++k)
            {
                r[k] = refPos[index + k] - refPos[myIndex + k];

                distSqr += r[k] * r[k];
            }

            float invDist = 1.0f / sqrt(distSqr + espSqr);
            float invDistCube =  invDist * invDist * invDist;
            float s = refPos[index + 3] * invDistCube;

            for(int k = 0; k < 3; ++k)
            {
                acc[k] += s * r[k];
            }
        }

        for(int k = 0; k < 3; ++k)
        {
            refPos[myIndex + k] += refVel[myIndex + k] * delT + 0.5f * acc[k] * delT * delT;
            refVel[myIndex + k] += acc[k] * delT;
        }
    }
}

int
NBody::initialize()
{
    /* Call base class Initialize to get default configuration */
    if(!this->SDKSample::initialize())
        return SDK_FAILURE;

    streamsdk::Option *num_particles = new streamsdk::Option;
    if(!num_particles)
    {
        std::cout << "error. Failed to allocate memory (num_particles)\n";
        return SDK_FAILURE;
    }

    num_particles->_sVersion = "x";
    num_particles->_lVersion = "particles";
    num_particles->_description = "Number of particles";
    num_particles->_type = streamsdk::CA_ARG_INT;
    num_particles->_value = &numParticles;

    sampleArgs->AddOption(num_particles);

    streamsdk::Option *num_iterations = new streamsdk::Option;
    if(!num_iterations)
    {
        std::cout << "error. Failed to allocate memory (num_iterations)\n";
        return SDK_FAILURE;
    }

    num_iterations->_sVersion = "i";
    num_iterations->_lVersion = "iterations";
    num_iterations->_description = "Number of iterations";
    num_iterations->_type = streamsdk::CA_ARG_INT;
    num_iterations->_value = &iterations;

    sampleArgs->AddOption(num_iterations);

    return SDK_SUCCESS;
}

int
NBody::setup()
{
    if(setupNBody() != SDK_SUCCESS)
        return SDK_FAILURE;

    int timer = sampleCommon->createTimer();
    sampleCommon->resetTimer(timer);
    sampleCommon->startTimer(timer);

    if(setupCL() != SDK_SUCCESS)
        return SDK_FAILURE;

    sampleCommon->stopTimer(timer);
    /* Compute setup time */
    setupTime = (double)(sampleCommon->readTimer(timer));

    display = !quiet;

    return SDK_SUCCESS;
}

/** 
* @brief Initialize GL 
*/
void 
GLInit()
{
    glClearColor(0.0 ,0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);	
    glLoadIdentity();
}

/** 
* @brief Glut Idle function
*/
void 
idle()
{
    glutPostRedisplay();
}

/** 
* @brief Glut reshape func
* 
* @param w numParticles of OpenGL window
* @param h height of OpenGL window 
*/
void 
reShape(int w,int h)
{
    glViewport(0, 0, w, h);

    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluPerspective(45.0f, w/h, 1.0f, 1000.0f);
    gluLookAt (0.0, 0.0, -2.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
}

/** 
* @brief OpenGL display function
*/
static int sDCounter = 0;
void displayfunc()
{
    glClearColor(0.0 ,0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    glPointSize(1.0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);

    glColor3f(1.0f,0.6f,0.0f);

    //Calling kernel for calculatig subsequent positions
    ((NBody*)me)->runCLKernels();

    glBegin(GL_POINTS);
    for(int i=0; i < numBodies; ++i)
    {
        //divided by 300 just for scaling
        glVertex3d(pos[i*4+ 0]/300, pos[i*4+1]/300, pos[i*4+2]/300);
    }
    glEnd();

    glFlush();
    glutSwapBuffers();

	sDCounter++;

	if ( sDCounter %100  == 0 )
	{
		printf("Interation count : %d\n", sDCounter);
	}

}

/* keyboard function */
void
keyboardFunc(unsigned char key, int mouseX, int mouseY)
{
    switch(key)
    {
        /* If the user hits escape or Q, then exit */
        /* ESCAPE_KEY = 27 */
    case 27:
    case 'q':
    case 'Q':
        {
            if(((NBody*)me)->cleanup() != SDK_SUCCESS)
                exit(1);
            else
                exit(0);
        }
    default:
        break;
    }
}


int 
NBody::run()
{
    /* Arguments are set and execution call is enqueued on command buffer */
    if(setupCLKernels() != SDK_SUCCESS)
    {
        return SDK_FAILURE;
    }

//	timing = 1;
    if(verify || timing)
    {
        int timer = sampleCommon->createTimer();
        sampleCommon->resetTimer(timer);
        sampleCommon->startTimer(timer);

        for(int i = 0; i < iterations; ++i)
        {

            runCLKernels();
        }

        sampleCommon->stopTimer(timer);

        /* Compute kernel time */
        kernelTime = (double)(sampleCommon->readTimer(timer)) / iterations;
    }

    if(!quiet)
    {
        sampleCommon->printArray<cl_float>("Output", pos, numBodies, 1);
    }

    if(timing)
    {
        printf("N: %d, Time(ms): %lf\n",
               numBodies, 
               kernelTime / iterations * 1000);
    }

    return SDK_SUCCESS;
}

int
NBody::verifyResults()
{
    if(verify)
    {
        /* reference implementation
        * it overwrites the input array with the output
        */

        refPos = (cl_float*)malloc(numBodies * sizeof(cl_float4));
        if(refPos == NULL)
        { 
            sampleCommon->error("Failed to allocate host memory. (refPos)");
            return SDK_FAILURE;
        }

        refVel = (cl_float*)malloc(numBodies * sizeof(cl_float4));
        if(refVel == NULL)
        { 
            sampleCommon->error("Failed to allocate host memory. (refVel)");
            return SDK_FAILURE;
        }

        memcpy(refPos, initPos, 4 * numBodies * sizeof(cl_float));
        memcpy(refVel, initVel, 4 * numBodies * sizeof(cl_float));

        for(int i = 0; i < iterations; ++i)
        {
            nBodyCPUReference();
        }

        /* compare the results and see if they match */
        if(compareArray(pos, refPos, 4 * numBodies))
        {
            std::cout << "Failed\n";
            return SDK_FAILURE;
        }
        else
        {
            std::cout << "Passed!\n";
            return SDK_SUCCESS;
        }
    }

    return SDK_SUCCESS;
}

void 
NBody::printStats()
{
    std::string strArray[4] = 
    {
        "Particles", 
        "Iterations", 
        "Time(sec)", 
        "kernelTime(sec)"
    };

    std::string stats[4];
    totalTime = setupTime + kernelTime;

    stats[0] = sampleCommon->toString(numParticles, std::dec);
    stats[1] = sampleCommon->toString(iterations, std::dec);
    stats[2] = sampleCommon->toString(totalTime, std::dec);
    stats[3] = sampleCommon->toString(kernelTime, std::dec);

    this->SDKSample::printStats(strArray, stats, 4);
}

int
NBody::cleanup()
{
    /* Releases OpenCL resources (Context, Memory etc.) */

	callCL(deviceType.c_str(), NULL, NULL, NULL, 0, NULL, NULL, NULL);


    return SDK_SUCCESS;
}

NBody::~NBody()
{

	callCL(deviceType.c_str(), NULL, NULL, NULL, 0, NULL, NULL, NULL);

    /* release program resources */
    if(initPos)
    {
        free(initPos);
        initPos = NULL;
    }

    if(initVel)
    {
        free(initVel);
        initVel = NULL;
    }

    if(pos)
    {
#if defined (_WIN32)
        _aligned_free(pos);
#else
        free(pos);
#endif
        pos = NULL;
    }
    if(vel)
    {
#if defined (_WIN32)
        _aligned_free(vel);
#else
        free(vel);
#endif
        vel = NULL;
    }


    if(refPos)
    {
        free(refPos);
        refPos = NULL;
    }

    if(refVel)
    {
        free(refVel);
        refVel = NULL;
    }


}


int 
main(int argc, char * argv[])
{
    NBody clNBody("OpenCL NBody");
    me = &clNBody;

    if(clNBody.initialize() != SDK_SUCCESS)
        return SDK_FAILURE;
    if(!clNBody.parseCommandLine(argc, argv))
        return SDK_FAILURE;
    if(clNBody.setup() != SDK_SUCCESS)
        return SDK_FAILURE;
    if(clNBody.run() != SDK_SUCCESS)
        return SDK_FAILURE;
    if(clNBody.verifyResults() != SDK_SUCCESS)
        return SDK_FAILURE;

    clNBody.printStats();

    if(display)
    {
        // Run in  graphical window if requested 
        glutInit(&argc, argv);
        glutInitWindowPosition(100,10);
        glutInitWindowSize(600,600); 
        glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
        glutCreateWindow("nbody simulation"); 
        GLInit(); 
        glutDisplayFunc(displayfunc); 
        glutReshapeFunc(reShape);
        glutIdleFunc(idle); 
        glutKeyboardFunc(keyboardFunc);
        glutMainLoop();
    }

    if(clNBody.cleanup()!=SDK_SUCCESS)
        return SDK_FAILURE;

    return SDK_SUCCESS;
}
