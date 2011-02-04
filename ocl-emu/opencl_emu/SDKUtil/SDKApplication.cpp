#include <SDKUtil/SDKApplication.hpp>

int 
SDKSample::initialize()
{
	sampleCommon = new streamsdk::SDKCommon();
    int defaultOptions = 7;

    if(multiDevice)
        defaultOptions = 6;

	
	streamsdk::Option *optionList = new streamsdk::Option[defaultOptions];
	if(!optionList)
	{
		std::cout<<"error. Failed to allocate memory (optionList)\n";
		return 0;
	}
	optionList[0]._sVersion = "";
	optionList[0]._lVersion = "device";
    
    if(multiDevice)
	    optionList[0]._description = "Execute the openCL kernel on a device [cpu|gpu|all]";
    else
        optionList[0]._description = "Execute the openCL kernel on a device [cpu|gpu]";

	optionList[0]._type = streamsdk::CA_ARG_STRING;
	optionList[0]._value = &deviceType;

	optionList[1]._sVersion = "q";
	optionList[1]._lVersion = "quiet";
	optionList[1]._description = "Quiet mode. Suppress all text output.";
	optionList[1]._type = streamsdk::CA_NO_ARGUMENT;
	optionList[1]._value = &quiet;

	optionList[2]._sVersion = "e";
	optionList[2]._lVersion = "verify";
	optionList[2]._description = "Verify results against reference implementation.";
	optionList[2]._type = streamsdk::CA_NO_ARGUMENT;
	optionList[2]._value = &verify;

	optionList[3]._sVersion = "t";
	optionList[3]._lVersion = "timing";
	optionList[3]._description = "Print timing.";
	optionList[3]._type = streamsdk::CA_NO_ARGUMENT;
	optionList[3]._value = &timing;

	optionList[4]._sVersion = "";
	optionList[4]._lVersion = "dump";
    optionList[4]._description = "Dump binary image for all devices";
	optionList[4]._type = streamsdk::CA_ARG_STRING;
	optionList[4]._value = &dumpBinary;

	optionList[5]._sVersion = "";
	optionList[5]._lVersion = "load";
    optionList[5]._description = "Load binary image and execute on device";
	optionList[5]._type = streamsdk::CA_ARG_STRING;
	optionList[5]._value = &loadBinary;

    if(multiDevice == false)
    {
        optionList[6]._sVersion = "d";
	    optionList[6]._lVersion = "deviceId";
	    optionList[6]._description = "Select deviceId to be used[0 to N-1 where N is number devices available].";
	    optionList[6]._type = streamsdk::CA_ARG_INT;
	    optionList[6]._value = &deviceId;
    }

	sampleArgs = new streamsdk::SDKCommandArgs(defaultOptions, optionList);
	if(!sampleArgs)
	{
		std::cout<<"Failed to allocate memory. (sampleArgs)\n";
		return 0;
	}
				
	return 1;
}

void SDKSample::printStats(std::string *statsStr, std::string * stats, int n)
{
	if(timing)
	{
		streamsdk::Table sampleStats;

		sampleStats._numColumns = n;
		sampleStats._numRows = 1;
		sampleStats._columnWidth = 25;
		sampleStats._delim = '$';
        
        sampleStats._dataItems = "";
        for(int i=0; i < n; ++i)
        {
            sampleStats._dataItems.append( statsStr[i] + "$");
        }
        sampleStats._dataItems.append("$");

        for(int i=0; i < n; ++i)
        {
            sampleStats._dataItems.append( stats[i] + "$");
        }

		sampleCommon->printTable(&sampleStats);
	}
}

int SDKSample::parseCommandLine(int argc, char**argv)
{
	if(sampleArgs==NULL)
	{
		std::cout<<"error. Command line parser not initialized.\n";
		return 0;
	}
	else
	{
		if(!sampleArgs->parse(argv,argc))
		{
			usage();
			return 0;
		}

		if(sampleArgs->isArgSet("h",true))
		{
			usage();
			return 1;
		}
	}

    /* check about the validity of the device type */

    if(multiDevice)
    {   
        if(!((deviceType.compare("cpu") == 0 ) 
              || (deviceType.compare("gpu") ==0) 
              || (deviceType.compare("gpu_emu") ==0) 
              || (deviceType.compare("all") ==0)))
        {
            std::cout << "error. Invalid device options. "
                      << "only \"cpu\" or \"gpu\" or \"all\" supported\n";
            usage();
            return 0;
        }
    }
    else
    {
        if(!((deviceType.compare("cpu") == 0 ) || (deviceType.compare("gpu") ==0) || (deviceType.compare("gpu_emu") ==0) ))
        {
            std::cout << "error. Invalid device options. "
                      << "only \"cpu\" or \"gpu\" or \"all\" supported\n";
            usage();
            return 0;
        }    
    }

    if(dumpBinary.size() != 0 && loadBinary.size() != 0)
    {
        std::cout << "error. --dump and --load options are mutually exclusive\n\n";
        usage();
        return 0;
    }

    if(deviceId < 0)
    {
        std::cout << "error. Invalid deviceId options. "
                  << "only 0 to N-1 where N is number of devices available\n";
        usage();
        return 0;
    }

	
	return 1;
}

void SDKSample::usage()
{
	if(sampleArgs==NULL)
		std::cout<<"error. Command line parser not initialized.\n";
	else
	{
		std::cout<<"Usage\n";
		std::cout<<sampleArgs->help();
	}
}

SDKSample::SDKSample(std::string sampleName, bool enableMultiDevice)
{
	name = sampleName;
	sampleCommon = NULL;
	sampleArgs = NULL;
	quiet = 0;
	verify = 0;
	timing = 0;
    deviceType = "gpu";
    multiDevice = enableMultiDevice;
    deviceId = 0;
}

SDKSample::SDKSample(const char* sampleName, bool enableMultiDevice)
{
	name = sampleName;
	sampleCommon = NULL;
	sampleArgs = NULL;
	quiet = 0;
	verify = 0;
	timing = 0;
    deviceType = "gpu";
    multiDevice = enableMultiDevice;
    deviceId = 0;
}

SDKSample::~SDKSample()
{
    delete sampleCommon;
    delete sampleArgs;
}
