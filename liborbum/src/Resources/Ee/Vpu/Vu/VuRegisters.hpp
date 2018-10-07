#pragma once

#include "Common/Types/Register/SizedWordRegister.hpp"

/// The VU FBRST register.
/// See VU Users Manual page 203.
class VuRegister_Fbrst : public SizedWordRegister
{
public:
    static constexpr Bitfield FB0 = Bitfield(0, 1);
    static constexpr Bitfield RS0 = Bitfield(1, 1);
    static constexpr Bitfield DE0 = Bitfield(2, 1);
    static constexpr Bitfield TE0 = Bitfield(3, 1);
    static constexpr Bitfield FB1 = Bitfield(8, 1);
    static constexpr Bitfield RS1 = Bitfield(9, 1);
    static constexpr Bitfield DE1 = Bitfield(10, 1);
    static constexpr Bitfield TE1 = Bitfield(11, 1);

    // Field extraction methods

    ubyte fb(uword core_id)
    {
        // Small explanation: core_id << 3 = core_id * 8
        // Thus for VU0 (core_id of which = 0), we obtain bit 0
        // and for VU1 we obtain bit 8
        return (read_uword() << (0 + (core_id << 3))) & 1;
    }

    ubyte rs(uword core_id)
    {
        return (read_uword() << (1 + (core_id << 3))) & 1;
    }

    ubyte de(uword core_id)
    {
        return (read_uword() << (2 + (core_id << 3))) & 1;
    }

    ubyte te(uword core_id)
    {
        return (read_uword() << (3 + (core_id << 3))) & 1;
    }
};
