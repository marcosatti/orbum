#include "stdafx.h"

#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "Common/Types/MIPSCoprocessor/COP0Registers_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"

IOPCoreCOP0_t::IOPCoreCOP0_t(const PS2Resources_t* const PS2Resources) : 
	PS2ResourcesSubobject(PS2Resources),
	INDX(std::make_shared<COP0RegisterReserved_t>()),
	RAND(std::make_shared<COP0RegisterReserved_t>()),
	TLBL(std::make_shared<COP0RegisterReserved_t>()),
	BPC(std::make_shared<COP0RegisterReserved_t>()),
	Context(std::make_shared<IOPCoreCOP0Register_Context_t>()),
	BDA(std::make_shared<COP0RegisterReserved_t>()),
	PIDMASK(std::make_shared<COP0RegisterReserved_t>()),
	DCIC(std::make_shared<COP0RegisterReserved_t>()),
	BADV(std::make_shared<COP0RegisterReserved_t>()),
	BDAM(std::make_shared<COP0RegisterReserved_t>()),
	TLBH(std::make_shared<COP0RegisterReserved_t>()),
	BPCM(std::make_shared<COP0RegisterReserved_t>()),
	Status(std::make_shared<IOPCoreCOP0Register_Status_t>()),
	Cause(std::make_shared<IOPCoreCOP0Register_Cause_t>()),
	EPC(std::make_shared<COP0RegisterEPC_t>()),
	PRId(std::make_shared<IOPCoreCOP0Register_PRId_t>()),
	ERREG(std::make_shared<COP0RegisterReserved_t>()),
	Registers{ INDX, RAND, TLBL, BPC, Context, BDA, PIDMASK, DCIC, 
			   BADV, BDAM, TLBH, BPCM, Status, Cause, EPC, PRId, 
			   ERREG, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		       nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr }
{
}

bool IOPCoreCOP0_t::isCoprocessorUsable() const
{
	// First check for kernel mode - the COP0 is always available in this mode. If not, then check that CU[bit 0] == 1 (ie: >0) in the status register.
	if (isOperatingKernelMode())
		return true;
	else if ((Status->getFieldValue(IOPCoreCOP0Register_Status_t::Fields::CU) & 0x1) > 0)
		return true;
	else
		return false;
}

void IOPCoreCOP0_t::initalise()
{
	for (auto& reg : Registers)
	{
		if (reg != nullptr)
			reg->initaliseAllFields();
	}
}

bool IOPCoreCOP0_t::isOperatingUserMode() const
{
	const u32& KUc = Status->getFieldValue(IOPCoreCOP0Register_Status_t::Fields::KUc);

	if (KUc == 1)
		return true;
	else
		return false;
}

bool IOPCoreCOP0_t::isOperatingSupervisorMode() const
{
	throw new std::runtime_error("Call to check if IOP Core running in supervisor mode - but it doesn't support this mode.");
}

bool IOPCoreCOP0_t::isOperatingKernelMode() const
{
	const u32& KUc = Status->getFieldValue(IOPCoreCOP0Register_Status_t::Fields::KUc);

	if (KUc == 0)
		return true;
	else
		return false;
}
