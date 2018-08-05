#pragma once

#include "Common/Constants.hpp"
#include "Resources/Ee/Timers/EeTimersUnits.hpp"

/// The EE Timers resources.
/// Defines the 4 timers within the EE, as listed on page 33 onwards of the EE Users Manual.
struct REeTimers
{
    REeTimers();

    EeTimersUnit_Hold unit_0;
    EeTimersUnit_Hold unit_1;
    EeTimersUnit_Base unit_2;
    EeTimersUnit_Base unit_3;

    /// Timer abstractions.
    EeTimersUnit units[Constants::EE::Timers::NUMBER_TIMERS];

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(unit_0),
            CEREAL_NVP(unit_1),
            CEREAL_NVP(unit_2),
            CEREAL_NVP(unit_3)
        );
    }
};
