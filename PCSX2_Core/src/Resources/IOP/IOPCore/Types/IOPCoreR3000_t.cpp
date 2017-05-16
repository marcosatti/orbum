#include "Common/Types/Register/Register32_t.h"
#include "Common/Types/Register/PCRegister32_t.h"
#include "Common/Types/Register/ConstantRegister32_t.h"
#include "Common/Types/Register/LinkRegister32_t.h"

#include "Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"

IOPCoreR3000_t::IOPCoreR3000_t() :
	PC(std::make_shared<PCRegister32_t>("IOPCore R3000 PC", false, false)),
	ZeroRegister(std::make_shared<ConstantRegister32_t>("IOPCore R3000 GPR0 (Zero)", false, false)),
	LinkRegister(std::make_shared<LinkRegister32_t>("IOPCore R3000 GPR31 (Link)", false, false, PC)),
	GPR{ ZeroRegister, std::make_shared<Register32_t>("IOPCore R3000 GPR1", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR2", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR3", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR4", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR5", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR6", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR7", false, false),
		std::make_shared<Register32_t>("IOPCore R3000 GPR8", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR9", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR10", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR11", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR12", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR13", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR14", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR15", false, false),
		std::make_shared<Register32_t>("IOPCore R3000 GPR16", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR17", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR18", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR19", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR20", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR21", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR22", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR23", false, false),
		std::make_shared<Register32_t>("IOPCore R3000 GPR24", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR25", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR26", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR27", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR28", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR29", false, false), std::make_shared<Register32_t>("IOPCore R3000 GPR30", false, false), LinkRegister },
	HI(std::make_shared<Register32_t>("IOPCore R3000 HI", false, false)),
	LO(std::make_shared<Register32_t>("IOPCore R3000 LO", false, false))
{
}