#include "stdafx.h"

#include "Common/Types/MIPSCoprocessor/COP0Registers_t.h"

COP0RegisterReserved_t::COP0RegisterReserved_t()
{
}

COP0RegisterEPC_t::COP0RegisterEPC_t()
{
	registerField(Fields::EPC, "EPC", 0, 32, 0);
}