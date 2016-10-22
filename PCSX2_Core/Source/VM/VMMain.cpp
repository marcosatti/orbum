#include "stdafx.h"

#include <memory>

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/Interpreter.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/Types/BootROM_t.h"

VMMain::VMMain(ExecutionCoreType executionCoreType, const std::string & bootROMPath) : 
	mStatus(VMMain::VMStatus::CREATED),
	mExecutionCoreType(executionCoreType),
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
	// Initalise VM.
	initaliseResources();
	initaliseExecutionCore();

	// Initiaise BIOS (BootROM).
	initaliseBootROM();
	
	// Initalise the execution core.
	mExecutionCoreComponent->initalise();
}

void VMMain::Run()
{
	// Set to running.
	mStatus = VMStatus::RUNNING;

	// Run the VM.
	while (mStatus == VMStatus::RUNNING)
	{
		mExecutionCoreComponent->executionStep(ClockSource_t::VM);
	}
}

void VMMain::Stop()
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

void VMMain::setStatus(const VMStatus& status)
{
	mStatus = status;
}

const std::shared_ptr<PS2Resources_t>& VMMain::getResources() const
{
	return mPS2Resources;
}

void VMMain::initaliseResources()
{
	mPS2Resources = std::make_shared<PS2Resources_t>();
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
	getResources()->EE->BootROM->loadBIOS(mBootROMPath);
}
