#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/TimerHandler/TimerHandler.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/COP0_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Exceptions_t.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Types/EECoreException_t.h"

using ExType = EECoreException_t::ExType;

TimerHandler::TimerHandler(const VMMain *const vmMain)
	: VMExecutionCoreComponent(vmMain)
{
}

void TimerHandler::incrementCountTimer(const EECoreInstructionInfo_t *const EECoreInstructionInfo) const
{
	auto& EECore = getVM()->getResources()->EE->EECore;
	EECore->COP0->Count->increment(EECoreInstructionInfo->mCycles);
}

void TimerHandler::checkTimerEvents() const
{
	auto& EECore = getVM()->getResources()->EE->EECore;
	
	// Check the COP0.Count register against the COP0.Compare register. See EE Core Users Manual page 72 for details.
	// The docs specify that an interrupt is raised when the two values are equal, but this is impossible to get correct (due to how emulation works), 
	//  so it is based on greater than or equal.
	// TODO: check for errors.
	if (EECore->COP0->Count->readWordU() >= EECore->COP0->Compare->readWordU())
	{
		// Set the IP7 field of the COP0.Cause register.
		EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::IP7, 1);

		// Queue an interrupt exception if the Status.IM7 and IE bits are set (Cause.IP is set above). 
		// See EE Core Users Manual page 72 and 74 for how the interrupt is raised.
		if (EECore->COP0->Status->getFieldValue(RegisterStatus_t::Fields::IE)
			&& EECore->COP0->Status->getFieldValue(RegisterStatus_t::Fields::IM7))
		{
			IntExceptionInfo_t intEx = { 0, 0, 1 };
			EECore->Exceptions->ExceptionQueue->push(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intEx, nullptr));
		}
	}
}
