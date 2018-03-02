#pragma once

#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

#include "Resources/Iop/Sio2/Sio2Registers.hpp"

/// SIO2 resources.
/// Responsible for communication with controllers and memory cards.
/// "SIO2 is a DMA interface for the SIO" - IopHW.h from PCSX2. See also IopSio2.h/cpp.
/// A lot of information can be found through the PS2SDK too: https://github.com/ps2dev/ps2sdk/tree/master/iop/system/sio2log/src.
struct RSio2
{
	RSio2();

	DmaFifoQueue<> data_fifo; // Fifo queue used for sending and receiving data (can change direction).

	SizedWordRegister port0_ctrl3; // TODO: figure out these names properly.
	SizedWordRegister port1_ctrl3;
	SizedWordRegister port2_ctrl3;
	SizedWordRegister port3_ctrl3;
	SizedWordRegister port4_ctrl3;
	SizedWordRegister port5_ctrl3;
	SizedWordRegister port6_ctrl3;
	SizedWordRegister port7_ctrl3;
	SizedWordRegister port8_ctrl3;
	SizedWordRegister port9_ctrl3;
	SizedWordRegister porta_ctrl3;
	SizedWordRegister portb_ctrl3;
	SizedWordRegister portc_ctrl3;
	SizedWordRegister portd_ctrl3;
	SizedWordRegister porte_ctrl3;
	SizedWordRegister portf_ctrl3;

	SizedWordRegister port0_ctrl1;
	SizedWordRegister port0_ctrl2;
	SizedWordRegister port1_ctrl1;
	SizedWordRegister port1_ctrl2;
	SizedWordRegister port2_ctrl1;
	SizedWordRegister port2_ctrl2;
	SizedWordRegister port3_ctrl1;
	SizedWordRegister port3_ctrl2;
	Sio2Register_Data data_in;
	Sio2Register_Data data_out;
	Sio2Register_Ctrl ctrl;
	SizedWordRegister recv1;
	SizedWordRegister recv2;         // Constant 0xF value.
	SizedWordRegister recv3;
	SizedWordRegister register_8278;
	SizedWordRegister register_827c;
	SizedWordRegister intr;          // Also known as the STAT register.
};