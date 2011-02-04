//
// Copyright (c) 2008 Advanced Micro Devices, Inc. All rights reserved.
//

#ifndef SDKAPPLICATION_H_
#define SDKAPPLICATION_H_
#include <SDKUtil/SDKCommon.hpp>
#include <SDKUtil/SDKCommandArgs.hpp>

#define CL_CONTEXT_OFFLINE_DEVICES_AMD        0x403F

class SDKApplication
{
protected:
    virtual int initialize() = 0;
    virtual int run() = 0;
    virtual int cleanup() = 0;
};

class SDKSample : public SDKApplication
{
protected:
    streamsdk::SDKCommandArgs *sampleArgs;
    streamsdk::SDKCommon *sampleCommon;
    std::string name; 
    double totalTime;
    int quiet;
    int verify;
    int timing;
    bool multiDevice;
    int deviceId;
    std::string deviceType;
    std::string dumpBinary;
    std::string loadBinary;
    
protected:
    virtual int setup() = 0;
    virtual int verifyResults() = 0;	
    virtual int genBinaryImage()= 0;
    virtual int initialize();
    virtual void printStats(std::string *stdStr, std::string * stats, int n);
    virtual ~SDKSample();

public:
    SDKSample(std::string sampleName, bool enableMultiDevice = false);
    SDKSample(const char* sampleName, bool enableMultiDevice = false);
    bool isDumpBinaryEnabled()
    {
        if(dumpBinary.size() == 0)
            return false;
        else
            return true;
    }

    bool isLoadBinaryEnabled()
    {
        if(loadBinary.size() == 0)
            return false;
        else
            return true;
    }
    int parseCommandLine(int argc, char **argv);
    void usage();
};

#endif


