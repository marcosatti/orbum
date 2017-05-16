#include "Common/Types/Register/Register32_t.h"

#include "Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "Resources/EE/EECore/Types/EECoreFPURegisters_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"

EECoreFPU_t::EECoreFPU_t(const std::shared_ptr<EECoreCOP0_t>& cop0) :
	COP0(cop0),
	FPR{ std::make_shared<Register32_t>("EECore FPU FPR0", false, false), std::make_shared<Register32_t>("EECore FPU FPR1", false, false), std::make_shared<Register32_t>("EECore FPU FPR2", false, false), std::make_shared<Register32_t>("EECore FPU FPR3", false, false), std::make_shared<Register32_t>("EECore FPU FPR4", false, false), std::make_shared<Register32_t>("EECore FPU FPR5", false, false), std::make_shared<Register32_t>("EECore FPU FPR6", false, false), std::make_shared<Register32_t>("EECore FPU FPR7", false, false),
	std::make_shared<Register32_t>("EECore FPU FPR8", false, false), std::make_shared<Register32_t>("EECore FPU FPR9", false, false), std::make_shared<Register32_t>("EECore FPU FPR10", false, false), std::make_shared<Register32_t>("EECore FPU FPR11", false, false), std::make_shared<Register32_t>("EECore FPU FPR12", false, false), std::make_shared<Register32_t>("EECore FPU FPR13", false, false), std::make_shared<Register32_t>("EECore FPU FPR14", false, false), std::make_shared<Register32_t>("EECore FPU FPR15", false, false),
	std::make_shared<Register32_t>("EECore FPU FPR16", false, false), std::make_shared<Register32_t>("EECore FPU FPR17", false, false), std::make_shared<Register32_t>("EECore FPU FPR18", false, false), std::make_shared<Register32_t>("EECore FPU FPR19", false, false), std::make_shared<Register32_t>("EECore FPU FPR20", false, false), std::make_shared<Register32_t>("EECore FPU FPR21", false, false), std::make_shared<Register32_t>("EECore FPU FPR22", false, false), std::make_shared<Register32_t>("EECore FPU FPR23", false, false),
	std::make_shared<Register32_t>("EECore FPU FPR24", false, false), std::make_shared<Register32_t>("EECore FPU FPR25", false, false), std::make_shared<Register32_t>("EECore FPU FPR26", false, false), std::make_shared<Register32_t>("EECore FPU FPR27", false, false), std::make_shared<Register32_t>("EECore FPU FPR28", false, false), std::make_shared<Register32_t>("EECore FPU FPR29", false, false), std::make_shared<Register32_t>("EECore FPU FPR30", false, false), std::make_shared<Register32_t>("EECore FPU FPR31", false, false) },
	ACC(std::make_shared<Register32_t>("EECore FPU ACC", false, false)),
	IRR(std::make_shared<EECoreFPURegister_IRR_t>("EECore FPU IRR", false, false)),
	CSR(std::make_shared<EECoreFPURegister_CSR_t>("EECore FPU CSR", false, false)),
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
