

#include "VM/VM.h"
#include "VM/Systems/EE/Timers/EETimers_s.h"

#include "Resources/RResources.hpp"
#include "Resources/Ee/REe.hpp"
#include "Resources/Ee/Timers/REeTimers.hpp"
#include "Resources/Ee/Timers/EeTimersUnitRegisters.hpp"
#include "Resources/EE/Timers/Types/EETimersTimers_t.h"
#include "Resources/Ee/Intc/REeIntc.hpp"
#include "Resources/Ee/Intc/EeIntcRegisters.hpp"
#include "Resources/GS/RGs.h"

EETimers_s::EETimers_s(VM * vm) :
	VMSystem_t(vm, Context_t::EETimers),
	mTimer(nullptr)
{
	// Set resource pointer variables.
	mTimers = getVM()->getResources()->EE->Timers;
	mINTC = getVM()->getResources()->EE->INTC;
	mGS = getVM()->getResources()->GS;
}

void EETimers_s::initialise()
{
	for (auto& timer : mTimers->TIMERS)
	{
		if (timer->COUNT != nullptr) timer->COUNT->initialise();
		if (timer->MODE != nullptr) timer->MODE->initialise();
		if (timer->COMP != nullptr) timer->COMP->initialise();
		if (timer->HOLD != nullptr) timer->HOLD->initialise();
	}
}

int EETimers_s::step(const Event_t & event)
{
	// Used to skip ticks. If no timer is enabled for counting, then all of the ticks will be consumed at the end.
	bool workDone = false;

	// Update the timers which are set to count based on the type of event recieved.
	for (auto& timer : mTimers->TIMERS)
	{
		// Set timer resource context.
		mTimer = timer.get();

		// Count only if enabled.
		if (mTimer->MODE->getFieldValue(, EeTimersUnitRegister_Mode::CUE) > 0)
		{
			// Check if the timer mode is equal to the clock source.
			if (event.mSource == mTimer->MODE->getEventSource())
			{
				// A timer consumed a tick for this clock source - do not skip any ticks.
				workDone = true;

				// Next check for the gate function. Also check for a special gate condition, for when CLKS == H_BLNK and GATS == HBLNK, 
				//  in which case count normally.
				if (mTimer->MODE->getFieldValue(, EeTimersUnitRegister_Mode::GATE)
					&& !mTimer->MODE->isGateHBLNKSpecial())
				{
					// Check if the timer needs to be reset.
					handleTimerGateReset();

					// If the timer is using GATM = 0, need to check if the signal is low first.
					if (mTimer->MODE->getFieldValue(, EeTimersUnitRegister_Mode::GATM) == 0)
					{
						throw std::runtime_error("EE Timer gate function not fully implemented (dependant on GS). Fix this up when completed.");

						const ubyte * gateSources[] = { nullptr, nullptr };
						uword index = mTimer->MODE->getFieldValue(, EeTimersUnitRegister_Mode::GATS);
						if (!(*gateSources[index]))
							mTimer->COUNT->increment(, 1);
					}
					else
					{
						mTimer->COUNT->increment(, 1);
					}
				}
				else
				{
					// Count normally without gate.
					mTimer->COUNT->increment(, 1);
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
		return event.mQuantity;
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
	if (mTimer->MODE->getFieldValue(, EeTimersUnitRegister_Mode::CMPE))
	{
		if (mTimer->COUNT->read_uword() == mTimer->COMP->read_uword())
		{
			interrupt = true;
		}
	}

	// Check for Overflow-Interrupt.
	if (mTimer->MODE->getFieldValue(, EeTimersUnitRegister_Mode::OVFE))
	{
		if (mTimer->COUNT->isOverflowed())
		{
			interrupt = true;
		}
	}

	// Assert interrupt bit if flag set. IRQ line for timers is 9 -> 12.
	// TODO: not sure if we need to deassert... the INTC is edge triggered. "...At the edge of an interrupt request signal..." see EE Users Manual page 28.
	if (interrupt)
		mINTC->STAT->setFieldValue(, EeIntcRegister_Stat::TIM_KEYS[mTimer->getTimerID()], 1);
}

void EETimers_s::handleTimerZRET() const
{
	// Check for ZRET condition.
	if (mTimer->MODE->getFieldValue(, EeTimersUnitRegister_Mode::ZRET))
	{
		// Check for Count >= Compare.
		if (mTimer->COUNT->read_uword() == mTimer->COMP->read_uword())
		{
			// Set Count to 0.
			mTimer->COUNT->reset();
		}
	}
}

void EETimers_s::handleTimerGateReset() const
{
	throw std::runtime_error("EE Timer gate function not fully implemented (dependant on GS). Fix this up when completed.");

	auto GATM = mTimer->MODE->getFieldValue(, EeTimersUnitRegister_Mode::GATM);
	auto GATS = mTimer->MODE->getFieldValue(, EeTimersUnitRegister_Mode::GATS);

	const ubyte * gateSources[] = { nullptr, nullptr };
	const ubyte * gateSourcesLast[] = {nullptr, nullptr };
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
		// Resets and starts counting at the gate signal�s rising edge.
		if (gateSource && !gateSourceLast)
			mTimer->COUNT->reset();
		break;
	}
	case 2:
	{
		// Resets and starts counting at the gate signal�s falling edge.
		if (!gateSource && gateSourceLast)
			mTimer->COUNT->reset();
		break;
	}
	case 3:
	{
		// Resets and starts counting at both edges of the gate signal.
		if ((gateSource && !gateSourceLast) || (!gateSource && gateSourceLast))
			mTimer->COUNT->reset();
		break;
	}
	default:
	{
		throw std::runtime_error("Could not determine timer gate context (GATM). Please fix!");
	}
	}
}
