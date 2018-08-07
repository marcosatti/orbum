#pragma once

#include "Common/Constants.hpp"
#include "Resources/Iop/Timers/IopTimersUnits.hpp"

/// IOP timers.
class RIopTimers
{
public:
    RIopTimers();

    /// Contains 16-bit (0 -> 2) and 32-bit (3 -> 5) timers.
    IopTimersUnit_Base unit_0;
    IopTimersUnit_Base unit_1;
    IopTimersUnit_Base unit_2;
    IopTimersUnit_Base unit_3;
    IopTimersUnit_Base unit_4;
    IopTimersUnit_Base unit_5;

    /// Timer abstractions.
    IopTimersUnit_Base* units[Constants::IOP::Timers::NUMBER_TIMERS];

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(unit_0),
            CEREAL_NVP(unit_1),
            CEREAL_NVP(unit_2),
            CEREAL_NVP(unit_3),
            CEREAL_NVP(unit_4),
            CEREAL_NVP(unit_5)
        );
    }
};