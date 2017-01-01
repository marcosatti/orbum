#include "stdafx.h"

#include "VM/ExecutionCore/Common/IOP/INTC/IOPIntc.h"
#include "VM/VMMain.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/INTC/IOPIntc_t.h"
#include "PS2Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreExceptions_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreException_t.h"

using ExType = IOPCoreException_t::ExType;

IOPIntc::IOPIntc(VMMain * vmMain) : 
	VMExecutionCoreComponent(vmMain)
{
}

s64 IOPIntc::executionStep(const ClockSource_t & clockSource)
{
	// First check the master CTRL register.
	const u32 I_CTRL = getResources()->IOP->INTC->CTRL->readWord();
	if (I_CTRL > 0)
	{
		// If any of the I_STAT with logical AND I_MASK bits are 1, then an interrupt may be generated.
		const u32 I_STAT = getResources()->IOP->INTC->STAT->readWord();
		if (I_STAT > 0)
		{
			const u32 I_MASK = getResources()->IOP->INTC->MASK->readWord();
			if ((I_STAT & I_MASK) > 0)
			{
				// Generate an INT0 signal/interrupt exception (the IOP Core exception handler will determine if it should be masked).
				auto& Exceptions = getResources()->IOP->IOPCore->Exceptions;
				IntExceptionInfo_t intInfo = { 1 };
				Exceptions->setException(IOPCoreException_t(ExType::EX_INTERRUPT, nullptr, &intInfo, nullptr));
			}
		}
	}
	
	// INTC has completed 1 cycle.
	return 1;
}
