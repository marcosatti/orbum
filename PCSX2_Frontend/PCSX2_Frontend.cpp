// PCSX2_Frontend.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VM/VMMain.h"
#include <iostream>


int main()
{
	VMMain vm(VMMain::ExecutionCoreType::INTERPRETER, "C:\\Shared\\scph10000.bin");

	try
	{
		vm.Run();
	}
	catch (std::runtime_error ex)
	{
		std::cout << ex.what();
		throw ex;
	}
	
    return 0;
}

