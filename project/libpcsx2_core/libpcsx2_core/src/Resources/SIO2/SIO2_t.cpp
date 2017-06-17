#include "Common/Types/Register/Register32_t.h"

#include "Resources/SIO2/SIO2_t.h"

SIO2_t::SIO2_t() :
	PORT0_CTRL3(std::make_shared<Register32_t>("SIO2 PORT0_CTRL3", true, true)),
	PORT1_CTRL3(std::make_shared<Register32_t>("SIO2 PORT1_CTRL3", true, true)),
	PORT2_CTRL3(std::make_shared<Register32_t>("SIO2 PORT2_CTRL3", true, true)),
	PORT3_CTRL3(std::make_shared<Register32_t>("SIO2 PORT3_CTRL3", true, true)),
	PORT4_CTRL3(std::make_shared<Register32_t>("SIO2 PORT4_CTRL3", true, true)),
	PORT5_CTRL3(std::make_shared<Register32_t>("SIO2 PORT5_CTRL3", true, true)),
	PORT6_CTRL3(std::make_shared<Register32_t>("SIO2 PORT6_CTRL3", true, true)),
	PORT7_CTRL3(std::make_shared<Register32_t>("SIO2 PORT7_CTRL3", true, true)),
	PORT8_CTRL3(std::make_shared<Register32_t>("SIO2 PORT8_CTRL3", true, true)),
	PORT9_CTRL3(std::make_shared<Register32_t>("SIO2 PORT9_CTRL3", true, true)),
	PORTA_CTRL3(std::make_shared<Register32_t>("SIO2 PORTA_CTRL3", true, true)),
	PORTB_CTRL3(std::make_shared<Register32_t>("SIO2 PORTB_CTRL3", true, true)),
	PORTC_CTRL3(std::make_shared<Register32_t>("SIO2 PORTC_CTRL3", true, true)),
	PORTD_CTRL3(std::make_shared<Register32_t>("SIO2 PORTD_CTRL3", true, true)),
	PORTE_CTRL3(std::make_shared<Register32_t>("SIO2 PORTE_CTRL3", true, true)),
	PORTF_CTRL3(std::make_shared<Register32_t>("SIO2 PORTF_CTRL3", true, true)),
	PORT0_CTRL1(std::make_shared<Register32_t>("SIO2 PORT0_CTRL1", true, true)),
	PORT0_CTRL2(std::make_shared<Register32_t>("SIO2 PORT0_CTRL2", true, true)),
	PORT1_CTRL1(std::make_shared<Register32_t>("SIO2 PORT1_CTRL1", true, true)),
	PORT1_CTRL2(std::make_shared<Register32_t>("SIO2 PORT1_CTRL2", true, true)),
	PORT2_CTRL1(std::make_shared<Register32_t>("SIO2 PORT2_CTRL1", true, true)),
	PORT2_CTRL2(std::make_shared<Register32_t>("SIO2 PORT2_CTRL2", true, true)),
	PORT3_CTRL1(std::make_shared<Register32_t>("SIO2 PORT3_CTRL1", true, true)),
	PORT3_CTRL2(std::make_shared<Register32_t>("SIO2 PORT3_CTRL2", true, true)),
	DATA_OUT(std::make_shared<Register32_t>("SIO2 DATA_OUT", true, true)),
	DATA_IN(std::make_shared<Register32_t>("SIO2 DATA_IN", true, true)),
	CTRL(std::make_shared<Register32_t>("SIO2 CTRL", true, true)),
	STAT_826C(std::make_shared<Register32_t>("SIO2 STAT_826C", true, true)),
	STAT_8270(std::make_shared<Register32_t>("SIO2 STAT_8270", true, true)),
	STAT_8274(std::make_shared<Register32_t>("SIO2 STAT_8274", true, true)),
	REGISTER_8278(std::make_shared<Register32_t>("SIO2 REGISTER_8278", true, true)),
	REGISTER_827C(std::make_shared<Register32_t>("SIO2 REGISTER_827C", true, true)),
	INTR(std::make_shared<Register32_t>("SIO2 REGISTER_INTR", true, true))
{
}
