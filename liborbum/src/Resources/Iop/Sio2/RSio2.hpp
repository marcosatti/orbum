#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

#include "Resources/Iop/Sio2/Sio2Registers.hpp"
#include "Resources/Iop/Sio2/Sio2Ports.hpp"

/// SIO2 resources.
/// Responsible for communication with controllers and memory cards.
/// "SIO2 is a DMA interface for the SIO" - IopHW.h from PCSX2. See also IopSio2.h/cpp.
/// A lot of information can be found through the PS2SDK too: https://github.com/ps2dev/ps2sdk/tree/master/iop/system/sio2log/src.
struct RSio2
{
	RSio2();

	/// SIO2 ports (16 total).
	Sio2Port_Full port_0;
	Sio2Port_Full port_1;
	Sio2Port_Full port_2;
	Sio2Port_Full port_3;
	Sio2Port_Slim port_4;
	Sio2Port_Slim port_5;
	Sio2Port_Slim port_6;
	Sio2Port_Slim port_7;
	Sio2Port_Slim port_8;
	Sio2Port_Slim port_9;
	Sio2Port_Slim port_a;
	Sio2Port_Slim port_b;
	Sio2Port_Slim port_c;
	Sio2Port_Slim port_d;
	Sio2Port_Slim port_e;
	Sio2Port_Slim port_f;
	Sio2Port ports[Constants::IOP::SIO2::NUMBER_PORTS];

	/// Common registers.
	DmaFifoQueue<> data_in;
	DmaFifoQueue<> data_out;
	Sio2Register_Ctrl ctrl;
	SizedWordRegister recv1;         // TODO: for now, returns device unplugged magic value (0x1D100).
	SizedWordRegister recv2;         // Constant 0xF value.
	SizedWordRegister recv3;
	SizedWordRegister register_8278;
	SizedWordRegister register_827c;
	SizedWordRegister intr;          // Also known as the STAT register.
};