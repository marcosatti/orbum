// PCSX2_Frontend.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VM/VmMain.h"
#include "VM/Types/VMOptions_t.h"
#include <fstream>

std::ofstream logFile;

void log(const char * buffer)
{
	logFile << buffer;
	printf(buffer);
}

int main()
{
	logFile.open("C:\\Shared\\PCSX2_Rewrite.txt");

	VMOptions_t vmOptions = 
	{
		log,
		"C:\\Shared\\scph10000.bin",
		ExecutionCore_t::Interpreter
	};

	VMMain vm(vmOptions);

	vm.Run();

	logFile.close();
	
    return 0;
}

