#pragma once

#include "Resources/Iop/Intc/IopIntcRegisters.hpp"

/// IOP INTC resources.
struct RIopIntc
{
    IopIntcRegister_Ctrl ctrl;
    IopIntcRegister_Mask mask;
    IopIntcRegister_Stat stat;
};
