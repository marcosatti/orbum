#include "stdafx.h"
#include <gtest/gtest.h>

#include <VM/VM.h>
#include <VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h>

class TEST_EECoreInterpreter_s : public testing::Test
{
public:
	VM * vm;
	EECoreInterpreter_s * core;

	virtual void SetUp()
	{
		VMOptions vmOptions =
		{
			nullptr,
			"",
			"",
			"",
			"",
			0,
			false,
			{}
		};
		
		vm = new VM(vmOptions);
		core = dynamic_cast<EECoreInterpreter_s*>(vm->mSystems[System_t::EECore].get());
	}

	virtual void TearDown() 
	{
		core = nullptr;
		delete vm;
	}
};

TEST_F(TEST_EECoreInterpreter_s, MIPS_INSTRUCTION_IMPLEMENTATIONS)
{
	// Test follows the basic MIPS III instruction set.
	// https://en.wikipedia.org/wiki/MIPS_instruction_set
}

/*
TEST_F(TEST_EECoreInterpreter_s, SONY_MMI_INSTRUCTION_IMPLEMENTATIONS)
{
}
*/