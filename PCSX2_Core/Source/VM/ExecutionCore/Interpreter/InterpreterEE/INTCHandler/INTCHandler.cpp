#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEE/INTCHandler/INTCHandler.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/Types/XORStorageObject/XORStorageObject_t.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Exceptions_t.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Types/EECoreException_t.h"

using ExType = EECoreException_t::ExType;

INTCHandler::INTCHandler(const VMMain* const vmMain) : 
	VMExecutionCoreComponent(vmMain)
{
}

void INTCHandler::checkInterrupt() const
{
	const u32 I_STAT = getVM()->getResources()->EE->EE_REGISTER_I_STAT->readWordU(0);
	if (I_STAT > 0)
	{
		const u32 I_MASK = getVM()->getResources()->EE->EE_REGISTER_I_MASK->readWordU(0);
		if ((I_STAT & I_MASK) > 0)
		{
			// Generate an INT0 signal/interrupt exception.
			auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
			IntExceptionInfo_t intInfo = { 0, 1, 0 };
			ExceptionQueue->push(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intInfo, nullptr));
		}
	}
}
