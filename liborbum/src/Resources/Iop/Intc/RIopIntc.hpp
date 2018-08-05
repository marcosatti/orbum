#pragma once

#include "Resources/Iop/Intc/IopIntcRegisters.hpp"

/// IOP INTC resources.
struct RIopIntc
{
    IopIntcRegister_Ctrl ctrl;
    IopIntcRegister_Mask mask;
    IopIntcRegister_Stat stat;

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(ctrl),
            CEREAL_NVP(mask),
            CEREAL_NVP(stat)
        );
    }
};
