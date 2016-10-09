#include "stdafx.h"

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/COP0_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/EE/EECore/COP1/COP1_t.h"
#include "Common/PS2Resources/EE/EECore/COP1/Types/COP1_BitfieldRegisters_t.h"
#include "Common/PS2Resources/Types/Registers/FPRegister32_t.h"


COP1_t::COP1_t(const PS2Resources_t* const PS2Resources) : 
	PS2ResourcesSubobject(PS2Resources),
	FPR{ std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(),
		 std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(),
		 std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(),
		 std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>() },
	ACC(std::make_shared<FPRegister32_t>()),
	IRR(std::make_shared<COP1RegisterIRR_t>()),
	CSR(std::make_shared<COP1RegisterCSR_t>()),
	BitfieldRegisters { IRR, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
						nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, CSR }
{
}

bool COP1_t::isCOP1Usable() const
{
	// Check that CU[bit 1] == 1 (ie: >0) in the status register.
	if ((getRootResources()->EE->EECore->COP0->Status->getFieldValue(COP0RegisterStatus_t::Fields::CU) & 0x2) > 0)
		return true;
	else
		return false;
}
