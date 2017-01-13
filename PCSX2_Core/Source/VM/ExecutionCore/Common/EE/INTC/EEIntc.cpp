#include "stdafx.h"

#include "Common/Types/Context_t.h"

#include "VM/ExecutionCore/Common/EE/INTC/EEIntc.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/INTC/EEIntc_t.h"
#include "PS2Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"

EEIntc::EEIntc(VMMain * vmMain) : 
	VMExecutionCoreComponent(vmMain)
{
}

s64 EEIntc::executionStep(const ClockSource_t & clockSource)
{
	auto& STAT = getResources()->EE->INTC->STAT;
	auto& MASK = getResources()->EE->INTC->MASK;
	auto& COP0 = getResources()->EE->EECore->COP0;

	// If any of the I_STAT with logical AND I_MASK bits are 1, then an interrupt may be generated.
	if (STAT->readWord(Context_t::RAW) & MASK->readWord(Context_t::RAW))
		COP0->Cause->setIRQLine(3);
	else
		COP0->Cause->clearIRQLine(3);
	
	// INTC has completed 1 cycle.
	return 1;
}
