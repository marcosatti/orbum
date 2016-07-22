#include "stdafx.h"

#include <memory>

#include "Globals.h"
#include "VMMain.h"
#include "Interpreter.h"
#include "ExceptionHandler.h"
#include "PS2Exception_t.h"
#include "MMUHandler.h"


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
	// TODO: Implement
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

void VMMain::copyResourcesTo(std::unique_ptr<PS2Resources_t>& uniquePtrTo) const
{
	uniquePtrTo = std::make_unique<PS2Resources_t>(*mPS2Resources);
}

