// PCSX2_Frontend.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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

std::ofstream logFile;
bool MTmode = false;

void log(const LogLevel_t level, const std::string message)
{
	if (MTmode)
	{
		static std::mutex mtx;
		std::lock_guard<std::mutex> lock(mtx);
	}

	std::string prefix;
	switch (level)
	{
	case Debug:
		prefix = "[Debug] "; break;
	case Info:
		prefix = "[Info] "; break;
	case Warning:
		prefix = "[Warning] "; break;
	}

	logFile << prefix << message << std::endl;
	std::cout << prefix << message << std::endl;

	logFile.flush();
	std::cout.flush();
}

int main()
{
	std::string workspace("..\\Workspace\\");
	logFile.open(workspace + "PCSX2_Rewrite_Log.txt");
	
	VMOptions vmOptions = 
	{
		log,
		workspace + "scph10000.bin",
		"",
		"",
		"",
		10,
		MTmode,
		{ }
	};

	try 
	{
		VM vm(vmOptions);

		while (vm.getStatus() == VM::VMStatus::Running)
			vm.run();

		vm.getResources()->EE->MainMemory->dump(std::string(workspace + "End_Dump_EE.bin").c_str());
		vm.getResources()->IOP->MainMemory->dump(std::string(workspace + "End_Dump_IOP.bin").c_str());
		vm.getResources()->SPU2->MainMemory->dump(std::string(workspace + "End_Dump_SPU2.bin").c_str());
		vm.getResources()->SPU2->DebugDummy->dump(std::string(workspace + "End_Dump_DebugDummy.bin").c_str());
	}
	catch (std::exception ex)
	{
		std::string msg("EXCEPTION: ");
		msg += ex.what();
		log(Debug, msg.c_str());
	}

	logFile.close();
	
    return 0;
}

