#include "stdafx.h"

#include "PS2Resources/SIF/SIF_t.h"
#include "Common/Types/Registers/DebugRegister32_t.h"
#include "Common/Types/Registers/ConstantRegister32_t.h"

SIF_t::SIF_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	MSCOM(std::make_shared<DebugRegister32_t>("SIF: MSCOM")),
	SMCOM(std::make_shared<DebugRegister32_t>("SIF: SMCOM")),
	MSFLG(std::make_shared<DebugRegister32_t>("SIF: MSFLG")),
	SMFLG(std::make_shared<DebugRegister32_t>("SIF: SMFLG")),
	REGISTER_0060(std::make_shared<ConstantRegister32_t>())
{
}
