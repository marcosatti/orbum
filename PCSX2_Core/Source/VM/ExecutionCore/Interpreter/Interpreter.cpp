#include "stdafx.h"

#include "Common/Global/Globals.h"


#include "VM/ExecutionCore/Interpreter/Interpreter.h"
#include "VM/VMMain.h"

#include "VM/ExecutionCore/Interpreter/EE/VPU/VUInterpreter/VUInterpreter.h"
#include "VM/ExecutionCore/Common/EE/VPU/VIF/VIF.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/ExecutionCore/Common/EE/DMAC/EEDmac.h"
#include "VM/ExecutionCore/Common/EE/INTC/EEIntc.h"
#include "VM/ExecutionCore/Common/EE/Timers/EETimers.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreInterpreter.h"
#include "VM/ExecutionCore/Common/IOP/INTC/IOPIntc.h"
#include "VM/ExecutionCore/Common/IOP/DMAC/IOPDmac.h"
#include "VM/ExecutionCore/Common/IOP/Timers/IOPTimers.h"
#include <thread>

Interpreter::Interpreter(VMMain * vmMain) :
	VMExecutionCore(vmMain),
	mInterpreterVU0(std::make_shared<VUInterpreter>(vmMain, 0)),
	mInterpreterVU1(std::make_shared<VUInterpreter>(vmMain, 1)),
	mVIF0(std::make_shared<VIF>(vmMain, 0)),
	mVIF1(std::make_shared<VIF>(vmMain, 1)),
	mEECoreInterpreter(std::make_shared<EECoreInterpreter>(vmMain, mInterpreterVU0)),
	mEEDmac(std::make_shared<EEDmac>(vmMain)),
	mEEIntc(std::make_shared<EEIntc>(vmMain)),
	mEETimers(std::make_shared<EETimers>(vmMain)),
	mIOPCoreInterpreter(std::make_shared<IOPCoreInterpreter>(vmMain)),
	mIOPIntc(std::make_shared<IOPIntc>(vmMain)),
	mIOPDmac(std::make_shared<IOPDmac>(vmMain)),
	mIOPTimers(std::make_shared<IOPTimers>(vmMain)),
	mComponents{ mEECoreInterpreter, mInterpreterVU0, mInterpreterVU1, mEEDmac, mEEIntc, mEETimers, mIOPCoreInterpreter, mIOPIntc, mIOPDmac, mIOPTimers }
{
}

Interpreter::~Interpreter()
{
}

void Interpreter::initalise()
{
	// Iterate through all components, initalising them.
	for (auto& component : mComponents)
		component->initalise();
}

void Interpreter::execute()
{
	std::vector<std::thread> threads;

	for (auto& component : mComponents)
	{
		threads.push_back(std::thread(&VMExecutionCoreComponent::executeBlock, &(*component)));
	}

	while (getVM()->getStatus() == VMMain::RUNNING)
	{
		// Aquire all mutex locks first (common sync point).
		for (auto& component : mComponents)
		{
			component->mSyncMutex.lock();
		}

		// Produce ticks for all components.
		for (auto& component : mComponents)
		{
			component->produceTicks(1000.0);
			component->run = true;
		}

		// Unlock the mutexes.
		for (auto& component : mComponents)
		{
			component->mSyncMutex.unlock();
		}

		// Notify them.
		for (auto& component : mComponents)
		{
			component->mSyncCV.notify_all();
		}
	}

	for (auto& t : threads)
		t.join();
}
