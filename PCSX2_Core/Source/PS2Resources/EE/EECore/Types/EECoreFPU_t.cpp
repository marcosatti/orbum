#include "stdafx.h"

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "Common/Types/MIPSCoprocessor/COP0Registers_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPURegisters_t.h"
#include "Common/Types/Registers/FPRegister32_t.h"


EECoreFPU_t::EECoreFPU_t(const PS2Resources_t* const PS2Resources) : 
	PS2ResourcesSubobject(PS2Resources),
	FPR{ std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(),
		 std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(),
		 std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(),
		 std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>(), std::make_shared<FPRegister32_t>() },
	ACC(std::make_shared<FPRegister32_t>()),
	IRR(std::make_shared<EECoreFPURegister_IRR_t>()),
	CSR(std::make_shared<EECoreFPURegister_CSR_t>()),
	FCR { IRR,     nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
	      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
	      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
	      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, CSR }
{
}

bool EECoreFPU_t::isCoprocessorUsable() const
{
	// Check that CU[bit 1] == 1 (ie: >0) in the status register.
	if ((getRootResources()->EE->EECore->COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::CU) & 0x2) > 0)
		return true;
	else
		return false;
}
