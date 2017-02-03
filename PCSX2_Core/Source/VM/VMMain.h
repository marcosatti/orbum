#pragma once

#include <memory>
#include <thread>

#include "VM/Types/VMOptions.h"
#include "VM/Types/VMSystem_t.h"

class Resources_t;
class VUInterpreter;
class VIF;
class VMMain;
class EECoreInterpreter;
class EEDmac;
class EEIntc;
class EETimers;
class IOPCoreInterpreter;
class IOPIntc;
class IOPDmac;
class IOPTimers;

/*
Entry point into all PCSX2 core emulation.
This is the VM manager for the PS2's execution. All user interface & host OS functionality will eventually come through here.
*/
class VMMain
{
public:
	enum VMStatus
	{
		Running,
		Exception,
		Stopped
	};

	explicit VMMain(const VMOptions & vmOptions);
	~VMMain();
	
	void reset();
	void reset(const VMOptions & options);
	void run();
	void stop();

	/*
	VM state functions.
	*/
	const VMStatus & getStatus() const;
	void setStatus(const VMStatus & status);
	const std::shared_ptr<Resources_t> & getResources() const;

	/*
	Logging.
	*/
	void log(const LogLevel_t & level, const char * format, ...) const;

private:
	/*
	VM state resources.
	*/
	VMOptions mVMOptions;
	VMStatus mStatus;
	std::shared_ptr<Resources_t> mResources;

	/*
	PS2 systems / components.
	*/
	std::shared_ptr<VUInterpreter> mInterpreterVU0;
	std::shared_ptr<VUInterpreter> mInterpreterVU1;
	std::shared_ptr<VIF> mVIF0;
	std::shared_ptr<VIF> mVIF1;
	std::shared_ptr<EECoreInterpreter> mEECoreInterpreter;
	std::shared_ptr<EEDmac> mEEDmac;
	std::shared_ptr<EEIntc> mEEIntc;
	std::shared_ptr<EETimers> mEETimers;
	std::shared_ptr<IOPCoreInterpreter> mIOPCoreInterpreter;
	std::shared_ptr<IOPIntc> mIOPIntc;
	std::shared_ptr<IOPDmac> mIOPDmac;
	std::shared_ptr<IOPTimers> mIOPTimers;
	std::vector<std::shared_ptr<VMSystem_t>> mSystems;

	/*
	Threading resources.
	*/
	std::vector<std::thread> mSystemThreads;
	bool mSystemThreadsInitalised;
};

