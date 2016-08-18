#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

void InterpreterEECore::SYNC_STYPE()
{
	// TODO: not sure I need to implement anything, since there is no hardware to be synced.
}

void InterpreterEECore::PREF()
{
	// TODO: Probably dont need to implement, as its just a prefetch which is meaningless in an emulator.
}

void InterpreterEECore::DI()
{
	// Disable Interrupts. No Exceptions.
	auto& statusReg = getVM()->getResources()->EE->EECore->COP0->Status;

	if ((statusReg->getFieldValue(RegisterStatus_t::Fields::EDI) == 1) ||
		(statusReg->getFieldValue(RegisterStatus_t::Fields::EXL) == 1) ||
		(statusReg->getFieldValue(RegisterStatus_t::Fields::ERL) == 1) || 
		(statusReg->getFieldValue(RegisterStatus_t::Fields::KSU) == 0))
	{
		statusReg->setFieldValue(RegisterStatus_t::Fields::EIE, 0);
	}
}

void InterpreterEECore::EI()
{
	// Enable Interrupts. No Exceptions.
	auto& statusReg = getVM()->getResources()->EE->EECore->COP0->Status;

	if ((statusReg->getFieldValue(RegisterStatus_t::Fields::EDI) == 1) ||
		(statusReg->getFieldValue(RegisterStatus_t::Fields::EXL) == 1) ||
		(statusReg->getFieldValue(RegisterStatus_t::Fields::ERL) == 1) ||
		(statusReg->getFieldValue(RegisterStatus_t::Fields::KSU) == 0))
	{
		statusReg->setFieldValue(RegisterStatus_t::Fields::EIE, 1);
	}
}
