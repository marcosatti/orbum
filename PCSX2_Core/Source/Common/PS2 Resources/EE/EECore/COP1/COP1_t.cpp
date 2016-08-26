#include "stdafx.h"

#include "Common/PS2 Resources/EE/EECore/COP1/COP1_t.h"
#include "Common/PS2 Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"
#include "Common/PS2 Resources/PS2Resources_t.h"

bool COP1_t::isCOP1Usable() const
{
	// Check that CU[bit 1] == 1 (ie: >0) in the status register.
	if ((getRootResources()->EE->EECore->COP0->Status->getFieldValue(RegisterStatus_t::Fields::CU) & 0x2) > 0)
		return true;
	else
		return false;
}