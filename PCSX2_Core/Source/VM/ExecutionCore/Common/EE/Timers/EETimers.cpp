#include "stdafx.h"

#include "Common/Types/Context_t.h"

#include "VM/ExecutionCore/Common/EE/Timers/EETimers.h"

#include "PS2Constants/PS2Constants.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/Timers/EETimers_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimer_t.h"
#include "PS2Resources/EE/INTC/EEIntc_t.h"
#include "PS2Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "PS2Resources/GS/GS_t.h"

EETimers::EETimers(VMMain * vmMain) :
	VMExecutionCoreComponent(vmMain), 
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

s64 EETimers::executionStep(const ClockSource_t & clockSource)
{
	// Set context.
	mClockSource = clockSource;

	// Update the timers which are set to count based on the type of event recieved.
	for (mTimerIndex = 0; mTimerIndex < PS2Constants::EE::Timers::NUMBER_TIMERS; mTimerIndex++)
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

					const u8 * gateSources[] = { &mGS->SIGNAL_HBLNK, &mGS->SIGNAL_VBLNK };
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

			// Check for zero return (ZRET) conditions (perform after interrupt check, otherwise interrupt may be missed).
			handleTimerZRET();
		}
	}

	// Timers has completed 1 cycle.
	return 1;
}

bool EETimers::isTimerCLKSEqual() const
{	
	// Static array used to cast the CLKS into the correct emulator ClockSource_t type. See EE Users Manual page 36.
	const ClockSource_t emuCLKS[4] = { ClockSource_t::BUSCLK, ClockSource_t::BUSCLK16, ClockSource_t::BUSCLK256, ClockSource_t::HBLNK };
	auto CLKS = emuCLKS[mTimer->MODE->getFieldValue(EETimersTimerRegister_MODE_t::Fields::CLKS)];
	return (CLKS == mClockSource);
}

void EETimers::handleTimerInterrupt() const
{

	bool interrupt = false;

	// Check for Compare-Interrupt.
	if (mTimer->MODE->getFieldValue(EETimersTimerRegister_MODE_t::Fields::CMPE))
	{
		if (mTimer->COUNT->readWord(Context_t::RAW) >= mTimer->COMP->readWord(Context_t::RAW))
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

	// Assert interrupt bit if flag set, otherwise deassert.
	if (interrupt)
		mINTC->STAT->setFieldValue(EEIntcRegister_STAT_t::Fields::TIM_KEYS[mTimerIndex], 1);
	else
		mINTC->STAT->setFieldValue(EEIntcRegister_STAT_t::Fields::TIM_KEYS[mTimerIndex], 0);
}

void EETimers::handleTimerZRET() const
{
	// Check for ZRET condition.
	if (mTimer->MODE->getFieldValue(EETimersTimerRegister_MODE_t::Fields::ZRET))
	{
		// Check for Count >= Compare.
		if (mTimer->COUNT->readWord(Context_t::RAW) >= mTimer->COMP->readWord(Context_t::RAW))
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

	const u8 * gateSources[] = { &mGS->SIGNAL_HBLNK, &mGS->SIGNAL_VBLNK };
	const u8 * gateSourcesLast[] = { &mGS->SIGNAL_HBLNK_LAST, &mGS->SIGNAL_VBLNK_LAST };
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
