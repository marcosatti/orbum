#pragma once

#include "Common/Types/Register/SizedDwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

/// Refer to EE User's Manual pg 183 for the registers.

// TODO: looks like a hybrid register... might end up splitting into two.
class IpuRegister_Cmd : public SizedDwordRegister
{
public:
    /// Register fields change depending on if reading or writing.
    /// BUSY field indicates the progress of the current decoding process.
    /// When set to 1, DATA field is meaningless.
    static constexpr Bitfield OPTION = Bitfield(0, 28);
    static constexpr Bitfield CODE = Bitfield(28, 4);
    static constexpr Bitfield DATA = Bitfield(0, 32);
    static constexpr Bitfield BUSY = Bitfield(63, 1);
};

class IpuRegister_Top : public SizedDwordRegister
{
public:
    /// BSTOP field is ineffective if BUSY is set to 1.
    static constexpr Bitfield BSTOP = Bitfield(0, 32);
    static constexpr Bitfield BUSY = Bitfield(63, 1);
};

class IpuRegister_Ctrl : public SizedWordRegister
{
public:
    static constexpr Bitfield IFC = Bitfield(0, 4);
    static constexpr Bitfield OFC = Bitfield(4, 4);
    static constexpr Bitfield CBP = Bitfield(8, 6);
    static constexpr Bitfield ECD = Bitfield(14, 1);
    static constexpr Bitfield SCD = Bitfield(15, 1);
    static constexpr Bitfield IDP = Bitfield(16, 2);
    static constexpr Bitfield AS = Bitfield(20, 1);
    static constexpr Bitfield IVF = Bitfield(21, 1);
    static constexpr Bitfield QST = Bitfield(22, 1);
    static constexpr Bitfield MP1 = Bitfield(23, 1);
    static constexpr Bitfield PCT = Bitfield(24, 3);
    static constexpr Bitfield RST = Bitfield(30, 1);
    static constexpr Bitfield BUSY = Bitfield(31, 1);
};

class IpuRegister_Bp : public SizedWordRegister
{
public:
    static constexpr Bitfield BP = Bitfield(0, 7);
    static constexpr Bitfield IFC = Bitfield(8, 4);
    static constexpr Bitfield FP = Bitfield(16, 2);
};
