#pragma once

#include <cereal/cereal.hpp>

#include "Common/Types/Primitive.hpp"

/// An IOP DMAtag type, as explained by wisi and SP193's IOP DMA docs.
/// Although a DMAtag is 128-bit long, only the lower 2 x 32-bits are used (referred to as 64-bits in the map data below).
/// The other 64-bits are discarded upon reading the tag.
class IopDmatag
{
public:
    static constexpr Bitfield ADDR = Bitfield(0, 24);   // For tag0.
    static constexpr Bitfield IRQ = Bitfield(30, 1);    // For tag0.
    static constexpr Bitfield ERT = Bitfield(31, 1);    // For tag0.
    static constexpr Bitfield LENGTH = Bitfield(0, 24); // For tag1.

    /// Construct a blank tag.
    IopDmatag() :
        tag0(0),
        tag1(0)
    {
    }

    /// Construct the tag with the raw values.
    /// - tag0 is for bits 0-31.
    /// - tag1 is for bits 32-63.
    IopDmatag(const uword tag0, const uword tag1) :
        tag0(tag0),
        tag1(tag1)
    {
    }

    /// Field extraction functions.
    /// See Bitfields above for the actual definitions.
    uword addr() const
    {
        return static_cast<uptr>(ADDR.extract_from(tag0));
    }

    bool irq() const
    {
        return IRQ.extract_from(tag0) > 0;
    }

    bool ert() const
    {
        return ERT.extract_from(tag0) > 0;
    }

    usize length() const
    {
        return static_cast<usize>(LENGTH.extract_from(tag1));
    }

    /// DMAtag values.
    /// All functions above extract information from these.
    /// tag0 is for bits 0-31.
    /// tag1 is for bits 32-63.
    uword tag0;
    uword tag1;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(tag0),
            CEREAL_NVP(tag1)
        );
    }
};
