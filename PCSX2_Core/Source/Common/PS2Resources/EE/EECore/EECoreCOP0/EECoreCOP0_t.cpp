#include "stdafx.h"

#include "Common/PS2Resources/EE/EECore/EECoreCOP0/EECoreCOP0_t.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"

EECoreCOP0_t::EECoreCOP0_t(const PS2Resources_t* const PS2Resources) : 
	PS2ResourcesSubobject(PS2Resources),
	PRId(std::make_shared<COP0RegisterPRId_EECore_t>()),
	BadPAddr(std::make_shared<COP0RegisterBadPAddr_t>()),
	BPC(std::make_shared<COP0RegisterBPC_t>()),
	IAB(std::make_shared<COP0RegisterIAB_t>()),
	IABM(std::make_shared<COP0RegisterIABM_t>()),
	DAB(std::make_shared<COP0RegisterDAB_t>()),
	DABM(std::make_shared<COP0RegisterDABM_t>()),
	DVB(std::make_shared<COP0RegisterDVB_t>()),
	DVBM(std::make_shared<COP0RegisterDVBM_t>()),
	PCCR(std::make_shared<COP0RegisterPCCR_t>()),
	PCR0(std::make_shared<COP0RegisterPCR0_t>()),
	PCR1(std::make_shared<COP0RegisterPCR1_t>()),
	Registers{ Index, Random, EntryLo0, EntryLo1, Context, PageMask, Wired, nullptr, 
	           BadVAddr, Count, EntryHi, Compare, Status, Cause, EPC, PRId, 
	           Config, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, BadPAddr,
	           BPC, PCCR, nullptr, nullptr, TagLo, TagHi, ErrorEPC, nullptr },
	PCRRegisters{ PCR0, PCR1 }
{
}

bool EECoreCOP0_t::isCoprocessorUsable() const
{
	// First check for kernel mode - the COP0 is always available in this mode. If not, then check that CU[bit 0] == 1 (ie: >0) in the status register.
	if (isOperatingKernelMode())
		return true;
	else if ((getRootResources()->EE->EECore->COP0->Status->getFieldValue(COP0RegisterStatus_t::Fields::CU) & 0x1) > 0)
		return true;
	else
		return false;
}

void EECoreCOP0_t::initalise()
{
	for (auto& reg : Registers)
	{
		if (reg != nullptr)
			reg->initaliseAllFields();
	}
}
