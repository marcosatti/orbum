#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/Systems/EE/Timers/EETimers.h"

#include "Common/Global/Globals.h"

#include "Resources/Resources_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/EE/Timers/EETimers_t.h"
#include "Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"
#include "Resources/EE/Timers/Types/EETimersTimers_t.h"
#include "Resources/EE/INTC/EEIntc_t.h"
#include "Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "Resources/GS/GS_t.h"

EETimers::EETimers(VM * vmMain) :
	VMSystem_t(vmMain, System_t::EETimers), 
	mTimerIndex(0), 
	mTimer(nullptr),
	mClockSource()
{
	// Set resource pointer variables.
	mTimers = getResources()->EE->Timers;
	mINTC = getResources()->EE->INTC;
	mGS = getResources()->GS;
}

EETimers::~EETimers()
{
}

double EETimers::executeStep(const ClockSource_t & clockSource, const double & ticksAvailable)
{
	// Set context.
	mClockSource = clockSource;

	// Update the timers which are set to count based on the type of event recieved.
	for (mTimerIndex = 0; mTimerIndex < Constants::EE::Timers::NUMBER_TIMERS; mTimerIndex++)
	{
		// Set context.
		mTimer = &(*mTimers->TIMERS[mTimerIndex]); // I give up, for now I need the speed for debugging. Change back later & sort out why this is so slow.

		// Count only if enabled.
		if (mTimer->MODE->getFieldValue(EETimersTimerRegister_MODE_t::Fields::CUE) == 0)
			continue;

		// Check if the timer mode is equal to the clock source.
		if (isTimerCLKSEqual())
		{
			// Next check for the gate function. Also check for a special gate condition, for when CLKS == H_BLNK and GATS == HBLNK, 
			//  in which case count normally.
			if (mTimer->MODE->getFieldValue(EETimersTimerRegister_MODE_t::Fields::GATE) 
				&& !mTimer->MODE->isGateHBLNKSpecial())
			{
				// Check if the timer needs to be reset.
				handleTimerGateReset();

				// If the timer is using GATM = 0, need to check if the signal is low first.
				if (mTimer->MODE->getFieldValue(EETimersTimerRegister_MODE_t::Fields::GATM) == 0)
				{
					throw std::runtime_error("EE Timer gate function not fully implemented (dependant on GS). Fix this up when completed.");

					const u8 * gateSources[] = { nullptr, nullptr };
					u32 index = mTimer->MODE->getFieldValue(EETimersTimerRegister_MODE_t::Fields::GATS);
					if (!(*gateSources[index]))
						mTimer->COUNT->increment(1);
				}
				else
				{
					mTimer->COUNT->increment(1);
				}
			}
			else
			{
				// Count normally without gate.
				mTimer->COUNT->increment(1);
			}

			// Check for interrupt conditions on the timer.
			handleTimerInterrupt();

			// Check for zero return (ZRET) conditions (perform after interrupt check, otherwise this may cause interrupt to be missed).
			handleTimerZRET();
		}
	}

	// Timers has completed 1 cycle.
	return 1;
}

bool EETimers::isTimerCLKSEqual() const
{	
	// Static array used to cast the CLKS into the correct emulator ClockSource_t type. See EE Users Manual page 36.
	static const ClockSource_t emuCLKS[4] = { ClockSource_t::EEBus, ClockSource_t::EEBus16, ClockSource_t::EEBus256, ClockSource_t::HBLNK };
	auto CLKS = emuCLKS[mTimer->MODE->getFieldValue(EETimersTimerRegister_MODE_t::Fields::CLKS)];
	return (CLKS == mClockSource);
}

void EETimers::handleTimerInterrupt() const
{
	bool interrupt = false;

	// Check for Compare-Interrupt.
	if (mTimer->MODE->getFieldValue(EETimersTimerRegister_MODE_t::Fields::CMPE))
	{
		if (mTimer->COUNT->readWord(RAW) == mTimer->COMP->readWord(RAW))
		{
			interrupt = true;
		}
	}

	// Check for Overflow-Interrupt.
	if (mTimer->MODE->getFieldValue(EETimersTimerRegister_MODE_t::Fields::OVFE))
	{
		if (mTimer->COUNT->isOverflowed())
		{
			interrupt = true;
		}
	}

	// Assert interrupt bit if flag set. IRQ line for timers is 9 -> 12.
	// TODO: not sure if we need to deassert... the INTC is edge triggered. "...At the edge of an interrupt request signal..." see EE Users Manual page 28.
	if (interrupt)
		mINTC->STAT->setFieldValue(EEIntcRegister_STAT_t::Fields::TIM_KEYS[mTimerIndex], 1);
}

void EETimers::handleTimerZRET() const
{
	// Check for ZRET condition.
	if (mTimer->MODE->getFieldValue(EETimersTimerRegister_MODE_t::Fields::ZRET))
	{
		// Check for Count >= Compare.
		if (mTimer->COUNT->readWord(RAW) == mTimer->COMP->readWord(RAW))
		{
			// Set Count to 0.
			mTimer->COUNT->reset();
		}
	}
}

void EETimers::handleTimerGateReset() const
{
	throw std::runtime_error("EE Timer gate function not fully implemented (dependant on GS). Fix this up when completed.");

	auto GATM = mTimer->MODE->getFieldValue(EETimersTimerRegister_MODE_t::Fields::GATM);
	auto GATS = mTimer->MODE->getFieldValue(EETimersTimerRegister_MODE_t::Fields::GATS);

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
			mTimer->COUNT->reset();
		break;
	}
	case 2:
	{
		// Resets and starts counting at the gate signal’s falling edge.
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
