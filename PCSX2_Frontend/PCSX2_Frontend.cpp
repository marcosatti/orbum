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
	logFile.open("C:\\Shared\\PCSX2_Rewrite.txt");

	VMOptions vmOptions = 
	{
		log,
		"C:\\Shared\\scph10000.bin",
		"",
		"",
		"",
		10,
		MTmode,
		{   
			{EECore, 1.0},    {EEDmac, 1.0},  {EETimers, 1.0}, {EEIntc, 1.0}, 
			{GIF, 1.0},       {IPU, 1.0},     {VIF0, 1.0},     {VU0, 1.0},   
			{VIF1, 1.0},      {VU1, 1.0},     {IOPCore, 1.0},  {IOPDmac, 1.0},
			{IOPTimers, 1.0}, {IOPIntc, 1.0}, {CDVD, 1.0},     {GSCore, 1.0},  {PCRTC, 1.0}
		}
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

