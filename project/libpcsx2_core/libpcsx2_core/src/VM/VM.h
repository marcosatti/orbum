#pragma once

#include <memory>
#include <thread>
#include <vector>
#include <utility>

#include "VM/Types/VMOptions.h"

class ThreadedRunnable_t;
class VMSystem_t;
class EECoreInterpreter_s;
class EEDmac_s;
class EETimers_s;
class EEIntc_s;
class VIF_s;
class VUInterpreter_s;
class IOPCoreInterpreter_s;
class IOPDmac_s;
class IOPTimers_s;
class IOPIntc_s;
class CDVD_s;
class SPU2_s;
class GSCore_s;
class CRTC_s;
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
	Constructs the VM. A reset is not performed; it must be called explicitly to run.
	*/
	explicit VM(const VMOptions & vmOptions);

	/*
	Deconstructs the VM through a call to stop().
	*/
	~VM();
	
	/*
	Resets the VM by setting up logging, resources and system threads.
	After a reset, the VM state is set to paused and is ready to run.
	The parameter loadBIOS controls automatically loading the BIOS into memory; call loadBIOS() explicitly otherwise;
	*/
	void reset(const bool loadBIOS);
	void reset(const bool loadBIOS, const VMOptions & options);

	/*
	Loads the various bios' into memory, from the VM option given in reset().
	*/
	void resetBIOS();

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

	/*
	PS2 system logic engines.
	*/
	std::shared_ptr<EECoreInterpreter_s> mSystemEECore;
	std::shared_ptr<EEDmac_s> mSystemEEDmac;
	std::shared_ptr<EETimers_s> mSystemEETimers;
	std::shared_ptr<EEIntc_s> mSystemEEIntc;
	std::shared_ptr<VIF_s> mSystemVIF0;
	std::shared_ptr<VIF_s> mSystemVIF1;
	std::shared_ptr<VUInterpreter_s> mSystemVU0;
	std::shared_ptr<VUInterpreter_s> mSystemVU1;
	std::shared_ptr<IOPCoreInterpreter_s> mSystemIOPCore;
	std::shared_ptr<IOPDmac_s> mSystemIOPDmac;
	std::shared_ptr<IOPTimers_s> mSystemIOPTimers;
	std::shared_ptr<IOPIntc_s> mSystemIOPIntc;
	std::shared_ptr<CDVD_s> mSystemCDVD;
	std::shared_ptr<SPU2_s> mSystemSPU2;
	std::shared_ptr<GSCore_s> mSystemGSCore;
	std::shared_ptr<CRTC_s> mSystemCRTC;
	std::vector<std::shared_ptr<VMSystem_t>> mSystems;

    /*
    Multi-threaded resources.
    */
    std::vector<std::shared_ptr<ThreadedRunnable_t>> mSystemThreads;
};

