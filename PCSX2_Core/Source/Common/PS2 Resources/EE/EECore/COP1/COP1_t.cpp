#include "stdafx.h"

#include "Common/PS2 Resources/EE/EECore/COP1/COP1_t.h"
#include "Common/PS2 Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"
#include "Common/PS2 Resources/PS2Resources_t.h"

bool COP1_t::isCOP1Usable() const
{
	// First check for kernel mode (Status.EXL == 1) - the coprocessor is always available in this mode. If not, then check that CU[bit 1] == 1 in the status register.
	// We need direct access to this value - using getFieldValue will result in a recursive isCOP1Usable ending in a crash (stack overflow).
	if (getRootResources()->EE->EECore->COP0->Status->getRawFieldValue(RegisterStatus_t::Fields::EXL) == 1)
		return true;
	else if ((getRootResources()->EE->EECore->COP0->Status->getRawFieldValue(RegisterStatus_t::Fields::CU) & 0x2) > 0)
		return true;
	else
		return false;
}