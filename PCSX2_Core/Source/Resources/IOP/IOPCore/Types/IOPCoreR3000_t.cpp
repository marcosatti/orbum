#include "stdafx.h"

#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/Registers/MIPS/PCRegister32_t.h"
#include "Common/Types/Registers/Constant/ConstantRegister32_t.h"
#include "Common/Types/Registers/MIPS/LinkRegister32_t.h"
#include "Common/Types/MIPSBranchDelay/MIPSBranchDelay_t.h"

#include "Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"

IOPCoreR3000_t::IOPCoreR3000_t() :
	PC(std::make_shared<PCRegister32_t>()),
	BD(std::make_shared<MIPSBranchDelay_t>(PC)),
	ZeroRegister(std::make_shared<ConstantRegister32_t>()),
	LinkRegister(std::make_shared<LinkRegister32_t>(PC)),
	GPR{ ZeroRegister, std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(),
		std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(),
		std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(),
		std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), std::make_shared<Register32_t>(), LinkRegister },
	HI(std::make_shared<Register32_t>()),
	LO(std::make_shared<Register32_t>())
{
}