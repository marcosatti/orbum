#include "Common/Types/Register/Register32_t.h"

#include "Resources/SIO2/SIO2_t.h"

SIO2_t::SIO2_t() :
	CTRL(std::make_shared<Register32_t>("SIO2 CTRL", true, true)),
	REGISTER_8278(std::make_shared<Register32_t>("SIO2 REGISTER_8278", true, true)),
	REGISTER_827C(std::make_shared<Register32_t>("SIO2 REGISTER_827C", true, true)),
	INTR(std::make_shared<Register32_t>("SIO2 REGISTER_INTR", true, true))
{
}
