#include "stdafx.h"

#include "Common/PS2Resources/EE/EECore/COP1/Types/COP1_BitfieldRegisters_t.h"

RegisterIRR_t::RegisterIRR_t()
{
	registerField(Fields::Rev, 0, 8, 0);
	registerField(Fields::Imp, 8, 8, 0x2E);
}

RegisterCSR_t::RegisterCSR_t()
{
	registerField(Fields::SU, 3, 1, 0);
	registerField(Fields::SO, 4, 1, 0);
	registerField(Fields::SD, 5, 1, 0);
	registerField(Fields::SI, 6, 1, 0);
	registerField(Fields::U, 14, 1, 0);
	registerField(Fields::O, 15, 1, 0);
	registerField(Fields::D, 16, 1, 0);
	registerField(Fields::I, 17, 1, 0);
	registerField(Fields::C, 23, 1, 0);
}
