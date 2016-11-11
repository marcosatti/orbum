#include "stdafx.h"

#include "VM/ExecutionCore/Common/EE/Timers/EETimers.h"
#include "VM/VMMain.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/Timers/EETimers_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimers_t.h"
#include "PS2Resources/EE/INTC/EEIntc_t.h"
#include "PS2Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "PS2Resources/GS/GS_t.h"
#include "PS2Constants/PS2Constants.h"

EETimers::EETimers(VMMain * vmMain) :
	VMExecutionCoreComponent(vmMain),
	mClockSources{ClockSource_t::BUSCLK, ClockSource_t::BUSCLK16, ClockSource_t::BUSCLK256, ClockSource_t::HBLNK}
{
}

EETimers::~EETimers()
{
}

const std::vector<ClockSource_t>& EETimers::getClockSources()
{
	return mClockSources;
}

s64 EETimers::executionStep(const ClockSource_t & clockSource)
{
	auto& Timers = getVM()->getResources()->EE->Timers;
	auto& GS = getVM()->getResources()->GS;
	const u8 * gateSources[] = { &GS->SIGNAL_HBLNK, &GS->SIGNAL_VBLNK };

	// Update the timers which are set to count based on the type of event recieved.
	for (auto i = 0; i < PS2Constants::EE::Timers::NUMBER_TIMERS; i++)
	{
		// Do not count if not enabled.
		if (!Timers->TIMERS[i]->mMODE->getFieldValue(EETimersTimerRegister_Mode_t::Fields::CUE))
			continue;

		// Check if the timer mode is equal to the clock source.
		if (isTimerCLKSEqual(i, clockSource))
		{
			// Next check for the gate function. Also check for a special gate condition, for when CLKS == H_BLNK and GATS == HBLNK, 
			//  in which case count normally.
			if (Timers->TIMERS[i]->mMODE->getFieldValue(EETimersTimerRegister_Mode_t::Fields::GATE) && !isTimerGateSpecialHBLNK(i))
			{
				// Check if the timer needs to be reset.
				checkTimerGateReset(i);

				// If the timer is using GATM = 0, need to check if the signal is low first.
				if (Timers->TIMERS[i]->mMODE->getFieldValue(EETimersTimerRegister_Mode_t::Fields::GATM) == 0)
				{
					if (!gateSources[Timers->TIMERS[i]->mMODE->getFieldValue(EETimersTimerRegister_Mode_t::Fields::GATS)])
						Timers->TIMERS[i]->mCOUNT->increment(1);
				}
				else
				{
					Timers->TIMERS[i]->mCOUNT->increment(1);
				}
			}
			else
			{
				// Count normally without gate.
				Timers->TIMERS[i]->mCOUNT->increment(1);
			}

			// Check for interrupt conditions on the timer.
			checkTimerInterrupt(i);

			// Check for zero return (ZRET) conditions (perform after interrupt check, otherwise interrupt may be missed).
			checkTimerZRET(i);
		}
	}

	// Timers has completed 1 cycle.
	return 1;
}

bool EETimers::isTimerCLKSEqual(const u32 & timerNumber, const ClockSource_t & clockSource) const
{
	auto& timer = getVM()->getResources()->EE->Timers->TIMERS[timerNumber];
	
	// Static array used to cast the CLKS into the correct emulator ClockSource_t type. See EE Users Manual page 36.
	static const ClockSource_t emuCLKS[4] = { ClockSource_t::BUSCLK, ClockSource_t::BUSCLK16, ClockSource_t::BUSCLK256, ClockSource_t::HBLNK };
	auto CLKS = emuCLKS[timer->mMODE->getFieldValue(EETimersTimerRegister_Mode_t::Fields::CLKS)];

	if (CLKS == clockSource)
		return true;
	else
		return false;
}

void EETimers::checkTimerInterrupt(const u32& timerNumber) const
{
	auto& I_STAT = getVM()->getResources()->EE->INTC->REGISTER_STAT; 
	auto& timer = getVM()->getResources()->EE->Timers->TIMERS[timerNumber];

	// Create a temp array of field keys needed for accessing the I_STAT register.
	u8 timerKeys[] = { EEIntcRegister_STAT_t::Fields::TIM0, EEIntcRegister_STAT_t::Fields::TIM1, EEIntcRegister_STAT_t::Fields::TIM2, EEIntcRegister_STAT_t::Fields::TIM3 };

	// Check for Compare-Interrupt, and write to the INTC I_STAT.TIM0 bit.
	if (timer->mMODE->getFieldValue(EETimersTimerRegister_Mode_t::Fields::CMPE))
	{
		if (timer->mCOUNT->readWordU() >= timer->mCOMP->readWordU())
		{
			I_STAT->setFieldValue(timerKeys[timerNumber], 1);
		}
	}

	// Check for Overflow-Interrupt, and write to the INTC I_STAT.TIM0 bit.
	if (timer->mMODE->getFieldValue(EETimersTimerRegister_Mode_t::Fields::OVFE))
	{
		if (timer->mCOUNT->isOverflowed())
		{
			I_STAT->setFieldValue(timerKeys[timerNumber], 1);
		}
	}
}

void EETimers::checkTimerZRET(const u32& timerNumber) const
{
	auto& timerRegister = getVM()->getResources()->EE->Timers->TIMERS[timerNumber];

	// Check for ZRET condition.
	if (timerRegister->mMODE->getFieldValue(EETimersTimerRegister_Mode_t::Fields::ZRET))
	{
		// Check for Count >= Compare.
		if (timerRegister->mCOUNT->readWordU() >= timerRegister->mCOMP->readWordU())
		{
			// Set Count to 0.
			timerRegister->mCOUNT->reset();
		}
	}
}

bool EETimers::isTimerGateSpecialHBLNK(const u32& timerNumber) const
{
	if (getVM()->getResources()->EE->Timers->TIMERS[timerNumber]->mMODE->getFieldValue(EETimersTimerRegister_Mode_t::Fields::CLKS) == 3 &&
		getVM()->getResources()->EE->Timers->TIMERS[timerNumber]->mMODE->getFieldValue(EETimersTimerRegister_Mode_t::Fields::GATS) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void EETimers::checkTimerGateReset(const u32& timerNumber) const
{
	auto& timer = getVM()->getResources()->EE->Timers->TIMERS[timerNumber];
	auto& GS = getVM()->getResources()->GS;

	auto GATM = timer->mMODE->getFieldValue(EETimersTimerRegister_Mode_t::Fields::GATM);
	auto GATS = timer->mMODE->getFieldValue(EETimersTimerRegister_Mode_t::Fields::GATS);

	const u8 * gateSources[] = { &GS->SIGNAL_HBLNK, &GS->SIGNAL_VBLNK };
	const u8 * gateSourcesLast[] = { &GS->SIGNAL_HBLNK_LAST, &GS->SIGNAL_VBLNK_LAST };
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
			timer->mCOUNT->reset();
		break;
	}
	case 2:
	{
		// Resets and starts counting at the gate signal’s falling edge.
		if (!gateSource && gateSourceLast)
			timer->mCOUNT->reset();
		break;
	}
	case 3:
	{
		// Resets and starts counting at both edges of the gate signal.
		if (gateSource && !gateSourceLast 
			|| !gateSource && gateSourceLast)
		{
			timer->mCOUNT->reset();
		}
		break;
	}
	default:
	{
		throw std::runtime_error("Could not determine timer gate context (GATM). Please fix!");
	}
	}
}
