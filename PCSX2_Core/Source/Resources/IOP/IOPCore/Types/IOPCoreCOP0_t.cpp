#include "stdafx.h"

#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"

IOPCoreCOP0_t::IOPCoreCOP0_t() :
	INDX(std::make_shared<Register32_t>()),
	RAND(std::make_shared<Register32_t>()),
	TLBL(std::make_shared<Register32_t>()),
	BPC(std::make_shared<Register32_t>()),
	Context(std::make_shared<IOPCoreCOP0Register_System_t>()),
	BDA(std::make_shared<Register32_t>()),
	PIDMASK(std::make_shared<Register32_t>()),
	DCIC(std::make_shared<Register32_t>()),
	BADV(std::make_shared<Register32_t>()),
	BDAM(std::make_shared<Register32_t>()),
	TLBH(std::make_shared<Register32_t>()),
	BPCM(std::make_shared<Register32_t>()),
	Status(std::make_shared<IOPCoreCOP0Register_Status_t>()),
	Cause(std::make_shared<IOPCoreCOP0Register_Cause_t>()),
	EPC(std::make_shared<Register32_t>()),
	PRId(std::make_shared<IOPCoreCOP0Register_PRId_t>()),
	ERREG(std::make_shared<Register32_t>()),
	Registers{ INDX, RAND, TLBL, BPC, Context, BDA, PIDMASK, DCIC, 
			   BADV, BDAM, TLBH, BPCM, Status, Cause, EPC, PRId, 
			   ERREG, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		       nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr }
{
}

bool IOPCoreCOP0_t::isCoprocessorUsable(const System_t context) const
{
	// First check for kernel mode - the COP0 is always available in this mode. If not, then check that CU[bit 0] == 1 (ie: >0) in the status register.
	if (getCPUOperatingContext(context) == MIPSCPUOperatingContext_t::Kernel)
		return true;
	else if ((Status->getFieldValue(context, IOPCoreCOP0Register_Status_t::Fields::CU) & 0x1) > 0)
		return true;
	else
		return false;
}

void IOPCoreCOP0_t::initalise()
{	
	for (auto& reg : Registers)
		if (reg != nullptr) reg->initalise();
}

MIPSCPUOperatingContext_t IOPCoreCOP0_t::getCPUOperatingContext(const System_t context) const
{
	const u32 KUc = Status->getFieldValue(context, IOPCoreCOP0Register_Status_t::Fields::KUc);

	if (KUc == 1)
		return MIPSCPUOperatingContext_t::User;
	else if (KUc == 0)
		return MIPSCPUOperatingContext_t::Kernel;
	else
		throw std::runtime_error("IOP COP0 could not determine CPU operating context! Please debug.");
}