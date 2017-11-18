

#include "VM/VM.h"
#include "VM/Systems/IOP/Timers/IOPTimers_s.h"

#include "Resources/RResources.hpp"
#include "Resources/IOP/IOP_t.h"
#include "Resources/IOP/Timers/IOPTimers_t.h"
#include "Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"
#include "Resources/IOP/Timers/Types/IOPTimersTimers_t.h"
#include "Resources/Iop/Intc/RIopIntc.hpp"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"

IOPTimers_s::IOPTimers_s(VM * vm) :
	VMSystem_t(vm, Context_t::IOPTimers),
	mTimer(nullptr)
{
	// Set resource pointer variables.
	mTimers = getVM()->getResources()->IOP->Timers;
	mINTC = getVM()->getResources()->IOP->INTC;
}

void IOPTimers_s::initialise()
{
	for (auto& timer : mTimers->TIMERS)
	{
		if (timer->COUNT != nullptr) timer->COUNT->initialise();
		if (timer->MODE != nullptr) timer->MODE->initialise();
		if (timer->COMP != nullptr) timer->COMP->initialise();
	}
}

int IOPTimers_s::step(const Event_t & event)
{
	// Used to skip ticks. If no timer is enabled for counting, then all of the ticks will be consumed at the end.
	bool workDone = false;

	// Update the timers which are set to count based on the type of event recieved.
	for (auto& timer : mTimers->TIMERS)
	{
		// Set timer resource context.
		mTimer = timer.get();
		
		// Count only if "enabled". There is no explicit "enable bit" in the IOP timers, however a timer is only useful to us if it can cause an interrupt, so we use this to check.
		// If a timer is written to (such that interrupt conditions are now enabled), the count register is cleared upon write anyway.
		// This means we do not have to consider the case where the timer suddenly comes alive, with a populated count register, therefore missing the interrupt condition.
		if (mTimer->MODE->isEnabled())
		{
			// Check if the timer mode is equal to the clock source.
			if (event.mSource == mTimer->MODE->getEventSource())
			{
				// A timer consumed a tick for this clock source - do not skip any ticks.
				workDone = true;

				// Next check for the gate function.
				if (mTimer->MODE->getFieldValue(, IOPTimersTimerRegister_MODE_t::SyncEnable) > 0)
				{
					throw std::runtime_error("IOP Timers sync mode (gate) = 1, but not implemented.");
				}
				else
				{
					// Count normally without gate.
					mTimer->COUNT->increment(, 1);
				}

				// Check for interrupt conditions on the timer. Needs to be done before handling the overflow or target conditions.
				handleTimerInterrupt();

				// Check for overflow conditions on the timer.
				handleTimerOverflow();

				// Check for target conditions on the timer.
				handleTimerTarget();
			}
		}
	}

	// Timers has completed 1 cycle.
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
	if (!workDone)
		return event.mQuantity;
	else
		return 1;
#else
	return 1;
#endif
}

void IOPTimers_s::handleTimerInterrupt() const
{
	bool interrupt = false;

	// Check for Compare-Interrupt.
	if (mTimer->MODE->getFieldValue(, IOPTimersTimerRegister_MODE_t::IrqOnTarget))
	{
		if (mTimer->COUNT->read_uword() == mTimer->COMP->read_uword())
		{
			interrupt = true;
		}
	}

	// Check for Overflow-Interrupt.
	if (mTimer->MODE->getFieldValue(, IOPTimersTimerRegister_MODE_t::IrqOnOF))
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
		if (mTimer->MODE->getFieldValue(, IOPTimersTimerRegister_MODE_t::IrqRepeat))
		{
			// Check for IRQ toggle mode.
			if (mTimer->MODE->getFieldValue(, IOPTimersTimerRegister_MODE_t::IrqToggle))
			{
				// Toggle bit.
				throw std::runtime_error("IOP Timers int toggle mode not implemented.");
				// uword value = mTimer->MODE->getFieldValue(, IOPTimersTimerRegister_MODE_t::IrqRequest);
				// mTimer->MODE->setFieldValue(, IOPTimersTimerRegister_MODE_t::IrqRequest, value ^ 1);
			}
			else
			{
				// Set bit low (0).
				mTimer->MODE->setFieldValue(, IOPTimersTimerRegister_MODE_t::IrqRequest, 0);
			}
		}
		else
		{
			throw std::runtime_error("IOP Timers int oneshot mode not implemented.");
		}

		// Check for internal interrupt bit is low, and send INTC interrupt.
		if (mTimer->MODE->getFieldValue(, IOPTimersTimerRegister_MODE_t::IrqRequest) == 0)
		{
			// Raise IRQ.
			mINTC->STAT->setFieldValue(, IOPIntcRegister_STAT_t::TMR_KEYS[mTimer->getTimerID()], 1);
		}
	}
}

void IOPTimers_s::handleTimerOverflow() const
{
	// Check for overflow conditions.
	if (mTimer->COUNT->isOverflowed())
	{
		// Check for target reset condition.
		if (mTimer->MODE->getFieldValue(, IOPTimersTimerRegister_MODE_t::ResetMode) == 0)
		{
			// Set Count to 0.
			mTimer->COUNT->reset();
		}

		// Set reach overflow bit.
		mTimer->MODE->setFieldValue(, IOPTimersTimerRegister_MODE_t::ReachOF, 1);
	}
}

void IOPTimers_s::handleTimerTarget() const
{
	// Check for Count >= Compare.
	if (mTimer->COUNT->read_uword() == mTimer->COMP->read_uword())
	{
		// Check for target reset condition.
		if (mTimer->MODE->getFieldValue(, IOPTimersTimerRegister_MODE_t::ResetMode) > 0)
		{
			// Set Count to 0.
			mTimer->COUNT->reset();
		}

		// Set reach target bit.
		mTimer->MODE->setFieldValue(, IOPTimersTimerRegister_MODE_t::ReachTarget, 1);
	}
}
