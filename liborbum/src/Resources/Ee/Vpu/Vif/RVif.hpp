#pragma once

#include <cereal/cereal.hpp>

#include "Common/Constants.hpp"
#include "Resources/Ee/Vpu/Vif/VifUnits.hpp"

/// RVif declares the collective VIF structure.
class RVif
{
public:
    RVif();

    /// VIF structure.
    VifUnit_Base unit_0;
    VifUnit_Base unit_1;
    VifUnit_Base* units[Constants::EE::VPU::VIF::NUMBER_VIF_CORES];

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            CEREAL_NVP(unit_0),
            CEREAL_NVP(unit_1));
    }
};