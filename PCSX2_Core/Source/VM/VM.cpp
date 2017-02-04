#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Memory/ROMemory_t.h"

#include "VM/VM.h"
#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/Systems/EE/DMAC/EEDmac.h"
#include "VM/Systems/EE/Timers/EETimers.h"
#include "VM/Systems/EE/INTC/EEIntc.h"
#include "VM/Systems/EE/VPU/VIF/VIF.h"
#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter.h"
#include "VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter.h"
#include "VM/Systems/IOP/DMAC/IOPDmac.h"
#include "VM/Systems/IOP/Timers/IOPTimers.h"
#include "VM/Systems/IOP/INTC/IOPIntc.h"

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
	// Initalise logging.
	LOG_CALLBACK_FUNCPTR = mVMOptions.LOG_CALLBACK_FUNCPTR;
	log(Info, "VM reset started...");

	// Initalise resources.
	mResources = std::make_shared<Resources_t>();

	// Set system speed bias's.
	mResources->Clock->setSystemSpeedBias(System_t::EECore,    mVMOptions.EE_CORE_BIAS);
	mResources->Clock->setSystemSpeedBias(System_t::EEDmac,    mVMOptions.EE_DMAC_BIAS);
	mResources->Clock->setSystemSpeedBias(System_t::EETimers,  mVMOptions.EE_TIMERS_BIAS);
	mResources->Clock->setSystemSpeedBias(System_t::EEIntc,    mVMOptions.EE_INTC_BIAS);
	mResources->Clock->setSystemSpeedBias(System_t::VIF0,      mVMOptions.VIF0_BIAS);
	mResources->Clock->setSystemSpeedBias(System_t::VU0,       mVMOptions.VU0_BIAS);
	mResources->Clock->setSystemSpeedBias(System_t::VIF1,      mVMOptions.VIF1_BIAS);
	mResources->Clock->setSystemSpeedBias(System_t::VU1,       mVMOptions.VU1_BIAS);
	mResources->Clock->setSystemSpeedBias(System_t::IOPCore,   mVMOptions.IOP_CORE_BIAS);
	mResources->Clock->setSystemSpeedBias(System_t::IOPDmac,   mVMOptions.IOP_DMAC_BIAS);
	mResources->Clock->setSystemSpeedBias(System_t::IOPTimers, mVMOptions.IOP_TIMERS_BIAS);
	mResources->Clock->setSystemSpeedBias(System_t::IOPIntc,   mVMOptions.IOP_INTC_BIAS);

	log(Info, "VM resources initalised.");

	// Initalise Roms.
	getResources()->EE->BootROM->readFile(mVMOptions.BOOT_ROM_PATH, 0, Constants::EE::ROM::SIZE_BOOT_ROM, 0); // BootROM.
	// ROM1.
	// ROM2.
	// EROM.

	log(Info, "VM roms initalised.");

	// Set to running.
	mStatus = Running;

	// Create components.
	mInterpreterVU0 = std::make_shared<VUInterpreter>(this, 0);
	mInterpreterVU1 = std::make_shared<VUInterpreter>(this, 1);
	mVIF0 = std::make_shared<VIF>(this, 0);
	mVIF1 = std::make_shared<VIF>(this, 1);
	mEECoreInterpreter = std::make_shared<EECoreInterpreter>(this, mInterpreterVU0);
	mEEDmac = std::make_shared<EEDmac>(this);
	mEEIntc = std::make_shared<EEIntc>(this);
	mEETimers = std::make_shared<EETimers>(this);
	mIOPCoreInterpreter = std::make_shared<IOPCoreInterpreter>(this);
	mIOPIntc = std::make_shared<IOPIntc>(this);
	mIOPDmac = std::make_shared<IOPDmac>(this);
	mIOPTimers = std::make_shared<IOPTimers>(this);
	mSystems = { mEECoreInterpreter, mInterpreterVU0, mInterpreterVU1, mEEDmac, mEEIntc, mEETimers, mIOPCoreInterpreter, mIOPIntc, mIOPDmac, mIOPTimers };

	// Initalise components.
	for (auto& system : mSystems)
		system->initalise();

	// Use multithreaded systems if enabled.
	if (mVMOptions.USE_MULTI_THREADED_SYSTEMS)
	{
		// Clear any existing threads... could be dangerous since we have detached them... TODO: look into this.
		mSystemThreads.empty();

		// Initalise threads.
		for (auto& component : mSystems)
			mSystemThreads.push_back(std::thread(&VMSystem_t::threadLoop, &(*component)));

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

	log(Info, "VM systems initalised.");
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
	}
	else
	{
		// Running in single threaded mode.
		// Run through each of the systems separately.
		for (auto& system : mSystems)
		{
			system->produceTicks(ClockSource_t::EECore, mVMOptions.TIME_SLICE_PER_RUN / 1.0e6 * Constants::EE::EECore::EECORE_CLK_SPEED);
			system->executeTicks();
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