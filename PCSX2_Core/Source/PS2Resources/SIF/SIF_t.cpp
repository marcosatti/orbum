#include "stdafx.h"

#include "PS2Resources/SIF/SIF_t.h"
#include "Common/Types/Registers/Register32_t.h"

SIF_t::SIF_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	MSCOM(std::make_shared<Register32_t>("SIF: MSCOM")),
	SMCOM(std::make_shared<Register32_t>("SIF: SMCOM")),
	MSFLG(std::make_shared<Register32_t>("SIF: MSFLG")),
	SMFLG(std::make_shared<Register32_t>("SIF: SMFLG")),
	REGISTER_F240(std::make_shared<Register32_t>()),
	REGISTER_F250(std::make_shared<Register32_t>()),
	REGISTER_F260(std::make_shared<Register32_t>()),
	REGISTER_F300(std::make_shared<Register32_t>()),
	REGISTER_F380(std::make_shared<Register32_t>())
{
}
