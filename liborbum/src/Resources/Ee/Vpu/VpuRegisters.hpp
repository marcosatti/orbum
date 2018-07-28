#pragma once

#include "Common/Types/Register/SizedWordRegister.hpp"

/// The VPU STAT register.
/// See VU Users Manual page 203.
class VpuRegister_Stat : public SizedWordRegister
{
public:
    static constexpr Bitfield VBS0 = Bitfield(0, 1);
    static constexpr Bitfield VDS0 = Bitfield(1, 1);
    static constexpr Bitfield VTS0 = Bitfield(2, 1);
    static constexpr Bitfield VFS0 = Bitfield(3, 1);
    static constexpr Bitfield DIV0 = Bitfield(5, 1);
    static constexpr Bitfield IBS0 = Bitfield(7, 1);
    static constexpr Bitfield VBS1 = Bitfield(8, 1);
    static constexpr Bitfield VDS1 = Bitfield(9, 1);
    static constexpr Bitfield VTS1 = Bitfield(10, 1);
    static constexpr Bitfield VFS1 = Bitfield(11, 1);
    static constexpr Bitfield VGW1 = Bitfield(12, 1);
    static constexpr Bitfield DIV1 = Bitfield(13, 1);
    static constexpr Bitfield EFU1 = Bitfield(14, 1);
};