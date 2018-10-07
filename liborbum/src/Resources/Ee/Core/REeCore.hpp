#pragma once

#include <cereal/cereal.hpp>

#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Resources/Ee/Core/EeCoreCop0.hpp"
#include "Resources/Ee/Core/EeCoreFpu.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"
#include "Resources/Ee/Core/EeCoreTlb.hpp"

/// REeCore declares the R5900 structure, co-processors, etc, forming the EE Core.
/// For reference documentation, see the EE Core Users Manual (SCE).
/// VU0 is attached to the EE Core as COP2, declared separately from here.
class REeCore
{
public:
    REeCore();

    /// R5900 CPU.
    EeCoreR5900 r5900;

    /// COP0 coprocessor.
    EeCoreCop0 cop0;

    /// FPU (COP1) coprocessor.
    EeCoreFpu fpu;

    /// TLB state.
    EeCoreTlb tlb;

    /// Scratchpad memory.
    ArrayByteMemory scratchpad_memory;

public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            CEREAL_NVP(r5900),
            CEREAL_NVP(cop0),
            CEREAL_NVP(fpu),
            CEREAL_NVP(tlb),
            CEREAL_NVP(scratchpad_memory));
    }
};
