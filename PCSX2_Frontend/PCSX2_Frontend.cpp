// PCSX2_Frontend.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VM/VMMain.h"
#include "VM/Types/VMOptions_t.h"
#include <fstream>

std::ofstream logFile;

void log(const char * buffer)
{
	logFile << buffer;
	logFile.flush();
	fprintf(stderr, buffer);
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

	try 
	{
		VMMain vm(vmOptions);
		vm.Run();
	}
	catch (std::exception ex)
	{
		std::string msg("EXCEPTION: ");
		msg += ex.what();
		log(msg.c_str());
	}

	logFile.close();
	
    return 0;
}

