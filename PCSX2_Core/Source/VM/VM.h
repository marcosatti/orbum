#pragma once

#include <memory>
#include <thread>
#include <vector>

#include "Common/Types/EnumMap_t.h"

#include "VM/Types/VMOptions.h"
#include "VM/Types/VMSystem_s.h"

class Resources_t;
class VUInterpreter_s;
class VIF_s;
class EECoreInterpreter_s;
class EEDmac_s;
class EEIntc_s;
class EETimers_s;
class IOPCoreInterpreter_s;
class IOPIntc_s;
class IOPDmac_s;
class IOPTimers_s;

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
		Exception,
		Stopped
	};

	explicit VM(const VMOptions & vmOptions);
	~VM();
	
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
	EnumMap_t<System_t, std::shared_ptr<VMSystem_s>> mSystems;

	/*
	Threading resources.
	*/
	std::vector<std::thread> mSystemThreads;
	bool mSystemThreadsInitalised;
};

