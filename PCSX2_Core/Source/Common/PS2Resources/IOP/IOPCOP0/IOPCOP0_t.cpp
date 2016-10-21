#include "stdafx.h"

#include "Common/PS2Resources/IOP/IOPCOP0/IOPCOP0_t.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"

IOPCOP0_t::IOPCOP0_t(const PS2Resources_t* const PS2Resources) : 
	PS2ResourcesSubobject(PS2Resources),
	PRId(std::make_shared<COP0RegisterPRId_IOP_t>()),
	Reserved7(std::make_shared<COP0RegisterReserved_t>()),
	Registers{ Index, Random, EntryLo0, EntryLo1, Context, PageMask, Wired, Reserved7, 
	           BadVAddr, Count, EntryHi, Compare, Status, Cause, EPC, PRId, 
	           Config, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
			   nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr }
{
}

bool IOPCOP0_t::isCoprocessorUsable() const
{
	// First check for kernel mode - the COP0 is always available in this mode. If not, then check that CU[bit 0] == 1 (ie: >0) in the status register.
	if (isOperatingKernelMode())
		return true;
	else if ((getRootResources()->IOP->COP0->Status->getFieldValue(COP0RegisterStatus_t::Fields::CU) & 0x1) > 0)
		return true;
	else
		return false;
}

void IOPCOP0_t::initalise()
{
	for (auto& reg : Registers)
	{
		if (reg != nullptr)
			reg->initaliseAllFields();
	}
}
