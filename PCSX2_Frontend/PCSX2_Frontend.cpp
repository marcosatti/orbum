// PCSX2_Frontend.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <mutex>

#include "Common/Global/Log.h"
#include "VM/VM.h"
#include "VM/Types/VMOptions.h"

std::ofstream logFile;

void log(const LogLevel_t level, const std::string message)
{
	static std::mutex mtx;
	std::lock_guard<std::mutex> lock(mtx);

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
	logFile.open("C:\\Shared\\PCSX2_Rewrite.txt");

	VMOptions vmOptions = 
	{
		log,
		"C:\\Shared\\scph10000.bin",
		"",
		"",
		"",
		50,
		true,
		1.0,
		1.0,
		1.0,
		1.0,
		1.0,
		1.0,
		1.0,
		1.0,
		1.0,
		1.0, 
		1.0,
		1.0,
	};

	try 
	{
		VM vm(vmOptions);

		while (true)
			vm.run();
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

