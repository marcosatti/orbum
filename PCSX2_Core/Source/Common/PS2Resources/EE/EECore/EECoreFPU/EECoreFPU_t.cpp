#include "stdafx.h"

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreCOP0/EECoreCOP0_t.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreFPU/EECoreFPU_t.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/COP1_BitfieldRegisters_t.h"
#include "Common/PS2Resources/Types/Registers/FPRegister32_t.h"


EECoreFPU_t::EECoreFPU_t(const PS2Resources_t* const PS2Resources) : 
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

bool EECoreFPU_t::isCoprocessorUsable() const
{
	// Check that CU[bit 1] == 1 (ie: >0) in the status register.
	if ((getRootResources()->EE->EECore->COP0->Status->getFieldValue(COP0RegisterStatus_t::Fields::CU) & 0x2) > 0)
		return true;
	else
		return false;
}
