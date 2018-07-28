#include "Resources/Iop/Core/IopCoreCop0.hpp"

#include "Resources/Iop/Core/IopCoreCop0Registers.hpp"

IopCoreCop0::IopCoreCop0() :
    registers{nullptr}
{
}

bool IopCoreCop0::is_usable()
{
    // Check for kernel mode - the COP0 is always available in this mode,
    // or check that CU[bit 0] == 1 (ie: >0) in the status register (always valid no matter context).
    if ((status.extract_field(IopCoreCop0Register_Status::CU) & 0x1) > 0)
        return true;
    else if (operating_context() == MipsCoprocessor0::OperatingContext::Kernel)
        return true;
    else
        return false;
}

MipsCoprocessor0::OperatingContext IopCoreCop0::operating_context()
{
    return status.operating_context;
}