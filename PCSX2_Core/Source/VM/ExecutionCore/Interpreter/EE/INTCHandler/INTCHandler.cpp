#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/EE/INTCHandler/INTCHandler.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/INTC/INTC_t.h"
#include "Common/PS2Resources/EE/INTC/Types/INTC_Registers_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreExceptions/EECoreExceptions_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreExceptions/Types/EECoreException_t.h"

using ExType = EECoreException_t::ExType;

INTCHandler::INTCHandler(VMMain * vmMain) : 
	VMExecutionCoreComponent(vmMain),
	mClockSources{ ClockSource_t::BUSCLK }
{
}

const std::vector<ClockSource_t>& INTCHandler::getClockSources()
{
	return mClockSources;
}

s64 INTCHandler::executionStep(const ClockSource_t & clockSource)
{
	// If any of the I_STAT with logical AND I_MASK bits are 1, then an interrupt may be generated.
	const u32 I_STAT = getVM()->getResources()->EE->INTC->INTC_REGISTER_I_STAT->readWordU();
	if (I_STAT > 0)
	{
		const u32 I_MASK = getVM()->getResources()->EE->INTC->INTC_REGISTER_I_MASK->readWordU();
		if ((I_STAT & I_MASK) > 0)
		{
			// Generate an INT0 signal/interrupt exception (the EE Core exception handler will determine if it should be masked).
			auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
			IntExceptionInfo_t intInfo = { 0, 1, 0 };
			Exceptions->setException(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intInfo, nullptr));
		}
	}
	
	// INTC has completed 1 cycle.
	return 1;
}
