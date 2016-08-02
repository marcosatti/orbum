#pragma once

#include <memory>
#include <string>

#include "Common/Global/Globals.h"
#include "Common/PS2 Resources/PS2Resources_t.h"
#include "VM/Component Interfaces/VMMMUComponent.h"
#include "VM/Component Interfaces/VMExceptionHandlerComponent.h"
#include "VM/Component Interfaces/VMExecutionCoreComponent.h"

/*
TODO: Fill in documentation.
*/

/*
Entry point into all PCSX2 core emulation.
This virtual machine (VM) acts as a hypervisor (manager) for the PS2's execution. All user interface & host OS functionality will eventually come through here.
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
	explicit VMMain(const ExecutionCoreType executionCoreType, const std::string & bootROMPath);
	
	// Initialise
	void LoadExecutable(std::string&& excutablePath) const;
	void Reset();

	// Run
	void Run() const;

	// Run
	void Stop() const;

	// Destroy
	~VMMain();

	/*
	VMMain state functions.
	*/
	INLINE const VMStatus& getStatus() const;
	INLINE const std::unique_ptr<PS2Resources_t>& getResources() const;
	INLINE const std::unique_ptr<VMMMUComponent>& getMMU() const;
	
	/*
	Misc helper functions.
	*/
	void copyResourcesTo(std::unique_ptr<PS2Resources_t> &uniquePtrTo) const;

private:
	/*
	VM State variables.
	*/
	VMStatus mStatus;
	ExecutionCoreType mExecutionCoreType;
	std::unique_ptr<PS2Resources_t> mPS2Resources;
	const std::unique_ptr<VMExceptionHandlerComponent> mExceptionHandlerComponent;
	std::unique_ptr<VMExecutionCoreComponent> mExecutionCoreComponent;
	const std::unique_ptr<VMMMUComponent> mMMUComponent;
	const std::string mBootROMPath;

	// Initalisation (called through reset()).
	/*
	Initalisation for the PS2 resources.
	*/
	void initaliseResources();

	/*
	Initalise the PS2 Physical memory by mapping it to the memory regions allocated by mPS2Resources.
	See the function definition for the memory allocation details.
	Also see 'Memory Mappings.xlsx' for information as some parts are PCSX2 specific.
	*/
	void initalisePS2MemoryMap() const;

	/*
	Initalise the execution core (interpreter or recompiler).
	*/
	void initaliseExecutionCore();

	/*
	Load the bios into the BootROM resource
	*/
	void initaliseBootROM() const;
};

