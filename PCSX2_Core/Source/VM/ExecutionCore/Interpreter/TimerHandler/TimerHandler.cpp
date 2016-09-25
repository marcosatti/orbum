#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/TimerHandler/TimerHandler.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/GS/GS_t.h"
#include "Common/PS2Resources/EE/Types/EE_Registers_t.h"
#include "Common/PS2Constants/PS2Constants.h"

TimerHandler::TimerHandler(VMMain * vmMain) :
	VMExecutionCoreComponent(vmMain)
{
}

TimerHandler::~TimerHandler()
{
}

void TimerHandler::executionStep_BUSCLK() const
{
	updateTimers(ClockSource_t::BUSCLK);
}

void TimerHandler::executionStep_BUSCLK16() const
{
	updateTimers(ClockSource_t::BUSCLK16);
}

void TimerHandler::executionStep_BUSCLK256() const
{
	updateTimers(ClockSource_t::BUSCLK256);
}

void TimerHandler::executionStep_HBLNK() const
{
	updateTimers(ClockSource_t::HBLNK);
}

void TimerHandler::updateTimers(const ClockSource_t & clockSource) const
{
	auto& EE = getVM()->getResources()->EE;
	auto& GS = getVM()->getResources()->GS;
	const u8 * gateSources[] = { &GS->SIGNAL_HBLNK, &GS->SIGNAL_VBLNK };

	// Update the timers which are set to count based on the type of event recieved.
	for (auto i = 0; i < PS2Constants::EE::NUMBER_TIMERS; i++)
	{
		// Do not count if not enabled.
		if (!EE->TimerRegisters[i].Mode->getFieldValue(EERegisterTimerMode_t::Fields::CUE))
			continue;

		// Check if the timer mode is equal to the clock source.
		if (isTimerCLKSEqual(i, clockSource))
		{
			// Next check for the gate function. Also check for a special gate condition, for when CLKS == H_BLNK and GATS == HBLNK, 
			//  in which case count normally.
			if (EE->TimerRegisters[i].Mode->getFieldValue(EERegisterTimerMode_t::Fields::GATE) && !isTimerGateSpecialHBLNK(i))
			{
				// Check if the timer needs to be reset.
				checkTimerGateReset(i);

				// If the timer is using GATM = 0, need to check if the signal is low first.
				if (EE->TimerRegisters[i].Mode->getFieldValue(EERegisterTimerMode_t::Fields::GATM) == 0)
				{
					if (!gateSources[EE->TimerRegisters[i].Mode->getFieldValue(EERegisterTimerMode_t::Fields::GATS)])
						EE->TimerRegisters[i].Count->increment(1);
				}
				else
				{
					EE->TimerRegisters[i].Count->increment(1);	
				}
			}
			else
			{
				// Count normally without gate.
				EE->TimerRegisters[i].Count->increment(1);
			}

			// Check for interrupt conditions on the timer.
			checkTimerInterrupt(i);

			// Check for zero return (ZRET) conditions (perform after interrupt check, otherwise interrupt may be missed).
			checkTimerZRET(i);
		}
	}
}

bool TimerHandler::isTimerCLKSEqual(const u32 & timerNumber, const ClockSource_t & clockSource) const
{
	auto& timerRegister = getVM()->getResources()->EE->TimerRegisters[timerNumber];
	auto CLKS = static_cast<ClockSource_t>(timerRegister.Mode->getFieldValue(EERegisterTimerMode_t::Fields::CLKS));

	if (CLKS == clockSource)
		return true;
	else
		return false;
}

void TimerHandler::checkTimerInterrupt(const u32& timerNumber) const
{
	auto& I_STAT = getVM()->getResources()->EE->EE_REGISTER_I_STAT;
	auto& timerRegister = getVM()->getResources()->EE->TimerRegisters[timerNumber];

	// Create a temp array of field keys needed for accessing the I_STAT register.
	char * timerKeys[] = { EERegisterINTCIStat_t::Fields::TIM0, EERegisterINTCIStat_t::Fields::TIM1, EERegisterINTCIStat_t::Fields::TIM2, EERegisterINTCIStat_t::Fields::TIM3 };

	// Check for Compare-Interrupt, and write to the INTC I_STAT.TIM0 bit.
	if (timerRegister.Mode->getFieldValue(EERegisterTimerMode_t::Fields::CMPE))
	{
		if (timerRegister.Count->readWordU(0) >= timerRegister.Compare->readWordU(0))
		{
			I_STAT->setFieldValue(timerKeys[timerNumber], 1);
		}
	}

	// Check for Overflow-Interrupt, and write to the INTC I_STAT.TIM0 bit.
	if (timerRegister.Mode->getFieldValue(EERegisterTimerMode_t::Fields::OVFE))
	{
		if (timerRegister.Count->readWordU(0) > Constants::VALUE_U16_MAX)
		{
			I_STAT->setFieldValue(timerKeys[timerNumber], 1);
		}
	}
}

void TimerHandler::checkTimerZRET(const u32& timerNumber) const
{
	auto& timerRegister = getVM()->getResources()->EE->TimerRegisters[timerNumber];

	// Check for ZRET condition.
	if (timerRegister.Mode->getFieldValue(EERegisterTimerMode_t::Fields::ZRET))
	{
		// Check for Count >= Compare.
		if (timerRegister.Count->readWordU(0) >= timerRegister.Compare->readWordU(0))
		{
			// Set Count to 0.
			timerRegister.Count->reset();
		}
	}
}

bool TimerHandler::isTimerGateSpecialHBLNK(const u32& timerNumber) const
{
	if (getVM()->getResources()->EE->TimerRegisters[timerNumber].Mode->getFieldValue(EERegisterTimerMode_t::Fields::CLKS) == 3 &&
		getVM()->getResources()->EE->TimerRegisters[timerNumber].Mode->getFieldValue(EERegisterTimerMode_t::Fields::GATS) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TimerHandler::checkTimerGateReset(const u32& timerNumber) const
{
	auto& timer = getVM()->getResources()->EE->TimerRegisters[timerNumber];
	auto GATM = timer.Mode->getFieldValue(EERegisterTimerMode_t::Fields::GATM);
	auto& GS = getVM()->getResources()->GS;

	const u8 * gateSources[] = { &GS->SIGNAL_HBLNK, &GS->SIGNAL_VBLNK };
	const u8 * gateSourcesLast[] = { &GS->SIGNAL_HBLNK_LAST, &GS->SIGNAL_VBLNK_LAST };
	auto GATS = getVM()->getResources()->EE->TimerRegisters[timerNumber].Mode->getFieldValue(EERegisterTimerMode_t::Fields::GATS);
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
			timer.Count->reset();
		break;
	}
	case 2:
	{
		// Resets and starts counting at the gate signal’s falling edge.
		if (!gateSource && gateSourceLast)
			timer.Count->reset();
		break;
	}
	case 3:
	{
		// Resets and starts counting at both edges of the gate signal.
		if (gateSource && !gateSourceLast 
			|| !gateSource && gateSourceLast)
		{
			timer.Count->reset();
		}
		break;
	}
	default:
	{
		throw std::runtime_error("Could not determine timer gate context (GATM). Please fix!");
	}
	}
}
