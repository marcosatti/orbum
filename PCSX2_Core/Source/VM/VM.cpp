#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Memory/ROMemory_t.h"

#include "VM/VM.h"
#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"
#include "VM/Systems/EE/DMAC/EEDmac_s.h"
#include "VM/Systems/EE/Timers/EETimers_s.h"
#include "VM/Systems/EE/INTC/EEIntc_s.h"
#include "VM/Systems/EE/VPU/VIF/VIF_s.h"
#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter_s.h"
#include "VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h"
#include "VM/Systems/IOP/DMAC/IOPDmac_s.h"
#include "VM/Systems/IOP/Timers/IOPTimers_s.h"
#include "VM/Systems/IOP/INTC/IOPIntc_s.h"
#include "VM/Systems/GS/GSCore/GSCore_s.h"
#include "VM/Systems/GS/PCRTC/PCRTC_s.h"

#include "Resources/Resources_t.h"
#include "Resources/EE/EE_t.h"

VM::VM(const VMOptions & vmOptions) : 
	mVMOptions(vmOptions),
	mStatus(Stopped),
	mSystemThreadsInitalised(false)
{
	// Initialise everything.
	reset();
}

void VM::reset()
{
	// Set to running.
	mStatus = Running;

	// Initalise logging.
	LOG_CALLBACK_FUNCPTR = mVMOptions.LOG_CALLBACK_FUNCPTR;
	log(Info, "VM reset started...");

	// Initalise resources.
	mResources = std::make_shared<Resources_t>();

	log(Info, "VM resources initalised.");

	// Initalise Roms.
	mResources->EE->BootROM->readFile(mVMOptions.BOOT_ROM_PATH, 0, Constants::EE::ROM::SIZE_BOOT_ROM, 0); // BootROM.
	// ROM1.
	// ROM2.
	// EROM.

	log(Info, "VM roms initalised.");

	// Create components.
	auto vu0temp = std::make_shared<VUInterpreter_s>(this, 0);
	mSystems =
	{
		{VU0, vu0temp},
		{VU1, std::make_shared<VUInterpreter_s>(this, 1)},
		{VIF0, std::make_shared<VIF_s>(this, 0)},
		{VIF1, std::make_shared<VIF_s>(this, 1)},
		{EECore, std::make_shared<EECoreInterpreter_s>(this, vu0temp)},
		{EEDmac, std::make_shared<EEDmac_s>(this)},
		{EEIntc, std::make_shared<EEIntc_s>(this)},
		{EETimers, std::make_shared<EETimers_s>(this)},
		{IOPCore, std::make_shared<IOPCoreInterpreter_s>(this)},
		{IOPIntc, std::make_shared<IOPIntc_s>(this)},
		{IOPDmac, std::make_shared<IOPDmac_s>(this)},
		{IOPTimers, std::make_shared<IOPTimers_s>(this)},
		{GSCore, std::make_shared<GSCore_s>(this)},
		{PCRTC, std::make_shared<PCRTC_s>(this)}
	};

	// Initalise components.
	for (auto& system : mSystems)
		system.second->initalise();

	log(Info, "VM systems initalised.");

	// Use multithreaded systems if enabled.
	if (mVMOptions.USE_MULTI_THREADED_SYSTEMS)
	{
		throw std::runtime_error("VM MT mode needs reworking.");
		/*
		// Clear any existing threads... could be dangerous since we have detached them... TODO: look into this.
		mSystemThreads.empty();

		// Initalise threads.
		for (auto& component : mSystems)
			mSystemThreads.push_back(std::thread(&VMSystem_s::threadLoop, &(*component)));

		// Detach threads.
		for (auto& thread : mSystemThreads)
			thread.detach();

		// Set threaded state to initalised.
		mSystemThreadsInitalised = true;
		*/
	}
	else
	{
		mSystemThreadsInitalised = false;
	}

	log(Info, "VM reset done.");
}

void VM::reset(const VMOptions& options)
{
	mVMOptions = options;
	reset();
}

void VM::run()
{
	if (mVMOptions.USE_MULTI_THREADED_SYSTEMS)
	{
		throw std::runtime_error("VM MT mode needs reworking.");
		/*
		// Running in multithreaded mode.
		if (!mSystemThreadsInitalised)
			throw std::runtime_error("VM MT mode was not setup before running!");

		// Aquire all mutex locks first (common sync point).
		for (auto& system : mSystems)
		{
			system->mThreadMutex.lock();
		}

		// Produce ticks for all components.
		for (auto& system : mSystems)
		{
			system->produceTicks(ClockSource_t::EECore, mVMOptions.TIME_SLICE_PER_RUN / 1.0e6 * Constants::EE::EECore::EECORE_CLK_SPEED);
			system->mThreadRun = true;
		}

		// Unlock the mutexes.
		for (auto& system : mSystems)
		{
			system->mThreadMutex.unlock();
		}

		// Notify them.
		for (auto& system : mSystems)
		{
			system->mThreadSync.notify_all();
		}
		*/
	}
	else
	{
		// Running in single threaded mode.
		// Run through each of the systems separately.
		for (auto& system : mSystems)
		{
			system.second->run(mVMOptions.TIME_SLICE_PER_RUN  * mVMOptions.SYSTEM_BIASES[system.first]);
		}
	}
}

void VM::stop()
{
	// Set to stopped.
	mStatus = Stopped;

	// Set system threads state to not initalised.
	mSystemThreadsInitalised = false;

	log(Info, "VM stopped ok.");
}

VM::~VM()
{
}

const VM::VMStatus& VM::getStatus() const
{
	return mStatus;
}

void VM::setStatus(const VMStatus& status)
{
	mStatus = status;
}

const std::shared_ptr<Resources_t> & VM::getResources() const
{
	return mResources;
}

const std::shared_ptr<VMSystem_s> & VM::getSystem(const System & system)
{
	return mSystems[system];
}
