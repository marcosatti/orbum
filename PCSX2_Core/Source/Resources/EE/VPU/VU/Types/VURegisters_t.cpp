#include "stdafx.h"

#include "Resources/EE/VPU/VU/Types/VURegisters_t.h"

VURegister_FBRST_t::VURegister_FBRST_t()
{
	registerField(Fields::FB0, "FB0", 0, 1, 0);
	registerField(Fields::RS0, "RS0", 1, 1, 0);
	registerField(Fields::DE0, "DE0", 2, 1, 0);
	registerField(Fields::TE0, "TE0", 3, 1, 0);
	registerField(Fields::FB1, "FB1", 8, 1, 0);
	registerField(Fields::RS1, "RS1", 9, 1, 0);
	registerField(Fields::DE1, "DE1", 10, 1, 0);
	registerField(Fields::TE1, "TE1", 11, 1, 0);
}
