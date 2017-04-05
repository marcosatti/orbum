#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Register/BitfieldRegister32_t.h"

/*
The VPU STAT register.
See VU Users Manual page 203.
*/
class VPURegister_STAT_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int VBS0 = 0;
		static constexpr int VDS0 = 1;
		static constexpr int VTS0 = 2;
		static constexpr int VFS0 = 3;
		static constexpr int DIV0 = 4;
		static constexpr int IBS0 = 5;
		static constexpr int VBS1 = 6;
		static constexpr int VDS1 = 7;
		static constexpr int VTS1 = 8;
		static constexpr int VFS1 = 9;
		static constexpr int VGW1 = 10;
		static constexpr int DIV1 = 11;
		static constexpr int EFU1 = 12;
	};

	VPURegister_STAT_t();
};