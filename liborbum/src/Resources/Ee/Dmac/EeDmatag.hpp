#pragma once

#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Primitive.hpp"

/// An EE DMAtag type, as explained on page 58 of the EE Users Manual.
/// Although a DMAtag is 128-bit long, only the lower 2 x 32-bits are used (referred to as 64-bits in the map data below).
struct EeDmatag
{
    static constexpr Bitfield QWC = Bitfield(0, 16);  // For tag0.
    static constexpr Bitfield TAG = Bitfield(16, 16); // For tag0. Needed by CHCR register (all upper 16 bits).
    static constexpr Bitfield PCE = Bitfield(26, 2);  // For tag0.
    static constexpr Bitfield ID = Bitfield(28, 3);   // For tag0.
    static constexpr Bitfield IRQ = Bitfield(31, 1);  // For tag0.
    static constexpr Bitfield ADDR = Bitfield(0, 31); // For tag1.
    static constexpr Bitfield SPR = Bitfield(31, 1);  // For tag1.

    /// Construct a blank DMAtag.
    EeDmatag() :
        tag0(0),
        tag1(0)
    {
    }

    /// Construct the tag with the raw values.
    /// - tag0 is for bits 0-31.
    /// - tag1 is for bits 32-63.
    EeDmatag(const uword tag0, const uword tag1) :
        tag0(tag0),
        tag1(tag1)
    {
    }

    /// Field extraction functions.
    /// See Bitfields above for the actual definitions.
    usize qwc() const
    {
        return static_cast<usize>(QWC.extract_from(tag0));
    }

    uhword tag() const
    {
        return static_cast<uhword>(TAG.extract_from(tag0));
    }

    ubyte pce() const
    {
        return static_cast<ubyte>(PCE.extract_from(tag0));
    }

    ubyte id() const
    {
        return static_cast<ubyte>(ID.extract_from(tag0));
    }

    bool irq() const
    {
        return IRQ.extract_from(tag0) > 0;
    }

    uptr addr() const
    {
        return static_cast<uptr>(ADDR.extract_from(tag1));
    }

    bool spr() const
    {
        return SPR.extract_from(tag1) > 0;
    }

    /// DMAtag values.
    /// All functions above extract information from these.
    /// tag0 is for bits 0-31.
    /// tag1 is for bits 32-63.
    uword tag0;
    uword tag1;
};