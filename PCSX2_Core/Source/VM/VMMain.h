#pragma once

#include <memory>
#include <string>

class VMExecutionCoreComponent;
class VMMMUHandler;
class PS2Resources_t;

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
	void Run();

	// Run
	void Stop();

	// Destroy
	~VMMain();

	/*
	VMMain state functions.
	*/
	const VMStatus& getStatus() const;
	const std::shared_ptr<PS2Resources_t>& getResources() const;
	const std::shared_ptr<VMMMUHandler>& getMMU() const;
	
	/*
	Misc helper functions.
	*/

private:
	/*
	VM State variables.
	*/
	VMStatus mStatus;
	ExecutionCoreType mExecutionCoreType;
	std::shared_ptr<PS2Resources_t> mPS2Resources;
	std::unique_ptr<VMExecutionCoreComponent> mExecutionCoreComponent;
	const std::shared_ptr<VMMMUHandler> mMMUComponent;
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
	void initalisePS2PhysicalMemoryMap() const;

	/*
	Initalise the execution core (interpreter or recompiler).
	*/
	void initaliseExecutionCore();

	/*
	Load the bios into the BootROM resource
	*/
	void initaliseBootROM() const;
};

