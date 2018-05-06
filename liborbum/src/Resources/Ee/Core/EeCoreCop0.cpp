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
    return status.operating_context;
}
