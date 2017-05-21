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
#include "VM/Systems/CDVD/CDVD_s.h"
#include "VM/Systems/SPU2/SPU2_s.h"
#include "VM/Systems/GS/GSCore/GSCore_s.h"
#include "VM/Systems/GS/CRTC/CRTC_s.h"

#include "Resources/Resources_t.h"
#include "Resources/Clock/Clock_t.h"
#include "Resources/EE/EE_t.h"

VM::VM(const VMOptions & vmOptions) : 
	mVMOptions(vmOptions),
	mStatus(Stopped)
{
	// Initialise everything.
	reset();
}

VM::~VM()
{
	// Call stop to handle thread cleanup.
	stop();
}

void VM::reset()
{
	// Initialise logging.
	LOG_CALLBACK_FUNCPTR = mVMOptions.LOG_CALLBACK_FUNCPTR;
	log(Info, "VM reset started...");

	// Set status to stopped.
	mStatus = Stopped;

	// Wait for any existing system threads.
	for (auto& thread : mSystemThreads)
		thread.join();

	// Destroy the old threads.
	mSystemThreads.empty();

	log(Info, "VM system threads state reset.");

	// Initialise resources and set system bias speeds.
	mResources = std::make_shared<Resources_t>();
	mResources->Clock->setSystemClockBiases(mVMOptions.SYSTEM_BIASES);

	log(Info, "VM resources initialised.");

	// Initialise Roms.
	if (!mVMOptions.BOOT_ROM_PATH.empty())
		mResources->EE->BootROM->readFile(mVMOptions.BOOT_ROM_PATH.c_str(), 0, Constants::EE::ROM::SIZE_BOOT_ROM, 0); // BootROM.
	// ROM1.
	// ROM2.
	// EROM.

	log(Info, "VM roms initialised.");

	// Create components.
	auto vu0temp = std::make_shared<VUInterpreter_s>(this, 0);
	mSystems =
	{
		std::make_shared<EECoreInterpreter_s>(this, vu0temp),
		std::make_shared<EEDmac_s>(this),
		std::make_shared<EETimers_s>(this),
		std::make_shared<EEIntc_s>(this),
		// std::make_shared<GIF_s>(this),
		// std::make_shared<IPU_s>(this),
		std::make_shared<VIF_s>(this, 0),
		vu0temp,
		std::make_shared<VIF_s>(this, 1),
		std::make_shared<VUInterpreter_s>(this, 1),
		std::make_shared<IOPCoreInterpreter_s>(this),
		std::make_shared<IOPDmac_s>(this),
		std::make_shared<IOPTimers_s>(this),
		std::make_shared<IOPIntc_s>(this),
		std::make_shared<CDVD_s>(this),
		std::make_shared<SPU2_s>(this),
		std::make_shared<GSCore_s>(this),
		std::make_shared<CRTC_s>(this),
	};

	// Initialise systems.
	for (auto& system : mSystems)
		system->initialise();

	log(Info, "VM systems initialised.");

	// Reset done, set status to paused now (threads created will exit otherwise).
	mStatus = Paused;

	// Create system threads.
	for (auto& system : mSystems)
		mSystemThreads.push_back(std::thread(&VMSystem_t::run, system.get()));

	log(Info, "VM system threads initialised.");
	log(Info, "VM reset done, now paused.");
}

void VM::reset(const VMOptions& options)
{
	mVMOptions = options;
	reset();
}

void VM::run()
{
	// Reset() must have been called before attempting to run.
	if (mStatus == Stopped)
		throw std::runtime_error("VM needs to be reset first before running!");

	// Produce ticks (independent clock sources) for the systems to use.
	getResources()->Clock->addSystemClockTicksAll(mVMOptions.TIME_SLICE_PER_RUN);

	// Set to running.
	mStatus = Running;

	if (mVMOptions.USE_MULTI_THREADED_SYSTEMS)
	{
		// Run through each of the systems simultaneously.
		for (auto& system : mSystems)
			system->notify();

		// Re-synchonise the threads (lock), check for any exceptions.
		for (auto& system : mSystems)
		{
			system->mThreadMutex.lock();
			if (system->mIsExcepted)
				throw std::runtime_error(system->mExceptionMessage);
		}
	}
	else
	{
		// Run through each of the systems sequentially.
		for (auto& system : mSystems)
		{
			// Notify system.
			system->notify();

			// Re-synchonise the threads (lock), check for any exceptions.
			system->mThreadMutex.lock();
			if (system->mIsExcepted)
				throw std::runtime_error(system->mExceptionMessage);
		}
	}

	// Set to paused.
	mStatus = Paused;
}

void VM::stop()
{
	// Set to stopped.
	mStatus = Stopped;

	// Notify systems.
	for (auto& system : mSystems)
		system->notify();

	// Join existing system threads.
	for (auto& thread : mSystemThreads)
		thread.join();

	// Destroy the old threads.
	mSystemThreads.empty();

	// Destroy the resources.
	mResources.reset();

	log(Info, "VM stopped ok.");
	LOG_CALLBACK_FUNCPTR = nullptr;
}

VM::VMStatus VM::getStatus() const
{
	return mStatus;
}

const std::shared_ptr<Resources_t> & VM::getResources() const
{
	return mResources;
}