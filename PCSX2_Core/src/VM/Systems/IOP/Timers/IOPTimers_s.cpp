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
	VMSystem_t(vm, System_t::IOPTimers),
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

int IOPTimers_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
	// Used to skip ticks. If no timer is enabled for counting, then all of the ticks will be consumed.
	bool workDone = false;
#endif

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
			if (clockSource == mTimer->MODE->getClockSource())
			{
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
				// A timer consumed a tick for this clock source - do not skip any ticks.
				workDone = true;
#endif
				// Next check for the gate function.
				if (mTimer->MODE->getFieldValue(getContext(), IOPTimersTimerRegister_MODE_t::Fields::SyncEnable) > 0)
				{
					throw std::runtime_error("IOP Timers sync mode (gate) = 1, but not implemented.");
				}
				else
				{
					// Count normally without gate.
					mTimer->COUNT->increment(getContext(), 1);
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
		return ticksAvailable;
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
	if (mTimer->MODE->getFieldValue(getContext(), IOPTimersTimerRegister_MODE_t::Fields::IrqOnTarget))
	{
		if (mTimer->COUNT->readWord(getContext()) == mTimer->COMP->readWord(getContext()))
		{
			interrupt = true;
		}
	}

	// Check for Overflow-Interrupt.
	if (mTimer->MODE->getFieldValue(getContext(), IOPTimersTimerRegister_MODE_t::Fields::IrqOnOF))
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
		if (mTimer->MODE->getFieldValue(getContext(), IOPTimersTimerRegister_MODE_t::Fields::IrqRepeat))
		{
			// Check for IRQ toggle mode.
			if (mTimer->MODE->getFieldValue(getContext(), IOPTimersTimerRegister_MODE_t::Fields::IrqToggle))
			{
				// Toggle bit.
				throw std::runtime_error("IOP Timers int toggle mode not implemented.");
				// u32 value = mTimer->MODE->getFieldValue(getContext(), IOPTimersTimerRegister_MODE_t::Fields::IrqRequest);
				// mTimer->MODE->setFieldValue(getContext(), IOPTimersTimerRegister_MODE_t::Fields::IrqRequest, value ^ 1);
			}
			else
			{
				// Set bit low (0).
				mTimer->MODE->setFieldValue(getContext(), IOPTimersTimerRegister_MODE_t::Fields::IrqRequest, 0);
			}
		}
		else
		{
			throw std::runtime_error("IOP Timers int oneshot mode not implemented.");
		}

		// Check for internal interrupt bit is low, and send INTC interrupt.
		if (mTimer->MODE->getFieldValue(getContext(), IOPTimersTimerRegister_MODE_t::Fields::IrqRequest) == 0)
		{
			// Raise IRQ.
			mINTC->STAT->setFieldValue(getContext(), IOPIntcRegister_STAT_t::Fields::TMR_KEYS[mTimer->getTimerID()], 1);
		}
	}
}

void IOPTimers_s::handleTimerOverflow() const
{
	// Check for overflow conditions.
	if (mTimer->COUNT->isOverflowed())
	{
		// Check for target reset condition.
		if (mTimer->MODE->getFieldValue(getContext(), IOPTimersTimerRegister_MODE_t::Fields::ResetMode) == 0)
		{
			// Set Count to 0.
			mTimer->COUNT->reset(getContext());
		}

		// Set reach overflow bit.
		mTimer->MODE->setFieldValue(getContext(), IOPTimersTimerRegister_MODE_t::Fields::ReachOF, 1);
	}
}

void IOPTimers_s::handleTimerTarget() const
{
	// Check for Count >= Compare.
	if (mTimer->COUNT->readWord(getContext()) == mTimer->COMP->readWord(getContext()))
	{
		// Check for target reset condition.
		if (mTimer->MODE->getFieldValue(getContext(), IOPTimersTimerRegister_MODE_t::Fields::ResetMode) > 0)
		{
			// Set Count to 0.
			mTimer->COUNT->reset(getContext());
		}

		// Set reach target bit.
		mTimer->MODE->setFieldValue(getContext(), IOPTimersTimerRegister_MODE_t::Fields::ReachTarget, 1);
	}
}
