#include "stdafx.h"

#include "Common/Types/Register/Register32_t.h"

#include "Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "Resources/EE/EECore/Types/EECoreFPURegisters_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"

EECoreFPU_t::EECoreFPU_t(const std::shared_ptr<EECoreCOP0_t>& cop0) :
	COP0(cop0),
	FPR{ std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(),
	std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(),
	std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(),
	std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>() },
	ACC(std::make_shared<Register32_t>()),
	IRR(std::make_shared<EECoreFPURegister_IRR_t>()),
	CSR(std::make_shared<EECoreFPURegister_CSR_t>()),
	FCR{ IRR, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, CSR }
{
}

bool EECoreFPU_t::isCoprocessorUsable(const System_t context) const
{
	// Check that CU[bit 1] == 1 (ie: >0) in the status register.
	if ((COP0->Status->getFieldValue(context, EECoreCOP0Register_Status_t::Fields::CU) & 0x2) > 0)
		return true;
	else
		return false;
}
