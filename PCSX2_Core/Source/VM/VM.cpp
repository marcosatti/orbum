#include "stdafx.h"

#include <memory>
#include <cmath>

#include "Common/Global/Globals.h"
#include "Common/Types/Memory/ROByteMemory_t.h"

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
#include "VM/Systems/GS/CRTC/CRTC_s.h"

#include "Resources/Resources_t.h"
#include "Resources/Clock/Clock_t.h"
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

	// Initalise resources and set system bias speeds.
	mResources = std::make_shared<Resources_t>();
	mResources->Clock->setSystemClockBiases(mVMOptions.SYSTEM_BIASES);

	log(Info, "VM resources initalised.");

	// Initalise Roms.
	if (!mVMOptions.BOOT_ROM_PATH.empty())
		mResources->EE->BootROM->readFile(mVMOptions.BOOT_ROM_PATH.c_str(), 0, Constants::EE::ROM::SIZE_BOOT_ROM, 0); // BootROM.
	// ROM1.
	// ROM2.
	// EROM.

	log(Info, "VM roms initalised.");

	// Create components.
	auto vu0temp = std::make_shared<VUInterpreter_s>(this, 0);
	mSystems =
	{
		std::make_shared<EECoreInterpreter_s>(this, vu0temp),
		std::make_shared<EEDmac_s>(this),
		std::make_shared<EETimers_s>(this),
		std::make_shared<EEIntc_s>(this),
		nullptr,
		nullptr,
		std::make_shared<VIF_s>(this, 0),
		vu0temp,
		std::make_shared<VIF_s>(this, 1),
		std::make_shared<VUInterpreter_s>(this, 1),
		std::make_shared<IOPCoreInterpreter_s>(this),
		std::make_shared<IOPDmac_s>(this),
		std::make_shared<IOPTimers_s>(this),
		std::make_shared<IOPIntc_s>(this),
		nullptr,
		std::make_shared<GSCore_s>(this),
		std::make_shared<CRTC_s>(this)
	};

	// Initalise components.
	for (auto& system : mSystems)
		if (system.second != nullptr) 
			system.second->initalise();

	log(Info, "VM systems initalised.");

	// Use multithreaded systems if enabled.
	if (mVMOptions.USE_MULTI_THREADED_SYSTEMS)
	{
		// Clear any existing threads... could be dangerous since we have detached them... TODO: look into this.
		mSystemThreads.empty();

		// Initalise threads.
		for (auto& system : mSystems)
			if (system.second != nullptr)
				mSystemThreads.push_back(std::thread(&VMSystem_s::threadLoop, &(*system.second)));

		// Detach threads.
		for (auto& thread : mSystemThreads)
			thread.detach();

		// Set threaded state to initalised.
		mSystemThreadsInitalised = true;
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
	auto& Clock = getResources()->Clock;

	if (mVMOptions.USE_MULTI_THREADED_SYSTEMS)
	{
		// Running in multithreaded mode.
		if (!mSystemThreadsInitalised)
			throw std::runtime_error("VM MT mode was not setup before running!");

		// Aquire all mutex locks first (common sync point).
		for (auto& system : mSystems)
		{
			if (system.second != nullptr) 
				system.second->mThreadMutex.lock();
		}

		// Produce ticks (independent clock sources) for the systems to use.
		Clock->addSystemClockTicksAll(mVMOptions.TIME_SLICE_PER_RUN);

		// Unlock the mutexes.
		for (auto& system : mSystems)
		{
			if (system.second != nullptr)
			{
				system.second->mThreadRun = true;
				system.second->mThreadMutex.unlock();
			}
		}

		// Notify them.
		for (auto& system : mSystems)
		{
			if (system.second != nullptr)
				system.second->mThreadSync.notify_all();
		}
	}
	else
	{
		// Running in single threaded mode.
		// Produce ticks (independent clock sources) for the systems to use.
		Clock->addSystemClockTicksAll(mVMOptions.TIME_SLICE_PER_RUN);

		// Run through each of the systems separately.
		for (auto& system : mSystems)
		{
			if (system.second != nullptr)
				system.second->run();
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
