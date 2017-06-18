#include <iostream>
#include <fstream>
#include <mutex>

#include "Common/Global/Log.h"
#include "VM/VM.h"
#include "VM/Types/VMOptions.h"
#include "Common/Types/Memory/ByteMemory_t.h"
#include "Common/Types/Memory/HwordMemory_t.h"
#include "Resources/Resources_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/IOP/IOP_t.h"
#include "Resources/SPU2/SPU2_t.h"
#include "Resources/CDVD/CDVD_t.h"
#include "Resources/CDVD/Types/CDVDNvrams_t.h"

std::ofstream logFile;
volatile bool DEBUG_RUN = true;

void log(const LogLevel_t level, const std::string & message)
{
	std::string prefix;
	switch (level)
	{
	case Debug:
		prefix = "[Debug] "; break;
	case Info:
		prefix = "[Info] "; break;
	case Warning:
		prefix = "[Warning] "; break;
	case Fatal:
		prefix = "[Fatal] "; break;
	}

	logFile << prefix << message << std::endl;
	std::cout << prefix << message << std::endl;

	logFile.flush();
	std::cout.flush();
}

int main(int argc, char * argv[])
{
	std::string workspace("./workspace/");

	if (argc > 1)
		workspace = argv[1];

    std::cout << "PCSX2_Frontend starting, called with arguments:" << std::endl;
    for (int i = 0; i < argc; i++)
        std::cout << i << ": " << argv[i] << std::endl;
    std::cout << "Using workspace directory: " << workspace << std::endl;

	logFile.open(workspace + "PCSX2_Rewrite_Log.txt");

	VMOptions vmOptions = 
	{
		log,
		workspace + "scph10000.bin",
		"",
		"",
		"",
		10,
		VMOptions::ST,
		{ }
	};

	try
	{
		VM vm(vmOptions);

		try 
		{
			vm.reset(true);
			
			while (vm.getStatus() == VM::VMStatus::Paused && DEBUG_RUN)
				vm.run();
		}
		catch (const std::runtime_error & ex)
		{
			log(Fatal, ex.what());
		}

		vm.getResources()->EE->MainMemory->dump(std::string(workspace + "End_Dump_EE.bin").c_str());
		vm.getResources()->IOP->MainMemory->dump(std::string(workspace + "End_Dump_IOP.bin").c_str());
		vm.getResources()->SPU2->MainMemory->dump(std::string(workspace + "End_Dump_SPU2.bin").c_str());
		vm.getResources()->CDVD->NVRAM->MainMemory->dump(std::string(workspace + "End_Dump_CDVD_NVRAM.bin").c_str());
	}
	catch (const std::exception & ex)
	{
		log(Fatal, ex.what());
	}       

	logFile.close();
	
    return 0;
}

