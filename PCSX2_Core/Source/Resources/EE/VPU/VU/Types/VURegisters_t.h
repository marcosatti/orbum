#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Register/BitfieldRegister32_t.h"

/*
The VU FBRST register.
See VU Users Manual page 203.
*/
class VURegister_FBRST_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int FB0 = 0;
		static constexpr int RS0 = 1;
		static constexpr int DE0 = 2;
		static constexpr int TE0 = 3;
		static constexpr int FB1 = 4;
		static constexpr int RS1 = 5;
		static constexpr int DE1 = 6;
		static constexpr int TE1 = 7;
	};

	VURegister_FBRST_t();
};

