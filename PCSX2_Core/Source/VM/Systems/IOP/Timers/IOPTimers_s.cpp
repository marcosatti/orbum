#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Systems/IOP/Timers/IOPTimers_s.h"

#include "Resources/Resources_t.h"
#include "Resources/IOP/IOP_t.h"
#include "Resources/IOP/Timers/IOPTimers_t.h"
#include "Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"
#include "Resources/IOP/Timers/Types/IOPTimersTimers_t.h"
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"

IOPTimers_s::IOPTimers_s(VM * vm) :
	VMSystem_s(vm, System_t::IOPTimers),
	mTimerIndex(0),
	mTimer(nullptr)
{
	// Set resource pointer variables.
	mTimers = getVM()->getResources()->IOP->Timers;
	mINTC = getVM()->getResources()->IOP->INTC;
}

IOPTimers_s::~IOPTimers_s()
{
}

int IOPTimers_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	// Update the timers which are set to count based on the type of event recieved.
	for (mTimerIndex = 0; mTimerIndex < Constants::IOP::Timers::NUMBER_TIMERS; mTimerIndex++)
	{
		// Set context.
		mTimer = &(*mTimers->TIMERS[mTimerIndex]); // I give up, for now I need the speed for debugging. Change back later & sort out why this is so slow.
		
		// Count only if "enabled". There is no explicit "enable bit" in the IOP timers, however a timer is only useful to us if it can cause an interrupt, so we use this to check.
		// If a timer is written to (such that interrupt conditions are now enabled), the count register is cleared upon write anyway.
		// This means we do not have to consider the case where the timer suddenly comes alive, with a populated count register.
		if (!mTimer->MODE->isEnabled())
			continue;

		// Check if the timer mode is equal to the clock source.
		if (clockSource == mTimer->MODE->getClockSource())
		{
			// Next check for the gate function.
			if (mTimer->MODE->getFieldValue(IOPTimersTimerRegister_MODE_t::Fields::SyncEnable) > 0)
			{
				throw std::runtime_error("IOP Timers sync mode (gate) = 1, but not implemented.");
			}
			else
			{
				// Count normally without gate.
				mTimer->COUNT->increment(1);
			}

			// Check for interrupt conditions on the timer.
			handleTimerInterrupt();

			// Check for overflow conditions on the timer.
			handleTimerOverflow();

			// Check for target conditions on the timer.
			handleTimerTarget();
		}
	}

	// Timers has completed 1 cycle.
	return 1;
}

void IOPTimers_s::handleTimerInterrupt() const
{
	bool interrupt = false;

	// Check for Compare-Interrupt.
	if (mTimer->MODE->getFieldValue(IOPTimersTimerRegister_MODE_t::Fields::IrqOnTarget))
	{
		if (mTimer->COUNT->readWord(RAW) == mTimer->COMP->readWord(RAW))
		{
			interrupt = true;
		}
	}

	// Check for Overflow-Interrupt.
	if (mTimer->MODE->getFieldValue(IOPTimersTimerRegister_MODE_t::Fields::IrqOnOF))
	{
		if (mTimer->COUNT->isOverflowed())
		{
			interrupt = true;
		}
	}

	// Handle internal interrupt bit if interrupt flag set. 
	// TODO: needs work. I dont know how the IOP expects this to work and I cant figure out what PCSX2 does.
	if (interrupt)
	{
		// If after this code block has run, and the internal IrqRequest bit is low (0), then an external interrupt should be generated (ie: to INTC).
		// Check if we are using one-shot or repeat.
		if (mTimer->MODE->getFieldValue(IOPTimersTimerRegister_MODE_t::Fields::IrqRepeat))
		{
			// Check for IRQ toggle mode.
			if (mTimer->MODE->getFieldValue(IOPTimersTimerRegister_MODE_t::Fields::IrqToggle))
			{
				// Toggle bit.
				u32 value = mTimer->MODE->getFieldValue(IOPTimersTimerRegister_MODE_t::Fields::IrqRequest);
				mTimer->MODE->setFieldValue(IOPTimersTimerRegister_MODE_t::Fields::IrqRequest, value ^ 1);
			}
			else
			{
				// Set bit low (0).
				mTimer->MODE->setFieldValue(IOPTimersTimerRegister_MODE_t::Fields::IrqRequest, 0);
			}
		}
		else
		{
			throw std::runtime_error("IOP Timers oneshot mode not implemented.");
		}

		// Check for internal interrupt bit is low, and send INTC interrupt.
		if (mTimer->MODE->getFieldValue(IOPTimersTimerRegister_MODE_t::Fields::IrqRequest) == 0)
		{
			// Raise IRQ.
			mINTC->STAT->setFieldValue(IOPIntcRegister_STAT_t::Fields::TMR_KEYS[mTimerIndex], 1);
		}
	}
}

void IOPTimers_s::handleTimerOverflow() const
{
	// Check for overflow conditions.
	if (mTimer->COUNT->isOverflowed())
	{
		// Set reach overflow bit (reset is done automatically inside count register).
		mTimer->MODE->setFieldValue(IOPTimersTimerRegister_MODE_t::Fields::ReachOF, 1);
	}
}

void IOPTimers_s::handleTimerTarget() const
{
	// Check for target condition.
	if (mTimer->MODE->getFieldValue(IOPTimersTimerRegister_MODE_t::Fields::ResetMode) > 0)
	{
		// Check for Count >= Compare.
		if (mTimer->COUNT->readWord(RAW) == mTimer->COMP->readWord(RAW))
		{
			// Set Count to 0.
			mTimer->COUNT->reset();

			// Set reach target bit.
			mTimer->MODE->setFieldValue(IOPTimersTimerRegister_MODE_t::Fields::ReachTarget, 1);
		}
	}
}
