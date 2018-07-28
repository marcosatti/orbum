#include "Resources/Ee/Core/EeCoreFpu.hpp"

#include "Resources/Ee/Core/EeCoreCop0Registers.hpp"

EeCoreFpu::EeCoreFpu() :
    fcr{nullptr},
    cop0(nullptr)
{
}

bool EeCoreFpu::is_usable()
{
    if ((cop0->status.extract_field(EeCoreCop0Register_Status::CU) & 0x2) > 0)
        return true;
    else
        return false;
}
