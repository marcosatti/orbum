#pragma once

#include <memory>
#include <string>

#include "Types/VMOptions_t.h"

class VMExecutionCore;
class PS2Resources_t;

/*
Entry point into all PCSX2 core emulation.
This virtual machine (VM) acts as a hypervisor (manager) for the PS2's execution. All user interface & host OS functionality will eventually come through here.
*/
class VMMain
{
public:
	// Lifecycle status type
	enum VMStatus
	{
		CREATED,
		INITIALISED,
		RUNNING,
		EXCEPTION,
		STOPPED,
		DESTROYED
	};

	/*
	Lifecycle functions
	*/
	// Create
	explicit VMMain(const VMOptions_t & vmOptions);
	
	// Initialise
	void Reset();

	// Run
	void Run();

	// Stop
	void Stop();

	// Destroy
	~VMMain();

	/*
	VMMain state functions.
	*/
	const VMStatus & getStatus() const;
	void setStatus(const VMStatus & status);
	const std::shared_ptr<PS2Resources_t> & getResources() const;
	
	/*
	Misc helper functions.
	*/

private:
	/*
	VM State variables.
	*/
	VMOptions_t mVMOptions;
	VMStatus mStatus;
	std::shared_ptr<PS2Resources_t> mPS2Resources;
	std::unique_ptr<VMExecutionCore> mExecutionCore;

	// Initalisation (called through reset()).
	/*
	Initalisation for the PS2 resources.
	*/
	void initaliseResources();

	/*
	Initalise the execution core (interpreter or recompiler).
	*/
	void initaliseExecutionCore();

	/*
	Load the bios into the BootROM resource
	*/
	void initaliseBootROM() const;
};

