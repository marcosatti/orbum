#pragma once

#include <cereal/cereal.hpp>

#include "Common/Types/Primitive.hpp"

/// Real time clock of the CDVD.
class CdvdRtc
{
public:
    CdvdRtc();

    /// Clock values, used by the CDVD.
    /// These are internal registers only accessible though the RTC commands.
    ubyte second;
    ubyte minute;
    ubyte hour;
    ubyte day;
    ubyte month;
    ubyte year;

    /// Increments the RTC internal registers by the number of microseconds.
    void increment(const double time_us);

private:
    /// Number of microseconds that have passed, used by emulator.
    double microseconds;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(second),
            CEREAL_NVP(minute),
            CEREAL_NVP(hour),
            CEREAL_NVP(day),
            CEREAL_NVP(month),
            CEREAL_NVP(year),
            CEREAL_NVP(microseconds)
        );
    }
};