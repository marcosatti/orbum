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
class SIO0_s;
class SIO2_s;
class RResources;

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
	const RResources & getResources() const;

	/*
	PS2 system logic engines.
	*/
	EECoreInterpreter_s mSystemEECore;
	EEDmac_s mSystemEEDmac;
	EETimers_s mSystemEETimers;
	EEIntc_s mSystemEEIntc;
	VIF_s mSystemVIF0;
	VIF_s mSystemVIF1;
	VUInterpreter_s mSystemVU0;
	VUInterpreter_s mSystemVU1;
	IOPCoreInterpreter_s mSystemIOPCore;
	IOPDmac_s mSystemIOPDmac;
	IOPTimers_s mSystemIOPTimers;
	IOPIntc_s mSystemIOPIntc;
	CDVD_s mSystemCDVD;
	SPU2_s mSystemSPU2;
	GSCore_s mSystemGSCore;
	CRTC_s mSystemCRTC;
	SIO0_s mSystemSIO0;
	SIO2_s mSystemSIO2;
	std::vector<VMSystem_t> mSystems;

    /*
    Multi-threaded resources.
    */
    std::vector<ThreadedRunnable_t> mSystemThreads;

private:
	/*
	VM state resources.
	*/
	VMOptions mVMOptions;
	VMStatus mStatus;
	RResources mResources;
};

