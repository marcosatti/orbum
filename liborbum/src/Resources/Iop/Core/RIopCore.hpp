#pragma once

#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Resources/Iop/Core/IopCoreCop0.hpp"
#include "Resources/Iop/Core/IopCoreR3000.hpp"

class RIopCore
{
public:
    RIopCore();

    /// R3000 CPU.
    IopCoreR3000 r3000;

    /// COP0 coprocessor.
    IopCoreCop0 cop0;

    /// Scratchpad memory (1KB). Allocated at 0x1F800000.
    ArrayByteMemory scratchpad_memory;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(r3000),
            CEREAL_NVP(cop0),
            CEREAL_NVP(scratchpad_memory)
        );
    }
};
