#pragma once

#include <cereal/cereal.hpp>

#include "Resources/Ee/Vpu/Vif/RVif.hpp"
#include "Resources/Ee/Vpu/VpuRegisters.hpp"
#include "Resources/Ee/Vpu/Vu/RVu.hpp"

/// RVpu declares the collective VPU structure.
class RVpu
{
public:
    /// Shared registers.
    VpuRegister_Stat stat;

    /// VIF structure.
    RVif vif;

    /// VU structure.
    RVu vu;

public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            CEREAL_NVP(stat),
            CEREAL_NVP(vif),
            CEREAL_NVP(vu));
    }
};