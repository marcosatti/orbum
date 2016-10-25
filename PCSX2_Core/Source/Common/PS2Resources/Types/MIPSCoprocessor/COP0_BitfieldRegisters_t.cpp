#include "stdafx.h"

#include "Common/PS2Resources/Types/MIPSCoprocessor/COP0_BitfieldRegisters_t.h"

COP0RegisterReserved_t::COP0RegisterReserved_t()
{
}

COP0RegisterEPC_t::COP0RegisterEPC_t()
{
	registerField(Fields::EPC, "EPC", 0, 32, 0);
}