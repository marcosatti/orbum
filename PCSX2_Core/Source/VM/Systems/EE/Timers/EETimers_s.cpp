#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Systems/EE/Timers/EETimers_s.h"

#include "Resources/Resources_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/EE/Timers/EETimers_t.h"
#include "Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"
#include "Resources/EE/Timers/Types/EETimersTimers_t.h"
#include "Resources/EE/INTC/EEIntc_t.h"
#include "Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "Resources/GS/GS_t.h"

EETimers_s::EETimers_s(VM * vm) :
	VMSystem_s(vm, System_t::EETimers),
	mTimer(nullptr)
{
	// Set resource pointer variables.
	mTimers = getVM()->getResources()->EE->Timers;
	mINTC = getVM()->getResources()->EE->INTC;
	mGS = getVM()->getResources()->GS;
}

void EETimers_s::initalise()
{
	for (auto& timer : mTimers->TIMERS)
	{
		if (timer->COUNT != nullptr) timer->COUNT->initalise();
		if (timer->MODE != nullptr) timer->MODE->initalise();
		if (timer->COMP != nullptr) timer->COMP->initalise();
		if (timer->HOLD != nullptr) timer->HOLD->initalise();
	}
}

int EETimers_s::step(const ClockSource_t clockSource, const int ticksAvailable)
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

		// Count only if enabled.
		if (mTimer->MODE->getFieldValue(getContext(), EETimersTimerRegister_MODE_t::Fields::CUE) > 0)
		{
			// Check if the timer mode is equal to the clock source.
			if (clockSource == mTimer->MODE->getClockSource())
			{
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
				// A timer consumed a tick for this clock source - do not skip any ticks.
				workDone = true;
#endif
				// Next check for the gate function. Also check for a special gate condition, for when CLKS == H_BLNK and GATS == HBLNK, 
				//  in which case count normally.
				if (mTimer->MODE->getFieldValue(getContext(), EETimersTimerRegister_MODE_t::Fields::GATE)
					&& !mTimer->MODE->isGateHBLNKSpecial(getContext()))
				{
					// Check if the timer needs to be reset.
					handleTimerGateReset();

					// If the timer is using GATM = 0, need to check if the signal is low first.
					if (mTimer->MODE->getFieldValue(getContext(), EETimersTimerRegister_MODE_t::Fields::GATM) == 0)
					{
						throw std::runtime_error("EE Timer gate function not fully implemented (dependant on GS). Fix this up when completed.");

						const u8 * gateSources[] = { nullptr, nullptr };
						u32 index = mTimer->MODE->getFieldValue(getContext(), EETimersTimerRegister_MODE_t::Fields::GATS);
						if (!(*gateSources[index]))
							mTimer->COUNT->increment(getContext(), 1);
					}
					else
					{
						mTimer->COUNT->increment(getContext(), 1);
					}
				}
				else
				{
					// Count normally without gate.
					mTimer->COUNT->increment(getContext(), 1);
				}

				// Check for interrupt conditions on the timer.
				handleTimerInterrupt();

				// Check for zero return (ZRET) conditions (perform after interrupt check, otherwise this may cause interrupt to be missed).
				handleTimerZRET();
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

void EETimers_s::handleTimerInterrupt() const
{
	bool interrupt = false;

	// Check for Compare-Interrupt.
	if (mTimer->MODE->getFieldValue(getContext(), EETimersTimerRegister_MODE_t::Fields::CMPE))
	{
		if (mTimer->COUNT->readWord(getContext()) == mTimer->COMP->readWord(getContext()))
		{
			interrupt = true;
		}
	}

	// Check for Overflow-Interrupt.
	if (mTimer->MODE->getFieldValue(getContext(), EETimersTimerRegister_MODE_t::Fields::OVFE))
	{
		if (mTimer->COUNT->isOverflowed())
		{
			interrupt = true;
		}
	}

	// Assert interrupt bit if flag set. IRQ line for timers is 9 -> 12.
	// TODO: not sure if we need to deassert... the INTC is edge triggered. "...At the edge of an interrupt request signal..." see EE Users Manual page 28.
	if (interrupt)
		mINTC->STAT->setFieldValue(getContext(), EEIntcRegister_STAT_t::Fields::TIM_KEYS[mTimer->getTimerID()], 1);
}

void EETimers_s::handleTimerZRET() const
{
	// Check for ZRET condition.
	if (mTimer->MODE->getFieldValue(getContext(), EETimersTimerRegister_MODE_t::Fields::ZRET))
	{
		// Check for Count >= Compare.
		if (mTimer->COUNT->readWord(getContext()) == mTimer->COMP->readWord(getContext()))
		{
			// Set Count to 0.
			mTimer->COUNT->reset(getContext());
		}
	}
}

void EETimers_s::handleTimerGateReset() const
{
	throw std::runtime_error("EE Timer gate function not fully implemented (dependant on GS). Fix this up when completed.");

	auto GATM = mTimer->MODE->getFieldValue(getContext(), EETimersTimerRegister_MODE_t::Fields::GATM);
	auto GATS = mTimer->MODE->getFieldValue(getContext(), EETimersTimerRegister_MODE_t::Fields::GATS);

	const u8 * gateSources[] = { nullptr, nullptr };
	const u8 * gateSourcesLast[] = {nullptr, nullptr };
	auto& gateSource = gateSources[GATS];
	auto& gateSourceLast = gateSourcesLast[GATS];

	switch (GATM)
	{
	case 0:
	{
		// Do not need to reset for GATM = 0 according to the docs.
		break;
	}
	case 1:
	{
		// Resets and starts counting at the gate signal’s rising edge.
		if (gateSource && !gateSourceLast)
			mTimer->COUNT->reset(getContext());
		break;
	}
	case 2:
	{
		// Resets and starts counting at the gate signal’s falling edge.
		if (!gateSource && gateSourceLast)
			mTimer->COUNT->reset(getContext());
		break;
	}
	case 3:
	{
		// Resets and starts counting at both edges of the gate signal.
		if ((gateSource && !gateSourceLast) || (!gateSource && gateSourceLast))
			mTimer->COUNT->reset(getContext());
		break;
	}
	default:
	{
		throw std::runtime_error("Could not determine timer gate context (GATM). Please fix!");
	}
	}
}
