#pragma once

#include "Common/Types/FpuFlags.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Resources/Ee/Vpu/Vu/VuVectorField.hpp"

/// The VU unit Status flags register.
/// See VU Users Manual page 39.
class VuUnitRegister_Status : public SizedWordRegister
{
public:
    static constexpr Bitfield Z = Bitfield(0, 1);
    static constexpr Bitfield S = Bitfield(1, 1);
    static constexpr Bitfield U = Bitfield(2, 1);
    static constexpr Bitfield O = Bitfield(3, 1);
    static constexpr Bitfield I = Bitfield(4, 1);
    static constexpr Bitfield D = Bitfield(5, 1);
    static constexpr Bitfield ZS = Bitfield(6, 1);
    static constexpr Bitfield SS = Bitfield(7, 1);
    static constexpr Bitfield US = Bitfield(8, 1);
    static constexpr Bitfield OS = Bitfield(9, 1);
    static constexpr Bitfield IS = Bitfield(10, 1);
    static constexpr Bitfield DS = Bitfield(11, 1);

    /// Functions to set flags and update corresponding sticky flag.
    /// The flags act as a "total" state - if any of the X, Y, Z, W
    /// sub-flags from FMAC operations are set, then these are set
    /// as well... The manual explains it better. See VU Users Manual page 40.
    void set_z_flag_sticky(const uword value);
    void set_s_flag_sticky(const uword value);
    void set_u_flag_sticky(const uword value);
    void set_o_flag_sticky(const uword value);
    void set_i_flag_sticky(const uword value);
    void set_d_flag_sticky(const uword value);
};

/// The VU unit MAC flags register.
/// See VU Users Manual page 39.
class VuUnitRegister_Mac : public SizedWordRegister
{
public:
    static constexpr Bitfield ZW = Bitfield(0, 1);
    static constexpr Bitfield ZZ = Bitfield(1, 1);
    static constexpr Bitfield ZY = Bitfield(2, 1);
    static constexpr Bitfield ZX = Bitfield(3, 1);
    static constexpr Bitfield SW = Bitfield(4, 1);
    static constexpr Bitfield SZ = Bitfield(5, 1);
    static constexpr Bitfield SY = Bitfield(6, 1);
    static constexpr Bitfield SX = Bitfield(7, 1);
    static constexpr Bitfield UW = Bitfield(8, 1);
    static constexpr Bitfield UZ = Bitfield(9, 1);
    static constexpr Bitfield UY = Bitfield(10, 1);
    static constexpr Bitfield UX = Bitfield(11, 1);
    static constexpr Bitfield OW = Bitfield(12, 1);
    static constexpr Bitfield OZ = Bitfield(13, 1);
    static constexpr Bitfield OY = Bitfield(14, 1);
    static constexpr Bitfield OX = Bitfield(15, 1);

    static constexpr Bitfield X_FLAGS[] = {ZX, SX, UX, OX};
    static constexpr Bitfield Y_FLAGS[] = {ZY, SY, UY, OY};
    static constexpr Bitfield Z_FLAGS[] = {ZZ, SZ, UZ, OZ};
    static constexpr Bitfield W_FLAGS[] = {ZW, SW, UW, OW};

    VuUnitRegister_Mac();

    /// Updates or clear all flags (Z, S, U, O) for the given vector field,
    /// of which at least one function should be run on each instruction that modifies this register.
    /// VuVectorField takes care of mapping the field indexes to enums.
    /// See VU Users Manual page 39.
    void update_vector_field(const VuVectorField::Field field, const FpuFlags& flags);
    void clear_vector_field(const VuVectorField::Field field);

    /// A reference to the VU status flags register, which fields are changed when various MAC register write conditions occur.
    /// See VU Users Manual page 39.
    VuUnitRegister_Status* status;
};

/// The VU unit Clipping flags register.
/// See VU Users Manual page 39.
/// Bitfields are organsied by {Neg/Pos}{X/Y/Z}_{digit below} for:
/// - Current judgement = 0.
/// - Previous judgement = 1.
/// - 2nd previous judgement = 2.
/// - 3rd previous judgement = 3.
class VuUnitRegister_Clipping : public SizedWordRegister
{
public:
    static constexpr Bitfield NEGX_0 = Bitfield(0, 1);
    static constexpr Bitfield POSX_0 = Bitfield(1, 1);
    static constexpr Bitfield NEGY_0 = Bitfield(2, 1);
    static constexpr Bitfield POSY_0 = Bitfield(3, 1);
    static constexpr Bitfield NEGZ_0 = Bitfield(4, 1);
    static constexpr Bitfield POSZ_0 = Bitfield(5, 1);
    static constexpr Bitfield NEGX_1 = Bitfield(6, 1);
    static constexpr Bitfield POSX_1 = Bitfield(7, 1);
    static constexpr Bitfield NEGY_1 = Bitfield(8, 1);
    static constexpr Bitfield POSY_1 = Bitfield(9, 1);
    static constexpr Bitfield NEGZ_1 = Bitfield(10, 1);
    static constexpr Bitfield POSZ_1 = Bitfield(11, 1);
    static constexpr Bitfield NEGX_2 = Bitfield(12, 1);
    static constexpr Bitfield POSX_2 = Bitfield(13, 1);
    static constexpr Bitfield NEGY_2 = Bitfield(14, 1);
    static constexpr Bitfield POSY_2 = Bitfield(15, 1);
    static constexpr Bitfield NEGZ_2 = Bitfield(16, 1);
    static constexpr Bitfield POSZ_2 = Bitfield(17, 1);
    static constexpr Bitfield NEGX_3 = Bitfield(18, 1);
    static constexpr Bitfield POSX_3 = Bitfield(19, 1);
    static constexpr Bitfield NEGY_3 = Bitfield(20, 1);
    static constexpr Bitfield POSY_3 = Bitfield(21, 1);
    static constexpr Bitfield NEGZ_3 = Bitfield(22, 1);
    static constexpr Bitfield POSZ_3 = Bitfield(23, 1);

    // Shifts the register 6-bits (judgement) right, evicting the MSB 6-bits (LSB's set to 0).
    // Bits 24-31 are always set to 0 when this function is run.
    // See VU Users Manual page 75 & 202.
    // Designed to be used in the CLIP instruction first, then set the clipping results.
    void shift_judgement();
};

/// The VU unit CMSAR register.
/// See VU Users Manual page 202.
/// Used by CMSAR0 and CMSAR1.
class VuUnitRegister_Cmsar : public SizedWordRegister
{
public:
    static constexpr Bitfield CMSAR = Bitfield(0, 16);
};
