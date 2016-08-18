#include "stdafx.h"

#include "Common/PS2 Resources/EE/EECore/COP0/COP0_t.h"
#include "Common/PS2 Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"
#include "Common/PS2 Resources/PS2Resources_t.h"

bool COP0_t::isCOP0Usable() const
{
	// First check for kernel mode (Status.EXL == 1) - the coprocessor is always available in this mode. If not, then check that CU[bit 0] == 1 in the status register.
	if (getRootResources()->EE->EECore->COP0->Status->getFieldValue(RegisterStatus_t::Fields::EXL) == 1)
		return true;
	else if ((getRootResources()->EE->EECore->COP0->Status->getFieldValue(RegisterStatus_t::Fields::CU) & 0x1) > 0)
		return true;
	else
		return false;
}