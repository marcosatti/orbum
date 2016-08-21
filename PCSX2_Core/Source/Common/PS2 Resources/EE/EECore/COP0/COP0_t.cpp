#include "stdafx.h"

#include "Common/PS2 Resources/EE/EECore/COP0/COP0_t.h"
#include "Common/PS2 Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"
#include "Common/PS2 Resources/PS2Resources_t.h"

bool COP0_t::isOperatingUserMode() const
{
	const u32& KSU = Status->getRawFieldValue(RegisterStatus_t::Fields::KSU);
	const u32& ERL = Status->getRawFieldValue(RegisterStatus_t::Fields::ERL);
	const u32& EXL = Status->getRawFieldValue(RegisterStatus_t::Fields::EXL);

	if (KSU == 2 && ERL == 0 && EXL == 0)
		return true;
	else
		return false;
}

bool COP0_t::isOperatingSupervisorMode() const
{
	const u32& KSU = Status->getRawFieldValue(RegisterStatus_t::Fields::KSU);
	const u32& ERL = Status->getRawFieldValue(RegisterStatus_t::Fields::ERL);
	const u32& EXL = Status->getRawFieldValue(RegisterStatus_t::Fields::EXL);

	if (KSU == 1 && ERL == 0 && EXL == 0)
		return true;
	else
		return false;
}

bool COP0_t::isOperatingKernelMode() const
{
	const u32& KSU = Status->getRawFieldValue(RegisterStatus_t::Fields::KSU);
	const u32& ERL = Status->getRawFieldValue(RegisterStatus_t::Fields::ERL);
	const u32& EXL = Status->getRawFieldValue(RegisterStatus_t::Fields::EXL);

	if (KSU == 0 || ERL == 1 || EXL == 1)
		return true;
	else
		return false;
}

bool COP0_t::isCOP0Usable() const
{
	// First check for kernel mode - the COP0 is always available in this mode. If not, then check that CU[bit 0] == 1 (ie: >0) in the status register.
	if (isOperatingKernelMode())
		return true;
	else if ((getRootResources()->EE->EECore->COP0->Status->getRawFieldValue(RegisterStatus_t::Fields::CU) & 0x1) > 0)
		return true;
	else
		return false;
}
