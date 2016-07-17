#include "stdafx.h"

#include <memory>

#include "Globals.h"
#include "VMMain.h"
#include "Interpreter.h"
#include "ExceptionHandler.h"
#include "PS2Exception_t.h"


VMMain::VMMain(ExecutionCoreType executionCoreType) 
	: _executionCoreType(executionCoreType),
	_resources(std::make_unique<PS2Resources_t>()),
	_exceptionHandlerComponent(std::make_unique<ExceptionHandler>(this)),
	_status(VMMain::VMStatus::CREATED)

{
	// Initialise ExecutionCore based on parsed type
	switch(_executionCoreType)
	{
	case ExecutionCoreType::INTERPRETER:
	{
		_executionCoreComponent = std::make_unique<Interpreter>(this);
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
			_executionCoreComponent->executionLoop();
		}
	}
	catch (const PS2Exception_t& ps2Exception)
	{
		_exceptionHandlerComponent->handleException(ps2Exception);
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
	return _status;
}

const std::unique_ptr<PS2Resources_t>& VMMain::getResources() const
{
	return _resources;
}

void VMMain::copyResourcesTo(std::unique_ptr<PS2Resources_t>& uniquePtrTo) const
{
	uniquePtrTo = std::make_unique<PS2Resources_t>(*_resources);
}

