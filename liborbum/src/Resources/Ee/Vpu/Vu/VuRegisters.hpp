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
};
