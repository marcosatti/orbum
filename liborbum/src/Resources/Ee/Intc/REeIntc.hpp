#pragma once

#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Resources/Ee/Intc/EeIntcRegisters.hpp"

class REeIntc
{
public:
    REeIntc();

    /// EE INTC memory mapped registers. See page 24 of EE Users Manual.
    EeIntcRegister_Mask mask;
    EeIntcRegister_Stat stat;
    ArrayByteMemory memory_f020;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(mask),
            CEREAL_NVP(stat),
            CEREAL_NVP(memory_f020)
        );
    }
};
