#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/Primitive.hpp"

/// Contains static channel properties for the Spu2 Cores.
/// See Spu2 Overview manual.
struct Spu2CoreConstants
{
    struct Spu2CoreInfo
    {
        // The base TSA start hword addresses come from the Spu2 Overview manual page 28.
        uptr base_tsa_left;  // For the left audio channel in stereo mode (TODO: also used for mono?).
        uptr base_tsa_right; // For the right audio channel in stereo mode.
    };

    static constexpr Spu2CoreInfo SPU2_STATIC_INFO[Constants::SPU2::NUMBER_CORES] =
        {
            {0x2000, 0x2200},
            {0x2400, 0x2600},
    };
};
