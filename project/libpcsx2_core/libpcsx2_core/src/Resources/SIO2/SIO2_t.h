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
	std::shared_ptr<Register32_t> CTRL;
	std::shared_ptr<Register32_t> REGISTER_8278;
	std::shared_ptr<Register32_t> REGISTER_827C;
	std::shared_ptr<Register32_t> INTR;
};