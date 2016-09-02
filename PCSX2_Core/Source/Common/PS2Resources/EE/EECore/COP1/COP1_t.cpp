#include "stdafx.h"

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/COP0_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/EE/EECore/COP1/COP1_t.h"
#include "Common/PS2Resources/EE/EECore/COP1/Types/COP1_BitfieldRegisters_t.h"
#include "Common/PS2Resources/EE/EECore/COP1/Types/FPRegister32_t.h"


COP1_t::COP1_t(const PS2Resources_t* const PS2Resources) : PS2ResourcesSubobject(PS2Resources)
{
	// Initialise Class.
	std::shared_ptr<FPRegister32_t> FPR[32] = {
		std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(),
		std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(),
		std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(),
		std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>()
	};

	IRR = std::make_shared<RegisterIRR_t>(); // Also known as FCR[0].
	CSR = std::make_shared<RegisterCSR_t>(); // Also known as FCR[31].

	std::shared_ptr<BitfieldRegister32_t> BitfieldRegisters[32] = {
		IRR, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, CSR
	};
}

bool COP1_t::isCOP1Usable() const
{
	// Check that CU[bit 1] == 1 (ie: >0) in the status register.
	if ((getRootResources()->EE->EECore->COP0->Status->getFieldValue(RegisterStatus_t::Fields::CU) & 0x2) > 0)
		return true;
	else
		return false;
}
