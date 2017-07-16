#include "Common/Types/Register/Register16_t.h"

#include "Resources/IOP/SIO0/SIO0_t.h"

SIO0_t::SIO0_t() :
	DATA(std::make_shared<Register16_t>("SIO0 DATA", true, true)),
	STAT(std::make_shared<Register16_t>("SIO0 STAT", true, true)),
	MODE(std::make_shared<Register16_t>("SIO0 MODE", true, true)),
	CTRL(std::make_shared<Register16_t>("SIO0 CTRL", true, true))
{
}
