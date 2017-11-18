#include "Resources/Ee/Core/EeCoreCop0.hpp"
#include "Resources/Ee/Core/EeCoreCop0Registers.hpp"

EeCoreCop0::EeCoreCop0() :
	registers{nullptr},
	pcr_registers{nullptr}
{
}

bool EeCoreCop0::is_usable()
{
	// First check for kernel mode - the COP0 is always available in this mode. If not, then check that CU[bit 0] == 1 (ie: >0) in the status register.
	if (operating_context() == MipsCoprocessor0::OperatingContext::Kernel)
		return true;
	else if ((status.extract_field(EeCoreCop0Register_Status::CU) & 0x1) > 0)
		return true;
	else
		return false;
}

MipsCoprocessor0::OperatingContext EeCoreCop0::operating_context()
{
	const uword KSU = status.extract_field(EeCoreCop0Register_Status::KSU);
	const uword ERL = status.extract_field(EeCoreCop0Register_Status::ERL);
	const uword EXL = status.extract_field(EeCoreCop0Register_Status::EXL);

	if (KSU == 2 && ERL == 0 && EXL == 0)
		return MipsCoprocessor0::OperatingContext::User;
	else if (KSU == 0 || ERL == 1 || EXL == 1)
		return MipsCoprocessor0::OperatingContext::Kernel;
	else if (KSU == 1 && ERL == 0 && EXL == 0)
		return MipsCoprocessor0::OperatingContext::Supervisor;
	else
		throw std::runtime_error("EE COP0 could not determine CPU operating context! Please debug.");
}
