#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Common/Types/Register/Register32_t.h"
#include "Common/Types/Register/Register128_t.h"
#include "Common/Types/Register/ConstantRegister128_t.h"
#include "Common/Types/Register/PCRegister32_t.h"
#include "Common/Types/Register/LinkRegister128_t.h"

EECoreR5900_t::EECoreR5900_t() : 
	PC(std::make_shared<PCRegister32_t>("EECore R5900 PC", false, false)),
	ZeroRegister(std::make_shared<ConstantRegister128_t>("EECore R5900 GPR0 (Zero)", false, false)),
	LinkRegister(std::make_shared<LinkRegister128_t>("EECore R5900 GPR31 (Link)", false, false, PC)),
	GPR{ ZeroRegister, std::make_shared<Register128_t>("EECore R5900 GPR1", false, false), std::make_shared<Register128_t>("EECore R5900 GPR2", false, false), std::make_shared<Register128_t>("EECore R5900 GPR3", false, false), std::make_shared<Register128_t>("EECore R5900 GPR4", false, false), std::make_shared<Register128_t>("EECore R5900 GPR5", false, false), std::make_shared<Register128_t>("EECore R5900 GPR6", false, false), std::make_shared<Register128_t>("EECore R5900 GPR7", false, false),
		std::make_shared<Register128_t>("EECore R5900 GPR8", false, false), std::make_shared<Register128_t>("EECore R5900 GPR9", false, false), std::make_shared<Register128_t>("EECore R5900 GPR10", false, false), std::make_shared<Register128_t>("EECore R5900 GPR11", false, false), std::make_shared<Register128_t>("EECore R5900 GPR12", false, false), std::make_shared<Register128_t>("EECore R5900 GPR13", false, false), std::make_shared<Register128_t>("EECore R5900 GPR14", false, false), std::make_shared<Register128_t>("EECore R5900 GPR15", false, false),
		std::make_shared<Register128_t>("EECore R5900 GPR16", false, false), std::make_shared<Register128_t>("EECore R5900 GPR17", false, false), std::make_shared<Register128_t>("EECore R5900 GPR18", false, false), std::make_shared<Register128_t>("EECore R5900 GPR19", false, false), std::make_shared<Register128_t>("EECore R5900 GPR20", false, false), std::make_shared<Register128_t>("EECore R5900 GPR21", false, false), std::make_shared<Register128_t>("EECore R5900 GPR22", false, false), std::make_shared<Register128_t>("EECore R5900 GPR23", false, false),
		std::make_shared<Register128_t>("EECore R5900 GPR24", false, false), std::make_shared<Register128_t>("EECore R5900 GPR25", false, false), std::make_shared<Register128_t>("EECore R5900 GPR26", false, false), std::make_shared<Register128_t>("EECore R5900 GPR27", false, false), std::make_shared<Register128_t>("EECore R5900 GPR28", false, false), std::make_shared<Register128_t>("EECore R5900 GPR29", false, false), std::make_shared<Register128_t>("EECore R5900 GPR30", false, false), LinkRegister },
	HI(std::make_shared<Register128_t>("EECore R5900 HI", false, false)),
	LO(std::make_shared<Register128_t>("EECore R5900 LO", false, false)),
	SA(std::make_shared<Register32_t>("EECore R5900 SA", false, false))
{
}