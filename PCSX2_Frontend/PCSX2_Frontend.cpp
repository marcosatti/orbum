// PCSX2_Frontend.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VM/VMMain.h"


int main()
{
	VMMain vm(VMMain::ExecutionCoreType::INTERPRETER, "C:\\Shared\\scph10000.bin");
	vm.Run();
    return 0;
}

