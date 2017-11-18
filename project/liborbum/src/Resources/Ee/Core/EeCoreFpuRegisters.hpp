#pragma once

#include "Common/Types/FpuFlags.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

/// FPU registers, see EE Core Users Manual page 158 onwards.

class EeCoreFpuRegister_Irr : public SizedWordRegister
{
public:
	static constexpr Bitfield REV = Bitfield(0, 8);
	static constexpr Bitfield IMP = Bitfield(8, 8);

	static constexpr uword INITIAL_VALUE = 0x00002E00;

	EeCoreFpuRegister_Irr();
};

class EeCoreFpuRegister_Csr : public SizedWordRegister
{
public:
	static constexpr Bitfield SU = Bitfield(3, 1);
	static constexpr Bitfield SO = Bitfield(4, 1);
	static constexpr Bitfield SD = Bitfield(5, 1);
	static constexpr Bitfield SI = Bitfield(6, 1);
	static constexpr Bitfield U  = Bitfield(14, 1);
	static constexpr Bitfield O  = Bitfield(15, 1);
	static constexpr Bitfield D  = Bitfield(16, 1);
	static constexpr Bitfield I  = Bitfield(17, 1);
	static constexpr Bitfield C  = Bitfield(23, 1);

	/// Functions to set status flags and update sticky flags (OR) (flags SU, SO, SD, SI).
	/// See EE Core Users Manual page 159.
	void set_u_flag_sticky(const uword value);
	void set_o_flag_sticky(const uword value);
	void set_d_flag_sticky(const uword value);
	void set_i_flag_sticky(const uword value);

	/// Update or clears the U, O, (D, I) flags, which both should be done on each instruction that modifies this register.
	/// The C flag is not changed! Needs to be done manually.
	void update_result_flags(const FpuFlags & flags);
	void clear_flags(); // Clears the D and I flags too.
};