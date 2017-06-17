#pragma once

#include <memory>

class Register32_t;

/*
SIO2 resources.
Responsible for communication with controllers and memory cards.
"SIO2 is a DMA interface for the SIO" - IopHW.h from PCSX2. See also IopSio2.h/cpp.
A lot of information can be found through the PS2SDK too: https://github.com/ps2dev/ps2sdk/tree/master/iop/system/sio2log/src.
*/
class SIO2_t
{
public:
	SIO2_t();

	/*
	SIO2 Registers.
	*/
	std::shared_ptr<Register32_t> PORT0_CTRL3; // TODO: figure out these names properly.
	std::shared_ptr<Register32_t> PORT1_CTRL3;
	std::shared_ptr<Register32_t> PORT2_CTRL3;
	std::shared_ptr<Register32_t> PORT3_CTRL3;
	std::shared_ptr<Register32_t> PORT4_CTRL3;
	std::shared_ptr<Register32_t> PORT5_CTRL3;
	std::shared_ptr<Register32_t> PORT6_CTRL3;
	std::shared_ptr<Register32_t> PORT7_CTRL3;
	std::shared_ptr<Register32_t> PORT8_CTRL3;
	std::shared_ptr<Register32_t> PORT9_CTRL3;
	std::shared_ptr<Register32_t> PORTA_CTRL3;
	std::shared_ptr<Register32_t> PORTB_CTRL3;
	std::shared_ptr<Register32_t> PORTC_CTRL3;
	std::shared_ptr<Register32_t> PORTD_CTRL3;
	std::shared_ptr<Register32_t> PORTE_CTRL3;
	std::shared_ptr<Register32_t> PORTF_CTRL3;

	std::shared_ptr<Register32_t> PORT0_CTRL1;
	std::shared_ptr<Register32_t> PORT0_CTRL2;
	std::shared_ptr<Register32_t> PORT1_CTRL1;
	std::shared_ptr<Register32_t> PORT1_CTRL2;
	std::shared_ptr<Register32_t> PORT2_CTRL1;
	std::shared_ptr<Register32_t> PORT2_CTRL2;
	std::shared_ptr<Register32_t> PORT3_CTRL1;
	std::shared_ptr<Register32_t> PORT3_CTRL2;
	std::shared_ptr<Register32_t> DATA_OUT;
	std::shared_ptr<Register32_t> DATA_IN;
	std::shared_ptr<Register32_t> CTRL;
	std::shared_ptr<Register32_t> STAT_826C;
	std::shared_ptr<Register32_t> STAT_8270;
	std::shared_ptr<Register32_t> STAT_8274;
	std::shared_ptr<Register32_t> REGISTER_8278;
	std::shared_ptr<Register32_t> REGISTER_827C;
	std::shared_ptr<Register32_t> INTR;          // Also known as the STAT register.
};