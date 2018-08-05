#pragma once

#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Resources/Iop/Timers/IopTimersUnitRegisters.hpp"

/// Represents IOP Timer unit.
/// Documentation taken from PCSX2 and No$PSX docs.
class IopTimersUnit_Base
{
public:
    IopTimersUnit_Base(const int unit_id);

    int unit_id;

    IopTimersUnitRegister_Count count;
    IopTimersUnitRegister_Mode mode;
    SizedWordRegister compare;

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(unit_id),
            CEREAL_NVP(count),
            CEREAL_NVP(mode),
            CEREAL_NVP(compare)
        );
    }
};