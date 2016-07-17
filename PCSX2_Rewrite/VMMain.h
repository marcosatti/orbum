#pragma once

#include <memory>

#include "Globals.h"

#include "PS2Resources_t.h"
#include "VMExceptionHandlerComponent.h"
#include "VMExecutionCoreComponent.h"

/*
TODO: Fill in documentation.
*/

/*
Entry point into all PCSX2 core emulation.
*/
class VMMain
{
public:
	/*
	Types
	*/

	// Lifecycle status
	enum VMStatus
	{
		CREATED,
		INITIALISED,
		RUNNING,
		EXCEPTION,
		STOPPED,
		DESTROYED
	};

	// Execution Core Type
	enum ExecutionCoreType
	{
		INTERPRETER,
		RECOMPILER
	};

	/*
	Lifecycle functions
	*/
	// Create
	explicit VMMain(const ExecutionCoreType executionCoreType);
	
	// Initialise
	void LoadExecutable(std::string&& excutablePath) const;

	void Reset() const;

	// Run
	void Run() const;

	// Run
	void Stop() const;

	// Destroy
	~VMMain();

	/*
	VMMain state functions
	*/
	INLINE const VMStatus& getStatus() const;
	const std::unique_ptr<PS2Resources_t>& getResources() const;
	void copyResourcesTo(std::unique_ptr<PS2Resources_t> &uniquePtrTo) const;

private:
	VMStatus _status;
	ExecutionCoreType _executionCoreType;
	const std::unique_ptr<PS2Resources_t> _resources;
	const std::unique_ptr<VMExceptionHandlerComponent> _exceptionHandlerComponent;
	std::unique_ptr<VMExecutionCoreComponent> _executionCoreComponent;
};

