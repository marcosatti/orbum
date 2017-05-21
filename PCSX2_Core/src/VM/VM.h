#pragma once

#include <memory>
#include <thread>
#include <vector>

#include "Common/Types/EnumMap_t.h"

#include "VM/Types/VMOptions.h"
#include "VM/Types/VMSystem_t.h"

class Resources_t;

/*
Entry point into all PCSX2 core emulation.
This is the VM manager for the PS2's execution. All user interface & host OS functionality will eventually come through here.
*/
class VM
{
public:
	enum VMStatus
	{
		Running,
		Paused,
		Stopped
	};

	/*
	Constructs the VM through a call to reset().
	*/
	explicit VM(const VMOptions & vmOptions);

	/*
	Deconstructs the VM through a call to stop().
	*/
	~VM();
	
	/*
	Resets the VM by setting up logging, resources and system threads.
	After a reset, the VM state is set to paused and is ready to run.
	*/
	void reset();
	void reset(const VMOptions & options);

	/*
	Runs through one time step (set in the VM options), and then pauses the VM state.
	If a call to run is made while the VM state is in the stopped state, a runtime_error will be thrown.
	*/
	void run();

	/*
	Stops the VM by deconstructing the logging, resources and system threads.
	After calling stop, the VM state will need to be reset again before calling run.
	*/
	void stop();

	/*
	Returns the VM state.
	*/
	VMStatus getStatus() const;

	/*
	Returns a reference to the PS2 resources.
	*/
	const std::shared_ptr<Resources_t> & getResources() const;

private:
	// Friend classes for the unit test functions.
	friend class TEST_EECoreInterpreter_s;
	friend class TEST_IOPCoreInterpreter_s;

	/*
	VM state resources.
	*/
	VMOptions mVMOptions;
	VMStatus mStatus;
	std::shared_ptr<Resources_t> mResources;
	std::vector<std::thread> mSystemThreads;

	/*
	PS2 System logic engines.
	*/
	std::vector<std::shared_ptr<VMSystem_t>> mSystems;
};

