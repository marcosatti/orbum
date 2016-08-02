#include "stdafx.h"

#include <memory>
#include <fstream>

#include "VM/VMMain.h"
#include "VM/ExceptionHandler/ExceptionHandler.h"
#include "VM/MMUHandler/MMUHandler.h"
#include "VM/ExecutionCore/Interpreter/Interpreter.h"


VMMain::VMMain(ExecutionCoreType executionCoreType, const std::string & bootROMPath) 
	: mStatus(VMMain::VMStatus::CREATED),
	mExecutionCoreType(executionCoreType),
	mExceptionHandlerComponent(std::make_unique<ExceptionHandler>(this)),
	mMMUComponent(std::make_unique<MMUHandler>(this)),
	mBootROMPath(bootROMPath)
{
	// Initialise everything.
	Reset();
}

void VMMain::LoadExecutable(std::string&& excutablePath) const
{
	// TODO: Implement.
}

void VMMain::Reset()
{
	// TODO: Implement.

	// Initalise VM.
	initaliseResources();
	initaliseExecutionCore();
	initalisePS2MemoryMap();
	
	// A PS2 reset is done according to the Reset signal/exception defined on page 95 of the EE Core Users Manual.
	// This means we can raise a Reset exception (to handle) and it will be equivilant to setting everything manually!
	// After this is done, call Run() to begin execution.
	mExceptionHandlerComponent->handleException(PS2Exception_t(PS2Exception_t::ExceptionType::EX_RESET));
}

void VMMain::Run() const
{
	// TODO: Implement.
	try
	{
		while (getStatus() == VMStatus::RUNNING)
		{
			mExecutionCoreComponent->executionLoop();
		}
	}
	catch (const PS2Exception_t& ps2Exception)
	{
		mExceptionHandlerComponent->handleException(ps2Exception);
	}
}

void VMMain::Stop() const
{
	// TODO: Implement.
}

VMMain::~VMMain()
{
}

const VMMain::VMStatus& VMMain::getStatus() const
{
	return mStatus;
}

const std::unique_ptr<PS2Resources_t>& VMMain::getResources() const
{
	return mPS2Resources;
}

const std::unique_ptr<VMMMUComponent>& VMMain::getMMU() const
{
	return mMMUComponent;
}

void VMMain::copyResourcesTo(std::unique_ptr<PS2Resources_t>& uniquePtrTo) const
{
	uniquePtrTo = std::make_unique<PS2Resources_t>(*mPS2Resources);
}

void VMMain::initaliseResources()
{
	// Any old resources are destroyed automatically through unique_ptr.
	mPS2Resources = std::make_unique<PS2Resources_t>();
}

void VMMain::initalisePS2MemoryMap() const
{
	// Main memory 32MB
	getMMU()->mapMemory(getResources()->MainMemory.getBaseAddress(), PS2Constants::SIZE_MAIN_MEMORY, PS2Constants::PADDRESS_MAIN_MEMORY);

	// Scratchpad memory 16KB
	getMMU()->mapMemory(getResources()->EE.EECore.ScratchpadMemory.getBaseAddress(), PS2Constants::EE::EECore::SIZE_SCRATCHPAD_MEMORY, PS2Constants::EE::EECore::PADDRESS_SCRATCHPAD_MEMORY);

	// Boot ROM 4MB
	getMMU()->mapMemory(getResources()->MainMemory.getBaseAddress(), PS2Constants::SIZE_BOOT_ROM, PS2Constants::PADDRESS_BOOT_ROM);
}

void VMMain::initaliseExecutionCore()
{
	switch (mExecutionCoreType)
	{
	case ExecutionCoreType::INTERPRETER:
	{
		mExecutionCoreComponent = std::make_unique<Interpreter>(this);
		break;
	}
	case ExecutionCoreType::RECOMPILER:
	{
		// TODO: Implement.
		break;
	}
	}
}

void VMMain::initaliseBootROM() const
{
	char * memoryBase = reinterpret_cast<char*>(getResources()->BootROM.getBaseAddress());
	std::ifstream file(mBootROMPath, std::ifstream::binary);
	file.seekg(std::ifstream::beg);
	file.read(memoryBase, PS2Constants::SIZE_BOOT_ROM);
}
