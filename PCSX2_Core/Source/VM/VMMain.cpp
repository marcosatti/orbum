#include "stdafx.h"

#include <memory>

#include "VM/VMMain.h"
#include "VM/ExceptionHandler/ExceptionHandler.h"
#include "VM/MMUHandler/MMUHandler.h"
#include "VM/ExecutionCore/Interpreter/Interpreter.h"


VMMain::VMMain(ExecutionCoreType executionCoreType) 
	: mStatus(VMMain::VMStatus::CREATED),
	mExecutionCoreType(executionCoreType),
	mPS2Resources(std::make_unique<PS2Resources_t>()),
	mExceptionHandlerComponent(std::make_unique<ExceptionHandler>(this)),
	mMMUComponent(std::make_unique<MMUHandler>(this))
{
	// Initialise ExecutionCore based on parsed type
	switch(mExecutionCoreType)
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

void VMMain::LoadExecutable(std::string&& excutablePath) const
{
	// TODO: Implement.
}

void VMMain::Reset() const
{
	// TODO: Implement.
	
	// A reset is done according to the Reset signal/exception defined on page 95 of the EE Core Users Manual is raised.
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

void VMMain::initalisePS2PhysicalMemory() const
{
	// Main memory 32MB
	getMMU()->mapMemory(getResources()->MainMemory.getBaseAddress(), PS2Constants::EE::SIZE_MAIN_MEMORY, PS2Constants::EE::PADDRESS_MAIN_MEMORY);
}
