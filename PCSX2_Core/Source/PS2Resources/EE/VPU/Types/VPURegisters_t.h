#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
The VPU STAT register.
See VU Users Manual page 203.
*/
class VPURegister_STAT_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 VBS0 = 0;
		static constexpr u8 VDS0 = 1;
		static constexpr u8 VTS0 = 2;
		static constexpr u8 VFS0 = 3;
		static constexpr u8 DIV0 = 4;
		static constexpr u8 IBS0 = 5;
		static constexpr u8 VBS1 = 6;
		static constexpr u8 VDS1 = 7;
		static constexpr u8 VTS1 = 8;
		static constexpr u8 VFS1 = 9;
		static constexpr u8 VGW1 = 10;
		static constexpr u8 DIV1 = 11;
		static constexpr u8 EFU1 = 12;
	};

	VPURegister_STAT_t();
};