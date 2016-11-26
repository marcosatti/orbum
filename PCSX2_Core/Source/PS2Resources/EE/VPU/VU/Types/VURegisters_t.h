#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
The VU FBRST register.
See VU Users Manual page 203.
*/
class VURegister_FBRST_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 FB0 = 0;
		static constexpr u8 RS0 = 1;
		static constexpr u8 DE0 = 2;
		static constexpr u8 TE0 = 3;
		static constexpr u8 FB1 = 4;
		static constexpr u8 RS1 = 5;
		static constexpr u8 DE1 = 6;
		static constexpr u8 TE1 = 7;
	};

	VURegister_FBRST_t();
};

