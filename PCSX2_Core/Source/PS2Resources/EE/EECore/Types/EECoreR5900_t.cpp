#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/Constant/ConstantRegister128_t.h"
#include "Common/Types/Registers/MIPS/PCRegister32_t.h"
#include "Common/Types/Registers/MIPS/LinkRegister128_t.h"
#include "Common/Types/MIPSBranchDelay/MIPSBranchDelay_t.h"

EECoreR5900_t::EECoreR5900_t() : 
	PC(std::make_shared<PCRegister32_t>()),
	BD(std::make_shared<MIPSBranchDelay_t>(PC)),
	ZeroRegister(std::make_shared<ConstantRegister128_t>()),
	LinkRegister(std::make_shared<LinkRegister128_t>(PC)),
	GPR{ ZeroRegister, std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(),
		std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), std::make_shared<Register128_t>(), LinkRegister },
	HI(std::make_shared<Register128_t>()),
	LO(std::make_shared<Register128_t>()),
	SA(std::make_shared<Register32_t>())
{
}