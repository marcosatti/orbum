#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class Resources_t;
class Register32_t;
class PCRegister32_t;
class LinkRegister32_t;
class ConstantRegister32_t;

/*
The IOP MIPS R3000 CPU (used as the IOP / PSX CPU).
It uses a little-endian configuration (bit 0 is always the LSB).

There is no official documentation from Sony on any of the IOP - implementation is based off PCSX2's code, and other documents available online.
There are many user-submitted documents about the PSX architecture, which has been used to aid implementation.
*/
class IOPCoreR3000_t
{
public:
	IOPCoreR3000_t();

	/*
	The 32-bit Program Counter (PC) register.
	Points to the current instruction virtual address.
	Must be initialised before LinkRegister and BD below due to dependency.
	*/
	std::shared_ptr<PCRegister32_t> PC;

	/*
	The 32 general purpose registers. They are each 32-bits long.
	GPR[0] is hardwired to 0.
	GPR[31] is known as the link register.
	*/
	std::shared_ptr<ConstantRegister32_t> ZeroRegister;
	std::shared_ptr<LinkRegister32_t> LinkRegister;
	std::shared_ptr<Register32_t> GPR[Constants::IOP::IOPCore::R3000::NUMBER_GP_REGISTERS];

	/*
	The HI and LO registers.
	These registers are used to hold the results of integer multiply and divide operations.
	They are 32-bit long.
	*/
	std::shared_ptr<Register32_t> HI;
	std::shared_ptr<Register32_t> LO;
};

