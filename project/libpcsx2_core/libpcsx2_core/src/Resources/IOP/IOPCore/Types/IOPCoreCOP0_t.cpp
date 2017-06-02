#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"

IOPCoreCOP0_t::IOPCoreCOP0_t() :
	INDX(std::make_shared<Register32_t>("IOPCore COP0 INDX", false, false)),
	RAND(std::make_shared<Register32_t>("IOPCore COP0 RAND", false, false)),
	TLBL(std::make_shared<Register32_t>("IOPCore COP0 TLBL", false, false)),
	BPC(std::make_shared<Register32_t>("IOPCore COP0 BPC", false, false)),
	Context(std::make_shared<IOPCoreCOP0Register_Context_t>("IOPCore COP0 Context", false, false)),
	BDA(std::make_shared<Register32_t>("IOPCore COP0 BDA", false, false)),
	PIDMASK(std::make_shared<Register32_t>("IOPCore COP0 PIDMASK", false, false)),
	DCIC(std::make_shared<Register32_t>("IOPCore COP0 DCIC", false, false)),
	BADV(std::make_shared<Register32_t>("IOPCore COP0 BADV", false, false)),
	BDAM(std::make_shared<Register32_t>("IOPCore COP0 BDAM", false, false)),
	TLBH(std::make_shared<Register32_t>("IOPCore COP0 TLBH", false, false)),
	BPCM(std::make_shared<Register32_t>("IOPCore COP0 BPCM", false, false)),
	Status(std::make_shared<IOPCoreCOP0Register_Status_t>("IOPCore COP0 Status", false, false)),
	Cause(std::make_shared<IOPCoreCOP0Register_Cause_t>("IOPCore COP0 Cause", false, false)),
	EPC(std::make_shared<Register32_t>("IOPCore COP0 EPC", false, false)),
	PRId(std::make_shared<IOPCoreCOP0Register_PRId_t>("IOPCore COP0 PRId", false, false)),
	ERREG(std::make_shared<Register32_t>("IOPCore COP0 ERREG", false, false)),
	Registers{ INDX, RAND, TLBL, BPC, Context, BDA, PIDMASK, DCIC, 
			   BADV, BDAM, TLBH, BPCM, Status, Cause, EPC, PRId, 
			   ERREG, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		       nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr }
{
}

bool IOPCoreCOP0_t::isCoprocessorUsable(const Context_t context) const
{
	// First check for kernel mode - the COP0 is always available in this mode. If not, then check that CU[bit 0] == 1 (ie: >0) in the status register.
	if (getCPUOperatingContext(context) == MIPSCPUOperatingContext_t::Kernel)
		return true;
	else if ((Status->getFieldValue(context, IOPCoreCOP0Register_Status_t::Fields::CU) & 0x1) > 0)
		return true;
	else
		return false;
}

void IOPCoreCOP0_t::initialise()
{	
	for (auto& reg : Registers)
		if (reg != nullptr) reg->initialise();
}

MIPSCPUOperatingContext_t IOPCoreCOP0_t::getCPUOperatingContext(const Context_t context) const
{
	const u32 KUc = Status->getFieldValue(context, IOPCoreCOP0Register_Status_t::Fields::KUc);

	if (KUc == 1)
		return MIPSCPUOperatingContext_t::User;
	else if (KUc == 0)
		return MIPSCPUOperatingContext_t::Kernel;
	else
		throw std::runtime_error("IOP COP0 could not determine CPU operating context! Please debug.");
}